$input a_position, a_color1, a_normal
$output v_view, v_bc, v_normal

/*
 * Copyright 2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"
#include "uniforms.sh"

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );

	v_view = u_camPos - mul(u_model[0], vec4(a_position, 1.0) ).xyz;
	v_bc = a_color1;

	vec3 normal = a_normal.xyz*2.0 - 1.0;
	v_normal = mul(u_model[0], vec4(normal, 0.0) ).xyz;
}
