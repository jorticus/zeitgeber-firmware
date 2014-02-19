
OUT_HEADER = "../drivers/oledlut.h"
MAX_VALUE = 200

def cie1931(L):
    """
    Input: Luminance (0.0 to 1.0)
    Output: Lightness (0.0 to 1.0)
    """
    L = L * 100
    if L <= 8:
        return (L/902.3)
    else:
        return ((L+16.0)/116.0)**3

input = range(64)

# Linear
output = [int((x/63.0)*MAX_VALUE) for x in input]

# CIE1931 Lightness
#output = [int(cie1931(x/63.0)*MAX_VALUE) for x in input]

print output

if min(output) < 0 or max(output) > 255:
    raise ValueError("LUT values exceed allowable range")

with open(OUT_HEADER, 'w') as f:
    f.write("\n")
    f.write("const uint8 gamma_lut[64] = {\n")

    i = 0
    for y in range(8):
        f.write("    ")
        for x in range(8):
            f.write("%d, " % output[i])
            i += 1
        f.write("\n")

    f.write("};\n\n")