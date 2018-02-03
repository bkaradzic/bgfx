/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if (BX_PLATFORM_BSD || BX_PLATFORM_LINUX) && (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

#	if BGFX_USE_GLX
#		define GLX_GLXEXT_PROTOTYPES
#		include <glx/glxext.h>

// will include X11 which #defines None...
#undef None

namespace bgfx { namespace gl
{
	typedef int (*PFNGLXSWAPINTERVALMESAPROC)(uint32_t _interval);

	PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
	PFNGLXSWAPINTERVALEXTPROC         glXSwapIntervalEXT;
	PFNGLXSWAPINTERVALMESAPROC        glXSwapIntervalMESA;
	PFNGLXSWAPINTERVALSGIPROC         glXSwapIntervalSGI;

#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func
#	include "glimports.h"

	struct SwapChainGL
	{
		SwapChainGL(::Window _window, XVisualInfo* _visualInfo, GLXContext _context)
			: m_window(_window)
		{
			m_context = glXCreateContext( (::Display*)g_platformData.ndt, _visualInfo, _context, GL_TRUE);
		}

		~SwapChainGL()
		{
			glXMakeCurrent( (::Display*)g_platformData.ndt, 0, 0);
			glXDestroyContext( (::Display*)g_platformData.ndt, m_context);
		}

		void makeCurrent()
		{
			glXMakeCurrent( (::Display*)g_platformData.ndt, m_window, m_context);
		}

		void swapBuffers()
		{
			glXSwapBuffers( (::Display*)g_platformData.ndt, m_window);
		}

		Window m_window;
		GLXContext m_context;
	};

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_width, _height);

		m_context = (GLXContext)g_platformData.context;

		if (NULL == g_platformData.context)
		{
			XLockDisplay( (::Display*)g_platformData.ndt);

			int major, minor;
			bool version = glXQueryVersion( (::Display*)g_platformData.ndt, &major, &minor);
			BGFX_FATAL(version, Fatal::UnableToInitialize, "Failed to query GLX version");
			BGFX_FATAL( (major == 1 && minor >= 2) || major > 1
					, Fatal::UnableToInitialize
					, "GLX version is not >=1.2 (%d.%d)."
					, major
					, minor
					);

			int32_t screen = DefaultScreen( (::Display*)g_platformData.ndt);

			const char* extensions = glXQueryExtensionsString( (::Display*)g_platformData.ndt, screen);
			BX_TRACE("GLX extensions:");
			dumpExtensions(extensions);

			const int attrsGlx[] =
			{
				GLX_RENDER_TYPE, GLX_RGBA_BIT,
				GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
				GLX_DOUBLEBUFFER, true,
				GLX_RED_SIZE, 8,
				GLX_BLUE_SIZE, 8,
				GLX_GREEN_SIZE, 8,
				//			GLX_ALPHA_SIZE, 8,
				GLX_DEPTH_SIZE, 24,
				GLX_STENCIL_SIZE, 8,
				0,
			};

			// Find suitable config
			GLXFBConfig bestConfig = NULL;

			int numConfigs;
			GLXFBConfig* configs = glXChooseFBConfig( (::Display*)g_platformData.ndt, screen, attrsGlx, &numConfigs);

			BX_TRACE("glX num configs %d", numConfigs);

			for (int ii = 0; ii < numConfigs; ++ii)
			{
				m_visualInfo = glXGetVisualFromFBConfig( (::Display*)g_platformData.ndt, configs[ii]);
				if (NULL != m_visualInfo)
				{
					BX_TRACE("---");
					bool valid = true;
					for (uint32_t attr = 6; attr < BX_COUNTOF(attrsGlx)-1 && attrsGlx[attr] != 0; attr += 2)
					{
						int value;
						glXGetFBConfigAttrib( (::Display*)g_platformData.ndt, configs[ii], attrsGlx[attr], &value);
						BX_TRACE("glX %d/%d %2d: %4x, %8x (%8x%s)"
								, ii
								, numConfigs
								, attr/2
								, attrsGlx[attr]
								, value
								, attrsGlx[attr + 1]
								, value < attrsGlx[attr + 1] ? " *" : ""
								);

						if (value < attrsGlx[attr + 1])
						{
							valid = false;
#if !BGFX_CONFIG_DEBUG
							break;
#endif // BGFX_CONFIG_DEBUG
						}
					}

					if (valid)
					{
						bestConfig = configs[ii];
						BX_TRACE("Best config %d.", ii);
						break;
					}
				}

				XFree(m_visualInfo);
				m_visualInfo = NULL;
			}

			XFree(configs);
			BGFX_FATAL(m_visualInfo, Fatal::UnableToInitialize, "Failed to find a suitable X11 display configuration.");

			BX_TRACE("Create GL 2.1 context.");
			m_context = glXCreateContext( (::Display*)g_platformData.ndt, m_visualInfo, 0, GL_TRUE);
			BGFX_FATAL(NULL != m_context, Fatal::UnableToInitialize, "Failed to create GL 2.1 context.");

#if BGFX_CONFIG_RENDERER_OPENGL >= 31
			glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress( (const GLubyte*)"glXCreateContextAttribsARB");

			if (NULL != glXCreateContextAttribsARB)
			{
				BX_TRACE("Create GL 3.1 context.");
				int32_t flags = BGFX_CONFIG_DEBUG ? GLX_CONTEXT_DEBUG_BIT_ARB : 0;
				const int contextAttrs[] =
				{
					GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
					GLX_CONTEXT_MINOR_VERSION_ARB, 1,
					GLX_CONTEXT_FLAGS_ARB, flags,
					GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
					0,
				};

				GLXContext context = glXCreateContextAttribsARB( (::Display*)g_platformData.ndt, bestConfig, 0, true, contextAttrs);

				if (NULL != context)
				{
					glXDestroyContext( (::Display*)g_platformData.ndt, m_context);
					m_context = context;
				}
			}
#else
			BX_UNUSED(bestConfig);
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 31

			XUnlockDisplay( (::Display*)g_platformData.ndt);
		}

		import();

		glXMakeCurrent( (::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, m_context);
		m_current = NULL;

		glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress( (const GLubyte*)"glXSwapIntervalEXT");
		if (NULL != glXSwapIntervalEXT)
		{
			BX_TRACE("Using glXSwapIntervalEXT.");
			glXSwapIntervalEXT( (::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, 0);
		}
		else
		{
			glXSwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress( (const GLubyte*)"glXSwapIntervalMESA");
			if (NULL != glXSwapIntervalMESA)
			{
				BX_TRACE("Using glXSwapIntervalMESA.");
				glXSwapIntervalMESA(0);
			}
			else
			{
				glXSwapIntervalSGI = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddress( (const GLubyte*)"glXSwapIntervalSGI");
				if (NULL != glXSwapIntervalSGI)
				{
					BX_TRACE("Using glXSwapIntervalSGI.");
					glXSwapIntervalSGI(0);
				}
			}
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glXSwapBuffers( (::Display*)g_platformData.ndt, (::Window)g_platformData.nwh);

		g_internalData.context = m_context;
	}

	void GlContext::destroy()
	{
		glXMakeCurrent( (::Display*)g_platformData.ndt, 0, 0);
		if (NULL == g_platformData.context)
		{
			glXDestroyContext( (::Display*)g_platformData.ndt, m_context);
			XFree(m_visualInfo);
		}
		m_context    = NULL;
		m_visualInfo = NULL;
	}

	void GlContext::resize(uint32_t /*_width*/, uint32_t /*_height*/, uint32_t _flags)
	{
		bool vsync = !!(_flags&BGFX_RESET_VSYNC);
		int32_t interval = vsync ? 1 : 0;

		if (NULL != glXSwapIntervalEXT)
		{
			glXSwapIntervalEXT( (::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, interval);
		}
		else if (NULL != glXSwapIntervalMESA)
		{
			glXSwapIntervalMESA(interval);
		}
		else if (NULL != glXSwapIntervalSGI)
		{
			glXSwapIntervalSGI(interval);
		}
	}

	uint64_t GlContext::getCaps() const
	{
		return BGFX_CAPS_SWAP_CHAIN;
	}

	SwapChainGL* GlContext::createSwapChain(void* _nwh)
	{
		return BX_NEW(g_allocator, SwapChainGL)( (::Window)_nwh, m_visualInfo, m_context);
	}

	void GlContext::destroySwapChain(SwapChainGL* _swapChain)
	{
		BX_DELETE(g_allocator, _swapChain);
		glXMakeCurrent( (::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, m_context);
	}

	void GlContext::swap(SwapChainGL* _swapChain)
	{
		makeCurrent(_swapChain);

		if (NULL == _swapChain)
		{
			glXSwapBuffers( (::Display*)g_platformData.ndt, (::Window)g_platformData.nwh);
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
				glXMakeCurrent( (::Display*)g_platformData.ndt, (::Window)g_platformData.nwh, m_context);
			}
			else
			{
				_swapChain->makeCurrent();
			}
		}
	}

	void GlContext::import()
	{
#	define GL_EXTENSION(_optional, _proto, _func, _import) \
				{ \
					if (NULL == _func) \
					{ \
						_func = (_proto)glXGetProcAddress( (const GLubyte*)#_import); \
						BX_TRACE("%p " #_func " (" #_import ")", _func); \
						BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGL context. glXGetProcAddress %s", #_import); \
					} \
				}
#	include "glimports.h"
	}

} /* namespace gl */ } // namespace bgfx

#	endif // BGFX_USE_GLX

#endif // (BX_PLATFORM_BSD || BX_PLATFORM_LINUX) && (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
