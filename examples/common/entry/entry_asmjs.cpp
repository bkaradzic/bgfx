/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "entry_p.h"

#if BX_PLATFORM_EMSCRIPTEN

#include <emscripten.h>

namespace entry
{
	const Event* poll()
	{
		return NULL;
	}

	void release(const Event* /*_event*/)
	{
	}

	void setWindowSize(uint32_t /*_width*/, uint32_t /*_height*/)
	{
	}

	void toggleWindowFrame()
	{
	}

	void setMouseLock(bool /*_lock*/)
	{
	}
}

int main(int _argc, char** _argv)
{
	return entry::main(_argc, _argv);
}

#endif // BX_PLATFORM_EMSCRIPTEN
