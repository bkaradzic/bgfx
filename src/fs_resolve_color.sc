/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_shader.sh"

SAMPLER2DMS(bgfx_texColorMs, 0);

void main()
{
	ivec2 coord = ivec2(gl_FragCoord.xy);

	gl_FragColor = (vec4_splat(0.0)
		+ texelFetch(bgfx_texColorMs, coord, 0)
		+ texelFetch(bgfx_texColorMs, coord, 1)
		+ texelFetch(bgfx_texColorMs, coord, 2)
		+ texelFetch(bgfx_texColorMs, coord, 3)
		) * 0.25;
}
