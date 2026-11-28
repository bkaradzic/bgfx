$input v_color0, v_position

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform vec4 u_clipPlanes[6];
uniform vec4 u_cameraPos;

void main()
{
	// During the stencil passes, only clip against planes facing the camera.
	// The normal mesh pass still clips against every plane.
	for (int ii = 0; ii < 6; ++ii)
	{
		float cameraPlaneDistance = dot(u_cameraPos.xyz, u_clipPlanes[ii].xyz) + u_clipPlanes[ii].w;
		float clipDistance = dot(v_position, u_clipPlanes[ii].xyz) + u_clipPlanes[ii].w;
		if (cameraPlaneDistance > 0.0 && clipDistance > 0.0)
		{
			discard;
		}
	}

	// Stencil values are written by the fixed-function stencil state; the
	// fragment shader only needs to keep the fragment alive.
	gl_FragColor = v_color0;
}
