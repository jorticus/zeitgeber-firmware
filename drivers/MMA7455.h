/*
 * File:   MMA7455.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

#ifndef MMA7455_H
#define	MMA7455_H

typedef enum {
    range_8g = 0b00,
    range_4g = 0b10,
    range_2g = 0b01
} mma7455_range_t;

typedef enum {
    mmaStandby,         // Low power standby mode (2.5uA)
    mmaMeasure,         // XYZ measurement mode
    mmaLevelDetect,
    mmaPulseDetect
} mma7455_mode_t;


// Current XYZ reading (updated automatically if in mmaMeasure mode)
extern vector3_t mma7455_current;



extern bool mma7455_init();

// Set accelerometer operating mode
extern void mma7455_SetMode(mma7455_mode_t mode);

// Set accelerometer g range
extern void mma7455_SetRange(mma7455_range_t range);

// Perform an offset calibration
extern void mma7455_Calibrate();

// Perform a manual reading (you should check the DRDY bit before reading)
extern vector3_t mma7455_ReadXYZ();

#endif	/* MMA7455_H */