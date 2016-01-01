/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

#	if BGFX_USE_EGL

#		if BX_PLATFORM_RPI
#			include <X11/Xlib.h>
#			include <bcm_host.h>
#		endif // BX_PLATFORM_RPI

namespace bgfx { namespace gl
{
#ifndef EGL_CONTEXT_FLAG_NO_ERROR_BIT_KHR
#	define EGL_CONTEXT_FLAG_NO_ERROR_BIT_KHR 0x00000008
#endif // EGL_CONTEXT_FLAG_NO_ERROR_BIT_KHR

#if BGFX_USE_GL_DYNAMIC_LIB

	typedef void (*EGLPROC)(void);

	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLCHOOSECONFIGPROC)(EGLDisplay dpy, const EGLint *attrib_list,	EGLConfig *configs, EGLint config_size,	EGLint *num_config);
	typedef EGLContext  (EGLAPIENTRY* PFNEGLCREATECONTEXTPROC)(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
	typedef EGLSurface  (EGLAPIENTRY* PFNEGLCREATEWINDOWSURFACEPROC)(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list);
	typedef EGLint      (EGLAPIENTRY* PFNEGLGETERRORPROC)(void);
	typedef EGLDisplay  (EGLAPIENTRY* PFNEGLGETDISPLAYPROC)(EGLNativeDisplayType display_id);
	typedef EGLPROC     (EGLAPIENTRY* PFNEGLGETPROCADDRESSPROC)(const char *procname);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLINITIALIZEPROC)(EGLDisplay dpy, EGLint *major, EGLint *minor);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLMAKECURRENTPROC)(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLDESTROYCONTEXTPROC)(EGLDisplay dpy, EGLContext ctx);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLDESTROYSURFACEPROC)(EGLDisplay dpy, EGLSurface surface);
	typedef const char* (EGLAPIENTRY* PGNEGLQUERYSTRINGPROC)(EGLDisplay dpy, EGLint name);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLSWAPBUFFERSPROC)(EGLDisplay dpy, EGLSurface surface);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLSWAPINTERVALPROC)(EGLDisplay dpy, EGLint interval);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLTERMINATEPROC)(EGLDisplay dpy);

#define EGL_IMPORT \
			EGL_IMPORT_FUNC(PFNEGLCHOOSECONFIGPROC,        eglChooseConfig); \
			EGL_IMPORT_FUNC(PFNEGLCREATECONTEXTPROC,       eglCreateContext); \
			EGL_IMPORT_FUNC(PFNEGLCREATEWINDOWSURFACEPROC, eglCreateWindowSurface); \
			EGL_IMPORT_FUNC(PFNEGLGETDISPLAYPROC,          eglGetDisplay); \
			EGL_IMPORT_FUNC(PFNEGLGETERRORPROC,            eglGetError); \
			EGL_IMPORT_FUNC(PFNEGLGETPROCADDRESSPROC,      eglGetProcAddress); \
			EGL_IMPORT_FUNC(PFNEGLDESTROYCONTEXTPROC,      eglDestroyContext); \
			EGL_IMPORT_FUNC(PFNEGLDESTROYSURFACEPROC,      eglDestroySurface); \
			EGL_IMPORT_FUNC(PFNEGLINITIALIZEPROC,          eglInitialize); \
			EGL_IMPORT_FUNC(PFNEGLMAKECURRENTPROC,         eglMakeCurrent); \
			EGL_IMPORT_FUNC(PGNEGLQUERYSTRINGPROC,         eglQueryString); \
			EGL_IMPORT_FUNC(PFNEGLSWAPBUFFERSPROC,         eglSwapBuffers); \
			EGL_IMPORT_FUNC(PFNEGLSWAPINTERVALPROC,        eglSwapInterval); \
			EGL_IMPORT_FUNC(PFNEGLTERMINATEPROC,           eglTerminate);

#define EGL_IMPORT_FUNC(_proto, _func) _proto _func
EGL_IMPORT
#undef EGL_IMPORT_FUNC

	void* eglOpen()
	{
		void* handle = bx::dlopen("libEGL." BX_DL_EXT);
		BGFX_FATAL(NULL != handle, Fatal::UnableToInitialize, "Failed to load libEGL dynamic library.");

#define EGL_IMPORT_FUNC(_proto, _func) \
			_func = (_proto)bx::dlsym(handle, #_func); \
			BX_TRACE("%p " #_func, _func); \
			BGFX_FATAL(NULL != _func, Fatal::UnableToInitialize, "Failed get " #_func ".")
EGL_IMPORT
#undef EGL_IMPORT_FUNC

		return handle;
	}

	void eglClose(void* _handle)
	{
		bx::dlclose(_handle);

#define EGL_IMPORT_FUNC(_proto, _func) _func = NULL
EGL_IMPORT
#undef EGL_IMPORT_FUNC
	}

#else

	void* eglOpen()
	{
		return NULL;
	}

	void eglClose(void* /*_handle*/)
	{
	}
#endif // BGFX_USE_GL_DYNAMIC_LIB

#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func = NULL
#	include "glimports.h"

	static EGLint s_contextAttrs[16];

	struct SwapChainGL
	{
		SwapChainGL(EGLDisplay _display, EGLConfig _config, EGLContext _context, EGLNativeWindowType _nwh)
			: m_nwh(_nwh)
			, m_display(_display)
		{
			m_surface = eglCreateWindowSurface(m_display, _config, _nwh, NULL);
			BGFX_FATAL(m_surface != EGL_NO_SURFACE, Fatal::UnableToInitialize, "Failed to create surface.");

			m_context = eglCreateContext(m_display, _config, _context, s_contextAttrs);
			BX_CHECK(NULL != m_context, "Create swap chain failed: %x", eglGetError() );

			makeCurrent();
			GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f) );
			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );
			swapBuffers();
			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );
			swapBuffers();
		}

		~SwapChainGL()
		{
			eglMakeCurrent(EGL_NO_DISPLAY, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglDestroyContext(m_display, m_context);
			eglDestroySurface(m_display, m_surface);
		}

		void makeCurrent()
		{
			eglMakeCurrent(m_display, m_surface, m_surface, m_context);
		}

		void swapBuffers()
		{
			eglSwapBuffers(m_display, m_surface);
		}

		EGLNativeWindowType m_nwh;
		EGLContext m_context;
		EGLDisplay m_display;
		EGLSurface m_surface;
	};

#	if BX_PLATFORM_RPI
	static EGL_DISPMANX_WINDOW_T s_dispmanWindow;
#	endif // BX_PLATFORM_RPI

	void GlContext::create(uint32_t _width, uint32_t _height)
	{
#	if BX_PLATFORM_RPI
		bcm_host_init();
#	endif // BX_PLATFORM_RPI

		m_eglLibrary = eglOpen();

		if (NULL == g_platformData.context)
		{
#	if BX_PLATFORM_RPI
			g_platformData.ndt = EGL_DEFAULT_DISPLAY;
#	endif // BX_PLATFORM_RPI

			BX_UNUSED(_width, _height);
			EGLNativeDisplayType ndt = (EGLNativeDisplayType)g_platformData.ndt;
			EGLNativeWindowType  nwh = (EGLNativeWindowType )g_platformData.nwh;

#	if BX_PLATFORM_WINDOWS
			if (NULL == g_platformData.ndt)
			{
				ndt = GetDC( (HWND)g_platformData.nwh);
			}
#	endif // BX_PLATFORM_WINDOWS

			m_display = eglGetDisplay(ndt);
			BGFX_FATAL(m_display != EGL_NO_DISPLAY, Fatal::UnableToInitialize, "Failed to create display %p", m_display);

			EGLint major = 0;
			EGLint minor = 0;
			EGLBoolean success = eglInitialize(m_display, &major, &minor);
			BGFX_FATAL(success && major >= 1 && minor >= 3, Fatal::UnableToInitialize, "Failed to initialize %d.%d", major, minor);

			BX_TRACE("EGL info:");
			const char* clientApis = eglQueryString(m_display, EGL_CLIENT_APIS);
			BX_TRACE("   APIs: %s", clientApis); BX_UNUSED(clientApis);

			const char* vendor = eglQueryString(m_display, EGL_VENDOR);
			BX_TRACE(" Vendor: %s", vendor); BX_UNUSED(vendor);

			const char* version = eglQueryString(m_display, EGL_VERSION);
			BX_TRACE("Version: %s", version); BX_UNUSED(version);

			const char* extensions = eglQueryString(m_display, EGL_EXTENSIONS);
			BX_TRACE("Supported EGL extensions:");
			dumpExtensions(extensions);

			EGLint attrs[] =
			{
				EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,

#	if BX_PLATFORM_ANDROID
				EGL_DEPTH_SIZE, 16,
#	else
				EGL_DEPTH_SIZE, 24,
#	endif // BX_PLATFORM_
				EGL_STENCIL_SIZE, 8,

				EGL_NONE
			};

			EGLint numConfig = 0;
			success = eglChooseConfig(m_display, attrs, &m_config, 1, &numConfig);
			BGFX_FATAL(success, Fatal::UnableToInitialize, "eglChooseConfig");

#	if BX_PLATFORM_ANDROID

			EGLint format;
			eglGetConfigAttrib(m_display, m_config, EGL_NATIVE_VISUAL_ID, &format);
			ANativeWindow_setBuffersGeometry( (ANativeWindow*)g_platformData.nwh, _width, _height, format);

#	elif BX_PLATFORM_RPI
			DISPMANX_DISPLAY_HANDLE_T dispmanDisplay = vc_dispmanx_display_open(0);
			DISPMANX_UPDATE_HANDLE_T  dispmanUpdate  = vc_dispmanx_update_start(0);

			VC_RECT_T dstRect = { 0, 0, int32_t(_width),        int32_t(_height)       };
			VC_RECT_T srcRect = { 0, 0, int32_t(_width)  << 16, int32_t(_height) << 16 };

			DISPMANX_ELEMENT_HANDLE_T dispmanElement = vc_dispmanx_element_add(dispmanUpdate
				, dispmanDisplay
				, 0
				, &dstRect
				, 0
				, &srcRect
				, DISPMANX_PROTECTION_NONE
				, NULL
				, NULL
				, DISPMANX_NO_ROTATE
				);

			s_dispmanWindow.element = dispmanElement;
			s_dispmanWindow.width   = _width;
			s_dispmanWindow.height  = _height;
			nwh = &s_dispmanWindow;

			vc_dispmanx_update_submit_sync(dispmanUpdate);
#	endif // BX_PLATFORM_ANDROID

			m_surface = eglCreateWindowSurface(m_display, m_config, nwh, NULL);
			BGFX_FATAL(m_surface != EGL_NO_SURFACE, Fatal::UnableToInitialize, "Failed to create surface.");

			const bool hasEglKhrCreateContext = !!bx::findIdentifierMatch(extensions, "EGL_KHR_create_context");
			const bool hasEglKhrNoError       = !!bx::findIdentifierMatch(extensions, "EGL_KHR_create_context_no_error");

			for (uint32_t ii = 0; ii < 2; ++ii)
			{
				bx::StaticMemoryBlockWriter writer(s_contextAttrs, sizeof(s_contextAttrs) );

				EGLint flags = 0;

#	if BX_PLATFORM_RPI
				BX_UNUSED(hasEglKhrCreateContext, hasEglKhrNoError);
#else
				if (hasEglKhrCreateContext)
				{
					bx::write(&writer, EGLint(EGL_CONTEXT_MAJOR_VERSION_KHR) );
					bx::write(&writer, EGLint(BGFX_CONFIG_RENDERER_OPENGLES / 10) );

					bx::write(&writer, EGLint(EGL_CONTEXT_MINOR_VERSION_KHR) );
					bx::write(&writer, EGLint(BGFX_CONFIG_RENDERER_OPENGLES % 10) );

					flags |= BGFX_CONFIG_DEBUG && hasEglKhrNoError ? 0
						| EGL_CONTEXT_FLAG_NO_ERROR_BIT_KHR
						: 0
						;

					if (0 == ii)
					{
						flags |= BGFX_CONFIG_DEBUG ? 0
							| EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR
//							| EGL_OPENGL_ES3_BIT_KHR
							: 0
							;

						bx::write(&writer, EGLint(EGL_CONTEXT_FLAGS_KHR) );
						bx::write(&writer, flags);
					}
				}
				else
#	endif // BX_PLATFORM_RPI
				{
					bx::write(&writer, EGLint(EGL_CONTEXT_CLIENT_VERSION) );
					bx::write(&writer, 2);
				}

				bx::write(&writer, EGLint(EGL_NONE) );

				m_context = eglCreateContext(m_display, m_config, EGL_NO_CONTEXT, s_contextAttrs);
				if (NULL != m_context)
				{
					break;
				}

				BX_TRACE("Failed to create EGL context with EGL_CONTEXT_FLAGS_KHR (%08x).", flags);
			}

			BGFX_FATAL(m_context != EGL_NO_CONTEXT, Fatal::UnableToInitialize, "Failed to create context.");

			success = eglMakeCurrent(m_display, m_surface, m_surface, m_context);
			BGFX_FATAL(success, Fatal::UnableToInitialize, "Failed to set context.");
			m_current = NULL;

			eglSwapInterval(m_display, 0);
		}

		import();
	}

	void GlContext::destroy()
	{
		if (NULL != m_display)
		{
			eglMakeCurrent(EGL_NO_DISPLAY, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglDestroyContext(m_display, m_context);
			eglDestroySurface(m_display, m_surface);
			eglTerminate(m_display);
			m_context = NULL;
		}

		eglClose(m_eglLibrary);

#	if BX_PLATFORM_RPI
		bcm_host_deinit();
#	endif // BX_PLATFORM_RPI
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
#	if BX_PLATFORM_ANDROID
		if (NULL != m_display)
		{
			EGLint format;
			eglGetConfigAttrib(m_display, m_config, EGL_NATIVE_VISUAL_ID, &format);
			ANativeWindow_setBuffersGeometry( (ANativeWindow*)g_platformData.nwh, _width, _height, format);
		}
#	elif BX_PLATFORM_EMSCRIPTEN
		emscripten_set_canvas_size(_width, _height);
#	else
		BX_UNUSED(_width, _height);
#	endif // BX_PLATFORM_*

		if (NULL != m_display)
		{
			bool vsync = !!(_flags&BGFX_RESET_VSYNC);
			eglSwapInterval(m_display, vsync ? 1 : 0);
		}
	}

	uint64_t GlContext::getCaps() const
	{
		return BX_ENABLED(0
						| BX_PLATFORM_LINUX
						| BX_PLATFORM_WINDOWS
						)
			? BGFX_CAPS_SWAP_CHAIN
			: 0
			;
	}

	SwapChainGL* GlContext::createSwapChain(void* _nwh)
	{
		return BX_NEW(g_allocator, SwapChainGL)(m_display, m_config, m_context, (EGLNativeWindowType)_nwh);
	}

	void GlContext::destroySwapChain(SwapChainGL* _swapChain)
	{
		BX_DELETE(g_allocator, _swapChain);
	}

	void GlContext::swap(SwapChainGL* _swapChain)
	{
		makeCurrent(_swapChain);

		if (NULL == _swapChain)
		{
			if (NULL != m_display)
			{
				eglSwapBuffers(m_display, m_surface);
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
				if (NULL != m_display)
				{
					eglMakeCurrent(m_display, m_surface, m_surface, m_context);
				}
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
#	if BX_PLATFORM_WINDOWS || BX_PLATFORM_LINUX
		void* glesv2 = bx::dlopen("libGLESv2." BX_DL_EXT);
#		define GL_EXTENSION(_optional, _proto, _func, _import) \
					{ \
						if (NULL == _func) \
						{ \
							_func = (_proto)bx::dlsym(glesv2, #_import); \
							BX_TRACE("\t%p " #_func " (" #_import ")", _func); \
							BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGLES context. eglGetProcAddress(\"%s\")", #_import); \
						} \
					}
#	else
#		define GL_EXTENSION(_optional, _proto, _func, _import) \
					{ \
						if (NULL == _func) \
						{ \
							_func = (_proto)eglGetProcAddress(#_import); \
							BX_TRACE("\t%p " #_func " (" #_import ")", _func); \
							BGFX_FATAL(_optional || NULL != _func, Fatal::UnableToInitialize, "Failed to create OpenGLES context. eglGetProcAddress(\"%s\")", #_import); \
						} \
					}
#	endif // BX_PLATFORM_
#	include "glimports.h"
	}

} /* namespace gl */ } // namespace bgfx

#	endif // BGFX_USE_EGL
#endif // (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
