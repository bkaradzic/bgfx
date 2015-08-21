/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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
			: m_current(NULL)
			, m_context(0)
			, m_visualInfo(NULL)
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

		SwapChainGL* m_current;
		GLXContext m_context;
		XVisualInfo* m_visualInfo;
	};
} /* namespace gl */ } // namespace bgfx

#endif // BGFX_USE_GLX

#endif // BGFX_GLCONTEXT_GLX_H_HEADER_GUARD
