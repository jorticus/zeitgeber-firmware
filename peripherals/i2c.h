/*
 * File:   i2c.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

#ifndef PI2C_H
#define	PI2C_H

////////// Defines /////////////////////////////////////////////////////////////

#define I2C_WRITE 0
#define I2C_READ 1

////////// Methods /////////////////////////////////////////////////////////////

void i2c_init();

void i2c_start();
void i2c_repeated_restart();
void i2c_stop();

void i2c_ack();
void i2c_nack();

void i2c_write(uint8 data);
uint8 i2c_read();

////////// Usage ///////////////////////////////////////////////////////////////

/* Typical usage for writing a byte:
    i2c_start()
    i2c_write((device_addr << 1) | I2C_WRITE);
    i2c_write(data);
    i2c_stop();
*/

/* Typical usage for reading a byte:
    i2c_start()
    i2c_write((device_addr << 1) | I2C_WRITE);
    i2c_write(data);

    i2c_repeated_restart();
    i2c_write((device_addr << 1) | I2C_READ);
    b1 = i2c_read();
    i2c_ack();
    b2 = i2c_read();
    i2c_nack();
    i2c_stop();
*/

#endif	/* PI2C_H */