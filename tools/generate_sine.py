import math

OUT_HEADER = "../util/sine.c"
MAX_VALUE = 32767
N = 512

input = range(N)
output = [math.sin( (x/float(N-1))*2*math.pi)*MAX_VALUE for x in input]

with open(OUT_HEADER, 'w') as f:
    f.write('\n\n#include "system.h"\n\n')
    f.write('const int16 sine_table[] = {\n')

    x = 0
    for i in range(N):
        f.write("%d, " % output[i])
        x += 1
        if x == 8:
            x = 0
            f.write("\n")


    f.write("};\n\n")