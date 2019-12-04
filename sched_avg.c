// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
 */

#include <linux/module.h>
#include <linux/percpu.h>
#include <linux/hrtimer.h>
#include <linux/sched.h>
#include <linux/math64.h>
#include "walt.h"
#include <trace/events/sched.h>
static DEFINE_PER_CPU(u64,z5c03c65a13);static DEFINE_PER_CPU(u64,zde16cdc0f2);
static DEFINE_PER_CPU(u64,z95bc2af379);static DEFINE_PER_CPU(u64,nr);static 
DEFINE_PER_CPU(u64,nr_max);static DEFINE_PER_CPU(spinlock_t,ze6ee2b56c7)=
__SPIN_LOCK_UNLOCKED(ze6ee2b56c7);static s64 zd1b16ed698;unsigned int 
sysctl_sched_busy_hyst_enable_cpus;unsigned int sysctl_sched_busy_hyst;unsigned 
int sysctl_sched_coloc_busy_hyst_enable_cpus=(0xdd+5972-0x17c1);unsigned int 
sysctl_sched_coloc_busy_hyst=39000000;unsigned int 
sysctl_sched_coloc_busy_hyst_max_ms=(0x17d9+4727-0x16c8);static DEFINE_PER_CPU(
atomic64_t,z739b44b3f3)=ATOMIC64_INIT((0x15b8+2703-0x2047));static 
DEFINE_PER_CPU(u64,z701fb8f8ec);
#define zcc368a061f		(0x1ba+1172-0x63f)
#define z74fd8dfb0d (sysctl_sched_coloc_busy_hyst_max_ms * NSEC_PER_MSEC)
void sched_get_nr_running_avg(struct sched_avg_stats*zf0f82ef4d0){int 
z8f9ab72eb9;u64 z3822d537f6=sched_clock();u64 z65b7325c24=z3822d537f6-
zd1b16ed698;u64 z42db3f0aea,z346aee5ac3;bool z6f04dcfcbc=false;if(!z65b7325c24)
return;for_each_possible_cpu(z8f9ab72eb9){unsigned long z05b7c9a580;u64 
z1f1d98d140;spin_lock_irqsave(&per_cpu(ze6ee2b56c7,z8f9ab72eb9),z05b7c9a580);
z3822d537f6=sched_clock();z1f1d98d140=z3822d537f6-per_cpu(zde16cdc0f2,
z8f9ab72eb9);BUG_ON((s64)z1f1d98d140<(0x556+8286-0x25b4));z42db3f0aea=per_cpu(
z5c03c65a13,z8f9ab72eb9);z42db3f0aea+=per_cpu(nr,z8f9ab72eb9)*z1f1d98d140;
z42db3f0aea=div64_u64((z42db3f0aea*(0x870+6390-0x2102)),z65b7325c24);z346aee5ac3
=per_cpu(z95bc2af379,z8f9ab72eb9);z346aee5ac3+=walt_big_tasks(z8f9ab72eb9)*
z1f1d98d140;z346aee5ac3=div64_u64((z346aee5ac3*(0x1675+1869-0x1d5e)),z65b7325c24
);zf0f82ef4d0[z8f9ab72eb9].nr=(int)div64_u64((z42db3f0aea+zcc368a061f),
(0x13db+2649-0x1dd0));zf0f82ef4d0[z8f9ab72eb9].nr_misfit=(int)div64_u64((
z346aee5ac3+zcc368a061f),(0x5f4+4705-0x17f1));zf0f82ef4d0[z8f9ab72eb9].nr_max=
per_cpu(nr_max,z8f9ab72eb9);zf0f82ef4d0[z8f9ab72eb9].nr_scaled=z42db3f0aea;
trace_sched_get_nr_running_avg(z8f9ab72eb9,zf0f82ef4d0[z8f9ab72eb9].nr,
zf0f82ef4d0[z8f9ab72eb9].nr_misfit,zf0f82ef4d0[z8f9ab72eb9].nr_max,zf0f82ef4d0[
z8f9ab72eb9].nr_scaled);per_cpu(zde16cdc0f2,z8f9ab72eb9)=z3822d537f6;per_cpu(
z5c03c65a13,z8f9ab72eb9)=(0xfa+6502-0x1a60);per_cpu(z95bc2af379,z8f9ab72eb9)=
(0x14b8+3212-0x2144);per_cpu(nr_max,z8f9ab72eb9)=per_cpu(nr,z8f9ab72eb9);
spin_unlock_irqrestore(&per_cpu(ze6ee2b56c7,z8f9ab72eb9),z05b7c9a580);}
for_each_possible_cpu(z8f9ab72eb9){if(per_cpu(z701fb8f8ec,z8f9ab72eb9)){
z6f04dcfcbc=true;break;}}if(z6f04dcfcbc&&get_rtgb_active_time()>=z74fd8dfb0d)
sched_update_hyst_times();zd1b16ed698=z3822d537f6;}EXPORT_SYMBOL(
sched_get_nr_running_avg);void sched_update_hyst_times(void){u64 z86ea06dbda,
zc11d8dcd20;bool ze5f9c419f8;int z8f9ab72eb9;ze5f9c419f8=is_rtgb_active()&&(
sched_boost()!=CONSERVATIVE_BOOST)&&(get_rtgb_active_time()<z74fd8dfb0d);
for_each_possible_cpu(z8f9ab72eb9){z86ea06dbda=(BIT(z8f9ab72eb9)&
sysctl_sched_busy_hyst_enable_cpus)?sysctl_sched_busy_hyst:(0x1ddd+171-0x1e88);
zc11d8dcd20=((BIT(z8f9ab72eb9)&sysctl_sched_coloc_busy_hyst_enable_cpus)&&
ze5f9c419f8)?sysctl_sched_coloc_busy_hyst:(0x18dc+2587-0x22f7);per_cpu(
z701fb8f8ec,z8f9ab72eb9)=max(z86ea06dbda,zc11d8dcd20);}}
#define z8dd50955b9		(0x5a3+5785-0x1c39)
#define zed8d29ed55	(0x2d4+965-0x68f)
static inline void zecd7b5dadc(int z8f9ab72eb9,bool zea3d214cf5,unsigned long 
za70cd3cf53,u64 z3822d537f6){bool z164d00420c=false,zb616236140=false;if(!
per_cpu(z701fb8f8ec,z8f9ab72eb9))return;if(za70cd3cf53>=z8dd50955b9&&per_cpu(nr,
z8f9ab72eb9)<z8dd50955b9)z164d00420c=true;if(zea3d214cf5&&(cpu_util(z8f9ab72eb9)
*zed8d29ed55)>capacity_orig_of(z8f9ab72eb9))zb616236140=true;if(z164d00420c||
zb616236140)atomic64_set(&per_cpu(z739b44b3f3,z8f9ab72eb9),z3822d537f6+per_cpu(
z701fb8f8ec,z8f9ab72eb9));}void sched_update_nr_prod(int z8f9ab72eb9,long 
z17abc14e87,bool zef3ecb031d){u64 z1f1d98d140;u64 z3822d537f6;unsigned long 
z05b7c9a580,z8a91c84c00;spin_lock_irqsave(&per_cpu(ze6ee2b56c7,z8f9ab72eb9),
z05b7c9a580);z8a91c84c00=per_cpu(nr,z8f9ab72eb9);z3822d537f6=sched_clock();
z1f1d98d140=z3822d537f6-per_cpu(zde16cdc0f2,z8f9ab72eb9);BUG_ON((s64)z1f1d98d140
<(0x1748+3991-0x26df));per_cpu(zde16cdc0f2,z8f9ab72eb9)=z3822d537f6;per_cpu(nr,
z8f9ab72eb9)=z8a91c84c00+(zef3ecb031d?z17abc14e87:-z17abc14e87);BUG_ON((s64)
per_cpu(nr,z8f9ab72eb9)<(0xf54+2700-0x19e0));if(per_cpu(nr,z8f9ab72eb9)>per_cpu(
nr_max,z8f9ab72eb9))per_cpu(nr_max,z8f9ab72eb9)=per_cpu(nr,z8f9ab72eb9);
zecd7b5dadc(z8f9ab72eb9,!zef3ecb031d,z8a91c84c00,z3822d537f6);per_cpu(
z5c03c65a13,z8f9ab72eb9)+=z8a91c84c00*z1f1d98d140;per_cpu(z95bc2af379,
z8f9ab72eb9)+=walt_big_tasks(z8f9ab72eb9)*z1f1d98d140;spin_unlock_irqrestore(&
per_cpu(ze6ee2b56c7,z8f9ab72eb9),z05b7c9a580);}EXPORT_SYMBOL(
sched_update_nr_prod);unsigned int sched_get_cpu_util(int z8f9ab72eb9){struct rq
*rq=cpu_rq(z8f9ab72eb9);u64 zb0b0149580;unsigned long zfbbdeffe9c,z05b7c9a580;
unsigned int z517f9bdd84;raw_spin_lock_irqsave(&rq->lock,z05b7c9a580);
zb0b0149580=rq->cfs.avg.util_avg;zfbbdeffe9c=capacity_orig_of(z8f9ab72eb9);
zb0b0149580=rq->prev_runnable_sum+rq->grp_time.prev_runnable_sum;zb0b0149580=
div64_u64(zb0b0149580,sched_ravg_window>>SCHED_CAPACITY_SHIFT);
raw_spin_unlock_irqrestore(&rq->lock,z05b7c9a580);zb0b0149580=(zb0b0149580>=
zfbbdeffe9c)?zfbbdeffe9c:zb0b0149580;z517f9bdd84=div64_ul((zb0b0149580*
(0x1dc1+2278-0x2643)),zfbbdeffe9c);return z517f9bdd84;}u64 zf13fe5ef8d(int 
z8f9ab72eb9){u64 z2c53bb3f34=sched_clock();u64 z09c73f1899=atomic64_read(&
per_cpu(z739b44b3f3,z8f9ab72eb9));if(z2c53bb3f34<z09c73f1899)return z09c73f1899-
z2c53bb3f34;return(0x1dac+644-0x2030);}
