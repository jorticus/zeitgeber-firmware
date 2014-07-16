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

const uint8 bitreverse[256] =
{
  0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0,
  0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
  0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8,
  0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
  0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4,
  0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
  0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC,
  0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
  0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2,
  0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
  0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA,
  0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
  0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6,
  0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
  0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE,
  0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
  0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1,
  0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
  0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9,
  0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
  0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5,
  0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
  0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED,
  0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
  0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3,
  0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
  0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB,
  0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
  0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7,
  0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
  0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF,
  0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF};

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
    register uint i=size;
    while (i--) {
        // This generates quite a few instructions, but is unavoidable
        // due to requiring EDS space
        color_t c = *buf++;

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
