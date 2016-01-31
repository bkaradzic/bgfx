#ifndef __DARKRL__MATH_HPP__
#define __DARKRL__MATH_HPP__

#include <algorithm>
#include <math.h>

#include "Types.hpp"

template<typename T>
inline T AlignPOT( T val )
{
    if( val == 0 ) return 1;
    val--;
    for( unsigned int i=1; i<sizeof( T ) * 8; i <<= 1 )
    {
        val |= val >> i;
    }
    return val + 1;
}

inline int CountSetBits( uint32 val )
{
    val -= ( val >> 1 ) & 0x55555555;
    val = ( ( val >> 2 ) & 0x33333333 ) + ( val & 0x33333333 );
    val = ( ( val >> 4 ) + val ) & 0x0f0f0f0f;
    val += val >> 8;
    val += val >> 16;
    return val & 0x0000003f;
}

inline int CountLeadingZeros( uint32 val )
{
    val |= val >> 1;
    val |= val >> 2;
    val |= val >> 4;
    val |= val >> 8;
    val |= val >> 16;
    return 32 - CountSetBits( val );
}

inline float sRGB2linear( float v )
{
    const float a = 0.055f;
    if( v <= 0.04045f )
    {
        return v / 12.92f;
    }
    else
    {
        return powf( ( v + a ) / ( 1 + a ), 2.4f );
    }
}

inline float linear2sRGB( float v )
{
    const float a = 0.055f;
    if( v <= 0.0031308f )
    {
        return 12.92f * v;
    }
    else
    {
        return ( 1 + a ) * pow( v, 1/2.4f ) - a;
    }
}

template<class T>
inline T SmoothStep( T x )
{
    return x*x*(3-2*x);
}

inline uint8 clampu8( int32 val )
{
    return std::min( std::max( 0, val ), 255 );
}

template<class T>
inline T sq( T val )
{
    return val * val;
}

static inline int mul8bit( int a, int b )
{
    int t = a*b + 128;
    return ( t + ( t >> 8 ) ) >> 8;
}

#endif
