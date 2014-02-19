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
#include "core/kernel.h"

#include "usb_config.h"
#include "./USB/usb.h"
#include "./USB/usb_function_hid.h"

#include "api/clock.h"
#include "background/power_monitor.h"
#include "api/graphics/gfx.h"
#include "drivers/ssd1351.h"

////////// Defines /////////////////////////////////////////////////////////////

// Run this as fast as possible, since usually it's only
// checking if data is received and nothing else.
#define PROCESS_COMMS_INTERVAL 25

////////// Variables ///////////////////////////////////////////////////////////

//unsigned char rx_usb_buffer[64];
//unsigned char tx_usb_buffer[64];

//USB_HANDLE USBOutHandle = 0; //USB handle.  Must be initialized to 0 at startup.
//USB_HANDLE USBInHandle = 0; //USB handle.  Must be initialized to 0 at startup.
bool usb_connected = false;
comms_status_t comms_status = cmDisconnected;

unsigned char tx_buffer[PACKET_SIZE];

static task_t* comms_task;

////////// Prototypes //////////////////////////////////////////////////////////

void ProcessComms();
void comms_ReceivedPacket(unsigned char* packet);
void comms_SendPacket(unsigned char* buffer);
void comms_sleep();
void comms_wake();

////////// Methods /////////////////////////////////////////////////////////////

void InitializeComms() {
    InitializeUSB(&comms_sleep, &comms_wake);
    
    // Communications, only needs to be run when USB is connected
    comms_task = RegisterTask("Comms", ProcessComms);
    comms_task->state = tsRun;

    usb_connected = false;
    comms_status = cmDisconnected;
}

void comms_sleep() {
    // Called by the USB module when the USB becomes disconnected
    comms_task->state = tsStop;
    usb_connected = false;
    comms_status = cmDisconnected;
}

void comms_wake() {
    // Called by the USB module when the USB becomes connected
    comms_task->state = tsRun;
    usb_connected = true;
    comms_status = cmIdle;
}

void ProcessComms() {
    while (1) {
        USBProcess(&comms_ReceivedPacket);
        //TODO: determine whether status is cmIdle or cmActive
        Delay(PROCESS_COMMS_INTERVAL);
    }
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

        ////////// Basic System Commands //////////

        case CMD_PING:
            break;

        case CMD_RESET:
            Reset(); // Causes immediate reset of the MCU
            break;

        case CMD_SET_LED:
            comms_set_led(packet[1], packet[2]);
            break;

        ////////// Diagnostics //////////

        case CMD_GET_BATTERY_INFO:
        {
            battery_info_t* tx_packet = (battery_info_t*)tx_buffer;

            // power_monitor.h
            tx_packet->level = battery_level;
            tx_packet->voltage = battery_voltage;
            tx_packet->charge_status = charge_status;
            tx_packet->power_status = power_status;
            tx_packet->battery_status = battery_status;
            tx_packet->bq25010_status = bq25010_status;

            break;
        }

        case CMD_GET_CPU_INFO:
        {
            cpu_info_t* tx_packet = (cpu_info_t*)tx_buffer;

            // systick.h
            tx_packet->systick = systick;

            break;
        }

        ////////// Display Interface //////////

        case CMD_QUERY_DISPLAY:
        {
            display_query_t* tx_packet = (display_query_t*)tx_buffer;

            // gfx.h
            tx_packet->width = DISPLAY_WIDTH;
            tx_packet->height = DISPLAY_HEIGHT;
            tx_packet->bpp = DISPLAY_BPP;

            tx_packet->display_on = display_power;

            break;
        }

        case CMD_SET_DISPLAY_POWER:
        {
            bool on = packet[1];
            if (on)
                ssd1351_DisplayOn();
            else
                ssd1351_DisplayOff();

            break;
        }

        case CMD_DISPLAY_OVERRIDE:
        {
            bool override = packet[1];
            // TODO
            break;
        }

        case CMD_UPDATE_DISPLAY_BUF:
        {
            //TODO: Will require multiple RX packets
            break;
        }

        case CMD_READ_DISPLAY_BUF:
        {
            //TODO: Will require multiple TX packets
            break;
        }

        ////////// Sensors //////////

        case CMD_QUERY_SENSORS:
        {
            sensor_query_t* tx_packet = (sensor_query_t*)tx_buffer;

            tx_packet->count = 0;
            //TODO: Dynamically populate with known system sensors
            
            break;
        }

        case CMD_SET_SENSOR_ENABLE:
        {
            uint16 index = packet[1];

            // TODO: Enable/disable the specified sensor/
            // may already be enabled by the system,
            // and may be re-enabled by the system as required.

            break;
        }

        case CMD_GET_SENSOR_DATA:
        {
            uint16 index = packet[1];

            // TODO: Return the data for the specified sensor index.
            // Won't return the data until the sensor has been updated,
            // will return 0 if the sensor is currently disabled.
            break;
        }

        ////////// Time & Date //////////

        case CMD_GET_DATETIME:
        {
            datetime_packet_t* tx_packet = (datetime_packet_t*)tx_buffer;
            rtc_time_t time = ClockGetTime();
            rtc_date_t date = ClockGetDate();

            tx_packet->hour = time.hour;
            tx_packet->minute = time.min;
            tx_packet->second = time.sec;

            tx_packet->day_of_week = date.day_of_week;
            tx_packet->day = date.day;
            tx_packet->month = date.month;
            tx_packet->year = date.year;
            break;
        }

        case CMD_SET_DATETIME:
        {
            datetime_packet_t* rx_packet = (datetime_packet_t*)packet;

            ClockSetTime(
                rx_packet->hour,
                rx_packet->minute,
                rx_packet->second
            );

            ClockSetDate(
                rx_packet->day_of_week,
                rx_packet->day,
                rx_packet->month,
                rx_packet->year
            );



            break;
        }


        default:
            return; // Don't send any response
    }

    tx_buffer[0] = packet[0];
    USBSendPacket(tx_buffer);
}