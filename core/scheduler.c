/*
 * File:   scheduler.c
 * Author: Jared
 *
 * Created on 5 July 2013, 2:33 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "scheduler.h"

////////// Constants ///////////////////////////////////////////////////////////

#define SLEEP_THRESHOLD 100 // ticks

////////// Variables ///////////////////////////////////////////////////////////

task_t tasks[MAX_TASKS];
uint num_tasks = 0;

////////// Code ////////////////////////////////////////////////////////////////

task_t* RegisterTask(task_proc_t proc, uint interval) {
    task_t* task = &task[num_tasks++];

    task->proc = proc;
    task->interval = interval;

    task->state = tsStop;
    task->next_run = interval; // should be current tick + interval
    task->cpu_time = 0;

    return task;
}

void ProcessTasks() {
    uint i;
    uint time = 0; // TODO: system tick
    uint next_task = 3000; //TODO: MAX_INT

    for (i=0; i<num_tasks; i++) {
        task_t* task = &tasks[i];

        if (task->state == tsRun) {
            task->proc();

            // Find the amount of time to the next task
            if (task->next_run < next_task)
                next_task = task->next_run;
        }
    }

    // Put the system in sleep mode if no tasks are scheduled for a while
    if (next_task > SLEEP_THRESHOLD) {
        // Configure timer to wake up system in next_task - time ticks
        // NOTE that the system might wake up earlier than expected through other interrupts
        // (eg. accelerometer interrupt)
        //Sleep();
        
        

        //TODO: Sleep, Idle, or Doze?
    }

    // TODO: Figure out how to make the processor go to sleep for a preset time
    // Wake up using a timer interrupt?
    // Ignore sleeping tasks
}

