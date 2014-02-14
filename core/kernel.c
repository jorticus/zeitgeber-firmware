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
#include "background/comms.h"

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

#define KernelSwitchToTask(task) current_task = task

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

    //T1CON = T1_OFF & T1_IDLE_CON & T1_GATE_OFF &
    //        SYSTICK_PS(SYSTICK_PRESCALER) & T1_SYNC_EXT_OFF & T1_SOURCE_INT;

    T1CON =  T1_OFF & T1_IDLE_CON & T1_GATE_OFF & T1_PS_1_1 & T1_SYNC_EXT_OFF & T1_SOURCE_EXT;

    TMR1 = 0x0000;
    PR1 = 32;  // 32.768kHz / 32 = 1024Hz = 1 tick per 976ms

    _T1IF = 0;
    _T1IP = 1; // Low priority so it doesn't pre-empt other interrupts
    _T1IE = 1;

    T1CONbits.TON = 1;
}

void InitializeKernel(void) {
    current_stack_base = stack_base;

    // IMPORTANT: The idle task MUST be the first task registered,
    //  and its state MUST be set to tsStop.
    idle_task = RegisterTask("idle", KernelIdleTask);
    idle_task->state = tsStop;
}

task_t* RegisterTask(char* name, task_proc_t proc) {
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

    // Initialize the kernel
    current_task_index = 0;
    current_task = idle_task;
    KernelStartTask(idle_task);

    // We shouldn't get here!!
    Reset(); // Safety trap
}

void KernelIdleTask() {
    // This task runs whenever nothing else needs to run.

    while (1) {
        // Go to sleep for a bit... (will wake up on systick)
        if (usb_connected) {
            // Use Idle mode if connected to USB, because Sleep mode will kill the connection.
            Idle();
        } else {
            Sleep();
            //Idle();
        }

        // Average current (screen off):
        //  Sleep: 2.85mA
        //  Idle: 11.45mA
        //  None: 19.09mA
        //TODO: Baseline is 800uA-1mA, try and get it down to that level

        // Check to see if any tasks need to run yet
        Delay(0);
    }
}

void KernelSwitchTask() {
    // NOTE: Called directly from the kernel core (see kernel_asm.s)
    // The kernel will automatically push the current task's registers
    // onto the stack, then store the stack pointer to 'task_sp'.

    static uint last_tick;
    uint i;

    // Rollover occurred (should occur roughly every 65 seconds)
    if (last_tick > systick) {
        fix_rollover(last_tick);
    }
    last_tick = systick;

    // Find the next task that needs to be run
    uint start_index = current_task_index;
    do {
        current_task_index++;

        if (current_task_index == num_tasks)
            current_task_index = 0;

        task_t* task = &tasks[current_task_index];

        if (task->state == tsRun) {
            if (systick > task->next_run) {
                task->next_run = systick;// + 50;

                _LAT(LED2) = 1;
                KernelSwitchToTask(task);
                return;
            }
        }

    } while (current_task_index != start_index);

    // If no tasks need to be run, go to the idle task (puts the MCU into sleep mode)
    _LAT(LED2) = 0;
    current_task = idle_task;

    // Upon returning, the kernel will switch the stack to the pointer
    // in 'task_sp', then pop the task's registers back, and continue
    // where the task was left off.
}

void Delay(uint millis) {
    // Delay for the specified amount of time, allowing other tasks to execute.
    // If t=0, it just forces a context switch
    current_task->next_run = systick + millis;
    KernelSwitchContext();
}

void WaitUntil(uint tick) {
    // Wait until systick reaches the specified value.
    // Useful for functions that take a long or variable amount of time to execute,
    // but are required to execute periodically (eg. 10Hz)
    // If tick < current systick, the task will execute in the next available slot.
    current_task->next_run = tick;
    KernelSwitchContext();
}