/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh"

IMAGE2D_RO(s_texOcclusionDepthIn, r32f, 0);
IMAGE2D_WO(s_texOcclusionDepthOut, r32f, 1);

uniform vec4 u_inputRTSize;

NUM_THREADS(16, 16, 1)
void main()
{
	// this shader can be used to both copy a mip over to the output and downscale it.

	ivec2 coord = ivec2(gl_GlobalInvocationID.xy);

	if (all(lessThan(coord.xy, u_inputRTSize.xy) ) )
	{
		float maxDepth = 1.0;

		vec4 depths = vec4(
				imageLoad(s_texOcclusionDepthIn, ivec2(u_inputRTSize.zw * coord.xy                   ) ).x
			, imageLoad(s_texOcclusionDepthIn, ivec2(u_inputRTSize.zw * coord.xy + ivec2(1.0, 0.0) ) ).x
			, imageLoad(s_texOcclusionDepthIn, ivec2(u_inputRTSize.zw * coord.xy + ivec2(0.0, 1.0) ) ).x
			, imageLoad(s_texOcclusionDepthIn, ivec2(u_inputRTSize.zw * coord.xy + ivec2(1.0, 1.0) ) ).x
			);

		// find and return max depth
		maxDepth = max(
				max(depths.x, depths.y)
			, max(depths.z, depths.w)
			);

		imageStore(s_texOcclusionDepthOut, coord, vec4(maxDepth,0,0,1) );
	}
}
