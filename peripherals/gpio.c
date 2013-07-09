/*
 * File:   gpio.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "gpio.h"

////////// Globals /////////////////////////////////////////////////////////////

buttons_t buttons;
button_handlers_t button_handlers;

////////// Methods /////////////////////////////////////////////////////////////

void gpio_init() {
    // Ports are already initialized in the main Initialization routine

    // Register PWM/tick handlers for flashing/beeping
}


void gpio_process() {
    // Debouncing

    // Callbacks
}


void gpio_flash(uint led) {

}

void gpio_beep() {

}

void gpio_vibrate() {

}