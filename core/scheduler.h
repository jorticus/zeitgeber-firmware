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

////////// Kernel Configuration ////////////////////////////////////////////////



////////// Typedefs ////////////////////////////////////////////////////////////

typedef void (*task_proc_t)(void);

typedef enum { 
    tsStop,     // Task is not running
    tsIdle,     // Task is using a peripheral (do not put CPU into sleep mode)
    tsRun       // Task is actively running
} task_state_t;

typedef struct {
    uint16 sp;          // Stored task stack pointer for context switch (MUST BE FIRST MEMBER IN STRUCT)

    uint16 stack_base;  // Task stack base address
    uint16 stack_size;  // Task stack size
    
	char name[6];

    task_proc_t proc;
    //task_proc_t start;
    //task_proc_t stop;

    task_state_t state;
    uint priority;  // 0:lowest, 255:highest

    uint interval;
    uint cpu_time;
    uint next_run;
	uint ticks;

    // Preemption
    bool running;
    bool flagged;
} task_t;


////////// Constants ///////////////////////////////////////////////////////////

#define MAX_TASKS 10

#define MAX_TIME_SLOTS 5  // 5 ticks before a task can be interrupted

////////// Methods /////////////////////////////////////////////////////////////

extern void InitializeKernel();
extern task_t* RegisterTask(char* name, task_proc_t proc, uint interval);
extern void KernelStart();

// Load the current stack pointer into the stack_base variable,
// which will then be used as the base stack pointer for application tasks.
#define KernelSetSP() asm("mov W15, _stack_base\nmov W15, _current_stack_base")

#endif	/* SCHEDULER_H */

