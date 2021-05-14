// SPDX-License-Identifier: GPL-2.0-only
// Copyright(c) 2017-2021 Intel Corporation

#include <linux/atomic.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/module.h>

#include "device.h"
#include "hw.h"

static int recovery_timeout = 60;

#ifdef CONFIG_DEBUG_INTEL_GNA
module_param(recovery_timeout, int, 0644);
MODULE_PARM_DESC(recovery_timeout, "Recovery timeout in seconds");
#endif

static void gna_devm_idr_destroy(void *data)
{
	struct idr *idr = data;

	idr_destroy(idr);
}

int gna_probe(struct device *parent, struct gna_dev_info *dev_info, void __iomem *iobase)
{
	static atomic_t dev_last_idx = ATOMIC_INIT(-1);
	struct gna_private *gna_priv;
	const char *dev_misc_name;
	u32 bld_reg;
	int ret;

	gna_priv = devm_kzalloc(parent, sizeof(*gna_priv), GFP_KERNEL);
	if (!gna_priv)
		return -ENOMEM;

	gna_priv->index = atomic_inc_return(&dev_last_idx);
	gna_priv->recovery_timeout_jiffies = msecs_to_jiffies(recovery_timeout * 1000);
	gna_priv->iobase = iobase;
	gna_priv->info = *dev_info;
	gna_priv->parent = parent;

	dev_misc_name = devm_kasprintf(parent, GFP_KERNEL, "%s%d", GNA_DV_NAME, gna_priv->index);
	if (!dev_misc_name)
		return -ENOMEM;

	gna_priv->name = dev_misc_name;

	if (!(sizeof(dma_addr_t) > 4) ||
		dma_set_mask(parent, DMA_BIT_MASK(64))) {
		ret = dma_set_mask(parent, DMA_BIT_MASK(32));
		if (ret) {
			dev_err(parent, "dma_set_mask error: %d\n", ret);
			return ret;
		}
	}

	bld_reg = gna_reg_read(gna_priv, GNA_MMIO_IBUFFS);
	gna_priv->hw_info.in_buf_s = bld_reg & GENMASK(7, 0);

	ret = gna_mmu_alloc(gna_priv);
	if (ret) {
		dev_err(parent, "mmu allocation failed\n");
		return ret;

	}
	dev_dbg(parent, "maximum memory size %llu num pd %d\n",
		gna_priv->info.max_hw_mem, gna_priv->info.num_pagetables);
	dev_dbg(parent, "desc rsvd size %d mmu vamax size %d\n",
		gna_priv->info.desc_info.rsvd_size,
		gna_priv->info.desc_info.mmu_info.vamax_size);

	mutex_init(&gna_priv->mmu_lock);

	idr_init(&gna_priv->memory_idr);
	ret = devm_add_action(parent, gna_devm_idr_destroy, &gna_priv->memory_idr);
	if (ret) {
		dev_err(parent, "could not add devm action for idr\n");
		return ret;
	}

	mutex_init(&gna_priv->memidr_lock);

	return 0;
}

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("Intel(R) Gaussian & Neural Accelerator (Intel(R) GNA) Driver");
MODULE_LICENSE("GPL");
