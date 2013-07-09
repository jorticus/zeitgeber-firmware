/* 
 * File:   system.h
 * Author: Jared
 *
 * Created on 5 July 2013, 12:48 PM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#include <p24Fxxxx.h>
#include <GenericTypeDefs.h>

typedef UINT uint;
typedef UINT8 uint8;
typedef UINT16 uint16;
typedef INT8 int8;
typedef INT16 int16;
typedef INT32 int32;
typedef enum { false, true } bool;

// Generic function pointer
typedef void (*proc_t)(void);

#define isr __attribute__((interrupt, auto_psv))
#define shadow_isr __attribute__((interrupt, shadow, auto_psv))

#endif	/* SYSTEM_H */

