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

#endif	/* UTIL_H */

