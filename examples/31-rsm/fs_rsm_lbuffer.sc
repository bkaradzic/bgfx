$input v_lightCenterScale, v_color0

/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLER2D(s_normal, 0); // Normal output from gbuffer
SAMPLER2D(s_depth,  1);  // Depth output from gbuffer

uniform mat4 u_invMvp;

void main()
{
#if BGFX_SHADER_LANGUAGE_HLSL && (BGFX_SHADER_LANGUAGE_HLSL < 400)
	vec2 texCoord = gl_FragCoord.xy * u_viewTexel.xy + u_viewTexel.xy * vec2_splat(0.5);
#else
	vec2 texCoord = gl_FragCoord.xy * u_viewTexel.xy;
#endif

	// Get world position
	float deviceDepth = texture2D(s_depth, texCoord).x;
	float depth       = toClipSpaceDepth(deviceDepth);

	vec3 clip = vec3(texCoord * 2.0 - 1.0, depth);
#if !BGFX_SHADER_LANGUAGE_GLSL
	clip.y = -clip.y;
#endif // !BGFX_SHADER_LANGUAGE_GLSL
	vec3 wpos = clipToWorld(u_invMvp, clip);

	// Get normal from its map, and decompress
	vec3 n  = texture2D(s_normal, texCoord).xyz*2.0-1.0;

	// Do lighting
	vec3 pointToLight = v_lightCenterScale.xyz-wpos;
	float lightLen = sqrt(dot(pointToLight, pointToLight));

	float lightFalloff;

	if (lightLen > v_lightCenterScale.w)
		lightFalloff = 0.0;
	else
		lightFalloff = 1.0-(lightLen/v_lightCenterScale.w);  // Linear falloff for light (could use dist sq if you want)

	vec3 l = normalize(pointToLight)*lightFalloff;

	gl_FragColor.xyz = v_color0.xyz * max(0.0, dot(n,l));

	gl_FragColor.w = 1.0;
}
