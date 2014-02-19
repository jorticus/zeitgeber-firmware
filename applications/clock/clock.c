/*
 * File:   applications/clock/clock.c
 * Author: Jared
 *
 * Created on 14 February 2014, 1:39 PM
 *
 * clock test application
 *
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "api/app.h"
#include "api/api.h"
#include "api/clock.h"
#include "api/graphics/gfx.h"
#include "util/util.h"
#include "core/kernel.h"
#include "background/power_monitor.h"
#include "applications/clock/clock_font.h"



////////// App Definition //////////////////////////////////////////////////////

void appclock_Initialize();
void appclock_Process();
void appclock_Draw();

application_t appclock = APPLICATION("Clock", appclock_Initialize, appclock_Process, appclock_Draw);

////////// Variables ///////////////////////////////////////////////////////////

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
void appclock_Initialize() {

    
}

// Called periodically when state==asRunning
void appclock_Process() {
    while (1) {
        Delay(1000);
    }
}

// Called periodically when isForeground==true (30Hz)
void appclock_Draw() {
    char s[10];

    //SetFontSize(2);

    //RtcTimeToStr(s);
    //DrawString(s, 8,8,WHITE);

    rtc_time_t time = ClockGetTime();
    uint8 hour12 = ClockGet12Hour(time.hour);

    int x = 0;
    x = DrawClockInt(x,20, hour12, false);
    x = DrawClockDigit(x,20, CLOCK_DIGIT_COLON);
    x = DrawClockInt(x,20, time.min, true);
    x = DrawClockDigit(x,20, (ClockIsPM(time.hour)) ? CLOCK_DIGIT_PM : CLOCK_DIGIT_AM);
    
    utoa(s, time.sec, 10);
    DrawString(s, 8,60, WHITE);
    
    rtc_date_t date = ClockGetDate();
    sprintf(s, "%d/%.2d/%d", date.day, date.month, 2000+date.year);
    DrawString(s, 8,68, WHITE);
    
    
    DrawString(days[date.day_of_week], 8,76, WHITE);

}
