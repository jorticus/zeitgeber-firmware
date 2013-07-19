/*
 * File:   app.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "core/scheduler.h"
#include "core/os.h"
#include "app.h"

////////// Variables ///////////////////////////////////////////////////////////

#define MAX_APPLICATIONS 10

application_t* installed_apps[MAX_APPLICATIONS];
uint app_count = 0;


////////// Methods /////////////////////////////////////////////////////////////

void RegisterUserApplication(application_t* app) {

    // Assign a scheduler task to the app
    app->task = RegisterTask(app->process, APP_INTERVAL);

    installed_apps[app_count++] = app;
}
