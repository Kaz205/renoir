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
(0x584+4599-0x170b);unsigned int sysctl_sched_coloc_busy_hyst=39000000;unsigned 
int sysctl_sched_coloc_busy_hyst_max_ms=(0x160a+9265-0x26b3);static 
DEFINE_PER_CPU(atomic64_t,WALT739b44b3f3)=ATOMIC64_INIT((0x17c0+188-0x187c));
static DEFINE_PER_CPU(u64,WALT701fb8f8ec);
#define WALTcc368a061f		(0xae4+3659-0x1920)
#define WALT74fd8dfb0d (sysctl_sched_coloc_busy_hyst_max_ms * NSEC_PER_MSEC)
void sched_get_nr_running_avg(struct sched_avg_stats*WALTf0f82ef4d0){int 
WALT8f9ab72eb9;u64 WALT3822d537f6=sched_clock();u64 WALT65b7325c24=
WALT3822d537f6-WALTd1b16ed698;u64 WALT42db3f0aea,WALT346aee5ac3;bool 
WALT6f04dcfcbc=false;if(!WALT65b7325c24)return;for_each_possible_cpu(
WALT8f9ab72eb9){unsigned long WALT05b7c9a580;u64 WALT1f1d98d140;
spin_lock_irqsave(&per_cpu(WALTe6ee2b56c7,WALT8f9ab72eb9),WALT05b7c9a580);
WALT3822d537f6=sched_clock();WALT1f1d98d140=WALT3822d537f6-per_cpu(
WALTde16cdc0f2,WALT8f9ab72eb9);BUG_ON((s64)WALT1f1d98d140<(0x6f8+4766-0x1996));
WALT42db3f0aea=per_cpu(WALT5c03c65a13,WALT8f9ab72eb9);WALT42db3f0aea+=per_cpu(nr
,WALT8f9ab72eb9)*WALT1f1d98d140;WALT42db3f0aea=div64_u64((WALT42db3f0aea*
(0x134+443-0x28b)),WALT65b7325c24);WALT346aee5ac3=per_cpu(WALT95bc2af379,
WALT8f9ab72eb9);WALT346aee5ac3+=walt_big_tasks(WALT8f9ab72eb9)*WALT1f1d98d140;
WALT346aee5ac3=div64_u64((WALT346aee5ac3*(0x3b5+1756-0xa2d)),WALT65b7325c24);
WALTf0f82ef4d0[WALT8f9ab72eb9].nr=(int)div64_u64((WALT42db3f0aea+WALTcc368a061f)
,(0x3af+7570-0x20dd));WALTf0f82ef4d0[WALT8f9ab72eb9].nr_misfit=(int)div64_u64((
WALT346aee5ac3+WALTcc368a061f),(0xc01+4754-0x1e2f));WALTf0f82ef4d0[
WALT8f9ab72eb9].nr_max=per_cpu(nr_max,WALT8f9ab72eb9);WALTf0f82ef4d0[
WALT8f9ab72eb9].nr_scaled=WALT42db3f0aea;trace_sched_get_nr_running_avg(
WALT8f9ab72eb9,WALTf0f82ef4d0[WALT8f9ab72eb9].nr,WALTf0f82ef4d0[WALT8f9ab72eb9].
nr_misfit,WALTf0f82ef4d0[WALT8f9ab72eb9].nr_max,WALTf0f82ef4d0[WALT8f9ab72eb9].
nr_scaled);per_cpu(WALTde16cdc0f2,WALT8f9ab72eb9)=WALT3822d537f6;per_cpu(
WALT5c03c65a13,WALT8f9ab72eb9)=(0x174d+2221-0x1ffa);per_cpu(WALT95bc2af379,
WALT8f9ab72eb9)=(0x69f+6598-0x2065);per_cpu(nr_max,WALT8f9ab72eb9)=per_cpu(nr,
WALT8f9ab72eb9);spin_unlock_irqrestore(&per_cpu(WALTe6ee2b56c7,WALT8f9ab72eb9),
WALT05b7c9a580);}for_each_possible_cpu(WALT8f9ab72eb9){if(per_cpu(WALT701fb8f8ec
,WALT8f9ab72eb9)){WALT6f04dcfcbc=true;break;}}if(WALT6f04dcfcbc&&
get_rtgb_active_time()>=WALT74fd8dfb0d)sched_update_hyst_times();WALTd1b16ed698=
WALT3822d537f6;}EXPORT_SYMBOL(sched_get_nr_running_avg);void 
sched_update_hyst_times(void){u64 WALT86ea06dbda,WALTc11d8dcd20;bool 
WALTe5f9c419f8;int WALT8f9ab72eb9;WALTe5f9c419f8=is_rtgb_active()&&(sched_boost(
)!=CONSERVATIVE_BOOST)&&(get_rtgb_active_time()<WALT74fd8dfb0d);
for_each_possible_cpu(WALT8f9ab72eb9){WALT86ea06dbda=(BIT(WALT8f9ab72eb9)&
sysctl_sched_busy_hyst_enable_cpus)?sysctl_sched_busy_hyst:(0x4ea+1637-0xb4f);
WALTc11d8dcd20=((BIT(WALT8f9ab72eb9)&sysctl_sched_coloc_busy_hyst_enable_cpus)&&
WALTe5f9c419f8)?sysctl_sched_coloc_busy_hyst:(0x12f0+997-0x16d5);per_cpu(
WALT701fb8f8ec,WALT8f9ab72eb9)=max(WALT86ea06dbda,WALTc11d8dcd20);}}
#define WALT8dd50955b9		(0x1240+4254-0x22db)
#define WALTed8d29ed55	(0x639+4705-0x1890)
static inline void WALTecd7b5dadc(int WALT8f9ab72eb9,bool WALTea3d214cf5,
unsigned long WALTa70cd3cf53,u64 WALT3822d537f6){bool WALT164d00420c=false,
WALTb616236140=false;if(!per_cpu(WALT701fb8f8ec,WALT8f9ab72eb9))return;if(
WALTa70cd3cf53>=WALT8dd50955b9&&per_cpu(nr,WALT8f9ab72eb9)<WALT8dd50955b9)
WALT164d00420c=true;if(WALTea3d214cf5&&(cpu_util(WALT8f9ab72eb9)*WALTed8d29ed55)
>capacity_orig_of(WALT8f9ab72eb9))WALTb616236140=true;if(WALT164d00420c||
WALTb616236140)atomic64_set(&per_cpu(WALT739b44b3f3,WALT8f9ab72eb9),
WALT3822d537f6+per_cpu(WALT701fb8f8ec,WALT8f9ab72eb9));}void 
sched_update_nr_prod(int WALT8f9ab72eb9,long WALT17abc14e87,bool WALTef3ecb031d)
{u64 WALT1f1d98d140;u64 WALT3822d537f6;unsigned long WALT05b7c9a580,
WALT8a91c84c00;spin_lock_irqsave(&per_cpu(WALTe6ee2b56c7,WALT8f9ab72eb9),
WALT05b7c9a580);WALT8a91c84c00=per_cpu(nr,WALT8f9ab72eb9);WALT3822d537f6=
sched_clock();WALT1f1d98d140=WALT3822d537f6-per_cpu(WALTde16cdc0f2,
WALT8f9ab72eb9);BUG_ON((s64)WALT1f1d98d140<(0x628+725-0x8fd));per_cpu(
WALTde16cdc0f2,WALT8f9ab72eb9)=WALT3822d537f6;per_cpu(nr,WALT8f9ab72eb9)=
WALT8a91c84c00+(WALTef3ecb031d?WALT17abc14e87:-WALT17abc14e87);BUG_ON((s64)
per_cpu(nr,WALT8f9ab72eb9)<(0xa41+7297-0x26c2));if(per_cpu(nr,WALT8f9ab72eb9)>
per_cpu(nr_max,WALT8f9ab72eb9))per_cpu(nr_max,WALT8f9ab72eb9)=per_cpu(nr,
WALT8f9ab72eb9);WALTecd7b5dadc(WALT8f9ab72eb9,!WALTef3ecb031d,WALT8a91c84c00,
WALT3822d537f6);per_cpu(WALT5c03c65a13,WALT8f9ab72eb9)+=WALT8a91c84c00*
WALT1f1d98d140;per_cpu(WALT95bc2af379,WALT8f9ab72eb9)+=walt_big_tasks(
WALT8f9ab72eb9)*WALT1f1d98d140;spin_unlock_irqrestore(&per_cpu(WALTe6ee2b56c7,
WALT8f9ab72eb9),WALT05b7c9a580);}EXPORT_SYMBOL(sched_update_nr_prod);unsigned 
int sched_get_cpu_util(int WALT8f9ab72eb9){struct rq*rq=cpu_rq(WALT8f9ab72eb9);
u64 WALTb0b0149580;unsigned long WALTfbbdeffe9c,WALT05b7c9a580;unsigned int 
WALT517f9bdd84;raw_spin_lock_irqsave(&rq->lock,WALT05b7c9a580);WALTb0b0149580=rq
->cfs.avg.util_avg;WALTfbbdeffe9c=capacity_orig_of(WALT8f9ab72eb9);
WALTb0b0149580=rq->prev_runnable_sum+rq->grp_time.prev_runnable_sum;
WALTb0b0149580=div64_u64(WALTb0b0149580,sched_ravg_window>>SCHED_CAPACITY_SHIFT)
;raw_spin_unlock_irqrestore(&rq->lock,WALT05b7c9a580);WALTb0b0149580=(
WALTb0b0149580>=WALTfbbdeffe9c)?WALTfbbdeffe9c:WALTb0b0149580;WALT517f9bdd84=
div64_ul((WALTb0b0149580*(0x1601+4151-0x25d4)),WALTfbbdeffe9c);return 
WALT517f9bdd84;}u64 sched_lpm_disallowed_time(int WALT8f9ab72eb9){u64 
WALT2c53bb3f34=sched_clock();u64 WALT09c73f1899=atomic64_read(&per_cpu(
WALT739b44b3f3,WALT8f9ab72eb9));if(WALT2c53bb3f34<WALT09c73f1899)return 
WALT09c73f1899-WALT2c53bb3f34;return(0x4ac+3579-0x12a7);}
