$input a_position

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_shader.sh"

uniform vec4 bgfx_clear_depth;

void main()
{
	gl_Position = vec4(a_position.xy, bgfx_clear_depth.x, 1.0);
}
