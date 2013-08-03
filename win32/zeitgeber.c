// Zeitgeber.X.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "zeitgeber.h"

#include <api\api.h>
#include <core\os.h>
#include <applications\main\appmain.h>

#define DLLEXPORT __declspec(dllexport)



extern bool ol_power;
extern uint8 ol_contrast;

// GFX Library Stuff
extern color_t screen[DISPLAY_SIZE];

// Power Monitor
extern charge_status_t charge_status;
extern bool battery;


typedef struct {
	bool ol_power;
	bool ol_reset;
	bool btn1;
	bool btn2;
	bool btn3;
	bool btn4;
	bool led1;
	bool led2;
	bool motor;
	bool peizo;
	bool vbus_sense;
	bool inta;
	bool intm;
	bool pw_stat1;
	bool pw_stat2;
	bool pw_ce;
	bool bt_reset;
	uint16 an_vbat;
	uint16 an_light;
} hardware_status_t;

typedef struct {
	uint8 x;

} scheduler_status_t;


////////// Callbacks //////////


#define DEF_CALLBACK(ret, name, ...) \
	typedef ret (*name##_t)(__VA_ARGS__); \
	name##_t name = NULL; \
	DLLEXPORT void set_##name(name##_t cb) { name = cb; }

#define CALL(cb) if (cb != NULL) cb


DEF_CALLBACK(void, onTest, int x);
DEF_CALLBACK(void, onDisplayUpdate, uint8* screen, uint w, uint h);
DEF_CALLBACK(void, onLedUpdate, bool led1, bool led2);
//DEF_CALLBACK(void, onStatusUpdate, hardware_status_t status);

//ZEITGEBER_API void (*onTest)(int x);

////////// Emulator Interface //////////

DLLEXPORT void zInitialize() {
	int i;

    // API
    InitializePowerMonitor(); // Battery charging/power supply monitor

    if (!InitializeOled()) {
        // Error initializing the OLED display
        // Since the display is not initialized,
        // we could revert to showing debug information through the USB port?
    }

    // Display loading message on OLED
    

    /*if (!InitializeUsb()) {
        // Error initializing USB
        // Display error message on screen
    }

    if (!InitializeSensors()) {
        // Error initializing sensors
        // Display error message on screen/usb status
    }

    if (!InitializeBluetooth()) {
        // Error initializing bluetooth
        // Display error message on screen/usb status
    }*/

	for (i=0; i<DISPLAY_SIZE; i++) {
		screen[i] = COLOR(0,0,0);
	}

	InitializeOS();

	RegisterUserApplication(&appmain);

	SetForegroundApp(&appmain);

	// Update OLED
	UpdateDisplay();
}

DLLEXPORT void zProcess() {
	ProcessTasks();
}

DLLEXPORT void zUpdateButton(uint8 idx, bool state) {
	switch (idx) {
	case 1: BTN1 = state; break;
	case 2: BTN2 = state; break;	
	case 3: BTN3 = state; break;
	case 4: BTN4 = state; break;
	}
}

DLLEXPORT void zGetHardwareStatus(hardware_status_t* status) {
	status->ol_power = OL_POWER;
	status->ol_reset = OL_RESET;
	status->btn1 = BTN1;
	status->btn2 = BTN2;
	status->btn3 = BTN3;
	status->btn4 = BTN4;
	status->led1 = LED1;
	status->led2 = LED2;
	status->motor = VMOTOR;
	status->peizo = PEIZO;
	status->intm = INTM;
	status->inta = INTA;
	status->pw_stat1 = PW_STAT1;
	status->pw_stat2 = PW_STAT2;
	status->pw_ce = PW_CE;
	status->an_vbat = 0; //TODO
	status->an_light = 0; //TODO
}

extern task_t tasks[MAX_TASKS];
extern uint num_tasks;
DLLEXPORT uint zGetNumTasks() {
	return num_tasks;
}
DLLEXPORT task_t* zGetTask(uint index) {
	if (index >= 0 && index < num_tasks) {
		return &tasks[index];
	}
	return NULL;
}

extern volatile uint systick;
DLLEXPORT void zSetSystick(uint tick) {
	systick = tick;
}

// See zeitgeber.c (Win32 DLL interface)
void ssd1351_UpdateScreen(uint8* buf, uint8 w, uint8 h) {
	onDisplayUpdate(buf, w, h);
}



