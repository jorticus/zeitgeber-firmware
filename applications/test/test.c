/* 
 * File:   applications/main/appmain.c
 * Author: Jared
 *
 * Created on 5 July 2013, 12:48 PM
 *
 * Main test application
 *
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "system.h"
#include "api/app.h"
#include "api/api.h"
#include "api/clock.h"
#include "api/graphics/gfx.h"
#include "util/util.h"
#include "core/kernel.h"
#include "background/power_monitor.h"
#include "peripherals/adc.h"
#include "api/calendar.h"

#include "gui/Wallpapers/wallpaper7.h"
#define wallpaper img_wallpaper7
//#include "gui/Wallpapers/gaben.h"
//#define wallpaper img_gaben
//#include "gui/Wallpapers/leaves.h"
//#define wallpaper img_leaves

// Sample 128x128 image
// 5:6:5 16-bit pixel format, RGB ordering
//#include "tools/wolf.h"
//const PROGMEM image_t wolf_image = {wolf_bytes, WOLF_WIDTH, WOLF_HEIGHT};

////////// App Definition //////////////////////////////////////////////////////

static void Initialize();
static void Draw();

application_t apptest = {.name="Test", .init=Initialize, .draw=Draw};

////////// Variables ///////////////////////////////////////////////////////////
extern task_t* draw_task;
extern uint anext_task;

extern uint16 task_sp;
extern task_t* current_task;
extern uint16 stack_base;

extern bool usb_connected;

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
static void Initialize() {

}

static void DrawTestGradient() {
    UINT8 x = 8;
    UINT8 y = 8;

    for (y=0; y<128; y++) {
        color_s c;

        // Gray
        c.r = y >> 2;
        c.g = y >> 1;
        c.b = c.r;
        for (x=0; x<32; x++) {
            SetPixel(x,y, c.val);
        }

        // Red
        c.r = y >> 2;
        c.g = 0;
        c.b = 0;
        for (x=32; x<64; x++) {
            SetPixel(x,y, c.val);
        }

        // Green
        c.r = 0;
        c.g = y >> 1;
        c.b = 0;
        for (x=64; x<96; x++) {
            SetPixel(x,y, c.val);
        }

        // Blue
        c.r = 0;
        c.g = 0;
        c.b = y >> 2;
        for (x=96; x<128; x++) {
            SetPixel(x,y, c.val);
        }
    }
    return;
}


void TestEDS() {
    __eds__ color_t* c = wallpaper7_bytes;
    uint ix,iy;
    for (iy=0; iy<wallpaper.height; iy++) {
        for (ix=0; ix<wallpaper.width; ix++) {
            SetPixel(ix,iy,*c++);
        }
    }
}

// Called periodically when isForeground==true (30Hz)
static void Draw() {

    //DrawTestGradient();

    DrawImage(0,0,&wallpaper);
    //TestEDS();

}
