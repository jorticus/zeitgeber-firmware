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

// Charging status
typedef enum { chgFault, chgDone, chgFastCharge, chgPrecharge } charge_status_t;
extern charge_status_t charge_status;

// Battery status (if batFlat and not charging, you should turn everything off to conserve power)
//typedef enum { batGood, batFlat } battery_status_t;
//extern battery_status_t battery_status;
extern bool battery_good;

// Battery voltage, in millivolts
extern uint battery_voltage;

// Battery level, in percent (0-100)
extern uint battery_level;

extern bool wut; // Can't remember what I was going to put here.

////////// Methods /////////////////////////////////////////////////////////////

extern void InitializePowerMonitor();
extern void ProcessPowerMonitor();

#endif	/* POWER_H */