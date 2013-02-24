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
	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

#	define GL_IMPORT(_optional, _proto, _func) _proto _func
#		include "glimports.h"
#	undef GL_IMPORT

	static HGLRC createContext(HDC _hdc)
	{
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd) );
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int pixelFormat = ChoosePixelFormat(_hdc, &pfd);
		BGFX_FATAL(0 != pixelFormat, Fatal::UnableToInitialize, "ChoosePixelFormat failed!");

		DescribePixelFormat(_hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

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
		result = SetPixelFormat(_hdc, pixelFormat, &pfd);
		BGFX_FATAL(0 != result, Fatal::UnableToInitialize, "SetPixelFormat failed!");

		HGLRC context = wglCreateContext(_hdc);
		BGFX_FATAL(NULL != context, Fatal::UnableToInitialize, "wglCreateContext failed!");

		result = wglMakeCurrent(_hdc, context);
		BGFX_FATAL(0 != result, Fatal::UnableToInitialize, "wglMakeCurrent failed!");

		return context;
	}

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

		// Dummy window to peek into WGL functionality.
		//
		// An application can only set the pixel format of a window one time.
		// Once a window's pixel format is set, it cannot be changed.
		// MSDN: http://msdn.microsoft.com/en-us/library/windows/desktop/dd369049%28v=vs.85%29.aspx
		HWND hwnd = CreateWindowA("STATIC"
			, ""
			, WS_POPUP|WS_DISABLED
			, -32000
			, -32000
			, 0
			, 0
			, NULL
			, NULL
			, GetModuleHandle(NULL)
			, 0
			);

		HDC hdc = GetDC(hwnd);
		BGFX_FATAL(NULL != hdc, Fatal::UnableToInitialize, "GetDC failed!");

		HGLRC context = createContext(hdc);

		wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

		if (NULL != wglGetExtensionsStringARB)
		{
			BX_TRACE("WGL extensions:");
			const char* extensions = (const char*)wglGetExtensionsStringARB(hdc);
			if (NULL != extensions)
			{
				char name[1024];
				const char* pos = extensions;
				const char* end = extensions + strlen(extensions);
				while (pos < end)
				{
					uint32_t len;
					const char* space = strchr(pos, ' ');
					if (NULL != space)
					{
						len = uint32_min(sizeof(name), (uint32_t)(space - pos) );
					}
					else
					{
						len = uint32_min(sizeof(name), (uint32_t)strlen(pos) );
					}

					strncpy(name, pos, len);
					name[len] = '\0';

					BX_TRACE("\t%s", name);

					pos += len+1;
				}
			}
		}

		if (NULL != wglChoosePixelFormatARB
		&&  NULL != wglCreateContextAttribsARB)
		{
			int32_t attrs[] =
			{
				WGL_SAMPLE_BUFFERS_ARB, 0,
				WGL_SAMPLES_ARB, 0,
				WGL_SUPPORT_OPENGL_ARB, true,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_DRAW_TO_WINDOW_ARB, true,
				WGL_DOUBLE_BUFFER_ARB, true,
				WGL_COLOR_BITS_ARB, 32,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_STENCIL_BITS_ARB, 8,
				0
			};

			int result;
			int pixelFormat;
			uint32_t numFormats = 0;
			do 
			{
				result = wglChoosePixelFormatARB(m_hdc, attrs, NULL, 1, &pixelFormat, &numFormats);
				if (0 == result
				||  0 == numFormats)
				{
					attrs[3] >>= 1;
					attrs[1] = attrs[3] == 0 ? 0 : 1;
				}

			} while (0 == numFormats);

			PIXELFORMATDESCRIPTOR pfd;
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

			result = SetPixelFormat(m_hdc, pixelFormat, &pfd);
			BGFX_FATAL(0 != result, Fatal::UnableToInitialize, "SetPixelFormat failed (last err: 0x%08x)!", GetLastError() );

			const int32_t contextAttrs[] =
			{
#if 1
 				WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
 				WGL_CONTEXT_MINOR_VERSION_ARB, 1,
#else
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 2,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#endif // 1
#if BGFX_CONFIG_DEBUG
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif // BGFX_CONFIG_DEBUG
				0
			};

			m_context = wglCreateContextAttribsARB(m_hdc, 0, contextAttrs);
		}

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(context);
		DestroyWindow(hwnd);

		if (NULL == m_context)
		{
			m_context = createContext(m_hdc);
		}

		int result = wglMakeCurrent(m_hdc, m_context);
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
