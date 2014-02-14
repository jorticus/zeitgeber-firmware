/*
 * File:   i2c.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <i2c.h>
#include "system.h"
#include "hardware.h"
#include "peripherals/i2c.h"

////////// Defines /////////////////////////////////////////////////////////////

// I2C clock frequency (Hz)
#define FSCL 100000

#define BRGVAL (((POSC/2)/FSCL) - ((POSC/2)/10000000)-1)

#define I2C_BUS_IDLE                0b000000
#define I2C_SENDING_START           0b000001    // CON.SEN
#define I2C_SENDING_REPEATED_START  0b000010    // CON.RSEN
#define I2C_SENDING_STOP            0b000100    // CON.PEN
#define I2C_RECEIVING               0b001000    // CON.RCEN
#define I2C_SENDING_ACK             0b010000    // CON.ACKEN
#define I2C_TRANSMITTING            0b100000    // STAT.TRSTAT

////////// State Variables /////////////////////////////////////////////////////

uint8 i2c_device_addr = 0x00;

//uint8 i2c_state = I2C_BUS_IDLE;
#define i2c_state() ((I2C2CON & 0b11111) | (I2C2STATbits.TRSTAT << 5))

////////// Prototypes //////////////////////////////////////////////////////////

void i2c_ack();
void i2c_nack();

////////// Methods /////////////////////////////////////////////////////////////

void i2c_init() {
    _I2C2MD = 0;

    // Set up I2C
    I2C2CON = 0x0000;
    I2C2STAT = 0x0000;
    I2C2BRG = BRGVAL;

    I2C2CONbits.I2CEN = 1;

    // Initialize interrupts
    //...
}

void i2c_start() {
    while (i2c_state() != 0);

    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN);
}

void i2c_repeated_restart() {
    while (i2c_state() != 0);

    I2C2CONbits.RSEN = 1;
    while (I2C2CONbits.RSEN);
}

void i2c_stop() {
    while (i2c_state() != 0);
    if (I2C2STATbits.P) return;

    I2C2CONbits.PEN = 1;
    while (I2C2CONbits.PEN);
}

void i2c_ack() {
    while (i2c_state() != 0);
    if (I2C2STATbits.P) return;

    I2C2CONbits.ACKDT = 0; // ACK
    I2C2CONbits.ACKEN = 1;
    while (I2C2CONbits.ACKEN);
}

void i2c_nack() {
    while (i2c_state() != 0);
    if (I2C2STATbits.P) return;

    I2C2CONbits.ACKDT = 1; // NACK
    I2C2CONbits.ACKEN = 1;
    while (I2C2CONbits.ACKEN);
}

void i2c_write(uint8 data) {
    while (i2c_state() != 0);
    if (I2C2STATbits.P) return;

    I2C2TRN = data;

    // Wait for all 8 bits + ACK to be received
    while(I2C2STATbits.TBF);
    while(I2C2STATbits.TRSTAT);

    if (I2C2STATbits.ACKSTAT)
        i2c_stop();
}

uint8 i2c_read() {
    while (i2c_state() != 0);
    if (I2C2STATbits.P) return 255;

    I2C2CONbits.RCEN = 1;

    // Wait for 8 bits to be received
    //while(!I2C2STATbits.RBF);
    while(I2C2CONbits.RCEN);

    return I2C2RCV;
}
