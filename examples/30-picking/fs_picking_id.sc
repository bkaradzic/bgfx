$input v_pos, v_view, v_normal, v_color0

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform vec4 u_id;

void main()
{
	gl_FragColor.xyz = u_id.xyz; // This is dumb, should use u8 texture
	gl_FragColor.w = 1.0;
}
