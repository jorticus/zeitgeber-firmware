/* 
 * File:   scheduler.h
 * Author: Jared
 *
 * Created on 5 July 2013, 2:33 PM
 *
 * Schedules tasks and manages sleep modes
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

////////// Typedefs ////////////////////////////////////////////////////////////

typedef void (*task_proc_t)(void);

typedef enum { 
    tsStop,     // Task is not running
    tsIdle,     // Task is using a peripheral (do not put CPU into sleep mode)
    tsRun       // Task is actively running
} task_state_t;

typedef struct {
    task_proc_t proc;
    //task_proc_t start;
    //task_proc_t stop;

    task_state_t state;

    uint interval;
    uint cpu_time;
    uint next_run;
} task_t;

////////// Constants ///////////////////////////////////////////////////////////

#define MAX_TASKS 20

////////// Methods /////////////////////////////////////////////////////////////

extern task_t* RegisterTask(task_proc_t proc, uint interval);
extern void ProcessTasks();


#endif	/* SCHEDULER_H */

