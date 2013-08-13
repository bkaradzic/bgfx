/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "entry.h"

#if BX_PLATFORM_OSX

#include <SDL2/SDL.h>
#include <bgfxplatform.h>
#include "entry_p.h"

#include <stdio.h>
#include <bx/thread.h>

namespace entry
{
	struct MainThreadEntry
	{
		int m_argc;
		char** m_argv;

		static int32_t threadFunc(void* _userData);
	};

	struct Context
	{
		Context()
			: m_window(NULL)
		{
		}

		void run()
		{
			const char* argv[1] = { "sdl.so" };
			m_mte.m_argc = 1;
			m_mte.m_argv = const_cast<char**>(argv);

			SDL_Init(SDL_INIT_VIDEO);

			m_window = SDL_CreateWindow("bgfx"
							, SDL_WINDOWPOS_UNDEFINED
							, SDL_WINDOWPOS_UNDEFINED
							, 1200
							, 720
							, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL
							);

			bgfx::sdlSetWindow(m_window);
			m_thread.init(MainThreadEntry::threadFunc, &m_mte);

			bool exit = false;
			SDL_Event event;
			while (!exit && SDL_WaitEvent(&event) )
			{
				switch (event.type)
				{
				case SDL_QUIT:
					m_eventQueue.postExitEvent();
					exit = true;
					break;
				}
			}

			m_thread.shutdown();

			SDL_DestroyWindow(m_window);
			SDL_Quit();
		}

		MainThreadEntry m_mte;
		bx::Thread m_thread;

		EventQueue m_eventQueue;

		SDL_Window* m_window;
	};

	static Context s_ctx;

	const Event* poll()
	{
		return s_ctx.m_eventQueue.poll();
	}

	void release(const Event* _event)
	{
		s_ctx.m_eventQueue.release(_event);
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

	int32_t MainThreadEntry::threadFunc(void* _userData)
	{
		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = main(self->m_argc, self->m_argv);

		SDL_Event event;
		event.type = SDL_QUIT;
		SDL_PushEvent(&event);
		return result;
	}

} // namespace entry

int main(int _argc, const char* _argv[])
{
	using namespace entry;
	s_ctx.run();
}

#endif // BX_PLATFORM_
