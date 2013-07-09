/*
 * File:   oled/ssd1351.c
 * Author: Jared
 *
 * Created on 9 July 2013, 12:51 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "hardware.h"
#include "oled.h"
#include "comms.h"
#include "ssd1351.h"

////////// Defines /////////////////////////////////////////////////////////////

#define SSD1351_CMD_SETCOLUMNADDRESS          0x15
#define SSD1351_CMD_SETROWADDRESS             0x75
#define SSD1351_CMD_WRITERAM                  0x5C // Write data to GRAM and increment until another command is sent
#define SSD1351_CMD_READRAM                   0x5D // Read data from GRAM and increment until another command is sent
#define SSD1351_CMD_COLORDEPTH                0xA0 // Numerous functions include increment direction ... see DS
                                            // A0[0] = Address Increment Mode (0 = horizontal, 1 = vertical)
                                            // A0[1] = Column Address Remap (0 = left to right, 1 = right to left)
                                            // A0[2] = Color Remap (0 = ABC, 1 = CBA) - HW RGB/BGR switch
                                            // A0[4] = COM Scan Direction (0 = top to bottom, 1 = bottom to top)
                                            // A0[5] = Odd/Even Paid Split
                                            // A0[7:6] = Display Color Mode (00 = 8-bit, 01 = 65K, 10/11 = 262K, 8/16-bit interface only)
#define SSD1351_CMD_SETDISPLAYSTARTLINE       0xA1
#define SSD1351_CMD_SETDISPLAYOFFSET          0xA2
#define SSD1351_CMD_SETDISPLAYMODE_ALLOFF     0xA4 // Force entire display area to grayscale GS0
#define SSD1351_CMD_SETDISPLAYMODE_ALLON      0xA5 // Force entire display area to grayscale GS63
#define SSD1351_CMD_SETDISPLAYMODE_RESET      0xA6 // Resets the display area relative to the above two commands
#define SSD1351_CMD_SETDISPLAYMODE_INVERT     0xA7 // Inverts the display contents (GS0 -> GS63, GS63 -> GS0, etc.)
#define SSD1351_CMD_FUNCTIONSELECTION         0xAB // Enable/Disable the internal VDD regulator
#define SSD1351_CMD_SLEEPMODE_DISPLAYOFF      0xAE // Sleep mode on (display off)
#define SSD1351_CMD_SLEEPMODE_DISPLAYON       0xAF // Sleep mode off (display on)
#define SSD1351_CMD_SETPHASELENGTH            0xB1 // Larger capacitance may require larger delay to discharge previous pixel state
#define SSD1351_CMD_ENHANCEDDRIVINGSCHEME     0xB2
#define SSD1351_CMD_SETFRONTCLOCKDIV          0xB3 // DCLK divide ration fro CLK (from 1 to 16)
#define SSD1351_CMD_SETSEGMENTLOWVOLTAGE      0xB4
#define SSD1351_CMD_SETGPIO                   0xB5
#define SSD1351_CMD_SETSECONDPRECHARGEPERIOD  0xB6
#define SSD1351_CMD_GRAYSCALELOOKUP           0xB8
#define SSD1351_CMD_LINEARLUT                 0xB9
#define SSD1351_CMD_SETPRECHARGEVOLTAGE       0xBB
#define SSD1351_CMD_SETVCOMHVOLTAGE           0xBE
#define SSD1351_CMD_SETCONTRAST               0xC1
#define SSD1351_CMD_MASTERCONTRAST            0xC7
#define SSD1351_CMD_SETMUXRRATIO              0xCA
#define SSD1351_CMD_NOP3                      0xD1
#define SSD1351_CMD_NOP4                      0xE3
#define SSD1351_CMD_SETCOMMANDLOCK            0xFD
#define SSD1351_CMD_HORIZONTALSCROLL          0x96
#define SSD1351_CMD_STOPMOVING                0x9E
#define SSD1351_CMD_STARTMOVING               0x9F

const uint8 gamma_lut[] = {
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
    0x12, 0x13, 0x15, 0x17, 0x19, 0x1B, 0x1D, 0x1F,
    0x21, 0x23, 0x25, 0x27, 0x2A, 0x2D, 0x30, 0x33,
    0x36, 0x39, 0x3C, 0x3F, 0x42, 0x45, 0x48, 0x4C,
    0x50, 0x54, 0x58, 0x5C, 0x60, 0x64, 0x68, 0x6C,
    0x70, 0x74, 0x78, 0x7D, 0x82, 0x87, 0x8C, 0x91,
    0x96, 0x9B, 0xA0, 0xA5, 0xAA, 0xAF, 0xB4
};

////////// Methods /////////////////////////////////////////////////////////////

void ssd1351_Init() {

}

void ssd1351_PowerOn() {
    // Power on initialization sequence
    
    ssd1351_command(SSD1351_CMD_SETCOMMANDLOCK);
    ssd1351_data(0x12);

    ssd1351_command(SSD1351_CMD_SETCOMMANDLOCK);
    ssd1351_data(0xB1);

    ssd1351_command(SSD1351_CMD_SLEEPMODE_DISPLAYOFF);

    ssd1351_command(SSD1351_CMD_SETFRONTCLOCKDIV);
    ssd1351_data(0xF1);

    //...
    
}

void ssd1351_PowerOff() {
    // Power off initialization sequence
}

void ssd1351_SetCursor(uint8 x, uint8 y) {

}