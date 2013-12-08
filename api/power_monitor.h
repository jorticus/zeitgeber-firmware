/*
 * File:   power_monitor.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * Monitors battery charging/battery voltage
 */

#ifndef POWER_MONITOR_H
#define	POWER_MONITOR_H

////////// Properties //////////////////////////////////////////////////////////

// Status of the BQ25010 charging chip
typedef enum {
    chgUnknown = 0,
    chgBattery = 0b011,
    chgPrecharge = 0b100,
    chgCharging = 0b010,
    chgCharged = 0b110,
    chgFault = 0b111
} charge_status_t;
extern charge_status_t charge_status;

// System power stauts
typedef enum {
    pwBattery,
    pwCharged,
    pwCharging,
} power_status_t;
extern power_status_t power_status;

// Battery status (if batFlat and not charging, you should turn everything off to conserve power)
typedef enum {
    batFull,
    batNormal,
    batLow,
    batFlat,
    batNotConnected
} battery_status_t;
extern battery_status_t battery_status;

// For debugging
extern uint8 bq25010_status;

// Battery voltage, in millivolts
extern uint battery_voltage;

// Battery level, in percent (0-100)
extern uint battery_level;

extern const char* power_status_message[];
extern const char* battery_status_message[];

////////// Methods /////////////////////////////////////////////////////////////

void InitializePowerMonitor();
void ProcessPowerMonitor();
//uint8 GetChargeStatus();

#endif	/* POWER_H */