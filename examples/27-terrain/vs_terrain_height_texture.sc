$input a_position, a_texcoord0
$output v_position, v_texcoord0

/*
 * Copyright 2015 Andrew Mac. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLER2D(s_heightTexture, 0);

void main()
{
	v_texcoord0 = a_texcoord0;
	v_position = a_position.xyz;
	v_position.y = texture2DLod(s_heightTexture, a_texcoord0, 0).x * 255.0;

	gl_Position = mul(u_modelViewProj, vec4(v_position.xyz, 1.0));
}
