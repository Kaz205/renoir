include $(srctree)/techpack/sched/sched.conf
LINUXINCLUDE    += \
		-include $(srctree)/techpack/sched/schedconf.h
ccflags-y := -Wno-non-literal-null-conversion
ccflags-y += $(call cc-option, -Wno-misleading-indentation)
obj-$(CONFIG_SCHED_WALT) += walt.o boost.o sched_avg.o qc_vas.o core_ctl.o trace.o
obj-$(CONFIG_CPU_BOOST) += cpu-boost.o
