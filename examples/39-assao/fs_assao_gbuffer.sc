$input v_normal,  v_texcoord0

/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

SAMPLER2D(s_albedo, 0);

void main()
{
	vec3 normalWorldSpace = v_normal;

	// Write normal
	gl_FragData[0].xyz = normalWorldSpace.xyz; // Normal is already compressed to [0,1] so can fit in gbuffer
	gl_FragData[0].w = 0.0;

	// Write color
	gl_FragData[1] = texture2D(s_albedo,  v_texcoord0);
}
