/*
 * Copyright 2018 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh" 
#include "uniforms.sh"

IMAGE2D_ARRAY_WR(s_target, rg8, 0);
SAMPLER2DARRAY(s_blurInput, 1);

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

// ********************************************************************************************************
// Pixel shader that does smart blurring (to avoid bleeding)

void AddSample( float ssaoValue, float edgeValue, inout float sum, inout float sumWeight )
{
    float weight = edgeValue;    

    sum += (weight * ssaoValue);
    sumWeight += weight;
}

vec2 SampleBlurred( ivec2 inPos, vec2 coord )
{
    float packedEdges   = texelFetch(s_blurInput, ivec3(inPos.xy,0.0), 0 ).y;
    vec4 edgesLRTB    = UnpackEdges( packedEdges );

#if BGFX_SHADER_LANGUAGE_GLSL
    vec4 valuesUL     = textureGather(s_blurInput, vec3(coord - u_halfViewportPixelSize * 0.5 + vec2(0.0,u_halfViewportPixelSize.y), 0.0), 0).wzyx;
    vec4 valuesBR     = textureGather(s_blurInput, vec3(coord + u_halfViewportPixelSize * 0.5 + vec2(0.0,-u_halfViewportPixelSize.y), 0.0), 0).wzyx;
#else
    vec4 valuesUL     = textureGather(s_blurInput, vec3(coord - u_halfViewportPixelSize * 0.5, 0.0), 0);
    vec4 valuesBR     = textureGather(s_blurInput, vec3(coord + u_halfViewportPixelSize * 0.5, 0.0), 0);
#endif

    float ssaoValue     = valuesUL.y;
    float ssaoValueL    = valuesUL.x;
    float ssaoValueT    = valuesUL.z;
    float ssaoValueR    = valuesBR.z;
    float ssaoValueB    = valuesBR.x;

    float sumWeight = 0.5f;
    float sum = ssaoValue * sumWeight;

    AddSample( ssaoValueL, edgesLRTB.x, sum, sumWeight );
    AddSample( ssaoValueR, edgesLRTB.y, sum, sumWeight );

    AddSample( ssaoValueT, edgesLRTB.z, sum, sumWeight );
    AddSample( ssaoValueB, edgesLRTB.w, sum, sumWeight );

    float ssaoAvg = sum / sumWeight;

    ssaoValue = ssaoAvg; //min( ssaoValue, ssaoAvg ) * 0.2 + ssaoAvg * 0.8;

    return vec2( ssaoValue, packedEdges );
}

// edge-sensitive blur
NUM_THREADS(8, 8, 1)
void main() 
{
	uvec2 dtID = uvec2(gl_GlobalInvocationID.xy) + uvec2(u_rect.xy);
	if (all(lessThan(dtID.xy, u_rect.zw) ) )
	{
		vec2 inUV = (dtID.xy+vec2(0.5,0.5)) * u_halfViewportPixelSize;
	    imageStore(s_target, ivec3(dtID.xy, u_layer), SampleBlurred( ivec2(dtID.xy), inUV ).xyyy);
	}
}

