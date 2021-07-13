$input v_normal

/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

BGFX_BEGIN_UNIFORM_BLOCK(UniformsMaterial)
uniform vec4 u_tint;
BGFX_END_UNIFORM_BLOCK

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
