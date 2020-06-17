// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#include <linux/irq.h>
#include <linux/delay.h>
#include <trace/events/sched.h>
#include "walt.h"
#ifdef CONFIG_SCHED_WALT
unsigned int sysctl_sched_min_task_util_for_boost=(0x1dda+1420-0x2333);unsigned 
int sysctl_sched_min_task_util_for_colocation=(0x16e0+2294-0x1fb3);unsigned int 
sched_task_filter_util=(0x121c+588-0x1445);int WALT1ab55d3fe3(struct rq*rq,
struct task_struct*WALT0609dbaf9d,int WALT525181d1b1){unsigned long flags;int 
WALT094475d445=(0x1677+350-0x17d5);raw_spin_lock_irqsave(&rq->lock,flags);if(!rq
->active_balance){rq->active_balance=(0x125a+3255-0x1f10);rq->push_cpu=
WALT525181d1b1;get_task_struct(WALT0609dbaf9d);rq->wrq.push_task=WALT0609dbaf9d;
WALT094475d445=(0x1eb7+1690-0x2550);}raw_spin_unlock_irqrestore(&rq->lock,flags)
;return WALT094475d445;}struct WALT9e9109c2b0{struct work_struct WALT61a2ee39fd;
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
WALTd600851d0e=(0xf16+2845-0x1a33),WALT32bc620250,WALT603690f2ae=
(0x1472+4175-0x24c1);int WALT915c187717=nr_cpu_ids,WALT69f29b0e89=nr_cpu_ids;int
 WALT5d971be8b8,WALT3eb4d59849=cpu_of(WALTd01f3eedf0);struct rq*WALT38ee64137f;
struct WALT9e9109c2b0*WALT81107b3e03=NULL;if(!walt_rotation_enabled)return;if(!
is_min_capacity_cpu(WALT3eb4d59849))return;WALT0cc0a342b9=sched_ktime_clock();
for_each_possible_cpu(WALT5d971be8b8){struct rq*rq=cpu_rq(WALT5d971be8b8);if(!
is_min_capacity_cpu(WALT5d971be8b8))break;if(is_reserved(WALT5d971be8b8))
continue;if(!rq->misfit_task_load||rq->curr->sched_class!=&fair_sched_class)
continue;WALT70b23f67e1=WALT0cc0a342b9-rq->curr->wts.last_enqueued_ts;if(
WALT70b23f67e1>WALTd600851d0e){WALTd600851d0e=WALT70b23f67e1;WALT915c187717=
WALT5d971be8b8;}}if(WALT915c187717!=WALT3eb4d59849)return;for_each_possible_cpu(
WALT5d971be8b8){struct rq*rq=cpu_rq(WALT5d971be8b8);if(is_min_capacity_cpu(
WALT5d971be8b8))continue;if(is_reserved(WALT5d971be8b8))continue;if(rq->curr->
sched_class!=&fair_sched_class)continue;if(rq->nr_running>(0x739+6221-0x1f85))
continue;WALT32bc620250=WALT0cc0a342b9-rq->curr->wts.last_enqueued_ts;if(
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
active_balance;int WALT525181d1b1=-(0x164c+3960-0x25c3);int WALT7965e1fb10=
task_cpu(WALT0609dbaf9d);int WALT083920bcc8;if(rq->misfit_task_load){if(rq->curr
->state!=TASK_RUNNING||rq->curr->nr_cpus_allowed==(0x1185+3778-0x2046))return;
raw_spin_lock(&WALTead2f8c599);rcu_read_lock();WALT525181d1b1=
find_energy_efficient_cpu(WALT0609dbaf9d,WALT7965e1fb10,(0x1d46+2346-0x2670),
(0x19b+8571-0x2315));rcu_read_unlock();if((WALT525181d1b1>=(0x50d+4934-0x1853))
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
(0x13e2+3507-0x2195);}ssize_t sched_init_task_load_write(struct file*file,const 
char __user*WALT33c5f8b4bc,size_t WALT33ea1b60d7,loff_t*WALT042458434d){struct 
inode*inode=file_inode(file);struct task_struct*WALT0609dbaf9d;char 
WALTfc9cd6af11[PROC_NUMBUF];int WALTdbf899ce1d,WALT2839a901be;memset(
WALTfc9cd6af11,(0x8b4+2970-0x144e),sizeof(WALTfc9cd6af11));if(WALT33ea1b60d7>
sizeof(WALTfc9cd6af11)-(0x33+252-0x12e))WALT33ea1b60d7=sizeof(WALTfc9cd6af11)-
(0x6d0+276-0x7e3);if(copy_from_user(WALTfc9cd6af11,WALT33c5f8b4bc,WALT33ea1b60d7
)){WALT2839a901be=-EFAULT;goto WALTe1f307999b;}WALT2839a901be=kstrtoint(strstrip
(WALTfc9cd6af11),(0x1dac+2014-0x258a),&WALTdbf899ce1d);if(WALT2839a901be)goto 
WALTe1f307999b;WALT0609dbaf9d=get_proc_task(inode);if(!WALT0609dbaf9d)return-
ESRCH;WALT2839a901be=sched_set_init_task_load(WALT0609dbaf9d,WALTdbf899ce1d);
put_task_struct(WALT0609dbaf9d);WALTe1f307999b:return WALT2839a901be<
(0xacf+1765-0x11b4)?WALT2839a901be:WALT33ea1b60d7;}int sched_init_task_load_open
(struct inode*inode,struct file*WALT65b461521a){return single_open(
WALT65b461521a,sched_init_task_load_show,inode);}int sched_group_id_show(struct 
seq_file*WALT0a6cda24c8,void*WALTe57683840e){struct inode*inode=WALT0a6cda24c8->
private;struct task_struct*WALT0609dbaf9d;WALT0609dbaf9d=get_proc_task(inode);if
(!WALT0609dbaf9d)return-ESRCH;seq_printf(WALT0a6cda24c8,"\x25\x64" "\n",
sched_get_group_id(WALT0609dbaf9d));put_task_struct(WALT0609dbaf9d);return
(0x59c+6929-0x20ad);}ssize_t sched_group_id_write(struct file*file,const char 
__user*WALT33c5f8b4bc,size_t WALT33ea1b60d7,loff_t*WALT042458434d){struct inode*
inode=file_inode(file);struct task_struct*WALT0609dbaf9d;char WALTfc9cd6af11[
PROC_NUMBUF];int WALTe3d424fbb1,WALT2839a901be;memset(WALTfc9cd6af11,
(0x3c3+8574-0x2541),sizeof(WALTfc9cd6af11));if(WALT33ea1b60d7>sizeof(
WALTfc9cd6af11)-(0xc5d+2888-0x17a4))WALT33ea1b60d7=sizeof(WALTfc9cd6af11)-
(0x1136+864-0x1495);if(copy_from_user(WALTfc9cd6af11,WALT33c5f8b4bc,
WALT33ea1b60d7)){WALT2839a901be=-EFAULT;goto WALTe1f307999b;}WALT2839a901be=
kstrtoint(strstrip(WALTfc9cd6af11),(0xb06+2287-0x13f5),&WALTe3d424fbb1);if(
WALT2839a901be)goto WALTe1f307999b;WALT0609dbaf9d=get_proc_task(inode);if(!
WALT0609dbaf9d)return-ESRCH;WALT2839a901be=sched_set_group_id(WALT0609dbaf9d,
WALTe3d424fbb1);put_task_struct(WALT0609dbaf9d);WALTe1f307999b:return 
WALT2839a901be<(0x959+1012-0xd4d)?WALT2839a901be:WALT33ea1b60d7;}int 
sched_group_id_open(struct inode*inode,struct file*WALT65b461521a){return 
single_open(WALT65b461521a,sched_group_id_show,inode);}
#ifdef CONFIG_SMP
int sched_wake_up_idle_show(struct seq_file*WALT0a6cda24c8,void*WALTe57683840e){
struct inode*inode=WALT0a6cda24c8->private;struct task_struct*WALT0609dbaf9d;
WALT0609dbaf9d=get_proc_task(inode);if(!WALT0609dbaf9d)return-ESRCH;seq_printf(
WALT0a6cda24c8,"\x25\x64" "\n",sched_get_wake_up_idle(WALT0609dbaf9d));
put_task_struct(WALT0609dbaf9d);return(0x516+4000-0x14b6);}ssize_t 
sched_wake_up_idle_write(struct file*file,const char __user*WALT33c5f8b4bc,
size_t WALT33ea1b60d7,loff_t*WALT042458434d){struct inode*inode=file_inode(file)
;struct task_struct*WALT0609dbaf9d;char WALTfc9cd6af11[PROC_NUMBUF];int 
WALTe46fad7f31,WALT2839a901be;memset(WALTfc9cd6af11,(0x1c51+649-0x1eda),sizeof(
WALTfc9cd6af11));if(WALT33ea1b60d7>sizeof(WALTfc9cd6af11)-(0x92a+5552-0x1ed9))
WALT33ea1b60d7=sizeof(WALTfc9cd6af11)-(0xf3d+1361-0x148d);if(copy_from_user(
WALTfc9cd6af11,WALT33c5f8b4bc,WALT33ea1b60d7)){WALT2839a901be=-EFAULT;goto 
WALTe1f307999b;}WALT2839a901be=kstrtoint(strstrip(WALTfc9cd6af11),
(0xc72+756-0xf66),&WALTe46fad7f31);if(WALT2839a901be)goto WALTe1f307999b;
WALT0609dbaf9d=get_proc_task(inode);if(!WALT0609dbaf9d)return-ESRCH;
WALT2839a901be=sched_set_wake_up_idle(WALT0609dbaf9d,WALTe46fad7f31);
put_task_struct(WALT0609dbaf9d);WALTe1f307999b:return WALT2839a901be<
(0x14e4+670-0x1782)?WALT2839a901be:WALT33ea1b60d7;}int sched_wake_up_idle_open(
struct inode*inode,struct file*WALT65b461521a){return single_open(WALT65b461521a
,sched_wake_up_idle_show,inode);}int group_balance_cpu_not_isolated(struct 
sched_group*WALT8a34fc2d7e){cpumask_t cpus;cpumask_and(&cpus,sched_group_span(
WALT8a34fc2d7e),group_balance_mask(WALT8a34fc2d7e));cpumask_andnot(&cpus,&cpus,
cpu_isolated_mask);return cpumask_first(&cpus);}
#endif 
#ifdef CONFIG_PROC_SYSCTL
static void WALTca71bfe44d(bool WALT5829e80183){int WALT5d971be8b8=
(0x805+2486-0x11bb),cpu;struct walt_sched_cluster*cluster;int WALT4141a1c7ab=
num_sched_clusters-(0x610+6574-0x1fbd);if(WALT4141a1c7ab>(0x136c+1841-0x1a9c)){
for_each_sched_cluster(cluster){for_each_cpu(cpu,&cluster->cpus){if(
WALT5829e80183)sched_capacity_margin_up[cpu]=sysctl_sched_capacity_margin_up[
WALT5d971be8b8];else sched_capacity_margin_down[cpu]=
sysctl_sched_capacity_margin_down[WALT5d971be8b8];}if(++WALT5d971be8b8>=
WALT4141a1c7ab)break;}}else{for_each_possible_cpu(cpu){if(WALT5829e80183)
sched_capacity_margin_up[cpu]=sysctl_sched_capacity_margin_up[
(0x1730+3639-0x2567)];else sched_capacity_margin_down[cpu]=
sysctl_sched_capacity_margin_down[(0x6c5+2709-0x115a)];}}}int 
sched_updown_migrate_handler(struct ctl_table*table,int WALT123284dc15,void 
__user*WALTfc9cd6af11,size_t*WALTc6af6558dd,loff_t*WALT9057b9d303){int 
WALT083920bcc8,WALT5d971be8b8;unsigned int*data=(unsigned int*)table->data;
unsigned int*WALT2582fdae21;static DEFINE_MUTEX(WALT8a2c4b3219);int 
WALT4141a1c7ab=num_sched_clusters?num_sched_clusters-(0xf64+3081-0x1b6c):
(0x49a+1859-0xbdd);if(WALT4141a1c7ab<=(0x127c+4467-0x23ef))return-EINVAL;
mutex_lock(&WALT8a2c4b3219);if(table->maxlen!=(sizeof(unsigned int)*
WALT4141a1c7ab))table->maxlen=sizeof(unsigned int)*WALT4141a1c7ab;if(!
WALT123284dc15){WALT083920bcc8=proc_douintvec_capacity(table,WALT123284dc15,
WALTfc9cd6af11,WALTc6af6558dd,WALT9057b9d303);goto WALTa4b70d54fd;}
WALT2582fdae21=kzalloc(table->maxlen,GFP_KERNEL);if(!WALT2582fdae21){
WALT083920bcc8=-ENOMEM;goto WALTa4b70d54fd;}memcpy(WALT2582fdae21,data,table->
maxlen);WALT083920bcc8=proc_douintvec_capacity(table,WALT123284dc15,
WALTfc9cd6af11,WALTc6af6558dd,WALT9057b9d303);if(WALT083920bcc8){memcpy(data,
WALT2582fdae21,table->maxlen);goto WALT44a8d790b1;}for(WALT5d971be8b8=
(0x6f5+1400-0xc6d);WALT5d971be8b8<WALT4141a1c7ab;WALT5d971be8b8++){if(
sysctl_sched_capacity_margin_up[WALT5d971be8b8]>
sysctl_sched_capacity_margin_down[WALT5d971be8b8]){memcpy(data,WALT2582fdae21,
table->maxlen);WALT083920bcc8=-EINVAL;goto WALT44a8d790b1;}}WALTca71bfe44d(data
==&sysctl_sched_capacity_margin_up[(0x59c+6305-0x1e3d)]);WALT44a8d790b1:kfree(
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
(0xb29+6291-0x23bc);}static int WALT8d3857ab85(void*data){watchdog_enable(
smp_processor_id());return(0x1211+1344-0x1751);}static void WALT3b8baee159(int 
cpu){struct sched_domain*WALTe761d6c70c;mutex_lock(&sched_domains_mutex);
rcu_read_lock();for_each_domain(cpu,WALTe761d6c70c){int WALTd7a8f45160=
group_balance_cpu(WALTe761d6c70c->groups);init_sched_groups_capacity(cpu,
WALTe761d6c70c);if(cpu!=WALTd7a8f45160)init_sched_groups_capacity(WALTd7a8f45160
,WALTe761d6c70c);}rcu_read_unlock();mutex_unlock(&sched_domains_mutex);}static 
unsigned int WALT10baa2902e[NR_CPUS];int sched_isolate_cpu(int cpu){struct rq*rq
;cpumask_t WALT8d8e5eee2e;int WALT97642c3096=(0x5f2+6199-0x1e29);u64 
WALT969c3c9b78=(0x1d7f+1997-0x254c);if(trace_sched_isolate_enabled())
WALT969c3c9b78=sched_clock();cpu_maps_update_begin();cpumask_andnot(&
WALT8d8e5eee2e,cpu_online_mask,cpu_isolated_mask);if(cpu<(0x240f+32-0x242f)||cpu
>=nr_cpu_ids||!cpu_possible(cpu)||!cpu_online(cpu)){WALT97642c3096=-EINVAL;goto 
WALTe1f307999b;}rq=cpu_rq(cpu);if(++WALT10baa2902e[cpu]>(0x3d6+8439-0x24cc))goto
 WALTe1f307999b;if(cpumask_weight(&WALT8d8e5eee2e)==(0x133+3167-0xd91)){--
WALT10baa2902e[cpu];WALT97642c3096=-EINVAL;goto WALTe1f307999b;}if(!
watchdog_configured(cpu)){msleep((0x7cb+2842-0x12d1));if(!watchdog_configured(
cpu)){--WALT10baa2902e[cpu];WALT97642c3096=-EBUSY;goto WALTe1f307999b;}}
set_cpu_isolated(cpu,true);cpumask_clear_cpu(cpu,&WALT8d8e5eee2e);
smp_call_function_any(&WALT8d8e5eee2e,hrtimer_quiesce_cpu,&cpu,
(0x5b4+3071-0x11b2));smp_call_function_any(&WALT8d8e5eee2e,timer_quiesce_cpu,&
cpu,(0x201+1964-0x9ac));watchdog_disable(cpu);irq_lock_sparse();stop_cpus(
cpumask_of(cpu),WALT517bfbcfb2,(0x119d+327-0x12e4));irq_unlock_sparse();
calc_load_migrate(rq);update_max_interval();WALT3b8baee159(cpu);WALTe1f307999b:
cpu_maps_update_done();trace_sched_isolate(cpu,cpumask_bits(cpu_isolated_mask)[
(0xdf8+944-0x11a8)],WALT969c3c9b78,(0x54b+6395-0x1e45));return WALT97642c3096;}
int sched_unisolate_cpu_unlocked(int cpu){int WALT97642c3096=(0x2a1+4156-0x12dd)
;u64 WALT969c3c9b78=(0xa03+177-0xab4);if(cpu<(0x17a8+1045-0x1bbd)||cpu>=
nr_cpu_ids||!cpu_possible(cpu)){WALT97642c3096=-EINVAL;goto WALTe1f307999b;}if(
trace_sched_isolate_enabled())WALT969c3c9b78=sched_clock();if(!WALT10baa2902e[
cpu]){WALT97642c3096=-EINVAL;goto WALTe1f307999b;}if(--WALT10baa2902e[cpu])goto 
WALTe1f307999b;set_cpu_isolated(cpu,false);update_max_interval();WALT3b8baee159(
cpu);if(cpu_online(cpu)){stop_cpus(cpumask_of(cpu),WALT8d3857ab85,
(0xeab+3093-0x1ac0));if(!atomic_fetch_or(NOHZ_KICK_MASK,nohz_flags(cpu)))
smp_send_reschedule(cpu);}WALTe1f307999b:trace_sched_isolate(cpu,cpumask_bits(
cpu_isolated_mask)[(0x5ec+2575-0xffb)],WALT969c3c9b78,(0x1ed+2267-0xac8));return
 WALT97642c3096;}int sched_unisolate_cpu(int cpu){int WALT97642c3096;
cpu_maps_update_begin();WALT97642c3096=sched_unisolate_cpu_unlocked(cpu);
cpu_maps_update_done();return WALT97642c3096;}void detach_one_task_core(struct 
task_struct*WALT0609dbaf9d,struct rq*rq,struct list_head*tasks){
lockdep_assert_held(&rq->lock);WALT0609dbaf9d->on_rq=TASK_ON_RQ_MIGRATING;
deactivate_task(rq,WALT0609dbaf9d,(0x5bc+7064-0x2154));list_add(&WALT0609dbaf9d
->se.group_node,tasks);}void attach_tasks_core(struct list_head*tasks,struct rq*
rq){struct task_struct*WALT0609dbaf9d;lockdep_assert_held(&rq->lock);while(!
list_empty(tasks)){WALT0609dbaf9d=list_first_entry(tasks,struct task_struct,se.
group_node);list_del_init(&WALT0609dbaf9d->se.group_node);BUG_ON(task_rq(
WALT0609dbaf9d)!=rq);activate_task(rq,WALT0609dbaf9d,(0x1992+2435-0x2315));
WALT0609dbaf9d->on_rq=TASK_ON_RQ_QUEUED;}}
#endif 
#endif 

