/* SPDX-License-Identifier: GPL-2.0 */

#ifndef _PLATFORM_DATA_X86_INTEL_IOM_H_
#define _PLATFORM_DATA_X86_INTEL_IOM_H_

#include <linux/bits.h>
#include <linux/types.h>

/* Input Output Manager (IOM) PORT STATUS */
#define IOM_PORT_STATUS_ACTIVITY_TYPE_MASK		GENMASK(9, 6)
#define IOM_PORT_STATUS_ACTIVITY_TYPE_SHIFT		0x06
#define IOM_PORT_STATUS_ACTIVITY_TYPE_USB		0x03
/* activity type: Safe Mode */
#define IOM_PORT_STATUS_ACTIVITY_TYPE_SAFE_MODE		0x04
/* activity type: Display Port */
#define IOM_PORT_STATUS_ACTIVITY_TYPE_DP		0x05
/* activity type: Display Port Multi Function Device */
#define IOM_PORT_STATUS_ACTIVITY_TYPE_DP_MFD		0x06
/* activity type: Thunderbolt */
#define IOM_PORT_STATUS_ACTIVITY_TYPE_TBT		0x07
#define IOM_PORT_STATUS_ACTIVITY_TYPE_ALT_MODE_USB	0x0c
#define IOM_PORT_STATUS_ACTIVITY_TYPE_ALT_MODE_TBT_USB	0x0d
/* Upstream Facing Port Information */
#define IOM_PORT_STATUS_UFP				BIT(10)
/* Display Port Hot Plug Detect status */
#define IOM_PORT_STATUS_DHPD_HPD_STATUS_MASK		GENMASK(13, 12)
#define IOM_PORT_STATUS_DHPD_HPD_STATUS_SHIFT		0x0c
#define IOM_PORT_STATUS_DHPD_HPD_STATUS_ASSERT		0x01
#define IOM_PORT_STATUS_DHPD_HPD_SOURCE_TBT		BIT(14)
#define IOM_PORT_STATUS_CONNECTED			BIT(31)

#define IOM_MAX_PORTS					4
/* Register length in bytes */
#define IOM_REG_LEN					4

struct intel_iom;

#ifdef CONFIG_ACPI

int intel_iom_port_status(u8 port, u32 *status);

#else

int intel_iom_port_status(u8 port, u32 *status)
{
	return 0;
}

#endif

#endif /* _PLATFORM_DATA_X86_INTEL_IOM_H_ */
