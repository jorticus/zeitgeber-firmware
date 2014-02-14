/*
 * File:   cpu.c
 * Author: Jared
 *
 * Created on 5 July 2013, 2:56 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "cpu.h"
#include "hardware.h"

// Sleep mode stops clock operation and halts all code execution
// Idle mode halts the CPU and code execution, but allows peripheral
//   modules to continue operation

// Note that we can reduce power consumption further by disabling the
// voltage regulator (RCONbits.VREGS=0), but this will add some delay
// when the device wakes back up. Would only be suitable for long sleeps
// (~1 second sleeps?)

////////// Methods /////////////////////////////////////////////////////////////

void InitializeIO() {
    // Initialize all the IO pins immediately into a valid state

    /// Analog ///
    ANSB = 0x0000;
    ANSC = 0x0000;
    ANSD = 0x0000;
    ANSF = 0x0000;
    ANSG = 0x0000;
//    _ANS(AN_VBAT) = ANALOG;
//    _ANS(AN_LIGHT) = ANALOG;
    _TRIS(ANR_VBAT) = INPUT;
    _TRIS(ANR_LIGHT) = INPUT;

    /// OLED ///
    _TRIS(OL_E) = OUTPUT;
    _TRIS(OL_RW) = OUTPUT;
    _TRIS(OL_DC) = OUTPUT;
    _TRIS(OL_CS) = OUTPUT;
    _TRIS(OL_RESET) = OUTPUT;
    _TRIS(OL_POWER) = OUTPUT;
    OL_DATA_TRIS &= ~OL_DATA_MASK; // D0..D7 output
    _LAT(OL_POWER) = 0;          // OLED supply off
    _LAT(OL_RESET) = 1;          // Disable OLED

    /// Buttons ///
    _TRIS(BTN1) = INPUT;
    _TRIS(BTN2) = INPUT;
    _TRIS(BTN3) = INPUT;
    _TRIS(BTN4) = INPUT;

    /// Status LEDs ///
    _TRIS(LED1) = OUTPUT;
    _TRIS(LED2) = OUTPUT;
    _LAT(LED1) = 0;
    _LAT(LED2) = 0;

    /// Misc GPIO ///
    _TRIS(VMOTOR) = OUTPUT;
    _TRIS(PEIZO) = OUTPUT;
//    _TRIS(VBUS_SENSE) = INPUT;
    _LAT(VMOTOR) = 0;
    _LAT(PEIZO) = 0;

    /// Sensors ///
    _TRIS(SDA) = INPUT; // Bi-directional
    _TRIS(SCL) = INPUT;
    _TRIS(INTM) = INPUT;
    _TRIS(INTA) = INPUT;

    /// Power Supply ///
    _TRIS(PW_STAT1) = INPUT;
    _TRIS(PW_STAT2) = INPUT;
    _TRIS(PW_CE) = OUTPUT;
    _LAT(PW_CE) = 0;        // Enable charging

    /// Bluetooth ///
    _TRIS(BT_MISO) = INPUT;
    _TRIS(BT_MOSI) = OUTPUT;
    _TRIS(BT_REQN) = OUTPUT;
    _TRIS(BT_SCK) = OUTPUT;
    _TRIS(BT_RDYN) = INPUT;
    _TRIS(BT_RESET) = OUTPUT;
    _LAT(BT_RESET) = 1;     // Keep BT in reset

    /// Pin-Change Interrupts ///
    _CNIEn(INTM_CN) = 1;
    _CNIEn(INTA_CN) = 1;

    /// Pin Pull Ups ///
    /*_CNPUE(BTN1_CN) = 1;
    _CNPUE(BTN2_CN) = 1;
    _CNPUE(BTN3_CN) = 1;
    _CNPUE(BTN4_CN) = 1;*/
    _CNPUE(SDA_CN) = 1;
    _CNPUE(SCL_CN) = 1;

    /// USB ///
    _TRIS(USB_DPLUS) = INPUT;
    _TRIS(USB_DMINUS) = INPUT;
    _TRIS(USB_VBUS) = INPUT;
    _CNPUE(USB_DPLUS_CN) = 0;

    /// Peripheral Pin Select ///
    // BT_MISO : SDI
    // BT_MOSI : SDO
    // BT_SCK : SCK
    // Chip select?

    /// Disable Unused Peripherals ///
    // Setting the PMD bit on a peripheral will cut the clock source to it.
    // You will not be able to write to any of its registers.

    // Disable ALL peripherals, let the system modules explicitly enable them if needed
    PMD1 = 0xFFFF;
    PMD2 = 0xFFFF;
    PMD3 = 0xFFFF;
    PMD4 = 0xFFFF;
    PMD5 = 0xFFFF;
    PMD6 = 0xFFFF;
}

void InitializeOsc() {

    _CPDIV = 0b00; //CPU prescaler

 	//On the PIC24FJ64GB004 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 32MHz
	//operation.  On these devices, user firmware needs to manually set the CLKDIV<PLLEN> bit to
	//power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        CLKDIVbits.PLLEN = 1;
        while(pll_startup_counter--);
    }
}
