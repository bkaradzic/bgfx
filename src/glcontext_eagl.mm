/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BX_PLATFORM_IOS && (BGFX_CONFIG_RENDERER_OPENGLES|BGFX_CONFIG_RENDERER_OPENGL)
#	include <UIKit/UIKit.h>
#	include <QuartzCore/CAEAGLLayer.h>
#	include "renderer_gl.h"

namespace bgfx { namespace gl
{
#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func = NULL
#	include "glimports.h"

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_width, _height);
		CAEAGLLayer* layer = (CAEAGLLayer*)g_bgfxEaglLayer;
		layer.opaque = true;

		layer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys
										: [NSNumber numberWithBool:false]
										, kEAGLDrawablePropertyRetainedBacking
										, kEAGLColorFormatRGBA8
										, kEAGLDrawablePropertyColorFormat
										, nil
										];

		EAGLContext* context = [ [EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
		BX_CHECK(NULL != context, "Failed to create kEAGLRenderingAPIOpenGLES2 context.");
		m_context = (void*)context;
		[EAGLContext setCurrentContext:context];

		GL_CHECK(glGenFramebuffers(1, &m_fbo) );
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo) );

		GL_CHECK(glGenRenderbuffers(1, &m_colorRbo) );
		GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_colorRbo) );

		[context renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRbo) );

		GLint width;
		GLint height;
		GL_CHECK(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width) );
		GL_CHECK(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height) );
		BX_TRACE("Screen size: %d x %d", width, height);

		GL_CHECK(glGenRenderbuffers(1, &m_depthStencilRbo) );
		GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilRbo) );
		GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, width, height) ); // from OES_packed_depth_stencil
		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRbo) );
		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRbo) );
        
		BX_CHECK(GL_FRAMEBUFFER_COMPLETE ==  glCheckFramebufferStatus(GL_FRAMEBUFFER)
			, "glCheckFramebufferStatus failed 0x%08x"
			, glCheckFramebufferStatus(GL_FRAMEBUFFER)
			);
	}

	void GlContext::destroy()
	{
		if (0 != m_fbo)
		{
			GL_CHECK(glDeleteFramebuffers(1, &m_fbo) );
			m_fbo = 0;
		}

		if (0 != m_colorRbo)
		{
			GL_CHECK(glDeleteRenderbuffers(1, &m_colorRbo) );
			m_colorRbo = 0;
		}

		if (0 != m_depthStencilRbo)
		{
			GL_CHECK(glDeleteRenderbuffers(1, &m_depthStencilRbo) );
			m_depthStencilRbo = 0;
		}

		EAGLContext* context = (EAGLContext*)m_context;
		[context release];
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, bool _vsync)
	{
		BX_UNUSED(_width, _height, _vsync);
		BX_TRACE("resize context");
	}

	bool GlContext::isSwapChainSupported()
	{
		return false;
	}

	SwapChainGL* GlContext::createSwapChain(void* /*_nwh*/)
	{
		BX_CHECK(false, "Shouldn't be called!");
		return NULL;
	}

	void GlContext::destroySwapChain(SwapChainGL*  /*_swapChain*/)
	{
		BX_CHECK(false, "Shouldn't be called!");
	}

	void GlContext::swap(SwapChainGL* _swapChain)
	{
		BX_CHECK(NULL == _swapChain, "Shouldn't be called!"); BX_UNUSED(_swapChain);
		GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_colorRbo) );
		EAGLContext* context = (EAGLContext*)m_context;
		[context presentRenderbuffer:GL_RENDERBUFFER];
	}

	void GlContext::makeCurrent(SwapChainGL* /*_swapChain*/)
	{
	}

	void GlContext::import()
	{
	}

} /* namespace gl */ } // namespace bgfx

#endif // BX_PLATFORM_IOS && (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
