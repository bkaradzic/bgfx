/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bx/bx.h>

#if BX_PLATFORM_WINDOWS

#include <bgfxplatform.h>
#include <bx/uint32_t.h>
#include <bx/thread.h>

#include "entry.h"
#include "dbg.h"

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
		Context()
			: m_frame(true)
			, m_exit(false)
		{
		}

		int32_t main(int _argc, char** _argv)
		{
			HINSTANCE instance = (HINSTANCE)GetModuleHandle(NULL);

			WNDCLASSEX wnd;
			memset(&wnd, 0, sizeof(wnd) );
			wnd.cbSize = sizeof(wnd);
			wnd.lpfnWndProc = DefWindowProc;
			wnd.hInstance = instance;
			wnd.hIcon = LoadIcon(instance, IDI_APPLICATION);
			wnd.hCursor = LoadCursor(instance, IDC_ARROW);
			wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wnd.lpszClassName = "bgfx_letterbox";
			wnd.hIconSm = LoadIcon(instance, IDI_APPLICATION);
			RegisterClassExA(&wnd);

			memset(&wnd, 0, sizeof(wnd) );
			wnd.cbSize = sizeof(wnd);
			wnd.style = CS_HREDRAW | CS_VREDRAW;
			wnd.lpfnWndProc = wndProc;
			wnd.hInstance = instance;
			wnd.hIcon = LoadIcon(instance, IDI_APPLICATION);
			wnd.hCursor = LoadCursor(instance, IDC_ARROW);
			wnd.lpszClassName = "bgfx";
			wnd.hIconSm = LoadIcon(instance, IDI_APPLICATION);
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
				, DEFAULT_WIDTH
				, DEFAULT_HEIGHT
				, hwnd
				, NULL
				, instance
				, 0
				);

			bgfx::setHwnd(m_hwnd);

			adjust(DEFAULT_WIDTH, DEFAULT_HEIGHT, true);

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);

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

			return 0;
		}

		LRESULT process(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
		{
			switch (_id)
			{
			case WM_CLOSE:
				TerminateProcess(GetCurrentProcess(), 0);
				break;

			case WM_SIZING:
				{
					RECT clientRect;
					GetClientRect(_hwnd, &clientRect);
					uint32_t width = clientRect.right-clientRect.left;
					uint32_t height = clientRect.bottom-clientRect.top;

					RECT& rect = *(RECT*)_lparam;
					uint32_t frameWidth = rect.right-rect.left - width;
					uint32_t frameHeight = rect.bottom-rect.top - height;

					switch (_wparam)
					{
					case WMSZ_LEFT:
					case WMSZ_RIGHT:
						{
							float aspectRatio = 1.0f/m_aspectRatio;
							width = bx::uint32_max(DEFAULT_WIDTH/4, width);
							height = uint32_t(float(width)*aspectRatio);
						}
						break;

					default:
						{
							float aspectRatio = m_aspectRatio;
							height = bx::uint32_max(DEFAULT_HEIGHT/4, height);
							width = uint32_t(float(height)*aspectRatio);
						}
						break;
					}

					rect.right = rect.left + width + frameWidth;
					rect.bottom = rect.top + height + frameHeight;

					SetWindowPos(_hwnd
						, HWND_TOP
						, rect.left
						, rect.top
						, (rect.right-rect.left)
						, (rect.bottom-rect.top)
						, SWP_SHOWWINDOW
						);
				}
				return 0;

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

			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				if ((WM_KEYDOWN == _id && VK_F11 == _wparam)
				||  (WM_SYSKEYDOWN == _id && VK_RETURN == _wparam) )
				{
					toggleWindowFrame();
				}
				break;

			default:
				break;
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
			AdjustWindowRect(&newrect, style, FALSE);
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
				width = bx::uint32_max(DEFAULT_WIDTH/4, width);
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

		static LRESULT CALLBACK wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam);

		void toggleWindowFrame()
		{
			adjust(m_width, m_height, !m_frame);
		}

		HWND m_hwnd;
		RECT m_rect;
		DWORD m_style;
		uint32_t m_width;
		uint32_t m_height;
		float m_aspectRatio;
		bool m_frame;
		bool m_exit;
	};

	static Context s_ctx;

	LRESULT CALLBACK Context::wndProc(HWND _hwnd, UINT _id, WPARAM _wparam, LPARAM _lparam)
	{
		return s_ctx.process(_hwnd, _id, _wparam, _lparam);
	}

	Event::Enum poll()
	{
		return Event::Nop;
	}

} // namespace entry

int main(int _argc, char** _argv)
{
	using namespace entry;
	return s_ctx.main(_argc, _argv);
}

#endif // BX_PLATFORM_WINDOWS
