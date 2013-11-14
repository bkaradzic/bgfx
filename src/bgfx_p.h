/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_P_H_HEADER_GUARD
#define BGFX_P_H_HEADER_GUARD

#include "bgfx.h"
#include "config.h"

#include <inttypes.h>
#include <stdarg.h> // va_list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>

namespace bgfx
{
	void fatal(Fatal::Enum _code, const char* _format, ...);
	void dbgPrintf(const char* _format, ...);
}

#define _BX_TRACE(_format, ...) \
				do { \
					bgfx::dbgPrintf(BX_FILE_LINE_LITERAL "BGFX " _format "\n", ##__VA_ARGS__); \
				} while(0)

#define _BX_WARN(_condition, _format, ...) \
				do { \
					if (!(_condition) ) \
					{ \
						BX_TRACE("WARN " _format, ##__VA_ARGS__); \
					} \
				} while(0)

#define _BX_CHECK(_condition, _format, ...) \
				do { \
					if (!(_condition) ) \
					{ \
						BX_TRACE("CHECK " _format, ##__VA_ARGS__); \
						bgfx::fatal(bgfx::Fatal::DebugCheck, _format, ##__VA_ARGS__); \
					} \
				} while(0)

#if BGFX_CONFIG_DEBUG
#	define BX_TRACE _BX_TRACE
#	define BX_WARN  _BX_WARN
#	define BX_CHECK _BX_CHECK
#	define BX_CONFIG_ALLOCATOR_DEBUG 1
#endif // BGFX_CONFIG_DEBUG

#define BGFX_FATAL(_condition, _err, _format, ...) \
			do { \
				if (!(_condition) ) \
				{ \
					fatal(_err, _format, ##__VA_ARGS__); \
				} \
			} while(0)

#include <bx/bx.h>
#include <bx/debug.h>
#include <bx/blockalloc.h>
#include <bx/endian.h>
#include <bx/handlealloc.h>
#include <bx/hash.h>
#include <bx/radixsort.h>
#include <bx/ringbuffer.h>
#include <bx/uint32_t.h>
#include <bx/readerwriter.h>
#include <bx/allocator.h>
#include <bx/string.h>
#include <bx/os.h>

#include "image.h"

#define BGFX_CHUNK_MAGIC_FSH BX_MAKEFOURCC('F', 'S', 'H', 0x1)
#define BGFX_CHUNK_MAGIC_TEX BX_MAKEFOURCC('T', 'E', 'X', 0x0)
#define BGFX_CHUNK_MAGIC_VSH BX_MAKEFOURCC('V', 'S', 'H', 0x1)

#include <list> // mingw wants it to be before tr1/unordered_*...

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
namespace stl = tinystl;
#else
#	include <string>
#	include <unordered_map>
#	include <unordered_set>
namespace stl
{
	using namespace std;
	using namespace std::tr1;
}
#endif // BGFX_CONFIG_USE_TINYSTL

#if BX_PLATFORM_ANDROID
#	include <android/native_window.h>
#elif BX_PLATFORM_WINDOWS
#	include <windows.h>
#elif BX_PLATFORM_XBOX360
#	include <malloc.h>
#	include <xtl.h>
#endif // BX_PLATFORM_*

#include <bx/cpu.h>
#include <bx/thread.h>
#include <bx/timer.h>

#include "vertexdecl.h"

#define BGFX_DEFAULT_WIDTH  1280
#define BGFX_DEFAULT_HEIGHT 720

#define BGFX_STATE_TEX0      UINT64_C(0x0100000000000000)
#define BGFX_STATE_TEX1      UINT64_C(0x0200000000000000)
#define BGFX_STATE_TEX2      UINT64_C(0x0400000000000000)
#define BGFX_STATE_TEX3      UINT64_C(0x0800000000000000)
#define BGFX_STATE_TEX4      UINT64_C(0x1000000000000000)
#define BGFX_STATE_TEX5      UINT64_C(0x2000000000000000)
#define BGFX_STATE_TEX6      UINT64_C(0x4000000000000000)
#define BGFX_STATE_TEX7      UINT64_C(0x8000000000000000)
#define BGFX_STATE_TEX_MASK  UINT64_C(0xff00000000000000)
#define BGFX_STATE_TEX_COUNT 8

#define BGFX_SAMPLER_DEFAULT_FLAGS      UINT32_C(0x10000000)
#define BGFX_SAMPLER_TEXTURE            UINT32_C(0x00000000)
#define BGFX_SAMPLER_RENDERTARGET_COLOR UINT32_C(0x40000000)
#define BGFX_SAMPLER_RENDERTARGET_DEPTH UINT32_C(0x80000000)
#define BGFX_SAMPLER_TYPE_MASK          UINT32_C(0xc0000000)

#if BGFX_CONFIG_RENDERER_DIRECT3D9
#	define BGFX_RENDERER_NAME "Direct3D 9"
#elif BGFX_CONFIG_RENDERER_DIRECT3D11
#	define BGFX_RENDERER_NAME "Direct3D 11"
#elif BGFX_CONFIG_RENDERER_OPENGL
#	if BGFX_CONFIG_RENDERER_OPENGL >= 31
#		define BGFX_RENDERER_NAME "OpenGL 3.1"
#	else
#		define BGFX_RENDERER_NAME "OpenGL 2.1"
#	endif // BGFX_CONFIG_RENDERER_OPENGL
#elif BGFX_CONFIG_RENDERER_OPENGLES2
#	define BGFX_RENDERER_NAME "OpenGL ES 2"
#elif BGFX_CONFIG_RENDERER_OPENGLES3
#	define BGFX_RENDERER_NAME "OpenGL ES 3"
#endif // BGFX_CONFIG_RENDERER_

namespace bgfx
{
#if BX_PLATFORM_ANDROID
	extern ::ANativeWindow* g_bgfxAndroidWindow;
#elif BX_PLATFORM_IOS
	extern void* g_bgfxEaglLayer;
#elif BX_PLATFORM_OSX
	extern void* g_bgfxNSWindow;
#elif BX_PLATFORM_WINDOWS
	extern ::HWND g_bgfxHwnd;
#endif // BX_PLATFORM_*

	struct Clear
	{
		uint32_t m_rgba;
		float m_depth;
		uint8_t m_stencil;
		uint8_t m_flags;
	};

	struct Rect
	{
		void clear()
		{
			m_x =
			m_y =
			m_width =
			m_height = 0;
		}

		bool isZero() const
		{
			uint64_t ui64 = *( (uint64_t*)this);
			return UINT64_C(0) == ui64;
		}

		void intersect(const Rect& _a, const Rect& _b)
		{
			const uint16_t sx = bx::uint16_max(_a.m_x, _b.m_x);
			const uint16_t sy = bx::uint16_max(_a.m_y, _b.m_y);
			const uint16_t ex = bx::uint16_min(_a.m_x + _a.m_width,  _b.m_x + _b.m_width );
			const uint16_t ey = bx::uint16_min(_a.m_y + _a.m_height, _b.m_y + _b.m_height);
			m_x = sx;
			m_y = sy;
			m_width  = (uint16_t)bx::uint32_satsub(ex, sx);
			m_height = (uint16_t)bx::uint32_satsub(ey, sy);
		}

		uint16_t m_x;
		uint16_t m_y;
		uint16_t m_width;
		uint16_t m_height;
	};

	struct TextureCreate
	{
		uint32_t m_flags;
		uint16_t m_width;
		uint16_t m_height;
		uint16_t m_sides;
		uint16_t m_depth;
		uint8_t m_numMips;
		uint8_t m_format;
		bool m_cubeMap;
		const Memory* m_mem;
	};

	extern const uint32_t g_uniformTypeSize[UniformType::Count+1];
	extern CallbackI* g_callback;
	extern bx::ReallocatorI* g_allocator;
	extern Caps g_caps;

	void setGraphicsDebuggerPresent(bool _present);
	bool isGraphicsDebuggerPresent();
	void release(const Memory* _mem);
	const char* getAttribName(Attrib::Enum _attr);
	bool renderFrame();

	inline uint32_t gcd(uint32_t _a, uint32_t _b)
	{
		do
		{
			uint32_t tmp = _a % _b;
			_a = _b;
			_b = tmp;
		}
		while (_b);

		return _a;
	}

	inline uint32_t lcm(uint32_t _a, uint32_t _b)
	{
		return _a * (_b / gcd(_a, _b) );
	}

	inline uint32_t strideAlign(uint32_t _offset, uint32_t _stride)
	{
		using namespace bx;
		const uint32_t mod    = uint32_mod(_offset, _stride);
		const uint32_t add    = uint32_sub(_stride, mod);
		const uint32_t mask   = uint32_cmpeq(mod, 0);
		const uint32_t tmp    = uint32_selb(mask, 0, add);
		const uint32_t result = uint32_add(_offset, tmp);

		return result;
	}

	inline uint32_t strideAlign16(uint32_t _offset, uint32_t _stride)
	{
		uint32_t align = lcm(16, _stride);
		return _offset+align-(_offset%align);
	}

	inline uint32_t strideAlign256(uint32_t _offset, uint32_t _stride)
	{
		uint32_t align = lcm(256, _stride);
		return _offset+align-(_offset%align);
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

	void dump(const VertexDecl& _decl);

	struct TextVideoMem
	{
		TextVideoMem()
			: m_mem(NULL)
			, m_size(0)
			, m_width(0)
			, m_height(0)
			, m_small(false)
		{
			resize();
			clear();
		}

		~TextVideoMem()
		{
			BX_FREE(g_allocator, m_mem);
		}

		void resize(bool _small = false, uint16_t _width = BGFX_DEFAULT_WIDTH, uint16_t _height = BGFX_DEFAULT_HEIGHT)
		{
			uint32_t width = bx::uint32_max(1, _width/8);
			uint32_t height = bx::uint32_max(1, _height/(_small ? 8 : 16) );

			if (NULL == m_mem
			||  m_width != width
			||  m_height != height
			||  m_small != _small)
			{
				m_small = _small;
				m_width = (uint16_t)width;
				m_height = (uint16_t)height;

				uint32_t size = m_size;
				m_size = m_width * m_height * 2;

				m_mem = (uint8_t*)BX_REALLOC(g_allocator, m_mem, m_size);

				if (size < m_size)
				{
					memset(&m_mem[size], 0, m_size-size);
				}
			}
		}

		void clear(uint8_t _attr = 0)
		{
			uint8_t* mem = m_mem;
			for (uint32_t ii = 0, num = m_size/2; ii < num; ++ii)
			{
				mem[0] = 0;
				mem[1] = _attr;
				mem += 2;
			}
		}

		void printfVargs(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList)
		{
			if (_x < m_width && _y < m_height)
			{
				char* temp = (char*)alloca(m_width);

				uint32_t num = bx::vsnprintf(temp, m_width, _format, _argList);

				uint8_t* mem = &m_mem[(_y*m_width+_x)*2];
				for (uint32_t ii = 0, xx = _x; ii < num && xx < m_width; ++ii, ++xx)
				{
					mem[0] = temp[ii];
					mem[1] = _attr;
					mem += 2;
				}
			}
		}

		void printf(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...)
		{
			va_list argList;
			va_start(argList, _format);
			printfVargs(_x, _y, _attr, _format, argList);
			va_end(argList);
		}

		uint8_t* m_mem;
		uint32_t m_size;
		uint16_t m_width;
		uint16_t m_height;
		bool m_small;
	};

	struct TextVideoMemBlitter
	{
		void init();
		void shutdown();

		void blit(const TextVideoMem* _mem)
		{
			blit(*_mem);
		}

		void blit(const TextVideoMem& _mem);
		void setup();
		void render(uint32_t _numIndices);

		TextureHandle m_texture;
		TransientVertexBuffer* m_vb;
		TransientIndexBuffer* m_ib;
		VertexDecl m_decl;
		ProgramHandle m_program;
		bool m_init;
	};

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
				bx::radixSort32(m_keys, tempKeys, m_values, tempValues, m_num);
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
		void init();
		void shutdown();
		void clear(const Rect& _rect, const Clear& _clear, uint32_t _height = 0);

		TransientVertexBuffer* m_vb;
		IndexBufferHandle m_ib;
		VertexDecl m_decl;
		ProgramHandle m_program;
	};

	struct PredefinedUniform
	{
		enum Enum
		{
			ViewRect,
			ViewTexel,
			View,
			ViewProj,
			ViewProjX,
			Model,
			ModelView,
			ModelViewProj,
			ModelViewProjX,
			AlphaRef,
			Count
		};

		uint32_t m_loc;
		uint16_t m_count;
		uint8_t m_type;
	};

	const char* getPredefinedUniformName(PredefinedUniform::Enum _enum);
	PredefinedUniform::Enum nameToPredefinedUniformEnum(const char* _name);

	struct CommandBuffer
	{
		CommandBuffer()
			: m_pos(0)
			, m_size(BGFX_CONFIG_MAX_COMMAND_BUFFER_SIZE)
		{
			finish();
		}

		enum Enum
		{
			RendererInit,
			RendererShutdownBegin,
			CreateVertexDecl,
			CreateIndexBuffer,
			CreateVertexBuffer,
			CreateDynamicIndexBuffer,
			UpdateDynamicIndexBuffer,
			CreateDynamicVertexBuffer,
			UpdateDynamicVertexBuffer,
			CreateVertexShader,
			CreateFragmentShader,
			CreateProgram,
			CreateTexture,
			UpdateTexture,
			CreateRenderTarget,
			CreateUniform,
			UpdateViewName,
			End,
			RendererShutdownEnd,
			DestroyVertexDecl,
			DestroyIndexBuffer,
			DestroyVertexBuffer,
			DestroyDynamicIndexBuffer,
			DestroyDynamicVertexBuffer,
			DestroyVertexShader,
			DestroyFragmentShader,
			DestroyProgram,
			DestroyTexture,
			DestroyRenderTarget,
			DestroyUniform,
			SaveScreenShot,
		};

		void write(const void* _data, uint32_t _size)
		{
			BX_CHECK(m_size == BGFX_CONFIG_MAX_COMMAND_BUFFER_SIZE, "Called write outside start/finish?");
			BX_CHECK(m_pos < m_size, "");
			memcpy(&m_buffer[m_pos], _data, _size);
			m_pos += _size;
		}

		template<typename Type>
		void write(const Type& _in)
		{
			write(reinterpret_cast<const uint8_t*>(&_in), sizeof(Type) );
		}

		void read(void* _data, uint32_t _size)
		{
			BX_CHECK(m_pos < m_size, "");
			memcpy(_data, &m_buffer[m_pos], _size);
			m_pos += _size;
		}

		template<typename Type>
		void read(Type& _in)
		{
			read(reinterpret_cast<uint8_t*>(&_in), sizeof(Type) );
		}

		const uint8_t* skip(uint32_t _size)
		{
			BX_CHECK(m_pos < m_size, "");
			const uint8_t* result = &m_buffer[m_pos];
			m_pos += _size;
			return result;
		}

		void reset()
		{
			m_pos = 0;
		}

		void start()
		{
			m_pos = 0;
			m_size = BGFX_CONFIG_MAX_COMMAND_BUFFER_SIZE;
		}

		void finish()
		{
			uint8_t cmd = End;
			write(cmd);
			m_size = m_pos;
			m_pos = 0;
		}

		uint32_t m_pos;
		uint32_t m_size;
		uint8_t m_buffer[BGFX_CONFIG_MAX_COMMAND_BUFFER_SIZE];

	private:
		CommandBuffer(const CommandBuffer&);
		void operator=(const CommandBuffer&);
	};

	struct SortKey
	{
		uint64_t encode()
		{
			// |               3               2               1               0|
			// |fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210|
			// |             vvvvvsssssssssssttmmmmmmmmmdddddddddddddddddddddddd|
			// |                 ^          ^ ^        ^                       ^|
			// |                 |          | |        |                       ||

			uint64_t tmp0 = m_depth;
			uint64_t tmp1 = uint64_t(m_program)<<0x18;
			uint64_t tmp2 = uint64_t(m_trans)<<0x21;
			uint64_t tmp3 = uint64_t(m_seq)<<0x23;
			uint64_t tmp4 = uint64_t(m_view)<<0x2e;
			uint64_t key = tmp0|tmp1|tmp2|tmp3|tmp4;
			return key;
		}

		void decode(uint64_t _key)
		{
			m_depth = _key&0xffffffff;
			m_program = (_key>>0x18)&(BGFX_CONFIG_MAX_PROGRAMS-1);
			m_trans = (_key>>0x21)&0x3;
			m_seq = (_key>>0x23)&0x7ff;
			m_view = (_key>>0x2e)&(BGFX_CONFIG_MAX_VIEWS-1);
		}

		void reset()
		{
			m_depth = 0;
			m_program = 0;
			m_seq = 0;
			m_view = 0;
			m_trans = 0;
		}

		int32_t m_depth;
		uint16_t m_program;
		uint16_t m_seq;
		uint8_t m_view;
		uint8_t m_trans;
	};

	BX_ALIGN_STRUCT_16(struct) Matrix4
	{
		float val[16];

		void setIdentity()
		{
			memset(val, 0, sizeof(val) );
			val[0] = val[5] = val[10] = val[15] = 1.0f;
		}
	};

	void mtxMul(float* __restrict _result, const float* __restrict _a, const float* __restrict _b);
	void mtxOrtho(float* _result, float _left, float _right, float _bottom, float _top, float _near, float _far);

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

		uint32_t add(const void* _mtx, uint16_t _num)
		{
			if (NULL != _mtx)
			{
				BX_CHECK(m_num+_num < BGFX_CONFIG_MAX_MATRIX_CACHE, "Matrix cache overflow. %d (max: %d)", m_num+_num, BGFX_CONFIG_MAX_MATRIX_CACHE);

				uint32_t num = bx::uint32_min(BGFX_CONFIG_MAX_MATRIX_CACHE-m_num, _num);
				uint32_t first = m_num;
				memcpy(&m_cache[m_num], _mtx, sizeof(Matrix4)*num);
				m_num += num;
				return first;
			}

			return 0;
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
			BX_CHECK(m_num+1 < BGFX_CONFIG_MAX_RECT_CACHE, "Rect cache overflow. %d (max: %d)", m_num, BGFX_CONFIG_MAX_RECT_CACHE);

			uint32_t first = m_num;
			Rect& rect = m_cache[m_num];

			rect.m_x = _x;
			rect.m_y = _y;
			rect.m_width = _width;
			rect.m_height = _height;

			m_num++;
			return first;
		}

		Rect m_cache[BGFX_CONFIG_MAX_RECT_CACHE];
		uint32_t m_num;
	};

	struct Sampler
	{
		uint32_t m_flags;
		uint16_t m_idx;
	};

#define CONSTANT_OPCODE_TYPE_SHIFT 27
#define CONSTANT_OPCODE_TYPE_MASK  UINT32_C(0xf8000000)
#define CONSTANT_OPCODE_LOC_SHIFT  11
#define CONSTANT_OPCODE_LOC_MASK   UINT32_C(0x07fff800)
#define CONSTANT_OPCODE_NUM_SHIFT  1
#define CONSTANT_OPCODE_NUM_MASK   UINT32_C(0x000007fe)
#define CONSTANT_OPCODE_COPY_SHIFT 0
#define CONSTANT_OPCODE_COPY_MASK  UINT32_C(0x00000001)

#define BGFX_UNIFORM_FRAGMENTBIT UINT8_C(0x10)

	class ConstantBuffer
	{
	public:
		static ConstantBuffer* create(uint32_t _size)
		{
			uint32_t size = BX_ALIGN_16(bx::uint32_max(_size, sizeof(ConstantBuffer) ) );
			void* data = BX_ALLOC(g_allocator, size);
			return ::new(data) ConstantBuffer(_size);
		}

		static void destroy(ConstantBuffer* _constantBuffer)
		{
			_constantBuffer->~ConstantBuffer();
			BX_FREE(g_allocator, _constantBuffer);
		}

		static uint32_t encodeOpcode(UniformType::Enum _type, uint16_t _loc, uint16_t _num, uint16_t _copy)
		{
			const uint32_t type = _type << CONSTANT_OPCODE_TYPE_SHIFT;
			const uint32_t loc  = _loc  << CONSTANT_OPCODE_LOC_SHIFT;
			const uint32_t num  = _num  << CONSTANT_OPCODE_NUM_SHIFT;
			const uint32_t copy = _copy << CONSTANT_OPCODE_COPY_SHIFT;
			return type|loc|num|copy;
		}

		static void decodeOpcode(uint32_t _opcode, UniformType::Enum& _type, uint16_t& _loc, uint16_t& _num, uint16_t& _copy)
		{
			const uint32_t type = (_opcode&CONSTANT_OPCODE_TYPE_MASK) >> CONSTANT_OPCODE_TYPE_SHIFT;
			const uint32_t loc  = (_opcode&CONSTANT_OPCODE_LOC_MASK)  >> CONSTANT_OPCODE_LOC_SHIFT;
			const uint32_t num  = (_opcode&CONSTANT_OPCODE_NUM_MASK)  >> CONSTANT_OPCODE_NUM_SHIFT;
			const uint32_t copy = (_opcode&CONSTANT_OPCODE_COPY_MASK) >> CONSTANT_OPCODE_COPY_SHIFT;

			_type = (UniformType::Enum)(type);
			_copy = (uint16_t)copy;
			_num = (uint16_t)num;
			_loc = (uint16_t)loc;
		}

		void write(const void* _data, uint32_t _size)
		{
			BX_CHECK(m_pos + _size < m_size, "Write would go out of bounds. pos %d + size %d > max size: %d).", m_pos, _size, m_size);

			if (m_pos + _size < m_size)
			{
				memcpy(&m_buffer[m_pos], _data, _size);
				m_pos += _size;
			}
		}

		void write(uint32_t _value)
		{
			write(&_value, sizeof(uint32_t) );
		}

		const char* read(uint32_t _size)
		{
			BX_CHECK(m_pos < m_size, "Out of bounds %d (size: %d).", m_pos, m_size);
			const char* result = &m_buffer[m_pos];
			m_pos += _size;
			return result;
		}

		uint32_t read()
		{
			const char* result = read(sizeof(uint32_t) );
			return *( (uint32_t*)result);
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
		void writeUniformRef(UniformType::Enum _type, uint16_t _loc, const void* _value, uint16_t _num = 1);
		void writeMarker(const char* _marker);
		void commit();

	private:
		ConstantBuffer(uint32_t _size)
			: m_size(_size-sizeof(m_buffer) )
			, m_pos(0)
		{
			finish();
		}

		~ConstantBuffer()
		{
		}

		uint32_t m_size;
		uint32_t m_pos;
		char m_buffer[8];
	};

	typedef const void* (*UniformFn)(const void* _data);

	struct UniformInfo
	{
		const void* m_data;
		UniformFn m_func;
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

 		const UniformInfo* find(const char* _name) const
 		{
			UniformHashMap::const_iterator it = m_uniforms.find(_name);
			if (it != m_uniforms.end() )
			{
				return &it->second;
			}

 			return NULL;
 		}

		const UniformInfo& add(const char* _name, const void* _data, UniformFn _func = NULL)
		{
			UniformHashMap::iterator it = m_uniforms.find(_name);
			if (it == m_uniforms.end() )
			{
				UniformInfo info;
				info.m_data = _data;
				info.m_func = _func;

				stl::pair<UniformHashMap::iterator, bool> result = m_uniforms.insert(UniformHashMap::value_type(_name, info) );
				return result.first->second;
			}

			return it->second;
		}

 	private:
 		typedef stl::unordered_map<stl::string, UniformInfo> UniformHashMap;
 		UniformHashMap m_uniforms;
 	};

	struct RenderState
	{
		void reset()
		{
			m_constEnd = 0;
			clear();
		}

		void clear()
		{
			m_constBegin = m_constEnd;
			m_flags = BGFX_STATE_DEFAULT;
			m_stencil = packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT);
			m_rgba = UINT32_MAX;
			m_matrix = 0;
			m_startIndex = 0;
			m_numIndices = UINT32_MAX;
			m_startVertex = 0;
			m_numVertices = UINT32_MAX;
			m_instanceDataOffset = 0;
			m_instanceDataStride = 0;
			m_numInstances = 1;
			m_num = 1;
			m_scissor = UINT16_MAX;
			m_vertexBuffer.idx = invalidHandle;
			m_vertexDecl.idx = invalidHandle;
			m_indexBuffer.idx = invalidHandle;
			m_instanceDataBuffer.idx = invalidHandle;

			for (uint32_t ii = 0; ii < BGFX_STATE_TEX_COUNT; ++ii)
			{
				m_sampler[ii].m_idx = invalidHandle;
				m_sampler[ii].m_flags = BGFX_SAMPLER_TEXTURE;
			}
		}

		uint64_t m_flags;
		uint64_t m_stencil;
		uint32_t m_rgba;
		uint32_t m_constBegin;
		uint32_t m_constEnd;
		uint32_t m_matrix;
		uint32_t m_startIndex;
		uint32_t m_numIndices;
		uint32_t m_startVertex;
		uint32_t m_numVertices;
		uint32_t m_instanceDataOffset;
		uint16_t m_instanceDataStride;
		uint16_t m_numInstances;
		uint16_t m_num;
		uint16_t m_scissor;

		VertexBufferHandle m_vertexBuffer;
		VertexDeclHandle m_vertexDecl;
		IndexBufferHandle m_indexBuffer;
		VertexBufferHandle m_instanceDataBuffer;
		Sampler m_sampler[BGFX_STATE_TEX_COUNT];
	};

	struct Resolution
	{
		Resolution()
			: m_width(BGFX_DEFAULT_WIDTH)
			, m_height(BGFX_DEFAULT_HEIGHT)
			, m_flags(BGFX_RESET_NONE)
		{
		}

		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_flags;
	};

	struct DynamicIndexBuffer
	{
		IndexBufferHandle m_handle;
		uint32_t m_offset;
		uint32_t m_size;
	};

	struct DynamicVertexBuffer
	{
		VertexBufferHandle m_handle;
		uint32_t m_offset;
		uint32_t m_size;
		uint32_t m_startVertex;
		uint32_t m_numVertices;
		uint32_t m_stride;
		VertexDeclHandle m_decl;
	};

	struct Frame
	{
		BX_CACHE_LINE_ALIGN_MARKER();

		Frame()
		{
		}

		~Frame()
		{
		}

		void create()
		{
			m_constantBuffer = ConstantBuffer::create(BGFX_CONFIG_MAX_CONSTANT_BUFFER_SIZE);
			reset();
			start();
			m_textVideoMem = BX_NEW(g_allocator, TextVideoMem);
		}

		void destroy()
		{
			ConstantBuffer::destroy(m_constantBuffer);
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
			m_flags = BGFX_STATE_NONE;
			m_state.reset();
			m_matrixCache.reset();
			m_rectCache.reset();
			m_key.reset();
			m_num = 0;
			m_numRenderStates = 0;
			m_numDropped = 0;
			m_iboffset = 0;
			m_vboffset = 0;
			m_cmdPre.start();
			m_cmdPost.start();
			m_constantBuffer->reset();
			m_discard = false;
		}

		void finish()
		{
			m_cmdPre.finish();
			m_cmdPost.finish();

			m_constantBuffer->finish();

			if (0 < m_numDropped)
			{
				BX_TRACE("Too many draw calls: %d, dropped %d (max: %d)"
					, m_num+m_numDropped
					, m_numDropped
					, BGFX_CONFIG_MAX_DRAW_CALLS
					);
			}
		}

		void setMarker(const char* _name)
		{
			m_constantBuffer->writeMarker(_name);
		}

		void setState(uint64_t _state, uint32_t _rgba)
		{
			uint8_t blend = ( (_state&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT)&0xff;
			// transparency sort order table
			m_key.m_trans = "\x0\x1\x1\x2\x2\x1\x2\x1\x2\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1"[( (blend)&0xf) + (!!blend)];
			m_state.m_flags = _state;
			m_state.m_rgba = _rgba;
		}

		void setStencil(uint32_t _fstencil, uint32_t _bstencil)
		{
			m_state.m_stencil = packStencil(_fstencil, _bstencil);
		}

		uint16_t setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
		{
			uint16_t scissor = m_rectCache.add(_x, _y, _width, _height);
			m_state.m_scissor = scissor;
			return scissor;
		}

		void setScissor(uint16_t _cache)
		{
			m_state.m_scissor = _cache;
		}

		uint32_t setTransform(const void* _mtx, uint16_t _num)
		{
			m_state.m_matrix = m_matrixCache.add(_mtx, _num);
			m_state.m_num = _num;

			return m_state.m_matrix;
		}

		void setTransform(uint32_t _cache, uint16_t _num)
		{
			m_state.m_matrix = _cache;
			m_state.m_num = _num;
		}

		void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
		{
			m_state.m_startIndex = _firstIndex;
			m_state.m_numIndices = _numIndices;
			m_state.m_indexBuffer = _handle;
		}

		void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _numIndices)
		{
			m_state.m_indexBuffer = _tib->handle;
			m_state.m_startIndex = _tib->startIndex;
			m_state.m_numIndices = _numIndices;
			m_discard = 0 == _numIndices;
		}

		void setVertexBuffer(VertexBufferHandle _handle, uint32_t _numVertices)
		{
			BX_CHECK(_handle.idx < BGFX_CONFIG_MAX_VERTEX_BUFFERS, "Invalid vertex buffer handle. %d (< %d)", _handle.idx, BGFX_CONFIG_MAX_VERTEX_BUFFERS);
			m_state.m_startVertex = 0;
			m_state.m_numVertices = _numVertices;
			m_state.m_vertexBuffer = _handle;
		}

		void setVertexBuffer(const DynamicVertexBuffer& _dvb, uint32_t _numVertices)
		{
			m_state.m_startVertex = _dvb.m_startVertex;
			m_state.m_numVertices = bx::uint32_min(_dvb.m_numVertices, _numVertices);
			m_state.m_vertexBuffer = _dvb.m_handle;
			m_state.m_vertexDecl = _dvb.m_decl;
		}

		void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _numVertices)
		{
			m_state.m_startVertex = _tvb->startVertex;
			m_state.m_numVertices = bx::uint32_min(_tvb->size/_tvb->stride, _numVertices);
			m_state.m_vertexBuffer = _tvb->handle;
			m_state.m_vertexDecl = _tvb->decl;
		}

		void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint16_t _num)
		{
 			m_state.m_instanceDataOffset = _idb->offset;
			m_state.m_instanceDataStride = _idb->stride;
			m_state.m_numInstances = bx::uint16_min( (uint16_t)_idb->num, _num);
			m_state.m_instanceDataBuffer = _idb->handle;
			BX_FREE(g_allocator, const_cast<InstanceDataBuffer*>(_idb) );
		}

		void setProgram(ProgramHandle _handle)
		{
			BX_CHECK(isValid(_handle), "Can't set program with invalid handle.");
			m_key.m_program = _handle.idx;
		}

		void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags)
		{
			m_flags |= BGFX_STATE_TEX0<<_stage;
			Sampler& sampler = m_state.m_sampler[_stage];
			sampler.m_idx = _handle.idx;
			sampler.m_flags = 0
						| BGFX_SAMPLER_TEXTURE
						| ( (_flags&BGFX_SAMPLER_TYPE_MASK) ? BGFX_SAMPLER_DEFAULT_FLAGS : _flags)
						;

			if (isValid(_sampler) )
			{
				uint32_t stage = _stage;
				setUniform(_sampler, &stage);
			}
		}

		void setTexture(uint8_t _stage, UniformHandle _sampler, RenderTargetHandle _handle, bool _depth, uint32_t _flags)
		{
			m_flags |= BGFX_STATE_TEX0<<_stage;
			Sampler& sampler = m_state.m_sampler[_stage];
			sampler.m_idx = _handle.idx;
			sampler.m_flags = 0
						| (_depth ? BGFX_SAMPLER_RENDERTARGET_DEPTH : BGFX_SAMPLER_RENDERTARGET_COLOR)
						| ( (_flags&BGFX_SAMPLER_TYPE_MASK) ? BGFX_SAMPLER_DEFAULT_FLAGS : _flags)
						;

			if (isValid(_sampler) )
			{
				uint32_t stage = _stage;
				setUniform(_sampler, &stage);
			}
		}

		void discard()
		{
			m_discard = false;
			m_state.clear();
			m_flags = BGFX_STATE_NONE;
		}

		uint32_t submit(uint8_t _id, int32_t _depth);
		uint32_t submitMask(uint32_t _viewMask, int32_t _depth);
		void sort();

		bool checkAvailTransientIndexBuffer(uint32_t _num)
		{
			uint32_t offset = m_iboffset;
			uint32_t iboffset = offset + _num*sizeof(uint16_t);
			iboffset = bx::uint32_min(iboffset, BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
			uint32_t num = (iboffset-offset)/sizeof(uint16_t);
			return num == _num;
		}

		uint32_t allocTransientIndexBuffer(uint32_t& _num)
		{
			uint32_t offset = m_iboffset;
			m_iboffset = offset + _num*sizeof(uint16_t);
			m_iboffset = bx::uint32_min(m_iboffset, BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
			_num = (m_iboffset-offset)/sizeof(uint16_t);
			return offset;
		}

		bool checkAvailTransientVertexBuffer(uint32_t _num, uint16_t _stride)
		{
			uint32_t offset = strideAlign(m_vboffset, _stride);
			uint32_t vboffset = offset + _num * _stride;
			vboffset = bx::uint32_min(vboffset, BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
			uint32_t num = (vboffset-offset)/_stride;
			return num == _num;
		}

		uint32_t allocTransientVertexBuffer(uint32_t& _num, uint16_t _stride)
		{
			uint32_t offset = strideAlign(m_vboffset, _stride);
			m_vboffset = offset + _num * _stride;
			m_vboffset = bx::uint32_min(m_vboffset, BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
			_num = (m_vboffset-offset)/_stride;
			return offset;
		}

		void writeConstant(UniformType::Enum _type, UniformHandle _handle, const void* _value, uint16_t _num)
		{
			m_constantBuffer->writeUniform(_type, _handle.idx, _value, _num);
		}

		void free(IndexBufferHandle _handle)
		{
			m_freeIndexBufferHandle[m_numFreeIndexBufferHandles] = _handle;
			++m_numFreeIndexBufferHandles;
		}

		void free(VertexDeclHandle _handle)
		{
			m_freeVertexDeclHandle[m_numFreeVertexDeclHandles] = _handle;
			++m_numFreeVertexDeclHandles;
		}

		void free(VertexBufferHandle _handle)
		{
			m_freeVertexBufferHandle[m_numFreeVertexBufferHandles] = _handle;
			++m_numFreeVertexBufferHandles;
		}

		void free(VertexShaderHandle _handle)
		{
			m_freeVertexShaderHandle[m_numFreeVertexShaderHandles] = _handle;
			++m_numFreeVertexShaderHandles;
		}

		void free(FragmentShaderHandle _handle)
		{
			m_freeFragmentShaderHandle[m_numFreeFragmentShaderHandles] = _handle;
			++m_numFreeFragmentShaderHandles;
		}

		void free(ProgramHandle _handle)
		{
			m_freeProgramHandle[m_numFreeProgramHandles] = _handle;
			++m_numFreeProgramHandles;
		}

		void free(TextureHandle _handle)
		{
			m_freeTextureHandle[m_numFreeTextureHandles] = _handle;
			++m_numFreeTextureHandles;
		}

		void free(RenderTargetHandle _handle)
		{
			m_freeRenderTargetHandle[m_numFreeRenderTargetHandles] = _handle;
			++m_numFreeRenderTargetHandles;
		}

		void free(UniformHandle _handle)
		{
			m_freeUniformHandle[m_numFreeUniformHandles] = _handle;
			++m_numFreeUniformHandles;
		}

		void resetFreeHandles()
		{
			m_numFreeIndexBufferHandles = 0;
			m_numFreeVertexDeclHandles = 0;
			m_numFreeVertexBufferHandles = 0;
			m_numFreeVertexShaderHandles = 0;
			m_numFreeFragmentShaderHandles = 0;
			m_numFreeFragmentShaderHandles = 0;
			m_numFreeProgramHandles = 0;
			m_numFreeTextureHandles = 0;
			m_numFreeRenderTargetHandles = 0;
			m_numFreeUniformHandles = 0;
		}

		SortKey m_key;

		RenderTargetHandle m_rt[BGFX_CONFIG_MAX_VIEWS];
		Clear m_clear[BGFX_CONFIG_MAX_VIEWS];
		Rect m_rect[BGFX_CONFIG_MAX_VIEWS];
		Rect m_scissor[BGFX_CONFIG_MAX_VIEWS];
		Matrix4 m_view[BGFX_CONFIG_MAX_VIEWS];
		Matrix4 m_proj[BGFX_CONFIG_MAX_VIEWS];
		uint8_t m_other[BGFX_CONFIG_MAX_VIEWS];

		uint64_t m_sortKeys[BGFX_CONFIG_MAX_DRAW_CALLS];
		uint16_t m_sortValues[BGFX_CONFIG_MAX_DRAW_CALLS];
		RenderState m_renderState[BGFX_CONFIG_MAX_DRAW_CALLS];
		RenderState m_state;
		uint64_t m_flags;

		ConstantBuffer* m_constantBuffer;

		uint16_t m_num;
		uint16_t m_numRenderStates;
		uint16_t m_numDropped;

		MatrixCache m_matrixCache;
		RectCache m_rectCache;

		uint32_t m_iboffset;
		uint32_t m_vboffset;
		TransientIndexBuffer* m_transientIb;
		TransientVertexBuffer* m_transientVb;

		Resolution m_resolution;
		uint32_t m_debug;

		CommandBuffer m_cmdPre;
		CommandBuffer m_cmdPost;

		uint16_t m_numFreeIndexBufferHandles;
		uint16_t m_numFreeVertexDeclHandles;
		uint16_t m_numFreeVertexBufferHandles;
		uint16_t m_numFreeVertexShaderHandles;
		uint16_t m_numFreeFragmentShaderHandles;
		uint16_t m_numFreeProgramHandles;
		uint16_t m_numFreeTextureHandles;
		uint16_t m_numFreeRenderTargetHandles;
		uint16_t m_numFreeUniformHandles;

		IndexBufferHandle m_freeIndexBufferHandle[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexDeclHandle m_freeVertexDeclHandle[BGFX_CONFIG_MAX_VERTEX_DECLS];
		VertexBufferHandle m_freeVertexBufferHandle[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		VertexShaderHandle m_freeVertexShaderHandle[BGFX_CONFIG_MAX_VERTEX_SHADERS];
		FragmentShaderHandle m_freeFragmentShaderHandle[BGFX_CONFIG_MAX_FRAGMENT_SHADERS];
		ProgramHandle m_freeProgramHandle[BGFX_CONFIG_MAX_PROGRAMS];
		TextureHandle m_freeTextureHandle[BGFX_CONFIG_MAX_TEXTURES];
		RenderTargetHandle m_freeRenderTargetHandle[BGFX_CONFIG_MAX_RENDER_TARGETS];
		UniformHandle m_freeUniformHandle[BGFX_CONFIG_MAX_UNIFORMS];
		TextVideoMem* m_textVideoMem;

		int64_t m_waitSubmit;
		int64_t m_waitRender;

		bool m_discard;
	};

	struct VertexDeclRef
	{
		VertexDeclRef()
		{
		}

		void init()
		{
			memset(m_vertexDeclRef, 0, sizeof(m_vertexDeclRef) );
			memset(m_vertexBufferRef, 0xff, sizeof(m_vertexBufferRef) );
		}

		template <uint16_t MaxHandlesT>
		void shutdown(bx::HandleAllocT<MaxHandlesT>& _handleAlloc)
		{
			for (VertexDeclMap::iterator it = m_vertexDeclMap.begin(), itEnd = m_vertexDeclMap.end(); it != itEnd; ++it)
			{
				_handleAlloc.free(it->second.idx);
			}

			m_vertexDeclMap.clear();
		}

		VertexDeclHandle find(uint32_t _hash)
		{
			VertexDeclMap::const_iterator it = m_vertexDeclMap.find(_hash);
			if (it != m_vertexDeclMap.end() )
			{
				return it->second;
			}

			VertexDeclHandle result = BGFX_INVALID_HANDLE;
			return result;
		}

		void add(VertexBufferHandle _handle, VertexDeclHandle _declHandle, uint32_t _hash)
		{
			m_vertexBufferRef[_handle.idx] = _declHandle;
			m_vertexDeclRef[_declHandle.idx]++;
			m_vertexDeclMap.insert(stl::make_pair(_hash, _declHandle) );
		}

		VertexDeclHandle release(VertexBufferHandle _handle)
		{
			VertexDeclHandle declHandle = m_vertexBufferRef[_handle.idx];
			if (isValid(declHandle) )
			{
				m_vertexDeclRef[declHandle.idx]--;

				if (0 != m_vertexDeclRef[declHandle.idx])
				{
					VertexDeclHandle invalid = BGFX_INVALID_HANDLE;
					return invalid;
				}
			}

			return declHandle;
		}

		typedef stl::unordered_map<uint32_t, VertexDeclHandle> VertexDeclMap;
		VertexDeclMap m_vertexDeclMap;
		uint16_t m_vertexDeclRef[BGFX_CONFIG_MAX_VERTEX_DECLS];
		VertexDeclHandle m_vertexBufferRef[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
	};

	// First-fit non-local allocator.
	class NonLocalAllocator
	{
	public:
		static const uint64_t invalidBlock = UINT64_MAX;

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

		uint64_t alloc(uint32_t _size)
		{
			for (FreeList::iterator it = m_free.begin(), itEnd = m_free.end(); it != itEnd; ++it)
			{
				if (it->m_size >= _size)
				{
					uint64_t ptr = it->m_ptr;

					m_used.insert(stl::make_pair(ptr, _size) );

					if (it->m_size != _size)
					{
						it->m_size -= _size;
						it->m_ptr += _size;
					}
					else
					{
						m_free.erase(it);
					}

					return ptr;
				}
			}

			// there is no block large enough.
			return invalidBlock;
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

		void compact()
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

		typedef std::list<Free> FreeList;
		FreeList m_free;

		typedef stl::unordered_map<uint64_t, uint32_t> UsedList;
		UsedList m_used;
	};

#if BGFX_CONFIG_DEBUG
#	define BGFX_API_FUNC(_api) BX_NO_INLINE _api
#else
#	define BGFX_API_FUNC(_api) _api
#endif // BGFX_CONFIG_DEBUG

	struct Context
	{
		Context()
			: m_render(&m_frame[0])
			, m_submit(&m_frame[1])
			, m_numFreeDynamicIndexBufferHandles(0)
			, m_numFreeDynamicVertexBufferHandles(0)
			, m_frames(0)
			, m_debug(BGFX_DEBUG_NONE)
			, m_rendererInitialized(false)
			, m_exit(false)
		{
		}

		~Context()
		{
		}

		static int32_t renderThread(void* _userData)
		{
			BX_TRACE("render thread start");
			Context* ctx = (Context*)_userData;
			while (!ctx->renderFrame() );
			BX_TRACE("render thread exit");
			return EXIT_SUCCESS;
		}

		// game thread
		void init(bool _createRenderThread);
		void shutdown();

		CommandBuffer& getCommandBuffer(CommandBuffer::Enum _cmd)
		{
			CommandBuffer& cmdbuf = _cmd < CommandBuffer::End ? m_submit->m_cmdPre : m_submit->m_cmdPost;
			uint8_t cmd = (uint8_t)_cmd;
			cmdbuf.write(cmd);
			return cmdbuf;
		}

		BGFX_API_FUNC(void reset(uint32_t _width, uint32_t _height, uint32_t _flags) )
		{
			BX_WARN(0 != _width && 0 != _height, "Frame buffer resolution width or height cannot be 0 (width %d, height %d).", _width, _height);
			m_resolution.m_width = bx::uint32_max(1, _width);
			m_resolution.m_height = bx::uint32_max(1, _height);
			m_resolution.m_flags = _flags;

			memset(m_rt, 0xff, sizeof(m_rt) );
		}

		BGFX_API_FUNC(void setDebug(uint32_t _debug) )
		{
			m_debug = _debug;
		}

		BGFX_API_FUNC(void dbgTextClear(uint8_t _attr, bool _small) )
		{
			m_submit->m_textVideoMem->resize(_small, (uint16_t)m_resolution.m_width, (uint16_t)m_resolution.m_height);
			m_submit->m_textVideoMem->clear(_attr);
		}

		BGFX_API_FUNC(void dbgTextPrintfVargs(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList) )
		{
			m_submit->m_textVideoMem->printfVargs(_x, _y, _attr, _format, _argList);
		}

		BGFX_API_FUNC(IndexBufferHandle createIndexBuffer(const Memory* _mem) )
		{
			IndexBufferHandle handle = { m_indexBufferHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate index buffer handle.");
			if (isValid(handle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateIndexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyIndexBuffer(IndexBufferHandle _handle) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyIndexBuffer);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		VertexDeclHandle findVertexDecl(const VertexDecl& _decl)
		{
			VertexDeclHandle declHandle = m_declRef.find(_decl.m_hash);

			if (!isValid(declHandle) )
			{
				VertexDeclHandle temp = { m_vertexDeclHandle.alloc() };
				declHandle = temp;
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexDecl);
				cmdbuf.write(declHandle);
				cmdbuf.write(_decl);
			}

			return declHandle;
		}

		BGFX_API_FUNC(VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl) )
		{
			VertexBufferHandle handle = { m_vertexBufferHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate vertex buffer handle.");
			if (isValid(handle) )
			{
				VertexDeclHandle declHandle = findVertexDecl(_decl);
				m_declRef.add(handle, declHandle, _decl.m_hash);

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
				cmdbuf.write(declHandle);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyVertexBuffer(VertexBufferHandle _handle) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexBuffer);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		void destroyVertexBufferInternal(VertexBufferHandle _handle)
		{
			VertexDeclHandle declHandle = m_declRef.release(_handle);
			if (isValid(declHandle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexDecl);
				cmdbuf.write(declHandle);
			}

			m_vertexBufferHandle.free(_handle.idx);
		}

		BGFX_API_FUNC(DynamicIndexBufferHandle createDynamicIndexBuffer(uint32_t _num) )
		{
			DynamicIndexBufferHandle handle = BGFX_INVALID_HANDLE;
			uint32_t size = BX_ALIGN_16(_num*2);
			uint64_t ptr = m_dynamicIndexBufferAllocator.alloc(size);
			if (ptr == NonLocalAllocator::invalidBlock)
			{
				IndexBufferHandle indexBufferHandle = { m_indexBufferHandle.alloc() };
				BX_WARN(isValid(indexBufferHandle), "Failed to allocate index buffer handle.");
				if (!isValid(indexBufferHandle) )
				{
					return handle;
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicIndexBuffer);
				cmdbuf.write(indexBufferHandle);
				cmdbuf.write(BGFX_CONFIG_DYNAMIC_INDEX_BUFFER_SIZE);

				m_dynamicIndexBufferAllocator.add(uint64_t(indexBufferHandle.idx)<<32, BGFX_CONFIG_DYNAMIC_INDEX_BUFFER_SIZE);
				ptr = m_dynamicIndexBufferAllocator.alloc(size);
			}

			handle.idx = m_dynamicIndexBufferHandle.alloc();
			BX_WARN(isValid(handle), "Failed to allocate dynamic index buffer handle.");
			if (!isValid(handle) )
			{
				return handle;
			}

			DynamicIndexBuffer& dib = m_dynamicIndexBuffers[handle.idx];
			dib.m_handle.idx = uint16_t(ptr>>32);
			dib.m_offset = uint32_t(ptr);
			dib.m_size = size;

			return handle;
		}

		BGFX_API_FUNC(DynamicIndexBufferHandle createDynamicIndexBuffer(const Memory* _mem) )
		{
			DynamicIndexBufferHandle handle = createDynamicIndexBuffer(_mem->size/2);
			if (isValid(handle) )
			{
				updateDynamicIndexBuffer(handle, _mem);
			}
			return handle;
		}

		BGFX_API_FUNC(void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, const Memory* _mem) )
		{
			DynamicIndexBuffer& dib = m_dynamicIndexBuffers[_handle.idx];
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::UpdateDynamicIndexBuffer);
			cmdbuf.write(dib.m_handle);
			cmdbuf.write(dib.m_offset);
			cmdbuf.write(dib.m_size);
			cmdbuf.write(_mem);
		}

		BGFX_API_FUNC(void destroyDynamicIndexBuffer(DynamicIndexBufferHandle _handle) )
		{
			m_freeDynamicIndexBufferHandle[m_numFreeDynamicIndexBufferHandles++] = _handle;
		}

		void destroyDynamicIndexBufferInternal(DynamicIndexBufferHandle _handle)
		{
			DynamicIndexBuffer& dib = m_dynamicIndexBuffers[_handle.idx];
			m_dynamicIndexBufferAllocator.free(uint64_t(dib.m_handle.idx)<<32 | dib.m_offset);
			m_dynamicIndexBufferHandle.free(_handle.idx);
		}

		BGFX_API_FUNC(DynamicVertexBufferHandle createDynamicVertexBuffer(uint16_t _num, const VertexDecl& _decl) )
		{
			DynamicVertexBufferHandle handle = BGFX_INVALID_HANDLE;
			uint32_t size = strideAlign16(_num*_decl.m_stride, _decl.m_stride);
			uint64_t ptr = m_dynamicVertexBufferAllocator.alloc(size);
			if (ptr == NonLocalAllocator::invalidBlock)
			{
				VertexBufferHandle vertexBufferHandle = { m_vertexBufferHandle.alloc() };

				BX_WARN(isValid(handle), "Failed to allocate dynamic vertex buffer handle.");
				if (!isValid(vertexBufferHandle) )
				{
					return handle;
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicVertexBuffer);
				cmdbuf.write(vertexBufferHandle);
				cmdbuf.write(BGFX_CONFIG_DYNAMIC_VERTEX_BUFFER_SIZE);

				m_dynamicVertexBufferAllocator.add(uint64_t(vertexBufferHandle.idx)<<32, BGFX_CONFIG_DYNAMIC_VERTEX_BUFFER_SIZE);
				ptr = m_dynamicVertexBufferAllocator.alloc(size);
			}

			VertexDeclHandle declHandle = findVertexDecl(_decl);

			handle.idx = m_dynamicVertexBufferHandle.alloc();
			DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[handle.idx];
			dvb.m_handle.idx = uint16_t(ptr>>32);
			dvb.m_offset = uint32_t(ptr);
			dvb.m_size = size;
			dvb.m_startVertex = dvb.m_offset/_decl.m_stride;
			dvb.m_numVertices = dvb.m_size/_decl.m_stride;
			dvb.m_decl = declHandle;
			m_declRef.add(dvb.m_handle, declHandle, _decl.m_hash);

			return handle;
		}

		BGFX_API_FUNC(DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexDecl& _decl) )
		{
			DynamicVertexBufferHandle handle = createDynamicVertexBuffer(_mem->size/_decl.m_stride, _decl);
			if (isValid(handle) )
			{
				updateDynamicVertexBuffer(handle, _mem);
			}
			return handle;
		}

		BGFX_API_FUNC(void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, const Memory* _mem) )
		{
			DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[_handle.idx];
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::UpdateDynamicVertexBuffer);
			cmdbuf.write(dvb.m_handle);
			cmdbuf.write(dvb.m_offset);
			cmdbuf.write(dvb.m_size);
			cmdbuf.write(_mem);
		}

		BGFX_API_FUNC(void destroyDynamicVertexBuffer(DynamicVertexBufferHandle _handle) )
		{
			m_freeDynamicVertexBufferHandle[m_numFreeDynamicVertexBufferHandles++] = _handle;
		}

		void destroyDynamicVertexBufferInternal(DynamicVertexBufferHandle _handle)
		{
			DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[_handle.idx];

			VertexDeclHandle declHandle = m_declRef.release(dvb.m_handle);
			if (invalidHandle != declHandle.idx)
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexDecl);
				cmdbuf.write(declHandle);
			}

			m_dynamicVertexBufferAllocator.free(uint64_t(dvb.m_handle.idx)<<32 | dvb.m_offset);
			m_dynamicVertexBufferHandle.free(_handle.idx);
		}

		BGFX_API_FUNC(bool checkAvailTransientIndexBuffer(uint32_t _num) const)
		{
			return m_submit->checkAvailTransientIndexBuffer(_num);
		}

		BGFX_API_FUNC(bool checkAvailTransientVertexBuffer(uint32_t _num, uint16_t _stride) const)
		{
			return m_submit->checkAvailTransientVertexBuffer(_num, _stride);
		}

		TransientIndexBuffer* createTransientIndexBuffer(uint32_t _size)
		{
			TransientIndexBuffer* ib = NULL;

			IndexBufferHandle handle = { m_indexBufferHandle.alloc() };
			BX_WARN(isValid(handle), "Failed to allocate transient index buffer handle.");
			if (isValid(handle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicIndexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_size);

				ib = (TransientIndexBuffer*)BX_ALLOC(g_allocator, sizeof(TransientIndexBuffer)+_size);
				ib->data = (uint8_t*)&ib[1];
				ib->size = _size;
				ib->handle = handle;
			}

			return ib;
		}

		void destroyTransientIndexBuffer(TransientIndexBuffer* _ib)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyDynamicIndexBuffer);
			cmdbuf.write(_ib->handle);

			m_submit->free(_ib->handle);
			BX_FREE(g_allocator, const_cast<TransientIndexBuffer*>(_ib) );
		}

		BGFX_API_FUNC(void allocTransientIndexBuffer(TransientIndexBuffer* _tib, uint32_t _num) )
		{
			uint32_t offset = m_submit->allocTransientIndexBuffer(_num);

			TransientIndexBuffer& dib = *m_submit->m_transientIb;

			_tib->data = &dib.data[offset];
			_tib->size = _num * sizeof(uint16_t);
			_tib->handle = dib.handle;
			_tib->startIndex = offset/sizeof(uint16_t);
		}

		TransientVertexBuffer* createTransientVertexBuffer(uint32_t _size, const VertexDecl* _decl = NULL)
		{
			TransientVertexBuffer* vb = NULL;

			VertexBufferHandle handle = { m_vertexBufferHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate transient vertex buffer handle.");
			if (isValid(handle) )
			{
				uint16_t stride = 0;
				VertexDeclHandle declHandle = BGFX_INVALID_HANDLE;

				if (NULL != _decl)
				{
					declHandle = findVertexDecl(*_decl);
					m_declRef.add(handle, declHandle, _decl->m_hash);

					stride = _decl->m_stride;
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicVertexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_size);

				vb = (TransientVertexBuffer*)BX_ALLOC(g_allocator, sizeof(TransientVertexBuffer)+_size);
				vb->data = (uint8_t*)&vb[1];
				vb->size = _size;
				vb->startVertex = 0;
				vb->stride = stride;
				vb->handle = handle;
				vb->decl = declHandle;
			}

			return vb;
		}

		void destroyTransientVertexBuffer(TransientVertexBuffer* _vb)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyDynamicVertexBuffer);
			cmdbuf.write(_vb->handle);

			m_submit->free(_vb->handle);
			BX_FREE(g_allocator, const_cast<TransientVertexBuffer*>(_vb) );
		}

		BGFX_API_FUNC(void allocTransientVertexBuffer(TransientVertexBuffer* _tvb, uint32_t _num, const VertexDecl& _decl) )
		{
			VertexDeclHandle declHandle = m_declRef.find(_decl.m_hash);

			TransientVertexBuffer& dvb = *m_submit->m_transientVb;

			if (!isValid(declHandle) )
			{
				VertexDeclHandle temp = { m_vertexDeclHandle.alloc() };
				declHandle = temp;
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexDecl);
				cmdbuf.write(declHandle);
				cmdbuf.write(_decl);
				m_declRef.add(dvb.handle, declHandle, _decl.m_hash);
			}

			uint32_t offset = m_submit->allocTransientVertexBuffer(_num, _decl.m_stride);

			_tvb->data = &dvb.data[offset];
			_tvb->size = _num * _decl.m_stride;
			_tvb->startVertex = offset/_decl.m_stride;
			_tvb->stride = _decl.m_stride;
			_tvb->handle = dvb.handle;
			_tvb->decl = declHandle;
		}

		BGFX_API_FUNC(const InstanceDataBuffer* allocInstanceDataBuffer(uint32_t _num, uint16_t _stride) )
		{
			uint16_t stride = BX_ALIGN_16(_stride);
			uint32_t offset = m_submit->allocTransientVertexBuffer(_num, stride);

			TransientVertexBuffer& dvb = *m_submit->m_transientVb;
			InstanceDataBuffer* idb = (InstanceDataBuffer*)BX_ALLOC(g_allocator, sizeof(InstanceDataBuffer) );
			idb->data = &dvb.data[offset];
			idb->size = _num * stride;
			idb->offset = offset;
			idb->stride = stride;
			idb->num = _num;
			idb->handle = dvb.handle;

			return idb;
		}

		BGFX_API_FUNC(VertexShaderHandle createVertexShader(const Memory* _mem) )
		{
			bx::MemoryReader reader(_mem->data, _mem->size);

			uint32_t magic;
			bx::read(&reader, magic);

			if (BGFX_CHUNK_MAGIC_VSH != magic)
			{
				BX_WARN(false, "Invalid vertex shader signature! 0x%08x", magic);
				VertexShaderHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			VertexShaderHandle handle = { m_vertexShaderHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate vertex shader handle.");
			if (isValid(handle) )
			{
				VertexShaderRef& vsr = m_vertexShaderRef[handle.idx];
				vsr.m_refCount = 1;
				bx::read(&reader, vsr.m_outputHash);

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexShader);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyVertexShader(VertexShaderHandle _handle) )
		{
			if (!isValid(_handle) )
			{
				BX_WARN(false, "Passing invalid vertex shader handle to bgfx::destroyVertexShader");
				return;
			}

			vertexShaderDecRef(_handle);
		}

		void vertexShaderIncRef(VertexShaderHandle _handle)
		{
			VertexShaderRef& vsr = m_vertexShaderRef[_handle.idx];
			++vsr.m_refCount;
		}

		void vertexShaderDecRef(VertexShaderHandle _handle)
		{
			VertexShaderRef& vsr = m_vertexShaderRef[_handle.idx];
			int32_t refs = --vsr.m_refCount;
			if (0 == refs)
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexShader);
				cmdbuf.write(_handle);
				m_submit->free(_handle);
			}
		}

		BGFX_API_FUNC(FragmentShaderHandle createFragmentShader(const Memory* _mem) )
		{
			bx::MemoryReader reader(_mem->data, _mem->size);

			uint32_t magic;
			bx::read(&reader, magic);

			if (BGFX_CHUNK_MAGIC_FSH != magic)
			{
				BX_WARN(false, "Invalid fragment shader signature! 0x%08x", magic);
				FragmentShaderHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			FragmentShaderHandle handle = { m_fragmentShaderHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate fragment shader handle.");
			if (isValid(handle) )
			{
				FragmentShaderRef& fsr = m_fragmentShaderRef[handle.idx];
				fsr.m_refCount = 1;
				bx::read(&reader, fsr.m_inputHash);

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateFragmentShader);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyFragmentShader(FragmentShaderHandle _handle) )
		{
			if (!isValid(_handle) )
			{
				BX_WARN(false, "Passing invalid fragment shader handle to bgfx::destroyFragmentShader");
				return;
			}

			fragmentShaderDecRef(_handle);
		}

		void fragmentShaderIncRef(FragmentShaderHandle _handle)
		{
			FragmentShaderRef& fsr = m_fragmentShaderRef[_handle.idx];
			++fsr.m_refCount;
		}

		void fragmentShaderDecRef(FragmentShaderHandle _handle)
		{
			FragmentShaderRef& fsr = m_fragmentShaderRef[_handle.idx];
			int32_t refs = --fsr.m_refCount;
			if (0 == refs)
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyFragmentShader);
				cmdbuf.write(_handle);
				m_submit->free(_handle);
			}
		}

		BGFX_API_FUNC(ProgramHandle createProgram(VertexShaderHandle _vsh, FragmentShaderHandle _fsh) )
		{
			if (!isValid(_vsh)
			||  !isValid(_fsh) )
			{
				BX_WARN(false, "Vertex/fragment shader is invalid (vsh %d, fsh %d).", _vsh.idx, _fsh.idx);
				ProgramHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			const VertexShaderRef& vsr = m_vertexShaderRef[_vsh.idx];
			const FragmentShaderRef& fsr = m_fragmentShaderRef[_fsh.idx];
			if (vsr.m_outputHash != fsr.m_inputHash)
			{
				BX_WARN(vsr.m_outputHash == fsr.m_inputHash, "Vertex shader output doesn't match fragment shader input.");
				ProgramHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			ProgramHandle handle;
 			handle.idx = m_programHandle.alloc();

			BX_WARN(isValid(handle), "Failed to allocate program handle.");
			if (isValid(handle) )
			{
				vertexShaderIncRef(_vsh);
				fragmentShaderIncRef(_fsh);
				m_programRef[handle.idx].m_vsh = _vsh;
				m_programRef[handle.idx].m_fsh = _fsh;

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateProgram);
				cmdbuf.write(handle);
				cmdbuf.write(_vsh);
				cmdbuf.write(_fsh);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyProgram(ProgramHandle _handle) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyProgram);
			cmdbuf.write(_handle);
			m_submit->free(_handle);

			vertexShaderDecRef(m_programRef[_handle.idx].m_vsh);
			fragmentShaderDecRef(m_programRef[_handle.idx].m_fsh);
		}

		BGFX_API_FUNC(TextureHandle createTexture(const Memory* _mem, uint32_t _flags, TextureInfo* _info = NULL) )
		{
			if (NULL != _info)
			{
				ImageContainer imageContainer;
				if (imageParse(imageContainer, _mem->data, _mem->size) )
				{
					calcTextureSize(*_info
						, (uint16_t)imageContainer.m_width
						, (uint16_t)imageContainer.m_height
						, (uint16_t)imageContainer.m_depth
						, imageContainer.m_numMips
						, TextureFormat::Enum(imageContainer.m_format)
						);
				}
				else
				{
					_info->format = TextureFormat::Unknown;
					_info->storageSize = 0;
					_info->width = 0;
					_info->height = 0;
					_info->depth = 0;
					_info->numMips = 0;
					_info->bitsPerPixel = 0;
				}
			}

			TextureHandle handle = { m_textureHandle.alloc() };
			BX_WARN(isValid(handle), "Failed to allocate texture handle.");
			if (isValid(handle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateTexture);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
				cmdbuf.write(_flags);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyTexture(TextureHandle _handle) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyTexture);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		BGFX_API_FUNC(void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, uint16_t _x, uint16_t _y, uint16_t _z, uint16_t _width, uint16_t _height, uint16_t _depth, uint16_t _pitch, const Memory* _mem) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::UpdateTexture);
			cmdbuf.write(_handle);
			cmdbuf.write(_side);
			cmdbuf.write(_mip);
			Rect rect;
			rect.m_x = _x;
			rect.m_y = _y;
			rect.m_width = _width;
			rect.m_height = _height;
			cmdbuf.write(rect);
			cmdbuf.write(_z);
			cmdbuf.write(_depth);
			cmdbuf.write(_pitch);
			cmdbuf.write(_mem);
		}

		BGFX_API_FUNC(RenderTargetHandle createRenderTarget(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags) )
		{
			RenderTargetHandle handle = { m_renderTargetHandle.alloc() };
			BX_WARN(isValid(handle), "Failed to allocate render target handle.");

			if (isValid(handle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateRenderTarget);
				cmdbuf.write(handle);
				cmdbuf.write(_width);
				cmdbuf.write(_height);
				cmdbuf.write(_flags);
				cmdbuf.write(_textureFlags);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyRenderTarget(RenderTargetHandle _handle) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyRenderTarget);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		BGFX_API_FUNC(UniformHandle createUniform(const char* _name, UniformType::Enum _type, uint16_t _num) )
		{
			BX_WARN(PredefinedUniform::Count == nameToPredefinedUniformEnum(_name), "%s is predefined uniform name.", _name);
			if (PredefinedUniform::Count != nameToPredefinedUniformEnum(_name) )
			{
				UniformHandle handle = BGFX_INVALID_HANDLE;
				return handle;
			}

			UniformHashMap::iterator it = m_uniformHashMap.find(_name);
			if (it != m_uniformHashMap.end() )
			{
				UniformHandle handle = it->second;
				UniformRef& uniform = m_uniformRef[handle.idx];
				++uniform.m_refCount;
				return handle;
			}

			UniformHandle handle = { m_uniformHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate uniform handle.");
			if (isValid(handle) )
			{
				UniformRef& uniform = m_uniformRef[handle.idx];
				uniform.m_refCount = 1;
				uniform.m_type = _type;
				uniform.m_num = _num;

				m_uniformHashMap.insert(stl::make_pair(stl::string(_name), handle) );

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateUniform);
				cmdbuf.write(handle);
				cmdbuf.write(_type);
				cmdbuf.write(_num);
				uint8_t len = (uint8_t)strlen(_name)+1;
				cmdbuf.write(len);
				cmdbuf.write(_name, len);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyUniform(UniformHandle _handle) )
		{
			UniformRef& uniform = m_uniformRef[_handle.idx];
			BX_CHECK(uniform.m_refCount > 0, "Destroying already destroyed uniform %d.", _handle.idx);
			int32_t refs = --uniform.m_refCount;

			if (0 == refs)
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyUniform);
				cmdbuf.write(_handle);
				m_submit->free(_handle);
			}
		}

		BGFX_API_FUNC(void saveScreenShot(const char* _filePath) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::SaveScreenShot);
			uint16_t len = (uint16_t)strlen(_filePath)+1;
			cmdbuf.write(len);
			cmdbuf.write(_filePath, len);
		}

		BGFX_API_FUNC(void setViewName(uint8_t _id, const char* _name) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::UpdateViewName);
			cmdbuf.write(_id);
			uint16_t len = (uint16_t)strlen(_name)+1;
			cmdbuf.write(len);
			cmdbuf.write(_name, len);
		}

		BGFX_API_FUNC(void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height) )
		{
			Rect& rect = m_rect[_id];
			rect.m_x = _x;
			rect.m_y = _y;
			rect.m_width = bx::uint16_max(_width, 1);
			rect.m_height = bx::uint16_max(_height, 1);
		}

		BGFX_API_FUNC(void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height) )
		{
			for (uint32_t view = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, view += 1, ntz = bx::uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				view += ntz;

				setViewRect( (uint8_t)view, _x, _y, _width, _height);
			}
		}

		BGFX_API_FUNC(void setViewScissor(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height) )
		{
			Rect& scissor = m_scissor[_id];
			scissor.m_x = _x;
			scissor.m_y = _y;
			scissor.m_width = _width;
			scissor.m_height = _height;
		}

		BGFX_API_FUNC(void setViewScissorMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height) )
		{
			for (uint32_t view = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, view += 1, ntz = bx::uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				view += ntz;

				setViewScissor( (uint8_t)view, _x, _y, _width, _height);
			}
		}

		BGFX_API_FUNC(void setViewClear(uint8_t _id, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil) )
		{
			Clear& clear = m_clear[_id];
			clear.m_flags = _flags;
			clear.m_rgba = _rgba;
			clear.m_depth = _depth;
			clear.m_stencil = _stencil;
		}

		BGFX_API_FUNC(void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil) )
		{
			for (uint32_t view = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, view += 1, ntz = bx::uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				view += ntz;

				setViewClear( (uint8_t)view, _flags, _rgba, _depth, _stencil);
			}
		}

		BGFX_API_FUNC(void setViewSeq(uint8_t _id, bool _enabled) )
		{
			m_seqMask[_id] = _enabled ? 0xffff : 0x0;
		}

		BGFX_API_FUNC(void setViewSeqMask(uint32_t _viewMask, bool _enabled) )
		{
			uint16_t mask = _enabled ? 0xffff : 0x0;
			for (uint32_t view = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, view += 1, ntz = bx::uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				view += ntz;

				m_seqMask[view] = mask;
			}
		}

		BGFX_API_FUNC(void setViewRenderTarget(uint8_t _id, RenderTargetHandle _handle) )
		{
			m_rt[_id] = _handle;
		}

		BGFX_API_FUNC(void setViewRenderTargetMask(uint32_t _viewMask, RenderTargetHandle _handle) )
		{
			for (uint32_t view = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, view += 1, ntz = bx::uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				view += ntz;

				m_rt[view] = _handle;
			}
		}

		BGFX_API_FUNC(void setViewTransform(uint8_t _id, const void* _view, const void* _proj, uint8_t _other) )
		{
			if (BGFX_CONFIG_MAX_VIEWS > _other)
			{
				m_other[_id] = _other;
			}
			else
			{
				m_other[_id] = _id;
			}

			if (NULL != _view)
			{
				memcpy(m_view[_id].val, _view, sizeof(Matrix4) );
			}
			else
			{
				m_view[_id].setIdentity();
			}

			if (NULL != _proj)
			{
				memcpy(m_proj[_id].val, _proj, sizeof(Matrix4) );
			}
			else
			{
				m_proj[_id].setIdentity();
			}
		}

		BGFX_API_FUNC(void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj, uint8_t _other) )
		{
			for (uint32_t view = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, view += 1, ntz = bx::uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				view += ntz;

				setViewTransform( (uint8_t)view, _view, _proj, _other);
			}
		}

		BGFX_API_FUNC(void setMarker(const char* _marker) )
		{
			m_submit->setMarker(_marker);
		}

		BGFX_API_FUNC(void setState(uint64_t _state, uint32_t _rgba) )
		{
			m_submit->setState(_state, _rgba);
		}

		BGFX_API_FUNC(void setStencil(uint32_t _fstencil, uint32_t _bstencil) )
		{
			m_submit->setStencil(_fstencil, _bstencil);
		}

		BGFX_API_FUNC(uint16_t setScissor(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height) )
		{
			return m_submit->setScissor(_x, _y, _width, _height);
		}

		BGFX_API_FUNC(void setScissor(uint16_t _cache) )
		{
			m_submit->setScissor(_cache);
		}

		BGFX_API_FUNC(uint32_t setTransform(const void* _mtx, uint16_t _num) )
		{
			return m_submit->setTransform(_mtx, _num);
		}

		BGFX_API_FUNC(void setTransform(uint32_t _cache, uint16_t _num) )
		{
			m_submit->setTransform(_cache, _num);
		}

		BGFX_API_FUNC(void setUniform(UniformHandle _handle, const void* _value, uint16_t _num) )
		{
			UniformRef& uniform = m_uniformRef[_handle.idx];
			BX_CHECK(uniform.m_num >= _num, "Truncated uniform update. %d (max: %d)", _num, uniform.m_num);
			m_submit->writeConstant(uniform.m_type, _handle, _value, bx::uint16_min(uniform.m_num, _num) );
		}

		BGFX_API_FUNC(void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices) )
		{
			m_submit->setIndexBuffer(_handle, _firstIndex, _numIndices);
		}

		BGFX_API_FUNC(void setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices) )
		{
			m_submit->setIndexBuffer(m_dynamicIndexBuffers[_handle.idx].m_handle, _firstIndex, _numIndices);
		}

		BGFX_API_FUNC(void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _numIndices) )
		{
			m_submit->setIndexBuffer(_tib, _numIndices);
		}

		BGFX_API_FUNC(void setVertexBuffer(VertexBufferHandle _handle, uint32_t _numVertices) )
		{
			m_submit->setVertexBuffer(_handle, _numVertices);
		}

		BGFX_API_FUNC(void setVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _numVertices) )
		{
			m_submit->setVertexBuffer(m_dynamicVertexBuffers[_handle.idx], _numVertices);
		}

		BGFX_API_FUNC(void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _numVertices) )
		{
			m_submit->setVertexBuffer(_tvb, _numVertices);
		}

		BGFX_API_FUNC(void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint16_t _num) )
		{
			m_submit->setInstanceDataBuffer(_idb, _num);
		}

		BGFX_API_FUNC(void setProgram(ProgramHandle _handle) )
		{
			m_submit->setProgram(_handle);
		}

		BGFX_API_FUNC(void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags) )
		{
			m_submit->setTexture(_stage, _sampler, _handle, _flags);
		}

		BGFX_API_FUNC(void setTexture(uint8_t _stage, UniformHandle _sampler, RenderTargetHandle _handle, bool _depth, uint32_t _flags) )
		{
			m_submit->setTexture(_stage, _sampler, _handle, _depth, _flags);
		}

		BGFX_API_FUNC(uint32_t submit(uint8_t _id, int32_t _depth) )
		{
			return m_submit->submit(_id, _depth);
		}

		BGFX_API_FUNC(uint32_t submitMask(uint32_t _viewMask, int32_t _depth) )
		{
			return m_submit->submitMask(_viewMask, _depth);
		}

		BGFX_API_FUNC(void discard() )
		{
			m_submit->discard();
		}

		BGFX_API_FUNC(uint32_t frame() );

		void dumpViewStats();
		void freeDynamicBuffers();
		void freeAllHandles(Frame* _frame);
		void frameNoRenderWait();
		void swap();

		// render thread
		bool renderFrame();
		void rendererFlip();
		void rendererInit();
		void rendererShutdown();
		void rendererCreateIndexBuffer(IndexBufferHandle _handle, Memory* _mem);
		void rendererDestroyIndexBuffer(IndexBufferHandle _handle);
		void rendererCreateVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle);
		void rendererDestroyVertexBuffer(VertexBufferHandle _handle);
		void rendererCreateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size);
		void rendererUpdateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem);
		void rendererDestroyDynamicIndexBuffer(IndexBufferHandle _handle);
		void rendererCreateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size);
		void rendererUpdateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem);
		void rendererDestroyDynamicVertexBuffer(VertexBufferHandle _handle);
		void rendererCreateVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl);
		void rendererDestroyVertexDecl(VertexDeclHandle _handle);
		void rendererCreateVertexShader(VertexShaderHandle _handle, Memory* _mem);
		void rendererDestroyVertexShader(VertexShaderHandle _handle);
		void rendererCreateFragmentShader(FragmentShaderHandle _handle, Memory* _mem);
		void rendererDestroyFragmentShader(FragmentShaderHandle _handle);
		void rendererCreateProgram(ProgramHandle _handle, VertexShaderHandle _vsh, FragmentShaderHandle _fsh);
		void rendererDestroyProgram(FragmentShaderHandle _handle);
		void rendererCreateTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags);
		void rendererUpdateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip);
		void rendererUpdateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem);
		void rendererUpdateTextureEnd();
		void rendererDestroyTexture(TextureHandle _handle);
		void rendererCreateRenderTarget(RenderTargetHandle _handle, uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags);
		void rendererDestroyRenderTarget(RenderTargetHandle _handle);
		void rendererCreateUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name);
		void rendererDestroyUniform(UniformHandle _handle);
		void rendererSaveScreenShot(const char* _filePath);
		void rendererUpdateViewName(uint8_t _id, const char* _name);
		void rendererUpdateUniform(uint16_t _loc, const void* _data, uint32_t _size);
		void rendererSetMarker(const char* _marker, uint32_t _size);
		void rendererUpdateUniforms(ConstantBuffer* _constantBuffer, uint32_t _begin, uint32_t _end);
		void flushTextureUpdateBatch(CommandBuffer& _cmdbuf);
		void rendererExecCommands(CommandBuffer& _cmdbuf);
		void rendererSubmit();

#if BGFX_CONFIG_MULTITHREADED
		void gameSemPost()
		{
			m_gameSem.post();
		}

		void gameSemWait()
		{
			int64_t start = bx::getHPCounter();
			bool ok = m_gameSem.wait();
			BX_CHECK(ok, "Semaphore wait failed."); BX_UNUSED(ok);
			m_render->m_waitSubmit = bx::getHPCounter()-start;
		}

		void renderSemPost()
		{
			m_renderSem.post();
		}

		void renderSemWait()
		{
			int64_t start = bx::getHPCounter();
			bool ok = m_renderSem.wait();
			BX_CHECK(ok, "Semaphore wait failed."); BX_UNUSED(ok);
			m_submit->m_waitRender = bx::getHPCounter() - start;
		}

		bx::Semaphore m_renderSem;
		bx::Semaphore m_gameSem;
#else
		void gameSemPost()
		{
		}

		void gameSemWait()
		{
		}

		void renderSemPost()
		{
		}

		void renderSemWait()
		{
		}
#endif // BGFX_CONFIG_MULTITHREADED

		bx::Thread m_thread;
		Frame m_frame[2];
		Frame* m_render;
		Frame* m_submit;

		uint64_t m_tempKeys[BGFX_CONFIG_MAX_DRAW_CALLS];
		uint16_t m_tempValues[BGFX_CONFIG_MAX_DRAW_CALLS];

		DynamicIndexBuffer m_dynamicIndexBuffers[BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS];
		DynamicVertexBuffer m_dynamicVertexBuffers[BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS];

		uint16_t m_numFreeDynamicIndexBufferHandles;
		uint16_t m_numFreeDynamicVertexBufferHandles;
		DynamicIndexBufferHandle m_freeDynamicIndexBufferHandle[BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS];
		DynamicVertexBufferHandle m_freeDynamicVertexBufferHandle[BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS];

		NonLocalAllocator m_dynamicIndexBufferAllocator;
		bx::HandleAllocT<BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS> m_dynamicIndexBufferHandle;
		NonLocalAllocator m_dynamicVertexBufferAllocator;
		bx::HandleAllocT<BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS> m_dynamicVertexBufferHandle;

		bx::HandleAllocT<BGFX_CONFIG_MAX_INDEX_BUFFERS> m_indexBufferHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_VERTEX_DECLS > m_vertexDeclHandle;

		bx::HandleAllocT<BGFX_CONFIG_MAX_VERTEX_BUFFERS> m_vertexBufferHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_VERTEX_SHADERS> m_vertexShaderHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_FRAGMENT_SHADERS> m_fragmentShaderHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_PROGRAMS> m_programHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_TEXTURES> m_textureHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_RENDER_TARGETS> m_renderTargetHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_UNIFORMS> m_uniformHandle;

		struct FragmentShaderRef
		{
			int32_t m_refCount;
			uint32_t m_inputHash;
		};
		
		struct VertexShaderRef
		{
			int32_t m_refCount;
			uint32_t m_outputHash;
		};

		struct ProgramRef
		{
			VertexShaderHandle m_vsh;
			FragmentShaderHandle m_fsh;
		};

		struct UniformRef
		{
			int32_t m_refCount;
			UniformType::Enum m_type;
			uint16_t m_num;
		};

		typedef stl::unordered_map<stl::string, UniformHandle> UniformHashMap;
		UniformHashMap m_uniformHashMap;
		UniformRef m_uniformRef[BGFX_CONFIG_MAX_UNIFORMS];
		VertexShaderRef m_vertexShaderRef[BGFX_CONFIG_MAX_VERTEX_SHADERS];
		FragmentShaderRef m_fragmentShaderRef[BGFX_CONFIG_MAX_FRAGMENT_SHADERS];
		ProgramRef m_programRef[BGFX_CONFIG_MAX_PROGRAMS];
		VertexDeclRef m_declRef;

		RenderTargetHandle m_rt[BGFX_CONFIG_MAX_VIEWS];
		Clear m_clear[BGFX_CONFIG_MAX_VIEWS];
		Rect m_rect[BGFX_CONFIG_MAX_VIEWS];
		Rect m_scissor[BGFX_CONFIG_MAX_VIEWS];
		Matrix4 m_view[BGFX_CONFIG_MAX_VIEWS];
		Matrix4 m_proj[BGFX_CONFIG_MAX_VIEWS];
		uint8_t m_other[BGFX_CONFIG_MAX_VIEWS];
		uint16_t m_seq[BGFX_CONFIG_MAX_VIEWS];
		uint16_t m_seqMask[BGFX_CONFIG_MAX_VIEWS];

		Resolution m_resolution;
		uint32_t m_frames;
		uint32_t m_debug;

		TextVideoMemBlitter m_textVideoMemBlitter;
		ClearQuad m_clearQuad;

		bool m_rendererInitialized;
		bool m_exit;

		BX_CACHE_LINE_ALIGN_MARKER();
		typedef UpdateBatchT<256> TextureUpdateBatch;
		TextureUpdateBatch m_textureUpdateBatch;
	};

#undef BGFX_API_FUNC

} // namespace bgfx

#endif // BGFX_P_H_HEADER_GUARD
