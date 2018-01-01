/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_shader.sh"

uniform vec4 bgfx_clear_color[8];

void main()
{
	gl_FragColor = bgfx_clear_color[0];
}
