$input a_position, a_normal, a_texcoord0
$output v_normal, v_texcoord0, v_texcoord1

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "../common/common.sh"
#include "parameters.sh"

void main()
{
	// Calculate vertex position
	vec3 pos = a_position.xyz;
	gl_Position = mul(u_modelViewProj, vec4(pos, 1.0));

	// Calculate normal, unpack
	vec3 osNormal = a_normal.xyz * 2.0 - 1.0;

	// Transform normal into world space
	vec3 wsNormal = mul(u_model[0], vec4(osNormal, 0.0)).xyz;
	v_normal.xyz = normalize(wsNormal);

	v_texcoord0 = a_texcoord0;

	// Pass through world space position
	vec3 wsPos  = mul(u_model[0], vec4(pos, 1.0)).xyz;
	v_texcoord1 = vec4(wsPos, 1.0);
}
