$input v_texcoord0, v_color0

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

SAMPLER2D(s_texColor, 0);

uniform vec4 u_params;
#define u_textureLod u_params.x

void main()
{
	vec4 color = texture2DLod(s_texColor, v_texcoord0.xy, u_textureLod);
	gl_FragColor = color * v_color0;
}
