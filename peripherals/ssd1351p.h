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

////////// Defines /////////////////////////////////////////////////////////////

#define READ    1
#define WRITE   0

#define DATA    1
#define COMMAND 0

////////// Methods /////////////////////////////////////////////////////////////

extern void oled_write(char c);
extern void oled_writebuf(char* buf, uint size);
extern char oled_read();

extern void ssd1351_command(uint8 cmd);
extern void ssd1351_data(uint8 data);

////////// Macros //////////////////////////////////////////////////////////////

#define mSetCommandMode() _LAT(OL_DC) = COMMAND
#define mSetDataMode() _LAT(OL_DC) = DATA


#endif	/* SSD1351_H */