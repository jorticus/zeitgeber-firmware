/*
 * File:   rtc.c
 * Author: Jared
 *
 * Created on 5 July 2013, 3:07 PM
 */

#include <stdio.h>
#include <system.h>
#include <Rtcc.h>
#include "rtc.h"

#include "rtc_strings.h"

const int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
// Note february will be +1 if year is a leap-year


volatile rtc_time_t rtc_time;

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



void rtc_init() {
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

    // Initialize date/time
    rtccTime tm;
    tm.l = 0x00000000;
    RtccWriteTime(&tm, true);
   /* rtccTimeDate td;
    td.f.year = 0x13;
    td.f.mon = 0x08;
    td.f.mday = 0x17;
    td.f.wday = 0x06;
    td.f.hour = 0x16;
    td.f.min = 0x00;
    td.f.sec = 0x00;
    RtccWriteTimeDate(&td, false);*/

}

void bcd2str(BYTE bcd, char* s) {
    s[0] = '0' + ((bcd & 0xF0) >> 4);
    s[1] = '0' + (bcd & 0x0F);
    s[2] = '\0';
}

byte bcd2int(byte bcd) {
    return (bcd & 0x0F) + (((bcd & 0xF0)>>4)*10);
}

byte int2bcd(byte i) {
     return ((i / 10) << 4) | (i % 10);
    /*byte result;
    while (i >= 10) {
        i -= 10;
        result += 0x10;
    }
    return result + i;*/
}

void RtcTimeToStr(char* s) {
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

rtc_time_t RtcGetTime() {
    rtc_time_t time;
    rtccTime tm;

    RtccReadTime(&tm);

    time.hour24 = bcd2int(tm.f.hour);
    time.min = bcd2int(tm.f.min);
    time.sec = bcd2int(tm.f.sec);

    if (time.hour24 > 12) {
        time.hour12 = time.hour24 - 12;
        time.pm = true;
    } else {
        time.hour12 = time.hour24;
        time.pm = false;
    }

    return time;
}

rtc_date_t RtcGetDate() {
    rtc_date_t date;
    rtccDate dt;

    RtccReadDate(&dt);
    date.day_of_week = bcd2int(dt.f.wday);
    date.day = bcd2int(dt.f.mday);
    date.month = bcd2int(dt.f.mon);
    date.year = bcd2int(dt.f.year);

    return date;
}

void RtcSetTimesfd(rtc_time_t time) {
    // Initialize date/time
    rtccTime tm;
    tm.l = 0x00000000;
    tm.f.hour = time.hour24;
    RtccWriteTime(&tm, false);
   /* rtccTimeDate td;
    td.f.year = 0x13;
    td.f.mon = 0x08;
    td.f.mday = 0x17;
    td.f.wday = 0x06;
    td.f.hour = 0x16;
    td.f.min = 0x00;
    td.f.sec = 0x00;
    RtccWriteTimeDate(&td, false);*/
}

bool RtcSetTime(uint8 hour, uint8 minute, uint8 second) {
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

bool RtcSetDate(rtc_dow_t day_of_week, uint8 day, uint8 month, uint8 year) {
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

void RtcSetCalibration(int8 cal) {
    SetRtcWren();
    _CAL = cal;
    ClearRtcWren();
}