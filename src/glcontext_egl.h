/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_GLCONTEXT_EGL_H_HEADER_GUARD
#define BGFX_GLCONTEXT_EGL_H_HEADER_GUARD

#if BGFX_USE_EGL

#include <EGL/egl.h>

namespace bgfx
{
	struct GlContext
	{
		GlContext()
			: m_context(NULL)
			, m_display(NULL)
			, m_surface(NULL)
		{
		}

		void create(uint32_t _width, uint32_t _height);
		void destroy();
		void resize(uint32_t _width, uint32_t _height, bool _vsync);
		void swap();
		void import();

		bool isValid() const
		{
			return NULL != m_context;
		}

		void* m_eglLibrary;
		EGLContext m_context;
		EGLDisplay m_display;
		EGLSurface m_surface;
	};
} // namespace bgfx

#endif // BGFX_USE_EGL

#endif // BGFX_GLCONTEXT_EGL_H_HEADER_GUARD
