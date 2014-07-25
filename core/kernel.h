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

#define SYSTICK_PERIOD 1        //ms  (Note: It is recommended you keep it at 1ms or timings will be wrong)
#define SYSTICK_PRESCALER 8     // 1, 8, 64, 256

#define TASK_NAME_LEN 6         // Maximum chars allocated for a task's name

// IMPORTANT: If you increase the stack size, make sure you also increase the allocated space in kernel_asm.s
#define TASK_STACK_SIZE 512     // Size of the stack for each task
#define MAX_TASKS 8            // Maximum number of tasks allocated

#define CALC_CPU_TICKS 1000      // Number of CPU ticks before CPU utilization is re-calculated.

#define CPU_TICK_HISTORY_LEN 128

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
    
    char name[TASK_NAME_LEN+1];

    task_proc_t proc;
    task_state_t state;

    uint next_run;

    uint ticks;
    uint last_run;
    uint cpu_usage;
    uint cpu_ticks;
} task_t;


////////// Constants ///////////////////////////////////////////////////////////


// Calculations
#define SYSTICK_PR (POSC/2 / SYSTICK_PRESCALER * SYSTICK_PERIOD / 1000)
#define SYSTICK_PS_VAL(val) T1_PS_1_##val   // lookup the relevant T1_PS_1_x define
#define SYSTICK_PS(val) SYSTICK_PS_VAL(val) // required for the macro to work


////////// Methods /////////////////////////////////////////////////////////////

extern void InitializeKernel();
extern void KernelStart();

extern task_t* RegisterTask(char* name, task_proc_t proc);

extern void Delay(uint millis);
extern void WaitUntil(uint tick);

#define WaitFor(condition) while (!(condition)) { Delay(0); }

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

extern uint total_cpu_ticks;

extern uint cpu_tick_history_idx;
extern uint cpu_tick_history[CPU_TICK_HISTORY_LEN];


#endif	/* SCHEDULER_H */

