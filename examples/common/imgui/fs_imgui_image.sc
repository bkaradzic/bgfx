$input v_texcoord0

/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx_shader.sh>

uniform float u_imageLod;
SAMPLER2D(u_texColor, 0);

void main()
{
	vec4 color = texture2DLod(u_texColor, v_texcoord0, u_imageLod);
	gl_FragColor = vec4(color.xyz, 1.0);
}
