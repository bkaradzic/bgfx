$input v_texcoord0, v_color0

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

SAMPLER2D(s_texColor, 0);

void main()
{
	float alpha = texture2D(s_texColor, v_texcoord0).x;
	gl_FragColor = vec4(v_color0.xyz, v_color0.w * alpha);
}
