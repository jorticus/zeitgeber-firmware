
import sys
import os.path
from PIL import Image

IMG_FILENAME = 'gaben.jpg'
SIZE = (128,128)

SAVE_OUTPUT_IMAGE = False


if len(sys.argv) >= 2:
    IMG_FILENAME = ' '.join(sys.argv[1:])

(IMG_PATH, IMG_FNAME) = os.path.split(IMG_FILENAME)
IMG_NAME = os.path.splitext(IMG_FNAME)[0]
H_FILENAME = os.path.join(IMG_PATH, IMG_NAME + '.h')

DISP_WIDTH = SIZE[0]
DISP_HEIGHT = SIZE[1]

########## Resize/crop ##########
im = Image.open(IMG_FILENAME)

im_width = im.size[0]
im_height = im.size[1]
im_ratio = float(im_width) / float(im_height)

#print im_ratio

# Portrait
if 1.0 > im_ratio:
    im_height = int(DISP_HEIGHT/im_ratio)
    im = im.resize((DISP_WIDTH, im_height), Image.ANTIALIAS)
    im = im.crop((0, im_height/2 - DISP_HEIGHT/2, DISP_WIDTH, im_height/2 + DISP_HEIGHT/2))

# Landscape
elif 1.0 < im_ratio:
    im_width = int(DISP_WIDTH*im_ratio)
    im = im.resize((im_width, DISP_HEIGHT), Image.ANTIALIAS)
    im = im.crop((im_width/2 - DISP_WIDTH/2, 0, im_width/2 + DISP_WIDTH/2, DISP_HEIGHT))

# Square
else:
    im = im.resize((DISP_WIDTH, DISP_HEIGHT), Image.ANTIALIAS)


if SAVE_OUTPUT_IMAGE:
    im.save('out.png')

########## Extract Raw Pixels ##########

pixels = []
for y in range(DISP_HEIGHT):
    for x in range(DISP_WIDTH):
        pixels.append(im.getpixel((x,y)))

########## Pack Pixels ##########

# Assuming RGB layout

# 262K color (6:6:6) format (18 bits, 3 bytes per pixel)
# R5 R4 R3 R2 R1 R0, G5 G4 G3 G2 G1 G0, B5 B4 B3 B2 B1

# pixels = ["0x%.2x,0x%.2x,0x%.2x" % (
#     p[0]*64/256,
#     p[1]*64/256,
#     p[2]*64/256
# ) for p in pixels]
# dataformat = 'const uint8 __attribute__((space(prog)))'
# byte_multiplier = 3

# 65K color (5:6:5) format (16 bits, 2 bytes per pixel)
# R4 R3 R2 R1 R0 G5 G4 G3 G2 G1 G0 B4 B3 B2 B1 B0

pixels = ["0x%.4x" % (
    (p[0]*32/256) << 11 | (p[1]*64/256) << 5 | (p[2]*32/256)
) for p in pixels]
#dataformat = 'const uint16 __attribute__((space(prog)))'
dataformat = 'uint16 PROGMEM'
byte_multiplier = 2

# 256 color (3:3:2) format (8 bits, 1 byte per pixel)
# NOTE: Not directly supported by the SD1351 driver!
# Have to implement additional code to expand the bytes to one of the above formats (probably 6:6:6)

# pixels = ["0x%.2x" % (
#     (p[0]*8/256) << 5 | (p[1]*8/256) << 2 | (p[2]*4/256)
# ) for p in pixels]
# dataformat = 'const uint8 __attribute__((space(prog)))'
# byte_multiplier = 1


########## Generate Header ##########

size = DISP_WIDTH*DISP_HEIGHT*byte_multiplier

f = open(H_FILENAME, 'w')
f.write("#define %s_WIDTH\t%d\n" % (IMG_NAME.upper(), DISP_WIDTH))
f.write("#define %s_HEIGHT\t%d\n" % (IMG_NAME.upper(), DISP_HEIGHT))
f.write("#define {0}_SIZE\t({0}_WIDTH * {0}_HEIGHT * {1})".format(IMG_NAME.upper(), byte_multiplier))
f.write("\n")
f.write("%s %s_bytes[%d] = {\n" % (dataformat, IMG_NAME, size))

try:
    i = 0
    for i in range(DISP_HEIGHT):
        x = i*DISP_WIDTH
        line = pixels[x:x+DISP_WIDTH]
        f.write("\t" + ','.join(line) + ",\n")


finally:
    f.write("};")
    f.close()


