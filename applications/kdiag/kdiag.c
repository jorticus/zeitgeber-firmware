/*
 * File:   applications/kdiag/kdiag.c
 * Author: Jared
 *
 * Created on 17 February 2104, 1:58 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "system.h"
#include "api/app.h"
#include "api/graphics/gfx.h"

////////// App Definition //////////////////////////////////////////////////////

void appkdiag_Initialize();
void appkdiag_Process();
void appkdiag_Draw();

application_t appkdiag = APPLICATION("K-Diag", appkdiag_Initialize, appkdiag_Process, appkdiag_Draw);

////////// Variables ///////////////////////////////////////////////////////////

extern uint num_tasks;
extern task_t tasks[];

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
void appkdiag_Initialize() {
    appkdiag.task->state = tsStop;
}

// Called periodically when state==asRunning
void appkdiag_Process() {
    while (1) {
        Delay(1000);
    }
}

// Called periodically when isForeground==true (30Hz)
void appkdiag_Draw() {
    uint i;
    uint x=0;
    uint y=16;
    

    DrawString("Kernel Diagnostics", 8,y, WHITE);
    y += 16;
    
    for (i=0; i<num_tasks; i++) {
        task_t* task = &tasks[i];
        
        
        DrawString(task->name, 8,y, (task->state == tsRun) ? WHITE : GRAY);
        y += 8;
    }



}
