$input a_position, a_normal, a_tangent, a_texcoord0
$output v_pos, v_normal, v_tangent, v_bitangent, v_texcoord0

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_time;

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0) );
	v_pos = gl_Position.xyz;

	vec4 normal = a_normal * 2.0 - 1.0;
	vec4 tangent = a_tangent * 2.0 - 1.0;

	vec3 ws_normal = mul(u_model[0], vec4(normal.xyz, 0.0) ).xyz;
	vec3 ws_tangent = mul(u_model[0], vec4(tangent.xyz, 0.0) ).xyz;
	vec3 ws_bitangent = cross(ws_normal.xyz, ws_tangent.xyz) * tangent.w;

	v_normal = ws_normal;
	v_tangent = ws_tangent;
	v_bitangent = ws_bitangent;

	v_texcoord0 = a_texcoord0;
}
