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

#include "system.h"
#include "peripherals/i2c.h"
#include "core/kernel.h"
#include "hardware.h"
#include "MMA7455.h"
#include "util/vector.h"
//#include "peripherals/i2c.h"

////////// Defines /////////////////////////////////////////////////////////////

// Default I2C device address (can be changed through I2CAD register)
#define MMA7455_I2CADDR 0x1D

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

#define WHOAMI_MAGIC_NUMBER 85


// Mode Control Register (MCTL)
#define MODE        0   // Mode
#define GLVL        2   // g Level
#define STON        4   // Self test enable
#define SPI3W       5   // SPI 3/4 wire mode (0=4wire, 1=3wire)
#define DRPD        6   // Data ready status output to INT1 disable

typedef union {
    struct {
        unsigned :5;
        unsigned PERR:1;    // Parity error detected in trim data
        unsigned DOVR:1;    // Data is overwritten
        unsigned DRDY:1;    // Data is ready
    };
    uint8 val;
} accel_status_t;

#define mDataReady accel_Status().DRDY

////////// Variables ///////////////////////////////////////////////////////////

vector3i_t accel_current;
accel_mode_t last_mode = accStandby;
accel_mode_t accel_mode = accStandby;
accel_range_t accel_range = range_2g; // TODO: what is the default
uint8 accel_scale = 2;

proc_t accel_callbacks[4];

////////// Methods /////////////////////////////////////////////////////////////

bool accel_init() {
    i2c_init();

    // Check WhoAmI register
    return accel_read(WHOAMI) == WHOAMI_MAGIC_NUMBER;
}

uint8 accel_read(uint8 reg_addr) {
    uint8 result;

    i2c_start();
    i2c_write((MMA7455_I2CADDR << 1) | I2C_WRITE);
    i2c_write(reg_addr);
    i2c_repeated_restart();
    i2c_write((MMA7455_I2CADDR << 1) | I2C_READ);
    result = i2c_read();
    i2c_nack();
    i2c_stop();

    return result;
}

void accel_write(uint8 reg_addr, uint8 value) {
    i2c_start();
    i2c_write((MMA7455_I2CADDR << 1) | I2C_WRITE);
    i2c_write(reg_addr);
    i2c_write(value);
    i2c_nack();
    i2c_stop();
}

void accel_modify(uint8 reg, uint8 value, uint8 mask) {
    uint8 curr = accel_read(reg);
    curr &= ~mask;
    curr |= value & mask;
    accel_write(reg, curr);
}

void accel_SetMode(accel_mode_t mode) {
    //if (mode != accel_mode) {
    accel_mode = mode;
    accel_modify(MCTL, mode << MODE, 0b11 << MODE);
    //}
}

void accel_Standby() {
    last_mode = accel_mode;
    accel_SetMode(accStandby);
}

void accel_Restore() {
    accel_SetMode(last_mode);
}

void accel_SetRange(accel_range_t range) {
    if (range != accel_range) {
        accel_range = range;
        accel_modify(MCTL, range << GLVL, 0b11 << GLVL);

        switch (accel_range) {
            case range_2g: accel_scale = 2; break;
            case range_4g: accel_scale = 4; break;
            case range_8g: accel_scale = 8; break;
        }
    }
}


void accel_Calibrate() {
    // Read offset

    // Store into offset drift registers

    // See Freescale app note AN3745
}

vector3i_t accel_ReadXYZ() {
    // Read low byte first to ensure high byte is latched
    // Note: _OUTH must be read directly after _OUTL
    // Result is 2's complement
    accel_current.x = (accel_read(XOUTL) | (accel_read(XOUTH) << 8));// * accel_scale;
    accel_current.y = (accel_read(YOUTL) | (accel_read(YOUTH) << 8));// * accel_scale;
    accel_current.z = (accel_read(ZOUTL) | (accel_read(ZOUTH) << 8));// * accel_scale;

    // Sign-extension
    if (accel_current.x & 0x0200) accel_current.x |= 0xFC00;
    if (accel_current.y & 0x0200) accel_current.y |= 0xFC00;
    if (accel_current.z & 0x0200) accel_current.z |= 0xFC00;

    return accel_current;
}

vector3c_t accel_ReadXYZ8() {
    vector3c_t vec;

    vec.x = accel_read(XOUT8);// * accel_scale;
    vec.y = accel_read(YOUT8);// * accel_scale;
    vec.z = accel_read(ZOUT8);// * accel_scale;
    
    return vec;
}

uint8 accel_ReadTemperature() {
    return accel_read(TOUT);
}

accel_status_t accel_Status() {
    return (accel_status_t)accel_read(STATUS);
}

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
    proc_t cb = accel_callbacks[(uint8)accel_mode];
    if (cb != NULL) cb();
}

