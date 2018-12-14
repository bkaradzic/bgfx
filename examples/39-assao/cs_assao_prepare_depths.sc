/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

SAMPLER2D(s_depthSource, 0);

IMAGE2D_WR(s_target0, r16f, 1); 
IMAGE2D_WR(s_target1, r16f, 2);
IMAGE2D_WR(s_target2, r16f, 3);
IMAGE2D_WR(s_target3, r16f, 4);

float ScreenSpaceToViewSpaceDepth( float screenDepth )
{
    float depthLinearizeMul = u_depthUnpackConsts.x;
    float depthLinearizeAdd = u_depthUnpackConsts.y;

    // Optimised version of "-cameraClipNear / (cameraClipFar - projDepth * (cameraClipFar - cameraClipNear)) * cameraClipFar"

    // Set your depthLinearizeMul and depthLinearizeAdd to:
    // depthLinearizeMul = ( cameraClipFar * cameraClipNear) / ( cameraClipFar - cameraClipNear );
    // depthLinearizeAdd = cameraClipFar / ( cameraClipFar - cameraClipNear );

    return depthLinearizeMul / ( depthLinearizeAdd - screenDepth );
}


NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy);

	uvec2 dim = imageSize(s_target0).xy;
	if (all(lessThan(dtID.xy, dim) ) )
	{ 
		ivec2 baseCoord = ivec2(dtID.xy) * 2;
#if BGFX_SHADER_LANGUAGE_GLSL 
		float a = texelFetch(s_depthSource, baseCoord + ivec2( 0, 1 ), 0).x;
		float b = texelFetch(s_depthSource, baseCoord + ivec2( 1, 1 ), 0).x;
		float c = texelFetch(s_depthSource, baseCoord + ivec2( 0, 0 ), 0).x;
		float d = texelFetch(s_depthSource, baseCoord + ivec2( 1, 0 ), 0).x;
#else
		float a = texelFetch(s_depthSource, baseCoord + ivec2( 0, 0 ), 0).x;
		float b = texelFetch(s_depthSource, baseCoord + ivec2( 1, 0 ), 0).x;
		float c = texelFetch(s_depthSource, baseCoord + ivec2( 0, 1 ), 0).x;
		float d = texelFetch(s_depthSource, baseCoord + ivec2( 1, 1 ), 0).x;
#endif

		imageStore(s_target0, ivec2(dtID.xy), ScreenSpaceToViewSpaceDepth( a ).xxxx);
		imageStore(s_target1, ivec2(dtID.xy), ScreenSpaceToViewSpaceDepth( b ).xxxx);
		imageStore(s_target2, ivec2(dtID.xy), ScreenSpaceToViewSpaceDepth( c ).xxxx);
		imageStore(s_target3, ivec2(dtID.xy), ScreenSpaceToViewSpaceDepth( d ).xxxx);
	}
}

