$input a_position, a_normal
$output v_color0, v_position

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
	vec3 normal = a_normal.xyz*2.0 - 1.0;
	v_color0 = vec4(abs(normal), 1.0);
	v_position = a_position;
}
