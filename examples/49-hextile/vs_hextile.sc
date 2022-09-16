$input a_position, a_texcoord0
$output v_position, v_texcoord0

/*
 * Copyright 2015 Andrew Mac. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

void main()
{
	vec3 vp = mul(u_model[0], vec4(a_position.xyz, 1.0)).xyz;
	v_position = vp;
	v_texcoord0 = mul(u_model[0], vec4(a_texcoord0.xy, 1.0, 1.0)).xy;

	gl_Position = mul(u_viewProj, vec4(vp.xyz, 1.0));
}
