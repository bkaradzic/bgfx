/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_COMPUTE_H_HEADER_GUARD
#define BGFX_COMPUTE_H_HEADER_GUARD

#include "bgfx_shader.sh"

#ifndef __cplusplus

#if BGFX_SHADER_LANGUAGE_HLSL

#define SHARED groupshared

#define r32ui   uint
#define r32f    float
#define rg16f   float2
#define rgba16f float4
#define rgba8   float4
#define rgba32f float4

#define IMAGE2D_RO( _name, _format, _reg) Texture2D<_format>   _name : register(t[_reg])
#define UIMAGE2D_RO(_name, _format, _reg) Texture2D<_format>   _name : register(t[_reg])
#define IMAGE2D_WR( _name, _format, _reg) RWTexture2D<_format> _name : register(u[_reg])
#define UIMAGE2D_WR(_name, _format, _reg) RWTexture2D<_format> _name : register(u[_reg])
#define IMAGE2D_RW( _name,          _reg) RWTexture2D<float>   _name : register(u[_reg])
#define UIMAGE2D_RW(_name,          _reg) RWTexture2D<uint>    _name : register(u[_reg])

#define IMAGE2D_ARRAY_RO( _name, _format, _reg) Texture2DArray<_format>   _name : register(t[_reg])
#define UIMAGE2D_ARRAY_RO(_name, _format, _reg) Texture2DArray<_format>   _name : register(t[_reg])
#define IMAGE2D_ARRAY_WR( _name, _format, _reg) RWTexture2DArray<_format> _name : register(u[_reg])
#define UIMAGE2D_ARRAY_WR(_name, _format, _reg) RWTexture2DArray<_format> _name : register(u[_reg])
#define IMAGE2D_ARRAY_RW( _name,          _reg) RWTexture2DArray<float>   _name : register(u[_reg])
#define UIMAGE2D_ARRAY_RW(_name,          _reg) RWTexture2DArray<uint>    _name : register(u[_reg])

#define IMAGE3D_RO( _name, _format, _reg) Texture3D<_format>   _name : register(t[_reg])
#define UIMAGE3D_RO(_name, _format, _reg) Texture3D<_format>   _name : register(t[_reg])
#define IMAGE3D_WR( _name, _format, _reg) RWTexture3D<_format> _name : register(u[_reg])
#define UIMAGE3D_WR(_name, _format, _reg) RWTexture3D<_format> _name : register(u[_reg])
#define IMAGE3D_RW( _name,          _reg) RWTexture3D<float>   _name : register(u[_reg])
#define UIMAGE3D_RW(_name,          _reg) RWTexture3D<uint>    _name : register(u[_reg])

#define BUFFER_RO(_name, _struct, _reg) Buffer<_struct>   _name : register(t[_reg])
#define BUFFER_RW(_name, _struct, _reg) RWBuffer<_struct> _name : register(u[_reg])
#define BUFFER_WR(_name, _struct, _reg) BUFFER_RW(_name, _struct, _reg)

#define NUM_THREADS(_x, _y, _z) [numthreads(_x, _y, _z)]

#define __IMAGE_IMPL(_textureType, _storeComponents, _type, _loadComponents)                                                     \
	_type imageLoad(       Texture2D<_textureType> _image, ivec2 _uv)                { return _image[_uv ]._loadComponents;    } \
	_type imageLoad(RWTexture2DArray<_textureType> _image, ivec3 _uvw)               { return _image[_uvw ]._loadComponents;   } \
	_type imageLoad(       Texture3D<_textureType> _image, ivec3 _uvw)               { return _image[_uvw]._loadComponents;    } \
	_type imageLoad(     RWTexture2D<_textureType> _image, ivec2 _uv)                { return _image[_uv ]._loadComponents;    } \
	_type imageLoad(RWTexture2DArray<_textureType> _image, ivec3 _uvw, _type _value) { return _image[_uvw]._loadComponents;    } \
	_type imageLoad(     RWTexture3D<_textureType> _image, ivec3 _uvw, _type _value) { return _image[_uvw]._loadComponents;    } \
	void imageStore(     RWTexture2D<_textureType> _image, ivec2 _uv,  _type _value) { _image[_uv ] = _value._storeComponents; } \
	void imageStore(RWTexture2DArray<_textureType> _image, ivec3 _uvw, _type _value) { _image[_uvw] = _value._storeComponents; } \
	void imageStore(     RWTexture3D<_textureType> _image, ivec3 _uvw, _type _value) { _image[_uvw] = _value._storeComponents; }

__IMAGE_IMPL(float, x,    vec4,  xxxx)
__IMAGE_IMPL(vec2,  xy,   vec4,  xyyy)
__IMAGE_IMPL(vec3,  xyz,  vec4,  xyzz)
__IMAGE_IMPL(vec4,  xyzw, vec4,  xyzw)
__IMAGE_IMPL(uint,  x,    uvec4, xxxx)
__IMAGE_IMPL(uvec2, xy,   uvec4, xyyy)
__IMAGE_IMPL(uvec3, xyz,  uvec4, xyzz)
__IMAGE_IMPL(uvec4, xyzw, uvec4, xyzw)
__IMAGE_IMPL(int,   x,    ivec4, xxxx)
__IMAGE_IMPL(ivec2, xy,   ivec4, xyyy)
__IMAGE_IMPL(ivec3, xyz,  ivec4, xyzz)
__IMAGE_IMPL(ivec4, xyzw, ivec4, xyzw)

ivec2 imageSize(Texture2D _image)
{
	ivec2 result;
	_image.GetDimensions(result.x, result.y);
	return result;
}

ivec2 imageSize(Texture2D<uint> _image)
{
	ivec2 result;
	_image.GetDimensions(result.x, result.y);
	return result;
}

ivec2 imageSize(RWTexture2D<float4> _image)
{
	ivec2 result;
	_image.GetDimensions(result.x, result.y);
	return result;
}

ivec2 imageSize(RWTexture2D<uint> _image)
{
	ivec2 result;
	_image.GetDimensions(result.x, result.y);
	return result;
}

#define __ATOMIC_IMPL_TYPE(_genType, _glFunc, _dxFunc)      \
			_genType _glFunc(_genType _mem, _genType _data) \
			{                                               \
				_genType result;                            \
				_dxFunc(_mem, _data, result);               \
				return result;                              \
			}

#define __ATOMIC_IMPL(_glFunc, _dxFunc)                \
			__ATOMIC_IMPL_TYPE(int,  _glFunc, _dxFunc) \
			__ATOMIC_IMPL_TYPE(uint, _glFunc, _dxFunc)

__ATOMIC_IMPL(atomicAdd,      InterlockedAdd);
__ATOMIC_IMPL(atomicAnd,      InterlockedAnd);
__ATOMIC_IMPL(atomicExchange, InterlockedExchange);
__ATOMIC_IMPL(atomicMax,      InterlockedMax);
__ATOMIC_IMPL(atomicMin,      InterlockedMin);
__ATOMIC_IMPL(atomicOr,       InterlockedOr);
__ATOMIC_IMPL(atomicXor,      InterlockedXor);

int atomicCompSwap(int _mem, int _compare, int _data)
{
	int result;
	InterlockedCompareExchange(_mem, _compare, _data, result);
	return result;
}

uint atomicCompSwap(uint _mem, uint _compare, uint _data)
{
	uint result;
	InterlockedCompareExchange(_mem, _compare, _data, result);
	return result;
}

// InterlockedCompareStore

#define barrier()                    GroupMemoryBarrierWithGroupSync()
#define memoryBarrier()              GroupMemoryBarrierWithGroupSync()
#define memoryBarrierAtomicCounter() GroupMemoryBarrierWithGroupSync()
#define memoryBarrierBuffer()        GroupMemoryBarrierWithGroupSync()
#define memoryBarrierImage()         GroupMemoryBarrierWithGroupSync()
#define memoryBarrierShared()        GroupMemoryBarrierWithGroupSync()
#define groupMemoryBarrier()         GroupMemoryBarrierWithGroupSync()

#else

#define SHARED shared

#define __IMAGE_XX(_name, _format, _reg, _image, _access) \
			layout(_format, binding=_reg) _access uniform highp _image _name

#define readwrite
#define IMAGE2D_RO( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2D,  readonly)
#define UIMAGE2D_RO(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2D, readonly)
#define IMAGE2D_WR( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2D,  writeonly)
#define UIMAGE2D_WR(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2D, writeonly)
#define IMAGE2D_RW( _name,          _reg) __IMAGE_XX(_name, r32f,    _reg, image2D,  readwrite)
#define UIMAGE2D_RW(_name,          _reg) __IMAGE_XX(_name, r32ui,   _reg, uimage2D, readwrite)

#define IMAGE2D_ARRAY_RO( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2DArray,  readonly)
#define UIMAGE2D_ARRAY_RO(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2DArray, readonly)
#define IMAGE2D_ARRAY_WR( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image2DArray,  writeonly)
#define UIMAGE2D_ARRAY_WR(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage2DArray, writeonly)
#define IMAGE2D_ARRAY_RW( _name,          _reg) __IMAGE_XX(_name, r32f,    _reg, image2DArray,  readwrite)
#define UIMAGE2D_ARRAY_RW(_name,          _reg) __IMAGE_XX(_name, r32ui,   _reg, uimage2DArray, readwrite)

#define IMAGE3D_RO( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image3D,  readonly)
#define UIMAGE3D_RO(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage3D, readonly)
#define IMAGE3D_WR( _name, _format, _reg) __IMAGE_XX(_name, _format, _reg, image3D,  writeonly)
#define UIMAGE3D_WR(_name, _format, _reg) __IMAGE_XX(_name, _format, _reg, uimage3D, writeonly)
#define IMAGE3D_RW( _name,          _reg) __IMAGE_XX(_name, r32f,    _reg, image3D,  readwrite)
#define UIMAGE3D_RW(_name,          _reg) __IMAGE_XX(_name, r32ui,   _reg, uimage3D, readwrite)

#define __BUFFER_XX(_name, _type, _reg, _access)                        \
			layout(std430, binding=_reg) _access buffer _name ## Buffer \
			{                                                           \
				_type _name[];                                          \
			}

#define BUFFER_RO(_name, _type, _reg) __BUFFER_XX(_name, _type, _reg, readonly)
#define BUFFER_RW(_name, _type, _reg) __BUFFER_XX(_name, _type, _reg, readwrite)
#define BUFFER_WR(_name, _type, _reg) __BUFFER_XX(_name, _type, _reg, writeonly)

#define NUM_THREADS(_x, _y, _z) layout (local_size_x = _x, local_size_y = _y, local_size_z = _z) in;

#endif // BGFX_SHADER_LANGUAGE_HLSL

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
