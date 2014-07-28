/* 
 * File:   util.h
 * Author: Jared
 *
 * Created on 29 August 2013, 6:17 PM
 *
 * Miscellaneous Utillities
 */

#ifndef UTIL_H
#define	UTIL_H

//uint lerp(uint a, uint b, uint x);

#define mLerp(inl, inh, outl, outh, value) ( (value - inl) * (outh - outl) / (inh - inl) + outl )

void bcd2str(byte bcd, char* s);
byte bcd2int(byte bcd);
byte int2bcd(byte i);

char* decitoa(char* buf, unsigned val);

#endif	/* UTIL_H */

