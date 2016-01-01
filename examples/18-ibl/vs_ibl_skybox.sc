$input a_position, a_texcoord0
$output v_dir

/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform mat4 u_mtx;

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );

	vec2 tex = 2.0 * a_texcoord0 - 1.0;
	v_dir = mul(u_mtx, vec4(tex, 1.0, 0.0) ).xyz;
}
