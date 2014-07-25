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

static void Initialize();
static void Draw();

application_t appkdiag = {.name="K-Diag", .init=Initialize, .draw=Draw};

////////// Variables ///////////////////////////////////////////////////////////

extern uint num_tasks;
extern task_t tasks[];

////////// Code ////////////////////////////////////////////////////////////////

// Called when CPU initializes 
static void Initialize() {
    appkdiag.task->state = tsStop;
}

// Called periodically when isForeground==true (30Hz)
static void Draw() {
    uint i, x, y;
    char s[20];

    // Draw CPU utilization history graph
    i = cpu_tick_history_idx;
    uint lx=0, ly=0;
    for (x=0; x<CPU_TICK_HISTORY_LEN; x++) {

        uint value = cpu_tick_history[i] * 128 / 1000;
        //uint millivalue = cpu_tick_history[i] * 128 / 10;
        if (value > 128) value = 128;
        //if (millivalue > 128) millivalue = 128;

        //DrawLine(x,128, x,(128-millivalue), HEXCOLOR32(0x2E3449));
        DrawLine(x,128, x,(128-value), SKYBLUE);

        if (i++ == CPU_TICK_HISTORY_LEN)
            i -= CPU_TICK_HISTORY_LEN;
    }

    x = 0; y = 16;
    
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
