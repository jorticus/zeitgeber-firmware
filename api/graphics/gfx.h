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


// RGB (5:6:5) 16-bit format
typedef union {
    struct {
        unsigned r: 5;
        unsigned g: 6;
        unsigned b: 5;
    };
    uint16 val;
} color_s;

typedef uint16 color_t;

#define COLOR(R,G,B) (color_t)(((R*32/256)<<11) | ((G*32/256)<<5) | (B*32/256))

// Grayscale format
/*typedef union {
    uint8 val;
} color_t;*/

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 128

#define DISPLAY_SIZE (DISPLAY_WIDTH*DISPLAY_HEIGHT*sizeof(color_t))

//////////////////////////////////


typedef struct {
    color_t *pixels;
    int width;
    int height;
} image_t;


#define NO_FILL 16
#define NO_LINE 16

#define WHITE 1
#define BLACK 0

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
extern void DrawImage(int x, int y, int w, int h, image_t image);
//extern image_t OffsetImage(int x, int y, image_t image);

///// Fonts /////

// Draw a character using the current font
extern int DrawChar(char c, uint8 x, uint8 y, color_t color) ;

// Draw a variable-width string using the current font
extern int DrawString(const char* str, uint8 x, uint8 y, color_t color);

// Calculate the width in pixels of the provided string, including 1px char spacing
extern int StringWidth(const char* str);

#endif	/* GFX_H */

