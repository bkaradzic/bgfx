$input a_position, a_normal
$output v_view, v_normal, v_shadowcoord

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform mat4 u_lightMtx;

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );

	vec4 normal = a_normal * 2.0 - 1.0;
	v_normal = normalize(mul(u_modelView, vec4(normal.xyz, 0.0) ).xyz);
	v_view = mul(u_modelView, vec4(a_position, 1.0)).xyz;

	const float shadowMapOffset = 0.001;
	vec3 posOffset = a_position + normal.xyz * shadowMapOffset;
	v_shadowcoord = mul(u_lightMtx, vec4(posOffset, 1.0) );
}
