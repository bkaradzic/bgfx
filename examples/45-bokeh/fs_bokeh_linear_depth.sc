$input v_texcoord0

/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "../common/common.sh"
#include "parameters.sh"

SAMPLER2D(s_depth, 0);

// from assao sample, cs_assao_prepare_depths.sc
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


void main()
{
	vec2 texCoord = v_texcoord0;
	float depth = texture2D(s_depth, texCoord).x;
	float linearDepth = ScreenSpaceToViewSpaceDepth(depth);
	gl_FragColor = vec4_splat(linearDepth);
}
