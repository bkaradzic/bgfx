/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/platform.h>

#include "bgfx_p.h"
#include <bgfx/embedded_shader.h>
#include <bx/file.h>
#include <bx/mutex.h>

#include "topology.h"

BX_ERROR_RESULT(BGFX_ERROR_TEXTURE_VALIDATION,  BX_MAKEFOURCC('b', 'g', 0, 1) );

namespace bgfx
{
#define BGFX_API_THREAD_MAGIC UINT32_C(0x78666762)

#if BGFX_CONFIG_MULTITHREADED
#	define BGFX_CHECK_API_THREAD() \
				BX_CHECK(NULL != s_ctx, "Library is not initialized yet."); \
				BX_CHECK(BGFX_API_THREAD_MAGIC == s_threadIndex, "Must be called from main thread.")
#	define BGFX_CHECK_RENDER_THREAD() BX_CHECK(BGFX_API_THREAD_MAGIC != s_threadIndex, "Must be called from render thread.")
#else
#	define BGFX_CHECK_API_THREAD()
#	define BGFX_CHECK_RENDER_THREAD()
#endif // BGFX_CONFIG_MULTITHREADED

#define BGFX_CHECK_CAPS(_caps, _msg) \
		BX_CHECK(0 != (g_caps.supported & (_caps) ) \
			, _msg " Use bgfx::getCaps to check " #_caps " backend renderer capabilities." \
			);

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

		virtual void fatal(Fatal::Enum _code, const char* _str) override
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

		virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) override
		{
			char temp[2048];
			char* out = temp;
			va_list argListCopy;
			va_copy(argListCopy, _argList);
			int32_t len   = bx::snprintf(out, sizeof(temp), "%s (%d): ", _filePath, _line);
			int32_t total = len + bx::vsnprintf(out + len, sizeof(temp)-len, _format, argListCopy);
			va_end(argListCopy);
			if ( (int32_t)sizeof(temp) < total)
			{
				out = (char*)alloca(total+1);
				bx::memCopy(out, temp, len);
				bx::vsnprintf(out + len, total-len, _format, _argList);
			}
			out[total] = '\0';
			bx::debugOutput(out);
		}

		virtual void profilerBegin(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
		{
		}

		virtual void profilerBeginLiteral(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
		{
		}

		virtual void profilerEnd() override
		{
		}

		virtual uint32_t cacheReadSize(uint64_t /*_id*/) override
		{
			return 0;
		}

		virtual bool cacheRead(uint64_t /*_id*/, void* /*_data*/, uint32_t /*_size*/) override
		{
			return false;
		}

		virtual void cacheWrite(uint64_t /*_id*/, const void* /*_data*/, uint32_t /*_size*/) override
		{
		}

		virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip) override
		{
			BX_UNUSED(_filePath, _width, _height, _pitch, _data, _size, _yflip);

			const int32_t len = bx::strLen(_filePath)+5;
			char* filePath = (char*)alloca(len);
			bx::strCopy(filePath, len, _filePath);
			bx::strCat(filePath, len, ".tga");

			bx::FileWriter writer;
			if (bx::open(&writer, filePath) )
			{
				bimg::imageWriteTga(&writer, _width, _height, _pitch, _data, false, _yflip);
				bx::close(&writer);
			}
		}

		virtual void captureBegin(uint32_t /*_width*/, uint32_t /*_height*/, uint32_t /*_pitch*/, TextureFormat::Enum /*_format*/, bool /*_yflip*/) override
		{
			BX_TRACE("Warning: using capture without callback (a.k.a. pointless).");
		}

		virtual void captureEnd() override
		{
		}

		virtual void captureFrame(const void* /*_data*/, uint32_t /*_size*/) override
		{
		}
	};

#ifndef BGFX_CONFIG_MEMORY_TRACKING
#	define BGFX_CONFIG_MEMORY_TRACKING (BGFX_CONFIG_DEBUG && BX_CONFIG_SUPPORTS_THREADING)
#endif // BGFX_CONFIG_MEMORY_TRACKING

	const size_t kNaturalAlignment = 8;

	class AllocatorStub : public bx::AllocatorI
	{
	public:
		AllocatorStub()
#if BGFX_CONFIG_MEMORY_TRACKING
			: m_numBlocks(0)
			, m_maxBlocks(0)
#endif // BGFX_CONFIG_MEMORY_TRACKING
		{
		}

		virtual void* realloc(void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line) override
		{
			if (0 == _size)
			{
				if (NULL != _ptr)
				{
					if (kNaturalAlignment >= _align)
					{
#if BGFX_CONFIG_MEMORY_TRACKING
						{
							bx::MutexScope scope(m_mutex);
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

				return NULL;
			}
			else if (NULL == _ptr)
			{
				if (kNaturalAlignment >= _align)
				{
#if BGFX_CONFIG_MEMORY_TRACKING
					{
						bx::MutexScope scope(m_mutex);
						++m_numBlocks;
						m_maxBlocks = bx::uint32_max(m_maxBlocks, m_numBlocks);
					}
#endif // BGFX_CONFIG_MEMORY_TRACKING

					return ::malloc(_size);
				}

				return bx::alignedAlloc(this, _size, _align, _file, _line);
			}

			if (kNaturalAlignment >= _align)
			{
#if BGFX_CONFIG_MEMORY_TRACKING
				if (NULL == _ptr)
				{
					bx::MutexScope scope(m_mutex);
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
		bx::Mutex m_mutex;
		uint32_t m_numBlocks;
		uint32_t m_maxBlocks;
#endif // BGFX_CONFIG_MEMORY_TRACKING
	};

	static CallbackStub*  s_callbackStub  = NULL;
	static AllocatorStub* s_allocatorStub = NULL;
	static bool s_graphicsDebuggerPresent = false;

	CallbackI* g_callback = NULL;
	bx::AllocatorI* g_allocator = NULL;

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
	InternalData g_internalData;
	PlatformData g_platformData;
	bool g_platformDataChangedSinceReset = false;

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

	void setPlatformData(const PlatformData& _data)
	{
		if (NULL != s_ctx)
		{
			BGFX_FATAL(true
				&& g_platformData.ndt     == _data.ndt
				&& g_platformData.context == _data.context
				, Fatal::UnableToInitialize
				, "Only backbuffer pointer and native window handle can be changed after initialization!"
				);
		}
		bx::memCopy(&g_platformData, &_data, sizeof(PlatformData) );
		g_platformDataChangedSinceReset = true;
	}

	const InternalData* getInternalData()
	{
		BGFX_CHECK_RENDER_THREAD();
		return &g_internalData;
	}

	uintptr_t overrideInternal(TextureHandle _handle, uintptr_t _ptr)
	{
		BGFX_CHECK_RENDER_THREAD();
		RendererContextI* rci = s_ctx->m_renderCtx;
		if (0 == rci->getInternal(_handle) )
		{
			return 0;
		}

		rci->overrideInternal(_handle, _ptr);

		return rci->getInternal(_handle);
	}

	uintptr_t overrideInternal(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint32_t _flags)
	{
		BGFX_CHECK_RENDER_THREAD();
		RendererContextI* rci = s_ctx->m_renderCtx;
		if (0 == rci->getInternal(_handle) )
		{
			return 0;
		}

		uint32_t size = sizeof(uint32_t) + sizeof(TextureCreate);
		Memory* mem = const_cast<Memory*>(alloc(size) );

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic);

		TextureCreate tc;
		tc.m_width     = _width;
		tc.m_height    = _height;
		tc.m_depth     = 0;
		tc.m_numLayers = 1;
		tc.m_numMips   = uint8_t(bx::uint16_max(1, _numMips) );
		tc.m_format    = _format;
		tc.m_cubeMap   = false;
		tc.m_mem       = NULL;
		bx::write(&writer, tc);

		rci->destroyTexture(_handle);
		rci->createTexture(_handle, mem, _flags, 0);

		release(mem);

		return rci->getInternal(_handle);
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
		va_list argList;
		va_start(argList, _format);

		if (BX_UNLIKELY(NULL == g_callback) )
		{
			bx::debugPrintfVargs(_format, argList);
			abort();
		}
		else
		{
			char temp[8192];
			char* out = temp;
			int32_t len = bx::vsnprintf(out, sizeof(temp), _format, argList);
			if ( (int32_t)sizeof(temp) < len)
			{
				out = (char*)alloca(len+1);
				len = bx::vsnprintf(out, len, _format, argList);
			}
			out[len] = '\0';

			g_callback->fatal(_code, out);
		}

		va_end(argList);
	}

	void trace(const char* _filePath, uint16_t _line, const char* _format, ...)
	{
		va_list argList;
		va_start(argList, _format);

		if (BX_UNLIKELY(NULL == g_callback) )
		{
			bx::debugPrintfVargs(_format, argList);
		}
		else
		{
			g_callback->traceVargs(_filePath, _line, _format, argList);
		}

		va_end(argList);
	}

#include "vs_debugfont.bin.h"
#include "fs_debugfont.bin.h"
#include "vs_clear.bin.h"
#include "fs_clear0.bin.h"
#include "fs_clear1.bin.h"
#include "fs_clear2.bin.h"
#include "fs_clear3.bin.h"
#include "fs_clear4.bin.h"
#include "fs_clear5.bin.h"
#include "fs_clear6.bin.h"
#include "fs_clear7.bin.h"

	static const EmbeddedShader s_embeddedShaders[] =
	{
		BGFX_EMBEDDED_SHADER(vs_debugfont),
		BGFX_EMBEDDED_SHADER(fs_debugfont),
		BGFX_EMBEDDED_SHADER(vs_clear),
		BGFX_EMBEDDED_SHADER(fs_clear0),
		BGFX_EMBEDDED_SHADER(fs_clear1),
		BGFX_EMBEDDED_SHADER(fs_clear2),
		BGFX_EMBEDDED_SHADER(fs_clear3),
		BGFX_EMBEDDED_SHADER(fs_clear4),
		BGFX_EMBEDDED_SHADER(fs_clear5),
		BGFX_EMBEDDED_SHADER(fs_clear6),
		BGFX_EMBEDDED_SHADER(fs_clear7),

		BGFX_EMBEDDED_SHADER_END()
	};

	ShaderHandle createEmbeddedShader(const EmbeddedShader* _es, RendererType::Enum _type, const char* _name)
	{
		for (const EmbeddedShader* es = _es; NULL != es->name; ++es)
		{
			if (0 == bx::strCmp(_name, es->name) )
			{
				for (const EmbeddedShader::Data* esd = es->data; RendererType::Count != esd->type; ++esd)
				{
					if (_type == esd->type
					&&  1 < esd->size)
					{
						ShaderHandle handle = createShader(makeRef(esd->data, esd->size) );
						if (isValid(handle) )
						{
							setName(handle, _name);
						}

						return handle;
					}
				}
			}
		}

		ShaderHandle handle = BGFX_INVALID_HANDLE;
		return handle;
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
					bx::memSet(&pix[xx*_bpp], _charset[ii*_height+yy]&bit ? 255 : 0, _bpp);
				}

				pix += _pitch;
			}
		}
	}

	static uint8_t parseAttrTo(char*& _ptr, char _to, uint8_t _default)
	{
		const char* str = bx::strFind(_ptr, _to);
		if (NULL != str
		&&  3 > str-_ptr)
		{
			char tmp[4];

			int32_t len = int32_t(str-_ptr);
			bx::strCopy(tmp, sizeof(tmp), _ptr, len);

			uint8_t attr = uint8_t(atoi(tmp) );
			_ptr += len+1;
			return attr;
		}

		return _default;
	}

	static uint8_t parseAttr(char*& _ptr, uint8_t _default)
	{
		char* ptr = _ptr;
		if (*ptr++ != '[')
		{
			return _default;
		}

		if (0 == bx::strCmp(ptr, "0m", 2) )
		{
			_ptr = ptr + 2;
			return _default;
		}

		uint8_t fg = parseAttrTo(ptr, ';', _default & 0xf);
		uint8_t bg = parseAttrTo(ptr, 'm', _default >> 4);

		uint8_t attr = (bg<<4) | fg;
		_ptr = ptr;
		return attr;
	}

	void TextVideoMem::printfVargs(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList)
	{
		if (_x < m_width && _y < m_height)
		{
			va_list argListCopy;
			va_copy(argListCopy, _argList);
			uint32_t num = bx::vsnprintf(NULL, 0, _format, argListCopy) + 1;
			char* temp = (char*)alloca(num);
			va_copy(argListCopy, _argList);
			num = bx::vsnprintf(temp, num, _format, argListCopy);

			uint8_t attr = _attr;
			uint8_t* mem = &m_mem[(_y*m_width+_x)*2];
			for (uint32_t ii = 0, xx = _x; ii < num && xx < m_width; ++ii)
			{
				char ch = temp[ii];
				if (BX_UNLIKELY(ch == '\x1b') )
				{
					char* ptr = &temp[ii+1];
					attr = parseAttr(ptr, _attr);
					ii += uint32_t(ptr - &temp[ii+1]);
				}
				else
				{
					mem[0] = ch;
					mem[1] = attr;
					mem += 2;
					++xx;
				}
			}
		}
	}

	static const uint32_t numCharsPerBatch = 1024;
	static const uint32_t numBatchVertices = numCharsPerBatch*4;
	static const uint32_t numBatchIndices  = numCharsPerBatch*6;

	void TextVideoMemBlitter::init()
	{
		BGFX_CHECK_API_THREAD();
		m_decl
			.begin()
			.add(Attrib::Position,  3, AttribType::Float)
			.add(Attrib::Color0,    4, AttribType::Uint8, true)
			.add(Attrib::Color1,    4, AttribType::Uint8, true)
			.add(Attrib::TexCoord0, 2, AttribType::Float)
			.end();

		uint16_t width  = 2048;
		uint16_t height = 24;
		uint8_t  bpp    = 1;
		uint32_t pitch  = width*bpp;

		const Memory* mem;

		mem = alloc(pitch*height);
		uint8_t* rgba = mem->data;
		charsetFillTexture(vga8x8, rgba, 8, pitch, bpp);
		charsetFillTexture(vga8x16, &rgba[8*pitch], 16, pitch, bpp);
		m_texture = createTexture2D(width, height, false, 1, TextureFormat::R8
						, BGFX_TEXTURE_MIN_POINT
						| BGFX_TEXTURE_MAG_POINT
						| BGFX_TEXTURE_MIP_POINT
						| BGFX_TEXTURE_U_CLAMP
						| BGFX_TEXTURE_V_CLAMP
						, mem
						);

		ShaderHandle vsh = createEmbeddedShader(s_embeddedShaders, g_caps.rendererType, "vs_debugfont");
		ShaderHandle fsh = createEmbeddedShader(s_embeddedShaders, g_caps.rendererType, "fs_debugfont");

		m_program = createProgram(vsh, fsh, true);

		m_vb = s_ctx->createTransientVertexBuffer(numBatchVertices*m_decl.m_stride, &m_decl);
		m_ib = s_ctx->createTransientIndexBuffer(numBatchIndices*2);
	}

	void TextVideoMemBlitter::shutdown()
	{
		BGFX_CHECK_API_THREAD();

		if (isValid(m_program) )
		{
			destroy(m_program);
		}

		destroy(m_texture);
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

						bx::memCopy(vertex, vert, sizeof(vert) );
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
		BGFX_CHECK_API_THREAD();

		if (RendererType::Noop != g_caps.rendererType)
		{
			m_decl
				.begin()
				.add(Attrib::Position, 3, AttribType::Float)
				.end();

			ShaderHandle vsh = createEmbeddedShader(s_embeddedShaders, g_caps.rendererType, "vs_clear");

			for (uint32_t ii = 0, num = g_caps.limits.maxFBAttachments; ii < num; ++ii)
			{
				char name[32];
				bx::snprintf(name, BX_COUNTOF(name), "fs_clear%d", ii);
				ShaderHandle fsh = createEmbeddedShader(s_embeddedShaders, g_caps.rendererType, name);

				m_program[ii] = createProgram(vsh, fsh);
				BX_CHECK(isValid(m_program[ii]), "Failed to create clear quad program.");
				destroy(fsh);
			}

			destroy(vsh);

			m_vb = s_ctx->createTransientVertexBuffer(4*m_decl.m_stride, &m_decl);
		}
	}

	void ClearQuad::shutdown()
	{
		BGFX_CHECK_API_THREAD();

		if (RendererType::Noop != g_caps.rendererType)
		{
			for (uint32_t ii = 0, num = g_caps.limits.maxFBAttachments; ii < num; ++ii)
			{
				if (isValid(m_program[ii]) )
				{
					destroy(m_program[ii]);
					m_program[ii].idx = kInvalidHandle;
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
			&&  0 == bx::strCmp(_name, s_uniformTypeName[ii]) )
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
			if (0 == bx::strCmp(_name, s_predefinedName[ii]) )
			{
				return PredefinedUniform::Enum(ii);
			}
		}

		return PredefinedUniform::Count;
	}

	void EncoderImpl::submit(ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, int32_t _depth, bool _preserveState)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM)
		&& !_preserveState)
		{
			m_uniformSet.clear();
		}

		if (BX_ENABLED(BGFX_CONFIG_DEBUG_OCCLUSION)
		&&  isValid(_occlusionQuery) )
		{
			BX_CHECK(m_occlusionQuerySet.end() == m_occlusionQuerySet.find(_occlusionQuery.idx)
				, "OcclusionQuery %d was already used for this frame."
				, _occlusionQuery.idx
				);
			m_occlusionQuerySet.insert(_occlusionQuery.idx);
		}

		if (m_discard)
		{
			discard();
			return;
		}

		if (0 == m_draw.m_numVertices
		&&  0 == m_draw.m_numIndices)
		{
			discard();
			++m_numDropped;
			return;
		}

		const uint32_t renderItemIdx = bx::atomicFetchAndAddsat<uint32_t>(&m_frame->m_numRenderItems, 1, BGFX_CONFIG_MAX_DRAW_CALLS);
		if (BGFX_CONFIG_MAX_DRAW_CALLS-1 <= renderItemIdx)
		{
			discard();
			++m_numDropped;
			return;
		}

		++m_numSubmitted;

		UniformBuffer* uniformBuffer = m_frame->m_uniformBuffer[m_uniformIdx];
		m_uniformEnd = uniformBuffer->getPos();

		m_key.m_program = kInvalidHandle == _program.idx
			? 0
			: _program.idx
			;

		m_key.m_view = _id;

		SortKey::Enum type = SortKey::SortProgram;
		switch (s_ctx->m_view[_id].m_mode)
		{
		case ViewMode::Sequential:      m_key.m_seq   = s_ctx->getSeqIncr(_id); type = SortKey::SortSequence; break;
		case ViewMode::DepthAscending:  m_key.m_depth = (uint32_t)_depth;       type = SortKey::SortDepth;    break;
		case ViewMode::DepthDescending: m_key.m_depth = (uint32_t)-_depth;      type = SortKey::SortDepth;    break;
		default: break;
		}

		uint64_t key = m_key.encodeDraw(type);

		m_frame->m_sortKeys[renderItemIdx]   = key;
		m_frame->m_sortValues[renderItemIdx] = RenderItemCount(renderItemIdx);

		m_draw.m_uniformIdx   = m_uniformIdx;
		m_draw.m_uniformBegin = m_uniformBegin;
		m_draw.m_uniformEnd   = m_uniformEnd;

		uint32_t numVertices = UINT32_MAX;
		for (uint32_t idx = 0, streamMask = m_draw.m_streamMask, ntz = bx::uint32_cnttz(streamMask)
			; 0 != streamMask
			; streamMask >>= 1, idx += 1, ntz = bx::uint32_cnttz(streamMask)
			)
		{
			streamMask >>= ntz;
			idx         += ntz;
			numVertices = bx::uint32_min(numVertices, m_numVertices[idx]);
		}
		m_draw.m_numVertices = numVertices;

		if (isValid(_occlusionQuery) )
		{
			m_draw.m_stateFlags |= BGFX_STATE_INTERNAL_OCCLUSION_QUERY;
			m_draw.m_occlusionQuery = _occlusionQuery;
		}

		m_frame->m_renderItem[renderItemIdx].draw = m_draw;
		m_frame->m_renderItemBind[renderItemIdx]  = m_bind;

		if (!_preserveState)
		{
			m_draw.clear();
			m_bind.clear();
			m_uniformBegin = m_uniformEnd;
		}
	}

	void EncoderImpl::dispatch(ViewId _id, ProgramHandle _handle, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
		{
			m_uniformSet.clear();
		}

		if (m_discard)
		{
			discard();
			return;
		}

		const uint32_t renderItemIdx = bx::atomicFetchAndAddsat<uint32_t>(&m_frame->m_numRenderItems, 1, BGFX_CONFIG_MAX_DRAW_CALLS);
		if (BGFX_CONFIG_MAX_DRAW_CALLS-1 <= renderItemIdx)
		{
			discard();
			++m_numDropped;
			return;
		}

		++m_numSubmitted;

		UniformBuffer* uniformBuffer = m_frame->m_uniformBuffer[m_uniformIdx];
		m_uniformEnd = uniformBuffer->getPos();

		m_compute.m_startMatrix = m_draw.m_startMatrix;
		m_compute.m_numMatrices = m_draw.m_numMatrices;
		m_compute.m_numX   = bx::uint32_max(_numX, 1);
		m_compute.m_numY   = bx::uint32_max(_numY, 1);
		m_compute.m_numZ   = bx::uint32_max(_numZ, 1);
		m_compute.m_submitFlags = _flags;

		m_key.m_program = _handle.idx;
		m_key.m_depth   = 0;
		m_key.m_view    = _id;
		m_key.m_seq     = s_ctx->getSeqIncr(_id);

		uint64_t key = m_key.encodeCompute();
		m_frame->m_sortKeys[renderItemIdx]   = key;
		m_frame->m_sortValues[renderItemIdx] = RenderItemCount(renderItemIdx);

		m_compute.m_uniformIdx   = m_uniformIdx;
		m_compute.m_uniformBegin = m_uniformBegin;
		m_compute.m_uniformEnd   = m_uniformEnd;
		m_frame->m_renderItem[renderItemIdx].compute = m_compute;
		m_frame->m_renderItemBind[renderItemIdx]     = m_bind;

		m_compute.clear();
		m_bind.clear();
		m_uniformBegin = m_uniformEnd;
	}

	void EncoderImpl::blit(ViewId _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
	{
		BX_WARN(m_frame->m_numBlitItems < BGFX_CONFIG_MAX_BLIT_ITEMS
			, "Exceed number of available blit items per frame. BGFX_CONFIG_MAX_BLIT_ITEMS is %d. Skipping blit."
			, BGFX_CONFIG_MAX_BLIT_ITEMS
			);
		if (m_frame->m_numBlitItems < BGFX_CONFIG_MAX_BLIT_ITEMS)
		{
			uint16_t item = m_frame->m_numBlitItems++;

			BlitItem& bi = m_frame->m_blitItem[item];
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
			m_frame->m_blitKeys[item] = key.encode();
		}
	}

	void Frame::sort()
	{
		BGFX_PROFILER_SCOPE("bgfx/Sort", 0xff2040ff);

		ViewId viewRemap[BGFX_CONFIG_MAX_VIEWS];
		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			viewRemap[m_viewRemap[ii] ] = ViewId(ii);
		}

		for (uint32_t ii = 0, num = m_numRenderItems; ii < num; ++ii)
		{
			m_sortKeys[ii] = SortKey::remapView(m_sortKeys[ii], viewRemap);
		}
		bx::radixSort(m_sortKeys, s_ctx->m_tempKeys, m_sortValues, s_ctx->m_tempValues, m_numRenderItems);

		for (uint32_t ii = 0, num = m_numBlitItems; ii < num; ++ii)
		{
			m_blitKeys[ii] = BlitKey::remapView(m_blitKeys[ii], viewRemap);
		}
		bx::radixSort(m_blitKeys, (uint32_t*)&s_ctx->m_tempKeys, m_numBlitItems);
	}

	RenderFrame::Enum renderFrame(int32_t _msecs)
	{
		if (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) )
		{
			if (NULL == s_ctx)
			{
				s_renderFrameCalled = true;
				s_threadIndex = ~BGFX_API_THREAD_MAGIC;
				return RenderFrame::NoContext;
			}

			BGFX_CHECK_RENDER_THREAD();
			int32_t msecs = -1 == _msecs
				? BGFX_CONFIG_API_SEMAPHORE_TIMEOUT
				: _msecs
				;
			RenderFrame::Enum result = s_ctx->renderFrame(msecs);
			if (RenderFrame::Exiting == result)
			{
				Context* ctx = s_ctx;
				ctx->apiSemWait();
				s_ctx = NULL;
				ctx->renderSemPost();
			}

			return result;
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
		uint16_t num = (uint16_t)bx::strLen(_marker)+1;
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
		CAPS_FLAGS(BGFX_CAPS_ALPHA_TO_COVERAGE),
		CAPS_FLAGS(BGFX_CAPS_BLEND_INDEPENDENT),
		CAPS_FLAGS(BGFX_CAPS_COMPUTE),
		CAPS_FLAGS(BGFX_CAPS_CONSERVATIVE_RASTER),
		CAPS_FLAGS(BGFX_CAPS_DRAW_INDIRECT),
		CAPS_FLAGS(BGFX_CAPS_FRAGMENT_DEPTH),
		CAPS_FLAGS(BGFX_CAPS_FRAGMENT_ORDERING),
		CAPS_FLAGS(BGFX_CAPS_GRAPHICS_DEBUGGER),
		CAPS_FLAGS(BGFX_CAPS_HIDPI),
		CAPS_FLAGS(BGFX_CAPS_HMD),
		CAPS_FLAGS(BGFX_CAPS_INDEX32),
		CAPS_FLAGS(BGFX_CAPS_INSTANCING),
		CAPS_FLAGS(BGFX_CAPS_OCCLUSION_QUERY),
		CAPS_FLAGS(BGFX_CAPS_RENDERER_MULTITHREADED),
		CAPS_FLAGS(BGFX_CAPS_SWAP_CHAIN),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_2D_ARRAY),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_3D),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_BLIT),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_COMPARE_ALL),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_COMPARE_LEQUAL),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_CUBE_ARRAY),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_DIRECT_ACCESS),
		CAPS_FLAGS(BGFX_CAPS_TEXTURE_READ_BACK),
		CAPS_FLAGS(BGFX_CAPS_VERTEX_ATTRIB_HALF),
		CAPS_FLAGS(BGFX_CAPS_VERTEX_ATTRIB_UINT10),
#undef CAPS_FLAGS
	};

	static void dumpCaps()
	{
		BX_TRACE("");

		if (0 < g_caps.numGPUs)
		{
			BX_TRACE("Detected GPUs (%d):", g_caps.numGPUs);
			BX_TRACE("\t +----------------   Index");
			BX_TRACE("\t |  +-------------   Device ID");
			BX_TRACE("\t |  |    +--------   Vendor ID");
			for (uint32_t ii = 0; ii < g_caps.numGPUs; ++ii)
			{
				const Caps::GPU& gpu = g_caps.gpu[ii];
				BX_UNUSED(gpu);

				BX_TRACE("\t %d: %04x %04x"
					, ii
					, gpu.deviceId
					, gpu.vendorId
					);
			}

			BX_TRACE("");
		}

		RendererType::Enum renderers[RendererType::Count];
		uint8_t num = getSupportedRenderers(BX_COUNTOF(renderers), renderers);

		BX_TRACE("Supported renderer backends (%d):", num);
		for (uint32_t ii = 0; ii < num; ++ii)
		{
			BX_TRACE("\t - %s", getRendererName(renderers[ii]) );
		}

		BX_TRACE("");
		BX_TRACE("Sort key masks:");
		BX_TRACE("\t   View     %016" PRIx64, SORT_KEY_VIEW_MASK);
		BX_TRACE("\t   Draw bit %016" PRIx64, SORT_KEY_DRAW_BIT);

		BX_TRACE("");
		BX_TRACE("\tD  Type     %016" PRIx64, SORT_KEY_DRAW_TYPE_MASK);

		BX_TRACE("");
		BX_TRACE("\tD0 Trans    %016" PRIx64, SORT_KEY_DRAW_0_TRANS_MASK);
		BX_TRACE("\tD0 Program  %016" PRIx64, SORT_KEY_DRAW_0_PROGRAM_MASK);
		BX_TRACE("\tD0 Depth    %016" PRIx64, SORT_KEY_DRAW_0_DEPTH_MASK);

		BX_TRACE("");
		BX_TRACE("\tD1 Depth    %016" PRIx64, SORT_KEY_DRAW_1_DEPTH_MASK);
		BX_TRACE("\tD1 Trans    %016" PRIx64, SORT_KEY_DRAW_1_TRANS_MASK);
		BX_TRACE("\tD1 Program  %016" PRIx64, SORT_KEY_DRAW_1_PROGRAM_MASK);

		BX_TRACE("");
		BX_TRACE("\tD2 Seq      %016" PRIx64, SORT_KEY_DRAW_2_SEQ_MASK);
		BX_TRACE("\tD2 Trans    %016" PRIx64, SORT_KEY_DRAW_2_TRANS_MASK);
		BX_TRACE("\tD2 Program  %016" PRIx64, SORT_KEY_DRAW_2_PROGRAM_MASK);

		BX_TRACE("");
		BX_TRACE("\t C Seq      %016" PRIx64, SORT_KEY_COMPUTE_SEQ_MASK);
		BX_TRACE("\t C Program  %016" PRIx64, SORT_KEY_COMPUTE_PROGRAM_MASK);

		BX_TRACE("");
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

		BX_TRACE("");
		BX_TRACE("Limits:");
#define LIMITS(_x) BX_TRACE("\t%-24s %d", #_x, g_caps.limits._x)
		LIMITS(maxDrawCalls);
		LIMITS(maxBlits);
		LIMITS(maxTextureSize);
		LIMITS(maxViews);
		LIMITS(maxFrameBuffers);
		LIMITS(maxFBAttachments);
		LIMITS(maxPrograms);
		LIMITS(maxShaders);
		LIMITS(maxTextures);
		LIMITS(maxTextureSamplers);
		LIMITS(maxVertexDecls);
		LIMITS(maxVertexStreams);
		LIMITS(maxIndexBuffers);
		LIMITS(maxVertexBuffers);
		LIMITS(maxDynamicIndexBuffers);
		LIMITS(maxDynamicVertexBuffers);
		LIMITS(maxUniforms);
		LIMITS(maxOcclusionQueries);
		LIMITS(maxEncoders);
#undef LIMITS

		BX_TRACE("");
		BX_TRACE("Supported texture formats:");
		BX_TRACE("\t +----------------   2D: x = supported / * = emulated");
		BX_TRACE("\t |+---------------   2D: sRGB format");
		BX_TRACE("\t ||+--------------   3D: x = supported / * = emulated");
		BX_TRACE("\t |||+-------------   3D: sRGB format");
		BX_TRACE("\t ||||+------------ Cube: x = supported / * = emulated");
		BX_TRACE("\t |||||+----------- Cube: sRGB format");
		BX_TRACE("\t ||||||+---------- vertex format");
		BX_TRACE("\t |||||||+--------- image");
		BX_TRACE("\t ||||||||+-------- framebuffer");
		BX_TRACE("\t |||||||||+------- MSAA framebuffer");
		BX_TRACE("\t ||||||||||+------ MSAA texture");
		BX_TRACE("\t |||||||||||+----- Auto-generated mips");
		BX_TRACE("\t ||||||||||||  +-- name");
		for (uint32_t ii = 0; ii < TextureFormat::Count; ++ii)
		{
			if (TextureFormat::Unknown != ii
			&&  TextureFormat::UnknownDepth != ii)
			{
				uint16_t flags = g_caps.formats[ii];
				BX_TRACE("\t[%c%c%c%c%c%c%c%c%c%c%c%c] %s"
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
					, flags&BGFX_CAPS_FORMAT_TEXTURE_MIP_AUTOGEN      ? 'M' : ' '
					, getName(TextureFormat::Enum(ii) )
					);
				BX_UNUSED(flags);
			}
		}

		BX_TRACE("");
		BX_TRACE("NDC depth [%d, 1], origin %s left."
			, g_caps.homogeneousDepth ? -1 : 0
			, g_caps.originBottomLeft ? "bottom" : "top"
			);

		BX_TRACE("");
	}

	TextureFormat::Enum getViableTextureFormat(const bimg::ImageContainer& _imageContainer)
	{
		const uint32_t formatCaps = g_caps.formats[_imageContainer.m_format];
		bool convert = 0 == formatCaps;

		if (_imageContainer.m_cubeMap)
		{
			convert |= 0 == (formatCaps & BGFX_CAPS_FORMAT_TEXTURE_CUBE)
					&& 0 != (formatCaps & BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED)
					;
		}
		else if (_imageContainer.m_depth > 1)
		{
			convert |= 0 == (formatCaps & BGFX_CAPS_FORMAT_TEXTURE_3D)
					&& 0 != (formatCaps & BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED)
					;
		}
		else
		{
			convert |= 0 == (formatCaps & BGFX_CAPS_FORMAT_TEXTURE_2D)
					&& 0 != (formatCaps & BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED)
					;
		}

		if (convert)
		{
			return TextureFormat::BGRA8;
		}

		return TextureFormat::Enum(_imageContainer.m_format);
	}

	const char* getName(TextureFormat::Enum _fmt)
	{
		return bimg::getName(bimg::TextureFormat::Enum(_fmt));
	}

	const char* getName(UniformHandle _handle)
	{
		return s_ctx->m_uniformRef[_handle.idx].m_name.getPtr();
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
		TextureFormat::PTC12,
		TextureFormat::PTC14,
		TextureFormat::PTC12A,
		TextureFormat::PTC14A,
		TextureFormat::PTC22,
		TextureFormat::PTC24,
		TextureFormat::BGRA8, // GL doesn't support BGRA8 without extensions.
		TextureFormat::RGBA8, // D3D9 doesn't support RGBA8
	};

	bool Context::init(RendererType::Enum _type)
	{
		BX_CHECK(!m_rendererInitialized, "Already initialized?");

		m_exit    = false;
		m_flipped = true;
		m_frames  = 0;
		m_debug   = BGFX_DEBUG_NONE;
		m_frameTimeLast = bx::getHPCounter();

		m_submit->create();

#if BGFX_CONFIG_MULTITHREADED
		m_render->create();

		if (s_renderFrameCalled)
		{
			// When bgfx::renderFrame is called before init render thread
			// should not be created.
			BX_TRACE("Application called bgfx::renderFrame directly, not creating render thread.");
			m_singleThreaded = true
				&& ~BGFX_API_THREAD_MAGIC == s_threadIndex
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

		s_threadIndex = BGFX_API_THREAD_MAGIC;

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_viewRemap); ++ii)
		{
			m_viewRemap[ii] = ViewId(ii);
		}

		for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
		{
			resetView(ViewId(ii) );
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

		uint16_t idx = m_encoderHandle.alloc();
		BX_CHECK(0 == idx, "Internal encoder handle is not 0 (idx %d).", idx); BX_UNUSED(idx);
		m_encoder[0].begin(m_submit, 0);
		m_encoder0 = reinterpret_cast<Encoder*>(&m_encoder[0]);

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
			g_caps.formats[fmt] |= 0 == (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_2D  ) ? BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED   : 0;
			g_caps.formats[fmt] |= 0 == (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_3D  ) ? BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED   : 0;
			g_caps.formats[fmt] |= 0 == (g_caps.formats[fmt] & BGFX_CAPS_FORMAT_TEXTURE_CUBE) ? BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED : 0;
		}

		for (uint32_t ii = 0; ii < TextureFormat::UnknownDepth; ++ii)
		{
			bool convertable = bimg::imageConvert(bimg::TextureFormat::BGRA8, bimg::TextureFormat::Enum(ii) );
			g_caps.formats[ii] |= 0 == (g_caps.formats[ii] & BGFX_CAPS_FORMAT_TEXTURE_2D  ) && convertable ? BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED   : 0;
			g_caps.formats[ii] |= 0 == (g_caps.formats[ii] & BGFX_CAPS_FORMAT_TEXTURE_3D  ) && convertable ? BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED   : 0;
			g_caps.formats[ii] |= 0 == (g_caps.formats[ii] & BGFX_CAPS_FORMAT_TEXTURE_CUBE) && convertable ? BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED : 0;
		}

		g_caps.rendererType = m_renderCtx->getRendererType();
		initAttribTypeSizeTable(g_caps.rendererType);

		g_caps.supported |= 0
			| (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) && !m_singleThreaded ? BGFX_CAPS_RENDERER_MULTITHREADED : 0)
			| (isGraphicsDebuggerPresent() ? BGFX_CAPS_GRAPHICS_DEBUGGER : 0)
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

		g_internalData.caps = getCaps();

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

		m_encoder[0].end(true);

		m_dynVertexBufferAllocator.compact();
		m_dynIndexBufferAllocator.compact();

		BX_CHECK(m_vertexDeclHandle.getNumHandles() == m_declRef.m_vertexDeclMap.getNumElements()
				, "VertexDeclRef mismatch, num handles %d, handles in hash map %d."
				, m_vertexDeclHandle.getNumHandles()
				, m_declRef.m_vertexDeclMap.getNumElements()
				);

		m_declRef.shutdown(m_vertexDeclHandle);

#if BGFX_CONFIG_MULTITHREADED
		// Render thread shutdown sequence.
		renderSemWait(); // Wait for previous frame.
		apiSemPost();   // OK to set context to NULL.
		// s_ctx is NULL here.
		renderSemWait(); // In RenderFrame::Exiting state.

		if (m_thread.isRunning() )
		{
			m_thread.shutdown();
		}

		m_render->destroy();
#endif // BGFX_CONFIG_MULTITHREADED

		bx::memSet(&g_internalData, 0, sizeof(InternalData) );
		s_ctx = NULL;

		m_submit->destroy();

		if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
		{
#define CHECK_HANDLE_LEAK(_handleAlloc)                                                               \
					BX_MACRO_BLOCK_BEGIN                                                              \
						if (0 != _handleAlloc.getNumHandles() )                                       \
						{                                                                             \
							BX_TRACE("LEAK: " #_handleAlloc " %d (max: %d)"                           \
								, _handleAlloc.getNumHandles()                                        \
								, _handleAlloc.getMaxHandles()                                        \
								);                                                                    \
							for (uint16_t ii = 0, num = _handleAlloc.getNumHandles(); ii < num; ++ii) \
							{                                                                         \
								BX_TRACE("\t%3d: %4d", ii, _handleAlloc.getHandleAt(ii) );            \
							}                                                                         \
						}                                                                             \
					BX_MACRO_BLOCK_END

#define CHECK_HANDLE_LEAK_NAME(_handleAlloc, _type, _ref)                                             \
					BX_MACRO_BLOCK_BEGIN                                                              \
						if (0 != _handleAlloc.getNumHandles() )                                       \
						{                                                                             \
							BX_TRACE("LEAK: " #_handleAlloc " %d (max: %d)"                           \
								, _handleAlloc.getNumHandles()                                        \
								, _handleAlloc.getMaxHandles()                                        \
								);                                                                    \
							for (uint16_t ii = 0, num = _handleAlloc.getNumHandles(); ii < num; ++ii) \
							{                                                                         \
								uint16_t idx = _handleAlloc.getHandleAt(ii);                          \
								const _type& ref = _ref[idx]; BX_UNUSED(ref);                         \
								BX_TRACE("\t%3d: %4d %s (count %d)"                                   \
										, ii                                                          \
										, idx                                                         \
										, ref.m_name.getPtr()                                         \
										, ref.m_refCount                                              \
										);                                                            \
							}                                                                         \
						}                                                                             \
					BX_MACRO_BLOCK_END

			CHECK_HANDLE_LEAK     (m_dynamicIndexBufferHandle                          );
			CHECK_HANDLE_LEAK     (m_dynamicVertexBufferHandle                         );
			CHECK_HANDLE_LEAK     (m_indexBufferHandle                                 );
			CHECK_HANDLE_LEAK     (m_vertexDeclHandle                                  );
			CHECK_HANDLE_LEAK     (m_vertexBufferHandle                                );
			CHECK_HANDLE_LEAK_NAME(m_shaderHandle,             ShaderRef,  m_shaderRef );
			CHECK_HANDLE_LEAK     (m_programHandle                                     );
			CHECK_HANDLE_LEAK_NAME(m_textureHandle,            TextureRef, m_textureRef);
			CHECK_HANDLE_LEAK     (m_frameBufferHandle                                 );
			CHECK_HANDLE_LEAK_NAME(m_uniformHandle,            UniformRef, m_uniformRef);
			CHECK_HANDLE_LEAK     (m_occlusionQueryHandle                              );
#undef CHECK_HANDLE_LEAK
#undef CHECK_HANDLE_LEAK_NAME
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

		for (uint16_t ii = 0, num = m_numFreeOcclusionQueryHandles; ii < num; ++ii)
		{
			m_occlusionQueryHandle.free(m_freeOcclusionQueryHandle[ii].idx);
		}
		m_numFreeOcclusionQueryHandles = 0;
	}

	void Context::freeAllHandles(Frame* _frame)
	{
		for (uint16_t ii = 0, num = _frame->m_freeIndexBuffer.getNumQueued(); ii < num; ++ii)
		{
			m_indexBufferHandle.free(_frame->m_freeIndexBuffer.get(ii).idx);
		}

		for (uint16_t ii = 0, num = _frame->m_freeVertexBuffer.getNumQueued(); ii < num; ++ii)
		{
			destroyVertexBufferInternal(_frame->m_freeVertexBuffer.get(ii));
		}

		for (uint16_t ii = 0, num = _frame->m_freeVertexDecl.getNumQueued(); ii < num; ++ii)
		{
			m_vertexDeclHandle.free(_frame->m_freeVertexDecl.get(ii).idx);
		}

		for (uint16_t ii = 0, num = _frame->m_freeShader.getNumQueued(); ii < num; ++ii)
		{
			m_shaderHandle.free(_frame->m_freeShader.get(ii).idx);
		}

		for (uint16_t ii = 0, num = _frame->m_freeProgram.getNumQueued(); ii < num; ++ii)
		{
			m_programHandle.free(_frame->m_freeProgram.get(ii).idx);
		}

		for (uint16_t ii = 0, num = _frame->m_freeTexture.getNumQueued(); ii < num; ++ii)
		{
			m_textureHandle.free(_frame->m_freeTexture.get(ii).idx);
		}

		for (uint16_t ii = 0, num = _frame->m_freeFrameBuffer.getNumQueued(); ii < num; ++ii)
		{
			m_frameBufferHandle.free(_frame->m_freeFrameBuffer.get(ii).idx);
		}

		for (uint16_t ii = 0, num = _frame->m_freeUniform.getNumQueued(); ii < num; ++ii)
		{
			m_uniformHandle.free(_frame->m_freeUniform.get(ii).idx);
		}
	}

	Encoder* Context::begin()
	{
		EncoderImpl* encoder = &m_encoder[0];

#if BGFX_CONFIG_MULTITHREADED
		if (BGFX_API_THREAD_MAGIC != s_threadIndex)
		{
			bx::MutexScope scopeLock(m_encoderApiLock);

			uint16_t idx = m_encoderHandle.alloc();
			if (kInvalidHandle == idx)
			{
				return NULL;
			}

			encoder = &m_encoder[idx];
			encoder->begin(m_submit, uint8_t(idx) );
		}
#endif // BGFX_CONFIG_MULTITHREADED

		return reinterpret_cast<Encoder*>(encoder);
	}

	void Context::end(Encoder* _encoder)
	{
#if BGFX_CONFIG_MULTITHREADED
		if (BGFX_API_THREAD_MAGIC != s_threadIndex)
		{
			EncoderImpl* encoder = reinterpret_cast<EncoderImpl*>(_encoder);
			encoder->end(true);

			m_encoderEndSem.post();
		}
#else
		BX_UNUSED(_encoder);
#endif // BGFX_CONFIG_MULTITHREADED
	}

	uint32_t Context::frame(bool _capture)
	{
		m_encoder[0].end(true);

#if BGFX_CONFIG_MULTITHREADED
		bx::MutexScope resourceApiScope(m_resourceApiLock);

		encoderApiWait();
		bx::MutexScope encoderApiScope(m_encoderApiLock);
#else
		encoderApiWait();
#endif // BGFX_CONFIG_MULTITHREADED

		m_submit->m_capture = _capture;

		BGFX_PROFILER_SCOPE("bgfx/API thread frame", 0xff2040ff);
		// wait for render thread to finish
		renderSemWait();
		frameNoRenderWait();

		m_encoder[0].begin(m_submit, 0);

		return m_frames;
	}

	void Context::frameNoRenderWait()
	{
		swap();

		// release render thread
		apiSemPost();
	}

	void Context::swap()
	{
		freeDynamicBuffers();
		m_submit->m_resolution = m_resolution;
		m_resolution.m_flags &= ~BGFX_RESET_INTERNAL_FORCE;
		m_submit->m_debug = m_debug;
		m_submit->m_perfStats.numViews = 0;

		bx::memCopy(m_submit->m_viewRemap, m_viewRemap, sizeof(m_viewRemap) );
		bx::memCopy(m_submit->m_view, m_view, sizeof(m_view) );

		if (m_colorPaletteDirty > 0)
		{
			--m_colorPaletteDirty;
			bx::memCopy(m_submit->m_colorPalette, m_clearColor, sizeof(m_clearColor) );
		}
		m_submit->finish();

		bx::xchg(m_render, m_submit);

		bx::memCopy(m_render->m_occlusion, m_submit->m_occlusion, sizeof(m_submit->m_occlusion) );

		if (!BX_ENABLED(BGFX_CONFIG_MULTITHREADED)
		||  m_singleThreaded)
		{
			renderFrame();
		}

		m_frames++;
		m_submit->start();

		bx::memSet(m_seq, 0, sizeof(m_seq) );
		freeAllHandles(m_submit);

		m_submit->resetFreeHandles();
		m_submit->m_textVideoMem->resize(m_render->m_textVideoMem->m_small
			, m_resolution.m_width
			, m_resolution.m_height
			);

		int64_t now = bx::getHPCounter();
		m_submit->m_perfStats.cpuTimeFrame = now - m_frameTimeLast;
		m_frameTimeLast = now;
	}

	///
	RendererContextI* rendererCreate(RendererType::Enum _type, const Init& _init);

	///
	void rendererDestroy(RendererContextI* _renderCtx);

	void Context::flip()
	{
		if (m_rendererInitialized
		&& !m_flipped)
		{
			m_renderCtx->flip(m_render->m_hmd);
			m_flipped = true;

			if (m_renderCtx->isDeviceRemoved() )
			{
				// Something horribly went wrong, fallback to noop renderer.
				rendererDestroy(m_renderCtx);

				Init init;
				m_renderCtx = rendererCreate(RendererType::Noop, init);
				g_caps.rendererType = RendererType::Noop;
			}
		}
	}

	RenderFrame::Enum Context::renderFrame(int32_t _msecs)
	{
		BGFX_PROFILER_SCOPE("bgfx::renderFrame", 0xff2040ff);

		if (!m_flipAfterRender)
		{
			BGFX_PROFILER_SCOPE("bgfx/flip", 0xff2040ff);
			flip();
		}

		if (apiSemWait(_msecs) )
		{
			{
				BGFX_PROFILER_SCOPE("bgfx/Exec commands pre", 0xff2040ff);
				rendererExecCommands(m_render->m_cmdPre);
			}

			if (m_rendererInitialized)
			{
				BGFX_PROFILER_SCOPE("bgfx/Render submit", 0xff2040ff);
				m_renderCtx->submit(m_render, m_clearQuad, m_textVideoMemBlitter);
				m_flipped = false;
			}

			{
				BGFX_PROFILER_SCOPE("bgfx/Exec commands post", 0xff2040ff);
				rendererExecCommands(m_render->m_cmdPost);
			}

			renderSemPost();

			if (m_flipAfterRender)
			{
				BGFX_PROFILER_SCOPE("bgfx/flip", 0xff2040ff);
				flip();
			}
		}
		else
		{
			return RenderFrame::Timeout;
		}

		return m_exit
			? RenderFrame::Exiting
			: RenderFrame::Render
			;
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

	typedef RendererContextI* (*RendererCreateFn)(const Init& _init);
	typedef void (*RendererDestroyFn)();

#define BGFX_RENDERER_CONTEXT(_namespace)                                   \
			namespace _namespace                                            \
			{                                                               \
				extern RendererContextI* rendererCreate(const Init& _init); \
				extern void rendererDestroy();                              \
			}

	BGFX_RENDERER_CONTEXT(noop);
	BGFX_RENDERER_CONTEXT(d3d9);
	BGFX_RENDERER_CONTEXT(d3d11);
	BGFX_RENDERER_CONTEXT(d3d12);
	BGFX_RENDERER_CONTEXT(mtl);
	BGFX_RENDERER_CONTEXT(gl);
	BGFX_RENDERER_CONTEXT(vk);
	BGFX_RENDERER_CONTEXT(gnm);

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
		{ noop::rendererCreate,  noop::rendererDestroy,  BGFX_RENDERER_NOOP_NAME,       true                              }, // Noop
		{ d3d9::rendererCreate,  d3d9::rendererDestroy,  BGFX_RENDERER_DIRECT3D9_NAME,  !!BGFX_CONFIG_RENDERER_DIRECT3D9  }, // Direct3D9
		{ d3d11::rendererCreate, d3d11::rendererDestroy, BGFX_RENDERER_DIRECT3D11_NAME, !!BGFX_CONFIG_RENDERER_DIRECT3D11 }, // Direct3D11
		{ d3d12::rendererCreate, d3d12::rendererDestroy, BGFX_RENDERER_DIRECT3D12_NAME, !!BGFX_CONFIG_RENDERER_DIRECT3D12 }, // Direct3D12
		{ gnm::rendererCreate,   gnm::rendererDestroy,   BGFX_RENDERER_GNM_NAME,        !!BGFX_CONFIG_RENDERER_GNM        }, // GNM
#if BX_PLATFORM_OSX || BX_PLATFORM_IOS
		{ mtl::rendererCreate,   mtl::rendererDestroy,   BGFX_RENDERER_METAL_NAME,      !!BGFX_CONFIG_RENDERER_METAL      }, // Metal
#else
		{ noop::rendererCreate,  noop::rendererDestroy,  BGFX_RENDERER_NOOP_NAME,       false                             }, // Noop
#endif // BX_PLATFORM_OSX || BX_PLATFORM_IOS
		{ gl::rendererCreate,    gl::rendererDestroy,    BGFX_RENDERER_OPENGL_NAME,     !!BGFX_CONFIG_RENDERER_OPENGLES   }, // OpenGLES
		{ gl::rendererCreate,    gl::rendererDestroy,    BGFX_RENDERER_OPENGL_NAME,     !!BGFX_CONFIG_RENDERER_OPENGL     }, // OpenGL
		{ vk::rendererCreate,    vk::rendererDestroy,    BGFX_RENDERER_VULKAN_NAME,     !!BGFX_CONFIG_RENDERER_VULKAN     }, // Vulkan
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_rendererCreator) == RendererType::Count);

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
		bx::memSet(&ovi, 0, sizeof(ovi) );
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

	static int32_t compareDescending(const void* _lhs, const void* _rhs)
	{
		return *(const int32_t*)_rhs - *(const int32_t*)_lhs;
	}

	RendererContextI* rendererCreate(RendererType::Enum _type, const Init& _init)
	{
		int32_t scores[RendererType::Count];
		uint32_t numScores = 0;

		for (uint32_t ii = 0; ii < RendererType::Count; ++ii)
		{
			RendererType::Enum renderer = RendererType::Enum(ii);
			if (s_rendererCreator[ii].supported)
			{
				int32_t score = 0;
				if (_type == renderer)
				{
					score += 1000;
				}

				score += RendererType::Noop != renderer ? 1 : 0;

				if (BX_ENABLED(BX_PLATFORM_WINDOWS) )
				{
					if (windowsVersionIs(Condition::GreaterEqual, 0x0602) )
					{
						score += RendererType::Direct3D11 == renderer ? 20 : 0;
						score += RendererType::Direct3D12 == renderer ? 10 : 0;
					}
					else if (windowsVersionIs(Condition::GreaterEqual, 0x0601) )
					{
						score += RendererType::Direct3D11 == renderer ?   20 : 0;
						score += RendererType::Direct3D9  == renderer ?   10 : 0;
						score += RendererType::Direct3D12 == renderer ? -100 : 0;
					}
					else
					{
						score += RendererType::Direct3D12 == renderer ? -100 : 0;
					}
				}
				else if (BX_ENABLED(BX_PLATFORM_LINUX) )
				{
					score += RendererType::OpenGL   == renderer ? 20 : 0;
					score += RendererType::OpenGLES == renderer ? 10 : 0;
				}
				else if (BX_ENABLED(BX_PLATFORM_OSX) )
				{
					score += RendererType::OpenGL   == renderer ? 20 : 0;
				}
				else if (BX_ENABLED(0
					 ||  BX_PLATFORM_ANDROID
					 ||  BX_PLATFORM_EMSCRIPTEN
					 ||  BX_PLATFORM_IOS
					 ||  BX_PLATFORM_RPI
					 ) )
				{
					score += RendererType::OpenGLES == renderer ? 20 : 0;
				}
				else if (BX_ENABLED(BX_PLATFORM_PS4) )
				{
					score += RendererType::Gnm      == renderer ? 20 : 0;
				}
				else if (BX_ENABLED(0
					 ||  BX_PLATFORM_XBOXONE
					 ||  BX_PLATFORM_WINRT
					 ) )
				{
					score += RendererType::Direct3D11 == renderer ? 20 : 0;
				}

				scores[numScores++] = (score<<8) | uint8_t(renderer);
			}
		}

		bx::quickSort(scores, numScores, sizeof(int32_t), compareDescending);

		RendererContextI* renderCtx = NULL;
		for (uint32_t ii = 0; ii < numScores; ++ii)
		{
			RendererType::Enum renderer = RendererType::Enum(scores[ii] & 0xff);
			renderCtx = s_rendererCreator[renderer].createFn(_init);
			if (NULL != renderCtx)
			{
				break;
			}

			s_rendererCreator[renderer].supported = false;
		}

		return renderCtx;
	}

	void rendererDestroy(RendererContextI* _renderCtx)
	{
		if (NULL != _renderCtx)
		{
			s_rendererCreator[_renderCtx->getRendererType()].destroyFn();
		}
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

					Init init;
					m_renderCtx = rendererCreate(type, init);

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

					rendererDestroy(m_renderCtx);
					m_renderCtx = NULL;

					m_exit = true;
				}
				BX_FALLTHROUGH;

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

					void* ptr = m_renderCtx->createTexture(handle, mem, flags, skip);
					if (NULL != ptr)
					{
						setDirectAccessPtr(handle, ptr);
					}

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

					uint8_t mip;
					_cmdbuf.read(mip);

					m_renderCtx->readTexture(handle, data, mip);
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

					uint8_t numMips;
					_cmdbuf.read(numMips);

					m_renderCtx->resizeTexture(handle, width, height, numMips);
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

						Attachment attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
						_cmdbuf.read(attachment, sizeof(Attachment) * num);

						m_renderCtx->createFrameBuffer(handle, num, attachment);
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

			case CommandBuffer::RequestScreenShot:
				{
					FrameBufferHandle handle;
					_cmdbuf.read(handle);

					uint16_t len;
					_cmdbuf.read(len);

					const char* filePath = (const char*)_cmdbuf.skip(len);

					m_renderCtx->requestScreenShot(handle, filePath);
				}
				break;

			case CommandBuffer::UpdateViewName:
				{
					ViewId id;
					_cmdbuf.read(id);

					uint16_t len;
					_cmdbuf.read(len);

					const char* name = (const char*)_cmdbuf.skip(len);

					m_renderCtx->updateViewName(id, name);
				}
				break;

			case CommandBuffer::InvalidateOcclusionQuery:
				{
					OcclusionQueryHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->invalidateOcclusionQuery(handle);
				}
				break;

			case CommandBuffer::SetName:
				{
					Handle handle;
					_cmdbuf.read(handle);

					uint16_t len;
					_cmdbuf.read(len);

					const char* name = (const char*)_cmdbuf.skip(len);

					m_renderCtx->setName(handle, name);
				}
				break;

			default:
				BX_CHECK(false, "Invalid command: %d", command);
				break;
			}
		} while (!end);

		flushTextureUpdateBatch(_cmdbuf);
	}

	uint32_t topologyConvert(TopologyConvert::Enum _conversion, void* _dst, uint32_t _dstSize, const void* _indices, uint32_t _numIndices, bool _index32)
	{
		return topologyConvert(_conversion, _dst, _dstSize, _indices, _numIndices, _index32, g_allocator);
	}

	void topologySortTriList(TopologySort::Enum _sort, void* _dst, uint32_t _dstSize, const float _dir[3], const float _pos[3], const void* _vertices, uint32_t _stride, const void* _indices, uint32_t _numIndices, bool _index32)
	{
		topologySortTriList(_sort, _dst, _dstSize, _dir, _pos, _vertices, _stride, _indices, _numIndices, _index32, g_allocator);
	}

	uint8_t getSupportedRenderers(uint8_t _max, RendererType::Enum* _enum)
	{
		_enum = _max == 0 ? NULL : _enum;

		uint8_t num = 0;
		for (uint8_t ii = 0; ii < RendererType::Count; ++ii)
		{
			if ( (RendererType::Direct3D11 == ii || RendererType::Direct3D12 == ii)
			&&  windowsVersionIs(Condition::LessEqual, 0x0502) )
			{
				continue;
			}

			if (NULL == _enum)
			{
				num++;
			}
			else
			{
				if (num < _max
				&&  s_rendererCreator[ii].supported)
				{
					_enum[num++] = RendererType::Enum(ii);
				}
			}
		}

		return num;
	}

	const char* getRendererName(RendererType::Enum _type)
	{
		BX_CHECK(_type < RendererType::Count, "Invalid renderer type %d.", _type);
		return s_rendererCreator[_type].name;
	}

	bool init(RendererType::Enum _type, uint16_t _vendorId, uint16_t _deviceId, CallbackI* _callback, bx::AllocatorI* _allocator)
	{
		if (NULL != s_ctx)
		{
			BX_TRACE("bgfx is already initialized.");
			return false;
		}

		struct ErrorState
		{
			enum Enum
			{
				Default,
				ContextAllocated,
			};
		};

		ErrorState::Enum errorState = ErrorState::Default;

		if (NULL != _allocator)
		{
			g_allocator = _allocator;
		}
		else
		{
			bx::DefaultAllocator allocator;
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

		if (true
		&&  !BX_ENABLED(BX_PLATFORM_EMSCRIPTEN || BX_PLATFORM_PS4)
		&&  RendererType::Noop != _type
		&&  NULL == g_platformData.ndt
		&&  NULL == g_platformData.nwh
		&&  NULL == g_platformData.context
		&&  NULL == g_platformData.backBuffer
		&&  NULL == g_platformData.backBufferDS
		   )
		{
			BX_TRACE("bgfx platform data like window handle or backbuffer must be set.");
			goto error;
		}

		bx::memSet(&g_caps, 0, sizeof(g_caps) );
		g_caps.limits.maxDrawCalls            = BGFX_CONFIG_MAX_DRAW_CALLS;
		g_caps.limits.maxBlits                = BGFX_CONFIG_MAX_BLIT_ITEMS;
		g_caps.limits.maxViews                = BGFX_CONFIG_MAX_VIEWS;
		g_caps.limits.maxFrameBuffers         = BGFX_CONFIG_MAX_FRAME_BUFFERS;
		g_caps.limits.maxPrograms             = BGFX_CONFIG_MAX_PROGRAMS;
		g_caps.limits.maxShaders              = BGFX_CONFIG_MAX_SHADERS;
		g_caps.limits.maxTextures             = BGFX_CONFIG_MAX_TEXTURES;
		g_caps.limits.maxTextureSamplers      = BGFX_CONFIG_MAX_TEXTURE_SAMPLERS;
		g_caps.limits.maxVertexDecls          = BGFX_CONFIG_MAX_VERTEX_DECLS;
		g_caps.limits.maxVertexStreams        = 1;
		g_caps.limits.maxIndexBuffers         = BGFX_CONFIG_MAX_INDEX_BUFFERS;
		g_caps.limits.maxVertexBuffers        = BGFX_CONFIG_MAX_VERTEX_BUFFERS;
		g_caps.limits.maxDynamicIndexBuffers  = BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS;
		g_caps.limits.maxDynamicVertexBuffers = BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS;
		g_caps.limits.maxUniforms             = BGFX_CONFIG_MAX_UNIFORMS;
		g_caps.limits.maxOcclusionQueries     = BGFX_CONFIG_MAX_OCCLUSION_QUERIES;
		g_caps.limits.maxFBAttachments        = 1;
		g_caps.limits.maxEncoders             = BGFX_CONFIG_MAX_ENCODERS;

		g_caps.vendorId = _vendorId;
		g_caps.deviceId = _deviceId;

		BX_TRACE("Init...");

		errorState = ErrorState::ContextAllocated;

		s_ctx = BX_ALIGNED_NEW(g_allocator, Context, 64);
		if (s_ctx->init(_type) )
		{
			BX_TRACE("Init complete.");
			return true;
		}

error:
		BX_TRACE("Init failed.");

		switch (errorState)
		{
		case ErrorState::ContextAllocated:
			BX_ALIGNED_DELETE(g_allocator, s_ctx, 64);
			s_ctx = NULL;

		case ErrorState::Default:
			if (NULL != s_callbackStub)
			{
				BX_DELETE(g_allocator, s_callbackStub);
				s_callbackStub = NULL;
			}

			if (NULL != s_allocatorStub)
			{
				bx::DefaultAllocator allocator;
				BX_DELETE(&allocator, s_allocatorStub);
				s_allocatorStub = NULL;
			}

			s_threadIndex = 0;
			g_callback    = NULL;
			g_allocator   = NULL;
			break;
		}

		return false;
	}

	void shutdown()
	{
		BX_TRACE("Shutdown...");

		BGFX_CHECK_API_THREAD();
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
			bx::DefaultAllocator allocator;
			BX_DELETE(&allocator, s_allocatorStub);
			s_allocatorStub = NULL;
		}

		s_threadIndex = 0;
		g_callback    = NULL;
		g_allocator   = NULL;
	}

	void reset(uint32_t _width, uint32_t _height, uint32_t _flags)
	{
		BGFX_CHECK_API_THREAD();
		BX_CHECK(0 == (_flags&BGFX_RESET_RESERVED_MASK), "Do not set reset reserved flags!");
		s_ctx->reset(_width, _height, _flags);
	}

	Encoder* begin()
	{
		return s_ctx->begin();
	}

#define BGFX_ENCODER(_func) reinterpret_cast<EncoderImpl*>(this)->_func

	void Encoder::setMarker(const char* _marker)
	{
		BGFX_ENCODER(setMarker(_marker) );
	}

	void Encoder::setState(uint64_t _state, uint32_t _rgba)
	{
		BX_CHECK(0 == (_state&BGFX_STATE_RESERVED_MASK), "Do not set state reserved flags!");
		BGFX_ENCODER(setState(_state, _rgba) );
	}

	void Encoder::setCondition(OcclusionQueryHandle _handle, bool _visible)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_OCCLUSION_QUERY, "Occlusion query is not supported!");
		BGFX_ENCODER(setCondition(_handle, _visible) );
	}

	void Encoder::setStencil(uint32_t _fstencil, uint32_t _bstencil)
	{
		BGFX_ENCODER(setStencil(_fstencil, _bstencil) );
	}

	uint16_t Encoder::setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		return BGFX_ENCODER(setScissor(_x, _y, _width, _height) );
	}

	void Encoder::setScissor(uint16_t _cache)
	{
		BGFX_ENCODER(setScissor(_cache) );
	}

	uint32_t Encoder::setTransform(const void* _mtx, uint16_t _num)
	{
		return BGFX_ENCODER(setTransform(_mtx, _num) );
	}

	uint32_t Encoder::allocTransform(Transform* _transform, uint16_t _num)
	{
		return BGFX_ENCODER(allocTransform(_transform, _num) );
	}

	void Encoder::setTransform(uint32_t _cache, uint16_t _num)
	{
		BGFX_ENCODER(setTransform(_cache, _num) );
	}

	void Encoder::setUniform(UniformHandle _handle, const void* _value, uint16_t _num)
	{
		BGFX_CHECK_HANDLE("setUniform", s_ctx->m_uniformHandle, _handle);
		const Context::UniformRef& uniform = s_ctx->m_uniformRef[_handle.idx];
		BX_CHECK(isValid(_handle) && 0 < uniform.m_refCount, "Setting invalid uniform (handle %3d)!", _handle.idx);
		BX_CHECK(_num == UINT16_MAX || uniform.m_num >= _num, "Truncated uniform update. %d (max: %d)", _num, uniform.m_num);
		BGFX_ENCODER(setUniform(uniform.m_type, _handle, _value, UINT16_MAX != _num ? _num : uniform.m_num) );
	}

	void Encoder::setIndexBuffer(IndexBufferHandle _handle)
	{
		setIndexBuffer(_handle, 0, UINT32_MAX);
	}

	void Encoder::setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_HANDLE("setIndexBuffer", s_ctx->m_indexBufferHandle, _handle);
		BGFX_ENCODER(setIndexBuffer(_handle, _firstIndex, _numIndices) );
	}

	void Encoder::setIndexBuffer(DynamicIndexBufferHandle _handle)
	{
		setIndexBuffer(_handle, 0, UINT32_MAX);
	}

	void Encoder::setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_HANDLE("setIndexBuffer", s_ctx->m_dynamicIndexBufferHandle, _handle);
		const DynamicIndexBuffer& dib = s_ctx->m_dynamicIndexBuffers[_handle.idx];
		BGFX_ENCODER(setIndexBuffer(dib, _firstIndex, _numIndices) );
	}

	void Encoder::setIndexBuffer(const TransientIndexBuffer* _tib)
	{
		setIndexBuffer(_tib, 0, UINT32_MAX);
	}

	void Encoder::setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BX_CHECK(NULL != _tib, "_tib can't be NULL");
		BGFX_CHECK_HANDLE("setIndexBuffer", s_ctx->m_indexBufferHandle, _tib->handle);
		BGFX_ENCODER(setIndexBuffer(_tib, _firstIndex, _numIndices) );
	}

	void Encoder::setVertexBuffer(uint8_t _stream, VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices)
	{
		BGFX_CHECK_HANDLE("setVertexBuffer", s_ctx->m_vertexBufferHandle, _handle);
		BGFX_ENCODER(setVertexBuffer(_stream, _handle, _startVertex, _numVertices) );
	}

	void Encoder::setVertexBuffer(uint8_t _stream, VertexBufferHandle _handle)
	{
		setVertexBuffer(_stream, _handle, 0, UINT32_MAX);
	}

	void Encoder::setVertexBuffer(uint8_t _stream, DynamicVertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices)
	{
		BGFX_CHECK_HANDLE("setVertexBuffer", s_ctx->m_dynamicVertexBufferHandle, _handle);
		const DynamicVertexBuffer& dvb = s_ctx->m_dynamicVertexBuffers[_handle.idx];
		BGFX_ENCODER(setVertexBuffer(_stream, dvb, _startVertex, _numVertices) );
	}

	void Encoder::setVertexBuffer(uint8_t _stream, DynamicVertexBufferHandle _handle)
	{
		setVertexBuffer(_stream, _handle, 0, UINT32_MAX);
	}

	void Encoder::setVertexBuffer(uint8_t _stream, const TransientVertexBuffer* _tvb, uint32_t _startVertex, uint32_t _numVertices)
	{
		BX_CHECK(NULL != _tvb, "_tvb can't be NULL");
		BGFX_CHECK_HANDLE("setVertexBuffer", s_ctx->m_vertexBufferHandle, _tvb->handle);
		BGFX_ENCODER(setVertexBuffer(_stream, _tvb, _startVertex, _numVertices) );
	}

	void Encoder::setVertexBuffer(uint8_t _stream, const TransientVertexBuffer* _tvb)
	{
		setVertexBuffer(_stream, _tvb, 0, UINT32_MAX);
	}

	void Encoder::setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint32_t _num)
	{
		BX_CHECK(NULL != _idb, "_idb can't be NULL");
		BGFX_ENCODER(setInstanceDataBuffer(_idb, _num) );
	}

	void Encoder::setInstanceDataBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num)
	{
		BGFX_CHECK_HANDLE("setInstanceDataBuffer", s_ctx->m_vertexBufferHandle, _handle);
		const VertexBuffer& vb = s_ctx->m_vertexBuffers[_handle.idx];
		BGFX_ENCODER(setInstanceDataBuffer(_handle, _startVertex, _num, vb.m_stride) );
	}

	void Encoder::setInstanceDataBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num)
	{
		BGFX_CHECK_HANDLE("setInstanceDataBuffer", s_ctx->m_dynamicVertexBufferHandle, _handle);
		const DynamicVertexBuffer& dvb = s_ctx->m_dynamicVertexBuffers[_handle.idx];
		BGFX_ENCODER(setInstanceDataBuffer(dvb.m_handle
			, dvb.m_startVertex + _startVertex
			, _num
			, dvb.m_stride
			) );
	}

	void Encoder::setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags)
	{
		BGFX_CHECK_HANDLE_INVALID_OK("setTexture/TextureHandle", s_ctx->m_textureHandle, _handle);
		BX_CHECK(_stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, "Invalid stage %d (max %d).", _stage, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
		BGFX_ENCODER(setTexture(_stage, _sampler, _handle, _flags) );
	}

	void Encoder::touch(ViewId _id)
	{
		ProgramHandle handle = BGFX_INVALID_HANDLE;
		submit(_id, handle);
	}

	void Encoder::submit(ViewId _id, ProgramHandle _program, int32_t _depth, bool _preserveState)
	{
		OcclusionQueryHandle handle = BGFX_INVALID_HANDLE;
		submit(_id, _program, handle, _depth, _preserveState);
	}

	void Encoder::submit(ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, int32_t _depth, bool _preserveState)
	{
		BX_CHECK(false
			|| !isValid(_occlusionQuery)
			|| 0 != (g_caps.supported & BGFX_CAPS_OCCLUSION_QUERY)
			, "Occlusion query is not supported! Use bgfx::getCaps to check BGFX_CAPS_OCCLUSION_QUERY backend renderer capabilities."
			);
		BGFX_CHECK_HANDLE_INVALID_OK("submit", s_ctx->m_programHandle, _program);
		BGFX_CHECK_HANDLE_INVALID_OK("submit", s_ctx->m_occlusionQueryHandle, _occlusionQuery);
		BGFX_ENCODER(submit(_id, _program, _occlusionQuery, _depth, _preserveState) );
	}

	void Encoder::submit(ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, int32_t _depth, bool _preserveState)
	{
		BGFX_CHECK_HANDLE_INVALID_OK("submit", s_ctx->m_programHandle, _program);
		BGFX_CHECK_HANDLE("submit", s_ctx->m_vertexBufferHandle, _indirectHandle);
		BGFX_CHECK_CAPS(BGFX_CAPS_DRAW_INDIRECT, "Draw indirect is not supported!");
		BGFX_ENCODER(submit(_id, _program, _indirectHandle, _start, _num, _depth, _preserveState) );
	}

	void Encoder::setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access)
	{
		BX_CHECK(_stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, "Invalid stage %d (max %d).", _stage, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_indexBufferHandle, _handle);
		BGFX_ENCODER(setBuffer(_stage, _handle, _access) );
	}

	void Encoder::setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access)
	{
		BX_CHECK(_stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, "Invalid stage %d (max %d).", _stage, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_vertexBufferHandle, _handle);
		BGFX_ENCODER(setBuffer(_stage, _handle, _access) );
	}

	void Encoder::setBuffer(uint8_t _stage, DynamicIndexBufferHandle _handle, Access::Enum _access)
	{
		BX_CHECK(_stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, "Invalid stage %d (max %d).", _stage, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_dynamicIndexBufferHandle, _handle);
		const DynamicIndexBuffer& dib = s_ctx->m_dynamicIndexBuffers[_handle.idx];
		BGFX_ENCODER(setBuffer(_stage, dib.m_handle, _access) );
	}

	void Encoder::setBuffer(uint8_t _stage, DynamicVertexBufferHandle _handle, Access::Enum _access)
	{
		BX_CHECK(_stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, "Invalid stage %d (max %d).", _stage, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_dynamicVertexBufferHandle, _handle);
		const DynamicVertexBuffer& dvb = s_ctx->m_dynamicVertexBuffers[_handle.idx];
		BGFX_ENCODER(setBuffer(_stage, dvb.m_handle, _access) );
	}

	void Encoder::setBuffer(uint8_t _stage, IndirectBufferHandle _handle, Access::Enum _access)
	{
		BX_CHECK(_stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, "Invalid stage %d (max %d).", _stage, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_vertexBufferHandle, _handle);
		VertexBufferHandle handle = { _handle.idx };
		BGFX_ENCODER(setBuffer(_stage, handle, _access) );
	}

	void Encoder::setImage(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format)
	{
		BX_CHECK(_stage < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS, "Invalid stage %d (max %d).", _stage, BGFX_CONFIG_MAX_TEXTURE_SAMPLERS);
		_format = TextureFormat::Count == _format
			? TextureFormat::Enum(s_ctx->m_textureRef[_handle.idx].m_format)
			: _format
			;
		BX_CHECK(_format != TextureFormat::BGRA8
			, "Can't use TextureFormat::BGRA8 with compute, use TextureFormat::RGBA8 instead."
			);
		BGFX_ENCODER(setImage(_stage, _sampler, _handle, _mip, _access, _format) );
	}

	void Encoder::dispatch(ViewId _id, ProgramHandle _program, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_COMPUTE, "Compute is not supported!");
		BGFX_CHECK_HANDLE_INVALID_OK("dispatch", s_ctx->m_programHandle, _program);
		BGFX_ENCODER(dispatch(_id, _program, _numX, _numY, _numZ, _flags) );
	}

	void Encoder::dispatch(ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_DRAW_INDIRECT, "Dispatch indirect is not supported!");
		BGFX_CHECK_CAPS(BGFX_CAPS_COMPUTE, "Compute is not supported!");
		BGFX_CHECK_HANDLE_INVALID_OK("dispatch", s_ctx->m_programHandle, _program);
		BGFX_CHECK_HANDLE("dispatch", s_ctx->m_vertexBufferHandle, _indirectHandle);
		BGFX_ENCODER(dispatch(_id, _program, _indirectHandle, _start, _num, _flags) );
	}

	void Encoder::discard()
	{
		BGFX_ENCODER(discard() );
	}

	void Encoder::blit(ViewId _id, TextureHandle _dst, uint16_t _dstX, uint16_t _dstY, TextureHandle _src, uint16_t _srcX, uint16_t _srcY, uint16_t _width, uint16_t _height)
	{
		blit(_id, _dst, 0, _dstX, _dstY, 0, _src, 0, _srcX, _srcY, 0, _width, _height, 0);
	}

	void Encoder::blit(ViewId _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_TEXTURE_BLIT, "Texture blit is not supported!");
		const Context::TextureRef& src = s_ctx->m_textureRef[_src.idx];
		const Context::TextureRef& dst = s_ctx->m_textureRef[_dst.idx];
		BX_CHECK(src.m_format == dst.m_format
			, "Texture format must match (src %s, dst %s)."
			, bimg::getName(bimg::TextureFormat::Enum(src.m_format) )
			, bimg::getName(bimg::TextureFormat::Enum(dst.m_format) )
			);
		BX_UNUSED(src, dst);
		BGFX_ENCODER(blit(_id, _dst, _dstMip, _dstX, _dstY, _dstZ, _src, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth) );
	}

#undef BGFX_ENCODER

	void end(Encoder* _encoder)
	{
		s_ctx->end(_encoder);
	}

	uint32_t frame(bool _capture)
	{
		BGFX_CHECK_API_THREAD();
		return s_ctx->frame(_capture);
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
		bx::memCopy(mem->data, _data, _size);
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
		BGFX_CHECK_API_THREAD();
		s_ctx->setDebug(_debug);
	}

	void dbgTextClear(uint8_t _attr, bool _small)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->dbgTextClear(_attr, _small);
	}

	void dbgTextPrintfVargs(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList)
	{
		s_ctx->dbgTextPrintfVargs(_x, _y, _attr, _format, _argList);
	}

	void dbgTextPrintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...)
	{
		BGFX_CHECK_API_THREAD();
		va_list argList;
		va_start(argList, _format);
		s_ctx->dbgTextPrintfVargs(_x, _y, _attr, _format, argList);
		va_end(argList);
	}

	void dbgTextImage(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->dbgTextImage(_x, _y, _width, _height, _data, _pitch);
	}

	IndexBufferHandle createIndexBuffer(const Memory* _mem, uint16_t _flags)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createIndexBuffer(_mem, _flags);
	}

	void destroy(IndexBufferHandle _handle)
	{
		s_ctx->destroyIndexBuffer(_handle);
	}

	VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl, uint16_t _flags)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		BX_CHECK(isValid(_decl), "Invalid VertexDecl.");
		return s_ctx->createVertexBuffer(_mem, _decl, _flags);
	}

	void destroy(VertexBufferHandle _handle)
	{
		s_ctx->destroyVertexBuffer(_handle);
	}

	DynamicIndexBufferHandle createDynamicIndexBuffer(uint32_t _num, uint16_t _flags)
	{
		return s_ctx->createDynamicIndexBuffer(_num, _flags);
	}

	DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem, uint16_t _flags)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createDynamicIndexBuffer(_mem, _flags);
	}

	void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _startIndex, const Memory* _mem)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		s_ctx->updateDynamicIndexBuffer(_handle, _startIndex, _mem);
	}

	void destroy(DynamicIndexBufferHandle _handle)
	{
		s_ctx->destroyDynamicIndexBuffer(_handle);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(uint32_t _num, const VertexDecl& _decl, uint16_t _flags)
	{
		BX_CHECK(isValid(_decl), "Invalid VertexDecl.");
		return s_ctx->createDynamicVertexBuffer(_num, _decl, _flags);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexDecl& _decl, uint16_t _flags)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		BX_CHECK(isValid(_decl), "Invalid VertexDecl.");
		return s_ctx->createDynamicVertexBuffer(_mem, _decl, _flags);
	}

	void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, const Memory* _mem)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		s_ctx->updateDynamicVertexBuffer(_handle, _startVertex, _mem);
	}

	void destroy(DynamicVertexBufferHandle _handle)
	{
		s_ctx->destroyDynamicVertexBuffer(_handle);
	}

	uint32_t getAvailTransientIndexBuffer(uint32_t _num)
	{
		BX_CHECK(0 < _num, "Requesting 0 indices.");
		return s_ctx->getAvailTransientIndexBuffer(_num);
	}

	uint32_t getAvailTransientVertexBuffer(uint32_t _num, const VertexDecl& _decl)
	{
		BX_CHECK(0 < _num, "Requesting 0 vertices.");
		BX_CHECK(isValid(_decl), "Invalid VertexDecl.");
		return s_ctx->getAvailTransientVertexBuffer(_num, _decl.m_stride);
	}

	uint32_t getAvailInstanceDataBuffer(uint32_t _num, uint16_t _stride)
	{
		BX_CHECK(0 < _num, "Requesting 0 instances.");
		return s_ctx->getAvailTransientVertexBuffer(_num, _stride);
	}

	void allocTransientIndexBuffer(TransientIndexBuffer* _tib, uint32_t _num)
	{
		BX_CHECK(NULL != _tib, "_tib can't be NULL");
		BX_CHECK(0 < _num, "Requesting 0 indices.");
		s_ctx->allocTransientIndexBuffer(_tib, _num);
		BX_CHECK(_num == _tib->size/2, "Failed to allocate transient index buffer (requested %d, available %d). Use bgfx::checkAvailTransient* functions to ensure availability."
			, _num
			, _tib->size/2
			);
	}

	void allocTransientVertexBuffer(TransientVertexBuffer* _tvb, uint32_t _num, const VertexDecl& _decl)
	{
		BX_CHECK(NULL != _tvb, "_tvb can't be NULL");
		BX_CHECK(0 < _num, "Requesting 0 vertices.");
		BX_CHECK(UINT16_MAX >= _num, "Requesting %d vertices (max: %d).", _num, UINT16_MAX);
		BX_CHECK(isValid(_decl), "Invalid VertexDecl.");
		s_ctx->allocTransientVertexBuffer(_tvb, _num, _decl);
		BX_CHECK(_num == _tvb->size / _decl.m_stride, "Failed to allocate transient vertex buffer (requested %d, available %d). Use bgfx::checkAvailTransient* functions to ensure availability."
			, _num
			, _tvb->size / _decl.m_stride
			);
	}

	bool allocTransientBuffers(bgfx::TransientVertexBuffer* _tvb, const bgfx::VertexDecl& _decl, uint32_t _numVertices, bgfx::TransientIndexBuffer* _tib, uint32_t _numIndices)
	{
		BGFX_MUTEX_SCOPE(s_ctx->m_resourceApiLock);

		if (_numVertices == getAvailTransientVertexBuffer(_numVertices, _decl)
		&&  _numIndices  == getAvailTransientIndexBuffer(_numIndices) )
		{
			allocTransientVertexBuffer(_tvb, _numVertices, _decl);
			allocTransientIndexBuffer(_tib, _numIndices);
			return true;
		}

		return false;
	}

	void allocInstanceDataBuffer(InstanceDataBuffer* _idb, uint32_t _num, uint16_t _stride)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_INSTANCING, "Instancing is not supported!");
		BX_CHECK(_stride == BX_ALIGN_16(_stride), "Stride must be multiple of 16.");
		BX_CHECK(0 < _num, "Requesting 0 instanced data vertices.");
		s_ctx->allocInstanceDataBuffer(_idb, _num, _stride);
		BX_CHECK(_num == _idb->size / _stride, "Failed to allocate instance data buffer (requested %d, available %d). Use bgfx::checkAvailTransient* functions to ensure availability."
			, _num
			, _idb->size / _stride
			);
	}

	IndirectBufferHandle createIndirectBuffer(uint32_t _num)
	{
		return s_ctx->createIndirectBuffer(_num);
	}

	void destroy(IndirectBufferHandle _handle)
	{
		s_ctx->destroyIndirectBuffer(_handle);
	}

	ShaderHandle createShader(const Memory* _mem)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createShader(_mem);
	}

	uint16_t getShaderUniforms(ShaderHandle _handle, UniformHandle* _uniforms, uint16_t _max)
	{
		return s_ctx->getShaderUniforms(_handle, _uniforms, _max);
	}

	void setName(ShaderHandle _handle, const char* _name)
	{
		s_ctx->setName(_handle, _name);
	}

	void destroy(ShaderHandle _handle)
	{
		s_ctx->destroyShader(_handle);
	}

	ProgramHandle createProgram(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders)
	{
		if (!isValid(_fsh) )
		{
			return createProgram(_vsh, _destroyShaders);
		}

		return s_ctx->createProgram(_vsh, _fsh, _destroyShaders);
	}

	ProgramHandle createProgram(ShaderHandle _csh, bool _destroyShader)
	{
		return s_ctx->createProgram(_csh, _destroyShader);
	}

	void destroy(ProgramHandle _handle)
	{
		s_ctx->destroyProgram(_handle);
	}

	static void isTextureValid(uint16_t _depth, bool _cubeMap, uint16_t _numLayers, TextureFormat::Enum _format, uint32_t _flags, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		const bool is3DTexture = 1 < _depth;

		if (_cubeMap && is3DTexture)
		{
			_err->setError(BGFX_ERROR_TEXTURE_VALIDATION
				, "Texture can't be depth and cube map at the same time."
				);
			return;
		}

		if (is3DTexture
		&& 	0 == (g_caps.supported & BGFX_CAPS_TEXTURE_3D) )
		{
			_err->setError(BGFX_ERROR_TEXTURE_VALIDATION
				, "Texture3D is not supported! "
				  "Use bgfx::getCaps to check BGFX_CAPS_TEXTURE_3D backend renderer capabilities."
				);
			return;
		}

		if (0 != (_flags & BGFX_TEXTURE_RT_MASK)
		&&  0 != (_flags & BGFX_TEXTURE_READ_BACK) )
		{
			_err->setError(BGFX_ERROR_TEXTURE_VALIDATION
				, "Can't create render target with BGFX_TEXTURE_READ_BACK flag."
				);
			return;
		}

		if (1 < _numLayers
		&&  0 == (g_caps.supported & BGFX_CAPS_TEXTURE_2D_ARRAY) )
		{
			_err->setError(BGFX_ERROR_TEXTURE_VALIDATION
				, "Texture array is not supported! "
				  "Use bgfx::getCaps to check BGFX_CAPS_TEXTURE_2D_ARRAY backend renderer capabilities."
				);
			return;
		}

		bool formatSupported = 0 != (g_caps.formats[_format] & (0
				| BGFX_CAPS_FORMAT_TEXTURE_2D
				| BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED
				| BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
				) );
		uint16_t srgbCaps = BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB;

		if (_cubeMap)
		{
			formatSupported = 0 != (g_caps.formats[_format] & (0
				| BGFX_CAPS_FORMAT_TEXTURE_CUBE
				| BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED
				| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
				) );
			srgbCaps = BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB;
		}
		else if (is3DTexture)
		{
			formatSupported = 0 != (g_caps.formats[_format] & (0
				| BGFX_CAPS_FORMAT_TEXTURE_3D
				| BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED
				| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
				) );
			srgbCaps = BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB;
		}

		if (formatSupported
		&&  0 != (_flags & BGFX_TEXTURE_RT_MASK) )
		{
			formatSupported = 0 != (g_caps.formats[_format] & (0
				| BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER
				) );
		}

		if (!formatSupported)
		{
			_err->setError(BGFX_ERROR_TEXTURE_VALIDATION
				, "Texture format is not supported! "
				  "Use bgfx::isTextureValid to check support for texture format before creating it."
				);
			return;
		}

		if (0 != (_flags & BGFX_TEXTURE_MSAA_SAMPLE)
		&&  0 == (g_caps.formats[_format] & BGFX_CAPS_FORMAT_TEXTURE_MSAA) )
		{
			_err->setError(BGFX_ERROR_TEXTURE_VALIDATION
				, "MSAA sampling for this texture format is not supported."
				);
			return;
		}

		if (0 != (_flags & BGFX_TEXTURE_SRGB)
		&&  0 == (g_caps.supported & srgbCaps & (0
				| BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
				| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
				| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
				) ) )
		{
			_err->setError(BGFX_ERROR_TEXTURE_VALIDATION
				, "sRGB sampling for this texture format is not supported."
				);
			return;
		}
	}

	bool isTextureValid(uint16_t _depth, bool _cubeMap, uint16_t _numLayers, TextureFormat::Enum _format, uint32_t _flags)
	{
		bx::Error err;
		isTextureValid(_depth, _cubeMap, _numLayers, _format, _flags, &err);
		return err.isOk();
	}

	void calcTextureSize(TextureInfo& _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format)
	{
		bimg::imageGetSize( (bimg::TextureInfo*)&_info, _width, _height, _depth, _cubeMap, _hasMips, _numLayers, bimg::TextureFormat::Enum(_format) );
	}

	TextureHandle createTexture(const Memory* _mem, uint32_t _flags, uint8_t _skip, TextureInfo* _info)
	{
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

	static TextureHandle createTexture2D(BackbufferRatio::Enum _ratio, uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		bx::Error err;
		isTextureValid(0, false, _numLayers, _format, _flags, &err);
		BX_CHECK(err.isOk(), "%s (layers %d, format %s)"
			, err.getMessage().getPtr()
			, _numLayers
			, getName(_format)
			);

		if (BackbufferRatio::Count != _ratio)
		{
			_width  = uint16_t(s_ctx->m_resolution.m_width);
			_height = uint16_t(s_ctx->m_resolution.m_height);
			getTextureSizeFromRatio(_ratio, _width, _height);
		}

		const uint8_t numMips = calcNumMips(_hasMips, _width, _height);
		_numLayers = bx::uint16_max(_numLayers, 1);

		if (BX_ENABLED(BGFX_CONFIG_DEBUG)
		&&  NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _width, _height, 1, false, _hasMips, _numLayers, _format);
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

		TextureCreate tc;
		tc.m_width     = _width;
		tc.m_height    = _height;
		tc.m_depth     = 0;
		tc.m_numLayers = _numLayers;
		tc.m_numMips   = numMips;
		tc.m_format    = _format;
		tc.m_cubeMap   = false;
		tc.m_mem       = _mem;
		bx::write(&writer, tc);

		return s_ctx->createTexture(mem, _flags, 0, NULL, _ratio);
	}

	TextureHandle createTexture2D(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		BX_CHECK(_width > 0 && _height > 0, "Invalid texture size (width %d, height %d).", _width, _height);
		return createTexture2D(BackbufferRatio::Count, _width, _height, _hasMips, _numLayers, _format, _flags, _mem);
	}

	TextureHandle createTexture2D(BackbufferRatio::Enum _ratio, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint32_t _flags)
	{
		BX_CHECK(_ratio < BackbufferRatio::Count, "Invalid back buffer ratio.");
		return createTexture2D(_ratio, 0, 0, _hasMips, _numLayers, _format, _flags, NULL);
	}

	TextureHandle createTexture3D(uint16_t _width, uint16_t _height, uint16_t _depth, bool _hasMips, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		bx::Error err;
		isTextureValid(_depth, false, 1, _format, _flags, &err);
		BX_CHECK(err.isOk(), "%s", err.getMessage().getPtr() );

		const uint8_t numMips = calcNumMips(_hasMips, _width, _height, _depth);

		if (BX_ENABLED(BGFX_CONFIG_DEBUG)
		&&  NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _width, _height, _depth, false, _hasMips, 1, _format);
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
		tc.m_width     = _width;
		tc.m_height    = _height;
		tc.m_depth     = _depth;
		tc.m_numLayers = 1;
		tc.m_numMips   = numMips;
		tc.m_format    = _format;
		tc.m_cubeMap   = false;
		tc.m_mem       = _mem;
		bx::write(&writer, tc);

		return s_ctx->createTexture(mem, _flags, 0, NULL, BackbufferRatio::Count);
	}

	TextureHandle createTextureCube(uint16_t _size, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint32_t _flags, const Memory* _mem)
	{
		bx::Error err;
		isTextureValid(0, true, _numLayers, _format, _flags, &err);
		BX_CHECK(err.isOk(), "%s", err.getMessage().getPtr() );

		const uint8_t numMips = calcNumMips(_hasMips, _size, _size);
		_numLayers = bx::uint16_max(_numLayers, 1);

		if (BX_ENABLED(BGFX_CONFIG_DEBUG)
		&&  NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _size, _size, 1, true, _hasMips, _numLayers, _format);
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
		tc.m_width     = _size;
		tc.m_height    = _size;
		tc.m_depth     = 0;
		tc.m_numLayers = _numLayers;
		tc.m_numMips   = numMips;
		tc.m_format    = _format;
		tc.m_cubeMap   = true;
		tc.m_mem       = _mem;
		bx::write(&writer, tc);

		return s_ctx->createTexture(mem, _flags, 0, NULL, BackbufferRatio::Count);
	}

	void setName(TextureHandle _handle, const char* _name)
	{
		s_ctx->setName(_handle, _name);
	}

	void* getDirectAccessPtr(TextureHandle _handle)
	{
		return s_ctx->getDirectAccessPtr(_handle);
	}

	void destroy(TextureHandle _handle)
	{
		s_ctx->destroyTexture(_handle);
	}

	void updateTexture2D(TextureHandle _handle, uint16_t _layer, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem, uint16_t _pitch)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		if (_width  == 0
		||  _height == 0)
		{
			release(_mem);
		}
		else
		{
			s_ctx->updateTexture(_handle, 0, _mip, _x, _y, _layer, _width, _height, 1, _pitch, _mem);
		}
	}

	void updateTexture3D(TextureHandle _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const Memory* _mem)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		BGFX_CHECK_CAPS(BGFX_CAPS_TEXTURE_3D, "Texture3D is not supported!");

		if (0 == _width
		||  0 == _height
		||  0 == _depth)
		{
			release(_mem);
		}
		else
		{
			s_ctx->updateTexture(_handle, 0, _mip, _x, _y, _z, _width, _height, _depth, UINT16_MAX, _mem);
		}
	}

	void updateTextureCube(TextureHandle _handle, uint16_t _layer, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const Memory* _mem, uint16_t _pitch)
	{
		BX_CHECK(NULL != _mem, "_mem can't be NULL");
		BX_CHECK(_side <= 5, "Invalid side %d.", _side);
		if (0 == _width
		||  0 == _height)
		{
			release(_mem);
		}
		else
		{
			s_ctx->updateTexture(_handle, _side, _mip, _x, _y, _layer, _width, _height, 1, _pitch, _mem);
		}
	}

	uint32_t readTexture(TextureHandle _handle, void* _data, uint8_t _mip)
	{
		BX_CHECK(NULL != _data, "_data can't be NULL");
		BGFX_CHECK_CAPS(BGFX_CAPS_TEXTURE_READ_BACK, "Texture read-back is not supported!");
		return s_ctx->readTexture(_handle, _data, _mip);
	}

	FrameBufferHandle createFrameBuffer(uint16_t _width, uint16_t _height, TextureFormat::Enum _format, uint32_t _textureFlags)
	{
		_textureFlags |= _textureFlags&BGFX_TEXTURE_RT_MSAA_MASK ? 0 : BGFX_TEXTURE_RT;
		TextureHandle th = createTexture2D(_width, _height, false, 1, _format, _textureFlags);
		return createFrameBuffer(1, &th, true);
	}

	FrameBufferHandle createFrameBuffer(BackbufferRatio::Enum _ratio, TextureFormat::Enum _format, uint32_t _textureFlags)
	{
		BX_CHECK(_ratio < BackbufferRatio::Count, "Invalid back buffer ratio.");
		_textureFlags |= _textureFlags&BGFX_TEXTURE_RT_MSAA_MASK ? 0 : BGFX_TEXTURE_RT;
		TextureHandle th = createTexture2D(_ratio, false, 1, _format, _textureFlags);
		return createFrameBuffer(1, &th, true);
	}

	FrameBufferHandle createFrameBuffer(uint8_t _num, const TextureHandle* _handles, bool _destroyTextures)
	{
		Attachment attachment[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
		for (uint8_t ii = 0; ii < _num; ++ii)
		{
			Attachment& at = attachment[ii];
			at.handle = _handles[ii];
			at.mip    = 0;
			at.layer  = 0;
		}
		return createFrameBuffer(_num, attachment, _destroyTextures);
	}

	FrameBufferHandle createFrameBuffer(uint8_t _num, const Attachment* _attachment, bool _destroyTextures)
	{
		BX_CHECK(_num != 0, "Number of frame buffer attachments can't be 0.");
		BX_CHECK(_num <= BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
			, "Number of frame buffer attachments is larger than allowed %d (max: %d)."
			, _num
			, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
			);
		BX_CHECK(NULL != _attachment, "_attachment can't be NULL");
		return s_ctx->createFrameBuffer(_num, _attachment, _destroyTextures);
	}

	FrameBufferHandle createFrameBuffer(void* _nwh, uint16_t _width, uint16_t _height, TextureFormat::Enum _depthFormat)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_SWAP_CHAIN, "Swap chain is not supported!");
		BX_WARN(_width > 0 && _height > 0
			, "Invalid frame buffer dimensions (width %d, height %d)."
			, _width
			, _height
			);
		return s_ctx->createFrameBuffer(
			  _nwh
			, bx::uint16_max(_width, 1)
			, bx::uint16_max(_height, 1)
			, _depthFormat
			);
	}

	TextureHandle getTexture(FrameBufferHandle _handle, uint8_t _attachment)
	{
		return s_ctx->getTexture(_handle, _attachment);
	}

	void destroy(FrameBufferHandle _handle)
	{
		s_ctx->destroyFrameBuffer(_handle);
	}

	UniformHandle createUniform(const char* _name, UniformType::Enum _type, uint16_t _num)
	{
		return s_ctx->createUniform(_name, _type, _num);
	}

	void getUniformInfo(UniformHandle _handle, UniformInfo& _info)
	{
		s_ctx->getUniformInfo(_handle, _info);
	}

	void destroy(UniformHandle _handle)
	{
		s_ctx->destroyUniform(_handle);
	}

	OcclusionQueryHandle createOcclusionQuery()
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_OCCLUSION_QUERY, "Occlusion query is not supported!");
		return s_ctx->createOcclusionQuery();
	}

	OcclusionQueryResult::Enum getResult(OcclusionQueryHandle _handle, int32_t* _result)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_OCCLUSION_QUERY, "Occlusion query is not supported!");
		return s_ctx->getResult(_handle, _result);
	}

	void destroy(OcclusionQueryHandle _handle)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_OCCLUSION_QUERY, "Occlusion query is not supported!");
		s_ctx->destroyOcclusionQuery(_handle);
	}

	void setPaletteColor(uint8_t _index, uint32_t _rgba)
	{
		const uint8_t rr = uint8_t(_rgba>>24);
		const uint8_t gg = uint8_t(_rgba>>16);
		const uint8_t bb = uint8_t(_rgba>> 8);
		const uint8_t aa = uint8_t(_rgba>> 0);

		const float rgba[4] =
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
		float rgba[4] = { _r, _g, _b, _a };
		s_ctx->setPaletteColor(_index, rgba);
	}

	void setPaletteColor(uint8_t _index, const float _rgba[4])
	{
		s_ctx->setPaletteColor(_index, _rgba);
	}

	bool checkView(ViewId _id)
	{
		// workaround GCC 4.9 type-limit check.
		const uint32_t id = _id;
		return id < BGFX_CONFIG_MAX_VIEWS;
	}

	void setViewName(ViewId _id, const char* _name)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewName(_id, _name);
	}

	void setViewRect(ViewId _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewRect(_id, _x, _y, _width, _height);
	}

	void setViewRect(ViewId _id, uint16_t _x, uint16_t _y, BackbufferRatio::Enum _ratio)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);

		uint16_t width  = uint16_t(s_ctx->m_resolution.m_width);
		uint16_t height = uint16_t(s_ctx->m_resolution.m_height);
		getTextureSizeFromRatio(_ratio, width, height);
		setViewRect(_id, _x, _y, width, height);
	}

	void setViewScissor(ViewId _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewScissor(_id, _x, _y, _width, _height);
	}

	void setViewClear(ViewId _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewClear(_id, _flags, _rgba, _depth, _stencil);
	}

	void setViewClear(ViewId _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewClear(_id, _flags, _depth, _stencil, _0, _1, _2, _3, _4, _5, _6, _7);
	}

	void setViewMode(ViewId _id, ViewMode::Enum _mode)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewMode(_id, _mode);
	}

	void setViewFrameBuffer(ViewId _id, FrameBufferHandle _handle)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewFrameBuffer(_id, _handle);
	}

	void setViewTransform(ViewId _id, const void* _view, const void* _projL, uint8_t _flags, const void* _projR)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewTransform(_id, _view, _projL, _flags, _projR);
	}

	void setViewOrder(ViewId _id, uint16_t _num, const ViewId* _order)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewOrder(_id, _num, _order);
	}

	void resetView(ViewId _id)
	{
		BX_CHECK(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->resetView(_id);
	}

	void setMarker(const char* _marker)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setMarker(_marker);
	}

	void setState(uint64_t _state, uint32_t _rgba)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setState(_state, _rgba);
	}

	void setCondition(OcclusionQueryHandle _handle, bool _visible)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setCondition(_handle, _visible);
	}

	void setStencil(uint32_t _fstencil, uint32_t _bstencil)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setStencil(_fstencil, _bstencil);
	}

	uint16_t setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BGFX_CHECK_API_THREAD();
		return s_ctx->m_encoder0->setScissor(_x, _y, _width, _height);
	}

	void setScissor(uint16_t _cache)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setScissor(_cache);
	}

	uint32_t setTransform(const void* _mtx, uint16_t _num)
	{
		BGFX_CHECK_API_THREAD();
		return s_ctx->m_encoder0->setTransform(_mtx, _num);
	}

	uint32_t allocTransform(Transform* _transform, uint16_t _num)
	{
		BGFX_CHECK_API_THREAD();
		return s_ctx->m_encoder0->allocTransform(_transform, _num);
	}

	void setTransform(uint32_t _cache, uint16_t _num)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setTransform(_cache, _num);
	}

	void setUniform(UniformHandle _handle, const void* _value, uint16_t _num)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setUniform(_handle, _value, _num);
	}

	void setIndexBuffer(IndexBufferHandle _handle)
	{
		setIndexBuffer(_handle, 0, UINT32_MAX);
	}

	void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setIndexBuffer(_handle, _firstIndex, _numIndices);
	}

	void setIndexBuffer(DynamicIndexBufferHandle _handle)
	{
		setIndexBuffer(_handle, 0, UINT32_MAX);
	}

	void setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setIndexBuffer(_handle, _firstIndex, _numIndices);
	}

	void setIndexBuffer(const TransientIndexBuffer* _tib)
	{
		setIndexBuffer(_tib, 0, UINT32_MAX);
	}

	void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setIndexBuffer(_tib, _firstIndex, _numIndices);
	}

	void setVertexBuffer(uint8_t _stream, VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setVertexBuffer(_stream, _handle, _startVertex, _numVertices);
	}

	void setVertexBuffer(uint8_t _stream, VertexBufferHandle _handle)
	{
		setVertexBuffer(_stream, _handle, 0, UINT32_MAX);
	}

	void setVertexBuffer(uint8_t _stream, DynamicVertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setVertexBuffer(_stream, _handle, _startVertex, _numVertices);
	}

	void setVertexBuffer(uint8_t _stream, DynamicVertexBufferHandle _handle)
	{
		setVertexBuffer(_stream, _handle, 0, UINT32_MAX);
	}

	void setVertexBuffer(uint8_t _stream, const TransientVertexBuffer* _tvb, uint32_t _startVertex, uint32_t _numVertices)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setVertexBuffer(_stream, _tvb, _startVertex, _numVertices);
	}

	void setVertexBuffer(uint8_t _stream, const TransientVertexBuffer* _tvb)
	{
		setVertexBuffer(_stream, _tvb, 0, UINT32_MAX);
	}

	void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint32_t _num)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setInstanceDataBuffer(_idb, _num);
	}

	void setInstanceDataBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setInstanceDataBuffer(_handle, _startVertex, _num);
	}

	void setInstanceDataBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setInstanceDataBuffer(_handle, _startVertex, _num);
	}

	void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setTexture(_stage, _sampler, _handle, _flags);
	}

	void touch(ViewId _id)
	{
		ProgramHandle handle = BGFX_INVALID_HANDLE;
		submit(_id, handle);
	}

	void submit(ViewId _id, ProgramHandle _program, int32_t _depth, bool _preserveState)
	{
		OcclusionQueryHandle handle = BGFX_INVALID_HANDLE;
		submit(_id, _program, handle, _depth, _preserveState);
	}

	void submit(ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, int32_t _depth, bool _preserveState)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->submit(_id, _program, _occlusionQuery, _depth, _preserveState);
	}

	void submit(ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, int32_t _depth, bool _preserveState)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->submit(_id, _program, _indirectHandle, _start, _num, _depth, _preserveState);
	}

	void setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, DynamicIndexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, DynamicVertexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, IndirectBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setImage(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->setImage(_stage, _sampler, _handle, _mip, _access, _format);
	}

	void dispatch(ViewId _id, ProgramHandle _handle, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->dispatch(_id, _handle, _numX, _numY, _numZ, _flags);
	}

	void dispatch(ViewId _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->dispatch(_id, _handle, _indirectHandle, _start, _num, _flags);
	}

	void discard()
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->discard();
	}

	void blit(ViewId _id, TextureHandle _dst, uint16_t _dstX, uint16_t _dstY, TextureHandle _src, uint16_t _srcX, uint16_t _srcY, uint16_t _width, uint16_t _height)
	{
		blit(_id, _dst, 0, _dstX, _dstY, 0, _src, 0, _srcX, _srcY, 0, _width, _height, 0);
	}

	void blit(ViewId _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->m_encoder0->blit(_id, _dst, _dstMip, _dstX, _dstY, _dstZ, _src, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
	}

	void requestScreenShot(FrameBufferHandle _handle, const char* _filePath)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->requestScreenShot(_handle, _filePath);
	}
} // namespace bgfx

#if BX_PLATFORM_WINDOWS
extern "C"
{
	// When laptop setup has integrated and discrete GPU, following driver workarounds will
	// select discrete GPU:

	// Reference: https://docs.nvidia.com/gameworks/content/technologies/desktop/optimus.htm
	__declspec(dllexport) uint32_t NvOptimusEnablement = UINT32_C(1);

	// Reference: http://gpuopen.com/amdpowerxpressrequesthighperformance/
	__declspec(dllexport) uint32_t AmdPowerXpressRequestHighPerformance = UINT32_C(1);
}
#endif // BX_PLATFORM_WINDOWS

#define BGFX_TEXTURE_FORMAT_BIMG(_fmt) \
			BX_STATIC_ASSERT(uint32_t(bgfx::TextureFormat::_fmt) == uint32_t(bimg::TextureFormat::_fmt) )

BGFX_TEXTURE_FORMAT_BIMG(BC1);
BGFX_TEXTURE_FORMAT_BIMG(BC2);
BGFX_TEXTURE_FORMAT_BIMG(BC3);
BGFX_TEXTURE_FORMAT_BIMG(BC4);
BGFX_TEXTURE_FORMAT_BIMG(BC5);
BGFX_TEXTURE_FORMAT_BIMG(BC6H);
BGFX_TEXTURE_FORMAT_BIMG(BC7);
BGFX_TEXTURE_FORMAT_BIMG(ETC1);
BGFX_TEXTURE_FORMAT_BIMG(ETC2);
BGFX_TEXTURE_FORMAT_BIMG(ETC2A);
BGFX_TEXTURE_FORMAT_BIMG(ETC2A1);
BGFX_TEXTURE_FORMAT_BIMG(PTC12);
BGFX_TEXTURE_FORMAT_BIMG(PTC14);
BGFX_TEXTURE_FORMAT_BIMG(PTC12A);
BGFX_TEXTURE_FORMAT_BIMG(PTC14A);
BGFX_TEXTURE_FORMAT_BIMG(PTC22);
BGFX_TEXTURE_FORMAT_BIMG(PTC24);
BGFX_TEXTURE_FORMAT_BIMG(Unknown);
BGFX_TEXTURE_FORMAT_BIMG(R1);
BGFX_TEXTURE_FORMAT_BIMG(A8);
BGFX_TEXTURE_FORMAT_BIMG(R8);
BGFX_TEXTURE_FORMAT_BIMG(R8I);
BGFX_TEXTURE_FORMAT_BIMG(R8U);
BGFX_TEXTURE_FORMAT_BIMG(R8S);
BGFX_TEXTURE_FORMAT_BIMG(R16);
BGFX_TEXTURE_FORMAT_BIMG(R16I);
BGFX_TEXTURE_FORMAT_BIMG(R16U);
BGFX_TEXTURE_FORMAT_BIMG(R16F);
BGFX_TEXTURE_FORMAT_BIMG(R16S);
BGFX_TEXTURE_FORMAT_BIMG(R32I);
BGFX_TEXTURE_FORMAT_BIMG(R32U);
BGFX_TEXTURE_FORMAT_BIMG(R32F);
BGFX_TEXTURE_FORMAT_BIMG(RG8);
BGFX_TEXTURE_FORMAT_BIMG(RG8I);
BGFX_TEXTURE_FORMAT_BIMG(RG8U);
BGFX_TEXTURE_FORMAT_BIMG(RG8S);
BGFX_TEXTURE_FORMAT_BIMG(RG16);
BGFX_TEXTURE_FORMAT_BIMG(RG16I);
BGFX_TEXTURE_FORMAT_BIMG(RG16U);
BGFX_TEXTURE_FORMAT_BIMG(RG16F);
BGFX_TEXTURE_FORMAT_BIMG(RG16S);
BGFX_TEXTURE_FORMAT_BIMG(RG32I);
BGFX_TEXTURE_FORMAT_BIMG(RG32U);
BGFX_TEXTURE_FORMAT_BIMG(RG32F);
BGFX_TEXTURE_FORMAT_BIMG(RGB8);
BGFX_TEXTURE_FORMAT_BIMG(RGB8I);
BGFX_TEXTURE_FORMAT_BIMG(RGB8U);
BGFX_TEXTURE_FORMAT_BIMG(RGB8S);
BGFX_TEXTURE_FORMAT_BIMG(RGB9E5F);
BGFX_TEXTURE_FORMAT_BIMG(BGRA8);
BGFX_TEXTURE_FORMAT_BIMG(RGBA8);
BGFX_TEXTURE_FORMAT_BIMG(RGBA8I);
BGFX_TEXTURE_FORMAT_BIMG(RGBA8U);
BGFX_TEXTURE_FORMAT_BIMG(RGBA8S);
BGFX_TEXTURE_FORMAT_BIMG(RGBA16);
BGFX_TEXTURE_FORMAT_BIMG(RGBA16I);
BGFX_TEXTURE_FORMAT_BIMG(RGBA16U);
BGFX_TEXTURE_FORMAT_BIMG(RGBA16F);
BGFX_TEXTURE_FORMAT_BIMG(RGBA16S);
BGFX_TEXTURE_FORMAT_BIMG(RGBA32I);
BGFX_TEXTURE_FORMAT_BIMG(RGBA32U);
BGFX_TEXTURE_FORMAT_BIMG(RGBA32F);
BGFX_TEXTURE_FORMAT_BIMG(R5G6B5);
BGFX_TEXTURE_FORMAT_BIMG(RGBA4);
BGFX_TEXTURE_FORMAT_BIMG(RGB5A1);
BGFX_TEXTURE_FORMAT_BIMG(RGB10A2);
BGFX_TEXTURE_FORMAT_BIMG(RG11B10F);
BGFX_TEXTURE_FORMAT_BIMG(UnknownDepth);
BGFX_TEXTURE_FORMAT_BIMG(D16);
BGFX_TEXTURE_FORMAT_BIMG(D24);
BGFX_TEXTURE_FORMAT_BIMG(D24S8);
BGFX_TEXTURE_FORMAT_BIMG(D32);
BGFX_TEXTURE_FORMAT_BIMG(D16F);
BGFX_TEXTURE_FORMAT_BIMG(D24F);
BGFX_TEXTURE_FORMAT_BIMG(D32F);
BGFX_TEXTURE_FORMAT_BIMG(D0S8);
BGFX_TEXTURE_FORMAT_BIMG(Count);

#undef BGFX_TEXTURE_FORMAT_BIMG

#include <bgfx/c99/bgfx.h>
#include <bgfx/c99/platform.h>

#define FLAGS_MASK_TEST(_flags, _mask) ( (_flags) == ( (_flags) & (_mask) ) )

BX_STATIC_ASSERT(FLAGS_MASK_TEST(0
	| BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER
	| BGFX_TEXTURE_INTERNAL_SHARED
	, BGFX_TEXTURE_RESERVED_MASK
	) );

BX_STATIC_ASSERT(FLAGS_MASK_TEST(0
	| BGFX_RESET_INTERNAL_FORCE
	, BGFX_RESET_RESERVED_MASK
	) );

BX_STATIC_ASSERT(FLAGS_MASK_TEST(0
	| BGFX_STATE_INTERNAL_SCISSOR
	| BGFX_STATE_INTERNAL_OCCLUSION_QUERY
	, BGFX_STATE_RESERVED_MASK
	) );

BX_STATIC_ASSERT(FLAGS_MASK_TEST(0
	| BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE
	, BGFX_SUBMIT_RESERVED_MASK
	) );

#undef FLAGS_MASK_TEST

#define BGFX_C99_ENUM_CHECK(_enum, _c99enumcount) \
			BX_STATIC_ASSERT(_enum::Count == _enum::Enum(_c99enumcount) )

BGFX_C99_ENUM_CHECK(bgfx::Fatal,                BGFX_FATAL_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::RendererType,         BGFX_RENDERER_TYPE_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::Attrib,               BGFX_ATTRIB_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::AttribType,           BGFX_ATTRIB_TYPE_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::TextureFormat,        BGFX_TEXTURE_FORMAT_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::UniformType,          BGFX_UNIFORM_TYPE_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::BackbufferRatio,      BGFX_BACKBUFFER_RATIO_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::OcclusionQueryResult, BGFX_OCCLUSION_QUERY_RESULT_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::TopologyConvert,      BGFX_TOPOLOGY_CONVERT_COUNT);
BGFX_C99_ENUM_CHECK(bgfx::RenderFrame,          BGFX_RENDER_FRAME_COUNT);
#undef BGFX_C99_ENUM_CHECK

#define BGFX_C99_STRUCT_SIZE_CHECK(_cppstruct, _c99struct) \
			BX_STATIC_ASSERT(sizeof(_cppstruct) == sizeof(_c99struct) )

BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Memory,                bgfx_memory_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Transform,             bgfx_transform_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::HMD::Eye,              bgfx_hmd_eye_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::HMD,                   bgfx_hmd_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Stats,                 bgfx_stats_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::VertexDecl,            bgfx_vertex_decl_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::TransientIndexBuffer,  bgfx_transient_index_buffer_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::TransientVertexBuffer, bgfx_transient_vertex_buffer_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::InstanceDataBuffer,    bgfx_instance_data_buffer_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::TextureInfo,           bgfx_texture_info_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::UniformInfo,           bgfx_uniform_info_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Attachment,            bgfx_attachment_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Caps::GPU,             bgfx_caps_gpu_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Caps::Limits,          bgfx_caps_limits_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::Caps,                  bgfx_caps_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::PlatformData,          bgfx_platform_data_t);
BGFX_C99_STRUCT_SIZE_CHECK(bgfx::InternalData,          bgfx_internal_data_t);
#undef BGFX_C99_STRUCT_SIZE_CHECK

namespace bgfx
{
	struct CallbackC99 : public CallbackI
	{
		virtual ~CallbackC99()
		{
		}

		virtual void fatal(Fatal::Enum _code, const char* _str) override
		{
			m_interface->vtbl->fatal(m_interface, (bgfx_fatal_t)_code, _str);
		}

		virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) override
		{
			m_interface->vtbl->trace_vargs(m_interface, _filePath, _line, _format, _argList);
		}

		virtual void profilerBegin(const char* _name, uint32_t _abgr, const char* _filePath, uint16_t _line) override
		{
			m_interface->vtbl->profiler_begin(m_interface, _name, _abgr, _filePath, _line);
		}

		virtual void profilerBeginLiteral(const char* _name, uint32_t _abgr, const char* _filePath, uint16_t _line) override
		{
			m_interface->vtbl->profiler_begin_literal(m_interface, _name, _abgr, _filePath, _line);
		}

		virtual void profilerEnd() override
		{
			m_interface->vtbl->profiler_end(m_interface);
		}

		virtual uint32_t cacheReadSize(uint64_t _id) override
		{
			return m_interface->vtbl->cache_read_size(m_interface, _id);
		}

		virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) override
		{
			return m_interface->vtbl->cache_read(m_interface, _id, _data, _size);
		}

		virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) override
		{
			m_interface->vtbl->cache_write(m_interface, _id, _data, _size);
		}

		virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t _size, bool _yflip) override
		{
			m_interface->vtbl->screen_shot(m_interface, _filePath, _width, _height, _pitch, _data, _size, _yflip);
		}

		virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch, TextureFormat::Enum _format, bool _yflip) override
		{
			m_interface->vtbl->capture_begin(m_interface, _width, _height, _pitch, (bgfx_texture_format_t)_format, _yflip);
		}

		virtual void captureEnd() override
		{
			m_interface->vtbl->capture_end(m_interface);
		}

		virtual void captureFrame(const void* _data, uint32_t _size) override
		{
			m_interface->vtbl->capture_frame(m_interface, _data, _size);
		}

		bgfx_callback_interface_t* m_interface;
	};

	class AllocatorC99 : public bx::AllocatorI
	{
	public:
		virtual ~AllocatorC99()
		{
		}

		virtual void* realloc(void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line) override
		{
			return m_interface->vtbl->realloc(m_interface, _ptr, _size, _align, _file, _line);
		}

		bgfx_allocator_interface_t* m_interface;
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

uint32_t bgfx_topology_convert(bgfx_topology_convert_t _conversion, void* _dst, uint32_t _dstSize, const void* _indices, uint32_t _numIndices, bool _index32)
{
	return bgfx::topologyConvert(bgfx::TopologyConvert::Enum(_conversion), _dst, _dstSize, _indices, _numIndices, _index32);
}

void bgfx_topology_sort_tri_list(bgfx_topology_sort_t _sort, void* _dst, uint32_t _dstSize, const float _dir[3], const float _pos[3], const void* _vertices, uint32_t _stride, const void* _indices, uint32_t _numIndices, bool _index32)
{
	bgfx::topologySortTriList(bgfx::TopologySort::Enum(_sort), _dst, _dstSize, _dir, _pos, _vertices, _stride, _indices, _numIndices, _index32);
}

BGFX_C_API uint8_t bgfx_get_supported_renderers(uint8_t _max, bgfx_renderer_type_t* _enum)
{
	return bgfx::getSupportedRenderers(_max, (bgfx::RendererType::Enum*)_enum);
}

BGFX_C_API const char* bgfx_get_renderer_name(bgfx_renderer_type_t _type)
{
	return bgfx::getRendererName(bgfx::RendererType::Enum(_type) );
}

BGFX_C_API bool bgfx_init(bgfx_renderer_type_t _type, uint16_t _vendorId, uint16_t _deviceId, bgfx_callback_interface_t* _callback, bgfx_allocator_interface_t* _allocator)
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

BGFX_C_API uint32_t bgfx_frame(bool _capture)
{
	return bgfx::frame(_capture);
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

BGFX_C_API void bgfx_dbg_text_vprintf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList)
{
	bgfx::dbgTextPrintfVargs(_x, _y, _attr, _format, _argList);
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
	bgfx::destroy(handle.cpp);
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
	bgfx::destroy(handle.cpp);
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
	bgfx::destroy(handle.cpp);
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
	bgfx::destroy(handle.cpp);
}

BGFX_C_API uint32_t bgfx_get_avail_transient_index_buffer(uint32_t _num)
{
	return bgfx::getAvailTransientIndexBuffer(_num);
}

BGFX_C_API uint32_t bgfx_get_avail_transient_vertex_buffer(uint32_t _num, const bgfx_vertex_decl_t* _decl)
{
	const bgfx::VertexDecl& decl = *(const bgfx::VertexDecl*)_decl;
	return bgfx::getAvailTransientVertexBuffer(_num, decl);
}

BGFX_C_API uint32_t bgfx_get_avail_instance_data_buffer(uint32_t _num, uint16_t _stride)
{
	return bgfx::getAvailInstanceDataBuffer(_num, _stride);
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

BGFX_C_API void bgfx_alloc_instance_data_buffer(bgfx_instance_data_buffer_t* _idb, uint32_t _num, uint16_t _stride)
{
	bgfx::allocInstanceDataBuffer( (bgfx::InstanceDataBuffer*)_idb, _num, _stride);
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
	bgfx::destroy(handle.cpp);
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

BGFX_C_API void bgfx_set_shader_name(bgfx_shader_handle_t _handle, const char* _name)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } handle = { _handle };
	bgfx::setName(handle.cpp, _name);
}

BGFX_C_API void bgfx_destroy_shader(bgfx_shader_handle_t _handle)
{
	union { bgfx_shader_handle_t c; bgfx::ShaderHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
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
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bool bgfx_is_texture_valid(uint16_t _depth, bool _cubeMap, uint16_t _numLayers, bgfx_texture_format_t _format, uint32_t _flags)
{
	return bgfx::isTextureValid(_depth, _cubeMap, _numLayers, bgfx::TextureFormat::Enum(_format), _flags);
}

BGFX_C_API void bgfx_calc_texture_size(bgfx_texture_info_t* _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format)
{
	bgfx::TextureInfo& info = *(bgfx::TextureInfo*)_info;
	bgfx::calcTextureSize(info, _width, _height, _depth, _cubeMap, _hasMips, _numLayers, bgfx::TextureFormat::Enum(_format) );
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture(const bgfx_memory_t* _mem, uint32_t _flags, uint8_t _skip, bgfx_texture_info_t* _info)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	bgfx::TextureInfo* info = (bgfx::TextureInfo*)_info;
	handle.cpp = bgfx::createTexture( (const bgfx::Memory*)_mem, _flags, _skip, info);
	return handle.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	handle.cpp = bgfx::createTexture2D(_width, _height, _hasMips, _numLayers, bgfx::TextureFormat::Enum(_format), _flags, (const bgfx::Memory*)_mem);
	return handle.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_2d_scaled(bgfx_backbuffer_ratio_t _ratio, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint32_t _flags)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	handle.cpp = bgfx::createTexture2D(bgfx::BackbufferRatio::Enum(_ratio), _hasMips, _numLayers, bgfx::TextureFormat::Enum(_format), _flags);
	return handle.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_3d(uint16_t _width, uint16_t _height, uint16_t _depth, bool _hasMips, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	handle.cpp = bgfx::createTexture3D(_width, _height, _depth, _hasMips, bgfx::TextureFormat::Enum(_format), _flags, (const bgfx::Memory*)_mem);
	return handle.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_create_texture_cube(uint16_t _size, bool _hasMips, uint16_t _numLayers, bgfx_texture_format_t _format, uint32_t _flags, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle;
	handle.cpp = bgfx::createTextureCube(_size, _hasMips, _numLayers, bgfx::TextureFormat::Enum(_format), _flags, (const bgfx::Memory*)_mem);
	return handle.c;
}

BGFX_C_API void bgfx_update_texture_2d(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::updateTexture2D(handle.cpp, _layer, _mip, _x, _y, _width, _height, (const bgfx::Memory*)_mem, _pitch);
}

BGFX_C_API void bgfx_update_texture_3d(bgfx_texture_handle_t _handle, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, const bgfx_memory_t* _mem)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::updateTexture3D(handle.cpp, _mip, _x, _y, _z, _width, _height, _depth, (const bgfx::Memory*)_mem);
}

BGFX_C_API void bgfx_update_texture_cube(bgfx_texture_handle_t _handle, uint16_t _layer, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const bgfx_memory_t* _mem, uint16_t _pitch)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::updateTextureCube(handle.cpp, _layer, _side, _mip, _x, _y, _width, _height, (const bgfx::Memory*)_mem, _pitch);
}

BGFX_C_API uint32_t bgfx_read_texture(bgfx_texture_handle_t _handle, void* _data, uint8_t _mip)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	return bgfx::readTexture(handle.cpp, _data, _mip);
}

BGFX_C_API void bgfx_set_texture_name(bgfx_texture_handle_t _handle, const char* _name)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::setName(handle.cpp, _name);
}

BGFX_C_API void* bgfx_get_direct_access_ptr(bgfx_texture_handle_t _handle)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	return bgfx::getDirectAccessPtr(handle.cpp);
}

BGFX_C_API void bgfx_destroy_texture(bgfx_texture_handle_t _handle)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
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

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_attachment(uint8_t _num, const bgfx_attachment_t* _attachment, bool _destroyTextures)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle;
	handle.cpp = bgfx::createFrameBuffer(_num, (const bgfx::Attachment*)_attachment, _destroyTextures);
	return handle.c;
}

BGFX_C_API bgfx_frame_buffer_handle_t bgfx_create_frame_buffer_from_nwh(void* _nwh, uint16_t _width, uint16_t _height, bgfx_texture_format_t _depthFormat)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle;
	handle.cpp = bgfx::createFrameBuffer(_nwh, _width, _height, bgfx::TextureFormat::Enum(_depthFormat) );
	return handle.c;
}

BGFX_C_API bgfx_texture_handle_t bgfx_get_texture(bgfx_frame_buffer_handle_t _handle, uint8_t _attachment)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } textureHandle;
	textureHandle.cpp = bgfx::getTexture(handle.cpp, _attachment);
	return textureHandle.c;
}

BGFX_C_API void bgfx_destroy_frame_buffer(bgfx_frame_buffer_handle_t _handle)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_uniform_handle_t bgfx_create_uniform(const char* _name, bgfx_uniform_type_t _type, uint16_t _num)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle;
	handle.cpp = bgfx::createUniform(_name, bgfx::UniformType::Enum(_type), _num);
	return handle.c;
}

BGFX_C_API void bgfx_get_uniform_info(bgfx_uniform_handle_t _handle, bgfx_uniform_info_t* _info)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle = { _handle };
	bgfx::UniformInfo& info = *(bgfx::UniformInfo*)_info;
	bgfx::getUniformInfo(handle.cpp, info);
}

BGFX_C_API void bgfx_destroy_uniform(bgfx_uniform_handle_t _handle)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API bgfx_occlusion_query_handle_t bgfx_create_occlusion_query()
{
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle;
	handle.cpp = bgfx::createOcclusionQuery();
	return handle.c;
}

BGFX_C_API bgfx_occlusion_query_result_t bgfx_get_result(bgfx_occlusion_query_handle_t _handle, int32_t* _result)
{
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle = { _handle };
	return bgfx_occlusion_query_result_t(bgfx::getResult(handle.cpp, _result) );
}

BGFX_C_API void bgfx_destroy_occlusion_query(bgfx_occlusion_query_handle_t _handle)
{
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle = { _handle };
	bgfx::destroy(handle.cpp);
}

BGFX_C_API void bgfx_set_palette_color(uint8_t _index, const float _rgba[4])
{
	bgfx::setPaletteColor(_index, _rgba);
}

BGFX_C_API void bgfx_set_view_name(bgfx_view_id_t _id, const char* _name)
{
	bgfx::setViewName(_id, _name);
}

BGFX_C_API void bgfx_set_view_rect(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	bgfx::setViewRect(_id, _x, _y, _width, _height);
}

BGFX_C_API void bgfx_set_view_rect_auto(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, bgfx_backbuffer_ratio_t _ratio)
{
	bgfx::setViewRect(_id, _x, _y, bgfx::BackbufferRatio::Enum(_ratio));
}

BGFX_C_API void bgfx_set_view_scissor(bgfx_view_id_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	bgfx::setViewScissor(_id, _x, _y, _width, _height);
}

BGFX_C_API void bgfx_set_view_clear(bgfx_view_id_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
{
	bgfx::setViewClear(_id, _flags, _rgba, _depth, _stencil);
}

BGFX_C_API void bgfx_set_view_clear_mrt(bgfx_view_id_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7)
{
	bgfx::setViewClear(_id, _flags, _depth, _stencil, _0, _1, _2, _3, _4, _5, _6, _7);
}

BGFX_C_API void bgfx_set_view_mode(bgfx_view_id_t _id, bgfx_view_mode_t _mode)
{
	bgfx::setViewMode(_id, bgfx::ViewMode::Enum(_mode) );
}

BGFX_C_API void bgfx_set_view_frame_buffer(bgfx_view_id_t _id, bgfx_frame_buffer_handle_t _handle)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	bgfx::setViewFrameBuffer(_id, handle.cpp);
}

BGFX_C_API void bgfx_set_view_transform(bgfx_view_id_t _id, const void* _view, const void* _proj)
{
	bgfx::setViewTransform(_id, _view, _proj);
}

BGFX_C_API void bgfx_set_view_transform_stereo(bgfx_view_id_t _id, const void* _view, const void* _projL, uint8_t _flags, const void* _projR)
{
	bgfx::setViewTransform(_id, _view, _projL, _flags, _projR);
}

BGFX_C_API void bgfx_set_view_order(bgfx_view_id_t _id, uint16_t _num, const bgfx_view_id_t* _order)
{
	bgfx::setViewOrder(_id, _num, _order);
}

BGFX_C_API void bgfx_reset_view(bgfx_view_id_t _id)
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

BGFX_C_API void bgfx_set_condition(bgfx_occlusion_query_handle_t _handle, bool _visible)
{
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle = { _handle };
	bgfx::setCondition(handle.cpp, _visible);
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

BGFX_C_API void bgfx_set_vertex_buffer(uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	bgfx::setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_set_dynamic_vertex_buffer(uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	bgfx::setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices);
}

BGFX_C_API void bgfx_set_transient_vertex_buffer(uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices)
{
	bgfx::setVertexBuffer(_stream, (const bgfx::TransientVertexBuffer*)_tvb, _startVertex, _numVertices);
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

BGFX_C_API void bgfx_touch(bgfx_view_id_t _id)
{
	return bgfx::touch(_id);
}

BGFX_C_API void bgfx_submit(bgfx_view_id_t _id, bgfx_program_handle_t _handle, int32_t _depth, bool _preserveState)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	bgfx::submit(_id, handle.cpp, _depth, _preserveState);
}

BGFX_C_API void bgfx_submit_occlusion_query(bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, int32_t _depth, bool _preserveState)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	union { bgfx_occlusion_query_handle c; bgfx::OcclusionQueryHandle cpp; } occlusionQuery = { _occlusionQuery };
	bgfx::submit(_id, program.cpp, occlusionQuery.cpp, _depth, _preserveState);
}

BGFX_C_API void bgfx_submit_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, int32_t _depth, bool _preserveState)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	bgfx::submit(_id, handle.cpp, indirectHandle.cpp, _start, _num, _depth, _preserveState);
}

BGFX_C_API void bgfx_set_image(uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } sampler = { _sampler };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle  = { _handle  };
	bgfx::setImage(_stage, sampler.cpp, handle.cpp, _mip, bgfx::Access::Enum(_access), bgfx::TextureFormat::Enum(_format) );
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

BGFX_C_API void bgfx_dispatch(bgfx_view_id_t _id, bgfx_program_handle_t _handle, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	bgfx::dispatch(_id, handle.cpp, _numX, _numY, _numZ, _flags);
}

BGFX_C_API void bgfx_dispatch_indirect(bgfx_view_id_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	bgfx::dispatch(_id, handle.cpp, indirectHandle.cpp, _start, _num, _flags);
}

BGFX_C_API void bgfx_discard()
{
	bgfx::discard();
}

BGFX_C_API void bgfx_blit(bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } dst = { _dst };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } src = { _src };
	bgfx::blit(_id, dst.cpp, _dstMip, _dstX, _dstY, _dstZ, src.cpp, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
}

#define BGFX_ENCODER(_func) reinterpret_cast<bgfx::Encoder*>(_encoder)->_func

BGFX_C_API void bgfx_encoder_set_marker(bgfx_encoder* _encoder, const char* _marker)
{
	BGFX_ENCODER(setMarker(_marker) );
}

BGFX_C_API void bgfx_encoder_set_state(bgfx_encoder* _encoder, uint64_t _state, uint32_t _rgba)
{
	BGFX_ENCODER(setState(_state, _rgba) );
}

BGFX_C_API void bgfx_encoder_set_condition(bgfx_encoder* _encoder, bgfx_occlusion_query_handle_t _handle, bool _visible)
{
	union { bgfx_occlusion_query_handle_t c; bgfx::OcclusionQueryHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setCondition(handle.cpp, _visible) );
}

BGFX_C_API void bgfx_encoder_set_stencil(bgfx_encoder* _encoder, uint32_t _fstencil, uint32_t _bstencil)
{
	BGFX_ENCODER(setStencil(_fstencil, _bstencil) );
}

BGFX_C_API uint16_t bgfx_encoder_set_scissor(bgfx_encoder* _encoder, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	return BGFX_ENCODER(setScissor(_x, _y, _width, _height) );
}

BGFX_C_API void bgfx_encoder_set_scissor_cached(bgfx_encoder* _encoder, uint16_t _cache)
{
	BGFX_ENCODER(setScissor(_cache) );
}

BGFX_C_API uint32_t bgfx_encoder_set_transform(bgfx_encoder* _encoder, const void* _mtx, uint16_t _num)
{
	return BGFX_ENCODER(setTransform(_mtx, _num) );
}

BGFX_C_API uint32_t bgfx_encoder_alloc_transform(bgfx_encoder* _encoder, bgfx_transform_t* _transform, uint16_t _num)
{
	return BGFX_ENCODER(allocTransform( (bgfx::Transform*)_transform, _num) );
}

BGFX_C_API void bgfx_encoder_set_transform_cached(bgfx_encoder* _encoder, uint32_t _cache, uint16_t _num)
{
	BGFX_ENCODER(setTransform(_cache, _num) );
}

BGFX_C_API void bgfx_encoder_set_uniform(bgfx_encoder* _encoder, bgfx_uniform_handle_t _handle, const void* _value, uint16_t _num)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setUniform(handle.cpp, _value, _num) );
}

BGFX_C_API void bgfx_encoder_set_index_buffer(bgfx_encoder* _encoder, bgfx_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setIndexBuffer(handle.cpp, _firstIndex, _numIndices) );
}

BGFX_C_API void bgfx_encoder_set_dynamic_index_buffer(bgfx_encoder* _encoder, bgfx_dynamic_index_buffer_handle_t _handle, uint32_t _firstIndex, uint32_t _numIndices)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setIndexBuffer(handle.cpp, _firstIndex, _numIndices) );
}

BGFX_C_API void bgfx_encoder_set_transient_index_buffer(bgfx_encoder* _encoder, const bgfx_transient_index_buffer_t* _tib, uint32_t _firstIndex, uint32_t _numIndices)
{
	BGFX_ENCODER(setIndexBuffer( (const bgfx::TransientIndexBuffer*)_tib, _firstIndex, _numIndices) );
}

BGFX_C_API void bgfx_encoder_set_vertex_buffer(bgfx_encoder* _encoder, uint8_t _stream, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices) );
}

BGFX_C_API void bgfx_encoder_set_dynamic_vertex_buffer(bgfx_encoder* _encoder, uint8_t _stream, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _numVertices)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setVertexBuffer(_stream, handle.cpp, _startVertex, _numVertices) );
}

BGFX_C_API void bgfx_encoder_set_transient_vertex_buffer(bgfx_encoder* _encoder, uint8_t _stream, const bgfx_transient_vertex_buffer_t* _tvb, uint32_t _startVertex, uint32_t _numVertices)
{
	BGFX_ENCODER(setVertexBuffer(_stream, (const bgfx::TransientVertexBuffer*)_tvb, _startVertex, _numVertices) );
}

BGFX_C_API void bgfx_encoder_set_instance_data_buffer(bgfx_encoder* _encoder, const bgfx_instance_data_buffer_t* _idb, uint32_t _num)
{
	BGFX_ENCODER(setInstanceDataBuffer( (const bgfx::InstanceDataBuffer*)_idb, _num) );
}

BGFX_C_API void bgfx_encoder_set_instance_data_from_vertex_buffer(bgfx_encoder* _encoder, bgfx_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setInstanceDataBuffer(handle.cpp, _startVertex, _num) );
}

BGFX_C_API void bgfx_encoder_set_instance_data_from_dynamic_vertex_buffer(bgfx_encoder* _encoder, bgfx_dynamic_vertex_buffer_handle_t _handle, uint32_t _startVertex, uint32_t _num)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setInstanceDataBuffer(handle.cpp, _startVertex, _num) );
}

BGFX_C_API void bgfx_encoder_set_texture(bgfx_encoder* _encoder, uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint32_t _flags)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } sampler = { _sampler };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle  = { _handle  };
	BGFX_ENCODER(setTexture(_stage, sampler.cpp, handle.cpp, _flags) );
}

BGFX_C_API void bgfx_encoder_touch(bgfx_encoder* _encoder, bgfx_view_id_t _id)
{
	return BGFX_ENCODER(touch(_id) );
}

BGFX_C_API void bgfx_encoder_submit(bgfx_encoder* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _handle, int32_t _depth, bool _preserveState)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	BGFX_ENCODER(submit(_id, handle.cpp, _depth, _preserveState) );
}

BGFX_C_API void bgfx_encoder_submit_occlusion_query(bgfx_encoder* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _program, bgfx_occlusion_query_handle_t _occlusionQuery, int32_t _depth, bool _preserveState)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } program = { _program };
	union { bgfx_occlusion_query_handle c; bgfx::OcclusionQueryHandle cpp; } occlusionQuery = { _occlusionQuery };
	BGFX_ENCODER(submit(_id, program.cpp, occlusionQuery.cpp, _depth, _preserveState) );
}

BGFX_C_API void bgfx_encoder_submit_indirect(bgfx_encoder* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, int32_t _depth, bool _preserveState)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	BGFX_ENCODER(submit(_id, handle.cpp, indirectHandle.cpp, _start, _num, _depth, _preserveState) );
}

BGFX_C_API void bgfx_encoder_set_image(bgfx_encoder* _encoder, uint8_t _stage, bgfx_uniform_handle_t _sampler, bgfx_texture_handle_t _handle, uint8_t _mip, bgfx_access_t _access, bgfx_texture_format_t _format)
{
	union { bgfx_uniform_handle_t c; bgfx::UniformHandle cpp; } sampler = { _sampler };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle  = { _handle  };
	BGFX_ENCODER(setImage(_stage, sampler.cpp, handle.cpp, _mip, bgfx::Access::Enum(_access), bgfx::TextureFormat::Enum(_format) ) );
}

BGFX_C_API void bgfx_encoder_set_compute_index_buffer(bgfx_encoder* _encoder, uint8_t _stage, bgfx_index_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_index_buffer_handle_t c; bgfx::IndexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) ) );
}

BGFX_C_API void bgfx_encoder_set_compute_vertex_buffer(bgfx_encoder* _encoder, uint8_t _stage, bgfx_vertex_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_vertex_buffer_handle_t c; bgfx::VertexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) ) );
}

BGFX_C_API void bgfx_encoder_set_compute_dynamic_index_buffer(bgfx_encoder* _encoder, uint8_t _stage, bgfx_dynamic_index_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_dynamic_index_buffer_handle_t c; bgfx::DynamicIndexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) ) );
}

BGFX_C_API void bgfx_encoder_set_compute_dynamic_vertex_buffer(bgfx_encoder* _encoder, uint8_t _stage, bgfx_dynamic_vertex_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_dynamic_vertex_buffer_handle_t c; bgfx::DynamicVertexBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) ) );
}

BGFX_C_API void bgfx_encoder_set_compute_indirect_buffer(bgfx_encoder* _encoder, uint8_t _stage, bgfx_indirect_buffer_handle_t _handle, bgfx_access_t _access)
{
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } handle = { _handle };
	BGFX_ENCODER(setBuffer(_stage, handle.cpp, bgfx::Access::Enum(_access) ) );
}

BGFX_C_API void bgfx_encoder_dispatch(bgfx_encoder* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _handle, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	BGFX_ENCODER(dispatch(_id, handle.cpp, _numX, _numY, _numZ, _flags) );
}

BGFX_C_API void bgfx_encoder_dispatch_indirect(bgfx_encoder* _encoder, bgfx_view_id_t _id, bgfx_program_handle_t _handle, bgfx_indirect_buffer_handle_t _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
{
	union { bgfx_program_handle_t c; bgfx::ProgramHandle cpp; } handle = { _handle };
	union { bgfx_indirect_buffer_handle_t c; bgfx::IndirectBufferHandle cpp; } indirectHandle = { _indirectHandle };
	BGFX_ENCODER(dispatch(_id, handle.cpp, indirectHandle.cpp, _start, _num, _flags) );
}

BGFX_C_API void bgfx_encoder_discard(bgfx_encoder* _encoder)
{
	BGFX_ENCODER(discard() );
}

BGFX_C_API void bgfx_encoder_blit(bgfx_encoder* _encoder, bgfx_view_id_t _id, bgfx_texture_handle_t _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, bgfx_texture_handle_t _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } dst = { _dst };
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } src = { _src };
	BGFX_ENCODER(blit(_id, dst.cpp, _dstMip, _dstX, _dstY, _dstZ, src.cpp, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth) );
}

#undef BGFX_ENCODER

BGFX_C_API void bgfx_request_screen_shot(bgfx_frame_buffer_handle _handle, const char* _filePath)
{
	union { bgfx_frame_buffer_handle_t c; bgfx::FrameBufferHandle cpp; } handle = { _handle };
	bgfx::requestScreenShot(handle.cpp, _filePath);
}

BGFX_C_API bgfx_render_frame_t bgfx_render_frame(int32_t _msecs)
{
	return bgfx_render_frame_t(bgfx::renderFrame(_msecs) );
}

BGFX_C_API void bgfx_set_platform_data(const bgfx_platform_data_t* _data)
{
	bgfx::setPlatformData(*(const bgfx::PlatformData*)_data);
}

BGFX_C_API const bgfx_internal_data_t* bgfx_get_internal_data()
{
	return (const bgfx_internal_data_t*)bgfx::getInternalData();
}

BGFX_C_API uintptr_t bgfx_override_internal_texture_ptr(bgfx_texture_handle_t _handle, uintptr_t _ptr)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	return bgfx::overrideInternal(handle.cpp, _ptr);
}

BGFX_C_API uintptr_t bgfx_override_internal_texture(bgfx_texture_handle_t _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, bgfx_texture_format_t _format, uint32_t _flags)
{
	union { bgfx_texture_handle_t c; bgfx::TextureHandle cpp; } handle = { _handle };
	return bgfx::overrideInternal(handle.cpp, _width, _height, _numMips, bgfx::TextureFormat::Enum(_format), _flags);
}

BGFX_C_API bgfx_interface_vtbl_t* bgfx_get_interface(uint32_t _version)
{
	if (_version == BGFX_API_VERSION)
	{
#define BGFX_IMPORT                                                        \
	BGFX_IMPORT_FUNC(render_frame)                                         \
	BGFX_IMPORT_FUNC(set_platform_data)                                    \
	BGFX_IMPORT_FUNC(get_internal_data)                                    \
	BGFX_IMPORT_FUNC(override_internal_texture_ptr)                        \
	BGFX_IMPORT_FUNC(override_internal_texture)                            \
	BGFX_IMPORT_FUNC(vertex_decl_begin)                                    \
	BGFX_IMPORT_FUNC(vertex_decl_add)                                      \
	BGFX_IMPORT_FUNC(vertex_decl_skip)                                     \
	BGFX_IMPORT_FUNC(vertex_decl_end)                                      \
	BGFX_IMPORT_FUNC(vertex_pack)                                          \
	BGFX_IMPORT_FUNC(vertex_unpack)                                        \
	BGFX_IMPORT_FUNC(vertex_convert)                                       \
	BGFX_IMPORT_FUNC(weld_vertices)                                        \
	BGFX_IMPORT_FUNC(topology_convert)                                     \
	BGFX_IMPORT_FUNC(topology_sort_tri_list)                               \
	BGFX_IMPORT_FUNC(get_supported_renderers)                              \
	BGFX_IMPORT_FUNC(get_renderer_name)                                    \
	BGFX_IMPORT_FUNC(init)                                                 \
	BGFX_IMPORT_FUNC(shutdown)                                             \
	BGFX_IMPORT_FUNC(reset)                                                \
	BGFX_IMPORT_FUNC(frame)                                                \
	BGFX_IMPORT_FUNC(get_renderer_type)                                    \
	BGFX_IMPORT_FUNC(get_caps)                                             \
	BGFX_IMPORT_FUNC(get_hmd)                                              \
	BGFX_IMPORT_FUNC(get_stats)                                            \
	BGFX_IMPORT_FUNC(alloc)                                                \
	BGFX_IMPORT_FUNC(copy)                                                 \
	BGFX_IMPORT_FUNC(make_ref)                                             \
	BGFX_IMPORT_FUNC(make_ref_release)                                     \
	BGFX_IMPORT_FUNC(set_debug)                                            \
	BGFX_IMPORT_FUNC(dbg_text_clear)                                       \
	BGFX_IMPORT_FUNC(dbg_text_printf)                                      \
	BGFX_IMPORT_FUNC(dbg_text_vprintf)                                     \
	BGFX_IMPORT_FUNC(dbg_text_image)                                       \
	BGFX_IMPORT_FUNC(create_index_buffer)                                  \
	BGFX_IMPORT_FUNC(destroy_index_buffer)                                 \
	BGFX_IMPORT_FUNC(create_vertex_buffer)                                 \
	BGFX_IMPORT_FUNC(destroy_vertex_buffer)                                \
	BGFX_IMPORT_FUNC(create_dynamic_index_buffer)                          \
	BGFX_IMPORT_FUNC(create_dynamic_index_buffer_mem)                      \
	BGFX_IMPORT_FUNC(update_dynamic_index_buffer)                          \
	BGFX_IMPORT_FUNC(destroy_dynamic_index_buffer)                         \
	BGFX_IMPORT_FUNC(create_dynamic_vertex_buffer)                         \
	BGFX_IMPORT_FUNC(create_dynamic_vertex_buffer_mem)                     \
	BGFX_IMPORT_FUNC(update_dynamic_vertex_buffer)                         \
	BGFX_IMPORT_FUNC(destroy_dynamic_vertex_buffer)                        \
	BGFX_IMPORT_FUNC(get_avail_transient_index_buffer)                     \
	BGFX_IMPORT_FUNC(get_avail_transient_vertex_buffer)                    \
	BGFX_IMPORT_FUNC(get_avail_instance_data_buffer)                       \
	BGFX_IMPORT_FUNC(alloc_transient_index_buffer)                         \
	BGFX_IMPORT_FUNC(alloc_transient_vertex_buffer)                        \
	BGFX_IMPORT_FUNC(alloc_transient_buffers)                              \
	BGFX_IMPORT_FUNC(alloc_instance_data_buffer)                           \
	BGFX_IMPORT_FUNC(create_indirect_buffer)                               \
	BGFX_IMPORT_FUNC(destroy_indirect_buffer)                              \
	BGFX_IMPORT_FUNC(create_shader)                                        \
	BGFX_IMPORT_FUNC(get_shader_uniforms)                                  \
	BGFX_IMPORT_FUNC(set_shader_name)                                      \
	BGFX_IMPORT_FUNC(destroy_shader)                                       \
	BGFX_IMPORT_FUNC(create_program)                                       \
	BGFX_IMPORT_FUNC(create_compute_program)                               \
	BGFX_IMPORT_FUNC(destroy_program)                                      \
	BGFX_IMPORT_FUNC(is_texture_valid)                                     \
	BGFX_IMPORT_FUNC(calc_texture_size)                                    \
	BGFX_IMPORT_FUNC(create_texture)                                       \
	BGFX_IMPORT_FUNC(create_texture_2d)                                    \
	BGFX_IMPORT_FUNC(create_texture_2d_scaled)                             \
	BGFX_IMPORT_FUNC(create_texture_3d)                                    \
	BGFX_IMPORT_FUNC(create_texture_cube)                                  \
	BGFX_IMPORT_FUNC(update_texture_2d)                                    \
	BGFX_IMPORT_FUNC(update_texture_3d)                                    \
	BGFX_IMPORT_FUNC(update_texture_cube)                                  \
	BGFX_IMPORT_FUNC(read_texture)                                         \
	BGFX_IMPORT_FUNC(set_texture_name)                                     \
	BGFX_IMPORT_FUNC(get_direct_access_ptr)                                \
	BGFX_IMPORT_FUNC(destroy_texture)                                      \
	BGFX_IMPORT_FUNC(create_frame_buffer)                                  \
	BGFX_IMPORT_FUNC(create_frame_buffer_scaled)                           \
	BGFX_IMPORT_FUNC(create_frame_buffer_from_attachment)                  \
	BGFX_IMPORT_FUNC(create_frame_buffer_from_nwh)                         \
	BGFX_IMPORT_FUNC(get_texture)                                          \
	BGFX_IMPORT_FUNC(destroy_frame_buffer)                                 \
	BGFX_IMPORT_FUNC(create_uniform)                                       \
	BGFX_IMPORT_FUNC(get_uniform_info)                                     \
	BGFX_IMPORT_FUNC(destroy_uniform)                                      \
	BGFX_IMPORT_FUNC(create_occlusion_query)                               \
	BGFX_IMPORT_FUNC(get_result)                                           \
	BGFX_IMPORT_FUNC(destroy_occlusion_query)                              \
	BGFX_IMPORT_FUNC(set_palette_color)                                    \
	BGFX_IMPORT_FUNC(set_view_name)                                        \
	BGFX_IMPORT_FUNC(set_view_rect)                                        \
	BGFX_IMPORT_FUNC(set_view_scissor)                                     \
	BGFX_IMPORT_FUNC(set_view_clear)                                       \
	BGFX_IMPORT_FUNC(set_view_clear_mrt)                                   \
	BGFX_IMPORT_FUNC(set_view_mode)                                        \
	BGFX_IMPORT_FUNC(set_view_frame_buffer)                                \
	BGFX_IMPORT_FUNC(set_view_transform)                                   \
	BGFX_IMPORT_FUNC(set_view_transform_stereo)                            \
	BGFX_IMPORT_FUNC(set_view_order)                                       \
	BGFX_IMPORT_FUNC(encoder_set_marker)                                   \
	BGFX_IMPORT_FUNC(encoder_set_state)                                    \
	BGFX_IMPORT_FUNC(encoder_set_condition)                                \
	BGFX_IMPORT_FUNC(encoder_set_stencil)                                  \
	BGFX_IMPORT_FUNC(encoder_set_scissor)                                  \
	BGFX_IMPORT_FUNC(encoder_set_scissor_cached)                           \
	BGFX_IMPORT_FUNC(encoder_set_transform)                                \
	BGFX_IMPORT_FUNC(encoder_alloc_transform)                              \
	BGFX_IMPORT_FUNC(encoder_set_transform_cached)                         \
	BGFX_IMPORT_FUNC(encoder_set_uniform)                                  \
	BGFX_IMPORT_FUNC(encoder_set_index_buffer)                             \
	BGFX_IMPORT_FUNC(encoder_set_dynamic_index_buffer)                     \
	BGFX_IMPORT_FUNC(encoder_set_transient_index_buffer)                   \
	BGFX_IMPORT_FUNC(encoder_set_vertex_buffer)                            \
	BGFX_IMPORT_FUNC(encoder_set_dynamic_vertex_buffer)                    \
	BGFX_IMPORT_FUNC(encoder_set_transient_vertex_buffer)                  \
	BGFX_IMPORT_FUNC(encoder_set_instance_data_buffer)                     \
	BGFX_IMPORT_FUNC(encoder_set_instance_data_from_vertex_buffer)         \
	BGFX_IMPORT_FUNC(encoder_set_instance_data_from_dynamic_vertex_buffer) \
	BGFX_IMPORT_FUNC(encoder_set_texture)                                  \
	BGFX_IMPORT_FUNC(encoder_touch)                                        \
	BGFX_IMPORT_FUNC(encoder_submit)                                       \
	BGFX_IMPORT_FUNC(encoder_submit_occlusion_query)                       \
	BGFX_IMPORT_FUNC(encoder_submit_indirect)                              \
	BGFX_IMPORT_FUNC(encoder_set_image)                                    \
	BGFX_IMPORT_FUNC(encoder_set_compute_index_buffer)                     \
	BGFX_IMPORT_FUNC(encoder_set_compute_vertex_buffer)                    \
	BGFX_IMPORT_FUNC(encoder_set_compute_dynamic_index_buffer)             \
	BGFX_IMPORT_FUNC(encoder_set_compute_dynamic_vertex_buffer)            \
	BGFX_IMPORT_FUNC(encoder_set_compute_indirect_buffer)                  \
	BGFX_IMPORT_FUNC(encoder_dispatch)                                     \
	BGFX_IMPORT_FUNC(encoder_dispatch_indirect)                            \
	BGFX_IMPORT_FUNC(encoder_discard)                                      \
	BGFX_IMPORT_FUNC(encoder_blit)                                         \
	BGFX_IMPORT_FUNC(request_screen_shot)

		static bgfx_interface_vtbl_t s_bgfx_interface =
		{
#define BGFX_IMPORT_FUNC(_name) BX_CONCATENATE(bgfx_, _name),
			BGFX_IMPORT
#undef BGFX_IMPORT_FUNC
		};

		return &s_bgfx_interface;
	}

	return NULL;
}
