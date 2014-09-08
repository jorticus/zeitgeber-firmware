/*
 * File:   calendar.c
 * Author: Jared
 *
 * Created on 16 February 2014, 6:35 PM
 */

#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "calendar.h"
#include "api/graphics/gfx.h"


////////// Includes ////////////////////////////////////////////////////////////

////////// Variables ///////////////////////////////////////////////////////////

event_t event_alloc[MAX_EVENTS];
event_t *events[MAX_EVENTS];
uint num_events;

////////// Code ////////////////////////////////////////////////////////////////

event_t* malloc_event() {
   //event_t* event = (event_t*)malloc(sizeof(event_t));
    if (num_events == MAX_EVENTS)
        return NULL;
    event_t* event = &event_alloc[num_events++];

    if (event != NULL) {
        event->active = true;
        event->color = WHITE;
        event->label[0] = '\0';
        event->location[0] = '\0';
    }
    return event;
}

event_t* AddTimetableEvent(const char* label, const char* location, rtc_dow_t day, uint hr, uint min) {
    event_t* event = malloc_event();

    if (event != NULL) {
        strncpy(event->label, label, MAX_LABEL_LEN-1);
        event->label[MAX_LABEL_LEN-1] = '\0';

        strncpy(event->location, location, MAX_LABEL_LEN-1);
        event->location[MAX_LABEL_LEN-1] = '\0';
        
        event->day = day;
        event->hr = hr;
        event->min = min;
    }
    return event;
}

void CalendarAddEvent(event_t* event) {
    if (num_events < MAX_EVENTS) {
        event_t* new_event = malloc(sizeof(event_t));
        memcpy(new_event, event, sizeof(event_t));

        events[num_events] = new_event;
        num_events++;
    }
}


timestamp_t EventGetTimestamp(event_t* event) {
    timestamp_t ts = ClockGetTimestamp();

    // Weekly events
    if (event->event_type == etTimetableEvent) {
        //ts.day = event->day; TODO: event->day is a day_of_week, so need to find the day of the start of week first!
        ts.hour = event->hr;
        ts.min = event->min;
    }
    //TODO: other event types

    return ts;
}


event_t* CalendarGetNextEvent() {
    // Scan the calendar, find the next upcoming event
    uint i;
    timestamp_t next_ts = {MAX_UINT32};
    event_t* next_event = NULL;

    if (num_events == 0)
        return NULL;

    for (i=0; i<num_events; i++) {
        event_t* event = &events[i];
        timestamp_t ts = EventGetTimestamp(event);

        if (ts.ts < next_ts.ts) {
            next_ts = ts;
            next_event = event;
        }
    }
    
    return next_event;
}


int CalendarDrawEvent(uint8 x, uint8 y, event_t* event, color_t color) {
    char s[10];
    uint w;

    // Time
    sprintf(s, "%d:%02d", event->hr, event->min);
    w = MeasureImString(s) + 4;
    DrawImString(s, x-w,y, color);
    x += 4;

    // Label
    DrawImString(event->label, x,y, WHITE);
    y += active_imfont->char_height - 2;

    // Location
    if (event->location[0] != '\0') {
        DrawImString(event->location, x,y, WHITE);
        y += active_imfont->char_height;
    }
    //y += 1;

    //DrawBox(x-4,64, 2,24, SKYBLUE,SKYBLUE);

    return y;
}
