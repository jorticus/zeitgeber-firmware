/*
 * File:   os.c
 * Author: Jared
 *
 * Created on 19 July 2013, 5:41 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "api/graphics/gfx.h"
#include "core/scheduler.h"
#include "os.h"

////////// Variables ///////////////////////////////////////////////////////////




application_t* foreground_app = NULL;

static task_t* draw_task;

void Draw();

////////// Methods /////////////////////////////////////////////////////////////

void InitializeOS() {
    // This task performs all drawing to the OLED
    draw_task = RegisterTask("Draw", Draw, DRAW_INTERVAL);
	draw_task->state = tsRun;
}

void SetForegroundApp(application_t* app) {
    if (foreground_app != NULL)
        foreground_app->isForeground = false;
    app->isForeground = true;
	foreground_app = app;

	//TODO: Do we set the old app to tsIdle?? Or execute some callback?
	app->task->state = tsRun;

    //TODO: Maybe some sort of transition between screens?
}

// Called periodically
void Draw() {
	// Clear screen & set defaults
	DrawBox(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,SHADE(40),BLACK);
	SetFont(fonts.Stellaris);
	SetFontSize(1);

    // Draw foreground app
    if (foreground_app != NULL) {
        foreground_app->draw();
    }

    // Draw status bar icons here
    // ...

	// Finally update the display
	UpdateDisplay();
}
