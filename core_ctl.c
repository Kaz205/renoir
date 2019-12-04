// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019, The Linux Foundation. All rights reserved.
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
(0x525+2860-0x1050))return-EINVAL;z048da5e00c->min_cpus=min(zc94d3d8015,
z048da5e00c->max_cpus);cpuset_next(z048da5e00c);ze68f5dd857(z048da5e00c);return 
z33ea1b60d7;}static ssize_t show_min_cpus(const struct zd84195416f*z048da5e00c,
char*z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",
z048da5e00c->min_cpus);}static ssize_t store_max_cpus(struct zd84195416f*
z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015;
if(sscanf(z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=(0x3f9+8923-0x26d3))return-
EINVAL;zc94d3d8015=min(zc94d3d8015,z048da5e00c->z3fc386a32e);z048da5e00c->
max_cpus=zc94d3d8015;z048da5e00c->min_cpus=min(z048da5e00c->min_cpus,z048da5e00c
->max_cpus);cpuset_next(z048da5e00c);ze68f5dd857(z048da5e00c);return z33ea1b60d7
;}static ssize_t show_max_cpus(const struct zd84195416f*z048da5e00c,char*
z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",z048da5e00c->
max_cpus);}static ssize_t store_offline_delay_ms(struct zd84195416f*z048da5e00c,
const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015;if(sscanf(
z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=(0x1d01+1119-0x215f))return-EINVAL;
z048da5e00c->offline_delay_ms=zc94d3d8015;z041d9949cf(z048da5e00c);return 
z33ea1b60d7;}static ssize_t show_task_thres(const struct zd84195416f*z048da5e00c
,char*z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",
z048da5e00c->task_thres);}static ssize_t store_task_thres(struct zd84195416f*
z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015;
if(sscanf(z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=(0x3e7+1060-0x80a))return-
EINVAL;if(zc94d3d8015<z048da5e00c->z3fc386a32e)return-EINVAL;z048da5e00c->
task_thres=zc94d3d8015;z041d9949cf(z048da5e00c);return z33ea1b60d7;}static 
ssize_t show_nr_prev_assist_thresh(const struct zd84195416f*z048da5e00c,char*
z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",z048da5e00c->
nr_prev_assist_thresh);}static ssize_t store_nr_prev_assist_thresh(struct 
zd84195416f*z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int 
zc94d3d8015;if(sscanf(z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)!=
(0x11c1+196-0x1284))return-EINVAL;z048da5e00c->nr_prev_assist_thresh=zc94d3d8015
;z041d9949cf(z048da5e00c);return z33ea1b60d7;}static ssize_t 
show_offline_delay_ms(const struct zd84195416f*z048da5e00c,char*z33c5f8b4bc){
return snprintf(z33c5f8b4bc,PAGE_SIZE,"\x25\x75" "\n",z048da5e00c->
offline_delay_ms);}static ssize_t store_busy_up_thres(struct zd84195416f*
z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015[
MAX_CPUS_PER_CLUSTER];int z083920bcc8,z5d971be8b8;z083920bcc8=sscanf(z33c5f8b4bc
,"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
zc94d3d8015[(0x1130+3870-0x204e)],&zc94d3d8015[(0x15+1035-0x41f)],&zc94d3d8015[
(0x5b1+1172-0xa43)],&zc94d3d8015[(0x20ab+570-0x22e2)],&zc94d3d8015[
(0xd1a+1307-0x1231)],&zc94d3d8015[(0x2351+463-0x251b)]);if(z083920bcc8!=
(0x2d8+3914-0x1221)&&z083920bcc8!=z048da5e00c->z3fc386a32e)return-EINVAL;if(
z083920bcc8==(0xa34+895-0xdb2)){for(z5d971be8b8=(0x96b+4348-0x1a67);z5d971be8b8<
z048da5e00c->z3fc386a32e;z5d971be8b8++)z048da5e00c->busy_up_thres[z5d971be8b8]=
zc94d3d8015[(0x164+1492-0x738)];}else{for(z5d971be8b8=(0x2bc+6871-0x1d93);
z5d971be8b8<z048da5e00c->z3fc386a32e;z5d971be8b8++)z048da5e00c->busy_up_thres[
z5d971be8b8]=zc94d3d8015[z5d971be8b8];}z041d9949cf(z048da5e00c);return 
z33ea1b60d7;}static ssize_t show_busy_up_thres(const struct zd84195416f*
z048da5e00c,char*z33c5f8b4bc){int z5d971be8b8,z33ea1b60d7=(0xae8+203-0xbb3);for(
z5d971be8b8=(0x337+3016-0xeff);z5d971be8b8<z048da5e00c->z3fc386a32e;z5d971be8b8
++)z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,
"\x25\x75\x20",z048da5e00c->busy_up_thres[z5d971be8b8]);z33ea1b60d7+=snprintf(
z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,"\n");return z33ea1b60d7;}static 
ssize_t store_busy_down_thres(struct zd84195416f*z048da5e00c,const char*
z33c5f8b4bc,size_t z33ea1b60d7){unsigned int zc94d3d8015[MAX_CPUS_PER_CLUSTER];
int z083920bcc8,z5d971be8b8;z083920bcc8=sscanf(z33c5f8b4bc,
"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
zc94d3d8015[(0x7e2+7577-0x257b)],&zc94d3d8015[(0x1d20+511-0x1f1e)],&zc94d3d8015[
(0xbd3+6672-0x25e1)],&zc94d3d8015[(0x131a+4953-0x2670)],&zc94d3d8015[
(0x9d2+1677-0x105b)],&zc94d3d8015[(0x22a+5514-0x17af)]);if(z083920bcc8!=
(0xfcf+1720-0x1686)&&z083920bcc8!=z048da5e00c->z3fc386a32e)return-EINVAL;if(
z083920bcc8==(0x437+8442-0x2530)){for(z5d971be8b8=(0x1b4f+2997-0x2704);
z5d971be8b8<z048da5e00c->z3fc386a32e;z5d971be8b8++)z048da5e00c->busy_down_thres[
z5d971be8b8]=zc94d3d8015[(0x20c0+1373-0x261d)];}else{for(z5d971be8b8=
(0x23a+2947-0xdbd);z5d971be8b8<z048da5e00c->z3fc386a32e;z5d971be8b8++)
z048da5e00c->busy_down_thres[z5d971be8b8]=zc94d3d8015[z5d971be8b8];}z041d9949cf(
z048da5e00c);return z33ea1b60d7;}static ssize_t show_busy_down_thres(const 
struct zd84195416f*z048da5e00c,char*z33c5f8b4bc){int z5d971be8b8,z33ea1b60d7=
(0x189b+2111-0x20da);for(z5d971be8b8=(0x1a85+1390-0x1ff3);z5d971be8b8<
z048da5e00c->z3fc386a32e;z5d971be8b8++)z33ea1b60d7+=snprintf(z33c5f8b4bc+
z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,"\x25\x75\x20",z048da5e00c->busy_down_thres[
z5d971be8b8]);z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-
z33ea1b60d7,"\n");return z33ea1b60d7;}static ssize_t store_enable(struct 
zd84195416f*z048da5e00c,const char*z33c5f8b4bc,size_t z33ea1b60d7){unsigned int 
zc94d3d8015;bool zd09cc5ef75;if(sscanf(z33c5f8b4bc,"\x25\x75" "\n",&zc94d3d8015)
!=(0x648+7495-0x238e))return-EINVAL;zd09cc5ef75=!!zc94d3d8015;if(zd09cc5ef75!=
z048da5e00c->enable){z048da5e00c->enable=zd09cc5ef75;z041d9949cf(z048da5e00c);}
return z33ea1b60d7;}static ssize_t show_enable(const struct zd84195416f*
z048da5e00c,char*z33c5f8b4bc){return scnprintf(z33c5f8b4bc,PAGE_SIZE,
"\x25\x75" "\n",z048da5e00c->enable);}static ssize_t show_need_cpus(const struct
 zd84195416f*z048da5e00c,char*z33c5f8b4bc){return snprintf(z33c5f8b4bc,PAGE_SIZE
,"\x25\x75" "\n",z048da5e00c->need_cpus);}static ssize_t show_active_cpus(const 
struct zd84195416f*z048da5e00c,char*z33c5f8b4bc){return snprintf(z33c5f8b4bc,
PAGE_SIZE,"\x25\x75" "\n",z048da5e00c->active_cpus);}static ssize_t 
show_global_state(const struct zd84195416f*z048da5e00c,char*z33c5f8b4bc){struct 
z722543f60e*ze2cca49edf;struct zd84195416f*z1b752e214a;ssize_t z33ea1b60d7=
(0xf3f+2297-0x1838);unsigned int z8f9ab72eb9;spin_lock_irq(&z78e2cdac9a);
for_each_possible_cpu(z8f9ab72eb9){ze2cca49edf=&per_cpu(z22ef1845d7,z8f9ab72eb9)
;z1b752e214a=ze2cca49edf->z1b752e214a;if(!z1b752e214a||!z1b752e214a->zb6181247c7
)continue;z33ea1b60d7+=snprintf(z33c5f8b4bc+z33ea1b60d7,PAGE_SIZE-z33ea1b60d7,
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
z05b7c9a580;int z083920bcc8;int z30bdc18e2b=(0xda6+5864-0x248e);z083920bcc8=
sscanf(z33c5f8b4bc,
"\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75\x20\x25\x75" "\n",&
zc94d3d8015[(0x1ebb+1179-0x2356)],&zc94d3d8015[(0x1f7d+1869-0x26c9)],&
zc94d3d8015[(0x833+7334-0x24d7)],&zc94d3d8015[(0x341+2966-0xed4)],&zc94d3d8015[
(0x1b17+656-0x1da3)],&zc94d3d8015[(0x1f8+6087-0x19ba)]);if(z083920bcc8!=
z048da5e00c->z3fc386a32e)return-EINVAL;spin_lock_irqsave(&z78e2cdac9a,
z05b7c9a580);for(z5d971be8b8=(0x4c1+2341-0xde6);z5d971be8b8<z048da5e00c->
z3fc386a32e;z5d971be8b8++){ze2cca49edf=&per_cpu(z22ef1845d7,z5d971be8b8+
z048da5e00c->z76f375774d);ze2cca49edf->not_preferred=zc94d3d8015[z5d971be8b8];
z30bdc18e2b+=!!zc94d3d8015[z5d971be8b8];}z048da5e00c->z9656065c1c=z30bdc18e2b;
spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);return z33ea1b60d7;}static 
ssize_t show_not_preferred(const struct zd84195416f*z048da5e00c,char*z33c5f8b4bc
){struct z722543f60e*ze2cca49edf;ssize_t z33ea1b60d7=(0x1c2b+1615-0x227a);
unsigned long z05b7c9a580;int z5d971be8b8;spin_lock_irqsave(&z78e2cdac9a,
z05b7c9a580);for(z5d971be8b8=(0xd01+1724-0x13bd);z5d971be8b8<z048da5e00c->
z3fc386a32e;z5d971be8b8++){ze2cca49edf=&per_cpu(z22ef1845d7,z5d971be8b8+
z048da5e00c->z76f375774d);z33ea1b60d7+=scnprintf(z33c5f8b4bc+z33ea1b60d7,
PAGE_SIZE-z33ea1b60d7,"\x43\x50\x55\x23\x25\x64\x3a\x20\x25\x75" "\n",
ze2cca49edf->z8f9ab72eb9,ze2cca49edf->not_preferred);}spin_unlock_irqrestore(&
z78e2cdac9a,z05b7c9a580);return z33ea1b60d7;}struct core_ctl_attr{struct 
attribute attr;ssize_t(*show)(const struct zd84195416f*,char*);ssize_t(*store)(
struct zd84195416f*,const char*,size_t z33ea1b60d7);};
#define core_ctl_attr_ro(zb25dfb9431)		\
static struct core_ctl_attr zb25dfb9431 =	\
__ATTR(zb25dfb9431, (0x129+2763-0xad0), show_##zb25dfb9431, NULL)
#define core_ctl_attr_rw(zb25dfb9431)			\
static struct core_ctl_attr zb25dfb9431 =		\
__ATTR(zb25dfb9431, (0x3d0+5557-0x17e1), show_##zb25dfb9431, store_##zb25dfb9431\
)
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
z1b752e214a;int z7cdf3ec737=(0x11a+6770-0x1b8c);z213747575e(z1b752e214a,
z6b2e94bfe7){for_each_cpu(z8f9ab72eb9,&z1b752e214a->z39abd1de52)z7cdf3ec737+=
z3d55024438[z8f9ab72eb9].nr;}return z7cdf3ec737;}static int z91003ac218(int 
z6b2e94bfe7){int z8f9ab72eb9;struct zd84195416f*z79d47a94b2;int z33128046d7=
(0x4c7+5680-0x1af7);if(z6b2e94bfe7==(0x4a4+7889-0x2375))return(0x313+1679-0x9a2)
;z79d47a94b2=&z9a7bdf60eb[z6b2e94bfe7-(0x5a4+7441-0x22b4)];for_each_cpu(
z8f9ab72eb9,&z79d47a94b2->z39abd1de52)z33128046d7+=z3d55024438[z8f9ab72eb9].
nr_misfit;return z33128046d7;}static int z4e9e6ae627(int z6b2e94bfe7){int 
z8f9ab72eb9;struct zd84195416f*z1b752e214a=&z9a7bdf60eb[z6b2e94bfe7];int 
zf368d5dcae=(0x19b5+1955-0x2158);for_each_cpu(z8f9ab72eb9,&z1b752e214a->
z39abd1de52)zf368d5dcae=max(zf368d5dcae,z3d55024438[z8f9ab72eb9].nr_max);return 
zf368d5dcae;}static int z9385e48bfe(int z6b2e94bfe7){int nr_big=
(0x1692+4203-0x26fd);int z8f9ab72eb9;struct zd84195416f*z1b752e214a=&z9a7bdf60eb
[z6b2e94bfe7];if(z6b2e94bfe7==(0x83b+4462-0x19a9)){for_each_cpu(z8f9ab72eb9,&
z1b752e214a->z39abd1de52)nr_big+=z3d55024438[z8f9ab72eb9].nr_misfit;}else{
for_each_cpu(z8f9ab72eb9,&z1b752e214a->z39abd1de52)nr_big+=z3d55024438[
z8f9ab72eb9].nr;}return nr_big;}static int z4d8e98122d(int z6b2e94bfe7){int 
zf32c877095=(0x12d1+2841-0x1dea);int z8f9ab72eb9;struct zd84195416f*z79d47a94b2;
if(z6b2e94bfe7==(0x1317+1818-0x1a31))return(0x646+7299-0x22c9);z6b2e94bfe7--;
z79d47a94b2=&z9a7bdf60eb[z6b2e94bfe7];if(z79d47a94b2->zd76a53732a)return
(0x1069+3634-0x1e9b);for_each_cpu(z8f9ab72eb9,&z79d47a94b2->z39abd1de52)
zf32c877095+=z3d55024438[z8f9ab72eb9].nr;zf32c877095+=z91003ac218(z6b2e94bfe7);
if(zf32c877095>z79d47a94b2->active_cpus)zf32c877095=zf32c877095-z79d47a94b2->
active_cpus;else zf32c877095=(0x728+6251-0x1f93);return zf32c877095;}static int 
zf3336414f3(int z6b2e94bfe7){int z8f9ab72eb9;struct zd84195416f*z1b752e214a;int 
z49c28541b7=(0x49d+2347-0xdc8);if(z6b2e94bfe7!=(0xd5b+5690-0x2395))return
(0x18aa+2992-0x245a);z213747575e(z1b752e214a,z6b2e94bfe7){int nr_scaled=
(0x9d2+3362-0x16f4);int active_cpus=z1b752e214a->active_cpus;for_each_cpu(
z8f9ab72eb9,&z1b752e214a->z39abd1de52)nr_scaled+=z3d55024438[z8f9ab72eb9].
nr_scaled;nr_scaled/=(0x17eb+3656-0x25cf);if(z6b2e94bfe7==(0x5df+7171-0x21e2))
z49c28541b7+=nr_scaled;else z49c28541b7+=max((0x12f3+923-0x168e),nr_scaled-
active_cpus);}return z49c28541b7;}static void z595408d471(void){struct 
zd84195416f*z1b752e214a;unsigned int z6b2e94bfe7=(0xbe0+3611-0x19fb);unsigned 
long z05b7c9a580;int zd8515de889=(0x18ff+5-0x1904);sched_get_nr_running_avg(
z3d55024438);spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);z213747575e(z1b752e214a
,z6b2e94bfe7){int z7cdf3ec737,z33128046d7;if(!z1b752e214a->zb6181247c7)continue;
z7cdf3ec737=z586cb87856(z6b2e94bfe7);z33128046d7=z91003ac218(z6b2e94bfe7);
z1b752e214a->z78602fc8a3=z7cdf3ec737+z33128046d7;z1b752e214a->zf368d5dcae=
z4e9e6ae627(z6b2e94bfe7);z1b752e214a->z263a14abab=z4d8e98122d(z6b2e94bfe7);
z1b752e214a->zcc9821f091=zf3336414f3(z6b2e94bfe7);trace_core_ctl_update_nr_need(
z1b752e214a->z76f375774d,z7cdf3ec737,z33128046d7,z1b752e214a->z78602fc8a3,
z1b752e214a->zf368d5dcae,z1b752e214a->z263a14abab);zd8515de889+=z9385e48bfe(
z6b2e94bfe7);}spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);z86ffcc7dfd=
zd8515de889;walt_rotation_checkpoint(zd8515de889);}
#define zc2db0febb0	(0x5a6+1198-0xa50)
static unsigned int z50b207ad6d(const struct zd84195416f*z1b752e214a,unsigned 
int zeadf56a7a3){if(z1b752e214a->z78602fc8a3>=z1b752e214a->task_thres)return 
z1b752e214a->z3fc386a32e;if(z1b752e214a->z263a14abab>=z1b752e214a->
nr_prev_assist_thresh)zeadf56a7a3=zeadf56a7a3+z1b752e214a->z263a14abab;if(
z1b752e214a->z78602fc8a3>zeadf56a7a3)zeadf56a7a3=zeadf56a7a3+
(0x16d5+4137-0x26fd);if(z1b752e214a->zf368d5dcae>zc2db0febb0)zeadf56a7a3=
zeadf56a7a3+(0xe6f+4354-0x1f70);if(zeadf56a7a3<z1b752e214a->zcc9821f091)
zeadf56a7a3=z1b752e214a->zcc9821f091;return zeadf56a7a3;}static unsigned int 
za16d868f28(const struct zd84195416f*z1b752e214a,unsigned int need_cpus){return 
min(max(z1b752e214a->min_cpus,need_cpus),z1b752e214a->max_cpus);}static unsigned
 int zbc04b417fa(const struct zd84195416f*z1b752e214a){return z1b752e214a->
z3fc386a32e-sched_isolate_count(&z1b752e214a->z39abd1de52,true);}static bool 
z375fa7adc6(const struct z722543f60e*z048da5e00c){return cpu_online(z048da5e00c
->z8f9ab72eb9)&&!cpu_isolated(z048da5e00c->z8f9ab72eb9);}static bool z05c5275688
(const struct zd84195416f*z1b752e214a,unsigned int zf32c877095){return(
zf32c877095<z1b752e214a->active_cpus||(zf32c877095>z1b752e214a->active_cpus&&
z1b752e214a->zd76a53732a));}static bool eval_need(struct zd84195416f*z1b752e214a
){unsigned long z05b7c9a580;struct z722543f60e*ze2cca49edf;unsigned int 
need_cpus=(0xa49+6678-0x245f),zefe45c244d,z8255d868d2;int z083920bcc8=
(0xc4a+1393-0x11bb);bool z11e2990555=false;unsigned int zeadf56a7a3;s64 
z2c53bb3f34,zcc63e644e4;if(unlikely(!z1b752e214a->zb6181247c7))return
(0x14f4+269-0x1601);spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);if(z1b752e214a->
boost||!z1b752e214a->enable){need_cpus=z1b752e214a->max_cpus;}else{z1b752e214a->
active_cpus=zbc04b417fa(z1b752e214a);z8255d868d2=z1b752e214a->active_cpus?
z1b752e214a->active_cpus-(0xf83+4932-0x22c6):(0x903+6913-0x2404);
list_for_each_entry(ze2cca49edf,&z1b752e214a->z895ecc2391,za7f3b2896c){bool 
z28dac86562=ze2cca49edf->z087db4d18a;if(ze2cca49edf->z517f9bdd84>=z1b752e214a->
busy_up_thres[z8255d868d2]||sched_cpu_high_irqload(ze2cca49edf->z8f9ab72eb9))
ze2cca49edf->z087db4d18a=true;else if(ze2cca49edf->z517f9bdd84<z1b752e214a->
busy_down_thres[z8255d868d2])ze2cca49edf->z087db4d18a=false;
trace_core_ctl_set_busy(ze2cca49edf->z8f9ab72eb9,ze2cca49edf->z517f9bdd84,
z28dac86562,ze2cca49edf->z087db4d18a);need_cpus+=ze2cca49edf->z087db4d18a;}
need_cpus=z50b207ad6d(z1b752e214a,need_cpus);}zeadf56a7a3=za16d868f28(
z1b752e214a,need_cpus);z11e2990555=z05c5275688(z1b752e214a,zeadf56a7a3);
zefe45c244d=z1b752e214a->need_cpus;z2c53bb3f34=ktime_to_ms(ktime_get());if(
zeadf56a7a3>z1b752e214a->active_cpus){z083920bcc8=(0xc06+6510-0x2573);}else{if(
zeadf56a7a3==zefe45c244d&&zeadf56a7a3==z1b752e214a->active_cpus){z1b752e214a->
z474287bcf5=z2c53bb3f34;spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);return
(0x619+6937-0x2132);}zcc63e644e4=z2c53bb3f34-z1b752e214a->z474287bcf5;
z083920bcc8=zcc63e644e4>=z1b752e214a->offline_delay_ms;}if(z083920bcc8){
z1b752e214a->z474287bcf5=z2c53bb3f34;z1b752e214a->need_cpus=zeadf56a7a3;}
trace_core_ctl_eval_need(z1b752e214a->z76f375774d,zefe45c244d,zeadf56a7a3,
z083920bcc8&&z11e2990555);spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);
return z083920bcc8&&z11e2990555;}static void z041d9949cf(struct zd84195416f*
z1b752e214a){if(eval_need(z1b752e214a))ze68f5dd857(z1b752e214a);}static void 
ze68f5dd857(struct zd84195416f*z1b752e214a){unsigned long z05b7c9a580;
spin_lock_irqsave(&z1b752e214a->zffb20e4808,z05b7c9a580);z1b752e214a->
za280f52f04=true;spin_unlock_irqrestore(&z1b752e214a->zffb20e4808,z05b7c9a580);
wake_up_process(z1b752e214a->z2e935f34a1);}static u64 zdfa13d72c3;int 
core_ctl_set_boost(bool boost){unsigned int z6b2e94bfe7=(0x54b+2376-0xe93);
struct zd84195416f*z1b752e214a;unsigned long z05b7c9a580;int z083920bcc8=
(0xaf1+1055-0xf10);bool z37066d5eec=false;if(unlikely(!z69be84bb38))return
(0x1714+1268-0x1c08);spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);z213747575e(
z1b752e214a,z6b2e94bfe7){if(boost){z37066d5eec=!z1b752e214a->boost;++z1b752e214a
->boost;}else{if(!z1b752e214a->boost){z083920bcc8=-EINVAL;break;}else{--
z1b752e214a->boost;z37066d5eec=!z1b752e214a->boost;}}}spin_unlock_irqrestore(&
z78e2cdac9a,z05b7c9a580);if(z37066d5eec){z6b2e94bfe7=(0xfc8+900-0x134c);
z213747575e(z1b752e214a,z6b2e94bfe7)z041d9949cf(z1b752e214a);}
trace_core_ctl_set_boost(z1b752e214a->boost,z083920bcc8);return z083920bcc8;}
EXPORT_SYMBOL(core_ctl_set_boost);void core_ctl_notifier_register(struct 
notifier_block*zfe5c53f6bd){atomic_notifier_chain_register(&ze24f5fc06e,
zfe5c53f6bd);}void core_ctl_notifier_unregister(struct notifier_block*
zfe5c53f6bd){atomic_notifier_chain_unregister(&ze24f5fc06e,zfe5c53f6bd);}static 
void z521764ce34(void){struct core_ctl_notif_data z89bf9aac81={
(0x129+6717-0x1b66)};struct notifier_block*z9e976b309a;rcu_read_lock();
z9e976b309a=rcu_dereference_raw(ze24f5fc06e.head);rcu_read_unlock();if(!
z9e976b309a)return;z89bf9aac81.nr_big=z86ffcc7dfd;walt_fill_ta_data(&z89bf9aac81
);trace_core_ctl_notif_data(z89bf9aac81.nr_big,z89bf9aac81.coloc_load_pct,
z89bf9aac81.ta_util_pct,z89bf9aac81.cur_cap_pct);atomic_notifier_call_chain(&
ze24f5fc06e,(0x1a00+923-0x1d9b),&z89bf9aac81);}void core_ctl_check(u64 
zd872303760){int z8f9ab72eb9;struct z722543f60e*ze2cca49edf;struct zd84195416f*
z1b752e214a;unsigned int z6b2e94bfe7=(0x966+5610-0x1f50);unsigned long 
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
z3fc386a32e=z1b752e214a->z3fc386a32e;unsigned int z3407f2d0ae=(0xe33+335-0xf82);
bool z23fe99670b=z1b752e214a->z9656065c1c;spin_lock_irqsave(&z78e2cdac9a,
z05b7c9a580);list_for_each_entry_safe(ze2cca49edf,zb9b0dca770,&z1b752e214a->
z895ecc2391,za7f3b2896c){if(!z3fc386a32e--)break;if(!z375fa7adc6(ze2cca49edf))
continue;if(z1b752e214a->active_cpus==zf32c877095)break;if(ze2cca49edf->
z087db4d18a)continue;if(z1b752e214a->z9656065c1c&&!ze2cca49edf->not_preferred)
continue;if(!z25bcd77821(ze2cca49edf->z8f9ab72eb9,z1b752e214a))continue;
spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);pr_debug(
"\x54\x72\x79\x69\x6e\x67\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,ze2cca49edf->z8f9ab72eb9);if(!sched_isolate_cpu(ze2cca49edf->z8f9ab72eb9)){
ze2cca49edf->z7f508cb38b=true;z7e643441e5(ze2cca49edf);z3407f2d0ae++;}else{
pr_debug(
"\x55\x6e\x61\x62\x6c\x65\x20\x74\x6f\x20\x69\x73\x6f\x6c\x61\x74\x65\x20\x43\x50\x55\x25\x75" "\n"
,ze2cca49edf->z8f9ab72eb9);}z1b752e214a->active_cpus=zbc04b417fa(z1b752e214a);
spin_lock_irqsave(&z78e2cdac9a,z05b7c9a580);}z1b752e214a->zd76a53732a+=
z3407f2d0ae;spin_unlock_irqrestore(&z78e2cdac9a,z05b7c9a580);zcd588e3717:if(
z1b752e214a->active_cpus<=z1b752e214a->max_cpus)return;z3407f2d0ae=
(0x195+2360-0xacd);z3fc386a32e=z1b752e214a->z3fc386a32e;spin_lock_irqsave(&
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
unsigned int za857c3409b=(0x6d2+710-0x998);spin_lock_irqsave(&z78e2cdac9a,
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
unsigned long z05b7c9a580;while((0x6dd+7368-0x23a4)){set_current_state(
TASK_INTERRUPTIBLE);spin_lock_irqsave(&z1b752e214a->zffb20e4808,z05b7c9a580);if(
!z1b752e214a->za280f52f04){spin_unlock_irqrestore(&z1b752e214a->zffb20e4808,
z05b7c9a580);schedule();if(kthread_should_stop())break;spin_lock_irqsave(&
z1b752e214a->zffb20e4808,z05b7c9a580);}set_current_state(TASK_RUNNING);
z1b752e214a->za280f52f04=false;spin_unlock_irqrestore(&z1b752e214a->zffb20e4808,
z05b7c9a580);z5b4f389aad(z1b752e214a);}return(0x187+2450-0xb19);}static int 
z7641504060(unsigned int z8f9ab72eb9,bool zf62b956761){struct z722543f60e*
z048da5e00c=&per_cpu(z22ef1845d7,z8f9ab72eb9);struct zd84195416f*z1b752e214a=
z048da5e00c->z1b752e214a;unsigned int zf32c877095;bool zc7196d407f=false,
zfbe01eaa1f=false;unsigned long z05b7c9a580;if(unlikely(!z1b752e214a||!
z1b752e214a->zb6181247c7))return(0x20b+2670-0xc79);if(zf62b956761){z1b752e214a->
active_cpus=zbc04b417fa(z1b752e214a);z7e643441e5(z048da5e00c);}else{if(
z048da5e00c->z7f508cb38b){sched_unisolate_cpu_unlocked(z8f9ab72eb9);z048da5e00c
->z7f508cb38b=false;zfbe01eaa1f=true;}z7e643441e5(z048da5e00c);z048da5e00c->
z517f9bdd84=(0x1fa2+941-0x234f);z1b752e214a->active_cpus=zbc04b417fa(z1b752e214a
);}zf32c877095=za16d868f28(z1b752e214a,z1b752e214a->need_cpus);spin_lock_irqsave
(&z78e2cdac9a,z05b7c9a580);if(zfbe01eaa1f)z1b752e214a->zd76a53732a--;zc7196d407f
=z05c5275688(z1b752e214a,zf32c877095);spin_unlock_irqrestore(&z78e2cdac9a,
z05b7c9a580);if(zc7196d407f)ze68f5dd857(z1b752e214a);return(0x509+4231-0x1590);}
static int z32859df63c(unsigned int z8f9ab72eb9){return z7641504060(z8f9ab72eb9,
true);}static int z182ef3e766(unsigned int z8f9ab72eb9){return z7641504060(
z8f9ab72eb9,false);}static struct zd84195416f*zd5d0009aa2(unsigned int 
z76f375774d){unsigned int z5d971be8b8;for(z5d971be8b8=(0xbd0+3226-0x186a);
z5d971be8b8<z3480a8e71f;++z5d971be8b8){if(z9a7bdf60eb[z5d971be8b8].z76f375774d==
z76f375774d)return&z9a7bdf60eb[z5d971be8b8];}return NULL;}static int zfec3515cc6
(const struct cpumask*zdf9caaa1ec){struct device*zf018520c69;unsigned int 
z76f375774d=cpumask_first(zdf9caaa1ec);struct zd84195416f*z1b752e214a;struct 
z722543f60e*z048da5e00c;unsigned int z8f9ab72eb9;struct sched_param z88d2ec5be5=
{.sched_priority=MAX_RT_PRIO-(0x15d+5885-0x1859)};if(zd5d0009aa2(z76f375774d))
return(0x10fd+5031-0x24a4);zf018520c69=get_cpu_device(z76f375774d);if(!
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
(0x232+8995-0x2554);z1b752e214a->max_cpus=z1b752e214a->z3fc386a32e;z1b752e214a->
need_cpus=z1b752e214a->z3fc386a32e;z1b752e214a->offline_delay_ms=
(0xa79+766-0xd13);z1b752e214a->task_thres=UINT_MAX;z1b752e214a->
nr_prev_assist_thresh=UINT_MAX;z1b752e214a->z78602fc8a3=z1b752e214a->z3fc386a32e
;z1b752e214a->enable=true;z1b752e214a->z9656065c1c=(0x9+9131-0x23b4);z1b752e214a
->zcc9821f091=(0x9f3+1692-0x108f);INIT_LIST_HEAD(&z1b752e214a->z895ecc2391);
spin_lock_init(&z1b752e214a->zffb20e4808);for_each_cpu(z8f9ab72eb9,zdf9caaa1ec){
pr_info("\x49\x6e\x69\x74\x20\x43\x50\x55\x25\x75\x20\x73\x74\x61\x74\x65" "\n",
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
,z083920bcc8);}z69be84bb38=true;return(0x12d9+4006-0x227f);}late_initcall(
core_ctl_init);
