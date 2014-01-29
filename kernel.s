;
; Pre-empting multi task kernel
; Author: Jared Sanson
; Created: 8/01/2014
;

#include <scheduler.h>

;--- Useful definitions ---
.equ SP, W15

;--- Externs and Globals ---
.text

.global __T1Interrupt
.global _KernelInitTaskStack
.global _KernelStartTask

.extern _KernelProcess
.extern _ProcessTasks
.extern _KernelSwitchContext

.extern _systick_init
.extern _systick

.extern _PreemptTask
.extern _current_task
.extern _stack_base
.extern _current_stack_base
.extern _task_sp
;.extern _kernel_sp


;--- Code ---

;Note: you should set the T1 interrupt priority to 1 so this can't
; interrupt other interrupts. If this were to interrupt another ISR,
; the interrupt could be context switched to another task, and the interrupt
; won't finish until we context switch back to it!

__T1Interrupt:
    bclr IFS0, #3

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

    call _KernelSwitchContext

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


;
;__T1Interrupt:
;    ; Actions performed on interrupt:
;    ;push PC<15:0>
;    ;push SR<7:0>, IPL3, PC<22:16>
;    ;push 0x0000
;    ;IPL set to interrupt priority (disables lower priority interrupts)
;    ;T1IF set
;
;    ; Since we're modifying the stack, we need to use shadow registers.
;    ; This will push w0-w3 and SR (N,OV,Z,C,DC)
;    push.s
;
;    ; Store DSRPAG in w3 since the stack is taken
;    ;mov DSRPAG, w3
;    ;mov #0x200, w0
;    ;mov w0, DSRPAG
;
;    ; Clear the interrupt flag (_T1IF=0)
;    bclr IFS0, #3
;
;    ; Increment the systick here
;    inc _systick
;    clrwdt
;
;    ; Restore the original CPU priority level
;    ; SR<7:0>, IPL3, PC<22:16>
;    pop w1
;    ; PC<15:0>
;    ;pop w1
;
;    ; Get IPL<2:0> bits
;    lsr w1, #8, w2
;    mov #0x0007, w0
;    and w2, w0, w2
;
;    ; If the CPU priority is not 0, then this interrupt has
;    ; pre-empted another interrupt.
;    ; To prevent data-loss, we must retfie here and forget about
;    ; trying to preempt the main task code.
;    ;TODO: Test by removing this code and seeing if USB comms becomes unreliable.
;    sub w0, #0, [w15]
;    bra Z, $+8
;        push w1
;        pop.s
;        retfie
;
;;;; Task Preemption ;;;
;
;
;    ; Mask out SR/IPL3 and push PC<22:16> back onto the stack
;    ;mov #0x007F, w0
;    ;and w1, w0, w1
;    ;push w1
;
;    ;and w0, #0xFFFF, w2
;    ;mov w2,
;    ;lsr w0, #8, w2
;    ;mov w2, SR
;
;    ;call _PreemptTask
;
;    ; Determine if the currently running task needs to be interrupted
;
;
;    ; Store the current task's registers.
;    ; Here _current_task is a pointer to the current task's struct,
;    ; with the first byte being the local task stack (see scheduler.h)
;
;    ;TODO: Can I tell the C compiler to never use w14?
;    ;NOTE: Disabling the frame pointer in gcc seems to work, except W14 is
;    ;   still used in the standard libraries. Need to recompile the standard libraries??
;    mov _current_task, w0
;    mov w14, [w0+14*2]      ; Store w14 in stack[14] so we can use it to point to the stack array
;    pop.s
;
;    mov _current_task, w14      ; Put the address of stack[] in w14
;    mov w0, [w14++]
;    mov w1, [w14++]
;    mov w2, [w14++]
;    mov w3, [w14++]
;    mov w4, [w14++]
;    mov w5, [w14++]
;    mov w6, [w14++]
;    mov w7, [w14++]
;    mov w9, [w14++]
;    mov w8, [w14++]
;    mov w10, [w14++]
;    mov w11, [w14++]
;    mov w12, [w14++]
;    mov w13, [w14++]
;    inc w14     ; Skip w14 since it's already stored
;    ;mov w14, [w14++]
;    mov w15, [w14++]
;    ;mov SR, [w15++]
;    ;and move PC
;    ;TODO: replace the above with a loop? or will that mangle the working registers?
;    ;TODO: investigate stack frame on w14, I think that could avoid a lot of this trouble.
;    ;  I think the LNK/ULNK instructions have something to do with this.
;
;    ; Go to the next task in the list
;
;    ; Restore its context
;
;    ; Return to the stored PC
;
;    ;TODO: What happens to the stack?
;    ; seems like every time we send control back to the scheduler
;    ; the stack will grow.
;    ; Maybe we should implement the scheduler in assembly and just GOTO to it?
;    ;
;    ; Should the systick be disabled while the scheduler is processing??
;
;
;
;    ; Store the current PC/SR in the currently running task
;    mov _current_task, w0
;    ;mov SR, [w0+24]
;
;    ; Clear the CPU priority (IPL) to re-enable interrupts
;    mov SR, w1
;    mov #0xFF1F, w0
;    and w1, w0, w0
;    mov w0, SR
;    bclr CORCON, #3
;
;    ; Restore DSRPAG
;    ;mov w3, DSRPAG
;
;    ;TODO: Context switch to the next task
;
;    ; Discard the current return address
;    ;pop w0
;    ;pop w0
;
;    ; Restore the stack and goto the scheduler
;    pop.s
;    return
;
;    ;TODO: Somewhere around here we need to push all registers and SR
;    ; into the currently pre-empted task, and switch task context
;    ; by restoring the registers for the next task to run.
    

;--- DISASSEMBLY ---
;47:                void isr _T1Interrupt() {
;01866C  781F80     MOV W0, [W15++]
;01866E  F80032     PUSH DSRPAG
;018670  202000     MOV #0x200, W0
;018672  880190     MOV W0, DSRPAG
;018674  FA0000     LNK #0x0
;48:                    _T1IF = 0;
;018676  A96084     BCLR IFS0, #3
;49:                    systick++; // atomic operation since systick is a uint16
;018678  8069F0     MOV 0xD3E, W0
;01867A  E80000     INC W0, W0
;01867C  8869F0     MOV W0, 0xD3E
;50:                }
;01867E  FA8000     ULNK
;018680  F90032     POP DSRPAG
;018682  78004F     MOV [--W15], W0
;018684  064000     RETFIE


;--- Stack Definition ---

.section app_stack, stack
.space (0xB00)

;.section app_stack, stack
;_initial_sp_addr:
;    ; Used to reference the base stack address
;.space (0x100)
