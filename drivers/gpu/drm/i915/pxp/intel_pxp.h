/* SPDX-License-Identifier: MIT */
/*
 * Copyright(c) 2020, Intel Corporation. All rights reserved.
 */

#ifndef __INTEL_PXP_H__
#define __INTEL_PXP_H__

#include <linux/workqueue.h>
#include "intel_pxp_context.h"

#define PXP_IRQ_VECTOR_DISPLAY_PXP_STATE_TERMINATED BIT(1)
#define PXP_IRQ_VECTOR_DISPLAY_APP_TERM_PER_FW_REQ BIT(2)
#define PXP_IRQ_VECTOR_PXP_DISP_STATE_RESET_COMPLETE BIT(3)

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
	struct work_struct irq_work;
	u32 handled_irr;
	u32 current_events;

	struct pxp_context ctx;
};

#ifdef CONFIG_DRM_I915_PXP
void intel_pxp_irq_handler(struct intel_pxp *pxp, u16 iir);
int i915_pxp_teardown_required_callback(struct intel_pxp *pxp);
int i915_pxp_global_terminate_complete_callback(struct intel_pxp *pxp);

int intel_pxp_init(struct intel_pxp *pxp);
void intel_pxp_uninit(struct intel_pxp *pxp);
#else
static inline void intel_pxp_irq_handler(struct intel_pxp *pxp, u16 iir)
{
}

static inline int i915_pxp_teardown_required_callback(struct intel_pxp *pxp)
{
	return 0;
}

static inline int i915_pxp_global_terminate_complete_callback(struct intel_pxp *pxp)
{
	return 0;
}

static inline int intel_pxp_init(struct intel_pxp *pxp)
{
	return 0;
}

static inline void intel_pxp_uninit(struct intel_pxp *pxp)
{
}
#endif

#endif /* __INTEL_PXP_PM_H__ */
