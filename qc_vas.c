// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#include <linux/irq.h>
#include <linux/delay.h>
#include <trace/events/sched.h>
#include "walt.h"
#ifdef CONFIG_SCHED_WALT
unsigned int sysctl_sched_min_task_util_for_boost=(0x1089+5547-0x2601);unsigned 
int sysctl_sched_min_task_util_for_colocation=(0x1294+4490-0x23fb);unsigned int 
sched_task_filter_util=(0x127a+959-0x1616);
#ifdef CONFIG_CFS_BANDWIDTH
void walt_init_cfs_rq_stats(struct z321ecb98bb*z321ecb98bb){z321ecb98bb->
walt_stats.nr_big_tasks=(0x1dc0+2277-0x26a5);z321ecb98bb->walt_stats.
cumulative_runnable_avg_scaled=(0x4f6+2133-0xd4b);z321ecb98bb->walt_stats.
pred_demands_sum_scaled=(0x17a4+2093-0x1fd1);}void walt_inc_cfs_rq_stats(struct 
z321ecb98bb*z321ecb98bb,struct task_struct*z0609dbaf9d){inc_nr_big_task(&
z321ecb98bb->walt_stats,z0609dbaf9d);fixup_cumulative_runnable_avg(&z321ecb98bb
->walt_stats,z0609dbaf9d->ravg.demand_scaled,z0609dbaf9d->ravg.
pred_demand_scaled);}void walt_dec_cfs_rq_stats(struct z321ecb98bb*z321ecb98bb,
struct task_struct*z0609dbaf9d){dec_nr_big_task(&z321ecb98bb->walt_stats,
z0609dbaf9d);fixup_cumulative_runnable_avg(&z321ecb98bb->walt_stats,-(s64)
z0609dbaf9d->ravg.demand_scaled,-(s64)z0609dbaf9d->ravg.pred_demand_scaled);}
void walt_inc_throttled_cfs_rq_stats(struct zb80fc696d2*zf0f82ef4d0,struct 
z321ecb98bb*z38fb231785){struct rq*rq=zd8ee186a7b(z38fb231785);zf0f82ef4d0->
nr_big_tasks+=z38fb231785->walt_stats.nr_big_tasks;fixup_cumulative_runnable_avg
(zf0f82ef4d0,z38fb231785->walt_stats.cumulative_runnable_avg_scaled,z38fb231785
->walt_stats.pred_demands_sum_scaled);if(zf0f82ef4d0==&rq->walt_stats)
walt_fixup_cum_window_demand(rq,z38fb231785->walt_stats.
cumulative_runnable_avg_scaled);}void walt_dec_throttled_cfs_rq_stats(struct 
zb80fc696d2*zf0f82ef4d0,struct z321ecb98bb*z38fb231785){struct rq*rq=zd8ee186a7b
(z38fb231785);zf0f82ef4d0->nr_big_tasks-=z38fb231785->walt_stats.nr_big_tasks;
fixup_cumulative_runnable_avg(zf0f82ef4d0,-z38fb231785->walt_stats.
cumulative_runnable_avg_scaled,-z38fb231785->walt_stats.pred_demands_sum_scaled)
;if(zf0f82ef4d0==&rq->walt_stats)walt_fixup_cum_window_demand(rq,-z38fb231785->
walt_stats.cumulative_runnable_avg_scaled);}void walt_fixup_sched_stats_fair(
struct rq*rq,struct task_struct*z0609dbaf9d,u16 z8143bfdfea,u16 z77a2404d60){
struct z321ecb98bb*z321ecb98bb;struct z4eb2b276fc*se=&z0609dbaf9d->se;s64 
zad18716537=(s64)z8143bfdfea-z0609dbaf9d->ravg.demand_scaled;s64 z5ae7e7adb9=(
s64)z77a2404d60-z0609dbaf9d->ravg.pred_demand_scaled;zd6d9098f73(se){z321ecb98bb
=za7f33affdd(se);fixup_cumulative_runnable_avg(&z321ecb98bb->walt_stats,
zad18716537,z5ae7e7adb9);if(zbdb087de18(z321ecb98bb))break;}if(!se){
fixup_cumulative_runnable_avg(&rq->walt_stats,zad18716537,z5ae7e7adb9);
walt_fixup_cum_window_demand(rq,zad18716537);}}void walt_fixup_nr_big_tasks(
struct rq*rq,struct task_struct*z0609dbaf9d,int z17abc14e87,bool zef3ecb031d){
struct z321ecb98bb*z321ecb98bb;struct z4eb2b276fc*se=&z0609dbaf9d->se;
zd6d9098f73(se){z321ecb98bb=za7f33affdd(se);z321ecb98bb->walt_stats.nr_big_tasks
+=zef3ecb031d?z17abc14e87:-z17abc14e87;BUG_ON(z321ecb98bb->walt_stats.
nr_big_tasks<(0x57+1091-0x49a));if(zbdb087de18(z321ecb98bb))break;}if(!se)
walt_adjust_nr_big_tasks(rq,z17abc14e87,zef3ecb031d);}int z2e361dba6e(struct 
task_struct*z0609dbaf9d){struct z4eb2b276fc*se=&z0609dbaf9d->se;struct 
z321ecb98bb*z321ecb98bb;if(!z99c9b6d23b())return(0x4a+4035-0x100d);zd6d9098f73(
se){z321ecb98bb=za7f33affdd(se);if(!z321ecb98bb->zfe4952bade)continue;if(
z321ecb98bb->z54899c08c2<=(0xd09+2158-0x1577))return(0xb6d+5152-0x1f8c);}return
(0xd99+6253-0x2606);}
#else 
void walt_fixup_sched_stats_fair(struct rq*rq,struct task_struct*z0609dbaf9d,u16
 z8143bfdfea,u16 z77a2404d60){fixup_walt_sched_stats_common(rq,z0609dbaf9d,
z8143bfdfea,z77a2404d60);}void walt_fixup_nr_big_tasks(struct rq*rq,struct 
task_struct*z0609dbaf9d,int z17abc14e87,bool zef3ecb031d){
walt_adjust_nr_big_tasks(rq,z17abc14e87,zef3ecb031d);}int z2e361dba6e(struct 
task_struct*z0609dbaf9d){return false;}
#endif 
int z1ab55d3fe3(struct rq*rq,struct task_struct*z0609dbaf9d,int z525181d1b1){
unsigned long flags;int z094475d445=(0x1891+2771-0x2364);raw_spin_lock_irqsave(&
rq->lock,flags);if(!rq->active_balance){rq->active_balance=(0x65d+4289-0x171d);
rq->push_cpu=z525181d1b1;get_task_struct(z0609dbaf9d);rq->push_task=z0609dbaf9d;
z094475d445=(0x267+6403-0x1b69);}raw_spin_unlock_irqrestore(&rq->lock,flags);
return z094475d445;}struct z9e9109c2b0{struct work_struct z61a2ee39fd;struct 
task_struct*z6216002a44;struct task_struct*zdd524a14fe;int z3eb4d59849;int 
z69f29b0e89;};DEFINE_PER_CPU(struct z9e9109c2b0,z5b856a0e80);void zfd6ca4cbe7(
struct work_struct*z9932a7275f){struct z9e9109c2b0*z81107b3e03=container_of(
z9932a7275f,struct z9e9109c2b0,z61a2ee39fd);migrate_swap(z81107b3e03->
z6216002a44,z81107b3e03->zdd524a14fe,z81107b3e03->z69f29b0e89,z81107b3e03->
z3eb4d59849);put_task_struct(z81107b3e03->z6216002a44);put_task_struct(
z81107b3e03->zdd524a14fe);clear_reserved(z81107b3e03->z3eb4d59849);
clear_reserved(z81107b3e03->z69f29b0e89);}void walt_rotate_work_init(void){int 
z5d971be8b8;for_each_possible_cpu(z5d971be8b8){struct z9e9109c2b0*z81107b3e03=&
per_cpu(z5b856a0e80,z5d971be8b8);INIT_WORK(&z81107b3e03->z61a2ee39fd,zfd6ca4cbe7
);}}
#define z04d8c7d834      16000000
void z02def4fea3(struct rq*zd01f3eedf0){u64 z0cc0a342b9,z70b23f67e1,zd600851d0e=
(0x4db+518-0x6e1),z32bc620250,z603690f2ae=(0x4fa+3192-0x1172);int z915c187717=
nr_cpu_ids,z69f29b0e89=nr_cpu_ids;int z5d971be8b8,z3eb4d59849=cpu_of(zd01f3eedf0
);struct rq*z38ee64137f;struct z9e9109c2b0*z81107b3e03=NULL;if(!
walt_rotation_enabled)return;if(!is_min_capacity_cpu(z3eb4d59849))return;
z0cc0a342b9=sched_ktime_clock();for_each_possible_cpu(z5d971be8b8){struct rq*rq=
cpu_rq(z5d971be8b8);if(!is_min_capacity_cpu(z5d971be8b8))break;if(is_reserved(
z5d971be8b8))continue;if(!rq->misfit_task_load||rq->curr->sched_class!=&
fair_sched_class)continue;z70b23f67e1=z0cc0a342b9-rq->curr->last_enqueued_ts;if(
z70b23f67e1>zd600851d0e){zd600851d0e=z70b23f67e1;z915c187717=z5d971be8b8;}}if(
z915c187717!=z3eb4d59849)return;for_each_possible_cpu(z5d971be8b8){struct rq*rq=
cpu_rq(z5d971be8b8);if(is_min_capacity_cpu(z5d971be8b8))continue;if(is_reserved(
z5d971be8b8))continue;if(rq->curr->sched_class!=&fair_sched_class)continue;if(rq
->nr_running>(0xc76+4209-0x1ce6))continue;z32bc620250=z0cc0a342b9-rq->curr->
last_enqueued_ts;if(z32bc620250<z04d8c7d834)continue;if(z32bc620250>z603690f2ae)
{z603690f2ae=z32bc620250;z69f29b0e89=z5d971be8b8;}}if(z69f29b0e89==nr_cpu_ids)
return;z38ee64137f=cpu_rq(z69f29b0e89);double_rq_lock(zd01f3eedf0,z38ee64137f);
if(z38ee64137f->curr->sched_class==&fair_sched_class){get_task_struct(
zd01f3eedf0->curr);get_task_struct(z38ee64137f->curr);mark_reserved(z3eb4d59849)
;mark_reserved(z69f29b0e89);z81107b3e03=&per_cpu(z5b856a0e80,z3eb4d59849);
z81107b3e03->z6216002a44=zd01f3eedf0->curr;z81107b3e03->zdd524a14fe=z38ee64137f
->curr;z81107b3e03->z3eb4d59849=z3eb4d59849;z81107b3e03->z69f29b0e89=z69f29b0e89
;}double_rq_unlock(zd01f3eedf0,z38ee64137f);if(z81107b3e03)queue_work_on(
z3eb4d59849,system_highpri_wq,&z81107b3e03->z61a2ee39fd);}DEFINE_RAW_SPINLOCK(
zead2f8c599);void check_for_migration(struct rq*rq,struct task_struct*
z0609dbaf9d){int active_balance;int z525181d1b1=-(0x1ccb+833-0x200b);int 
z7965e1fb10=task_cpu(z0609dbaf9d);int z083920bcc8;if(rq->misfit_task_load){if(rq
->curr->state!=TASK_RUNNING||rq->curr->nr_cpus_allowed==(0xeef+305-0x101f))
return;if(z2e361dba6e(z0609dbaf9d))return;raw_spin_lock(&zead2f8c599);
rcu_read_lock();z525181d1b1=find_energy_efficient_cpu(z0609dbaf9d,z7965e1fb10,
(0x544+3649-0x1385),(0x6f5+2723-0x1197));rcu_read_unlock();if((z525181d1b1!=-
(0xa95+3359-0x17b3))&&(z525181d1b1!=z7965e1fb10)&&(capacity_orig_of(z525181d1b1)
>capacity_orig_of(z7965e1fb10))){active_balance=z1ab55d3fe3(rq,z0609dbaf9d,
z525181d1b1);if(active_balance){mark_reserved(z525181d1b1);raw_spin_unlock(&
zead2f8c599);z083920bcc8=stop_one_cpu_nowait(z7965e1fb10,
active_load_balance_cpu_stop,rq,&rq->active_balance_work);if(!z083920bcc8)
clear_reserved(z525181d1b1);else wake_up_if_idle(z525181d1b1);return;}}else{
z02def4fea3(rq);}raw_spin_unlock(&zead2f8c599);}}int sched_init_task_load_show(
struct seq_file*z0a6cda24c8,void*ze57683840e){struct inode*inode=z0a6cda24c8->
private;struct task_struct*z0609dbaf9d;z0609dbaf9d=get_proc_task(inode);if(!
z0609dbaf9d)return-ESRCH;seq_printf(z0a6cda24c8,"\x25\x64" "\n",
sched_get_init_task_load(z0609dbaf9d));put_task_struct(z0609dbaf9d);return
(0xbaa+974-0xf78);}ssize_t sched_init_task_load_write(struct file*file,const 
char __user*z33c5f8b4bc,size_t z33ea1b60d7,loff_t*z042458434d){struct inode*
inode=file_inode(file);struct task_struct*z0609dbaf9d;char zfc9cd6af11[
PROC_NUMBUF];int zdbf899ce1d,z2839a901be;memset(zfc9cd6af11,(0x1038+3299-0x1d1b)
,sizeof(zfc9cd6af11));if(z33ea1b60d7>sizeof(zfc9cd6af11)-(0x5d+1339-0x597))
z33ea1b60d7=sizeof(zfc9cd6af11)-(0x677+1692-0xd12);if(copy_from_user(zfc9cd6af11
,z33c5f8b4bc,z33ea1b60d7)){z2839a901be=-EFAULT;goto ze1f307999b;}z2839a901be=
kstrtoint(strstrip(zfc9cd6af11),(0x414+1206-0x8ca),&zdbf899ce1d);if(z2839a901be)
goto ze1f307999b;z0609dbaf9d=get_proc_task(inode);if(!z0609dbaf9d)return-ESRCH;
z2839a901be=sched_set_init_task_load(z0609dbaf9d,zdbf899ce1d);put_task_struct(
z0609dbaf9d);ze1f307999b:return z2839a901be<(0xae4+6430-0x2402)?z2839a901be:
z33ea1b60d7;}int sched_init_task_load_open(struct inode*inode,struct file*
z65b461521a){return single_open(z65b461521a,sched_init_task_load_show,inode);}
int sched_group_id_show(struct seq_file*z0a6cda24c8,void*ze57683840e){struct 
inode*inode=z0a6cda24c8->private;struct task_struct*z0609dbaf9d;z0609dbaf9d=
get_proc_task(inode);if(!z0609dbaf9d)return-ESRCH;seq_printf(z0a6cda24c8,
"\x25\x64" "\n",sched_get_group_id(z0609dbaf9d));put_task_struct(z0609dbaf9d);
return(0x192b+2097-0x215c);}ssize_t sched_group_id_write(struct file*file,const 
char __user*z33c5f8b4bc,size_t z33ea1b60d7,loff_t*z042458434d){struct inode*
inode=file_inode(file);struct task_struct*z0609dbaf9d;char zfc9cd6af11[
PROC_NUMBUF];int ze3d424fbb1,z2839a901be;memset(zfc9cd6af11,(0x550+7515-0x22ab),
sizeof(zfc9cd6af11));if(z33ea1b60d7>sizeof(zfc9cd6af11)-(0x1e7b+378-0x1ff4))
z33ea1b60d7=sizeof(zfc9cd6af11)-(0x12b5+1343-0x17f3);if(copy_from_user(
zfc9cd6af11,z33c5f8b4bc,z33ea1b60d7)){z2839a901be=-EFAULT;goto ze1f307999b;}
z2839a901be=kstrtoint(strstrip(zfc9cd6af11),(0x3d7+8649-0x25a0),&ze3d424fbb1);if
(z2839a901be)goto ze1f307999b;z0609dbaf9d=get_proc_task(inode);if(!z0609dbaf9d)
return-ESRCH;z2839a901be=sched_set_group_id(z0609dbaf9d,ze3d424fbb1);
put_task_struct(z0609dbaf9d);ze1f307999b:return z2839a901be<(0x51d+2569-0xf26)?
z2839a901be:z33ea1b60d7;}int sched_group_id_open(struct inode*inode,struct file*
z65b461521a){return single_open(z65b461521a,sched_group_id_show,inode);}void 
sched_exit(struct task_struct*z0609dbaf9d){struct rq_flags z8d267b09c4;struct rq
*rq;u64 z790680e4aa;sched_set_group_id(z0609dbaf9d,(0x73+9290-0x24bd));rq=
task_rq_lock(z0609dbaf9d,&z8d267b09c4);z790680e4aa=sched_ktime_clock();
walt_update_task_ravg(rq->curr,rq,TASK_UPDATE,z790680e4aa,(0x77f+3583-0x157e));
dequeue_task_core(rq,z0609dbaf9d,(0x8d2+4817-0x1ba3));reset_task_stats(
z0609dbaf9d);z0609dbaf9d->ravg.mark_start=z790680e4aa;z0609dbaf9d->ravg.
sum_history[(0xfad+210-0x107f)]=EXITING_TASK_MARKER;enqueue_task_core(rq,
z0609dbaf9d,(0x37f+3841-0x1280));clear_ed_task(z0609dbaf9d,rq);task_rq_unlock(rq
,z0609dbaf9d,&z8d267b09c4);free_task_load_ptrs(z0609dbaf9d);}
#ifdef CONFIG_SMP
int sched_wake_up_idle_show(struct seq_file*z0a6cda24c8,void*ze57683840e){struct
 inode*inode=z0a6cda24c8->private;struct task_struct*z0609dbaf9d;z0609dbaf9d=
get_proc_task(inode);if(!z0609dbaf9d)return-ESRCH;seq_printf(z0a6cda24c8,
"\x25\x64" "\n",sched_get_wake_up_idle(z0609dbaf9d));put_task_struct(z0609dbaf9d
);return(0x9f1+6097-0x21c2);}ssize_t sched_wake_up_idle_write(struct file*file,
const char __user*z33c5f8b4bc,size_t z33ea1b60d7,loff_t*z042458434d){struct 
inode*inode=file_inode(file);struct task_struct*z0609dbaf9d;char zfc9cd6af11[
PROC_NUMBUF];int ze46fad7f31,z2839a901be;memset(zfc9cd6af11,(0xe1b+5658-0x2435),
sizeof(zfc9cd6af11));if(z33ea1b60d7>sizeof(zfc9cd6af11)-(0x6a9+6733-0x20f5))
z33ea1b60d7=sizeof(zfc9cd6af11)-(0x9b0+3790-0x187d);if(copy_from_user(
zfc9cd6af11,z33c5f8b4bc,z33ea1b60d7)){z2839a901be=-EFAULT;goto ze1f307999b;}
z2839a901be=kstrtoint(strstrip(zfc9cd6af11),(0x8a0+6993-0x23f1),&ze46fad7f31);if
(z2839a901be)goto ze1f307999b;z0609dbaf9d=get_proc_task(inode);if(!z0609dbaf9d)
return-ESRCH;z2839a901be=sched_set_wake_up_idle(z0609dbaf9d,ze46fad7f31);
put_task_struct(z0609dbaf9d);ze1f307999b:return z2839a901be<(0x971+572-0xbad)?
z2839a901be:z33ea1b60d7;}int sched_wake_up_idle_open(struct inode*inode,struct 
file*z65b461521a){return single_open(z65b461521a,sched_wake_up_idle_show,inode);
}int group_balance_cpu_not_isolated(struct sched_group*z8a34fc2d7e){cpumask_t 
cpus;cpumask_and(&cpus,sched_group_span(z8a34fc2d7e),group_balance_mask(
z8a34fc2d7e));cpumask_andnot(&cpus,&cpus,cpu_isolated_mask);return cpumask_first
(&cpus);}
#endif 
#ifdef CONFIG_PROC_SYSCTL
static void zca71bfe44d(bool z5829e80183){int z5d971be8b8=(0x3bd+8121-0x2376),
cpu;struct sched_cluster*cluster;int z4141a1c7ab=num_sched_clusters-
(0x1d1b+1942-0x24b0);if(z4141a1c7ab>(0x590+6671-0x1f9e)){for_each_sched_cluster(
cluster){for_each_cpu(cpu,&cluster->cpus){if(z5829e80183)
sched_capacity_margin_up[cpu]=sysctl_sched_capacity_margin_up[z5d971be8b8];else 
sched_capacity_margin_down[cpu]=sysctl_sched_capacity_margin_down[z5d971be8b8];}
if(++z5d971be8b8>=z4141a1c7ab)break;}}else{for_each_possible_cpu(cpu){if(
z5829e80183)sched_capacity_margin_up[cpu]=sysctl_sched_capacity_margin_up[
(0x500+3701-0x1375)];else sched_capacity_margin_down[cpu]=
sysctl_sched_capacity_margin_down[(0x2af+7800-0x2127)];}}}int 
sched_updown_migrate_handler(struct ctl_table*table,int z123284dc15,void __user*
zfc9cd6af11,size_t*zc6af6558dd,loff_t*z9057b9d303){int z083920bcc8,z5d971be8b8;
unsigned int*data=(unsigned int*)table->data;unsigned int*z2582fdae21;static 
DEFINE_MUTEX(z8a2c4b3219);int z4141a1c7ab=num_sched_clusters?num_sched_clusters-
(0xa36+732-0xd11):(0x79c+2769-0x126d);if(z4141a1c7ab<=(0x142+2385-0xa93))return-
EINVAL;mutex_lock(&z8a2c4b3219);if(table->maxlen!=(sizeof(unsigned int)*
z4141a1c7ab))table->maxlen=sizeof(unsigned int)*z4141a1c7ab;if(!z123284dc15){
z083920bcc8=proc_douintvec_capacity(table,z123284dc15,zfc9cd6af11,zc6af6558dd,
z9057b9d303);goto za4b70d54fd;}z2582fdae21=kzalloc(table->maxlen,GFP_KERNEL);if(
!z2582fdae21){z083920bcc8=-ENOMEM;goto za4b70d54fd;}memcpy(z2582fdae21,data,
table->maxlen);z083920bcc8=proc_douintvec_capacity(table,z123284dc15,zfc9cd6af11
,zc6af6558dd,z9057b9d303);if(z083920bcc8){memcpy(data,z2582fdae21,table->maxlen)
;goto z44a8d790b1;}for(z5d971be8b8=(0x700+6116-0x1ee4);z5d971be8b8<z4141a1c7ab;
z5d971be8b8++){if(sysctl_sched_capacity_margin_up[z5d971be8b8]>
sysctl_sched_capacity_margin_down[z5d971be8b8]){memcpy(data,z2582fdae21,table->
maxlen);z083920bcc8=-EINVAL;goto z44a8d790b1;}}zca71bfe44d(data==&
sysctl_sched_capacity_margin_up[(0x4c1+2586-0xedb)]);z44a8d790b1:kfree(
z2582fdae21);za4b70d54fd:mutex_unlock(&z8a2c4b3219);return z083920bcc8;}
#endif 
int sched_isolate_count(const cpumask_t*zdf9caaa1ec,bool z8a374ecb25){cpumask_t 
z005cc38736=CPU_MASK_NONE;if(z8a374ecb25){cpumask_complement(&z005cc38736,
cpu_online_mask);cpumask_or(&z005cc38736,&z005cc38736,cpu_isolated_mask);
cpumask_and(&z005cc38736,&z005cc38736,zdf9caaa1ec);}else{cpumask_and(&
z005cc38736,zdf9caaa1ec,cpu_isolated_mask);}return cpumask_weight(&z005cc38736);
}
#ifdef CONFIG_HOTPLUG_CPU
static int z517bfbcfb2(void*data){unsigned int cpu=smp_processor_id();struct rq*
rq=cpu_rq(cpu);struct rq_flags z8d267b09c4;local_irq_disable();
irq_migrate_all_off_this_cpu();sched_ttwu_pending();rq_lock(rq,&z8d267b09c4);if(
rq->rd){BUG_ON(!cpumask_test_cpu(cpu,rq->rd->span));set_rq_offline(rq);}
migrate_tasks(rq,&z8d267b09c4,false);if(rq->rd)set_rq_online(rq);rq_unlock(rq,&
z8d267b09c4);clear_walt_request(cpu);local_irq_enable();return
(0x1e3+5403-0x16fe);}static int z8d3857ab85(void*data){watchdog_enable(
smp_processor_id());return(0x810+5301-0x1cc5);}static void z3b8baee159(int cpu){
struct sched_domain*ze761d6c70c;mutex_lock(&sched_domains_mutex);rcu_read_lock()
;for_each_domain(cpu,ze761d6c70c){int zd7a8f45160=group_balance_cpu(ze761d6c70c
->groups);init_sched_groups_capacity(cpu,ze761d6c70c);if(cpu!=zd7a8f45160)
init_sched_groups_capacity(zd7a8f45160,ze761d6c70c);}rcu_read_unlock();
mutex_unlock(&sched_domains_mutex);}static unsigned int z10baa2902e[NR_CPUS];int
 sched_isolate_cpu(int cpu){struct rq*rq;cpumask_t z8d8e5eee2e;int z97642c3096=
(0xaf2+6332-0x23ae);u64 z969c3c9b78=(0xcb8+1075-0x10eb);if(
trace_sched_isolate_enabled())z969c3c9b78=sched_clock();cpu_maps_update_begin();
cpumask_andnot(&z8d8e5eee2e,cpu_online_mask,cpu_isolated_mask);if(cpu<
(0xcd1+4366-0x1ddf)||cpu>=nr_cpu_ids||!cpu_possible(cpu)||!cpu_online(cpu)){
z97642c3096=-EINVAL;goto ze1f307999b;}rq=cpu_rq(cpu);if(++z10baa2902e[cpu]>
(0xbcf+6944-0x26ee))goto ze1f307999b;if(cpumask_weight(&z8d8e5eee2e)==
(0x8a6+3426-0x1607)){--z10baa2902e[cpu];z97642c3096=-EINVAL;goto ze1f307999b;}if
(!watchdog_configured(cpu)){msleep((0x1077+2211-0x1906));if(!watchdog_configured
(cpu)){--z10baa2902e[cpu];z97642c3096=-EBUSY;goto ze1f307999b;}}set_cpu_isolated
(cpu,true);cpumask_clear_cpu(cpu,&z8d8e5eee2e);smp_call_function_any(&
z8d8e5eee2e,hrtimer_quiesce_cpu,&cpu,(0xd38+2441-0x16c0));smp_call_function_any(
&z8d8e5eee2e,timer_quiesce_cpu,&cpu,(0x1397+4187-0x23f1));watchdog_disable(cpu);
irq_lock_sparse();stop_cpus(cpumask_of(cpu),z517bfbcfb2,(0x4ec+6171-0x1d07));
irq_unlock_sparse();calc_load_migrate(rq);update_max_interval();z3b8baee159(cpu)
;ze1f307999b:cpu_maps_update_done();trace_sched_isolate(cpu,cpumask_bits(
cpu_isolated_mask)[(0x987+67-0x9ca)],z969c3c9b78,(0xf25+5755-0x259f));return 
z97642c3096;}int sched_unisolate_cpu_unlocked(int cpu){int z97642c3096=
(0x1a87+821-0x1dbc);u64 z969c3c9b78=(0xc8b+3655-0x1ad2);if(cpu<
(0xeff+654-0x118d)||cpu>=nr_cpu_ids||!cpu_possible(cpu)){z97642c3096=-EINVAL;
goto ze1f307999b;}if(trace_sched_isolate_enabled())z969c3c9b78=sched_clock();if(
!z10baa2902e[cpu]){z97642c3096=-EINVAL;goto ze1f307999b;}if(--z10baa2902e[cpu])
goto ze1f307999b;set_cpu_isolated(cpu,false);update_max_interval();z3b8baee159(
cpu);if(cpu_online(cpu)){stop_cpus(cpumask_of(cpu),z8d3857ab85,
(0x771+3451-0x14ec));if(!atomic_fetch_or(NOHZ_KICK_MASK,nohz_flags(cpu)))
smp_send_reschedule(cpu);}ze1f307999b:trace_sched_isolate(cpu,cpumask_bits(
cpu_isolated_mask)[(0x9bc+82-0xa0e)],z969c3c9b78,(0x34a+8051-0x22bd));return 
z97642c3096;}int sched_unisolate_cpu(int cpu){int z97642c3096;
cpu_maps_update_begin();z97642c3096=sched_unisolate_cpu_unlocked(cpu);
cpu_maps_update_done();return z97642c3096;}void detach_one_task_core(struct 
task_struct*z0609dbaf9d,struct rq*rq,struct list_head*tasks){lockdep_assert_held
(&rq->lock);z0609dbaf9d->on_rq=TASK_ON_RQ_MIGRATING;deactivate_task(rq,
z0609dbaf9d,(0x3fa+2444-0xd86));list_add(&z0609dbaf9d->se.group_node,tasks);}
void attach_tasks_core(struct list_head*tasks,struct rq*rq){struct task_struct*
z0609dbaf9d;lockdep_assert_held(&rq->lock);while(!list_empty(tasks)){z0609dbaf9d
=list_first_entry(tasks,struct task_struct,se.group_node);list_del_init(&
z0609dbaf9d->se.group_node);BUG_ON(task_rq(z0609dbaf9d)!=rq);activate_task(rq,
z0609dbaf9d,(0xd0a+6596-0x26ce));z0609dbaf9d->on_rq=TASK_ON_RQ_QUEUED;}}
#endif 
#endif 

