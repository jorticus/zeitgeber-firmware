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
#include "peripherals/adc.h"

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
#define BATTERY_100_VOLTAGE     4000 //mV
// TODO: Tweak the above values. Could use a look-up table if this isn't sufficient?

////////// Globals /////////////////////////////////////////////////////////////

power_status_t power_status = pwUnknown;
charge_status_t charge_status = chgFault;
//battery_status_t battery_status = batFlat;
bool battery_good = TRUE;
uint battery_voltage = 0;
uint battery_level = 0;

const char* chargeStatusMessage[] = {
                        // VBUS    STAT1   STAT2   Index
    "Battery",        // 0       0       0       0          ???
    "Battery",         // 0       0       1       1
    "Battery",          // 0       1       0       2

    "Battery",          // 0       1       1       3
    "Precharge",        // 1       0       0       4
    "Charging",         // 1       0       1       5
    "Charged",          // 1       1       0       6
    "Fault"             // 1       1       1       7
};

////////// Methods /////////////////////////////////////////////////////////////

void InitializePowerMonitor() {
    // Battery voltage on AN_VBAT
}

void cb_ConvertedVBat(uint16 voltage) {
    battery_voltage = voltage * 2; // The battery voltage is divided by 2 before the ADC

    //TODO: Average the voltage

    // Calculate the battery level
    //TODO: Could add a more advanced algorithm
    if (battery_voltage < BATTERY_0_VOLTAGE)
        battery_level = 0;
    else if (battery_voltage > BATTERY_100_VOLTAGE)
        battery_level = 100;
    else {
       battery_level = (battery_voltage - BATTERY_0_VOLTAGE) / (BATTERY_100_VOLTAGE - BATTERY_0_VOLTAGE);
    }
}

void ProcessPowerMonitor() {
    // Determine the current status of the power chip
    BYTE status = (_PORT(USB_VBUS) << 2) | (_PORT(PW_STAT1) << 1) | (_PORT(PW_STAT2));

    if (status < 0b011) status = 0b011;
    power_status = (power_status_t)status;

    // Read battery voltage (and VDD)
    adc_SetCallback(AN_VBAT, cb_ConvertedVBat);
    adc_StartConversion(AN_VBAT);


	/*uint level;

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
     */
}

uint8 GetChargeStatus() {
    return (_PORT(USB_VBUS) << 2) | (_PORT(PW_STAT1) << 1) | (_PORT(PW_STAT2));
}
