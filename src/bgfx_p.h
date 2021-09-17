/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_P_H_HEADER_GUARD
#define BGFX_P_H_HEADER_GUARD

#include <bx/platform.h>

#ifndef BGFX_CONFIG_DEBUG
#	define BGFX_CONFIG_DEBUG 0
#endif // BGFX_CONFIG_DEBUG

#if BGFX_CONFIG_DEBUG || BX_COMPILER_CLANG_ANALYZER
#	define BX_TRACE _BX_TRACE
#	define BX_WARN  _BX_WARN
#	define BX_ASSERT _BX_ASSERT
#	define BX_CONFIG_ALLOCATOR_DEBUG 1
#endif // BGFX_CONFIG_DEBUG

#include <bgfx/bgfx.h>
#include "config.h"

#include <inttypes.h>

// Check handle, cannot be bgfx::kInvalidHandle and must be valid.
#define BGFX_CHECK_HANDLE(_desc, _handleAlloc, _handle) \
	BX_ASSERT(isValid(_handle)                          \
		&& _handleAlloc.isValid(_handle.idx)            \
		, "Invalid handle. %s handle: %d (max %d)"      \
		, _desc                                         \
		, _handle.idx                                   \
		, _handleAlloc.getMaxHandles()                  \
		)

// Check handle, it's ok to be bgfx::kInvalidHandle or must be valid.
#define BGFX_CHECK_HANDLE_INVALID_OK(_desc, _handleAlloc, _handle) \
	BX_ASSERT(!isValid(_handle)                                    \
		|| _handleAlloc.isValid(_handle.idx)                       \
		, "Invalid handle. %s handle: %d (max %d)"                 \
		, _desc                                                    \
		, _handle.idx                                              \
		, _handleAlloc.getMaxHandles()                             \
		)

#if BGFX_CONFIG_MULTITHREADED
#	define BGFX_MUTEX_SCOPE(_mutex) bx::MutexScope BX_CONCATENATE(mutexScope, __LINE__)(_mutex)
#else
#	define BGFX_MUTEX_SCOPE(_mutex) BX_NOOP()
#endif // BGFX_CONFIG_MULTITHREADED

#if BGFX_CONFIG_PROFILER
#	define BGFX_PROFILER_SCOPE(_name, _abgr)            ProfilerScope BX_CONCATENATE(profilerScope, __LINE__)(_name, _abgr, __FILE__, uint16_t(__LINE__) )
#	define BGFX_PROFILER_BEGIN(_name, _abgr)            g_callback->profilerBegin(_name, _abgr, __FILE__, uint16_t(__LINE__) )
#	define BGFX_PROFILER_BEGIN_LITERAL(_name, _abgr)    g_callback->profilerBeginLiteral(_name, _abgr, __FILE__, uint16_t(__LINE__) )
#	define BGFX_PROFILER_END()                          g_callback->profilerEnd()
#	define BGFX_PROFILER_SET_CURRENT_THREAD_NAME(_name) BX_NOOP()
#else
#	define BGFX_PROFILER_SCOPE(_name, _abgr)            BX_NOOP()
#	define BGFX_PROFILER_BEGIN(_name, _abgr)            BX_NOOP()
#	define BGFX_PROFILER_BEGIN_LITERAL(_name, _abgr)    BX_NOOP()
#	define BGFX_PROFILER_END()                          BX_NOOP()
#	define BGFX_PROFILER_SET_CURRENT_THREAD_NAME(_name) BX_NOOP()
#endif // BGFX_PROFILER_SCOPE

namespace bgfx
{
#if BX_COMPILER_CLANG_ANALYZER
	void __attribute__( (analyzer_noreturn) ) fatal(Fatal::Enum _code, const char* _format, ...);
#else
	void fatal(const char* _filePath, uint16_t _line, Fatal::Enum _code, const char* _format, ...);
#endif // BX_COMPILER_CLANG_ANALYZER

	void trace(const char* _filePath, uint16_t _line, const char* _format, ...);

	inline bool operator==(const VertexLayoutHandle& _lhs, const VertexLayoutHandle& _rhs) { return _lhs.idx == _rhs.idx; }
	inline bool operator==(const UniformHandle& _lhs,    const UniformHandle&    _rhs) { return _lhs.idx == _rhs.idx; }
}

#define _BX_TRACE(_format, ...)                                                         \
	BX_MACRO_BLOCK_BEGIN                                                                \
		bgfx::trace(__FILE__, uint16_t(__LINE__), "BGFX " _format "\n", ##__VA_ARGS__); \
	BX_MACRO_BLOCK_END

#define _BX_WARN(_condition, _format, ...)            \
	BX_MACRO_BLOCK_BEGIN                              \
		if (!BX_IGNORE_C4127(_condition) )            \
		{                                             \
			BX_TRACE("WARN " _format, ##__VA_ARGS__); \
		}                                             \
	BX_MACRO_BLOCK_END

#define _BX_ASSERT(_condition, _format, ...)                                                            \
	BX_MACRO_BLOCK_BEGIN                                                                                \
		if (!BX_IGNORE_C4127(_condition) )                                                              \
		{                                                                                               \
			BX_TRACE("CHECK " _format, ##__VA_ARGS__);                                                  \
			bgfx::fatal(__FILE__, uint16_t(__LINE__), bgfx::Fatal::DebugCheck, _format, ##__VA_ARGS__); \
		}                                                                                               \
	BX_MACRO_BLOCK_END

#define BGFX_FATAL(_condition, _err, _format, ...)                             \
	BX_MACRO_BLOCK_BEGIN                                                       \
		if (!BX_IGNORE_C4127(_condition) )                                     \
		{                                                                      \
			fatal(__FILE__, uint16_t(__LINE__), _err, _format, ##__VA_ARGS__); \
		}                                                                      \
	BX_MACRO_BLOCK_END

#define BGFX_ERROR_CHECK(_condition, _err, _result, _msg, _format, ...) \
	if (!BX_IGNORE_C4127(_condition) )                                  \
	{                                                                   \
		BX_ERROR_SET(_err, _result, _msg);                              \
		BX_TRACE("%.*s: 0x%08x '%.*s' - " _format                       \
			, bxErrorScope.getName().getLength()                        \
			, bxErrorScope.getName().getPtr()                           \
			, _err->get().code                                          \
			, _err->getMessage().getLength()                            \
			, _err->getMessage().getPtr()                               \
			, ##__VA_ARGS__                                             \
			);                                                          \
		return;                                                         \
	}

#define BGFX_ERROR_ASSERT(_err)            \
	BX_ASSERT((_err)->isOk()               \
		, "ERROR: 0x%08x '%.*s'."          \
		, (_err)->get().code               \
		, (_err)->getMessage().getLength() \
		, (_err)->getMessage().getPtr()    \
		);

#include <bx/allocator.h>
#include <bx/bx.h>
#include <bx/cpu.h>
#include <bx/debug.h>
#include <bx/endian.h>
#include <bx/error.h>
#include <bx/float4x4_t.h>
#include <bx/handlealloc.h>
#include <bx/hash.h>
#include <bx/math.h>
#include <bx/mutex.h>
#include <bx/os.h>
#include <bx/readerwriter.h>
#include <bx/ringbuffer.h>
#include <bx/sort.h>
#include <bx/string.h>
#include <bx/thread.h>
#include <bx/timer.h>
#include <bx/uint32_t.h>

#include <bgfx/platform.h>
#include <bimg/bimg.h>
#include "shader.h"
#include "vertexlayout.h"
#include "version.h"

#define BGFX_CHUNK_MAGIC_TEX BX_MAKEFOURCC('T', 'E', 'X', 0x0)

#define BGFX_CLEAR_COLOR_USE_PALETTE UINT16_C(0x8000)
#define BGFX_CLEAR_MASK (0                 \
			| BGFX_CLEAR_COLOR             \
			| BGFX_CLEAR_DEPTH             \
			| BGFX_CLEAR_STENCIL           \
			| BGFX_CLEAR_COLOR_USE_PALETTE \
			)

#if BGFX_CONFIG_USE_TINYSTL
namespace bgfx
{
	struct TinyStlAllocator
	{
		static void* static_allocate(size_t _bytes);
		static void static_deallocate(void* _ptr, size_t /*_bytes*/);
	};
} // namespace bgfx
#	define TINYSTL_ALLOCATOR bgfx::TinyStlAllocator
#	include <tinystl/string.h>
#	include <tinystl/unordered_map.h>
#	include <tinystl/unordered_set.h>
#	include <tinystl/vector.h>

namespace tinystl
{
	template<typename T, typename Alloc = TINYSTL_ALLOCATOR>
	class list : public vector<T, Alloc>
	{
	public:
		void push_front(const T& _value)
		{
			this->insert(this->begin(), _value);
		}

		void pop_front()
		{
			this->erase(this->begin() );
		}

		void sort()
		{
			bx::quickSort(
				  this->begin()
				, uint32_t(this->end() - this->begin() )
				, sizeof(T)
				, [](const void* _a, const void* _b) -> int32_t {
					const T& lhs = *(const T*)(_a);
					const T& rhs = *(const T*)(_b);
					return lhs < rhs ? -1 : 1;
				});
		}
	};

} // namespace tinystl

namespace stl = tinystl;
#else
#	include <list>
#	include <string>
#	include <unordered_map>
#	include <unordered_set>
#	include <vector>
namespace stl = std;
#endif // BGFX_CONFIG_USE_TINYSTL

#if BX_PLATFORM_ANDROID
#	include <android/native_window.h>
#elif BX_PLATFORM_WINDOWS
#	include <windows.h>
#endif // BX_PLATFORM_*

#define BGFX_MAX_COMPUTE_BINDINGS BGFX_CONFIG_MAX_TEXTURE_SAMPLERS

#define BGFX_SAMPLER_INTERNAL_DEFAULT       UINT32_C(0x10000000)
#define BGFX_SAMPLER_INTERNAL_SHARED        UINT32_C(0x20000000)

#define BGFX_RESET_INTERNAL_FORCE           UINT32_C(0x80000000)

#define BGFX_STATE_INTERNAL_SCISSOR         UINT64_C(0x2000000000000000)
#define BGFX_STATE_INTERNAL_OCCLUSION_QUERY UINT64_C(0x4000000000000000)

#define BGFX_SUBMIT_INTERNAL_NONE              UINT8_C(0x00)
#define BGFX_SUBMIT_INTERNAL_INDEX32           UINT8_C(0x40)
#define BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE UINT8_C(0x80)
#define BGFX_SUBMIT_INTERNAL_RESERVED_MASK     UINT8_C(0xff)

#define BGFX_RENDERER_NOOP_NAME       "Noop"
#define BGFX_RENDERER_AGC_NAME        "AGC"
#define BGFX_RENDERER_DIRECT3D9_NAME  "Direct3D 9"
#define BGFX_RENDERER_DIRECT3D11_NAME "Direct3D 11"
#define BGFX_RENDERER_DIRECT3D12_NAME "Direct3D 12"
#define BGFX_RENDERER_GNM_NAME        "GNM"
#define BGFX_RENDERER_METAL_NAME      "Metal"
#define BGFX_RENDERER_NVN_NAME        "NVN"
#define BGFX_RENDERER_VULKAN_NAME     "Vulkan"
#define BGFX_RENDERER_WEBGPU_NAME     "WebGPU"

#if BGFX_CONFIG_RENDERER_OPENGL
#	if BGFX_CONFIG_RENDERER_OPENGL >= 31 && BGFX_CONFIG_RENDERER_OPENGL <= 33
#		if BGFX_CONFIG_RENDERER_OPENGL == 31
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 3.1"
#		elif BGFX_CONFIG_RENDERER_OPENGL == 32
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 3.2"
#		else
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 3.3"
#		endif // 31+
#	elif BGFX_CONFIG_RENDERER_OPENGL >= 40 && BGFX_CONFIG_RENDERER_OPENGL <= 46
#		if BGFX_CONFIG_RENDERER_OPENGL == 40
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 4.0"
#		elif BGFX_CONFIG_RENDERER_OPENGL == 41
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 4.1"
#		elif BGFX_CONFIG_RENDERER_OPENGL == 42
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 4.2"
#		elif BGFX_CONFIG_RENDERER_OPENGL == 43
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 4.3"
#		elif BGFX_CONFIG_RENDERER_OPENGL == 44
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 4.4"
#		elif BGFX_CONFIG_RENDERER_OPENGL == 45
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 4.5"
#		else
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 4.6"
#		endif // 40+
#	else
#		define BGFX_RENDERER_OPENGL_NAME "OpenGL 2.1"
#	endif // BGFX_CONFIG_RENDERER_OPENGL
#elif BGFX_CONFIG_RENDERER_OPENGLES
#	if BGFX_CONFIG_RENDERER_OPENGLES == 30
#		define BGFX_RENDERER_OPENGL_NAME "OpenGL ES 3.0"
#	elif BGFX_CONFIG_RENDERER_OPENGLES == 31
#		define BGFX_RENDERER_OPENGL_NAME "OpenGL ES 3.1"
#	elif BGFX_CONFIG_RENDERER_OPENGLES >= 32
#		define BGFX_RENDERER_OPENGL_NAME "OpenGL ES 3.2"
#	else
#		define BGFX_RENDERER_OPENGL_NAME "OpenGL ES 2.0"
#	endif // BGFX_CONFIG_RENDERER_OPENGLES
#else
#	define BGFX_RENDERER_OPENGL_NAME "OpenGL"
#endif //

namespace bgfx
{
	extern InternalData g_internalData;
	extern PlatformData g_platformData;
	extern bool g_platformDataChangedSinceReset;
	extern void isFrameBufferValid(uint8_t _num, const Attachment* _attachment, bx::Error* _err);

#if BGFX_CONFIG_MAX_DRAW_CALLS < (64<<10)
	typedef uint16_t RenderItemCount;
#else
	typedef uint32_t RenderItemCount;
#endif // BGFX_CONFIG_MAX_DRAW_CALLS < (64<<10)

	struct Handle
	{
		enum Enum
		{
			IndexBuffer,
			Shader,
			Texture,
			VertexBuffer,

			Count
		};

		uint16_t type;
		uint16_t idx;
	};

#define CONVERT_HANDLE(_name)                           \
	inline Handle convert(_name##Handle _handle)        \
	{                                                   \
		Handle handle = { Handle::_name, _handle.idx }; \
		return handle;                                  \
	}

	CONVERT_HANDLE(IndexBuffer);
	CONVERT_HANDLE(Shader);
	CONVERT_HANDLE(Texture);
	CONVERT_HANDLE(VertexBuffer);

#undef CONVERT_HANDLE

	const char* getTypeName(Handle _handle);

	inline bool isValid(const VertexLayout& _layout)
	{
		return 0 != _layout.m_stride;
	}

	struct Condition
	{
		enum Enum
		{
			LessEqual,
			GreaterEqual,
		};
	};

	bool windowsVersionIs(Condition::Enum _op, uint32_t _version);

	constexpr bool isShaderType(uint32_t _magic, char _type)
	{
		return uint32_t(_type) == (_magic & BX_MAKEFOURCC(0xff, 0, 0, 0) );
	}

	inline bool isShaderBin(uint32_t _magic)
	{
		return BX_MAKEFOURCC(0, 'S', 'H', 0) == (_magic & BX_MAKEFOURCC(0, 0xff, 0xff, 0) )
			&& (isShaderType(_magic, 'C') || isShaderType(_magic, 'F') || isShaderType(_magic, 'V') )
			;
	}

	inline bool isShaderVerLess(uint32_t _magic, uint8_t _version)
	{
		return (_magic & BX_MAKEFOURCC(0, 0, 0, 0xff) ) < BX_MAKEFOURCC(0, 0, 0, _version);
	}

	const char* getShaderTypeName(uint32_t _magic);

	struct Clear
	{
		void set(uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
		{
			m_flags    = _flags;
			m_index[0] = uint8_t(_rgba>>24);
			m_index[1] = uint8_t(_rgba>>16);
			m_index[2] = uint8_t(_rgba>> 8);
			m_index[3] = uint8_t(_rgba>> 0);
			m_depth    = _depth;
			m_stencil  = _stencil;
		}

		void set(uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7)
		{
			m_flags = (_flags & ~BGFX_CLEAR_COLOR)
				| (0xff != (_0&_1&_2&_3&_4&_5&_6&_7) ? BGFX_CLEAR_COLOR|BGFX_CLEAR_COLOR_USE_PALETTE : 0)
				;
			m_index[0] = _0;
			m_index[1] = _1;
			m_index[2] = _2;
			m_index[3] = _3;
			m_index[4] = _4;
			m_index[5] = _5;
			m_index[6] = _6;
			m_index[7] = _7;
			m_depth    = _depth;
			m_stencil  = _stencil;
		}

		uint8_t  m_index[8];
		float    m_depth;
		uint8_t  m_stencil;
		uint16_t m_flags;
	};

	struct Rect
	{
		Rect()
		{
		}

		Rect(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
			: m_x(_x)
			, m_y(_y)
			, m_width(_width)
			, m_height(_height)
		{
		}

		void clear()
		{
			m_x      = 0;
			m_y      = 0;
			m_width  = 0;
			m_height = 0;
		}

		bool isZero() const
		{
			uint64_t ui64 = *( (uint64_t*)this);
			return UINT64_C(0) == ui64;
		}

		bool isZeroArea() const
		{
			return 0 == m_width
				|| 0 == m_height
				;
		}

		void set(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
		{
			m_x = _x;
			m_y = _y;
			m_width  = _width;
			m_height = _height;
		}

		void setIntersect(const Rect& _a, const Rect& _b)
		{
			const uint16_t sx = bx::max<uint16_t>(_a.m_x, _b.m_x);
			const uint16_t sy = bx::max<uint16_t>(_a.m_y, _b.m_y);
			const uint16_t ex = bx::min<uint16_t>(_a.m_x + _a.m_width,  _b.m_x + _b.m_width );
			const uint16_t ey = bx::min<uint16_t>(_a.m_y + _a.m_height, _b.m_y + _b.m_height);
			m_x = sx;
			m_y = sy;
			m_width  = (uint16_t)bx::uint32_satsub(ex, sx);
			m_height = (uint16_t)bx::uint32_satsub(ey, sy);
		}

		void intersect(const Rect& _a)
		{
			setIntersect(*this, _a);
		}

		uint16_t m_x;
		uint16_t m_y;
		uint16_t m_width;
		uint16_t m_height;
	};

	struct TextureCreate
	{
		TextureFormat::Enum m_format;
		uint16_t m_width;
		uint16_t m_height;
		uint16_t m_depth;
		uint16_t m_numLayers;
		uint8_t  m_numMips;
		bool     m_cubeMap;
		const Memory* m_mem;
	};

	extern const uint32_t g_uniformTypeSize[UniformType::Count+1];
	extern CallbackI* g_callback;
	extern bx::AllocatorI* g_allocator;
	extern Caps g_caps;

	typedef bx::StringT<&g_allocator> String;

	struct ProfilerScope
	{
		ProfilerScope(const char* _name, uint32_t _abgr, const char* _filePath, uint16_t _line)
		{
			g_callback->profilerBeginLiteral(_name, _abgr, _filePath, _line);
		}

		~ProfilerScope()
		{
			g_callback->profilerEnd();
		}
	};

	void setGraphicsDebuggerPresent(bool _present);
	bool isGraphicsDebuggerPresent();
	void release(const Memory* _mem);
	const char* getAttribName(Attrib::Enum _attr);
	const char* getAttribNameShort(Attrib::Enum _attr);
	void getTextureSizeFromRatio(BackbufferRatio::Enum _ratio, uint16_t& _width, uint16_t& _height);
	TextureFormat::Enum getViableTextureFormat(const bimg::ImageContainer& _imageContainer);
	const char* getName(TextureFormat::Enum _fmt);
	const char* getName(UniformHandle _handle);
	const char* getName(ShaderHandle _handle);
	const char* getName(Topology::Enum _topology);

	template<typename Ty>
	inline void release(Ty)
	{
	}

	template<>
	inline void release(Memory* _mem)
	{
		release( (const Memory*)_mem);
	}

	inline uint32_t castfu(float _value)
	{
		union {	float fl; uint32_t ui; } un;
		un.fl = _value;
		return un.ui;
	}

	inline uint64_t packStencil(uint32_t _fstencil, uint32_t _bstencil)
	{
		return (uint64_t(_bstencil)<<32)|uint64_t(_fstencil);
	}

	inline uint32_t unpackStencil(uint8_t _0or1, uint64_t _stencil)
	{
		return uint32_t( (_stencil >> (32*_0or1) ) );
	}

	inline bool needBorderColor(uint64_t _flags)
	{
		return BGFX_SAMPLER_U_BORDER == (_flags & BGFX_SAMPLER_U_BORDER)
			|| BGFX_SAMPLER_V_BORDER == (_flags & BGFX_SAMPLER_V_BORDER)
			|| BGFX_SAMPLER_W_BORDER == (_flags & BGFX_SAMPLER_W_BORDER)
			;
	}

	inline uint8_t calcNumMips(bool _hasMips, uint16_t _width, uint16_t _height, uint16_t _depth = 1)
	{
		if (_hasMips)
		{
			const uint32_t max = bx::max(_width, _height, _depth);
			const uint32_t num = 1 + uint32_t(bx::log2<int32_t>(max) );

			return uint8_t(num);
		}

		return 1;
	}

	/// Dump vertex layout info into debug output.
	void dump(const VertexLayout& _layout);

	/// Dump resolution and reset info into debug output.
	void dump(const Resolution& _resolution);

	struct TextVideoMem
	{
		TextVideoMem()
			: m_mem(NULL)
			, m_size(0)
			, m_width(0)
			, m_height(0)
			, m_small(false)
		{
			resize(false, 1, 1);
			clear();
		}

		~TextVideoMem()
		{
			BX_FREE(g_allocator, m_mem);
		}

		void resize(bool _small, uint32_t _width, uint32_t _height)
		{
			uint32_t width  = bx::uint32_imax(1, _width/8);
			uint32_t height = bx::uint32_imax(1, _height/(_small ? 8 : 16) );

			if (NULL == m_mem
			||  m_width  != width
			||  m_height != height
			||  m_small  != _small)
			{
				m_small  = _small;
				m_width  = (uint16_t)width;
				m_height = (uint16_t)height;

				uint32_t size = m_size;
				m_size = m_width * m_height;

				m_mem = (MemSlot*)BX_REALLOC(g_allocator, m_mem, m_size * sizeof(MemSlot) );

				if (size < m_size)
				{
					bx::memSet(&m_mem[size], 0, (m_size-size) * sizeof(MemSlot) );
				}
			}
		}

		void clear(uint8_t _attr = 0)
		{
			MemSlot* mem = m_mem;
			bx::memSet(mem, 0, m_size * sizeof(MemSlot) );
			if (_attr != 0)
			{
				for (uint32_t ii = 0, num = m_size; ii < num; ++ii)
				{
					mem[ii].attribute = _attr;
				}
			}
		}

		void printfVargs(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList);

		void printf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...)
		{
			va_list argList;
			va_start(argList, _format);
			printfVargs(_x, _y, _attr, _format, argList);
			va_end(argList);
		}

		void image(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch)
		{
			if (_x < m_width && _y < m_height)
			{
				MemSlot* dst = &m_mem[_y*m_width+_x];
				const uint8_t* src = (const uint8_t*)_data;
				const uint32_t width  =  bx::min<uint32_t>(m_width,  _width +_x)-_x;
				const uint32_t height =  bx::min<uint32_t>(m_height, _height+_y)-_y;
				const uint32_t dstPitch = m_width;

				for (uint32_t ii = 0; ii < height; ++ii)
				{
					for (uint32_t jj = 0; jj < width; ++jj)
					{
						dst[jj].character = src[jj*2];
						dst[jj].attribute = src[jj*2+1];
					}

					src += _pitch;
					dst += dstPitch;
				}
			}
		}

		struct MemSlot
		{
			uint8_t attribute;
			uint8_t character;
		};

		MemSlot* m_mem;
		uint32_t m_size;
		uint16_t m_width;
		uint16_t m_height;
		bool m_small;
	};

	struct TextVideoMemBlitter
	{
		void init();
		void shutdown();

		TextureHandle m_texture;
		TransientVertexBuffer* m_vb;
		TransientIndexBuffer* m_ib;
		VertexLayout m_layout;
		ProgramHandle m_program;
	};

	struct RendererContextI;

	extern void blit(RendererContextI* _renderCtx, TextVideoMemBlitter& _blitter, const TextVideoMem& _mem);

	inline void blit(RendererContextI* _renderCtx, TextVideoMemBlitter& _blitter, const TextVideoMem* _mem)
	{
		blit(_renderCtx, _blitter, *_mem);
	}

	template <uint32_t maxKeys>
	struct UpdateBatchT
	{
		UpdateBatchT()
			: m_num(0)
		{
		}

		void add(uint32_t _key, uint32_t _value)
		{
			uint32_t num = m_num++;
			m_keys[num] = _key;
			m_values[num] = _value;
		}

		bool sort()
		{
			if (0 < m_num)
			{
				uint32_t* tempKeys = (uint32_t*)alloca(sizeof(m_keys) );
				uint32_t* tempValues = (uint32_t*)alloca(sizeof(m_values) );
				bx::radixSort(m_keys, tempKeys, m_values, tempValues, m_num);
				return true;
			}

			return false;
		}

		bool isFull() const
		{
			return m_num >= maxKeys;
		}

		void reset()
		{
			m_num = 0;
		}

		uint32_t m_num;
		uint32_t m_keys[maxKeys];
		uint32_t m_values[maxKeys];
	};

	struct ClearQuad
	{
		ClearQuad()
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_program); ++ii)
			{
				m_program[ii].idx = kInvalidHandle;
			}
		}

		void init();
		void shutdown();

		VertexBufferHandle m_vb;
		VertexLayout m_layout;
		ProgramHandle m_program[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
	};

	struct PredefinedUniform
	{
		enum Enum
		{
			ViewRect,
			ViewTexel,
			View,
			InvView,
			Proj,
			InvProj,
			ViewProj,
			InvViewProj,
			Model,
			ModelView,
			ModelViewProj,
			AlphaRef,
			Count
		};

		uint32_t m_loc;
		uint16_t m_count;
		uint8_t m_type;
	};

	const char* getUniformTypeName(UniformType::Enum _enum);
	UniformType::Enum nameToUniformTypeEnum(const char* _name);
	const char* getPredefinedUniformName(PredefinedUniform::Enum _enum);
	PredefinedUniform::Enum nameToPredefinedUniformEnum(const char* _name);

	class CommandBuffer
	{
		BX_CLASS(CommandBuffer
			, NO_COPY
			, NO_ASSIGNMENT
			);

	public:
		CommandBuffer()
			: m_buffer(NULL)
			, m_pos(0)
			, m_size(0)
			, m_minCapacity(0)
		{
			resize();
			finish();
		}

		~CommandBuffer()
		{
			BX_FREE(g_allocator, m_buffer);
		}

		void init(uint32_t _minCapacity)
		{
			m_minCapacity = bx::alignUp(_minCapacity, 1024);
			resize();
		}

		enum Enum
		{
			RendererInit,
			RendererShutdownBegin,
			CreateVertexLayout,
			CreateIndexBuffer,
			CreateVertexBuffer,
			CreateDynamicIndexBuffer,
			UpdateDynamicIndexBuffer,
			CreateDynamicVertexBuffer,
			UpdateDynamicVertexBuffer,
			CreateShader,
			CreateProgram,
			CreateTexture,
			UpdateTexture,
			ResizeTexture,
			CreateFrameBuffer,
			CreateUniform,
			UpdateViewName,
			InvalidateOcclusionQuery,
			SetName,
			End,
			RendererShutdownEnd,
			DestroyVertexLayout,
			DestroyIndexBuffer,
			DestroyVertexBuffer,
			DestroyDynamicIndexBuffer,
			DestroyDynamicVertexBuffer,
			DestroyShader,
			DestroyProgram,
			DestroyTexture,
			DestroyFrameBuffer,
			DestroyUniform,
			ReadTexture,
		};

		void resize(uint32_t _capacity = 0)
		{
			m_capacity = bx::alignUp(bx::max(_capacity, m_minCapacity), 1024);
			m_buffer = (uint8_t*)BX_REALLOC(g_allocator, m_buffer, m_capacity);
		}

		void write(const void* _data, uint32_t _size)
		{
			BX_ASSERT(m_size == 0, "Called write outside start/finish (m_size: %d)?", m_size);
			if (m_pos + _size > m_capacity)
			{
				resize(m_capacity + (16<<10) );
			}

			bx::memCopy(&m_buffer[m_pos], _data, _size);
			m_pos += _size;
		}

		template<typename Type>
		void write(const Type& _in)
		{
			align(BX_ALIGNOF(Type) );
			write(reinterpret_cast<const uint8_t*>(&_in), sizeof(Type) );
		}

		void read(void* _data, uint32_t _size)
		{
			BX_ASSERT(m_pos + _size <= m_size
				, "CommandBuffer::read error (pos: %d-%d, size: %d)."
				, m_pos
				, m_pos + _size
				, m_size
				);
			bx::memCopy(_data, &m_buffer[m_pos], _size);
			m_pos += _size;
		}

		template<typename Type>
		void read(Type& _in)
		{
			align(BX_ALIGNOF(Type) );
			read(reinterpret_cast<uint8_t*>(&_in), sizeof(Type) );
		}

		const uint8_t* skip(uint32_t _size)
		{
			BX_ASSERT(m_pos + _size <= m_size
				, "CommandBuffer::skip error (pos: %d-%d, size: %d)."
				, m_pos
				, m_pos + _size
				, m_size
				);
			const uint8_t* result = &m_buffer[m_pos];
			m_pos += _size;
			return result;
		}

		template<typename Type>
		void skip()
		{
			align(BX_ALIGNOF(Type) );
			skip(sizeof(Type) );
		}

		void align(uint32_t _alignment)
		{
			const uint32_t mask = _alignment-1;
			const uint32_t pos = (m_pos+mask) & (~mask);
			m_pos = pos;
		}

		void reset()
		{
			m_pos = 0;
		}

		void start()
		{
			m_pos = 0;
			m_size = 0;
		}

		void finish()
		{
			uint8_t cmd = End;
			write(cmd);
			m_size = m_pos;
			m_pos = 0;

			if (m_size < m_minCapacity
			&&  m_capacity != m_minCapacity)
			{
				resize();
			}
		}

		uint8_t* m_buffer;
		uint32_t m_pos;
		uint32_t m_size;
		uint32_t m_capacity;
		uint32_t m_minCapacity;
	};

	//
	constexpr uint8_t  kSortKeyViewNumBits         = 10;
	constexpr uint8_t  kSortKeyViewBitShift        = 64-kSortKeyViewNumBits;
	constexpr uint64_t kSortKeyViewMask            = uint64_t(BGFX_CONFIG_MAX_VIEWS-1)<<kSortKeyViewBitShift;

	constexpr uint8_t  kSortKeyDrawBitShift        = kSortKeyViewBitShift - 1;
	constexpr uint64_t kSortKeyDrawBit             = uint64_t(1)<<kSortKeyDrawBitShift;

	//
	constexpr uint8_t  kSortKeyDrawTypeNumBits     = 2;
	constexpr uint8_t  kSortKeyDrawTypeBitShift    = kSortKeyDrawBitShift - kSortKeyDrawTypeNumBits;
	constexpr uint64_t kSortKeyDrawTypeMask        = uint64_t(3)<<kSortKeyDrawTypeBitShift;

	constexpr uint64_t kSortKeyDrawTypeProgram     = uint64_t(0)<<kSortKeyDrawTypeBitShift;
	constexpr uint64_t kSortKeyDrawTypeDepth       = uint64_t(1)<<kSortKeyDrawTypeBitShift;
	constexpr uint64_t kSortKeyDrawTypeSequence    = uint64_t(2)<<kSortKeyDrawTypeBitShift;

	//
	constexpr uint8_t  kSortKeyTransNumBits        = 2;

	constexpr uint8_t  kSortKeyDraw0BlendShift     = kSortKeyDrawTypeBitShift - kSortKeyTransNumBits;
	constexpr uint64_t kSortKeyDraw0BlendMask      = uint64_t(0x3)<<kSortKeyDraw0BlendShift;

	constexpr uint8_t  kSortKeyDraw0ProgramShift   = kSortKeyDraw0BlendShift - BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM;
	constexpr uint64_t kSortKeyDraw0ProgramMask    = uint64_t(BGFX_CONFIG_MAX_PROGRAMS-1)<<kSortKeyDraw0ProgramShift;

	constexpr uint8_t  kSortKeyDraw0DepthShift     = kSortKeyDraw0ProgramShift - BGFX_CONFIG_SORT_KEY_NUM_BITS_DEPTH;
	constexpr uint64_t kSortKeyDraw0DepthMask      = ( (uint64_t(1)<<BGFX_CONFIG_SORT_KEY_NUM_BITS_DEPTH)-1)<<kSortKeyDraw0DepthShift;

	//
	constexpr uint8_t  kSortKeyDraw1DepthShift     = kSortKeyDrawTypeBitShift - BGFX_CONFIG_SORT_KEY_NUM_BITS_DEPTH;
	constexpr uint64_t kSortKeyDraw1DepthMask      = ( (uint64_t(1)<<BGFX_CONFIG_SORT_KEY_NUM_BITS_DEPTH)-1)<<kSortKeyDraw1DepthShift;

	constexpr uint8_t  kSortKeyDraw1BlendShift     = kSortKeyDraw1DepthShift - kSortKeyTransNumBits;
	constexpr uint64_t kSortKeyDraw1BlendMask      = uint64_t(0x3)<<kSortKeyDraw1BlendShift;

	constexpr uint8_t  kSortKeyDraw1ProgramShift   = kSortKeyDraw1BlendShift - BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM;
	constexpr uint64_t kSortKeyDraw1ProgramMask    = uint64_t(BGFX_CONFIG_MAX_PROGRAMS-1)<<kSortKeyDraw1ProgramShift;

	//
	constexpr uint8_t  kSortKeyDraw2SeqShift       = kSortKeyDrawTypeBitShift - BGFX_CONFIG_SORT_KEY_NUM_BITS_SEQ;
	constexpr uint64_t kSortKeyDraw2SeqMask        = ( (uint64_t(1)<<BGFX_CONFIG_SORT_KEY_NUM_BITS_SEQ)-1)<<kSortKeyDraw2SeqShift;

	constexpr uint8_t  kSortKeyDraw2BlendShift     = kSortKeyDraw2SeqShift - kSortKeyTransNumBits;
	constexpr uint64_t kSortKeyDraw2BlendMask      = uint64_t(0x3)<<kSortKeyDraw2BlendShift;

	constexpr uint8_t  kSortKeyDraw2ProgramShift   = kSortKeyDraw2BlendShift - BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM;
	constexpr uint64_t kSortKeyDraw2ProgramMask    = uint64_t(BGFX_CONFIG_MAX_PROGRAMS-1)<<kSortKeyDraw2ProgramShift;

	//
	constexpr uint8_t  kSortKeyComputeSeqShift     = kSortKeyDrawBitShift - BGFX_CONFIG_SORT_KEY_NUM_BITS_SEQ;
	constexpr uint64_t kSortKeyComputeSeqMask      = ( (uint64_t(1)<<BGFX_CONFIG_SORT_KEY_NUM_BITS_SEQ)-1)<<kSortKeyComputeSeqShift;

	constexpr uint8_t  kSortKeyComputeProgramShift = kSortKeyComputeSeqShift - BGFX_CONFIG_SORT_KEY_NUM_BITS_PROGRAM;
	constexpr uint64_t kSortKeyComputeProgramMask  = uint64_t(BGFX_CONFIG_MAX_PROGRAMS-1)<<kSortKeyComputeProgramShift;

	BX_STATIC_ASSERT(BGFX_CONFIG_MAX_VIEWS <= (1<<kSortKeyViewNumBits) );
	BX_STATIC_ASSERT( (BGFX_CONFIG_MAX_PROGRAMS & (BGFX_CONFIG_MAX_PROGRAMS-1) ) == 0); // Must be power of 2.
	BX_STATIC_ASSERT( (0 // Render key mask shouldn't overlap.
		| kSortKeyViewMask
		| kSortKeyDrawBit
		| kSortKeyDrawTypeMask
		| kSortKeyDraw0BlendMask
		| kSortKeyDraw0ProgramMask
		| kSortKeyDraw0DepthMask
		) == (0
		^ kSortKeyViewMask
		^ kSortKeyDrawBit
		^ kSortKeyDrawTypeMask
		^ kSortKeyDraw0BlendMask
		^ kSortKeyDraw0ProgramMask
		^ kSortKeyDraw0DepthMask
		) );
	BX_STATIC_ASSERT( (0 // Render key mask shouldn't overlap.
		| kSortKeyViewMask
		| kSortKeyDrawBit
		| kSortKeyDrawTypeMask
		| kSortKeyDraw1DepthMask
		| kSortKeyDraw1BlendMask
		| kSortKeyDraw1ProgramMask
		) == (0
		^ kSortKeyViewMask
		^ kSortKeyDrawBit
		^ kSortKeyDrawTypeMask
		^ kSortKeyDraw1DepthMask
		^ kSortKeyDraw1BlendMask
		^ kSortKeyDraw1ProgramMask
		) );
	BX_STATIC_ASSERT( (0 // Render key mask shouldn't overlap.
		| kSortKeyViewMask
		| kSortKeyDrawBit
		| kSortKeyDrawTypeMask
		| kSortKeyDraw2SeqMask
		| kSortKeyDraw2BlendMask
		| kSortKeyDraw2ProgramMask
		) == (0
		^ kSortKeyViewMask
		^ kSortKeyDrawBit
		^ kSortKeyDrawTypeMask
		^ kSortKeyDraw2SeqMask
		^ kSortKeyDraw2BlendMask
		^ kSortKeyDraw2ProgramMask
		) );
	BX_STATIC_ASSERT( (0 // Compute key mask shouldn't overlap.
		| kSortKeyViewMask
		| kSortKeyDrawBit
		| kSortKeyComputeSeqShift
		| kSortKeyComputeProgramMask
		) == (0
		^ kSortKeyViewMask
		^ kSortKeyDrawBit
		^ kSortKeyComputeSeqShift
		^ kSortKeyComputeProgramMask
		) );

	// |               3               2               1               0|
	// |fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210| Common
	// |vvvvvvvvd                                                       |
	// |       ^^                                                       |
	// |       ||                                                       |
	// |  view-+|                                                       |
	// |        +-draw                                                  |
	// |----------------------------------------------------------------| Draw Key 0 - Sort by program
	// |        |kkttpppppppppdddddddddddddddddddddddddddddddd          |
	// |        |   ^        ^                               ^          |
	// |        |   |        |                               |          |
	// |        |   +-blend  +-program                 depth-+          |
	// |        |                                                       |
	// |----------------------------------------------------------------| Draw Key 1 - Sort by depth
	// |        |kkddddddddddddddddddddddddddddddddttppppppppp          |
	// |        |                                ^^ ^        ^          |
	// |        |                                || +-trans  |          |
	// |        |                          depth-+   program-+          |
	// |        |                                                       |
	// |----------------------------------------------------------------| Draw Key 2 - Sequential
	// |        |kkssssssssssssssssssssttppppppppp                      |
	// |        |                     ^ ^        ^                      |
	// |        |                     | |        |                      |
	// |        |                 seq-+ +-trans  +-program              |
	// |        |                                                       |
	// |----------------------------------------------------------------| Compute Key
	// |        |ssssssssssssssssssssppppppppp                          |
	// |        |                   ^        ^                          |
	// |        |                   |        |                          |
	// |        |               seq-+        +-program                  |
	// |        |                                                       |
	// |--------+-------------------------------------------------------|
	//
	struct SortKey
	{
		enum Enum
		{
			SortProgram,
			SortDepth,
			SortSequence,
		};

		uint64_t encodeDraw(Enum _type)
		{
			switch (_type)
			{
			case SortProgram:
				{
					const uint64_t depth   = (uint64_t(m_depth      ) << kSortKeyDraw0DepthShift  ) & kSortKeyDraw0DepthMask;
					const uint64_t program = (uint64_t(m_program.idx) << kSortKeyDraw0ProgramShift) & kSortKeyDraw0ProgramMask;
					const uint64_t blend   = (uint64_t(m_blend      ) << kSortKeyDraw0BlendShift  ) & kSortKeyDraw0BlendMask;
					const uint64_t view    = (uint64_t(m_view       ) << kSortKeyViewBitShift     ) & kSortKeyViewMask;
					const uint64_t key     = view|kSortKeyDrawBit|kSortKeyDrawTypeProgram|blend|program|depth;

					return key;
				}
				break;

			case SortDepth:
				{
					const uint64_t depth   = (uint64_t(m_depth      ) << kSortKeyDraw1DepthShift  ) & kSortKeyDraw1DepthMask;
					const uint64_t program = (uint64_t(m_program.idx) << kSortKeyDraw1ProgramShift) & kSortKeyDraw1ProgramMask;
					const uint64_t blend   = (uint64_t(m_blend      ) << kSortKeyDraw1BlendShift) & kSortKeyDraw1BlendMask;
					const uint64_t view    = (uint64_t(m_view       ) << kSortKeyViewBitShift     ) & kSortKeyViewMask;
					const uint64_t key     = view|kSortKeyDrawBit|kSortKeyDrawTypeDepth|depth|blend|program;
					return key;
				}
				break;

			case SortSequence:
				{
					const uint64_t seq     = (uint64_t(m_seq        ) << kSortKeyDraw2SeqShift    ) & kSortKeyDraw2SeqMask;
					const uint64_t program = (uint64_t(m_program.idx) << kSortKeyDraw2ProgramShift) & kSortKeyDraw2ProgramMask;
					const uint64_t blend   = (uint64_t(m_blend      ) << kSortKeyDraw2BlendShift  ) & kSortKeyDraw2BlendMask;
					const uint64_t view    = (uint64_t(m_view       ) << kSortKeyViewBitShift     ) & kSortKeyViewMask;
					const uint64_t key     = view|kSortKeyDrawBit|kSortKeyDrawTypeSequence|seq|blend|program;

					BX_ASSERT(seq == (uint64_t(m_seq) << kSortKeyDraw2SeqShift)
						, "SortKey error, sequence is truncated (m_seq: %d)."
						, m_seq
						);

					return key;
				}
				break;
			}

			BX_ASSERT(false, "You should not be here.");
			return 0;
		}

		uint64_t encodeCompute()
		{
			const uint64_t program = (uint64_t(m_program.idx) << kSortKeyComputeProgramShift) & kSortKeyComputeProgramMask;
			const uint64_t seq     = (uint64_t(m_seq        ) << kSortKeyComputeSeqShift    ) & kSortKeyComputeSeqMask;
			const uint64_t view    = (uint64_t(m_view       ) << kSortKeyViewBitShift       ) & kSortKeyViewMask;
			const uint64_t key     = program|seq|view;

			BX_ASSERT(seq == (uint64_t(m_seq) << kSortKeyComputeSeqShift)
				, "SortKey error, sequence is truncated (m_seq: %d)."
				, m_seq
				);

			return key;
		}

		/// Returns true if item is compute command.
		bool decode(uint64_t _key, ViewId _viewRemap[BGFX_CONFIG_MAX_VIEWS])
		{
			m_view = _viewRemap[(_key & kSortKeyViewMask) >> kSortKeyViewBitShift];

			if (_key & kSortKeyDrawBit)
			{
				uint64_t type = _key & kSortKeyDrawTypeMask;

				if (type == kSortKeyDrawTypeDepth)
				{
					m_program.idx = uint16_t( (_key & kSortKeyDraw1ProgramMask) >> kSortKeyDraw1ProgramShift);
					return false;
				}

				if (type == kSortKeyDrawTypeSequence)
				{
					m_program.idx = uint16_t( (_key & kSortKeyDraw2ProgramMask) >> kSortKeyDraw2ProgramShift);
					return false;
				}

				m_program.idx = uint16_t( (_key & kSortKeyDraw0ProgramMask) >> kSortKeyDraw0ProgramShift);
				return false; // draw
			}

			m_program.idx = uint16_t( (_key & kSortKeyComputeProgramMask) >> kSortKeyComputeProgramShift);
			return true; // compute
		}

		static ViewId decodeView(uint64_t _key)
		{
			return ViewId( (_key & kSortKeyViewMask) >> kSortKeyViewBitShift);
		}

		static uint64_t remapView(uint64_t _key, ViewId _viewRemap[BGFX_CONFIG_MAX_VIEWS])
		{
			const ViewId   oldView = decodeView(_key);
			const uint64_t view    = uint64_t(_viewRemap[oldView]) << kSortKeyViewBitShift;
			const uint64_t key     = (_key & ~kSortKeyViewMask) | view;
			return key;
		}

		void reset()
		{
			m_depth   = 0;
			m_seq     = 0;
			m_program = {0};
			m_view    = 0;
			m_blend   = 0;
		}

		uint32_t      m_depth;
		uint32_t      m_seq;
		ProgramHandle m_program;
		ViewId        m_view;
		uint8_t       m_blend;
	};
#undef SORT_KEY_RENDER_DRAW

	struct BlitKey
	{
		uint32_t encode()
		{
			return 0
				| (uint32_t(m_view) << 24)
				|  uint32_t(m_item)
				;
		}

		void decode(uint32_t _key)
		{
			m_item = uint16_t(_key & UINT16_MAX);
			m_view =   ViewId(_key >> 24);
		}

		static uint32_t remapView(uint32_t _key, ViewId _viewRemap[BGFX_CONFIG_MAX_VIEWS])
		{
			const ViewId   oldView = ViewId(_key >> 24);
			const uint32_t view    = uint32_t(_viewRemap[oldView]) << 24;
			const uint32_t key     = (_key & ~UINT32_C(0xff000000) ) | view;
			return key;
		}

		uint16_t m_item;
		ViewId   m_view;
	};

	BX_ALIGN_DECL_16(struct) Srt
	{
		float rotate[4];
		float translate[3];
		float pad0;
		float scale[3];
		float pad1;
	};

	BX_ALIGN_DECL_16(struct) Matrix4
	{
		union
		{
			float val[16];
			bx::float4x4_t f4x4;
		} un;

		void setIdentity()
		{
			bx::memSet(un.val, 0, sizeof(un.val) );
			un.val[0] = un.val[5] = un.val[10] = un.val[15] = 1.0f;
		}
	};

	struct MatrixCache
	{
		MatrixCache()
			: m_num(1)
		{
			m_cache[0].setIdentity();
		}

		void reset()
		{
			m_num = 1;
		}

		uint32_t reserve(uint16_t* _num)
		{
			uint32_t num = *_num;
			uint32_t first = bx::atomicFetchAndAddsat<uint32_t>(&m_num, num, BGFX_CONFIG_MAX_MATRIX_CACHE - 1);
			BX_WARN(first+num < BGFX_CONFIG_MAX_MATRIX_CACHE, "Matrix cache overflow. %d (max: %d)", first+num, BGFX_CONFIG_MAX_MATRIX_CACHE);
			num = bx::min(num, BGFX_CONFIG_MAX_MATRIX_CACHE-1-first);
			*_num = (uint16_t)num;
			return first;
		}

		uint32_t add(const void* _mtx, uint16_t _num)
		{
			if (NULL != _mtx)
			{
				uint32_t first = reserve(&_num);
				bx::memCopy(&m_cache[first], _mtx, sizeof(Matrix4)*_num);
				return first;
			}

			return 0;
		}

		float* toPtr(uint32_t _cacheIdx)
		{
			BX_ASSERT(_cacheIdx < BGFX_CONFIG_MAX_MATRIX_CACHE, "Matrix cache out of bounds index %d (max: %d)"
				, _cacheIdx
				, BGFX_CONFIG_MAX_MATRIX_CACHE
				);
			return m_cache[_cacheIdx].un.val;
		}

		uint32_t fromPtr(const void* _ptr) const
		{
			return uint32_t( (const Matrix4*)_ptr - m_cache);
		}

		Matrix4 m_cache[BGFX_CONFIG_MAX_MATRIX_CACHE];
		uint32_t m_num;
	};

	struct RectCache
	{
		RectCache()
			: m_num(0)
		{
		}

		void reset()
		{
			m_num = 0;
		}

		uint32_t add(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
		{
			const uint32_t first = bx::atomicFetchAndAddsat<uint32_t>(&m_num, 1, BGFX_CONFIG_MAX_RECT_CACHE-1);
			BX_ASSERT(first+1 < BGFX_CONFIG_MAX_RECT_CACHE, "Rect cache overflow. %d (max: %d)", first, BGFX_CONFIG_MAX_RECT_CACHE);

			Rect& rect = m_cache[first];

			rect.m_x = _x;
			rect.m_y = _y;
			rect.m_width = _width;
			rect.m_height = _height;

			return first;
		}

		Rect     m_cache[BGFX_CONFIG_MAX_RECT_CACHE];
		uint32_t m_num;
	};

	constexpr uint8_t  kConstantOpcodeTypeShift = 27;
	constexpr uint32_t kConstantOpcodeTypeMask  = UINT32_C(0xf8000000);
	constexpr uint8_t  kConstantOpcodeLocShift  = 11;
	constexpr uint32_t kConstantOpcodeLocMask   = UINT32_C(0x07fff800);
	constexpr uint8_t  kConstantOpcodeNumShift  = 1;
	constexpr uint32_t kConstantOpcodeNumMask   = UINT32_C(0x000007fe);
	constexpr uint8_t  kConstantOpcodeCopyShift = 0;
	constexpr uint32_t kConstantOpcodeCopyMask  = UINT32_C(0x00000001);

	constexpr uint8_t kUniformFragmentBit  = 0x10;
	constexpr uint8_t kUniformSamplerBit   = 0x20;
	constexpr uint8_t kUniformReadOnlyBit  = 0x40;
	constexpr uint8_t kUniformCompareBit   = 0x80;
	constexpr uint8_t kUniformMask = 0
		| kUniformFragmentBit
		| kUniformSamplerBit
		| kUniformReadOnlyBit
		| kUniformCompareBit
		;

	class UniformBuffer
	{
	public:
		static UniformBuffer* create(uint32_t _size = 1<<20)
		{
			const uint32_t structSize = sizeof(UniformBuffer)-sizeof(UniformBuffer::m_buffer);

			uint32_t size = bx::alignUp(_size, 16);
			void*    data = BX_ALLOC(g_allocator, size+structSize);
			return BX_PLACEMENT_NEW(data, UniformBuffer)(size);
		}

		static void destroy(UniformBuffer* _uniformBuffer)
		{
			_uniformBuffer->~UniformBuffer();
			BX_FREE(g_allocator, _uniformBuffer);
		}

		static void update(UniformBuffer** _uniformBuffer, uint32_t _threshold = 64<<10, uint32_t _grow = 1<<20)
		{
			UniformBuffer* uniformBuffer = *_uniformBuffer;
			if (_threshold >= uniformBuffer->m_size - uniformBuffer->m_pos)
			{
				const uint32_t structSize = sizeof(UniformBuffer)-sizeof(UniformBuffer::m_buffer);
				uint32_t size = bx::alignUp(uniformBuffer->m_size + _grow, 16);
				void*    data = BX_REALLOC(g_allocator, uniformBuffer, size+structSize);
				uniformBuffer = reinterpret_cast<UniformBuffer*>(data);
				uniformBuffer->m_size = size;

				*_uniformBuffer = uniformBuffer;
			}
		}

		static uint32_t encodeOpcode(UniformType::Enum _type, uint16_t _loc, uint16_t _num, uint16_t _copy)
		{
			const uint32_t type = _type << kConstantOpcodeTypeShift;
			const uint32_t loc  = _loc  << kConstantOpcodeLocShift;
			const uint32_t num  = _num  << kConstantOpcodeNumShift;
			const uint32_t copy = _copy << kConstantOpcodeCopyShift;
			return type|loc|num|copy;
		}

		static void decodeOpcode(uint32_t _opcode, UniformType::Enum& _type, uint16_t& _loc, uint16_t& _num, uint16_t& _copy)
		{
			const uint32_t type = (_opcode&kConstantOpcodeTypeMask) >> kConstantOpcodeTypeShift;
			const uint32_t loc  = (_opcode&kConstantOpcodeLocMask ) >> kConstantOpcodeLocShift;
			const uint32_t num  = (_opcode&kConstantOpcodeNumMask ) >> kConstantOpcodeNumShift;
			const uint32_t copy = (_opcode&kConstantOpcodeCopyMask); // >> kConstantOpcodeCopyShift;

			_type = (UniformType::Enum)(type);
			_copy = (uint16_t)copy;
			_num  = (uint16_t)num;
			_loc  = (uint16_t)loc;
		}

		void write(const void* _data, uint32_t _size)
		{
			BX_ASSERT(m_pos + _size < m_size, "Write would go out of bounds. pos %d + size %d > max size: %d).", m_pos, _size, m_size);

			if (m_pos + _size < m_size)
			{
				bx::memCopy(&m_buffer[m_pos], _data, _size);
				m_pos += _size;
			}
		}

		void write(uint32_t _value)
		{
			write(&_value, sizeof(uint32_t) );
		}

		const char* read(uint32_t _size)
		{
			BX_ASSERT(m_pos < m_size, "Out of bounds %d (size: %d).", m_pos, m_size);
			const char* result = &m_buffer[m_pos];
			m_pos += _size;
			return result;
		}

		uint32_t read()
		{
			uint32_t result;
			bx::memCopy(&result, read(sizeof(uint32_t) ), sizeof(uint32_t) );
			return result;
		}

		bool isEmpty() const
		{
			return 0 == m_pos;
		}

		uint32_t getPos() const
		{
			return m_pos;
		}

		void reset(uint32_t _pos = 0)
		{
			m_pos = _pos;
		}

		void finish()
		{
			write(UniformType::End);
			m_pos = 0;
		}

		void writeUniform(UniformType::Enum _type, uint16_t _loc, const void* _value, uint16_t _num = 1);
		void writeUniformHandle(UniformType::Enum _type, uint16_t _loc, UniformHandle _handle, uint16_t _num = 1);
		void writeMarker(const char* _marker);

	private:
		UniformBuffer(uint32_t _size)
			: m_size(_size)
			, m_pos(0)
		{
			finish();
		}

		~UniformBuffer()
		{
		}

		uint32_t m_size;
		uint32_t m_pos;
		char     m_buffer[256<<20];
	};

	struct UniformRegInfo
	{
		UniformHandle m_handle;
	};

	class UniformRegistry
	{
	public:
		UniformRegistry()
		{
		}

		~UniformRegistry()
		{
		}

		const UniformRegInfo* find(const char* _name) const
		{
			uint16_t handle = m_uniforms.find(bx::hash<bx::HashMurmur2A>(_name) );
			if (kInvalidHandle != handle)
			{
				return &m_info[handle];
			}

			return NULL;
		}

		const UniformRegInfo& add(UniformHandle _handle, const char* _name)
		{
			BX_ASSERT(isValid(_handle), "Uniform handle is invalid (name: %s)!", _name);
			const uint32_t key = bx::hash<bx::HashMurmur2A>(_name);
			m_uniforms.removeByKey(key);
			m_uniforms.insert(key, _handle.idx);

			UniformRegInfo& info = m_info[_handle.idx];
			info.m_handle = _handle;

			return info;
		}

		void remove(UniformHandle _handle)
		{
			m_uniforms.removeByHandle(_handle.idx);
		}

	private:
		typedef bx::HandleHashMapT<BGFX_CONFIG_MAX_UNIFORMS*2> UniformHashMap;
		UniformHashMap m_uniforms;
		UniformRegInfo m_info[BGFX_CONFIG_MAX_UNIFORMS];
	};

	struct Binding
	{
		enum Enum
		{
			Image,
			IndexBuffer,
			VertexBuffer,
			Texture,

			Count
		};

		uint32_t m_samplerFlags;
		uint16_t m_idx;
		uint8_t  m_type;
		uint8_t  m_format;
		uint8_t  m_access;
		uint8_t  m_mip;
	};

	struct Stream
	{
		void clear()
		{
			m_startVertex      = 0;
			m_handle.idx       = kInvalidHandle;
			m_layoutHandle.idx = kInvalidHandle;
		}

		uint32_t           m_startVertex;
		VertexBufferHandle m_handle;
		VertexLayoutHandle m_layoutHandle;
	};

	BX_ALIGN_DECL_CACHE_LINE(struct) RenderBind
	{
		void clear(uint8_t _flags = BGFX_DISCARD_ALL)
		{
			if (0 != (_flags & BGFX_DISCARD_BINDINGS) )
			{
				for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++ii)
				{
					Binding& bind = m_bind[ii];
					bind.m_idx = kInvalidHandle;
					bind.m_type = 0;
					bind.m_samplerFlags = 0;
				}
			}
		};

		Binding m_bind[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
	};

	BX_ALIGN_DECL_CACHE_LINE(struct) RenderDraw
	{
		void clear(uint8_t _flags = BGFX_DISCARD_ALL)
		{
			if (0 != (_flags & BGFX_DISCARD_STATE) )
			{
				m_uniformBegin  = 0;
				m_uniformEnd    = 0;
				m_uniformIdx    = UINT8_MAX;

				m_stateFlags    = BGFX_STATE_DEFAULT;
				m_stencil       = packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT);
				m_rgba          = 0;
				m_scissor       = UINT16_MAX;
			}

			if (0 != (_flags & BGFX_DISCARD_TRANSFORM) )
			{
				m_startMatrix = 0;
				m_numMatrices = 1;
			}

			if (0 != (_flags & BGFX_DISCARD_INSTANCE_DATA) )
			{
				m_instanceDataOffset = 0;
				m_instanceDataStride = 0;
				m_numInstances       = 1;
				m_instanceDataBuffer.idx = kInvalidHandle;
			}

			if (0 != (_flags & BGFX_DISCARD_VERTEX_STREAMS) )
			{
				m_numVertices = UINT32_MAX;
				m_streamMask  = 0;
				m_stream[0].clear();
			}

			if (0 != (_flags & BGFX_DISCARD_INDEX_BUFFER) )
			{
				m_startIndex      = 0;
				m_numIndices      = UINT32_MAX;
				m_indexBuffer.idx = kInvalidHandle;
				m_submitFlags     = 0;
			}
			else
			{
				m_submitFlags = isIndex16() ? 0 : BGFX_SUBMIT_INTERNAL_INDEX32;
			}

			m_startIndirect = 0;
			m_numIndirect   = UINT16_MAX;
			m_indirectBuffer.idx = kInvalidHandle;
			m_occlusionQuery.idx = kInvalidHandle;
		}

		bool setStreamBit(uint8_t _stream, VertexBufferHandle _handle)
		{
			const uint8_t bit  = 1<<_stream;
			const uint8_t mask = m_streamMask & ~bit;
			const uint8_t tmp  = isValid(_handle) ? bit : 0;
			m_streamMask = mask | tmp;
			return 0 != tmp;
		}

		bool isIndex16() const
		{
			return 0 == (m_submitFlags & BGFX_SUBMIT_INTERNAL_INDEX32);
		}

		Stream   m_stream[BGFX_CONFIG_MAX_VERTEX_STREAMS];
		uint64_t m_stateFlags;
		uint64_t m_stencil;
		uint32_t m_rgba;
		uint32_t m_uniformBegin;
		uint32_t m_uniformEnd;
		uint32_t m_startMatrix;
		uint32_t m_startIndex;
		uint32_t m_numIndices;
		uint32_t m_numVertices;
		uint32_t m_instanceDataOffset;
		uint32_t m_numInstances;
		uint16_t m_instanceDataStride;
		uint16_t m_startIndirect;
		uint16_t m_numIndirect;
		uint16_t m_numMatrices;
		uint16_t m_scissor;
		uint8_t  m_submitFlags;
		uint8_t  m_streamMask;
		uint8_t  m_uniformIdx;

		IndexBufferHandle    m_indexBuffer;
		VertexBufferHandle   m_instanceDataBuffer;
		IndirectBufferHandle m_indirectBuffer;
		OcclusionQueryHandle m_occlusionQuery;
	};

	BX_ALIGN_DECL_CACHE_LINE(struct) RenderCompute
	{
		void clear(uint8_t _flags)
		{
			if (0 != (_flags & BGFX_DISCARD_STATE) )
			{
				m_uniformBegin = 0;
				m_uniformEnd   = 0;
				m_uniformIdx   = UINT8_MAX;
			}

			if (0 != (_flags & BGFX_DISCARD_TRANSFORM) )
			{
				m_startMatrix = 0;
				m_numMatrices = 0;
			}

			m_numX               = 0;
			m_numY               = 0;
			m_numZ               = 0;
			m_submitFlags        = 0;
			m_indirectBuffer.idx = kInvalidHandle;
			m_startIndirect      = 0;
			m_numIndirect        = UINT16_MAX;
		}

		uint32_t m_uniformBegin;
		uint32_t m_uniformEnd;
		uint32_t m_startMatrix;
		IndirectBufferHandle m_indirectBuffer;

		uint32_t m_numX;
		uint32_t m_numY;
		uint32_t m_numZ;
		uint16_t m_startIndirect;
		uint16_t m_numIndirect;
		uint16_t m_numMatrices;
		uint8_t  m_submitFlags;
		uint8_t  m_uniformIdx;
	};

	union RenderItem
	{
		RenderDraw    draw;
		RenderCompute compute;
	};

	BX_ALIGN_DECL_CACHE_LINE(struct) BlitItem
	{
		uint16_t m_srcX;
		uint16_t m_srcY;
		uint16_t m_srcZ;
		uint16_t m_dstX;
		uint16_t m_dstY;
		uint16_t m_dstZ;
		uint16_t m_width;
		uint16_t m_height;
		uint16_t m_depth;
		uint8_t  m_srcMip;
		uint8_t  m_dstMip;
		TextureHandle m_src;
		TextureHandle m_dst;
	};

	struct IndexBuffer
	{
		String   m_name;
		uint32_t m_size;
		uint16_t m_flags;
	};

	struct VertexBuffer
	{
		String   m_name;
		uint32_t m_size;
		uint16_t m_stride;
	};

	struct DynamicIndexBuffer
	{
		IndexBufferHandle m_handle;
		uint32_t m_offset;
		uint32_t m_size;
		uint32_t m_startIndex;
		uint16_t m_flags;
	};

	struct DynamicVertexBuffer
	{
		VertexBufferHandle m_handle;
		uint32_t m_offset;
		uint32_t m_size;
		uint32_t m_startVertex;
		uint32_t m_numVertices;
		uint16_t m_stride;
		VertexLayoutHandle m_layoutHandle;
		uint16_t m_flags;
	};

	struct ShaderRef
	{
		UniformHandle* m_uniforms;
		String   m_name;
		uint32_t m_hashIn;
		uint32_t m_hashOut;
		uint16_t m_num;
		int16_t  m_refCount;
	};

	struct ProgramRef
	{
		ShaderHandle m_vsh;
		ShaderHandle m_fsh;
		int16_t      m_refCount;
	};

	struct UniformRef
	{
		String            m_name;
		UniformType::Enum m_type;
		uint16_t          m_num;
		int16_t           m_refCount;
	};

	struct TextureRef
	{
		void init(
			  BackbufferRatio::Enum _ratio
			, uint16_t _width
			, uint16_t _height
			, uint16_t _depth
			, TextureFormat::Enum _format
			, uint32_t _storageSize
			, uint8_t _numMips
			, uint16_t _numLayers
			, bool _ptrPending
			, bool _immutable
			, bool _cubeMap
			, uint64_t _flags
			)
		{
			m_ptr         = _ptrPending ? (void*)UINTPTR_MAX : NULL;
			m_storageSize = _storageSize;
			m_refCount    = 1;
			m_bbRatio     = uint8_t(_ratio);
			m_width       = _width;
			m_height      = _height;
			m_depth       = _depth;
			m_format      = uint8_t(_format);
			m_numSamples  = 1 << bx::uint32_satsub((_flags & BGFX_TEXTURE_RT_MSAA_MASK) >> BGFX_TEXTURE_RT_MSAA_SHIFT, 1);
			m_numMips     = _numMips;
			m_numLayers   = _numLayers;
			m_owned       = false;
			m_immutable   = _immutable;
			m_cubeMap     = _cubeMap;
			m_flags       = _flags;
		}

		bool isRt() const
		{
			return 0 != (m_flags & BGFX_TEXTURE_RT_MASK);
		}

		bool isReadBack() const
		{
			return 0 != (m_flags&BGFX_TEXTURE_READ_BACK);
		}

		bool isCubeMap() const
		{
			return m_cubeMap;
		}

		bool is3D() const
		{
			return 0 < m_depth;
		}

		String   m_name;
		void*    m_ptr;
		uint64_t m_flags;
		uint32_t m_storageSize;
		int16_t  m_refCount;
		uint8_t  m_bbRatio;
		uint16_t m_width;
		uint16_t m_height;
		uint16_t m_depth;
		uint8_t  m_format;
		uint8_t  m_numSamples;
		uint8_t  m_numMips;
		uint16_t m_numLayers;
		bool     m_owned;
		bool     m_immutable;
		bool     m_cubeMap;
	};

	struct FrameBufferRef
	{
		String m_name;
		uint16_t m_width;
		uint16_t m_height;

		union un
		{
			TextureHandle m_th[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
			void* m_nwh;
		} un;

		bool m_window;
	};

	BX_ALIGN_DECL_CACHE_LINE(struct) View
	{
		void reset()
		{
			setRect(0, 0, 1, 1);
			setScissor(0, 0, 0, 0);
			setClear(BGFX_CLEAR_NONE, 0, 0.0f, 0);
			setMode(ViewMode::Default);
			setFrameBuffer(BGFX_INVALID_HANDLE);
			setTransform(NULL, NULL);
		}

		void setRect(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
		{
			m_rect.m_x      = uint16_t(bx::max<int16_t>(int16_t(_x), 0) );
			m_rect.m_y      = uint16_t(bx::max<int16_t>(int16_t(_y), 0) );
			m_rect.m_width  = bx::max<uint16_t>(_width,  1);
			m_rect.m_height = bx::max<uint16_t>(_height, 1);
		}

		void setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
		{
			m_scissor.m_x = _x;
			m_scissor.m_y = _y;
			m_scissor.m_width  = _width;
			m_scissor.m_height = _height;
		}

		void setClear(uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
		{
			m_clear.set(_flags, _rgba, _depth, _stencil);
		}

		void setClear(uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7)
		{
			m_clear.set(_flags, _depth, _stencil, _0, _1, _2, _3, _4, _5, _6, _7);
		}

		void setMode(ViewMode::Enum _mode)
		{
			m_mode = uint8_t(_mode);
		}

		void setFrameBuffer(FrameBufferHandle _handle)
		{
			m_fbh = _handle;
		}

		void setTransform(const void* _view, const void* _proj)
		{
			if (NULL != _view)
			{
				bx::memCopy(m_view.un.val, _view, sizeof(Matrix4) );
			}
			else
			{
				m_view.setIdentity();
			}

			if (NULL != _proj)
			{
				bx::memCopy(m_proj.un.val, _proj, sizeof(Matrix4) );
			}
			else
			{
				m_proj.setIdentity();
			}
		}

		Clear   m_clear;
		Rect    m_rect;
		Rect    m_scissor;
		Matrix4 m_view;
		Matrix4 m_proj;
		FrameBufferHandle m_fbh;
		uint8_t m_mode;
	};

	struct FrameCache
	{
		void reset()
		{
			m_matrixCache.reset();
			m_rectCache.reset();
		}

		bool isZeroArea(const Rect& _rect, uint16_t _scissor) const
		{
			if (UINT16_MAX != _scissor)
			{
				Rect scissorRect;
				scissorRect.setIntersect(_rect, m_rectCache.m_cache[_scissor]);
				return scissorRect.isZeroArea();
			}

			return false;
		}

		MatrixCache m_matrixCache;
		RectCache m_rectCache;
	};

	struct ScreenShot
	{
		bx::FilePath filePath;
		FrameBufferHandle handle;
	};

	BX_ALIGN_DECL_CACHE_LINE(struct) Frame
	{
		Frame()
			: m_waitSubmit(0)
			, m_waitRender(0)
			, m_capture(false)
		{
			SortKey term;
			term.reset();
			term.m_program = BGFX_INVALID_HANDLE;
			m_sortKeys[BGFX_CONFIG_MAX_DRAW_CALLS]   = term.encodeDraw(SortKey::SortProgram);
			m_sortValues[BGFX_CONFIG_MAX_DRAW_CALLS] = BGFX_CONFIG_MAX_DRAW_CALLS;
			bx::memSet(m_occlusion, 0xff, sizeof(m_occlusion) );

			m_perfStats.viewStats = m_viewStats;
		}

		~Frame()
		{
		}

		void create(uint32_t _minResourceCbSize)
		{
			m_cmdPre.init(_minResourceCbSize);
			m_cmdPost.init(_minResourceCbSize);

			{
				const uint32_t num = g_caps.limits.maxEncoders;

				m_uniformBuffer = (UniformBuffer**)BX_ALLOC(g_allocator, sizeof(UniformBuffer*)*num);

				for (uint32_t ii = 0; ii < num; ++ii)
				{
					m_uniformBuffer[ii] = UniformBuffer::create();
				}
			}

			reset();
			start();
			m_textVideoMem = BX_NEW(g_allocator, TextVideoMem);
		}

		void destroy()
		{
			for (uint32_t ii = 0, num = g_caps.limits.maxEncoders; ii < num; ++ii)
			{
				UniformBuffer::destroy(m_uniformBuffer[ii]);
			}

			BX_FREE(g_allocator, m_uniformBuffer);
			BX_DELETE(g_allocator, m_textVideoMem);
		}

		void reset()
		{
			start();
			finish();
			resetFreeHandles();
		}

		void start()
		{
			m_perfStats.transientVbUsed = m_vboffset;
			m_perfStats.transientIbUsed = m_iboffset;

			m_frameCache.reset();
			m_numRenderItems = 0;
			m_numBlitItems   = 0;
			m_iboffset = 0;
			m_vboffset = 0;
			m_cmdPre.start();
			m_cmdPost.start();
			m_capture = false;
			m_numScreenShots = 0;
		}

		void finish()
		{
			m_cmdPre.finish();
			m_cmdPost.finish();
		}

		void sort();

		uint32_t getAvailTransientIndexBuffer(uint32_t _num, uint16_t _indexSize)
		{
			const uint32_t offset = bx::strideAlign(m_iboffset, _indexSize);
			uint32_t iboffset = offset + _num*_indexSize;
			iboffset = bx::min<uint32_t>(iboffset, g_caps.limits.transientIbSize);
			const uint32_t num = (iboffset-offset)/_indexSize;
			return num;
		}

		uint32_t allocTransientIndexBuffer(uint32_t& _num, uint16_t _indexSize)
		{
			uint32_t offset = bx::strideAlign(m_iboffset, _indexSize);
			uint32_t num    = getAvailTransientIndexBuffer(_num, _indexSize);
			m_iboffset = offset + num*_indexSize;
			_num = num;

			return offset;
		}

		uint32_t getAvailTransientVertexBuffer(uint32_t _num, uint16_t _stride)
		{
			uint32_t offset   = bx::strideAlign(m_vboffset, _stride);
			uint32_t vboffset = offset + _num * _stride;
			vboffset = bx::min<uint32_t>(vboffset, g_caps.limits.transientVbSize);
			uint32_t num = (vboffset-offset)/_stride;
			return num;
		}

		uint32_t allocTransientVertexBuffer(uint32_t& _num, uint16_t _stride)
		{
			uint32_t offset = bx::strideAlign(m_vboffset, _stride);
			uint32_t num    = getAvailTransientVertexBuffer(_num, _stride);
			m_vboffset = offset + num * _stride;
			_num = num;

			return offset;
		}

		bool free(IndexBufferHandle _handle)
		{
			return m_freeIndexBuffer.queue(_handle);
		}

		bool free(VertexLayoutHandle _handle)
		{
			return m_freeVertexLayout.queue(_handle);
		}

		bool free(VertexBufferHandle _handle)
		{
			return m_freeVertexBuffer.queue(_handle);
		}

		bool free(ShaderHandle _handle)
		{
			return m_freeShader.queue(_handle);
		}

		bool free(ProgramHandle _handle)
		{
			return m_freeProgram.queue(_handle);
		}

		bool free(TextureHandle _handle)
		{
			return m_freeTexture.queue(_handle);
		}

		bool free(FrameBufferHandle _handle)
		{
			return m_freeFrameBuffer.queue(_handle);
		}

		bool free(UniformHandle _handle)
		{
			return m_freeUniform.queue(_handle);
		}

		void resetFreeHandles()
		{
			m_freeIndexBuffer.reset();
			m_freeVertexLayout.reset();
			m_freeVertexBuffer.reset();
			m_freeShader.reset();
			m_freeProgram.reset();
			m_freeTexture.reset();
			m_freeFrameBuffer.reset();
			m_freeUniform.reset();
		}

		ViewId m_viewRemap[BGFX_CONFIG_MAX_VIEWS];
		float m_colorPalette[BGFX_CONFIG_MAX_COLOR_PALETTE][4];

		View m_view[BGFX_CONFIG_MAX_VIEWS];

		int32_t m_occlusion[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];

		uint64_t m_sortKeys[BGFX_CONFIG_MAX_DRAW_CALLS+1];
		RenderItemCount m_sortValues[BGFX_CONFIG_MAX_DRAW_CALLS+1];
		RenderItem m_renderItem[BGFX_CONFIG_MAX_DRAW_CALLS+1];
		RenderBind m_renderItemBind[BGFX_CONFIG_MAX_DRAW_CALLS + 1];

		uint32_t m_blitKeys[BGFX_CONFIG_MAX_BLIT_ITEMS+1];
		BlitItem m_blitItem[BGFX_CONFIG_MAX_BLIT_ITEMS+1];

		FrameCache m_frameCache;
		UniformBuffer** m_uniformBuffer;

		uint32_t m_numRenderItems;
		uint16_t m_numBlitItems;

		uint32_t m_iboffset;
		uint32_t m_vboffset;
		TransientIndexBuffer* m_transientIb;
		TransientVertexBuffer* m_transientVb;

		Resolution m_resolution;
		uint32_t m_debug;

		ScreenShot m_screenShot[BGFX_CONFIG_MAX_SCREENSHOTS];
		uint8_t m_numScreenShots;

		CommandBuffer m_cmdPre;
		CommandBuffer m_cmdPost;

		template<typename Ty, uint32_t Max>
		struct FreeHandle
		{
			FreeHandle()
				: m_num(0)
			{
			}

			bool isQueued(Ty _handle)
			{
				for (uint32_t ii = 0, num = m_num; ii < num; ++ii)
				{
					if (m_queue[ii].idx == _handle.idx)
					{
						return true;
					}
				}

				return false;
			}

			bool queue(Ty _handle)
			{
				if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
				{
					if (isQueued(_handle) )
					{
						return false;
					}
				}

				m_queue[m_num] = _handle;
				++m_num;

				return true;
			}

			void reset()
			{
				m_num = 0;
			}

			Ty get(uint16_t _idx) const
			{
				return m_queue[_idx];
			}

			uint16_t getNumQueued() const
			{
				return m_num;
			}

			Ty m_queue[Max];
			uint16_t m_num;
		};

		FreeHandle<IndexBufferHandle,  BGFX_CONFIG_MAX_INDEX_BUFFERS>  m_freeIndexBuffer;
		FreeHandle<VertexLayoutHandle, BGFX_CONFIG_MAX_VERTEX_LAYOUTS> m_freeVertexLayout;
		FreeHandle<VertexBufferHandle, BGFX_CONFIG_MAX_VERTEX_BUFFERS> m_freeVertexBuffer;
		FreeHandle<ShaderHandle,       BGFX_CONFIG_MAX_SHADERS>        m_freeShader;
		FreeHandle<ProgramHandle,      BGFX_CONFIG_MAX_PROGRAMS>       m_freeProgram;
		FreeHandle<TextureHandle,      BGFX_CONFIG_MAX_TEXTURES>       m_freeTexture;
		FreeHandle<FrameBufferHandle,  BGFX_CONFIG_MAX_FRAME_BUFFERS>  m_freeFrameBuffer;
		FreeHandle<UniformHandle,      BGFX_CONFIG_MAX_UNIFORMS>       m_freeUniform;

		TextVideoMem* m_textVideoMem;

		Stats     m_perfStats;
		ViewStats m_viewStats[BGFX_CONFIG_MAX_VIEWS];

		int64_t m_waitSubmit;
		int64_t m_waitRender;

		bool m_capture;
	};

	BX_ALIGN_DECL_CACHE_LINE(struct) EncoderImpl
	{
		EncoderImpl()
		{
			discard(BGFX_DISCARD_ALL);
		}

		void begin(Frame* _frame, uint8_t _idx)
		{
			m_frame = _frame;

			m_cpuTimeBegin = bx::getHPCounter();

			m_uniformIdx   = _idx;
			m_uniformBegin = 0;
			m_uniformEnd   = 0;

			UniformBuffer* uniformBuffer = m_frame->m_uniformBuffer[m_uniformIdx];
			uniformBuffer->reset();

			m_numSubmitted = 0;
			m_numDropped   = 0;
		}

		void end(bool _finalize)
		{
			if (_finalize)
			{
				UniformBuffer* uniformBuffer = m_frame->m_uniformBuffer[m_uniformIdx];
				uniformBuffer->finish();

				m_cpuTimeEnd = bx::getHPCounter();
			}

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_OCCLUSION) )
			{
				m_occlusionQuerySet.clear();
			}

			if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
			{
				m_uniformSet.clear();
			}
		}

		void setMarker(const char* _name)
		{
			UniformBuffer* uniformBuffer = m_frame->m_uniformBuffer[m_uniformIdx];
			uniformBuffer->writeMarker(_name);
		}

		void setUniform(UniformType::Enum _type, UniformHandle _handle, const void* _value, uint16_t _num)
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
			{
				BX_ASSERT(m_uniformSet.end() == m_uniformSet.find(_handle.idx)
					, "Uniform %d (%s) was already set for this draw call."
					, _handle.idx
					, getName(_handle)
					);
				m_uniformSet.insert(_handle.idx);
			}

			UniformBuffer::update(&m_frame->m_uniformBuffer[m_uniformIdx]);
			UniformBuffer* uniformBuffer = m_frame->m_uniformBuffer[m_uniformIdx];
			uniformBuffer->writeUniform(_type, _handle.idx, _value, _num);
		}

		void setState(uint64_t _state, uint32_t _rgba)
		{
			uint8_t blend = ( (_state&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT)&0xff;
			uint8_t alphaRef = ( (_state&BGFX_STATE_ALPHA_REF_MASK)>>BGFX_STATE_ALPHA_REF_SHIFT)&0xff;
			// transparency sort order table
			m_key.m_blend = "\x0\x2\x2\x3\x3\x2\x3\x2\x3\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2"[( (blend)&0xf) + (!!blend)] + !!alphaRef;
			m_draw.m_stateFlags = _state;
			m_draw.m_rgba = _rgba;
		}

		void setCondition(OcclusionQueryHandle _handle, bool _visible)
		{
			m_draw.m_occlusionQuery = _handle;
			m_draw.m_submitFlags   |= _visible ? BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE : 0;
		}

		void setStencil(uint32_t _fstencil, uint32_t _bstencil)
		{
			m_draw.m_stencil = packStencil(_fstencil, _bstencil);
		}

		uint16_t setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
		{
			uint16_t scissor = (uint16_t)m_frame->m_frameCache.m_rectCache.add(_x, _y, _width, _height);
			m_draw.m_scissor = scissor;
			return scissor;
		}

		void setScissor(uint16_t _cache)
		{
			m_draw.m_scissor = _cache;
		}

		uint32_t setTransform(const void* _mtx, uint16_t _num)
		{
			m_draw.m_startMatrix = m_frame->m_frameCache.m_matrixCache.add(_mtx, _num);
			m_draw.m_numMatrices = _num;

			return m_draw.m_startMatrix;
		}

		uint32_t allocTransform(Transform* _transform, uint16_t _num)
		{
			uint32_t first   = m_frame->m_frameCache.m_matrixCache.reserve(&_num);
			_transform->data = m_frame->m_frameCache.m_matrixCache.toPtr(first);
			_transform->num  = _num;

			return first;
		}

		void setTransform(uint32_t _cache, uint16_t _num)
		{
			BX_ASSERT(_cache < BGFX_CONFIG_MAX_MATRIX_CACHE, "Matrix cache out of bounds index %d (max: %d)"
				, _cache
				, BGFX_CONFIG_MAX_MATRIX_CACHE
				);
			m_draw.m_startMatrix = _cache;
			m_draw.m_numMatrices = uint16_t(bx::min<uint32_t>(_cache+_num, BGFX_CONFIG_MAX_MATRIX_CACHE-1) - _cache);
		}

		void setIndexBuffer(IndexBufferHandle _handle, const IndexBuffer& _ib, uint32_t _firstIndex, uint32_t _numIndices)
		{
			BX_ASSERT(UINT8_MAX != m_draw.m_streamMask, "bgfx::setVertexCount was already called for this draw call.");
			m_draw.m_startIndex  = _firstIndex;
			m_draw.m_numIndices  = _numIndices;
			m_draw.m_indexBuffer = _handle;
			m_draw.m_submitFlags |= 0 == (_ib.m_flags & BGFX_BUFFER_INDEX32) ? BGFX_SUBMIT_INTERNAL_NONE : BGFX_SUBMIT_INTERNAL_INDEX32;
		}

		void setIndexBuffer(const DynamicIndexBuffer& _dib, uint32_t _firstIndex, uint32_t _numIndices)
		{
			BX_ASSERT(UINT8_MAX != m_draw.m_streamMask, "bgfx::setVertexCount was already called for this draw call.");
			const uint32_t indexSize = 0 == (_dib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
			m_draw.m_startIndex  = _dib.m_startIndex + _firstIndex;
			m_draw.m_numIndices  = bx::min(_numIndices, _dib.m_size/indexSize);
			m_draw.m_indexBuffer = _dib.m_handle;
			m_draw.m_submitFlags |= 0 == (_dib.m_flags & BGFX_BUFFER_INDEX32) ? BGFX_SUBMIT_INTERNAL_NONE : BGFX_SUBMIT_INTERNAL_INDEX32;
		}

		void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _firstIndex, uint32_t _numIndices)
		{
			BX_ASSERT(UINT8_MAX != m_draw.m_streamMask, "bgfx::setVertexCount was already called for this draw call.");
			const uint32_t indexSize  = _tib->isIndex16 ? 2 : 4;
			const uint32_t numIndices = bx::min(_numIndices, _tib->size/indexSize);
			m_draw.m_indexBuffer = _tib->handle;
			m_draw.m_startIndex  = _tib->startIndex + _firstIndex;
			m_draw.m_numIndices  = numIndices;
			m_draw.m_submitFlags |= _tib->isIndex16 ? BGFX_SUBMIT_INTERNAL_NONE : BGFX_SUBMIT_INTERNAL_INDEX32;
			m_discard            = 0 == numIndices;
		}

		void setVertexBuffer(
			  uint8_t _stream
			, VertexBufferHandle _handle
			, uint32_t _startVertex
			, uint32_t _numVertices
			, VertexLayoutHandle _layoutHandle
			)
		{
			BX_ASSERT(UINT8_MAX != m_draw.m_streamMask, "bgfx::setVertexCount was already called for this draw call.");
			BX_ASSERT(_stream < BGFX_CONFIG_MAX_VERTEX_STREAMS, "Invalid stream %d (max %d).", _stream, BGFX_CONFIG_MAX_VERTEX_STREAMS);
			if (m_draw.setStreamBit(_stream, _handle) )
			{
				Stream& stream = m_draw.m_stream[_stream];
				stream.m_startVertex   = _startVertex;
				stream.m_handle        = _handle;
				stream.m_layoutHandle  = _layoutHandle;
				m_numVertices[_stream] = _numVertices;
			}
		}

		void setVertexBuffer(
			  uint8_t _stream
			, const DynamicVertexBuffer& _dvb
			, uint32_t _startVertex
			, uint32_t _numVertices
			, VertexLayoutHandle _layoutHandle
			)
		{
			BX_ASSERT(UINT8_MAX != m_draw.m_streamMask, "bgfx::setVertexCount was already called for this draw call.");
			BX_ASSERT(_stream < BGFX_CONFIG_MAX_VERTEX_STREAMS, "Invalid stream %d (max %d).", _stream, BGFX_CONFIG_MAX_VERTEX_STREAMS);
			if (m_draw.setStreamBit(_stream, _dvb.m_handle) )
			{
				Stream& stream = m_draw.m_stream[_stream];
				stream.m_startVertex   = _dvb.m_startVertex + _startVertex;
				stream.m_handle        = _dvb.m_handle;
				stream.m_layoutHandle  = isValid(_layoutHandle) ? _layoutHandle : _dvb.m_layoutHandle;
				m_numVertices[_stream] =
					bx::min(bx::uint32_imax(0, _dvb.m_numVertices - _startVertex), _numVertices)
					;
			}
		}

		void setVertexBuffer(
			  uint8_t _stream
			, const TransientVertexBuffer* _tvb
			, uint32_t _startVertex
			, uint32_t _numVertices
			, VertexLayoutHandle _layoutHandle
			)
		{
			BX_ASSERT(UINT8_MAX != m_draw.m_streamMask, "bgfx::setVertexCount was already called for this draw call.");
			BX_ASSERT(_stream < BGFX_CONFIG_MAX_VERTEX_STREAMS, "Invalid stream %d (max %d).", _stream, BGFX_CONFIG_MAX_VERTEX_STREAMS);
			if (m_draw.setStreamBit(_stream, _tvb->handle) )
			{
				Stream& stream = m_draw.m_stream[_stream];
				stream.m_startVertex   = _tvb->startVertex + _startVertex;
				stream.m_handle        = _tvb->handle;
				stream.m_layoutHandle  = isValid(_layoutHandle) ? _layoutHandle : _tvb->layoutHandle;
				m_numVertices[_stream] = bx::min(bx::uint32_imax(0, _tvb->size/_tvb->stride - _startVertex), _numVertices);
			}
		}

		void setVertexCount(uint32_t _numVertices)
		{
			BX_ASSERT(0 == m_draw.m_streamMask, "Vertex buffer already set.");
			m_draw.m_streamMask  = UINT8_MAX;
			Stream& stream = m_draw.m_stream[0];
			stream.m_startVertex        = 0;
			stream.m_handle.idx         = kInvalidHandle;
			stream.m_layoutHandle.idx   = kInvalidHandle;
			m_numVertices[0]            = _numVertices;
		}

		void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint32_t _start, uint32_t _num)
		{
			const uint32_t start = bx::min(_start, _idb->num);
			const uint32_t num   = bx::min(_idb->num - start, _num);
			m_draw.m_instanceDataOffset = _idb->offset + start*_idb->stride;
			m_draw.m_instanceDataStride = _idb->stride;
			m_draw.m_numInstances       = num;
			m_draw.m_instanceDataBuffer = _idb->handle;
		}

		void setInstanceDataBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num, uint16_t _stride)
		{
			m_draw.m_instanceDataOffset = _startVertex * _stride;
			m_draw.m_instanceDataStride = _stride;
			m_draw.m_numInstances       = _num;
			m_draw.m_instanceDataBuffer = _handle;
		}

		void setInstanceCount(uint32_t _numInstances)
		{
			BX_ASSERT(!isValid(m_draw.m_instanceDataBuffer), "Instance buffer already set.");
			m_draw.m_numInstances = _numInstances;
		}

		void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags)
		{
			Binding& bind = m_bind.m_bind[_stage];
			bind.m_idx    = _handle.idx;
			bind.m_type   = uint8_t(Binding::Texture);
			bind.m_samplerFlags = (_flags&BGFX_SAMPLER_INTERNAL_DEFAULT)
				? BGFX_SAMPLER_INTERNAL_DEFAULT
				: _flags
				;

			if (isValid(_sampler) )
			{
				uint32_t stage = _stage;
				setUniform(UniformType::Sampler, _sampler, &stage, 1);
			}
		}

		void setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access)
		{
			Binding& bind = m_bind.m_bind[_stage];
			bind.m_idx    = _handle.idx;
			bind.m_type   = uint8_t(Binding::IndexBuffer);
			bind.m_format = 0;
			bind.m_access = uint8_t(_access);
			bind.m_mip    = 0;
		}

		void setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access)
		{
			Binding& bind = m_bind.m_bind[_stage];
			bind.m_idx    = _handle.idx;
			bind.m_type   = uint8_t(Binding::VertexBuffer);
			bind.m_format = 0;
			bind.m_access = uint8_t(_access);
			bind.m_mip    = 0;
		}

		void setImage(uint8_t _stage, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format)
		{
			Binding& bind = m_bind.m_bind[_stage];
			bind.m_idx    = _handle.idx;
			bind.m_type   = uint8_t(Binding::Image);
			bind.m_format = uint8_t(_format);
			bind.m_access = uint8_t(_access);
			bind.m_mip    = _mip;
		}

		void discard(uint8_t _flags)
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
			{
				m_uniformSet.clear();
			}

			m_discard = false;
			m_draw.clear(_flags);
			m_compute.clear(_flags);
			m_bind.clear(_flags);
		}

		void submit(ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint32_t _depth, uint8_t _flags);

		void submit(ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint32_t _depth, uint8_t _flags)
		{
			m_draw.m_startIndirect  = _start;
			m_draw.m_numIndirect    = _num;
			m_draw.m_indirectBuffer = _indirectHandle;
			OcclusionQueryHandle handle = BGFX_INVALID_HANDLE;
			submit(_id, _program, handle, _depth, _flags);
		}

		void dispatch(ViewId _id, ProgramHandle _handle, uint32_t _ngx, uint32_t _ngy, uint32_t _ngz, uint8_t _flags);

		void dispatch(ViewId _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
		{
			m_compute.m_indirectBuffer = _indirectHandle;
			m_compute.m_startIndirect  = _start;
			m_compute.m_numIndirect    = _num;
			dispatch(_id, _handle, 0, 0, 0, _flags);
		}

		void blit(ViewId _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);

		Frame* m_frame;

		SortKey m_key;

		RenderDraw    m_draw;
		RenderCompute m_compute;
		RenderBind    m_bind;

		uint32_t m_numSubmitted;
		uint32_t m_numDropped;

		uint32_t m_uniformBegin;
		uint32_t m_uniformEnd;
		uint32_t m_numVertices[BGFX_CONFIG_MAX_VERTEX_STREAMS];
		uint8_t  m_uniformIdx;
		bool     m_discard;

		typedef stl::unordered_set<uint16_t> HandleSet;
		HandleSet m_uniformSet;
		HandleSet m_occlusionQuerySet;

		int64_t m_cpuTimeBegin;
		int64_t m_cpuTimeEnd;
	};

	struct VertexLayoutRef
	{
		VertexLayoutRef()
		{
		}

		void init()
		{
			bx::memSet(m_refCount,                  0, sizeof(m_refCount)               );
			bx::memSet(m_vertexBufferRef,        0xff, sizeof(m_vertexBufferRef)        );
			bx::memSet(m_dynamicVertexBufferRef, 0xff, sizeof(m_dynamicVertexBufferRef) );
		}

		template <uint16_t MaxHandlesT>
		void shutdown(bx::HandleAllocT<MaxHandlesT>& _handleAlloc)
		{
			for (uint16_t ii = 0, num = _handleAlloc.getNumHandles(); ii < num; ++ii)
			{
				VertexLayoutHandle handle = { _handleAlloc.getHandleAt(ii) };
				m_refCount[handle.idx] = 0;
				m_vertexLayoutMap.removeByHandle(handle.idx);
				_handleAlloc.free(handle.idx);
			}

			m_vertexLayoutMap.reset();
		}

		VertexLayoutHandle find(uint32_t _hash)
		{
			VertexLayoutHandle handle = { m_vertexLayoutMap.find(_hash) };
			return handle;
		}

		void add(VertexLayoutHandle _layoutHandle, uint32_t _hash)
		{
			m_refCount[_layoutHandle.idx]++;
			m_vertexLayoutMap.insert(_hash, _layoutHandle.idx);
		}

		void add(VertexBufferHandle _handle, VertexLayoutHandle _layoutHandle, uint32_t _hash)
		{
			BX_ASSERT(m_vertexBufferRef[_handle.idx].idx == kInvalidHandle, "");
			m_vertexBufferRef[_handle.idx] = _layoutHandle;
			m_refCount[_layoutHandle.idx]++;
			m_vertexLayoutMap.insert(_hash, _layoutHandle.idx);
		}

		void add(DynamicVertexBufferHandle _handle, VertexLayoutHandle _layoutHandle, uint32_t _hash)
		{
			BX_ASSERT(m_dynamicVertexBufferRef[_handle.idx].idx == kInvalidHandle, "");
			m_dynamicVertexBufferRef[_handle.idx] = _layoutHandle;
			m_refCount[_layoutHandle.idx]++;
			m_vertexLayoutMap.insert(_hash, _layoutHandle.idx);
		}

		VertexLayoutHandle release(VertexLayoutHandle _layoutHandle)
		{
			if (isValid(_layoutHandle) )
			{
				m_refCount[_layoutHandle.idx]--;

				if (0 == m_refCount[_layoutHandle.idx])
				{
					m_vertexLayoutMap.removeByHandle(_layoutHandle.idx);
					return _layoutHandle;
				}
			}

			return BGFX_INVALID_HANDLE;
		}

		VertexLayoutHandle release(VertexBufferHandle _handle)
		{
			VertexLayoutHandle layoutHandle = m_vertexBufferRef[_handle.idx];
			layoutHandle = release(layoutHandle);
			m_vertexBufferRef[_handle.idx].idx = kInvalidHandle;

			return layoutHandle;
		}

		VertexLayoutHandle release(DynamicVertexBufferHandle _handle)
		{
			VertexLayoutHandle layoutHandle = m_dynamicVertexBufferRef[_handle.idx];
			layoutHandle = release(layoutHandle);
			m_dynamicVertexBufferRef[_handle.idx].idx = kInvalidHandle;

			return layoutHandle;
		}

		typedef bx::HandleHashMapT<BGFX_CONFIG_MAX_VERTEX_LAYOUTS*2> VertexLayoutMap;
		VertexLayoutMap m_vertexLayoutMap;

		uint16_t m_refCount[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		VertexLayoutHandle m_vertexBufferRef[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		VertexLayoutHandle m_dynamicVertexBufferRef[BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS];
	};

	// First-fit non-local allocator.
	class NonLocalAllocator
	{
	public:
		static const uint64_t kInvalidBlock = UINT64_MAX;

		NonLocalAllocator()
		{
		}

		~NonLocalAllocator()
		{
		}

		void reset()
		{
			m_free.clear();
			m_used.clear();
		}

		void add(uint64_t _ptr, uint32_t _size)
		{
			m_free.push_back(Free(_ptr, _size) );
		}

		uint64_t remove()
		{
			BX_ASSERT(0 == m_used.size(), "");

			if (0 < m_free.size() )
			{
				Free freeBlock = m_free.front();
				m_free.pop_front();
				return freeBlock.m_ptr;
			}

			return 0;
		}

		uint64_t alloc(uint32_t _size)
		{
			_size = bx::max(_size, 16u);

			for (FreeList::iterator it = m_free.begin(), itEnd = m_free.end(); it != itEnd; ++it)
			{
				if (it->m_size >= _size)
				{
					uint64_t ptr = it->m_ptr;

					m_used.insert(stl::make_pair(ptr, _size) );

					if (it->m_size != _size)
					{
						it->m_size -= _size;
						it->m_ptr  += _size;
					}
					else
					{
						m_free.erase(it);
					}

					return ptr;
				}
			}

			// there is no block large enough.
			return kInvalidBlock;
		}

		void free(uint64_t _block)
		{
			UsedList::iterator it = m_used.find(_block);
			if (it != m_used.end() )
			{
				m_free.push_front(Free(it->first, it->second) );
				m_used.erase(it);
			}
		}

		bool compact()
		{
			m_free.sort();

			for (FreeList::iterator it = m_free.begin(), next = it, itEnd = m_free.end(); next != itEnd;)
			{
				if ( (it->m_ptr + it->m_size) == next->m_ptr)
				{
					it->m_size += next->m_size;
					next = m_free.erase(next);
				}
				else
				{
					it = next;
					++next;
				}
			}

			return 0 == m_used.size();
		}

	private:
		struct Free
		{
			Free(uint64_t _ptr, uint32_t _size)
				: m_ptr(_ptr)
				, m_size(_size)
			{
			}

			bool operator<(const Free& rhs) const
			{
				return m_ptr < rhs.m_ptr;
			}

			uint64_t m_ptr;
			uint32_t m_size;
		};

		typedef stl::list<Free> FreeList;
		FreeList m_free;

		typedef stl::unordered_map<uint64_t, uint32_t> UsedList;
		UsedList m_used;
	};

	struct BX_NO_VTABLE RendererContextI
	{
		virtual ~RendererContextI() = 0;
		virtual RendererType::Enum getRendererType() const = 0;
		virtual const char* getRendererName() const = 0;
		virtual bool isDeviceRemoved() = 0;
		virtual void flip() = 0;
		virtual void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) = 0;
		virtual void destroyIndexBuffer(IndexBufferHandle _handle) = 0;
		virtual void createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _layout) = 0;
		virtual void destroyVertexLayout(VertexLayoutHandle _handle) = 0;
		virtual void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _layoutHandle, uint16_t _flags) = 0;
		virtual void destroyVertexBuffer(VertexBufferHandle _handle) = 0;
		virtual void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) = 0;
		virtual void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) = 0;
		virtual void destroyDynamicIndexBuffer(IndexBufferHandle _handle) = 0;
		virtual void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) = 0;
		virtual void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) = 0;
		virtual void destroyDynamicVertexBuffer(VertexBufferHandle _handle) = 0;
		virtual void createShader(ShaderHandle _handle, const Memory* _mem) = 0;
		virtual void destroyShader(ShaderHandle _handle) = 0;
		virtual void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) = 0;
		virtual void destroyProgram(ProgramHandle _handle) = 0;
		virtual void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) = 0;
		virtual void updateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip) = 0;
		virtual void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) = 0;
		virtual void updateTextureEnd() = 0;
		virtual void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) = 0;
		virtual void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers) = 0;
		virtual void overrideInternal(TextureHandle _handle, uintptr_t _ptr) = 0;
		virtual uintptr_t getInternal(TextureHandle _handle) = 0;
		virtual void destroyTexture(TextureHandle _handle) = 0;
		virtual void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) = 0;
		virtual void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat) = 0;
		virtual void destroyFrameBuffer(FrameBufferHandle _handle) = 0;
		virtual void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) = 0;
		virtual void destroyUniform(UniformHandle _handle) = 0;
		virtual void requestScreenShot(FrameBufferHandle _handle, const char* _filePath) = 0;
		virtual void updateViewName(ViewId _id, const char* _name) = 0;
		virtual void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) = 0;
		virtual void invalidateOcclusionQuery(OcclusionQueryHandle _handle) = 0;
		virtual void setMarker(const char* _marker, uint16_t _len) = 0;
		virtual void setName(Handle _handle, const char* _name, uint16_t _len) = 0;
		virtual void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) = 0;
		virtual void blitSetup(TextVideoMemBlitter& _blitter) = 0;
		virtual void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) = 0;
	};

	inline RendererContextI::~RendererContextI()
	{
	}

	void rendererUpdateUniforms(RendererContextI* _renderCtx, UniformBuffer* _uniformBuffer, uint32_t _begin, uint32_t _end);

#if BGFX_CONFIG_DEBUG
#	define BGFX_API_FUNC(_func) BX_NO_INLINE _func
#else
#	define BGFX_API_FUNC(_func) _func
#endif // BGFX_CONFIG_DEBUG

	struct Context
	{
		static constexpr uint32_t kAlignment = 64;

		Context()
			: m_render(&m_frame[0])
			, m_submit(&m_frame[BGFX_CONFIG_MULTITHREADED ? 1 : 0])
			, m_numFreeDynamicIndexBufferHandles(0)
			, m_numFreeDynamicVertexBufferHandles(0)
			, m_numFreeOcclusionQueryHandles(0)
			, m_colorPaletteDirty(0)
			, m_frames(0)
			, m_debug(BGFX_DEBUG_NONE)
			, m_rtMemoryUsed(0)
			, m_textureMemoryUsed(0)
			, m_renderCtx(NULL)
			, m_rendererInitialized(false)
			, m_exit(false)
			, m_flipAfterRender(false)
			, m_singleThreaded(false)
		{
		}

		~Context()
		{
		}

#if BX_CONFIG_SUPPORTS_THREADING
		static int32_t renderThread(bx::Thread* /*_self*/, void* /*_userData*/)
		{
			BX_TRACE("render thread start");
			BGFX_PROFILER_SET_CURRENT_THREAD_NAME("bgfx - Render Thread");
			while (RenderFrame::Exiting != bgfx::renderFrame() ) {};
			BX_TRACE("render thread exit");
			return bx::kExitSuccess;
		}
#endif

		// game thread
		bool init(const Init& _init);
		void shutdown();

		CommandBuffer& getCommandBuffer(CommandBuffer::Enum _cmd)
		{
			CommandBuffer& cmdbuf = _cmd < CommandBuffer::End ? m_submit->m_cmdPre : m_submit->m_cmdPost;
			uint8_t cmd = (uint8_t)_cmd;
			cmdbuf.write(cmd);
			return cmdbuf;
		}

		BGFX_API_FUNC(void reset(uint32_t _width, uint32_t _height, uint32_t _flags, TextureFormat::Enum _format) )
		{
			const TextureFormat::Enum format = TextureFormat::Count != _format ? _format : m_init.resolution.format;

			if (!g_platformDataChangedSinceReset
			&&  m_init.resolution.format == format
			&&  m_init.resolution.width  == _width
			&&  m_init.resolution.height == _height
			&&  m_init.resolution.reset  == _flags)
			{
				// Nothing changed, ignore request.
				return;
			}

			BX_WARN(g_caps.limits.maxTextureSize >= _width
				&&  g_caps.limits.maxTextureSize >= _height
				, "Frame buffer resolution width or height can't be larger than limits.maxTextureSize %d (width %d, height %d)."
				, g_caps.limits.maxTextureSize
				, _width
				, _height
				);
			m_init.resolution.format = format;
			m_init.resolution.width  = bx::clamp(_width,  1u, g_caps.limits.maxTextureSize);
			m_init.resolution.height = bx::clamp(_height, 1u, g_caps.limits.maxTextureSize);
			m_init.resolution.reset  = 0
				| _flags
				| (g_platformDataChangedSinceReset ? BGFX_RESET_INTERNAL_FORCE : 0)
				;
			dump(m_init.resolution);
			g_platformDataChangedSinceReset = false;

			m_flipAfterRender = !!(_flags & BGFX_RESET_FLIP_AFTER_RENDER);

			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				m_view[ii].setFrameBuffer(BGFX_INVALID_HANDLE);
			}

			for (uint16_t ii = 0, num = m_textureHandle.getNumHandles(); ii < num; ++ii)
			{
				uint16_t textureIdx = m_textureHandle.getHandleAt(ii);
				const TextureRef& ref = m_textureRef[textureIdx];
				if (BackbufferRatio::Count != ref.m_bbRatio)
				{
					TextureHandle handle = { textureIdx };
					resizeTexture(handle
						, uint16_t(m_init.resolution.width)
						, uint16_t(m_init.resolution.height)
						, ref.m_numMips
						, ref.m_numLayers
						);
					m_init.resolution.reset |= BGFX_RESET_INTERNAL_FORCE;
				}
			}
		}

		BGFX_API_FUNC(void setDebug(uint32_t _debug) )
		{
			m_debug = _debug;
		}

		BGFX_API_FUNC(void dbgTextClear(uint8_t _attr, bool _small) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			m_submit->m_textVideoMem->resize(_small, (uint16_t)m_init.resolution.width, (uint16_t)m_init.resolution.height);
			m_submit->m_textVideoMem->clear(_attr);
		}

		BGFX_API_FUNC(void dbgTextPrintfVargs(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			m_submit->m_textVideoMem->printfVargs(_x, _y, _attr, _format, _argList);
		}

		BGFX_API_FUNC(void dbgTextImage(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			m_submit->m_textVideoMem->image(_x, _y, _width, _height, _data, _pitch);
		}

		BGFX_API_FUNC(const Stats* getPerfStats() )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			Stats& stats = m_submit->m_perfStats;
			const Resolution& resolution = m_submit->m_resolution;
			stats.width  = uint16_t(resolution.width);
			stats.height = uint16_t(resolution.height);
			const TextVideoMem* tvm = m_submit->m_textVideoMem;
			stats.textWidth  = tvm->m_width;
			stats.textHeight = tvm->m_height;
			stats.encoderStats = m_encoderStats;

			stats.numDynamicIndexBuffers  = m_dynamicIndexBufferHandle.getNumHandles();
			stats.numDynamicVertexBuffers = m_dynamicVertexBufferHandle.getNumHandles();
			stats.numFrameBuffers         = m_frameBufferHandle.getNumHandles();
			stats.numIndexBuffers         = m_indexBufferHandle.getNumHandles();
			stats.numOcclusionQueries     = m_occlusionQueryHandle.getNumHandles();
			stats.numPrograms             = m_programHandle.getNumHandles();
			stats.numShaders              = m_shaderHandle.getNumHandles();
			stats.numTextures             = m_textureHandle.getNumHandles();
			stats.numUniforms             = m_uniformHandle.getNumHandles();
			stats.numVertexBuffers        = m_vertexBufferHandle.getNumHandles();
			stats.numVertexLayouts        = m_layoutHandle.getNumHandles();

			stats.textureMemoryUsed = m_textureMemoryUsed;
			stats.rtMemoryUsed      = m_rtMemoryUsed;

			return &stats;
		}

		BGFX_API_FUNC(IndexBufferHandle createIndexBuffer(const Memory* _mem, uint16_t _flags) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			IndexBufferHandle handle = { m_indexBufferHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate index buffer handle.");
			if (isValid(handle) )
			{
				IndexBuffer& ib = m_indexBuffers[handle.idx];
				ib.m_size  = _mem->size;
				ib.m_flags = _flags;

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateIndexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
				cmdbuf.write(_flags);

				setDebugName(convert(handle) );
			}
			else
			{
				release(_mem);
			}

			return handle;
		}

		BGFX_API_FUNC(void setName(IndexBufferHandle _handle, const bx::StringView& _name) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("setName", m_indexBufferHandle, _handle);

			IndexBuffer& ref = m_indexBuffers[_handle.idx];
			ref.m_name.set(_name);

			setName(convert(_handle), _name);
		}

		BGFX_API_FUNC(void destroyIndexBuffer(IndexBufferHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyIndexBuffer", m_indexBufferHandle, _handle);
			bool ok = m_submit->free(_handle); BX_UNUSED(ok);
			BX_ASSERT(ok, "Index buffer handle %d is already destroyed!", _handle.idx);

			IndexBuffer& ref = m_indexBuffers[_handle.idx];
			ref.m_name.clear();

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyIndexBuffer);
			cmdbuf.write(_handle);
		}

		VertexLayoutHandle findOrCreateVertexLayout(const VertexLayout& _layout, bool _refCountOnCreation = false)
		{
			VertexLayoutHandle layoutHandle = m_vertexLayoutRef.find(_layout.m_hash);

			if (isValid(layoutHandle) )
			{
				return layoutHandle;
			}

			layoutHandle = { m_layoutHandle.alloc() };
			if (!isValid(layoutHandle) )
			{
				BX_TRACE("WARNING: Failed to allocate vertex layout handle (BGFX_CONFIG_MAX_VERTEX_LAYOUTS, max: %d).", BGFX_CONFIG_MAX_VERTEX_LAYOUTS);
				return BGFX_INVALID_HANDLE;
			}

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexLayout);
			cmdbuf.write(layoutHandle);
			cmdbuf.write(_layout);

			if (_refCountOnCreation)
			{
				m_vertexLayoutRef.add(layoutHandle, _layout.m_hash);
			}

			return layoutHandle;
		}

		BGFX_API_FUNC(VertexLayoutHandle createVertexLayout(const VertexLayout& _layout) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			VertexLayoutHandle handle = findOrCreateVertexLayout(_layout);
			if (!isValid(handle) )
			{
				return BGFX_INVALID_HANDLE;
			}

			m_vertexLayoutRef.add(handle, _layout.m_hash);

			return handle;
		}

		BGFX_API_FUNC(void destroyVertexLayout(VertexLayoutHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);
			if (isValid(m_vertexLayoutRef.release(_handle) ) )
			{
				m_submit->free(_handle);
			}
		}

		BGFX_API_FUNC(VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexLayout& _layout, uint16_t _flags) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			VertexBufferHandle handle = { m_vertexBufferHandle.alloc() };

			if (isValid(handle) )
			{
				VertexLayoutHandle layoutHandle = findOrCreateVertexLayout(_layout);
				if (!isValid(layoutHandle) )
				{
					BX_TRACE("WARNING: Failed to allocate vertex layout handle (BGFX_CONFIG_MAX_VERTEX_LAYOUTS, max: %d).", BGFX_CONFIG_MAX_VERTEX_LAYOUTS);
					m_vertexBufferHandle.free(handle.idx);
					return BGFX_INVALID_HANDLE;
				}

				m_vertexLayoutRef.add(handle, layoutHandle, _layout.m_hash);

				VertexBuffer& vb = m_vertexBuffers[handle.idx];
				vb.m_size   = _mem->size;
				vb.m_stride = _layout.m_stride;

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
				cmdbuf.write(layoutHandle);
				cmdbuf.write(_flags);

				setDebugName(convert(handle) );

				return handle;
			}

			BX_TRACE("WARNING: Failed to allocate vertex buffer handle (BGFX_CONFIG_MAX_VERTEX_BUFFERS, max: %d).", BGFX_CONFIG_MAX_VERTEX_BUFFERS);
			release(_mem);

			return BGFX_INVALID_HANDLE;
		}

		BGFX_API_FUNC(void setName(VertexBufferHandle _handle, const bx::StringView& _name) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("setName", m_vertexBufferHandle, _handle);

			VertexBuffer& ref = m_vertexBuffers[_handle.idx];
			ref.m_name.set(_name);

			setName(convert(_handle), _name);
		}

		BGFX_API_FUNC(void destroyVertexBuffer(VertexBufferHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyVertexBuffer", m_vertexBufferHandle, _handle);
			bool ok = m_submit->free(_handle); BX_UNUSED(ok);
			BX_ASSERT(ok, "Vertex buffer handle %d is already destroyed!", _handle.idx);

			VertexBuffer& ref = m_vertexBuffers[_handle.idx];
			ref.m_name.clear();

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexBuffer);
			cmdbuf.write(_handle);
		}

		void destroyVertexBufferInternal(VertexBufferHandle _handle)
		{
			VertexLayoutHandle layoutHandle = m_vertexLayoutRef.release(_handle);
			if (isValid(layoutHandle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexLayout);
				cmdbuf.write(layoutHandle);
				m_render->free(layoutHandle);
			}

			m_vertexBufferHandle.free(_handle.idx);
		}

		uint64_t allocDynamicIndexBuffer(uint32_t _size, uint16_t _flags)
		{
			uint64_t ptr = m_dynIndexBufferAllocator.alloc(_size);
			if (ptr == NonLocalAllocator::kInvalidBlock)
			{
				IndexBufferHandle indexBufferHandle = { m_indexBufferHandle.alloc() };
				if (!isValid(indexBufferHandle) )
				{
					BX_TRACE("Failed to allocate index buffer handle.");
					return NonLocalAllocator::kInvalidBlock;
				}

				const uint32_t allocSize = bx::max<uint32_t>(BGFX_CONFIG_DYNAMIC_INDEX_BUFFER_SIZE, _size);

				IndexBuffer& ib = m_indexBuffers[indexBufferHandle.idx];
				ib.m_size = allocSize;

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicIndexBuffer);
				cmdbuf.write(indexBufferHandle);
				cmdbuf.write(allocSize);
				cmdbuf.write(_flags);

				m_dynIndexBufferAllocator.add(uint64_t(indexBufferHandle.idx) << 32, allocSize);
				ptr = m_dynIndexBufferAllocator.alloc(_size);
			}

			return ptr;
		}

		uint64_t allocIndexBuffer(uint32_t _size, uint16_t _flags)
		{
			IndexBufferHandle indexBufferHandle = { m_indexBufferHandle.alloc() };
			if (!isValid(indexBufferHandle) )
			{
				BX_TRACE("Failed to allocate index buffer handle.");
				return NonLocalAllocator::kInvalidBlock;
			}

			IndexBuffer& ib = m_indexBuffers[indexBufferHandle.idx];
			ib.m_size = _size;

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicIndexBuffer);
			cmdbuf.write(indexBufferHandle);
			cmdbuf.write(_size);
			cmdbuf.write(_flags);

			setDebugName(convert(indexBufferHandle), "Dynamic Index Buffer");

			return uint64_t(indexBufferHandle.idx) << 32;
		}

		BGFX_API_FUNC(DynamicIndexBufferHandle createDynamicIndexBuffer(uint32_t _num, uint16_t _flags) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			DynamicIndexBufferHandle handle = { m_dynamicIndexBufferHandle.alloc() };
			if (!isValid(handle) )
			{
				BX_TRACE("Failed to allocate dynamic index buffer handle.");
				return handle;
			}

			const uint32_t indexSize = 0 == (_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
			const uint32_t size = bx::alignUp(_num*indexSize, 16);

			const uint64_t ptr = (0 != (_flags & BGFX_BUFFER_COMPUTE_READ_WRITE) )
				? allocIndexBuffer(size, _flags)
				: allocDynamicIndexBuffer(size, _flags)
				;

			if (ptr == NonLocalAllocator::kInvalidBlock)
			{
				m_dynamicIndexBufferHandle.free(handle.idx);
				return BGFX_INVALID_HANDLE;
			}

			DynamicIndexBuffer& dib = m_dynamicIndexBuffers[handle.idx];
			dib.m_handle.idx = uint16_t(ptr>>32);
			dib.m_offset     = uint32_t(ptr);
			dib.m_size       = _num * indexSize;
			dib.m_startIndex = bx::strideAlign(dib.m_offset, indexSize)/indexSize;
			dib.m_flags      = _flags;

			return handle;
		}

		BGFX_API_FUNC(DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem, uint16_t _flags) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BX_ASSERT(0 == (_flags &  BGFX_BUFFER_COMPUTE_READ_WRITE), "Cannot initialize compute buffer from CPU.");
			const uint32_t indexSize = 0 == (_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
			DynamicIndexBufferHandle handle = createDynamicIndexBuffer(_mem->size/indexSize, _flags);

			if (!isValid(handle) )
			{
				release(_mem);
				return BGFX_INVALID_HANDLE;
			}

			update(handle, 0, _mem);

			return handle;
		}

		BGFX_API_FUNC(void update(DynamicIndexBufferHandle _handle, uint32_t _startIndex, const Memory* _mem) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("updateDynamicIndexBuffer", m_dynamicIndexBufferHandle, _handle);

			DynamicIndexBuffer& dib = m_dynamicIndexBuffers[_handle.idx];
			BX_ASSERT(0 == (dib.m_flags &  BGFX_BUFFER_COMPUTE_WRITE), "Can't update GPU buffer from CPU.");
			const uint32_t indexSize = 0 == (dib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;

			if (dib.m_size < _mem->size
			&&  0 != (dib.m_flags & BGFX_BUFFER_ALLOW_RESIZE) )
			{
				m_dynIndexBufferAllocator.free(uint64_t(dib.m_handle.idx)<<32 | dib.m_offset);
				m_dynIndexBufferAllocator.compact();

				const uint64_t ptr = (0 != (dib.m_flags & BGFX_BUFFER_COMPUTE_READ) )
					? allocIndexBuffer(_mem->size, dib.m_flags)
					: allocDynamicIndexBuffer(_mem->size, dib.m_flags)
					;

				dib.m_handle.idx = uint16_t(ptr>>32);
				dib.m_offset     = uint32_t(ptr);
				dib.m_size       = _mem->size;
				dib.m_startIndex = bx::strideAlign(dib.m_offset, indexSize)/indexSize;
			}

			const uint32_t offset = (dib.m_startIndex + _startIndex)*indexSize;
			const uint32_t size   = bx::min<uint32_t>(offset
				+ bx::min(bx::uint32_satsub(dib.m_size, _startIndex*indexSize), _mem->size)
				, m_indexBuffers[dib.m_handle.idx].m_size) - offset
				;
			BX_ASSERT(_mem->size <= size, "Truncating dynamic index buffer update (size %d, mem size %d)."
				, size
				, _mem->size
				);
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::UpdateDynamicIndexBuffer);
			cmdbuf.write(dib.m_handle);
			cmdbuf.write(offset);
			cmdbuf.write(size);
			cmdbuf.write(_mem);
		}

		BGFX_API_FUNC(void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyDynamicIndexBuffer", m_dynamicIndexBufferHandle, _handle);

			m_freeDynamicIndexBufferHandle[m_numFreeDynamicIndexBufferHandles++] = _handle;
		}

		void destroyDynamicIndexBufferInternal(DynamicIndexBufferHandle _handle)
		{
			DynamicIndexBuffer& dib = m_dynamicIndexBuffers[_handle.idx];

			if (0 != (dib.m_flags & BGFX_BUFFER_COMPUTE_READ_WRITE) )
			{
				destroyIndexBuffer(dib.m_handle);
			}
			else
			{
				m_dynIndexBufferAllocator.free(uint64_t(dib.m_handle.idx)<<32 | dib.m_offset);
				if (m_dynIndexBufferAllocator.compact() )
				{
					for (uint64_t ptr = m_dynIndexBufferAllocator.remove(); 0 != ptr; ptr = m_dynIndexBufferAllocator.remove() )
					{
						IndexBufferHandle handle = { uint16_t(ptr>>32) };
						destroyIndexBuffer(handle);
					}
				}
			}

			m_dynamicIndexBufferHandle.free(_handle.idx);
		}

		uint64_t allocDynamicVertexBuffer(uint32_t _size, uint16_t _flags)
		{
			uint64_t ptr = m_dynVertexBufferAllocator.alloc(_size);
			if (ptr == NonLocalAllocator::kInvalidBlock)
			{
				VertexBufferHandle vertexBufferHandle = { m_vertexBufferHandle.alloc() };
				if (!isValid(vertexBufferHandle) )
				{
					BX_TRACE("Failed to allocate dynamic vertex buffer handle.");
					return NonLocalAllocator::kInvalidBlock;
				}

				const uint32_t allocSize = bx::max<uint32_t>(BGFX_CONFIG_DYNAMIC_VERTEX_BUFFER_SIZE, _size);

				VertexBuffer& vb = m_vertexBuffers[vertexBufferHandle.idx];
				vb.m_size   = allocSize;
				vb.m_stride = 0;

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicVertexBuffer);
				cmdbuf.write(vertexBufferHandle);
				cmdbuf.write(allocSize);
				cmdbuf.write(_flags);

				m_dynVertexBufferAllocator.add(uint64_t(vertexBufferHandle.idx) << 32, allocSize);
				ptr = m_dynVertexBufferAllocator.alloc(_size);
			}

			return ptr;
		}

		uint64_t allocVertexBuffer(uint32_t _size, uint16_t _flags)
		{
			VertexBufferHandle vertexBufferHandle = { m_vertexBufferHandle.alloc() };

			if (!isValid(vertexBufferHandle) )
			{
				BX_TRACE("WARNING: Failed to allocate vertex buffer handle (BGFX_CONFIG_MAX_VERTEX_BUFFERS, max: %d).", BGFX_CONFIG_MAX_VERTEX_BUFFERS);
				return NonLocalAllocator::kInvalidBlock;
			}

			VertexBuffer& vb = m_vertexBuffers[vertexBufferHandle.idx];
			vb.m_size   = _size;
			vb.m_stride = 0;

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicVertexBuffer);
			cmdbuf.write(vertexBufferHandle);
			cmdbuf.write(_size);
			cmdbuf.write(_flags);

			setDebugName(convert(vertexBufferHandle), "Dynamic Vertex Buffer");

			return uint64_t(vertexBufferHandle.idx)<<32;
		}

		BGFX_API_FUNC(DynamicVertexBufferHandle createDynamicVertexBuffer(uint32_t _num, const VertexLayout& _layout, uint16_t _flags) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			VertexLayoutHandle layoutHandle = findOrCreateVertexLayout(_layout);
			if (!isValid(layoutHandle) )
			{
				BX_TRACE("WARNING: Failed to allocate vertex layout handle (BGFX_CONFIG_MAX_VERTEX_LAYOUTS, max: %d).", BGFX_CONFIG_MAX_VERTEX_LAYOUTS);
				return BGFX_INVALID_HANDLE;
			}

			DynamicVertexBufferHandle handle = { m_dynamicVertexBufferHandle.alloc() };
			if (!isValid(handle) )
			{
				BX_TRACE("WARNING: Failed to allocate dynamic vertex buffer handle (BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS, max: %d).", BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS);
				return BGFX_INVALID_HANDLE;
			}

			const uint32_t size = bx::strideAlign<16>(_num*_layout.m_stride, _layout.m_stride)+_layout.m_stride;

			const uint64_t ptr = (0 != (_flags & BGFX_BUFFER_COMPUTE_READ_WRITE) )
				? allocVertexBuffer(size, _flags)
				: allocDynamicVertexBuffer(size, _flags)
				;

			if (ptr == NonLocalAllocator::kInvalidBlock)
			{
				m_dynamicVertexBufferHandle.free(handle.idx);
				return BGFX_INVALID_HANDLE;
			}

			DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[handle.idx];
			dvb.m_handle.idx    = uint16_t(ptr>>32);
			dvb.m_offset        = uint32_t(ptr);
			dvb.m_size          = _num * _layout.m_stride;
			dvb.m_startVertex   = bx::strideAlign(dvb.m_offset, _layout.m_stride)/_layout.m_stride;
			dvb.m_numVertices   = _num;
			dvb.m_stride        = _layout.m_stride;
			dvb.m_layoutHandle  = layoutHandle;
			dvb.m_flags         = _flags;
			m_vertexLayoutRef.add(handle, layoutHandle, _layout.m_hash);

			return handle;
		}

		BGFX_API_FUNC(DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexLayout& _layout, uint16_t _flags) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			uint32_t numVertices = _mem->size/_layout.m_stride;
			DynamicVertexBufferHandle handle = createDynamicVertexBuffer(numVertices, _layout, _flags);

			if (!isValid(handle) )
			{
				release(_mem);
				return BGFX_INVALID_HANDLE;
			}

			update(handle, 0, _mem);

			return handle;
		}

		BGFX_API_FUNC(void update(DynamicVertexBufferHandle _handle, uint32_t _startVertex, const Memory* _mem) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("updateDynamicVertexBuffer", m_dynamicVertexBufferHandle, _handle);

			DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[_handle.idx];
			BX_ASSERT(0 == (dvb.m_flags &  BGFX_BUFFER_COMPUTE_WRITE), "Can't update GPU write buffer from CPU.");

			if (dvb.m_size < _mem->size
			&&  0 != (dvb.m_flags & BGFX_BUFFER_ALLOW_RESIZE) )
			{
				m_dynVertexBufferAllocator.free(uint64_t(dvb.m_handle.idx)<<32 | dvb.m_offset);
				m_dynVertexBufferAllocator.compact();

				const uint32_t size = bx::strideAlign<16>(_mem->size, dvb.m_stride)+dvb.m_stride;

				const uint64_t ptr = (0 != (dvb.m_flags & BGFX_BUFFER_COMPUTE_READ) )
					? allocVertexBuffer(size, dvb.m_flags)
					: allocDynamicVertexBuffer(size, dvb.m_flags)
					;

				dvb.m_handle.idx  = uint16_t(ptr>>32);
				dvb.m_offset      = uint32_t(ptr);
				dvb.m_size        = size;
				dvb.m_numVertices = _mem->size / dvb.m_stride;
				dvb.m_startVertex = bx::strideAlign(dvb.m_offset, dvb.m_stride)/dvb.m_stride;
			}

			const uint32_t offset = (dvb.m_startVertex + _startVertex)*dvb.m_stride;
			const uint32_t size   = bx::min<uint32_t>(offset
				+ bx::min(bx::uint32_satsub(dvb.m_size, _startVertex*dvb.m_stride), _mem->size)
				, m_vertexBuffers[dvb.m_handle.idx].m_size) - offset
				;
			BX_ASSERT(_mem->size <= size, "Truncating dynamic vertex buffer update (size %d, mem size %d)."
				, size
				, _mem->size
				);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::UpdateDynamicVertexBuffer);
			cmdbuf.write(dvb.m_handle);
			cmdbuf.write(offset);
			cmdbuf.write(size);
			cmdbuf.write(_mem);
		}

		BGFX_API_FUNC(void destroyDynamicVertexBuffer(DynamicVertexBufferHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyDynamicVertexBuffer", m_dynamicVertexBufferHandle, _handle);

			m_freeDynamicVertexBufferHandle[m_numFreeDynamicVertexBufferHandles++] = _handle;
		}

		void destroyDynamicVertexBufferInternal(DynamicVertexBufferHandle _handle)
		{
			VertexLayoutHandle layoutHandle = m_vertexLayoutRef.release(_handle);
			BGFX_CHECK_HANDLE_INVALID_OK("destroyDynamicVertexBufferInternal", m_layoutHandle, layoutHandle);

			if (isValid(layoutHandle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexLayout);
				cmdbuf.write(layoutHandle);
				m_render->free(layoutHandle);
			}

			DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[_handle.idx];

			if (0 != (dvb.m_flags & BGFX_BUFFER_COMPUTE_READ_WRITE) )
			{
				destroyVertexBuffer(dvb.m_handle);
			}
			else
			{
				m_dynVertexBufferAllocator.free(uint64_t(dvb.m_handle.idx)<<32 | dvb.m_offset);
				if (m_dynVertexBufferAllocator.compact() )
				{
					for (uint64_t ptr = m_dynVertexBufferAllocator.remove(); 0 != ptr; ptr = m_dynVertexBufferAllocator.remove() )
					{
						VertexBufferHandle handle = { uint16_t(ptr>>32) };
						destroyVertexBuffer(handle);
					}
				}
			}

			m_dynamicVertexBufferHandle.free(_handle.idx);
		}

		BGFX_API_FUNC(uint32_t getAvailTransientIndexBuffer(uint32_t _num, bool _index32) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			const bool isIndex16     = !_index32;
			const uint16_t indexSize = isIndex16 ? 2 : 4;
			return m_submit->getAvailTransientIndexBuffer(_num, indexSize);
		}

		BGFX_API_FUNC(uint32_t getAvailTransientVertexBuffer(uint32_t _num, uint16_t _stride) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			return m_submit->getAvailTransientVertexBuffer(_num, _stride);
		}

		TransientIndexBuffer* createTransientIndexBuffer(uint32_t _size)
		{
			TransientIndexBuffer* tib = NULL;

			IndexBufferHandle handle = { m_indexBufferHandle.alloc() };
			BX_WARN(isValid(handle), "Failed to allocate transient index buffer handle.");
			if (isValid(handle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicIndexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_size);
				uint16_t flags = BGFX_BUFFER_NONE;
				cmdbuf.write(flags);

				const uint32_t size = 0
					+ bx::alignUp<uint32_t>(sizeof(TransientIndexBuffer), 16)
					+ bx::alignUp(_size, 16)
					;
				tib = (TransientIndexBuffer*)BX_ALIGNED_ALLOC(g_allocator, size, 16);
				tib->data   = (uint8_t *)tib + bx::alignUp(sizeof(TransientIndexBuffer), 16);
				tib->size   = _size;
				tib->handle = handle;

				setDebugName(convert(handle), "Transient Index Buffer");
			}

			return tib;
		}

		void destroyTransientIndexBuffer(TransientIndexBuffer* _tib)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyDynamicIndexBuffer);
			cmdbuf.write(_tib->handle);

			m_submit->free(_tib->handle);
			BX_ALIGNED_FREE(g_allocator, _tib, 16);
		}

		BGFX_API_FUNC(void allocTransientIndexBuffer(TransientIndexBuffer* _tib, uint32_t _num, bool _index32) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			const bool isIndex16     = !_index32;
			const uint16_t indexSize = isIndex16 ? 2 : 4;
			const uint32_t offset    = m_submit->allocTransientIndexBuffer(_num, indexSize);

			TransientIndexBuffer& tib = *m_submit->m_transientIb;

			_tib->data       = &tib.data[offset];
			_tib->size       = _num * indexSize;
			_tib->handle     = tib.handle;
			_tib->startIndex = bx::strideAlign(offset, indexSize) / indexSize;
			_tib->isIndex16  = isIndex16;
		}

		TransientVertexBuffer* createTransientVertexBuffer(uint32_t _size, const VertexLayout* _layout = NULL)
		{
			TransientVertexBuffer* tvb = NULL;

			VertexBufferHandle handle = { m_vertexBufferHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate transient vertex buffer handle.");
			if (isValid(handle) )
			{
				uint16_t stride = 0;
				VertexLayoutHandle layoutHandle = BGFX_INVALID_HANDLE;

				if (NULL != _layout)
				{
					layoutHandle = findOrCreateVertexLayout(*_layout);
					m_vertexLayoutRef.add(handle, layoutHandle, _layout->m_hash);

					stride = _layout->m_stride;
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicVertexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_size);
				uint16_t flags = BGFX_BUFFER_NONE;
				cmdbuf.write(flags);

				const uint32_t size = 0
					+ bx::alignUp<uint32_t>(sizeof(TransientVertexBuffer), 16)
					+ bx::alignUp(_size, 16)
					;
				tvb = (TransientVertexBuffer*)BX_ALIGNED_ALLOC(g_allocator, size, 16);
				tvb->data = (uint8_t *)tvb + bx::alignUp(sizeof(TransientVertexBuffer), 16);
				tvb->size = _size;
				tvb->startVertex = 0;
				tvb->stride = stride;
				tvb->handle = handle;
				tvb->layoutHandle = layoutHandle;

				setDebugName(convert(handle), "Transient Vertex Buffer");
			}

			return tvb;
		}

		void destroyTransientVertexBuffer(TransientVertexBuffer* _tvb)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyDynamicVertexBuffer);
			cmdbuf.write(_tvb->handle);

			m_submit->free(_tvb->handle);
			BX_ALIGNED_FREE(g_allocator, _tvb, 16);
		}

		BGFX_API_FUNC(void allocTransientVertexBuffer(TransientVertexBuffer* _tvb, uint32_t _num, VertexLayoutHandle _layoutHandle, uint16_t _stride) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			const uint32_t offset = m_submit->allocTransientVertexBuffer(_num, _stride);
			const TransientVertexBuffer& dvb = *m_submit->m_transientVb;

			_tvb->data         = &dvb.data[offset];
			_tvb->size         = _num * _stride;
			_tvb->startVertex  = bx::strideAlign(offset, _stride)/_stride;
			_tvb->stride       = _stride;
			_tvb->handle       = dvb.handle;
			_tvb->layoutHandle = _layoutHandle;
		}

		BGFX_API_FUNC(void allocInstanceDataBuffer(InstanceDataBuffer* _idb, uint32_t _num, uint16_t _stride) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			const uint16_t stride = bx::alignUp(_stride, 16);
			const uint32_t offset = m_submit->allocTransientVertexBuffer(_num, stride);

			TransientVertexBuffer& dvb = *m_submit->m_transientVb;
			_idb->data   = &dvb.data[offset];
			_idb->size   = _num * stride;
			_idb->offset = offset;
			_idb->num    = _num;
			_idb->stride = stride;
			_idb->handle = dvb.handle;
		}

		IndirectBufferHandle createIndirectBuffer(uint32_t _num)
		{
			BX_UNUSED(_num);
			IndirectBufferHandle handle = { m_vertexBufferHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate draw indirect buffer handle.");
			if (isValid(handle) )
			{
				uint32_t size  = _num * BGFX_CONFIG_DRAW_INDIRECT_STRIDE;
				uint16_t flags = BGFX_BUFFER_DRAW_INDIRECT;

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicVertexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(size);
				cmdbuf.write(flags);
			}

			return handle;
		}

		void destroyIndirectBuffer(IndirectBufferHandle _handle)
		{
			VertexBufferHandle handle = { _handle.idx };
			BGFX_CHECK_HANDLE("destroyDrawIndirectBuffer", m_vertexBufferHandle, handle);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyDynamicVertexBuffer);
			cmdbuf.write(handle);
			m_submit->free(handle);
		}

		BGFX_API_FUNC(ShaderHandle createShader(const Memory* _mem) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			bx::MemoryReader reader(_mem->data, _mem->size);

			bx::Error err;

			uint32_t magic;
			bx::read(&reader, magic, &err);

			if (!err.isOk() )
			{
				BX_TRACE("Couldn't read shader signature!");
				release(_mem);
				return BGFX_INVALID_HANDLE;
			}

			if (!isShaderBin(magic) )
			{
				BX_TRACE("Invalid shader signature! %c%c%c%d."
					, ( (uint8_t*)&magic)[0]
					, ( (uint8_t*)&magic)[1]
					, ( (uint8_t*)&magic)[2]
					, ( (uint8_t*)&magic)[3]
					);
				release(_mem);
				return BGFX_INVALID_HANDLE;
			}

			if (isShaderType(magic, 'C')
			&&  0 == (g_caps.supported & BGFX_CAPS_COMPUTE) )
			{
				BX_TRACE("Creating compute shader but compute is not supported!");
				release(_mem);
				return BGFX_INVALID_HANDLE;
			}

			if ( (isShaderType(magic, 'C') && isShaderVerLess(magic, 3) )
			||   (isShaderType(magic, 'F') && isShaderVerLess(magic, 5) )
			||   (isShaderType(magic, 'V') && isShaderVerLess(magic, 5) ) )
			{
				BX_TRACE("Unsupported shader binary version.");
				release(_mem);
				return BGFX_INVALID_HANDLE;
			}

			const uint32_t shaderHash = bx::hash<bx::HashMurmur2A>(_mem->data, _mem->size);
			const uint16_t idx = m_shaderHashMap.find(shaderHash);
			if (kInvalidHandle != idx)
			{
				ShaderHandle handle = { idx };
				shaderIncRef(handle);
				release(_mem);
				return handle;
			}

			uint32_t hashIn;
			bx::read(&reader, hashIn, &err);

			uint32_t hashOut;

			if (isShaderVerLess(magic, 6) )
			{
				hashOut = hashIn;
			}
			else
			{
				bx::read(&reader, hashOut, &err);
			}

			uint16_t count;
			bx::read(&reader, count, &err);

			if (!err.isOk() )
			{
				BX_TRACE("Corrupted shader binary!");
				release(_mem);
				return BGFX_INVALID_HANDLE;
			}

			ShaderHandle handle = { m_shaderHandle.alloc() };

			if (!isValid(handle) )
			{
				BX_TRACE("Failed to allocate shader handle.");
				release(_mem);
				return BGFX_INVALID_HANDLE;
			}

			bool ok = m_shaderHashMap.insert(shaderHash, handle.idx);
			BX_ASSERT(ok, "Shader already exists!"); BX_UNUSED(ok);

			ShaderRef& sr = m_shaderRef[handle.idx];
			sr.m_refCount = 1;
			sr.m_hashIn   = hashIn;
			sr.m_hashOut  = hashOut;
			sr.m_num      = 0;
			sr.m_uniforms = NULL;

			UniformHandle* uniforms = (UniformHandle*)alloca(count*sizeof(UniformHandle) );

			for (uint32_t ii = 0; ii < count; ++ii)
			{
				uint8_t nameSize = 0;
				bx::read(&reader, nameSize, &err);

				char name[256];
				bx::read(&reader, &name, nameSize, &err);
				name[nameSize] = '\0';

				uint8_t type = 0;
				bx::read(&reader, type, &err);
				type &= ~kUniformMask;

				uint8_t num;
				bx::read(&reader, num, &err);

				uint16_t regIndex;
				bx::read(&reader, regIndex, &err);

				uint16_t regCount;
				bx::read(&reader, regCount, &err);

				if (!isShaderVerLess(magic, 8) )
				{
					uint16_t texInfo;
					bx::read(&reader, texInfo);
				}

				if (!isShaderVerLess(magic, 10) )
				{
					uint16_t texFormat = 0;
					bx::read(&reader, texFormat);
				}

				PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
				if (PredefinedUniform::Count == predefined && UniformType::End != UniformType::Enum(type) )
				{
					uniforms[sr.m_num] = createUniform(name, UniformType::Enum(type), regCount);
					sr.m_num++;
				}
			}

			if (0 != sr.m_num)
			{
				uint32_t size = sr.m_num*sizeof(UniformHandle);
				sr.m_uniforms = (UniformHandle*)BX_ALLOC(g_allocator, size);
				bx::memCopy(sr.m_uniforms, uniforms, size);
			}

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateShader);
			cmdbuf.write(handle);
			cmdbuf.write(_mem);

			setDebugName(convert(handle) );

			return handle;
		}

		BGFX_API_FUNC(uint16_t getShaderUniforms(ShaderHandle _handle, UniformHandle* _uniforms, uint16_t _max) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			if (!isValid(_handle) )
			{
				BX_WARN(false, "Passing invalid shader handle to bgfx::getShaderUniforms.");
				return 0;
			}

			ShaderRef& sr = m_shaderRef[_handle.idx];
			if (NULL != _uniforms)
			{
				bx::memCopy(_uniforms, sr.m_uniforms, bx::min<uint16_t>(_max, sr.m_num)*sizeof(UniformHandle) );
			}

			return sr.m_num;
		}

		void setName(Handle _handle, const bx::StringView& _name)
		{
			char tmp[1024];
			uint16_t len = 1+(uint16_t)bx::snprintf(tmp, BX_COUNTOF(tmp), "%sH %d: %.*s", getTypeName(_handle), _handle.idx, _name.getLength(), _name.getPtr() );

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::SetName);
			cmdbuf.write(_handle);
			cmdbuf.write(len);
			cmdbuf.write(tmp, len);
		}

		void setDebugName(Handle _handle, const bx::StringView& _name = "")
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG) )
			{
				setName(_handle, _name);
			}
		}

		BGFX_API_FUNC(void setName(ShaderHandle _handle, const bx::StringView& _name) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("setName", m_shaderHandle, _handle);

			ShaderRef& sr = m_shaderRef[_handle.idx];
			sr.m_name.set(_name);

			setName(convert(_handle), _name);
		}

		BGFX_API_FUNC(void destroyShader(ShaderHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyShader", m_shaderHandle, _handle);

			if (!isValid(_handle) )
			{
				BX_WARN(false, "Passing invalid shader handle to bgfx::destroyShader.");
				return;
			}

			shaderDecRef(_handle);
		}

		void shaderTakeOwnership(ShaderHandle _handle)
		{
			shaderDecRef(_handle);
		}

		void shaderIncRef(ShaderHandle _handle)
		{
			ShaderRef& sr = m_shaderRef[_handle.idx];
			++sr.m_refCount;
		}

		void shaderDecRef(ShaderHandle _handle)
		{
			ShaderRef& sr = m_shaderRef[_handle.idx];
			int32_t refs = --sr.m_refCount;
			if (0 == refs)
			{
				bool ok = m_submit->free(_handle); BX_UNUSED(ok);
				BX_ASSERT(ok, "Shader handle %d is already destroyed!", _handle.idx);

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyShader);
				cmdbuf.write(_handle);

				if (0 != sr.m_num)
				{
					for (uint32_t ii = 0, num = sr.m_num; ii < num; ++ii)
					{
						destroyUniform(sr.m_uniforms[ii]);
					}

					BX_FREE(g_allocator, sr.m_uniforms);
					sr.m_uniforms = NULL;
					sr.m_num = 0;
				}

				m_shaderHashMap.removeByHandle(_handle.idx);
			}
		}

		BGFX_API_FUNC(ProgramHandle createProgram(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			if (!isValid(_vsh)
			||  !isValid(_fsh) )
			{
				BX_TRACE("Vertex/fragment shader is invalid (vsh %d, fsh %d).", _vsh.idx, _fsh.idx);
				return BGFX_INVALID_HANDLE;
			}

			ProgramHandle handle = { m_programHashMap.find(uint32_t(_fsh.idx<<16)|_vsh.idx) };
			if (isValid(handle) )
			{
				ProgramRef& pr = m_programRef[handle.idx];
				++pr.m_refCount;
				shaderIncRef(pr.m_vsh);
				shaderIncRef(pr.m_fsh);
			}
			else
			{
				const ShaderRef& vsr = m_shaderRef[_vsh.idx];
				const ShaderRef& fsr = m_shaderRef[_fsh.idx];
				if (vsr.m_hashOut != fsr.m_hashIn)
				{
					BX_TRACE("Vertex shader output doesn't match fragment shader input.");
					return BGFX_INVALID_HANDLE;
				}

				handle.idx = m_programHandle.alloc();

				BX_WARN(isValid(handle), "Failed to allocate program handle.");
				if (isValid(handle) )
				{
					shaderIncRef(_vsh);
					shaderIncRef(_fsh);
					ProgramRef& pr = m_programRef[handle.idx];
					pr.m_vsh = _vsh;
					pr.m_fsh = _fsh;
					pr.m_refCount = 1;

					const uint32_t key = uint32_t(_fsh.idx<<16)|_vsh.idx;
					bool ok = m_programHashMap.insert(key, handle.idx);
					BX_ASSERT(ok, "Program already exists (key: %x, handle: %3d)!", key, handle.idx); BX_UNUSED(ok);

					CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateProgram);
					cmdbuf.write(handle);
					cmdbuf.write(_vsh);
					cmdbuf.write(_fsh);
				}
			}

			if (_destroyShaders)
			{
				shaderTakeOwnership(_vsh);
				shaderTakeOwnership(_fsh);
			}

			return handle;
		}

		BGFX_API_FUNC(ProgramHandle createProgram(ShaderHandle _vsh, bool _destroyShader) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			if (!isValid(_vsh) )
			{
				BX_WARN(false, "Compute shader is invalid (vsh %d).", _vsh.idx);
				return BGFX_INVALID_HANDLE;
			}

			ProgramHandle handle = { m_programHashMap.find(_vsh.idx) };

			if (isValid(handle) )
			{
				ProgramRef& pr = m_programRef[handle.idx];
				++pr.m_refCount;
				shaderIncRef(pr.m_vsh);
			}
			else
			{
				handle.idx = m_programHandle.alloc();

				BX_WARN(isValid(handle), "Failed to allocate program handle.");
				if (isValid(handle) )
				{
					shaderIncRef(_vsh);
					ProgramRef& pr = m_programRef[handle.idx];
					pr.m_vsh = _vsh;
					ShaderHandle fsh = BGFX_INVALID_HANDLE;
					pr.m_fsh = fsh;
					pr.m_refCount = 1;

					const uint32_t key = uint32_t(_vsh.idx);
					bool ok = m_programHashMap.insert(key, handle.idx);
					BX_ASSERT(ok, "Program already exists (key: %x, handle: %3d)!", key, handle.idx); BX_UNUSED(ok);

					CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateProgram);
					cmdbuf.write(handle);
					cmdbuf.write(_vsh);
					cmdbuf.write(fsh);
				}
			}

			if (_destroyShader)
			{
				shaderTakeOwnership(_vsh);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyProgram(ProgramHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyProgram", m_programHandle, _handle);

			ProgramRef& pr = m_programRef[_handle.idx];
			shaderDecRef(pr.m_vsh);

			if (isValid(pr.m_fsh) )
			{
				shaderDecRef(pr.m_fsh);
			}

			int32_t refs = --pr.m_refCount;
			if (0 == refs)
			{
				bool ok = m_submit->free(_handle); BX_UNUSED(ok);
				BX_ASSERT(ok, "Program handle %d is already destroyed!", _handle.idx);

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyProgram);
				cmdbuf.write(_handle);

				m_programHashMap.removeByHandle(_handle.idx);
			}
		}

		BGFX_API_FUNC(TextureHandle createTexture(const Memory* _mem, uint64_t _flags, uint8_t _skip, TextureInfo* _info, BackbufferRatio::Enum _ratio, bool _immutable) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			TextureInfo ti;
			if (NULL == _info)
			{
				_info = &ti;
			}

			bimg::ImageContainer imageContainer;
			if (bimg::imageParse(imageContainer, _mem->data, _mem->size) )
			{
				calcTextureSize(*_info
					, (uint16_t)imageContainer.m_width
					, (uint16_t)imageContainer.m_height
					, (uint16_t)imageContainer.m_depth
					, imageContainer.m_cubeMap
					, imageContainer.m_numMips > 1
					, imageContainer.m_numLayers
					, TextureFormat::Enum(imageContainer.m_format)
					);
			}
			else
			{
				_info->format = TextureFormat::Unknown;
				_info->storageSize = 0;
				_info->width   = 0;
				_info->height  = 0;
				_info->depth   = 0;
				_info->numMips = 0;
				_info->bitsPerPixel = 0;
				_info->cubeMap = false;

				return BGFX_INVALID_HANDLE;
			}

			_flags |= imageContainer.m_srgb ? BGFX_TEXTURE_SRGB : 0;

			TextureHandle handle = { m_textureHandle.alloc() };
			BX_WARN(isValid(handle), "Failed to allocate texture handle.");

			if (!isValid(handle) )
			{
				release(_mem);
				return BGFX_INVALID_HANDLE;
			}

			TextureRef& ref = m_textureRef[handle.idx];
			ref.init(
				  _ratio
				, uint16_t(imageContainer.m_width)
				, uint16_t(imageContainer.m_height)
				, uint16_t(imageContainer.m_depth)
				, _info->format
				, _info->storageSize
				, imageContainer.m_numMips
				, imageContainer.m_numLayers
				, 0 != (g_caps.supported & BGFX_CAPS_TEXTURE_DIRECT_ACCESS)
				, _immutable
				, imageContainer.m_cubeMap
				, _flags
				);

			if (ref.isRt() )
			{
				m_rtMemoryUsed += int64_t(ref.m_storageSize);
			}
			else
			{
				m_textureMemoryUsed += int64_t(ref.m_storageSize);
			}

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateTexture);
			cmdbuf.write(handle);
			cmdbuf.write(_mem);
			cmdbuf.write(_flags);
			cmdbuf.write(_skip);

			setDebugName(convert(handle) );

			return handle;
		}

		BGFX_API_FUNC(void setName(TextureHandle _handle, const bx::StringView& _name) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);
			BGFX_CHECK_HANDLE("setName", m_textureHandle, _handle);

			TextureRef& ref = m_textureRef[_handle.idx];
			ref.m_name.set(_name);

			setName(convert(_handle), _name);
		}

		void setDirectAccessPtr(TextureHandle _handle, void* _ptr)
		{
			TextureRef& ref = m_textureRef[_handle.idx];
			ref.m_ptr = _ptr;
		}

		BGFX_API_FUNC(void* getDirectAccessPtr(TextureHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);
			BGFX_CHECK_HANDLE("getDirectAccessPtr", m_textureHandle, _handle);

			TextureRef& ref = m_textureRef[_handle.idx];
			return ref.m_ptr;
		}

		BGFX_API_FUNC(void destroyTexture(TextureHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyTexture", m_textureHandle, _handle);

			if (!isValid(_handle) )
			{
				BX_WARN(false, "Passing invalid texture handle to bgfx::destroyTexture");
				return;
			}

			textureDecRef(_handle);
		}

		BGFX_API_FUNC(uint32_t readTexture(TextureHandle _handle, void* _data, uint8_t _mip) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("readTexture", m_textureHandle, _handle);

			const TextureRef& ref = m_textureRef[_handle.idx];
			BX_ASSERT(ref.isReadBack(), "Can't read from texture which was not created with BGFX_TEXTURE_READ_BACK.");
			BX_ASSERT(_mip < ref.m_numMips, "Invalid mip: %d num mips:", _mip, ref.m_numMips);
			BX_UNUSED(ref);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::ReadTexture);
			cmdbuf.write(_handle);
			cmdbuf.write(_data);
			cmdbuf.write(_mip);
			return m_frames + 2;
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height, uint8_t _numMips, uint16_t _numLayers)
		{
			const TextureRef& ref = m_textureRef[_handle.idx];
			BX_ASSERT(BackbufferRatio::Count != ref.m_bbRatio, "");

			getTextureSizeFromRatio(BackbufferRatio::Enum(ref.m_bbRatio), _width, _height);
			_numMips = calcNumMips(1 < _numMips, _width, _height);

			BX_TRACE("Resize %3d: %4dx%d %s"
				, _handle.idx
				, _width
				, _height
				, bimg::getName(bimg::TextureFormat::Enum(ref.m_format) )
				);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::ResizeTexture);
			cmdbuf.write(_handle);
			cmdbuf.write(_width);
			cmdbuf.write(_height);
			cmdbuf.write(_numMips);
			cmdbuf.write(_numLayers);
		}

		void textureTakeOwnership(TextureHandle _handle)
		{
			TextureRef& ref = m_textureRef[_handle.idx];
			if (!ref.m_owned)
			{
				ref.m_owned = true;
				textureDecRef(_handle);
			}
		}

		void textureIncRef(TextureHandle _handle)
		{
			TextureRef& ref = m_textureRef[_handle.idx];
			++ref.m_refCount;
		}

		void textureDecRef(TextureHandle _handle)
		{
			TextureRef& ref = m_textureRef[_handle.idx];
			int32_t refs = --ref.m_refCount;
			if (0 == refs)
			{
				ref.m_name.clear();

				if (ref.isRt() )
				{
					m_rtMemoryUsed -= int64_t(ref.m_storageSize);
				}
				else
				{
					m_textureMemoryUsed -= int64_t(ref.m_storageSize);
				}

				bool ok = m_submit->free(_handle); BX_UNUSED(ok);
				BX_ASSERT(ok, "Texture handle %d is already destroyed!", _handle.idx);

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyTexture);
				cmdbuf.write(_handle);
			}
		}

		BGFX_API_FUNC(void updateTexture(
			  TextureHandle _handle
			, uint8_t _side
			, uint8_t _mip
			, uint16_t _x
			, uint16_t _y
			, uint16_t _z
			, uint16_t _width
			, uint16_t _height
			, uint16_t _depth
			, uint16_t _pitch
			, const Memory* _mem
		) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			const TextureRef& ref = m_textureRef[_handle.idx];
			if (ref.m_immutable)
			{
				BX_WARN(false, "Can't update immutable texture.");
				release(_mem);
				return;
			}

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::UpdateTexture);
			cmdbuf.write(_handle);
			cmdbuf.write(_side);
			cmdbuf.write(_mip);
			Rect rect;
			rect.m_x = _x;
			rect.m_y = _y;
			rect.m_width  = _width;
			rect.m_height = _height;
			cmdbuf.write(rect);
			cmdbuf.write(_z);
			cmdbuf.write(_depth);
			cmdbuf.write(_pitch);
			cmdbuf.write(_mem);
		}

		BGFX_API_FUNC(FrameBufferHandle createFrameBuffer(uint8_t _num, const Attachment* _attachment, bool _destroyTextures) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			bx::Error err;
			isFrameBufferValid(_num, _attachment, &err);
			BGFX_ERROR_ASSERT(&err);

			if (!err.isOk() )
			{
				return BGFX_INVALID_HANDLE;
			}

			FrameBufferHandle handle = { m_frameBufferHandle.alloc() };
			BX_WARN(isValid(handle), "Failed to allocate frame buffer handle.");

			if (isValid(handle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateFrameBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(false);
				cmdbuf.write(_num);

				const TextureRef& firstTexture = m_textureRef[_attachment[0].handle.idx];
				const BackbufferRatio::Enum bbRatio = BackbufferRatio::Enum(firstTexture.m_bbRatio);

				FrameBufferRef& fbr = m_frameBufferRef[handle.idx];
				if (BackbufferRatio::Count == bbRatio)
				{
					fbr.m_width  = bx::max<uint16_t>(firstTexture.m_width  >> _attachment[0].mip, 1);
					fbr.m_height = bx::max<uint16_t>(firstTexture.m_height >> _attachment[0].mip, 1);
				}

				fbr.m_window = false;
				bx::memSet(fbr.un.m_th, 0xff, sizeof(fbr.un.m_th) );

				for (uint32_t ii = 0; ii < _num; ++ii)
				{
					TextureHandle texHandle = _attachment[ii].handle;
					fbr.un.m_th[ii] = texHandle;
					textureIncRef(texHandle);
				}

				cmdbuf.write(_attachment, sizeof(Attachment) * _num);
			}

			if (_destroyTextures)
			{
				for (uint32_t ii = 0; ii < _num; ++ii)
				{
					textureTakeOwnership(_attachment[ii].handle);
				}
			}

			return handle;
		}

		BGFX_API_FUNC(FrameBufferHandle createFrameBuffer(void* _nwh, uint16_t _width, uint16_t _height, TextureFormat::Enum _format, TextureFormat::Enum _depthFormat) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			FrameBufferHandle handle = { m_frameBufferHandle.alloc() };
			BX_WARN(isValid(handle), "Failed to allocate frame buffer handle.");

			if (isValid(handle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateFrameBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(true);
				cmdbuf.write(_nwh);
				cmdbuf.write(_width);
				cmdbuf.write(_height);
				cmdbuf.write(_format);
				cmdbuf.write(_depthFormat);

				FrameBufferRef& fbr = m_frameBufferRef[handle.idx];
				fbr.m_width  = _width;
				fbr.m_height = _height;
				fbr.m_window = true;
				fbr.un.m_nwh = _nwh;
			}

			return handle;
		}

		BGFX_API_FUNC(void setName(FrameBufferHandle _handle, const bx::StringView& _name) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("setName", m_frameBufferHandle, _handle);

			FrameBufferRef& fbr = m_frameBufferRef[_handle.idx];
			fbr.m_name.set(_name);

//			setName(convert(_handle), _name);
		}

		BGFX_API_FUNC(TextureHandle getTexture(FrameBufferHandle _handle, uint8_t _attachment) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("getTexture", m_frameBufferHandle, _handle);

			const FrameBufferRef& fbr = m_frameBufferRef[_handle.idx];
			if (!fbr.m_window)
			{
				const uint32_t attachment = bx::min<uint32_t>(_attachment, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS);
				return fbr.un.m_th[attachment];
			}

			return BGFX_INVALID_HANDLE;
		}

		BGFX_API_FUNC(void destroyFrameBuffer(FrameBufferHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyFrameBuffer", m_frameBufferHandle, _handle);
			bool ok = m_submit->free(_handle); BX_UNUSED(ok);
			BX_ASSERT(ok, "Frame buffer handle %d is already destroyed!", _handle.idx);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyFrameBuffer);
			cmdbuf.write(_handle);

			FrameBufferRef& fbr = m_frameBufferRef[_handle.idx];
			fbr.m_name.clear();

			if (!fbr.m_window)
			{
				for (uint32_t ii = 0; ii < BX_COUNTOF(fbr.un.m_th); ++ii)
				{
					TextureHandle th = fbr.un.m_th[ii];
					if (isValid(th) )
					{
						textureDecRef(th);
					}
				}
			}
		}

		BGFX_API_FUNC(UniformHandle createUniform(const char* _name, UniformType::Enum _type, uint16_t _num) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			if (PredefinedUniform::Count != nameToPredefinedUniformEnum(_name) )
			{
				BX_TRACE("%s is predefined uniform name.", _name);
				return BGFX_INVALID_HANDLE;
			}

			_num  = bx::max<uint16_t>(1, _num);

			uint16_t idx = m_uniformHashMap.find(bx::hash<bx::HashMurmur2A>(_name) );
			if (kInvalidHandle != idx)
			{
				UniformHandle handle = { idx };
				UniformRef& uniform = m_uniformRef[handle.idx];
				BX_ASSERT(uniform.m_type == _type
					, "Uniform type mismatch (type: %d, expected %d)."
					, _type
					, uniform.m_type
					);

				uint32_t oldsize = g_uniformTypeSize[uniform.m_type];
				uint32_t newsize = g_uniformTypeSize[_type];

				if (oldsize < newsize
				||  uniform.m_num < _num)
				{
					uniform.m_type = oldsize < newsize ? _type : uniform.m_type;
					uniform.m_num  = bx::max<uint16_t>(uniform.m_num, _num);

					CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateUniform);
					cmdbuf.write(handle);
					cmdbuf.write(uniform.m_type);
					cmdbuf.write(uniform.m_num);
					uint8_t len = (uint8_t)bx::strLen(_name)+1;
					cmdbuf.write(len);
					cmdbuf.write(_name, len);
				}

				++uniform.m_refCount;
				return handle;
			}

			UniformHandle handle = { m_uniformHandle.alloc() };

			if (!isValid(handle) )
			{
				BX_TRACE("Failed to allocate uniform handle.");
				return BGFX_INVALID_HANDLE;
			}

			BX_TRACE("Creating uniform (handle %3d) %s", handle.idx, _name);

			UniformRef& uniform = m_uniformRef[handle.idx];
			uniform.m_name.set(_name);
			uniform.m_refCount = 1;
			uniform.m_type = _type;
			uniform.m_num  = _num;

			bool ok = m_uniformHashMap.insert(bx::hash<bx::HashMurmur2A>(_name), handle.idx);
			BX_ASSERT(ok, "Uniform already exists (name: %s)!", _name); BX_UNUSED(ok);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateUniform);
			cmdbuf.write(handle);
			cmdbuf.write(_type);
			cmdbuf.write(_num);
			uint8_t len = (uint8_t)bx::strLen(_name)+1;
			cmdbuf.write(len);
			cmdbuf.write(_name, len);

			return handle;
		}

		BGFX_API_FUNC(void getUniformInfo(UniformHandle _handle, UniformInfo& _info) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("getUniformInfo", m_uniformHandle, _handle);

			UniformRef& uniform = m_uniformRef[_handle.idx];
			bx::strCopy(_info.name, sizeof(_info.name), uniform.m_name.getPtr() );
			_info.type = uniform.m_type;
			_info.num  = uniform.m_num;
		}

		BGFX_API_FUNC(void destroyUniform(UniformHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyUniform", m_uniformHandle, _handle);

			UniformRef& uniform = m_uniformRef[_handle.idx];
			BX_ASSERT(uniform.m_refCount > 0, "Destroying already destroyed uniform %d.", _handle.idx);
			int32_t refs = --uniform.m_refCount;

			if (0 == refs)
			{
				bool ok = m_submit->free(_handle); BX_UNUSED(ok);
				BX_ASSERT(ok, "Uniform handle %d is already destroyed!", _handle.idx);

				uniform.m_name.clear();
				m_uniformHashMap.removeByHandle(_handle.idx);

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyUniform);
				cmdbuf.write(_handle);
			}
		}

		BGFX_API_FUNC(OcclusionQueryHandle createOcclusionQuery() )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			OcclusionQueryHandle handle = { m_occlusionQueryHandle.alloc() };
			if (isValid(handle) )
			{
				m_submit->m_occlusion[handle.idx] = INT32_MIN;

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::InvalidateOcclusionQuery);
				cmdbuf.write(handle);
			}

			return handle;
		}

		BGFX_API_FUNC(OcclusionQueryResult::Enum getResult(OcclusionQueryHandle _handle, int32_t* _result) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("getResult", m_occlusionQueryHandle, _handle);

			switch (m_submit->m_occlusion[_handle.idx])
			{
			case 0:         return OcclusionQueryResult::Invisible;
			case INT32_MIN: return OcclusionQueryResult::NoResult;
			default: break;
			}

			if (NULL != _result)
			{
				*_result = m_submit->m_occlusion[_handle.idx];
			}

			return OcclusionQueryResult::Visible;
		}

		BGFX_API_FUNC(void destroyOcclusionQuery(OcclusionQueryHandle _handle) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE("destroyOcclusionQuery", m_occlusionQueryHandle, _handle);

			m_freeOcclusionQueryHandle[m_numFreeOcclusionQueryHandles++] = _handle;
		}

		BGFX_API_FUNC(void requestScreenShot(FrameBufferHandle _handle, const char* _filePath) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BGFX_CHECK_HANDLE_INVALID_OK("requestScreenShot", m_frameBufferHandle, _handle);

			if (isValid(_handle) )
			{
				const FrameBufferRef& fbr = m_frameBufferRef[_handle.idx];
				if (!fbr.m_window)
				{
					BX_TRACE("requestScreenShot can be done only for window frame buffer handles (handle: %d).", _handle.idx);
					return;
				}
			}

			if (m_submit->m_numScreenShots >= BGFX_CONFIG_MAX_SCREENSHOTS)
			{
				BX_TRACE("Only %d screenshots can be requested.", BGFX_CONFIG_MAX_SCREENSHOTS);
				return;
			}

			for (uint8_t ii = 0, num = m_submit->m_numScreenShots; ii < num; ++ii)
			{
				const ScreenShot& screenShot = m_submit->m_screenShot[ii];
				if (screenShot.handle.idx == _handle.idx)
				{
					BX_TRACE("Already requested screenshot on handle %d.", _handle.idx);
					return;
				}
			}

			ScreenShot& screenShot = m_submit->m_screenShot[m_submit->m_numScreenShots++];
			screenShot.handle = _handle;
			screenShot.filePath.set(_filePath);
		}

		BGFX_API_FUNC(void setPaletteColor(uint8_t _index, const float _rgba[4]) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			BX_ASSERT(_index < BGFX_CONFIG_MAX_COLOR_PALETTE, "Color palette index out of bounds %d (max: %d)."
				, _index
				, BGFX_CONFIG_MAX_COLOR_PALETTE
				);
			bx::memCopy(&m_clearColor[_index][0], _rgba, 16);
			m_colorPaletteDirty = 2;
		}

		BGFX_API_FUNC(void setViewName(ViewId _id, const char* _name) )
		{
			BGFX_MUTEX_SCOPE(m_resourceApiLock);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::UpdateViewName);
			cmdbuf.write(_id);
			uint16_t len = (uint16_t)bx::strLen(_name)+1;
			cmdbuf.write(len);
			cmdbuf.write(_name, len);
		}

		BGFX_API_FUNC(void setViewRect(ViewId _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height) )
		{
			m_view[_id].setRect(_x, _y, _width, _height);
		}

		BGFX_API_FUNC(void setViewScissor(ViewId _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height) )
		{
			m_view[_id].setScissor(_x, _y, _width, _height);
		}

		BGFX_API_FUNC(void setViewClear(ViewId _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil) )
		{
			BX_ASSERT(bx::equal(_depth, bx::clamp(_depth, 0.0f, 1.0f), 0.0001f)
				, "Clear depth value must be between 0.0 and 1.0 (_depth %f)."
				, _depth
				);

			m_view[_id].setClear(_flags, _rgba, _depth, _stencil);
		}

		BGFX_API_FUNC(void setViewClear(ViewId _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7) )
		{
			BX_ASSERT(bx::equal(_depth, bx::clamp(_depth, 0.0f, 1.0f), 0.0001f)
				, "Clear depth value must be between 0.0 and 1.0 (_depth %f)."
				, _depth
				);

			m_view[_id].setClear(_flags, _depth, _stencil, _0, _1, _2, _3, _4, _5, _6, _7);
		}

		BGFX_API_FUNC(void setViewMode(ViewId _id, ViewMode::Enum _mode) )
		{
			m_view[_id].setMode(_mode);
		}

		BGFX_API_FUNC(void setViewFrameBuffer(ViewId _id, FrameBufferHandle _handle) )
		{
			BGFX_CHECK_HANDLE_INVALID_OK("setViewFrameBuffer", m_frameBufferHandle, _handle);
			m_view[_id].setFrameBuffer(_handle);
		}

		BGFX_API_FUNC(void setViewTransform(ViewId _id, const void* _view, const void* _proj) )
		{
			m_view[_id].setTransform(_view, _proj);
		}

		BGFX_API_FUNC(void resetView(ViewId _id) )
		{
			m_view[_id].reset();
		}

		BGFX_API_FUNC(void setViewOrder(ViewId _id, uint16_t _num, const ViewId* _order) )
		{
			const uint32_t num = bx::min(_id + _num, BGFX_CONFIG_MAX_VIEWS) - _id;
			if (NULL == _order)
			{
				for (uint32_t ii = 0; ii < num; ++ii)
				{
					ViewId id = ViewId(ii+_id);
					m_viewRemap[id] = id;
				}
			}
			else
			{
				bx::memCopy(&m_viewRemap[_id], _order, num*sizeof(ViewId) );
			}
		}

		BGFX_API_FUNC(Encoder* begin(bool _forThread) );

		BGFX_API_FUNC(void end(Encoder* _encoder) );

		BGFX_API_FUNC(uint32_t frame(bool _capture = false) );

		uint32_t getSeqIncr(ViewId _id)
		{
			return bx::atomicFetchAndAdd<uint32_t>(&m_seq[_id], 1);
		}

		void dumpViewStats();
		void freeDynamicBuffers();
		void freeAllHandles(Frame* _frame);
		void frameNoRenderWait();
		void swap();

		// render thread
		void flip();
		RenderFrame::Enum renderFrame(int32_t _msecs = -1);
		void flushTextureUpdateBatch(CommandBuffer& _cmdbuf);
		void rendererExecCommands(CommandBuffer& _cmdbuf);

#if BGFX_CONFIG_MULTITHREADED
		void apiSemPost()
		{
			if (!m_singleThreaded)
			{
				m_apiSem.post();
			}
		}

		bool apiSemWait(int32_t _msecs = -1)
		{
			if (m_singleThreaded)
			{
				return true;
			}

			BGFX_PROFILER_SCOPE("bgfx/API thread wait", 0xff2040ff);
			int64_t start = bx::getHPCounter();
			bool ok = m_apiSem.wait(_msecs);
			if (ok)
			{
				m_render->m_waitSubmit = bx::getHPCounter()-start;
				m_submit->m_perfStats.waitSubmit = m_submit->m_waitSubmit;
				return true;
			}

			return false;
		}

		void renderSemPost()
		{
			if (!m_singleThreaded)
			{
				m_renderSem.post();
			}
		}

		void renderSemWait()
		{
			if (!m_singleThreaded)
			{
				BGFX_PROFILER_SCOPE("bgfx/Render thread wait", 0xff2040ff);
				int64_t start = bx::getHPCounter();
				bool ok = m_renderSem.wait();
				BX_ASSERT(ok, "Semaphore wait failed."); BX_UNUSED(ok);
				m_submit->m_waitRender = bx::getHPCounter() - start;
				m_submit->m_perfStats.waitRender = m_submit->m_waitRender;
			}
		}

		void encoderApiWait()
		{
			uint16_t numEncoders = m_encoderHandle->getNumHandles();

			for (uint16_t ii = 1; ii < numEncoders; ++ii)
			{
				m_encoderEndSem.wait();
			}

			for (uint16_t ii = 0; ii < numEncoders; ++ii)
			{
				uint16_t idx = m_encoderHandle->getHandleAt(ii);
				m_encoderStats[ii].cpuTimeBegin = m_encoder[idx].m_cpuTimeBegin;
				m_encoderStats[ii].cpuTimeEnd   = m_encoder[idx].m_cpuTimeEnd;
			}

			m_submit->m_perfStats.numEncoders = uint8_t(numEncoders);

			m_encoderHandle->reset();
			uint16_t idx = m_encoderHandle->alloc();
			BX_ASSERT(0 == idx, "Internal encoder handle is not 0 (idx %d).", idx); BX_UNUSED(idx);
		}

		bx::Semaphore m_renderSem;
		bx::Semaphore m_apiSem;
		bx::Semaphore m_encoderEndSem;
		bx::Mutex     m_encoderApiLock;
		bx::Mutex     m_resourceApiLock;
		bx::Thread    m_thread;
#else
		void apiSemPost()
		{
		}

		bool apiSemWait(int32_t _msecs = -1)
		{
			BX_UNUSED(_msecs);
			return true;
		}

		void renderSemPost()
		{
		}

		void renderSemWait()
		{
		}

		void encoderApiWait()
		{
			m_encoderStats[0].cpuTimeBegin = m_encoder[0].m_cpuTimeBegin;
			m_encoderStats[0].cpuTimeEnd   = m_encoder[0].m_cpuTimeEnd;
			m_submit->m_perfStats.numEncoders = 1;
		}
#endif // BGFX_CONFIG_MULTITHREADED

		EncoderStats* m_encoderStats;
		Encoder*      m_encoder0;
		EncoderImpl*  m_encoder;
		uint32_t      m_numEncoders;
		bx::HandleAlloc* m_encoderHandle;

		Frame  m_frame[1+(BGFX_CONFIG_MULTITHREADED ? 1 : 0)];
		Frame* m_render;
		Frame* m_submit;

		uint64_t m_tempKeys[BGFX_CONFIG_MAX_DRAW_CALLS];
		RenderItemCount m_tempValues[BGFX_CONFIG_MAX_DRAW_CALLS];

		IndexBuffer  m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBuffer m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];

		DynamicIndexBuffer  m_dynamicIndexBuffers[BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS];
		DynamicVertexBuffer m_dynamicVertexBuffers[BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS];

		uint16_t m_numFreeDynamicIndexBufferHandles;
		uint16_t m_numFreeDynamicVertexBufferHandles;
		uint16_t m_numFreeOcclusionQueryHandles;
		DynamicIndexBufferHandle  m_freeDynamicIndexBufferHandle[BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS];
		DynamicVertexBufferHandle m_freeDynamicVertexBufferHandle[BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS];
		OcclusionQueryHandle      m_freeOcclusionQueryHandle[BGFX_CONFIG_MAX_OCCLUSION_QUERIES];

		NonLocalAllocator m_dynIndexBufferAllocator;
		bx::HandleAllocT<BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS> m_dynamicIndexBufferHandle;
		NonLocalAllocator m_dynVertexBufferAllocator;
		bx::HandleAllocT<BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS> m_dynamicVertexBufferHandle;

		bx::HandleAllocT<BGFX_CONFIG_MAX_INDEX_BUFFERS> m_indexBufferHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_VERTEX_LAYOUTS > m_layoutHandle;

		bx::HandleAllocT<BGFX_CONFIG_MAX_VERTEX_BUFFERS> m_vertexBufferHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_SHADERS> m_shaderHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_PROGRAMS> m_programHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_TEXTURES> m_textureHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_FRAME_BUFFERS> m_frameBufferHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_UNIFORMS> m_uniformHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_OCCLUSION_QUERIES> m_occlusionQueryHandle;

		typedef bx::HandleHashMapT<BGFX_CONFIG_MAX_UNIFORMS*2> UniformHashMap;
		UniformHashMap m_uniformHashMap;
		UniformRef     m_uniformRef[BGFX_CONFIG_MAX_UNIFORMS];

		typedef bx::HandleHashMapT<BGFX_CONFIG_MAX_SHADERS*2> ShaderHashMap;
		ShaderHashMap m_shaderHashMap;
		ShaderRef     m_shaderRef[BGFX_CONFIG_MAX_SHADERS];

		typedef bx::HandleHashMapT<BGFX_CONFIG_MAX_PROGRAMS*2> ProgramHashMap;
		ProgramHashMap m_programHashMap;
		ProgramRef     m_programRef[BGFX_CONFIG_MAX_PROGRAMS];

		TextureRef      m_textureRef[BGFX_CONFIG_MAX_TEXTURES];
		FrameBufferRef  m_frameBufferRef[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		VertexLayoutRef m_vertexLayoutRef;

		ViewId m_viewRemap[BGFX_CONFIG_MAX_VIEWS];
		uint32_t m_seq[BGFX_CONFIG_MAX_VIEWS];
		View m_view[BGFX_CONFIG_MAX_VIEWS];

		float m_clearColor[BGFX_CONFIG_MAX_COLOR_PALETTE][4];

		uint8_t m_colorPaletteDirty;

		Init     m_init;
		int64_t  m_frameTimeLast;
		uint32_t m_frames;
		uint32_t m_debug;

		int64_t m_rtMemoryUsed;
		int64_t m_textureMemoryUsed;

		TextVideoMemBlitter m_textVideoMemBlitter;
		ClearQuad m_clearQuad;

		RendererContextI* m_renderCtx;

		bool m_rendererInitialized;
		bool m_exit;
		bool m_flipAfterRender;
		bool m_singleThreaded;
		bool m_flipped;

		typedef UpdateBatchT<256> TextureUpdateBatch;
		BX_ALIGN_DECL_CACHE_LINE(TextureUpdateBatch m_textureUpdateBatch);
	};

#undef BGFX_API_FUNC

} // namespace bgfx

#endif // BGFX_P_H_HEADER_GUARD
