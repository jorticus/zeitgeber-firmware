/*
 * File:   oled.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *

 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "hardware.h"
#include "oled.h"
//#include "comms.h"
#include "drivers/ssd1351.h"

////////// Methods /////////////////////////////////////////////////////////////

bool InitializeOled() {




    return FALSE;
}

void OledProcess() {
//    OledStateProcess();
}

void OledPowerOn() {
    // 1. VCI & VDDIO on (always on from system power)
    // 2. Send display off command
    // 3. Initialization
    // 4. Clear screen
    // 5. Power up VCC (OL_POWER=1)
    // 6. Delay 100ms
    // 7. Send display on command

    _LAT(OL_RESET) = 0;

    // Send initialization sequence
    ssd1351_PowerOn();

    _LAT(OL_POWER) = 1;
}

void OledPowerOff() {
    // 1. Send display off command
    // 2. Power down VCC (OL_POWER=0)
    // 3. Delay 100ms
    // 4. Power down VCI & VDDIO (always on from system power)
    // Since VCI & VDDIO are always on, we don't need to delay.

    _LAT(OL_RESET) = 1;
    _LAT(OL_POWER) = 0;

}


