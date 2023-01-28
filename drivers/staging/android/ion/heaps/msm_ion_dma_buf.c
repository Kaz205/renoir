// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2011 Google, Inc.
 * Copyright (c) 2011-2020, The Linux Foundation. All rights reserved.
 */

#include <linux/device.h>
#include <linux/dma-buf.h>
#include <linux/dma-noncoherent.h>
#include <linux/err.h>
#include <linux/export.h>
#include <linux/file.h>
#include <linux/kthread.h>
#include <linux/list.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/rbtree.h>
#include <linux/slab.h>
#include <linux/msm_dma_iommu_mapping.h>

#include "msm_ion_priv.h"
#include "ion_secure_util.h"

static struct sg_table *dup_sg_table(struct sg_table *table)
{
	struct sg_table *new_table;
	int ret, i;
	struct scatterlist *sg, *new_sg;

	new_table = kzalloc(sizeof(*new_table), GFP_KERNEL);
	if (!new_table)
		return ERR_PTR(-ENOMEM);

	ret = sg_alloc_table(new_table, table->nents, GFP_KERNEL);
	if (ret) {
		kfree(new_table);
		return ERR_PTR(-ENOMEM);
	}

	new_sg = new_table->sgl;
	for_each_sg(table->sgl, sg, table->nents, i) {
		memcpy(new_sg, sg, sizeof(*sg));
		sg_dma_address(new_sg) = 0;
		sg_dma_len(new_sg) = 0;
		new_sg = sg_next(new_sg);
	}

	return new_table;
}

static void free_duped_table(struct sg_table *table)
{
	sg_free_table(table);
	kfree(table);
}

struct msm_ion_dma_buf_attachment {
	struct device *dev;
	struct sg_table *table;
	struct list_head list;
	bool dma_mapped;
	struct rw_semaphore map_rwsem;
};

static int msm_ion_dma_buf_attach(struct dma_buf *dmabuf,
			      struct dma_buf_attachment *attachment)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);
	struct ion_dma_buf_attachment *a;

	spin_lock(&buffer->freelist_lock);
	list_for_each_entry(a, &buffer->map_freelist, list) {
		if (a->dev == dev) {
			list_del(&a->list);
			spin_unlock(&buffer->freelist_lock);
			attachment->priv = a;
			return 0;
		}
	}
	spin_unlock(&buffer->freelist_lock);

	a = kmalloc(sizeof(*a), GFP_KERNEL);
	if (!a)
		return -ENOMEM;

	if (ion_dup_sg_table(&a->table, buffer->sg_table)) {
		kfree(a);
		return -ENOMEM;
	}

	a->dev = dev;
	a->dma_mapped = false;
	a->map_rwsem = (struct rw_semaphore)__RWSEM_INITIALIZER(a->map_rwsem);
	attachment->priv = a;
	a->next = buffer->attachments;
	buffer->attachments = a;

	return 0;
}

static void msm_ion_dma_buf_detatch(struct dma_buf *dmabuf,
				struct dma_buf_attachment *attachment)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);
	struct ion_dma_buf_attachment *a = attachment->priv;

	spin_lock(&buffer->freelist_lock);
	list_add(&a->list, &buffer->map_freelist);
	spin_unlock(&buffer->freelist_lock);
}

static struct sg_table
*msm_ion_map_dma_buf(struct dma_buf_attachment *attachment,
		     enum dma_data_direction direction)
{
	struct msm_ion_dma_buf_attachment *a = attachment->priv;
	int count, map_attrs = attachment->dma_map_attrs;
	struct ion_buffer *buffer = container_of(attachment->dmabuf->priv,
						 typeof(*buffer), iommu_data);
	unsigned long ino = file_inode(attachment->dmabuf->file)->i_ino;

	if (!(buffer->flags & ION_FLAG_CACHED) ||
	    !hlos_accessible_buffer(buffer))
		map_attrs |= DMA_ATTR_SKIP_CPU_SYNC;

	if ((buffer->flags & ION_FLAG_CACHED) &&
	    hlos_accessible_buffer(buffer) &&
	    dev_is_dma_coherent_hint_cached(attachment->dev))
		map_attrs |= DMA_ATTR_FORCE_COHERENT;

	if (((dev_is_dma_coherent(attachment->dev) &&
	      !(map_attrs & DMA_ATTR_FORCE_NON_COHERENT)) ||
	     (map_attrs & DMA_ATTR_FORCE_COHERENT)) &&
	    !(buffer->flags & ION_FLAG_CACHED)) {
		pr_warn_ratelimited("dev:%s Cannot DMA map uncached buffer as IO-coherent attrs:0x%lx\n",
				    dev_name(attachment->dev), map_attrs);
		return ERR_PTR(-EINVAL);
	}

	down_write(&a->map_rwsem);
	if (map_attrs & DMA_ATTR_DELAYED_UNMAP) {
		count = msm_dma_map_sg_attrs(attachment->dev, a->table->sgl,
					     a->table->nents, direction,
					     attachment->dmabuf, map_attrs);
	} else {
		count = dma_map_sg_attrs(attachment->dev, a->table->sgl,
					 a->table->nents, direction,
					 map_attrs);
	}

	if (count)
		a->dma_mapped = true;
	up_write(&a->map_rwsem);

	return count ? &a->table : ERR_PTR(-ENOMEM);
}

static void msm_ion_unmap_dma_buf(struct dma_buf_attachment *attachment,
			      struct sg_table *table,
			      enum dma_data_direction direction)
{
	int map_attrs;
	struct ion_buffer *buffer = container_of(attachment->dmabuf->priv,
						 typeof(*buffer), iommu_data);
	struct msm_ion_dma_buf_attachment *a = attachment->priv;
	unsigned long ino = file_inode(attachment->dmabuf->file)->i_ino;

	map_attrs = attachment->dma_map_attrs;
	if (!(buffer->flags & ION_FLAG_CACHED) ||
	    !hlos_accessible_buffer(buffer))
		map_attrs |= DMA_ATTR_SKIP_CPU_SYNC;

	if ((buffer->flags & ION_FLAG_CACHED) &&
	    hlos_accessible_buffer(buffer) &&
	    dev_is_dma_coherent_hint_cached(attachment->dev))
		map_attrs |= DMA_ATTR_FORCE_COHERENT;

	down_write(&a->map_rwsem);
	if (map_attrs & DMA_ATTR_DELAYED_UNMAP)
		msm_dma_unmap_sg_attrs(attachment->dev, table->sgl,
				       table->nents, direction,
				       attachment->dmabuf,
				       map_attrs);
	else
		dma_unmap_sg_attrs(attachment->dev, table->sgl, table->nents,
				   direction, map_attrs);
	a->dma_mapped = false;
	up_write(&a->map_rwsem);
}

void ion_pages_sync_for_device(struct device *dev, struct page *page,
			       size_t size, enum dma_data_direction dir)
{
	struct scatterlist sg;

	sg_init_table(&sg, 1);
	sg_set_page(&sg, page, size, 0);
	/*
	 * This is not correct - sg_dma_address needs a dma_addr_t that is valid
	 * for the targeted device, but this works on the currently targeted
	 * hardware.
	 */
	sg_dma_address(&sg) = page_to_phys(page);
	dma_sync_sg_for_device(dev, &sg, 1, dir);
}

static int msm_ion_mmap(struct dma_buf *dmabuf, struct vm_area_struct *vma)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);
	struct msm_ion_buf_lock_state *lock_state = buffer->priv_virt;
	int ret = 0;

	if (!hlos_accessible_buffer(buffer)) {
		pr_err_ratelimited("%s: this buffer cannot be mapped to userspace\n",
				   __func__);
		return -EINVAL;
	}

	if (!(buffer->flags & ION_FLAG_CACHED))
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	mutex_lock(&buffer->lock);
	/* now map it to userspace */
	ret = ion_heap_map_user(buffer->heap, buffer, vma);
	mutex_unlock(&buffer->lock);

	return ret;
}

static inline bool is_msm_ion_dma_buf(struct ion_buffer *buffer)
{
	return buffer->heap->buf_ops.attach == msm_ion_dma_buf_attach;
}

int msm_ion_dma_buf_lock(struct dma_buf *dmabuf)
{
	struct ion_buffer *buffer;
	struct msm_ion_buf_lock_state *lock_state;
	int ret = 0;

	if (!dmabuf)
		return -EINVAL;

	buffer = container_of(dmabuf->priv, typeof(*buffer), iommu_data);
	lock_state = buffer->priv_virt;

	if ((!lock_state) || !is_msm_ion_dma_buf(buffer)) {
		pr_err("%s: userspace map locking is not supported for this dma-buf\n",
		       __func__);
		return -EINVAL;
	}

	if (lock_state->locked) {
		ret = -EINVAL;
		pr_err("%s: buffer is already locked\n", __func__);
	} else if (lock_state->vma_count) {
		ret = -EBUSY;
	} else {
		lock_state->locked = true;
	}

	return ret;
}
EXPORT_SYMBOL(msm_ion_dma_buf_lock);

void msm_ion_dma_buf_unlock(struct dma_buf *dmabuf)
{
	struct ion_buffer *buffer;
	struct msm_ion_buf_lock_state *lock_state;

	if (!dmabuf)
		return;

	buffer = container_of(dmabuf->priv, typeof(*buffer), iommu_data);
	lock_state = buffer->priv_virt;

	if (!lock_state || !is_msm_ion_dma_buf(buffer)) {
		pr_err("%s: userspace map unlocking is not supported for this dma-buf\n",
		       __func__);
		return;
	}

	if (!lock_state->locked)
		pr_warn("%s: buffer is already unlocked\n", __func__);
	else
		lock_state->locked = false;
}
EXPORT_SYMBOL(msm_ion_dma_buf_unlock);

static void msm_ion_dma_buf_release(struct dma_buf *dmabuf)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);

	msm_dma_buf_freed(&buffer->iommu_data);
	ion_free(buffer);
}

static void *msm_ion_dma_buf_vmap(struct dma_buf *dmabuf)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);
	void *vaddr;

	if (!hlos_accessible_buffer(buffer))
		return ERR_PTR(-EINVAL);

	mutex_lock(&buffer->kmap_lock);
	if (buffer->kmap_cnt) {
		buffer->kmap_cnt++;
		vaddr = buffer->vaddr;
	} else {
		vaddr = ion_heap_map_kernel(buffer);
		if (IS_ERR_OR_NULL(vaddr)) {
			vaddr = ERR_PTR(-EINVAL);
		} else {
			buffer->vaddr = vaddr;
			buffer->kmap_cnt++;
		}
	}
	mutex_unlock(&buffer->kmap_lock);

	return vaddr;
}

static void msm_ion_dma_buf_vunmap(struct dma_buf *dmabuf, void *vaddr)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);

	mutex_lock(&buffer->kmap_lock);
	if (hlos_accessible_buffer(buffer) && !--buffer->kmap_cnt)
		ion_heap_unmap_kernel(buffer);
	mutex_unlock(&buffer->kmap_lock);
}

static void *msm_ion_dma_buf_kmap(struct dma_buf *dmabuf, unsigned long offset)
{
	/*
	 * TODO: Once clients remove their hacks where they assume kmap(ed)
	 * addresses are virtually contiguous implement this properly
	 */
	void *vaddr = msm_ion_dma_buf_vmap(dmabuf);

	if (IS_ERR(vaddr))
		return vaddr;

	return vaddr + offset * PAGE_SIZE;
}

static void msm_ion_dma_buf_kunmap(struct dma_buf *dmabuf, unsigned long offset,
			       void *ptr)
{
	msm_ion_dma_buf_vunmap(dmabuf, NULL);
}

static int ion_sgl_sync_range(struct device *dev, struct scatterlist *sgl,
			      unsigned int nents, unsigned long offset,
			      unsigned long length,
			      enum dma_data_direction dir, bool for_cpu)
{
	int i;
	struct scatterlist *sg;
	unsigned int len = 0;
	dma_addr_t sg_dma_addr;

	for_each_sg(sgl, sg, nents, i) {
		if (sg_dma_len(sg) == 0)
			break;

		if (i > 0) {
			if (get_dma_ops(dev)) {
				pr_warn_ratelimited("Partial cmo only supported with 1 segment\n"
					"is dma_set_max_seg_size being set on dev:%s\n",
					dev_name(dev));
			}
			return -EINVAL;
		}
	}

	for_each_sg(sgl, sg, nents, i) {
		unsigned int sg_offset, sg_left, size = 0;

		if (i == 0)
			sg_dma_addr = sg_dma_address(sg);

		len += sg->length;
		if (len <= offset) {
			sg_dma_addr += sg->length;
			continue;
		}

		sg_left = len - offset;
		sg_offset = sg->length - sg_left;

		size = (length < sg_left) ? length : sg_left;
		if (for_cpu)
			dma_sync_single_range_for_cpu(dev, sg_dma_addr,
						      sg_offset, size, dir);
		else
			dma_sync_single_range_for_device(dev, sg_dma_addr,
							 sg_offset, size, dir);

		offset += size;
		length -= size;
		sg_dma_addr += sg->length;

		if (length == 0)
			break;
	}

	return 0;
}

static int msm_ion_dma_buf_begin_cpu_access(struct dma_buf *dmabuf,
					    enum dma_data_direction direction)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);
	struct msm_ion_dma_buf_attachment *a;

	if (!hlos_accessible_buffer(buffer))
		return -EPERM;

	if (!(buffer->flags & ION_FLAG_CACHED))
		return 0;


	list_for_each_entry(a, &buffer->attachments, list) {
		if (down_read_trylock(&a->map_rwsem)) {
			if (a->dma_mapped)
				dma_sync_sg_for_cpu(a->dev, a->table->sgl,
				    	a->table->nents, direction);
			up_read(&a->map_rwsem);
		}
	}
	return 0;
}

static int msm_ion_dma_buf_end_cpu_access(struct dma_buf *dmabuf,
					  enum dma_data_direction direction)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);
	struct msm_ion_dma_buf_attachment *a;
	unsigned long ino = file_inode(dmabuf->file)->i_ino;

	if (!hlos_accessible_buffer(buffer))
		return -EPERM;

	if (!(buffer->flags & ION_FLAG_CACHED))
		return 0;

	list_for_each_entry(a, &buffer->attachments, list) {
		if (down_read_trylock(&a->map_rwsem)) {
			if (a->dma_mapped)
				dma_sync_sg_for_device(a->dev, a->table->sgl, a->table->nents,
				       	direction);
			up_read(&a->map_rwsem);
		}
	}

	return 0;
}

static int msm_ion_dma_buf_begin_cpu_access_partial(struct dma_buf *dmabuf,
						enum dma_data_direction dir,
						unsigned int offset,
						unsigned int len)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);
	struct msm_ion_dma_buf_attachment *a;
	unsigned long ino = file_inode(dmabuf->file)->i_ino;
	int ret = 0;

	if (!hlos_accessible_buffer(buffer))
		return -EPERM;

	if (!(buffer->flags & ION_FLAG_CACHED))
		return 0;

	list_for_each_entry(a, &buffer->attachments, list) {
		if (down_read_trylock(&a->map_rwsem)) {
			if (a->dma_mapped)
				ret = ion_sgl_sync_range(a->dev, a->table->sgl, a->table->nents,
							offset, len, dir, true);
		up_read(&a->map_rwsem);
	}

	return ret;
}

static int msm_ion_dma_buf_end_cpu_access_partial(struct dma_buf *dmabuf,
					      enum dma_data_direction direction,
					      unsigned int offset,
					      unsigned int len)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);
	struct msm_ion_dma_buf_attachment *a;
	int ret = 0;

	if (!hlos_accessible_buffer(buffer))
		return -EPERM;

	if (!(buffer->flags & ION_FLAG_CACHED))
		return 0;

	list_for_each_entry(a, &buffer->attachments, list) {
		if (down_read_trylock(&a->map_rwsem)) {
			if (a->dma_mapped)
				ret = ion_sgl_sync_range(a->dev, a->table->sgl, a->table->nents,
							offset, len, direction, false);
		up_read(&a->map_rwsem);
	}
out:
	return ret;
}

static int msm_ion_dma_buf_get_flags(struct dma_buf *dmabuf,
				 unsigned long *flags)
{
	struct ion_buffer *buffer = container_of(dmabuf->priv, typeof(*buffer),
						 iommu_data);
	*flags = buffer->flags;

	return 0;
}

const struct dma_buf_ops msm_ion_dma_buf_ops = {
	.map_dma_buf = msm_ion_map_dma_buf,
	.unmap_dma_buf = msm_ion_unmap_dma_buf,
	.mmap = msm_ion_mmap,
	.release = msm_ion_dma_buf_release,
	.attach = msm_ion_dma_buf_attach,
	.detach = msm_ion_dma_buf_detatch,
	.begin_cpu_access = msm_ion_dma_buf_begin_cpu_access,
	.end_cpu_access = msm_ion_dma_buf_end_cpu_access,
	.begin_cpu_access_partial = msm_ion_dma_buf_begin_cpu_access_partial,
	.end_cpu_access_partial = msm_ion_dma_buf_end_cpu_access_partial,
	.map = msm_ion_dma_buf_kmap,
	.unmap = msm_ion_dma_buf_kunmap,
	.vmap = msm_ion_dma_buf_vmap,
	.vunmap = msm_ion_dma_buf_vunmap,
	.get_flags = msm_ion_dma_buf_get_flags,
};
