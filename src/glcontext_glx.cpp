/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if (BX_PLATFORM_FREEBSD || BX_PLATFORM_LINUX) && (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"
#	define GLX_GLXEXT_PROTOTYPES
#	include <glx/glxext.h>

namespace bgfx
{
	typedef int (*PFNGLXSWAPINTERVALMESAPROC)(uint32_t _interval);

	PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
	PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT;
	PFNGLXSWAPINTERVALMESAPROC glXSwapIntervalMESA;
	PFNGLXSWAPINTERVALSGIPROC glXSwapIntervalSGI;

#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func
#	include "glimports.h"

	static ::Display* s_display;
	static ::Window s_window;

	void x11SetDisplayWindow(::Display* _display, ::Window _window)
	{
		s_display = _display;
		s_window = _window;
	}

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_width, _height);
		XLockDisplay(s_display);

		int major, minor;
		bool version = glXQueryVersion(s_display, &major, &minor);
		BGFX_FATAL(version, Fatal::UnableToInitialize, "Failed to query GLX version");
		BGFX_FATAL( (major == 1 && minor >= 2) || major > 1
				, Fatal::UnableToInitialize
				, "GLX version is not >=1.2 (%d.%d)."
				, major
				, minor
				);

		int32_t screen = DefaultScreen(s_display);

		const char* extensions = glXQueryExtensionsString(s_display, screen);
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
		GLXFBConfig* configs = glXChooseFBConfig(s_display, screen, attrsGlx, &numConfigs);

		BX_TRACE("glX num configs %d", numConfigs);

		XVisualInfo* visualInfo = NULL;
		for (int ii = 0; ii < numConfigs; ++ii)
		{
			visualInfo = glXGetVisualFromFBConfig(s_display, configs[ii]);
			if (NULL != visualInfo)
			{
				BX_TRACE("---");
				bool valid = true;
				for (uint32_t attr = 6; attr < BX_COUNTOF(attrsGlx)-1 && attrsGlx[attr] != None; attr += 2)
				{
					int value;
					glXGetFBConfigAttrib(s_display, configs[ii], attrsGlx[attr], &value);
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

			XFree(visualInfo);
			visualInfo = NULL;
		}

		XFree(configs);
		BGFX_FATAL(visualInfo, Fatal::UnableToInitialize, "Failed to find a suitable X11 display configuration.");

		BX_TRACE("Create GL 2.1 context.");
		m_context = glXCreateContext(s_display, visualInfo, 0, GL_TRUE);
		BGFX_FATAL(NULL != m_context, Fatal::UnableToInitialize, "Failed to create GL 2.1 context.");

		XFree(visualInfo);

#if BGFX_CONFIG_RENDERER_OPENGL >= 31
		glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress( (const GLubyte*)"glXCreateContextAttribsARB");

		if (NULL != glXCreateContextAttribsARB)
		{
			BX_TRACE("Create GL 3.1 context.");
			const int contextAttrs[] =
			{
				GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
				GLX_CONTEXT_MINOR_VERSION_ARB, 1,
				GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
				0,
			};

			GLXContext context = glXCreateContextAttribsARB(s_display, bestConfig, 0, true, contextAttrs);

			if (NULL != context)
			{
				glXDestroyContext(s_display, m_context);
				m_context = context;
			}
		}
#else
		BX_UNUSED(bestConfig);
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 31

		XUnlockDisplay(s_display);

		import();

		glXMakeCurrent(s_display, s_window, m_context);

		glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress( (const GLubyte*)"glXSwapIntervalEXT");
		if (NULL != glXSwapIntervalEXT)
		{
			BX_TRACE("Using glXSwapIntervalEXT.");
			glXSwapIntervalEXT(s_display, s_window, 0);
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
		glXSwapBuffers(s_display, s_window);
	}

	void GlContext::destroy()
	{
		glXMakeCurrent(s_display, 0, 0);
		glXDestroyContext(s_display, m_context);
	}

	void GlContext::resize(uint32_t /*_width*/, uint32_t /*_height*/, bool _vsync)
	{
		int32_t interval = _vsync ? 1 : 0;

		if (NULL != glXSwapIntervalEXT)
		{
			glXSwapIntervalEXT(s_display, s_window, interval);
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

	void GlContext::swap()
	{
		glXSwapBuffers(s_display, s_window);
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

} // namespace bgfx

#endif // (BX_PLATFORM_FREEBSD || BX_PLATFORM_LINUX) && (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
