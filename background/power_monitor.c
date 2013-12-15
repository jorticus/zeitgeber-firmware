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

// Battery is 4200mV at full charge
#define BATTERY_0_VOLTAGE       3600UL //mV
#define BATTERY_100_VOLTAGE     4150UL //mV

#define BATTERY_LOW             3750UL //mV (arbitrarily chosen)
//#define BATTERY_NOT_CONNECTED   500UL  //mV currently not possible due to the hardware

// Nominal VDD voltage is 3400mV
#define VDD_WARN                3200 //mV
#define VDD_SHUTDOWN            3100 //mV

////////// Globals /////////////////////////////////////////////////////////////

power_status_t power_status = pwBattery;
charge_status_t charge_status = chgFault;
battery_status_t battery_status = batNotConnected;
uint8 bq25010_status = 0;

bool battery_good = TRUE;
uint battery_voltage = 0;
uint battery_level = 0;

/*const char* chargeStatusMessage[] = {
                        // VBUS    STAT1   STAT2   Index
    "Battery",          // 0       0       0       0          ???
    "Battery",          // 0       0       1       1
    "Battery",          // 0       1       0       2

    "Battery",          // 0       1       1       3
    "Precharge",        // 1       0       0       4
    "Charging",         // 1       0       1       5
    "Charged",          // 1       1       0       6
    "Fault"             // 1       1       1       7
};*/
const char* power_status_message[] = {
    "Battery",
    "Fully Charged",
    "Charging",
    "Flat",
    "No Battery"
};
const char* battery_status_message[] = {
    "Full",
    "Normal",
    "Low",
    "Flat",
    "Not Connected"
};

////////// Locals //////////////////////////////////////////////////////////////

#define NUM_VBAT_SAMPLES 16
uint16 vbat_history[NUM_VBAT_SAMPLES];
uint8 vbat_idx = 0;
uint8 vbat_count = NUM_VBAT_SAMPLES-1;

////////// Methods /////////////////////////////////////////////////////////////

void InitializePowerMonitor() {
    // Battery voltage on AN_VBAT
}

void cb_ConvertedVBat(voltage_t voltage) {
    vbat_history[vbat_idx++] = voltage * 2; // The battery voltage is divided by 2 before the ADC

    if (vbat_idx == NUM_VBAT_SAMPLES)
        vbat_idx = 0;

    uint8 i;
    uint32 avg = 0;
    if (vbat_count == 0) {
        for (i=0; i<NUM_VBAT_SAMPLES; i++) {
            avg += vbat_history[i];
        }
        battery_voltage = avg / NUM_VBAT_SAMPLES;
    } else {
        vbat_count--;
        for (i=0; i<vbat_idx; i++) {
            avg += vbat_history[i];
        }
        battery_voltage = avg / vbat_idx;
    }

    // Calculate the battery level
    //TODO: Could add a more advanced algorithm
    if (battery_voltage < BATTERY_0_VOLTAGE) {
        battery_level = 0;
        battery_status = batFlat;
    } else if (battery_voltage > BATTERY_100_VOLTAGE) {
        battery_level = 100;
        battery_status = batFull;
    } else {
       battery_level = (unsigned long)((unsigned long)battery_voltage - BATTERY_0_VOLTAGE) * 100UL / (unsigned long)(BATTERY_100_VOLTAGE - BATTERY_0_VOLTAGE);
       if (battery_voltage < BATTERY_LOW)
           battery_status = batLow;
       else
           battery_status = batNormal;
    }
}

void ProcessPowerMonitor() {

    // For debugging
    bq25010_status = (USB_VBUS_SENSE << 2) | (_PORT(PW_STAT1) << 1) | (_PORT(PW_STAT2));

    // Determine current power state
    if (USB_VBUS_SENSE) {
        if (_PORT(PW_STAT1) == 0)
            power_status = pwCharging;
        else {
            if (_PORT(PW_STAT2) == 0)
                power_status = pwCharged;
            else
                power_status = pwBattery; // Actually Fault
        }
    } else {
        power_status = pwBattery;
    }

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
    return (USB_VBUS_SENSE << 2) | (_PORT(PW_STAT1) << 1) | (_PORT(PW_STAT2));
}
