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
