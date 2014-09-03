/*
 * File:   btaci_events.h
 * Author: Jared
 *
 * Created on 3 September 2014, 11:30 PM
 */

#ifndef BTACI_EVENTS_H
#define	BTACI_EVENTS_H


//// 26. System Events ////

#define NRF_EVENT_DEVICE_STARTED        0x81    // DeviceStartedEvent indicates reset recovery or a state change
#define NRF_EVENT_ECHO                  0x82    // Response from an ACI Echo command
#define NRF_EVENT_HARDWARE_ERROR        0x83
#define NRF_EVENT_COMMAND_RESPONSE      0x84
#define NRF_EVENT_CONNECTED             0x85    // A connection has been established with a peer device
#define NRF_EVENT_DISCONNECTED          0x86
#define NRF_EVENT_BOND_STATUS           0x87
#define NRF_EVENT_PIPE_STATUS           0x88
#define NRF_EVENT_TIMING                0x89
#define NRF_EVENT_DISPLAY_KEY           0x8E
#define NRF_EVENT_KEY_REQUEST           0x8F


typedef struct {
    uint8 len;
    uint8 event;

    uint8 operating_mode;
    uint8 hw_error;
    uint8 data_credit_available;
} device_started_evt;

typedef struct {
    uint8 len;
    uint8 event;

    uint8 command;
    uint8 status;
    uint8 response_data[MAX_CONTENT_SIZE];
} command_response_evt;

typedef struct {
    uint8 len;
    uint8 event;

    uint8 address_type;
    address_t peer_address;
    uint16 connection_interval; //TODO: Verify byte order
    uint16 slave_latency;
    uint16 supervision_timeout;
    uint8 master_clock_accuracy;
} connected_evt;



//// 27. Data Events ////

#define NRF_EVENT_DATA_CREDIT           0x8A    // Number of credits to return to the application controller
#define NRF_EVENT_PIPE_ERROR            0x8D    // A pipe transmission failure/error has occurred
#define NRF_EVENT_DATA_RECEIVED         0x8C    // Indicates that data has been received from the peer device
#define NRF_EVENT_DATA_ACK              0x8B    // Indicates reception of data by the peer device




#endif	/* BTACI_EVENTS_H */

