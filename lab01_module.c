#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/timer.h>
#include <linux/syslog.h>
#include <linux/kthread.h>
#include <linux/sched.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Elaine Cole, Jesse Huang, Zhengliang Liu");
MODULE_DESCRIPTION("TIMER MODULE");

static struct task_struct *task;
static ulong log_sec = 1;
static ulong log_nsec = 0; // What to put here? Is the time sec + nsec?
module_param(log_sec, ulong, 0);
module_param(log_nsec, ulong, 0);

static ktime_t interval;
static struct hrtimer timer;

int counter;
static int labfunction(void *something)
{
printk("labfunction is running");
counter = 0;
while(!kthread_should_stop())
{
//struct task_struct *temp_curr = current; //global macro
printk("labfunction is still running with itr %d, nvcsw %lu, nivcsw %lu\n", counter, current->nvcsw, current->nivcsw);
++counter;

set_current_state(TASK_INTERRUPTIBLE);
schedule();
}
printk("labfunction stopped");
return 0;
}

enum hrtimer_restart nextcall(struct hrtimer *some_timer)
{
printk("timer is working");
wake_up_process(task);
hrtimer_forward_now(some_timer, interval);
return HRTIMER_RESTART;
}



static int __init lab01_module_init(void)
{

interval = ktime_set(log_sec, log_nsec);
hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
timer.function = &nextcall;
task = kthread_run(labfunction,NULL,"mythread");
hrtimer_start(&timer, interval,HRTIMER_MODE_REL); 
return 0;
}

static void __exit lab01_module_exit(void)
{
printk("exiting");
kthread_stop(task);
hrtimer_cancel(&timer);

}

module_init(lab01_module_init);
module_exit(lab01_module_exit);
