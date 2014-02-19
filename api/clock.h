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

typedef uint32 timestamp_t;


typedef enum {
    dwSunday=0, dwMonday, dwTuesday, dwWednesday, dwThursday, dwFriday, dwSaturday
} rtc_dow_t;

typedef struct {
	uint8 hour;
    uint8 min;
    uint8 sec;
} rtc_time_t;

typedef struct {
    rtc_dow_t day_of_week;
    uint8 day;
    uint8 month;
    uint8 year;
} rtc_date_t;

////////// Methods /////////////////////////////////////////////////////////////


void InitializeClock();

void ClockTimeToStr(char* s);

rtc_time_t ClockGetTime();
rtc_date_t ClockGetDate();

uint8 ClockGet12Hour(uint8 hour24);
#define ClockIsPM(hour24) (hour24 >= 12)

bool ClockSetTime(uint8 hour, uint8 minute, uint8 second);
bool ClockSetDate(rtc_dow_t day_of_week, uint8 day, uint8 month, uint8 year);

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

