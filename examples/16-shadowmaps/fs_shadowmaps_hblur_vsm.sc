$input v_texcoord0, v_texcoord1, v_texcoord2, v_texcoord3, v_texcoord4

/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.sh"
SAMPLER2D(s_shadowMap0, 4);

void main()
{
	gl_FragColor = blur9VSM(s_shadowMap0
						, v_texcoord0
						, v_texcoord1
						, v_texcoord2
						, v_texcoord3
						, v_texcoord4
						);
}
