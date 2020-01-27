// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#define pr_fmt(zc4af4bede1)	"\x63\x6f\x72\x65\x5f\x63\x74\x6c\x3a\x20" \
zc4af4bede1
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
struct zd84195416f{bool zb6181247c7;unsigned int min_cpus;unsigned int max_cpus;
unsigned int offline_delay_ms;unsigned int busy_up_thres[MAX_CPUS_PER_CLUSTER];
unsigned int busy_down_thres[MAX_CPUS_PER_CLUSTER];unsigned int active_cpus;
unsigned int z3fc386a32e;unsigned int zd76a53732a;unsigned int z9656065c1c;
cpumask_t z39abd1de52;unsigned int need_cpus;unsigned int task_thres;unsigned 
int zf368d5dcae;unsigned int z263a14abab;unsigned int nr_prev_assist_thresh;s64 
z474287bcf5;struct list_head z895ecc2391;bool za280f52f04;spinlock_t zffb20e4808
;bool enable;int z78602fc8a3;struct task_struct*z2e935f34a1;unsigned int 
z76f375774d;unsigned int boost;struct kobject kobj;unsigned int zcc9821f091;};
struct z722543f60e{bool z087db4d18a;unsigned int z517f9bdd84;unsigned int 
z8f9ab72eb9;bool not_preferred;struct zd84195416f*z1b752e214a;struct list_head 
za7f3b2896c;bool z7f508cb38b;};static DEFINE_PER_CPU(struct z722543f60e,
z22ef1845d7);static struct zd84195416f z9a7bdf60eb[MAX_CLUSTERS];static unsigned
 int z3480a8e71f;
#define z213747575e(z1b752e214a, z8aa1674e1f) \
	for ((z1b752e214a) = &z9a7bdf60eb[z8aa1674e1f]; (z8aa1674e1f) < z3480a8e71f;\
		(z8aa1674e1f)++, (z1b752e214a) = &z9a7bdf60eb[z8aa1674e1f])
static DEFINE_SPINLOCK(z78e2cdac9a);static void z041d9949cf(struct zd84195416f*
z048da5e00c);static void ze68f5dd857(struct zd84195416f*z048da5e00c);static bool
 z69be84bb38;ATOMIC_NOTIFIER_HEAD(ze24f5fc06e);static unsigned int z86ffcc7dfd;
static unsigned int zbc04b417fa(const struct zd84195416f*z1b752e214a);static 
void cpuset_next(struct zd84195416f*z1b752e214a);static ssize_t store_min_cpus(
struct zd84195416f*z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){
unsigned int zc94d3d8015;if(sscanf(z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=
(0x1223+1003-0x160d))return-EINVAL;z048da5e00c->min_cpus=min(zc94d3d8015,
z048da5e00c->max_cpus);cpuset_next(z048da5e00c);ze68f5dd857(z048da5e00c);return 
z33ea1b60d7;}static ssize_t show_min_cpus(const struct zd84195416f*z048da5e00c,
char*z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",
z048da5e00c->min_cpus);}static ssize_t store_max_cpus(struct zd84195416f*
z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015;
if(sscanf(z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=(0xb9d+847-0xeeb))return-
EINVAL;zc94d3d8015=min(zc94d3d8015,z048da5e00c->z3fc386a32e);z048da5e00c->
max_cpus=zc94d3d8015;z048da5e00c->min_cpus=min(z048da5e00c->min_cpus,z048da5e00c
->max_cpus);cpuset_next(z048da5e00c);ze68f5dd857(z048da5e00c);return z33ea1b60d7
;}static ssize_t show_max_cpus(const struct zd84195416f*z048da5e00c,char*
z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",z048da5e00c->
max_cpus);}static ssize_t store_offline_delay_ms(struct zd84195416f*z048da5e00c,
const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015;if(sscanf(
z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=(0xc89+3997-0x1c25))return-EINVAL;
z048da5e00c->offline_delay_ms=zc94d3d8015;z041d9949cf(z048da5e00c);return 
z33ea1b60d7;}static ssize_t show_task_thres(const struct zd84195416f*z048da5e00c
,char*z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",
z048da5e00c->task_thres);}static ssize_t store_task_thres(struct zd84195416f*
z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015;
if(sscanf(z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=(0x1767+3157-0x23bb))return
-EINVAL;if(zc94d3d8015<z048da5e00c->z3fc386a32e)return-EINVAL;z048da5e00c->
task_thres=zc94d3d8015;z041d9949cf(z048da5e00c);return z33ea1b60d7;}static 
ssize_t show_nr_prev_assist_thresh(const struct zd84195416f*z048da5e00c,char*
z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",z048da5e00c->
nr_prev_assist_thresh);}static ssize_t store_nr_prev_assist_thresh(struct 
zd84195416f*z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int 
zc94d3d8015;if(sscanf(z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=
(0x46+8604-0x21e1))return-EINVAL;z048da5e00c->nr_prev_assist_thresh=zc94d3d8015;
z041d9949cf(z048da5e00c);return z33ea1b60d7;}static ssize_t 
show_offline_delay_ms(const struct zd84195416f*z048da5e00c,char*z33c5f8b4bc){
return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",z048da5e00c->
offline_delay_ms);}static ssize_t store_busy_up_thres(struct zd84195416f*
z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015[
MAX_CPUS_PER_CLUSTER];int z083920bcc8,z5d971be8b8;z083920bcc8=sscanf(z33c5f8b4bc
,"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
zc94d3d8015[(0x379+3021-0xf46)],&zc94d3d8015[(0xc43+4535-0x1df9)],&zc94d3d8015[
(0x56a+5946-0x1ca2)],&zc94d3d8015[(0x1da+2110-0xa15)],&zc94d3d8015[
(0x917+884-0xc87)],&zc94d3d8015[(0x2470+153-0x2504)]);if(z083920bcc8!=
(0x1b3+8289-0x2213)&&z083920bcc8!=z048da5e00c->z3fc386a32e)return-EINVAL;if(
z083920bcc8==(0x7c1+1504-0xda0)){for(z5d971be8b8=(0x838+4463-0x19a7);z5d971be8b8
<z048da5e00c->z3fc386a32e;z5d971be8b8++)z048da5e00c->busy_up_thres[z5d971be8b8]=
zc94d3d8015[(0xa57+342-0xbad)];}else{for(z5d971be8b8=(0x455+5070-0x1823);
z5d971be8b8<z048da5e00c->z3fc386a32e;z5d971be8b8++)z048da5e00c->busy_up_thres[
z5d971be8b8]=zc94d3d8015[z5d971be8b8];}z041d9949cf(z048da5e00c);return 
z33ea1b60d7;}static ssize_t show_busy_up_thres(const struct zd84195416f*
z048da5e00c,char*z33c5f8b4bc){int z5d971be8b8,z33ea1b60d7=(0x1bef+1842-0x2321);
for(z5d971be8b8=(0xfed+1939-0x1780);z5d971be8b8<z048da5e00c->z3fc386a32e;
z5d971be8b8++)z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-
z33ea1b60d7,"\x25\x75\x20",z048da5e00c->busy_up_thres[z5d971be8b8]);z33ea1b60d7
+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,"\n");return 
z33ea1b60d7;}static ssize_t store_busy_down_thres(struct zd84195416f*z048da5e00c
,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015[
MAX_CPUS_PER_CLUSTER];int z083920bcc8,z5d971be8b8;z083920bcc8=sscanf(z33c5f8b4bc
,"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
zc94d3d8015[(0xdcf+1903-0x153e)],&zc94d3d8015[(0x3ef+1651-0xa61)],&zc94d3d8015[
(0xd92+4677-0x1fd5)],&zc94d3d8015[(0x1013+1945-0x17a9)],&zc94d3d8015[
(0xabf+4828-0x1d97)],&zc94d3d8015[(0x331+1063-0x753)]);if(z083920bcc8!=
(0x1370+698-0x1629)&&z083920bcc8!=z048da5e00c->z3fc386a32e)return-EINVAL;if(
z083920bcc8==(0xe2d+4787-0x20df)){for(z5d971be8b8=(0x59+5772-0x16e5);z5d971be8b8
<z048da5e00c->z3fc386a32e;z5d971be8b8++)z048da5e00c->busy_down_thres[z5d971be8b8
]=zc94d3d8015[(0x425+2252-0xcf1)];}else{for(z5d971be8b8=(0x527+8329-0x25b0);
z5d971be8b8<z048da5e00c->z3fc386a32e;z5d971be8b8++)z048da5e00c->busy_down_thres[
z5d971be8b8]=zc94d3d8015[z5d971be8b8];}z041d9949cf(z048da5e00c);return 
z33ea1b60d7;}static ssize_t show_busy_down_thres(const struct zd84195416f*
z048da5e00c,char*z33c5f8b4bc){int z5d971be8b8,z33ea1b60d7=(0x12f6+4365-0x2403);
for(z5d971be8b8=(0x7df+2303-0x10de);z5d971be8b8<z048da5e00c->z3fc386a32e;
z5d971be8b8++)z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-
z33ea1b60d7,"\x25\x75\x20",z048da5e00c->busy_down_thres[z5d971be8b8]);
z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,"\n");return
 z33ea1b60d7;}static ssize_t store_enable(struct zd84195416f*z048da5e00c,const 
char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015;bool zd09cc5ef75;
if(sscanf(z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=(0x982+6905-0x247a))return-
EINVAL;zd09cc5ef75=!!zc94d3d8015;if(zd09cc5ef75!=z048da5e00c->enable){
z048da5e00c->enable=zd09cc5ef75;z041d9949cf(z048da5e00c);}return z33ea1b60d7;}
static ssize_t show_enable(const struct zd84195416f*z048da5e00c,char*z33c5f8b4bc
){return scnprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",z048da5e00c->enable);}
static ssize_t show_need_cpus(const struct zd84195416f*z048da5e00c,char*
z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",z048da5e00c->
need_cpus);}static ssize_t show_active_cpus(const struct zd84195416f*z048da5e00c
,char*z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",
z048da5e00c->active_cpus);}static ssize_t show_global_state(const struct 
zd84195416f*z048da5e00c,char*z33c5f8b4bc){struct z722543f60e*ze2cca49edf;struct 
zd84195416f*z1b752e214a;ssize_t z33ea1b60d7=(0x212d+1033-0x2536);unsigned int 
z8f9ab72eb9;spin_lock_irq(&z78e2cdac9a);for_each_possible_cpu(z8f9ab72eb9){
ze2cca49edf=&per_cpu(z22ef1845d7,z8f9ab72eb9);z1b752e214a=ze2cca49edf->
z1b752e214a;if(!z1b752e214a||!z1b752e214a->zb6181247c7)continue;z33ea1b60d7+=
snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,
"\x43\x50\x55\x25\x75" "\n",z8f9ab72eb9);z33ea1b60d7+=snprintf(z33c5f8b4bc+
z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,"\t" "\x43\x50\x55\x3a\x20\x25\x75" "\n",
ze2cca49edf->z8f9ab72eb9);z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,
PAGE_SIZE-z33ea1b60d7,"\t" "\x4f\x6e\x6c\x69\x6e\x65\x3a\x20\x25\x75" "\n",
cpu_online(ze2cca49edf->z8f9ab72eb9));z33ea1b60d7+=snprintf(z33c5f8b4bc+
z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,
"\t" "\x49\x73\x6f\x6c\x61\x74\x65\x64\x3a\x20\x25\x75" "\n",cpu_isolated(
ze2cca49edf->z8f9ab72eb9));z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,
PAGE_SIZE-z33ea1b60d7,
"\t" "\x46\x69\x72\x73\x74\x20\x43\x50\x55\x3a\x20\x25\x75" "\n",z1b752e214a->
z76f375774d);z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7
,"\t" "\x42\x75\x73\x79\x25\x25\x3a\x20\x25\x75" "\n",ze2cca49edf->z517f9bdd84);
z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,
"\t" "\x49\x73\x20\x62\x75\x73\x79\x3a\x20\x25\x75" "\n",ze2cca49edf->
z087db4d18a);z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7
,
"\t" "\x4e\x6f\x74\x20\x70\x72\x65\x66\x65\x72\x72\x65\x64\x3a\x20\x25\x75" "\n"
,ze2cca49edf->not_preferred);z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,
PAGE_SIZE-z33ea1b60d7,
"\t" "\x4e\x72\x20\x72\x75\x6e\x6e\x69\x6e\x67\x3a\x20\x25\x75" "\n",z1b752e214a
->z78602fc8a3);z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-
z33ea1b60d7,
"\t" "\x41\x63\x74\x69\x76\x65\x20\x43\x50\x55\x73\x3a\x20\x25\x75" "\n",
zbc04b417fa(z1b752e214a));z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,
PAGE_SIZE-z33ea1b60d7,
"\t" "\x4e\x65\x65\x64\x20\x43\x50\x55\x73\x3a\x20\x25\x75" "\n",z1b752e214a->
need_cpus);z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,
"\t" "\x4e\x72\x20\x69\x73\x6f\x6c\x61\x74\x65\x64\x20\x43\x50\x55\x73\x3a\x20\x25\x75" "\n"
,z1b752e214a->zd76a53732a);z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,
PAGE_SIZE-z33ea1b60d7,"\t" "\x42\x6f\x6f\x73\x74\x3a\x20\x25\x75" "\n",(unsigned
 int)z1b752e214a->boost);}spin_unlock_irq(&z78e2cdac9a);return z33ea1b60d7;}
static ssize_t store_not_preferred(struct zd84195416f*z048da5e00c,const char*
z33c5f8b4bc,size_t z33ea1b60d7){struct z722543f60e*ze2cca49edf;unsigned int 
z5d971be8b8;unsigned int zc94d3d8015[MAX_CPUS_PER_CLUSTER];unsigned long 
z05b7c9a580;int z083920bcc8;int z30bdc18e2b=(0xf00+1987-0x16c3);z083920bcc8=
sscanf(z33c5f8b4bc,
"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
zc94d3d8015[(0x1f33+335-0x2082)],&zc94d3d8015[(0x1fa6+423-0x214c)],&zc94d3d8015[
(0xd5a+5131-0x2163)],&zc94d3d8015[(0xcbb+1525-0x12ad)],&zc94d3d8015[
(0x1fa8+877-0x2311)],&zc94d3d8015[(0x9cd+2056-0x11d0)]);if(z083920bcc8!=
z048da5e00c->z3fc386a32e)return-EINVAL;spin_lock_irqsave(&z78e2cdac9a,
z05b7c9a580);for(z5d971be8b8=(0xcd2+269-0xddf);z5d971be8b8<z048da5e00c->
z3fc386a32e;z5d971be8b8++){ze2cca49edf=&per_cpu(z22ef1845d7,z5d971be8b8+
z048da5e00c->z76f375774d);ze2cca49edf->not_preferred=zc94d3d8015[z5d971be8b8];
z30bdc18e2b+=!!zc94d3d8015[z5d971be8b8];}z048da5e00c->z9656065c1c=z30bdc18e2b;
spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);return z33ea1b60d7;}static 
ssize_t show_not_preferred(const struct zd84195416f*z048da5e00c,char*z33c5f8b4bc
){struct z722543f60e*ze2cca49edf;ssize_t z33ea1b60d7=(0x1ea6+1026-0x22a8);
unsigned long z05b7c9a580;int z5d971be8b8;spin_lock_irqsave(&z78e2cdac9a,
z05b7c9a580);for(z5d971be8b8=(0x1202+2795-0x1ced);z5d971be8b8<z048da5e00c->
z3fc386a32e;z5d971be8b8++){ze2cca49edf=&per_cpu(z22ef1845d7,z5d971be8b8+
z048da5e00c->z76f375774d);z33ea1b60d7+=scnprintf(z33c5f8b4bc+z33ea1b60d7,
PAGE_SIZE-z33ea1b60d7,"\x43\x50\x55\x23\x25\x64\x3a\x20\x25\x75" "\n",
ze2cca49edf->z8f9ab72eb9,ze2cca49edf->not_preferred);}spin_unlock_irqrestore(&
z78e2cdac9a,z05b7c9a580);return z33ea1b60d7;}struct core_ctl_attr{struct 
attribute attr;ssize_t(*show)(const struct zd84195416f*,char*);ssize_t(*store)(
struct zd84195416f*,const char*,size_t z33ea1b60d7);};
#define core_ctl_attr_ro(zb25dfb9431)		\
static struct core_ctl_attr zb25dfb9431 =	\
__ATTR(zb25dfb9431, (0x12f+9318-0x2471), show_##zb25dfb9431, NULL)
#define core_ctl_attr_rw(zb25dfb9431)			\
static struct core_ctl_attr zb25dfb9431 =		\
__ATTR(zb25dfb9431, (0x18e8+3025-0x2315), show_##zb25dfb9431, store_##\
zb25dfb9431)
core_ctl_attr_rw(min_cpus);core_ctl_attr_rw(max_cpus);core_ctl_attr_rw(
offline_delay_ms);core_ctl_attr_rw(busy_up_thres);core_ctl_attr_rw(
busy_down_thres);core_ctl_attr_rw(task_thres);core_ctl_attr_rw(
nr_prev_assist_thresh);core_ctl_attr_ro(need_cpus);core_ctl_attr_ro(active_cpus)
;core_ctl_attr_ro(global_state);core_ctl_attr_rw(not_preferred);core_ctl_attr_rw
(enable);static struct attribute*default_attrs[]={&min_cpus.attr,&max_cpus.attr,
&offline_delay_ms.attr,&busy_up_thres.attr,&busy_down_thres.attr,&task_thres.
attr,&nr_prev_assist_thresh.attr,&enable.attr,&need_cpus.attr,&active_cpus.attr,
&global_state.attr,&not_preferred.attr,NULL};
#define ze67e7bc098(z041cb91678) container_of(z041cb91678, struct zd84195416f, \
kobj)
#define zc8af498370(z6268ff8549) container_of(z6268ff8549, struct core_ctl_attr,\
 attr)
static ssize_t show(struct kobject*kobj,struct attribute*attr,char*z33c5f8b4bc){
struct zd84195416f*zf8791a57cc=ze67e7bc098(kobj);struct core_ctl_attr*
z9514acbabb=zc8af498370(attr);ssize_t z083920bcc8=-EIO;if(z9514acbabb->show)
z083920bcc8=z9514acbabb->show(zf8791a57cc,z33c5f8b4bc);return z083920bcc8;}
static ssize_t store(struct kobject*kobj,struct attribute*attr,const char*
z33c5f8b4bc,size_t z33ea1b60d7){struct zd84195416f*zf8791a57cc=ze67e7bc098(kobj)
;struct core_ctl_attr*z9514acbabb=zc8af498370(attr);ssize_t z083920bcc8=-EIO;if(
z9514acbabb->store)z083920bcc8=z9514acbabb->store(zf8791a57cc,z33c5f8b4bc,
z33ea1b60d7);return z083920bcc8;}static const struct sysfs_ops sysfs_ops={.show=
show,.store=store,};static struct kobj_type ze314eed4f2={.sysfs_ops=&sysfs_ops,.
default_attrs=default_attrs,};static struct sched_avg_stats z3d55024438[NR_CPUS]
;static int z586cb87856(int z6b2e94bfe7){int z8f9ab72eb9;struct zd84195416f*
z1b752e214a;int z7cdf3ec737=(0x1a+710-0x2e0);z213747575e(z1b752e214a,z6b2e94bfe7
){for_each_cpu(z8f9ab72eb9,&z1b752e214a->z39abd1de52)z7cdf3ec737+=z3d55024438[
z8f9ab72eb9].nr;}return z7cdf3ec737;}static int z91003ac218(int z6b2e94bfe7){int
 z8f9ab72eb9;struct zd84195416f*z79d47a94b2;int z33128046d7=(0x1006+2795-0x1af1)
;if(z6b2e94bfe7==(0x55+511-0x254))return(0x1399+714-0x1663);z79d47a94b2=&
z9a7bdf60eb[z6b2e94bfe7-(0x14ac+3922-0x23fd)];for_each_cpu(z8f9ab72eb9,&
z79d47a94b2->z39abd1de52)z33128046d7+=z3d55024438[z8f9ab72eb9].nr_misfit;return 
z33128046d7;}static int z4e9e6ae627(int z6b2e94bfe7){int z8f9ab72eb9;struct 
zd84195416f*z1b752e214a=&z9a7bdf60eb[z6b2e94bfe7];int zf368d5dcae=
(0x4c1+84-0x515);for_each_cpu(z8f9ab72eb9,&z1b752e214a->z39abd1de52)zf368d5dcae=
max(zf368d5dcae,z3d55024438[z8f9ab72eb9].nr_max);return zf368d5dcae;}static int 
z9385e48bfe(int z6b2e94bfe7){int nr_big=(0xb40+6499-0x24a3);int z8f9ab72eb9;
struct zd84195416f*z1b752e214a=&z9a7bdf60eb[z6b2e94bfe7];if(z6b2e94bfe7==
(0xd35+4775-0x1fdc)){for_each_cpu(z8f9ab72eb9,&z1b752e214a->z39abd1de52)nr_big+=
z3d55024438[z8f9ab72eb9].nr_misfit;}else{for_each_cpu(z8f9ab72eb9,&z1b752e214a->
z39abd1de52)nr_big+=z3d55024438[z8f9ab72eb9].nr;}return nr_big;}static int 
z4d8e98122d(int z6b2e94bfe7){int zf32c877095=(0xc00+3623-0x1a27);int z8f9ab72eb9
;struct zd84195416f*z79d47a94b2;if(z6b2e94bfe7==(0xad+8963-0x23b0))return
(0xea9+2580-0x18bd);z6b2e94bfe7--;z79d47a94b2=&z9a7bdf60eb[z6b2e94bfe7];if(
z79d47a94b2->zd76a53732a)return(0xd79+82-0xdcb);for_each_cpu(z8f9ab72eb9,&
z79d47a94b2->z39abd1de52)zf32c877095+=z3d55024438[z8f9ab72eb9].nr;zf32c877095+=
z91003ac218(z6b2e94bfe7);if(zf32c877095>z79d47a94b2->active_cpus)zf32c877095=
zf32c877095-z79d47a94b2->active_cpus;else zf32c877095=(0x1128+180-0x11dc);return
 zf32c877095;}static int zf3336414f3(int z6b2e94bfe7){int z8f9ab72eb9;struct 
zd84195416f*z1b752e214a;int z49c28541b7=(0xa17+6448-0x2347);if(z6b2e94bfe7!=
(0x570+4533-0x1725))return(0x1a8f+3040-0x266f);z213747575e(z1b752e214a,
z6b2e94bfe7){int nr_scaled=(0x381+1534-0x97f);int active_cpus=z1b752e214a->
active_cpus;for_each_cpu(z8f9ab72eb9,&z1b752e214a->z39abd1de52)nr_scaled+=
z3d55024438[z8f9ab72eb9].nr_scaled;nr_scaled/=(0x152b+1706-0x1b71);if(
z6b2e94bfe7==(0x11e2+4876-0x24ee))z49c28541b7+=nr_scaled;else z49c28541b7+=max(
(0xfb8+4921-0x22f1),nr_scaled-active_cpus);}return z49c28541b7;}static void 
z595408d471(void){struct zd84195416f*z1b752e214a;unsigned int z6b2e94bfe7=
(0x1c4+3975-0x114b);unsigned long z05b7c9a580;int zd8515de889=
(0x124f+1174-0x16e5);sched_get_nr_running_avg(z3d55024438);spin_lock_irqsave(&
z78e2cdac9a,z05b7c9a580);z213747575e(z1b752e214a,z6b2e94bfe7){int z7cdf3ec737,
z33128046d7;if(!z1b752e214a->zb6181247c7)continue;z7cdf3ec737=z586cb87856(
z6b2e94bfe7);z33128046d7=z91003ac218(z6b2e94bfe7);z1b752e214a->z78602fc8a3=
z7cdf3ec737+z33128046d7;z1b752e214a->zf368d5dcae=z4e9e6ae627(z6b2e94bfe7);
z1b752e214a->z263a14abab=z4d8e98122d(z6b2e94bfe7);z1b752e214a->zcc9821f091=
zf3336414f3(z6b2e94bfe7);trace_core_ctl_update_nr_need(z1b752e214a->z76f375774d,
z7cdf3ec737,z33128046d7,z1b752e214a->z78602fc8a3,z1b752e214a->zf368d5dcae,
z1b752e214a->z263a14abab);zd8515de889+=z9385e48bfe(z6b2e94bfe7);}
spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);z86ffcc7dfd=zd8515de889;
walt_rotation_checkpoint(zd8515de889);}
#define zc2db0febb0	(0x8b+9705-0x2670)
static unsigned int z50b207ad6d(const struct zd84195416f*z1b752e214a,unsigned 
int zeadf56a7a3){if(z1b752e214a->z78602fc8a3>=z1b752e214a->task_thres)return 
z1b752e214a->z3fc386a32e;if(z1b752e214a->z263a14abab>=z1b752e214a->
nr_prev_assist_thresh)zeadf56a7a3=zeadf56a7a3+z1b752e214a->z263a14abab;if(
z1b752e214a->z78602fc8a3>zeadf56a7a3)zeadf56a7a3=zeadf56a7a3+(0x24d+5030-0x15f2)
;if(z1b752e214a->zf368d5dcae>zc2db0febb0)zeadf56a7a3=zeadf56a7a3+
(0x1042+5214-0x249f);if(zeadf56a7a3<z1b752e214a->zcc9821f091)zeadf56a7a3=
z1b752e214a->zcc9821f091;return zeadf56a7a3;}static unsigned int za16d868f28(
const struct zd84195416f*z1b752e214a,unsigned int need_cpus){return min(max(
z1b752e214a->min_cpus,need_cpus),z1b752e214a->max_cpus);}static unsigned int 
zbc04b417fa(const struct zd84195416f*z1b752e214a){return z1b752e214a->
z3fc386a32e-sched_isolate_count(&z1b752e214a->z39abd1de52,true);}static bool 
z375fa7adc6(const struct z722543f60e*z048da5e00c){return cpu_online(z048da5e00c
->z8f9ab72eb9)&&!cpu_isolated(z048da5e00c->z8f9ab72eb9);}static bool z05c5275688
(const struct zd84195416f*z1b752e214a,unsigned int zf32c877095){return(
zf32c877095<z1b752e214a->active_cpus||(zf32c877095>z1b752e214a->active_cpus&&
z1b752e214a->zd76a53732a));}static bool zf6692437dc(const struct zd84195416f*
z1b752e214a){return(is_min_capacity_cpu(z1b752e214a->z76f375774d)&&
sched_ravg_window<DEFAULT_SCHED_RAVG_WINDOW);}static bool eval_need(struct 
zd84195416f*z1b752e214a){unsigned long z05b7c9a580;struct z722543f60e*
ze2cca49edf;unsigned int need_cpus=(0x113+1480-0x6db),zefe45c244d,z8255d868d2;
int z083920bcc8=(0x15b+3323-0xe56);bool z11e2990555=false;unsigned int 
zeadf56a7a3;s64 z2c53bb3f34,zcc63e644e4;if(unlikely(!z1b752e214a->zb6181247c7))
return(0x138+3663-0xf87);spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);if(
z1b752e214a->boost||!z1b752e214a->enable||zf6692437dc(z1b752e214a)){need_cpus=
z1b752e214a->max_cpus;}else{z1b752e214a->active_cpus=zbc04b417fa(z1b752e214a);
z8255d868d2=z1b752e214a->active_cpus?z1b752e214a->active_cpus-
(0x185f+1372-0x1dba):(0xf41+3616-0x1d61);list_for_each_entry(ze2cca49edf,&
z1b752e214a->z895ecc2391,za7f3b2896c){bool z28dac86562=ze2cca49edf->z087db4d18a;
if(ze2cca49edf->z517f9bdd84>=z1b752e214a->busy_up_thres[z8255d868d2]||
sched_cpu_high_irqload(ze2cca49edf->z8f9ab72eb9))ze2cca49edf->z087db4d18a=true;
else if(ze2cca49edf->z517f9bdd84<z1b752e214a->busy_down_thres[z8255d868d2])
ze2cca49edf->z087db4d18a=false;trace_core_ctl_set_busy(ze2cca49edf->z8f9ab72eb9,
ze2cca49edf->z517f9bdd84,z28dac86562,ze2cca49edf->z087db4d18a);need_cpus+=
ze2cca49edf->z087db4d18a;}need_cpus=z50b207ad6d(z1b752e214a,need_cpus);}
zeadf56a7a3=za16d868f28(z1b752e214a,need_cpus);z11e2990555=z05c5275688(
z1b752e214a,zeadf56a7a3);zefe45c244d=z1b752e214a->need_cpus;z2c53bb3f34=
ktime_to_ms(ktime_get());if(zeadf56a7a3>z1b752e214a->active_cpus){z083920bcc8=
(0x22+3622-0xe47);}else{if(zeadf56a7a3==zefe45c244d&&zeadf56a7a3==z1b752e214a->
active_cpus){z1b752e214a->z474287bcf5=z2c53bb3f34;spin_unlock_irqrestore(&
z78e2cdac9a,z05b7c9a580);return(0x2d4+2346-0xbfe);}zcc63e644e4=z2c53bb3f34-
z1b752e214a->z474287bcf5;z083920bcc8=zcc63e644e4>=z1b752e214a->offline_delay_ms;
}if(z083920bcc8){z1b752e214a->z474287bcf5=z2c53bb3f34;z1b752e214a->need_cpus=
zeadf56a7a3;}trace_core_ctl_eval_need(z1b752e214a->z76f375774d,zefe45c244d,
zeadf56a7a3,z083920bcc8&&z11e2990555);spin_unlock_irqrestore(&z78e2cdac9a,
z05b7c9a580);return z083920bcc8&&z11e2990555;}static void z041d9949cf(struct 
zd84195416f*z1b752e214a){if(eval_need(z1b752e214a))ze68f5dd857(z1b752e214a);}
static void ze68f5dd857(struct zd84195416f*z1b752e214a){unsigned long 
z05b7c9a580;spin_lock_irqsave(&z1b752e214a->zffb20e4808,z05b7c9a580);z1b752e214a
->za280f52f04=true;spin_unlock_irqrestore(&z1b752e214a->zffb20e4808,z05b7c9a580)
;wake_up_process(z1b752e214a->z2e935f34a1);}static u64 zdfa13d72c3;int 
core_ctl_set_boost(bool boost){unsigned int z6b2e94bfe7=(0x1cc1+257-0x1dc2);
struct zd84195416f*z1b752e214a;unsigned long z05b7c9a580;int z083920bcc8=
(0xc2c+3354-0x1946);bool z37066d5eec=false;if(unlikely(!z69be84bb38))return
(0x4ec+8721-0x26fd);spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);z213747575e(
z1b752e214a,z6b2e94bfe7){if(boost){z37066d5eec=!z1b752e214a->boost;++z1b752e214a
->boost;}else{if(!z1b752e214a->boost){z083920bcc8=-EINVAL;break;}else{--
z1b752e214a->boost;z37066d5eec=!z1b752e214a->boost;}}}spin_unlock_irqrestore(&
z78e2cdac9a,z05b7c9a580);if(z37066d5eec){z6b2e94bfe7=(0x63f+6168-0x1e57);
z213747575e(z1b752e214a,z6b2e94bfe7)z041d9949cf(z1b752e214a);}
trace_core_ctl_set_boost(z1b752e214a->boost,z083920bcc8);return z083920bcc8;}
EXPORT_SYMBOL(core_ctl_set_boost);void core_ctl_notifier_register(struct 
notifier_block*zfe5c53f6bd){atomic_notifier_chain_register(&ze24f5fc06e,
zfe5c53f6bd);}void core_ctl_notifier_unregister(struct notifier_block*
zfe5c53f6bd){atomic_notifier_chain_unregister(&ze24f5fc06e,zfe5c53f6bd);}static 
void z521764ce34(void){struct core_ctl_notif_data z89bf9aac81={
(0x86b+3163-0x14c6)};struct notifier_block*z9e976b309a;rcu_read_lock();
z9e976b309a=rcu_dereference_raw(ze24f5fc06e.head);rcu_read_unlock();if(!
z9e976b309a)return;z89bf9aac81.nr_big=z86ffcc7dfd;walt_fill_ta_data(&z89bf9aac81
);trace_core_ctl_notif_data(z89bf9aac81.nr_big,z89bf9aac81.coloc_load_pct,
z89bf9aac81.ta_util_pct,z89bf9aac81.cur_cap_pct);atomic_notifier_call_chain(&
ze24f5fc06e,(0x157f+2095-0x1dae),&z89bf9aac81);}void core_ctl_check(u64 
zd872303760){int z8f9ab72eb9;struct z722543f60e*ze2cca49edf;struct zd84195416f*
z1b752e214a;unsigned int z6b2e94bfe7=(0x196f+1239-0x1e46);unsigned long 
z05b7c9a580;if(unlikely(!z69be84bb38))return;if(zd872303760==zdfa13d72c3)return;
zdfa13d72c3=zd872303760;spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);
for_each_possible_cpu(z8f9ab72eb9){ze2cca49edf=&per_cpu(z22ef1845d7,z8f9ab72eb9)
;z1b752e214a=ze2cca49edf->z1b752e214a;if(!z1b752e214a||!z1b752e214a->zb6181247c7
)continue;ze2cca49edf->z517f9bdd84=sched_get_cpu_util(z8f9ab72eb9);}
spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);z595408d471();z213747575e(
z1b752e214a,z6b2e94bfe7){if(eval_need(z1b752e214a))ze68f5dd857(z1b752e214a);}
z521764ce34();}static void z7e643441e5(struct z722543f60e*z722543f60e){unsigned 
long z05b7c9a580;spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);list_del(&
z722543f60e->za7f3b2896c);list_add_tail(&z722543f60e->za7f3b2896c,&z722543f60e->
z1b752e214a->z895ecc2391);spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);}
static void cpuset_next(struct zd84195416f*z1b752e214a){}static bool z25bcd77821
(int z8f9ab72eb9,struct zd84195416f*z1b752e214a){return true;}static void 
zb426628abe(struct zd84195416f*z1b752e214a,unsigned int zf32c877095){struct 
z722543f60e*ze2cca49edf,*zb9b0dca770;unsigned long z05b7c9a580;unsigned int 
z3fc386a32e=z1b752e214a->z3fc386a32e;unsigned int z3407f2d0ae=
(0x1163+4672-0x23a3);bool z23fe99670b=z1b752e214a->z9656065c1c;spin_lock_irqsave
(&z78e2cdac9a,z05b7c9a580);list_for_each_entry_safe(ze2cca49edf,zb9b0dca770,&
z1b752e214a->z895ecc2391,za7f3b2896c){if(!z3fc386a32e--)break;if(!z375fa7adc6(
ze2cca49edf))continue;if(z1b752e214a->active_cpus==zf32c877095)break;if(
ze2cca49edf->z087db4d18a)continue;if(z1b752e214a->z9656065c1c&&!ze2cca49edf->
not_preferred)continue;if(!z25bcd77821(ze2cca49edf->z8f9ab72eb9,z1b752e214a))
continue;spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);pr_debug(
"\x54\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,ze2cca49edf->z8f9ab72eb9);if(!sched_isolate_cpu(ze2cca49edf->z8f9ab72eb9)){
ze2cca49edf->z7f508cb38b=true;z7e643441e5(ze2cca49edf);z3407f2d0ae++;}else{
pr_debug(
"\x55\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,ze2cca49edf->z8f9ab72eb9);}z1b752e214a->active_cpus=zbc04b417fa(z1b752e214a);
spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);}z1b752e214a->zd76a53732a+=
z3407f2d0ae;spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);zcd588e3717:if(
z1b752e214a->active_cpus<=z1b752e214a->max_cpus)return;z3407f2d0ae=
(0x19e9+2228-0x229d);z3fc386a32e=z1b752e214a->z3fc386a32e;spin_lock_irqsave(&
z78e2cdac9a,z05b7c9a580);list_for_each_entry_safe(ze2cca49edf,zb9b0dca770,&
z1b752e214a->z895ecc2391,za7f3b2896c){if(!z3fc386a32e--)break;if(!z375fa7adc6(
ze2cca49edf))continue;if(z1b752e214a->active_cpus<=z1b752e214a->max_cpus)break;
if(z23fe99670b&&!ze2cca49edf->not_preferred)continue;spin_unlock_irqrestore(&
z78e2cdac9a,z05b7c9a580);pr_debug(
"\x54\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,ze2cca49edf->z8f9ab72eb9);if(!sched_isolate_cpu(ze2cca49edf->z8f9ab72eb9)){
ze2cca49edf->z7f508cb38b=true;z7e643441e5(ze2cca49edf);z3407f2d0ae++;}else{
pr_debug(
"\x55\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,ze2cca49edf->z8f9ab72eb9);}z1b752e214a->active_cpus=zbc04b417fa(z1b752e214a);
spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);}z1b752e214a->zd76a53732a+=
z3407f2d0ae;spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);if(z23fe99670b&&
z1b752e214a->active_cpus>z1b752e214a->max_cpus){z23fe99670b=false;goto 
zcd588e3717;}}static void z8d759fe75f(struct zd84195416f*z1b752e214a,unsigned 
int zf32c877095,bool z16510eae6d){struct z722543f60e*ze2cca49edf,*zb9b0dca770;
unsigned long z05b7c9a580;unsigned int z3fc386a32e=z1b752e214a->z3fc386a32e;
unsigned int za857c3409b=(0xe94+3585-0x1c95);spin_lock_irqsave(&z78e2cdac9a,
z05b7c9a580);list_for_each_entry_safe(ze2cca49edf,zb9b0dca770,&z1b752e214a->
z895ecc2391,za7f3b2896c){if(!z3fc386a32e--)break;if(!ze2cca49edf->z7f508cb38b)
continue;if((cpu_online(ze2cca49edf->z8f9ab72eb9)&&!cpu_isolated(ze2cca49edf->
z8f9ab72eb9))||(!z16510eae6d&&ze2cca49edf->not_preferred))continue;if(
z1b752e214a->active_cpus==zf32c877095)break;spin_unlock_irqrestore(&z78e2cdac9a,
z05b7c9a580);pr_debug(
"\x54\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x75\x6e\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,ze2cca49edf->z8f9ab72eb9);if(!sched_unisolate_cpu(ze2cca49edf->z8f9ab72eb9)){
ze2cca49edf->z7f508cb38b=false;z7e643441e5(ze2cca49edf);za857c3409b++;}else{
pr_debug(
"\x55\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x75\x6e\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,ze2cca49edf->z8f9ab72eb9);}z1b752e214a->active_cpus=zbc04b417fa(z1b752e214a);
spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);}z1b752e214a->zd76a53732a-=
za857c3409b;spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);}static void 
z06ff7ad6cf(struct zd84195416f*z1b752e214a,unsigned int zf32c877095){bool 
z02ab9de09c=false;z8d759fe75f(z1b752e214a,zf32c877095,z02ab9de09c);if(
z1b752e214a->active_cpus==zf32c877095)return;z02ab9de09c=true;z8d759fe75f(
z1b752e214a,zf32c877095,z02ab9de09c);}static void __ref z5b4f389aad(struct 
zd84195416f*z1b752e214a){unsigned int zf32c877095;zf32c877095=za16d868f28(
z1b752e214a,z1b752e214a->need_cpus);if(z05c5275688(z1b752e214a,zf32c877095)){
pr_debug(
"\x54\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x61\x64\x6a\x75\x73\x74\x20\x67\x72\x6f\x75\x70\x20\x25\x75\x20\x66\x72\x6f\x6d\x20\x25\x75\x20\x74\x6f\x20\x25\x75" "\n"
,z1b752e214a->z76f375774d,z1b752e214a->active_cpus,zf32c877095);if(z1b752e214a->
active_cpus>zf32c877095)zb426628abe(z1b752e214a,zf32c877095);else if(z1b752e214a
->active_cpus<zf32c877095)z06ff7ad6cf(z1b752e214a,zf32c877095);}}static int 
__ref zcc8e90311b(void*zf8791a57cc){struct zd84195416f*z1b752e214a=zf8791a57cc;
unsigned long z05b7c9a580;while((0x818+5865-0x1f00)){set_current_state(
TASK_INTERRUPTIBLE);spin_lock_irqsave(&z1b752e214a->zffb20e4808,z05b7c9a580);if(
!z1b752e214a->za280f52f04){spin_unlock_irqrestore(&z1b752e214a->zffb20e4808,
z05b7c9a580);schedule();if(kthread_should_stop())break;spin_lock_irqsave(&
z1b752e214a->zffb20e4808,z05b7c9a580);}set_current_state(TASK_RUNNING);
z1b752e214a->za280f52f04=false;spin_unlock_irqrestore(&z1b752e214a->zffb20e4808,
z05b7c9a580);z5b4f389aad(z1b752e214a);}return(0xcf9+2382-0x1647);}static int 
z7641504060(unsigned int z8f9ab72eb9,bool zf62b956761){struct z722543f60e*
z048da5e00c=&per_cpu(z22ef1845d7,z8f9ab72eb9);struct zd84195416f*z1b752e214a=
z048da5e00c->z1b752e214a;unsigned int zf32c877095;bool zc7196d407f=false,
zfbe01eaa1f=false;unsigned long z05b7c9a580;if(unlikely(!z1b752e214a||!
z1b752e214a->zb6181247c7))return(0x1692+3440-0x2402);if(zf62b956761){z1b752e214a
->active_cpus=zbc04b417fa(z1b752e214a);z7e643441e5(z048da5e00c);}else{if(
z048da5e00c->z7f508cb38b){sched_unisolate_cpu_unlocked(z8f9ab72eb9);z048da5e00c
->z7f508cb38b=false;zfbe01eaa1f=true;}z7e643441e5(z048da5e00c);z048da5e00c->
z517f9bdd84=(0xdbd+3814-0x1ca3);z1b752e214a->active_cpus=zbc04b417fa(z1b752e214a
);}zf32c877095=za16d868f28(z1b752e214a,z1b752e214a->need_cpus);spin_lock_irqsave
(&z78e2cdac9a,z05b7c9a580);if(zfbe01eaa1f)z1b752e214a->zd76a53732a--;zc7196d407f
=z05c5275688(z1b752e214a,zf32c877095);spin_unlock_irqrestore(&z78e2cdac9a,
z05b7c9a580);if(zc7196d407f)ze68f5dd857(z1b752e214a);return(0x364+1588-0x998);}
static int z32859df63c(unsigned int z8f9ab72eb9){return z7641504060(z8f9ab72eb9,
true);}static int z182ef3e766(unsigned int z8f9ab72eb9){return z7641504060(
z8f9ab72eb9,false);}static struct zd84195416f*zd5d0009aa2(unsigned int 
z76f375774d){unsigned int z5d971be8b8;for(z5d971be8b8=(0xc3a+4513-0x1ddb);
z5d971be8b8<z3480a8e71f;++z5d971be8b8){if(z9a7bdf60eb[z5d971be8b8].z76f375774d==
z76f375774d)return&z9a7bdf60eb[z5d971be8b8];}return NULL;}static int zfec3515cc6
(const struct cpumask*zdf9caaa1ec){struct device*zf018520c69;unsigned int 
z76f375774d=cpumask_first(zdf9caaa1ec);struct zd84195416f*z1b752e214a;struct 
z722543f60e*z048da5e00c;unsigned int z8f9ab72eb9;struct sched_param z88d2ec5be5=
{.sched_priority=MAX_RT_PRIO-(0xc89+2149-0x14ed)};if(zd5d0009aa2(z76f375774d))
return(0xd66+1942-0x14fc);zf018520c69=get_cpu_device(z76f375774d);if(!
zf018520c69)return-ENODEV;pr_info(
"\x43\x72\x65\x61\x74\x69\x6e\x67\x20\x43\x50\x55\x20\x67\x72\x6f\x75\x70\x20\x25\x64" "\n"
,z76f375774d);if(z3480a8e71f==MAX_CLUSTERS){pr_err(
"\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x63\x6c\x75\x73\x74\x65\x72\x73\x2e\x20\x4f\x6e\x6c\x79\x20\x25\x75\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64" "\n"
,MAX_CLUSTERS);return-EINVAL;}z1b752e214a=&z9a7bdf60eb[z3480a8e71f];++
z3480a8e71f;cpumask_copy(&z1b752e214a->z39abd1de52,zdf9caaa1ec);z1b752e214a->
z3fc386a32e=cpumask_weight(zdf9caaa1ec);if(z1b752e214a->z3fc386a32e>
MAX_CPUS_PER_CLUSTER){pr_err(
"\x48\x57\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69\x6f\x6e\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64" "\n"
);return-EINVAL;}z1b752e214a->z76f375774d=z76f375774d;z1b752e214a->min_cpus=
(0x8f2+7154-0x24e3);z1b752e214a->max_cpus=z1b752e214a->z3fc386a32e;z1b752e214a->
need_cpus=z1b752e214a->z3fc386a32e;z1b752e214a->offline_delay_ms=
(0x1011+3800-0x1e85);z1b752e214a->task_thres=UINT_MAX;z1b752e214a->
nr_prev_assist_thresh=UINT_MAX;z1b752e214a->z78602fc8a3=z1b752e214a->z3fc386a32e
;z1b752e214a->enable=true;z1b752e214a->z9656065c1c=(0xebd+2137-0x1716);
z1b752e214a->zcc9821f091=(0xfc0+3173-0x1c25);INIT_LIST_HEAD(&z1b752e214a->
z895ecc2391);spin_lock_init(&z1b752e214a->zffb20e4808);for_each_cpu(z8f9ab72eb9,
zdf9caaa1ec){pr_info(
"\x49\x6e\x69\x74\x20\x43\x50\x55\x25\x75\x20\x73\x74\x61\x74\x65" "\n",
z8f9ab72eb9);z048da5e00c=&per_cpu(z22ef1845d7,z8f9ab72eb9);z048da5e00c->
z1b752e214a=z1b752e214a;z048da5e00c->z8f9ab72eb9=z8f9ab72eb9;list_add_tail(&
z048da5e00c->za7f3b2896c,&z1b752e214a->z895ecc2391);}z1b752e214a->active_cpus=
zbc04b417fa(z1b752e214a);z1b752e214a->z2e935f34a1=kthread_run(zcc8e90311b,(void*
)z1b752e214a,"\x63\x6f\x72\x65\x5f\x63\x74\x6c\x2f\x25\x64",z76f375774d);if(
IS_ERR(z1b752e214a->z2e935f34a1))return PTR_ERR(z1b752e214a->z2e935f34a1);
sched_setscheduler_nocheck(z1b752e214a->z2e935f34a1,SCHED_FIFO,&z88d2ec5be5);
z1b752e214a->zb6181247c7=true;kobject_init(&z1b752e214a->kobj,&ze314eed4f2);
return kobject_add(&z1b752e214a->kobj,&zf018520c69->kobj,
"\x63\x6f\x72\x65\x5f\x63\x74\x6c");}static int __init core_ctl_init(void){
struct sched_cluster*z1b752e214a;int z083920bcc8;cpuhp_setup_state_nocalls(
CPUHP_AP_ONLINE_DYN,
"\x63\x6f\x72\x65\x5f\x63\x74\x6c\x2f\x69\x73\x6f\x6c\x61\x74\x69\x6f\x6e\x3a\x6f\x6e\x6c\x69\x6e\x65"
,z32859df63c,NULL);cpuhp_setup_state_nocalls(CPUHP_CORE_CTL_ISOLATION_DEAD,
"\x63\x6f\x72\x65\x5f\x63\x74\x6c\x2f\x69\x73\x6f\x6c\x61\x74\x69\x6f\x6e\x3a\x64\x65\x61\x64"
,NULL,z182ef3e766);for_each_sched_cluster(z1b752e214a){z083920bcc8=zfec3515cc6(&
z1b752e214a->cpus);if(z083920bcc8)pr_warn(
"\x75\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x63\x72\x65\x61\x74\x65\x20\x63\x6f\x72\x65\x20\x63\x74\x6c\x20\x67\x72\x6f\x75\x70\x3a\x20\x25\x64" "\n"
,z083920bcc8);}z69be84bb38=true;return(0x195+841-0x4de);}late_initcall(
core_ctl_init);
