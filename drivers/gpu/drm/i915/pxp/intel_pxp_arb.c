// SPDX-License-Identifier: MIT
/*
 * Copyright(c) 2020, Intel Corporation. All rights reserved.
 */

#include "gt/intel_context.h"
#include "gt/intel_engine_pm.h"

#include "intel_pxp_arb.h"
#include "intel_pxp.h"
#include "intel_pxp_context.h"
#include "intel_pxp_tee.h"

#define GEN12_KCR_SIP _MMIO(0x32260) /* KCR type0 session in play 0-31 */

/* Arbitrary session */
#define ARB_SESSION_INDEX 0xf
#define ARB_SESSION_TYPE SESSION_TYPE_TYPE0
#define ARB_PROTECTION_MODE PROTECTION_MODE_HM

static bool is_hw_arb_session_in_play(struct intel_pxp *pxp)
{
	u32 regval_sip = 0;
	intel_wakeref_t wakeref;
	struct intel_gt *gt = container_of(pxp, struct intel_gt, pxp);

	with_intel_runtime_pm(&gt->i915->runtime_pm, wakeref) {
		regval_sip = intel_uncore_read(gt->uncore, GEN12_KCR_SIP);
	}

	return regval_sip & BIT(ARB_SESSION_INDEX);
}

/* wait hw session_in_play reg to match the current sw state */
static int wait_arb_hw_sw_state(struct intel_pxp *pxp)
{
	const int max_retry = 10;
	const int ms_delay = 10;
	int retry = 0;
	int ret;
	struct pxp_protected_session *arb = &pxp->ctx.arb_session;

	ret = -EINVAL;
	for (retry = 0; retry < max_retry; retry++) {
		if (is_hw_arb_session_in_play(pxp) ==
		    arb->is_in_play) {
			ret = 0;
			break;
		}

		msleep(ms_delay);
	}

	return ret;
}

static void arb_session_entry_init(struct intel_pxp *pxp)
{
	struct pxp_protected_session *arb = &pxp->ctx.arb_session;

	arb->context_id = pxp->ctx.id;
	arb->type = ARB_SESSION_TYPE;
	arb->protection_mode = ARB_PROTECTION_MODE;
	arb->index = ARB_SESSION_INDEX;
	arb->is_in_play = false;
}

int intel_pxp_arb_reserve_session(struct intel_pxp *pxp)
{
	int ret;

	lockdep_assert_held(&pxp->ctx.mutex);

	arb_session_entry_init(pxp);
	ret = wait_arb_hw_sw_state(pxp);

	return ret;
}

/**
 * intel_pxp_arb_mark_session_in_play - To put an reserved protected session to "in_play" state
 * @pxp: pointer to pxp struct.
 *
 * Return: status. 0 means update is successful.
 */
static int intel_pxp_arb_mark_session_in_play(struct intel_pxp *pxp)
{
	struct pxp_protected_session *arb = &pxp->ctx.arb_session;

	lockdep_assert_held(&pxp->ctx.mutex);

	if (arb->is_in_play)
		return -EINVAL;

	arb->is_in_play = true;
	return 0;
}

int intel_pxp_arb_create_session(struct intel_pxp *pxp)
{
	int ret;
	struct intel_gt *gt = container_of(pxp, typeof(*gt), pxp);

	lockdep_assert_held(&pxp->ctx.mutex);

	if (pxp->ctx.flag_display_hm_surface_keys) {
		drm_err(&gt->i915->drm, "%s: arb session is alive so skipping the creation\n",
			__func__);
		return 0;
	}

	ret = intel_pxp_arb_reserve_session(pxp);
	if (ret) {
		drm_err(&gt->i915->drm, "Failed to reserve arb session\n");
		goto end;
	}

	ret = intel_pxp_tee_cmd_create_arb_session(pxp);
	if (ret) {
		drm_err(&gt->i915->drm, "Failed to send tee cmd for arb session creation\n");
		goto end;
	}

	ret = intel_pxp_arb_mark_session_in_play(pxp);
	if (ret) {
		drm_err(&gt->i915->drm, "Failed to mark arb session status in play\n");
		goto end;
	}

	pxp->ctx.flag_display_hm_surface_keys = true;

end:
	return ret;
}
