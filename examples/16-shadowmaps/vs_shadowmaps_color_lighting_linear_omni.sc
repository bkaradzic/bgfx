$input a_position, a_normal
$output v_position, v_normal, v_view, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform vec4 u_params1;
#define u_shadowMapOffset u_params1.y

uniform mat4 u_lightMtx;
uniform mat4 u_shadowMapMtx0;
uniform mat4 u_shadowMapMtx1;
uniform mat4 u_shadowMapMtx2;
uniform mat4 u_shadowMapMtx3;

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );

	vec4 normal = a_normal * 2.0 - 1.0;
	v_normal = normalize(mul(u_modelView, vec4(normal.xyz, 0.0) ).xyz);
	v_view = mul(u_modelView, vec4(a_position, 1.0)).xyz;

	vec4 posOffset = vec4(a_position + normal.xyz * u_shadowMapOffset, 1.0);
	v_position = mul(u_lightMtx, posOffset);

	v_texcoord1 = mul(u_shadowMapMtx0, v_position);
	v_texcoord2 = mul(u_shadowMapMtx1, v_position);
	v_texcoord3 = mul(u_shadowMapMtx2, v_position);
	v_texcoord4 = mul(u_shadowMapMtx3, v_position);

	v_texcoord1.z += 0.5;
	v_texcoord2.z += 0.5;
	v_texcoord3.z += 0.5;
	v_texcoord4.z += 0.5;
}
