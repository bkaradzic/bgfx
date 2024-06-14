$input v_texcoord0

/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLERCUBE(s_texCube, 0);
uniform vec4 u_time;

void main()
{
	float lod = (1.0 - cos(u_time.x)) * 4.0; // 0 to 8
	gl_FragColor = textureCubeLod(s_texCube, v_texcoord0, lod);
}
