/*
 * File:   os.c
 * Author: Jared
 *
 * Created on 19 July 2013, 5:41 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "system.h"
#include "core/kernel.h"
#include "api/graphics/gfx.h"
#include "os.h"
#include "api/app.h"
#include "hardware.h"

#include "drivers/ssd1351.h"
#include "background/comms.h"
#include "background/power_monitor.h"
#include "drivers/MMA7455.h"
#include "util/util.h"
#include "peripherals/gpio.h"
#include "peripherals/cn.h"


////////// GUI Resources ///////////////////////////////////////////////////////

#include "gui/icons/usb.h"
#include "gui/icons/power.h"

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

bool displayOn = true;

task_t* core_task;
task_t* draw_task;

uint draw_ticks;

uint current_app = 0;

volatile bool lock_display = false;
volatile bool display_frame_ready = false;

////////// Prototypes //////////////////////////////////////////////////////////

void ProcessCore();
void DrawFrame();
void DrawLoop();
void DisplayBootScreen();
void CheckButtons();

void OnBTN1Change(bool btn_pressed);
void OnBTN2Change(bool btn_pressed);
void OnBTN3Change(bool btn_pressed);
void OnBTN4Change(bool btn_pressed);

////////// Methods /////////////////////////////////////////////////////////////

void InitializeOS() {
    ClrWdt();

    // High priority tasks that must be run all the time
    core_task = RegisterTask("Core", ProcessCore);
    core_task->state = tsRun;

    // Drawing, only needs to be run when screen is on
    draw_task = RegisterTask("Draw", DrawLoop);

    // Initialize button interrupts
    _CNIEn(BTN1_CN) = 1;
    _CNIEn(BTN2_CN) = 1;
    _CNIEn(BTN3_CN) = 1;
    _CNIEn(BTN4_CN) = 1;
    cn_register_cb(_CNIDX(BTN1_CN), _PINREF(BTN1), OnBTN1Change);
    cn_register_cb(_CNIDX(BTN2_CN), _PINREF(BTN2), OnBTN2Change);
    cn_register_cb(_CNIDX(BTN3_CN), _PINREF(BTN3), OnBTN3Change);
    cn_register_cb(_CNIDX(BTN4_CN), _PINREF(BTN4), OnBTN4Change);
}

void ScreenOff() {
    AppGlobalEvent(evtScreenOff, NULL);

    accel_SetMode(accStandby);

    // Disable drawing
    draw_task->state = tsStop;

    /*if (foreground_app != NULL) {
        foreground_app->task->state = tsStop;
    }*/

    ssd1351_DisplayOff();
    ssd1351_PowerOff();
    _LAT(LED1) = 0;
    _LAT(LED2) = 0;

    displayOn = false;
}

void ScreenOn() {
    // Draw a frame before fading in
    DrawFrame();
    //_LAT(OL_POWER) = 1;
    UpdateDisplay();

    ssd1351_PowerOn();
    ssd1351_DisplayOn();

    draw_task->state = tsRun;

    AppGlobalEvent(evtScreenOn, NULL);

    displayOn = true;
}


void ProcessCore() {
    while (1) {
        ProcessPowerMonitor();

        if (displayOn)
            Delay(CORE_PROCESS_INTERVAL);
        else
            Delay(CORE_STANDBY_INTERVAL);
    }
}

static void NextApp() {
    if (current_app <= app_count-2) {
        current_app++;
        SetForegroundApp(installed_apps[current_app]);
    }
}
static void PrevApp() {
    if (current_app > 0) {
        current_app--;
        SetForegroundApp(installed_apps[current_app]);
    }
}

static inline void OnBTNChange(bool btn_pressed, uint btn) {
    if (btn_pressed) {
        if (!displayOn) {
            ScreenOn();
        }
        else {
            switch (btn) {
                case 1:
                    break;
                case 2:
                    PrevApp();
                    break;
                case 3:
                    NextApp();
                    break;
                case 4:
                    ScreenOff();
                    break;
            }
        }

        AppForegroundEvent(evtBtnPress, btn);
    } else {
        AppForegroundEvent(evtBtnRelease, btn);
    }
}
void OnBTN1Change(bool btn_pressed) {
    OnBTNChange(btn_pressed, 1);
}
void OnBTN2Change(bool btn_pressed) {
    OnBTNChange(btn_pressed, 2);
}
void OnBTN3Change(bool btn_pressed) {
    OnBTNChange(btn_pressed, 3);
}
void OnBTN4Change(bool btn_pressed) {
    OnBTNChange(btn_pressed, 4);
}


void BootPrintln(const char* s) {
    static uint32 y = 8;
    DrawString(s, 8, y, WHITE);
    UpdateDisplay();
    y += 10;
}

void DisplayBootScreen() {
    byte y = 8;
    char s[10];
    byte x;
    uint32 i;

    ClrWdt();
    ClearImage();

    ClrWdt();
    BootPrintln("OLED Watch v1.0");
    //DrawString("Booting...", 8, y, WHITE); y += 10;

    
    
    for (i=0; i<1000000; i++) { ClrWdt(); }
}

void DrawFrame() {
    //_LAT(LED1) = 1;

    global_drawop = SRCCOPY;
    SetFontSize(1);
    SetFont(fonts.Stellaris);

    // Draw the wallpaper
    //DrawImage(0,0,wallpaper);
    ClearImage();

    // Draw foreground app
    if (foreground_app != NULL)
        foreground_app->draw();

    // Draw the battery bar
    uint8 w = mLerp(0,100, 0,DISPLAY_WIDTH, battery_level);
    color_t c = WHITE;
    switch (power_status) {
        case pwBattery: {
            switch (battery_status) {
                case batFull: c = SKYBLUE; break;
                case batNormal: c = SKYBLUE; break;
                case batLow: c = RED; break;
                // No need to put batFlat or batNotConnected
                default: break;
            }
            break;
        }
        case pwCharged: c = GREEN; break;
        case pwCharging: c = ORANGE; break;
    }
    // Extra padding at the top of the display to compensate for the bezel
    //DrawBox(0,0, DISPLAY_WIDTH,4, BLACK,BLACK);
    DrawBox(0,0, w,3, c,c);

    // Draw the battery icon
    if (power_status == pwBattery) {
        char s[8];
        sprintf(s, "%3d%%", battery_level);
        //utoa(s, battery_level, 10);
        //int x = DISPLAY_WIDTH - StringWidth(s) - 2;
        int x = DISPLAY_WIDTH - 30;
        DrawImString(s, x,5, WHITE);

    } else {
        if (usb_connected) {
            DrawImage(DISPLAY_WIDTH-USB_WIDTH-2,5, &img_usb);
        } else {
            DrawImage(DISPLAY_WIDTH-POWER_WIDTH-2,6, &img_power);
        }
    }

    // Framerate debug info
    if (displayOn)
    {
        char s[8];
        sprintf(s, "%d", draw_ticks);
        DrawString(s, 4,5, DARKGREEN);
    }
}

// Called periodically
void DrawLoop() {
    while (1) {
        uint t1, t2;
        uint next_tick = systick + DRAW_INTERVAL;

        t1 = systick;

        if (!lock_display) {
            display_frame_ready = false;

            DrawFrame();
        
            display_frame_ready = true;

            //_LAT(LED1) = 1;
            UpdateDisplay();
            //_LAT(LED1) = 0;
        }

        t2 = systick;
        draw_ticks = (t2 >= t1) ? (t2 - t1) : 0;

        Delay(DRAW_INTERVAL);
        //WaitUntil(next_tick);
        //Delay(0);
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
