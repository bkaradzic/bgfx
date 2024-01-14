$input v_texcoord0

/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.sh"

SAMPLER2D(s_normal, 0);
SAMPLER2D(s_depth,  1);

uniform vec4 u_lightPosRadius[1];
uniform vec4 u_lightRgbInnerR[1];
uniform mat4 u_mtx;

void main()
{
	vec3  normal      = decodeNormalUint(texture2D(s_normal, v_texcoord0).xyz);
	float deviceDepth = texture2D(s_depth, v_texcoord0).x;
	float depth       = toClipSpaceDepth(deviceDepth);

	vec3 clip = vec3(v_texcoord0 * 2.0 - 1.0, depth);
#if !BGFX_SHADER_LANGUAGE_GLSL
	clip.y = -clip.y;
#endif // !BGFX_SHADER_LANGUAGE_GLSL
	vec3 wpos = clipToWorld(u_mtx, clip);

	vec3 view = mul(u_view, vec4(wpos, 0.0) ).xyz;
	view = -normalize(view);

	vec3 lightColor = calcLight(wpos, normal, view, u_lightPosRadius[0].xyz, u_lightPosRadius[0].w, u_lightRgbInnerR[0].xyz, u_lightRgbInnerR[0].w);
	gl_FragColor.xyz = toGamma(lightColor.xyz);
	gl_FragColor.w = 1.0;
}
