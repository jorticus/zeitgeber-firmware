/* 
 * File:   vector.h
 * Author: Jared
 *
 * Created on 9 July 2013, 2:40 PM
 *
 * Integer vector math
 */

#ifndef VECTOR_H
#define	VECTOR_H

///// int16 /////

typedef struct {
    int16 X;
    int16 Y;
} vector2i_t;

typedef struct {
    int16 X;
    int16 Y;
    int16 Z;
} vector3i_t;

typedef struct {
    int16 X;
    int16 Y;
    int16 Z;
    int16 W;
} vector4i_t;

///// uint16 /////

typedef struct {
    uint16 X;
    uint16 Y;
} vector2u_t;

typedef struct {
    uint16 X;
    uint16 Y;
    uint16 Z;
} vector3u_t;

typedef struct {
    uint16 X;
    uint16 Y;
    uint16 Z;
    uint16 W;
} vector4u_t;

///// int32 /////

typedef struct {
    int32 X;
    int32 Y;
} vector2l_t;

typedef struct {
    int32 X;
    int32 Y;
    int32 Z;
} vector3l_t;

typedef struct {
    int32 X;
    int32 Y;
    int32 Z;
    int32 W;
} vector4l_t;

typedef vector3i_t euler_t;
typedef vector4i_t quaternion_t;


#endif	/* VECTOR_H */

