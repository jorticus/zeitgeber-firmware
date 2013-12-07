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

void BcdToStr(BYTE bcd, char* s) {
    s[0] = '0' + ((bcd & 0xF0) >> 4);
    s[1] = '0' + (bcd & 0x0F);
    s[2] = '\0';
}

BYTE BcdToInt(BYTE bcd) {
    return (bcd & 0x0F) + (((bcd & 0xF0)>>4)*10);
}

void RtcTimeToStr(char* s) {
    rtccTime tm;
    RtccReadTime_v1(&tm);

    sprintf(s, "%d:%d:%d",
            BcdToInt(tm.f.hour),
            BcdToInt(tm.f.min),
            BcdToInt(tm.f.sec)
    );

    /*BcdToStr(tm.f.hour, &s[0]);
    s[2] = ':';
    BcdToStr(tm.f.min, &s[3]);
    s[5] = ':';
    BcdToStr(tm.f.sec, &s[6]);*/

}

void RtcDateToStr(char* s) {

}

void RtcSetCalibration(int8 cal) {
    SetRtcWren();
    _CAL = cal;
    ClearRtcWren();
}