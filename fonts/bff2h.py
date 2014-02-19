
from bffloader import BffFont

# BFF_FILE = "Segoe UI.bff"
# OUTPUT_H_FILE = "SegoeUI.h"
# FONT_NAME = "segoe_ui"

BFF_FILE = "Titillium Web.bff"
OUTPUT_H_FILE = "TitilliumWeb.h"
FONT_NAME = "titillium_web"

FONT_END = ord('~')

font = BffFont()
font.load(BFF_FILE)

if font.base != ord(' '):
    raise ValueError("Font base must start at 32 (space character)")

font.image = font.image.convert('L')


with open(OUTPUT_H_FILE, 'w') as f:
    offsets = []
    offset = 0

    f.write("uint8 __eds__ {fontname}_bytes[] __attribute__((space(prog))) = {{\n".format(fontname=FONT_NAME))
    for c in range(font.base, FONT_END+1):
        glyph, width = font.get_glyph(chr(c))

        offsets.append(offset)
        f.write("    // '{char}'\n".format(char=chr(c)))
        for y in range(font.cellHeight):
            f.write("    ")
            for x in range(width):
                px = glyph.getpixel((x, y)) * (2**5) / (2**8)
                f.write("0x%.2x," % px)
                offset += 1
            f.write("\n")
        f.write("\n")

    f.write("};\n\n")

    f.write("const uint16 {fontname}_offsets[] = {{\n".format(fontname=FONT_NAME))
    f.write("    ")
    f.write(", ".join([str(w) for w in offsets]))
    f.write("\n};\n\n")

    f.write("const uint8 {fontname}_widths[] = {{\n".format(fontname=FONT_NAME))
    f.write("    ")
    f.write(", ".join([str(w) for w in font.widths[font.base:]]))
    f.write("\n};\n\n")

    f.write("""\
imfont_t font_{fontname} = {{
    {fontname}_bytes,
    {fontname}_offsets,
    {fontname}_widths,
    {cellwidth}, {cellheight}
}};""".format(fontname=FONT_NAME, cellwidth=font.cellWidth, cellheight=font.cellHeight))
