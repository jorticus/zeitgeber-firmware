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
    while (1);
}

void isr _AddressError() {
    while (1);
}

void isr _StackError() {
    while (1);
}

void isr _MathError() {
    while (1);
}
