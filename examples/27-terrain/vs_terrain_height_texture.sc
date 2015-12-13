$input a_position, a_texcoord0
$output v_position, v_texcoord0

/*
 * Copyright 2015 Andrew Mac. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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
