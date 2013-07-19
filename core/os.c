/*
 * File:   os.c
 * Author: Jared
 *
 * Created on 19 July 2013, 5:41 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "core/scheduler.h"
#include "os.h"

////////// Variables ///////////////////////////////////////////////////////////




application_t* foreground_app = NULL;

static task_t* draw_task;

void Draw();

////////// Methods /////////////////////////////////////////////////////////////

void InitializeOS() {
    // This task performs all drawing to the OLED
    draw_task = RegisterTask(Draw, DRAW_INTERVAL);
}

void SetForegroundApp(application_t* app) {
    if (foreground_app != NULL)
        foreground_app->isForeground = false;
    app->isForeground = true;

    //TODO: Maybe some sort of transition between screens?
}

// Called periodically
void Draw() {

    // Draw foreground app
    if (foreground_app != NULL) {
        foreground_app->draw();
    }

    // Draw status bar icons here
    // ...
}
