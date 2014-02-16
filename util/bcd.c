/*
 * File:   bcd.c
 * Author: Jared
 *
 * Created on 16 February 2014, 7:03 PM
 */

#include "system.h"
#include "util.h"

void bcd2str(byte bcd, char* s) {
    s[0] = '0' + ((bcd & 0xF0) >> 4);
    s[1] = '0' + (bcd & 0x0F);
    s[2] = '\0';
}

byte bcd2int(byte bcd) {
    return (bcd & 0x0F) + (((bcd & 0xF0)>>4)*10);
}

byte int2bcd(byte i) {
     return ((i / 10) << 4) | (i % 10);
}
