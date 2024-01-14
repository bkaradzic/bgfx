$input v_texcoord0, v_color0

/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.sh"

SAMPLER2DARRAY(s_texColor, 0);

void main()
{
	vec4 color = texture2DArrayLod(s_texColor, vec3(v_texcoord0.xy, u_textureLayer), u_textureLod);
	gl_FragColor = toEv(color * v_color0);
}
