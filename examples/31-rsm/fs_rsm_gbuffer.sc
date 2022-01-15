$input v_normal

/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform vec4 u_tint;

void main()
{
	vec3 normalWorldSpace = v_normal;

	// Write normal
	gl_FragData[0].xyz = normalWorldSpace.xyz; // Normal is already compressed to [0,1] so can fit in gbuffer
	gl_FragData[0].w = 0.0;

	// Write color
	gl_FragData[1] = u_tint;
}
