// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#include "walt.h"
#include <linux/of.h>
#include <linux/sched/core_ctl.h>
#include <trace/events/sched.h>
unsigned int sysctl_sched_boost;unsigned int sched_boost_type;enum 
sched_boost_policy boost_policy;static enum sched_boost_policy z61af0b86f7=
SCHED_BOOST_NONE;static DEFINE_MUTEX(z6e41ffbf4c);static void za33e3d1e60(int 
z3e92d20441){if(z3e92d20441==NO_BOOST||z3e92d20441==RESTRAINED_BOOST){
boost_policy=SCHED_BOOST_NONE;return;}if(z61af0b86f7){boost_policy=z61af0b86f7;
return;}if(hmp_capable()){boost_policy=SCHED_BOOST_ON_BIG;return;}boost_policy=
SCHED_BOOST_ON_ALL;}static bool z9fe78fc867(int z3e92d20441){return z3e92d20441
>=RESTRAINED_BOOST_DISABLE&&z3e92d20441<=RESTRAINED_BOOST;}static void 
z1930bdc4b4(void){}static void z3d22747cee(void){core_ctl_set_boost(true);
walt_enable_frequency_aggregation(true);}static void z50f061c8fa(void){
core_ctl_set_boost(false);walt_enable_frequency_aggregation(false);}static void 
zc6ee839520(void){update_cgroup_boost_settings();sched_task_filter_util=
sysctl_sched_min_task_util_for_boost;}static void z5e55108518(void){
sched_task_filter_util=sysctl_sched_min_task_util_for_colocation;
restore_cgroup_boost_settings();}static void z5b02b95569(void){
walt_enable_frequency_aggregation(true);}static void z1c89b1952d(void){
walt_enable_frequency_aggregation(false);}struct zde3b1af216{int z2c102704c8;
void(*z6e3a1d0a71)(void);void(*zc8253195c8)(void);};static struct zde3b1af216 
za01af1d7f0[]={[NO_BOOST]={.z2c102704c8=(0x1edd+254-0x1fdb),.z6e3a1d0a71=
z1930bdc4b4,.zc8253195c8=z1930bdc4b4,},[FULL_THROTTLE_BOOST]={.z2c102704c8=
(0x1f+4186-0x1079),.z6e3a1d0a71=z3d22747cee,.zc8253195c8=z50f061c8fa,},[
CONSERVATIVE_BOOST]={.z2c102704c8=(0x1a04+1077-0x1e39),.z6e3a1d0a71=zc6ee839520,
.zc8253195c8=z5e55108518,},[RESTRAINED_BOOST]={.z2c102704c8=(0x64a+7705-0x2463),
.z6e3a1d0a71=z5b02b95569,.zc8253195c8=z1c89b1952d,},};
#define SCHED_BOOST_START FULL_THROTTLE_BOOST
#define z53b005dde7 (RESTRAINED_BOOST + (0x11ff+3410-0x1f50))
static int z6e07b2160c(void){int z5d971be8b8;for(z5d971be8b8=SCHED_BOOST_START;
z5d971be8b8<z53b005dde7;z5d971be8b8++){if(za01af1d7f0[z5d971be8b8].z2c102704c8>=
(0xb7a+1790-0x1277))return z5d971be8b8;}return NO_BOOST;}static void z82bb50b2e6
(int z3e92d20441){struct zde3b1af216*z829d21719f=&za01af1d7f0[z3e92d20441];int 
z1b640d0ec5;if(z829d21719f->z2c102704c8<=(0x9ef+5419-0x1f1a))return;z829d21719f
->z2c102704c8--;if(z829d21719f->z2c102704c8)return;z829d21719f->zc8253195c8();
z1b640d0ec5=z6e07b2160c();za01af1d7f0[z1b640d0ec5].z6e3a1d0a71();}static void 
zde4620d4a3(int z3e92d20441){struct zde3b1af216*z829d21719f=&za01af1d7f0[
z3e92d20441];int z1b640d0ec5,zf5f877aea3=sched_boost_type;z829d21719f->
z2c102704c8++;if(z829d21719f->z2c102704c8!=(0x140b+4829-0x26e7))return;
z1b640d0ec5=z6e07b2160c();if(z1b640d0ec5==zf5f877aea3)return;za01af1d7f0[
zf5f877aea3].zc8253195c8();za01af1d7f0[z1b640d0ec5].z6e3a1d0a71();}static void 
z6db3ec41d4(void){int z5d971be8b8;for(z5d971be8b8=SCHED_BOOST_START;z5d971be8b8<
z53b005dde7;z5d971be8b8++){if(za01af1d7f0[z5d971be8b8].z2c102704c8>
(0x77+3543-0xe4e)){za01af1d7f0[z5d971be8b8].zc8253195c8();za01af1d7f0[
z5d971be8b8].z2c102704c8=(0xca+8705-0x22cb);}}}static void z991cee001b(int 
z3e92d20441){if(z3e92d20441==(0xe3f+231-0xf26))z6db3ec41d4();else if(z3e92d20441
>(0x3f+3108-0xc63))zde4620d4a3(z3e92d20441);else z82bb50b2e6(-z3e92d20441);
sched_boost_type=z6e07b2160c();sysctl_sched_boost=sched_boost_type;za33e3d1e60(
sysctl_sched_boost);trace_sched_set_boost(sysctl_sched_boost);}void z36aa7fba6a(
void){struct device_node*za9dc58639c;const char*boost_policy;za9dc58639c=
of_find_node_by_path("\x2f\x73\x63\x68\x65\x64\x2d\x68\x6d\x70");if(!za9dc58639c
)return;if(!of_property_read_string(za9dc58639c,
"\x62\x6f\x6f\x73\x74\x2d\x70\x6f\x6c\x69\x63\x79",&boost_policy)){if(!strcmp(
boost_policy,"\x62\x6f\x6f\x73\x74\x2d\x6f\x6e\x2d\x62\x69\x67"))z61af0b86f7=
SCHED_BOOST_ON_BIG;else if(!strcmp(boost_policy,
"\x62\x6f\x6f\x73\x74\x2d\x6f\x6e\x2d\x61\x6c\x6c"))z61af0b86f7=
SCHED_BOOST_ON_ALL;}}int sched_set_boost(int z3e92d20441){int z083920bcc8=
(0x39d+5603-0x1980);mutex_lock(&z6e41ffbf4c);if(z9fe78fc867(z3e92d20441))
z991cee001b(z3e92d20441);else z083920bcc8=-EINVAL;mutex_unlock(&z6e41ffbf4c);
return z083920bcc8;}int sched_boost_handler(struct ctl_table*z047dc75d0e,int 
z123284dc15,void __user*zfc9cd6af11,size_t*zc6af6558dd,loff_t*z9057b9d303){int 
z083920bcc8;unsigned int*data=(unsigned int*)z047dc75d0e->data;mutex_lock(&
z6e41ffbf4c);z083920bcc8=proc_dointvec_minmax(z047dc75d0e,z123284dc15,
zfc9cd6af11,zc6af6558dd,z9057b9d303);if(z083920bcc8||!z123284dc15)goto 
z02a8afcd23;if(z9fe78fc867(*data))z991cee001b(*data);else z083920bcc8=-EINVAL;
z02a8afcd23:mutex_unlock(&z6e41ffbf4c);return z083920bcc8;}
