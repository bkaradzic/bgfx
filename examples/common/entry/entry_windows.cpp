/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_WINDOWS

#include <bgfx/platform.h>

#include <bx/mutex.h>
#include <bx/handlealloc.h>
#include <bx/os.h>
#include <bx/thread.h>
#include <bx/timer.h>
#include <bx/uint32_t.h>

#include <tinystl/allocator.h>
#include <tinystl/string.h>

#include <windows.h>
#include <windowsx.h>
#include <xinput.h>

#ifndef XINPUT_GAMEPAD_GUIDE
#	define XINPUT_GAMEPAD_GUIDE 0x400
#endif // XINPUT_GAMEPAD_GUIDE

#ifndef XINPUT_DLL_A
#	define XINPUT_DLL_A "xinput.dll"
#endif // XINPUT_DLL_A

namespace entry
{
	///
	inline void winSetHwnd(::HWND _window)
	{
		bgfx::PlatformData pd;
		bx::memSet(&pd, 0, sizeof(pd) );
		pd.nwh = _window;
		bgfx::setPlatformData(pd);
	}

	typedef DWORD (WINAPI* PFN_XINPUT_GET_STATE)(DWORD dwUserIndex, XINPUT_STATE* pState);
	typedef void  (WINAPI* PFN_XINPUT_ENABLE)(BOOL enable); // 1.4+

	PFN_XINPUT_GET_STATE XInputGetState;
	PFN_XINPUT_ENABLE    XInputEnable;

	struct XInputRemap
	{
		uint16_t  m_bit;
		Key::Enum m_key;
	};

	static XInputRemap s_xinputRemap[] =
	{
		{ XINPUT_GAMEPAD_DPAD_UP,        Key::GamepadUp        },
		{ XINPUT_GAMEPAD_DPAD_DOWN,      Key::GamepadDown      },
		{ XINPUT_GAMEPAD_DPAD_LEFT,      Key::GamepadLeft      },
		{ XINPUT_GAMEPAD_DPAD_RIGHT,     Key::GamepadRight     },
		{ XINPUT_GAMEPAD_START,          Key::GamepadStart     },
		{ XINPUT_GAMEPAD_BACK,           Key::GamepadBack      },
		{ XINPUT_GAMEPAD_LEFT_THUMB,     Key::GamepadThumbL    },
		{ XINPUT_GAMEPAD_RIGHT_THUMB,    Key::GamepadThumbR    },
		{ XINPUT_GAMEPAD_LEFT_SHOULDER,  Key::GamepadShoulderL },
		{ XINPUT_GAMEPAD_RIGHT_SHOULDER, Key::GamepadShoulderR },
		{ XINPUT_GAMEPAD_GUIDE,          Key::GamepadGuide     },
		{ XINPUT_GAMEPAD_A,              Key::GamepadA         },
		{ XINPUT_GAMEPAD_B,              Key::GamepadB         },
		{ XINPUT_GAMEPAD_X,              Key::GamepadX         },
		{ XINPUT_GAMEPAD_Y,              Key::GamepadY         },
	};

	struct XInput
	{
		XInput()
			: m_xinputdll(NULL)
		{
			bx::memSet(m_connected, 0, sizeof(m_connected) );
			bx::memSet(m_state, 0, sizeof(m_state) );

			m_deadzone[GamepadAxis::LeftX ] =
			m_deadzone[GamepadAxis::LeftY ] = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			m_deadzone[GamepadAxis::RightX] =
			m_deadzone[GamepadAxis::RightY] = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			m_deadzone[GamepadAxis::LeftZ ] =
			m_deadzone[GamepadAxis::RightZ] = XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

			bx::memSet(m_flip, 1, sizeof(m_flip) );
			m_flip[GamepadAxis::LeftY ] =
			m_flip[GamepadAxis::RightY] = -1;
		}

		void init()
		{
			m_xinputdll = bx::dlopen(XINPUT_DLL_A);

			if (NULL != m_xinputdll)
			{
				XInputGetState = (PFN_XINPUT_GET_STATE)bx::dlsym(m_xinputdll, "XInputGetState");
//				XInputEnable   = (PFN_XINPUT_ENABLE   )bx::dlsym(m_xinputdll, "XInputEnable"  );

				if (NULL == XInputGetState)
				{
					shutdown();
				}
			}
		}

		void shutdown()
		{
			if (NULL != m_xinputdll)
			{
				bx::dlclose(m_xinputdll);
				m_xinputdll = NULL;
			}
		}

		bool filter(GamepadAxis::Enum _axis, int32_t _old, int32_t* _value)
		{
			const int32_t deadzone = m_deadzone[_axis];
			int32_t value = *_value;
			value = value > deadzone || value < -deadzone ? value : 0;
			*_value = value * m_flip[_axis];
			return _old != value;
		}

		void update(EventQueue& _eventQueue)
		{
			int64_t now = bx::getHPCounter();
			static int64_t next = now;

			if (now < next)
			{
				return;
			}

			const int64_t timerFreq = bx::getHPFrequency();
			next = now + timerFreq/60;

			if (NULL == m_xinputdll)
			{
				return;
			}

			WindowHandle defaultWindow = { 0 };

			for (uint16_t ii = 0; ii < BX_COUNTOF(m_state); ++ii)
			{
				XINPUT_STATE state;
				DWORD result = XInputGetState(ii, &state);

				GamepadHandle handle = { ii };

				bool connected = ERROR_SUCCESS == result;
				if (connected != m_connected[ii])
				{
					_eventQueue.postGamepadEvent(defaultWindow, handle, connected);
				}

				m_connected[ii] = connected;

				if (connected
				&&  m_state[ii].dwPacketNumber != state.dwPacketNumber)
				{
					XINPUT_GAMEPAD& gamepad = m_state[ii].Gamepad;
					const uint16_t changed = gamepad.wButtons ^ state.Gamepad.wButtons;
					const uint16_t current = gamepad.wButtons;
					if (0 != changed)
					{
						for (uint32_t jj = 0; jj < BX_COUNTOF(s_xinputRemap); ++jj)
						{
							uint16_t bit = s_xinputRemap[jj].m_bit;
							if (bit & changed)
							{
								_eventQueue.postKeyEvent(defaultWindow, s_xinputRemap[jj].m_key, 0, 0 == (current & bit) );
							}
						}

						gamepad.wButtons = state.Gamepad.wButtons;
					}

					if (gamepad.bLeftTrigger != state.Gamepad.bLeftTrigger)
					{
						int32_t value = state.Gamepad.bLeftTrigger;
						if (filter(GamepadAxis::LeftZ, gamepad.bLeftTrigger, &value) )
						{
							_eventQueue.postAxisEvent(defaultWindow, handle, GamepadAxis::LeftZ, value);
						}

						gamepad.bLeftTrigger = state.Gamepad.bLeftTrigger;
					}

					if (gamepad.bRightTrigger != state.Gamepad.bRightTrigger)
					{
						int32_t value = state.Gamepad.bRightTrigger;
						if (filter(GamepadAxis::RightZ, gamepad.bRightTrigger, &value) )
						{
							_eventQueue.postAxisEvent(defaultWindow, handle, GamepadAxis::RightZ, value);
						}

						gamepad.bRightTrigger = state.Gamepad.bRightTrigger;
					}

					if (gamepad.sThumbLX != state.Gamepad.sThumbLX)
					{
						int32_t value = state.Gamepad.sThumbLX;
						if (filter(GamepadAxis::LeftX, gamepad.sThumbLX, &value) )
						{
							_eventQueue.postAxisEvent(defaultWindow, handle, GamepadAxis::LeftX, value);
						}

						gamepad.sThumbLX = state.Gamepad.sThumbLX;
					}

					if (gamepad.sThumbLY != state.Gamepad.sThumbLY)
					{
						int32_t value = state.Gamepad.sThumbLY;
						if (filter(GamepadAxis::LeftY, gamepad.sThumbLY, &value) )
						{
							_eventQueue.postAxisEvent(defaultWindow, handle, GamepadAxis::LeftY, value);
						}

						gamepad.sThumbLY = state.Gamepad.sThumbLY;
					}

					if (gamepad.sThumbRX != state.Gamepad.sThumbRX)
					{
						int32_t value = state.Gamepad.sThumbRX;
						if (filter(GamepadAxis::RightX, gamepad.sThumbRX, &value) )
						{
							_eventQueue.postAxisEvent(defaultWindow, handle, GamepadAxis::RightX, value);
						}

						gamepad.sThumbRX = state.Gamepad.sThumbRX;
					}

					if (gamepad.sThumbRY != state.Gamepad.sThumbRY)
					{
						int32_t value = state.Gamepad.sThumbRY;
						if (filter(GamepadAxis::RightY, gamepad.sThumbRY, &value) )
						{
							_eventQueue.postAxisEvent(defaultWindow, handle, GamepadAxis::RightY, value);
						}

						gamepad.sThumbRY = state.Gamepad.sThumbRY;
					}
				}
			}
		}

		void* m_xinputdll;

		int32_t m_deadzone[GamepadAxis::Count];
		int8_t m_flip[GamepadAxis::Count];
		XINPUT_STATE m_state[ENTRY_CONFIG_MAX_GAMEPADS];
		bool m_connected[ENTRY_CONFIG_MAX_GAMEPADS];
	};

	XInput s_xinput;

	enum
	{
		WM_USER_WINDOW_CREATE = WM_USER,
		WM_USER_WINDOW_DESTROY,
		WM_USER_WINDOW_SET_TITLE,
		WM_USER_WINDOW_SET_POS,
		WM_USER_WINDOW_SET_SIZE,
		WM_USER_WINDOW_TOGGLE_FRAME,
		WM_USER_WINDOW_MOUSE_LOCK,
	};

	struct TranslateKeyModifiers
	{
		int m_vk;
		Modifier::Enum m_modifier;
	};

	static const TranslateKeyModifiers s_translateKeyModifiers[8] =
	{
		{ VK_LMENU,    Modifier::LeftAlt    },
		{ VK_RMENU,    Modifier::RightAlt   },
		{ VK_LCONTROL, Modifier::LeftCtrl   },
		{ VK_RCONTROL, Modifier::RightCtrl  },
		{ VK_LSHIFT,   Modifier::LeftShift  },
		{ VK_RSHIFT,   Modifier::RightShift },
		{ VK_LWIN,     Modifier::LeftMeta   },
		{ VK_RWIN,     Modifier::RightMeta  },
	};

	static uint8_t translateKeyModifiers()
	{
		uint8_t modifiers = 0;
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_translateKeyModifiers); ++ii)
		{
			const TranslateKeyModifiers& tkm = s_translateKeyModifiers[ii];
			modifiers |= 0 > GetKeyState(tkm.m_vk) ? tkm.m_modifier : Modifier::None;
		}
		return modifiers;
	}

	static uint8_t s_translateKey[256];

	static Key::Enum translateKey(WPARAM _wparam)
	{
		return (Key::Enum)s_translateKey[_wparam&0xff];
	}

	struct MainThreadEntry
	{
		int m_argc;
		char** m_argv;

		static int32_t threadFunc(void* _userData);
	};

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

	static void mouseCapture(HWND _hwnd, bool _capture)
	{
		if (_capture)
		{
			SetCapture(_hwnd);
		}
		else
		{
			ReleaseCapture();
		}
	}

	struct Context
	{
		Context()
			: m_mz(0)
			, m_frame(true)
			, m_mouseLock(NULL)
			, m_init(false)
			, m_exit(false)
		{
			bx::memSet(s_translateKey, 0, sizeof(s_translateKey) );
			s_translateKey[VK_ESCAPE]     = Key::Esc;
			s_translateKey[VK_RETURN]     = Key::Return;
			s_translateKey[VK_TAB]        = Key::Tab;
			s_translateKey[VK_BACK]       = Key::Backspace;
			s_translateKey[VK_SPACE]      = Key::Space;
			s_translateKey[VK_UP]         = Key::Up;
			s_translateKey[VK_DOWN]       = Key::Down;
			s_translateKey[VK_LEFT]       = Key::Left;
			s_translateKey[VK_RIGHT]      = Key::Right;
			s_translateKey[VK_INSERT]     = Key::Insert;
			s_translateKey[VK_DELETE]     = Key::Delete;
			s_translateKey[VK_HOME]       = Key::Home;
			s_translateKey[VK_END]        = Key::End;
			s_translateKey[VK_PRIOR]      = Key::PageUp;
			s_translateKey[VK_NEXT]       = Key::PageDown;
			s_translateKey[VK_SNAPSHOT]   = Key::Print;
			s_translateKey[VK_OEM_PLUS]   = Key::Plus;
			s_translateKey[VK_OEM_MINUS]  = Key::Minus;
			s_translateKey[VK_OEM_4]      = Key::LeftBracket;
			s_translateKey[VK_OEM_6]      = Key::RightBracket;
			s_translateKey[VK_OEM_1]      = Key::Semicolon;
			s_translateKey[VK_OEM_7]      = Key::Quote;
			s_translateKey[VK_OEM_COMMA]  = Key::Comma;
			s_translateKey[VK_OEM_PERIOD] = Key::Period;
			s_translateKey[VK_DECIMAL] 	  = Key::Period;
			s_translateKey[VK_OEM_2]      = Key::Slash;
			s_translateKey[VK_OEM_5]      = Key::Backslash;
			s_translateKey[VK_OEM_3]      = Key::Tilde;
			s_translateKey[VK_F1]         = Key::F1;
			s_translateKey[VK_F2]         = Key::F2;
			s_translateKey[VK_F3]         = Key::F3;
			s_translateKey[VK_F4]         = Key::F4;
			s_translateKey[VK_F5]         = Key::F5;
			s_translateKey[VK_F6]         = Key::F6;
			s_translateKey[VK_F7]         = Key::F7;
			s_translateKey[VK_F8]         = Key::F8;
			s_translateKey[VK_F9]         = Key::F9;
			s_translateKey[VK_F10]        = Key::F10;
			s_translateKey[VK_F11]        = Key::F11;
			s_translateKey[VK_F12]        = Key::F12;
			s_translateKey[VK_NUMPAD0]    = Key::NumPad0;
			s_translateKey[VK_NUMPAD1]    = Key::NumPad1;
			s_translateKey[VK_NUMPAD2]    = Key::NumPad2;
			s_translateKey[VK_NUMPAD3]    = Key::NumPad3;
			s_translateKey[VK_NUMPAD4]    = Key::NumPad4;
			s_translateKey[VK_NUMPAD5]    = Key::NumPad5;
			s_translateKey[VK_NUMPAD6]    = Key::NumPad6;
			s_translateKey[VK_NUMPAD7]    = Key::NumPad7;
			s_translateKey[VK_NUMPAD8]    = Key::NumPad8;
			s_translateKey[VK_NUMPAD9]    = Key::NumPad9;
			s_translateKey[uint8_t('0')]  = Key::Key0;
			s_translateKey[uint8_t('1')]  = Key::Key1;
			s_translateKey[uint8_t('2')]  = Key::Key2;
			s_translateKey[uint8_t('3')]  = Key::Key3;
			s_translateKey[uint8_t('4')]  = Key::Key4;
			s_translateKey[uint8_t('5')]  = Key::Key5;
			s_translateKey[uint8_t('6')]  = Key::Key6;
			s_translateKey[uint8_t('7')]  = Key::Key7;
			s_translateKey[uint8_t('8')]  = Key::Key8;
			s_translateKey[uint8_t('9')]  = Key::Key9;
			s_translateKey[uint8_t('A')]  = Key::KeyA;
			s_translateKey[uint8_t('B')]  = Key::KeyB;
			s_translateKey[uint8_t('C')]  = Key::KeyC;
			s_translateKey[uint8_t('D')]  = Key::KeyD;
			s_translateKey[uint8_t('E')]  = Key::KeyE;
			s_translateKey[uint8_t('F')]  = Key::KeyF;
			s_translateKey[uint8_t('G')]  = Key::KeyG;
			s_translateKey[uint8_t('H')]  = Key::KeyH;
			s_translateKey[uint8_t('I')]  = Key::KeyI;
			s_translateKey[uint8_t('J')]  = Key::KeyJ;
			s_translateKey[uint8_t('K')]  = Key::KeyK;
			s_translateKey[uint8_t('L')]  = Key::KeyL;
			s_translateKey[uint8_t('M')]  = Key::KeyM;
			s_translateKey[uint8_t('N')]  = Key::KeyN;
			s_translateKey[uint8_t('O')]  = Key::KeyO;
			s_translateKey[uint8_t('P')]  = Key::KeyP;
			s_translateKey[uint8_t('Q')]  = Key::KeyQ;
			s_translateKey[uint8_t('R')]  = Key::KeyR;
			s_translateKey[uint8_t('S')]  = Key::KeyS;
			s_translateKey[uint8_t('T')]  = Key::KeyT;
			s_translateKey[uint8_t('U')]  = Key::KeyU;
			s_translateKey[uint8_t('V')]  = Key::KeyV;
			s_translateKey[uint8_t('W')]  = Key::KeyW;
			s_translateKey[uint8_t('X')]  = Key::KeyX;
			s_translateKey[uint8_t('Y')]  = Key::KeyY;
			s_translateKey[uint8_t('Z')]  = Key::KeyZ;
		}

		int32_t run(int _argc, char** _argv)
		{
			SetDllDirectoryA(".");

			s_xinput.init();

			HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);

			WNDCLASSEXA wnd;
			bx::memSet(&wnd, 0, sizeof(wnd) );
			wnd.cbSize = sizeof(wnd);
			wnd.style = CS_HREDRAW | CS_VREDRAW;
			wnd.lpfnWndProc = wndProc;
			wnd.hInstance = instance;
			wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
			wnd.lpszClassName = "bgfx";
			wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			RegisterClassExA(&wnd);

			m_windowAlloc.alloc();
			m_hwnd[0] = CreateWindowA("bgfx"
				, "BGFX"
				, WS_OVERLAPPEDWINDOW|WS_VISIBLE
				, 0
				, 0
				, ENTRY_DEFAULT_WIDTH
				, ENTRY_DEFAULT_HEIGHT
				, NULL
				, NULL
				, instance
				, 0
				);

			m_flags[0] = 0
				| ENTRY_WINDOW_FLAG_ASPECT_RATIO
				| ENTRY_WINDOW_FLAG_FRAME
				;

			winSetHwnd(m_hwnd[0]);

			adjust(m_hwnd[0], ENTRY_DEFAULT_WIDTH, ENTRY_DEFAULT_HEIGHT, true);
			clear(m_hwnd[0]);

			m_width     = ENTRY_DEFAULT_WIDTH;
			m_height    = ENTRY_DEFAULT_HEIGHT;
			m_oldWidth  = ENTRY_DEFAULT_WIDTH;
			m_oldHeight = ENTRY_DEFAULT_HEIGHT;

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);
			m_init = true;

			m_eventQueue.postSizeEvent(findHandle(m_hwnd[0]), m_width, m_height);

			MSG msg;
			msg.message = WM_NULL;

			while (!m_exit)
			{
				s_xinput.update(m_eventQueue);
				WaitForInputIdle(GetCurrentProcess(), 16);

				while (0 != PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			thread.shutdown();

			DestroyWindow(m_hwnd[0]);

			s_xinput.shutdown();

			return thread.getExitCode();
		}

		LRESULT process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
		{
			if (m_init)
			{
				switch (_id)
				{
				case WM_USER_WINDOW_CREATE:
					{
						Msg* msg = (Msg*)_lparam;
						HWND hwnd = CreateWindowA("bgfx"
							, msg->m_title.c_str()
							, WS_OVERLAPPEDWINDOW|WS_VISIBLE
							, msg->m_x
							, msg->m_y
							, msg->m_width
							, msg->m_height
							, NULL
							, NULL
							, (HINSTANCE)GetModuleHandle(NULL)
							, 0
							);
						clear(hwnd);

						m_hwnd[_wparam]  = hwnd;
						m_flags[_wparam] = msg->m_flags;
						WindowHandle handle = { (uint16_t)_wparam };
						m_eventQueue.postSizeEvent(handle, msg->m_width, msg->m_height);
						m_eventQueue.postWindowEvent(handle, hwnd);

						delete msg;
					}
					break;

				case WM_USER_WINDOW_DESTROY:
					{
						WindowHandle handle = { (uint16_t)_wparam };
						m_eventQueue.postWindowEvent(handle);
						DestroyWindow(m_hwnd[_wparam]);
						m_hwnd[_wparam] = 0;

						if (0 == handle.idx)
						{
							m_exit = true;
							m_eventQueue.postExitEvent();
						}
					}
					break;

				case WM_USER_WINDOW_SET_TITLE:
					{
						Msg* msg = (Msg*)_lparam;
						SetWindowTextA(m_hwnd[_wparam], msg->m_title.c_str() );
						delete msg;
					}
					break;

				case WM_USER_WINDOW_SET_POS:
					{
						Msg* msg = (Msg*)_lparam;
						SetWindowPos(m_hwnd[_wparam], 0, msg->m_x, msg->m_y, 0, 0
							, SWP_NOACTIVATE
							| SWP_NOOWNERZORDER
							| SWP_NOSIZE
							);
						delete msg;
					}
					break;

				case WM_USER_WINDOW_SET_SIZE:
					{
						uint32_t width  = GET_X_LPARAM(_lparam);
						uint32_t height = GET_Y_LPARAM(_lparam);
						adjust(m_hwnd[_wparam], width, height, true);
					}
					break;

				case WM_USER_WINDOW_TOGGLE_FRAME:
					{
						if (m_frame)
						{
							m_oldWidth  = m_width;
							m_oldHeight = m_height;
						}
						adjust(m_hwnd[_wparam], m_oldWidth, m_oldHeight, !m_frame);
					}
					break;

				case WM_USER_WINDOW_MOUSE_LOCK:
					setMouseLock(m_hwnd[_wparam], !!_lparam);
					break;

				case WM_DESTROY:
					break;

				case WM_QUIT:
				case WM_CLOSE:
					destroyWindow(findHandle(_hwnd) );
					// Don't process message. Window will be destroyed later.
					return 0;

				case WM_SIZING:
					{
						WindowHandle handle = findHandle(_hwnd);

						if (isValid(handle)
						&&  ENTRY_WINDOW_FLAG_ASPECT_RATIO & m_flags[handle.idx])
						{
							RECT& rect = *(RECT*)_lparam;
							uint32_t width  = rect.right  - rect.left - m_frameWidth;
							uint32_t height = rect.bottom - rect.top  - m_frameHeight;

							// Recalculate size according to aspect ratio
							switch (_wparam)
							{
							case WMSZ_LEFT:
							case WMSZ_RIGHT:
								{
									float aspectRatio = 1.0f/m_aspectRatio;
									width  = bx::uint32_max(ENTRY_DEFAULT_WIDTH/4, width);
									height = uint32_t(float(width)*aspectRatio);
								}
								break;

							default:
								{
									float aspectRatio = m_aspectRatio;
									height = bx::uint32_max(ENTRY_DEFAULT_HEIGHT/4, height);
									width  = uint32_t(float(height)*aspectRatio);
								}
								break;
							}

							// Recalculate position using different anchor points
							switch(_wparam)
							{
							case WMSZ_LEFT:
							case WMSZ_TOPLEFT:
							case WMSZ_BOTTOMLEFT:
								rect.left   = rect.right - width  - m_frameWidth;
								rect.bottom = rect.top   + height + m_frameHeight;
								break;

							default:
								rect.right  = rect.left + width  + m_frameWidth;
								rect.bottom = rect.top  + height + m_frameHeight;
								break;
							}

							m_eventQueue.postSizeEvent(findHandle(_hwnd), width, height);
						}
					}
					return 0;

				case WM_SIZE:
					{
						WindowHandle handle = findHandle(_hwnd);
						if (isValid(handle) )
						{
							uint32_t width  = GET_X_LPARAM(_lparam);
							uint32_t height = GET_Y_LPARAM(_lparam);

							m_width  = width;
							m_height = height;
							m_eventQueue.postSizeEvent(handle, m_width, m_height);
						}
					}
					break;

				case WM_SYSCOMMAND:
					switch (_wparam)
					{
					case SC_MINIMIZE:
					case SC_RESTORE:
						{
							HWND parent = GetWindow(_hwnd, GW_OWNER);
							if (NULL != parent)
							{
								PostMessage(parent, _id, _wparam, _lparam);
							}
						}
					}
					break;

				case WM_MOUSEMOVE:
					{
						int32_t mx = GET_X_LPARAM(_lparam);
						int32_t my = GET_Y_LPARAM(_lparam);

						if (_hwnd == m_mouseLock)
						{
							mx -= m_mx;
							my -= m_my;

							if (0 == mx
							&&  0 == my)
							{
								break;
							}

							setMousePos(_hwnd, m_mx, m_my);
						}

						m_eventQueue.postMouseEvent(findHandle(_hwnd), mx, my, m_mz);
					}
					break;

				case WM_MOUSEWHEEL:
					{
						POINT pt = { GET_X_LPARAM(_lparam), GET_Y_LPARAM(_lparam) };
						ScreenToClient(_hwnd, &pt);
						int32_t mx = pt.x;
						int32_t my = pt.y;
						m_mz += GET_WHEEL_DELTA_WPARAM(_wparam)/WHEEL_DELTA;
						m_eventQueue.postMouseEvent(findHandle(_hwnd), mx, my, m_mz);
					}
					break;

				case WM_LBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_LBUTTONDBLCLK:
					{
						mouseCapture(_hwnd, _id == WM_LBUTTONDOWN);
						int32_t mx = GET_X_LPARAM(_lparam);
						int32_t my = GET_Y_LPARAM(_lparam);
						m_eventQueue.postMouseEvent(findHandle(_hwnd), mx, my, m_mz, MouseButton::Left, _id == WM_LBUTTONDOWN);
					}
					break;

				case WM_MBUTTONDOWN:
				case WM_MBUTTONUP:
				case WM_MBUTTONDBLCLK:
					{
						mouseCapture(_hwnd, _id == WM_MBUTTONDOWN);
						int32_t mx = GET_X_LPARAM(_lparam);
						int32_t my = GET_Y_LPARAM(_lparam);
						m_eventQueue.postMouseEvent(findHandle(_hwnd), mx, my, m_mz, MouseButton::Middle, _id == WM_MBUTTONDOWN);
					}
					break;

				case WM_RBUTTONDOWN:
				case WM_RBUTTONUP:
				case WM_RBUTTONDBLCLK:
					{
						mouseCapture(_hwnd, _id == WM_RBUTTONDOWN);
						int32_t mx = GET_X_LPARAM(_lparam);
						int32_t my = GET_Y_LPARAM(_lparam);
						m_eventQueue.postMouseEvent(findHandle(_hwnd), mx, my, m_mz, MouseButton::Right, _id == WM_RBUTTONDOWN);
					}
					break;

				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
				case WM_KEYUP:
				case WM_SYSKEYUP:
					{
						uint8_t modifiers = translateKeyModifiers();
						Key::Enum key = translateKey(_wparam);

						WindowHandle handle = findHandle(_hwnd);

						if (Key::Print == key
						&&  0x3 == ( (uint32_t)(_lparam)>>30) )
						{
							// VK_SNAPSHOT doesn't generate keydown event. Fire on down event when previous
							// key state bit is set to 1 and transition state bit is set to 1.
							//
							// http://msdn.microsoft.com/en-us/library/windows/desktop/ms646280%28v=vs.85%29.aspx
							m_eventQueue.postKeyEvent(handle, key, modifiers, true);
						}

						m_eventQueue.postKeyEvent(handle, key, modifiers, _id == WM_KEYDOWN || _id == WM_SYSKEYDOWN);
					}
					break;

				case WM_CHAR:
					{
						uint8_t utf8[4] = {};
						uint8_t len = (uint8_t)WideCharToMultiByte(CP_UTF8
											, 0
											, (LPCWSTR)&_wparam
											, 1
											, (LPSTR)utf8
											, BX_COUNTOF(utf8)
											, NULL
											, NULL
											);
						if (0 != len)
						{
							WindowHandle handle = findHandle(_hwnd);
							m_eventQueue.postCharEvent(handle, len, utf8);
						}
					}
					break;

				default:
					break;
				}
			}

			return DefWindowProc(_hwnd, _id, _wparam, _lparam);
		}

		WindowHandle findHandle(HWND _hwnd)
		{
			bx::MutexScope scope(m_lock);
			for (uint16_t ii = 0, num = m_windowAlloc.getNumHandles(); ii < num; ++ii)
			{
				uint16_t idx = m_windowAlloc.getHandleAt(ii);
				if (_hwnd == m_hwnd[idx])
				{
					WindowHandle handle = { idx };
					return handle;
				}
			}

			WindowHandle invalid = { UINT16_MAX };
			return invalid;
		}

		void clear(HWND _hwnd)
		{
			RECT rect;
			GetWindowRect(_hwnd, &rect);
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0) );
			HDC hdc = GetDC(_hwnd);
			SelectObject(hdc, brush);
			FillRect(hdc, &rect, brush);
		}

		void adjust(HWND _hwnd, uint32_t _width, uint32_t _height, bool _windowFrame)
		{
			m_width  = _width;
			m_height = _height;
			m_aspectRatio = float(_width)/float(_height);

			ShowWindow(_hwnd, SW_SHOWNORMAL);
			RECT rect;
			RECT newrect = {0, 0, (LONG)_width, (LONG)_height};
			DWORD style = WS_POPUP|WS_SYSMENU;

			if (m_frame)
			{
				GetWindowRect(_hwnd, &m_rect);
				m_style = GetWindowLong(_hwnd, GWL_STYLE);
			}

			if (_windowFrame)
			{
				rect = m_rect;
				style = m_style;
			}
			else
			{
#if defined(__MINGW32__)
				rect  = m_rect;
				style = m_style;
#else
				HMONITOR monitor = MonitorFromWindow(_hwnd, MONITOR_DEFAULTTONEAREST);
				MONITORINFO mi;
				mi.cbSize = sizeof(mi);
				GetMonitorInfo(monitor, &mi);
				newrect = mi.rcMonitor;
				rect = mi.rcMonitor;
				m_aspectRatio = float(newrect.right  - newrect.left)/float(newrect.bottom - newrect.top);
#endif // !defined(__MINGW__)
			}

			SetWindowLong(_hwnd, GWL_STYLE, style);
			uint32_t prewidth  = newrect.right - newrect.left;
			uint32_t preheight = newrect.bottom - newrect.top;
			AdjustWindowRect(&newrect, style, FALSE);
			m_frameWidth  = (newrect.right  - newrect.left) - prewidth;
			m_frameHeight = (newrect.bottom - newrect.top ) - preheight;
			UpdateWindow(_hwnd);

			if (rect.left == -32000
			||  rect.top  == -32000)
			{
				rect.left = 0;
				rect.top  = 0;
			}

			int32_t left   = rect.left;
			int32_t top    = rect.top;
			int32_t width  = (newrect.right-newrect.left);
			int32_t height = (newrect.bottom-newrect.top);

			if (!_windowFrame)
			{
				float aspectRatio = 1.0f/m_aspectRatio;
				width  = bx::uint32_max(ENTRY_DEFAULT_WIDTH/4, width);
				height = uint32_t(float(width)*aspectRatio);

				left   = newrect.left+(newrect.right -newrect.left-width)/2;
				top    = newrect.top +(newrect.bottom-newrect.top-height)/2;
			}

			SetWindowPos(_hwnd
				, HWND_TOP
				, left
				, top
				, width
				, height
				, SWP_SHOWWINDOW
				);

			ShowWindow(_hwnd, SW_RESTORE);

			m_frame = _windowFrame;
		}

		void setMousePos(HWND _hwnd, int32_t _mx, int32_t _my)
		{
			POINT pt = { _mx, _my };
			ClientToScreen(_hwnd, &pt);
			SetCursorPos(pt.x, pt.y);
		}

		void setMouseLock(HWND _hwnd, bool _lock)
		{
			if (_hwnd != m_mouseLock)
			{
				if (_lock)
				{
					m_mx = m_width/2;
					m_my = m_height/2;
					ShowCursor(false);
					setMousePos(_hwnd, m_mx, m_my);
				}
				else
				{
					setMousePos(_hwnd, m_mx, m_my);
					ShowCursor(true);
				}

				m_mouseLock = _hwnd;
			}
		}

		static LRESULT CALLBACK wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);

		EventQueue m_eventQueue;
		bx::Mutex m_lock;

		bx::HandleAllocT<ENTRY_CONFIG_MAX_WINDOWS> m_windowAlloc;

		HWND m_hwnd[ENTRY_CONFIG_MAX_WINDOWS];
		uint32_t m_flags[ENTRY_CONFIG_MAX_WINDOWS];
		RECT m_rect;
		DWORD m_style;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_oldWidth;
		uint32_t m_oldHeight;
		uint32_t m_frameWidth;
		uint32_t m_frameHeight;
		float m_aspectRatio;

		int32_t m_mx;
		int32_t m_my;
		int32_t m_mz;

		bool m_frame;
		HWND m_mouseLock;
		bool m_init;
		bool m_exit;

	};

	static Context s_ctx;

	LRESULT CALLBACK Context::wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
	{
		return s_ctx.process(_hwnd, _id, _wparam, _lparam);
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
			PostMessage(s_ctx.m_hwnd[0], WM_USER_WINDOW_CREATE, handle.idx, (LPARAM)msg);
		}

		return handle;
	}

	void destroyWindow(WindowHandle _handle)
	{
		if (UINT16_MAX != _handle.idx)
		{
			PostMessage(s_ctx.m_hwnd[0], WM_USER_WINDOW_DESTROY, _handle.idx, 0);

			bx::MutexScope scope(s_ctx.m_lock);
			s_ctx.m_windowAlloc.free(_handle.idx);
		}
	}

	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y)
	{
		Msg* msg = new Msg;
		msg->m_x = _x;
		msg->m_y = _y;
		PostMessage(s_ctx.m_hwnd[0], WM_USER_WINDOW_SET_POS, _handle.idx, (LPARAM)msg);
	}

	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height)
	{
		PostMessage(s_ctx.m_hwnd[0], WM_USER_WINDOW_SET_SIZE, _handle.idx, (_height<<16) | (_width&0xffff) );
	}

	void setWindowTitle(WindowHandle _handle, const char* _title)
	{
		Msg* msg = new Msg;
		msg->m_title = _title;
		PostMessage(s_ctx.m_hwnd[0], WM_USER_WINDOW_SET_TITLE, _handle.idx, (LPARAM)msg);
	}

	void toggleWindowFrame(WindowHandle _handle)
	{
		PostMessage(s_ctx.m_hwnd[0], WM_USER_WINDOW_TOGGLE_FRAME, _handle.idx, 0);
	}

	void toggleFullscreen(WindowHandle _handle)
	{
		PostMessage(s_ctx.m_hwnd[0], WM_USER_WINDOW_TOGGLE_FRAME, _handle.idx, 0);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		PostMessage(s_ctx.m_hwnd[0], WM_USER_WINDOW_MOUSE_LOCK, _handle.idx, _lock);
	}

	int32_t MainThreadEntry::threadFunc(void* _userData)
	{
		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = main(self->m_argc, self->m_argv);
		PostMessage(s_ctx.m_hwnd[0], WM_QUIT, 0, 0);
		return result;
	}

} // namespace entry

int main(int _argc, char** _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // BX_PLATFORM_WINDOWS
