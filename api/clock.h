/* 
 * File:   clock.h
 * Author: Jared
 *
 * Created on 9 July 2013, 2:40 PM
 *
 * Real-Time Clock module
 * The RTC will continue operating even in Sleep mode when all
 * other peripherals are disabled.
 */

#ifndef CLOCK_H
#define	CLOCK_H

////////// Defines /////////////////////////////////////////////////////////////

// 1: Enable RTC output, 0: Disable RTC output
#define RTCC_OUTPUT_EN 1

////////// Typedefs ////////////////////////////////////////////////////////////

typedef enum {
    MONDAY=0, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
} dow_t;

typedef struct {
    union {
        struct __attribute__((packed)) {
            unsigned sec: 6;    // 0-59 (0-63)
            unsigned min: 6;    // 0-59 (0-63)
            unsigned hour: 5;   // 0-24 (0-31)

            unsigned day: 5;    // 1-31 (0-31)
            unsigned month: 4;  // 1-12 (0-15)
            unsigned year: 6;   // 0-63  Maximum supported year is 2063!
        };
        uint32 raw;
    };
    dow_t dow;  // Day-of-week (Separate from the raw timestamp)
} timestamp_t;

////////// Methods /////////////////////////////////////////////////////////////


void InitializeClock();

void ClockTimeToStr(char* s);

timestamp_t ClockNow();

uint8 ClockGet12Hour(uint8 hour24);
#define ClockIsPM(hour24) (hour24 >= 12)

bool ClockSetTime(uint8 hour, uint8 minute, uint8 second);
bool ClockSetDate(dow_t day_of_week, uint8 day, uint8 month, uint8 year);
bool ClockSetTimestamp(timestamp_t ts);

void TimestampAddSecond(timestamp_t* ts, int seconds);
void TimestampAddMinute(timestamp_t* ts, int minutes);
void TimestampAddHour(timestamp_t* ts, int hours);
void TimestampAddDay(timestamp_t* ts, int days);


void RtcSetCalibration(int8 cal);

////////// Constants ///////////////////////////////////////////////////////////

// Localized calendar strings
extern const char* days[];          // Monday, Tuesday, ...
extern const char* short_days[];    // Mon, Tue, ...
extern const char* months[];        // January, February, ...
extern const char* short_months[];  // Jan, Feb, ...
extern const char* ampm[];          // am, pm
extern const char* day_suffix[];    // 0th, 1st, 2nd, 3rd, 4th

extern const int days_in_month[];

#endif	/* CLOCK_H */

