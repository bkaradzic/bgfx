$input v_k

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

BGFX_BEGIN_UNIFORM_BLOCK(UniformsMaterial)
uniform vec4 u_color;
BGFX_END_UNIFORM_BLOCK

void main()
{
	gl_FragColor.xyz = u_color.xyz;
	gl_FragColor.w = 0.98;
}
