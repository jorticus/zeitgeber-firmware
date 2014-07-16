/*
 * File:   gfx.c
 * Author: Jared
 *
 * Created on 19 July 2013, 5:41 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "gfx.h"
#include <drivers\ssd1351.h>

////////// Variables ///////////////////////////////////////////////////////////

// Internal screen buffer
__eds__ color_t screen[DISPLAY_SIZE] __attribute__((space(eds),section(".gfx"),eds));
//color_t screen[DISPLAY_SIZE-1];

drawop_t global_drawop = SRCCOPY;

// Custom fonts
//#include "font.h"
//extern const font_t* active_font;
//extern unsigned int font_size;

// Uncomment to flip the screen vertically
//#define FLIP_DISPLAY

#pragma code


////////// Utilities ///////////////////////////////////////////////////////////

int abs(int v) {
    return (v > 0) ? v : -v;
}


////////// Device Dependant Functions //////////////////////////////////////////

void UpdateDisplay() {
    ssd1351_UpdateScreen(screen, DISPLAY_SIZE);
}

////////// Low Level Functions /////////////////////////////////////////////////


static INLINE uint16 threshold(uint16 color) {
	return (color > COLOR(0x7F,0x7F,0x7F)) ? 0xFFFF : 0x0000;
}

static INLINE void DrawOp(drawop_t drawop, __eds__ color_t* destbuf, __eds__ color_t* srcbuf, __eds__ color_t* maskbuf, bool invert) {
    color_t srccol = (invert) ? ~*srcbuf : *srcbuf;

    switch (drawop) {

        // Win32 Bit Blit Operations
        case BLACKNESS:		*destbuf = 0x0000; break;
        //case MERGECOPY:		*destbuf = *srcbuf & threshold(*maskbuf); break;
        case MERGECOPY:		if (threshold(*maskbuf)) *destbuf = srccol; break;
        case MERGEPAINT:	*destbuf = *destbuf | ~srccol; break;
        case NOTSRCCOPY:	*destbuf = ~srccol; break;
        case NOTSRCERASE:	*destbuf = ~(*destbuf | srccol); break;
        case PATCOPY:		*destbuf |= threshold(*maskbuf); break;
        case PATINVERT:		*destbuf = *destbuf ^ threshold(*maskbuf); break;
        case PATPAINT:		*destbuf = *destbuf | ~srccol | threshold(*maskbuf); break;
        case SRCAND:		*destbuf = *destbuf & *srcbuf; break;
        case SRCCOPY:		*destbuf = srccol; break;
        case SRCERASE:		*destbuf = ~*destbuf & srccol; break;
        case SRCINVERT:		*destbuf = *destbuf ^ srccol; break;
        case SRCPAINT:		*destbuf = *destbuf | srccol; break;
        case WHITENESS:		*destbuf = 0xFFFF; break;

        // Extra Operations
        //case ADD:			*destbuf += *srcbuf; break;
        //case SUBTRACTSRC:	*destbuf = *destbuf - *srcbuf; break;
        //case SUBTRACTDEST:	*destbuf = *srcbuf - *destbuf; break;

        // Advanced Operations (Slow/Experimental)
        /*case MULTIPLY: {
            //TODO: Optimise
            color_s src, dest;
            src.val = *srcbuf;
            dest.val = *destbuf;

            dest.r = (uint32)dest.r * (uint32)src.r >> 5;
            dest.g = (uint32)dest.g * (uint32)src.g >> 6;
            dest.b = (uint32)dest.b * (uint32)src.b >> 5;

            *destbuf = dest.val;
        } break;*/

        // Additive blending, limited
        /*case ADDLIMIT: {
            uint32 val = *destbuf + *srcbuf;
            if (val > 0xFFFF) val = 0xFFFF;
            *destbuf = val;
        } break;*/

        case ADD: {
            color_s src, dest;
            uint8 r,g,b;
            src.val = srccol;
            dest.val = *destbuf;

            r = dest.r + src.r;
            g = dest.g + src.g;
            b = dest.b + src.b;

            if (r > 0x1F) r = 0x1F;
            if (g > 0x3F) g = 0x3F;
            if (b > 0x1F) b = 0x1F;

            dest.r = r; dest.g = g; dest.b = b;
            *destbuf = dest.val;
        } break;

        case SUBTRACT: {
            color_s src, dest;
            int8 r,g,b;
            src.val = srccol;
            dest.val = *destbuf;

            r = dest.r;
            g = dest.g;
            b = dest.b;

            r -= src.r;
            g -= src.g;
            b -= src.b;

            if (r < 0) r = 0;
            if (g < 0) g = 0;
            if (b < 0) b = 0;

            dest.r = r; dest.g = g; dest.b = b;
            *destbuf = dest.val;
        } break;

        // 50% Alpha Blend
        case BLEND: {
            //TODO: Optimise
            color_s src, dest;
            src.val = srccol;
            dest.val = *destbuf;

            dest.r = dest.r/2 + src.r/2;
            dest.g = dest.g/2 + src.g/2;
            dest.b = dest.b/2 + src.b/2;

            *destbuf = dest.val;
        } break;
    }
}

void ClearImage() {
    int i;
    for (i = 0; i < DISPLAY_SIZE; i++) {
		color_t  c = {0x00};
        screen[i] = c;
    }
}

static INLINE uint byte_index(uint8 x, uint8 y) {
#ifdef FLIP_DISPLAY
    return (DISPLAY_WIDTH * DISPLAY_HEIGHT) - (x + (y * DISPLAY_WIDTH)) - 1;
#else
    return (x + (y * DISPLAY_WIDTH));
#endif
}

/*INLINE int bit_index(uint8 x) {
    return x % 8;
}*/

// Set a single pixel
void SetPixel(uint8 x, uint8 y, color_t color) {
    uint idx = byte_index(x,y);
	//screen[idx] = color;
    DrawOp(global_drawop, &screen[idx], &color, NULL, false);
}

// Invert the colour of a pixel (XOR)
void TogglePixel(uint8 x, uint8 y) {
    uint idx = byte_index(x,y);
	screen[idx] ^= 0xFFFF;
}

// Returns colour for the given pixel
color_t GetPixel(uint8 x, uint8 y) {
    //int idx = byte_index(x, y);
    //uint8 mask = 1 << bit_index(x);

    //return screen[idx] & mask ? 1 : 0;
	return 0;
}


////////// Basic Drawing Functions /////////////////////////////////////////////

// Draw a box

void DrawBox(uint8 x, uint8 y, uint8 w, uint8 h, color_t border, color_t fill) {
    int i, j;

    // Draw box fill
	//if (fill.val != NO_FILL) {
        for (j = y + 1; j < y + h - 1; j++) {
            for (i = x; i < x + w - 1; i++) {
                SetPixel(i, j, fill);
            }
        }
    //}

    // Draw box border
    //if (border.val != NO_LINE) {
        for (i = y; i < (y + h); i++) {
            SetPixel(x, i, border);
            SetPixel(x + w - 1, i, border);
        }
        for (i = x; i < (x + w); i++) {
            SetPixel(i, y, border);
            SetPixel(i, y + h - 1, border);
        }
    //}
}

// Draw a box with rounded corners (rounded by 1px)

void DrawRoundedBox(uint8 x, uint8 y, uint8 w, uint8 h, color_t border, color_t fill) {
    int i, j;

    // Draw box fill
    //if (fill != NO_FILL) {
        for (j = y + 1; j < y + h; j++) {
            for (i = x; i < x + w - 2; i++) {
                SetPixel(i, j, fill);
            }
        }
    //}

    // Draw box border
    //if (border != NO_LINE) {
        for (i = y + 1; i < (y + h); i++) {
            SetPixel(x - 1, i, border);
            SetPixel(x + w - 2, i, border);
        }
        for (i = x; i < (x + w - 2); i++) {
            SetPixel(i, y, border);
            SetPixel(i, y + h, border);
        }
    //}
}


// Draw a line between two points

void DrawLine(int x0, int y0, int x1, int y1, color_t color) {
    //Bresenham's Line Algorithm
    int dx, dy;
	int sx, sy, err;
	int e2;

    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    sx = (x0 < x1) ? 1 : -1;
    sy = (y0 < y1) ? 1 : -1;
    err = dx - dy;

    while (1) {
        SetPixel(x0, y0, color);

        if ((x0 == x1) && (y0 == y1)) return;
        e2 = 2 * err;
        if (e2 > -dy) {
            err = err - dy;
            x0 = x0 + sx;
        }
        if (e2 < dx) {
            err = err + dx;
            y0 = y0 + sy;
        }
    }
}

INLINE uint max(uint a, uint b) {
	return (a < b) ? b : a;
}
INLINE uint min(uint a, uint b) {
	return (a < b) ? a : b;
}




// Copy a source image to the screen using the specified drawing operation
void BitBlit(image_t* src, image_t* mask, uint xdest, uint ydest, uint width, uint height, uint xsrc, uint ysrc, drawop_t drawop, bool invert) {
    /*if (src != NULL) {
        uint x,y,w,h;
        uint destDelta, srcDelta;
        __eds__ color_t *srcbuf;
        __eds__ color_t *destbuf;
        __eds__ color_t *maskbuf;

        if (width == 0) width = src->width;
        if (height == 0) height = src->height;

        // If mask isn't defined, make it something valid
        if (mask == NULL) mask = src;

        srcbuf = &src->pixels[0];
        destbuf = &screen[0];
        maskbuf = &mask->pixels[0]; //TODO: Tradeoff between mask image size (1 bit) and performance (16 bit)


        // Calculate minimum clipping region
        w = min(src->width, width);
        h = min(src->height, height);

        // Offset the source image
        // Use if statement because this is less likely to be used (and can be optimised away)
        if (xsrc != 0 || ysrc != 0) {
                srcbuf += xsrc + (ysrc * src->width);
        }

        // Offset the dest buffer
        // No if statement because this is more likely to be used
        destbuf += xdest + (ydest * DISPLAY_WIDTH);

        // Precompute deltas
        destDelta = DISPLAY_WIDTH - w;
        srcDelta = src->width - w;

        // Copy pixels from the image directly to the screen buffer
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                DrawOp(drawop, destbuf, srcbuf, maskbuf, invert);
                destbuf++; srcbuf++; maskbuf++;
            }

            // Skip over pixels that lie outside the clipping region
            destbuf += destDelta;
            srcbuf += srcDelta;
        }
    }*/
}

