/*
 * File:   btle.c
 * Author: Jared
 *
 * Created on 27 August 2014, 9:05 PM
 *
 * Handles communication with the BTLE transciever
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include <spi.h>
#include "hardware.h"

////////// BTLE Module Methods /////////////////////////////////////////////////

// btaci.c
void btle_aci_init();
void btle_aci_process();

////////// Methods /////////////////////////////////////////////////////////////

void InitializeBTLE() {
   /* device_state = Initial;
    credits = 0;
    next_setup_message = -2;
    connection_status = Disconnected;*/

    // Initialize the Application Controller Interface (ACI)
    btle_aci_init();

    
}

void BTLEProcess() {
    btle_aci_process();
}
