/*
 * File:   oled/ssd1351.c
 * Author: Jared
 *
 * Created on 9 July 2013, 12:51 PM
 * OLED is configured for 68XX-parallel (8-bit) communication
 *
 * Pins:
 * OL_E         Enable signal
 * OL_RW        Read/Write signal (high=read, low=write)
 * OL_DC        Data/Command control
 * OL_CS        Chip select (active low)
 * OL_RESET     Reset signal for the OLED
 * OL_SHDN      OLED power supply shut down (active low)
 * OL_DATA_LAT  8-bit data bus (RD0=D7, RD7=D0)
 *
 * IMPORTANT: This file must be compiled with -menable-large-arrays (32k arrays) !!
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <system.h>
#include "hardware.h"
#include "ssd1351p.h"
#include "util/util.h"

////////// Macros //////////////////////////////////////////////////////////////

#define mDataTrisWrite() (OL_DATA_TRIS &= ~OL_DATA_MASK)
#define mDataTrisRead() (OL_DATA_TRIS = (OL_DATA_TRIS & ~OL_DATA_MASK) | OL_DATA_MASK)

#define mSetCommandMode() _LAT(OL_DC) = COMMAND
#define mSetDataMode() _LAT(OL_DC) = DATA

#define RESET _LAT(OL_RESET)
#define POWER _LAT(OL_POWER)

////////// Methods /////////////////////////////////////////////////////////////

void ssd1351_write(BYTE c) {
    mDataTrisWrite();
    _LAT(OL_RW) = WRITE;
    _LAT(OL_E) = 1;
    _LAT(OL_CS) = 0;

    // Write data out
    register BYTE b = bitreverse[c];
    OL_DATA_LAT = (OL_DATA_LAT & ~OL_DATA_MASK) | b;

    _LAT(OL_CS) = 1;
    _LAT(OL_E) = 0;
}
void ssd1351_writebuf(char* buf, uint size) {
    mDataTrisWrite();
    _LAT(OL_RW) = WRITE;

    uint i;
    for (i=0; i<size; i++) {
        ssd1351_write(buf[i]);
    }
}

extern void ssd1351_writeimgbuf(__eds__ color_t* buf, uint size) {
    // Optimised for speed

    mSetDataMode();
    mDataTrisWrite();
    _LAT(OL_RW) = WRITE;
    _LAT(OL_CS) = 0;

    // By accessing the port this way, the compiler will (probably) optimize
    // the operation as a single MOV.B instruction, instead of having
    // to do a complicated operation such as:
    // OL_DATA_LAT = (OL_DATA_LAT & ~OL_DATA_MASK) | b;
    typedef struct {
        unsigned data: 8;
        unsigned :8;
    } ol_data_port_t;
    volatile ol_data_port_t* dp = (volatile ol_data_port_t*)&OL_DATA_LAT;

    // The register keyword forces the compiler to use fast registers
    // NOTE: Do not modify this, the compiler crashes with any other looping method!
    //  eg. for(i=0; i<size; i++) buf[i]  or even  *buf++
    register uint i=size;
    register uint j=0;
    while (i--) {
        // This generates quite a few instructions, but is unavoidable
        // due to requiring EDS space
        color_t c = buf[j++];

        _LAT(OL_E) = 1;
        dp->data = bitreverse[(byte)(c >> 8)];
        _LAT(OL_E) = 0;
        _LAT(OL_E) = 1;
        dp->data = bitreverse[(byte)c];
        _LAT(OL_E) = 0;
    }
    _LAT(OL_CS) = 1;
}

char ssd1351_read() {
    mDataTrisRead();
    //OL_DATA_LAT &= ~OL_DATA_MASK | 0xFF;
    OL_DATA_LAT |= 0xFF;
    _LAT(OL_RW) = READ;
    _LAT(OL_E) = 1;
    Nop();
    _LAT(OL_CS) = 0;
    Nop();

    //for (i=0; i<200; i++);

    //_LAT(OL_E) = 0;


    // Read data in
    char c = 0;
    c = _RD0; c <<= 1;
    c |= _RD1; c <<= 1;
    c |= _RD2; c <<= 1;
    c |= _RD3; c <<= 1;
    c |= _RD4; c <<= 1;
    c |= _RD5; c <<= 1;
    c |= _RD6; c <<= 1;
    c |= _RD7;

    Nop();

    _LAT(OL_CS) = 1;

   // Nop();

    _LAT(OL_E) = 0;
    Nop();

    //for (i=0; i<200; i++);


    return c;
}

void ssd1351_command(uint8 cmd) {
    mSetCommandMode();
    ssd1351_write(cmd);
}

void ssd1351_data(uint8 data) {
    mSetDataMode();
    ssd1351_write(data);
}

void ssd1351_send(uint8 cmd, uint8 data) {
    mSetCommandMode();
    ssd1351_write(cmd);

    mSetDataMode();
    ssd1351_write(data);
}

void ssd1351_sendv(uint8 cmd, uint8 count, ...) {
    va_list ap;
    va_start(ap, count);

    mSetCommandMode();
    ssd1351_write(cmd);

    mSetDataMode();
    uint i;
    for (i=0; i<count; i++)
        ssd1351_write(va_arg(ap, uint8));

    va_end(ap);
}


void ssd1351_sendbuf(uint8 cmd, uint8* buf, uint8 len) {
    mSetCommandMode();
    ssd1351_write(cmd);

    mSetDataMode();
    uint i;
    for (i=0; i<len; i++)
        ssd1351_write(buf[i]);
}
