$input v_texcoord0, v_color0

/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 color = texture2DLod(s_texColor, v_texcoord0.xy, u_textureLod);
	gl_FragColor = toEv(color * v_color0);
}
