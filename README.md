Elaine Cole, elainemcole@wustl.edu 
Jesse Huang, jessehuang@wustl.edu 
Zhengliang Liu, zhengliang@wustl.edu


## 2. Module Design#
We create a file lab01_module.c and assign default values to both log_sec and log_nsec. We use two static ulong variables to declare the two values and initialized them to one and zero, respectively. Then we use module_param() to parse command line arguments.The first argument is the name of the variable that holds the value of the command line inputs, the second argument is the type of the variables, the third arguments sets the flag to 0, which only allows the parameters to be set on load time (there is no corresponding files under sysfs/module/...). 


## 3. Timer Design and Evaluation

We initialize the ktime_t interval using our two module arguments log_sec and log_nsec. With this value, we can declare a function nextcall that wakes up our task thread (which calls labfunction() at the interval that we specified. 
labfunction(), in turn, sets the current state as TASK_INTERRUPTIBLE and calls schedule(), effectively putting itself to sleep.
This has the effect of executing the loop in labfunction() once every interval, because that is how often nextcall() wakes up its thread.

### Evaluation

We tested the timing variations of the kernel module with the following parameter values:

##### default; last 10 interations:
[823025.306047] labfunction is still running with itr 8, nvcsw 9, nivcsw 0
[823026.306005] timer is working
[823026.306072] labfunction is still running with itr 9, nvcsw 10, nivcsw 0
[823027.306008] timer is working
[823027.306055] labfunction is still running with itr 10, nvcsw 11, nivcsw 0
[823028.306015] timer is working
[823028.306065] labfunction is still running with itr 11, nvcsw 12, nivcsw 0
[823029.306019] timer is working
[823029.306072] labfunction is still running with itr 12, nvcsw 13, nivcsw 0
[823030.306023] timer is working
[823030.306073] labfunction is still running with itr 13, nvcsw 14, nivcsw 0
[823031.306026] timer is working
[823031.306111] labfunction is still running with itr 14, nvcsw 15, nivcsw 0
[823032.306036] timer is working
[823032.306082] labfunction is still running with itr 15, nvcsw 16, nivcsw 0
[823033.306035] timer is working
[823033.306065] labfunction is still running with itr 16, nvcsw 17, nivcsw 0
[823034.306041] timer is working
[823034.306089] labfunction is still running with itr 17, nvcsw 18, nivcsw 0
[823035.306047] timer is working
[823035.306096] labfunction is still running with itr 18, nvcsw 19, nivcsw 0

Variance: .02289483814e-10s = 0.002289483814 nanoseconds
##### log_sec=0 log_nsec=10000; last 10 iterations: 

[823384.188494] labfunction is still running with itr 331535, nvcsw 330892, nivcsw 55
[823384.188502] timer is working
[823384.188505] labfunction is still running with itr 331536, nvcsw 330893, nivcsw 55
[823384.188515] labfunction is still running with itr 331537, nvcsw 330894, nivcsw 55
[823384.188521] timer is working
[823384.188532] labfunction is still running with itr 331538, nvcsw 330895, nivcsw 55
[823384.188532] timer is working
[823384.188541] timer is working
[823384.188552] labfunction is still running with itr 331539, nvcsw 330896, nivcsw 55
[823384.188553] timer is working
[823384.188561] timer is working
[823384.188573] labfunction is still running with itr 331540, nvcsw 330897, nivcsw 55
[823384.188573] timer is working
[823384.188581] timer is working
[823384.188593] labfunction is still running with itr 331541, nvcsw 330898, nivcsw 55
[823384.188593] timer is working
[823384.188602] timer is working
[823384.188611] timer is working
[823384.188614] labfunction is still running with itr 331542, nvcsw 330899, nivcsw 55
[823384.188622] timer is working
[823384.188625] labfunction is still running with itr 331543, nvcsw 330900, nivcsw 55
[823384.188636] labfunction is still running with itr 331544, nvcsw 330901, nivcsw 55
[823384.188641] timer is working
[823384.188652] labfunction is still running with itr 331545, nvcsw 330902, nivcsw 55
[823384.188652] timer is working
[823384.188661] timer is working
[823384.188672] labfunction is still running with itr 331546, nvcsw 330903, nivcsw 55


Variance: 0.0144690428412 nanoseconds

##### log_sec=1 log_nsec=1000; last 10 iterations: 
[823532.392484] timer is working
[823532.392487] labfunction is still running with itr 169955, nvcsw 169856, nivcsw 115
[823532.392497] labfunction is still running with itr 169956, nvcsw 169857, nivcsw 115
[823532.392511] timer is working
[823532.392516] timer is working
[823532.392522] labfunction is still running with itr 169957, nvcsw 169858, nivcsw 115
[823532.392522] timer is working
[823532.392525] timer is working
[823532.392530] timer is working
[823532.392537] labfunction is still running with itr 169958, nvcsw 169859, nivcsw 115
[823532.392548] timer is working
[823532.392555] timer is working
[823532.392559] labfunction is still running with itr 169959, nvcsw 169860, nivcsw 115
[823532.392560] timer is working
[823532.392563] timer is working
[823532.392573] labfunction is still running with itr 169960, nvcsw 169861, nivcsw 115
[823532.392581] timer is working
[823532.392586] timer is working
[823532.392592] labfunction is still running with itr 169961, nvcsw 169862, nivcsw 115
[823532.392592] timer is working
[823532.392595] timer is working
[823532.392600] timer is working
[823532.392606] labfunction is still running with itr 169962, nvcsw 169863, nivcsw 115
[823532.392617] timer is working
[823532.392622] timer is working
[823532.392626] timer is working
[823532.392630] labfunction is still running with itr 169963, nvcsw 169864, nivcsw 115
[823532.392650] timer is working
[823532.392656] timer is working
[823532.392660] timer is working
[823532.392662] labfunction is still running with itr 169964, nvcsw 169865, nivcsw 115
[823532.392676] labfunction is still running with itr 169965, nvcsw 169866, nivcsw 115
[823532.392687] timer is working
[823532.392692] timer is working
[823532.392697] timer is working
[823532.392700] labfunction is still running with itr 169966, nvcsw 169867, nivcsw 115
[823532.392710] labfunction is still running with itr 169967, nvcsw 169868, nivcsw 115
[823532.392725] timer is working
[823532.392732] timer is working
[823532.392734] exiting
[823532.392737] labfunction is still running with itr 169968, nvcsw 169869, nivcsw 115


The variance of the last 10 samples is 0.04817272804309999 nanoseconds.

Based on these different parameter specifications, we can argue that the timer is fairly precise and consistent.

# Thread Design and Evaluation # 

To implement the requirements of the thread design and evaluation, we create the static function labfunction() which runs in kernel thread(s) when they are spawned by the module. Using printk(), we generate messages with the function name as proof that it is running, returning zero upon successful completion. Then, we edit our lab01_module_init() function to store the result of kthread_run() spawning a kernel thread into our task_struct variable task (added at the top of our module). 

Once this is successfully loading and unloading on the Raspberry Pi, we then modify labfunction() to repeatedly loop the appropriate printk() log message, pass TASK_INTERRUPTIBLE to set_current_state() and then call schedule(), suspending the execution until another code wakes it up. kthread_should_stop() evaluates whether or not it should stop executing, exiting the loop, printk() a message, and returning zero. We then modify our nextcall() timer expiration function to pass the task_struct pointer variable task into wake_up_process(), waking the kernel thread so that another loop iteration occurs. 

Fragments of the system log as kernel thread iterates: 

$ sudo insmod lab01_module.ko 
[850948.017188] labfunction is running
[850948.017206] labfunction is still running with itr 0, nvcsw 1, nivcsw 0
[850949.017193] timer is working
[850949.017389] labfunction is still running with itr 1, nvcsw 2, nivcsw 0
[850950.017209] timer is working
[850950.017384] labfunction is still running with itr 2, nvcsw 3, nivcsw 0
[850951.017217] timer is working
[850951.017380] labfunction is still running with itr 3, nvcsw 4, nivcsw 0
[850952.017228] timer is working
[850952.017398] labfunction is still running with itr 4, nvcsw 5, nivcsw 0
[850953.017239] timer is working
[850953.017396] labfunction is still running with itr 5, nvcsw 6, nivcsw 0
[850954.017251] timer is working
[850954.017406] labfunction is still running with itr 6, nvcsw 7, nivcsw 0
[850955.017258] timer is working
[850955.017360] labfunction is still running with itr 7, nvcsw 8, nivcsw 0
[850956.017282] timer is working
[850956.017459] labfunction is still running with itr 8, nvcsw 9, nivcsw 0
[850957.017294] timer is working
[850957.017478] labfunction is still running with itr 9, nvcsw 10, nivcsw 0
[850958.017305] timer is working
[850958.017351] labfunction is still running with itr 10, nvcsw 11, nivcsw 0
[850959.017312] timer is working
[850959.017370] labfunction is still running with itr 11, nvcsw 12, nivcsw 0
[850959.337174] exiting
[850959.337249] labfunction stopped

Timer expiration: 1 second 
Voluntary context switches: 12
Involuntary context switches: 0 

$ sudo insmod lab01_module.ko log_sec=0 log_nsec=10000

[850795.006422] labfunction is still running with itr 146607, nvcsw 146512, nivcsw 76
[850795.006423] timer is working
[850795.006431] timer is working
[850795.006446] labfunction is still running with itr 146608, nvcsw 146513, nivcsw 76
[850795.006447] timer is working
[850795.006462] timer is working
[850795.006471] timer is working
[850795.006475] labfunction is still running with itr 146609, nvcsw 146514, nivcsw 76
[850795.006481] timer is working
[850795.006492] labfunction is still running with itr 146610, nvcsw 146515, nivcsw 76
[850795.006493] timer is working
[850795.006501] timer is working
[850795.006512] labfunction is still running with itr 146611, nvcsw 146516, nivcsw 76
[850795.006513] timer is working
[850795.006521] timer is working
[850795.006530] exiting
[850795.006533] labfunction is still running with itr 146612, nvcsw 146517, nivcsw 76
[850795.006533] timer is working
[850795.006541] timer is working
[850795.006543] labfunction stopped
[850795.006551] timer is working
[850795.006561] timer is working

Timer expiration: 10000 nanoseconds 
Voluntary context switches: 146517
Involuntary context switches: 76

$ sudo insmod lab01_module.ko log_sec=0 log_nsec=1000

[850859.230904] labfunction is still running with itr 154557, nvcsw 154274, nivcsw 100
[850859.230906] timer is working
[850859.230936] timer is working
[850859.230941] timer is working
[850859.230945] timer is working
[850859.230948] labfunction is still running with itr 154558, nvcsw 154275, nivcsw 100
[850859.230956] timer is working
[850859.230960] labfunction is still running with itr 154559, nvcsw 154276, nivcsw 100
[850859.230963] timer is working
[850859.230968] timer is working
[850859.230973] labfunction is still running with itr 154560, nvcsw 154277, nivcsw 100
[850859.230974] timer is working
[850859.230977] timer is working
[850859.230982] exiting
[850859.230983] timer is working
[850859.230988] labfunction is still running with itr 154561, nvcsw 154278, nivcsw 100
[850859.230998] timer is working
[850859.231005] timer is working
[850859.231008] labfunction stopped
[850859.231011] timer is working
[850859.231015] timer is working

Timer expiration: 1000 nanoseconds 
Voluntary context switches: 154278
Involuntary context switches: 100

It seems that the module’s kernel thread may preempt involuntarily more often when the time expiration is shorter (i.e., with timer default expiring once every second, there are no involuntary context switches, while when the timer expires once every 10000 and 1000 nanoseconds, there are 76 and 100 involuntary context switches, respectively). This makes sense because the shorter the time means that the process has to switch back and forth more often. 

#Multi-threading Design and Evaluation #

I declare 4 struct task_struct * so that I could have one thread for each CPU core later. I issue 4 calls to wake_up_process() so that the nextcall() function (the function I implemented for the timer to call repeatedly) wakes up the 4 threads after they are scheduled to sleep .During the initialization process lab01_module_init() I initialize 4 kernel threads and then bind each one of them to a core using kthread_bind(). When the module unloads, I call kthread_stop() 4 times to end the 4 processes. 

With default parameters:
[130276.169164] timer is working
[130276.169206] labfunction is still running with processor 0,  itr 70, nvcsw 19, nivcsw 0
[130276.169214] labfunction is still running with processor 1,  itr 70, nvcsw 19, nivcsw 0
[130276.169220] labfunction is still running with processor 2,  itr 70, nvcsw 19, nivcsw 0
[130276.169227] labfunction is still running with processor 3,  itr 70, nvcsw 19, nivcsw 0
[130277.169163] timer is working
[130277.169188] labfunction is still running with processor 0,  itr 74, nvcsw 20, nivcsw 0
[130277.169191] labfunction is still running with processor 1,  itr 74, nvcsw 20, nivcsw 0
[130277.169195] labfunction is still running with processor 2,  itr 74, nvcsw 20, nivcsw 0
[130277.169198] labfunction is still running with processor 3,  itr 74, nvcsw 20, nivcsw 0

With log_sec=0, log_nsec=1000:

[131857.040846] timer is working
[131857.040947] timer is working
[131857.041001] timer is working
[131857.041095] timer is working
[131857.041233] labfunction is still running with processor 1,  itr 2170572, nvcsw 712256, nivcsw 201
[131857.041454] timer is working
[131857.041649] timer is working
[131857.041795] timer is working
[131857.041957] labfunction is still running with processor 3,  itr 2170629, nvcsw 659878, nivcsw 134
[131857.042193] timer is working

With log_sec=0, log_nsec=10000:

[132023.871736] labfunction is still running with processor 3,  itr 985698, nvcsw 335744, nivcsw 716
[132023.871786] labfunction is still running with processor 3,  itr 985706, nvcsw 335747, nivcsw 716
[132023.871835] labfunction is still running with processor 3,  itr 985715, nvcsw 335750, nivcsw 716
[132023.871880] timer is working
[132023.871906] labfunction is still running with processor 1,  itr 985727, nvcsw 230169, nivcsw 172
[132023.871956] labfunction is still running with processor 3,  itr 985735, nvcsw 335757, nivcsw 716
[132023.872013] labfunction is still running with processor 3,  itr 985746, nvcsw 335761, nivcsw 716
[132023.872048] timer is working
[132023.872079] labfunction is still running with processor 3,  itr 985758, nvcsw 335765, nivcsw 716
[132023.872138] labfunction is still running with processor 2,  itr 985767, nvcsw 298519, nivcsw 209

The timing variation is much larger compared to single-thread execution (As you can see, core1 hasn’t finished a single iteration and the time stamping of core 3 has huge variations).  The relative frequency of voluntary and involuntary context switches increases for the case of multi-thread execution (roughly 3:1). During single-thread execution the number of involuntary context switches is negligible. 





#System Performance# (Q7)
kworker and systemd-journal are able to preempt our processes.
systemd-journal = the logging system (print) 
kworker 

#Development Effort# (Q8)
9 hours in code implementation and 3 hours for report write-up. We spent at least 12 hours on this lab. Much of the time was spent on reading the usages of the functions. 

