// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#include <linux/module.h>
#include <linux/percpu.h>
#include <linux/hrtimer.h>
#include <linux/sched.h>
#include <linux/math64.h>
#include "walt.h"
#include <trace/events/sched.h>
static DEFINE_PER_CPU(u64,WALT5c03c65a13);static DEFINE_PER_CPU(u64,
WALTde16cdc0f2);static DEFINE_PER_CPU(u64,WALT95bc2af379);static DEFINE_PER_CPU(
u64,nr);static DEFINE_PER_CPU(u64,nr_max);static DEFINE_PER_CPU(spinlock_t,
WALTe6ee2b56c7)=__SPIN_LOCK_UNLOCKED(WALTe6ee2b56c7);static s64 WALTd1b16ed698;
unsigned int sysctl_sched_busy_hyst_enable_cpus;unsigned int 
sysctl_sched_busy_hyst;unsigned int sysctl_sched_coloc_busy_hyst_enable_cpus=
(0xfb2+3842-0x1e44);unsigned int sysctl_sched_coloc_busy_hyst_cpu[NR_CPUS]={[
(0x447+8660-0x261b)...NR_CPUS-(0x709+6694-0x212e)]=39000000};unsigned int 
sysctl_sched_coloc_busy_hyst_max_ms=(0x1627+3842-0x11a1);unsigned int 
sysctl_sched_coloc_busy_hyst_cpu_busy_pct[NR_CPUS]={[(0x387+1412-0x90b)...
NR_CPUS-(0x2e7+6782-0x1d64)]=(0x2a2+4378-0x13b2)};static DEFINE_PER_CPU(
atomic64_t,WALT739b44b3f3)=ATOMIC64_INIT((0x5d7+4139-0x1602));static 
DEFINE_PER_CPU(u64,WALT701fb8f8ec);static DEFINE_PER_CPU(u64,WALTe6a70b82b5);
static DEFINE_PER_CPU(u64,WALTd437d08ea3);
#define WALTcc368a061f		(0xf95+5445-0x24cb)
#define WALT74fd8dfb0d (sysctl_sched_coloc_busy_hyst_max_ms * NSEC_PER_MSEC)
void sched_get_nr_running_avg(struct sched_avg_stats*WALTf0f82ef4d0){int 
WALT8f9ab72eb9;u64 WALT3822d537f6=sched_clock();u64 WALT65b7325c24=
WALT3822d537f6-WALTd1b16ed698;u64 WALT42db3f0aea,WALT346aee5ac3;bool 
WALT6f04dcfcbc=false;if(!WALT65b7325c24)return;for_each_possible_cpu(
WALT8f9ab72eb9){unsigned long WALT05b7c9a580;u64 WALT1f1d98d140;
spin_lock_irqsave(&per_cpu(WALTe6ee2b56c7,WALT8f9ab72eb9),WALT05b7c9a580);
WALT3822d537f6=sched_clock();WALT1f1d98d140=WALT3822d537f6-per_cpu(
WALTde16cdc0f2,WALT8f9ab72eb9);BUG_ON((s64)WALT1f1d98d140<(0x3ff+6959-0x1f2e));
WALT42db3f0aea=per_cpu(WALT5c03c65a13,WALT8f9ab72eb9);WALT42db3f0aea+=per_cpu(nr
,WALT8f9ab72eb9)*WALT1f1d98d140;WALT42db3f0aea=div64_u64((WALT42db3f0aea*
(0x12f2+5175-0x26c5)),WALT65b7325c24);WALT346aee5ac3=per_cpu(WALT95bc2af379,
WALT8f9ab72eb9);WALT346aee5ac3+=walt_big_tasks(WALT8f9ab72eb9)*WALT1f1d98d140;
WALT346aee5ac3=div64_u64((WALT346aee5ac3*(0x914+7082-0x245a)),WALT65b7325c24);
WALTf0f82ef4d0[WALT8f9ab72eb9].nr=(int)div64_u64((WALT42db3f0aea+WALTcc368a061f)
,(0xfc2+5099-0x2349));WALTf0f82ef4d0[WALT8f9ab72eb9].nr_misfit=(int)div64_u64((
WALT346aee5ac3+WALTcc368a061f),(0x7c1+5180-0x1b99));WALTf0f82ef4d0[
WALT8f9ab72eb9].nr_max=per_cpu(nr_max,WALT8f9ab72eb9);WALTf0f82ef4d0[
WALT8f9ab72eb9].nr_scaled=WALT42db3f0aea;trace_sched_get_nr_running_avg(
WALT8f9ab72eb9,WALTf0f82ef4d0[WALT8f9ab72eb9].nr,WALTf0f82ef4d0[WALT8f9ab72eb9].
nr_misfit,WALTf0f82ef4d0[WALT8f9ab72eb9].nr_max,WALTf0f82ef4d0[WALT8f9ab72eb9].
nr_scaled);per_cpu(WALTde16cdc0f2,WALT8f9ab72eb9)=WALT3822d537f6;per_cpu(
WALT5c03c65a13,WALT8f9ab72eb9)=(0x1d11+140-0x1d9d);per_cpu(WALT95bc2af379,
WALT8f9ab72eb9)=(0xec6+2268-0x17a2);per_cpu(nr_max,WALT8f9ab72eb9)=per_cpu(nr,
WALT8f9ab72eb9);spin_unlock_irqrestore(&per_cpu(WALTe6ee2b56c7,WALT8f9ab72eb9),
WALT05b7c9a580);}for_each_possible_cpu(WALT8f9ab72eb9){if(per_cpu(WALTd437d08ea3
,WALT8f9ab72eb9)){WALT6f04dcfcbc=true;break;}}if(WALT6f04dcfcbc&&
get_rtgb_active_time()>=WALT74fd8dfb0d)sched_update_hyst_times();WALTd1b16ed698=
WALT3822d537f6;}EXPORT_SYMBOL(sched_get_nr_running_avg);void 
sched_update_hyst_times(void){bool WALTe5f9c419f8;int WALT8f9ab72eb9;unsigned 
long WALTc752305af9,WALT523e5f5a97;WALTe5f9c419f8=is_rtgb_active()&&(sched_boost
()!=CONSERVATIVE_BOOST)&&(get_rtgb_active_time()<WALT74fd8dfb0d);
for_each_possible_cpu(WALT8f9ab72eb9){WALTc752305af9=arch_scale_cpu_capacity(
WALT8f9ab72eb9);WALT523e5f5a97=sysctl_sched_coloc_busy_hyst_cpu_busy_pct[
WALT8f9ab72eb9];per_cpu(WALT701fb8f8ec,WALT8f9ab72eb9)=(BIT(WALT8f9ab72eb9)&
sysctl_sched_busy_hyst_enable_cpus)?sysctl_sched_busy_hyst:(0x18d3+853-0x1c28);
per_cpu(WALTd437d08ea3,WALT8f9ab72eb9)=((BIT(WALT8f9ab72eb9)&
sysctl_sched_coloc_busy_hyst_enable_cpus)&&WALTe5f9c419f8)?
sysctl_sched_coloc_busy_hyst_cpu[WALT8f9ab72eb9]:(0x27a+7022-0x1de8);per_cpu(
WALTe6a70b82b5,WALT8f9ab72eb9)=mult_frac(WALTc752305af9,WALT523e5f5a97,
(0x826+7464-0x24ea));}}
#define WALT8dd50955b9		(0x1248+3211-0x1ed0)
#define WALTed8d29ed55	(0x1272+775-0x156f)
static inline void WALTecd7b5dadc(int WALT8f9ab72eb9,bool WALTea3d214cf5,
unsigned long WALTa70cd3cf53,u64 WALT3822d537f6){bool WALT164d00420c=false;bool 
WALTb616236140=false,WALTb25f184b7b=false;u64 WALT0150aac757;if(!per_cpu(
WALT701fb8f8ec,WALT8f9ab72eb9)&&!per_cpu(WALTd437d08ea3,WALT8f9ab72eb9))return;
if(WALTa70cd3cf53>=WALT8dd50955b9&&per_cpu(nr,WALT8f9ab72eb9)<WALT8dd50955b9)
WALT164d00420c=true;if(WALTea3d214cf5&&(cpu_util(WALT8f9ab72eb9)*WALTed8d29ed55)
>capacity_orig_of(WALT8f9ab72eb9))WALTb616236140=true;if(WALTea3d214cf5&&
cpu_util(WALT8f9ab72eb9)>per_cpu(WALTe6a70b82b5,WALT8f9ab72eb9))WALTb25f184b7b=
true;WALT0150aac757=max((WALT164d00420c||WALTb616236140)?per_cpu(WALT701fb8f8ec,
WALT8f9ab72eb9):(0x811+1609-0xe5a),(WALT164d00420c||WALTb25f184b7b)?per_cpu(
WALTd437d08ea3,WALT8f9ab72eb9):(0x563+3640-0x139b));if(WALT0150aac757)
atomic64_set(&per_cpu(WALT739b44b3f3,WALT8f9ab72eb9),WALT3822d537f6+
WALT0150aac757);}int sched_busy_hyst_handler(struct ctl_table*WALT047dc75d0e,int
 WALT123284dc15,void __user*WALTfc9cd6af11,size_t*WALTc6af6558dd,loff_t*
WALT9057b9d303){int WALT083920bcc8;if(WALT047dc75d0e->maxlen>(sizeof(unsigned 
int)*num_possible_cpus()))WALT047dc75d0e->maxlen=sizeof(unsigned int)*
num_possible_cpus();WALT083920bcc8=proc_dointvec_minmax(WALT047dc75d0e,
WALT123284dc15,WALTfc9cd6af11,WALTc6af6558dd,WALT9057b9d303);if(!WALT083920bcc8
&&WALT123284dc15)sched_update_hyst_times();return WALT083920bcc8;}void 
sched_update_nr_prod(int WALT8f9ab72eb9,long WALT17abc14e87,bool WALTef3ecb031d)
{u64 WALT1f1d98d140;u64 WALT3822d537f6;unsigned long WALT05b7c9a580,
WALT8a91c84c00;spin_lock_irqsave(&per_cpu(WALTe6ee2b56c7,WALT8f9ab72eb9),
WALT05b7c9a580);WALT8a91c84c00=per_cpu(nr,WALT8f9ab72eb9);WALT3822d537f6=
sched_clock();WALT1f1d98d140=WALT3822d537f6-per_cpu(WALTde16cdc0f2,
WALT8f9ab72eb9);BUG_ON((s64)WALT1f1d98d140<(0x1c6b+358-0x1dd1));per_cpu(
WALTde16cdc0f2,WALT8f9ab72eb9)=WALT3822d537f6;per_cpu(nr,WALT8f9ab72eb9)=
WALT8a91c84c00+(WALTef3ecb031d?WALT17abc14e87:-WALT17abc14e87);BUG_ON((s64)
per_cpu(nr,WALT8f9ab72eb9)<(0x51b+8366-0x25c9));if(per_cpu(nr,WALT8f9ab72eb9)>
per_cpu(nr_max,WALT8f9ab72eb9))per_cpu(nr_max,WALT8f9ab72eb9)=per_cpu(nr,
WALT8f9ab72eb9);WALTecd7b5dadc(WALT8f9ab72eb9,!WALTef3ecb031d,WALT8a91c84c00,
WALT3822d537f6);per_cpu(WALT5c03c65a13,WALT8f9ab72eb9)+=WALT8a91c84c00*
WALT1f1d98d140;per_cpu(WALT95bc2af379,WALT8f9ab72eb9)+=walt_big_tasks(
WALT8f9ab72eb9)*WALT1f1d98d140;spin_unlock_irqrestore(&per_cpu(WALTe6ee2b56c7,
WALT8f9ab72eb9),WALT05b7c9a580);}EXPORT_SYMBOL(sched_update_nr_prod);unsigned 
int sched_get_cpu_util(int WALT8f9ab72eb9){struct rq*rq=cpu_rq(WALT8f9ab72eb9);
u64 WALTb0b0149580;unsigned long WALTfbbdeffe9c,WALT05b7c9a580;unsigned int 
WALT517f9bdd84;raw_spin_lock_irqsave(&rq->lock,WALT05b7c9a580);WALTfbbdeffe9c=
capacity_orig_of(WALT8f9ab72eb9);WALTb0b0149580=rq->wrq.prev_runnable_sum+rq->
wrq.grp_time.prev_runnable_sum;WALTb0b0149580=div64_u64(WALTb0b0149580,
sched_ravg_window>>SCHED_CAPACITY_SHIFT);raw_spin_unlock_irqrestore(&rq->lock,
WALT05b7c9a580);WALTb0b0149580=(WALTb0b0149580>=WALTfbbdeffe9c)?WALTfbbdeffe9c:
WALTb0b0149580;WALT517f9bdd84=div64_ul((WALTb0b0149580*(0xb35+5770-0x215b)),
WALTfbbdeffe9c);return WALT517f9bdd84;}u64 sched_lpm_disallowed_time(int 
WALT8f9ab72eb9){u64 WALT2c53bb3f34=sched_clock();u64 WALT09c73f1899=
atomic64_read(&per_cpu(WALT739b44b3f3,WALT8f9ab72eb9));if(WALT2c53bb3f34<
WALT09c73f1899)return WALT09c73f1899-WALT2c53bb3f34;return(0x19a1+1756-0x207d);}
