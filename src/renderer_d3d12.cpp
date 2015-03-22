/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D12
#	include "../../d3d12/src/renderer_d3d12.cpp"
#else

namespace bgfx { namespace d3d12
{
	RendererContextI* rendererCreate()
	{
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace d3d12 */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_DIRECT3D12
