/*
 * File:   adc.h
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

#ifndef ADC_H
#define	ADC_H

////////// Defines /////////////////////////////////////////////////////////////

#define ADC_CHANNELS 30

//#define VREF 3300 //mV  //TODO: Calibrate

// Additional analog channels
#define AN_VBG2     24
#define AN_VBG      25
#define AN_VCAP     26
#define AN_VBG6     27

////////// Typedefs ////////////////////////////////////////////////////////////

typedef uint16 voltage_t;

typedef enum { adcDone, adcConverting } adc_status_t;

typedef void (*adc_conversion_cb)(voltage_t);

typedef struct {
    adc_conversion_cb callback;     // Callback when conversion is done

    // The following values are not valid if adc_status == adcConverting:
    voltage_t voltage;                 // Calibrated voltage reading
    uint16 ach;                     // Raw channel reading
    uint16 abg;                     // Raw bandgap reading
} adc_channel_t;

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
extern volatile adc_channel_t adc_channels[ADC_CHANNELS];
extern volatile adc_status_t adc_status;

extern volatile voltage_t vdd;

// Poll this to tell when the channel has finished conversion
//extern volatile adc_status_t adc_status[ADC_CHANNELS];

////////// Macros //////////////////////////////////////////////////////////////

//#define mAdcChannelBusy(channel) (adc_status[channel]!=adcDone)
#define mAdcBusy (adc_status!=adcDone)
#define mAdcValue(channel) (adc_values[channel])

#endif	/* ADC_H */