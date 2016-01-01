/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
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
#	define BX_CHECK _BX_CHECK
#	define BX_CONFIG_ALLOCATOR_DEBUG 1
#endif // BGFX_CONFIG_DEBUG

#include <bgfx/bgfx.h>
#include "config.h"

#include <inttypes.h>
#include <stdarg.h> // va_list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>

// Check handle, cannot be bgfx::invalidHandle and must be valid.
#define BGFX_CHECK_HANDLE(_desc, _handleAlloc, _handle) \
			BX_CHECK(isValid(_handle) \
				&& _handleAlloc.isValid(_handle.idx) \
				, "Invalid handle. %s handle: %d (max %d)" \
				, _desc \
				, _handle.idx \
				, _handleAlloc.getMaxHandles() \
				)

// Check handle, it's ok to be bgfx::invalidHandle or must be valid.
#define BGFX_CHECK_HANDLE_INVALID_OK(_desc, _handleAlloc, _handle) \
			BX_CHECK(!isValid(_handle) \
				|| _handleAlloc.isValid(_handle.idx) \
				, "Invalid handle. %s handle: %d (max %d)" \
				, _desc \
				, _handle.idx \
				, _handleAlloc.getMaxHandles() \
				)

#ifndef BGFX_PROFILER_SCOPE
#	if BGFX_CONFIG_PROFILER_MICROPROFILE
#		include <microprofile.h>
#		define BGFX_PROFILER_SCOPE(_group, _name, _color) MICROPROFILE_SCOPEI(#_group, #_name, _color)
#		define BGFX_PROFILER_BEGIN(_group, _name, _color) BX_NOOP()
#		define BGFX_PROFILER_BEGIN_DYNAMIC(_namestr) BX_NOOP()
#		define BGFX_PROFILER_END() BX_NOOP()
#		define BGFX_PROFILER_SET_CURRENT_THREAD_NAME(_name) BX_NOOP()
#	elif BGFX_CONFIG_PROFILER_REMOTERY
#		define RMT_ENABLED BGFX_CONFIG_PROFILER_REMOTERY
#		define RMT_USE_D3D11 BGFX_CONFIG_RENDERER_DIRECT3D11
#		define RMT_USE_OPENGL BGFX_CONFIG_RENDERER_OPENGL
#		include <remotery/lib/Remotery.h>
#		define BGFX_PROFILER_SCOPE(_group, _name, _color) rmt_ScopedCPUSample(_group##_##_name)
#		define BGFX_PROFILER_BEGIN(_group, _name, _color) rmt_BeginCPUSample(_group##_##_name)
#		define BGFX_PROFILER_BEGIN_DYNAMIC(_namestr) rmt_BeginCPUSampleDynamic(_namestr)
#		define BGFX_PROFILER_END() rmt_EndCPUSample()
#		define BGFX_PROFILER_SET_CURRENT_THREAD_NAME(_name) rmt_SetCurrentThreadName(_name)
#	else
#		define BGFX_PROFILER_SCOPE(_group, _name, _color) BX_NOOP()
#		define BGFX_PROFILER_BEGIN(_group, _name, _color) BX_NOOP()
#		define BGFX_PROFILER_BEGIN_DYNAMIC(_namestr) BX_NOOP()
#		define BGFX_PROFILER_END() BX_NOOP()
#		define BGFX_PROFILER_SET_CURRENT_THREAD_NAME(_name) BX_NOOP()
#	endif // BGFX_CONFIG_PROFILER_*
#endif // BGFX_PROFILER_SCOPE

namespace bgfx
{
#if BX_COMPILER_CLANG_ANALYZER
	void __attribute__( (analyzer_noreturn) ) fatal(Fatal::Enum _code, const char* _format, ...);
#else
	void fatal(Fatal::Enum _code, const char* _format, ...);
#endif // BX_COMPILER_CLANG_ANALYZER

	void trace(const char* _filePath, uint16_t _line, const char* _format, ...);

	void dbgPrintfVargs(const char* _format, va_list _argList);
	void dbgPrintf(const char* _format, ...);
}

#define _BX_TRACE(_format, ...) \
				BX_MACRO_BLOCK_BEGIN \
					bgfx::trace(__FILE__, uint16_t(__LINE__), "BGFX " _format "\n", ##__VA_ARGS__); \
				BX_MACRO_BLOCK_END

#define _BX_WARN(_condition, _format, ...) \
				BX_MACRO_BLOCK_BEGIN \
					if (!BX_IGNORE_C4127(_condition) ) \
					{ \
						BX_TRACE("WARN " _format, ##__VA_ARGS__); \
					} \
				BX_MACRO_BLOCK_END

#define _BX_CHECK(_condition, _format, ...) \
				BX_MACRO_BLOCK_BEGIN \
					if (!BX_IGNORE_C4127(_condition) ) \
					{ \
						BX_TRACE("CHECK " _format, ##__VA_ARGS__); \
						bgfx::fatal(bgfx::Fatal::DebugCheck, _format, ##__VA_ARGS__); \
					} \
				BX_MACRO_BLOCK_END

#define BGFX_FATAL(_condition, _err, _format, ...) \
			BX_MACRO_BLOCK_BEGIN \
				if (!BX_IGNORE_C4127(_condition) ) \
				{ \
					fatal(_err, _format, ##__VA_ARGS__); \
				} \
			BX_MACRO_BLOCK_END

#include <bx/bx.h>
#include <bx/debug.h>
#include <bx/fpumath.h>
#include <bx/float4x4_t.h>
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

#include <bgfx/bgfxplatform.h>
#include "image.h"

#define BGFX_CHUNK_MAGIC_CSH BX_MAKEFOURCC('C', 'S', 'H', 0x2)
#define BGFX_CHUNK_MAGIC_FSH BX_MAKEFOURCC('F', 'S', 'H', 0x4)
#define BGFX_CHUNK_MAGIC_TEX BX_MAKEFOURCC('T', 'E', 'X', 0x0)
#define BGFX_CHUNK_MAGIC_VSH BX_MAKEFOURCC('V', 'S', 'H', 0x4)

#define BGFX_CLEAR_COLOR_USE_PALETTE UINT16_C(0x8000)
#define BGFX_CLEAR_MASK (0 \
			| BGFX_CLEAR_COLOR \
			| BGFX_CLEAR_DEPTH \
			| BGFX_CLEAR_STENCIL \
			| BGFX_CLEAR_COLOR_USE_PALETTE \
			)

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
#	include <tinystl/vector.h>
namespace stl = tinystl;
#else
#	include <string>
#	include <unordered_map>
#	include <unordered_set>
#	include <vector>
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

#define BGFX_MAX_COMPUTE_BINDINGS 8

#define BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER  UINT32_C(0x10000000)

#define BGFX_RESET_INTERNAL_FORCE              UINT32_C(0x80000000)

#define BGFX_STATE_INTERNAL_SCISSOR            UINT64_C(0x2000000000000000)
#define BGFX_STATE_INTERNAL_OCCLUSION_QUERY    UINT64_C(0x4000000000000000)

#define BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE UINT8_C(0x80)

#define BGFX_RENDERER_DIRECT3D9_NAME  "Direct3D 9"
#define BGFX_RENDERER_DIRECT3D11_NAME "Direct3D 11"
#define BGFX_RENDERER_DIRECT3D12_NAME "Direct3D 12"
#define BGFX_RENDERER_METAL_NAME "Metal"
#define BGFX_RENDERER_VULKAN_NAME "Vulkan"
#define BGFX_RENDERER_NULL_NAME "NULL"

#if BGFX_CONFIG_RENDERER_OPENGL
#	if BGFX_CONFIG_RENDERER_OPENGL >= 31 && BGFX_CONFIG_RENDERER_OPENGL <= 33
#		if BGFX_CONFIG_RENDERER_OPENGL == 31
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 3.1"
#		elif BGFX_CONFIG_RENDERER_OPENGL == 32
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 3.2"
#		else
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 3.3"
#		endif // 31+
#	elif BGFX_CONFIG_RENDERER_OPENGL >= 40 && BGFX_CONFIG_RENDERER_OPENGL <= 45
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
#		else
#			define BGFX_RENDERER_OPENGL_NAME "OpenGL 4.5"
#		endif // 40+
#	else
#		define BGFX_RENDERER_OPENGL_NAME "OpenGL 2.1"
#	endif // BGFX_CONFIG_RENDERER_OPENGL
#elif BGFX_CONFIG_RENDERER_OPENGLES
#	if BGFX_CONFIG_RENDERER_OPENGLES == 30
#		define BGFX_RENDERER_OPENGL_NAME "OpenGL ES 3.0"
#	elif BGFX_CONFIG_RENDERER_OPENGLES >= 31
#		define BGFX_RENDERER_OPENGL_NAME "OpenGL ES 3.1"
#	else
#		define BGFX_RENDERER_OPENGL_NAME "OpenGL ES 2.0"
#	endif // BGFX_CONFIG_RENDERER_OPENGLES
#else
#	define BGFX_RENDERER_OPENGL_NAME "OpenGL"
#endif //

namespace bgfx
{
	extern PlatformData g_platformData;

#if BGFX_CONFIG_MAX_DRAW_CALLS < (64<<10)
	typedef uint16_t RenderItemCount;
#else
	typedef uint32_t RenderItemCount;
#endif // BGFX_CONFIG_MAX_DRAW_CALLS < (64<<10)

	struct Clear
	{
		uint8_t  m_index[8];
		float    m_depth;
		uint8_t  m_stencil;
		uint16_t m_flags;
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
			using namespace bx;
			const uint16_t sx = uint16_max(_a.m_x, _b.m_x);
			const uint16_t sy = uint16_max(_a.m_y, _b.m_y);
			const uint16_t ex = uint16_min(_a.m_x + _a.m_width,  _b.m_x + _b.m_width );
			const uint16_t ey = uint16_min(_a.m_y + _a.m_height, _b.m_y + _b.m_height);
			m_x = sx;
			m_y = sy;
			m_width  = (uint16_t)uint32_satsub(ex, sx);
			m_height = (uint16_t)uint32_satsub(ey, sy);
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
	extern bx::AllocatorI* g_allocator;
	extern Caps g_caps;

	void setGraphicsDebuggerPresent(bool _present);
	bool isGraphicsDebuggerPresent();
	void release(const Memory* _mem);
	const char* getAttribName(Attrib::Enum _attr);
	void getTextureSizeFromRatio(BackbufferRatio::Enum _ratio, uint16_t& _width, uint16_t& _height);

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

	inline bool needBorderColor(uint32_t _flags)
	{
		return BGFX_TEXTURE_U_BORDER == (_flags & BGFX_TEXTURE_U_BORDER)
			|| BGFX_TEXTURE_V_BORDER == (_flags & BGFX_TEXTURE_V_BORDER)
			|| BGFX_TEXTURE_W_BORDER == (_flags & BGFX_TEXTURE_W_BORDER)
			;
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

		void resize(bool _small = false, uint32_t _width = BGFX_DEFAULT_WIDTH, uint32_t _height = BGFX_DEFAULT_HEIGHT)
		{
			uint32_t width = bx::uint32_max(1, _width/8);
			uint32_t height = bx::uint32_max(1, _height/(_small ? 8 : 16) );

			if (NULL == m_mem
			||  m_width != width
			||  m_height != height
			||  m_small != _small)
			{
				m_small  = _small;
				m_width  = (uint16_t)width;
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

		void image(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch)
		{
			if (_x < m_width && _y < m_height)
			{
				uint8_t* dst = &m_mem[(_y*m_width+_x)*2];
				const uint8_t* src = (const uint8_t*)_data;
				const uint32_t width  = (bx::uint32_min(m_width,  _width +_x)-_x)*2;
				const uint32_t height =  bx::uint32_min(m_height, _height+_y)-_y;
				const uint32_t dstPitch = m_width*2;

				for (uint32_t yy = 0; yy < height; ++yy)
				{
					memcpy(dst, src, width);
					dst += dstPitch;
					src += _pitch;
				}
			}
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

		TextureHandle m_texture;
		TransientVertexBuffer* m_vb;
		TransientIndexBuffer* m_ib;
		VertexDecl m_decl;
		ProgramHandle m_program;
		bool m_init;
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
		ClearQuad()
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_program); ++ii)
			{
				m_program[ii].idx = invalidHandle;
			}
		}

		void init();
		void shutdown();

		TransientVertexBuffer* m_vb;
		VertexDecl m_decl;
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
			CreateShader,
			CreateProgram,
			CreateTexture,
			UpdateTexture,
			ResizeTexture,
			CreateFrameBuffer,
			CreateUniform,
			UpdateViewName,
			End,
			RendererShutdownEnd,
			DestroyVertexDecl,
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
			align(BX_ALIGNOF(Type) );
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
			align(BX_ALIGNOF(Type) );
			read(reinterpret_cast<uint8_t*>(&_in), sizeof(Type) );
		}

		const uint8_t* skip(uint32_t _size)
		{
			BX_CHECK(m_pos < m_size, "");
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

#define SORT_KEY_DRAW_BIT              (UINT64_C(1)<<0x36)

#define SORT_KEY_SEQ_SHIFT             0x2b
#define SORT_KEY_SEQ_MASK              (UINT64_C(0x7ff)<<SORT_KEY_SEQ_SHIFT)

#define SORT_KEY_VIEW_SHIFT            0x37
#define SORT_KEY_VIEW_MASK             ( (uint64_t(BGFX_CONFIG_MAX_VIEWS-1) )<<SORT_KEY_VIEW_SHIFT)

#define SORT_KEY_DRAW_TRANS_SHIFT      0x29
#define SORT_KEY_DRAW_TRANS_MASK       (UINT64_C(0x3)<<SORT_KEY_DRAW_TRANS_SHIFT)

#define SORT_KEY_DRAW_PROGRAM_SHIFT    0x20
#define SORT_KEY_DRAW_PROGRAM_MASK     ( (uint64_t(BGFX_CONFIG_MAX_PROGRAMS-1) )<<SORT_KEY_DRAW_PROGRAM_SHIFT)

#define SORT_KEY_DRAW_DEPTH_SHIFT      0
#define SORT_KEY_DRAW_DEPTH_MASK       ( (uint64_t(UINT32_MAX) )<<SORT_KEY_DRAW_DEPTH_SHIFT)

#define SORT_KEY_COMPUTE_PROGRAM_SHIFT 0x22
#define SORT_KEY_COMPUTE_PROGRAM_MASK  ( (uint64_t(BGFX_CONFIG_MAX_PROGRAMS-1) )<<SORT_KEY_COMPUTE_PROGRAM_SHIFT)

	BX_STATIC_ASSERT(BGFX_CONFIG_MAX_VIEWS <= 256);
	BX_STATIC_ASSERT( (BGFX_CONFIG_MAX_PROGRAMS & (BGFX_CONFIG_MAX_PROGRAMS-1) ) == 0); // Must be power of 2.
	BX_STATIC_ASSERT( (0 // Render key mask shouldn't overlap.
		| SORT_KEY_DRAW_BIT
		| SORT_KEY_SEQ_MASK
		| SORT_KEY_VIEW_MASK
		| SORT_KEY_DRAW_TRANS_MASK
		| SORT_KEY_DRAW_PROGRAM_MASK
		| SORT_KEY_DRAW_DEPTH_MASK
		) == (0
		^ SORT_KEY_DRAW_BIT
		^ SORT_KEY_SEQ_MASK
		^ SORT_KEY_VIEW_MASK
		^ SORT_KEY_DRAW_TRANS_MASK
		^ SORT_KEY_DRAW_PROGRAM_MASK
		^ SORT_KEY_DRAW_DEPTH_MASK
		) );
	BX_STATIC_ASSERT( (0 // Compute key mask shouldn't overlap.
		| SORT_KEY_DRAW_BIT
		| SORT_KEY_SEQ_MASK
		| SORT_KEY_VIEW_MASK
		| SORT_KEY_COMPUTE_PROGRAM_MASK
		) == (0
		^ SORT_KEY_DRAW_BIT
		^ SORT_KEY_SEQ_MASK
		^ SORT_KEY_VIEW_MASK
		^ SORT_KEY_COMPUTE_PROGRAM_MASK
		) );

	struct SortKey
	{
		uint64_t encodeDraw()
		{
			// |               3               2               1               0|
			// |fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210|
			// | vvvvvvvvdsssssssssssttpppppppppdddddddddddddddddddddddddddddddd|
			// |        ^^          ^ ^        ^                               ^|
			// |        ||          | |        |                               ||
			// |   view-+|      seq-+ +-trans  +-program                 depth-+|
			// |         +-draw                                                 |

			const uint64_t depth   = (uint64_t(m_depth  ) << SORT_KEY_DRAW_DEPTH_SHIFT  ) & SORT_KEY_DRAW_DEPTH_MASK;
			const uint64_t program = (uint64_t(m_program) << SORT_KEY_DRAW_PROGRAM_SHIFT) & SORT_KEY_DRAW_PROGRAM_MASK;
			const uint64_t trans   = (uint64_t(m_trans  ) << SORT_KEY_DRAW_TRANS_SHIFT  ) & SORT_KEY_DRAW_TRANS_MASK;
			const uint64_t seq     = (uint64_t(m_seq    ) << SORT_KEY_SEQ_SHIFT         ) & SORT_KEY_SEQ_MASK;
			const uint64_t view    = (uint64_t(m_view   ) << SORT_KEY_VIEW_SHIFT        ) & SORT_KEY_VIEW_MASK;
			const uint64_t key     = depth|program|trans|SORT_KEY_DRAW_BIT|seq|view;

			BX_CHECK(seq == (uint64_t(m_seq) << SORT_KEY_SEQ_SHIFT), "SortKey error, sequence is truncated (m_seq: %d)."
				, m_seq
				);

			return key;
		}

		uint64_t encodeCompute()
		{
			// |               3               2               1               0|
			// |fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210|
			// | vvvvvvvvdsssssssssssppppppppp                                  |
			// |        ^^          ^        ^                                  |
			// |        ||          |        |                                  |
			// |   view-+|      seq-+        +-program                          |
			// |         +-draw                                                 |

			const uint64_t program = (uint64_t(m_program) << SORT_KEY_COMPUTE_PROGRAM_SHIFT) & SORT_KEY_COMPUTE_PROGRAM_MASK;
			const uint64_t seq     = (uint64_t(m_seq    ) << SORT_KEY_SEQ_SHIFT            ) & SORT_KEY_SEQ_MASK;
			const uint64_t view    = (uint64_t(m_view   ) << SORT_KEY_VIEW_SHIFT           ) & SORT_KEY_VIEW_MASK;
			const uint64_t key     = program|seq|view;

			BX_CHECK(seq == (uint64_t(m_seq) << SORT_KEY_SEQ_SHIFT), "SortKey error, sequence is truncated (m_seq: %d)."
				, m_seq
				);

			return key;
		}

		/// Returns true if item is command.
		bool decode(uint64_t _key)
		{
			m_seq  = uint16_t( (_key & SORT_KEY_SEQ_MASK ) >> SORT_KEY_SEQ_SHIFT);
			m_view =  uint8_t( (_key & SORT_KEY_VIEW_MASK) >> SORT_KEY_VIEW_SHIFT);
			if (_key & SORT_KEY_DRAW_BIT)
			{
				m_depth   = uint32_t( (_key & SORT_KEY_DRAW_DEPTH_MASK  ) >> SORT_KEY_DRAW_DEPTH_SHIFT);
				m_program = uint16_t( (_key & SORT_KEY_DRAW_PROGRAM_MASK) >> SORT_KEY_DRAW_PROGRAM_SHIFT);
				m_trans   =  uint8_t( (_key & SORT_KEY_DRAW_TRANS_MASK  ) >> SORT_KEY_DRAW_TRANS_SHIFT);
				return false; // draw
			}

			m_program = uint16_t( (_key & SORT_KEY_COMPUTE_PROGRAM_MASK) >> SORT_KEY_COMPUTE_PROGRAM_SHIFT);
			return true; // compute
		}

		bool decode(uint64_t _key, uint8_t _viewRemap[BGFX_CONFIG_MAX_VIEWS])
		{
			bool compute = decode(_key);
			m_view = _viewRemap[m_view];
			return compute;
		}

		static uint64_t remapView(uint64_t _key, uint8_t _viewRemap[BGFX_CONFIG_MAX_VIEWS])
		{
			const uint8_t  oldView  = uint8_t( (_key & SORT_KEY_VIEW_MASK) >> SORT_KEY_VIEW_SHIFT);
			const uint64_t view     = uint64_t(_viewRemap[oldView])        << SORT_KEY_VIEW_SHIFT;
			const uint64_t key      = (_key & ~SORT_KEY_VIEW_MASK) | view;
			return key;
		}

		void reset()
		{
			m_depth   = 0;
			m_program = 0;
			m_seq     = 0;
			m_view    = 0;
			m_trans   = 0;
		}

		uint32_t m_depth;
		uint16_t m_program;
		uint16_t m_seq;
		uint8_t  m_view;
		uint8_t  m_trans;
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
			m_view =  uint8_t(_key >> 24);
		}

		static uint32_t remapView(uint32_t _key, uint8_t _viewRemap[BGFX_CONFIG_MAX_VIEWS])
		{
			const uint8_t  oldView  = uint8_t(_key >> 24);
			const uint32_t view     = uint32_t(_viewRemap[oldView]) << 24;
			const uint32_t key      = (_key & ~UINT32_C(0xff000000) ) | view;
			return key;
		}

		uint16_t m_item;
		uint8_t  m_view;
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
			memset(un.val, 0, sizeof(un.val) );
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
			BX_WARN(m_num+num < BGFX_CONFIG_MAX_MATRIX_CACHE, "Matrix cache overflow. %d (max: %d)", m_num+num, BGFX_CONFIG_MAX_MATRIX_CACHE);
			num = bx::uint32_min(num, BGFX_CONFIG_MAX_MATRIX_CACHE-m_num);
			uint32_t first = m_num;
			m_num += num;
			*_num = (uint16_t)num;
			return first;
		}

		uint32_t add(const void* _mtx, uint16_t _num)
		{
			if (NULL != _mtx)
			{
				uint32_t first = reserve(&_num);
				memcpy(&m_cache[first], _mtx, sizeof(Matrix4)*_num);
				return first;
			}

			return 0;
		}

		float* toPtr(uint32_t _cacheIdx)
		{
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

#define CONSTANT_OPCODE_TYPE_SHIFT 27
#define CONSTANT_OPCODE_TYPE_MASK  UINT32_C(0xf8000000)
#define CONSTANT_OPCODE_LOC_SHIFT  11
#define CONSTANT_OPCODE_LOC_MASK   UINT32_C(0x07fff800)
#define CONSTANT_OPCODE_NUM_SHIFT  1
#define CONSTANT_OPCODE_NUM_MASK   UINT32_C(0x000007fe)
#define CONSTANT_OPCODE_COPY_SHIFT 0
#define CONSTANT_OPCODE_COPY_MASK  UINT32_C(0x00000001)

#define BGFX_UNIFORM_FRAGMENTBIT UINT8_C(0x10)
#define BGFX_UNIFORM_SAMPLERBIT  UINT8_C(0x20)
#define BGFX_UNIFORM_MASK (BGFX_UNIFORM_FRAGMENTBIT|BGFX_UNIFORM_SAMPLERBIT)

	class UniformBuffer
	{
	public:
		static UniformBuffer* create(uint32_t _size = 1<<20)
		{
			uint32_t size = BX_ALIGN_16(bx::uint32_max(_size, sizeof(UniformBuffer) ) );
			void*    data = BX_ALLOC(g_allocator, size);
			return ::new(data) UniformBuffer(_size);
		}

		static void destroy(UniformBuffer* _uniformBuffer)
		{
			_uniformBuffer->~UniformBuffer();
			BX_FREE(g_allocator, _uniformBuffer);
		}

		static void update(UniformBuffer*& _uniformBuffer, uint32_t _treshold = 64<<10, uint32_t _grow = 1<<20)
		{
			if (_treshold >= _uniformBuffer->m_size - _uniformBuffer->m_pos)
			{
				uint32_t size = BX_ALIGN_16(bx::uint32_max(_uniformBuffer->m_size + _grow, sizeof(UniformBuffer) ) );
				void*    data = BX_REALLOC(g_allocator, _uniformBuffer, size);
				_uniformBuffer = reinterpret_cast<UniformBuffer*>(data);
				_uniformBuffer->m_size = size;
			}
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
			const uint32_t loc  = (_opcode&CONSTANT_OPCODE_LOC_MASK ) >> CONSTANT_OPCODE_LOC_SHIFT;
			const uint32_t num  = (_opcode&CONSTANT_OPCODE_NUM_MASK ) >> CONSTANT_OPCODE_NUM_SHIFT;
			const uint32_t copy = (_opcode&CONSTANT_OPCODE_COPY_MASK); // >> CONSTANT_OPCODE_COPY_SHIFT;

			_type = (UniformType::Enum)(type);
			_copy = (uint16_t)copy;
			_num  = (uint16_t)num;
			_loc  = (uint16_t)loc;
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
			uint32_t result;
			memcpy(&result, read(sizeof(uint32_t) ), sizeof(uint32_t) );
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
			: m_size(_size-sizeof(m_buffer) )
			, m_pos(0)
		{
			finish();
		}

		~UniformBuffer()
		{
		}

		uint32_t m_size;
		uint32_t m_pos;
		char m_buffer[8];
	};

	struct UniformInfo
	{
		const void* m_data;
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

 		const UniformInfo* find(const char* _name) const
 		{
			UniformHashMap::const_iterator it = m_uniforms.find(_name);
			if (it != m_uniforms.end() )
			{
				return &it->second;
			}

 			return NULL;
 		}

		const UniformInfo& add(UniformHandle _handle, const char* _name, const void* _data)
		{
			UniformHashMap::iterator it = m_uniforms.find(_name);
			if (it == m_uniforms.end() )
			{
				UniformInfo info;
				info.m_data   = _data;
				info.m_handle = _handle;

				stl::pair<UniformHashMap::iterator, bool> result = m_uniforms.insert(UniformHashMap::value_type(_name, info) );
				return result.first->second;
			}

			UniformInfo& info = it->second;
			info.m_data   = _data;
			info.m_handle = _handle;

			return info;
		}

	private:
		typedef stl::unordered_map<stl::string, UniformInfo> UniformHashMap;
		UniformHashMap m_uniforms;
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

		uint16_t m_idx;
		uint8_t  m_type;

		union
		{
			struct
			{
				uint32_t m_textureFlags;
			} m_draw;

			struct
			{
				uint8_t  m_format;
				uint8_t  m_access;
				uint8_t  m_mip;
			} m_compute;

		} m_un;
	};

	struct RenderDraw
	{
		void clear()
		{
			m_constBegin  = 0;
			m_constEnd    = 0;
			m_stateFlags  = BGFX_STATE_DEFAULT;
			m_stencil     = packStencil(BGFX_STENCIL_DEFAULT, BGFX_STENCIL_DEFAULT);
			m_rgba        = 0;
			m_matrix      = 0;
			m_startIndex  = 0;
			m_numIndices  = UINT32_MAX;
			m_startVertex = 0;
			m_numVertices = UINT32_MAX;
			m_instanceDataOffset = 0;
			m_instanceDataStride = 0;
			m_numInstances       = 1;
			m_startIndirect = 0;
			m_numIndirect   = UINT16_MAX;
			m_num           = 1;
			m_submitFlags   = BGFX_SUBMIT_EYE_FIRST;
			m_scissor       = UINT16_MAX;
			m_vertexBuffer.idx       = invalidHandle;
			m_vertexDecl.idx         = invalidHandle;
			m_indexBuffer.idx        = invalidHandle;
			m_instanceDataBuffer.idx = invalidHandle;
			m_indirectBuffer.idx     = invalidHandle;
			m_occlusionQuery.idx     = invalidHandle;

			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++ii)
			{
				Binding& bind = m_bind[ii];
				bind.m_idx  = invalidHandle;
				bind.m_type = 0;
				bind.m_un.m_draw.m_textureFlags = 0;
			}
		}

		Binding  m_bind[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
		uint64_t m_stateFlags;
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
		uint16_t m_startIndirect;
		uint16_t m_numIndirect;
		uint16_t m_num;
		uint16_t m_scissor;
		uint8_t  m_submitFlags;

		VertexBufferHandle   m_vertexBuffer;
		VertexDeclHandle     m_vertexDecl;
		IndexBufferHandle    m_indexBuffer;
		VertexBufferHandle   m_instanceDataBuffer;
		IndirectBufferHandle m_indirectBuffer;
		OcclusionQueryHandle m_occlusionQuery;
	};

	struct RenderCompute
	{
		void clear()
		{
			m_constBegin  = 0;
			m_constEnd    = 0;
			m_matrix      = 0;
			m_numX        = 0;
			m_numY        = 0;
			m_numZ        = 0;
			m_num         = 0;
			m_submitFlags = BGFX_SUBMIT_EYE_FIRST;

			m_indirectBuffer.idx = invalidHandle;
			m_startIndirect      = 0;
			m_numIndirect        = UINT16_MAX;

			for (uint32_t ii = 0; ii < BGFX_MAX_COMPUTE_BINDINGS; ++ii)
			{
				m_bind[ii].m_idx = invalidHandle;
			}
		}

		Binding  m_bind[BGFX_MAX_COMPUTE_BINDINGS];
		uint32_t m_constBegin;
		uint32_t m_constEnd;
		uint32_t m_matrix;
		IndirectBufferHandle m_indirectBuffer;

		uint16_t m_numX;
		uint16_t m_numY;
		uint16_t m_numZ;
		uint16_t m_startIndirect;
		uint16_t m_numIndirect;
		uint16_t m_num;
		uint8_t  m_submitFlags;
	};

	union RenderItem
	{
		RenderDraw    draw;
		RenderCompute compute;
	};

	struct BlitItem
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

	struct VertexBuffer
	{
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
		VertexDeclHandle m_decl;
		uint16_t m_flags;
	};

	BX_ALIGN_DECL_CACHE_LINE(struct) Frame
	{
		Frame()
			: m_uniformMax(0)
			, m_waitSubmit(0)
			, m_waitRender(0)
			, m_hmdInitialized(false)
		{
			SortKey term;
			term.reset();
			term.m_program = invalidHandle;
			m_sortKeys[BGFX_CONFIG_MAX_DRAW_CALLS]   = term.encodeDraw();
			m_sortValues[BGFX_CONFIG_MAX_DRAW_CALLS] = BGFX_CONFIG_MAX_DRAW_CALLS;
			memset(m_occlusion, 0xff, sizeof(m_occlusion) );
		}

		~Frame()
		{
		}

		void create()
		{
			m_uniformBuffer = UniformBuffer::create();
			reset();
			start();
			m_textVideoMem = BX_NEW(g_allocator, TextVideoMem);
		}

		void destroy()
		{
			UniformBuffer::destroy(m_uniformBuffer);
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
			m_stateFlags = BGFX_STATE_NONE;
			m_uniformBegin = 0;
			m_uniformEnd   = 0;
			m_draw.clear();
			m_compute.clear();
			m_matrixCache.reset();
			m_rectCache.reset();
			m_key.reset();
			m_num            = 0;
			m_numRenderItems = 0;
			m_numDropped     = 0;
			m_numBlitItems   = 0;
			m_iboffset = 0;
			m_vboffset = 0;
			m_cmdPre.start();
			m_cmdPost.start();
			m_uniformBuffer->reset();
			m_discard = false;
		}

		void finish()
		{
			m_cmdPre.finish();
			m_cmdPost.finish();

			m_uniformMax = bx::uint32_max(m_uniformMax, m_uniformBuffer->getPos() );
			m_uniformBuffer->finish();

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
			m_uniformBuffer->writeMarker(_name);
		}

		void setState(uint64_t _state, uint32_t _rgba)
		{
			uint8_t blend = ( (_state&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT)&0xff;
			// transparency sort order table
			m_key.m_trans = "\x0\x1\x1\x2\x2\x1\x2\x1\x2\x1\x1\x1\x1\x1\x1\x1\x1\x1\x1"[( (blend)&0xf) + (!!blend)];
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
			uint16_t scissor = (uint16_t)m_rectCache.add(_x, _y, _width, _height);
			m_draw.m_scissor = scissor;
			return scissor;
		}

		void setScissor(uint16_t _cache)
		{
			m_draw.m_scissor = _cache;
		}

		uint32_t setTransform(const void* _mtx, uint16_t _num)
		{
			m_draw.m_matrix = m_matrixCache.add(_mtx, _num);
			m_draw.m_num    = _num;

			return m_draw.m_matrix;
		}

		uint32_t allocTransform(Transform* _transform, uint16_t _num)
		{
			uint32_t first   = m_matrixCache.reserve(&_num);
			_transform->data = m_matrixCache.toPtr(first);
			_transform->num  = _num;

			return first;
		}

		void setTransform(uint32_t _cache, uint16_t _num)
		{
			m_draw.m_matrix = _cache;
			m_draw.m_num    = _num;
		}

		void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices)
		{
			m_draw.m_startIndex  = _firstIndex;
			m_draw.m_numIndices  = _numIndices;
			m_draw.m_indexBuffer = _handle;
		}

		void setIndexBuffer(const DynamicIndexBuffer& _dib, uint32_t _firstIndex, uint32_t _numIndices)
		{
			const uint32_t indexSize = 0 == (_dib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
			m_draw.m_startIndex  = _dib.m_startIndex + _firstIndex;
			m_draw.m_numIndices  = bx::uint32_min(_numIndices, _dib.m_size/indexSize);
			m_draw.m_indexBuffer = _dib.m_handle;
		}

		void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _firstIndex, uint32_t _numIndices)
		{
			m_draw.m_indexBuffer = _tib->handle;
			m_draw.m_startIndex  = _firstIndex;
			m_draw.m_numIndices  = _numIndices;
			m_discard = 0 == _numIndices;
		}

		void setVertexBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices)
		{
			m_draw.m_startVertex  = _startVertex;
			m_draw.m_numVertices  = _numVertices;
			m_draw.m_vertexBuffer = _handle;
		}

		void setVertexBuffer(const DynamicVertexBuffer& _dvb, uint32_t _numVertices)
		{
			m_draw.m_startVertex  = _dvb.m_startVertex;
			m_draw.m_numVertices  = bx::uint32_min(_dvb.m_numVertices, _numVertices);
			m_draw.m_vertexBuffer = _dvb.m_handle;
			m_draw.m_vertexDecl   = _dvb.m_decl;
		}

		void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _startVertex, uint32_t _numVertices)
		{
			m_draw.m_startVertex  = _tvb->startVertex + _startVertex;
			m_draw.m_numVertices  = bx::uint32_min(_tvb->size/_tvb->stride, _numVertices);
			m_draw.m_vertexBuffer = _tvb->handle;
			m_draw.m_vertexDecl   = _tvb->decl;
		}

		void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint32_t _num)
		{
 			m_draw.m_instanceDataOffset = _idb->offset;
			m_draw.m_instanceDataStride = _idb->stride;
			m_draw.m_numInstances       = uint16_t(bx::uint32_min(_idb->num, _num) );
			m_draw.m_instanceDataBuffer = _idb->handle;
			BX_FREE(g_allocator, const_cast<InstanceDataBuffer*>(_idb) );
		}

		void setInstanceDataBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num, uint16_t _stride)
		{
			m_draw.m_instanceDataOffset = _startVertex * _stride;
			m_draw.m_instanceDataStride = _stride;
			m_draw.m_numInstances       = uint16_t(_num);
			m_draw.m_instanceDataBuffer = _handle;
		}

		void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags)
		{
			Binding& bind = m_draw.m_bind[_stage];
			bind.m_idx    = _handle.idx;
			bind.m_type   = uint8_t(Binding::Texture);
			bind.m_un.m_draw.m_textureFlags = (_flags&BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER)
				? BGFX_TEXTURE_INTERNAL_DEFAULT_SAMPLER
				: _flags
				;

			if (isValid(_sampler) )
			{
				uint32_t stage = _stage;
				setUniform(_sampler, &stage);
			}
		}

		void setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access)
		{
			Binding& bind = m_compute.m_bind[_stage];
			bind.m_idx    = _handle.idx;
			bind.m_type   = uint8_t(Binding::IndexBuffer);
			bind.m_un.m_compute.m_format = 0;
			bind.m_un.m_compute.m_access = uint8_t(_access);
			bind.m_un.m_compute.m_mip    = 0;
		}

		void setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access)
		{
			Binding& bind = m_compute.m_bind[_stage];
			bind.m_idx    = _handle.idx;
			bind.m_type   = uint8_t(Binding::VertexBuffer);
			bind.m_un.m_compute.m_format = 0;
			bind.m_un.m_compute.m_access = uint8_t(_access);
			bind.m_un.m_compute.m_mip    = 0;
		}

		void setImage(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format)
		{
			Binding& bind = m_compute.m_bind[_stage];
			bind.m_idx    = _handle.idx;
			bind.m_type   = uint8_t(Binding::Image);
			bind.m_un.m_compute.m_format = uint8_t(_format);
			bind.m_un.m_compute.m_access = uint8_t(_access);
			bind.m_un.m_compute.m_mip    = _mip;

			if (isValid(_sampler) )
			{
				uint32_t stage = _stage;
				setUniform(_sampler, &stage);
			}
		}

		void discard()
		{
			m_discard = false;
			m_draw.clear();
			m_compute.clear();
			m_stateFlags = BGFX_STATE_NONE;
		}

		uint32_t submit(uint8_t _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, int32_t _depth);

		uint32_t submit(uint8_t _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, int32_t _depth)
		{
			m_draw.m_startIndirect  = _start;
			m_draw.m_numIndirect    = _num;
			m_draw.m_indirectBuffer = _indirectHandle;
			OcclusionQueryHandle handle = BGFX_INVALID_HANDLE;
			return submit(_id, _program, handle, _depth);
		}

		uint32_t dispatch(uint8_t _id, ProgramHandle _handle, uint16_t _ngx, uint16_t _ngy, uint16_t _ngz, uint8_t _flags);

		uint32_t dispatch(uint8_t _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags)
		{
			m_compute.m_indirectBuffer = _indirectHandle;
			m_compute.m_startIndirect  = _start;
			m_compute.m_numIndirect    = _num;
			return dispatch(_id, _handle, 0, 0, 0, _flags);
		}

		void blit(uint8_t _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth);

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
			uint32_t offset = bx::strideAlign(m_iboffset, sizeof(uint16_t) );
			m_iboffset = offset + _num*sizeof(uint16_t);
			m_iboffset = bx::uint32_min(m_iboffset, BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
			_num = (m_iboffset-offset)/sizeof(uint16_t);
			return offset;
		}

		bool checkAvailTransientVertexBuffer(uint32_t _num, uint16_t _stride)
		{
			uint32_t offset = bx::strideAlign(m_vboffset, _stride);
			uint32_t vboffset = offset + _num * _stride;
			vboffset = bx::uint32_min(vboffset, BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
			uint32_t num = (vboffset-offset)/_stride;
			return num == _num;
		}

		uint32_t allocTransientVertexBuffer(uint32_t& _num, uint16_t _stride)
		{
			uint32_t offset = bx::strideAlign(m_vboffset, _stride);
			m_vboffset = offset + _num * _stride;
			m_vboffset = bx::uint32_min(m_vboffset, BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
			_num = (m_vboffset-offset)/_stride;
			return offset;
		}

		void writeUniform(UniformType::Enum _type, UniformHandle _handle, const void* _value, uint16_t _num)
		{
			UniformBuffer::update(m_uniformBuffer);
			m_uniformBuffer->writeUniform(_type, _handle.idx, _value, _num);
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

		void free(ShaderHandle _handle)
		{
			m_freeShaderHandle[m_numFreeShaderHandles] = _handle;
			++m_numFreeShaderHandles;
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

		void free(FrameBufferHandle _handle)
		{
			m_freeFrameBufferHandle[m_numFreeFrameBufferHandles] = _handle;
			++m_numFreeFrameBufferHandles;
		}

		void free(UniformHandle _handle)
		{
			m_freeUniformHandle[m_numFreeUniformHandles] = _handle;
			++m_numFreeUniformHandles;
		}

		void resetFreeHandles()
		{
			m_numFreeIndexBufferHandles  = 0;
			m_numFreeVertexDeclHandles   = 0;
			m_numFreeVertexBufferHandles = 0;
			m_numFreeShaderHandles       = 0;
			m_numFreeProgramHandles      = 0;
			m_numFreeTextureHandles      = 0;
			m_numFreeFrameBufferHandles  = 0;
			m_numFreeUniformHandles      = 0;
		}

		SortKey m_key;

		uint8_t m_viewRemap[BGFX_CONFIG_MAX_VIEWS];
		FrameBufferHandle m_fb[BGFX_CONFIG_MAX_VIEWS];
		Clear m_clear[BGFX_CONFIG_MAX_VIEWS];
		float m_colorPalette[BGFX_CONFIG_MAX_COLOR_PALETTE][4];
		Rect m_rect[BGFX_CONFIG_MAX_VIEWS];
		Rect m_scissor[BGFX_CONFIG_MAX_VIEWS];
		Matrix4 m_view[BGFX_CONFIG_MAX_VIEWS];
		Matrix4 m_proj[2][BGFX_CONFIG_MAX_VIEWS];
		uint8_t m_viewFlags[BGFX_CONFIG_MAX_VIEWS];
		uint8_t m_occlusion[BGFX_CONFIG_MAX_OCCUSION_QUERIES];

		uint64_t m_sortKeys[BGFX_CONFIG_MAX_DRAW_CALLS+1];
		RenderItemCount m_sortValues[BGFX_CONFIG_MAX_DRAW_CALLS+1];
		RenderItem m_renderItem[BGFX_CONFIG_MAX_DRAW_CALLS+1];
		RenderDraw m_draw;
		RenderCompute m_compute;
		uint32_t m_blitKeys[BGFX_CONFIG_MAX_BLIT_ITEMS+1];
		BlitItem m_blitItem[BGFX_CONFIG_MAX_BLIT_ITEMS+1];
		uint64_t m_stateFlags;
		uint32_t m_uniformBegin;
		uint32_t m_uniformEnd;
		uint32_t m_uniformMax;

		UniformBuffer* m_uniformBuffer;

		RenderItemCount m_num;
		RenderItemCount m_numRenderItems;
		RenderItemCount m_numDropped;
		uint16_t m_numBlitItems;

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
		uint16_t m_numFreeShaderHandles;
		uint16_t m_numFreeProgramHandles;
		uint16_t m_numFreeTextureHandles;
		uint16_t m_numFreeFrameBufferHandles;
		uint16_t m_numFreeUniformHandles;
		uint16_t m_numFreeWindowHandles;

		IndexBufferHandle m_freeIndexBufferHandle[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexDeclHandle m_freeVertexDeclHandle[BGFX_CONFIG_MAX_VERTEX_DECLS];
		VertexBufferHandle m_freeVertexBufferHandle[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		ShaderHandle m_freeShaderHandle[BGFX_CONFIG_MAX_SHADERS];
		ProgramHandle m_freeProgramHandle[BGFX_CONFIG_MAX_PROGRAMS];
		TextureHandle m_freeTextureHandle[BGFX_CONFIG_MAX_TEXTURES];
		FrameBufferHandle m_freeFrameBufferHandle[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		UniformHandle m_freeUniformHandle[BGFX_CONFIG_MAX_UNIFORMS];
		TextVideoMem* m_textVideoMem;
		HMD m_hmd;
		Stats m_perfStats;

		int64_t m_waitSubmit;
		int64_t m_waitRender;

		bool m_hmdInitialized;
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

		uint64_t remove()
		{
			BX_CHECK(0 == m_used.size(), "");

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

		typedef std::list<Free> FreeList;
		FreeList m_free;

		typedef stl::unordered_map<uint64_t, uint32_t> UsedList;
		UsedList m_used;
	};

	struct BX_NO_VTABLE RendererContextI
	{
		virtual ~RendererContextI() = 0;
		virtual RendererType::Enum getRendererType() const = 0;
		virtual const char* getRendererName() const = 0;
		virtual void flip(HMD& _hmd) = 0;
		virtual void createIndexBuffer(IndexBufferHandle _handle, Memory* _mem, uint16_t _flags) = 0;
		virtual void destroyIndexBuffer(IndexBufferHandle _handle) = 0;
		virtual void createVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl) = 0;
		virtual void destroyVertexDecl(VertexDeclHandle _handle) = 0;
		virtual void createVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle, uint16_t _flags) = 0;
		virtual void destroyVertexBuffer(VertexBufferHandle _handle) = 0;
		virtual void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) = 0;
		virtual void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) = 0;
		virtual void destroyDynamicIndexBuffer(IndexBufferHandle _handle) = 0;
		virtual void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) = 0;
		virtual void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, Memory* _mem) = 0;
		virtual void destroyDynamicVertexBuffer(VertexBufferHandle _handle) = 0;
		virtual void createShader(ShaderHandle _handle, Memory* _mem) = 0;
		virtual void destroyShader(ShaderHandle _handle) = 0;
		virtual void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) = 0;
		virtual void destroyProgram(ProgramHandle _handle) = 0;
		virtual void createTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags, uint8_t _skip) = 0;
		virtual void updateTextureBegin(TextureHandle _handle, uint8_t _side, uint8_t _mip) = 0;
		virtual void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) = 0;
		virtual void updateTextureEnd() = 0;
		virtual void readTexture(TextureHandle _handle, void* _data) = 0;
		virtual void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height) = 0;
		virtual void destroyTexture(TextureHandle _handle) = 0;
		virtual void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const TextureHandle* _textureHandles) = 0;
		virtual void createFrameBuffer(FrameBufferHandle _handle, void* _nwh, uint32_t _width, uint32_t _height, TextureFormat::Enum _depthFormat) = 0;
		virtual void destroyFrameBuffer(FrameBufferHandle _handle) = 0;
		virtual void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) = 0;
		virtual void destroyUniform(UniformHandle _handle) = 0;
		virtual void saveScreenShot(const char* _filePath) = 0;
		virtual void updateViewName(uint8_t _id, const char* _name) = 0;
		virtual void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) = 0;
		virtual void setMarker(const char* _marker, uint32_t _size) = 0;
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
		Context()
			: m_render(&m_frame[0])
			, m_submit(&m_frame[BGFX_CONFIG_MULTITHREADED ? 1 : 0])
			, m_numFreeDynamicIndexBufferHandles(0)
			, m_numFreeDynamicVertexBufferHandles(0)
			, m_colorPaletteDirty(0)
			, m_instBufferCount(0)
			, m_frames(0)
			, m_debug(BGFX_DEBUG_NONE)
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

		static int32_t renderThread(void* /*_userData*/)
		{
			BX_TRACE("render thread start");
			BGFX_PROFILER_SET_CURRENT_THREAD_NAME("bgfx - Render Thread");
			while (RenderFrame::Exiting != bgfx::renderFrame() ) {};
			BX_TRACE("render thread exit");
			return EXIT_SUCCESS;
		}

		// game thread
		bool init(RendererType::Enum _type);
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
			m_resolution.m_width  = bx::uint32_max(1, _width);
			m_resolution.m_height = bx::uint32_max(1, _height);
			m_resolution.m_flags  = _flags;

			m_flipAfterRender = !!(_flags & BGFX_RESET_FLIP_AFTER_RENDER);

			memset(m_fb, 0xff, sizeof(m_fb) );

			for (uint16_t ii = 0, num = m_textureHandle.getNumHandles(); ii < num; ++ii)
			{
				uint16_t textureIdx = m_textureHandle.getHandleAt(ii);
				const TextureRef& textureRef = m_textureRef[textureIdx];
				if (BackbufferRatio::Count != textureRef.m_bbRatio)
				{
					TextureHandle handle = { textureIdx };
					resizeTexture(handle
						, uint16_t(m_resolution.m_width)
						, uint16_t(m_resolution.m_height)
						);
					m_resolution.m_flags |= BGFX_RESET_INTERNAL_FORCE;
				}
			}
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

		BGFX_API_FUNC(void dbgTextImage(uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height, const void* _data, uint16_t _pitch) )
		{
			m_submit->m_textVideoMem->image(_x, _y, _width, _height, _data, _pitch);
		}

		BGFX_API_FUNC(const HMD* getHMD() )
		{
			if (m_submit->m_hmdInitialized)
			{
				return &m_submit->m_hmd;
			}

			return NULL;
		}

		BGFX_API_FUNC(const Stats* getPerfStats() )
		{
			return &m_submit->m_perfStats;
		}

		BGFX_API_FUNC(IndexBufferHandle createIndexBuffer(const Memory* _mem, uint16_t _flags) )
		{
			IndexBufferHandle handle = { m_indexBufferHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate index buffer handle.");
			if (isValid(handle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateIndexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
				cmdbuf.write(_flags);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyIndexBuffer(IndexBufferHandle _handle) )
		{
			BGFX_CHECK_HANDLE("destroyIndexBuffer", m_indexBufferHandle, _handle);

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

		BGFX_API_FUNC(VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl, uint16_t _flags) )
		{
			VertexBufferHandle handle = { m_vertexBufferHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate vertex buffer handle.");
			if (isValid(handle) )
			{
				VertexDeclHandle declHandle = findVertexDecl(_decl);
				m_declRef.add(handle, declHandle, _decl.m_hash);

				m_vertexBuffers[handle.idx].m_stride = _decl.m_stride;

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
				cmdbuf.write(declHandle);
				cmdbuf.write(_flags);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyVertexBuffer(VertexBufferHandle _handle) )
		{
			BGFX_CHECK_HANDLE("destroyVertexBuffer", m_vertexBufferHandle, _handle);

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

		uint64_t allocDynamicIndexBuffer(uint32_t _size, uint16_t _flags)
		{
			uint64_t ptr = m_dynIndexBufferAllocator.alloc(_size);
			if (ptr == NonLocalAllocator::invalidBlock)
			{
				IndexBufferHandle indexBufferHandle = { m_indexBufferHandle.alloc() };
				BX_WARN(isValid(indexBufferHandle), "Failed to allocate index buffer handle.");
				if (!isValid(indexBufferHandle) )
				{
					return ptr;
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicIndexBuffer);
				cmdbuf.write(indexBufferHandle);
				cmdbuf.write(BGFX_CONFIG_DYNAMIC_INDEX_BUFFER_SIZE);
				cmdbuf.write(_flags);

				m_dynIndexBufferAllocator.add(uint64_t(indexBufferHandle.idx) << 32, BGFX_CONFIG_DYNAMIC_INDEX_BUFFER_SIZE);
				ptr = m_dynIndexBufferAllocator.alloc(_size);
			}

			return ptr;
		}

		BGFX_API_FUNC(DynamicIndexBufferHandle createDynamicIndexBuffer(uint32_t _num, uint16_t _flags) )
		{
			DynamicIndexBufferHandle handle = BGFX_INVALID_HANDLE;
			const uint32_t indexSize = 0 == (_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
			uint32_t size = BX_ALIGN_16(_num*indexSize);

			uint64_t ptr = 0;
			if (0 != (_flags & BGFX_BUFFER_COMPUTE_WRITE) )
			{
				IndexBufferHandle indexBufferHandle = { m_indexBufferHandle.alloc() };
				if (!isValid(indexBufferHandle) )
				{
					return handle;
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicIndexBuffer);
				cmdbuf.write(indexBufferHandle);
				cmdbuf.write(size);
				cmdbuf.write(_flags);

				ptr = uint64_t(indexBufferHandle.idx) << 32;
			}
			else
			{
				ptr = allocDynamicIndexBuffer(size, _flags);
				if (ptr == NonLocalAllocator::invalidBlock)
				{
					return handle;
				}
			}

			handle.idx = m_dynamicIndexBufferHandle.alloc();
			BX_WARN(isValid(handle), "Failed to allocate dynamic index buffer handle.");
			if (!isValid(handle) )
			{
				return handle;
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
			BX_CHECK(0 == (_flags &  BGFX_BUFFER_COMPUTE_READ_WRITE), "Cannot initialize compute buffer from CPU.");
			const uint32_t indexSize = 0 == (_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;
			DynamicIndexBufferHandle handle = createDynamicIndexBuffer(_mem->size/indexSize, _flags);
			if (isValid(handle) )
			{
				updateDynamicIndexBuffer(handle, 0, _mem);
			}
			return handle;
		}

		BGFX_API_FUNC(void updateDynamicIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _startIndex, const Memory* _mem) )
		{
			BGFX_CHECK_HANDLE("updateDynamicIndexBuffer", m_dynamicIndexBufferHandle, _handle);

			DynamicIndexBuffer& dib = m_dynamicIndexBuffers[_handle.idx];
			BX_CHECK(0 == (dib.m_flags &  BGFX_BUFFER_COMPUTE_READ_WRITE), "Can't update GPU buffer from CPU.");
			const uint32_t indexSize = 0 == (dib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;

			if (dib.m_size < _mem->size
			&&  0 != (dib.m_flags & BGFX_BUFFER_ALLOW_RESIZE) )
			{
				m_dynIndexBufferAllocator.free(uint64_t(dib.m_handle.idx)<<32 | dib.m_offset);
				m_dynIndexBufferAllocator.compact();

				uint64_t ptr = allocDynamicIndexBuffer(_mem->size, dib.m_flags);
				dib.m_handle.idx = uint16_t(ptr>>32);
				dib.m_offset     = uint32_t(ptr);
				dib.m_size       = _mem->size;
				dib.m_startIndex = bx::strideAlign(dib.m_offset, indexSize)/indexSize;
			}

			uint32_t offset = (dib.m_startIndex + _startIndex)*indexSize;
			uint32_t size   = bx::uint32_min(bx::uint32_satsub(dib.m_size, _startIndex*indexSize), _mem->size);
			BX_CHECK(_mem->size <= size, "Truncating dynamic index buffer update (size %d, mem size %d)."
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
			BGFX_CHECK_HANDLE("destroyDynamicIndexBuffer", m_dynamicIndexBufferHandle, _handle);

			m_freeDynamicIndexBufferHandle[m_numFreeDynamicIndexBufferHandles++] = _handle;
		}

		void destroyDynamicIndexBufferInternal(DynamicIndexBufferHandle _handle)
		{
			DynamicIndexBuffer& dib = m_dynamicIndexBuffers[_handle.idx];

			if (0 != (dib.m_flags & BGFX_BUFFER_COMPUTE_WRITE) )
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
			if (ptr == NonLocalAllocator::invalidBlock)
			{
				VertexBufferHandle vertexBufferHandle = { m_vertexBufferHandle.alloc() };

				BX_WARN(isValid(vertexBufferHandle), "Failed to allocate dynamic vertex buffer handle.");
				if (!isValid(vertexBufferHandle) )
				{
					return NonLocalAllocator::invalidBlock;
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicVertexBuffer);
				cmdbuf.write(vertexBufferHandle);
				cmdbuf.write(BGFX_CONFIG_DYNAMIC_VERTEX_BUFFER_SIZE);
				cmdbuf.write(_flags);

				m_dynVertexBufferAllocator.add(uint64_t(vertexBufferHandle.idx)<<32, BGFX_CONFIG_DYNAMIC_VERTEX_BUFFER_SIZE);
				ptr = m_dynVertexBufferAllocator.alloc(_size);
			}

			return ptr;
		}

		BGFX_API_FUNC(DynamicVertexBufferHandle createDynamicVertexBuffer(uint32_t _num, const VertexDecl& _decl, uint16_t _flags) )
		{
			DynamicVertexBufferHandle handle = BGFX_INVALID_HANDLE;
			uint32_t size = bx::strideAlign16(_num*_decl.m_stride, _decl.m_stride);

			uint64_t ptr = 0;
			if (0 != (_flags & BGFX_BUFFER_COMPUTE_WRITE) )
			{
				VertexBufferHandle vertexBufferHandle = { m_vertexBufferHandle.alloc() };
				if (!isValid(vertexBufferHandle) )
				{
					return handle;
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateDynamicVertexBuffer);
				cmdbuf.write(vertexBufferHandle);
				cmdbuf.write(size);
				cmdbuf.write(_flags);

				ptr = uint64_t(vertexBufferHandle.idx)<<32;
			}
			else
			{
				ptr = allocDynamicVertexBuffer(size, _flags);
				if (ptr == NonLocalAllocator::invalidBlock)
				{
					return handle;
				}
			}

			VertexDeclHandle declHandle = findVertexDecl(_decl);

			handle.idx = m_dynamicVertexBufferHandle.alloc();
			DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[handle.idx];
			dvb.m_handle.idx  = uint16_t(ptr>>32);
			dvb.m_offset      = uint32_t(ptr);
			dvb.m_size        = _num * _decl.m_stride;
			dvb.m_startVertex = bx::strideAlign(dvb.m_offset, _decl.m_stride)/_decl.m_stride;
			dvb.m_numVertices = _num;
			dvb.m_stride      = _decl.m_stride;
			dvb.m_decl        = declHandle;
			dvb.m_flags       = _flags;
			m_declRef.add(dvb.m_handle, declHandle, _decl.m_hash);

			return handle;
		}

		BGFX_API_FUNC(DynamicVertexBufferHandle createDynamicVertexBuffer(const Memory* _mem, const VertexDecl& _decl, uint16_t _flags) )
		{
			uint32_t numVertices = _mem->size/_decl.m_stride;
			BX_CHECK(numVertices <= UINT16_MAX, "Num vertices exceeds maximum (num %d, max %d).", numVertices, UINT16_MAX);
			DynamicVertexBufferHandle handle = createDynamicVertexBuffer(uint16_t(numVertices), _decl, _flags);
			if (isValid(handle) )
			{
				updateDynamicVertexBuffer(handle, 0, _mem);
			}
			return handle;
		}

		BGFX_API_FUNC(void updateDynamicVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, const Memory* _mem) )
		{
			BGFX_CHECK_HANDLE("updateDynamicVertexBuffer", m_dynamicVertexBufferHandle, _handle);

			DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[_handle.idx];
			BX_CHECK(0 == (dvb.m_flags &  BGFX_BUFFER_COMPUTE_READ_WRITE), "Can't update GPU buffer from CPU.");

			if (dvb.m_size < _mem->size
			&&  0 != (dvb.m_flags & BGFX_BUFFER_ALLOW_RESIZE) )
			{
				m_dynVertexBufferAllocator.free(uint64_t(dvb.m_handle.idx)<<32 | dvb.m_offset);
				m_dynVertexBufferAllocator.compact();

				uint64_t ptr = allocDynamicVertexBuffer(_mem->size, dvb.m_flags);
				dvb.m_handle.idx  = uint16_t(ptr>>32);
				dvb.m_offset      = uint32_t(ptr);
				dvb.m_size        = _mem->size;
				dvb.m_numVertices = dvb.m_size / dvb.m_stride;
				dvb.m_startVertex = bx::strideAlign(dvb.m_offset, dvb.m_stride)/dvb.m_stride;
			}

			uint32_t offset = (dvb.m_startVertex + _startVertex)*dvb.m_stride;
			uint32_t size   = bx::uint32_min(bx::uint32_satsub(dvb.m_size, _startVertex*dvb.m_stride), _mem->size);
			BX_CHECK(_mem->size <= size, "Truncating dynamic vertex buffer update (size %d, mem size %d)."
				, dvb.m_size
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
			BGFX_CHECK_HANDLE("destroyDynamicVertexBuffer", m_dynamicVertexBufferHandle, _handle);

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

			if (0 != (dvb.m_flags & BGFX_BUFFER_COMPUTE_WRITE) )
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

				tib = (TransientIndexBuffer*)BX_ALLOC(g_allocator, sizeof(TransientIndexBuffer)+_size);
				tib->data   = (uint8_t*)&tib[1];
				tib->size   = _size;
				tib->handle = handle;
			}

			return tib;
		}

		void destroyTransientIndexBuffer(TransientIndexBuffer* _tib)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyDynamicIndexBuffer);
			cmdbuf.write(_tib->handle);

			m_submit->free(_tib->handle);
			BX_FREE(g_allocator, _tib);
		}

		BGFX_API_FUNC(void allocTransientIndexBuffer(TransientIndexBuffer* _tib, uint32_t _num) )
		{
			uint32_t offset = m_submit->allocTransientIndexBuffer(_num);

			TransientIndexBuffer& tib = *m_submit->m_transientIb;

			_tib->data       = &tib.data[offset];
			_tib->size       = _num * 2;
			_tib->handle     = tib.handle;
			_tib->startIndex = bx::strideAlign(offset, 2)/2;
		}

		TransientVertexBuffer* createTransientVertexBuffer(uint32_t _size, const VertexDecl* _decl = NULL)
		{
			TransientVertexBuffer* tvb = NULL;

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
				uint16_t flags = BGFX_BUFFER_NONE;
				cmdbuf.write(flags);

				tvb = (TransientVertexBuffer*)BX_ALLOC(g_allocator, sizeof(TransientVertexBuffer)+_size);
				tvb->data = (uint8_t*)&tvb[1];
				tvb->size = _size;
				tvb->startVertex = 0;
				tvb->stride = stride;
				tvb->handle = handle;
				tvb->decl   = declHandle;
			}

			return tvb;
		}

		void destroyTransientVertexBuffer(TransientVertexBuffer* _tvb)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyDynamicVertexBuffer);
			cmdbuf.write(_tvb->handle);

			m_submit->free(_tvb->handle);
			BX_FREE(g_allocator, _tvb);
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
			_tvb->startVertex = bx::strideAlign(offset, _decl.m_stride)/_decl.m_stride;
			_tvb->stride = _decl.m_stride;
			_tvb->handle = dvb.handle;
			_tvb->decl   = declHandle;
		}

		BGFX_API_FUNC(const InstanceDataBuffer* allocInstanceDataBuffer(uint32_t _num, uint16_t _stride) )
		{
			++m_instBufferCount;

			uint16_t stride = BX_ALIGN_16(_stride);
			uint32_t offset = m_submit->allocTransientVertexBuffer(_num, stride);

			TransientVertexBuffer& dvb = *m_submit->m_transientVb;
			InstanceDataBuffer* idb = (InstanceDataBuffer*)BX_ALLOC(g_allocator, sizeof(InstanceDataBuffer) );
			idb->data   = &dvb.data[offset];
			idb->size   = _num * stride;
			idb->offset = offset;
			idb->num    = _num;
			idb->stride = stride;
			idb->handle = dvb.handle;

			return idb;
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
			bx::MemoryReader reader(_mem->data, _mem->size);

			uint32_t magic;
			bx::read(&reader, magic);

			if (BGFX_CHUNK_MAGIC_CSH != magic
			&&  BGFX_CHUNK_MAGIC_FSH != magic
			&&  BGFX_CHUNK_MAGIC_VSH != magic)
			{
				BX_WARN(false, "Invalid shader signature! %c%c%c%d."
					, ( (uint8_t*)&magic)[0]
					, ( (uint8_t*)&magic)[1]
					, ( (uint8_t*)&magic)[2]
					, ( (uint8_t*)&magic)[3]
					);
				ShaderHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			ShaderHandle handle = { m_shaderHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate shader handle.");
			if (isValid(handle) )
			{
				uint32_t iohash;
				bx::read(&reader, iohash);

				uint16_t count;
				bx::read(&reader, count);

				ShaderRef& sr = m_shaderRef[handle.idx];
				sr.m_refCount = 1;
				sr.m_hash     = iohash;
				sr.m_num      = 0;
				sr.m_owned    = false;
				sr.m_uniforms = NULL;

				UniformHandle* uniforms = (UniformHandle*)alloca(count*sizeof(UniformHandle) );

				for (uint32_t ii = 0; ii < count; ++ii)
				{
					uint8_t nameSize;
					bx::read(&reader, nameSize);

					char name[256];
					bx::read(&reader, &name, nameSize);
					name[nameSize] = '\0';

					uint8_t type;
					bx::read(&reader, type);
					type &= ~BGFX_UNIFORM_MASK;

					uint8_t num;
					bx::read(&reader, num);

					uint16_t regIndex;
					bx::read(&reader, regIndex);

					uint16_t regCount;
					bx::read(&reader, regCount);

					PredefinedUniform::Enum predefined = nameToPredefinedUniformEnum(name);
					if (PredefinedUniform::Count == predefined)
					{
						uniforms[sr.m_num] = createUniform(name, UniformType::Enum(type), regCount);
						sr.m_num++;
					}
				}

				if (0 != sr.m_num)
				{
					uint32_t size = sr.m_num*sizeof(UniformHandle);
					sr.m_uniforms = (UniformHandle*)BX_ALLOC(g_allocator, size);
					memcpy(sr.m_uniforms, uniforms, size);
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateShader);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
			}

			return handle;
		}

		BGFX_API_FUNC(uint16_t getShaderUniforms(ShaderHandle _handle, UniformHandle* _uniforms, uint16_t _max) )
		{
			if (!isValid(_handle) )
			{
				BX_WARN(false, "Passing invalid shader handle to bgfx::getShaderUniforms.");
				return 0;
			}

			ShaderRef& sr = m_shaderRef[_handle.idx];
			if (NULL != _uniforms)
			{
				memcpy(_uniforms, sr.m_uniforms, bx::uint16_min(_max, sr.m_num)*sizeof(UniformHandle) );
			}

			return sr.m_num;
		}

		BGFX_API_FUNC(void destroyShader(ShaderHandle _handle) )
		{
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
			ShaderRef& sr = m_shaderRef[_handle.idx];
			if (!sr.m_owned)
			{
				sr.m_owned = true;
				shaderDecRef(_handle);
			}
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
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyShader);
				cmdbuf.write(_handle);
				m_submit->free(_handle);

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
			}
		}

		BGFX_API_FUNC(ProgramHandle createProgram(ShaderHandle _vsh, ShaderHandle _fsh, bool _destroyShaders) )
		{
			if (!isValid(_vsh)
			||  !isValid(_fsh) )
			{
				BX_WARN(false, "Vertex/fragment shader is invalid (vsh %d, fsh %d).", _vsh.idx, _fsh.idx);
				ProgramHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			ProgramHashMap::const_iterator it = m_programHashMap.find(uint32_t(_fsh.idx<<16)|_vsh.idx);
			if (it != m_programHashMap.end() )
			{
				ProgramHandle handle = it->second;
				ProgramRef& pr = m_programRef[handle.idx];
				++pr.m_refCount;
				return handle;
			}

			const ShaderRef& vsr = m_shaderRef[_vsh.idx];
			const ShaderRef& fsr = m_shaderRef[_fsh.idx];
			if (vsr.m_hash != fsr.m_hash)
			{
				BX_WARN(vsr.m_hash == fsr.m_hash, "Vertex shader output doesn't match fragment shader input.");
				ProgramHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			ProgramHandle handle;
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

				m_programHashMap.insert(stl::make_pair(uint32_t(_fsh.idx<<16)|_vsh.idx, handle) );

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateProgram);
				cmdbuf.write(handle);
				cmdbuf.write(_vsh);
				cmdbuf.write(_fsh);
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
			if (!isValid(_vsh) )
			{
				BX_WARN(false, "Vertex/fragment shader is invalid (vsh %d).", _vsh.idx);
				ProgramHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			ProgramHashMap::const_iterator it = m_programHashMap.find(_vsh.idx);
			if (it != m_programHashMap.end() )
			{
				ProgramHandle handle = it->second;
				ProgramRef& pr = m_programRef[handle.idx];
				++pr.m_refCount;
				return handle;
			}

			ProgramHandle handle;
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

				m_programHashMap.insert(stl::make_pair(uint32_t(_vsh.idx), handle) );

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateProgram);
				cmdbuf.write(handle);
				cmdbuf.write(_vsh);
				cmdbuf.write(fsh);
			}

			if (_destroyShader)
			{
				shaderTakeOwnership(_vsh);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyProgram(ProgramHandle _handle) )
		{
			BGFX_CHECK_HANDLE("destroyProgram", m_programHandle, _handle);

			ProgramRef& pr = m_programRef[_handle.idx];
			int32_t refs = --pr.m_refCount;
			if (0 == refs)
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyProgram);
				cmdbuf.write(_handle);
				m_submit->free(_handle);

				shaderDecRef(pr.m_vsh);
				uint32_t hash = pr.m_vsh.idx;

				if (isValid(pr.m_fsh) )
				{
					shaderDecRef(pr.m_fsh);
					hash |= pr.m_fsh.idx << 16;
				}

				m_programHashMap.erase(m_programHashMap.find(hash) );
			}
		}

		BGFX_API_FUNC(TextureHandle createTexture(const Memory* _mem, uint32_t _flags, uint8_t _skip, TextureInfo* _info, BackbufferRatio::Enum _ratio) )
		{
			TextureInfo ti;
			if (NULL == _info)
			{
				_info = &ti;
			}

			ImageContainer imageContainer;
			if (imageParse(imageContainer, _mem->data, _mem->size) )
			{
				calcTextureSize(*_info
					, (uint16_t)imageContainer.m_width
					, (uint16_t)imageContainer.m_height
					, (uint16_t)imageContainer.m_depth
					, imageContainer.m_cubeMap
					, imageContainer.m_numMips
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
			}

			TextureHandle handle = { m_textureHandle.alloc() };
			BX_WARN(isValid(handle), "Failed to allocate texture handle.");
			if (isValid(handle) )
			{
				TextureRef& ref = m_textureRef[handle.idx];
				ref.m_refCount = 1;
				ref.m_bbRatio  = uint8_t(_ratio);
				ref.m_format   = uint8_t(_info->format);
				ref.m_owned    = false;

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateTexture);
				cmdbuf.write(handle);
				cmdbuf.write(_mem);
				cmdbuf.write(_flags);
				cmdbuf.write(_skip);
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyTexture(TextureHandle _handle) )
		{
			BGFX_CHECK_HANDLE("destroyTexture", m_textureHandle, _handle);

			if (!isValid(_handle) )
			{
				BX_WARN(false, "Passing invalid texture handle to bgfx::destroyTexture");
				return;
			}

			textureDecRef(_handle);
		}

		BGFX_API_FUNC(void readTexture(TextureHandle _handle, void* _data) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::ReadTexture);
			cmdbuf.write(_handle);
			cmdbuf.write(_data);
		}

		BGFX_API_FUNC(void readTexture(FrameBufferHandle _handle, uint8_t _attachment, void* _data) )
		{
			const FrameBufferRef& ref = m_frameBufferRef[_handle.idx];
			BX_CHECK(!ref.m_window, "Can't sample window frame buffer.");
			TextureHandle textureHandle = ref.un.m_th[_attachment];
			BX_CHECK(isValid(textureHandle), "Frame buffer texture %d is invalid.", _attachment);
			readTexture(textureHandle, _data);
		}

		void resizeTexture(TextureHandle _handle, uint16_t _width, uint16_t _height)
		{
			const TextureRef& textureRef = m_textureRef[_handle.idx];
			BX_CHECK(BackbufferRatio::Count != textureRef.m_bbRatio, "");

			getTextureSizeFromRatio(BackbufferRatio::Enum(textureRef.m_bbRatio), _width, _height);

			BX_TRACE("Resize %3d: %4dx%d %s"
				, _handle.idx
				, _width
				, _height
				, bgfx::getName(TextureFormat::Enum(textureRef.m_format) )
				);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::ResizeTexture);
			cmdbuf.write(_handle);
			cmdbuf.write(_width);
			cmdbuf.write(_height);
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
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyTexture);
				cmdbuf.write(_handle);
				m_submit->free(_handle);
			}
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

		bool checkFrameBuffer(uint8_t _num, const TextureHandle* _handles) const
		{
			uint8_t color = 0;
			uint8_t depth = 0;

			for (uint32_t ii = 0; ii < _num; ++ii)
			{
				TextureHandle texHandle = _handles[ii];
				if (isDepth(TextureFormat::Enum(m_textureRef[texHandle.idx].m_format)))
				{
					++depth;
				}
				else
				{
					++color;
				}
			}

			return color <= g_caps.maxFBAttachments
				&& depth <= 1
				;
		}

		BGFX_API_FUNC(FrameBufferHandle createFrameBuffer(uint8_t _num, const TextureHandle* _handles, bool _destroyTextures) )
		{
			BX_CHECK(checkFrameBuffer(_num, _handles)
				, "Too many frame buffer attachments (num attachments: %d, max color attachments %d)!"
				, _num
				, g_caps.maxFBAttachments
				);

			FrameBufferHandle handle = { m_frameBufferHandle.alloc() };
			BX_WARN(isValid(handle), "Failed to allocate frame buffer handle.");

			if (isValid(handle) )
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateFrameBuffer);
				cmdbuf.write(handle);
				cmdbuf.write(false);
				cmdbuf.write(_num);

				FrameBufferRef& ref = m_frameBufferRef[handle.idx];
				ref.m_window = false;
				memset(ref.un.m_th, 0xff, sizeof(ref.un.m_th) );
				BackbufferRatio::Enum bbRatio = BackbufferRatio::Enum(m_textureRef[_handles[0].idx].m_bbRatio);
				for (uint32_t ii = 0; ii < _num; ++ii)
				{
					TextureHandle texHandle = _handles[ii];
					BGFX_CHECK_HANDLE("createFrameBuffer texture handle", m_textureHandle, texHandle);
					BX_CHECK(bbRatio == m_textureRef[texHandle.idx].m_bbRatio, "Mismatch in texture back-buffer ratio.");
					BX_UNUSED(bbRatio);

					cmdbuf.write(texHandle);

					ref.un.m_th[ii] = texHandle;
					textureIncRef(texHandle);
				}
			}

			if (_destroyTextures)
			{
				for (uint32_t ii = 0; ii < _num; ++ii)
				{
					textureTakeOwnership(_handles[ii]);
				}
			}

			return handle;
		}

		BGFX_API_FUNC(FrameBufferHandle createFrameBuffer(void* _nwh, uint16_t _width, uint16_t _height, TextureFormat::Enum _depthFormat) )
		{
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
				cmdbuf.write(_depthFormat);

				FrameBufferRef& ref = m_frameBufferRef[handle.idx];
				ref.m_window = true;
				ref.un.m_nwh = _nwh;
			}

			return handle;
		}

		BGFX_API_FUNC(void destroyFrameBuffer(FrameBufferHandle _handle) )
		{
			BGFX_CHECK_HANDLE("destroyFrameBuffer", m_frameBufferHandle, _handle);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyFrameBuffer);
			cmdbuf.write(_handle);
			m_submit->free(_handle);

			FrameBufferRef& ref = m_frameBufferRef[_handle.idx];
			if (!ref.m_window)
			{
				for (uint32_t ii = 0; ii < BX_COUNTOF(ref.un.m_th); ++ii)
				{
					TextureHandle th = ref.un.m_th[ii];
					if (isValid(th) )
					{
						textureDecRef(th);
					}
				}
			}
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

				uint32_t oldsize = g_uniformTypeSize[uniform.m_type];
				uint32_t newsize = g_uniformTypeSize[_type];

				if (oldsize < newsize
				||  uniform.m_num < _num)
				{
					uniform.m_type = oldsize < newsize ? _type : uniform.m_type;
					uniform.m_num  = bx::uint16_max(uniform.m_num, _num);

					CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateUniform);
					cmdbuf.write(handle);
					cmdbuf.write(uniform.m_type);
					cmdbuf.write(uniform.m_num);
					uint8_t len = (uint8_t)strlen(_name)+1;
					cmdbuf.write(len);
					cmdbuf.write(_name, len);
				}

				++uniform.m_refCount;
				return handle;
			}

			UniformHandle handle = { m_uniformHandle.alloc() };

			BX_WARN(isValid(handle), "Failed to allocate uniform handle.");
			if (isValid(handle) )
			{
				BX_TRACE("Creating uniform (handle %3d) %s", handle.idx, _name);

				UniformRef& uniform = m_uniformRef[handle.idx];
				uniform.m_refCount = 1;
				uniform.m_type = _type;
				uniform.m_num  = _num;

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
			BGFX_CHECK_HANDLE("destroyUniform", m_uniformHandle, _handle);

			UniformRef& uniform = m_uniformRef[_handle.idx];
			BX_CHECK(uniform.m_refCount > 0, "Destroying already destroyed uniform %d.", _handle.idx);
			int32_t refs = --uniform.m_refCount;

			if (0 == refs)
			{
				for (UniformHashMap::iterator it = m_uniformHashMap.begin(), itEnd = m_uniformHashMap.end(); it != itEnd; ++it)
				{
					if (it->second.idx == _handle.idx)
					{
						m_uniformHashMap.erase(it);
						break;
					}
				}

				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyUniform);
				cmdbuf.write(_handle);
				m_submit->free(_handle);
			}
		}

		BGFX_API_FUNC(OcclusionQueryHandle createOcclusionQuery() )
		{
			OcclusionQueryHandle handle = { m_occlusionQueryHandle.alloc() };
			if (isValid(handle) )
			{
				m_submit->m_occlusion[handle.idx] = UINT8_MAX;
			}
			return handle;
		}

		BGFX_API_FUNC(OcclusionQueryResult::Enum getResult(OcclusionQueryHandle _handle) )
		{
			BGFX_CHECK_HANDLE("destroyOcclusionQuery", m_occlusionQueryHandle, _handle);

			switch (m_submit->m_occlusion[_handle.idx])
			{
			case 0:         return OcclusionQueryResult::Invisible;
			case UINT8_MAX: return OcclusionQueryResult::NoResult;
			default:;
			}

			return OcclusionQueryResult::Visible;
		}

		BGFX_API_FUNC(void destroyOcclusionQuery(OcclusionQueryHandle _handle) )
		{
			BGFX_CHECK_HANDLE("destroyOcclusionQuery", m_occlusionQueryHandle, _handle);
			m_occlusionQueryHandle.free(_handle.idx);
		}

		BGFX_API_FUNC(void saveScreenShot(const char* _filePath) )
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::SaveScreenShot);
			uint16_t len = (uint16_t)strlen(_filePath)+1;
			cmdbuf.write(len);
			cmdbuf.write(_filePath, len);
		}

		BGFX_API_FUNC(void setPaletteColor(uint8_t _index, const float _rgba[4]) )
		{
			BX_CHECK(_index < BGFX_CONFIG_MAX_COLOR_PALETTE, "Color palette index out of bounds %d (max: %d)."
				, _index
				, BGFX_CONFIG_MAX_COLOR_PALETTE
				);
			memcpy(&m_clearColor[_index][0], _rgba, 16);
			m_colorPaletteDirty = 2;
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
			rect.m_width  = bx::uint16_max(_width,  1);
			rect.m_height = bx::uint16_max(_height, 1);
		}

		BGFX_API_FUNC(void setViewScissor(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height) )
		{
			Rect& scissor = m_scissor[_id];
			scissor.m_x = _x;
			scissor.m_y = _y;
			scissor.m_width  = _width;
			scissor.m_height = _height;
		}

		BGFX_API_FUNC(void setViewClear(uint8_t _id, uint16_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil) )
		{
			Clear& clear = m_clear[_id];
			clear.m_flags = _flags;
			clear.m_index[0] = uint8_t(_rgba>>24);
			clear.m_index[1] = uint8_t(_rgba>>16);
			clear.m_index[2] = uint8_t(_rgba>> 8);
			clear.m_index[3] = uint8_t(_rgba>> 0);
			clear.m_depth    = _depth;
			clear.m_stencil  = _stencil;
		}

		BGFX_API_FUNC(void setViewClear(uint8_t _id, uint16_t _flags, float _depth, uint8_t _stencil, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4, uint8_t _5, uint8_t _6, uint8_t _7) )
		{
			Clear& clear = m_clear[_id];
			clear.m_flags = (_flags & ~BGFX_CLEAR_COLOR)
				| (0xff != (_0&_1&_2&_3&_4&_5&_6&_7) ? BGFX_CLEAR_COLOR|BGFX_CLEAR_COLOR_USE_PALETTE : 0)
				;
			clear.m_index[0] = _0;
			clear.m_index[1] = _1;
			clear.m_index[2] = _2;
			clear.m_index[3] = _3;
			clear.m_index[4] = _4;
			clear.m_index[5] = _5;
			clear.m_index[6] = _6;
			clear.m_index[7] = _7;
			clear.m_depth    = _depth;
			clear.m_stencil  = _stencil;
		}

		BGFX_API_FUNC(void setViewSeq(uint8_t _id, bool _enabled) )
		{
			m_seqMask[_id] = _enabled ? 0xffff : 0x0;
		}

		BGFX_API_FUNC(void setViewFrameBuffer(uint8_t _id, FrameBufferHandle _handle) )
		{
			BGFX_CHECK_HANDLE_INVALID_OK("setViewFrameBuffer", m_frameBufferHandle, _handle);
			m_fb[_id] = _handle;
		}

		BGFX_API_FUNC(void setViewTransform(uint8_t _id, const void* _view, const void* _proj, uint8_t _flags, const void* _proj1) )
		{
			m_viewFlags[_id] = _flags;

			if (NULL != _view)
			{
				memcpy(m_view[_id].un.val, _view, sizeof(Matrix4) );
			}
			else
			{
				m_view[_id].setIdentity();
			}

			if (NULL != _proj)
			{
				memcpy(m_proj[0][_id].un.val, _proj, sizeof(Matrix4) );
			}
			else
			{
				m_proj[0][_id].setIdentity();
			}

			if (NULL != _proj1)
			{
				memcpy(m_proj[1][_id].un.val, _proj1, sizeof(Matrix4) );
			}
			else
			{
				memcpy(m_proj[1][_id].un.val, m_proj[0][_id].un.val, sizeof(Matrix4) );
			}
		}

		BGFX_API_FUNC(void resetView(uint8_t _id) )
		{
			setViewRect(_id, 0, 0, 1, 1);
			setViewScissor(_id, 0, 0, 0, 0);
			setViewClear(_id, BGFX_CLEAR_NONE, 0, 0.0f, 0);
			setViewSeq(_id, false);
			bgfx::FrameBufferHandle invalid = BGFX_INVALID_HANDLE;
			setViewFrameBuffer(_id, invalid);
			setViewTransform(_id, NULL, NULL, BGFX_VIEW_NONE, NULL);
		}

		BGFX_API_FUNC(void setViewRemap(uint8_t _id, uint8_t _num, const void* _remap) )
		{
			const uint32_t num = bx::uint32_min(_id + _num, BGFX_CONFIG_MAX_VIEWS) - _id;
			if (NULL == _remap)
			{
				for (uint32_t ii = 0; ii < num; ++ii)
				{
					uint8_t id = uint8_t(ii+_id);
					m_viewRemap[id] = id;
				}
			}
			else
			{
				memcpy(&m_viewRemap[_id], _remap, num);
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

		BGFX_API_FUNC(void setCondition(OcclusionQueryHandle _handle, bool _visible) )
		{
			m_submit->setCondition(_handle, _visible);
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

		BGFX_API_FUNC(uint32_t allocTransform(Transform* _transform, uint16_t _num) )
		{
			return m_submit->allocTransform(_transform, _num);
		}

		BGFX_API_FUNC(void setTransform(uint32_t _cache, uint16_t _num) )
		{
			m_submit->setTransform(_cache, _num);
		}

		BGFX_API_FUNC(void setUniform(UniformHandle _handle, const void* _value, uint16_t _num) )
		{
			BGFX_CHECK_HANDLE("setUniform", m_uniformHandle, _handle);
			UniformRef& uniform = m_uniformRef[_handle.idx];
			BX_CHECK(uniform.m_num >= _num, "Truncated uniform update. %d (max: %d)", _num, uniform.m_num);
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
			{
				BX_CHECK(m_uniformSet.end() == m_uniformSet.find(_handle.idx)
					, "Uniform %d (%s) was already set for this draw call."
					, _handle.idx
					, getName(_handle)
					);
				m_uniformSet.insert(_handle.idx);
			}
			m_submit->writeUniform(uniform.m_type, _handle, _value, bx::uint16_min(uniform.m_num, _num) );
		}

		BGFX_API_FUNC(void setIndexBuffer(IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices) )
		{
			BGFX_CHECK_HANDLE("setIndexBuffer", m_indexBufferHandle, _handle);
			m_submit->setIndexBuffer(_handle, _firstIndex, _numIndices);
		}

		BGFX_API_FUNC(void setIndexBuffer(DynamicIndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices) )
		{
			BGFX_CHECK_HANDLE("setIndexBuffer", m_dynamicIndexBufferHandle, _handle);
			m_submit->setIndexBuffer(m_dynamicIndexBuffers[_handle.idx], _firstIndex, _numIndices);
		}

		BGFX_API_FUNC(void setIndexBuffer(const TransientIndexBuffer* _tib, uint32_t _firstIndex, uint32_t _numIndices) )
		{
			BGFX_CHECK_HANDLE("setIndexBuffer", m_indexBufferHandle, _tib->handle);
			m_submit->setIndexBuffer(_tib, _firstIndex, _numIndices);
		}

		BGFX_API_FUNC(void setVertexBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices) )
		{
			BGFX_CHECK_HANDLE("setVertexBuffer", m_vertexBufferHandle, _handle);
			m_submit->setVertexBuffer(_handle, _startVertex, _numVertices);
		}

		BGFX_API_FUNC(void setVertexBuffer(DynamicVertexBufferHandle _handle, uint32_t _numVertices) )
		{
			BGFX_CHECK_HANDLE("setVertexBuffer", m_dynamicVertexBufferHandle, _handle);
			m_submit->setVertexBuffer(m_dynamicVertexBuffers[_handle.idx], _numVertices);
		}

		BGFX_API_FUNC(void setVertexBuffer(const TransientVertexBuffer* _tvb, uint32_t _startVertex, uint32_t _numVertices) )
		{
			BGFX_CHECK_HANDLE("setVertexBuffer", m_vertexBufferHandle, _tvb->handle);
			m_submit->setVertexBuffer(_tvb, _startVertex, _numVertices);
		}

		BGFX_API_FUNC(void setInstanceDataBuffer(const InstanceDataBuffer* _idb, uint32_t _num) )
		{
			--m_instBufferCount;

			m_submit->setInstanceDataBuffer(_idb, _num);
		}

		BGFX_API_FUNC(void setInstanceDataBuffer(VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num) )
		{
			BGFX_CHECK_HANDLE("setInstanceDataBuffer", m_vertexBufferHandle, _handle);
			const VertexBuffer& vb = m_vertexBuffers[_handle.idx];
			m_submit->setInstanceDataBuffer(_handle, _startVertex, _num, vb.m_stride);
		}

		BGFX_API_FUNC(void setInstanceDataBuffer(DynamicVertexBufferHandle _handle, uint32_t _startVertex, uint32_t _num) )
		{
			BGFX_CHECK_HANDLE("setInstanceDataBuffer", m_dynamicVertexBufferHandle, _handle);
			const DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[_handle.idx];
			m_submit->setInstanceDataBuffer(dvb.m_handle
				, dvb.m_startVertex + _startVertex
				, _num
				, dvb.m_stride
				);
		}

		BGFX_API_FUNC(void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags) )
		{
			BGFX_CHECK_HANDLE_INVALID_OK("setTexture/TextureHandle", m_textureHandle, _handle);
			m_submit->setTexture(_stage, _sampler, _handle, _flags);
		}

		BGFX_API_FUNC(void setTexture(uint8_t _stage, UniformHandle _sampler, FrameBufferHandle _handle, uint8_t _attachment, uint32_t _flags) )
		{
			BGFX_CHECK_HANDLE_INVALID_OK("setTexture/FrameBufferHandle", m_frameBufferHandle, _handle);
			BX_CHECK(_attachment < g_caps.maxFBAttachments, "Frame buffer attachment index %d is invalid.", _attachment);
			TextureHandle textureHandle = BGFX_INVALID_HANDLE;
			if (isValid(_handle) )
			{
				const FrameBufferRef& ref = m_frameBufferRef[_handle.idx];
				BX_CHECK(!ref.m_window, "Can't sample window frame buffer.");
				textureHandle = ref.un.m_th[_attachment];
				BX_CHECK(isValid(textureHandle), "Frame buffer texture %d is invalid.", _attachment);
			}

			m_submit->setTexture(_stage, _sampler, textureHandle, _flags);
		}

		BGFX_API_FUNC(uint32_t submit(uint8_t _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, int32_t _depth) )
		{
			BGFX_CHECK_HANDLE_INVALID_OK("submit", m_programHandle, _program);
			BGFX_CHECK_HANDLE_INVALID_OK("submit", m_occlusionQueryHandle, _occlusionQuery);
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
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

			return m_submit->submit(_id, _program, _occlusionQuery, _depth);
		}

		BGFX_API_FUNC(uint32_t submit(uint8_t _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, int32_t _depth) )
		{
			BGFX_CHECK_HANDLE_INVALID_OK("submit", m_programHandle, _handle);
			BGFX_CHECK_HANDLE("submit", m_vertexBufferHandle, _indirectHandle);
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
			{
				m_uniformSet.clear();
			}
			return m_submit->submit(_id, _handle, _indirectHandle, _start, _num, _depth);
		}

		BGFX_API_FUNC(void setBuffer(uint8_t _stage, IndexBufferHandle _handle, Access::Enum _access) )
		{
			BGFX_CHECK_HANDLE("setBuffer", m_indexBufferHandle, _handle);
			m_submit->setBuffer(_stage, _handle, _access);
		}

		BGFX_API_FUNC(void setBuffer(uint8_t _stage, VertexBufferHandle _handle, Access::Enum _access) )
		{
			BGFX_CHECK_HANDLE("setBuffer", m_vertexBufferHandle, _handle);
			m_submit->setBuffer(_stage, _handle, _access);
		}

		BGFX_API_FUNC(void setBuffer(uint8_t _stage, DynamicIndexBufferHandle _handle, Access::Enum _access) )
		{
			BGFX_CHECK_HANDLE("setBuffer", m_dynamicIndexBufferHandle, _handle);
			const DynamicIndexBuffer& dib = m_dynamicIndexBuffers[_handle.idx];
			m_submit->setBuffer(_stage, dib.m_handle, _access);
		}

		BGFX_API_FUNC(void setBuffer(uint8_t _stage, DynamicVertexBufferHandle _handle, Access::Enum _access) )
		{
			BGFX_CHECK_HANDLE("setBuffer", m_dynamicVertexBufferHandle, _handle);
			const DynamicVertexBuffer& dvb = m_dynamicVertexBuffers[_handle.idx];
			m_submit->setBuffer(_stage, dvb.m_handle, _access);
		}

		BGFX_API_FUNC(void setBuffer(uint8_t _stage, IndirectBufferHandle _handle, Access::Enum _access) )
		{
			BGFX_CHECK_HANDLE("setBuffer", m_vertexBufferHandle, _handle);
			VertexBufferHandle handle = { _handle.idx };
			m_submit->setBuffer(_stage, handle, _access);
		}

		BGFX_API_FUNC(void setImage(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format) )
		{
			_format = TextureFormat::Count == _format ? TextureFormat::Enum(m_textureRef[_handle.idx].m_format) : _format;
			BX_CHECK(_format != TextureFormat::BGRA8
					, "Can't use TextureFormat::BGRA8 with compute, use TextureFormat::RGBA8 instead."
					);
			m_submit->setImage(_stage, _sampler, _handle, _mip, _access, _format);
		}

		BGFX_API_FUNC(void setImage(uint8_t _stage, UniformHandle _sampler, FrameBufferHandle _handle, uint8_t _attachment, Access::Enum _access, TextureFormat::Enum _format) )
		{
			BX_CHECK(_attachment < g_caps.maxFBAttachments, "Frame buffer attachment index %d is invalid.", _attachment);
			TextureHandle textureHandle = BGFX_INVALID_HANDLE;
			if (isValid(_handle) )
			{
				const FrameBufferRef& ref = m_frameBufferRef[_handle.idx];
				BX_CHECK(!ref.m_window, "Can't sample window frame buffer.");
				textureHandle = ref.un.m_th[_attachment];
				BX_CHECK(isValid(textureHandle), "Frame buffer texture %d is invalid.", _attachment);
			}

			setImage(_stage, _sampler, textureHandle, 0, _access, _format);
		}

		BGFX_API_FUNC(uint32_t dispatch(uint8_t _id, ProgramHandle _handle, uint16_t _numX, uint16_t _numY, uint16_t _numZ, uint8_t _flags) )
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
			{
				m_uniformSet.clear();
			}
			return m_submit->dispatch(_id, _handle, _numX, _numY, _numZ, _flags);
		}

		BGFX_API_FUNC(uint32_t dispatch(uint8_t _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start, uint16_t _num, uint8_t _flags) )
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
			{
				m_uniformSet.clear();
			}
			return m_submit->dispatch(_id, _handle, _indirectHandle, _start, _num, _flags);
		}

		BGFX_API_FUNC(void discard() )
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_UNIFORM) )
			{
				m_uniformSet.clear();
			}
			m_submit->discard();
		}

		BGFX_API_FUNC(void blit(uint8_t _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth) )
		{
			const TextureRef& src = m_textureRef[_src.idx];
			const TextureRef& dst = m_textureRef[_dst.idx];
			BX_CHECK(src.m_format == dst.m_format
				, "Texture format must match (src %s, dst %s)."
				, bgfx::getName(TextureFormat::Enum(src.m_format) )
				, bgfx::getName(TextureFormat::Enum(dst.m_format) )
				);
			BX_UNUSED(src, dst);
			m_submit->blit(_id, _dst, _dstMip, _dstX, _dstY, _dstZ, _src, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
		}

		BGFX_API_FUNC(void blit(uint8_t _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, FrameBufferHandle _src, uint8_t _attachment, uint8_t _srcMip, uint16_t _srcX, uint16_t _srcY, uint16_t _srcZ, uint16_t _width, uint16_t _height, uint16_t _depth) )
		{
			const FrameBufferRef& ref = m_frameBufferRef[_src.idx];
			BX_CHECK(!ref.m_window, "Can't sample window frame buffer.");
			TextureHandle textureHandle = ref.un.m_th[_attachment];
			BX_CHECK(isValid(textureHandle), "Frame buffer texture %d is invalid.", _attachment);
			blit(_id, _dst, _dstMip, _dstX, _dstY, _dstZ, textureHandle, _srcMip, _srcX, _srcY, _srcZ, _width, _height, _depth);
		}

		BGFX_API_FUNC(uint32_t frame() );

		void dumpViewStats();
		void freeDynamicBuffers();
		void freeAllHandles(Frame* _frame);
		void frameNoRenderWait();
		void swap();
		const char* getName(UniformHandle _handle) const;

		// render thread
		bool renderFrame();
		void flushTextureUpdateBatch(CommandBuffer& _cmdbuf);
		void rendererExecCommands(CommandBuffer& _cmdbuf);

#if BGFX_CONFIG_MULTITHREADED
		void gameSemPost()
		{
			if (!m_singleThreaded)
			{
				m_gameSem.post();
			}
		}

		void gameSemWait()
		{
			if (!m_singleThreaded)
			{
				BGFX_PROFILER_SCOPE(bgfx, main_thread_wait, 0xff2040ff);
				int64_t start = bx::getHPCounter();
				bool ok = m_gameSem.wait();
				BX_CHECK(ok, "Semaphore wait failed."); BX_UNUSED(ok);
				m_render->m_waitSubmit = bx::getHPCounter()-start;
			}
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
				BGFX_PROFILER_SCOPE(bgfx, render_thread_wait, 0xff2040ff);
				int64_t start = bx::getHPCounter();
				bool ok = m_renderSem.wait();
				BX_CHECK(ok, "Semaphore wait failed."); BX_UNUSED(ok);
				m_submit->m_waitRender = bx::getHPCounter() - start;
			}
		}

		bx::Semaphore m_renderSem;
		bx::Semaphore m_gameSem;
		bx::Thread m_thread;
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

		Frame m_frame[1+(BGFX_CONFIG_MULTITHREADED ? 1 : 0)];
		Frame* m_render;
		Frame* m_submit;

		uint64_t m_tempKeys[BGFX_CONFIG_MAX_DRAW_CALLS];
		RenderItemCount m_tempValues[BGFX_CONFIG_MAX_DRAW_CALLS];

		VertexBuffer m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];

		DynamicIndexBuffer  m_dynamicIndexBuffers[BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS];
		DynamicVertexBuffer m_dynamicVertexBuffers[BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS];

		uint16_t m_numFreeDynamicIndexBufferHandles;
		uint16_t m_numFreeDynamicVertexBufferHandles;
		DynamicIndexBufferHandle m_freeDynamicIndexBufferHandle[BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS];
		DynamicVertexBufferHandle m_freeDynamicVertexBufferHandle[BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS];

		NonLocalAllocator m_dynIndexBufferAllocator;
		bx::HandleAllocT<BGFX_CONFIG_MAX_DYNAMIC_INDEX_BUFFERS> m_dynamicIndexBufferHandle;
		NonLocalAllocator m_dynVertexBufferAllocator;
		bx::HandleAllocT<BGFX_CONFIG_MAX_DYNAMIC_VERTEX_BUFFERS> m_dynamicVertexBufferHandle;

		bx::HandleAllocT<BGFX_CONFIG_MAX_INDEX_BUFFERS> m_indexBufferHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_VERTEX_DECLS > m_vertexDeclHandle;

		bx::HandleAllocT<BGFX_CONFIG_MAX_VERTEX_BUFFERS> m_vertexBufferHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_SHADERS> m_shaderHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_PROGRAMS> m_programHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_TEXTURES> m_textureHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_FRAME_BUFFERS> m_frameBufferHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_UNIFORMS> m_uniformHandle;
		bx::HandleAllocT<BGFX_CONFIG_MAX_OCCUSION_QUERIES> m_occlusionQueryHandle;

		struct ShaderRef
		{
			UniformHandle* m_uniforms;
			uint32_t m_hash;
			int16_t  m_refCount;
			uint16_t m_num;
			bool     m_owned;
		};

		struct ProgramRef
		{
			ShaderHandle m_vsh;
			ShaderHandle m_fsh;
			int16_t m_refCount;
		};

		struct UniformRef
		{
			UniformType::Enum m_type;
			uint16_t m_num;
			int16_t m_refCount;
		};

		struct TextureRef
		{
			int16_t m_refCount;
			uint8_t m_bbRatio;
			uint8_t m_format;
			bool    m_owned;
		};

		struct FrameBufferRef
		{
			union un
			{
				TextureHandle m_th[BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS];
				void* m_nwh;
			} un;
			bool m_window;
		};

		typedef stl::unordered_set<uint16_t> HandleSet;
		HandleSet m_uniformSet;
		HandleSet m_occlusionQuerySet;

		typedef stl::unordered_map<stl::string, UniformHandle> UniformHashMap;
		UniformHashMap m_uniformHashMap;
		UniformRef m_uniformRef[BGFX_CONFIG_MAX_UNIFORMS];

		ShaderRef m_shaderRef[BGFX_CONFIG_MAX_SHADERS];

		typedef stl::unordered_map<uint32_t, ProgramHandle> ProgramHashMap;
		ProgramHashMap m_programHashMap;
		ProgramRef m_programRef[BGFX_CONFIG_MAX_PROGRAMS];

		TextureRef m_textureRef[BGFX_CONFIG_MAX_TEXTURES];
		FrameBufferRef m_frameBufferRef[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		VertexDeclRef m_declRef;

		uint8_t m_viewRemap[BGFX_CONFIG_MAX_VIEWS];
		FrameBufferHandle m_fb[BGFX_CONFIG_MAX_VIEWS];
		Clear m_clear[BGFX_CONFIG_MAX_VIEWS];

		float m_clearColor[BGFX_CONFIG_MAX_COLOR_PALETTE][4];
		Rect m_rect[BGFX_CONFIG_MAX_VIEWS];
		Rect m_scissor[BGFX_CONFIG_MAX_VIEWS];
		Matrix4 m_view[BGFX_CONFIG_MAX_VIEWS];
		Matrix4 m_proj[2][BGFX_CONFIG_MAX_VIEWS];
		uint8_t m_viewFlags[BGFX_CONFIG_MAX_VIEWS];
		uint16_t m_seq[BGFX_CONFIG_MAX_VIEWS];
		uint16_t m_seqMask[BGFX_CONFIG_MAX_VIEWS];

		uint8_t m_colorPaletteDirty;

		Resolution m_resolution;
		int32_t  m_instBufferCount;
		uint32_t m_frames;
		uint32_t m_debug;

		TextVideoMemBlitter m_textVideoMemBlitter;
		ClearQuad m_clearQuad;

		RendererContextI* m_renderCtx;

		bool m_rendererInitialized;
		bool m_exit;
		bool m_flipAfterRender;
		bool m_singleThreaded;

		typedef UpdateBatchT<256> TextureUpdateBatch;
		BX_ALIGN_DECL_CACHE_LINE(TextureUpdateBatch m_textureUpdateBatch);
	};

#undef BGFX_API_FUNC

} // namespace bgfx

#endif // BGFX_P_H_HEADER_GUARD
