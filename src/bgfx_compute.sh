/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_COMPUTE_H_HEADER_GUARD
#define BGFX_COMPUTE_H_HEADER_GUARD

#include "bgfx_shader.sh"

#ifndef __cplusplus

#if BGFX_SHADER_LANGUAGE_GLSL

#define SHARED shared

#define __IMAGE_XX(_name, _format, _reg, _image, _access) \
	layout(_format, binding=_reg) _access uniform highp _image _name

#define readwrite
#define IMAGE2D_RO( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2D,  readonly)
#define UIMAGE2D_RO(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2D, readonly)
#define IMAGE2D_WR( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2D,  writeonly)
#define UIMAGE2D_WR(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2D, writeonly)
#define IMAGE2D_RW( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2D,  readwrite)
#define UIMAGE2D_RW(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2D, readwrite)

#define IMAGE2D_ARRAY_RO( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2DArray,  readonly)
#define UIMAGE2D_ARRAY_RO(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2DArray, readonly)
#define IMAGE2D_ARRAY_WR( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2DArray,  writeonly)
#define UIMAGE2D_ARRAY_WR(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2DArray, writeonly)
#define IMAGE2D_ARRAY_RW( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2DArray,  readwrite)
#define UIMAGE2D_ARRAY_RW(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2DArray, readwrite)

#define IMAGE3D_RO( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image3D,  readonly)
#define UIMAGE3D_RO(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage3D, readonly)
#define IMAGE3D_WR( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image3D,  writeonly)
#define UIMAGE3D_WR(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage3D, writeonly)
#define IMAGE3D_RW( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image3D,  readwrite)
#define UIMAGE3D_RW(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage3D, readwrite)

#define __BUFFER_XX(_name, _type, _reg, _access)                \
	layout(std430, binding=_reg) _access buffer _name ## Buffer \
	{                                                           \
		_type _name[];                                          \
	}

#define BUFFER_RO(_name, _type, _reg) __BUFFER_XX(_name, _type, _reg, readonly)
#define BUFFER_RW(_name, _type, _reg) __BUFFER_XX(_name, _type, _reg, readwrite)
#define BUFFER_WR(_name, _type, _reg) __BUFFER_XX(_name, _type, _reg, writeonly)

#define NUM_THREADS(_x, _y, _z) layout (local_size_x = _x, local_size_y = _y, local_size_z = _z) in;

#define atomicFetchAndAdd(_mem, _data, _original)      _original = atomicAdd(_mem, _data)
#define atomicFetchAndAnd(_mem, _data, _original)      _original = atomicAnd(_mem, _data)
#define atomicFetchAndMax(_mem, _data, _original)      _original = atomicMax(_mem, _data)
#define atomicFetchAndMin(_mem, _data, _original)      _original = atomicMin(_mem, _data)
#define atomicFetchAndOr(_mem, _data, _original)       _original = atomicOrnterlockedOr(_mem, _data)
#define atomicFetchAndXor(_mem, _data, _original)      _original = atomicXor(_mem, _data)
#define atomicFetchAndExchange(_mem, _data, _original) _original = atomicExchange(_mem, _data)

#else

#define SHARED groupshared

#define r32ui    uint
#define rg32ui   uint2
#define rgba32ui uint4
#define r32f     float
#define rg16f    float2
#define rgba16f  float4
#if BGFX_SHADER_LANGUAGE_HLSL
#	define rgba8 unorm float4
#else
#	define rgba8       float4
#endif // BGFX_SHADER_LANGUAGE_HLSL
#define rgba32f  float4

#define IMAGE2D_RO( _name, _format, _reg)                         \
	Texture2D<_format> _name ## Texture : REGISTER(t, _reg);      \
	static BgfxROImage2D_ ## _format _name = { _name ## Texture }

#define UIMAGE2D_RO(_name, _format, _reg) IMAGE2D_RO(_name, _format, _reg)

#define IMAGE2D_RW( _name, _format, _reg)                       \
	RWTexture2D<_format> _name ## Texture : REGISTER(u, _reg);  \
	static BgfxRWImage2D_ ## _format _name = { _name ## Texture }

#define IMAGE2D_WR( _name, _format, _reg) IMAGE2D_RW(_name, _format, _reg)
#define UIMAGE2D_WR(_name, _format, _reg) IMAGE2D_RW(_name, _format, _reg)
#define UIMAGE2D_RW(_name, _format, _reg) IMAGE2D_RW(_name, _format, _reg)

#define IMAGE2D_ARRAY_RO(_name, _format, _reg)                       \
	Texture2DArray<_format> _name ## Texture : REGISTER(t, _reg);    \
	static BgfxROImage2DArray_ ## _format _name = { _name ## Texture }

#define UIMAGE2D_ARRAY_RO(_name, _format, _reg) IMAGE2D_ARRAY_RO(_name, _format, _reg)

#define IMAGE2D_ARRAY_RW(_name, _format, _reg)                         \
	RWTexture2DArray<_format> _name ## Texture : REGISTER(u, _reg);    \
	static BgfxRWImage2DArray_ ## _format _name = { _name ## Texture }

#define UIMAGE2D_ARRAY_RW(_name, _format, _reg) IMAGE2D_ARRAY_RW(_name, _format, _reg)
#define IMAGE2D_ARRAY_WR( _name, _format, _reg) IMAGE2D_ARRAY_RW(_name, _format, _reg)
#define UIMAGE2D_ARRAY_WR(_name, _format, _reg) IMAGE2D_ARRAY_RW(_name, _format, _reg)

#define IMAGE3D_RO( _name, _format, _reg)                       \
	Texture3D<_format> _name ## Texture : REGISTER(t, _reg);    \
	static BgfxROImage3D_ ## _format _name = { _name ## Texture }

#define UIMAGE3D_RO(_name, _format, _reg) IMAGE3D_RO(_name, _format, _reg)

#define IMAGE3D_RW( _name, _format, _reg)                       \
	RWTexture3D<_format> _name ## Texture : REGISTER(u, _reg);  \
	static BgfxRWImage3D_ ## _format _name = { _name ## Texture }

#define UIMAGE3D_RW(_name, _format, _reg) IMAGE3D_RW(_name, _format, _reg)
#define IMAGE3D_WR( _name, _format, _reg) IMAGE3D_RW(_name, _format, _reg)
#define UIMAGE3D_WR(_name, _format, _reg) IMAGE3D_RW(_name, _format, _reg)

#define BUFFER_RO(_name, _struct, _reg) Buffer<_struct>   _name : REGISTER(t, _reg)
#define BUFFER_RW(_name, _struct, _reg) RWBuffer<_struct> _name : REGISTER(u, _reg)
#define BUFFER_WR(_name, _struct, _reg) BUFFER_RW(_name, _struct, _reg)

#define NUM_THREADS(_x, _y, _z) [numthreads(_x, _y, _z)]

#define __IMAGE_IMPL_S(_format, _storeComponents, _type, _loadComponents) \
	\
	struct BgfxROImage2D_ ## _format                                      \
	{                                                                     \
		Texture2D<_format> m_texture;                                     \
	};                                                                    \
	\
	struct BgfxRWImage2D_ ## _format                                      \
	{                                                                     \
		RWTexture2D<_format> m_texture;                                   \
	};                                                                    \
	\
	struct BgfxROImage2DArray_ ## _format                                 \
	{                                                                     \
		Texture2DArray<_format> m_texture;                                \
	};                                                                    \
	\
	struct BgfxRWImage2DArray_ ## _format                                 \
	{                                                                     \
		RWTexture2DArray<_format> m_texture;                              \
	};                                                                    \
	\
	struct BgfxROImage3D_ ## _format                                      \
	{                                                                     \
		Texture3D<_format> m_texture;                                     \
	};                                                                    \
	\
	struct BgfxRWImage3D_ ## _format                                      \
	{                                                                     \
		RWTexture3D<_format> m_texture;                                   \
	};                                                                    \

#define __IMAGE_IMPL_A(_format, _storeComponents, _type, _loadComponents)            \
	__IMAGE_IMPL_S(_format, _storeComponents, _type, _loadComponents)                \
	\
	_type imageLoad(BgfxROImage2D_ ## _format _image, ivec2 _uv)                     \
	{                                                                                \
		return _image.m_texture[_uv]._loadComponents;                                \
	}                                                                                \
	\
	ivec2 imageSize(BgfxROImage2D_ ## _format _image)                                \
	{                                                                                \
		uvec2 result;                                                                \
		_image.m_texture.GetDimensions(result.x, result.y);                          \
		return ivec2(result);                                                        \
	}                                                                                \
	\
	_type imageLoad(BgfxRWImage2D_ ## _format _image, ivec2 _uv)                     \
	{                                                                                \
		return _image.m_texture[_uv]._loadComponents;                                \
	}                                                                                \
	\
	ivec2 imageSize(BgfxRWImage2D_ ## _format _image)                                \
	{                                                                                \
		uvec2 result;                                                                \
		_image.m_texture.GetDimensions(result.x, result.y);                          \
		return ivec2(result);                                                        \
	}                                                                                \
	\
	void imageStore(BgfxRWImage2D_ ## _format _image, ivec2 _uv,  _type _value)      \
	{                                                                                \
		_image.m_texture[_uv] = _value._storeComponents;                             \
	}                                                                                \
	\
	_type imageLoad(BgfxROImage2DArray_ ## _format _image, ivec3 _uvw)               \
	{                                                                                \
		return _image.m_texture[_uvw]._loadComponents;                               \
	}                                                                                \
	\
	ivec3 imageSize(BgfxROImage2DArray_ ## _format _image)                           \
	{                                                                                \
		uvec3 result;                                                                \
		_image.m_texture.GetDimensions(result.x, result.y, result.z);                \
		return ivec3(result);                                                        \
	}                                                                                \
	\
	_type imageLoad(BgfxRWImage2DArray_ ## _format _image, ivec3 _uvw)               \
	{                                                                                \
		return _image.m_texture[_uvw]._loadComponents;                               \
	}                                                                                \
	\
	void imageStore(BgfxRWImage2DArray_ ## _format _image, ivec3 _uvw, _type _value) \
	{                                                                                \
		_image.m_texture[_uvw] = _value._storeComponents;                            \
	}                                                                                \
	\
	ivec3 imageSize(BgfxRWImage2DArray_ ## _format _image)                           \
	{                                                                                \
		uvec3 result;                                                                \
		_image.m_texture.GetDimensions(result.x, result.y, result.z);                \
		return ivec3(result);                                                        \
	}                                                                                \
	\
	_type imageLoad(BgfxROImage3D_ ## _format _image, ivec3 _uvw)                    \
	{                                                                                \
		return _image.m_texture[_uvw]._loadComponents;                               \
	}                                                                                \
	\
	ivec3 imageSize(BgfxROImage3D_ ## _format _image)                                \
	{                                                                                \
		uvec3 result;                                                                \
		_image.m_texture.GetDimensions(result.x, result.y, result.z);                \
		return ivec3(result);                                                        \
	}                                                                                \
	\
	_type imageLoad(BgfxRWImage3D_ ## _format _image, ivec3 _uvw)                    \
	{                                                                                \
		return _image.m_texture[_uvw]._loadComponents;                               \
	}                                                                                \
	\
	ivec3 imageSize(BgfxRWImage3D_ ## _format _image)                                \
	{                                                                                \
		uvec3 result;                                                                \
		_image.m_texture.GetDimensions(result.x, result.y, result.z);                \
		return ivec3(result);                                                        \
	}                                                                                \
	\
	void imageStore(BgfxRWImage3D_ ## _format _image, ivec3 _uvw, _type _value)      \
	{                                                                                \
		_image.m_texture[_uvw] = _value._storeComponents;                            \
	}

__IMAGE_IMPL_A(rgba8,       xyzw, vec4,  xyzw)
__IMAGE_IMPL_A(rg16f,       xy,   vec4,  xyyy)
#if BGFX_SHADER_LANGUAGE_HLSL
__IMAGE_IMPL_S(rgba16f,     xyzw, vec4,  xyzw)
#else
__IMAGE_IMPL_A(rgba16f,     xyzw, vec4,  xyzw)
#endif // BGFX_SHADER_LANGUAGE_HLSL
__IMAGE_IMPL_A(r32f,        x,    vec4,  xxxx)
__IMAGE_IMPL_A(rgba32f,     xyzw, vec4,  xyzw)
__IMAGE_IMPL_A(r32ui,       x,    uvec4, xxxx)
__IMAGE_IMPL_A(rg32ui,      xy,   uvec4, xyyy)
__IMAGE_IMPL_A(rgba32ui,    xyzw, uvec4, xyzw)

#define atomicAdd(_mem, _data)                         InterlockedAdd(_mem, _data)
#define atomicAnd(_mem, _data)                         InterlockedAnd(_mem, _data)
#define atomicMax(_mem, _data)                         InterlockedMax(_mem, _data)
#define atomicMin(_mem, _data)                         InterlockedMin(_mem, _data)
#define atomicOr(_mem,  _data)                         InterlockedOr(_mem, _data)
#define atomicXor(_mem, _data)                         InterlockedXor(_mem, _data)
#define atomicFetchAndAdd(_mem, _data, _original)      InterlockedAdd(_mem, _data, _original)
#define atomicFetchAndAnd(_mem, _data, _original)      InterlockedAnd(_mem, _data, _original)
#define atomicFetchAndMax(_mem, _data, _original)      InterlockedMax(_mem, _data, _original)
#define atomicFetchAndMin(_mem, _data, _original)      InterlockedMin(_mem, _data, _original)
#define atomicFetchAndOr(_mem, _data, _original)       InterlockedOr(_mem, _data, _original)
#define atomicFetchAndXor(_mem, _data, _original)      InterlockedXor(_mem, _data, _original)
#define atomicFetchAndExchange(_mem, _data, _original) InterlockedExchange(_mem, _data, _original)
#define atomicCompSwap(_mem, _compare, _data)          InterlockedCompareExchange(_mem,_compare, _data)

// InterlockedCompareStore

#define barrier()                    GroupMemoryBarrierWithGroupSync()
#define memoryBarrier()              GroupMemoryBarrierWithGroupSync()
#define memoryBarrierAtomicCounter() GroupMemoryBarrierWithGroupSync()
#define memoryBarrierBuffer()        GroupMemoryBarrierWithGroupSync()
#define memoryBarrierImage()         GroupMemoryBarrierWithGroupSync()
#define memoryBarrierShared()        GroupMemoryBarrierWithGroupSync()
#define groupMemoryBarrier()         GroupMemoryBarrierWithGroupSync()

#endif // BGFX_SHADER_LANGUAGE_GLSL

#define dispatchIndirect(_buffer \
			, _offset            \
			, _numX              \
			, _numY              \
			, _numZ              \
			)                    \
			_buffer[_offset*2+0] = uvec4(_numX, _numY, _numZ, 0u)

#define drawIndirect(_buffer \
			, _offset        \
			, _numVertices   \
			, _numInstances  \
			, _startVertex   \
			, _startInstance \
			)                \
			_buffer[_offset*2+0] = uvec4(_numVertices, _numInstances, _startVertex, _startInstance)

#define drawIndexedIndirect(_buffer \
			, _offset               \
			, _numIndices           \
			, _numInstances         \
			, _startIndex           \
			, _startVertex          \
			, _startInstance        \
			)                       \
			_buffer[_offset*2+0] = uvec4(_numIndices, _numInstances, _startIndex, _startVertex); \
			_buffer[_offset*2+1] = uvec4(_startInstance, 0u, 0u, 0u)

#endif // __cplusplus

#endif // BGFX_COMPUTE_H_HEADER_GUARD
