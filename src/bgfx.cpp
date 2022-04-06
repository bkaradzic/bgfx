/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bx/platform.h>

#include "bgfx_p.h"
#include <bgfx/embedded_shader.h>
#include <bx/file.h>
#include <bx/mutex.h>

#include "topology.h"

#if BX_PLATFORM_OSX || BX_PLATFORM_IOS
#	include <objc/message.h>
#elif BX_PLATFORM_WINDOWS
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif // WIN32_LEAN_AND_MEAN
#	include <windows.h>
#endif // BX_PLATFORM_OSX

BX_ERROR_RESULT(BGFX_ERROR_TEXTURE_VALIDATION,      BX_MAKEFOURCC('b', 'g', 0, 1) );
BX_ERROR_RESULT(BGFX_ERROR_FRAME_BUFFER_VALIDATION, BX_MAKEFOURCC('b', 'g', 0, 2) );
BX_ERROR_RESULT(BGFX_ERROR_IDENTIFIER_VALIDATION,   BX_MAKEFOURCC('b', 'g', 0, 3) );

namespace bgfx
{
#define BGFX_API_THREAD_MAGIC UINT32_C(0x78666762)

#if BGFX_CONFIG_MULTITHREADED

#	define BGFX_CHECK_API_THREAD()                                   \
		BX_ASSERT(NULL != s_ctx, "Library is not initialized yet."); \
		BX_ASSERT(BGFX_API_THREAD_MAGIC == s_threadIndex, "Must be called from main thread.")

#	define BGFX_CHECK_RENDER_THREAD()                         \
		BX_ASSERT( (NULL != s_ctx && s_ctx->m_singleThreaded) \
			|| ~BGFX_API_THREAD_MAGIC == s_threadIndex        \
			, "Must be called from render thread."            \
			)

#else
#	define BGFX_CHECK_API_THREAD()
#	define BGFX_CHECK_RENDER_THREAD()
#endif // BGFX_CONFIG_MULTITHREADED

#define BGFX_CHECK_CAPS(_caps, _msg)                                                   \
	BX_ASSERT(0 != (g_caps.supported & (_caps) )                                       \
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

		virtual void fatal(const char* _filePath, uint16_t _line, Fatal::Enum _code, const char* _str) override
		{
			bgfx::trace(_filePath, _line, "BGFX FATAL 0x%08x: %s\n", _code, _str);

			if (Fatal::DebugCheck == _code)
			{
				bx::debugBreak();
			}
			else
			{
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
							BX_ASSERT(m_numBlocks > 0, "Number of blocks is 0. Possible alloc/free mismatch?");
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
						m_maxBlocks = bx::max(m_maxBlocks, m_numBlocks);
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
					m_maxBlocks = bx::max(m_maxBlocks, m_numBlocks);
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

	const char* getTypeName(Handle _handle)
	{
		switch (_handle.type)
		{
		case Handle::IndexBuffer:  return "IB";
		case Handle::Shader:       return "S";
		case Handle::Texture:      return "T";
		case Handle::VertexBuffer: return "VB";
		default:                   break;
		}

		BX_ASSERT(false, "You should not be here.");
		return "?";
	}

	void AllocatorStub::checkLeaks()
	{
#if BGFX_CONFIG_MEMORY_TRACKING
		// BK - CallbackStub will be deleted after printing this info, so there is always one
		// leak if CallbackStub is used.
		BX_WARN(uint32_t(NULL != s_callbackStub ? 1 : 0) == m_numBlocks
			, "\n\n"
			  "\n########################################################"
			  "\n"
			  "\nMEMORY LEAK: Number of leaked blocks %d (Max blocks: %d)"
			  "\n"
			  "\n########################################################"
			  "\n\n"
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

	uintptr_t overrideInternal(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, TextureFormat::Enum _format, uint64_t _flags)
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
		bx::write(&writer, magic, bx::ErrorAssert{});

		TextureCreate tc;
		tc.m_width     = _width;
		tc.m_height    = _height;
		tc.m_depth     = 0;
		tc.m_numLayers = 1;
		tc.m_numMips   = bx::max<uint8_t>(1, _numMips);
		tc.m_format    = _format;
		tc.m_cubeMap   = false;
		tc.m_mem       = NULL;
		bx::write(&writer, tc, bx::ErrorAssert{});

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

	void fatal(const char* _filePath, uint16_t _line, Fatal::Enum _code, const char* _format, ...)
	{
		va_list argList;
		va_start(argList, _format);

		char temp[8192];
		char* out = temp;
		int32_t len = bx::vsnprintf(out, sizeof(temp), _format, argList);
		if ( (int32_t)sizeof(temp) < len)
		{
			out = (char*)alloca(len+1);
			len = bx::vsnprintf(out, len, _format, argList);
		}
		out[len] = '\0';

		if (BX_UNLIKELY(NULL == g_callback) )
		{
			bx::debugPrintf("%s(%d): BGFX FATAL 0x%08x: %s", _filePath, _line, _code, out);
			abort();
		}
		else
		{
			g_callback->fatal(_filePath, _line, _code, out);
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

	void dump(const VertexLayout& _layout)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
		{
			BX_TRACE("VertexLayout %08x (%08x), stride %d"
				, _layout.m_hash
				, bx::hash<bx::HashMurmur2A>(_layout.m_attributes)
				, _layout.m_stride
				);

			for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
			{
				if (UINT16_MAX != _layout.m_attributes[attr])
				{
					uint8_t num;
					AttribType::Enum type;
					bool normalized;
					bool asInt;
					_layout.decode(Attrib::Enum(attr), num, type, normalized, asInt);

					BX_TRACE("\tattr %2d: %-20s num %d, type %d, norm [%c], asint [%c], offset %2d"
						, attr
						, getAttribName(Attrib::Enum(attr) )
						, num
						, type
						, normalized ? 'x' : ' '
						, asInt      ? 'x' : ' '
						, _layout.m_offset[attr]
						);
				}
			}
		}
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
		const bx::StringView str = bx::strFind(_ptr, _to);
		if (!str.isEmpty()
		&&  3 > str.getPtr()-_ptr)
		{
			char tmp[4];

			int32_t len = int32_t(str.getPtr()-_ptr);
			bx::strCopy(tmp, sizeof(tmp), _ptr, len);

			uint32_t attr;
			bx::fromString(&attr, tmp);

			_ptr += len+1;
			return uint8_t(attr);
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
			MemSlot* mem = &m_mem[_y*m_width+_x];
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
					mem->character = ch;
					mem->attribute = attr;
					++mem;
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
		m_layout
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
			, BGFX_SAMPLER_MIN_POINT
			| BGFX_SAMPLER_MAG_POINT
			| BGFX_SAMPLER_MIP_POINT
			| BGFX_SAMPLER_U_CLAMP
			| BGFX_SAMPLER_V_CLAMP
			, mem
			);

		ShaderHandle vsh = createEmbeddedShader(s_embeddedShaders, g_caps.rendererType, "vs_debugfont");
		ShaderHandle fsh = createEmbeddedShader(s_embeddedShaders, g_caps.rendererType, "fs_debugfont");

		BX_ASSERT(isValid(vsh) && isValid(fsh), "Failed to create embedded blit shaders");

		m_program = createProgram(vsh, fsh, true);

		m_vb = s_ctx->createTransientVertexBuffer(numBatchVertices*m_layout.m_stride, &m_layout);
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

	static const uint32_t paletteSrgb[] =
	{
		0x0,        // Black
		0xffa46534, // Blue
		0xff069a4e, // Green
		0xff9a9806, // Cyan
		0xff0000cc, // Red
		0xff7b5075, // Magenta
		0xff00a0c4, // Brown
		0xffcfd7d3, // Light Gray
		0xff535755, // Dark Gray
		0xffcf9f72, // Light Blue
		0xff34e28a, // Light Green
		0xffe2e234, // Light Cyan
		0xff2929ef, // Light Red
		0xffa87fad, // Light Magenta
		0xff4fe9fc, // Yellow
		0xffeceeee, // White
	};
	BX_STATIC_ASSERT(BX_COUNTOF(paletteSrgb) == 16);

	static const uint32_t paletteLinear[] =
	{
		0x0,        // Black
		0xff5e2108, // Blue
		0xff005213, // Green
		0xff525000, // Cyan
		0xff000099, // Red
		0xff32142d, // Magenta
		0xff00598c, // Brown
		0xff9fada6, // Light Gray
		0xff161817, // Dark Gray
		0xff9f582a, // Light Blue
		0xff08c140, // Light Green
		0xffc1c108, // Light Cyan
		0xff0505dc, // Light Red
		0xff63366a, // Light Magenta
		0xff13cff8, // Yellow
		0xffd5dada  // White
	};
	BX_STATIC_ASSERT(BX_COUNTOF(paletteLinear) == 16);

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

		uint32_t yy = 0;
		uint32_t xx = 0;

		const float texelWidth      = 1.0f/2048.0f;
		const float texelWidthHalf  = RendererType::Direct3D9 == g_caps.rendererType ? 0.0f : texelWidth*0.5f;
		const float texelHeight     = 1.0f/24.0f;
		const float texelHeightHalf = RendererType::Direct3D9 == g_caps.rendererType ? texelHeight*0.5f : 0.0f;
		const float utop       = (_mem.m_small ? 0.0f :  8.0f)*texelHeight + texelHeightHalf;
		const float ubottom    = (_mem.m_small ? 8.0f : 24.0f)*texelHeight + texelHeightHalf;
		const float fontHeight = (_mem.m_small ? 8.0f : 16.0f);

		_renderCtx->blitSetup(_blitter);

		const uint32_t* palette = 0 != (s_ctx->m_init.resolution.reset & BGFX_RESET_SRGB_BACKBUFFER)
			? paletteLinear
			: paletteSrgb
			;

		for (;yy < _mem.m_height;)
		{
			Vertex* vertex = (Vertex*)_blitter.m_vb->data;
			uint16_t* indices = (uint16_t*)_blitter.m_ib->data;
			uint32_t startVertex = 0;
			uint32_t numIndices = 0;

			for (; yy < _mem.m_height && numIndices < numBatchIndices; ++yy)
			{
				xx = xx < _mem.m_width ? xx : 0;
				const TextVideoMem::MemSlot* line = &_mem.m_mem[yy*_mem.m_width+xx];

				for (; xx < _mem.m_width && numIndices < numBatchIndices; ++xx)
				{
					uint32_t ch = line->character;
					const uint8_t attr = line->attribute;

					if (ch > 0xff)
					{
						ch = 0;
					}

					if (0 != (ch|attr)
					&& (' ' != ch || 0 != (attr&0xf0) ) )
					{
						const uint32_t fg = palette[attr&0xf];
						const uint32_t bg = palette[(attr>>4)&0xf];

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

					line++;
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
			m_layout
				.begin()
				.add(Attrib::Position, 2, AttribType::Float)
				.end();

			ShaderHandle vsh = createEmbeddedShader(s_embeddedShaders, g_caps.rendererType, "vs_clear");
			BX_ASSERT(isValid(vsh), "Failed to create clear quad embedded vertex shader \"vs_clear\"");

			for (uint32_t ii = 0, num = g_caps.limits.maxFBAttachments; ii < num; ++ii)
			{
				char name[32];
				bx::snprintf(name, BX_COUNTOF(name), "fs_clear%d", ii);
				ShaderHandle fsh = createEmbeddedShader(s_embeddedShaders, g_caps.rendererType, name);
				BX_ASSERT(isValid(fsh), "Failed to create clear quad embedded fragment shader \"%s\"", name);

				m_program[ii] = createProgram(vsh, fsh);
				BX_ASSERT(isValid(m_program[ii]), "Failed to create clear quad program.");
				destroy(fsh);
			}

			destroy(vsh);

			struct Vertex
			{
				float m_x;
				float m_y;
			};

			const uint16_t stride = m_layout.m_stride;
			const bgfx::Memory* mem = bgfx::alloc(4 * stride);
			Vertex* vertex = (Vertex*)mem->data;
			BX_ASSERT(stride == sizeof(Vertex), "Stride/Vertex mismatch (stride %d, sizeof(Vertex) %d)", stride, sizeof(Vertex));

			vertex->m_x = -1.0f;
			vertex->m_y = -1.0f;
			vertex++;
			vertex->m_x = 1.0f;
			vertex->m_y = -1.0f;
			vertex++;
			vertex->m_x = -1.0f;
			vertex->m_y = 1.0f;
			vertex++;
			vertex->m_x = 1.0f;
			vertex->m_y = 1.0f;

			m_vb = s_ctx->createVertexBuffer(mem, m_layout, 0);
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

			s_ctx->destroyVertexBuffer(m_vb);
		}
	}

	const char* s_uniformTypeName[] =
	{
		"sampler1",
		NULL,
		"vec4",
		"mat3",
		"mat4",
	};
	BX_STATIC_ASSERT(UniformType::Count == BX_COUNTOF(s_uniformTypeName) );

	const char* getUniformTypeName(UniformType::Enum _enum)
	{
		BX_ASSERT(_enum < UniformType::Count, "%d < UniformType::Count %d", _enum, UniformType::Count);
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

	PredefinedUniform::Enum nameToPredefinedUniformEnum(const bx::StringView& _name)
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

	void srtToMatrix4_x1(void* _dst, const void* _src)
	{
		      Matrix4* mtx = reinterpret_cast<  Matrix4*>(_dst);
		const     Srt* srt = reinterpret_cast<const Srt*>(_src);

		const float rx = srt->rotate[0];
		const float ry = srt->rotate[1];
		const float rz = srt->rotate[2];
		const float rw = srt->rotate[3];

		const float xx2 = 2.0f * rx * rx;
		const float yy2 = 2.0f * ry * ry;
		const float zz2 = 2.0f * rz * rz;
		const float yx2 = 2.0f * ry * rx;
		const float yz2 = 2.0f * ry * rz;
		const float yw2 = 2.0f * ry * rw;
		const float wz2 = 2.0f * rw * rz;
		const float wx2 = 2.0f * rw * rx;
		const float xz2 = 2.0f * rx * rz;

		const float sx = srt->scale[0];
		const float sy = srt->scale[1];
		const float sz = srt->scale[2];

		mtx->un.val[ 0] = (1.0f - yy2 - zz2)*sx;
		mtx->un.val[ 1] = (       yx2 + wz2)*sx;
		mtx->un.val[ 2] = (       xz2 - yw2)*sx;
		mtx->un.val[ 3] = 0.0f;

		mtx->un.val[ 4] = (       yx2 - wz2)*sy;
		mtx->un.val[ 5] = (1.0f - xx2 - zz2)*sy;
		mtx->un.val[ 6] = (       yz2 + wx2)*sy;
		mtx->un.val[ 7] = 0.0f;

		mtx->un.val[ 8] = (       xz2 + yw2)*sz;
		mtx->un.val[ 9] = (       yz2 - wx2)*sz;
		mtx->un.val[10] = (1.0f - xx2 - yy2)*sz;
		mtx->un.val[11] = 0.0f;

		const float tx = srt->translate[0];
		const float ty = srt->translate[1];
		const float tz = srt->translate[2];

		mtx->un.val[12] = tx;
		mtx->un.val[13] = ty;
		mtx->un.val[14] = tz;
		mtx->un.val[15] = 1.0f;
	}

	void transpose(void* _dst, uint32_t _dstStride, const void* _src, uint32_t _srcStride = sizeof(bx::simd128_t) )
	{
		      uint8_t* dst = reinterpret_cast<      uint8_t *>(_dst);
		const uint8_t* src = reinterpret_cast<const uint8_t *>(_src);

		using namespace bx;

		const simd128_t r0 = simd_ld<simd128_t>(src);
		src += _srcStride;

		const simd128_t r1 = simd_ld<simd128_t>(src);
		src += _srcStride;

		const simd128_t r2 = simd_ld<simd128_t>(src);
		src += _srcStride;

		const simd128_t r3 = simd_ld<simd128_t>(src);

		const simd128_t aibj = simd_shuf_xAyB(r0,   r2);   // aibj
		const simd128_t emfn = simd_shuf_xAyB(r1,   r3);   // emfn
		const simd128_t ckdl = simd_shuf_zCwD(r0,   r2);   // ckdl
		const simd128_t gohp = simd_shuf_zCwD(r1,   r3);   // gohp
		const simd128_t aeim = simd_shuf_xAyB(aibj, emfn); // aeim
		const simd128_t bfjn = simd_shuf_zCwD(aibj, emfn); // bfjn
		const simd128_t cgko = simd_shuf_xAyB(ckdl, gohp); // cgko
		const simd128_t dhlp = simd_shuf_zCwD(ckdl, gohp); // dhlp

		simd_st(dst, aeim);
		dst += _dstStride;

		simd_st(dst, bfjn);
		dst += _dstStride;

		simd_st(dst, cgko);
		dst += _dstStride;

		simd_st(dst, dhlp);
	}

	void srtToMatrix4_x4_Ref(void* _dst, const void* _src)
	{
		      uint8_t* dst = reinterpret_cast<      uint8_t*>(_dst);
		const uint8_t* src = reinterpret_cast<const uint8_t*>(_src);

		srtToMatrix4_x1(dst + 0*sizeof(Matrix4), src + 0*sizeof(Srt) );
		srtToMatrix4_x1(dst + 1*sizeof(Matrix4), src + 1*sizeof(Srt) );
		srtToMatrix4_x1(dst + 2*sizeof(Matrix4), src + 2*sizeof(Srt) );
		srtToMatrix4_x1(dst + 3*sizeof(Matrix4), src + 3*sizeof(Srt) );
	}

	void srtToMatrix4_x4_Simd(void* _dst, const void* _src)
	{
		using namespace bx;

		      simd128_t* dst = reinterpret_cast<      simd128_t*>(_dst);
		const simd128_t* src = reinterpret_cast<const simd128_t*>(_src);

		simd128_t rotate[4];
		simd128_t translate[4];
		simd128_t scale[4];

		transpose(rotate,    sizeof(simd128_t), src + 0, sizeof(Srt) );
		transpose(translate, sizeof(simd128_t), src + 1, sizeof(Srt) );
		transpose(scale,     sizeof(simd128_t), src + 2, sizeof(Srt) );

		const simd128_t rx    = simd_ld<simd128_t>(rotate + 0);
		const simd128_t ry    = simd_ld<simd128_t>(rotate + 1);
		const simd128_t rz    = simd_ld<simd128_t>(rotate + 2);
		const simd128_t rw    = simd_ld<simd128_t>(rotate + 3);

		const simd128_t tx    = simd_ld<simd128_t>(translate + 0);
		const simd128_t ty    = simd_ld<simd128_t>(translate + 1);
		const simd128_t tz    = simd_ld<simd128_t>(translate + 2);

		const simd128_t sx    = simd_ld<simd128_t>(scale + 0);
		const simd128_t sy    = simd_ld<simd128_t>(scale + 1);
		const simd128_t sz    = simd_ld<simd128_t>(scale + 2);

		const simd128_t zero  = simd_splat(0.0f);
		const simd128_t one   = simd_splat(1.0f);
		const simd128_t two   = simd_splat(2.0f);

		const simd128_t xx    = simd_mul(rx,    rx);
		const simd128_t xx2   = simd_mul(two,   xx);
		const simd128_t yy    = simd_mul(ry,    ry);
		const simd128_t yy2   = simd_mul(two,   yy);
		const simd128_t zz    = simd_mul(rz,    rz);
		const simd128_t zz2   = simd_mul(two,   zz);
		const simd128_t yx    = simd_mul(ry,    rx);
		const simd128_t yx2   = simd_mul(two,   yx);
		const simd128_t yz    = simd_mul(ry,    rz);
		const simd128_t yz2   = simd_mul(two,   yz);
		const simd128_t yw    = simd_mul(ry,    rw);
		const simd128_t yw2   = simd_mul(two,   yw);
		const simd128_t wz    = simd_mul(rw,    rz);
		const simd128_t wz2   = simd_mul(two,   wz);
		const simd128_t wx    = simd_mul(rw,    rx);
		const simd128_t wx2   = simd_mul(two,   wx);
		const simd128_t xz    = simd_mul(rx,    rz);
		const simd128_t xz2   = simd_mul(two,   xz);
		const simd128_t t0x   = simd_sub(one,   yy2);
		const simd128_t r0x   = simd_sub(t0x,   zz2);
		const simd128_t r0y   = simd_add(yx2,   wz2);
		const simd128_t r0z   = simd_sub(xz2,   yw2);
		const simd128_t r1x   = simd_sub(yx2,   wz2);
		const simd128_t omxx2 = simd_sub(one,   xx2);
		const simd128_t r1y   = simd_sub(omxx2, zz2);
		const simd128_t r1z   = simd_add(yz2,   wx2);
		const simd128_t r2x   = simd_add(xz2,   yw2);
		const simd128_t r2y   = simd_sub(yz2,   wx2);
		const simd128_t r2z   = simd_sub(omxx2, yy2);

		simd128_t tmp[4];
		tmp[0] = simd_mul(r0x, sx);
		tmp[1] = simd_mul(r0y, sx);
		tmp[2] = simd_mul(r0z, sx);
		tmp[3] = zero;
		transpose(dst + 0, sizeof(Matrix4), tmp);

		tmp[0] = simd_mul(r1x, sy);
		tmp[1] = simd_mul(r1y, sy);
		tmp[2] = simd_mul(r1z, sy);
		tmp[3] = zero;
		transpose(dst + 1, sizeof(Matrix4), tmp);

		tmp[0] = simd_mul(r2x, sz);
		tmp[1] = simd_mul(r2y, sz);
		tmp[2] = simd_mul(r2z, sz);
		tmp[3] = zero;
		transpose(dst + 2, sizeof(Matrix4), tmp);

		tmp[0] = tx;
		tmp[1] = ty;
		tmp[2] = tz;
		tmp[3] = one;
		transpose(dst + 3, sizeof(Matrix4), tmp);
	}

	void srtToMatrix4(void* _dst, const void* _src, uint32_t _num)
	{
		      uint8_t* dst = reinterpret_cast<      uint8_t*>(_dst);
		const uint8_t* src = reinterpret_cast<const uint8_t*>(_src);

		if (!bx::isAligned(src, 16) )
		{
			for (uint32_t ii = 0, num = _num / 4; ii < num; ++ii)
			{
				srtToMatrix4_x4_Ref(dst, src);
				src += 4*sizeof(Srt);
				dst += 4*sizeof(Matrix4);
			}
		}
		else
		{
			for (uint32_t ii = 0, num = _num / 4; ii < num; ++ii)
			{
				srtToMatrix4_x4_Simd(dst, src);
				src += 4*sizeof(Srt);
				dst += 4*sizeof(Matrix4);
			}
		}

		for (uint32_t ii = 0, num = _num & 3; ii < num; ++ii)
		{
			srtToMatrix4_x1(dst, src);
			src += sizeof(Srt);
			dst += sizeof(Matrix4);
		}
	}

	void EncoderImpl::submit(ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint32_t _depth, uint8_t _flags)
	{
		if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM)
		&& (_flags & BGFX_DISCARD_STATE))
		{
			m_uniformSet.clear();
		}

		if (BX_ENABLED(BGFX_CONFIG_DEBUG_OCCLUSION)
		&&  isValid(_occlusionQuery) )
		{
			BX_ASSERT(m_occlusionQuerySet.end() == m_occlusionQuerySet.find(_occlusionQuery.idx)
				, "OcclusionQuery %d was already used for this frame."
				, _occlusionQuery.idx
				);
			m_occlusionQuerySet.insert(_occlusionQuery.idx);
		}

		if (m_discard)
		{
			discard(_flags);
			return;
		}

		if (0 == m_draw.m_numVertices
		&&  0 == m_draw.m_numIndices)
		{
			discard(_flags);
			++m_numDropped;
			return;
		}

		const uint32_t renderItemIdx = bx::atomicFetchAndAddsat<uint32_t>(&m_frame->m_numRenderItems, 1, BGFX_CONFIG_MAX_DRAW_CALLS);
		if (BGFX_CONFIG_MAX_DRAW_CALLS <= renderItemIdx)
		{
			discard(_flags);
			++m_numDropped;
			return;
		}

		++m_numSubmitted;

		UniformBuffer* uniformBuffer = m_frame->m_uniformBuffer[m_uniformIdx];
		m_uniformEnd = uniformBuffer->getPos();

		m_key.m_program = isValid(_program)
			? _program
			: ProgramHandle{0}
			;

		m_key.m_view = _id;

		SortKey::Enum type;
		switch (s_ctx->m_view[_id].m_mode)
		{
		case ViewMode::Sequential:      m_key.m_seq   = s_ctx->getSeqIncr(_id); type = SortKey::SortSequence; break;
		case ViewMode::DepthAscending:  m_key.m_depth =            _depth;      type = SortKey::SortDepth;    break;
		case ViewMode::DepthDescending: m_key.m_depth = UINT32_MAX-_depth;      type = SortKey::SortDepth;    break;
		default:                        m_key.m_depth =            _depth;      type = SortKey::SortProgram;  break;
		}

		uint64_t key = m_key.encodeDraw(type);

		m_frame->m_sortKeys[renderItemIdx]   = key;
		m_frame->m_sortValues[renderItemIdx] = RenderItemCount(renderItemIdx);

		m_draw.m_uniformIdx   = m_uniformIdx;
		m_draw.m_uniformBegin = m_uniformBegin;
		m_draw.m_uniformEnd   = m_uniformEnd;

		if (UINT8_MAX != m_draw.m_streamMask)
		{
			uint32_t numVertices = UINT32_MAX;
			for (uint32_t idx = 0, streamMask = m_draw.m_streamMask
				; 0 != streamMask
				; streamMask >>= 1, idx += 1
				)
			{
				const uint32_t ntz = bx::uint32_cnttz(streamMask);
				streamMask >>= ntz;
				idx         += ntz;
				numVertices = bx::min(numVertices, m_numVertices[idx]);
			}

			m_draw.m_numVertices = numVertices;
		}
		else
		{
			m_draw.m_numVertices = m_numVertices[0];
		}

		if (isValid(_occlusionQuery) )
		{
			m_draw.m_stateFlags |= BGFX_STATE_INTERNAL_OCCLUSION_QUERY;
			m_draw.m_occlusionQuery = _occlusionQuery;
		}

		m_frame->m_renderItem[renderItemIdx].draw = m_draw;
		m_frame->m_renderItemBind[renderItemIdx]  = m_bind;

		m_draw.clear(_flags);
		m_bind.clear(_flags);
		if (_flags & BGFX_DISCARD_STATE)
		{
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
			discard(_flags);
			return;
		}

		const uint32_t renderItemIdx = bx::atomicFetchAndAddsat<uint32_t>(&m_frame->m_numRenderItems, 1, BGFX_CONFIG_MAX_DRAW_CALLS);
		if (BGFX_CONFIG_MAX_DRAW_CALLS-1 <= renderItemIdx)
		{
			discard(_flags);
			++m_numDropped;
			return;
		}

		++m_numSubmitted;

		UniformBuffer* uniformBuffer = m_frame->m_uniformBuffer[m_uniformIdx];
		m_uniformEnd = uniformBuffer->getPos();

		m_compute.m_startMatrix = m_draw.m_startMatrix;
		m_compute.m_numMatrices = m_draw.m_numMatrices;
		m_compute.m_numX   = bx::max(_numX, 1u);
		m_compute.m_numY   = bx::max(_numY, 1u);
		m_compute.m_numZ   = bx::max(_numZ, 1u);

		m_key.m_program = _handle;
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

		m_compute.clear(_flags);
		m_bind.clear(_flags);
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

			View& view = m_view[ii];
			Rect rect(0, 0, uint16_t(m_resolution.width), uint16_t(m_resolution.height) );

			if (isValid(view.m_fbh) )
			{
				const FrameBufferRef& fbr = s_ctx->m_frameBufferRef[view.m_fbh.idx];
				const BackbufferRatio::Enum bbRatio = fbr.m_window
					? BackbufferRatio::Count
					: BackbufferRatio::Enum(s_ctx->m_textureRef[fbr.un.m_th[0].idx].m_bbRatio)
					;

				if (BackbufferRatio::Count != bbRatio)
				{
					getTextureSizeFromRatio(bbRatio, rect.m_width, rect.m_height);
				}
				else
				{
					rect.m_width  = fbr.m_width;
					rect.m_height = fbr.m_height;
				}
			}

			view.m_rect.intersect(rect);

			if (!view.m_scissor.isZero() )
			{
				view.m_scissor.intersect(rect);
			}
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
			if (s_renderFrameCalled)
			{
				BGFX_CHECK_RENDER_THREAD();
			}

			if (NULL == s_ctx)
			{
				s_renderFrameCalled = true;
				s_threadIndex = ~BGFX_API_THREAD_MAGIC;
				return RenderFrame::NoContext;
			}

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

		BX_ASSERT(false, "This call only makes sense if used with multi-threaded renderer.");
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
		CAPS_FLAGS(BGFX_CAPS_HDR10),
		CAPS_FLAGS(BGFX_CAPS_HIDPI),
		CAPS_FLAGS(BGFX_CAPS_IMAGE_RW),
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
		CAPS_FLAGS(BGFX_CAPS_VERTEX_ID),
		CAPS_FLAGS(BGFX_CAPS_VIEWPORT_LAYER_ARRAY),
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

		BX_TRACE("GPU device, Device ID: %04x, Vendor ID: %04x", g_caps.deviceId, g_caps.vendorId);
		BX_TRACE("");

		RendererType::Enum renderers[RendererType::Count];
		uint8_t num = getSupportedRenderers(BX_COUNTOF(renderers), renderers);

		BX_TRACE("Supported renderer backends (%d):", num);
		for (uint32_t ii = 0; ii < num; ++ii)
		{
			BX_TRACE("\t - %s", getRendererName(renderers[ii]) );
		}

		BX_TRACE("");
		BX_TRACE("Sort key masks:");
		BX_TRACE("\t   View     %016" PRIx64, kSortKeyViewMask);
		BX_TRACE("\t   Draw bit %016" PRIx64, kSortKeyDrawBit);

		BX_TRACE("");
		BX_TRACE("\tD  Type     %016" PRIx64, kSortKeyDrawTypeMask);

		BX_TRACE("");
		BX_TRACE("\tD0 Blend    %016" PRIx64, kSortKeyDraw0BlendMask);
		BX_TRACE("\tD0 Program  %016" PRIx64, kSortKeyDraw0ProgramMask);
		BX_TRACE("\tD0 Depth    %016" PRIx64, kSortKeyDraw0DepthMask);

		BX_TRACE("");
		BX_TRACE("\tD1 Depth    %016" PRIx64, kSortKeyDraw1DepthMask);
		BX_TRACE("\tD1 Blend    %016" PRIx64, kSortKeyDraw1BlendMask);
		BX_TRACE("\tD1 Program  %016" PRIx64, kSortKeyDraw1ProgramMask);

		BX_TRACE("");
		BX_TRACE("\tD2 Seq      %016" PRIx64, kSortKeyDraw2SeqMask);
		BX_TRACE("\tD2 Blend    %016" PRIx64, kSortKeyDraw2BlendMask);
		BX_TRACE("\tD2 Program  %016" PRIx64, kSortKeyDraw2ProgramMask);

		BX_TRACE("");
		BX_TRACE("\t C Seq      %016" PRIx64, kSortKeyComputeSeqMask);
		BX_TRACE("\t C Program  %016" PRIx64, kSortKeyComputeProgramMask);

		BX_TRACE("");
		BX_TRACE("Capabilities (renderer %s, vendor 0x%04x, device 0x%04x):"
				, s_ctx->m_renderCtx->getRendererName()
				, g_caps.vendorId
				, g_caps.deviceId
				);
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_capsFlags); ++ii)
		{
			BX_TRACE("\t[%c] %s"
				, 0 != (g_caps.supported & s_capsFlags[ii].m_flag) ? 'x' : ' '
				, s_capsFlags[ii].m_str
				);
		}
		BX_UNUSED(s_capsFlags);

		BX_TRACE("");
		BX_TRACE("Limits:");
#define LIMITS(_x) BX_TRACE("\t%-24s%10d", #_x, g_caps.limits._x)
		LIMITS(maxDrawCalls);
		LIMITS(maxBlits);
		LIMITS(maxTextureSize);
		LIMITS(maxTextureLayers);
		LIMITS(maxViews);
		LIMITS(maxFrameBuffers);
		LIMITS(maxFBAttachments);
		LIMITS(maxPrograms);
		LIMITS(maxShaders);
		LIMITS(maxTextures);
		LIMITS(maxTextureSamplers);
		LIMITS(maxComputeBindings);
		LIMITS(maxVertexLayouts);
		LIMITS(maxVertexStreams);
		LIMITS(maxIndexBuffers);
		LIMITS(maxVertexBuffers);
		LIMITS(maxDynamicIndexBuffers);
		LIMITS(maxDynamicVertexBuffers);
		LIMITS(maxUniforms);
		LIMITS(maxOcclusionQueries);
		LIMITS(maxEncoders);
		LIMITS(minResourceCbSize);
		LIMITS(transientVbSize);
		LIMITS(transientIbSize);
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
		BX_TRACE("\t |||||||+--------- image: i = read-write / r = read / w = write");
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
				uint32_t flags = g_caps.formats[ii];
				BX_TRACE("\t[%c%c%c%c%c%c%c%c%c%c%c%c] %s"
					, flags&BGFX_CAPS_FORMAT_TEXTURE_2D               ? 'x' : flags&BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED ? '*' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB          ? 'l' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_3D               ? 'x' : flags&BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED ? '*' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB          ? 'l' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_CUBE             ? 'x' : flags&BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED ? '*' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB        ? 'l' : ' '
					, flags&BGFX_CAPS_FORMAT_TEXTURE_VERTEX           ? 'v' : ' '
					, (flags&BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ) &&
					  (flags&BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE)    ? 'i' : flags&BGFX_CAPS_FORMAT_TEXTURE_IMAGE_READ ? 'r' : flags&BGFX_CAPS_FORMAT_TEXTURE_IMAGE_WRITE ? 'w' : ' '
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

	void dump(const Resolution& _resolution)
	{
		const uint32_t reset = _resolution.reset;
		const uint32_t msaa = (reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;
		BX_UNUSED(reset, msaa);

		BX_TRACE("Reset back-buffer swap chain:");
		BX_TRACE("\t%dx%d, format: %s, numBackBuffers: %d, maxFrameLatency: %d"
			, _resolution.width
			, _resolution.height
			, TextureFormat::Count == _resolution.format
				? "*default*"
				: bimg::getName(bimg::TextureFormat::Enum(_resolution.format) )
			, _resolution.numBackBuffers
			, _resolution.maxFrameLatency
			);
		BX_TRACE("\t[%c] MSAAx%d", 0 != msaa ? 'x' : ' ', 1<<msaa);
		BX_TRACE("\t[%c] Fullscreen",         0 != (reset & BGFX_RESET_FULLSCREEN)         ? 'x' : ' ');
		BX_TRACE("\t[%c] V-sync",             0 != (reset & BGFX_RESET_VSYNC)              ? 'x' : ' ');
		BX_TRACE("\t[%c] Max Anisotropy",     0 != (reset & BGFX_RESET_MAXANISOTROPY)      ? 'x' : ' ');
		BX_TRACE("\t[%c] Capture",            0 != (reset & BGFX_RESET_CAPTURE)            ? 'x' : ' ');
		BX_TRACE("\t[%c] Flush After Render", 0 != (reset & BGFX_RESET_FLUSH_AFTER_RENDER) ? 'x' : ' ');
		BX_TRACE("\t[%c] Flip After Render",  0 != (reset & BGFX_RESET_FLIP_AFTER_RENDER)  ? 'x' : ' ');
		BX_TRACE("\t[%c] sRGB Back Buffer",   0 != (reset & BGFX_RESET_SRGB_BACKBUFFER)    ? 'x' : ' ');
		BX_TRACE("\t[%c] HDR10",              0 != (reset & BGFX_RESET_HDR10)              ? 'x' : ' ');
		BX_TRACE("\t[%c] Hi-DPI",             0 != (reset & BGFX_RESET_HIDPI)              ? 'x' : ' ');
		BX_TRACE("\t[%c] Depth Clamp",        0 != (reset & BGFX_RESET_DEPTH_CLAMP)        ? 'x' : ' ');
		BX_TRACE("\t[%c] Suspend",            0 != (reset & BGFX_RESET_SUSPEND)            ? 'x' : ' ');
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

	const char* getName(ShaderHandle _handle)
	{
		return s_ctx->m_shaderRef[_handle.idx].m_name.getPtr();
	}

	static const char* s_topologyName[] =
	{
		"Triangles",
		"TriStrip",
		"Lines",
		"LineStrip",
		"Points",
	};
	BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_topologyName) );

	const char* getName(Topology::Enum _topology)
	{
		return s_topologyName[bx::min(_topology, Topology::PointList)];
	}

	const char* getShaderTypeName(uint32_t _magic)
	{
		if (isShaderType(_magic, 'C') )
		{
			return "Compute";
		}
		else if (isShaderType(_magic, 'F') )
		{
			return "Fragment";
		}
		else if (isShaderType(_magic, 'V') )
		{
			return "Vertex";
		}

		BX_ASSERT(false, "Invalid shader type!");

		return NULL;
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
		TextureFormat::ATC,
		TextureFormat::ATCE,
		TextureFormat::ATCI,
		TextureFormat::ASTC4x4,
		TextureFormat::ASTC5x5,
		TextureFormat::ASTC6x6,
		TextureFormat::ASTC8x5,
		TextureFormat::ASTC8x6,
		TextureFormat::ASTC10x5,
		TextureFormat::BGRA8, // GL doesn't support BGRA8 without extensions.
		TextureFormat::RGBA8, // D3D9 doesn't support RGBA8
	};

	bool Context::init(const Init& _init)
	{
		BX_ASSERT(!m_rendererInitialized, "Already initialized?");

		m_init = _init;
		m_init.resolution.reset &= ~BGFX_RESET_INTERNAL_FORCE;
		m_init.resolution.numBackBuffers  = bx::clamp<uint8_t>(_init.resolution.numBackBuffers, 2, BGFX_CONFIG_MAX_BACK_BUFFERS);
		m_init.resolution.maxFrameLatency = bx::min<uint8_t>(_init.resolution.maxFrameLatency, BGFX_CONFIG_MAX_FRAME_LATENCY);
		dump(m_init.resolution);

		if (g_platformData.ndt          == NULL
		&&  g_platformData.nwh          == NULL
		&&  g_platformData.context      == NULL
		&&  g_platformData.backBuffer   == NULL
		&&  g_platformData.backBufferDS == NULL)
		{
			bx::memCopy(&g_platformData, &m_init.platformData, sizeof(PlatformData) );
		}
		else
		{
			bx::memCopy(&m_init.platformData, &g_platformData, sizeof(PlatformData) );
		}

		if (true
		&&  !BX_ENABLED(BX_PLATFORM_EMSCRIPTEN || BX_PLATFORM_PS4)
		&&  RendererType::Noop != m_init.type
		&&  NULL == m_init.platformData.ndt
		&&  NULL == m_init.platformData.nwh
		&&  NULL == m_init.platformData.context
		&&  NULL == m_init.platformData.backBuffer
		&&  NULL == m_init.platformData.backBufferDS
		   )
		{
			BX_TRACE("bgfx platform data like window handle or backbuffer is not set, creating headless device.");
		}

		m_exit    = false;
		m_flipped = true;
		m_frames  = 0;
		m_debug   = BGFX_DEBUG_NONE;
		m_frameTimeLast = bx::getHPCounter();

		m_submit->create(_init.limits.minResourceCbSize);

#if BGFX_CONFIG_MULTITHREADED
		m_render->create(_init.limits.minResourceCbSize);

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

		m_vertexLayoutRef.init();

		CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::RendererInit);
		cmdbuf.write(_init);

		frameNoRenderWait();

		m_encoderHandle = bx::createHandleAlloc(g_allocator, _init.limits.maxEncoders);
		m_encoder       = (EncoderImpl*)BX_ALIGNED_ALLOC(g_allocator, sizeof(EncoderImpl)*_init.limits.maxEncoders, BX_ALIGNOF(EncoderImpl) );
		m_encoderStats  = (EncoderStats*)BX_ALLOC(g_allocator, sizeof(EncoderStats)*_init.limits.maxEncoders);
		for (uint32_t ii = 0, num = _init.limits.maxEncoders; ii < num; ++ii)
		{
			BX_PLACEMENT_NEW(&m_encoder[ii], EncoderImpl);
		}

		uint16_t idx = m_encoderHandle->alloc();
		BX_ASSERT(0 == idx, "Internal encoder handle is not 0 (idx %d).", idx); BX_UNUSED(idx);
		m_encoder[0].begin(m_submit, 0);
		m_encoder0 = BX_ENABLED(BGFX_CONFIG_ENCODER_API_ONLY)
			? NULL
			: reinterpret_cast<Encoder*>(&m_encoder[0])
			;

		// Make sure renderer init is called from render thread.
		// g_caps is initialized and available after this point.
		frame();

		if (!m_rendererInitialized)
		{
			getCommandBuffer(CommandBuffer::RendererShutdownEnd);
			frame();
			frame();
			m_vertexLayoutRef.shutdown(m_layoutHandle);
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

		g_caps.supported &= _init.capabilities;
		g_caps.supported |= 0
			| (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) && !m_singleThreaded ? BGFX_CAPS_RENDERER_MULTITHREADED : 0)
			| (isGraphicsDebuggerPresent() ? BGFX_CAPS_GRAPHICS_DEBUGGER : 0)
			;

		dumpCaps();

		m_textVideoMemBlitter.init();
		m_clearQuad.init();

		m_submit->m_transientVb = createTransientVertexBuffer(_init.limits.transientVbSize);
		m_submit->m_transientIb = createTransientIndexBuffer(_init.limits.transientIbSize);
		frame();

		if (BX_ENABLED(BGFX_CONFIG_MULTITHREADED) )
		{
			m_submit->m_transientVb = createTransientVertexBuffer(_init.limits.transientVbSize);
			m_submit->m_transientIb = createTransientIndexBuffer(_init.limits.transientIbSize);
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

		frame(); // If any VertexLayouts needs to be destroyed.

		getCommandBuffer(CommandBuffer::RendererShutdownEnd);
		frame();

		m_encoder[0].end(true);
		m_encoderHandle->free(0);
		bx::destroyHandleAlloc(g_allocator, m_encoderHandle);
		m_encoderHandle = NULL;

		for (uint32_t ii = 0, num = g_caps.limits.maxEncoders; ii < num; ++ii)
		{
			m_encoder[ii].~EncoderImpl();
		}

		BX_ALIGNED_FREE(g_allocator, m_encoder, BX_ALIGNOF(EncoderImpl) );
		BX_FREE(g_allocator, m_encoderStats);

		m_dynVertexBufferAllocator.compact();
		m_dynIndexBufferAllocator.compact();

		BX_ASSERT(
			  m_layoutHandle.getNumHandles() == m_vertexLayoutRef.m_vertexLayoutMap.getNumElements()
			, "VertexLayoutRef mismatch, num handles %d, handles in hash map %d."
			, m_layoutHandle.getNumHandles()
			, m_vertexLayoutRef.m_vertexLayoutMap.getNumElements()
			);

		m_vertexLayoutRef.shutdown(m_layoutHandle);

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
#define CHECK_HANDLE_LEAK(_name, _handleAlloc)                                        \
	BX_MACRO_BLOCK_BEGIN                                                              \
		if (0 != _handleAlloc.getNumHandles() )                                       \
		{                                                                             \
			BX_TRACE("LEAK: %s %d (max: %d)"                                          \
				, _name                                                               \
				, _handleAlloc.getNumHandles()                                        \
				, _handleAlloc.getMaxHandles()                                        \
				);                                                                    \
			for (uint16_t ii = 0, num = _handleAlloc.getNumHandles(); ii < num; ++ii) \
			{                                                                         \
				BX_TRACE("\t%3d: %4d", ii, _handleAlloc.getHandleAt(ii) );            \
			}                                                                         \
		}                                                                             \
	BX_MACRO_BLOCK_END

#define CHECK_HANDLE_LEAK_NAME(_name, _handleAlloc, _type, _ref)                      \
	BX_MACRO_BLOCK_BEGIN                                                              \
		if (0 != _handleAlloc.getNumHandles() )                                       \
		{                                                                             \
			BX_TRACE("LEAK: %s %d (max: %d)"                                          \
				, _name                                                               \
				, _handleAlloc.getNumHandles()                                        \
				, _handleAlloc.getMaxHandles()                                        \
				);                                                                    \
			for (uint16_t ii = 0, num = _handleAlloc.getNumHandles(); ii < num; ++ii) \
			{                                                                         \
				uint16_t idx = _handleAlloc.getHandleAt(ii);                          \
				const _type& ref = _ref[idx]; BX_UNUSED(ref);                         \
				BX_TRACE("\t%3d: %4d %s"                                              \
					, ii                                                              \
					, idx                                                             \
					, ref.m_name.getPtr()                                             \
					);                                                                \
			}                                                                         \
		}                                                                             \
	BX_MACRO_BLOCK_END

#define CHECK_HANDLE_LEAK_RC_NAME(_name, _handleAlloc, _type, _ref)                   \
	BX_MACRO_BLOCK_BEGIN                                                              \
		if (0 != _handleAlloc.getNumHandles() )                                       \
		{                                                                             \
			BX_TRACE("LEAK: %s %d (max: %d)"                                          \
				, _name                                                               \
				, _handleAlloc.getNumHandles()                                        \
				, _handleAlloc.getMaxHandles()                                        \
				);                                                                    \
			for (uint16_t ii = 0, num = _handleAlloc.getNumHandles(); ii < num; ++ii) \
			{                                                                         \
				uint16_t idx = _handleAlloc.getHandleAt(ii);                          \
				const _type& ref = _ref[idx]; BX_UNUSED(ref);                         \
				BX_TRACE("\t%3d: %4d %s (count %d)"                                   \
					, ii                                                              \
					, idx                                                             \
					, ref.m_name.getPtr()                                             \
					, ref.m_refCount                                                  \
					);                                                                \
			}                                                                         \
		}                                                                             \
	BX_MACRO_BLOCK_END

			CHECK_HANDLE_LEAK        ("DynamicIndexBufferHandle",  m_dynamicIndexBufferHandle                                  );
			CHECK_HANDLE_LEAK        ("DynamicVertexBufferHandle", m_dynamicVertexBufferHandle                                 );
			CHECK_HANDLE_LEAK_NAME   ("IndexBufferHandle",         m_indexBufferHandle,        IndexBuffer,    m_indexBuffers  );
			CHECK_HANDLE_LEAK        ("VertexLayoutHandle",        m_layoutHandle                                              );
			CHECK_HANDLE_LEAK_NAME   ("VertexBufferHandle",        m_vertexBufferHandle,       VertexBuffer,   m_vertexBuffers );
			CHECK_HANDLE_LEAK_RC_NAME("ShaderHandle",              m_shaderHandle,             ShaderRef,      m_shaderRef     );
			CHECK_HANDLE_LEAK        ("ProgramHandle",             m_programHandle                                             );
			CHECK_HANDLE_LEAK_RC_NAME("TextureHandle",             m_textureHandle,            TextureRef,     m_textureRef    );
			CHECK_HANDLE_LEAK_NAME   ("FrameBufferHandle",         m_frameBufferHandle,        FrameBufferRef, m_frameBufferRef);
			CHECK_HANDLE_LEAK_RC_NAME("UniformHandle",             m_uniformHandle,            UniformRef,     m_uniformRef    );
			CHECK_HANDLE_LEAK        ("OcclusionQueryHandle",      m_occlusionQueryHandle                                      );
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

		for (uint16_t ii = 0, num = _frame->m_freeVertexLayout.getNumQueued(); ii < num; ++ii)
		{
			m_layoutHandle.free(_frame->m_freeVertexLayout.get(ii).idx);
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

	Encoder* Context::begin(bool _forThread)
	{
		EncoderImpl* encoder = &m_encoder[0];

#if BGFX_CONFIG_MULTITHREADED
		if (_forThread || BGFX_API_THREAD_MAGIC != s_threadIndex)
		{
			bx::MutexScope scopeLock(m_encoderApiLock);

			uint16_t idx = m_encoderHandle->alloc();
			if (kInvalidHandle == idx)
			{
				return NULL;
			}

			encoder = &m_encoder[idx];
			encoder->begin(m_submit, uint8_t(idx) );
		}
#else
		BX_UNUSED(_forThread);
#endif // BGFX_CONFIG_MULTITHREADED

		return reinterpret_cast<Encoder*>(encoder);
	}

	void Context::end(Encoder* _encoder)
	{
#if BGFX_CONFIG_MULTITHREADED
		EncoderImpl* encoder = reinterpret_cast<EncoderImpl*>(_encoder);
		if (encoder != &m_encoder[0])
		{
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
		m_submit->m_resolution = m_init.resolution;
		m_init.resolution.reset &= ~BGFX_RESET_INTERNAL_FORCE;
		m_submit->m_debug = m_debug;
		m_submit->m_perfStats.numViews = 0;

		bx::memCopy(m_submit->m_viewRemap, m_viewRemap, sizeof(m_viewRemap) );
		bx::memCopy(m_submit->m_view, m_view, sizeof(m_view) );

		if (m_colorPaletteDirty > 0)
		{
			--m_colorPaletteDirty;
			bx::memCopy(m_submit->m_colorPalette, m_clearColor, sizeof(m_clearColor) );
		}

		freeAllHandles(m_submit);
		m_submit->resetFreeHandles();

		m_submit->finish();

		bx::swap(m_render, m_submit);

		bx::memCopy(m_render->m_occlusion, m_submit->m_occlusion, sizeof(m_submit->m_occlusion) );

		if (!BX_ENABLED(BGFX_CONFIG_MULTITHREADED)
		||  m_singleThreaded)
		{
			renderFrame();
		}

		m_frames++;
		m_submit->start();

		bx::memSet(m_seq, 0, sizeof(m_seq) );

		m_submit->m_textVideoMem->resize(
			  m_render->m_textVideoMem->m_small
			, m_init.resolution.width
			, m_init.resolution.height
			);

		int64_t now = bx::getHPCounter();
		m_submit->m_perfStats.cpuTimeFrame = now - m_frameTimeLast;
		m_frameTimeLast = now;
	}

	///
	RendererContextI* rendererCreate(const Init& _init);

	///
	void rendererDestroy(RendererContextI* _renderCtx);

	void Context::flip()
	{
		if (m_rendererInitialized
		&& !m_flipped)
		{
			m_renderCtx->flip();
			m_flipped = true;

			if (m_renderCtx->isDeviceRemoved() )
			{
				// Something horribly went wrong, fallback to noop renderer.
				rendererDestroy(m_renderCtx);

				Init init;
				init.type = RendererType::Noop;
				m_renderCtx = rendererCreate(init);
				g_caps.rendererType = RendererType::Noop;
			}
		}
	}

#if BX_PLATFORM_OSX || BX_PLATFORM_IOS
	struct NSAutoreleasePoolScope
	{
		NSAutoreleasePoolScope()
		{
			id obj = class_createInstance(objc_getClass("NSAutoreleasePool"), 0);
			typedef id(*objc_msgSend_init)(void*, SEL);
			pool = ((objc_msgSend_init)objc_msgSend)(obj, sel_getUid("init") );
		}

		~NSAutoreleasePoolScope()
		{
			typedef void(*objc_msgSend_release)(void*, SEL);
			((objc_msgSend_release)objc_msgSend)(pool, sel_getUid("release") );
		}

		id pool;
	};
#endif // BX_PLATFORM_OSX

	RenderFrame::Enum Context::renderFrame(int32_t _msecs)
	{
		BGFX_PROFILER_SCOPE("bgfx::renderFrame", 0xff2040ff);

#if BX_PLATFORM_OSX || BX_PLATFORM_IOS
		NSAutoreleasePoolScope pool;
#endif // BX_PLATFORM_OSX

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
				{
					BGFX_PROFILER_SCOPE("bgfx/Render submit", 0xff2040ff);
					m_renderCtx->submit(m_render, m_clearQuad, m_textVideoMemBlitter);
					m_flipped = false;
				}

				{
					BGFX_PROFILER_SCOPE("bgfx/Screenshot", 0xff2040ff);
					for (uint8_t ii = 0, num = m_render->m_numScreenShots; ii < num; ++ii)
					{
						const ScreenShot& screenShot = m_render->m_screenShot[ii];
						m_renderCtx->requestScreenShot(screenShot.handle, screenShot.filePath.getCPtr() );
					}
				}
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
				_renderCtx->setMarker(data, uint16_t(size)-1);
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

				const Memory* mem;
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

#define BGFX_RENDERER_CONTEXT(_namespace)                           \
	namespace _namespace                                            \
	{                                                               \
		extern RendererContextI* rendererCreate(const Init& _init); \
		extern void rendererDestroy();                              \
	}

	BGFX_RENDERER_CONTEXT(noop);
	BGFX_RENDERER_CONTEXT(agc);
	BGFX_RENDERER_CONTEXT(d3d9);
	BGFX_RENDERER_CONTEXT(d3d11);
	BGFX_RENDERER_CONTEXT(d3d12);
	BGFX_RENDERER_CONTEXT(gnm);
	BGFX_RENDERER_CONTEXT(mtl);
	BGFX_RENDERER_CONTEXT(nvn);
	BGFX_RENDERER_CONTEXT(gl);
	BGFX_RENDERER_CONTEXT(vk);
	BGFX_RENDERER_CONTEXT(webgpu);

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
		{ noop::rendererCreate,   noop::rendererDestroy,   BGFX_RENDERER_NOOP_NAME,       true                              }, // Noop
		{ agc::rendererCreate,    agc::rendererDestroy,    BGFX_RENDERER_AGC_NAME,        !!BGFX_CONFIG_RENDERER_AGC        }, // GNM
		{ d3d9::rendererCreate,   d3d9::rendererDestroy,   BGFX_RENDERER_DIRECT3D9_NAME,  !!BGFX_CONFIG_RENDERER_DIRECT3D9  }, // Direct3D9
		{ d3d11::rendererCreate,  d3d11::rendererDestroy,  BGFX_RENDERER_DIRECT3D11_NAME, !!BGFX_CONFIG_RENDERER_DIRECT3D11 }, // Direct3D11
		{ d3d12::rendererCreate,  d3d12::rendererDestroy,  BGFX_RENDERER_DIRECT3D12_NAME, !!BGFX_CONFIG_RENDERER_DIRECT3D12 }, // Direct3D12
		{ gnm::rendererCreate,    gnm::rendererDestroy,    BGFX_RENDERER_GNM_NAME,        !!BGFX_CONFIG_RENDERER_GNM        }, // GNM
#if BX_PLATFORM_OSX || BX_PLATFORM_IOS
		{ mtl::rendererCreate,    mtl::rendererDestroy,    BGFX_RENDERER_METAL_NAME,      !!BGFX_CONFIG_RENDERER_METAL      }, // Metal
#else
		{ noop::rendererCreate,   noop::rendererDestroy,   BGFX_RENDERER_NOOP_NAME,       false                             }, // Noop
#endif // BX_PLATFORM_OSX || BX_PLATFORM_IOS
		{ nvn::rendererCreate,    nvn::rendererDestroy,    BGFX_RENDERER_NVN_NAME,        !!BGFX_CONFIG_RENDERER_NVN        }, // NVN
		{ gl::rendererCreate,     gl::rendererDestroy,     BGFX_RENDERER_OPENGL_NAME,     !!BGFX_CONFIG_RENDERER_OPENGLES   }, // OpenGLES
		{ gl::rendererCreate,     gl::rendererDestroy,     BGFX_RENDERER_OPENGL_NAME,     !!BGFX_CONFIG_RENDERER_OPENGL     }, // OpenGL
		{ vk::rendererCreate,     vk::rendererDestroy,     BGFX_RENDERER_VULKAN_NAME,     !!BGFX_CONFIG_RENDERER_VULKAN     }, // Vulkan
		{ webgpu::rendererCreate, webgpu::rendererDestroy, BGFX_RENDERER_WEBGPU_NAME,     !!BGFX_CONFIG_RENDERER_WEBGPU     }, // WebGPU
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_rendererCreator) == RendererType::Count);

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

	RendererContextI* rendererCreate(const Init& _init)
	{
		int32_t scores[RendererType::Count];
		uint32_t numScores = 0;

		for (uint32_t ii = 0; ii < RendererType::Count; ++ii)
		{
			RendererType::Enum renderer = RendererType::Enum(ii);
			if (s_rendererCreator[ii].supported)
			{
				int32_t score = 0;
				if (_init.type == renderer)
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
					score += RendererType::Vulkan   == renderer ? 30 : 0;
					score += RendererType::OpenGL   == renderer ? 20 : 0;
					score += RendererType::OpenGLES == renderer ? 10 : 0;
				}
				else if (BX_ENABLED(BX_PLATFORM_OSX) )
				{
					score += RendererType::Metal    == renderer ? 20 : 0;
					score += RendererType::OpenGL   == renderer ? 10 : 0;
				}
				else if (BX_ENABLED(BX_PLATFORM_IOS) )
				{
					score += RendererType::Metal    == renderer ? 20 : 0;
					score += RendererType::OpenGLES == renderer ? 10 : 0;
				}
				else if (BX_ENABLED(0
					 ||  BX_PLATFORM_ANDROID
					 ||  BX_PLATFORM_EMSCRIPTEN
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
					score += RendererType::Direct3D12 == renderer ? 20 : 0;
					score += RendererType::Direct3D11 == renderer ? 10 : 0;
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
					BX_ASSERT(CommandBuffer::RendererInit == command
						, "RendererInit must be the first command in command buffer before initialization. Unexpected command %d?"
						, command
						);
					BX_ASSERT(!m_rendererInitialized, "This shouldn't happen! Bad synchronization?");

					Init init;
					_cmdbuf.read(init);

					m_renderCtx = rendererCreate(init);

					m_rendererInitialized = NULL != m_renderCtx;

					if (!m_rendererInitialized)
					{
						_cmdbuf.read(command);
						BX_ASSERT(CommandBuffer::End == command, "Unexpected command %d?"
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
					BX_ASSERT(m_rendererInitialized, "This shouldn't happen! Bad synchronization?");
					m_rendererInitialized = false;
				}
				break;

			case CommandBuffer::RendererShutdownEnd:
				{
					BX_ASSERT(!m_rendererInitialized && !m_exit, "This shouldn't happen! Bad synchronization?");

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
					BGFX_PROFILER_SCOPE("CreateIndexBuffer", 0xff2040ff);

					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					const Memory* mem;
					_cmdbuf.read(mem);

					uint16_t flags;
					_cmdbuf.read(flags);

					m_renderCtx->createIndexBuffer(handle, mem, flags);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyIndexBuffer:
				{
					BGFX_PROFILER_SCOPE("DestroyIndexBuffer", 0xff2040ff);

					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyIndexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateVertexLayout:
				{
					BGFX_PROFILER_SCOPE("CreateVertexLayout", 0xff2040ff);

					VertexLayoutHandle handle;
					_cmdbuf.read(handle);

					VertexLayout layout;
					_cmdbuf.read(layout);

					m_renderCtx->createVertexLayout(handle, layout);
				}
				break;

			case CommandBuffer::DestroyVertexLayout:
				{
					BGFX_PROFILER_SCOPE("DestroyVertexLayout", 0xff2040ff);

					VertexLayoutHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyVertexLayout(handle);
				}
				break;

			case CommandBuffer::CreateVertexBuffer:
				{
					BGFX_PROFILER_SCOPE("CreateVertexBuffer", 0xff2040ff);

					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					const Memory* mem;
					_cmdbuf.read(mem);

					VertexLayoutHandle layoutHandle;
					_cmdbuf.read(layoutHandle);

					uint16_t flags;
					_cmdbuf.read(flags);

					m_renderCtx->createVertexBuffer(handle, mem, layoutHandle, flags);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyVertexBuffer:
				{
					BGFX_PROFILER_SCOPE("DestroyVertexBuffer", 0xff2040ff);

					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyVertexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateDynamicIndexBuffer:
				{
					BGFX_PROFILER_SCOPE("CreateDynamicIndexBuffer", 0xff2040ff);

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
					BGFX_PROFILER_SCOPE("UpdateDynamicIndexBuffer", 0xff2040ff);

					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					uint32_t offset;
					_cmdbuf.read(offset);

					uint32_t size;
					_cmdbuf.read(size);

					const Memory* mem;
					_cmdbuf.read(mem);

					m_renderCtx->updateDynamicIndexBuffer(handle, offset, size, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyDynamicIndexBuffer:
				{
					BGFX_PROFILER_SCOPE("DestroyDynamicIndexBuffer", 0xff2040ff);

					IndexBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyDynamicIndexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateDynamicVertexBuffer:
				{
					BGFX_PROFILER_SCOPE("CreateDynamicVertexBuffer", 0xff2040ff);

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
					BGFX_PROFILER_SCOPE("UpdateDynamicVertexBuffer", 0xff2040ff);

					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					uint32_t offset;
					_cmdbuf.read(offset);

					uint32_t size;
					_cmdbuf.read(size);

					const Memory* mem;
					_cmdbuf.read(mem);

					m_renderCtx->updateDynamicVertexBuffer(handle, offset, size, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyDynamicVertexBuffer:
				{
					BGFX_PROFILER_SCOPE("DestroyDynamicVertexBuffer", 0xff2040ff);

					VertexBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyDynamicVertexBuffer(handle);
				}
				break;

			case CommandBuffer::CreateShader:
				{
					BGFX_PROFILER_SCOPE("CreateShader", 0xff2040ff);

					ShaderHandle handle;
					_cmdbuf.read(handle);

					const Memory* mem;
					_cmdbuf.read(mem);

					m_renderCtx->createShader(handle, mem);

					release(mem);
				}
				break;

			case CommandBuffer::DestroyShader:
				{
					BGFX_PROFILER_SCOPE("DestroyShader", 0xff2040ff);

					ShaderHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyShader(handle);
				}
				break;

			case CommandBuffer::CreateProgram:
				{
					BGFX_PROFILER_SCOPE("CreateProgram", 0xff2040ff);

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
					BGFX_PROFILER_SCOPE("DestroyProgram", 0xff2040ff);

					ProgramHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyProgram(handle);
				}
				break;

			case CommandBuffer::CreateTexture:
				{
					BGFX_PROFILER_SCOPE("CreateTexture", 0xff2040ff);

					TextureHandle handle;
					_cmdbuf.read(handle);

					const Memory* mem;
					_cmdbuf.read(mem);

					uint64_t flags;
					_cmdbuf.read(flags);

					uint8_t skip;
					_cmdbuf.read(skip);

					void* ptr = m_renderCtx->createTexture(handle, mem, flags, skip);
					if (NULL != ptr)
					{
						setDirectAccessPtr(handle, ptr);
					}

					bx::MemoryReader reader(mem->data, mem->size);
					bx::Error err;

					uint32_t magic;
					bx::read(&reader, magic, &err);

					if (BGFX_CHUNK_MAGIC_TEX == magic)
					{
						TextureCreate tc;
						bx::read(&reader, tc, &err);

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
					BGFX_PROFILER_SCOPE("UpdateTexture", 0xff2040ff);

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
					BGFX_PROFILER_SCOPE("ReadTexture", 0xff2040ff);

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
					BGFX_PROFILER_SCOPE("ResizeTexture", 0xff2040ff);

					TextureHandle handle;
					_cmdbuf.read(handle);

					uint16_t width;
					_cmdbuf.read(width);

					uint16_t height;
					_cmdbuf.read(height);

					uint8_t numMips;
					_cmdbuf.read(numMips);

					uint16_t numLayers;
					_cmdbuf.read(numLayers);

					m_renderCtx->resizeTexture(handle, width, height, numMips, numLayers);
				}
				break;

			case CommandBuffer::DestroyTexture:
				{
					BGFX_PROFILER_SCOPE("DestroyTexture", 0xff2040ff);

					TextureHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyTexture(handle);
				}
				break;

			case CommandBuffer::CreateFrameBuffer:
				{
					BGFX_PROFILER_SCOPE("CreateFrameBuffer", 0xff2040ff);

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

						TextureFormat::Enum format;
						_cmdbuf.read(format);

						TextureFormat::Enum depthFormat;
						_cmdbuf.read(depthFormat);

						m_renderCtx->createFrameBuffer(handle, nwh, width, height, format, depthFormat);
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
					BGFX_PROFILER_SCOPE("DestroyFrameBuffer", 0xff2040ff);

					FrameBufferHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyFrameBuffer(handle);
				}
				break;

			case CommandBuffer::CreateUniform:
				{
					BGFX_PROFILER_SCOPE("CreateUniform", 0xff2040ff);

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
					BGFX_PROFILER_SCOPE("DestroyUniform", 0xff2040ff);

					UniformHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->destroyUniform(handle);
				}
				break;

			case CommandBuffer::UpdateViewName:
				{
					BGFX_PROFILER_SCOPE("UpdateViewName", 0xff2040ff);

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
					BGFX_PROFILER_SCOPE("InvalidateOcclusionQuery", 0xff2040ff);

					OcclusionQueryHandle handle;
					_cmdbuf.read(handle);

					m_renderCtx->invalidateOcclusionQuery(handle);
				}
				break;

			case CommandBuffer::SetName:
				{
					BGFX_PROFILER_SCOPE("SetName", 0xff2040ff);

					Handle handle;
					_cmdbuf.read(handle);

					uint16_t len;
					_cmdbuf.read(len);

					const char* name = (const char*)_cmdbuf.skip(len);

					m_renderCtx->setName(handle, name, len-1);
				}
				break;

			default:
				BX_ASSERT(false, "Invalid command: %d", command);
				break;
			}
		} while (!end);

		flushTextureUpdateBatch(_cmdbuf);
	}

	uint32_t weldVertices(void* _output, const VertexLayout& _layout, const void* _data, uint32_t _num, bool _index32, float _epsilon)
	{
		return weldVertices(_output, _layout, _data, _num, _index32, _epsilon, g_allocator);
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
		BX_ASSERT(_type < RendererType::Count, "Invalid renderer type %d.", _type);
		return s_rendererCreator[_type].name;
	}

	PlatformData::PlatformData()
		: ndt(NULL)
		, nwh(NULL)
		, context(NULL)
		, backBuffer(NULL)
		, backBufferDS(NULL)
	{
	}

	Resolution::Resolution()
		: format(TextureFormat::RGBA8)
		, width(1280)
		, height(720)
		, reset(BGFX_RESET_NONE)
		, numBackBuffers(2)
		, maxFrameLatency(0)
	{
	}

	Init::Limits::Limits()
		: maxEncoders(BGFX_CONFIG_DEFAULT_MAX_ENCODERS)
		, minResourceCbSize(BGFX_CONFIG_MIN_RESOURCE_COMMAND_BUFFER_SIZE)
		, transientVbSize(BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE)
		, transientIbSize(BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE)
	{
	}

	Init::Init()
		: type(RendererType::Count)
		, vendorId(BGFX_PCI_ID_NONE)
		, deviceId(0)
		, capabilities(UINT64_MAX)
		, debug(BX_ENABLED(BGFX_CONFIG_DEBUG) )
		, profile(BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION) )
		, callback(NULL)
		, allocator(NULL)
	{
	}

	void Attachment::init(TextureHandle _handle, Access::Enum _access, uint16_t _layer, uint16_t _numLayers, uint16_t _mip, uint8_t _resolve)
	{
		access    = _access;
		handle    = _handle;
		mip       = _mip;
		layer     = _layer;
		numLayers = _numLayers;
		resolve   = _resolve;
	}

	bool init(const Init& _userInit)
	{
		if (NULL != s_ctx)
		{
			BX_TRACE("bgfx is already initialized.");
			return false;
		}

		Init init = _userInit;

		init.limits.maxEncoders       = bx::clamp<uint16_t>(init.limits.maxEncoders, 1, (0 != BGFX_CONFIG_MULTITHREADED) ? 128 : 1);
		init.limits.minResourceCbSize = bx::min<uint32_t>(init.limits.minResourceCbSize, BGFX_CONFIG_MIN_RESOURCE_COMMAND_BUFFER_SIZE);

		struct ErrorState
		{
			enum Enum
			{
				Default,
				ContextAllocated,
			};
		};

		ErrorState::Enum errorState = ErrorState::Default;

		if (NULL != init.allocator)
		{
			g_allocator = init.allocator;
		}
		else
		{
			bx::DefaultAllocator allocator;
			g_allocator =
				s_allocatorStub = BX_NEW(&allocator, AllocatorStub);
		}

		if (NULL != init.callback)
		{
			g_callback = init.callback;
		}
		else
		{
			g_callback =
				s_callbackStub = BX_NEW(g_allocator, CallbackStub);
		}

		bx::memSet(&g_caps, 0, sizeof(g_caps) );
		g_caps.limits.maxDrawCalls            = BGFX_CONFIG_MAX_DRAW_CALLS;
		g_caps.limits.maxBlits                = BGFX_CONFIG_MAX_BLIT_ITEMS;
		g_caps.limits.maxTextureSize          = 0;
		g_caps.limits.maxTextureLayers        = 1;
		g_caps.limits.maxViews                = BGFX_CONFIG_MAX_VIEWS;
		g_caps.limits.maxFrameBuffers         = BGFX_CONFIG_MAX_FRAME_BUFFERS;
		g_caps.limits.maxPrograms             = BGFX_CONFIG_MAX_PROGRAMS;
		g_caps.limits.maxShaders              = BGFX_CONFIG_MAX_SHADERS;
		g_caps.limits.maxTextures             = BGFX_CONFIG_MAX_TEXTURES;
		g_caps.limits.maxTextureSamplers      = BGFX_CONFIG_MAX_TEXTURE_SAMPLERS;
		g_caps.limits.maxComputeBindings      = 0;
		g_caps.limits.maxVertexLayouts        = BGFX_CONFIG_MAX_VERTEX_LAYOUTS;
		g_caps.limits.maxVertexStreams        = 1;
		g_caps.limits.maxIndexBuffers         = BGFX_CONFIG_MAX_INDEX_BUFFERS;
		g_caps.limits.maxVertexBuffers        = BGFX_CONFIG_MAX_VERTEX_BUFFERS;
		g_caps.limits.maxDynamicIndexBuffers  = BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS;
		g_caps.limits.maxDynamicVertexBuffers = BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS;
		g_caps.limits.maxUniforms             = BGFX_CONFIG_MAX_UNIFORMS;
		g_caps.limits.maxOcclusionQueries     = BGFX_CONFIG_MAX_OCCLUSION_QUERIES;
		g_caps.limits.maxFBAttachments        = 1;
		g_caps.limits.maxEncoders             = init.limits.maxEncoders;
		g_caps.limits.minResourceCbSize       = init.limits.minResourceCbSize;
		g_caps.limits.transientVbSize         = init.limits.transientVbSize;
		g_caps.limits.transientIbSize         = init.limits.transientIbSize;

		g_caps.vendorId = init.vendorId;
		g_caps.deviceId = init.deviceId;

		BX_TRACE("Init...");

		// bgfx 1.104.7082
		//      ^ ^^^ ^^^^
		//      | |   +--- Commit number  (https://github.com/bkaradzic/bgfx / git rev-list --count HEAD)
		//      | +------- API version    (from https://github.com/bkaradzic/bgfx/blob/master/scripts/bgfx.idl#L4)
		//      +--------- Major revision (always 1)
		BX_TRACE("Version 1.%d.%d (commit: " BGFX_REV_SHA1 ")", BGFX_API_VERSION, BGFX_REV_NUMBER);

		errorState = ErrorState::ContextAllocated;

		s_ctx = BX_ALIGNED_NEW(g_allocator, Context, Context::kAlignment);
		if (s_ctx->init(init) )
		{
			BX_TRACE("Init complete.");
			return true;
		}

		BX_TRACE("Init failed.");

		switch (errorState)
		{
		case ErrorState::ContextAllocated:
			BX_ALIGNED_DELETE(g_allocator, s_ctx, Context::kAlignment);
			s_ctx = NULL;
			BX_FALLTHROUGH;

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
		BX_ASSERT(NULL == s_ctx, "bgfx is should be uninitialized here.");

		BX_ALIGNED_DELETE(g_allocator, ctx, Context::kAlignment);

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

	void reset(uint32_t _width, uint32_t _height, uint32_t _flags, TextureFormat::Enum _format)
	{
		BGFX_CHECK_API_THREAD();
		BX_ASSERT(0 == (_flags&BGFX_RESET_RESERVED_MASK), "Do not set reset reserved flags!");
		s_ctx->reset(_width, _height, _flags, _format);
	}

	Encoder* begin(bool _forThread)
	{
		return s_ctx->begin(_forThread);
	}

#define BGFX_ENCODER(_func) reinterpret_cast<EncoderImpl*>(this)->_func

	void Encoder::setMarker(const char* _marker)
	{
		BGFX_ENCODER(setMarker(_marker) );
	}

	void Encoder::setState(uint64_t _state, uint32_t _rgba)
	{
		BX_ASSERT(0 == (_state&BGFX_STATE_RESERVED_MASK), "Do not set state reserved flags!");
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
		const UniformRef& uniform = s_ctx->m_uniformRef[_handle.idx];
		BX_ASSERT(isValid(_handle) && 0 < uniform.m_refCount, "Setting invalid uniform (handle %3d)!", _handle.idx);
		BX_ASSERT(_num == UINT16_MAX || uniform.m_num >= _num, "Truncated uniform update. %d (max: %d)", _num, uniform.m_num);
		BGFX_ENCODER(setUniform(uniform.m_type, _handle, _value, UINT16_MAX != _num ? _num : uniform.m_num) );
	}

	void Encoder::setIndexBuffer(IndexBufferHandle _handle)
	{
		setIndexBuffer(_handle, 0, UINT32_MAX);
	}

	void Encoder::setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_HANDLE("setIndexBuffer", s_ctx->m_indexBufferHandle, _handle);
		const IndexBuffer& ib = s_ctx->m_indexBuffers[_handle.idx];
		BGFX_ENCODER(setIndexBuffer(_handle, ib, _firstIndex, _numIndices) );
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
		BX_ASSERT(NULL != _tib, "_tib can't be NULL");
		BGFX_CHECK_HANDLE("setIndexBuffer", s_ctx->m_indexBufferHandle, _tib->handle);
		BGFX_ENCODER(setIndexBuffer(_tib, _firstIndex, _numIndices) );
	}

	void Encoder::setVertexBuffer(
		  uint8_t _stream
		, VertexBufferHandle _handle
		, uint32_t _startVertex
		, uint32_t _numVertices
		, VertexLayoutHandle _layoutHandle
	)
	{
		BGFX_CHECK_HANDLE("setVertexBuffer", s_ctx->m_vertexBufferHandle, _handle);
		BGFX_CHECK_HANDLE_INVALID_OK("setVertexBuffer", s_ctx->m_layoutHandle, _layoutHandle);
		BGFX_ENCODER(setVertexBuffer(_stream, _handle, _startVertex, _numVertices, _layoutHandle) );
	}

	void Encoder::setVertexBuffer(uint8_t _stream, VertexBufferHandle _handle)
	{
		setVertexBuffer(_stream, _handle, 0, UINT32_MAX);
	}

	void Encoder::setVertexBuffer(
		  uint8_t _stream
		, DynamicVertexBufferHandle _handle
		, uint32_t _startVertex
		, uint32_t _numVertices
		, VertexLayoutHandle _layoutHandle
		)
	{
		BGFX_CHECK_HANDLE("setVertexBuffer", s_ctx->m_dynamicVertexBufferHandle, _handle);
		BGFX_CHECK_HANDLE_INVALID_OK("setVertexBuffer", s_ctx->m_layoutHandle, _layoutHandle);
		const DynamicVertexBuffer& dvb = s_ctx->m_dynamicVertexBuffers[_handle.idx];
		BGFX_ENCODER(setVertexBuffer(_stream, dvb, _startVertex, _numVertices, _layoutHandle) );
	}

	void Encoder::setVertexBuffer(uint8_t _stream, DynamicVertexBufferHandle _handle)
	{
		setVertexBuffer(_stream, _handle, 0, UINT32_MAX);
	}

	void Encoder::setVertexBuffer(
		  uint8_t _stream
		, const TransientVertexBuffer* _tvb
		, uint32_t _startVertex
		, uint32_t _numVertices
		, VertexLayoutHandle _layoutHandle
		)
	{
		BX_ASSERT(NULL != _tvb, "_tvb can't be NULL");
		BGFX_CHECK_HANDLE("setVertexBuffer", s_ctx->m_vertexBufferHandle, _tvb->handle);
		BGFX_CHECK_HANDLE_INVALID_OK("setVertexBuffer", s_ctx->m_layoutHandle, _layoutHandle);
		BGFX_ENCODER(setVertexBuffer(_stream, _tvb, _startVertex, _numVertices, _layoutHandle) );
	}

	void Encoder::setVertexBuffer(uint8_t _stream, const TransientVertexBuffer* _tvb)
	{
		setVertexBuffer(_stream, _tvb, 0, UINT32_MAX);
	}

	void Encoder::setVertexCount(uint32_t _numVertices)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_VERTEX_ID, "Auto generated vertices are not supported!");
		BGFX_ENCODER(setVertexCount(_numVertices) );
	}

	void Encoder::setInstanceDataBuffer(const InstanceDataBuffer* _idb)
	{
		setInstanceDataBuffer(_idb, 0, UINT32_MAX);
	}

	void Encoder::setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint32_t _start, uint32_t _num)
	{
		BX_ASSERT(NULL != _idb, "_idb can't be NULL");
		BGFX_ENCODER(setInstanceDataBuffer(_idb, _start, _num) );
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

	void Encoder::setInstanceCount(uint32_t _numInstances)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_VERTEX_ID, "Auto generated instances are not supported!");
		BGFX_ENCODER(setInstanceCount(_numInstances) );
	}

	void Encoder::setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags)
	{
		BGFX_CHECK_HANDLE("setTexture/UniformHandle", s_ctx->m_uniformHandle, _sampler);
		BGFX_CHECK_HANDLE_INVALID_OK("setTexture/TextureHandle", s_ctx->m_textureHandle, _handle);
		BX_ASSERT(_stage < g_caps.limits.maxTextureSamplers, "Invalid stage %d (max %d).", _stage, g_caps.limits.maxTextureSamplers);

		if (isValid(_handle) )
		{
			const TextureRef& ref = s_ctx->m_textureRef[_handle.idx];
			BX_ASSERT(!ref.isReadBack()
				, "Can't sample from texture which was created with BGFX_TEXTURE_READ_BACK. This is CPU only texture."
				);
			BX_UNUSED(ref);
		}

		BGFX_ENCODER(setTexture(_stage, _sampler, _handle, _flags) );
	}

	void Encoder::touch(ViewId _id)
	{
		ProgramHandle handle = BGFX_INVALID_HANDLE;
		submit(_id, handle);
	}

	void Encoder::submit(ViewId _id, ProgramHandle _program, uint32_t _depth, uint8_t _flags)
	{
		OcclusionQueryHandle handle = BGFX_INVALID_HANDLE;
		submit(_id, _program, handle, _depth, _flags);
	}

	void Encoder::submit(ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint32_t _depth, uint8_t _flags)
	{
		BX_ASSERT(false
			|| !isValid(_occlusionQuery)
			|| 0 != (g_caps.supported & BGFX_CAPS_OCCLUSION_QUERY)
			, "Occlusion query is not supported! Use bgfx::getCaps to check BGFX_CAPS_OCCLUSION_QUERY backend renderer capabilities."
			);
		BGFX_CHECK_HANDLE_INVALID_OK("submit", s_ctx->m_programHandle, _program);
		BGFX_CHECK_HANDLE_INVALID_OK("submit", s_ctx->m_occlusionQueryHandle, _occlusionQuery);
		BGFX_ENCODER(submit(_id, _program, _occlusionQuery, _depth, _flags) );
	}

	void Encoder::submit(ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, uint8_t _flags)
	{
		BGFX_CHECK_HANDLE_INVALID_OK("submit", s_ctx->m_programHandle, _program);
		BGFX_CHECK_HANDLE("submit", s_ctx->m_vertexBufferHandle, _indirectHandle);
		BGFX_CHECK_CAPS(BGFX_CAPS_DRAW_INDIRECT, "Draw indirect is not supported!");
		BGFX_ENCODER(submit(_id, _program, _indirectHandle, _start, _num, _depth, _flags) );
	}

	void Encoder::setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access)
	{
		BX_ASSERT(_stage < g_caps.limits.maxComputeBindings, "Invalid stage %d (max %d).", _stage, g_caps.limits.maxComputeBindings);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_indexBufferHandle, _handle);
		BGFX_ENCODER(setBuffer(_stage, _handle, _access) );
	}

	void Encoder::setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access)
	{
		BX_ASSERT(_stage < g_caps.limits.maxComputeBindings, "Invalid stage %d (max %d).", _stage, g_caps.limits.maxComputeBindings);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_vertexBufferHandle, _handle);
		BGFX_ENCODER(setBuffer(_stage, _handle, _access) );
	}

	void Encoder::setBuffer(uint8_t _stage, DynamicIndexBufferHandle _handle, Access::Enum _access)
	{
		BX_ASSERT(_stage < g_caps.limits.maxComputeBindings, "Invalid stage %d (max %d).", _stage, g_caps.limits.maxComputeBindings);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_dynamicIndexBufferHandle, _handle);
		const DynamicIndexBuffer& dib = s_ctx->m_dynamicIndexBuffers[_handle.idx];
		BGFX_ENCODER(setBuffer(_stage, dib.m_handle, _access) );
	}

	void Encoder::setBuffer(uint8_t _stage, DynamicVertexBufferHandle _handle, Access::Enum _access)
	{
		BX_ASSERT(_stage < g_caps.limits.maxComputeBindings, "Invalid stage %d (max %d).", _stage, g_caps.limits.maxComputeBindings);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_dynamicVertexBufferHandle, _handle);
		const DynamicVertexBuffer& dvb = s_ctx->m_dynamicVertexBuffers[_handle.idx];
		BGFX_ENCODER(setBuffer(_stage, dvb.m_handle, _access) );
	}

	void Encoder::setBuffer(uint8_t _stage, IndirectBufferHandle _handle, Access::Enum _access)
	{
		BX_ASSERT(_stage < g_caps.limits.maxComputeBindings, "Invalid stage %d (max %d).", _stage, g_caps.limits.maxComputeBindings);
		BGFX_CHECK_HANDLE("setBuffer", s_ctx->m_vertexBufferHandle, _handle);
		VertexBufferHandle handle = { _handle.idx };
		BGFX_ENCODER(setBuffer(_stage, handle, _access) );
	}

	void Encoder::setImage(uint8_t _stage, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format)
	{
		BX_ASSERT(_stage < g_caps.limits.maxComputeBindings, "Invalid stage %d (max %d).", _stage, g_caps.limits.maxComputeBindings);
		BGFX_CHECK_HANDLE_INVALID_OK("setImage/TextureHandle", s_ctx->m_textureHandle, _handle);
		_format = TextureFormat::Count == _format
			? TextureFormat::Enum(s_ctx->m_textureRef[_handle.idx].m_format)
			: _format
			;
		BX_ASSERT(_format != TextureFormat::BGRA8
			, "Can't use TextureFormat::BGRA8 with compute, use TextureFormat::RGBA8 instead."
			);

		if (isValid(_handle) )
		{
			const TextureRef& ref = s_ctx->m_textureRef[_handle.idx];
			BX_ASSERT(!ref.isReadBack()
				, "Can't texture (handle %d, '%S') which was created with BGFX_TEXTURE_READ_BACK with compute. This is CPU only texture."
				, _handle.idx
				, &ref.m_name
				);
			BX_UNUSED(ref);
		}

		BGFX_ENCODER(setImage(_stage, _handle, _mip, _access, _format) );
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

	void Encoder::discard(uint8_t _flags)
	{
		BGFX_ENCODER(discard(_flags) );
	}

	void Encoder::blit(ViewId _id, TextureHandle _dst, uint16_t _dstX, uint16_t _dstY, TextureHandle _src, uint16_t _srcX, uint16_t _srcY, uint16_t _width, uint16_t _height)
	{
		blit(_id, _dst, 0, _dstX, _dstY, 0, _src, 0, _srcX, _srcY, 0, _width, _height, 0);
	}

	void Encoder::blit(ViewId _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_TEXTURE_BLIT, "Texture blit is not supported!");
		BGFX_CHECK_HANDLE("blit/src TextureHandle", s_ctx->m_textureHandle, _src);
		BGFX_CHECK_HANDLE("blit/dst TextureHandle", s_ctx->m_textureHandle, _dst);

		const TextureRef& src = s_ctx->m_textureRef[_src.idx];
		const TextureRef& dst = s_ctx->m_textureRef[_dst.idx];

		BX_ASSERT(dst.isBlitDst()
			, "Blit destination texture (handle %d, '%S') is not created with `BGFX_TEXTURE_BLIT_DST` flag."
			, _dst.idx
			, &dst.m_name
			);

		BX_ASSERT(src.m_format == dst.m_format
			, "Texture format must match (src %s, dst %s)."
			, bimg::getName(bimg::TextureFormat::Enum(src.m_format) )
			, bimg::getName(bimg::TextureFormat::Enum(dst.m_format) )
			);
		BX_ASSERT(_srcMip < src.m_numMips, "Invalid blit src mip (%d > %d)", _srcMip, src.m_numMips - 1);
		BX_ASSERT(_dstMip < dst.m_numMips, "Invalid blit dst mip (%d > %d)", _dstMip, dst.m_numMips - 1);

		uint32_t srcWidth  = bx::max<uint32_t>(1, src.m_width  >> _srcMip);
		uint32_t srcHeight = bx::max<uint32_t>(1, src.m_height >> _srcMip);
		uint32_t dstWidth  = bx::max<uint32_t>(1, dst.m_width  >> _dstMip);
		uint32_t dstHeight = bx::max<uint32_t>(1, dst.m_height >> _dstMip);

		uint32_t srcDepth  = src.isCubeMap() ? 6 : bx::max<uint32_t>(1, src.m_depth >> _srcMip);
		uint32_t dstDepth  = dst.isCubeMap() ? 6 : bx::max<uint32_t>(1, dst.m_depth >> _dstMip);

		BX_ASSERT(_srcX < srcWidth && _srcY < srcHeight && _srcZ < srcDepth
			, "Blit src coordinates out of range (%d, %d, %d) >= (%d, %d, %d)"
			, _srcX, _srcY, _srcZ
			, srcWidth, srcHeight, srcDepth
			);
		BX_ASSERT(_dstX < dstWidth && _dstY < dstHeight && _dstZ < dstDepth
			, "Blit dst coordinates out of range (%d, %d, %d) >= (%d, %d, %d)"
			, _dstX, _dstY, _dstZ
			, dstWidth, dstHeight, dstDepth
			);

		srcWidth  = bx::min<uint32_t>(srcWidth,  _srcX + _width ) - _srcX;
		srcHeight = bx::min<uint32_t>(srcHeight, _srcY + _height) - _srcY;
		srcDepth  = bx::min<uint32_t>(srcDepth,  _srcZ + _depth ) - _srcZ;
		dstWidth  = bx::min<uint32_t>(dstWidth,  _dstX + _width ) - _dstX;
		dstHeight = bx::min<uint32_t>(dstHeight, _dstY + _height) - _dstY;
		dstDepth  = bx::min<uint32_t>(dstDepth,  _dstZ + _depth ) - _dstZ;

		const uint16_t width  = uint16_t(bx::min(srcWidth,  dstWidth ) );
		const uint16_t height = uint16_t(bx::min(srcHeight, dstHeight) );
		const uint16_t depth  = uint16_t(bx::min(srcDepth,  dstDepth ) );

		BGFX_ENCODER(blit(_id, _dst, _dstMip, _dstX, _dstY, _dstZ, _src, _srcMip, _srcX, _srcY, _srcZ, width, height, depth) );
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
		BX_ASSERT(0 < _size, "Invalid memory operation. _size is 0.");
		Memory* mem = (Memory*)BX_ALLOC(g_allocator, sizeof(Memory) + _size);
		mem->size = _size;
		mem->data = (uint8_t*)mem + sizeof(Memory);
		return mem;
	}

	const Memory* copy(const void* _data, uint32_t _size)
	{
		BX_ASSERT(0 < _size, "Invalid memory operation. _size is 0.");
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
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
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
		BX_ASSERT(
			  0 == (_flags & BGFX_BUFFER_INDEX32) || 0 != (g_caps.supported & BGFX_CAPS_INDEX32)
			, "32-bit indices are not supported. Use bgfx::getCaps to check BGFX_CAPS_INDEX32 backend renderer capabilities."
			);
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createIndexBuffer(_mem, _flags);
	}

	void setName(IndexBufferHandle _handle, const char* _name, int32_t _len)
	{
		s_ctx->setName(_handle, bx::StringView(_name, _len) );
	}

	void destroy(IndexBufferHandle _handle)
	{
		s_ctx->destroyIndexBuffer(_handle);
	}

	VertexLayoutHandle createVertexLayout(const VertexLayout& _layout)
	{
		return s_ctx->createVertexLayout(_layout);
	}

	void destroy(VertexLayoutHandle _handle)
	{
		s_ctx->destroyVertexLayout(_handle);
	}

	VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexLayout& _layout, uint16_t _flags)
	{
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
		BX_ASSERT(isValid(_layout), "Invalid VertexLayout.");
		return s_ctx->createVertexBuffer(_mem, _layout, _flags);
	}

	void setName(VertexBufferHandle _handle, const char* _name, int32_t _len)
	{
		s_ctx->setName(_handle, bx::StringView(_name, _len) );
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
		BX_ASSERT(
			  0 == (_flags & BGFX_BUFFER_INDEX32) || 0 != (g_caps.supported & BGFX_CAPS_INDEX32)
			, "32-bit indices are not supported. Use bgfx::getCaps to check BGFX_CAPS_INDEX32 backend renderer capabilities."
			);
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createDynamicIndexBuffer(_mem, _flags);
	}

	void update(DynamicIndexBufferHandle _handle, uint32_t _startIndex, const Memory* _mem)
	{
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
		s_ctx->update(_handle, _startIndex, _mem);
	}

	void destroy(DynamicIndexBufferHandle _handle)
	{
		s_ctx->destroyDynamicIndexBuffer(_handle);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(uint32_t _num, const VertexLayout& _layout, uint16_t _flags)
	{
		BX_ASSERT(isValid(_layout), "Invalid VertexLayout.");
		return s_ctx->createDynamicVertexBuffer(_num, _layout, _flags);
	}

	DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexLayout& _layout, uint16_t _flags)
	{
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
		BX_ASSERT(isValid(_layout), "Invalid VertexLayout.");
		return s_ctx->createDynamicVertexBuffer(_mem, _layout, _flags);
	}

	void update(DynamicVertexBufferHandle _handle, uint32_t _startVertex, const Memory* _mem)
	{
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
		s_ctx->update(_handle, _startVertex, _mem);
	}

	void destroy(DynamicVertexBufferHandle _handle)
	{
		s_ctx->destroyDynamicVertexBuffer(_handle);
	}

	uint32_t getAvailTransientIndexBuffer(uint32_t _num, bool _index32)
	{
		BX_ASSERT(0 < _num, "Requesting 0 indices.");
		return s_ctx->getAvailTransientIndexBuffer(_num, _index32);
	}

	uint32_t getAvailTransientVertexBuffer(uint32_t _num, const VertexLayout& _layout)
	{
		BX_ASSERT(0 < _num, "Requesting 0 vertices.");
		BX_ASSERT(isValid(_layout), "Invalid VertexLayout.");
		return s_ctx->getAvailTransientVertexBuffer(_num, _layout.m_stride);
	}

	uint32_t getAvailInstanceDataBuffer(uint32_t _num, uint16_t _stride)
	{
		BX_ASSERT(0 < _num, "Requesting 0 instances.");
		return s_ctx->getAvailTransientVertexBuffer(_num, _stride);
	}

	void allocTransientIndexBuffer(TransientIndexBuffer* _tib, uint32_t _num, bool _index32)
	{
		BX_ASSERT(NULL != _tib, "_tib can't be NULL");
		BX_ASSERT(0 < _num, "Requesting 0 indices.");
		BX_ASSERT(
			  !_index32 || 0 != (g_caps.supported & BGFX_CAPS_INDEX32)
			, "32-bit indices are not supported. Use bgfx::getCaps to check BGFX_CAPS_INDEX32 backend renderer capabilities."
			);

		s_ctx->allocTransientIndexBuffer(_tib, _num, _index32);

		const uint32_t indexSize = _tib->isIndex16 ? 2 : 4;
		BX_ASSERT(_num == _tib->size/ indexSize
			, "Failed to allocate transient index buffer (requested %d, available %d). "
			  "Use bgfx::getAvailTransient* functions to ensure availability."
			, _num
			, _tib->size/indexSize
			);
		BX_UNUSED(indexSize);
	}

	void allocTransientVertexBuffer(TransientVertexBuffer* _tvb, uint32_t _num, const VertexLayout& _layout)
	{
		BX_ASSERT(NULL != _tvb, "_tvb can't be NULL");
		BX_ASSERT(0 < _num, "Requesting 0 vertices.");
		BX_ASSERT(isValid(_layout), "Invalid VertexLayout.");

		VertexLayoutHandle layoutHandle;
		{
			BGFX_MUTEX_SCOPE(s_ctx->m_resourceApiLock);
			layoutHandle = s_ctx->findOrCreateVertexLayout(_layout, true);
		}
		BX_ASSERT(isValid(layoutHandle), "Failed to allocate vertex layout handle (BGFX_CONFIG_MAX_VERTEX_LAYOUTS, max: %d).", BGFX_CONFIG_MAX_VERTEX_LAYOUTS);

		s_ctx->allocTransientVertexBuffer(_tvb, _num, layoutHandle, _layout.m_stride);

		BX_ASSERT(_num == _tvb->size / _layout.m_stride
			, "Failed to allocate transient vertex buffer (requested %d, available %d). "
			  "Use bgfx::getAvailTransient* functions to ensure availability."
			, _num
			, _tvb->size / _layout.m_stride
			);
	}

	bool allocTransientBuffers(bgfx::TransientVertexBuffer* _tvb, const bgfx::VertexLayout& _layout, uint32_t _numVertices, bgfx::TransientIndexBuffer* _tib, uint32_t _numIndices, bool _index32)
	{
		BGFX_MUTEX_SCOPE(s_ctx->m_resourceApiLock);

		if (_numVertices == getAvailTransientVertexBuffer(_numVertices, _layout)
		&&  _numIndices  == getAvailTransientIndexBuffer(_numIndices, _index32) )
		{
			allocTransientVertexBuffer(_tvb, _numVertices, _layout);
			allocTransientIndexBuffer(_tib, _numIndices, _index32);
			return true;
		}

		return false;
	}

	void allocInstanceDataBuffer(InstanceDataBuffer* _idb, uint32_t _num, uint16_t _stride)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_INSTANCING, "Instancing is not supported!");
		BX_ASSERT(bx::isAligned(_stride, 16), "Stride must be multiple of 16.");
		BX_ASSERT(0 < _num, "Requesting 0 instanced data vertices.");
		s_ctx->allocInstanceDataBuffer(_idb, _num, _stride);
		BX_ASSERT(_num == _idb->size / _stride
			, "Failed to allocate instance data buffer (requested %d, available %d). "
			  "Use bgfx::getAvailTransient* functions to ensure availability."
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
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createShader(_mem);
	}

	uint16_t getShaderUniforms(ShaderHandle _handle, UniformHandle* _uniforms, uint16_t _max)
	{
		BX_WARN(NULL == _uniforms || 0 != _max
			, "Passing uniforms array pointer, but array maximum capacity is set to 0."
			);

		uint16_t num = s_ctx->getShaderUniforms(_handle, _uniforms, _max);

		BX_WARN(0 == _max || num <= _max
			, "Shader has more uniforms that capacity of output array. Output is truncated (num %d, max %d)."
			, num
			, _max
			);

		return num;
	}

	void setName(ShaderHandle _handle, const char* _name, int32_t _len)
	{
		s_ctx->setName(_handle, bx::StringView(_name, _len) );
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

	void isFrameBufferValid(uint8_t _num, const Attachment* _attachment, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err, "Frame buffer validation");

		uint8_t color = 0;
		uint8_t depth = 0;

		const TextureRef& firstTexture = s_ctx->m_textureRef[_attachment[0].handle.idx];

		const uint16_t firstAttachmentWidth  = bx::max<uint16_t>(firstTexture.m_width  >> _attachment[0].mip, 1);
		const uint16_t firstAttachmentHeight = bx::max<uint16_t>(firstTexture.m_height >> _attachment[0].mip, 1);

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			const Attachment&   at = _attachment[ii];
			const TextureHandle texHandle = at.handle;
			const TextureRef&   tr = s_ctx->m_textureRef[texHandle.idx];

			BGFX_ERROR_CHECK(true
				&& isValid(texHandle)
				&& s_ctx->m_textureHandle.isValid(texHandle.idx)
				, _err
				, BGFX_ERROR_FRAME_BUFFER_VALIDATION
				, "Invalid texture attachment."
				, "Attachment %d, texture handle %d."
				, ii
				, texHandle.idx
				);

			BGFX_ERROR_CHECK(true
				&& at.mip < tr.m_numMips
				, _err
				, BGFX_ERROR_FRAME_BUFFER_VALIDATION
				, "Invalid texture mip level."
				, "Attachment %d, Mip %d, texture (handle %d) number of mips %d."
				, ii
				, at.mip
				, texHandle.idx
				, tr.m_numMips
				);

			{
				const uint16_t numLayers = tr.is3D()
					? bx::max<uint16_t>(tr.m_depth >> at.mip, 1)
					: tr.m_numLayers * (tr.isCubeMap() ? 6 : 1)
					;

				BGFX_ERROR_CHECK(true
					&& (at.layer + at.numLayers) <= numLayers
					, _err
					, BGFX_ERROR_FRAME_BUFFER_VALIDATION
					, "Invalid texture layer range."
					, "Attachment %d, Layer: %d, Num: %d, Max number of layers: %d."
					, ii
					, at.layer
					, at.numLayers
					, numLayers
					);
			}

			BGFX_ERROR_CHECK(true
				&& _attachment[0].numLayers == at.numLayers
				, _err
				, BGFX_ERROR_FRAME_BUFFER_VALIDATION
				, "Mismatch in attachment layer count."
				, "Attachment %d, Given: %d, Expected: %d."
				, ii
				, at.numLayers
				, _attachment[0].numLayers
				);

			BGFX_ERROR_CHECK(true
				&& firstTexture.m_bbRatio == tr.m_bbRatio
				, _err
				, BGFX_ERROR_FRAME_BUFFER_VALIDATION
				, "Mismatch in texture back-buffer ratio."
				, "Attachment %d, Given: %d, Expected: %d."
				, ii
				, tr.m_bbRatio
				, firstTexture.m_bbRatio
				);

			BGFX_ERROR_CHECK(true
				&& firstTexture.m_numSamples == tr.m_numSamples
				, _err
				, BGFX_ERROR_FRAME_BUFFER_VALIDATION
				, "Mismatch in texture sample count."
				, "Attachment %d, Given: %d, Expected: %d."
				, ii
				, tr.m_numSamples
				, firstTexture.m_numSamples
				);

			if (BackbufferRatio::Count == firstTexture.m_bbRatio)
			{
				const uint16_t width  = bx::max<uint16_t>(tr.m_width  >> at.mip, 1);
				const uint16_t height = bx::max<uint16_t>(tr.m_height >> at.mip, 1);

				BGFX_ERROR_CHECK(true
					&& width  == firstAttachmentWidth
					&& height == firstAttachmentHeight
					, _err
					, BGFX_ERROR_FRAME_BUFFER_VALIDATION
					, "Mismatch in texture size."
					, "Attachment %d, Given: %dx%d, Expected: %dx%d."
					, ii
					, width
					, height
					, firstAttachmentWidth
					, firstAttachmentHeight
					);
			}

			if (bimg::isDepth(bimg::TextureFormat::Enum(tr.m_format) ) )
			{
				++depth;
			}
			else
			{
				++color;
			}

			BGFX_ERROR_CHECK(true
				&& 0 == (tr.m_flags & BGFX_TEXTURE_READ_BACK)
				, _err
				, BGFX_ERROR_FRAME_BUFFER_VALIDATION
				, "Frame buffer texture cannot be created with `BGFX_TEXTURE_READ_BACK`."
				, "Attachment %d, texture flags 0x%016" PRIx64 "."
				, ii
				, tr.m_flags
				);

			BGFX_ERROR_CHECK(true
				&& 0 != (tr.m_flags & BGFX_TEXTURE_RT_MASK)
				, _err
				, BGFX_ERROR_FRAME_BUFFER_VALIDATION
				, "Frame buffer texture is not created with one of `BGFX_TEXTURE_RT*` flags."
				, "Attachment %d, texture flags 0x%016" PRIx64 "."
				, ii
				, tr.m_flags
				);
		}

		BGFX_ERROR_CHECK(true
			&& color <= g_caps.limits.maxFBAttachments
			, _err
			, BGFX_ERROR_FRAME_BUFFER_VALIDATION
			, "Too many frame buffer color attachments."
			, "Num: %d, Max: %d."
			, _num
			, g_caps.limits.maxFBAttachments
			);

		BGFX_ERROR_CHECK(true
			&& depth <= 1
			, _err
			, BGFX_ERROR_FRAME_BUFFER_VALIDATION
			, "There can be only one depth texture attachment."
			, "Num depth attachments %d."
			, depth
			);
	}

	bool isFrameBufferValid(uint8_t _num, const Attachment* _attachment)
	{
		BGFX_MUTEX_SCOPE(s_ctx->m_resourceApiLock);
		bx::Error err;
		isFrameBufferValid(_num, _attachment, &err);
		return err.isOk();
	}

	static void isTextureValid(uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, uint16_t _numLayers, TextureFormat::Enum _format, uint64_t _flags, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err, "Texture validation");

		const bool is3DTexture = 1 < _depth;

		BGFX_ERROR_CHECK(false
			|| !_cubeMap
			|| !is3DTexture
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "Texture can't be 3D and cube map at the same time."
			, ""
			);

		BGFX_ERROR_CHECK(false
			|| !is3DTexture
			|| 0 != (g_caps.supported & BGFX_CAPS_TEXTURE_3D)
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "Texture3D is not supported! "
			  "Use bgfx::getCaps to check `BGFX_CAPS_TEXTURE_3D` backend renderer capabilities."
			, ""
			);

		BGFX_ERROR_CHECK(false
			|| _width  <= g_caps.limits.maxTextureSize
			|| _height <= g_caps.limits.maxTextureSize
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "Requested texture width/height is above the `maxTextureSize` limit."
			, "Texture width x height requested %d x %d (Max: %d)."
			, _width
			, _height
			, g_caps.limits.maxTextureSize
			);

		BGFX_ERROR_CHECK(false
			|| 0 == (_flags & BGFX_TEXTURE_RT_MASK)
			|| 0 == (_flags & BGFX_TEXTURE_READ_BACK)
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "Can't create render target with `BGFX_TEXTURE_READ_BACK` flag."
			, ""
			);

		BGFX_ERROR_CHECK(false
			|| 0 == (_flags & BGFX_TEXTURE_COMPUTE_WRITE)
			|| 0 == (_flags & BGFX_TEXTURE_READ_BACK)
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "Can't create compute texture with `BGFX_TEXTURE_READ_BACK` flag."
			, ""
			);

		BGFX_ERROR_CHECK(false
			|| 1 >= _numLayers
			|| 0 != (g_caps.supported & BGFX_CAPS_TEXTURE_2D_ARRAY)
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "Texture array is not supported! "
			  "Use bgfx::getCaps to check `BGFX_CAPS_TEXTURE_2D_ARRAY` backend renderer capabilities."
			, ""
			);

		BGFX_ERROR_CHECK(false
			|| _numLayers <= g_caps.limits.maxTextureLayers
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "Requested number of texture array layers is above the `maxTextureLayers` limit."
			, "Number of texture array layers requested %d (Max: %d)."
			, _numLayers
			, g_caps.limits.maxTextureLayers
			);

		bool formatSupported;
		if (0 != (_flags & (BGFX_TEXTURE_RT | BGFX_TEXTURE_RT_WRITE_ONLY)) )
		{
			formatSupported = 0 != (g_caps.formats[_format] & BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER);
		}
		else
		{
			formatSupported = 0 != (g_caps.formats[_format] & (0
				| BGFX_CAPS_FORMAT_TEXTURE_2D
				| BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED
				| BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
				) );
		}

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

		BGFX_ERROR_CHECK(
			  formatSupported
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "Texture format is not supported! "
			  "Use bgfx::isTextureValid to check support for texture format before creating it."
			, "Texture format: %s."
			, getName(_format)
			);

		BGFX_ERROR_CHECK(false
			|| 0 == (_flags & BGFX_TEXTURE_MSAA_SAMPLE)
			|| 0 != (g_caps.formats[_format] & BGFX_CAPS_FORMAT_TEXTURE_MSAA)
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "MSAA sampling for this texture format is not supported."
			, "Texture format: %s."
			, getName(_format)
			);

		BGFX_ERROR_CHECK(false
			|| 0 == (_flags & BGFX_TEXTURE_SRGB)
			|| 0 != (g_caps.formats[_format] & srgbCaps & (0
					| BGFX_CAPS_FORMAT_TEXTURE_2D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_3D_SRGB
					| BGFX_CAPS_FORMAT_TEXTURE_CUBE_SRGB
					) )
			, _err
			, BGFX_ERROR_TEXTURE_VALIDATION
			, "sRGB sampling for this texture format is not supported."
			, "Texture format: %s."
			, getName(_format)
			);
	}

	bool isTextureValid(uint16_t _depth, bool _cubeMap, uint16_t _numLayers, TextureFormat::Enum _format, uint64_t _flags)
	{
		bx::Error err;
		isTextureValid(0, 0, _depth, _cubeMap, _numLayers, _format, _flags, &err);
		return err.isOk();
	}

	void isIdentifierValid(const bx::StringView& _name, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err, "Uniform identifier validation");

		BGFX_ERROR_CHECK(false
			|| !_name.isEmpty()
			, _err
			, BGFX_ERROR_IDENTIFIER_VALIDATION
			, "Identifier can't be empty."
			, ""
			);

		BGFX_ERROR_CHECK(false
			|| PredefinedUniform::Count == nameToPredefinedUniformEnum(_name)
			, _err
			, BGFX_ERROR_IDENTIFIER_VALIDATION
			, "Identifier can't use predefined uniform name."
			, ""
			);

		const char ch = *_name.getPtr();
		BGFX_ERROR_CHECK(false
			|| bx::isAlpha(ch)
			|| '_' == ch
			, _err
			, BGFX_ERROR_IDENTIFIER_VALIDATION
			, "The first character of an identifier should be either an alphabet character or an underscore."
			, ""
			);

		bool result = true;

		for (const char* ptr = _name.getPtr() + 1, *term = _name.getTerm()
			; ptr != term && result
			; ++ptr
			)
		{
			result &= bx::isAlphaNum(*ptr) || '_' == *ptr;
		}

		BGFX_ERROR_CHECK(false
			|| result
			, _err
			, BGFX_ERROR_IDENTIFIER_VALIDATION
			, "Identifier contains invalid characters. Identifier must be the alphabet character, number, or underscore."
			, ""
			);
	}

	void calcTextureSize(TextureInfo& _info, uint16_t _width, uint16_t _height, uint16_t _depth, bool _cubeMap, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format)
	{
		bimg::imageGetSize( (bimg::TextureInfo*)&_info, _width, _height, _depth, _cubeMap, _hasMips, _numLayers, bimg::TextureFormat::Enum(_format) );
	}

	TextureHandle createTexture(const Memory* _mem, uint64_t _flags, uint8_t _skip, TextureInfo* _info)
	{
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
		return s_ctx->createTexture(_mem, _flags, _skip, _info, BackbufferRatio::Count, false);
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

		_width  = bx::max<uint16_t>(1, _width);
		_height = bx::max<uint16_t>(1, _height);
	}

	static TextureHandle createTexture2D(BackbufferRatio::Enum _ratio, uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint64_t _flags, const Memory* _mem)
	{
		if (BackbufferRatio::Count != _ratio)
		{
			_width  = uint16_t(s_ctx->m_init.resolution.width);
			_height = uint16_t(s_ctx->m_init.resolution.height);
			getTextureSizeFromRatio(_ratio, _width, _height);
		}

		bx::ErrorAssert err;
		isTextureValid(_width, _height, 0, false, _numLayers, _format, _flags, &err);

		if (!err.isOk() )
		{
			return BGFX_INVALID_HANDLE;
		}

		const uint8_t numMips = calcNumMips(_hasMips, _width, _height);
		_numLayers = bx::max<uint16_t>(_numLayers, 1);

		if (BX_ENABLED(BGFX_CONFIG_DEBUG)
		&&  NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _width, _height, 1, false, _hasMips, _numLayers, _format);
			BX_ASSERT(ti.storageSize == _mem->size
				, "createTexture2D: Texture storage size doesn't match passed memory size (storage size: %d, memory size: %d)"
				, ti.storageSize
				, _mem->size
				);
		}

		uint32_t size = sizeof(uint32_t)+sizeof(TextureCreate);
		const Memory* mem = alloc(size);

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic, bx::ErrorAssert{});

		TextureCreate tc;
		tc.m_width     = _width;
		tc.m_height    = _height;
		tc.m_depth     = 0;
		tc.m_numLayers = _numLayers;
		tc.m_numMips   = numMips;
		tc.m_format    = _format;
		tc.m_cubeMap   = false;
		tc.m_mem       = _mem;
		bx::write(&writer, tc, bx::ErrorAssert{});

		return s_ctx->createTexture(mem, _flags, 0, NULL, _ratio, NULL != _mem);
	}

	TextureHandle createTexture2D(uint16_t _width, uint16_t _height, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint64_t _flags, const Memory* _mem)
	{
		BX_ASSERT(_width > 0 && _height > 0, "Invalid texture size (width %d, height %d).", _width, _height);
		return createTexture2D(BackbufferRatio::Count, _width, _height, _hasMips, _numLayers, _format, _flags, _mem);
	}

	TextureHandle createTexture2D(BackbufferRatio::Enum _ratio, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint64_t _flags)
	{
		BX_ASSERT(_ratio < BackbufferRatio::Count, "Invalid back buffer ratio.");
		return createTexture2D(_ratio, 0, 0, _hasMips, _numLayers, _format, _flags, NULL);
	}

	TextureHandle createTexture3D(uint16_t _width, uint16_t _height, uint16_t _depth, bool _hasMips, TextureFormat::Enum _format, uint64_t _flags, const Memory* _mem)
	{
		bx::ErrorAssert err;
		isTextureValid(_width, _height, _depth, false, 1, _format, _flags, &err);

		if (!err.isOk() )
		{
			return BGFX_INVALID_HANDLE;
		}

		const uint8_t numMips = calcNumMips(_hasMips, _width, _height, _depth);

		if (BX_ENABLED(BGFX_CONFIG_DEBUG)
		&&  NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _width, _height, _depth, false, _hasMips, 1, _format);
			BX_ASSERT(ti.storageSize == _mem->size
				, "createTexture3D: Texture storage size doesn't match passed memory size (storage size: %d, memory size: %d)"
				, ti.storageSize
				, _mem->size
				);
		}

		uint32_t size = sizeof(uint32_t)+sizeof(TextureCreate);
		const Memory* mem = alloc(size);

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic, bx::ErrorAssert{});

		TextureCreate tc;
		tc.m_width     = _width;
		tc.m_height    = _height;
		tc.m_depth     = _depth;
		tc.m_numLayers = 1;
		tc.m_numMips   = numMips;
		tc.m_format    = _format;
		tc.m_cubeMap   = false;
		tc.m_mem       = _mem;
		bx::write(&writer, tc, bx::ErrorAssert{});

		return s_ctx->createTexture(mem, _flags, 0, NULL, BackbufferRatio::Count, NULL != _mem);
	}

	TextureHandle createTextureCube(uint16_t _size, bool _hasMips, uint16_t _numLayers, TextureFormat::Enum _format, uint64_t _flags, const Memory* _mem)
	{
		bx::ErrorAssert err;
		isTextureValid(_size, _size, 0, true, _numLayers, _format, _flags, &err);

		if (!err.isOk() )
		{
			return BGFX_INVALID_HANDLE;
		}

		const uint8_t numMips = calcNumMips(_hasMips, _size, _size);
		_numLayers = bx::max<uint16_t>(_numLayers, 1);

		if (BX_ENABLED(BGFX_CONFIG_DEBUG)
		&&  NULL != _mem)
		{
			TextureInfo ti;
			calcTextureSize(ti, _size, _size, 1, true, _hasMips, _numLayers, _format);
			BX_ASSERT(ti.storageSize == _mem->size
				, "createTextureCube: Texture storage size doesn't match passed memory size (storage size: %d, memory size: %d)"
				, ti.storageSize
				, _mem->size
				);
		}

		uint32_t size = sizeof(uint32_t)+sizeof(TextureCreate);
		const Memory* mem = alloc(size);

		bx::StaticMemoryBlockWriter writer(mem->data, mem->size);
		uint32_t magic = BGFX_CHUNK_MAGIC_TEX;
		bx::write(&writer, magic, bx::ErrorAssert{});

		TextureCreate tc;
		tc.m_width     = _size;
		tc.m_height    = _size;
		tc.m_depth     = 0;
		tc.m_numLayers = _numLayers;
		tc.m_numMips   = numMips;
		tc.m_format    = _format;
		tc.m_cubeMap   = true;
		tc.m_mem       = _mem;
		bx::write(&writer, tc, bx::ErrorAssert{});

		return s_ctx->createTexture(mem, _flags, 0, NULL, BackbufferRatio::Count, NULL != _mem);
	}

	void setName(TextureHandle _handle, const char* _name, int32_t _len)
	{
		s_ctx->setName(_handle, bx::StringView(_name, _len) );
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
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
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
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
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
		BX_ASSERT(NULL != _mem, "_mem can't be NULL");
		BX_ASSERT(_side <= 5, "Invalid side %d.", _side);
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
		BX_ASSERT(NULL != _data, "_data can't be NULL");
		BGFX_CHECK_CAPS(BGFX_CAPS_TEXTURE_READ_BACK, "Texture read-back is not supported!");
		return s_ctx->readTexture(_handle, _data, _mip);
	}

	FrameBufferHandle createFrameBuffer(uint16_t _width, uint16_t _height, TextureFormat::Enum _format, uint64_t _textureFlags)
	{
		_textureFlags |= _textureFlags&BGFX_TEXTURE_RT_MSAA_MASK ? 0 : BGFX_TEXTURE_RT;
		TextureHandle th = createTexture2D(_width, _height, false, 1, _format, _textureFlags);
		return createFrameBuffer(1, &th, true);
	}

	FrameBufferHandle createFrameBuffer(BackbufferRatio::Enum _ratio, TextureFormat::Enum _format, uint64_t _textureFlags)
	{
		BX_ASSERT(_ratio < BackbufferRatio::Count, "Invalid back buffer ratio.");
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
			at.init(_handles[ii], Access::Write, 0, 1, 0, BGFX_RESOLVE_AUTO_GEN_MIPS);
		}
		return createFrameBuffer(_num, attachment, _destroyTextures);
	}

	FrameBufferHandle createFrameBuffer(uint8_t _num, const Attachment* _attachment, bool _destroyTextures)
	{
		BX_ASSERT(_num != 0, "Number of frame buffer attachments can't be 0.");
		BX_ASSERT(_num <= BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
			, "Number of frame buffer attachments is larger than allowed %d (max: %d)."
			, _num
			, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS
			);
		BX_ASSERT(NULL != _attachment, "_attachment can't be NULL");
		return s_ctx->createFrameBuffer(_num, _attachment, _destroyTextures);
	}

	FrameBufferHandle createFrameBuffer(void* _nwh, uint16_t _width, uint16_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat)
	{
		BGFX_CHECK_CAPS(BGFX_CAPS_SWAP_CHAIN, "Swap chain is not supported!");
		BX_WARN(_width > 0 && _height > 0
			, "Invalid frame buffer dimensions (width %d, height %d)."
			, _width
			, _height
			);
		BX_ASSERT(_format == TextureFormat::Count || bimg::isColor(bimg::TextureFormat::Enum(_format) )
			, "Invalid texture format for color (%s)."
			, bimg::getName(bimg::TextureFormat::Enum(_format) )
			);
		BX_ASSERT(_depthFormat == TextureFormat::Count || bimg::isDepth(bimg::TextureFormat::Enum(_depthFormat) )
			, "Invalid texture format for depth (%s)."
			, bimg::getName(bimg::TextureFormat::Enum(_depthFormat) )
			);
		return s_ctx->createFrameBuffer(
			  _nwh
			, bx::max<uint16_t>(_width, 1)
			, bx::max<uint16_t>(_height, 1)
			, _format
			, _depthFormat
			);
	}

	void setName(FrameBufferHandle _handle, const char* _name, int32_t _len)
	{
		s_ctx->setName(_handle, bx::StringView(_name, _len) );
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
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewName(_id, _name);
	}

	void setViewRect(ViewId _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewRect(_id, _x, _y, _width, _height);
	}

	void setViewRect(ViewId _id, uint16_t _x, uint16_t _y, BackbufferRatio::Enum _ratio)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);

		uint16_t width  = uint16_t(s_ctx->m_init.resolution.width);
		uint16_t height = uint16_t(s_ctx->m_init.resolution.height);
		getTextureSizeFromRatio(_ratio, width, height);
		setViewRect(_id, _x, _y, width, height);
	}

	void setViewScissor(ViewId _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewScissor(_id, _x, _y, _width, _height);
	}

	void setViewClear(ViewId _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewClear(_id, _flags, _rgba, _depth, _stencil);
	}

	void setViewClear(ViewId _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewClear(_id, _flags, _depth, _stencil, _0, _1, _2, _3, _4, _5, _6, _7);
	}

	void setViewMode(ViewId _id, ViewMode::Enum _mode)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewMode(_id, _mode);
	}

	void setViewFrameBuffer(ViewId _id, FrameBufferHandle _handle)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewFrameBuffer(_id, _handle);
	}

	void setViewTransform(ViewId _id, const void* _view, const void* _proj)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewTransform(_id, _view, _proj);
	}

	void setViewOrder(ViewId _id, uint16_t _num, const ViewId* _order)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->setViewOrder(_id, _num, _order);
	}

	void resetView(ViewId _id)
	{
		BX_ASSERT(checkView(_id), "Invalid view id: %d", _id);
		s_ctx->resetView(_id);
	}

#define BGFX_CHECK_ENCODER0()                               \
	BGFX_CHECK_API_THREAD();                                \
	BGFX_FATAL(NULL != s_ctx->m_encoder0, Fatal::DebugCheck \
		, "bgfx is configured to allow only encoder API. See: `BGFX_CONFIG_ENCODER_API_ONLY`.")

	void setMarker(const char* _marker)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setMarker(_marker);
	}

	void setState(uint64_t _state, uint32_t _rgba)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setState(_state, _rgba);
	}

	void setCondition(OcclusionQueryHandle _handle, bool _visible)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setCondition(_handle, _visible);
	}

	void setStencil(uint32_t _fstencil, uint32_t _bstencil)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setStencil(_fstencil, _bstencil);
	}

	uint16_t setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		BGFX_CHECK_ENCODER0();
		return s_ctx->m_encoder0->setScissor(_x, _y, _width, _height);
	}

	void setScissor(uint16_t _cache)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setScissor(_cache);
	}

	uint32_t setTransform(const void* _mtx, uint16_t _num)
	{
		BGFX_CHECK_ENCODER0();
		return s_ctx->m_encoder0->setTransform(_mtx, _num);
	}

	uint32_t allocTransform(Transform* _transform, uint16_t _num)
	{
		BGFX_CHECK_ENCODER0();
		return s_ctx->m_encoder0->allocTransform(_transform, _num);
	}

	void setTransform(uint32_t _cache, uint16_t _num)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setTransform(_cache, _num);
	}

	void setUniform(UniformHandle _handle, const void* _value, uint16_t _num)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setUniform(_handle, _value, _num);
	}

	void setIndexBuffer(IndexBufferHandle _handle)
	{
		setIndexBuffer(_handle, 0, UINT32_MAX);
	}

	void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setIndexBuffer(_handle, _firstIndex, _numIndices);
	}

	void setIndexBuffer(DynamicIndexBufferHandle _handle)
	{
		setIndexBuffer(_handle, 0, UINT32_MAX);
	}

	void setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setIndexBuffer(_handle, _firstIndex, _numIndices);
	}

	void setIndexBuffer(const TransientIndexBuffer* _tib)
	{
		setIndexBuffer(_tib, 0, UINT32_MAX);
	}

	void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _firstIndex, uint32_t _numIndices)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setIndexBuffer(_tib, _firstIndex, _numIndices);
	}

	void setVertexBuffer(
		  uint8_t _stream
		, VertexBufferHandle _handle
		, uint32_t _startVertex
		, uint32_t _numVertices
		, VertexLayoutHandle _layoutHandle
		)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setVertexBuffer(_stream, _handle, _startVertex, _numVertices, _layoutHandle);
	}

	void setVertexBuffer(uint8_t _stream, VertexBufferHandle _handle)
	{
		setVertexBuffer(_stream, _handle, 0, UINT32_MAX);
	}

	void setVertexBuffer(
		  uint8_t _stream
		, DynamicVertexBufferHandle _handle
		, uint32_t _startVertex
		, uint32_t _numVertices
		, VertexLayoutHandle _layoutHandle
		)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setVertexBuffer(_stream, _handle, _startVertex, _numVertices, _layoutHandle);
	}

	void setVertexBuffer(uint8_t _stream, DynamicVertexBufferHandle _handle)
	{
		setVertexBuffer(_stream, _handle, 0, UINT32_MAX);
	}

	void setVertexBuffer(
		  uint8_t _stream
		, const TransientVertexBuffer* _tvb
		, uint32_t _startVertex
		, uint32_t _numVertices
		, VertexLayoutHandle _layoutHandle
		)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setVertexBuffer(_stream, _tvb, _startVertex, _numVertices, _layoutHandle);
	}

	void setVertexBuffer(uint8_t _stream, const TransientVertexBuffer* _tvb)
	{
		setVertexBuffer(_stream, _tvb, 0, UINT32_MAX);
	}

	void setVertexCount(uint32_t _numVertices)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setVertexCount(_numVertices);
	}

	void setInstanceDataBuffer(const InstanceDataBuffer* _idb)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setInstanceDataBuffer(_idb);
	}

	void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint32_t _start, uint32_t _num)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setInstanceDataBuffer(_idb, _start, _num);
	}

	void setInstanceDataBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setInstanceDataBuffer(_handle, _startVertex, _num);
	}

	void setInstanceDataBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setInstanceDataBuffer(_handle, _startVertex, _num);
	}

	void setInstanceCount(uint32_t _numInstances)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setInstanceCount(_numInstances);
	}

	void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setTexture(_stage, _sampler, _handle, _flags);
	}

	void touch(ViewId _id)
	{
		ProgramHandle handle = BGFX_INVALID_HANDLE;
		submit(_id, handle);
	}

	void submit(ViewId _id, ProgramHandle _program, uint32_t _depth, uint8_t _flags)
	{
		OcclusionQueryHandle handle = BGFX_INVALID_HANDLE;
		submit(_id, _program, handle, _depth, _flags);
	}

	void submit(ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint32_t _depth, uint8_t _flags)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->submit(_id, _program, _occlusionQuery, _depth, _flags);
	}

	void submit(ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, uint8_t _flags)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->submit(_id, _program, _indirectHandle, _start, _num, _depth, _flags);
	}

	void setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, DynamicIndexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, DynamicVertexBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setBuffer(uint8_t _stage, IndirectBufferHandle _handle, Access::Enum _access)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setBuffer(_stage, _handle, _access);
	}

	void setImage(uint8_t _stage, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->setImage(_stage, _handle, _mip, _access, _format);
	}

	void dispatch(ViewId _id, ProgramHandle _handle, uint32_t _numX, uint32_t _numY, uint32_t _numZ, uint8_t _flags)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->dispatch(_id, _handle, _numX, _numY, _numZ, _flags);
	}

	void dispatch(ViewId _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->dispatch(_id, _handle, _indirectHandle, _start, _num, _flags);
	}

	void discard(uint8_t _flags)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->discard(_flags);
	}

	void blit(ViewId _id, TextureHandle _dst, uint16_t _dstX, uint16_t _dstY, TextureHandle _src, uint16_t _srcX, uint16_t _srcY, uint16_t _width, uint16_t _height)
	{
		blit(_id, _dst, 0, _dstX, _dstY, 0, _src, 0, _srcX, _srcY, 0, _width, _height, 0);
	}

	void blit(ViewId _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth)
	{
		BGFX_CHECK_ENCODER0();
		s_ctx->m_encoder0->blit(_id, _dst, _dstMip, _dstX, _dstY, _dstZ, _src, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
	}

	void requestScreenShot(FrameBufferHandle _handle, const char* _filePath)
	{
		BGFX_CHECK_API_THREAD();
		s_ctx->requestScreenShot(_handle, _filePath);
	}

#undef BGFX_CHECK_ENCODER0

} // namespace bgfx

#if BGFX_CONFIG_PREFER_DISCRETE_GPU
extern "C"
{
	// When laptop setup has integrated and discrete GPU, following driver workarounds will
	// select discrete GPU:

	// Reference(s):
	// - https://web.archive.org/web/20180722051003/https://docs.nvidia.com/gameworks/content/technologies/desktop/optimus.htm
	//
	__declspec(dllexport) uint32_t NvOptimusEnablement = UINT32_C(1);

	// Reference(s):
	// - https://web.archive.org/web/20180722051032/https://gpuopen.com/amdpowerxpressrequesthighperformance/
	//
	__declspec(dllexport) uint32_t AmdPowerXpressRequestHighPerformance = UINT32_C(1);
}
#endif // BGFX_CONFIG_PREFER_DISCRETE_GPU

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
BGFX_TEXTURE_FORMAT_BIMG(ATC);
BGFX_TEXTURE_FORMAT_BIMG(ATCE);
BGFX_TEXTURE_FORMAT_BIMG(ATCI);
BGFX_TEXTURE_FORMAT_BIMG(ASTC4x4);
BGFX_TEXTURE_FORMAT_BIMG(ASTC5x5);
BGFX_TEXTURE_FORMAT_BIMG(ASTC6x6);
BGFX_TEXTURE_FORMAT_BIMG(ASTC8x5);
BGFX_TEXTURE_FORMAT_BIMG(ASTC8x6);
BGFX_TEXTURE_FORMAT_BIMG(ASTC10x5);
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

#define FLAGS_MASK_TEST(_flags, _mask) ( (_flags) == ( (_flags) & (_mask) ) )

BX_STATIC_ASSERT(FLAGS_MASK_TEST(0
	| BGFX_SAMPLER_INTERNAL_DEFAULT
	| BGFX_SAMPLER_INTERNAL_SHARED
	, BGFX_SAMPLER_RESERVED_MASK
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
	, BGFX_SUBMIT_INTERNAL_RESERVED_MASK
	) );

BX_STATIC_ASSERT( (0
	| BGFX_STATE_ALPHA_REF_MASK
	| BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
	| BGFX_STATE_BLEND_EQUATION_MASK
	| BGFX_STATE_BLEND_INDEPENDENT
	| BGFX_STATE_BLEND_MASK
	| BGFX_STATE_CONSERVATIVE_RASTER
	| BGFX_STATE_CULL_MASK
	| BGFX_STATE_DEPTH_TEST_MASK
	| BGFX_STATE_FRONT_CCW
	| BGFX_STATE_LINEAA
	| BGFX_STATE_MSAA
	| BGFX_STATE_POINT_SIZE_MASK
	| BGFX_STATE_PT_MASK
	| BGFX_STATE_RESERVED_MASK
	| BGFX_STATE_WRITE_MASK
	) == (0
	^ BGFX_STATE_ALPHA_REF_MASK
	^ BGFX_STATE_BLEND_ALPHA_TO_COVERAGE
	^ BGFX_STATE_BLEND_EQUATION_MASK
	^ BGFX_STATE_BLEND_INDEPENDENT
	^ BGFX_STATE_BLEND_MASK
	^ BGFX_STATE_CONSERVATIVE_RASTER
	^ BGFX_STATE_CULL_MASK
	^ BGFX_STATE_DEPTH_TEST_MASK
	^ BGFX_STATE_FRONT_CCW
	^ BGFX_STATE_LINEAA
	^ BGFX_STATE_MSAA
	^ BGFX_STATE_POINT_SIZE_MASK
	^ BGFX_STATE_PT_MASK
	^ BGFX_STATE_RESERVED_MASK
	^ BGFX_STATE_WRITE_MASK
	) );

BX_STATIC_ASSERT(FLAGS_MASK_TEST(BGFX_CAPS_TEXTURE_COMPARE_LEQUAL, BGFX_CAPS_TEXTURE_COMPARE_ALL) );

BX_STATIC_ASSERT( (0
	| BGFX_CAPS_ALPHA_TO_COVERAGE
	| BGFX_CAPS_BLEND_INDEPENDENT
	| BGFX_CAPS_COMPUTE
	| BGFX_CAPS_CONSERVATIVE_RASTER
	| BGFX_CAPS_DRAW_INDIRECT
	| BGFX_CAPS_FRAGMENT_DEPTH
	| BGFX_CAPS_FRAGMENT_ORDERING
	| BGFX_CAPS_GRAPHICS_DEBUGGER
	| BGFX_CAPS_HDR10
	| BGFX_CAPS_HIDPI
	| BGFX_CAPS_INDEX32
	| BGFX_CAPS_INSTANCING
	| BGFX_CAPS_OCCLUSION_QUERY
	| BGFX_CAPS_RENDERER_MULTITHREADED
	| BGFX_CAPS_SWAP_CHAIN
	| BGFX_CAPS_TEXTURE_2D_ARRAY
	| BGFX_CAPS_TEXTURE_3D
	| BGFX_CAPS_TEXTURE_BLIT
	| BGFX_CAPS_TEXTURE_CUBE_ARRAY
	| BGFX_CAPS_TEXTURE_DIRECT_ACCESS
	| BGFX_CAPS_TEXTURE_READ_BACK
	| BGFX_CAPS_VERTEX_ATTRIB_HALF
	| BGFX_CAPS_VERTEX_ATTRIB_UINT10
	| BGFX_CAPS_VERTEX_ID
	) == (0
	^ BGFX_CAPS_ALPHA_TO_COVERAGE
	^ BGFX_CAPS_BLEND_INDEPENDENT
	^ BGFX_CAPS_COMPUTE
	^ BGFX_CAPS_CONSERVATIVE_RASTER
	^ BGFX_CAPS_DRAW_INDIRECT
	^ BGFX_CAPS_FRAGMENT_DEPTH
	^ BGFX_CAPS_FRAGMENT_ORDERING
	^ BGFX_CAPS_GRAPHICS_DEBUGGER
	^ BGFX_CAPS_HDR10
	^ BGFX_CAPS_HIDPI
	^ BGFX_CAPS_INDEX32
	^ BGFX_CAPS_INSTANCING
	^ BGFX_CAPS_OCCLUSION_QUERY
	^ BGFX_CAPS_RENDERER_MULTITHREADED
	^ BGFX_CAPS_SWAP_CHAIN
	^ BGFX_CAPS_TEXTURE_2D_ARRAY
	^ BGFX_CAPS_TEXTURE_3D
	^ BGFX_CAPS_TEXTURE_BLIT
	^ BGFX_CAPS_TEXTURE_CUBE_ARRAY
	^ BGFX_CAPS_TEXTURE_DIRECT_ACCESS
	^ BGFX_CAPS_TEXTURE_READ_BACK
	^ BGFX_CAPS_VERTEX_ATTRIB_HALF
	^ BGFX_CAPS_VERTEX_ATTRIB_UINT10
	^ BGFX_CAPS_VERTEX_ID
	) );

#undef FLAGS_MASK_TEST

namespace bgfx
{
	struct CallbackC99 : public CallbackI
	{
		virtual ~CallbackC99()
		{
		}

		virtual void fatal(const char* _filePath, uint16_t _line, Fatal::Enum _code, const char* _str) override
		{
			m_interface->vtbl->fatal(m_interface, _filePath, _line, (bgfx_fatal_t)_code, _str);
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

#include "bgfx.idl.inl"
