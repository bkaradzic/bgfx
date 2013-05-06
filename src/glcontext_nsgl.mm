/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

#	if BX_PLATFORM_OSX

#		include <mach-o/dyld.h>
#		include <dlfcn.h>
#		include <stdlib.h>
#		include <string.h>
#		include <Cocoa/Cocoa.h>
#		include <OpenGL/OpenGL.h>

static void* NSGLGetProcAddress (const char* name) {
	static void* const dylib =
	dlopen("/System/Library/Frameworks/"
		   "OpenGL.framework/Versions/Current/OpenGL",
		   RTLD_LAZY);
    return dylib ? dlsym(dylib, name) : NULL;
}

namespace bgfx
{

#	define GL_IMPORT(_optional, _proto, _func) _proto _func
#		include "glimports.h"
#	undef GL_IMPORT
	
	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		NSWindow* nsWindow = (NSWindow*)g_bgfxNSWindow;
		
		NSOpenGLPixelFormatAttribute pixelFormatAttributes[] = {
			NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersionLegacy, //NSOpenGLProfileVersion3_2Core,
			NSOpenGLPFAColorSize    , 24,
			NSOpenGLPFAAlphaSize    ,  8,
			NSOpenGLPFADepthSize    , 24,
			NSOpenGLPFAStencilSize  ,  8,
			NSOpenGLPFADoubleBuffer ,
			NSOpenGLPFAAccelerated  ,
			NSOpenGLPFANoRecovery   ,
			0
		};
		
		NSOpenGLPixelFormat* pixelFormat =
		[[NSOpenGLPixelFormat alloc]
		 initWithAttributes:pixelFormatAttributes];
		
		NSRect glViewRect = [[nsWindow contentView] bounds];
		
		NSOpenGLView* glView =
		[[NSOpenGLView alloc]
		 initWithFrame:glViewRect
		 pixelFormat:pixelFormat];
		
		[pixelFormat release];
		
		[nsWindow setContentView:glView];
		
		NSOpenGLContext* glContext = [glView openGLContext];
		[glContext makeCurrentContext];
		
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
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, bool _vsync)
	{
	}

	void GlContext::swap()
	{
		NSOpenGLContext* glContext = (NSOpenGLContext*)m_context;
		[glContext makeCurrentContext];
		[glContext flushBuffer];
	}

	void GlContext::import()
	{
#	define GL_IMPORT(_optional, _proto, _func) \
		{ \
			_func = (_proto)NSGLGetProcAddress(#_func); \
			BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGL context. NSGLGetProcAddress(\"%s\")", #_func); \
		}
#	include "glimports.h"
#	undef GL_IMPORT
	}

} // namespace bgfx

#	endif // BX_PLATFORM_OSX
#endif //(BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
