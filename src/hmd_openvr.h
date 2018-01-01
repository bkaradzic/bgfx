/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef BGFX_OPENVR_H_HEADER_GUARD
#define BGFX_OPENVR_H_HEADER_GUARD

#include "bgfx_p.h"

namespace bgfx
{
	void* loadOpenVR();
	void unloadOpenVR(void*);

} // namespace bgfx

#endif // BGFX_OPENVR_H_HEADER_GUARD
