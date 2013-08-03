/*
 * File:   power_monitor.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * Pins:
 * PW_STAT1     INPUT       Charge status
 * PW_STAT2     INPUT       Charge status
 * PW_CE        OUTPUT      Charge enable
 * AN_VBAT      ADC         Battery voltage   (Divided by 2, LPF at 32Hz)
 *
 * Charger is configured for 100mA USB charge.
 * Higher charge current is available through the EPWR testpoint on the PCB.
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "hardware.h"
#include "power_monitor.h"

////////// Defines /////////////////////////////////////////////////////////////

// STAT1=1, STAT2=1 -> Precharge in progress        chgPrecharge
// STAT1=1, STAT2=0 -> Fast charge in progress      chgFastCharge
// STAT1=0, STAT2=1 -> Charge done                  chgDone
// STAT1=0, STAT2=0 -> Timer fault                  chgFault

#define BATTERY_MIN_THRESHOLD   2700 //mV
#define HYSTERESIS              100 //mV
// Make hysteresis large enough to be unaffected by switching
// peripherals off when entering deep sleep mode.

#define BATTERY_0_VOLTAGE       2800 //mV
#define BATTERY_100_VOLTAGE     3800 //mV
// TODO: Tweak the above values. Could use a look-up table if this isn't sufficient?

////////// Globals /////////////////////////////////////////////////////////////

charge_status_t charge_status = chgFault;
//battery_status_t battery_status = batFlat;
bool battery_good = TRUE;
uint battery_voltage = 0;
uint battery_level = 0;

////////// Methods /////////////////////////////////////////////////////////////

void InitializePowerMonitor() {
    // Battery voltage on AN_VBAT
}

//TODO: Check STAT1/STAT2 inputs and VBAT, update status accordingly
void ProcessPowerMonitor() {
	uint level;

    // Convert the two STAT pins into a byte, then typecast directly to the charge_status enum
#ifdef _MSC_VER
	// charge_status is updated through interface.h in win32
#else
    charge_status = (charge_status_t)( (_PORT(PW_STAT1) << 1) | _PORT(PW_STAT2) );
#endif

    battery_voltage = 0; //ReadAdc(AN_VBAT_CHANNEL) * 2; // The battery voltage is divided by 2
    //TODO: Average the battery voltage

    // Check battery voltage
    if (battery_voltage < BATTERY_MIN_THRESHOLD - HYSTERESIS) {
        battery_good = FALSE;

        //TODO: Put the watch into a battery sleep mode, but allow it to
        // wake up if a button is pushed or if it is plugged into USB.
    } else if (battery_voltage > BATTERY_MIN_THRESHOLD + HYSTERESIS) {
        battery_good = TRUE;
    }

    // battery_status is only used to indicate the battery is "flat", so
    // the watch will turn itself off to save power.

    // Convert the battery voltage to a percentage that can be displayed
    level = battery_voltage - BATTERY_0_VOLTAGE;
    level = level / (BATTERY_100_VOLTAGE - BATTERY_0_VOLTAGE);
    battery_level = level; // Atomic write
}