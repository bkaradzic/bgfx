/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh"

SAMPLER2D(s_texOcclusionDepth, 0);

BUFFER_RO(instanceDataIn, vec4, 1);
BUFFER_RW(drawcallInstanceCount, uint, 2);
BUFFER_WR(instancePredicates, bool, 3);

uniform vec4 u_inputRTSize;
uniform vec4 u_cullingConfig;

NUM_THREADS(64, 1, 1)
void main()
{
	bool predicate = false;

	//make sure that we not processing more instances than available
	if (gl_GlobalInvocationID.x < uint(u_cullingConfig.x) )
	{
		//get the bounding box for this instance
		vec4 bboxMin = instanceDataIn[2 * gl_GlobalInvocationID.x] ;
		vec3 bboxMax = instanceDataIn[2 * gl_GlobalInvocationID.x + 1].xyz;

		int drawcallID = int(bboxMin.w);

		//Adapted from http://blog.selfshadow.com/publications/practical-visibility/
		vec3 bboxSize = bboxMax.xyz - bboxMin.xyz;

		vec3 boxCorners[] = {
			bboxMin.xyz,
			bboxMin.xyz + vec3(bboxSize.x,0,0),
			bboxMin.xyz + vec3(0, bboxSize.y,0),
			bboxMin.xyz + vec3(0, 0, bboxSize.z),
			bboxMin.xyz + vec3(bboxSize.xy,0),
			bboxMin.xyz + vec3(0, bboxSize.yz),
			bboxMin.xyz + vec3(bboxSize.x, 0, bboxSize.z),
			bboxMin.xyz + bboxSize.xyz
		};
		float minZ = 1.0;
		vec2 minXY = vec2(1.0, 1.0);
		vec2 maxXY = vec2(0.0, 0.0);

		UNROLL
		for (int i = 0; i < 8; i++)
		{
			//transform World space aaBox to NDC
			vec4 clipPos = mul( u_viewProj, vec4(boxCorners[i], 1) );

#if BGFX_SHADER_LANGUAGE_GLSL 
			clipPos.z = 0.5 * ( clipPos.z + clipPos.w );
#endif
			clipPos.z = max(clipPos.z, 0);

			clipPos.xyz = clipPos.xyz / clipPos.w;

			clipPos.xy = clamp(clipPos.xy, -1, 1);
			clipPos.xy = clipPos.xy * vec2(0.5, -0.5) + vec2(0.5, 0.5);

			minXY = min(clipPos.xy, minXY);
			maxXY = max(clipPos.xy, maxXY);

			minZ = saturate(min(minZ, clipPos.z));
		}

		vec4 boxUVs = vec4(minXY, maxXY);

		// Calculate hi-Z buffer mip
		ivec2 size = ivec2( (maxXY - minXY) * u_inputRTSize.xy);
		float mip = ceil(log2(max(size.x, size.y)));

		mip = clamp(mip, 0, u_cullingConfig.z);

		// Texel footprint for the lower (finer-grained) level
		float level_lower = max(mip - 1, 0);
		vec2 scale = vec2_splat(exp2(-level_lower) );
		vec2 a = floor(boxUVs.xy*scale);
		vec2 b = ceil(boxUVs.zw*scale);
		vec2 dims = b - a;

		// Use the lower level if we only touch <= 2 texels in both dimensions
		if (dims.x <= 2 && dims.y <= 2)
			mip = level_lower;

#if BGFX_SHADER_LANGUAGE_GLSL
		boxUVs.y = 1.0 - boxUVs.y;
		boxUVs.w = 1.0 - boxUVs.w;
#endif
		//load depths from high z buffer
		vec4 depth =
		{
			texture2DLod(s_texOcclusionDepth, boxUVs.xy, mip).x,
			texture2DLod(s_texOcclusionDepth, boxUVs.zy, mip).x,
			texture2DLod(s_texOcclusionDepth, boxUVs.xw, mip).x,
			texture2DLod(s_texOcclusionDepth, boxUVs.zw, mip).x,
		};

		//find the max depth
		float maxDepth = max( max(depth.x, depth.y), max(depth.z, depth.w) );

		if ( minZ <= maxDepth )
		{
			predicate = true;

			//increase instance count for this particular prop type
			atomicAdd(drawcallInstanceCount[ drawcallID ], 1);
		}
	}

	instancePredicates[gl_GlobalInvocationID.x] = predicate;
}
