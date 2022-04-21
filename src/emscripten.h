/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_EMSCRIPTEN_H_HEADER_GUARD
#define BGFX_EMSCRIPTEN_H_HEADER_GUARD

#if BX_PLATFORM_EMSCRIPTEN

#	include <emscripten/emscripten.h>
#	include <emscripten/html5.h>

#	define _EMSCRIPTEN_CHECK(_check, _call)                                                                   \
		BX_MACRO_BLOCK_BEGIN                                                                                  \
			EMSCRIPTEN_RESULT __result__ = _call;                                                             \
			_check(EMSCRIPTEN_RESULT_SUCCESS == __result__, #_call " FAILED 0x%08x\n", (uint32_t)__result__); \
			BX_UNUSED(__result__);                                                                            \
		BX_MACRO_BLOCK_END

#	if BGFX_CONFIG_DEBUG
#		define EMSCRIPTEN_CHECK(_call) _EMSCRIPTEN_CHECK(BX_ASSERT, _call)
#	else
#		define EMSCRIPTEN_CHECK(_call) _call
#	endif // BGFX_CONFIG_DEBUG

#	ifndef HTML5_TARGET_CANVAS_SELECTOR
#		define HTML5_TARGET_CANVAS_SELECTOR "#canvas"
#	endif // HTML5_TARGET_CANVAS_SELECTOR

#endif // BX_PLATFORM_EMSCRIPTEN

#endif // BGFX_EMSCRIPTEN_H_HEADER_GUARD
