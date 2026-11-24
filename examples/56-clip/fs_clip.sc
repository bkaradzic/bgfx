$input v_color0, v_position

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform vec4 u_clipPlane0;
uniform vec4 u_clipPlane1;

void main()
{
	// The normal mesh pass clips against every active plane.
	float clipDistance0 = dot(v_position, u_clipPlane0.xyz) + u_clipPlane0.w;
	if (clipDistance0 > 0.0)
	{
		discard;
	}

	float clipDistance1 = dot(v_position, u_clipPlane1.xyz) + u_clipPlane1.w;
	if (clipDistance1 > 0.0)
	{
		discard;
	}

	gl_FragColor = v_color0;
}
