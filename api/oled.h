/*
 * File:   oled.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * OLED API, provides direct access to the OLED display.
 */

#ifndef OLED_H
#define	OLED_H

extern bool InitializeOled();

extern void OledPowerOn();
extern void OledPowerOff();

extern void OledDisplayOn();
extern void OledDisplayOff();

extern void OledClear();

#endif	/* OLED_H */