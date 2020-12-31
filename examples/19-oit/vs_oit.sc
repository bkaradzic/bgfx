$input a_position
$output v_pos

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	vec3 wpos = mul(u_model[0], vec4(a_position, 1.0) ).xyz;
	gl_Position = mul(u_viewProj, vec4(wpos, 1.0) );
	v_pos = gl_Position;
	vec4 temp =  mul(u_view, vec4(wpos, 1.0) );
	v_pos.x = temp.z;
}
