/* 
 * File:   systick.h
 * Author: Jared
 *
 * Created on 5 July 2013, 2:56 PM
 *
 * Provides a system tick, used in the system task scheduler
 */

#ifndef SYSTICK_H
#define	SYSTICK_H

#define SYSTICK_PERIOD 1 //ms
#define SYSTICK_PRESCALER 8  // 1, 8, 64, 256

// Calculations
#define SYSTICK_PR (POSC/2 / SYSTICK_PRESCALER * SYSTICK_PERIOD / 1000)
#define SYSTICK_PS_VAL(val) T1_PS_1_##val   // lookup the relevant T1_PS_1_x define
#define SYSTICK_PS(val) SYSTICK_PS_VAL(val) // required for the macro to work


extern volatile uint systick;

void systick_init();

#endif	/* SYSTICK_H */

