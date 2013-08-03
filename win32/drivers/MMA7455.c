/*
 * File:   win32/drivers/MMA7455.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * 2g/4g/8g 3-axis low-g digital accelerometer
 *
 * --WIN32 SPECIFIC DRIVER--
 * Returns sample accelerometer data
 * TODO: Could provide GUI input to control the data coming out of it,
 * or use some sort of stored data
 */

// !!! WIN32 DRIVER !!!

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "drivers/MMA7455.h"
#include "util/vector.h"
//#include "peripherals/i2c.h"

////////// Defines /////////////////////////////////////////////////////////////

////////// Variables ///////////////////////////////////////////////////////////

vector3_t accel_current;
accel_mode_t accel_mode = accStandby;
accel_range_t accel_range = range_2g; // TODO: what is the default

proc_t accel_callbacks[4];

////////// Methods /////////////////////////////////////////////////////////////

bool accel_init() {
    return true;
}

void accel_SetMode(accel_mode_t mode) {
    accel_mode = mode;
}

void accel_Standby() {
    accel_SetMode(accStandby);
}

void accel_SetRange(accel_range_t range) {
    accel_range = range;
}


void accel_Calibrate() {
    // Read offset

    // Store into offset drift registers

    // See Freescale app note AN3745
}

vector3_t accel_ReadXYZ() {

    // Normalize the result independant of the range setting
    //TODO: verify if this is what we want
    int16 scale;
    switch (accel_range) {
        case range_2g: scale = 2; break;
        case range_4g: scale = 4; break;
        case range_8g: scale = 8; break;
    }

    // Read low byte first to ensure high byte is latched
    accel_current.x = 0;
    accel_current.y = 0;
    accel_current.z = 0;

    return accel_current;
}

uint8 accel_ReadTemperature() {
    return 0;
}

/*accel_status_t accel_Status() {
	return 
    //return (accel_status_t)accel_read(STATUS);
}*/

void accel_ClearInterrupts() {
    //accel_write(0x03);
    //accel_write(0x00);
}

void accel_RegisterCallback(accel_mode_t mode, proc_t cb) {

}

//TODO: Pulse/Level detection stuff

////////// Interrupts //////////////////////////////////////////////////////////

// Pin change interrupt for INT1
// INT1 signifies different events depending on mode.
// In mmaMeasure mode, INT1 is the DRDY status bit, signifying data is ready to be read

void accel_isr() {
	proc_t cb;

    //TODO: Do we need to modify the INTREG bits (swap INT1/INT2 pin status) depending on mode??
    // The hardware is configured to use only one interrupt

    switch (accel_mode) {

        // Data ready, read next sample (stored in 'current')
        case accMeasure: {
            accel_ReadXYZ();
            break;
        }

        // Level detect interrupt
        case accLevelDetect: {
            accel_ClearInterrupts();

            //TODO: Do something here
            break;
        }

        // Pulse detect interrupt
        case accPulseDetect: {
            accel_ClearInterrupts();

            //TODO: Do soemthing here
            break;
        }

        case accStandby:
            break;
    }

    // Execute callback
    cb = accel_callbacks[(uint8)accel_mode];
    if (cb != NULL) cb();
}

