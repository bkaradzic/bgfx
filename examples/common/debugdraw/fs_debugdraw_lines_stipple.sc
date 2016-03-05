$input v_color0, v_stipple

/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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
