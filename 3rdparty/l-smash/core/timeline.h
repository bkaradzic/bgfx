/*****************************************************************************
 * timeline.h
 *****************************************************************************
 * Copyright (C) 2011-2017 L-SMASH project
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

#ifndef LSMASH_TIMELINE_H
#define LSMASH_TIMELINE_H

typedef struct isom_timeline_tag isom_timeline_t;

typedef struct
{
    uint64_t       data_offset;
    uint64_t       length;
    uint32_t       number;  /* useless at present */
    lsmash_file_t *file;
} isom_portable_chunk_t;

typedef struct
{
    uint64_t pos;                   /* position of the first sample in this bunch */
    uint32_t duration;              /* duration in media timescale each sample has */
    uint32_t offset;                /* offset between composition time and decoding time each sample has */
    uint32_t length;                /* data size each sample has */
    uint32_t index;                 /* sample_description_index applied to each sample */
    isom_portable_chunk_t *chunk;   /* chunk samples belong to */
    lsmash_sample_property_t prop;  /* property applied to each sample */
    uint32_t sample_count;          /* number of samples in this bunch */
} isom_lpcm_bunch_t;

isom_timeline_t *isom_timeline_create( void );

void isom_timeline_destroy
(
    isom_timeline_t *timeline
);

int isom_timeline_set_track_ID
(
    isom_timeline_t *timeline,
    uint32_t         track_ID
);

int isom_timeline_set_movie_timescale
(
    isom_timeline_t *timeline,
    uint32_t         movie_timescale
);

int isom_timeline_set_media_timescale
(
    isom_timeline_t *timeline,
    uint32_t         media_timescale
);

int isom_timeline_set_sample_count
(
    isom_timeline_t *timeline,
    uint32_t         sample_count
);

int isom_timeline_set_max_sample_size
(
    isom_timeline_t *timeline,
    uint32_t         max_sample_size
);

int isom_timeline_set_media_duration
(
    isom_timeline_t *timeline,
    uint32_t         media_duration
);

int isom_timeline_set_track_duration
(
    isom_timeline_t *timeline,
    uint32_t         track_duration
);

void isom_timeline_set_lpcm_sample_getter_funcs
(
    isom_timeline_t *timeline
);

isom_timeline_t *isom_get_timeline
(
    lsmash_root_t *root,
    uint32_t       track_ID
);

void isom_remove_timelines
(
    lsmash_file_t *file
);

int isom_timeline_construct
(
    lsmash_root_t *root,
    uint32_t       track_ID
);

int isom_add_lpcm_bunch_entry
(
    isom_timeline_t   *timeline,
    isom_lpcm_bunch_t *src_bunch
);

isom_elst_entry_t *isom_timelime_get_explicit_timeline_map
(
    lsmash_root_t *root,
    uint32_t       track_ID,
    uint32_t       edit_number
);

uint32_t isom_timelime_count_explicit_timeline_map
(
    lsmash_root_t *root,
    uint32_t       track_ID
);

#endif /* LSMASH_TIMELINE_H */
