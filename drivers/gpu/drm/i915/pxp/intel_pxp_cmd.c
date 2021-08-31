// SPDX-License-Identifier: MIT
/*
 * Copyright(c) 2020, Intel Corporation. All rights reserved.
 */

#include "intel_pxp_cmd.h"
#include "i915_drv.h"
#include "gt/intel_context.h"
#include "gt/intel_engine_pm.h"

struct i915_vma *intel_pxp_cmd_get_batch(struct intel_pxp *pxp,
					 struct intel_context *ce,
					 struct intel_gt_buffer_pool_node *pool,
					 u32 *cmd_buf, int cmd_size_in_dw)
{
	struct i915_vma *batch = ERR_PTR(-EINVAL);
	struct intel_gt *gt = container_of(pxp, struct intel_gt, pxp);
	u32 *cmd;

	if (!ce || !ce->engine || !cmd_buf)
		return ERR_PTR(-EINVAL);

	if (cmd_size_in_dw * 4 > PAGE_SIZE) {
		drm_err(&gt->i915->drm, "Failed to %s, invalid cmd_size_id_dw=[%d]\n",
			__func__, cmd_size_in_dw);
		return ERR_PTR(-EINVAL);
	}

	cmd = i915_gem_object_pin_map(pool->obj, I915_MAP_FORCE_WC);
	if (IS_ERR(cmd)) {
		drm_err(&gt->i915->drm, "Failed to i915_gem_object_pin_map()\n");
		return ERR_PTR(-EINVAL);
	}

	memcpy(cmd, cmd_buf, cmd_size_in_dw * 4);

	if (drm_debug_enabled(DRM_UT_DRIVER)) {
		print_hex_dump(KERN_DEBUG, "cmd binaries:",
			       DUMP_PREFIX_OFFSET, 4, 4, cmd, cmd_size_in_dw * 4, true);
	}

	i915_gem_object_unpin_map(pool->obj);

	batch = i915_vma_instance(pool->obj, ce->vm, NULL);
	if (IS_ERR(batch)) {
		drm_err(&gt->i915->drm, "Failed to i915_vma_instance()\n");
		return batch;
	}

	return batch;
}

int intel_pxp_cmd_submit(struct intel_pxp *pxp, u32 *cmd, int cmd_size_in_dw)
{
	int err = -EINVAL;
	struct i915_vma *batch;
	struct i915_request *rq;
	struct intel_context *ce = NULL;
	bool is_engine_pm_get = false;
	bool is_batch_vma_pin = false;
	bool is_skip_req_on_err = false;
	bool is_engine_get_pool = false;
	struct intel_gt_buffer_pool_node *pool = NULL;
	struct intel_gt *gt = container_of(pxp, struct intel_gt, pxp);

	if (!HAS_ENGINE(gt, VCS0) ||
	    !gt->engine[VCS0]->kernel_context) {
		err = -EINVAL;
		goto end;
	}

	if (!cmd || (cmd_size_in_dw * 4) > PAGE_SIZE) {
		drm_err(&gt->i915->drm, "Failed to %s bad params\n", __func__);
		return -EINVAL;
	}

	ce = gt->engine[VCS0]->kernel_context;

	intel_engine_pm_get(ce->engine);
	is_engine_pm_get = true;

	pool = intel_gt_get_buffer_pool(gt, PAGE_SIZE);
	if (IS_ERR(pool)) {
		drm_err(&gt->i915->drm, "Failed to intel_engine_get_pool()\n");
		err = PTR_ERR(pool);
		goto end;
	}
	is_engine_get_pool = true;

	batch = intel_pxp_cmd_get_batch(pxp, ce, pool, cmd, cmd_size_in_dw);
	if (IS_ERR(batch)) {
		drm_err(&gt->i915->drm, "Failed to intel_pxp_cmd_get_batch()\n");
		err = PTR_ERR(batch);
		goto end;
	}

	err = i915_vma_pin(batch, 0, 0, PIN_USER);
	if (err) {
		drm_err(&gt->i915->drm, "Failed to i915_vma_pin()\n");
		goto end;
	}
	is_batch_vma_pin = true;

	rq = intel_context_create_request(ce);
	if (IS_ERR(rq)) {
		drm_err(&gt->i915->drm, "Failed to intel_context_create_request()\n");
		err = PTR_ERR(rq);
		goto end;
	}
	is_skip_req_on_err = true;

	err = intel_gt_buffer_pool_mark_active(pool, rq);
	if (err) {
		drm_err(&gt->i915->drm, "Failed to intel_engine_pool_mark_active()\n");
		goto end;
	}

	i915_vma_lock(batch);
	err = i915_request_await_object(rq, batch->obj, false);
	if (!err)
		err = i915_vma_move_to_active(batch, rq, 0);
	i915_vma_unlock(batch);
	if (err) {
		drm_err(&gt->i915->drm, "Failed to i915_request_await_object()\n");
		goto end;
	}

	if (ce->engine->emit_init_breadcrumb) {
		err = ce->engine->emit_init_breadcrumb(rq);
		if (err) {
			drm_err(&gt->i915->drm, "Failed to emit_init_breadcrumb()\n");
			goto end;
		}
	}

	err = ce->engine->emit_bb_start(rq, batch->node.start,
		batch->node.size, 0);
	if (err) {
		drm_err(&gt->i915->drm, "Failed to emit_bb_start()\n");
		goto end;
	}

	i915_request_add(rq);

end:
	if (unlikely(err) && is_skip_req_on_err)
		i915_request_set_error_once(rq, err);

	if (is_batch_vma_pin)
		i915_vma_unpin(batch);

	if (is_engine_get_pool)
		intel_gt_buffer_pool_put(pool);

	if (is_engine_pm_get)
		intel_engine_pm_put(ce->engine);

	return err;
}
