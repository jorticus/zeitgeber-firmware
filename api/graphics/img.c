/* 
 * File:   img.c
 * Author: Jared
 *
 * Created on 16 July 2014, 3:41 PM
 */

#include <system.h>
#include "api/graphics/gfx.h"

void DrawImage(int x, int y, image_t image) {
	//BitBlit(&image, NULL, x, y, w, h, 0, 0, SRCCOPY,0);

    __eds__ color_t* c = image.pixels;
    uint ix,iy;
    for (iy=0; iy<image.height; iy++) {
        for (ix=0; ix<image.width; ix++) {
            SetPixel(ix+x,iy+y,*c++);
        }
    }

   /* int idx = 0;
    int mask = 1;
	color_t chunk = image.pixels[0];

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
                chunk = image.pixels[idx].val;
            }

            // Clip pixels outside the specified region
            if ((ix < w) && (iy < h)) {
                SetPixel(ix, iy, pixel);
            }
        }

    }*/
}


