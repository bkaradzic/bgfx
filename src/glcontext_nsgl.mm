/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BX_PLATFORM_OSX && (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"
#	include <AvailabilityMacros.h>
#	include <Cocoa/Cocoa.h>
#	include <bx/os.h>

BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wdeprecated-declarations")

namespace bgfx { namespace gl
{

#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func
#	include "glimports.h"

	struct SwapChainGL
	{
		SwapChainGL(void* _nwh,NSOpenGLContext *_context)
		{
			NSObject* nwh=(NSObject*)_nwh;

			NSWindow* nsWindow = nil;
			NSView* contentView = nil;
			if ([nwh isKindOfClass:[NSView class]])
			{
				contentView = (NSView*)nwh;
			}
			else if ([nwh isKindOfClass:[NSWindow class]])
			{
				nsWindow = (NSWindow*)nwh;
				contentView = [nsWindow contentView];
			}

#if defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
			NSOpenGLPixelFormatAttribute profile =
#if BGFX_CONFIG_RENDERER_OPENGL >= 31
				NSOpenGLProfileVersion3_2Core
#else
				NSOpenGLProfileVersionLegacy
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 31
				;
#endif // defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)

			NSOpenGLPixelFormatAttribute pixelFormatAttributes[] = {
#if defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
				NSOpenGLPFAOpenGLProfile, profile,
#endif // defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
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

			NSRect glViewRect = [contentView bounds];
			NSOpenGLView* glView = [[NSOpenGLView alloc] initWithFrame:glViewRect pixelFormat:pixelFormat];


			// GLFW creates a helper contentView that handles things like keyboard and drag and
			// drop events. We don't want to clobber that view if it exists. Instead we just
			// add ourselves as a subview and make the view resize automatically.
			if (nil != contentView)
			{
				[glView setAutoresizingMask:( NSViewHeightSizable |
						NSViewWidthSizable |
						NSViewMinXMargin |
						NSViewMaxXMargin |
						NSViewMinYMargin |
						NSViewMaxYMargin )];
				[contentView addSubview:glView];
			}
			else
			{
				if (nil != nsWindow)
					[nsWindow setContentView:glView];
			}

			NSOpenGLContext* glContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:_context];
			BGFX_FATAL(NULL != glContext, Fatal::UnableToInitialize, "Failed to initialize GL context.");

			void (^attachBlock)(void) = ^(void) {
				[glView setOpenGLContext: glContext];
				[glContext setView:glView];
			};

			if([NSThread isMainThread])
			{
				attachBlock();
			}
			else
			{
				dispatch_sync(dispatch_get_main_queue(),attachBlock);
			}

			[pixelFormat release];

			[glContext makeCurrentContext];
			GLint interval = 0;
			[glContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];


			m_view    = glView;
			m_context = glContext;
		}

		~SwapChainGL()
		{
			if(m_context!=nil) [m_context release];
			if(m_view!=nil) [m_view release];
		}

		void makeCurrent()
		{
			[m_context makeCurrentContext];
		}

		void swapBuffers()
		{
			[m_context makeCurrentContext];
			[m_context flushBuffer];
		}

		NSOpenGLView *m_view;
		NSOpenGLContext *m_context;
	};

	class AutoreleasePoolHolder
	{
	public:
		AutoreleasePoolHolder() : m_pool([[NSAutoreleasePool alloc] init])
		{
		}

		~AutoreleasePoolHolder()
		{
			[m_pool release];
		}

	private:
		AutoreleasePoolHolder(AutoreleasePoolHolder const&);

		NSAutoreleasePool* const m_pool;
	};

	static void* s_opengl = NULL;

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_width, _height);

		s_opengl = bx::dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL");
		BX_ASSERT(NULL != s_opengl, "OpenGL dynamic library is not found!");

		const AutoreleasePoolHolder pool;
		NSObject* nwh = (NSObject*)g_platformData.nwh;
		m_context = g_platformData.context;

		NSWindow* nsWindow = nil;
		NSView* contentView = nil;
		if ([nwh isKindOfClass:[NSView class]])
		{
			contentView = (NSView*)nwh;
		}
		else if ([nwh isKindOfClass:[NSWindow class]])
		{
			nsWindow = (NSWindow*)nwh;
			contentView = [nsWindow contentView];
		}

		if (NULL == g_platformData.context)
		{
#if defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
			NSOpenGLPixelFormatAttribute profile =
#if BGFX_CONFIG_RENDERER_OPENGL >= 31
				NSOpenGLProfileVersion3_2Core
#else
				NSOpenGLProfileVersionLegacy
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 31
				;
#endif // defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)

			NSOpenGLPixelFormatAttribute pixelFormatAttributes[] = {
#if defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
				NSOpenGLPFAOpenGLProfile, profile,
#endif // defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
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

			NSRect glViewRect = [contentView bounds];
			NSOpenGLView* glView = [[NSOpenGLView alloc] initWithFrame:glViewRect pixelFormat:pixelFormat];

			[pixelFormat release];
			// GLFW creates a helper contentView that handles things like keyboard and drag and
			// drop events. We don't want to clobber that view if it exists. Instead we just
			// add ourselves as a subview and make the view resize automatically.
			if (nil != contentView)
			{
				[glView setAutoresizingMask:( NSViewHeightSizable |
						NSViewWidthSizable |
						NSViewMinXMargin |
						NSViewMaxXMargin |
						NSViewMinYMargin |
						NSViewMaxYMargin )];
				[contentView addSubview:glView];
			}
			else
			{
				if (nil != nsWindow)
					[nsWindow setContentView:glView];
			}

			NSOpenGLContext* glContext = [glView openGLContext];
			BGFX_FATAL(NULL != glContext, Fatal::UnableToInitialize, "Failed to initialize GL context.");

			[glContext makeCurrentContext];
			GLint interval = 0;
			[glContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];

			// When initializing NSOpenGLView programatically (as we are), this sometimes doesn't
			// get hooked up properly (especially when there are existing window elements). This ensures
			// we are valid. Otherwise, you'll probably get a GL_INVALID_FRAMEBUFFER_OPERATION when
			// trying to glClear() for the first time.
			[glContext setView:glView];

			m_view    = glView;
			m_context = glContext;
		}
		else
		{
			[(NSOpenGLContext*)g_platformData.context makeCurrentContext];
		}

		import();

		g_internalData.context = m_context;
	}

	void GlContext::destroy()
	{
		if (NULL == g_platformData.context)
		{
			NSOpenGLView* glView = (NSOpenGLView*)m_view;
			[glView release];
		}

		m_view    = NULL;
		m_context = NULL;
		bx::dlclose(s_opengl);
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		BX_UNUSED(_width, _height);

#if defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
		bool hidpi = !!(_flags&BGFX_RESET_HIDPI);
        if (m_view)
        {
            NSOpenGLView* glView = (NSOpenGLView*)m_view;
            if ([glView respondsToSelector:@selector(setWantsBestResolutionOpenGLSurface:)])
                [glView setWantsBestResolutionOpenGLSurface:hidpi];
        }
#endif // defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)

		bool vsync = !!(_flags&BGFX_RESET_VSYNC);
		GLint interval = vsync ? 1 : 0;
		NSOpenGLContext* glContext = (NSOpenGLContext*)m_context;
		[glContext setValues:&interval forParameter:NSOpenGLCPSwapInterval];
		[glContext update];
	}

	uint64_t GlContext::getCaps() const
	{
		uint64_t caps = 0;
#if defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
		NSObject* nwh = (NSObject*)g_platformData.nwh;
		if ([nwh respondsToSelector:@selector(backingScaleFactor)] && (1.0f < [(id)nwh backingScaleFactor]))
			caps |= BGFX_CAPS_HIDPI;
#endif // defined(MAC_OS_X_VERSION_MAX_ALLOWED) && (MAC_OS_X_VERSION_MAX_ALLOWED >= 1070)
		caps |= BGFX_CAPS_SWAP_CHAIN;
		return caps;
	}

	SwapChainGL* GlContext::createSwapChain(void* _nwh)
	{
		return BX_NEW(g_allocator, SwapChainGL)(_nwh,(NSOpenGLContext*)m_context);
	}

	void GlContext::destroySwapChain(SwapChainGL* _swapChain)
	{
		BX_DELETE(g_allocator, _swapChain);
	}

	void GlContext::swap(SwapChainGL* _swapChain)
	{
		if (NULL == _swapChain)
		{
			NSOpenGLContext* glContext = (NSOpenGLContext*)m_context;
			[glContext makeCurrentContext];
			[glContext flushBuffer];
		}
		else
		{
			_swapChain->makeCurrent();
			_swapChain->swapBuffers();
		}
	}

	void GlContext::makeCurrent(SwapChainGL* _swapChain)
	{
		if (NULL == _swapChain)
		{
			NSOpenGLContext* glContext = (NSOpenGLContext*)m_context;
			[glContext makeCurrentContext];
		}
		else
		{
			_swapChain->makeCurrent();
		}
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
					BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGL context. GetProcAddress(\"%s\")", #_import); \
				}
#	include "glimports.h"
	}

} /* namespace gl */ } // namespace bgfx

void* nsglGetProcAddress(const GLubyte* _name)
{
	using namespace bgfx::gl;
	if (NULL == s_opengl)
	{
		s_opengl = bx::dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL");
	}
	return bx::dlsym(s_opengl, (const char*)_name);
}

#endif // BX_PLATFORM_OSX && (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
