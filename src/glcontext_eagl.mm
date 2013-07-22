/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BX_PLATFORM_IOS && (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
#	include <UIKit/UIKit.h>
#	include <QuartzCore/CAEAGLLayer.h>
#	include "renderer_gl.h"

namespace bgfx
{
	void GlContext::create(uint32_t _width, uint32_t _height)
	{
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

		GL_CHECK(glGenRenderbuffers(1, &m_depthRbo) );
		GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_depthRbo) );
		GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height) );
		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRbo) );

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

		if (0 != m_depthRbo)
		{
			GL_CHECK(glDeleteRenderbuffers(1, &m_depthRbo) );
			m_depthRbo = 0;
		}

		EAGLContext* context = (EAGLContext*)m_context;
		[context release];
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, bool _vsync)
	{
		BX_TRACE("resize context");
	}

	void GlContext::swap()
	{
		GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_colorRbo) );
		EAGLContext* context = (EAGLContext*)m_context;
		[context presentRenderbuffer:GL_RENDERBUFFER];
	}

	void GlContext::import()
	{
	}

} // namespace bgfx

#endif // BX_PLATFORM_IOS && (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
