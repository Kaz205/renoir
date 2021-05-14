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

int gna_probe(struct device *parent, struct gna_dev_info *dev_info, void __iomem *iobase)
{
	static atomic_t dev_last_idx = ATOMIC_INIT(-1);
	struct gna_private *gna_priv;
	const char *dev_misc_name;
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

	return 0;
}

MODULE_AUTHOR("Intel Corporation");
MODULE_DESCRIPTION("Intel(R) Gaussian & Neural Accelerator (Intel(R) GNA) Driver");
MODULE_LICENSE("GPL");
