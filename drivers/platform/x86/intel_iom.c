// SPDX-License-Identifier: GPL-2.0
/*
 * Intel Core SoC Input Output Manager (IOM) driver.
 *
 * This driver provides access to the Input Output Manager (IOM) (that
 * is part of Tiger Lake SoC) registers that can be used to know about
 * Type-C Sub System related information (such as Type-C port status,
 * activity type on Type-C ports).
 *
 * Copyright (C) 2020, Intel Corporation
 * Author: Rajmohan Mani <rajmohan.mani@intel.com>
 */

#include <linux/io.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/platform_data/x86/intel_iom.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#define IOM_PORT_STATUS_OFFSET				0x560

struct intel_iom {
	struct device *dev;
	void __iomem *regbar;
};

struct intel_iom iom_dev;

/**
 * intel_iom_port_status() - Get status bits for the Type-C port
 * @port: Type-C port number
 * @status: pointer to receive the status bits
 *
 * Returns 0 on success, error otherwise.
 */
int intel_iom_port_status(u8 port, u32 *status)
{
	struct intel_iom *iom = &iom_dev;
	void __iomem *reg;

	if (!iom->dev || !iom->regbar)
		return -ENODEV;

	if (!status || (port > IOM_MAX_PORTS - 1))
		return -EINVAL;

	reg = iom->regbar + IOM_PORT_STATUS_OFFSET + IOM_REG_LEN * port;

	*status = ioread32(reg);

	return 0;
}
EXPORT_SYMBOL_GPL(intel_iom_port_status);

static int intel_iom_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	void __iomem *addr;

	addr = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(addr))
		return PTR_ERR(addr);

	iom_dev.regbar = addr;

	iom_dev.dev = dev;
	dev_set_drvdata(dev, &iom_dev);
	return 0;
}

static const struct acpi_device_id intel_iom_acpi_ids[] = {
	{ "INTC1072" },
	{}
};
MODULE_DEVICE_TABLE(acpi, intel_iom_acpi_ids);

static struct platform_driver intel_iom_driver = {
	.probe = intel_iom_probe,
	.driver = {
		.name = "intel_iom",
		.acpi_match_table = intel_iom_acpi_ids,
	},
};

module_platform_driver_probe(intel_iom_driver, intel_iom_probe);

MODULE_AUTHOR("Rajmohan Mani <rajmohan.mani@intel.com>");
MODULE_DESCRIPTION("Intel IOM driver");
MODULE_LICENSE("GPL v2");
