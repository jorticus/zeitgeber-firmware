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

// Sample 128x128 image
// 5:6:5 16-bit pixel format, RGB ordering
//#include "tools/wolf.h"
//__prog__ uint16* wolf_bytes = (__prog__ uint16*)&wolf_image; 

////////// App Definition //////////////////////////////////////////////////////

void appmain_Initialize();
void appmain_Process();

application_t appmain = APP(appmain_Initialize, appmain_Process); //{.init=appmain_Initialize, .process=appmain_Process};

////////// Variables ///////////////////////////////////////////////////////////

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes
void appmain_Initialize() {

}

// Called periodically. DO NOT BLOCK!
void appmain_Process() {

}
