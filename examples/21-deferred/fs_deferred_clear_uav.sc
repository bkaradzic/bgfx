$input v_texcoord0

/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx_compute.sh>

IMAGE2D_RW(i_light, rgba8, 2);

void main()
{
	ivec2 coord = ivec2(gl_FragCoord.xy);
	imageStore(i_light, coord, vec4(0.0, 0.0, 0.0, 0.0) );
}
