/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if (BGFX_CONFIG_RENDERER_OPENGLES|BGFX_CONFIG_RENDERER_OPENGL)
#	include "renderer_gl.h"
#	include <bx/timer.h>
#	include <bx/uint32_t.h>

#if BGFX_CONFIG_RENDERER_OPENGL
#	define glClearDepthf(_depth) glClearDepth(_depth)
#endif // BGFX_CONFIG_RENDERER_OPENGL

namespace bgfx
{
#if BGFX_CONFIG_RENDERER_OPENGL
#	define GL_IMPORT(_optional, _proto, _func) _proto _func
#	include "glimports.h"
#	undef GL_IMPORT
#endif // BGFX_CONFIG_RENDERER_OPENGL

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
#elif BX_PLATFORM_WINDOWS
			, m_context(NULL)
			, m_hdc(NULL)
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
#if BX_PLATFORM_NACL || BX_PLATFORM_LINUX
				setRenderContextSize(_resolution.m_width, _resolution.m_height);
#endif // BX_PLATFORM_
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
				}
				else
				{
					m_graphicsInterface->ResizeBuffers(m_context, _width, _height);
				}

#elif BX_PLATFORM_WINDOWS
				if (NULL == m_hdc)
				{
					m_hdc = GetDC(g_bgfxHwnd);
					BGFX_FATAL(NULL != m_hdc, bgfx::Fatal::OPENGL_UnableToCreateContext, "GetDC failed!");

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
					BGFX_FATAL(0 != pixelFormat, bgfx::Fatal::OPENGL_UnableToCreateContext, "ChoosePixelFormat failed!");

					DescribePixelFormat(m_hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

					int result;
					result = SetPixelFormat(m_hdc, pixelFormat, &pfd);
					BGFX_FATAL(0 != result, bgfx::Fatal::OPENGL_UnableToCreateContext, "SetPixelFormat failed!");

					m_context = wglCreateContext(m_hdc);
					BGFX_FATAL(NULL != m_context, bgfx::Fatal::OPENGL_UnableToCreateContext, "wglCreateContext failed!");
					
					result = wglMakeCurrent(m_hdc, m_context);
					BGFX_FATAL(0 != result, bgfx::Fatal::OPENGL_UnableToCreateContext, "wglMakeCurrent failed!");

#	define GL_IMPORT(_optional, _proto, _func) \
				{ \
					_func = (_proto)wglGetProcAddress(#_func); \
					BGFX_FATAL(_optional || NULL != _func, bgfx::Fatal::OPENGL_UnableToCreateContext, "Failed to create OpenGL context. wglGetProcAddress(\"%s\")", #_func); \
				}
#	include "glimports.h"
#	undef GL_IMPORT
				}
#elif BX_PLATFORM_LINUX

				if (0 == m_display)
				{
					Display* display = XOpenDisplay(0);
					XLockDisplay(display);
					BGFX_FATAL(display, bgfx::Fatal::OPENGL_UnableToCreateContext, "Failed to open X display (0).");

					int glxMajor, glxMinor;
					if (!glXQueryVersion(display, &glxMajor, &glxMinor))
					{
						BGFX_FATAL(false, bgfx::Fatal::OPENGL_UnableToCreateContext, "Failed to query GLX version");
					}
					BGFX_FATAL((glxMajor == 1 && glxMinor >= 3) || glxMajor > 1, bgfx::Fatal::OPENGL_UnableToCreateContext, "GLX version is not >=1.3 (%d.%d).", glxMajor, glxMinor);

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
					GLXFBConfig	bestconfig;

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
							for (int attridx = 0; attridx < countof(glxAttribs) && glxAttribs[attridx] != None; attridx += 2)
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
					BGFX_FATAL(visualInfo, bgfx::Fatal::OPENGL_UnableToCreateContext, "Failed to find a suitable X11 display configuration.");

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
					BGFX_FATAL(window, bgfx::Fatal::OPENGL_UnableToCreateContext, "Failed to create X11 window.");

					XMapRaised(display, window);
					XFlush(display);
					XFree(visualInfo);

					BX_TRACE("create context");

					typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
					glXCreateContextAttribsARBProc glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
					BGFX_FATAL(glXCreateContextAttribsARB, bgfx::Fatal::OPENGL_UnableToCreateContext, "Failed to get glXCreateContextAttribsARB.");

					const int contextArrib[] =
					{
						GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
						GLX_CONTEXT_MINOR_VERSION_ARB, 0,
						None,
					};

					m_context = glXCreateContextAttribsARB(display, bestconfig, 0, True, contextArrib);
					BGFX_FATAL(m_context, bgfx::Fatal::OPENGL_UnableToCreateContext, "Failed to create GLX context.");

					glXMakeCurrent(display, window, m_context);

#	define GL_IMPORT(_optional, _proto, _func) \
				{ \
					_func = (_proto)glXGetProcAddress((const GLubyte*)#_func); \
					BGFX_FATAL(_optional || NULL != _func, bgfx::Fatal::OPENGL_UnableToCreateContext, "Failed to create OpenGL context. glXGetProcAddress %s", #_func); \
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
#endif // BX_PLATFORM_
			}

			m_flip = true;
		}

		void flip()
		{
			if (m_flip)
			{
#if BX_PLATFORM_NACL
				glSetCurrentContextPPAPI(m_context);
				m_graphicsInterface->SwapBuffers(m_context, naclSwapComplete);
#elif BX_PLATFORM_WINDOWS
				wglMakeCurrent(m_hdc, m_context);
				SwapBuffers(m_hdc);
#elif BX_PLATFORM_LINUX
				glXSwapBuffers(m_display, m_window);
#endif // BX_PLATFORM_
			}

			if (NULL != m_postSwapBuffers)
			{
				m_postSwapBuffers(m_resolution.m_width, m_resolution.m_height);
			}
		}

		void init()
		{
			setRenderContextSize(BGFX_DEFAULT_WIDTH, BGFX_DEFAULT_HEIGHT);
		}

		void saveScreenShot(Memory* _mem)
		{
#if BGFX_CONFIG_RENDERER_OPENGL
			void* data = g_realloc(NULL, m_resolution.m_width*m_resolution.m_height*4);
			glReadPixels(0, 0, m_resolution.m_width, m_resolution.m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			saveTga( (const char*)_mem->data, m_resolution.m_width, m_resolution.m_height, m_resolution.m_width*4, data);
			g_free(data);
#endif // BGFX_CONFIG_RENDERER_OPENGL
		}

		IndexBuffer m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBuffer m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		Shader m_vertexShaders[BGFX_CONFIG_MAX_VERTEX_SHADERS];
		Shader m_fragmentShaders[BGFX_CONFIG_MAX_FRAGMENT_SHADERS];
		Material m_materials[BGFX_CONFIG_MAX_MATERIALS];
		Texture m_textures[BGFX_CONFIG_MAX_TEXTURES];
		VertexDecl m_vertexDecls[BGFX_CONFIG_MAX_VERTEX_DECLS];
		RenderTarget m_renderTargets[BGFX_CONFIG_MAX_RENDER_TARGETS];
		UniformRegistry m_uniformReg;
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

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
#elif BX_PLATFORM_WINDOWS
		HGLRC m_context;
		HDC m_hdc;
#elif BX_PLATFORM_LINUX
		GLXContext m_context;
		Window m_window;
		Display* m_display;
#endif // BX_PLATFORM_NACL
	};

	RendererContext s_renderCtx;

#if BX_PLATFORM_NACL
	void naclSetIntefraces(PP_Instance _instance, const PPB_Instance* _instInterface, const PPB_Graphics3D* _graphicsInterface, PostSwapBuffersFn _postSwapBuffers)
	{
		s_renderCtx.m_instance = _instance;
		s_renderCtx.m_instInterface = _instInterface;
		s_renderCtx.m_graphicsInterface = _graphicsInterface;
		s_renderCtx.m_postSwapBuffers = _postSwapBuffers;
		s_renderCtx.setRenderContextSize(BGFX_DEFAULT_WIDTH, BGFX_DEFAULT_HEIGHT);
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
		"a_color",
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

	static const GLenum s_attribType[AttribType::Count] =
	{
		GL_UNSIGNED_BYTE,
		GL_UNSIGNED_SHORT,
		GL_FLOAT,
	};

	static const GLenum s_blendFactor[] =
	{
		0, // ignored
		GL_ZERO,
		GL_ONE,
		GL_SRC_COLOR,
		GL_ONE_MINUS_SRC_COLOR,
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA,
		GL_DST_ALPHA,
		GL_ONE_MINUS_DST_ALPHA,
		GL_DST_COLOR,
		GL_ONE_MINUS_DST_COLOR,
		GL_SRC_ALPHA_SATURATE,
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

	ConstantType::Enum convertGlType(GLenum _type)
	{
		switch (_type)
		{
		case GL_FLOAT:
			return ConstantType::Uniform1fv;

		case GL_FLOAT_VEC2:
			return ConstantType::Uniform2fv;

		case GL_FLOAT_VEC3:
			return ConstantType::Uniform3fv;

		case GL_FLOAT_VEC4:
			return ConstantType::Uniform4fv;

		case GL_FLOAT_MAT2:
			break;

		case GL_FLOAT_MAT3:
			return ConstantType::Uniform3x3fv;

		case GL_FLOAT_MAT4:
			return ConstantType::Uniform4x4fv;

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
			return ConstantType::Uniform1iv;
		};

		return ConstantType::End;
	}

	void Material::create(const Shader& _vsh, const Shader& _fsh)
	{
		m_id = glCreateProgram();
		BX_TRACE("material create: %d: %d, %d", m_id, _vsh.m_id, _fsh.m_id);

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

	void Material::destroy()
	{
		GL_CHECK(glUseProgram(0) );
		GL_CHECK(glDeleteProgram(m_id) );
	}

	void Material::init()
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
					ConstantType::Enum type = convertGlType(gltype);
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
		}

		m_constantBuffer->finish();

		g_free(name);

		memset(m_attributes, 0xff, sizeof(m_attributes) );
		uint32_t used = 0;
		for (uint32_t ii = 0; ii < Attrib::Count; ++ii)
		{
			GLuint loc = glGetAttribLocation(m_id, s_attribName[ii]);
			if ( GLuint(-1) != loc )
			{
				BX_TRACE("attr %s: %d", s_attribName[ii], loc);
				m_attributes[ii] = loc;
				m_used[used++] = ii;
			}
		}
		m_used[used] = Attrib::Count;
	}

	void Material::bindAttributes(const VertexDecl& _vertexDecl, uint32_t _baseVertex)
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

				uint32_t baseVertex = _baseVertex*_vertexDecl.m_stride + _vertexDecl.m_offset[attr];
				GL_CHECK(glVertexAttribPointer(loc, num, s_attribType[type], normalized, _vertexDecl.m_stride, (void*)(uintptr_t)baseVertex) );
			}
			else
			{
				GL_CHECK(glDisableVertexAttribArray(loc) );

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
// 
// 		uint32_t changed = enabled^m_enabled;
// 		m_enabled = enabled;
// 
// 		if (0 != changed)
// 		{
// 			uint32_t test = 1;
// 			for (uint32_t attr = 0; attr != Attrib::Count; ++attr)
// 			{
// 				if ( (changed & test)
// 				&&   !(enabled & test) )
// 				{
// 					GLuint loc = m_attributes[attr];
// 					GL_CHECK(glDisableVertexAttribArray(loc) );
// 				}
// 
// 				test <<= 1;
// 			}
// 		}
	}

	void Texture::create(const Memory* _mem, uint32_t _flags)
	{
		m_target = GL_TEXTURE_2D;

		GL_CHECK(glGenTextures(1, &m_id) );
		BX_CHECK(0 != m_id, "Failed to generate texture id.");
		GL_CHECK(glBindTexture(m_target, m_id) );

		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_WRAP_S, s_textureAddress[(_flags&BGFX_TEXTURE_U_MASK)>>BGFX_TEXTURE_U_SHIFT]) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_WRAP_T, s_textureAddress[(_flags&BGFX_TEXTURE_V_MASK)>>BGFX_TEXTURE_V_SHIFT]) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, s_textureFilter[(_flags&BGFX_TEXTURE_MIN_MASK)>>BGFX_TEXTURE_MIN_SHIFT]) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, s_textureFilter[(_flags&BGFX_TEXTURE_MAG_MASK)>>BGFX_TEXTURE_MAG_SHIFT]) );

		Dds dds;

		if (parseDds(dds, _mem) )
		{
			GLenum typefmt[4] =
			{
				GL_RGBA,
				GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
 				GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
 				GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
			};

			GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, 1 < dds.m_numMips ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR) );

			GLenum fmt = typefmt[dds.m_type];

			uint32_t width = dds.m_width;
			uint32_t height = dds.m_height;

			if (!s_renderCtx.m_dxtSupport
			||  0 == dds.m_type)
			{
				fmt = s_extension[Extension::EXT_texture_format_BGRA8888].m_supported ? GL_BGRA_EXT : GL_RGBA;

				uint8_t bpp = 4;
				if (dds.m_type == 0
				&&  dds.m_bpp == 1)
				{
					fmt = GL_LUMINANCE;
					bpp = 1;
				}

				uint8_t* bits = (uint8_t*)g_realloc(NULL, dds.m_width*dds.m_height*bpp);

				for (uint32_t lod = 0, num = dds.m_numMips; lod < num; ++lod)
				{
					width = uint32_max(1, width);
					height = uint32_max(1, height);

					Mip mip;
					if (getRawImageData(dds, lod, _mem, mip) )
					{
						mip.decode(bits);

						if (GL_RGBA == fmt)
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

						GL_CHECK(glTexImage2D(m_target
							, lod
							, fmt
							, width
							, height
							, 0
							, fmt
							, GL_UNSIGNED_BYTE
							, bits
						) );
					}

					width >>= 1;
					height >>= 1;
				}

				g_free(bits);
			}
			else
			{
				for (uint32_t ii = 0, num = dds.m_numMips; ii < num; ++ii)
				{
					width = uint32_max(1, width);
					height = uint32_max(1, height);

					Mip mip;
					if (getRawImageData(dds, ii, _mem, mip) )
					{
						GL_CHECK(glCompressedTexImage2D(m_target
							, ii
							, fmt
							, width
							, height
							, 0
							, mip.m_size
							, mip.m_data
							) );
					}

					width >>= 1;
					height >>= 1;
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
				uint16_t width;
				stream.read(width);

				uint16_t height;
				stream.read(height);

				uint8_t bpp;
				stream.read(bpp);

				uint8_t numMips;
				stream.read(numMips);

				stream.align(16);

				GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, 1 < dds.m_numMips ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR) );

				for (uint8_t mip = 0; mip < numMips; ++mip)
				{
					width = uint32_max(width, 1);
					height = uint32_max(height, 1);

					const uint8_t* data = stream.getDataPtr();
					stream.skip(width*height*bpp);

					GL_CHECK(glTexImage2D(m_target
						, mip
						, 1 == bpp ? GL_LUMINANCE : GL_RGBA
						, width
						, height
						, 0
						, 1 == bpp ? GL_LUMINANCE : GL_RGBA
						, GL_UNSIGNED_BYTE
						, data
						) );

					width >>= 1;
					height >>= 1;
				}
			}
			else
			{
				//
			}
		}

		GL_CHECK(glBindTexture(m_target, 0) );
	}

	void Texture::createColor(uint32_t _width, uint32_t _height)
	{
		GLenum internalFormat = /*_fp ? GL_RGBA16F_ARB :*/ GL_RGBA;
		GLenum type = /*_fp ? GL_HALF_FLOAT_ARB :*/ GL_UNSIGNED_BYTE;
		m_target = /*0 != _depth ? GL_TEXTURE_3D :*/ GL_TEXTURE_2D;

		GL_CHECK(glGenTextures(1, &m_id) );
		BX_CHECK(0 != m_id, "Failed to generate texture id.");
		GL_CHECK(glBindTexture(m_target, m_id) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
		GL_CHECK(glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
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

	void RenderTarget::create(uint16_t _width, uint16_t _height, uint32_t _flags)
	{
		BX_TRACE("Create render target %dx%d 0x%02x", _width, _height, _flags);

		m_width = _width;
		m_height = _height;

		uint32_t colorFormat = (_flags&BGFX_RENDER_TARGET_COLOR_MASK)>>BGFX_RENDER_TARGET_COLOR_SHIFT;
		uint32_t depthFormat = (_flags&BGFX_RENDER_TARGET_DEPTH_MASK)>>BGFX_RENDER_TARGET_DEPTH_SHIFT;

		if (0 < colorFormat)
		{
			m_color.createColor(_width, _height);
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
							, GL_TEXTURE_2D
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
					, GL_TEXTURE_2D
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

	void ConstantBuffer::commit(bool _force)
	{
		reset();

		do
		{
			uint32_t opcode = read();

			if (ConstantType::End == opcode)
			{
				break;
			}

			ConstantType::Enum type;
			uint16_t loc;
			uint16_t num;
			uint16_t copy;
			decodeOpcode(opcode, type, loc, num, copy);

			const char* data;
			if (copy)
			{
				data = read(g_constantTypeSize[type]*num);
			}
			else
			{
				memcpy(&data, read(sizeof(void*) ), sizeof(void*) );
			}

#define CASE_IMPLEMENT_UNIFORM(_uniform, _glsuffix, _dxsuffix, _type) \
		case ConstantType::_uniform: \
			{ \
				_type* value = (_type*)data; \
				GL_CHECK(glUniform##_glsuffix(loc, num, value) ); \
			} \
			break;
			
#define CASE_IMPLEMENT_UNIFORM_T(_uniform, _glsuffix, _dxsuffix, _type) \
		case ConstantType::_uniform: \
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
// 

			CASE_IMPLEMENT_UNIFORM(Uniform1i, 1iv, I, int);
			CASE_IMPLEMENT_UNIFORM(Uniform1f, 1fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform1iv, 1iv, I, int);
			CASE_IMPLEMENT_UNIFORM(Uniform1fv, 1fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform2fv, 2fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform3fv, 3fv, F, float);
			CASE_IMPLEMENT_UNIFORM(Uniform4fv, 4fv, F, float);
			CASE_IMPLEMENT_UNIFORM_T(Uniform3x3fv, Matrix3fv, F, float);
			CASE_IMPLEMENT_UNIFORM_T(Uniform4x4fv, Matrix4fv, F, float);

			case ConstantType::End:
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

		Material& material = s_renderCtx.m_materials[m_material.idx];
		GL_CHECK(glUseProgram(material.m_id) );
		GL_CHECK(glUniform1i(material.m_sampler[0], 0) );

		float proj[16];
		matrix_ortho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

		GL_CHECK(glUniformMatrix4fv(material.m_predefined[0].m_loc
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
		s_renderCtx.m_indexBuffers[m_ib->handle.idx].update(_numIndices*2, m_ib->data);
		s_renderCtx.m_vertexBuffers[m_vb->handle.idx].update(numVertices*m_decl.m_stride, m_vb->data);

		VertexBuffer& vb = s_renderCtx.m_vertexBuffers[m_vb->handle.idx];
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vb.m_id) );

		IndexBuffer& ib = s_renderCtx.m_indexBuffers[m_ib->handle.idx];
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.m_id) );

		Material& material = s_renderCtx.m_materials[m_material.idx];
		material.bindAttributes(m_decl, 0);

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

		GLint* formats = (GLint*)alloca(sizeof(GLint)*numCmpFormats);
		glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, formats);

		for (GLint ii = 0; ii < numCmpFormats; ++ii)
		{
			BX_TRACE("\t%3d: %8x", ii, formats[ii]);
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

		const char* extensions = (const char*)glGetString(GL_EXTENSIONS);

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

 			pos += len+1;
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

	void Context::rendererShutdown()
	{
	}

	void Context::rendererCreateIndexBuffer(IndexBufferHandle _handle, Memory* _mem)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].create(_mem->size, _mem->data);
	}

	void Context::rendererDestroyIndexBuffer(IndexBufferHandle _handle)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].create(_size, NULL);
	}

	void Context::rendererDestroyDynamicIndexBuffer(IndexBufferHandle _handle)
	{
		s_renderCtx.m_indexBuffers[_handle.idx].destroy();
	}

	void Context::rendererCreateVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl)
	{
		VertexDecl& decl = s_renderCtx.m_vertexDecls[_handle.idx];
		memcpy(&decl, &_decl, sizeof(VertexDecl) );
		dump(decl);
	}

	void Context::rendererDestroyVertexDecl(VertexDeclHandle _handle)
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

	void Context::rendererCreateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size)
	{
		VertexDeclHandle decl = BGFX_INVALID_HANDLE;
		s_renderCtx.m_vertexBuffers[_handle.idx].create(_size, NULL, decl);
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

	void Context::rendererCreateMaterial(MaterialHandle _handle, VertexShaderHandle _vsh, FragmentShaderHandle _fsh)
	{
		s_renderCtx.m_materials[_handle.idx].create(s_renderCtx.m_vertexShaders[_vsh.idx], s_renderCtx.m_fragmentShaders[_fsh.idx]);
	}

	void Context::rendererDestroyMaterial(FragmentShaderHandle _handle)
	{
		s_renderCtx.m_materials[_handle.idx].destroy();
	}

	void Context::rendererCreateTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags)
	{
		s_renderCtx.m_textures[_handle.idx].create(_mem, _flags);
	}

	void Context::rendererDestroyTexture(TextureHandle _handle)
	{
		s_renderCtx.m_textures[_handle.idx].destroy();
	}

	void Context::rendererCreateRenderTarget(RenderTargetHandle _handle, uint16_t _width, uint16_t _height, uint32_t _flags)
	{
		s_renderCtx.m_renderTargets[_handle.idx].create(_width, _height, _flags);
	}

	void Context::rendererDestroyRenderTarget(RenderTargetHandle _handle)
	{
		s_renderCtx.m_renderTargets[_handle.idx].destroy();
	}

	void Context::rendererCreateUniform(UniformHandle _handle, ConstantType::Enum _type, uint16_t _num, const char* _name)
	{
		uint32_t size = g_constantTypeSize[_type]*_num;
		void* data = g_realloc(NULL, size);
		s_renderCtx.m_uniforms[_handle.idx] = data;
		s_renderCtx.m_uniformReg.reg(_name, s_renderCtx.m_uniforms[_handle.idx]);
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

		if (0 < m_render->m_iboffset)
		{
			DynamicIndexBuffer* ib = m_render->m_dynamicIb;
			s_renderCtx.m_indexBuffers[ib->handle.idx].update(m_render->m_iboffset, ib->data);
		}

		if (0 < m_render->m_vboffset)
		{
			DynamicVertexBuffer* vb = m_render->m_dynamicVb;
			s_renderCtx.m_vertexBuffers[vb->handle.idx].update(m_render->m_vboffset, vb->data);
		}

		m_render->sort();

		RenderState currentState;
		currentState.reset();
		currentState.m_flags = BGFX_STATE_NONE;

		Matrix4 viewProj[BGFX_CONFIG_MAX_VIEWS];
		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			matrix_mul(viewProj[ii].val, m_render->m_view[ii].val, m_render->m_proj[ii].val);
		}

		uint16_t materialIdx = bgfx::invalidHandle;
		SortKey key;
		uint8_t view = 0xff;
		RenderTargetHandle rt = BGFX_INVALID_HANDLE;
		int32_t height = m_render->m_resolution.m_height;
		float alphaRef = 0.0f;
		GLenum primType = m_render->m_debug&BGFX_DEBUG_WIREFRAME ? GL_LINES : GL_TRIANGLES;
		uint32_t primNumVerts = 3;
		uint32_t baseVertex = 0;

		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0) );

		uint32_t statsNumPrims = 0;
		uint32_t statsNumIndices = 0;

		int64_t elapsed = -bx::getHPCounter();

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
					materialIdx = bgfx::invalidHandle;

					if (m_render->m_rt[view].idx != rt.idx)
					{
						rt = m_render->m_rt[view];

						if (rt.idx == bgfx::invalidHandle)
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

#if BGFX_CONFIG_RENDERER_OPENGLES
#else
						if (BGFX_STATE_ALPHA_TEST & newFlags)
						{
							GL_CHECK(glEnable(GL_ALPHA_TEST) );
						}
						else
						{
							GL_CHECK(glDisable(GL_ALPHA_TEST) );
						}

						if ( (BGFX_STATE_PT_POINTS|BGFX_STATE_POINT_SIZE_MASK) & changedFlags)
						{
							float pointSize = (float)(uint32_max(1, (newFlags&BGFX_STATE_POINT_SIZE_MASK)>>BGFX_STATE_POINT_SIZE_SHIFT) );
							GL_CHECK(glPointSize(pointSize) );
						}
#endif // BGFX_CONFIG_RENDERER_OPENGLES
						}

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
								GL_CHECK(glBlendFunc(s_blendFactor[src], s_blendFactor[dst]) );
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

					bool materialChanged = false;
					bool constantsChanged = state.m_constBegin < state.m_constEnd;
					bool bindAttribs = false;
					rendererUpdateUniforms(m_render->m_constantBuffer, state.m_constBegin, state.m_constEnd);

					if (key.m_material != materialIdx)
					{
						materialIdx = key.m_material;
						GLuint id = bgfx::invalidHandle == materialIdx ? 0 : s_renderCtx.m_materials[materialIdx].m_id;
						GL_CHECK(glUseProgram(id) );
						materialChanged = 
							constantsChanged = 
							bindAttribs = true;
					}

					if (bgfx::invalidHandle != materialIdx)
					{
						Material& material = s_renderCtx.m_materials[materialIdx];

						if (constantsChanged)
						{
							material.m_constantBuffer->commit(materialChanged);
						}

						for (uint32_t ii = 0, num = material.m_numPredefined; ii < num; ++ii)
						{
							PredefinedUniform& predefined = material.m_predefined[ii];
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

							case PredefinedUniform::ModelViewProj:
								{
									Matrix4 modelViewProj;
									const Matrix4& model = m_render->m_matrixCache.m_cache[state.m_matrix];
									matrix_mul(modelViewProj.val, model.val, viewProj[view].val);

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
									matrix_mul(viewProjBias.val, viewProj[other].val, s_bias);

									Matrix4 modelViewProj;
									matrix_mul(modelViewProj.val, model.val, viewProjBias.val);

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
									matrix_mul(viewProjBias.val, viewProj[other].val, s_bias);

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
									||  materialChanged)
								{
									GL_CHECK(glActiveTexture(GL_TEXTURE0+stage) );
									if (bgfx::invalidHandle != sampler.m_idx)
									{
										GLuint id = 0;
										switch (sampler.m_flags&BGFX_SAMPLER_TYPE_MASK)
										{
										case 0:
											id = s_renderCtx.m_textures[sampler.m_idx].m_id;
											break;

										case 1:
											id = s_renderCtx.m_renderTargets[sampler.m_idx].m_color.m_id;
											break;

										case 2:
											id = s_renderCtx.m_renderTargets[sampler.m_idx].m_depth.m_id;
											break;
										}

										GL_CHECK(glBindTexture(GL_TEXTURE_2D, id) );
										//								GL_CHECK(glUniform1i(material.m_sampler[stage], stage) );
									}
								}

								current = sampler;
								flag <<= 1;
							}

							GL_CHECK(glActiveTexture(GL_TEXTURE0) );
						}

						if (currentState.m_vertexBuffer.idx != state.m_vertexBuffer.idx || materialChanged)
						{
							currentState.m_vertexBuffer = state.m_vertexBuffer;

							uint16_t handle = state.m_vertexBuffer.idx;
							if (bgfx::invalidHandle != handle)
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
							if (bgfx::invalidHandle != handle)
							{
								IndexBuffer& ib = s_renderCtx.m_indexBuffers[handle];
								GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib.m_id) );
							}
							else
							{
								GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) );
							}
						}

						if (bgfx::invalidHandle != currentState.m_vertexBuffer.idx)
						{
							if (baseVertex != state.m_startVertex
							||  bindAttribs)
							{
								baseVertex = state.m_startVertex;
								VertexBuffer& vb = s_renderCtx.m_vertexBuffers[state.m_vertexBuffer.idx];
								uint16_t decl = vb.m_decl.idx == bgfx::invalidHandle ? state.m_vertexDecl.idx : vb.m_decl.idx;
								s_renderCtx.m_materials[materialIdx].bindAttributes(s_renderCtx.m_vertexDecls[decl], state.m_startVertex);
							}

							uint32_t numIndices = 0;
							uint32_t numPrims = 0;

							if (bgfx::invalidHandle != state.m_indexBuffer.idx)
							{
								if (BGFX_DRAW_WHOLE_INDEX_BUFFER == state.m_startIndex)
								{
									numIndices = s_renderCtx.m_indexBuffers[state.m_indexBuffer.idx].m_size/2;
									numPrims = numIndices/primNumVerts;

									GL_CHECK(glDrawElements(primType
										, s_renderCtx.m_indexBuffers[state.m_indexBuffer.idx].m_size/2
										, GL_UNSIGNED_SHORT
										, (void*)0
										) );
								}
								else if (primNumVerts <= state.m_numIndices)
								{
									numIndices = state.m_numIndices;
									numPrims = numIndices/primNumVerts;

									GL_CHECK(glDrawElements(primType
										, numIndices
										, GL_UNSIGNED_SHORT
										, (void*)(uintptr_t)(state.m_startIndex*2)
										) );
								}
							}
							else
							{
								numPrims = state.m_numVertices/primNumVerts;

								GL_CHECK(glDrawArrays(primType
									, 0
									, state.m_numVertices
									) );
							}

							statsNumPrims += numPrims;
							statsNumIndices += numIndices;
						}
					}
				}
		}

		int64_t now = bx::getHPCounter();
		elapsed += now;

		static int64_t last = now;
		int64_t frameTime = now - last;
		last = now;

		if (m_render->m_debug & (BGFX_DEBUG_IFH|BGFX_DEBUG_STATS) )
		{
			TextVideoMem& tvm = s_renderCtx.m_textVideoMem;

			static int64_t next = now;

			if (now >= next)
			{
				next = now + bx::getHPFrequency();
				double freq = double(bx::getHPFrequency() );
				double toMs = 1000.0/freq;

				tvm.clear();
				uint16_t pos = 10;
				tvm.printf(10, pos++, 0x8e, "      Frame: %3.4f [ms] / %3.2f", double(frameTime)*toMs, freq/frameTime);
				tvm.printf(10, pos++, 0x8e, " Draw calls: %4d / %3.4f [ms]", m_render->m_num, double(elapsed)*toMs);
				tvm.printf(10, pos++, 0x8e, "      Prims: %7d", statsNumPrims);
				tvm.printf(10, pos++, 0x8e, "    Indices: %7d", statsNumIndices);
				tvm.printf(10, pos++, 0x8e, "   DVB size: %7d", m_render->m_vboffset);
				tvm.printf(10, pos++, 0x8e, "   DIB size: %7d", m_render->m_iboffset);

				uint8_t attr[2] = { 0x89, 0x8a };
				uint8_t attrIndex = m_render->m_waitSubmit < m_render->m_waitRender;

				tvm.printf(10, pos++, attr[attrIndex&1], "Submit wait: %3.4f [ms]", double(m_render->m_waitSubmit)*toMs);
				tvm.printf(10, pos++, attr[(attrIndex+1)&1], "Render wait: %3.4f [ms]", double(m_render->m_waitRender)*toMs);
			}

			g_textVideoMemBlitter.blit(tvm);
		}
		else if (m_render->m_debug & BGFX_DEBUG_TEXT)
		{
			g_textVideoMemBlitter.blit(m_render->m_textVideoMem);
		}

		GREMEDY_FRAMETERMINATOR();
	}
}

#endif // (BGFX_CONFIG_RENDERER_OPENGLES|BGFX_CONFIG_RENDERER_OPENGL)
