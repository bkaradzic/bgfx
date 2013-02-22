/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/bx.h>

#if BX_PLATFORM_EMSCRIPTEN

#include <emscripten/emscripten.h>
#include <alloca.h>
#include <setjmp.h>

#include "entry.h"

namespace entry
{
	const Event* poll()
	{
		return NULL;
	}

	void release(const Event* _event)
	{
	}

	void setWindowSize(uint32_t _width, uint32_t _height)
	{
	}

	void toggleWindowFrame()
	{
	}

	void setMouseLock(bool _lock)
	{
	}

} // namespace entry

extern int _main_(int _argc, char** _argv);

static jmp_buf s_main;
static jmp_buf s_loop;

void emscripten_yield()
{
	if (!setjmp(s_main) )
	{
		longjmp(s_loop, 1);
	}
}

void loop()
{
	if (!setjmp(s_loop) )
	{
		longjmp(s_main, 1);
	}
}

int main(int _argc, char** _argv)
{
	if (!setjmp(s_loop) )
	{
		alloca(16<<10);
		_main_(_argc, _argv);
	}

	emscripten_set_main_loop(loop, 10, true);
}

#endif // BX_PLATFORM_EMSCRIPTEN
