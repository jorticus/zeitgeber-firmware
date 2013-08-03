#ifndef COLORS_H
#define COLORS_H

/*enum colors {
	AliceBlue = HEXCOLOR(0xF0F8FF),
	AntiqueWhite = HEXCOLOR(0xFAEBD7),
	Aqua = HEXCOLOR(0x00FFFF),
	Aquamarine = HEXCOLOR(0x7FFFD4),
	Azure = HEXCOLOR(0xF0FFFF),
	Beige = HEXCOLOR(0xF5F5DC),
	Bisque = HEXCOLOR(0xFFE4C4),
	Black = HEXCOLOR(0x000000),
	BlanchedAlmond = HEXCOLOR(0xFFEBCD),
	Blue = HEXCOLOR(0x0000FF),
	BlueViolet = HEXCOLOR(0x8A2BE2),

};*/

// Standard Web Colours
enum colors {
	AQUA	= HEXCOLOR(0x0FF),
	BLACK	= HEXCOLOR(0x000),
	BLUE	= HEXCOLOR(0x00F),
	FUCHSIA	= HEXCOLOR(0xF0F),
	GRAY	= HEXCOLOR(0x888),
	GREEN	= HEXCOLOR(0x080),
	LIME	= HEXCOLOR(0x0F0),
	MAROON	= HEXCOLOR(0x800),
	NAVY	= HEXCOLOR(0x008),
	OLIVE	= HEXCOLOR(0x880),
	ORANGE	= HEXCOLOR(0xFA0),
	PURPLE	= HEXCOLOR(0x808),
	RED		= HEXCOLOR(0xF00),
	SILVER	= HEXCOLOR(0xCCC),
	TEAL	= HEXCOLOR(0x088),
	WHITE	= HEXCOLOR(0xFFF),
	YELLOW	= HEXCOLOR(0xFF0),
};

// Generate a shade of gray (where val is 0-255)
#define SHADE(val) COLOR(val,val,val)

// Lighten the specified color (0=original color, 100=white)
//#define LIGHTEN(color, val)

// Darken the specified color (0=original color, 100=black)
//#define DARKEN(color, val)

#endif
