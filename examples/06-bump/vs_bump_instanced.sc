$input a_position, a_normal, a_tangent, a_texcoord0, i_data0, i_data1, i_data2, i_data3
$output v_wpos, v_view, v_normal, v_tangent, v_bitangent, v_texcoord0

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	mat4 model;
	model[0] = i_data0;
	model[1] = i_data1;
	model[2] = i_data2;
	model[3] = i_data3;

	vec3 wpos = instMul(model, vec4(a_position, 1.0) ).xyz;
	gl_Position = mul(u_viewProj, vec4(wpos, 1.0) );
	
	vec4 normal = a_normal * 2.0 - 1.0;
	vec3 wnormal = instMul(model, vec4(normal.xyz, 0.0) ).xyz;

	vec4 tangent = a_tangent * 2.0 - 1.0;
	vec3 wtangent = instMul(model, vec4(tangent.xyz, 0.0) ).xyz;

	v_normal = wnormal;
	v_tangent = wtangent;
	v_bitangent = cross(v_normal, v_tangent) * tangent.w;

	mat3 tbn = mat3(v_tangent, v_bitangent, v_normal);

	v_wpos = wpos;

	vec3 weyepos = mul(vec4(0.0, 0.0, 0.0, 1.0), u_view).xyz;		
	v_view = instMul(weyepos - wpos, tbn);

	v_texcoord0 = a_texcoord0;
}
