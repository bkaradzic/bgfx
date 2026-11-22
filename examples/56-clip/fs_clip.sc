$input v_color0, v_position

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform vec4 u_clipPlane;

void main()
{
	// The plane equation
	float clipDistance = dot(v_position, u_clipPlane.xyz) + u_clipPlane.w;

	if (clipDistance > 0.0)
	{
		discard;
	}

	gl_FragColor = v_color0;
}
