// SPDX-License-Identifier: GPL-2.0
/*
 * Driver for the Intel Broxton PMC
 *
 * (C) Copyright 2014 - 2020 Intel Corporation
 *
 * This driver is based on Intel SCU IPC driver (intel_scu_ipc.c) by
 * Sreedhara DS <sreedhara.ds@intel.com>
 *
 * The PMC running on the ARC processor communicates with another entity
 * running in the IA core through an IPC mechanism which in turn sends
 * messages between the IA and the PMC.
 */

#include <linux/acpi.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/io-64-nonatomic-lo-hi.h>
#include <linux/mfd/core.h>
#include <linux/mfd/intel_pmc_bxt.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/platform_data/itco_wdt.h>

#include <asm/intel_scu_ipc.h>

/* Residency with clock rate at 19.2MHz to usecs */
#define S0IX_RESIDENCY_IN_USECS(d, s)		\
({						\
	u64 result = 10ull * ((d) + (s));	\
	do_div(result, 192);			\
	result;					\
})

/* Resources exported from IFWI */
#define PLAT_RESOURCE_IPC_INDEX		0
#define PLAT_RESOURCE_IPC_SIZE		0x1000
#define PLAT_RESOURCE_GCR_OFFSET	0x1000
#define PLAT_RESOURCE_GCR_SIZE		0x1000
#define PLAT_RESOURCE_BIOS_DATA_INDEX	1
#define PLAT_RESOURCE_BIOS_IFACE_INDEX	2
#define PLAT_RESOURCE_TELEM_SSRAM_INDEX	3
#define PLAT_RESOURCE_ISP_DATA_INDEX	4
#define PLAT_RESOURCE_ISP_IFACE_INDEX	5
#define PLAT_RESOURCE_GTD_DATA_INDEX	6
#define PLAT_RESOURCE_GTD_IFACE_INDEX	7
#define PLAT_RESOURCE_ACPI_IO_INDEX	0

/*
 * BIOS does not create an ACPI device for each PMC function, but
 * exports multiple resources from one ACPI device (IPC) for multiple
 * functions. This driver is responsible for creating a child device and
 * to export resources for those functions.
 */
#define TCO_DEVICE_NAME			"iTCO_wdt"
#define SMI_EN_OFFSET			0x40
#define SMI_EN_SIZE			4
#define TCO_BASE_OFFSET			0x60
#define TCO_REGS_SIZE			16
#define PUNIT_DEVICE_NAME		"intel_punit_ipc"
#define TELEMETRY_DEVICE_NAME		"intel_telemetry"
#define TELEM_SSRAM_SIZE		240
#define TELEM_PMC_SSRAM_OFFSET		0x1B00
#define TELEM_PUNIT_SSRAM_OFFSET	0x1A00

/* Commands */
#define PMC_NORTHPEAK_CTRL		0xED

/* PMC_CFG_REG bit masks */
#define PMC_CFG_NO_REBOOT_EN		BIT(4)

/* Index to cells array in below struct */
enum {
	PMC_TCO,
	PMC_PUNIT,
	PMC_TELEM,
};

struct intel_pmc_dev {
	struct device *dev;
	struct intel_scu_ipc_dev *scu;

	struct mfd_cell cells[PMC_TELEM + 1];

	void __iomem *gcr_mem_base;
	spinlock_t gcr_lock;

	struct resource *telem_base;
};

static inline bool is_gcr_valid(u32 offset)
{
	return offset < PLAT_RESOURCE_GCR_SIZE - 8;
}

/**
 * intel_pmc_gcr_read64() - Read a 64-bit PMC GCR register
 * @pmc: PMC device pointer
 * @offset: offset of GCR register from GCR address base
 * @data: data pointer for storing the register output
 *
 * Reads the 64-bit PMC GCR register at given offset.
 *
 * Return: Negative value on error or 0 on success.
 */
int intel_pmc_gcr_read64(struct intel_pmc_dev *pmc, u32 offset, u64 *data)
{
	if (!is_gcr_valid(offset))
		return -EINVAL;

	spin_lock(&pmc->gcr_lock);
	*data = readq(pmc->gcr_mem_base + offset);
	spin_unlock(&pmc->gcr_lock);

	return 0;
}
EXPORT_SYMBOL_GPL(intel_pmc_gcr_read64);

/**
 * intel_pmc_gcr_update() - Update PMC GCR register bits
 * @pmc: PMC device pointer
 * @offset: offset of GCR register from GCR address base
 * @mask: bit mask for update operation
 * @val: update value
 *
 * Updates the bits of given GCR register as specified by
 * @mask and @val.
 *
 * Return: Negative value on error or 0 on success.
 */
static int intel_pmc_gcr_update(struct intel_pmc_dev *pmc, u32 offset, u32 mask,
				u32 val)
{
	u32 new_val;

	if (!is_gcr_valid(offset))
		return -EINVAL;

	spin_lock(&pmc->gcr_lock);
	new_val = readl(pmc->gcr_mem_base + offset);

	new_val = (new_val & ~mask) | (val & mask);
	writel(new_val, pmc->gcr_mem_base + offset);

	new_val = readl(pmc->gcr_mem_base + offset);
	spin_unlock(&pmc->gcr_lock);

	/* Check whether the bit update is successful */
	return (new_val & mask) != (val & mask) ? -EIO : 0;
}

/**
 * intel_pmc_s0ix_counter_read() - Read S0ix residency.
 * @pmc: PMC device pointer
 * @data: Out param that contains current S0ix residency count.
 *
 * Writes to @data how many usecs the system has been in low-power S0ix
 * state.
 *
 * Return: An error code or 0 on success.
 */
int intel_pmc_s0ix_counter_read(struct intel_pmc_dev *pmc, u64 *data)
{
	u64 deep, shlw;

	spin_lock(&pmc->gcr_lock);
	deep = readq(pmc->gcr_mem_base + PMC_GCR_TELEM_DEEP_S0IX_REG);
	shlw = readq(pmc->gcr_mem_base + PMC_GCR_TELEM_SHLW_S0IX_REG);
	spin_unlock(&pmc->gcr_lock);

	*data = S0IX_RESIDENCY_IN_USECS(deep, shlw);
	return 0;
}
EXPORT_SYMBOL_GPL(intel_pmc_s0ix_counter_read);

static ssize_t simplecmd_store(struct device *dev, struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct intel_pmc_dev *pmc = dev_get_drvdata(dev);
	struct intel_scu_ipc_dev *scu = pmc->scu;
	int subcmd;
	int cmd;
	int ret;

	ret = sscanf(buf, "%d %d", &cmd, &subcmd);
	if (ret != 2) {
		dev_err(dev, "Invalid values, expected: cmd subcmd\n");
		return -EINVAL;
	}

	ret = intel_scu_ipc_dev_simple_command(scu, cmd, subcmd);
	return ret ?: count;
}
static DEVICE_ATTR_WO(simplecmd);

static ssize_t northpeak_store(struct device *dev, struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct intel_pmc_dev *pmc = dev_get_drvdata(dev);
	struct intel_scu_ipc_dev *scu = pmc->scu;
	unsigned long val;
	int subcmd;
	int ret;

	ret = kstrtoul(buf, 0, &val);
	if (ret)
		return ret;

	if (val)
		subcmd = 1;
	else
		subcmd = 0;

	ret = intel_scu_ipc_dev_simple_command(scu, PMC_NORTHPEAK_CTRL, subcmd);
	return ret ?: count;
}
static DEVICE_ATTR_WO(northpeak);

static struct attribute *intel_pmc_attrs[] = {
	&dev_attr_northpeak.attr,
	&dev_attr_simplecmd.attr,
	NULL
};

static const struct attribute_group intel_pmc_group = {
	.attrs = intel_pmc_attrs,
};

static const struct attribute_group *intel_pmc_groups[] = {
	&intel_pmc_group,
	NULL
};

/* Templates used to construct MFD cells */

static const struct mfd_cell punit = {
	.name = PUNIT_DEVICE_NAME,
};

static int update_no_reboot_bit(void *priv, bool set)
{
	struct intel_pmc_dev *pmc = priv;
	u32 bits = PMC_CFG_NO_REBOOT_EN;
	u32 value = set ? bits : 0;

	return intel_pmc_gcr_update(pmc, PMC_GCR_PMC_CFG_REG, bits, value);
}

static const struct itco_wdt_platform_data tco_pdata = {
	.name = "Apollo Lake SoC",
	.version = 5,
	.update_no_reboot_bit = update_no_reboot_bit,
};

static const struct mfd_cell tco = {
	.name = TCO_DEVICE_NAME,
	.ignore_resource_conflicts = true,
};

static const struct resource telem_res[] = {
	DEFINE_RES_MEM(TELEM_PUNIT_SSRAM_OFFSET, TELEM_SSRAM_SIZE),
	DEFINE_RES_MEM(TELEM_PMC_SSRAM_OFFSET, TELEM_SSRAM_SIZE),
};

static const struct mfd_cell telem = {
	.name = TELEMETRY_DEVICE_NAME,
	.resources = telem_res,
	.num_resources = ARRAY_SIZE(telem_res),
};

static int intel_pmc_get_tco_resources(struct platform_device *pdev,
				       struct intel_pmc_dev *pmc)
{
	struct itco_wdt_platform_data *pdata;
	struct resource *res, *tco_res;

	if (acpi_has_watchdog())
		return 0;

	res = platform_get_resource(pdev, IORESOURCE_IO,
				    PLAT_RESOURCE_ACPI_IO_INDEX);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get IO resource\n");
		return -EINVAL;
	}

	tco_res = devm_kcalloc(&pdev->dev, 2, sizeof(*tco_res), GFP_KERNEL);
	if (!tco_res)
		return -ENOMEM;

	tco_res[0].flags = IORESOURCE_IO;
	tco_res[0].start = res->start + TCO_BASE_OFFSET;
	tco_res[0].end = tco_res[0].start + TCO_REGS_SIZE - 1;
	tco_res[1].flags = IORESOURCE_IO;
	tco_res[1].start = res->start + SMI_EN_OFFSET;
	tco_res[1].end = tco_res[1].start + SMI_EN_SIZE - 1;

	pmc->cells[PMC_TCO].resources = tco_res;
	pmc->cells[PMC_TCO].num_resources = 2;

	pdata = devm_kmemdup(&pdev->dev, &tco_pdata, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	pdata->no_reboot_priv = pmc;
	pmc->cells[PMC_TCO].platform_data = pdata;
	pmc->cells[PMC_TCO].pdata_size = sizeof(*pdata);

	return 0;
}

static int intel_pmc_get_resources(struct platform_device *pdev,
				   struct intel_pmc_dev *pmc,
				   struct intel_scu_ipc_pdata *pdata)
{
	struct resource *res, *punit_res;
	struct resource gcr_res;
	size_t npunit_res = 0;
	int ret;

	pdata->irq = platform_get_irq_optional(pdev, 0);

	res = platform_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_IPC_INDEX);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get IPC resource\n");
		return -EINVAL;
	}

	/* IPC registers */
	pdata->mem.flags = res->flags;
	pdata->mem.start = res->start;
	pdata->mem.end = res->start + PLAT_RESOURCE_IPC_SIZE - 1;

	/* GCR registers */
	gcr_res.flags = res->flags;
	gcr_res.start = res->start + PLAT_RESOURCE_GCR_OFFSET;
	gcr_res.end = gcr_res.start + PLAT_RESOURCE_GCR_SIZE - 1;

	pmc->gcr_mem_base = devm_ioremap_resource(&pdev->dev, &gcr_res);
	if (IS_ERR(pmc->gcr_mem_base))
		return PTR_ERR(pmc->gcr_mem_base);

	pmc->cells[PMC_TCO] = tco;
	pmc->cells[PMC_PUNIT] = punit;
	pmc->cells[PMC_TELEM] = telem;

	/* iTCO watchdog only if there is no WDAT ACPI table */
	ret = intel_pmc_get_tco_resources(pdev, pmc);
	if (ret)
		return ret;

	punit_res = devm_kcalloc(&pdev->dev, 6, sizeof(*punit_res), GFP_KERNEL);
	if (!punit_res)
		return -ENOMEM;

	/* This is index 0 to cover BIOS data register */
	res = platform_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_BIOS_DATA_INDEX);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get resource of P-unit BIOS data\n");
		return -EINVAL;
	}
	punit_res[npunit_res++] = *res;

	/* This is index 1 to cover BIOS interface register */
	res = platform_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_BIOS_IFACE_INDEX);
	if (!res) {
		dev_err(&pdev->dev, "Failed to get resource of P-unit BIOS interface\n");
		return -EINVAL;
	}
	punit_res[npunit_res++] = *res;

	/* This is index 2 to cover ISP data register, optional */
	res = platform_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_ISP_DATA_INDEX);
	if (res)
		punit_res[npunit_res++] = *res;

	/* This is index 3 to cover ISP interface register, optional */
	res = platform_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_ISP_IFACE_INDEX);
	if (res)
		punit_res[npunit_res++] = *res;

	/* This is index 4 to cover GTD data register, optional */
	res = platform_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_GTD_DATA_INDEX);
	if (res)
		punit_res[npunit_res++] = *res;

	/* This is index 5 to cover GTD interface register, optional */
	res = platform_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_GTD_IFACE_INDEX);
	if (res)
		punit_res[npunit_res++] = *res;

	pmc->cells[PMC_PUNIT].resources = punit_res;
	pmc->cells[PMC_PUNIT].num_resources = npunit_res;

	/* Telemetry SSRAM is optional */
	res = platform_get_resource(pdev, IORESOURCE_MEM,
				    PLAT_RESOURCE_TELEM_SSRAM_INDEX);
	if (res)
		pmc->telem_base = res;

	return 0;
}

static int intel_pmc_create_devices(struct intel_pmc_dev *pmc)
{
	int ret;

	if (pmc->cells[PMC_TCO].num_resources) {
		ret = devm_mfd_add_devices(pmc->dev, PLATFORM_DEVID_AUTO,
					   &pmc->cells[PMC_TCO], 1, NULL, 0, NULL);
		if (ret)
			return ret;
	}

	ret = devm_mfd_add_devices(pmc->dev, PLATFORM_DEVID_AUTO,
				   &pmc->cells[PMC_PUNIT], 1, NULL, 0, NULL);
	if (ret)
		return ret;

	if (pmc->telem_base) {
		ret = devm_mfd_add_devices(pmc->dev, PLATFORM_DEVID_AUTO,
					   &pmc->cells[PMC_TELEM], 1,
					   pmc->telem_base, 0, NULL);
	}

	return ret;
}

static const struct acpi_device_id intel_pmc_acpi_ids[] = {
	{ "INT34D2" },
	{ }
};
MODULE_DEVICE_TABLE(acpi, intel_pmc_acpi_ids);

static int intel_pmc_probe(struct platform_device *pdev)
{
	struct intel_scu_ipc_pdata pdata = {};
	struct intel_pmc_dev *pmc;
	int ret;

	pmc = devm_kzalloc(&pdev->dev, sizeof(*pmc), GFP_KERNEL);
	if (!pmc)
		return -ENOMEM;

	pmc->dev = &pdev->dev;
	spin_lock_init(&pmc->gcr_lock);

	ret = intel_pmc_get_resources(pdev, pmc, &pdata);
	if (ret) {
		dev_err(&pdev->dev, "Failed to request resources\n");
		return ret;
	}

	pmc->scu = devm_intel_scu_ipc_register(&pdev->dev, &pdata);
	if (IS_ERR(pmc->scu))
		return PTR_ERR(pmc->scu);

	platform_set_drvdata(pdev, pmc);

	ret = intel_pmc_create_devices(pmc);
	if (ret)
		dev_err(&pdev->dev, "Failed to create PMC devices\n");

	return ret;
}

static struct platform_driver intel_pmc_driver = {
	.probe = intel_pmc_probe,
	.driver = {
		.name = "intel_pmc_bxt",
		.acpi_match_table = intel_pmc_acpi_ids,
		.dev_groups = intel_pmc_groups,
	},
};

module_platform_driver(intel_pmc_driver);

MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_AUTHOR("Zha Qipeng <qipeng.zha@intel.com>");
MODULE_DESCRIPTION("Intel Broxton PMC driver");
MODULE_LICENSE("GPL v2");
