/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/bx.h>

#if BX_PLATFORM_LINUX

#include "bgfxplatform.h"
#include <stdlib.h>

#include <bx/thread.h>
#include <bx/os.h>

#undef None
#include "entry.h"

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720

extern int _main_(int _argc, char** _argv);

namespace entry
{
	struct MainThreadEntry
	{
		int m_argc;
		char** m_argv;

		static int32_t threadFunc(void* _userData)
		{
			MainThreadEntry* self = (MainThreadEntry*)_userData;
			return _main_(self->m_argc, self->m_argv);
		}
	};

	struct Context
	{
		int32_t run(int _argc, char** _argv)
		{
			m_display = XOpenDisplay(0);

			XLockDisplay(m_display);

			int32_t screen = DefaultScreen(m_display);
			int32_t depth = DefaultDepth(m_display, screen);
			Visual* visual = DefaultVisual(m_display, screen);
			Window root = RootWindow(m_display, screen);

			XSetWindowAttributes windowAttrs;
			windowAttrs.colormap =
				XCreateColormap(m_display
						, root
						, visual
						, AllocNone
						);
			windowAttrs.background_pixmap = 0;
			windowAttrs.border_pixel = 0;

			m_window = XCreateWindow(m_display
									, root
									, 0, 0
									, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0, depth
									, InputOutput
									, visual
									, CWBorderPixel|CWColormap
									, &windowAttrs
									);

			XMapRaised(m_display, m_window);
			XFlush(m_display);

			XUnlockDisplay(m_display);

//			XResizeWindow(s_display, s_window, _width, _height);

			bgfx::x11SetDisplayWindow(m_display, m_window);

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);

			thread.shutdown();

			return EXIT_SUCCESS;
		}

		Display* m_display;
		Window m_window;
	};

	static Context s_ctx;

	Event::Enum poll()
	{
		return Event::Nop;
	}

} // namespace entry

int main(int _argc, char** _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // BX_PLATFORM_LINUX
