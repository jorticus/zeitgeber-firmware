/*
 * File:   systick.c
 * Author: Jared
 *
 * Created on 5 July 2013, 2:56 PM
 */

#include <timer.h>
#include <system.h>
#include "systick.h"

volatile uint systick = 1;

// Note: since we want to stop the systick interrupt from waking the CPU
// out of sleep mode, we'll need to add the number of ticks spent sleeping somehow?
// or maybe turn down the timer rate while it sleeps in case an asynchronous interrupt
// wakes the processor (eg. accelerometer interrupt)

void systick_init() {
    // Configure a system tick timer with interrupt

    _T1MD = 0; // Enable T1 peripheral

    T1CON = T1_OFF & T1_IDLE_CON & T1_GATE_OFF &
            T1_PS_1_8 & T1_SYNC_EXT_OFF & T1_SOURCE_INT;

    TMR1 = 0x0000;
    PR1 = 0xFFFF;

    _T1IF = 0;
    //_T1IP = 7;
    _T1IE = 1;

    T1CONbits.TON = 1;

    //TODO: Can't get timers to work.
}

void isr _T1Interrupt() {
    _T1IF = 0;
    systick++;
}

