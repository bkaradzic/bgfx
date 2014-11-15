/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_DIRECT3D12

namespace bgfx
{
	RendererContextI* rendererCreateD3D12()
	{
		return NULL;
	}

	void rendererDestroyD3D12()
	{
	}
} // namespace bgfx

#else

namespace bgfx
{
	RendererContextI* rendererCreateD3D12()
	{
		return NULL;
	}

	void rendererDestroyD3D12()
	{
	}
} // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_DIRECT3D12
