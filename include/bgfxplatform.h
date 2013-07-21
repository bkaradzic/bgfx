/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __BGFXPLATFORM_H__
#define __BGFXPLATFORM_H__

// NOTICE:
// This header file contains platform specific interfaces. It is only
// necessary to use this header in conjunction with creating windows.

#include <bx/bx.h>

#if BX_PLATFORM_ANDROID
#	include <android/native_window.h>

namespace bgfx
{
	void androidSetWindow(::ANativeWindow* _window);
} // namespace bgfx

#elif BX_PLATFORM_IOS
namespace bgfx
{
	void iosSetEaglLayer(void* _layer);
} // namespace bgfx

#elif BX_PLATFORM_LINUX
#	include <X11/Xlib.h>

namespace bgfx
{
	void x11SetDisplayWindow(::Display* _display, ::Window _window);
} // namespace bgfx

#elif BX_PLATFORM_NACL
#	include <ppapi/c/ppb_graphics_3d.h>
#	include <ppapi/c/ppb_instance.h>

namespace bgfx
{
	typedef void (*PostSwapBuffersFn)(uint32_t _width, uint32_t _height);
	void naclSetIntefraces(::PP_Instance, const ::PPB_Instance*, const ::PPB_Graphics3D*, PostSwapBuffersFn);
} // namespace bgfx

#elif BX_PLATFORM_OSX
#	include <Cocoa/Cocoa.h>
#	include <stdlib.h>

namespace bgfx
{
	void osxSetNSWindow(void* _window);
} // namespace bgfx

#elif BX_PLATFORM_WINDOWS
#	include <windows.h>

namespace bgfx
{
	void winSetHwnd(::HWND _window);
} // namespace bgfx

#endif // BX_PLATFORM_

#endif // __BGFXPLATFORM_H__
