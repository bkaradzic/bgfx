/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_SDL

#if BX_PLATFORM_WINDOWS
#	define SDL_MAIN_HANDLED
#endif // BX_PLATFORM_WINDOWS

#include <SDL2/SDL.h>
#include <bgfxplatform.h>

#include <stdio.h>
#include <bx/thread.h>
#include <bx/handlealloc.h>
#include <tinystl/allocator.h>
#include <tinystl/string.h>

namespace entry
{
	static uint8_t translateKeyModifiers(uint16_t _sdl)
	{
		uint8_t modifiers = 0;
		modifiers |= _sdl & KMOD_LALT   ? Modifier::LeftAlt    : 0;
		modifiers |= _sdl & KMOD_RALT   ? Modifier::RightAlt   : 0;
		modifiers |= _sdl & KMOD_LCTRL  ? Modifier::LeftCtrl   : 0;
		modifiers |= _sdl & KMOD_RCTRL  ? Modifier::RightCtrl  : 0;
		modifiers |= _sdl & KMOD_LSHIFT ? Modifier::LeftShift  : 0;
		modifiers |= _sdl & KMOD_RSHIFT ? Modifier::RightShift : 0;
		modifiers |= _sdl & KMOD_LGUI   ? Modifier::LeftMeta   : 0;
		modifiers |= _sdl & KMOD_RGUI   ? Modifier::RightMeta  : 0;
		return modifiers;
	}

	static uint8_t s_translateKey[256];

	static void initTranslateKey(uint16_t _sdl, Key::Enum _key)
	{
		BX_CHECK(_sdl < BX_COUNTOF(s_translateKey), "Out of bounds %d.", _sdl);
		s_translateKey[_sdl&0xff] = (uint8_t)_key;
	}

	static Key::Enum translateKey(SDL_Scancode _sdl)
	{
		return (Key::Enum)s_translateKey[_sdl&0xff];
	}

	struct MainThreadEntry
	{
		int m_argc;
		char** m_argv;

		static int32_t threadFunc(void* _userData);
	};

	///
	static void* sdlNativeWindowHandle(SDL_Window* _window)
	{
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi) )
		{
			return NULL;
		}

#	if BX_PLATFORM_LINUX || BX_PLATFORM_FREEBSD
		return (void*)wmi.info.x11.window;
#	elif BX_PLATFORM_OSX
		return wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
		return wmi.info.win.window;
#	endif // BX_PLATFORM_
	}

	struct Msg
	{
		Msg()
			: m_x(0)
			, m_y(0)
			, m_width(0)
			, m_height(0)
			, m_flags(0)
		{
		}

		int32_t  m_x;
		int32_t  m_y;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_flags;
		tinystl::string m_title;
	};

	static uint32_t s_userEventStart;

	enum SDL_USER_WINDOW
	{
		SDL_USER_WINDOW_CREATE,
		SDL_USER_WINDOW_DESTROY,
		SDL_USER_WINDOW_SET_TITLE,
		SDL_USER_WINDOW_SET_POS,
		SDL_USER_WINDOW_SET_SIZE,
		SDL_USER_WINDOW_TOGGLE_FRAME,
		SDL_USER_WINDOW_MOUSE_LOCK,
	};

	static void sdlPostEvent(SDL_USER_WINDOW _type, WindowHandle _handle, Msg* _msg = NULL, uint32_t _code = 0)
	{
		SDL_Event event;
		SDL_UserEvent& uev = event.user;
		uev.type = s_userEventStart + _type;

		union { void* p; WindowHandle h; } cast;
		cast.h = _handle;
		uev.data1 = cast.p;
		
		uev.data2 = _msg;
		uev.code = _code;
		SDL_PushEvent(&event);
	}

	static WindowHandle getWindowHandle(const SDL_UserEvent& _uev)
	{
		union { void* p; WindowHandle h; } cast;
		cast.p = _uev.data1;
		return cast.h;
	}

	struct Context
	{
		Context()
			: m_width(ENTRY_DEFAULT_WIDTH)
			, m_height(ENTRY_DEFAULT_HEIGHT)
			, m_aspectRatio(16.0f/9.0f)
			, m_mouseLock(false)
		{
			memset(s_translateKey, 0, sizeof(s_translateKey) );
			initTranslateKey(SDL_SCANCODE_ESCAPE,       Key::Esc);
			initTranslateKey(SDL_SCANCODE_RETURN,       Key::Return);
			initTranslateKey(SDL_SCANCODE_TAB,          Key::Tab);
			initTranslateKey(SDL_SCANCODE_BACKSPACE,    Key::Backspace);
			initTranslateKey(SDL_SCANCODE_SPACE,        Key::Space);
			initTranslateKey(SDL_SCANCODE_UP,           Key::Up);
			initTranslateKey(SDL_SCANCODE_DOWN,         Key::Down);
			initTranslateKey(SDL_SCANCODE_LEFT,         Key::Left);
			initTranslateKey(SDL_SCANCODE_RIGHT,        Key::Right);
			initTranslateKey(SDL_SCANCODE_PAGEUP,       Key::PageUp);
			initTranslateKey(SDL_SCANCODE_PAGEDOWN,     Key::PageDown);
			initTranslateKey(SDL_SCANCODE_HOME,         Key::Home);
			initTranslateKey(SDL_SCANCODE_END,          Key::End);
			initTranslateKey(SDL_SCANCODE_PRINTSCREEN,  Key::Print);
			initTranslateKey(SDL_SCANCODE_KP_PLUS,      Key::Plus);
			initTranslateKey(SDL_SCANCODE_KP_MINUS,     Key::Minus);
			initTranslateKey(SDL_SCANCODE_F1,           Key::F1);
			initTranslateKey(SDL_SCANCODE_F2,           Key::F2);
			initTranslateKey(SDL_SCANCODE_F3,           Key::F3);
			initTranslateKey(SDL_SCANCODE_F4,           Key::F4);
			initTranslateKey(SDL_SCANCODE_F5,           Key::F5);
			initTranslateKey(SDL_SCANCODE_F6,           Key::F6);
			initTranslateKey(SDL_SCANCODE_F7,           Key::F7);
			initTranslateKey(SDL_SCANCODE_F8,           Key::F8);
			initTranslateKey(SDL_SCANCODE_F9,           Key::F9);
			initTranslateKey(SDL_SCANCODE_F10,          Key::F10);
			initTranslateKey(SDL_SCANCODE_F11,          Key::F11);
			initTranslateKey(SDL_SCANCODE_F12,          Key::F12);
			initTranslateKey(SDL_SCANCODE_KP_0,         Key::NumPad0);
			initTranslateKey(SDL_SCANCODE_KP_1,         Key::NumPad1);
			initTranslateKey(SDL_SCANCODE_KP_2,         Key::NumPad2);
			initTranslateKey(SDL_SCANCODE_KP_3,         Key::NumPad3);
			initTranslateKey(SDL_SCANCODE_KP_4,         Key::NumPad4);
			initTranslateKey(SDL_SCANCODE_KP_5,         Key::NumPad5);
			initTranslateKey(SDL_SCANCODE_KP_6,         Key::NumPad6);
			initTranslateKey(SDL_SCANCODE_KP_7,         Key::NumPad7);
			initTranslateKey(SDL_SCANCODE_KP_8,         Key::NumPad8);
			initTranslateKey(SDL_SCANCODE_KP_9,         Key::NumPad9);
			initTranslateKey(SDL_SCANCODE_0,            Key::Key0);
			initTranslateKey(SDL_SCANCODE_1,            Key::Key1);
			initTranslateKey(SDL_SCANCODE_2,            Key::Key2);
			initTranslateKey(SDL_SCANCODE_3,            Key::Key3);
			initTranslateKey(SDL_SCANCODE_4,            Key::Key4);
			initTranslateKey(SDL_SCANCODE_5,            Key::Key5);
			initTranslateKey(SDL_SCANCODE_6,            Key::Key6);
			initTranslateKey(SDL_SCANCODE_7,            Key::Key7);
			initTranslateKey(SDL_SCANCODE_8,            Key::Key8);
			initTranslateKey(SDL_SCANCODE_9,            Key::Key9);
			initTranslateKey(SDL_SCANCODE_A,            Key::KeyA);
			initTranslateKey(SDL_SCANCODE_B,            Key::KeyB);
			initTranslateKey(SDL_SCANCODE_C,            Key::KeyC);
			initTranslateKey(SDL_SCANCODE_D,            Key::KeyD);
			initTranslateKey(SDL_SCANCODE_E,            Key::KeyE);
			initTranslateKey(SDL_SCANCODE_F,            Key::KeyF);
			initTranslateKey(SDL_SCANCODE_G,            Key::KeyG);
			initTranslateKey(SDL_SCANCODE_H,            Key::KeyH);
			initTranslateKey(SDL_SCANCODE_I,            Key::KeyI);
			initTranslateKey(SDL_SCANCODE_J,            Key::KeyJ);
			initTranslateKey(SDL_SCANCODE_K,            Key::KeyK);
			initTranslateKey(SDL_SCANCODE_L,            Key::KeyL);
			initTranslateKey(SDL_SCANCODE_M,            Key::KeyM);
			initTranslateKey(SDL_SCANCODE_N,            Key::KeyN);
			initTranslateKey(SDL_SCANCODE_O,            Key::KeyO);
			initTranslateKey(SDL_SCANCODE_P,            Key::KeyP);
			initTranslateKey(SDL_SCANCODE_Q,            Key::KeyQ);
			initTranslateKey(SDL_SCANCODE_R,            Key::KeyR);
			initTranslateKey(SDL_SCANCODE_S,            Key::KeyS);
			initTranslateKey(SDL_SCANCODE_T,            Key::KeyT);
			initTranslateKey(SDL_SCANCODE_U,            Key::KeyU);
			initTranslateKey(SDL_SCANCODE_V,            Key::KeyV);
			initTranslateKey(SDL_SCANCODE_W,            Key::KeyW);
			initTranslateKey(SDL_SCANCODE_X,            Key::KeyX);
			initTranslateKey(SDL_SCANCODE_Y,            Key::KeyY);
			initTranslateKey(SDL_SCANCODE_Z,            Key::KeyZ);
		}

		void run(int _argc, char** _argv)
		{
			m_mte.m_argc = _argc;
			m_mte.m_argv = _argv;

			SDL_Init(SDL_INIT_VIDEO);

			m_windowAlloc.alloc();
			m_window[0] = SDL_CreateWindow("bgfx"
							, SDL_WINDOWPOS_UNDEFINED
							, SDL_WINDOWPOS_UNDEFINED
							, m_width
							, m_height
							, SDL_WINDOW_SHOWN
							| SDL_WINDOW_RESIZABLE
							);

			m_flags[0] = 0
				| ENTRY_WINDOW_FLAG_ASPECT_RATIO
				| ENTRY_WINDOW_FLAG_FRAME
				;

			s_userEventStart = SDL_RegisterEvents(7);

			bgfx::sdlSetWindow(m_window[0]);
			bgfx::renderFrame();

			m_thread.init(MainThreadEntry::threadFunc, &m_mte);

			// Force window resolution...
			WindowHandle defaultWindow = { 0 };
			setWindowSize(defaultWindow, m_width, m_height, true);

			bool exit = false;
			SDL_Event event;
			while (!exit)
			{
				bgfx::renderFrame();

				while (SDL_PollEvent(&event) )
				{
					switch (event.type)
					{
					case SDL_QUIT:
						m_eventQueue.postExitEvent();
						exit = true;
						break;

					case SDL_MOUSEMOTION:
						{
							const SDL_MouseMotionEvent& mev = event.motion;
							WindowHandle handle = findHandle(mev.windowID);
							if (isValid(handle) )
							{
								m_eventQueue.postMouseEvent(handle, mev.x, mev.y, 0);
							}
						}
						break;

					case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
						{
							const SDL_MouseButtonEvent& mev = event.button;
							WindowHandle handle = findHandle(mev.windowID);
							if (isValid(handle) )
							{
								MouseButton::Enum button;
								switch (mev.button)
								{
								default:
								case SDL_BUTTON_LEFT:   button = MouseButton::Left;   break;
								case SDL_BUTTON_MIDDLE: button = MouseButton::Middle; break;
								case SDL_BUTTON_RIGHT:  button = MouseButton::Right;  break;
								}

								m_eventQueue.postMouseEvent(handle
									, mev.x
									, mev.y
									, 0
									, button
									, mev.type == SDL_MOUSEBUTTONDOWN
									);
							}
						}
						break;

					case SDL_KEYDOWN:
					case SDL_KEYUP:
						{
							const SDL_KeyboardEvent& kev = event.key;
							WindowHandle handle = findHandle(kev.windowID);
							if (isValid(handle) )
							{
								uint8_t modifiers = translateKeyModifiers(kev.keysym.mod);
								Key::Enum key = translateKey(kev.keysym.scancode);
								m_eventQueue.postKeyEvent(handle, key, modifiers, kev.state == SDL_PRESSED);
							}
						}
						break;

					case SDL_WINDOWEVENT:
						{
							const SDL_WindowEvent& wev = event.window;
							switch (wev.event)
							{
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
								{
									WindowHandle handle = findHandle(wev.windowID);
									setWindowSize(handle, wev.data1, wev.data2);
								}
								break;

							case SDL_WINDOWEVENT_SHOWN:
							case SDL_WINDOWEVENT_HIDDEN:
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_MOVED:
							case SDL_WINDOWEVENT_MINIMIZED:
							case SDL_WINDOWEVENT_MAXIMIZED:
							case SDL_WINDOWEVENT_RESTORED:
							case SDL_WINDOWEVENT_ENTER:
							case SDL_WINDOWEVENT_LEAVE:
							case SDL_WINDOWEVENT_FOCUS_GAINED:
							case SDL_WINDOWEVENT_FOCUS_LOST:
								break;

							case SDL_WINDOWEVENT_CLOSE:
								{
									WindowHandle handle = findHandle(wev.windowID);
									if (0 == handle.idx)
									{
										m_eventQueue.postExitEvent();
										exit = true;
									}
								}
								break;
							}
						}
						break;

					default:
						{
							const SDL_UserEvent& uev = event.user;
							switch (uev.type - s_userEventStart)
							{
							case SDL_USER_WINDOW_CREATE:
								{
									WindowHandle handle = getWindowHandle(uev);
									Msg* msg = (Msg*)uev.data2;

									m_window[handle.idx] = SDL_CreateWindow(msg->m_title.c_str()
																, msg->m_x
																, msg->m_y
																, msg->m_width
																, msg->m_height
																, SDL_WINDOW_SHOWN
																| SDL_WINDOW_RESIZABLE
																);

									m_flags[handle.idx] = msg->m_flags;

									void* nwh = sdlNativeWindowHandle(m_window[handle.idx]);
									if (NULL != nwh)
									{
										m_eventQueue.postWindowEvent(handle, nwh);
										m_eventQueue.postSizeEvent(handle, msg->m_width, msg->m_height);
									}

									delete msg;
								}
								break;

							case SDL_USER_WINDOW_DESTROY:
								{
									WindowHandle handle = getWindowHandle(uev);
									if (isValid(handle) )
									{
										m_eventQueue.postWindowEvent(handle);
										SDL_DestroyWindow(m_window[handle.idx]);
										m_window[handle.idx] = NULL;
									}
								}
								break;

							case SDL_USER_WINDOW_SET_TITLE:
								{
									WindowHandle handle = getWindowHandle(uev);
									Msg* msg = (Msg*)uev.data2;
									if (isValid(handle) )
									{
										SDL_SetWindowTitle(m_window[handle.idx], msg->m_title.c_str());
									}
									delete msg;
								}
								break;

							case SDL_USER_WINDOW_SET_POS:
								{
									WindowHandle handle = getWindowHandle(uev);
									Msg* msg = (Msg*)uev.data2;
									SDL_SetWindowPosition(m_window[handle.idx], msg->m_x, msg->m_y);
									delete msg;
								}
								break;

							case SDL_USER_WINDOW_SET_SIZE:
								{
									WindowHandle handle = getWindowHandle(uev);
									Msg* msg = (Msg*)uev.data2;
									if (isValid(handle) )
									{
										setWindowSize(handle, msg->m_width, msg->m_height);
									}
									delete msg;
								}
								break;

							case SDL_USER_WINDOW_TOGGLE_FRAME:
								{
									WindowHandle handle = getWindowHandle(uev);
									if (isValid(handle) )
									{
										m_flags[handle.idx] ^= ENTRY_WINDOW_FLAG_FRAME;
										SDL_SetWindowBordered(m_window[handle.idx], (SDL_bool)!!(m_flags[handle.idx] & ENTRY_WINDOW_FLAG_FRAME) );
									}
								}
								break;

							case SDL_USER_WINDOW_MOUSE_LOCK:
								{
									SDL_SetRelativeMouseMode(!!uev.code ? SDL_TRUE : SDL_FALSE);
								}
								break;

							default:
								break;
							}
						}
						break;
					}
				}
			}

			while (bgfx::RenderFrame::NoContext != bgfx::renderFrame() ) {};
			m_thread.shutdown();

			SDL_DestroyWindow(m_window[0]);
			SDL_Quit();
		}

		WindowHandle findHandle(uint32_t _windowId)
		{
			SDL_Window* window = SDL_GetWindowFromID(_windowId);
			return findHandle(window);
		}

		WindowHandle findHandle(SDL_Window* _window)
		{
			bx::LwMutexScope scope(m_lock);
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

		void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height, bool _force = false)
		{
			if (_width  != m_width
			||  _height != m_height
			||  _force)
			{
				m_width  = _width;
				m_height = _height;

				if (m_width < m_height)
				{
					float aspectRatio = 1.0f/m_aspectRatio;
					m_width = bx::uint32_max(ENTRY_DEFAULT_WIDTH/4, m_width);
					m_height = uint32_t(float(m_width)*aspectRatio);
				}
				else
				{
					float aspectRatio = m_aspectRatio;
					m_height = bx::uint32_max(ENTRY_DEFAULT_HEIGHT/4, m_height);
					m_width = uint32_t(float(m_height)*aspectRatio);
				}

				SDL_SetWindowSize(m_window[_handle.idx], m_width, m_height);
				m_eventQueue.postSizeEvent(_handle, m_width, m_height);
			}
		}

		MainThreadEntry m_mte;
		bx::Thread m_thread;

		EventQueue m_eventQueue;
		bx::LwMutex m_lock;

		bx::HandleAllocT<ENTRY_CONFIG_MAX_WINDOWS> m_windowAlloc;
		SDL_Window* m_window[ENTRY_CONFIG_MAX_WINDOWS];
		uint32_t m_flags[ENTRY_CONFIG_MAX_WINDOWS];

		uint32_t m_width;
		uint32_t m_height;
		float m_aspectRatio;

		int32_t m_mx;
		int32_t m_my;
		bool m_mouseLock;
	};

	static Context s_ctx;

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
		bx::LwMutexScope scope(s_ctx.m_lock);
		WindowHandle handle = { s_ctx.m_windowAlloc.alloc() };

		if (UINT16_MAX != handle.idx)
		{
			Msg* msg = new Msg;
			msg->m_x      = _x;
			msg->m_y      = _y;
			msg->m_width  = _width;
			msg->m_height = _height;
			msg->m_title  = _title;
			msg->m_flags  = _flags;

			sdlPostEvent(SDL_USER_WINDOW_CREATE, handle, msg);
		}

		return handle;
	}

	void destroyWindow(WindowHandle _handle)
	{
		if (UINT16_MAX != _handle.idx)
		{
			sdlPostEvent(SDL_USER_WINDOW_DESTROY, _handle);

			bx::LwMutexScope scope(s_ctx.m_lock);
			s_ctx.m_windowAlloc.free(_handle.idx);
		}
	}

	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y)
	{
		Msg* msg = new Msg;
		msg->m_x = _x;
		msg->m_y = _y;

		sdlPostEvent(SDL_USER_WINDOW_SET_POS, _handle, msg);
	}

	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height)
	{
		Msg* msg = new Msg;
		msg->m_width  = _width;
		msg->m_height = _height;

		sdlPostEvent(SDL_USER_WINDOW_SET_SIZE, _handle, msg);
	}

	void setWindowTitle(WindowHandle _handle, const char* _title)
	{
		Msg* msg = new Msg;
		msg->m_title = _title;

		sdlPostEvent(SDL_USER_WINDOW_SET_TITLE, _handle, msg);
	}

	void toggleWindowFrame(WindowHandle _handle)
	{
		sdlPostEvent(SDL_USER_WINDOW_TOGGLE_FRAME, _handle);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		sdlPostEvent(SDL_USER_WINDOW_MOUSE_LOCK, _handle, NULL, _lock);
	}

	int32_t MainThreadEntry::threadFunc(void* _userData)
	{
		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = main(self->m_argc, self->m_argv);

		SDL_Event event;
		SDL_QuitEvent& qev = event.quit;
		qev.type = SDL_QUIT;
		SDL_PushEvent(&event);
		return result;
	}

} // namespace entry

int main(int _argc, char** _argv)
{
	using namespace entry;
	s_ctx.run(_argc, _argv);
	return 0;
}

#endif // ENTRY_CONFIG_USE_SDL
