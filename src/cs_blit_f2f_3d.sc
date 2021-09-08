/*
 * Copyright 2018 Kostas Anagnostou. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_compute.sh"

// NOTE: The format here is not representative of the actual texture format
// (at least for PS5, perhaps it is on other platforms). I am using the format
// required to get the data type correct: float4.
IMAGE3D_RO(s_srcTexture, rgba32f, 0);
IMAGE3D_WR(s_dstTexture, rgba32f, 1);

BGFX_BEGIN_UNIFORM_BLOCK(UniformsMaterial)
uniform vec4 u_srcOffset;
uniform vec4 u_dstOffset;
BGFX_END_UNIFORM_BLOCK

NUM_THREADS(4, 4, 4)
void main()
{
	ivec3 srcCoord = (ivec3)(u_srcOffset.xyz + gl_GlobalInvocationID.xyz);
	ivec3 dstCoord = (ivec3)(u_dstOffset.xyz + gl_GlobalInvocationID.xyz);
	imageStore(s_dstTexture, dstCoord, imageLoad(s_srcTexture, srcCoord));
}
