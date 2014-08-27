/*
 * File:   gpio.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * LED/Button/Actuator outputs and inputs
 */

#ifndef GPIO_H
#define	GPIO_H

////////// Includes ////////////////////////////////////////////////////////////

#include "hardware.h"

////////// Properties //////////////////////////////////////////////////////////

typedef struct {
    volatile uint* tris;
    volatile uint* port;
    volatile uint* lat;
    uint pin;
    uint pin_mask;
} pinref_t;

#define _TRIS_REG(pin)            pin(_TRIS_REG_F)
#define _TRIS_REG_F(alpha,bit)    (TRIS ## alpha)
#define _PORT_REG(pin)            pin(_PORT_REG_F)
#define _PORT_REG_F(alpha,bit)    (PORT ## alpha)
#define _LAT_REG(pin)            pin(_LAT_REG_F)
#define _LAT_REG_F(alpha,bit)    (LAT ## alpha)

#define _PIN_IDX(pin)          pin(_PIN_IDX_F)
#define _PIN_IDX_F(alpha,bit)   bit

#define _PINREF(pin) (pinref_t){&_TRIS_REG(pin), &_PORT_REG(pin), &_LAT_REG(pin), _PIN_IDX(pin), 1 << _PIN_IDX(pin)}

uint gpio_read(pinref_t* pinref);
void gpio_write(pinref_t* pinref, uint value);

////////// Methods /////////////////////////////////////////////////////////////



#endif	/* GPIO_H */