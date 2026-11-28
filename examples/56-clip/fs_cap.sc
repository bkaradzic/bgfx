$input v_color0, v_position

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform vec4 u_clipPlanes[6];
uniform vec4 u_capIndex;

void main()
{
	// Keep this cap inside the retained side of every other clipping plane.
	for (int ii = 0; ii < 6; ++ii)
	{
		if (float(ii) != u_capIndex.x)
		{
			float otherPlaneDistance = dot(v_position, u_clipPlanes[ii].xyz) + u_clipPlanes[ii].w;
			if (otherPlaneDistance > 0.0)
			{
				discard;
			}
		}
	}

	gl_FragColor = v_color0;
}
