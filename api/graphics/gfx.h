/* 
 * File:   gfx.h
 * Author: Jared
 *
 * Created on 19 July 2013, 5:41 PM
 *
 * Graphics library
 */

#ifndef GFX_H
#define	GFX_H

///// DISPLAY CONFIGURATION /////


// Unused within the graphics library, but provided for use elsewhere.
#define DISPLAY_BPP 16

typedef uint16 color_t;

// RGB (5:6:5) 16-bit format
typedef union {
    struct {
        unsigned r: 5;
        unsigned g: 6;
        unsigned b: 5;
    };
    color_t val;
} color_s;

// NOTE: Do not use the following macros for run-time color calculation, they haven't been optimised.

// Define a constant RGB color (0-255)
#define COLOR(R,G,B) (color_t)(((R*32/256)<<11) | ((G*32/256)<<5) | (B*32/256))

// Define a color using a 24-bit hex (WARNING: since colors are 16-bit, some resolution will be lost)
#define HEXCOLOR32(H) (color_t)( ((((H&0xFF0000)>>16)*32/256)<<11) | ((((H&0x00FF00)>>8)*32/256)<<5) | ((H&0x0000FF)*32/256) )

// Define a color using a 12-bit hex (NOTE: not all colors can be produced using this)
//TODO: This doesn't work for 0x888
#define HEXCOLOR(H) (color_t)( (H&0xF00)<<4 | (H&0x0F0)<<3 | (H&0x00F)<<1)

#include "api/graphics/font.h"
#include "api/graphics/imfont.h"
#include "colors.h"


#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128

//#define DISPLAY_SIZE (DISPLAY_WIDTH*DISPLAY_HEIGHT*sizeof(color_t))
#define DISPLAY_SIZE (DISPLAY_WIDTH*DISPLAY_HEIGHT)


//////////////////////////////////

typedef struct {
    __eds__ color_t *pixels;
    int width;
    int height;
} image_t;


#define NO_FILL 16
#define NO_LINE 16

//#define WHITE 1
//#define BLACK 0

//TODO: Rename and cleanup non-useful operations
typedef enum {
	// Standard Win32 Bit-Blit Operations
	BLACKNESS,		// dest = 0
	MERGECOPY,		// if (mask) dest = src		- Draw image over dest masked by mask
	MERGEPAINT,		// dest = dest | ~src
	NOTSRCCOPY,		// dest = ~src				- Draw inverted image
	NOTSRCERASE,	// dest = ~(dest | src)
	PATCOPY,		// dest = mask				- Display the mask (for debugging)
	PATINVERT,		// dest = dest ^ mask		- Invert the dest with the given mask
	PATPAINT,		// deat = dest | ~src | mask
	SRCAND,			// dest = dest & src
	SRCCOPY,		// dest = src				- Same as DrawImage
	SRCERASE,		// dest = ~dest & src
	SRCINVERT,		// dest = dest ^ src
	SRCPAINT,		// dest = dest | src
	WHITENESS,		// dest = 1

	// Experimental (Possibly Slow)
	ADD,			// dest = dest + src
	SUBTRACT,
	//ADDLIMIT,		// dest = dest + src (limited between 0-1)
	//SUBTRACTSRC,	// dest = dest - src
	//SUBTRACTDEST,	// dest = src - dest
	//MULTIPLY,		// dest = dest * src (normalized)
	BLEND,			// dest = dest*0.5 + src*0.5 (alpha blending)
} drawop_t;


extern drawop_t global_drawop;

///// Low Level /////

#include <system.h>

void SetPixel(uint8 x, uint8 y, color_t color);
void TogglePixel(uint8 x, uint8 y);
color_t GetPixel(uint8 x, uint8 y);

///// Display /////

// Copy the screen buffer to the display
extern void UpdateDisplay();

///// Screen Buffer /////

// Clear the internal screen buffer
extern void ClearImage();

///// Drawing /////

extern void DrawBox(uint8 x, uint8 y, uint8 w, uint8 h, color_t border, color_t fill);
extern void DrawRoundedBox(uint8 x, uint8 y, uint8 w, uint8 h, color_t border, color_t fill);
extern void DrawLine(int x0, int y0, int x1, int y1, color_t color);
extern void DrawImage(int x, int y, image_t image);
//extern image_t OffsetImage(int x, int y, image_t image);
void BitBlit(image_t* src, image_t* mask, uint xdest, uint ydest, uint width, uint height, uint xsrc, uint ysrc, drawop_t rop, bool invert);

///// Fonts /////

#include <api/graphics/font.h>

// Draw a character using the current font
extern int DrawChar(char c, uint8 x, uint8 y, color_t color) ;

// Draw a variable-width string using the current font
extern int DrawString(const char* str, uint8 x, uint8 y, color_t color);

// Calculate the width in pixels of the provided string, including 1px char spacing
extern int StringWidth(const char* str);

#endif	/* GFX_H */

