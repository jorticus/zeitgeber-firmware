/*
 * File:   light.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * Ambient Light Sensor (TEMT6000)
 * The light sensor is connected to an ADC channel and is 
 * low-pass filtered at approximately 160Hz
 */

#ifndef LIGHT_H
#define	LIGHT_H

extern void InitializeLightSensor();
extern uint ReadLightSensor();

#endif	/* LIGHT_H */