/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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
