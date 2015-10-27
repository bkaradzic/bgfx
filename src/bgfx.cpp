/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

namespace bgfx
{
#define BGFX_MAIN_THREAD_MAGIC UINT32_C(0x78666762)

#if BGFX_CONFIG_MULTITHREADED
#	define BGFX_CHECK_MAIN_THREAD() \
				BX_CHECK(NULL != s_ctx, "Library is not initialized yet."); \
				BX_CHECK(BGFX_MAIN_THREAD_MAGIC == s_threadIndex, "Must be called from main thread.")
#	define BGFX_CHECK_RENDER_THREAD() BX_CHECK(BGFX_MAIN_THREAD_MAGIC != s_threadIndex, "Must be called from render thread.")
#else
#	define BGFX_CHECK_MAIN_THREAD()
#	define BGFX_CHECK_RENDER_THREAD()
#endif // BGFX_CONFIG_MULTITHREADED

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

		virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) BX_OVERRIDE
		{
			char temp[2048];
			char* out = temp;
			int32_t len   = bx::snprintf(out, sizeof(temp), "%s (%d): ", _filePath, _line);
			int32_t total = len + bx::vsnprintf(out + len, sizeof(temp)-len, _format, _argList);
			if ( (int32_t)sizeof(temp) < total)
			{
				out = (char*)alloca(total+1);
				memcpy(out, temp, len);
				bx::vsnprintf(out + len, total-len, _format, _argList);
			}
			out[total] = '\0';
			bx::debugOutput(out);
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

#ifndef BGFX_CONFIG_MEMORY_TRACKING
#	define BGFX_CONFIG_MEMORY_TRACKING (BGFX_CONFIG_DEBUG && BX_CONFIG_SUPPORTS_THREADING)
#endif // BGFX_CONFIG_MEMORY_TRACKING

	class AllocatorStub : public bx::ReallocatorI
	{
	public:
		AllocatorStub()
#if BGFX_CONFIG_MEMORY_TRACKING
			: m_numBlocks(0)
			, m_maxBlocks(0)
#endif // BGFX_CONFIG_MEMORY_TRACKING
		{
		}

		virtual void* alloc(size_t _size, size_t _align, const char* _file, uint32_t _line) BX_OVERRIDE
		{
			if (BX_CONFIG_ALLOCATOR_NATURAL_ALIGNMENT >= _align)
			{
#if BGFX_CONFIG_MEMORY_TRACKING
				{
					bx::LwMutexScope scope(m_mutex);
					++m_numBlocks;
					m_maxBlocks = bx::uint32_max(m_maxBlocks, m_numBlocks);
				}
#endif // BGFX_CONFIG_MEMORY_TRACKING

				return ::malloc(_size);
			}

			return bx::alignedAlloc(this, _size, _align, _file, _line);
		}

		virtual void free(void* _ptr, size_t _align, const char* _file, uint32_t _line) BX_OVERRIDE
		{
			if (NULL != _ptr)
			{
				if (BX_CONFIG_ALLOCATOR_NATURAL_ALIGNMENT >= _align)
				{
#if BGFX_CONFIG_MEMORY_TRACKING
					{
						bx::LwMutexScope scope(m_mutex);
						BX_CHECK(m_numBlocks > 0, "Number of blocks is 0. Possible alloc/free mismatch?");
						--m_numBlocks;
					}
#endif // BGFX_CONFIG_MEMORY_TRACKING

					::free(_ptr);
				}
				else
				{
					bx::alignedFree(this, _ptr, _align, _file, _line);
				}
			}
		}

		virtual void* realloc(void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line) BX_OVERRIDE
		{
			if (BX_CONFIG_ALLOCATOR_NATURAL_ALIGNMENT >= _align)
			{
#if BGFX_CONFIG_MEMORY_TRACKING
				if (NULL == _ptr)
				{
					bx::LwMutexScope scope(m_mutex);
					++m_numBlocks;
					m_maxBlocks = bx::uint32_max(m_maxBlocks, m_numBlocks);
				}
#endif // BGFX_CONFIG_MEMORY_TRACKING

				return ::realloc(_ptr, _size);
			}

			return bx::alignedRealloc(this, _ptr, _size, _align, _file, _line);
		}

		void checkLeaks();

	protected:
#if BGFX_CONFIG_MEMORY_TRACKING
		bx::LwMutex m_mutex;
		uint32_t m_numBlocks;
		uint32_t m_maxBlocks;
#endif // BGFX_CONFIG_MEMORY_TRACKING
	};

	static CallbackStub*  s_callbackStub  = NULL;
	static AllocatorStub* s_allocatorStub = NULL;
	static bool s_graphicsDebuggerPresent = false;

	CallbackI* g_callback = NULL;
	bx::ReallocatorI* g_allocator = NULL;

	Caps g_caps;

#if BGFX_CONFIG_MULTITHREADED && !defined(BX_THREAD_LOCAL)
	class ThreadData
	{
		BX_CLASS(ThreadData
			, NO_COPY
			, NO_ASSIGNMENT
			);

	public:
		ThreadData(uintptr_t _rhs)
		{
			union { uintptr_t ui; void* ptr; } cast = { _rhs };
			m_tls.set(cast.ptr);
		}

		operator uintptr_t() const
		{
			union { uintptr_t ui; void* ptr; } cast;
			cast.ptr = m_tls.get();
			return cast.ui;
		}

		uintptr_t operator=(uintptr_t _rhs)
		{
			union { uintptr_t ui; void* ptr; } cast = { _rhs };
			m_tls.set(cast.ptr);
			return _rhs;
		}

		bool operator==(uintptr_t _rhs) const
		{
			uintptr_t lhs = *this;
			return lhs == _rhs;
		}

	private:
		bx::TlsData m_tls;
	};

	static ThreadData s_threadIndex(0);
#elif !BGFX_CONFIG_MULTITHREADED
	static uint32_t s_threadIndex(0);
#else
	static BX_THREAD_LOCAL uint32_t s_threadIndex(0);
#endif

	static Context* s_ctx = NULL;
	static bool s_renderFrameCalled = false;
	PlatformData g_platformData;

	void AllocatorStub::checkLeaks()
	{
#if BGFX_CONFIG_MEMORY_TRACKING
		// BK - CallbackStub will be deleted after printing this info, so there is always one
		// leak if CallbackStub is used.
		BX_WARN(uint32_t(NULL != s_callbackStub ? 1 : 0) == m_numBlocks
			, "MEMORY LEAK: %d (max: %d)"
			, m_numBlocks
			, m_maxBlocks
			);
#endif // BGFX_CONFIG_MEMORY_TRACKING
	}

	void setPlatformData(const PlatformData& _pd)
	{
		if (NULL != s_ctx)
		{
			BGFX_FATAL(true
				&& g_platformData.ndt     == _pd.ndt
				&& g_platformData.nwh     == _pd.nwh
				&& g_platformData.context == _pd.context
				, Fatal::UnableToInitialize
				, "Only backbuffer pointer can be changed after initialization!"
				);
		}
		memcpy(&g_platformData, &_pd, sizeof(PlatformData) );
	}

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
		char* out = temp;
		int32_t len = bx::vsnprintf(out, sizeof(temp), _format, argList);
		if ( (int32_t)sizeof(temp) < len)
		{
			out = (char*)alloca(len+1);
			len = bx::vsnprintf(out, len, _format, argList);
		}
		out[len] = '\0';
		va_end(argList);

		g_callback->fatal(_code, out);
	}

	void trace(const char* _filePath, uint16_t _line, const char* _format, ...)
	{
		va_list argList;
		va_start(argList, _format);
		g_callback->traceVargs(_filePath, _line, _format, argList);
		va_end(argList);

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
		m_decl
			.begin()
			.add(Attrib::Position,  3, AttribType::Float)
			.add(Attrib::Color0,    4, AttribType::Uint8, true)
			.add(Attrib::Color1,    4, AttribType::Uint8, true)
			.add(Attrib::TexCoord0, 2, AttribType::Float)
			.end();

		uint16_t width = 2048;
		uint16_t height = 24;
		uint8_t bpp = 1;
		uint32_t pitch = width*bpp;

		const Memory* mem;

		mem = alloc(pitch*height);
		uint8_t* rgba = mem->data;
		charsetFillTexture(vga8x8, rgba, 8, pitch, bpp);
		charsetFillTexture(vga8x16, &rgba[8*pitch], 16, pitch, bpp);
		m_texture = createTexture2D(width, height, 1, TextureFormat::R8
						, BGFX_TEXTURE_MIN_POINT
						| BGFX_TEXTURE_MAG_POINT
						| BGFX_TEXTURE_MIP_POINT
						| BGFX_TEXTURE_U_CLAMP
						| BGFX_TEXTURE_V_CLAMP
						, mem
						);

		switch (g_caps.rendererType)
		{
		case RendererType::Direct3D9:
			mem = makeRef(vs_debugfont_dx9, sizeof(vs_debugfont_dx9) );
			break;

		case RendererType::Direct3D11:
		case RendererType::Direct3D12:
			mem = makeRef(vs_debugfont_dx11, sizeof(vs_debugfont_dx11) );
			break;

		case RendererType::Metal:
			mem = makeRef(vs_debugfont_mtl, sizeof(vs_debugfont_mtl) );
			break;

		default:
			mem = makeRef(vs_debugfont_glsl, sizeof(vs_debugfont_glsl) );
			break;
		}

		ShaderHandle vsh = createShader(mem);

		switch (g_caps.rendererType)
		{
		case RendererType::Direct3D9:
			mem = makeRef(fs_debugfont_dx9, sizeof(fs_debugfont_dx9) );
			break;

		case RendererType::Direct3D11:
		case RendererType::Direct3D12:
			mem = makeRef(fs_debugfont_dx11, sizeof(fs_debugfont_dx11) );
			break;

		case RendererType::Metal:
			mem = makeRef(fs_debugfont_mtl, sizeof(fs_debugfont_mtl) );
			break;

		default:
			mem = makeRef(fs_debugfont_glsl, sizeof(fs_debugfont_glsl) );
			break;
		}

		ShaderHandle fsh = createShader(mem);

		m_program = createProgram(vsh, fsh, true);

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

	void blit(RendererContextI* _renderCtx, TextVideoMemBlitter& _blitter, const TextVideoMem& _mem)
	{
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
		const float texelWidthHalf = RendererType::Direct3D9 == g_caps.rendererType ? 0.0f : texelWidth*0.5f;
		const float texelHeight = 1.0f/24.0f;
		const float texelHeightHalf = RendererType::Direct3D9 == g_caps.rendererType ? texelHeight*0.5f : 0.0f;
		const float utop = (_mem.m_small ? 0.0f : 8.0f)*texelHeight + texelHeightHalf;
		const float ubottom = (_mem.m_small ? 8.0f : 24.0f)*texelHeight + texelHeightHalf;
		const float fontHeight = (_mem.m_small ? 8.0f : 16.0f);

		_renderCtx->blitSetup(_blitter);

		for (;yy < _mem.m_height;)
		{
			Vertex* vertex = (Vertex*)_blitter.m_vb->data;
			uint16_t* indices = (uint16_t*)_blitter.m_ib->data;
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

						indices[0] = uint16_t(startVertex+0);
						indices[1] = uint16_t(startVertex+1);
						indices[2] = uint16_t(startVertex+2);
						indices[3] = uint16_t(startVertex+2);
						indices[4] = uint16_t(startVertex+3);
						indices[5] = uint16_t(startVertex+0);

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

			_renderCtx->blitRender(_blitter, numIndices);
		}
	}

	void ClearQuad::init()
	{
		BGFX_CHECK_MAIN_THREAD();

		if (RendererType::Null != g_caps.rendererType)
		{
			m_decl
				.begin()
				.add(Attrib::Position, 3, AttribType::Float)
				.end();

			ShaderHandle vsh = BGFX_INVALID_HANDLE;

			struct Mem
			{
				Mem(const void* _data, size_t _size)
					: data(_data)
					, size(_size)
				{
				}

				const void*  data;
				size_t size;
			};

			const Memory* fragMem[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			if (RendererType::Direct3D9 == g_caps.rendererType)
			{
				vsh = createShader(makeRef(vs_clear_dx9, sizeof(vs_clear_dx9) ) );

				const Mem mem[] =
				{
					Mem(fs_clear0_dx9, sizeof(fs_clear0_dx9) ),
					Mem(fs_clear1_dx9, sizeof(fs_clear1_dx9) ),
					Mem(fs_clear2_dx9, sizeof(fs_clear2_dx9) ),
					Mem(fs_clear3_dx9, sizeof(fs_clear3_dx9) ),
					Mem(fs_clear4_dx9, sizeof(fs_clear4_dx9) ),
					Mem(fs_clear5_dx9, sizeof(fs_clear5_dx9) ),
					Mem(fs_clear6_dx9, sizeof(fs_clear6_dx9) ),
					Mem(fs_clear7_dx9, sizeof(fs_clear7_dx9) ),
				};

				for (uint32_t ii = 0, num = g_caps.maxFBAttachments; ii < num; ++ii)
				{
					fragMem[ii] = makeRef(mem[ii].data, uint32_t(mem[ii].size) );
				}
			}
			else if (RendererType::Direct3D11 == g_caps.rendererType
				 ||  RendererType::Direct3D12 == g_caps.rendererType)
			{
				vsh = createShader(makeRef(vs_clear_dx11, sizeof(vs_clear_dx11) ) );

				const Mem mem[] =
				{
					Mem(fs_clear0_dx11, sizeof(fs_clear0_dx11) ),
					Mem(fs_clear1_dx11, sizeof(fs_clear1_dx11) ),
					Mem(fs_clear2_dx11, sizeof(fs_clear2_dx11) ),
					Mem(fs_clear3_dx11, sizeof(fs_clear3_dx11) ),
					Mem(fs_clear4_dx11, sizeof(fs_clear4_dx11) ),
					Mem(fs_clear5_dx11, sizeof(fs_clear5_dx11) ),
					Mem(fs_clear6_dx11, sizeof(fs_clear6_dx11) ),
					Mem(fs_clear7_dx11, sizeof(fs_clear7_dx11) ),
				};

				for (uint32_t ii = 0, num = g_caps.maxFBAttachments; ii < num; ++ii)
				{
					fragMem[ii] = makeRef(mem[ii].data, uint32_t(mem[ii].size) );
				}
			}
			else if (RendererType::OpenGLES == g_caps.rendererType
				 ||  RendererType::OpenGL   == g_caps.rendererType)
			{
				vsh = createShader(makeRef(vs_clear_glsl, sizeof(vs_clear_glsl) ) );

				const Mem mem[] =
				{
					Mem(fs_clear0_glsl, sizeof(fs_clear0_glsl) ),
					Mem(fs_clear1_glsl, sizeof(fs_clear1_glsl) ),
					Mem(fs_clear2_glsl, sizeof(fs_clear2_glsl) ),
					Mem(fs_clear3_glsl, sizeof(fs_clear3_glsl) ),
					Mem(fs_clear4_glsl, sizeof(fs_clear4_glsl) ),
					Mem(fs_clear5_glsl, sizeof(fs_clear5_glsl) ),
					Mem(fs_clear6_glsl, sizeof(fs_clear6_glsl) ),
					Mem(fs_clear7_glsl, sizeof(fs_clear7_glsl) ),
				};

				for (uint32_t ii = 0, num = g_caps.maxFBAttachments; ii < num; ++ii)
				{
					fragMem[ii] = makeRef(mem[ii].data, uint32_t(mem[ii].size) );
				}
			}
			else if (RendererType::Metal == g_caps.rendererType)
			{
				vsh = createShader(makeRef(vs_clear_mtl, sizeof(vs_clear_mtl) ) );

				const Mem mem[] =
				{
					Mem(fs_clear0_mtl, sizeof(fs_clear0_mtl) ),
					Mem(fs_clear1_mtl, sizeof(fs_clear1_mtl) ),
					Mem(fs_clear2_mtl, sizeof(fs_clear2_mtl) ),
					Mem(fs_clear3_mtl, sizeof(fs_clear3_mtl) ),
					Mem(fs_clear4_mtl, sizeof(fs_clear4_mtl) ),
					Mem(fs_clear5_mtl, sizeof(fs_clear5_mtl) ),
					Mem(fs_clear6_mtl, sizeof(fs_clear6_mtl) ),
					Mem(fs_clear7_mtl, sizeof(fs_clear7_mtl) ),
				};

				for (uint32_t ii = 0, num = g_caps.maxFBAttachments; ii < num; ++ii)
				{
					fragMem[ii] = makeRef(mem[ii].data, uint32_t(mem[ii].size) );
				}
			}
			else
			{
				BGFX_FATAL(false, Fatal::UnableToInitialize, "Unknown renderer type %d", g_caps.rendererType);
			}

			for (uint32_t ii = 0, num = g_caps.maxFBAttachments; ii < num; ++ii)
			{
				ShaderHandle fsh = createShader(fragMem[ii]);
				m_program[ii] = createProgram(vsh, fsh);
				BX_CHECK(isValid(m_program[ii]), "Failed to create clear quad program.");
				destroyShader(fsh);
			}

			destroyShader(vsh);

			m_vb = s_ctx->createTransientVertexBuffer(4*m_decl.m_stride, &m_decl);
		}
	}

	void ClearQuad::shutdown()
	{
		BGFX_CHECK_MAIN_THREAD();

		if (RendererType::Null != g_caps.rendererType)
		{
			for (uint32_t ii = 0, num = g_caps.maxFBAttachments; ii < num; ++ii)
			{
				if (isValid(m_program[ii]) )
				{
					destroyProgram(m_program[ii]);
					m_program[ii].idx = invalidHandle;
				}
			}

			s_ctx->destroyTransientVertexBuffer(m_vb);
		}
	}

	const char* s_uniformTypeName[] =
	{
		"int1",
		NULL,
		"vec4",
		"mat3",
		"mat4",
	};
	BX_STATIC_ASSERT(UniformType::Count == BX_COUNTOF(s_uniformTypeName) );

	const char* getUniformTypeName(UniformType::Enum _enum)
	{
		BX_CHECK(_enum < UniformType::Count, "%d < UniformType::Count %d", _enum, UniformType::Count);
		return s_uniformTypeName[_enum];
	}

	UniformType::Enum nameToUniformTypeEnum(const char* _name)
	{
		for (uint32_t ii = 0; ii < UniformType::Count; ++ii)
		{
			if (NULL != s_uniformTypeName[ii]
			&&  0 == strcmp(_name, s_uniformTypeName[ii]) )
			{
				return UniformType::Enum(ii);
			}
		}

		return UniformType::Count;
	}

	static const char* s_predefinedName[PredefinedUniform::Count] =
	{
		"u_viewRect",
		"u_viewTexel",
		"u_view",
		"u_invView",
		"u_proj",
		"u_invProj",
		"u_viewProj",
		"u_invViewProj",
		"u_model",
		"u_modelView",
		"u_modelViewProj",
		"u_alphaRef4",
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

	uint32_t Frame::submit(uint8_t _id, ProgramHandle _handle, int32_t _depth)
	{
		if (m_discard)
		{
			discard();
			return m_num;
		}

		if (BGFX_CONFIG_MAX_DRAW_CALLS-1 <= m_num
		|| (0 == m_draw.m_numVertices && 0 == m_draw.m_numIndices) )
		{
			++m_numDropped;
			return m_num;
		}

		m_uniformEnd = m_uniformBuffer->getPos();

		m_key.m_program = invalidHandle == _handle.idx
			? 0
			: _handle.idx
			;

		m_key.m_depth  = (uint32_t)_depth;
		m_key.m_view   = _id;
		m_key.m_seq    = s_ctx->m_seq[_id] & s_ctx->m_seqMask[_id];
		s_ctx->m_seq[_id]++;

		uint64_t key = m_key.encodeDraw();
		m_sortKeys[m_num]   = key;
		m_sortValues[m_num] = m_numRenderItems;
		++m_num;

		m_draw.m_constBegin = m_uniformBegin;
		m_draw.m_constEnd   = m_uniformEnd;
		m_draw.m_flags |= m_flags;
		m_renderItem[m_numRenderItems].draw = m_draw;
		++m_numRenderItems;

		m_draw.clear();
		m_uniformBegin = m_uniformEnd;
		m_flags = BGFX_STATE_NONE;

		return m_num;
	}

	uint32_t Frame::dispatch(uint8_t _id, ProgramHandle _handle, uint16_t _numX, uint16_t _numY, uint16_t _numZ, uint8_t _flags)
	{
		if (m_discard)
		{
			discard();
			return m_num;
		}

		if (BGFX_CONFIG_MAX_DRAW_CALLS-1 <= m_num)
		{
			++m_numDropped;
			return m_num;
		}

		m_uniformEnd = m_uniformBuffer->getPos();

		m_compute.m_matrix = m_draw.m_matrix;
		m_compute.m_num    = m_draw.m_num;
		m_compute.m_numX   = bx::uint16_max(_numX, 1);
		m_compute.m_numY   = bx::uint16_max(_numY, 1);
		m_compute.m_numZ   = bx::uint16_max(_numZ, 1);
		m_compute.m_submitFlags = _flags;

		m_key.m_program = _handle.idx;
		m_key.m_depth   = 0;
		m_key.m_view    = _id;
		m_key.m_seq     = s_ctx->m_seq[_id];
		s_ctx->m_seq[_id]++;

		uint64_t key = m_key.encodeCompute();
		m_sortKeys[m_num]   = key;
		m_sortValues[m_num] = m_numRenderItems;
		++m_num;

		m_compute.m_constBegin = m_uniformBegin;
		m_compute.m_constEnd   = m_uniformEnd;
		m_renderItem[m_numRenderItems].compute = m_compute;
		++m_numRenderItems;

		m_compute.clear();
		m_uniformBegin = m_uniformEnd;

		return m_num;
	}

	void Frame::blit(uint8_t _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
	{
		uint16_t item = m_numBlitItems++;

		BlitItem& bi = m_blitItem[item];
		bi.m_srcX    = _srcX;
		bi.m_srcY    = _srcY;
		bi.m_srcZ    = _srcZ;
		bi.m_dstX    = _dstX;
		bi.m_dstY    = _dstY;
		bi.m_dstZ    = _dstZ;
		bi.m_width   = _width;
		bi.m_height  = _height;
		bi.m_depth   = _depth;
		bi.m_srcMip  = _srcMip;
		bi.m_dstMip  = _dstMip;
		bi.m_src     = _src;
		bi.m_dst     = _dst;

		BlitKey key;
		key.m_view = _id;
		key.m_item = item;
		m_blitKeys[item] = key.encode();
	}

	void Frame::sort()
	{
		for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
		{
			m_sortKeys[ii] = SortKey::remapView(m_sortKeys[ii], m_viewRemap);
		}
		bx::radixSort64(m_sortKeys, s_ctx->m_tempKeys, m_sortValues, s_ctx->m_tempValues, m_num);

		for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
		{
			m_blitKeys[ii] = BlitKey::remapView(m_blitKeys[ii], m_viewRemap);
		}
		bx::radixSort32(m_blitKeys, (uint32_t*)&s_ctx->m_tempKeys, m_numBlitItems);
	}

	RenderFrame::Enum renderFrame()
	{
		if (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) )
		{
			if (NULL == s_ctx)
			{
				s_renderFrameCalled = true;
				s_threadIndex = ~BGFX_MAIN_THREAD_MAGIC;
				return RenderFrame::NoContext;
			}

			BGFX_CHECK_RENDER_THREAD();
			if (s_ctx->renderFrame() )
			{
				Context* ctx = s_ctx;
				ctx->gameSemWait();
				s_ctx = NULL;
				ctx->renderSemPost();
				return RenderFrame::Exiting;
			}

			return RenderFrame::Render;
		}

		BX_CHECK(false, "This call only makes sense if used with multi-threaded renderer.");
		return RenderFrame::NoContext;
	}

	const uint32_t g_uniformTypeSize[UniformType::Count+1] =
	{
		sizeof(int32_t),
		0,
		4*sizeof(float),
		3*3*sizeof(float),
		4*4*sizeof(float),
		1,
	};

	void UniformBuffer::writeUniform(UniformType::Enum _type, uint16_t _loc, const void* _value, uint16_t _num)
	{
		uint32_t opcode = encodeOpcode(_type, _loc, _num, true);
		write(opcode);
		write(_value, g_uniformTypeSize[_type]*_num);
	}

	void UniformBuffer::writeUniformHandle(UniformType::Enum _type, uint16_t _loc, UniformHandle _handle, uint16_t _num)
	{
		uint32_t opcode = encodeOpcode(_type, _loc, _num, false);
		write(opcode);
		write(&_handle, sizeof(UniformHandle) );
	}

	void UniformBuffer::writeMarker(const char* _marker)
	{
		uint16_t num = (uint16_t)strlen(_marker)+1;
		uint32_t opcode = encodeOpcode(bgfx::UniformType::Count, 0, num, true);
		write(opcode);
		write(_marker, num);
	}

	struct CapsFlags
	{
		uint64_t m_flag;
		const char* m_str;
	};

	static const CapsFlags s_capsFlags[] =
	{
#define CAPS_FLAGS(_x) { _x, #_x }
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_COMPARE_LEQUAL),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_COMPARE_ALL),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_3D),
		CAPS_FLAGS(BGFX_CAPS_VERTEX_ATTRIB_HALF),
		CAPS_FLAGS(BGFX_CAPS_VERTEX_ATTRIB_UINT10),
		CAPS_FLAGS(BGFX_CAPS_INSTANCING),
		CAPS_FLAGS(BGFX_CAPS_RENDERER_MULTITHREADED),
		CAPS_FLAGS(BGFX_CAPS_FRAGMENT_DEPTH),
		CAPS_FLAGS(BGFX_CAPS_BLEND_INDEPENDENT),
		CAPS_FLAGS(BGFX_CAPS_COMPUTE),
		CAPS_FLAGS(BGFX_CAPS_FRAGMENT_ORDERING),
		CAPS_FLAGS(BGFX_CAPS_SWAP_CHAIN),
		CAPS_FLAGS(BGFX_CAPS_HMD),
		CAPS_FLAGS(BGFX_CAPS_INDEX32),
		CAPS_FLAGS(BGFX_CAPS_DRAW_INDIRECT),
		CAPS_FLAGS(BGFX_CAPS_HIDPI),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_BLIT),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_READ_BACK),
#undef CAPS_FLAGS
	};

	static void dumpCaps()
	{
		BX_TRACE("Supported capabilities (renderer %s, vendor 0x%04x, device 0x%04x):"
				, s_ctx->m_renderCtx->getRendererName()
				, g_caps.vendorId
				, g_caps.deviceId
				);
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_capsFlags); ++ii)
		{
			if (0 != (g_caps.supported & s_capsFlags[ii].m_flag) )
			{
				BX_TRACE("\t%s", s_capsFlags[ii].m_str);
			}
		}

		BX_TRACE("Supported texture formats:");
		BX_TRACE("\t +---------------   2D: x = supported / * = emulated");
		BX_TRACE("\t |+--------------   2D: sRGB format");
		BX_TRACE("\t ||+-------------   3D: x = supported / * = emulated");
		BX_TRACE("\t |||+------------   3D: sRGB format");
		BX_TRACE("\t ||||+----------- Cube: x = supported / * = emulated");
		BX_TRACE("\t |||||+---------- Cube: sRGB format");
		BX_TRACE("\t ||||||+--------- vertex format");
		BX_TRACE("\t |||||||+-------- image");
		BX_TRACE("\t ||||||||+------- framebuffer");
		BX_TRACE("\t |||||||||+------ MSAA framebuffer");
		BX_TRACE("\t ||||||||||+----- MSAA texture");
		BX_TRACE("\t |||||||||||  +-- name");
		for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
		{
			if (TextureFormat::Unknown != ii
			&&  TextureFormat::UnknownDepth != ii)
			{
				uint16_t flags = g_caps.formats[ii];
				BX_TRACE("\t[%c%c%c%c%c%c%c%c%c%c%c] %s"
					, flags&BGFX_CAPS_FORMAT_TEXTURE_2D               ? 'x' : flags&BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED ? '*' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB          ? 'l' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_3D               ? 'x' : flags&BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED ? '*' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB          ? 'l' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_CUBE             ? 'x' : flags&BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED ? '*' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB        ? 'l' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_VERTEX           ? 'v' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_IMAGE            ? 'i' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER      ? 'f' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER_MSAA ? '+' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_MSAA             ? 'm' : ' '
					, getName(TextureFormat::Enum(ii) )
					);
				BX_UNUSED(flags);
			}
		}

		BX_TRACE("Max FB attachments: %d", g_caps.maxFBAttachments);
	}

	static TextureFormat::Enum s_emulatedFormats[] =
	{
		TextureFormat::BC1,
		TextureFormat::BC2,
		TextureFormat::BC3,
		TextureFormat::BC4,
		TextureFormat::BC5,
		TextureFormat::ETC1,
		TextureFormat::ETC2,
		TextureFormat::ETC2A,
		TextureFormat::ETC2A1,
		TextureFormat::PTC14,
		TextureFormat::PTC14A,
		TextureFormat::BGRA8, // GL doesn't support BGRA8 without extensions.
		TextureFormat::RGBA8, // D3D9 doesn't support RGBA8
	};

	bool Context::init(RendererType::Enum _type)
	{
		BX_CHECK(!m_rendererInitialized, "Already initialized?");

		m_exit   = false;
		m_frames = 0;
		m_debug  = BGFX_DEBUG_NONE;

		m_submit->create();

#if BGFX_CONFIG_MULTITHREADED
		m_render->create();

		if (s_renderFrameCalled)
		{
			// When bgfx::renderFrame is called before init render thread
			// should not be created.
			BX_TRACE("Application called bgfx::renderFrame directly, not creating render thread.");
			m_singleThreaded = true
				&& ~BGFX_MAIN_THREAD_MAGIC == s_threadIndex
				;
		}
		else
		{
			BX_TRACE("Creating rendering thread.");
			m_thread.init(renderThread, this, 0, "bgfx - renderer backend thread");
			m_singleThreaded = false;
		}
#else
		BX_TRACE("Multithreaded renderer is disabled.");
		m_singleThreaded = true;
#endif // BGFX_CONFIG_MULTITHREADED

		BX_TRACE("Running in %s-threaded mode", m_singleThreaded ? "single" : "multi");

		s_threadIndex = BGFX_MAIN_THREAD_MAGIC;

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_viewRemap); ++ii)
		{
			m_viewRemap[ii] = uint8_t(ii);
		}

		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			resetView(uint8_t(ii) );
		}

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_clearColor); ++ii)
		{
			m_clearColor[ii][0] = 0.0f;
			m_clearColor[ii][1] = 0.0f;
			m_clearColor[ii][2] = 0.0f;
			m_clearColor[ii][3] = 1.0f;
		}

		m_declRef.init();

		CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::RendererInit);
		cmdbuf.write(_type);

		frameNoRenderWait();

		// Make sure renderer init is called from render thread.
		// g_caps is initialized and available after this point.
		frame();

		if (!m_rendererInitialized)
		{
			getCommandBuffer(CommandBuffer::RendererShutdownEnd);
			frame();
			frame();
			m_declRef.shutdown(m_vertexDeclHandle);
			m_submit->destroy();
#if BGFX_CONFIG_MULTITHREADED
			m_render->destroy();
#endif // BGFX_CONFIG_MULTITHREADED
			return false;
		}

		for (uint32_t ii = 0; ii < BX_COUNTOF(s_emulatedFormats); ++ii)
		{
			const uint32_t fmt = s_emulatedFormats[ii];
			if (0 == (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_2D) )
			{
				g_caps.formats[fmt] |= BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED;
			}

			if (0 == (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_3D) )
			{
				g_caps.formats[fmt] |= BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED;
			}

			if (0 == (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_CUBE) )
			{
				g_caps.formats[fmt] |= BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED;
			}
		}

		g_caps.rendererType = m_renderCtx->getRendererType();
		initAttribTypeSizeTable(g_caps.rendererType);

		g_caps.supported |= 0
			| (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) && !m_singleThreaded ? BGFX_CAPS_RENDERER_MULTITHREADED : 0)
			;

		dumpCaps();

		m_textVideoMemBlitter.init();
		m_clearQuad.init();

		m_submit->m_transientVb = createTransientVertexBuffer(BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
		m_submit->m_transientIb = createTransientIndexBuffer(BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
		frame();

		if (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) )
		{
			m_submit->m_transientVb = createTransientVertexBuffer(BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
			m_submit->m_transientIb = createTransientIndexBuffer(BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
			frame();
		}

		return true;
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

		if (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) )
		{
			destroyTransientVertexBuffer(m_submit->m_transientVb);
			destroyTransientIndexBuffer(m_submit->m_transientIb);
			frame();
		}

		frame(); // If any VertexDecls needs to be destroyed.

		getCommandBuffer(CommandBuffer::RendererShutdownEnd);
		frame();

		m_dynVertexBufferAllocator.compact();
		m_dynIndexBufferAllocator.compact();

		m_declRef.shutdown(m_vertexDeclHandle);

#if BGFX_CONFIG_MULTITHREADED
		// Render thread shutdown sequence.
		renderSemWait(); // Wait for previous frame.
		gameSemPost();   // OK to set context to NULL.
		// s_ctx is NULL here.
		renderSemWait(); // In RenderFrame::Exiting state.

		if (m_thread.isRunning() )
		{
			m_thread.shutdown();
		}

		m_render->destroy();
#endif // BGFX_CONFIG_MULTITHREADED

		s_ctx = NULL;

		m_submit->destroy();

		if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
		{
#define CHECK_HANDLE_LEAK(_handleAlloc) \
					BX_MACRO_BLOCK_BEGIN \
						BX_WARN(0 == _handleAlloc.getNumHandles() \
							, "LEAK: " #_handleAlloc " %d (max: %d)" \
							, _handleAlloc.getNumHandles() \
							, _handleAlloc.getMaxHandles() \
							); \
					BX_MACRO_BLOCK_END

			CHECK_HANDLE_LEAK(m_dynamicIndexBufferHandle);
			CHECK_HANDLE_LEAK(m_dynamicVertexBufferHandle);
			CHECK_HANDLE_LEAK(m_indexBufferHandle);
			CHECK_HANDLE_LEAK(m_vertexDeclHandle);
			CHECK_HANDLE_LEAK(m_vertexBufferHandle);
			CHECK_HANDLE_LEAK(m_shaderHandle);
			CHECK_HANDLE_LEAK(m_programHandle);
			CHECK_HANDLE_LEAK(m_textureHandle);
			CHECK_HANDLE_LEAK(m_frameBufferHandle);
			CHECK_HANDLE_LEAK(m_uniformHandle);
#undef CHECK_HANDLE_LEAK
		}
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

		for (uint16_t ii = 0, num = _frame->m_numFreeShaderHandles; ii < num; ++ii)
		{
			m_shaderHandle.free(_frame->m_freeShaderHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeProgramHandles; ii < num; ++ii)
		{
			m_programHandle.free(_frame->m_freeProgramHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeTextureHandles; ii < num; ++ii)
		{
			m_textureHandle.free(_frame->m_freeTextureHandle[ii].idx);
		}

		for (uint16_t ii = 0, num = _frame->m_numFreeFrameBufferHandles; ii < num; ++ii)
		{
			m_frameBufferHandle.free(_frame->m_freeFrameBufferHandle[ii].idx);
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
	}

	void Context::swap()
	{
		freeDynamicBuffers();
		m_submit->m_resolution = m_resolution;
		m_resolution.m_flags &= ~BGFX_RESET_FORCE;
		m_submit->m_debug = m_debug;

		memcpy(m_submit->m_viewRemap, m_viewRemap, sizeof(m_viewRemap) );
		memcpy(m_submit->m_fb, m_fb, sizeof(m_fb) );
		memcpy(m_submit->m_clear, m_clear, sizeof(m_clear) );
		memcpy(m_submit->m_rect, m_rect, sizeof(m_rect) );
		memcpy(m_submit->m_scissor, m_scissor, sizeof(m_scissor) );
		memcpy(m_submit->m_view, m_view, sizeof(m_view) );
		memcpy(m_submit->m_proj, m_proj, sizeof(m_proj) );
		memcpy(m_submit->m_viewFlags, m_viewFlags, sizeof(m_viewFlags) );
		if (m_colorPaletteDirty > 0)
		{
			--m_colorPaletteDirty;
			memcpy(m_submit->m_colorPalette, m_clearColor, sizeof(m_clearColor) );
		}
		m_submit->finish();

		bx::xchg(m_render, m_submit);

		if (!BX_ENABLED(BGFX_CONFIG_MULTITHREADED)
		||  m_singleThreaded)
		{
			renderFrame();
		}

		m_frames++;
		m_submit->start();

		memset(m_seq, 0, sizeof(m_seq) );
		freeAllHandles(m_submit);

		m_submit->resetFreeHandles();
		m_submit->m_textVideoMem->resize(m_render->m_textVideoMem->m_small
			, m_resolution.m_width
			, m_resolution.m_height
			);
	}

	const char* Context::getName(UniformHandle _handle) const
	{
		for (UniformHashMap::const_iterator it = m_uniformHashMap.begin(), itEnd = m_uniformHashMap.end(); it != itEnd; ++it)
		{
			if (it->second.idx == _handle.idx)
			{
				return it->first.c_str();
			}
		}

		return NULL;
	}

	bool Context::renderFrame()
	{
		if (m_rendererInitialized
		&&  !m_flipAfterRender)
		{
			m_renderCtx->flip(m_render->m_hmd);
		}

		gameSemWait();

		rendererExecCommands(m_render->m_cmdPre);
		if (m_rendererInitialized)
		{
			m_renderCtx->submit(m_render, m_clearQuad, m_textVideoMemBlitter);
		}
		rendererExecCommands(m_render->m_cmdPost);

		renderSemPost();

		if (m_rendererInitialized
		&&  m_flipAfterRender)
		{
			m_renderCtx->flip(m_render->m_hmd);
		}

		return m_exit;
	}

	void rendererUpdateUniforms(RendererContextI* _renderCtx, UniformBuffer* _uniformBuffer, uint32_t _begin, uint32_t _end)
	{
		_uniformBuffer->reset(_begin);
		while (_uniformBuffer->getPos() < _end)
		{
			uint32_t opcode = _uniformBuffer->read();

			if (UniformType::End == opcode)
			{
				break;
			}

			UniformType::Enum type;
			uint16_t loc;
			uint16_t num;
			uint16_t copy;
			UniformBuffer::decodeOpcode(opcode, type, loc, num, copy);

			uint32_t size = g_uniformTypeSize[type]*num;
			const char* data = _uniformBuffer->read(size);
			if (UniformType::Count > type)
			{
				if (copy)
				{
					_renderCtx->updateUniform(loc, data, size);
				}
				else
				{
					_renderCtx->updateUniform(loc, *(const char**)(data), size);
				}
			}
			else
			{
				_renderCtx->setMarker(data, size);
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
						m_renderCtx->updateTextureEnd();
					}
					currentKey = key;
					m_renderCtx->updateTextureBegin(handle, side, mip);
				}

				m_renderCtx->updateTexture(handle, side, mip, rect, zz, depth, pitch, mem);

				release(mem);
			}

			if (currentKey != UINT32_MAX)
			{
				m_renderCtx->updateTextureEnd();
			}

			m_textureUpdateBatch.reset();

			_cmdbuf.m_pos = pos;
		}
	}

	typedef RendererContextI* (*RendererCreateFn)();
	typedef void (*RendererDestroyFn)();

#define BGFX_RENDERER_CONTEXT(_namespace) \
			namespace _namespace \
			{ \
				extern RendererContextI* rendererCreate(); \
				extern void rendererDestroy(); \
			}

	BGFX_RENDERER_CONTEXT(noop);
	BGFX_RENDERER_CONTEXT(d3d9);
	BGFX_RENDERER_CONTEXT(d3d11);
	BGFX_RENDERER_CONTEXT(d3d12);
	BGFX_RENDERER_CONTEXT(mtl);
	BGFX_RENDERER_CONTEXT(gl);
	BGFX_RENDERER_CONTEXT(vk);

#undef BGFX_RENDERER_CONTEXT

	struct RendererCreator
	{
		RendererCreateFn  createFn;
		RendererDestroyFn destroyFn;
		const char* name;
		bool supported;
	};

	static RendererCreator s_rendererCreator[] =
	{
		{ noop::rendererCreate,  noop::rendererDestroy,  BGFX_RENDERER_NULL_NAME,       !!BGFX_CONFIG_RENDERER_NULL       }, // Noop
		{ d3d9::rendererCreate,  d3d9::rendererDestroy,  BGFX_RENDERER_DIRECT3D9_NAME,  !!BGFX_CONFIG_RENDERER_DIRECT3D9  }, // Direct3D9
		{ d3d11::rendererCreate, d3d11::rendererDestroy, BGFX_RENDERER_DIRECT3D11_NAME, !!BGFX_CONFIG_RENDERER_DIRECT3D11 }, // Direct3D11
		{ d3d12::rendererCreate, d3d12::rendererDestroy, BGFX_RENDERER_DIRECT3D12_NAME, !!BGFX_CONFIG_RENDERER_DIRECT3D12 }, // Direct3D12
#if BX_PLATFORM_OSX || BX_PLATFORM_IOS
		{ mtl::rendererCreate,   mtl::rendererDestroy,   BGFX_RENDERER_METAL_NAME,      !!BGFX_CONFIG_RENDERER_METAL      }, // Metal
#else
		{ noop::rendererCreate,  noop::rendererDestroy,  BGFX_RENDERER_NULL_NAME,       !!BGFX_CONFIG_RENDERER_NULL       }, // Noop
#endif // BX_PLATFORM_OSX || BX_PLATFORM_IOS
		{ gl::rendererCreate,    gl::rendererDestroy,    BGFX_RENDERER_OPENGL_NAME,     !!BGFX_CONFIG_RENDERER_OPENGLES   }, // OpenGLES
		{ gl::rendererCreate,    gl::rendererDestroy,    BGFX_RENDERER_OPENGL_NAME,     !!BGFX_CONFIG_RENDERER_OPENGL     }, // OpenGL
		{ vk::rendererCreate,    vk::rendererDestroy,    BGFX_RENDERER_VULKAN_NAME,     !!BGFX_CONFIG_RENDERER_VULKAN     }, // Vulkan
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_rendererCreator) == RendererType::Count);

	static RendererDestroyFn s_rendererDestroyFn;

	struct Condition
	{
		enum Enum
		{
			LessEqual,
			GreaterEqual,
		};
	};

	bool windowsVersionIs(Condition::Enum _op, uint32_t _version)
	{
#if BX_PLATFORM_WINDOWS
		static const uint8_t s_condition[] =
		{
			VER_LESS_EQUAL,
			VER_GREATER_EQUAL,
		};

		OSVERSIONINFOEXA ovi;
		memset(&ovi, 0, sizeof(ovi) );
		ovi.dwOSVersionInfoSize = sizeof(ovi);
		// _WIN32_WINNT_WINBLUE 0x0603
		// _WIN32_WINNT_WIN8    0x0602
		// _WIN32_WINNT_WIN7    0x0601
		// _WIN32_WINNT_VISTA   0x0600
		ovi.dwMajorVersion = HIBYTE(_version);
		ovi.dwMinorVersion = LOBYTE(_version);
		DWORDLONG cond = 0;
		VER_SET_CONDITION(cond, VER_MAJORVERSION, s_condition[_op]);
		VER_SET_CONDITION(cond, VER_MINORVERSION, s_condition[_op]);
		return !!VerifyVersionInfoA(&ovi, VER_MAJORVERSION | VER_MINORVERSION, cond);
#else
		BX_UNUSED(_op, _version);
		return false;
#endif // BX_PLATFORM_WINDOWS
	}

	RendererContextI* rendererCreate(RendererType::Enum _type)
	{
		if (RendererType::Count == _type)
		{
again:
			if (BX_ENABLED(BX_PLATFORM_WINDOWS) )
			{
				RendererType::Enum first  = RendererType::Direct3D9;
				RendererType::Enum second = RendererType::Direct3D11;

				if (windowsVersionIs(Condition::GreaterEqual, 0x0602) )
				{
					first  = RendererType::Direct3D11;
					second = RendererType::Direct3D12;
					if (!s_rendererCreator[second].supported)
					{
						second = RendererType::Direct3D9;
					}
				}
				else if (windowsVersionIs(Condition::GreaterEqual, 0x0601) )
				{
					first  = RendererType::Direct3D11;
					second = RendererType::Direct3D9;
				}

				if (s_rendererCreator[first].supported)
				{
					_type = first;
				}
				else if (s_rendererCreator[second].supported)
				{
					_type = second;
				}
				else if (s_rendererCreator[RendererType::OpenGL].supported)
				{
					_type = RendererType::OpenGL;
				}
				else if (s_rendererCreator[RendererType::OpenGLES].supported)
				{
					_type = RendererType::OpenGLES;
				}
				else if (s_rendererCreator[RendererType::Direct3D12].supported)
				{
					_type = RendererType::Direct3D12;
				}
				else if (s_rendererCreator[RendererType::Vulkan].supported)
				{
					_type = RendererType::Vulkan;
				}
				else
				{
					_type = RendererType::Null;
				}
			}
			else if (BX_ENABLED(BX_PLATFORM_IOS) )
			{
				if (s_rendererCreator[RendererType::Metal].supported)
				{
					_type = RendererType::Metal;
				}
				else if (s_rendererCreator[RendererType::OpenGLES].supported)
				{
					_type = RendererType::OpenGLES;
				}
			}
			else if (BX_ENABLED(0
				 ||  BX_PLATFORM_ANDROID
				 ||  BX_PLATFORM_EMSCRIPTEN
				 ||  BX_PLATFORM_NACL
				 ||  BX_PLATFORM_RPI
				 ) )
			{
				_type = RendererType::OpenGLES;
			}
			else if (BX_ENABLED(BX_PLATFORM_WINRT) )
			{
				_type = RendererType::Direct3D11;
			}
			else
			{
#if 0
				if (s_rendererCreator[RendererType::Metal].supported)
				{
					_type = RendererType::Metal;
				}
				else
#endif // 0
				if (s_rendererCreator[RendererType::OpenGL].supported)
				{
					_type = RendererType::OpenGL;
				}
				else if (s_rendererCreator[RendererType::OpenGLES].supported)
				{
					_type = RendererType::OpenGLES;
				}
			}

			if (!s_rendererCreator[_type].supported)
			{
				_type = RendererType::Null;
			}
		}

		RendererContextI* renderCtx = s_rendererCreator[_type].createFn();

		if (NULL == renderCtx)
		{
			s_rendererCreator[_type].supported = false;
			goto again;
		}

		s_rendererDestroyFn = s_rendererCreator[_type].destroyFn;

		return renderCtx;
	}

	void rendererDestroy()
	{
		s_rendererDestroyFn();
	}

	void Context::rendererExecCommands(CommandBuffer& _cmdbuf)
	{
		_cmdbuf.reset();

		bool end = false;

		if (NULL == m_renderCtx)
		{
			uint8_t command;
			_cmdbuf.read(command);

			switch (command)
			{
			case CommandBuffer::RendererShutdownEnd:
				m_exit = true;
				return;

			case CommandBuffer::End:
				return;

			default:
				{
					BX_CHECK(CommandBuffer::RendererInit == command
						, "RendererInit must be the first command in command buffer before initialization. Unexpected command %d?"
						, command
						);
					BX_CHECK(!m_rendererInitialized, "This shouldn't happen! Bad synchronization?");

					RendererType::Enum type;
					_cmdbuf.read(type);

					m_renderCtx = rendererCreate(type);
					m_rendererInitialized = NULL != m_renderCtx;

					if (!m_rendererInitialized)
					{
						_cmdbuf.read(command);
						BX_CHECK(CommandBuffer::End == command, "Unexpected command %d?"
							, command
							);
						return;
					}
				}
				break;
			}
		}

		do
		{
			uint8_t command;
			_cmdbuf.read(command);

			switch (command)
			{
			case CommandBuffer::RendererShutdownBegin:
				{
					BX_CHECK(m_rendererInitialized, "This shouldn't happen! Bad synchronization?");
					m_rendererInitialized = false;
				}
				break;

			case CommandBuffer::RendererShutdownEnd:
				{
					BX_CHECK(!m_rendererInitialized && !m_exit, "This shouldn't happen! Bad synchronization?");
					rendererDestroy();
					m_renderCtx = NULL;
					m_exit = true;
				}
				// fall through

			case CommandBuffer::End:
				end = true;
				break;

			case CommandBuffer::CreateIndexBuffer:
				{
					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					Memory* mem;
					_cmdbuf.read(mem);

					uint16_t flags;
					_cmdbuf.read(flags);

					m_renderCtx->createIndexBuffer(handle, mem, flags);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyIndexBuffer:
				{
					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyIndexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateVertexDecl:
				{
					VertexDeclHandle handle;
					_cmdbuf.read(handle);

					VertexDecl decl;
					_cmdbuf.read(decl);

					m_renderCtx->createVertexDecl(handle, decl);
				}
				break;

			case CommandBuffer::DestroyVertexDecl:
				{
					VertexDeclHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyVertexDecl(handle);
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

					uint16_t flags;
					_cmdbuf.read(flags);

					m_renderCtx->createVertexBuffer(handle, mem, declHandle, flags);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyVertexBuffer:
				{
					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyVertexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateDynamicIndexBuffer:
				{
					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					uint32_t size;
					_cmdbuf.read(size);

					uint16_t flags;
					_cmdbuf.read(flags);

					m_renderCtx->createDynamicIndexBuffer(handle, size, flags);
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

					m_renderCtx->updateDynamicIndexBuffer(handle, offset, size, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyDynamicIndexBuffer:
				{
					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyDynamicIndexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateDynamicVertexBuffer:
				{
					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					uint32_t size;
					_cmdbuf.read(size);

					uint16_t flags;
					_cmdbuf.read(flags);

					m_renderCtx->createDynamicVertexBuffer(handle, size, flags);
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

					m_renderCtx->updateDynamicVertexBuffer(handle, offset, size, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyDynamicVertexBuffer:
				{
					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyDynamicVertexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateShader:
				{
					ShaderHandle handle;
					_cmdbuf.read(handle);

					Memory* mem;
					_cmdbuf.read(mem);

					m_renderCtx->createShader(handle, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyShader:
				{
					ShaderHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyShader(handle);
				}
				break;

			case CommandBuffer::CreateProgram:
				{
					ProgramHandle handle;
					_cmdbuf.read(handle);

					ShaderHandle vsh;
					_cmdbuf.read(vsh);

					ShaderHandle fsh;
					_cmdbuf.read(fsh);

					m_renderCtx->createProgram(handle, vsh, fsh);
				}
				break;

			case CommandBuffer::DestroyProgram:
				{
					ProgramHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyProgram(handle);
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

					uint8_t skip;
					_cmdbuf.read(skip);

					m_renderCtx->createTexture(handle, mem, flags, skip);

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

					_cmdbuf.skip<Rect>();
					_cmdbuf.skip<uint16_t>();
					_cmdbuf.skip<uint16_t>();
					_cmdbuf.skip<uint16_t>();
					_cmdbuf.skip<Memory*>();

					uint32_t key = (handle.idx<<16)
						| (side<<8)
						| mip
						;

					m_textureUpdateBatch.add(key, value);
				}
				break;

			case CommandBuffer::ReadTexture:
				{
					TextureHandle handle;
					_cmdbuf.read(handle);

					void* data;
					_cmdbuf.read(data);

					m_renderCtx->readTexture(handle, data);
				}
				break;

			case CommandBuffer::ResizeTexture:
				{
					TextureHandle handle;
					_cmdbuf.read(handle);

					uint16_t width;
					_cmdbuf.read(width);

					uint16_t height;
					_cmdbuf.read(height);

					m_renderCtx->resizeTexture(handle, width, height);
				}
				break;

			case CommandBuffer::DestroyTexture:
				{
					TextureHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyTexture(handle);
				}
				break;

			case CommandBuffer::CreateFrameBuffer:
				{
					FrameBufferHandle handle;
					_cmdbuf.read(handle);

					bool window;
					_cmdbuf.read(window);

					if (window)
					{
						void* nwh;
						_cmdbuf.read(nwh);

						uint16_t width;
						_cmdbuf.read(width);

						uint16_t height;
						_cmdbuf.read(height);

						TextureFormat::Enum depthFormat;
						_cmdbuf.read(depthFormat);

						m_renderCtx->createFrameBuffer(handle, nwh, width, height, depthFormat);
					}
					else
					{
						uint8_t num;
						_cmdbuf.read(num);

						TextureHandle textureHandles[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
						for (uint32_t ii = 0; ii < num; ++ii)
						{
							_cmdbuf.read(textureHandles[ii]);
						}

						m_renderCtx->createFrameBuffer(handle, num, textureHandles);
					}
				}
				break;

			case CommandBuffer::DestroyFrameBuffer:
				{
					FrameBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyFrameBuffer(handle);
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

					m_renderCtx->createUniform(handle, type, num, name);
				}
				break;

			case CommandBuffer::DestroyUniform:
				{
					UniformHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyUniform(handle);
				}
				break;

			case CommandBuffer::SaveScreenShot:
				{
					uint16_t len;
					_cmdbuf.read(len);

					const char* filePath = (const char*)_cmdbuf.skip(len);

					m_renderCtx->saveScreenShot(filePath);
				}
				break;

			case CommandBuffer::UpdateViewName:
				{
					uint8_t id;
					_cmdbuf.read(id);

					uint16_t len;
					_cmdbuf.read(len);

					const char* name = (const char*)_cmdbuf.skip(len);

					m_renderCtx->updateViewName(id, name);
				}
				break;

			default:
				BX_CHECK(false, "Invalid command: %d", command);
				break;
			}
		} while (!end);

		flushTextureUpdateBatch(_cmdbuf);
	}

	uint8_t getSupportedRenderers(RendererType::Enum _enum[RendererType::Count])
	{
		uint8_t num = 0;
		for (uint8_t ii = 0; ii < uint8_t(RendererType::Count); ++ii)
		{
			if ( (RendererType::Direct3D11 == ii || RendererType::Direct3D12 == ii)
			&&  windowsVersionIs(Condition::LessEqual, 0x0502) )
			{
				continue;
			}

			if (s_rendererCreator[ii].supported)
			{
				_enum[num++] = RendererType::Enum(ii);
			}
		}

		return num;
	}

	const char* getRendererName(RendererType::Enum _type)
	{
		BX_CHECK(_type < RendererType::Count, "Invalid renderer type %d.", _type);
		return s_rendererCreator[_type].name;
	}

	bool init(RendererType::Enum _type, uint16_t _vendorId, uint16_t _deviceId, CallbackI* _callback, bx::ReallocatorI* _allocator)
	{
		BX_CHECK(NULL == s_ctx, "bgfx is already initialized.");

		memset(&g_caps, 0, sizeof(g_caps) );
		g_caps.maxViews     = BGFX_CONFIG_MAX_VIEWS;
		g_caps.maxDrawCalls = BGFX_CONFIG_MAX_DRAW_CALLS;
		g_caps.maxFBAttachments = 1;
		g_caps.vendorId = _vendorId;
		g_caps.deviceId = _deviceId;

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

		BX_TRACE("Init...");

		s_ctx = BX_ALIGNED_NEW(g_allocator, Context, 16);
		if (!s_ctx->init(_type) )
		{
			BX_TRACE("Init failed.");

			BX_ALIGNED_DELETE(g_allocator, s_ctx, 16);
			s_ctx = NULL;

			if (NULL != s_callbackStub)
			{
				BX_DELETE(g_allocator, s_callbackStub);
				s_callbackStub = NULL;
			}

			if (NULL != s_allocatorStub)
			{
				bx::CrtAllocator allocator;
				BX_DELETE(&allocator, s_allocatorStub);
				s_allocatorStub = NULL;
			}

			s_threadIndex = 0;
			g_callback    = NULL;
			g_allocator   = NULL;
			return false;
		}

		BX_TRACE("Init complete.");
		return true;
	}

	void shutdown()
	{
		BX_TRACE("Shutdown...");

		BGFX_CHECK_MAIN_THREAD();
		Context* ctx = s_ctx; // it's going to be NULLd inside shutdown.
		ctx->shutdown();
		BX_CHECK(NULL == s_ctx, "bgfx is should be uninitialized here.");

		BX_ALIGNED_DELETE(g_allocator, ctx, 16);

		BX_TRACE("Shutdown complete.");

		if (NULL != s_allocatorStub)
		{
			s_allocatorStub->checkLeaks();
		}

		if (NULL != s_callbackStub)
		{
			BX_DELETE(g_allocator, s_callbackStub);
			s_callbackStub = NULL;
		}

		if (NULL != s_allocatorStub)
		{
			bx::CrtAllocator allocator;
			BX_DELETE(&allocator, s_allocatorStub);
			s_allocatorStub = NULL;
		}

		s_threadIndex = 0;
		g_callback    = NULL;
		g_allocator   = NULL;
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

	const Caps* getCaps()
	{
		return &g_caps;
	}

	const HMD* getHMD()
	{
		return s_ctx->getHMD();
	}

	const Stats* getStats()
	{
		return s_ctx->getPerfStats();
	}

	RendererType::Enum getRendererType()
	{
		return g_caps.rendererType;
	}

	const Memory* alloc(uint32_t _size)
	{
		BX_CHECK(0 < _size, "Invalid memory operation. _size is 0.");
		Memory* mem = (Memory*)BX_ALLOC(g_allocator, sizeof(Memory) + _size);
		mem->size = _size;
		mem->data = (uint8_t*)mem + sizeof(Memory);
		return mem;
	}

	const Memory* copy(const void* _data, uint32_t _size)
	{
		BX_CHECK(0 < _size, "Invalid memory operation. _size is 0.");
		const Memory* mem = alloc(_size);
		memcpy(mem->data, _data, _size);
		return mem;
	}

	struct MemoryRef
	{
		Memory mem;
		ReleaseFn releaseFn;
		void* userData;
	};

	const Memory* makeRef(const void* _data, uint32_t _size, ReleaseFn _releaseFn, void* _userData)
	{
		MemoryRef* memRef = (MemoryRef*)BX_ALLOC(g_allocator, sizeof(MemoryRef) );
		memRef->mem.size  = _size;
		memRef->mem.data  = (uint8_t*)_data;
		memRef->releaseFn = _releaseFn;
		memRef->userData  = _userData;
		return &memRef->mem;
	}

	bool isMemoryRef(const Memory* _mem)
	{
		return _mem->data != (uint8_t*)_mem + sizeof(Memory);
	}

	void release(const Memory* _mem)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		Memory* mem = const_cast<Memory*>(_mem);
		if (isMemoryRef(mem) )
		{
			MemoryRef* memRef = reinterpret_cast<MemoryRef*>(mem);
			if (NULL != memRef->releaseFn)
			{
				memRef->releaseFn(mem->data, memRef->userData);
			}
		}
		BX_FREE(g_allocator, mem);
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

	void dbgTextPrintfVargs(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList)
	{
		s_ctx->dbgTextPrintfVargs(_x, _y, _attr, _format, _argList);
	}

	void dbgTextPrintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...)
	{
		BGFX_CHECK_MAIN_THREAD();
		va_list argList;
		va_start(argList, _format);
		s_ctx->dbgTextPrintfVargs(_x, _y, _attr, _format, argList);
		va_end(argList);
	}

	void dbgTextImage(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->dbgTextImage(_x, _y, _width, _height, _data, _pitch);
	}

	IndexBufferHandle createIndexBuffer(const Memory* _mem, uint16_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createIndexBuffer(_mem, _flags);
	}

	void destroyIndexBuffer(IndexBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyIndexBuffer(_handle);
	}

	VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl, uint16_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		BX_CHECK(0 != _decl.m_stride, "Invalid VertexDecl.");
		return s_ctx->createVertexBuffer(_mem, _decl, _flags);
	}

	void destroyVertexBuffer(VertexBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyVertexBuffer(_handle);
	}

	DynamicIndexBufferHandle createDynamicIndexBuffer(uint32_t _num, uint16_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->createDynamicIndexBuffer(_num, _flags);
	}

	DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem, uint16_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createDynamicIndexBuffer(_mem, _flags);
	}

	void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _startIndex, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		s_ctx->updateDynamicIndexBuffer(_handle, _startIndex, _mem);
	}

	void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyDynamicIndexBuffer(_handle);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(uint32_t _num, const VertexDecl& _decl, uint16_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 != _decl.m_stride, "Invalid VertexDecl.");
		return s_ctx->createDynamicVertexBuffer(_num, _decl, _flags);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexDecl& _decl, uint16_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		BX_CHECK(0 != _decl.m_stride, "Invalid VertexDecl.");
		return s_ctx->createDynamicVertexBuffer(_mem, _decl, _flags);
	}

	void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		s_ctx->updateDynamicVertexBuffer(_handle, _startVertex, _mem);
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

	bool allocTransientBuffers(bgfx::TransientVertexBuffer* _tvb, const bgfx::VertexDecl& _decl, uint32_t _numVertices, bgfx::TransientIndexBuffer* _tib, uint32_t _numIndices)
	{
		if (checkAvailTransientBuffers(_numVertices, _decl, _numIndices) )
		{
			allocTransientVertexBuffer(_tvb, _numVertices, _decl);
			allocTransientIndexBuffer(_tib, _numIndices);
			return true;
		}

		return false;
	}

	const InstanceDataBuffer* allocInstanceDataBuffer(uint32_t _num, uint16_t _stride)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 != (g_caps.supported & BGFX_CAPS_INSTANCING), "Instancing is not supported! Use bgfx::getCaps to check backend renderer capabilities.");
		BX_CHECK(0 < _num, "Requesting 0 instanced data vertices.");
		return s_ctx->allocInstanceDataBuffer(_num, _stride);
	}

	IndirectBufferHandle createIndirectBuffer(uint32_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->createIndirectBuffer(_num);
	}

	void destroyIndirectBuffer(IndirectBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyIndirectBuffer(_handle);
	}

	ShaderHandle createShader(const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createShader(_mem);
	}

	uint16_t getShaderUniforms(ShaderHandle _handle, UniformHandle* _uniforms, uint16_t _max)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->getShaderUniforms(_handle, _uniforms, _max);
	}

	void destroyShader(ShaderHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyShader(_handle);
	}

	ProgramHandle createProgram(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders)
	{
		BGFX_CHECK_MAIN_THREAD();
		if (!isValid(_fsh) )
		{
			return createProgram(_vsh, _destroyShaders);
		}

		return s_ctx->createProgram(_vsh, _fsh, _destroyShaders);
	}

	ProgramHandle createProgram(ShaderHandle _csh, bool _destroyShader)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->createProgram(_csh, _destroyShader);
	}

	void destroyProgram(ProgramHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyProgram(_handle);
	}

	void calcTextureSize(TextureInfo& _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, uint8_t _numMips, TextureFormat::Enum _format)
	{
		const ImageBlockInfo& blockInfo = getBlockInfo(_format);
		const uint8_t  bpp         = blockInfo.bitsPerPixel;
		const uint16_t blockWidth  = blockInfo.blockWidth;
		const uint16_t blockHeight = blockInfo.blockHeight;
		const uint16_t minBlockX   = blockInfo.minBlockX;
		const uint16_t minBlockY   = blockInfo.minBlockY;

		_width   = bx::uint16_max(blockWidth  * minBlockX, ( (_width  + blockWidth  - 1) / blockWidth)*blockWidth);
		_height  = bx::uint16_max(blockHeight * minBlockY, ( (_height + blockHeight - 1) / blockHeight)*blockHeight);
		_depth   = bx::uint16_max(1, _depth);
		_numMips = uint8_t(bx::uint16_max(1, _numMips) );

		uint32_t width  = _width;
		uint32_t height = _height;
		uint32_t depth  = _depth;
		uint32_t sides  = _cubeMap ? 6 : 1;
		uint32_t size   = 0;

		for (uint32_t lod = 0; lod < _numMips; ++lod)
		{
			width  = bx::uint32_max(blockWidth  * minBlockX, ( (width  + blockWidth  - 1) / blockWidth )*blockWidth);
			height = bx::uint32_max(blockHeight * minBlockY, ( (height + blockHeight - 1) / blockHeight)*blockHeight);
			depth  = bx::uint32_max(1, depth);

			size += width*height*depth*bpp/8 * sides;

			width  >>= 1;
			height >>= 1;
			depth  >>= 1;
		}

		_info.format  = _format;
		_info.width   = _width;
		_info.height  = _height;
		_info.depth   = _depth;
		_info.numMips = _numMips;
		_info.cubeMap = _cubeMap;
		_info.storageSize  = size;
		_info.bitsPerPixel = bpp;
	}

	TextureHandle createTexture(const Memory* _mem, uint32_t _flags, uint8_t _skip, TextureInfo* _info)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createTexture(_mem, _flags, _skip, _info, BackbufferRatio::Count);
	}

	void getTextureSizeFromRatio(BackbufferRatio::Enum _ratio, uint16_t& _width, uint16_t& _height)
	{
		switch (_ratio)
		{
		case BackbufferRatio::Half:      _width /=  2; _height /=  2; break;
		case BackbufferRatio::Quarter:   _width /=  4; _height /=  4; break;
		case BackbufferRatio::Eighth:    _width /=  8; _height /=  8; break;
		case BackbufferRatio::Sixteenth: _width /= 16; _height /= 16; break;
		case BackbufferRatio::Double:    _width *=  2; _height *=  2; break;

		default:
			break;
		}

		_width  = bx::uint16_max(1, _width);
		_height = bx::uint16_max(1, _height);
	}

	TextureHandle createTexture2D(BackbufferRatio::Enum _ratio, uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();

		_numMips = uint8_t(bx::uint32_max(1, _numMips) );

		if (BX_ENABLED(BGFX_CONFIG_DEBUG)
		&&  NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _width, _height, 1, false, _numMips, _format);
			BX_CHECK(ti.storageSize == _mem->size
				, "createTexture2D: Texture storage size doesn't match passed memory size (storage size: %d, memory size: %d)"
				, ti.storageSize
				, _mem->size
				);
		}

		uint32_t size = sizeof(uint32_t)+sizeof(TextureCreate);
		const Memory* mem = alloc(size);

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic);

		if (BackbufferRatio::Count != _ratio)
		{
			_width  = uint16_t(s_ctx->m_resolution.m_width);
			_height = uint16_t(s_ctx->m_resolution.m_height);
			getTextureSizeFromRatio(_ratio, _width, _height);
		}

		TextureCreate tc;
		tc.m_flags   = _flags;
		tc.m_width   = _width;
		tc.m_height  = _height;
		tc.m_sides   = 0;
		tc.m_depth   = 0;
		tc.m_numMips = _numMips;
		tc.m_format  = uint8_t(_format);
		tc.m_cubeMap = false;
		tc.m_mem     = _mem;
		bx::write(&writer, tc);

		return s_ctx->createTexture(mem, _flags, 0, NULL, _ratio);
	}

	TextureHandle createTexture2D(uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		BX_CHECK(_width > 0 && _height > 0, "Invalid texture size (width %d, height %d).", _width, _height);
		return createTexture2D(BackbufferRatio::Count, _width, _height, _numMips, _format, _flags, _mem);
	}

	TextureHandle createTexture2D(BackbufferRatio::Enum _ratio, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags)
	{
		BX_CHECK(_ratio < BackbufferRatio::Count, "Invalid back buffer ratio.");
		return createTexture2D(_ratio, 0, 0, _numMips, _format, _flags, NULL);
	}

	TextureHandle createTexture3D(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 != (g_caps.supported & BGFX_CAPS_TEXTURE_3D)
			, "Texture3D is not supported! Use bgfx::getCaps to check BGFX_CAPS_TEXTURE_3D backend renderer capabilities."
			);

		_numMips = uint8_t(bx::uint32_max(1, _numMips) );

		if (BX_ENABLED(BGFX_CONFIG_DEBUG)
		&&  NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _width, _height, _depth, false, _numMips, _format);
			BX_CHECK(ti.storageSize == _mem->size
				, "createTexture3D: Texture storage size doesn't match passed memory size (storage size: %d, memory size: %d)"
				, ti.storageSize
				, _mem->size
				);
		}

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

		return s_ctx->createTexture(mem, _flags, 0, NULL, BackbufferRatio::Count);
	}

	TextureHandle createTextureCube(uint16_t _size, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		BGFX_CHECK_MAIN_THREAD();

		_numMips = uint8_t(bx::uint32_max(1, _numMips) );

		if (BX_ENABLED(BGFX_CONFIG_DEBUG)
		&&  NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _size, _size, 1, true, _numMips, _format);
			BX_CHECK(ti.storageSize == _mem->size
				, "createTextureCube: Texture storage size doesn't match passed memory size (storage size: %d, memory size: %d)"
				, ti.storageSize
				, _mem->size
				);
		}

		uint32_t size = sizeof(uint32_t)+sizeof(TextureCreate);
		const Memory* mem = alloc(size);

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic);

		TextureCreate tc;
		tc.m_flags   = _flags;
		tc.m_width   = _size;
		tc.m_height  = _size;
		tc.m_sides   = 6;
		tc.m_depth   = 0;
		tc.m_numMips = _numMips;
		tc.m_format  = uint8_t(_format);
		tc.m_cubeMap = true;
		tc.m_mem     = _mem;
		bx::write(&writer, tc);

		return s_ctx->createTexture(mem, _flags, 0, NULL, BackbufferRatio::Count);
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
		BX_CHECK(0 != (g_caps.supported & BGFX_CAPS_TEXTURE_3D)
			, "Texture3D is not supported! Use bgfx::getCaps to check BGFX_CAPS_TEXTURE_3D backend renderer capabilities."
			);
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

	void readTexture(TextureHandle _handle, void* _data)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _data, "_data can't be NULL");
		BX_CHECK(0 != (g_caps.supported & BGFX_CAPS_TEXTURE_READ_BACK)
			, "Texture read-back is not supported! Use bgfx::getCaps to check BGFX_CAPS_TEXTURE_READ_BACK backend renderer capabilities."
			);
		s_ctx->readTexture(_handle, _data);
	}

	void readTexture(FrameBufferHandle _handle, uint8_t _attachment, void* _data)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _data, "_data can't be NULL");
		BX_CHECK(0 != (g_caps.supported & BGFX_CAPS_TEXTURE_READ_BACK)
			, "Texture read-back is not supported! Use bgfx::getCaps to check BGFX_CAPS_TEXTURE_READ_BACK backend renderer capabilities."
			);
		s_ctx->readTexture(_handle, _attachment, _data);
	}

	FrameBufferHandle createFrameBuffer(uint16_t _width, uint16_t _height, TextureFormat::Enum _format, uint32_t _textureFlags)
	{
		_textureFlags |= _textureFlags&BGFX_TEXTURE_RT_MSAA_MASK ? 0 : BGFX_TEXTURE_RT;
		TextureHandle th = createTexture2D(_width, _height, 1, _format, _textureFlags);
		return createFrameBuffer(1, &th, true);
	}

	FrameBufferHandle createFrameBuffer(BackbufferRatio::Enum _ratio, TextureFormat::Enum _format, uint32_t _textureFlags)
	{
		BX_CHECK(_ratio < BackbufferRatio::Count, "Invalid back buffer ratio.");
		_textureFlags |= _textureFlags&BGFX_TEXTURE_RT_MSAA_MASK ? 0 : BGFX_TEXTURE_RT;
		TextureHandle th = createTexture2D(_ratio, 1, _format, _textureFlags);
		return createFrameBuffer(1, &th, true);
	}

	FrameBufferHandle createFrameBuffer(uint8_t _num, const TextureHandle* _handles, bool _destroyTextures)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(_num != 0, "Number of frame buffer attachments can't be 0.");
		BX_CHECK(_num <= BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS, "Number of frame buffer attachments is larger than allowed %d (max: %d)."
			, _num
			, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
			);
		BX_CHECK(NULL != _handles, "_handles can't be NULL");
		return s_ctx->createFrameBuffer(_num, _handles, _destroyTextures);
	}

	FrameBufferHandle createFrameBuffer(void* _nwh, uint16_t _width, uint16_t _height, TextureFormat::Enum _depthFormat)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->createFrameBuffer(_nwh, _width, _height, _depthFormat);
	}

	void destroyFrameBuffer(FrameBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->destroyFrameBuffer(_handle);
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

	void setPaletteColor(uint8_t _index, uint32_t _rgba)
	{
		BGFX_CHECK_MAIN_THREAD();

		const uint8_t rr = uint8_t(_rgba>>24);
		const uint8_t gg = uint8_t(_rgba>>16);
		const uint8_t bb = uint8_t(_rgba>> 8);
		const uint8_t aa = uint8_t(_rgba>> 0);

		float rgba[4] =
		{
			rr * 1.0f/255.0f,
			gg * 1.0f/255.0f,
			bb * 1.0f/255.0f,
			aa * 1.0f/255.0f,
		};
		s_ctx->setPaletteColor(_index, rgba);
	}

	void setPaletteColor(uint8_t _index, float _r, float _g, float _b, float _a)
	{
		BGFX_CHECK_MAIN_THREAD();
		float rgba[4] = { _r, _g, _b, _a };
		s_ctx->setPaletteColor(_index, rgba);
	}

	void setPaletteColor(uint8_t _index, const float _rgba[4])
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setPaletteColor(_index, _rgba);
	}

	bool checkView(uint8_t _id)
	{
		// workaround GCC 4.9 type-limit check.
		const uint32_t id = _id;
		return id < BGFX_CONFIG_MAX_VIEWS;
	}

	void setViewName(uint8_t _id, const char* _name)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewName(_id, _name);
	}

	void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewRect(_id, _x, _y, _width, _height);
	}

	void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, BackbufferRatio::Enum _ratio)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);

		uint16_t width  = uint16_t(s_ctx->m_resolution.m_width);
		uint16_t height = uint16_t(s_ctx->m_resolution.m_height);
		getTextureSizeFromRatio(_ratio, width, height);
		setViewRect(_id, _x, _y, width, height);
	}

	void setViewScissor(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewScissor(_id, _x, _y, _width, _height);
	}

	void setViewClear(uint8_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewClear(_id, _flags, _rgba, _depth, _stencil);
	}

	void setViewClear(uint8_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewClear(_id, _flags, _depth, _stencil, _0, _1, _2, _3, _4, _5, _6, _7);
	}

	void setViewSeq(uint8_t _id, bool _enabled)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewSeq(_id, _enabled);
	}

	void setViewFrameBuffer(uint8_t _id, FrameBufferHandle _handle)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewFrameBuffer(_id, _handle);
	}

	void setViewTransform(uint8_t _id, const void* _view, const void* _projL, uint8_t _flags, const void* _projR)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewTransform(_id, _view, _projL, _flags, _projR);
	}

	void setViewRemap(uint8_t _id, uint8_t _num, const void* _remap)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewRemap(_id, _num, _remap);
	}

	void resetView(uint8_t _id)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->resetView(_id);
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

	uint32_t allocTransform(Transform* _transform, uint16_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->allocTransform(_transform, _num);
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

	void setIndexBuffer(const TransientIndexBuffer* _tib)
	{
		setIndexBuffer(_tib, 0, UINT32_MAX);
	}

	void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _tib, "_tib can't be NULL");
		uint32_t numIndices = bx::uint32_min(_numIndices, _tib->size/2);
		s_ctx->setIndexBuffer(_tib, _tib->startIndex + _firstIndex, numIndices);
	}

	void setVertexBuffer(VertexBufferHandle _handle)
	{
		setVertexBuffer(_handle, 0, UINT32_MAX);
	}

	void setVertexBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setVertexBuffer(_handle, _startVertex, _numVertices);
	}

	void setVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _numVertices)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setVertexBuffer(_handle, _numVertices);
	}

	void setVertexBuffer(const TransientVertexBuffer* _tvb)
	{
		setVertexBuffer(_tvb, 0, UINT32_MAX);
	}

	void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _startVertex, uint32_t _numVertices)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _tvb, "_tvb can't be NULL");
		s_ctx->setVertexBuffer(_tvb, _startVertex, _numVertices);
	}

	void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint32_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(NULL != _idb, "_idb can't be NULL");
		s_ctx->setInstanceDataBuffer(_idb, _num);
	}

	void setInstanceDataBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setInstanceDataBuffer(_handle, _startVertex, _num);
	}

	void setInstanceDataBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setInstanceDataBuffer(_handle, _startVertex, _num);
	}

	void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setTexture(_stage, _sampler, _handle, _flags);
	}

	void setTexture(uint8_t _stage, UniformHandle _sampler, FrameBufferHandle _handle, uint8_t _attachment, uint32_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setTexture(_stage, _sampler, _handle, _attachment, _flags);
	}

	uint32_t touch(uint8_t _id)
	{
		ProgramHandle handle = BGFX_INVALID_HANDLE;
		return submit(_id, handle);
	}

	uint32_t submit(uint8_t _id, ProgramHandle _handle, int32_t _depth)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->submit(_id, _handle, _depth);
	}

	uint32_t submit(uint8_t _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, int32_t _depth)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->submit(_id, _handle, _indirectHandle, _start, _num, _depth);
	}

	void setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, DynamicIndexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, DynamicVertexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, IndirectBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setBuffer(_stage, _handle, _access);
	}

	void setImage(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setImage(_stage, _sampler, _handle, _mip, _access, _format);
	}

	void setImage(uint8_t _stage, UniformHandle _sampler, FrameBufferHandle _handle, uint8_t _attachment, Access::Enum _access, TextureFormat::Enum _format)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->setImage(_stage, _sampler, _handle, _attachment, _access, _format);
	}

	uint32_t dispatch(uint8_t _id, ProgramHandle _handle, uint16_t _numX, uint16_t _numY, uint16_t _numZ, uint8_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->dispatch(_id, _handle, _numX, _numY, _numZ, _flags);
	}

	uint32_t dispatch(uint8_t _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
	{
		BGFX_CHECK_MAIN_THREAD();
		return s_ctx->dispatch(_id, _handle, _indirectHandle, _start, _num, _flags);
	}

	void discard()
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->discard();
	}

	void blit(uint8_t _id, TextureHandle _dst, uint16_t _dstX, uint16_t _dstY, TextureHandle _src, uint16_t _srcX, uint16_t _srcY, uint16_t _width, uint16_t _height)
	{
		blit(_id, _dst, 0, _dstX, _dstY, 0, _src, 0, _srcX, _srcY, 0, _width, _height, 0);
	}

	void blit(uint8_t _id, TextureHandle _dst, uint16_t _dstX, uint16_t _dstY, FrameBufferHandle _src, uint8_t _attachment, uint16_t _srcX, uint16_t _srcY, uint16_t _width, uint16_t _height)
	{
		blit(_id, _dst, 0, _dstX, _dstY, 0, _src, _attachment, 0, _srcX, _srcY, 0, _width, _height, 0);
	}

	void blit(uint8_t _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 != (g_caps.supported & BGFX_CAPS_TEXTURE_BLIT)
			, "Texture blit is not supported, use bgfx::getCaps to test BGFX_CAPS_TEXTURE_BLIT feature availability"
			);
		s_ctx->blit(_id, _dst, _dstMip, _dstX, _dstY, _dstZ, _src, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
	}

	void blit(uint8_t _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, FrameBufferHandle _src, uint8_t _attachment, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
	{
		BGFX_CHECK_MAIN_THREAD();
		BX_CHECK(0 != (g_caps.supported & BGFX_CAPS_TEXTURE_BLIT)
			, "Texture blit is not supported! Use bgfx::getCaps to check BGFX_CAPS_TEXTURE_BLIT backend renderer capabilities."
			);
		s_ctx->blit(_id, _dst, _dstMip, _dstX, _dstY, _dstZ, _src, _attachment, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
	}

	void saveScreenShot(const char* _filePath)
	{
		BGFX_CHECK_MAIN_THREAD();
		s_ctx->saveScreenShot(_filePath);
	}
} // namespace bgfx

#include <bgfx/c99/bgfx.h>
#include <bgfx/c99/bgfxplatform.h>

BX_STATIC_ASSERT(bgfx::Fatal::Count         == bgfx::Fatal::Enum(BGFX_FATAL_COUNT) );
BX_STATIC_ASSERT(bgfx::RendererType::Count  == bgfx::RendererType::Enum(BGFX_RENDERER_TYPE_COUNT) );
BX_STATIC_ASSERT(bgfx::Attrib::Count        == bgfx::Attrib::Enum(BGFX_ATTRIB_COUNT) );
BX_STATIC_ASSERT(bgfx::AttribType::Count    == bgfx::AttribType::Enum(BGFX_ATTRIB_TYPE_COUNT) );
BX_STATIC_ASSERT(bgfx::TextureFormat::Count == bgfx::TextureFormat::Enum(BGFX_TEXTURE_FORMAT_COUNT) );
BX_STATIC_ASSERT(bgfx::UniformType::Count   == bgfx::UniformType::Enum(BGFX_UNIFORM_TYPE_COUNT) );
BX_STATIC_ASSERT(bgfx::RenderFrame::Count   == bgfx::RenderFrame::Enum(BGFX_RENDER_FRAME_COUNT) );

BX_STATIC_ASSERT(sizeof(bgfx::Memory)                == sizeof(bgfx_memory_t) );
BX_STATIC_ASSERT(sizeof(bgfx::VertexDecl)            == sizeof(bgfx_vertex_decl_t) );
BX_STATIC_ASSERT(sizeof(bgfx::TransientIndexBuffer)  == sizeof(bgfx_transient_index_buffer_t) );
BX_STATIC_ASSERT(sizeof(bgfx::TransientVertexBuffer) == sizeof(bgfx_transient_vertex_buffer_t) );
BX_STATIC_ASSERT(sizeof(bgfx::InstanceDataBuffer)    == sizeof(bgfx_instance_data_buffer_t) );
BX_STATIC_ASSERT(sizeof(bgfx::TextureInfo)           == sizeof(bgfx_texture_info_t) );
BX_STATIC_ASSERT(sizeof(bgfx::Caps)                  == sizeof(bgfx_caps_t) );
BX_STATIC_ASSERT(sizeof(bgfx::PlatformData)          == sizeof(bgfx_platform_data_t) );

namespace bgfx
{
	struct CallbackC99 : public CallbackI
	{
		virtual ~CallbackC99()
		{
		}

		virtual void fatal(Fatal::Enum _code, const char* _str) BX_OVERRIDE
		{
			m_interface->vtbl->fatal(m_interface, (bgfx_fatal_t)_code, _str);
		}

		virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) BX_OVERRIDE
		{
			m_interface->vtbl->trace_vargs(m_interface, _filePath, _line, _format, _argList);
		}

		virtual uint32_t cacheReadSize(uint64_t _id) BX_OVERRIDE
		{
			return m_interface->vtbl->cache_read_size(m_interface, _id);
		}

		virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) BX_OVERRIDE
		{
			return m_interface->vtbl->cache_read(m_interface, _id, _data, _size);
		}

		virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) BX_OVERRIDE
		{
			m_interface->vtbl->cache_write(m_interface, _id, _data, _size);
		}

		virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip) BX_OVERRIDE
		{
			m_interface->vtbl->screen_shot(m_interface, _filePath, _width, _height, _pitch, _data, _size, _yflip);
		}

		virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, TextureFormat::Enum _format, bool _yflip) BX_OVERRIDE
		{
			m_interface->vtbl->capture_begin(m_interface, _width, _height, _pitch, (bgfx_texture_format_t)_format, _yflip);
		}

		virtual void captureEnd() BX_OVERRIDE
		{
			m_interface->vtbl->capture_end(m_interface);
		}

		virtual void captureFrame(const void* _data, uint32_t _size) BX_OVERRIDE
		{
			m_interface->vtbl->capture_frame(m_interface, _data, _size);
		}

		bgfx_callback_interface_t* m_interface;
	};

	class AllocatorC99 : public bx::ReallocatorI
	{
	public:
		virtual ~AllocatorC99()
		{
		}

		virtual void* alloc(size_t _size, size_t _align, const char* _file, uint32_t _line) BX_OVERRIDE
		{
			return m_interface->vtbl->alloc(m_interface, _size, _align, _file, _line);
		}

		virtual void free(void* _ptr, size_t _align, const char* _file, uint32_t _line) BX_OVERRIDE
		{
			m_interface->vtbl->free(m_interface, _ptr, _align, _file, _line);
		}

		virtual void* realloc(void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line) BX_OVERRIDE
		{
			return m_interface->vtbl->realloc(m_interface, _ptr, _size, _align, _file, _line);
		}

		bgfx_reallocator_interface_t* m_interface;
	};

} // namespace bgfx

BGFX_C_API void bgfx_vertex_decl_begin(bgfx_vertex_decl_t* _decl, bgfx_renderer_type_t _renderer)
{
	bgfx::VertexDecl* decl = (bgfx::VertexDecl*)_decl;
	decl->begin(bgfx::RendererType::Enum(_renderer) );
}

BGFX_C_API void bgfx_vertex_decl_add(bgfx_vertex_decl_t* _decl, bgfx_attrib_t _attrib, uint8_t _num, bgfx_attrib_type_t _type, bool _normalized, bool _asInt)
{
	bgfx::VertexDecl* decl = (bgfx::VertexDecl*)_decl;
	decl->add(bgfx::Attrib::Enum(_attrib)
		, _num
		, bgfx::AttribType::Enum(_type)
		, _normalized
		, _asInt
		);
}

BGFX_C_API void bgfx_vertex_decl_skip(bgfx_vertex_decl_t* _decl, uint8_t _num)
{
	bgfx::VertexDecl* decl = (bgfx::VertexDecl*)_decl;
	decl->skip(_num);
}

BGFX_C_API void bgfx_vertex_decl_end(bgfx_vertex_decl_t* _decl)
{
	bgfx::VertexDecl* decl = (bgfx::VertexDecl*)_decl;
	decl->end();
}

BGFX_C_API void bgfx_vertex_pack(const float _input[4], bool _inputNormalized, bgfx_attrib_t _attr, const bgfx_vertex_decl_t* _decl, void* _data, uint32_t _index)
{
	bgfx::VertexDecl& decl = *(bgfx::VertexDecl*)_decl;
	bgfx::vertexPack(_input, _inputNormalized, bgfx::Attrib::Enum(_attr), decl, _data, _index);
}

BGFX_C_API void bgfx_vertex_unpack(float _output[4], bgfx_attrib_t _attr, const bgfx_vertex_decl_t* _decl, const void* _data, uint32_t _index)
{
	bgfx::VertexDecl& decl = *(bgfx::VertexDecl*)_decl;
	bgfx::vertexUnpack(_output, bgfx::Attrib::Enum(_attr), decl, _data, _index);
}

BGFX_C_API void bgfx_vertex_convert(const bgfx_vertex_decl_t* _destDecl, void* _destData, const bgfx_vertex_decl_t* _srcDecl, const void* _srcData, uint32_t _num)
{
	bgfx::VertexDecl& destDecl = *(bgfx::VertexDecl*)_destDecl;
	bgfx::VertexDecl& srcDecl  = *(bgfx::VertexDecl*)_srcDecl;
	bgfx::vertexConvert(destDecl, _destData, srcDecl, _srcData, _num);
}

BGFX_C_API uint16_t bgfx_weld_vertices(uint16_t* _output, const bgfx_vertex_decl_t* _decl, const void* _data, uint16_t _num, float _epsilon)
{
	bgfx::VertexDecl& decl = *(bgfx::VertexDecl*)_decl;
	return bgfx::weldVertices(_output, decl, _data, _num, _epsilon);
}

BGFX_C_API void bgfx_image_swizzle_bgra8(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst)
{
	bgfx::imageSwizzleBgra8(_width, _height, _pitch, _src, _dst);
}

BGFX_C_API void bgfx_image_rgba8_downsample_2x2(uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _src, void* _dst)
{
	bgfx::imageRgba8Downsample2x2(_width, _height, _pitch, _src, _dst);
}

BGFX_C_API uint8_t bgfx_get_supported_renderers(bgfx_renderer_type_t _enum[BGFX_RENDERER_TYPE_COUNT])
{
	return bgfx::getSupportedRenderers( (bgfx::RendererType::Enum*)_enum);
}

BGFX_C_API const char* bgfx_get_renderer_name(bgfx_renderer_type_t _type)
{
	return bgfx::getRendererName(bgfx::RendererType::Enum(_type) );
}

BGFX_C_API bool bgfx_init(bgfx_renderer_type_t _type, uint16_t _vendorId, uint16_t _deviceId, bgfx_callback_interface_t* _callback, bgfx_reallocator_interface_t* _allocator)
{
	static bgfx::CallbackC99 s_callback;
	s_callback.m_interface = _callback;

	static bgfx::AllocatorC99 s_allocator;
	s_allocator.m_interface = _allocator;

	return bgfx::init(bgfx::RendererType::Enum(_type)
		, _vendorId
		, _deviceId
		, NULL == _callback  ? NULL : &s_callback
		, NULL == _allocator ? NULL : &s_allocator
		);
}

BGFX_C_API void bgfx_shutdown()
{
	return bgfx::shutdown();
}

BGFX_C_API void bgfx_reset(uint32_t _width, uint32_t _height, uint32_t _flags)
{
	bgfx::reset(_width, _height, _flags);
}

BGFX_C_API uint32_t bgfx_frame()
{
	return bgfx::frame();
}

BGFX_C_API bgfx_renderer_type_t bgfx_get_renderer_type()
{
	return bgfx_renderer_type_t(bgfx::getRendererType() );
}

BGFX_C_API const bgfx_caps_t* bgfx_get_caps()
{
	return (const bgfx_caps_t*)bgfx::getCaps();
}

BGFX_C_API const bgfx_hmd_t* bgfx_get_hmd()
{
	return (const bgfx_hmd_t*)bgfx::getHMD();
}

BGFX_C_API const bgfx_stats_t* bgfx_get_stats()
{
	return (const bgfx_stats_t*)bgfx::getStats();
}

BGFX_C_API const bgfx_memory_t* bgfx_alloc(uint32_t _size)
{
	return (const bgfx_memory_t*)bgfx::alloc(_size);
}

BGFX_C_API const bgfx_memory_t* bgfx_copy(const void* _data, uint32_t _size)
{
	return (const bgfx_memory_t*)bgfx::copy(_data, _size);
}

BGFX_C_API const bgfx_memory_t* bgfx_make_ref(const void* _data, uint32_t _size)
{
	return (const bgfx_memory_t*)bgfx::makeRef(_data, _size);
}

BGFX_C_API const bgfx_memory_t* bgfx_make_ref_release(const void* _data, uint32_t _size, bgfx_release_fn_t _releaseFn, void* _userData)
{
	return (const bgfx_memory_t*)bgfx::makeRef(_data, _size, _releaseFn, _userData);
}

BGFX_C_API void bgfx_set_debug(uint32_t _debug)
{
	bgfx::setDebug(_debug);
}

BGFX_C_API void bgfx_dbg_text_clear(uint8_t _attr, bool _small)
{
	bgfx::dbgTextClear(_attr, _small);
}

BGFX_C_API void bgfx_dbg_text_printf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...)
{
	va_list argList;
	va_start(argList, _format);
	bgfx::dbgTextPrintfVargs(_x, _y, _attr, _format, argList);
	va_end(argList);
}

BGFX_C_API void bgfx_dbg_text_image(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch)
{
	bgfx::dbgTextImage(_x, _y, _width, _height, _data, _pitch);
}

BGFX_C_API bgfx_index_buffer_handle_t bgfx_create_index_buffer(const bgfx_memory_t* _mem, uint16_t _flags)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle;
	handle.cpp = bgfx::createIndexBuffer( (const bgfx::Memory*)_mem, _flags);
	return handle.c;
}

BGFX_C_API void bgfx_destroy_index_buffer(bgfx_index_buffer_handle_t _handle)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	bgfx::destroyIndexBuffer(handle.cpp);
}

BGFX_C_API bgfx_vertex_buffer_handle_t bgfx_create_vertex_buffer(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl, uint16_t _flags)
{
	const bgfx::VertexDecl& decl = *(const bgfx::VertexDecl*)_decl;
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle;
	handle.cpp = bgfx::createVertexBuffer( (const bgfx::Memory*)_mem, decl, _flags);
	return handle.c;
}

BGFX_C_API void bgfx_destroy_vertex_buffer(bgfx_vertex_buffer_handle_t _handle)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::destroyVertexBuffer(handle.cpp);
}

BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer(uint32_t _num, uint16_t _flags)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle;
	handle.cpp = bgfx::createDynamicIndexBuffer(_num, _flags);
	return handle.c;
}

BGFX_C_API bgfx_dynamic_index_buffer_handle_t bgfx_create_dynamic_index_buffer_mem(const bgfx_memory_t* _mem, uint16_t _flags)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle;
	handle.cpp = bgfx::createDynamicIndexBuffer( (const bgfx::Memory*)_mem, _flags);
	return handle.c;
}

BGFX_C_API void bgfx_update_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _startIndex, const bgfx_memory_t* _mem)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	bgfx::updateDynamicIndexBuffer(handle.cpp, _startIndex, (const bgfx::Memory*)_mem);
}

BGFX_C_API void bgfx_destroy_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	bgfx::destroyDynamicIndexBuffer(handle.cpp);
}

BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t* _decl, uint16_t _flags)
{
	const bgfx::VertexDecl& decl = *(const bgfx::VertexDecl*)_decl;
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle;
	handle.cpp = bgfx::createDynamicVertexBuffer(_num, decl, _flags);
	return handle.c;
}

BGFX_C_API bgfx_dynamic_vertex_buffer_handle_t bgfx_create_dynamic_vertex_buffer_mem(const bgfx_memory_t* _mem, const bgfx_vertex_decl_t* _decl, uint16_t _flags)
{
	const bgfx::VertexDecl& decl = *(const bgfx::VertexDecl*)_decl;
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle;
	handle.cpp = bgfx::createDynamicVertexBuffer( (const bgfx::Memory*)_mem, decl, _flags);
	return handle.c;
}

BGFX_C_API void bgfx_update_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, const bgfx_memory_t* _mem)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::updateDynamicVertexBuffer(handle.cpp, _startVertex, (const bgfx::Memory*)_mem);
}

BGFX_C_API void bgfx_destroy_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::destroyDynamicVertexBuffer(handle.cpp);
}

BGFX_C_API bool bgfx_check_avail_transient_index_buffer(uint32_t _num)
{
	return bgfx::checkAvailTransientIndexBuffer(_num);
}

BGFX_C_API bool bgfx_check_avail_transient_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t* _decl)
{
	const bgfx::VertexDecl& decl = *(const bgfx::VertexDecl*)_decl;
	return bgfx::checkAvailTransientVertexBuffer(_num, decl);
}

BGFX_C_API bool bgfx_check_avail_instance_data_buffer(uint32_t _num, uint16_t _stride)
{
	return bgfx::checkAvailInstanceDataBuffer(_num, _stride);
}

BGFX_C_API bool bgfx_check_avail_transient_buffers(uint32_t _numVertices, const bgfx_vertex_decl_t* _decl, uint32_t _numIndices)
{
	const bgfx::VertexDecl& decl = *(const bgfx::VertexDecl*)_decl;
	return bgfx::checkAvailTransientBuffers(_numVertices, decl, _numIndices);
}

BGFX_C_API void bgfx_alloc_transient_index_buffer(bgfx_transient_index_buffer_t* _tib, uint32_t _num)
{
	bgfx::allocTransientIndexBuffer( (bgfx::TransientIndexBuffer*)_tib, _num);
}

BGFX_C_API void bgfx_alloc_transient_vertex_buffer(bgfx_transient_vertex_buffer_t* _tvb, uint32_t _num, const bgfx_vertex_decl_t* _decl)
{
	const bgfx::VertexDecl& decl = *(const bgfx::VertexDecl*)_decl;
	bgfx::allocTransientVertexBuffer( (bgfx::TransientVertexBuffer*)_tvb, _num, decl);
}

BGFX_C_API bool bgfx_alloc_transient_buffers(bgfx_transient_vertex_buffer_t* _tvb, const bgfx_vertex_decl_t* _decl, uint32_t _numVertices, bgfx_transient_index_buffer_t* _tib, uint32_t _numIndices)
{
	const bgfx::VertexDecl& decl = *(const bgfx::VertexDecl*)_decl;
	return bgfx::allocTransientBuffers( (bgfx::TransientVertexBuffer*)_tvb, decl, _numVertices, (bgfx::TransientIndexBuffer*)_tib, _numIndices);
}

BGFX_C_API const bgfx_instance_data_buffer_t* bgfx_alloc_instance_data_buffer(uint32_t _num, uint16_t _stride)
{
	return (bgfx_instance_data_buffer_t*)bgfx::allocInstanceDataBuffer(_num, _stride);
}

BGFX_C_API bgfx_indirect_buffer_handle_t bgfx_create_indirect_buffer(uint32_t _num)
{
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } handle;
	handle.cpp = bgfx::createIndirectBuffer(_num);
	return handle.c;
}

BGFX_C_API void bgfx_destroy_indirect_buffer(bgfx_indirect_buffer_handle_t _handle)
{
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } handle = { _handle };
	bgfx::destroyIndirectBuffer(handle.cpp);
}

BGFX_C_API bgfx_shader_handle_t bgfx_create_shader(const bgfx_memory_t* _mem)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } handle;
	handle.cpp = bgfx::createShader( (const bgfx::Memory*)_mem);
	return handle.c;
}

BGFX_C_API uint16_t bgfx_get_shader_uniforms(bgfx_shader_handle_t _handle, bgfx_uniform_handle_t* _uniforms, uint16_t _max)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } handle = { _handle };
	return bgfx::getShaderUniforms(handle.cpp, (bgfx::UniformHandle*)_uniforms, _max);
}

BGFX_C_API void bgfx_destroy_shader(bgfx_shader_handle_t _handle)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } handle = { _handle };
	bgfx::destroyShader(handle.cpp);
}

BGFX_C_API bgfx_program_handle_t bgfx_create_program(bgfx_shader_handle_t _vsh, bgfx_shader_handle_t _fsh, bool _destroyShaders)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } vsh = { _vsh };
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } fsh = { _fsh };
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle;
	handle.cpp = bgfx::createProgram(vsh.cpp, fsh.cpp, _destroyShaders);
	return handle.c;
}

BGFX_C_API bgfx_program_handle_t bgfx_create_compute_program(bgfx_shader_handle_t _csh, bool _destroyShaders)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } csh = { _csh };
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle;
	handle.cpp = bgfx::createProgram(csh.cpp, _destroyShaders);
	return handle.c;
}

BGFX_C_API void bgfx_destroy_program(bgfx_program_handle_t _handle)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	bgfx::destroyProgram(handle.cpp);
}

BGFX_C_API void bgfx_calc_texture_size(bgfx_texture_info_t* _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, uint8_t _numMips, bgfx_texture_format_t _format)
{
	bgfx::TextureInfo& info = *(bgfx::TextureInfo*)_info;
	bgfx::calcTextureSize(info, _width, _height, _depth, _cubeMap, _numMips, bgfx::TextureFormat::Enum(_format) );
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture(const bgfx_memory_t* _mem, uint32_t _flags, uint8_t _skip, bgfx_texture_info_t* _info)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	bgfx::TextureInfo* info = (bgfx::TextureInfo*)_info;
	handle.cpp = bgfx::createTexture( (const bgfx::Memory*)_mem, _flags, _skip, info);
	return handle.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d(uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	handle.cpp = bgfx::createTexture2D(_width, _height, _numMips, bgfx::TextureFormat::Enum(_format), _flags, (const bgfx::Memory*)_mem);
	return handle.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d_scaled(bgfx_backbuffer_ratio_t _ratio, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	handle.cpp = bgfx::createTexture2D(bgfx::BackbufferRatio::Enum(_ratio), _numMips, bgfx::TextureFormat::Enum(_format), _flags);
	return handle.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_3d(uint16_t _width, uint16_t _height, uint16_t _depth, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	handle.cpp = bgfx::createTexture3D(_width, _height, _depth, _numMips, bgfx::TextureFormat::Enum(_format), _flags, (const bgfx::Memory*)_mem);
	return handle.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_cube(uint16_t _size, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	handle.cpp = bgfx::createTextureCube(_size, _numMips, bgfx::TextureFormat::Enum(_format), _flags, (const bgfx::Memory*)_mem);
	return handle.c;
}

BGFX_C_API void bgfx_update_texture_2d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::updateTexture2D(handle.cpp, _mip, _x, _y, _width, _height, (const bgfx::Memory*)_mem, _pitch);
}

BGFX_C_API void bgfx_update_texture_3d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::updateTexture3D(handle.cpp, _mip, _x, _y, _z, _width, _height, _depth, (const bgfx::Memory*)_mem);
}

BGFX_C_API void bgfx_update_texture_cube(bgfx_texture_handle_t _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::updateTextureCube(handle.cpp, _side, _mip, _x, _y, _width, _height, (const bgfx::Memory*)_mem, _pitch);
}

BGFX_C_API void bgfx_destroy_texture(bgfx_texture_handle_t _handle)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::destroyTexture(handle.cpp);
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer(uint16_t _width, uint16_t _height, bgfx_texture_format_t _format, uint32_t _textureFlags)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle;
	handle.cpp = bgfx::createFrameBuffer(_width, _height, bgfx::TextureFormat::Enum(_format), _textureFlags);
	return handle.c;
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_scaled(bgfx_backbuffer_ratio_t _ratio, bgfx_texture_format_t _format, uint32_t _textureFlags)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle;
	handle.cpp = bgfx::createFrameBuffer(bgfx::BackbufferRatio::Enum(_ratio), bgfx::TextureFormat::Enum(_format), _textureFlags);
	return handle.c;
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_handles(uint8_t _num, const bgfx_texture_handle_t* _handles, bool _destroyTextures)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle;
	handle.cpp = bgfx::createFrameBuffer(_num, (const bgfx::TextureHandle*)_handles, _destroyTextures);
	return handle.c;
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_nwh(void* _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _depthFormat)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle;
	handle.cpp = bgfx::createFrameBuffer(_nwh, _width, _height, bgfx::TextureFormat::Enum(_depthFormat) );
	return handle.c;
}

BGFX_C_API void bgfx_destroy_frame_buffer(bgfx_frame_buffer_handle_t _handle)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	bgfx::destroyFrameBuffer(handle.cpp);
}

BGFX_C_API bgfx_uniform_handle_t bgfx_create_uniform(const char* _name, bgfx_uniform_type_t _type, uint16_t _num)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle;
	handle.cpp = bgfx::createUniform(_name, bgfx::UniformType::Enum(_type), _num);
	return handle.c;
}

BGFX_C_API void bgfx_destroy_uniform(bgfx_uniform_handle_t _handle)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle = { _handle };
	bgfx::destroyUniform(handle.cpp);
}

BGFX_C_API void bgfx_set_palette_color(uint8_t _index, const float _rgba[4])
{
	bgfx::setPaletteColor(_index, _rgba);
}

BGFX_C_API void bgfx_set_view_name(uint8_t _id, const char* _name)
{
	bgfx::setViewName(_id, _name);
}

BGFX_C_API void bgfx_set_view_rect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	bgfx::setViewRect(_id, _x, _y, _width, _height);
}

BGFX_C_API void bgfx_set_view_scissor(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	bgfx::setViewScissor(_id, _x, _y, _width, _height);
}

BGFX_C_API void bgfx_set_view_clear(uint8_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
{
	bgfx::setViewClear(_id, _flags, _rgba, _depth, _stencil);
}

BGFX_C_API void bgfx_set_view_clear_mrt(uint8_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7)
{
	bgfx::setViewClear(_id, _flags, _depth, _stencil, _0, _1, _2, _3, _4, _5, _6, _7);
}

BGFX_C_API void bgfx_set_view_seq(uint8_t _id, bool _enabled)
{
	bgfx::setViewSeq(_id, _enabled);
}

BGFX_C_API void bgfx_set_view_frame_buffer(uint8_t _id, bgfx_frame_buffer_handle_t _handle)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	bgfx::setViewFrameBuffer(_id, handle.cpp);
}

BGFX_C_API void bgfx_set_view_transform(uint8_t _id, const void* _view, const void* _proj)
{
	bgfx::setViewTransform(_id, _view, _proj);
}

BGFX_C_API void bgfx_set_view_transform_stereo(uint8_t _id, const void* _view, const void* _projL, uint8_t _flags, const void* _projR)
{
	bgfx::setViewTransform(_id, _view, _projL, _flags, _projR);
}

BGFX_C_API void bgfx_set_view_remap(uint8_t _id, uint8_t _num, const void* _remap)
{
	bgfx::setViewRemap(_id, _num, _remap);
}

BGFX_C_API void bgfx_reset_view(uint8_t _id)
{
	bgfx::resetView(_id);
}

BGFX_C_API void bgfx_set_marker(const char* _marker)
{
	bgfx::setMarker(_marker);
}

BGFX_C_API void bgfx_set_state(uint64_t _state, uint32_t _rgba)
{
	bgfx::setState(_state, _rgba);
}

BGFX_C_API void bgfx_set_stencil(uint32_t _fstencil, uint32_t _bstencil)
{
	bgfx::setStencil(_fstencil, _bstencil);
}

BGFX_C_API uint16_t bgfx_set_scissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	return bgfx::setScissor(_x, _y, _width, _height);
}

BGFX_C_API void bgfx_set_scissor_cached(uint16_t _cache)
{
	bgfx::setScissor(_cache);
}

BGFX_C_API uint32_t bgfx_set_transform(const void* _mtx, uint16_t _num)
{
	return bgfx::setTransform(_mtx, _num);
}

BGFX_C_API uint32_t bgfx_alloc_transform(bgfx_transform_t* _transform, uint16_t _num)
{
	return bgfx::allocTransform( (bgfx::Transform*)_transform, _num);
}

BGFX_C_API void bgfx_set_transform_cached(uint32_t _cache, uint16_t _num)
{
	bgfx::setTransform(_cache, _num);
}

BGFX_C_API void bgfx_set_uniform(bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle = { _handle };
	bgfx::setUniform(handle.cpp, _value, _num);
}

BGFX_C_API void bgfx_set_index_buffer(bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	bgfx::setIndexBuffer(handle.cpp, _firstIndex, _numIndices);
}

BGFX_C_API void bgfx_set_dynamic_index_buffer(bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	bgfx::setIndexBuffer(handle.cpp, _firstIndex, _numIndices);
}

BGFX_C_API void bgfx_set_transient_index_buffer(const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices)
{
	bgfx::setIndexBuffer( (const bgfx::TransientIndexBuffer*)_tib, _firstIndex, _numIndices);
}

BGFX_C_API void bgfx_set_vertex_buffer(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::setVertexBuffer(handle.cpp, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_set_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _numVertices)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::setVertexBuffer(handle.cpp, _numVertices);
}

BGFX_C_API void bgfx_set_transient_vertex_buffer(const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices)
{
	bgfx::setVertexBuffer( (const bgfx::TransientVertexBuffer*)_tvb, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_set_instance_data_buffer(const bgfx_instance_data_buffer_t* _idb, uint32_t _num)
{
	bgfx::setInstanceDataBuffer( (const bgfx::InstanceDataBuffer*)_idb, _num);
}

BGFX_C_API void bgfx_set_instance_data_from_vertex_buffer(bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::setInstanceDataBuffer(handle.cpp, _startVertex, _num);
}

BGFX_C_API void bgfx_set_instance_data_from_dynamic_vertex_buffer(bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::setInstanceDataBuffer(handle.cpp, _startVertex, _num);
}

BGFX_C_API void bgfx_set_texture(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } sampler = { _sampler };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle  = { _handle  };
	bgfx::setTexture(_stage, sampler.cpp, handle.cpp, _flags);
}

BGFX_C_API void bgfx_set_texture_from_frame_buffer(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_frame_buffer_handle_t _handle, uint8_t _attachment, uint32_t _flags)
{
	union { bgfx_uniform_handle_t c;      bgfx::UniformHandle cpp;     } sampler = { _sampler };
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle  = { _handle };
	bgfx::setTexture(_stage, sampler.cpp, handle.cpp, _attachment, _flags);
}

BGFX_C_API uint32_t bgfx_touch(uint8_t _id)
{
	return bgfx::touch(_id);
}

BGFX_C_API uint32_t bgfx_submit(uint8_t _id, bgfx_program_handle_t _handle, int32_t _depth)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	return bgfx::submit(_id, handle.cpp, _depth);
}

BGFX_C_API uint32_t bgfx_submit_indirect(uint8_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, int32_t _depth)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	return bgfx::submit(_id, handle.cpp, indirectHandle.cpp, _start, _num, _depth);
}

BGFX_C_API void bgfx_set_image(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } sampler = { _sampler };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle  = { _handle  };
	bgfx::setImage(_stage, sampler.cpp, handle.cpp, _mip, bgfx::Access::Enum(_access), bgfx::TextureFormat::Enum(_format) );
}

BGFX_C_API void bgfx_set_image_from_frame_buffer(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_frame_buffer_handle_t _handle, uint8_t _attachment, bgfx_access_t _access, bgfx_texture_format_t _format)
{
	union { bgfx_uniform_handle_t c;      bgfx::UniformHandle cpp;     } sampler = { _sampler };
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle  = { _handle };
	bgfx::setImage(_stage, sampler.cpp, handle.cpp, _attachment, bgfx::Access::Enum(_access), bgfx::TextureFormat::Enum(_format) );
}

BGFX_C_API void bgfx_set_compute_index_buffer(uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) );
}

BGFX_C_API void bgfx_set_compute_vertex_buffer(uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) );
}

BGFX_C_API void bgfx_set_compute_dynamic_index_buffer(uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) );
}

BGFX_C_API void bgfx_set_compute_dynamic_vertex_buffer(uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) );
}

BGFX_C_API void bgfx_set_compute_indirect_buffer(uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } handle = { _handle };
	bgfx::setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) );
}

BGFX_C_API uint32_t bgfx_dispatch(uint8_t _id, bgfx_program_handle_t _handle, uint16_t _numX, uint16_t _numY, uint16_t _numZ, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	return bgfx::dispatch(_id, handle.cpp, _numX, _numY, _numZ, _flags);
}

BGFX_C_API uint32_t bgfx_dispatch_indirect(uint8_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	return bgfx::dispatch(_id, handle.cpp, indirectHandle.cpp, _start, _num, _flags);
}

BGFX_C_API void bgfx_discard()
{
	bgfx::discard();
}

BGFX_C_API void bgfx_blit(uint8_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } dst = { _dst };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } src = { _src };
	bgfx::blit(_id, dst.cpp, _dstMip, _dstX, _dstY, _dstZ, src.cpp, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
}

BGFX_C_API void bgfx_save_screen_shot(const char* _filePath)
{
	bgfx::saveScreenShot(_filePath);
}

BGFX_C_API bgfx_render_frame_t bgfx_render_frame()
{
	return bgfx_render_frame_t(bgfx::renderFrame() );
}

BGFX_C_API void bgfx_set_platform_data(bgfx_platform_data_t* _pd)
{
	bgfx::setPlatformData(*(bgfx::PlatformData*)_pd);
}
