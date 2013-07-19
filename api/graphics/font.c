/*
 * fonts.c
 *
 *  Created on: 2/05/2013
 *      Author: Jared
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "font.h"
#include "gfx.h"

////////// Macros //////////////////////////////////////////////////////////////

#define FONTDEF(name, w, h) const font_t font_##name = {(const unsigned char*)fontdata_##name, w, h}
#define FONT(name) .##name = &font_##name

////////// Font Definitions ////////////////////////////////////////////////////

// Default Stellaris API font
#include "fonts\stellaris_font.h"

// Small fonts
#include "fonts\pzim3x5_font.h" // upper-case, plain text, 3px wide
#include "fonts\5x5_font.h" 		// upper-case, square characters
#include "fonts\BMplain_font.h"  // square characters, 'e' and 's' look sharp like 'z'

// Artsy
#include "fonts\m38_font.h" 	//very blocky
#include "fonts\bubblesstandard_font.h"
#include "fonts\haiku_font.h" 	//doesnt look right
#include "fonts\Blokus_font.h" 	//broken? freehand style

// Futuristic
#include "fonts\SUPERDIG_font.h"
#include "fonts\sloth_font.h"
#include "fonts\7linedigital_font.h" //7-seg display
#include "fonts\Raumsond_font.h" //good small font

// Variable-width
// NOTE: Variable width characters are not currently implemented. These fonts will have bad kerning
#include "fonts\tama_mini02_font.h" // square numbers, plain text
#include "fonts\zxpix_font.h" // large print
#include "fonts\BMSPA_font.h" // upper-case, very large print
#include "fonts\aztech_font.h" // squiggly
#include "fonts\formplex12_font.h" // bold, blocky, '0' needs tweaking

////////// Font Table //////////////////////////////////////////////////////////

const fonts_t fonts = {
    .Stellaris = &font_Stellaris,
    .PZim3x5 = &font_PZim3x5,
    .f5x5 = &font_f5x5,
    .BMPlain = &font_BMPlain,
    .m38 = &font_m38,
    .Bubble = &font_Bubble,
    .Haiku = &font_Haiku,
    .Blokus = &font_Blokus,
    .SuperDigital = &font_SuperDigital,
    .Sloth = &font_Sloth,
    .SevenSeg = &font_SevenSeg,
    .Raumsond = &font_Raumsond,
    .TamaMini02 = &font_TamaMini02,
    .ZxPix = &font_ZxPix,
    .BMSPA = &font_BMSPA,
    .Aztech = &font_Aztech,
    .Formplex12 = &font_Formplex12,
};


////////// Globals /////////////////////////////////////////////////////////////

const font_t* active_font = &font_Stellaris;
unsigned int font_size = 1;

////////// Functions ///////////////////////////////////////////////////////////

void SetFont(const font_t* font) {
	active_font = font;
}

void SetFontSize(unsigned int size) {
    font_size = size;
}

////////// Drawing /////////////////////////////////////////////////////////////

static int CharIndex(const font_t* font, char c) {
    // Convert the character to an index
    c = c & 0x7F;
    if (c < ' ') {
        c = 0;
    } else {
        c -= ' ';
    }
    return c * font->char_width;
}

static int CharWidth(const font_t* font, char c) {
    // Dynamically determine character width
    int i;
    int width = 0;
    const uint8* chr = &font->data[CharIndex(font, c)];
    for (i = 0; i < font->char_width; i++) {
        if (chr[i]) width++;
    }
    if (width == 0) width = 3; // ' ' char
    return width;
}

int DrawChar(char c, uint8 x, uint8 y, color_t color) {
    int i, j;

    // active_font->data is a pointer to a multidimensional array of [96][char_width]
    // which is really just a 1D array of size 96*char_width.
    int idx = CharIndex(active_font, c);
    const uint8* chr = &active_font->data[idx];

    int width = CharWidth(active_font, c);

    // Draw pixels
    if (font_size == 1) { // For performance, avoid scaling if size==1
        for (j = 0; j < width; j++) {
            for (i = 0; i < active_font->char_height; i++) {

                if (chr[j] & (1 << i)) {
                    SetPixel(x + j, y + i, color);
                }
            }
        }
    } else {
        for (j = 0; j < width * font_size; j++) {
            for (i = 0; i < active_font->char_height * font_size; i++) {

                if (chr[j / font_size] & (1 << (i / font_size))) {
                    SetPixel(x + j, y + i, color);
                }
            }
        }
    }

    return width;
}

int DrawString(const char* str, uint8 x, uint8 y, color_t color) {
    while (*str) {
        uint8 cw = DrawChar(*str++, x, y, color);
        x += (cw + 1) * font_size;
    }
    return x;
}

int StringWidth(const char* str) {
    int width = 0;
    while (*str) {
        char c = *str++;
        int idx = CharIndex(active_font, c);
        int cw = CharWidth(active_font, idx);
        width += (cw + 1) * font_size;
    }
}
