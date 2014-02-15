/* 
 * File:   app.h
 * Author: Jared
 *
 * Created on 9 July 2013, 2:40 PM
 *
 * User-mode application definitions
 */

#ifndef APP_H
#define	APP_H

#include "core/kernel.h"

#define MAX_APPLICATIONS 10

typedef enum { 
    asIdle,         // App is not active and is not processing. Allows CPU to go into sleep state
    asWaiting,      // App is waiting for an interrupt, but not currently processing anything. The app should register a callback to set the state to asRunning when the interrupt executes
    asRunning,      // App is currently processing stuff, but not actively displaying on the screen (with the exception of icons at the top of the screen)
    //asForeground    // App is the foreground display app being drawn
} app_state_t;

typedef struct {
	char name[6];

    proc_t init;
    proc_t process;
    proc_t draw;
    app_state_t state;

    // READ ONLY, SYSTEM USE
    bool isForeground;  // App is currently the foreground process being drawn on the screen
    task_t* task;
} application_t;

#define APPLICATION(name, init, process, draw) {name, init, process, draw, asIdle, false, NULL}

// Register a user-mode application with the system
void RegisterUserApplication(application_t* app);

// Create a new application struct
//application_t NewApplication(proc_t init, proc_t process, proc_t draw);

extern application_t* installed_apps[MAX_APPLICATIONS];
extern uint app_count;


#endif	/* APP_H */

