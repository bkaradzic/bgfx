/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_SHADER_H_HEADER_GUARD
#define BGFX_SHADER_H_HEADER_GUARD

#if !defined(BGFX_CONFIG_MAX_BONES)
#	define BGFX_CONFIG_MAX_BONES 32
#endif // !defined(BGFX_CONFIG_MAX_BONES)

#ifndef __cplusplus

#if BGFX_SHADER_LANGUAGE_HLSL > 3
#	define BRANCH [branch]
#	define LOOP   [loop]
#	define UNROLL [unroll]
#else
#	define BRANCH
#	define LOOP
#	define UNROLL
#endif // BGFX_SHADER_LANGUAGE_HLSL > 3

#if BGFX_SHADER_LANGUAGE_HLSL > 3 && BGFX_SHADER_TYPE_FRAGMENT
#	define EARLY_DEPTH_STENCIL [earlydepthstencil]
#else
#	define EARLY_DEPTH_STENCIL
#endif // BGFX_SHADER_LANGUAGE_HLSL > 3 && BGFX_SHADER_TYPE_FRAGMENT

#if BGFX_SHADER_LANGUAGE_GLSL
#   define ARRAY_BEGIN(_type, _name, _count) _type _name[_count] = _type[](
#   define ARRAY_END() )
#else
#   define ARRAY_BEGIN(_type, _name, _count) _type _name[_count] = {
#   define ARRAY_END() }
#endif // BGFX_SHADER_LANGUAGE_GLSL

#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_SPIRV
#	define CONST(_x) static const _x
#	define dFdx(_x) ddx(_x)
#	define dFdy(_y) ddy(-_y)
#	define inversesqrt(_x) rsqrt(_x)
#	define fract(_x) frac(_x)

#	define bvec2 bool2
#	define bvec3 bool3
#	define bvec4 bool4

#	if BGFX_SHADER_LANGUAGE_HLSL > 4
#		define REGISTER(_type, _reg) register(_type[_reg])
#	else
#		define REGISTER(_type, _reg) register(_type ## _reg)
#	endif // BGFX_SHADER_LANGUAGE_HLSL

#	if BGFX_SHADER_LANGUAGE_HLSL > 3 || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_SPIRV
#		if BGFX_SHADER_LANGUAGE_HLSL > 4 || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_SPIRV
#			define dFdxCoarse(_x) ddx_coarse(_x)
#			define dFdxFine(_x)   ddx_fine(_x)
#			define dFdyCoarse(_y) ddy_coarse(-_y)
#			define dFdyFine(_y)   ddy_fine(-_y)
#		endif // BGFX_SHADER_LANGUAGE_HLSL > 4

#		if BGFX_SHADER_LANGUAGE_HLSL
float intBitsToFloat(int   _x) { return asfloat(_x); }
vec2  intBitsToFloat(uint2 _x) { return asfloat(_x); }
vec3  intBitsToFloat(uint3 _x) { return asfloat(_x); }
vec4  intBitsToFloat(uint4 _x) { return asfloat(_x); }
#		endif // BGFX_SHADER_LANGUAGE_HLSL

float uintBitsToFloat(uint  _x) { return asfloat(_x); }
vec2  uintBitsToFloat(uint2 _x) { return asfloat(_x); }
vec3  uintBitsToFloat(uint3 _x) { return asfloat(_x); }
vec4  uintBitsToFloat(uint4 _x) { return asfloat(_x); }

uint  floatBitsToUint(float _x) { return asuint(_x); }
uvec2 floatBitsToUint(vec2  _x) { return asuint(_x); }
uvec3 floatBitsToUint(vec3  _x) { return asuint(_x); }
uvec4 floatBitsToUint(vec4  _x) { return asuint(_x); }

int   floatBitsToInt(float _x) { return asint(_x); }
ivec2 floatBitsToInt(vec2  _x) { return asint(_x); }
ivec3 floatBitsToInt(vec3  _x) { return asint(_x); }
ivec4 floatBitsToInt(vec4  _x) { return asint(_x); }

uint  bitfieldReverse(uint  _x) { return reversebits(_x); }
uint2 bitfieldReverse(uint2 _x) { return reversebits(_x); }
uint3 bitfieldReverse(uint3 _x) { return reversebits(_x); }
uint4 bitfieldReverse(uint4 _x) { return reversebits(_x); }

#		if !BGFX_SHADER_LANGUAGE_SPIRV
uint packHalf2x16(vec2 _x)
{
	return (f32tof16(_x.y)<<16) | f32tof16(_x.x);
}

vec2 unpackHalf2x16(uint _x)
{
	return vec2(f16tof32(_x & 0xffff), f16tof32(_x >> 16) );
}
#		endif // !BGFX_SHADER_LANGUAGE_SPIRV

struct BgfxSampler2D
{
	SamplerState m_sampler;
	Texture2D m_texture;
};

struct BgfxISampler2D
{
	Texture2D<ivec4> m_texture;
};

struct BgfxUSampler2D
{
	Texture2D<uvec4> m_texture;
};

struct BgfxSampler2DArray
{
	SamplerState m_sampler;
	Texture2DArray m_texture;
};

struct BgfxSampler2DShadow
{
	SamplerComparisonState m_sampler;
	Texture2D m_texture;
};

struct BgfxSampler3D
{
	SamplerState m_sampler;
	Texture3D m_texture;
};

struct BgfxISampler3D
{
	Texture3D<ivec4> m_texture;
};

struct BgfxUSampler3D
{
	Texture3D<uvec4> m_texture;
};

struct BgfxSamplerCube
{
	SamplerState m_sampler;
	TextureCube m_texture;
};

struct BgfxSampler2DMS
{
	Texture2DMS<vec4> m_texture;
};

vec4 bgfxTexture2D(BgfxSampler2D _sampler, vec2 _coord)
{
	return _sampler.m_texture.Sample(_sampler.m_sampler, _coord);
}

vec4 bgfxTexture2DLod(BgfxSampler2D _sampler, vec2 _coord, float _level)
{
	return _sampler.m_texture.SampleLevel(_sampler.m_sampler, _coord, _level);
}

vec4 bgfxTexture2DProj(BgfxSampler2D _sampler, vec3 _coord)
{
	vec2 coord = _coord.xy * rcp(_coord.z);
	return _sampler.m_texture.Sample(_sampler.m_sampler, coord);
}

vec4 bgfxTexture2DProj(BgfxSampler2D _sampler, vec4 _coord)
{
	vec2 coord = _coord.xy * rcp(_coord.w);
	return _sampler.m_texture.Sample(_sampler.m_sampler, coord);
}

vec4 bgfxTexture2DGrad(BgfxSampler2D _sampler, vec2 _coord, vec2 _dPdx, vec2 _dPdy)
{
	return _sampler.m_texture.SampleGrad(_sampler.m_sampler, _coord, _dPdx, _dPdy);
}

vec4 bgfxTexture2DArray(BgfxSampler2DArray _sampler, vec3 _coord)
{
	return _sampler.m_texture.Sample(_sampler.m_sampler, _coord);
}

vec4 bgfxTexture2DArrayLod(BgfxSampler2DArray _sampler, vec3 _coord, float _lod)
{
	return _sampler.m_texture.SampleLevel(_sampler.m_sampler, _coord, _lod);
}

float bgfxShadow2D(BgfxSampler2DShadow _sampler, vec3 _coord)
{
	return _sampler.m_texture.SampleCmpLevelZero(_sampler.m_sampler, _coord.xy, _coord.z);
}

float bgfxShadow2DProj(BgfxSampler2DShadow _sampler, vec4 _coord)
{
	vec3 coord = _coord.xyz * rcp(_coord.w);
	return _sampler.m_texture.SampleCmpLevelZero(_sampler.m_sampler, coord.xy, coord.z);
}

vec4 bgfxTexture3D(BgfxSampler3D _sampler, vec3 _coord)
{
	return _sampler.m_texture.Sample(_sampler.m_sampler, _coord);
}

vec4 bgfxTexture3DLod(BgfxSampler3D _sampler, vec3 _coord, float _level)
{
	return _sampler.m_texture.SampleLevel(_sampler.m_sampler, _coord, _level);
}

ivec4 bgfxTexture3D(BgfxISampler3D _sampler, vec3 _coord)
{
	uvec3 size;
	_sampler.m_texture.GetDimensions(size.x, size.y, size.z);
	return _sampler.m_texture.Load(ivec4(_coord * size, 0) );
}

uvec4 bgfxTexture3D(BgfxUSampler3D _sampler, vec3 _coord)
{
	uvec3 size;
	_sampler.m_texture.GetDimensions(size.x, size.y, size.z);
	return _sampler.m_texture.Load(ivec4(_coord * size, 0) );
}

vec4 bgfxTextureCube(BgfxSamplerCube _sampler, vec3 _coord)
{
	return _sampler.m_texture.Sample(_sampler.m_sampler, _coord);
}

vec4 bgfxTextureCubeLod(BgfxSamplerCube _sampler, vec3 _coord, float _level)
{
	return _sampler.m_texture.SampleLevel(_sampler.m_sampler, _coord, _level);
}

vec4 bgfxTexelFetch(BgfxSampler2D _sampler, ivec2 _coord, int _lod)
{
	return _sampler.m_texture.Load(ivec3(_coord, _lod) );
}

ivec4 bgfxTexelFetch(BgfxISampler2D _sampler, ivec2 _coord, int _lod)
{
	return _sampler.m_texture.Load(ivec3(_coord, _lod) );
}

uvec4 bgfxTexelFetch(BgfxUSampler2D _sampler, ivec2 _coord, int _lod)
{
	return _sampler.m_texture.Load(ivec3(_coord, _lod) );
}

vec4 bgfxTexelFetch(BgfxSampler2DMS _sampler, ivec2 _coord, int _sampleIdx)
{
	return _sampler.m_texture.Load(_coord, _sampleIdx);
}

vec4 bgfxTexelFetch(BgfxSampler3D _sampler, ivec3 _coord, int _lod)
{
	return _sampler.m_texture.Load(ivec4(_coord, _lod) );
}

#		define SAMPLER2D(_name, _reg) \
			uniform SamplerState _name ## Sampler : REGISTER(s, _reg); \
			uniform Texture2D _name ## Texture : REGISTER(t, _reg); \
			static BgfxSampler2D _name = { _name ## Sampler, _name ## Texture }
#		define ISAMPLER2D(_name, _reg) \
			uniform Texture2D<ivec4> _name ## Texture : REGISTER(t, _reg); \
			static BgfxISampler2D _name = { _name ## Texture }
#		define USAMPLER2D(_name, _reg) \
			uniform Texture2D<uvec4> _name ## Texture : REGISTER(t, _reg); \
			static BgfxUSampler2D _name = { _name ## Texture }
#		define sampler2D BgfxSampler2D
#		define texture2D(_sampler, _coord) bgfxTexture2D(_sampler, _coord)
#		define texture2DLod(_sampler, _coord, _level) bgfxTexture2DLod(_sampler, _coord, _level)
#		define texture2DProj(_sampler, _coord) bgfxTexture2DProj(_sampler, _coord)
#		define texture2DGrad(_sampler, _coord, _dPdx, _dPdy) bgfxTexture2DGrad(_sampler, _coord, _dPdx, _dPdy)

#		define SAMPLER2DARRAY(_name, _reg) \
			uniform SamplerState _name ## Sampler : REGISTER(s, _reg); \
			uniform Texture2DArray _name ## Texture : REGISTER(t, _reg); \
			static BgfxSampler2DArray _name = { _name ## Sampler, _name ## Texture }
#		define sampler2DArray BgfxSampler2DArray
#		define texture2DArray(_sampler, _coord) bgfxTexture2DArray(_sampler, _coord)
#		define texture2DArrayLod(_sampler, _coord, _lod) bgfxTexture2DArrayLod(_sampler, _coord, _lod)

#		define SAMPLER2DMS(_name, _reg) \
			uniform Texture2DMS<vec4> _name ## Texture : REGISTER(t, _reg); \
			static BgfxSampler2DMS _name = { _name ## Texture }
#		define sampler2DMS BgfxSampler2DMS

#		define SAMPLER2DSHADOW(_name, _reg) \
			uniform SamplerComparisonState _name ## SamplerComparison : REGISTER(s, _reg); \
			uniform Texture2D _name ## Texture : REGISTER(t, _reg); \
			static BgfxSampler2DShadow _name = { _name ## SamplerComparison, _name ## Texture }
#		define sampler2DShadow BgfxSampler2DShadow
#		define shadow2D(_sampler, _coord) bgfxShadow2D(_sampler, _coord)
#		define shadow2DProj(_sampler, _coord) bgfxShadow2DProj(_sampler, _coord)

#		define SAMPLER3D(_name, _reg) \
			uniform SamplerState _name ## Sampler : REGISTER(s, _reg); \
			uniform Texture3D _name ## Texture : REGISTER(t, _reg); \
			static BgfxSampler3D _name = { _name ## Sampler, _name ## Texture }
#		define ISAMPLER3D(_name, _reg) \
			uniform Texture3D<ivec4> _name ## Texture : REGISTER(t, _reg); \
			static BgfxISampler3D _name = { _name ## Texture }
#		define USAMPLER3D(_name, _reg) \
			uniform Texture3D<uvec4> _name ## Texture : REGISTER(t, _reg); \
			static BgfxUSampler3D _name = { _name ## Texture }
#		define sampler3D BgfxSampler3D
#		define texture3D(_sampler, _coord) bgfxTexture3D(_sampler, _coord)
#		define texture3DLod(_sampler, _coord, _level) bgfxTexture3DLod(_sampler, _coord, _level)

#		define SAMPLERCUBE(_name, _reg) \
			uniform SamplerState _name ## Sampler : REGISTER(s, _reg); \
			uniform TextureCube _name ## Texture : REGISTER(t, _reg); \
			static BgfxSamplerCube _name = { _name ## Sampler, _name ## Texture }
#		define samplerCube BgfxSamplerCube
#		define textureCube(_sampler, _coord) bgfxTextureCube(_sampler, _coord)
#		define textureCubeLod(_sampler, _coord, _level) bgfxTextureCubeLod(_sampler, _coord, _level)

#		define texelFetch(_sampler, _coord, _lod) bgfxTexelFetch(_sampler, _coord, _lod)
#	else

#		define sampler2DShadow sampler2D

vec4 bgfxTexture2DProj(sampler2D _sampler, vec3 _coord)
{
	return tex2Dproj(_sampler, vec4(_coord.xy, 0.0, _coord.z) );
}

vec4 bgfxTexture2DProj(sampler2D _sampler, vec4 _coord)
{
	return tex2Dproj(_sampler, _coord);
}

float bgfxShadow2D(sampler2DShadow _sampler, vec3 _coord)
{
#if 0
	float occluder = tex2D(_sampler, _coord.xy).x;
	return step(_coord.z, occluder);
#else
	return tex2Dproj(_sampler, vec4(_coord.xy, _coord.z, 1.0) ).x;
#endif // 0
}

float bgfxShadow2DProj(sampler2DShadow _sampler, vec4 _coord)
{
#if 0
	vec3 coord = _coord.xyz * rcp(_coord.w);
	float occluder = tex2D(_sampler, coord.xy).x;
	return step(coord.z, occluder);
#else
	return tex2Dproj(_sampler, _coord).x;
#endif // 0
}

#		define SAMPLER2D(_name, _reg) uniform sampler2D _name : REGISTER(s, _reg)
#		define SAMPLER2DMS(_name, _reg) uniform sampler2DMS _name : REGISTER(s, _reg)
#		define texture2D(_sampler, _coord) tex2D(_sampler, _coord)
#		define texture2DProj(_sampler, _coord) bgfxTexture2DProj(_sampler, _coord)

#		define SAMPLER2DARRAY(_name, _reg) SAMPLER2D(_name, _reg)
#		define texture2DArray(_sampler, _coord) texture2D(_sampler, (_coord).xy)
#		define texture2DArrayLod(_sampler, _coord, _lod) texture2DLod(_sampler, _coord, _lod)

#		define SAMPLER2DSHADOW(_name, _reg) uniform sampler2DShadow _name : REGISTER(s, _reg)
#		define shadow2D(_sampler, _coord) bgfxShadow2D(_sampler, _coord)
#		define shadow2DProj(_sampler, _coord) bgfxShadow2DProj(_sampler, _coord)

#		define SAMPLER3D(_name, _reg) uniform sampler3D _name : REGISTER(s, _reg)
#		define texture3D(_sampler, _coord) tex3D(_sampler, _coord)

#		define SAMPLERCUBE(_name, _reg) uniform samplerCUBE _name : REGISTER(s, _reg)
#		define textureCube(_sampler, _coord) texCUBE(_sampler, _coord)

#		if BGFX_SHADER_LANGUAGE_HLSL == 2
#			define texture2DLod(_sampler, _coord, _level) tex2D(_sampler, (_coord).xy)
#			define texture2DGrad(_sampler, _coord, _dPdx, _dPdy) tex2D(_sampler, _coord)
#			define texture3DLod(_sampler, _coord, _level) tex3D(_sampler, (_coord).xyz)
#			define textureCubeLod(_sampler, _coord, _level) texCUBE(_sampler, (_coord).xyz)
#		else
#			define texture2DLod(_sampler, _coord, _level) tex2Dlod(_sampler, vec4( (_coord).xy, 0.0, _level) )
#			define texture2DGrad(_sampler, _coord, _dPdx, _dPdy) tex2Dgrad(_sampler, _coord, _dPdx, _dPdy)
#			define texture3DLod(_sampler, _coord, _level) tex3Dlod(_sampler, vec4( (_coord).xyz, _level) )
#			define textureCubeLod(_sampler, _coord, _level) texCUBElod(_sampler, vec4( (_coord).xyz, _level) )
#		endif // BGFX_SHADER_LANGUAGE_HLSL == 2

#	endif // BGFX_SHADER_LANGUAGE_HLSL > 3

vec3 instMul(vec3 _vec, mat3 _mtx) { return mul(_mtx, _vec); }
vec3 instMul(mat3 _mtx, vec3 _vec) { return mul(_vec, _mtx); }
vec4 instMul(vec4 _vec, mat4 _mtx) { return mul(_mtx, _vec); }
vec4 instMul(mat4 _mtx, vec4 _vec) { return mul(_vec, _mtx); }

bvec2 lessThan(vec2 _a, vec2 _b) { return _a < _b; }
bvec3 lessThan(vec3 _a, vec3 _b) { return _a < _b; }
bvec4 lessThan(vec4 _a, vec4 _b) { return _a < _b; }

bvec2 lessThanEqual(vec2 _a, vec2 _b) { return _a <= _b; }
bvec3 lessThanEqual(vec3 _a, vec3 _b) { return _a <= _b; }
bvec4 lessThanEqual(vec4 _a, vec4 _b) { return _a <= _b; }

bvec2 greaterThan(vec2 _a, vec2 _b) { return _a > _b; }
bvec3 greaterThan(vec3 _a, vec3 _b) { return _a > _b; }
bvec4 greaterThan(vec4 _a, vec4 _b) { return _a > _b; }

bvec2 greaterThanEqual(vec2 _a, vec2 _b) { return _a >= _b; }
bvec3 greaterThanEqual(vec3 _a, vec3 _b) { return _a >= _b; }
bvec4 greaterThanEqual(vec4 _a, vec4 _b) { return _a >= _b; }

bvec2 notEqual(vec2 _a, vec2 _b) { return _a != _b; }
bvec3 notEqual(vec3 _a, vec3 _b) { return _a != _b; }
bvec4 notEqual(vec4 _a, vec4 _b) { return _a != _b; }

bvec2 equal(vec2 _a, vec2 _b) { return _a == _b; }
bvec3 equal(vec3 _a, vec3 _b) { return _a == _b; }
bvec4 equal(vec4 _a, vec4 _b) { return _a == _b; }

float mix(float _a, float _b, float _t) { return lerp(_a, _b, _t); }
vec2  mix(vec2  _a, vec2  _b, vec2  _t) { return lerp(_a, _b, _t); }
vec3  mix(vec3  _a, vec3  _b, vec3  _t) { return lerp(_a, _b, _t); }
vec4  mix(vec4  _a, vec4  _b, vec4  _t) { return lerp(_a, _b, _t); }

float mod(float _a, float _b) { return _a - _b * floor(_a / _b); }
vec2  mod(vec2  _a, vec2  _b) { return _a - _b * floor(_a / _b); }
vec3  mod(vec3  _a, vec3  _b) { return _a - _b * floor(_a / _b); }
vec4  mod(vec4  _a, vec4  _b) { return _a - _b * floor(_a / _b); }

#else
#	define CONST(_x) const _x
#	define atan2(_x, _y) atan(_x, _y)
#	define mul(_a, _b) ( (_a) * (_b) )
#	define saturate(_x) clamp(_x, 0.0, 1.0)
#	define SAMPLER2D(_name, _reg)       uniform sampler2D _name
#	define SAMPLER2DMS(_name, _reg)     uniform sampler2DMS _name
#	define SAMPLER3D(_name, _reg)       uniform sampler3D _name
#	define SAMPLERCUBE(_name, _reg)     uniform samplerCube _name
#	define SAMPLER2DSHADOW(_name, _reg) uniform sampler2DShadow _name

#	define SAMPLER2DARRAY(_name, _reg)       uniform sampler2DArray _name
#	define SAMPLER2DMSARRAY(_name, _reg)     uniform sampler2DMSArray _name
#	define SAMPLERCUBEARRAY(_name, _reg)     uniform samplerCubeArray _name
#	define SAMPLER2DARRAYSHADOW(_name, _reg) uniform sampler2DArrayShadow _name

#	if BGFX_SHADER_LANGUAGE_GLSL >= 130
#		define ISAMPLER2D(_name, _reg) uniform isampler2D _name
#		define USAMPLER2D(_name, _reg) uniform usampler2D _name
#		define ISAMPLER3D(_name, _reg) uniform isampler3D _name
#		define USAMPLER3D(_name, _reg) uniform usampler3D _name

#		define texture2D(_sampler, _coord)      texture(_sampler, _coord)
#		define texture2DArray(_sampler, _coord) texture(_sampler, _coord)
#		define texture3D(_sampler, _coord)      texture(_sampler, _coord)
#	endif // BGFX_SHADER_LANGUAGE_GLSL >= 130

vec3 instMul(vec3 _vec, mat3 _mtx) { return mul(_vec, _mtx); }
vec3 instMul(mat3 _mtx, vec3 _vec) { return mul(_mtx, _vec); }
vec4 instMul(vec4 _vec, mat4 _mtx) { return mul(_vec, _mtx); }
vec4 instMul(mat4 _mtx, vec4 _vec) { return mul(_mtx, _vec); }

float rcp(float _a) { return 1.0/_a; }
vec2  rcp(vec2  _a) { return vec2(1.0)/_a; }
vec3  rcp(vec3  _a) { return vec3(1.0)/_a; }
vec4  rcp(vec4  _a) { return vec4(1.0)/_a; }
#endif // BGFX_SHADER_LANGUAGE_*

vec2 vec2_splat(float _x) { return vec2(_x, _x); }
vec3 vec3_splat(float _x) { return vec3(_x, _x, _x); }
vec4 vec4_splat(float _x) { return vec4(_x, _x, _x, _x); }

#if BGFX_SHADER_LANGUAGE_GLSL >= 130 || BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_SPIRV
uvec2 uvec2_splat(uint _x) { return uvec2(_x, _x); }
uvec3 uvec3_splat(uint _x) { return uvec3(_x, _x, _x); }
uvec4 uvec4_splat(uint _x) { return uvec4(_x, _x, _x, _x); }
#endif // BGFX_SHADER_LANGUAGE_GLSL >= 130 || BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_SPIRV

uniform vec4  u_viewRect;
uniform vec4  u_viewTexel;
uniform mat4  u_view;
uniform mat4  u_invView;
uniform mat4  u_proj;
uniform mat4  u_invProj;
uniform mat4  u_viewProj;
uniform mat4  u_invViewProj;
uniform mat4  u_model[BGFX_CONFIG_MAX_BONES];
uniform mat4  u_modelView;
uniform mat4  u_modelViewProj;
uniform vec4  u_alphaRef4;
#define u_alphaRef u_alphaRef4.x

#endif // __cplusplus

#endif // BGFX_SHADER_H_HEADER_GUARD
