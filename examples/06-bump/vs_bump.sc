$input a_position, a_normal, a_tangent, a_texcoord0, i_data0, i_data1, i_data2, i_data3
$output v_wpos, v_view, v_normal, v_tangent, v_texcoord0

/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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
	
	vec3 normal = a_normal * 2.0f - 1.0f;
	vec3 wnormal = instMul(model, vec4(normal, 0.0) ).xyz;

	vec3 tangent = a_tangent * 2.0f - 1.0f;
	vec3 wtangent = instMul(model, vec4(tangent.xyz, 0.0) ).xyz;

	vec3 viewNormal = normalize(mul(u_view, vec4(wnormal, 0.0) ).xyz);
	vec3 viewTangent = normalize(mul(u_view, vec4(wtangent, 0.0) ).xyz);
	mat3 tbn = mat3(viewTangent, cross(viewNormal, viewTangent), viewNormal);

	v_wpos = wpos;

	vec3 view = -mul(u_view, vec4(wpos, 1.0) ).xyz;
	v_view = mul(tbn, view);

	v_normal = viewNormal;
	v_tangent = viewTangent;

	v_texcoord0 = a_texcoord0;
}
