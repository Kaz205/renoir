// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#include <linux/syscore_ops.h>
#include <linux/cpufreq.h>
#include <linux/list_sort.h>
#include <linux/jiffies.h>
#include <linux/sched/stat.h>
#include <trace/events/sched.h>
#include "walt.h"
#include <trace/events/sched.h>
const char*task_event_names[]={
"\x50\x55\x54\x5f\x50\x52\x45\x56\x5f\x54\x41\x53\x4b",
"\x50\x49\x43\x4b\x5f\x4e\x45\x58\x54\x5f\x54\x41\x53\x4b",
"\x54\x41\x53\x4b\x5f\x57\x41\x4b\x45",
"\x54\x41\x53\x4b\x5f\x4d\x49\x47\x52\x41\x54\x45",
"\x54\x41\x53\x4b\x5f\x55\x50\x44\x41\x54\x45",
"\x49\x52\x51\x5f\x55\x50\x44\x41\x54\x45"};const char*migrate_type_names[]={
"\x47\x52\x4f\x55\x50\x5f\x54\x4f\x5f\x52\x51",
"\x52\x51\x5f\x54\x4f\x5f\x47\x52\x4f\x55\x50",
"\x52\x51\x5f\x54\x4f\x5f\x52\x51",
"\x47\x52\x4f\x55\x50\x5f\x54\x4f\x5f\x47\x52\x4f\x55\x50"};
#define z88b9b0b9ce (0xda1+5861-0x2486)
#define z19b86f3ee0 (0x783+5661-0x1d9f)
#define z53b6c10420 9500000
#define MAX_NUM_CGROUP_COLOC_ID (0x1866+3714-0x26d4)
#define WINDOW_STATS_RECENT		(0x4f7+6734-0x1f45)
#define WINDOW_STATS_MAX		(0x515+8015-0x2463)
#define WINDOW_STATS_MAX_RECENT_AVG	(0x190d+3437-0x2678)
#define WINDOW_STATS_AVG		(0x1d3+5532-0x176c)
#define WINDOW_STATS_INVALID_POLICY	(0xd3+5689-0x1708)
#define MAX_NR_CLUSTERS			(0x740+794-0xa57)
#define FREQ_REPORT_MAX_CPU_LOAD_TOP_TASK	(0x1695+1862-0x1ddb)
#define FREQ_REPORT_CPU_LOAD			(0x1850+2559-0x224e)
#define FREQ_REPORT_TOP_TASK			(0x596+4203-0x15ff)
#define zdbeb076c45 100000000
static ktime_t z482beda45b;static bool z42c0a8ecd1;static struct 
cpu_cycle_counter_cb cpu_cycle_counter_cb;static bool z3b880410aa;static 
DEFINE_MUTEX(z6e47d2c346);static atomic64_t z8d508f7c3b;static u64 
walt_load_reported_window;static struct irq_work z5bb9cd73e7;static struct 
irq_work z72f8d06752;u64 sched_ktime_clock(void){if(unlikely(z42c0a8ecd1))return
 ktime_to_ns(z482beda45b);return ktime_get_ns();}static void zfb3bba3e8e(void){
z42c0a8ecd1=false;}static int z588a01c1cd(void){z482beda45b=ktime_get();
z42c0a8ecd1=true;return(0x606+6121-0x1def);}static struct syscore_ops 
z3c69fe9894={.resume=zfb3bba3e8e,.suspend=z588a01c1cd};static int __init 
z5a716155ff(void){register_syscore_ops(&z3c69fe9894);return(0x780+644-0xa04);}
late_initcall(z5a716155ff);static void z04b55e82dd(const cpumask_t*cpus,unsigned
 long*flags){int cpu;int z8025f196c5=(0xecc+5597-0x24a9);local_irq_save(*flags);
for_each_cpu(cpu,cpus){if(z8025f196c5==(0x8d2+6092-0x209e))raw_spin_lock(&cpu_rq
(cpu)->lock);else raw_spin_lock_nested(&cpu_rq(cpu)->lock,z8025f196c5);
z8025f196c5++;}}static void zbe61fad8ce(const cpumask_t*cpus,unsigned long*flags
){int cpu;for_each_cpu(cpu,cpus)raw_spin_unlock(&cpu_rq(cpu)->lock);
local_irq_restore(*flags);}
#ifdef CONFIG_HZ_300
#define zd5df7640b9 (3333333 * (0x10e0+2082-0x18fc))
#else
#define zd5df7640b9 20000000
#endif
#define zffe0d3899f 1000000000
#define z5656b853de (NSEC_PER_SEC / zd5df7640b9)
unsigned int sysctl_sched_capacity_margin_up[MAX_MARGIN_LEVELS]={[
(0x542+5502-0x1ac0)...MAX_MARGIN_LEVELS-(0x2176+536-0x238d)]=(0x1551+833-0x145c)
};unsigned int sysctl_sched_capacity_margin_down[MAX_MARGIN_LEVELS]={[
(0xa24+6254-0x2292)...MAX_MARGIN_LEVELS-(0x11e4+3090-0x1df5)]=
(0x1418+5955-0x26a6)};__read_mostly unsigned int sysctl_sched_cpu_high_irqload=
TICK_NSEC;unsigned int sysctl_sched_walt_rotate_big_tasks;unsigned int 
walt_rotation_enabled;__read_mostly unsigned int 
sysctl_sched_asym_cap_sibling_freq_match_pct=(0x561+4391-0x1624);__read_mostly 
unsigned int za591b9e54c=(0xbfa+628-0xe69);static __read_mostly unsigned int 
zdedb054041=(0x557+268-0x662);__read_mostly unsigned int 
sysctl_sched_window_stats_policy=WINDOW_STATS_MAX_RECENT_AVG;unsigned int 
sysctl_sched_ravg_window_nr_ticks=(HZ/z5656b853de);static unsigned int 
zb67de743f5=(HZ/z5656b853de);unsigned int 
sysctl_sched_dynamic_ravg_window_enable=(HZ==(0x90b+4505-0x19aa));__read_mostly 
unsigned int sched_ravg_window=zd5df7640b9;__read_mostly unsigned int 
z95efc1452f=zd5df7640b9;static DEFINE_SPINLOCK(z19d7dae9b5);u64 zc6e1c5745d;
static __read_mostly unsigned int walt_cpu_util_freq_divisor;unsigned int 
__read_mostly sched_init_task_load_windows;unsigned int __read_mostly 
zb0bc76dcf5;unsigned int __read_mostly z8bf7fc10da=(0x1c35+102-0x1c8c);unsigned 
int max_possible_freq=(0x5eb+5421-0x1b17);unsigned int min_max_freq=
(0x428+5600-0x1a07);unsigned int max_possible_capacity=(0x192d+3766-0x23e3);
unsigned int min_max_possible_capacity=(0x11a4+2467-0x1747);unsigned int 
__read_mostly sched_disable_window_stats;__read_mostly unsigned int 
sched_load_granule=zd5df7640b9/NUM_LOAD_INDICES;static const unsigned int 
z64333e9737=BITS_TO_LONGS(NUM_LOAD_INDICES+(0x2071+1354-0x25ba))*sizeof(unsigned
 long);__read_mostly unsigned int zed0bb72c67;static int __init z365d6e8b5b(char
*zcf96530e6c){unsigned int z4ae816ebd1;get_option(&zcf96530e6c,&z4ae816ebd1);if(
z4ae816ebd1<zd5df7640b9||z4ae816ebd1>zffe0d3899f){WARN_ON((0x43f+3153-0x108f));
return-EINVAL;}sched_ravg_window=z4ae816ebd1;return(0x13ec+550-0x1612);}
early_param(
"\x73\x63\x68\x65\x64\x5f\x72\x61\x76\x67\x5f\x77\x69\x6e\x64\x6f\x77",
z365d6e8b5b);static int __init z8c5c1ddf5d(char*zcf96530e6c){unsigned int 
z23b9d3f649;get_option(&zcf96530e6c,&z23b9d3f649);sched_predl=!!z23b9d3f649;
return(0xc27+4011-0x1bd2);}early_param(
"\x73\x63\x68\x65\x64\x5f\x70\x72\x65\x64\x6c",z8c5c1ddf5d);__read_mostly 
unsigned int zd07944bdc3;
#define zecf40170d4(z68a26cf33f) ((z68a26cf33f)/zd07944bdc3)
#define z33b027c8ca(z0dfd61a6cb)        printk_deferred(\
"\x25\x73\x3d\x25\x6c\x6c\x75", #z0dfd61a6cb, z0dfd61a6cb)
#define z19f3dd399d(z0dfd61a6cb)               #z0dfd61a6cb
static inline void z1efe882752(struct task_struct*z0609dbaf9d){char zb49c1cb1d4[
NR_CPUS*(0x7f9+6573-0x2196)];int z5d971be8b8,z2dc758aa44=(0x3dc+4052-0x13b0);int
 z8c35dbc183=NR_CPUS*(0x11a0+520-0x1398);z33b027c8ca(z0609dbaf9d->pid);
z33b027c8ca(z0609dbaf9d->ravg.mark_start);z33b027c8ca(z0609dbaf9d->ravg.demand);
z33b027c8ca(z0609dbaf9d->ravg.coloc_demand);z33b027c8ca(sched_ravg_window);
z33b027c8ca(z95efc1452f);for(z5d971be8b8=(0x55a+8567-0x26d1);z5d971be8b8<
nr_cpu_ids;z5d971be8b8++)z2dc758aa44+=scnprintf(zb49c1cb1d4+z2dc758aa44,
z8c35dbc183-z2dc758aa44,"\x25\x75\x20",z0609dbaf9d->ravg.curr_window_cpu[
z5d971be8b8]);printk_deferred("\x25\x73\x3d\x25\x64\x20\x28\x25\x73\x29" "\n",
z19f3dd399d(z0609dbaf9d->ravg.curr_window),z0609dbaf9d->ravg.curr_window,
zb49c1cb1d4);for(z5d971be8b8=(0x795+7460-0x24b9),z2dc758aa44=(0xb4f+4803-0x1e12)
;z5d971be8b8<nr_cpu_ids;z5d971be8b8++)z2dc758aa44+=scnprintf(zb49c1cb1d4+
z2dc758aa44,z8c35dbc183-z2dc758aa44,"\x25\x75\x20",z0609dbaf9d->ravg.
prev_window_cpu[z5d971be8b8]);printk_deferred(
"\x25\x73\x3d\x25\x64\x20\x28\x25\x73\x29" "\n",z19f3dd399d(z0609dbaf9d->ravg.
prev_window),z0609dbaf9d->ravg.prev_window,zb49c1cb1d4);z33b027c8ca(z0609dbaf9d
->last_wake_ts);z33b027c8ca(z0609dbaf9d->last_enqueued_ts);z33b027c8ca(
z0609dbaf9d->misfit);z33b027c8ca(z0609dbaf9d->unfilter);}static inline void 
zbe464df6bf(int cpu){struct rq*rq=cpu_rq(cpu);struct task_struct*zca60978f56=
cpu_curr(cpu);int z5d971be8b8;printk_deferred(
"\x43\x50\x55\x3a\x25\x64\x20\x6e\x72\x5f\x72\x75\x6e\x6e\x69\x6e\x67\x3a\x25\x75\x20\x63\x75\x72\x72\x65\x6e\x74\x3a\x20\x25\x64\x20\x28\x25\x73\x29" "\n"
,cpu,rq->nr_running,zca60978f56->pid,zca60978f56->comm);printk_deferred(
"\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d"
);z33b027c8ca(rq->window_start);z33b027c8ca(rq->prev_window_size);z33b027c8ca(rq
->curr_runnable_sum);z33b027c8ca(rq->prev_runnable_sum);z33b027c8ca(rq->
nt_curr_runnable_sum);z33b027c8ca(rq->nt_prev_runnable_sum);z33b027c8ca(rq->
cum_window_demand_scaled);z33b027c8ca(rq->task_exec_scale);z33b027c8ca(rq->
grp_time.curr_runnable_sum);z33b027c8ca(rq->grp_time.prev_runnable_sum);
z33b027c8ca(rq->grp_time.nt_curr_runnable_sum);z33b027c8ca(rq->grp_time.
nt_prev_runnable_sum);for(z5d971be8b8=(0xb1f+704-0xddf);z5d971be8b8<
NUM_TRACKED_WINDOWS;z5d971be8b8++){printk_deferred(
"\x72\x71\x2d\x3e\x6c\x6f\x61\x64\x5f\x73\x75\x62\x73\x5b\x25\x64\x5d\x2e\x77\x69\x6e\x64\x6f\x77\x5f\x73\x74\x61\x72\x74\x3d\x25\x6c\x6c\x75\x29" "\n"
,z5d971be8b8,rq->load_subs[z5d971be8b8].window_start);printk_deferred(
"\x72\x71\x2d\x3e\x6c\x6f\x61\x64\x5f\x73\x75\x62\x73\x5b\x25\x64\x5d\x2e\x73\x75\x62\x73\x3d\x25\x6c\x6c\x75\x29" "\n"
,z5d971be8b8,rq->load_subs[z5d971be8b8].subs);printk_deferred(
"\x72\x71\x2d\x3e\x6c\x6f\x61\x64\x5f\x73\x75\x62\x73\x5b\x25\x64\x5d\x2e\x6e\x65\x77\x5f\x73\x75\x62\x73\x3d\x25\x6c\x6c\x75\x29" "\n"
,z5d971be8b8,rq->load_subs[z5d971be8b8].new_subs);}z1efe882752(zca60978f56);
z33b027c8ca(sched_capacity_margin_up[cpu]);z33b027c8ca(
sched_capacity_margin_down[cpu]);}static inline void z71e92e3d78(void){int cpu;
printk_deferred(
"\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x20\x57\x41\x4c\x54\x20\x52\x51\x20\x44\x55\x4d\x50\x20\x53\x54\x41\x52\x54\x20\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d" "\n"
);printk_deferred(
"\x53\x63\x68\x65\x64\x20\x6b\x74\x69\x6d\x65\x5f\x67\x65\x74\x3a\x20\x25\x6c\x6c\x75" "\n"
,sched_ktime_clock());printk_deferred(
"\x54\x69\x6d\x65\x20\x6c\x61\x73\x74\x20\x77\x69\x6e\x64\x6f\x77\x20\x63\x68\x61\x6e\x67\x65\x64\x3d\x25\x6c\x75" "\n"
,zc6e1c5745d);for_each_online_cpu(cpu)zbe464df6bf(cpu);z33b027c8ca(
max_possible_capacity);z33b027c8ca(min_max_possible_capacity);printk_deferred(
"\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x20\x57\x41\x4c\x54\x20\x52\x51\x20\x44\x55\x4d\x50\x20\x45\x4e\x44\x20\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d" "\n"
);}static int z22b60684f8;
#define z609fba09ac(z8f713ea8e0)				\
({							\
	if (unlikely(!!(z8f713ea8e0)) && !z22b60684f8) {	\
		z22b60684f8 = (0x1a2b+2103-0x2261);			\
		z71e92e3d78();				\
		BUG_ON(z8f713ea8e0);			\
	}						\
})
void inc_rq_walt_stats(struct rq*rq,struct task_struct*z0609dbaf9d){
inc_nr_big_task(&rq->walt_stats,z0609dbaf9d);walt_inc_cumulative_runnable_avg(rq
,z0609dbaf9d);}void dec_rq_walt_stats(struct rq*rq,struct task_struct*
z0609dbaf9d){dec_nr_big_task(&rq->walt_stats,z0609dbaf9d);
walt_dec_cumulative_runnable_avg(rq,z0609dbaf9d);}void 
fixup_walt_sched_stats_common(struct rq*rq,struct task_struct*z0609dbaf9d,u16 
z8143bfdfea,u16 z77a2404d60){s64 zad18716537=(s64)z8143bfdfea-z0609dbaf9d->ravg.
demand_scaled;s64 z5ae7e7adb9=(s64)z77a2404d60-z0609dbaf9d->ravg.
pred_demand_scaled;fixup_cumulative_runnable_avg(&rq->walt_stats,zad18716537,
z5ae7e7adb9);walt_fixup_cum_window_demand(rq,zad18716537);}__read_mostly bool 
sched_freq_aggr_en;static u64 z6bdc3765bb(struct rq*rq,u64 z790680e4aa,int 
z3205babe24){s64 z17abc14e87;int z09570395b5;u64 z901ba13dc5=rq->window_start;
z17abc14e87=z790680e4aa-rq->window_start;if(z17abc14e87<(0xcc2+3859-0x1bd5)){
printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x43\x50\x55\x25\x64\x3b\x20\x77\x61\x6c\x6c\x63\x6c\x6f\x63\x6b\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x77\x69\x6e\x64\x6f\x77\x5f\x73\x74\x61\x72\x74\x3d\x25\x6c\x6c\x75"
,rq->cpu,z790680e4aa,rq->window_start);z609fba09ac((0x1f19+345-0x2071));}if(
z17abc14e87<sched_ravg_window)return z901ba13dc5;z09570395b5=div64_u64(
z17abc14e87,sched_ravg_window);rq->window_start+=(u64)z09570395b5*(u64)
sched_ravg_window;rq->cum_window_demand_scaled=rq->walt_stats.
cumulative_runnable_avg_scaled;rq->prev_window_size=sched_ravg_window;return 
z901ba13dc5;}static inline u64 z2cd0d15eb3(int cpu,u64 z790680e4aa){struct rq*rq
=cpu_rq(cpu);if(rq->last_cc_update!=z790680e4aa){rq->cycles=cpu_cycle_counter_cb
.get_cpu_cycle_counter(cpu);rq->last_cc_update=z790680e4aa;}return rq->cycles;}
static void z1360b17c9b(struct task_struct*z0609dbaf9d,int cpu,u64 z790680e4aa){
if(z3b880410aa)z0609dbaf9d->cpu_cycles=z2cd0d15eb3(cpu,z790680e4aa);}static 
inline bool ze99faa0ca8(void){return(walt_rotation_enabled||(sched_boost_policy(
)!=SCHED_BOOST_NONE));}void clear_ed_task(struct task_struct*z0609dbaf9d,struct 
rq*rq){if(z0609dbaf9d==rq->ed_task)rq->ed_task=NULL;}static inline bool 
z30dc154c3b(struct task_struct*z0609dbaf9d,u64 z790680e4aa){return(z790680e4aa-
z0609dbaf9d->last_wake_ts>=z53b6c10420);}bool early_detection_notify(struct rq*
rq,u64 z790680e4aa){struct task_struct*z0609dbaf9d;int zd7f6dc4db2=
(0x269+4751-0x14ee);rq->ed_task=NULL;if(!ze99faa0ca8()||!rq->cfs.h_nr_running)
return(0x11e8+810-0x1512);list_for_each_entry(z0609dbaf9d,&rq->cfs_tasks,se.
group_node){if(!zd7f6dc4db2)break;if(z30dc154c3b(z0609dbaf9d,z790680e4aa)){rq->
ed_task=z0609dbaf9d;return(0x6ba+3667-0x150c);}zd7f6dc4db2--;}return
(0xb5f+5861-0x2244);}void sched_account_irqstart(int cpu,struct task_struct*curr
,u64 z790680e4aa){struct rq*rq=cpu_rq(cpu);if(!rq->window_start||
sched_disable_window_stats)return;if(is_idle_task(curr)){raw_spin_lock(&rq->lock
);z1360b17c9b(curr,cpu,sched_ktime_clock());raw_spin_unlock(&rq->lock);}}
unsigned int walt_big_tasks(int cpu){struct rq*rq=cpu_rq(cpu);return rq->
walt_stats.nr_big_tasks;}void clear_walt_request(int cpu){struct rq*rq=cpu_rq(
cpu);unsigned long flags;clear_reserved(cpu);if(rq->push_task){struct 
task_struct*push_task=NULL;raw_spin_lock_irqsave(&rq->lock,flags);if(rq->
push_task){clear_reserved(rq->push_cpu);push_task=rq->push_task;rq->push_task=
NULL;}rq->active_balance=(0x2b5+1364-0x809);raw_spin_unlock_irqrestore(&rq->lock
,flags);if(push_task)put_task_struct(push_task);}}static u32 top_task_load(
struct rq*rq){int z6b2e94bfe7=rq->prev_top;u8 prev=(0x8fb+5217-0x1d5b)-rq->
curr_table;if(!z6b2e94bfe7){int z1d278c4a11=NUM_LOAD_INDICES-(0x187+4240-0x1216)
;if(!test_bit(z1d278c4a11,rq->top_tasks_bitmap[prev]))return(0xba3+3724-0x1a2f);
else return sched_load_granule;}else if(z6b2e94bfe7==NUM_LOAD_INDICES-
(0x661+4037-0x1625)){return sched_ravg_window;}else{return(z6b2e94bfe7+
(0x12c7+3846-0x21cc))*sched_load_granule;}}unsigned int sysctl_sched_user_hint;
static unsigned long zfac0edc4a3;static bool z0bb76a2e0a(struct sched_cluster*
cluster);static inline bool z625289a60c(struct sched_cluster*cluster){if(
sched_freq_aggr_en||!sysctl_sched_user_hint||!cluster->aggr_grp_load)return 
false;return z0bb76a2e0a(cluster);}static inline u64 freq_policy_load(struct rq*
rq){unsigned int z71357e08e4=zed0bb72c67;struct sched_cluster*cluster=rq->
cluster;u64 aggr_grp_load=cluster->aggr_grp_load;u64 z514f31b9a6,z3d3b61fd9a=
(0x1612+3125-0x2247);struct task_struct*z17badca024=per_cpu(ksoftirqd,cpu_of(rq)
);if(rq->ed_task!=NULL){z514f31b9a6=sched_ravg_window;goto z02a8afcd23;}if(
sched_freq_aggr_en)z514f31b9a6=rq->prev_runnable_sum+aggr_grp_load;else 
z514f31b9a6=rq->prev_runnable_sum+rq->grp_time.prev_runnable_sum;if(z17badca024
&&z17badca024->state==TASK_RUNNING)z514f31b9a6=max_t(u64,z514f31b9a6,task_load(
z17badca024));z3d3b61fd9a=top_task_load(rq);switch(z71357e08e4){case 
FREQ_REPORT_MAX_CPU_LOAD_TOP_TASK:z514f31b9a6=max_t(u64,z514f31b9a6,z3d3b61fd9a)
;break;case FREQ_REPORT_TOP_TASK:z514f31b9a6=z3d3b61fd9a;break;case 
FREQ_REPORT_CPU_LOAD:break;default:break;}if(z625289a60c(cluster)){if(is_suh_max
())z514f31b9a6=sched_ravg_window;else z514f31b9a6=div64_u64(z514f31b9a6*
sysctl_sched_user_hint,(u64)(0x1dda+526-0x1f84));}z02a8afcd23:
trace_sched_load_to_gov(rq,aggr_grp_load,z3d3b61fd9a,sched_freq_aggr_en,
z514f31b9a6,z71357e08e4,walt_rotation_enabled,sysctl_sched_user_hint);return 
z514f31b9a6;}static bool rtgb_active;static inline unsigned long z2744a2207f(int
 cpu,struct sched_walt_cpu_load*zcb55d41e86){u64 zb0b0149580,z978a7841c5;struct 
rq*rq=cpu_rq(cpu);unsigned long capacity=capacity_orig_of(cpu);int zf4f061ddc1;
zf4f061ddc1=per_cpu(sched_load_boost,cpu);z978a7841c5=zb0b0149580=
freq_policy_load(rq);zb0b0149580=div64_u64(zb0b0149580*((0x1b47+2208-0x2383)+
zf4f061ddc1),walt_cpu_util_freq_divisor);if(zcb55d41e86){u64 nl=cpu_rq(cpu)->
nt_prev_runnable_sum+rq->grp_time.nt_prev_runnable_sum;u64 pl=rq->walt_stats.
pred_demands_sum_scaled;rq->old_busy_time=div64_u64(z978a7841c5,
sched_ravg_window>>SCHED_CAPACITY_SHIFT);rq->old_estimated_time=pl;nl=div64_u64(
nl*((0xae5+1155-0xf04)+zf4f061ddc1),walt_cpu_util_freq_divisor);zcb55d41e86->
prev_window_util=zb0b0149580;zcb55d41e86->nl=nl;zcb55d41e86->pl=pl;zcb55d41e86->
ws=walt_load_reported_window;zcb55d41e86->rtgb_active=rtgb_active;}return(
zb0b0149580>=capacity)?capacity:zb0b0149580;}
#define z1c84aa4dd0(z60feb671ba, z4e03fa2834, z8a98b5f42b)	\
			(max(z60feb671ba, mult_frac(z4e03fa2834, z8a98b5f42b, (0xbb9+2159-0x13c4))))
unsigned long cpu_util_freq_walt(int cpu,struct sched_walt_cpu_load*zcb55d41e86)
{struct sched_walt_cpu_load zd64f78c90a={(0xeaa+1780-0x159e)};unsigned long 
zb0b0149580=(0xd22+1781-0x1417),z53081359ce=(0x757+491-0x942);unsigned long 
capacity=capacity_orig_of(cpu);int z5d971be8b8,z568475e381=
sysctl_sched_asym_cap_sibling_freq_match_pct;if(!cpumask_test_cpu(cpu,&
asym_cap_sibling_cpus))return z2744a2207f(cpu,zcb55d41e86);for_each_cpu(
z5d971be8b8,&asym_cap_sibling_cpus){if(z5d971be8b8==cpu)zb0b0149580=z2744a2207f(
cpu,zcb55d41e86);else z53081359ce=z2744a2207f(z5d971be8b8,&zd64f78c90a);}if(cpu
==cpumask_last(&asym_cap_sibling_cpus))z568475e381=(0x1485+567-0x1658);
zb0b0149580=z1c84aa4dd0(zb0b0149580,z53081359ce,z568475e381);zcb55d41e86->
prev_window_util=zb0b0149580;zcb55d41e86->nl=z1c84aa4dd0(zcb55d41e86->nl,
zd64f78c90a.nl,z568475e381);zcb55d41e86->pl=z1c84aa4dd0(zcb55d41e86->pl,
zd64f78c90a.pl,z568475e381);return(zb0b0149580>=capacity)?capacity:zb0b0149580;}
static inline void za647ab699e(struct rq*rq){u64 ws=rq->window_start;u64 
z49da7a746a=ws-sched_ravg_window;struct load_subtractions*zfd921988bb=rq->
load_subs;int z5d971be8b8;for(z5d971be8b8=(0x209+111-0x278);z5d971be8b8<
NUM_TRACKED_WINDOWS;z5d971be8b8++){if(zfd921988bb[z5d971be8b8].window_start==ws)
{rq->curr_runnable_sum-=zfd921988bb[z5d971be8b8].subs;rq->nt_curr_runnable_sum-=
zfd921988bb[z5d971be8b8].new_subs;}else if(zfd921988bb[z5d971be8b8].window_start
==z49da7a746a){rq->prev_runnable_sum-=zfd921988bb[z5d971be8b8].subs;rq->
nt_prev_runnable_sum-=zfd921988bb[z5d971be8b8].new_subs;}zfd921988bb[z5d971be8b8
].subs=(0x122b+357-0x1390);zfd921988bb[z5d971be8b8].new_subs=(0xd9a+1738-0x1464)
;}z609fba09ac((s64)rq->prev_runnable_sum<(0xe19+3836-0x1d15));z609fba09ac((s64)
rq->curr_runnable_sum<(0xb16+1737-0x11df));z609fba09ac((s64)rq->
nt_prev_runnable_sum<(0x13d7+181-0x148c));z609fba09ac((s64)rq->
nt_curr_runnable_sum<(0x162b+3559-0x2412));}static inline void z06281e0b6d(
struct rq*rq,u64 ws,int z6b2e94bfe7){rq->load_subs[z6b2e94bfe7].window_start=ws;
rq->load_subs[z6b2e94bfe7].subs=(0x739+118-0x7af);rq->load_subs[z6b2e94bfe7].
new_subs=(0x644+6347-0x1f0f);}static int get_top_index(unsigned long*z75c312d1cd
,unsigned long z8ba4e33369){int z6b2e94bfe7=find_next_bit(z75c312d1cd,
NUM_LOAD_INDICES,z8ba4e33369);if(z6b2e94bfe7==NUM_LOAD_INDICES)return
(0x6e7+5565-0x1ca4);return NUM_LOAD_INDICES-(0xd1+2992-0xc80)-z6b2e94bfe7;}
static bool z433ae47377(struct rq*rq,u64 ws){int z5d971be8b8;u64 z52cf8663bf=
ULLONG_MAX;int zf9248c507e=(0x1d3f+1487-0x230e);for(z5d971be8b8=
(0xd80+4591-0x1f6f);z5d971be8b8<NUM_TRACKED_WINDOWS;z5d971be8b8++){u64 
zafddce82cf=rq->load_subs[z5d971be8b8].window_start;if(ws==zafddce82cf)return 
z5d971be8b8;if(zafddce82cf<z52cf8663bf){z52cf8663bf=zafddce82cf;zf9248c507e=
z5d971be8b8;}}z06281e0b6d(rq,ws,zf9248c507e);return zf9248c507e;}static void 
zb0531277d9(int z6b2e94bfe7,struct rq*rq,u32 z316dfbac15,bool z5eebbbffe9){rq->
load_subs[z6b2e94bfe7].subs+=z316dfbac15;if(z5eebbbffe9)rq->load_subs[
z6b2e94bfe7].new_subs+=z316dfbac15;}static inline struct sched_cluster*
cpu_cluster(int cpu){return cpu_rq(cpu)->cluster;}void z0dd808419c(struct 
task_struct*z0609dbaf9d,int cpu,u64 ws,bool z5eebbbffe9){struct sched_cluster*
cluster=cpu_cluster(cpu);struct cpumask zf48c6e4ef8=cluster->cpus;u64 
z49da7a746a=ws-sched_ravg_window;int z5d971be8b8;cpumask_clear_cpu(cpu,&
zf48c6e4ef8);raw_spin_lock(&cluster->load_lock);for_each_cpu(z5d971be8b8,&
zf48c6e4ef8){struct rq*rq=cpu_rq(z5d971be8b8);int z6b2e94bfe7;if(z0609dbaf9d->
ravg.curr_window_cpu[z5d971be8b8]){z6b2e94bfe7=z433ae47377(rq,ws);zb0531277d9(
z6b2e94bfe7,rq,z0609dbaf9d->ravg.curr_window_cpu[z5d971be8b8],z5eebbbffe9);
z0609dbaf9d->ravg.curr_window_cpu[z5d971be8b8]=(0x154b+3318-0x2241);}if(
z0609dbaf9d->ravg.prev_window_cpu[z5d971be8b8]){z6b2e94bfe7=z433ae47377(rq,
z49da7a746a);zb0531277d9(z6b2e94bfe7,rq,z0609dbaf9d->ravg.prev_window_cpu[
z5d971be8b8],z5eebbbffe9);z0609dbaf9d->ravg.prev_window_cpu[z5d971be8b8]=
(0x2112+103-0x2179);}}raw_spin_unlock(&cluster->load_lock);}static inline void 
z6aa95e2012(struct task_struct*z0609dbaf9d,int z525181d1b1,int task_cpu,bool 
z5eebbbffe9){struct rq*zeb0037895f=cpu_rq(z525181d1b1);struct rq*zd01f3eedf0=
cpu_rq(task_cpu);if(same_freq_domain(z525181d1b1,task_cpu))return;z0609dbaf9d->
ravg.curr_window_cpu[z525181d1b1]=z0609dbaf9d->ravg.curr_window;z0609dbaf9d->
ravg.prev_window_cpu[z525181d1b1]=z0609dbaf9d->ravg.prev_window;zeb0037895f->
curr_runnable_sum+=z0609dbaf9d->ravg.curr_window;zeb0037895f->prev_runnable_sum
+=z0609dbaf9d->ravg.prev_window;if(zd01f3eedf0->curr_runnable_sum<z0609dbaf9d->
ravg.curr_window_cpu[task_cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x25\x64\x20\x2d\x3e\x20\x43\x50\x55\x25\x64\x20\x73\x72\x63\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,zd01f3eedf0->cpu,zeb0037895f->cpu,zd01f3eedf0->
curr_runnable_sum,z0609dbaf9d->ravg.curr_window_cpu[task_cpu]);z1efe882752(
z0609dbaf9d);z609fba09ac((0x5fb+7238-0x2240));}zd01f3eedf0->curr_runnable_sum-=
z0609dbaf9d->ravg.curr_window_cpu[task_cpu];if(zd01f3eedf0->prev_runnable_sum<
z0609dbaf9d->ravg.prev_window_cpu[task_cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x25\x64\x20\x2d\x3e\x20\x43\x50\x55\x25\x64\x20\x73\x72\x63\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,zd01f3eedf0->cpu,zeb0037895f->cpu,zd01f3eedf0->
prev_runnable_sum,z0609dbaf9d->ravg.prev_window_cpu[task_cpu]);z1efe882752(
z0609dbaf9d);z609fba09ac((0x10e8+3134-0x1d25));}zd01f3eedf0->prev_runnable_sum-=
z0609dbaf9d->ravg.prev_window_cpu[task_cpu];if(z5eebbbffe9){zeb0037895f->
nt_curr_runnable_sum+=z0609dbaf9d->ravg.curr_window;zeb0037895f->
nt_prev_runnable_sum+=z0609dbaf9d->ravg.prev_window;if(zd01f3eedf0->
nt_curr_runnable_sum<z0609dbaf9d->ravg.curr_window_cpu[task_cpu]){
printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x25\x64\x20\x2d\x3e\x20\x43\x50\x55\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,zd01f3eedf0->cpu,zeb0037895f->cpu,zd01f3eedf0->
nt_curr_runnable_sum,z0609dbaf9d->ravg.curr_window_cpu[task_cpu]);z1efe882752(
z0609dbaf9d);z609fba09ac((0x568+8209-0x2578));}zd01f3eedf0->nt_curr_runnable_sum
-=z0609dbaf9d->ravg.curr_window_cpu[task_cpu];if(zd01f3eedf0->
nt_prev_runnable_sum<z0609dbaf9d->ravg.prev_window_cpu[task_cpu]){
printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x25\x64\x20\x2d\x3e\x20\x43\x50\x55\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,zd01f3eedf0->cpu,zeb0037895f->cpu,zd01f3eedf0->
nt_prev_runnable_sum,z0609dbaf9d->ravg.prev_window_cpu[task_cpu]);z1efe882752(
z0609dbaf9d);z609fba09ac((0xba3+1903-0x1311));}zd01f3eedf0->nt_prev_runnable_sum
-=z0609dbaf9d->ravg.prev_window_cpu[task_cpu];}z0609dbaf9d->ravg.curr_window_cpu
[task_cpu]=(0x113a+4243-0x21cd);z0609dbaf9d->ravg.prev_window_cpu[task_cpu]=
(0xfcb+5312-0x248b);z0dd808419c(z0609dbaf9d,task_cpu,zd01f3eedf0->window_start,
z5eebbbffe9);}static u32 zb7bb6f3305(u32 z514f31b9a6){u32 z6b2e94bfe7=
z514f31b9a6/sched_load_granule;return min(z6b2e94bfe7,(u32)(NUM_LOAD_INDICES-
(0xcb+7476-0x1dfe)));}static void z9be28a1f9c(struct task_struct*z0609dbaf9d,
struct rq*zd01f3eedf0,struct rq*z38ee64137f){int z6b2e94bfe7;int z722eaaf4cf;u32
 curr_window=z0609dbaf9d->ravg.curr_window;u32 prev_window=z0609dbaf9d->ravg.
prev_window;u8 z792740f2d5=zd01f3eedf0->curr_table;u8 z6f47937b7c=z38ee64137f->
curr_table;u8*z146a962968;u8*zbf29d6b684;if(curr_window){z146a962968=zd01f3eedf0
->top_tasks[z792740f2d5];zbf29d6b684=z38ee64137f->top_tasks[z6f47937b7c];
z6b2e94bfe7=zb7bb6f3305(curr_window);z146a962968[z6b2e94bfe7]-=
(0x14fa+239-0x15e8);zbf29d6b684[z6b2e94bfe7]+=(0xb8c+6009-0x2304);if(!
z146a962968[z6b2e94bfe7])__clear_bit(NUM_LOAD_INDICES-z6b2e94bfe7-
(0x1ea9+891-0x2223),zd01f3eedf0->top_tasks_bitmap[z792740f2d5]);if(zbf29d6b684[
z6b2e94bfe7]==(0xfb0+2948-0x1b33))__set_bit(NUM_LOAD_INDICES-z6b2e94bfe7-
(0xda2+3878-0x1cc7),z38ee64137f->top_tasks_bitmap[z6f47937b7c]);if(z6b2e94bfe7>
z38ee64137f->curr_top)z38ee64137f->curr_top=z6b2e94bfe7;z722eaaf4cf=zd01f3eedf0
->curr_top;if(z6b2e94bfe7==z722eaaf4cf&&!z146a962968[z6b2e94bfe7])zd01f3eedf0->
curr_top=get_top_index(zd01f3eedf0->top_tasks_bitmap[z792740f2d5],z722eaaf4cf);}
if(prev_window){z792740f2d5=(0xd85+3955-0x1cf7)-z792740f2d5;z6f47937b7c=
(0x3c8+5192-0x180f)-z6f47937b7c;z146a962968=zd01f3eedf0->top_tasks[z792740f2d5];
zbf29d6b684=z38ee64137f->top_tasks[z6f47937b7c];z6b2e94bfe7=zb7bb6f3305(
prev_window);z146a962968[z6b2e94bfe7]-=(0x1122+3996-0x20bd);zbf29d6b684[
z6b2e94bfe7]+=(0xdf0+2839-0x1906);if(!z146a962968[z6b2e94bfe7])__clear_bit(
NUM_LOAD_INDICES-z6b2e94bfe7-(0x237+5721-0x188f),zd01f3eedf0->top_tasks_bitmap[
z792740f2d5]);if(zbf29d6b684[z6b2e94bfe7]==(0x687+1365-0xbdb))__set_bit(
NUM_LOAD_INDICES-z6b2e94bfe7-(0x41f+8636-0x25da),z38ee64137f->top_tasks_bitmap[
z6f47937b7c]);if(z6b2e94bfe7>z38ee64137f->prev_top)z38ee64137f->prev_top=
z6b2e94bfe7;z722eaaf4cf=zd01f3eedf0->prev_top;if(z6b2e94bfe7==z722eaaf4cf&&!
z146a962968[z6b2e94bfe7])zd01f3eedf0->prev_top=get_top_index(zd01f3eedf0->
top_tasks_bitmap[z792740f2d5],z722eaaf4cf);}}static inline bool is_new_task(
struct task_struct*z0609dbaf9d){return z0609dbaf9d->ravg.active_time<zdbeb076c45
;}void fixup_busy_time(struct task_struct*z0609dbaf9d,int z525181d1b1){struct rq
*zd01f3eedf0=task_rq(z0609dbaf9d);struct rq*zeb0037895f=cpu_rq(z525181d1b1);u64 
z790680e4aa;u64*z42b4427a2c,*z2e4da9dbb4;u64*z262b512e81,*z086b45bedf;u64*
zf7e69c10fd,*z847919a57a;u64*z7ba10de4f4,*z082a99fd0f;bool z5eebbbffe9;struct 
related_thread_group*grp;if(!z0609dbaf9d->on_rq&&z0609dbaf9d->state!=TASK_WAKING
)return;if(exiting_task(z0609dbaf9d)){clear_ed_task(z0609dbaf9d,zd01f3eedf0);
return;}if(z0609dbaf9d->state==TASK_WAKING)double_rq_lock(zd01f3eedf0,
zeb0037895f);if(sched_disable_window_stats)goto z02a8afcd23;z790680e4aa=
sched_ktime_clock();walt_update_task_ravg(task_rq(z0609dbaf9d)->curr,task_rq(
z0609dbaf9d),TASK_UPDATE,z790680e4aa,(0x1c43+2138-0x249d));walt_update_task_ravg
(zeb0037895f->curr,zeb0037895f,TASK_UPDATE,z790680e4aa,(0x1404+2016-0x1be4));
walt_update_task_ravg(z0609dbaf9d,task_rq(z0609dbaf9d),TASK_MIGRATE,z790680e4aa,
(0x207+6291-0x1a9a));z1360b17c9b(z0609dbaf9d,z525181d1b1,z790680e4aa);if(
z0609dbaf9d->state==TASK_WAKING&&z0609dbaf9d->last_sleep_ts>=zd01f3eedf0->
window_start){walt_fixup_cum_window_demand(zd01f3eedf0,-(s64)z0609dbaf9d->ravg.
demand_scaled);walt_fixup_cum_window_demand(zeb0037895f,z0609dbaf9d->ravg.
demand_scaled);}z5eebbbffe9=is_new_task(z0609dbaf9d);grp=z0609dbaf9d->grp;if(grp
){struct group_cpu_time*z627d50b29d;z627d50b29d=&zd01f3eedf0->grp_time;
z42b4427a2c=&z627d50b29d->curr_runnable_sum;z262b512e81=&z627d50b29d->
prev_runnable_sum;zf7e69c10fd=&z627d50b29d->nt_curr_runnable_sum;z7ba10de4f4=&
z627d50b29d->nt_prev_runnable_sum;z627d50b29d=&zeb0037895f->grp_time;z2e4da9dbb4
=&z627d50b29d->curr_runnable_sum;z086b45bedf=&z627d50b29d->prev_runnable_sum;
z847919a57a=&z627d50b29d->nt_curr_runnable_sum;z082a99fd0f=&z627d50b29d->
nt_prev_runnable_sum;if(z0609dbaf9d->ravg.curr_window){*z42b4427a2c-=z0609dbaf9d
->ravg.curr_window;*z2e4da9dbb4+=z0609dbaf9d->ravg.curr_window;if(z5eebbbffe9){*
zf7e69c10fd-=z0609dbaf9d->ravg.curr_window;*z847919a57a+=z0609dbaf9d->ravg.
curr_window;}}if(z0609dbaf9d->ravg.prev_window){*z262b512e81-=z0609dbaf9d->ravg.
prev_window;*z086b45bedf+=z0609dbaf9d->ravg.prev_window;if(z5eebbbffe9){*
z7ba10de4f4-=z0609dbaf9d->ravg.prev_window;*z082a99fd0f+=z0609dbaf9d->ravg.
prev_window;}}}else{z6aa95e2012(z0609dbaf9d,z525181d1b1,task_cpu(z0609dbaf9d),
z5eebbbffe9);}z9be28a1f9c(z0609dbaf9d,zd01f3eedf0,zeb0037895f);if(!
same_freq_domain(z525181d1b1,task_cpu(z0609dbaf9d))){zd01f3eedf0->notif_pending=
true;zeb0037895f->notif_pending=true;sched_irq_work_queue(&z72f8d06752);}if(
ze99faa0ca8()){if(z0609dbaf9d==zd01f3eedf0->ed_task){zd01f3eedf0->ed_task=NULL;
zeb0037895f->ed_task=z0609dbaf9d;}else if(z30dc154c3b(z0609dbaf9d,z790680e4aa)){
zeb0037895f->ed_task=z0609dbaf9d;}}z02a8afcd23:if(z0609dbaf9d->state==
TASK_WAKING)double_rq_unlock(zd01f3eedf0,zeb0037895f);}void set_window_start(
struct rq*rq){static int ze66a622f51;if(likely(rq->window_start))return;if(!
ze66a622f51){rq->window_start=(0x872+4406-0x19a7);ze66a622f51=
(0x10b4+3245-0x1d60);atomic64_set(&z8d508f7c3b,rq->window_start);
walt_load_reported_window=atomic64_read(&z8d508f7c3b);}else{struct rq*
z3e3d21be47=cpu_rq(cpumask_any(cpu_online_mask));raw_spin_unlock(&rq->lock);
double_rq_lock(rq,z3e3d21be47);rq->window_start=z3e3d21be47->window_start;rq->
curr_runnable_sum=rq->prev_runnable_sum=(0x21b6+1322-0x26e0);rq->
nt_curr_runnable_sum=rq->nt_prev_runnable_sum=(0x430+6486-0x1d86);
raw_spin_unlock(&z3e3d21be47->lock);}rq->curr->ravg.mark_start=rq->window_start;
}unsigned int max_possible_efficiency=(0x126b+1961-0x1a13);unsigned int 
min_possible_efficiency=UINT_MAX;unsigned int sysctl_sched_conservative_pl;
unsigned int sysctl_sched_many_wakeup_threshold=(0x56d+3328-0xe85);
#define z07c7d3e0b1 (0xd87+5572-0x2343)
#define z07f1c18f03 (0x7d0+2895-0x131d)
#define zedc4e7b72b (0x40a+1891-0xb5d)
#define zd412d902d5 (0x559+1362-0xa9b)
static inline void zcd30d5f093(u8*zc0f271aeff,int z8aa1674e1f){int z5d971be8b8,
z2a39967a03;for(z5d971be8b8=(0x56+5240-0x14ce);z5d971be8b8<NUM_BUSY_BUCKETS;
z5d971be8b8++){if(z8aa1674e1f!=z5d971be8b8){if(zc0f271aeff[z5d971be8b8]>
z07f1c18f03)zc0f271aeff[z5d971be8b8]-=z07f1c18f03;else zc0f271aeff[z5d971be8b8]=
(0x531+5434-0x1a6b);}else{z2a39967a03=zc0f271aeff[z5d971be8b8]>=zedc4e7b72b?
zd412d902d5:z07c7d3e0b1;if(zc0f271aeff[z5d971be8b8]>U8_MAX-z2a39967a03)
zc0f271aeff[z5d971be8b8]=U8_MAX;else zc0f271aeff[z5d971be8b8]+=z2a39967a03;}}}
static inline int z5161a2cdf5(u32 zfd7e825862){int z57acf293db;z57acf293db=
mult_frac(zfd7e825862,NUM_BUSY_BUCKETS,max_task_load());z57acf293db=min(
z57acf293db,NUM_BUSY_BUCKETS-(0xeb2+1311-0x13d0));if(!z57acf293db)z57acf293db++;
return z57acf293db;}static u32 zd706aa2c09(struct task_struct*z0609dbaf9d,int 
z9f089c6af4,u32 z8a690d3852){int z5d971be8b8;u8*zc0f271aeff=z0609dbaf9d->ravg.
busy_buckets;u32*z53b45fa17b=z0609dbaf9d->ravg.sum_history;u32 zf78d322c50,
z51a9118714;u64 z75472ab857=(0xb60+2105-0x1399);int zc4b85e3bbe=NUM_BUSY_BUCKETS
,final;u32 z083920bcc8=z8a690d3852;if(unlikely(is_new_task(z0609dbaf9d)))goto 
ze1f307999b;for(z5d971be8b8=z9f089c6af4;z5d971be8b8<NUM_BUSY_BUCKETS;z5d971be8b8
++){if(zc0f271aeff[z5d971be8b8]){zc4b85e3bbe=z5d971be8b8;break;}}if(zc4b85e3bbe
>=NUM_BUSY_BUCKETS)goto ze1f307999b;final=zc4b85e3bbe;if(final<
(0x437+4079-0x1424)){zf78d322c50=(0x959+3685-0x17be);final=(0xeec+4198-0x1f51);}
else{zf78d322c50=mult_frac(final,max_task_load(),NUM_BUSY_BUCKETS);}z51a9118714=
mult_frac(final+(0x152c+1623-0x1b82),max_task_load(),NUM_BUSY_BUCKETS);for(
z5d971be8b8=(0x499+1814-0xbaf);z5d971be8b8<za591b9e54c;z5d971be8b8++){if(
z53b45fa17b[z5d971be8b8]>=zf78d322c50&&z53b45fa17b[z5d971be8b8]<z51a9118714){
z083920bcc8=z53b45fa17b[z5d971be8b8];break;}}if(z083920bcc8<zf78d322c50)
z083920bcc8=(zf78d322c50+z51a9118714)/(0x1690+547-0x18b1);z083920bcc8=max(
z8a690d3852,z083920bcc8);ze1f307999b:trace_sched_update_pred_demand(z0609dbaf9d,
z8a690d3852,mult_frac((unsigned int)z75472ab857,(0x4b8+7434-0x215e),
sched_ravg_window),z083920bcc8);return z083920bcc8;}static inline u32 
za50ae1c837(struct task_struct*z0609dbaf9d){if(z0609dbaf9d->ravg.pred_demand>=
z0609dbaf9d->ravg.curr_window)return z0609dbaf9d->ravg.pred_demand;return 
zd706aa2c09(z0609dbaf9d,z5161a2cdf5(z0609dbaf9d->ravg.curr_window),z0609dbaf9d->
ravg.curr_window);}void zbc967ce57f(struct rq*rq,struct task_struct*z0609dbaf9d,
int z3205babe24){u32 new,zec59fbb1ff;u16 zb2100a439c;if(!sched_predl)return;if(
is_idle_task(z0609dbaf9d)||exiting_task(z0609dbaf9d))return;if(z3205babe24!=
PUT_PREV_TASK&&z3205babe24!=TASK_UPDATE&&(!z88b9b0b9ce||(z3205babe24!=
TASK_MIGRATE&&z3205babe24!=PICK_NEXT_TASK)))return;if(z3205babe24==TASK_UPDATE){
if(!z0609dbaf9d->on_rq&&!z88b9b0b9ce)return;}new=za50ae1c837(z0609dbaf9d);
zec59fbb1ff=z0609dbaf9d->ravg.pred_demand;if(zec59fbb1ff>=new)return;zb2100a439c
=zecf40170d4(new);if(task_on_rq_queued(z0609dbaf9d)&&(!task_has_dl_policy(
z0609dbaf9d)||!z0609dbaf9d->dl.dl_throttled)&&z0609dbaf9d->sched_class->
fixup_walt_sched_stats)z0609dbaf9d->sched_class->fixup_walt_sched_stats(rq,
z0609dbaf9d,z0609dbaf9d->ravg.demand_scaled,zb2100a439c);z0609dbaf9d->ravg.
pred_demand=new;z0609dbaf9d->ravg.pred_demand_scaled=zb2100a439c;}void 
z66971bc3d0(unsigned long*z75c312d1cd){memset(z75c312d1cd,(0x229+8315-0x22a4),
z64333e9737);__set_bit(NUM_LOAD_INDICES,z75c312d1cd);}static inline void 
clear_top_tasks_table(u8*table){memset(table,(0x3bc+1157-0x841),NUM_LOAD_INDICES
*sizeof(u8));}static void z81ac526b7a(struct task_struct*z0609dbaf9d,struct rq*
rq,u32 z394bc84586,int z3b5207d436,bool zdd3d5a87d4){u8 curr=rq->curr_table;u8 
prev=(0x307+6187-0x1b31)-curr;u8*curr_table=rq->top_tasks[curr];u8*z78d0a88386=
rq->top_tasks[prev];int zbbf323d019,z6a0597304c,z64adf5cf6f;u32 curr_window=
z0609dbaf9d->ravg.curr_window;u32 prev_window=z0609dbaf9d->ravg.prev_window;bool
 zd4e56af857;if(z394bc84586==curr_window&&!z3b5207d436)return;zbbf323d019=
zb7bb6f3305(z394bc84586);z6a0597304c=zb7bb6f3305(curr_window);if(!z3b5207d436){
zd4e56af857=!z394bc84586&&curr_window;if(zbbf323d019!=z6a0597304c||zd4e56af857){
if(z394bc84586)curr_table[zbbf323d019]-=(0x156d+2790-0x2052);if(curr_window)
curr_table[z6a0597304c]+=(0x1853+2173-0x20cf);if(z6a0597304c>rq->curr_top)rq->
curr_top=z6a0597304c;}if(!curr_table[zbbf323d019])__clear_bit(NUM_LOAD_INDICES-
zbbf323d019-(0x16c1+2077-0x1edd),rq->top_tasks_bitmap[curr]);if(curr_table[
z6a0597304c]==(0x7c5+5139-0x1bd7))__set_bit(NUM_LOAD_INDICES-z6a0597304c-
(0x1f85+1234-0x2456),rq->top_tasks_bitmap[curr]);return;}z64adf5cf6f=zb7bb6f3305
(prev_window);if(zdd3d5a87d4){if(prev_window){z78d0a88386[z64adf5cf6f]+=
(0x7ef+6372-0x20d2);rq->prev_top=z64adf5cf6f;}if(z78d0a88386[z64adf5cf6f]==
(0x146a+2603-0x1e94))__set_bit(NUM_LOAD_INDICES-z64adf5cf6f-(0xc2d+6508-0x2598),
rq->top_tasks_bitmap[prev]);}else{zd4e56af857=!z394bc84586&&prev_window;if(
zbbf323d019!=z64adf5cf6f||zd4e56af857){if(z394bc84586)z78d0a88386[zbbf323d019]-=
(0x4ab+4647-0x16d1);z78d0a88386[z64adf5cf6f]+=(0x162+8417-0x2242);if(z64adf5cf6f
>rq->prev_top)rq->prev_top=z64adf5cf6f;if(!z78d0a88386[zbbf323d019])__clear_bit(
NUM_LOAD_INDICES-zbbf323d019-(0x450+2506-0xe19),rq->top_tasks_bitmap[prev]);if(
z78d0a88386[z64adf5cf6f]==(0x13c6+1938-0x1b57))__set_bit(NUM_LOAD_INDICES-
z64adf5cf6f-(0x1a83+1113-0x1edb),rq->top_tasks_bitmap[prev]);}}if(curr_window){
curr_table[z6a0597304c]+=(0x1096+2581-0x1aaa);if(z6a0597304c>rq->curr_top)rq->
curr_top=z6a0597304c;if(curr_table[z6a0597304c]==(0x226c+535-0x2482))__set_bit(
NUM_LOAD_INDICES-z6a0597304c-(0x719+5462-0x1c6e),rq->top_tasks_bitmap[curr]);}}
static void z05813ee528(struct rq*rq,bool zdd3d5a87d4){u8 curr_table=rq->
curr_table;u8 z78d0a88386=(0xf90+669-0x122c)-curr_table;int curr_top=rq->
curr_top;clear_top_tasks_table(rq->top_tasks[z78d0a88386]);z66971bc3d0(rq->
top_tasks_bitmap[z78d0a88386]);if(zdd3d5a87d4){curr_top=(0x11e1+5272-0x2679);
clear_top_tasks_table(rq->top_tasks[curr_table]);z66971bc3d0(rq->
top_tasks_bitmap[curr_table]);}rq->curr_table=z78d0a88386;rq->prev_top=curr_top;
rq->curr_top=(0x186f+733-0x1b4c);}static u32 z0c92d7b1ad[NR_CPUS];static void 
zd12ebe5060(struct task_struct*z0609dbaf9d,bool zdd3d5a87d4){u32*z1d6a0b8b72=
z0c92d7b1ad;u32 curr_window;int z5d971be8b8;curr_window=(0x1194+4807-0x245b);if(
!zdd3d5a87d4){curr_window=z0609dbaf9d->ravg.curr_window;z1d6a0b8b72=z0609dbaf9d
->ravg.curr_window_cpu;}z0609dbaf9d->ravg.prev_window=curr_window;z0609dbaf9d->
ravg.curr_window=(0x114+4430-0x1262);for(z5d971be8b8=(0x1d53+2024-0x253b);
z5d971be8b8<nr_cpu_ids;z5d971be8b8++){z0609dbaf9d->ravg.prev_window_cpu[
z5d971be8b8]=z1d6a0b8b72[z5d971be8b8];z0609dbaf9d->ravg.curr_window_cpu[
z5d971be8b8]=(0x1666+1380-0x1bca);}if(is_new_task(z0609dbaf9d))z0609dbaf9d->ravg
.active_time+=z0609dbaf9d->ravg.last_win_size;}void sched_set_io_is_busy(int 
zc94d3d8015){zdedb054041=zc94d3d8015;}static inline int z40d96c83d6(struct rq*rq
){if(!zdedb054041)return(0x304+8544-0x2464);return atomic_read(&rq->nr_iowait);}
static int z596816cbc6(struct rq*rq,struct task_struct*z0609dbaf9d,u64 
z59018c6914,int z3205babe24){if(is_idle_task(z0609dbaf9d)){if(z3205babe24==
PICK_NEXT_TASK)return(0x14ad+4116-0x24c1);return z59018c6914||z40d96c83d6(rq);}
if(z3205babe24==TASK_WAKE)return(0xa4d+5079-0x1e24);if(z3205babe24==
PUT_PREV_TASK||z3205babe24==IRQ_UPDATE)return(0x120+1466-0x6d9);if(z3205babe24==
TASK_UPDATE){if(rq->curr==z0609dbaf9d)return(0x65f+8333-0x26eb);return 
z0609dbaf9d->on_rq?z88b9b0b9ce:(0x132c+2331-0x1c47);}return z88b9b0b9ce;}
#define z20b422fc7b(z98927a0ef6, zc096799050) div64_u64((z98927a0ef6) + (\
zc096799050 - (0x88d+5899-0x1f97)), zc096799050)
static inline u64 zb95ca9f31b(u64 z17abc14e87,struct rq*rq){return(z17abc14e87*
rq->task_exec_scale)>>(0x1171+942-0x1515);}static inline unsigned int 
z603dc3b6ad(struct rq*rq,unsigned int z514f31b9a6){return mult_frac(
cpu_max_possible_freq(cpu_of(rq)),z514f31b9a6,(unsigned int)capacity_orig_of(
cpu_of(rq)));}bool do_pl_notif(struct rq*rq){u64 prev=rq->old_busy_time;u64 pl=
rq->walt_stats.pred_demands_sum_scaled;int cpu=cpu_of(rq);if(capacity_orig_of(
cpu)==capacity_curr_of(cpu))return false;prev=max(prev,rq->old_estimated_time);
return(pl>prev)&&(z603dc3b6ad(rq,pl-prev)>400000);}static void z8ebc59a5de(
struct rq*rq,bool zdd3d5a87d4){u64 z36b7a61385=rq->curr_runnable_sum;u64 
z41bd9431ad=rq->nt_curr_runnable_sum;u64 zc62485a0c5=rq->grp_time.
curr_runnable_sum;u64 z1ae796a363=rq->grp_time.nt_curr_runnable_sum;if(unlikely(
zdd3d5a87d4)){z36b7a61385=(0xe28+4428-0x1f74);z41bd9431ad=(0xae5+4213-0x1b5a);
zc62485a0c5=(0x6ec+7854-0x259a);z1ae796a363=(0x11bf+623-0x142e);}rq->
prev_runnable_sum=z36b7a61385;rq->nt_prev_runnable_sum=z41bd9431ad;rq->grp_time.
prev_runnable_sum=zc62485a0c5;rq->grp_time.nt_prev_runnable_sum=z1ae796a363;rq->
curr_runnable_sum=(0x627+2353-0xf58);rq->nt_curr_runnable_sum=
(0xc71+1567-0x1290);rq->grp_time.curr_runnable_sum=(0xdb1+3534-0x1b7f);rq->
grp_time.nt_curr_runnable_sum=(0x22a8+418-0x244a);}static void z130dee47f1(
struct task_struct*z0609dbaf9d,struct rq*rq,int z3205babe24,u64 z790680e4aa,u64 
z59018c6914){int z3b5207d436,zdd3d5a87d4=(0x5c9+7038-0x2147);int zd7f58f7fc0=(
z0609dbaf9d==rq->curr);u64 mark_start=z0609dbaf9d->ravg.mark_start;u64 
window_start=rq->window_start;u32 z4ae816ebd1=rq->prev_window_size;u64 
z17abc14e87;u64*curr_runnable_sum=&rq->curr_runnable_sum;u64*prev_runnable_sum=&
rq->prev_runnable_sum;u64*nt_curr_runnable_sum=&rq->nt_curr_runnable_sum;u64*
nt_prev_runnable_sum=&rq->nt_prev_runnable_sum;bool z5eebbbffe9;struct 
related_thread_group*grp;int cpu=rq->cpu;u32 z394bc84586=z0609dbaf9d->ravg.
curr_window;z3b5207d436=mark_start<window_start;if(z3b5207d436)zdd3d5a87d4=(
window_start-mark_start)>=z4ae816ebd1;if(!is_idle_task(z0609dbaf9d)&&!
exiting_task(z0609dbaf9d)){if(z3b5207d436)zd12ebe5060(z0609dbaf9d,zdd3d5a87d4);}
z5eebbbffe9=is_new_task(z0609dbaf9d);if(zd7f58f7fc0&&z3b5207d436){z8ebc59a5de(rq
,zdd3d5a87d4);z05813ee528(rq,zdd3d5a87d4);}if(!z596816cbc6(rq,z0609dbaf9d,
z59018c6914,z3205babe24))goto z02a8afcd23;grp=z0609dbaf9d->grp;if(grp){struct 
group_cpu_time*z627d50b29d=&rq->grp_time;curr_runnable_sum=&z627d50b29d->
curr_runnable_sum;prev_runnable_sum=&z627d50b29d->prev_runnable_sum;
nt_curr_runnable_sum=&z627d50b29d->nt_curr_runnable_sum;nt_prev_runnable_sum=&
z627d50b29d->nt_prev_runnable_sum;}if(!z3b5207d436){if(!z59018c6914||!
is_idle_task(z0609dbaf9d)||z40d96c83d6(rq))z17abc14e87=z790680e4aa-mark_start;
else z17abc14e87=z59018c6914;z17abc14e87=zb95ca9f31b(z17abc14e87,rq);*
curr_runnable_sum+=z17abc14e87;if(z5eebbbffe9)*nt_curr_runnable_sum+=z17abc14e87
;if(!is_idle_task(z0609dbaf9d)&&!exiting_task(z0609dbaf9d)){z0609dbaf9d->ravg.
curr_window+=z17abc14e87;z0609dbaf9d->ravg.curr_window_cpu[cpu]+=z17abc14e87;}
goto z02a8afcd23;}if(!zd7f58f7fc0){if(!zdd3d5a87d4){z17abc14e87=zb95ca9f31b(
window_start-mark_start,rq);if(!exiting_task(z0609dbaf9d)){z0609dbaf9d->ravg.
prev_window+=z17abc14e87;z0609dbaf9d->ravg.prev_window_cpu[cpu]+=z17abc14e87;}}
else{z17abc14e87=zb95ca9f31b(z4ae816ebd1,rq);if(!exiting_task(z0609dbaf9d)){
z0609dbaf9d->ravg.prev_window=z17abc14e87;z0609dbaf9d->ravg.prev_window_cpu[cpu]
=z17abc14e87;}}*prev_runnable_sum+=z17abc14e87;if(z5eebbbffe9)*
nt_prev_runnable_sum+=z17abc14e87;z17abc14e87=zb95ca9f31b(z790680e4aa-
window_start,rq);*curr_runnable_sum+=z17abc14e87;if(z5eebbbffe9)*
nt_curr_runnable_sum+=z17abc14e87;if(!exiting_task(z0609dbaf9d)){z0609dbaf9d->
ravg.curr_window=z17abc14e87;z0609dbaf9d->ravg.curr_window_cpu[cpu]=z17abc14e87;
}goto z02a8afcd23;}if(!z59018c6914||!is_idle_task(z0609dbaf9d)||z40d96c83d6(rq))
{if(!zdd3d5a87d4){z17abc14e87=zb95ca9f31b(window_start-mark_start,rq);if(!
is_idle_task(z0609dbaf9d)&&!exiting_task(z0609dbaf9d)){z0609dbaf9d->ravg.
prev_window+=z17abc14e87;z0609dbaf9d->ravg.prev_window_cpu[cpu]+=z17abc14e87;}}
else{z17abc14e87=zb95ca9f31b(z4ae816ebd1,rq);if(!is_idle_task(z0609dbaf9d)&&!
exiting_task(z0609dbaf9d)){z0609dbaf9d->ravg.prev_window=z17abc14e87;z0609dbaf9d
->ravg.prev_window_cpu[cpu]=z17abc14e87;}}*prev_runnable_sum+=z17abc14e87;if(
z5eebbbffe9)*nt_prev_runnable_sum+=z17abc14e87;z17abc14e87=zb95ca9f31b(
z790680e4aa-window_start,rq);*curr_runnable_sum+=z17abc14e87;if(z5eebbbffe9)*
nt_curr_runnable_sum+=z17abc14e87;if(!is_idle_task(z0609dbaf9d)&&!exiting_task(
z0609dbaf9d)){z0609dbaf9d->ravg.curr_window=z17abc14e87;z0609dbaf9d->ravg.
curr_window_cpu[cpu]=z17abc14e87;}goto z02a8afcd23;}if(z59018c6914){z609fba09ac(
!is_idle_task(z0609dbaf9d));mark_start=z790680e4aa-z59018c6914;if(mark_start>
window_start){*curr_runnable_sum=zb95ca9f31b(z59018c6914,rq);return;}z17abc14e87
=window_start-mark_start;if(z17abc14e87>z4ae816ebd1)z17abc14e87=z4ae816ebd1;
z17abc14e87=zb95ca9f31b(z17abc14e87,rq);*prev_runnable_sum+=z17abc14e87;
z17abc14e87=z790680e4aa-window_start;rq->curr_runnable_sum=zb95ca9f31b(
z17abc14e87,rq);return;}z02a8afcd23:if(!is_idle_task(z0609dbaf9d)&&!exiting_task
(z0609dbaf9d))z81ac526b7a(z0609dbaf9d,rq,z394bc84586,z3b5207d436,zdd3d5a87d4);}
static inline u32 zfa0202d8d2(struct task_struct*z0609dbaf9d,u32 z8a690d3852){
int z57acf293db;u32 pred_demand;if(!sched_predl)return(0x165c+71-0x16a3);
z57acf293db=z5161a2cdf5(z8a690d3852);pred_demand=zd706aa2c09(z0609dbaf9d,
z57acf293db,z8a690d3852);zcd30d5f093(z0609dbaf9d->ravg.busy_buckets,z57acf293db)
;return pred_demand;}static int z9e189b41d3(struct rq*rq,struct task_struct*
z0609dbaf9d,int z3205babe24){if(exiting_task(z0609dbaf9d)||is_idle_task(
z0609dbaf9d))return(0xc0f+5595-0x21ea);if(z3205babe24==TASK_WAKE||(!z19b86f3ee0
&&(z3205babe24==PICK_NEXT_TASK||z3205babe24==TASK_MIGRATE)))return
(0x50+6754-0x1ab2);if(z3205babe24==PICK_NEXT_TASK&&rq->curr==rq->idle)return
(0xe36+5970-0x2588);if(z3205babe24==TASK_UPDATE){if(rq->curr==z0609dbaf9d)return
(0xbd1+6069-0x2385);return z0609dbaf9d->on_rq?z19b86f3ee0:(0x408+1777-0xaf9);}
return(0xc73+2276-0x1556);}unsigned int sysctl_sched_task_unfilter_period=
200000000;static void z5807425a04(struct rq*rq,struct task_struct*z0609dbaf9d,
u32 z8a690d3852,int z7d946df0fb,int z3205babe24){u32*z53b45fa17b=&z0609dbaf9d->
ravg.sum_history[(0x1c65+2295-0x255c)];int z7a1e3fe84e,zc98feb876b;u32 max=
(0x634+7324-0x22d0),zf034c4ad57,demand,pred_demand;u64 sum=(0xf38+95-0xf97);u16 
demand_scaled,pred_demand_scaled;if(!z8a690d3852||is_idle_task(z0609dbaf9d)||
exiting_task(z0609dbaf9d)||!z7d946df0fb)goto z02a8afcd23;zc98feb876b=za591b9e54c
-(0xa65+805-0xd89);z7a1e3fe84e=zc98feb876b-z7d946df0fb;for(;z7a1e3fe84e>=
(0x17f9+3073-0x23fa);--zc98feb876b,--z7a1e3fe84e){z53b45fa17b[zc98feb876b]=
z53b45fa17b[z7a1e3fe84e];sum+=z53b45fa17b[zc98feb876b];if(z53b45fa17b[
zc98feb876b]>max)max=z53b45fa17b[zc98feb876b];}for(zc98feb876b=
(0xdc4+3877-0x1ce9);zc98feb876b<z7d946df0fb&&zc98feb876b<za591b9e54c;zc98feb876b
++){z53b45fa17b[zc98feb876b]=z8a690d3852;sum+=z53b45fa17b[zc98feb876b];if(
z53b45fa17b[zc98feb876b]>max)max=z53b45fa17b[zc98feb876b];}z0609dbaf9d->ravg.sum
=(0x9f0+1222-0xeb6);if(sysctl_sched_window_stats_policy==WINDOW_STATS_RECENT){
demand=z8a690d3852;}else if(sysctl_sched_window_stats_policy==WINDOW_STATS_MAX){
demand=max;}else{zf034c4ad57=div64_u64(sum,za591b9e54c);if(
sysctl_sched_window_stats_policy==WINDOW_STATS_AVG)demand=zf034c4ad57;else 
demand=max(zf034c4ad57,z8a690d3852);}pred_demand=zfa0202d8d2(z0609dbaf9d,
z8a690d3852);demand_scaled=zecf40170d4(demand);pred_demand_scaled=zecf40170d4(
pred_demand);if(!task_has_dl_policy(z0609dbaf9d)||!z0609dbaf9d->dl.dl_throttled)
{if(task_on_rq_queued(z0609dbaf9d)&&z0609dbaf9d->sched_class->
fixup_walt_sched_stats)z0609dbaf9d->sched_class->fixup_walt_sched_stats(rq,
z0609dbaf9d,demand_scaled,pred_demand_scaled);else if(rq->curr==z0609dbaf9d)
walt_fixup_cum_window_demand(rq,demand_scaled);}z0609dbaf9d->ravg.demand=demand;
z0609dbaf9d->ravg.demand_scaled=demand_scaled;z0609dbaf9d->ravg.coloc_demand=
div64_u64(sum,za591b9e54c);z0609dbaf9d->ravg.pred_demand=pred_demand;z0609dbaf9d
->ravg.pred_demand_scaled=pred_demand_scaled;if(demand_scaled>
sched_task_filter_util)z0609dbaf9d->unfilter=sysctl_sched_task_unfilter_period;
else if(z0609dbaf9d->unfilter)z0609dbaf9d->unfilter=max_t(int,
(0x1338+4074-0x2322),z0609dbaf9d->unfilter-z0609dbaf9d->ravg.last_win_size);
z02a8afcd23:trace_sched_update_history(rq,z0609dbaf9d,z8a690d3852,z7d946df0fb,
z3205babe24);}static u64 zd042bf0817(struct rq*rq,struct task_struct*z0609dbaf9d
,u64 z17abc14e87){z17abc14e87=zb95ca9f31b(z17abc14e87,rq);z0609dbaf9d->ravg.sum
+=z17abc14e87;if(unlikely(z0609dbaf9d->ravg.sum>sched_ravg_window))z0609dbaf9d->
ravg.sum=sched_ravg_window;return z17abc14e87;}static u64 zd61ac3ed43(struct 
task_struct*z0609dbaf9d,struct rq*rq,int z3205babe24,u64 z790680e4aa){u64 
mark_start=z0609dbaf9d->ravg.mark_start;u64 z17abc14e87,window_start=rq->
window_start;int z3b5207d436,z51e91ddbe6;u32 z4ae816ebd1=sched_ravg_window;u64 
z8a690d3852;z3b5207d436=mark_start<window_start;if(!z9e189b41d3(rq,z0609dbaf9d,
z3205babe24)){if(z3b5207d436)z5807425a04(rq,z0609dbaf9d,z0609dbaf9d->ravg.sum,
(0x1882+2546-0x2273),z3205babe24);return(0xf2a+1974-0x16e0);}if(!z3b5207d436){
return zd042bf0817(rq,z0609dbaf9d,z790680e4aa-mark_start);}z17abc14e87=
window_start-mark_start;z51e91ddbe6=div64_u64(z17abc14e87,z4ae816ebd1);
window_start-=(u64)z51e91ddbe6*(u64)z4ae816ebd1;z8a690d3852=zd042bf0817(rq,
z0609dbaf9d,window_start-mark_start);z5807425a04(rq,z0609dbaf9d,z0609dbaf9d->
ravg.sum,(0xc17+2006-0x13ec),z3205babe24);if(z51e91ddbe6){u64 za08f625e72=
zb95ca9f31b(z4ae816ebd1,rq);z5807425a04(rq,z0609dbaf9d,za08f625e72,z51e91ddbe6,
z3205babe24);z8a690d3852+=z51e91ddbe6*za08f625e72;}window_start+=(u64)
z51e91ddbe6*(u64)z4ae816ebd1;mark_start=window_start;z8a690d3852+=zd042bf0817(rq
,z0609dbaf9d,z790680e4aa-mark_start);return z8a690d3852;}static inline unsigned 
int cpu_cur_freq(int cpu){return cpu_rq(cpu)->cluster->cur_freq;}static void 
zeaadfc2aba(struct task_struct*z0609dbaf9d,struct rq*rq,int z3205babe24,u64 
z790680e4aa,u64 z59018c6914){u64 z6f5b2bdad3;u64 z88024db1de;u64 z6d1d7700ef;int
 cpu=cpu_of(rq);lockdep_assert_held(&rq->lock);if(!z3b880410aa){rq->
task_exec_scale=z20b422fc7b(cpu_cur_freq(cpu)*topology_get_cpu_scale(cpu),rq->
cluster->max_possible_freq);return;}z6f5b2bdad3=z2cd0d15eb3(cpu,z790680e4aa);if(
!is_idle_task(rq->curr)||z59018c6914){if(unlikely(z6f5b2bdad3<z0609dbaf9d->
cpu_cycles))z88024db1de=z6f5b2bdad3+(U64_MAX-z0609dbaf9d->cpu_cycles);else 
z88024db1de=z6f5b2bdad3-z0609dbaf9d->cpu_cycles;z88024db1de=z88024db1de*
NSEC_PER_MSEC;if(z3205babe24==IRQ_UPDATE&&is_idle_task(z0609dbaf9d))z6d1d7700ef=
z59018c6914;else z6d1d7700ef=z790680e4aa-z0609dbaf9d->ravg.mark_start;
z609fba09ac((s64)z6d1d7700ef<(0x1e89+335-0x1fd8));rq->task_exec_scale=
z20b422fc7b(z88024db1de*topology_get_cpu_scale(cpu),z6d1d7700ef*rq->cluster->
max_possible_freq);trace_sched_get_task_cpu_cycles(cpu,z3205babe24,z88024db1de,
z6d1d7700ef,z0609dbaf9d);}z0609dbaf9d->cpu_cycles=z6f5b2bdad3;}static inline 
void z4f54d6a4cc(u64 z901ba13dc5,struct rq*rq){u64 z5f54ca7c5e;if(z901ba13dc5==
rq->window_start)return;z5f54ca7c5e=atomic64_cmpxchg(&z8d508f7c3b,z901ba13dc5,rq
->window_start);if(z5f54ca7c5e==z901ba13dc5)sched_irq_work_queue(&z5bb9cd73e7);}
void walt_update_task_ravg(struct task_struct*z0609dbaf9d,struct rq*rq,int 
z3205babe24,u64 z790680e4aa,u64 z59018c6914){u64 z901ba13dc5;if(!rq->
window_start||sched_disable_window_stats||z0609dbaf9d->ravg.mark_start==
z790680e4aa)return;lockdep_assert_held(&rq->lock);z901ba13dc5=z6bdc3765bb(rq,
z790680e4aa,z3205babe24);if(!z0609dbaf9d->ravg.mark_start){z1360b17c9b(
z0609dbaf9d,cpu_of(rq),z790680e4aa);goto z02a8afcd23;}zeaadfc2aba(z0609dbaf9d,rq
,z3205babe24,z790680e4aa,z59018c6914);zd61ac3ed43(z0609dbaf9d,rq,z3205babe24,
z790680e4aa);z130dee47f1(z0609dbaf9d,rq,z3205babe24,z790680e4aa,z59018c6914);
zbc967ce57f(rq,z0609dbaf9d,z3205babe24);if(exiting_task(z0609dbaf9d))goto 
z02a8afcd23;trace_sched_update_task_ravg(z0609dbaf9d,rq,z3205babe24,z790680e4aa,
z59018c6914,&rq->grp_time);trace_sched_update_task_ravg_mini(z0609dbaf9d,rq,
z3205babe24,z790680e4aa,z59018c6914,&rq->grp_time);z02a8afcd23:z0609dbaf9d->ravg
.mark_start=z790680e4aa;z0609dbaf9d->ravg.last_win_size=sched_ravg_window;
z4f54d6a4cc(z901ba13dc5,rq);}u32 sched_get_init_task_load(struct task_struct*
z0609dbaf9d){return z0609dbaf9d->init_load_pct;}int sched_set_init_task_load(
struct task_struct*z0609dbaf9d,int init_load_pct){if(init_load_pct<
(0x84c+1297-0xd5d)||init_load_pct>(0x755+22-0x707))return-EINVAL;z0609dbaf9d->
init_load_pct=init_load_pct;return(0x1a59+1207-0x1f10);}void init_new_task_load(
struct task_struct*z0609dbaf9d){int z5d971be8b8;u32 zb5ef75b5b9=
sched_init_task_load_windows;u32 zbec959d3fa=zb0bc76dcf5;u32 init_load_pct=
current->init_load_pct;z0609dbaf9d->init_load_pct=(0x10d6+3770-0x1f90);
rcu_assign_pointer(z0609dbaf9d->grp,NULL);INIT_LIST_HEAD(&z0609dbaf9d->grp_list)
;memset(&z0609dbaf9d->ravg,(0x1beb+742-0x1ed1),sizeof(struct ravg));z0609dbaf9d
->cpu_cycles=(0x62+4277-0x1117);z0609dbaf9d->ravg.curr_window_cpu=kcalloc(
nr_cpu_ids,sizeof(u32),GFP_KERNEL|__GFP_NOFAIL);z0609dbaf9d->ravg.
prev_window_cpu=kcalloc(nr_cpu_ids,sizeof(u32),GFP_KERNEL|__GFP_NOFAIL);if(
init_load_pct){zb5ef75b5b9=div64_u64((u64)init_load_pct*(u64)sched_ravg_window,
(0x676+7625-0x23db));zbec959d3fa=zecf40170d4(zb5ef75b5b9);}z0609dbaf9d->ravg.
demand=zb5ef75b5b9;z0609dbaf9d->ravg.demand_scaled=zbec959d3fa;z0609dbaf9d->ravg
.coloc_demand=zb5ef75b5b9;z0609dbaf9d->ravg.pred_demand=(0x96d+6399-0x226c);
z0609dbaf9d->ravg.pred_demand_scaled=(0x953+710-0xc19);for(z5d971be8b8=
(0x6f6+2831-0x1205);z5d971be8b8<RAVG_HIST_SIZE_MAX;++z5d971be8b8)z0609dbaf9d->
ravg.sum_history[z5d971be8b8]=zb5ef75b5b9;z0609dbaf9d->misfit=false;z0609dbaf9d
->unfilter=sysctl_sched_task_unfilter_period;}void free_task_load_ptrs(struct 
task_struct*z0609dbaf9d){kfree(z0609dbaf9d->ravg.curr_window_cpu);kfree(
z0609dbaf9d->ravg.prev_window_cpu);z0609dbaf9d->ravg.curr_window_cpu=NULL;
z0609dbaf9d->ravg.prev_window_cpu=NULL;}void reset_task_stats(struct task_struct
*z0609dbaf9d){u32 sum=(0xa4c+7078-0x25f2);u32*zd74c5f0f49=NULL;u32*z72caf72ca7=
NULL;if(exiting_task(z0609dbaf9d)){sum=EXITING_TASK_MARKER;}else{zd74c5f0f49=
z0609dbaf9d->ravg.curr_window_cpu;z72caf72ca7=z0609dbaf9d->ravg.prev_window_cpu;
memset(zd74c5f0f49,(0x2457+607-0x26b6),sizeof(u32)*nr_cpu_ids);memset(
z72caf72ca7,(0x1b9+4694-0x140f),sizeof(u32)*nr_cpu_ids);}memset(&z0609dbaf9d->
ravg,(0xd12+4198-0x1d78),sizeof(struct ravg));z0609dbaf9d->ravg.curr_window_cpu=
zd74c5f0f49;z0609dbaf9d->ravg.prev_window_cpu=z72caf72ca7;z0609dbaf9d->ravg.
sum_history[(0x26f+294-0x395)]=sum;}void mark_task_starting(struct task_struct*
z0609dbaf9d){u64 z790680e4aa;struct rq*rq=task_rq(z0609dbaf9d);if(!rq->
window_start||sched_disable_window_stats){reset_task_stats(z0609dbaf9d);return;}
z790680e4aa=sched_ktime_clock();z0609dbaf9d->ravg.mark_start=z0609dbaf9d->
last_wake_ts=z790680e4aa;z0609dbaf9d->last_enqueued_ts=z790680e4aa;z1360b17c9b(
z0609dbaf9d,cpu_of(rq),z790680e4aa);}
#define z07441adb9e(zd3f2891e0f)				\
		div64_u64(((u64)sched_ravg_window * zd3f2891e0f *	\
			topology_get_cpu_scale(			\
			cluster_first_cpu(sched_cluster[(0x905+401-0xa96)]))),	\
			((u64)SCHED_CAPACITY_SCALE * (0xc01+7001-0x26f6)))
unsigned int __read_mostly sched_group_upmigrate=20000000;unsigned int 
__read_mostly sysctl_sched_group_upmigrate_pct=(0x15d7+3724-0x23ff);unsigned int
 __read_mostly sched_group_downmigrate=19000000;unsigned int __read_mostly 
sysctl_sched_group_downmigrate_pct=(0x166+3767-0xfbe);static inline void 
zfbcbf0e27a(void){sched_group_upmigrate=z07441adb9e(
sysctl_sched_group_upmigrate_pct);sched_group_downmigrate=z07441adb9e(
sysctl_sched_group_downmigrate_pct);}static void zc55fd0bd6e(const cpumask_t*
cpus){unsigned long flags;z04b55e82dd(cpu_possible_mask,&flags);if(
cpumask_intersects(cpus,&sched_cluster[(0xaa5+5253-0x1f2a)]->cpus))zfbcbf0e27a()
;zbe61fad8ce(cpu_possible_mask,&flags);}struct sched_cluster*sched_cluster[
NR_CPUS];int num_sched_clusters;struct list_head cluster_head;cpumask_t 
asym_cap_sibling_cpus=CPU_MASK_NONE;static struct sched_cluster z2d02e5bf36={.
list=LIST_HEAD_INIT(z2d02e5bf36.list),.id=(0x932+7443-0x2645),.max_power_cost=
(0x12d+8740-0x2350),.min_power_cost=(0x103a+71-0x1080),.max_possible_capacity=
(0x1949+4515-0x26ec),.efficiency=(0x94c+1105-0xd9c),.cur_freq=
(0xaff+1933-0x128b),.max_freq=(0x642+407-0x7d8),.max_mitigated_freq=UINT_MAX,.
min_freq=(0x7e2+3086-0x13ef),.max_possible_freq=(0x7b9+2427-0x1133),.
exec_scale_factor=(0xcd9+5445-0x1e1e),.aggr_grp_load=(0x1dd+7157-0x1dd2),};void 
init_clusters(void){z2d02e5bf36.cpus=*cpu_possible_mask;raw_spin_lock_init(&
z2d02e5bf36.load_lock);INIT_LIST_HEAD(&cluster_head);list_add(&z2d02e5bf36.list,
&cluster_head);}static void z9cd889a347(struct sched_cluster*cluster,struct 
list_head*z4464c6f5dc){struct sched_cluster*zb9b0dca770;struct list_head*
z83f88df353=z4464c6f5dc;list_for_each_entry(zb9b0dca770,z4464c6f5dc,list){if(
cluster->max_power_cost<zb9b0dca770->max_power_cost)break;z83f88df353=&
zb9b0dca770->list;}list_add(&cluster->list,z83f88df353);}static struct 
sched_cluster*z209e94ab80(const struct cpumask*cpus){struct sched_cluster*
cluster=NULL;cluster=kzalloc(sizeof(struct sched_cluster),GFP_ATOMIC);if(!
cluster){pr_warn(
"\x43\x6c\x75\x73\x74\x65\x72\x20\x61\x6c\x6c\x6f\x63\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x50\x6f\x73\x73\x69\x62\x6c\x65\x20\x62\x61\x64\x20\x73\x63\x68\x65\x64\x75\x6c\x69\x6e\x67" "\n"
);return NULL;}INIT_LIST_HEAD(&cluster->list);cluster->max_power_cost=
(0x1f09+434-0x20ba);cluster->min_power_cost=(0x5f3+1199-0xaa1);cluster->
max_possible_capacity=(0x6b2+8848-0x2542);cluster->efficiency=
(0x1db4+2333-0x26d0);cluster->cur_freq=(0xccc+3213-0x1958);cluster->max_freq=
(0x6d9+1040-0xae8);cluster->max_mitigated_freq=UINT_MAX;cluster->min_freq=
(0x210a+216-0x21e1);cluster->max_possible_freq=(0xc7f+2118-0x14c4);cluster->
freq_init_done=false;raw_spin_lock_init(&cluster->load_lock);cluster->cpus=*cpus
;cluster->efficiency=topology_get_cpu_scale(cpumask_first(cpus));if(cluster->
efficiency>max_possible_efficiency)max_possible_efficiency=cluster->efficiency;
if(cluster->efficiency<min_possible_efficiency)min_possible_efficiency=cluster->
efficiency;return cluster;}static void z2273ecae7d(const struct cpumask*cpus,
struct list_head*z4464c6f5dc){struct sched_cluster*cluster=z209e94ab80(cpus);int
 z5d971be8b8;if(!cluster)return;for_each_cpu(z5d971be8b8,cpus)cpu_rq(z5d971be8b8
)->cluster=cluster;z9cd889a347(cluster,z4464c6f5dc);num_sched_clusters++;}static
 void z3ccb151752(struct list_head*z4464c6f5dc){struct sched_cluster*cluster,*
zb9b0dca770;int z5d971be8b8;list_for_each_entry_safe(cluster,zb9b0dca770,
z4464c6f5dc,list){for_each_cpu(z5d971be8b8,&cluster->cpus)cpu_rq(z5d971be8b8)->
cluster=&z2d02e5bf36;list_del(&cluster->list);num_sched_clusters--;kfree(cluster
);}}static int zb1d505f198(struct sched_cluster*cluster){int capacity=
(0x1756+3439-0x20c5);capacity*=((0x1154+2599-0x177b)*cluster->efficiency)/
min_possible_efficiency;capacity>>=(0x47b+117-0x4e6);capacity*=(
(0xe06+6029-0x2193)*cluster->max_possible_freq)/min_max_freq;capacity>>=
(0x351+3187-0xfba);return capacity;}unsigned int max_power_cost=
(0x23ac+319-0x24ea);static int z9e1f99ebe0(void*z64e0e8cc28,struct list_head*
z6268ff8549,struct list_head*z2e962a7c2f){struct sched_cluster*z82a09781dc,*
z73f10f0abe;int z083920bcc8;z82a09781dc=container_of(z6268ff8549,struct 
sched_cluster,list);z73f10f0abe=container_of(z2e962a7c2f,struct sched_cluster,
list);z083920bcc8=z82a09781dc->max_power_cost>z73f10f0abe->max_power_cost||(
z82a09781dc->max_power_cost==z73f10f0abe->max_power_cost&&z82a09781dc->
max_possible_capacity<z73f10f0abe->max_possible_capacity);return z083920bcc8;}
static inline void assign_cluster_ids(struct list_head*z4464c6f5dc){struct 
sched_cluster*cluster;int z7609b61ad1=(0x3e9+8118-0x239f);list_for_each_entry(
cluster,z4464c6f5dc,list){cluster->id=z7609b61ad1;sched_cluster[z7609b61ad1++]=
cluster;}WARN_ON(z7609b61ad1>MAX_NR_CLUSTERS);}static inline void move_list(
struct list_head*z6f47937b7c,struct list_head*z792740f2d5,bool z0a017c4f94){
struct list_head*zc4b85e3bbe,*zc636d24b23;zc4b85e3bbe=z792740f2d5->next;
zc636d24b23=z792740f2d5->prev;if(z0a017c4f94){INIT_LIST_HEAD_RCU(z792740f2d5);
synchronize_rcu();}zc4b85e3bbe->prev=z6f47937b7c;z6f47937b7c->prev=zc636d24b23;
zc636d24b23->next=z6f47937b7c;smp_mb();z6f47937b7c->next=zc4b85e3bbe;}void 
z31f93e0c52(void){struct sched_cluster*cluster;struct list_head zd94226e3b2;
unsigned int ze92e4e02ed=(0x2127+949-0x24db);INIT_LIST_HEAD(&zd94226e3b2);
for_each_sched_cluster(cluster){cluster->max_power_cost=power_cost(
cluster_first_cpu(cluster),max_task_load());cluster->min_power_cost=power_cost(
cluster_first_cpu(cluster),(0x83+6598-0x1a49));if(cluster->max_power_cost>
ze92e4e02ed)ze92e4e02ed=cluster->max_power_cost;}max_power_cost=ze92e4e02ed;
move_list(&zd94226e3b2,&cluster_head,true);list_sort(NULL,&zd94226e3b2,
z9e1f99ebe0);assign_cluster_ids(&zd94226e3b2);move_list(&cluster_head,&
zd94226e3b2,false);}static void z4ceaf4cda7(void){struct sched_cluster*cluster;
u64 za85cf99964=(0xfe2+3067-0x1bdd),zd350724547=U64_MAX;unsigned long flags;
z04b55e82dd(cpu_possible_mask,&flags);for_each_sched_cluster(cluster){u64 
z58a329c64d;z58a329c64d=cluster->max_possible_capacity=zb1d505f198(cluster);
cluster->exec_scale_factor=DIV_ROUND_UP(cluster->efficiency*(0x116f+4258-0x1e11)
,max_possible_efficiency);if(z58a329c64d>za85cf99964)za85cf99964=z58a329c64d;if(
z58a329c64d<zd350724547)zd350724547=z58a329c64d;}max_possible_capacity=
za85cf99964;min_max_possible_capacity=zd350724547;zfbcbf0e27a();zbe61fad8ce(
cpu_possible_mask,&flags);}void update_cluster_topology(void){struct cpumask 
cpus=*cpu_possible_mask;const struct cpumask*zf48c6e4ef8;struct sched_cluster*
cluster;struct list_head zd94226e3b2;int z5d971be8b8;INIT_LIST_HEAD(&zd94226e3b2
);for_each_cpu(z5d971be8b8,&cpus){zf48c6e4ef8=topology_possible_sibling_cpumask(
z5d971be8b8);if(cpumask_empty(zf48c6e4ef8)){WARN((0x1aa3+1534-0x20a0),
"\x57\x41\x4c\x54\x3a\x20\x49\x6e\x76\x61\x6c\x69\x64\x20\x63\x70\x75\x20\x74\x6f\x70\x6f\x6c\x6f\x67\x79\x21\x21"
);z3ccb151752(&zd94226e3b2);return;}cpumask_andnot(&cpus,&cpus,zf48c6e4ef8);
z2273ecae7d(zf48c6e4ef8,&zd94226e3b2);}assign_cluster_ids(&zd94226e3b2);
move_list(&cluster_head,&zd94226e3b2,false);z4ceaf4cda7();for_each_sched_cluster
(cluster){if(cpumask_weight(&cluster->cpus)==(0x1686+642-0x1907))cpumask_or(&
asym_cap_sibling_cpus,&asym_cap_sibling_cpus,&cluster->cpus);}if(cpumask_weight(
&asym_cap_sibling_cpus)==(0x1d63+1412-0x22e6))cpumask_clear(&
asym_cap_sibling_cpus);}static unsigned long zd32227a91e[NR_CPUS];static int 
z67e73a304b(struct notifier_block*z9e976b309a,unsigned long zc94d3d8015,void*
data){struct cpufreq_policy*policy=(struct cpufreq_policy*)data;struct 
sched_cluster*cluster=NULL;struct cpumask za6602efd51=*policy->related_cpus;
unsigned int z8192744c36=(0x249f+252-0x259b);int z5d971be8b8,z2dc758aa44,
z9cbef1f657=(0x2b2+5763-0x1935);if(zc94d3d8015!=CPUFREQ_CREATE_POLICY)return
(0x2da+8770-0x251c);max_possible_freq=max(max_possible_freq,policy->cpuinfo.
max_freq);if(min_max_freq==(0xf92+5024-0x2331))min_max_freq=UINT_MAX;
min_max_freq=min(min_max_freq,policy->cpuinfo.max_freq);z609fba09ac(!
min_max_freq);z609fba09ac(!policy->max);for_each_cpu(z5d971be8b8,&za6602efd51)
zd32227a91e[z5d971be8b8]=policy->cpuinfo.max_freq;for_each_cpu(z5d971be8b8,&
za6602efd51){cluster=cpu_rq(z5d971be8b8)->cluster;cpumask_andnot(&za6602efd51,&
za6602efd51,&cluster->cpus);z8192744c36=cluster->max_freq;cluster->min_freq=
policy->min;cluster->max_freq=policy->max;cluster->cur_freq=policy->cur;if(!
cluster->freq_init_done){mutex_lock(&z6e47d2c346);for_each_cpu(z2dc758aa44,&
cluster->cpus)cpumask_copy(&cpu_rq(z2dc758aa44)->freq_domain_cpumask,policy->
related_cpus);cluster->max_possible_freq=policy->cpuinfo.max_freq;cluster->
max_possible_capacity=zb1d505f198(cluster);cluster->freq_init_done=true;
z31f93e0c52();z4ceaf4cda7();mutex_unlock(&z6e47d2c346);continue;}z9cbef1f657+=(
z8192744c36!=cluster->max_freq);}if(z9cbef1f657)zc55fd0bd6e(policy->related_cpus
);return(0xe4a+4038-0x1e10);}static struct notifier_block z484a0e2bc8={.
notifier_call=z67e73a304b};static int z1b3d573ceb(struct notifier_block*
z9e976b309a,unsigned long zc94d3d8015,void*data){struct cpufreq_freqs*
zbd4095257b=(struct cpufreq_freqs*)data;unsigned int cpu=zbd4095257b->policy->
cpu,z21186056ab=zbd4095257b->new;unsigned long flags;struct sched_cluster*
cluster;struct cpumask z6dfb01003b=cpu_rq(cpu)->freq_domain_cpumask;int 
z5d971be8b8,z2dc758aa44;if(z3b880410aa)return NOTIFY_DONE;if(zc94d3d8015!=
CPUFREQ_POSTCHANGE)return NOTIFY_DONE;if(cpu_cur_freq(cpu)==z21186056ab)return 
NOTIFY_OK;for_each_cpu(z5d971be8b8,&z6dfb01003b){cluster=cpu_rq(z5d971be8b8)->
cluster;for_each_cpu(z2dc758aa44,&cluster->cpus){struct rq*rq=cpu_rq(z2dc758aa44
);raw_spin_lock_irqsave(&rq->lock,flags);walt_update_task_ravg(rq->curr,rq,
TASK_UPDATE,sched_ktime_clock(),(0x10d6+4924-0x2412));raw_spin_unlock_irqrestore
(&rq->lock,flags);}cluster->cur_freq=z21186056ab;cpumask_andnot(&z6dfb01003b,&
z6dfb01003b,&cluster->cpus);}return NOTIFY_OK;}static struct notifier_block 
zcc7354a27f={.notifier_call=z1b3d573ceb};static int z0b2479e1f9(void){int 
z083920bcc8;z083920bcc8=cpufreq_register_notifier(&z484a0e2bc8,
CPUFREQ_POLICY_NOTIFIER);if(!z083920bcc8)z083920bcc8=cpufreq_register_notifier(&
zcc7354a27f,CPUFREQ_TRANSITION_NOTIFIER);return z083920bcc8;}core_initcall(
z0b2479e1f9);int register_cpu_cycle_counter_cb(struct cpu_cycle_counter_cb*
z5303ed5f85){unsigned long flags;mutex_lock(&z6e47d2c346);if(!z5303ed5f85->
get_cpu_cycle_counter){mutex_unlock(&z6e47d2c346);return-EINVAL;}z04b55e82dd(
cpu_possible_mask,&flags);cpu_cycle_counter_cb=*z5303ed5f85;z3b880410aa=true;
zbe61fad8ce(cpu_possible_mask,&flags);mutex_unlock(&z6e47d2c346);
cpufreq_unregister_notifier(&zcc7354a27f,CPUFREQ_TRANSITION_NOTIFIER);return
(0x1624+2839-0x213b);}static void z2c39f55a97(struct rq*rq,struct 
related_thread_group*grp,struct task_struct*z0609dbaf9d,int z3205babe24);
unsigned int __read_mostly z38c9c057a0;unsigned int __read_mostly 
sysctl_sched_coloc_downmigrate_ns;struct related_thread_group*z7c7bf2c77f[
MAX_NUM_CGROUP_COLOC_ID];static LIST_HEAD(z929dec1bfc);static DEFINE_RWLOCK(
zc37082022e);static inline void zb7252e9a3d(struct related_thread_group*grp,u64 
demand,bool zf4f061ddc1){if(zf4f061ddc1){grp->skip_min=false;return;}if(
is_suh_max())demand=sched_group_upmigrate;if(!grp->skip_min){if(demand>=
sched_group_upmigrate){grp->skip_min=true;}return;}if(demand<
sched_group_downmigrate){if(!sysctl_sched_coloc_downmigrate_ns){grp->skip_min=
false;return;}if(!grp->downmigrate_ts){grp->downmigrate_ts=grp->last_update;
return;}if(grp->last_update-grp->downmigrate_ts>
sysctl_sched_coloc_downmigrate_ns){grp->downmigrate_ts=(0x38d+5904-0x1a9d);grp->
skip_min=false;}}else if(grp->downmigrate_ts)grp->downmigrate_ts=
(0x28+7770-0x1e82);}int preferred_cluster(struct sched_cluster*cluster,struct 
task_struct*z0609dbaf9d){struct related_thread_group*grp;int z094475d445=-
(0xb4f+6139-0x2349);rcu_read_lock();grp=task_related_thread_group(z0609dbaf9d);
if(grp)z094475d445=(sched_cluster[(int)grp->skip_min]==cluster||cpumask_subset(&
cluster->cpus,&asym_cap_sibling_cpus));rcu_read_unlock();return z094475d445;}
static void zb53071212f(struct related_thread_group*grp){struct task_struct*
z0609dbaf9d;u64 zd26a455a6d=(0x1b75+2818-0x2677);bool z509eaf33de=false;u64 
z790680e4aa;bool z4288c41a52=grp->skip_min;if(list_empty(&grp->tasks)){grp->
skip_min=false;goto ze1f307999b;}if(!hmp_capable()){grp->skip_min=false;goto 
ze1f307999b;}z790680e4aa=sched_ktime_clock();if(z790680e4aa-grp->last_update<
sched_ravg_window/(0xef8+31-0xf0d))return;list_for_each_entry(z0609dbaf9d,&grp->
tasks,grp_list){if(task_boost_policy(z0609dbaf9d)==SCHED_BOOST_ON_BIG){
z509eaf33de=true;break;}if(z0609dbaf9d->ravg.mark_start<z790680e4aa-(
sched_ravg_window*za591b9e54c))continue;zd26a455a6d+=z0609dbaf9d->ravg.
coloc_demand;if(!trace_sched_set_preferred_cluster_enabled()){if(zd26a455a6d>
sched_group_upmigrate)break;}}grp->last_update=z790680e4aa;zb7252e9a3d(grp,
zd26a455a6d,z509eaf33de);trace_sched_set_preferred_cluster(grp,zd26a455a6d);
ze1f307999b:if(grp->id==DEFAULT_CGROUP_COLOC_ID&&grp->skip_min!=z4288c41a52){if(
grp->skip_min)grp->start_ts=sched_clock();sched_update_hyst_times();}}void 
set_preferred_cluster(struct related_thread_group*grp){raw_spin_lock(&grp->lock)
;zb53071212f(grp);raw_spin_unlock(&grp->lock);}int update_preferred_cluster(
struct related_thread_group*grp,struct task_struct*z0609dbaf9d,u32 z3678748cf3,
bool z53c3aaf16d){u32 z30f2685d2b=task_load(z0609dbaf9d);if(!grp)return
(0x53+2499-0xa16);if(unlikely(z53c3aaf16d&&is_suh_max()))return
(0x1c3+4672-0x1402);if(abs(z30f2685d2b-z3678748cf3)>sched_ravg_window/
(0x8f+4151-0x10c2)||sched_ktime_clock()-grp->last_update>sched_ravg_window)
return(0xed7+4113-0x1ee7);return(0x17ac+3363-0x24cf);}
#define zdebf0e8b8a	(0x4eb+1244-0x9c7)
#define z56968f5b11	(0x1a26+669-0x1cc2)
static inline struct related_thread_group*zaf37716888(unsigned int ze3d424fbb1){
return z7c7bf2c77f[ze3d424fbb1];}int alloc_related_thread_groups(void){int 
z5d971be8b8,z083920bcc8;struct related_thread_group*grp;for(z5d971be8b8=
(0x187c+1513-0x1e64);z5d971be8b8<MAX_NUM_CGROUP_COLOC_ID;z5d971be8b8++){grp=
kzalloc(sizeof(*grp),GFP_NOWAIT);if(!grp){z083920bcc8=-ENOMEM;goto z2839a901be;}
grp->id=z5d971be8b8;INIT_LIST_HEAD(&grp->tasks);INIT_LIST_HEAD(&grp->list);
raw_spin_lock_init(&grp->lock);z7c7bf2c77f[z5d971be8b8]=grp;}return
(0x168b+3404-0x23d7);z2839a901be:for(z5d971be8b8=(0x966+769-0xc66);z5d971be8b8<
MAX_NUM_CGROUP_COLOC_ID;z5d971be8b8++){grp=zaf37716888(z5d971be8b8);if(grp){
kfree(grp);z7c7bf2c77f[z5d971be8b8]=NULL;}else{break;}}return z083920bcc8;}
static void z8787eee242(struct task_struct*z0609dbaf9d){struct 
related_thread_group*grp=z0609dbaf9d->grp;struct rq*rq;int zebef427696=
(0x15bf+1475-0x1b81);struct rq_flags z8d267b09c4;raw_spin_lock(&grp->lock);rq=
__task_rq_lock(z0609dbaf9d,&z8d267b09c4);z2c39f55a97(rq,z0609dbaf9d->grp,
z0609dbaf9d,z56968f5b11);list_del_init(&z0609dbaf9d->grp_list);
rcu_assign_pointer(z0609dbaf9d->grp,NULL);__task_rq_unlock(rq,&z8d267b09c4);if(!
list_empty(&grp->tasks)){zebef427696=(0x3d9+1512-0x9c1);zb53071212f(grp);}
raw_spin_unlock(&grp->lock);if(zebef427696&&grp->id!=DEFAULT_CGROUP_COLOC_ID)
list_del_init(&grp->list);}static int z20198aa4d2(struct task_struct*z0609dbaf9d
,struct related_thread_group*grp){struct rq*rq;struct rq_flags z8d267b09c4;
raw_spin_lock(&grp->lock);rq=__task_rq_lock(z0609dbaf9d,&z8d267b09c4);
z2c39f55a97(rq,grp,z0609dbaf9d,zdebf0e8b8a);list_add(&z0609dbaf9d->grp_list,&grp
->tasks);rcu_assign_pointer(z0609dbaf9d->grp,grp);__task_rq_unlock(rq,&
z8d267b09c4);zb53071212f(grp);raw_spin_unlock(&grp->lock);return
(0x80d+1409-0xd8e);}void add_new_task_to_grp(struct task_struct*new){unsigned 
long flags;struct related_thread_group*grp;struct task_struct*z38944a4944=new->
group_leader;unsigned int zd6dfed7cd3=sched_get_group_id(z38944a4944);if(!
z38c9c057a0&&zd6dfed7cd3!=DEFAULT_CGROUP_COLOC_ID)return;if(thread_group_leader(
new))return;if(zd6dfed7cd3==DEFAULT_CGROUP_COLOC_ID){if(!(task_group(new)==
task_group(z38944a4944)))return;}write_lock_irqsave(&zc37082022e,flags);
rcu_read_lock();grp=task_related_thread_group(z38944a4944);rcu_read_unlock();if(
!grp||new->grp){write_unlock_irqrestore(&zc37082022e,flags);return;}
raw_spin_lock(&grp->lock);rcu_assign_pointer(new->grp,grp);list_add(&new->
grp_list,&grp->tasks);raw_spin_unlock(&grp->lock);write_unlock_irqrestore(&
zc37082022e,flags);}static int z3f0a317889(struct task_struct*z0609dbaf9d,
unsigned int ze3d424fbb1){int z094475d445=(0x1071+1727-0x1730);unsigned long 
flags;struct related_thread_group*grp=NULL;if(ze3d424fbb1>=
MAX_NUM_CGROUP_COLOC_ID)return-EINVAL;raw_spin_lock_irqsave(&z0609dbaf9d->
pi_lock,flags);write_lock(&zc37082022e);if((current!=z0609dbaf9d&&z0609dbaf9d->
flags&PF_EXITING)||(!z0609dbaf9d->grp&&!ze3d424fbb1)||(z0609dbaf9d->grp&&
ze3d424fbb1))goto z02a8afcd23;if(!ze3d424fbb1){z8787eee242(z0609dbaf9d);goto 
z02a8afcd23;}grp=zaf37716888(ze3d424fbb1);if(list_empty(&grp->list))list_add(&
grp->list,&z929dec1bfc);z094475d445=z20198aa4d2(z0609dbaf9d,grp);z02a8afcd23:
write_unlock(&zc37082022e);raw_spin_unlock_irqrestore(&z0609dbaf9d->pi_lock,
flags);return z094475d445;}int sched_set_group_id(struct task_struct*z0609dbaf9d
,unsigned int ze3d424fbb1){if(ze3d424fbb1==DEFAULT_CGROUP_COLOC_ID)return-EINVAL
;return z3f0a317889(z0609dbaf9d,ze3d424fbb1);}unsigned int sched_get_group_id(
struct task_struct*z0609dbaf9d){unsigned int ze3d424fbb1;struct 
related_thread_group*grp;rcu_read_lock();grp=task_related_thread_group(
z0609dbaf9d);ze3d424fbb1=grp?grp->id:(0x1bf2+1899-0x235d);rcu_read_unlock();
return ze3d424fbb1;}
#if defined(CONFIG_SCHED_TUNE)
static int __init z9d6579065e(void){struct related_thread_group*grp=NULL;
unsigned long flags;grp=zaf37716888(DEFAULT_CGROUP_COLOC_ID);write_lock_irqsave(
&zc37082022e,flags);list_add(&grp->list,&z929dec1bfc);write_unlock_irqrestore(&
zc37082022e,flags);return(0x102b+231-0x1112);}late_initcall(z9d6579065e);int 
sync_cgroup_colocation(struct task_struct*z0609dbaf9d,bool z605be289c8){unsigned
 int z76b79b2ac3=z605be289c8?DEFAULT_CGROUP_COLOC_ID:(0x1ada+1430-0x2070);return
 z3f0a317889(z0609dbaf9d,z76b79b2ac3);}
#endif
static bool z0bb76a2e0a(struct sched_cluster*cluster){struct 
related_thread_group*grp;bool z3b12e8b981;grp=zaf37716888(
DEFAULT_CGROUP_COLOC_ID);if(!grp)return false;z3b12e8b981=!grp->skip_min&&(
sched_boost_policy()!=SCHED_BOOST_ON_BIG);return(is_min_capacity_cluster(cluster
)==z3b12e8b981);}static unsigned long z02784f0b7d[NR_CPUS];static unsigned long 
z93f1afe3f9[NR_CPUS];unsigned long thermal_cap(int cpu){return z93f1afe3f9[cpu]?
:SCHED_CAPACITY_SCALE;}unsigned long za877a3f404(int cpu,unsigned long 
z83b213a9c5){struct rq*rq=cpu_rq(cpu);
#ifdef CONFIG_ENERGY_MODEL
int zc635079501;struct root_domain*rd=rq->rd;struct perf_domain*pd;unsigned long
 zbd4095257b,ze613a69699;if(!z02784f0b7d[cpu]){rcu_read_lock();pd=
rcu_dereference(rd->pd);if(!pd||!pd->em_pd||!pd->em_pd->table){rcu_read_unlock()
;return rq->cpu_capacity_orig;}zc635079501=em_pd_nr_cap_states(pd->em_pd);
ze613a69699=arch_scale_cpu_capacity(cpu);zbd4095257b=pd->em_pd->table[
zc635079501-(0xcaa+1729-0x136a)].frequency;z02784f0b7d[cpu]=DIV_ROUND_UP(
ze613a69699*zbd4095257b,zd32227a91e[cpu]);rcu_read_unlock();}
#endif
if(zd32227a91e[cpu])return div64_ul(z83b213a9c5*z02784f0b7d[cpu],zd32227a91e[cpu
]);else return rq->cpu_capacity_orig;}static DEFINE_SPINLOCK(
cpu_freq_min_max_lock);void sched_update_cpu_freq_min_max(const cpumask_t*cpus,
u32 z6d51f2da16,u32 za52cccd9d0){struct cpumask cpumask;struct sched_cluster*
cluster;int z5d971be8b8,z9cbef1f657=(0x281+4697-0x14da);unsigned long flags;
spin_lock_irqsave(&cpu_freq_min_max_lock,flags);cpumask_copy(&cpumask,cpus);
for_each_cpu(z5d971be8b8,&cpumask)z93f1afe3f9[z5d971be8b8]=za877a3f404(
z5d971be8b8,za52cccd9d0);for_each_cpu(z5d971be8b8,&cpumask){cluster=cpu_rq(
z5d971be8b8)->cluster;cpumask_andnot(&cpumask,&cpumask,&cluster->cpus);
z9cbef1f657+=(cluster->max_mitigated_freq!=za52cccd9d0);cluster->
max_mitigated_freq=za52cccd9d0;}spin_unlock_irqrestore(&cpu_freq_min_max_lock,
flags);if(z9cbef1f657)zc55fd0bd6e(cpus);}void note_task_waking(struct 
task_struct*z0609dbaf9d,u64 z790680e4aa){z0609dbaf9d->last_wake_ts=z790680e4aa;}
static void z2c39f55a97(struct rq*rq,struct related_thread_group*grp,struct 
task_struct*z0609dbaf9d,int z3205babe24){u64 z790680e4aa;struct group_cpu_time*
z627d50b29d;u64*z42b4427a2c,*z2e4da9dbb4;u64*z262b512e81,*z086b45bedf;u64*
zf7e69c10fd,*z847919a57a;u64*z7ba10de4f4,*z082a99fd0f;int z0504870d67;int cpu=
cpu_of(rq);bool z5eebbbffe9;int z5d971be8b8;z790680e4aa=sched_ktime_clock();
walt_update_task_ravg(rq->curr,rq,TASK_UPDATE,z790680e4aa,(0xa9a+2791-0x1581));
walt_update_task_ravg(z0609dbaf9d,rq,TASK_UPDATE,z790680e4aa,
(0x13eb+3813-0x22d0));z5eebbbffe9=is_new_task(z0609dbaf9d);z627d50b29d=&rq->
grp_time;if(z3205babe24==zdebf0e8b8a){z0504870d67=RQ_TO_GROUP;z42b4427a2c=&rq->
curr_runnable_sum;z2e4da9dbb4=&z627d50b29d->curr_runnable_sum;z262b512e81=&rq->
prev_runnable_sum;z086b45bedf=&z627d50b29d->prev_runnable_sum;zf7e69c10fd=&rq->
nt_curr_runnable_sum;z847919a57a=&z627d50b29d->nt_curr_runnable_sum;z7ba10de4f4=
&rq->nt_prev_runnable_sum;z082a99fd0f=&z627d50b29d->nt_prev_runnable_sum;if(*
z42b4427a2c<z0609dbaf9d->ravg.curr_window_cpu[cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,cpu,z3205babe24,*z42b4427a2c,z0609dbaf9d->ravg.curr_window_cpu
[cpu]);z1efe882752(z0609dbaf9d);z609fba09ac((0x709+6498-0x206a));}*z42b4427a2c-=
z0609dbaf9d->ravg.curr_window_cpu[cpu];if(*z262b512e81<z0609dbaf9d->ravg.
prev_window_cpu[cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,cpu,z3205babe24,*z262b512e81,z0609dbaf9d->ravg.prev_window_cpu
[cpu]);z1efe882752(z0609dbaf9d);z609fba09ac((0x191+1480-0x758));}*z262b512e81-=
z0609dbaf9d->ravg.prev_window_cpu[cpu];if(z5eebbbffe9){if(*zf7e69c10fd<
z0609dbaf9d->ravg.curr_window_cpu[cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,cpu,z3205babe24,*zf7e69c10fd,z0609dbaf9d->ravg.curr_window_cpu
[cpu]);z1efe882752(z0609dbaf9d);z609fba09ac((0x343+1661-0x9bf));}*zf7e69c10fd-=
z0609dbaf9d->ravg.curr_window_cpu[cpu];if(*z7ba10de4f4<z0609dbaf9d->ravg.
prev_window_cpu[cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,cpu,z3205babe24,*z7ba10de4f4,z0609dbaf9d->ravg.prev_window_cpu
[cpu]);z1efe882752(z0609dbaf9d);z609fba09ac((0x16c+4515-0x130e));}*z7ba10de4f4-=
z0609dbaf9d->ravg.prev_window_cpu[cpu];}z0dd808419c(z0609dbaf9d,cpu,rq->
window_start,z5eebbbffe9);}else{z0504870d67=GROUP_TO_RQ;z42b4427a2c=&z627d50b29d
->curr_runnable_sum;z2e4da9dbb4=&rq->curr_runnable_sum;z262b512e81=&z627d50b29d
->prev_runnable_sum;z086b45bedf=&rq->prev_runnable_sum;zf7e69c10fd=&z627d50b29d
->nt_curr_runnable_sum;z847919a57a=&rq->nt_curr_runnable_sum;z7ba10de4f4=&
z627d50b29d->nt_prev_runnable_sum;z082a99fd0f=&rq->nt_prev_runnable_sum;if(*
z42b4427a2c<z0609dbaf9d->ravg.curr_window){printk_deferred(
"\x57\x41\x4c\x54\x2d\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,cpu,z3205babe24,*z42b4427a2c,z0609dbaf9d->ravg.curr_window);
z1efe882752(z0609dbaf9d);z609fba09ac((0x899+5379-0x1d9b));}*z42b4427a2c-=
z0609dbaf9d->ravg.curr_window;if(*z262b512e81<z0609dbaf9d->ravg.prev_window){
printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,cpu,z3205babe24,*z262b512e81,z0609dbaf9d->ravg.prev_window);
z1efe882752(z0609dbaf9d);z609fba09ac((0x8ba+4371-0x19cc));}*z262b512e81-=
z0609dbaf9d->ravg.prev_window;if(z5eebbbffe9){if(*zf7e69c10fd<z0609dbaf9d->ravg.
curr_window){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,cpu,z3205babe24,*zf7e69c10fd,z0609dbaf9d->ravg.curr_window);
z1efe882752(z0609dbaf9d);z609fba09ac((0x626+5169-0x1a56));}*zf7e69c10fd-=
z0609dbaf9d->ravg.curr_window;if(*z7ba10de4f4<z0609dbaf9d->ravg.prev_window){
printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,z0609dbaf9d->pid,cpu,z3205babe24,*z7ba10de4f4,z0609dbaf9d->ravg.prev_window);
z1efe882752(z0609dbaf9d);z609fba09ac((0xfdb+1752-0x16b2));}*z7ba10de4f4-=
z0609dbaf9d->ravg.prev_window;}for_each_possible_cpu(z5d971be8b8){z0609dbaf9d->
ravg.curr_window_cpu[z5d971be8b8]=(0x850+1123-0xcb3);z0609dbaf9d->ravg.
prev_window_cpu[z5d971be8b8]=(0x154+4305-0x1225);}}*z2e4da9dbb4+=z0609dbaf9d->
ravg.curr_window;*z086b45bedf+=z0609dbaf9d->ravg.prev_window;if(z5eebbbffe9){*
z847919a57a+=z0609dbaf9d->ravg.curr_window;*z082a99fd0f+=z0609dbaf9d->ravg.
prev_window;}z0609dbaf9d->ravg.curr_window_cpu[cpu]=z0609dbaf9d->ravg.
curr_window;z0609dbaf9d->ravg.prev_window_cpu[cpu]=z0609dbaf9d->ravg.prev_window
;trace_sched_migration_update_sum(z0609dbaf9d,z0504870d67,rq);}bool 
is_rtgb_active(void){struct related_thread_group*grp;grp=zaf37716888(
DEFAULT_CGROUP_COLOC_ID);return grp&&grp->skip_min;}u64 get_rtgb_active_time(
void){struct related_thread_group*grp;u64 z2c53bb3f34=sched_clock();grp=
zaf37716888(DEFAULT_CGROUP_COLOC_ID);if(grp&&grp->skip_min&&grp->start_ts)return
 z2c53bb3f34-grp->start_ts;return(0xac8+518-0xcce);}static void z82ef581fb8(void
);static void zaea65e35d7(void){zfbcbf0e27a();z82ef581fb8();}void walt_irq_work(
struct irq_work*irq_work){struct sched_cluster*cluster;struct rq*rq;int cpu;u64 
z0cc0a342b9;bool zd7ac89c463=false,zfc516a8062=false;u64 z392940921f=
(0x823+1856-0xf63),z9ef535cb5f=(0xc98+2232-0x1550);int z8025f196c5=
(0x1039+2790-0x1b1f);u64 zaeec67ca96;unsigned long flags;if(irq_work==&
z72f8d06752)zd7ac89c463=true;for_each_cpu(cpu,cpu_possible_mask){if(z8025f196c5
==(0x13ef+4794-0x26a9))raw_spin_lock(&cpu_rq(cpu)->lock);else 
raw_spin_lock_nested(&cpu_rq(cpu)->lock,z8025f196c5);z8025f196c5++;}z0cc0a342b9=
sched_ktime_clock();zaeec67ca96=get_jiffies_64();walt_load_reported_window=
atomic64_read(&z8d508f7c3b);for_each_sched_cluster(cluster){u64 aggr_grp_load=
(0x479+986-0x853);raw_spin_lock(&cluster->load_lock);for_each_cpu(cpu,&cluster->
cpus){rq=cpu_rq(cpu);if(rq->curr){walt_update_task_ravg(rq->curr,rq,TASK_UPDATE,
z0cc0a342b9,(0xfdf+3279-0x1cae));za647ab699e(rq);aggr_grp_load+=rq->grp_time.
prev_runnable_sum;}if(zd7ac89c463&&rq->notif_pending&&cpumask_test_cpu(cpu,&
asym_cap_sibling_cpus)){zfc516a8062=true;rq->notif_pending=false;}}cluster->
aggr_grp_load=aggr_grp_load;z392940921f+=aggr_grp_load;if(
is_min_capacity_cluster(cluster))z9ef535cb5f=aggr_grp_load;raw_spin_unlock(&
cluster->load_lock);}if(z392940921f){if(cpumask_weight(&asym_cap_sibling_cpus)){
u64 z2a9650c76f=z392940921f-z9ef535cb5f;for_each_cpu(cpu,&asym_cap_sibling_cpus)
cpu_cluster(cpu)->aggr_grp_load=z2a9650c76f;}rtgb_active=is_rtgb_active();}else{
rtgb_active=false;}if(!zd7ac89c463&&sysctl_sched_user_hint&&time_after(jiffies,
zfac0edc4a3))sysctl_sched_user_hint=(0x401+812-0x72d);for_each_sched_cluster(
cluster){cpumask_t z8fc9e418fd;unsigned int z3fc386a32e,z5d971be8b8=
(0xd51+3740-0x1bec);cpumask_and(&z8fc9e418fd,&cluster->cpus,cpu_online_mask);
z3fc386a32e=cpumask_weight(&z8fc9e418fd);for_each_cpu(cpu,&z8fc9e418fd){int 
z26b84a07e7=SCHED_CPUFREQ_WALT;rq=cpu_rq(cpu);if(zd7ac89c463){if(rq->
notif_pending){z26b84a07e7|=SCHED_CPUFREQ_INTERCLUSTER_MIG;rq->notif_pending=
false;}}if(zfc516a8062&&cpumask_test_cpu(cpu,&asym_cap_sibling_cpus))z26b84a07e7
|=SCHED_CPUFREQ_INTERCLUSTER_MIG;if(z5d971be8b8==z3fc386a32e)cpufreq_update_util
(cpu_rq(cpu),z26b84a07e7);else cpufreq_update_util(cpu_rq(cpu),z26b84a07e7|
SCHED_CPUFREQ_CONTINUE);z5d971be8b8++;if(rq->high_irqload)rq->high_irqload=(
zaeec67ca96-rq->irqload_ts<SCHED_HIGH_IRQ_TIMEOUT);}}if(!zd7ac89c463){
spin_lock_irqsave(&z19d7dae9b5,flags);if(sched_ravg_window!=z95efc1452f){
zc6e1c5745d=sched_ktime_clock();printk_deferred(
"\x41\x4c\x45\x52\x54\x3a\x20\x63\x68\x61\x6e\x67\x69\x6e\x67\x20\x77\x69\x6e\x64\x6f\x77\x20\x73\x69\x7a\x65\x20\x66\x72\x6f\x6d\x20\x25\x75\x20\x74\x6f\x20\x25\x75\x20\x61\x74\x20\x25\x6c\x75" "\n"
,sched_ravg_window,z95efc1452f,zc6e1c5745d);sched_ravg_window=z95efc1452f;
zaea65e35d7();}spin_unlock_irqrestore(&z19d7dae9b5,flags);}for_each_cpu(cpu,
cpu_possible_mask)raw_spin_unlock(&cpu_rq(cpu)->lock);if(!zd7ac89c463)
core_ctl_check(this_rq()->window_start);}void walt_rotation_checkpoint(int 
zbd4d7a57a3){if(!hmp_capable())return;if(!sysctl_sched_walt_rotate_big_tasks||
sched_boost()!=NO_BOOST){walt_rotation_enabled=(0x1400+3131-0x203b);return;}
walt_rotation_enabled=zbd4d7a57a3>=num_possible_cpus();}void walt_fill_ta_data(
struct core_ctl_notif_data*data){struct related_thread_group*grp;unsigned long 
flags;u64 zd8ca2b9a3c=(0x13ef+422-0x1595),z790680e4aa;struct task_struct*
z0609dbaf9d;int zba0d35d300,z4e46740d20=(0x148b+1510-0x1671);struct 
sched_cluster*cluster;int z5d971be8b8=(0x486+1730-0xb48);grp=zaf37716888(
DEFAULT_CGROUP_COLOC_ID);raw_spin_lock_irqsave(&grp->lock,flags);if(list_empty(&
grp->tasks)){raw_spin_unlock_irqrestore(&grp->lock,flags);goto z81c6b6b7f4;}
z790680e4aa=sched_ktime_clock();list_for_each_entry(z0609dbaf9d,&grp->tasks,
grp_list){if(z0609dbaf9d->ravg.mark_start<z790680e4aa-(sched_ravg_window*
za591b9e54c))continue;zd8ca2b9a3c+=z0609dbaf9d->ravg.coloc_demand;}
raw_spin_unlock_irqrestore(&grp->lock,flags);zba0d35d300=this_rq()->rd->
min_cap_orig_cpu;if(zba0d35d300!=-(0x690+1773-0xd7c))z4e46740d20=
arch_scale_cpu_capacity(zba0d35d300);data->coloc_load_pct=div64_u64(zd8ca2b9a3c*
(0xf94+3950-0x1b02)*(0x147a+2724-0x1eba),(u64)sched_ravg_window*z4e46740d20);
z81c6b6b7f4:for_each_sched_cluster(cluster){int z61c3a9ab4e=cluster_first_cpu(
cluster);if(z5d971be8b8==MAX_CLUSTERS)break;z4e46740d20=arch_scale_cpu_capacity(
z61c3a9ab4e);data->ta_util_pct[z5d971be8b8]=div64_u64(cluster->aggr_grp_load*
(0xf5c+5208-0x1fb4)*(0x490+474-0x606),(u64)sched_ravg_window*z4e46740d20);
z4e46740d20=arch_scale_freq_capacity(z61c3a9ab4e);data->cur_cap_pct[z5d971be8b8]
=(z4e46740d20*(0xb17+947-0xe66))/(0x1887+4640-0x26a7);z5d971be8b8++;}}int 
walt_proc_group_thresholds_handler(struct ctl_table*table,int z123284dc15,void 
__user*zfc9cd6af11,size_t*zc6af6558dd,loff_t*z9057b9d303){int z083920bcc8;static
 DEFINE_MUTEX(z8a2c4b3219);struct rq*rq=cpu_rq(cpumask_first(cpu_possible_mask))
;unsigned long flags;mutex_lock(&z8a2c4b3219);z083920bcc8=proc_dointvec_minmax(
table,z123284dc15,zfc9cd6af11,zc6af6558dd,z9057b9d303);if(z083920bcc8||!
z123284dc15){mutex_unlock(&z8a2c4b3219);return z083920bcc8;}
raw_spin_lock_irqsave(&rq->lock,flags);zfbcbf0e27a();raw_spin_unlock_irqrestore(
&rq->lock,flags);mutex_unlock(&z8a2c4b3219);return z083920bcc8;}static void 
z82ef581fb8(void){walt_cpu_util_freq_divisor=(sched_ravg_window>>
SCHED_CAPACITY_SHIFT)*(0x99+7880-0x1efd);zd07944bdc3=sched_ravg_window>>
SCHED_CAPACITY_SHIFT;sched_init_task_load_windows=div64_u64((u64)z8bf7fc10da*(
u64)sched_ravg_window,(0x911+5756-0x1f29));zb0bc76dcf5=zecf40170d4(
sched_init_task_load_windows);}static void z42949ab86e(void){init_irq_work(&
z72f8d06752,walt_irq_work);init_irq_work(&z5bb9cd73e7,walt_irq_work);
walt_rotate_work_init();z82ef581fb8();}void walt_sched_init_rq(struct rq*rq){int
 z2dc758aa44;if(cpu_of(rq)==(0x1cb+7825-0x205c))z42949ab86e();cpumask_set_cpu(
cpu_of(rq),&rq->freq_domain_cpumask);rq->walt_stats.
cumulative_runnable_avg_scaled=(0x5fd+4979-0x1970);rq->prev_window_size=
sched_ravg_window;rq->window_start=(0x12e7+2160-0x1b57);rq->walt_stats.
nr_big_tasks=(0x4bf+5375-0x19be);rq->walt_flags=(0x472+2451-0xe05);rq->
cur_irqload=(0x10bb+2719-0x1b5a);rq->avg_irqload=(0x1d3+884-0x547);rq->
irqload_ts=(0xb7+3154-0xd09);rq->high_irqload=false;rq->task_exec_scale=
(0x19f0+2606-0x201e);rq->push_task=NULL;rq->cluster=&z2d02e5bf36;rq->
curr_runnable_sum=rq->prev_runnable_sum=(0x109b+790-0x13b1);rq->
nt_curr_runnable_sum=rq->nt_prev_runnable_sum=(0x1022+1536-0x1622);memset(&rq->
grp_time,(0x2254+979-0x2627),sizeof(struct group_cpu_time));rq->old_busy_time=
(0xa94+6143-0x2293);rq->old_estimated_time=(0x6b5+1066-0xadf);rq->
old_busy_time_group=(0xfaf+1429-0x1544);rq->walt_stats.pred_demands_sum_scaled=
(0x1209+4855-0x2500);rq->ed_task=NULL;rq->curr_table=(0xfa8+1225-0x1471);rq->
prev_top=(0xd85+2706-0x1817);rq->curr_top=(0x64f+6483-0x1fa2);rq->last_cc_update
=(0x1d49+345-0x1ea2);rq->cycles=(0xbdc+1087-0x101b);for(z2dc758aa44=
(0x1060+5116-0x245c);z2dc758aa44<NUM_TRACKED_WINDOWS;z2dc758aa44++){memset(&rq->
load_subs[z2dc758aa44],(0x941+4135-0x1968),sizeof(struct load_subtractions));rq
->top_tasks[z2dc758aa44]=kcalloc(NUM_LOAD_INDICES,sizeof(u8),GFP_NOWAIT);BUG_ON(
!rq->top_tasks[z2dc758aa44]);z66971bc3d0(rq->top_tasks_bitmap[z2dc758aa44]);}rq
->cum_window_demand_scaled=(0x96+3073-0xc97);rq->notif_pending=false;}int 
z8eaedbdb28(struct ctl_table*table,int z123284dc15,void __user*zfc9cd6af11,
size_t*zc6af6558dd,loff_t*z9057b9d303){int z083920bcc8;unsigned int zed2a7cf76b;
static DEFINE_MUTEX(z8a2c4b3219);mutex_lock(&z8a2c4b3219);zfac0edc4a3=jiffies+HZ
;zed2a7cf76b=sysctl_sched_user_hint;z083920bcc8=proc_dointvec_minmax(table,
z123284dc15,zfc9cd6af11,zc6af6558dd,z9057b9d303);if(z083920bcc8||!z123284dc15||(
zed2a7cf76b==sysctl_sched_user_hint))goto zd0213cc3f9;sched_irq_work_queue(&
z72f8d06752);zd0213cc3f9:mutex_unlock(&z8a2c4b3219);return z083920bcc8;}static 
inline void z39b6f75650(void){int zf55fa86af6;unsigned long flags;
spin_lock_irqsave(&z19d7dae9b5,flags);zf55fa86af6=min(zb67de743f5,
sysctl_sched_ravg_window_nr_ticks);z95efc1452f=zf55fa86af6*(NSEC_PER_SEC/HZ);
spin_unlock_irqrestore(&z19d7dae9b5,flags);}int sched_ravg_window_handler(struct
 ctl_table*table,int z123284dc15,void __user*zfc9cd6af11,size_t*zc6af6558dd,
loff_t*z9057b9d303){int z083920bcc8=-EPERM;static DEFINE_MUTEX(z8a2c4b3219);
unsigned int z7c755fe34d;mutex_lock(&z8a2c4b3219);if(z123284dc15&&(HZ!=
(0x26c+3643-0xfad)||!sysctl_sched_dynamic_ravg_window_enable))goto zd0213cc3f9;
z7c755fe34d=sysctl_sched_ravg_window_nr_ticks;z083920bcc8=
proc_douintvec_ravg_window(table,z123284dc15,zfc9cd6af11,zc6af6558dd,z9057b9d303
);if(z083920bcc8||!z123284dc15||(z7c755fe34d==sysctl_sched_ravg_window_nr_ticks)
)goto zd0213cc3f9;z39b6f75650();zd0213cc3f9:mutex_unlock(&z8a2c4b3219);return 
z083920bcc8;}void sched_set_refresh_rate(enum fps fps){if(HZ==
(0x126+4328-0x1114)&&sysctl_sched_dynamic_ravg_window_enable){if(fps>FPS90)
zb67de743f5=(0x1ec7+1353-0x240e);else if(fps==FPS90)zb67de743f5=
(0x4b1+5282-0x1950);else zb67de743f5=(0x118a+3753-0x202e);z39b6f75650();}}
EXPORT_SYMBOL(sched_set_refresh_rate);
