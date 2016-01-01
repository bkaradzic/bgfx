$input v_position, v_texcoord0

/*
 * Copyright 2015 Andrew Mac. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	gl_FragColor = vec4(v_texcoord0.x, v_texcoord0.y, v_position.y / 50.0, 1.0);
}
