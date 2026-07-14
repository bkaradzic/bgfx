$input v_texcoord0

/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx_shader.sh>

SAMPLER2DARRAY(s_texColor, 0);

uniform vec4 u_eyeParams; // x = array layer to sample

void main()
{
	gl_FragColor = texture2DArray(s_texColor, vec3(v_texcoord0, u_eyeParams.x) );
}
