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

//#define AUTO_DISABLE

#define AdcOn() AD1CON1bits.ADON = 1
#define AdcOff() AD1CON1bits.ADON = 0

#define mAdcEnabled (_ADC1MD==0)

#define VBG_VOLTAGE 1200UL //mV - Bandgap reference voltage

////////// Global Variables ////////////////////////////////////////////////////

volatile uint8 current_channel = 0;
volatile adc_channel_t adc_channels[ADC_CHANNELS];
volatile adc_status_t adc_status = adcDone;
//uint8 adc_channels = 0;

////////// Local Variables /////////////////////////////////////////////////////

// Store the initial vref, then calibrate
//uint16 vref = VREF;

volatile voltage_t vdd = 0; // Automatically set after any ADC conversion

////////// Prototypes //////////////////////////////////////////////////////////

void adc_enable();
void adc_disable();
void adc_Calibrate();

////////// Methods /////////////////////////////////////////////////////////////

void adc_init() {

    uint i;
    for (i=0; i<ADC_CHANNELS; i++) {
        adc_channels[i].callback = NULL;
        adc_channels[i].voltage = 0;
        adc_channels[i].abg = 0;
        adc_channels[i].ach = 0;
    }

    //adc_enable();

    //TODO: Configure the interrupt

    // Calibrate against the internal bandgap reference
    //adc_Calibrate();

    //adc_disable();
    //AD1CON1bits.ADON = 1;

}

void adc_enable() {
    _ADC1MD = 0; // Enable ADC peripheral

    AD1CON1 = ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF;
    AD1CON2 = ADC_VREF_AVDD_AVSS | ADC_SCAN_OFF | ADC_INTR_2_CONV | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_ON;
    AD1CON3 = ADC_CONV_CLK_SYSTEM | ADC_SAMPLE_TIME_31 | ADC_CONV_CLK_256Tcy;

    AD1CHS = ADC_CH0_NEG_SAMPLEB_VREFN | ADC_CH0_NEG_SAMPLEA_VREFN;

    // Enable bandgap on mux B
    _CH0SB = AN_VBG;
    ANCFG = 0x03;

    // Enable interrupts
    _AD1IF = 0;
    _AD1IE = 1;

    AD1CON1bits.ADON = 1;
}

void adc_disable() {
    AD1CON1bits.ADON = 0;   // Turn off ADC
    _ADC1MD = 1;            // Disable ADC peripheral
}


/*void adc_CalibrateFinished(uint16 value) {
    // Use the measured bandgap value to correct vref
    //TODO
}

void adc_SetBandgap(bool enabled) {
    // Enables VBG, VBG/2, VBG/6 reference inputs
    ANCFG = (enabled) ? 0x03 : 0x00;
}

void adc_Calibrate() {
    // Start conversion on the internal bandgap reference voltage

    adc_SetCallback(AN_VBG, adc_CalibrateFinished);
    adc_StartConversion(AN_VBG);
}*/


void adc_SetCallback(uint8 channel, adc_conversion_cb callback) {
    //adc_callbacks[channel] = callback;
    adc_channels[channel].callback = callback;
}

void adc_StartConversion(uint8 channel) {
    //TODO: What if we are already converting??
    if (!mAdcEnabled)
        adc_enable();

    adc_status = adcConverting;
    current_channel = channel;
    
    // Start ADC conversion on the specified channel
    _CH0SA = channel; // MUX A
    AD1CON1bits.ASAM = 1;
    AD1CON1bits.SAMP = 1;
}

// Blocking read for debugging
uint adc_Read(uint8 channel) {
    if (!mAdcEnabled)
        adc_enable();

    adc_status = adcConverting;
    current_channel = channel;

    volatile adc_channel_t* ch = &adc_channels[channel];
    ch->callback = NULL;

    _CH0SA = channel; // MUX A
    AD1CON1bits.ASAM = 1;
    AD1CON1bits.SAMP = 1;

    while (mAdcBusy);

    return adc_channels[channel].voltage;
}



////////// Interrupts //////////////////////////////////////////////////////////

void isr _ADC1Interrupt() {
    _AD1IF = 0;

    // ADC alternates between mux A and mux B,
    // and interrupt is triggered on every second sample.
    // Thus ADC1BUF0=VBG and ADC1BUF1=channel

    // Update Global Variables
    volatile adc_channel_t* ch = &adc_channels[current_channel];
    ch->abg = ADC1BUF1;
    ch->ach = ADC1BUF0;

    // Calibration
    vdd = VBG_VOLTAGE * 1024UL / (unsigned long)ch->abg;
    ch->voltage = (unsigned long)vdd * (unsigned long)ch->ach / 1024;

    // ADC Conversion Callback
    if (ch->callback != NULL) ch->callback(ch->voltage);

    AD1CON1bits.ASAM = 0;
    //AD1CON1bits.SAMP = 0;

    adc_status = adcDone;
    
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

