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

////////// Defines /////////////////////////////////////////////////////////////

#define AUTO_DISABLE

#define AdcOn() AD1CON1bits.ADON = 1
#define AdcOff() AD1CON1bits.ADON = 0

#define mAdcEnabled (_ADC1MD==0)

////////// Global Variables ////////////////////////////////////////////////////

volatile uint8 adc_values[ADC_CHANNELS];
volatile adc_status_t adc_status[ADC_CHANNELS];
proc_t adc_callbacks[ADC_CHANNELS];
//uint8 adc_channels = 0;

////////// Local Variables /////////////////////////////////////////////////////

// Store the initial vref, then calibrate
uint16 vref = VREF;

////////// Prototypes //////////////////////////////////////////////////////////

void adc_enable();
void adc_disable();
void adc_calibrate();

////////// Methods /////////////////////////////////////////////////////////////

void adc_init() {

    /*uint i;
    for (i=0; i<ADC_CHANNELS; i++) {
        adc_values[i] = 0;
        adc_status[i] = adcDone;
        adc_callbacks[i] = NULL;
    }*/

    adc_enable();

    // Calibrate against the internal bandgap reference
    adc_calibrate();

    //adc_disable();
    //AD1CON1bits.ADON = 1;
}

void adc_enable() {
    _ADC1MD = 0; // Enable ADC peripheral

    AD1CON1 = ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF;
    AD1CON2 = ADC_VREF_AVDD_AVSS | ADC_SCAN_OFF | ADC_INTR_EACH_CONV | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF;
    AD1CON3 = ADC_CONV_CLK_SYSTEM | ADC_SAMPLE_TIME_31 | ADC_CONV_CLK_2Tcy;

    AD1CON1bits.ADON = 1;
}

void adc_disable() {
    AD1CON1bits.ADON = 0;   // Turn off ADC
    _ADC1MD = 1;            // Disable ADC peripheral
}


void adc_CalibrateFinished(uint16 value) {
    // Use the measured bandgap value to correct vref
    //TODO
}

void adc_Calibrate() {
    // Start conversion on the internal bandgap reference voltage

    adc_SetCallback(0, adc_CalibrateFinished);
    adc_StartConversion(0); //TODO: which channel?
}


void adc_SetCallback(uint8 channel, adc_conversion_cb callback) {
    adc_callbacks[channel] = callback;
}

void adc_StartConversion(uint8 channel) {

    if (!mAdcEnabled)
        adc_enable();

    adc_status[channel] = adcConverting;
    // Start ADC conversion on the specified channel
}



////////// Interrupts //////////////////////////////////////////////////////////

void isr _ADC1Interrupt() {
    // TODO: Clear ADC IE

    uint8 channel = 0; // TODO: Figure out which channel
    uint16 value = 0;

    // Update Global Variables
    adc_values[channel] = value;
    adc_status[channel] = adcDone;

    // ADC Conversion Callback
    adc_conversion_cb callback = adc_callbacks[channel];
    if (callback != NULL) callback(value);

    
    // If all conversions have finished, disable the ADC
#ifdef AUTO_DISABLE
    uint i;
    bool test = false;
    for (i=0; i<ADC_CHANNELS; i++) {
        if (adc_status[i] == adcConverting) {
            test = true;
            break;
        }
    }
    if (!test) adc_disable();
#endif
}
