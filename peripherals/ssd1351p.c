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

////////// Methods /////////////////////////////////////////////////////////////

void ssd1351_write(char c) {
    _LAT(OL_RW) = WRITE;
    _LAT(OL_E) = 1;
    _LAT(OL_CS) = 0;

    //TODO: bitreversal write

    _LAT(OL_E) = 0;

    // Delay?

    _LAT(OL_CS) = 1;
}
void ssd1351_writebuf(char* buf, uint size) {
    uint i;
    for (i=0; i<size; i++) {
        ssd1351_write(buf[i]);
    }
}

char ssd1351_read() {
    _LAT(OL_RW) = READ;
    _LAT(OL_E) = 1;
    _LAT(OL_CS) = 0;

    char c = 0; //TODO: bitreversal read

    _LAT(OL_E) = 0;

    // Delay?

    _LAT(OL_CS) = 1;


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
