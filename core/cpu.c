/*
 * File:   cpu.c
 * Author: Jared
 *
 * Created on 5 July 2013, 2:56 PM
 */

#include <system.h>
#include "cpu.h"

// Sleep mode stops clock operation and halts all code execution
// Idle mode halts the CPU and code execution, but allows peripheral
//   modules to continue operation

// Note that we can reduce power consumption further by disabling the
// voltage regulator (RCONbits.VREGS=0), but this will add some delay
// when the device wakes back up. Would only be suitable for long sleeps
// (~1 second sleeps?)

