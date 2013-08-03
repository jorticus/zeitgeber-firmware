// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ZEITGEBER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ZEITGEBER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ZEITGEBER_EXPORTS
#define ZEITGEBER_API __declspec(dllexport)
#else
#define ZEITGEBER_API __declspec(dllimport)
#endif

////////// Includes //////////

#include "system.h"
#include "api\graphics\gfx.h"
#include "api\power_monitor.h"
#include "hardware.h"

////////// Typedefs //////////

typedef void (*proc_t)(void);

////////// Callbacks //////////

//extern ZEITGEBER_API void (*onDisplayUpdate)(color_t* screen, uint w, uint h);
//extern ZEITGEBER_API void (*onLedUpdate)(bool led1, bool led2);

////////// Emulator Interface //////////

//extern ZEITGEBER_API void zInitialize();
//extern ZEITGEBER_API void zProcess();

////////// Low Level Interface //////////



// OLED Stuff
/*extern bool ol_power;
extern uint8 ol_contrast;

// GFX Library Stuff
extern color_t screen[DISPLAY_SIZE];

// Power Monitor
extern charge_status_t charge_status;
extern bool battery;

// GPIO
#include "hardware.h"
*/


