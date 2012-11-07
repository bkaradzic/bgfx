/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"
#	include <bx/timer.h>
#	include <bx/uint32_t.h>

#if BGFX_CONFIG_RENDERER_OPENGL
#	define glClearDepthf(_depth) glClearDepth(_depth)
#endif // BGFX_CONFIG_RENDERER_OPENGL

namespace bgfx
{
#if BGFX_USE_WGL
	PFNWGLGETPROCADDRESSPROC wglGetProcAddress;
	PFNWGLMAKECURRENTPROC wglMakeCurrent;
	PFNWGLCREATECONTEXTPROC wglCreateContext;
	PFNWGLDELETECONTEXTPROC wglDeleteContext;
#endif // BGFX_USE_WGL

#define GL_IMPORT(_optional, _proto, _func) _proto _func
#include "glimports.h"
#undef GL_IMPORT

	static void GL_APIENTRY stubVertexAttribDivisor(GLuint /*_index*/, GLuint /*_divisor*/)
	{
	}

	static void GL_APIENTRY stubDrawArraysInstanced(GLenum _mode, GLint _first, GLsizei _count, GLsizei /*_primcount*/)
	{
		glDrawArrays(_mode, _first, _count);
	}

	static void GL_APIENTRY stubDrawElementsInstanced(GLenum _mode, GLsizei _count, GLenum _type, const GLvoid* _indices, GLsizei /*_primcount*/)
	{
		glDrawElements(_mode, _count, _type, _indices);
	}

#if BGFX_CONFIG_RENDERER_OPENGLES3
#	define s_vertexAttribDivisor glVertexAttribDivisor
#	define s_drawArraysInstanced glDrawArraysInstanced
#	define s_drawElementsInstanced glDrawElementsInstanced
#else
	static PFNGLVERTEXATTRIBDIVISORBGFXPROC s_vertexAttribDivisor = stubVertexAttribDivisor;
	static PFNGLDRAWARRAYSINSTANCEDBGFXPROC s_drawArraysInstanced = stubDrawArraysInstanced;
	static PFNGLDRAWELEMENTSINSTANCEDBGFXPROC s_drawElementsInstanced = stubDrawElementsInstanced;
#endif // BGFX_CONFIG_RENDERER_OPENGLES3

	typedef void (*PostSwapBuffersFn)(uint32_t _width, uint32_t _height);

#if BX_PLATFORM_NACL
	void naclSwapCompleteCb(void* _data, int32_t _result);

	PP_CompletionCallback naclSwapComplete = 
	{
		naclSwapCompleteCb,
		NULL,
		PP_COMPLETIONCALLBACK_FLAG_NONE
	};
#endif // BX_PLATFORM_NACL

	struct RendererContext
	{
		RendererContext()
			: m_dxtSupport(false)
			, m_flip(false)
			, m_postSwapBuffers(NULL)
			, m_hash( (BX_PLATFORM_WINDOWS<<1) | BX_ARCH_64BIT)
#if BX_PLATFORM_NACL
			, m_context(0)
			, m_instance(0)
			, m_instInterface(NULL)
			, m_graphicsInterface(NULL)
			, m_instancedArrays(NULL)
#elif BGFX_USE_WGL
			, m_context(NULL)
			, m_hdc(NULL)
#elif BGFX_USE_EGL
			, m_context(NULL)
			, m_display(NULL)
			, m_surface(NULL)
#elif BX_PLATFORM_LINUX
			, m_context(0)
			, m_window(0)
			, m_display(NULL)
#endif // BX_PLATFORM_
		{
			memset(&m_resolution, 0, sizeof(m_resolution) );
		}

		void updateResolution(const Resolution& _resolution)
		{
			if (m_resolution.m_width != _resolution.m_width
			||  m_resolution.m_height != _resolution.m_height
			||  m_resolution.m_flags != _resolution.m_flags)
			{
				m_textVideoMem.resize(false, _resolution.m_width, _resolution.m_height);
				m_textVideoMem.clear();

				m_resolution = _resolution;
				setRenderContextSize(_resolution.m_width, _resolution.m_height);
			}
		}

		void setRenderContextSize(uint32_t _width, uint32_t _height)
		{
			if (_width != 0
			||  _height != 0)
			{
#if BX_PLATFORM_NACL
				if (0 == m_context)
				{
					BX_TRACE("create context");

					int32_t attribs[] =
					{
						PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 8,
						PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 24,
						PP_GRAPHICS3DATTRIB_STENCIL_SIZE, 8,
						PP_GRAPHICS3DATTRIB_SAMPLES, 0,
						PP_GRAPHICS3DATTRIB_SAMPLE_BUFFERS, 0,
						PP_GRAPHICS3DATTRIB_WIDTH, _width,
						PP_GRAPHICS3DATTRIB_HEIGHT, _height,
						PP_GRAPHICS3DATTRIB_NONE
					};

					m_context = m_graphicsInterface->Create(m_instance, 0, attribs);
					m_instInterface->BindGraphics(m_instance, m_context);
					glSetCurrentContextPPAPI(m_context);
					m_graphicsInterface->SwapBuffers(m_context, naclSwapComplete);

#if 0
#	define GL_IMPORT(_optional, _proto, _func) \
			{ \
				_func = (_proto)eglGetProcAddress(#_func); \
				BGFX_FATAL(_optional || NULL != _func, Fatal::OPENGL_UnableToCreateContext, "Failed to create OpenGL context. eglGetProcAddress(\"%s\")", #_func); \
			}
#	include "glimports.h"
#	undef GL_IMPORT
#endif
				}
				else
				{
					m_graphicsInterface->ResizeBuffers(m_context, _width, _height);
				}

#elif BGFX_USE_WGL
				if (NULL == m_hdc)
				{
					m_opengl32dll = LoadLibrary("opengl32.dll");
					BGFX_FATAL(NULL != m_opengl32dll, Fatal::OPENGL_UnableToCreateContext, "Failed to load opengl32.dll.");

					wglGetProcAddress = (PFNWGLGETPROCADDRESSPROC)GetProcAddress(m_opengl32dll, "wglGetProcAddress");
					BGFX_FATAL(NULL != wglGetProcAddress, Fatal::OPENGL_UnableToCreateContext, "Failed get wglGetProcAddress.");

					wglMakeCurrent = (PFNWGLMAKECURRENTPROC)GetProcAddress(m_opengl32dll, "wglMakeCurrent");
					BGFX_FATAL(NULL != wglMakeCurrent, Fatal::OPENGL_UnableToCreateContext, "Failed get wglMakeCurrent.");

					wglCreateContext = (PFNWGLCREATECONTEXTPROC)GetProcAddress(m_opengl32dll, "wglCreateContext");
					BGFX_FATAL(NULL != wglCreateContext, Fatal::OPENGL_UnableToCreateContext, "Failed get wglCreateContext.");

					wglDeleteContext = (PFNWGLDELETECONTEXTPROC)GetProcAddress(m_opengl32dll, "wglDeleteContext");
					BGFX_FATAL(NULL != wglDeleteContext, Fatal::OPENGL_UnableToCreateContext, "Failed get wglDeleteContext.");

					m_hdc = GetDC(g_bgfxHwnd);
					BGFX_FATAL(NULL != m_hdc, Fatal::OPENGL_UnableToCreateContext, "GetDC failed!");

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
					BGFX_FATAL(0 != pixelFormat, Fatal::OPENGL_UnableToCreateContext, "ChoosePixelFormat failed!");

					DescribePixelFormat(m_hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

					int result;
					result = SetPixelFormat(m_hdc, pixelFormat, &pfd);
					BGFX_FATAL(0 != result, Fatal::OPENGL_UnableToCreateContext, "SetPixelFormat failed!");

					m_context = wglCreateContext(m_hdc);
					BGFX_FATAL(NULL != m_context, Fatal::OPENGL_UnableToCreateContext, "wglCreateContext failed!");
					
					result = wglMakeCurrent(m_hdc, m_context);
					BGFX_FATAL(0 != result, Fatal::OPENGL_UnableToCreateContext, "wglMakeCurrent failed!");

#	define GL_IMPORT(_optional, _proto, _func) \
				{ \
					_func = (_proto)wglGetProcAddress(#_func); \
					if (_func == NULL) \
					{ \
						_func = (_proto)GetProcAddress(m_opengl32dll, #_func); \
					} \
					BGFX_FATAL(_optional || NULL != _func, Fatal::OPENGL_UnableToCreateContext, "Failed to create OpenGL context. wglGetProcAddress(\"%s\")", #_func); \
				}
#	include "glimports.h"
#	undef GL_IMPORT
				}
#elif BX_PLATFORM_LINUX

				if (0 == m_display)
				{
					Display* display = XOpenDisplay(0);
					XLockDisplay(display);
					BGFX_FATAL(display, Fatal::OPENGL_UnableToCreateContext, "Failed to open X display (0).");

					int glxMajor, glxMinor;
					if (!glXQueryVersion(display, &glxMajor, &glxMinor) )
					{
						BGFX_FATAL(false, Fatal::OPENGL_UnableToCreateContext, "Failed to query GLX version");
					}
					BGFX_FATAL((glxMajor == 1 && glxMinor >= 3) || glxMajor > 1, Fatal::OPENGL_UnableToCreateContext, "GLX version is not >=1.3 (%d.%d).", glxMajor, glxMinor);

					const int glxAttribs[] =
					{
						GLX_X_RENDERABLE, True,
						GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
						GLX_RENDER_TYPE, GLX_RGBA_BIT,
						GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
						GLX_RED_SIZE, 8,
						GLX_BLUE_SIZE, 8,
						GLX_GREEN_SIZE, 8,
						GLX_ALPHA_SIZE, 8,
						GLX_DEPTH_SIZE, 24,
						GLX_STENCIL_SIZE, 8,
						GLX_DOUBLEBUFFER, True,
						None,
					};

					// Find suitable config
					GLXFBConfig	bestconfig = NULL;

					int nconfigs;
					GLXFBConfig* configs = glXChooseFBConfig(display, DefaultScreen(display), glxAttribs, &nconfigs);

					XVisualInfo* visualInfo = 0;
					for (int ii = 0; ii < nconfigs; ++ii)
					{
						visualInfo = glXGetVisualFromFBConfig(display, configs[ii]);
						if (visualInfo)
						{
							// Check if meets min spec
							bool validconfig = true;
							for (uint32_t attridx = 0; attridx < countof(glxAttribs)-1 && glxAttribs[attridx] != None; attridx += 2)
							{
								int value;
								glXGetFBConfigAttrib(display, configs[ii], glxAttribs[attridx], &value);
								if (value < glxAttribs[attridx + 1])
								{
									validconfig = false;
									break;
								}
							}

							if (validconfig)
							{
								bestconfig = configs[ii];
								break;
							}
						}

						XFree(visualInfo);
						visualInfo = 0;
					}

					XFree(configs);
					BGFX_FATAL(visualInfo, Fatal::OPENGL_UnableToCreateContext, "Failed to find a suitable X11 display configuration.");

					// Generate colormaps
					XSetWindowAttributes windowAttrs;
					windowAttrs.colormap = XCreateColormap(display, RootWindow(display, visualInfo->screen), visualInfo->visual, AllocNone);
					windowAttrs.background_pixmap = None;
					windowAttrs.border_pixel = 0;

					Window window = XCreateWindow(
											  display
											, RootWindow(display, visualInfo->screen)
											, 0, 0
											, _width, _height, 0, visualInfo->depth
											, InputOutput
											, visualInfo->visual
											, CWBorderPixel|CWColormap
											, &windowAttrs
											);
					BGFX_FATAL(window, Fatal::OPENGL_UnableToCreateContext, "Failed to create X11 window.");

					XMapRaised(display, window);
					XFlush(display);
					XFree(visualInfo);

					BX_TRACE("create context");

					typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
					glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
					BGFX_FATAL(glXCreateContextAttribsARB, Fatal::OPENGL_UnableToCreateContext, "Failed to get glXCreateContextAttribsARB.");

					const int contextArrib[] =
					{
						GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
						GLX_CONTEXT_MINOR_VERSION_ARB, 0,
						None,
					};

					m_context = glXCreateContextAttribsARB(display, bestconfig, 0, True, contextArrib);
					BGFX_FATAL(m_context, Fatal::OPENGL_UnableToCreateContext, "Failed to create GLX context.");

					glXMakeCurrent(display, window, m_context);

#	define GL_IMPORT(_optional, _proto, _func) \
				{ \
					_func = (_proto)glXGetProcAddress((const GLubyte*)#_func); \
					BGFX_FATAL(_optional || NULL != _func, Fatal::OPENGL_UnableToCreateContext, "Failed to create OpenGL context. glXGetProcAddress %s", #_func); \
				}
#	include "glimports.h"
#	undef GL_IMPORT
					glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT);
					glXSwapBuffers(display, window);

					m_display = display;
					m_window = window;
					XUnlockDisplay(display);
				}
				else
				{
					XResizeWindow(m_display, m_window, _width, _height);
				}
#elif BGFX_USE_EGL
				if (NULL == m_context)
				{
					EGLNativeDisplayType ndt = EGL_DEFAULT_DISPLAY;
					EGLNativeWindowType nwt = (EGLNativeWindowType)NULL;
#	if BX_PLATFORM_WINDOWS
					ndt = GetDC(g_bgfxHwnd);
					nwt = g_bgfxHwnd;
#	endif // BX_PLATFORM_
					m_display = eglGetDisplay(ndt);
					BGFX_FATAL(m_display != EGL_NO_DISPLAY, Fatal::OPENGL_UnableToCreateContext, "Failed to create display 0x%08x", m_display);

					EGLint major = 0;
					EGLint minor = 0;
					EGLBoolean success = eglInitialize(m_display, &major, &minor);
					BGFX_FATAL(success && major >= 1 && minor >= 3, Fatal::OPENGL_UnableToCreateContext, "Failed to initialize %d.%d", major, minor);

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
	
					EGLint contextAttrs[] =
					{
#	if BGFX_CONFIG_RENDERER_OPENGLES2
						EGL_CONTEXT_CLIENT_VERSION, 2,
#	elif BGFX_CONFIG_RENDERER_OPENGLES3
						EGL_CONTEXT_CLIENT_VERSION, 3,
#	endif // BGFX_CONFIG_RENDERER_

						EGL_NONE
					};

					EGLint numConfig = 0;
					EGLConfig config = 0;
					success = eglChooseConfig(m_display, attrs, &config, 1, &numConfig);
					BGFX_FATAL(success, Fatal::OPENGL_UnableToCreateContext, "eglChooseConfig");

					m_surface = eglCreateWindowSurface(m_display, config, nwt, NULL);
					BGFX_FATAL(m_surface != EGL_NO_SURFACE, Fatal::OPENGL_UnableToCreateContext, "Failed to create surface.");

					m_context = eglCreateContext(m_display, config, EGL_NO_CONTEXT, contextAttrs);
					BGFX_FATAL(m_context != EGL_NO_CONTEXT, Fatal::OPENGL_UnableToCreateContext, "Failed to create context.");

					success = eglMakeCurrent(m_display, m_surface, m_surface, m_context);
					BGFX_FATAL(success, Fatal::OPENGL_UnableToCreateContext, "Failed to set context.");

#	if BX_PLATFORM_EMSCRIPTEN
					emscripten_set_canvas_size(_width, _height);
#	else
#		define GL_IMPORT(_optional, _proto, _func) \
					{ \
						_func = (_proto)eglGetProcAddress(#_func); \
						BX_TRACE(#_func " 0x%08x", _func); \
						BGFX_FATAL(_optional || NULL != _func, Fatal::OPENGL_UnableToCreateContext, "Failed to create OpenGLES context. eglGetProcAddress(\"%s\")", #_func); \
					}
#		include "glimports.h"
#		undef GL_IMPORT
#	endif // !BX_PLATFORM_EMSCRIPTEN
				}
#endif // BX_PLATFORM_
			}

#if !BGFX_CONFIG_RENDERER_OPENGLES3
			if (NULL != glVertexAttribDivisor
			&&  NULL != glDrawArraysInstanced
			&&  NULL != glDrawElementsInstanced)
			{
				s_vertexAttribDivisor = glVertexAttribDivisor;
				s_drawArraysInstanced = glDrawArraysInstanced;
				s_drawElementsInstanced = glDrawElementsInstanced;
			}
			else
			{
				s_vertexAttribDivisor = stubVertexAttribDivisor;
				s_drawArraysInstanced = stubDrawArraysInstanced;
				s_drawElementsInstanced = stubDrawElementsInstanced;
			}
#endif // !BGFX_CONFIG_RENDERER_OPENGLES3

			m_flip = true;
		}

		void flip()
		{
			if (m_flip)
			{
#if BX_PLATFORM_NACL
				glSetCurrentContextPPAPI(m_context);
				m_graphicsInterface->SwapBuffers(m_context, naclSwapComplete);
#elif BGFX_USE_WGL
				wglMakeCurrent(m_hdc, m_context);
				SwapBuffers(m_hdc);
#elif BGFX_USE_EGL
				eglMakeCurrent(m_display, m_surface, m_surface, m_context);
				eglSwapBuffers(m_display, m_surface);
#elif BX_PLATFORM_LINUX
				glXSwapBuffers(m_display, m_window);
#endif // BX_PLATFORM_
			}

			if (NULL != m_postSwapBuffers)
			{
				m_postSwapBuffers(m_resolution.m_width, m_resolution.m_height);
			}
		}

		void saveScreenShot(Memory* _mem)
		{
			void* data = g_realloc(NULL, m_resolution.m_width*m_resolution.m_height*4);
			glReadPixels(0, 0, m_resolution.m_width, m_resolution.m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);

			uint8_t* rgba = (uint8_t*)data;
			for (uint32_t ii = 0, num = m_resolution.m_width*m_resolution.m_height; ii < num; ++ii)
			{
				uint8_t temp = rgba[0];
				rgba[0] = rgba[2];
				rgba[2] = temp;
				rgba += 4;
			}

			saveTga( (const char*)_mem->data, m_resolution.m_width, m_resolution.m_height, m_resolution.m_width*4, data, false, true);
			g_free(data);
		}

		void init()
		{
			setRenderContextSize(BGFX_DEFAULT_WIDTH, BGFX_DEFAULT_HEIGHT);
#if BGFX_CONFIG_RENDERER_OPENGL
			m_queries.create();
#endif // BGFX_CONFIG_RENDERER_OPENGL
		}

		void shutdown()
		{
#if BGFX_CONFIG_RENDERER_OPENGL
			m_queries.destroy();
#endif // BGFX_CONFIG_RENDERER_OPENGL

#if BGFX_USE_WGL
			if (NULL != m_hdc)
			{
				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(m_context);
				m_context = NULL;
			}

			FreeLibrary(m_opengl32dll);
#elif BGFX_USE_EGL
			eglMakeCurrent(EGL_NO_DISPLAY, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglDestroyContext(m_display, m_context);
			eglDestroySurface(m_display, m_surface);
			eglTerminate(m_display);
			m_context = NULL;
#endif // BGFX_USE_
		}

		IndexBuffer m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBuffer m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		Shader m_vertexShaders[BGFX_CONFIG_MAX_VERTEX_SHADERS];
		Shader m_fragmentShaders[BGFX_CONFIG_MAX_FRAGMENT_SHADERS];
		Program m_program[BGFX_CONFIG_MAX_PROGRAMS];
		Texture m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexDecl m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
		RenderTarget m_renderTargets[BGFX_CONFIG_MAX_RENDER_TARGETS];
		UniformRegistry m_uniformReg;
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
#if BGFX_CONFIG_RENDERER_OPENGL
		Queries m_queries;
#endif // BGFX_CONFIG_RENDERER_OPENGL

		TextVideoMem m_textVideoMem;

		Resolution m_resolution;
		bool m_dxtSupport;
		bool m_flip;

		PostSwapBuffersFn m_postSwapBuffers;
		uint64_t m_hash;

#if BX_PLATFORM_NACL
		PP_Resource m_context;
		PP_Instance m_instance;
		const PPB_Instance* m_instInterface;
		const PPB_Graphics3D* m_graphicsInterface;
		const PPB_OpenGLES2InstancedArrays* m_instancedArrays;
#elif BGFX_USE_WGL
		HMODULE m_opengl32dll;
		HGLRC m_context;
		HDC m_hdc;
#elif BGFX_USE_EGL
		EGLContext m_context;
		EGLDisplay m_display;
		EGLSurface m_surface;
#elif BX_PLATFORM_LINUX
		GLXContext m_context;
		Window m_window;
		Display* m_display;
#endif // BX_PLATFORM_NACL
	};

	RendererContext s_renderCtx;

#if BX_PLATFORM_NACL
	static void GL_APIENTRY naclVertexAttribDivisor(GLuint _index, GLuint _divisor)
	{
		s_renderCtx.m_instancedArrays->VertexAttribDivisorANGLE(s_renderCtx.m_context, _index, _divisor);
	}

	static void GL_APIENTRY naclDrawArraysInstanced(GLenum _mode, GLint _first, GLsizei _count, GLsizei _primcount)
	{
		s_renderCtx.m_instancedArrays->DrawArraysInstancedANGLE(s_renderCtx.m_context, _mode, _first, _count, _primcount);
	}

	static void GL_APIENTRY naclDrawElementsInstanced(GLenum _mode, GLsizei _count, GLenum _type, const GLvoid* _indices, GLsizei _primcount)
	{
		s_renderCtx.m_instancedArrays->DrawElementsInstancedANGLE(s_renderCtx.m_context, _mode, _count, _type, _indices, _primcount);
	}

	void naclSetIntefraces(PP_Instance _instance, const PPB_Instance* _instInterface, const PPB_Graphics3D* _graphicsInterface, PostSwapBuffersFn _postSwapBuffers)
	{
		s_renderCtx.m_instance = _instance;
		s_renderCtx.m_instInterface = _instInterface;
		s_renderCtx.m_graphicsInterface = _graphicsInterface;
		s_renderCtx.m_postSwapBuffers = _postSwapBuffers;
		s_renderCtx.m_instancedArrays = glGetInstancedArraysInterfacePPAPI();
		s_renderCtx.setRenderContextSize(BGFX_DEFAULT_WIDTH, BGFX_DEFAULT_HEIGHT);

		if (NULL != s_renderCtx.m_instancedArrays)
		{
			s_vertexAttribDivisor = naclVertexAttribDivisor;
			s_drawArraysInstanced = naclDrawArraysInstanced;
			s_drawElementsInstanced = naclDrawElementsInstanced;
		}
	}

	void naclSwapCompleteCb(void* /*_data*/, int32_t /*_result*/)
	{
		renderFrame();
	}
#elif BX_PLATFORM_LINUX
	bool linuxGetDisplay(Display** _display, Window* _window)
	{
		if (!s_renderCtx.m_display)
		{
			return false;
		}

		*_display = s_renderCtx.m_display;
		*_window = s_renderCtx.m_window;
		return true;
	}
#endif // BX_PLATFORM_

	struct Extension
	{
		enum Enum
		{
			EXT_texture_format_BGRA8888,
			EXT_texture_compression_s3tc,
			EXT_texture_compression_dxt1,
			CHROMIUM_texture_compression_dxt3,
			CHROMIUM_texture_compression_dxt5,
			OES_standard_derivatives,
			ARB_get_program_binary,
			OES_get_program_binary,
			EXT_framebuffer_blit,
			ARB_timer_query,
			EXT_timer_query,
			EXT_texture_sRGB,
			ARB_framebuffer_sRGB,
			EXT_framebuffer_sRGB,
			ARB_multisample,
			CHROMIUM_framebuffer_multisample,
			ANGLE_translated_shader_source,
			ARB_instanced_arrays,
			ANGLE_instanced_arrays,
			ARB_texture_float,
			OES_texture_float,
			OES_texture_float_linear,
			OES_texture_half_float,
			OES_texture_half_float_linear,
			ARB_half_float_vertex,
			OES_vertex_half_float,
			ARB_vertex_type_2_10_10_10_rev,
			OES_vertex_type_10_10_10_2,
			EXT_occlusion_query_boolean,
			ATI_meminfo,
			NVX_gpu_memory_info,

			Count
		};

		const char* m_name;
		bool m_supported;
		bool m_initialize;
	};

	static Extension s_extension[Extension::Count] =
	{
		// Nvidia BGRA on Linux bug:
		// https://groups.google.com/a/chromium.org/forum/?fromgroups#!topic/chromium-reviews/yFfbUdyeUCQ
		{ "GL_EXT_texture_format_BGRA8888",       false, !BX_PLATFORM_LINUX },
		{ "GL_EXT_texture_compression_s3tc",      false, true },
		{ "GL_EXT_texture_compression_dxt1",      false, true },
		{ "GL_CHROMIUM_texture_compression_dxt3", false, true },
		{ "GL_CHROMIUM_texture_compression_dxt5", false, true },
		{ "GL_OES_standard_derivatives",          false, true },
		{ "GL_ARB_get_program_binary",            false, true },
		{ "GL_OES_get_program_binary",            false, false },
		{ "GL_EXT_framebuffer_blit",              false, true },
		{ "GL_ARB_timer_query",                   false, true },
		{ "GL_EXT_timer_query",                   false, true },
		{ "GL_EXT_texture_sRGB",                  false, true },
		{ "GL_ARB_framebuffer_sRGB",              false, true },
		{ "GL_EXT_framebuffer_sRGB",              false, true },
		{ "GL_ARB_multisample",                   false, true },
		{ "GL_CHROMIUM_framebuffer_multisample",  false, true },
		{ "GL_ANGLE_translated_shader_source",    false, true },
		{ "GL_ARB_instanced_arrays",              false, true },
		{ "GL_ANGLE_instanced_arrays",            false, true },
		{ "GL_ARB_texture_float",                 false, true },
		{ "GL_OES_texture_float",                 false, true },
		{ "GL_OES_texture_float_linear",          false, true },
		{ "GL_OES_texture_half_float",            false, true },
		{ "GL_OES_texture_half_float_linear",     false, true },
		{ "GL_ARB_half_float_vertex",             false, true },
		{ "GL_OES_vertex_half_float",             false, true },
		{ "GL_ARB_vertex_type_2_10_10_10_rev",    false, true },
		{ "GL_OES_vertex_type_10_10_10_2",        false, true },
		{ "GL_EXT_occlusion_query_boolean",       false, true },
		{ "GL_ATI_meminfo",                       false, true },
		{ "GL_NVX_gpu_memory_info",               false, true },
	};

	static const GLenum s_primType[] =
	{
		GL_TRIANGLES,
		GL_LINES,
		GL_POINTS,
	};

	static const uint32_t s_primNumVerts[] =
	{
		3,
		2,
		1,
	};

	static const char* s_attribName[Attrib::Count] =
	{
		"a_position",
		"a_normal",
		"a_tangent",
		"a_color0",
		"a_color1",
		"a_indices",
		"a_weight",
		"a_texcoord0",
		"a_texcoord1",
		"a_texcoord2",
		"a_texcoord3",
		"a_texcoord4",
		"a_texcoord5",
		"a_texcoord6",
		"a_texcoord7",
	};

	static const char* s_instanceDataName[BGFX_CONFIG_MAX_INSTANCE_DATA_COUNT] =
	{
		"i_data0",
		"i_data1",
		"i_data2",
		"i_data3",
		"i_data4",
	};

	static const GLenum s_attribType[AttribType::Count] =
	{
		GL_UNSIGNED_BYTE,
		GL_UNSIGNED_SHORT,
#if BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
		GL_HALF_FLOAT,
#else
		GL_HALF_FLOAT_OES,
#endif // BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
		GL_FLOAT,
	};

	static const GLenum s_blendFactor[][2] =
	{
		{ 0,                      0                      }, // ignored
		{ GL_ZERO,                GL_ZERO                },
		{ GL_ONE,                 GL_ONE                 },
		{ GL_SRC_COLOR,           GL_SRC_COLOR           },
		{ GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR },
		{ GL_SRC_ALPHA,           GL_SRC_ALPHA           },
		{ GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA },
		{ GL_DST_ALPHA,           GL_DST_ALPHA           },
		{ GL_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA },
		{ GL_DST_COLOR,           GL_DST_COLOR           },
		{ GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_DST_COLOR },
		{ GL_SRC_ALPHA_SATURATE,  GL_ONE                 },
	};

	static const GLenum s_depthFunc[] =
	{
		0, // ignored
		GL_LESS,
		GL_LEQUAL,
		GL_EQUAL,
		GL_GEQUAL,
		GL_GREATER,
		GL_NOTEQUAL,
		GL_NEVER,
		GL_ALWAYS,
	};

	// Specifies the internal format of the texture.
	// Must be one of the following symbolic constants:
	// GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA.
	static const GLenum s_colorFormat[] =
	{
		0, // ignored
		GL_RGBA,
		GL_RGBA,
	};

	static const GLenum s_depthFormat[] =
	{
		0, // ignored
		0,
	};

	static const GLenum s_textureAddress[] =
	{
		GL_REPEAT,
		GL_MIRRORED_REPEAT,
		GL_CLAMP_TO_EDGE,
	};

	static const GLenum s_textureFilter[] =
	{
		GL_LINEAR,
		GL_NEAREST,
	};

	struct TextureFormatInfo
	{
		GLenum m_internalFmt;
		GLenum m_fmt;
		GLenum m_type;
		uint8_t m_bpp;
	};

	static const TextureFormatInfo s_textureFormat[TextureFormat::Count] =
	{
		{ GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_ZERO,      GL_ZERO,           4 },
		{ GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, GL_ZERO,      GL_ZERO,           4 },
		{ GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, GL_ZERO,      GL_ZERO,           4 },
		{ GL_ZERO,                          GL_ZERO,      GL_ZERO,           0 },
		{ GL_LUMINANCE,                     GL_LUMINANCE, GL_UNSIGNED_BYTE,  1 },
		{ GL_RGBA,                          GL_RGBA,      GL_UNSIGNED_BYTE,  4 },
		{ GL_RGBA,                          GL_RGBA,      GL_UNSIGNED_BYTE,  4 },
#if BGFX_CONFIG_RENDERER_OPENGL
		{ GL_RGBA16,                        GL_RGBA,      GL_UNSIGNED_SHORT, 8 },
#else
		{ GL_RGBA,                          GL_RGBA,      GL_UNSIGNED_BYTE,  8 },
#endif // BGFX_CONFIG_RENDERER_OPENGL
	};

	const char* glslTypeName(GLuint _type)
	{
#define GLSL_TYPE(_ty) case _ty: return #_ty

		switch (_type)
		{
			GLSL_TYPE(GL_FLOAT);
			GLSL_TYPE(GL_FLOAT_VEC2);
			GLSL_TYPE(GL_FLOAT_VEC3);
			GLSL_TYPE(GL_FLOAT_VEC4);
			GLSL_TYPE(GL_FLOAT_MAT2);
			GLSL_TYPE(GL_FLOAT_MAT3);
			GLSL_TYPE(GL_FLOAT_MAT4);
// 			GLSL_TYPE(GL_FLOAT_MAT2x3);
// 			GLSL_TYPE(GL_FLOAT_MAT2x4);
// 			GLSL_TYPE(GL_FLOAT_MAT3x2);
// 			GLSL_TYPE(GL_FLOAT_MAT3x4);
// 			GLSL_TYPE(GL_FLOAT_MAT4x2);
// 			GLSL_TYPE(GL_FLOAT_MAT4x3);
// 			GLSL_TYPE(GL_SAMPLER_1D);
 			GLSL_TYPE(GL_SAMPLER_2D);
//			GLSL_TYPE(GL_SAMPLER_3D);
			GLSL_TYPE(GL_SAMPLER_CUBE);
// 			GLSL_TYPE(GL_SAMPLER_1D_SHADOW);
// 			GLSL_TYPE(GL_SAMPLER_2D_SHADOW);
		}

#undef GLSL_TYPE

		return "UNKNOWN GLSL TYPE!";
	}

	const char* glEnumName(GLenum _enum)
	{
#define GLENUM(_ty) case _ty: return #_ty

		switch (_enum)
		{
			GLENUM(GL_TEXTURE);
			GLENUM(GL_RENDERBUFFER);
		}

#undef GLENUM

		return "UNKNOWN GLENUM!";
	}

	UniformType::Enum convertGlType(GLenum _type)
	{
		switch (_type)
		{
		case GL_FLOAT:
			return UniformType::Uniform1fv;

		case GL_FLOAT_VEC2:
			return UniformType::Uniform2fv;

		case GL_FLOAT_VEC3:
			return UniformType::Uniform3fv;

		case GL_FLOAT_VEC4:
			return UniformType::Uniform4fv;

		case GL_FLOAT_MAT2:
			break;

		case GL_FLOAT_MAT3:
			return UniformType::Uniform3x3fv;

		case GL_FLOAT_MAT4:
			return UniformType::Uniform4x4fv;

// 		case GL_FLOAT_MAT2x3:
// 		case GL_FLOAT_MAT2x4:
// 		case GL_FLOAT_MAT3x2:
// 		case GL_FLOAT_MAT3x4:
// 		case GL_FLOAT_MAT4x2:
// 		case GL_FLOAT_MAT4x3:
// 			break;

		case GL_SAMPLER_2D:
		case GL_SAMPLER_CUBE:
// 		case GL_SAMPLER_1D:
// 		case GL_SAMPLER_3D:
// 		case GL_SAMPLER_1D_SHADOW:
// 		case GL_SAMPLER_2D_SHADOW:
			return UniformType::Uniform1iv;
		};

		return UniformType::End;
	}

	void Program::create(const Shader& _vsh, const Shader& _fsh)
	{
		m_id = glCreateProgram();
		BX_TRACE("program create: %d: %d, %d", m_id, _vsh.m_id, _fsh.m_id);

		bool cached = false;

#if BGFX_CONFIG_RENDERER_OPENGL
		uint64_t id = (uint64_t(_vsh.m_hash)<<32) | _fsh.m_hash;
		id ^= s_renderCtx.m_hash;

		if (s_extension[Extension::ARB_get_program_binary].m_supported)
		{
			uint32_t length;
			g_cache(id, false, NULL, length);
			cached = length > 0;

			if (cached)
			{
				void* data = g_realloc(NULL, length);
				g_cache(id, false, data, length);

				StreamRead stream(data, length);

				GLenum format;
				stream.read(format);

				GL_CHECK(glProgramBinary(m_id, format, stream.getDataPtr(), stream.remaining() ) );

				g_free(data);
			}
			else
			{
				GL_CHECK(glProgramParameteri(m_id, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE) );
			}
		}
#endif // BGFX_CONFIG_RENDERER_OPENGL

		if (!cached)
		{
			GL_CHECK(glAttachShader(m_id, _vsh.m_id) );
			GL_CHECK(glAttachShader(m_id, _fsh.m_id) );
			GL_CHECK(glLinkProgram(m_id) );

			GLint linked = 0;
			GL_CHECK(glGetProgramiv(m_id, GL_LINK_STATUS, &linked) );

			if (0 == linked)
			{
				char log[1024];
				GL_CHECK(glGetProgramInfoLog(m_id, sizeof(log), NULL, log) );
				BX_TRACE("%d: %s", linked, log);

				GL_CHECK(glDeleteProgram(m_id) );
				return;
			}

#if BGFX_CONFIG_RENDERER_OPENGL
			if (s_extension[Extension::ARB_get_program_binary].m_supported)
			{
				GLint programLength;
				GLenum format;
				GL_CHECK(glGetProgramiv(m_id, GL_PROGRAM_BINARY_LENGTH, &programLength) );

				uint32_t length = programLength + 4;
				uint8_t* data = (uint8_t*)g_realloc(NULL, length);
				GL_CHECK(glGetProgramBinary(m_id, programLength, NULL, &format, &data[4]) );
				*(uint32_t*)data = format;

				g_cache(id, true, data, length);

				g_free(data);
			}
#endif // BGFX_CONFIG_RENDERER_OPENGL
		}

		init();
	}

	void Program::destroy()
	{
		GL_CHECK(glUseProgram(0) );
		GL_CHECK(glDeleteProgram(m_id) );
	}

	void Program::init()
	{
		GLint activeAttribs;
		GLint activeUniforms;

		GL_CHECK(glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTES, &activeAttribs) );
		GL_CHECK(glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &activeUniforms) );

		GLint max0, max1;
		GL_CHECK(glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max0) );
		GL_CHECK(glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max1) );

		GLint maxLength = uint32_max(max0, max1);
		char* name = (char*)g_realloc(NULL, maxLength + 1);

		BX_TRACE("Program %d", m_id);
		BX_TRACE("Attributes:");
		for (int32_t ii = 0; ii < activeAttribs; ++ii)
		{
			GLint size;
			GLenum type;

			GL_CHECK(glGetActiveAttrib(m_id, ii, maxLength + 1, NULL, &size, &type, name) );
			BX_TRACE("\t%s %s is at location %d"
				, glslTypeName(type)
				, name
				, glGetAttribLocation(m_id, name)
				);
		}

		m_numPredefined = 0;
		m_constantBuffer = ConstantBuffer::create(1024);
 		m_numSamplers = 0;

		BX_TRACE("Uniforms:");
		for (int32_t ii = 0; ii < activeUniforms; ++ii)
		{
			GLint num;
			GLenum gltype;

			GL_CHECK(glGetActiveUniform(m_id, ii, maxLength + 1, NULL, &num, &gltype, name) );
			GLint loc = glGetUniformLocation(m_id, name);

			int offset = 0;
			char* array = strchr(name, '[');
			if (NULL != array)
			{
				BX_TRACE("--- %s", name);
				*array = '\0';
				array++;
				char* end = strchr(array, ']');
				*end = '\0';
				offset = atoi(array);
			}

 			if (GL_SAMPLER_2D == gltype)
 			{
 				BX_TRACE("Sampler %d at %d.", m_numSamplers, loc);
 				m_sampler[m_numSamplers] = loc;
 				m_numSamplers++;
 			}

			const void* data = NULL;
			PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
			if (PredefinedUniform::Count != predefined)
			{
				m_predefined[m_numPredefined].m_loc = loc;
				m_predefined[m_numPredefined].m_type = predefined;
				m_predefined[m_numPredefined].m_count = num;
				m_numPredefined++;
			}
			else
			{
				const UniformInfo* info = s_renderCtx.m_uniformReg.find(name);
				if (NULL != info)
				{
					data = info->m_data;
					UniformType::Enum type = convertGlType(gltype);
					m_constantBuffer->writeUniformRef(type, loc, data, num);
					BX_TRACE("store %s %p", name, data);
				}
			}

			BX_TRACE("\tuniform %s %s%s is at location %d, size %d (%p), offset %d"
				, glslTypeName(gltype)
				, name
				, PredefinedUniform::Count != predefined ? "*" : ""
				, loc
				, num
				, data
				, offset
				);
			BX_UNUSED(offset);
		}

		m_constantBuffer->finish();

		g_free(name);

		memset(m_attributes, 0xff, sizeof(m_attributes) );
		uint32_t used = 0;
		for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
		{
			GLuint loc = glGetAttribLocation(m_id, s_attribName[ii]);
			if (GLuint(-1) != loc )
			{
				BX_TRACE("attr %s: %d", s_attribName[ii], loc);
				m_attributes[ii] = loc;
				m_used[used++] = ii;
			}
		}
		m_used[used] = Attrib::Count;

		used = 0;
		for (uint32_t ii = 0; ii < countof(s_instanceDataName); ++ii)
		{
			GLuint loc = glGetAttribLocation(m_id, s_instanceDataName[ii]);
			if (GLuint(-1) != loc )
			{
				BX_TRACE("instance data %s: %d", s_instanceDataName[ii], loc);
				m_instanceData[used++] = loc;
			}
		}
		m_instanceData[used] = 0xffff;
	}

	void Program::bindAttributes(const VertexDecl& _vertexDecl, uint32_t _baseVertex) const
	{
		uint32_t enabled = 0;
		for (uint32_t ii = 0; Attrib::Count != m_used[ii]; ++ii)
		{
			Attrib::Enum attr = Attrib::Enum(m_used[ii]);
			GLuint loc = m_attributes[attr];

			uint8_t num;
			AttribType::Enum type;
			bool normalized;
			_vertexDecl.decode(attr, num, type, normalized);

			if (0xffff != loc
			&&  0xff != _vertexDecl.m_attributes[attr])
			{
				GL_CHECK(glEnableVertexAttribArray(loc) );
				enabled |= 1<<attr;

				GL_CHECK(s_vertexAttribDivisor(loc, 0) );

				uint32_t baseVertex = _baseVertex*_vertexDecl.m_stride + _vertexDecl.m_offset[attr];
				GL_CHECK(glVertexAttribPointer(loc, num, s_attribType[type], normalized, _vertexDecl.m_stride, (void*)(uintptr_t)baseVertex) );
			}
			else
			{
//				GL_CHECK(glDisableVertexAttribArray(loc) );

				switch (num)
				{
				case 1:
					GL_CHECK(glVertexAttrib1f(loc, 0.0f) );
					break;

				case 2:
					GL_CHECK(glVertexAttrib2f(loc, 0.0f, 0.0f) );
					break;

				case 3:
					GL_CHECK(glVertexAttrib3f(loc, 0.0f, 0.0f, 0.0f) );
					break;

				case 4:
					GL_CHECK(glVertexAttrib4f(loc, 0.0f, 0.0f, 0.0f, 0.0f) );
					break;

				default:
					BX_CHECK(false, "You should not be here!");
					break;
				}
			}
		}
	}

	void Program::bindInstanceData(uint32_t _stride, uint32_t _baseVertex) const
	{
		uint32_t baseVertex = _baseVertex;
		for (uint32_t ii = 0; 0xffff != m_instanceData[ii]; ++ii)
		{
			GLuint loc = m_instanceData[ii];
			GL_CHECK(glEnableVertexAttribArray(loc) );
			GL_CHECK(glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, _stride, (void*)(uintptr_t)baseVertex) );
			GL_CHECK(s_vertexAttribDivisor(loc, 1) );
			baseVertex += 16;
		}
	}

	static void texImage(GLenum _target, GLint _level, GLint _internalFormat, GLsizei _width, GLsizei _height, GLsizei _depth, GLint _border, GLenum _format, GLenum _type, const GLvoid* _pixels)
	{
#if BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
		if (_target == GL_TEXTURE_3D)
		{
			GL_CHECK(glTexImage3D(_target
				, _level
				, _internalFormat
				, _width
				, _height
				, _depth
				, _border
				, _format
				, _type
				, _pixels
				) );
		}
		else
#endif // BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
		{
			BX_UNUSED(_depth);
			GL_CHECK(glTexImage2D(_target
				, _level
				, _internalFormat
				, _width
				, _height
				, _border
				, _format
				, _type
				, _pixels
				) );
		}
	}

	static void compressedTexImage(GLenum _target, GLint _level, GLenum _internalformat, GLsizei _width, GLsizei _height, GLsizei _depth, GLint _border, GLsizei _imageSize, const GLvoid* _data)
	{
#if BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
		if (_target == GL_TEXTURE_3D)
		{
			GL_CHECK(glCompressedTexImage3D(_target
				, _level
				, _internalformat
				, _width
				, _height
				, _depth
				, _border
				, _imageSize
				, _data
				) );
		}
		else
#endif // BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
		{
			BX_UNUSED(_depth);
			GL_CHECK(glCompressedTexImage2D(_target
				, _level
				, _internalformat
				, _width
				, _height
				, _border
				, _imageSize
				, _data
				) );
		}
	}

	void Texture::create(const Memory* _mem, uint32_t _flags)
	{
		Dds dds;
		uint8_t numMips = 0;

		if (parseDds(dds, _mem) )
		{
			numMips = dds.m_numMips;

			if (dds.m_cubeMap)
			{
				m_target = GL_TEXTURE_CUBE_MAP;
			}
#if BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
			else if (dds.m_depth > 1)
			{
				m_target = GL_TEXTURE_3D;
			}
#endif // BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
			else
			{
				m_target = GL_TEXTURE_2D;
			}

			GL_CHECK(glGenTextures(1, &m_id) );
			BX_CHECK(0 != m_id, "Failed to generate texture id.");
			GL_CHECK(glBindTexture(m_target, m_id) );

			const TextureFormatInfo& tfi = s_textureFormat[dds.m_type];
			GLenum internalFmt = tfi.m_internalFmt;
			m_fmt = tfi.m_fmt;

			GLenum target = m_target;
			if (dds.m_cubeMap)
			{
				target = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
			}

			if (!s_renderCtx.m_dxtSupport
			||  TextureFormat::Unknown < dds.m_type)
			{
				bool decompress = TextureFormat::Unknown > dds.m_type;

				if (GL_RGBA == internalFmt
				||  decompress)
				{
					internalFmt = s_extension[Extension::EXT_texture_format_BGRA8888].m_supported ? GL_BGRA_EXT : GL_RGBA;
					m_fmt = internalFmt;
				}

				m_type = tfi.m_type;
				if (decompress)
				{
					m_type = GL_UNSIGNED_BYTE;
				}

				uint8_t* bits = (uint8_t*)g_realloc(NULL, dds.m_width*dds.m_height*tfi.m_bpp);

				for (uint8_t side = 0, numSides = dds.m_cubeMap ? 6 : 1; side < numSides; ++side)
				{
					uint32_t width = dds.m_width;
					uint32_t height = dds.m_height;
					uint32_t depth = dds.m_depth;

					for (uint32_t lod = 0, num = dds.m_numMips; lod < num; ++lod)
					{
						width = uint32_max(1, width);
						height = uint32_max(1, height);
						depth = uint32_max(1, depth);

						Mip mip;
						if (getRawImageData(dds, side, lod, _mem, mip) )
						{
							mip.decode(bits);

							if (GL_RGBA == internalFmt)
							{
								uint32_t dstpitch = width*4;
								for (uint32_t yy = 0; yy < height; ++yy)
								{
									uint8_t* dst = &bits[yy*dstpitch];

									for (uint32_t xx = 0; xx < width; ++xx)
									{
										uint8_t tmp = dst[0];
										dst[0] = dst[2];
										dst[2] = tmp;
										dst += 4;
									}
								}
							}

							texImage(target+side
								, lod
								, internalFmt
								, width
								, height
								, depth
								, 0
								, m_fmt
								, m_type
								, bits
								);
						}

						width >>= 1;
						height >>= 1;
						depth >>= 1;
					}
				}

				g_free(bits);
			}
			else
			{
				for (uint8_t side = 0, numSides = dds.m_cubeMap ? 6 : 1; side < numSides; ++side)
				{
					uint32_t width = dds.m_width;
					uint32_t height = dds.m_height;
					uint32_t depth = dds.m_depth;

					for (uint32_t ii = 0, num = dds.m_numMips; ii < num; ++ii)
					{
						width = uint32_max(1, width);
						height = uint32_max(1, height);
						depth = uint32_max(1, depth);

						Mip mip;
						if (getRawImageData(dds, side, ii, _mem, mip) )
						{
							compressedTexImage(target+side
								, ii
								, internalFmt
								, width
								, height
								, depth
								, 0
								, mip.m_size
								, mip.m_data
								);
						}

						width >>= 1;
						height >>= 1;
						depth >>= 1;
					}
				}
			}
		}
		else
		{
			StreamRead stream(_mem->data, _mem->size);

			uint32_t magic;
			stream.read(magic);

			if (BGFX_MAGIC == magic)
			{
				TextureCreate tc;
				stream.read(tc);

				if (tc.m_cubeMap)
				{
					m_target = GL_TEXTURE_CUBE_MAP;
				}
#if BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
				else if (tc.m_depth > 1)
				{
					m_target = GL_TEXTURE_3D;
				}
#endif // BGFX_CONFIG_RENDERER_OPENGL|BGFX_CONFIG_RENDERER_OPENGLES3
				else
				{
					m_target = GL_TEXTURE_2D;
				}

				GL_CHECK(glGenTextures(1, &m_id) );
				BX_CHECK(0 != m_id, "Failed to generate texture id.");
				GL_CHECK(glBindTexture(m_target, m_id) );

				const TextureFormatInfo& tfi = s_textureFormat[tc.m_type];
				GLenum internalFmt = tfi.m_internalFmt;
				m_fmt = tfi.m_fmt;
				m_type = tfi.m_type;

				GLenum target = m_target;
				if (tc.m_cubeMap)
				{
					target = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
				}

				uint32_t bpp = s_textureFormat[tc.m_type].m_bpp;
				uint8_t* data = NULL != tc.m_mem ? tc.m_mem->data : NULL;

				for (uint8_t side = 0, numSides = tc.m_cubeMap ? 6 : 1; side < numSides; ++side)
				{
					uint32_t width = tc.m_width;
					uint32_t height = tc.m_height;
					uint32_t depth = tc.m_depth;

					for (uint32_t lod = 0, num = tc.m_numMips; lod < num; ++lod)
					{
						width = uint32_max(width, 1);
						height = uint32_max(height, 1);
						depth = uint32_max(1, depth);

						texImage(target+side
							, lod
							, internalFmt
							, width
							, height
							, depth
							, 0
							, m_fmt
							, m_type
							, data
							);

						if (NULL != data)
						{
							data += width*height*bpp;
						}

						width >>= 1;
						height >>= 1;
						depth >>= 1;
					}
				}

				if (NULL != tc.m_mem)
				{
					release(tc.m_mem);
				}
			}
			else
			{
				//
			}
		}

		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_WRAP_S, s_textureAddress[(_flags&BGFX_TEXTURE_U_MASK)>>BGFX_TEXTURE_U_SHIFT]) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_WRAP_T, s_textureAddress[(_flags&BGFX_TEXTURE_V_MASK)>>BGFX_TEXTURE_V_SHIFT]) );

#if BGFX_CONFIG_RENDERER_OPENGL
		if (m_target == GL_TEXTURE_3D)
		{
			GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_WRAP_R, s_textureAddress[(_flags&BGFX_TEXTURE_W_MASK)>>BGFX_TEXTURE_W_SHIFT]) );
		}
#endif // BGFX_CONFIG_RENDERER_OPENGL

		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, s_textureFilter[(_flags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT]) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, s_textureFilter[(_flags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT]) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, 1 < numMips ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR) );

		GL_CHECK(glBindTexture(m_target, 0) );
	}

	void Texture::createColor(uint32_t _width, uint32_t _height, GLenum _min, GLenum _mag)
	{
		GLenum internalFormat = /*_fp ? GL_RGBA16F_ARB :*/ GL_RGBA;
		GLenum type = /*_fp ? GL_HALF_FLOAT_ARB :*/ GL_UNSIGNED_BYTE;
		m_target = /*0 != _depth ? GL_TEXTURE_3D :*/ GL_TEXTURE_2D;

		GL_CHECK(glGenTextures(1, &m_id) );
		BX_CHECK(0 != m_id, "Failed to generate texture id.");
		GL_CHECK(glBindTexture(m_target, m_id) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, _min) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, _mag) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );

		GL_CHECK(glTexImage2D(m_target
			, 0
			, internalFormat
			, _width
			, _height
			, 0
			, GL_RGBA
			, type
			, NULL
			) );

		GL_CHECK(glBindTexture(m_target, 0) );
	}

	void Texture::createDepth(uint32_t _width, uint32_t _height)
	{
		m_target = GL_TEXTURE_2D;

		GL_CHECK(glGenTextures(1, &m_id) );
		BX_CHECK(0 != m_id, "Failed to generate texture id.");
		GL_CHECK(glBindTexture(m_target, m_id) );
//		glTexParameteri(m_target, GL_TEXTURE_COMPARE_MODE, GL_NONE);
//		glTexParameteri(m_target, GL_DEPTH_TEXTURE_MODE, GL_NONE);
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );

		// OpenGL ES 2.0 doesn't support GL_DEPTH_COMPONENT... this will fail.
		GL_CHECK(glTexImage2D(m_target
							, 0
							, GL_DEPTH_COMPONENT
							, _width
							, _height
							, 0
							, GL_DEPTH_COMPONENT
							, GL_FLOAT
							, NULL
							) );

		GL_CHECK(glBindTexture(m_target, 0) );
	}

	void Texture::destroy()
	{
		if (0 != m_id)
		{
			GL_CHECK(glBindTexture(m_target, 0) );
			GL_CHECK(glDeleteTextures(1, &m_id) );
			m_id = 0;
		}
	}

	void Texture::update(uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, const Memory* _mem)
	{
		GL_CHECK(glBindTexture(m_target, m_id) );
		GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1) );

		switch (m_target)
		{
		case GL_TEXTURE_2D:
			{
				GL_CHECK(glTexSubImage2D(m_target
					, _mip
					, _rect.m_x
					, _rect.m_y
					, _rect.m_width
					, _rect.m_height
					, m_fmt
					, m_type
					, _mem->data
					) );
			}
			break;

		case GL_TEXTURE_CUBE_MAP:
			{
				GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+_side
					, _mip
					, _rect.m_x
					, _rect.m_y
					, _rect.m_width
					, _rect.m_height
					, m_fmt
					, m_type
					, _mem->data
					) );
			}
			break;

#if BGFX_CONFIG_RENDERER_OPENGL
		case GL_TEXTURE_3D:
			{
				GL_CHECK(glTexSubImage3D(m_target
					, _mip
					, _rect.m_x
					, _rect.m_y
					, _z
					, _rect.m_width
					, _rect.m_height
					, _depth
					, m_fmt
					, m_type
					, _mem->data
					) );
			}
			break;
#endif // BGFX_CONFIG_RENDERER_OPENGL
		}
	}

	void RenderTarget::create(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags)
	{
		BX_TRACE("Create render target %dx%d 0x%02x", _width, _height, _flags);

		m_width = _width;
		m_height = _height;

//		m_msaa = s_msaa[(m_flags&BGFX_RENDER_TARGET_MSAA_MASK)>>BGFX_RENDER_TARGET_MSAA_SHIFT];
		uint32_t colorFormat = (_flags&BGFX_RENDER_TARGET_COLOR_MASK)>>BGFX_RENDER_TARGET_COLOR_SHIFT;
		uint32_t depthFormat = (_flags&BGFX_RENDER_TARGET_DEPTH_MASK)>>BGFX_RENDER_TARGET_DEPTH_SHIFT;
		GLenum minFilter = s_textureFilter[(_textureFlags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT];
		GLenum magFilter = s_textureFilter[(_textureFlags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT];

		if (0 < colorFormat)
		{
			m_color.createColor(_width, _height, minFilter, magFilter);
		}
		
#if 0 // GLES can't create texture with depth texture format...
		if (0 < depthFormat)
		{
			m_depth.createDepth(_width, _height);
		}
#endif // 

		GL_CHECK(glGenFramebuffers(1, &m_fbo) );
		BX_CHECK(0 != m_fbo, "Failed to generate framebuffer id.");
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo) );

		if (0 < colorFormat)
		{
			GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER
							, GL_COLOR_ATTACHMENT0
							, m_color.m_target
							, m_color.m_id
							, 0
							) );
		}

		if (0 < depthFormat)
		{
			if (0 < colorFormat)
			{
#if BGFX_CONFIG_RENDERER_OPENGL
				GLenum depthComponent = GL_DEPTH_COMPONENT32;
#else
				GLenum depthComponent = GL_DEPTH_COMPONENT16;
#endif // BGFX_CONFIG_RENDERER_OPENGL

				GL_CHECK(glGenRenderbuffers(1, &m_rbo) );
				BX_CHECK(0 != m_rbo, "Failed to generate renderbuffer id.");
				GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, m_rbo) );
				GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, depthComponent, _width, _height) );
				GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0) );

				GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER
					, GL_DEPTH_ATTACHMENT
					, GL_RENDERBUFFER
					, m_rbo
					) );
			}
			else
			{
				GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER
					, GL_DEPTH_ATTACHMENT
					, m_depth.m_target
					, m_depth.m_id
					, 0
					) );
			}
		}

		BX_CHECK(GL_FRAMEBUFFER_COMPLETE ==  glCheckFramebufferStatus(GL_FRAMEBUFFER)
				, "glCheckFramebufferStatus failed 0x%08x"
				, glCheckFramebufferStatus(GL_FRAMEBUFFER)
				);

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0) );
	}

	void RenderTarget::destroy()
	{
		GL_CHECK(glDeleteFramebuffers(1, &m_fbo) );

		if (0 != m_rbo)
		{
			GL_CHECK(glDeleteRenderbuffers(1, &m_rbo) );
		}

		m_color.destroy();
		m_depth.destroy();
	}

	void ConstantBuffer::commit()
	{
		reset();

		do
		{
			uint32_t opcode = read();

			if (UniformType::End == opcode)
			{
				break;
			}

			UniformType::Enum type;
			uint16_t loc;
			uint16_t num;
			uint16_t copy;
			decodeOpcode(opcode, type, loc, num, copy);

			const char* data;
			if (copy)
			{
				data = read(g_uniformTypeSize[type]*num);
			}
			else
			{
				memcpy(&data, read(sizeof(void*) ), sizeof(void*) );
			}

#define CASE_IMPLEMENT_UNIFORM(_uniform, _glsuffix, _dxsuffix, _type) \
		case UniformType::_uniform: \
			{ \
				_type* value = (_type*)data; \
				GL_CHECK(glUniform##_glsuffix(loc, num, value) ); \
			} \
			break;
			
#define CASE_IMPLEMENT_UNIFORM_T(_uniform, _glsuffix, _dxsuffix, _type) \
		case UniformType::_uniform: \
			{ \
				_type* value = (_type*)data; \
				GL_CHECK(glUniform##_glsuffix(loc, num, GL_FALSE, value) ); \
			} \
			break;

			switch (type)
			{
// 			case ConstantType::Uniform1iv:
// 				{
// 					int* value = (int*)data;
// 					BX_TRACE("Uniform1iv sampler %d, loc %d (num %d, copy %d)", *value, loc, num, copy);
// 					GL_CHECK(glUniform1iv(loc, num, value) );
// 				}
// 				break;

			CASE_IMPLEMENT_UNIFORM(Uniform1i, 1iv, I, int);
			CASE_IMPLEMENT_UNIFORM(Uniform1f, 1fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform1iv, 1iv, I, int);
			CASE_IMPLEMENT_UNIFORM(Uniform1fv, 1fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform2fv, 2fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform3fv, 3fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform4fv, 4fv, F, float);
			CASE_IMPLEMENT_UNIFORM_T(Uniform3x3fv, Matrix3fv, F, float);
			CASE_IMPLEMENT_UNIFORM_T(Uniform4x4fv, Matrix4fv, F, float);

			case UniformType::End:
				break;

			default:
				BX_TRACE("%4d: INVALID 0x%08x, t %d, l %d, n %d, c %d", m_pos, opcode, type, loc, num, copy);
				break;
			}

#undef CASE_IMPLEMENT_UNIFORM
#undef CASE_IMPLEMENT_UNIFORM_T

		} while (true);
	}

	void TextVideoMemBlitter::setup()
	{
		uint32_t width = s_renderCtx.m_resolution.m_width;
		uint32_t height = s_renderCtx.m_resolution.m_height;

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0) );
		GL_CHECK(glViewport(0, 0, width, height) );

		GL_CHECK(glDisable(GL_DEPTH_TEST) );
		GL_CHECK(glDepthFunc(GL_ALWAYS) );
		GL_CHECK(glDisable(GL_CULL_FACE) );
		GL_CHECK(glDisable(GL_BLEND) );
		GL_CHECK(glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE) );
#if BGFX_CONFIG_RENDERER_OPENGL
		GL_CHECK(glDisable(GL_ALPHA_TEST) );
#endif // BGFX_CONFIG_RENDERER_OPENGL

		Program& program = s_renderCtx.m_program[m_program.idx];
		GL_CHECK(glUseProgram(program.m_id) );
		GL_CHECK(glUniform1i(program.m_sampler[0], 0) );

		float proj[16];
		mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

		GL_CHECK(glUniformMatrix4fv(program.m_predefined[0].m_loc
			, 1
			, GL_FALSE
			, proj
			) );

		GL_CHECK(glActiveTexture(GL_TEXTURE0) );
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, s_renderCtx.m_textures[m_texture.idx].m_id) );
	}

	void TextVideoMemBlitter::render(uint32_t _numIndices)
	{
		uint32_t numVertices = _numIndices*4/6;
		s_renderCtx.m_indexBuffers[m_ib->handle.idx].update(0, _numIndices*2, m_ib->data);
		s_renderCtx.m_vertexBuffers[m_vb->handle.idx].update(0, numVertices*m_decl.m_stride, m_vb->data);

		VertexBuffer& vb = s_renderCtx.m_vertexBuffers[m_vb->handle.idx];
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vb.m_id) );

		IndexBuffer& ib = s_renderCtx.m_indexBuffers[m_ib->handle.idx];
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.m_id) );

		Program& program = s_renderCtx.m_program[m_program.idx];
		program.bindAttributes(m_decl, 0);

		GL_CHECK(glDrawElements(GL_TRIANGLES
			, _numIndices
			, GL_UNSIGNED_SHORT
			, (void*)0
			) );
	}

	void Context::flip()
	{
		s_renderCtx.flip();
	}

	GLint glGet(GLenum _pname)
	{
		GLint result;
		GL_CHECK(glGetIntegerv(_pname, &result) );
		return result;
	}

	void Context::rendererInit()
	{
		s_renderCtx.init();

#if BGFX_CONFIG_DEBUG
		GLint numCmpFormats;
		GL_CHECK(glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &numCmpFormats) );

		BX_TRACE("GL_NUM_COMPRESSED_TEXTURE_FORMATS %d", numCmpFormats);

		if (0 < numCmpFormats)
		{
			GLint* formats = (GLint*)alloca(sizeof(GLint)*numCmpFormats);
			glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, formats);

			for (GLint ii = 0; ii < numCmpFormats; ++ii)
			{
				BX_TRACE("\t%3d: %8x", ii, formats[ii]);
			}
		}

#	define GL_GET(_pname, _min) BX_TRACE(#_pname " %d (min: %d)", glGet(_pname), _min)

		GL_GET(GL_MAX_FRAGMENT_UNIFORM_VECTORS, 16);
		GL_GET(GL_MAX_VERTEX_UNIFORM_VECTORS, 128);
		GL_GET(GL_MAX_VARYING_VECTORS, 8);
		GL_GET(GL_MAX_VERTEX_ATTRIBS, 8);
		GL_GET(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, 8);
		GL_GET(GL_MAX_CUBE_MAP_TEXTURE_SIZE, 16);
		GL_GET(GL_MAX_TEXTURE_IMAGE_UNITS, 8);
		GL_GET(GL_MAX_TEXTURE_SIZE, 64);
		GL_GET(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, 0);
		GL_GET(GL_MAX_RENDERBUFFER_SIZE, 1);
#endif // BGFX_CONFIG_DEBUG

		const char* version = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
		BX_TRACE("GLSL version: %s", version);

		const char* extensions = (const char*)glGetString(GL_EXTENSIONS);
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

				bool supported = false;
				for (uint32_t ii = 0; ii < Extension::Count; ++ii)
				{
					Extension& extension = s_extension[ii];
					if (!extension.m_supported
					&&  extension.m_initialize)
					{
						if (0 == strcmp(name, extension.m_name) )
						{
							extension.m_supported = true;
							supported = true;
							break;
						}
					}
				}

				BX_TRACE("GL_EXTENSION%s: %s", supported ? " (supported)" : "", name);
				BX_UNUSED(supported);

 				pos += len+1;
 			}

			BX_TRACE("Supported extensions:");
			for (uint32_t ii = 0; ii < Extension::Count; ++ii)
			{
				if (s_extension[ii].m_supported)
				{
					BX_TRACE("\t%2d: %s", ii, s_extension[ii].m_name);
				}
			}

			s_renderCtx.m_dxtSupport = true
				&& s_extension[Extension::EXT_texture_compression_dxt1].m_supported
				&& s_extension[Extension::CHROMIUM_texture_compression_dxt3].m_supported
				&& s_extension[Extension::CHROMIUM_texture_compression_dxt5].m_supported
				;

			s_renderCtx.m_dxtSupport |=
				s_extension[Extension::EXT_texture_compression_s3tc].m_supported
				;
		}
	}

	void Context::rendererShutdown()
	{
		s_renderCtx.shutdown();
	}

	void Context::rendererCreateIndexBuffer(IndexBufferHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].create(_mem->size, _mem->data);
	}

	void Context::rendererDestroyIndexBuffer(IndexBufferHandle _handle)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl)
	{
		VertexDecl& decl = s_renderCtx.m_vertexDecls[_handle.idx];
		memcpy(&decl, &_decl, sizeof(VertexDecl) );
		dump(decl);
	}

	void Context::rendererDestroyVertexDecl(VertexDeclHandle /*_handle*/)
	{
	}

	void Context::rendererCreateVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _declHandle);
	}

	void Context::rendererDestroyVertexBuffer(VertexBufferHandle _handle)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].create(_size, NULL);
	}

	void Context::rendererUpdateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].update(_offset, uint32_min(_size, _mem->size), _mem->data);
	}

	void Context::rendererDestroyDynamicIndexBuffer(IndexBufferHandle _handle)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size)
	{
		VertexDeclHandle decl = BGFX_INVALID_HANDLE;
		s_renderCtx.m_vertexBuffers[_handle.idx].create(_size, NULL, decl);
	}

	void Context::rendererUpdateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].update(_offset, uint32_min(_size, _mem->size), _mem->data);
	}

	void Context::rendererDestroyDynamicVertexBuffer(VertexBufferHandle _handle)
	{
		s_renderCtx.m_vertexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateVertexShader(VertexShaderHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_vertexShaders[_handle.idx].create(GL_VERTEX_SHADER, _mem->data);
	}

	void Context::rendererDestroyVertexShader(VertexShaderHandle _handle)
	{
		s_renderCtx.m_vertexShaders[_handle.idx].destroy();
	}

	void Context::rendererCreateFragmentShader(FragmentShaderHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_fragmentShaders[_handle.idx].create(GL_FRAGMENT_SHADER, _mem->data);
	}

	void Context::rendererDestroyFragmentShader(FragmentShaderHandle _handle)
	{
		s_renderCtx.m_fragmentShaders[_handle.idx].destroy();
	}

	void Context::rendererCreateProgram(ProgramHandle _handle, VertexShaderHandle _vsh, FragmentShaderHandle _fsh)
	{
		s_renderCtx.m_program[_handle.idx].create(s_renderCtx.m_vertexShaders[_vsh.idx], s_renderCtx.m_fragmentShaders[_fsh.idx]);
	}

	void Context::rendererDestroyProgram(FragmentShaderHandle _handle)
	{
		s_renderCtx.m_program[_handle.idx].destroy();
	}

	void Context::rendererCreateTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags)
	{
		s_renderCtx.m_textures[_handle.idx].create(_mem, _flags);
	}

	void Context::rendererUpdateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, const Memory* _mem)
	{
		s_renderCtx.m_textures[_handle.idx].update(_side, _mip, _rect, _z, _depth, _mem);
	}

	void Context::rendererDestroyTexture(TextureHandle _handle)
	{
		s_renderCtx.m_textures[_handle.idx].destroy();
	}

	void Context::rendererCreateRenderTarget(RenderTargetHandle _handle, uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags)
	{
		s_renderCtx.m_renderTargets[_handle.idx].create(_width, _height, _flags, _textureFlags);
	}

	void Context::rendererDestroyRenderTarget(RenderTargetHandle _handle)
	{
		s_renderCtx.m_renderTargets[_handle.idx].destroy();
	}

	void Context::rendererCreateUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name)
	{
		uint32_t size = g_uniformTypeSize[_type]*_num;
		void* data = g_realloc(NULL, size);
		memset(data, 0, size);
		s_renderCtx.m_uniforms[_handle.idx] = data;
		s_renderCtx.m_uniformReg.add(_name, s_renderCtx.m_uniforms[_handle.idx]);
	}

	void Context::rendererDestroyUniform(UniformHandle _handle)
	{
		g_free(s_renderCtx.m_uniforms[_handle.idx]);
	}

	void Context::rendererSaveScreenShot(Memory* _mem)
	{
		s_renderCtx.saveScreenShot(_mem);
	}

	void Context::rendererUpdateUniform(uint16_t _loc, const void* _data, uint32_t _size)
	{
		memcpy(s_renderCtx.m_uniforms[_loc], _data, _size);
	}

	void Context::rendererSubmit()
	{
		s_renderCtx.updateResolution(m_render->m_resolution);

		int64_t elapsed = -bx::getHPCounter();
#if BGFX_CONFIG_RENDERER_OPENGL
		if (m_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			s_renderCtx.m_queries.begin(0, GL_TIME_ELAPSED);
		}
#endif // BGFX_CONFIG_RENDERER_OPENGL

		if (0 < m_render->m_iboffset)
		{
			TransientIndexBuffer* ib = m_render->m_transientIb;
			s_renderCtx.m_indexBuffers[ib->handle.idx].update(0, m_render->m_iboffset, ib->data);
		}

		if (0 < m_render->m_vboffset)
		{
			TransientVertexBuffer* vb = m_render->m_transientVb;
			s_renderCtx.m_vertexBuffers[vb->handle.idx].update(0, m_render->m_vboffset, vb->data);
		}

		m_render->sort();

		RenderState currentState;
		currentState.reset();
		currentState.m_flags = BGFX_STATE_NONE;

		Matrix4 viewProj[BGFX_CONFIG_MAX_VIEWS];
		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			mtxMul(viewProj[ii].val, m_render->m_view[ii].val, m_render->m_proj[ii].val);
		}

		uint16_t programIdx = invalidHandle;
		SortKey key;
		uint8_t view = 0xff;
		RenderTargetHandle rt = BGFX_INVALID_HANDLE;
		int32_t height = m_render->m_resolution.m_height;
		float alphaRef = 0.0f;
		GLenum primType = m_render->m_debug&BGFX_DEBUG_WIREFRAME ? GL_LINES : GL_TRIANGLES;
		uint32_t primNumVerts = 3;
		uint32_t baseVertex = 0;

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0) );

		uint32_t statsNumPrimsSubmitted = 0;
		uint32_t statsNumIndices = 0;
		uint32_t statsNumInstances = 0;
		uint32_t statsNumPrimsRendered = 0;

		if (0 == (m_render->m_debug&BGFX_DEBUG_IFH) )
		{
			for (uint32_t item = 0, numItems = m_render->m_num; item < numItems; ++item)
			{
				key.decode(m_render->m_sortKeys[item]);
				const RenderState& state = m_render->m_renderState[m_render->m_sortValues[item] ];

				const uint64_t newFlags = state.m_flags;
				uint64_t changedFlags = currentState.m_flags ^ state.m_flags;
				currentState.m_flags = newFlags;

				if (key.m_view != view)
				{
					currentState.clear();
					changedFlags = BGFX_STATE_MASK;
					currentState.m_flags = newFlags;

					GREMEDY_SETMARKER("view");

					view = key.m_view;
					programIdx = invalidHandle;

					if (m_render->m_rt[view].idx != rt.idx)
					{
						rt = m_render->m_rt[view];

						if (rt.idx == invalidHandle)
						{
							GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0) );
							height = m_render->m_resolution.m_height;
						}
						else
						{
							RenderTarget& renderTarget = s_renderCtx.m_renderTargets[rt.idx];
							GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, renderTarget.m_fbo) );
							height = renderTarget.m_height;
						}
					}

					Rect& rect = m_render->m_rect[view];

					GL_CHECK(glViewport(rect.m_x, height-rect.m_height-rect.m_y, rect.m_width, rect.m_height) );

					Clear& clear = m_render->m_clear[view];

					if (BGFX_CLEAR_NONE != clear.m_flags)
					{
						GLuint flags = 0;
						if (BGFX_CLEAR_COLOR_BIT & clear.m_flags)
						{
							flags |= GL_COLOR_BUFFER_BIT;
							uint32_t rgba = clear.m_rgba;
							float rr = (rgba>>24)/255.0f;
							float gg = ( (rgba>>16)&0xff)/255.0f;
							float bb = ( (rgba>>8)&0xff)/255.0f;
							float aa = (rgba&0xff)/255.0f;
							GL_CHECK(glClearColor(rr, gg, bb, aa) );
							GL_CHECK(glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE) );
						}

						if (BGFX_CLEAR_DEPTH_BIT & clear.m_flags)
						{
							flags |= GL_DEPTH_BUFFER_BIT;
							GL_CHECK(glClearDepthf(clear.m_depth) );
							GL_CHECK(glDepthMask(GL_TRUE) );
						}

						if (BGFX_CLEAR_STENCIL_BIT & clear.m_flags)
						{
							flags |= GL_STENCIL_BUFFER_BIT;
							GL_CHECK(glClearStencil(clear.m_stencil) );
						}

						if (0 != flags)
						{
							GL_CHECK(glEnable(GL_SCISSOR_TEST) );
							GL_CHECK(glScissor(rect.m_x, height-rect.m_height-rect.m_y, rect.m_width, rect.m_height) );
							GL_CHECK(glClear(flags) );
							GL_CHECK(glDisable(GL_SCISSOR_TEST) );
						}
					}

					GL_CHECK(glEnable(GL_DEPTH_TEST) );
					GL_CHECK(glDepthFunc(GL_LESS) );
					GL_CHECK(glEnable(GL_CULL_FACE) );
					GL_CHECK(glDisable(GL_BLEND) );
				}

				if ( (BGFX_STATE_CULL_MASK|BGFX_STATE_DEPTH_WRITE|BGFX_STATE_DEPTH_TEST_MASK
				     |BGFX_STATE_ALPHA_MASK|BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE
				     |BGFX_STATE_BLEND_MASK|BGFX_STATE_ALPHA_REF_MASK|BGFX_STATE_PT_MASK
				     |BGFX_STATE_POINT_SIZE_MASK) & changedFlags)
				{
					if (BGFX_STATE_CULL_MASK & changedFlags)
					{
						if (BGFX_STATE_CULL_CW & newFlags)
						{
							GL_CHECK(glEnable(GL_CULL_FACE) );
							GL_CHECK(glCullFace(GL_BACK) );
						}
						else if (BGFX_STATE_CULL_CCW & newFlags)
						{
							GL_CHECK(glEnable(GL_CULL_FACE) );
							GL_CHECK(glCullFace(GL_FRONT) );
						}
						else
						{
							GL_CHECK(glDisable(GL_CULL_FACE) );
						}
					}

					if (BGFX_STATE_DEPTH_WRITE & changedFlags)
					{
						GL_CHECK(glDepthMask(!!(BGFX_STATE_DEPTH_WRITE & newFlags) ) );
					}

					if (BGFX_STATE_DEPTH_TEST_MASK & changedFlags)
					{
						uint32_t func = (newFlags&BGFX_STATE_DEPTH_TEST_MASK)>>BGFX_STATE_DEPTH_TEST_SHIFT;

						if (0 != func)
						{
							GL_CHECK(glEnable(GL_DEPTH_TEST) );
							GL_CHECK(glDepthFunc(s_depthFunc[func]) );
						}
						else
						{
							GL_CHECK(glDisable(GL_DEPTH_TEST) );
						}
					}

					if ( (BGFX_STATE_ALPHA_TEST|BGFX_STATE_ALPHA_REF_MASK) & changedFlags)
					{
						uint32_t ref = (newFlags&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT;
						alphaRef = ref/255.0f;

#if BGFX_CONFIG_RENDERER_OPENGL
						if (BGFX_STATE_ALPHA_TEST & newFlags)
						{
							GL_CHECK(glEnable(GL_ALPHA_TEST) );
						}
						else
						{
							GL_CHECK(glDisable(GL_ALPHA_TEST) );
						}
#endif // BGFX_CONFIG_RENDERER_OPENGL
					}

#if BGFX_CONFIG_RENDERER_OPENGL
					if ( (BGFX_STATE_PT_POINTS|BGFX_STATE_POINT_SIZE_MASK) & changedFlags)
					{
						float pointSize = (float)(uint32_max(1, (newFlags&BGFX_STATE_POINT_SIZE_MASK)>>BGFX_STATE_POINT_SIZE_SHIFT) );
						GL_CHECK(glPointSize(pointSize) );
					}
#endif // BGFX_CONFIG_RENDERER_OPENGL

					if ( (BGFX_STATE_ALPHA_WRITE|BGFX_STATE_RGB_WRITE) & changedFlags)
					{
						GLboolean alpha = !!(newFlags&BGFX_STATE_ALPHA_WRITE);
						GLboolean rgb = !!(newFlags&BGFX_STATE_RGB_WRITE);
						GL_CHECK(glColorMask(rgb, rgb, rgb, alpha) );
					}

					if (BGFX_STATE_BLEND_MASK & changedFlags)
					{
						if (BGFX_STATE_BLEND_MASK & newFlags)
						{
							uint32_t blend = (newFlags&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT;
							uint32_t src = blend&0xf;
							uint32_t dst = (blend>>4)&0xf;
							GL_CHECK(glEnable(GL_BLEND) );
							GL_CHECK(glBlendFunc(s_blendFactor[src][0], s_blendFactor[dst][1]) );
						}
						else
						{
							GL_CHECK(glDisable(GL_BLEND) );
						}
					}

					uint8_t primIndex = uint8_t( (newFlags&BGFX_STATE_PT_MASK)>>BGFX_STATE_PT_SHIFT);
					primType = m_render->m_debug&BGFX_DEBUG_WIREFRAME ? GL_LINES : s_primType[primIndex];
					primNumVerts = s_primNumVerts[primIndex];
				}

				bool programChanged = false;
				bool constantsChanged = state.m_constBegin < state.m_constEnd;
				bool bindAttribs = false;
				rendererUpdateUniforms(m_render->m_constantBuffer, state.m_constBegin, state.m_constEnd);

				if (key.m_program != programIdx)
				{
					programIdx = key.m_program;
					GLuint id = invalidHandle == programIdx ? 0 : s_renderCtx.m_program[programIdx].m_id;
					GL_CHECK(glUseProgram(id) );
					programChanged = 
						constantsChanged = 
						bindAttribs = true;
				}

				if (invalidHandle != programIdx)
				{
					Program& program = s_renderCtx.m_program[programIdx];

					if (constantsChanged)
					{
						program.m_constantBuffer->commit();
					}

					for (uint32_t ii = 0, num = program.m_numPredefined; ii < num; ++ii)
					{
						PredefinedUniform& predefined = program.m_predefined[ii];
						switch (predefined.m_type)
						{
						case PredefinedUniform::ViewRect:
							{
								float rect[4];
								rect[0] = m_render->m_rect[view].m_x;
								rect[1] = m_render->m_rect[view].m_y;
								rect[2] = m_render->m_rect[view].m_width;
								rect[3] = m_render->m_rect[view].m_height;

								GL_CHECK(glUniform4fv(predefined.m_loc
									, 1
									, &rect[0]
								) );
							}
							break;

						case PredefinedUniform::ViewTexel:
							{
								float rect[4];
								rect[0] = 1.0f/float(m_render->m_rect[view].m_width);
								rect[1] = 1.0f/float(m_render->m_rect[view].m_height);

								GL_CHECK(glUniform4fv(predefined.m_loc
									, 1
									, &rect[0]
								) );
							}
							break;

						case PredefinedUniform::View:
							{
								GL_CHECK(glUniformMatrix4fv(predefined.m_loc
									, 1
									, GL_FALSE
									, m_render->m_view[view].val
									) );
							}
							break;

						case PredefinedUniform::ViewProj:
							{
								GL_CHECK(glUniformMatrix4fv(predefined.m_loc
									, 1
									, GL_FALSE
									, viewProj[view].val
									) );
							}
							break;

						case PredefinedUniform::Model:
							{
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								GL_CHECK(glUniformMatrix4fv(predefined.m_loc
									, uint32_min(predefined.m_count, state.m_num)
									, GL_FALSE
									, model.val
									) );
							}
							break;

						case PredefinedUniform::ModelView:
							{
								Matrix4 modelView;
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								mtxMul(modelView.val, model.val, m_render->m_view[view].val);

								GL_CHECK(glUniformMatrix4fv(predefined.m_loc
									, 1
									, GL_FALSE
									, modelView.val
									) );
							}
							break;

						case PredefinedUniform::ModelViewProj:
							{
								Matrix4 modelViewProj;
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
								mtxMul(modelViewProj.val, model.val, viewProj[view].val);

								GL_CHECK(glUniformMatrix4fv(predefined.m_loc
									, 1
									, GL_FALSE
									, modelViewProj.val
									) );
							}
							break;

						case PredefinedUniform::ModelViewProjX:
							{
								const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];

								static const BX_ALIGN_STRUCT_16(float) s_bias[16] =
								{
									0.5f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.5f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.5f, 0.0f,
									0.5f, 0.5f, 0.5f, 1.0f,
								};

								uint8_t other = m_render->m_other[view];
								Matrix4 viewProjBias;
								mtxMul(viewProjBias.val, viewProj[other].val, s_bias);

								Matrix4 modelViewProj;
								mtxMul(modelViewProj.val, model.val, viewProjBias.val);

								GL_CHECK(glUniformMatrix4fv(predefined.m_loc
									, 1
									, GL_FALSE
									, modelViewProj.val
									) );
							}
							break;

						case PredefinedUniform::ViewProjX:
							{
								static const BX_ALIGN_STRUCT_16(float) s_bias[16] =
								{
									0.5f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.5f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.5f, 0.0f,
									0.5f, 0.5f, 0.5f, 1.0f,
								};

								uint8_t other = m_render->m_other[view];
								Matrix4 viewProjBias;
								mtxMul(viewProjBias.val, viewProj[other].val, s_bias);

								GL_CHECK(glUniformMatrix4fv(predefined.m_loc
									, 1
									, GL_FALSE
									, viewProjBias.val
									) );
							}
							break;

						case PredefinedUniform::AlphaRef:
							{
								GL_CHECK(glUniform1f(predefined.m_loc, alphaRef) );
							}
							break;

						case PredefinedUniform::Count:
							break;
						}
					}

//						if (BGFX_STATE_TEX_MASK & changedFlags)
					{
						uint64_t flag = BGFX_STATE_TEX0;
						for (uint32_t stage = 0; stage < BGFX_STATE_TEX_COUNT; ++stage)
						{
							const Sampler& sampler = state.m_sampler[stage];
							Sampler& current = currentState.m_sampler[stage];
							if (current.m_idx != sampler.m_idx
							||  current.m_flags != sampler.m_flags
							||  programChanged)
							{
								if (invalidHandle != sampler.m_idx)
								{
									GL_CHECK(glActiveTexture(GL_TEXTURE0+stage) );
									switch (sampler.m_flags&BGFX_SAMPLER_TYPE_MASK)
									{
									case BGFX_SAMPLER_TEXTURE:
										{
											const Texture& texture = s_renderCtx.m_textures[sampler.m_idx];
											GL_CHECK(glBindTexture(texture.m_target, texture.m_id) );
										}
										break;

									case BGFX_SAMPLER_RENDERTARGET_COLOR:
										{
											const RenderTarget& rt = s_renderCtx.m_renderTargets[sampler.m_idx];
											GL_CHECK(glBindTexture(rt.m_color.m_target, rt.m_color.m_id) );
										}
										break;

									case BGFX_SAMPLER_RENDERTARGET_DEPTH:
										{
											const RenderTarget& rt = s_renderCtx.m_renderTargets[sampler.m_idx];
											GL_CHECK(glBindTexture(rt.m_depth.m_target, rt.m_depth.m_id) );
										}
										break;
									}
								}
							}

							current = sampler;
							flag <<= 1;
						}
					}

					if (currentState.m_vertexBuffer.idx != state.m_vertexBuffer.idx || programChanged)
					{
						currentState.m_vertexBuffer = state.m_vertexBuffer;

						uint16_t handle = state.m_vertexBuffer.idx;
						if (invalidHandle != handle)
						{
							VertexBuffer& vb = s_renderCtx.m_vertexBuffers[handle];
							GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vb.m_id) );
							bindAttribs = true;
						}
						else
						{
							GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0) );
						}
					}

					if (currentState.m_indexBuffer.idx != state.m_indexBuffer.idx)
					{
						currentState.m_indexBuffer = state.m_indexBuffer;

						uint16_t handle = state.m_indexBuffer.idx;
						if (invalidHandle != handle)
						{
							IndexBuffer& ib = s_renderCtx.m_indexBuffers[handle];
							GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.m_id) );
						}
						else
						{
							GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
						}
					}

					if (invalidHandle != currentState.m_vertexBuffer.idx)
					{
						if (baseVertex != state.m_startVertex
						||  bindAttribs)
						{
							baseVertex = state.m_startVertex;
							const VertexBuffer& vb = s_renderCtx.m_vertexBuffers[state.m_vertexBuffer.idx];
							uint16_t decl = vb.m_decl.idx == invalidHandle ? state.m_vertexDecl.idx : vb.m_decl.idx;
							const Program& program = s_renderCtx.m_program[programIdx];
							program.bindAttributes(s_renderCtx.m_vertexDecls[decl], state.m_startVertex);
							
							if (invalidHandle != state.m_instanceDataBuffer.idx)
							{
								GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, s_renderCtx.m_vertexBuffers[state.m_instanceDataBuffer.idx].m_id) );
								program.bindInstanceData(state.m_instanceDataStride, state.m_instanceDataOffset);
							}
						}

						uint32_t numVertices = state.m_numVertices;
						if (UINT32_C(0xffffffff) == numVertices)
						{
							const VertexBuffer& vb = s_renderCtx.m_vertexBuffers[currentState.m_vertexBuffer.idx];
							uint16_t decl = vb.m_decl.idx == invalidHandle ? state.m_vertexDecl.idx : vb.m_decl.idx;
							const VertexDecl& vertexDecl = s_renderCtx.m_vertexDecls[decl];
							numVertices = vb.m_size/vertexDecl.m_stride;
						}

						uint32_t numIndices = 0;
						uint32_t numPrimsSubmitted = 0;
						uint32_t numInstances = 0;
						uint32_t numPrimsRendered = 0;

						if (invalidHandle != state.m_indexBuffer.idx)
						{
							if (BGFX_DRAW_WHOLE_INDEX_BUFFER == state.m_startIndex)
							{
								numIndices = s_renderCtx.m_indexBuffers[state.m_indexBuffer.idx].m_size/2;
								numPrimsSubmitted = numIndices/primNumVerts;
								numInstances = state.m_numInstances;
								numPrimsRendered = numPrimsSubmitted*state.m_numInstances;

								GL_CHECK(s_drawElementsInstanced(primType
									, numIndices
									, GL_UNSIGNED_SHORT
									, (void*)0
									, state.m_numInstances
									) );
							}
							else if (primNumVerts <= state.m_numIndices)
							{
								numIndices = state.m_numIndices;
								numPrimsSubmitted = numIndices/primNumVerts;
								numInstances = state.m_numInstances;
								numPrimsRendered = numPrimsSubmitted*state.m_numInstances;

								GL_CHECK(s_drawElementsInstanced(primType
									, numIndices
									, GL_UNSIGNED_SHORT
									, (void*)(uintptr_t)(state.m_startIndex*2)
									, state.m_numInstances
									) );
							}
						}
						else
						{
							numPrimsSubmitted = numVertices/primNumVerts;
							numInstances = state.m_numInstances;
							numPrimsRendered = numPrimsSubmitted*state.m_numInstances;

							GL_CHECK(s_drawArraysInstanced(primType
								, 0
								, numVertices
								, state.m_numInstances
								) );
						}

						statsNumPrimsSubmitted += numPrimsSubmitted;
						statsNumIndices += numIndices;
						statsNumInstances += numInstances;
						statsNumPrimsRendered += numPrimsRendered;
					}
				}
			}
		}

		int64_t now = bx::getHPCounter();
		elapsed += now;

		static int64_t last = now;
		int64_t frameTime = now - last;
		last = now;

		static int64_t min = frameTime;
		static int64_t max = frameTime;
		min = min > frameTime ? frameTime : min;
		max = max < frameTime ? frameTime : max;

		if (m_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			double elapsedGpuMs = 0.0;
#if BGFX_CONFIG_RENDERER_OPENGL
			s_renderCtx.m_queries.end(GL_TIME_ELAPSED);
			uint64_t elapsedGl = s_renderCtx.m_queries.getResult(0);
			elapsedGpuMs = double(elapsedGl)/1e6;
#endif // BGFX_CONFIG_RENDERER_OPENGL

			TextVideoMem& tvm = s_renderCtx.m_textVideoMem;

			static int64_t next = now;

			if (now >= next)
			{
				next = now + bx::getHPFrequency();
				double freq = double(bx::getHPFrequency() );
				double toMs = 1000.0/freq;
				double elapsedCpuMs = double(elapsed)*toMs;

				tvm.clear();
				uint16_t pos = 10;
				tvm.printf(0, 0, 0x8f, " " BGFX_RENDERER_NAME " ");
				tvm.printf(10, pos++, 0x8e, "  Frame CPU: %7.3f, % 7.3f \x1f, % 7.3f \x1e [ms] / % 6.2f FPS"
					, double(frameTime)*toMs
					, double(min)*toMs
					, double(max)*toMs
					, freq/frameTime
					);
				tvm.printf(10, pos++, 0x8e, " Draw calls: %4d / CPU %3.4f [ms] %c GPU %3.4f [ms]"
					, m_render->m_num
					, elapsedCpuMs
					, elapsedCpuMs > elapsedGpuMs ? '>' : '<'
					, elapsedGpuMs
					);
				tvm.printf(10, pos++, 0x8e, "      Prims: %7d (#inst: %5d), submitted: %7d"
					, statsNumPrimsRendered
					, statsNumInstances
					, statsNumPrimsSubmitted
					);
				tvm.printf(10, pos++, 0x8e, "    Indices: %7d", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, "   DVB size: %7d", m_render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "   DIB size: %7d", m_render->m_iboffset);

#if BGFX_CONFIG_RENDERER_OPENGL
				if (s_extension[Extension::ATI_meminfo].m_supported)
				{
					GLint vboFree[4];
					GL_CHECK(glGetIntegerv(GL_VBO_FREE_MEMORY_ATI, vboFree) );

					GLint texFree[4];
					GL_CHECK(glGetIntegerv(GL_TEXTURE_FREE_MEMORY_ATI, texFree) );

					GLint rbfFree[4];
					GL_CHECK(glGetIntegerv(GL_RENDERBUFFER_FREE_MEMORY_ATI, rbfFree) );

					pos++;
					tvm.printf(10, pos++, 0x8c, " -------------|    free|  free b|     aux|  aux fb");
					tvm.printf(10, pos++, 0x8e, "           VBO: %7d, %7d, %7d, %7d", vboFree[0], vboFree[1], vboFree[2], vboFree[3]);
					tvm.printf(10, pos++, 0x8e, "       Texture: %7d, %7d, %7d, %7d", texFree[0], texFree[1], texFree[2], texFree[3]);
					tvm.printf(10, pos++, 0x8e, " Render Buffer: %7d, %7d, %7d, %7d", rbfFree[0], rbfFree[1], rbfFree[2], rbfFree[3]);
				}
				else if (s_extension[Extension::NVX_gpu_memory_info].m_supported)
				{
					GLint dedicated;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &dedicated) );

					GLint totalAvail;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalAvail) );

					GLint currAvail;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &currAvail) );

					GLint evictedCount;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &evictedCount) );

					GLint evictedMemory;
					GL_CHECK(glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &evictedMemory) );

					pos++;
					tvm.printf(10, pos++, 0x8c, "----------|");
					tvm.printf(10, pos++, 0x8e, " Dedicated: %7d", dedicated);
					tvm.printf(10, pos++, 0x8e, " Available: %7d (%7d)", currAvail, totalAvail);
					tvm.printf(10, pos++, 0x8e, "  Eviction: %7d / %7d", evictedCount, evictedMemory);
				}
#endif // BGFX_CONFIG_RENDERER_OPENGL

				uint8_t attr[2] = { 0x89, 0x8a };
				uint8_t attrIndex = m_render->m_waitSubmit < m_render->m_waitRender;

				pos++;
				tvm.printf(10, pos++, attr[attrIndex&1], "Submit wait: %3.4f [ms]", double(m_render->m_waitSubmit)*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], "Render wait: %3.4f [ms]", double(m_render->m_waitRender)*toMs);

				min = frameTime;
				max = frameTime;
			}

			m_textVideoMemBlitter.blit(tvm);
		}
		else if (m_render->m_debug & BGFX_DEBUG_TEXT)
		{
			m_textVideoMemBlitter.blit(m_render->m_textVideoMem);
		}

		GREMEDY_FRAMETERMINATOR();
	}
}

#endif // (BGFX_CONFIG_RENDERER_OPENGLES2|BGFX_CONFIG_RENDERER_OPENGLES3|BGFX_CONFIG_RENDERER_OPENGL)
