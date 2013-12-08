/* 
 * File:   hardware.h
 * Author: Jared
 *
 * Created on 5 July 2013, 12:48 PM
 *
 * Hardware Configuration
 */

#ifndef HARDWARE_H
#define	HARDWARE_H

#define OUTPUT 0
#define INPUT 1

#define ANALOG 1
#define DIGITAL 0

#ifdef WIN32 

// MACROS FOR EASY PIN HANDLING IN PIC C18/C30
#define _TRIS(pin)           
#define _PORT(pin)            pin
#define _LAT(pin)            pin

/// OLED ///
#define OL_RESET    hw_ol_reset
#define OL_POWER    hw_ol_power

/// Buttons ///
#define BTN1        hw_btn1
#define BTN2        hw_btn2
#define BTN3        hw_btn3
#define BTN4        hw_btn4

/// Status LEDs ///
#define LED1        hw_led1
#define LED2        hw_led2

/// Misc GPIO ///
#define VMOTOR      hw_vmotor
#define PEIZO       hw_peizo
#define VBUS_SENSE  hw_vbus_sense

/// Sensors ///
#define INTM        hw_intm
#define INTA        hw_inta

/// Power Supply ///
#define PW_STAT1    hw_pw_stat1
#define PW_STAT2    hw_pw_stat2
#define PW_CE      hw_pw_ce

/// Bluetooth ///
#define BT_RESET    hw_bt_reset

/// Analog ///
#define AN_VBAT     hw_an_vbat
//#define AN_TEMP     R(B,1)    // AN1  // Not implemented in Rev2
#define AN_LIGHT    hw_an_light

extern bool hw_ol_power;
extern bool hw_ol_reset;

extern bool hw_btn1;
extern bool hw_btn2;
extern bool hw_btn3;
extern bool hw_btn4;

extern bool hw_led1;
extern bool hw_led2;

extern bool hw_vmotor;
extern bool hw_peizo;

extern bool hw_vbus_sense;

extern bool hw_intm;
extern bool hw_inta;

extern bool hw_pw_stat1;
extern bool hw_pw_stat2;
extern bool hw_pw_ce;

extern bool hw_bt_reset;

//extern uint16 hw_an_vbat;
//extern uint16 hw_an_light;

extern uint16 hw_dummy;

#else

// MACROS FOR EASY PIN HANDLING IN PIC C18/C30
#define _TRIS(pin)            pin(_TRIS_F)
#define _TRIS_F(alpha,bit)    (TRIS ## alpha ## bits.TRIS ## alpha ## bit)
#define _PORT(pin)            pin(_PORT_F)
#define _PORT_F(alpha,bit)    (PORT ## alpha ## bits.R ## alpha ## bit)
#define _LAT(pin)            pin(_LAT_F)
#define _LAT_F(alpha,bit)    (LAT ## alpha ## bits.LAT ## alpha ## bit)
//#define _WPU(pin)            pin(_WPU_F)
//#define _WPU_F(alpha,bit)    (WPU ## alpha ## bits.WPU ## alpha ## bit)
#define _ODC(pin)            pin(_ODC_F)
#define _ODC_F(alpha,bit)    (ODC ## alpha ## bits.ODC ## alpha ## bit)
#define _ANS(pin)            pin(_ANS_F)
#define _ANS_F(alpha,bit)    (ANS ## alpha ## bits.ANS ## alpha ## bit)

#define _TOGGLE(pin)            pin(_TOGGLE_F)
#define _TOGGLE_F(alpha,bit)    __builtin_btg((void*)&LAT ## alpha, bit)

#define _CNIEn(pin)            pin(_CNIEn_F)
#define _CNIEn_F(alpha)    (_CN ## alpha ## IE)
#define _CNPUE(pin)            pin(_CNPUE_F)
#define _CNPUE_F(alpha)    (_CN ## alpha ## PUE)
#define _CNPDE(pin)            pin(_CNPDE_F)
#define _CNPDE_F(alpha)    (_CN ## alpha ## PDE)

////////// GPIO Configuration //////////////////////////////////////////////////

/// USB ///
#define USB_DPLUS(R)    R(G,2)
#define USB_DMINUS(R)   R(G,3)
#define USB_VBUS(R)     R(F,7)
#define USB_DPLUS_CN(CN)    CN(83) // Pull-up required for USB enumeration?

//#define USB_VBUS_SENSE _PORT(USB_VBUS)
#define USB_VBUS_SENSE _SESVD

/// OLED ///
#define OL_E(R)        R(E,0)
#define OL_RW(R)       R(E,1)
#define OL_DC(R)       R(E,2)
#define OL_CS(R)       R(E,3)
#define OL_RESET(R)    R(E,4)
#define OL_POWER(R)     R(F,1)

#define OL_DATA_TRIS  TRISD
#define OL_DATA_LAT   LATD
#define OL_DATA_PORT  PORTD
#define OL_DATA_MASK  0x00FF

/// Buttons ///
#define BTN1(R)        R(B,14)
#define BTN2(R)        R(D,11)
#define BTN3(R)        R(E,5)
#define BTN4(R)        R(G,9)
#define BTN1_CN(CN)    CN(32)  //  Pull-ups
#define BTN2_CN(CN)    CN(56)
#define BTN3_CN(CN)    CN(63)
#define BTN4_CN(CN)    CN(11)

/// Status LEDs ///
#define LED1(R)        R(G,8)
#define LED2(R)        R(E,6)

/// Misc GPIO ///
#define VMOTOR(R)      R(E,7)
#define PEIZO(R)       R(D,10)
//#define VBUS_SENSE(R)  R(F,7)

/// Sensors ///
#define SDA(R)         R(F,4)   // SDA2
#define SCL(R)         R(F,5)   // SCL2
#define INTM(R)        R(B,12)
#define INTA(R)        R(B,13)
#define SDA_CN(CN)     CN(17)  // Pull-ups
#define SCL_CN(CN)     CN(18)
#define INTM_CN(CN)    CN(30)  // Pin-change interrupt
#define INTA_CN(CN)    CN(31)

/// Power Supply ///
#define PW_STAT1(R)    R(G,6)
#define PW_STAT2(R)    R(B,5)
#define PW_CE(R)       R(F,3)

/// Bluetooth ///
#define BT_MISO(R)     R(B,6)  // RP6
#define BT_MOSI(R)     R(B,7)  // RP7
#define BT_REQN(R)     R(B,8)
#define BT_SCK(R)      R(B,9)  // RP9
#define BT_RDYN(R)     R(B,10)
#define BT_RESET(R)    R(B,11)
#define BT_RDYN_CN(CN) CN(28)

/// Analog ///
#define ANR_VBAT(R)     R(B,0)    // AN0
//#define AN_TEMP(R)     R(B,1)    // AN1  // Not implemented in Rev2
#define ANR_LIGHT(R)    R(B,2)    // AN2
#define AN_VBAT         0
#define AN_LIGHT        2

// AN3 (RB3), AN4 (RB4), RD9 are broken out on testpads

#endif

////////// Hardware Configuration //////////////////////////////////////////////

// Primary oscillator is 32MHz
// Secondary oscillator is 32.768kHz (For RTCC module)

#define POSC 32000000ULL

#endif	/* HARDWARE_H */

