/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

IMAGE2D_WO(s_target, r8, 0);
SAMPLER2DARRAY(s_finalSSAO,  1); 

NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy);

	uvec2 dim = imageSize(s_target).xy;
	if (all(lessThan(dtID.xy, dim) ) )
	{
		uvec2 basePos = uvec2(dtID.xy) * 2;

		vec2 baseUV = (vec2(basePos) + vec2( 0.5, 0.5 ) ) * u_halfViewportPixelSize;
		vec2 gatherUV = (vec2(basePos) + vec2( 1.0, 1.0 ) ) * u_halfViewportPixelSize;

		float avg = 0.0;
		float minV = 1.0;
		float maxV = 0.0;
		UNROLL
		for( int i = 0; i < 4; i++ )
		{
			vec4 vals = textureGather(s_finalSSAO, vec3( gatherUV, i ), 0);

			// apply the same modifications that would have been applied in the main shader
			vals = u_effectShadowStrength * vals;

			vals = 1-vals;

			vals = pow( saturate( vals ), u_effectShadowPow.xxxx );

			avg += dot( vec4( vals.x, vals.y, vals.z, vals.w ), vec4( 1.0 / 16.0, 1.0 / 16.0, 1.0 / 16.0, 1.0 / 16.0 ) );

			maxV = max( maxV, max( max( vals.x, vals.y ), max( vals.z, vals.w ) ) );
			minV = min( minV, min( min( vals.x, vals.y ), min( vals.z, vals.w ) ) );
		}

		float minMaxDiff = maxV - minV;

		imageStore(s_target, ivec2(dtID.xy), pow( saturate( minMaxDiff * 2.0 ), 0.8 ).xxxx);
	}
}
