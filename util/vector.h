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

///// int8 /////

typedef struct {
    int8 x;
    int8 y;
    int8 z;
} vector3c_t;

///// int16 /////

typedef struct {
    int16 x;
    int16 y;
} vector2i_t;

typedef struct {
    int16 x;
    int16 y;
    int16 z;
} vector3i_t;

typedef struct {
    int16 x;
    int16 y;
    int16 z;
    int16 w;
} vector4i_t;

///// uint16 /////

typedef struct {
    uint16 x;
    uint16 y;
} vector2u_t;

typedef struct {
    uint16 x;
    uint16 y;
    uint16 z;
} vector3u_t;

typedef struct {
    uint16 x;
    uint16 y;
    uint16 z;
    uint16 w;
} vector4u_t;

///// int32 /////

typedef struct {
    int32 x;
    int32 y;
} vector2l_t;

typedef struct {
    int32 x;
    int32 y;
    int32 z;
} vector3l_t;

typedef struct {
    int32 x;
    int32 y;
    int32 z;
    int32 w;
} vector4l_t;

typedef vector3i_t euler_t;
typedef vector4i_t quaternion_t;


#endif	/* VECTOR_H */

