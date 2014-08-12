$input v_texcoord0

/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx_shader.sh>

uniform float u_imageLod;
uniform vec4 u_swizzle;
SAMPLER2D(s_texColor, 0);

void main()
{
	float color = dot(texture2DLod(s_texColor, v_texcoord0, u_imageLod), u_swizzle);
	gl_FragColor = vec4(vec3_splat(color), 1.0);
}
