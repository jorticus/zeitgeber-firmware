/*
 * File:   gpio.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * Pins:
 * BT_MISO      INPUT
 * BT_MOSI      OUTPUT
 * BT_SCK       OUTPUT
 * BT_REQN      OUTPUT      ACI request pin (handshaking, active low)
 * BT_RDYN      INPUT       ACI device ready indication (handshaking, active low)
 * BT_RESET     INPUT       Reset, active low
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "hardware.h"

////////// Methods /////////////////////////////////////////////////////////////

void EnableBluetooth() {
#ifndef WIN32
    _CNPUE(BT_RDYN_CN) = 1; // RDYN line must have a pull-up
    _LAT(BT_RESET) = 0;
    _LAT(BT_REQN) = 1;
#endif
}

void DisableBluetooth() {
#ifndef WIN32
    _LAT(BT_RESET) = 1;
    _CNPUE(BT_RDYN_CN) = 0; // Disable pull-up
    _LAT(BT_REQN) = 0;
#endif
}

bool InitializeBluetooth() {
#ifdef WIN32
	return true;
#else
    // Set up SPI1

    // Enable bluetooth chip
    //EnableBluetooth();

    // Attempt to communicate with the bluetooth chip, fail if we can't

    // Configure the chip, and put it to sleep

    DisableBluetooth();

    return FALSE;
#endif
}

