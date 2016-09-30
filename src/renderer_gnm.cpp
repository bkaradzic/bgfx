/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_GNM

namespace bgfx { namespace gnm
{
	RendererContextI* rendererCreate()
	{
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace gnm */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_GNM
