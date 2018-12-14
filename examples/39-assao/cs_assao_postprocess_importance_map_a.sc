/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

IMAGE2D_WR(s_target, r8, 0);
SAMPLER2D(s_importanceMap, 1);

// Shaders below only needed for adaptive quality level

CONST(float cSmoothenImportance) = 1.0;

NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy);

	uvec2 dim = imageSize(s_target).xy;
	if (all(lessThan(dtID.xy, dim) ) )
	{
		uvec2 pos = uvec2(dtID.xy);
		vec2 inUV = (dtID.xy+vec2(0.5,0.5)) * u_quarterResPixelSize;

		float centre = texture2DLod(s_importanceMap, inUV, 0.0 ).x;
		//return centre;

		vec2 halfPixel = u_quarterResPixelSize * 0.5f;

#if BGFX_SHADER_LANGUAGE_GLSL
		halfPixel.y = -halfPixel.y;
#endif 
		vec4 vals;
		vals.x = texture2DLod(s_importanceMap, inUV + vec2( -halfPixel.x * 3, -halfPixel.y ), 0.0 ).x;
		vals.y = texture2DLod(s_importanceMap, inUV + vec2( +halfPixel.x, -halfPixel.y * 3 ), 0.0 ).x;
		vals.z = texture2DLod(s_importanceMap, inUV + vec2( +halfPixel.x * 3, +halfPixel.y ), 0.0 ).x;
		vals.w = texture2DLod(s_importanceMap, inUV + vec2( -halfPixel.x, +halfPixel.y * 3 ), 0.0 ).x;

		float avgVal = dot( vals, vec4( 0.25, 0.25, 0.25, 0.25 ) );
		vals.xy = max( vals.xy, vals.zw );
		float maxVal = max( centre, max( vals.x, vals.y ) );

		imageStore(s_target, ivec2(dtID.xy), mix( maxVal, avgVal, cSmoothenImportance ).xxxx);
	}
}
