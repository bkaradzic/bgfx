/*****************************************************************************
 * bits.c
 *****************************************************************************
 * Copyright (C) 2010-2017 L-SMASH project
 *
 * Authors: Takashi Hirata <silverfilain@gmail.com>
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

#include "internal.h" /* must be placed first */

void lsmash_bits_init( lsmash_bits_t *bits, lsmash_bs_t *bs )
{
    debug_if( !bits || !bs )
        return;
    bits->bs    = bs;
    bits->store = 0;
    bits->cache = 0;
}

lsmash_bits_t *lsmash_bits_create( lsmash_bs_t *bs )
{
    debug_if( !bs )
        return NULL;
    lsmash_bits_t *bits = (lsmash_bits_t *)lsmash_malloc( sizeof(lsmash_bits_t) );
    if( !bits )
        return NULL;
    lsmash_bits_init( bits, bs );
    return bits;
}

/* Must be used ONLY for bits struct created with isom_create_bits.
 * Otherwise, just lsmash_free() the bits struct. */
void lsmash_bits_cleanup( lsmash_bits_t *bits )
{
    debug_if( !bits )
        return;
    lsmash_free( bits );
}

void lsmash_bits_empty( lsmash_bits_t *bits )
{
    debug_if( !bits )
        return;
    lsmash_bs_empty( bits->bs );
    bits->store = 0;
    bits->cache = 0;
}

#define BITS_IN_BYTE 8
void lsmash_bits_put_align( lsmash_bits_t *bits )
{
    debug_if( !bits )
        return;
    if( !bits->store )
        return;
    lsmash_bs_put_byte( bits->bs, bits->cache << ( BITS_IN_BYTE - bits->store ) );
}

void lsmash_bits_get_align( lsmash_bits_t *bits )
{
    debug_if( !bits )
        return;
    bits->store = 0;
    bits->cache = 0;
}

/* we can change value's type to unsigned int for 64-bit operation if needed. */
static inline uint8_t lsmash_bits_mask_lsb8( uint32_t value, uint32_t width )
{
    return (uint8_t)( value & ~( ~0U << width ) );
}

void lsmash_bits_put( lsmash_bits_t *bits, uint32_t width, uint64_t value )
{
    debug_if( !bits || !width )
        return;
    if( bits->store )
    {
        if( bits->store + width < BITS_IN_BYTE )
        {
            /* cache can contain all of value's bits. */
            bits->cache <<= width;
            bits->cache |= lsmash_bits_mask_lsb8( value, width );
            bits->store += width;
            return;
        }
        /* flush cache with value's some leading bits. */
        uint32_t free_bits = BITS_IN_BYTE - bits->store;
        bits->cache <<= free_bits;
        bits->cache |= lsmash_bits_mask_lsb8( value >> (width -= free_bits), free_bits );
        lsmash_bs_put_byte( bits->bs, bits->cache );
        bits->store = 0;
        bits->cache = 0;
    }
    /* cache is empty here. */
    /* byte unit operation. */
    while( width > BITS_IN_BYTE )
        lsmash_bs_put_byte( bits->bs, (uint8_t)(value >> (width -= BITS_IN_BYTE)) );
    /* bit unit operation for residual. */
    if( width )
    {
        bits->cache = lsmash_bits_mask_lsb8( value, width );
        bits->store = width;
    }
}

uint64_t lsmash_bits_get( lsmash_bits_t *bits, uint32_t width )
{
    debug_if( !bits || !width )
        return 0;
    uint64_t value = 0;
    if( bits->store )
    {
        if( bits->store >= width )
        {
            /* cache contains all of bits required. */
            bits->store -= width;
            return lsmash_bits_mask_lsb8( bits->cache >> bits->store, width );
        }
        /* fill value's leading bits with cache's residual. */
        value = lsmash_bits_mask_lsb8( bits->cache, bits->store );
        width -= bits->store;
        bits->store = 0;
        bits->cache = 0;
    }
    /* cache is empty here. */
    /* byte unit operation. */
    while( width > BITS_IN_BYTE )
    {
        value <<= BITS_IN_BYTE;
        width -= BITS_IN_BYTE;
        value |= lsmash_bs_get_byte( bits->bs );
    }
    /* bit unit operation for residual. */
    if( width )
    {
        bits->cache = lsmash_bs_get_byte( bits->bs );
        bits->store = BITS_IN_BYTE - width;
        value <<= width;
        value |= lsmash_bits_mask_lsb8( bits->cache >> bits->store, width );
    }
    return value;
}

void *lsmash_bits_export_data( lsmash_bits_t *bits, uint32_t *length )
{
    lsmash_bits_put_align( bits );
    return lsmash_bs_export_data( bits->bs, length );
}

int lsmash_bits_import_data( lsmash_bits_t *bits, void *data, uint32_t length )
{
    return lsmash_bs_import_data( bits->bs, data, length );
}

/****
 bitstream with bytestream for adhoc operation
****/

lsmash_bits_t *lsmash_bits_adhoc_create()
{
    lsmash_bs_t *bs = lsmash_bs_create();
    if( !bs )
        return NULL;
    lsmash_bits_t *bits = lsmash_bits_create( bs );
    if( !bits )
    {
        lsmash_bs_cleanup( bs );
        return NULL;
    }
    return bits;
}

void lsmash_bits_adhoc_cleanup( lsmash_bits_t *bits )
{
    if( !bits )
        return;
    lsmash_bs_cleanup( bits->bs );
    lsmash_bits_cleanup( bits );
}
