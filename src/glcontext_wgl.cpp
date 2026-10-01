/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES|BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

#	if BGFX_USE_WGL

#		if BGFX_CONFIG_RENDERER_OPENGLES
#			define BGFX_WGL_CONTEXT_VERSION     BGFX_CONFIG_RENDERER_OPENGLES
#			define BGFX_WGL_CONTEXT_PROFILE_BIT WGL_CONTEXT_ES_PROFILE_BIT_EXT
#		else
#			define BGFX_WGL_CONTEXT_VERSION     BGFX_CONFIG_RENDERER_OPENGL
#			define BGFX_WGL_CONTEXT_PROFILE_BIT WGL_CONTEXT_CORE_PROFILE_BIT_ARB
#		endif // BGFX_CONFIG_RENDERER_OPENGLES

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
#	undef GL_IMPORT

	template<typename ProtoT>
	static ProtoT wglGetProc(const char* _name)
	{
		return reinterpret_cast<ProtoT>( (void*)wglGetProcAddress(_name) );
	}

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

	static HGLRC createContext(HDC _hdc, const SwapChain& _swapChain)
	{
		const bimg::ImageBlockInfo& colorBlockInfo       = bimg::getBlockInfo(bimg::TextureFormat::Enum(_swapChain.formatColor) );
		const bimg::ImageBlockInfo& depthStecilBlockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(_swapChain.formatDepthStencil) );

		PIXELFORMATDESCRIPTOR pfd;
		bx::memSet(&pfd, 0, sizeof(pfd) );
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags  = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType   = PFD_TYPE_RGBA;
		pfd.cColorBits   = colorBlockInfo.bitsPerPixel;
		pfd.cAlphaBits   = colorBlockInfo.aBits;
		pfd.cDepthBits   = depthStecilBlockInfo.depthBits;
		pfd.cStencilBits = depthStecilBlockInfo.stencilBits;
		pfd.iLayerType   = PFD_MAIN_PLANE;

		int pixelFormat = ChoosePixelFormat(_hdc, &pfd);

		if (0 == pixelFormat)
		{
			BX_TRACE("Init error: ChoosePixelFormat failed (last err: 0x%08x).", GetLastError() );
			return NULL;
		}

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

		if (0 == result)
		{
			BX_TRACE("Init error: SetPixelFormat failed (last err: 0x%08x).", GetLastError() );
			return NULL;
		}

		HGLRC context = wglCreateContext(_hdc);

		if (NULL == context)
		{
			BX_TRACE("Init error: wglCreateContext failed (last err: 0x%08x).", GetLastError() );
			return NULL;
		}

		result = wglMakeCurrent(_hdc, context);

		if (0 == result)
		{
			BX_TRACE("Init error: wglMakeCurrent failed (last err: 0x%08x).", GetLastError() );
			wglDeleteContext(context);
			return NULL;
		}

		return context;
	}

	static HWND createDummyWindow()
	{
		// An application can only set the pixel format of a window one time.
		// Once a window's pixel format is set, it cannot be changed.
		// MSDN: https://web.archive.org/web/20190207230357/https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/nf-wingdi-setpixelformat
		return CreateWindowA("STATIC"
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
	}

	bool GlContext::create(const SwapChain& _swapChain, uint32_t _reset)
	{
		struct ErrorState
		{
			enum Enum
			{
				Default,
				LoadedOpenGL32,
				AcquiredDC,
				CreatedContext,
			};
		};

		ErrorState::Enum errorState = ErrorState::Default;

		HWND nwh = NULL;

		m_opengl32dll = bx::dlopen("opengl32.dll");

		if (NULL == m_opengl32dll)
		{
			BX_TRACE("Init error: Failed to load opengl32.dll.");
			goto error;
		}

		errorState = ErrorState::LoadedOpenGL32;

		wglGetProcAddress = bx::dlsym<PFNWGLGETPROCADDRESSPROC>(m_opengl32dll, "wglGetProcAddress");
		wglMakeCurrent    = bx::dlsym<PFNWGLMAKECURRENTPROC   >(m_opengl32dll, "wglMakeCurrent");
		wglCreateContext  = bx::dlsym<PFNWGLCREATECONTEXTPROC >(m_opengl32dll, "wglCreateContext");
		wglDeleteContext  = bx::dlsym<PFNWGLDELETECONTEXTPROC >(m_opengl32dll, "wglDeleteContext");

		if (NULL == wglGetProcAddress
		||  NULL == wglMakeCurrent
		||  NULL == wglCreateContext
		||  NULL == wglDeleteContext)
		{
			BX_TRACE("Init error: Failed to import functions from opengl32.dll.");
			goto error;
		}

		// If g_platformHooks.nwh is NULL, the assumption is that GL context was created
		// by user (for example, using SDL, GLFW, etc.)
		BX_WARN(NULL != _swapChain.nwh
			||  NULL != g_platformData.context
			, "Init::swapChain has no valid window handle. This might "
				"be intentional when GL context is created by the user."
			);

		m_nwh = _swapChain.nwh;

		nwh = (HWND)m_nwh;

		m_ownsContext = NULL == g_platformData.context;

		if (NULL == nwh
		&&  m_ownsContext)
		{
			m_dummyHwnd = createDummyWindow();

			if (NULL == m_dummyHwnd)
			{
				BX_TRACE("Init error: Failed to create headless window (last err: 0x%08x).", GetLastError() );
				goto error;
			}

			nwh = m_dummyHwnd;
		}

		if (NULL == nwh)
		{
			BX_TRACE("Init error: Caller-provided GL context also needs the window it was created for.");
			goto error;
		}

		m_hdc = GetDC(nwh);

		if (NULL == m_hdc)
		{
			BX_TRACE("Init error: GetDC failed.");
			goto error;
		}

		errorState = ErrorState::AcquiredDC;

		if (!m_ownsContext)
		{
			m_context = (HGLRC)g_platformData.context;

			int result = wglMakeCurrent(m_hdc, m_context);

			if (0 == result)
			{
				BX_TRACE("Init error: wglMakeCurrent failed (last err: 0x%08x).", GetLastError() );
				goto error;
			}

			m_pixelFormat = GetPixelFormat(m_hdc);

			if (0 != m_pixelFormat)
			{
				DescribePixelFormat(m_hdc, m_pixelFormat, sizeof(m_pfd), &m_pfd);

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
			}
			else
			{
				BX_TRACE("Caller-provided GL context window has no pixel format; secondary swap chains are unavailable (last err: 0x%08x)."
					, GetLastError()
					);
			}

			// WGL extensions can only be resolved once a context is current.
			wglGetExtensionsStringARB  = wglGetProc<PFNWGLGETEXTENSIONSSTRINGARBPROC >("wglGetExtensionsStringARB");
			wglChoosePixelFormatARB    = wglGetProc<PFNWGLCHOOSEPIXELFORMATARBPROC   >("wglChoosePixelFormatARB");
			wglCreateContextAttribsARB = wglGetProc<PFNWGLCREATECONTEXTATTRIBSARBPROC>("wglCreateContextAttribsARB");
			wglSwapIntervalEXT         = wglGetProc<PFNWGLSWAPINTERVALEXTPROC        >("wglSwapIntervalEXT");

			if (NULL != wglGetExtensionsStringARB)
			{
				const char* extensions = (const char*)wglGetExtensionsStringARB(m_hdc);
				BX_TRACE("WGL extensions:");
				dumpExtensions(extensions);
			}

			// Attributes for the contexts SwapChainGL shares with this one.
			const int32_t contextAttrs[9] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, BGFX_WGL_CONTEXT_VERSION / 10,
				WGL_CONTEXT_MINOR_VERSION_ARB, BGFX_WGL_CONTEXT_VERSION % 10,
				WGL_CONTEXT_FLAGS_ARB, BGFX_CONFIG_DEBUG ? WGL_CONTEXT_DEBUG_BIT_ARB : 0,
				WGL_CONTEXT_PROFILE_MASK_ARB, BGFX_WGL_CONTEXT_PROFILE_BIT,
				0
			};

			static_assert(sizeof(contextAttrs) == sizeof(m_contextAttrs) );
			bx::memCopy(m_contextAttrs, contextAttrs, sizeof(contextAttrs) );

			m_current = NULL;

			m_swapInterval = !!(_reset & BGFX_RESET_VSYNC) ? 1 : 0;

			if (NULL != wglSwapIntervalEXT)
			{
				wglSwapIntervalEXT(m_swapInterval);
			}
		}

		if (m_ownsContext)
		{
			// Dummy window to peek into WGL functionality.
			HWND hwnd = createDummyWindow();

			if (NULL == hwnd)
			{
				BX_TRACE("Init error: Failed to create dummy window (last err: 0x%08x).", GetLastError() );
				goto error;
			}

			HDC hdc = GetDC(hwnd);

			if (NULL == hdc)
			{
				BX_TRACE("Init error: GetDC failed.");
				DestroyWindow(hwnd);
				goto error;
			}

			HGLRC context = createContext(hdc, _swapChain);

			if (NULL == context)
			{
				DestroyWindow(hwnd);
				goto error;
			}

			wglGetExtensionsStringARB  = wglGetProc<PFNWGLGETEXTENSIONSSTRINGARBPROC >("wglGetExtensionsStringARB");
			wglChoosePixelFormatARB    = wglGetProc<PFNWGLCHOOSEPIXELFORMATARBPROC   >("wglChoosePixelFormatARB");
			wglCreateContextAttribsARB = wglGetProc<PFNWGLCREATECONTEXTATTRIBSARBPROC>("wglCreateContextAttribsARB");
			wglSwapIntervalEXT         = wglGetProc<PFNWGLSWAPINTERVALEXTPROC        >("wglSwapIntervalEXT");

			if (NULL != wglGetExtensionsStringARB)
			{
				const char* extensions = (const char*)wglGetExtensionsStringARB(hdc);
				BX_TRACE("WGL extensions:");
				dumpExtensions(extensions);
			}

			if (NULL != wglChoosePixelFormatARB
			&&  NULL != wglCreateContextAttribsARB)
			{
				const bimg::ImageBlockInfo& colorBlockInfo       = bimg::getBlockInfo(bimg::TextureFormat::Enum(_swapChain.formatColor) );
				const bimg::ImageBlockInfo& depthStecilBlockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(_swapChain.formatDepthStencil) );

				int32_t attrs[] =
				{
					WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
					WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
					WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
					WGL_SUPPORT_OPENGL_ARB, GL_TRUE,

					WGL_ALPHA_BITS_ARB,     colorBlockInfo.aBits,
					WGL_COLOR_BITS_ARB,     colorBlockInfo.bitsPerPixel,
					WGL_DEPTH_BITS_ARB,     depthStecilBlockInfo.depthBits,
					WGL_STENCIL_BITS_ARB,   depthStecilBlockInfo.stencilBits,

					WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
					WGL_SAMPLES_ARB,        0,
					WGL_SAMPLE_BUFFERS_ARB, GL_FALSE,

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
						if (0 == attrs[3])
						{
							break;
						}

						attrs[3] >>= 1;
						attrs[1] = attrs[3] == 0 ? 0 : 1;
					}

				} while (0 == numFormats);

				if (0 == numFormats)
				{
					BX_TRACE("Init error: wglChoosePixelFormatARB failed (last err: 0x%08x).", GetLastError() );

					wglMakeCurrent(NULL, NULL);
					wglDeleteContext(context);
					DestroyWindow(hwnd);

					goto error;
				}

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
					WGL_CONTEXT_MAJOR_VERSION_ARB, BGFX_WGL_CONTEXT_VERSION / 10,
					WGL_CONTEXT_MINOR_VERSION_ARB, BGFX_WGL_CONTEXT_VERSION % 10,
					WGL_CONTEXT_FLAGS_ARB, flags,
					WGL_CONTEXT_PROFILE_MASK_ARB, BGFX_WGL_CONTEXT_PROFILE_BIT,
					0
				};

				m_context = wglCreateContextAttribsARB(m_hdc, 0, contextAttrs);
				if (NULL == m_context)
				{
					// NVIDIA doesn't like context profile mask for contexts below 3.2?
					contextAttrs[6] = WGL_CONTEXT_PROFILE_MASK_ARB == contextAttrs[6] ? 0 : contextAttrs[6];
					m_context = wglCreateContextAttribsARB(m_hdc, 0, contextAttrs);
				}

				if (NULL == m_context)
				{
					BX_TRACE("Init error: Failed to create context (last err: 0x%08x).", GetLastError() );

					wglMakeCurrent(NULL, NULL);
					wglDeleteContext(context);
					DestroyWindow(hwnd);

					goto error;
				}

				static_assert(sizeof(contextAttrs) == sizeof(m_contextAttrs) );
				bx::memCopy(m_contextAttrs, contextAttrs, sizeof(contextAttrs) );
			}

			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(context);
			DestroyWindow(hwnd);

			if (NULL == m_context)
			{
				m_context = createContext(m_hdc, _swapChain);

				if (NULL == m_context)
				{
					goto error;
				}
			}

			errorState = ErrorState::CreatedContext;

			int result = wglMakeCurrent(m_hdc, m_context);

			if (0 == result)
			{
				BX_TRACE("Init error: wglMakeCurrent failed (last err: 0x%08x).", GetLastError() );
				goto error;
			}

			m_current = NULL;

			m_swapInterval = !!(_reset & BGFX_RESET_VSYNC) ? 1 : 0;
			if (NULL != wglSwapIntervalEXT)
			{
				wglSwapIntervalEXT(m_swapInterval);
			}
		}

		if (!import() )
		{
			goto error;
		}

		g_internalData.context = m_context;

		return true;

	error:
		switch (errorState)
		{
		case ErrorState::CreatedContext:
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(m_context);
			[[fallthrough]];

		case ErrorState::AcquiredDC:
			ReleaseDC(nwh, m_hdc);
			m_hdc = NULL;
			[[fallthrough]];

		case ErrorState::LoadedOpenGL32:
			if (NULL != m_dummyHwnd)
			{
				DestroyWindow(m_dummyHwnd);
				m_dummyHwnd = NULL;
			}

			bx::dlclose(m_opengl32dll);
			m_opengl32dll = NULL;
			[[fallthrough]];

		case ErrorState::Default:
		default:
			m_context     = NULL;
			m_pixelFormat = 0;
			break;
		}

		return false;
	}

	void GlContext::destroy()
	{
		if (NULL != m_hdc)
		{
			wglMakeCurrent(NULL, NULL);

			if (m_ownsContext)
			{
				wglDeleteContext(m_context);
			}

			m_context     = NULL;
			m_pixelFormat = 0;
			m_current     = NULL;

			ReleaseDC(NULL != m_dummyHwnd ? m_dummyHwnd : (HWND)m_nwh, m_hdc);
			m_hdc = NULL;
		}

		if (NULL != m_dummyHwnd)
		{
			DestroyWindow(m_dummyHwnd);
			m_dummyHwnd = NULL;
		}

		bx::dlclose(m_opengl32dll);
		m_opengl32dll = NULL;
	}

	void GlContext::resize(const SwapChain& _swapChain, uint32_t _reset)
	{
		BX_UNUSED(_swapChain);

		const bool vsync = !!(_reset & BGFX_RESET_VSYNC);
		m_swapInterval = vsync ? 1 : 0;

		if (NULL != wglSwapIntervalEXT)
		{
			// Apply to the currently-bound (main) context. Secondary SwapChainGL contexts
			// get the value applied lazily in makeCurrent() when they become current, since
			// wglSwapIntervalEXT is per-context on Windows.
			wglSwapIntervalEXT(m_swapInterval);
		}
	}

	uint64_t GlContext::getCaps() const
	{
		if (NULL == wglCreateContextAttribsARB)
		{
			return 0;
		}

		if (!m_ownsContext
		&&  (0 == m_pixelFormat || 0 == (m_pfd.dwFlags & PFD_DRAW_TO_WINDOW) ) )
		{
			return 0;
		}

		return BGFX_CAPS_SWAP_CHAIN;
	}

	SwapChainGL* GlContext::createSwapChain(void* _nwh, int32_t _width, int32_t _height)
	{
		BX_UNUSED(_width, _height);
		SwapChainGL* swapChain = BX_NEW(g_allocator, SwapChainGL)(_nwh);

		int result = SetPixelFormat(swapChain->m_hdc, m_pixelFormat, &m_pfd);
		BX_WARN(result, "SetPixelFormat failed (last err: 0x%08x)!", GetLastError() ); BX_UNUSED(result);

		swapChain->m_context = wglCreateContextAttribsARB(swapChain->m_hdc, m_context, m_contextAttrs);
		BX_ASSERT(NULL != swapChain->m_context, "Create swap chain failed: %x", glGetError() );
		return swapChain;
	}

	void GlContext::destroySwapChain(SwapChainGL*  _swapChain)
	{
		bx::deleteObject(g_allocator, _swapChain);
		wglMakeCurrent(m_hdc, m_context);
	}

	void GlContext::swap(SwapChainGL* _swapChain)
	{
		makeCurrent(_swapChain);

		if (NULL == _swapChain)
		{
			if (NULL != m_nwh)
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

			// wglSwapIntervalEXT is per-context on Windows, so re-apply the cached interval
			// every time a different context becomes current. Without this, secondary swap
			// chains keep their driver default (typically vsync ON) even after resize().
			if (NULL != wglSwapIntervalEXT)
			{
				wglSwapIntervalEXT(m_swapInterval);
			}
		}
	}

	bool GlContext::import()
	{
		BX_TRACE("Import:");

		bool imported = true;

#	define GL_EXTENSION(_optional, _proto, _func, _import)                                     \
		{                                                                                      \
			if (NULL == _func)                                                                 \
			{                                                                                  \
				_func = wglGetProc<_proto>(#_import);                                          \
				if (NULL == _func)                                                             \
				{                                                                              \
					_func = bx::dlsym<_proto>(m_opengl32dll, #_import);                        \
					BX_TRACE("    %p " #_func " (" #_import ")", _func);                       \
				}                                                                              \
				else                                                                           \
				{                                                                              \
					BX_TRACE("wgl %p " #_func " (" #_import ")", _func);                       \
				}                                                                              \
				if (!BX_IGNORE_C4127(_optional)                                                \
				&&  NULL == _func)                                                             \
				{                                                                              \
					BX_TRACE("Init error: Failed to import %s.", #_import);                    \
					imported = false;                                                          \
				}                                                                              \
			}                                                                                  \
		}

#	include "glimports.h"

#	undef GL_EXTENSION

		return imported;
	}

} } // namespace bgfx

#	endif // BGFX_USE_WGL
#endif // (BGFX_CONFIG_RENDERER_OPENGLES|BGFX_CONFIG_RENDERER_OPENGL)
