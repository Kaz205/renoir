// SPDX-License-Identifier: MIT
/*
 * Copyright(c) 2020 Intel Corporation.
 */
#include "i915_drv.h"
#include "intel_pxp.h"
#include "intel_pxp_context.h"
#include "intel_pxp_tee.h"
#include "intel_pxp_arb.h"

/* KCR register definitions */
#define KCR_INIT            _MMIO(0x320f0)
#define KCR_INIT_MASK_SHIFT (16)
/* Setting KCR Init bit is required after system boot */
#define KCR_INIT_ALLOW_DISPLAY_ME_WRITES (BIT(14) | (BIT(14) << KCR_INIT_MASK_SHIFT))

static void intel_pxp_write_irq_mask_reg(struct intel_gt *gt, u32 mask)
{
	lockdep_assert_held(&gt->irq_lock);

	intel_uncore_write(gt->uncore, GEN11_CRYPTO_INTR_MASK, mask << 16);
}

static int intel_pxp_teardown_required_callback(struct intel_pxp *pxp)
{
	int ret;

	mutex_lock(&pxp->ctx.mutex);

	pxp->ctx.global_state_attacked = true;
	pxp->ctx.flag_display_hm_surface_keys = false;

	ret = intel_pxp_arb_terminate_session(pxp);

	mutex_unlock(&pxp->ctx.mutex);

	return ret;
}

static int intel_pxp_global_terminate_complete_callback(struct intel_pxp *pxp)
{
	int ret = 0;
	struct intel_gt *gt = container_of(pxp, typeof(*gt), pxp);

	mutex_lock(&pxp->ctx.mutex);

	if (pxp->ctx.global_state_attacked) {
		pxp->ctx.global_state_attacked = false;

		/* Re-create the arb session after teardown handle complete */
		ret = intel_pxp_arb_create_session(pxp);
		if (ret) {
			drm_err(&gt->i915->drm, "Failed to create arb session\n");
			goto end;
		}
	}
end:
	mutex_unlock(&pxp->ctx.mutex);
	return ret;
}

static void intel_pxp_irq_work(struct work_struct *work)
{
	struct intel_pxp *pxp = container_of(work, typeof(*pxp), irq_work);
	struct intel_gt *gt = container_of(pxp, typeof(*gt), pxp);
	u32 events = 0;

	spin_lock_irq(&gt->irq_lock);
	events = fetch_and_zero(&pxp->current_events);
	spin_unlock_irq(&gt->irq_lock);

	if (events & PXP_IRQ_VECTOR_DISPLAY_PXP_STATE_TERMINATED ||
	    events & PXP_IRQ_VECTOR_DISPLAY_APP_TERM_PER_FW_REQ)
		intel_pxp_teardown_required_callback(pxp);

	if (events & PXP_IRQ_VECTOR_PXP_DISP_STATE_RESET_COMPLETE)
		intel_pxp_global_terminate_complete_callback(pxp);

	spin_lock_irq(&gt->irq_lock);
	intel_pxp_write_irq_mask_reg(gt, 0);
	spin_unlock_irq(&gt->irq_lock);
}

int intel_pxp_init(struct intel_pxp *pxp)
{
	struct intel_gt *gt = container_of(pxp, struct intel_gt, pxp);

	/* PXP only available for GEN12+ */
	if (INTEL_GEN(gt->i915) < 12)
		return -ENODEV;

	intel_pxp_ctx_init(&pxp->ctx);

	intel_uncore_write(gt->uncore, KCR_INIT, KCR_INIT_ALLOW_DISPLAY_ME_WRITES);

	intel_pxp_tee_component_init(pxp);

	INIT_WORK(&pxp->irq_work, intel_pxp_irq_work);

	pxp->handled_irr = (PXP_IRQ_VECTOR_DISPLAY_PXP_STATE_TERMINATED |
			    PXP_IRQ_VECTOR_DISPLAY_APP_TERM_PER_FW_REQ |
			    PXP_IRQ_VECTOR_PXP_DISP_STATE_RESET_COMPLETE);

	drm_info(&gt->i915->drm, "Protected Xe Path (PXP) protected content support initialized\n");

	return 0;
}

void intel_pxp_uninit(struct intel_pxp *pxp)
{
	intel_pxp_tee_component_fini(pxp);

	intel_pxp_ctx_fini(&pxp->ctx);
}

/**
 * intel_pxp_irq_handler - Proxies KCR interrupts to PXP.
 * @pxp: pointer to pxp struct
 * @iir: GT interrupt vector associated with the interrupt
 *
 * Dispatches each vector element into an IRQ to PXP.
 */
void intel_pxp_irq_handler(struct intel_pxp *pxp, u16 iir)
{
	struct drm_i915_private *i915;
	const u32 events = iir & pxp->handled_irr;
	struct intel_gt *gt = container_of(pxp, typeof(*gt), pxp);

	if (!gt || !gt->i915 || INTEL_GEN(i915) < 12)
		return;

	i915 = gt->i915;

	lockdep_assert_held(&gt->irq_lock);

	if (unlikely(!events)) {
		drm_err(&i915->drm, "%s returned due to iir=[0x%04x]\n", __func__, iir);
		return;
	}

	intel_pxp_write_irq_mask_reg(gt, pxp->handled_irr);

	pxp->current_events |= events;
	schedule_work(&pxp->irq_work);
}
