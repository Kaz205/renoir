// SPDX-License-Identifier: GPL-2.0-only
/* Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "cam_req_mgr_timer.h"
#include "cam_debug_util.h"

void crm_timer_reset(struct cam_req_mgr_timer *crm_timer)
{
	if (!crm_timer)
		return;
	CAM_DBG(CAM_CRM, "Starting timer to fire in %d ms. (jiffies=%lu)\n",
		crm_timer->expires, jiffies);
	mod_timer(&crm_timer->sys_timer,
		(jiffies + msecs_to_jiffies(crm_timer->expires)));
}

void crm_timer_callback(struct timer_list *timer_data)
{
	struct cam_req_mgr_timer *timer =
		container_of(timer_data, struct cam_req_mgr_timer, sys_timer);
	if (!timer) {
		CAM_ERR(CAM_CRM, "NULL timer");
		return;
	}
	CAM_DBG(CAM_CRM, "timer %pK parent %pK", timer, timer->parent);
	crm_timer_reset(timer);
}

void crm_timer_modify(struct cam_req_mgr_timer *crm_timer,
	int32_t expires)
{
	CAM_DBG(CAM_CRM, "new time %d", expires);
	if (crm_timer) {
		crm_timer->expires = expires;
		crm_timer_reset(crm_timer);
	}
}

/* TODO: Revisiting this code and check for memory leak. Rethinking
 * the usage of "kmem_cache_create" and "kmem_cache_alloc".
 */
int crm_timer_init(struct cam_req_mgr_timer **timer, int32_t expires,
		   void *parent, void (*timer_cb)(struct timer_list *))
{
	int                       ret = 0;
	struct cam_req_mgr_timer *crm_timer = NULL;
	struct kmem_cache *tm_kmem_cache = NULL;

	CAM_DBG(CAM_CRM, "init timer %d %pK", expires, *timer);

	if (*timer == NULL) {
		tm_kmem_cache = kmem_cache_create("crm_timer",
						  sizeof(*crm_timer), 64,
						  SLAB_CONSISTENCY_CHECKS |
						  SLAB_RED_ZONE | SLAB_POISON |
						  SLAB_STORE_USER, NULL);
		if (tm_kmem_cache) {
			crm_timer = kmem_cache_alloc(tm_kmem_cache, __GFP_ZERO |
						     GFP_KERNEL);
			if (!crm_timer) {
				ret = -ENOMEM;
				goto end;
			}
		}

		else {
			ret = -ENOMEM;
			goto end;
		}

		if (timer_cb != NULL)
			crm_timer->timer_cb = timer_cb;
		else
			crm_timer->timer_cb = crm_timer_callback;

		crm_timer->expires = expires;
		crm_timer->parent = parent;
		crm_timer->tmr_cachep = tm_kmem_cache;
		timer_setup(&crm_timer->sys_timer, crm_timer->timer_cb, 0);
		crm_timer_reset(crm_timer);
		*timer = crm_timer;
	} else {
		CAM_WARN(CAM_CRM, "Timer already exists!!");
		ret = -EINVAL;
	}
end:
	return ret;
}

void crm_timer_exit(struct cam_req_mgr_timer **crm_timer)
{
	CAM_DBG(CAM_CRM, "destroy timer %pK @ %pK", *crm_timer, crm_timer);
	if (*crm_timer) {
		del_timer_sync(&(*crm_timer)->sys_timer);
		if ((*crm_timer)->tmr_cachep)
			kmem_cache_free((*crm_timer)->tmr_cachep, *crm_timer);
		*crm_timer = NULL;
	}
}
