$input v_texcoord0, v_color0

/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx_shader.sh>

SAMPLER2D(u_texColor, 0);

void main()
{
	float alpha = texture2D(u_texColor, v_texcoord0).x;
	gl_FragColor = vec4(v_color0.xyz, v_color0.w * alpha);
}
