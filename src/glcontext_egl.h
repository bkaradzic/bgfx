/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_GLCONTEXT_EGL_H_HEADER_GUARD
#define BGFX_GLCONTEXT_EGL_H_HEADER_GUARD

#if BGFX_USE_EGL

#include <EGL/egl.h>
#include <EGL/eglext.h>

struct wl_egl_window;

// EGL pulls X11 crap...
#if defined(None)
#	undef None
#endif // defined(None)

#if defined(Success)
#	undef Success
#endif // defined(Success)

#if defined(Status)
#	undef Status
#endif // defined(Status)

namespace bgfx { namespace gl
{
	struct SwapChainGL;

	struct GlContext
	{
		GlContext()
			: m_eglDll(NULL)
			, m_current(NULL)
			, m_context(NULL)
			, m_display(NULL)
			, m_surface(NULL)
#if BX_PLATFORM_LINUX
			, m_waylandEglDll(NULL)
			, m_eglWindow(NULL)
#endif
			, m_msaaContext(false)
		{
		}

		void create(uint32_t _width, uint32_t _height, uint32_t _flags);
		void destroy();
		void resize(uint32_t _width, uint32_t _height, uint32_t _flags);

		uint64_t getCaps() const;
		SwapChainGL* createSwapChain(void* _nwh, int _w, int _h);
		void destroySwapChain(SwapChainGL*  _swapChain);
		void swap(SwapChainGL* _swapChain = NULL);
		void makeCurrent(SwapChainGL* _swapChain = NULL);

		void import();

		bool isValid() const
		{
			return NULL != m_context;
		}

		void* m_eglDll;
		SwapChainGL* m_current;
		EGLConfig  m_config;
		EGLContext m_context;
		EGLDisplay m_display;
		EGLSurface m_surface;

#if BX_PLATFORM_LINUX
		void*  m_waylandEglDll;
		struct wl_egl_window *m_eglWindow;
#endif

		// true when MSAA is handled by the context instead of using MSAA FBO
		bool m_msaaContext;
	};
} /* namespace gl */ } // namespace bgfx

#endif // BGFX_USE_EGL

#endif // BGFX_GLCONTEXT_EGL_H_HEADER_GUARD
