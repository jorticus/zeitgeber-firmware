/* 
 * File:   rtc.h
 * Author: Jared
 *
 * Created on 5 July 2013, 3:07 PM
 *
 * Real-Time Clock module
 * The RTC will continue operating even in Sleep mode when all
 * other peripherals are disabled.
 */

#ifndef RTC_H
#define	RTC_H

// 1: Enable RTC output, 0: Disable RTC output
#define RTCC_OUTPUT_EN 1

typedef enum {
    dwSunday=0, dwMonday, dwTuesday, dwWednesday, dwThursday, dwFriday, dwSaturday
} rtc_dow_t;

typedef struct {
	uint8 hour12;
    uint8 hour24;
    uint8 min;
    uint8 sec;
    bool pm;
} rtc_time_t;

typedef struct {
    rtc_dow_t day_of_week;
    uint8 day;
    uint8 month;
    uint8 year;
} rtc_date_t;

extern volatile rtc_time_t rtc_time;

extern void rtc_init();

// Localized calendar strings
extern const char* days[];          // Monday, Tuesday, ...
extern const char* short_days[];    // Mon, Tue, ...
extern const char* months[];        // January, February, ...
extern const char* short_months[];  // Jan, Feb, ...
extern const char* ampm[];          // am, pm

extern const int days_in_month[];

extern void RtcTimeToStr(char* s);

rtc_time_t RtcGetTime();
rtc_date_t RtcGetDate();

bool RtcSetTime(uint8 hour, uint8 minute, uint8 second);
bool RtcSetDate(rtc_dow_t day_of_week, uint8 day, uint8 month, uint8 year);

#endif	/* RTC_H */

