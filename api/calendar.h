/* 
 * File:   calendar.h
 * Author: Jared
 *
 * Created on 16 February 2014, 6:35 PM
 */

#ifndef CALENDAR_H
#define	CALENDAR_H

#include "api/graphics/gfx.h"
#include "api/clock.h"
#include "util/timestamp.h"

#define MAX_EVENTS 32

#define MAX_LABEL_LEN 20
#define MAX_LOCATION_LEN 20

typedef enum {
    rpSingle,
    rpDaily,
    rpWeekdays,
    rpWeekly,
    crMonthly,
    crYearly
} calendar_repeat_t;


#define WEEKLY_MONDAY       1<<0
#define WEEKLY_TUESDAY      1<<1
#define WEEKLY_WEDNESDAY    1<<2
#define WEEKLY_THURSDAY     1<<3
#define WEEKLY_FRIDAY       1<<4
#define WEEKLY_SATURDAY     1<<5
#define WEEKLY_SUNDAY       1<<6



typedef struct {
    bool active;

    char label[MAX_LABEL_LEN];
    char location[MAX_LOCATION_LEN];
    color_t color;

    rtc_dow_t day;
    uint hr;
    uint min;

    //char* label;        // Dynamically allocated
    //char* location;

    //timestamp_t start;
    //timestamp_t end;
    //bool all_day;

    // Recurrance properties
    /*calendar_repeat_t repeat;
    uint8 repeat_weekly_days;
    uint8 every; // Every X days/weeks/months*/

    // Alarm/Notifications
    //bool beep;

    // Internal state
    timestamp_t next_run;

} event_t;



extern event_t *events[MAX_EVENTS];
extern uint num_events;

event_t* NewEvent(const char* label, const char* location, rtc_dow_t day, uint hr, uint min);
int CalendarDrawEvent(uint8 x, uint8 y, event_t* event, color_t color);


#endif	/* CALENDAR_H */

