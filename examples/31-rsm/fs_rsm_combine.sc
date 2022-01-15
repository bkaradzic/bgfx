$input v_texcoord0

/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLER2D(s_normal, 0);
SAMPLER2D(s_color,  1);
SAMPLER2D(s_light,  2);
SAMPLER2D(s_depth,  3);
SAMPLER2DSHADOW(s_shadowMap, 4);

// Single directional light for entire scene
uniform vec4 u_lightDir;
uniform mat4 u_invMvp;
uniform mat4 u_lightMtx;
uniform vec4 u_shadowDimsInv;
uniform vec4 u_rsmAmount;

float hardShadow(sampler2DShadow _sampler, vec4 _shadowCoord, float _bias)
{
	vec2 texCoord = _shadowCoord.xy;
	return shadow2D(_sampler, vec3(texCoord.xy, _shadowCoord.z-_bias) );
}

float PCF(sampler2DShadow _sampler, vec4 _shadowCoord, float _bias, vec2 _texelSize)
{
	vec2 texCoord = _shadowCoord.xy;

	bool outside = any(greaterThan(texCoord, vec2_splat(1.0)))
		|| any(lessThan   (texCoord, vec2_splat(0.0)))
		;

	if (outside)
	{
		return 1.0;
	}

	float result = 0.0;
	vec2 offset = _texelSize * _shadowCoord.w;

	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-1.5, -1.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-1.5, -0.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-1.5,  0.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-1.5,  1.5) * offset, 0.0, 0.0), _bias);

	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-0.5, -1.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-0.5, -0.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-0.5,  0.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-0.5,  1.5) * offset, 0.0, 0.0), _bias);

	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(0.5, -1.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(0.5, -0.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(0.5,  0.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(0.5,  1.5) * offset, 0.0, 0.0), _bias);

	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(1.5, -1.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(1.5, -0.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(1.5,  0.5) * offset, 0.0, 0.0), _bias);
	result += hardShadow(_sampler, _shadowCoord + vec4(vec2(1.5,  1.5) * offset, 0.0, 0.0), _bias);

	return result / 16.0;
}

void main()
{
	vec3 n  = texture2D(s_normal, v_texcoord0).xyz;
	// Expand out normal
	n = n*2.0+-1.0;
	vec3 l = u_lightDir.xyz;//normalize(vec3(-0.8,0.75,-1.0));
	float dirLightIntensity = 1.0;
	float dirLight = max(0.0,dot(n,l)) * dirLightIntensity;

	// Apply shadow map

	// Get world position so we can transform it into light space, to look into shadow map
	vec2 texCoord = v_texcoord0.xy;
	float deviceDepth = texture2D(s_depth, texCoord).x;
	float depth       = toClipSpaceDepth(deviceDepth);
	vec3 clip = vec3(texCoord * 2.0 - 1.0, depth);
#if !BGFX_SHADER_LANGUAGE_GLSL
	clip.y = -clip.y;
#endif // !BGFX_SHADER_LANGUAGE_GLSL
	vec3 wpos = clipToWorld(u_invMvp, clip);

	const float shadowMapOffset = 0.003;
	vec3 posOffset = wpos + n.xyz * shadowMapOffset;
	vec4 shadowCoord = mul(u_lightMtx, vec4(posOffset, 1.0) );

#if !BGFX_SHADER_LANGUAGE_GLSL
	shadowCoord.y *= -1.0;
#endif // !BGFX_SHADER_LANGUAGE_GLSL

	float shadowMapBias = 0.001;
	vec2 texelSize = vec2_splat(u_shadowDimsInv.x);

	shadowCoord.xy /= shadowCoord.w;
	shadowCoord.xy = shadowCoord.xy*0.5 + 0.5;

#if BGFX_SHADER_LANGUAGE_GLSL
	shadowCoord.z = shadowCoord.z*0.5 + 0.5;
#endif // BGFX_SHADER_LANGUAGE_GLSL

	float visibility = PCF(s_shadowMap, shadowCoord, shadowMapBias, texelSize);

	dirLight *= visibility;

	// Light from light buffer
	vec3 albedo = texture2D(s_color, v_texcoord0).xyz;
	vec3 lightBuffer = texture2D(s_light, v_texcoord0).xyz;

	gl_FragColor.xyz = mix(dirLight * albedo, lightBuffer * albedo, u_rsmAmount.x);

	gl_FragColor.w = 1.0;
}
