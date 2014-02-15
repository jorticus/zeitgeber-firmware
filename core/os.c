/*
 * File:   os.c
 * Author: Jared
 *
 * Created on 19 July 2013, 5:41 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "system.h"
#include "core/kernel.h"
#include "api/graphics/gfx.h"
#include "os.h"
#include "hardware.h"

#include "drivers/ssd1351.h"
#include "background/comms.h"
#include "background/power_monitor.h"
#include "drivers/MMA7455.h"


////////// GUI Resources ///////////////////////////////////////////////////////

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

////////// Variables ///////////////////////////////////////////////////////////

bool displayOn = false;

application_t* foreground_app = NULL;

task_t* core_task;
task_t* draw_task;

uint draw_ticks;

////////// Prototypes //////////////////////////////////////////////////////////

void ProcessCore();
void Draw();
void DisplayBootScreen();
void CheckButtons();

////////// Methods /////////////////////////////////////////////////////////////

void InitializeOS() {
    ClrWdt();

    // High priority tasks that must be run all the time
    core_task = RegisterTask("Core", ProcessCore);
    core_task->state = tsRun;

    // Drawing, only needs to be run when screen is on
    draw_task = RegisterTask("Draw", Draw);
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

void ProcessCore() {
    while (1) {
        ProcessPowerMonitor();
        CheckButtons();
        Delay(PROCESS_CORE_INTERVAL);
    }
}

void CheckButtons() {
    UINT32 i;
/*#ifdef HID_BOOTLOADER
     // Execute bootloader if USB cable is plugged in and a button is pressed
    if (USB_VBUS_SENSE && (_PORT(BTN1) || _PORT(BTN4))) {
        _LAT(LED1) = 0; _LAT(LED2) = 0;
        for (i=0; i<100000; i++);
        while ( _PORT(BTN1) || _PORT(BTN4) );
        Reset();
    }
#endif*/

    // Wake up the display on any button press
    if (!displayOn) {
        if (_PORT(BTN1) || _PORT(BTN2) || _PORT(BTN3) || _PORT(BTN4)) {
            displayOn = true;
            ScreenOn();
            Delay(10);
        }
    }

    else {
        if (_PORT(BTN4)) {
            displayOn = false;
            ScreenOff();
            Delay(10);
        }
    }


    /*if (_PORT(BTN3)) {
        ssd1351_DisplayOff();
        WatchSleep();
    }*/
    // Can't use sleep yet until we can wake up from it.
}

void DisplayBootScreen() {
    byte y = 8;
    char s[10];
    byte x;
    uint32 i;

    ClrWdt();
    ClearImage();

    ClrWdt();
    DrawString("OLED Watch v1.0", 8, y, WHITE); y += 10;
    //DrawString("Booting...", 8, y, WHITE); y += 10;

    ClrWdt();
    UpdateDisplay();

    // Check the reset status
    // Software resets are the only type of reset that should occur normally
    if (RCON & UNEXPECTED_RESET) {
        //TODO: Draw an error icon or something

        if (RCONbits.BOR)
            // Likely cause: low battery voltage.
            DrawString("RST: Brown-out", 8,y,WHITE);
        else if (RCONbits.CM)
            DrawString("RST: Conf Mismatch", 8,y,WHITE);
        else if (RCONbits.IOPUWR)
            // Likely cause: pointer to function pointed to an invalid memory region, so PC encountered an invalid opcode
            DrawString("RST: Invalid Opcode", 8,y,WHITE);
        else if (RCONbits.EXTR)
            // Manual MCLR reset
            DrawString("RST: MCLR", 8,y,WHITE);
        else if (RCONbits.POR)
            // This will only happen if powering-up from a flat battery.
            DrawString("RST: Power-on", 8,y,WHITE);
        else if (RCONbits.WDTO)
            // This will happen if the code gets stuck in a loop somewhere
            DrawString("RST: Watchdog Timeout", 8,y,WHITE);
        else if (RCONbits.TRAPR)
            // This will happen if a trap interrupt is triggered
            DrawString("RST: Trap Error", 8,y,WHITE);
        //else if (RCONbits.SWR)
        //    DrawString("RST: Software", 8,y,WHITE);
        else {
            utoa(s, RCON & RCON_RESET, 16);
            x = 8;
            x = DrawString("RST: Unknown - ", x,y,WHITE);
            DrawString(s, x,y,WHITE);
        }
        y += 10;

        UpdateDisplay();

        // Optionally reset back into the bootloader,
        // to allow any problems to be fixed

    }
    RCON &= ~RCON_RESET;
    
    for (i=0; i<1000000; i++) { ClrWdt(); }
}

// Called periodically
void Draw() {
    while (1) {
        uint t1, t2;
        uint next_tick = systick + DRAW_INTERVAL;
        
        //_LAT(LED1) = 1;

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

        ClearImage();

        SetFontSize(1);
        SetFont(fonts.Stellaris);

        // Draw foreground app
        if (foreground_app != NULL)
            foreground_app->draw();

        t1 = systick;

        _LAT(LED1) = 1;
        UpdateDisplay();
        _LAT(LED1) = 0;

        t2 = systick;
        draw_ticks = (t2 >= t1) ? (t2 - t1) : 0;

        //Delay(DRAW_INTERVAL);
        //WaitUntil(next_tick);
        Delay(0);
    }
}



void WatchSleep() {
    ssd1351_DisplayOff();
    _LAT(BT_RESET) = 1;     // Turn off Bluetooth
    _LAT(VMOTOR) = 0;
    _LAT(PEIZO) = 0;
    _LAT(LED1) = 0;
    _LAT(LED2) = 0;
    _LAT(OL_POWER) = 0;     // Turn off OLED supply
    _LAT(OL_RESET) = 1;

    PMD1 = 0xFFFF;
    PMD2 = 0xFFFF;
    PMD3 = 0xFFFF;
    PMD4 = 0xFFFF;
    PMD5 = 0xFFFF;
    PMD6 = 0xFFFF;

    Sleep();
}

void ScreenOff() {
    // Disable drawing
    draw_task->state = tsStop;
    accel_Standby();

    ssd1351_DisplayOff();
    _LAT(LED1) = 0;
    _LAT(LED2) = 0;
}

void ScreenOn() {
    ssd1351_DisplayOn();

    accel_SetMode(accMeasure);
    draw_task->state = tsRun;
}
