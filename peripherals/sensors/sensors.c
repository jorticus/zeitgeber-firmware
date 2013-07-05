/*
 * File:   gpio.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "sensors.h"

#include "HMC5883.h"
#include "MMA7455.h"
#include "light.h"

////////// Methods /////////////////////////////////////////////////////////////

bool InitializeSensors() {
    if (!InitializeHMC5883()) return FALSE;
    if (!InitializeMMA7455()) return FALSE;
    //InitializeLight();

    return TRUE;
}
