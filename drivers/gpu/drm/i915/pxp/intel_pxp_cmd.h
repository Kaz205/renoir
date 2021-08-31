/* SPDX-License-Identifier: MIT */
/*
 * Copyright(c) 2020, Intel Corporation. All rights reserved.
 */

#ifndef __INTEL_PXP_CMD_H__
#define __INTEL_PXP_CMD_H__

#include "gt/intel_gt_buffer_pool.h"
#include "intel_pxp.h"

struct i915_vma *intel_pxp_cmd_get_batch(struct intel_pxp *pxp,
					 struct intel_context *ce,
					 struct intel_gt_buffer_pool_node *pool,
					 u32 *cmd_buf, int cmd_size_in_dw);

int intel_pxp_cmd_submit(struct intel_pxp *pxp, u32 *cmd, int cmd_size_in_dw);
#endif /* __INTEL_PXP_SM_H__ */
