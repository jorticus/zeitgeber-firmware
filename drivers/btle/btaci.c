/*
 * File:   BTACI.c
 * Author: Jared
 *
 * Created on 30 August 2014, 6:19 PM
 *
 * Handles communication with the BTLE ACI (Application Controller Interface)
 * This handles the SPI comms and RDYN/REQN control lines
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include <stdio.h>
#include <spi.h>
#include "hardware.h"
#include "util/fifo.h"
#include "util/util.h"

////////// Local Variables /////////////////////////////////////////////////////

#define FIFO_SIZE 8

#define MAX_PACKET_SIZE 32
#define MAX_TX_SIZE (MAX_PACKET_SIZE-1)
//#define MAX_RX_SIZE (MAX_PACKET_SIZE-2)

typedef struct {
    byte len;
    byte buf[MAX_PACKET_SIZE];
} message_t;


typedef struct {
    byte len;
    union {
        byte payload [MAX_PACKET_SIZE-1];
        
        struct {
            byte command;
        };
        
        struct {
            byte event;
        };
    };
} aci_packet_t;


static fifo_t recv_queue;
static fifo_t send_queue;

// recv_message_queue (queue of received ACI data, set asynchronously via interrupt)
// send_message_queue (queue of ACI commands to send. each goes through the reqn/rdyn handshaking process)
// aci_state (message_to_send, reqn, rdyn, waiting_for_rdyn/sending/done)


typedef enum { ddIdle, ddTransmit, ddReceive } aci_datadir_t;
typedef enum { txWaitForRDYN, txTransmit } aci_txstate_t;

static aci_datadir_t aci_state = ddIdle;
static aci_txstate_t aci_txstate;
static bool aci_rdyn = false;

static int credits = 0;

////////// Macros //////////////////////////////////////////////////////////////

#define _RDYN               (_PORT(BT_RDYN) == 0)

#define mREQN_START()       _LAT(BT_REQN) = 0
#define mREQN_FINISH()      _LAT(BT_REQN) = 1
#define mWaitRDYN()         while(!_RDYN) continue;
#define mWaitFinish()       while(_RDYN) continue;

////////// Prototypes //////////////////////////////////////////////////////////

static bool btle_aci_use_credit(byte command);
void btle_aci_transfer_packet(aci_packet_t* tx_packet);

////////// Methods /////////////////////////////////////////////////////////////


byte spi_transfer(byte b) {
    return 0;
}

static inline void btle_aci_start() {
    _LAT(BT_REQN) = 0;

    while (!_RDYN)
        continue;
}

static inline void btle_aci_stop() {
    _LAT(BT_REQN) = 1;

    while (_RDYN)
        continue;
}

void btle_aci_init() {
    // Initialize IO
    _LAT(BT_REQN) = 1;      // Active-low
    _TRIS(BT_REQN) = OUTPUT;
    _TRIS(BT_RDYN) = INPUT;
    
    // Set up pin-change interrupt for RDYN signal

    // Set up the SPI interface

    // Initialize FIFOs
    fifo_init(&recv_queue, FIFO_SIZE);
    fifo_init(&send_queue, FIFO_SIZE);

    _LAT(BT_RESET) = 1;     // Enable BT
    // NOTE: Must wait 62ms before RDYN is valid
}

void btle_aci_process() {

    // The bluetooth chip wants to send a packet
    if (_RDYN) {
        printf("NRF: Event received\n");
        btle_aci_transfer_packet(NULL);
    }
    
}

static bool btle_aci_use_credit(byte command) {
    // Check we have enough available credits
    if (command == 0 || command == 0) {

        if (credits < 1) {
            printf("NRF: Insufficient credits\n");
            return false; // Insufficient credits
        }

        // Use a credit
        credits--;
    }
    
    return true;
}



bool btle_aci_transfer_packet(aci_packet_t* tx_packet) {
    // Communications are full-duplex (receive and transmit at the same time)

    aci_packet_t rx_packet;

    byte tx_len = 0;
    byte tx_command = 0;

    if (tx_packet != NULL) {
        tx_len = tx_packet->len;
        tx_command = tx_packet->command;
        printf("TX: %d bytes (code:0x%x)\n", tx_packet->len, tx_packet->event);
    }
    
    // Check we have enough available credits
    if (tx_len > 0) {
        if (!btle_aci_use_credit(tx_command))
            return false; // Insufficient credits
    }

    // Start the transmission
    btle_aci_start();

    // Transfer the packet headers
    byte rx_debug = spi_transfer(tx_len);
    byte rx_len = spi_transfer(tx_command);
    rx_packet.len = rx_len;

    // Transfer all requires RX and TX bytes
    uint i;
    byte len = max(rx_len, tx_len);
    for (i=0; i<len; i++) {
        byte rxb, txb;

        if ((tx_packet != NULL) && (i < tx_len))
            txb = tx_packet->payload[i+1];  // Transmit payload
        else
            txb = 0x00;  // Receive only

        rxb = spi_transfer(txb);

        if (i < rx_len)
            rx_packet.payload[i] = rxb;
    }

    // Finish the transmission
    btle_aci_stop();

    // Process the received packet
    if ((rx_debug == 0) && (rx_packet.len > 0)) {
        printf("RX: %d bytes (code:0x%x)\n", rx_packet.len, rx_packet.event);

        //TODO: Process the event
        // is it a response to a command? -> set flag and notify
        // is it an asynchronous event? -> call an appropriate callback & debug
    }

    return true;
}
