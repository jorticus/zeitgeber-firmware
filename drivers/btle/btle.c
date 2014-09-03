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
#include "btaci.h"
#include "btaci_events.h"
#include "btaci_statuscodes.h"
#include "btaci_commands.h"
#include "usb_hal_pic24.h"

static task_t* btle_task;

////////// BTLE Module Methods /////////////////////////////////////////////////

// btaci.c
void btle_aci_init();
void btle_aci_process();
void btle_aci_debug_packet(aci_packet_t* packet);

extern device_state_t btle_device_state;

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

void BTLEStartup() {
    // Test sample packet (works in all operating modes)
    aci_packet_t packet;
    packet.command = NRF_CMD_GET_TEMPERATURE;
    packet.len = 1;
    btle_aci_transfer_packet(&packet);
}

void BTLESetup() {
    aci_packet_t packet;
    
    //TODO: How can we do this asynchronously? We need to send multiple packets
    // I think btle_device_state should remain in nsSetup mode until it is actually completed.
}

void BTLEProcess() {
    //TODO: How can we re-initialize after application start-up?

    // Initialize the Application Controller Interface (ACI)
    btle_aci_init();

    // Give some time for the chip to initialize
    Delay(100);

    printf("NRF: Ready\n");

     BTLEStartup();

    while (1) {
        btle_aci_process();

        // If currently in setup mode, start the setup process
        if (btle_device_state == nsSetup) {
            BTLESetup();
        }
        
        //Delay(25);
    }
}

bool btle_app_handle_event(aci_packet_t* rx_packet) {
   /* switch (rx_packet->command) {
        case NRF_EVENT_DEVICE_STARTED:
        {
            device_started_evt* event = (device_started_evt*)rx_packet;

            // If currently in setup mode, start the setup process
            if (event->operating_mode == 0x02) {
                BTLESetup();
                return true;
            }
        }
    }*/
    return false;
}

