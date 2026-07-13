$input a_position, a_color0
$output v_color0, v_eye

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx_shader.sh>

uniform vec4 u_eyeParams; // x = eye separation, y = eye index

void main()
{
	// Non-layered path: the eye is selected by a uniform and rendered into a
	// single layer of the array bound as the framebuffer attachment.
	float eyeIndex = u_eyeParams.y;

	vec4 pos = mul(u_modelViewProj, vec4(a_position, 1.0) );
	pos.x += (eyeIndex * 2.0 - 1.0) * u_eyeParams.x * pos.w;
	gl_Position = pos;

	v_color0 = a_color0;
	v_eye = eyeIndex;
}
