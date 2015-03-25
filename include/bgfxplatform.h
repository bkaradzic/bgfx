/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_PLATFORM_H_HEADER_GUARD
#define BGFX_PLATFORM_H_HEADER_GUARD

// NOTICE:
// This header file contains platform specific interfaces. It is only
// necessary to use this header in conjunction with creating windows.

#include <bx/platform.h>

namespace bgfx
{
	struct RenderFrame
	{
		enum Enum
		{
			NoContext,
			Render,
			Exiting,

			Count
		};
	};

	/// WARNING: This call should be only used on platforms that don't
	/// allow creating separate rendering thread. If it is called before
	/// to bgfx::init, render thread won't be created by bgfx::init call.
	RenderFrame::Enum renderFrame();
}

#if BX_PLATFORM_ANDROID
#	include <android/native_window.h>

namespace bgfx
{
	///
	void androidSetWindow(::ANativeWindow* _window);

} // namespace bgfx

#elif BX_PLATFORM_IOS
namespace bgfx
{
	///
	void iosSetEaglLayer(void* _layer);

} // namespace bgfx

#elif BX_PLATFORM_FREEBSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI

namespace bgfx
{
	///
	void x11SetDisplayWindow(void* _display, uint32_t _window, void* _glx = NULL);

} // namespace bgfx

#elif BX_PLATFORM_NACL
#	include <ppapi/c/ppb_graphics_3d.h>
#	include <ppapi/c/ppb_instance.h>

namespace bgfx
{
	typedef void (*PostSwapBuffersFn)(uint32_t _width, uint32_t _height);

	///
	bool naclSetInterfaces(::PP_Instance, const ::PPB_Instance*, const ::PPB_Graphics3D*, PostSwapBuffersFn);

} // namespace bgfx

#elif BX_PLATFORM_OSX
namespace bgfx
{
	///
	void osxSetNSWindow(void* _window, void* _nsgl = NULL);

} // namespace bgfx

#elif BX_PLATFORM_WINDOWS
#	include <windows.h>

namespace bgfx
{
	///
	void winSetHwnd(::HWND _window);

} // namespace bgfx

#elif BX_PLATFORM_WINRT
#   include <Unknwn.h>

namespace bgfx
{
	///
	void winrtSetWindow(IUnknown* _window);

} // namespace bgfx

#endif // BX_PLATFORM_

#if defined(_SDL_H)
// If SDL.h is included before bgfxplatform.h we can enable SDL window
// interop convenience code.

#	include <SDL2/SDL_syswm.h>

namespace bgfx
{
	///
	inline bool sdlSetWindow(SDL_Window* _window)
	{
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi) )
		{
			return false;
		}

#	if BX_PLATFORM_LINUX || BX_PLATFORM_FREEBSD
		x11SetDisplayWindow(wmi.info.x11.display, wmi.info.x11.window);
#	elif BX_PLATFORM_OSX
		osxSetNSWindow(wmi.info.cocoa.window);
#	elif BX_PLATFORM_WINDOWS
		winSetHwnd(wmi.info.win.window);
#	endif // BX_PLATFORM_

		return true;
	}

} // namespace bgfx

#elif defined(_glfw3_h_)
// If GLFW/glfw3.h is included before bgfxplatform.h we can enable GLFW3
// window interop convenience code.

#	if BX_PLATFORM_LINUX || BX_PLATFORM_FREEBSD
#		define GLFW_EXPOSE_NATIVE_X11
#		define GLFW_EXPOSE_NATIVE_GLX
#	elif BX_PLATFORM_OSX
#		define GLFW_EXPOSE_NATIVE_COCOA
#		define GLFW_EXPOSE_NATIVE_NSGL
#	elif BX_PLATFORM_WINDOWS
#		define GLFW_EXPOSE_NATIVE_WIN32
#		define GLFW_EXPOSE_NATIVE_WGL
#	endif //
#	include <GLFW/glfw3native.h>

namespace bgfx
{
	inline void glfwSetWindow(GLFWwindow* _window)
	{
#	if BX_PLATFORM_LINUX || BX_PLATFORM_FREEBSD
		::Display* display = glfwGetX11Display();
		::Window   window  = glfwGetX11Window(_window);
		void* glx          = glfwGetGLXContext(_window);
		x11SetDisplayWindow(display, window, glx);
#	elif BX_PLATFORM_OSX
		void* window = glfwGetCocoaWindow(_window);
		void* nsgl   = glfwGetNSGLContext(_window);
		osxSetNSWindow(window, nsgl);
#	elif BX_PLATFORM_WINDOWS
		HWND hwnd = glfwGetWin32Window(_window);
		winSetHwnd(hwnd);
#	endif // BX_PLATFORM_WINDOWS
	}

} // namespace bgfx

#endif // defined(_SDL_H)

#endif // BGFX_PLATFORM_H_HEADER_GUARD
