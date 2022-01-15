/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh"

SAMPLER2D(s_texOcclusionDepth, 0);
IMAGE2D_WR(s_texOcclusionDepthOut, r32f, 1);

uniform vec4 u_inputRTSize;

NUM_THREADS(16, 16, 1)
void main()
{
	// this shader can be used to both copy a mip over to the output and downscale it.

	ivec2 coord = ivec2(gl_GlobalInvocationID.xy);

	if (all(lessThan(coord.xy, u_inputRTSize.xy) ) )
	{
		float maxDepth = texelFetch(s_texOcclusionDepth, coord.xy, 0).x;

		imageStore(s_texOcclusionDepthOut, coord, vec4(maxDepth,0,0,1) );
	}
}
