/* 
 * File:   applications/clock/clock_font.h
 * Author: Jared
 *
 * Created on 14 February 2014, 1:39 PM
 */

#ifndef CLOCK_FONT_H
#define	CLOCK_FONT_H

#define CLOCK_DIGIT_COLON 10
#define CLOCK_DIGIT_AM 11
#define CLOCK_DIGIT_PM 12

extern const image_t* digits[];

int DrawClockInt(uint8 x, uint8 y, uint8 value, bool lead_zero);
int DrawClockDigit(uint8 x, uint8 y, uint8 digit);

#endif	/* CLOCK_FONT_H */

