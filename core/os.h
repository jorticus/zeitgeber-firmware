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

#define DRAW_INTERVAL 1000//(1000/30) // 30Hz refresh rate for OLED
#define PROCESS_CORE_INTERVAL 50
#define APP_INTERVAL (1000/100)

void InitializeOS();

// Set the specified app to be the foreground process
void SetForegroundApp(application_t* app);

void ScreenOff();
void ScreenOn();

#endif	/* OS_H */

