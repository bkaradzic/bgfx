/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

IMAGE2D_WR(s_target, r8, 0);
SAMPLER2D(s_importanceMap, 1);
BUFFER_RW(s_loadCounter, uint, 2);

CONST(float cSmoothenImportance) = 1.0;

// Shaders below only needed for adaptive quality level
NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy);

	uvec2 dim = imageSize(s_target).xy;
	if (all(lessThan(dtID.xy, dim) ) )
	{
		vec2 inUV = (dtID.xy+vec2(0.5,0.5)) * u_quarterResPixelSize;

		float centre = texture2DLod(s_importanceMap, inUV, 0.0 ).x;
		//return centre;

		vec2 halfPixel = u_quarterResPixelSize * 0.5f;

		vec4 vals;
		vals.x = texture2DLod(s_importanceMap, inUV + vec2( -halfPixel.x, -halfPixel.y * 3 ), 0.0 ).x;
		vals.y = texture2DLod(s_importanceMap, inUV + vec2( +halfPixel.x * 3, -halfPixel.y ), 0.0 ).x;
		vals.z = texture2DLod(s_importanceMap, inUV + vec2( +halfPixel.x, +halfPixel.y * 3 ), 0.0 ).x;
		vals.w = texture2DLod(s_importanceMap, inUV + vec2( -halfPixel.x * 3, +halfPixel.y ), 0.0 ).x;

		float avgVal = dot( vals, vec4( 0.25, 0.25, 0.25, 0.25 ) );
		vals.xy = max( vals.xy, vals.zw );
		float maxVal = max( centre, max( vals.x, vals.y ) );

		float retVal = mix( maxVal, avgVal, cSmoothenImportance );

		// sum the average; to avoid overflowing we assume max AO resolution is not bigger than 16384x16384; so quarter res (used here) will be 4096x4096, which leaves us with 8 bits per pixel 
		uint sum = uint(saturate(retVal) * 255.0 + 0.5);
    
		// save every 9th to avoid InterlockedAdd congestion - since we're blurring, this is good enough; compensated by multiplying LoadCounterAvgDiv by 9
#if BGFX_SHADER_LANGUAGE_GLSL 
		if( ((dtID.x % 3) + ((dim.y-1-dtID.y) % 3)) == 0  )
#else
		if( ((dtID.x % 3) + (dtID.y % 3)) == 0  )
#endif
			atomicAdd(s_loadCounter[0], sum );
		imageStore(s_target, ivec2(dtID.xy), retVal.xxxx);
	}
}
