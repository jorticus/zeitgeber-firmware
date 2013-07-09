/*
 * File:   MMA7455.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * 2g/4g/8g 3-axis low-g digital accelerometer
 *
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <i2c.h>
#include <system.h>
#include "MMA7455.h"
#include "util/vector.h"
//#include "peripherals/i2c.h"

////////// Defines /////////////////////////////////////////////////////////////

// Default I2C device address (can be changed through I2CAD register)
#define I2CADDR 0x1D

// Register definitions
#define XOUTL       0x00    // 10 bits output value X LSB
#define XOUTH       0x01    // 10 bits output value X MSB
#define YOUTL       0x02    // 10 bits output value Y LSB
#define YOUTH       0x03    // 10 bits output value Y MSB
#define ZOUTL       0x04    // 10 bits output value Z LSB
#define ZOUTH       0x05    // 10 bits output value Z MSB
#define XOUT8       0x06    // 8 bits output value X
#define YOUT8       0x07    // 8 bits output value Y
#define ZOUT8       0x08    // 8 bits output value Z
#define STATUS      0x09    // Status registers
#define DETSRC      0x0A    // Detection source registers
#define TOUT        0x0B    // Temperature output value
#define I2CAD       0x0D    // I2C Device Address
#define USRINF      0x0E    // User Information
#define WHOAMI      0x0F    // Who Am I value
#define XOFFL       0x10    // Offset drift X value LSB
#define XOFFH       0x11    // Offset drift X value MSB
#define YOFFL       0x12    // Offset drift Y value LSB
#define YOFFH       0x13    // Offset drift Y value MSB
#define ZOFFL       0x14    // Offset drift Z value LSB
#define ZOFFH       0x15    // Offset drift Z value MSB
#define MCTL        0x16    // Mode control
#define INTRST      0x17    // Interrupt latch reset
#define CTL1        0x18    // Control 1
#define CTL2        0x19    // Control 2
#define LDTH        0x1A    // Level detection threshold limit value
#define PDTH        0x1B    // Pulse detection threshold limit value
#define PW          0x1C    // Pulse duration value
#define LT          0x1D    // Latency time value
#define TW          0x1E    // Time window for 2nd pulse value


// Mode Control Register (MCTL)
#define MODE        0   // Mode
#define GLVL        2   // g Level
#define STON        4   // Self test enable
#define SPI3W       5   // SPI 3/4 wire mode (0=4wire, 1=3wire)
#define DRPD        6   // Data ready status output to INT1 disable

typedef struct {
    unsigned :5;
    unsigned PERR:1;    // Parity error detected in trim data
    unsigned DOVR:1;    // Data is overwritten
    unsigned DRDY:1;    // Data is ready
} mma7455_status_t;

#define mDataReady mma7455_Status().DRDY

////////// Variables ///////////////////////////////////////////////////////////

vector3_t mma7455_current;
mma7455_mode_t mma7455_mode = mmaStandby;
mma7455_range_t mma7455_range = range_2g; // TODO: what is the default

////////// Methods /////////////////////////////////////////////////////////////

bool mma7455_init() {

    // Check WhoAmI register

    return false;
}

void mma7455_write(uint8 reg, uint8 value) {

}

uint8 mma7455_read(uint8 reg) {

}

void mma7455_modify(uint8 reg, uint8 value, uint8 mask) {
    uint8 value = mma7455_read(reg);
    value &= ~mask;
    value |= value & mask;
    mma7455_write(reg, value);
}

void mma7455_SetMode(mma7455_mode_t mode) {
    if (mode != mma7455_mode) {
        mma7455_mode = mode;
        mma7455_modify(MCTL, mode << MODE, 0b11 << MODE);
    }
}

void mma7455_SetRange(mma7455_range_t range) {
    if (range != mma7455_range) {
        mma7455_range = range;
        mma7455_modify(MCTL, range << GLVL, 0b11 << GLVL);
    }
}


void mma7455_Calibrate() {
    // Read offset

    // Store into offset drift registers

    // See Freescale app note AN3745
}

vector3_t mma7455_ReadXYZ() {

    // Normalize the result independant of the range setting
    //TODO: verify if this is what we want
    int16 scale;
    switch (mma7455_range) {
        case range_2g: scale = 2; break;
        case range_4g: scale = 4; break;
        case range_8g: scale = 8; break;
    }

    // Read low byte first to ensure high byte is latched
    mma7455_current.x = (mma7455_read(XOUTL) | mma7455_read(XOUTH) << 8) * scale;
    mma7455_current.y = (mma7455_read(YOUTL) | mma7455_read(YOUTH) << 8) * scale;
    mma7455_current.z = (mma7455_read(ZOUTL) | mma7455_read(ZOUTH) << 8) * scale;

    return mma7455_current;
}

uint8 mma7455_ReadTemperature() {
    return mma7455_read(TOUT);
}

mma7455_status_t mma7455_Status() {
    return (mma7455_status_t)mma7455_read(STATUS);
}

void mma7455_ClearInterrupts() {
    mma7455_write(0x03);
    mma7455_write(0x00);
}

////////// Interrupts //////////////////////////////////////////////////////////

// Pin change interrupt for INT1
// INT1 signifies different events depending on mode.
// In mmaMeasure mode, INT1 is the DRDY status bit, signifying data is ready to be read

void mma7455_isr() {

    switch (mma7455_mode) {

        // Data ready, read next sample (stored in 'current')
        case mmaMeasure: {
            mma7455_ReadXYZ();
            break;
        }

        // Level detect interrupt
        case mmaLevelDetect: {
            mma7455_ClearInterrupts();

            //TODO: Do something here
            break;
        }

        // Pulse detect interrupt
        case mmaPulseDetect: {
            mma7455_ClearInterrupts();

            //TODO: Do soemthing here
            break;
        }
    }
}

