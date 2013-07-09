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

//TODO: Define available ADC channels
// or should this be in hardware.h ???

////////// Typedefs ////////////////////////////////////////////////////////////

typedef enum { adcDone, adcConverting } adc_status_t;

typedef void (*adc_conversion_cb)(uint16);

////////// Methods /////////////////////////////////////////////////////////////

extern void adc_init();

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