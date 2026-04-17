/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

// Developed by Minigraph
// Author:  James Stanard

#include "bgfx_compute.sh"

SAMPLER2D(bgfx_texMipSrc, 4);

IMAGE2D_WO(s_imgMip1, rgba8, 0);
IMAGE2D_WO(s_imgMip2, rgba8, 1);
IMAGE2D_WO(s_imgMip3, rgba8, 2);
IMAGE2D_WO(s_imgMip4, rgba8, 3);

uniform vec4 bgfx_mipGen;

SHARED float gs_R[64];
SHARED float gs_G[64];
SHARED float gs_B[64];
SHARED float gs_A[64];

void storeColor(uint _index, vec4 _color)
{
	gs_R[_index] = _color.x;
	gs_G[_index] = _color.y;
	gs_B[_index] = _color.z;
	gs_A[_index] = _color.w;
}

vec4 loadColor(uint _index)
{
	return vec4(gs_R[_index], gs_G[_index], gs_B[_index], gs_A[_index]);
}

NUM_THREADS(8, 8, 1)
void main()
{
	uint  gi   = gl_LocalInvocationIndex;
	uvec3 dtid = gl_GlobalInvocationID;

	uint  srcMipLevel  = uint(bgfx_mipGen.x);
	uint  numMipLevels = uint(bgfx_mipGen.y);
	vec2  texelSize    = bgfx_mipGen.zw;

	vec4 src1;

#if NON_POWER_OF_TWO == 0
	vec2 uv = texelSize * (vec2(dtid.xy) + vec2_splat(0.5) );
	src1 = texture2DLod(bgfx_texMipSrc, uv, float(srcMipLevel) );

#elif NON_POWER_OF_TWO == 1
	// > 2:1 in X dimension
	vec2 uv1 = texelSize * (vec2(dtid.xy) + vec2(0.25, 0.5) );
	vec2 off = texelSize * vec2(0.5, 0.0);
	src1 = 0.5 * (texture2DLod(bgfx_texMipSrc, uv1,       float(srcMipLevel) )
	            + texture2DLod(bgfx_texMipSrc, uv1 + off, float(srcMipLevel) ) );

#elif NON_POWER_OF_TWO == 2
	// > 2:1 in Y dimension
	vec2 uv1 = texelSize * (vec2(dtid.xy) + vec2(0.5, 0.25) );
	vec2 off = texelSize * vec2(0.0, 0.5);
	src1 = 0.5 * (texture2DLod(bgfx_texMipSrc, uv1,       float(srcMipLevel) )
	            + texture2DLod(bgfx_texMipSrc, uv1 + off, float(srcMipLevel) ) );

#elif NON_POWER_OF_TWO == 3
	// > 2:1 in both dimensions
	vec2 uv1 = texelSize * (vec2(dtid.xy) + vec2(0.25, 0.25) );
	vec2 off = texelSize * vec2_splat(0.5);
	src1  = texture2DLod(bgfx_texMipSrc, uv1,                      float(srcMipLevel) );
	src1 += texture2DLod(bgfx_texMipSrc, uv1 + vec2(off.x, 0.0),   float(srcMipLevel) );
	src1 += texture2DLod(bgfx_texMipSrc, uv1 + vec2(0.0, off.y),   float(srcMipLevel) );
	src1 += texture2DLod(bgfx_texMipSrc, uv1 + vec2(off.x, off.y), float(srcMipLevel) );
	src1 *= 0.25;
#endif // NON_POWER_OF_TWO

	imageStore(s_imgMip1, ivec2(dtid.xy), src1);

	if (numMipLevels == 1u)
	{
		return;
	}

	storeColor(gi, src1);
	barrier();

	// X and Y are even (bit pattern: 001001).
	if ( (gi & 0x9u) == 0u)
	{
		vec4 src2 = loadColor(gi + 0x01u);
		vec4 src3 = loadColor(gi + 0x08u);
		vec4 src4 = loadColor(gi + 0x09u);
		src1 = 0.25 * (src1 + src2 + src3 + src4);

		imageStore(s_imgMip2, ivec2(dtid.xy / 2u), src1);
		storeColor(gi, src1);
	}

	if (numMipLevels == 2u)
	{
		return;
	}

	barrier();

	if ( (gi & 0x1Bu) == 0u)
	{
		vec4 src2 = loadColor(gi + 0x02u);
		vec4 src3 = loadColor(gi + 0x10u);
		vec4 src4 = loadColor(gi + 0x12u);
		src1 = 0.25 * (src1 + src2 + src3 + src4);

		imageStore(s_imgMip3, ivec2(dtid.xy / 4u), src1);
		storeColor(gi, src1);
	}

	if (numMipLevels == 3u)
	{
		return;
	}

	barrier();

	// Only thread 0 (X and Y multiples of 8).
	if (gi == 0u)
	{
		vec4 src2 = loadColor(gi + 0x04u);
		vec4 src3 = loadColor(gi + 0x20u);
		vec4 src4 = loadColor(gi + 0x24u);
		src1 = 0.25 * (src1 + src2 + src3 + src4);

		imageStore(s_imgMip4, ivec2(dtid.xy / 8u), src1);
	}
}
