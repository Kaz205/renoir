// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#define pr_fmt(WALTc4af4bede1)	"\x63\x6f\x72\x65\x5f\x63\x74\x6c\x3a\x20" \
WALTc4af4bede1
#include <linux/init.h>
#include <linux/cpu.h>
#include <linux/cpumask.h>
#include <linux/cpufreq.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/sched/rt.h>
#include <linux/syscore_ops.h>
#include <uapi/linux/sched/types.h>
#include <linux/sched/core_ctl.h>
#include <trace/events/sched.h>
#include "walt.h"
struct WALTd84195416f{bool WALTb6181247c7;unsigned int min_cpus;unsigned int 
max_cpus;unsigned int offline_delay_ms;unsigned int busy_up_thres[
MAX_CPUS_PER_CLUSTER];unsigned int busy_down_thres[MAX_CPUS_PER_CLUSTER];
unsigned int active_cpus;unsigned int WALT3fc386a32e;unsigned int WALTd76a53732a
;unsigned int WALT9656065c1c;cpumask_t WALT39abd1de52;unsigned int need_cpus;
unsigned int task_thres;unsigned int WALTf368d5dcae;unsigned int WALT263a14abab;
unsigned int nr_prev_assist_thresh;s64 WALT474287bcf5;struct list_head 
WALT895ecc2391;bool WALTa280f52f04;spinlock_t WALTffb20e4808;bool enable;int 
WALT78602fc8a3;struct task_struct*WALT2e935f34a1;unsigned int WALT76f375774d;
unsigned int boost;struct kobject kobj;unsigned int WALTcc9821f091;};struct 
WALT722543f60e{bool WALT087db4d18a;unsigned int WALT517f9bdd84;unsigned int 
WALT8f9ab72eb9;bool not_preferred;struct WALTd84195416f*WALT1b752e214a;struct 
list_head WALTa7f3b2896c;bool WALT7f508cb38b;};static DEFINE_PER_CPU(struct 
WALT722543f60e,WALT22ef1845d7);static struct WALTd84195416f WALT9a7bdf60eb[
MAX_CLUSTERS];static unsigned int WALT3480a8e71f;
#define WALT213747575e(WALT1b752e214a, WALT8aa1674e1f) \
	for (; (WALT8aa1674e1f) < WALT3480a8e71f && ((WALT1b752e214a) = &WALT9a7bdf60eb\
[WALT8aa1674e1f]);\
		WALT8aa1674e1f++)
static DEFINE_SPINLOCK(WALT78e2cdac9a);static void WALT041d9949cf(struct 
WALTd84195416f*WALT048da5e00c);static void WALTe68f5dd857(struct WALTd84195416f*
WALT048da5e00c);static bool WALT69be84bb38;ATOMIC_NOTIFIER_HEAD(WALTe24f5fc06e);
static unsigned int WALT86ffcc7dfd;static unsigned int WALTbc04b417fa(const 
struct WALTd84195416f*WALT1b752e214a);static ssize_t store_min_cpus(struct 
WALTd84195416f*WALT048da5e00c,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){
unsigned int WALTc94d3d8015;if(sscanf(WALT33c5f8b4bc,"\x25\x75" "\n",&
WALTc94d3d8015)!=(0xb1+7285-0x1d25))return-EINVAL;WALT048da5e00c->min_cpus=min(
WALTc94d3d8015,WALT048da5e00c->WALT3fc386a32e);WALTe68f5dd857(WALT048da5e00c);
return WALT33ea1b60d7;}static ssize_t show_min_cpus(const struct WALTd84195416f*
WALT048da5e00c,char*WALT33c5f8b4bc){return snprintf(WALT33c5f8b4bc,PAGE_SIZE,
"\x25\x75" "\n",WALT048da5e00c->min_cpus);}static ssize_t store_max_cpus(struct 
WALTd84195416f*WALT048da5e00c,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){
unsigned int WALTc94d3d8015;if(sscanf(WALT33c5f8b4bc,"\x25\x75" "\n",&
WALTc94d3d8015)!=(0x1495+49-0x14c5))return-EINVAL;WALT048da5e00c->max_cpus=min(
WALTc94d3d8015,WALT048da5e00c->WALT3fc386a32e);WALTe68f5dd857(WALT048da5e00c);
return WALT33ea1b60d7;}static ssize_t show_max_cpus(const struct WALTd84195416f*
WALT048da5e00c,char*WALT33c5f8b4bc){return snprintf(WALT33c5f8b4bc,PAGE_SIZE,
"\x25\x75" "\n",WALT048da5e00c->max_cpus);}static ssize_t store_offline_delay_ms
(struct WALTd84195416f*WALT048da5e00c,const char*WALT33c5f8b4bc,size_t 
WALT33ea1b60d7){unsigned int WALTc94d3d8015;if(sscanf(WALT33c5f8b4bc,
"\x25\x75" "\n",&WALTc94d3d8015)!=(0xd11+4608-0x1f10))return-EINVAL;
WALT048da5e00c->offline_delay_ms=WALTc94d3d8015;WALT041d9949cf(WALT048da5e00c);
return WALT33ea1b60d7;}static ssize_t show_task_thres(const struct 
WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){return snprintf(
WALT33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",WALT048da5e00c->task_thres);}static 
ssize_t store_task_thres(struct WALTd84195416f*WALT048da5e00c,const char*
WALT33c5f8b4bc,size_t WALT33ea1b60d7){unsigned int WALTc94d3d8015;if(sscanf(
WALT33c5f8b4bc,"\x25\x75" "\n",&WALTc94d3d8015)!=(0x1d96+417-0x1f36))return-
EINVAL;if(WALTc94d3d8015<WALT048da5e00c->WALT3fc386a32e)return-EINVAL;
WALT048da5e00c->task_thres=WALTc94d3d8015;WALT041d9949cf(WALT048da5e00c);return 
WALT33ea1b60d7;}static ssize_t show_nr_prev_assist_thresh(const struct 
WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){return snprintf(
WALT33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",WALT048da5e00c->nr_prev_assist_thresh);
}static ssize_t store_nr_prev_assist_thresh(struct WALTd84195416f*WALT048da5e00c
,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){unsigned int WALTc94d3d8015;if
(sscanf(WALT33c5f8b4bc,"\x25\x75" "\n",&WALTc94d3d8015)!=(0xa80+7162-0x2679))
return-EINVAL;WALT048da5e00c->nr_prev_assist_thresh=WALTc94d3d8015;
WALT041d9949cf(WALT048da5e00c);return WALT33ea1b60d7;}static ssize_t 
show_offline_delay_ms(const struct WALTd84195416f*WALT048da5e00c,char*
WALT33c5f8b4bc){return snprintf(WALT33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",
WALT048da5e00c->offline_delay_ms);}static ssize_t store_busy_up_thres(struct 
WALTd84195416f*WALT048da5e00c,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){
unsigned int WALTc94d3d8015[MAX_CPUS_PER_CLUSTER];int WALT083920bcc8,
WALT5d971be8b8;WALT083920bcc8=sscanf(WALT33c5f8b4bc,
"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
WALTc94d3d8015[(0x1e6c+1549-0x2479)],&WALTc94d3d8015[(0x39+8106-0x1fe2)],&
WALTc94d3d8015[(0x1a+9809-0x2669)],&WALTc94d3d8015[(0x12d7+4336-0x23c4)],&
WALTc94d3d8015[(0x1247+4230-0x22c9)],&WALTc94d3d8015[(0x9a1+1376-0xefc)]);if(
WALT083920bcc8!=(0x151a+1444-0x1abd)&&WALT083920bcc8!=WALT048da5e00c->
WALT3fc386a32e)return-EINVAL;if(WALT083920bcc8==(0x2381+702-0x263e)){for(
WALT5d971be8b8=(0xd8f+4697-0x1fe8);WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e
;WALT5d971be8b8++)WALT048da5e00c->busy_up_thres[WALT5d971be8b8]=WALTc94d3d8015[
(0xc54+637-0xed1)];}else{for(WALT5d971be8b8=(0xb4a+5140-0x1f5e);WALT5d971be8b8<
WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++)WALT048da5e00c->busy_up_thres[
WALT5d971be8b8]=WALTc94d3d8015[WALT5d971be8b8];}WALT041d9949cf(WALT048da5e00c);
return WALT33ea1b60d7;}static ssize_t show_busy_up_thres(const struct 
WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){int WALT5d971be8b8,
WALT33ea1b60d7=(0xa28+7236-0x266c);for(WALT5d971be8b8=(0x819+6747-0x2274);
WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++)WALT33ea1b60d7+=
snprintf(WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,"\x25\x75\x20",
WALT048da5e00c->busy_up_thres[WALT5d971be8b8]);WALT33ea1b60d7+=snprintf(
WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,"\n");return 
WALT33ea1b60d7;}static ssize_t store_busy_down_thres(struct WALTd84195416f*
WALT048da5e00c,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){unsigned int 
WALTc94d3d8015[MAX_CPUS_PER_CLUSTER];int WALT083920bcc8,WALT5d971be8b8;
WALT083920bcc8=sscanf(WALT33c5f8b4bc,
"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
WALTc94d3d8015[(0xa42+3206-0x16c8)],&WALTc94d3d8015[(0xed0+3816-0x1db7)],&
WALTc94d3d8015[(0x18f2+2225-0x21a1)],&WALTc94d3d8015[(0x295+3132-0xece)],&
WALTc94d3d8015[(0x1c56+2581-0x2667)],&WALTc94d3d8015[(0x173a+3198-0x23b3)]);if(
WALT083920bcc8!=(0xd7c+4118-0x1d91)&&WALT083920bcc8!=WALT048da5e00c->
WALT3fc386a32e)return-EINVAL;if(WALT083920bcc8==(0x14a+2643-0xb9c)){for(
WALT5d971be8b8=(0x43+7527-0x1daa);WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;
WALT5d971be8b8++)WALT048da5e00c->busy_down_thres[WALT5d971be8b8]=WALTc94d3d8015[
(0x999+1334-0xecf)];}else{for(WALT5d971be8b8=(0xe94+3237-0x1b39);WALT5d971be8b8<
WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++)WALT048da5e00c->busy_down_thres[
WALT5d971be8b8]=WALTc94d3d8015[WALT5d971be8b8];}WALT041d9949cf(WALT048da5e00c);
return WALT33ea1b60d7;}static ssize_t show_busy_down_thres(const struct 
WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){int WALT5d971be8b8,
WALT33ea1b60d7=(0x1bf+5845-0x1894);for(WALT5d971be8b8=(0x414+1328-0x944);
WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++)WALT33ea1b60d7+=
snprintf(WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,"\x25\x75\x20",
WALT048da5e00c->busy_down_thres[WALT5d971be8b8]);WALT33ea1b60d7+=snprintf(
WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,"\n");return 
WALT33ea1b60d7;}static ssize_t store_enable(struct WALTd84195416f*WALT048da5e00c
,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){unsigned int WALTc94d3d8015;
bool WALTd09cc5ef75;if(sscanf(WALT33c5f8b4bc,"\x25\x75" "\n",&WALTc94d3d8015)!=
(0x1147+3756-0x1ff2))return-EINVAL;WALTd09cc5ef75=!!WALTc94d3d8015;if(
WALTd09cc5ef75!=WALT048da5e00c->enable){WALT048da5e00c->enable=WALTd09cc5ef75;
WALT041d9949cf(WALT048da5e00c);}return WALT33ea1b60d7;}static ssize_t 
show_enable(const struct WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){
return scnprintf(WALT33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",WALT048da5e00c->enable
);}static ssize_t show_need_cpus(const struct WALTd84195416f*WALT048da5e00c,char
*WALT33c5f8b4bc){return snprintf(WALT33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",
WALT048da5e00c->need_cpus);}static ssize_t show_active_cpus(const struct 
WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){return snprintf(
WALT33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",WALT048da5e00c->active_cpus);}static 
ssize_t show_global_state(const struct WALTd84195416f*WALT048da5e00c,char*
WALT33c5f8b4bc){struct WALT722543f60e*WALTe2cca49edf;struct WALTd84195416f*
WALT1b752e214a;ssize_t WALT33ea1b60d7=(0x147c+1726-0x1b3a);unsigned int 
WALT8f9ab72eb9;spin_lock_irq(&WALT78e2cdac9a);for_each_possible_cpu(
WALT8f9ab72eb9){WALTe2cca49edf=&per_cpu(WALT22ef1845d7,WALT8f9ab72eb9);
WALT1b752e214a=WALTe2cca49edf->WALT1b752e214a;if(!WALT1b752e214a||!
WALT1b752e214a->WALTb6181247c7)continue;WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+
WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,"\x43\x50\x55\x25\x75" "\n",
WALT8f9ab72eb9);WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE
-WALT33ea1b60d7,"\t" "\x43\x50\x55\x3a\x20\x25\x75" "\n",WALTe2cca49edf->
WALT8f9ab72eb9);WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE
-WALT33ea1b60d7,"\t" "\x4f\x6e\x6c\x69\x6e\x65\x3a\x20\x25\x75" "\n",cpu_online(
WALTe2cca49edf->WALT8f9ab72eb9));WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+
WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,
"\t" "\x49\x73\x6f\x6c\x61\x74\x65\x64\x3a\x20\x25\x75" "\n",cpu_isolated(
WALTe2cca49edf->WALT8f9ab72eb9));WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+
WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,
"\t" "\x46\x69\x72\x73\x74\x20\x43\x50\x55\x3a\x20\x25\x75" "\n",WALT1b752e214a
->WALT76f375774d);WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+WALT33ea1b60d7,
PAGE_SIZE-WALT33ea1b60d7,"\t" "\x42\x75\x73\x79\x25\x25\x3a\x20\x25\x75" "\n",
WALTe2cca49edf->WALT517f9bdd84);WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+
WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,
"\t" "\x49\x73\x20\x62\x75\x73\x79\x3a\x20\x25\x75" "\n",WALTe2cca49edf->
WALT087db4d18a);WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE
-WALT33ea1b60d7,
"\t" "\x4e\x6f\x74\x20\x70\x72\x65\x66\x65\x72\x72\x65\x64\x3a\x20\x25\x75" "\n"
,WALTe2cca49edf->not_preferred);WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+
WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,
"\t" "\x4e\x72\x20\x72\x75\x6e\x6e\x69\x6e\x67\x3a\x20\x25\x75" "\n",
WALT1b752e214a->WALT78602fc8a3);WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+
WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,
"\t" "\x41\x63\x74\x69\x76\x65\x20\x43\x50\x55\x73\x3a\x20\x25\x75" "\n",
WALTbc04b417fa(WALT1b752e214a));WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+
WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,
"\t" "\x4e\x65\x65\x64\x20\x43\x50\x55\x73\x3a\x20\x25\x75" "\n",WALT1b752e214a
->need_cpus);WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE-
WALT33ea1b60d7,
"\t" "\x4e\x72\x20\x69\x73\x6f\x6c\x61\x74\x65\x64\x20\x43\x50\x55\x73\x3a\x20\x25\x75" "\n"
,WALT1b752e214a->WALTd76a53732a);WALT33ea1b60d7+=snprintf(WALT33c5f8b4bc+
WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,
"\t" "\x42\x6f\x6f\x73\x74\x3a\x20\x25\x75" "\n",(unsigned int)WALT1b752e214a->
boost);}spin_unlock_irq(&WALT78e2cdac9a);return WALT33ea1b60d7;}static ssize_t 
store_not_preferred(struct WALTd84195416f*WALT048da5e00c,const char*
WALT33c5f8b4bc,size_t WALT33ea1b60d7){struct WALT722543f60e*WALTe2cca49edf;
unsigned int WALT5d971be8b8;unsigned int WALTc94d3d8015[MAX_CPUS_PER_CLUSTER];
unsigned long WALT05b7c9a580;int WALT083920bcc8;int WALT30bdc18e2b=
(0x801+4012-0x17ad);WALT083920bcc8=sscanf(WALT33c5f8b4bc,
"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
WALTc94d3d8015[(0xa8a+6112-0x226a)],&WALTc94d3d8015[(0xdd2+5975-0x2528)],&
WALTc94d3d8015[(0x1a8c+578-0x1ccc)],&WALTc94d3d8015[(0xca1+6646-0x2694)],&
WALTc94d3d8015[(0x10af+4926-0x23e9)],&WALTc94d3d8015[(0xf56+4164-0x1f95)]);if(
WALT083920bcc8!=WALT048da5e00c->WALT3fc386a32e)return-EINVAL;spin_lock_irqsave(&
WALT78e2cdac9a,WALT05b7c9a580);for(WALT5d971be8b8=(0x21d6+196-0x229a);
WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++){WALTe2cca49edf=&
per_cpu(WALT22ef1845d7,WALT5d971be8b8+WALT048da5e00c->WALT76f375774d);
WALTe2cca49edf->not_preferred=WALTc94d3d8015[WALT5d971be8b8];WALT30bdc18e2b+=!!
WALTc94d3d8015[WALT5d971be8b8];}WALT048da5e00c->WALT9656065c1c=WALT30bdc18e2b;
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);return WALT33ea1b60d7;}
static ssize_t show_not_preferred(const struct WALTd84195416f*WALT048da5e00c,
char*WALT33c5f8b4bc){struct WALT722543f60e*WALTe2cca49edf;ssize_t WALT33ea1b60d7
=(0xc39+5941-0x236e);unsigned long WALT05b7c9a580;int WALT5d971be8b8;
spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);for(WALT5d971be8b8=
(0xc09+44-0xc35);WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++)
{WALTe2cca49edf=&per_cpu(WALT22ef1845d7,WALT5d971be8b8+WALT048da5e00c->
WALT76f375774d);WALT33ea1b60d7+=scnprintf(WALT33c5f8b4bc+WALT33ea1b60d7,
PAGE_SIZE-WALT33ea1b60d7,"\x43\x50\x55\x23\x25\x64\x3a\x20\x25\x75" "\n",
WALTe2cca49edf->WALT8f9ab72eb9,WALTe2cca49edf->not_preferred);}
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);return WALT33ea1b60d7;}
struct core_ctl_attr{struct attribute attr;ssize_t(*show)(const struct 
WALTd84195416f*,char*);ssize_t(*store)(struct WALTd84195416f*,const char*,size_t
 WALT33ea1b60d7);};
#define core_ctl_attr_ro(WALTb25dfb9431)		\
static struct core_ctl_attr WALTb25dfb9431 =	\
__ATTR(WALTb25dfb9431, (0x63a+860-0x872), show_##WALTb25dfb9431, NULL)
#define core_ctl_attr_rw(WALTb25dfb9431)			\
static struct core_ctl_attr WALTb25dfb9431 =		\
__ATTR(WALTb25dfb9431, (0x17f0+2735-0x20fb), show_##WALTb25dfb9431, store_##\
WALTb25dfb9431)
core_ctl_attr_rw(min_cpus);core_ctl_attr_rw(max_cpus);core_ctl_attr_rw(
offline_delay_ms);core_ctl_attr_rw(busy_up_thres);core_ctl_attr_rw(
busy_down_thres);core_ctl_attr_rw(task_thres);core_ctl_attr_rw(
nr_prev_assist_thresh);core_ctl_attr_ro(need_cpus);core_ctl_attr_ro(active_cpus)
;core_ctl_attr_ro(global_state);core_ctl_attr_rw(not_preferred);core_ctl_attr_rw
(enable);static struct attribute*default_attrs[]={&min_cpus.attr,&max_cpus.attr,
&offline_delay_ms.attr,&busy_up_thres.attr,&busy_down_thres.attr,&task_thres.
attr,&nr_prev_assist_thresh.attr,&enable.attr,&need_cpus.attr,&active_cpus.attr,
&global_state.attr,&not_preferred.attr,NULL};
#define WALTe67e7bc098(WALT041cb91678) container_of(WALT041cb91678, struct \
WALTd84195416f, kobj)
#define WALTc8af498370(WALT6268ff8549) container_of(WALT6268ff8549, struct \
core_ctl_attr, attr)
static ssize_t show(struct kobject*kobj,struct attribute*attr,char*
WALT33c5f8b4bc){struct WALTd84195416f*WALTf8791a57cc=WALTe67e7bc098(kobj);struct
 core_ctl_attr*WALT9514acbabb=WALTc8af498370(attr);ssize_t WALT083920bcc8=-EIO;
if(WALT9514acbabb->show)WALT083920bcc8=WALT9514acbabb->show(WALTf8791a57cc,
WALT33c5f8b4bc);return WALT083920bcc8;}static ssize_t store(struct kobject*kobj,
struct attribute*attr,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){struct 
WALTd84195416f*WALTf8791a57cc=WALTe67e7bc098(kobj);struct core_ctl_attr*
WALT9514acbabb=WALTc8af498370(attr);ssize_t WALT083920bcc8=-EIO;if(
WALT9514acbabb->store)WALT083920bcc8=WALT9514acbabb->store(WALTf8791a57cc,
WALT33c5f8b4bc,WALT33ea1b60d7);return WALT083920bcc8;}static const struct 
sysfs_ops sysfs_ops={.show=show,.store=store,};static struct kobj_type 
WALTe314eed4f2={.sysfs_ops=&sysfs_ops,.default_attrs=default_attrs,};static 
struct sched_avg_stats WALT3d55024438[NR_CPUS];static int WALT586cb87856(int 
WALT6b2e94bfe7){int WALT8f9ab72eb9;struct WALTd84195416f*WALT1b752e214a;int 
WALT7cdf3ec737=(0x216+2615-0xc4d);WALT213747575e(WALT1b752e214a,WALT6b2e94bfe7){
for_each_cpu(WALT8f9ab72eb9,&WALT1b752e214a->WALT39abd1de52)WALT7cdf3ec737+=
WALT3d55024438[WALT8f9ab72eb9].nr;}return WALT7cdf3ec737;}static int 
WALT91003ac218(int WALT6b2e94bfe7){int WALT8f9ab72eb9;struct WALTd84195416f*
WALT79d47a94b2;int WALT33128046d7=(0x803+1989-0xfc8);if(WALT6b2e94bfe7==
(0xf16+1074-0x1348))return(0x1674+2714-0x210e);WALT79d47a94b2=&WALT9a7bdf60eb[
WALT6b2e94bfe7-(0x622+7608-0x23d9)];for_each_cpu(WALT8f9ab72eb9,&WALT79d47a94b2
->WALT39abd1de52)WALT33128046d7+=WALT3d55024438[WALT8f9ab72eb9].nr_misfit;return
 WALT33128046d7;}static int WALT4e9e6ae627(int WALT6b2e94bfe7){int 
WALT8f9ab72eb9;struct WALTd84195416f*WALT1b752e214a=&WALT9a7bdf60eb[
WALT6b2e94bfe7];int WALTf368d5dcae=(0x12b1+2283-0x1b9c);for_each_cpu(
WALT8f9ab72eb9,&WALT1b752e214a->WALT39abd1de52)WALTf368d5dcae=max(WALTf368d5dcae
,WALT3d55024438[WALT8f9ab72eb9].nr_max);return WALTf368d5dcae;}static int 
WALT9385e48bfe(int WALT6b2e94bfe7){int nr_big=(0x45+7914-0x1f2f);int 
WALT8f9ab72eb9;struct WALTd84195416f*WALT1b752e214a=&WALT9a7bdf60eb[
WALT6b2e94bfe7];if(WALT6b2e94bfe7==(0x968+2732-0x1414)){for_each_cpu(
WALT8f9ab72eb9,&WALT1b752e214a->WALT39abd1de52)nr_big+=WALT3d55024438[
WALT8f9ab72eb9].nr_misfit;}else{for_each_cpu(WALT8f9ab72eb9,&WALT1b752e214a->
WALT39abd1de52)nr_big+=WALT3d55024438[WALT8f9ab72eb9].nr;}return nr_big;}static 
int WALT4d8e98122d(int WALT6b2e94bfe7){int WALTf32c877095=(0x13b2+1521-0x19a3);
int WALT8f9ab72eb9;struct WALTd84195416f*WALT79d47a94b2;if(WALT6b2e94bfe7==
(0x1f59+37-0x1f7e))return(0x64d+4884-0x1961);WALT6b2e94bfe7--;WALT79d47a94b2=&
WALT9a7bdf60eb[WALT6b2e94bfe7];if(WALT79d47a94b2->WALTd76a53732a)return
(0x251b+178-0x25cd);for_each_cpu(WALT8f9ab72eb9,&WALT79d47a94b2->WALT39abd1de52)
WALTf32c877095+=WALT3d55024438[WALT8f9ab72eb9].nr;WALTf32c877095+=WALT91003ac218
(WALT6b2e94bfe7);if(WALTf32c877095>WALT79d47a94b2->active_cpus)WALTf32c877095=
WALTf32c877095-WALT79d47a94b2->active_cpus;else WALTf32c877095=
(0x18bf+1120-0x1d1f);return WALTf32c877095;}static int WALTf3336414f3(int 
WALT6b2e94bfe7){int WALT8f9ab72eb9;struct WALTd84195416f*WALT1b752e214a;int 
WALT49c28541b7=(0x131f+5044-0x26d3);if(WALT6b2e94bfe7!=(0x1904+2887-0x244b))
return(0x71d+1371-0xc78);WALT213747575e(WALT1b752e214a,WALT6b2e94bfe7){int 
nr_scaled=(0xb2c+3722-0x19b6);int active_cpus=WALT1b752e214a->active_cpus;
for_each_cpu(WALT8f9ab72eb9,&WALT1b752e214a->WALT39abd1de52)nr_scaled+=
WALT3d55024438[WALT8f9ab72eb9].nr_scaled;nr_scaled/=(0x306+3958-0x1218);if(
WALT6b2e94bfe7==(0x3a+5451-0x1585))WALT49c28541b7+=nr_scaled;else WALT49c28541b7
+=max((0x67c+8062-0x25fa),nr_scaled-active_cpus);}return WALT49c28541b7;}static 
void WALT595408d471(void){struct WALTd84195416f*WALT1b752e214a;unsigned int 
WALT6b2e94bfe7=(0x163+8471-0x227a);unsigned long WALT05b7c9a580;int 
WALTd8515de889=(0x23d+2384-0xb8d);sched_get_nr_running_avg(WALT3d55024438);
spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);WALT213747575e(WALT1b752e214a,
WALT6b2e94bfe7){int WALT7cdf3ec737,WALT33128046d7;if(!WALT1b752e214a->
WALTb6181247c7)continue;WALT7cdf3ec737=WALT586cb87856(WALT6b2e94bfe7);
WALT33128046d7=WALT91003ac218(WALT6b2e94bfe7);WALT1b752e214a->WALT78602fc8a3=
WALT7cdf3ec737+WALT33128046d7;WALT1b752e214a->WALTf368d5dcae=WALT4e9e6ae627(
WALT6b2e94bfe7);WALT1b752e214a->WALT263a14abab=WALT4d8e98122d(WALT6b2e94bfe7);
WALT1b752e214a->WALTcc9821f091=WALTf3336414f3(WALT6b2e94bfe7);
trace_core_ctl_update_nr_need(WALT1b752e214a->WALT76f375774d,WALT7cdf3ec737,
WALT33128046d7,WALT1b752e214a->WALT78602fc8a3,WALT1b752e214a->WALTf368d5dcae,
WALT1b752e214a->WALT263a14abab);WALTd8515de889+=WALT9385e48bfe(WALT6b2e94bfe7);}
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);WALT86ffcc7dfd=
WALTd8515de889;walt_rotation_checkpoint(WALTd8515de889);}
#define WALTc2db0febb0	(0x1f3+4302-0x12bd)
static unsigned int WALT50b207ad6d(const struct WALTd84195416f*WALT1b752e214a,
unsigned int WALTeadf56a7a3){if(WALT1b752e214a->WALT78602fc8a3>=WALT1b752e214a->
task_thres)return WALT1b752e214a->WALT3fc386a32e;if(WALT1b752e214a->
WALT263a14abab>=WALT1b752e214a->nr_prev_assist_thresh)WALTeadf56a7a3=
WALTeadf56a7a3+WALT1b752e214a->WALT263a14abab;if(WALT1b752e214a->WALT78602fc8a3>
WALTeadf56a7a3)WALTeadf56a7a3=WALTeadf56a7a3+(0x1863+1999-0x2031);if(
WALT1b752e214a->WALTf368d5dcae>WALTc2db0febb0)WALTeadf56a7a3=WALTeadf56a7a3+
(0x180+19-0x192);if(WALTeadf56a7a3<WALT1b752e214a->WALTcc9821f091)WALTeadf56a7a3
=WALT1b752e214a->WALTcc9821f091;return WALTeadf56a7a3;}static unsigned int 
WALTa16d868f28(const struct WALTd84195416f*WALT1b752e214a,unsigned int need_cpus
){return min(max(WALT1b752e214a->min_cpus,need_cpus),WALT1b752e214a->max_cpus);}
static unsigned int WALTbc04b417fa(const struct WALTd84195416f*WALT1b752e214a){
return WALT1b752e214a->WALT3fc386a32e-sched_isolate_count(&WALT1b752e214a->
WALT39abd1de52,true);}static bool WALT375fa7adc6(const struct WALT722543f60e*
WALT048da5e00c){return cpu_online(WALT048da5e00c->WALT8f9ab72eb9)&&!cpu_isolated
(WALT048da5e00c->WALT8f9ab72eb9);}static bool WALT05c5275688(const struct 
WALTd84195416f*WALT1b752e214a,unsigned int WALTf32c877095){return(WALTf32c877095
<WALT1b752e214a->active_cpus||(WALTf32c877095>WALT1b752e214a->active_cpus&&
WALT1b752e214a->WALTd76a53732a));}static bool WALTf6692437dc(const struct 
WALTd84195416f*WALT1b752e214a){return(is_min_capacity_cpu(WALT1b752e214a->
WALT76f375774d)&&sched_ravg_window<DEFAULT_SCHED_RAVG_WINDOW);}static bool 
eval_need(struct WALTd84195416f*WALT1b752e214a){unsigned long WALT05b7c9a580;
struct WALT722543f60e*WALTe2cca49edf;unsigned int need_cpus=(0x4fb+5626-0x1af5),
WALTefe45c244d,WALT8255d868d2;int WALT083920bcc8=(0x13f8+4657-0x2629);bool 
WALT11e2990555=false;unsigned int WALTeadf56a7a3;s64 WALT2c53bb3f34,
WALTcc63e644e4;if(unlikely(!WALT1b752e214a->WALTb6181247c7))return
(0x832+2620-0x126e);spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);if(
WALT1b752e214a->boost||!WALT1b752e214a->enable||WALTf6692437dc(WALT1b752e214a)){
need_cpus=WALT1b752e214a->max_cpus;}else{WALT1b752e214a->active_cpus=
WALTbc04b417fa(WALT1b752e214a);WALT8255d868d2=WALT1b752e214a->active_cpus?
WALT1b752e214a->active_cpus-(0x56+7153-0x1c46):(0x148+164-0x1ec);
list_for_each_entry(WALTe2cca49edf,&WALT1b752e214a->WALT895ecc2391,
WALTa7f3b2896c){bool WALT28dac86562=WALTe2cca49edf->WALT087db4d18a;if(
WALTe2cca49edf->WALT517f9bdd84>=WALT1b752e214a->busy_up_thres[WALT8255d868d2]||
sched_cpu_high_irqload(WALTe2cca49edf->WALT8f9ab72eb9))WALTe2cca49edf->
WALT087db4d18a=true;else if(WALTe2cca49edf->WALT517f9bdd84<WALT1b752e214a->
busy_down_thres[WALT8255d868d2])WALTe2cca49edf->WALT087db4d18a=false;
trace_core_ctl_set_busy(WALTe2cca49edf->WALT8f9ab72eb9,WALTe2cca49edf->
WALT517f9bdd84,WALT28dac86562,WALTe2cca49edf->WALT087db4d18a);need_cpus+=
WALTe2cca49edf->WALT087db4d18a;}need_cpus=WALT50b207ad6d(WALT1b752e214a,
need_cpus);}WALTeadf56a7a3=WALTa16d868f28(WALT1b752e214a,need_cpus);
WALT11e2990555=WALT05c5275688(WALT1b752e214a,WALTeadf56a7a3);WALTefe45c244d=
WALT1b752e214a->need_cpus;WALT2c53bb3f34=ktime_to_ms(ktime_get());if(
WALTeadf56a7a3>WALT1b752e214a->active_cpus){WALT083920bcc8=(0x1d9+1601-0x819);}
else{if(WALTeadf56a7a3==WALTefe45c244d&&WALTeadf56a7a3==WALT1b752e214a->
active_cpus){WALT1b752e214a->WALT474287bcf5=WALT2c53bb3f34;
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);return
(0x1de9+2312-0x26f1);}WALTcc63e644e4=WALT2c53bb3f34-WALT1b752e214a->
WALT474287bcf5;WALT083920bcc8=WALTcc63e644e4>=WALT1b752e214a->offline_delay_ms;}
if(WALT083920bcc8){WALT1b752e214a->WALT474287bcf5=WALT2c53bb3f34;WALT1b752e214a
->need_cpus=WALTeadf56a7a3;}trace_core_ctl_eval_need(WALT1b752e214a->
WALT76f375774d,WALTefe45c244d,WALTeadf56a7a3,WALT083920bcc8&&WALT11e2990555);
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);return WALT083920bcc8&&
WALT11e2990555;}static void WALT041d9949cf(struct WALTd84195416f*WALT1b752e214a)
{if(eval_need(WALT1b752e214a))WALTe68f5dd857(WALT1b752e214a);}static void 
WALTe68f5dd857(struct WALTd84195416f*WALT1b752e214a){unsigned long 
WALT05b7c9a580;spin_lock_irqsave(&WALT1b752e214a->WALTffb20e4808,WALT05b7c9a580)
;WALT1b752e214a->WALTa280f52f04=true;spin_unlock_irqrestore(&WALT1b752e214a->
WALTffb20e4808,WALT05b7c9a580);wake_up_process(WALT1b752e214a->WALT2e935f34a1);}
static u64 WALTdfa13d72c3;int core_ctl_set_boost(bool boost){unsigned int 
WALT6b2e94bfe7=(0x829+4690-0x1a7b);struct WALTd84195416f*WALT1b752e214a;unsigned
 long WALT05b7c9a580;int WALT083920bcc8=(0x743+3474-0x14d5);bool WALT37066d5eec=
false;if(unlikely(!WALT69be84bb38))return(0xb7+5015-0x144e);spin_lock_irqsave(&
WALT78e2cdac9a,WALT05b7c9a580);WALT213747575e(WALT1b752e214a,WALT6b2e94bfe7){if(
boost){WALT37066d5eec=!WALT1b752e214a->boost;++WALT1b752e214a->boost;}else{if(!
WALT1b752e214a->boost){WALT083920bcc8=-EINVAL;break;}else{--WALT1b752e214a->
boost;WALT37066d5eec=!WALT1b752e214a->boost;}}}spin_unlock_irqrestore(&
WALT78e2cdac9a,WALT05b7c9a580);if(WALT37066d5eec){WALT6b2e94bfe7=
(0x2c0+7716-0x20e4);WALT213747575e(WALT1b752e214a,WALT6b2e94bfe7)WALT041d9949cf(
WALT1b752e214a);}trace_core_ctl_set_boost(WALT1b752e214a->boost,WALT083920bcc8);
return WALT083920bcc8;}EXPORT_SYMBOL(core_ctl_set_boost);void 
core_ctl_notifier_register(struct notifier_block*WALTfe5c53f6bd){
atomic_notifier_chain_register(&WALTe24f5fc06e,WALTfe5c53f6bd);}void 
core_ctl_notifier_unregister(struct notifier_block*WALTfe5c53f6bd){
atomic_notifier_chain_unregister(&WALTe24f5fc06e,WALTfe5c53f6bd);}static void 
WALT521764ce34(void){struct core_ctl_notif_data WALT89bf9aac81={
(0x3b0+1344-0x8f0)};struct notifier_block*WALT9e976b309a;rcu_read_lock();
WALT9e976b309a=rcu_dereference_raw(WALTe24f5fc06e.head);rcu_read_unlock();if(!
WALT9e976b309a)return;WALT89bf9aac81.nr_big=WALT86ffcc7dfd;walt_fill_ta_data(&
WALT89bf9aac81);trace_core_ctl_notif_data(WALT89bf9aac81.nr_big,WALT89bf9aac81.
coloc_load_pct,WALT89bf9aac81.ta_util_pct,WALT89bf9aac81.cur_cap_pct);
atomic_notifier_call_chain(&WALTe24f5fc06e,(0x150b+4151-0x2542),&WALT89bf9aac81)
;}void core_ctl_check(u64 WALTd872303760){int WALT8f9ab72eb9;struct 
WALT722543f60e*WALTe2cca49edf;struct WALTd84195416f*WALT1b752e214a;unsigned int 
WALT6b2e94bfe7=(0x1361+372-0x14d5);unsigned long WALT05b7c9a580;if(unlikely(!
WALT69be84bb38))return;if(WALTd872303760==WALTdfa13d72c3)return;WALTdfa13d72c3=
WALTd872303760;spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);
for_each_possible_cpu(WALT8f9ab72eb9){WALTe2cca49edf=&per_cpu(WALT22ef1845d7,
WALT8f9ab72eb9);WALT1b752e214a=WALTe2cca49edf->WALT1b752e214a;if(!WALT1b752e214a
||!WALT1b752e214a->WALTb6181247c7)continue;WALTe2cca49edf->WALT517f9bdd84=
sched_get_cpu_util(WALT8f9ab72eb9);}spin_unlock_irqrestore(&WALT78e2cdac9a,
WALT05b7c9a580);WALT595408d471();WALT213747575e(WALT1b752e214a,WALT6b2e94bfe7){
if(eval_need(WALT1b752e214a))WALTe68f5dd857(WALT1b752e214a);}WALT521764ce34();}
static void WALT7e643441e5(struct WALT722543f60e*WALT722543f60e){unsigned long 
WALT05b7c9a580;spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);list_del(&
WALT722543f60e->WALTa7f3b2896c);list_add_tail(&WALT722543f60e->WALTa7f3b2896c,&
WALT722543f60e->WALT1b752e214a->WALT895ecc2391);spin_unlock_irqrestore(&
WALT78e2cdac9a,WALT05b7c9a580);}static bool WALT25bcd77821(int WALT8f9ab72eb9,
struct WALTd84195416f*WALT1b752e214a){return true;}static void WALTb426628abe(
struct WALTd84195416f*WALT1b752e214a,unsigned int WALTf32c877095){struct 
WALT722543f60e*WALTe2cca49edf,*WALTb9b0dca770;unsigned long WALT05b7c9a580;
unsigned int WALT3fc386a32e=WALT1b752e214a->WALT3fc386a32e;unsigned int 
WALT3407f2d0ae=(0x1c7+152-0x25f);bool WALT23fe99670b=WALT1b752e214a->
WALT9656065c1c;spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);
list_for_each_entry_safe(WALTe2cca49edf,WALTb9b0dca770,&WALT1b752e214a->
WALT895ecc2391,WALTa7f3b2896c){if(!WALT3fc386a32e--)break;if(!WALT375fa7adc6(
WALTe2cca49edf))continue;if(WALT1b752e214a->active_cpus==WALTf32c877095)break;if
(WALTe2cca49edf->WALT087db4d18a)continue;if(WALT1b752e214a->WALT9656065c1c&&!
WALTe2cca49edf->not_preferred)continue;if(!WALT25bcd77821(WALTe2cca49edf->
WALT8f9ab72eb9,WALT1b752e214a))continue;spin_unlock_irqrestore(&WALT78e2cdac9a,
WALT05b7c9a580);pr_debug(
"\x54\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,WALTe2cca49edf->WALT8f9ab72eb9);if(!sched_isolate_cpu(WALTe2cca49edf->
WALT8f9ab72eb9)){WALTe2cca49edf->WALT7f508cb38b=true;WALT7e643441e5(
WALTe2cca49edf);WALT3407f2d0ae++;}else{pr_debug(
"\x55\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,WALTe2cca49edf->WALT8f9ab72eb9);}WALT1b752e214a->active_cpus=WALTbc04b417fa(
WALT1b752e214a);spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);}
WALT1b752e214a->WALTd76a53732a+=WALT3407f2d0ae;spin_unlock_irqrestore(&
WALT78e2cdac9a,WALT05b7c9a580);WALTcd588e3717:if(WALT1b752e214a->active_cpus<=
WALT1b752e214a->max_cpus)return;WALT3407f2d0ae=(0x302+583-0x549);WALT3fc386a32e=
WALT1b752e214a->WALT3fc386a32e;spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580)
;list_for_each_entry_safe(WALTe2cca49edf,WALTb9b0dca770,&WALT1b752e214a->
WALT895ecc2391,WALTa7f3b2896c){if(!WALT3fc386a32e--)break;if(!WALT375fa7adc6(
WALTe2cca49edf))continue;if(WALT1b752e214a->active_cpus<=WALT1b752e214a->
max_cpus)break;if(WALT23fe99670b&&!WALTe2cca49edf->not_preferred)continue;
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);pr_debug(
"\x54\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,WALTe2cca49edf->WALT8f9ab72eb9);if(!sched_isolate_cpu(WALTe2cca49edf->
WALT8f9ab72eb9)){WALTe2cca49edf->WALT7f508cb38b=true;WALT7e643441e5(
WALTe2cca49edf);WALT3407f2d0ae++;}else{pr_debug(
"\x55\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,WALTe2cca49edf->WALT8f9ab72eb9);}WALT1b752e214a->active_cpus=WALTbc04b417fa(
WALT1b752e214a);spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);}
WALT1b752e214a->WALTd76a53732a+=WALT3407f2d0ae;spin_unlock_irqrestore(&
WALT78e2cdac9a,WALT05b7c9a580);if(WALT23fe99670b&&WALT1b752e214a->active_cpus>
WALT1b752e214a->max_cpus){WALT23fe99670b=false;goto WALTcd588e3717;}}static void
 WALT8d759fe75f(struct WALTd84195416f*WALT1b752e214a,unsigned int WALTf32c877095
,bool WALT16510eae6d){struct WALT722543f60e*WALTe2cca49edf,*WALTb9b0dca770;
unsigned long WALT05b7c9a580;unsigned int WALT3fc386a32e=WALT1b752e214a->
WALT3fc386a32e;unsigned int WALTa857c3409b=(0xb77+2364-0x14b3);spin_lock_irqsave
(&WALT78e2cdac9a,WALT05b7c9a580);list_for_each_entry_safe(WALTe2cca49edf,
WALTb9b0dca770,&WALT1b752e214a->WALT895ecc2391,WALTa7f3b2896c){if(!
WALT3fc386a32e--)break;if(!WALTe2cca49edf->WALT7f508cb38b)continue;if((
cpu_online(WALTe2cca49edf->WALT8f9ab72eb9)&&!cpu_isolated(WALTe2cca49edf->
WALT8f9ab72eb9))||(!WALT16510eae6d&&WALTe2cca49edf->not_preferred))continue;if(
WALT1b752e214a->active_cpus==WALTf32c877095)break;spin_unlock_irqrestore(&
WALT78e2cdac9a,WALT05b7c9a580);pr_debug(
"\x54\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x75\x6e\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,WALTe2cca49edf->WALT8f9ab72eb9);if(!sched_unisolate_cpu(WALTe2cca49edf->
WALT8f9ab72eb9)){WALTe2cca49edf->WALT7f508cb38b=false;WALT7e643441e5(
WALTe2cca49edf);WALTa857c3409b++;}else{pr_debug(
"\x55\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x75\x6e\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,WALTe2cca49edf->WALT8f9ab72eb9);}WALT1b752e214a->active_cpus=WALTbc04b417fa(
WALT1b752e214a);spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);}
WALT1b752e214a->WALTd76a53732a-=WALTa857c3409b;spin_unlock_irqrestore(&
WALT78e2cdac9a,WALT05b7c9a580);}static void WALT06ff7ad6cf(struct WALTd84195416f
*WALT1b752e214a,unsigned int WALTf32c877095){bool WALT02ab9de09c=false;
WALT8d759fe75f(WALT1b752e214a,WALTf32c877095,WALT02ab9de09c);if(WALT1b752e214a->
active_cpus==WALTf32c877095)return;WALT02ab9de09c=true;WALT8d759fe75f(
WALT1b752e214a,WALTf32c877095,WALT02ab9de09c);}static void __ref WALT5b4f389aad(
struct WALTd84195416f*WALT1b752e214a){unsigned int WALTf32c877095;WALTf32c877095
=WALTa16d868f28(WALT1b752e214a,WALT1b752e214a->need_cpus);if(WALT05c5275688(
WALT1b752e214a,WALTf32c877095)){pr_debug(
"\x54\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x61\x64\x6a\x75\x73\x74\x20\x67\x72\x6f\x75\x70\x20\x25\x75\x20\x66\x72\x6f\x6d\x20\x25\x75\x20\x74\x6f\x20\x25\x75" "\n"
,WALT1b752e214a->WALT76f375774d,WALT1b752e214a->active_cpus,WALTf32c877095);if(
WALT1b752e214a->active_cpus>WALTf32c877095)WALTb426628abe(WALT1b752e214a,
WALTf32c877095);else if(WALT1b752e214a->active_cpus<WALTf32c877095)
WALT06ff7ad6cf(WALT1b752e214a,WALTf32c877095);}}static int __ref WALTcc8e90311b(
void*WALTf8791a57cc){struct WALTd84195416f*WALT1b752e214a=WALTf8791a57cc;
unsigned long WALT05b7c9a580;while((0x702+3939-0x1664)){set_current_state(
TASK_INTERRUPTIBLE);spin_lock_irqsave(&WALT1b752e214a->WALTffb20e4808,
WALT05b7c9a580);if(!WALT1b752e214a->WALTa280f52f04){spin_unlock_irqrestore(&
WALT1b752e214a->WALTffb20e4808,WALT05b7c9a580);schedule();if(kthread_should_stop
())break;spin_lock_irqsave(&WALT1b752e214a->WALTffb20e4808,WALT05b7c9a580);}
set_current_state(TASK_RUNNING);WALT1b752e214a->WALTa280f52f04=false;
spin_unlock_irqrestore(&WALT1b752e214a->WALTffb20e4808,WALT05b7c9a580);
WALT5b4f389aad(WALT1b752e214a);}return(0x86b+7050-0x23f5);}static int 
WALT7641504060(unsigned int WALT8f9ab72eb9,bool WALTf62b956761){struct 
WALT722543f60e*WALT048da5e00c=&per_cpu(WALT22ef1845d7,WALT8f9ab72eb9);struct 
WALTd84195416f*WALT1b752e214a=WALT048da5e00c->WALT1b752e214a;unsigned int 
WALTf32c877095;bool WALTc7196d407f=false,WALTfbe01eaa1f=false;unsigned long 
WALT05b7c9a580;if(unlikely(!WALT1b752e214a||!WALT1b752e214a->WALTb6181247c7))
return(0x291+6886-0x1d77);if(WALTf62b956761){WALT1b752e214a->active_cpus=
WALTbc04b417fa(WALT1b752e214a);WALT7e643441e5(WALT048da5e00c);}else{if(
WALT048da5e00c->WALT7f508cb38b){sched_unisolate_cpu_unlocked(WALT8f9ab72eb9);
WALT048da5e00c->WALT7f508cb38b=false;WALTfbe01eaa1f=true;}WALT7e643441e5(
WALT048da5e00c);WALT048da5e00c->WALT517f9bdd84=(0x1279+2697-0x1d02);
WALT1b752e214a->active_cpus=WALTbc04b417fa(WALT1b752e214a);}WALTf32c877095=
WALTa16d868f28(WALT1b752e214a,WALT1b752e214a->need_cpus);spin_lock_irqsave(&
WALT78e2cdac9a,WALT05b7c9a580);if(WALTfbe01eaa1f)WALT1b752e214a->WALTd76a53732a
--;WALTc7196d407f=WALT05c5275688(WALT1b752e214a,WALTf32c877095);
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);if(WALTc7196d407f)
WALTe68f5dd857(WALT1b752e214a);return(0x977+6387-0x226a);}static int 
WALT32859df63c(unsigned int WALT8f9ab72eb9){return WALT7641504060(WALT8f9ab72eb9
,true);}static int WALT182ef3e766(unsigned int WALT8f9ab72eb9){return 
WALT7641504060(WALT8f9ab72eb9,false);}static struct WALTd84195416f*
WALTd5d0009aa2(unsigned int WALT76f375774d){unsigned int WALT5d971be8b8;for(
WALT5d971be8b8=(0x1712+4065-0x26f3);WALT5d971be8b8<WALT3480a8e71f;++
WALT5d971be8b8){if(WALT9a7bdf60eb[WALT5d971be8b8].WALT76f375774d==WALT76f375774d
)return&WALT9a7bdf60eb[WALT5d971be8b8];}return NULL;}static int WALTfec3515cc6(
const struct cpumask*WALTdf9caaa1ec){struct device*WALTf018520c69;unsigned int 
WALT76f375774d=cpumask_first(WALTdf9caaa1ec);struct WALTd84195416f*
WALT1b752e214a;struct WALT722543f60e*WALT048da5e00c;unsigned int WALT8f9ab72eb9;
struct sched_param WALT88d2ec5be5={.sched_priority=MAX_RT_PRIO-
(0x93f+4655-0x1b6d)};if(WALTd5d0009aa2(WALT76f375774d))return(0xca6+5066-0x2070)
;WALTf018520c69=get_cpu_device(WALT76f375774d);if(!WALTf018520c69)return-ENODEV;
pr_info(
"\x43\x72\x65\x61\x74\x69\x6e\x67\x20\x43\x50\x55\x20\x67\x72\x6f\x75\x70\x20\x25\x64" "\n"
,WALT76f375774d);if(WALT3480a8e71f==MAX_CLUSTERS){pr_err(
"\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x63\x6c\x75\x73\x74\x65\x72\x73\x2e\x20\x4f\x6e\x6c\x79\x20\x25\x75\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64" "\n"
,MAX_CLUSTERS);return-EINVAL;}WALT1b752e214a=&WALT9a7bdf60eb[WALT3480a8e71f];++
WALT3480a8e71f;cpumask_copy(&WALT1b752e214a->WALT39abd1de52,WALTdf9caaa1ec);
WALT1b752e214a->WALT3fc386a32e=cpumask_weight(WALTdf9caaa1ec);if(WALT1b752e214a
->WALT3fc386a32e>MAX_CPUS_PER_CLUSTER){pr_err(
"\x48\x57\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69\x6f\x6e\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64" "\n"
);return-EINVAL;}WALT1b752e214a->WALT76f375774d=WALT76f375774d;WALT1b752e214a->
min_cpus=(0xf77+2318-0x1884);WALT1b752e214a->max_cpus=WALT1b752e214a->
WALT3fc386a32e;WALT1b752e214a->need_cpus=WALT1b752e214a->WALT3fc386a32e;
WALT1b752e214a->offline_delay_ms=(0x960+2311-0x1203);WALT1b752e214a->task_thres=
UINT_MAX;WALT1b752e214a->nr_prev_assist_thresh=UINT_MAX;WALT1b752e214a->
WALT78602fc8a3=WALT1b752e214a->WALT3fc386a32e;WALT1b752e214a->enable=true;
WALT1b752e214a->WALT9656065c1c=(0x6c8+4573-0x18a5);WALT1b752e214a->
WALTcc9821f091=(0xb64+5253-0x1fe9);INIT_LIST_HEAD(&WALT1b752e214a->
WALT895ecc2391);spin_lock_init(&WALT1b752e214a->WALTffb20e4808);for_each_cpu(
WALT8f9ab72eb9,WALTdf9caaa1ec){pr_info(
"\x49\x6e\x69\x74\x20\x43\x50\x55\x25\x75\x20\x73\x74\x61\x74\x65" "\n",
WALT8f9ab72eb9);WALT048da5e00c=&per_cpu(WALT22ef1845d7,WALT8f9ab72eb9);
WALT048da5e00c->WALT1b752e214a=WALT1b752e214a;WALT048da5e00c->WALT8f9ab72eb9=
WALT8f9ab72eb9;list_add_tail(&WALT048da5e00c->WALTa7f3b2896c,&WALT1b752e214a->
WALT895ecc2391);}WALT1b752e214a->active_cpus=WALTbc04b417fa(WALT1b752e214a);
WALT1b752e214a->WALT2e935f34a1=kthread_run(WALTcc8e90311b,(void*)WALT1b752e214a,
"\x63\x6f\x72\x65\x5f\x63\x74\x6c\x2f\x25\x64",WALT76f375774d);if(IS_ERR(
WALT1b752e214a->WALT2e935f34a1))return PTR_ERR(WALT1b752e214a->WALT2e935f34a1);
sched_setscheduler_nocheck(WALT1b752e214a->WALT2e935f34a1,SCHED_FIFO,&
WALT88d2ec5be5);WALT1b752e214a->WALTb6181247c7=true;kobject_init(&WALT1b752e214a
->kobj,&WALTe314eed4f2);return kobject_add(&WALT1b752e214a->kobj,&WALTf018520c69
->kobj,"\x63\x6f\x72\x65\x5f\x63\x74\x6c");}static int __init core_ctl_init(void
){struct sched_cluster*WALT1b752e214a;int WALT083920bcc8;
cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
"\x63\x6f\x72\x65\x5f\x63\x74\x6c\x2f\x69\x73\x6f\x6c\x61\x74\x69\x6f\x6e\x3a\x6f\x6e\x6c\x69\x6e\x65"
,WALT32859df63c,NULL);cpuhp_setup_state_nocalls(CPUHP_CORE_CTL_ISOLATION_DEAD,
"\x63\x6f\x72\x65\x5f\x63\x74\x6c\x2f\x69\x73\x6f\x6c\x61\x74\x69\x6f\x6e\x3a\x64\x65\x61\x64"
,NULL,WALT182ef3e766);for_each_sched_cluster(WALT1b752e214a){WALT083920bcc8=
WALTfec3515cc6(&WALT1b752e214a->cpus);if(WALT083920bcc8)pr_warn(
"\x75\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x63\x72\x65\x61\x74\x65\x20\x63\x6f\x72\x65\x20\x63\x74\x6c\x20\x67\x72\x6f\x75\x70\x3a\x20\x25\x64" "\n"
,WALT083920bcc8);}WALT69be84bb38=true;return(0x6ed+6688-0x210d);}late_initcall(
core_ctl_init);
