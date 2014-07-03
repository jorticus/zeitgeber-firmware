;
; ViscOS Kernel - Pre-empting multi task kernel
; Author: Jared Sanson
; Created: 8/01/2014
;

#include "kernel.h"

;--- Useful definitions ---
.equ SP, W15

;--- Externs and Globals ---
.text

.global __T1Interrupt
.global _KernelSwitchContext
.global _KernelInitTaskStack
.global _KernelStartTask

.extern _systick
.extern _KernelSwitchTask


;--- Code ---

;Note: you should set the T1 interrupt priority to 1 so this can't
; interrupt other interrupts. If this were to interrupt another ISR,
; the interrupt could be context switched to another task, and the interrupt
; won't finish until we context switch back to it!

__T1Interrupt:
    bclr IFS0, #3

    ; Increment kernel systick
    ;clrwdt
    inc _systick

    ;btg LATE, #6  ; LED2

_KernelSwitchContext:
    ; Disable interrupts to prevent bad things from happening.
    disi #0x3FFF

    ; Save the current task's registers to its stack
    push.d w0
    push.d w2
    push.d w4
    push.d w6
    push.d w8
    push.d w10
    push.d w12
    push w14
    push RCOUNT
    push TBLPAG
    push CORCON

    push DSRPAG
    push DSWPAG
    ;push PSVPAG

    ; Store the current stack pointer for later use
    mov _current_task, w0
    mov SP, [w0]

    call _KernelSwitchTask

    ; Restore the stack pointer for the (new) current task
    mov _current_task, w0
    mov [w0], SP

_RestoreTaskContext:
    ;pop PSVPAG
    pop DSWPAG
    pop DSRPAG

    ; Restore the (new) current task's registers
    pop CORCON
    pop TBLPAG
    pop RCOUNT
    pop w14
    pop.d w12
    pop.d w10
    pop.d w8
    pop.d w6
    pop.d w4
    pop.d w2
    pop.d w0
    ;pop SP

    disi #0

    ; Continue where we left the (new) current task,
    ; since it will return to the PC stored in the current stack.
retfie


_KernelInitTaskStack: ;(task_t* task: W0, task_proc_t proc: W1)
    ; This function initializes the stack for the given task so on the first
    ; context switch, it will start executing the task's proc.

    push.s ; Store w0-w3
    mov SP, w3 ; Save the original stack pointer

    mov [w0], SP ; task->sp

    ; Push the proc address into the return address
    push w1     ; PC<15:0>
    mov #0, w1
    push w1     ; PC<22:16>

    ; Clear registers
    mov #0, w2
    push.d w2; w0
    push.d w2; w2
    push.d w2; w4
    push.d w2; w6
    push.d w2; w8
    push.d w2; w10
    push.d w2; w12
    push w2; w14
    push w2; RCOUNT

    push TBLPAG
    push CORCON

    push DSRPAG
    push DSWPAG
    ;push PSVPAG

    mov SP, [w0] ; task->sp

    mov w3, SP ; restore the original stack pointer
    pop.s
return


_KernelStartTask: ;(task_t* task: W0)
    ; The task stack must first be initialized with _KernelInitTaskStack before we can call this.

    ; To start a task, we set the current stack pointer to the task's stack pointer,
    ; then call the code exiting the ISR.
    mov [w0], SP
    goto _RestoreTaskContext


;--- Stack Definition ---

.section app_stack, stack
.space (2560)
