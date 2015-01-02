$input v_texcoord0

/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

SAMPLERCUBE(u_texCube, 0);

void main()
{
	gl_FragColor = textureCube(u_texCube, v_texcoord0);
}
