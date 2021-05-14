/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note */
/* Copyright(c) 2017-2021 Intel Corporation */

#ifndef _UAPI_GNA_H_
#define _UAPI_GNA_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <linux/types.h>

#define GNA_STS_SCORE_COMPLETED		_BITUL(0)
#define GNA_STS_STATISTICS_VALID	_BITUL(3)
#define GNA_STS_PCI_MMU_ERR		_BITUL(4)
#define GNA_STS_PCI_DMA_ERR		_BITUL(5)
#define GNA_STS_PCI_UNEXCOMPL_ERR	_BITUL(6)
#define GNA_STS_VA_OOR			_BITUL(7)
#define GNA_STS_PARAM_OOR		_BITUL(8)
#define GNA_STS_SATURATE		_BITUL(17)

#define GNA_ERROR			\
	(GNA_STS_PCI_DMA_ERR		|\
	 GNA_STS_PCI_MMU_ERR		|\
	 GNA_STS_PCI_UNEXCOMPL_ERR	|\
	 GNA_STS_PARAM_OOR		|\
	 GNA_STS_VA_OOR)

/*
 * Structure describes part of memory to be overwritten before starting GNA
 */
struct gna_memory_patch {
	/* offset from targeted memory */
	__u64 offset;

	__u64 size;
	__u64 value;
};

struct gna_buffer {
	__u64 memory_id;

	__u64 offset;
	__u64 size;

	__u64 patch_count;
	__u64 patches_ptr;
};

/*
 * Driver performance timestamps in nanoseconds.
 * Values regard system boot time, but do not count during suspend.
 */
struct gna_drv_perf {
	__u64 pre_processing;	/* driver starts pre-processing */
	__u64 processing;	/* hw starts processing */
	__u64 hw_completed;	/* hw finishes processing */
	__u64 completion;	/* driver finishes post-processing */
};

struct gna_hw_perf {
	__u64 total;
	__u64 stall;
};

struct gna_compute_cfg {
	__u32 layer_base;
	__u32 layer_count;

	/* List of GNA memory buffers */
	__u64 buffers_ptr;
	__u64 buffer_count;

	__u8 active_list_on;
	__u8 gna_mode;
	__u8 hw_perf_encoding;
	__u8 pad[5];
};

union gna_memory_map {
	struct {
		__u64 address;
		__u32 size;
		__u32 pad;
	} in;

	struct {
		__u64 memory_id;
	} out;
};

#if defined(__cplusplus)
}
#endif

#endif /* _UAPI_GNA_H_ */
