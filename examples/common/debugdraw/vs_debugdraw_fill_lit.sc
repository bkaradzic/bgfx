$input a_position
$output v_view, v_world

/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
	v_view  = mul(u_modelView, vec4(a_position, 1.0) ).xyz;
	v_world = mul(u_model[0],  vec4(a_position, 1.0) ).xyz;
}
