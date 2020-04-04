// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#define pr_fmt(WALTc4af4bede1) "\x63\x70\x75\x2d\x62\x6f\x6f\x73\x74\x3a\x20" \
WALTc4af4bede1
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cpufreq.h>
#include <linux/cpu.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/time.h>
#include <linux/sysfs.h>
#include <linux/pm_qos.h>
#include "walt.h"
#define cpu_boost_attr_rw(WALTb25dfb9431)		\
static struct kobj_attribute WALTb25dfb9431##_attr =	\
__ATTR(WALTb25dfb9431, (0x1331+3755-0x2038), show_##WALTb25dfb9431, store_##\
WALTb25dfb9431)
#define WALT4fd2c65c70(WALT424312941f)			\
static ssize_t show_##WALT424312941f			\
(struct kobject *kobj, struct kobj_attribute *attr, char *WALT33c5f8b4bc)	\
{								\
	return scnprintf(WALT33c5f8b4bc, PAGE_SIZE, "\x25\x75" "\n", WALT424312941f);	\
}
#define WALT110aa7e285(WALT424312941f)					\
static ssize_t store_##WALT424312941f				\
(struct kobject *kobj, struct kobj_attribute *attr,		\
const char *WALT33c5f8b4bc, size_t WALT33ea1b60d7)					\
{								\
								\
	sscanf(WALT33c5f8b4bc, "\x25\x75", &WALT424312941f);				\
	return WALT33ea1b60d7;						\
}
struct WALTce6d56b8bb{int cpu;unsigned int input_boost_min;unsigned int 
input_boost_freq;};static DEFINE_PER_CPU(struct WALTce6d56b8bb,WALTdd15390acf);
static struct workqueue_struct*WALT9762523439;static struct work_struct 
WALT22a243569d;static bool WALT9f1a9f39a2;static unsigned int input_boost_ms=
(0x16d+2026-0x92f);WALT4fd2c65c70(input_boost_ms);WALT110aa7e285(input_boost_ms)
;cpu_boost_attr_rw(input_boost_ms);static unsigned int sched_boost_on_input;
WALT4fd2c65c70(sched_boost_on_input);WALT110aa7e285(sched_boost_on_input);
cpu_boost_attr_rw(sched_boost_on_input);static bool WALT83486149e3;static struct
 delayed_work WALTe22e8298ec;static u64 WALT4ecacf5b3e;
#define MIN_INPUT_INTERVAL ((0x199+439-0x2ba) * USEC_PER_MSEC)
static DEFINE_PER_CPU(struct freq_qos_request,WALTb79580c5cb);static ssize_t 
store_input_boost_freq(struct kobject*kobj,struct kobj_attribute*attr,const char
*WALT33c5f8b4bc,size_t WALT33ea1b60d7){int WALT5d971be8b8,WALT363309dafd=
(0x148b+1878-0x1be1);unsigned int WALTc94d3d8015,cpu;const char*WALT55398c375d=
WALT33c5f8b4bc;bool WALT097cdda7e5=false;while((WALT55398c375d=strpbrk(
WALT55398c375d+(0x1d3c+1474-0x22fd),"\x20\x3a")))WALT363309dafd++;if(!
WALT363309dafd){if(sscanf(WALT33c5f8b4bc,"\x25\x75" "\n",&WALTc94d3d8015)!=
(0xef4+3292-0x1bcf))return-EINVAL;for_each_possible_cpu(WALT5d971be8b8)per_cpu(
WALTdd15390acf,WALT5d971be8b8).input_boost_freq=WALTc94d3d8015;goto 
WALT94baffc55b;}if(!(WALT363309dafd%(0x9fd+4631-0x1c12)))return-EINVAL;
WALT55398c375d=WALT33c5f8b4bc;for(WALT5d971be8b8=(0x113b+5012-0x24cf);
WALT5d971be8b8<WALT363309dafd;WALT5d971be8b8+=(0xa36+6768-0x24a4)){if(sscanf(
WALT55398c375d,"\x25\x75\x3a\x25\x75",&cpu,&WALTc94d3d8015)!=
(0x189c+3431-0x2601))return-EINVAL;if(cpu>=num_possible_cpus())return-EINVAL;
per_cpu(WALTdd15390acf,cpu).input_boost_freq=WALTc94d3d8015;WALT55398c375d=
strnchr(WALT55398c375d,PAGE_SIZE-(WALT55398c375d-WALT33c5f8b4bc),
((char)(0xf53+3856-0x1e43)));WALT55398c375d++;}WALT94baffc55b:
for_each_possible_cpu(WALT5d971be8b8){if(per_cpu(WALTdd15390acf,WALT5d971be8b8).
input_boost_freq){WALT097cdda7e5=true;break;}}WALT9f1a9f39a2=WALT097cdda7e5;
return WALT33ea1b60d7;}static ssize_t show_input_boost_freq(struct kobject*kobj,
struct kobj_attribute*attr,char*WALT33c5f8b4bc){int WALTb5bf6cca69=
(0x247b+240-0x256b),cpu;struct WALTce6d56b8bb*WALTe4d1b656b7;
for_each_possible_cpu(cpu){WALTe4d1b656b7=&per_cpu(WALTdd15390acf,cpu);
WALTb5bf6cca69+=snprintf(WALT33c5f8b4bc+WALTb5bf6cca69,PAGE_SIZE-WALTb5bf6cca69,
"\x25\x64\x3a\x25\x75\x20",cpu,WALTe4d1b656b7->input_boost_freq);}WALTb5bf6cca69
+=snprintf(WALT33c5f8b4bc+WALTb5bf6cca69,PAGE_SIZE-WALTb5bf6cca69,"\n");return 
WALTb5bf6cca69;}cpu_boost_attr_rw(input_boost_freq);static void WALT31eba71b41(
struct cpufreq_policy*WALT17deffe12c){unsigned int cpu=WALT17deffe12c->cpu;
struct WALTce6d56b8bb*WALTe4d1b656b7=&per_cpu(WALTdd15390acf,cpu);unsigned int 
WALTd51b8e5a9b=WALTe4d1b656b7->input_boost_min;struct freq_qos_request*
WALTb23a3d9940=&per_cpu(WALTb79580c5cb,cpu);int WALT083920bcc8;pr_debug(
"\x43\x50\x55\x25\x75\x20\x70\x6f\x6c\x69\x63\x79\x20\x6d\x69\x6e\x20\x62\x65\x66\x6f\x72\x65\x20\x62\x6f\x6f\x73\x74\x3a\x20\x25\x75\x20\x6b\x48\x7a" "\n"
,cpu,WALT17deffe12c->min);pr_debug(
"\x43\x50\x55\x25\x75\x20\x62\x6f\x6f\x73\x74\x20\x6d\x69\x6e\x3a\x20\x25\x75\x20\x6b\x48\x7a" "\n"
,cpu,WALTd51b8e5a9b);WALT083920bcc8=freq_qos_update_request(WALTb23a3d9940,
WALTd51b8e5a9b);if(WALT083920bcc8<(0x12d3+193-0x1394))pr_err(
"\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x75\x70\x64\x61\x74\x65\x20\x66\x72\x65\x71\x20\x63\x6f\x6e\x73\x74\x72\x61\x69\x6e\x74\x20\x69\x6e\x20\x62\x6f\x6f\x73\x74\x5f\x61\x64\x6a\x75\x73\x74\x3a\x20\x25\x64" "\n"
,WALTd51b8e5a9b);pr_debug(
"\x43\x50\x55\x25\x75\x20\x70\x6f\x6c\x69\x63\x79\x20\x6d\x69\x6e\x20\x61\x66\x74\x65\x72\x20\x62\x6f\x6f\x73\x74\x3a\x20\x25\x75\x20\x6b\x48\x7a" "\n"
,cpu,WALT17deffe12c->min);return;}static void WALT5368534a89(void){unsigned int 
WALT5d971be8b8;struct cpufreq_policy*WALT17deffe12c;struct cpumask 
WALT11da203bbd;get_online_cpus();WALT11da203bbd=*cpu_online_mask;for_each_cpu(
WALT5d971be8b8,&WALT11da203bbd){WALT17deffe12c=cpufreq_cpu_get(WALT5d971be8b8);
if(!WALT17deffe12c){pr_err(
"\x25\x73\x3a\x20\x63\x70\x75\x66\x72\x65\x71\x20\x70\x6f\x6c\x69\x63\x79\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64\x20\x66\x6f\x72\x20\x63\x70\x75\x25\x64" "\n"
,__func__,WALT5d971be8b8);return;}cpumask_andnot(&WALT11da203bbd,&WALT11da203bbd
,WALT17deffe12c->related_cpus);WALT31eba71b41(WALT17deffe12c);}put_online_cpus()
;}static void WALT95de59aedd(struct work_struct*WALT9932a7275f){unsigned int 
WALT5d971be8b8,WALT083920bcc8;struct WALTce6d56b8bb*WALT460c0e8c37;pr_debug(
"\x52\x65\x73\x65\x74\x74\x69\x6e\x67\x20\x69\x6e\x70\x75\x74\x20\x62\x6f\x6f\x73\x74\x20\x6d\x69\x6e\x20\x66\x6f\x72\x20\x61\x6c\x6c\x20\x43\x50\x55\x73" "\n"
);for_each_possible_cpu(WALT5d971be8b8){WALT460c0e8c37=&per_cpu(WALTdd15390acf,
WALT5d971be8b8);WALT460c0e8c37->input_boost_min=(0x18d1+2792-0x23b9);}
WALT5368534a89();if(WALT83486149e3){WALT083920bcc8=sched_set_boost(
(0x485+5812-0x1b39));if(WALT083920bcc8)pr_err(
"\x63\x70\x75\x2d\x62\x6f\x6f\x73\x74\x3a\x20\x73\x63\x68\x65\x64\x20\x62\x6f\x6f\x73\x74\x20\x64\x69\x73\x61\x62\x6c\x65\x20\x66\x61\x69\x6c\x65\x64" "\n"
);WALT83486149e3=false;}}static void WALT1ee1f01166(struct work_struct*
WALT9932a7275f){unsigned int WALT5d971be8b8,WALT083920bcc8;struct WALTce6d56b8bb
*WALT460c0e8c37;cancel_delayed_work_sync(&WALTe22e8298ec);if(WALT83486149e3){
sched_set_boost((0x2422+235-0x250d));WALT83486149e3=false;}pr_debug(
"\x53\x65\x74\x74\x69\x6e\x67\x20\x69\x6e\x70\x75\x74\x20\x62\x6f\x6f\x73\x74\x20\x6d\x69\x6e\x20\x66\x6f\x72\x20\x61\x6c\x6c\x20\x43\x50\x55\x73" "\n"
);for_each_possible_cpu(WALT5d971be8b8){WALT460c0e8c37=&per_cpu(WALTdd15390acf,
WALT5d971be8b8);WALT460c0e8c37->input_boost_min=WALT460c0e8c37->input_boost_freq
;}WALT5368534a89();if(sched_boost_on_input>(0xf4a+3613-0x1d67)){WALT083920bcc8=
sched_set_boost(sched_boost_on_input);if(WALT083920bcc8)pr_err(
"\x63\x70\x75\x2d\x62\x6f\x6f\x73\x74\x3a\x20\x73\x63\x68\x65\x64\x20\x62\x6f\x6f\x73\x74\x20\x65\x6e\x61\x62\x6c\x65\x20\x66\x61\x69\x6c\x65\x64" "\n"
);else WALT83486149e3=true;}queue_delayed_work(WALT9762523439,&WALTe22e8298ec,
msecs_to_jiffies(input_boost_ms));}static void WALT0e336f2913(struct 
input_handle*WALTb773b2097d,unsigned int WALT3e92d20441,unsigned int 
WALT5a776a7d24,int WALT95e2f0a380){u64 WALT2c53bb3f34;if(!WALT9f1a9f39a2)return;
WALT2c53bb3f34=ktime_to_us(ktime_get());if(WALT2c53bb3f34-WALT4ecacf5b3e<
MIN_INPUT_INTERVAL)return;if(work_pending(&WALT22a243569d))return;queue_work(
WALT9762523439,&WALT22a243569d);WALT4ecacf5b3e=ktime_to_us(ktime_get());}static 
int WALT86ec8ceef6(struct input_handler*handler,struct input_dev*dev,const 
struct input_device_id*WALTb13beca266){struct input_handle*WALTb773b2097d;int 
error;WALTb773b2097d=kzalloc(sizeof(struct input_handle),GFP_KERNEL);if(!
WALTb773b2097d)return-ENOMEM;WALTb773b2097d->dev=dev;WALTb773b2097d->handler=
handler;WALTb773b2097d->name="\x63\x70\x75\x66\x72\x65\x71";error=
input_register_handle(WALTb773b2097d);if(error)goto WALT5b81047b49;error=
input_open_device(WALTb773b2097d);if(error)goto WALTeafa714acc;return
(0x989+1167-0xe18);WALTeafa714acc:input_unregister_handle(WALTb773b2097d);
WALT5b81047b49:kfree(WALTb773b2097d);return error;}static void WALT8758b5addd(
struct input_handle*WALTb773b2097d){input_close_device(WALTb773b2097d);
input_unregister_handle(WALTb773b2097d);kfree(WALTb773b2097d);}static const 
struct input_device_id WALT6a35b945c0[]={{.flags=INPUT_DEVICE_ID_MATCH_EVBIT|
INPUT_DEVICE_ID_MATCH_ABSBIT,.evbit={BIT_MASK(EV_ABS)},.absbit={[BIT_WORD(
ABS_MT_POSITION_X)]=BIT_MASK(ABS_MT_POSITION_X)|BIT_MASK(ABS_MT_POSITION_Y)},},{
.flags=INPUT_DEVICE_ID_MATCH_KEYBIT|INPUT_DEVICE_ID_MATCH_ABSBIT,.keybit={[
BIT_WORD(BTN_TOUCH)]=BIT_MASK(BTN_TOUCH)},.absbit={[BIT_WORD(ABS_X)]=BIT_MASK(
ABS_X)|BIT_MASK(ABS_Y)},},{.flags=INPUT_DEVICE_ID_MATCH_EVBIT,.evbit={BIT_MASK(
EV_KEY)},},{},};static struct input_handler WALT56003a1ee4={.event=
WALT0e336f2913,.connect=WALT86ec8ceef6,.disconnect=WALT8758b5addd,.name=
"\x63\x70\x75\x2d\x62\x6f\x6f\x73\x74",.id_table=WALT6a35b945c0,};struct kobject
*cpu_boost_kobj;static int WALTdeb0b46b63(void){int cpu,WALT083920bcc8;struct 
WALTce6d56b8bb*WALTe4d1b656b7;struct cpufreq_policy*WALT17deffe12c;struct 
freq_qos_request*WALTb23a3d9940;WALT9762523439=alloc_workqueue(
"\x63\x70\x75\x62\x6f\x6f\x73\x74\x5f\x77\x71",WQ_HIGHPRI,(0x3ba+2782-0xe98));if
(!WALT9762523439)return-EFAULT;INIT_WORK(&WALT22a243569d,WALT1ee1f01166);
INIT_DELAYED_WORK(&WALTe22e8298ec,WALT95de59aedd);for_each_possible_cpu(cpu){
WALTe4d1b656b7=&per_cpu(WALTdd15390acf,cpu);WALTe4d1b656b7->cpu=cpu;
WALTb23a3d9940=&per_cpu(WALTb79580c5cb,cpu);WALT17deffe12c=cpufreq_cpu_get(cpu);
if(!WALT17deffe12c){pr_err(
"\x25\x73\x3a\x20\x63\x70\x75\x66\x72\x65\x71\x20\x70\x6f\x6c\x69\x63\x79\x20\x6e\x6f\x74\x20\x66\x6f\x75\x6e\x64\x20\x66\x6f\x72\x20\x63\x70\x75\x25\x64" "\n"
,__func__,cpu);return-ESRCH;}WALT083920bcc8=freq_qos_add_request(&WALT17deffe12c
->constraints,WALTb23a3d9940,FREQ_QOS_MIN,WALT17deffe12c->min);if(WALT083920bcc8
<(0xde7+5171-0x221a)){pr_err(
"\x25\x73\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x61\x64\x64\x20\x66\x72\x65\x71\x20\x63\x6f\x6e\x73\x74\x72\x61\x69\x6e\x74\x20\x28\x25\x64\x29" "\n"
,__func__,WALT083920bcc8);return WALT083920bcc8;}}cpu_boost_kobj=
kobject_create_and_add("\x63\x70\x75\x5f\x62\x6f\x6f\x73\x74",&cpu_subsys.
dev_root->kobj);if(!cpu_boost_kobj)pr_err(
"\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x20\x73\x79\x73\x66\x73\x20\x6e\x6f\x64\x65\x20\x66\x6f\x72\x20\x63\x70\x75\x5f\x62\x6f\x6f\x73\x74\x2e" "\n"
);WALT083920bcc8=sysfs_create_file(cpu_boost_kobj,&input_boost_ms_attr.attr);if(
WALT083920bcc8)pr_err(
"\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x72\x65\x61\x74\x65\x20\x69\x6e\x70\x75\x74\x5f\x62\x6f\x6f\x73\x74\x5f\x6d\x73\x20\x6e\x6f\x64\x65\x3a\x20\x25\x64" "\n"
,WALT083920bcc8);WALT083920bcc8=sysfs_create_file(cpu_boost_kobj,&
input_boost_freq_attr.attr);if(WALT083920bcc8)pr_err(
"\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x72\x65\x61\x74\x65\x20\x69\x6e\x70\x75\x74\x5f\x62\x6f\x6f\x73\x74\x5f\x66\x72\x65\x71\x20\x6e\x6f\x64\x65\x3a\x20\x25\x64" "\n"
,WALT083920bcc8);WALT083920bcc8=sysfs_create_file(cpu_boost_kobj,&
sched_boost_on_input_attr.attr);if(WALT083920bcc8)pr_err(
"\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x72\x65\x61\x74\x65\x20\x73\x63\x68\x65\x64\x5f\x62\x6f\x6f\x73\x74\x5f\x6f\x6e\x5f\x69\x6e\x70\x75\x74\x20\x6e\x6f\x64\x65\x3a\x20\x25\x64" "\n"
,WALT083920bcc8);WALT083920bcc8=input_register_handler(&WALT56003a1ee4);return
(0x1b52+987-0x1f2d);}late_initcall(WALTdeb0b46b63);
