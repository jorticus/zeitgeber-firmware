/*
 * File:   oled/state.c
 * Author: Jared
 *
 * Created on 9 July 2013, 12:51 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "hardware.h"
#include "oled.h"
#include "comms.h"

////////// Methods /////////////////////////////////////////////////////////////

/*typedef enum { STATE_POWER_OFF, STATE_POWER_ON } oled_state_t;

static oled_state_t state = STATE_POWER_OFF;

void OledStateProcess() {
    switch(state) {

        // OLED is currently off
        case STATE_POWER_OFF: {



            break;
        }

        // OLED is currently on
        case STATE_POWER_ON: {
            OledStatePowerOn();
            break;
        }


    }
}

typedef enum {
    PSON_TURN_ON,
    PSON_DELAY,
    PSON_DISPLAY_ON
} poweron_state_t;
poweron_state_t poweron_state = PSON_TURN_ON;

void OledStatePowerOn() {
    // 1. VCI & VDDIO on (always on from system power)
    // 2. Send display off command
    // 3. Initialization
    // 4. Clear screen
    // 5. Power up VCC (OL_SHDN=1)
    // 6. Delay 100ms
    // 7. Send display on command

    switch(poweron_state) {

        case PSON_TURN_ON: {

            // Display off command

            // Initialization commands

            // Clear screen

            // Power on
            _LAT(OL_POWER) = 1;

            poweron_state = PSON_DELAY;
            break;
        }

        case PSON_DELAY: {
            // Wait 100ms
            if (FALSE) {
                // Send display on command
                poweron_state = PSON_DISPLAY_ON;
            }
            break;
        }

        // PSO_DISPLAY_ON: Do nothing.
    }
}


typedef enum {
    PSOFF_TURN_OFF,
    PSOFF_DELAY,
    PSOFF_DISPLAY_OFF
} poweroff_state_t;
poweroff_state_t poweroff_state = PSOFF_TURN_OFF;

void OledPowerOn() {
    poweron_state = PSON_TURN_ON;
    state = STATE_POWER_ON;
}

void OledPowerOff() {
    poweroff_state = PSOFF_TURN_OFF;
    state = STATE_POWER_OFF;
}*/