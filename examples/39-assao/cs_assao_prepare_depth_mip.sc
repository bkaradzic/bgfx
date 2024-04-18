/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

IMAGE2D_RO(s_viewspaceDepthSource0, r16f, 0); 
IMAGE2D_RO(s_viewspaceDepthSource1, r16f, 1);
IMAGE2D_RO(s_viewspaceDepthSource2, r16f, 2);
IMAGE2D_RO(s_viewspaceDepthSource3, r16f, 3);

IMAGE2D_WO(s_target0, r16f, 4);
IMAGE2D_WO(s_target1, r16f, 5);
IMAGE2D_WO(s_target2, r16f, 6);
IMAGE2D_WO(s_target3, r16f, 7);

// calculate effect radius and fit our screen sampling pattern inside it
void CalculateRadiusParameters( const float pixCenterLength, const vec2 pixelDirRBViewspaceSizeAtCenterZ, out float pixLookupRadiusMod, out float effectRadius, out float falloffCalcMulSq )
{
    effectRadius = u_effectRadius;

    // leaving this out for performance reasons: use something similar if radius needs to scale based on distance
    //effectRadius *= pow( pixCenterLength, u_radiusDistanceScalingFunctionPow);

    // when too close, on-screen sampling disk will grow beyond screen size; limit this to avoid closeup temporal artifacts
    const float tooCloseLimitMod = saturate( pixCenterLength * u_effectSamplingRadiusNearLimitRec ) * 0.8 + 0.2;
    
    effectRadius *= tooCloseLimitMod;

    // 0.85 is to reduce the radius to allow for more samples on a slope to still stay within influence
    pixLookupRadiusMod = (0.85 * effectRadius) / pixelDirRBViewspaceSizeAtCenterZ.x;

    // used to calculate falloff (both for AO samples and per-sample weights)
    falloffCalcMulSq= -1.0f / (effectRadius*effectRadius);
}

NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy);

	uvec2 dim = uvec2(u_rect.zw);
	if (all(lessThan(dtID.xy, dim) ) )
	{ 
		ivec2 baseCoords = ivec2(dtID.xy) * 2;

		vec4 depthsArr[4];
		float depthsOutArr[4];

		// how to Gather a specific mip level?
		depthsArr[0].x = imageLoad(s_viewspaceDepthSource0, baseCoords + ivec2( 0, 0 )).x ;
		depthsArr[0].y = imageLoad(s_viewspaceDepthSource0, baseCoords + ivec2( 1, 0 )).x ;
		depthsArr[0].z = imageLoad(s_viewspaceDepthSource0, baseCoords + ivec2( 0, 1 )).x ;
		depthsArr[0].w = imageLoad(s_viewspaceDepthSource0, baseCoords + ivec2( 1, 1 )).x ;
		depthsArr[1].x = imageLoad(s_viewspaceDepthSource1, baseCoords + ivec2( 0, 0 )).x;
		depthsArr[1].y = imageLoad(s_viewspaceDepthSource1, baseCoords + ivec2( 1, 0 )).x;
		depthsArr[1].z = imageLoad(s_viewspaceDepthSource1, baseCoords + ivec2( 0, 1 )).x;
		depthsArr[1].w = imageLoad(s_viewspaceDepthSource1, baseCoords + ivec2( 1, 1 )).x;
		depthsArr[2].x = imageLoad(s_viewspaceDepthSource2, baseCoords + ivec2( 0, 0 )).x;
		depthsArr[2].y = imageLoad(s_viewspaceDepthSource2, baseCoords + ivec2( 1, 0 )).x;
		depthsArr[2].z = imageLoad(s_viewspaceDepthSource2, baseCoords + ivec2( 0, 1 )).x;
		depthsArr[2].w = imageLoad(s_viewspaceDepthSource2, baseCoords + ivec2( 1, 1 )).x;
		depthsArr[3].x = imageLoad(s_viewspaceDepthSource3, baseCoords + ivec2( 0, 0 )).x;
		depthsArr[3].y = imageLoad(s_viewspaceDepthSource3, baseCoords + ivec2( 1, 0 )).x;
		depthsArr[3].z = imageLoad(s_viewspaceDepthSource3, baseCoords + ivec2( 0, 1 )).x;
		depthsArr[3].w = imageLoad(s_viewspaceDepthSource3, baseCoords + ivec2( 1, 1 )).x;
		
	    const uvec2 SVPosui         = uvec2( dtID.xy );
		const uint pseudoRandomA    = (SVPosui.x ) + 2 * (SVPosui.y );

		float dummyUnused1;
		float dummyUnused2;
		float falloffCalcMulSq, falloffCalcAdd;
 
		UNROLL
		for( int i = 0; i < 4; i++ )
		{
			vec4 depths = depthsArr[i];
			float closest = min( min( depths.x, depths.y ), min( depths.z, depths.w ) );

			CalculateRadiusParameters( abs( closest ), vec2(1.0,1.0), dummyUnused1, dummyUnused2, falloffCalcMulSq );

			vec4 dists = depths - closest.xxxx;

			vec4 weights = saturate( dists * dists * falloffCalcMulSq + 1.0 );

			float smartAvg = dot( weights, depths ) / dot( weights, vec4( 1.0, 1.0, 1.0, 1.0 ) );

			const uint pseudoRandomIndex = ( pseudoRandomA + i ) % 4;

			//depthsOutArr[i] = closest;
			//depthsOutArr[i] = depths[ pseudoRandomIndex ];
			depthsOutArr[i] = smartAvg;
		}

		imageStore(s_target0, ivec2(dtID.xy), depthsOutArr[0].xxxx);
		imageStore(s_target1, ivec2(dtID.xy), depthsOutArr[1].xxxx);
		imageStore(s_target2, ivec2(dtID.xy), depthsOutArr[2].xxxx);
		imageStore(s_target3, ivec2(dtID.xy), depthsOutArr[3].xxxx);
	}
}
