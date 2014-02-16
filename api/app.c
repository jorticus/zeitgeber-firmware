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


////////// Methods /////////////////////////////////////////////////////////////

void RegisterUserApplication(application_t* app) {

    // Assign a scheduler task to the app
	app->task = RegisterTask(app->name, app->process);

    installed_apps[app_count++] = app;
}

void InitializeApplications() {
    uint i;
    for (i=0; i<app_count; i++) {
        application_t* app = installed_apps[i];

        if (app->init != NULL)
            app->init();
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
