/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 *
 * vim: set tabstop=4 expandtab:
 */

#ifndef BGFX_PLATFORM_C99_H_HEADER_GUARD
#define BGFX_PLATFORM_C99_H_HEADER_GUARD

// NOTICE:
// This header file contains platform specific interfaces. It is only
// necessary to use this header in conjunction with creating windows.

#include <bx/platform.h>

typedef enum bgfx_render_frame
{
    BGFX_RENDER_FRAME_NO_CONTEXT,
    BGFX_RENDER_FRAME_RENDER,
    BGFX_RENDER_FRAME_EXITING,

    BGFX_RENDER_FRAME_COUNT

} bgfx_render_frame_t;

/**
 * WARNING: This call should be only used on platforms that don't
 * allow creating separate rendering thread. If it is called before
 * to bgfx_init, render thread won't be created by bgfx_init call.
 */
BGFX_C_API bgfx_render_frame_t bgfx_render_frame();

typedef struct bgfx_platform_data
{
    void* ndt;
    void* nwh;
    void* context;
    void* backBuffer;
    void* backBufferDS;

} bgfx_platform_data_t;

BGFX_C_API void bgfx_set_platform_data(bgfx_platform_data_t* _pd);

#endif // BGFX_PLATFORM_C99_H_HEADER_GUARD
