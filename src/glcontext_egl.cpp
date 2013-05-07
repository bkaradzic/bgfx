/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

#	if BGFX_USE_EGL

namespace bgfx
{
#	define GL_IMPORT(_optional, _proto, _func) _proto _func
#		include "glimports.h"
#	undef GL_IMPORT

	void GlContext::create(uint32_t /*_width*/, uint32_t /*_height*/)
	{
		EGLNativeDisplayType ndt = EGL_DEFAULT_DISPLAY;
		EGLNativeWindowType nwt = (EGLNativeWindowType)NULL;
#	if BX_PLATFORM_WINDOWS
		ndt = GetDC(g_bgfxHwnd);
		nwt = g_bgfxHwnd;
#	endif // BX_PLATFORM_
		m_display = eglGetDisplay(ndt);
		BGFX_FATAL(m_display != EGL_NO_DISPLAY, Fatal::UnableToInitialize, "Failed to create display 0x%08x", m_display);

		EGLint major = 0;
		EGLint minor = 0;
		EGLBoolean success = eglInitialize(m_display, &major, &minor);
		BGFX_FATAL(success && major >= 1 && minor >= 3, Fatal::UnableToInitialize, "Failed to initialize %d.%d", major, minor);

		EGLint attrs[] =
		{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,

#	if BX_PLATFORM_ANDROID
			EGL_DEPTH_SIZE, 16,
#	else
			EGL_DEPTH_SIZE, 24,
#	endif // BX_PLATFORM_

			EGL_NONE
		};

		EGLint numConfig = 0;
		EGLConfig config;
		success = eglChooseConfig(m_display, attrs, &config, 1, &numConfig);
		BGFX_FATAL(success, Fatal::UnableToInitialize, "eglChooseConfig");

#	if BX_PLATFORM_ANDROID
		EGLint format;
		eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);
		ANativeWindow_setBuffersGeometry(g_bgfxAndroidWindow, 0, 0, format);
		nwt = g_bgfxAndroidWindow;
#	endif // BX_PLATFORM_ANDROID

		m_surface = eglCreateWindowSurface(m_display, config, nwt, NULL);
		BGFX_FATAL(m_surface != EGL_NO_SURFACE, Fatal::UnableToInitialize, "Failed to create surface.");

		EGLint contextAttrs[] =
		{
#	if BGFX_CONFIG_RENDERER_OPENGLES2
			EGL_CONTEXT_CLIENT_VERSION, 2,
#	elif BGFX_CONFIG_RENDERER_OPENGLES3
			EGL_CONTEXT_CLIENT_VERSION, 3,
#	endif // BGFX_CONFIG_RENDERER_

			EGL_NONE
		};

		m_context = eglCreateContext(m_display, config, EGL_NO_CONTEXT, contextAttrs);
		BGFX_FATAL(m_context != EGL_NO_CONTEXT, Fatal::UnableToInitialize, "Failed to create context.");

		success = eglMakeCurrent(m_display, m_surface, m_surface, m_context);
		BGFX_FATAL(success, Fatal::UnableToInitialize, "Failed to set context.");

		eglSwapInterval(m_display, 0);

#	if BX_PLATFORM_EMSCRIPTEN
		emscripten_set_canvas_size(_width, _height);
#	endif // BX_PLATFORM_EMSCRIPTEN

		import();
	}

	void GlContext::destroy()
	{
		eglMakeCurrent(EGL_NO_DISPLAY, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroyContext(m_display, m_context);
		eglDestroySurface(m_display, m_surface);
		eglTerminate(m_display);
		m_context = NULL;
	}

	void GlContext::resize(uint32_t /*_width*/, uint32_t /*_height*/, bool _vsync)
	{
		eglSwapInterval(m_display, _vsync ? 1 : 0);
	}

	void GlContext::swap()
	{
		eglMakeCurrent(m_display, m_surface, m_surface, m_context);
		eglSwapBuffers(m_display, m_surface);
	}

	void GlContext::import()
	{
#	if !BX_PLATFORM_EMSCRIPTEN
#		define GL_IMPORT(_optional, _proto, _func) \
		{ \
			_func = (_proto)eglGetProcAddress(#_func); \
			BX_TRACE(#_func " 0x%08x", _func); \
			BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGLES context. eglGetProcAddress(\"%s\")", #_func); \
		}
#		include "glimports.h"
#		undef GL_IMPORT
#	endif // !BX_PLATFORM_EMSCRIPTEN
	}

} // namespace bgfx

#	endif // BGFX_USE_EGL
#endif // (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
