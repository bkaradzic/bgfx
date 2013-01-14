/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

#	if BGFX_USE_WGL

namespace bgfx
{
	PFNWGLGETPROCADDRESSPROC wglGetProcAddress;
	PFNWGLMAKECURRENTPROC wglMakeCurrent;
	PFNWGLCREATECONTEXTPROC wglCreateContext;
	PFNWGLDELETECONTEXTPROC wglDeleteContext;

#	define GL_IMPORT(_optional, _proto, _func) _proto _func
#		include "glimports.h"
#	undef GL_IMPORT

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
		m_opengl32dll = LoadLibrary("opengl32.dll");
		BGFX_FATAL(NULL != m_opengl32dll, Fatal::UnableToInitialize, "Failed to load opengl32.dll.");

		wglGetProcAddress = (PFNWGLGETPROCADDRESSPROC)GetProcAddress(m_opengl32dll, "wglGetProcAddress");
		BGFX_FATAL(NULL != wglGetProcAddress, Fatal::UnableToInitialize, "Failed get wglGetProcAddress.");

		wglMakeCurrent = (PFNWGLMAKECURRENTPROC)GetProcAddress(m_opengl32dll, "wglMakeCurrent");
		BGFX_FATAL(NULL != wglMakeCurrent, Fatal::UnableToInitialize, "Failed get wglMakeCurrent.");

		wglCreateContext = (PFNWGLCREATECONTEXTPROC)GetProcAddress(m_opengl32dll, "wglCreateContext");
		BGFX_FATAL(NULL != wglCreateContext, Fatal::UnableToInitialize, "Failed get wglCreateContext.");

		wglDeleteContext = (PFNWGLDELETECONTEXTPROC)GetProcAddress(m_opengl32dll, "wglDeleteContext");
		BGFX_FATAL(NULL != wglDeleteContext, Fatal::UnableToInitialize, "Failed get wglDeleteContext.");

		m_hdc = GetDC(g_bgfxHwnd);
		BGFX_FATAL(NULL != m_hdc, Fatal::UnableToInitialize, "GetDC failed!");

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd) );
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
		BGFX_FATAL(0 != pixelFormat, Fatal::UnableToInitialize, "ChoosePixelFormat failed!");

		DescribePixelFormat(m_hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		BX_TRACE("Pixel format:\n"
			"\tiPixelType %d\n"
			"\tcColorBits %d\n"
			"\tcAlphaBits %d\n"
			"\tcDepthBits %d\n"
			"\tcStencilBits %d\n"
			, pfd.iPixelType
			, pfd.cColorBits
			, pfd.cAlphaBits
			, pfd.cDepthBits
			, pfd.cStencilBits
			);

		int result;
		result = SetPixelFormat(m_hdc, pixelFormat, &pfd);
		BGFX_FATAL(0 != result, Fatal::UnableToInitialize, "SetPixelFormat failed!");

		m_context = wglCreateContext(m_hdc);
		BGFX_FATAL(NULL != m_context, Fatal::UnableToInitialize, "wglCreateContext failed!");

		result = wglMakeCurrent(m_hdc, m_context);
		BGFX_FATAL(0 != result, Fatal::UnableToInitialize, "wglMakeCurrent failed!");

		import();
	}

	void GlContext::destroy()
	{
		wglMakeCurrent(NULL, NULL);

		wglDeleteContext(m_context);
		m_context = NULL;

		ReleaseDC(g_bgfxHwnd, m_hdc);
		m_hdc = NULL;

		FreeLibrary(m_opengl32dll);
		m_opengl32dll = NULL;
	}

	void GlContext::resize(uint32_t _width, uint32_t _height)
	{
	}

	void GlContext::swap()
	{
		wglMakeCurrent(m_hdc, m_context);
		SwapBuffers(m_hdc);
	}

	void GlContext::import()
	{
#	define GL_IMPORT(_optional, _proto, _func) \
		{ \
			_func = (_proto)wglGetProcAddress(#_func); \
			if (_func == NULL) \
			{ \
				_func = (_proto)GetProcAddress(m_opengl32dll, #_func); \
			} \
			BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGL context. wglGetProcAddress(\"%s\")", #_func); \
		}
#	include "glimports.h"
#	undef GL_IMPORT
	}

} // namespace bgfx

#	endif // BGFX_USE_WGL
#endif // (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
