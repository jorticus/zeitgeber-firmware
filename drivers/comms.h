/*
 * File:   comms.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * OLED low-level communication
 */

#ifndef OLED_COMMS_H
#define	OLED_COMMS_H

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

#endif	/* OLED_COMMS_H */