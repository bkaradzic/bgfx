$input v_texcoord0

/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	gl_FragColor = texture2D(s_texColor, v_texcoord0);
}
