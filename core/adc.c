/*
 * File:   adc.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 *
 * Internal VREF
 * Two ADC inputs:
 * AN_VBAT
 * AN_LIGHT
 *
 * Internal ADC channels:
 * VBG, VBG/2, VBG/6
 * VCAP
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#define USE_AND_OR
#include <adc.h>
#include "adc.h"


#define AdcOn() AD1CON1bits.ADON = 1
#define AdcOff() AD1CON1bits.ADON = 0


////////// Methods /////////////////////////////////////////////////////////////

void InitializeAdc() {
    _ADC1MD = 0; // Enable ADC peripheral

    AD1CON1 = ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF;
    AD1CON2 = ADC_VREF_AVDD_AVSS | ADC_SCAN_OFF | ADC_INTR_EACH_CONV | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF;
    AD1CON3 = ADC_CONV_CLK_SYSTEM | ADC_SAMPLE_TIME_31 | ADC_CONV_CLK_2Tcy;

    //AD1CON1bits.ADON = 1;
}

////////// Interrupts //////////////////////////////////////////////////////////

