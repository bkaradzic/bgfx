/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

UIMAGE2D_WR(s_loadCounterOutputUAV, r32ui, 0);

NUM_THREADS(1, 1, 1)
void main() 
{
	imageStore(s_loadCounterOutputUAV, ivec2(0, 0), uvec4(0,0,0,0));
}
