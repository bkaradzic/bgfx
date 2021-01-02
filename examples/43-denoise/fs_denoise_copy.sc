$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "../common/common.sh"
#include "parameters.sh"

SAMPLER2D(s_color, 0);

void main()
{
	vec2 texCoord = v_texcoord0;
	vec4 color = texture2D(s_color, texCoord);
	gl_FragColor = color;
}
