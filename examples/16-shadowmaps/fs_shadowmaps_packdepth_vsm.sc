$input v_position

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	float depth = v_position.z/v_position.w * 0.5 + 0.5;
	float depthSq = depth*depth;

	gl_FragColor = vec4(packHalfFloat(depth), packHalfFloat(depthSq));
}
