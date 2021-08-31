/* SPDX-License-Identifier: MIT */
/*
 * Copyright(c) 2020, Intel Corporation. All rights reserved.
 */

#ifndef __INTEL_PXP_CONTEXT_H__
#define __INTEL_PXP_CONTEXT_H__

#include <linux/mutex.h>
#include "intel_pxp_arb.h"

/* struct pxp_context - Represents combined view of driver and logical HW states. */
struct pxp_context {
	/** @mutex: mutex to protect the pxp context */
	struct mutex mutex;

	struct pxp_protected_session arb_session;
	u32 arb_session_pxp_tag;

	struct list_head type0_sessions;
	struct list_head type1_sessions;

	int id;

	bool global_state_attacked;
	bool global_state_in_suspend;
	bool flag_display_hm_surface_keys;
};

void intel_pxp_ctx_init(struct pxp_context *ctx);
void intel_pxp_ctx_fini(struct pxp_context *ctx);

#endif /* __INTEL_PXP_CONTEXT_H__ */
