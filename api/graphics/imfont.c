/*
 * File:   api/graphics/imfont.c
 * Author: Jared
 *
 * Created on 19 February 2014, 9:38 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include "system.h"
#include "gfx.h"
#include "imfont.h"

////////// Font Definitions ////////////////////////////////////////////////////

//#include "fonts/SegoeUI.h"
#include "fonts/TitilliumWeb.h"

#define FONT_BASE ' '

////////// Globals /////////////////////////////////////////////////////////////

//const imfont_t* active_imfont = &font_segoe_ui;
const imfont_t* active_imfont = &font_titillium_web;

////////// Functions ///////////////////////////////////////////////////////////

void SetImFont(const imfont_t* font) {
	active_imfont = font;
}

////////// Drawing /////////////////////////////////////////////////////////////

int MeasureImString(const char* str) {
    uint w = 0;
    while (*str) {
        char c = *str++;
        c = (c < ' ') ? 0 : c - ' ';
        w += active_imfont->widths[c];
    }
    return w;
}

int DrawImChar(char c, uint8 x, uint8 y, color_t color) {
    if (c < ' ')
        c = 0;
    else
        c -= ' ';

    uint16 offset = active_imfont->offsets[c];
    uint8 __eds__ *glyph = &active_imfont->data[offset];
    uint8 width = active_imfont->widths[c];
    uint8 height = active_imfont->char_height;

    uint i, j;
    for (j=0; j<height; j++) {
        for (i=0; i<width; i++) {
            if (*glyph) {
                color_s c;
                if (color == WHITE) {
                    c.r = *glyph;
                    c.g = *glyph << 1;
                    c.b = *glyph;
                }
                else {
                    color_s cin;
                    cin.val = color;

                    //TODO: Optimize
                    uint16 r = *glyph;
                    uint16 g = *glyph << 1;
                    uint16 b = *glyph;
                    c.r = (r * cin.r) >> 5;
                    c.g = (g * cin.g) >> 6;
                    c.b = (b * cin.b) >> 5;

                }

                SetPixel(x+i,y, c.val);
            }
            glyph++;
        }
        y++;
    }

    return width;
}

int DrawImString(const char* str, uint8 x, uint8 y, color_t color) {
    while (*str) {
        uint8 cw = DrawImChar(*str++, x, y, color);
        x += cw;
    }
    return x;
}