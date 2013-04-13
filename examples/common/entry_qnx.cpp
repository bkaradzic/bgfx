/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/bx.h>

#if BX_PLATFORM_QNX

#include <stdio.h>
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

int main(int _argc, char** _argv)
{
	_main_(_argc, _argv);
}

#endif // BX_PLATFORM_QNX
