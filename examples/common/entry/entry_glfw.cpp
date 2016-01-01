/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_GLFW

#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <bgfx/bgfxplatform.h>
#include "dbg.h"

// This is just trivial implementation of GLFW3 integration.
// It's here just for testing purpose.

namespace entry
{
	static void errorCb(int _error, const char* _description)
	{
		DBG("GLFW error %d: %s", _error, _description);
	}

	struct Context
	{
		Context()
		{
		}

		int run(int _argc, char** _argv)
		{
			glfwSetErrorCallback(errorCb);

			glfwInit();
			m_window = glfwCreateWindow(1280, 720, "bgfx", NULL, NULL);
			glfwMakeContextCurrent(m_window);

			glfwSetKeyCallback(m_window, keyCb);

			bgfx::glfwSetWindow(m_window);
			int result = main(_argc, _argv);

			glfwDestroyWindow(m_window);
			glfwTerminate();
			return result;
		}

		static void keyCb(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);

		EventQueue m_eventQueue;

		GLFWwindow* m_window;
	};

	Context s_ctx;

	void Context::keyCb(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
	{
		BX_UNUSED(_window, _scancode, _mods);
		if (_key    == GLFW_KEY_Q
		&&  _action == GLFW_PRESS
		&&  _mods   == GLFW_MOD_CONTROL)
		{
			s_ctx.m_eventQueue.postExitEvent();
		}
	}

	const Event* poll()
	{
		glfwPollEvents();

		if (glfwWindowShouldClose(s_ctx.m_window) )
		{
			s_ctx.m_eventQueue.postExitEvent();
		}
		return s_ctx.m_eventQueue.poll();
	}

	const Event* poll(WindowHandle _handle)
	{
		return s_ctx.m_eventQueue.poll(_handle);
	}

	void release(const Event* _event)
	{
		s_ctx.m_eventQueue.release(_event);
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
}

int main(int _argc, char** _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // ENTRY_CONFIG_USE_GLFW
