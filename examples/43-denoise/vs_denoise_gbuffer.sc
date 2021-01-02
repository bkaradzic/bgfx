$input a_position, a_normal, a_texcoord0
$output v_normal, v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3

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

	// Calculate previous frame's position
	mat4 worldToViewPrev = mat4(
		u_worldToViewPrev0,
		u_worldToViewPrev1,
		u_worldToViewPrev2,
		u_worldToViewPrev3
	);
	mat4 viewToProjPrev = mat4(
		u_viewToProjPrev0,
		u_viewToProjPrev1,
		u_viewToProjPrev2,
		u_viewToProjPrev3
	);

	vec3 wsPos  = mul(u_model[0], vec4(pos, 1.0)).xyz;
	vec3 vspPos = instMul(worldToViewPrev, vec4(wsPos, 1.0)).xyz;
	vec4 pspPos = instMul(viewToProjPrev, vec4(vspPos, 1.0));

	// Calculate normal, unpack
	vec3 osNormal = a_normal.xyz * 2.0 - 1.0;

	// Transform normal into world space
	vec3 wsNormal = mul(u_model[0], vec4(osNormal, 0.0)).xyz;

	v_normal.xyz = normalize(wsNormal);
	v_texcoord0 = a_texcoord0;

	// Store previous frame projection space position in extra texCoord attribute
	v_texcoord1 = pspPos;

	// Store world space view vector in extra texCoord attribute
	vec3 wsCamPos = mul(u_invView, vec4(0.0, 0.0, 0.0, 1.0)).xyz;
	vec3 view = normalize(wsCamPos - wsPos);

	v_texcoord2 = vec4(wsPos, 1.0);
	v_texcoord3 = vec4(wsCamPos, 1.0);
}
