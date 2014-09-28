/*
 * File:   app.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdio.h>
#include <Rtcc.h>
#include "system.h"
#include "clock.h"
#include "util/util.h"
//#include "peripherals/rtc.h"

////////// Variables ///////////////////////////////////////////////////////////


#include "rtc_strings.h"

const int days_in_month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
// Note february will be +1 if year is a leap-year

////////// Methods /////////////////////////////////////////////////////////////

__inline__ void SetRtcWren() {
    asm volatile("disi #5");
    asm volatile("mov #0x55, w7");
    asm volatile("mov w7, _NVMKEY");
    asm volatile("mov #0xAA, w8");
    asm volatile("mov w8, _NVMKEY");
    asm volatile("bset _RCFGCAL, #13");
}

__inline__ void ClearRtcWren() {
    RCFGCALbits.RTCWREN = 0;
    /*asm volatile("disi #5");
    asm volatile("mov #0x55, w7");
    asm volatile("mov w7, _NVMKEY");
    asm volatile("mov #0xAA, w8");
    asm volatile("mov w8, _NVMKEY");
    asm volatile("bclr _RCFGCAL, #13");*/
}


void InitializeClock() {
    _RTCCMD = 0;    // Enable peripheral module
    Nop();          // Saftey NOP


    // Enable secondary oscillator
    OSCCONbits.SOSCEN = 1;

    SetRtcWren();

    // RTC Output pin
    _RTCOE = RTCC_OUTPUT_EN;
    _RTSECSEL = 1; // Output seconds clock on RTC pin

    // Alarm
    _ALRMEN = 0;

    // Enable RTC
    RCFGCALbits.RTCEN = 1;

    // Note that the RCFGCAL and ACLFGRPT registers are only cleared
    // on a Power-on-Reset. The RTC will continue operating on any
    // other kind of reset (though the alarm will be disabled)

    ClearRtcWren();
}


void ClockTimeToStr(char* s) {
    rtccTime tm;
    RtccReadTime(&tm);

    sprintf(s, "%d:%d:%d",
            bcd2int(tm.f.hour),
            bcd2int(tm.f.min),
            bcd2int(tm.f.sec)
    );

    /*BcdToStr(tm.f.hour, &s[0]);
    s[2] = ':';
    BcdToStr(tm.f.min, &s[3]);
    s[5] = ':';
    BcdToStr(tm.f.sec, &s[6]);*/

}

int ClockDaySuffix(int day) {
    int i = day / 10;
    i = day - i*10;
    if (i > 4) i = 4;
    return i;
}

timestamp_t ClockNow() {
    timestamp_t ts;
    rtccTimeDate rtcc;

    RtccReadTimeDate(&rtcc);

    ts.hour = bcd2int(rtcc.f.hour);
    ts.min = bcd2int(rtcc.f.min);
    ts.sec = bcd2int(rtcc.f.sec);

    ts.day = bcd2int(rtcc.f.mday);
    ts.month = bcd2int(rtcc.f.mon);
    ts.year = bcd2int(rtcc.f.year);

    ts.dow = bcd2int(rtcc.f.wday);
    
    return ts;
}

uint8 ClockGet12Hour(uint8 hour24) {
    uint8 hour12 = hour24;

    if (hour24 == 0)
        return 12;
    else if (hour24 > 12)
        return hour24 - 12;
    else
        return hour24;
}

bool ClockSetTime(uint8 hour, uint8 minute, uint8 second) {
    bool result;
    rtccTime tm;
    tm.l = 0x00000000;
    tm.f.hour = int2bcd(hour);
    tm.f.min = int2bcd(minute);
    tm.f.sec = int2bcd(second);

    SetRtcWren();
    result = RtccWriteTime(&tm, true);
    ClearRtcWren();
    return result; // Returns false if values are out of range
}

bool ClockSetDate(dow_t day_of_week, uint8 day, uint8 month, uint8 year) {
    bool result;
    rtccDate dt;
    dt.l = 0x00000000;
    dt.f.wday = int2bcd(day_of_week);
    dt.f.mday = int2bcd(day);
    dt.f.mon = int2bcd(month);
    dt.f.year = int2bcd(year);

    SetRtcWren();
    result = RtccWriteDate(&dt, true);
    ClearRtcWren();
    return result; // Returns false if values are out of range
}

bool ClockSetTimestamp(timestamp_t ts) {
    return
        ClockSetTime(ts.hour, ts.min, ts.sec) &&
        ClockSetDate(ts.dow, ts.day, ts.month, ts.year);
}

void RtcSetCalibration(int8 cal) {
    SetRtcWren();
    _CAL = cal;
    ClearRtcWren();
}

static inline int AddCarry(int a, int b, int min, int max, int* carry) {
    int result = a + b;
    int _carry = 0;
    int delta = max - min + 1;

    while (result > max) {
        result -= delta;
        _carry++;
    }
    while (result < min) {
        result += delta;
        _carry--;
    }

    if (carry != NULL) *carry = _carry;
    return result;
}

void TimestampAddSecond(timestamp_t* ts, int seconds) {
    int carry = 0;
    ts->sec = (byte)AddCarry(ts->sec, seconds, 0, 59, &carry);
    if (carry != 0) {
        TimestampAddMinute(ts, carry);
    }
}

void TimestampAddMinute(timestamp_t* ts, int minutes) {
    int carry = 0;
    ts->min = (byte)AddCarry(ts->min, minutes, 0, 59, &carry);
    if (carry != 0) {
        TimestampAddHour(ts, carry);
    }
}

void TimestampAddHour(timestamp_t* ts, int hours) {
    int carry = 0;
    ts->hour = (byte)AddCarry(ts->hour, hours, 1, 12, &carry);
    if (carry != 0) {
        TimestampAddDay(ts, carry);
    }
}

void TimestampAddDay(timestamp_t* ts, int days) {
    int dim = days_in_month[ts->month];

    if ((days >= dim) || (days < -dim))
        return;  // Adding or subtracting more than 1 month is not supported! //TODO: Support

    int carry = 0;
    ts->day = (byte)AddCarry(ts->day, days, 1, dim, &carry);
    if (carry != 0) {
        ts->month = (byte)AddCarry(ts->month, carry, 1, 12, &carry);
        if (carry != 0) {
            ts->year += carry;
        }
    }

    // Also alter the current day-of-week
    ts->dow = (byte)AddCarry(ts->dow, days, 0, 6, NULL);
}
