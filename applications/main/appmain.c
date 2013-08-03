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

#include <system.h>
#include "api/app.h"
#include "api/api.h"
#include "api/graphics/gfx.h"

// Sample 128x128 image
// 5:6:5 16-bit pixel format, RGB ordering
#include "tools/wolf.h"
//PROGMEM uint16* wolf_bytes = (PROGMEM uint16*)&wolf_image; 

const image_t wolf_image = {wolf_bytes, WOLF_WIDTH, WOLF_HEIGHT};

////////// App Definition //////////////////////////////////////////////////////

void appmain_Initialize();
void appmain_Process();
void appmain_Draw();

application_t appmain = APPLICATION("Main", appmain_Initialize, appmain_Process, appmain_Draw);
/*application_t appmain = {
    appmain_Initialize,
    appmain_Process,
    appmain_Draw,
};*/

////////// Variables ///////////////////////////////////////////////////////////

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
void appmain_Initialize() {
    appmain.state = asIdle;

}

// Called periodically when state==asRunning
void appmain_Process() {

}

// Called periodically when isForeground==true (30Hz)
void appmain_Draw() {
    //NOTE: Even though it is not enforced, it is recommended to only draw within the specified bounds

    //TODO: Provide some way to draw to the statusbar at the top of the display

	DrawImage(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT,wolf_image);


	//DrawString("Hello World", 8,8, RED);



}
