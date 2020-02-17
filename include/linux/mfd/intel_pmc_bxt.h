/* SPDX-License-Identifier: GPL-2.0 */
#ifndef MFD_INTEL_PMC_BXT_H
#define MFD_INTEL_PMC_BXT_H

#include <linux/types.h>

/* GCR reg offsets from GCR base */
#define PMC_GCR_PMC_CFG_REG		0x08
#define PMC_GCR_TELEM_DEEP_S0IX_REG	0x78
#define PMC_GCR_TELEM_SHLW_S0IX_REG	0x80

/*
 * Pointer to the PMC device can be obtained by calling
 * dev_get_drvdata() to the parent MFD device.
 */
struct intel_pmc_dev;

int intel_pmc_s0ix_counter_read(struct intel_pmc_dev *pmc, u64 *data);
int intel_pmc_gcr_read64(struct intel_pmc_dev *pmc, u32 offset, u64 *data);

#endif /* MFD_INTEL_PMC_BXT_H */
