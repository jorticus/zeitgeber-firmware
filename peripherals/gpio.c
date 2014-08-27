/*
 * File:   gpio.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "gpio.h"

////////// Globals /////////////////////////////////////////////////////////////

////////// Methods /////////////////////////////////////////////////////////////

uint gpio_read(pinref_t* pinref) {
    return ((*pinref->port) & pinref->pin_mask) ? true : false;  // Assumes mask only has 1 bit set
}

void gpio_write(pinref_t* pinref, uint value) {
    if (value) {
        (*pinref->lat) |= pinref->pin_mask;
    } else {
        (*pinref->lat) &= ~pinref->pin_mask;
    }
}