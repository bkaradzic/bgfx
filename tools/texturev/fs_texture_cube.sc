$input v_texcoord0, v_color0

/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx_shader.sh>

SAMPLERCUBE(s_texColor, 0);
uniform mat4 u_mtx;

uniform vec4 u_params;
#define u_textureLod u_params.x

void main()
{
	vec3 dir = vec3( (v_texcoord0*2.0 - 1.0) * vec2(1.0, -1.0), 1.0);
	dir = normalize(mul(u_mtx, vec4(dir, 0.0) ).xyz);
	gl_FragColor = textureCubeLod(s_texColor, dir, u_textureLod) * v_color0;
}
