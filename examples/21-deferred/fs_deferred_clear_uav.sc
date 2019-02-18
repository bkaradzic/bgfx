$input v_texcoord0

/*
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"
#include <bgfx_compute.sh>

IMAGE2D_RW(s_lights, rgba8, 1);

void main()
{
    ivec2 coord = ivec2(gl_FragCoord.xy);
    imageStore(s_lights, coord, vec4(0.0, 0.0, 0.0, 0.0));
}
