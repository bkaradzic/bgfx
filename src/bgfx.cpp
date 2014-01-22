/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

namespace bgfx
{
#define BGFX_MAIN_THREAD_MAGIC 0x78666762

#if BGFX_CONFIG_MULTITHREADED && !BX_PLATFORM_OSX && !BX_PLATFORM_IOS
#	define BGFX_CHECK_MAIN_THREAD() \
				BX_CHECK(NULL != s_ctx, "Library is not initialized yet."); \
				BX_CHECK(BGFX_MAIN_THREAD_MAGIC == s_threadIndex, "Must be called from main thread.")
#	define BGFX_CHECK_RENDER_THREAD() BX_CHECK(BGFX_MAIN_THREAD_MAGIC != s_threadIndex, "Must be called from render thread.")
#else
#	define BGFX_CHECK_MAIN_THREAD()
#	define BGFX_CHECK_RENDER_THREAD()
#endif // BGFX_CONFIG_MULTITHREADED && !BX_PLATFORM_OSX && !BX_PLATFORM_IOS

#if BX_PLATFORM_ANDROID
	::ANativeWindow* g_bgfxAndroidWindow = NULL;
	void androidSetWindow(::ANativeWindow* _window)
	{
		g_bgfxAndroidWindow = _window;
	}
#elif BX_PLATFORM_IOS
	void* g_bgfxEaglLayer = NULL;
	void iosSetEaglLayer(void* _layer)
	{
		g_bgfxEaglLayer = _layer;
	}

#elif BX_PLATFORM_OSX
	void* g_bgfxNSWindow = NULL;

	void osxSetNSWindow(void* _window)
	{
		g_bgfxNSWindow = _window;
	}
#elif BX_PLATFORM_WINDOWS
	::HWND g_bgfxHwnd = NULL;

	void winSetHwnd(::HWND _window)
	{
		g_bgfxHwnd = _window;
	}
#endif // BX_PLATFORM_*

#if BGFX_CONFIG_USE_TINYSTL
	void* TinyStlAllocator::static_allocate(size_t _bytes)
	{
		return BX_ALLOC(g_allocator, _bytes);
	}

	void TinyStlAllocator::static_deallocate(void* _ptr, size_t /*_bytes*/)
	{
		if (NULL != _ptr)
		{
			BX_FREE(g_allocator, _ptr);
		}
	}
#endif // BGFX_CONFIG_USE_TINYSTL

	struct CallbackStub : public CallbackI
	{
		virtual ~CallbackStub()
		{
		}

		virtual void fatal(Fatal::Enum _code, const char* _str) BX_OVERRIDE
		{
			if (Fatal::DebugCheck == _code)
			{
				bx::debugBreak();
			}
			else
			{
				BX_TRACE("0x%08x: %s", _code, _str);
				BX_UNUSED(_code, _str);
				abort();
			}
		}

		virtual uint32_t cacheReadSize(uint64_t /*_id*/) BX_OVERRIDE
		{
			return 0;
		}

		virtual bool cacheRead(uint64_t /*_id*/, void* /*_data*/, uint32_t /*_size*/) BX_OVERRIDE
		{
			return false;
		}

		virtual void cacheWrite(uint64_t /*_id*/, const void* /*_data*/, uint32_t /*_size*/) BX_OVERRIDE
		{
		}

		virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip) BX_OVERRIDE
		{
			BX_UNUSED(_filePath, _width, _height, _pitch, _data, _size, _yflip);

#if BX_CONFIG_CRT_FILE_READER_WRITER
			char* filePath = (char*)alloca(strlen(_filePath)+5);
			strcpy(filePath, _filePath);
			strcat(filePath, ".tga");

			bx::CrtFileWriter writer;
			if (0 == writer.open(filePath) )
			{
				imageWriteTga(&writer, _width, _height, _pitch, _data, false, _yflip);
				writer.close();
			}
#endif // BX_CONFIG_CRT_FILE_READER_WRITER
		}

		virtual void captureBegin(uint32_t /*_width*/, uint32_t /*_height*/, uint32_t /*_pitch*/, TextureFormat::Enum /*_format*/, bool /*_yflip*/) BX_OVERRIDE
		{
			BX_TRACE("Warning: using capture without callback (a.k.a. pointless).");
		}

		virtual void captureEnd() BX_OVERRIDE
		{
		}

		virtual void captureFrame(const void* /*_data*/, uint32_t /*_size*/) BX_OVERRIDE
		{
		}
	};

	class AllocatorStub : public bx::ReallocatorI
	{
	public:
		AllocatorStub()
#if BGFX_CONFIG_DEBUG
			: m_numBlocks(0)
			, m_maxBlocks(0)
#endif // BGFX_CONFIG_DEBUG
		{
		}

		virtual void* alloc(size_t _size, const char* _file, uint32_t _line) BX_OVERRIDE
		{
#if BGFX_CONFIG_DEBUG
			{
				bx::LwMutexScope scope(m_mutex);
				++m_numBlocks;
				m_maxBlocks = bx::uint32_max(m_maxBlocks, m_numBlocks);
			}
#endif // BGFX_CONFIG_DEBUG

			BX_UNUSED(_file, _line);
			return ::malloc(_size);
		}

		virtual void free(void* _ptr, const char* _file, uint32_t _line) BX_OVERRIDE
		{
			if (NULL != _ptr)
			{
#if BGFX_CONFIG_DEBUG
				{
					bx::LwMutexScope scope(m_mutex);
					BX_CHECK(m_numBlocks > 0, "Number of blocks is 0. Possible alloc/free mismatch?");
					--m_numBlocks;
				}
#endif // BGFX_CONFIG_DEBUG

				BX_UNUSED(_file, _line);
				::free(_ptr);
			}
		}

		virtual void* realloc(void* _ptr, size_t _size, const char* _file, uint32_t _line) BX_OVERRIDE
		{
#if BGFX_CONFIG_DEBUG
			if (NULL == _ptr)
			{
				bx::LwMutexScope scope(m_mutex);
				++m_numBlocks;
				m_maxBlocks = bx::uint32_max(m_maxBlocks, m_numBlocks);
			}
#endif // BGFX_CONFIG_DEBUG

			BX_UNUSED(_file, _line);
			return ::realloc(_ptr, _size);
		}

		void checkLeaks()
		{
			BX_WARN(0 == m_numBlocks, "MEMORY LEAK: %d (max: %d)", m_numBlocks, m_maxBlocks);
		}

	protected:
#if BGFX_CONFIG_DEBUG
		bx::LwMutex m_mutex;
		uint32_t m_numBlocks;
		uint32_t m_maxBlocks;
#endif // BGFX_CONFIG_DEBUG
	};

	static CallbackStub* s_callbackStub = NULL;
	static AllocatorStub* s_allocatorStub = NULL;
	static bool s_graphicsDebuggerPresent = false;

	CallbackI* g_callback = NULL;
	bx::ReallocatorI* g_allocator = NULL;

	Caps g_caps;

	static BX_THREAD uint32_t s_threadIndex = 0;
	static Context* s_ctx = NULL;
	static bool s_renderFrameCalled = false;

	void setGraphicsDebuggerPresent(bool _present)
	{
		BX_TRACE("Graphics debugger is %spresent.", _present ? "" : "not ");
		s_graphicsDebuggerPresent = _present;
	}

	bool isGraphicsDebuggerPresent()
	{
		return s_graphicsDebuggerPresent;
	}

	void fatal(Fatal::Enum _code, const char* _format, ...)
	{
		char temp[8192];

		va_list argList;
		va_start(argList, _format);
		bx::vsnprintf(temp, sizeof(temp), _format, argList);
		va_end(argList);

		temp[sizeof(temp)-1] = '\0';

		g_callback->fatal(_code, temp);
	}

	void mtxOrtho(float* _result, float _left, float _right, float _bottom, float _top, float _near, float _far)
	{
		const float aa = 2.0f/(_right - _left);
		const float bb = 2.0f/(_top - _bottom);
		const float cc = 1.0f/(_far - _near);
		const float dd = (_left + _right)/(_left - _right);
		const float ee = (_top + _bottom)/(_bottom - _top);
		const float ff = _near / (_near - _far);

		memset(_result, 0, sizeof(float)*16);
		_result[0] = aa;
		_result[5] = bb;
		_result[10] = cc;
		_result[12] = dd;
		_result[13] = ee;
		_result[14] = ff;
		_result[15] = 1.0f;
	}

#include "charset.h"

	void charsetFillTexture(const uint8_t* _charset, uint8_t* _rgba, uint32_t _height, uint32_t _pitch, uint32_t _bpp)
	{
		for (uint32_t ii = 0; ii < 256; ++ii)
		{
			uint8_t* pix = &_rgba[ii*8*_bpp];
			for (uint32_t yy = 0; yy < _height; ++yy)
			{
				for (uint32_t xx = 0; xx < 8; ++xx)
				{
					uint8_t bit = 1<<(7-xx);
					memset(&pix[xx*_bpp], _charset[ii*_height+yy]&bit ? 255 : 0, _bpp);
				}

				pix += _pitch;
			}
		}
	}

	static const uint32_t numCharsPerBatch = 1024;
	static const uint32_t numBatchVertices = numCharsPerBatch*4;
	static const uint32_t numBatchIndices = numCharsPerBatch*6;

	void TextVideoMemBlitter::init()
	{
		BGFX_CHECK_MAIN_THREAD();
		m_decl.begin();
		m_decl.add(Attrib::Position, 3, AttribType::Float);
		m_decl.add(Attrib::Color0, 4, AttribType::Uint8, true);
		m_decl.add(Attrib::Color1, 4, AttribType::Uint8, true);
		m_decl.add(Attrib::TexCoord0, 2, AttribType::Float);
		m_decl.end();

		uint16_t width = 2048;
		uint16_t height = 24;
		uint8_t bpp = 1;
		uint32_t pitch = width*bpp;

		const Memory* mem;

		mem = alloc(pitch*height);
		uint8_t* rgba = mem->data;
		charsetFillTexture(vga8x8, rgba, 8, pitch, bpp);
		charsetFillTexture(vga8x16, &rgba[8*pitch], 16, pitch, bpp);
		m_texture = createTexture2D(width, height, 1, TextureFormat::L8
						, BGFX_TEXTURE_MIN_POINT
						| BGFX_TEXTURE_MAG_POINT
						| BGFX_TEXTURE_MIP_POINT
						| BGFX_TEXTURE_U_CLAMP
						| BGFX_TEXTURE_V_CLAMP
						, mem
						);

#if BGFX_CONFIG_RENDERER_DIRECT3D9
		mem = makeRef(vs_debugfont_dx9, sizeof(vs_debugfont_dx9) );
#elif BGFX_CONFIG_RENDERER_DIRECT3D11
		mem = makeRef(vs_debugfont_dx11, sizeof(vs_debugfont_dx11) );
#else
		mem = makeRef(vs_debugfont_glsl, sizeof(vs_debugfont_glsl) );
#endif // BGFX_CONFIG_RENDERER_
		VertexShaderHandle vsh = createVertexShader(mem);

#if BGFX_CONFIG_RENDERER_DIRECT3D9
		mem = makeRef(fs_debugfont_dx9, sizeof(fs_debugfont_dx9) );
#elif BGFX_CONFIG_RENDERER_DIRECT3D11
		mem = makeRef(fs_debugfont_dx11, sizeof(fs_debugfont_dx11) );
#else
		mem = makeRef(fs_debugfont_glsl, sizeof(fs_debugfont_glsl) );
#endif // BGFX_CONFIG_RENDERER_
		FragmentShaderHandle fsh = createFragmentShader(mem);

		m_program = createProgram(vsh, fsh);
		destroyVertexShader(vsh);
		destroyFragmentShader(fsh);

		m_vb = s_ctx->createTransientVertexBuffer(numBatchVertices*m_decl.m_stride, &m_decl);
		m_ib = s_ctx->createTransientIndexBuffer(numBatchIndices*2);
	}

	void TextVideoMemBlitter::shutdown()
	{
		BGFX_CHECK_MAIN_THREAD();

		destroyProgram(m_program);
		destroyTexture(m_texture);
		s_ctx->destroyTransientVertexBuffer(m_vb);
		s_ctx->destroyTransientIndexBuffer(m_ib);
	}

	void TextVideoMemBlitter::blit(const TextVideoMem& _mem)
	{
		BGFX_CHECK_RENDER_THREAD();
		struct Vertex
		{
			float m_x;
			float m_y;
			float m_z;
			uint32_t m_fg;
			uint32_t m_bg;
			float m_u;
			float m_v;
		};

		static uint32_t palette[16] =
		{
			0x0,
			0xff0000cc,
			0xff069a4e,
			0xff00a0c4,
			0xffa46534,
			0xff7b5075,
			0xff9a9806,
			0xffcfd7d3,
			0xff535755,
			0xff2929ef,
			0xff34e28a,
			0xff4fe9fc,
			0xffcf9f72,
			0xffa87fad,
			0xffe2e234,
			0xffeceeee,
		};

		uint32_t yy = 0;
		uint32_t xx = 0;

		const float texelWidth = 1.0f/2048.0f;
		const float texelWidthHalf = texelWidth*0.5f;
		const float texelHeight = 1.0f/24.0f;
#if BGFX_CONFIG_RENDERER_DIRECT3D9
		const float texelHeightHalf = texelHeight*0.5f;
#else
		const float texelHeightHalf = 0.0f;
#endif // BGFX_CONFIG_RENDERER_
		const float utop = (_mem.m_small ? 0.0f : 8.0f)*texelHeight + texelHeightHalf;
		const float ubottom = (_mem.m_small ? 8.0f : 24.0f)*texelHeight + texelHeightHalf;
		const float fontHeight = (_mem.m_small ? 8.0f : 16.0f);

		setup();

		for (;yy < _mem.m_height;)
		{
			Vertex* vertex = (Vertex*)m_vb->data;
			uint16_t* indices = (uint16_t*)m_ib->data;
			uint32_t startVertex = 0;
			uint32_t numIndices = 0;

			for (; yy < _mem.m_height && numIndices < numBatchIndices; ++yy)
			{
				xx = xx < _mem.m_width ? xx : 0;
				const uint8_t* line = &_mem.m_mem[(yy*_mem.m_width+xx)*2];

				for (; xx < _mem.m_width && numIndices < numBatchIndices; ++xx)
				{
					uint8_t ch = line[0];
					uint8_t attr = line[1];

					if (0 != (ch|attr)
					&& (' ' != ch || 0 != (attr&0xf0) ) )
					{
						uint32_t fg = palette[attr&0xf];
						uint32_t bg = palette[(attr>>4)&0xf];

						Vertex vert[4] =
						{
							{ (xx  )*8.0f, (yy  )*fontHeight, 0.0f, fg, bg, (ch  )*8.0f*texelWidth - texelWidthHalf, utop },
							{ (xx+1)*8.0f, (yy  )*fontHeight, 0.0f, fg, bg, (ch+1)*8.0f*texelWidth - texelWidthHalf, utop },
							{ (xx+1)*8.0f, (yy+1)*fontHeight, 0.0f, fg, bg, (ch+1)*8.0f*texelWidth - texelWidthHalf, ubottom },
							{ (xx  )*8.0f, (yy+1)*fontHeight, 0.0f, fg, bg, (ch  )*8.0f*texelWidth - texelWidthHalf, ubottom },
						};

						memcpy(vertex, vert, sizeof(vert) );
						vertex += 4;

						indices[0] = startVertex+0;
						indices[1] = startVertex+1;
						indices[2] = startVertex+2;
						indices[3] = startVertex+2;
						indices[4] = startVertex+3;
						indices[5] = startVertex+0;

						startVertex += 4;
						indices += 6;

						numIndices += 6;
					}

					line += 2;
				}

				if (numIndices >= numBatchIndices)
				{
					break;
				}
			}

			render(numIndices);
		}
	}

	void ClearQuad::init()
	{
		BGFX_CHECK_MAIN_THREAD();
#if BGFX_CONFIG_CLEAR_QUAD
		m_decl.begin();
		m_decl.add(Attrib::Position, 3, AttribType::Float);
		m_decl.add(Attrib::Color0, 4, AttribType::Uint8, true);
		m_decl.end();

		const Memory* mem;

#	if BGFX_CONFIG_RENDERER_DIRECT3D11
		mem = makeRef(vs_clear_dx11, sizeof(vs_clear_dx11) );
#	elif BGFX_CONFIG_RENDERER_OPENGL
		mem = makeRef(vs_clear_glsl, sizeof(vs_clear_glsl) );
#	endif // BGFX_CONFIG_RENDERER_*
		VertexShaderHandle vsh = createVertexShader(mem);

#	if BGFX_CONFIG_RENDERER_DIRECT3D11
		mem = makeRef(fs_clear_dx11, sizeof(fs_clear_dx11) );
#	elif BGFX_CONFIG_RENDERER_OPENGL
		mem = makeRef(fs_clear_glsl, sizeof(fs_clear_glsl) );
#	endif // BGFX_CONFIG_RENDERER_*
		FragmentShaderHandle fsh = createFragmentShader(mem);

		m_program = createProgram(vsh, fsh);
		destroyVertexShader(vsh);
		destroyFragmentShader(fsh);

		m_vb = s_ctx->createTransientVertexBuffer(4*m_decl.m_stride, &m_decl);

		mem = alloc(6*sizeof(uint16_t) );
		uint16_t* indices = (uint16_t*)mem->data;
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;
		m_ib = s_ctx->createIndexBuffer(mem);
#endif // BGFX_CONFIG_CLEAR_QUAD
	}

	void ClearQuad::shutdown()
	{
		BGFX_CHECK_MAIN_THREAD();

#if BGFX_CONFIG_CLEAR_QUAD
		destroyProgram(m_program);
		destroyIndexBuffer(m_ib);
		s_ctx->destroyTransientVertexBuffer(m_vb);
#endif // BGFX_CONFIG_CLEAR_QUAD
	}

	static const char* s_predefinedName[PredefinedUniform::Count] =
	{
		"u_viewRect",
		"u_viewTexel",
		"u_view",
		"u_viewProj",
		"u_viewProjX",
		"u_model",
		"u_modelView",
		"u_modelViewProj",
		"u_modelViewProjX",
		"u_alphaRef",
	};

	const char* getPredefinedUniformName(PredefinedUniform::Enum _enum)
	{
		return s_predefinedName[_enum];
	}

	PredefinedUniform::Enum nameToPredefinedUniformEnum(const char* _name)
	{
		for (uint32_t ii = 0; ii < PredefinedUniform::Count; ++ii)
		{
			if (0 == strcmp(_name, s_predefinedName[ii]) )
			{
				return PredefinedUniform::Enum(ii);
			}
		}

		return PredefinedUniform::Count;
	}

	uint32_t Frame::submit(uint8_t _id, int32_t _depth)
	{
		if (m_discard)
		{
			discard();
			return m_num;
		}

		if (BGFX_CONFIG_MAX_DRAW_CALLS-1 <= m_num
		|| (0 == m_state.m_numVertices && 0 == m_state.m_numIndices) )
		{
			++m_numDropped;
			return m_num;
		}

		BX_WARN(invalidHandle != m_key.m_program, "Program with invalid handle");
		if (invalidHandle != m_key.m_program)
		{
			m_key.m_depth = _depth;
			m_key.m_view = _id;
			m_key.m_seq = s_ctx->m_seq[_id] & s_ctx->m_seqMask[_id];
			s_ctx->m_seq[_id]++;
			uint64_t key = m_key.encode();
			m_sortKeys[m_num] = key;
			m_sortValues[m_num] = m_numRenderStates;
			++m_num;

			m_state.m_constEnd = m_constantBuffer->getPos();
			m_state.m_flags |= m_flags;
			m_renderState[m_numRenderStates] = m_state;
			++m_numRenderStates;
		}

		m_state.clear();
		m_flags = BGFX_STATE_NONE;

		return m_num;
	}

	uint32_t Frame::submitMask(uint32_t _viewMask, int32_t _depth)
	{
		if (m_discard)
		{
			discard();
			return m_num;
		}

		if (BGFX_CONFIG_MAX_DRAW_CALLS-1 <= m_num
		|| (0 == m_state.m_numVertices && 0 == m_state.m_numIndices) )
		{
			m_numDropped += bx::uint32_cntbits(_viewMask);
			return m_num;
		}

		BX_WARN(invalidHandle != m_key.m_program, "Program with invalid handle");
		if (invalidHandle != m_key.m_program)
		{
			m_key.m_depth = _depth;

			for (uint32_t id = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, id += 1, ntz = bx::uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				id += ntz;

				m_key.m_view = id;
				m_key.m_seq = s_ctx->m_seq[id] & s_ctx->m_seqMask[id];
				s_ctx->m_seq[id]++;
				uint64_t key = m_key.encode();
				m_sortKeys[m_num] = key;
				m_sortValues[m_num] = m_numRenderStates;
				++m_num;
			}

			m_state.m_constEnd = m_constantBuffer->getPos();
			m_state.m_flags |= m_flags;
			m_renderState[m_numRenderStates] = m_state;
			++m_numRenderStates;
		}

		m_state.clear();
		m_flags = BGFX_STATE_NONE;

		return m_num;
	}

	void Frame::sort()
	{
		bx::radixSort64(m_sortKeys, s_ctx->m_tempKeys, m_sortValues, s_ctx->m_tempValues, m_num);
	}

	const Caps* getCaps()
	{
		BGFX_CHECK_MAIN_THREAD();
		return &g_caps;
	}

	RendererType::Enum getRendererType()
	{
#if BGFX_CONFIG_RENDERER_DIRECT3D9
		return RendererType::Direct3D9;
#elif BGFX_CONFIG_RENDERER_DIRECT3D11
		return RendererType::Direct3D11;
#elif BGFX_CONFIG_RENDERER_OPENGL
		return RendererType::OpenGL;
#elif BGFX_CONFIG_RENDERER_OPENGLES2
		return RendererType::OpenGLES2;
#elif BGFX_CONFIG_RENDERER_OPENGLES3
		return RendererType::OpenGLES3;
#else
		return RendererType::Null;
#endif // BGFX_CONFIG_RENDERER_
	}

	struct CapsFlags
	{
		uint64_t m_flag;
		const char* m_str;
	};

	static const CapsFlags s_capsFlags[] =
	{
#define CAPS_FLAGS(_x) { _x, #_x }
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_BC1),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_BC2),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_BC3),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_BC4),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_BC5),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_ETC1),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_ETC2),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_ETC2A),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_ETC2A1),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_PTC12),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_PTC14),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_PTC14A),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_PTC12A),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_PTC22),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_PTC24),

		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_D16),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_D24),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_D24S8),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_D32),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_D16F),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_D24F),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_D32F),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_FORMAT_D0S8),

		CAPS_FLAGS(BGFX_CAPS_TEXTURE_3D),
		CAPS_FLAGS(BGFX_CAPS_VERTEX_ATTRIB_HALF),
		CAPS_FLAGS(BGFX_CAPS_INSTANCING),
		CAPS_FLAGS(BGFX_CAPS_RENDERER_MULTITHREADED),
		CAPS_FLAGS(BGFX_CAPS_FRAGMENT_DEPTH),
#undef CAPS_FLAGS
	};

	void init(CallbackI* _callback, bx::ReallocatorI* _allocator)
	{
		BX_TRACE("Init...");

		memset(&g_caps, 0, sizeof(g_caps) );
		g_caps.rendererType = getRendererType();
		g_caps.supported = 0
			| (BGFX_CONFIG_MULTITHREADED ? BGFX_CAPS_RENDERER_MULTITHREADED : 0)
			;
		g_caps.emulated = 0;
		g_caps.maxDrawCalls = BGFX_CONFIG_MAX_DRAW_CALLS;

		if (NULL != _allocator)
		{
			g_allocator = _allocator;
		}
		else
		{
			bx::CrtAllocator allocator;
			g_allocator =
			s_allocatorStub = BX_NEW(&allocator, AllocatorStub);
		}

		if (NULL != _callback)
		{
			g_callback = _callback;
		}
		else
		{
			g_callback =
			s_callbackStub = BX_NEW(g_allocator, CallbackStub);
		}

		s_threadIndex = BGFX_MAIN_THREAD_MAGIC;

		s_ctx = BX_NEW(g_allocator, Context);
		s_ctx->init();

		const uint64_t emulatedCaps = 0
			| BGFX_CAPS_TEXTURE_FORMAT_BC1
			| BGFX_CAPS_TEXTURE_FORMAT_BC2
			| BGFX_CAPS_TEXTURE_FORMAT_BC3
			| BGFX_CAPS_TEXTURE_FORMAT_BC4
			| BGFX_CAPS_TEXTURE_FORMAT_BC5
			| BGFX_CAPS_TEXTURE_FORMAT_ETC1
			| BGFX_CAPS_TEXTURE_FORMAT_ETC2
			| BGFX_CAPS_TEXTURE_FORMAT_ETC2A
			| BGFX_CAPS_TEXTURE_FORMAT_ETC2A1
			;

		g_caps.emulated |= emulatedCaps ^ (g_caps.supported & emulatedCaps);

		BX_TRACE("Supported capabilities:");
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_capsFlags); ++ii)
		{
			if (0 != (g_caps.supported & s_capsFlags[ii].m_flag) )
			{
				BX_TRACE("\t%s", s_capsFlags[ii].m_str);
			}
		}

		BX_TRACE("Emulated capabilities:");
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_capsFlags); ++ii)
		{
			if (0 != (g_caps.emulated & s_capsFlags[ii].m_flag) )
			{
				BX_TRACE("\t%s", s_capsFlags[ii].m_str);
			}
		}

		BX_TRACE("Init complete.");
	}

	void shutdown()
	{
		BX_TRACE("Shutdown...");

		BGFX_CHECK_MAIN_THREAD();
		Context* ctx = s_ctx; // it's going to be NULLd inside shutdown.
		ctx->shutdown();

		BX_DELETE(g_allocator, ctx);

		if (NULL != s_callbackStub)
		{
			BX_DELETE(g_allocator, s_callbackStub);
			s_callbackStub = NULL;
		}

		if (NULL != s_allocatorStub)
		{
			s_allocatorStub->checkLeaks();

			bx::CrtAllocator allocator;
			BX_DELETE(&allocator, s_allocatorStub);
			s_allocatorStub = NULL;
		}

		s_threadIndex = 0;
		g_callback = NULL;
		g_allocator = NULL;

		BX_TRACE("Shutdown complete.");
	}

	void reset(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->reset(_width, _height, _flags);
	}

	uint32_t frame()
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->frame();
	}

	RenderFrame::Enum renderFrame()
	{
		if (NULL == s_ctx)
		{
			s_renderFrameCalled = true;
			return RenderFrame::NoContext;
		}

		BGFX_CHECK_RENDER_THREAD();
		if (s_ctx->renderFrame() )
		{
			return RenderFrame::Exiting;
		}

		return RenderFrame::Render;
	}

	const uint32_t g_uniformTypeSize[UniformType::Count+1] =
	{
		sizeof(int32_t),
		sizeof(float),
		0,
		1*sizeof(int32_t),
		1*sizeof(float),
		2*sizeof(float),
		3*sizeof(float),
		4*sizeof(float),
		3*3*sizeof(float),
		4*4*sizeof(float),
		1,
	};

	void ConstantBuffer::writeUniform(UniformType::Enum _type, uint16_t _loc, const void* _value, uint16_t _num)
	{
		uint32_t opcode = encodeOpcode(_type, _loc, _num, true);
		write(opcode);
		write(_value, g_uniformTypeSize[_type]*_num);
	}

	void ConstantBuffer::writeUniformRef(UniformType::Enum _type, uint16_t _loc, const void* _value, uint16_t _num)
	{
		uint32_t opcode = encodeOpcode(_type, _loc, _num, false);
		write(opcode);
		write(&_value, sizeof(void*) );
	}

	void ConstantBuffer::writeMarker(const char* _marker)
	{
		uint16_t num = (uint16_t)strlen(_marker)+1;
		uint32_t opcode = encodeOpcode(bgfx::UniformType::Count, 0, num, true);
		write(opcode);
		write(_marker, num);
	}

	void Context::init()
	{
		BX_CHECK(!m_rendererInitialized, "Already initialized?");

		m_exit = false;
		m_frames = 0;
		m_render = &m_frame[0];
		m_submit = &m_frame[1];
		m_debug = BGFX_DEBUG_NONE;

		m_submit->create();
		m_render->create();

#if BGFX_CONFIG_MULTITHREADED
		if (s_renderFrameCalled)
		{
			// When bgfx::renderFrame is called before init render thread
			// should not be created.
			BX_TRACE("Application called bgfx::renderFrame directly, not creating render thread.");
		}
		else
		{
			BX_TRACE("Creating rendering thread.");
			m_thread.init(renderThread, this);
		}
#else
		BX_TRACE("Multithreaded renderer is disabled.");
#endif // BGFX_CONFIG_MULTITHREADED

		memset(m_rt, 0xff, sizeof(m_rt) );
		memset(m_clear, 0, sizeof(m_clear) );
		memset(m_rect, 0, sizeof(m_rect) );
		memset(m_scissor, 0, sizeof(m_scissor) );
		memset(m_seq, 0, sizeof(m_seq) );
		memset(m_seqMask, 0, sizeof(m_seqMask) );

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_rect); ++ii)
		{
			m_rect[ii].m_width = 1;
			m_rect[ii].m_height = 1;
		}

		m_declRef.init();

		frameNoRenderWait();

		getCommandBuffer(CommandBuffer::RendererInit);

		m_textVideoMemBlitter.init();
		m_clearQuad.init();

		m_submit->m_transientVb = createTransientVertexBuffer(BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
		m_submit->m_transientIb = createTransientIndexBuffer(BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
		frame();
		m_submit->m_transientVb = createTransientVertexBuffer(BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
		m_submit->m_transientIb = createTransientIndexBuffer(BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
		frame();

		for (uint8_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			char name[256];
			bx::snprintf(name, sizeof(name), "%02d view", ii);
			setViewName(ii, name);
		}

		BX_TRACE("Init complete.");
	}

	void Context::shutdown()
	{
		getCommandBuffer(CommandBuffer::RendererShutdownBegin);
		frame();

		destroyTransientVertexBuffer(m_submit->m_transientVb);
		destroyTransientIndexBuffer(m_submit->m_transientIb);
		m_textVideoMemBlitter.shutdown();
		m_clearQuad.shutdown();
		frame();

		destroyTransientVertexBuffer(m_submit->m_transientVb);
		destroyTransientIndexBuffer(m_submit->m_transientIb);
		frame();

		frame(); // If any VertexDecls needs to be destroyed.

		getCommandBuffer(CommandBuffer::RendererShutdownEnd);
		frame();

		m_declRef.shutdown(m_vertexDeclHandle);

#if BGFX_CONFIG_MULTITHREADED
		if (m_thread.isRunning() )
		{
			m_thread.shutdown();
		}
#endif // BGFX_CONFIG_MULTITHREADED

		s_ctx = NULL; // Can't be used by renderFrame at this point.
		renderSemWait();

		m_submit->destroy();
		m_render->destroy();

#if BGFX_CONFIG_DEBUG
#	define CHECK_HANDLE_LEAK(_handleAlloc) \
		do { \
			BX_WARN(0 == _handleAlloc.getNumHandles() \
				, "LEAK: " #_handleAlloc " %d (max: %d)" \
				, _handleAlloc.getNumHandles() \
				, _handleAlloc.getMaxHandles() \
				); \
		} while (0)

		CHECK_HANDLE_LEAK(m_dynamicIndexBufferHandle);
		CHECK_HANDLE_LEAK(m_dynamicVertexBufferHandle);
		CHECK_HANDLE_LEAK(m_indexBufferHandle);
		CHECK_HANDLE_LEAK(m_vertexDeclHandle);
		CHECK_HANDLE_LEAK(m_vertexBufferHandle);
		CHECK_HANDLE_LEAK(m_vertexShaderHandle);
		CHECK_HANDLE_LEAK(m_fragmentShaderHandle);
		CHECK_HANDLE_LEAK(m_programHandle);
		CHECK_HANDLE_LEAK(m_textureHandle);
		CHECK_HANDLE_LEAK(m_renderTargetHandle);
		CHECK_HANDLE_LEAK(m_uniformHandle);

#	undef CHECK_HANDLE_LEAK
#endif // BGFX_CONFIG_DEBUG
	}

	void Context::freeDynamicBuffers()
	{
		for (uint16_t ii = 0, num = m_numFreeDynamicIndexBufferHandles; ii < num; ++ii)
		{
			destroyDynamicIndexBufferInternal(m_freeDynamicIndexBufferHandle[ii]);
		}
		m_numFreeDynamicIndexBufferHandles = 0;

		for (uint16_t ii = 0, num = m_numFreeDynamicVertexBufferHandles; ii < num; ++ii)
		{
			destroyDynamicVertexBufferInternal(m_freeDynamicVertexBufferHandle[ii]);
		}
		m_numFreeDynamicVertexBufferHandles = 0;
	}

	void Context::freeAllHandles(Frame* _frame)
	{
		for (uint16_t ii = 0, num = _frame->m_numFreeIndexBufferHandles; ii < num; ++ii)
		{
			m_indexBufferHandle.free(_frame->m_freeIndexBufferHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeVertexDeclHandles; ii < num; ++ii)
		{
			m_vertexDeclHandle.free(_frame->m_freeVertexDeclHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeVertexBufferHandles; ii < num; ++ii)
		{
			destroyVertexBufferInternal(_frame->m_freeVertexBufferHandle[ii]);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeVertexShaderHandles; ii < num; ++ii)
		{
			m_vertexShaderHandle.free(_frame->m_freeVertexShaderHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeFragmentShaderHandles; ii < num; ++ii)
		{
			m_fragmentShaderHandle.free(_frame->m_freeFragmentShaderHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeProgramHandles; ii < num; ++ii)
		{
			m_programHandle.free(_frame->m_freeProgramHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeTextureHandles; ii < num; ++ii)
		{
			m_textureHandle.free(_frame->m_freeTextureHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeRenderTargetHandles; ii < num; ++ii)
		{
			m_renderTargetHandle.free(_frame->m_freeRenderTargetHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeUniformHandles; ii < num; ++ii)
		{
			m_uniformHandle.free(_frame->m_freeUniformHandle[ii].idx);
		}
	}

	uint32_t Context::frame()
	{
		BX_CHECK(0 == m_instBufferCount, "Instance buffer allocated, but not used. This is incorrect, and causes memory leak.");

		// wait for render thread to finish
		renderSemWait();
		frameNoRenderWait();

		return m_frames;
	}

	void Context::frameNoRenderWait()
	{
		swap();

		// release render thread
		gameSemPost();

#if !BGFX_CONFIG_MULTITHREADED
		renderFrame();
#endif // BGFX_CONFIG_MULTITHREADED
	}

	void Context::swap()
	{
		freeDynamicBuffers();
		m_submit->m_resolution = m_resolution;
		m_submit->m_debug = m_debug;
		memcpy(m_submit->m_rt, m_rt, sizeof(m_rt) );
		memcpy(m_submit->m_clear, m_clear, sizeof(m_clear) );
		memcpy(m_submit->m_rect, m_rect, sizeof(m_rect) );
		memcpy(m_submit->m_scissor, m_scissor, sizeof(m_scissor) );
		memcpy(m_submit->m_view, m_view, sizeof(m_view) );
		memcpy(m_submit->m_proj, m_proj, sizeof(m_proj) );
		memcpy(m_submit->m_other, m_other, sizeof(m_other) );
		m_submit->finish();

		Frame* temp = m_render;
		m_render = m_submit;
		m_submit = temp;

		m_frames++;
		m_submit->start();

		memset(m_seq, 0, sizeof(m_seq) );
		freeAllHandles(m_submit);

		m_submit->resetFreeHandles();
		m_submit->m_textVideoMem->resize(m_render->m_textVideoMem->m_small, m_resolution.m_width, m_resolution.m_height);
	}

	bool Context::renderFrame()
	{
		rendererFlip();

		gameSemWait();

		rendererExecCommands(m_render->m_cmdPre);
		if (m_rendererInitialized)
		{
			rendererSubmit();
		}
		rendererExecCommands(m_render->m_cmdPost);

		renderSemPost();

		return m_exit;
	}

	void Context::rendererUpdateUniforms(ConstantBuffer* _constantBuffer, uint32_t _begin, uint32_t _end)
	{
		_constantBuffer->reset(_begin);
		while (_constantBuffer->getPos() < _end)
		{
			uint32_t opcode = _constantBuffer->read();

			if (UniformType::End == opcode)
			{
				break;
			}

			UniformType::Enum type;
			uint16_t loc;
			uint16_t num;
			uint16_t copy;
			ConstantBuffer::decodeOpcode(opcode, type, loc, num, copy);

			uint32_t size = g_uniformTypeSize[type]*num;
			const char* data = _constantBuffer->read(size);
			if (UniformType::Count > type)
			{
				rendererUpdateUniform(loc, data, size);
			}
			else
			{
				rendererSetMarker(data, size);
			}
		}
	}

	void Context::flushTextureUpdateBatch(CommandBuffer& _cmdbuf)
	{
		if (m_textureUpdateBatch.sort() )
		{
			const uint32_t pos = _cmdbuf.m_pos;

			uint32_t currentKey = UINT32_MAX;

			for (uint32_t ii = 0, num = m_textureUpdateBatch.m_num; ii < num; ++ii)
			{
				_cmdbuf.m_pos = m_textureUpdateBatch.m_values[ii];

				TextureHandle handle;
				_cmdbuf.read(handle);

				uint8_t side;
				_cmdbuf.read(side);

				uint8_t mip;
				_cmdbuf.read(mip);

				Rect rect;
				_cmdbuf.read(rect);

				uint16_t zz;
				_cmdbuf.read(zz);

				uint16_t depth;
				_cmdbuf.read(depth);

				uint16_t pitch;
				_cmdbuf.read(pitch);

				Memory* mem;
				_cmdbuf.read(mem);

				uint32_t key = m_textureUpdateBatch.m_keys[ii];
				if (key != currentKey)
				{
					if (currentKey != UINT32_MAX)
					{
						rendererUpdateTextureEnd();
					}
					currentKey = key;
					rendererUpdateTextureBegin(handle, side, mip);
				}

				rendererUpdateTexture(handle, side, mip, rect, zz, depth, pitch, mem);

				release(mem);
			}

			if (currentKey != UINT32_MAX)
			{
				rendererUpdateTextureEnd();
			}

			m_textureUpdateBatch.reset();

			_cmdbuf.m_pos = pos;
		}
	}

	void Context::rendererExecCommands(CommandBuffer& _cmdbuf)
	{
		_cmdbuf.reset();

		bool end = false;

		do
		{
			uint8_t command;
			_cmdbuf.read(command);

			switch (command)
			{
			case CommandBuffer::RendererInit:
				{
					BX_CHECK(!m_rendererInitialized, "This shouldn't happen! Bad synchronization?");
					rendererInit();
					m_rendererInitialized = true;
				}
				break;

			case CommandBuffer::RendererShutdownBegin:
				{
					BX_CHECK(m_rendererInitialized, "This shouldn't happen! Bad synchronization?");
					m_rendererInitialized = false;
				}
				break;

			case CommandBuffer::RendererShutdownEnd:
				{
					BX_CHECK(!m_rendererInitialized && !m_exit, "This shouldn't happen! Bad synchronization?");
					rendererShutdown();
					m_exit = true;
				}
				break;

			case CommandBuffer::CreateIndexBuffer:
				{
					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					Memory* mem;
					_cmdbuf.read(mem);

					rendererCreateIndexBuffer(handle, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyIndexBuffer:
				{
					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyIndexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateVertexDecl:
				{
					VertexDeclHandle handle;
					_cmdbuf.read(handle);

					VertexDecl decl;
					_cmdbuf.read(decl);

					rendererCreateVertexDecl(handle, decl);
				}
				break;

			case CommandBuffer::DestroyVertexDecl:
				{
					VertexDeclHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyVertexDecl(handle);
				}
				break;

			case CommandBuffer::CreateVertexBuffer:
				{
					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					Memory* mem;
					_cmdbuf.read(mem);

					VertexDeclHandle declHandle;
					_cmdbuf.read(declHandle);

					rendererCreateVertexBuffer(handle, mem, declHandle);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyVertexBuffer:
				{
					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyVertexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateDynamicIndexBuffer:
				{
					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					uint32_t size;
					_cmdbuf.read(size);

					rendererCreateDynamicIndexBuffer(handle, size);
				}
				break;

			case CommandBuffer::UpdateDynamicIndexBuffer:
				{
					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					uint32_t offset;
					_cmdbuf.read(offset);

					uint32_t size;
					_cmdbuf.read(size);

					Memory* mem;
					_cmdbuf.read(mem);

					rendererUpdateDynamicIndexBuffer(handle, offset, size, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyDynamicIndexBuffer:
				{
					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyDynamicIndexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateDynamicVertexBuffer:
				{
					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					uint32_t size;
					_cmdbuf.read(size);

					rendererCreateDynamicVertexBuffer(handle, size);
				}
				break;

			case CommandBuffer::UpdateDynamicVertexBuffer:
				{
					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					uint32_t offset;
					_cmdbuf.read(offset);

					uint32_t size;
					_cmdbuf.read(size);

					Memory* mem;
					_cmdbuf.read(mem);

					rendererUpdateDynamicVertexBuffer(handle, offset, size, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyDynamicVertexBuffer:
				{
					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyDynamicVertexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateVertexShader:
				{
					VertexShaderHandle handle;
					_cmdbuf.read(handle);

					Memory* mem;
					_cmdbuf.read(mem);

					rendererCreateVertexShader(handle, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyVertexShader:
				{
					VertexShaderHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyVertexShader(handle);
				}
				break;

			case CommandBuffer::CreateFragmentShader:
				{
					FragmentShaderHandle handle;
					_cmdbuf.read(handle);

					Memory* mem;
					_cmdbuf.read(mem);

					rendererCreateFragmentShader(handle, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyFragmentShader:
				{
					FragmentShaderHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyFragmentShader(handle);
				}
				break;

			case CommandBuffer::CreateProgram:
				{
					ProgramHandle handle;
					_cmdbuf.read(handle);

					VertexShaderHandle vsh;
					_cmdbuf.read(vsh);

					FragmentShaderHandle fsh;
					_cmdbuf.read(fsh);

					rendererCreateProgram(handle, vsh, fsh);
				}
				break;

			case CommandBuffer::DestroyProgram:
				{
					FragmentShaderHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyProgram(handle);
				}
				break;

			case CommandBuffer::CreateTexture:
				{
					TextureHandle handle;
					_cmdbuf.read(handle);

					Memory* mem;
					_cmdbuf.read(mem);

					uint32_t flags;
					_cmdbuf.read(flags);

					rendererCreateTexture(handle, mem, flags);

					bx::MemoryReader reader(mem->data, mem->size);

					uint32_t magic;
					bx::read(&reader, magic);

					if (BGFX_CHUNK_MAGIC_TEX == magic)
					{
						TextureCreate tc;
						bx::read(&reader, tc);

						if (NULL != tc.m_mem)
						{
							release(tc.m_mem);
						}
					}

					release(mem);
				}
				break;

			case CommandBuffer::UpdateTexture:
				{
					if (m_textureUpdateBatch.isFull() )
					{
						flushTextureUpdateBatch(_cmdbuf);
					}

					uint32_t value = _cmdbuf.m_pos;

					TextureHandle handle;
					_cmdbuf.read(handle);

					uint8_t side;
					_cmdbuf.read(side);

					uint8_t mip;
					_cmdbuf.read(mip);

					_cmdbuf.skip(sizeof(Rect)
						+ sizeof(uint16_t)
						+ sizeof(uint16_t)
						+ sizeof(uint16_t)
						+ sizeof(Memory*)
						);

					uint32_t key = (handle.idx<<16)
						| (side<<8)
						| mip
						;

					m_textureUpdateBatch.add(key, value);
				}
				break;

			case CommandBuffer::DestroyTexture:
				{
					TextureHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyTexture(handle);
				}
				break;

			case CommandBuffer::CreateRenderTarget:
				{
					RenderTargetHandle handle;
					_cmdbuf.read(handle);

					uint16_t width;
					_cmdbuf.read(width);

					uint16_t height;
					_cmdbuf.read(height);

					uint32_t flags;
					_cmdbuf.read(flags);

					uint32_t textureFlags;
					_cmdbuf.read(textureFlags);

					rendererCreateRenderTarget(handle, width, height, flags, textureFlags);
				}
				break;

			case CommandBuffer::DestroyRenderTarget:
				{
					RenderTargetHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyRenderTarget(handle);
				}
				break;

			case CommandBuffer::CreateUniform:
				{
					UniformHandle handle;
					_cmdbuf.read(handle);

					UniformType::Enum type;
					_cmdbuf.read(type);

					uint16_t num;
					_cmdbuf.read(num);

					uint8_t len;
					_cmdbuf.read(len);

					const char* name = (const char*)_cmdbuf.skip(len);

					rendererCreateUniform(handle, type, num, name);
				}
				break;

			case CommandBuffer::DestroyUniform:
				{
					UniformHandle handle;
					_cmdbuf.read(handle);

					rendererDestroyUniform(handle);
				}
				break;

			case CommandBuffer::SaveScreenShot:
				{
					uint16_t len;
					_cmdbuf.read(len);

					const char* filePath = (const char*)_cmdbuf.skip(len);

					rendererSaveScreenShot(filePath);
				}
				break;

			case CommandBuffer::UpdateViewName:
				{
					uint8_t id;
					_cmdbuf.read(id);

					uint16_t len;
					_cmdbuf.read(len);

					const char* name = (const char*)_cmdbuf.skip(len);

					rendererUpdateViewName(id, name);
				}
				break;

			case CommandBuffer::End:
				end = true;
				break;

			default:
				BX_CHECK(false, "WTF!");
				break;
			}
		} while (!end);

		flushTextureUpdateBatch(_cmdbuf);
	}

	const Memory* alloc(uint32_t _size)
	{
		Memory* mem = (Memory*)BX_ALLOC(g_allocator, sizeof(Memory) + _size);
		mem->size = _size;
		mem->data = (uint8_t*)mem + sizeof(Memory);
		return mem;
	}

	const Memory* makeRef(const void* _data, uint32_t _size)
	{
		Memory* mem = (Memory*)BX_ALLOC(g_allocator, sizeof(Memory) );
		mem->size = _size;
		mem->data = (uint8_t*)_data;
		return mem;
	}

	void release(const Memory* _mem)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		BX_FREE(g_allocator, const_cast<Memory*>(_mem) );
	}

	void setDebug(uint32_t _debug)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setDebug(_debug);
	}

	void dbgTextClear(uint8_t _attr, bool _small)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->dbgTextClear(_attr, _small);
	}

	void dbgTextPrintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...)
	{
		BGFX_CHECK_MAIN_THREAD();
		va_list argList;
		va_start(argList, _format);
		s_ctx->dbgTextPrintfVargs(_x, _y, _attr, _format, argList);
		va_end(argList);
	}

	IndexBufferHandle createIndexBuffer(const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->createIndexBuffer(_mem);
	}

	void destroyIndexBuffer(IndexBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyIndexBuffer(_handle);
	}

	VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 != _decl.m_stride, "Invalid VertexDecl.");
		return s_ctx->createVertexBuffer(_mem, _decl);
	}

	void destroyVertexBuffer(VertexBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyVertexBuffer(_handle);
	}

	DynamicIndexBufferHandle createDynamicIndexBuffer(uint32_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->createDynamicIndexBuffer(_num);
	}

	DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createDynamicIndexBuffer(_mem);
	}

	void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		s_ctx->updateDynamicIndexBuffer(_handle, _mem);
	}

	void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyDynamicIndexBuffer(_handle);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(uint16_t _num, const VertexDecl& _decl)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 != _decl.m_stride, "Invalid VertexDecl.");
		return s_ctx->createDynamicVertexBuffer(_num, _decl);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexDecl& _decl)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		BX_CHECK(0 != _decl.m_stride, "Invalid VertexDecl.");
		return s_ctx->createDynamicVertexBuffer(_mem, _decl);
	}

	void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		s_ctx->updateDynamicVertexBuffer(_handle, _mem);
	}

	void destroyDynamicVertexBuffer(DynamicVertexBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyDynamicVertexBuffer(_handle);
	}

	bool checkAvailTransientIndexBuffer(uint32_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 < _num, "Requesting 0 indices.");
		return s_ctx->checkAvailTransientIndexBuffer(_num);
	}

	bool checkAvailTransientVertexBuffer(uint32_t _num, const VertexDecl& _decl)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 < _num, "Requesting 0 vertices.");
		BX_CHECK(0 != _decl.m_stride, "Invalid VertexDecl.");
		return s_ctx->checkAvailTransientVertexBuffer(_num, _decl.m_stride);
	}

	bool checkAvailInstanceDataBuffer(uint32_t _num, uint16_t _stride)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 < _num, "Requesting 0 instances.");
		return s_ctx->checkAvailTransientVertexBuffer(_num, _stride);
	}

	bool checkAvailTransientBuffers(uint32_t _numVertices, const VertexDecl& _decl, uint32_t _numIndices)
	{
		BX_CHECK(0 != _decl.m_stride, "Invalid VertexDecl.");
		return checkAvailTransientVertexBuffer(_numVertices, _decl)
			&& checkAvailTransientIndexBuffer(_numIndices)
			;
	}

	void allocTransientIndexBuffer(TransientIndexBuffer* _tib, uint32_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _tib, "_tib can't be NULL");
		BX_CHECK(0 < _num, "Requesting 0 indices.");
		return s_ctx->allocTransientIndexBuffer(_tib, _num);
	}

	void allocTransientVertexBuffer(TransientVertexBuffer* _tvb, uint32_t _num, const VertexDecl& _decl)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _tvb, "_tvb can't be NULL");
		BX_CHECK(0 < _num, "Requesting 0 vertices.");
		BX_CHECK(UINT16_MAX >= _num, "Requesting %d vertices (max: %d).", _num, UINT16_MAX);
		BX_CHECK(0 != _decl.m_stride, "Invalid VertexDecl.");
		return s_ctx->allocTransientVertexBuffer(_tvb, _num, _decl);
	}

	const InstanceDataBuffer* allocInstanceDataBuffer(uint32_t _num, uint16_t _stride)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 != (g_caps.supported & BGFX_CAPS_INSTANCING), "Instancing is not supported! Use bgfx::getCaps to check backend renderer capabilities.");
		BX_CHECK(0 < _num, "Requesting 0 instanced data vertices.");
		return s_ctx->allocInstanceDataBuffer(_num, _stride);
	}

	VertexShaderHandle createVertexShader(const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createVertexShader(_mem);
	}

	void destroyVertexShader(VertexShaderHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyVertexShader(_handle);
	}

	FragmentShaderHandle createFragmentShader(const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createFragmentShader(_mem);
	}

	void destroyFragmentShader(FragmentShaderHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyFragmentShader(_handle);
	}

	ProgramHandle createProgram(VertexShaderHandle _vsh, FragmentShaderHandle _fsh)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->createProgram(_vsh, _fsh);
	}

	void destroyProgram(ProgramHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyProgram(_handle);
	}

	void calcTextureSize(TextureInfo& _info, uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, TextureFormat::Enum _format)
	{
		_width   = bx::uint32_max(1, _width);
		_height  = bx::uint32_max(1, _height);
		_depth   = bx::uint32_max(1, _depth);
		_numMips = bx::uint32_max(1, _numMips);

		uint32_t width = _width;
		uint32_t height = _height;
		uint32_t depth = _depth;

		uint32_t bpp = getBitsPerPixel(_format);
		uint32_t size = 0;

		for (uint32_t lod = 0; lod < _numMips; ++lod)
		{
			width  = bx::uint32_max(1, width);
			height = bx::uint32_max(1, height);
			depth  = bx::uint32_max(1, depth);

			size += _width*_height*depth*bpp/8;

			width >>= 1;
			height >>= 1;
			depth >>= 1;
		}

		_info.format = _format;
		_info.storageSize = size;
		_info.width = _width;
		_info.height = _height;
		_info.depth = _depth;
		_info.numMips = _numMips;
		_info.bitsPerPixel = bpp;
	}

	TextureHandle createTexture(const Memory* _mem, uint32_t _flags, TextureInfo* _info)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createTexture(_mem, _flags, _info);
	}

	TextureHandle createTexture2D(uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();

#if BGFX_CONFIG_DEBUG
		if (NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _width, _height, 1, _numMips, _format);
			BX_CHECK(ti.storageSize == _mem->size
				, "createTexture2D: Texture storage size doesn't match passed memory size (storage size: %d, memory size: %d)"
				, ti.storageSize
				, _mem->size
				);
		}
#endif // BGFX_CONFIG_DEBUG

		uint32_t size = sizeof(uint32_t)+sizeof(TextureCreate);
		const Memory* mem = alloc(size);

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic);

		TextureCreate tc;
		tc.m_flags = _flags;
		tc.m_width = _width;
		tc.m_height = _height;
		tc.m_sides = 0;
		tc.m_depth = 0;
		tc.m_numMips = _numMips;
		tc.m_format = uint8_t(_format);
		tc.m_cubeMap = false;
		tc.m_mem = _mem;
		bx::write(&writer, tc);

		return s_ctx->createTexture(mem, _flags, NULL);
	}

	TextureHandle createTexture3D(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 != (g_caps.supported & BGFX_CAPS_TEXTURE_3D), "Texture3D is not supported! Use bgfx::getCaps to check backend renderer capabilities.");

#if BGFX_CONFIG_DEBUG
		if (NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _width, _height, _depth, _numMips, _format);
			BX_CHECK(ti.storageSize == _mem->size
				, "createTexture3D: Texture storage size doesn't match passed memory size (storage size: %d, memory size: %d)"
				, ti.storageSize
				, _mem->size
				);
		}
#endif // BGFX_CONFIG_DEBUG

		uint32_t size = sizeof(uint32_t)+sizeof(TextureCreate);
		const Memory* mem = alloc(size);

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic);

		TextureCreate tc;
		tc.m_flags = _flags;
		tc.m_width = _width;
		tc.m_height = _height;
		tc.m_sides = 0;
		tc.m_depth = _depth;
		tc.m_numMips = _numMips;
		tc.m_format = uint8_t(_format);
		tc.m_cubeMap = false;
		tc.m_mem = _mem;
		bx::write(&writer, tc);

		return s_ctx->createTexture(mem, _flags, NULL);
	}

	TextureHandle createTextureCube(uint16_t _size, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();

#if BGFX_CONFIG_DEBUG
		if (NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _size, _size, 1, _numMips, _format);
			BX_CHECK(ti.storageSize*6 == _mem->size
				, "createTextureCube: Texture storage size doesn't match passed memory size (storage size: %d, memory size: %d)"
				, ti.storageSize*6
				, _mem->size
				);
		}
#endif // BGFX_CONFIG_DEBUG

		uint32_t size = sizeof(uint32_t)+sizeof(TextureCreate);
		const Memory* mem = alloc(size);

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic);

		TextureCreate tc;
		tc.m_flags = _flags;
		tc.m_width = _size;
		tc.m_height = _size;
		tc.m_sides = 6;
		tc.m_depth = 0;
		tc.m_numMips = _numMips;
		tc.m_format = uint8_t(_format);
		tc.m_cubeMap = true;
		tc.m_mem = _mem;
		bx::write(&writer, tc);

		return s_ctx->createTexture(mem, _flags, NULL);
	}

	void destroyTexture(TextureHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyTexture(_handle);
	}

	void updateTexture2D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem, uint16_t _pitch)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		if (_width == 0
		||  _height == 0)
		{
			release(_mem);
		}
		else
		{
			s_ctx->updateTexture(_handle, 0, _mip, _x, _y, 0, _width, _height, 1, _pitch, _mem);
		}
	}

	void updateTexture3D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		if (_width == 0
		||  _height == 0
		||  _depth == 0)
		{
			release(_mem);
		}
		else
		{
			s_ctx->updateTexture(_handle, 0, _mip, _x, _y, _z, _width, _height, _depth, UINT16_MAX, _mem);
		}
	}

	void updateTextureCube(TextureHandle _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem, uint16_t _pitch)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		BX_CHECK(_side <= 5, "Invalid side %d.", _side);
		if (_width == 0
		||  _height == 0)
		{
			release(_mem);
		}
		else
		{
			s_ctx->updateTexture(_handle, _side, _mip, _x, _y, 0, _width, _height, 1, _pitch, _mem);
		}
	}

	RenderTargetHandle createRenderTarget(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_WARN(0 != _width && 0 != _height, "Render target resolution width or height cannot be 0 (width %d, height %d).", _width, _height);
		return s_ctx->createRenderTarget(bx::uint16_max(1, _width), bx::uint16_max(1, _height), _flags, _textureFlags);
	}

	void destroyRenderTarget(RenderTargetHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyRenderTarget(_handle);
	}

	UniformHandle createUniform(const char* _name, UniformType::Enum _type, uint16_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->createUniform(_name, _type, _num);
	}

	void destroyUniform(UniformHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyUniform(_handle);
	}

	void setViewName(uint8_t _id, const char* _name)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewName(_id, _name);
	}

	void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewRect(_id, _x, _y, _width, _height);
	}

	void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewRectMask(_viewMask, _x, _y, _width, _height);
	}

	void setViewScissor(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewScissor(_id, _x, _y, _width, _height);
	}

	void setViewScissorMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewScissorMask(_viewMask, _x, _y, _width, _height);
	}

	void setViewClear(uint8_t _id, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewClear(_id, _flags, _rgba, _depth, _stencil);
	}

	void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewClearMask(_viewMask, _flags, _rgba, _depth, _stencil);
	}

	void setViewSeq(uint8_t _id, bool _enabled)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewSeq(_id, _enabled);
	}

	void setViewSeqMask(uint32_t _viewMask, bool _enabled)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewSeqMask(_viewMask, _enabled);
	}

	void setViewRenderTarget(uint8_t _id, RenderTargetHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewRenderTarget(_id, _handle);
	}

	void setViewRenderTargetMask(uint32_t _mask, RenderTargetHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewRenderTargetMask(_mask, _handle);
	}

	void setViewTransform(uint8_t _id, const void* _view, const void* _proj, uint8_t _other)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewTransform(_id, _view, _proj, _other);
	}

	void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj, uint8_t _other)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setViewTransformMask(_viewMask, _view, _proj, _other);
	}

	void setMarker(const char* _marker)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setMarker(_marker);
	}

	void setState(uint64_t _state, uint32_t _rgba)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setState(_state, _rgba);
	}

	void setStencil(uint32_t _fstencil, uint32_t _bstencil)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setStencil(_fstencil, _bstencil);
	}

	uint16_t setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->setScissor(_x, _y, _width, _height);
	}

	void setScissor(uint16_t _cache)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setScissor(_cache);
	}

	uint32_t setTransform(const void* _mtx, uint16_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->setTransform(_mtx, _num);
	}

	void setTransform(uint32_t _cache, uint16_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setTransform(_cache, _num);
	}

	void setUniform(UniformHandle _handle, const void* _value, uint16_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setUniform(_handle, _value, _num);
	}

	void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setIndexBuffer(_handle, _firstIndex, _numIndices);
	}

	void setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setIndexBuffer(_handle, _firstIndex, _numIndices);
	}

	void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _numIndices)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _tib, "_tib can't be NULL");
		uint32_t numIndices = bx::uint32_min(_numIndices, _tib->size/2);
		s_ctx->setIndexBuffer(_tib, numIndices);
	}

	void setVertexBuffer(VertexBufferHandle _handle, uint32_t _numVertices)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setVertexBuffer(_handle, _numVertices);
	}

	void setVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _numVertices)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setVertexBuffer(_handle, _numVertices);
	}

	void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _numVertices)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _tvb, "_tvb can't be NULL");
		s_ctx->setVertexBuffer(_tvb, _numVertices);
	}

	void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint16_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setInstanceDataBuffer(_idb, _num);
	}

	void setProgram(ProgramHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setProgram(_handle);
	}

	void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setTexture(_stage, _sampler, _handle, _flags);
	}

	void setTexture(uint8_t _stage, UniformHandle _sampler, RenderTargetHandle _handle, bool _depth, uint32_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setTexture(_stage, _sampler, _handle, _depth, _flags);
	}

	uint32_t submit(uint8_t _id, int32_t _depth)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->submit(_id, _depth);
	}

	uint32_t submitMask(uint32_t _viewMask, int32_t _depth)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->submitMask(_viewMask, _depth);
	}

	void discard()
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->discard();
	}

	void saveScreenShot(const char* _filePath)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->saveScreenShot(_filePath);
	}
}
