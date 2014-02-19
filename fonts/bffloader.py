
import struct
from PIL import Image
from math import floor

BFG_RS_NONE  = 0x0      # Blend flags
BFG_RS_ALPHA = 0x1
BFG_RS_RGB   = 0x2
BFG_RS_RGBA  = 0x4

WIDTH_DATA_OFFSET  = 20 # Offset to width data with BFF file
MAP_DATA_OFFSET   = 276 # Offset to texture image data with BFF file


class BffFont(object):
    def __init__(self):
        # Font properties
        self.widths = None
        self.base = None
        self.cellWidth = None
        self.cellHeight = None

        # Image properties
        self.bpp = None
        self.imgWidth = None
        self.imgHeight = None

        self.numXCells = None
        self.numYCells = None

    def load(self, filename):
        with open(filename, 'rb') as f:
            dat = f.read()

        offset = 0

        # Check ID is 'BFF2'
        if ord(dat[0]) != 0xBF or ord(dat[1]) != 0xF2:
            raise Exception("Invalid file header")
        offset += 2

        def unpack(fmt, offset):
            result = struct.unpack_from(fmt, dat, offset=offset)
            offset += struct.calcsize(fmt)
            return result, offset

        # Grab the rest of the header
        self.imgWidth, self.imgHeight = struct.unpack("ii", dat[2:10])
        self.cellWidth, self.cellHeight = struct.unpack("ii", dat[10:18])

        self.bpp = ord(dat[18])
        self.base = ord(dat[19])

        ImgSize = (self.imgWidth*self.imgHeight)*(self.bpp/8)

        if len(dat) != (MAP_DATA_OFFSET + ImgSize):
            raise Exception("Invalid filesize")

        # Calculate font params
        RowPitch = self.imgWidth / self.cellWidth
        ColFactor = float(self.cellWidth)/float(self.imgWidth)
        RowFactor = float(self.cellHeight)/float(self.imgHeight)
        YOffset = self.cellHeight

        self.numXCells = floor(self.imgWidth / self.cellWidth)
        self.numYCells = floor(self.imgHeight / self.cellHeight)

        # Determine blending options based on BPP
        if self.bpp == 8: # Greyscale
            imgMode = 'L'
        elif self.bpp == 24: # RGB
            imgMode = 'RGB'
        elif self.bpp == 32: # RGBA
            imgMode = 'RGBA'
        else:
            raise Exception("Unsupported bit depth")

        # Grab char widths
        self.widths = [ord(w) for w in dat[WIDTH_DATA_OFFSET:WIDTH_DATA_OFFSET+256]]

        # Grab image data
        image_data = dat[MAP_DATA_OFFSET:MAP_DATA_OFFSET+ImgSize]
        self.image = Image.frombuffer(imgMode, (self.imgWidth, self.imgHeight), image_data, 'raw', imgMode, 0, 1)
        #self.image.save("out.png")

    def _get_offset(self, c):
        if ord(c) < self.base or ord(c) > 255:
            raise ValueError("Unsupported character")

        index = ord(c) - self.base
        xi = int(index % self.numXCells)
        yi = int(floor(index / self.numXCells))

        return index, xi*self.cellWidth, yi*self.cellHeight

    def get_glyph(self, c):
        index, x, y = self._get_offset(c)
        w = self.widths[ord(c)]
        h = self.cellHeight

        glyph = self.image.crop((x, y, x+w, y+h))
        return glyph, w


if __name__ == "__main__":
    font = BffFont()
    font.load("Segoe UI.bff")

    img, width = font.get_glyph('@')
    img = img.convert("RGB")
    img.save("glyph.png")
