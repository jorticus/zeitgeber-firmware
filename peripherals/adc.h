/*
 * File:   adc.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

#ifndef ADC_H
#define	ADC_H

////////// Defines /////////////////////////////////////////////////////////////

#define ADC_CHANNELS 8

#define VREF 3300 //mV  //TODO: Calibrate

// Additional analog channels
#define AN_VBG2     24
#define AN_VBG      25
#define AN_VCAP     26
#define AN_VBG6     27

////////// Typedefs ////////////////////////////////////////////////////////////

typedef enum { adcDone, adcConverting } adc_status_t;

typedef void (*adc_conversion_cb)(uint16);

////////// Methods /////////////////////////////////////////////////////////////

void adc_init();
void adc_enable();
void adc_disable();
uint adc_Read(uint8 channel);
void adc_SetBandgap(bool enabled);

// Optionally register a callback for the ADC channel. Set to NULL to disable callback
// WARNING: Called from within an ISR, take care to make sure it's thread-safe!
extern void adc_SetCallback(uint8 channel, adc_conversion_cb callback);

// Start conversion on the specified channel
extern void adc_StartConversion(uint8 channel);

////////// Properties //////////////////////////////////////////////////////////

// Stores the latest ADC conversion
extern volatile uint8 adc_values[ADC_CHANNELS];

// Poll this to tell when the channel has finished conversion
extern volatile adc_status_t adc_status[ADC_CHANNELS];

////////// Macros //////////////////////////////////////////////////////////////

#define mAdcChannelBusy(channel) (adc_status[channel]!=adcDone)
#define mAdcValue(channel) (adc_values[channel])

#endif	/* ADC_H */