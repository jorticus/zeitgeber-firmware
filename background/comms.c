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

#include "usb_config.h"
#include "./USB/usb.h"
#include "./USB/usb_function_hid.h"

#include "background/power_monitor.h"

////////// Defines /////////////////////////////////////////////////////////////

////////// Variables ///////////////////////////////////////////////////////////

//unsigned char rx_usb_buffer[64];
//unsigned char tx_usb_buffer[64];

//USB_HANDLE USBOutHandle = 0; //USB handle.  Must be initialized to 0 at startup.
//USB_HANDLE USBInHandle = 0; //USB handle.  Must be initialized to 0 at startup.

unsigned char tx_buffer[PACKET_SIZE];

////////// Prototypes //////////////////////////////////////////////////////////

void comms_ReceivedPacket(unsigned char* packet);
void comms_SendPacket(unsigned char* buffer);

////////// Methods /////////////////////////////////////////////////////////////

void InitializeComms() {

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