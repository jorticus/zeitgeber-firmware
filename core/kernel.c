/*
 * File:   scheduler.c
 * Author: Jared
 *
 * Created on 5 July 2013, 2:33 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <timer.h>
#include <stdlib.h>
#include "system.h"
#include "core/kernel.h"
#include "core/cpu.h"
#include "kernel.h"
#include "hardware.h"

////////// Constants ///////////////////////////////////////////////////////////

#define SLEEP_THRESHOLD 100 // ticks

//#define TASK_STACK_BASE 0//__SP_init
#define TASK_STACK_SIZE 256
//#define KERNEL_STACK_SIZE 32

//#define MAX_STACK_SIZE (TASK_STACK_SIZE*MAX_TASKS)

////////// Variables ///////////////////////////////////////////////////////////

task_t tasks[MAX_TASKS] __attribute__((section(".data.tasks")));

uint num_tasks = 0;
uint anext_task = MAX_UINT;
task_t* current_task;
uint current_task_index = 0;

uint16 stack_base = 0;
uint16 current_stack_base = 0;
uint16 task_sp = 0;
//uint16 kernel_sp = 0;

task_t* idle_task;
extern task_t* draw_task;
extern task_t* core_task;

////////// Prototypes //////////////////////////////////////////////////////////

void KernelIdleTask();
void KernelProcess();

// Defined in kernel.s
extern void KernelSwitchContext();
extern void KernelStartContext();
extern void KernelInitTaskStack(task_t* sp, task_proc_t proc);
extern void KernelStartTask(task_t* sp);

////////// Code ////////////////////////////////////////////////////////////////

#if SYSTICK_PR > 0xFFFF
#error SYSTICK too big
#elif SYSTICK_PR == 0
#error SYSTICK too small
#endif


volatile uint systick = 1;

// Note: since we want to stop the systick interrupt from waking the CPU
// out of sleep mode, we'll need to add the number of ticks spent sleeping somehow?
// or maybe turn down the timer rate while it sleeps in case an asynchronous interrupt
// wakes the processor (eg. accelerometer interrupt)

void systick_init() {
    // Configure a system tick timer with interrupt

    _T1MD = 0; // Enable T1 peripheral

    T1CON = T1_OFF & T1_IDLE_CON & T1_GATE_OFF &
            SYSTICK_PS(SYSTICK_PRESCALER) & T1_SYNC_EXT_OFF & T1_SOURCE_INT;

    TMR1 = 0x0000;
    PR1 = SYSTICK_PR;

    _T1IF = 0;
    _T1IP = 1; // Low priority so it doesn't pre-empt other interrupts
    _T1IE = 1;

    T1CONbits.TON = 1;
}

void InitializeKernel(void) {
    current_stack_base = stack_base;
    idle_task = RegisterTask("idle", KernelIdleTask, 0);
}

task_t* RegisterTask(char* name, task_proc_t proc, uint interval) {
    task_t* task = &tasks[num_tasks++];

    // Assign some stack space to this task
    current_stack_base += TASK_STACK_SIZE;
    task->sp = current_stack_base;
    task->stack_base = current_stack_base;
    task->stack_size = TASK_STACK_SIZE;
    
	uint i=0;
	for (i=0; i<6 && *name; i++)
		task->name[i] = *name++;

    task->proc = proc;
    task->interval = interval;

    task->state = tsRun;
    task->priority = 0;

    task->next_run = 0; // should be current tick + interval
    task->cpu_time = 0;
	task->ticks = 0;

    KernelInitTaskStack(task, task->proc);

    return task;
}

void fix_rollover(uint last_tick) {
    uint i;
    for (i=0; i<num_tasks; i++) {
        task_t* task = &tasks[i];
        if (task->next_run > last_tick)
            task->next_run -= last_tick;
        else if (task->next_run > task->interval)
            task->next_run = 0;
        // else rollover will have corrected it
    }
}

void KernelStart() {
    systick_init();

    // Overwrite the current stack pointer with the application stack base,
    // since we will never return from this function.
    //asm("mov _stack_base, W15");

    /*while(1) {
        KernelProcess();
    }*/

    //current_task = &tasks[0];
    //current_task_index = 0;
    current_task_index = 0;
    current_task = idle_task;
    //current_task = draw_task;

    // Context-switch into the idle task
    KernelStartTask(idle_task);

    while (1) {

    }

    Reset(); // Safety trap
}


void KernelIdleTask() {
    // Do nothing for now...
    while (1) {
        Yeild();
    }
}

/*void KernelProcess() {
    uint i;
    static uint last_tick = 0;
    uint current_tick = 0;
    uint next_task = MAX_UINT;
    //uint time = 0; // TODO: system tick
//    uint next_task = 3000; //TODO: MAX_INT

    //TODO: Need to implement sleeping in the scheduler,
    // perhaps taking into account whether it's being charged,
    // and whether the screen is on or not.
    // Do we use an Idle + timer interrupt, or rely on Sleep + Watchdog timeout?
    // Can we wake up exactly when the RTC second ticks over? (what about drawing latency?)
    // Need to turn off screen after some timeout.
    // Can we do pre-empting, using interrupts?
    // The draw task takes quite a long time, it would be nice if we could split it up into chunks.

    // High power mode:
    // Interrupt every 1ms (or 10ms?)
    // on interrupt pre-empt the currently running task and let something else run
    // Need to find a way to ensure all tasks get time to run
    // If next task is > 32ms away, enter Sleep mode and let the WDT wake it up (set WDT=32ms)
    // Increment systick by 32ms upon wakeup

    // Low power mode:
    // Interrupt every 1ms for systick, but perform no pre-emption.
    // Or perhaps we should reduce the systick timer to 10-100ms?
    // This mode should run when display is not drawing, and USB is not connected.
    // All tasks should be very short to run, maximising the amount of time spent in sleep mode.
    // Could potentially still do things like accel/magnetometer.


    // If next task to run is more than 32ms away,
    // enter sleep mode and let the WDT wake us up
    //TODO: Would a longer time be better?
    // need to investiage power implications.
    // Also check wake-up from sleep mode delay

    // Maybe use a longer WDT and Sleep for long tasks (>32ms)
    // and Idle + short systick timer interrupt for short tasks (<32ms)

    //
    // TLOCK = 200us
    // TOST = 1024 * 1/FOSC = 40.96us @ 25MHz
    // Total

    // If a task takes more than 500ms to process,
    // terminate it and restart it, and display a warning.
    // If it does it again, restart the PIC

    for (i=0; i<num_tasks; i++) {
        task_t* task = &tasks[i];
        current_tick = systick;  // copy, since the variable is volatile

        // Rollover occurred (should occur roughly every 65 seconds)
        if (last_tick > current_tick) {
            fix_rollover(last_tick);
        }

        if (task->state == tsRun) {
            if (current_tick > task->next_run) {
                task->ticks++;

                //task->running = true;
                current_task = task;
                task->proc();
                
                //task->running = false;

                // Note: don't care about rollover here.
                // also ignoring any time spent in proc()
                //current_tick = systick;
                task->next_run = current_tick + task->interval;
            }

            // Find the amount of time to the next task
            if (task->next_run < next_task)
                next_task = task->next_run;
        }

        last_tick = current_tick;
    }
    anext_task = next_task - current_tick;
    //TODO: Why is this always returning 0 or 65535?

    /*if (next_task == MAX_UINT) {
        // No pending tasks, enter sleep mode?
        anext_task = MAX_UINT;
    } else {
        if (next_task > current_tick) {
            next_task -= current_tick;
            anext_task = next_task;
        } else {
            anext_task = 0;
        }
    }*/

    // Put the system in sleep mode if no tasks are scheduled for a while
    /*if (next_task > SLEEP_THRESHOLD) {
        // Configure timer to wake up system in next_task - time ticks
        // NOTE that the system might wake up earlier than expected through other interrupts
        // (eg. accelerometer interrupt)
        //Sleep();



        //TODO: Sleep, Idle, or Doze?
    }*/

    // TODO: Figure out how to make the processor go to sleep for a preset time
    // Wake up using a timer interrupt?
    // Ignore sleeping tasks
//}

//void PreemptTask() {
    // Called every systick (see preempt.s)

    //systick++;

    //ClrWdt();

    
  /*      _IPL3 = 0;
    _IPL = 0x00;

    // Continue processing tasks
    asm("goto _RunKernel");*/

    /*task_proc_t test = PreemptTask;
    test();

    PreemptTask();


    while (1) {
        _LAT(LED1) = 0;
        _LAT(LED2) = 1;
    }*/
//}

void KernelSwitchTask() {
    static uint last_tick;
    uint i;

    // Rollover occurred (should occur roughly every 65 seconds)
    if (last_tick > systick) {
        fix_rollover(last_tick);
    }

    // Here we need to determine if any new tasks need to be run,
    // then if we need to context switch to another task.
    current_task_index++;
    if (current_task_index == num_tasks)
        current_task_index = 0;

    current_task = &tasks[current_task_index];

    //TODO: Replace this simple round-robin scheduler with a better one.
    //  It needs to be able to give every task a turn at processing,
    //  possibly taking into account priority.
    //  Should be able to use Delay() to signal that the task is finished
    //  processing for now.

    // Eventually could add some sort of WaitForResource() function
    // for waiting on non-blocking operations such as ADC reads and USB comms.

    // If the next task to run is quite a while away, then maybe we could
    // disable the tick and go to sleep, using the watchdog to wake the CPU up.

    last_tick = systick;
    _TOGGLE(LED2);
}

void KernelInterrupt() {
    // The kernel will automatically push the current task's registers
    // onto the stack, then store the stack pointer to 'task_sp'.
    ClrWdt();
    IncSystick();

    KernelSwitchTask();

    // Upon returning, the kernel will switch the stack to the pointer
    // in 'task_sp', then pop the task's registers back, and continue
    // where the task was left off.
}

/*void Delay(uint t) {
    // Wait for t milliseconds, allowing other tasks to process.
    // If t=0, forces the kernel to switch to the next task that's ready.
    task_t* task = current_task;

    task->next_run = systick + t;

    KernelSwitchTask();
}*/
