/*
 * File:   btaci_commands.h
 * Author: Jared
 *
 * Created on 3 September 2014, 11:30 PM
 */

#ifndef BTACI_COMMANDS_H
#define	BTACI_COMMANDS_H

//// 24. System Commands ////

#define NRF_CMD_TEST                    0x01
#define NRF_CMD_ECHO                    0x02
#define NRF_CMD_DTM_COMMAND             0x03
#define NRF_CMD_SLEEP                   0x04
#define NRF_CMD_WAKEUP                  0x05
#define NRF_CMD_SETUP                   0x06
#define NRF_CMD_READ_DYNAMIC_DATA       0x07
#define NRF_CMD_WRITE_DYNAMIC_DATA      0x08
#define NRF_CMD_GET_DEVICE_VERSION      0x09
#define NRF_CMD_GET_DEVICE_ADDRESS      0x0A
#define NRF_CMD_GET_BATTERY_LEVEL       0x0B
#define NRF_CMD_GET_TEMPERATURE         0x0C
#define NRF_CMD_RADIO_RESET             0x0E
#define NRF_CMD_CONNECT                 0x0F
#define NRF_CMD_BOND                    0x10
#define NRF_CMD_DISCONNECT              0x11
#define NRF_CMD_SET_TX_POWER            0x12
#define NRF_CMD_CHANGE_TIMING_REQUEST   0x13
#define NRF_CMD_OPEN_REMOTE_PIPE        0x14
#define NRF_CMD_SET_APPL_LATENCY        0x19
#define NRF_CMD_SET_KEY                 0x1A
#define NRF_CMD_OPEN_ADV_PIPE           0x1B
#define NRF_CMD_BROADCAST               0x1C
#define NRF_CMD_BOND_SECURITY_REQUEST   0x1D
#define NRF_CMD_DIRECTED_CONNECT        0x1E
#define NRF_CMD_CLOSE_REMOTE_PIPE       0x1F


//// 25. Data Commands ////

#define NRF_CMD_SET_LOCAL_DATA          0x0D
#define NRF_CMD_SEND_DATA               0x15
#define NRF_CMD_SEND_DATA_ACK           0x16
#define NRF_CMD_REQUEST_DATA            0x17
#define NRF_CMD_SEND_DATA_NACK          0x18


#endif	/* BTACI_COMMANDS_H */

