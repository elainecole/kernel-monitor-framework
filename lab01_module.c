
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <stdio.h>
#include <linux/timer.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Elaine Cole, Jesse Huang, Zhengliang Liu");
MODULE_DESCRIPTION("TIMER MODULE");

static unsigned long log_sec = 1;
static unsigned long log_nsec = 0; // What to put here? Is the time sec + nsec?
module_param(log_sec, unsigned long, 0);
module_param(log_nsec, unsigned long, 0);

static ktime_t interval;
static struct hrtimer timer;

enum hrtimer_restart nextcall(struct hrtimer *some_timer) {
  hrtimer_forward_now(some_timer, interval);
  return HRTIMER_RESTART;
}

static int lab01_module_init(void) {
  interval = ktime_set(log_sec, log_nsec);
  hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
  timer.function = &nextcall;
  hrtimer_start(&timer, interval,HRTIMER_MODE_REL);
  return 0;
}

static void lab01_module_exit(void) {
  hrtimer_cancel(&timer);
}

module_init(lab01_module_init);
module_exit(lab01_module_exit);
