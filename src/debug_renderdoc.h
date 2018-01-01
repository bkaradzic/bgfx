/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_RENDERDOC_H_HEADER_GUARD
#define BGFX_RENDERDOC_H_HEADER_GUARD

namespace bgfx
{
	void* loadRenderDoc();
	void unloadRenderDoc(void*);
	void renderDocTriggerCapture();

} // namespace bgfx

#endif // BGFX_RENDERDOC_H_HEADER_GUARD
