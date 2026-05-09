/*****************************************************************************
 * utils.h
 *****************************************************************************
 * Copyright (C) 2010-2017 L-SMASH project
 *
 * Authors: Yusuke Nakamura <muken.the.vfrmaniac@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *****************************************************************************/

/* This file is available under an ISC license. */

#ifndef LSMASH_UTIL_H
#define LSMASH_UTIL_H

#define debug_if(x) if(x)

#define LSMASH_MAX( a, b ) ((a) > (b) ? (a) : (b))
#define LSMASH_MIN( a, b ) ((a) < (b) ? (a) : (b))

#define EXPAND_VA_ARGS( ... ) __VA_ARGS__

/* default arguments
 * Use only CALL_FUNC_DEFAULT_ARGS().
 * The defined macros can't be passed a macro argument requiring the empty parameter list.
 *
 * The following is an example.
 *   #define TEMPLATE_A( ... ) CALL_FUNC_DEFAULT_ARGS( TEMPLATE_A, __VA_ARGS__ )
 *   #define TEMPLATE_A_1( _1 )     _1( 1 )
 *   #define TEMPLATE_B( ... ) CALL_FUNC_DEFAULT_ARGS( TEMPLATE_B, __VA_ARGS__ )
 *   #define TEMPLATE_B_2( _1, _2 ) ((_1) + (_2))
 *   #define TEMPLATE_B_1( _1 )     TEMPLATE_B_2( _1, 0 )
 *   #define TEMPLATE_B_0()
 *   int main( void )
 *   {
 *      TEMPLATE_A( TEMPLATE_B_1 ); // OK
 *      TEMPLATE_A( TEMPLATE_B );   // NG
 *      TEMPLATE_B( 1, 2 );         // OK
 *      TEMPLATE_B();               // NG
 *      return 0;
 *   }
 * */
#define NUM_ARGS( _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, ... ) _12
#ifdef _MSC_VER
#define COUNT_NUM_ARGS( ... ) EXPAND_VA_ARGS( NUM_ARGS( __VA_ARGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0 ) )
#else
#define COUNT_NUM_ARGS( ... ) NUM_ARGS( __VA_ARGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0 )
#endif
#define GET_FUNC_BY_NUM_ARGS_EXN( func_name, N )   func_name ## _ ## N
#define GET_FUNC_BY_NUM_ARGS_EX0( func_name, N )   GET_FUNC_BY_NUM_ARGS_EXN( func_name, N )
#define GET_FUNC_BY_NUM_ARGS_EX1( func_name, ... ) GET_FUNC_BY_NUM_ARGS_EX0( func_name, COUNT_NUM_ARGS( __VA_ARGS__ ) )
#define CALL_FUNC_DEFAULT_ARGS( func_name, ... )   GET_FUNC_BY_NUM_ARGS_EX1( func_name, __VA_ARGS__ ) ( __VA_ARGS__ )

/*---- class ----*/
typedef struct
{
    char  *name;
    size_t log_level_offset;    /* offset in the struct where 'log_level' is placed
                                 * If set to 0, 'log_level' is unavailable and implicitly set to LSMASH_LOG_INFO. */
} lsmash_class_t;

/*---- type ----*/
double lsmash_fixed2double( int64_t value, int frac_width );
float lsmash_int2float32( uint32_t value );
double lsmash_int2float64( uint64_t value );

/*---- others ----*/
typedef enum
{
    LSMASH_LOG_QUIET = 0,
    LSMASH_LOG_ERROR,
    LSMASH_LOG_WARNING,
    LSMASH_LOG_INFO,
} lsmash_log_level;

typedef struct
{
    uint64_t n;
    uint64_t d;
} lsmash_rational_u64_t;

typedef struct
{
    int64_t  n;
    uint64_t d;
} lsmash_rational_s64_t;

void lsmash_log
(
    const void      *class,
    lsmash_log_level level,
    const char      *message,
    ...
);

void lsmash_log_refresh_line
(
    const void *class
);

void lsmash_ifprintf
(
    FILE       *fp,
    int         indent,
    const char *format, ...
);

static inline uint32_t lsmash_count_bits
(
    uint32_t bits
)
{
    bits = (bits & 0x55555555) + ((bits >>  1) & 0x55555555);
    bits = (bits & 0x33333333) + ((bits >>  2) & 0x33333333);
    bits = (bits & 0x0f0f0f0f) + ((bits >>  4) & 0x0f0f0f0f);
    bits = (bits & 0x00ff00ff) + ((bits >>  8) & 0x00ff00ff);
    return (bits & 0x0000ffff) + ((bits >> 16) & 0x0000ffff);
}

static inline size_t lsmash_floor_log2
(
    uint64_t value
)
{
    assert( value >= 1 );
#if defined(__GNUC__) && (__GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))  /* GCC >= 3.4 */
    return (sizeof(uint64_t) - 1) - __builtin_clzll( value );
#else
    size_t s = 0;
    while( value )
    {
        value >>= 1;
        ++s;
    }
    return s - 1;
#endif
}

static inline size_t lsmash_ceil_log2
(
    uint64_t value
)
{
    return lsmash_floor_log2( value ) + ((value & (value - 1)) != 0);
}

int lsmash_compare_dts
(
    const lsmash_media_ts_t *a,
    const lsmash_media_ts_t *b
);

int lsmash_compare_cts
(
    const lsmash_media_ts_t *a,
    const lsmash_media_ts_t *b
);

static inline uint64_t lsmash_get_gcd
(
    uint64_t a,
    uint64_t b
)
{
    if( !b )
        return a;
    while( 1 )
    {
        uint64_t c = a % b;
        if( !c )
            return b;
        a = b;
        b = c;
    }
}

static inline uint64_t lsmash_get_lcm
(
    uint64_t a,
    uint64_t b
)
{
    if( !a )
        return 0;
    return (a / lsmash_get_gcd( a, b )) * b;
}

static inline void lsmash_reduce_fraction
(
    uint64_t *a,
    uint64_t *b
)
{
    if( !a || !b )
        return;
    uint64_t gcd = lsmash_get_gcd( *a, *b );
    if( gcd )
    {
        *a /= gcd;
        *b /= gcd;
    }
}

static inline void lsmash_reduce_fraction_su
(
    int64_t  *a,
    uint64_t *b
)
{
    if( !a || !b )
        return;
    uint64_t c = *a > 0 ? *a : -(*a);
    uint64_t gcd = lsmash_get_gcd( c, *b );
    if( gcd )
    {
        c /= gcd;
        *b /= gcd;
        *a = *a > 0 ? (signed)c : -(signed)c;
    }
}

#endif
