/* 
 * File:   system.h
 * Author: Jared
 *
 * Created on 5 July 2013, 12:48 PM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#define HID_BOOTLOADER

#ifdef WIN32

#include "win32\stdafx.h"
typedef unsigned short uint;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned int uint32;

#define false 0
#define true 1
#define bool char

#define NULL 0
#define FALSE 0
#define TRUE 1

#define PROGMEM
#define INLINE

#else

#include <p24Fxxxx.h>
#include <GenericTypeDefs.h>

typedef UINT uint;
typedef UINT8 uint8;
typedef UINT16 uint16;
typedef UINT32 uint32;
typedef INT8 int8;
typedef INT16 int16;
typedef INT32 int32;
typedef UINT8 byte;

//typedef enum { false, true } bool;
#define bool UINT8
#define true 1
#define false 0

#define PROGMEM //__prog__
#define INLINE __inline__

#define Reset() asm("reset")

#endif

#define RCON_RESET (_RCON_POR_MASK | _RCON_BOR_MASK | _RCON_WDTO_MASK | _RCON_SWR_MASK | _RCON_EXTR_MASK | _RCON_CM_MASK | _RCON_IOPUWR_MASK | _RCON_TRAPR_MASK)
#define UNEXPECTED_RESET (_RCON_POR_MASK| _RCON_BOR_MASK | _RCON_WDTO_MASK | _RCON_CM_MASK | _RCON_IOPUWR_MASK | _RCON_TRAPR_MASK)

#define MAX_UINT8 255
#define MAX_UINT16 65535
#define MAX_UINT32 4294967295ULL
#define MAX_UINT MAX_UINT16

// Generic function pointer
typedef void (*proc_t)(void);

#define isr __attribute__((interrupt, auto_psv))
#define shadow_isr __attribute__((interrupt, shadow, auto_psv))

#endif	/* SYSTEM_H */

