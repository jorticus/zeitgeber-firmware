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
#include "api/gfx/gfx.h"

// Sample 128x128 image
// 5:6:5 16-bit pixel format, RGB ordering
//#include "tools/wolf.h"
//__prog__ uint16* wolf_bytes = (__prog__ uint16*)&wolf_image; 

////////// App Definition //////////////////////////////////////////////////////

void appmain_Initialize();
void appmain_Process();
void appmain_Draw();

//application_t appmain = APP(appmain_Initialize, appmain_Process, appmain_Draw);
application_t appmain = {
    .init       = appmain_Initialize,
    .process    = appmain_Process,
    .draw       = appmain_Draw,
};

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
}
