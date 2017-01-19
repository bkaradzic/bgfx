/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_shader.sh"

uniform vec4 bgfx_clear_color[8];

void main()
{
	gl_FragData[0] = bgfx_clear_color[0];
	gl_FragData[1] = bgfx_clear_color[1];
	gl_FragData[2] = bgfx_clear_color[2];
	gl_FragData[3] = bgfx_clear_color[3];
	gl_FragData[4] = bgfx_clear_color[4];
	gl_FragData[5] = bgfx_clear_color[5];
	gl_FragData[6] = bgfx_clear_color[6];
	gl_FragData[7] = bgfx_clear_color[7];
}
