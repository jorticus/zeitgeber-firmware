/*
 * File:   os.c
 * Author: Jared
 *
 * Created on 19 July 2013, 5:41 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <system.h>
#include <core/systick.h>
#include "api/graphics/gfx.h"
#include "core/scheduler.h"
#include "os.h"

////////// Variables ///////////////////////////////////////////////////////////

//#include <gui/Wallpapers/wallpaper1.h>
/*#include <gui/Wallpapers/wallpaper2.h>
#include <gui/Wallpapers/wallpaper3.h>
#include <gui/Wallpapers/wallpaper4.h>
#include <gui/Wallpapers/wallpaper5.h>
#include <gui/Wallpapers/wallpaper6.h>
#include <gui/Wallpapers/wallpaper7.h>
#include <gui/Wallpapers/wallpaper8.h>
#include <gui/Wallpapers/wallpaper9.h>*/
//const image_t wallpapers[] = {
//	{wallpaper1_bytes, WALLPAPER1_WIDTH, WALLPAPER1_HEIGHT},
	/*{wallpaper2_bytes, WALLPAPER2_WIDTH, WALLPAPER2_HEIGHT},
	{wallpaper3_bytes, WALLPAPER3_WIDTH, WALLPAPER3_HEIGHT},
	{wallpaper4_bytes, WALLPAPER4_WIDTH, WALLPAPER4_HEIGHT},
	{wallpaper5_bytes, WALLPAPER5_WIDTH, WALLPAPER5_HEIGHT},
	{wallpaper6_bytes, WALLPAPER6_WIDTH, WALLPAPER6_HEIGHT},
	{wallpaper7_bytes, WALLPAPER7_WIDTH, WALLPAPER7_HEIGHT},
	{wallpaper8_bytes, WALLPAPER8_WIDTH, WALLPAPER8_HEIGHT},
	{wallpaper9_bytes, WALLPAPER9_WIDTH, WALLPAPER9_HEIGHT},*/
//};

/*#include <gui/statusbar.h>
const image_t imgStatusBar = {statusbar_bytes, STATUSBAR_WIDTH, STATUSBAR_HEIGHT};

#include <gui/icons/battery_50.h>
const image_t imgBattery = {battery_50_bytes, BATTERY_50_WIDTH, BATTERY_50_HEIGHT};
#include <gui/icons/battery_mask.h>
const image_t imgBatteryMask = {battery_mask_bytes, BATTERY_MASK_WIDTH, BATTERY_MASK_HEIGHT};

#include <gui/timemask.h>
const image_t imgTimeMask = {timemask_bytes, TIMEMASK_WIDTH, TIMEMASK_HEIGHT};
#include <gui/timeshadow.h>
const image_t imgTimeShadow = {timeshadow_bytes, TIMESHADOW_WIDTH, TIMESHADOW_HEIGHT};

#include <gui/icons/bat.h>
const image_t imgBat = {bat_bytes, BAT_WIDTH, BAT_HEIGHT};

#include <gui/icons/mail.h>
#include <gui/icons/calendar.h>
#include <gui/icons/comment.h>
#include <gui/icons/computer.h>*/


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
/*	static int i=0;

	uint16 ticks;
	uint16 starttick = systick;
	char s[16];

	// Clear screen and draw wallpaper
	ClearImage();
	DrawImage(0,0,0,0, wallpapers[0]);

	// Defaults
	SetFont(fonts.Stellaris);
	SetFontSize(1);

    // Draw foreground app
    if (foreground_app != NULL) {
        foreground_app->draw();
    }

    // Draw status bar
    BitBlit(&imgStatusBar, NULL, 0,0, 0,0, 0,0, ADD,0);
	//BitBlit(&imgBattery, &imgBatteryMask, DISPLAY_WIDTH-imgBattery.width-4,1, 0,0, 0,0, MERGECOPY,0);
	BitBlit(&imgBat, NULL, DISPLAY_WIDTH-imgBat.width-4,0, 0,0, 0,0, ADD,1);

	BitBlit(&img_mail, NULL, 4,0, 0,0, 0,0, ADD,1);
	BitBlit(&img_calendar, NULL, 24,0, 0,0, 0,0, ADD,1);
	BitBlit(&img_comment, NULL, 24*2,0, 0,0, 0,0, ADD,1);
	BitBlit(&img_computer, NULL, 24*3,0, 0,0, 0,0, ADD,1);

	BitBlit(&imgTimeShadow, NULL, i,40, 0,0, 0,0, SUBTRACT,1);
	BitBlit(&imgTimeShadow, &imgTimeMask, i,40, 0,0, 0,0, MERGECOPY,0);

	i++;

	ticks=  systick - starttick;

	ultoa(ticks, s, 10);
	DrawString("Running", 4, DISPLAY_HEIGHT-16, RED);

	// Finally update the display
	UpdateDisplay();*/
}
