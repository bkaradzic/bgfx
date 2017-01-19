$input a_position, a_color0, a_texcoord0
$output v_color0, v_stipple

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
	v_color0    = a_color0;
	v_stipple   = a_texcoord0.x;
}
