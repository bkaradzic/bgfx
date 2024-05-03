$input v_texcoord0

/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLERCUBE(s_texCube, 0);

void main()
{
	gl_FragColor = textureCube(s_texCube, v_texcoord0);
}
