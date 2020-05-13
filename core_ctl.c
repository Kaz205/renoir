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
	for ((WALT1b752e214a) = &WALT9a7bdf60eb[WALT8aa1674e1f]; (WALT8aa1674e1f) < \
WALT3480a8e71f;\
		(WALT8aa1674e1f)++, (WALT1b752e214a) = &WALT9a7bdf60eb[WALT8aa1674e1f])
static DEFINE_SPINLOCK(WALT78e2cdac9a);static void WALT041d9949cf(struct 
WALTd84195416f*WALT048da5e00c);static void WALTe68f5dd857(struct WALTd84195416f*
WALT048da5e00c);static bool WALT69be84bb38;ATOMIC_NOTIFIER_HEAD(WALTe24f5fc06e);
static unsigned int WALT86ffcc7dfd;static unsigned int WALTbc04b417fa(const 
struct WALTd84195416f*WALT1b752e214a);static ssize_t store_min_cpus(struct 
WALTd84195416f*WALT048da5e00c,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){
unsigned int WALTc94d3d8015;if(sscanf(WALT33c5f8b4bc,"\x25\x75" "\n",&
WALTc94d3d8015)!=(0x2da+6921-0x1de2))return-EINVAL;WALT048da5e00c->min_cpus=min(
WALTc94d3d8015,WALT048da5e00c->WALT3fc386a32e);WALTe68f5dd857(WALT048da5e00c);
return WALT33ea1b60d7;}static ssize_t show_min_cpus(const struct WALTd84195416f*
WALT048da5e00c,char*WALT33c5f8b4bc){return snprintf(WALT33c5f8b4bc,PAGE_SIZE,
"\x25\x75" "\n",WALT048da5e00c->min_cpus);}static ssize_t store_max_cpus(struct 
WALTd84195416f*WALT048da5e00c,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){
unsigned int WALTc94d3d8015;if(sscanf(WALT33c5f8b4bc,"\x25\x75" "\n",&
WALTc94d3d8015)!=(0xc43+3552-0x1a22))return-EINVAL;WALT048da5e00c->max_cpus=min(
WALTc94d3d8015,WALT048da5e00c->WALT3fc386a32e);WALTe68f5dd857(WALT048da5e00c);
return WALT33ea1b60d7;}static ssize_t show_max_cpus(const struct WALTd84195416f*
WALT048da5e00c,char*WALT33c5f8b4bc){return snprintf(WALT33c5f8b4bc,PAGE_SIZE,
"\x25\x75" "\n",WALT048da5e00c->max_cpus);}static ssize_t store_offline_delay_ms
(struct WALTd84195416f*WALT048da5e00c,const char*WALT33c5f8b4bc,size_t 
WALT33ea1b60d7){unsigned int WALTc94d3d8015;if(sscanf(WALT33c5f8b4bc,
"\x25\x75" "\n",&WALTc94d3d8015)!=(0x4ef+4388-0x1612))return-EINVAL;
WALT048da5e00c->offline_delay_ms=WALTc94d3d8015;WALT041d9949cf(WALT048da5e00c);
return WALT33ea1b60d7;}static ssize_t show_task_thres(const struct 
WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){return snprintf(
WALT33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",WALT048da5e00c->task_thres);}static 
ssize_t store_task_thres(struct WALTd84195416f*WALT048da5e00c,const char*
WALT33c5f8b4bc,size_t WALT33ea1b60d7){unsigned int WALTc94d3d8015;if(sscanf(
WALT33c5f8b4bc,"\x25\x75" "\n",&WALTc94d3d8015)!=(0x73d+5442-0x1c7e))return-
EINVAL;if(WALTc94d3d8015<WALT048da5e00c->WALT3fc386a32e)return-EINVAL;
WALT048da5e00c->task_thres=WALTc94d3d8015;WALT041d9949cf(WALT048da5e00c);return 
WALT33ea1b60d7;}static ssize_t show_nr_prev_assist_thresh(const struct 
WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){return snprintf(
WALT33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",WALT048da5e00c->nr_prev_assist_thresh);
}static ssize_t store_nr_prev_assist_thresh(struct WALTd84195416f*WALT048da5e00c
,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){unsigned int WALTc94d3d8015;if
(sscanf(WALT33c5f8b4bc,"\x25\x75" "\n",&WALTc94d3d8015)!=(0x316+4411-0x1450))
return-EINVAL;WALT048da5e00c->nr_prev_assist_thresh=WALTc94d3d8015;
WALT041d9949cf(WALT048da5e00c);return WALT33ea1b60d7;}static ssize_t 
show_offline_delay_ms(const struct WALTd84195416f*WALT048da5e00c,char*
WALT33c5f8b4bc){return snprintf(WALT33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",
WALT048da5e00c->offline_delay_ms);}static ssize_t store_busy_up_thres(struct 
WALTd84195416f*WALT048da5e00c,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){
unsigned int WALTc94d3d8015[MAX_CPUS_PER_CLUSTER];int WALT083920bcc8,
WALT5d971be8b8;WALT083920bcc8=sscanf(WALT33c5f8b4bc,
"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
WALTc94d3d8015[(0x1228+2336-0x1b48)],&WALTc94d3d8015[(0x1c6c+962-0x202d)],&
WALTc94d3d8015[(0x128c+1117-0x16e7)],&WALTc94d3d8015[(0x1278+1343-0x17b4)],&
WALTc94d3d8015[(0x10b8+584-0x12fc)],&WALTc94d3d8015[(0x11af+3880-0x20d2)]);if(
WALT083920bcc8!=(0x129c+941-0x1648)&&WALT083920bcc8!=WALT048da5e00c->
WALT3fc386a32e)return-EINVAL;if(WALT083920bcc8==(0xa7a+5898-0x2183)){for(
WALT5d971be8b8=(0x21cb+363-0x2336);WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e
;WALT5d971be8b8++)WALT048da5e00c->busy_up_thres[WALT5d971be8b8]=WALTc94d3d8015[
(0xa85+1264-0xf75)];}else{for(WALT5d971be8b8=(0xa2b+7144-0x2613);WALT5d971be8b8<
WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++)WALT048da5e00c->busy_up_thres[
WALT5d971be8b8]=WALTc94d3d8015[WALT5d971be8b8];}WALT041d9949cf(WALT048da5e00c);
return WALT33ea1b60d7;}static ssize_t show_busy_up_thres(const struct 
WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){int WALT5d971be8b8,
WALT33ea1b60d7=(0x197b+315-0x1ab6);for(WALT5d971be8b8=(0x204+9443-0x26e7);
WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++)WALT33ea1b60d7+=
snprintf(WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,"\x25\x75\x20",
WALT048da5e00c->busy_up_thres[WALT5d971be8b8]);WALT33ea1b60d7+=snprintf(
WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,"\n");return 
WALT33ea1b60d7;}static ssize_t store_busy_down_thres(struct WALTd84195416f*
WALT048da5e00c,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){unsigned int 
WALTc94d3d8015[MAX_CPUS_PER_CLUSTER];int WALT083920bcc8,WALT5d971be8b8;
WALT083920bcc8=sscanf(WALT33c5f8b4bc,
"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
WALTc94d3d8015[(0x4dd+617-0x746)],&WALTc94d3d8015[(0x1021+4302-0x20ee)],&
WALTc94d3d8015[(0x20c0+1322-0x25e8)],&WALTc94d3d8015[(0xdb2+2960-0x193f)],&
WALTc94d3d8015[(0x85c+5092-0x1c3c)],&WALTc94d3d8015[(0xf7+3740-0xf8e)]);if(
WALT083920bcc8!=(0xa15+5883-0x210f)&&WALT083920bcc8!=WALT048da5e00c->
WALT3fc386a32e)return-EINVAL;if(WALT083920bcc8==(0xe33+446-0xff0)){for(
WALT5d971be8b8=(0x1a46+923-0x1de1);WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e
;WALT5d971be8b8++)WALT048da5e00c->busy_down_thres[WALT5d971be8b8]=WALTc94d3d8015
[(0x804+5838-0x1ed2)];}else{for(WALT5d971be8b8=(0x13bc+4554-0x2586);
WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++)WALT048da5e00c->
busy_down_thres[WALT5d971be8b8]=WALTc94d3d8015[WALT5d971be8b8];}WALT041d9949cf(
WALT048da5e00c);return WALT33ea1b60d7;}static ssize_t show_busy_down_thres(const
 struct WALTd84195416f*WALT048da5e00c,char*WALT33c5f8b4bc){int WALT5d971be8b8,
WALT33ea1b60d7=(0xc96+4023-0x1c4d);for(WALT5d971be8b8=(0xf61+1524-0x1555);
WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++)WALT33ea1b60d7+=
snprintf(WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,"\x25\x75\x20",
WALT048da5e00c->busy_down_thres[WALT5d971be8b8]);WALT33ea1b60d7+=snprintf(
WALT33c5f8b4bc+WALT33ea1b60d7,PAGE_SIZE-WALT33ea1b60d7,"\n");return 
WALT33ea1b60d7;}static ssize_t store_enable(struct WALTd84195416f*WALT048da5e00c
,const char*WALT33c5f8b4bc,size_t WALT33ea1b60d7){unsigned int WALTc94d3d8015;
bool WALTd09cc5ef75;if(sscanf(WALT33c5f8b4bc,"\x25\x75" "\n",&WALTc94d3d8015)!=
(0x20b2+1199-0x2560))return-EINVAL;WALTd09cc5ef75=!!WALTc94d3d8015;if(
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
WALT1b752e214a;ssize_t WALT33ea1b60d7=(0x832+6901-0x2327);unsigned int 
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
(0x133d+3234-0x1fdf);WALT083920bcc8=sscanf(WALT33c5f8b4bc,
"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
WALTc94d3d8015[(0xfb1+2749-0x1a6e)],&WALTc94d3d8015[(0x12c5+4330-0x23ae)],&
WALTc94d3d8015[(0xc6+7989-0x1ff9)],&WALTc94d3d8015[(0x1790+2704-0x221d)],&
WALTc94d3d8015[(0x7d0+5894-0x1ed2)],&WALTc94d3d8015[(0x6e7+24-0x6fa)]);if(
WALT083920bcc8!=WALT048da5e00c->WALT3fc386a32e)return-EINVAL;spin_lock_irqsave(&
WALT78e2cdac9a,WALT05b7c9a580);for(WALT5d971be8b8=(0x1342+2560-0x1d42);
WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8++){WALTe2cca49edf=&
per_cpu(WALT22ef1845d7,WALT5d971be8b8+WALT048da5e00c->WALT76f375774d);
WALTe2cca49edf->not_preferred=WALTc94d3d8015[WALT5d971be8b8];WALT30bdc18e2b+=!!
WALTc94d3d8015[WALT5d971be8b8];}WALT048da5e00c->WALT9656065c1c=WALT30bdc18e2b;
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);return WALT33ea1b60d7;}
static ssize_t show_not_preferred(const struct WALTd84195416f*WALT048da5e00c,
char*WALT33c5f8b4bc){struct WALT722543f60e*WALTe2cca49edf;ssize_t WALT33ea1b60d7
=(0xb3+2351-0x9e2);unsigned long WALT05b7c9a580;int WALT5d971be8b8;
spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);for(WALT5d971be8b8=
(0xf56+3632-0x1d86);WALT5d971be8b8<WALT048da5e00c->WALT3fc386a32e;WALT5d971be8b8
++){WALTe2cca49edf=&per_cpu(WALT22ef1845d7,WALT5d971be8b8+WALT048da5e00c->
WALT76f375774d);WALT33ea1b60d7+=scnprintf(WALT33c5f8b4bc+WALT33ea1b60d7,
PAGE_SIZE-WALT33ea1b60d7,"\x43\x50\x55\x23\x25\x64\x3a\x20\x25\x75" "\n",
WALTe2cca49edf->WALT8f9ab72eb9,WALTe2cca49edf->not_preferred);}
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);return WALT33ea1b60d7;}
struct core_ctl_attr{struct attribute attr;ssize_t(*show)(const struct 
WALTd84195416f*,char*);ssize_t(*store)(struct WALTd84195416f*,const char*,size_t
 WALT33ea1b60d7);};
#define core_ctl_attr_ro(WALTb25dfb9431)		\
static struct core_ctl_attr WALTb25dfb9431 =	\
__ATTR(WALTb25dfb9431, (0x945+4555-0x19ec), show_##WALTb25dfb9431, NULL)
#define core_ctl_attr_rw(WALTb25dfb9431)			\
static struct core_ctl_attr WALTb25dfb9431 =		\
__ATTR(WALTb25dfb9431, (0xed2+2479-0x16dd), show_##WALTb25dfb9431, store_##\
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
WALT7cdf3ec737=(0x517+7517-0x2274);WALT213747575e(WALT1b752e214a,WALT6b2e94bfe7)
{for_each_cpu(WALT8f9ab72eb9,&WALT1b752e214a->WALT39abd1de52)WALT7cdf3ec737+=
WALT3d55024438[WALT8f9ab72eb9].nr;}return WALT7cdf3ec737;}static int 
WALT91003ac218(int WALT6b2e94bfe7){int WALT8f9ab72eb9;struct WALTd84195416f*
WALT79d47a94b2;int WALT33128046d7=(0x2f8+6607-0x1cc7);if(WALT6b2e94bfe7==
(0x137d+3962-0x22f7))return(0xdd8+5150-0x21f6);WALT79d47a94b2=&WALT9a7bdf60eb[
WALT6b2e94bfe7-(0xfbf+2069-0x17d3)];for_each_cpu(WALT8f9ab72eb9,&WALT79d47a94b2
->WALT39abd1de52)WALT33128046d7+=WALT3d55024438[WALT8f9ab72eb9].nr_misfit;return
 WALT33128046d7;}static int WALT4e9e6ae627(int WALT6b2e94bfe7){int 
WALT8f9ab72eb9;struct WALTd84195416f*WALT1b752e214a=&WALT9a7bdf60eb[
WALT6b2e94bfe7];int WALTf368d5dcae=(0x51+705-0x312);for_each_cpu(WALT8f9ab72eb9,
&WALT1b752e214a->WALT39abd1de52)WALTf368d5dcae=max(WALTf368d5dcae,WALT3d55024438
[WALT8f9ab72eb9].nr_max);return WALTf368d5dcae;}static int WALT9385e48bfe(int 
WALT6b2e94bfe7){int nr_big=(0x1c6+2037-0x9bb);int WALT8f9ab72eb9;struct 
WALTd84195416f*WALT1b752e214a=&WALT9a7bdf60eb[WALT6b2e94bfe7];if(WALT6b2e94bfe7
==(0x3eb+8617-0x2594)){for_each_cpu(WALT8f9ab72eb9,&WALT1b752e214a->
WALT39abd1de52)nr_big+=WALT3d55024438[WALT8f9ab72eb9].nr_misfit;}else{
for_each_cpu(WALT8f9ab72eb9,&WALT1b752e214a->WALT39abd1de52)nr_big+=
WALT3d55024438[WALT8f9ab72eb9].nr;}return nr_big;}static int WALT4d8e98122d(int 
WALT6b2e94bfe7){int WALTf32c877095=(0x18e2+2271-0x21c1);int WALT8f9ab72eb9;
struct WALTd84195416f*WALT79d47a94b2;if(WALT6b2e94bfe7==(0xd27+5911-0x243e))
return(0x683+429-0x830);WALT6b2e94bfe7--;WALT79d47a94b2=&WALT9a7bdf60eb[
WALT6b2e94bfe7];if(WALT79d47a94b2->WALTd76a53732a)return(0xb62+4614-0x1d68);
for_each_cpu(WALT8f9ab72eb9,&WALT79d47a94b2->WALT39abd1de52)WALTf32c877095+=
WALT3d55024438[WALT8f9ab72eb9].nr;WALTf32c877095+=WALT91003ac218(WALT6b2e94bfe7)
;if(WALTf32c877095>WALT79d47a94b2->active_cpus)WALTf32c877095=WALTf32c877095-
WALT79d47a94b2->active_cpus;else WALTf32c877095=(0xb50+1234-0x1022);return 
WALTf32c877095;}static int WALTf3336414f3(int WALT6b2e94bfe7){int WALT8f9ab72eb9
;struct WALTd84195416f*WALT1b752e214a;int WALT49c28541b7=(0x582+584-0x7ca);if(
WALT6b2e94bfe7!=(0x1ab1+409-0x1c4a))return(0x18bb+2934-0x2431);WALT213747575e(
WALT1b752e214a,WALT6b2e94bfe7){int nr_scaled=(0x42a+3665-0x127b);int active_cpus
=WALT1b752e214a->active_cpus;for_each_cpu(WALT8f9ab72eb9,&WALT1b752e214a->
WALT39abd1de52)nr_scaled+=WALT3d55024438[WALT8f9ab72eb9].nr_scaled;nr_scaled/=
(0x1056+1967-0x17a1);if(WALT6b2e94bfe7==(0x7a6+2245-0x106b))WALT49c28541b7+=
nr_scaled;else WALT49c28541b7+=max((0x4c9+567-0x700),nr_scaled-active_cpus);}
return WALT49c28541b7;}static void WALT595408d471(void){struct WALTd84195416f*
WALT1b752e214a;unsigned int WALT6b2e94bfe7=(0x1533+1877-0x1c88);unsigned long 
WALT05b7c9a580;int WALTd8515de889=(0x1523+3808-0x2403);sched_get_nr_running_avg(
WALT3d55024438);spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);WALT213747575e
(WALT1b752e214a,WALT6b2e94bfe7){int WALT7cdf3ec737,WALT33128046d7;if(!
WALT1b752e214a->WALTb6181247c7)continue;WALT7cdf3ec737=WALT586cb87856(
WALT6b2e94bfe7);WALT33128046d7=WALT91003ac218(WALT6b2e94bfe7);WALT1b752e214a->
WALT78602fc8a3=WALT7cdf3ec737+WALT33128046d7;WALT1b752e214a->WALTf368d5dcae=
WALT4e9e6ae627(WALT6b2e94bfe7);WALT1b752e214a->WALT263a14abab=WALT4d8e98122d(
WALT6b2e94bfe7);WALT1b752e214a->WALTcc9821f091=WALTf3336414f3(WALT6b2e94bfe7);
trace_core_ctl_update_nr_need(WALT1b752e214a->WALT76f375774d,WALT7cdf3ec737,
WALT33128046d7,WALT1b752e214a->WALT78602fc8a3,WALT1b752e214a->WALTf368d5dcae,
WALT1b752e214a->WALT263a14abab);WALTd8515de889+=WALT9385e48bfe(WALT6b2e94bfe7);}
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);WALT86ffcc7dfd=
WALTd8515de889;walt_rotation_checkpoint(WALTd8515de889);}
#define WALTc2db0febb0	(0xe09+4321-0x1ee6)
static unsigned int WALT50b207ad6d(const struct WALTd84195416f*WALT1b752e214a,
unsigned int WALTeadf56a7a3){if(WALT1b752e214a->WALT78602fc8a3>=WALT1b752e214a->
task_thres)return WALT1b752e214a->WALT3fc386a32e;if(WALT1b752e214a->
WALT263a14abab>=WALT1b752e214a->nr_prev_assist_thresh)WALTeadf56a7a3=
WALTeadf56a7a3+WALT1b752e214a->WALT263a14abab;if(WALT1b752e214a->WALT78602fc8a3>
WALTeadf56a7a3)WALTeadf56a7a3=WALTeadf56a7a3+(0x20a7+1212-0x2562);if(
WALT1b752e214a->WALTf368d5dcae>WALTc2db0febb0)WALTeadf56a7a3=WALTeadf56a7a3+
(0xe13+1874-0x1564);if(WALTeadf56a7a3<WALT1b752e214a->WALTcc9821f091)
WALTeadf56a7a3=WALT1b752e214a->WALTcc9821f091;return WALTeadf56a7a3;}static 
unsigned int WALTa16d868f28(const struct WALTd84195416f*WALT1b752e214a,unsigned 
int need_cpus){return min(max(WALT1b752e214a->min_cpus,need_cpus),WALT1b752e214a
->max_cpus);}static unsigned int WALTbc04b417fa(const struct WALTd84195416f*
WALT1b752e214a){return WALT1b752e214a->WALT3fc386a32e-sched_isolate_count(&
WALT1b752e214a->WALT39abd1de52,true);}static bool WALT375fa7adc6(const struct 
WALT722543f60e*WALT048da5e00c){return cpu_online(WALT048da5e00c->WALT8f9ab72eb9)
&&!cpu_isolated(WALT048da5e00c->WALT8f9ab72eb9);}static bool WALT05c5275688(
const struct WALTd84195416f*WALT1b752e214a,unsigned int WALTf32c877095){return(
WALTf32c877095<WALT1b752e214a->active_cpus||(WALTf32c877095>WALT1b752e214a->
active_cpus&&WALT1b752e214a->WALTd76a53732a));}static bool WALTf6692437dc(const 
struct WALTd84195416f*WALT1b752e214a){return(is_min_capacity_cpu(WALT1b752e214a
->WALT76f375774d)&&sched_ravg_window<DEFAULT_SCHED_RAVG_WINDOW);}static bool 
eval_need(struct WALTd84195416f*WALT1b752e214a){unsigned long WALT05b7c9a580;
struct WALT722543f60e*WALTe2cca49edf;unsigned int need_cpus=(0x16fb+1467-0x1cb6)
,WALTefe45c244d,WALT8255d868d2;int WALT083920bcc8=(0x1379+431-0x1528);bool 
WALT11e2990555=false;unsigned int WALTeadf56a7a3;s64 WALT2c53bb3f34,
WALTcc63e644e4;if(unlikely(!WALT1b752e214a->WALTb6181247c7))return
(0x128a+442-0x1444);spin_lock_irqsave(&WALT78e2cdac9a,WALT05b7c9a580);if(
WALT1b752e214a->boost||!WALT1b752e214a->enable||WALTf6692437dc(WALT1b752e214a)){
need_cpus=WALT1b752e214a->max_cpus;}else{WALT1b752e214a->active_cpus=
WALTbc04b417fa(WALT1b752e214a);WALT8255d868d2=WALT1b752e214a->active_cpus?
WALT1b752e214a->active_cpus-(0x12cd+4441-0x2425):(0x70+5896-0x1778);
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
WALTeadf56a7a3>WALT1b752e214a->active_cpus){WALT083920bcc8=(0x139a+2045-0x1b96);
}else{if(WALTeadf56a7a3==WALTefe45c244d&&WALTeadf56a7a3==WALT1b752e214a->
active_cpus){WALT1b752e214a->WALT474287bcf5=WALT2c53bb3f34;
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);return(0xd8f+4158-0x1dcd)
;}WALTcc63e644e4=WALT2c53bb3f34-WALT1b752e214a->WALT474287bcf5;WALT083920bcc8=
WALTcc63e644e4>=WALT1b752e214a->offline_delay_ms;}if(WALT083920bcc8){
WALT1b752e214a->WALT474287bcf5=WALT2c53bb3f34;WALT1b752e214a->need_cpus=
WALTeadf56a7a3;}trace_core_ctl_eval_need(WALT1b752e214a->WALT76f375774d,
WALTefe45c244d,WALTeadf56a7a3,WALT083920bcc8&&WALT11e2990555);
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);return WALT083920bcc8&&
WALT11e2990555;}static void WALT041d9949cf(struct WALTd84195416f*WALT1b752e214a)
{if(eval_need(WALT1b752e214a))WALTe68f5dd857(WALT1b752e214a);}static void 
WALTe68f5dd857(struct WALTd84195416f*WALT1b752e214a){unsigned long 
WALT05b7c9a580;spin_lock_irqsave(&WALT1b752e214a->WALTffb20e4808,WALT05b7c9a580)
;WALT1b752e214a->WALTa280f52f04=true;spin_unlock_irqrestore(&WALT1b752e214a->
WALTffb20e4808,WALT05b7c9a580);wake_up_process(WALT1b752e214a->WALT2e935f34a1);}
static u64 WALTdfa13d72c3;int core_ctl_set_boost(bool boost){unsigned int 
WALT6b2e94bfe7=(0x64+3437-0xdd1);struct WALTd84195416f*WALT1b752e214a;unsigned 
long WALT05b7c9a580;int WALT083920bcc8=(0x4ed+2437-0xe72);bool WALT37066d5eec=
false;if(unlikely(!WALT69be84bb38))return(0x64d+8369-0x26fe);spin_lock_irqsave(&
WALT78e2cdac9a,WALT05b7c9a580);WALT213747575e(WALT1b752e214a,WALT6b2e94bfe7){if(
boost){WALT37066d5eec=!WALT1b752e214a->boost;++WALT1b752e214a->boost;}else{if(!
WALT1b752e214a->boost){WALT083920bcc8=-EINVAL;break;}else{--WALT1b752e214a->
boost;WALT37066d5eec=!WALT1b752e214a->boost;}}}spin_unlock_irqrestore(&
WALT78e2cdac9a,WALT05b7c9a580);if(WALT37066d5eec){WALT6b2e94bfe7=
(0xe9d+5311-0x235c);WALT213747575e(WALT1b752e214a,WALT6b2e94bfe7)WALT041d9949cf(
WALT1b752e214a);}trace_core_ctl_set_boost(WALT1b752e214a->boost,WALT083920bcc8);
return WALT083920bcc8;}EXPORT_SYMBOL(core_ctl_set_boost);void 
core_ctl_notifier_register(struct notifier_block*WALTfe5c53f6bd){
atomic_notifier_chain_register(&WALTe24f5fc06e,WALTfe5c53f6bd);}void 
core_ctl_notifier_unregister(struct notifier_block*WALTfe5c53f6bd){
atomic_notifier_chain_unregister(&WALTe24f5fc06e,WALTfe5c53f6bd);}static void 
WALT521764ce34(void){struct core_ctl_notif_data WALT89bf9aac81={
(0x115c+3882-0x2086)};struct notifier_block*WALT9e976b309a;rcu_read_lock();
WALT9e976b309a=rcu_dereference_raw(WALTe24f5fc06e.head);rcu_read_unlock();if(!
WALT9e976b309a)return;WALT89bf9aac81.nr_big=WALT86ffcc7dfd;walt_fill_ta_data(&
WALT89bf9aac81);trace_core_ctl_notif_data(WALT89bf9aac81.nr_big,WALT89bf9aac81.
coloc_load_pct,WALT89bf9aac81.ta_util_pct,WALT89bf9aac81.cur_cap_pct);
atomic_notifier_call_chain(&WALTe24f5fc06e,(0x7d7+2173-0x1054),&WALT89bf9aac81);
}void core_ctl_check(u64 WALTd872303760){int WALT8f9ab72eb9;struct 
WALT722543f60e*WALTe2cca49edf;struct WALTd84195416f*WALT1b752e214a;unsigned int 
WALT6b2e94bfe7=(0xbb+8251-0x20f6);unsigned long WALT05b7c9a580;if(unlikely(!
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
WALT3407f2d0ae=(0x5a8+7973-0x24cd);bool WALT23fe99670b=WALT1b752e214a->
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
WALT1b752e214a->max_cpus)return;WALT3407f2d0ae=(0xb28+629-0xd9d);WALT3fc386a32e=
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
WALT3fc386a32e;unsigned int WALTa857c3409b=(0x1824+18-0x1836);spin_lock_irqsave(
&WALT78e2cdac9a,WALT05b7c9a580);list_for_each_entry_safe(WALTe2cca49edf,
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
unsigned long WALT05b7c9a580;while((0xd33+3144-0x197a)){set_current_state(
TASK_INTERRUPTIBLE);spin_lock_irqsave(&WALT1b752e214a->WALTffb20e4808,
WALT05b7c9a580);if(!WALT1b752e214a->WALTa280f52f04){spin_unlock_irqrestore(&
WALT1b752e214a->WALTffb20e4808,WALT05b7c9a580);schedule();if(kthread_should_stop
())break;spin_lock_irqsave(&WALT1b752e214a->WALTffb20e4808,WALT05b7c9a580);}
set_current_state(TASK_RUNNING);WALT1b752e214a->WALTa280f52f04=false;
spin_unlock_irqrestore(&WALT1b752e214a->WALTffb20e4808,WALT05b7c9a580);
WALT5b4f389aad(WALT1b752e214a);}return(0xbc0+304-0xcf0);}static int 
WALT7641504060(unsigned int WALT8f9ab72eb9,bool WALTf62b956761){struct 
WALT722543f60e*WALT048da5e00c=&per_cpu(WALT22ef1845d7,WALT8f9ab72eb9);struct 
WALTd84195416f*WALT1b752e214a=WALT048da5e00c->WALT1b752e214a;unsigned int 
WALTf32c877095;bool WALTc7196d407f=false,WALTfbe01eaa1f=false;unsigned long 
WALT05b7c9a580;if(unlikely(!WALT1b752e214a||!WALT1b752e214a->WALTb6181247c7))
return(0x15f8+2264-0x1ed0);if(WALTf62b956761){WALT1b752e214a->active_cpus=
WALTbc04b417fa(WALT1b752e214a);WALT7e643441e5(WALT048da5e00c);}else{if(
WALT048da5e00c->WALT7f508cb38b){sched_unisolate_cpu_unlocked(WALT8f9ab72eb9);
WALT048da5e00c->WALT7f508cb38b=false;WALTfbe01eaa1f=true;}WALT7e643441e5(
WALT048da5e00c);WALT048da5e00c->WALT517f9bdd84=(0xe3b+1096-0x1283);
WALT1b752e214a->active_cpus=WALTbc04b417fa(WALT1b752e214a);}WALTf32c877095=
WALTa16d868f28(WALT1b752e214a,WALT1b752e214a->need_cpus);spin_lock_irqsave(&
WALT78e2cdac9a,WALT05b7c9a580);if(WALTfbe01eaa1f)WALT1b752e214a->WALTd76a53732a
--;WALTc7196d407f=WALT05c5275688(WALT1b752e214a,WALTf32c877095);
spin_unlock_irqrestore(&WALT78e2cdac9a,WALT05b7c9a580);if(WALTc7196d407f)
WALTe68f5dd857(WALT1b752e214a);return(0x1d4d+671-0x1fec);}static int 
WALT32859df63c(unsigned int WALT8f9ab72eb9){return WALT7641504060(WALT8f9ab72eb9
,true);}static int WALT182ef3e766(unsigned int WALT8f9ab72eb9){return 
WALT7641504060(WALT8f9ab72eb9,false);}static struct WALTd84195416f*
WALTd5d0009aa2(unsigned int WALT76f375774d){unsigned int WALT5d971be8b8;for(
WALT5d971be8b8=(0x162+3208-0xdea);WALT5d971be8b8<WALT3480a8e71f;++WALT5d971be8b8
){if(WALT9a7bdf60eb[WALT5d971be8b8].WALT76f375774d==WALT76f375774d)return&
WALT9a7bdf60eb[WALT5d971be8b8];}return NULL;}static int WALTfec3515cc6(const 
struct cpumask*WALTdf9caaa1ec){struct device*WALTf018520c69;unsigned int 
WALT76f375774d=cpumask_first(WALTdf9caaa1ec);struct WALTd84195416f*
WALT1b752e214a;struct WALT722543f60e*WALT048da5e00c;unsigned int WALT8f9ab72eb9;
struct sched_param WALT88d2ec5be5={.sched_priority=MAX_RT_PRIO-
(0xa1c+4827-0x1cf6)};if(WALTd5d0009aa2(WALT76f375774d))return(0x1fc6+83-0x2019);
WALTf018520c69=get_cpu_device(WALT76f375774d);if(!WALTf018520c69)return-ENODEV;
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
min_cpus=(0x769+7050-0x22f2);WALT1b752e214a->max_cpus=WALT1b752e214a->
WALT3fc386a32e;WALT1b752e214a->need_cpus=WALT1b752e214a->WALT3fc386a32e;
WALT1b752e214a->offline_delay_ms=(0xd5d+651-0xf84);WALT1b752e214a->task_thres=
UINT_MAX;WALT1b752e214a->nr_prev_assist_thresh=UINT_MAX;WALT1b752e214a->
WALT78602fc8a3=WALT1b752e214a->WALT3fc386a32e;WALT1b752e214a->enable=true;
WALT1b752e214a->WALT9656065c1c=(0x21ea+701-0x24a7);WALT1b752e214a->
WALTcc9821f091=(0xb84+4376-0x1c9c);INIT_LIST_HEAD(&WALT1b752e214a->
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
,WALT083920bcc8);}WALT69be84bb38=true;return(0x51a+7641-0x22f3);}late_initcall(
core_ctl_init);
