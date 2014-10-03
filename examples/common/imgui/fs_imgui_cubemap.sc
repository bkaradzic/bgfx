$input v_normal

/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx_shader.sh>

uniform float u_imageLod;
SAMPLERCUBE(u_texColor, 0);

void main()
{
	gl_FragColor = textureCubeLod(u_texColor, v_normal, u_imageLod);
}
