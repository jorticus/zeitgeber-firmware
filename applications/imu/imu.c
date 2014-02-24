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

#include "drivers/MMA7455.h"

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

extern uint draw_ticks;

extern bool i2c_aborted;

#define LINE_HEIGHT 8

#define ACCEL_LOG_SIZE DISPLAY_WIDTH
vector3c_t accel_log[ACCEL_LOG_SIZE];
vector3c_t accel_vec;
uint accel_log_index = 0;

color_t colors[3] = {RED, LIME, BLUE};

bool accel_initted = false;

extern bool displayOn;

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
void appimu_Initialize() {

    accel_init();
    accel_SetMode(accMeasure);

    uint i;
    for (i=0; i<ACCEL_LOG_SIZE; i++) {
        accel_log[i].x = 0;
        accel_log[i].y = 0;
        accel_log[i].z = 0;
    }
}

// Called periodically when state==asRunning
void appimu_Process() {
    while (1) {
        /*if (!accel_initted) {
            accel_init();
            accel_SetMode(accMeasure);
            accel_initted = true;
        }*/

        if (appimu.task->state == tsRun) {
            Delay(10);
            
            accel_vec = accel_ReadXYZ8();
            accel_log[accel_log_index] = accel_vec;

            accel_log_index++;
            if (accel_log_index == ACCEL_LOG_SIZE)
                accel_log_index = 0;

        } else {
            Delay(1000);
        }
    }
}

// Called periodically when isForeground==true (30Hz)
void appimu_Draw() {


    UINT32 i;
    UINT8 x = 8;
    UINT8 y = 8;
    char s[10];

    /*utoa(s, draw_ticks, 10);
    x = 8;
    x = DrawString("ticks: ", x,24,WHITE);
    x = DrawString(s,        x,24, WHITE);*/

    y = 8;

    DrawString("Accelerometer", 8,1*LINE_HEIGHT, WHITE);

    //vector3i_t acc = accel_ReadXYZ();
    vector3c_t acc = accel_vec;//accel_ReadXYZ8();

    itoa(s, acc.x, 10);
    x = 8;
    x = DrawString("X: ", x,2*LINE_HEIGHT, colors[0]);
    x = DrawString(s,     x,2*LINE_HEIGHT, colors[0]);

    itoa(s, acc.y, 10);
    x = 8;
    x = DrawString("Y: ", x,3*LINE_HEIGHT, colors[1]);
    x = DrawString(s,     x,3*LINE_HEIGHT, colors[1]);

    itoa(s, acc.z, 10);
    x = 8;
    x = DrawString("Z: ", x,4*LINE_HEIGHT, colors[2]);
    x = DrawString(s,     x,4*LINE_HEIGHT, colors[2]);


    DrawString("Magnetometer", 8,11*LINE_HEIGHT, WHITE);

    itoa(s, 0, 10);
    x = 8;
    x = DrawString("X: ", x,12*LINE_HEIGHT, colors[0]);
    x = DrawString(s,     x,12*LINE_HEIGHT, colors[0]);

    itoa(s, 0, 10);
    x = 8;
    x = DrawString("Y: ", x,13*LINE_HEIGHT, colors[1]);
    x = DrawString(s,     x,13*LINE_HEIGHT, colors[1]);

    itoa(s, 0, 10);
    x = 8;
    x = DrawString("Z: ", x,14*LINE_HEIGHT, colors[2]);
    x = DrawString(s,     x,14*LINE_HEIGHT, colors[2]);



    #define GRAPH_Y (DISPLAY_HEIGHT/2)

    DrawLine(0, GRAPH_Y, DISPLAY_WIDTH, GRAPH_Y, GRAY);

    global_drawop = ADD;

    uint j;
    uint8 lx, ly;

    for (j=0; j<3; j++) {
        lx = 0;
        ly = 0;

        for (x=0; x<ACCEL_LOG_SIZE; x++) {
            i = x + accel_log_index;
            if (i >= ACCEL_LOG_SIZE) i -= ACCEL_LOG_SIZE;

            uint8 *values = &accel_log[i];

            y = GRAPH_Y - values[j];
            if (y >= DISPLAY_HEIGHT-1) y = DISPLAY_HEIGHT-1;
            //SetPixel(x, y, colors[j]);

            if (x > 0)
                DrawLine(lx, ly, x, y, colors[j]);
            lx = x;
            ly = y;


        }
    }
    global_drawop = SRCCOPY;


    /*SetFontSize(2);

    RtcTimeToStr(s);
    DrawString(s, 8,100,WHITE);*/


    //Sleep();
}
