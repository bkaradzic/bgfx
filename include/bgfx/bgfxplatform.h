/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
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
	/// Render frame enum.
	///
	/// @attention C99 equivalent is `bgfx_render_frame_t`.
	///
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

	/// Render frame.
	///
	/// @returns Current renderer state. See: `bgfx::RenderFrame`.
	///
	/// @warning This call should be only used on platforms that don't
	///   allow creating separate rendering thread. If it is called before
	///   to bgfx::init, render thread won't be created by bgfx::init call.
	RenderFrame::Enum renderFrame();

	/// Platform data.
	///
	/// @attention C99 equivalent is `bgfx_platform_data_t`.
	///
	struct PlatformData
	{
		void* ndt;          //!< Native display type
		void* nwh;          //!< Native window handle
		void* context;      //!< GL context, or D3D device
		void* backBuffer;   //!< GL backbuffer, or D3D render target view
		void* backBufferDS; //!< Backbuffer depth/stencil.
	};

	/// Set platform data.
	///
	/// @warning Must be called before `bgfx::init`.
	///
	/// @attention C99 equivalent is `bgfx_set_platform_data`.
	///
	void setPlatformData(const PlatformData& _hooks);

} // namespace bgfx

#if BX_PLATFORM_ANDROID
#	include <android/native_window.h>

namespace bgfx
{
	///
	inline void androidSetWindow(::ANativeWindow* _window)
	{
		PlatformData pd;
		pd.ndt          = NULL;
		pd.nwh          = _window;
		pd.context      = NULL;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		setPlatformData(pd);
	}

} // namespace bgfx

#elif BX_PLATFORM_IOS
namespace bgfx
{
	///
	inline void iosSetEaglLayer(void* _window)
	{
		PlatformData pd;
		pd.ndt          = NULL;
		pd.nwh          = _window;
		pd.context      = NULL;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		setPlatformData(pd);
	}

} // namespace bgfx

#elif BX_PLATFORM_BSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI

namespace bgfx
{
	///
	inline void x11SetDisplayWindow(void* _display, uint32_t _window, void* _glx = NULL)
	{
		PlatformData pd;
		pd.ndt          = _display;
		pd.nwh          = (void*)(uintptr_t)_window;
		pd.context      = _glx;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		setPlatformData(pd);
	}

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
	inline void osxSetNSWindow(void* _window, void* _nsgl = NULL)
	{
		PlatformData pd;
		pd.ndt          = NULL;
		pd.nwh          = _window;
		pd.context      = _nsgl;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		setPlatformData(pd);
	}

} // namespace bgfx

#elif BX_PLATFORM_WINDOWS
#	include <windows.h>

namespace bgfx
{
	///
	inline void winSetHwnd(::HWND _window)
	{
		PlatformData pd;
		pd.ndt          = NULL;
		pd.nwh          = _window;
		pd.context      = NULL;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		setPlatformData(pd);
	}

} // namespace bgfx

#elif BX_PLATFORM_WINRT
#   include <Unknwn.h>

namespace bgfx
{
	///
	inline void winrtSetWindow(::IUnknown* _window)
	{
		PlatformData pd;
		pd.ndt          = NULL;
		pd.nwh          = _window;
		pd.context      = NULL;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		setPlatformData(pd);
	}

} // namespace bgfx

#endif // BX_PLATFORM_

#if defined(_SDL_syswm_h)
// If SDL_syswm.h is included before bgfxplatform.h we can enable SDL window
// interop convenience code.

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

		PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
		pd.ndt          = wmi.info.x11.display;
		pd.nwh          = (void*)(uintptr_t)wmi.info.x11.window;
#	elif BX_PLATFORM_OSX
		pd.ndt          = NULL;
		pd.nwh          = wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
		pd.ndt          = NULL;
		pd.nwh          = wmi.info.win.window;
#	endif // BX_PLATFORM_
		pd.context      = NULL;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		setPlatformData(pd);

		return true;
	}

} // namespace bgfx

#elif defined(_glfw3_h_)
// If GLFW/glfw3.h is included before bgfxplatform.h we can enable GLFW3
// window interop convenience code.

#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
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
		PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
		pd.ndt          = glfwGetX11Display();
		pd.nwh          = (void*)(uintptr_t)glfwGetX11Window(_window);
		pd.context      = glfwGetGLXContext(_window);
#	elif BX_PLATFORM_OSX
		pd.ndt          = NULL;
		pd.nwh          = glfwGetCocoaWindow(_window);
		pd.context      = glfwGetNSGLContext(_window);
#	elif BX_PLATFORM_WINDOWS
		pd.ndt          = NULL;
		pd.nwh          = glfwGetWin32Window(_window);
		pd.context      = NULL;
#	endif // BX_PLATFORM_WINDOWS
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		setPlatformData(pd);
	}

} // namespace bgfx

#endif // defined(_SDL_H)

#endif // BGFX_PLATFORM_H_HEADER_GUARD
