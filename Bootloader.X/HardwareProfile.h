/********************************************************************
 FileName:     	HardwareProfile - PIC24FJ64GB004 PIM.h
 Dependencies:  See INCLUDES section
 Processor:     PIC24FJ64GB004
 Hardware:      PIC24FJ64GB004 PIM
 Compiler:      Microchip C30
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
  2.4b  04/08/2009   Initial support for PIC24FJ64GB004 family
********************************************************************/

#ifndef HARDWARE_PROFILE_ZEITGEBER_H
#define HARDWARE_PROFILE_ZEITGEBER_H

// Import hardware configuration from main project
#include <..\hardware.h>


//#define USE_SELF_POWER_SENSE_IO
//#define tris_self_power     TRISAbits.TRISA2    // Input
#define self_power          1


//#define USE_USB_BUS_SENSE_IO
//#define tris_usb_bus_sense  TRISFbits.TRISF7    // Input
#define USB_BUS_SENSE       _PORT(USB_VBUS)

//Uncomment this to make the output HEX of this project
//   to be able to be bootloaded using the HID bootloader
//#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER

#define PIC24FJ256DA210_DEV_BOARD

#define CLOCK_FREQ 32000000


#endif  //HARDWARE_PROFILE_PIC24FJ64GB004_PIM_H
