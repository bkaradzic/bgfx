$input v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4

/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.sh"

SAMPLER2D(s_texColor, 0);

void main()
{
	gl_FragColor = blur9(s_texColor, v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4);
}
