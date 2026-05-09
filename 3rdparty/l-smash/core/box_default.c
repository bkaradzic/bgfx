/*****************************************************************************
 * box_default.c
 *****************************************************************************
 * Copyright (C) 2017 L-SMASH project
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

#include "common/internal.h" /* must be placed first */

#include "box.h"
#include "box_default.h"

#define INITIALIZE_BASEBOX_COMMON( box_name )                                \
    .class        = &isom_box_default_class,                                 \
    .root         = (isom_root_abstract_t *)&isom_root_abstract_box_default, \
    .file         = (isom_file_abstract_t *)&isom_file_abstract_box_default, \
    .parent       = (isom_box_t *)&isom_opaque_box_default,                  \
    .nonexist_ptr = (void *)&isom_##box_name##_box_default,                  \
    .binary       = NULL,                                                    \
    .destruct     = NULL,                                                    \
    .write        = NULL,                                                    \
    .manager      = LSMASH_NON_EXISTING_BOX,                                 \
    .precedence   = 0,                                                       \
    .pos          = 0,                                                       \
    .extensions   = { .head = NULL },                                        \
    .size         = 0,                                                       \
    .type         = LSMASH_BOX_TYPE_INITIALIZER

#define DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( box_name )        \
    const isom_##box_name##_t isom_##box_name##_box_default = \
    {                                                         \
        INITIALIZE_BASEBOX_COMMON( box_name )                 \
    }

static const lsmash_class_t isom_box_default_class =
{
    "box_default"
};

typedef isom_box_t isom_opaque_t;
static const isom_box_t isom_opaque_box_default =
{
    INITIALIZE_BASEBOX_COMMON( opaque )
};

DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( dummy );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( unknown );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( ftyp );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( ctab );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( tkhd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( clef );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( prof );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( enof );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( elst );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( tref_type );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( tref );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mdhd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( hdlr );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( vmhd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( smhd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( hmhd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( nmhd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( gmin );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( text );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( dref_entry );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( dref );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( esds );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( btrt );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( glbl );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( clap );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( pasp );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( colr );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( gama );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( fiel );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( cspc );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( clli );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mdcv );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( sgbt );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( stsl );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( sample_entry );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mp4s_entry );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( visual_entry );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( frma );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( enda );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mp4a );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( terminator );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( chan );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( srat );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( audio_entry );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( tims );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( tsro );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( tssy );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( hint_entry );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( metadata_entry );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( qt_text_entry );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( ftab );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( stsd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( stts );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( ctts );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( cslg );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( stsz );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( stz2 );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( stss );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( stps );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( sdtp );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( stsc );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( stco );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( sgpd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( sbgp );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mvhd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( iods );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mdat );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( skip );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( chpl );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( keys );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mean );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( name );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( data );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( ilst );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( WLOC );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( LOOP );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( SelO );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( AllF );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( rtp );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( sdp );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( cprt );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mehd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( trex );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mfhd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( tfhd );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( tfdt );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( trun );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( tfra );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( mfro );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( styp );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( sidx );
DEFINE_SIMPLE_BOX_DEFAULT_CONSTANT( root_abstract );

#define INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( child_name ) \
    .child_name = (isom_##child_name##_t *)&isom_##child_name##_box_default

#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( ... ) \
        CALL_FUNC_DEFAULT_ARGS( DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT, __VA_ARGS__ )
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name, expanded_initializations ) \
    const isom_##box_name##_t isom_##box_name##_box_default =                                       \
    {                                                                                               \
        INITIALIZE_BASEBOX_COMMON( box_name ),                                                      \
        expanded_initializations                                                                    \
    }
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_12( box_name,                                     \
                                                         _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10 ) \
    DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name,                                   \
        EXPAND_VA_ARGS( INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _0 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _1 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _2 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _3 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _4 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _5 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _6 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _7 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _8 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _9 ),                     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _10 ) ) )
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_9( box_name, _0, _1, _2, _3, _4, _5, _6, _7 ) \
    DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name,                               \
        EXPAND_VA_ARGS( INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _0 ),                 \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _1 ),                 \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _2 ),                 \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _3 ),                 \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _4 ),                 \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _5 ),                 \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _6 ),                 \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _7 ) ) )
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_8( box_name, _0, _1, _2, _3, _4, _5, _6 ) \
    DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name,                           \
        EXPAND_VA_ARGS( INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _0 ),             \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _1 ),             \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _2 ),             \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _3 ),             \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _4 ),             \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _5 ),             \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _6 ) ) )
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_7( box_name, _0, _1, _2, _3, _4, _5 ) \
    DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name,                       \
        EXPAND_VA_ARGS( INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _0 ),         \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _1 ),         \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _2 ),         \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _3 ),         \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _4 ),         \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _5 ) ) )
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_6( box_name, _0, _1, _2, _3, _4 ) \
    DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name,                   \
        EXPAND_VA_ARGS( INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _0 ),     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _1 ),     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _2 ),     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _3 ),     \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _4 ) ) )
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_5( box_name, _0, _1, _2, _3 ) \
    DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name,               \
        EXPAND_VA_ARGS( INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _0 ), \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _1 ), \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _2 ), \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _3 ) ) )
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_4( box_name, _0, _1, _2 )     \
    DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name,               \
        EXPAND_VA_ARGS( INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _0 ), \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _1 ), \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _2 ) ) )
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_3( box_name, _0, _1 )         \
    DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name,               \
        EXPAND_VA_ARGS( INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _0 ), \
                        INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _1 ) ) )
#define DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_2( box_name, _0 ) \
    DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT_TEMPLATE( box_name,   \
        EXPAND_VA_ARGS( INITIALIZE_PREDEFINED_CHILD_BY_DEFAULT_CONSTANT_PTR( _0 ) ) )

DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( tapt, clef, enof, prof );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( edts, elst );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( gmhd, gmin, text );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( dinf, dref );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( wave, frma, enda, mp4a );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( tx3g_entry, ftab );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( stbl, stsd, stts, ctts, cslg, stss, stps, sdtp, stsc, stsz, stz2, stco );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( minf, vmhd, smhd, hmhd, nmhd, gmhd, hdlr, dinf, stbl );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( mdia, mdhd, hdlr, minf );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( metaitem, mean, name, data );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( meta, hdlr, dinf, keys, ilst );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( udta, chpl, meta, WLOC, LOOP, SelO, AllF, hnti );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( hnti, rtp, sdp );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( mvex, mehd );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( traf, tfhd, tfdt, sdtp );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( moof, mfhd );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( mfra, mfro );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( trak, tkhd, tapt, edts, tref, mdia, udta, meta );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( moov, mvhd, iods, udta, ctab, meta, mvex );
DEFINE_SIMPLE_CONTAINER_BOX_DEFAULT_CONSTANT( file_abstract, ftyp, moov, mdat, meta, mfra );

/* Box-lists predefined in the parent box definitions are initialized by 0s, thus the entry eliminator
 * of each list also be set to NULL (0). This must not be an issue since all box are deallocated through
 * the 'extensions' list of the parent box. Only 'entry' which holds the actual box data is deallocated
 * when the box is deallocated by the isom_remove_box_in_predefined_list() function. Because of that,
 * here, there are no explicit default constant definitions of indivisual predefined box-lists. */


/* Allocate box by default settings.
 *
 * Use this function to allocate boxes as much as possible, it covers forgetful settings. */
void *allocate_box_by_default
(
    const void  *nonexist_ptr,
    const size_t data_type_size
)
{
    assert( data_type_size >= offsetof( isom_box_t, manager ) + sizeof(((isom_box_t *)0)->manager) );
    isom_box_t *box = (isom_box_t *)lsmash_memdup( nonexist_ptr, data_type_size );
    if( !box )
        return (void *)nonexist_ptr;
    box->manager &= ~LSMASH_NON_EXISTING_BOX;
    lsmash_list_init( &box->extensions, isom_remove_extension_box );
    return (void *)box;
}
