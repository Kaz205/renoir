// SPDX-License-Identifier: MIT
/*
 * Copyright(c) 2020, Intel Corporation. All rights reserved.
 */
#include "gt/intel_context.h"
#include "gt/intel_engine_pm.h"
#include "intel_pxp_sm.h"
#include "intel_pxp.h"

#define KCR_STATUS_1   _MMIO(0x320f4)
#define KCR_STATUS_1_ATTACK_MASK 0x80000000

#define GEN12_KCR_TSIP _MMIO(0x32264) /* KCR type1 session in play 0-63 */

#define SESSION_TYPE_MASK BIT(7)
#define SESSION_ID_MASK (BIT(7) - 1)

static inline int session_max(int session_type)
{
	return (session_type == SESSION_TYPE_TYPE0) ?
		PXP_MAX_NORMAL_TYPE0_SESSIONS : PXP_MAX_TYPE1_SESSIONS;
}

static inline struct list_head *session_list(struct intel_pxp *pxp,
					     int session_type)
{
	return (session_type == SESSION_TYPE_TYPE0) ?
		&pxp->ctx.type0_sessions : &pxp->ctx.type1_sessions;
}

/**
 * is_sw_session_active - Check if the given sw session id is active.
 * @pxp: pointer to pxp struct
 * @session_type: Specified session type
 * @session_index: Numeric session identifier.
 * @is_in_play: Set false to return true if the specified session is active.
 *              Set true to also check if the session is active and in_play.
 *
 * The caller needs to use mutex lock to protect the session list
 * inside this function.
 *
 * Return : true if session with the same identifier is active (and in_play).
 */
static bool is_sw_session_active(struct intel_pxp *pxp, int session_type,
				 int session_index, bool is_in_play)
{
	struct intel_pxp_sm_session *curr, *n;

	lockdep_assert_held(&pxp->ctx.mutex);

	list_for_each_entry_safe(curr, n, session_list(pxp, session_type), list) {
		if (curr->index == session_index) {
			if (is_in_play && !curr->is_in_play)
				return false;
			return true;
		}
	}

	return false;
}

static bool is_hw_session_in_play(struct intel_pxp *pxp,
				  int session_type, int session_index)
{
	u64 regval_sip = 0;
	intel_wakeref_t wakeref;
	struct intel_gt *gt = container_of(pxp, struct intel_gt, pxp);

	with_intel_runtime_pm(&gt->i915->runtime_pm, wakeref) {
		if (session_type == SESSION_TYPE_TYPE0)
			regval_sip = intel_uncore_read(gt->uncore, GEN12_KCR_SIP);
		else
			regval_sip = intel_uncore_read64(gt->uncore, GEN12_KCR_TSIP);
	}

	return regval_sip & BIT(session_index);
}

/* wait hw session_in_play reg to match the current sw state */
static int wait_hw_sw_state(struct intel_pxp *pxp, int session_index, int session_type)
{
	const int max_retry = 10;
	int retry = 0;

	for (retry = 0; retry < max_retry; retry++) {
		if (is_hw_session_in_play(pxp, session_type, session_index) ==
		    is_sw_session_active(pxp, session_type, session_index, true))
			return 0;

		msleep(10);
	}
	return -EINVAL;
}

/**
 * is_type0_session_attacked - To check if type0 active sessions are attacked.
 * @pxp: pointer pxp struct
 *
 * Return: true if hardware sessions is attacked, false otherwise.
 */
static bool is_type0_session_attacked(struct intel_pxp *pxp)
{
	u32 regval = 0;
	intel_wakeref_t wakeref;
	struct intel_gt *gt = container_of(pxp, struct intel_gt, pxp);

	if (pxp->ctx.global_state_attacked)
		return true;

	with_intel_runtime_pm(&gt->i915->runtime_pm, wakeref)
		regval = intel_uncore_read(gt->uncore, KCR_STATUS_1);

	return regval & KCR_STATUS_1_ATTACK_MASK;
}

/**
 * create_session_entry - Create a new session entry with provided info.
 * @pxp: pointer to pxp struct
 * @drmfile: pointer to drm_file
 * @context_id: Numeric identifier of the context created by the caller.
 * @session_type: Type of the session requested. One of enum pxp_session_types.
 * @protection_mode: Type of protection requested for the session.
 *                   One of the enum pxp_protection_modes.
 * @session_index: Numeric session identifier.
 *
 * Return: status. 0 means creation is successful.
 */
static int create_session_entry(struct intel_pxp *pxp, struct drm_file *drmfile,
				int context_id, int session_type, int protection_mode,
				int session_index)
{
	struct intel_pxp_sm_session *session = NULL;
	int pid = 0;

	if (drmfile)
		pid = pid_nr(drmfile->pid);

	session = kzalloc(sizeof(*session), GFP_KERNEL);
	if (!session)
		return -ENOMEM;

	session->context_id = context_id;
	session->type = session_type;
	session->protection_mode = protection_mode;
	session->index = session_index;
	session->is_in_play = false;
	session->drmfile = drmfile;
	session->pid = pid;

	list_add(&session->list, session_list(pxp, session_type));
	return 0;
}

static int pxp_get_session_index(u32 session_id, int *index_out, int *type_out)
{
	if (!index_out || !type_out)
		return -EINVAL;

	*type_out = (session_id & SESSION_TYPE_MASK) ? SESSION_TYPE_TYPE1 : SESSION_TYPE_TYPE0;
	*index_out = session_id & SESSION_ID_MASK;

	return 0;
}

/**
 * intel_pxp_sm_ioctl_reserve_session - To reserve an available protected session.
 * @pxp: pointer to pxp struct
 * @drmfile: pointer to drm_file.
 * @session_type: Type of the session requested. One of enum pxp_session_types.
 * @protection_mode: Type of protection requested for the session. One of the
 *                   enum pxp_protection_modes.
 * @pxp_tag: Numeric session identifier returned back to caller.
 *
 * Return: status. 0 means reserve is successful.
 */
int intel_pxp_sm_ioctl_reserve_session(struct intel_pxp *pxp, struct drm_file *drmfile,
				       int session_type, int protection_mode,
				       u32 *pxp_tag)
{
	int ret;
	int idx = 0;

	if (!drmfile || !pxp_tag)
		return -EINVAL;

	lockdep_assert_held(&pxp->ctx.mutex);

	/* check if sessions are under attack. if so, don't allow creation */
	if (session_type == SESSION_TYPE_TYPE0 &&
	    is_type0_session_attacked(pxp))
		return -EPERM;

	for (idx = 0; idx < session_max(session_type); idx++) {
		if (!is_sw_session_active(pxp, session_type, idx, false)) {
			ret = wait_hw_sw_state(pxp, idx, session_type);
			if (ret)
				return PXP_SM_STATUS_RETRY_REQUIRED;

			ret = create_session_entry(pxp, drmfile, pxp->ctx.id,
						   session_type,
						   protection_mode, idx);
			*pxp_tag = idx;
			return ret;
		}
	}

	return PXP_SM_STATUS_SESSION_NOT_AVAILABLE;
}

/**
 * intel_pxp_sm_ioctl_mark_session_in_play - Put an reserved session to "in_play" state
 * @pxp: pointer to pxp struct
 * @session_type: Type of the session to be updated. One of enum pxp_session_types.
 * @session_id: Session identifier of the session, containing type and index info
 *
 * Return: status. 0 means update is successful.
 */
int intel_pxp_sm_ioctl_mark_session_in_play(struct intel_pxp *pxp, int session_type,
					    u32 session_id)
{
	int ret;
	int session_index;
	int session_type_in_id;
	struct intel_pxp_sm_session *curr, *n;
	struct intel_gt *gt = container_of(pxp, struct intel_gt, pxp);

	ret = pxp_get_session_index(session_id, &session_index, &session_type_in_id);
	if (ret)
		return ret;

	if (session_type != session_type_in_id)
		return -EINVAL;

	lockdep_assert_held(&pxp->ctx.mutex);

	list_for_each_entry_safe(curr, n, session_list(pxp, session_type), list) {
		if (curr->index == session_index) {
			curr->is_in_play = true;
			return 0;
		}
	}

	drm_err(&gt->i915->drm, "Failed to %s couldn't find active session\n", __func__);
	return -EINVAL;
}
