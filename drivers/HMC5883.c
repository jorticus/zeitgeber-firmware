/*
 * File:   HMC5883.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "HMC5883.h"
//#include "peripherals/i2c.h"

////////// Methods /////////////////////////////////////////////////////////////

bool mag_init() {
    return false;
}

void mag_write(uint8 reg, uint8 value) {

}

uint8 mag_read(uint8 reg) {
    return 0;
}

void mag_modify(uint8 reg, uint8 value, uint8 mask) {
    uint8 curr = mag_read(reg);
    curr &= ~mask;
    curr |= value & mask;
    mag_write(reg, curr);
}