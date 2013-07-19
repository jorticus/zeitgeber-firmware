/*
 * File:   compass.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * Uses the accelerometer and magnetometer to determine
 * the current compass heading.
 *
 * Assumes the watch is being kept relatively still
 */

#ifndef COMPASS_H
#define	COMPASS_H

typedef enum { N, NE, E, SE, S, SW, W, NW } compass_dir_t;

// Start the compass (uses both accelerometer and magnetometer)
extern void StartCompass();
extern void StopCompass();

// Get the compass heading
extern compass_dir_t GetCompassHeading();

// Get the compass angle (in degrees, 0 to 360)
extern uint16 GetCompassAngle();

#endif	/* COMPASS_H */