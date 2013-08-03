/*
 * File:   compass.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "compass.h"

////////// Global Variables ////////////////////////////////////////////////////

volatile uint16 compass_angle = 0;

////////// Methods /////////////////////////////////////////////////////////////

// Start the compass (uses both accelerometer and magnetometer)
void StartCompass() {
    // Register interrupts in accel/mag?
}

void StopCompass() {

}

//TODO: Figure out how to determine compass angle using
// the accelerometer and magnetometer. I think a gyro would have
// been better, but an accelerometer should work if you keep it still.
// (I think all it needs to work out is the current orientation?)

// Get the compass heading
compass_dir_t GetCompassHeading() {
	uint16 d;
    // Offset by 22 degrees, so North is between 0 and 45, etc.
    uint16 a = compass_angle + 23; //NOTE: 45/2 = 22.5
    if (a >= 360) a -= 360;

    // Convert to an index (0 to 7) corresponding to a region
    d = a / 45;

    // Typecast d to enum of N,NE,E,...
    return (compass_dir_t)d;
}

// Get the compass angle (in degrees, 0 to 360)
uint16 GetCompassAngle() {
    return compass_angle;
}
