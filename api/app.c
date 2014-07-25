/*
 * File:   app.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "core/kernel.h"
#include "core/os.h"
#include "app.h"

////////// Variables ///////////////////////////////////////////////////////////

application_t* installed_apps[MAX_APPLICATIONS];
uint app_count = 0;

application_t* foreground_app = NULL;

////////// Methods /////////////////////////////////////////////////////////////

void RegisterUserApplication(application_t* app) {

    // Assign a scheduler task to the app
    if (app->process != NULL)
        app->task = RegisterTask(app->name, app->process);

    installed_apps[app_count++] = app;
}

void InitializeApplications() {
    uint i;
    for (i=0; i<app_count; i++) {
        ClrWdt();
        application_t* app = installed_apps[i];
        BootPrintln(app->name);

        if (app->init != NULL)
            app->init();
    }
}

void SetForegroundApp(application_t* app) {
    if (foreground_app != NULL) {
        foreground_app->isForeground = false;
        //foreground_app->task->state = tsStop; // Disable the other app
    }
    app->isForeground = true;
    foreground_app = app;

    //app->task->state = tsRun;

    //TODO: Maybe some sort of transition between screens?
}

void AppForegroundEvent(event_type_t type, uint param) {
    if (foreground_app != NULL && foreground_app->event != NULL) {
        foreground_app->event(type, param);
    }
}

void AppGlobalEvent(event_type_t type, uint param) {
    uint i;
    for (i=0; i<app_count; i++) {
        if (installed_apps[i]->event != NULL)
            installed_apps[i]->event(type, param);
    }
}

/*application_t NewApplication(proc_t init, proc_t process, proc_t draw) {
	application_t app;

	app.init = init;
	app.process = process;
	app.draw = draw;

	app.state = asIdle;

	app.isForeground = false;
	app.task = NULL;

	return app;
}*/
