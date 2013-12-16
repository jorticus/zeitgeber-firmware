/*
 * File:   scheduler.c
 * Author: Jared
 *
 * Created on 5 July 2013, 2:33 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "system.h"
#include "core/systick.h"
#include "core/cpu.h"
#include "scheduler.h"
#include "hardware.h"

////////// Constants ///////////////////////////////////////////////////////////

#define SLEEP_THRESHOLD 100 // ticks

////////// Variables ///////////////////////////////////////////////////////////

task_t tasks[MAX_TASKS];
uint num_tasks = 0;

////////// Code ////////////////////////////////////////////////////////////////

task_t* RegisterTask(char* name, task_proc_t proc, uint interval) {
    task_t* task = &tasks[num_tasks++];

	uint i=0;
	for (i=0; i<6 && *name; i++)
		task->name[i] = *name++;

    task->proc = proc;
    task->interval = interval;

    task->state = tsStop;
    task->next_run = 0; // should be current tick + interval
    task->cpu_time = 0;
	task->ticks = 0;

    return task;
}

void sch_FixRollover(uint last_tick) {
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

void ProcessTasks() {
    uint i;
    static uint last_tick = 0;
    uint current_tick = 0;
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
            sch_FixRollover(last_tick);
        }
        
		if (task->state == tsRun && current_tick > task->next_run) {
            task->ticks++;
			task->proc();

            // Note: don't care about rollover here.
            // also ignoring any time spent in proc()
			task->next_run = current_tick + task->interval;

            // Find the amount of time to the next task
           // if (task->next_run < next_task)
            //    next_task = task->next_run;
        }

        last_tick = current_tick;
    }

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
}

