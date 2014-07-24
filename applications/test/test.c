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

//#include "gui/Wallpapers/wallpaper1.h"
//#define wallpaper img_wallpaper1
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

// Called periodically when isForeground==true (30Hz)
static void Draw() {
    UINT32 i;
    UINT8 x = 8;
    UINT8 y = 8;
    char s[10];

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



//	static uint i = 0;
    //NOTE: Even though it is not enforced, it is recommended to only draw within the specified bounds

    //TODO: Provide some way to draw to the statusbar at the top of the display

	//DrawImage(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,wolf_image);

	//DrawImage(0,0, 0,0, wallpaper);

	//BitBlit(&wolf_image, NULL, 32,32, 0,0, 0,0, MERGECOPY);


	//i++;
	//if (i++ == (DISPLAY_WIDTH - wolf_image.width)) i = 0;


	//DrawString("Hello World", 8,8, RED);


    //global_drawop = SRCCOPY;
    //SetFontSize(1);

    ClearImage();

    // BitBlit(&img_bat, NULL, i,40, 0,0, 0,0, ADD,1);


    //TODO: Reading two ADC samples next to each other produces invalid results
    // (eg. vbat reports 3600mV instead of 4200mV)

    utoa(s, systick, 10);
    x = 8;
    x = DrawString("systick: ", x,24,WHITE);
    x = DrawString(s,        x,24, WHITE);

    utoa(s, current_task->sp, 10);
    //utoa(s, task_sp, 10);
    //utoa(s, stack_base, 10);
    x = 8;
    x = DrawString("SP: ", x,38,WHITE);
    x = DrawString(s,        x,38, WHITE);

//    utoa(s, vdd, 10);
//    x = 8;
//    x = DrawString("VDD: ", x,38,WHITE);
//    x = DrawString(s,        x,38, WHITE);
//    x = DrawString("mV", x,38,WHITE);



    utoa(s, battery_voltage, 10);
    x = 8;
    x = DrawString("VBAT: ", x,52,WHITE);
    x = DrawString(s,        x,52, WHITE);
    x = DrawString("mV", x,52,WHITE);


    x = 8;
    x = DrawString(power_status_message[power_status], x,66, WHITE);
    x = DrawString(", ", x,66, WHITE);
    x = DrawString(battery_status_message[battery_status], x,66, WHITE);
    x = DrawString(", ", x,66, WHITE);
    utoa(s, bq25010_status, 10);
    DrawString(s,        x,66, WHITE);


    if (usb_connected) {
        DrawString("USB Connected", 8, 80, WHITE);
    }


    //VBAT = 503:an = ???V
    //VCAP = 541:an = 1.8V
    //VBG = 356:an = 1.2V
    //VREF = 1024:an = ???V

    //DrawString((_SESVD) ? "1" : "0", 8,80, WHITE);

    //            global_drawop = SUBTRACT;
    //
    //            uint8 w = mLerp(0,100, 4,DISPLAY_WIDTH-8, battery_level);
    //            DrawRoundedBox(4,4,w,10,SHADE(220),SHADE(128));


    SetFontSize(2);

    ClockTimeToStr(s);
    DrawString(s, 8,100,WHITE);

    //Sleep();
}
