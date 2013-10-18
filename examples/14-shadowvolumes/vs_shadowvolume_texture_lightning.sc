$input a_position, a_normal, a_texcoord0
$output  v_normal, v_view, v_texcoord0, v_pos

/*
 * Copyright 2013 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh" 

uniform float u_flipV;

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );

	vec4 normal = a_normal * 2.0f - 1.0f;
	v_normal = mul(u_modelView, vec4(normal.xyz, 0.0)).xyz;
	v_view = mul(u_modelView, vec4(a_position, 1.0)).xyz;

	v_texcoord0 = a_texcoord0;

	v_pos = gl_Position;
	v_pos.y *= -u_flipV;
}
