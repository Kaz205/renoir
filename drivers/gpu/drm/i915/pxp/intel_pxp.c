// SPDX-License-Identifier: MIT
/*
 * Copyright(c) 2020 Intel Corporation.
 */
#include "i915_drv.h"
#include "intel_pxp.h"
#include "intel_pxp_context.h"

int intel_pxp_init(struct intel_pxp *pxp)
{
	struct intel_gt *gt = container_of(pxp, struct intel_gt, pxp);

	/* PXP only available for GEN12+ */
	if (INTEL_GEN(gt->i915) < 12)
		return -ENODEV;

	intel_pxp_ctx_init(&pxp->ctx);

	drm_info(&gt->i915->drm, "Protected Xe Path (PXP) protected content support initialized\n");

	return 0;
}

void intel_pxp_uninit(struct intel_pxp *pxp)
{
	intel_pxp_ctx_fini(&pxp->ctx);
}
