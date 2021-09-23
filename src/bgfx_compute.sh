/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_COMPUTE_H_HEADER_GUARD
#define BGFX_COMPUTE_H_HEADER_GUARD

#include "bgfx_shader.sh"

#ifndef __cplusplus

#if BGFX_SHADER_LANGUAGE_HLSL > 0 && BGFX_SHADER_LANGUAGE_HLSL < 400
#	error "Compute is not supported!"
#endif // BGFX_SHADER_LANGUAGE_HLSL

#if BGFX_SHADER_LANGUAGE_METAL || BGFX_SHADER_LANGUAGE_SPIRV
#	define FORMAT(_format) [[spv::format_ ## _format]]
#	define WRITEONLY [[spv::nonreadable]]
#else
#	define FORMAT(_format)
#	define WRITEONLY
#endif // BGFX_SHADER_LANGUAGE_METAL || BGFX_SHADER_LANGUAGE_SPIRV

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

#define atomicFetchAndAdd(_mem, _data, _original)                    _original = atomicAdd(_mem, _data)
#define atomicFetchAndAnd(_mem, _data, _original)                    _original = atomicAnd(_mem, _data)
#define atomicFetchAndMax(_mem, _data, _original)                    _original = atomicMax(_mem, _data)
#define atomicFetchAndMin(_mem, _data, _original)                    _original = atomicMin(_mem, _data)
#define atomicFetchAndOr(_mem, _data, _original)                     _original = atomicOr(_mem, _data)
#define atomicFetchAndXor(_mem, _data, _original)                    _original = atomicXor(_mem, _data)
#define atomicFetchAndExchange(_mem, _data, _original)               _original = atomicExchange(_mem, _data)
#define atomicFetchCompareExchange(_mem, _compare, _data, _original) _original = atomicCompSwap(_mem,_compare, _data)

#else

#define SHARED groupshared

#define COMP_r32ui    uint
#define COMP_rg32ui   uint2
#define COMP_rgba32ui uint4
#define COMP_r32f     float
#define COMP_r16f     float
#define COMP_rg16f    float2
#define COMP_rgba16f  float4
#if BGFX_SHADER_LANGUAGE_HLSL
#	define COMP_rgba8 unorm float4
#	define COMP_rg8   unorm float2
#	define COMP_r8    unorm float
#else
#	define COMP_rgba8       float4
#	define COMP_rg8         float2
#	define COMP_r8          float
#endif // BGFX_SHADER_LANGUAGE_HLSL
#define COMP_rgba32f  float4

#define IMAGE2D_RO( _name, _format, _reg)                                       \
	FORMAT(_format) Texture2D<COMP_ ## _format> _name : REGISTER(t, _reg);      \

#define UIMAGE2D_RO(_name, _format, _reg) IMAGE2D_RO(_name, _format, _reg)

#define IMAGE2D_WR( _name, _format, _reg)                                                 \
	WRITEONLY FORMAT(_format) RWTexture2D<COMP_ ## _format> _name : REGISTER(u, _reg);  \
	
#define UIMAGE2D_WR(_name, _format, _reg) IMAGE2D_WR(_name, _format, _reg)

#define IMAGE2D_RW( _name, _format, _reg)                            \
	FORMAT(_format) RWTexture2D<COMP_ ## _format> _name : REGISTER(u, _reg);  \

#define UIMAGE2D_RW(_name, _format, _reg) IMAGE2D_RW(_name, _format, _reg)

#define IMAGE2D_ARRAY_RO(_name, _format, _reg)                                     \
	FORMAT(_format) Texture2DArray<COMP_ ## _format> _name : REGISTER(t, _reg);    \

#define UIMAGE2D_ARRAY_RO(_name, _format, _reg) IMAGE2D_ARRAY_RO(_name, _format, _reg)

#define IMAGE2D_ARRAY_WR( _name, _format, _reg)                                       \
	WRITEONLY FORMAT(_format) RWTexture2DArray<COMP_ ## _format> _name : REGISTER(u, _reg);    \

#define UIMAGE2D_ARRAY_WR(_name, _format, _reg) IMAGE2D_ARRAY_WR(_name, _format, _reg)

#define IMAGE2D_ARRAY_RW(_name, _format, _reg)                              \
	FORMAT(_format) RWTexture2DArray<COMP_ ## _format> _name : REGISTER(u, _reg);    \

#define UIMAGE2D_ARRAY_RW(_name, _format, _reg) IMAGE2D_ARRAY_RW(_name, _format, _reg)

#define IMAGE3D_RO( _name, _format, _reg)                                     \
	FORMAT(_format) Texture3D<COMP_ ## _format> _name : REGISTER(t, _reg);

#define UIMAGE3D_RO(_name, _format, _reg) IMAGE3D_RO(_name, _format, _reg)

#define IMAGE3D_WR( _name, _format, _reg)                                      \
	WRITEONLY FORMAT(_format) RWTexture3D<COMP_ ## _format> _name : REGISTER(u, _reg);

#define UIMAGE3D_WR(_name, _format, _reg) IMAGE3D_RW(_name, _format, _reg)

#define IMAGE3D_RW( _name, _format, _reg)                            \
	FORMAT(_format) RWTexture3D<COMP_ ## _format> _name : REGISTER(u, _reg);  \

#define UIMAGE3D_RW(_name, _format, _reg) IMAGE3D_RW(_name, _format, _reg)

#if BGFX_SHADER_LANGUAGE_METAL || BGFX_SHADER_LANGUAGE_SPIRV
#define BUFFER_RO(_name, _struct, _reg) StructuredBuffer<_struct>   _name : REGISTER(t, _reg)
#define BUFFER_RW(_name, _struct, _reg) RWStructuredBuffer <_struct> _name : REGISTER(u, _reg)
#define BUFFER_WR(_name, _struct, _reg) BUFFER_RW(_name, _struct, _reg)
#else
#define BUFFER_RO(_name, _struct, _reg) Buffer<_struct>   _name : REGISTER(t, _reg)
#define BUFFER_RW(_name, _struct, _reg) RWBuffer<_struct> _name : REGISTER(u, _reg)
#define BUFFER_WR(_name, _struct, _reg) BUFFER_RW(_name, _struct, _reg)
#endif

#define NUM_THREADS(_x, _y, _z) [numthreads(_x, _y, _z)]

#define __IMAGE_IMPL_A(_format, _storeComponents, _type, _loadComponents)       \
	_type imageLoad(Texture2D<_format> _image, ivec2 _uv)                       \
	{                                                                           \
		return _image[_uv]._loadComponents;                                     \
	}                                                                           \
	\
	ivec2 imageSize(Texture2D<_format> _image)                                  \
	{                                                                           \
		uvec2 result;                                                           \
		_image.GetDimensions(result.x, result.y);                               \
		return ivec2(result);                                                   \
	}                                                                           \
	\
	_type imageLoad(RWTexture2D<_format> _image, ivec2 _uv)                     \
	{                                                                           \
		return _image[_uv]._loadComponents;                                     \
	}                                                                           \
	\
	void imageStore(RWTexture2D<_format> _image, ivec2 _uv,  _type _value)      \
	{                                                                           \
		_image[_uv] = _value._storeComponents;                                  \
	}                                                                           \
	\
	ivec2 imageSize(RWTexture2D<_format> _image)                                \
	{                                                                           \
		uvec2 result;                                                           \
		_image.GetDimensions(result.x, result.y);                               \
		return ivec2(result);                                                   \
	}                                                                           \
	\
	_type imageLoad(Texture2DArray<_format> _image, ivec3 _uvw)                 \
	{                                                                           \
		return _image[_uvw]._loadComponents;                                    \
	}                                                                           \
	\
	ivec3 imageSize(Texture2DArray<_format> _image)                             \
	{                                                                           \
		uvec3 result;                                                           \
		_image.GetDimensions(result.x, result.y, result.z);                     \
		return ivec3(result);                                                   \
	}                                                                           \
	\
	_type imageLoad(RWTexture2DArray<_format> _image, ivec3 _uvw)               \
	{                                                                           \
		return _image[_uvw]._loadComponents;                                    \
	}                                                                           \
	\
	void imageStore(RWTexture2DArray<_format> _image, ivec3 _uvw, _type _value) \
	{                                                                           \
		_image[_uvw] = _value._storeComponents;                                 \
	}                                                                           \
	\
	ivec3 imageSize(RWTexture2DArray<_format> _image)                           \
	{                                                                           \
		uvec3 result;                                                           \
		_image.GetDimensions(result.x, result.y, result.z);                     \
		return ivec3(result);                                                   \
	}                                                                           \
	\
	_type imageLoad(Texture3D<_format> _image, ivec3 _uvw)                    \
	{                                                                           \
		return _image[_uvw]._loadComponents;                                    \
	}                                                                           \
	\
	ivec3 imageSize(Texture3D<_format> _image)                                \
	{                                                                           \
		uvec3 result;                                                           \
		_image.GetDimensions(result.x, result.y, result.z);                     \
		return ivec3(result);                                                   \
	}                                                                           \
	\
	_type imageLoad(RWTexture3D<_format> _image, ivec3 _uvw)                    \
	{                                                                           \
		return _image[_uvw]._loadComponents;                                    \
	}                                                                           \
	\
	void imageStore(RWTexture3D<_format> _image, ivec3 _uvw, _type _value)      \
	{                                                                           \
		_image[_uvw] = _value._storeComponents;                                 \
	}                                                                           \
	\
	ivec3 imageSize(RWTexture3D<_format> _image)                                \
	{                                                                           \
		uvec3 result;                                                           \
		_image.GetDimensions(result.x, result.y, result.z);                     \
		return ivec3(result);                                                   \
	}

#define __IMAGE_IMPL_ATOMIC(_format, _storeComponents, _type, _loadComponents)            \
	\
	void imageAtomicAdd(RWTexture2D<_format> _image, ivec2 _uv,  _type _value)       \
	{				                                                                 \
		InterlockedAdd(_image[_uv], _value._storeComponents);	                     \
	}                                                                                \


__IMAGE_IMPL_A(float,       x,    vec4,  xxxx)
__IMAGE_IMPL_A(float2,      xy,   vec4,  xyyy)
__IMAGE_IMPL_A(float4,      xyzw, vec4,  xyzw)

__IMAGE_IMPL_A(uint,        x,    uvec4, xxxx)
__IMAGE_IMPL_A(uint2,       xy,   uvec4, xyyy)
__IMAGE_IMPL_A(uint4,       xyzw, uvec4, xyzw)

#if BGFX_SHADER_LANGUAGE_HLSL
__IMAGE_IMPL_A(unorm float,       x,    vec4,  xxxx)
__IMAGE_IMPL_A(unorm float2,      xy,   vec4,  xyyy)
__IMAGE_IMPL_A(unorm float4,      xyzw, vec4,  xyzw)
#endif

__IMAGE_IMPL_ATOMIC(uint,       x,    uvec4, xxxx)


#define atomicAdd(_mem, _data)                                       InterlockedAdd(_mem, _data)
#define atomicAnd(_mem, _data)                                       InterlockedAnd(_mem, _data)
#define atomicMax(_mem, _data)                                       InterlockedMax(_mem, _data)
#define atomicMin(_mem, _data)                                       InterlockedMin(_mem, _data)
#define atomicOr(_mem, _data)                                        InterlockedOr(_mem, _data)
#define atomicXor(_mem, _data)                                       InterlockedXor(_mem, _data)
#define atomicFetchAndAdd(_mem, _data, _original)                    InterlockedAdd(_mem, _data, _original)
#define atomicFetchAndAnd(_mem, _data, _original)                    InterlockedAnd(_mem, _data, _original)
#define atomicFetchAndMax(_mem, _data, _original)                    InterlockedMax(_mem, _data, _original)
#define atomicFetchAndMin(_mem, _data, _original)                    InterlockedMin(_mem, _data, _original)
#define atomicFetchAndOr(_mem, _data, _original)                     InterlockedOr(_mem, _data, _original)
#define atomicFetchAndXor(_mem, _data, _original)                    InterlockedXor(_mem, _data, _original)
#define atomicFetchAndExchange(_mem, _data, _original)               InterlockedExchange(_mem, _data, _original)
#define atomicFetchCompareExchange(_mem, _compare, _data, _original) InterlockedCompareExchange(_mem,_compare, _data, _original)

// InterlockedCompareStore

#define barrier()                    GroupMemoryBarrierWithGroupSync()
#define memoryBarrier()              GroupMemoryBarrierWithGroupSync()
#define memoryBarrierAtomicCounter() GroupMemoryBarrierWithGroupSync()
#define memoryBarrierBuffer()        AllMemoryBarrierWithGroupSync()
#define memoryBarrierImage()         GroupMemoryBarrierWithGroupSync()
#define memoryBarrierShared()        GroupMemoryBarrierWithGroupSync()
#define groupMemoryBarrier()         GroupMemoryBarrierWithGroupSync()

#endif // BGFX_SHADER_LANGUAGE_GLSL

#define dispatchIndirect( \
	  _buffer             \
	, _offset             \
	, _numX               \
	, _numY               \
	, _numZ               \
	)                     \
	_buffer[(_offset)*2+0] = uvec4(_numX, _numY, _numZ, 0u)

#define drawIndirect( \
	  _buffer         \
	, _offset         \
	, _numVertices    \
	, _numInstances   \
	, _startVertex    \
	, _startInstance  \
	)                 \
	_buffer[(_offset)*2+0] = uvec4(_numVertices, _numInstances, _startVertex, _startInstance)

#define drawIndexedIndirect( \
	  _buffer                \
	, _offset                \
	, _numIndices            \
	, _numInstances          \
	, _startIndex            \
	, _startVertex           \
	, _startInstance         \
	)                        \
	_buffer[(_offset)*2+0] = uvec4(_numIndices, _numInstances, _startIndex, _startVertex); \
	_buffer[(_offset)*2+1] = uvec4(_startInstance, 0u, 0u, 0u)

#endif // __cplusplus

#endif // BGFX_COMPUTE_H_HEADER_GUARD
