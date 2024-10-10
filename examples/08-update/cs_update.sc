/*
 * Copyright 2014 Stanlo Slasinski. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh"

IMAGE2D_ARRAY_WO(s_texColor, rgba8, 0);
uniform vec4 u_time;

NUM_THREADS(16, 16, 1)
void main()
{
	vec3 colors[] =
	{
		vec3(1.0, 0.0, 0.0),
		vec3(1.0, 1.0, 0.0),
		vec3(1.0, 0.0, 1.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 1.0, 1.0),
		vec3(0.0, 0.0, 1.0),
	};

	for (int face = 0; face < 6; face++)
	{
		vec3 color = colors[face]*0.75 + sin(u_time.x*4.0)*0.25;
		ivec3 dest = ivec3(gl_GlobalInvocationID.xy, face);
		imageStore(s_texColor, dest, vec4(color, 1.0) );
	}
}
