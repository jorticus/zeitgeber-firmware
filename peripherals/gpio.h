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

// Current state of the buttons
// You must manually clear buttons to 0
typedef struct {
    unsigned btn1: 1;
    unsigned btn2: 1;
    unsigned btn3: 1;
    unsigned btn4: 1;
} buttons_t;
extern buttons_t buttons;

typedef void (*btn_proc_t)(void);

// Callback functions which are activated when a button press is detected
typedef struct {
    btn_proc_t btn1_press;
    btn_proc_t btn2_press;
    btn_proc_t btn3_press;
    btn_proc_t btn4_press;
} button_handlers_t;
extern button_handlers_t button_handlers;

////////// Methods /////////////////////////////////////////////////////////////

extern void gpio_init();
extern void gpio_process();

extern void gpio_flash(uint led);
extern void gpio_beep();
extern void gpio_vibrate();


#endif	/* GPIO_H */