/*
 * File:   applications/imu/imu.c
 * Author: Jared
 *
 * Created on 14 February 2014, 1:39 PM
 *
 * IMU test application
 *
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "system.h"
#include "api/app.h"
#include "api/api.h"
#include "api/graphics/gfx.h"
#include "util/util.h"
#include "core/kernel.h"
#include "background/power_monitor.h"
#include "peripherals/adc.h"
#include "peripherals/rtc.h"

//#include "gui/Wallpapers/wallpaper7.h"
//#define wallpaper img_wallpaper7
//#include "gui/Wallpapers/gaben.h"
//#define wallpaper img_gaben
//#include "gui/Wallpapers/leaves.h"
//#define wallpaper img_leaves

// Sample 128x128 image
// 5:6:5 16-bit pixel format, RGB ordering
//#include "tools/wolf.h"
//const PROGMEM image_t wolf_image = {wolf_bytes, WOLF_WIDTH, WOLF_HEIGHT};

////////// App Definition //////////////////////////////////////////////////////

void appimu_Initialize();
void appimu_Process();
void appimu_Draw();

application_t appimu = APPLICATION("IMU", appimu_Initialize, appimu_Process, appimu_Draw);

////////// Variables ///////////////////////////////////////////////////////////

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
void appimu_Initialize() {
    appimu.state = asIdle;
}

// Called periodically when state==asRunning
void appimu_Process() {
    while (1) {
        Delay(1000);
    }
}

// Called periodically when isForeground==true (30Hz)
void appimu_Draw() {
    UINT32 i;
    UINT8 x = 8;
    UINT8 y = 8;
    char s[10];

    //DrawImage(0,0,wallpaper);
    ClearImage();

    SetFontSize(2);

    RtcTimeToStr(s);
    DrawString(s, 8,100,WHITE);

    //Sleep();
}
