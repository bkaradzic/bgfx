/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_SHADER_H_HEADER_GUARD
#define BGFX_SHADER_H_HEADER_GUARD

#if !defined(BGFX_CONFIG_MAX_BONES)
#	define BGFX_CONFIG_MAX_BONES 32
#endif // !defined(BGFX_CONFIG_MAX_BONES)

#ifndef __cplusplus

#if BGFX_SHADER_LANGUAGE_HLSL
#	define dFdx(_x) ddx(_x)
#	define dFdy(_y) ddy(-_y)
#	define inversesqrt(_x) rsqrt(_x)
#	define fract(_x) frac(_x)

#	define bvec2 bool2
#	define bvec3 bool3
#	define bvec4 bool4

#	if BGFX_SHADER_LANGUAGE_HLSL > 3
struct BgfxSampler2D
{
	SamplerState m_sampler;
	Texture2D m_texture;
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

struct BgfxSampler2DShadow
{
	SamplerComparisonState m_sampler;
	Texture2D m_texture;
};

float bgfxShadow2D(BgfxSampler2DShadow _sampler, vec3 _coord)
{
	return _sampler.m_texture.SampleCmpLevelZero(_sampler.m_sampler, _coord.xy, _coord.z * 2.0 - 1.0);
}

float bgfxShadow2DProj(BgfxSampler2DShadow _sampler, vec4 _coord)
{
	vec3 coord = _coord.xyz * rcp(_coord.w);
	return _sampler.m_texture.SampleCmpLevelZero(_sampler.m_sampler, coord.xy, coord.z * 2.0 - 1.0);
}

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
	ivec3 size;
	_sampler.m_texture.GetDimensions(size.x, size.y, size.z);
	return _sampler.m_texture.Load(ivec4(_coord * size, 0) );
}

uvec4 bgfxTexture3D(BgfxUSampler3D _sampler, vec3 _coord)
{
	uvec3 size;
	_sampler.m_texture.GetDimensions(size.x, size.y, size.z);
	return _sampler.m_texture.Load(uvec4(_coord * size, 0) );
}

struct BgfxSamplerCube
{
	SamplerState m_sampler;
	TextureCube m_texture;
};

vec4 bgfxTextureCube(BgfxSamplerCube _sampler, vec3 _coord)
{
	return _sampler.m_texture.Sample(_sampler.m_sampler, _coord);
}

vec4 bgfxTextureCubeLod(BgfxSamplerCube _sampler, vec3 _coord, float _level)
{
	return _sampler.m_texture.SampleLevel(_sampler.m_sampler, _coord, _level);
}

#		define SAMPLER2D(_name, _reg) \
			uniform SamplerState _name ## Sampler : register(s[_reg]); \
			uniform Texture2D _name ## Texture : register(t[_reg]); \
			static BgfxSampler2D _name = { _name ## Sampler, _name ## Texture }
#		define sampler2D BgfxSampler2D
#		define texture2D(_sampler, _coord) bgfxTexture2D(_sampler, _coord)
#		define texture2DLod(_sampler, _coord, _level) bgfxTexture2DLod(_sampler, _coord, _level)
#		define texture2DProj(_sampler, _coord) bgfxTexture2DProj(_sampler, _coord)

#		define SAMPLER2DSHADOW(_name, _reg) \
			uniform SamplerComparisonState _name ## Sampler : register(s[_reg]); \
			uniform Texture2D _name ## Texture : register(t[_reg]); \
			static BgfxSampler2DShadow _name = { _name ## Sampler, _name ## Texture }
#		define sampler2DShadow BgfxSampler2DShadow
#		define shadow2D(_sampler, _coord) bgfxShadow2D(_sampler, _coord)
#		define shadow2DProj(_sampler, _coord) bgfxShadow2DProj(_sampler, _coord)

#		define SAMPLER3D(_name, _reg) \
			uniform SamplerState _name ## Sampler : register(s[_reg]); \
			uniform Texture3D _name ## Texture : register(t[_reg]); \
			static BgfxSampler3D _name = { _name ## Sampler, _name ## Texture }
#		define ISAMPLER3D(_name, _reg) \
			uniform Texture3D<ivec4> _name ## Texture : register(t[_reg]); \
			static BgfxISampler3D _name = { _name ## Texture }
#		define USAMPLER3D(_name, _reg) \
			uniform Texture3D<uvec4> _name ## Texture : register(t[_reg]); \
			static BgfxUSampler3D _name = { _name ## Texture }
#		define sampler3D BgfxSampler3D
#		define texture3D(_sampler, _coord) bgfxTexture3D(_sampler, _coord)
#		define texture3DLod(_sampler, _coord, _level) bgfxTexture3DLod(_sampler, _coord, _level)

#		define SAMPLERCUBE(_name, _reg) \
			uniform SamplerState _name ## Sampler : register(s[_reg]); \
			uniform TextureCube _name ## Texture : register(t[_reg]); \
			static BgfxSamplerCube _name = { _name ## Sampler, _name ## Texture }
#		define samplerCube BgfxSamplerCube
#		define textureCube(_sampler, _coord) bgfxTextureCube(_sampler, _coord)
#		define textureCubeLod(_sampler, _coord, _level) bgfxTextureCubeLod(_sampler, _coord, _level)
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
	return step(_coord.z * 2.0 - 1.0, occluder);
#else
	return tex2Dproj(_sampler, vec4(_coord.xy, _coord.z * 2.0 - 1.0, 1.0) ).x;
#endif // 0
}

float bgfxShadow2DProj(sampler2DShadow _sampler, vec4 _coord)
{
#if 0
	vec3 coord = _coord.xyz * rcp(_coord.w);
	float occluder = tex2D(_sampler, coord.xy).x;
	return step(coord.z * 2.0 - 1.0, occluder);
#else
	return tex2Dproj(_sampler, _coord).x;
#endif // 0
}

#		define SAMPLER2D(_name, _reg) uniform sampler2D _name : register(s ## _reg)
#		define texture2D(_sampler, _coord) tex2D(_sampler, _coord)
#		define texture2DProj(_sampler, _coord) bgfxTexture2DProj(_sampler, _coord)

#		define SAMPLER2DSHADOW(_name, _reg) uniform sampler2DShadow _name : register(s ## _reg)
#		define shadow2D(_sampler, _coord) bgfxShadow2D(_sampler, _coord)
#		define shadow2DProj(_sampler, _coord) bgfxShadow2DProj(_sampler, _coord)

#		define SAMPLER3D(_name, _reg) uniform sampler3D _name : register(s ## _reg)
#		define texture3D(_sampler, _coord) tex3D(_sampler, _coord)

#		define SAMPLERCUBE(_name, _reg) uniform samplerCUBE _name : register(s[_reg])
#		define textureCube(_sampler, _coord) texCUBE(_sampler, _coord)

#		if BGFX_SHADER_LANGUAGE_HLSL == 2
#			define texture2DLod(_sampler, _coord, _level) tex2D(_sampler, (_coord).xy)
#			define texture3DLod(_sampler, _coord, _level) tex3D(_sampler, (_coord).xyz)
#			define textureCubeLod(_sampler, _coord, _level) texCUBE(_sampler, (_coord).xyz)
#		else
#			define texture2DLod(_sampler, _coord, _level) tex2Dlod(_sampler, vec4( (_coord).xy, 0.0, _level) )
#			define texture3DLod(_sampler, _coord, _level) tex3Dlod(_sampler, vec4( (_coord).xyz, _level) )
#			define textureCubeLod(_sampler, _coord, _level) texCUBElod(_sampler, vec4( (_coord).xyz, _level) )
#		endif // BGFX_SHADER_LANGUAGE_HLSL == 2

#	endif // BGFX_SHADER_LANGUAGE_HLSL > 3

vec2 vec2_splat(float _x) { return vec2(_x, _x); }
vec3 vec3_splat(float _x) { return vec3(_x, _x, _x); }
vec4 vec4_splat(float _x) { return vec4(_x, _x, _x, _x); }

uvec2 uvec2_splat(uint _x) { return uvec2(_x, _x); }
uvec3 uvec3_splat(uint _x) { return uvec3(_x, _x, _x); }
uvec4 uvec4_splat(uint _x) { return uvec4(_x, _x, _x, _x); }

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
#	define atan2(_x, _y) atan(_x, _y)
#	define mul(_a, _b) ( (_a) * (_b) )
#	define saturate(_x) clamp(_x, 0.0, 1.0)
#	define SAMPLER2D(_name, _reg) uniform sampler2D _name
#	define SAMPLER3D(_name, _reg) uniform sampler3D _name
#	define SAMPLERCUBE(_name, _reg) uniform samplerCube _name
#	define SAMPLER2DSHADOW(_name, _reg) uniform sampler2DShadow _name
#	define vec2_splat(_x) vec2(_x)
#	define vec3_splat(_x) vec3(_x)
#	define vec4_splat(_x) vec4(_x)
#	define uvec2_splat(_x) uvec2(_x)
#	define uvec3_splat(_x) uvec3(_x)
#	define uvec4_splat(_x) uvec4(_x)

#	if BGFX_SHADER_LANGUAGE_GLSL >= 130
#		define ISAMPLER3D(_name, _reg) uniform isampler3D _name
#		define USAMPLER3D(_name, _reg) uniform usampler3D _name
ivec4 texture3D(isampler3D _sampler, vec3 _coord) { return texture(_sampler, _coord); }
uvec4 texture3D(usampler3D _sampler, vec3 _coord) { return texture(_sampler, _coord); }
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
