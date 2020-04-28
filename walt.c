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
#define WALT88b9b0b9ce (0x17b0+537-0x19c9)
#define WALT19b86f3ee0 (0xabf+1211-0xf79)
#define WALT53b6c10420 9500000
#define MAX_NUM_CGROUP_COLOC_ID (0x1577+2283-0x1e4e)
#define WINDOW_STATS_RECENT		(0x117a+3141-0x1dbf)
#define WINDOW_STATS_MAX		(0x886+3873-0x17a6)
#define WINDOW_STATS_MAX_RECENT_AVG	(0x6e3+247-0x7d8)
#define WINDOW_STATS_AVG		(0x1a03+2932-0x2574)
#define WINDOW_STATS_INVALID_POLICY	(0xb41+5772-0x21c9)
#define MAX_NR_CLUSTERS			(0x1bab+563-0x1ddb)
#define FREQ_REPORT_MAX_CPU_LOAD_TOP_TASK	(0x5fc+3790-0x14ca)
#define FREQ_REPORT_CPU_LOAD			(0x974+6388-0x2267)
#define FREQ_REPORT_TOP_TASK			(0xdaf+1346-0x12ef)
#define WALTdbeb076c45 100000000
static ktime_t WALT482beda45b;static bool WALT42c0a8ecd1;static struct 
cpu_cycle_counter_cb cpu_cycle_counter_cb;static bool WALT3b880410aa;static 
DEFINE_MUTEX(WALT6e47d2c346);static atomic64_t WALT8d508f7c3b;static u64 
walt_load_reported_window;static struct irq_work WALT5bb9cd73e7;static struct 
irq_work WALT72f8d06752;u64 sched_ktime_clock(void){if(unlikely(WALT42c0a8ecd1))
return ktime_to_ns(WALT482beda45b);return ktime_get_ns();}static void 
WALTfb3bba3e8e(void){WALT42c0a8ecd1=false;}static int WALT588a01c1cd(void){
WALT482beda45b=ktime_get();WALT42c0a8ecd1=true;return(0xba4+2152-0x140c);}static
 struct syscore_ops WALT3c69fe9894={.resume=WALTfb3bba3e8e,.suspend=
WALT588a01c1cd};static int __init WALT5a716155ff(void){register_syscore_ops(&
WALT3c69fe9894);return(0x588+7267-0x21eb);}late_initcall(WALT5a716155ff);static 
void WALT04b55e82dd(const cpumask_t*cpus,unsigned long*flags){int cpu;int 
WALT8025f196c5=(0x7e3+1100-0xc2f);local_irq_save(*flags);for_each_cpu(cpu,cpus){
if(WALT8025f196c5==(0xc4b+5276-0x20e7))raw_spin_lock(&cpu_rq(cpu)->lock);else 
raw_spin_lock_nested(&cpu_rq(cpu)->lock,WALT8025f196c5);WALT8025f196c5++;}}
static void WALTbe61fad8ce(const cpumask_t*cpus,unsigned long*flags){int cpu;
for_each_cpu(cpu,cpus)raw_spin_unlock(&cpu_rq(cpu)->lock);local_irq_restore(*
flags);}unsigned int sysctl_sched_capacity_margin_up[MAX_MARGIN_LEVELS]={[
(0x196b+497-0x1b5c)...MAX_MARGIN_LEVELS-(0x9e3+6204-0x221e)]=(0x73d+448-0x4c7)};
unsigned int sysctl_sched_capacity_margin_down[MAX_MARGIN_LEVELS]={[
(0xee7+1829-0x160c)...MAX_MARGIN_LEVELS-(0xcb2+80-0xd01)]=(0x69c+5566-0x17a5)};
__read_mostly unsigned int sysctl_sched_cpu_high_irqload=TICK_NSEC;unsigned int 
sysctl_sched_walt_rotate_big_tasks;unsigned int walt_rotation_enabled;
__read_mostly unsigned int sysctl_sched_asym_cap_sibling_freq_match_pct=
(0xa22+1112-0xe16);__read_mostly unsigned int WALTa591b9e54c=(0xe6d+5127-0x226f)
;static __read_mostly unsigned int WALTdedb054041=(0x1041+4741-0x22c5);
__read_mostly unsigned int sysctl_sched_window_stats_policy=
WINDOW_STATS_MAX_RECENT_AVG;unsigned int sysctl_sched_ravg_window_nr_ticks=(HZ/
NR_WINDOWS_PER_SEC);static unsigned int WALTb67de743f5=(HZ/NR_WINDOWS_PER_SEC);
unsigned int sysctl_sched_dynamic_ravg_window_enable=(HZ==(0x1ad+7137-0x1c94));
__read_mostly unsigned int sched_ravg_window=DEFAULT_SCHED_RAVG_WINDOW;
__read_mostly unsigned int WALT95efc1452f=DEFAULT_SCHED_RAVG_WINDOW;static 
DEFINE_SPINLOCK(WALT19d7dae9b5);u64 WALTc6e1c5745d;static __read_mostly unsigned
 int walt_cpu_util_freq_divisor;unsigned int __read_mostly 
sched_init_task_load_windows;unsigned int __read_mostly WALTb0bc76dcf5;unsigned 
int __read_mostly WALT8bf7fc10da=(0x482+1737-0xb3c);unsigned int 
max_possible_capacity=(0x1af5+1352-0x1c3d);unsigned int 
min_max_possible_capacity=(0x1ba7+2239-0x2066);__read_mostly unsigned int 
sched_load_granule=DEFAULT_SCHED_RAVG_WINDOW/NUM_LOAD_INDICES;static const 
unsigned int WALT64333e9737=BITS_TO_LONGS(NUM_LOAD_INDICES+(0xd97+2148-0x15fa))*
sizeof(unsigned long);__read_mostly unsigned int WALTed0bb72c67;static int 
__init WALT365d6e8b5b(char*WALTcf96530e6c){unsigned int WALT4ae816ebd1;
get_option(&WALTcf96530e6c,&WALT4ae816ebd1);if(WALT4ae816ebd1<
DEFAULT_SCHED_RAVG_WINDOW||WALT4ae816ebd1>MAX_SCHED_RAVG_WINDOW){WARN_ON(
(0x1c9+5763-0x184b));return-EINVAL;}sched_ravg_window=WALT4ae816ebd1;return
(0xf54+3350-0x1c6a);}early_param(
"\x73\x63\x68\x65\x64\x5f\x72\x61\x76\x67\x5f\x77\x69\x6e\x64\x6f\x77",
WALT365d6e8b5b);static int __init WALT8c5c1ddf5d(char*WALTcf96530e6c){unsigned 
int WALT23b9d3f649;get_option(&WALTcf96530e6c,&WALT23b9d3f649);sched_predl=!!
WALT23b9d3f649;return(0x1a8d+2325-0x23a2);}early_param(
"\x73\x63\x68\x65\x64\x5f\x70\x72\x65\x64\x6c",WALT8c5c1ddf5d);__read_mostly 
unsigned int WALTd07944bdc3;
#define WALTecf40170d4(WALT68a26cf33f) ((WALT68a26cf33f)/WALTd07944bdc3)
#define WALT33b027c8ca(WALT0dfd61a6cb)        printk_deferred(\
"\x25\x73\x3d\x25\x6c\x6c\x75", #WALT0dfd61a6cb, WALT0dfd61a6cb)
#define WALT19f3dd399d(WALT0dfd61a6cb)               #WALT0dfd61a6cb
static inline void WALT1efe882752(struct task_struct*WALT0609dbaf9d){char 
WALTb49c1cb1d4[NR_CPUS*(0xacf+1048-0xed7)];int WALT5d971be8b8,WALT2dc758aa44=
(0x17e1+1597-0x1e1e);int WALT8c35dbc183=NR_CPUS*(0x462+7928-0x234a);
WALT33b027c8ca(WALT0609dbaf9d->pid);WALT33b027c8ca(WALT0609dbaf9d->ravg.
mark_start);WALT33b027c8ca(WALT0609dbaf9d->ravg.demand);WALT33b027c8ca(
WALT0609dbaf9d->ravg.coloc_demand);WALT33b027c8ca(sched_ravg_window);
WALT33b027c8ca(WALT95efc1452f);for(WALT5d971be8b8=(0x1384+1313-0x18a5);
WALT5d971be8b8<nr_cpu_ids;WALT5d971be8b8++)WALT2dc758aa44+=scnprintf(
WALTb49c1cb1d4+WALT2dc758aa44,WALT8c35dbc183-WALT2dc758aa44,"\x25\x75\x20",
WALT0609dbaf9d->ravg.curr_window_cpu[WALT5d971be8b8]);printk_deferred(
"\x25\x73\x3d\x25\x64\x20\x28\x25\x73\x29" "\n",WALT19f3dd399d(WALT0609dbaf9d->
ravg.curr_window),WALT0609dbaf9d->ravg.curr_window,WALTb49c1cb1d4);for(
WALT5d971be8b8=(0x149b+3253-0x2150),WALT2dc758aa44=(0x466+758-0x75c);
WALT5d971be8b8<nr_cpu_ids;WALT5d971be8b8++)WALT2dc758aa44+=scnprintf(
WALTb49c1cb1d4+WALT2dc758aa44,WALT8c35dbc183-WALT2dc758aa44,"\x25\x75\x20",
WALT0609dbaf9d->ravg.prev_window_cpu[WALT5d971be8b8]);printk_deferred(
"\x25\x73\x3d\x25\x64\x20\x28\x25\x73\x29" "\n",WALT19f3dd399d(WALT0609dbaf9d->
ravg.prev_window),WALT0609dbaf9d->ravg.prev_window,WALTb49c1cb1d4);
WALT33b027c8ca(WALT0609dbaf9d->last_wake_ts);WALT33b027c8ca(WALT0609dbaf9d->
last_enqueued_ts);WALT33b027c8ca(WALT0609dbaf9d->misfit);WALT33b027c8ca(
WALT0609dbaf9d->unfilter);}static inline void WALTbe464df6bf(int cpu){struct rq*
rq=cpu_rq(cpu);struct task_struct*WALTca60978f56=cpu_curr(cpu);int 
WALT5d971be8b8;get_task_struct(WALTca60978f56);printk_deferred(
"\x43\x50\x55\x3a\x25\x64\x20\x6e\x72\x5f\x72\x75\x6e\x6e\x69\x6e\x67\x3a\x25\x75\x20\x63\x75\x72\x72\x65\x6e\x74\x3a\x20\x25\x64\x20\x28\x25\x73\x29" "\n"
,cpu,rq->nr_running,WALTca60978f56->pid,WALTca60978f56->comm);printk_deferred(
"\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d"
);WALT33b027c8ca(rq->window_start);WALT33b027c8ca(rq->prev_window_size);
WALT33b027c8ca(rq->curr_runnable_sum);WALT33b027c8ca(rq->prev_runnable_sum);
WALT33b027c8ca(rq->nt_curr_runnable_sum);WALT33b027c8ca(rq->nt_prev_runnable_sum
);WALT33b027c8ca(rq->cum_window_demand_scaled);WALT33b027c8ca(rq->
task_exec_scale);WALT33b027c8ca(rq->grp_time.curr_runnable_sum);WALT33b027c8ca(
rq->grp_time.prev_runnable_sum);WALT33b027c8ca(rq->grp_time.nt_curr_runnable_sum
);WALT33b027c8ca(rq->grp_time.nt_prev_runnable_sum);for(WALT5d971be8b8=
(0xa57+3457-0x17d8);WALT5d971be8b8<NUM_TRACKED_WINDOWS;WALT5d971be8b8++){
printk_deferred(
"\x72\x71\x2d\x3e\x6c\x6f\x61\x64\x5f\x73\x75\x62\x73\x5b\x25\x64\x5d\x2e\x77\x69\x6e\x64\x6f\x77\x5f\x73\x74\x61\x72\x74\x3d\x25\x6c\x6c\x75\x29" "\n"
,WALT5d971be8b8,rq->load_subs[WALT5d971be8b8].window_start);printk_deferred(
"\x72\x71\x2d\x3e\x6c\x6f\x61\x64\x5f\x73\x75\x62\x73\x5b\x25\x64\x5d\x2e\x73\x75\x62\x73\x3d\x25\x6c\x6c\x75\x29" "\n"
,WALT5d971be8b8,rq->load_subs[WALT5d971be8b8].subs);printk_deferred(
"\x72\x71\x2d\x3e\x6c\x6f\x61\x64\x5f\x73\x75\x62\x73\x5b\x25\x64\x5d\x2e\x6e\x65\x77\x5f\x73\x75\x62\x73\x3d\x25\x6c\x6c\x75\x29" "\n"
,WALT5d971be8b8,rq->load_subs[WALT5d971be8b8].new_subs);}if(!exiting_task(
WALTca60978f56))WALT1efe882752(WALTca60978f56);WALT33b027c8ca(
sched_capacity_margin_up[cpu]);WALT33b027c8ca(sched_capacity_margin_down[cpu]);}
static inline void WALT71e92e3d78(void){int cpu;printk_deferred(
"\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x20\x57\x41\x4c\x54\x20\x52\x51\x20\x44\x55\x4d\x50\x20\x53\x54\x41\x52\x54\x20\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d" "\n"
);printk_deferred(
"\x53\x63\x68\x65\x64\x20\x6b\x74\x69\x6d\x65\x5f\x67\x65\x74\x3a\x20\x25\x6c\x6c\x75" "\n"
,sched_ktime_clock());printk_deferred(
"\x54\x69\x6d\x65\x20\x6c\x61\x73\x74\x20\x77\x69\x6e\x64\x6f\x77\x20\x63\x68\x61\x6e\x67\x65\x64\x3d\x25\x6c\x75" "\n"
,WALTc6e1c5745d);for_each_online_cpu(cpu)WALTbe464df6bf(cpu);WALT33b027c8ca(
max_possible_capacity);WALT33b027c8ca(min_max_possible_capacity);printk_deferred
(
"\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x20\x57\x41\x4c\x54\x20\x52\x51\x20\x44\x55\x4d\x50\x20\x45\x4e\x44\x20\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d\x3d" "\n"
);}static int WALT22b60684f8;
#define WALT609fba09ac(WALT8f713ea8e0)				\
({							\
	if (unlikely(!!(WALT8f713ea8e0)) && !WALT22b60684f8) {	\
		WALT22b60684f8 = (0x8c5+5209-0x1d1d);			\
		WALT71e92e3d78();				\
		BUG_ON(WALT8f713ea8e0);			\
	}						\
})
static inline void WALTa4ccf3d6c9(struct irq_work*WALT9932a7275f){if(likely(
cpu_online(raw_smp_processor_id())))irq_work_queue(WALT9932a7275f);else 
irq_work_queue_on(WALT9932a7275f,cpumask_any(cpu_online_mask));}static void 
WALT69efd235f7(struct rq*rq,struct task_struct*WALT0609dbaf9d,u16 WALT8143bfdfea
,u16 WALT77a2404d60){s64 WALTad18716537=(s64)WALT8143bfdfea-WALT0609dbaf9d->ravg
.demand_scaled;s64 WALT5ae7e7adb9=(s64)WALT77a2404d60-WALT0609dbaf9d->ravg.
pred_demand_scaled;fixup_cumulative_runnable_avg(&rq->walt_stats,WALTad18716537,
WALT5ae7e7adb9);walt_fixup_cum_window_demand(rq,WALTad18716537);}__read_mostly 
bool sched_freq_aggr_en;static u64 WALT6bdc3765bb(struct rq*rq,u64 
WALT790680e4aa,int WALT3205babe24){s64 WALT17abc14e87;int WALT09570395b5;u64 
WALT901ba13dc5=rq->window_start;WALT17abc14e87=WALT790680e4aa-rq->window_start;
if(WALT17abc14e87<(0x16d+2110-0x9ab)){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x43\x50\x55\x25\x64\x3b\x20\x77\x61\x6c\x6c\x63\x6c\x6f\x63\x6b\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x77\x69\x6e\x64\x6f\x77\x5f\x73\x74\x61\x72\x74\x3d\x25\x6c\x6c\x75"
,rq->cpu,WALT790680e4aa,rq->window_start);WALT609fba09ac((0x67d+1393-0xbed));}if
(WALT17abc14e87<sched_ravg_window)return WALT901ba13dc5;WALT09570395b5=div64_u64
(WALT17abc14e87,sched_ravg_window);rq->window_start+=(u64)WALT09570395b5*(u64)
sched_ravg_window;rq->cum_window_demand_scaled=rq->walt_stats.
cumulative_runnable_avg_scaled;rq->prev_window_size=sched_ravg_window;return 
WALT901ba13dc5;}static inline u64 WALT2cd0d15eb3(int cpu,u64 WALT790680e4aa){
struct rq*rq=cpu_rq(cpu);if(rq->last_cc_update!=WALT790680e4aa){rq->cycles=
cpu_cycle_counter_cb.get_cpu_cycle_counter(cpu);rq->last_cc_update=
WALT790680e4aa;}return rq->cycles;}static void WALT1360b17c9b(struct task_struct
*WALT0609dbaf9d,int cpu,u64 WALT790680e4aa){if(WALT3b880410aa)WALT0609dbaf9d->
cpu_cycles=WALT2cd0d15eb3(cpu,WALT790680e4aa);}static inline bool WALTe99faa0ca8
(void){return(walt_rotation_enabled||(sched_boost_policy()!=SCHED_BOOST_NONE));}
void clear_ed_task(struct task_struct*WALT0609dbaf9d,struct rq*rq){if(
WALT0609dbaf9d==rq->ed_task)rq->ed_task=NULL;}static inline bool WALT30dc154c3b(
struct task_struct*WALT0609dbaf9d,u64 WALT790680e4aa){return(WALT790680e4aa-
WALT0609dbaf9d->last_wake_ts>=WALT53b6c10420);}bool early_detection_notify(
struct rq*rq,u64 WALT790680e4aa){struct task_struct*WALT0609dbaf9d;int 
WALTd7f6dc4db2=(0x81a+6544-0x21a0);rq->ed_task=NULL;if(!WALTe99faa0ca8()||!rq->
cfs.h_nr_running)return(0x546+949-0x8fb);list_for_each_entry(WALT0609dbaf9d,&rq
->cfs_tasks,se.group_node){if(!WALTd7f6dc4db2)break;if(WALT30dc154c3b(
WALT0609dbaf9d,WALT790680e4aa)){rq->ed_task=WALT0609dbaf9d;return
(0x10ba+3718-0x1f3f);}WALTd7f6dc4db2--;}return(0xe42+6081-0x2603);}void 
sched_account_irqstart(int cpu,struct task_struct*curr,u64 WALT790680e4aa){
struct rq*rq=cpu_rq(cpu);if(!rq->window_start)return;if(is_idle_task(curr)){
raw_spin_lock(&rq->lock);WALT1360b17c9b(curr,cpu,sched_ktime_clock());
raw_spin_unlock(&rq->lock);}}unsigned int walt_big_tasks(int cpu){struct rq*rq=
cpu_rq(cpu);return rq->walt_stats.nr_big_tasks;}void clear_walt_request(int cpu)
{struct rq*rq=cpu_rq(cpu);unsigned long flags;clear_reserved(cpu);if(rq->
push_task){struct task_struct*push_task=NULL;raw_spin_lock_irqsave(&rq->lock,
flags);if(rq->push_task){clear_reserved(rq->push_cpu);push_task=rq->push_task;rq
->push_task=NULL;}rq->active_balance=(0x1475+123-0x14f0);
raw_spin_unlock_irqrestore(&rq->lock,flags);if(push_task)put_task_struct(
push_task);}}static u32 top_task_load(struct rq*rq){int WALT6b2e94bfe7=rq->
prev_top;u8 prev=(0xe22+3868-0x1d3d)-rq->curr_table;if(!WALT6b2e94bfe7){int 
WALT1d278c4a11=NUM_LOAD_INDICES-(0xfac+542-0x11c9);if(!test_bit(WALT1d278c4a11,
rq->top_tasks_bitmap[prev]))return(0x307+1344-0x847);else return 
sched_load_granule;}else if(WALT6b2e94bfe7==NUM_LOAD_INDICES-
(0x21ba+1151-0x2638)){return sched_ravg_window;}else{return(WALT6b2e94bfe7+
(0xc8c+603-0xee6))*sched_load_granule;}}unsigned int sysctl_sched_user_hint;
static unsigned long WALTfac0edc4a3;static bool WALT0bb76a2e0a(struct 
sched_cluster*cluster);static inline bool WALT625289a60c(struct sched_cluster*
cluster){if(sched_freq_aggr_en||!sysctl_sched_user_hint||!cluster->aggr_grp_load
)return false;return WALT0bb76a2e0a(cluster);}static inline u64 freq_policy_load
(struct rq*rq){unsigned int WALT71357e08e4=WALTed0bb72c67;struct sched_cluster*
cluster=rq->cluster;u64 aggr_grp_load=cluster->aggr_grp_load;u64 WALT514f31b9a6,
WALT3d3b61fd9a=(0x56+3265-0xd17);struct task_struct*WALT17badca024=per_cpu(
ksoftirqd,cpu_of(rq));if(rq->ed_task!=NULL){WALT514f31b9a6=sched_ravg_window;
goto WALT02a8afcd23;}if(sched_freq_aggr_en)WALT514f31b9a6=rq->prev_runnable_sum+
aggr_grp_load;else WALT514f31b9a6=rq->prev_runnable_sum+rq->grp_time.
prev_runnable_sum;if(WALT17badca024&&WALT17badca024->state==TASK_RUNNING)
WALT514f31b9a6=max_t(u64,WALT514f31b9a6,task_load(WALT17badca024));
WALT3d3b61fd9a=top_task_load(rq);switch(WALT71357e08e4){case 
FREQ_REPORT_MAX_CPU_LOAD_TOP_TASK:WALT514f31b9a6=max_t(u64,WALT514f31b9a6,
WALT3d3b61fd9a);break;case FREQ_REPORT_TOP_TASK:WALT514f31b9a6=WALT3d3b61fd9a;
break;case FREQ_REPORT_CPU_LOAD:break;default:break;}if(WALT625289a60c(cluster))
{if(is_suh_max())WALT514f31b9a6=sched_ravg_window;else WALT514f31b9a6=div64_u64(
WALT514f31b9a6*sysctl_sched_user_hint,(u64)(0xaa8+2172-0x12c0));}WALT02a8afcd23:
trace_sched_load_to_gov(rq,aggr_grp_load,WALT3d3b61fd9a,sched_freq_aggr_en,
WALT514f31b9a6,WALT71357e08e4,walt_rotation_enabled,sysctl_sched_user_hint);
return WALT514f31b9a6;}static bool rtgb_active;static inline unsigned long 
WALT2744a2207f(int cpu,struct sched_walt_cpu_load*WALTcb55d41e86){u64 
WALTb0b0149580,WALT978a7841c5;struct rq*rq=cpu_rq(cpu);unsigned long capacity=
capacity_orig_of(cpu);int WALTf4f061ddc1;WALTf4f061ddc1=per_cpu(sched_load_boost
,cpu);WALT978a7841c5=WALTb0b0149580=freq_policy_load(rq);WALTb0b0149580=
div64_u64(WALTb0b0149580*((0x1099+2603-0x1a60)+WALTf4f061ddc1),
walt_cpu_util_freq_divisor);if(WALTcb55d41e86){u64 nl=cpu_rq(cpu)->
nt_prev_runnable_sum+rq->grp_time.nt_prev_runnable_sum;u64 pl=rq->walt_stats.
pred_demands_sum_scaled;rq->old_busy_time=div64_u64(WALT978a7841c5,
sched_ravg_window>>SCHED_CAPACITY_SHIFT);rq->old_estimated_time=pl;nl=div64_u64(
nl*((0x747+5974-0x1e39)+WALTf4f061ddc1),walt_cpu_util_freq_divisor);
WALTcb55d41e86->nl=nl;WALTcb55d41e86->pl=pl;WALTcb55d41e86->ws=
walt_load_reported_window;WALTcb55d41e86->rtgb_active=rtgb_active;}return(
WALTb0b0149580>=capacity)?capacity:WALTb0b0149580;}
#define WALT1c84aa4dd0(WALT60feb671ba, WALT4e03fa2834, WALT8a98b5f42b)	\
			(max(WALT60feb671ba, mult_frac(WALT4e03fa2834, WALT8a98b5f42b, \
(0x126a+1768-0x18ee))))
unsigned long cpu_util_freq_walt(int cpu,struct sched_walt_cpu_load*
WALTcb55d41e86){struct sched_walt_cpu_load WALTd64f78c90a={(0x1ded+1323-0x2318)}
;unsigned long WALTb0b0149580=(0x1989+1386-0x1ef3),WALT53081359ce=
(0xd78+5435-0x22b3);unsigned long capacity=capacity_orig_of(cpu);int 
WALT5d971be8b8,WALT568475e381=sysctl_sched_asym_cap_sibling_freq_match_pct;if(!
cpumask_test_cpu(cpu,&asym_cap_sibling_cpus))return WALT2744a2207f(cpu,
WALTcb55d41e86);for_each_cpu(WALT5d971be8b8,&asym_cap_sibling_cpus){if(
WALT5d971be8b8==cpu)WALTb0b0149580=WALT2744a2207f(cpu,WALTcb55d41e86);else 
WALT53081359ce=WALT2744a2207f(WALT5d971be8b8,&WALTd64f78c90a);}if(cpu==
cpumask_last(&asym_cap_sibling_cpus))WALT568475e381=(0x5f0+7035-0x2107);
WALTb0b0149580=WALT1c84aa4dd0(WALTb0b0149580,WALT53081359ce,WALT568475e381);
WALTcb55d41e86->nl=WALT1c84aa4dd0(WALTcb55d41e86->nl,WALTd64f78c90a.nl,
WALT568475e381);WALTcb55d41e86->pl=WALT1c84aa4dd0(WALTcb55d41e86->pl,
WALTd64f78c90a.pl,WALT568475e381);return(WALTb0b0149580>=capacity)?capacity:
WALTb0b0149580;}static inline void WALTa647ab699e(struct rq*rq){u64 ws=rq->
window_start;u64 WALT49da7a746a=ws-sched_ravg_window;struct load_subtractions*
WALTfd921988bb=rq->load_subs;int WALT5d971be8b8;for(WALT5d971be8b8=
(0x1375+2924-0x1ee1);WALT5d971be8b8<NUM_TRACKED_WINDOWS;WALT5d971be8b8++){if(
WALTfd921988bb[WALT5d971be8b8].window_start==ws){rq->curr_runnable_sum-=
WALTfd921988bb[WALT5d971be8b8].subs;rq->nt_curr_runnable_sum-=WALTfd921988bb[
WALT5d971be8b8].new_subs;}else if(WALTfd921988bb[WALT5d971be8b8].window_start==
WALT49da7a746a){rq->prev_runnable_sum-=WALTfd921988bb[WALT5d971be8b8].subs;rq->
nt_prev_runnable_sum-=WALTfd921988bb[WALT5d971be8b8].new_subs;}WALTfd921988bb[
WALT5d971be8b8].subs=(0x1ef+5090-0x15d1);WALTfd921988bb[WALT5d971be8b8].new_subs
=(0x1fb8+1539-0x25bb);}WALT609fba09ac((s64)rq->prev_runnable_sum<
(0x6d0+723-0x9a3));WALT609fba09ac((s64)rq->curr_runnable_sum<(0x9e7+6284-0x2273)
);WALT609fba09ac((s64)rq->nt_prev_runnable_sum<(0x354+5328-0x1824));
WALT609fba09ac((s64)rq->nt_curr_runnable_sum<(0x1703+1865-0x1e4c));}static 
inline void WALT06281e0b6d(struct rq*rq,u64 ws,int WALT6b2e94bfe7){rq->load_subs
[WALT6b2e94bfe7].window_start=ws;rq->load_subs[WALT6b2e94bfe7].subs=
(0x832+4408-0x196a);rq->load_subs[WALT6b2e94bfe7].new_subs=(0x12c5+2883-0x1e08);
}static int get_top_index(unsigned long*WALT75c312d1cd,unsigned long 
WALT8ba4e33369){int WALT6b2e94bfe7=find_next_bit(WALT75c312d1cd,NUM_LOAD_INDICES
,WALT8ba4e33369);if(WALT6b2e94bfe7==NUM_LOAD_INDICES)return(0x19eb+1958-0x2191);
return NUM_LOAD_INDICES-(0x2033+1422-0x25c0)-WALT6b2e94bfe7;}static bool 
WALT433ae47377(struct rq*rq,u64 ws){int WALT5d971be8b8;u64 WALT52cf8663bf=
ULLONG_MAX;int WALTf9248c507e=(0x136d+2252-0x1c39);for(WALT5d971be8b8=
(0x74b+7673-0x2544);WALT5d971be8b8<NUM_TRACKED_WINDOWS;WALT5d971be8b8++){u64 
WALTafddce82cf=rq->load_subs[WALT5d971be8b8].window_start;if(ws==WALTafddce82cf)
return WALT5d971be8b8;if(WALTafddce82cf<WALT52cf8663bf){WALT52cf8663bf=
WALTafddce82cf;WALTf9248c507e=WALT5d971be8b8;}}WALT06281e0b6d(rq,ws,
WALTf9248c507e);return WALTf9248c507e;}static void WALTb0531277d9(int 
WALT6b2e94bfe7,struct rq*rq,u32 WALT316dfbac15,bool WALT5eebbbffe9){rq->
load_subs[WALT6b2e94bfe7].subs+=WALT316dfbac15;if(WALT5eebbbffe9)rq->load_subs[
WALT6b2e94bfe7].new_subs+=WALT316dfbac15;}static inline struct sched_cluster*
cpu_cluster(int cpu){return cpu_rq(cpu)->cluster;}void WALT0dd808419c(struct 
task_struct*WALT0609dbaf9d,int cpu,u64 ws,bool WALT5eebbbffe9){struct 
sched_cluster*cluster=cpu_cluster(cpu);struct cpumask WALTf48c6e4ef8=cluster->
cpus;u64 WALT49da7a746a=ws-sched_ravg_window;int WALT5d971be8b8;
cpumask_clear_cpu(cpu,&WALTf48c6e4ef8);raw_spin_lock(&cluster->load_lock);
for_each_cpu(WALT5d971be8b8,&WALTf48c6e4ef8){struct rq*rq=cpu_rq(WALT5d971be8b8)
;int WALT6b2e94bfe7;if(WALT0609dbaf9d->ravg.curr_window_cpu[WALT5d971be8b8]){
WALT6b2e94bfe7=WALT433ae47377(rq,ws);WALTb0531277d9(WALT6b2e94bfe7,rq,
WALT0609dbaf9d->ravg.curr_window_cpu[WALT5d971be8b8],WALT5eebbbffe9);
WALT0609dbaf9d->ravg.curr_window_cpu[WALT5d971be8b8]=(0x282+2423-0xbf9);}if(
WALT0609dbaf9d->ravg.prev_window_cpu[WALT5d971be8b8]){WALT6b2e94bfe7=
WALT433ae47377(rq,WALT49da7a746a);WALTb0531277d9(WALT6b2e94bfe7,rq,
WALT0609dbaf9d->ravg.prev_window_cpu[WALT5d971be8b8],WALT5eebbbffe9);
WALT0609dbaf9d->ravg.prev_window_cpu[WALT5d971be8b8]=(0xac4+5833-0x218d);}}
raw_spin_unlock(&cluster->load_lock);}static inline void WALT6aa95e2012(struct 
task_struct*WALT0609dbaf9d,int WALT525181d1b1,int task_cpu,bool WALT5eebbbffe9){
struct rq*WALTeb0037895f=cpu_rq(WALT525181d1b1);struct rq*WALTd01f3eedf0=cpu_rq(
task_cpu);if(same_freq_domain(WALT525181d1b1,task_cpu))return;WALT0609dbaf9d->
ravg.curr_window_cpu[WALT525181d1b1]=WALT0609dbaf9d->ravg.curr_window;
WALT0609dbaf9d->ravg.prev_window_cpu[WALT525181d1b1]=WALT0609dbaf9d->ravg.
prev_window;WALTeb0037895f->curr_runnable_sum+=WALT0609dbaf9d->ravg.curr_window;
WALTeb0037895f->prev_runnable_sum+=WALT0609dbaf9d->ravg.prev_window;if(
WALTd01f3eedf0->curr_runnable_sum<WALT0609dbaf9d->ravg.curr_window_cpu[task_cpu]
){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x25\x64\x20\x2d\x3e\x20\x43\x50\x55\x25\x64\x20\x73\x72\x63\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,WALTd01f3eedf0->cpu,WALTeb0037895f->cpu,WALTd01f3eedf0->
curr_runnable_sum,WALT0609dbaf9d->ravg.curr_window_cpu[task_cpu]);WALT1efe882752
(WALT0609dbaf9d);WALT609fba09ac((0x48b+4693-0x16df));}WALTd01f3eedf0->
curr_runnable_sum-=WALT0609dbaf9d->ravg.curr_window_cpu[task_cpu];if(
WALTd01f3eedf0->prev_runnable_sum<WALT0609dbaf9d->ravg.prev_window_cpu[task_cpu]
){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x25\x64\x20\x2d\x3e\x20\x43\x50\x55\x25\x64\x20\x73\x72\x63\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,WALTd01f3eedf0->cpu,WALTeb0037895f->cpu,WALTd01f3eedf0->
prev_runnable_sum,WALT0609dbaf9d->ravg.prev_window_cpu[task_cpu]);WALT1efe882752
(WALT0609dbaf9d);WALT609fba09ac((0x12b1+394-0x143a));}WALTd01f3eedf0->
prev_runnable_sum-=WALT0609dbaf9d->ravg.prev_window_cpu[task_cpu];if(
WALT5eebbbffe9){WALTeb0037895f->nt_curr_runnable_sum+=WALT0609dbaf9d->ravg.
curr_window;WALTeb0037895f->nt_prev_runnable_sum+=WALT0609dbaf9d->ravg.
prev_window;if(WALTd01f3eedf0->nt_curr_runnable_sum<WALT0609dbaf9d->ravg.
curr_window_cpu[task_cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x25\x64\x20\x2d\x3e\x20\x43\x50\x55\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,WALTd01f3eedf0->cpu,WALTeb0037895f->cpu,WALTd01f3eedf0->
nt_curr_runnable_sum,WALT0609dbaf9d->ravg.curr_window_cpu[task_cpu]);
WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac((0x18d+3915-0x10d7));}
WALTd01f3eedf0->nt_curr_runnable_sum-=WALT0609dbaf9d->ravg.curr_window_cpu[
task_cpu];if(WALTd01f3eedf0->nt_prev_runnable_sum<WALT0609dbaf9d->ravg.
prev_window_cpu[task_cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x25\x64\x20\x2d\x3e\x20\x43\x50\x55\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,WALTd01f3eedf0->cpu,WALTeb0037895f->cpu,WALTd01f3eedf0->
nt_prev_runnable_sum,WALT0609dbaf9d->ravg.prev_window_cpu[task_cpu]);
WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac((0xd17+3673-0x1b6f));}
WALTd01f3eedf0->nt_prev_runnable_sum-=WALT0609dbaf9d->ravg.prev_window_cpu[
task_cpu];}WALT0609dbaf9d->ravg.curr_window_cpu[task_cpu]=(0x3d+5562-0x15f7);
WALT0609dbaf9d->ravg.prev_window_cpu[task_cpu]=(0x8b9+1122-0xd1b);WALT0dd808419c
(WALT0609dbaf9d,task_cpu,WALTd01f3eedf0->window_start,WALT5eebbbffe9);}static 
u32 WALTb7bb6f3305(u32 WALT514f31b9a6){u32 WALT6b2e94bfe7=WALT514f31b9a6/
sched_load_granule;return min(WALT6b2e94bfe7,(u32)(NUM_LOAD_INDICES-
(0x1199+5093-0x257d)));}static void WALT9be28a1f9c(struct task_struct*
WALT0609dbaf9d,struct rq*WALTd01f3eedf0,struct rq*WALT38ee64137f){int 
WALT6b2e94bfe7;int WALT722eaaf4cf;u32 curr_window=WALT0609dbaf9d->ravg.
curr_window;u32 prev_window=WALT0609dbaf9d->ravg.prev_window;u8 WALT792740f2d5=
WALTd01f3eedf0->curr_table;u8 WALT6f47937b7c=WALT38ee64137f->curr_table;u8*
WALT146a962968;u8*WALTbf29d6b684;if(curr_window){WALT146a962968=WALTd01f3eedf0->
top_tasks[WALT792740f2d5];WALTbf29d6b684=WALT38ee64137f->top_tasks[
WALT6f47937b7c];WALT6b2e94bfe7=WALTb7bb6f3305(curr_window);WALT146a962968[
WALT6b2e94bfe7]-=(0x785+561-0x9b5);WALTbf29d6b684[WALT6b2e94bfe7]+=
(0x18d6+1064-0x1cfd);if(!WALT146a962968[WALT6b2e94bfe7])__clear_bit(
NUM_LOAD_INDICES-WALT6b2e94bfe7-(0x1a6d+1461-0x2021),WALTd01f3eedf0->
top_tasks_bitmap[WALT792740f2d5]);if(WALTbf29d6b684[WALT6b2e94bfe7]==
(0xee8+2869-0x1a1c))__set_bit(NUM_LOAD_INDICES-WALT6b2e94bfe7-(0xf8+4213-0x116c)
,WALT38ee64137f->top_tasks_bitmap[WALT6f47937b7c]);if(WALT6b2e94bfe7>
WALT38ee64137f->curr_top)WALT38ee64137f->curr_top=WALT6b2e94bfe7;WALT722eaaf4cf=
WALTd01f3eedf0->curr_top;if(WALT6b2e94bfe7==WALT722eaaf4cf&&!WALT146a962968[
WALT6b2e94bfe7])WALTd01f3eedf0->curr_top=get_top_index(WALTd01f3eedf0->
top_tasks_bitmap[WALT792740f2d5],WALT722eaaf4cf);}if(prev_window){WALT792740f2d5
=(0x1188+4940-0x24d3)-WALT792740f2d5;WALT6f47937b7c=(0x1c44+2359-0x257a)-
WALT6f47937b7c;WALT146a962968=WALTd01f3eedf0->top_tasks[WALT792740f2d5];
WALTbf29d6b684=WALT38ee64137f->top_tasks[WALT6f47937b7c];WALT6b2e94bfe7=
WALTb7bb6f3305(prev_window);WALT146a962968[WALT6b2e94bfe7]-=(0x354+2690-0xdd5);
WALTbf29d6b684[WALT6b2e94bfe7]+=(0xa4+585-0x2ec);if(!WALT146a962968[
WALT6b2e94bfe7])__clear_bit(NUM_LOAD_INDICES-WALT6b2e94bfe7-(0x148a+2713-0x1f22)
,WALTd01f3eedf0->top_tasks_bitmap[WALT792740f2d5]);if(WALTbf29d6b684[
WALT6b2e94bfe7]==(0xf52+776-0x1259))__set_bit(NUM_LOAD_INDICES-WALT6b2e94bfe7-
(0x5e4+502-0x7d9),WALT38ee64137f->top_tasks_bitmap[WALT6f47937b7c]);if(
WALT6b2e94bfe7>WALT38ee64137f->prev_top)WALT38ee64137f->prev_top=WALT6b2e94bfe7;
WALT722eaaf4cf=WALTd01f3eedf0->prev_top;if(WALT6b2e94bfe7==WALT722eaaf4cf&&!
WALT146a962968[WALT6b2e94bfe7])WALTd01f3eedf0->prev_top=get_top_index(
WALTd01f3eedf0->top_tasks_bitmap[WALT792740f2d5],WALT722eaaf4cf);}}static inline
 bool is_new_task(struct task_struct*WALT0609dbaf9d){return WALT0609dbaf9d->ravg
.active_time<WALTdbeb076c45;}void fixup_busy_time(struct task_struct*
WALT0609dbaf9d,int WALT525181d1b1){struct rq*WALTd01f3eedf0=task_rq(
WALT0609dbaf9d);struct rq*WALTeb0037895f=cpu_rq(WALT525181d1b1);u64 
WALT790680e4aa;u64*WALT42b4427a2c,*WALT2e4da9dbb4;u64*WALT262b512e81,*
WALT086b45bedf;u64*WALTf7e69c10fd,*WALT847919a57a;u64*WALT7ba10de4f4,*
WALT082a99fd0f;bool WALT5eebbbffe9;struct related_thread_group*grp;if(!
WALT0609dbaf9d->on_rq&&WALT0609dbaf9d->state!=TASK_WAKING)return;if(exiting_task
(WALT0609dbaf9d)){clear_ed_task(WALT0609dbaf9d,WALTd01f3eedf0);return;}if(
WALT0609dbaf9d->state==TASK_WAKING)double_rq_lock(WALTd01f3eedf0,WALTeb0037895f)
;WALT790680e4aa=sched_ktime_clock();walt_update_task_ravg(task_rq(WALT0609dbaf9d
)->curr,task_rq(WALT0609dbaf9d),TASK_UPDATE,WALT790680e4aa,(0x40b+512-0x60b));
walt_update_task_ravg(WALTeb0037895f->curr,WALTeb0037895f,TASK_UPDATE,
WALT790680e4aa,(0x483+3680-0x12e3));walt_update_task_ravg(WALT0609dbaf9d,task_rq
(WALT0609dbaf9d),TASK_MIGRATE,WALT790680e4aa,(0xa02+3113-0x162b));WALT1360b17c9b
(WALT0609dbaf9d,WALT525181d1b1,WALT790680e4aa);if(WALT0609dbaf9d->state==
TASK_WAKING&&WALT0609dbaf9d->last_sleep_ts>=WALTd01f3eedf0->window_start){
walt_fixup_cum_window_demand(WALTd01f3eedf0,-(s64)WALT0609dbaf9d->ravg.
demand_scaled);walt_fixup_cum_window_demand(WALTeb0037895f,WALT0609dbaf9d->ravg.
demand_scaled);}WALT5eebbbffe9=is_new_task(WALT0609dbaf9d);grp=WALT0609dbaf9d->
grp;if(grp){struct group_cpu_time*WALT627d50b29d;WALT627d50b29d=&WALTd01f3eedf0
->grp_time;WALT42b4427a2c=&WALT627d50b29d->curr_runnable_sum;WALT262b512e81=&
WALT627d50b29d->prev_runnable_sum;WALTf7e69c10fd=&WALT627d50b29d->
nt_curr_runnable_sum;WALT7ba10de4f4=&WALT627d50b29d->nt_prev_runnable_sum;
WALT627d50b29d=&WALTeb0037895f->grp_time;WALT2e4da9dbb4=&WALT627d50b29d->
curr_runnable_sum;WALT086b45bedf=&WALT627d50b29d->prev_runnable_sum;
WALT847919a57a=&WALT627d50b29d->nt_curr_runnable_sum;WALT082a99fd0f=&
WALT627d50b29d->nt_prev_runnable_sum;if(WALT0609dbaf9d->ravg.curr_window){*
WALT42b4427a2c-=WALT0609dbaf9d->ravg.curr_window;*WALT2e4da9dbb4+=WALT0609dbaf9d
->ravg.curr_window;if(WALT5eebbbffe9){*WALTf7e69c10fd-=WALT0609dbaf9d->ravg.
curr_window;*WALT847919a57a+=WALT0609dbaf9d->ravg.curr_window;}}if(
WALT0609dbaf9d->ravg.prev_window){*WALT262b512e81-=WALT0609dbaf9d->ravg.
prev_window;*WALT086b45bedf+=WALT0609dbaf9d->ravg.prev_window;if(WALT5eebbbffe9)
{*WALT7ba10de4f4-=WALT0609dbaf9d->ravg.prev_window;*WALT082a99fd0f+=
WALT0609dbaf9d->ravg.prev_window;}}}else{WALT6aa95e2012(WALT0609dbaf9d,
WALT525181d1b1,task_cpu(WALT0609dbaf9d),WALT5eebbbffe9);}WALT9be28a1f9c(
WALT0609dbaf9d,WALTd01f3eedf0,WALTeb0037895f);if(!same_freq_domain(
WALT525181d1b1,task_cpu(WALT0609dbaf9d))){WALTd01f3eedf0->notif_pending=true;
WALTeb0037895f->notif_pending=true;WALTa4ccf3d6c9(&WALT72f8d06752);}if(
WALTe99faa0ca8()){if(WALT0609dbaf9d==WALTd01f3eedf0->ed_task){WALTd01f3eedf0->
ed_task=NULL;WALTeb0037895f->ed_task=WALT0609dbaf9d;}else if(WALT30dc154c3b(
WALT0609dbaf9d,WALT790680e4aa)){WALTeb0037895f->ed_task=WALT0609dbaf9d;}}if(
WALT0609dbaf9d->state==TASK_WAKING)double_rq_unlock(WALTd01f3eedf0,
WALTeb0037895f);}void set_window_start(struct rq*rq){static int WALTe66a622f51;
if(likely(rq->window_start))return;if(!WALTe66a622f51){rq->window_start=
(0x15a4+1280-0x1aa3);WALTe66a622f51=(0x1128+3464-0x1eaf);atomic64_set(&
WALT8d508f7c3b,rq->window_start);walt_load_reported_window=atomic64_read(&
WALT8d508f7c3b);}else{struct rq*WALT3e3d21be47=cpu_rq(cpumask_any(
cpu_online_mask));raw_spin_unlock(&rq->lock);double_rq_lock(rq,WALT3e3d21be47);
rq->window_start=WALT3e3d21be47->window_start;rq->curr_runnable_sum=rq->
prev_runnable_sum=(0x1fac+1010-0x239e);rq->nt_curr_runnable_sum=rq->
nt_prev_runnable_sum=(0x5da+224-0x6ba);raw_spin_unlock(&WALT3e3d21be47->lock);}
rq->curr->ravg.mark_start=rq->window_start;}unsigned int 
sysctl_sched_conservative_pl;unsigned int sysctl_sched_many_wakeup_threshold=
(0x26d2+962-0x26ac);
#define WALT07c7d3e0b1 (0x7b5+3721-0x1636)
#define WALT07f1c18f03 (0x14c1+3572-0x22b3)
#define WALTedc4e7b72b (0x680+2200-0xf08)
#define WALTd412d902d5 (0x18bf+435-0x1a62)
static inline void WALTcd30d5f093(u8*WALTc0f271aeff,int WALT8aa1674e1f){int 
WALT5d971be8b8,WALT2a39967a03;for(WALT5d971be8b8=(0x45d+1694-0xafb);
WALT5d971be8b8<NUM_BUSY_BUCKETS;WALT5d971be8b8++){if(WALT8aa1674e1f!=
WALT5d971be8b8){if(WALTc0f271aeff[WALT5d971be8b8]>WALT07f1c18f03)WALTc0f271aeff[
WALT5d971be8b8]-=WALT07f1c18f03;else WALTc0f271aeff[WALT5d971be8b8]=
(0x9cf+5435-0x1f0a);}else{WALT2a39967a03=WALTc0f271aeff[WALT5d971be8b8]>=
WALTedc4e7b72b?WALTd412d902d5:WALT07c7d3e0b1;if(WALTc0f271aeff[WALT5d971be8b8]>
U8_MAX-WALT2a39967a03)WALTc0f271aeff[WALT5d971be8b8]=U8_MAX;else WALTc0f271aeff[
WALT5d971be8b8]+=WALT2a39967a03;}}}static inline int WALT5161a2cdf5(u32 
WALTfd7e825862){int WALT57acf293db;WALT57acf293db=mult_frac(WALTfd7e825862,
NUM_BUSY_BUCKETS,max_task_load());WALT57acf293db=min(WALT57acf293db,
NUM_BUSY_BUCKETS-(0x1802+3512-0x25b9));if(!WALT57acf293db)WALT57acf293db++;
return WALT57acf293db;}static u32 WALTd706aa2c09(struct task_struct*
WALT0609dbaf9d,int WALT9f089c6af4,u32 WALT8a690d3852){int WALT5d971be8b8;u8*
WALTc0f271aeff=WALT0609dbaf9d->ravg.busy_buckets;u32*WALT53b45fa17b=
WALT0609dbaf9d->ravg.sum_history;u32 WALTf78d322c50,WALT51a9118714;u64 
WALT75472ab857=(0x14e4+1293-0x19f1);int WALTc4b85e3bbe=NUM_BUSY_BUCKETS,final;
u32 WALT083920bcc8=WALT8a690d3852;if(unlikely(is_new_task(WALT0609dbaf9d)))goto 
WALTe1f307999b;for(WALT5d971be8b8=WALT9f089c6af4;WALT5d971be8b8<NUM_BUSY_BUCKETS
;WALT5d971be8b8++){if(WALTc0f271aeff[WALT5d971be8b8]){WALTc4b85e3bbe=
WALT5d971be8b8;break;}}if(WALTc4b85e3bbe>=NUM_BUSY_BUCKETS)goto WALTe1f307999b;
final=WALTc4b85e3bbe;if(final<(0xd9+872-0x43f)){WALTf78d322c50=
(0x1761+68-0x17a5);final=(0xb0f+4591-0x1cfd);}else{WALTf78d322c50=mult_frac(
final,max_task_load(),NUM_BUSY_BUCKETS);}WALT51a9118714=mult_frac(final+
(0x2d2+7771-0x212c),max_task_load(),NUM_BUSY_BUCKETS);for(WALT5d971be8b8=
(0x7e7+6683-0x2202);WALT5d971be8b8<WALTa591b9e54c;WALT5d971be8b8++){if(
WALT53b45fa17b[WALT5d971be8b8]>=WALTf78d322c50&&WALT53b45fa17b[WALT5d971be8b8]<
WALT51a9118714){WALT083920bcc8=WALT53b45fa17b[WALT5d971be8b8];break;}}if(
WALT083920bcc8<WALTf78d322c50)WALT083920bcc8=(WALTf78d322c50+WALT51a9118714)/
(0x283+5471-0x17e0);WALT083920bcc8=max(WALT8a690d3852,WALT083920bcc8);
WALTe1f307999b:trace_sched_update_pred_demand(WALT0609dbaf9d,WALT8a690d3852,
mult_frac((unsigned int)WALT75472ab857,(0x1639+646-0x185b),sched_ravg_window),
WALT083920bcc8);return WALT083920bcc8;}static inline u32 WALTa50ae1c837(struct 
task_struct*WALT0609dbaf9d){if(WALT0609dbaf9d->ravg.pred_demand>=WALT0609dbaf9d
->ravg.curr_window)return WALT0609dbaf9d->ravg.pred_demand;return WALTd706aa2c09
(WALT0609dbaf9d,WALT5161a2cdf5(WALT0609dbaf9d->ravg.curr_window),WALT0609dbaf9d
->ravg.curr_window);}void WALTbc967ce57f(struct rq*rq,struct task_struct*
WALT0609dbaf9d,int WALT3205babe24){u32 new,WALTec59fbb1ff;u16 WALTb2100a439c;if(
!sched_predl)return;if(is_idle_task(WALT0609dbaf9d)||exiting_task(WALT0609dbaf9d
))return;if(WALT3205babe24!=PUT_PREV_TASK&&WALT3205babe24!=TASK_UPDATE&&(!
WALT88b9b0b9ce||(WALT3205babe24!=TASK_MIGRATE&&WALT3205babe24!=PICK_NEXT_TASK)))
return;if(WALT3205babe24==TASK_UPDATE){if(!WALT0609dbaf9d->on_rq&&!
WALT88b9b0b9ce)return;}new=WALTa50ae1c837(WALT0609dbaf9d);WALTec59fbb1ff=
WALT0609dbaf9d->ravg.pred_demand;if(WALTec59fbb1ff>=new)return;WALTb2100a439c=
WALTecf40170d4(new);if(task_on_rq_queued(WALT0609dbaf9d)&&(!task_has_dl_policy(
WALT0609dbaf9d)||!WALT0609dbaf9d->dl.dl_throttled))WALT69efd235f7(rq,
WALT0609dbaf9d,WALT0609dbaf9d->ravg.demand_scaled,WALTb2100a439c);WALT0609dbaf9d
->ravg.pred_demand=new;WALT0609dbaf9d->ravg.pred_demand_scaled=WALTb2100a439c;}
void WALT66971bc3d0(unsigned long*WALT75c312d1cd){memset(WALT75c312d1cd,
(0x91a+7565-0x26a7),WALT64333e9737);__set_bit(NUM_LOAD_INDICES,WALT75c312d1cd);}
static inline void clear_top_tasks_table(u8*table){memset(table,
(0x31f+6905-0x1e18),NUM_LOAD_INDICES*sizeof(u8));}static void WALT81ac526b7a(
struct task_struct*WALT0609dbaf9d,struct rq*rq,u32 WALT394bc84586,int 
WALT3b5207d436,bool WALTdd3d5a87d4){u8 curr=rq->curr_table;u8 prev=
(0x76+6071-0x182c)-curr;u8*curr_table=rq->top_tasks[curr];u8*WALT78d0a88386=rq->
top_tasks[prev];int WALTbbf323d019,WALT6a0597304c,WALT64adf5cf6f;u32 curr_window
=WALT0609dbaf9d->ravg.curr_window;u32 prev_window=WALT0609dbaf9d->ravg.
prev_window;bool WALTd4e56af857;if(WALT394bc84586==curr_window&&!WALT3b5207d436)
return;WALTbbf323d019=WALTb7bb6f3305(WALT394bc84586);WALT6a0597304c=
WALTb7bb6f3305(curr_window);if(!WALT3b5207d436){WALTd4e56af857=!WALT394bc84586&&
curr_window;if(WALTbbf323d019!=WALT6a0597304c||WALTd4e56af857){if(WALT394bc84586
)curr_table[WALTbbf323d019]-=(0xae8+6014-0x2265);if(curr_window)curr_table[
WALT6a0597304c]+=(0x65f+4941-0x19ab);if(WALT6a0597304c>rq->curr_top)rq->curr_top
=WALT6a0597304c;}if(!curr_table[WALTbbf323d019])__clear_bit(NUM_LOAD_INDICES-
WALTbbf323d019-(0x81c+7271-0x2482),rq->top_tasks_bitmap[curr]);if(curr_table[
WALT6a0597304c]==(0x1cf7+1301-0x220b))__set_bit(NUM_LOAD_INDICES-WALT6a0597304c-
(0x241+7334-0x1ee6),rq->top_tasks_bitmap[curr]);return;}WALT64adf5cf6f=
WALTb7bb6f3305(prev_window);if(WALTdd3d5a87d4){if(prev_window){WALT78d0a88386[
WALT64adf5cf6f]+=(0x9a6+1329-0xed6);rq->prev_top=WALT64adf5cf6f;}if(
WALT78d0a88386[WALT64adf5cf6f]==(0x115+5923-0x1837))__set_bit(NUM_LOAD_INDICES-
WALT64adf5cf6f-(0x41+64-0x80),rq->top_tasks_bitmap[prev]);}else{WALTd4e56af857=!
WALT394bc84586&&prev_window;if(WALTbbf323d019!=WALT64adf5cf6f||WALTd4e56af857){
if(WALT394bc84586)WALT78d0a88386[WALTbbf323d019]-=(0x1583+1158-0x1a08);
WALT78d0a88386[WALT64adf5cf6f]+=(0xd6+6667-0x1ae0);if(WALT64adf5cf6f>rq->
prev_top)rq->prev_top=WALT64adf5cf6f;if(!WALT78d0a88386[WALTbbf323d019])
__clear_bit(NUM_LOAD_INDICES-WALTbbf323d019-(0x133c+3472-0x20cb),rq->
top_tasks_bitmap[prev]);if(WALT78d0a88386[WALT64adf5cf6f]==(0x1f36+1088-0x2375))
__set_bit(NUM_LOAD_INDICES-WALT64adf5cf6f-(0x1623+166-0x16c8),rq->
top_tasks_bitmap[prev]);}}if(curr_window){curr_table[WALT6a0597304c]+=
(0xda5+3807-0x1c83);if(WALT6a0597304c>rq->curr_top)rq->curr_top=WALT6a0597304c;
if(curr_table[WALT6a0597304c]==(0x1274+4480-0x23f3))__set_bit(NUM_LOAD_INDICES-
WALT6a0597304c-(0x25fb+207-0x26c9),rq->top_tasks_bitmap[curr]);}}static void 
WALT05813ee528(struct rq*rq,bool WALTdd3d5a87d4){u8 curr_table=rq->curr_table;u8
 WALT78d0a88386=(0x161+9640-0x2708)-curr_table;int curr_top=rq->curr_top;
clear_top_tasks_table(rq->top_tasks[WALT78d0a88386]);WALT66971bc3d0(rq->
top_tasks_bitmap[WALT78d0a88386]);if(WALTdd3d5a87d4){curr_top=
(0x5f8+7971-0x251b);clear_top_tasks_table(rq->top_tasks[curr_table]);
WALT66971bc3d0(rq->top_tasks_bitmap[curr_table]);}rq->curr_table=WALT78d0a88386;
rq->prev_top=curr_top;rq->curr_top=(0xd09+5203-0x215c);}static u32 
WALT0c92d7b1ad[NR_CPUS];static void WALTd12ebe5060(struct task_struct*
WALT0609dbaf9d,bool WALTdd3d5a87d4){u32*WALT1d6a0b8b72=WALT0c92d7b1ad;u32 
curr_window;int WALT5d971be8b8;curr_window=(0x15f+2987-0xd0a);if(!WALTdd3d5a87d4
){curr_window=WALT0609dbaf9d->ravg.curr_window;WALT1d6a0b8b72=WALT0609dbaf9d->
ravg.curr_window_cpu;}WALT0609dbaf9d->ravg.prev_window=curr_window;
WALT0609dbaf9d->ravg.curr_window=(0x36f+2547-0xd62);for(WALT5d971be8b8=
(0x1f27+1111-0x237e);WALT5d971be8b8<nr_cpu_ids;WALT5d971be8b8++){WALT0609dbaf9d
->ravg.prev_window_cpu[WALT5d971be8b8]=WALT1d6a0b8b72[WALT5d971be8b8];
WALT0609dbaf9d->ravg.curr_window_cpu[WALT5d971be8b8]=(0x11a4+4548-0x2368);}if(
is_new_task(WALT0609dbaf9d))WALT0609dbaf9d->ravg.active_time+=WALT0609dbaf9d->
ravg.last_win_size;}void sched_set_io_is_busy(int WALTc94d3d8015){WALTdedb054041
=WALTc94d3d8015;}static inline int WALT40d96c83d6(struct rq*rq){if(!
WALTdedb054041)return(0xc1d+3860-0x1b31);return atomic_read(&rq->nr_iowait);}
static int WALT596816cbc6(struct rq*rq,struct task_struct*WALT0609dbaf9d,u64 
WALT59018c6914,int WALT3205babe24){if(is_idle_task(WALT0609dbaf9d)){if(
WALT3205babe24==PICK_NEXT_TASK)return(0xe4+4514-0x1286);return WALT59018c6914||
WALT40d96c83d6(rq);}if(WALT3205babe24==TASK_WAKE)return(0x5df+3113-0x1208);if(
WALT3205babe24==PUT_PREV_TASK||WALT3205babe24==IRQ_UPDATE)return
(0x15d9+1253-0x1abd);if(WALT3205babe24==TASK_UPDATE){if(rq->curr==WALT0609dbaf9d
)return(0x15e8+2522-0x1fc1);return WALT0609dbaf9d->on_rq?WALT88b9b0b9ce:
(0xb15+371-0xc88);}return WALT88b9b0b9ce;}
#define WALT20b422fc7b(WALT98927a0ef6, WALTc096799050) div64_u64((WALT98927a0ef6\
) + (WALTc096799050 - (0x5c8+2773-0x109c)), WALTc096799050)
static inline u64 WALTb95ca9f31b(u64 WALT17abc14e87,struct rq*rq){return(
WALT17abc14e87*rq->task_exec_scale)>>(0x373+3557-0x114e);}static inline unsigned
 int WALT603dc3b6ad(struct rq*rq,unsigned int WALT514f31b9a6){return mult_frac(
cpu_max_possible_freq(cpu_of(rq)),WALT514f31b9a6,(unsigned int)
arch_scale_cpu_capacity(cpu_of(rq)));}bool do_pl_notif(struct rq*rq){u64 prev=rq
->old_busy_time;u64 pl=rq->walt_stats.pred_demands_sum_scaled;int cpu=cpu_of(rq)
;if(capacity_orig_of(cpu)==capacity_curr_of(cpu))return false;prev=max(prev,rq->
old_estimated_time);return(pl>prev)&&(WALT603dc3b6ad(rq,pl-prev)>400000);}static
 void WALT8ebc59a5de(struct rq*rq,bool WALTdd3d5a87d4){u64 WALT36b7a61385=rq->
curr_runnable_sum;u64 WALT41bd9431ad=rq->nt_curr_runnable_sum;u64 WALTc62485a0c5
=rq->grp_time.curr_runnable_sum;u64 WALT1ae796a363=rq->grp_time.
nt_curr_runnable_sum;if(unlikely(WALTdd3d5a87d4)){WALT36b7a61385=
(0x125+2057-0x92e);WALT41bd9431ad=(0x2283+179-0x2336);WALTc62485a0c5=
(0x11c8+2002-0x199a);WALT1ae796a363=(0x6b5+3949-0x1622);}rq->prev_runnable_sum=
WALT36b7a61385;rq->nt_prev_runnable_sum=WALT41bd9431ad;rq->grp_time.
prev_runnable_sum=WALTc62485a0c5;rq->grp_time.nt_prev_runnable_sum=
WALT1ae796a363;rq->curr_runnable_sum=(0x72f+2709-0x11c4);rq->
nt_curr_runnable_sum=(0x2da+3359-0xff9);rq->grp_time.curr_runnable_sum=
(0x684+6044-0x1e20);rq->grp_time.nt_curr_runnable_sum=(0x1126+2025-0x190f);}
static void WALT130dee47f1(struct task_struct*WALT0609dbaf9d,struct rq*rq,int 
WALT3205babe24,u64 WALT790680e4aa,u64 WALT59018c6914){int WALT3b5207d436,
WALTdd3d5a87d4=(0x944+7316-0x25d8);int WALTd7f58f7fc0=(WALT0609dbaf9d==rq->curr)
;u64 mark_start=WALT0609dbaf9d->ravg.mark_start;u64 window_start=rq->
window_start;u32 WALT4ae816ebd1=rq->prev_window_size;u64 WALT17abc14e87;u64*
curr_runnable_sum=&rq->curr_runnable_sum;u64*prev_runnable_sum=&rq->
prev_runnable_sum;u64*nt_curr_runnable_sum=&rq->nt_curr_runnable_sum;u64*
nt_prev_runnable_sum=&rq->nt_prev_runnable_sum;bool WALT5eebbbffe9;struct 
related_thread_group*grp;int cpu=rq->cpu;u32 WALT394bc84586=WALT0609dbaf9d->ravg
.curr_window;WALT3b5207d436=mark_start<window_start;if(WALT3b5207d436)
WALTdd3d5a87d4=(window_start-mark_start)>=WALT4ae816ebd1;if(!is_idle_task(
WALT0609dbaf9d)&&!exiting_task(WALT0609dbaf9d)){if(WALT3b5207d436)WALTd12ebe5060
(WALT0609dbaf9d,WALTdd3d5a87d4);}WALT5eebbbffe9=is_new_task(WALT0609dbaf9d);if(
WALTd7f58f7fc0&&WALT3b5207d436){WALT8ebc59a5de(rq,WALTdd3d5a87d4);WALT05813ee528
(rq,WALTdd3d5a87d4);}if(!WALT596816cbc6(rq,WALT0609dbaf9d,WALT59018c6914,
WALT3205babe24))goto WALT02a8afcd23;grp=WALT0609dbaf9d->grp;if(grp){struct 
group_cpu_time*WALT627d50b29d=&rq->grp_time;curr_runnable_sum=&WALT627d50b29d->
curr_runnable_sum;prev_runnable_sum=&WALT627d50b29d->prev_runnable_sum;
nt_curr_runnable_sum=&WALT627d50b29d->nt_curr_runnable_sum;nt_prev_runnable_sum=
&WALT627d50b29d->nt_prev_runnable_sum;}if(!WALT3b5207d436){if(!WALT59018c6914||!
is_idle_task(WALT0609dbaf9d)||WALT40d96c83d6(rq))WALT17abc14e87=WALT790680e4aa-
mark_start;else WALT17abc14e87=WALT59018c6914;WALT17abc14e87=WALTb95ca9f31b(
WALT17abc14e87,rq);*curr_runnable_sum+=WALT17abc14e87;if(WALT5eebbbffe9)*
nt_curr_runnable_sum+=WALT17abc14e87;if(!is_idle_task(WALT0609dbaf9d)&&!
exiting_task(WALT0609dbaf9d)){WALT0609dbaf9d->ravg.curr_window+=WALT17abc14e87;
WALT0609dbaf9d->ravg.curr_window_cpu[cpu]+=WALT17abc14e87;}goto WALT02a8afcd23;}
if(!WALTd7f58f7fc0){if(!WALTdd3d5a87d4){WALT17abc14e87=WALTb95ca9f31b(
window_start-mark_start,rq);if(!exiting_task(WALT0609dbaf9d)){WALT0609dbaf9d->
ravg.prev_window+=WALT17abc14e87;WALT0609dbaf9d->ravg.prev_window_cpu[cpu]+=
WALT17abc14e87;}}else{WALT17abc14e87=WALTb95ca9f31b(WALT4ae816ebd1,rq);if(!
exiting_task(WALT0609dbaf9d)){WALT0609dbaf9d->ravg.prev_window=WALT17abc14e87;
WALT0609dbaf9d->ravg.prev_window_cpu[cpu]=WALT17abc14e87;}}*prev_runnable_sum+=
WALT17abc14e87;if(WALT5eebbbffe9)*nt_prev_runnable_sum+=WALT17abc14e87;
WALT17abc14e87=WALTb95ca9f31b(WALT790680e4aa-window_start,rq);*curr_runnable_sum
+=WALT17abc14e87;if(WALT5eebbbffe9)*nt_curr_runnable_sum+=WALT17abc14e87;if(!
exiting_task(WALT0609dbaf9d)){WALT0609dbaf9d->ravg.curr_window=WALT17abc14e87;
WALT0609dbaf9d->ravg.curr_window_cpu[cpu]=WALT17abc14e87;}goto WALT02a8afcd23;}
if(!WALT59018c6914||!is_idle_task(WALT0609dbaf9d)||WALT40d96c83d6(rq)){if(!
WALTdd3d5a87d4){WALT17abc14e87=WALTb95ca9f31b(window_start-mark_start,rq);if(!
is_idle_task(WALT0609dbaf9d)&&!exiting_task(WALT0609dbaf9d)){WALT0609dbaf9d->
ravg.prev_window+=WALT17abc14e87;WALT0609dbaf9d->ravg.prev_window_cpu[cpu]+=
WALT17abc14e87;}}else{WALT17abc14e87=WALTb95ca9f31b(WALT4ae816ebd1,rq);if(!
is_idle_task(WALT0609dbaf9d)&&!exiting_task(WALT0609dbaf9d)){WALT0609dbaf9d->
ravg.prev_window=WALT17abc14e87;WALT0609dbaf9d->ravg.prev_window_cpu[cpu]=
WALT17abc14e87;}}*prev_runnable_sum+=WALT17abc14e87;if(WALT5eebbbffe9)*
nt_prev_runnable_sum+=WALT17abc14e87;WALT17abc14e87=WALTb95ca9f31b(
WALT790680e4aa-window_start,rq);*curr_runnable_sum+=WALT17abc14e87;if(
WALT5eebbbffe9)*nt_curr_runnable_sum+=WALT17abc14e87;if(!is_idle_task(
WALT0609dbaf9d)&&!exiting_task(WALT0609dbaf9d)){WALT0609dbaf9d->ravg.curr_window
=WALT17abc14e87;WALT0609dbaf9d->ravg.curr_window_cpu[cpu]=WALT17abc14e87;}goto 
WALT02a8afcd23;}if(WALT59018c6914){WALT609fba09ac(!is_idle_task(WALT0609dbaf9d))
;mark_start=WALT790680e4aa-WALT59018c6914;if(mark_start>window_start){*
curr_runnable_sum=WALTb95ca9f31b(WALT59018c6914,rq);return;}WALT17abc14e87=
window_start-mark_start;if(WALT17abc14e87>WALT4ae816ebd1)WALT17abc14e87=
WALT4ae816ebd1;WALT17abc14e87=WALTb95ca9f31b(WALT17abc14e87,rq);*
prev_runnable_sum+=WALT17abc14e87;WALT17abc14e87=WALT790680e4aa-window_start;rq
->curr_runnable_sum=WALTb95ca9f31b(WALT17abc14e87,rq);return;}WALT02a8afcd23:if(
!is_idle_task(WALT0609dbaf9d)&&!exiting_task(WALT0609dbaf9d))WALT81ac526b7a(
WALT0609dbaf9d,rq,WALT394bc84586,WALT3b5207d436,WALTdd3d5a87d4);}static inline 
u32 WALTfa0202d8d2(struct task_struct*WALT0609dbaf9d,u32 WALT8a690d3852){int 
WALT57acf293db;u32 pred_demand;if(!sched_predl)return(0xfdf+4564-0x21b3);
WALT57acf293db=WALT5161a2cdf5(WALT8a690d3852);pred_demand=WALTd706aa2c09(
WALT0609dbaf9d,WALT57acf293db,WALT8a690d3852);WALTcd30d5f093(WALT0609dbaf9d->
ravg.busy_buckets,WALT57acf293db);return pred_demand;}static int WALT9e189b41d3(
struct rq*rq,struct task_struct*WALT0609dbaf9d,int WALT3205babe24){if(
exiting_task(WALT0609dbaf9d)||is_idle_task(WALT0609dbaf9d))return
(0x13ec+1774-0x1ada);if(WALT3205babe24==TASK_WAKE||(!WALT19b86f3ee0&&(
WALT3205babe24==PICK_NEXT_TASK||WALT3205babe24==TASK_MIGRATE)))return
(0x16c6+65-0x1707);if(WALT3205babe24==PICK_NEXT_TASK&&rq->curr==rq->idle)return
(0x100c+5447-0x2553);if(WALT3205babe24==TASK_UPDATE){if(rq->curr==WALT0609dbaf9d
)return(0x1939+2068-0x214c);return WALT0609dbaf9d->on_rq?WALT19b86f3ee0:
(0x1795+75-0x17e0);}return(0x2015+1179-0x24af);}unsigned int 
sysctl_sched_task_unfilter_period=200000000;static void WALT5807425a04(struct rq
*rq,struct task_struct*WALT0609dbaf9d,u32 WALT8a690d3852,int WALT7d946df0fb,int 
WALT3205babe24){u32*WALT53b45fa17b=&WALT0609dbaf9d->ravg.sum_history[
(0xbd8+5661-0x21f5)];int WALT7a1e3fe84e,WALTc98feb876b;u32 max=(0xb1+267-0x1bc),
WALTf034c4ad57,demand,pred_demand;u64 sum=(0x774+2333-0x1091);u16 demand_scaled,
pred_demand_scaled;if(!WALT8a690d3852||is_idle_task(WALT0609dbaf9d)||
exiting_task(WALT0609dbaf9d)||!WALT7d946df0fb)goto WALT02a8afcd23;WALTc98feb876b
=WALTa591b9e54c-(0x2190+282-0x22a9);WALT7a1e3fe84e=WALTc98feb876b-WALT7d946df0fb
;for(;WALT7a1e3fe84e>=(0x1eab+1486-0x2479);--WALTc98feb876b,--WALT7a1e3fe84e){
WALT53b45fa17b[WALTc98feb876b]=WALT53b45fa17b[WALT7a1e3fe84e];sum+=
WALT53b45fa17b[WALTc98feb876b];if(WALT53b45fa17b[WALTc98feb876b]>max)max=
WALT53b45fa17b[WALTc98feb876b];}for(WALTc98feb876b=(0x22c1+1065-0x26ea);
WALTc98feb876b<WALT7d946df0fb&&WALTc98feb876b<WALTa591b9e54c;WALTc98feb876b++){
WALT53b45fa17b[WALTc98feb876b]=WALT8a690d3852;sum+=WALT53b45fa17b[WALTc98feb876b
];if(WALT53b45fa17b[WALTc98feb876b]>max)max=WALT53b45fa17b[WALTc98feb876b];}
WALT0609dbaf9d->ravg.sum=(0xcd1+1617-0x1322);if(sysctl_sched_window_stats_policy
==WINDOW_STATS_RECENT){demand=WALT8a690d3852;}else if(
sysctl_sched_window_stats_policy==WINDOW_STATS_MAX){demand=max;}else{
WALTf034c4ad57=div64_u64(sum,WALTa591b9e54c);if(sysctl_sched_window_stats_policy
==WINDOW_STATS_AVG)demand=WALTf034c4ad57;else demand=max(WALTf034c4ad57,
WALT8a690d3852);}pred_demand=WALTfa0202d8d2(WALT0609dbaf9d,WALT8a690d3852);
demand_scaled=WALTecf40170d4(demand);pred_demand_scaled=WALTecf40170d4(
pred_demand);if(!task_has_dl_policy(WALT0609dbaf9d)||!WALT0609dbaf9d->dl.
dl_throttled){if(task_on_rq_queued(WALT0609dbaf9d))WALT69efd235f7(rq,
WALT0609dbaf9d,demand_scaled,pred_demand_scaled);else if(rq->curr==
WALT0609dbaf9d)walt_fixup_cum_window_demand(rq,demand_scaled);}WALT0609dbaf9d->
ravg.demand=demand;WALT0609dbaf9d->ravg.demand_scaled=demand_scaled;
WALT0609dbaf9d->ravg.coloc_demand=div64_u64(sum,WALTa591b9e54c);WALT0609dbaf9d->
ravg.pred_demand=pred_demand;WALT0609dbaf9d->ravg.pred_demand_scaled=
pred_demand_scaled;if(demand_scaled>sched_task_filter_util)WALT0609dbaf9d->
unfilter=sysctl_sched_task_unfilter_period;else if(WALT0609dbaf9d->unfilter)
WALT0609dbaf9d->unfilter=max_t(int,(0x1319+4355-0x241c),WALT0609dbaf9d->unfilter
-WALT0609dbaf9d->ravg.last_win_size);WALT02a8afcd23:trace_sched_update_history(
rq,WALT0609dbaf9d,WALT8a690d3852,WALT7d946df0fb,WALT3205babe24);}static u64 
WALTd042bf0817(struct rq*rq,struct task_struct*WALT0609dbaf9d,u64 WALT17abc14e87
){WALT17abc14e87=WALTb95ca9f31b(WALT17abc14e87,rq);WALT0609dbaf9d->ravg.sum+=
WALT17abc14e87;if(unlikely(WALT0609dbaf9d->ravg.sum>sched_ravg_window))
WALT0609dbaf9d->ravg.sum=sched_ravg_window;return WALT17abc14e87;}static u64 
WALTd61ac3ed43(struct task_struct*WALT0609dbaf9d,struct rq*rq,int WALT3205babe24
,u64 WALT790680e4aa){u64 mark_start=WALT0609dbaf9d->ravg.mark_start;u64 
WALT17abc14e87,window_start=rq->window_start;int WALT3b5207d436,WALT51e91ddbe6;
u32 WALT4ae816ebd1=sched_ravg_window;u64 WALT8a690d3852;WALT3b5207d436=
mark_start<window_start;if(!WALT9e189b41d3(rq,WALT0609dbaf9d,WALT3205babe24)){if
(WALT3b5207d436)WALT5807425a04(rq,WALT0609dbaf9d,WALT0609dbaf9d->ravg.sum,
(0x1aa0+602-0x1cf9),WALT3205babe24);return(0x527+6296-0x1dbf);}if(!
WALT3b5207d436){return WALTd042bf0817(rq,WALT0609dbaf9d,WALT790680e4aa-
mark_start);}WALT17abc14e87=window_start-mark_start;WALT51e91ddbe6=div64_u64(
WALT17abc14e87,WALT4ae816ebd1);window_start-=(u64)WALT51e91ddbe6*(u64)
WALT4ae816ebd1;WALT8a690d3852=WALTd042bf0817(rq,WALT0609dbaf9d,window_start-
mark_start);WALT5807425a04(rq,WALT0609dbaf9d,WALT0609dbaf9d->ravg.sum,
(0x11ac+1739-0x1876),WALT3205babe24);if(WALT51e91ddbe6){u64 WALTa08f625e72=
WALTb95ca9f31b(WALT4ae816ebd1,rq);WALT5807425a04(rq,WALT0609dbaf9d,
WALTa08f625e72,WALT51e91ddbe6,WALT3205babe24);WALT8a690d3852+=WALT51e91ddbe6*
WALTa08f625e72;}window_start+=(u64)WALT51e91ddbe6*(u64)WALT4ae816ebd1;mark_start
=window_start;WALT8a690d3852+=WALTd042bf0817(rq,WALT0609dbaf9d,WALT790680e4aa-
mark_start);return WALT8a690d3852;}static inline unsigned int cpu_cur_freq(int 
cpu){return cpu_rq(cpu)->cluster->cur_freq;}static void WALTeaadfc2aba(struct 
task_struct*WALT0609dbaf9d,struct rq*rq,int WALT3205babe24,u64 WALT790680e4aa,
u64 WALT59018c6914){u64 WALT6f5b2bdad3;u64 WALT88024db1de;u64 WALT6d1d7700ef;int
 cpu=cpu_of(rq);lockdep_assert_held(&rq->lock);if(!WALT3b880410aa){rq->
task_exec_scale=WALT20b422fc7b(cpu_cur_freq(cpu)*arch_scale_cpu_capacity(cpu),rq
->cluster->max_possible_freq);return;}WALT6f5b2bdad3=WALT2cd0d15eb3(cpu,
WALT790680e4aa);if(!is_idle_task(rq->curr)||WALT59018c6914){if(unlikely(
WALT6f5b2bdad3<WALT0609dbaf9d->cpu_cycles))WALT88024db1de=WALT6f5b2bdad3+(
U64_MAX-WALT0609dbaf9d->cpu_cycles);else WALT88024db1de=WALT6f5b2bdad3-
WALT0609dbaf9d->cpu_cycles;WALT88024db1de=WALT88024db1de*NSEC_PER_MSEC;if(
WALT3205babe24==IRQ_UPDATE&&is_idle_task(WALT0609dbaf9d))WALT6d1d7700ef=
WALT59018c6914;else WALT6d1d7700ef=WALT790680e4aa-WALT0609dbaf9d->ravg.
mark_start;WALT609fba09ac((s64)WALT6d1d7700ef<(0x441+576-0x681));rq->
task_exec_scale=WALT20b422fc7b(WALT88024db1de*arch_scale_cpu_capacity(cpu),
WALT6d1d7700ef*rq->cluster->max_possible_freq);trace_sched_get_task_cpu_cycles(
cpu,WALT3205babe24,WALT88024db1de,WALT6d1d7700ef,WALT0609dbaf9d);}WALT0609dbaf9d
->cpu_cycles=WALT6f5b2bdad3;}static inline void WALT4f54d6a4cc(u64 
WALT901ba13dc5,struct rq*rq){u64 WALT5f54ca7c5e;if(WALT901ba13dc5==rq->
window_start)return;WALT5f54ca7c5e=atomic64_cmpxchg(&WALT8d508f7c3b,
WALT901ba13dc5,rq->window_start);if(WALT5f54ca7c5e==WALT901ba13dc5)
WALTa4ccf3d6c9(&WALT5bb9cd73e7);}void walt_update_task_ravg(struct task_struct*
WALT0609dbaf9d,struct rq*rq,int WALT3205babe24,u64 WALT790680e4aa,u64 
WALT59018c6914){u64 WALT901ba13dc5;if(!rq->window_start||WALT0609dbaf9d->ravg.
mark_start==WALT790680e4aa)return;lockdep_assert_held(&rq->lock);WALT901ba13dc5=
WALT6bdc3765bb(rq,WALT790680e4aa,WALT3205babe24);if(!WALT0609dbaf9d->ravg.
mark_start){WALT1360b17c9b(WALT0609dbaf9d,cpu_of(rq),WALT790680e4aa);goto 
WALT02a8afcd23;}WALTeaadfc2aba(WALT0609dbaf9d,rq,WALT3205babe24,WALT790680e4aa,
WALT59018c6914);WALTd61ac3ed43(WALT0609dbaf9d,rq,WALT3205babe24,WALT790680e4aa);
WALT130dee47f1(WALT0609dbaf9d,rq,WALT3205babe24,WALT790680e4aa,WALT59018c6914);
WALTbc967ce57f(rq,WALT0609dbaf9d,WALT3205babe24);if(exiting_task(WALT0609dbaf9d)
)goto WALT02a8afcd23;trace_sched_update_task_ravg(WALT0609dbaf9d,rq,
WALT3205babe24,WALT790680e4aa,WALT59018c6914,&rq->grp_time);
trace_sched_update_task_ravg_mini(WALT0609dbaf9d,rq,WALT3205babe24,
WALT790680e4aa,WALT59018c6914,&rq->grp_time);WALT02a8afcd23:WALT0609dbaf9d->ravg
.mark_start=WALT790680e4aa;WALT0609dbaf9d->ravg.last_win_size=sched_ravg_window;
WALT4f54d6a4cc(WALT901ba13dc5,rq);}u32 sched_get_init_task_load(struct 
task_struct*WALT0609dbaf9d){return WALT0609dbaf9d->init_load_pct;}int 
sched_set_init_task_load(struct task_struct*WALT0609dbaf9d,int init_load_pct){if
(init_load_pct<(0x152+5145-0x156b)||init_load_pct>(0xf41+1747-0x15b0))return-
EINVAL;WALT0609dbaf9d->init_load_pct=init_load_pct;return(0x532+4276-0x15e6);}
void init_new_task_load(struct task_struct*WALT0609dbaf9d){int WALT5d971be8b8;
u32 WALTb5ef75b5b9=sched_init_task_load_windows;u32 WALTbec959d3fa=
WALTb0bc76dcf5;u32 init_load_pct=current->init_load_pct;WALT0609dbaf9d->
init_load_pct=(0x3a3+353-0x504);rcu_assign_pointer(WALT0609dbaf9d->grp,NULL);
INIT_LIST_HEAD(&WALT0609dbaf9d->grp_list);memset(&WALT0609dbaf9d->ravg,
(0x2e2+5276-0x177e),sizeof(struct ravg));WALT0609dbaf9d->cpu_cycles=
(0x77f+2004-0xf53);WALT0609dbaf9d->ravg.curr_window_cpu=kcalloc(nr_cpu_ids,
sizeof(u32),GFP_KERNEL|__GFP_NOFAIL);WALT0609dbaf9d->ravg.prev_window_cpu=
kcalloc(nr_cpu_ids,sizeof(u32),GFP_KERNEL|__GFP_NOFAIL);if(init_load_pct){
WALTb5ef75b5b9=div64_u64((u64)init_load_pct*(u64)sched_ravg_window,
(0x995+6218-0x217b));WALTbec959d3fa=WALTecf40170d4(WALTb5ef75b5b9);}
WALT0609dbaf9d->ravg.demand=WALTb5ef75b5b9;WALT0609dbaf9d->ravg.demand_scaled=
WALTbec959d3fa;WALT0609dbaf9d->ravg.coloc_demand=WALTb5ef75b5b9;WALT0609dbaf9d->
ravg.pred_demand=(0xf95+4235-0x2020);WALT0609dbaf9d->ravg.pred_demand_scaled=
(0x32c+8694-0x2522);for(WALT5d971be8b8=(0x23ad+305-0x24de);WALT5d971be8b8<
RAVG_HIST_SIZE_MAX;++WALT5d971be8b8)WALT0609dbaf9d->ravg.sum_history[
WALT5d971be8b8]=WALTb5ef75b5b9;WALT0609dbaf9d->misfit=false;WALT0609dbaf9d->
unfilter=sysctl_sched_task_unfilter_period;}void free_task_load_ptrs(struct 
task_struct*WALT0609dbaf9d){kfree(WALT0609dbaf9d->ravg.curr_window_cpu);kfree(
WALT0609dbaf9d->ravg.prev_window_cpu);WALT0609dbaf9d->ravg.curr_window_cpu=NULL;
WALT0609dbaf9d->ravg.prev_window_cpu=NULL;}void reset_task_stats(struct 
task_struct*WALT0609dbaf9d){u32 sum=(0x7b4+2981-0x1359);u32*WALTd74c5f0f49=NULL;
u32*WALT72caf72ca7=NULL;if(exiting_task(WALT0609dbaf9d)){sum=EXITING_TASK_MARKER
;}else{WALTd74c5f0f49=WALT0609dbaf9d->ravg.curr_window_cpu;WALT72caf72ca7=
WALT0609dbaf9d->ravg.prev_window_cpu;memset(WALTd74c5f0f49,(0x89+1269-0x57e),
sizeof(u32)*nr_cpu_ids);memset(WALT72caf72ca7,(0x437+4659-0x166a),sizeof(u32)*
nr_cpu_ids);}memset(&WALT0609dbaf9d->ravg,(0x13b2+3834-0x22ac),sizeof(struct 
ravg));WALT0609dbaf9d->ravg.curr_window_cpu=WALTd74c5f0f49;WALT0609dbaf9d->ravg.
prev_window_cpu=WALT72caf72ca7;WALT0609dbaf9d->ravg.sum_history[
(0x112b+215-0x1202)]=sum;}void mark_task_starting(struct task_struct*
WALT0609dbaf9d){u64 WALT790680e4aa;struct rq*rq=task_rq(WALT0609dbaf9d);if(!rq->
window_start){reset_task_stats(WALT0609dbaf9d);return;}WALT790680e4aa=
sched_ktime_clock();WALT0609dbaf9d->ravg.mark_start=WALT0609dbaf9d->last_wake_ts
=WALT790680e4aa;WALT0609dbaf9d->last_enqueued_ts=WALT790680e4aa;WALT1360b17c9b(
WALT0609dbaf9d,cpu_of(rq),WALT790680e4aa);}unsigned int __read_mostly 
sched_group_upmigrate=20000000;unsigned int __read_mostly 
sysctl_sched_group_upmigrate_pct=(0x1a41+3159-0x2634);unsigned int __read_mostly
 sched_group_downmigrate=19000000;unsigned int __read_mostly 
sysctl_sched_group_downmigrate_pct=(0x457+6767-0x1e67);static inline void 
WALTfbcbf0e27a(void){unsigned int WALT6ace768b42=arch_scale_cpu_capacity(
cluster_first_cpu(sched_cluster[(0x1979+419-0x1b1c)]));u64 WALT205fc9f073=(
sched_ravg_window*WALT6ace768b42)>>SCHED_CAPACITY_SHIFT;sched_group_upmigrate=
div64_ul(WALT205fc9f073*sysctl_sched_group_upmigrate_pct,(0x1d58+1889-0x2455));
sched_group_downmigrate=div64_ul(WALT205fc9f073*
sysctl_sched_group_downmigrate_pct,(0x764+883-0xa73));}struct sched_cluster*
sched_cluster[NR_CPUS];__read_mostly int num_sched_clusters;struct list_head 
cluster_head;cpumask_t asym_cap_sibling_cpus=CPU_MASK_NONE;static struct 
sched_cluster WALT2d02e5bf36={.list=LIST_HEAD_INIT(WALT2d02e5bf36.list),.id=
(0x99a+615-0xc01),.cur_freq=(0x54+2057-0x85c),.max_possible_freq=
(0x1a0+2508-0xb6b),.aggr_grp_load=(0x132+1291-0x63d),};void init_clusters(void){
WALT2d02e5bf36.cpus=*cpu_possible_mask;raw_spin_lock_init(&WALT2d02e5bf36.
load_lock);INIT_LIST_HEAD(&cluster_head);list_add(&WALT2d02e5bf36.list,&
cluster_head);}static void WALT9cd889a347(struct sched_cluster*cluster,struct 
list_head*WALT4464c6f5dc){struct sched_cluster*WALTb9b0dca770;struct list_head*
WALT83f88df353=WALT4464c6f5dc;list_for_each_entry(WALTb9b0dca770,WALT4464c6f5dc,
list){if(arch_scale_cpu_capacity(cluster_first_cpu(cluster))<
arch_scale_cpu_capacity(cluster_first_cpu(WALTb9b0dca770)))break;WALT83f88df353=
&WALTb9b0dca770->list;}list_add(&cluster->list,WALT83f88df353);}static struct 
sched_cluster*WALT209e94ab80(const struct cpumask*cpus){struct sched_cluster*
cluster=NULL;cluster=kzalloc(sizeof(struct sched_cluster),GFP_ATOMIC);if(!
cluster){pr_warn(
"\x43\x6c\x75\x73\x74\x65\x72\x20\x61\x6c\x6c\x6f\x63\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x50\x6f\x73\x73\x69\x62\x6c\x65\x20\x62\x61\x64\x20\x73\x63\x68\x65\x64\x75\x6c\x69\x6e\x67" "\n"
);return NULL;}INIT_LIST_HEAD(&cluster->list);cluster->cur_freq=
(0x195+8469-0x22a9);cluster->max_possible_freq=(0xaaa+1761-0x118a);
raw_spin_lock_init(&cluster->load_lock);cluster->cpus=*cpus;return cluster;}
static void WALT2273ecae7d(const struct cpumask*cpus,struct list_head*
WALT4464c6f5dc){struct sched_cluster*cluster=WALT209e94ab80(cpus);int 
WALT5d971be8b8;if(!cluster)return;for_each_cpu(WALT5d971be8b8,cpus)cpu_rq(
WALT5d971be8b8)->cluster=cluster;WALT9cd889a347(cluster,WALT4464c6f5dc);
num_sched_clusters++;}static void WALT3ccb151752(struct list_head*WALT4464c6f5dc
){struct sched_cluster*cluster,*WALTb9b0dca770;int WALT5d971be8b8;
list_for_each_entry_safe(cluster,WALTb9b0dca770,WALT4464c6f5dc,list){
for_each_cpu(WALT5d971be8b8,&cluster->cpus)cpu_rq(WALT5d971be8b8)->cluster=&
WALT2d02e5bf36;list_del(&cluster->list);num_sched_clusters--;kfree(cluster);}}
static inline void assign_cluster_ids(struct list_head*WALT4464c6f5dc){struct 
sched_cluster*cluster;int WALT7609b61ad1=(0x2a1+7623-0x2068);list_for_each_entry
(cluster,WALT4464c6f5dc,list){cluster->id=WALT7609b61ad1;sched_cluster[
WALT7609b61ad1++]=cluster;}WARN_ON(WALT7609b61ad1>MAX_NR_CLUSTERS);}static 
inline void move_list(struct list_head*WALT6f47937b7c,struct list_head*
WALT792740f2d5,bool WALT0a017c4f94){struct list_head*WALTc4b85e3bbe,*
WALTc636d24b23;WALTc4b85e3bbe=WALT792740f2d5->next;WALTc636d24b23=WALT792740f2d5
->prev;if(WALT0a017c4f94){INIT_LIST_HEAD_RCU(WALT792740f2d5);synchronize_rcu();}
WALTc4b85e3bbe->prev=WALT6f47937b7c;WALT6f47937b7c->prev=WALTc636d24b23;
WALTc636d24b23->next=WALT6f47937b7c;smp_mb();WALT6f47937b7c->next=WALTc4b85e3bbe
;}static void WALT4ceaf4cda7(void){struct sched_cluster*cluster;u64 
WALTa85cf99964=(0x7b2+4802-0x1a74),WALTd350724547=U64_MAX;unsigned long flags;
WALT04b55e82dd(cpu_possible_mask,&flags);for_each_sched_cluster(cluster){u64 
WALT58a329c64d=arch_scale_cpu_capacity(cluster_first_cpu(cluster));if(
WALT58a329c64d>WALTa85cf99964)WALTa85cf99964=WALT58a329c64d;if(WALT58a329c64d<
WALTd350724547)WALTd350724547=WALT58a329c64d;}max_possible_capacity=
WALTa85cf99964;min_max_possible_capacity=WALTd350724547;WALTfbcbf0e27a();
WALTbe61fad8ce(cpu_possible_mask,&flags);}static bool WALTdd600935ff;
__read_mostly cpumask_t**cpu_array;static cpumask_t**WALT52a1ef5417(void){int 
WALT5d971be8b8;cpumask_t**WALTe421f3d6a7;WALTe421f3d6a7=kcalloc(
num_sched_clusters,sizeof(cpumask_t*),GFP_ATOMIC);if(!WALTe421f3d6a7)return NULL
;for(WALT5d971be8b8=(0x41d+6035-0x1bb0);WALT5d971be8b8<num_sched_clusters;
WALT5d971be8b8++){WALTe421f3d6a7[WALT5d971be8b8]=kcalloc(num_sched_clusters,
sizeof(cpumask_t),GFP_ATOMIC);if(!WALTe421f3d6a7[WALT5d971be8b8])return NULL;}
return WALTe421f3d6a7;}static cpumask_t**WALT516ffeae8c(void){int WALT5d971be8b8
;cpumask_t**WALTe421f3d6a7=WALT52a1ef5417();if(!WALTe421f3d6a7)return NULL;for(
WALT5d971be8b8=(0x1580+204-0x164c);WALT5d971be8b8<num_sched_clusters;
WALT5d971be8b8++){int WALT2dc758aa44,WALT041cb91678=(0x17d4+1613-0x1e20);
cpumask_copy(&WALTe421f3d6a7[WALT5d971be8b8][(0x59c+1920-0xd1c)],&sched_cluster[
WALT5d971be8b8]->cpus);for(WALT2dc758aa44=WALT5d971be8b8+(0x522+8209-0x2532);
WALT2dc758aa44<num_sched_clusters;WALT2dc758aa44++){cpumask_copy(&WALTe421f3d6a7
[WALT5d971be8b8][WALT041cb91678],&sched_cluster[WALT2dc758aa44]->cpus);
WALT041cb91678++;}for(WALT2dc758aa44=WALT5d971be8b8-(0xd5a+5656-0x2371);
WALT2dc758aa44>=(0x9f9+427-0xba4);WALT2dc758aa44--){cpumask_copy(&WALTe421f3d6a7
[WALT5d971be8b8][WALT041cb91678],&sched_cluster[WALT2dc758aa44]->cpus);
WALT041cb91678++;}}return WALTe421f3d6a7;}void walt_update_cluster_topology(void
){struct cpumask cpus=*cpu_possible_mask;const struct cpumask*WALTf48c6e4ef8;
struct sched_cluster*cluster;struct list_head WALTd94226e3b2;cpumask_t**
WALTb9b0dca770;int WALT5d971be8b8;INIT_LIST_HEAD(&WALTd94226e3b2);for_each_cpu(
WALT5d971be8b8,&cpus){WALTf48c6e4ef8=topology_possible_sibling_cpumask(
WALT5d971be8b8);if(cpumask_empty(WALTf48c6e4ef8)){WARN((0x15d5+3065-0x21cd),
"\x57\x41\x4c\x54\x3a\x20\x49\x6e\x76\x61\x6c\x69\x64\x20\x63\x70\x75\x20\x74\x6f\x70\x6f\x6c\x6f\x67\x79\x21\x21"
);WALT3ccb151752(&WALTd94226e3b2);return;}cpumask_andnot(&cpus,&cpus,
WALTf48c6e4ef8);WALT2273ecae7d(WALTf48c6e4ef8,&WALTd94226e3b2);}
assign_cluster_ids(&WALTd94226e3b2);list_for_each_entry(cluster,&WALTd94226e3b2,
list){struct cpufreq_policy*policy;policy=cpufreq_cpu_get_raw(cluster_first_cpu(
cluster));WALT609fba09ac(!policy);cluster->max_possible_freq=policy->cpuinfo.
max_freq;for_each_cpu(WALT5d971be8b8,&cluster->cpus)cpumask_copy(&cpu_rq(
WALT5d971be8b8)->freq_domain_cpumask,policy->related_cpus);}move_list(&
cluster_head,&WALTd94226e3b2,false);WALT4ceaf4cda7();for_each_sched_cluster(
cluster){if(cpumask_weight(&cluster->cpus)==(0x4f7+7715-0x2319))cpumask_or(&
asym_cap_sibling_cpus,&asym_cap_sibling_cpus,&cluster->cpus);}if(cpumask_weight(
&asym_cap_sibling_cpus)==(0x1079+1719-0x172f))cpumask_clear(&
asym_cap_sibling_cpus);WALTb9b0dca770=WALT516ffeae8c();if(!WALTb9b0dca770){
BUG_ON((0xf10+2790-0x19f5));return;}smp_store_release(&cpu_array,WALTb9b0dca770)
;WALTdd600935ff=true;}static int WALT1b3d573ceb(struct notifier_block*
WALT9e976b309a,unsigned long WALTc94d3d8015,void*data){struct cpufreq_freqs*
WALTbd4095257b=(struct cpufreq_freqs*)data;unsigned int cpu=WALTbd4095257b->
policy->cpu,WALT21186056ab=WALTbd4095257b->new;unsigned long flags;struct 
sched_cluster*cluster;struct cpumask WALT6dfb01003b=cpu_rq(cpu)->
freq_domain_cpumask;int WALT5d971be8b8,WALT2dc758aa44;if(WALT3b880410aa)return 
NOTIFY_DONE;if(cpu_rq(cpumask_first(&WALT6dfb01003b))->cluster==&WALT2d02e5bf36)
return NOTIFY_DONE;if(WALTc94d3d8015!=CPUFREQ_POSTCHANGE)return NOTIFY_DONE;if(
cpu_cur_freq(cpu)==WALT21186056ab)return NOTIFY_OK;for_each_cpu(WALT5d971be8b8,&
WALT6dfb01003b){cluster=cpu_rq(WALT5d971be8b8)->cluster;for_each_cpu(
WALT2dc758aa44,&cluster->cpus){struct rq*rq=cpu_rq(WALT2dc758aa44);
raw_spin_lock_irqsave(&rq->lock,flags);walt_update_task_ravg(rq->curr,rq,
TASK_UPDATE,sched_ktime_clock(),(0xe41+1774-0x152f));raw_spin_unlock_irqrestore(
&rq->lock,flags);}cluster->cur_freq=WALT21186056ab;cpumask_andnot(&
WALT6dfb01003b,&WALT6dfb01003b,&cluster->cpus);}return NOTIFY_OK;}static struct 
notifier_block WALTcc7354a27f={.notifier_call=WALT1b3d573ceb};static int 
WALT0b2479e1f9(void){return cpufreq_register_notifier(&WALTcc7354a27f,
CPUFREQ_TRANSITION_NOTIFIER);}core_initcall(WALT0b2479e1f9);int 
register_cpu_cycle_counter_cb(struct cpu_cycle_counter_cb*WALT5303ed5f85){
unsigned long flags;mutex_lock(&WALT6e47d2c346);if(!WALT5303ed5f85->
get_cpu_cycle_counter){mutex_unlock(&WALT6e47d2c346);return-EINVAL;}
WALT04b55e82dd(cpu_possible_mask,&flags);cpu_cycle_counter_cb=*WALT5303ed5f85;
WALT3b880410aa=true;WALTbe61fad8ce(cpu_possible_mask,&flags);mutex_unlock(&
WALT6e47d2c346);cpufreq_unregister_notifier(&WALTcc7354a27f,
CPUFREQ_TRANSITION_NOTIFIER);return(0x1694+3824-0x2584);}static void 
WALT2c39f55a97(struct rq*rq,struct related_thread_group*grp,struct task_struct*
WALT0609dbaf9d,int WALT3205babe24);unsigned int __read_mostly WALT38c9c057a0;
unsigned int __read_mostly sysctl_sched_coloc_downmigrate_ns;struct 
related_thread_group*WALT7c7bf2c77f[MAX_NUM_CGROUP_COLOC_ID];static LIST_HEAD(
WALT929dec1bfc);static DEFINE_RWLOCK(WALTc37082022e);static inline void 
WALTb7252e9a3d(struct related_thread_group*grp,u64 demand,bool WALTf4f061ddc1){
if(WALTf4f061ddc1){grp->skip_min=false;return;}if(is_suh_max())demand=
sched_group_upmigrate;if(!grp->skip_min){if(demand>=sched_group_upmigrate){grp->
skip_min=true;}return;}if(demand<sched_group_downmigrate){if(!
sysctl_sched_coloc_downmigrate_ns){grp->skip_min=false;return;}if(!grp->
downmigrate_ts){grp->downmigrate_ts=grp->last_update;return;}if(grp->last_update
-grp->downmigrate_ts>sysctl_sched_coloc_downmigrate_ns){grp->downmigrate_ts=
(0x179a+3358-0x24b8);grp->skip_min=false;}}else if(grp->downmigrate_ts)grp->
downmigrate_ts=(0x176b+1332-0x1c9f);}int preferred_cluster(struct sched_cluster*
cluster,struct task_struct*WALT0609dbaf9d){struct related_thread_group*grp;int 
WALT094475d445=-(0xee9+3659-0x1d33);rcu_read_lock();grp=
task_related_thread_group(WALT0609dbaf9d);if(grp)WALT094475d445=(sched_cluster[(
int)grp->skip_min]==cluster||cpumask_subset(&cluster->cpus,&
asym_cap_sibling_cpus));rcu_read_unlock();return WALT094475d445;}static void 
WALTb53071212f(struct related_thread_group*grp){struct task_struct*
WALT0609dbaf9d;u64 WALTd26a455a6d=(0x680+5850-0x1d5a);bool WALT509eaf33de=false;
u64 WALT790680e4aa;bool WALT4288c41a52=grp->skip_min;if(list_empty(&grp->tasks))
{grp->skip_min=false;goto WALTe1f307999b;}if(!hmp_capable()){grp->skip_min=false
;goto WALTe1f307999b;}WALT790680e4aa=sched_ktime_clock();if(WALT790680e4aa-grp->
last_update<sched_ravg_window/(0x5b5+3332-0x12af))return;list_for_each_entry(
WALT0609dbaf9d,&grp->tasks,grp_list){if(task_boost_policy(WALT0609dbaf9d)==
SCHED_BOOST_ON_BIG){WALT509eaf33de=true;break;}if(WALT0609dbaf9d->ravg.
mark_start<WALT790680e4aa-(sched_ravg_window*WALTa591b9e54c))continue;
WALTd26a455a6d+=WALT0609dbaf9d->ravg.coloc_demand;if(!
trace_sched_set_preferred_cluster_enabled()){if(WALTd26a455a6d>
sched_group_upmigrate)break;}}grp->last_update=WALT790680e4aa;WALTb7252e9a3d(grp
,WALTd26a455a6d,WALT509eaf33de);trace_sched_set_preferred_cluster(grp,
WALTd26a455a6d);WALTe1f307999b:if(grp->id==DEFAULT_CGROUP_COLOC_ID&&grp->
skip_min!=WALT4288c41a52){if(grp->skip_min)grp->start_ts=sched_clock();
sched_update_hyst_times();}}void set_preferred_cluster(struct 
related_thread_group*grp){raw_spin_lock(&grp->lock);WALTb53071212f(grp);
raw_spin_unlock(&grp->lock);}int update_preferred_cluster(struct 
related_thread_group*grp,struct task_struct*WALT0609dbaf9d,u32 WALT3678748cf3,
bool WALT53c3aaf16d){u32 WALT30f2685d2b=task_load(WALT0609dbaf9d);if(!grp)return
(0x48b+8640-0x264b);if(unlikely(WALT53c3aaf16d&&is_suh_max()))return
(0x17f4+3661-0x2640);if(abs(WALT30f2685d2b-WALT3678748cf3)>sched_ravg_window/
(0x46+8215-0x2059)||sched_ktime_clock()-grp->last_update>sched_ravg_window)
return(0x78f+1980-0xf4a);return(0x26b+740-0x54f);}
#define WALTdebf0e8b8a	(0x2d5+1495-0x8ac)
#define WALT56968f5b11	(0x8d1+1952-0x1070)
static inline struct related_thread_group*WALTaf37716888(unsigned int 
WALTe3d424fbb1){return WALT7c7bf2c77f[WALTe3d424fbb1];}int 
alloc_related_thread_groups(void){int WALT5d971be8b8,WALT083920bcc8;struct 
related_thread_group*grp;for(WALT5d971be8b8=(0x1871+360-0x19d8);WALT5d971be8b8<
MAX_NUM_CGROUP_COLOC_ID;WALT5d971be8b8++){grp=kzalloc(sizeof(*grp),GFP_NOWAIT);
if(!grp){WALT083920bcc8=-ENOMEM;goto WALT2839a901be;}grp->id=WALT5d971be8b8;
INIT_LIST_HEAD(&grp->tasks);INIT_LIST_HEAD(&grp->list);raw_spin_lock_init(&grp->
lock);WALT7c7bf2c77f[WALT5d971be8b8]=grp;}return(0x5d6+6148-0x1dda);
WALT2839a901be:for(WALT5d971be8b8=(0x6e4+463-0x8b2);WALT5d971be8b8<
MAX_NUM_CGROUP_COLOC_ID;WALT5d971be8b8++){grp=WALTaf37716888(WALT5d971be8b8);if(
grp){kfree(grp);WALT7c7bf2c77f[WALT5d971be8b8]=NULL;}else{break;}}return 
WALT083920bcc8;}static void WALT8787eee242(struct task_struct*WALT0609dbaf9d){
struct related_thread_group*grp=WALT0609dbaf9d->grp;struct rq*rq;int 
WALTebef427696=(0xd2b+2288-0x161a);struct rq_flags WALT8d267b09c4;raw_spin_lock(
&grp->lock);rq=__task_rq_lock(WALT0609dbaf9d,&WALT8d267b09c4);WALT2c39f55a97(rq,
WALT0609dbaf9d->grp,WALT0609dbaf9d,WALT56968f5b11);list_del_init(&WALT0609dbaf9d
->grp_list);rcu_assign_pointer(WALT0609dbaf9d->grp,NULL);__task_rq_unlock(rq,&
WALT8d267b09c4);if(!list_empty(&grp->tasks)){WALTebef427696=(0x33a+7163-0x1f35);
WALTb53071212f(grp);}raw_spin_unlock(&grp->lock);if(WALTebef427696&&grp->id!=
DEFAULT_CGROUP_COLOC_ID)list_del_init(&grp->list);}static int WALT20198aa4d2(
struct task_struct*WALT0609dbaf9d,struct related_thread_group*grp){struct rq*rq;
struct rq_flags WALT8d267b09c4;raw_spin_lock(&grp->lock);rq=__task_rq_lock(
WALT0609dbaf9d,&WALT8d267b09c4);WALT2c39f55a97(rq,grp,WALT0609dbaf9d,
WALTdebf0e8b8a);list_add(&WALT0609dbaf9d->grp_list,&grp->tasks);
rcu_assign_pointer(WALT0609dbaf9d->grp,grp);__task_rq_unlock(rq,&WALT8d267b09c4)
;WALTb53071212f(grp);raw_spin_unlock(&grp->lock);return(0x16f+6692-0x1b93);}void
 add_new_task_to_grp(struct task_struct*new){unsigned long flags;struct 
related_thread_group*grp;struct task_struct*WALT38944a4944=new->group_leader;
unsigned int WALTd6dfed7cd3=sched_get_group_id(WALT38944a4944);if(!
WALT38c9c057a0&&WALTd6dfed7cd3!=DEFAULT_CGROUP_COLOC_ID)return;if(
thread_group_leader(new))return;if(WALTd6dfed7cd3==DEFAULT_CGROUP_COLOC_ID){if(!
(task_group(new)==task_group(WALT38944a4944)))return;}write_lock_irqsave(&
WALTc37082022e,flags);rcu_read_lock();grp=task_related_thread_group(
WALT38944a4944);rcu_read_unlock();if(!grp||new->grp){write_unlock_irqrestore(&
WALTc37082022e,flags);return;}raw_spin_lock(&grp->lock);rcu_assign_pointer(new->
grp,grp);list_add(&new->grp_list,&grp->tasks);raw_spin_unlock(&grp->lock);
write_unlock_irqrestore(&WALTc37082022e,flags);}static int WALT3f0a317889(struct
 task_struct*WALT0609dbaf9d,unsigned int WALTe3d424fbb1){int WALT094475d445=
(0x611+2264-0xee9);unsigned long flags;struct related_thread_group*grp=NULL;if(
WALTe3d424fbb1>=MAX_NUM_CGROUP_COLOC_ID)return-EINVAL;raw_spin_lock_irqsave(&
WALT0609dbaf9d->pi_lock,flags);write_lock(&WALTc37082022e);if((current!=
WALT0609dbaf9d&&WALT0609dbaf9d->flags&PF_EXITING)||(!WALT0609dbaf9d->grp&&!
WALTe3d424fbb1)||(WALT0609dbaf9d->grp&&WALTe3d424fbb1))goto WALT02a8afcd23;if(!
WALTe3d424fbb1){WALT8787eee242(WALT0609dbaf9d);goto WALT02a8afcd23;}grp=
WALTaf37716888(WALTe3d424fbb1);if(list_empty(&grp->list))list_add(&grp->list,&
WALT929dec1bfc);WALT094475d445=WALT20198aa4d2(WALT0609dbaf9d,grp);WALT02a8afcd23
:write_unlock(&WALTc37082022e);raw_spin_unlock_irqrestore(&WALT0609dbaf9d->
pi_lock,flags);return WALT094475d445;}int sched_set_group_id(struct task_struct*
WALT0609dbaf9d,unsigned int WALTe3d424fbb1){if(WALTe3d424fbb1==
DEFAULT_CGROUP_COLOC_ID)return-EINVAL;return WALT3f0a317889(WALT0609dbaf9d,
WALTe3d424fbb1);}unsigned int sched_get_group_id(struct task_struct*
WALT0609dbaf9d){unsigned int WALTe3d424fbb1;struct related_thread_group*grp;
rcu_read_lock();grp=task_related_thread_group(WALT0609dbaf9d);WALTe3d424fbb1=grp
?grp->id:(0xe43+3691-0x1cae);rcu_read_unlock();return WALTe3d424fbb1;}
#if defined(CONFIG_UCLAMP_TASK_GROUP)
static int __init WALT9d6579065e(void){struct related_thread_group*grp=NULL;
unsigned long flags;grp=WALTaf37716888(DEFAULT_CGROUP_COLOC_ID);
write_lock_irqsave(&WALTc37082022e,flags);list_add(&grp->list,&WALT929dec1bfc);
write_unlock_irqrestore(&WALTc37082022e,flags);return(0x1bb+4802-0x147d);}
late_initcall(WALT9d6579065e);int sync_cgroup_colocation(struct task_struct*
WALT0609dbaf9d,bool WALT605be289c8){unsigned int WALT76b79b2ac3=WALT605be289c8?
DEFAULT_CGROUP_COLOC_ID:(0x94c+2999-0x1503);return WALT3f0a317889(WALT0609dbaf9d
,WALT76b79b2ac3);}
#endif
static bool WALT0bb76a2e0a(struct sched_cluster*cluster){struct 
related_thread_group*grp;bool WALT3b12e8b981;grp=WALTaf37716888(
DEFAULT_CGROUP_COLOC_ID);if(!grp)return false;WALT3b12e8b981=!grp->skip_min&&(
sched_boost_policy()!=SCHED_BOOST_ON_BIG);return(is_min_capacity_cluster(cluster
)==WALT3b12e8b981);}static unsigned long WALT93f1afe3f9[NR_CPUS];unsigned long 
thermal_cap(int cpu){return WALT93f1afe3f9[cpu]?:SCHED_CAPACITY_SCALE;}static 
inline unsigned long WALTa877a3f404(int cpu,unsigned long WALT83b213a9c5){if(
unlikely(!WALTdd600935ff))return capacity_orig_of(cpu);return mult_frac(
arch_scale_cpu_capacity(cpu),WALT83b213a9c5,cpu_max_possible_freq(cpu));}static 
DEFINE_SPINLOCK(cpu_freq_min_max_lock);void sched_update_cpu_freq_min_max(const 
cpumask_t*cpus,u32 WALT6d51f2da16,u32 WALTa52cccd9d0){struct cpumask cpumask;
struct sched_cluster*cluster;int WALT5d971be8b8;unsigned long flags;
spin_lock_irqsave(&cpu_freq_min_max_lock,flags);cpumask_copy(&cpumask,cpus);
for_each_cpu(WALT5d971be8b8,&cpumask)WALT93f1afe3f9[WALT5d971be8b8]=
WALTa877a3f404(WALT5d971be8b8,WALTa52cccd9d0);for_each_cpu(WALT5d971be8b8,&
cpumask){cluster=cpu_rq(WALT5d971be8b8)->cluster;cpumask_andnot(&cpumask,&
cpumask,&cluster->cpus);}spin_unlock_irqrestore(&cpu_freq_min_max_lock,flags);}
void note_task_waking(struct task_struct*WALT0609dbaf9d,u64 WALT790680e4aa){
WALT0609dbaf9d->last_wake_ts=WALT790680e4aa;}static void WALT2c39f55a97(struct 
rq*rq,struct related_thread_group*grp,struct task_struct*WALT0609dbaf9d,int 
WALT3205babe24){u64 WALT790680e4aa;struct group_cpu_time*WALT627d50b29d;u64*
WALT42b4427a2c,*WALT2e4da9dbb4;u64*WALT262b512e81,*WALT086b45bedf;u64*
WALTf7e69c10fd,*WALT847919a57a;u64*WALT7ba10de4f4,*WALT082a99fd0f;int 
WALT0504870d67;int cpu=cpu_of(rq);bool WALT5eebbbffe9;int WALT5d971be8b8;
WALT790680e4aa=sched_ktime_clock();walt_update_task_ravg(rq->curr,rq,TASK_UPDATE
,WALT790680e4aa,(0x1ac4+83-0x1b17));walt_update_task_ravg(WALT0609dbaf9d,rq,
TASK_UPDATE,WALT790680e4aa,(0x663+180-0x717));WALT5eebbbffe9=is_new_task(
WALT0609dbaf9d);WALT627d50b29d=&rq->grp_time;if(WALT3205babe24==WALTdebf0e8b8a){
WALT0504870d67=RQ_TO_GROUP;WALT42b4427a2c=&rq->curr_runnable_sum;WALT2e4da9dbb4=
&WALT627d50b29d->curr_runnable_sum;WALT262b512e81=&rq->prev_runnable_sum;
WALT086b45bedf=&WALT627d50b29d->prev_runnable_sum;WALTf7e69c10fd=&rq->
nt_curr_runnable_sum;WALT847919a57a=&WALT627d50b29d->nt_curr_runnable_sum;
WALT7ba10de4f4=&rq->nt_prev_runnable_sum;WALT082a99fd0f=&WALT627d50b29d->
nt_prev_runnable_sum;if(*WALT42b4427a2c<WALT0609dbaf9d->ravg.curr_window_cpu[cpu
]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,cpu,WALT3205babe24,*WALT42b4427a2c,WALT0609dbaf9d->ravg.
curr_window_cpu[cpu]);WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac(
(0x1a4d+232-0x1b34));}*WALT42b4427a2c-=WALT0609dbaf9d->ravg.curr_window_cpu[cpu]
;if(*WALT262b512e81<WALT0609dbaf9d->ravg.prev_window_cpu[cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,cpu,WALT3205babe24,*WALT262b512e81,WALT0609dbaf9d->ravg.
prev_window_cpu[cpu]);WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac(
(0xf44+5672-0x256b));}*WALT262b512e81-=WALT0609dbaf9d->ravg.prev_window_cpu[cpu]
;if(WALT5eebbbffe9){if(*WALTf7e69c10fd<WALT0609dbaf9d->ravg.curr_window_cpu[cpu]
){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,cpu,WALT3205babe24,*WALTf7e69c10fd,WALT0609dbaf9d->ravg.
curr_window_cpu[cpu]);WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac(
(0x1028+5813-0x26dc));}*WALTf7e69c10fd-=WALT0609dbaf9d->ravg.curr_window_cpu[cpu
];if(*WALT7ba10de4f4<WALT0609dbaf9d->ravg.prev_window_cpu[cpu]){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,cpu,WALT3205babe24,*WALT7ba10de4f4,WALT0609dbaf9d->ravg.
prev_window_cpu[cpu]);WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac(
(0x1ecb+1497-0x24a3));}*WALT7ba10de4f4-=WALT0609dbaf9d->ravg.prev_window_cpu[cpu
];}WALT0dd808419c(WALT0609dbaf9d,cpu,rq->window_start,WALT5eebbbffe9);}else{
WALT0504870d67=GROUP_TO_RQ;WALT42b4427a2c=&WALT627d50b29d->curr_runnable_sum;
WALT2e4da9dbb4=&rq->curr_runnable_sum;WALT262b512e81=&WALT627d50b29d->
prev_runnable_sum;WALT086b45bedf=&rq->prev_runnable_sum;WALTf7e69c10fd=&
WALT627d50b29d->nt_curr_runnable_sum;WALT847919a57a=&rq->nt_curr_runnable_sum;
WALT7ba10de4f4=&WALT627d50b29d->nt_prev_runnable_sum;WALT082a99fd0f=&rq->
nt_prev_runnable_sum;if(*WALT42b4427a2c<WALT0609dbaf9d->ravg.curr_window){
printk_deferred(
"\x57\x41\x4c\x54\x2d\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,cpu,WALT3205babe24,*WALT42b4427a2c,WALT0609dbaf9d->ravg.
curr_window);WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac((0x757+834-0xa98));}*
WALT42b4427a2c-=WALT0609dbaf9d->ravg.curr_window;if(*WALT262b512e81<
WALT0609dbaf9d->ravg.prev_window){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,cpu,WALT3205babe24,*WALT262b512e81,WALT0609dbaf9d->ravg.
prev_window);WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac((0x1dcb+1869-0x2517))
;}*WALT262b512e81-=WALT0609dbaf9d->ravg.prev_window;if(WALT5eebbbffe9){if(*
WALTf7e69c10fd<WALT0609dbaf9d->ravg.curr_window){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x63\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,cpu,WALT3205babe24,*WALTf7e69c10fd,WALT0609dbaf9d->ravg.
curr_window);WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac((0xd13+4449-0x1e73));
}*WALTf7e69c10fd-=WALT0609dbaf9d->ravg.curr_window;if(*WALT7ba10de4f4<
WALT0609dbaf9d->ravg.prev_window){printk_deferred(
"\x57\x41\x4c\x54\x2d\x42\x55\x47\x20\x70\x69\x64\x3d\x25\x75\x20\x43\x50\x55\x3d\x25\x64\x20\x65\x76\x65\x6e\x74\x3d\x25\x64\x20\x73\x72\x63\x5f\x6e\x74\x5f\x70\x72\x73\x3d\x25\x6c\x6c\x75\x20\x69\x73\x20\x6c\x65\x73\x73\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x61\x73\x6b\x5f\x63\x6f\x6e\x74\x72\x69\x62\x3d\x25\x6c\x6c\x75"
,WALT0609dbaf9d->pid,cpu,WALT3205babe24,*WALT7ba10de4f4,WALT0609dbaf9d->ravg.
prev_window);WALT1efe882752(WALT0609dbaf9d);WALT609fba09ac((0xc54+3214-0x18e1));
}*WALT7ba10de4f4-=WALT0609dbaf9d->ravg.prev_window;}for_each_possible_cpu(
WALT5d971be8b8){WALT0609dbaf9d->ravg.curr_window_cpu[WALT5d971be8b8]=
(0x278+3922-0x11ca);WALT0609dbaf9d->ravg.prev_window_cpu[WALT5d971be8b8]=
(0xf33+5177-0x236c);}}*WALT2e4da9dbb4+=WALT0609dbaf9d->ravg.curr_window;*
WALT086b45bedf+=WALT0609dbaf9d->ravg.prev_window;if(WALT5eebbbffe9){*
WALT847919a57a+=WALT0609dbaf9d->ravg.curr_window;*WALT082a99fd0f+=WALT0609dbaf9d
->ravg.prev_window;}WALT0609dbaf9d->ravg.curr_window_cpu[cpu]=WALT0609dbaf9d->
ravg.curr_window;WALT0609dbaf9d->ravg.prev_window_cpu[cpu]=WALT0609dbaf9d->ravg.
prev_window;trace_sched_migration_update_sum(WALT0609dbaf9d,WALT0504870d67,rq);}
bool is_rtgb_active(void){struct related_thread_group*grp;grp=WALTaf37716888(
DEFAULT_CGROUP_COLOC_ID);return grp&&grp->skip_min;}u64 get_rtgb_active_time(
void){struct related_thread_group*grp;u64 WALT2c53bb3f34=sched_clock();grp=
WALTaf37716888(DEFAULT_CGROUP_COLOC_ID);if(grp&&grp->skip_min&&grp->start_ts)
return WALT2c53bb3f34-grp->start_ts;return(0x576+225-0x657);}static void 
WALT82ef581fb8(void);static void WALTaea65e35d7(void){WALTfbcbf0e27a();
WALT82ef581fb8();}void walt_irq_work(struct irq_work*irq_work){struct 
sched_cluster*cluster;struct rq*rq;int cpu;u64 WALT0cc0a342b9;bool 
WALTd7ac89c463=false,WALTfc516a8062=false;u64 WALT392940921f=(0x236+1953-0x9d7),
WALT9ef535cb5f=(0x176d+2671-0x21dc);int WALT8025f196c5=(0x1543+3973-0x24c8);u64 
WALTaeec67ca96;unsigned long flags;if(irq_work==&WALT72f8d06752)WALTd7ac89c463=
true;for_each_cpu(cpu,cpu_possible_mask){if(WALT8025f196c5==(0x411+50-0x443))
raw_spin_lock(&cpu_rq(cpu)->lock);else raw_spin_lock_nested(&cpu_rq(cpu)->lock,
WALT8025f196c5);WALT8025f196c5++;}WALT0cc0a342b9=sched_ktime_clock();
WALTaeec67ca96=get_jiffies_64();walt_load_reported_window=atomic64_read(&
WALT8d508f7c3b);for_each_sched_cluster(cluster){u64 aggr_grp_load=
(0x12d7+276-0x13eb);raw_spin_lock(&cluster->load_lock);for_each_cpu(cpu,&cluster
->cpus){rq=cpu_rq(cpu);if(rq->curr){walt_update_task_ravg(rq->curr,rq,
TASK_UPDATE,WALT0cc0a342b9,(0x440+7974-0x2366));WALTa647ab699e(rq);aggr_grp_load
+=rq->grp_time.prev_runnable_sum;}if(WALTd7ac89c463&&rq->notif_pending&&
cpumask_test_cpu(cpu,&asym_cap_sibling_cpus)){WALTfc516a8062=true;rq->
notif_pending=false;}}cluster->aggr_grp_load=aggr_grp_load;WALT392940921f+=
aggr_grp_load;if(is_min_capacity_cluster(cluster))WALT9ef535cb5f=aggr_grp_load;
raw_spin_unlock(&cluster->load_lock);}if(WALT392940921f){if(cpumask_weight(&
asym_cap_sibling_cpus)){u64 WALT2a9650c76f=WALT392940921f-WALT9ef535cb5f;
for_each_cpu(cpu,&asym_cap_sibling_cpus)cpu_cluster(cpu)->aggr_grp_load=
WALT2a9650c76f;}rtgb_active=is_rtgb_active();}else{rtgb_active=false;}if(!
WALTd7ac89c463&&sysctl_sched_user_hint&&time_after(jiffies,WALTfac0edc4a3))
sysctl_sched_user_hint=(0xd7d+995-0x1160);for_each_sched_cluster(cluster){
cpumask_t WALT8fc9e418fd;unsigned int WALT3fc386a32e,WALT5d971be8b8=
(0x894+2825-0x139c);cpumask_and(&WALT8fc9e418fd,&cluster->cpus,cpu_online_mask);
WALT3fc386a32e=cpumask_weight(&WALT8fc9e418fd);for_each_cpu(cpu,&WALT8fc9e418fd)
{int WALT26b84a07e7=SCHED_CPUFREQ_WALT;rq=cpu_rq(cpu);if(WALTd7ac89c463){if(rq->
notif_pending){WALT26b84a07e7|=SCHED_CPUFREQ_INTERCLUSTER_MIG;rq->notif_pending=
false;}}if(WALTfc516a8062&&cpumask_test_cpu(cpu,&asym_cap_sibling_cpus))
WALT26b84a07e7|=SCHED_CPUFREQ_INTERCLUSTER_MIG;if(WALT5d971be8b8==WALT3fc386a32e
)cpufreq_update_util(cpu_rq(cpu),WALT26b84a07e7);else cpufreq_update_util(cpu_rq
(cpu),WALT26b84a07e7|SCHED_CPUFREQ_CONTINUE);WALT5d971be8b8++;if(rq->
high_irqload)rq->high_irqload=(WALTaeec67ca96-rq->irqload_ts<
SCHED_HIGH_IRQ_TIMEOUT);}}if(!WALTd7ac89c463){spin_lock_irqsave(&WALT19d7dae9b5,
flags);if(sched_ravg_window!=WALT95efc1452f){WALTc6e1c5745d=sched_ktime_clock();
printk_deferred(
"\x41\x4c\x45\x52\x54\x3a\x20\x63\x68\x61\x6e\x67\x69\x6e\x67\x20\x77\x69\x6e\x64\x6f\x77\x20\x73\x69\x7a\x65\x20\x66\x72\x6f\x6d\x20\x25\x75\x20\x74\x6f\x20\x25\x75\x20\x61\x74\x20\x25\x6c\x75" "\n"
,sched_ravg_window,WALT95efc1452f,WALTc6e1c5745d);sched_ravg_window=
WALT95efc1452f;WALTaea65e35d7();}spin_unlock_irqrestore(&WALT19d7dae9b5,flags);}
for_each_cpu(cpu,cpu_possible_mask)raw_spin_unlock(&cpu_rq(cpu)->lock);if(!
WALTd7ac89c463)core_ctl_check(this_rq()->window_start);}void 
walt_rotation_checkpoint(int WALTbd4d7a57a3){if(!hmp_capable())return;if(!
sysctl_sched_walt_rotate_big_tasks||sched_boost()!=NO_BOOST){
walt_rotation_enabled=(0x939+6046-0x20d7);return;}walt_rotation_enabled=
WALTbd4d7a57a3>=num_possible_cpus();}void walt_fill_ta_data(struct 
core_ctl_notif_data*data){struct related_thread_group*grp;unsigned long flags;
u64 WALTd8ca2b9a3c=(0x16e9+2562-0x20eb),WALT790680e4aa;struct task_struct*
WALT0609dbaf9d;int WALTba0d35d300,WALT4e46740d20=(0xa34+4699-0x188f);struct 
sched_cluster*cluster;int WALT5d971be8b8=(0x9cb+6940-0x24e7);grp=WALTaf37716888(
DEFAULT_CGROUP_COLOC_ID);raw_spin_lock_irqsave(&grp->lock,flags);if(list_empty(&
grp->tasks)){raw_spin_unlock_irqrestore(&grp->lock,flags);goto WALT81c6b6b7f4;}
WALT790680e4aa=sched_ktime_clock();list_for_each_entry(WALT0609dbaf9d,&grp->
tasks,grp_list){if(WALT0609dbaf9d->ravg.mark_start<WALT790680e4aa-(
sched_ravg_window*WALTa591b9e54c))continue;WALTd8ca2b9a3c+=WALT0609dbaf9d->ravg.
coloc_demand;}raw_spin_unlock_irqrestore(&grp->lock,flags);WALTba0d35d300=
this_rq()->rd->min_cap_orig_cpu;if(WALTba0d35d300!=-(0xa3f+6061-0x21eb))
WALT4e46740d20=arch_scale_cpu_capacity(WALTba0d35d300);data->coloc_load_pct=
div64_u64(WALTd8ca2b9a3c*(0x2100+1645-0x236d)*(0x17f0+2506-0x2156),(u64)
sched_ravg_window*WALT4e46740d20);WALT81c6b6b7f4:for_each_sched_cluster(cluster)
{int WALT61c3a9ab4e=cluster_first_cpu(cluster);if(WALT5d971be8b8==MAX_CLUSTERS)
break;WALT4e46740d20=arch_scale_cpu_capacity(WALT61c3a9ab4e);data->ta_util_pct[
WALT5d971be8b8]=div64_u64(cluster->aggr_grp_load*(0xb7a+5263-0x1c09)*
(0x671+1894-0xd73),(u64)sched_ravg_window*WALT4e46740d20);WALT4e46740d20=
arch_scale_freq_capacity(WALT61c3a9ab4e);data->cur_cap_pct[WALT5d971be8b8]=(
WALT4e46740d20*(0x1985+960-0x1ce1))/(0x1323+4830-0x2201);WALT5d971be8b8++;}}int 
walt_proc_group_thresholds_handler(struct ctl_table*table,int WALT123284dc15,
void __user*WALTfc9cd6af11,size_t*WALTc6af6558dd,loff_t*WALT9057b9d303){int 
WALT083920bcc8;static DEFINE_MUTEX(WALT8a2c4b3219);struct rq*rq=cpu_rq(
cpumask_first(cpu_possible_mask));unsigned long flags;if(unlikely(
num_sched_clusters<=(0x215+7789-0x2082)))return-EPERM;mutex_lock(&WALT8a2c4b3219
);WALT083920bcc8=proc_dointvec_minmax(table,WALT123284dc15,WALTfc9cd6af11,
WALTc6af6558dd,WALT9057b9d303);if(WALT083920bcc8||!WALT123284dc15){mutex_unlock(
&WALT8a2c4b3219);return WALT083920bcc8;}raw_spin_lock_irqsave(&rq->lock,flags);
WALTfbcbf0e27a();raw_spin_unlock_irqrestore(&rq->lock,flags);mutex_unlock(&
WALT8a2c4b3219);return WALT083920bcc8;}static void WALT82ef581fb8(void){
walt_cpu_util_freq_divisor=(sched_ravg_window>>SCHED_CAPACITY_SHIFT)*
(0x8f0+4832-0x1b6c);WALTd07944bdc3=sched_ravg_window>>SCHED_CAPACITY_SHIFT;
sched_init_task_load_windows=div64_u64((u64)WALT8bf7fc10da*(u64)
sched_ravg_window,(0x863+6593-0x21c0));WALTb0bc76dcf5=WALTecf40170d4(
sched_init_task_load_windows);}static void WALT42949ab86e(void){init_irq_work(&
WALT72f8d06752,walt_irq_work);init_irq_work(&WALT5bb9cd73e7,walt_irq_work);
walt_rotate_work_init();WALT82ef581fb8();}void walt_sched_init_rq(struct rq*rq){
int WALT2dc758aa44;if(cpu_of(rq)==(0x4b5+2363-0xdf0))WALT42949ab86e();
cpumask_set_cpu(cpu_of(rq),&rq->freq_domain_cpumask);rq->walt_stats.
cumulative_runnable_avg_scaled=(0x70+1494-0x646);rq->prev_window_size=
sched_ravg_window;rq->window_start=(0xa38+4863-0x1d37);rq->walt_stats.
nr_big_tasks=(0x9a9+6680-0x23c1);rq->walt_flags=(0xb8b+1087-0xfca);rq->
cur_irqload=(0x17e0+1812-0x1ef4);rq->avg_irqload=(0xe1d+3231-0x1abc);rq->
irqload_ts=(0xf11+837-0x1256);rq->high_irqload=false;rq->task_exec_scale=1024;rq
->push_task=NULL;rq->cluster=&WALT2d02e5bf36;rq->curr_runnable_sum=rq->
prev_runnable_sum=(0x1b3+5842-0x1885);rq->nt_curr_runnable_sum=rq->
nt_prev_runnable_sum=(0x1378+2284-0x1c64);memset(&rq->grp_time,
(0x11e5+5209-0x263e),sizeof(struct group_cpu_time));rq->old_busy_time=
(0x1545+3813-0x242a);rq->old_estimated_time=(0xa66+5615-0x2055);rq->
old_busy_time_group=(0xfe5+4746-0x226f);rq->walt_stats.pred_demands_sum_scaled=
(0xb4+1097-0x4fd);rq->ed_task=NULL;rq->curr_table=(0x17a4+3355-0x24bf);rq->
prev_top=(0xb46+5702-0x218c);rq->curr_top=(0x6a9+1566-0xcc7);rq->last_cc_update=
(0x20f+5319-0x16d6);rq->cycles=(0x733+1500-0xd0f);for(WALT2dc758aa44=
(0x9cb+3492-0x176f);WALT2dc758aa44<NUM_TRACKED_WINDOWS;WALT2dc758aa44++){memset(
&rq->load_subs[WALT2dc758aa44],(0x8a0+576-0xae0),sizeof(struct load_subtractions
));rq->top_tasks[WALT2dc758aa44]=kcalloc(NUM_LOAD_INDICES,sizeof(u8),GFP_NOWAIT)
;BUG_ON(!rq->top_tasks[WALT2dc758aa44]);WALT66971bc3d0(rq->top_tasks_bitmap[
WALT2dc758aa44]);}rq->cum_window_demand_scaled=(0x805+1292-0xd11);rq->
notif_pending=false;}int walt_proc_user_hint_handler(struct ctl_table*table,int 
WALT123284dc15,void __user*WALTfc9cd6af11,size_t*WALTc6af6558dd,loff_t*
WALT9057b9d303){int WALT083920bcc8;unsigned int WALTed2a7cf76b;static 
DEFINE_MUTEX(WALT8a2c4b3219);mutex_lock(&WALT8a2c4b3219);WALTfac0edc4a3=jiffies+
HZ;WALTed2a7cf76b=sysctl_sched_user_hint;WALT083920bcc8=proc_dointvec_minmax(
table,WALT123284dc15,WALTfc9cd6af11,WALTc6af6558dd,WALT9057b9d303);if(
WALT083920bcc8||!WALT123284dc15||(WALTed2a7cf76b==sysctl_sched_user_hint))goto 
WALTd0213cc3f9;WALTa4ccf3d6c9(&WALT72f8d06752);WALTd0213cc3f9:mutex_unlock(&
WALT8a2c4b3219);return WALT083920bcc8;}static inline void WALT39b6f75650(void){
int WALTf55fa86af6;unsigned long flags;spin_lock_irqsave(&WALT19d7dae9b5,flags);
WALTf55fa86af6=min(WALTb67de743f5,sysctl_sched_ravg_window_nr_ticks);
WALT95efc1452f=WALTf55fa86af6*(NSEC_PER_SEC/HZ);spin_unlock_irqrestore(&
WALT19d7dae9b5,flags);}int sched_ravg_window_handler(struct ctl_table*table,int 
WALT123284dc15,void __user*WALTfc9cd6af11,size_t*WALTc6af6558dd,loff_t*
WALT9057b9d303){int WALT083920bcc8=-EPERM;static DEFINE_MUTEX(WALT8a2c4b3219);
unsigned int WALT7c755fe34d;mutex_lock(&WALT8a2c4b3219);if(WALT123284dc15&&(HZ!=
(0x540+8492-0x2572)||!sysctl_sched_dynamic_ravg_window_enable))goto 
WALTd0213cc3f9;WALT7c755fe34d=sysctl_sched_ravg_window_nr_ticks;WALT083920bcc8=
proc_douintvec_ravg_window(table,WALT123284dc15,WALTfc9cd6af11,WALTc6af6558dd,
WALT9057b9d303);if(WALT083920bcc8||!WALT123284dc15||(WALT7c755fe34d==
sysctl_sched_ravg_window_nr_ticks))goto WALTd0213cc3f9;WALT39b6f75650();
WALTd0213cc3f9:mutex_unlock(&WALT8a2c4b3219);return WALT083920bcc8;}void 
sched_set_refresh_rate(enum fps fps){if(HZ==(0x1014+842-0x1264)&&
sysctl_sched_dynamic_ravg_window_enable){if(fps>FPS90)WALTb67de743f5=
(0xad+4413-0x11e8);else if(fps==FPS90)WALTb67de743f5=(0x1a96+704-0x1d53);else 
WALTb67de743f5=(0x540+84-0x58f);WALT39b6f75650();}}EXPORT_SYMBOL(
sched_set_refresh_rate);
