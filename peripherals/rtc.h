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

typedef struct {
	uint8 hour12;
    uint8 hour24;
    uint8 min;
    uint8 sec;
    bool pm;
} rtc_time_t;

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

rtc_time_t RtcTime();

#endif	/* RTC_H */

