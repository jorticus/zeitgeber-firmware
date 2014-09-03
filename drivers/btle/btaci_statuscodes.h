/*
 * File:   btaci_statuscodes.h
 * Author: Jared
 *
 * Created on 3 September 2014, 11:30 PM
 */

#ifndef BTACI_STATUSCODES_H
#define	BTACI_STATUSCODES_H

//// ACI Status Codes ////

#define ACI_STATUS_SUCCESS                          0x00    // Success
#define ACI_STATUS_TRANSACTION_CONTINUE             0x01    // Transaction continuation status
#define ACI_STATUS_TRANSACTION_COMPLETE             0x02    // Transaction completed
#define ACI_STATUS_EXTENDED                         0x03    // Extended status, further checks needed

#define ACI_STATUS_ERROR_UNKNOWN                    0x80    // Unknown error
#define ACI_STATUS_ERROR_INTERNAL                   0x81    // Internal error
#define ACI_STATUS_ERROR_CMD_UNKNOWN                0x82    // Unknown command
#define ACI_STATUS_ERROR_DEVICE_STATE_INVALID       0x83    // Command invalid in the current device state
#define ACI_STATUS_ERROR_INVALID_LENGTH             0x84    // Invalid length
#define ACI_STATUS_ERROR_INVALID_PARAMETER          0x85    // Invalid input parameters
#define ACI_STATUS_ERROR_BUSY                       0x86    // Busy
#define ACI_STATUS_ERROR_INVALID_DATA               0x87    // Invalid data format or contents
#define ACI_STATUS_ERROR_CRC_MISMATCH               0x88    // CRC mismatch
#define ACI_STATUS_ERROR_UNSUPPORTED_SETUP_FORMAT   0x89    // Unsupported setup format
#define ACI_STATUS_ERROR_INVALID_SEQ_NO             0x8A    // Invalid sequence number during a write dynamic data sequence
#define ACI_STATUS_ERROR_SETUP_LOCKED               0x8B    // Setup data is locked and cannot be modified
#define ACI_STATUS_ERROR_LOCK_FAILED                0x8C    // Setup error due to lock verification failure
#define ACI_STATUS_ERROR_BOND_REQUIRED              0x8D    // Bond required: Local service pipes need bonded/trusted peer
#define ACI_STATUS_ERROR_REJECTED                   0x8E    // Command rejected as a transaction is still pending
#define ACI_STATUS_ERROR_DATA_SIZE                  0x8F    // Pipe error event: data size exceeds size specified for pipe, transmit failed
#define ACI_STATUS_ERROR_PIPE_INVALID               0x90    // Pipe error event: transmit failed, invalid or unavailable pipe number or unknown pipe type
#define ACI_STATUS_ERROR_CREDIT_NOT_AVAILABLE       0x91    // Pipe error event: credit not available
#define ACI_STATUS_ERROR_PEER_ATT_ERROR             0x92    // Pipe error event: Peer device has set an error on a pipe operation on the remote characteristic
#define ACI_STATUS_ERROR_ADVT_TIMEOUT               0x93    // Connection was not established before the BTLE advertising was stopped
#define ACI_STATUS_ERROR_PEER_SMP_ERROR             0x94    // Remote device triggered a security manager protocol error
#define ACI_STATUS_ERROR_PIPE_TYPE_INVALID          0x95    // Pipe error event: pipe type invalid for the selected operation
#define ACI_STATUS_ERROR_PIPE_STATE_INVALID         0x96    // Pipe error event: pipe state invalid for the selected operation
#define ACI_STATUS_ERROR_INVALID_KEY_SIZE           0x97    // Invalid key size provided
#define ACI_STATUS_ERROR_INVALID_KEY_DATA           0x98    // Invalid key data provided

//// Bonding Status Codes ////
// Status codes applicable for BondStatusEvent

#define ACI_BOND_STATUS_SUCCESS                     0x00
#define ACI_BOND_STATUS_FAILED                      0x01
#define ACI_BOND_STATUS_FAILED_TIMED_OUT            0x02
#define ACI_BOND_STATUS_FAILED_PASSKEY_ENTRY_FAILED 0x81
#define ACI_BOND_STATUS_FAILED_OOB_UNAVAILABLE      0x82
#define ACI_BOND_STATUS_FAILED_AUTHENTICATION_REQ   0x83
#define ACI_BOND_STATUS_FAILED_CONFIRM_VALUE        0x84
#define ACI_BOND_STATUS_FAILED_PAIRING_UNSUPPORTED  0x85
#define ACI_BOND_STATUS_FAILED_ENCRYPTION_KEY_SIZE  0x86
#define ACI_BOND_STATUS_FAILED_SMP_CMD_UNSUPPORTED  0x87
#define ACI_BOND_STATUS_FAILED_UNSPECIFIED_REASON   0x88
#define ACI_BOND_STATUS_FAILED_REPEATED_ATTEMPTS    0x89
#define ACI_BOND_STATUS_FAILED_INVALID_PARAMETERS   0x90

//// Error Codes ////
// Status codes applicable for PipeErrorEvent

#define ERROR_INVALID_HANDLE                        0x01
#define ERROR_READ_NOT_PERMITTED                    0x02
#define ERROR_WRITE_NOT_PERMITTED                   0x03
#define ERROR_INVALID_PDU                           0x04
#define ERROR_INSUFFICIENT_AUTHENTICATION           0x05
#define ERROR_REQUEST_NOT_SUPPORTED                 0x06
#define ERROR_INVALID_OFFSET                        0x07
#define ERROR_INSUFFICIENT_AUTHORIZATION            0x08
#define ERROR_PREPARE_QUEUE_FULL                    0x09
#define ERROR_ATTRIBUTE_NOT_FOUND                   0x0A
#define ERROR_ATTRIBUTE_NOT_LONG                    0x0B
#define ERROR_INSUFFICIENT_ENCRYPTION_KEY_SIZE      0x0C
#define ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH        0x0D
#define ERROR_UNLIKELY_ERROR                        0x0E
#define ERROR_INSUFFICIENT_ENCRYPTION               0x0F
#define ERROR_UNSUPPORTED_GROUP_TYPE                0x10
#define ERROR_INSUFFICIENT_RESOURCES                0x11
// Application error from 0x80-0xFF


#endif	/* BTACI_STATUSCODES_H */

