$input v_texcoord0, v_color0

/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx_shader.sh>

SAMPLER2D(s_texColor, 0);

uniform vec4 u_params;
#define u_textureLod u_params.x

void main()
{
	vec4 color = texture2DLod(s_texColor, v_texcoord0, u_textureLod);
	gl_FragColor = color * v_color0;
}
