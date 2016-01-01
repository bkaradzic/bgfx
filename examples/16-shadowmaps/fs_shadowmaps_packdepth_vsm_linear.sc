$input v_depth

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	float depth = v_depth;
	float depthSq = depth*depth;

	//TODO: try this.
	//vec2 dxy = vec2(dFdx(depth), dFdy(depth));
	//depthSq += 0.25*dot(dxy, dxy);

	gl_FragColor = vec4(packHalfFloat(depth), packHalfFloat(depthSq));
}
