/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <bx/bx.h>
#include "../common/dbg.h"

void fatalCb(bgfx::Fatal::Enum _code, const char* _str)
{
	DBG("%x: %s", _code, _str);
}

int _main_(int _argc, char** _argv)
{
	bgfx::init(BX_PLATFORM_WINDOWS, fatalCb);
	bgfx::reset(1280, 720);

	bgfx::setDebug(BGFX_DEBUG_TEXT);

	bgfx::setViewRect(0, 0, 0, 1280, 720);
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT, 0x000000ff, 0.0f, 0);

	while (true)
	{
		bgfx::submit(0);

		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "BGFX: Hello, World!");

		bgfx::dbgTextPrintf(0, 2, 0x6f, "Initialization and debug text.");

		bgfx::frame();
	}

	bgfx::shutdown();

	return 0;
}
