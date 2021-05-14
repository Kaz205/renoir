/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright(c) 2017-2021 Intel Corporation */

#ifndef __GNA_HW_H__
#define __GNA_HW_H__

#include <linux/mm_types.h>

struct gna_dev_info {
	u32 hwid;
	u32 num_pagetables;
	u32 num_page_entries;
	u32 max_layer_count;
	u64 max_hw_mem;
};

#endif // __GNA_HW_H__
