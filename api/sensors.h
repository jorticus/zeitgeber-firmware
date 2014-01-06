/*
 * File:   sensors.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * Encapsulates all the device's sensors
 */

#ifndef SENSORS_H
#define	SENSORS_H

extern bool InitializeSensors();
extern void ProcessSensors();

// The sensor types below help the computer to know what sensors
// are available, as it may change with firmware/hardware revisions.

// Generic sensor types
#define SENSOR_UNKNOWN          0
#define SENSOR_GENERIC_8BIT     1
#define SENSOR_GENERIC_16BIT    2
#define SENSOR_GENERIC_24BIT    3
#define SENSOR_GENERIC_32BIT    4

// Processed sensor values
#define SENSOR_ACCEL            10  // 3x sint16: (X, Y, Z) in milli-g
#define SENSOR_GYRO             11  // 3x sint16: (A, B, C) in milli-units (Euler angles)
#define SENSOR_MAG              12  // 3x sint16: (X, Y, Z) in milli-gauss
#define SENSOR_AMBIENT_LIGHT    13  // 1x uint16, raw light level
#define SENSOR_TEMPERATURE      14  // 1x sint32, milli-degreesC
#define SENSOR_HUMIDITY         15  // 1x uint16, %*10 (0-10000)
#define SENSOR_PRESSURE         16  // 1x uint32
#define SENSOR_ALTITUDE         17  // 1x uint32, millimeters
// Add more here as required.

// Reserved for future use: IMU data (sensor fusion of accel/gyro/mag)
#define SENSOR_IMU_EULER        50  // 3x sint16 - Euler Angles
#define SENSOR_IMU_QUAT         51  // 4x sint16 - Quaternion
#define SENSOR_IMU_RMAT         52  // 9x sint16 - Rotation matrix

// Ambient light level, 0-255
extern uint8 ambient_light;

// Accelerometer
#include "drivers/MMA7455.h"

// Magnetometer
#include "drivers/HMC5883.h"

#endif	/* SENSORS_H */