/*
 * File:   light.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "light.h"

////////// Methods /////////////////////////////////////////////////////////////

void InitializeLightSensor() {
    // NOTE: Could use comparator to wake up the CPU when the light 
    // level changes sufficiently. This would avoid needing to use
    // periodic sampling.
}

uint ReadLightSensor() {
    // Read ADC channel (blocking)
    //TODO: non-blocking read
}