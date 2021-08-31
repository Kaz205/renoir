/* SPDX-License-Identifier: MIT */
/*
 * Copyright(c) 2020, Intel Corporation. All rights reserved.
 */

#ifndef __INTEL_PXP_CONTEXT_H__
#define __INTEL_PXP_CONTEXT_H__

#include <linux/mutex.h>

/* struct pxp_context - Represents combined view of driver and logical HW states. */
struct pxp_context {
	/** @mutex: mutex to protect the pxp context */
	struct mutex mutex;

	int id;
};

void intel_pxp_ctx_init(struct pxp_context *ctx);
void intel_pxp_ctx_fini(struct pxp_context *ctx);

#endif /* __INTEL_PXP_CONTEXT_H__ */
