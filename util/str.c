
#include <stdlib.h>
#include <stdio.h>

#include "system.h"
#include "util.h"

char* decitoa(char* buf, unsigned val) {
    sprintf(buf, "%d.%d", val/10, val%10);
    return buf;
}