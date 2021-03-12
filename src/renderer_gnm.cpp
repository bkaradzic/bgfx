/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "bgfx_p.h"

namespace bgfx
{

#define BGFX_DECLARE_EMBEDDED_SHADER(_name)                                                     \
			extern const uint8_t* BX_CONCATENATE(_name, _pssl);                                 \
			extern const uint32_t BX_CONCATENATE(_name, _pssl_size);                            \
			static const uint8_t  BX_CONCATENATE(_name, _int_pssl)[] = { 0 };                   \
			const uint8_t* BX_CONCATENATE(_name, _pssl) = &BX_CONCATENATE(_name, _int_pssl)[0]; \
			const uint32_t BX_CONCATENATE(_name, _pssl_size) = 1

BGFX_DECLARE_EMBEDDED_SHADER(vs_debugfont);
BGFX_DECLARE_EMBEDDED_SHADER(fs_debugfont);
BGFX_DECLARE_EMBEDDED_SHADER(vs_clear);
BGFX_DECLARE_EMBEDDED_SHADER(fs_clear0);
BGFX_DECLARE_EMBEDDED_SHADER(fs_clear1);
BGFX_DECLARE_EMBEDDED_SHADER(fs_clear2);
BGFX_DECLARE_EMBEDDED_SHADER(fs_clear3);
BGFX_DECLARE_EMBEDDED_SHADER(fs_clear4);
BGFX_DECLARE_EMBEDDED_SHADER(fs_clear5);
BGFX_DECLARE_EMBEDDED_SHADER(fs_clear6);
BGFX_DECLARE_EMBEDDED_SHADER(fs_clear7);

#undef BGFX_DECLARE_EMBEDDED_SHADER

} // namespace bgfx

namespace bgfx { namespace gnm
{
	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace gnm */ } // namespace bgfx
