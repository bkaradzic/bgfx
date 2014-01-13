$input v_position

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

void main()
{
	float depth = v_position.z/v_position.w * 0.5 + 0.5;
	float depthSq = depth*depth;

	//TODO: try this.
	//vec2 dxy = vec2(dFdx(depth), dFdy(depth));
	//depthSq += 0.25*dot(dxy, dxy);

	gl_FragColor = vec4(packHalfFloat(depth), packHalfFloat(depthSq));
}
