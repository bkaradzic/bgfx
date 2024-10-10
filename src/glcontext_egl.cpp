/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"

#	if BGFX_USE_EGL

#		if BX_PLATFORM_RPI
#			include <X11/Xlib.h>
#			include <bcm_host.h>
#		endif // BX_PLATFORM_RPI

#define _EGL_CHECK(_check, _call)                                   \
	BX_MACRO_BLOCK_BEGIN                                            \
		EGLBoolean success = _call;                                 \
		_check(success, #_call "; EGL error 0x%x", eglGetError() ); \
	BX_MACRO_BLOCK_END

#if BGFX_CONFIG_DEBUG
#	define EGL_CHECK(_call) _EGL_CHECK(BX_ASSERT, _call)
#else
#	define EGL_CHECK(_call) _call
#endif // BGFX_CONFIG_DEBUG

namespace bgfx { namespace gl
{
#ifndef EGL_CONTEXT_FLAG_NO_ERROR_BIT_KHR
#	define EGL_CONTEXT_FLAG_NO_ERROR_BIT_KHR 0x00000008
#endif // EGL_CONTEXT_FLAG_NO_ERROR_BIT_KHR

#if BGFX_USE_GL_DYNAMIC_LIB

	typedef void (*EGLPROC)(void);

	typedef EGLBoolean  (EGLAPIENTRY* PGNEGLBINDAPIPROC)(EGLenum api);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLCHOOSECONFIGPROC)(EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config);
	typedef EGLContext  (EGLAPIENTRY* PFNEGLCREATECONTEXTPROC)(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint* attrib_list);
	typedef EGLSurface  (EGLAPIENTRY* PFNEGLCREATEPBUFFERSURFACEPROC)(EGLDisplay display, EGLConfig config, EGLint const* attrib_list);
	typedef EGLSurface  (EGLAPIENTRY* PFNEGLCREATEWINDOWSURFACEPROC)(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint* attrib_list);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLDESTROYCONTEXTPROC)(EGLDisplay dpy, EGLContext ctx);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLDESTROYSURFACEPROC)(EGLDisplay dpy, EGLSurface surface);
	typedef EGLContext  (EGLAPIENTRY* PFNEGLGETCURRENTCONTEXTPROC)(void);
	typedef EGLSurface  (EGLAPIENTRY* PFNEGLGETCURRENTSURFACEPROC)(EGLint readdraw);
	typedef EGLDisplay  (EGLAPIENTRY* PFNEGLGETDISPLAYPROC)(EGLNativeDisplayType display_id);
	typedef EGLint      (EGLAPIENTRY* PFNEGLGETERRORPROC)(void);
	typedef EGLPROC     (EGLAPIENTRY* PFNEGLGETPROCADDRESSPROC)(const char* procname);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLINITIALIZEPROC)(EGLDisplay dpy, EGLint* major, EGLint* minor);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLMAKECURRENTPROC)(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLSWAPBUFFERSPROC)(EGLDisplay dpy, EGLSurface surface);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLSWAPINTERVALPROC)(EGLDisplay dpy, EGLint interval);
	typedef EGLBoolean  (EGLAPIENTRY* PFNEGLTERMINATEPROC)(EGLDisplay dpy);
	typedef const char* (EGLAPIENTRY* PGNEGLQUERYSTRINGPROC)(EGLDisplay dpy, EGLint name);

#define EGL_IMPORT                                                            \
	EGL_IMPORT_FUNC(PGNEGLBINDAPIPROC,              eglBindAPI);              \
	EGL_IMPORT_FUNC(PFNEGLCHOOSECONFIGPROC,         eglChooseConfig);         \
	EGL_IMPORT_FUNC(PFNEGLCREATECONTEXTPROC,        eglCreateContext);        \
	EGL_IMPORT_FUNC(PFNEGLCREATEPBUFFERSURFACEPROC, eglCreatePbufferSurface); \
	EGL_IMPORT_FUNC(PFNEGLCREATEWINDOWSURFACEPROC,  eglCreateWindowSurface);  \
	EGL_IMPORT_FUNC(PFNEGLDESTROYCONTEXTPROC,       eglDestroyContext);       \
	EGL_IMPORT_FUNC(PFNEGLDESTROYSURFACEPROC,       eglDestroySurface);       \
	EGL_IMPORT_FUNC(PFNEGLGETCURRENTCONTEXTPROC,    eglGetCurrentContext);    \
	EGL_IMPORT_FUNC(PFNEGLGETCURRENTSURFACEPROC,    eglGetCurrentSurface);    \
	EGL_IMPORT_FUNC(PFNEGLGETDISPLAYPROC,           eglGetDisplay);           \
	EGL_IMPORT_FUNC(PFNEGLGETERRORPROC,             eglGetError);             \
	EGL_IMPORT_FUNC(PFNEGLGETPROCADDRESSPROC,       eglGetProcAddress);       \
	EGL_IMPORT_FUNC(PFNEGLINITIALIZEPROC,           eglInitialize);           \
	EGL_IMPORT_FUNC(PFNEGLMAKECURRENTPROC,          eglMakeCurrent);          \
	EGL_IMPORT_FUNC(PFNEGLRELEASETHREADPROC,        eglReleaseThread);        \
	EGL_IMPORT_FUNC(PFNEGLSWAPBUFFERSPROC,          eglSwapBuffers);          \
	EGL_IMPORT_FUNC(PFNEGLSWAPINTERVALPROC,         eglSwapInterval);         \
	EGL_IMPORT_FUNC(PFNEGLTERMINATEPROC,            eglTerminate);            \
	EGL_IMPORT_FUNC(PGNEGLQUERYSTRINGPROC,          eglQueryString);          \

#define EGL_IMPORT_FUNC(_proto, _func) _proto _func
EGL_IMPORT
#undef EGL_IMPORT_FUNC

	void* eglOpen()
	{
	    void* handle = bx::dlopen(
#if BX_PLATFORM_LINUX
			"libEGL.so.1"
#else
			"libEGL." BX_DL_EXT
#endif // BX_PLATFORM_*
			);

		BGFX_FATAL(NULL != handle, Fatal::UnableToInitialize, "Failed to load libEGL dynamic library.");

#define EGL_IMPORT_FUNC(_proto, _func)         \
	_func = (_proto)bx::dlsym(handle, #_func); \
	BX_TRACE("%p " #_func, _func);             \
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

#if BX_PLATFORM_LINUX
#	define WL_EGL_IMPORT                                                                            \
		WL_EGL_FUNC(struct wl_egl_window *, wl_egl_window_create, (struct wl_surface *, int, int) ) \
		WL_EGL_FUNC(void, wl_egl_window_destroy, (struct wl_egl_window *))                          \
		WL_EGL_FUNC(void, wl_egl_window_resize, (struct wl_egl_window *, int, int, int, int))       \
		WL_EGL_FUNC(void, wl_egl_window_get_attached_size, (struct wl_egl_window *, int *, int *) ) \

#	define WL_EGL_FUNC(rt, fname, params)     \
		typedef rt(*PFNWLEGL_##fname) params; \
		PFNWLEGL_##fname BGFX_WAYLAND_##fname;

WL_EGL_IMPORT

#	undef WL_EGL_FUNC

	void* waylandEglOpen()
	{
		void* handle = bx::dlopen("libwayland-egl.so.1");
		BGFX_FATAL(handle != NULL, Fatal::UnableToInitialize, "Could not dlopen() libwayland-egl.so.1");

#	define WL_EGL_FUNC(rt, fname, params) BGFX_WAYLAND_##fname = (PFNWLEGL_##fname) bx::dlsym(handle, #fname);
		WL_EGL_IMPORT
#	undef WL_EGL_FUNC

		return handle;
	}

	void waylandEglClose(void* _handle)
	{
		bx::dlclose(_handle);

#	define WL_EGL_FUNC(rt, fname, params) BGFX_WAYLAND_##fname = NULL;
		WL_EGL_IMPORT
#	undef WL_EGL_FUNC
	}
#endif // BX_PLATFORM_LINUX

#	define GL_IMPORT(_optional, _proto, _func, _import) _proto _func = NULL
#	include "glimports.h"

	static EGLint s_contextAttrs[16];

	struct SwapChainGL
	{
		SwapChainGL(EGLDisplay _display, EGLConfig _config, EGLContext _context, EGLNativeWindowType _nwh, int _width, int _height)
			: m_nwh(_nwh)
			, m_display(_display)
#	if BX_PLATFORM_LINUX
			, m_eglWindow(NULL)
#	endif
		{
			EGLSurface defaultSurface = eglGetCurrentSurface(EGL_DRAW);

			BX_UNUSED(_width, _height);

			if (EGLNativeWindowType(0) == _nwh)
			{
				m_surface = eglCreatePbufferSurface(m_display, _config, NULL);
			}
			else
			{
#	if BX_PLATFORM_LINUX
				if (g_platformData.type == NativeWindowHandleType::Wayland)
				{
					// A wl_surface needs to be first wrapped in a wl_egl_window
					// before it can be used to create the EGLSurface.
					m_eglWindow = BGFX_WAYLAND_wl_egl_window_create( (wl_surface*)_nwh, _width, _height);
					_nwh = (EGLNativeWindowType) m_eglWindow;
				}
#	endif
				m_surface = eglCreateWindowSurface(m_display, _config, _nwh, NULL);
			}

			BGFX_FATAL(m_surface != EGL_NO_SURFACE, Fatal::UnableToInitialize, "Failed to create surface.");

			m_context = eglCreateContext(m_display, _config, _context, s_contextAttrs);
			BX_ASSERT(NULL != m_context, "Create swap chain failed: %x", eglGetError() );

			makeCurrent();
			GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f) );
			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );
			swapBuffers();

			GL_CHECK(glClear(GL_COLOR_BUFFER_BIT) );
			swapBuffers();

			EGL_CHECK(eglMakeCurrent(m_display, defaultSurface, defaultSurface, _context) );
		}

		~SwapChainGL()
		{
			EGLSurface defaultSurface = eglGetCurrentSurface(EGL_DRAW);
			EGLContext defaultContext = eglGetCurrentContext();

			EGL_CHECK(eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) );
			EGL_CHECK(eglDestroyContext(m_display, m_context) );
			EGL_CHECK(eglDestroySurface(m_display, m_surface) );
#	if BX_PLATFORM_LINUX
			if (m_eglWindow)
			{
				BGFX_WAYLAND_wl_egl_window_destroy(m_eglWindow);
			}
#	endif
			EGL_CHECK(eglMakeCurrent(m_display, defaultSurface, defaultSurface, defaultContext) );
		}

		void makeCurrent()
		{
			EGL_CHECK(eglMakeCurrent(m_display, m_surface, m_surface, m_context) );
		}

		void swapBuffers()
		{
			EGL_CHECK(eglSwapBuffers(m_display, m_surface) );
		}

		EGLNativeWindowType m_nwh;
		EGLContext m_context;
		EGLDisplay m_display;
		EGLSurface m_surface;
#	if BX_PLATFORM_LINUX
		wl_egl_window *m_eglWindow;
#	endif
	};

#	if BX_PLATFORM_RPI
	static EGL_DISPMANX_WINDOW_T s_dispmanWindow;
#	endif // BX_PLATFORM_RPI

	void GlContext::create(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		BX_UNUSED(_flags);

#	if BX_PLATFORM_RPI
		bcm_host_init();
#	endif // BX_PLATFORM_RPI

		m_eglDll = eglOpen();

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

			m_display = eglGetDisplay(NULL == ndt ? EGL_DEFAULT_DISPLAY : ndt);
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

			if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
			{
				EGLBoolean ok = eglBindAPI(EGL_OPENGL_API);
				BGFX_FATAL(ok, Fatal::UnableToInitialize, "Could not set API! error: %d", eglGetError());
			}

			const bool hasEglAndroidRecordable = !bx::findIdentifierMatch(extensions, "EGL_ANDROID_recordable").isEmpty();

			const uint32_t glVersion = !!BGFX_CONFIG_RENDERER_OPENGL
				? BGFX_CONFIG_RENDERER_OPENGL
				: BGFX_CONFIG_RENDERER_OPENGLES
				;

#if BX_PLATFORM_ANDROID
			const uint32_t msaa = (_flags&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
			const uint32_t msaaSamples = msaa == 0 ? 0 : 1<<msaa;
			m_msaaContext = true;
#endif // BX_PLATFORM_ANDROID

			const bool headless = EGLNativeWindowType(0) == nwh;

			EGLint attrs[] =
			{
				EGL_RENDERABLE_TYPE, !!BGFX_CONFIG_RENDERER_OPENGL
					? EGL_OPENGL_BIT
					: (glVersion >= 30) ? EGL_OPENGL_ES3_BIT_KHR : EGL_OPENGL_ES2_BIT
					,

				EGL_SURFACE_TYPE, headless ? EGL_PBUFFER_BIT : EGL_WINDOW_BIT,

				EGL_BLUE_SIZE,  8,
				EGL_GREEN_SIZE, 8,
				EGL_RED_SIZE,   8,
				EGL_ALPHA_SIZE, 8,

#	if BX_PLATFORM_ANDROID
				EGL_DEPTH_SIZE, 16,
				EGL_SAMPLES, (EGLint)msaaSamples,
#	else
				EGL_DEPTH_SIZE, 24,
#	endif // BX_PLATFORM_
				EGL_STENCIL_SIZE, 8,

				// Android Recordable surface
				hasEglAndroidRecordable ? EGL_RECORDABLE_ANDROID : EGL_NONE,
				hasEglAndroidRecordable ? 1                      : EGL_NONE,

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

#	if BX_PLATFORM_LINUX
			if (g_platformData.type == NativeWindowHandleType::Wayland)
			{
				m_waylandEglDll = waylandEglOpen();
			}
#	endif

			if (headless)
			{
				EGLint pbAttribs[] =
				{
					EGL_WIDTH,  EGLint(1),
					EGL_HEIGHT, EGLint(1),

					EGL_NONE
				};

				m_surface = eglCreatePbufferSurface(m_display, m_config, pbAttribs);
			}
			else
			{
#	if BX_PLATFORM_LINUX
				if (g_platformData.type == NativeWindowHandleType::Wayland)
				{
					// A wl_surface needs to be first wrapped in a wl_egl_window
					// before it can be used to create the EGLSurface.
					m_eglWindow = BGFX_WAYLAND_wl_egl_window_create( (wl_surface*)nwh, _width, _height);
					nwh = (EGLNativeWindowType) m_eglWindow;
				}
#	endif
				m_surface = eglCreateWindowSurface(m_display, m_config, nwh, NULL);
			}

			BGFX_FATAL(m_surface != EGL_NO_SURFACE, Fatal::UnableToInitialize, "Failed to create surface.");

			const bool hasEglKhrCreateContext = !bx::findIdentifierMatch(extensions, "EGL_KHR_create_context").isEmpty();
			const bool hasEglKhrNoError       = !bx::findIdentifierMatch(extensions, "EGL_KHR_create_context_no_error").isEmpty();

			for (uint32_t ii = 0; ii < 2; ++ii)
			{
				bx::StaticMemoryBlockWriter writer(s_contextAttrs, sizeof(s_contextAttrs) );

				EGLint flags = 0;

#	if BX_PLATFORM_RPI
				BX_UNUSED(hasEglKhrCreateContext, hasEglKhrNoError);
#	else
				if (hasEglKhrCreateContext)
				{
					if (BX_ENABLED(BGFX_CONFIG_RENDERER_OPENGL) )
					{
						bx::write(&writer, EGLint(EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR), bx::ErrorAssert{});
						bx::write(&writer, EGLint(EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR), bx::ErrorAssert{});
					}

					bx::write(&writer, EGLint(EGL_CONTEXT_MAJOR_VERSION_KHR), bx::ErrorAssert{});
					bx::write(&writer, EGLint(glVersion / 10), bx::ErrorAssert{});

					bx::write(&writer, EGLint(EGL_CONTEXT_MINOR_VERSION_KHR), bx::ErrorAssert{});
					bx::write(&writer, EGLint(glVersion % 10), bx::ErrorAssert{});

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

						bx::write(&writer, EGLint(EGL_CONTEXT_FLAGS_KHR), bx::ErrorAssert{} );
						bx::write(&writer, flags, bx::ErrorAssert{});
					}
				}
				else
#	endif // BX_PLATFORM_RPI
				{
					bx::write(&writer, EGLint(EGL_CONTEXT_CLIENT_VERSION), bx::ErrorAssert{} );
					bx::write(&writer, EGLint(glVersion / 10), bx::ErrorAssert{} );
				}

				bx::write(&writer, EGLint(EGL_NONE), bx::ErrorAssert{} );

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

		g_internalData.context = m_context;
	}

	void GlContext::destroy()
	{
		BX_TRACE("GLContext::destroy()");
		if (NULL != m_display)
		{
			EGL_CHECK(eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT) );
			EGL_CHECK(eglDestroyContext(m_display, m_context) );
			EGL_CHECK(eglDestroySurface(m_display, m_surface) );

#	if BX_PLATFORM_LINUX
			if (m_eglWindow)
			{
				BGFX_WAYLAND_wl_egl_window_destroy(m_eglWindow);
				waylandEglClose(m_waylandEglDll);
				m_waylandEglDll = NULL;
			}
#	endif

			EGL_CHECK(eglTerminate(m_display) );
			m_context = NULL;
		}

		EGL_CHECK(eglReleaseThread() );
		eglClose(m_eglDll);
		m_eglDll = NULL;

#	if BX_PLATFORM_RPI
		bcm_host_deinit();
#	endif // BX_PLATFORM_RPI
	}

	void GlContext::resize(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
#	if BX_PLATFORM_ANDROID
		if (NULL != m_display)
		{
			EGLNativeWindowType nwh = (EGLNativeWindowType )g_platformData.nwh;
			eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglDestroySurface(m_display, m_surface);
			m_surface = eglCreateWindowSurface(m_display, m_config, nwh, NULL);
			BGFX_FATAL(m_surface != EGL_NO_SURFACE, Fatal::UnableToInitialize, "Failed to create surface.");
			EGLBoolean success = eglMakeCurrent(m_display, m_surface, m_surface, m_context);
			BGFX_FATAL(success, Fatal::UnableToInitialize, "Failed to set context.");

			EGLint format;
			eglGetConfigAttrib(m_display, m_config, EGL_NATIVE_VISUAL_ID, &format);
			ANativeWindow_setBuffersGeometry( (ANativeWindow*)g_platformData.nwh, _width, _height, format);
		}
#	elif BX_PLATFORM_EMSCRIPTEN
		EMSCRIPTEN_CHECK(emscripten_set_canvas_element_size(HTML5_TARGET_CANVAS_SELECTOR, _width, _height) );
#	elif BX_PLATFORM_LINUX
		if (NULL != m_eglWindow)
		{
			BGFX_WAYLAND_wl_egl_window_resize(m_eglWindow, _width, _height, 0, 0);
		}
#	else
		BX_UNUSED(_width, _height);
#	endif // BX_PLATFORM_*

		if (NULL != m_display)
		{
			bool vsync = !!(_flags&BGFX_RESET_VSYNC);
			EGL_CHECK(eglSwapInterval(m_display, vsync ? 1 : 0) );
		}
	}

	uint64_t GlContext::getCaps() const
	{
		return BX_ENABLED(0
			| BX_PLATFORM_LINUX
			| BX_PLATFORM_WINDOWS
			| BX_PLATFORM_ANDROID
			)
			? BGFX_CAPS_SWAP_CHAIN
			: 0
			;
	}

	SwapChainGL* GlContext::createSwapChain(void* _nwh, int _width, int _height)
	{
		return BX_NEW(g_allocator, SwapChainGL)(m_display, m_config, m_context, (EGLNativeWindowType)_nwh, _width, _height);
	}

	void GlContext::destroySwapChain(SwapChainGL* _swapChain)
	{
		bx::deleteObject(g_allocator, _swapChain);
	}

	void GlContext::swap(SwapChainGL* _swapChain)
	{
		makeCurrent(_swapChain);

		if (NULL == _swapChain)
		{
			if (NULL != m_display)
			{
				EGL_CHECK(eglSwapBuffers(m_display, m_surface) );
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
					EGL_CHECK(eglMakeCurrent(m_display, m_surface, m_surface, m_context) );
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
#		if BX_PLATFORM_WINDOWS
#			define LIBRARY_NAME "libGL.dll"
#		elif BX_PLATFORM_LINUX
#			if BGFX_CONFIG_RENDERER_OPENGL
#				define LIBRARY_NAME "libGL.so.1"
#			else
#				define LIBRARY_NAME "libGLESv2.so.2"
#			endif
#		endif

		void* lib = bx::dlopen(LIBRARY_NAME);

#		define GL_EXTENSION(_optional, _proto, _func, _import)                           \
			{                                                                            \
				if (NULL == _func)                                                       \
				{                                                                        \
					_func = bx::dlsym<_proto>(lib, #_import);                            \
					BX_TRACE("\t%p " #_func " (" #_import ")", _func);                   \
					BGFX_FATAL(_optional || NULL != _func                                \
						, Fatal::UnableToInitialize                                      \
						, "Failed to create OpenGLES context. eglGetProcAddress(\"%s\")" \
						, #_import);                                                     \
				}                                                                        \
			}
#	else
#		define GL_EXTENSION(_optional, _proto, _func, _import)                           \
			{                                                                            \
				if (NULL == _func)                                                       \
				{                                                                        \
					_func = reinterpret_cast<_proto>(eglGetProcAddress(#_import) );      \
					BX_TRACE("\t%p " #_func " (" #_import ")", _func);                   \
					BGFX_FATAL(_optional || NULL != _func                                \
						, Fatal::UnableToInitialize                                      \
						, "Failed to create OpenGLES context. eglGetProcAddress(\"%s\")" \
						, #_import);                                                     \
				}                                                                        \
			}

#	endif // BX_PLATFORM_

#	include "glimports.h"

#	undef GL_EXTENSION
	}

} /* namespace gl */ } // namespace bgfx

#	endif // BGFX_USE_EGL
#endif // (BGFX_CONFIG_RENDERER_OPENGLES || BGFX_CONFIG_RENDERER_OPENGL)
