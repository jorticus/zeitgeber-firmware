/* 
 * File:   api/graphics/imfont.h
 * Author: Jared
 *
 * Created on 19 February 2014, 9:38 PM
 */

#ifndef IMFONT_H
#define	IMFONT_H

typedef struct {
    __eds__ uint8 *data;    // Raw image data
    const uint16 *offsets;   // Character glyph offsets
    const uint8 *widths;    // Character widths

    uint char_width;
    uint char_height;
} imfont_t;

extern const imfont_t* active_imfont;

void SetImFont(const imfont_t* font);

int MeasureImString(const char* str);
int DrawImChar(char c, uint8 x, uint8 y, color_t color);
int DrawImString(const char* str, uint8 x, uint8 y, color_t color);

#endif	/* IMFONT_H */

