/*
 * Copyright 2011-2025 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_RENDERDOC_H_HEADER_GUARD
#define BGFX_RENDERDOC_H_HEADER_GUARD

namespace bgfx
{
	void* findModule(const char* _name);
	void* loadRenderDoc();
	void unloadRenderDoc(void*);
	void renderDocTriggerCapture();

} // namespace bgfx

#endif // BGFX_RENDERDOC_H_HEADER_GUARD
