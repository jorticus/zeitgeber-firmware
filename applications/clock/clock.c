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

static void Initialize();
static void Draw();

application_t appclock = {.name="Clock", .init=Initialize, .draw=Draw};

////////// Variables ///////////////////////////////////////////////////////////

#define NUM_EVENTS 7
event_t* my_events[NUM_EVENTS];

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
static void Initialize() {
    appclock.task->state = tsStop;

    const event_t test = {.label="ENCE462", .location="Er466", .day=dwMonday, .time=((rtc_time_t){.hour=12})};

    //                       label      loc     day        hr min
    my_events[0] = NewEvent("ENCE462", "Er466", dwMonday,    12, 0);
    my_events[1] = NewEvent("COSC418", "Er235", dwMonday,    15, 0);
    my_events[2] = NewEvent("ENCE463", "KF07",  dwTuesday,    9, 0);
    my_events[3] = NewEvent("ENCE462", "KD05",  dwTuesday,   12, 0);
    my_events[4] = NewEvent("ENCE463", "E11",   dwWednesday, 10, 0);
    my_events[5] = NewEvent("ENCE463", "KD05",  dwThursday,  11, 0);
    my_events[6] = NewEvent("ENCE462", "Er466", dwThursday,  14, 0);
}

// Called periodically when isForeground==true (30Hz)
static void Draw() {
    char s[10];
    int x,y,i;

    //SetFontSize(2);

    rtc_time_t time = ClockGetTime();
    uint8 hour12 = ClockGet12Hour(time.hour);
    rtc_date_t date = ClockGetDate();


    //// Time ////
    y = 20;
    x = 10;
    x = DrawClockInt(x,y, hour12, false);
    x = DrawClockDigit(x,y, CLOCK_DIGIT_COLON);
    x = DrawClockInt(x,y, time.min, true);
    x = DrawClockDigit(x,y, (ClockIsPM(time.hour)) ? CLOCK_DIGIT_PM : CLOCK_DIGIT_AM);

    //// Date ////
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

    x = 44;
    y = 60;

    //// Upcoming Events ////

    //TODO: Sort events in circular order after the current time
    uint num = 0;

    rtc_dow_t tomorrow = date.day_of_week+1;
    if (tomorrow > dwSaturday) tomorrow = dwSunday;

    
    for (i=0; i<NUM_EVENTS; i++) {
        event_t* event = my_events[i];

        // First populate today's events
        if ((event->day == date.day_of_week) && (event->hr > time.hour) && (num <= 3)) {
            uint w;
            uint x2 = x;

            // Time
            sprintf(s, "%d:%02d", event->hr, event->min);
            w = MeasureImString(s) + 4;
            DrawImString(s, x2-w,y, SKYBLUE);
            x2 += 4;

            // Label
            DrawImString(event->label, x2,y, WHITE);
            y += active_imfont->char_height - 2;

            // Location
            if (event->location[0] != '\0') {
                DrawImString(event->location, x2,y, GRAY);
                y += active_imfont->char_height;
            }
            //y += 1;

            num++;
        }

        // Then populate tomorrow's events
        else if ((event->day > date.day_of_week) && (num <= 3)) {
            uint w;
            uint y2 = y;
            uint x2 = x;

            // Day & Time
            sprintf(s, "%d:%02d", event->hr, event->min);
            w = MeasureImString(s) + 4;
            DrawImString(s, x2-w,y2, HEXCOLOR(0xEEE));
            y2 += active_imfont->char_height - 2;

            w = MeasureImString(short_days[event->day]) + 4;
            DrawImString(short_days[event->day], x2-w,y2, GRAY);

            x2 += 4;

            // Label
            DrawImString(event->label, x2,y, WHITE);
            y += active_imfont->char_height - 2;

            // Location
            if (event->location[0] != '\0') {
                DrawImString(event->location, x2,y, GRAY);
            }
            y += active_imfont->char_height;
            //y += 1;
            num++;

        }
    }

    
}
