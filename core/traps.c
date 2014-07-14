/*
 * File:   traps.c
 * Author: Jared
 *
 * Created on 9 July 2013, 7:31 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include "system.h"

////////// Interrupts //////////////////////////////////////////////////////////

void isr _OscillatorFail() {
    Reset();
}

void isr _AddressError() {
    Reset();
}

void isr _StackError() {
    Reset();
}

void isr _MathError() {
    Reset();
}
