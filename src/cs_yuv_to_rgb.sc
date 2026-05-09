/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_compute.sh"

SAMPLER2D(bgfx_texY,    1);
SAMPLER2D(bgfx_texCbCr, 2);

IMAGE2D_WO(bgfx_imgRgba, rgba8, 0);

NUM_THREADS(8, 8, 1)
void main()
{
	ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
	ivec2 size  = imageSize(bgfx_imgRgba);

	if (coord.x >= size.x
	||  coord.y >= size.y)
	{
		return;
	}

	vec2 invSize = vec2(1.0, 1.0) / vec2(size);
	vec2 uv      = (vec2(coord) + vec2(0.5, 0.5) ) * invSize;

	float y  = texture2DLod(bgfx_texY,    uv, 0.0).x;
	vec2  cb = texture2DLod(bgfx_texCbCr, uv, 0.0).xy;

	float yL  = (y     - 16.0/255.0) * (255.0/219.0);
	float cbL = (cb.x  - 128.0/255.0) * (255.0/224.0);
	float crL = (cb.y  - 128.0/255.0) * (255.0/224.0);

	vec3 rgb;
	rgb.r = yL                  + 1.5748 * crL;
	rgb.g = yL - 0.1873 * cbL   - 0.4681 * crL;
	rgb.b = yL + 1.8556 * cbL;

	imageStore(bgfx_imgRgba, coord, vec4(clamp(rgb, 0.0, 1.0), 1.0) );
}
