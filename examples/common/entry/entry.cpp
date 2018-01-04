/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/bx.h>
#include <bx/file.h>
#include <bx/sort.h>
#include <bgfx/bgfx.h>

#include <time.h>

#if BX_PLATFORM_EMSCRIPTEN
#	include <emscripten.h>
#endif // BX_PLATFORM_EMSCRIPTEN

#include "entry_p.h"
#include "cmd.h"
#include "input.h"

extern "C" int32_t _main_(int32_t _argc, char** _argv);

namespace entry
{
	static uint32_t s_debug = BGFX_DEBUG_NONE;
	static uint32_t s_reset = BGFX_RESET_NONE;
	static uint32_t s_width = ENTRY_DEFAULT_WIDTH;
	static uint32_t s_height = ENTRY_DEFAULT_HEIGHT;
	static bool s_exit = false;

	static bx::FileReaderI* s_fileReader = NULL;
	static bx::FileWriterI* s_fileWriter = NULL;

	extern bx::AllocatorI* getDefaultAllocator();
	bx::AllocatorI* g_allocator = getDefaultAllocator();

	typedef bx::StringT<&g_allocator> String;

	static String s_currentDir;

	class FileReader : public bx::FileReader
	{
		typedef bx::FileReader super;

	public:
		virtual bool open(const bx::FilePath& _filePath, bx::Error* _err) override
		{
			String filePath(s_currentDir);
			filePath.append(_filePath.get() );
			return super::open(filePath.getPtr(), _err);
		}
	};

	class FileWriter : public bx::FileWriter
	{
		typedef bx::FileWriter super;

	public:
		virtual bool open(const bx::FilePath& _filePath, bool _append, bx::Error* _err) override
		{
			String filePath(s_currentDir);
			filePath.append(_filePath.get() );
			return super::open(filePath.getPtr(), _append, _err);
		}
	};

	void setCurrentDir(const char* _dir)
	{
		s_currentDir.set(_dir);
	}

#if ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR
	bx::AllocatorI* getDefaultAllocator()
	{
BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 's_allocator' hides global declaration
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
		static bx::DefaultAllocator s_allocator;
		return &s_allocator;
BX_PRAGMA_DIAGNOSTIC_POP();
	}
#endif // ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR

	static const char* s_keyName[] =
	{
		"None",
		"Esc",
		"Return",
		"Tab",
		"Space",
		"Backspace",
		"Up",
		"Down",
		"Left",
		"Right",
		"Insert",
		"Delete",
		"Home",
		"End",
		"PageUp",
		"PageDown",
		"Print",
		"Plus",
		"Minus",
		"LeftBracket",
		"RightBracket",
		"Semicolon",
		"Quote",
		"Comma",
		"Period",
		"Slash",
		"Backslash",
		"Tilde",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"NumPad0",
		"NumPad1",
		"NumPad2",
		"NumPad3",
		"NumPad4",
		"NumPad5",
		"NumPad6",
		"NumPad7",
		"NumPad8",
		"NumPad9",
		"Key0",
		"Key1",
		"Key2",
		"Key3",
		"Key4",
		"Key5",
		"Key6",
		"Key7",
		"Key8",
		"Key9",
		"KeyA",
		"KeyB",
		"KeyC",
		"KeyD",
		"KeyE",
		"KeyF",
		"KeyG",
		"KeyH",
		"KeyI",
		"KeyJ",
		"KeyK",
		"KeyL",
		"KeyM",
		"KeyN",
		"KeyO",
		"KeyP",
		"KeyQ",
		"KeyR",
		"KeyS",
		"KeyT",
		"KeyU",
		"KeyV",
		"KeyW",
		"KeyX",
		"KeyY",
		"KeyZ",
		"GamepadA",
		"GamepadB",
		"GamepadX",
		"GamepadY",
		"GamepadThumbL",
		"GamepadThumbR",
		"GamepadShoulderL",
		"GamepadShoulderR",
		"GamepadUp",
		"GamepadDown",
		"GamepadLeft",
		"GamepadRight",
		"GamepadBack",
		"GamepadStart",
		"GamepadGuide",
	};
	BX_STATIC_ASSERT(Key::Count == BX_COUNTOF(s_keyName) );

	const char* getName(Key::Enum _key)
	{
		BX_CHECK(_key < Key::Count, "Invalid key %d.", _key);
		return s_keyName[_key];
	}

	char keyToAscii(Key::Enum _key, uint8_t _modifiers)
	{
		const bool isAscii = (Key::Key0 <= _key && _key <= Key::KeyZ)
						  || (Key::Esc  <= _key && _key <= Key::Minus);
		if (!isAscii)
		{
			return '\0';
		}

		const bool isNumber = (Key::Key0 <= _key && _key <= Key::Key9);
		if (isNumber)
		{
			return '0' + char(_key - Key::Key0);
		}

		const bool isChar = (Key::KeyA <= _key && _key <= Key::KeyZ);
		if (isChar)
		{
			enum { ShiftMask = Modifier::LeftShift|Modifier::RightShift };

			const bool shift = !!(_modifiers&ShiftMask);
			return (shift ? 'A' : 'a') + char(_key - Key::KeyA);
		}

		switch (_key)
		{
		case Key::Esc:       return 0x1b;
		case Key::Return:    return '\n';
		case Key::Tab:       return '\t';
		case Key::Space:     return ' ';
		case Key::Backspace: return 0x08;
		case Key::Plus:      return '+';
		case Key::Minus:     return '-';
		default:             break;
		}

		return '\0';
	}

	bool setOrToggle(uint32_t& _flags, const char* _name, uint32_t _bit, int _first, int _argc, char const* const* _argv)
	{
		if (0 == bx::strCmp(_argv[_first], _name) )
		{
			int arg = _first+1;
			if (_argc > arg)
			{
				_flags &= ~_bit;

				bool set = false;
				bx::fromString(&set, _argv[arg]);

				_flags |= set ? _bit : 0;
			}
			else
			{
				_flags ^= _bit;
			}

			return true;
		}

		return false;
	}

	int cmdMouseLock(CmdContext* /*_context*/, void* /*_userData*/, int _argc, char const* const* _argv)
	{
		if (1 < _argc)
		{
			bool set = false;
			if (2 < _argc)
			{
				bx::fromString(&set, _argv[1]);
				inputSetMouseLock(set);
			}
			else
			{
				inputSetMouseLock(!inputIsMouseLocked() );
			}

			return bx::kExitSuccess;
		}

		return bx::kExitFailure;
	}

	int cmdGraphics(CmdContext* /*_context*/, void* /*_userData*/, int _argc, char const* const* _argv)
	{
		if (_argc > 1)
		{
			if (setOrToggle(s_reset, "vsync",       BGFX_RESET_VSYNC,              1, _argc, _argv)
			||  setOrToggle(s_reset, "maxaniso",    BGFX_RESET_MAXANISOTROPY,      1, _argc, _argv)
			||  setOrToggle(s_reset, "hmd",         BGFX_RESET_HMD,                1, _argc, _argv)
			||  setOrToggle(s_reset, "hmddbg",      BGFX_RESET_HMD_DEBUG,          1, _argc, _argv)
			||  setOrToggle(s_reset, "hmdrecenter", BGFX_RESET_HMD_RECENTER,       1, _argc, _argv)
			||  setOrToggle(s_reset, "msaa",        BGFX_RESET_MSAA_X16,           1, _argc, _argv)
			||  setOrToggle(s_reset, "flush",       BGFX_RESET_FLUSH_AFTER_RENDER, 1, _argc, _argv)
			||  setOrToggle(s_reset, "flip",        BGFX_RESET_FLIP_AFTER_RENDER,  1, _argc, _argv)
			||  setOrToggle(s_reset, "hidpi",       BGFX_RESET_HIDPI,              1, _argc, _argv)
			||  setOrToggle(s_reset, "depthclamp",  BGFX_RESET_DEPTH_CLAMP,        1, _argc, _argv)
			   )
			{
				return bx::kExitSuccess;
			}
			else if (setOrToggle(s_debug, "stats",     BGFX_DEBUG_STATS,     1, _argc, _argv)
				 ||  setOrToggle(s_debug, "ifh",       BGFX_DEBUG_IFH,       1, _argc, _argv)
				 ||  setOrToggle(s_debug, "text",      BGFX_DEBUG_TEXT,      1, _argc, _argv)
				 ||  setOrToggle(s_debug, "wireframe", BGFX_DEBUG_WIREFRAME, 1, _argc, _argv)
				 ||  setOrToggle(s_debug, "profiler",  BGFX_DEBUG_PROFILER,  1, _argc, _argv)
				    )
			{
				bgfx::setDebug(s_debug);
				return bx::kExitSuccess;
			}
			else if (0 == bx::strCmp(_argv[1], "screenshot") )
			{
				bgfx::FrameBufferHandle fbh = BGFX_INVALID_HANDLE;

				if (_argc > 2)
				{
					bgfx::requestScreenShot(fbh, _argv[2]);
				}
				else
				{
					time_t tt;
					time(&tt);

					char filePath[256];
					bx::snprintf(filePath, sizeof(filePath), "temp/screenshot-%d", tt);
					bgfx::requestScreenShot(fbh, filePath);
				}

				return bx::kExitSuccess;
			}
			else if (0 == bx::strCmp(_argv[1], "fullscreen") )
			{
				WindowHandle window = { 0 };
				toggleFullscreen(window);
				return bx::kExitSuccess;
			}
		}

		return bx::kExitFailure;
	}

	int cmdExit(CmdContext* /*_context*/, void* /*_userData*/, int /*_argc*/, char const* const* /*_argv*/)
	{
		s_exit = true;
		return bx::kExitSuccess;
	}

	static const InputBinding s_bindings[] =
	{
		{ entry::Key::KeyQ,         entry::Modifier::LeftCtrl,  1, NULL, "exit"                              },
		{ entry::Key::KeyQ,         entry::Modifier::RightCtrl, 1, NULL, "exit"                              },
		{ entry::Key::KeyF,         entry::Modifier::LeftCtrl,  1, NULL, "graphics fullscreen"               },
		{ entry::Key::KeyF,         entry::Modifier::RightCtrl, 1, NULL, "graphics fullscreen"               },
		{ entry::Key::Return,       entry::Modifier::RightAlt,  1, NULL, "graphics fullscreen"               },
		{ entry::Key::F1,           entry::Modifier::None,      1, NULL, "graphics stats"                    },
		{ entry::Key::F1,           entry::Modifier::LeftCtrl,  1, NULL, "graphics ifh"                      },
		{ entry::Key::GamepadStart, entry::Modifier::None,      1, NULL, "graphics stats"                    },
		{ entry::Key::F1,           entry::Modifier::LeftShift, 1, NULL, "graphics stats 0\ngraphics text 0" },
		{ entry::Key::F3,           entry::Modifier::None,      1, NULL, "graphics wireframe"                },
		{ entry::Key::F4,           entry::Modifier::None,      1, NULL, "graphics hmd"                      },
		{ entry::Key::F4,           entry::Modifier::LeftShift, 1, NULL, "graphics hmdrecenter"              },
		{ entry::Key::F4,           entry::Modifier::LeftCtrl,  1, NULL, "graphics hmddbg"                   },
		{ entry::Key::F6,           entry::Modifier::None,      1, NULL, "graphics profiler"                 },
		{ entry::Key::F7,           entry::Modifier::None,      1, NULL, "graphics vsync"                    },
		{ entry::Key::F8,           entry::Modifier::None,      1, NULL, "graphics msaa"                     },
		{ entry::Key::F9,           entry::Modifier::None,      1, NULL, "graphics flush"                    },
		{ entry::Key::F10,          entry::Modifier::None,      1, NULL, "graphics hidpi"                    },
		{ entry::Key::Print,        entry::Modifier::None,      1, NULL, "graphics screenshot"               },
		{ entry::Key::KeyP,         entry::Modifier::LeftCtrl,  1, NULL, "graphics screenshot"               },

		INPUT_BINDING_END
	};

#if BX_PLATFORM_EMSCRIPTEN
	static AppI* s_app;
	static void updateApp()
	{
		s_app->update();
	}
#endif // BX_PLATFORM_EMSCRIPTEN

	static AppI*    s_currentApp = NULL;
	static AppI*    s_apps       = NULL;
	static uint32_t s_numApps    = 0;

	static char s_restartArgs[1024] = { '\0' };

	static AppI* getCurrentApp(AppI* _set = NULL)
	{
		if (NULL != _set)
		{
			s_currentApp = _set;
		}
		else if (NULL == s_currentApp)
		{
			s_currentApp = getFirstApp();
		}

		return s_currentApp;
	}

	static AppI* getNextWrap(AppI* _app)
	{
		AppI* next = _app->getNext();
		if (NULL != next)
		{
			return next;
		}

		return getFirstApp();
	}

	int cmdApp(CmdContext* /*_context*/, void* /*_userData*/, int _argc, char const* const* _argv)
	{
		if (0 == bx::strCmp(_argv[1], "restart") )
		{
			if (2 == _argc)
			{
				bx::strCopy(s_restartArgs, BX_COUNTOF(s_restartArgs), getCurrentApp()->getName() );
				return bx::kExitSuccess;
			}

			if (0 == bx::strCmp(_argv[2], "next") )
			{
				AppI* next = getNextWrap(getCurrentApp() );
				bx::strCopy(s_restartArgs, BX_COUNTOF(s_restartArgs), next->getName() );
				return bx::kExitSuccess;
			}
			else if (0 == bx::strCmp(_argv[2], "prev") )
			{
				AppI* prev = getCurrentApp();
				for (AppI* app = getNextWrap(prev); app != getCurrentApp(); app = getNextWrap(app) )
				{
					prev = app;
				}

				bx::strCopy(s_restartArgs, BX_COUNTOF(s_restartArgs), prev->getName() );
				return bx::kExitSuccess;
			}

			for (AppI* app = getFirstApp(); NULL != app; app = app->getNext() )
			{
				if (0 == bx::strCmp(_argv[2], app->getName() ) )
				{
					bx::strCopy(s_restartArgs, BX_COUNTOF(s_restartArgs), app->getName() );
					return bx::kExitSuccess;
				}
			}
		}

		return bx::kExitFailure;
	}

	AppI::AppI(const char* _name, const char* _description)
	{
		m_name        = _name;
		m_description = _description;
		m_next        = s_apps;

		s_apps = this;
		s_numApps++;
	}

	AppI::~AppI()
	{
		for (AppI* prev = NULL, *app = s_apps, *next = app->getNext()
			; NULL != app
			; prev = app, app = next, next = app->getNext() )
		{
			if (app == this)
			{
				if (NULL != prev)
				{
					prev->m_next = next;
				}
				else
				{
					s_apps = next;
				}

				--s_numApps;

				break;
			}
		}
	}

	const char* AppI::getName() const
	{
		return m_name;
	}

	const char* AppI::getDescription() const
	{
		return m_description;
	}

	AppI* AppI::getNext()
	{
		return m_next;
	}

	AppI* getFirstApp()
	{
		return s_apps;
	}

	uint32_t getNumApps()
	{
		return s_numApps;
	}

	int runApp(AppI* _app, int _argc, const char* const* _argv)
	{
		_app->init(_argc, _argv, s_width, s_height);
		bgfx::frame();

		WindowHandle defaultWindow = { 0 };
		setWindowSize(defaultWindow, s_width, s_height);

#if BX_PLATFORM_EMSCRIPTEN
		s_app = _app;
		emscripten_set_main_loop(&updateApp, -1, 1);
#else
		while (_app->update() )
		{
			if (0 != bx::strLen(s_restartArgs) )
			{
				break;
			}
		}
#endif // BX_PLATFORM_EMSCRIPTEN

		return _app->shutdown();
	}

	static int32_t sortApp(const void* _lhs, const void* _rhs)
	{
		const AppI* lhs = *(const AppI**)_lhs;
		const AppI* rhs = *(const AppI**)_rhs;

		return bx::strCmpI(lhs->getName(), rhs->getName() );
	}

	static void sortApps()
	{
		if (2 > s_numApps)
		{
			return;
		}

		AppI** apps = (AppI**)BX_ALLOC(g_allocator, s_numApps*sizeof(AppI*) );

		uint32_t ii = 0;
		for (AppI* app = getFirstApp(); NULL != app; app = app->getNext() )
		{
			apps[ii++] = app;
		}
		bx::quickSort(apps, s_numApps, sizeof(AppI*), sortApp);

		s_apps = apps[0];
		for (ii = 1; ii < s_numApps; ++ii)
		{
			AppI* app = apps[ii-1];
			app->m_next = apps[ii];
		}
		apps[s_numApps-1]->m_next = NULL;

		BX_FREE(g_allocator, apps);
	}

	int main(int _argc, const char* const* _argv)
	{
		//DBG(BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME);

		s_fileReader = BX_NEW(g_allocator, FileReader);
		s_fileWriter = BX_NEW(g_allocator, FileWriter);

		cmdInit();
		cmdAdd("mouselock", cmdMouseLock);
		cmdAdd("graphics",  cmdGraphics );
		cmdAdd("exit",      cmdExit     );
		cmdAdd("app",       cmdApp      );

		inputInit();
		inputAddBindings("bindings", s_bindings);

		entry::WindowHandle defaultWindow = { 0 };

		bx::FilePath fp(_argv[0]);
		char title[bx::kMaxFilePath];
		bx::strCopy(title, BX_COUNTOF(title), fp.getBaseName() );

		entry::setWindowTitle(defaultWindow, title);
		setWindowSize(defaultWindow, ENTRY_DEFAULT_WIDTH, ENTRY_DEFAULT_HEIGHT);

		sortApps();

		const char* find = "";
		if (1 < _argc)
		{
			find = _argv[_argc-1];
		}

restart:
		AppI* selected = NULL;

		for (AppI* app = getFirstApp(); NULL != app; app = app->getNext() )
		{
			if (NULL == selected
			&&  bx::strFindI(app->getName(), find) )
			{
				selected = app;
			}
#if 0
			DBG("%c %s, %s"
				, app == selected ? '>' : ' '
				, app->getName()
				, app->getDescription()
				);
#endif // 0
		}

		int32_t result = bx::kExitSuccess;
		s_restartArgs[0] = '\0';
		if (0 == s_numApps)
		{
			result = ::_main_(_argc, (char**)_argv);
		}
		else
		{
			result = runApp(getCurrentApp(selected), _argc, _argv);
		}

		if (0 != bx::strLen(s_restartArgs) )
		{
			find = s_restartArgs;
			goto restart;
		}

		setCurrentDir("");

		inputRemoveBindings("bindings");
		inputShutdown();

		cmdShutdown();

		BX_DELETE(g_allocator, s_fileReader);
		s_fileReader = NULL;

		BX_DELETE(g_allocator, s_fileWriter);
		s_fileWriter = NULL;

		return result;
	}

	bool processEvents(uint32_t& _width, uint32_t& _height, uint32_t& _debug, uint32_t& _reset, MouseState* _mouse)
	{
		s_debug = _debug;
		s_reset = _reset;

		WindowHandle handle = { UINT16_MAX };

		bool mouseLock = inputIsMouseLocked();

		const Event* ev;
		do
		{
			struct SE { const Event* m_ev; SE() : m_ev(poll() ) {} ~SE() { if (NULL != m_ev) { release(m_ev); } } } scopeEvent;
			ev = scopeEvent.m_ev;

			if (NULL != ev)
			{
				switch (ev->m_type)
				{
				case Event::Axis:
					{
						const AxisEvent* axis = static_cast<const AxisEvent*>(ev);
						inputSetGamepadAxis(axis->m_gamepad, axis->m_axis, axis->m_value);
					}
					break;

				case Event::Char:
					{
						const CharEvent* chev = static_cast<const CharEvent*>(ev);
						inputChar(chev->m_len, chev->m_char);
					}
					break;

				case Event::Exit:
					return true;

				case Event::Gamepad:
					{
//						const GamepadEvent* gev = static_cast<const GamepadEvent*>(ev);
//						DBG("gamepad %d, %d", gev->m_gamepad.idx, gev->m_connected);
					}
					break;

				case Event::Mouse:
					{
						const MouseEvent* mouse = static_cast<const MouseEvent*>(ev);
						handle = mouse->m_handle;

						inputSetMousePos(mouse->m_mx, mouse->m_my, mouse->m_mz);
						if (!mouse->m_move)
						{
							inputSetMouseButtonState(mouse->m_button, mouse->m_down);
						}

						if (NULL != _mouse
						&&  !mouseLock)
						{
							_mouse->m_mx = mouse->m_mx;
							_mouse->m_my = mouse->m_my;
							_mouse->m_mz = mouse->m_mz;
							if (!mouse->m_move)
							{
								_mouse->m_buttons[mouse->m_button] = mouse->m_down;
							}
						}
					}
					break;

				case Event::Key:
					{
						const KeyEvent* key = static_cast<const KeyEvent*>(ev);
						handle = key->m_handle;

						inputSetKeyState(key->m_key, key->m_modifiers, key->m_down);
					}
					break;

				case Event::Size:
					{
						const SizeEvent* size = static_cast<const SizeEvent*>(ev);
						handle  = size->m_handle;
						_width  = size->m_width;
						_height = size->m_height;
						_reset  = !s_reset; // force reset
					}
					break;

				case Event::Window:
					break;

				case Event::Suspend:
					break;

				case Event::DropFile:
					{
						const DropFileEvent* drop = static_cast<const DropFileEvent*>(ev);
						DBG("%s", drop->m_filePath.get() );
					}
					break;

				default:
					break;
				}
			}

			inputProcess();

		} while (NULL != ev);

		if (handle.idx == 0
		&&  _reset != s_reset)
		{
			_reset = s_reset;
			bgfx::reset(_width, _height, _reset);
			inputSetMouseResolution(uint16_t(_width), uint16_t(_height) );
		}

		_debug = s_debug;

		s_width = _width;
		s_height = _height;

		return s_exit;
	}

	WindowState s_window[ENTRY_CONFIG_MAX_WINDOWS];

	bool processWindowEvents(WindowState& _state, uint32_t& _debug, uint32_t& _reset)
	{
		s_debug = _debug;
		s_reset = _reset;

		WindowHandle handle = { UINT16_MAX };

		bool mouseLock = inputIsMouseLocked();
		bool clearDropFile = true;

		const Event* ev;
		do
		{
			struct SE
			{
				SE(WindowHandle _handle)
					: m_ev(poll(_handle) )
				{
				}

				~SE()
				{
					if (NULL != m_ev)
					{
						release(m_ev);
					}
				}

				const Event* m_ev;

			} scopeEvent(handle);
			ev = scopeEvent.m_ev;

			if (NULL != ev)
			{
				handle = ev->m_handle;
				WindowState& win = s_window[handle.idx];

				switch (ev->m_type)
				{
				case Event::Axis:
					{
						const AxisEvent* axis = static_cast<const AxisEvent*>(ev);
						inputSetGamepadAxis(axis->m_gamepad, axis->m_axis, axis->m_value);
					}
					break;

				case Event::Char:
					{
						const CharEvent* chev = static_cast<const CharEvent*>(ev);
						win.m_handle = chev->m_handle;
						inputChar(chev->m_len, chev->m_char);
					}
					break;

				case Event::Exit:
					return true;

				case Event::Gamepad:
					{
						const GamepadEvent* gev = static_cast<const GamepadEvent*>(ev);
						DBG("gamepad %d, %d", gev->m_gamepad.idx, gev->m_connected);
					}
					break;

				case Event::Mouse:
					{
						const MouseEvent* mouse = static_cast<const MouseEvent*>(ev);
						win.m_handle = mouse->m_handle;

						if (mouse->m_move)
						{
							inputSetMousePos(mouse->m_mx, mouse->m_my, mouse->m_mz);
						}
						else
						{
							inputSetMouseButtonState(mouse->m_button, mouse->m_down);
						}

						if (!mouseLock)
						{
							if (mouse->m_move)
							{
								win.m_mouse.m_mx = mouse->m_mx;
								win.m_mouse.m_my = mouse->m_my;
								win.m_mouse.m_mz = mouse->m_mz;
							}
							else
							{
								win.m_mouse.m_buttons[mouse->m_button] = mouse->m_down;
							}
						}
					}
					break;

				case Event::Key:
					{
						const KeyEvent* key = static_cast<const KeyEvent*>(ev);
						win.m_handle = key->m_handle;

						inputSetKeyState(key->m_key, key->m_modifiers, key->m_down);
					}
					break;

				case Event::Size:
					{
						const SizeEvent* size = static_cast<const SizeEvent*>(ev);
						win.m_handle = size->m_handle;
						win.m_width  = size->m_width;
						win.m_height = size->m_height;
						_reset  = win.m_handle.idx == 0
								? !s_reset
								: _reset
								; // force reset
					}
					break;

				case Event::Window:
					{
						const WindowEvent* window = static_cast<const WindowEvent*>(ev);
						win.m_handle = window->m_handle;
						win.m_nwh    = window->m_nwh;
						ev = NULL;
					}
					break;

				case Event::Suspend:
					break;

				case Event::DropFile:
					{
						const DropFileEvent* drop = static_cast<const DropFileEvent*>(ev);
						win.m_dropFile = drop->m_filePath;
						clearDropFile = false;
					}
					break;

				default:
					break;
				}
			}

			inputProcess();

		} while (NULL != ev);

		if (isValid(handle) )
		{
			WindowState& win = s_window[handle.idx];
			if (clearDropFile)
			{
				win.m_dropFile.clear();
			}

			_state = win;

			if (handle.idx == 0)
			{
				inputSetMouseResolution(uint16_t(win.m_width), uint16_t(win.m_height) );
			}
		}

		if (_reset != s_reset)
		{
			_reset = s_reset;
			bgfx::reset(s_window[0].m_width, s_window[0].m_height, _reset);
			inputSetMouseResolution(uint16_t(s_window[0].m_width), uint16_t(s_window[0].m_height) );
		}

		_debug = s_debug;

		return s_exit;
	}

	bx::FileReaderI* getFileReader()
	{
		return s_fileReader;
	}

	bx::FileWriterI* getFileWriter()
	{
		return s_fileWriter;
	}

	bx::AllocatorI* getAllocator()
	{
		if (NULL == g_allocator)
		{
			g_allocator = getDefaultAllocator();
		}

		return g_allocator;
	}

	void* TinyStlAllocator::static_allocate(size_t _bytes)
	{
		return BX_ALLOC(getAllocator(), _bytes);
	}

	void TinyStlAllocator::static_deallocate(void* _ptr, size_t /*_bytes*/)
	{
		if (NULL != _ptr)
		{
			BX_FREE(getAllocator(), _ptr);
		}
	}

} // namespace entry

extern "C" bool entry_process_events(uint32_t* _width, uint32_t* _height, uint32_t* _debug, uint32_t* _reset)
{
	return entry::processEvents(*_width, *_height, *_debug, *_reset, NULL);
}
