$input v_color0, v_stipple

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

void main()
{
	if (0.125 < mod(v_stipple, 0.25) )
	{
		discard;
	}

	gl_FragColor = v_color0;
}
