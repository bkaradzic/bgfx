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

	static uint32_t s_userEventStart = SDL_USEREVENT;

#define SDL_USER_SET_WINDOW_SIZE     (s_userEventStart+0)
#define SDL_USER_TOGGLE_WINDOW_FRAME (s_userEventStart+1)
#define SDL_USER_MOUSE_LOCK          (s_userEventStart+2)

	struct Context
	{
		Context()
			: m_window(NULL)
			, m_width(ENTRY_DEFAULT_WIDTH)
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

		void run()
		{
			const char* argv[1] = { "sdl.so" };
			m_mte.m_argc = 1;
			m_mte.m_argv = const_cast<char**>(argv);

			SDL_Init(SDL_INIT_VIDEO);

			m_window = SDL_CreateWindow("bgfx"
							, SDL_WINDOWPOS_UNDEFINED
							, SDL_WINDOWPOS_UNDEFINED
							, m_width
							, m_height
							, SDL_WINDOW_SHOWN
							| SDL_WINDOW_OPENGL
							| SDL_WINDOW_RESIZABLE
							);

			s_userEventStart = SDL_RegisterEvents(3);

			bgfx::sdlSetWindow(m_window);
			m_thread.init(MainThreadEntry::threadFunc, &m_mte);

			// Force window resolution...
			setWindowSize(m_width, m_height, true);

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

				case SDL_MOUSEMOTION:
					{
						const SDL_MouseMotionEvent& mev = event.motion;
						m_eventQueue.postMouseEvent(mev.x, mev.y, 0);
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					{
						const SDL_MouseButtonEvent& mev = event.button;
						m_eventQueue.postMouseEvent(mev.x, mev.y, 0, MouseButton::Left, mev.type == SDL_MOUSEBUTTONDOWN);
					}
					break;

				case SDL_KEYDOWN:
				case SDL_KEYUP:
					{
						const SDL_KeyboardEvent& kev = event.key;
						uint8_t modifiers = translateKeyModifiers(kev.keysym.mod);
						Key::Enum key = translateKey(kev.keysym.scancode);
 						m_eventQueue.postKeyEvent(key, modifiers, kev.state == SDL_PRESSED);
					}
					break;

				case SDL_WINDOWEVENT:
					{
						const SDL_WindowEvent& wev = event.window;
						switch (wev.event)
						{
						case SDL_WINDOWEVENT_RESIZED:
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							setWindowSize(wev.data1, wev.data2);
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
							m_eventQueue.postExitEvent();
							exit = true;
							break;
						}
					}
					break;

				default:
					{
						const SDL_UserEvent uev = event.user;
						if (SDL_USER_SET_WINDOW_SIZE == event.type)
						{
							uint32_t width = *(uint32_t*)&uev.data1;
							uint32_t height = *(uint32_t*)&uev.data2;
							setWindowSize(width, height);
						}
						else if (SDL_USER_TOGGLE_WINDOW_FRAME == event.type)
						{
							DBG("SDL_USER_TOGGLE_WINDOW_FRAME");
						}
						else if (SDL_USER_MOUSE_LOCK == event.type)
						{
							setMouseLock(!!uev.code);
						}
					}
					break;
				}
			}

			m_thread.shutdown();

			SDL_DestroyWindow(m_window);
			SDL_Quit();
		}

		void setMousePos(int32_t _mx, int32_t _my)
		{
			BX_UNUSED(_mx, _my);
		}

		void setMouseLock(bool _lock)
		{
			SDL_SetRelativeMouseMode(_lock ? SDL_TRUE : SDL_FALSE);
		}

		void setWindowSize(uint32_t _width, uint32_t _height, bool _force = false)
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

				SDL_SetWindowSize(m_window, m_width, m_height);
				m_eventQueue.postSizeEvent(m_width, m_height);
			}
		}

		void setWindowTitle(const char* _title)
		{
			SDL_WM_SetCaption(_title, NULL);
		}

		MainThreadEntry m_mte;
		bx::Thread m_thread;

		EventQueue m_eventQueue;

		SDL_Window* m_window;

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

	void release(const Event* _event)
	{
		s_ctx.m_eventQueue.release(_event);
	}

	void setWindowSize(uint32_t _width, uint32_t _height)
	{
		SDL_Event event;
		SDL_UserEvent& uev = event.user;
		uev.type = SDL_USER_SET_WINDOW_SIZE;
		uev.data1 = reinterpret_cast<void*>(_width);
		uev.data2 = reinterpret_cast<void*>(_height);
		SDL_PushEvent(&event);
	}

	void setWindowTitle(const char* _title)
	{
		s_ctx.setWindowTitle(_title);
	}

	void toggleWindowFrame()
	{
	}

	void setMouseLock(bool _lock)
	{
		SDL_Event event;
		SDL_UserEvent& uev = event.user;
		uev.type = SDL_USER_MOUSE_LOCK;
		uev.code = _lock;
		DBG("setMouseLock %d", event.type);
		SDL_PushEvent(&event);
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

int main(int _argc, const char* _argv[])
{
	BX_UNUSED(_argc, _argv);
	using namespace entry;
	s_ctx.run();
	return 0;
}

#endif // ENTRY_CONFIG_USE_SDL
