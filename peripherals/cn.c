/*
 * File:   cn.c
 * Author: Jared
 *
 * Created on 27 August 2014, 9:21 PM
 */

#include <system.h>
#include "hardware.h"
#include "peripherals/gpio.h"
#include "peripherals/cn.h"

typedef struct {
    uint cn_pin;            // eg. CN1
    pinref_t pinref;

    cn_cb callback;
    bool state;
} cn_info_t;

static cn_info_t cn_pins[NUM_CN_PINS];
static uint cn_pin_count = 0;


// Register a pin-change interrupt callback
void cn_register_cb(uint cn_pin, pinref_t pinref, cn_cb callback) {
    if (cn_pin < NUM_CN_PINS) {
        // Assign callback
        cn_info_t* info = &cn_pins[cn_pin_count++];

        info->cn_pin = cn_pin;
        info->pinref = pinref;
        info->callback = callback;

        // Configure pin as input

        info->state = gpio_read(&pinref);
    }

    _CNIE = 1;
    _CNIP = 3;
    _CNIF = 0;

    // Enable CN interrupts if not already enabled
    /*if (!cn_enabled) {

        cn_enabled = true;
    }*/
}





// Global pin-change interrupt handler
void isr _CNInterrupt() {
    _CNIF = 0;

    // Determine which pin changed
    int i;
    for (i=0; i<cn_pin_count; i++) {
        cn_info_t* info = &cn_pins[i];

        bool new_state = gpio_read(&info->pinref);
        if (info->state != new_state) {
            info->state = new_state;
            info->callback(new_state);
        }
    }

}
