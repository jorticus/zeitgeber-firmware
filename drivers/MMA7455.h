/*
 * File:   MMA7455.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

#ifndef MMA7455_H
#define	MMA7455_H

#include "util/vector.h"

typedef enum {
    range_8g = 0b00,
    range_4g = 0b10,
    range_2g = 0b01
} accel_range_t;

typedef enum {
    accStandby,         // Low power standby mode (2.5uA)
    accMeasure,         // XYZ measurement mode
    accLevelDetect,     // Level detect mode
    accPulseDetect      // Pulse detect mode
} accel_mode_t;


// Current XYZ reading (updated automatically if in mmaMeasure mode)
extern vector3i_t accel_current;



extern bool accel_init();

uint8 accel_read(uint8 reg_addr);


// Set accelerometer operating mode
extern void accel_SetMode(accel_mode_t mode);

extern void accel_Restore();

// Turn off accelerometer to save power. Equivalent to accel_SetMode(accStandby);
extern void accel_Standby();

// Set accelerometer g range
extern void accel_SetRange(accel_range_t range);

// Perform an offset calibration
extern void accel_Calibrate();

// Perform a manual reading (you should check the DRDY bit before reading)
extern vector3i_t accel_ReadXYZ();
extern vector3c_t accel_ReadXYZ8();

// Called when interrupt is executed for the specified mode
// ie. to set up a callback for the pulse detect mode
// Registering NULL will disable the callback
extern void accel_RegisterCallback(accel_mode_t mode, proc_t cb);

#endif	/* MMA7455_H */