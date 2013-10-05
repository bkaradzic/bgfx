/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_LINUX

#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>
#include <bgfxplatform.h> // will include X11 which #defines None... Don't mess with order of includes.

#undef None
#include <bx/thread.h>
#include <bx/os.h>
#include <string.h> // memset

namespace entry
{
	static uint8_t s_translateKey[512];

	static void initTranslateKey(uint16_t _xk, Key::Enum _key)
	{
		_xk += 256;
		BX_CHECK(_xk < BX_COUNTOF(s_translateKey), "Out of bounds %d.", _xk);
		s_translateKey[_xk&0x1ff] = (uint8_t)_key;
	}

	Key::Enum fromXk(uint16_t _xk)
	{
		_xk += 256;
		return 512 > _xk ? (Key::Enum)s_translateKey[_xk] : Key::None;
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
			: m_modifiers(Modifier::None)
			, m_exit(false)
		{
			memset(s_translateKey, 0, sizeof(s_translateKey) );
			initTranslateKey(XK_Escape,       Key::Esc);
			initTranslateKey(XK_Return,       Key::Return);
			initTranslateKey(XK_Tab,          Key::Tab);
			initTranslateKey(XK_BackSpace,    Key::Backspace);
			initTranslateKey(XK_space,        Key::Space);
			initTranslateKey(XK_Up,           Key::Up);
			initTranslateKey(XK_Down,         Key::Down);
			initTranslateKey(XK_Left,         Key::Left);
			initTranslateKey(XK_Right,        Key::Right);
			initTranslateKey(XK_Page_Up,      Key::PageUp);
			initTranslateKey(XK_Page_Down,    Key::PageUp);
			initTranslateKey(XK_Home,         Key::Home);
			initTranslateKey(XK_KP_End,       Key::End);
			initTranslateKey(XK_Print,        Key::Print);
			initTranslateKey(XK_equal,        Key::Plus);
			initTranslateKey(XK_minus,        Key::Minus);
			initTranslateKey(XK_F1,           Key::F1);
			initTranslateKey(XK_F2,           Key::F2);
			initTranslateKey(XK_F3,           Key::F3);
			initTranslateKey(XK_F4,           Key::F4);
			initTranslateKey(XK_F5,           Key::F5);
			initTranslateKey(XK_F6,           Key::F6);
			initTranslateKey(XK_F7,           Key::F7);
			initTranslateKey(XK_F8,           Key::F8);
			initTranslateKey(XK_F9,           Key::F9);
			initTranslateKey(XK_F10,          Key::F10);
			initTranslateKey(XK_F11,          Key::F11);
			initTranslateKey(XK_F12,          Key::F12);
			initTranslateKey(XK_KP_Insert,    Key::NumPad0);
			initTranslateKey(XK_KP_End,       Key::NumPad1);
			initTranslateKey(XK_KP_Down,      Key::NumPad2);
			initTranslateKey(XK_KP_Page_Down, Key::NumPad3);
			initTranslateKey(XK_KP_Left,      Key::NumPad4);
			initTranslateKey(XK_KP_Begin,     Key::NumPad5);
			initTranslateKey(XK_KP_Right,     Key::NumPad6);
			initTranslateKey(XK_KP_Home,      Key::NumPad7);
			initTranslateKey(XK_KP_Up,        Key::NumPad8);
			initTranslateKey(XK_KP_Page_Up,   Key::NumPad9);
			initTranslateKey('0',             Key::Key0);
			initTranslateKey('1',             Key::Key1);
			initTranslateKey('2',             Key::Key2);
			initTranslateKey('3',             Key::Key3);
			initTranslateKey('4',             Key::Key4);
			initTranslateKey('5',             Key::Key5);
			initTranslateKey('6',             Key::Key6);
			initTranslateKey('7',             Key::Key7);
			initTranslateKey('8',             Key::Key8);
			initTranslateKey('9',             Key::Key9);
			initTranslateKey('a',             Key::KeyA);
			initTranslateKey('b',             Key::KeyB);
			initTranslateKey('c',             Key::KeyC);
			initTranslateKey('d',             Key::KeyD);
			initTranslateKey('e',             Key::KeyE);
			initTranslateKey('f',             Key::KeyF);
			initTranslateKey('g',             Key::KeyG);
			initTranslateKey('h',             Key::KeyH);
			initTranslateKey('i',             Key::KeyI);
			initTranslateKey('j',             Key::KeyJ);
			initTranslateKey('k',             Key::KeyK);
			initTranslateKey('l',             Key::KeyL);
			initTranslateKey('m',             Key::KeyM);
			initTranslateKey('n',             Key::KeyN);
			initTranslateKey('o',             Key::KeyO);
			initTranslateKey('p',             Key::KeyP);
			initTranslateKey('q',             Key::KeyQ);
			initTranslateKey('r',             Key::KeyR);
			initTranslateKey('s',             Key::KeyS);
			initTranslateKey('t',             Key::KeyT);
			initTranslateKey('u',             Key::KeyU);
			initTranslateKey('v',             Key::KeyV);
			initTranslateKey('w',             Key::KeyW);
			initTranslateKey('x',             Key::KeyX);
			initTranslateKey('y',             Key::KeyY);
			initTranslateKey('z',             Key::KeyZ);
		}

		int32_t run(int _argc, char** _argv)
		{
			XInitThreads();
			m_display = XOpenDisplay(0);

			int32_t screen = DefaultScreen(m_display);
			int32_t depth = DefaultDepth(m_display, screen);
			Visual* visual = DefaultVisual(m_display, screen);
			Window root = RootWindow(m_display, screen);

			XSetWindowAttributes windowAttrs;
			memset(&windowAttrs, 0, sizeof(windowAttrs) );
			windowAttrs.background_pixmap = 0;
			windowAttrs.border_pixel = 0;
			windowAttrs.event_mask = 0
					| ButtonPressMask
					| ButtonReleaseMask
					| ExposureMask
					| KeyPressMask
					| KeyReleaseMask
					| PointerMotionMask
					| ResizeRedirectMask
					| StructureNotifyMask
					;

			m_window = XCreateWindow(m_display
									, root
									, 0, 0
									, ENTRY_DEFAULT_WIDTH, ENTRY_DEFAULT_HEIGHT, 0, depth
									, InputOutput
									, visual
									, CWBorderPixel|CWEventMask
									, &windowAttrs
									);

			const char *wmDeleteWindowName = "WM_DELETE_WINDOW";
			Atom wmDeleteWindow;
			XInternAtoms(m_display, (char **)&wmDeleteWindowName, 1, False, &wmDeleteWindow);
			XSetWMProtocols(m_display, m_window, &wmDeleteWindow, 1);

			XMapWindow(m_display, m_window);
			XStoreName(m_display, m_window, "BGFX");

			bgfx::x11SetDisplayWindow(m_display, m_window);

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);

			while (!m_exit)
			{
				if (XPending(m_display) )
				{
					XEvent event;
					XNextEvent(m_display, &event);

					switch (event.type)
					{
						case Expose:
							break;

						case ConfigureNotify:
							break;

						case ClientMessage:
							if((Atom)event.xclient.data.l[0] == wmDeleteWindow)
							{
								m_eventQueue.postExitEvent();
							}
							break;

						case ButtonPress:
						case ButtonRelease:
							{
								const XButtonEvent& xbutton = event.xbutton;
								MouseButton::Enum mb;
								switch (xbutton.button)
								{
									case Button1: mb = MouseButton::Left;   break;
									case Button2: mb = MouseButton::Middle; break;
									case Button3: mb = MouseButton::Right;  break;
									default:      mb = MouseButton::None;   break;
								}

								if (MouseButton::None != mb)
								{
									m_eventQueue.postMouseEvent(xbutton.x
										, xbutton.y
										, mb
										, event.type == ButtonPress
										);
								}
							}
							break;

						case MotionNotify:
							{
								const XMotionEvent& xmotion = event.xmotion;
								m_eventQueue.postMouseEvent(xmotion.x
										, xmotion.y
										);
							}
							break;

						case KeyPress:
						case KeyRelease:
							{
								XKeyEvent& xkey = event.xkey;
								KeySym keysym = XLookupKeysym(&xkey, 0);
								switch (keysym)
								{
								case XK_Meta_L:    setModifier(Modifier::LeftMeta,   KeyPress == event.type); break;
								case XK_Meta_R:    setModifier(Modifier::RightMeta,  KeyPress == event.type); break;
								case XK_Control_L: setModifier(Modifier::LeftCtrl,   KeyPress == event.type); break;
								case XK_Control_R: setModifier(Modifier::RightCtrl,  KeyPress == event.type); break;
								case XK_Shift_L:   setModifier(Modifier::LeftShift,  KeyPress == event.type); break;
								case XK_Shift_R:   setModifier(Modifier::RightShift, KeyPress == event.type); break;
								case XK_Alt_L:     setModifier(Modifier::LeftAlt,    KeyPress == event.type); break;
								case XK_Alt_R:     setModifier(Modifier::RightAlt,   KeyPress == event.type); break;

								default:
									{
										Key::Enum key = fromXk(keysym);
										if (Key::None != key)
										{
											m_eventQueue.postKeyEvent(key, m_modifiers, KeyPress == event.type);
										}
									}
									break;
								}
							}
							break;

						case ResizeRequest:
							{
								const XResizeRequestEvent& xresize = event.xresizerequest;
								XResizeWindow(m_display, m_window, xresize.width, xresize.height);
							}
							break;
					}
				}
			}

			thread.shutdown();

			XUnmapWindow(m_display, m_window);
			XDestroyWindow(m_display, m_window);

			return EXIT_SUCCESS;
		}

		void setModifier(Modifier::Enum _modifier, bool _set)
		{
			m_modifiers &= ~_modifier;
			m_modifiers |= _set ? _modifier : 0;
		}

		uint8_t m_modifiers;
		Display* m_display;
		Window m_window;
		bool m_exit;

		EventQueue m_eventQueue;
	};

	static Context s_ctx;

	int32_t MainThreadEntry::threadFunc(void* _userData)
	{
		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = main(self->m_argc, self->m_argv);
		s_ctx.m_exit = true;
		return result;
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
		XResizeRequestEvent ev;
		ev.type = ResizeRequest;
		ev.serial = 0;
		ev.send_event = true;
		ev.display = s_ctx.m_display;
		ev.window = s_ctx.m_window;
		ev.width = (int)_width;
		ev.height = (int)_height;
		XSendEvent(s_ctx.m_display, s_ctx.m_window, false, ResizeRedirectMask, (XEvent*)&ev);
	}

	void toggleWindowFrame()
	{
	}

	void setMouseLock(bool _lock)
	{
	}

} // namespace entry

int main(int _argc, char** _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // ENTRY_CONFIG_USE_NATIVE && BX_PLATFORM_LINUX
