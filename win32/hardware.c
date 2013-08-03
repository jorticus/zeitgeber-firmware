
#include <system.h>
#include "hardware.h"


// Stores the state of GPIO inputs/outputs for emulation

bool hw_ol_power = false;
bool hw_ol_reset = false;

bool hw_btn1 = false;
bool hw_btn2 = false;
bool hw_btn3 = false;
bool hw_btn4 = false;

bool hw_led1 = false;
bool hw_led2 = false;

bool hw_vmotor = false;
bool hw_peizo = false;

bool hw_vbus_sense = 0;

bool hw_intm = false;
bool hw_inta = false;

bool hw_pw_stat1 = false;
bool hw_pw_stat2 = false;
bool hw_pw_ce = false;

bool hw_bt_reset = false;

uint16 hw_an_vbat = 0;
uint16 hw_an_light = 0;

uint16 hw_dummy = 0;