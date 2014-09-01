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
#include "core/kernel.h"


static task_t* btle_task;

////////// BTLE Module Methods /////////////////////////////////////////////////

// btaci.c
void btle_aci_init();
void btle_aci_process();

// btle.c
void BTLEProcess();

////////// Methods /////////////////////////////////////////////////////////////

void InitializeBTLE() {
   /* device_state = Initial;
    credits = 0;
    next_setup_message = -2;
    connection_status = Disconnected;*/

    // Set up task
    btle_task = RegisterTask("BTLE", BTLEProcess);
    btle_task->state = tsRun;

    //
}

void BTLEProcess() {
    //TODO: How can we re-initialize after application start-up?

    // Initialize the Application Controller Interface (ACI)
    btle_aci_init();

    // Give some time for the chip to initialize
    //Delay(100);

    printf("NRF: Ready\n");

    /*_LAT(BT_REQN) = 0;
    Delay(1);
    _LAT(BT_REQN) = 1;*/

    while (1) {
        btle_aci_process();
        
        //Delay(25);
    }
}
