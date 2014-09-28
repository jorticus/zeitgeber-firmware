/*
 * File:   calendar.c
 * Author: Jared
 *
 * Created on 16 February 2014, 6:35 PM
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "system.h"
#include "calendar.h"
#include "api/graphics/gfx.h"
#include "api/clock.h"


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
    event_t* event = &event_alloc[num_events];
    
    events[num_events] = event;
    num_events++;

    if (event != NULL) {
        event->active = true;
        event->color = WHITE;
        event->label[0] = '\0';
        event->location[0] = '\0';
    }
    return event;
}

event_t* AddTimetableEvent(const char* label, const char* location, dow_t day_of_week, uint hr, uint min) {
    event_t* event = malloc_event();

    if (event != NULL) {
        strncpy(event->label, label, MAX_LABEL_LEN-1);
        event->label[MAX_LABEL_LEN-1] = '\0';

        strncpy(event->location, location, MAX_LABEL_LEN-1);
        event->location[MAX_LABEL_LEN-1] = '\0';
        
        event->dow = day_of_week;
        event->hr = hr;
        event->min = min;

        event->event_type = etTimetableEvent;
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


timestamp_t EventGetTimestamp(timestamp_t ts, event_t* event) {

    // Weekly events
    switch (event->event_type) {
        case etTimetableEvent: {
            // Find the next occurrance of this weekly event (occurring after the provided timestamp)

            int delta = event->dow - ts.dow;

            if (delta < 0)  // If event is in the future
                delta += 7; // then it must occur next week

            TimestampAddDay(&ts, delta);

            // And set the time to the event's time
            ts.hour = event->hr;
            ts.min = event->min;
            ts.sec = 0;
            break;
        }
        
        //TODO: other event types

        default: {
            timestamp_t nullts = {0};
            return nullts;
        }
    }

    // Cache the result
    event->next_occurrance = ts;

    return ts;
}


event_t* CalendarGetNextEvent(timestamp_t ts) {
    // Scan the calendar, find the next upcoming event
    uint i;
    event_t* next_event = NULL;
    uint32 next_ts = MAX_UINT32;

    if (num_events == 0)
        return NULL;

    // Find the next event that occurs after the given timestamp
    for (i=0; i<num_events; i++) {
        event_t* event = events[i];
        timestamp_t evt_ts = EventGetTimestamp(ts, event);

        if ((evt_ts.raw > ts.raw) && (evt_ts.raw < next_ts)) {
            next_ts = evt_ts.raw;
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
