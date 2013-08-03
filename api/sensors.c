/*
 * File:   sensors.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * Ambient light sensor (TEMT6000)
 * Low pass filtered at approximately 160Hz
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "sensors.h"

//#include <i2c.h>
#include "drivers/HMC5883.h"
#include "drivers/MMA7455.h"

////////// Global Variables ////////////////////////////////////////////////////

uint8 ambient_light = 0;

////////// Methods /////////////////////////////////////////////////////////////

bool InitializeSensors() {

    // Initialize I2C


    // Initialize Magnetometer/Accelerometer
    if (!mag_init()) return FALSE;
    if (!accel_init()) return FALSE;

    // Initialize Ambient Light

    return TRUE;
}

void ProcessSensors() {
    // Read ambient light sensor repeatedly?
    // Could use comparator to wake up the CPU when the light
    // level changes sufficiently. This would avoid needing to use
    // periodic sampling.
}