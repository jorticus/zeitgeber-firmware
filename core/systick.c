/*
 * File:   systick.c
 * Author: Jared
 *
 * Created on 5 July 2013, 2:56 PM
 */

#include <system.h>
#include "systick.h"

// Note: since we want to stop the systick interrupt from waking the CPU
// out of sleep mode, we'll need to add the number of ticks spent sleeping somehow?
// or maybe turn down the timer rate while it sleeps in case an asynchronous interrupt
// wakes the processor (eg. accelerometer interrupt)

void systick_init() {
    // Configure a system tick timer with interrupt
}