/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_GLCONTEXT_GLX_H_HEADER_GUARD
#define BGFX_GLCONTEXT_GLX_H_HEADER_GUARD

#if BGFX_USE_GLX

#	include <X11/Xlib.h>
#	include <GL/glx.h>

namespace bgfx { namespace gl
{
	struct SwapChainGL;

	struct GlContext
	{
		GlContext()
		{
		}

		void create(uint32_t _width, uint32_t _height);
		void destroy();
		void resize(uint32_t _width, uint32_t _height, uint32_t _flags);

		uint64_t getCaps() const;
		SwapChainGL* createSwapChain(void* _nwh);
		void destroySwapChain(SwapChainGL*  _swapChain);
		void swap(SwapChainGL* _swapChain = NULL);
		void makeCurrent(SwapChainGL* _swapChain = NULL);

		void import();

		bool isValid() const
		{
			return 0 != m_context;
		}

		SwapChainGL* m_current = NULL;
		GLXContext m_context = 0;
		XVisualInfo* m_visualInfo = NULL;
		::Display* m_display = NULL;
	};
} /* namespace gl */ } // namespace bgfx

#endif // BGFX_USE_GLX

#endif // BGFX_GLCONTEXT_GLX_H_HEADER_GUARD
