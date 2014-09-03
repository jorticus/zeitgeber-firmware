/*
 * File:   btaci.h
 * Author: Jared
 *
 * Created on 3 September 2014, 11:30 PM
 */

#ifndef BTACI_H
#define	BTACI_H

#define FIFO_SIZE 8

#define MAX_PACKET_SIZE 32
#define MAX_TX_SIZE (MAX_PACKET_SIZE-1)
#define MAX_CONTENT_SIZE (MAX_PACKET_SIZE-2)

typedef struct {
    byte len;
    byte buf[MAX_PACKET_SIZE];
} message_t;

typedef struct {
    byte len;   // Length of the payload
    union {
        byte payload [MAX_PACKET_SIZE-1];

        struct {
            byte command;
            byte content [MAX_CONTENT_SIZE];
        };
    };
} aci_packet_t;

typedef struct {
    byte b[6];
} address_t;

typedef enum { nsUnknown=0x00, nsTest=0x01, nsSetup=0x02, nsStandby=0x03 } device_state_t;


bool btle_aci_transfer_packet(aci_packet_t* tx_packet);
void btle_aci_reset();
void btle_debug_packet(aci_packet_t* packet);

#endif	/* BTACI_H */

