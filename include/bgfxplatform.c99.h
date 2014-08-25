/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
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

#if BX_PLATFORM_ANDROID
#    include <android/native_window.h>

/**
 *
 */
BGFX_C_API void bgfx_android_set_window(ANativeWindow* _window);

#elif BX_PLATFORM_IOS

/**
 *
 */
BGFX_C_API void bgfx_ios_set_eagl_layer(void* _layer);

#elif BX_PLATFORM_FREEBSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI
#    include <X11/Xlib.h>

/**
 *
 */
BGFX_C_API void bgfx_x11_set_display_window(Display* _display, Window _window);

#elif BX_PLATFORM_NACL
#    include <ppapi/c/ppb_graphics_3d.h>
#    include <ppapi/c/ppb_instance.h>

typedef void (*bgfx_post_swap_buffers_fn)(uint32_t _width, uint32_t _height);

/**
 *
 */
BGFX_C_API bool bgfx_nacl_set_interfaces(PP_Instance, const PPB_Instance*, const PPB_Graphics3D*, bgfx_post_swap_buffers_fn);

#elif BX_PLATFORM_OSX

/**
 *
 */
BGFX_C_API void bgfx_osx_set_ns_window(void* _window);

#elif BX_PLATFORM_WINDOWS
#    include <windows.h>

/**
 *
 */
BGFX_C_API void bgfx_win_set_hwnd(HWND _window);

#endif // BX_PLATFORM_

#endif // BGFX_PLATFORM_C99_H_HEADER_GUARD
