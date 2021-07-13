$input v_texcoord0

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

BGFX_BEGIN_UNIFORM_BLOCK(UniformsMaterial)
uniform vec4 u_color;
BGFX_END_UNIFORM_BLOCK

SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 tcolor = toLinear(texture2D(s_texColor, v_texcoord0));

	if (tcolor.x < 0.1)
	{
		discard;
	}

	gl_FragColor = toGamma(tcolor + u_color);
}
