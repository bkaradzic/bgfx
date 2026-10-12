/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "bgfx_shader.sh"

#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_SPIRV
SAMPLER2DMSARRAY(bgfx_texDepthMs, 0);

void main()
{
	gl_FragDepth = texelFetch(bgfx_texDepthMs, ivec3(gl_FragCoord.xy, 0), 0).x;
}
#else
SAMPLER2DMS(bgfx_texDepthMs, 0);

void main()
{
	gl_FragDepth = texelFetch(bgfx_texDepthMs, ivec2(gl_FragCoord.xy), 0).x;
}
#endif // BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_SPIRV
