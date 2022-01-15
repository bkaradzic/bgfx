$input v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4

/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	gl_FragColor = blur9(s_texColor, v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4);
}
