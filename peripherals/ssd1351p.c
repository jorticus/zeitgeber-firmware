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
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <system.h>
#include "hardware.h"
#include "ssd1351p.h"

////////// Macros //////////////////////////////////////////////////////////////

#define mDataTrisWrite() (OL_DATA_TRIS &= ~OL_DATA_MASK)
#define mDataTrisRead() (OL_DATA_TRIS = (OL_DATA_TRIS & ~OL_DATA_MASK) | OL_DATA_MASK)

#define mSetCommandMode() _LAT(OL_DC) = COMMAND
#define mSetDataMode() _LAT(OL_DC) = DATA

#define RESET _LAT(OL_RESET)
#define POWER _LAT(OL_POWER)

////////// Methods /////////////////////////////////////////////////////////////

void ssd1351_write(char c) {
    UINT i;

    mDataTrisWrite();
    _LAT(OL_RW) = WRITE;
    _LAT(OL_E) = 1;
    Nop();
    _LAT(OL_CS) = 0;
    Nop();

    // Write data out
    BYTE b = c;
    _LATD7 = (b & 0b1); b >>= 1;    //1
    _LATD6 = (b & 0b1); b >>= 1;    //1
    _LATD5 = (b & 0b1); b >>= 1;    //1
    _LATD4 = (b & 0b1); b >>= 1;    //1
    _LATD3 = (b & 0b1); b >>= 1;    //0
    _LATD2 = (b & 0b1); b >>= 1;    //1
    _LATD1 = (b & 0b1); b >>= 1;    //0
    _LATD0 = (b & 0b1);             //1

    for (i=0; i<200; i++);

    _LAT(OL_CS) = 1;

    for (i=0; i<100; i++);

    _LAT(OL_E) = 0;

    for (i=0; i<100; i++);

    //_LAT(OL_CS) = 1;

    //for (i=0; i<10000; i++);
}
void ssd1351_writebuf(char* buf, uint size) {
    uint i;
    for (i=0; i<size; i++) {
        ssd1351_write(buf[i]);
    }
}

char ssd1351_read() {
    UINT i;

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

    Nop();

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
