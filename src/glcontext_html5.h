/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
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
			, m_msaaContext(false)
		{
		}

		void create(const Resolution& _resolution);
		void destroy();
		void resize(const Resolution& _resolution);

		uint64_t getCaps() const;
		SwapChainGL* createSwapChain(void* _nwh, int32_t _width, int32_t _height);
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
		// true when MSAA is handled by the context instead of using MSAA FBO
		bool m_msaaContext;
	};
} /* namespace gl */ } // namespace bgfx

#endif // BGFX_USE_HTML5

#endif // BGFX_GLCONTEXT_HTML5_H_HEADER_GUARD
