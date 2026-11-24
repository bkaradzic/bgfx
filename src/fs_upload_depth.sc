/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_shader.sh"

SAMPLER2D(bgfx_texDepth, 0);

void main()
{
	gl_FragDepth = texelFetch(bgfx_texDepth, ivec2(gl_FragCoord.xy), 0).x;
}
