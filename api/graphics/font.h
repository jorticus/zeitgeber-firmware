/*
 * font.h
 *
 *  Created on: 2/05/2013
 *      Author: Jared
 *
 *  Allows you to change the font used to print strings.
 *  Usage:
 *    SetFont(fonts.<font name>);
 *
 */

#ifndef FONT_H_
#define FONT_H_

typedef struct {
    const unsigned char* data;
    unsigned char char_width;
    unsigned char char_height;
} font_t;


extern void SetFont(const font_t* font);
void SetFontSize(unsigned int size);

// Hard-coded fonts available for use
typedef struct {
    // Default Stellaris API Font
    const font_t* Stellaris;

    // The below fonts were obtained freely from <TODO: Insert URL>

    // Small fonts
    const font_t* PZim3x5;		// upper-case, plain text, 3px wide
    const font_t* f5x5;			// upper-case, square characters
    const font_t* BMPlain;		// square characters, 'e' and 's' look sharp like 'z'

    // Artsy
    const font_t* m38;			// very blocky
    const font_t* Bubble;
    const font_t* Haiku;		// doesnt look right
    const font_t* Blokus;		// broken? freehand style

    // Futuristic/Digital
    const font_t* SuperDigital;
    const font_t* Sloth;
    const font_t* SevenSeg;		// 7-seg display
    const font_t* Raumsond;		// good small font

    // Variable-width (not currently implemented, these fonts will show very bad kerning)
    const font_t* TamaMini02;	// square numbers, plain text
    const font_t* ZxPix;		// large print
    const font_t* BMSPA;		// upper-case, very large print
    const font_t* Aztech;		// squiggly
    const font_t* Formplex12;	// bold, blocky, '0' char needs tweaking
} fonts_t;
extern const fonts_t fonts;


#endif /* FONT_H_ */
