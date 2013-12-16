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
#include "peripherals/ssd1351p.h"

////////// Methods /////////////////////////////////////////////////////////////

bool InitializeOled() {
    ClrWdt();
    //TODO: Test display for communication by attempting to communicate

    // Fully power on the display
    //OledPowerOn();
    
    ssd1351_PowerOn();

    //ssd1351_DisplayOn();

    // Show loading message/image
    //TODO

   return ssd1351_Test();
}

void OledProcess() {
//    OledStateProcess();
}


void OledDisplayOn() {
    ssd1351_DisplayOn();
}

void OledDisplayOff() {
    ssd1351_DisplayOff();
}


void OledPowerOn() {
    ssd1351_PowerOn();
}

void OledPowerOff() {
    ssd1351_PowerOff();
}

void OledClear() {
    ssd1351_ClearScreen();
}




