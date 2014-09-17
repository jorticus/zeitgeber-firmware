/* 
 * File:   usb.h
 * Author: Jared
 *
 * Created on 8 December 2013, 4:54 PM
 */

#ifndef USB_H
#define	USB_H

#define PACKET_SIZE 64

extern void InitializeUSB();

extern unsigned char usb_rx_buffer[PACKET_SIZE];
extern unsigned char usb_tx_buffer[PACKET_SIZE];

//extern USB_HANDLE USBOutHandle = 0;
//extern USB_HANDLE USBInHandle = 0;

typedef void (*usb_rx_packet_cb)(unsigned char* packet);

void USBProcess(usb_rx_packet_cb receive_callback);
void USBSendPacket(unsigned char* packet);
BOOL USBBusy();

#endif	/* USB_H */

