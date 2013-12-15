/* 
 * File:   comms.h
 * Author: Jared Sanson
 *
 * Created on 13 December 2013, 6:55 PM
 */

#ifndef COMMS_H
#define	COMMS_H

#define CMD_PING                0x01
#define CMD_RESET               0x02
#define CMD_SET_LED             0x03

// System debug information
#define CMD_GET_BATTERY_INFO    0x10    // Battery voltage, VDD, levels, status
#define CMD_GET_CPU_INFO        0x11    // Osc freq, systick, utilization, time spent in sleep

// Display interface
#define CMD_QUERY_DISPLAY       0x20
#define CMD_SET_DISPLAY_POWER   0x21
#define CMD_DISABLE_DISPLAY     0x22
#define CMD_ENABLE_DISPLAY      0x23
#define CMD_UPDATE_IMAGE        0x24
#define CMD_RETRIEVE_IMAGE      0x25

// Sensors
#define CMD_QUERY_SENSORS       0x30    // Return a list of available sensors
#define CMD_GET_SENSOR_DATA     0x31    // Retrieve processed data for the given sensor

#include "background/power_monitor.h"

typedef struct {
    byte command;
    byte reserved;

    uint16 level;
    uint16 voltage;

    charge_status_t charge_status;
    power_status_t power_status;
    battery_status_t battery_status;

    uint8 bq25010_status;
} battery_info_t;

typedef struct {
    uint systick;
    //TODO: add more fields
} cpu_info_t;

void InitializeComms();

extern bool usb_connected;

#endif	/* COMMS_H */

