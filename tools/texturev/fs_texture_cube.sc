$input v_texcoord0, v_color0

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"

SAMPLERCUBE(s_texColor, 0);
uniform mat4 u_mtx;

void main()
{
	vec3 dir = vec3( (v_texcoord0.xy*2.0 - 1.0) * vec2(1.0, -1.0), 1.0);
	dir = normalize(mul(u_mtx, vec4(dir, 0.0) ).xyz);

	vec4 color = textureCubeLod(s_texColor, dir, u_textureLod);
	color.xyz = applyExposure(color.xyz);
	color *= v_color0;

	gl_FragColor = toOutput(color, u_outputFormat, u_sdrWhiteNits);
}
