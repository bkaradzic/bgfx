$input v_color0, v_texcoord0

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bgfx_shader.sh>

SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 rgba = texture2D(s_texColor, v_texcoord0.xy).xxxx;

	rgba.xyz = rgba.xyz * v_color0.xyz * rgba.w * v_color0.w;
	rgba.w   = rgba.w * v_color0.w * (1.0f - v_texcoord0.z);
	gl_FragColor = rgba;
}
