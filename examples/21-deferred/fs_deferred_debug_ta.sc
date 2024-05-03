$input v_texcoord0

/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "../common/common.sh"

SAMPLER2DARRAY(s_texColor, 0);

uniform vec4 u_layer;

void main()
{
	gl_FragColor = texture2DArray(s_texColor, vec3(v_texcoord0, u_layer.x) );
}
