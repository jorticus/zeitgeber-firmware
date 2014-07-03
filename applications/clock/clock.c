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
#include "api/graphics/imfont.h"
#include "util/util.h"
#include "core/kernel.h"
#include "background/power_monitor.h"
#include "applications/clock/clock_font.h"
#include "api/calendar.h"



////////// App Definition //////////////////////////////////////////////////////

void appclock_Initialize();
void appclock_Process();
void appclock_Draw();

application_t appclock = APPLICATION("Clock", appclock_Initialize, appclock_Process, appclock_Draw);

////////// Variables ///////////////////////////////////////////////////////////

event_t* event1;
event_t* event2;

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
void appclock_Initialize() {
    event1 = NewEvent("ENCE461", "KH03");
    event2 = NewEvent("COSC401", "KF08");
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
    int x,y,i;

    //SetFontSize(2);


    //// Time ////

    rtc_time_t time = ClockGetTime();
    uint8 hour12 = ClockGet12Hour(time.hour);

    y = 20;
    x = 10;
    x = DrawClockInt(x,y, hour12, false);
    x = DrawClockDigit(x,y, CLOCK_DIGIT_COLON);
    x = DrawClockInt(x,y, time.min, true);
    x = DrawClockDigit(x,y, (ClockIsPM(time.hour)) ? CLOCK_DIGIT_PM : CLOCK_DIGIT_AM);

    //// Date ////

    rtc_date_t date = ClockGetDate();
    y = 45;
    x = 12;
    x = DrawImString(days[date.day_of_week], x,y, WHITE);
    x += 4;

    utoa(s, date.day, 10);
    i = ClockDaySuffix(date.day);
    x = DrawImString(s, x,y, WHITE);
    x = DrawImString(day_suffix[i], x,y, WHITE);
    x += 4;

    x = DrawImString(short_months[date.month-1], x,y, WHITE);

    //sprintf(s, " %d/%02d", date.day, date.month);
    //x = DrawImString(s, x,45, WHITE);


    //// Upcoming Events ////

    /*x = 44;
    y = 66;

    y = CalendarDrawEvent(x,y, event1);
    y = CalendarDrawEvent(x,y, event2);*/

    //DrawBox(8,60, DISPLAY_WIDTH-16,2, SKYBLUE,SKYBLUE);



}
