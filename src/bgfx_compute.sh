/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef BGFX_COMPUTE_H_HEADER_GUARD
#define BGFX_COMPUTE_H_HEADER_GUARD

#ifndef __cplusplus

#if BGFX_SHADER_LANGUAGE_HLSL

#define IMAGE2D_RO(_name, _reg) Texture2D           _name : register(t[_reg])
#define IMAGE2D_RW(_name, _reg) RWTexture2D<float4> _name : register(u[_reg])
#define IMAGE2D_WR(_name, _reg) IMAGE2D_RW(_name, _reg)

#define BUFFER_RO(_name, _struct, _reg) StructuredBuffer<_struct>   _name : register(b[_reg])
#define BUFFER_RW(_name, _struct, _reg) RWStructuredBuffer<_struct> _name : register(b[_reg])
#define BUFFER_WR(_name, _struct, _reg) BUFFER_RW(_name, _struct, _reg)

#define NUM_THREADS(_x, _y, _z) [numthreads(_x, _y, _z)]

vec4 imageLoad(Texture2D _image, ivec2 _uv)
{
	return _image.Load(uint3(_uv.xy, 0) );
}

ivec2 imageSize(Texture2D _image)
{
	ivec2 result;
	_image.GetDimensions(result.x, result.y);
	return result;
}

//vec4 imageLoad(RWTexture2D<float4> _image, ivec2 _uv)
//{
//	return _image[_uv];
//}

ivec2 imageSize(RWTexture2D<float4> _image)
{
	ivec2 result;
	_image.GetDimensions(result.x, result.y);
	return result;
}

void imageStore(RWTexture2D<float4> _image, ivec2 _uv, vec4 _rgba)
{
	_image[_uv] = _rgba;
}

#define __ATOMIC_IMPL_TYPE(_genType, _glFunc, _dxFunc) \
			_genType _glFunc(_genType _mem, _genType _data) \
			{ \
				_genType result; \
				_dxFunc(_mem, _data, result); \
				return result; \
			}

#define __ATOMIC_IMPL(_glFunc, _dxFunc) \
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

#define __IMAGE2D_XX(_name, _reg, _access) \
			layout(rgba8, binding=_reg) _access uniform highp image2D _name

#define IMAGE2D_RO(_name, _reg) __IMAGE2D_XX(_name, _reg, readonly)
#define IMAGE2D_RW(_name, _reg) __IMAGE2D_XX(_name, _reg, readwrite)
#define IMAGE2D_WR(_name, _reg) __IMAGE2D_XX(_name, _reg, writeonly)

#define __BUFFER_XX(_name, _type, _reg, _access) \
			layout(std430, binding=_reg) _access buffer _name ## Buffer \
			{ \
				_type _name[]; \
			}

#define BUFFER_RO(_name, _type, _reg) __BUFFER_XX(_name, _type, _reg, readonly)
#define BUFFER_RW(_name, _type, _reg) __BUFFER_XX(_name, _type, _reg, readwrite)
#define BUFFER_WR(_name, _type, _reg) __BUFFER_XX(_name, _type, _reg, writeonly)

#define NUM_THREADS(_x, _y, _z) layout (local_size_x = _x, local_size_y = _y, local_size_z = _z) in;

#endif // BGFX_SHADER_LANGUAGE_HLSL

#endif // __cplusplus

#endif // BGFX_COMPUTE_H_HEADER_GUARD
