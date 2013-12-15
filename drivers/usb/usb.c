/*
 * File:   drivers/usb/usb.c
 * Author: Jared
 *
 * Created on 8 December 2013, 4:25 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "hardware.h"
#include "drivers/usb/usb.h"

#include "usb_config.h"
#include "./USB/usb.h"
#include "./USB/usb_function_hid.h"

////////// Defines /////////////////////////////////////////////////////////////

////////// Global Variables ////////////////////////////////////////////////////

//char USB_In_Buffer[64];
//char USB_Out_Buffer[64];

//unsigned char ReceivedDataBuffer[64];
//unsigned char ToSendDataBuffer[64];

unsigned char usb_rx_buffer[PACKET_SIZE];
//unsigned char usb_tx_buffer[PACKET_SIZE];

USB_HANDLE USBOutHandle = 0; //USB handle.  Must be initialized to 0 at startup.
USB_HANDLE USBInHandle = 0; //USB handle.  Must be initialized to 0 at startup.

static proc_t on_usb_sleep = NULL;
static proc_t on_usb_wake = NULL;

////////// Methods /////////////////////////////////////////////////////////////

void InitializeUSB(proc_t usb_sleep_cb, proc_t usb_wake_cb) {
    // Enable USB peripheral
    _USB1MD = 0;

    // Required for the USB device to enumerate
    _CNPUE(USB_DPLUS_CN) = 1;

    USBDeviceInit(); //usb_device.c.  Initializes USB module SFRs and firmware
    //variables to known states.

    //initialize the variable holding the handle for the last
    // transmission
    USBOutHandle = 0;
    USBInHandle = 0;

    on_usb_sleep = usb_sleep_cb;
    on_usb_wake = usb_wake_cb;

    // Attach USB interrupts
#if defined(USB_INTERRUPT)
    USBDeviceAttach();
#endif
}

void USBProcess(usb_rx_packet_cb receive_callback) {
    if ((USBDeviceState < CONFIGURED_STATE) || (USBSuspendControl == 1)) return;

    //Check if we have received an OUT data packet from the host
    if (!HIDRxHandleBusy(USBOutHandle)) {
        receive_callback(usb_rx_buffer);

        // Re-arm the OUT endpoint, so we can receive the next OUT data packet
        // that the host may try to send us.
        USBOutHandle = HIDRxPacket(HID_EP, (BYTE*) &usb_rx_buffer, PACKET_SIZE);
    }
}

void USBSendPacket(unsigned char* packet) {
    if(!HIDTxHandleBusy(USBInHandle)) {
        USBInHandle = HIDTxPacket(HID_EP,(BYTE*)&packet[0], PACKET_SIZE);
    }
}

BOOL USBTransmitBusy() {
    return HIDTxHandleBusy(USBInHandle);
}


////////// USB Callbacks ///////////////////////////////////////////////////////

/* 
 * Call back that is invoked when a USB suspend is detected
 */
void USBCBSuspend(void) {
    if (on_usb_sleep != NULL)
        on_usb_sleep();

    //Example power saving code.  Insert appropriate code here for the desired
    //application behavior.  If the microcontroller will be put to sleep, a
    //process similar to that shown below may be used:

    //ConfigureIOPinsForLowPower();
    //SaveStateOfAllInterruptEnableBits();
    //DisableAllInterruptEnableBits();
    //EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
    //Sleep();
    //RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
    //RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

    //IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is
    //cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause
    //things to not work as intended.


#if defined(__C30__) || defined __XC16__
    // USBSleepOnSuspend();
#endif
}

/*
 * The host may put USB peripheral devices in low power
 * suspend mode (by "sending" 3+ms of idle).  Once in suspend
 * mode, the host may wake the device back up by sending non-
 * idle state signalling.
 *
 * This call back is invoked when a wakeup from USB suspend
 * is detected.
 */
void USBCBWakeFromSuspend(void) {
    // If clock switching or other power savings measures were taken when
    // executing the USBCBSuspend() function, now would be a good time to
    // switch back to normal full power run mode conditions.  The host allows
    // 10+ milliseconds of wakeup time, after which the device must be
    // fully back to normal, and capable of receiving and processing USB
    // packets.  In order to do this, the USB module must receive proper
    // clocking (IE: 48MHz clock must be available to SIE for full speed USB
    // operation).
    // Make sure the selected oscillator settings are consistent with USB
    // operation before returning from this function.

    if (on_usb_wake != NULL)
        on_usb_wake();
}

/*
 * The USB host sends out a SOF packet to full-speed
 * devices every 1 ms. This interrupt may be useful
 * for isochronous pipes. End designers should
 * implement callback routine as necessary.
 */
void USBCB_SOF_Handler(void) {
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.

}

/*
 * The purpose of this callback is mainly for
 * debugging during development. Check UEIR to see
 * which error causes the interrupt.
 */
void USBCBErrorHandler(void) {
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

    // Typically, user firmware does not need to do anything special
    // if a USB error occurs.  For example, if the host sends an OUT
    // packet to your device, but the packet gets corrupted (ex:
    // because of a bad connection, or the user unplugs the
    // USB cable during the transmission) this will typically set
    // one or more USB error interrupt flags.  Nothing specific
    // needs to be done however, since the SIE will automatically
    // send a "NAK" packet to the host.  In response to this, the
    // host will normally retry to send the packet again, and no
    // data loss occurs.  The system will typically recover
    // automatically, without the need for application firmware
    // intervention.

    // Nevertheless, this callback function is provided, such as
    // for debugging purposes.
}

/*
 *  When SETUP packets arrive from the host, some
 * 	firmware must process the request and respond
 *	appropriately to fulfill the request.  Some of
 *	the SETUP packets will be for standard
 *	USB "chapter 9" (as in, fulfilling chapter 9 of
 *	the official USB specifications) requests, while
 *	others may be specific to the USB device class
 *	that is being implemented.  For example, a HID
 *	class device needs to be able to respond to
 *	"GET REPORT" type of requests.  This
 *	is not a standard USB chapter 9 request, and
 *	therefore not handled by usb_device.c.  Instead
 *	this request should be handled by class specific
 *	firmware, such as that contained in usb_function_hid.c.
 */
void USBCBCheckOtherReq(void) {
    USBCheckHIDRequest();
}

/* The USBCBStdSetDscHandler() callback function is
 * called when a SETUP, bRequest: SET_DESCRIPTOR request
 * arrives.  Typically SET_DESCRIPTOR requests are
 * not used in most applications, and it is
 * optional to support this type of request.
 */
void USBCBStdSetDscHandler(void) {
    // Must claim session ownership if supporting this request
}

/* This function is called when the device becomes
 * initialized, which occurs after the host sends a
 * SET_CONFIGURATION (wValue not = 0) request.  This
 * callback function should initialize the endpoints
 * for the device's usage according to the current
 * configuration.
 */
void USBCBInitEP(void) {
    //enable the HID endpoint
    USBEnableEndpoint(HID_EP, USB_IN_ENABLED | USB_OUT_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP);
    //Re-arm the OUT endpoint for the next packet
    USBOutHandle = HIDRxPacket(HID_EP, (BYTE*) & usb_rx_buffer, PACKET_SIZE);

    if (on_usb_wake != NULL)
        on_usb_wake();
}

/*
 * This function is called from the USB stack to
 * notify a user application that a USB event
 * occured.  This callback is in interrupt context
 * when the USB_INTERRUPT option is selected.
 */
BOOL USER_USB_CALLBACK_EVENT_HANDLER(int event, void *pdata, WORD size) {
    switch (event) {
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED:
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            //Add application specific callback task or callback function here if desired.
            //The EVENT_TRANSFER_TERMINATED event occurs when the host performs a CLEAR
            //FEATURE (endpoint halt) request on an application endpoint which was
            //previously armed (UOWN was = 1).  Here would be a good place to:
            //1.  Determine which endpoint the transaction that just got terminated was
            //      on, by checking the handle value in the *pdata.
            //2.  Re-arm the endpoint if desired (typically would be the case for OUT
            //      endpoints).
            break;
        default:
            break;
    }
    return TRUE;
}