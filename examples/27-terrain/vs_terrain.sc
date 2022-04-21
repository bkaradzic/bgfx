$input a_position, a_texcoord0
$output v_position, v_texcoord0

/*
 * Copyright 2015 Andrew Mac. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

void main()
{
	v_position = a_position.xyz;
	v_texcoord0 = a_texcoord0;

	gl_Position = mul(u_modelViewProj, vec4(v_position.xyz, 1.0));
}
