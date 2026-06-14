/*****************************************************************************
 * osdep.c
 *****************************************************************************
 * Copyright (C) 2013-2017 L-SMASH project
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

#include "internal.h" /* must be placed first */

#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32

int lsmash_string_to_wchar( int cp, const char *from, wchar_t **to )
{
    int nc = MultiByteToWideChar( cp, 0, from, -1, 0, 0 );
    if( nc == 0 )
        return 0;
    *to = lsmash_malloc( nc * sizeof(wchar_t) );
    MultiByteToWideChar( cp, 0, from, -1, *to, nc );
    return nc;
}

int lsmash_string_from_wchar( int cp, const wchar_t *from, char **to )
{
    int nc = WideCharToMultiByte( cp, 0, from, -1, 0, 0, 0, 0 );
    if( nc == 0 )
        return 0;
    *to = lsmash_malloc( nc * sizeof(char) );
    WideCharToMultiByte( cp, 0, from, -1, *to, nc, 0, 0 );
    return nc;
}

FILE *lsmash_win32_fopen( const char *name, const char *mode )
{
    wchar_t *wname = NULL, *wmode = NULL;
    lsmash_string_to_wchar( CP_UTF8, name, &wname );
    lsmash_string_to_wchar( CP_UTF8, mode, &wmode );
    FILE *fp = _wfopen( wname, wmode );
    if( !fp )
        fp = fopen( name, mode );
    lsmash_free( wname );
    lsmash_free( wmode );
    return fp;
}

#endif

