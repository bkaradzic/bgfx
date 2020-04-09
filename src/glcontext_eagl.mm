/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
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

	static void* s_opengles = NULL;

	struct SwapChainGL
	{
		SwapChainGL(EAGLContext *_context, CAEAGLLayer *_layer)
			: m_context(_context)
			, m_fbo(0)
			, m_colorRbo(0)
			, m_depthStencilRbo(0)
		{
			_layer.contentsScale = [UIScreen mainScreen].scale;

			_layer.opaque = [_layer.style valueForKey:@"opaque"] == nil
				? true
				: [[_layer.style valueForKey:@"opaque"] boolValue]
				;

			_layer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys
				: [NSNumber numberWithBool:false]
				, kEAGLDrawablePropertyRetainedBacking
				, kEAGLColorFormatRGBA8
				, kEAGLDrawablePropertyColorFormat
				, nil
				];

			[EAGLContext setCurrentContext:_context];

			GL_CHECK(glGenFramebuffers(1, &m_fbo) );
			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo) );

			GL_CHECK(glGenRenderbuffers(1, &m_colorRbo) );
			GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_colorRbo) );

			[_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_layer];
			GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRbo) );

			GLint width;
			GLint height;
			GL_CHECK(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width) );
			GL_CHECK(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height) );
			BX_TRACE("Screen size: %d x %d", width, height);

			m_width = width;
			m_height = height;
			m_layer = _layer;

			createFrameBuffers(m_width, m_height);
		}

		~SwapChainGL()
		{
			destroyFrameBuffers();
		}

		void destroyFrameBuffers()
		{
			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0) );
			GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0) );
			GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0) );
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
		}

		void createFrameBuffers(GLint _width, GLint _height)
		{
			GL_CHECK(glGenRenderbuffers(1, &m_depthStencilRbo) );
			GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilRbo) );
			GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height) );
			GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRbo) );
			GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRbo) );

			GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			BX_CHECK(GL_FRAMEBUFFER_COMPLETE == err, "glCheckFramebufferStatus failed 0x%08x", err);
			BX_UNUSED(err);

			makeCurrent();

			GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f) );
			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );

			swapBuffers();

			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );

			swapBuffers();
		}

		void makeCurrent()
		{
			[EAGLContext setCurrentContext:m_context];
			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo) );

			GLint newWidth = m_layer.bounds.size.width*[UIScreen mainScreen].scale;
			GLint newHeight = m_layer.bounds.size.height*[UIScreen mainScreen].scale;
			resize(newWidth, newHeight);
		}

		void resize(GLint _width, GLint _height)
		{
			if (m_width  == _width
			&&  m_height == _height)
			{
				return;
			}

			destroyFrameBuffers();

			m_width = _width;
			m_height = _height;

			createFrameBuffers(m_width, m_height);
		}

		void swapBuffers()
		{
			GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_colorRbo) );
			[m_context presentRenderbuffer:GL_RENDERBUFFER];
		}

		EAGLContext* m_context;

		CAEAGLLayer *m_layer;
		GLuint m_fbo;
		GLuint m_colorRbo;
		GLuint m_depthStencilRbo;
		GLint m_width;
		GLint m_height;
	};

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		s_opengles = bx::dlopen("/System/Library/Frameworks/OpenGLES.framework/OpenGLES");
		BX_CHECK(NULL != s_opengles, "OpenGLES dynamic library is not found!");

		BX_UNUSED(_width, _height);
		CAEAGLLayer* layer = (__bridge CAEAGLLayer*)g_platformData.nwh;
		layer.opaque = [layer.style valueForKey:@"opaque"] == nil ? true : [[layer.style valueForKey:@"opaque"] boolValue];

		layer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys
			: [NSNumber numberWithBool:false]
			, kEAGLDrawablePropertyRetainedBacking
			, kEAGLColorFormatRGBA8
			, kEAGLDrawablePropertyColorFormat
			, nil
			];

		EAGLContext* context = (__bridge EAGLContext*)g_platformData.context;
		if (NULL == context)
		{
			context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
			if (NULL == context)
			{
				context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
			}
		}
		BX_CHECK(NULL != context, "No valid OpenGLES context.");

		m_context = (__bridge void*)context;
		[EAGLContext setCurrentContext:context];
		[CATransaction flush];

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
		GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height) );
		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRbo) );
		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRbo) );

		BX_CHECK(GL_FRAMEBUFFER_COMPLETE ==  glCheckFramebufferStatus(GL_FRAMEBUFFER)
			, "glCheckFramebufferStatus failed 0x%08x"
			, glCheckFramebufferStatus(GL_FRAMEBUFFER)
			);

		makeCurrent();
		GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f) );
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );
		swap(NULL);
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );
		swap(NULL);

		import();

		g_internalData.context = m_context;
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

		EAGLContext* context = (__bridge EAGLContext*)m_context;

		bx::dlclose(s_opengles);
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		BX_UNUSED(_width, _height, _flags);
		BX_TRACE("resize context");

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

		GL_CHECK(glGenFramebuffers(1, &m_fbo) );
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo) );

		GL_CHECK(glGenRenderbuffers(1, &m_colorRbo) );
		GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_colorRbo) );

		[((__bridge EAGLContext*)m_context) renderbufferStorage:GL_RENDERBUFFER fromDrawable:(__bridge CAEAGLLayer*)g_platformData.nwh];
		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRbo) );

		GLint width;
		GLint height;
		GL_CHECK(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width) );
		GL_CHECK(glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height) );
		BX_TRACE("Screen size: %d x %d", width, height);

		GL_CHECK(glGenRenderbuffers(1, &m_depthStencilRbo) );
		GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilRbo) );
		GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height) );
		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRbo) );
		GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilRbo) );

		BX_CHECK(GL_FRAMEBUFFER_COMPLETE ==  glCheckFramebufferStatus(GL_FRAMEBUFFER)
			, "glCheckFramebufferStatus failed 0x%08x"
			, glCheckFramebufferStatus(GL_FRAMEBUFFER)
			);
	}

	uint64_t GlContext::getCaps() const
	{
		return BGFX_CAPS_SWAP_CHAIN;
	}

	SwapChainGL* GlContext::createSwapChain(void* _nwh)
	{
		return BX_NEW(g_allocator, SwapChainGL)(/*m_display, m_config,*/ (__bridge EAGLContext*)m_context, (__bridge CAEAGLLayer*)_nwh);
	}

	void GlContext::destroySwapChain(SwapChainGL* _swapChain)
	{
		BX_DELETE(g_allocator, _swapChain);
	}

	void GlContext::swap(SwapChainGL* _swapChain)
	{
		makeCurrent(_swapChain);

		if (NULL == _swapChain)
		{
			GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_colorRbo) );
			EAGLContext* context = (__bridge EAGLContext*)m_context;
			[context presentRenderbuffer:GL_RENDERBUFFER];
		}
		else
		{
		    _swapChain->swapBuffers();
		}
	}

	void GlContext::makeCurrent(SwapChainGL* _swapChain)
	{
		if (m_current != _swapChain)
		{
			m_current = _swapChain;

			if (NULL == _swapChain)
			{
				[EAGLContext setCurrentContext:(__bridge EAGLContext*)m_context];
				GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo) );
			}
			else
			{
				_swapChain->makeCurrent();
			}
		}
	}

	void GlContext::import()
	{
		BX_TRACE("Import:");
#	define GL_EXTENSION(_optional, _proto, _func, _import)                        \
		{                                                                         \
			if (_func == NULL)                                                    \
			{                                                                     \
				_func = (_proto)bx::dlsym(s_opengles, #_import);                  \
				BX_TRACE("%p " #_func " (" #_import ")", _func);                  \
			}                                                                     \
			BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize      \
				, "Failed to create OpenGLES context. EAGLGetProcAddress(\"%s\")" \
				, #_import);                                                      \
		}
#	include "glimports.h"
	}

} /* namespace gl */ } // namespace bgfx

#endif // BX_PLATFORM_IOS && (BGFX_CONFIG_RENDERER_OPENGLES|BGFX_CONFIG_RENDERER_OPENGL)
