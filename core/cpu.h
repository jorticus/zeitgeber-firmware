/* 
 * File:   cpu.h
 * Author: Jared
 *
 * Created on 5 July 2013, 2:56 PM
 *
 * Provides methods for controlling CPU performance and power saving features
 */

#ifndef CPU_H
#define	CPU_H


typedef enum { 
    cpuNormal,      // Running foreground tasks
    cpuBackground,  // Running background tasks
    cpuIdle,        // Idle
    cpuSleep        // Sleeping
} cpu_state_t;
extern cpu_state_t cpu_state;

extern void InitializeIO();
extern void InitializeOsc();

extern void WatchSleep();

#endif	/* CPU_H */

