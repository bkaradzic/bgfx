/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

SAMPLER2D(s_depthSource, 0);

IMAGE2D_WR(s_target0, r16f, 1);
IMAGE2D_WR(s_target1, r16f, 2);
IMAGE2D_WR(s_normalsOutputUAV, rgba8, 5);

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

vec3 NDCToViewspace( vec2 pos, float viewspaceDepth )
{
    vec3 ret;

    ret.xy = (u_ndcToViewMul * pos.xy + u_ndcToViewAdd) * viewspaceDepth;
    ret.z = viewspaceDepth;

    return ret;
}

vec4 CalculateEdges( const float centerZ, const float leftZ, const float rightZ, const float topZ, const float bottomZ )
{
    // slope-sensitive depth-based edge detection
    vec4 edgesLRTB = vec4( leftZ, rightZ, topZ, bottomZ ) - centerZ;
    vec4 edgesLRTBSlopeAdjusted = edgesLRTB + edgesLRTB.yxwz;
    edgesLRTB = min( abs( edgesLRTB ), abs( edgesLRTBSlopeAdjusted ) );
    return saturate( ( 1.3 - edgesLRTB / (centerZ * 0.040) ) );

    // cheaper version but has artifacts
    // edgesLRTB = abs( vec4( leftZ, rightZ, topZ, bottomZ ) - centerZ; );
    // return saturate( ( 1.3 - edgesLRTB / (pixZ * 0.06 + 0.1) ) );
}


vec3 CalculateNormal( const vec4 edgesLRTB, vec3 pixCenterPos, vec3 pixLPos, vec3 pixRPos, vec3 pixTPos, vec3 pixBPos )
{
    // Get this pixel's viewspace normal
    vec4 acceptedNormals  = vec4( edgesLRTB.x*edgesLRTB.z, edgesLRTB.z*edgesLRTB.y, edgesLRTB.y*edgesLRTB.w, edgesLRTB.w*edgesLRTB.x );

    pixLPos = normalize(pixLPos - pixCenterPos);
    pixRPos = normalize(pixRPos - pixCenterPos);
    pixTPos = normalize(pixTPos - pixCenterPos);
    pixBPos = normalize(pixBPos - pixCenterPos);

    vec3 pixelNormal = vec3( 0, 0, -0.0005 );
    pixelNormal += ( acceptedNormals.x ) * cross( pixLPos, pixTPos );
    pixelNormal += ( acceptedNormals.y ) * cross( pixTPos, pixRPos );
    pixelNormal += ( acceptedNormals.z ) * cross( pixRPos, pixBPos );
    pixelNormal += ( acceptedNormals.w ) * cross( pixBPos, pixLPos );
    pixelNormal = normalize( pixelNormal );
    
    return pixelNormal;
}

NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy);

	uvec2 dim = imageSize(s_target0).xy;
	if (all(lessThan(dtID.xy, dim) ) )
	{
		ivec2 baseCoords = ivec2(dtID.xy) * 2;
#if BGFX_SHADER_LANGUAGE_GLSL
		vec2 upperLeftUV = (vec2(dtID.xy) + vec2(0.25,0.75)) * u_viewport2xPixelSize;
#else
		vec2 upperLeftUV = (vec2(dtID.xy) + vec2(0.25,0.25)) * u_viewport2xPixelSize;
#endif

		ivec2 baseCoord = ivec2(dtID.xy) * 2;
#if BGFX_SHADER_LANGUAGE_GLSL
		float z0 = ScreenSpaceToViewSpaceDepth( texelFetchOffset(s_depthSource, baseCoord, 0, ivec2( 0, 1 ) ).x );
		float z1 = ScreenSpaceToViewSpaceDepth( texelFetchOffset(s_depthSource, baseCoord, 0, ivec2( 1, 1 ) ).x );
		float z2 = ScreenSpaceToViewSpaceDepth( texelFetchOffset(s_depthSource, baseCoord, 0, ivec2( 0, 0 ) ).x );
		float z3 = ScreenSpaceToViewSpaceDepth( texelFetchOffset(s_depthSource, baseCoord, 0, ivec2( 1, 0 ) ).x );
#else
		float z0 = ScreenSpaceToViewSpaceDepth( texelFetchOffset(s_depthSource, baseCoord, 0, ivec2( 0, 0 ) ).x );
		float z1 = ScreenSpaceToViewSpaceDepth( texelFetchOffset(s_depthSource, baseCoord, 0, ivec2( 1, 0 ) ).x );
		float z2 = ScreenSpaceToViewSpaceDepth( texelFetchOffset(s_depthSource, baseCoord, 0, ivec2( 0, 1 ) ).x );
		float z3 = ScreenSpaceToViewSpaceDepth( texelFetchOffset(s_depthSource, baseCoord, 0, ivec2( 1, 1 ) ).x );
#endif

		imageStore(s_target0, ivec2(dtID.xy), z0.xxxx );
		imageStore(s_target1, ivec2(dtID.xy), z3.xxxx );

		float pixZs[4][4];

		// middle 4
		pixZs[1][1] = z0;
		pixZs[2][1] = z1;
		pixZs[1][2] = z2;
		pixZs[2][2] = z3;
#if BGFX_SHADER_LANGUAGE_GLSL
		// left 2
		pixZs[0][1] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2( -1, 0 ) ).x ); 
		pixZs[0][2] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2( -1, -1 ) ).x ); 

		// right 2
		pixZs[3][1] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  2, 0 ) ).x ); 
		pixZs[3][2] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  2, -1 ) ).x ); 

		// top 2
		pixZs[1][0] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  0, 1 ) ).x );
		pixZs[2][0] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  1, 1 ) ).x );

		// bottom 2
		pixZs[1][3] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  0,  -2 ) ).x );
		pixZs[2][3] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  1,  -2 ) ).x );
#else
		// left 2
		pixZs[0][1] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2( -1, 0 ) ).x ); 
		pixZs[0][2] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2( -1, 1 ) ).x ); 

		// right 2
		pixZs[3][1] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  2, 0 ) ).x ); 
		pixZs[3][2] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  2, 1 ) ).x ); 

		// top 2
		pixZs[1][0] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  0, -1 ) ).x );
		pixZs[2][0] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  1, -1 ) ).x );

		// bottom 2
		pixZs[1][3] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  0,  2 ) ).x );
		pixZs[2][3] = ScreenSpaceToViewSpaceDepth(  texture2DLodOffset(s_depthSource, upperLeftUV, 0.0, ivec2(  1,  2 ) ).x );
#endif

		vec4 edges0 = CalculateEdges( pixZs[1][1], pixZs[0][1], pixZs[2][1], pixZs[1][0], pixZs[1][2] );
		vec4 edges1 = CalculateEdges( pixZs[2][1], pixZs[1][1], pixZs[3][1], pixZs[2][0], pixZs[2][2] );
		vec4 edges2 = CalculateEdges( pixZs[1][2], pixZs[0][2], pixZs[2][2], pixZs[1][1], pixZs[1][3] );
		vec4 edges3 = CalculateEdges( pixZs[2][2], pixZs[1][2], pixZs[3][2], pixZs[2][1], pixZs[2][3] );

		vec2 viewportPixelSize = u_viewportPixelSize;
#if BGFX_SHADER_LANGUAGE_GLSL
		viewportPixelSize.y = -viewportPixelSize.y;
#endif

		vec3 pixPos[4][4];
		// there is probably a way to optimize the math below; however no approximation will work, has to be precise.

		// middle 4
		pixPos[1][1] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( 0.0,  0.0 ), pixZs[1][1] );
		pixPos[2][1] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( 1.0,  0.0 ), pixZs[2][1] );
		pixPos[1][2] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( 0.0,  1.0 ), pixZs[1][2] );
		pixPos[2][2] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( 1.0,  1.0 ), pixZs[2][2] );

		// left 2
		pixPos[0][1] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( -1.0,  0.0), pixZs[0][1] );
		//pixPos[0][2] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( -1.0,  1.0), pixZs[0][2] );
		// right 2                                                                                     
		//pixPos[3][1] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2(  2.0,  0.0), pixZs[3][1] );
		pixPos[3][2] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2(  2.0,  1.0), pixZs[3][2] );
		// top 2                                                                                       
		pixPos[1][0] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( 0.0, -1.0 ), pixZs[1][0] );
		//pixPos[2][0] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( 1.0, -1.0 ), pixZs[2][0] );
		// bottom 2                                                                                    
		//pixPos[1][3] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( 0.0,  2.0 ), pixZs[1][3] );
		pixPos[2][3] = NDCToViewspace( upperLeftUV + viewportPixelSize * vec2( 1.0,  2.0 ), pixZs[2][3] );

		vec3 norm0 = CalculateNormal( edges0, pixPos[1][1], pixPos[0][1], pixPos[2][1], pixPos[1][0], pixPos[1][2] );
		vec3 norm3 = CalculateNormal( edges3, pixPos[2][2], pixPos[1][2], pixPos[3][2], pixPos[2][1], pixPos[2][3] );

#if BGFX_SHADER_LANGUAGE_GLSL
		imageStore(s_normalsOutputUAV, baseCoords + ivec2( 0, 1 ), vec4( norm0 * 0.5 + 0.5, 0.0 ));
		imageStore(s_normalsOutputUAV, baseCoords + ivec2( 1, 0 ), vec4( norm3 * 0.5 + 0.5, 0.0 ));
#else
		imageStore(s_normalsOutputUAV, baseCoords + ivec2( 0, 0 ), vec4( norm0 * 0.5 + 0.5, 0.0 ));
		imageStore(s_normalsOutputUAV, baseCoords + ivec2( 1, 1 ), vec4( norm3 * 0.5 + 0.5, 0.0 ));
#endif
	}
}
