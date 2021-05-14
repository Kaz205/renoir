/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright(c) 2017-2021 Intel Corporation */

#ifndef __GNA_DEVICE_H__
#define __GNA_DEVICE_H__

#include <linux/types.h>

#include "hw.h"

#define GNA_DV_NAME	"intel_gna"

struct device;

struct gna_private {
	int index;

	int recovery_timeout_jiffies;

	const char *name;
	struct device *parent;

	/* device related resources */
	void __iomem *iobase;
	struct gna_dev_info info;
};

int gna_probe(struct device *parent, struct gna_dev_info *dev_info, void __iomem *iobase);

#endif /* __GNA_DEVICE_H__ */
