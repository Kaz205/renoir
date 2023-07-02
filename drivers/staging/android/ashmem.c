// SPDX-License-Identifier: GPL-2.0
/* mm/ashmem.c
 *
 * Anonymous Shared Memory Subsystem, ashmem
 *
 * Copyright (C) 2008 Google, Inc.
 *
 * Robert Love <rlove@google.com>
 */

#define pr_fmt(fmt) "ashmem: " fmt

#include <linux/miscdevice.h>
#include <linux/mman.h>
#include <linux/shmem_fs.h>
#include "ashmem.h"

/**
 * struct ashmem_area - The anonymous shared memory area
 * @ashmem_mutex:	The mutex lock for ashmem operations
 * @file:		The shmem-based backing file
 * @size:		The size of the mapping, in bytes
 * @prot_mask:		The allowed protection bits, as vm_flags
 *
 * The lifecycle of this structure is from our parent file's open() until
 * its release().
 *
 * Warning: Mappings do NOT pin this structure; It dies on close()
 */
struct ashmem_area {
	struct mutex ashmem_mutex;
	struct file *file;
	size_t size;
	unsigned long prot_mask;
};

static struct kmem_cache *ashmem_area_cachep __read_mostly;
static DEFINE_MUTEX(prot_mask_lock);

#define PROT_MASK		(PROT_EXEC | PROT_READ | PROT_WRITE)

/**
 * ashmem_open() - Opens an Anonymous Shared Memory structure
 * @inode:	   The backing file's index node(?)
 * @file:	   The backing file
 *
 * Please note that the ashmem_area is not returned by this function - It is
 * instead written to "file->private_data".
 *
 * Return: 0 if successful, or another code if unsuccessful.
 */
static int ashmem_open(struct inode *inode, struct file *file)
{
	struct ashmem_area *asma;
	int ret;

	ret = generic_file_open(inode, file);
	if (ret)
		return ret;

	asma = kmem_cache_alloc(ashmem_area_cachep, GFP_KERNEL);
	if (!asma)
		return -ENOMEM;

	mutex_init(&asma->ashmem_mutex);
	asma->prot_mask = PROT_MASK;
	file->private_data = asma;

	return 0;
}

/**
 * ashmem_release() - Releases an Anonymous Shared Memory structure
 * @ignored:	      The backing file's Index Node(?) - It is ignored here.
 * @file:	      The backing file
 *
 * Return: 0 if successful. If it is anything else, go have a coffee and
 * try again.
 */
static int ashmem_release(struct inode *ignored, struct file *file)
{
	struct ashmem_area *asma = file->private_data;

	if (asma->file)
		fput(asma->file);
	kmem_cache_free(ashmem_area_cachep, asma);
	mutex_destroy(&asma->ashmem_mutex);

	return 0;
}

static ssize_t ashmem_read_iter(struct kiocb *iocb, struct iov_iter *iter)
{
	struct ashmem_area *asma = iocb->ki_filp->private_data;
	int ret = 0;

	/* If size is not set, or set to 0, always return EOF. */
	if (!READ_ONCE(asma->size))
		return ret;

	if (!READ_ONCE(asma->file))
		return -EBADF;

	/*
	 * asma and asma->file are used outside the lock here.  We assume
	 * once asma->file is set it will never be changed, and will not
	 * be destroyed until all references to the file are dropped and
	 * ashmem_release is called.
	 */
	ret = vfs_iter_read(asma->file, iter, &iocb->ki_pos, 0);
	mutex_lock(&asma->ashmem_mutex);
	if (ret > 0)
		asma->file->f_pos = iocb->ki_pos;
	mutex_unlock(&asma->ashmem_mutex);
	return ret;
}

static loff_t ashmem_llseek(struct file *file, loff_t offset, int origin)
{
	struct ashmem_area *asma = file->private_data;
	loff_t ret;

	if (!READ_ONCE(asma->size))
		return -EINVAL;

	if (!READ_ONCE(asma->file))
		return -EBADF;

	ret = vfs_llseek(asma->file, offset, origin);
	if (ret < 0)
		return ret;

	/** Copy f_pos from backing file, since f_ops->llseek() sets it */
	file->f_pos = asma->file->f_pos;
	return ret;
}

static inline vm_flags_t calc_vm_may_flags(unsigned long prot)
{
	return _calc_vm_trans(prot, PROT_READ,  VM_MAYREAD) |
	       _calc_vm_trans(prot, PROT_WRITE, VM_MAYWRITE) |
	       _calc_vm_trans(prot, PROT_EXEC,  VM_MAYEXEC);
}

static int ashmem_vmfile_mmap(struct file *file, struct vm_area_struct *vma)
{
	/* do not allow to mmap ashmem backing shmem file directly */
	return -EPERM;
}

static unsigned long
ashmem_vmfile_get_unmapped_area(struct file *file, unsigned long addr,
				unsigned long len, unsigned long pgoff,
				unsigned long flags)
{
	return current->mm->get_unmapped_area(file, addr, len, pgoff, flags);
}

static int ashmem_mmap(struct file *file, struct vm_area_struct *vma)
{
	static struct file_operations vmfile_fops;
	struct ashmem_area *asma = file->private_data;
	int ret = 0;
	size_t size = READ_ONCE(asma->size);

	/* user needs to SET_SIZE before mapping */
	if (!size)
		return -EINVAL;

	/* requested mapping size larger than object size */
	if (vma->vm_end - vma->vm_start > PAGE_ALIGN(size))
		return -EINVAL;

	mutex_lock(&asma->ashmem_mutex);
	mutex_lock(&prot_mask_lock);
	/* requested protection bits must match our allowed protection mask */
	if ((vma->vm_flags & ~calc_vm_prot_bits(asma->prot_mask, 0)) &
	    calc_vm_prot_bits(PROT_MASK, 0)) {
		mutex_unlock(&prot_mask_lock);
		mutex_unlock(&asma->ashmem_mutex);
		return -EPERM;
	}
	vma->vm_flags &= ~calc_vm_may_flags(~asma->prot_mask);
	mutex_unlock(&prot_mask_lock);

	if (!asma->file) {
		struct file *vmfile;
		struct inode *inode;

		/* ... and allocate the backing shmem file */
		vmfile = shmem_file_setup(0, asma->size, vma->vm_flags);
		if (IS_ERR(vmfile)) {
			ret = PTR_ERR(vmfile);
			goto out;
		}
		vmfile->f_mode |= FMODE_LSEEK;
		inode = file_inode(vmfile);
		asma->file = vmfile;
		/*
		 * override mmap operation of the vmfile so that it can't be
		 * remapped which would lead to creation of a new vma with no
		 * asma permission checks. Have to override get_unmapped_area
		 * as well to prevent VM_BUG_ON check for f_ops modification.
		 */
		if (!vmfile_fops.mmap) {
			vmfile_fops = *vmfile->f_op;
			vmfile_fops.mmap = ashmem_vmfile_mmap;
			vmfile_fops.get_unmapped_area =
					ashmem_vmfile_get_unmapped_area;
		}
		vmfile->f_op = &vmfile_fops;
	}
	get_file(asma->file);

	/*
	 * XXX - Reworked to use shmem_zero_setup() instead of
	 * shmem_set_file while we're in staging. -jstultz
	 */
	if (vma->vm_flags & VM_SHARED) {
		ret = shmem_zero_setup(vma);
		if (ret) {
			fput(asma->file);
			goto out;
		}
	} else {
		vma_set_anonymous(vma);
	}

	if (vma->vm_file)
		fput(vma->vm_file);
	vma->vm_file = asma->file;

out:
	mutex_unlock(&asma->ashmem_mutex);
	return ret;
}

static int set_prot_mask(struct ashmem_area *asma, unsigned long prot)
{
	int ret = 0;

	mutex_lock(&prot_mask_lock);
	/* the user can only remove, not add, protection bits */
	if ((asma->prot_mask & prot) != prot) {
		ret = -EINVAL;
		goto out;
	}

	/* does the application expect PROT_READ to imply PROT_EXEC? */
	if ((prot & PROT_READ) && (current->personality & READ_IMPLIES_EXEC))
		prot |= PROT_EXEC;

	asma->prot_mask = prot;

out:
	mutex_unlock(&prot_mask_lock);
	return ret;
}

static long ashmem_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct ashmem_area *asma = file->private_data;
	long ret = -EINVAL;

	switch (cmd) {
	case ASHMEM_SET_NAME:
	case ASHMEM_GET_NAME:
	case ASHMEM_PIN:
	case ASHMEM_UNPIN:
		return 0;
	case ASHMEM_SET_SIZE:
		mutex_lock(&asma->ashmem_mutex);
		if (!asma->file) {
			ret = 0;
			asma->size = (size_t)arg;
		}
		mutex_unlock(&asma->ashmem_mutex);
		return ret;
	case ASHMEM_GET_SIZE:
		return asma->size;
	case ASHMEM_SET_PROT_MASK:
		return set_prot_mask(asma, arg);
	case ASHMEM_GET_PROT_MASK:
		return asma->prot_mask;
	case ASHMEM_GET_PIN_STATUS:
		return ASHMEM_IS_PINNED;
	case ASHMEM_PURGE_ALL_CACHES:
		return capable(CAP_SYS_ADMIN) ? 0 : -EPERM;
	}

	return -ENOTTY;
}

/* support of 32bit userspace on 64bit platforms */
#ifdef CONFIG_COMPAT
static long compat_ashmem_ioctl(struct file *file, unsigned int cmd,
				unsigned long arg)
{
	switch (cmd) {
	case COMPAT_ASHMEM_SET_SIZE:
		cmd = ASHMEM_SET_SIZE;
		break;
	case COMPAT_ASHMEM_SET_PROT_MASK:
		cmd = ASHMEM_SET_PROT_MASK;
		break;
	}
	return ashmem_ioctl(file, cmd, arg);
}
#endif
static const struct file_operations ashmem_fops = {
	.owner = THIS_MODULE,
	.open = ashmem_open,
	.release = ashmem_release,
	.read_iter = ashmem_read_iter,
	.llseek = ashmem_llseek,
	.mmap = ashmem_mmap,
	.unlocked_ioctl = ashmem_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = compat_ashmem_ioctl,
#endif
};

static struct miscdevice ashmem_misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "ashmem",
	.fops = &ashmem_fops,
};

static int __init ashmem_init(void)
{
	int ret;

	ashmem_area_cachep = kmem_cache_create("ashmem_area_cache",
					       sizeof(struct ashmem_area),
					       0, 0, NULL);
	if (!ashmem_area_cachep) {
		pr_err("failed to create slab cache\n");
		return -ENOMEM;
	}

	ret = misc_register(&ashmem_misc);
	if (ret) {
		pr_err("failed to register misc device!\n");
		kmem_cache_destroy(ashmem_area_cachep);
		return ret;
	}

	pr_info("initialized\n");

	return 0;
}
device_initcall(ashmem_init);
