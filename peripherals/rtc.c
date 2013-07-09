/*
 * File:   rtc.c
 * Author: Jared
 *
 * Created on 5 July 2013, 3:07 PM
 */

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

}

void RtcSetCalibration(int8 cal) {
    SetRtcWren();
    _CAL = cal;
    ClearRtcWren();
}