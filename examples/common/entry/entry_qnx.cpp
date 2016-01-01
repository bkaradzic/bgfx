/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_QNX

#include <stdio.h>

namespace entry
{
	const Event* poll()
	{
		return NULL;
	}

	const Event* poll(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
		return NULL;
	}

	void release(const Event* _event)
	{
		BX_UNUSED(_event);
	}

	WindowHandle createWindow(int32_t _x, int32_t _y, uint32_t _width, uint32_t _height, uint32_t _flags, const char* _title)
	{
		BX_UNUSED(_x, _y, _width, _height, _flags, _title);
		WindowHandle handle = { UINT16_MAX };
		return handle;
	}

	void destroyWindow(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y)
	{
		BX_UNUSED(_handle, _x, _y);
	}

	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height)
	{
		BX_UNUSED(_handle, _width, _height);
	}

	void setWindowTitle(WindowHandle _handle, const char* _title)
	{
		BX_UNUSED(_handle, _title);
	}

	void toggleWindowFrame(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void toggleFullscreen(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		BX_UNUSED(_handle, _lock);
	}

} // namespace entry

int main(int _argc, char** _argv)
{
	entry::main(_argc, _argv);
}

#endif // ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_QNX
