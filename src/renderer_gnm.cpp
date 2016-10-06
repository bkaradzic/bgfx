/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

namespace bgfx
{

#define BGFX_DECALRE_EMBEDDED_SHADER(_name)            \
			extern const uint8_t  _name ## _pssl[];    \
			extern const uint32_t _name ## _pssl_size; \
			const uint8_t  _name ## _pssl[] = { 0 };   \
			const uint32_t _name ## _pssl_size = 1

BGFX_DECALRE_EMBEDDED_SHADER(vs_debugfont);
BGFX_DECALRE_EMBEDDED_SHADER(fs_debugfont);
BGFX_DECALRE_EMBEDDED_SHADER(vs_clear);
BGFX_DECALRE_EMBEDDED_SHADER(fs_clear0);
BGFX_DECALRE_EMBEDDED_SHADER(fs_clear1);
BGFX_DECALRE_EMBEDDED_SHADER(fs_clear2);
BGFX_DECALRE_EMBEDDED_SHADER(fs_clear3);
BGFX_DECALRE_EMBEDDED_SHADER(fs_clear4);
BGFX_DECALRE_EMBEDDED_SHADER(fs_clear5);
BGFX_DECALRE_EMBEDDED_SHADER(fs_clear6);
BGFX_DECALRE_EMBEDDED_SHADER(fs_clear7);

#undef BGFX_DECALRE_EMBEDDED_SHADER

} // namespace bgfx

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
