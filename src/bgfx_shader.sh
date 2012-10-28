/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __BGFX_SHADER_H__
#define __BGFX_SHADER_H__

#ifndef __cplusplus

#if BGFX_SHADER_LANGUAGE_HLSL
#	define dFdx ddx
#	define dFdy ddy

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

struct BgfxSampler3D
{
	SamplerState m_sampler;
	Texture3D m_texture;
};

vec4 bgfxTexture3D(BgfxSampler3D _sampler, vec3 _coord)
{
	return _sampler.m_texture.Sample(_sampler.m_sampler, _coord);
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

#		define SAMPLER2D(_name, _reg) \
			uniform SamplerState _name ## Sampler : register(s[_reg]); \
			uniform Texture2D _name ## Texture : register(t[_reg]); \
			static BgfxSampler2D _name = { _name ## Sampler, _name ## Texture }
#		define sampler2D BgfxSampler2D
#		define texture2D(_name, _coord) bgfxTexture2D(_name, _coord)

#		define SAMPLER3D(_name, _reg) \
			uniform SamplerState _name ## Sampler : register(s[_reg]); \
			uniform Texture3D _name ## Texture : register(t[_reg]); \
			static BgfxSampler3D _name = { _name ## Sampler, _name ## Texture }
#		define sampler3D BgfxSampler3D
#		define texture3D(_name, _coord) bgfxTexture3D(_name, _coord)

#		define SAMPLERCUBE(_name, _reg) \
			uniform SamplerState _name ## Sampler : register(s[_reg]); \
			uniform TextureCube _name ## Texture : register(t[_reg]); \
			static BgfxSamplerCube _name = { _name ## Sampler, _name ## Texture }
#		define samplerCube BgfxSamplerCube
#		define textureCube(_name, _coord) bgfxTextureCube(_name, _coord)
#	else
#		define SAMPLER2D(_name, _reg) uniform sampler2D _name : register(s ## _reg)
#		define texture2D tex2D
#		define SAMPLER3D(_name, _reg) uniform sampler3D _name : register(s ## _reg)
#		define texture3D tex3D
#		define SAMPLERCUBE(_name, _reg) uniform samplerCUBE _name : register(s[_reg])
#		define textureCube texCUBE
#	endif //

#	define vec2_splat(_x) float2(_x, _x)
#	define vec3_splat(_x) float3(_x, _x, _x)
#	define vec4_splat(_x) float4(_x, _x, _x, _x)

vec4 instMul(mat4 _mtx, vec4 _vec)
{
	return mul(_vec, _mtx);
}
#elif BGFX_SHADER_LANGUAGE_GLSL
#	define atan2(_x, _y) atan(_x, _y)
#	define frac(_x) fract(_x)
#	define lerp(_x, _y, _t) mix(_x, _y, _t)
#	define mul(_a, _b) ( (_a) * (_b) )
#	define saturate(_x) clamp(_x, 0.0, 1.0)
#	define SAMPLER2D(_name, _reg) uniform sampler2D _name
#	define SAMPLER3D(_name, _reg) uniform sampler3D _name
#	define SAMPLERCUBE(_name, _reg) uniform samplerCube _name
#	define vec2_splat(_x) vec2(_x)
#	define vec3_splat(_x) vec3(_x)
#	define vec4_splat(_x) vec4(_x)

vec4 instMul(mat4 _mtx, vec4 _vec)
{
	return mul(_mtx, _vec);
}
#endif // BGFX_SHADER_LANGUAGE_HLSL

#endif // __cplusplus

#endif // __BGFX_SHADER_H__
