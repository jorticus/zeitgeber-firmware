/*
 * File:   win32/drivers/ssd1351.c
 * Author: Jared
 *
 * Created on 9 July 2013, 12:51 PM
 *
 * --WIN32 SPECIFIC DRIVER--
 * Emulates the SSD1351 display for win32 by writing to a bitmap,
 * which can then be drawn directly to the GUI
 */

// !!! WIN32 DRIVER !!!

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "hardware.h"
#include "drivers/ssd1351.h"
#include "peripherals/ssd1351p.h"

////////// Variables ///////////////////////////////////////////////////////////

bool ol_power = false;
uint8 ol_contrast = 0;

////////// Methods /////////////////////////////////////////////////////////////

bool ssd1351_Test() {
    // Check that we can communicate with the display
    return true;
}

void ssd1351_PowerOn() {
    // Power on initialization sequence

    
    // Clear Screen
    ssd1351_ClearScreen();
    
    ssd1351_DisplayOn();
}

void ssd1351_DisplayOn() {
    //ssd1351_command(CMD_DISPLAY_ON);
	ol_power = true;
}

void ssd1351_PowerOff() {
    // Power off sequence
    ssd1351_DisplayOff();
}

void ssd1351_DisplayOff() {
    ol_power = false;
}

void ssd1351_SetContrast(uint8 contrast) {
    if (contrast > 0x0F) contrast = 0x0F;
    ol_contrast = contrast;
}

void ssd1351_ClearScreen() {
    //TODO: How do we clear the screen?
}


