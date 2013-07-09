/*
 * File:   gpio.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "sensors.h"

#include "drivers/HMC5883.h"
#include "drivers/MMA7455.h"
#include "light.h"

////////// Methods /////////////////////////////////////////////////////////////

bool InitializeSensors() {
    if (!hmc5883_init()) return FALSE;
    if (!mma7455_init()) return FALSE;
    //InitializeLight();

    return TRUE;
}
