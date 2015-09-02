/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <bx/string.h>
#include <bx/readerwriter.h>

#include <time.h>

#if BX_PLATFORM_EMSCRIPTEN
#	include <emscripten.h>
#endif // BX_PLATFORM_EMSCRIPTEN

#include "entry_p.h"
#include "cmd.h"
#include "input.h"

extern "C" int _main_(int _argc, char** _argv);

namespace entry
{
	static uint32_t s_debug = BGFX_DEBUG_NONE;
	static uint32_t s_reset = BGFX_RESET_NONE;
	static bool s_exit = false;
	static bx::FileReaderI* s_fileReader = NULL;
	static bx::FileWriterI* s_fileWriter = NULL;

	extern bx::ReallocatorI* getDefaultAllocator();
	static bx::ReallocatorI* s_allocator = getDefaultAllocator();

#if ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR
	bx::ReallocatorI* getDefaultAllocator()
	{
BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 's_allocator' hides global declaration
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
		static bx::CrtAllocator s_allocator;
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
			return '0' + (_key - Key::Key0);
		}

		const bool isChar = (Key::KeyA <= _key && _key <= Key::KeyZ);
		if (isChar)
		{
			enum { ShiftMask = Modifier::LeftShift|Modifier::RightShift };

			const bool shift = !!(_modifiers&ShiftMask);
			return (shift ? 'A' : 'a') + (_key - Key::KeyA);
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
		if (0 == strcmp(_argv[_first], _name) )
		{
			int arg = _first+1;
			if (_argc > arg)
			{
				_flags &= ~_bit;
				_flags |= bx::toBool(_argv[arg]) ? _bit : 0;
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
		if (_argc > 1)
		{
			inputSetMouseLock(_argc > 1 ? bx::toBool(_argv[1]) : !inputIsMouseLocked() );
			return 0;
		}

		return 1;
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
			   )
			{
				return 0;
			}
			else if (setOrToggle(s_debug, "stats",     BGFX_DEBUG_STATS,     1, _argc, _argv)
				 ||  setOrToggle(s_debug, "ifh",       BGFX_DEBUG_IFH,       1, _argc, _argv)
				 ||  setOrToggle(s_debug, "text",      BGFX_DEBUG_TEXT,      1, _argc, _argv)
				 ||  setOrToggle(s_debug, "wireframe", BGFX_DEBUG_WIREFRAME, 1, _argc, _argv) )
			{
				bgfx::setDebug(s_debug);
				return 0;
			}
			else if (0 == strcmp(_argv[1], "screenshot") )
			{
				if (_argc > 2)
				{
					bgfx::saveScreenShot(_argv[2]);
				}
				else
				{
					time_t tt;
					time(&tt);

					char filePath[256];
					bx::snprintf(filePath, sizeof(filePath), "temp/screenshot-%d", tt);
					bgfx::saveScreenShot(filePath);
				}

				return 0;
			}
			else if (0 == strcmp(_argv[1], "fullscreen") )
			{
				WindowHandle window = { 0 };
				toggleFullscreen(window);
				return 0;
			}
		}

		return 1;
	}

	int cmdExit(CmdContext* /*_context*/, void* /*_userData*/, int /*_argc*/, char const* const* /*_argv*/)
	{
		s_exit = true;
		return 0;
	}

	static const InputBinding s_bindings[] =
	{
		{ entry::Key::KeyQ,         entry::Modifier::LeftCtrl,  1, NULL, "exit"                              },
		{ entry::Key::KeyQ,         entry::Modifier::RightCtrl, 1, NULL, "exit"                              },
		{ entry::Key::KeyF,         entry::Modifier::LeftCtrl,  1, NULL, "graphics fullscreen"               },
		{ entry::Key::KeyF,         entry::Modifier::RightCtrl, 1, NULL, "graphics fullscreen"               },
		{ entry::Key::Return,       entry::Modifier::RightAlt,  1, NULL, "graphics fullscreen"               },
		{ entry::Key::F1,           entry::Modifier::None,      1, NULL, "graphics stats"                    },
		{ entry::Key::GamepadStart, entry::Modifier::None,      1, NULL, "graphics stats"                    },
		{ entry::Key::F1,           entry::Modifier::LeftShift, 1, NULL, "graphics stats 0\ngraphics text 0" },
		{ entry::Key::F3,           entry::Modifier::None,      1, NULL, "graphics wireframe"                },
		{ entry::Key::F4,           entry::Modifier::None,      1, NULL, "graphics hmd"                      },
		{ entry::Key::F4,           entry::Modifier::LeftShift, 1, NULL, "graphics hmdrecenter"              },
		{ entry::Key::F4,           entry::Modifier::LeftCtrl,  1, NULL, "graphics hmddbg"                   },
		{ entry::Key::F7,           entry::Modifier::None,      1, NULL, "graphics vsync"                    },
		{ entry::Key::F8,           entry::Modifier::None,      1, NULL, "graphics msaa"                     },
		{ entry::Key::F9,           entry::Modifier::None,      1, NULL, "graphics flush"                    },
		{ entry::Key::F10,          entry::Modifier::None,      1, NULL, "graphics hidpi"                    },
		{ entry::Key::Print,        entry::Modifier::None,      1, NULL, "graphics screenshot"               },

		INPUT_BINDING_END
	};

#if BX_PLATFORM_EMSCRIPTEN
	static AppI* s_app;
	static void updateApp()
	{
		s_app->update();
	}
#endif // BX_PLATFORM_EMSCRIPTEN

	int runApp(AppI* _app, int _argc, char** _argv)
	{
		_app->init(_argc, _argv);

#if BX_PLATFORM_EMSCRIPTEN
		s_app = _app;
		emscripten_set_main_loop(&updateApp, -1, 1);
#else
		while (_app->update() );
#endif // BX_PLATFORM_EMSCRIPTEN

		return _app->shutdown();
	}

	int main(int _argc, char** _argv)
	{
		//DBG(BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME);

#if BX_CONFIG_CRT_FILE_READER_WRITER
		s_fileReader = new bx::CrtFileReader;
		s_fileWriter = new bx::CrtFileWriter;
#endif // BX_CONFIG_CRT_FILE_READER_WRITER

		cmdInit();
		cmdAdd("mouselock", cmdMouseLock);
		cmdAdd("graphics",  cmdGraphics );
		cmdAdd("exit",      cmdExit     );

		inputInit();
		inputAddBindings("bindings", s_bindings);

		entry::WindowHandle defaultWindow = { 0 };
		entry::setWindowTitle(defaultWindow, bx::baseName(_argv[0]) );

		int32_t result = ::_main_(_argc, _argv);

		inputRemoveBindings("bindings");
		inputShutdown();

		cmdShutdown();

#if BX_CONFIG_CRT_FILE_READER_WRITER
		delete s_fileReader;
		s_fileReader = NULL;

		delete s_fileWriter;
		s_fileWriter = NULL;
#endif // BX_CONFIG_CRT_FILE_READER_WRITER

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
						const GamepadEvent* gev = static_cast<const GamepadEvent*>(ev);
						DBG("gamepad %d, %d", gev->m_gamepad.idx, gev->m_connected);
					}
					break;

				case Event::Mouse:
					{
						const MouseEvent* mouse = static_cast<const MouseEvent*>(ev);
						handle = mouse->m_handle;

						if (mouse->m_move)
						{
							inputSetMousePos(mouse->m_mx, mouse->m_my, mouse->m_mz);
						}
						else
						{
							inputSetMouseButtonState(mouse->m_button, mouse->m_down);
						}

						if (NULL != _mouse
						&&  !mouseLock)
						{
							if (mouse->m_move)
							{
								_mouse->m_mx = mouse->m_mx;
								_mouse->m_my = mouse->m_my;
								_mouse->m_mz = mouse->m_mz;
							}
							else
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
			inputSetMouseResolution(_width, _height);
		}

		_debug = s_debug;

		return s_exit;
	}

	WindowState s_window[ENTRY_CONFIG_MAX_WINDOWS];

	bool processWindowEvents(WindowState& _state, uint32_t& _debug, uint32_t& _reset)
	{
		s_debug = _debug;
		s_reset = _reset;

		WindowHandle handle = { UINT16_MAX };

		bool mouseLock = inputIsMouseLocked();

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

				default:
					break;
				}
			}

			inputProcess();

		} while (NULL != ev);

		if (isValid(handle) )
		{
			const WindowState& win = s_window[handle.idx];
			_state = win;

			if (handle.idx == 0)
			{
				inputSetMouseResolution(win.m_width, win.m_height);
			}
		}

		if (_reset != s_reset)
		{
			_reset = s_reset;
			bgfx::reset(s_window[0].m_width, s_window[0].m_height, _reset);
			inputSetMouseResolution(s_window[0].m_width, s_window[0].m_height);
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

	bx::ReallocatorI* getAllocator()
	{
		return s_allocator;
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
