/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

IMAGE2D_WR(s_target, r8, 0);
SAMPLER2DARRAY(s_finalSSAO,	1);

// edge-ignorant blur & apply (for the lowest quality level 0)
NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy) + uvec2(u_rect.xy);
	if (all(lessThan(dtID.xy, u_rect.zw) ) )
	{
		vec2 inUV = (dtID.xy+vec2(0.5,0.5)) * u_viewportPixelSize;
		float a = texture2DArrayLod(s_finalSSAO, vec3( inUV.xy, 0 ), 0.0 ).x;
		float b = texture2DArrayLod(s_finalSSAO, vec3( inUV.xy, 1 ), 0.0 ).x;
		float c = texture2DArrayLod(s_finalSSAO, vec3( inUV.xy, 2 ), 0.0 ).x;
		float d = texture2DArrayLod(s_finalSSAO, vec3( inUV.xy, 3 ), 0.0 ).x;
		float avg = (a+b+c+d) * 0.25;
		avg = pow(avg,1.0/2.2);
		imageStore(s_target, ivec2(dtID.xy), avg.xxxx);
	}
}

