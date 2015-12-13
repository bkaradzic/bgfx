$input v_position, v_texcoord0

/*
 * Copyright 2015 Andrew Mac. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.sh"

void main()
{
	gl_FragColor = vec4(v_texcoord0.x, v_texcoord0.y, v_position.y / 50.0, 1.0);
}
