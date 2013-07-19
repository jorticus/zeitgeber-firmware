/*
 * File:   gfx.c
 * Author: Jared
 *
 * Created on 19 July 2013, 5:41 PM
 */

////////// Includes ////////////////////////////////////////////////////////////

#include <system.h>
#include "gfx.h"

////////// Variables ///////////////////////////////////////////////////////////

// Internal screen buffer
static color_t screen[DISPLAY_SIZE];

// Custom fonts
//#include "font.h"
//extern const font_t* active_font;
//extern unsigned int font_size;


////////// Utilities ///////////////////////////////////////////////////////////

int abs(int v) {
    return (v > 0) ? v : -v;
}


////////// Device Dependant Functions //////////////////////////////////////////

void UpdateDisplay() {
    //TODO: Copy screen buffer to OLED display
    // or are there more efficient ways of updating the display? (by region?)
}

////////// Low Level Functions /////////////////////////////////////////////////

void ClearImage() {
    int i;
    for (i = 0; i < IMAGE_SIZE; i++) {
        screen[i] = 0x00;
    }
}

/*__inline__ int byte_index(uint8 x, uint8 y) {
    return (x >> 3) + (y * BYTES_PER_LINE);
}

__inline__ int bit_index(uint8 x) {
    return x % 8;
}*/

// Set a single pixel to be black (0) or white (1)

void SetPixel(uint8 x, uint8 y, color_t color) {
    int idx = byte_index(x, y);
    uint8 mask = 1 << bit_index(x);

    // Clear bit
   /* screen[idx] &= ~mask;

    // Set bit if value is true
    if (color.val)
        screen[idx] |= mask;*/
}

// Toggle a pixel between white and black

void TogglePixel(uint8 x, uint8 y) {
    int idx = byte_index(x, y);
    uint8 mask = 1 << bit_index(x);

    screen[idx] ^= mask;
}

// Returns 0 (black) or 1 (white) for the given pixel

uint8 GetPixel(uint8 x, uint8 y) {
    int idx = byte_index(x, y);
    uint8 mask = 1 << bit_index(x);

    return screen[idx] & mask ? 1 : 0;
}


////////// Basic Drawing Functions /////////////////////////////////////////////

// Draw a box

void DrawBox(uint8 x, uint8 y, uint8 w, uint8 h, color_t border, color_t fill) {
    int i, j;

    // Draw box fill
    if (fill != NO_FILL) {
        for (j = y + 1; j < y + h - 1; j++) {
            for (i = x; i < x + w - 1; i++) {
                SetPixel(i, j, fill);
            }
        }
    }

    // Draw box border
    if (border != NO_LINE) {
        for (i = y; i < (y + h); i++) {
            SetPixel(x, i, border);
            SetPixel(x + w - 1, i, border);
        }
        for (i = x; i < (x + w); i++) {
            SetPixel(i, y, border);
            SetPixel(i, y + h - 1, border);
        }
    }
}

// Draw a box with rounded corners (rounded by 1px)

void DrawRoundedBox(uint8 x, uint8 y, uint8 w, uint8 h, color_t border, color_t fill) {
    int i, j;

    // Draw box fill
    if (fill != NO_FILL) {
        for (j = y + 1; j < y + h; j++) {
            for (i = x; i < x + w - 2; i++) {
                SetPixel(i, j, fill);
            }
        }
    }

    // Draw box border
    if (border != NO_LINE) {
        for (i = y + 1; i < (y + h); i++) {
            SetPixel(x - 1, i, border);
            SetPixel(x + w - 2, i, border);
        }
        for (i = x; i < (x + w - 2); i++) {
            SetPixel(i, y, border);
            SetPixel(i, y + h, border);
        }
    }
}


// Draw a line between two points

void DrawLine(int x0, int y0, int x1, int y1, color_t color) {
    //Bresenham's Line Algorithm

    int dx, dy;
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);

    int sx, sy, err;

    sx = (x0 < x1) ? 1 : -1;
    sy = (y0 < y1) ? 1 : -1;
    err = dx - dy;

    int e2;

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

void DrawImage(int x, int y, int w, int h, image_t image) {
    int idx = 0;
    int mask = 1;
    uint8 chunk = image.pixels[0];

    // Precalculate x,y position for performance
    int iw = x + image.width;
    int ih = y + image.height;
    w += x;
    h += y;

    int ix, iy;
    for (iy = y; iy < ih; iy++) {
        for (ix = x; ix < iw; ix++) {
            // Retrieve the current pixel
            uint8 pixel = chunk & mask;

            // Go to the next pixel in the image
            // (pixels are grouped into 8 pixels per byte)
            mask <<= 1;
            if (mask == (1 << 8)) {
                mask = 1;
                idx++;
                chunk = image.pixels[idx];
            }

            // Clip pixels outside the specified region
            if ((ix < w) && (iy < h)) {
                SetPixel(ix, iy, pixel);
            }
        }

    }
}

// Return the image offset by some amount
// IMPORTANT: x must be a multiple of 8 (0,8,16,...)

image_t OffsetImage(int x, int y, image_t image) {
    x >>= 8;

    int offset = x + (y * image.width);

    image_t new_image = {&image.pixels[offset], image.width - x, image.height - y};

    return new_image;
}
