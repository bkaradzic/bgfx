/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES|BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

#	if BGFX_USE_WGL

namespace bgfx { namespace gl
{
	PFNWGLGETPROCADDRESSPROC wglGetProcAddress;
	PFNWGLMAKECURRENTPROC wglMakeCurrent;
	PFNWGLCREATECONTEXTPROC wglCreateContext;
	PFNWGLDELETECONTEXTPROC wglDeleteContext;
	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func
#	include "glimports.h"

	struct SwapChainGL
	{
		SwapChainGL(void* _nwh)
			: m_hwnd( (HWND)_nwh)
		{
			m_hdc = GetDC(m_hwnd);
		}

		~SwapChainGL()
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(m_context);
			ReleaseDC(m_hwnd, m_hdc);
		}

		void makeCurrent()
		{
			wglMakeCurrent(m_hdc, m_context);
			GLenum err = glGetError();
			BX_WARN(0 == err, "wglMakeCurrent failed with GL error: 0x%04x.", err); BX_UNUSED(err);
		}

		void swapBuffers()
		{
			SwapBuffers(m_hdc);
		}

		HWND  m_hwnd;
		HDC   m_hdc;
		HGLRC m_context;
	};

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

	void GlContext::create(uint32_t /*_width*/, uint32_t /*_height*/)
	{
		m_opengl32dll = bx::dlopen("opengl32.dll");
		BGFX_FATAL(NULL != m_opengl32dll, Fatal::UnableToInitialize, "Failed to load opengl32.dll.");

		wglGetProcAddress = (PFNWGLGETPROCADDRESSPROC)bx::dlsym(m_opengl32dll, "wglGetProcAddress");
		BGFX_FATAL(NULL != wglGetProcAddress, Fatal::UnableToInitialize, "Failed get wglGetProcAddress.");

		// If g_platformHooks.nwh is NULL, the assumption is that GL context was created
		// by user (for example, using SDL, GLFW, etc.)
		BX_WARN(NULL != g_platformData.nwh
			, "bgfx::setPlatform with valid window is not called. This might "
			  "be intentional when GL context is created by the user."
			);

		if (NULL != g_platformData.nwh)
		{
			wglMakeCurrent = (PFNWGLMAKECURRENTPROC)bx::dlsym(m_opengl32dll, "wglMakeCurrent");
			BGFX_FATAL(NULL != wglMakeCurrent, Fatal::UnableToInitialize, "Failed get wglMakeCurrent.");

			wglCreateContext = (PFNWGLCREATECONTEXTPROC)bx::dlsym(m_opengl32dll, "wglCreateContext");
			BGFX_FATAL(NULL != wglCreateContext, Fatal::UnableToInitialize, "Failed get wglCreateContext.");

			wglDeleteContext = (PFNWGLDELETECONTEXTPROC)bx::dlsym(m_opengl32dll, "wglDeleteContext");
			BGFX_FATAL(NULL != wglDeleteContext, Fatal::UnableToInitialize, "Failed get wglDeleteContext.");

			m_hdc = GetDC( (HWND)g_platformData.nwh);
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

			wglGetExtensionsStringARB  = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
			wglChoosePixelFormatARB    = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
			wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
			wglSwapIntervalEXT         = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

			if (NULL != wglGetExtensionsStringARB)
			{
				const char* extensions = (const char*)wglGetExtensionsStringARB(hdc);
				BX_TRACE("WGL extensions:");
				dumpExtensions(extensions);
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
				uint32_t numFormats = 0;
				do
				{
					result = wglChoosePixelFormatARB(m_hdc, attrs, NULL, 1, &m_pixelFormat, &numFormats);
					if (0 == result
					||  0 == numFormats)
					{
						attrs[3] >>= 1;
						attrs[1] = attrs[3] == 0 ? 0 : 1;
					}

				} while (0 == numFormats);

				DescribePixelFormat(m_hdc, m_pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &m_pfd);

				BX_TRACE("Pixel format:\n"
					"\tiPixelType %d\n"
					"\tcColorBits %d\n"
					"\tcAlphaBits %d\n"
					"\tcDepthBits %d\n"
					"\tcStencilBits %d\n"
					, m_pfd.iPixelType
					, m_pfd.cColorBits
					, m_pfd.cAlphaBits
					, m_pfd.cDepthBits
					, m_pfd.cStencilBits
					);

				result = SetPixelFormat(m_hdc, m_pixelFormat, &m_pfd);
				// When window is created by SDL and SDL_WINDOW_OPENGL is set, SetPixelFormat
				// will fail. Just warn and continue. In case it failed for some other reason
				// create context will fail and it will error out there.
				BX_WARN(result, "SetPixelFormat failed (last err: 0x%08x)!", GetLastError() );

				int32_t flags = BGFX_CONFIG_DEBUG ? WGL_CONTEXT_DEBUG_BIT_ARB : 0;
				BX_UNUSED(flags);
				int32_t contextAttrs[9] =
				{
#if BGFX_CONFIG_RENDERER_OPENGL >= 31
					WGL_CONTEXT_MAJOR_VERSION_ARB, BGFX_CONFIG_RENDERER_OPENGL / 10,
					WGL_CONTEXT_MINOR_VERSION_ARB, BGFX_CONFIG_RENDERER_OPENGL % 10,
					WGL_CONTEXT_FLAGS_ARB, flags,
					WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#else
					WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
					WGL_CONTEXT_MINOR_VERSION_ARB, 1,
					0, 0,
					0, 0,
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 31
					0
				};

				m_context = wglCreateContextAttribsARB(m_hdc, 0, contextAttrs);
				if (NULL == m_context)
				{
					// nVidia doesn't like context profile mask for contexts below 3.2?
					contextAttrs[6] = WGL_CONTEXT_PROFILE_MASK_ARB == contextAttrs[6] ? 0 : contextAttrs[6];
					m_context = wglCreateContextAttribsARB(m_hdc, 0, contextAttrs);
				}
				BGFX_FATAL(NULL != m_context, Fatal::UnableToInitialize, "Failed to create context 0x%08x.", GetLastError() );

				BX_STATIC_ASSERT(sizeof(contextAttrs) == sizeof(m_contextAttrs) );
				memcpy(m_contextAttrs, contextAttrs, sizeof(contextAttrs) );
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
			m_current = NULL;

			if (NULL != wglSwapIntervalEXT)
			{
				wglSwapIntervalEXT(0);
			}
		}

		import();
	}

	void GlContext::destroy()
	{
		if (NULL != g_platformData.nwh)
		{
			wglMakeCurrent(NULL, NULL);

			wglDeleteContext(m_context);
			m_context = NULL;

			ReleaseDC( (HWND)g_platformData.nwh, m_hdc);
			m_hdc = NULL;
		}

		bx::dlclose(m_opengl32dll);
		m_opengl32dll = NULL;
	}

	void GlContext::resize(uint32_t /*_width*/, uint32_t /*_height*/, uint32_t _flags)
	{
		if (NULL != wglSwapIntervalEXT)
		{
			bool vsync = !!(_flags&BGFX_RESET_VSYNC);
			wglSwapIntervalEXT(vsync ? 1 : 0);
		}
	}

	uint64_t GlContext::getCaps() const
	{
		return BGFX_CAPS_SWAP_CHAIN;
	}

	SwapChainGL* GlContext::createSwapChain(void* _nwh)
	{
		SwapChainGL* swapChain = BX_NEW(g_allocator, SwapChainGL)(_nwh);

		int result = SetPixelFormat(swapChain->m_hdc, m_pixelFormat, &m_pfd);
		BX_WARN(result, "SetPixelFormat failed (last err: 0x%08x)!", GetLastError() ); BX_UNUSED(result);

		swapChain->m_context = wglCreateContextAttribsARB(swapChain->m_hdc, m_context, m_contextAttrs);
		BX_CHECK(NULL != swapChain->m_context, "Create swap chain failed: %x", glGetError() );
		return swapChain;
	}

	void GlContext::destroySwapChain(SwapChainGL*  _swapChain)
	{
		BX_DELETE(g_allocator, _swapChain);
	}

	void GlContext::swap(SwapChainGL* _swapChain)
	{
		makeCurrent(_swapChain);

		if (NULL == _swapChain)
		{
			if (NULL != g_platformData.nwh)
			{
				SwapBuffers(m_hdc);
			}
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
				wglMakeCurrent(m_hdc, m_context);
				GLenum err = glGetError();
				BX_WARN(0 == err, "wglMakeCurrent failed with GL error: 0x%04x.", err); BX_UNUSED(err);
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
#	define GL_EXTENSION(_optional, _proto, _func, _import) \
				{ \
					if (NULL == _func) \
					{ \
						_func = (_proto)wglGetProcAddress(#_import); \
						if (_func == NULL) \
						{ \
							_func = (_proto)bx::dlsym(m_opengl32dll, #_import); \
							BX_TRACE("    %p " #_func " (" #_import ")", _func); \
						} \
						else \
						{ \
							BX_TRACE("wgl %p " #_func " (" #_import ")", _func); \
						} \
						BGFX_FATAL(BX_IGNORE_C4127(_optional) || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGL context. wglGetProcAddress(\"%s\")", #_import); \
					} \
				}
#	include "glimports.h"
	}

} } // namespace bgfx

#	endif // BGFX_USE_WGL
#endif // (BGFX_CONFIG_RENDERER_OPENGLES|BGFX_CONFIG_RENDERER_OPENGL)
