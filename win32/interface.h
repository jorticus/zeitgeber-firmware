/*
 * win32<->pic interface definitions
 *
 * Allows the GUI to access the underlying emulation layer
 *
 */

#ifndef INTERFACE_H
#define INTERFACE_H

// OLED Stuff
extern bool ol_power;
extern uint8 ol_contrast;

// GFX Library Stuff
#include "api\graphics\gfx.h"
extern color_t screen[DISPLAY_SIZE];

// Power Monitor
#include "api\power_monitor.h"
extern charge_status_t charge_status;
extern bool battery;

// GPIO
#include "hardware.h"


#endif
