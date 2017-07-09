$input v_texcoord0, v_color0

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

SAMPLERCUBE(s_texColor, 0);

uniform vec4 u_params;
#define u_textureLod u_params.x

void main()
{
	vec4 color = textureCubeLod(s_texColor, v_texcoord0, u_textureLod);
	gl_FragColor = color * v_color0;
}
