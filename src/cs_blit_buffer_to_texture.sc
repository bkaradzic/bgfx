/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh"

BUFFER_RO(bgfx_blitSrc, vec4, 0);
IMAGE2D_ARRAY_WO(bgfx_blitDst, rgba32f, 0);

uniform vec4 bgfx_blitRegion[2];

#define bgfx_dstOrigin      ivec3(bgfx_blitRegion[0].xyz)
#define bgfx_blitSize       ivec3(bgfx_blitRegion[1].xyz)
#define bgfx_blitRowPitch   int(bgfx_blitRegion[0].w)
#define bgfx_blitSlicePitch int(bgfx_blitRegion[1].w)

NUM_THREADS(8, 8, 1)
void main()
{
	ivec3 coord = ivec3(gl_GlobalInvocationID.xyz);

	if (coord.x >= bgfx_blitSize.x
	||  coord.y >= bgfx_blitSize.y
	||  coord.z >= bgfx_blitSize.z)
	{
		return;
	}

	int index = coord.z * bgfx_blitSlicePitch + coord.y * bgfx_blitRowPitch + coord.x;

	imageStore(bgfx_blitDst, bgfx_dstOrigin + coord, bgfx_blitSrc[index]);
}
