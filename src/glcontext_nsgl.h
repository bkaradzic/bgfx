/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_GLCONTEXT_NSGL_H_HEADER_GUARD
#define BGFX_GLCONTEXT_NSGL_H_HEADER_GUARD

#if BX_PLATFORM_OSX

namespace bgfx { namespace gl
{
	struct SwapChainGL;

	struct GlContext
	{
		GlContext()
			: m_context(0)
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

		void* m_view;
		void* m_context;
	};
} /* namespace gl */ } // namespace bgfx

#endif // BX_PLATFORM_OSX

#endif // BGFX_GLCONTEXT_NSGL_H_HEADER_GUARD
