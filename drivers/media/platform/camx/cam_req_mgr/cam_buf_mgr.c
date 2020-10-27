// SPDX-License-Identifier: GPL-2.0
/*
 * Spectra camera buffer manager
 *
 * Copyright 2020 Google LLC.
 */

#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <linux/dma-buf.h>
#include <media/cam_req_mgr.h>

#include "cam_req_mgr_dev.h"
#include "cam_debug_util.h"
#include "cam_buf_mgr.h"

struct cmm_node {
	struct page *page;
	struct list_head list;
};

struct cmm_dma_buf_attachment {
	struct sg_table *table;
	struct list_head list;
	bool dma_mapped;
};

/**
 * struct cmm_buf_context - camera buffer manager context
 *
 * @dev:         device context
 * @dev_lock:    lock protecting the tree of nodes
 */
struct cmm_buf_context {
	struct device *dev;
	struct mutex dev_lock;	/* device lock */
};

/**
 * struct cmm_buffer - metadata for a buffer
 *
 * @flags:    buffer specific flags
 * @size:     size of the buffer
 * @b_lock:   protects the camera buffer fields
 * @kmap_cnt: number of times the buffer is mapped to the kernel
 * @vaddr:    the kernel mapping if kmap_cnt is not zero
 * @sg_table: the sg table for the buffer
 * @attached: list of entry attachments
 */
struct cmm_buffer {
	unsigned long flags;
	size_t size;
	struct mutex b_lock;	/* buffer lock */
	int kmap_cnt;
	void *vaddr;
	struct sg_table *sg_table;
	struct list_head attached;
};

static struct cmm_buf_context *idev;

static void *_cmm_sgt_alloc(unsigned int num_pages)
{
	struct sg_table *sgt;
	int rc;

	sgt = kzalloc(sizeof(*sgt), GFP_KERNEL);
	if (IS_ERR_OR_NULL(sgt))
		return ERR_CAST(sgt);

	rc = sg_alloc_table(sgt, num_pages, GFP_KERNEL);
	if (rc) {
		sgt = ERR_PTR(rc);
		goto err_sgt_free;
	}

	return sgt;

err_sgt_free:
	sg_free_table(sgt);

	return ERR_CAST(sgt);
}

static void _cmm_sgt_free(struct sg_table *sgt)
{
	struct scatterlist *scl;
	int i = 0;

	if (sgt->sgl) {
		for_each_sg(sgt->sgl, scl, sgt->nents, i)
			__free_pages(sg_page(scl), 0);
	}

	sg_free_table(sgt);

	kfree(sgt);
}

static struct cmm_node *_cmm_node_create(struct cmm_buffer *cbuf)
{
	struct cmm_node *node;
	struct page *page;

	node = kmalloc(sizeof(*node), GFP_KERNEL);
	if (IS_ERR_OR_NULL(node))
		return ERR_CAST(node);

	page = alloc_page(GFP_KERNEL);
	if (IS_ERR_OR_NULL(page))
		goto err_free_info;

	node->page = page;

	INIT_LIST_HEAD(&node->list);

	return node;

err_free_info:
	kfree(node);

	return ERR_CAST(page);
}

static void _cmm_node_destroy(struct cmm_node *node, struct scatterlist *scl,
			      struct scatterlist *scl_sync)
{
	if (!node)
		return;

	if (scl_sync) {
		sg_set_page(scl_sync, node->page, PAGE_SIZE, 0);
		sg_dma_address(scl_sync) = page_to_phys(node->page);
	}

	sg_set_page(scl, node->page, PAGE_SIZE, 0);
	sg_dma_address(scl) = page_to_phys(node->page);

	list_del(&node->list);

	kfree(node);
}

/* TODO: Revisiting this code. This piece of code is partly extracted
 * from MSM ION manager, but it could be simplified. In general this
 * manager could be refactored and all sg lists manipulations should be
 * optimized. In best case, significant part of the code can be removed
 * and migrated to the V4L2 APIs exported by "videobuf2-dma-sg".
 */
static int _cmm_nodes_update(struct cmm_buffer *cbuf, unsigned int num_pages)
{
	struct list_head head;
	struct cmm_node *node;
	struct sg_table *sgt;
	struct scatterlist *scl;
	int i, rc = 0;

	sgt = _cmm_sgt_alloc(num_pages);
	if (IS_ERR_OR_NULL(sgt)) {
		CAM_ERR(CAM_MEM, "Cannot allocate cbuf nents");
		return PTR_ERR(sgt);
	}

	INIT_LIST_HEAD(&head);

	for (i = 0; i < num_pages; i++) {
		node = _cmm_node_create(cbuf);
		if (IS_ERR(node)) {
			rc = PTR_ERR(node);
			break;
		}
		list_add_tail(&node->list, &head);
	}

	scl = cbuf->sg_table->sgl;
	for (i = 0; i < num_pages; i++) {
		node = list_first_entry_or_null(&head, struct cmm_node, list);
		_cmm_node_destroy(node, scl, sgt->sgl);
		sgt->sgl = sg_next(sgt->sgl);
		scl	 = sg_next(scl);
	}

	_cmm_sgt_free(sgt);

	return 0;
}

static int _cmm_cbuf_alloc(struct cmm_buffer *cbuf)
{
	size_t num_pages = cbuf->size >> PAGE_SHIFT;
	int rc;

	if (num_pages > totalram_pages() / 2)
		return -ENOMEM;

	cbuf->sg_table = _cmm_sgt_alloc(num_pages);
	if (IS_ERR_OR_NULL(cbuf->sg_table)) {
		CAM_ERR(CAM_MEM, "Cannot allocate cbuf scl table");
		return PTR_ERR(cbuf->sg_table);
	}

	rc = _cmm_nodes_update(cbuf, num_pages);
	if (rc) {
		CAM_ERR(CAM_MEM, "Cannot update nodes/num_pages");
		goto err_cbuf_sgt_free;
	}

	return rc;

err_cbuf_sgt_free:
	_cmm_sgt_free(cbuf->sg_table);

	return rc;
}

static void _cmm_cbuf_free(struct cmm_buffer *cbuf)
{
	_cmm_sgt_free(cbuf->sg_table);
}

static struct cmm_buffer *_cmm_cbuf_create(struct cmm_buf_context *ctx,
					   unsigned long len,
					   unsigned long flags)
{
	struct cmm_buffer *cbuf;
	struct sg_table *table;
	int ret;

	CAM_DBG(CAM_MEM, "Create camera cbuf: len:%lu", len);

	cbuf = kzalloc(sizeof(*cbuf), GFP_KERNEL);
	if (!cbuf)
		return ERR_PTR(-ENOMEM);

	cbuf->size = PAGE_ALIGN(len);
	cbuf->flags = flags;

	ret = _cmm_cbuf_alloc(cbuf);
	if (ret)
		goto err_buf_free;

	if (IS_ERR_OR_NULL(cbuf->sg_table)) {
		ret = PTR_ERR(cbuf->sg_table);
		goto err_cbuf_free;
	}

	table = cbuf->sg_table;

	INIT_LIST_HEAD(&cbuf->attached);
	mutex_init(&cbuf->b_lock);

	return cbuf;

err_cbuf_free:
	_cmm_sgt_free(cbuf->sg_table);
err_buf_free:
	kfree(cbuf);

	return ERR_PTR(ret);
}

static void _cmm_cbuf_destroy(struct cmm_buffer *cbuf)
{
	CAM_DBG(CAM_MEM, "Destroy camera buffer: %pK", cbuf);

	if (cbuf->kmap_cnt > 0) {
		pr_err_once("Likely missing a call to unmap\n");
		vunmap(cbuf->vaddr);
	}

	mutex_destroy(&cbuf->b_lock);
	_cmm_cbuf_free(cbuf);
	kfree(cbuf);
}

static void *_cmm_dma_kmap_get(struct cmm_buffer *cbuf)
{
	struct scatterlist *scl;
	pgprot_t pgprot;
	struct sg_table *sgt = cbuf->sg_table;
	int npages = PAGE_ALIGN(cbuf->size) / PAGE_SIZE;
	struct page **pages = vmalloc(sizeof(struct page *) * npages);
	struct page **tmp = pages;
	void *vaddr;
	int i, j;

	if (cbuf->kmap_cnt) {
		cbuf->kmap_cnt++;
		return cbuf->vaddr;
	}

	if (!pages)
		return ERR_PTR(-ENOMEM);

	if (cbuf->flags & CAM_MEM_FLAG_CACHE)
		pgprot = PAGE_KERNEL;
	else
		pgprot = pgprot_writecombine(PAGE_KERNEL);

	for_each_sg(sgt->sgl, scl, sgt->nents, i) {
		int entry_pages = PAGE_ALIGN(scl->length) / PAGE_SIZE;
		struct page *page = sg_page(scl);

		WARN_ON(i >= npages);
		for (j = 0; j < entry_pages; j++)
			*(tmp++) = page++;
	}

	vaddr = vmap(pages, npages, VM_MAP, pgprot);
	vfree(pages);

	if (IS_ERR_OR_NULL(vaddr)) {
		if (WARN_ONCE(1, "Map should return valid pointer"))
			return ERR_PTR(-ENOMEM);
	}

	cbuf->vaddr = vaddr;
	cbuf->kmap_cnt++;

	return vaddr;
}

static void _cmm_dma_kmap_put(struct cmm_buffer *cbuf)
{
	if (cbuf->kmap_cnt == 0) {
		pr_warn_ratelimited("Likely unbalanced map/unmap, pid:%d\n",
				    current->pid);
		return;
	}

	cbuf->kmap_cnt--;
	if (!cbuf->kmap_cnt) {
		vunmap(cbuf->vaddr);
		cbuf->vaddr = NULL;
	}
}

static struct sg_table *_cmm_dma_sg_table_new(struct sg_table *sgt)
{
	struct sg_table *new_sgt;
	struct scatterlist *scl, *new_scl;
	int ret, i;

	new_sgt = kzalloc(sizeof(*new_sgt), GFP_KERNEL);
	if (!new_sgt)
		return ERR_PTR(-ENOMEM);

	ret = sg_alloc_table(new_sgt, sgt->nents, GFP_KERNEL);
	if (ret) {
		kfree(new_sgt);
		return ERR_PTR(-ENOMEM);
	}

	new_scl = new_sgt->sgl;
	for_each_sg(sgt->sgl, scl, sgt->nents, i) {
		memcpy(new_scl, scl, sizeof(*scl));
		sg_dma_address(new_scl) = 0;
		sg_dma_len(new_scl) = 0;
		new_scl = sg_next(new_scl);
	}

	return new_sgt;
}

static void _cmm_dma_sg_table_del(struct sg_table *sgt)
{
	sg_free_table(sgt);
	kfree(sgt);
}

static int _op_dma_buf_attach(struct dma_buf *dmabuf,
			      struct dma_buf_attachment *attachment)
{
	struct cmm_buffer *cbuf = dmabuf->priv;
	struct cmm_dma_buf_attachment *new_att;
	struct sg_table *sgt;
	int rc;

	new_att = kzalloc(sizeof(*new_att), GFP_KERNEL);
	if (IS_ERR_OR_NULL(new_att))
		return PTR_ERR(new_att);

	sgt = _cmm_dma_sg_table_new(cbuf->sg_table);
	if (IS_ERR_OR_NULL(sgt)) {
		rc = PTR_ERR(sgt);
		goto err_free_att;
	}

	new_att->table = sgt;
	new_att->dma_mapped = false;
	INIT_LIST_HEAD(&new_att->list);

	attachment->priv = new_att;

	mutex_lock(&cbuf->b_lock);
	list_add(&new_att->list, &cbuf->attached);
	mutex_unlock(&cbuf->b_lock);

	return 0;

err_free_att:
	kfree(new_att);

	return rc;
}

static void _op_dma_buf_detatch(struct dma_buf *dmabuf,
				struct dma_buf_attachment *attachment)
{
	struct cmm_dma_buf_attachment *a = attachment->priv;
	struct cmm_buffer *buffer = dmabuf->priv;

	mutex_lock(&buffer->b_lock);
	list_del(&a->list);
	mutex_unlock(&buffer->b_lock);
	_cmm_dma_sg_table_del(a->table);

	kfree(a);
}

static struct sg_table *_op_dma_buf_map(struct dma_buf_attachment *attachment,
					enum dma_data_direction direction)
{
	struct cmm_dma_buf_attachment *a = attachment->priv;
	struct sg_table *table;
	int count, map_attrs;
	struct cmm_buffer *buffer = attachment->dmabuf->priv;

	table = a->table;

	map_attrs = attachment->dma_map_attrs;
	if (!(buffer->flags & CAM_MEM_FLAG_CACHE))
		map_attrs |= DMA_ATTR_SKIP_CPU_SYNC;

	mutex_lock(&buffer->b_lock);
	count = dma_map_sg_attrs(attachment->dev, table->sgl,
				 table->nents, direction,
				 map_attrs);

	if (count <= 0) {
		mutex_unlock(&buffer->b_lock);
		return ERR_PTR(-ENOMEM);
	}

	a->dma_mapped = true;
	mutex_unlock(&buffer->b_lock);

	return table;
}

static void _op_dma_buf_unmap(struct dma_buf_attachment *attachment,
			      struct sg_table *table,
			      enum dma_data_direction direction)
{
	int map_attrs;
	struct cmm_buffer *buffer = attachment->dmabuf->priv;
	struct cmm_dma_buf_attachment *a = attachment->priv;

	map_attrs = attachment->dma_map_attrs;
	if (!(buffer->flags & CAM_MEM_FLAG_CACHE))
		map_attrs |= DMA_ATTR_SKIP_CPU_SYNC;

	mutex_lock(&buffer->b_lock);
	dma_unmap_sg_attrs(attachment->dev, table->sgl, table->nents,
			   direction, map_attrs);
	a->dma_mapped = false;
	mutex_unlock(&buffer->b_lock);
}

static int _op_dma_buf_mmap(struct dma_buf *dmabuf, struct vm_area_struct *vma)
{
	struct cmm_buffer *buffer = dmabuf->priv;
	struct sg_table *table = buffer->sg_table;
	unsigned long addr = vma->vm_start;
	unsigned long offset = vma->vm_pgoff * PAGE_SIZE;
	struct scatterlist *sg;
	int i, ret = 0;

	if (!(buffer->flags & CAM_MEM_FLAG_CACHE))
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

	vma->vm_private_data = buffer;

	mutex_lock(&buffer->b_lock);

	for_each_sg(table->sgl, sg, table->nents, i) {
		struct page *page = sg_page(sg);
		unsigned long remainder = vma->vm_end - addr;
		unsigned long len = sg->length;

		if (offset >= sg->length) {
			offset -= sg->length;
			continue;
		} else if (offset) {
			page += offset / PAGE_SIZE;
			len = sg->length - offset;
			offset = 0;
		}
		len = min(len, remainder);
		ret = remap_pfn_range(vma, addr, page_to_pfn(page), len,
				      vma->vm_page_prot);
		if (ret)
			goto err_vm_close;

		addr += len;
		if (addr >= vma->vm_end)
			break;
	}

	mutex_unlock(&buffer->b_lock);

	return ret;

err_vm_close:
	mutex_unlock(&buffer->b_lock);
	CAM_ERR(CAM_MEM, "failure mapping buffer to userspace");

	return ret;
}

static void _op_dma_buf_release(struct dma_buf *dmabuf)
{
	struct cmm_buffer *buffer = dmabuf->priv;

	_cmm_cbuf_destroy(buffer);
	kfree(dmabuf->exp_name);
}

static void *_op_dma_buf_vmap(struct dma_buf *dmabuf)
{
	struct cmm_buffer *buffer = dmabuf->priv;
	void *vaddr = ERR_PTR(-EINVAL);

	mutex_lock(&buffer->b_lock);
	vaddr = _cmm_dma_kmap_get(buffer);
	mutex_unlock(&buffer->b_lock);

	return vaddr;
}

static void _op_dma_buf_vunmap(struct dma_buf *dmabuf, void *vaddr)
{
	struct cmm_buffer *buffer = dmabuf->priv;

	mutex_lock(&buffer->b_lock);
	_cmm_dma_kmap_put(buffer);
	mutex_unlock(&buffer->b_lock);
}

static void *_op_dma_buf_kmap(struct dma_buf *dmabuf, unsigned long offset)
{
	void *vaddr = _op_dma_buf_vmap(dmabuf);

	if (IS_ERR_OR_NULL(vaddr))
		return ERR_CAST(vaddr);

	return vaddr + offset * PAGE_SIZE;
}

static void _op_dma_buf_kunmap(struct dma_buf *dmabuf, unsigned long offset,
			       void *ptr)
{
	_op_dma_buf_vunmap(dmabuf, ptr);
}

static int _op_dma_buf_beg_cpu_access(struct dma_buf *dmabuf,
				      enum dma_data_direction direction)
{
	struct cmm_buffer *cbuf = dmabuf->priv;
	struct cmm_dma_buf_attachment *att;
	int ret = 0;

	mutex_lock(&cbuf->b_lock);
	list_for_each_entry(att, &cbuf->attached, list) {
		dma_sync_sg_for_cpu(idev->dev, att->table->sgl,
				    att->table->nents, direction);
	}
	mutex_unlock(&cbuf->b_lock);

	return ret;
}

static int _op_dma_buf_end_cpu_access(struct dma_buf *dmabuf,
				      enum dma_data_direction direction)
{
	struct cmm_buffer *cbuf = dmabuf->priv;
	struct cmm_dma_buf_attachment *att;
	int ret = 0;

	mutex_lock(&cbuf->b_lock);
	list_for_each_entry(att, &cbuf->attached, list) {
		dma_sync_sg_for_device(idev->dev, att->table->sgl,
				       att->table->nents, direction);
	}
	mutex_unlock(&cbuf->b_lock);

	return ret;
}

static int _op_dma_buf_get_flags(struct dma_buf *dmabuf,
				 unsigned long *flags)
{
	struct cmm_buffer *buffer = dmabuf->priv;
	*flags = buffer->flags;

	return 0;
}

static const struct dma_buf_ops cmm_dma_buf_ops = {
	.map_dma_buf	  = _op_dma_buf_map,
	.unmap_dma_buf	  = _op_dma_buf_unmap,
	.mmap		  = _op_dma_buf_mmap,
	.release	  = _op_dma_buf_release,
	.attach		  = _op_dma_buf_attach,
	.detach		  = _op_dma_buf_detatch,
	.begin_cpu_access = _op_dma_buf_beg_cpu_access,
	.end_cpu_access   = _op_dma_buf_end_cpu_access,
	.map		  = _op_dma_buf_kmap,
	.unmap		  = _op_dma_buf_kunmap,
	.vmap		  = _op_dma_buf_vmap,
	.vunmap		  = _op_dma_buf_vunmap,
	.get_flags	  = _op_dma_buf_get_flags,
};

struct dma_buf *cmm_alloc_buffer(size_t len, unsigned int flags)
{
	struct cmm_buf_context *ctx = idev;
	struct cmm_buffer *buffer = NULL;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	struct dma_buf *dmabuf;

	len = PAGE_ALIGN(len);
	if (!len)
		return ERR_PTR(-EINVAL);

	buffer = _cmm_cbuf_create(ctx, len, flags);
	if (IS_ERR_OR_NULL(buffer)) {
		CAM_ERR(CAM_MEM, "Cannot create camera buffer");
		return ERR_CAST(buffer);
	}

	exp_info.ops = &cmm_dma_buf_ops;
	exp_info.size = buffer->size;
	exp_info.flags = O_RDWR;
	exp_info.priv = buffer;
	exp_info.exp_name = kasprintf(GFP_KERNEL, "%s%p", KBUILD_MODNAME, ctx);

	dmabuf = dma_buf_export(&exp_info);
	if (IS_ERR(dmabuf)) {
		CAM_ERR(CAM_MEM, "Cannot export camera buffer");
		_cmm_cbuf_destroy(buffer);
		kfree(exp_info.exp_name);
		return ERR_CAST(dmabuf);
	}

	return dmabuf;
}

void cmm_free_buffer(struct dma_buf *dmabuf)
{
	if (!dmabuf) {
		CAM_ERR(CAM_MEM, "Invalid argument(s)");
		return;
	}

	dma_buf_put(dmabuf);
}

int cam_buf_mgr_init(struct platform_device *pdev)
{
	idev = kzalloc(sizeof(*idev), GFP_KERNEL);
	if (IS_ERR_OR_NULL(idev)) {
		CAM_ERR(CAM_MEM, "Cannot allocate memory");
		return PTR_ERR(idev);
	}

	idev->dev = &pdev->dev;
	mutex_init(&idev->dev_lock);

	return 0;
}

void cam_buf_mgr_exit(struct platform_device *pdev)
{
	if (IS_ERR_OR_NULL(idev)) {
		CAM_ERR(CAM_MEM, "Invalid CBM context");
		return;
	}

	mutex_destroy(&idev->dev_lock);
	kfree(idev);
}
