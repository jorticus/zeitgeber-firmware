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

typedef enum {
    tpNormal,
    tpHigh
} task_priority_t;

typedef struct {
    uint16 stack[18];

	char name[6];

    task_proc_t proc;
    //task_proc_t start;
    //task_proc_t stop;

    task_state_t state;
    task_priority_t priority;

    uint interval;
    uint cpu_time;
    uint next_run;
	uint ticks;

    // Preemption
    bool running;
    bool flagged;
} task_t;


////////// Constants ///////////////////////////////////////////////////////////

#define MAX_TASKS 20

#define MAX_TIME_SLOTS 5  // 5 ticks before a task can be interrupted

////////// Methods /////////////////////////////////////////////////////////////

extern task_t* RegisterTask(char* name, task_proc_t proc, uint interval);
extern void RunKernel();


#endif	/* SCHEDULER_H */

