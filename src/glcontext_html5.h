/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_GLCONTEXT_HTML5_H_HEADER_GUARD
#define BGFX_GLCONTEXT_HTML5_H_HEADER_GUARD

#if BGFX_USE_HTML5

namespace bgfx { namespace gl
{
	struct SwapChainGL;

	struct GlContext
	{
		GlContext()
			: m_current(NULL)
			, m_primary(NULL)
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

		void import(int webGLVersion);

		bool isValid() const
		{
			return NULL != m_primary;
		}

        SwapChainGL* m_current;
		SwapChainGL* m_primary;
	};
} /* namespace gl */ } // namespace bgfx

#endif // BGFX_USE_HTML5

#endif // BGFX_GLCONTEXT_HTML5_H_HEADER_GUARD
