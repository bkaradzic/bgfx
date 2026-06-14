/*****************************************************************************
 * bits.h
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

typedef struct
{
    lsmash_bs_t *bs;
    uint8_t      store;
    uint8_t      cache;
} lsmash_bits_t;

void lsmash_bits_init( lsmash_bits_t* bits, lsmash_bs_t *bs );
lsmash_bits_t *lsmash_bits_create( lsmash_bs_t *bs );
void lsmash_bits_cleanup( lsmash_bits_t *bits );
void lsmash_bits_empty( lsmash_bits_t *bits );
void lsmash_bits_put_align( lsmash_bits_t *bits );
void lsmash_bits_get_align( lsmash_bits_t *bits );
void lsmash_bits_put( lsmash_bits_t *bits, uint32_t width, uint64_t value );
uint64_t lsmash_bits_get( lsmash_bits_t *bits, uint32_t width );
void *lsmash_bits_export_data( lsmash_bits_t *bits, uint32_t *length );
int lsmash_bits_import_data( lsmash_bits_t *bits, void *data, uint32_t length );

lsmash_bits_t *lsmash_bits_adhoc_create();
void lsmash_bits_adhoc_cleanup( lsmash_bits_t *bits );
