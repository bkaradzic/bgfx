/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

IMAGE2D_WR(s_target, r8, 0);
SAMPLER2DARRAY(s_finalSSAO,  1); 

// unpacking for edges; 2 bits per edge mean 4 gradient values (0, 0.33, 0.66, 1) for smoother transitions!

vec4 UnpackEdges( float _packedVal )
{
    uint packedVal = uint(_packedVal * 255.5);
    vec4 edgesLRTB;
    edgesLRTB.x = float((packedVal >> 6) & 0x03) / 3.0;          // there's really no need for mask (as it's an 8 bit input) but I'll leave it in so it doesn't cause any trouble in the future
    edgesLRTB.y = float((packedVal >> 4) & 0x03) / 3.0;
    edgesLRTB.z = float((packedVal >> 2) & 0x03) / 3.0;
    edgesLRTB.w = float((packedVal >> 0) & 0x03) / 3.0;

    return saturate( edgesLRTB + u_invSharpness );
}

NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy) + uvec2(u_rect.xy);
	if (all(lessThan(dtID.xy, u_rect.zw) ) )
	{
		float ao;
		uvec2 pixPos     = uvec2(dtID.xy);
		uvec2 pixPosHalf = pixPos / uvec2(2, 2);

		// calculate index in the four deinterleaved source array texture
		int mx = (int(pixPos.x) % 2);
#if BGFX_SHADER_LANGUAGE_GLSL
		int dimy = imageSize(s_target).y; 
		int my = (int(dimy-1-pixPos.y) % 2);
#else
		int my = (int(pixPos.y) % 2);
#endif
		int ic = mx + my * 2;       // center index
		int ih = (1-mx) + my * 2;   // neighbouring, horizontal
		int iv = mx + (1-my) * 2;   // neighbouring, vertical
		int id = (1-mx) + (1-my)*2; // diagonal

		vec2 centerVal = texelFetch(s_finalSSAO, ivec3(pixPosHalf, ic), 0 ).xy;
    
		ao = centerVal.x;

	#if 1   // change to 0 if you want to disable last pass high-res blur (for debugging purposes, etc.)
		vec4 edgesLRTB = UnpackEdges( centerVal.y );

		// return 1.0 - vec4( edgesLRTB.x, edgesLRTB.y * 0.5 + edgesLRTB.w * 0.5, edgesLRTB.z, 0.0 ); // debug show edges

		// convert index shifts to sampling offsets
		float fmx   = float(mx);
		float fmy   = float(my);
    
		// in case of an edge, push sampling offsets away from the edge (towards pixel center)
		float fmxe  = (edgesLRTB.y - edgesLRTB.x);
		float fmye  = (edgesLRTB.w - edgesLRTB.z);

		// calculate final sampling offsets and sample using bilinear filter
#if BGFX_SHADER_LANGUAGE_GLSL
		vec2  uvH = (dtID.xy + vec2( fmx + fmxe - 0.5, 1.0 - (0.5 - fmy) ) ) * 0.5 * u_halfViewportPixelSize;
#else
		vec2  uvH = (dtID.xy + vec2( fmx + fmxe - 0.5, 0.5 - fmy ) ) * 0.5 * u_halfViewportPixelSize;
#endif
		float   aoH = texture2DArrayLod(s_finalSSAO, vec3( uvH, ih ), 0 ).x;
#if BGFX_SHADER_LANGUAGE_GLSL
		vec2  uvV = (dtID.xy + vec2( 0.5 - fmx, 1.0 - (fmy - 0.5 + fmye) ) ) * 0.5 * u_halfViewportPixelSize;
#else
		vec2  uvV = (dtID.xy + vec2( 0.5 - fmx, fmy - 0.5 + fmye ) ) * 0.5 * u_halfViewportPixelSize;
#endif
		float   aoV = texture2DArrayLod(s_finalSSAO, vec3( uvV, iv ), 0 ).x;
#if BGFX_SHADER_LANGUAGE_GLSL
		vec2  uvD = (dtID.xy + vec2( fmx - 0.5 + fmxe, 1.0 - (fmy - 0.5 + fmye) ) ) * 0.5 * u_halfViewportPixelSize;
#else
		vec2  uvD = (dtID.xy + vec2( fmx - 0.5 + fmxe, fmy - 0.5 + fmye ) ) * 0.5 * u_halfViewportPixelSize;
#endif
		float   aoD = texture2DArrayLod(s_finalSSAO, vec3( uvD, id ), 0 ).x;

		// reduce weight for samples near edge - if the edge is on both sides, weight goes to 0
		vec4 blendWeights;
		blendWeights.x = 1.0;
		blendWeights.y = (edgesLRTB.x + edgesLRTB.y) * 0.5;
		blendWeights.z = (edgesLRTB.z + edgesLRTB.w) * 0.5;
		blendWeights.w = (blendWeights.y + blendWeights.z) * 0.5;

		// calculate weighted average
		float blendWeightsSum   = dot( blendWeights, vec4( 1.0, 1.0, 1.0, 1.0 ) );
		ao = dot( vec4( ao, aoH, aoV, aoD ), blendWeights ) / blendWeightsSum;
	#endif

		ao = pow(ao,1.0/2.2);

		imageStore(s_target, ivec2(dtID.xy), ao.xxxx);
	}
}

