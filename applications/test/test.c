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
#include "api/graphics/gfx.h"
#include "util/util.h"
#include "core/systick.h"
#include "background/power_monitor.h"
#include "peripherals/adc.h"
#include "peripherals/rtc.h"

#include "gui/Wallpapers/wallpaper7.h"
#define wallpaper img_wallpaper7

// Sample 128x128 image
// 5:6:5 16-bit pixel format, RGB ordering
//#include "tools/wolf.h"
//const PROGMEM image_t wolf_image = {wolf_bytes, WOLF_WIDTH, WOLF_HEIGHT};

////////// App Definition //////////////////////////////////////////////////////

void apptest_Initialize();
void apptest_Process();
void apptest_Draw();

application_t apptest = APPLICATION("Test", apptest_Initialize, apptest_Process, apptest_Draw);

////////// Variables ///////////////////////////////////////////////////////////

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
void apptest_Initialize() {
    apptest.state = asIdle;

}

// Called periodically when state==asRunning
void apptest_Process() {

}

// Called periodically when isForeground==true (30Hz)
void apptest_Draw() {
    UINT32 i;
    UINT8 x = 8;
    UINT8 y = 8;
    char s[10];

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

    DrawImage(0,0,wallpaper);
    // BitBlit(&img_bat, NULL, i,40, 0,0, 0,0, ADD,1);


    //TODO: Reading two ADC samples next to each other produces invalid results
    // (eg. vbat reports 3600mV instead of 4200mV)

    utoa(s, systick, 10);
    x = 8;
    x = DrawString("systick: ", x,24,WHITE);
    x = DrawString(s,        x,24, WHITE);

    utoa(s, vdd, 10);
    x = 8;
    x = DrawString("VDD: ", x,38,WHITE);
    x = DrawString(s,        x,38, WHITE);
    x = DrawString("mV", x,38,WHITE);



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


    //VBAT = 503:an = ???V
    //VCAP = 541:an = 1.8V
    //VBG = 356:an = 1.2V
    //VREF = 1024:an = ???V

    // Draw the battery bar
    uint8 w = mLerp(0,100, 0,DISPLAY_WIDTH, battery_level);
    color_t c = WHITE;
    switch (power_status) {
        case pwBattery: {
            switch (battery_status) {
                case batFull: c = GREEN; break;
                case batNormal: c = NAVY; break;
                case batLow: c = RED; break;
                // No need to put batFlat or batNotConnected
                default: break;
            }
            break;
        }
        case pwCharged: c = GREEN; break;
        case pwCharging: c = ORANGE; break;
    }
    DrawBox(0,0, w,3, c,c);

    // Draw the battery status
    if (power_status == pwBattery) {
        utoa(s, battery_level, 10);
        x = DrawString(s,   6,5,WHITE);
        x = DrawString("%", x,5,WHITE);
    } else {
        DrawString(power_status_message[power_status], 6,5, WHITE);
    }

    //DrawString((_SESVD) ? "1" : "0", 8,80, WHITE);

    //            global_drawop = SUBTRACT;
    //
    //            uint8 w = mLerp(0,100, 4,DISPLAY_WIDTH-8, battery_level);
    //            DrawRoundedBox(4,4,w,10,SHADE(220),SHADE(128));


    SetFontSize(2);

    RtcTimeToStr(s);
    DrawString(s, 8,100,WHITE);
}