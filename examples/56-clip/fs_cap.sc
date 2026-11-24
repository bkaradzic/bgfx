$input v_color0, v_position

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform vec4 u_clipPlane0;
uniform vec4 u_clipPlane1;
uniform vec4 u_capIndex;

void main()
{
	// A cap lies on its own plane, so do not test that plane again. Test the
	// other plane so the cap is limited to the intersection of both cuts.
	if (u_capIndex.x < 0.5)
	{
		float otherPlaneDistance = dot(v_position, u_clipPlane1.xyz) + u_clipPlane1.w;
		if (otherPlaneDistance > 0.0)
		{
			discard;
		}
	}
	else
	{
		float otherPlaneDistance = dot(v_position, u_clipPlane0.xyz) + u_clipPlane0.w;
		if (otherPlaneDistance > 0.0)
		{
			discard;
		}
	}

	gl_FragColor = v_color0;
}
