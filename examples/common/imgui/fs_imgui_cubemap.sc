$input v_normal

/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx_shader.sh>

SAMPLERCUBE(s_texColor, 0);

void main()
{
	gl_FragColor = textureCube(s_texColor, v_normal);
}
