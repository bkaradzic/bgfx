/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"
#if BGFX_CONFIG_RENDERER_METAL
#	include "../../bgfx-ext/src/renderer_mtl.cpp"
#else

namespace bgfx { namespace mtl
{
	RendererContextI* rendererCreate()
	{
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace mtl */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_METAL
