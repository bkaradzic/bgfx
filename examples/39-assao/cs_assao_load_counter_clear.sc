/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

BUFFER_WO(s_loadCounter, uint, 0);

NUM_THREADS(1, 1, 1)
void main() 
{
	s_loadCounter[0] = 0;
}
