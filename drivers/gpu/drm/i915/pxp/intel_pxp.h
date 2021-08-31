/* SPDX-License-Identifier: MIT */
/*
 * Copyright(c) 2020, Intel Corporation. All rights reserved.
 */

#ifndef __INTEL_PXP_H__
#define __INTEL_PXP_H__

#include "intel_pxp_context.h"

enum pxp_session_types {
	SESSION_TYPE_TYPE0 = 0,
	SESSION_TYPE_TYPE1 = 1,

	SESSION_TYPE_MAX
};

enum pxp_protection_modes {
	PROTECTION_MODE_NONE = 0,
	PROTECTION_MODE_LM   = 2,
	PROTECTION_MODE_HM   = 3,
	PROTECTION_MODE_SM   = 6,

	PROTECTION_MODE_ALL
};

struct intel_pxp {
	struct pxp_context ctx;
};

#ifdef CONFIG_DRM_I915_PXP
int intel_pxp_init(struct intel_pxp *pxp);
void intel_pxp_uninit(struct intel_pxp *pxp);
#else
static inline int intel_pxp_init(struct intel_pxp *pxp)
{
	return 0;
}

static inline void intel_pxp_uninit(struct intel_pxp *pxp)
{
}
#endif

#endif /* __INTEL_PXP_PM_H__ */
