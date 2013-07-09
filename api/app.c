/*
 * File:   app.c
 * Author: Jared
 *
 * Created on 5 July 2013, 4:07 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "app.h"

////////// Variables ///////////////////////////////////////////////////////////

#define MAX_APPLICATIONS 10

application_t* installed_apps[MAX_APPLICATIONS];
uint app_count = 0;

//TODO: Find a way of organising apps on the OLED,
// but also allowing them to run in the background.

////////// Methods /////////////////////////////////////////////////////////////

void RegisterUserApplication(application_t* app) {
    installed_apps[app_count++] = app;
}
