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

typedef enum { evtUnknown, evtBtnPress, evtScreenOff, evtScreenOn } event_type_t;

typedef void (*event_proc_t)(event_type_t, uint param);

typedef struct {
    char name[6];

    proc_t init;
    proc_t process;     // Optional background processing task
    proc_t draw;
    event_proc_t event;

    // READ ONLY, SYSTEM USE
    bool isForeground;  // App is currently the foreground process being drawn on the screen
    task_t* task;
} application_t;

// Register a user-mode application with the system
void RegisterUserApplication(application_t* app);

// Set the current foreground app
void SetForegroundApp(application_t* app);

// Send an event to the current foreground app
void AppForegroundEvent(event_type_t type, uint param);

// Send an event to all registered apps
void AppGlobalEvent(event_type_t type, uint param);

// Create a new application struct
//application_t NewApplication(proc_t init, proc_t process, proc_t draw);

extern application_t* installed_apps[MAX_APPLICATIONS];
extern uint app_count;
extern application_t* foreground_app;


#endif	/* APP_H */

