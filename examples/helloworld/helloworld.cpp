/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <conio.h>

int main(int _argc, const char** _argv)
{
	bgfx::init(true);
	bgfx::reset(1280, 720);

	bgfx::setDebug(BGFX_DEBUG_TEXT);

	while (!_kbhit() )
	{
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 0, 0x4f, "Hello world!");

		bgfx::dbgTextPrintf(0, 5, 0x6f, "BGFX initialization and debug text.");

		bgfx::frame();
	}

	bgfx::shutdown();

	return 0;
}
