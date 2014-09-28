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

extern event_t *events[];
extern uint num_events;

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
static void Initialize() {
    //                       label      loc     day        hr min
    AddTimetableEvent("ENCE462", "Fri", FRIDAY,  14, 0);
    AddTimetableEvent("COSC418", "Er235", MONDAY,    15, 0);
    AddTimetableEvent("ENCE463", "KD05",  THURSDAY,  11, 0);
    AddTimetableEvent("ENCE462", "Mon", MONDAY,    12, 0);
    
    AddTimetableEvent("ENCE463", "KF07",  TUESDAY,    9, 0);
    AddTimetableEvent("ENCE462", "Tue",  TUESDAY,   12, 0);
    AddTimetableEvent("ENCE463", "E11",   WEDNESDAY, 10, 0);
}

// Called periodically when isForeground==true (30Hz)
static void Draw() {
    char s[50];
    int x,y,i;
    int cx, cy, r;
    static int a = 0;

    //SetFontSize(2);

    timestamp_t now = ClockNow();
    uint8 hour12 = ClockGet12Hour(now.hour);
    
    //// Analog Clock ////
#if 0
    DrawString("12", 64-6, 6, GRAY);
    DrawString("3", 128-8, 64-4, GRAY);
    DrawString("6", 64-6, 128-10, GRAY);
    DrawString("9", 2, 64-4, GRAY);

    DrawLinePolar(54, time.sec * 512 / 60, 64, 64, HEXCOLOR(0x444444));
    DrawLinePolar(35, time.hour * 512 / 12, 64, 64, SKYBLUE);
    DrawLinePolar(50, time.min * 512 / 60, 64, 64, SKYBLUE);
#endif

    //// Time ////
    y = 16;
    x = 10;
    x = DrawClockInt(x,y, hour12, false);
    x = DrawClockDigit(x,y, CLOCK_DIGIT_COLON);
    x = DrawClockInt(x,y, now.min, true);
    x = DrawClockDigit(x,y, (ClockIsPM(now.hour)) ? CLOCK_DIGIT_PM : CLOCK_DIGIT_AM);

    //// Date ////
    y = 45;

    sprintf(s, "%d/%02d", now.day, now.month);
    x = 64 - (StringWidth(s) / 2);
    x = DrawImString(s, x,y, WHITE);


    x = 128 - 16 - StringWidth(short_days[now.dow]);
    x = DrawImString(short_days[now.dow], x,y, WHITE);


    //// Upcoming Events ////

    x = 55;
    y = 60;

    timestamp_t ts = now;
    for (i=0; i<3; i++) {
        
        event_t* event = CalendarGetNextEvent(ts);
        if (event == NULL)
            break;

        ts = event->next_occurrance;

        bool occurs_today = (event->dow == now.dow);
        color_t accent = (occurs_today) ? SKYBLUE : HEXCOLOR(0xEEE);

        uint w;
        uint x2 = x;

        // Time
        sprintf(s, "%d:%02d", event->hr, event->min);
        w = MeasureImString(s) + 4;
        DrawImString(s, x-w,y, accent);
        x2 += 4;

        // Label
        DrawImString(event->label, x2,y, WHITE);
        y += active_imfont->char_height - 2;

        bool double_height = false;

        // Location
        if (event->location[0] != '\0') {
            DrawImString(event->location, x2,y, GRAY);
            double_height = true;
        }

        // Day (if not today)
        if (!occurs_today) {
            const char* day_s = short_days[event->dow];
            w = MeasureImString(day_s) + 4;
            DrawImString(day_s, x-w,y, GRAY);
            double_height = true;
        }

        if (double_height) {
             y += active_imfont->char_height;
        }
    }

}
