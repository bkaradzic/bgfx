$input v_color0, v_position

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

uniform vec4 u_clipPlane0;
uniform vec4 u_clipPlane1;
uniform vec4 u_cameraPos;

void main()
{
	// During the stencil passes, only clip against planes facing the camera.
	// The normal mesh pass still clips against every plane.
	float cameraPlaneDistance0 = dot(u_cameraPos.xyz, u_clipPlane0.xyz) + u_clipPlane0.w;
	float clipDistance0 = dot(v_position, u_clipPlane0.xyz) + u_clipPlane0.w;
	if (cameraPlaneDistance0 > 0.0 && clipDistance0 > 0.0)
	{
		discard;
	}

	float cameraPlaneDistance1 = dot(u_cameraPos.xyz, u_clipPlane1.xyz) + u_clipPlane1.w;
	float clipDistance1 = dot(v_position, u_clipPlane1.xyz) + u_clipPlane1.w;
	if (cameraPlaneDistance1 > 0.0 && clipDistance1 > 0.0)
	{
		discard;
	}

	// Stencil values are written by the fixed-function stencil state; the
	// fragment shader only needs to keep the fragment alive.
	gl_FragColor = v_color0;
}
