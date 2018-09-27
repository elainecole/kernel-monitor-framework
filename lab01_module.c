/*
 * lab01_module.c - SIngle Kernel Thread Timer Module
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

static struct task_struct *task; // holds pointer to task struct for module's kernel thread
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
    //struct task_struct *temp_curr = current;
    printk("labfunction is still running with itr %d, nvcsw %lu, nivcsw %lu\n", counter, current->nvcsw, current->nivcsw);
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
  wake_up_process(task); // wake up kernel thread
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
  task = kthread_run(labfunction, NULL, "mythread"); // spawn a kernel thread and store result in task
  hrtimer_start(&timer, interval,HRTIMER_MODE_REL);
  return 0;
}

/*
 * lab01_module_exit - the exit function, called when the module is removed.
 */
static void __exit lab01_module_exit(void) {
  printk("exiting\n");
  kthread_stop(task); // alerts thread that it should cease execution
  hrtimer_cancel(&timer);
}

module_init(lab01_module_init);
module_exit(lab01_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Elaine Cole, Jesse Huang, Zhengliang Liu");
MODULE_DESCRIPTION("Time Module");
