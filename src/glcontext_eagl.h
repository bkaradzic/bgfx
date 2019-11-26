/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_GLCONTEXT_EAGL_H_HEADER_GUARD
#define BGFX_GLCONTEXT_EAGL_H_HEADER_GUARD

#if BX_PLATFORM_IOS

namespace bgfx { namespace gl
{
	struct SwapChainGL;

	struct GlContext
	{
		GlContext()
			: m_current(0)
			, m_context(0)
			, m_fbo(0)
			, m_colorRbo(0)
			, m_depthStencilRbo(0)
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

		GLuint getFbo()
		{
			return m_fbo;
		}

		bool isValid() const
		{
			return 0 != m_context;
		}

		SwapChainGL* m_current;
		void* m_context;

		GLuint m_fbo;
		GLuint m_colorRbo;
		GLuint m_depthStencilRbo;
	};
} /* namespace gl */ } // namespace bgfx

#endif // BX_PLATFORM_IOS

#endif // BGFX_GLCONTEXT_EAGL_H_HEADER_GUARD
