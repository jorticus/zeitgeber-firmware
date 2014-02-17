/* 
 * File:   os.h
 * Author: Jared
 *
 * Created on 19 July 2013, 5:41 PM
 *
 * Operating system
 */

#ifndef OS_H
#define	OS_H

#include "api/app.h"

#define DRAW_INTERVAL 100
//#define PROCESS_CORE_INTERVAL 250
#define APP_INTERVAL (1000/100)

#define CORE_PROCESS_INTERVAL 50    // Update rate when screen is on
#define CORE_STANDBY_INTERVAL 250   // Update rate when screen is off (standby)

void InitializeOS();

// Set the specified app to be the foreground process
void SetForegroundApp(application_t* app);

void ScreenOff();
void ScreenOn();
void DisplayBootScreen();

#endif	/* OS_H */

