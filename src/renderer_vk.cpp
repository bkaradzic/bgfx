/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_VULKAN
#	include "../../bgfx-ext/src/renderer_vk.cpp"
#else

namespace bgfx { namespace vk
{
	RendererContextI* rendererCreate()
	{
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace vk */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_VULKAN
