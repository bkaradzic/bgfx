/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_WINDOWS

#include <bgfxplatform.h>

#include <bx/uint32_t.h>
#include <bx/thread.h>

#include <windowsx.h>

#define WM_USER_SET_WINDOW_SIZE     (WM_USER+0)
#define WM_USER_TOGGLE_WINDOW_FRAME (WM_USER+1)
#define WM_USER_MOUSE_LOCK          (WM_USER+2)

namespace entry
{
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

	struct Context
	{
		Context()
			: m_mz(0)
			, m_frame(true)
			, m_mouseLock(false)
			, m_init(false)
			, m_exit(false)
		{
			memset(s_translateKey, 0, sizeof(s_translateKey) );
			s_translateKey[VK_ESCAPE]    = Key::Esc;
			s_translateKey[VK_RETURN]    = Key::Return;
			s_translateKey[VK_TAB]       = Key::Tab;
			s_translateKey[VK_BACK]      = Key::Backspace;
			s_translateKey[VK_SPACE]     = Key::Space;
			s_translateKey[VK_UP]        = Key::Up;
			s_translateKey[VK_DOWN]      = Key::Down;
			s_translateKey[VK_LEFT]      = Key::Left;
			s_translateKey[VK_RIGHT]     = Key::Right;
			s_translateKey[VK_PRIOR]     = Key::PageUp;
			s_translateKey[VK_NEXT]      = Key::PageUp;
			s_translateKey[VK_HOME]      = Key::Home;
			s_translateKey[VK_END]       = Key::End;
			s_translateKey[VK_SNAPSHOT]  = Key::Print;
			s_translateKey[VK_OEM_PLUS]  = Key::Plus;
			s_translateKey[VK_OEM_MINUS] = Key::Minus;
			s_translateKey[VK_F1]        = Key::F1;
			s_translateKey[VK_F2]        = Key::F2;
			s_translateKey[VK_F3]        = Key::F3;
			s_translateKey[VK_F4]        = Key::F4;
			s_translateKey[VK_F5]        = Key::F5;
			s_translateKey[VK_F6]        = Key::F6;
			s_translateKey[VK_F7]        = Key::F7;
			s_translateKey[VK_F8]        = Key::F8;
			s_translateKey[VK_F9]        = Key::F9;
			s_translateKey[VK_F10]       = Key::F10;
			s_translateKey[VK_F11]       = Key::F11;
			s_translateKey[VK_F12]       = Key::F12;
			s_translateKey[VK_NUMPAD0]   = Key::NumPad0;
			s_translateKey[VK_NUMPAD1]   = Key::NumPad1;
			s_translateKey[VK_NUMPAD2]   = Key::NumPad2;
			s_translateKey[VK_NUMPAD3]   = Key::NumPad3;
			s_translateKey[VK_NUMPAD4]   = Key::NumPad4;
			s_translateKey[VK_NUMPAD5]   = Key::NumPad5;
			s_translateKey[VK_NUMPAD6]   = Key::NumPad6;
			s_translateKey[VK_NUMPAD7]   = Key::NumPad7;
			s_translateKey[VK_NUMPAD8]   = Key::NumPad8;
			s_translateKey[VK_NUMPAD9]   = Key::NumPad9;
			s_translateKey['0']          = Key::Key0;
			s_translateKey['1']          = Key::Key1;
			s_translateKey['2']          = Key::Key2;
			s_translateKey['3']          = Key::Key3;
			s_translateKey['4']          = Key::Key4;
			s_translateKey['5']          = Key::Key5;
			s_translateKey['6']          = Key::Key6;
			s_translateKey['7']          = Key::Key7;
			s_translateKey['8']          = Key::Key8;
			s_translateKey['9']          = Key::Key9;
			s_translateKey['A']          = Key::KeyA;
			s_translateKey['B']          = Key::KeyB;
			s_translateKey['C']          = Key::KeyC;
			s_translateKey['D']          = Key::KeyD;
			s_translateKey['E']          = Key::KeyE;
			s_translateKey['F']          = Key::KeyF;
			s_translateKey['G']          = Key::KeyG;
			s_translateKey['H']          = Key::KeyH;
			s_translateKey['I']          = Key::KeyI;
			s_translateKey['J']          = Key::KeyJ;
			s_translateKey['K']          = Key::KeyK;
			s_translateKey['L']          = Key::KeyL;
			s_translateKey['M']          = Key::KeyM;
			s_translateKey['N']          = Key::KeyN;
			s_translateKey['O']          = Key::KeyO;
			s_translateKey['P']          = Key::KeyP;
			s_translateKey['Q']          = Key::KeyQ;
			s_translateKey['R']          = Key::KeyR;
			s_translateKey['S']          = Key::KeyS;
			s_translateKey['T']          = Key::KeyT;
			s_translateKey['U']          = Key::KeyU;
			s_translateKey['V']          = Key::KeyV;
			s_translateKey['W']          = Key::KeyW;
			s_translateKey['X']          = Key::KeyX;
			s_translateKey['Y']          = Key::KeyY;
			s_translateKey['Z']          = Key::KeyZ;
		}

		int32_t run(int _argc, char** _argv)
		{
			SetDllDirectory(".");

			HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);

			WNDCLASSEX wnd;
			memset(&wnd, 0, sizeof(wnd) );
			wnd.cbSize = sizeof(wnd);
			wnd.lpfnWndProc = DefWindowProc;
			wnd.hInstance = instance;
			wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
			wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wnd.lpszClassName = "bgfx_letterbox";
			wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			RegisterClassExA(&wnd);

			memset(&wnd, 0, sizeof(wnd) );
			wnd.cbSize = sizeof(wnd);
			wnd.style = CS_HREDRAW | CS_VREDRAW;
			wnd.lpfnWndProc = wndProc;
			wnd.hInstance = instance;
			wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
			wnd.lpszClassName = "bgfx";
			wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
			RegisterClassExA(&wnd);

			HWND hwnd = CreateWindowA("bgfx_letterbox"
				, "BGFX"
				, WS_POPUP|WS_SYSMENU
				, -32000
				, -32000
				, 0
				, 0
				, NULL
				, NULL
				, instance
				, 0
				);

			m_hwnd = CreateWindowA("bgfx"
				, "BGFX"
				, WS_OVERLAPPEDWINDOW|WS_VISIBLE
				, 0
				, 0
				, ENTRY_DEFAULT_WIDTH
				, ENTRY_DEFAULT_HEIGHT
				, hwnd
				, NULL
				, instance
				, 0
				);

			bgfx::winSetHwnd(m_hwnd);

			adjust(ENTRY_DEFAULT_WIDTH, ENTRY_DEFAULT_HEIGHT, true);
			m_width = ENTRY_DEFAULT_WIDTH;
			m_height = ENTRY_DEFAULT_HEIGHT;
			m_oldWidth = ENTRY_DEFAULT_WIDTH;
			m_oldHeight = ENTRY_DEFAULT_HEIGHT;

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);
			m_init = true;

			m_eventQueue.postSizeEvent(m_width, m_height);

			MSG msg;
			msg.message = WM_NULL;

			while (!m_exit)
			{
				WaitMessage();

				while (0 != PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			thread.shutdown();

			DestroyWindow(m_hwnd);
			DestroyWindow(hwnd);

			return 0;
		}

		LRESULT process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
		{
			if (m_init)
			{
				switch (_id)
				{
				case WM_USER_SET_WINDOW_SIZE:
					{
						uint32_t width = GET_X_LPARAM(_lparam);
						uint32_t height = GET_Y_LPARAM(_lparam);
						adjust(width, height, true);
					}
					break;

				case WM_USER_TOGGLE_WINDOW_FRAME:
					{
						if (m_frame)
						{
							m_oldWidth = m_width;
							m_oldHeight = m_height;
						}
						adjust(m_oldWidth, m_oldHeight, !m_frame);
					}
					break;

				case WM_USER_MOUSE_LOCK:
					setMouseLock(!!_lparam);
					break;

				case WM_DESTROY:
					break;

				case WM_QUIT:
				case WM_CLOSE:
					m_exit = true;
					m_eventQueue.postExitEvent();
					break;

				case WM_SIZING:
					{
						RECT& rect = *(RECT*)_lparam;
						uint32_t width = rect.right - rect.left - m_frameWidth;
						uint32_t height = rect.bottom - rect.top - m_frameHeight;

						//Recalculate size according to aspect ratio
						switch (_wparam)
						{
						case WMSZ_LEFT:
						case WMSZ_RIGHT:
							{
								float aspectRatio = 1.0f/m_aspectRatio;
								width = bx::uint32_max(ENTRY_DEFAULT_WIDTH/4, width);
								height = uint32_t(float(width)*aspectRatio);
							}
							break;

						default:
							{
								float aspectRatio = m_aspectRatio;
								height = bx::uint32_max(ENTRY_DEFAULT_HEIGHT/4, height);
								width = uint32_t(float(height)*aspectRatio);
							}
							break;
						}

						//Recalculate position using different anchor points
						switch(_wparam)
						{
						case WMSZ_LEFT:
						case WMSZ_TOPLEFT:
						case WMSZ_BOTTOMLEFT:
							rect.left = rect.right - width - m_frameWidth;
							rect.bottom = rect.top + height + m_frameHeight;
							break;

						default:
							rect.right = rect.left + width + m_frameWidth;
							rect.bottom = rect.top + height + m_frameHeight;
							break;
						}

						m_eventQueue.postSizeEvent(m_width, m_height);
					}
					return 0;

				case WM_SIZE:
					{
						uint32_t width = GET_X_LPARAM(_lparam);
						uint32_t height = GET_Y_LPARAM(_lparam);

						m_width = width;
						m_height = height;
						m_eventQueue.postSizeEvent(m_width, m_height);
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

						if (m_mouseLock)
						{
							mx -= m_mx;
							my -= m_my;

							if (0 == mx
							&&  0 == my)
							{
								break;
							}

							setMousePos(m_mx, m_my);
						}

						m_eventQueue.postMouseEvent(mx, my, m_mz);
					}
					break;

				case WM_MOUSEWHEEL:
					{
						POINT pt = { GET_X_LPARAM(_lparam), GET_Y_LPARAM(_lparam) };
						ScreenToClient(m_hwnd, &pt);
						int32_t mx = pt.x;
						int32_t my = pt.y;
						m_mz += GET_WHEEL_DELTA_WPARAM(_wparam);
						m_eventQueue.postMouseEvent(mx, my, m_mz);
					}
					break;

				case WM_LBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_LBUTTONDBLCLK:
					{
						int32_t mx = GET_X_LPARAM(_lparam);
						int32_t my = GET_Y_LPARAM(_lparam);
						m_eventQueue.postMouseEvent(mx, my, m_mz, MouseButton::Left, _id == WM_LBUTTONDOWN);
					}
					break;

				case WM_MBUTTONDOWN:
				case WM_MBUTTONUP:
				case WM_MBUTTONDBLCLK:
					{
						int32_t mx = GET_X_LPARAM(_lparam);
						int32_t my = GET_Y_LPARAM(_lparam);
						m_eventQueue.postMouseEvent(mx, my, m_mz, MouseButton::Middle, _id == WM_MBUTTONDOWN);
					}
					break;

				case WM_RBUTTONUP:
				case WM_RBUTTONDOWN:
				case WM_RBUTTONDBLCLK:
					{
						int32_t mx = GET_X_LPARAM(_lparam);
						int32_t my = GET_Y_LPARAM(_lparam);
						m_eventQueue.postMouseEvent(mx, my, m_mz, MouseButton::Right, _id == WM_RBUTTONDOWN);
					}
					break;

				case WM_KEYDOWN:
				case WM_SYSKEYDOWN:
				case WM_KEYUP:
				case WM_SYSKEYUP:
					{
						uint8_t modifiers = translateKeyModifiers();
						Key::Enum key = translateKey(_wparam);

						if (Key::Print == key
						&&  0x3 == ( (uint32_t)(_lparam)>>30) )
						{
							// VK_SNAPSHOT doesn't generate keydown event. Fire on down event when previous
							// key state bit is set to 1 and transition state bit is set to 1.
							//
							// http://msdn.microsoft.com/en-us/library/windows/desktop/ms646280%28v=vs.85%29.aspx
							m_eventQueue.postKeyEvent(key, modifiers, true);
						}

						m_eventQueue.postKeyEvent(key, modifiers, _id == WM_KEYDOWN || _id == WM_SYSKEYDOWN);
					}
					break;

				default:
					break;
				}
			}

			return DefWindowProc(_hwnd, _id, _wparam, _lparam);
		}

		void adjust(uint32_t _width, uint32_t _height, bool _windowFrame)
		{
			m_width = _width;
			m_height = _height;
			m_aspectRatio = float(_width)/float(_height);

			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			RECT rect;
			RECT newrect = {0, 0, (LONG)_width, (LONG)_height};
			DWORD style = WS_POPUP|WS_SYSMENU;

			if (m_frame)
			{
				GetWindowRect(m_hwnd, &m_rect);
				m_style = GetWindowLong(m_hwnd, GWL_STYLE);
			}

			if (_windowFrame)
			{
				rect = m_rect;
				style = m_style;
			}
			else
			{
#if defined(__MINGW32__)
				rect = m_rect;
				style = m_style;
#else
				HMONITOR monitor = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);
				MONITORINFO mi;
				mi.cbSize = sizeof(mi);
				GetMonitorInfo(monitor, &mi);
				newrect = mi.rcMonitor;
				rect = mi.rcMonitor;
#endif // !defined(__MINGW__)
			}

			SetWindowLong(m_hwnd, GWL_STYLE, style);
			uint32_t prewidth = newrect.right - newrect.left;
			uint32_t preheight = newrect.bottom - newrect.top;
			AdjustWindowRect(&newrect, style, FALSE);
			m_frameWidth = (newrect.right - newrect.left) - prewidth;
			m_frameHeight = (newrect.bottom - newrect.top) - preheight;
			UpdateWindow(m_hwnd);

			if (rect.left == -32000
			||  rect.top == -32000)
			{
				rect.left = 0;
				rect.top = 0;
			}

			int32_t left = rect.left;
			int32_t top = rect.top;
			int32_t width = (newrect.right-newrect.left);
			int32_t height = (newrect.bottom-newrect.top);

			if (!_windowFrame)
			{
				float aspectRatio = 1.0f/m_aspectRatio;
				width = bx::uint32_max(ENTRY_DEFAULT_WIDTH/4, width);
				height = uint32_t(float(width)*aspectRatio);

				left = newrect.left+(newrect.right-newrect.left-width)/2;
				top = newrect.top+(newrect.bottom-newrect.top-height)/2;
			}

			HWND parent = GetWindow(m_hwnd, GW_OWNER);
			if (NULL != parent)
			{
				if (_windowFrame)
				{
					SetWindowPos(parent
						, HWND_TOP
						, -32000
						, -32000
						, 0
						, 0
						, SWP_SHOWWINDOW
						);
				}
				else
				{
					SetWindowPos(parent
						, HWND_TOP
						, newrect.left
						, newrect.top
						, newrect.right-newrect.left
						, newrect.bottom-newrect.top
						, SWP_SHOWWINDOW
						);
				}
			}

			SetWindowPos(m_hwnd
				, HWND_TOP
				, left
				, top
				, width
				, height
				, SWP_SHOWWINDOW
				);

			ShowWindow(m_hwnd, SW_RESTORE);

			m_frame = _windowFrame;
		}

		void setMousePos(int32_t _mx, int32_t _my)
		{
			POINT pt = { _mx, _my };
			ClientToScreen(m_hwnd, &pt);
			SetCursorPos(pt.x, pt.y);
		}

		void setMouseLock(bool _lock)
		{
			if (_lock != m_mouseLock)
			{
				if (_lock)
				{
					m_mx = m_width/2;
					m_my = m_height/2;
					ShowCursor(false);
					setMousePos(m_mx, m_my);
				}
				else
				{
					setMousePos(m_mx, m_my);
					ShowCursor(true);
				}

				m_mouseLock = _lock;
			}
		}

		static LRESULT CALLBACK wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);

		EventQueue m_eventQueue;

		HWND m_hwnd;
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
		bool m_mouseLock;
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

	void release(const Event* _event)
	{
		s_ctx.m_eventQueue.release(_event);
	}

	void setWindowSize(uint32_t _width, uint32_t _height)
	{
		PostMessage(s_ctx.m_hwnd, WM_USER_SET_WINDOW_SIZE, 0, (_height<<16) | (_width&0xffff) );
	}

	void setWindowTitle(const char* _title)
	{
		SetWindowTextA(s_ctx.m_hwnd, _title);
		SetWindowTextA(GetWindow(s_ctx.m_hwnd, GW_HWNDNEXT), _title);
	}

	void toggleWindowFrame()
	{
		PostMessage(s_ctx.m_hwnd, WM_USER_TOGGLE_WINDOW_FRAME, 0, 0);
	}

	void setMouseLock(bool _lock)
	{
		PostMessage(s_ctx.m_hwnd, WM_USER_MOUSE_LOCK, 0, _lock);
	}

	int32_t MainThreadEntry::threadFunc(void* _userData)
	{
		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = main(self->m_argc, self->m_argv);
		PostMessage(s_ctx.m_hwnd, WM_QUIT, 0, 0);
		return result;
	}

} // namespace entry

int main(int _argc, char** _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // BX_PLATFORM_WINDOWS
