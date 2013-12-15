/*
 * File:   comms.c
 * Author: Jared Sanson
 *
 * Created on 13 December 2013, 6:55 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "hardware.h"
#include "drivers/usb/usb.h"
#include "background/comms.h"
#include "core/scheduler.h"

#include "usb_config.h"
#include "./USB/usb.h"
#include "./USB/usb_function_hid.h"

#include "background/power_monitor.h"

////////// Defines /////////////////////////////////////////////////////////////

// Run this as fast as possible, since usually it's only
// checking if data is received and nothing else.
#define PROCESS_COMMS_INTERVAL 0 //ms

////////// Variables ///////////////////////////////////////////////////////////

//unsigned char rx_usb_buffer[64];
//unsigned char tx_usb_buffer[64];

//USB_HANDLE USBOutHandle = 0; //USB handle.  Must be initialized to 0 at startup.
//USB_HANDLE USBInHandle = 0; //USB handle.  Must be initialized to 0 at startup.
bool usb_connected = false;

unsigned char tx_buffer[PACKET_SIZE];

static task_t* comms_task;

////////// Prototypes //////////////////////////////////////////////////////////

void comms_ReceivedPacket(unsigned char* packet);
void comms_SendPacket(unsigned char* buffer);
void comms_sleep();
void comms_wake();

////////// Methods /////////////////////////////////////////////////////////////

void InitializeComms() {
    InitializeUSB(&comms_sleep, &comms_wake);
    
    // Communications, only needs to be run when USB is connected
    comms_task = RegisterTask("Comms", ProcessComms, PROCESS_COMMS_INTERVAL);
    comms_task->state = tsRun;

    usb_connected = false;
}

void comms_sleep() {
    comms_task->state = tsStop;
    usb_connected = false;
}

void comms_wake() {
    comms_task->state = tsRun;
    usb_connected = true;
}

void ProcessComms() {
    USBProcess(&comms_ReceivedPacket);
}

void comms_set_led(byte led, byte value) {
    switch (led) {
        case 1:
            _LAT(LED1) = value;
            break;
        case 2:
            _LAT(LED2) = value;
            break;
    }
}

// Called when a packet is received
void comms_ReceivedPacket(unsigned char* packet) {
    // packet is 64 bytes

    //NOTE: If transferring multiple packets,
    // it might pay to temporarily reduce the task interval.

    switch (packet[0]) {
        case CMD_PING:
            break;

        case CMD_RESET:
            Reset(); // Causes immediate reset of the MCU
            break;

        case CMD_SET_LED:
            comms_set_led(packet[1], packet[2]);
            break;

        case CMD_GET_BATTERY_INFO:
        {
            battery_info_t* tx_packet = (battery_info_t*)tx_buffer;
            tx_packet->level = battery_level;
            tx_packet->voltage = battery_voltage;
            tx_packet->charge_status = charge_status;
            tx_packet->power_status = power_status;
            tx_packet->battery_status = battery_status;
            tx_packet->bq25010_status = bq25010_status;
        }
        break;

        default:
            return; // Don't send any response
    }

    tx_buffer[0] = packet[0];
    USBSendPacket(tx_buffer);
}