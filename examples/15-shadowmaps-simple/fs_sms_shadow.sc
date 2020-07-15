/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

void main()
{
	// Vulkan does not like shader writing to a target that is not attached
#ifndef BGFX_SHADER_LANGUAGE_SPIRV
	gl_FragColor = vec4_splat(0.0);
#endif
}
