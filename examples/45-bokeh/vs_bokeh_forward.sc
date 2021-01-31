$input a_position, a_normal, a_texcoord0
$output v_normal, v_texcoord0, v_texcoord1, v_texcoord2

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "../common/common.sh"

void main()
{
	// Calculate vertex position
	vec3 pos = a_position.xyz;
	gl_Position = mul(u_modelViewProj, vec4(pos, 1.0));

	vec3 wsPos  = mul(u_model[0], vec4(pos, 1.0)).xyz;

	// Calculate normal, unpack
	vec3 osNormal = a_normal.xyz * 2.0 - 1.0;

	// Transform normal into world space
	vec3 wsNormal = mul(u_model[0], vec4(osNormal, 0.0)).xyz;

	v_normal.xyz = normalize(wsNormal);
	v_texcoord0 = a_texcoord0;

	// Store world space view vector in extra texCoord attribute
	vec3 wsCamPos = mul(u_invView, vec4(0.0, 0.0, 0.0, 1.0)).xyz;
	vec3 view = normalize(wsCamPos - wsPos);

	v_texcoord1 = vec4(wsPos, 1.0);
	v_texcoord2 = vec4(view, 1.0);
}
