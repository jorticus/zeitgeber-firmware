#ifndef TIMER_H
#define TIMER_H

 /******************************************************************************
 *
 *                  TIMER PERIPHERAL LIBRARY HEADER FILE
 *
 ******************************************************************************
 * FileName:        timer.h
 * Dependencies:    See include below
 * Processor:       PIC24
 * Compiler:        MPLAB C30
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *****************************************************************************/

#include "PIC24F_periph_features.h"

//This preprocessor conditional statement is to avoid unintended linking for unsuppported devices.
#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2) || defined (LIB_BUILD)
/*Registers Defaults*/
#define TMR1_VALUE          0x0000
#define PR1_VALUE           0xFFFF
#define T1CON_VALUE         0x0000

#ifndef USE_AND_OR /* Format for AND_OR based bit setting */
/* Timer1 Control Register (T1CON) Bit Defines */
#define T1_ON               0xffff  /* Timer1 ON */
#define T1_OFF              0x7fff  /* Timer1 OFF */

#define T1_IDLE_CON         0xdfff /* operate during sleep */
#define T1_IDLE_STOP        0xffff /* stop operation during sleep */

#if defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2)
#define T1_CLK_LPRC         0xfeff /* Timer extended clock source using LPRC oscillator */
#define T1_CLK_EXT        	0xfdff /* Timer extended clock source using external clock input */
#define T1_CLK_SOSC       	0xfcff /* Timer extended clock source using Secondary oscillator */
#endif

#define T1_GATE_ON          0xffff /* Timer Gate time accumulation enabled */
#define T1_GATE_OFF         0xffbf /* Timer Gate time accumulation disabled */

#define T1_PS_1_1           0xffcf /* Prescaler 1:1 */
#define T1_PS_1_8           0xffdf /* Prescaler 1:8 */
#define T1_PS_1_64          0xffef /* Prescaler 1:64 */
#define T1_PS_1_256         0xffff /* Prescaler 1:256 */

#define T1_SYNC_EXT_ON      0xffff /* Synch external clk input */
#define T1_SYNC_EXT_OFF     0xfffb /* Do not synch external clk input */

#define T1_SOURCE_EXT       0xffff /* External clock source */
#define T1_SOURCE_INT       0xfffd /* Internal clock source */

/* defines for Timer Interrupts */
#define T1_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T1_INT_PRIOR_6      0xfffe /* 110 = Interrupt is priority 6 */
#define T1_INT_PRIOR_5      0xfffd /* 101 = Interrupt is priority 5 */
#define T1_INT_PRIOR_4      0xfffc /* 100 = Interrupt is priority 4 */
#define T1_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T1_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T1_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T1_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */

#define T1_INT_ON           0xffff /* Interrupt Enable */
#define T1_INT_OFF          0xfff7 /* Interrupt Disable */

#else /* Format for backward compatibility (AND based bit setting). */

/* T1CON: TIMER1 CONTROL REGISTER */   
#define T1_ON               0x8000 /* Timer1 ON */
#define T1_OFF              0x0000 /* Timer1 OFF */
#define T1_OFF_ON_MASK      (~T1_ON)

#define T1_IDLE_STOP        0x2000 /* operate during sleep */
#define T1_IDLE_CON         0x0000 /* stop operation during sleep */
#define T1_IDLE_MASK        (~T1_IDLE_STOP)

#if defined (tmr_v1_4) || defined (tmr_v2_1) || defined (tmr_v2_2)
#define T1_CLK_LPRC         0x0200 /* Timer extended clock source using LPRC oscillator */
#define T1_CLK_EXT        	0x0100 /* Timer extended clock source using external clock input */
#define T1_CLK_SOSC       	0x0000 /* Timer extended clock source using Secondary oscillator */
#define T1_CLK_MASK        (~T1_EXTND_CLK)
#endif

#define T1_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T1_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T1_GATE_MASK        (~T1_GATE_ON)

#define T1_PS_1_1           0x0000 /* Prescaler 1:1 */
#define T1_PS_1_8           0x0010 /* Prescaler 1:8 */
#define T1_PS_1_64          0x0020 /* Prescaler 1:64 */
#define T1_PS_1_256         0x0030 /* Prescaler 1:256 */ 
#define T1_PS_MASK          (~T1_PS_1_256)

#define T1_SYNC_EXT_ON      0x0004 /* Synch external clk input */
#define T1_SYNC_EXT_OFF     0x0000 /* Do not synch external clk input */
#define T1_SYNC_EXT_MASK    (~T1_SYNC_EXT_ON)

#define T1_SOURCE_EXT       0x0002 /* External clock source */
#define T1_SOURCE_INT       0x0000 /* Internal clock source */
#define T1_SOURCE_MASK      (~T1_SOURCE_EXT)

/* defines for Timer Interrupts */
#define T1_INT_PRIOR_0      0x0000 /* 000 = Interrupt is priority 0 */
#define T1_INT_PRIOR_1      0x0001 /* 001 = Interrupt is priority 1 */
#define T1_INT_PRIOR_2      0x0002 /* 010 = Interrupt is priority 2 */
#define T1_INT_PRIOR_3      0x0003 /* 011 = Interrupt is priority 3 */
#define T1_INT_PRIOR_4      0x0004 /* 100 = Interrupt is priority 4 */
#define T1_INT_PRIOR_5      0x0005 /* 101 = Interrupt is priority 5 */
#define T1_INT_PRIOR_6      0x0006 /* 110 = Interrupt is priority 6 */
#define T1_INT_PRIOR_7      0x0007 /* 111 = Interrupt is priority 7 */
#define T1_INT_PRIOR_MASK   (~T1_INT_PRIOR_7) 

#define T1_INT_ON           0x0008 /* Interrupt Enable */
#define T1_INT_OFF          0x0000 /* Interrupt Disable */
#define T1_INT_MASK         (~T1_INT_ON)
    
#endif /* USE_AND_OR */

/**********************************************************************
Macro       : EnableIntT1

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT1                    (IEC0bits.T1IE = 1)

/**********************************************************************
Macro       : DisableIntT1

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT1                   (IEC0bits.T1IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT1(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT1(priority)     (IPC0bits.T1IP = priority)

/*******************************************************************
Macro       : T1_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T1_Clear_Intr_Status_Bit     (IFS0bits.T1IF = 0)


/* Timer1 Function Prototypes */
void __attribute__ ((section(".libperi"))) OpenTimer1( unsigned int config, unsigned int period);

void __attribute__ ((section (".libperi"))) CloseTimer1(void);

unsigned int __attribute__ ((section (".libperi"))) ReadTimer1(void);

void __attribute__ ((section (".libperi"))) WriteTimer1( unsigned int timer);

void __attribute__ ((section (".libperi"))) ConfigIntTimer1(unsigned int config);


/*Registers Defaults*/
#define TMR2_VALUE          0x0000
#define PR2_VALUE           0xFFFF
#define T2CON_VALUE         0x0000

#ifndef USE_AND_OR /* Format for AND_OR based bit setting */  
/* Timer2 Control Register (T2CON) Bit Defines */
#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T2_ON               0xffff /* Timer2 ON */
#define T2_OFF              0x7fff /* Timer2 OFF */
#elif defined (tmr_v2_1) || defined (tmr_v2_2) 
#define T2_ON               0xff /* Timer2 ON */
#define T2_OFF              0xbf /* Timer2 OFF */
#endif

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T2_IDLE_CON         0xdfff /* operate during sleep */
#define T2_IDLE_STOP        0xffff /* stop operation during sleep */

#define T2_GATE_ON          0xffff /* Timer2 Gate time accumulation enabled  */
#define T2_GATE_OFF         0xffbf /* Timer2 Gate time accumulation disabled */
#endif

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T2_PS_1_1           0xffcf /* Prescaler 1:1   */
#define T2_PS_1_8           0xffdf /*Prescaler 1:8   */
#define T2_PS_1_64          0xffef /*Prescaler 1:64  */
#define T2_PS_1_256         0xffff  /*Prescaler 1:256 */
#elif defined (tmr_v2_1) || defined (tmr_v2_2) 
#define T2_PS_1_1      0xfc  //Timer2 Prescale 1:1
#define T2_PS_1_4      0xfd  //Timer2 Prescale 1:4
#define T2_PS_1_16     0xfe  //Timer2 Prescale 1:16
#endif

/* Timer 2 and Timer 3 form a 32 bit Timer */
#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T2_32BIT_MODE_ON    0xffff      
#define T2_32BIT_MODE_OFF   0xfff7      

#define T2_SOURCE_EXT       0xffff /* External clock source */
#define T2_SOURCE_INT       0xfffd /* Internal clock source */
#endif

#if defined (tmr_v2_1) || defined (tmr_v2_2)
#define T2_POST_1_1    0x87  //Timer2 Postscaler 1:1
#define T2_POST_1_2    0x8f  //Timer2 Postscaler 1:2
#define T2_POST_1_3    0x97  //Timer2 Postscaler 1:3
#define T2_POST_1_4    0x9f  //Timer2 Postscaler 1:4
#define T2_POST_1_5    0xa7  //Timer2 Postscaler 1:5
#define T2_POST_1_6    0xaf  //Timer2 Postscaler 1:6
#define T2_POST_1_7    0xb7  //Timer2 Postscaler 1:7
#define T2_POST_1_8    0xbf  //Timer2 Postscaler 1:8
#define T2_POST_1_9    0xc7  //Timer2 Postscaler 1:9
#define T2_POST_1_10   0xcf  //Timer2 Postscaler 1:10
#define T2_POST_1_11   0xd7  //Timer2 Postscaler 1:11
#define T2_POST_1_12   0xdf  //Timer2 Postscaler 1:12
#define T2_POST_1_13   0xe7  //Timer2 Postscaler 1:13
#define T2_POST_1_14   0xef //Timer2 Postscaler 1:14
#define T2_POST_1_15   0xf7  //Timer2 Postscaler 1:15
#define T2_POST_1_16   0xff  //Timer2 Postscaler 1:16
#endif

/* defines for Timer Interrupts */
#define T2_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T2_INT_PRIOR_6      0xfffe /* 110 = Interrupt is priority 6 */
#define T2_INT_PRIOR_5      0xfffd /* 101 = Interrupt is priority 5 */
#define T2_INT_PRIOR_4      0xfffc /* 100 = Interrupt is priority 4 */
#define T2_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T2_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T2_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T2_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */

#define T2_INT_ON           0xffff /* Interrupt Enable */
#define T2_INT_OFF          0xfff7 /* Interrupt Disable */

#else /* Format for backward compatibility (AND based bit setting). */

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T2_ON               0x8000 /* Timer2 ON */
#define T2_OFF              0x0000 /* Timer2 OFF */
#elif defined (tmr_v2_1) || defined (tmr_v2_2)
#define T2_ON               0x04 /* Timer2 ON */
#define T2_OFF              0x00 /* Timer2 OFF */
#endif
#define T2_OFF_ON_MASK      (~T2_ON)

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T2_IDLE_STOP        0x2000 /* operate during sleep */
#define T2_IDLE_CON         0x0000 /* stop operation during sleep */
#define T2_IDLE_MASK        (~T2_IDLE_STOP)

#define T2_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T2_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T2_GATE_MASK        (~T2_GATE_ON)
#endif

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T2_PS_1_1           0x0000  /* Prescaler    1:1 */
#define T2_PS_1_8           0x0010  /* Prescaler    1:8 */
#define T2_PS_1_64          0x0020  /* Prescaler    1:64 */
#define T2_PS_1_256         0x0030  /*Prescaler     1:256 */
#define T2_PS_MASK          (~T2_PS_1_256)
#elif defined (tmr_v2_1) || defined (tmr_v2_2)
#define T2_PS_1_1      0x00  //Timer2 Prescale 1:1
#define T2_PS_1_4      0x01  //Timer2 Prescale 1:4
#define T2_PS_1_16     0x03  //Timer2 Prescale 1:16
#define T2_PS_MASK 		(~T2_PS_1_16)	//Mask Timer2 Input Clock Prescale Select bits
#endif

/* Timer 2 and Timer 3 form a 32 bit Timer */
#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T2_32BIT_MODE_ON    0x0008 /*Timer 32 bit mode enalbed*/     
#define T2_32BIT_MODE_OFF   0x0000 /*Timer 32 bit mode disalbed*/
#define T2_32BIT_MODE_MASK   (~T2_32BIT_MODE_ON)

#define T2_SOURCE_EXT       0x0002 /* External clock source */
#define T2_SOURCE_INT       0x0000 /* Internal clock source */
#define T2_SOURCE_MASK      (~T2_SOURCE_EXT)
#endif

#if defined (tmr_v2_1) || defined (tmr_v2_2)
#define T2_POST_1_1    0x00  //Timer2 Postscaler 1:1
#define T2_POST_1_2    0x08  //Timer2 Postscaler 1:2
#define T2_POST_1_3    0x10  //Timer2 Postscaler 1:3
#define T2_POST_1_4    0x18  //Timer2 Postscaler 1:4
#define T2_POST_1_5    0x20  //Timer2 Postscaler 1:5
#define T2_POST_1_6    0x28  //Timer2 Postscaler 1:6
#define T2_POST_1_7    0x30  //Timer2 Postscaler 1:7
#define T2_POST_1_8    0x38  //Timer2 Postscaler 1:8
#define T2_POST_1_9    0x40  //Timer2 Postscaler 1:9
#define T2_POST_1_10   0x48  //Timer2 Postscaler 1:10
#define T2_POST_1_11   0x50  //Timer2 Postscaler 1:11
#define T2_POST_1_12   0x58  //Timer2 Postscaler 1:12
#define T2_POST_1_13   0x60  //Timer2 Postscaler 1:13
#define T2_POST_1_14   0x68 //Timer2 Postscaler 1:14
#define T2_POST_1_15   0x70 //Timer2 Postscaler 1:15
#define T2_POST_1_16   0x78  //Timer2 Postscaler 1:16
#define	T2_POST_MASK	(~T2_POST_1_16)	//Mask Timer2 Postscale Selection bits
#endif

/* defines for Timer Interrupts */
#define T2_INT_PRIOR_0      0x0000 /* 000 = Interrupt is priority 0 */
#define T2_INT_PRIOR_1      0x0001 /* 001 = Interrupt is priority 1 */
#define T2_INT_PRIOR_2      0x0002 /* 010 = Interrupt is priority 2 */
#define T2_INT_PRIOR_3      0x0003 /* 011 = Interrupt is priority 3 */
#define T2_INT_PRIOR_4      0x0004 /* 100 = Interrupt is priority 4 */
#define T2_INT_PRIOR_5      0x0005 /* 101 = Interrupt is priority 5 */
#define T2_INT_PRIOR_6      0x0006 /* 110 = Interrupt is priority 6 */
#define T2_INT_PRIOR_7      0x0007 /* 111 = Interrupt is priority 7 */
#define T2_INT_PRIOR_MASK   (~T2_INT_PRIOR_7)       

#define T2_INT_ON           0x0008 /* Interrupt Enable */
#define T2_INT_OFF          0x0000 /* Interrupt Disable */
#define T2_INT_MASK         (~T2_INT_ON)

#endif /* USE_AND_OR */

/**********************************************************************
Macro       : EnableIntT2

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT2                    (IEC0bits.T2IE = 1)

/**********************************************************************
Macro       : DisableIntT2

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT2                  (IEC0bits.T2IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT2(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT2(priority)     (IPC1bits.T2IP = priority)

/*******************************************************************
Macro       : T2_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T2_Clear_Intr_Status_Bit     (IFS0bits.T2IF = 0)


/* Timer2 Function Prototypes */

/* OpenTimer2 */
void __attribute__ ((section(".libperi"))) OpenTimer2(unsigned int config, unsigned int period);

void __attribute__ ((section (".libperi"))) CloseTimer2(void);

unsigned int __attribute__ ((section (".libperi"))) ReadTimer2(void);

void __attribute__ ((section (".libperi"))) WriteTimer2( unsigned int timer);

void __attribute__ ((section (".libperi"))) ConfigIntTimer2(unsigned int config);


/*Registers Defaults*/
#define TMR3_VALUE          0x0000
#define PR3_VALUE           0xFFFF
#define T3CON_VALUE         0x0000

#ifndef USE_AND_OR /* Format for AND_OR based bit setting */
/* Timer3 Control Register (T3CON) Bit Defines */
#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T3_ON               0xffff /* Timer3 ON */      
#define T3_OFF              0x7fff /* Timer3 OFF */   
#elif defined (tmr_v2_1) || defined (tmr_v2_2) 
#define T3_ON         		0xff  //Timer3 ON 
#define T3_OFF         		0xfe  //Timer3 OFF 
#endif


#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T3_IDLE_CON         0xdfff  /* operate during sleep */    
#define T3_IDLE_STOP        0xffff  /* stop operation during sleep */

#define T3_GATE_ON          0xffff/* Timer3 Gate  time accumulation enabled  */      
#define T3_GATE_OFF         0xffbf /* Timer Gate time accumulation disabled */
#endif

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T3_PS_1_1           0xffcf /* Prescaler 1:1   */
#define T3_PS_1_8           0xffdf /*Prescaler 1:8   */
#define T3_PS_1_64          0xffef /*Prescaler 1:64  */
#define T3_PS_1_256         0xffff /*Prescaler 1:256 */
#elif defined (tmr_v2_1) || defined (tmr_v2_2)
#define T3_PS_1_1        	0xcf  //Timer3 1:1 prescale value
#define T3_PS_1_2        	0xdf  //Timer3 1:2 prescale value
#define T3_PS_1_4        	0xef  //Timer3 1:4 prescale value
#define T3_PS_1_8        	0xff  //Timer3 1:8 prescale value
#endif

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T3_SOURCE_EXT       0xffff/* External clock source */
#define T3_SOURCE_INT       0xfffd /* Internal clock source */
#endif

#if defined (tmr_v2_1) || defined (tmr_v2_2)
#define T3_SOURCE_LPRC		0xff  // Clock source is LPRC
#define T3_SOURCE_EXT_CLK 		0xbf  // Clock source is External Clock source selected by T3CON
#define T3_SOURCE_FOSC_2 	0x7f  //Clock source is instruction clock (FOSC/2)
#define T3_SOURCE_FOSC   	0x3f  //Closck source is system clock (FOSC)

#define T3_OSCEN_OFF    	0xf7  // T3CKI digital input pin used as clock source
#define T3_OSCEN_ON     	0xff  // Timer1  oscilator / Secondary oscillator enabled which is used by Timer3

#define T3_SYNC_EXT_ON      0xfa // Synchronize external clock input
#define T3_SYNC_EXT_OFF     0xff  // Do not synchronize external clock input

#endif

/* defines for Timer Interrupts */ 
#define T3_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T3_INT_PRIOR_6      0xfffe/* 110 = Interrupt is priority 6 */
#define T3_INT_PRIOR_5      0xfffd/* 101 = Interrupt is priority 5 */
#define T3_INT_PRIOR_4      0xfffc/* 100 = Interrupt is priority 4 */
#define T3_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T3_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T3_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T3_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */
  
#define T3_INT_ON           0xffff /* Interrupt Enable */
#define T3_INT_OFF          0xfff7 /* Interrupt Disable */

#else /* Format for backward compatibility (AND based bit setting). */

 /* T3CON: TIMER3 CONTROL REGISTER */   
#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T3_ON               0x8000 /* Timer3 ON */
#define T3_OFF              0x0000 /* Timer3 OFF */
#elif defined (tmr_v2_1) || defined (tmr_v2_2)
#define T3_ON         		0x01  //Timer3 ON 
#define T3_OFF         		0x00  //Timer3 OFF 
#endif
#define T3_OFF_ON_MASK      (~T3_ON)

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T3_IDLE_STOP        0x2000 /* operate during sleep */
#define T3_IDLE_CON         0x0000 /* stop operation during sleep */
#define T3_IDLE_MASK        (~T3_IDLE_STOP)

#define T3_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T3_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T3_GATE_MASK        (~T3_GATE_ON)
#endif

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T3_PS_1_1           0x0000 /* Prescaler 1:1 */      
#define T3_PS_1_8           0x0010 /*Prescaler 1:8 */     
#define T3_PS_1_64          0x0020 /*Prescaler 1:64 */      
#define T3_PS_1_256         0x0030 /*Prescaler 1:256 */     
#define T3_PS_MASK          (~T3_PS_1_256)
#elif defined (tmr_v2_1) || defined (tmr_v2_2)
#define T3_PS_1_1        	0x00  //Timer3 1:1 prescale value
#define T3_PS_1_2        	0x10  //Timer3 1:2 prescale value
#define T3_PS_1_4        	0x20  //Timer3 1:4 prescale value
#define T3_PS_1_8        	0x30  //Timer3 1:8 prescale value
#define T3_PS_MASK		 	(~T3_PS_1_8)		//Mask Timer3 Input Clock Prescale Select bits
#endif

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define T3_SOURCE_EXT       0x0002 /* External clock source */ 
#define T3_SOURCE_INT       0x0000 /* Internal clock source */
#define T3_SOURCE_MASK      (~T3_SOURCE_EXT)
#endif

#if defined (tmr_v2_1) || defined (tmr_v2_2)
#define T3_SOURCE_LPRC		0xc0  // Clock source is LPRC
#define T3_SOURCE_EXT_CLK 		0x80  // Clock source is External Clock source selected by T3CON
#define T3_SOURCE_FOSC_2 	0x40  //Clock source is instruction clock (FOSC/2)
#define T3_SOURCE_FOSC   	0x00  //Closck source is system clock (FOSC)
#define	T3_SOURCE_MASK	 	(~T3_SOURCE_FOSC)	//Mask Timer3 Clock Source Select bits

#define T3_OSCEN_OFF    	0x00  // T3CKI digital input pin used as clock source
#define T3_OSCEN_ON     	0x08  // Timer1  oscilator / Secondary oscillator enabled which is used by Timer3
#define	T3_OSC_MASK		 	(~T3_OSC1EN_ON)		//Mask Timer3 Oscillator Source Select bit

#define T3_SYNC_EXT_ON      0x00 // Synchronize external clock input
#define T3_SYNC_EXT_OFF     0x04  // Do not synchronize external clock input
#define T3_SYNC_MASK	    (~T3_SYNC_EXT_OFF)	// Mask Timer3 External Clock Input Synchronization Select bit

#endif

/* defines for Timer Interrupts */ 
#define T3_INT_PRIOR_0      0x0000 /* 000 = Interrupt is priority 0 */    
#define T3_INT_PRIOR_1      0x0001 /* 001 = Interrupt is priority 1 */      
#define T3_INT_PRIOR_2      0x0002 /* 010 = Interrupt is priority 2 */     
#define T3_INT_PRIOR_3      0x0003/* 011 = Interrupt is priority 3 */      
#define T3_INT_PRIOR_4      0x0004 /* 100 = Interrupt is priority 4 */     
#define T3_INT_PRIOR_5      0x0005 /* 101 = Interrupt is priority 5 */     
#define T3_INT_PRIOR_6      0x0006 /* 110 = Interrupt is priority 6 */     
#define T3_INT_PRIOR_7      0x0007 /* 111 = Interrupt is priority 7 */
#define T3_INT_PRIOR_MASK      (~T3_INT_PRIOR_7)      
 
#define T3_INT_ON           0x0008/* Interrupt Enable */      
#define T3_INT_OFF          0x0000/* Interrupt Disable */
#define T3_INT_MASK         (~T2_INT_ON)

#endif /* USE_AND_OR */

/**********************************************************************
Macro       : EnableIntT3

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT3                    (IEC0bits.T3IE = 1)

/**********************************************************************
Macro       : DisableIntT3

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT3                   (IEC0bits.T3IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT3(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT3(priority)     (IPC2bits.T3IP = priority)

/*******************************************************************
Macro       : T3_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T3_Clear_Intr_Status_Bit     (IFS0bits.T3IF = 0)


/* Timer3 Function Prototypes */

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3)|| defined (tmr_v1_4)|| defined (LIB_BUILD)
#ifndef LIB_BUILD
#define OpenTimer3  OpenTimer3_v1
#define CloseTimer3  CloseTimer3_v1
#define ConfigIntTimer3  ConfigIntTimer3_v1
#endif
void  __attribute__ ((section(".libperi"))) OpenTimer3_v1(unsigned int config , unsigned int period);

void __attribute__ ((section (".libperi"))) CloseTimer3_v1(void) ;

void __attribute__ ((section (".libperi")))  ConfigIntTimer3_v1(unsigned int config) ;
#endif

#if defined (tmr_v2_1) || defined (tmr_v2_2)|| defined (LIB_BUILD)
#ifndef LIB_BUILD
#define OpenTimer3  OpenTimer3_v2
#define CloseTimer3  CloseTimer3_v2
#define ConfigIntTimer3  ConfigIntTimer3_v2
#endif
void  __attribute__ ((section(".libperi"))) OpenTimer3_v2(unsigned int config);

void __attribute__ ((section (".libperi"))) CloseTimer3_v2(void) ;

void __attribute__ ((section (".libperi")))  ConfigIntTimer3_v2(unsigned int config) ;
#endif

unsigned int __attribute__ ((section (".libperi"))) ReadTimer3(void) ;

void  __attribute__ ((section (".libperi")))WriteTimer3( unsigned int timer) ;



/*Registers Defaults*/
#if defined (tmr_v2_1) || defined (tmr_v2_2) || defined (LIB_BUILD)

#define T3GCON_VALUE         0x0000

#ifndef USE_AND_OR /* Format for AND_OR based bit setting */

#define T3_GATE_ON 	        0xff  //Timer3 counting is controlled by Timer3 gate function
#define T3_GATE_OFF 	    0x7f  //Timer3 counts regardless of Timer3 gate function

#define T3_GATE_POL_HI     	0xff  //Gate  is active-high
#define T3_GATE_POL_LO   	0xbf //Gate is active-low

#define T3_GATE_TOGGLE_ON 	0xff  //Gate Toggle mode is enabled
#define T3_GATE_TOGGLE_OFF 	0xdf  //Gate Toggle mode is disabled

#define T3_GATE_1SHOT_ON     0xff //Gate one shot is enabled
#define T3_GATE_1SHOT_OFF    0xf7  //Gate one shot is disabled

#define T3_GATE_SRC_T3GPIN   0xfc  //Timer3 gate pin
#define T3_GATE_SRC_T2       0xfd  //Timer2 match PR2 output
#define T3_GATE_SRC_CMP1     0xfe  //Comparator 1 input
#define T3_GATE_SRC_CMP2     0xff  //Comparator 2 input

/* defines for Timer Interrupts */ 
#define T3_GATE_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T3_GATE_INT_PRIOR_6      0xfffe/* 110 = Interrupt is priority 6 */
#define T3_GATE_INT_PRIOR_5      0xfffd/* 101 = Interrupt is priority 5 */
#define T3_GATE_INT_PRIOR_4      0xfffc/* 100 = Interrupt is priority 4 */
#define T3_GATE_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T3_GATE_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T3_GATE_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T3_GATE_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */
  
#define T3_GATE_INT_ON           0xffff /* Interrupt Enable */
#define T3_GATE_INT_OFF          0xfff7 /* Interrupt Disable */

#else

#define T3_GATE_ON 	        	0x80  //Timer3 counting is controlled by Timer3 gate function
#define T3_GATE_OFF 	        0x00 //Timer3 is always counting 
#define T3_GATE_MASK         	(~TIMER_GATE_ON)	//Mask Timer3 Gate Enable bit

#define T3_GATE_POL_HI     		0x40  //Gate  is active-high
#define T3_GATE_POL_LO   		0x00  //Gate is active-low
#define	T3_GATE_POL_MASK	    (~TIMER_GATE_POL_HI)	//Mask Timer3 Gate Polarity bit

#define T3_GATE_TOGGLE_ON 		0x20  //Gate Toggle mode is enabled
#define T3_GATE_TOGGLE_OFF 		0x00  //Gate Toggle mode is disabled
#define T3_GATE_TOGGLE_MASK  	(~TIMER_GATE_TOGGLE_ON)	//Mask Timer3 Gate Toggle Mode bit

#define T3_GATE_1SHOT_ON     	0x10  //Gate one shot is enabled
#define T3_GATE_1SHOT_OFF    	0x00  //Gate one shot is disabled
#define T3_GATE_1SHOT_MASK   	(~TIMER_GATE_1SHOT_MASK)	//Mask Timer3 Gate Single Pulse Mode bit

#define T3_GATE_SRC_T3GPIN   	0x00  //Timer3 gate pin
#define T3_GATE_SRC_T2       	0x01  //Timer2 match PR2 output
#define T3_GATE_SRC_CMP1     	0x02  //Comparator 1 input
#define T3_GATE_SRC_CMP2     	0x03  //Comparator 2 input
#define TIMER_GATE_SRC_MASK     (~TIMER_GATE_SRC_T2) 	//Mask Timer3 Gate Source Select bits

/* defines for Timer Interrupts */ 
#define T3_GATE_INT_PRIOR_0      0x0000 /* 000 = Interrupt is priority 0 */    
#define T3_GATE_INT_PRIOR_1      0x0001 /* 001 = Interrupt is priority 1 */      
#define T3_GATE_INT_PRIOR_2      0x0002 /* 010 = Interrupt is priority 2 */     
#define T3_GATE_INT_PRIOR_3      0x0003/* 011 = Interrupt is priority 3 */      
#define T3_GATE_INT_PRIOR_4      0x0004 /* 100 = Interrupt is priority 4 */     
#define T3_GATE_INT_PRIOR_5      0x0005 /* 101 = Interrupt is priority 5 */     
#define T3_GATE_INT_PRIOR_6      0x0006 /* 110 = Interrupt is priority 6 */     
#define T3_GATE_INT_PRIOR_7      0x0007 /* 111 = Interrupt is priority 7 */
#define T3_GATE_INT_PRIOR_MASK      (~T3_INT_PRIOR_7)      
 
#define T3_INT_ON           0x0008/* Interrupt Enable */      
#define T3_INT_OFF          0x0000/* Interrupt Disable */
#define T3_INT_MASK         (~T2_INT_ON)

#endif
/**********************************************************************
Macro       : EnableIntT3G

Include     : uart.h
 
Description : This macro enables the gated timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Gated Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT3G                    (IEC2bits.T3GIE = 1)

/**********************************************************************
Macro       : DisableIntT3G

Include     : uart.h
 
Description : This macro disables the gated timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Gated Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT3G                   (IEC2bits.T3GIE = 0)

/**********************************************************************
Macro       : SetPriorityIntT3G(priority)

Include     : uart.h
 
Description : This macro sets priority for gated timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Gated Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT3G(priority)     (IPC9bits.T3GIP = priority)

/*******************************************************************
Macro       : T3G_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T3G_Clear_Intr_Status_Bit     (IFS2bits.T3GIF = 0)

/* Timer3 Function Prototypes */

void __attribute__ ((section(".libperi")))OpenTimer3G(unsigned int config);

#ifndef USE_OR_MASKS
#define T2_SOURCE_CCP           0xff			// T2 is source for CCP
#define T3_SOURCE_CCP         	0xbf				// T3 is source for CCP
#define T4_SOURCE_CCP           0xb7			// T4 is source for CCP
#else //!USE_OR_MASKS
#define T2_SOURCE_CCP        	0x48			// T2 is source for CCP
#define T3_SOURCE_CCP       	0x08			// T3is source for CCP
#define T4_SOURCE_CCP        	0x00			// T4 is source for CCP
#define TMR_SOURCE_CCP_MASK		(~T3_SOURCE_CCP)	
#endif //USE_OR_MASKS

void  __attribute__ ((section (".libperi")))SetTmrCCPSrc(unsigned char config);

#endif

#if defined (tmr_v1_1) || defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)
#define _T23Interrupt _T3Interrupt

#ifndef USE_AND_OR /* Format for AND_OR based bit setting */

/* Timer3 Control Register (T3CON) Bit Defines */
#define T23_ON               0xffff /* Timer23 ON */
#define T23_OFF              0x7fff /* Timer23 OFF */

#define T23_IDLE_CON         0xdfff  /* operate during sleep */
#define T23_IDLE_STOP        0xffff  /* stop operation during sleep */

#define T23_GATE_ON          0xffff/* Timer3 Gate  time accumulation enabled  */
#define T23_GATE_OFF         0xffbf /* Timer Gate time accumulation disabled */

#define T23_PS_1_1           0xffcf /* Prescaler 1:1   */
#define T23_PS_1_8           0xffdf /*  Prescaler 1:8   */
#define T23_PS_1_64          0xffef /* Prescaler 1:64  */
#define T23_PS_1_256         0xffff /* Prescaler 1:256 */

#define T23_SOURCE_EXT       0xffff/* External clock source */
#define T23_SOURCE_INT       0xfffd /* Internal clock source */

/* defines for Timer Interrupts */
#define T23_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T23_INT_PRIOR_6      0xfffe/* 110 = Interrupt is priority 6 */
#define T23_INT_PRIOR_5      0xfffd/* 101 = Interrupt is priority 5 */
#define T23_INT_PRIOR_4      0xfffc/* 100 = Interrupt is priority 4 */
#define T23_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T23_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T23_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T23_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */
  
#define T23_INT_ON           0xffff /* Interrupt Enable */
#define T23_INT_OFF          0xfff7 /* Interrupt Disable */

#else /* Format for backward compatibility (AND based bit setting). */

 /* T3CON: TIMER3 CONTROL REGISTER */   
#define T23_ON               0x8000 /* Timer23 ON */
#define T23_OFF              0x0000 /* Timer23 OFF */
#define T23_OFF_ON_MASK      (~T23_ON)

#define T23_IDLE_STOP        0x2000 /* operate during sleep */
#define T23_IDLE_CON         0x0000 /* stop operation during sleep */
#define T23_IDLE_MASK        (~T23_IDLE_STOP)

#define T23_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T23_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T23_GATE_MASK        (~T23_GATE_ON)

#define T23_PS_1_1           0x0000 /* Prescaler 1:1 */
#define T23_PS_1_8           0x0010 /* Prescaler 1:8 */
#define T23_PS_1_64          0x0020 /*Prescaler 1:64 */
#define T23_PS_1_256         0x0030 /*Prescaler 1:256 */
#define T23_PS_MASK          (~T23_PS_1_256)

#define T23_SOURCE_EXT       0x0002 /* External clock source */
#define T23_SOURCE_INT       0x0000 /* Internal clock source */
#define T23_SOURCE_MASK      (~T3_SOURCE_EXT)

/* defines for Timer Interrupts */ 
#define T23_INT_PRIOR_0      0x0000 /* 000 = Interrupt is priority 0 */
#define T23_INT_PRIOR_1      0x0001 /* 001 = Interrupt is priority 1 */
#define T23_INT_PRIOR_2      0x0002 /* 010 = Interrupt is priority 2 */
#define T23_INT_PRIOR_3      0x0003 /* 011 = Interrupt is priority 3 */
#define T23_INT_PRIOR_4      0x0004 /* 100 = Interrupt is priority 4 */
#define T23_INT_PRIOR_5      0x0005 /* 101 = Interrupt is priority 5 */
#define T23_INT_PRIOR_6      0x0006 /* 110 = Interrupt is priority 6 */
#define T23_INT_PRIOR_7      0x0007 /* 111 = Interrupt is priority 7 */
#define T23_INT_PRIOR_MASK      (~T3_INT_PRIOR_7)      
 
#define T23_INT_ON           0x0008/* Interrupt Enable */
#define T23_INT_OFF          0x0000/* Interrupt Disable */
#define T23_INT_MASK         (~T2_INT_ON)

#endif /* USE_AND_OR */

/**********************************************************************
Macro       : EnableIntT23

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT23                    (IEC0bits.T3IE = 1)

/**********************************************************************
Macro       : DisableIntT23

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT23                   (IEC0bits.T3IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT23(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT23(priority)     (IPC2bits.T3IP = priority)

/*******************************************************************
Macro       : T23_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T23_Clear_Intr_Status_Bit     (IFS0bits.T3IF = 0)


/* Timer 23 mode using Timer 2 and Timer3*/

/*Timer 23 bit mode Prototypes*/

void  __attribute__ ((section(".libperi"))) OpenTimer23(unsigned int config, unsigned long int period);

void  __attribute__ ((section (".libperi"))) CloseTimer23(void);

unsigned long __attribute__ ((section (".libperi"))) ReadTimer23(void) ;

void __attribute__ ((section (".libperi"))) WriteTimer23(unsigned long int timer);

void __attribute__ ((section (".libperi"))) ConfigIntTimer23(unsigned int config);

#endif

#if defined (tmr_v1_2) || defined (tmr_v1_3) || defined (tmr_v1_4)||defined (tmr_v2_2) 
/*Registers Defaults*/
#define TMR4_VALUE          0x0000
#define PR4_VALUE           0xFFFF
#define T4CON_VALUE         0x0000

#ifndef USE_AND_OR /* Format for AND_OR based bit setting */

/* Timer4 Control Register (T4CON) Bit Defines */
#ifndef tmr_v2_2
#define T4_ON               0xffff /* Timer4 ON */
#define T4_OFF              0x7fff /* Timer4 OFF */

#define T4_IDLE_CON         0xdfff /* operate during sleep */
#define T4_IDLE_STOP        0xffff /* stop operation during sleep */

#define T4_GATE_ON          0xffff  /* Timer Gate time accumulation enabled */
#define T4_GATE_OFF         0xffbf/* Timer Gate time accumulation disabled */
      
#define T4_PS_1_1           0xffcf /* Prescaler 1:1   */
#define T4_PS_1_8           0xffdf/*Prescaler 1:8   */
#define T4_PS_1_64          0xffef/*Prescaler 1:64  */
#define T4_PS_1_256         0xffff /*Prescaler 1:256 */

#define T4_SOURCE_EXT       0xffff /* External clock source */
#define T4_SOURCE_INT       0xfffd  /* Internal clock source */
#endif
    
#if defined (tmr_v2_2)
#define T4_POST_1_1    0x87  //Timer2 Postscaler 1:1
#define T4_POST_1_2    0x8f  //Timer2 Postscaler 1:2
#define T4_POST_1_3    0x97  //Timer2 Postscaler 1:3
#define T4_POST_1_4    0x9f  //Timer2 Postscaler 1:4
#define T4_POST_1_5    0xa7  //Timer2 Postscaler 1:5
#define T4_POST_1_6    0xaf  //Timer2 Postscaler 1:6
#define T4_POST_1_7    0xb7  //Timer2 Postscaler 1:7
#define T4_POST_1_8    0xbf  //Timer2 Postscaler 1:8
#define T4_POST_1_9    0xc7  //Timer2 Postscaler 1:9
#define T4_POST_1_10   0xcf  //Timer2 Postscaler 1:10
#define T4_POST_1_11   0xd7  //Timer2 Postscaler 1:11
#define T4_POST_1_12   0xdf  //Timer2 Postscaler 1:12
#define T4_POST_1_13   0xe7  //Timer2 Postscaler 1:13
#define T4_POST_1_14   0xef //Timer2 Postscaler 1:14
#define T4_POST_1_15   0xf7  //Timer2 Postscaler 1:15
#define T4_POST_1_16   0xff  //Timer2 Postscaler 1:16
#define T4_PS_1_1      0xfC  //Timer2 Prescale 1:1
#define T4_PS_1_4      0xfD  //Timer2 Prescale 1:4
#define T4_PS_1_16     0xfe  //Timer2 Prescale 1:16

#define T4_ON               0xff /* Timer2 ON */
#define T4_OFF              0xbf /* Timer2 OFF */
#endif

/* Timer 4 and Timer 5 form a 32 bit Timer */
#ifndef tmr_v2_2
#define T4_32BIT_MODE_ON    0xffff /*Timer 4 and 5 - 32 bit mode enabled*/ 
#define T4_32BIT_MODE_OFF   0xfff7 /*Timer 4 and 5 - 32 bit mode disabled*/ 

/* defines for Timer Interrupts */ 
#define T4_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T4_INT_PRIOR_6      0xfffe /* 110 = Interrupt is priority 6 */
#define T4_INT_PRIOR_5      0xfffd /* 101 = Interrupt is priority 5 */
#define T4_INT_PRIOR_4      0xfffc /* 100 = Interrupt is priority 4 */
#define T4_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T4_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T4_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T4_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */
  
#define T4_INT_ON           0xffff/* Interrupt Enable */
#define T4_INT_OFF          0xfff7 /* Interrupt Disable */
#endif

#else /* Format for backward compatibility (AND based bit setting). */

/* T4CON: TIMER4 CONTROL REGISTER */  
#ifndef tmr_v2_2
#define T4_ON               0x8000/* Timer4 ON */    
#define T4_OFF              0x0000 /* Timer4 OFF */
#define T4_OFF_ON_MASK      (~T4_ON)

#define T4_IDLE_STOP        0x2000/* operate during sleep */
#define T4_IDLE_CON         0x0000 /* stop operation during sleep */
#define T4_IDLE_MASK        (~T4_IDLE_STOP)

#define T4_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T4_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T4_GATE_MASK        (~T4_GATE_ON)

#define T4_PS_1_1           0x0000/* Prescaler 1:1 */
#define T4_PS_1_8           0x0010/*Prescaler 1:8 */
#define T4_PS_1_64          0x0020 /*Prescaler 1:64 */
#define T4_PS_1_256         0x0030 /*Prescaler 1:256 */
#define T4_PS_MASK          (~T4_PS_1_256)
#endif

#if defined (tmr_v2_2)
#define T4_POST_1_1    0x00  //Timer2 Postscaler 1:1
#define T4_POST_1_2    0x08  //Timer2 Postscaler 1:2
#define T4_POST_1_3    0x10  //Timer2 Postscaler 1:3
#define T4_POST_1_4    0x18  //Timer2 Postscaler 1:4
#define T4_POST_1_5    0x20  //Timer2 Postscaler 1:5
#define T4_POST_1_6    0x28  //Timer2 Postscaler 1:6
#define T4_POST_1_7    0x30  //Timer2 Postscaler 1:7
#define T4_POST_1_8    0x38  //Timer2 Postscaler 1:8
#define T4_POST_1_9    0x40  //Timer2 Postscaler 1:9
#define T4_POST_1_10   0x48  //Timer2 Postscaler 1:10
#define T4_POST_1_11   0x50  //Timer2 Postscaler 1:11
#define T4_POST_1_12   0x58  //Timer2 Postscaler 1:12
#define T4_POST_1_13   0x60  //Timer2 Postscaler 1:13
#define T4_POST_1_14   0x68 //Timer2 Postscaler 1:14
#define T4_POST_1_15   0x70 //Timer2 Postscaler 1:15
#define T4_POST_1_16   0x78  //Timer2 Postscaler 1:16
#define	T4_POST_MASK	(~T2_POST_1_16)	//Mask Timer2 Postscale Selection bits

#define T4_PS_1_1      0x00  //Timer2 Prescale 1:1
#define T4_PS_1_4      0x01  //Timer2 Prescale 1:4
#define T4_PS_1_16     0x03  //Timer2 Prescale 1:16
#define T4_PS_MASK 		(~T2_PS_1_16)	//Mask Timer2 Input Clock Prescale Select bits

#define T4_ON               0x04 /* Timer2 ON */
#define T4_OFF              0x00 /* Timer2 OFF */
#endif

/* Timer 2 and Timer 3 form a 32 bit Timer */
#ifndef tmr_v2_2
#define T4_32BIT_MODE_ON    0x0008 /* Timer4 32bit mode enabled*/      
#define T4_32BIT_MODE_OFF   0x0000 /* Timer4 32bit mode disabled*/
#define T4_32BIT_MODE_MASK   (~T4_32BIT_MODE_ON)

#define T4_SOURCE_EXT       0x0002 /* External clock source */
#define T4_SOURCE_INT       0x0000 /* Internal clock source */
#define T4_SOURCE_MASK      (~T4_SOURCE_EXT)

/* defines for Timer Interrupts */
#define T4_INT_PRIOR_0      0x0000  /* 000 = Interrupt is priority 0 */
#define T4_INT_PRIOR_1      0x0001/* 001 = Interrupt is priority 1 */
#define T4_INT_PRIOR_2      0x0002 /* 010 = Interrupt is priority 2 */
#define T4_INT_PRIOR_3      0x0003 /* 011 = Interrupt is priority 3 */
#define T4_INT_PRIOR_4      0x0004 /* 100 = Interrupt is priority 4 */
#define T4_INT_PRIOR_5      0x0005 /* 101 = Interrupt is priority 5 */
#define T4_INT_PRIOR_6      0x0006 /* 110 = Interrupt is priority 6 */
#define T4_INT_PRIOR_7      0x0007 /* 111 = Interrupt is priority 7 */
#define T4_INT_PRIOR_MASK   (~T4_INT_PRIOR_7)     

#define T4_INT_ON           0x0008/* Interrupt Enable */
#define T4_INT_OFF          0x0000/* Interrupt Disable */
#define T4_INT_MASK         (~T4_INT_ON)   
#endif

#endif 

/**********************************************************************
Macro       : EnableIntT4

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT4                    (IEC1bits.T4IE = 1)

/**********************************************************************
Macro       : DisableIntT4

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT4                   (IEC1bits.T4IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT4(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT4(priority)     (IPC6bits.T4IP = priority)

/*******************************************************************
Macro       : T4_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T4_Clear_Intr_Status_Bit     (IFS1bits.T4IF = 0)


/* Timer4 Function Declarations */
void __attribute__ ((section(".libperi"))) OpenTimer4(unsigned int config , unsigned int period);

void __attribute__ ((section (".libperi"))) CloseTimer4(void);

unsigned int __attribute__ ((section (".libperi"))) ReadTimer4(void);

void __attribute__ ((section (".libperi"))) WriteTimer4(unsigned int timer );

void __attribute__ ((section (".libperi"))) ConfigIntTimer4(unsigned int config);

/*Registers Defaults*/
#ifndef tmr_v2_2
#define TMR5_VALUE          0x0000
#define PR5_VALUE           0xFFFF
#define T5CON_VALUE         0x0000

#ifndef USE_AND_OR /* Format for AND_OR based bit setting */

#define T5_ON               0xffff /* Timer5 ON */
#define T5_OFF              0x7fff /* Timer5 OFF */

#define T5_IDLE_CON         0xdfff /* operate during sleep */
#define T5_IDLE_STOP        0xffff /* stop operation during sleep */

#define T5_GATE_ON          0xffff /* Timer Gate time accumulation enabled */
#define T5_GATE_OFF         0xffbf /* Timer Gate time accumulation disabled */

#define T5_PS_1_1           0xffcf /* Prescaler 1:1   */
#define T5_PS_1_8           0xffdf /* Prescaler 1:8   */
#define T5_PS_1_64          0xffef /* Prescaler 1:64  */
#define T5_PS_1_256         0xffff /* Prescaler 1:256 */

#define T5_SOURCE_EXT       0xffff/* External clock source */
#define T5_SOURCE_INT       0xfffd /* Internal clock source */

/* defines for Timer Interrupts */
#define T5_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T5_INT_PRIOR_6      0xfffe /* 110 = Interrupt is priority 6 */
#define T5_INT_PRIOR_5      0xfffd /* 101 = Interrupt is priority 5 */
#define T5_INT_PRIOR_4      0xfffc /* 100 = Interrupt is priority 4 */
#define T5_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T5_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T5_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T5_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */

#define T5_INT_ON           0xffff /* Interrupt Enable */
#define T5_INT_OFF          0xfff7  /* Interrupt Disable */

#else /* Format for backward compatibility (AND based bit setting). */

/* T5CON: TIMER5 CONTROL REGISTER */   
#define T5_ON               0x8000 /* Timer5 ON */
#define T5_OFF              0x0000 /* Timer5 OFF */
#define T5_OFF_ON_MASK      (~T5_ON)

#define T5_IDLE_STOP        0x2000 /* operate during sleep */
#define T5_IDLE_CON         0x0000 /* stop operation during sleep */
#define T5_IDLE_MASK        (~T5_IDLE_STOP)

#define T5_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T5_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T5_GATE_MASK        (~T5_GATE_ON)

#define T5_PS_1_1           0x0000 /* Prescaler 1:1 */
#define T5_PS_1_8           0x0010/* Prescaler 1:8 */
#define T5_PS_1_64          0x0020/* Prescaler 1:64 */
#define T5_PS_1_256         0x0030 /* Prescaler 1:256 */
#define T5_PS_MASK          (~T5_PS_1_256)

#define T5_SOURCE_EXT       0x0002 /* External clock source */
#define T5_SOURCE_INT       0x0000 /* Internal clock source */
#define T5_SOURCE_MASK      (~T5_SOURCE_EXT)

/* defines for Timer Interrupts */
#define T5_INT_PRIOR_0      0x0000 /* 000 = Interrupt is priority 0 */
#define T5_INT_PRIOR_1      0x0001 /* 001 = Interrupt is priority 1 */
#define T5_INT_PRIOR_2      0x0002 /* 010 = Interrupt is priority 2 */
#define T5_INT_PRIOR_3      0x0003 /* 011 = Interrupt is priority 3 */
#define T5_INT_PRIOR_4      0x0004 /* 100 = Interrupt is priority 4 */
#define T5_INT_PRIOR_5      0x0005 /* 101 = Interrupt is priority 5 */
#define T5_INT_PRIOR_6      0x0006 /* 110 = Interrupt is priority 6 */
#define T5_INT_PRIOR_7      0x0007 /* 111 = Interrupt is priority 7 */
#define T5_INT_PRIOR_MASK   (~T5_INT_PRIOR_7)       

#define T5_INT_ON           0x0008 /* Interrupt Enable */
#define T5_INT_OFF          0x0000 /* Interrupt Disable */
#define T5_INT_MASK         (~T5_INT_ON)

#endif

/**********************************************************************
Macro       : EnableIntT5

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT5                    (IEC1bits.T5IE = 1)

/**********************************************************************
Macro       : DisableIntT5

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT5                  (IEC1bits.T5IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT5(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT5(priority)     (IPC7bits.T5IP = priority)

/*******************************************************************
Macro       : T5_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T5_Clear_Intr_Status_Bit     (IFS1bits.T5IF = 0)

/* Timer5 Function Declarations */

void  __attribute__ ((section(".libperi"))) OpenTimer5(unsigned int config, unsigned int period);

void  __attribute__ ((section (".libperi"))) CloseTimer5(void);

unsigned int  __attribute__ ((section (".libperi"))) ReadTimer5(void);

void  __attribute__ ((section (".libperi"))) WriteTimer5(unsigned int timer);

void  __attribute__ ((section (".libperi"))) ConfigIntTimer5(unsigned int config);

#define _T45Interrupt _T5Interrupt

#ifndef USE_AND_OR /* Format for AND_OR based bit setting */

#define T45_ON               0xffff /* Timer45 ON */
#define T45_OFF              0x7fff /* Timer45 OFF */

#define T45_IDLE_CON         0xdfff /* operate during sleep */
#define T45_IDLE_STOP        0xffff /* stop operation during sleep */

#define T45_GATE_ON          0xffff /* Timer Gate time accumulation enabled */
#define T45_GATE_OFF         0xffbf /* Timer Gate time accumulation disabled */

#define T45_PS_1_1           0xffcf /* Prescaler 1:1   */
#define T45_PS_1_8           0xffdf /* Prescaler 1:8   */
#define T45_PS_1_64          0xffef /*  Prescaler 1:64  */
#define T45_PS_1_256         0xffff /* Prescaler  1:256 */

#define T45_SOURCE_EXT       0xffff/* External clock source */
#define T45_SOURCE_INT       0xfffd /* Internal clock source */

/* defines for Timer Interrupts */
#define T45_INT_PRIOR_7      0xffff /* 111 = Interrupt is priority 7 */
#define T45_INT_PRIOR_6      0xfffe /* 110 = Interrupt is priority 6 */
#define T45_INT_PRIOR_5      0xfffd /* 101 = Interrupt is priority 5 */
#define T45_INT_PRIOR_4      0xfffc /* 100 = Interrupt is priority 4 */
#define T45_INT_PRIOR_3      0xfffb /* 011 = Interrupt is priority 3 */
#define T45_INT_PRIOR_2      0xfffa /* 010 = Interrupt is priority 2 */
#define T45_INT_PRIOR_1      0xfff9 /* 001 = Interrupt is priority 1 */
#define T45_INT_PRIOR_0      0xfff8 /* 000 = Interrupt is priority 0 */

#define T45_INT_ON           0xffff /* Interrupt Enable */
#define T45_INT_OFF          0xfff7  /* Interrupt Disable */

#else /* Format for backward compatibility (AND based bit setting). */

/* T5CON: TIMER5 CONTROL REGISTER */   
#define T45_ON               0x8000 /* Timer45 ON */
#define T45_OFF              0x0000 /* Timer45 OFF */
#define T45_OFF_ON_MASK      (~T5_ON)

#define T45_IDLE_STOP        0x2000 /* operate during sleep */
#define T45_IDLE_CON         0x0000 /* stop operation during sleep */
#define T45_IDLE_MASK        (~T5_IDLE_STOP)

#define T45_GATE_ON          0x0040 /* Timer Gate time accumulation enabled */
#define T45_GATE_OFF         0x0000 /* Timer Gate time accumulation disabled */
#define T45_GATE_MASK        (~T5_GATE_ON)

#define T45_PS_1_1           0x0000 /* Prescaler 1:1 */
#define T45_PS_1_8           0x0010/* Prescaler 1:8 */
#define T45_PS_1_64          0x0020/* Prescaler 1:64 */
#define T45_PS_1_256         0x0030 /* Prescaler 1:256 */
#define T45_PS_MASK          (~T5_PS_1_256)

#define T45_SOURCE_EXT       0x0002 /* External clock source */
#define T45_SOURCE_INT       0x0000 /* Internal clock source */
#define T45_SOURCE_MASK      (~T5_SOURCE_EXT)

/* defines for Timer Interrupts */
#define T45_INT_PRIOR_0      0x0000 /* 000 = Interrupt is priority 0 */
#define T45_INT_PRIOR_1      0x0001 /* 001 = Interrupt is priority 1 */
#define T45_INT_PRIOR_2      0x0002 /* 010 = Interrupt is priority 2 */
#define T45_INT_PRIOR_3      0x0003 /* 011 = Interrupt is priority 3 */
#define T45_INT_PRIOR_4      0x0004 /* 100 = Interrupt is priority 4 */
#define T45_INT_PRIOR_5      0x0005 /* 101 = Interrupt is priority 5 */
#define T45_INT_PRIOR_6      0x0006 /* 110 = Interrupt is priority 6 */
#define T45_INT_PRIOR_7      0x0007 /* 111 = Interrupt is priority 7 */
#define T45_INT_PRIOR_MASK   (~T5_INT_PRIOR_7)       

#define T45_INT_ON           0x0008 /* Interrupt Enable */
#define T45_INT_OFF          0x0000 /* Interrupt Disable */
#define T45_INT_MASK         (~T5_INT_ON)

#endif

/**********************************************************************
Macro       : EnableIntT45

Include     : uart.h
 
Description : This macro enables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro sets Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/  
#define EnableIntT45                   (IEC1bits.T5IE = 1)

/**********************************************************************
Macro       : DisableIntT45

Include     : uart.h
 
Description : This macro disables the timer interrupt.
 
Arguments   : None
 
Remarks     : This macro clears Timer Interrupt Enable bit of Interrupt 
              Enable Control register.
**********************************************************************/ 
#define DisableIntT45                   (IEC1bits.T5IE = 0)

/**********************************************************************
Macro       : SetPriorityIntT45(priority)

Include     : uart.h
 
Description : This macro sets priority for timer interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority
 
Remarks     : This macro sets Timer Interrupt Priority bits of Interrupt 
              Priority Control register.
**********************************************************************/ 
#define SetPriorityIntT45(priority)     (IPC7bits.T5IP = priority)

/*******************************************************************
Macro       : T45_Clear_Intr_Status_Bit

Include     : timer.h 

Description : Macro to Clear external Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
#define T45_Clear_Intr_Status_Bit     (IFS1bits.T5IF = 0)

/* Timer 45 mode using Timer 4 and Timer 5 */

#if defined (tmr_v1_2) || defined (LIB_BUILD)
#ifndef LIB_BUILD
#define OpenTimer45  OpenTimer45_v1
#define CloseTimer45  CloseTimer45_v1
#endif
void  __attribute__ ((section(".libperi"))) OpenTimer45_v1(unsigned int config , unsigned long int period);

void  __attribute__ ((section (".libperi"))) CloseTimer45_v1(void);
#endif

#if defined (tmr_v1_3) || defined (tmr_v1_4) || defined (LIB_BUILD)
#ifndef LIB_BUILD
#define OpenTimer45  OpenTimer45_v2
#define CloseTimer45  CloseTimer45_v2
#endif
void  __attribute__ ((section(".libperi"))) OpenTimer45_v2(unsigned int config , unsigned long int period);

void  __attribute__ ((section (".libperi"))) CloseTimer45_v2(void);
#endif


unsigned long  __attribute__ ((section (".libperi"))) ReadTimer45(void);

void  __attribute__ ((section (".libperi"))) WriteTimer45(unsigned long int timer);

void  __attribute__ ((section (".libperi"))) ConfigIntTimer45(unsigned int config);

#endif
#endif

#else		//This preprocessor conditional statement is to avoid unintended linking for unsuppported devices.
#warning "Does not build on this target"
#endif

#endif /* TIMER_H */
