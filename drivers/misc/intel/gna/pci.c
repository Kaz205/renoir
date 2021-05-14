// SPDX-License-Identifier: GPL-2.0-only
// Copyright(c) 2017-2021 Intel Corporation

#include <linux/module.h>
#include <linux/pci.h>

#include "device.h"
#include "pci.h"

int gna_pci_probe(struct pci_dev *pcidev, const struct pci_device_id *pci_id)
{
	struct gna_dev_info *dev_info;
	void __iomem *iobase;
	int ret;

	ret = pcim_enable_device(pcidev);
	if (ret) {
		dev_err(&pcidev->dev, "pci device can't be enabled\n");
		return ret;
	}

	ret = pcim_iomap_regions(pcidev, BIT(0), pci_name(pcidev));
	if (ret) {
		dev_err(&pcidev->dev, "cannot iomap regions\n");
		return ret;
	}

	iobase = pcim_iomap_table(pcidev)[0];

	pci_set_master(pcidev);

	dev_info = (struct gna_dev_info *)pci_id->driver_data;

	ret = gna_probe(&pcidev->dev, dev_info, iobase);
	if (ret) {
		dev_err(&pcidev->dev, "could not initialize device\n");
		return ret;
	}

	return 0;
}

static struct pci_driver gna_pci_driver = {
	.name = GNA_DV_NAME,
	.probe = gna_pci_probe,
};

module_pci_driver(gna_pci_driver);
