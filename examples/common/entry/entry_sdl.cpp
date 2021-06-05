/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_SDL

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	if ENTRY_CONFIG_USE_WAYLAND
#		include <wayland-egl.h>
#	endif
#elif BX_PLATFORM_WINDOWS
#	define SDL_MAIN_HANDLED
#endif

#include <bx/os.h>

#include <SDL2/SDL.h>

BX_PRAGMA_DIAGNOSTIC_PUSH()
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wextern-c-compat")
#include <SDL2/SDL_syswm.h>
BX_PRAGMA_DIAGNOSTIC_POP()

#include <bgfx/platform.h>
#if defined(None) // X11 defines this...
#	undef None
#endif // defined(None)

#include <bx/mutex.h>
#include <bx/thread.h>
#include <bx/handlealloc.h>
#include <bx/readerwriter.h>
#include <tinystl/allocator.h>
#include <tinystl/string.h>

namespace entry
{
	///
	static void* sdlNativeWindowHandle(SDL_Window* _window)
	{
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi) )
		{
			return NULL;
		}

#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
		wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
		if(!win_impl)
		{
			int width, height;
			SDL_GetWindowSize(_window, &width, &height);
			struct wl_surface* surface = wmi.info.wl.surface;
			if(!surface)
				return nullptr;
			win_impl = wl_egl_window_create(surface, width, height);
			SDL_SetWindowData(_window, "wl_egl_window", win_impl);
		}
		return (void*)(uintptr_t)win_impl;
#		else
		return (void*)wmi.info.x11.window;
#		endif
#	elif BX_PLATFORM_OSX || BX_PLATFORM_IOS
		return wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
		return wmi.info.win.window;
#   elif BX_PLATFORM_ANDROID
		return wmi.info.android.window;
#	endif // BX_PLATFORM_
	}

	inline bool sdlSetWindow(SDL_Window* _window)
	{
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if (!SDL_GetWindowWMInfo(_window, &wmi) )
		{
			return false;
		}

		bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
		pd.ndt          = wmi.info.wl.display;
#		else
		pd.ndt          = wmi.info.x11.display;
#		endif
#	else
		pd.ndt          = NULL;
#	endif // BX_PLATFORM_
		pd.nwh          = sdlNativeWindowHandle(_window);

		pd.context      = NULL;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		bgfx::setPlatformData(pd);

		return true;
	}

	static void sdlDestroyWindow(SDL_Window* _window)
	{
		if(!_window)
			return;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
		wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
		if(win_impl)
		{
			SDL_SetWindowData(_window, "wl_egl_window", nullptr);
			wl_egl_window_destroy(win_impl);
		}
#		endif
#	endif
		SDL_DestroyWindow(_window);
	}

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

	static uint8_t translateKeyModifierPress(uint16_t _key)
	{
		uint8_t modifier;
		switch (_key)
		{
			case SDL_SCANCODE_LALT:   { modifier = Modifier::LeftAlt;    } break;
			case SDL_SCANCODE_RALT:   { modifier = Modifier::RightAlt;   } break;
			case SDL_SCANCODE_LCTRL:  { modifier = Modifier::LeftCtrl;   } break;
			case SDL_SCANCODE_RCTRL:  { modifier = Modifier::RightCtrl;  } break;
			case SDL_SCANCODE_LSHIFT: { modifier = Modifier::LeftShift;  } break;
			case SDL_SCANCODE_RSHIFT: { modifier = Modifier::RightShift; } break;
			case SDL_SCANCODE_LGUI:   { modifier = Modifier::LeftMeta;   } break;
			case SDL_SCANCODE_RGUI:   { modifier = Modifier::RightMeta;  } break;
			default:                  { modifier = 0;                    } break;
		}

		return modifier;
	}

	static uint8_t s_translateKey[256];

	static void initTranslateKey(uint16_t _sdl, Key::Enum _key)
	{
		BX_ASSERT(_sdl < BX_COUNTOF(s_translateKey), "Out of bounds %d.", _sdl);
		s_translateKey[_sdl&0xff] = (uint8_t)_key;
	}

	static Key::Enum translateKey(SDL_Scancode _sdl)
	{
		return (Key::Enum)s_translateKey[_sdl&0xff];
	}

	static uint8_t s_translateGamepad[256];

	static void initTranslateGamepad(uint8_t _sdl, Key::Enum _button)
	{
		s_translateGamepad[_sdl] = _button;
	}

	static Key::Enum translateGamepad(uint8_t _sdl)
	{
		return Key::Enum(s_translateGamepad[_sdl]);
	}

	static uint8_t s_translateGamepadAxis[256];

	static void initTranslateGamepadAxis(uint8_t _sdl, GamepadAxis::Enum _axis)
	{
		s_translateGamepadAxis[_sdl] = uint8_t(_axis);
	}

	static GamepadAxis::Enum translateGamepadAxis(uint8_t _sdl)
	{
		return GamepadAxis::Enum(s_translateGamepadAxis[_sdl]);
	}

	struct AxisDpadRemap
	{
		Key::Enum first;
		Key::Enum second;
	};

	static AxisDpadRemap s_axisDpad[] =
	{
		{ Key::GamepadLeft, Key::GamepadRight },
		{ Key::GamepadUp,   Key::GamepadDown  },
		{ Key::None,        Key::None         },
		{ Key::GamepadLeft, Key::GamepadRight },
		{ Key::GamepadUp,   Key::GamepadDown  },
		{ Key::None,        Key::None         },
	};

	struct GamepadSDL
	{
		GamepadSDL()
			: m_controller(NULL)
			, m_jid(INT32_MAX)
		{
			bx::memSet(m_value, 0, sizeof(m_value) );

			// Deadzone values from xinput.h
			m_deadzone[GamepadAxis::LeftX ] =
			m_deadzone[GamepadAxis::LeftY ] = 7849;
			m_deadzone[GamepadAxis::RightX] =
			m_deadzone[GamepadAxis::RightY] = 8689;
			m_deadzone[GamepadAxis::LeftZ ] =
			m_deadzone[GamepadAxis::RightZ] = 30;
		}

		void create(const SDL_JoyDeviceEvent& _jev)
		{
			m_joystick = SDL_JoystickOpen(_jev.which);
			SDL_Joystick* joystick = m_joystick;
			m_jid = SDL_JoystickInstanceID(joystick);
		}

		void create(const SDL_ControllerDeviceEvent& _cev)
		{
			m_controller = SDL_GameControllerOpen(_cev.which);
			SDL_Joystick* joystick = SDL_GameControllerGetJoystick(m_controller);
			m_jid = SDL_JoystickInstanceID(joystick);
		}

		void update(EventQueue& _eventQueue, WindowHandle _handle, GamepadHandle _gamepad, GamepadAxis::Enum _axis, int32_t _value)
		{
			if (filter(_axis, &_value) )
			{
				_eventQueue.postAxisEvent(_handle, _gamepad, _axis, _value);

				if (Key::None != s_axisDpad[_axis].first)
				{
					if (_value == 0)
					{
						_eventQueue.postKeyEvent(_handle, s_axisDpad[_axis].first,  0, false);
						_eventQueue.postKeyEvent(_handle, s_axisDpad[_axis].second, 0, false);
					}
					else
					{
						_eventQueue.postKeyEvent(_handle
								, 0 > _value ? s_axisDpad[_axis].first : s_axisDpad[_axis].second
								, 0
								, true
								);
					}
				}
			}
		}

		void destroy()
		{
			if (NULL != m_controller)
			{
				SDL_GameControllerClose(m_controller);
				m_controller = NULL;
			}

			if (NULL != m_joystick)
			{
				SDL_JoystickClose(m_joystick);
				m_joystick = NULL;
			}

			m_jid = INT32_MAX;
		}

		bool filter(GamepadAxis::Enum _axis, int32_t* _value)
		{
			const int32_t old = m_value[_axis];
			const int32_t deadzone = m_deadzone[_axis];
			int32_t value = *_value;
			value = value > deadzone || value < -deadzone ? value : 0;
			m_value[_axis] = value;
			*_value = value;
			return old != value;
		}

		int32_t m_value[GamepadAxis::Count];
		int32_t m_deadzone[GamepadAxis::Count];

		SDL_Joystick*       m_joystick;
		SDL_GameController* m_controller;
//		SDL_Haptic*         m_haptic;
		SDL_JoystickID      m_jid;
	};

	struct MainThreadEntry
	{
		int m_argc;
		char** m_argv;

		static int32_t threadFunc(bx::Thread* _thread, void* _userData);
	};

	struct Msg
	{
		Msg()
			: m_x(0)
			, m_y(0)
			, m_width(0)
			, m_height(0)
			, m_flags(0)
			, m_flagsEnabled(false)
		{
		}

		int32_t  m_x;
		int32_t  m_y;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_flags;
		tinystl::string m_title;
		bool m_flagsEnabled;
	};

	static uint32_t s_userEventStart;

	enum SDL_USER_WINDOW
	{
		SDL_USER_WINDOW_CREATE,
		SDL_USER_WINDOW_DESTROY,
		SDL_USER_WINDOW_SET_TITLE,
		SDL_USER_WINDOW_SET_FLAGS,
		SDL_USER_WINDOW_SET_POS,
		SDL_USER_WINDOW_SET_SIZE,
		SDL_USER_WINDOW_TOGGLE_FRAME,
		SDL_USER_WINDOW_TOGGLE_FULL_SCREEN,
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
			, m_mx(0)
			, m_my(0)
			, m_mz(0)
			, m_mouseLock(false)
			, m_fullscreen(false)
		{
			bx::memSet(s_translateKey, 0, sizeof(s_translateKey) );
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
			initTranslateKey(SDL_SCANCODE_EQUALS,       Key::Plus);
			initTranslateKey(SDL_SCANCODE_KP_MINUS,     Key::Minus);
			initTranslateKey(SDL_SCANCODE_MINUS,        Key::Minus);
			initTranslateKey(SDL_SCANCODE_GRAVE,        Key::Tilde);
			initTranslateKey(SDL_SCANCODE_KP_COMMA,     Key::Comma);
			initTranslateKey(SDL_SCANCODE_COMMA,        Key::Comma);
			initTranslateKey(SDL_SCANCODE_KP_PERIOD,    Key::Period);
			initTranslateKey(SDL_SCANCODE_PERIOD,       Key::Period);
			initTranslateKey(SDL_SCANCODE_SLASH,        Key::Slash);
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

			bx::memSet(s_translateGamepad, uint8_t(Key::Count), sizeof(s_translateGamepad) );
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_A,             Key::GamepadA);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_B,             Key::GamepadB);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_X,             Key::GamepadX);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_Y,             Key::GamepadY);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_LEFTSTICK,     Key::GamepadThumbL);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_RIGHTSTICK,    Key::GamepadThumbR);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_LEFTSHOULDER,  Key::GamepadShoulderL);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, Key::GamepadShoulderR);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_DPAD_UP,       Key::GamepadUp);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_DPAD_DOWN,     Key::GamepadDown);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_DPAD_LEFT,     Key::GamepadLeft);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_DPAD_RIGHT,    Key::GamepadRight);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_BACK,          Key::GamepadBack);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_START,         Key::GamepadStart);
			initTranslateGamepad(SDL_CONTROLLER_BUTTON_GUIDE,         Key::GamepadGuide);

			bx::memSet(s_translateGamepadAxis, uint8_t(GamepadAxis::Count), sizeof(s_translateGamepadAxis) );
			initTranslateGamepadAxis(SDL_CONTROLLER_AXIS_LEFTX,        GamepadAxis::LeftX);
			initTranslateGamepadAxis(SDL_CONTROLLER_AXIS_LEFTY,        GamepadAxis::LeftY);
			initTranslateGamepadAxis(SDL_CONTROLLER_AXIS_TRIGGERLEFT,  GamepadAxis::LeftZ);
			initTranslateGamepadAxis(SDL_CONTROLLER_AXIS_RIGHTX,       GamepadAxis::RightX);
			initTranslateGamepadAxis(SDL_CONTROLLER_AXIS_RIGHTY,       GamepadAxis::RightY);
			initTranslateGamepadAxis(SDL_CONTROLLER_AXIS_TRIGGERRIGHT, GamepadAxis::RightZ);
		}

		int run(int _argc, char** _argv)
		{
			m_mte.m_argc = _argc;
			m_mte.m_argv = _argv;

			SDL_Init(0
				| SDL_INIT_GAMECONTROLLER
				);

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

			sdlSetWindow(m_window[0]);
			bgfx::renderFrame();

			m_thread.init(MainThreadEntry::threadFunc, &m_mte);

			// Force window resolution...
			WindowHandle defaultWindow = { 0 };
			setWindowSize(defaultWindow, m_width, m_height, true);

			SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

			bx::FileReaderI* reader = NULL;
			while (NULL == reader)
			{
				reader = getFileReader();
				bx::sleep(100);
			}

			if (bx::open(reader, "gamecontrollerdb.txt") )
			{
				bx::AllocatorI* allocator = getAllocator();
				uint32_t size = (uint32_t)bx::getSize(reader);
				void* data = BX_ALLOC(allocator, size + 1);
				bx::read(reader, data, size);
				bx::close(reader);
				((char*)data)[size] = '\0';

				if (SDL_GameControllerAddMapping( (char*)data) < 0) {
					DBG("SDL game controller add mapping failed: %s", SDL_GetError());
				}

				BX_FREE(allocator, data);
			}

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
							m_mx = mev.x;
							m_my = mev.y;

							WindowHandle handle = findHandle(mev.windowID);
							if (isValid(handle) )
							{
								m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_mz);
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
									, m_mz
									, button
									, mev.type == SDL_MOUSEBUTTONDOWN
									);
							}
						}
						break;

					case SDL_MOUSEWHEEL:
						{
							const SDL_MouseWheelEvent& mev = event.wheel;
							m_mz += mev.y;

							WindowHandle handle = findHandle(mev.windowID);
							if (isValid(handle) )
							{
								m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_mz);
							}
						}
						break;

					case SDL_TEXTINPUT:
						{
							const SDL_TextInputEvent& tev = event.text;
							WindowHandle handle = findHandle(tev.windowID);
							if (isValid(handle) )
							{
								m_eventQueue.postCharEvent(handle, 1, (const uint8_t*)tev.text);
							}
						}
						break;

					case SDL_KEYDOWN:
						{
							const SDL_KeyboardEvent& kev = event.key;
							WindowHandle handle = findHandle(kev.windowID);
							if (isValid(handle) )
							{
								uint8_t modifiers = translateKeyModifiers(kev.keysym.mod);
								Key::Enum key = translateKey(kev.keysym.scancode);

#if 0
								DBG("SDL scancode %d, key %d, name %s, key name %s"
									, kev.keysym.scancode
									, key
									, SDL_GetScancodeName(kev.keysym.scancode)
									, SDL_GetKeyName(kev.keysym.scancode)
									);
#endif // 0

								/// If you only press (e.g.) 'shift' and nothing else, then key == 'shift', modifier == 0.
								/// Further along, pressing 'shift' + 'ctrl' would be: key == 'shift', modifier == 'ctrl.
								if (0 == key && 0 == modifiers)
								{
									modifiers = translateKeyModifierPress(kev.keysym.scancode);
								}

								if (Key::Esc == key)
								{
									uint8_t pressedChar[4];
									pressedChar[0] = 0x1b;
									m_eventQueue.postCharEvent(handle, 1, pressedChar);
								}
								else if (Key::Return == key)
								{
									uint8_t pressedChar[4];
									pressedChar[0] = 0x0d;
									m_eventQueue.postCharEvent(handle, 1, pressedChar);
								}
								else if (Key::Backspace == key)
								{
									uint8_t pressedChar[4];
									pressedChar[0] = 0x08;
									m_eventQueue.postCharEvent(handle, 1, pressedChar);
								}

								m_eventQueue.postKeyEvent(handle, key, modifiers, kev.state == SDL_PRESSED);
							}
						}
						break;

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

					case SDL_JOYAXISMOTION:
						{
							const SDL_JoyAxisEvent& jev = event.jaxis;
							GamepadHandle handle = findGamepad(jev.which);
							if (isValid(handle) )
							{
								GamepadAxis::Enum axis = translateGamepadAxis(jev.axis);
								m_gamepad[handle.idx].update(m_eventQueue, defaultWindow, handle, axis, jev.value);
							}
						}
						break;

					case SDL_CONTROLLERAXISMOTION:
						{
							const SDL_ControllerAxisEvent& aev = event.caxis;
							GamepadHandle handle = findGamepad(aev.which);
							if (isValid(handle) )
							{
								GamepadAxis::Enum axis = translateGamepadAxis(aev.axis);
								m_gamepad[handle.idx].update(m_eventQueue, defaultWindow, handle, axis, aev.value);
							}
						}
						break;

					case SDL_JOYBUTTONDOWN:
					case SDL_JOYBUTTONUP:
						{
							const SDL_JoyButtonEvent& bev = event.jbutton;
							GamepadHandle handle = findGamepad(bev.which);

							if (isValid(handle) )
							{
								Key::Enum key = translateGamepad(bev.button);
								if (Key::Count != key)
								{
									m_eventQueue.postKeyEvent(defaultWindow, key, 0, event.type == SDL_JOYBUTTONDOWN);
								}
							}
						}
						break;

					case SDL_CONTROLLERBUTTONDOWN:
					case SDL_CONTROLLERBUTTONUP:
						{
							const SDL_ControllerButtonEvent& bev = event.cbutton;
							GamepadHandle handle = findGamepad(bev.which);
							if (isValid(handle) )
							{
								Key::Enum key = translateGamepad(bev.button);
								if (Key::Count != key)
								{
									m_eventQueue.postKeyEvent(defaultWindow, key, 0, event.type == SDL_CONTROLLERBUTTONDOWN);
								}
							}
						}
						break;

					case SDL_JOYDEVICEADDED:
						{
							GamepadHandle handle = { m_gamepadAlloc.alloc() };
							if (isValid(handle) )
							{
								const SDL_JoyDeviceEvent& jev = event.jdevice;
								m_gamepad[handle.idx].create(jev);
								m_eventQueue.postGamepadEvent(defaultWindow, handle, true);
							}
						}
						break;

					case SDL_JOYDEVICEREMOVED:
						{
							const SDL_JoyDeviceEvent& jev = event.jdevice;
							GamepadHandle handle = findGamepad(jev.which);
							if (isValid(handle) )
							{
								m_gamepad[handle.idx].destroy();
								m_gamepadAlloc.free(handle.idx);
								m_eventQueue.postGamepadEvent(defaultWindow, handle, false);
							}
						}
						break;

					case SDL_CONTROLLERDEVICEADDED:
						{
							GamepadHandle handle = { m_gamepadAlloc.alloc() };
							if (isValid(handle) )
							{
								const SDL_ControllerDeviceEvent& cev = event.cdevice;
								m_gamepad[handle.idx].create(cev);
								m_eventQueue.postGamepadEvent(defaultWindow, handle, true);
							}
						}
						break;

					case SDL_CONTROLLERDEVICEREMAPPED:
						{

						}
						break;

					case SDL_CONTROLLERDEVICEREMOVED:
						{
							const SDL_ControllerDeviceEvent& cev = event.cdevice;
							GamepadHandle handle = findGamepad(cev.which);
							if (isValid(handle) )
							{
								m_gamepad[handle.idx].destroy();
								m_gamepadAlloc.free(handle.idx);
								m_eventQueue.postGamepadEvent(defaultWindow, handle, false);
							}
						}
						break;

					case SDL_DROPFILE:
						{
							const SDL_DropEvent& dev = event.drop;
							WindowHandle handle = defaultWindow; //findHandle(dev.windowID);
							if (isValid(handle) )
							{
								m_eventQueue.postDropFileEvent(handle, dev.file);
								SDL_free(dev.file);
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
										m_eventQueue.postSizeEvent(handle, msg->m_width, msg->m_height);
										m_eventQueue.postWindowEvent(handle, nwh);
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
										sdlDestroyWindow(m_window[handle.idx]);
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
										SDL_SetWindowTitle(m_window[handle.idx], msg->m_title.c_str() );
									}
									delete msg;
								}
								break;

							case SDL_USER_WINDOW_SET_FLAGS:
								{
									WindowHandle handle = getWindowHandle(uev);
									Msg* msg = (Msg*)uev.data2;

									if (msg->m_flagsEnabled)
									{
										m_flags[handle.idx] |= msg->m_flags;
									}
									else
									{
										m_flags[handle.idx] &= ~msg->m_flags;
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

							case SDL_USER_WINDOW_TOGGLE_FULL_SCREEN:
								{
									WindowHandle handle = getWindowHandle(uev);
									m_fullscreen = !m_fullscreen;
									SDL_SetWindowFullscreen(m_window[handle.idx], m_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
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

			sdlDestroyWindow(m_window[0]);
			SDL_Quit();

			return m_thread.getExitCode();
		}

		WindowHandle findHandle(uint32_t _windowId)
		{
			SDL_Window* window = SDL_GetWindowFromID(_windowId);
			return findHandle(window);
		}

		WindowHandle findHandle(SDL_Window* _window)
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

		void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height, bool _force = false)
		{
			if (_width  != m_width
			||  _height != m_height
			||  _force)
			{
				m_width  = _width;
				m_height = _height;

				SDL_SetWindowSize(m_window[_handle.idx], m_width, m_height);
				m_eventQueue.postSizeEvent(_handle, m_width, m_height);
			}
		}

		GamepadHandle findGamepad(SDL_JoystickID _jid)
		{
			for (uint32_t ii = 0, num = m_gamepadAlloc.getNumHandles(); ii < num; ++ii)
			{
				uint16_t idx = m_gamepadAlloc.getHandleAt(ii);
				if (_jid == m_gamepad[idx].m_jid)
				{
					GamepadHandle handle = { idx };
					return handle;
				}
			}

			GamepadHandle invalid = { UINT16_MAX };
			return invalid;
		}

		MainThreadEntry m_mte;
		bx::Thread m_thread;

		EventQueue m_eventQueue;
		bx::Mutex m_lock;

		bx::HandleAllocT<ENTRY_CONFIG_MAX_WINDOWS> m_windowAlloc;
		SDL_Window* m_window[ENTRY_CONFIG_MAX_WINDOWS];
		uint32_t m_flags[ENTRY_CONFIG_MAX_WINDOWS];

		bx::HandleAllocT<ENTRY_CONFIG_MAX_GAMEPADS> m_gamepadAlloc;
		GamepadSDL m_gamepad[ENTRY_CONFIG_MAX_GAMEPADS];

		uint32_t m_width;
		uint32_t m_height;
		float m_aspectRatio;

		int32_t m_mx;
		int32_t m_my;
		int32_t m_mz;
		bool m_mouseLock;
		bool m_fullscreen;
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
		bx::MutexScope scope(s_ctx.m_lock);
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

			bx::MutexScope scope(s_ctx.m_lock);
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

	void setWindowFlags(WindowHandle _handle, uint32_t _flags, bool _enabled)
	{
		Msg* msg = new Msg;
		msg->m_flags = _flags;
		msg->m_flagsEnabled = _enabled;
		sdlPostEvent(SDL_USER_WINDOW_SET_FLAGS, _handle, msg);
	}

	void toggleFullscreen(WindowHandle _handle)
	{
		sdlPostEvent(SDL_USER_WINDOW_TOGGLE_FULL_SCREEN, _handle);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		sdlPostEvent(SDL_USER_WINDOW_MOUSE_LOCK, _handle, NULL, _lock);
	}

	int32_t MainThreadEntry::threadFunc(bx::Thread* _thread, void* _userData)
	{
		BX_UNUSED(_thread);

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
	return s_ctx.run(_argc, _argv);
}

#endif // ENTRY_CONFIG_USE_SDL
