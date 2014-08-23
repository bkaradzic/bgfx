/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_ANDROID

#include <bgfxplatform.h>

#include <stdio.h>
#include <bx/thread.h>

#include <android/input.h>
#include <android/log.h>
#include <android/looper.h>
#include <android/window.h>
#include <android_native_app_glue.h>

extern "C"
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <android_native_app_glue.c>
#pragma GCC diagnostic pop
} // extern "C"

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

		void run(android_app* _app)
		{
			m_app = _app;
			m_app->userData = (void*)this;
			m_app->onAppCmd = onAppCmdCB;
			m_app->onInputEvent = onInputEventCB;

			const char* argv[1] = { "android.so" };
			m_mte.m_argc = 1;
			m_mte.m_argv = const_cast<char**>(argv);
			
			while (0 == m_app->destroyRequested)
			{
				int32_t num;
				android_poll_source* source;
				/*int32_t id =*/ ALooper_pollAll(-1, NULL, &num, (void**)&source);

				if (NULL != source)
				{
					source->process(m_app, source);
				}
			}

			m_thread.shutdown();
		}

		void onAppCmd(int32_t _cmd)
		{
			switch (_cmd)
			{
				case APP_CMD_INPUT_CHANGED:
					// Command from main thread: the AInputQueue has changed.  Upon processing
					// this command, android_app->inputQueue will be updated to the new queue
					// (or NULL).
					break;

				case APP_CMD_INIT_WINDOW:
					// Command from main thread: a new ANativeWindow is ready for use.  Upon
					// receiving this command, android_app->window will contain the new window
					// surface.
					if (m_window == NULL)
					{
						m_window = m_app->window;
						bgfx::androidSetWindow(m_app->window);
						m_thread.init(MainThreadEntry::threadFunc, &m_mte);
					}
					break;

				case APP_CMD_TERM_WINDOW:
					// Command from main thread: the existing ANativeWindow needs to be
					// terminated.  Upon receiving this command, android_app->window still
					// contains the existing window; after calling android_app_exec_cmd
					// it will be set to NULL.
					break;

				case APP_CMD_WINDOW_RESIZED:
					// Command from main thread: the current ANativeWindow has been resized.
					// Please redraw with its new size.
					break;

				case APP_CMD_WINDOW_REDRAW_NEEDED:
					// Command from main thread: the system needs that the current ANativeWindow
					// be redrawn.  You should redraw the window before handing this to
					// android_app_exec_cmd() in order to avoid transient drawing glitches.
					break;

				case APP_CMD_CONTENT_RECT_CHANGED:
					// Command from main thread: the content area of the window has changed,
					// such as from the soft input window being shown or hidden.  You can
					// find the new content rect in android_app::contentRect.
					break;

				case APP_CMD_GAINED_FOCUS:
					// Command from main thread: the app's activity window has gained
					// input focus.
					break;

				case APP_CMD_LOST_FOCUS:
					// Command from main thread: the app's activity window has lost
					// input focus.
					break;

				case APP_CMD_CONFIG_CHANGED:
					// Command from main thread: the current device configuration has changed.
					break;

				case APP_CMD_LOW_MEMORY:
					// Command from main thread: the system is running low on memory.
					// Try to reduce your memory use.
					break;

				case APP_CMD_START:
					// Command from main thread: the app's activity has been started.
					break;

				case APP_CMD_RESUME:
					// Command from main thread: the app's activity has been resumed.
					break;

				case APP_CMD_SAVE_STATE:
					// Command from main thread: the app should generate a new saved state
					// for itself, to restore from later if needed.  If you have saved state,
					// allocate it with malloc and place it in android_app.savedState with
					// the size in android_app.savedStateSize.  The will be freed for you
					// later.
					break;

				case APP_CMD_PAUSE:
					// Command from main thread: the app's activity has been paused.
					break;

				case APP_CMD_STOP:
					// Command from main thread: the app's activity has been stopped.
					break;

				case APP_CMD_DESTROY:
					// Command from main thread: the app's activity is being destroyed,
					// and waiting for the app thread to clean up and exit before proceeding.
					m_eventQueue.postExitEvent();
					break;
			}
		}

		int32_t onInputEvent(AInputEvent* _event)
		{
			BX_UNUSED(_event);
			return 0;
		}

		static void onAppCmdCB(struct android_app* _app, int32_t _cmd)
		{
			Context* self = (Context*)_app->userData;
			self->onAppCmd(_cmd);
		}

		static int32_t onInputEventCB(struct android_app* _app, AInputEvent* _event)
		{
			Context* self = (Context*)_app->userData;
			return self->onInputEvent(_event);
		}

		MainThreadEntry m_mte;
		bx::Thread m_thread;

		EventQueue m_eventQueue;

		ANativeWindow* m_window;
		android_app* m_app;
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
		BX_UNUSED(_width, _height);
	}

	void setWindowTitle(const char* _title)
	{
		BX_UNUSED(_title);
	}

	void toggleWindowFrame()
	{
	}

	void setMouseLock(bool _lock)
	{
		BX_UNUSED(_lock);
	}

	int32_t MainThreadEntry::threadFunc(void* _userData)
	{
		int32_t result = chdir("/sdcard/bgfx/examples/runtime");
		BX_CHECK(0 == result, "Failed to chdir to dir. android.permission.WRITE_EXTERNAL_STORAGE?", errno);

		MainThreadEntry* self = (MainThreadEntry*)_userData;
		result = main(self->m_argc, self->m_argv);
//		PostMessage(s_ctx.m_hwnd, WM_QUIT, 0, 0);
		return result;
	}

} // namespace entry

extern "C" void android_main(android_app* _app)
{
	using namespace entry;
	s_ctx.run(_app);
}

#endif // ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_ANDROID
