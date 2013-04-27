/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BX_PLATFORM_NACL & (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

namespace bgfx
{
#	define GL_IMPORT(_optional, _proto, _func) _proto _func
#		include "glimports.h"
#	undef GL_IMPORT

	void naclSwapCompleteCb(void* _data, int32_t _result);

	PP_CompletionCallback naclSwapComplete = 
	{
		naclSwapCompleteCb,
		NULL,
		PP_COMPLETIONCALLBACK_FLAG_NONE
	};

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		int32_t attribs[] =
		{
			PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 8,
			PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 24,
			PP_GRAPHICS3DATTRIB_STENCIL_SIZE, 8,
			PP_GRAPHICS3DATTRIB_SAMPLES, 0,
			PP_GRAPHICS3DATTRIB_SAMPLE_BUFFERS, 0,
			PP_GRAPHICS3DATTRIB_WIDTH, int32_t(_width),
			PP_GRAPHICS3DATTRIB_HEIGHT, int32_t(_height),
			PP_GRAPHICS3DATTRIB_NONE
		};

		m_context = m_graphicsInterface->Create(m_instance, 0, attribs);
		m_instInterface->BindGraphics(m_instance, m_context);
		glSetCurrentContextPPAPI(m_context);
		m_graphicsInterface->SwapBuffers(m_context, naclSwapComplete);
	}

	void GlContext::destroy()
	{
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, bool /*_vsync*/)
	{
		m_graphicsInterface->ResizeBuffers(m_context, _width, _height);
	}

	void GlContext::swap()
	{
		glSetCurrentContextPPAPI(m_context);
		m_graphicsInterface->SwapBuffers(m_context, naclSwapComplete);
	}

	void GlContext::import()
	{
	}
} // namespace bgfx

#endif // BX_PLATFORM_NACL & (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
