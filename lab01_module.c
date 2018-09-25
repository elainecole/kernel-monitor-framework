/*
 * lab01_module.c - The Lab 1 Kernel Module
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/timer.h>

static ulong log_sec = 1; // seconds, defaults to expire once/sec
static ulong log_nsec = 0; // nanoseconds
module_param(log_sec, ulong, 0);
module_param(log_nsec, ulong, 0);

static ktime_t interval; // timer interval
static struct hrtimer timer; // timer

/*
 * nextcall -
 *
enum hrtimer_restart nextcall(struct hrtimer *some_timer) {
  hrtimer_forward_now(some_timer, interval);
  return HRTIMER_RESTART;
}

/*
 * lab01_module_init - the init function called when module is loaded.
 * returns zero if successfully loaded, nonzero otherwise.
 */
static int lab01_module_init(void) {
  interval = ktime_set(log_sec, log_nsec);
  hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
  timer.function = &nextcall;
  hrtimer_start(&timer, interval,HRTIMER_MODE_REL);
  return 0;
}

/*
 * lab01_module_exit - the exit function, called when the module is removed.
 */
static void lab01_module_exit(void) {
  hrtimer_cancel(&timer);
}

module_init(lab01_module_init);
module_exit(lab01_module_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Elaine Cole, Jesse Huang, Zhengliang Liu");
MODULE_DESCRIPTION("TIMER MODULE");
