// SPDX-License-Identifier: GPL-2.0
/*
 * Driver for the Intel Integrated Type-C Sub System Mux
 *
 * Copyright (C) 2018-2020 Intel Corporation
 *
 * Based on drivers/extcon/extcon-usbc-cros-ec.c
 *
 * This driver uses Intel PMC (Power Management Controller) IPC (Inter
 * Processor Communication) to configure the required muxing for the
 * Intel TCSS (Type-C Sub System)
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>

static int cros_ec_tcss_probe(struct platform_device *pdev)
{
	return 0;
}

static const struct of_device_id cros_ec_tcss_of_match[] = {
	{.compatible = "google,extcon-tcss-cros-ec"},
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, cros_ec_tcss_of_match);

static struct platform_driver tcss_cros_ec_driver = {
	.driver = {
		   .name = "extcon-tcss-cros-ec",
		   .of_match_table = cros_ec_tcss_of_match,
	},
	.probe = cros_ec_tcss_probe,
};

module_platform_driver(tcss_cros_ec_driver);

MODULE_DESCRIPTION("ChromeOS Embedded Controller Intel TCSS driver");
MODULE_AUTHOR("Vijay P Hiremath <vijay.p.hiremath@intel.com>");
MODULE_AUTHOR("Divya Sasidharan <divya.s.sasidharan@intel.com>");
MODULE_AUTHOR("Utkarsh Patel <utkarsh.h.patel@intel.com>");
MODULE_LICENSE("GPL v2");
