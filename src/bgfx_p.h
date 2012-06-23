/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __BGFX_P_H__
#define __BGFX_P_H__

#include "bgfx.h"
#include <inttypes.h>
#include <stdarg.h> // va_list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void dbgPrintf(const char* _format, ...);
extern void dbgPrintfData(const void* _data, uint32_t _size, const char* _format, ...);

#ifndef BGFX_CONFIG_DEBUG
#	define BGFX_CONFIG_DEBUG 0
#endif // BGFX_CONFIG_DEBUG

#if BGFX_CONFIG_DEBUG
#	define BX_TRACE(_format, ...) \
				do { \
					dbgPrintf(BX_FILE_LINE_LITERAL "BGFX " _format "\n", ##__VA_ARGS__); \
				} while(0)

#	define BX_CHECK(_condition, _format, ...) \
				do { \
					if (!(_condition) ) \
					{ \
						BX_TRACE(BX_FILE_LINE_LITERAL "CHECK " _format, ##__VA_ARGS__); \
						bx::debugBreak(); \
					} \
				} while(0)
#endif // 0

#define BGFX_FATAL(_condition, _err, _format, ...) \
			do { \
				if (!(_condition) ) \
				{ \
					fatal(_err, _format, ##__VA_ARGS__); \
				} \
			} while(0)

#define BX_NAMESPACE 1
#include <bx/bx.h>
#include <bx/countof.h>
#include <bx/debug.h>
#include <bx/blockalloc.h>
#include <bx/handlealloc.h>
#include <bx/hash.h>
#include <bx/ringbuffer.h>
#include <bx/uint32_t.h>
#include <bx/radixsort.h>

#if BX_PLATFORM_WINDOWS
#	include <windows.h>
extern HWND g_bgfxHwnd;
#elif BX_PLATFORM_XBOX360
#	include <malloc.h>
#	include <xtl.h>
#endif // BX_PLATFORM_WINDOWS

#ifndef MAKEFOURCC
#	define MAKEFOURCC(_a, _b, _c, _d) (0 \
				| ( (uint32_t)(_a) \
				| ( (uint32_t)(_b) << 8) \
				| ( (uint32_t)(_c) << 16) \
				| ( (uint32_t)(_d) << 24) \
				) )
#endif // MAKEFOURCC

#include "dds.h"

#define BGFX_MAGIC MAKEFOURCC('B','G','F','X')

namespace std { namespace tr1 {} using namespace tr1; } // namespace std
#include <string>
#include <unordered_map>

#include "config.h"

#if BGFX_CONFIG_MULTITHREADED
#	include <bx/sem.h>
#endif // BGFX_CONFIG_MULTITHREADED

#include <bx/cpu.h>
#include <bx/timer.h>

#define BGFX_DRAW_WHOLE_INDEX_BUFFER 0xffffffff

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

#define BGFX_SAMPLER_TEXTURE            UINT16_C(0x0000)
#define BGFX_SAMPLER_RENDERTARGET_COLOR UINT16_C(0x0001)
#define BGFX_SAMPLER_RENDERTARGET_DEPTH UINT16_C(0x0002)
#define BGFX_SAMPLER_TYPE_MASK          UINT16_C(0x0003)

namespace bgfx
{
	extern const uint32_t g_constantTypeSize[ConstantType::Count];
	extern fatalFn g_fatal;
	extern reallocFn g_realloc;
	extern freeFn g_free;
	extern cacheFn g_cache;

	void fatal(bgfx::Fatal::Enum _code, const char* _format, ...);
	void release(Memory* _mem);
	void saveTga(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data);
	const char* getAttribName(Attrib::Enum _attr);
	bool renderFrame();

	inline uint32_t uint16_min(uint16_t _a, uint16_t _b)
	{
		return _a > _b ? _b : _a;
	}

	inline uint32_t hash(const void* _data, uint32_t _size)
	{
		HashMurmur2A murmur;
		murmur.begin();
		murmur.add(_data, (int)_size);
		return murmur.end();
	}

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

	BX_FORCE_INLINE uint32_t castfi(float _value)
	{
		union {	float fl; uint32_t ui; } un;
		un.fl = _value;
		return un.ui;
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
			g_free(m_mem);
		}

		void resize(bool _small = false, uint16_t _width = BGFX_DEFAULT_WIDTH, uint16_t _height = BGFX_DEFAULT_HEIGHT)
		{
			uint32_t width = uint32_max(1, _width/8);
			uint32_t height = uint32_max(1, _height/(_small ? 8 : 16) );

			if (NULL == m_mem
			||  m_width != width
			||  m_height != height
			||  m_small != _small)
			{
				m_small = _small;
				m_width = (uint16_t)width;
				m_height = (uint16_t)height;
				m_size = m_width * m_height * 2;

				m_mem = (uint8_t*)g_realloc(m_mem, m_size);
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

				uint32_t num = vsnprintf(temp, m_width, _format, _argList);

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

		void blit(const TextVideoMem* _mem)
		{
			blit(*_mem);
		}

		void blit(const TextVideoMem& _mem);
		void setup();
		void render(uint32_t _numIndices);

		bgfx::TextureHandle m_texture;
		TransientVertexBuffer* m_vb;
		TransientIndexBuffer* m_ib;
		bgfx::VertexDecl m_decl;
		bgfx::MaterialHandle m_material;
	};

	extern TextVideoMemBlitter g_textVideoMemBlitter;

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
			ModelViewProj,
			ModelViewProjX,
			AlphaRef,
			Count
		};

		uint8_t m_type;
		uint16_t m_loc;
		uint16_t m_count;
	};

	PredefinedUniform::Enum nameToPredefinedUniformEnum(const char* _name);

	class StreamRead
	{
	public:
		StreamRead(const void* _data, uint32_t _size)
			: m_data( (uint8_t*)_data)
			, m_size(_size)
			, m_pos(0)
		{
		}

		~StreamRead()
		{
		}

		void skip(uint32_t _size)
		{
			BX_CHECK(m_size-m_pos >= _size, "Available %d, requested %d.", m_size-m_pos, _size);
			m_pos += _size;
		}

		void read(void* _data, uint32_t _size)
		{
			BX_CHECK(m_size-m_pos >= _size, "Available %d, requested %d.", m_size-m_pos, _size);
			memcpy(_data, &m_data[m_pos], _size);
			m_pos += _size;
		}

		template<typename Ty>
		void read(Ty& _value)
		{
			read(&_value, sizeof(Ty) );
		}

		const uint8_t* getDataPtr() const
		{
			return &m_data[m_pos];
		}

		uint32_t getPos() const
		{
			return m_pos;
		}

		void align(uint16_t _align)
		{
			m_pos = strideAlign(m_pos, _align);
		}

		uint32_t remaining() const
		{
			return m_size-m_pos;
		}

	private:
		const uint8_t* m_data;
		uint32_t m_size;
		uint32_t m_pos;
	};

	class StreamWrite
	{
	public:
		StreamWrite(void* _data, uint32_t _size)
			: m_data( (uint8_t*)_data)
			, m_size(_size)
			, m_pos(0)
		{
		}

		~StreamWrite()
		{
		}

		void write(void* _data, uint32_t _size)
		{
			BX_CHECK(m_size-m_pos >= _size, "Write out of bounds. Available %d, requested %d.", m_size-m_pos, _size);
			memcpy(&m_data[m_pos], _data, _size);
			m_pos += _size;
		}

		template<typename Ty>
		void write(Ty& _value)
		{
			write(&_value, sizeof(Ty) );
		}

		uint8_t* getDataPtr() const
		{
			return &m_data[m_pos];
		}

		uint32_t getPos() const
		{
			return m_pos;
		}

		void align(uint16_t _align)
		{
			m_pos = strideAlign(m_pos, _align);
		}

	private:
		uint8_t* m_data;
		uint32_t m_size;
		uint32_t m_pos;
	};

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
			CreateVertexDecl,
			CreateIndexBuffer,
			CreateTransientIndexBuffer,
			CreateVertexBuffer,
			CreateTransientVertexBuffer,
			CreateVertexShader,
			CreateFragmentShader,
			CreateMaterial,
			CreateTexture,
			CreateRenderTarget,
			CreateUniform,
			End,
			RendererShutdown,
			DestroyVertexDecl,
			DestroyIndexBuffer,
			DestroyTransientIndexBuffer,
			DestroyVertexBuffer,
			DestroyTransientVertexBuffer,
			DestroyVertexShader,
			DestroyFragmentShader,
			DestroyMaterial,
			DestroyTexture,
			DestroyRenderTarget,
			DestroyUniform,
			SaveScreenShot,
		};

		void write(const void* _data, uint32_t _size)
		{
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

		void reset()
		{
			m_pos = 0;
		}

		void finish()
		{
			uint8_t cmd = End;
			write(cmd);
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
			uint64_t tmp1 = uint64_t(m_material)<<0x18;
			uint64_t tmp2 = uint64_t(m_trans)<<0x21;
			uint64_t tmp3 = uint64_t(m_seq)<<0x23;
			uint64_t tmp4 = uint64_t(m_view)<<0x2e;
			uint64_t key = tmp0|tmp1|tmp2|tmp3|tmp4;
			return key;
		}

		void decode(uint64_t _key)
		{
			m_depth = _key&0xffffffff;
			m_material = (_key>>0x18)&(BGFX_CONFIG_MAX_MATERIALS-1);
			m_trans = (_key>>0x21)&0x3;
			m_seq = (_key>>0x23)&0x7ff;
			m_view = (_key>>0x2e)&(BGFX_CONFIG_MAX_VIEWS-1);
		}

		void reset()
		{
			m_depth = 0;
			m_material = 0;
			m_seq = 0;
			m_view = 0;
			m_trans = 0;
		}

		int32_t m_depth;
		uint16_t m_material;
		uint16_t m_seq;
		uint8_t m_view;
		uint8_t m_trans;
	};

	struct Clear
	{
		uint32_t m_rgba;
		float m_depth;
		uint8_t m_stencil;
		uint8_t m_flags;
	};

	struct Rect
	{
		uint16_t m_x;
		uint16_t m_y;
		uint16_t m_width;
		uint16_t m_height;
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

	void matrix_mul(float* __restrict _result, const float* __restrict _a, const float* __restrict _b);
	void matrix_ortho(float* _result, float _left, float _right, float _bottom, float _top, float _near, float _far);

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

				uint32_t num = uint32_min(BGFX_CONFIG_MAX_MATRIX_CACHE-m_num, _num);
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

	struct Sampler
	{
		uint16_t m_idx;
		uint16_t m_flags;
	};
	
	struct Constant
	{
		ConstantType::Enum m_type;
		uint16_t m_num;
	};

#define CONSTANT_OPCODE_MASK(_bits) ( (1<<_bits)-1)

#define CONSTANT_OPCODE_TYPE_BITS 8
#define CONSTANT_OPCODE_TYPE_MASK CONSTANT_OPCODE_MASK(CONSTANT_OPCODE_TYPE_BITS)
#define CONSTANT_OPCODE_LOC_BITS 10
#define CONSTANT_OPCODE_LOC_MASK CONSTANT_OPCODE_MASK(CONSTANT_OPCODE_LOC_BITS)
#define CONSTANT_OPCODE_NUM_BITS 10
#define CONSTANT_OPCODE_NUM_MASK CONSTANT_OPCODE_MASK(CONSTANT_OPCODE_NUM_BITS)
#define CONSTANT_OPCODE_COPY_BITS 1
#define CONSTANT_OPCODE_COPY_MASK CONSTANT_OPCODE_MASK(CONSTANT_OPCODE_COPY_BITS)

#define BGFX_UNIFORM_FUNCTIONBIT UINT8_C(0x40)
#define BGFX_UNIFORM_FRAGMENTBIT UINT8_C(0x80)
#define BGFX_UNIFORM_TYPEMASK    UINT8_C(0x3f)

	class ConstantBuffer
	{
	public:
		static ConstantBuffer* create(uint32_t _size)
		{
			uint32_t size = BX_ALIGN_16(uint32_max(_size, sizeof(ConstantBuffer) ) );
			void* data = g_realloc(NULL, size);
			return ::new(data) ConstantBuffer(_size);
		}

		static void destroy(ConstantBuffer* _constantBuffer)
		{
			_constantBuffer->~ConstantBuffer();
			g_free(_constantBuffer);
		}

		static uint32_t encodeOpcode(ConstantType::Enum _type, uint16_t _loc, uint16_t _num, uint16_t _copy)
		{
			uint32_t opcode = 0;

			opcode <<= CONSTANT_OPCODE_TYPE_BITS;
			opcode |= _type&CONSTANT_OPCODE_TYPE_MASK;

			opcode <<= CONSTANT_OPCODE_LOC_BITS;
			opcode |= _loc&CONSTANT_OPCODE_LOC_MASK;

			opcode <<= CONSTANT_OPCODE_NUM_BITS;
			opcode |= _num&CONSTANT_OPCODE_NUM_MASK;

			opcode <<= CONSTANT_OPCODE_COPY_BITS;
			opcode |= _copy&CONSTANT_OPCODE_COPY_MASK;

			return opcode;
		}

		static void decodeOpcode(uint32_t _opcode, ConstantType::Enum& _type, uint16_t& _loc, uint16_t& _num, uint16_t& _copy)
		{
			uint32_t copy;
			uint32_t num;
			uint32_t loc;

			copy = _opcode&CONSTANT_OPCODE_COPY_MASK;
			_opcode >>= CONSTANT_OPCODE_COPY_BITS;

			num = _opcode&CONSTANT_OPCODE_NUM_MASK;
			_opcode >>= CONSTANT_OPCODE_NUM_BITS;

			loc = _opcode&CONSTANT_OPCODE_LOC_MASK;
			_opcode >>= CONSTANT_OPCODE_LOC_BITS;

			_type = (ConstantType::Enum)(_opcode&CONSTANT_OPCODE_TYPE_MASK);
			_opcode >>= CONSTANT_OPCODE_TYPE_BITS;

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
			write(ConstantType::End);
			m_pos = 0;
		}

		void writeUniform(ConstantType::Enum _type, uint16_t _loc, const void* _value, uint16_t _num = 1);
		void writeUniformRef(ConstantType::Enum _type, uint16_t _loc, const void* _value, uint16_t _num = 1);
		void commit(bool _force);

	private:
		ConstantBuffer(uint32_t _size)
			: m_size(_size-sizeof(m_buffer) )
			, m_pos(0)
		{
			BX_TRACE("ConstantBuffer %d, %d", _size, m_size);
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

		const UniformInfo& reg(const char* _name, const void* _data, UniformFn _func = NULL)
		{
			UniformHashMap::const_iterator it = m_uniforms.find(_name);
			if (it == m_uniforms.end() )
			{
				UniformInfo info;
				info.m_data = _data;
				info.m_func = _func;

				std::pair<UniformHashMap::iterator, bool> result = m_uniforms.insert(UniformHashMap::value_type(_name, info) );
				return result.first->second;	
			}

			return it->second;
		}

 	private:
 		typedef std::unordered_map<std::string, UniformInfo> UniformHashMap;
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
			m_matrix = 0;
			m_startIndex = BGFX_DRAW_WHOLE_INDEX_BUFFER;
			m_numIndices = 0;
			m_startVertex = 0;
			m_numVertices = UINT32_C(0xffffffff);
			m_num = 1;
			m_vertexBuffer.idx = bgfx::invalidHandle;
			m_vertexDecl.idx = bgfx::invalidHandle;
			m_indexBuffer.idx = bgfx::invalidHandle;
			
			for (uint32_t ii = 0; ii < BGFX_STATE_TEX_COUNT; ++ii)
			{
				m_sampler[ii].m_idx = bgfx::invalidHandle;
				m_sampler[ii].m_flags = BGFX_SAMPLER_TEXTURE;
			}
		}

		uint64_t m_flags;
		uint32_t m_constBegin;
		uint32_t m_constEnd;
		uint32_t m_matrix;
		uint32_t m_startIndex;
		uint32_t m_numIndices;
		uint32_t m_startVertex;
		uint32_t m_numVertices;
		uint16_t m_num;

		VertexBufferHandle m_vertexBuffer;
		VertexDeclHandle m_vertexDecl;
		IndexBufferHandle m_indexBuffer;
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
			m_textVideoMem = new TextVideoMem;
		}

		void destroy()
		{
			ConstantBuffer::destroy(m_constantBuffer);
			delete m_textVideoMem;
		}

		void reset()
		{
			m_state.reset();
			m_matrixCache.reset();
			m_key.reset();
			m_num = 0;
			m_numRenderStates = 0;
			m_numDropped = 0;
			m_iboffset = 0;
			m_vboffset = 0;
			m_cmdPre.reset();
			m_cmdPost.reset();
			m_constantBuffer->reset();
			m_discard = false;
			resetFreeHandles();
		}

		void finish()
		{
			m_cmdPre.finish();
			m_cmdPost.finish();
			m_constantBuffer->finish();

			if (0 < m_numDropped)
			{
				BX_TRACE("Too many draw calls: %d, dropped %d (max: %d)", m_num+m_numDropped, m_numDropped, BGFX_CONFIG_MAX_DRAW_CALLS);
			}
		}

		void setViewTransform(uint8_t _id, const void* _view, const void* _proj, uint8_t _other)
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
				m_view[_id].setIdentity();
			}
		}

		void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj, uint8_t _other)
		{
			for (uint32_t id = 0, viewMask = _viewMask, ntz = uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, id += 1, ntz = uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				id += ntz;

				setViewTransform(id, _view, _proj, _other);
			}
		}

		void setState(uint64_t _state)
		{
			uint8_t blend = ( (_state&BGFX_STATE_BLEND_MASK)>>BGFX_STATE_BLEND_SHIFT)&0xff;
			m_key.m_trans = "\x0\x1\x1\x2\x2\x1\x2\x1\x2\x1\x1\x1\x1\x1\x1\x1\x1"[( (blend)&0xf) + (!!blend)];
			m_state.m_flags = _state;
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

		void setIndexBuffer(const TransientIndexBuffer* _ib, uint32_t _numIndices)
		{
			m_state.m_indexBuffer = _ib->handle;
			m_state.m_startIndex = _ib->startIndex;
			m_state.m_numIndices = _numIndices;
			m_discard = 0 == _numIndices;
			g_free(const_cast<TransientIndexBuffer*>(_ib) );
		}

		void setVertexBuffer(VertexBufferHandle _handle)
		{
			BX_CHECK(_handle.idx < BGFX_CONFIG_MAX_VERTEX_BUFFERS, "Invalid vertex buffer handle. %d (< %d)", _handle.idx, BGFX_CONFIG_MAX_VERTEX_BUFFERS);
			m_state.m_startVertex = 0;
			m_state.m_numVertices = UINT32_C(0xffffffff);
			m_state.m_vertexBuffer = _handle;
		}

		void setVertexBuffer(const TransientVertexBuffer* _vb)
		{
			m_state.m_startVertex = _vb->startVertex;
			m_state.m_numVertices = _vb->size/_vb->stride;
			m_state.m_vertexBuffer = _vb->handle;
			m_state.m_vertexDecl = _vb->decl;
			g_free(const_cast<TransientVertexBuffer*>(_vb) );
		}

		void setMaterial(MaterialHandle _handle)
		{
			BX_CHECK(invalidHandle != _handle.idx, "Can't set material with invalid handle.");
			m_key.m_material = _handle.idx;
		}

		void setTexture(uint8_t _stage, UniformHandle _sampler, TextureHandle _handle)
		{
			m_flags |= BGFX_STATE_TEX0<<_stage;
			Sampler& sampler = m_state.m_sampler[_stage];
			sampler.m_idx = _handle.idx;
			sampler.m_flags = BGFX_SAMPLER_TEXTURE;

			if (bgfx::invalidHandle != _sampler.idx)
			{
				uint32_t stage = _stage;
				setUniform(_sampler, &stage);
			}
		}

		void setTexture(uint8_t _stage, UniformHandle _sampler, RenderTargetHandle _handle, bool _depth)
		{
			m_flags |= BGFX_STATE_TEX0<<_stage;
			Sampler& sampler = m_state.m_sampler[_stage];
			sampler.m_idx = _handle.idx;
			sampler.m_flags = _depth ? BGFX_SAMPLER_RENDERTARGET_DEPTH : BGFX_SAMPLER_RENDERTARGET_COLOR;

			if (bgfx::invalidHandle != _sampler.idx)
			{
				uint32_t stage = _stage;
				setUniform(_sampler, &stage);
			}
		}

		void submit(uint8_t _id);
		void submitMask(uint32_t _viewMask);
		void sort();

		bool checkAvailTransientIndexBuffer(uint16_t _num)
		{
			uint32_t offset = m_iboffset;
			uint32_t iboffset = offset + _num*sizeof(uint16_t);
			iboffset = uint32_min(iboffset, BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
			uint32_t num = (iboffset-offset)/sizeof(uint16_t);
			return num == _num;
		}

		uint32_t allocTransientIndexBuffer(uint16_t& _num)
		{
			uint32_t offset = m_iboffset;
			m_iboffset = offset + _num*sizeof(uint16_t);
			m_iboffset = uint32_min(m_iboffset, BGFX_CONFIG_TRANSIENT_INDEX_BUFFER_SIZE);
			_num = uint16_t( (m_iboffset-offset)/sizeof(uint16_t) );
			return offset;
		}

		bool checkAvailTransientVertexBuffer(uint16_t _num, uint16_t _stride)
		{
			uint32_t offset = strideAlign(m_vboffset, _stride);
			uint32_t vboffset = offset + _num * _stride;
			vboffset = uint32_min(vboffset, BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
			uint32_t num = (vboffset-offset)/_stride;
			return num == _num;
		}

		uint32_t allocTransientVertexBuffer(uint16_t& _num, uint16_t _stride)
		{
			uint32_t offset = strideAlign(m_vboffset, _stride);
			m_vboffset = offset + _num * _stride;
			m_vboffset = uint32_min(m_vboffset, BGFX_CONFIG_TRANSIENT_VERTEX_BUFFER_SIZE);
			_num = uint16_t( (m_vboffset-offset)/_stride);
			return offset;
		}

		void writeConstant(ConstantType::Enum _type, UniformHandle _handle, const void* _value, uint16_t _num)
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

		void free(MaterialHandle _handle)
		{
			m_freeMaterialHandle[m_numFreeMaterialHandles] = _handle;
			++m_numFreeMaterialHandles;
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
			m_numFreeMaterialHandles = 0;
			m_numFreeTextureHandles = 0;
			m_numFreeRenderTargetHandles = 0;
			m_numFreeUniformHandles = 0;
		}

		SortKey m_key;

		RenderTargetHandle m_rt[BGFX_CONFIG_MAX_VIEWS];
		Clear m_clear[BGFX_CONFIG_MAX_VIEWS];
		Rect m_rect[BGFX_CONFIG_MAX_VIEWS];
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
		uint16_t m_numFreeMaterialHandles;
		uint16_t m_numFreeTextureHandles;
		uint16_t m_numFreeRenderTargetHandles;
		uint16_t m_numFreeUniformHandles;

		IndexBufferHandle m_freeIndexBufferHandle[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexDeclHandle m_freeVertexDeclHandle[BGFX_CONFIG_MAX_VERTEX_DECLS];
		VertexBufferHandle m_freeVertexBufferHandle[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		VertexShaderHandle m_freeVertexShaderHandle[BGFX_CONFIG_MAX_VERTEX_SHADERS];
		FragmentShaderHandle m_freeFragmentShaderHandle[BGFX_CONFIG_MAX_FRAGMENT_SHADERS];
		MaterialHandle m_freeMaterialHandle[BGFX_CONFIG_MAX_MATERIALS];
		TextureHandle m_freeTextureHandle[BGFX_CONFIG_MAX_TEXTURES];
		RenderTargetHandle m_freeRenderTargetHandle[BGFX_CONFIG_MAX_RENDER_TARGETS];
		UniformHandle m_freeUniformHandle[BGFX_CONFIG_MAX_UNIFORMS];
		TextVideoMem* m_textVideoMem;

		int64_t m_waitSubmit;
		int64_t m_waitRender;

		bool m_discard;
	};

	struct MaterialRef
	{
		MaterialRef()
		{
		}

		MaterialHandle find(uint32_t _hash)
		{
			MaterialMap::const_iterator it = m_materialMap.find(_hash);
			if (it != m_materialMap.end() )
			{
				return it->second;
			}

			MaterialHandle result = BGFX_INVALID_HANDLE;
			return result;
		}

		void add(MaterialHandle _handle, uint32_t _hash)
		{
			m_materialMap.insert(std::make_pair(_hash, _handle) );
		}

		typedef std::unordered_map<uint32_t, MaterialHandle> MaterialMap;
		MaterialMap m_materialMap;
	};

	struct VertexDeclRef
	{
		VertexDeclRef()
		{
			memset(m_vertexDeclRef, 0, sizeof(m_vertexDeclRef) );
			memset(m_vertexBufferRef, 0xff, sizeof(m_vertexBufferRef) );
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
			m_vertexDeclMap.insert(std::make_pair(_hash, _declHandle) );
		}

		VertexDeclHandle release(VertexBufferHandle _handle)
		{
			VertexDeclHandle declHandle = m_vertexBufferRef[_handle.idx];
			m_vertexDeclRef[declHandle.idx]--;

			if (0 != m_vertexDeclRef[declHandle.idx])
			{
				VertexDeclHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			return declHandle;
		}

		typedef std::unordered_map<uint32_t, VertexDeclHandle> VertexDeclMap;
		VertexDeclMap m_vertexDeclMap;
		uint16_t m_vertexDeclRef[BGFX_CONFIG_MAX_VERTEX_DECLS];
		VertexDeclHandle m_vertexBufferRef[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
	};

#if BX_PLATFORM_WINDOWS || BX_PLATFORM_XBOX360
	DWORD WINAPI renderThread(LPVOID _arg);
#elif BX_PLATFORM_LINUX
	void* renderThread(void*);
#endif // BX_PLATFORM_

	struct Context
	{
		Context()
			: m_render(&m_frame[0])
			, m_submit(&m_frame[1])
			, m_indexBufferHandle(BGFX_CONFIG_MAX_INDEX_BUFFERS)
			, m_vertexDeclHandle(BGFX_CONFIG_MAX_VERTEX_DECLS)
			, m_vertexBufferHandle(BGFX_CONFIG_MAX_VERTEX_BUFFERS)
			, m_vertexShaderHandle(BGFX_CONFIG_MAX_VERTEX_SHADERS)
			, m_fragmentShaderHandle(BGFX_CONFIG_MAX_FRAGMENT_SHADERS)
			, m_materialHandle(BGFX_CONFIG_MAX_MATERIALS)
			, m_textureHandle(BGFX_CONFIG_MAX_TEXTURES)
			, m_renderTargetHandle(BGFX_CONFIG_MAX_RENDER_TARGETS)
			, m_uniformHandle(BGFX_CONFIG_MAX_UNIFORMS)
			, m_frames(0)
			, m_debug(BGFX_DEBUG_NONE)
			, m_rendererInitialized(false)
			, m_exit(false)
		{
		}

		~Context()
		{
		}

		// game thread
		void init(bool _createRenderThread);
		void shutdown();

		void frame()
		{
#if BX_PLATFORM_WINDOWS
			m_window.update();
#endif // BX_PLATFORM_WINDOWS

			// wait for render thread to finish
			renderSemWait();

			swap();

			// release render thread
			gameSemPost();

#if !BGFX_CONFIG_MULTITHREADED
			renderFrame();
#endif // BGFX_CONFIG_MULTITHREADED
		}

		CommandBuffer& getCommandBuffer(CommandBuffer::Enum _cmd)
		{
			CommandBuffer& cmdbuf = _cmd < CommandBuffer::End ? m_submit->m_cmdPre : m_submit->m_cmdPost;
			uint8_t cmd = (uint8_t)_cmd;
			cmdbuf.write(cmd);
			return cmdbuf;
		}

		void reset(uint32_t _width, uint32_t _height, uint32_t _flags)
		{
			m_resolution.m_width = _width;
			m_resolution.m_height = _height;
			m_resolution.m_flags = _flags&(~BGFX_RESET_FULLSCREEN_FAKE);

			memset(m_rt, 0xff, sizeof(m_rt) );

#if BX_PLATFORM_WINDOWS
			uint32_t fullscreen = (_flags&BGFX_RESET_FULLSCREEN_MASK)>>BGFX_RESET_FULLSCREEN_SHIFT;
			m_window.adjust(_width, _height, BGFX_RESET_FULLSCREEN_FAKE != fullscreen);
#endif // BX_PLATFORM_WINDOWS
		}

		void dbgTextClear(uint8_t _attr, bool _small)
		{
			m_submit->m_textVideoMem->resize(_small, m_resolution.m_width, m_resolution.m_height);
			m_submit->m_textVideoMem->clear(_attr);
		}

		void dbgTextPrintfVargs(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, va_list _argList)
		{
			m_submit->m_textVideoMem->printfVargs(_x, _y, _attr, _format, _argList);
		}

		IndexBufferHandle createIndexBuffer(const Memory* _mem)
		{
			IndexBufferHandle handle = { m_indexBufferHandle.alloc() };
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateIndexBuffer);
			cmdbuf.write(handle);
			cmdbuf.write(_mem);
			return handle;
		}

		void destroyIndexBuffer(IndexBufferHandle _handle)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyIndexBuffer);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		TransientIndexBuffer* createTransientIndexBuffer(uint32_t _size)
		{
			IndexBufferHandle handle = { m_indexBufferHandle.alloc() };
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateTransientIndexBuffer);
			cmdbuf.write(handle);
			cmdbuf.write(_size);

			TransientIndexBuffer* ib = (TransientIndexBuffer*)g_realloc(NULL, sizeof(TransientIndexBuffer)+_size);
			ib->data = (uint8_t*)&ib[1];
			ib->size = _size;
			ib->handle = handle;

			return ib;
		}

		void destroyTransientIndexBuffer(TransientIndexBuffer* _ib)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyTransientIndexBuffer);
			cmdbuf.write(_ib->handle);

			m_submit->free(_ib->handle);
			g_free(const_cast<TransientIndexBuffer*>(_ib) );
		}

		const TransientIndexBuffer* allocTransientIndexBuffer(uint16_t _num)
		{
			uint32_t offset = m_submit->allocTransientIndexBuffer(_num);

			TransientIndexBuffer& dib = *m_submit->m_transientIb;

			TransientIndexBuffer* ib = (TransientIndexBuffer*)g_realloc(NULL, sizeof(TransientIndexBuffer) );
			ib->data = &dib.data[offset];
			ib->size = _num * sizeof(uint16_t);
			ib->handle = dib.handle;
			ib->startIndex = offset/sizeof(uint16_t);

			return ib;
		}

		VertexDeclHandle findVertexDecl(const VertexDecl& _decl)
		{
			VertexDeclHandle declHandle = m_declRef.find(_decl.m_hash);

			if (bgfx::invalidHandle == declHandle.idx)
			{
				VertexDeclHandle temp = { m_vertexDeclHandle.alloc() };
				declHandle = temp;
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexDecl);
				cmdbuf.write(declHandle);
				cmdbuf.write(_decl);
			}

			return declHandle;
		}

		VertexBufferHandle createVertexBuffer(const Memory* _mem, const VertexDecl& _decl)
		{
			VertexBufferHandle handle = { m_vertexBufferHandle.alloc() };

			VertexDeclHandle declHandle = findVertexDecl(_decl);
			m_declRef.add(handle, declHandle, _decl.m_hash);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexBuffer);
			cmdbuf.write(handle);
			cmdbuf.write(_mem);
			cmdbuf.write(declHandle);
			return handle;
		}

		void destroyVertexBuffer(VertexBufferHandle _handle)
		{
			VertexDeclHandle declHandle = m_declRef.release(_handle);
			if (bgfx::invalidHandle != declHandle.idx)
			{
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexDecl);
				cmdbuf.write(declHandle);
			}

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexBuffer);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		TransientVertexBuffer* createTransientVertexBuffer(uint32_t _size, const VertexDecl* _decl = NULL)
		{
			VertexBufferHandle handle = { m_vertexBufferHandle.alloc() };

			uint16_t stride = 0;
			VertexDeclHandle declHandle = BGFX_INVALID_HANDLE;

			if (NULL != _decl)
			{
				declHandle = findVertexDecl(*_decl);
				m_declRef.add(handle, declHandle, _decl->m_hash);

				stride = _decl->m_stride;
			}

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateTransientVertexBuffer);
			cmdbuf.write(handle);
			cmdbuf.write(_size);

			TransientVertexBuffer* vb = (TransientVertexBuffer*)g_realloc(NULL, sizeof(TransientVertexBuffer)+_size);
			vb->data = (uint8_t*)&vb[1];
			vb->size = _size;
			vb->startVertex = 0;
			vb->stride = stride;
			vb->handle = handle;
			vb->decl = declHandle;

			return vb;
		}

		void destroyTransientVertexBuffer(TransientVertexBuffer* _vb)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyTransientVertexBuffer);
			cmdbuf.write(_vb->handle);

			m_submit->free(_vb->handle);
			g_free(const_cast<TransientVertexBuffer*>(_vb) );
		}

		const TransientVertexBuffer* allocTransientVertexBuffer(uint16_t _num, const VertexDecl& _decl)
		{
			VertexDeclHandle declHandle = m_declRef.find(_decl.m_hash);

			TransientVertexBuffer& dvb = *m_submit->m_transientVb;

			if (bgfx::invalidHandle == declHandle.idx)
			{
				VertexDeclHandle temp = { m_vertexDeclHandle.alloc() };
				declHandle = temp;
				CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexDecl);
				cmdbuf.write(declHandle);
				cmdbuf.write(_decl);
				m_declRef.add(dvb.handle, declHandle, _decl.m_hash);
			}

			uint32_t offset = m_submit->allocTransientVertexBuffer(_num, _decl.m_stride);

			TransientVertexBuffer* vb = (TransientVertexBuffer*)g_realloc(NULL, sizeof(TransientVertexBuffer) );
			vb->data = &dvb.data[offset];
			vb->size = _num * _decl.m_stride;
			vb->startVertex = offset/_decl.m_stride;
			vb->stride = _decl.m_stride;
			vb->handle = dvb.handle;
			vb->decl = declHandle;

			return vb;
		}

		VertexShaderHandle createVertexShader(const Memory* _mem)
		{
			VertexShaderHandle handle = { m_vertexShaderHandle.alloc() };
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateVertexShader);
			cmdbuf.write(handle);
			cmdbuf.write(_mem);
			return handle;
		}

		void destroyVertexShader(VertexShaderHandle _handle)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyVertexShader);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		FragmentShaderHandle createFragmentShader(const Memory* _mem)
		{
			FragmentShaderHandle handle = { m_fragmentShaderHandle.alloc() };
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateFragmentShader);
			cmdbuf.write(handle);
			cmdbuf.write(_mem);
			return handle;
		}

		void destroyFragmentShader(FragmentShaderHandle _handle)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyFragmentShader);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		MaterialHandle createMaterial(VertexShaderHandle _vsh, FragmentShaderHandle _fsh)
		{
			MaterialHandle handle;
// 			uint32_t hash = _vsh.idx<<16 | _fsh.idx;
// 
// 			MaterialHandle handle = m_materialRef.find(hash);
// 
// 			if (bgfx::invalidHandle != handle.idx)
// 			{
// 				return handle;
// 			}
// 
 			handle.idx = m_materialHandle.alloc();
// 			m_materialRef.add(handle, hash);

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateMaterial);
			cmdbuf.write(handle);
			cmdbuf.write(_vsh);
			cmdbuf.write(_fsh);
			return handle;
		}

		void destroyMaterial(MaterialHandle _handle)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyMaterial);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		TextureHandle createTexture(const Memory* _mem, uint32_t _flags, uint16_t* _width, uint16_t* _height)
		{
			if (NULL != _width
			||  NULL != _height)
			{
				int width = 0;
				int height = 0;

				Dds dds;
				if (parseDds(dds, _mem) )
				{
					width = dds.m_width;
					height = dds.m_height;
				}

				if (NULL != _width)
				{
					*_width = (uint16_t)width;
				}

				if (NULL != _height)
				{
					*_height = (uint16_t)height;
				}
			}

			TextureHandle handle = { m_textureHandle.alloc() };
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateTexture);
			cmdbuf.write(handle);
			cmdbuf.write(_mem);
			cmdbuf.write(_flags);
			return handle;
		}

		void destroyTexture(TextureHandle _handle)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyTexture);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		RenderTargetHandle createRenderTarget(uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags)
		{
			RenderTargetHandle handle = { m_renderTargetHandle.alloc() };

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateRenderTarget);
			cmdbuf.write(handle);
			cmdbuf.write(_width);
			cmdbuf.write(_height);
			cmdbuf.write(_flags);
			cmdbuf.write(_textureFlags);
			return handle;
		}

		void destroyRenderTarget(RenderTargetHandle _handle)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyRenderTarget);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		UniformHandle createUniform(const char* _name, ConstantType::Enum _type, uint16_t _num)
		{
			BX_CHECK(PredefinedUniform::Count == nameToPredefinedUniformEnum(_name), "%s is predefined uniform name.", _name);

			UniformHandle handle = { m_uniformHandle.alloc() };

			Constant& constant = m_constant[handle.idx];
			constant.m_type = _type;
			constant.m_num = _num;

			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::CreateUniform);
			cmdbuf.write(handle);
			cmdbuf.write(_type);
			cmdbuf.write(_num);
			uint8_t len = (uint8_t)strlen(_name);
			cmdbuf.write(len);
			cmdbuf.write(_name, len);
			return handle;
		}

		void destroyUniform(UniformHandle _handle)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::DestroyUniform);
			cmdbuf.write(_handle);
			m_submit->free(_handle);
		}

		void saveScreenShot(const Memory* _mem)
		{
			CommandBuffer& cmdbuf = getCommandBuffer(CommandBuffer::SaveScreenShot);
			cmdbuf.write(_mem);
		}

		void setUniform(UniformHandle _handle, const void* _value, uint16_t _num)
		{
			Constant& constant = m_constant[_handle.idx];
			BX_CHECK(constant.m_num >= _num, "Truncated uniform update. %d (max: %d)", _num, constant.m_num);
			m_submit->writeConstant(constant.m_type, _handle, _value, uint16_min(constant.m_num, _num) );
		}

		void setUniform(MaterialHandle _material, UniformHandle _handle, const void* _value)
		{
			BX_CHECK(false, "NOT IMPLEMENTED!");
		}

		void setViewRect(uint8_t _id, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
		{
			Rect& rect = m_rect[_id];
			rect.m_x = _x;
			rect.m_y = _y;
			rect.m_width = _width;
			rect.m_height = _height;
		}

		void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
		{
			for (uint32_t id = 0, viewMask = _viewMask, ntz = uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, id += 1, ntz = uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				id += ntz;

				setViewRect(id, _x, _y, _width, _height);
			}
		}

		void setViewClear(uint8_t _id, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
		{
			Clear& clear = m_clear[_id];
			clear.m_flags = _flags;
			clear.m_rgba = _rgba;
			clear.m_depth = _depth;
			clear.m_stencil = _stencil;
		}

		void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
		{
			for (uint32_t id = 0, viewMask = _viewMask, ntz = uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, id += 1, ntz = uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				id += ntz;

				setViewClear(id, _flags, _rgba, _depth, _stencil);
			}
		}

		void setViewSeq(uint8_t _id, bool _enabled)
		{
			m_seqMask[_id] = _enabled ? 0xffff : 0x0;
		}

		void setViewSeqMask(uint32_t _viewMask, bool _enabled)
		{
			uint16_t mask = _enabled ? 0xffff : 0x0;
			for (uint32_t id = 0, viewMask = _viewMask, ntz = uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, id += 1, ntz = uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				id += ntz;

				m_seqMask[id] = mask;
			}
		}

		void setViewRenderTarget(uint8_t _id, RenderTargetHandle _handle)
		{
			m_rt[_id] = _handle;
		}

		void setViewRenderTargetMask(uint32_t _viewMask, RenderTargetHandle _handle)
		{
			for (uint32_t id = 0, viewMask = _viewMask, ntz = uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, id += 1, ntz = uint32_cnttz(viewMask) )
			{
				viewMask >>= ntz;
				id += ntz;

				m_rt[id] = _handle;
			}
		}

		void dumpViewStats()
		{
#if 0 // BGFX_CONFIG_DEBUG
			for (uint8_t view = 0; view < BGFX_CONFIG_MAX_VIEWS; ++view)
			{
				if (0 < m_seq[view])
				{
					BX_TRACE("%d: %d", view, m_seq[view]);
				}
			}
#endif // BGFX_CONFIG_DEBUG
		}

		void freeAllHandles(Frame* _frame)
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
				m_vertexBufferHandle.free(_frame->m_freeVertexBufferHandle[ii].idx);
			}

			for (uint16_t ii = 0, num = _frame->m_numFreeVertexShaderHandles; ii < num; ++ii)
			{
				m_vertexShaderHandle.free(_frame->m_freeVertexShaderHandle[ii].idx);
			}

			for (uint16_t ii = 0, num = _frame->m_numFreeFragmentShaderHandles; ii < num; ++ii)
			{
				m_fragmentShaderHandle.free(_frame->m_freeFragmentShaderHandle[ii].idx);
			}

			for (uint16_t ii = 0, num = _frame->m_numFreeMaterialHandles; ii < num; ++ii)
			{
				m_materialHandle.free(_frame->m_freeMaterialHandle[ii].idx);
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

		void swap()
		{
			m_submit->m_resolution = m_resolution;
			m_submit->m_debug = m_debug;
			memcpy(m_submit->m_rt, m_rt, sizeof(m_rt) );
			memcpy(m_submit->m_clear, m_clear, sizeof(m_clear) );
			memcpy(m_submit->m_rect, m_rect, sizeof(m_rect) );
			m_submit->finish();

			dumpViewStats();

			freeAllHandles(m_render);

			memset(m_seq, 0, sizeof(m_seq) );
			Frame* temp = m_render;
			m_render = m_submit;
			m_submit = temp;
			m_frames++;
			m_submit->reset();

			m_submit->m_textVideoMem->resize(m_render->m_textVideoMem->m_small, m_resolution.m_width, m_resolution.m_height);
		}

		void flip();

		// render thread
		bool renderFrame()
		{
			flip();

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

		void rendererInit();
		void rendererShutdown();
		void rendererCreateIndexBuffer(IndexBufferHandle _handle, Memory* _mem);
		void rendererDestroyIndexBuffer(IndexBufferHandle _handle);
		void rendererCreateTransientIndexBuffer(IndexBufferHandle _handle, uint32_t _size);
		void rendererDestroyTransientIndexBuffer(IndexBufferHandle _handle);
		void rendererCreateVertexBuffer(VertexBufferHandle _handle, Memory* _mem, VertexDeclHandle _declHandle);
		void rendererDestroyVertexBuffer(VertexBufferHandle _handle);
		void rendererCreateTransientVertexBuffer(VertexBufferHandle _handle, uint32_t _size);
		void rendererDestroyTransientVertexBuffer(VertexBufferHandle _handle);
		void rendererCreateVertexDecl(VertexDeclHandle _handle, const VertexDecl& _decl);
		void rendererDestroyVertexDecl(VertexDeclHandle _handle);
		void rendererCreateVertexShader(VertexShaderHandle _handle, Memory* _mem);
		void rendererDestroyVertexShader(VertexShaderHandle _handle);
		void rendererCreateFragmentShader(FragmentShaderHandle _handle, Memory* _mem);
		void rendererDestroyFragmentShader(FragmentShaderHandle _handle);
		void rendererCreateMaterial(MaterialHandle _handle, VertexShaderHandle _vsh, FragmentShaderHandle _fsh);
		void rendererDestroyMaterial(FragmentShaderHandle _handle);
		void rendererCreateTexture(TextureHandle _handle, Memory* _mem, uint32_t _flags);
		void rendererDestroyTexture(TextureHandle _handle);
		void rendererCreateRenderTarget(RenderTargetHandle _handle, uint16_t _width, uint16_t _height, uint32_t _flags, uint32_t _textureFlags);
		void rendererDestroyRenderTarget(RenderTargetHandle _handle);
		void rendererCreateUniform(UniformHandle _handle, ConstantType::Enum _type, uint16_t _num, const char* _name);
		void rendererDestroyUniform(UniformHandle _handle);
		void rendererSaveScreenShot(Memory* _mem);
		void rendererUpdateUniform(uint16_t _loc, const void* _data, uint32_t _size);

		void rendererUpdateUniforms(ConstantBuffer* _constantBuffer, uint32_t _begin, uint32_t _end)
		{
			_constantBuffer->reset(_begin);
			while (_constantBuffer->getPos() < _end)
			{
				uint32_t opcode = _constantBuffer->read();

				if (ConstantType::End == opcode)
				{
					break;
				}

				ConstantType::Enum type;
				uint16_t loc;
				uint16_t num;
				uint16_t copy;
				ConstantBuffer::decodeOpcode(opcode, type, loc, num, copy);

				const char* data;
				uint32_t size = g_constantTypeSize[type]*num;
				data = _constantBuffer->read(size);
				rendererUpdateUniform(loc, data, size);
			}
		}
		
		void rendererExecCommands(CommandBuffer& _cmdbuf)
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
						rendererInit();
						m_rendererInitialized = true;
					}
					break;

				case CommandBuffer::RendererShutdown:
					{
						rendererShutdown();
						m_rendererInitialized = false;
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

				case CommandBuffer::CreateTransientIndexBuffer:
					{
						IndexBufferHandle handle;
						_cmdbuf.read(handle);

						uint32_t size;
						_cmdbuf.read(size);

						rendererCreateTransientIndexBuffer(handle, size);
					}
					break;

				case CommandBuffer::DestroyTransientIndexBuffer:
					{
						IndexBufferHandle handle;
						_cmdbuf.read(handle);

						rendererDestroyTransientIndexBuffer(handle);
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

				case CommandBuffer::CreateTransientVertexBuffer:
					{
						VertexBufferHandle handle;
						_cmdbuf.read(handle);

						uint32_t size;
						_cmdbuf.read(size);

						rendererCreateTransientVertexBuffer(handle, size);
					}
					break;

				case CommandBuffer::DestroyTransientVertexBuffer:
					{
						VertexBufferHandle handle;
						_cmdbuf.read(handle);

						rendererDestroyTransientVertexBuffer(handle);
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

				case CommandBuffer::CreateMaterial:
					{
						MaterialHandle handle;
						_cmdbuf.read(handle);

						VertexShaderHandle vsh;
						_cmdbuf.read(vsh);

						FragmentShaderHandle fsh;
						_cmdbuf.read(fsh);

						rendererCreateMaterial(handle, vsh, fsh);
					}
					break;

				case CommandBuffer::DestroyMaterial:
					{
						FragmentShaderHandle handle;
						_cmdbuf.read(handle);

						rendererDestroyMaterial(handle);
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

						release(mem);
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

						ConstantType::Enum type;
						_cmdbuf.read(type);

						uint16_t num;
						_cmdbuf.read(num);

						uint8_t len;
						_cmdbuf.read(len);

						char name[256];
						_cmdbuf.read(name, len);
						name[len] = '\0';

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
						Memory* mem;
						_cmdbuf.read(mem);

						rendererSaveScreenShot(mem);

						release(mem);
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
		}

		void rendererSubmit();

#if BGFX_CONFIG_MULTITHREADED
		void gameSemPost()
		{
// 			BX_TRACE("game post");
			m_gameSem.post();
		}

		void gameSemWait()
		{
// 			BX_TRACE("game wait");
			int64_t start = bx::getHPCounter();
			m_gameSem.wait();
			m_render->m_waitSubmit = bx::getHPCounter()-start;
		}

		void renderSemPost()
		{
// 			BX_TRACE("render post");
			m_renderSem.post();
		}

		void renderSemWait()
		{
// 			BX_TRACE("render wait");
			int64_t start = bx::getHPCounter();
			m_renderSem.wait();
			m_submit->m_waitRender = bx::getHPCounter() - start;
		}

		Semaphore m_renderSem;
		Semaphore m_gameSem;

#	if BX_PLATFORM_WINDOWS|BX_PLATFORM_XBOX360
		HANDLE m_renderThread;
#	else
		pthread_t m_renderThread;
#	endif // BX_PLATFORM_WINDOWS|BX_PLATFORM_XBOX360

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

		Frame m_frame[2];
		Frame* m_render;
		Frame* m_submit;

		uint64_t m_tempKeys[BGFX_CONFIG_MAX_DRAW_CALLS];
		uint16_t m_tempValues[BGFX_CONFIG_MAX_DRAW_CALLS];

		HandleAlloc m_indexBufferHandle;
		HandleAlloc m_vertexDeclHandle;
		HandleAlloc m_vertexBufferHandle;
		HandleAlloc m_vertexShaderHandle;
		HandleAlloc m_fragmentShaderHandle;
		HandleAlloc m_materialHandle;
		HandleAlloc m_textureHandle;
		HandleAlloc m_renderTargetHandle;
		HandleAlloc m_uniformHandle;

		MaterialRef m_materialRef;
		VertexDeclRef m_declRef;

		RenderTargetHandle m_rt[BGFX_CONFIG_MAX_VIEWS];
		Clear m_clear[BGFX_CONFIG_MAX_VIEWS];
		Rect m_rect[BGFX_CONFIG_MAX_VIEWS];
		Constant m_constant[BGFX_CONFIG_MAX_UNIFORMS];
		uint16_t m_seq[BGFX_CONFIG_MAX_VIEWS];
		uint16_t m_seqMask[BGFX_CONFIG_MAX_VIEWS];

		Resolution m_resolution;
		uint32_t m_frames;
		uint32_t m_debug;

#if BX_PLATFORM_WINDOWS
		struct Window
		{
			Window()
				: m_frame(true)
				, m_update(false)
			{
			}

			void init()
			{
				if (NULL == g_bgfxHwnd)
				{					
					HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);

					WNDCLASSEX wnd;
					memset(&wnd, 0, sizeof(wnd) );
					wnd.cbSize = sizeof(wnd);
					wnd.lpfnWndProc = DefWindowProc;
					wnd.hInstance = instance;
					wnd.hIcon = LoadIcon(instance, IDI_APPLICATION);
					wnd.hCursor = LoadCursor(instance, IDC_ARROW);
					wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
					wnd.lpszClassName = "bgfx_letterbox";
					wnd.hIconSm = LoadIcon(instance, IDI_APPLICATION);
					RegisterClassExA(&wnd);

					memset(&wnd, 0, sizeof(wnd) );
					wnd.cbSize = sizeof(wnd);
					wnd.style = CS_HREDRAW | CS_VREDRAW;
					wnd.lpfnWndProc = wndProc;
					wnd.hInstance = instance;
					wnd.hIcon = LoadIcon(instance, IDI_APPLICATION);
					wnd.hCursor = LoadCursor(instance, IDC_ARROW);
					wnd.lpszClassName = "bgfx";
					wnd.hIconSm = LoadIcon(instance, IDI_APPLICATION);
					RegisterClassExA(&wnd);

					HWND hwnd = CreateWindowA("bgfx_letterbox"
						, "BGFX"
						, WS_POPUP|WS_SYSMENU
						, -32000
						, -32000
						, 0
						, 0
						, NULL
						, NULL
						, instance
						, 0
						);

					g_bgfxHwnd = CreateWindowA("bgfx"
						, "BGFX"
						, WS_OVERLAPPEDWINDOW|WS_VISIBLE
						, 0
						, 0
						, BGFX_DEFAULT_WIDTH
						, BGFX_DEFAULT_HEIGHT
						, hwnd
						, NULL
						, instance
						, 0
						);

					m_update = true;
				}
			}

			LRESULT process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
			{
				switch (_id)
				{
				case WM_CLOSE:
					TerminateProcess(GetCurrentProcess(), 0);
					break;

				case WM_SIZING:
					{
						RECT clientRect;
						GetClientRect(_hwnd, &clientRect);
						uint32_t width = clientRect.right-clientRect.left;
						uint32_t height = clientRect.bottom-clientRect.top;

						RECT& rect = *(RECT*)_lparam;
						uint32_t frameWidth = rect.right-rect.left - width;
						uint32_t frameHeight = rect.bottom-rect.top - height;

						switch (_wparam)
						{
						case WMSZ_LEFT:
						case WMSZ_RIGHT:
							{
								float aspectRatio = 1.0f/m_aspectRatio;
								width = bx::uint32_max(BGFX_DEFAULT_WIDTH/4, width);
								height = uint32_t(float(width)*aspectRatio);
							}
							break;

						default:
							{
								float aspectRatio = m_aspectRatio;
								height = bx::uint32_max(BGFX_DEFAULT_HEIGHT/4, height);
								width = uint32_t(float(height)*aspectRatio);
							}
							break;
						}

						rect.right = rect.left + width + frameWidth;
						rect.bottom = rect.top + height + frameHeight;

						SetWindowPos(_hwnd
							, HWND_TOP
							, rect.left
							, rect.top
							, (rect.right-rect.left)
							, (rect.bottom-rect.top)
							, SWP_SHOWWINDOW
							);
					}
					return 0;

				case WM_SYSCOMMAND:
					switch (_wparam)
					{
					case SC_MINIMIZE:
					case SC_RESTORE:
						{
							HWND parent = GetWindow(_hwnd, GW_OWNER);
							if (NULL != parent)
							{
								PostMessage(parent, _id, _wparam, _lparam);
							}
						}
					}
					break;

				default:
					break;
				}

				return DefWindowProc(_hwnd, _id, _wparam, _lparam);
			}

			void update()
			{
				if (m_update)
				{
					MSG msg;
					msg.message = WM_NULL;
					if (0 != PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
			}

			void adjust(uint32_t _width, uint32_t _height, bool _windowFrame)
			{
				m_aspectRatio = float(_width)/float(_height);

				ShowWindow(g_bgfxHwnd, SW_SHOWNORMAL);
				RECT rect;
				RECT newrect = {0, 0, (LONG)_width, (LONG)_height};
				DWORD style = WS_POPUP|WS_SYSMENU;

				if (m_frame)
				{
					GetWindowRect(g_bgfxHwnd, &m_rect);
					m_style = GetWindowLong(g_bgfxHwnd, GWL_STYLE);
				}

				if (_windowFrame)
				{
					rect = m_rect;
					style = m_style;
				}
				else
				{
#if defined(__MINGW32__)
					rect = m_rect;
					style = m_style;
#else
					HMONITOR monitor = MonitorFromWindow(g_bgfxHwnd, MONITOR_DEFAULTTONEAREST);
					MONITORINFO mi;
					mi.cbSize = sizeof(mi);
					GetMonitorInfo(monitor, &mi);
					newrect = mi.rcMonitor;
					rect = mi.rcMonitor;
#endif // !defined(__MINGW__)
				}

				SetWindowLong(g_bgfxHwnd, GWL_STYLE, style);
				AdjustWindowRect(&newrect, style, FALSE);
				UpdateWindow(g_bgfxHwnd);

				if (rect.left == -32000
				||  rect.top == -32000)
				{
					rect.left = 0;
					rect.top = 0;
				}

				int32_t left = rect.left;
				int32_t top = rect.top;
				int32_t width = (newrect.right-newrect.left);
				int32_t height = (newrect.bottom-newrect.top);

				if (!_windowFrame)
				{
					float aspectRatio = 1.0f/m_aspectRatio;
					width = bx::uint32_max(BGFX_DEFAULT_WIDTH/4, width);
					height = uint32_t(float(width)*aspectRatio);

					left = newrect.left+(newrect.right-newrect.left-width)/2;
					top = newrect.top+(newrect.bottom-newrect.top-height)/2;
				}

				HWND parent = GetWindow(g_bgfxHwnd, GW_OWNER);
				if (NULL != parent)
				{
					if (_windowFrame)
					{
						SetWindowPos(parent
							, HWND_TOP
							, -32000
							, -32000
							, 0
							, 0
							, SWP_SHOWWINDOW
							);
					}
					else
					{
						SetWindowPos(parent
							, HWND_TOP
							, newrect.left
							, newrect.top
							, newrect.right-newrect.left
							, newrect.bottom-newrect.top
							, SWP_SHOWWINDOW
							);
					}
				}

				SetWindowPos(g_bgfxHwnd
					, HWND_TOP
					, left
					, top
					, width
					, height
					, SWP_SHOWWINDOW
					);

				ShowWindow(g_bgfxHwnd, SW_RESTORE);

				m_frame = _windowFrame;
			}

		private:
			static LRESULT CALLBACK wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);

			RECT m_rect;
			DWORD m_style;
			float m_aspectRatio;
			bool m_frame;
			bool m_update;
		};

		Window m_window;
#endif // BX_PLATFORM_WINDOWS

		bool m_rendererInitialized;
		bool m_exit;
	};

} // namespace bgfx

#endif // __BGFX_P_H__
