/*
 * Copyright 2011-2023 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_GLFW

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#if GLFW_VERSION_MINOR < 2
#	error "GLFW 3.2 or later is required"
#endif // GLFW_VERSION_MINOR < 2

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	if ENTRY_CONFIG_USE_WAYLAND
#		include <wayland-egl.h>
#		define GLFW_EXPOSE_NATIVE_WAYLAND
#	else
#		define GLFW_EXPOSE_NATIVE_X11
#		define GLFW_EXPOSE_NATIVE_GLX
#	endif
#elif BX_PLATFORM_OSX
#	define GLFW_EXPOSE_NATIVE_COCOA
#	define GLFW_EXPOSE_NATIVE_NSGL
#elif BX_PLATFORM_WINDOWS
#	define GLFW_EXPOSE_NATIVE_WIN32
#	define GLFW_EXPOSE_NATIVE_WGL
#endif //
#include <GLFW/glfw3native.h>

#include <bgfx/platform.h>

#include <bx/handlealloc.h>
#include <bx/thread.h>
#include <bx/mutex.h>
#include <tinystl/string.h>

#include "dbg.h"

namespace entry
{
	static void* glfwNativeWindowHandle(GLFWwindow* _window)
	{
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
# 		if ENTRY_CONFIG_USE_WAYLAND
		wl_egl_window *win_impl = (wl_egl_window*)glfwGetWindowUserPointer(_window);
		if(!win_impl)
		{
			int width, height;
			glfwGetWindowSize(_window, &width, &height);
			struct wl_surface* surface = (struct wl_surface*)glfwGetWaylandWindow(_window);
			if(!surface)
				return nullptr;
			win_impl = wl_egl_window_create(surface, width, height);
			glfwSetWindowUserPointer(_window, (void*)(uintptr_t)win_impl);
		}
		return (void*)(uintptr_t)win_impl;
#		else
		return (void*)(uintptr_t)glfwGetX11Window(_window);
#		endif
#	elif BX_PLATFORM_OSX
		return glfwGetCocoaWindow(_window);
#	elif BX_PLATFORM_WINDOWS
		return glfwGetWin32Window(_window);
#	endif // BX_PLATFORM_
	}

	static void glfwDestroyWindowImpl(GLFWwindow *_window)
	{
		if(!_window)
			return;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
		wl_egl_window *win_impl = (wl_egl_window*)glfwGetWindowUserPointer(_window);
		if(win_impl)
		{
			glfwSetWindowUserPointer(_window, nullptr);
			wl_egl_window_destroy(win_impl);
		}
#		endif
#	endif
		glfwDestroyWindow(_window);
	}

	static uint8_t translateKeyModifiers(int _glfw)
	{
		uint8_t modifiers = 0;

		if (_glfw & GLFW_MOD_ALT)
		{
			modifiers |= Modifier::LeftAlt;
		}

		if (_glfw & GLFW_MOD_CONTROL)
		{
			modifiers |= Modifier::LeftCtrl;
		}

		if (_glfw & GLFW_MOD_SUPER)
		{
			modifiers |= Modifier::LeftMeta;
		}

		if (_glfw & GLFW_MOD_SHIFT)
		{
			modifiers |= Modifier::LeftShift;
		}

		return modifiers;
	}

	static Key::Enum s_translateKey[GLFW_KEY_LAST + 1];

	static Key::Enum translateKey(int _key)
	{
		return s_translateKey[_key];
	}

	static MouseButton::Enum translateMouseButton(int _button)
	{
		if (_button == GLFW_MOUSE_BUTTON_LEFT)
		{
			return MouseButton::Left;
		}
		else if (_button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			return MouseButton::Right;
		}

		return MouseButton::Middle;
	}

	static GamepadAxis::Enum translateGamepadAxis(int _axis)
	{
		// HACK: Map XInput 360 controller until GLFW gamepad API

		static GamepadAxis::Enum axes[] =
		{
			GamepadAxis::LeftX,
			GamepadAxis::LeftY,
			GamepadAxis::RightX,
			GamepadAxis::RightY,
			GamepadAxis::LeftZ,
			GamepadAxis::RightZ,
		};
		return axes[_axis];
	}

	static Key::Enum translateGamepadButton(int _button)
	{
		// HACK: Map XInput 360 controller until GLFW gamepad API

		static Key::Enum buttons[] =
		{
			Key::GamepadA,
			Key::GamepadB,
			Key::GamepadX,
			Key::GamepadY,
			Key::GamepadShoulderL,
			Key::GamepadShoulderR,
			Key::GamepadBack,
			Key::GamepadStart,
			Key::GamepadThumbL,
			Key::GamepadThumbR,
			Key::GamepadUp,
			Key::GamepadRight,
			Key::GamepadDown,
			Key::GamepadLeft,
			Key::GamepadGuide,
		};
		return buttons[_button];
	}

	struct GamepadGLFW
	{
		GamepadGLFW()
			: m_connected(false)
		{
			bx::memSet(m_axes, 0, sizeof(m_axes));
			bx::memSet(m_buttons, 0, sizeof(m_buttons));
		}

		void update(EventQueue& _eventQueue)
		{
			int numButtons, numAxes;
			const unsigned char* buttons = glfwGetJoystickButtons(m_handle.idx, &numButtons);
			const float* axes = glfwGetJoystickAxes(m_handle.idx, &numAxes);

			if (NULL == buttons || NULL == axes)
			{
				return;
			}

			if (numAxes > GamepadAxis::Count)
			{
				numAxes = GamepadAxis::Count;
			}

			if (numButtons > Key::Count - Key::GamepadA)
			{
				numButtons = Key::Count - Key::GamepadA;
			}

			WindowHandle defaultWindow = { 0 };

			for (int ii = 0; ii < numAxes; ++ii)
			{
				GamepadAxis::Enum axis = translateGamepadAxis(ii);
				int32_t value = (int32_t) (axes[ii] * 32768.f);
				if (GamepadAxis::LeftY == axis || GamepadAxis::RightY == axis)
				{
					value = -value;
				}

				if (m_axes[ii] != value)
				{
					m_axes[ii] = value;
					_eventQueue.postAxisEvent(defaultWindow
						, m_handle
						, axis
						, value);
				}
			}

			for (int ii = 0; ii < numButtons; ++ii)
			{
				Key::Enum key = translateGamepadButton(ii);
				if (m_buttons[ii] != buttons[ii])
				{
					m_buttons[ii] = buttons[ii];
					_eventQueue.postKeyEvent(defaultWindow
						, key
						, 0
						, buttons[ii] != 0);
				}
			}
		}

		bool m_connected;
		GamepadHandle m_handle;
		int32_t m_axes[GamepadAxis::Count];
		uint8_t m_buttons[Key::Count - Key::GamepadA];
	};

	struct MainThreadEntry
	{
		int m_argc;
		const char* const* m_argv;

		static int32_t threadFunc(bx::Thread* _thread, void* _userData);
	};

	enum MsgType
	{
		GLFW_WINDOW_CREATE,
		GLFW_WINDOW_DESTROY,
		GLFW_WINDOW_SET_TITLE,
		GLFW_WINDOW_SET_POS,
		GLFW_WINDOW_SET_SIZE,
		GLFW_WINDOW_TOGGLE_FRAME,
		GLFW_WINDOW_TOGGLE_FULL_SCREEN,
		GLFW_WINDOW_MOUSE_LOCK,
	};

	struct Msg
	{
		Msg(MsgType _type)
			: m_type(_type)
			, m_x(0)
			, m_y(0)
			, m_width(0)
			, m_height(0)
			, m_value(false)
		{
		}

		MsgType  m_type;
		int32_t  m_x;
		int32_t  m_y;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_flags;
		bool	 m_value;
		tinystl::string m_title;
		WindowHandle m_handle;
	};

	static void errorCb(int _error, const char* _description)
	{
		DBG("GLFW error %d: %s", _error, _description);
	}

	static void joystickCb(int _jid, int _action);

	// Based on cutef8 by Jeff Bezanson (Public Domain)
	static uint8_t encodeUTF8(uint8_t _chars[4], uint32_t _scancode)
	{
		uint8_t length = 0;

		if (_scancode < 0x80)
		{
			_chars[length++] = (char) _scancode;
		}
		else if (_scancode < 0x800)
		{
			_chars[length++] =  (_scancode >>  6)         | 0xc0;
			_chars[length++] =  (_scancode        & 0x3f) | 0x80;
		}
		else if (_scancode < 0x10000)
		{
			_chars[length++] =  (_scancode >> 12)         | 0xe0;
			_chars[length++] = ((_scancode >>  6) & 0x3f) | 0x80;
			_chars[length++] =  (_scancode        & 0x3f) | 0x80;
		}
		else if (_scancode < 0x110000)
		{
			_chars[length++] =  (_scancode >> 18)         | 0xf0;
			_chars[length++] = ((_scancode >> 12) & 0x3f) | 0x80;
			_chars[length++] = ((_scancode >>  6) & 0x3f) | 0x80;
			_chars[length++] =  (_scancode        & 0x3f) | 0x80;
		}

		return length;
	}

	struct Context
	{
		Context()
			: m_msgs(getAllocator() )
			, m_scrollPos(0.0f)
		{
			bx::memSet(s_translateKey, 0, sizeof(s_translateKey));
			s_translateKey[GLFW_KEY_ESCAPE]       = Key::Esc;
			s_translateKey[GLFW_KEY_ENTER]        = Key::Return;
			s_translateKey[GLFW_KEY_TAB]          = Key::Tab;
			s_translateKey[GLFW_KEY_BACKSPACE]    = Key::Backspace;
			s_translateKey[GLFW_KEY_SPACE]        = Key::Space;
			s_translateKey[GLFW_KEY_UP]           = Key::Up;
			s_translateKey[GLFW_KEY_DOWN]         = Key::Down;
			s_translateKey[GLFW_KEY_LEFT]         = Key::Left;
			s_translateKey[GLFW_KEY_RIGHT]        = Key::Right;
			s_translateKey[GLFW_KEY_PAGE_UP]      = Key::PageUp;
			s_translateKey[GLFW_KEY_PAGE_DOWN]    = Key::PageDown;
			s_translateKey[GLFW_KEY_HOME]         = Key::Home;
			s_translateKey[GLFW_KEY_END]          = Key::End;
			s_translateKey[GLFW_KEY_PRINT_SCREEN] = Key::Print;
			s_translateKey[GLFW_KEY_KP_ADD]       = Key::Plus;
			s_translateKey[GLFW_KEY_EQUAL]        = Key::Plus;
			s_translateKey[GLFW_KEY_KP_SUBTRACT]  = Key::Minus;
			s_translateKey[GLFW_KEY_MINUS]        = Key::Minus;
			s_translateKey[GLFW_KEY_COMMA]        = Key::Comma;
			s_translateKey[GLFW_KEY_PERIOD]       = Key::Period;
			s_translateKey[GLFW_KEY_SLASH]        = Key::Slash;
			s_translateKey[GLFW_KEY_F1]           = Key::F1;
			s_translateKey[GLFW_KEY_F2]           = Key::F2;
			s_translateKey[GLFW_KEY_F3]           = Key::F3;
			s_translateKey[GLFW_KEY_F4]           = Key::F4;
			s_translateKey[GLFW_KEY_F5]           = Key::F5;
			s_translateKey[GLFW_KEY_F6]           = Key::F6;
			s_translateKey[GLFW_KEY_F7]           = Key::F7;
			s_translateKey[GLFW_KEY_F8]           = Key::F8;
			s_translateKey[GLFW_KEY_F9]           = Key::F9;
			s_translateKey[GLFW_KEY_F10]          = Key::F10;
			s_translateKey[GLFW_KEY_F11]          = Key::F11;
			s_translateKey[GLFW_KEY_F12]          = Key::F12;
			s_translateKey[GLFW_KEY_KP_0]         = Key::NumPad0;
			s_translateKey[GLFW_KEY_KP_1]         = Key::NumPad1;
			s_translateKey[GLFW_KEY_KP_2]         = Key::NumPad2;
			s_translateKey[GLFW_KEY_KP_3]         = Key::NumPad3;
			s_translateKey[GLFW_KEY_KP_4]         = Key::NumPad4;
			s_translateKey[GLFW_KEY_KP_5]         = Key::NumPad5;
			s_translateKey[GLFW_KEY_KP_6]         = Key::NumPad6;
			s_translateKey[GLFW_KEY_KP_7]         = Key::NumPad7;
			s_translateKey[GLFW_KEY_KP_8]         = Key::NumPad8;
			s_translateKey[GLFW_KEY_KP_9]         = Key::NumPad9;
			s_translateKey[GLFW_KEY_0]            = Key::Key0;
			s_translateKey[GLFW_KEY_1]            = Key::Key1;
			s_translateKey[GLFW_KEY_2]            = Key::Key2;
			s_translateKey[GLFW_KEY_3]            = Key::Key3;
			s_translateKey[GLFW_KEY_4]            = Key::Key4;
			s_translateKey[GLFW_KEY_5]            = Key::Key5;
			s_translateKey[GLFW_KEY_6]            = Key::Key6;
			s_translateKey[GLFW_KEY_7]            = Key::Key7;
			s_translateKey[GLFW_KEY_8]            = Key::Key8;
			s_translateKey[GLFW_KEY_9]            = Key::Key9;
			s_translateKey[GLFW_KEY_A]            = Key::KeyA;
			s_translateKey[GLFW_KEY_B]            = Key::KeyB;
			s_translateKey[GLFW_KEY_C]            = Key::KeyC;
			s_translateKey[GLFW_KEY_D]            = Key::KeyD;
			s_translateKey[GLFW_KEY_E]            = Key::KeyE;
			s_translateKey[GLFW_KEY_F]            = Key::KeyF;
			s_translateKey[GLFW_KEY_G]            = Key::KeyG;
			s_translateKey[GLFW_KEY_H]            = Key::KeyH;
			s_translateKey[GLFW_KEY_I]            = Key::KeyI;
			s_translateKey[GLFW_KEY_J]            = Key::KeyJ;
			s_translateKey[GLFW_KEY_K]            = Key::KeyK;
			s_translateKey[GLFW_KEY_L]            = Key::KeyL;
			s_translateKey[GLFW_KEY_M]            = Key::KeyM;
			s_translateKey[GLFW_KEY_N]            = Key::KeyN;
			s_translateKey[GLFW_KEY_O]            = Key::KeyO;
			s_translateKey[GLFW_KEY_P]            = Key::KeyP;
			s_translateKey[GLFW_KEY_Q]            = Key::KeyQ;
			s_translateKey[GLFW_KEY_R]            = Key::KeyR;
			s_translateKey[GLFW_KEY_S]            = Key::KeyS;
			s_translateKey[GLFW_KEY_T]            = Key::KeyT;
			s_translateKey[GLFW_KEY_U]            = Key::KeyU;
			s_translateKey[GLFW_KEY_V]            = Key::KeyV;
			s_translateKey[GLFW_KEY_W]            = Key::KeyW;
			s_translateKey[GLFW_KEY_X]            = Key::KeyX;
			s_translateKey[GLFW_KEY_Y]            = Key::KeyY;
			s_translateKey[GLFW_KEY_Z]            = Key::KeyZ;
		}

		int run(int _argc, const char* const* _argv)
		{
			m_mte.m_argc = _argc;
			m_mte.m_argv = _argv;

			glfwSetErrorCallback(errorCb);

			if (!glfwInit() )
			{
				DBG("glfwInit failed!");
				return bx::kExitFailure;
			}

			glfwSetJoystickCallback(joystickCb);

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			WindowHandle handle = { m_windowAlloc.alloc() };
			m_window[0] = glfwCreateWindow(ENTRY_DEFAULT_WIDTH
				, ENTRY_DEFAULT_HEIGHT
				, "bgfx"
				, NULL
				, NULL
				);

			if (!m_window[0])
			{
				DBG("glfwCreateWindow failed!");
				glfwTerminate();
				return bx::kExitFailure;
			}

			glfwSetKeyCallback(m_window[0], keyCb);
			glfwSetCharCallback(m_window[0], charCb);
			glfwSetScrollCallback(m_window[0], scrollCb);
			glfwSetCursorPosCallback(m_window[0], cursorPosCb);
			glfwSetMouseButtonCallback(m_window[0], mouseButtonCb);
			glfwSetWindowSizeCallback(m_window[0], windowSizeCb);
			glfwSetDropCallback(m_window[0], dropFileCb);

			m_eventQueue.postSizeEvent(handle, ENTRY_DEFAULT_WIDTH, ENTRY_DEFAULT_HEIGHT);

			for (uint32_t ii = 0; ii < ENTRY_CONFIG_MAX_GAMEPADS; ++ii)
			{
				m_gamepad[ii].m_handle.idx = ii;
				if (glfwJoystickPresent(ii))
				{
					m_gamepad[ii].m_connected = true;
					m_eventQueue.postGamepadEvent(handle
						, m_gamepad[ii].m_handle
						, true);
				}
			}

			m_thread.init(MainThreadEntry::threadFunc, &m_mte);

			while (NULL != m_window[0]
			&&     !glfwWindowShouldClose(m_window[0]))
			{
				glfwWaitEventsTimeout(0.016);

				for (uint32_t ii = 0; ii < ENTRY_CONFIG_MAX_GAMEPADS; ++ii)
				{
					if (m_gamepad[ii].m_connected)
					{
						m_gamepad[ii].update(m_eventQueue);
					}
				}

				while (Msg* msg = m_msgs.pop())
				{
					switch (msg->m_type)
					{
					case GLFW_WINDOW_CREATE:
						{
							GLFWwindow* window = glfwCreateWindow(msg->m_width
								, msg->m_height
								, msg->m_title.c_str()
								, NULL
								, NULL);
							if (!window)
							{
								break;
							}

							glfwSetWindowPos(window, msg->m_x, msg->m_y);
							if (msg->m_flags & ENTRY_WINDOW_FLAG_ASPECT_RATIO)
							{
								glfwSetWindowAspectRatio(window, msg->m_width, msg->m_height);
							}

							glfwSetKeyCallback(window, keyCb);
							glfwSetCharCallback(window, charCb);
							glfwSetScrollCallback(window, scrollCb);
							glfwSetCursorPosCallback(window, cursorPosCb);
							glfwSetMouseButtonCallback(window, mouseButtonCb);
							glfwSetWindowSizeCallback(window, windowSizeCb);
							glfwSetDropCallback(window, dropFileCb);

							m_window[msg->m_handle.idx] = window;
							m_eventQueue.postSizeEvent(msg->m_handle, msg->m_width, msg->m_height);
							m_eventQueue.postWindowEvent(msg->m_handle, glfwNativeWindowHandle(window));
						}
						break;

					case GLFW_WINDOW_DESTROY:
						{
							if (isValid(msg->m_handle) )
							{
								GLFWwindow* window = m_window[msg->m_handle.idx];
								m_eventQueue.postWindowEvent(msg->m_handle);
								glfwDestroyWindowImpl(window);
								m_window[msg->m_handle.idx] = NULL;
							}
						}
						break;

					case GLFW_WINDOW_SET_TITLE:
						{
							GLFWwindow* window = m_window[msg->m_handle.idx];
							glfwSetWindowTitle(window, msg->m_title.c_str());
						}
						break;

					case GLFW_WINDOW_SET_POS:
						{
							GLFWwindow* window = m_window[msg->m_handle.idx];
							glfwSetWindowPos(window, msg->m_x, msg->m_y);
						}
						break;

					case GLFW_WINDOW_SET_SIZE:
						{
							GLFWwindow* window = m_window[msg->m_handle.idx];
							glfwSetWindowSize(window, msg->m_width, msg->m_height);
						}
						break;

					case GLFW_WINDOW_TOGGLE_FRAME:
						{
							// Wait for glfwSetWindowDecorated to exist
						}
						break;

					case GLFW_WINDOW_TOGGLE_FULL_SCREEN:
						{
							GLFWwindow* window = m_window[msg->m_handle.idx];
							if (glfwGetWindowMonitor(window) )
							{
								glfwSetWindowMonitor(window
									, NULL
									, m_oldX
									, m_oldY
									, m_oldWidth
									, m_oldHeight
									, 0
									);
							}
							else
							{
								GLFWmonitor* monitor = glfwGetPrimaryMonitor();
								if (NULL != monitor)
								{
									glfwGetWindowPos(window, &m_oldX, &m_oldY);
									glfwGetWindowSize(window, &m_oldWidth, &m_oldHeight);

									const GLFWvidmode* mode = glfwGetVideoMode(monitor);
									glfwSetWindowMonitor(window
										, monitor
										, 0
										, 0
										, mode->width
										, mode->height
										, mode->refreshRate
										);
								}

							}
						}
						break;

					case GLFW_WINDOW_MOUSE_LOCK:
						{
							GLFWwindow* window = m_window[msg->m_handle.idx];
							if (msg->m_value)
							{
								glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
							}
							else
							{
								glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
							}
						}
						break;
					}

					delete msg;
				}
			}

			m_eventQueue.postExitEvent();
			m_thread.shutdown();

			glfwDestroyWindowImpl(m_window[0]);
			glfwTerminate();

			return m_thread.getExitCode();
		}

		WindowHandle findHandle(GLFWwindow* _window)
		{
			bx::MutexScope scope(m_lock);
			for (uint32_t ii = 0, num = m_windowAlloc.getNumHandles(); ii < num; ++ii)
			{
				uint16_t idx = m_windowAlloc.getHandleAt(ii);
				if (_window == m_window[idx])
				{
					WindowHandle handle = { idx };
					return handle;
				}
			}

			WindowHandle invalid = { UINT16_MAX };
			return invalid;
		}

		static void keyCb(GLFWwindow* _window, int32_t _key, int32_t _scancode, int32_t _action, int32_t _mods);
		static void charCb(GLFWwindow* _window, uint32_t _scancode);
		static void scrollCb(GLFWwindow* _window, double _dx, double _dy);
		static void cursorPosCb(GLFWwindow* _window, double _mx, double _my);
		static void mouseButtonCb(GLFWwindow* _window, int32_t _button, int32_t _action, int32_t _mods);
		static void windowSizeCb(GLFWwindow* _window, int32_t _width, int32_t _height);
		static void dropFileCb(GLFWwindow* _window, int32_t _count, const char** _filePaths);

		MainThreadEntry m_mte;
		bx::Thread m_thread;

		EventQueue m_eventQueue;
		bx::Mutex m_lock;

		GLFWwindow* m_window[ENTRY_CONFIG_MAX_WINDOWS];
		bx::HandleAllocT<ENTRY_CONFIG_MAX_WINDOWS> m_windowAlloc;

		GamepadGLFW m_gamepad[ENTRY_CONFIG_MAX_GAMEPADS];

		bx::SpScUnboundedQueueT<Msg> m_msgs;

		int32_t m_oldX;
		int32_t m_oldY;
		int32_t m_oldWidth;
		int32_t m_oldHeight;

		double m_scrollPos;
	};

	Context s_ctx;

	void Context::keyCb(GLFWwindow* _window, int32_t _key, int32_t _scancode, int32_t _action, int32_t _mods)
	{
		BX_UNUSED(_scancode);
		if (_key == GLFW_KEY_UNKNOWN)
		{
			return;
		}
		WindowHandle handle = s_ctx.findHandle(_window);
		int mods = translateKeyModifiers(_mods);
		Key::Enum key = translateKey(_key);
		bool down = (_action == GLFW_PRESS || _action == GLFW_REPEAT);
		s_ctx.m_eventQueue.postKeyEvent(handle, key, mods, down);
	}

	void Context::charCb(GLFWwindow* _window, uint32_t _scancode)
	{
		WindowHandle handle = s_ctx.findHandle(_window);
		uint8_t chars[4];
		uint8_t length = encodeUTF8(chars, _scancode);
		if (!length)
		{
			return;
		}

		s_ctx.m_eventQueue.postCharEvent(handle, length, chars);
	}

	void Context::scrollCb(GLFWwindow* _window, double _dx, double _dy)
	{
		BX_UNUSED(_dx);
		WindowHandle handle = s_ctx.findHandle(_window);
		double mx, my;
		glfwGetCursorPos(_window, &mx, &my);
		s_ctx.m_scrollPos += _dy;
		s_ctx.m_eventQueue.postMouseEvent(handle
			, (int32_t) mx
			, (int32_t) my
			, (int32_t) s_ctx.m_scrollPos
			);
	}

	void Context::cursorPosCb(GLFWwindow* _window, double _mx, double _my)
	{
		WindowHandle handle = s_ctx.findHandle(_window);
		s_ctx.m_eventQueue.postMouseEvent(handle
			, (int32_t) _mx
			, (int32_t) _my
			, (int32_t) s_ctx.m_scrollPos
			);
	}

	void Context::mouseButtonCb(GLFWwindow* _window, int32_t _button, int32_t _action, int32_t _mods)
	{
		BX_UNUSED(_mods);
		WindowHandle handle = s_ctx.findHandle(_window);
		bool down = _action == GLFW_PRESS;
		double mx, my;
		glfwGetCursorPos(_window, &mx, &my);
		s_ctx.m_eventQueue.postMouseEvent(handle
			, (int32_t) mx
			, (int32_t) my
			, (int32_t) s_ctx.m_scrollPos
			, translateMouseButton(_button)
			, down
			);
	}

	void Context::windowSizeCb(GLFWwindow* _window, int32_t _width, int32_t _height)
	{
		WindowHandle handle = s_ctx.findHandle(_window);
		s_ctx.m_eventQueue.postSizeEvent(handle, _width, _height);
	}

	void Context::dropFileCb(GLFWwindow* _window, int32_t _count, const char** _filePaths)
	{
		WindowHandle handle = s_ctx.findHandle(_window);
		for (int32_t ii = 0; ii < _count; ++ii)
		{
			s_ctx.m_eventQueue.postDropFileEvent(handle, _filePaths[ii]);
		}
	}

	static void joystickCb(int _jid, int _action)
	{
		if (_jid >= ENTRY_CONFIG_MAX_GAMEPADS)
		{
			return;
		}

		WindowHandle defaultWindow = { 0 };
		GamepadHandle handle = { (uint16_t) _jid };

		if (_action == GLFW_CONNECTED)
		{
			s_ctx.m_gamepad[_jid].m_connected = true;
			s_ctx.m_eventQueue.postGamepadEvent(defaultWindow, handle, true);
		}
		else if (_action == GLFW_DISCONNECTED)
		{
			s_ctx.m_gamepad[_jid].m_connected = false;
			s_ctx.m_eventQueue.postGamepadEvent(defaultWindow, handle, false);
		}
	}

	const Event* poll()
	{
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
		Msg* msg = new Msg(GLFW_WINDOW_CREATE);
		msg->m_x = _x;
		msg->m_y = _y;
		msg->m_width = _width;
		msg->m_height = _height;
		msg->m_flags = _flags;
		msg->m_title = _title;
		msg->m_handle.idx = s_ctx.m_windowAlloc.alloc();
		s_ctx.m_msgs.push(msg);
		return msg->m_handle;
	}

	void destroyWindow(WindowHandle _handle)
	{
		Msg* msg = new Msg(GLFW_WINDOW_DESTROY);
		msg->m_handle = _handle;
		s_ctx.m_msgs.push(msg);
	}

	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y)
	{
		Msg* msg = new Msg(GLFW_WINDOW_SET_POS);
		msg->m_x = _x;
		msg->m_y = _y;
		msg->m_handle = _handle;
		s_ctx.m_msgs.push(msg);
	}

	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height)
	{
		Msg* msg = new Msg(GLFW_WINDOW_SET_SIZE);
		msg->m_width = _width;
		msg->m_height = _height;
		msg->m_handle = _handle;
		s_ctx.m_msgs.push(msg);
	}

	void setWindowTitle(WindowHandle _handle, const char* _title)
	{
		Msg* msg = new Msg(GLFW_WINDOW_SET_TITLE);
		msg->m_title = _title;
		msg->m_handle = _handle;
		s_ctx.m_msgs.push(msg);
	}

	void setWindowFlags(WindowHandle _handle, uint32_t _flags, bool _enabled)
	{
		BX_UNUSED(_handle, _flags, _enabled);
	}

	void toggleFullscreen(WindowHandle _handle)
	{
		Msg* msg = new Msg(GLFW_WINDOW_TOGGLE_FULL_SCREEN);
		msg->m_handle = _handle;
		s_ctx.m_msgs.push(msg);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		Msg* msg = new Msg(GLFW_WINDOW_MOUSE_LOCK);
		msg->m_value = _lock;
		msg->m_handle = _handle;
		s_ctx.m_msgs.push(msg);
	}

	void* getNativeWindowHandle(WindowHandle _handle)
	{
		return glfwNativeWindowHandle(s_ctx.m_window[_handle.idx]);
	}

	void* getNativeDisplayHandle()
	{
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
		return glfwGetWaylandDisplay();
#		else
		return glfwGetX11Display();
#		endif // ENTRY_CONFIG_USE_WAYLAND
#	else
		return NULL;
#	endif // BX_PLATFORM_*
	}

	bgfx::NativeWindowHandleType::Enum getNativeWindowHandleType(WindowHandle _handle)
	{
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
		return bgfx::NativeWindowHandleType::Wayland;
#		else
		return bgfx::NativeWindowHandleType::Default;
#		endif // ENTRY_CONFIG_USE_WAYLAND
#	else
		return bgfx::NativeWindowHandleType::Default;
#	endif // BX_PLATFORM_*
	}

	int32_t MainThreadEntry::threadFunc(bx::Thread* _thread, void* _userData)
	{
		BX_UNUSED(_thread);

		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = main(self->m_argc, self->m_argv);

		// Destroy main window on exit...
		Msg* msg = new Msg(GLFW_WINDOW_DESTROY);
		msg->m_handle.idx = 0;
		s_ctx.m_msgs.push(msg);

		return result;
	}
}

int main(int _argc, const char* const* _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // ENTRY_CONFIG_USE_GLFW
