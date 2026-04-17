$input v_texcoord0

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLER2D(s_texColor, 0);
uniform vec4 u_texMipLevel;

void main()
{
	gl_FragColor = texture2DLod(s_texColor, v_texcoord0.xy*0.5+0.5, u_texMipLevel.x);
}
