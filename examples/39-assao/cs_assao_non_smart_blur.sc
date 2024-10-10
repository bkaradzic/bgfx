/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

IMAGE2D_ARRAY_WO(s_target, rg8, 0);
SAMPLER2DARRAY(s_blurInput,  1); 

// edge-ignorant blur in x and y directions, 9 pixels touched (for the lowest quality level 0)
NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy) + uvec2(u_rect.xy);
	if (all(lessThan(dtID.xy, u_rect.zw) ) )
	{
		vec2 inUV = (dtID.xy+vec2(0.5,0.5)) * u_halfViewportPixelSize;
		vec2 halfPixel = u_halfViewportPixelSize * 0.5f;

#if BGFX_SHADER_LANGUAGE_GLSL
		halfPixel.y = -halfPixel.y;
#endif

		vec2 centre = texture2DArrayLod(s_blurInput, vec3(inUV, 0.0), 0.0 ).xy;

		vec4 vals;
		vals.x = texture2DArrayLod(s_blurInput, vec3(inUV + vec2( -halfPixel.x * 3, -halfPixel.y ),0.0) , 0.0 ).x;
		vals.y = texture2DArrayLod(s_blurInput, vec3(inUV + vec2( +halfPixel.x, -halfPixel.y * 3 ),0.0) , 0.0 ).x;
		vals.z = texture2DArrayLod(s_blurInput, vec3(inUV + vec2( -halfPixel.x, +halfPixel.y * 3 ),0.0) , 0.0 ).x;
		vals.w = texture2DArrayLod(s_blurInput, vec3(inUV + vec2( +halfPixel.x * 3, +halfPixel.y ),0.0) , 0.0 ).x;

		imageStore(s_target, ivec3(dtID.xy,u_layer), vec4(dot( vals, 0.2.xxxx ) + centre.x * 0.2, centre.y, 0.0, 0.0));
	}
}

