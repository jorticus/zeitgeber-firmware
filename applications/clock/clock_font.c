/*
 * File:   applications/clock/clock_font.c
 * Author: Jared
 *
 * Created on 14 February 2014, 1:39 PM
 *
 * Custom clock font
 *
 */

#include "system.h"
#include "api/graphics/gfx.h"
#include "clock_font.h"

#include "gui/clock/c0_s1.h"
#include "gui/clock/c1_s1.h"
#include "gui/clock/c2_s1.h"
#include "gui/clock/c3_s1.h"
#include "gui/clock/c4_s1.h"
#include "gui/clock/c5_s1.h"
#include "gui/clock/c6_s1.h"
#include "gui/clock/c7_s1.h"
#include "gui/clock/c8_s1.h"
#include "gui/clock/c9_s1.h"
#include "gui/clock/colon_s1.h"
#include "gui/clock/am_s1.h"
#include "gui/clock/pm_s1.h"

//const image_t img_c2 = {c2_bytes, C2_WIDTH, C2_HEIGHT};

const image_t* digits[] = {
    &img_c0_s1, &img_c1_s1, &img_c2_s1, &img_c3_s1, &img_c4_s1,
    &img_c5_s1, &img_c6_s1, &img_c7_s1, &img_c8_s1, &img_c9_s1,
    &img_colon_s1, &img_am_s1, &img_pm_s1
};

int DrawClockInt(uint8 x, uint8 y, uint8 value, bool lead_zero) {
    uint8 tens = value/10;
    uint8 ones = value - (tens*10);

    if (lead_zero || tens)
        x = DrawClockDigit(x, y, tens);
    x = DrawClockDigit(x, y, ones);
    return x;
}

int DrawClockDigit(uint8 x, uint8 y, uint8 digit) {
    if (digit < 13) {
        const image_t* img = digits[digit];
        DrawImage(x,y, *img);
        x += img->width;
    }
    return x;
}

