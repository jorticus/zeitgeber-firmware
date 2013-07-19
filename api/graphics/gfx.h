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

//#define DFMT_RGB_343
//#define DFMT_RGB_888
//#define DFMT_GRAY_8
//#define DFMT_BW

// RGB (3:4:3) format
typedef union {
    struct {
        unsigned r: 3;
        unsigned g: 4;
        unsigned b: 3;
    };
    uint8 val;
} color_t;

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

extern void Setpixel(uint8 x, uint8 y, color_t color);
extern void TogglePixel(uint8 x, uint8 y);
extern uint8 GetPixel(uint8 x, uint8 y);

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

