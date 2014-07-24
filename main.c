/* 
 * File:   main.c
 * Author: Jared
 *
 * Created on 5 July 2013, 12:48 PM
 *
 * Zeitgebers are events that keep our circadian rhythms regulated.
 * An alarm clock is an example of an artificial zeitgeber
 *
 * Code is organised into the following layer model:
 * Hardware Layer       Hardware specific definitions (hardware.h)
 * Peripheral Layer     PIC peripherals; connects the driver layer to the hardware layer (peripherals/...)
 * Driver Layer         Drivers; provides ways of communicating with attached sensors/devices (drivers/...)
 * API Layer            API; to provide an easy to use interface of the drivers to the user-mode application (api/...)
 * Application Layer    User-mode applications (applications/...)
 *
 * In addition there is also the core/... directory, which contains
 * the system kernel and other system related code.
 * 
 * And finally, the main.c initializes all the peripherals and apis
 * (drivers are initialized through the appropriate api)
 * and is also in charge of running the kernel.
 *
 * Peripherals/drivers may define their own interrupts.
 *
 * User-mode applications should only need access to the API code, nothing else.
 *
 * ERRATA (xxxDAxxx) http://ww1.microchip.com/downloads/en/DeviceDoc/80000505g.pdf
 */

#include <stdlib.h>
#include <system.h>
#include <Rtcc.h>
#include "hardware.h"

// Core
#include "core/kernel.h"
#include "core/os.h"
#include "core/cpu.h"

// Peripherals
#include "peripherals/adc.h"
#include "peripherals/pwm.h"
#include "peripherals/gpio.h"
#include "drivers/usb/usb.h"

// API
#include "api/oled.h"
#include "api/clock.h"

// Background tasks
#include "background/comms.h"
#include "background/power_monitor.h"

// User-mode applications
#include "api/app.h"
#include "applications/clock/clock.h"
#include "applications/imu/imu.h"
#include "applications/test/test.h"
#include "applications/kdiag/kdiag.h"

#include "drivers/ssd1351.h"
#include "api/graphics/gfx.h"
#include "util/util.h"
#include "api/graphics/font.h"
#include "core/error.h"

//#include "gui/icons/bat.h"

//#include "tools/DSC09748.h"
//const image_t img = {DSC09748_bytes, DSC09748_WIDTH, DSC09748_HEIGHT};

//#include "tools/fluffy.h"
//const image_t img = {fluffy_bytes, FLUFFY_WIDTH,  FLUFFY_HEIGHT};

//#include <gui/statusbar.h>
//#include <gui/icons/battery_50.h>
//#include <gui/icons/bat.h>

//#include "tools/wolf.h"
//const image_t img = {wolf_bytes, WOLF_WIDTH,  WOLF_HEIGHT};

#ifndef HID_BOOTLOADER
    _CONFIG1(FWDTEN_OFF & FWPSA_PR128 & WDTPS_PS32 & WINDIS_OFF & ICS_PGx2 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
    _CONFIG2(POSCMOD_HS & IOL1WAY_ON & OSCIOFNC_OFF & FCKSM_CSDCMD & FNOSC_PRIPLL & PLL96MHZ_ON & PLLDIV_DIV8 & IESO_OFF) // For 32MHz OSC
    _CONFIG3(0xFFFF);
#endif

void Shutdown() {
    // Stop execution and completely shut down the processor to save power.

    //AD1CON1bits.ADON = 0;

    // Disable peripherals
    PMD1 = 0xFFFF;
    PMD2 = 0xFFFF;
    PMD3 = 0xFFFF;
    PMD4 = 0xFFFF;
    PMD5 = 0xFFFF;
    PMD6 = 0xFFFF;

    _LAT(OL_POWER) = 0;
    _LAT(OL_RESET) = 1;
    _LAT(BT_RESET) = 1;

    _LAT(LED1) = 0;
    _LAT(LED2) = 0;

    _LAT(VMOTOR) = 0;
    _LAT(PEIZO) = 0;

    RCONbits.SWDTEN = 0;

    Sleep(); // Permanent sleep
    while(1); // Trap

    //TODO: Could we wake back up upon USB connect?
}

void Initialize() {
    InitializeIO();
    InitializeOsc();

    //_LAT(LED1) = 1;
    //_LAT(LED2) = 1;

    // Peripherals
    //pwm_init();
    //gpio_init();
    adc_init();
    adc_enable();

    InitializeClock();
    InitializeKernel();
    InitializeComms();
    InitializeOled();
    InitializeOS();

    ClearImage();
    ScreenOn();
    DisplayBootScreen();

    // Enable watchdog
    RCONbits.SWDTEN = 1;

    _LAT(LED1) = 0;
}

int main() {
    KernelSetSP(); // Sets stack_base to the current stack address
    Initialize();

    RegisterUserApplication(&appclock);
    RegisterUserApplication(&appimu); //TODO: I2C pullups are too weak?
    RegisterUserApplication(&apptest);
    RegisterUserApplication(&appkdiag);

    ClrWdt();
    BootPrintln("Initializing apps:");
    InitializeApplications();

    ClrWdt();
    BootPrintln("Starting the kernel");
    SetForegroundApp(&appclock);
    //SetForegroundApp(&apptest);
    //SetForegroundApp(&appimu);

    ClrWdt();
    KernelStart();
    return 0;
}
