/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "entry_p.h"

#if ENTRY_CONFIG_USE_NATIVE && (BX_PLATFORM_BSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI)

#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>
#include <X11/Xlib.h> // will include X11 which #defines None... Don't mess with order of includes.
#include <X11/Xutil.h>
#include <bgfx/platform.h>

#include <unistd.h> // syscall

#undef None
#include <bx/thread.h>
#include <bx/os.h>
#include <bx/handlealloc.h>
#include <bx/mutex.h>

#include <string>

#include <fcntl.h>

namespace entry
{
	static const char* s_applicationName  = "BGFX";
	static const char* s_applicationClass = "bgfx";

	///
	inline void x11SetDisplayWindow(void* _display, uint32_t _window, void* _glx = NULL)
	{
		bgfx::PlatformData pd;
		pd.ndt          = _display;
		pd.nwh          = (void*)(uintptr_t)_window;
		pd.context      = _glx;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		bgfx::setPlatformData(pd);
	}

#define JS_EVENT_BUTTON 0x01 /* button pressed/released */
#define JS_EVENT_AXIS   0x02 /* joystick moved */
#define JS_EVENT_INIT   0x80 /* initial state of device */

	struct JoystickEvent
	{
		uint32_t time;   /* event timestamp in milliseconds */
		int16_t  value;  /* value */
		uint8_t  type;   /* event type */
		uint8_t  number; /* axis/button number */
	};

	static Key::Enum s_translateButton[] =
	{
		Key::GamepadA,
		Key::GamepadB,
		Key::GamepadX,
		Key::GamepadY,
		Key::GamepadShoulderL,
		Key::GamepadShoulderR,
		Key::GamepadBack,
		Key::GamepadStart,
		Key::GamepadGuide,
		Key::GamepadThumbL,
		Key::GamepadThumbR,
	};

	static GamepadAxis::Enum s_translateAxis[] =
	{
		GamepadAxis::LeftX,
		GamepadAxis::LeftY,
		GamepadAxis::LeftZ,
		GamepadAxis::RightX,
		GamepadAxis::RightY,
		GamepadAxis::RightZ,
	};

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
	BX_STATIC_ASSERT(BX_COUNTOF(s_translateAxis) == BX_COUNTOF(s_axisDpad) );

	struct Joystick
	{
		Joystick()
			: m_fd(-1)
		{
		}

		void init()
		{
			m_fd = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);

			bx::memSet(m_value, 0, sizeof(m_value) );

			// Deadzone values from xinput.h
			m_deadzone[GamepadAxis::LeftX ] =
			m_deadzone[GamepadAxis::LeftY ] = 7849;
			m_deadzone[GamepadAxis::RightX] =
			m_deadzone[GamepadAxis::RightY] = 8689;
			m_deadzone[GamepadAxis::LeftZ ] =
			m_deadzone[GamepadAxis::RightZ] = 30;
		}

		void shutdown()
		{
			if (-1 != m_fd)
			{
				close(m_fd);
			}
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

		bool update(EventQueue& _eventQueue)
		{
			if (-1 == m_fd)
			{
				return false;
			}

			JoystickEvent event;
			int32_t bytes = read(m_fd, &event, sizeof(JoystickEvent) );
			if (bytes != sizeof(JoystickEvent) )
			{
				return false;
			}

			WindowHandle defaultWindow = { 0 };
			GamepadHandle handle = { 0 };

			if (event.type & JS_EVENT_BUTTON)
			{
				if (event.number < BX_COUNTOF(s_translateButton) )
				{
					_eventQueue.postKeyEvent(defaultWindow, s_translateButton[event.number], 0, 0 != event.value);
				}
			}
			else if (event.type & JS_EVENT_AXIS)
			{
				if (event.number < BX_COUNTOF(s_translateAxis) )
				{
					GamepadAxis::Enum axis = s_translateAxis[event.number];
					int32_t value = event.value;
					if (filter(axis, &value) )
					{
						_eventQueue.postAxisEvent(defaultWindow, handle, axis, value);

						if (Key::None != s_axisDpad[axis].first)
						{
							if (m_value[axis] == 0)
							{
								_eventQueue.postKeyEvent(defaultWindow, s_axisDpad[axis].first,  0, false);
								_eventQueue.postKeyEvent(defaultWindow, s_axisDpad[axis].second, 0, false);
							}
							else
							{
								_eventQueue.postKeyEvent(defaultWindow
									, 0 > m_value[axis] ? s_axisDpad[axis].first : s_axisDpad[axis].second
									, 0
									, true
									);
							}
						}

					}
				}
			}

			return true;
		}

		int m_fd;
		int32_t m_value[GamepadAxis::Count];
		int32_t m_deadzone[GamepadAxis::Count];
	};

	static Joystick s_joystick;

	static uint8_t s_translateKey[512];

	static void initTranslateKey(uint16_t _xk, Key::Enum _key)
	{
		_xk += 256;
		BX_ASSERT(_xk < BX_COUNTOF(s_translateKey), "Out of bounds %d.", _xk);
		s_translateKey[_xk&0x1ff] = (uint8_t)_key;
	}

	Key::Enum fromXk(uint16_t _xk)
	{
		_xk += 256;
		return 512 > _xk ? (Key::Enum)s_translateKey[_xk] : Key::None;
	}

	struct MainThreadEntry
	{
		int32_t m_argc;
		const char* const* m_argv;

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
		{
		}

		int32_t  m_x;
		int32_t  m_y;
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_flags;
		std::string m_title;
	};

	struct Context
	{
		Context()
			: m_modifiers(Modifier::None)
			, m_exit(false)
		{
			bx::memSet(s_translateKey, 0, sizeof(s_translateKey) );
			initTranslateKey(XK_Escape,       Key::Esc);
			initTranslateKey(XK_Return,       Key::Return);
			initTranslateKey(XK_Tab,          Key::Tab);
			initTranslateKey(XK_BackSpace,    Key::Backspace);
			initTranslateKey(XK_space,        Key::Space);
			initTranslateKey(XK_Up,           Key::Up);
			initTranslateKey(XK_Down,         Key::Down);
			initTranslateKey(XK_Left,         Key::Left);
			initTranslateKey(XK_Right,        Key::Right);
			initTranslateKey(XK_Insert,       Key::Insert);
			initTranslateKey(XK_Delete,       Key::Delete);
			initTranslateKey(XK_Home,         Key::Home);
			initTranslateKey(XK_KP_End,       Key::End);
			initTranslateKey(XK_Page_Up,      Key::PageUp);
			initTranslateKey(XK_Page_Down,    Key::PageDown);
			initTranslateKey(XK_Print,        Key::Print);
			initTranslateKey(XK_equal,        Key::Plus);
			initTranslateKey(XK_minus,        Key::Minus);
			initTranslateKey(XK_bracketleft,  Key::LeftBracket);
			initTranslateKey(XK_bracketright, Key::RightBracket);
			initTranslateKey(XK_semicolon,    Key::Semicolon);
			initTranslateKey(XK_apostrophe,   Key::Quote);
			initTranslateKey(XK_comma,        Key::Comma);
			initTranslateKey(XK_period,       Key::Period);
			initTranslateKey(XK_slash,        Key::Slash);
			initTranslateKey(XK_backslash,    Key::Backslash);
			initTranslateKey(XK_grave,        Key::Tilde);
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

			m_mx = 0;
			m_my = 0;
			m_mz = 0;
		}

		int32_t run(int _argc, const char* const* _argv)
		{
			XInitThreads();
			m_display = XOpenDisplay(NULL);

			int32_t screen = DefaultScreen(m_display);
			m_depth  = DefaultDepth(m_display, screen);
			m_visual = DefaultVisual(m_display, screen);
			m_root   = RootWindow(m_display, screen);

			bx::memSet(&m_windowAttrs, 0, sizeof(m_windowAttrs) );
			m_windowAttrs.background_pixel = 0;
			m_windowAttrs.border_pixel = 0;
			m_windowAttrs.bit_gravity = StaticGravity;
			m_windowAttrs.event_mask = 0
					| ButtonPressMask
					| ButtonReleaseMask
					| ExposureMask
					| KeyPressMask
					| KeyReleaseMask
					| PointerMotionMask
					| StructureNotifyMask
					;

			m_windowAlloc.alloc();
			m_window[0] = XCreateWindow(m_display
									, m_root
									, 0, 0
									, 1, 1, 0
									, m_depth
									, InputOutput
									, m_visual
									, CWBorderPixel|CWEventMask|CWBackPixel|CWBitGravity
									, &m_windowAttrs
									);

			const char* wmDeleteWindowName = "WM_DELETE_WINDOW";
			Atom wmDeleteWindow;
			XInternAtoms(m_display, (char **)&wmDeleteWindowName, 1, False, &wmDeleteWindow);
			XSetWMProtocols(m_display, m_window[0], &wmDeleteWindow, 1);

			XMapWindow(m_display, m_window[0]);
			XStoreName(m_display, m_window[0], s_applicationName);

			XClassHint* hint = XAllocClassHint();
			hint->res_name  = (char*)s_applicationName;
			hint->res_class = (char*)s_applicationClass;
			XSetClassHint(m_display, m_window[0], hint);
			XFree(hint);

			XIM im;
			im = XOpenIM(m_display, NULL, NULL, NULL);

			XIC ic;
			ic = XCreateIC(im
					, XNInputStyle
					, 0
					| XIMPreeditNothing
					| XIMStatusNothing
					, XNClientWindow
					, m_window[0]
					, NULL
					);

			//
			x11SetDisplayWindow(m_display, m_window[0]);

			MainThreadEntry mte;
			mte.m_argc = _argc;
			mte.m_argv = _argv;

			bx::Thread thread;
			thread.init(mte.threadFunc, &mte);

			WindowHandle defaultWindow = { 0 };
			m_eventQueue.postSizeEvent(defaultWindow, 1, 1);

			s_joystick.init();

			while (!m_exit)
			{
				bool joystick = s_joystick.update(m_eventQueue);
				bool xpending = XPending(m_display);

				if (!xpending)
				{
					bx::sleep(joystick ? 8 : 16);
				}
				else
				{
					XEvent event;
					XNextEvent(m_display, &event);

					switch (event.type)
					{
						case Expose:
							break;

						case ClientMessage:
							if ( (Atom)event.xclient.data.l[0] == wmDeleteWindow)
							{
								m_eventQueue.postExitEvent();
							}
							break;

						case ButtonPress:
						case ButtonRelease:
							{
								const XButtonEvent& xbutton = event.xbutton;
								MouseButton::Enum mb = MouseButton::None;
								switch (xbutton.button)
								{
									case Button1: mb = MouseButton::Left;   break;
									case Button2: mb = MouseButton::Middle; break;
									case Button3: mb = MouseButton::Right;  break;
									case Button4: ++m_mz; break;
									case Button5: --m_mz; break;
								}

								WindowHandle handle = findHandle(xbutton.window);
								if (MouseButton::None != mb)
								{
									m_eventQueue.postMouseEvent(handle
										, xbutton.x
										, xbutton.y
										, m_mz
										, mb
										, event.type == ButtonPress
										);
								}
								else
								{
									m_eventQueue.postMouseEvent(handle
											, m_mx
											, m_my
											, m_mz
											);
								}
							}
							break;

						case MotionNotify:
							{
								const XMotionEvent& xmotion = event.xmotion;
								WindowHandle handle = findHandle(xmotion.window);

								m_mx = xmotion.x;
								m_my = xmotion.y;

								m_eventQueue.postMouseEvent(handle
										, m_mx
										, m_my
										, m_mz
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
										WindowHandle handle = findHandle(xkey.window);
										if (KeyPress == event.type)
										{
											Status status = 0;
											uint8_t utf8[4];
											int len = Xutf8LookupString(ic, &xkey, (char*)utf8, sizeof(utf8), &keysym, &status);
											switch (status)
											{
											case XLookupChars:
											case XLookupBoth:
												if (0 != len)
												{
													m_eventQueue.postCharEvent(handle, len, utf8);
												}
												break;

											default:
												break;
											}
										}

										Key::Enum key = fromXk(keysym);
										if (Key::None != key)
										{
											m_eventQueue.postKeyEvent(handle, key, m_modifiers, KeyPress == event.type);
										}
									}
									break;
								}
							}
							break;

						case ConfigureNotify:
							{
								const XConfigureEvent& xev = event.xconfigure;
								WindowHandle handle = findHandle(xev.window);
								if (isValid(handle) )
								{
									m_eventQueue.postSizeEvent(handle, xev.width, xev.height);
								}
							}
							break;
					}
				}
			}

			thread.shutdown();

			s_joystick.shutdown();

			XDestroyIC(ic);
			XCloseIM(im);

			XUnmapWindow(m_display, m_window[0]);
			XDestroyWindow(m_display, m_window[0]);

			return thread.getExitCode();
		}

		void setModifier(Modifier::Enum _modifier, bool _set)
		{
			m_modifiers &= ~_modifier;
			m_modifiers |= _set ? _modifier : 0;
		}

		void createWindow(WindowHandle _handle, Msg* msg)
		{
			Window window = XCreateWindow(m_display
									, m_root
									, msg->m_x
									, msg->m_y
									, msg->m_width
									, msg->m_height
									, 0
									, m_depth
									, InputOutput
									, m_visual
									, CWBorderPixel|CWEventMask|CWBackPixel|CWBitGravity
									, &m_windowAttrs
									);
			m_window[_handle.idx] = window;

			const char* wmDeleteWindowName = "WM_DELETE_WINDOW";
			Atom wmDeleteWindow;
			XInternAtoms(m_display, (char **)&wmDeleteWindowName, 1, False, &wmDeleteWindow);
			XSetWMProtocols(m_display, window, &wmDeleteWindow, 1);

			XMapWindow(m_display, window);
			XStoreName(m_display, window, msg->m_title.c_str() );

			XClassHint* hint = XAllocClassHint();
			hint->res_name  = (char*)msg->m_title.c_str();
			hint->res_class = (char*)s_applicationClass;
			XSetClassHint(m_display, window, hint);
			XFree(hint);

			m_eventQueue.postSizeEvent(_handle, msg->m_width, msg->m_height);

			union cast
			{
				void* p;
				::Window w;
			};

			cast c;
			c.w = window;
			m_eventQueue.postWindowEvent(_handle, c.p);

			delete msg;
		}

		WindowHandle findHandle(Window _window)
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

		uint8_t m_modifiers;
		bool m_exit;

		int32_t m_mx;
		int32_t m_my;
		int32_t m_mz;

		EventQueue m_eventQueue;
		bx::Mutex m_lock;
		bx::HandleAllocT<ENTRY_CONFIG_MAX_WINDOWS> m_windowAlloc;

		int32_t m_depth;
		Visual* m_visual;
		Window  m_root;

		XSetWindowAttributes m_windowAttrs;

		Display* m_display;
		Window m_window[ENTRY_CONFIG_MAX_WINDOWS];
		uint32_t m_flags[ENTRY_CONFIG_MAX_WINDOWS];
	};

	static Context s_ctx;

	int32_t MainThreadEntry::threadFunc(bx::Thread* _thread, void* _userData)
	{
		BX_UNUSED(_thread);

		MainThreadEntry* self = (MainThreadEntry*)_userData;
		int32_t result = main(self->m_argc, self->m_argv);
		s_ctx.m_exit = true;
		return result;
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

		if (isValid(handle) )
		{
			Msg* msg = new Msg;
			msg->m_x      = _x;
			msg->m_y      = _y;
			msg->m_width  = _width;
			msg->m_height = _height;
			msg->m_title  = _title;
			msg->m_flags  = _flags;
			s_ctx.createWindow(handle, msg);
		}

		return handle;
	}

	void destroyWindow(WindowHandle _handle)
	{
		if (isValid(_handle) )
		{
			s_ctx.m_eventQueue.postWindowEvent(_handle, NULL);
			XUnmapWindow(s_ctx.m_display, s_ctx.m_window[_handle.idx]);
			XDestroyWindow(s_ctx.m_display, s_ctx.m_window[_handle.idx]);

			bx::MutexScope scope(s_ctx.m_lock);
			s_ctx.m_windowAlloc.free(_handle.idx);
		}
	}

	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y)
	{
		Display* display = s_ctx.m_display;
		Window   window  = s_ctx.m_window[_handle.idx];
		XMoveWindow(display, window, _x, _y);
	}

	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height)
	{
		Display* display = s_ctx.m_display;
		Window   window  = s_ctx.m_window[_handle.idx];
		XResizeWindow(display, window, int32_t(_width), int32_t(_height) );
	}

	void setWindowTitle(WindowHandle _handle, const char* _title)
	{
		Display* display = s_ctx.m_display;
		Window   window  = s_ctx.m_window[_handle.idx];

		XTextProperty tp;
		Xutf8TextListToTextProperty(display, (char**)&_title, 1, XUTF8StringStyle, &tp);
		XSetWMName(display, window, &tp);
	}

	void setWindowFlags(WindowHandle _handle, uint32_t _flags, bool _enabled)
	{
		BX_UNUSED(_handle, _flags, _enabled);
	}

	void toggleFullscreen(WindowHandle _handle)
	{
		BX_UNUSED(_handle);
	}

	void setMouseLock(WindowHandle _handle, bool _lock)
	{
		BX_UNUSED(_handle, _lock);
	}

} // namespace entry

int main(int _argc, const char* const* _argv)
{
	using namespace entry;
	return s_ctx.run(_argc, _argv);
}

#endif // ENTRY_CONFIG_USE_NATIVE && (BX_PLATFORM_BSD || BX_PLATFORM_LINUX || BX_PLATFORM_RPI)
