include $(srctree)/techpack/sched/sched.conf
LINUXINCLUDE    += \
		-include $(srctree)/techpack/sched/schedconf.h

obj-$(CONFIG_SCHED_WALT) += trace.o

ifneq ($(HAS_SCHED_SRC_DIR),true)
ccflags-y := -Wno-non-literal-null-conversion
obj-$(CONFIG_SCHED_WALT) += walt.o boost.o sched_avg.o qc_vas.o core_ctl.o
#obj-$(CONFIG_CPU_BOOST) += cpu-boost.o
else # HAS_SCHED_SRC_DIR
obj-$(CONFIG_SCHED_WALT) += src/walt.o src/boost.o src/sched_avg.o src/qc_vas.o src/core_ctl.o
#obj-$(CONFIG_CPU_BOOST) += src/cpu-boost.o
endif # HAS_SCHED_SRC_DIR
