/*
 * mt_lab01_module.c - Multi-Thread Kernel Timer Module
 */

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

// pointers to task structs for module's kernel threads:
static struct task_struct *task;
static struct task_struct *task2;
static struct task_struct *task3;
static struct task_struct *task4;

static ulong log_sec = 1; // seconds, set timer defaults to expiring once every second
static ulong log_nsec = 0; // nanoseconds
module_param(log_sec, ulong, 0);
module_param(log_nsec, ulong, 0);

static ktime_t interval;
static struct hrtimer timer;

int counter;

/*
 * labfunction - runs in one or more kernel threads when they are spawned by the module.
 *  Returns 0 if completed successfully.
 */
static int labfunction(void *something) {
  printk("labfunction is running\n");
  counter = 0;
  while(!kthread_should_stop()) {
    //struct task_struct *temp_curr = current; //global macro
    printk("labfunction is still running with processor %d,  itr %d, nvcsw %lu, nivcsw %lu\n",smp_processor_id(), counter, current->nvcsw, current->nivcsw);
    ++counter;

    set_current_state(TASK_INTERRUPTIBLE);
    schedule(); // suspend its execution until another piece of code wakes it up
  }
  printk("labfunction stopped\n");
  return 0;
}

/*
 * nextcall - timer expiration function
 */
enum hrtimer_restart nextcall(struct hrtimer *some_timer) {
  printk("timer is working\n");
  // wake up kernel threads:
  wake_up_process(task);
  wake_up_process(task2);
  wake_up_process(task3);
  wake_up_process(task4);

  hrtimer_forward_now(some_timer, interval);
  return HRTIMER_RESTART;
}

/*
 * lab01_module_init - the init function, called when the module is loaded.
 *  Returns zero if successfully loaded, nonzero otherwise.
 */
static int __init lab01_module_init(void) {
  interval = ktime_set(log_sec, log_nsec);
  hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
  timer.function = &nextcall;
  //task = kthread_run(labfunction,NULL,"mythread");
  task = kthread_create(labfunction, NULL, "mythread");
  task2 = kthread_create(labfunction, NULL, "mythread2");
  task3 = kthread_create(labfunction, NULL, "mythread3");
  task4 = kthread_create(labfunction, NULL, "mythread4");

  kthread_bind(task,0);
  kthread_bind(task2,1);
  kthread_bind(task3,2);
  kthread_bind(task4,3);

  hrtimer_start(&timer, interval,HRTIMER_MODE_REL);
  return 0;
}

/*
 * lab01_module_exit - the exit function, called when the module is removed.
 */
static void __exit lab01_module_exit(void) {
  printk("exiting\n");
  // alert threads that they should cease execution:
  kthread_stop(task);
  kthread_stop(task2);
  kthread_stop(task3);
  kthread_stop(task4);

  hrtimer_cancel(&timer);
}

module_init(lab01_module_init);
module_exit(lab01_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Elaine Cole, Jesse Huang, Zhengliang Liu");
MODULE_DESCRIPTION("Timer Module");
