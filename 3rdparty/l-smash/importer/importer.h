/*****************************************************************************
 * importer.h
 *****************************************************************************
 * Copyright (C) 2010-2017 L-SMASH project
 *
 * Authors: Takashi Hirata <silverfilain@gmail.com>
 * Contributors: Yusuke Nakamura <muken.the.vfrmaniac@gmail.com>
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

#ifndef LSMASH_IMPORTER_H
#define LSMASH_IMPORTER_H

/***************************************************************************
    importer
***************************************************************************/
typedef struct importer_tag importer_t;

#ifdef LSMASH_IMPORTER_INTERNAL

#include "core/box.h"
#include "codecs/description.h"

typedef void     ( *importer_cleanup )           ( importer_t * );
typedef int      ( *importer_get_accessunit )    ( importer_t *, uint32_t, lsmash_sample_t ** );
typedef int      ( *importer_probe )             ( importer_t * );
typedef uint32_t ( *importer_get_last_duration ) ( importer_t *, uint32_t );
typedef int      ( *importer_construct_timeline )( importer_t *, uint32_t );

typedef enum
{
    IMPORTER_ERROR  = -1,
    IMPORTER_OK     = 0,
    IMPORTER_CHANGE = 1,
    IMPORTER_EOF    = 2,
} importer_status;

typedef struct
{
    lsmash_class_t              class;
    int                         detectable;
    importer_probe              probe;
    importer_get_accessunit     get_accessunit;
    importer_get_last_duration  get_last_delta;
    importer_cleanup            cleanup;
    importer_construct_timeline construct_timeline;
} importer_functions;

struct importer_tag
{
    const lsmash_class_t    *class;
    lsmash_log_level         log_level;
    importer_status          status;
    lsmash_root_t           *root;          /* pointer to a referenced ROOT */
    lsmash_file_t           *file;          /* pointer to a file which this importer handles */
    lsmash_bs_t             *bs;
    lsmash_file_parameters_t file_param;
    void                    *info;          /* importer internal status information. */
    importer_functions       funcs;
    lsmash_entry_list_t     *summaries;
    int                      is_adhoc_open; /* If set to 1, it means this importer is not allocated by lsmash_read_file().
                                             * This is a poor design due to historical implementation between the importer
                                             * framework and ISOBMFF demuxer framework. The importer shall be hidden inside
                                             * the file handling abstraction layer. That'll achieve integration of the muxer
                                             * and the remuxer CLIs. */
};

int lsmash_importer_make_fake_movie
(
    importer_t *importer
);

int lsmash_importer_make_fake_track
(
    importer_t       *importer,
    lsmash_media_type media_type,
    uint32_t         *track_ID
);

void lsmash_importer_break_fake_movie
(
    importer_t *importer
);

#else

int lsmash_importer_set_file
(
    importer_t    *importer,
    lsmash_file_t *file
);

/* importing functions */
importer_t *lsmash_importer_alloc
(
    lsmash_root_t *root
);

void lsmash_importer_destroy
(
    importer_t *importer
);

int lsmash_importer_find
(
    importer_t *importer,
    const char *format,
    int         auto_detect
);

importer_t *lsmash_importer_open
(
    lsmash_root_t *root,
    const char    *identifier,
    const char    *format
);

void lsmash_importer_close
(
    importer_t *importer
);

int lsmash_importer_get_access_unit
(
    importer_t       *importer,
    uint32_t          track_number,
    lsmash_sample_t **p_sample
);

uint32_t lsmash_importer_get_last_delta
(
    importer_t *importer,
    uint32_t    track_number
);

int lsmash_importer_construct_timeline
(
    importer_t *importer,
    uint32_t    track_number
);

uint32_t lsmash_importer_get_track_count
(
    importer_t *importer
);

lsmash_summary_t *lsmash_duplicate_summary
(
    importer_t *importer,
    uint32_t    track_number
);

#endif /* #ifdef LSMASH_IMPORTER_INTERNAL */

#endif /* #ifndef LSMASH_IMPORTER_H */
