// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#include <linux/irq.h>
#include <linux/delay.h>
#include <trace/events/sched.h>
#include "walt.h"
#ifdef CONFIG_SCHED_WALT
unsigned int sysctl_sched_min_task_util_for_boost=(0xbbd+4403-0x1cbd);unsigned 
int sysctl_sched_min_task_util_for_colocation=(0xd40+6580-0x26d1);unsigned int 
sched_task_filter_util=(0x1571+2949-0x20d3);int WALT1ab55d3fe3(struct rq*rq,
struct task_struct*WALT0609dbaf9d,int WALT525181d1b1){unsigned long flags;int 
WALT094475d445=(0x347+2449-0xcd8);raw_spin_lock_irqsave(&rq->lock,flags);if(!rq
->active_balance){rq->active_balance=(0x1fff+1177-0x2497);rq->push_cpu=
WALT525181d1b1;get_task_struct(WALT0609dbaf9d);rq->push_task=WALT0609dbaf9d;
WALT094475d445=(0x8b8+5627-0x1eb2);}raw_spin_unlock_irqrestore(&rq->lock,flags);
return WALT094475d445;}struct WALT9e9109c2b0{struct work_struct WALT61a2ee39fd;
struct task_struct*WALT6216002a44;struct task_struct*WALTdd524a14fe;int 
WALT3eb4d59849;int WALT69f29b0e89;};DEFINE_PER_CPU(struct WALT9e9109c2b0,
WALT5b856a0e80);void WALTfd6ca4cbe7(struct work_struct*WALT9932a7275f){struct 
WALT9e9109c2b0*WALT81107b3e03=container_of(WALT9932a7275f,struct WALT9e9109c2b0,
WALT61a2ee39fd);migrate_swap(WALT81107b3e03->WALT6216002a44,WALT81107b3e03->
WALTdd524a14fe,WALT81107b3e03->WALT69f29b0e89,WALT81107b3e03->WALT3eb4d59849);
put_task_struct(WALT81107b3e03->WALT6216002a44);put_task_struct(WALT81107b3e03->
WALTdd524a14fe);clear_reserved(WALT81107b3e03->WALT3eb4d59849);clear_reserved(
WALT81107b3e03->WALT69f29b0e89);}void walt_rotate_work_init(void){int 
WALT5d971be8b8;for_each_possible_cpu(WALT5d971be8b8){struct WALT9e9109c2b0*
WALT81107b3e03=&per_cpu(WALT5b856a0e80,WALT5d971be8b8);INIT_WORK(&WALT81107b3e03
->WALT61a2ee39fd,WALTfd6ca4cbe7);}}
#define WALT04d8c7d834      16000000
void WALT02def4fea3(struct rq*WALTd01f3eedf0){u64 WALT0cc0a342b9,WALT70b23f67e1,
WALTd600851d0e=(0x943+1519-0xf32),WALT32bc620250,WALT603690f2ae=
(0x7bc+3740-0x1658);int WALT915c187717=nr_cpu_ids,WALT69f29b0e89=nr_cpu_ids;int 
WALT5d971be8b8,WALT3eb4d59849=cpu_of(WALTd01f3eedf0);struct rq*WALT38ee64137f;
struct WALT9e9109c2b0*WALT81107b3e03=NULL;if(!walt_rotation_enabled)return;if(!
is_min_capacity_cpu(WALT3eb4d59849))return;WALT0cc0a342b9=sched_ktime_clock();
for_each_possible_cpu(WALT5d971be8b8){struct rq*rq=cpu_rq(WALT5d971be8b8);if(!
is_min_capacity_cpu(WALT5d971be8b8))break;if(is_reserved(WALT5d971be8b8))
continue;if(!rq->misfit_task_load||rq->curr->sched_class!=&fair_sched_class)
continue;WALT70b23f67e1=WALT0cc0a342b9-rq->curr->last_enqueued_ts;if(
WALT70b23f67e1>WALTd600851d0e){WALTd600851d0e=WALT70b23f67e1;WALT915c187717=
WALT5d971be8b8;}}if(WALT915c187717!=WALT3eb4d59849)return;for_each_possible_cpu(
WALT5d971be8b8){struct rq*rq=cpu_rq(WALT5d971be8b8);if(is_min_capacity_cpu(
WALT5d971be8b8))continue;if(is_reserved(WALT5d971be8b8))continue;if(rq->curr->
sched_class!=&fair_sched_class)continue;if(rq->nr_running>(0x727+1912-0xe9e))
continue;WALT32bc620250=WALT0cc0a342b9-rq->curr->last_enqueued_ts;if(
WALT32bc620250<WALT04d8c7d834)continue;if(WALT32bc620250>WALT603690f2ae){
WALT603690f2ae=WALT32bc620250;WALT69f29b0e89=WALT5d971be8b8;}}if(WALT69f29b0e89
==nr_cpu_ids)return;WALT38ee64137f=cpu_rq(WALT69f29b0e89);double_rq_lock(
WALTd01f3eedf0,WALT38ee64137f);if(WALT38ee64137f->curr->sched_class==&
fair_sched_class){get_task_struct(WALTd01f3eedf0->curr);get_task_struct(
WALT38ee64137f->curr);mark_reserved(WALT3eb4d59849);mark_reserved(WALT69f29b0e89
);WALT81107b3e03=&per_cpu(WALT5b856a0e80,WALT3eb4d59849);WALT81107b3e03->
WALT6216002a44=WALTd01f3eedf0->curr;WALT81107b3e03->WALTdd524a14fe=
WALT38ee64137f->curr;WALT81107b3e03->WALT3eb4d59849=WALT3eb4d59849;
WALT81107b3e03->WALT69f29b0e89=WALT69f29b0e89;}double_rq_unlock(WALTd01f3eedf0,
WALT38ee64137f);if(WALT81107b3e03)queue_work_on(WALT3eb4d59849,system_highpri_wq
,&WALT81107b3e03->WALT61a2ee39fd);}DEFINE_RAW_SPINLOCK(WALTead2f8c599);void 
check_for_migration(struct rq*rq,struct task_struct*WALT0609dbaf9d){int 
active_balance;int WALT525181d1b1=-(0xe0f+5242-0x2288);int WALT7965e1fb10=
task_cpu(WALT0609dbaf9d);int WALT083920bcc8;if(rq->misfit_task_load){if(rq->curr
->state!=TASK_RUNNING||rq->curr->nr_cpus_allowed==(0x832+6032-0x1fc1))return;
raw_spin_lock(&WALTead2f8c599);rcu_read_lock();WALT525181d1b1=
find_energy_efficient_cpu(WALT0609dbaf9d,WALT7965e1fb10,(0x3ed+4275-0x14a0),
(0x865+1125-0xcc9));rcu_read_unlock();if((WALT525181d1b1!=-(0x26b+9198-0x2658))
&&(WALT525181d1b1!=WALT7965e1fb10)&&(capacity_orig_of(WALT525181d1b1)>
capacity_orig_of(WALT7965e1fb10))){active_balance=WALT1ab55d3fe3(rq,
WALT0609dbaf9d,WALT525181d1b1);if(active_balance){mark_reserved(WALT525181d1b1);
raw_spin_unlock(&WALTead2f8c599);WALT083920bcc8=stop_one_cpu_nowait(
WALT7965e1fb10,active_load_balance_cpu_stop,rq,&rq->active_balance_work);if(!
WALT083920bcc8)clear_reserved(WALT525181d1b1);else wake_up_if_idle(
WALT525181d1b1);return;}}else{WALT02def4fea3(rq);}raw_spin_unlock(&
WALTead2f8c599);}}int sched_init_task_load_show(struct seq_file*WALT0a6cda24c8,
void*WALTe57683840e){struct inode*inode=WALT0a6cda24c8->private;struct 
task_struct*WALT0609dbaf9d;WALT0609dbaf9d=get_proc_task(inode);if(!
WALT0609dbaf9d)return-ESRCH;seq_printf(WALT0a6cda24c8,"\x25\x64" "\n",
sched_get_init_task_load(WALT0609dbaf9d));put_task_struct(WALT0609dbaf9d);return
(0x201a+480-0x21fa);}ssize_t sched_init_task_load_write(struct file*file,const 
char __user*WALT33c5f8b4bc,size_t WALT33ea1b60d7,loff_t*WALT042458434d){struct 
inode*inode=file_inode(file);struct task_struct*WALT0609dbaf9d;char 
WALTfc9cd6af11[PROC_NUMBUF];int WALTdbf899ce1d,WALT2839a901be;memset(
WALTfc9cd6af11,(0x549+244-0x63d),sizeof(WALTfc9cd6af11));if(WALT33ea1b60d7>
sizeof(WALTfc9cd6af11)-(0x239b+652-0x2626))WALT33ea1b60d7=sizeof(WALTfc9cd6af11)
-(0x1db9+1109-0x220d);if(copy_from_user(WALTfc9cd6af11,WALT33c5f8b4bc,
WALT33ea1b60d7)){WALT2839a901be=-EFAULT;goto WALTe1f307999b;}WALT2839a901be=
kstrtoint(strstrip(WALTfc9cd6af11),(0x1b9b+2437-0x2520),&WALTdbf899ce1d);if(
WALT2839a901be)goto WALTe1f307999b;WALT0609dbaf9d=get_proc_task(inode);if(!
WALT0609dbaf9d)return-ESRCH;WALT2839a901be=sched_set_init_task_load(
WALT0609dbaf9d,WALTdbf899ce1d);put_task_struct(WALT0609dbaf9d);WALTe1f307999b:
return WALT2839a901be<(0x640+7622-0x2406)?WALT2839a901be:WALT33ea1b60d7;}int 
sched_init_task_load_open(struct inode*inode,struct file*WALT65b461521a){return 
single_open(WALT65b461521a,sched_init_task_load_show,inode);}int 
sched_group_id_show(struct seq_file*WALT0a6cda24c8,void*WALTe57683840e){struct 
inode*inode=WALT0a6cda24c8->private;struct task_struct*WALT0609dbaf9d;
WALT0609dbaf9d=get_proc_task(inode);if(!WALT0609dbaf9d)return-ESRCH;seq_printf(
WALT0a6cda24c8,"\x25\x64" "\n",sched_get_group_id(WALT0609dbaf9d));
put_task_struct(WALT0609dbaf9d);return(0x922+5552-0x1ed2);}ssize_t 
sched_group_id_write(struct file*file,const char __user*WALT33c5f8b4bc,size_t 
WALT33ea1b60d7,loff_t*WALT042458434d){struct inode*inode=file_inode(file);struct
 task_struct*WALT0609dbaf9d;char WALTfc9cd6af11[PROC_NUMBUF];int WALTe3d424fbb1,
WALT2839a901be;memset(WALTfc9cd6af11,(0xce4+5861-0x23c9),sizeof(WALTfc9cd6af11))
;if(WALT33ea1b60d7>sizeof(WALTfc9cd6af11)-(0x65+1498-0x63e))WALT33ea1b60d7=
sizeof(WALTfc9cd6af11)-(0xa07+2423-0x137d);if(copy_from_user(WALTfc9cd6af11,
WALT33c5f8b4bc,WALT33ea1b60d7)){WALT2839a901be=-EFAULT;goto WALTe1f307999b;}
WALT2839a901be=kstrtoint(strstrip(WALTfc9cd6af11),(0xe9a+5333-0x236f),&
WALTe3d424fbb1);if(WALT2839a901be)goto WALTe1f307999b;WALT0609dbaf9d=
get_proc_task(inode);if(!WALT0609dbaf9d)return-ESRCH;WALT2839a901be=
sched_set_group_id(WALT0609dbaf9d,WALTe3d424fbb1);put_task_struct(WALT0609dbaf9d
);WALTe1f307999b:return WALT2839a901be<(0x536+5403-0x1a51)?WALT2839a901be:
WALT33ea1b60d7;}int sched_group_id_open(struct inode*inode,struct file*
WALT65b461521a){return single_open(WALT65b461521a,sched_group_id_show,inode);}
void sched_exit(struct task_struct*WALT0609dbaf9d){struct rq_flags 
WALT8d267b09c4;struct rq*rq;u64 WALT790680e4aa;sched_set_group_id(WALT0609dbaf9d
,(0x4c6+2880-0x1006));rq=task_rq_lock(WALT0609dbaf9d,&WALT8d267b09c4);
WALT790680e4aa=sched_ktime_clock();walt_update_task_ravg(rq->curr,rq,TASK_UPDATE
,WALT790680e4aa,(0x1ce5+277-0x1dfa));dequeue_task_core(rq,WALT0609dbaf9d,
(0x8e6+6120-0x20ce));reset_task_stats(WALT0609dbaf9d);WALT0609dbaf9d->ravg.
mark_start=WALT790680e4aa;WALT0609dbaf9d->ravg.sum_history[(0x1420+2008-0x1bf8)]
=EXITING_TASK_MARKER;enqueue_task_core(rq,WALT0609dbaf9d,(0x3b5+4183-0x140c));
clear_ed_task(WALT0609dbaf9d,rq);task_rq_unlock(rq,WALT0609dbaf9d,&
WALT8d267b09c4);free_task_load_ptrs(WALT0609dbaf9d);}
#ifdef CONFIG_SMP
int sched_wake_up_idle_show(struct seq_file*WALT0a6cda24c8,void*WALTe57683840e){
struct inode*inode=WALT0a6cda24c8->private;struct task_struct*WALT0609dbaf9d;
WALT0609dbaf9d=get_proc_task(inode);if(!WALT0609dbaf9d)return-ESRCH;seq_printf(
WALT0a6cda24c8,"\x25\x64" "\n",sched_get_wake_up_idle(WALT0609dbaf9d));
put_task_struct(WALT0609dbaf9d);return(0x527+2243-0xdea);}ssize_t 
sched_wake_up_idle_write(struct file*file,const char __user*WALT33c5f8b4bc,
size_t WALT33ea1b60d7,loff_t*WALT042458434d){struct inode*inode=file_inode(file)
;struct task_struct*WALT0609dbaf9d;char WALTfc9cd6af11[PROC_NUMBUF];int 
WALTe46fad7f31,WALT2839a901be;memset(WALTfc9cd6af11,(0x17d9+1838-0x1f07),sizeof(
WALTfc9cd6af11));if(WALT33ea1b60d7>sizeof(WALTfc9cd6af11)-(0x9a5+2797-0x1491))
WALT33ea1b60d7=sizeof(WALTfc9cd6af11)-(0x18b4+2881-0x23f4);if(copy_from_user(
WALTfc9cd6af11,WALT33c5f8b4bc,WALT33ea1b60d7)){WALT2839a901be=-EFAULT;goto 
WALTe1f307999b;}WALT2839a901be=kstrtoint(strstrip(WALTfc9cd6af11),
(0x13d0+1510-0x19b6),&WALTe46fad7f31);if(WALT2839a901be)goto WALTe1f307999b;
WALT0609dbaf9d=get_proc_task(inode);if(!WALT0609dbaf9d)return-ESRCH;
WALT2839a901be=sched_set_wake_up_idle(WALT0609dbaf9d,WALTe46fad7f31);
put_task_struct(WALT0609dbaf9d);WALTe1f307999b:return WALT2839a901be<
(0x1a30+3215-0x26bf)?WALT2839a901be:WALT33ea1b60d7;}int sched_wake_up_idle_open(
struct inode*inode,struct file*WALT65b461521a){return single_open(WALT65b461521a
,sched_wake_up_idle_show,inode);}int group_balance_cpu_not_isolated(struct 
sched_group*WALT8a34fc2d7e){cpumask_t cpus;cpumask_and(&cpus,sched_group_span(
WALT8a34fc2d7e),group_balance_mask(WALT8a34fc2d7e));cpumask_andnot(&cpus,&cpus,
cpu_isolated_mask);return cpumask_first(&cpus);}
#endif 
#ifdef CONFIG_PROC_SYSCTL
static void WALTca71bfe44d(bool WALT5829e80183){int WALT5d971be8b8=
(0x74d+2036-0xf41),cpu;struct sched_cluster*cluster;int WALT4141a1c7ab=
num_sched_clusters-(0x5e0+4620-0x17eb);if(WALT4141a1c7ab>(0x217f+1401-0x26f7)){
for_each_sched_cluster(cluster){for_each_cpu(cpu,&cluster->cpus){if(
WALT5829e80183)sched_capacity_margin_up[cpu]=sysctl_sched_capacity_margin_up[
WALT5d971be8b8];else sched_capacity_margin_down[cpu]=
sysctl_sched_capacity_margin_down[WALT5d971be8b8];}if(++WALT5d971be8b8>=
WALT4141a1c7ab)break;}}else{for_each_possible_cpu(cpu){if(WALT5829e80183)
sched_capacity_margin_up[cpu]=sysctl_sched_capacity_margin_up[
(0x869+2406-0x11cf)];else sched_capacity_margin_down[cpu]=
sysctl_sched_capacity_margin_down[(0x551+3601-0x1362)];}}}int 
sched_updown_migrate_handler(struct ctl_table*table,int WALT123284dc15,void 
__user*WALTfc9cd6af11,size_t*WALTc6af6558dd,loff_t*WALT9057b9d303){int 
WALT083920bcc8,WALT5d971be8b8;unsigned int*data=(unsigned int*)table->data;
unsigned int*WALT2582fdae21;static DEFINE_MUTEX(WALT8a2c4b3219);int 
WALT4141a1c7ab=num_sched_clusters?num_sched_clusters-(0x183f+1040-0x1c4e):
(0x986+4340-0x1a7a);if(WALT4141a1c7ab<=(0x1bb2+2686-0x2630))return-EINVAL;
mutex_lock(&WALT8a2c4b3219);if(table->maxlen!=(sizeof(unsigned int)*
WALT4141a1c7ab))table->maxlen=sizeof(unsigned int)*WALT4141a1c7ab;if(!
WALT123284dc15){WALT083920bcc8=proc_douintvec_capacity(table,WALT123284dc15,
WALTfc9cd6af11,WALTc6af6558dd,WALT9057b9d303);goto WALTa4b70d54fd;}
WALT2582fdae21=kzalloc(table->maxlen,GFP_KERNEL);if(!WALT2582fdae21){
WALT083920bcc8=-ENOMEM;goto WALTa4b70d54fd;}memcpy(WALT2582fdae21,data,table->
maxlen);WALT083920bcc8=proc_douintvec_capacity(table,WALT123284dc15,
WALTfc9cd6af11,WALTc6af6558dd,WALT9057b9d303);if(WALT083920bcc8){memcpy(data,
WALT2582fdae21,table->maxlen);goto WALT44a8d790b1;}for(WALT5d971be8b8=
(0x20d2+1576-0x26fa);WALT5d971be8b8<WALT4141a1c7ab;WALT5d971be8b8++){if(
sysctl_sched_capacity_margin_up[WALT5d971be8b8]>
sysctl_sched_capacity_margin_down[WALT5d971be8b8]){memcpy(data,WALT2582fdae21,
table->maxlen);WALT083920bcc8=-EINVAL;goto WALT44a8d790b1;}}WALTca71bfe44d(data
==&sysctl_sched_capacity_margin_up[(0x386+3585-0x1187)]);WALT44a8d790b1:kfree(
WALT2582fdae21);WALTa4b70d54fd:mutex_unlock(&WALT8a2c4b3219);return 
WALT083920bcc8;}
#endif 
int sched_isolate_count(const cpumask_t*WALTdf9caaa1ec,bool WALT8a374ecb25){
cpumask_t WALT005cc38736=CPU_MASK_NONE;if(WALT8a374ecb25){cpumask_complement(&
WALT005cc38736,cpu_online_mask);cpumask_or(&WALT005cc38736,&WALT005cc38736,
cpu_isolated_mask);cpumask_and(&WALT005cc38736,&WALT005cc38736,WALTdf9caaa1ec);}
else{cpumask_and(&WALT005cc38736,WALTdf9caaa1ec,cpu_isolated_mask);}return 
cpumask_weight(&WALT005cc38736);}
#ifdef CONFIG_HOTPLUG_CPU
static int WALT517bfbcfb2(void*data){unsigned int cpu=smp_processor_id();struct 
rq*rq=cpu_rq(cpu);struct rq_flags WALT8d267b09c4;local_irq_disable();
irq_migrate_all_off_this_cpu();sched_ttwu_pending();rq_lock(rq,&WALT8d267b09c4);
if(rq->rd){BUG_ON(!cpumask_test_cpu(cpu,rq->rd->span));set_rq_offline(rq);}
migrate_tasks(rq,&WALT8d267b09c4,false);if(rq->rd)set_rq_online(rq);rq_unlock(rq
,&WALT8d267b09c4);clear_walt_request(cpu);local_irq_enable();return
(0xc44+6108-0x2420);}static int WALT8d3857ab85(void*data){watchdog_enable(
smp_processor_id());return(0x21d+227-0x300);}static void WALT3b8baee159(int cpu)
{struct sched_domain*WALTe761d6c70c;mutex_lock(&sched_domains_mutex);
rcu_read_lock();for_each_domain(cpu,WALTe761d6c70c){int WALTd7a8f45160=
group_balance_cpu(WALTe761d6c70c->groups);init_sched_groups_capacity(cpu,
WALTe761d6c70c);if(cpu!=WALTd7a8f45160)init_sched_groups_capacity(WALTd7a8f45160
,WALTe761d6c70c);}rcu_read_unlock();mutex_unlock(&sched_domains_mutex);}static 
unsigned int WALT10baa2902e[NR_CPUS];int sched_isolate_cpu(int cpu){struct rq*rq
;cpumask_t WALT8d8e5eee2e;int WALT97642c3096=(0x8d3+6317-0x2180);u64 
WALT969c3c9b78=(0xcbb+1571-0x12de);if(trace_sched_isolate_enabled())
WALT969c3c9b78=sched_clock();cpu_maps_update_begin();cpumask_andnot(&
WALT8d8e5eee2e,cpu_online_mask,cpu_isolated_mask);if(cpu<(0x16ff+1103-0x1b4e)||
cpu>=nr_cpu_ids||!cpu_possible(cpu)||!cpu_online(cpu)){WALT97642c3096=-EINVAL;
goto WALTe1f307999b;}rq=cpu_rq(cpu);if(++WALT10baa2902e[cpu]>(0x8f0+2303-0x11ee)
)goto WALTe1f307999b;if(cpumask_weight(&WALT8d8e5eee2e)==(0x1253+1795-0x1955)){
--WALT10baa2902e[cpu];WALT97642c3096=-EINVAL;goto WALTe1f307999b;}if(!
watchdog_configured(cpu)){msleep((0x2205+1002-0x25db));if(!watchdog_configured(
cpu)){--WALT10baa2902e[cpu];WALT97642c3096=-EBUSY;goto WALTe1f307999b;}}
set_cpu_isolated(cpu,true);cpumask_clear_cpu(cpu,&WALT8d8e5eee2e);
smp_call_function_any(&WALT8d8e5eee2e,hrtimer_quiesce_cpu,&cpu,
(0x1e0d+2130-0x265e));smp_call_function_any(&WALT8d8e5eee2e,timer_quiesce_cpu,&
cpu,(0x46b+3347-0x117d));watchdog_disable(cpu);irq_lock_sparse();stop_cpus(
cpumask_of(cpu),WALT517bfbcfb2,(0x160a+1784-0x1d02));irq_unlock_sparse();
calc_load_migrate(rq);update_max_interval();WALT3b8baee159(cpu);WALTe1f307999b:
cpu_maps_update_done();trace_sched_isolate(cpu,cpumask_bits(cpu_isolated_mask)[
(0x1e91+517-0x2096)],WALT969c3c9b78,(0x6bd+1708-0xd68));return WALT97642c3096;}
int sched_unisolate_cpu_unlocked(int cpu){int WALT97642c3096=(0x2012+223-0x20f1)
;u64 WALT969c3c9b78=(0x1703+469-0x18d8);if(cpu<(0x1b70+2496-0x2530)||cpu>=
nr_cpu_ids||!cpu_possible(cpu)){WALT97642c3096=-EINVAL;goto WALTe1f307999b;}if(
trace_sched_isolate_enabled())WALT969c3c9b78=sched_clock();if(!WALT10baa2902e[
cpu]){WALT97642c3096=-EINVAL;goto WALTe1f307999b;}if(--WALT10baa2902e[cpu])goto 
WALTe1f307999b;set_cpu_isolated(cpu,false);update_max_interval();WALT3b8baee159(
cpu);if(cpu_online(cpu)){stop_cpus(cpumask_of(cpu),WALT8d3857ab85,
(0xe0f+492-0xffb));if(!atomic_fetch_or(NOHZ_KICK_MASK,nohz_flags(cpu)))
smp_send_reschedule(cpu);}WALTe1f307999b:trace_sched_isolate(cpu,cpumask_bits(
cpu_isolated_mask)[(0x10ba+5096-0x24a2)],WALT969c3c9b78,(0x1992+3187-0x2605));
return WALT97642c3096;}int sched_unisolate_cpu(int cpu){int WALT97642c3096;
cpu_maps_update_begin();WALT97642c3096=sched_unisolate_cpu_unlocked(cpu);
cpu_maps_update_done();return WALT97642c3096;}void detach_one_task_core(struct 
task_struct*WALT0609dbaf9d,struct rq*rq,struct list_head*tasks){
lockdep_assert_held(&rq->lock);WALT0609dbaf9d->on_rq=TASK_ON_RQ_MIGRATING;
deactivate_task(rq,WALT0609dbaf9d,(0xa25+1571-0x1048));list_add(&WALT0609dbaf9d
->se.group_node,tasks);}void attach_tasks_core(struct list_head*tasks,struct rq*
rq){struct task_struct*WALT0609dbaf9d;lockdep_assert_held(&rq->lock);while(!
list_empty(tasks)){WALT0609dbaf9d=list_first_entry(tasks,struct task_struct,se.
group_node);list_del_init(&WALT0609dbaf9d->se.group_node);BUG_ON(task_rq(
WALT0609dbaf9d)!=rq);activate_task(rq,WALT0609dbaf9d,(0x1af+6349-0x1a7c));
WALT0609dbaf9d->on_rq=TASK_ON_RQ_QUEUED;}}
#endif 
#endif 

