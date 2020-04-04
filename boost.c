// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#include "walt.h"
#include <linux/of.h>
#include <linux/sched/core_ctl.h>
#include <trace/events/sched.h>
unsigned int sysctl_sched_boost;unsigned int sched_boost_type;enum 
sched_boost_policy boost_policy;static enum sched_boost_policy WALT61af0b86f7=
SCHED_BOOST_NONE;static DEFINE_MUTEX(WALT6e41ffbf4c);
#if defined(CONFIG_UCLAMP_TASK_GROUP)
void walt_init_sched_boost(struct task_group*WALTf1cad98b51){WALTf1cad98b51->
sched_boost_no_override=false;WALTf1cad98b51->sched_boost_enabled=true;
WALTf1cad98b51->colocate=false;WALTf1cad98b51->colocate_update_disabled=false;}
static void update_cgroup_boost_settings(void){struct task_group*WALTf1cad98b51;
rcu_read_lock();list_for_each_entry_rcu(WALTf1cad98b51,&task_groups,list){if(
WALTf1cad98b51->sched_boost_no_override)continue;WALTf1cad98b51->
sched_boost_enabled=false;}rcu_read_unlock();}static void 
restore_cgroup_boost_settings(void){struct task_group*WALTf1cad98b51;
rcu_read_lock();list_for_each_entry_rcu(WALTf1cad98b51,&task_groups,list)
WALTf1cad98b51->sched_boost_enabled=true;rcu_read_unlock();}
#else
static void update_cgroup_boost_settings(void){}static void 
restore_cgroup_boost_settings(void){}
#endif
static void WALTa33e3d1e60(int WALT3e92d20441){if(WALT3e92d20441==NO_BOOST||
WALT3e92d20441==RESTRAINED_BOOST){boost_policy=SCHED_BOOST_NONE;return;}if(
WALT61af0b86f7){boost_policy=WALT61af0b86f7;return;}if(hmp_capable()){
boost_policy=SCHED_BOOST_ON_BIG;return;}boost_policy=SCHED_BOOST_ON_ALL;}static 
bool WALT9fe78fc867(int WALT3e92d20441){return WALT3e92d20441>=
RESTRAINED_BOOST_DISABLE&&WALT3e92d20441<=RESTRAINED_BOOST;}static void 
WALT1930bdc4b4(void){}static void WALT3d22747cee(void){core_ctl_set_boost(true);
walt_enable_frequency_aggregation(true);}static void WALT50f061c8fa(void){
core_ctl_set_boost(false);walt_enable_frequency_aggregation(false);}static void 
WALTc6ee839520(void){update_cgroup_boost_settings();sched_task_filter_util=
sysctl_sched_min_task_util_for_boost;}static void WALT5e55108518(void){
sched_task_filter_util=sysctl_sched_min_task_util_for_colocation;
restore_cgroup_boost_settings();}static void WALT5b02b95569(void){
walt_enable_frequency_aggregation(true);}static void WALT1c89b1952d(void){
walt_enable_frequency_aggregation(false);}struct WALTde3b1af216{int 
WALT2c102704c8;void(*WALT6e3a1d0a71)(void);void(*WALTc8253195c8)(void);};static 
struct WALTde3b1af216 WALTa01af1d7f0[]={[NO_BOOST]={.WALT2c102704c8=
(0x13f+7813-0x1fc4),.WALT6e3a1d0a71=WALT1930bdc4b4,.WALTc8253195c8=
WALT1930bdc4b4,},[FULL_THROTTLE_BOOST]={.WALT2c102704c8=(0x26a+1510-0x850),.
WALT6e3a1d0a71=WALT3d22747cee,.WALTc8253195c8=WALT50f061c8fa,},[
CONSERVATIVE_BOOST]={.WALT2c102704c8=(0x1437+3723-0x22c2),.WALT6e3a1d0a71=
WALTc6ee839520,.WALTc8253195c8=WALT5e55108518,},[RESTRAINED_BOOST]={.
WALT2c102704c8=(0x10c5+4837-0x23aa),.WALT6e3a1d0a71=WALT5b02b95569,.
WALTc8253195c8=WALT1c89b1952d,},};
#define SCHED_BOOST_START FULL_THROTTLE_BOOST
#define WALT53b005dde7 (RESTRAINED_BOOST + (0x13db+1084-0x1816))
static int WALT6e07b2160c(void){int WALT5d971be8b8;for(WALT5d971be8b8=
SCHED_BOOST_START;WALT5d971be8b8<WALT53b005dde7;WALT5d971be8b8++){if(
WALTa01af1d7f0[WALT5d971be8b8].WALT2c102704c8>=(0x1061+2730-0x1b0a))return 
WALT5d971be8b8;}return NO_BOOST;}static void WALT82bb50b2e6(int WALT3e92d20441){
struct WALTde3b1af216*WALT829d21719f=&WALTa01af1d7f0[WALT3e92d20441];int 
WALT1b640d0ec5;if(WALT829d21719f->WALT2c102704c8<=(0x5c0+3791-0x148f))return;
WALT829d21719f->WALT2c102704c8--;if(WALT829d21719f->WALT2c102704c8)return;
WALT829d21719f->WALTc8253195c8();WALT1b640d0ec5=WALT6e07b2160c();WALTa01af1d7f0[
WALT1b640d0ec5].WALT6e3a1d0a71();}static void WALTde4620d4a3(int WALT3e92d20441)
{struct WALTde3b1af216*WALT829d21719f=&WALTa01af1d7f0[WALT3e92d20441];int 
WALT1b640d0ec5,WALTf5f877aea3=sched_boost_type;WALT829d21719f->WALT2c102704c8++;
if(WALT829d21719f->WALT2c102704c8!=(0x10d0+3509-0x1e84))return;WALT1b640d0ec5=
WALT6e07b2160c();if(WALT1b640d0ec5==WALTf5f877aea3)return;WALTa01af1d7f0[
WALTf5f877aea3].WALTc8253195c8();WALTa01af1d7f0[WALT1b640d0ec5].WALT6e3a1d0a71()
;}static void WALT6db3ec41d4(void){int WALT5d971be8b8;for(WALT5d971be8b8=
SCHED_BOOST_START;WALT5d971be8b8<WALT53b005dde7;WALT5d971be8b8++){if(
WALTa01af1d7f0[WALT5d971be8b8].WALT2c102704c8>(0x927+1483-0xef2)){WALTa01af1d7f0
[WALT5d971be8b8].WALTc8253195c8();WALTa01af1d7f0[WALT5d971be8b8].WALT2c102704c8=
(0x5d1+6868-0x20a5);}}}static void WALT991cee001b(int WALT3e92d20441){if(
WALT3e92d20441==(0x529+4902-0x184f))WALT6db3ec41d4();else if(WALT3e92d20441>
(0x2aa+6052-0x1a4e))WALTde4620d4a3(WALT3e92d20441);else WALT82bb50b2e6(-
WALT3e92d20441);sched_boost_type=WALT6e07b2160c();sysctl_sched_boost=
sched_boost_type;WALTa33e3d1e60(sysctl_sched_boost);trace_sched_set_boost(
sysctl_sched_boost);}void WALT36aa7fba6a(void){struct device_node*WALTa9dc58639c
;const char*boost_policy;WALTa9dc58639c=of_find_node_by_path(
"\x2f\x73\x63\x68\x65\x64\x2d\x68\x6d\x70");if(!WALTa9dc58639c)return;if(!
of_property_read_string(WALTa9dc58639c,
"\x62\x6f\x6f\x73\x74\x2d\x70\x6f\x6c\x69\x63\x79",&boost_policy)){if(!strcmp(
boost_policy,"\x62\x6f\x6f\x73\x74\x2d\x6f\x6e\x2d\x62\x69\x67"))WALT61af0b86f7=
SCHED_BOOST_ON_BIG;else if(!strcmp(boost_policy,
"\x62\x6f\x6f\x73\x74\x2d\x6f\x6e\x2d\x61\x6c\x6c"))WALT61af0b86f7=
SCHED_BOOST_ON_ALL;}}int sched_set_boost(int WALT3e92d20441){int WALT083920bcc8=
(0x87f+4811-0x1b4a);mutex_lock(&WALT6e41ffbf4c);if(WALT9fe78fc867(WALT3e92d20441
))WALT991cee001b(WALT3e92d20441);else WALT083920bcc8=-EINVAL;mutex_unlock(&
WALT6e41ffbf4c);return WALT083920bcc8;}int sched_boost_handler(struct ctl_table*
WALT047dc75d0e,int WALT123284dc15,void __user*WALTfc9cd6af11,size_t*
WALTc6af6558dd,loff_t*WALT9057b9d303){int WALT083920bcc8;unsigned int*data=(
unsigned int*)WALT047dc75d0e->data;mutex_lock(&WALT6e41ffbf4c);WALT083920bcc8=
proc_dointvec_minmax(WALT047dc75d0e,WALT123284dc15,WALTfc9cd6af11,WALTc6af6558dd
,WALT9057b9d303);if(WALT083920bcc8||!WALT123284dc15)goto WALT02a8afcd23;if(
WALT9fe78fc867(*data))WALT991cee001b(*data);else WALT083920bcc8=-EINVAL;
WALT02a8afcd23:mutex_unlock(&WALT6e41ffbf4c);return WALT083920bcc8;}
