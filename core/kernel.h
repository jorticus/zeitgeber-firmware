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

#define SYSTICK_PERIOD 1 //ms
#define SYSTICK_PRESCALER 8  // 1, 8, 64, 256


////////// Typedefs ////////////////////////////////////////////////////////////

// IMPORTANT: The task_proc must NEVER return!
//   Returning will cause bad things to happen, such as popping things off
//   the end of the stack and returning to unknown addresses.
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


// Calculations
#define SYSTICK_PR (POSC/2 / SYSTICK_PRESCALER * SYSTICK_PERIOD / 1000)
#define SYSTICK_PS_VAL(val) T1_PS_1_##val   // lookup the relevant T1_PS_1_x define
#define SYSTICK_PS(val) SYSTICK_PS_VAL(val) // required for the macro to work


////////// Methods /////////////////////////////////////////////////////////////

extern void InitializeKernel();
extern void KernelStart();

extern task_t* RegisterTask(char* name, task_proc_t proc, uint interval);

//extern void Delay(uint t);

// Forces a context switch to the next task
extern void KernelSwitchContext();
#define Yeild() KernelSwitchContext()
//#define Yeild()

// Load the current stack pointer into the stack_base variable,
// which will then be used as the base stack pointer for application tasks.
#define KernelSetSP() asm("mov W15, _stack_base\nmov W15, _current_stack_base")

#if SYSTICK_PERIOD == 1
    #define IncSystick() systick++
#else
    #define IncSystick() systick += SYSTICK_PERIOD
#endif


////////// Properties //////////////////////////////////////////////////////////

extern volatile uint systick;


#endif	/* SCHEDULER_H */

