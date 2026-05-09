/*****************************************************************************
 * memint.h
 *****************************************************************************
 * Copyright (C) 2014-2017 L-SMASH project
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

/*---- memory writers ----*/
#define LSMASH_SET_BYTE( p, x )          \
    do                                   \
    {                                    \
        ((uint8_t *)(p))[0] = (x);       \
    } while( 0 )
#define LSMASH_SET_BE16( p, x )          \
    do                                   \
    {                                    \
        ((uint8_t *)(p))[0] = (x) >> 8;  \
        ((uint8_t *)(p))[1] = (x);       \
    } while( 0 )
#define LSMASH_SET_BE24( p, x )          \
    do                                   \
    {                                    \
        ((uint8_t *)(p))[0] = (x) >> 16; \
        ((uint8_t *)(p))[1] = (x) >>  8; \
        ((uint8_t *)(p))[2] = (x);       \
    } while( 0 )
#define LSMASH_SET_BE32( p, x )          \
    do                                   \
    {                                    \
        ((uint8_t *)(p))[0] = (x) >> 24; \
        ((uint8_t *)(p))[1] = (x) >> 16; \
        ((uint8_t *)(p))[2] = (x) >>  8; \
        ((uint8_t *)(p))[3] = (x);       \
    } while( 0 )
#define LSMASH_SET_BE64( p, x )          \
    do                                   \
    {                                    \
        ((uint8_t *)(p))[0] = (x) >> 56; \
        ((uint8_t *)(p))[1] = (x) >> 48; \
        ((uint8_t *)(p))[2] = (x) >> 40; \
        ((uint8_t *)(p))[3] = (x) >> 32; \
        ((uint8_t *)(p))[4] = (x) >> 24; \
        ((uint8_t *)(p))[5] = (x) >> 16; \
        ((uint8_t *)(p))[6] = (x) >>  8; \
        ((uint8_t *)(p))[7] = (x);       \
    } while( 0 )
#define LSMASH_SET_LE16( p, x )          \
    do                                   \
    {                                    \
        ((uint8_t *)(p))[0] = (x);       \
        ((uint8_t *)(p))[1] = (x) >> 8;  \
    } while( 0 )
#define LSMASH_SET_LE32( p, x )          \
    do                                   \
    {                                    \
        ((uint8_t *)(p))[0] = (x);       \
        ((uint8_t *)(p))[1] = (x) >>  8; \
        ((uint8_t *)(p))[2] = (x) >> 16; \
        ((uint8_t *)(p))[3] = (x) >> 24; \
    } while( 0 )

/*---- memory readers ----*/
#define LSMASH_GET_BYTE( p )                      \
    (((const uint8_t *)(p))[0])
#define LSMASH_GET_BE16( p )                      \
     (((uint16_t)((const uint8_t *)(p))[0] << 8)  \
    | ((uint16_t)((const uint8_t *)(p))[1]))
#define LSMASH_GET_BE24( p )                      \
     (((uint32_t)((const uint8_t *)(p))[0] << 16) \
    | ((uint32_t)((const uint8_t *)(p))[1] <<  8) \
    | ((uint32_t)((const uint8_t *)(p))[2]))
#define LSMASH_GET_BE32( p )                      \
     (((uint32_t)((const uint8_t *)(p))[0] << 24) \
    | ((uint32_t)((const uint8_t *)(p))[1] << 16) \
    | ((uint32_t)((const uint8_t *)(p))[2] <<  8) \
    | ((uint32_t)((const uint8_t *)(p))[3]))
#define LSMASH_GET_BE64( p )                      \
     (((uint64_t)((const uint8_t *)(p))[0] << 56) \
    | ((uint64_t)((const uint8_t *)(p))[1] << 48) \
    | ((uint64_t)((const uint8_t *)(p))[2] << 40) \
    | ((uint64_t)((const uint8_t *)(p))[3] << 32) \
    | ((uint64_t)((const uint8_t *)(p))[4] << 24) \
    | ((uint64_t)((const uint8_t *)(p))[5] << 16) \
    | ((uint64_t)((const uint8_t *)(p))[6] <<  8) \
    | ((uint64_t)((const uint8_t *)(p))[7]))
#define LSMASH_GET_LE16( p )                      \
     (((uint16_t)((const uint8_t *)(p))[0])       \
    | ((uint16_t)((const uint8_t *)(p))[1] << 8))
#define LSMASH_GET_LE32( p )                      \
     (((uint32_t)((const uint8_t *)(p))[0])       \
    | ((uint32_t)((const uint8_t *)(p))[1] <<  8) \
    | ((uint32_t)((const uint8_t *)(p))[2] << 16) \
    | ((uint32_t)((const uint8_t *)(p))[3] << 24))
