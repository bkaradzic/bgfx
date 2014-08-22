/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BX_PLATFORM_OSX && (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"
#	include <Cocoa/Cocoa.h>
#	include <bx/os.h>

namespace bgfx
{

#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func
#	include "glimports.h"
	
	static void* s_opengl = NULL;

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_width, _height);

		s_opengl = bx::dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL");
		BX_CHECK(NULL != s_opengl, "OpenGL dynamic library is not found!");

		NSWindow* nsWindow = (NSWindow*)g_bgfxNSWindow;

		NSOpenGLPixelFormatAttribute profile =
#if BGFX_CONFIG_RENDERER_OPENGL >= 31
			NSOpenGLProfileVersion3_2Core
#else
			NSOpenGLProfileVersionLegacy
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 31
			;

		NSOpenGLPixelFormatAttribute pixelFormatAttributes[] = {
			NSOpenGLPFAOpenGLProfile, profile,
			NSOpenGLPFAColorSize,     24,
			NSOpenGLPFAAlphaSize,     8,
			NSOpenGLPFADepthSize,     24,
			NSOpenGLPFAStencilSize,   8,
			NSOpenGLPFADoubleBuffer,  true,
			NSOpenGLPFAAccelerated,   true,
			NSOpenGLPFANoRecovery,    true,
			0,                        0,
		};

		NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
		BGFX_FATAL(NULL != pixelFormat, Fatal::UnableToInitialize, "Failed to initialize pixel format.");

		NSRect glViewRect = [[nsWindow contentView] bounds];
		NSOpenGLView* glView = [[NSOpenGLView alloc] initWithFrame:glViewRect pixelFormat:pixelFormat];
		
		[pixelFormat release];
		[nsWindow setContentView:glView];
		
		NSOpenGLContext* glContext = [glView openGLContext];
		BGFX_FATAL(NULL != glContext, Fatal::UnableToInitialize, "Failed to initialize GL context.");

		[glContext makeCurrentContext];
		GLint interval = 0;
		[glContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];
		
		m_view    = glView;
		m_context = glContext;

		import();
	}

	void GlContext::destroy()
	{
		NSOpenGLView* glView = (NSOpenGLView*)m_view;
		m_view = 0;
		m_context = 0;
		[glView release];

		bx::dlclose(s_opengl);
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, bool _vsync)
	{
		BX_UNUSED(_width, _height, _vsync);

		GLint interval = _vsync ? 1 : 0;
		NSOpenGLContext* glContext = (NSOpenGLContext*)m_context;
		[glContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];
	}

	void GlContext::swap()
	{
		NSOpenGLContext* glContext = (NSOpenGLContext*)m_context;
		[glContext makeCurrentContext];
		[glContext flushBuffer];
	}

	void GlContext::import()
	{
		BX_TRACE("Import:");
#	define GL_EXTENSION(_optional, _proto, _func, _import) \
				{ \
					if (_func == NULL) \
					{ \
						_func = (_proto)bx::dlsym(s_opengl, #_import); \
						BX_TRACE("%p " #_func " (" #_import ")", _func); \
					} \
					BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGL context. NSGLGetProcAddress(\"%s\")", #_import); \
				}
#	include "glimports.h"
	}

} // namespace bgfx

#endif // BX_PLATFORM_OSX && (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
