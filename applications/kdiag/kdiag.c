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
    char s[20];
    

    DrawString("Kernel Info", 8,y, WHITE);
    y += 12;

    DrawString("CPU%", 60,y, WHITE);
    //DrawString("%CPU", 88,y, WHITE);
    y += 8;

    // NOTE: Starting at 1 to skip the Idle task
    for (i=1; i<num_tasks; i++) {
        task_t* task = &tasks[i];

        color_t color = (task->state == tsRun) ? WHITE : GRAY;
        
        DrawString(task->name, 8,y, color);
        
        //utoa(s, task->next_run, 10);
        utoa(s, task->cpu_ticks, 10);
        DrawString(s, 60,y, color);

        //utoa(s, task->cpu_usage, 10);
        //DrawString(s, 88,y, color);

        y += 8;
    }

    DrawString("Total", 8,y, WHITE);

    utoa(s, total_cpu_ticks, 10);
    DrawString(s, 60,y, WHITE);

    //utoa(s, 0, 10);
    //DrawString(s, 88,y, WHITE);


}
