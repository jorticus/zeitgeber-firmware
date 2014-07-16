/*
 * File:   peripherals/ssd1351p.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * SSD1351 Peripheral Interface
 * Handles low-level data communication with the OLED display
 */

#ifndef SSD1351_PERIPH_H
#define	SSD1351_PERIPH_H

#include "api/graphics/gfx.h"

////////// Defines /////////////////////////////////////////////////////////////

#define READ    1
#define WRITE   0

#define DATA    1
#define COMMAND 0

////////// Methods /////////////////////////////////////////////////////////////

extern void ssd1351_write(BYTE c);
extern void ssd1351_writebuf(char* buf, uint size);
extern void ssd1351_writeimgbuf(__eds__ color_t* buf, uint size);
extern char ssd1351_read();

extern void ssd1351_command(uint8 cmd);
extern void ssd1351_data(uint8 data);

// Send a command followed by data
extern void ssd1351_send(uint8 cmd, uint8 data);
extern void ssd1351_sendv(uint8 cmd, uint8 count, ...);
extern void ssd1351_sendbuf(uint8 cmd, uint8* buf, uint8 len);


#endif	/* SSD1351_H */