$input v_texcoord0

/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.sh"
#include <bgfx_compute.sh>

FRAMEBUFFER_IMAGE2D_RW(s_light, rgba8, 0);

void main()
{
    ivec2 coord = ivec2(gl_FragCoord.xy);
    imageStore(s_light, coord, vec4(0.0, 0.0, 0.0, 0.0));
}
