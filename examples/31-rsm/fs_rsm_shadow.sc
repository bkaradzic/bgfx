$input v_normal

/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform vec4 u_tint;

void main()
{
#if BGFX_SHADER_LANGUAGE_HLSL && (BGFX_SHADER_LANGUAGE_HLSL < 400)
	vec2 texCoord = gl_FragCoord.xy * u_viewTexel.xy + u_viewTexel.xy * vec2_splat(0.5);
#else
	vec2 texCoord = gl_FragCoord.xy * u_viewTexel.xy;
#endif

	gl_FragData[0].xyz = u_tint.xyz;  // Color of light sphere
	gl_FragData[0].w = -v_normal.z;   // Radius of light sphere
}
