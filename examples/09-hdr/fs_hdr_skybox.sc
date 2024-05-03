$input v_texcoord0

/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.sh"

SAMPLERCUBE(s_texCube, 0);
uniform mat4 u_mtx;

void main()
{
	vec3 dir = vec3(v_texcoord0*2.0 - 1.0, 1.0);
	dir = normalize(mul(u_mtx, vec4(dir, 0.0) ).xyz);
	gl_FragColor = encodeRGBE8(textureCube(s_texCube, dir).xyz);
}
