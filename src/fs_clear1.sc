/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_shader.sh"

uniform vec4 bgfx_clear_color[8];

void main()
{
	gl_FragData[0] = bgfx_clear_color[0];
	gl_FragData[1] = bgfx_clear_color[1];
}
