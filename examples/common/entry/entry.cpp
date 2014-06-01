/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <bx/string.h>
#include <bx/readerwriter.h>

#include <time.h>

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

	void cmd(const void* _userData)
	{
		cmdExec( (const char*)_userData);
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
			if (setOrToggle(s_reset, "vsync", BGFX_RESET_VSYNC,    1, _argc, _argv)
			||  setOrToggle(s_reset, "msaa",  BGFX_RESET_MSAA_X16, 1, _argc, _argv) )
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
		{ entry::Key::KeyQ,  entry::Modifier::LeftCtrl,  1, cmd, "exit"                              },
		{ entry::Key::F1,    entry::Modifier::None,      1, cmd, "graphics stats"                    },
		{ entry::Key::F1,    entry::Modifier::LeftShift, 1, cmd, "graphics stats 0\ngraphics text 0" },
		{ entry::Key::F3,    entry::Modifier::None,      1, cmd, "graphics wireframe"                },
		{ entry::Key::F7,    entry::Modifier::None,      1, cmd, "graphics vsync"                    },
		{ entry::Key::F8,    entry::Modifier::None,      1, cmd, "graphics msaa"                     },
		{ entry::Key::Print, entry::Modifier::None,      1, cmd, "graphics screenshot"               },

		INPUT_BINDING_END
	};

	int main(int _argc, char** _argv)
	{
		//DBG(BX_COMPILER_NAME " / " BX_CPU_NAME " / " BX_ARCH_NAME " / " BX_PLATFORM_NAME);

#if BX_CONFIG_CRT_FILE_READER_WRITER
		s_fileReader = new bx::CrtFileReader;
		s_fileWriter = new bx::CrtFileWriter;
#endif // BX_CONFIG_CRT_FILE_READER_WRITER

		cmdAdd("mouselock", cmdMouseLock);
		cmdAdd("graphics",  cmdGraphics );
		cmdAdd("exit",      cmdExit     );

		inputAddBindings("bindings", s_bindings);

		int32_t result = ::_main_(_argc, _argv);

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
				case Event::Exit:
					return true;

				case Event::Mouse:
					{
						const MouseEvent* mouse = static_cast<const MouseEvent*>(ev);

						if (mouse->m_move)
						{
							inputSetMousePos(mouse->m_mx, mouse->m_my);
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
						inputSetKeyState(key->m_key, key->m_modifiers, key->m_down);
					}
					break;

				case Event::Size:
					{
						const SizeEvent* size = static_cast<const SizeEvent*>(ev);
						_width = size->m_width;
						_height = size->m_height;
						_reset = !s_reset; // force reset
					}
					break;

				default:
					break;
				}
			}

			inputProcess();

		} while (NULL != ev);

		if (_reset != s_reset)
		{
			_reset = s_reset;
			bgfx::reset(_width, _height, _reset);
			inputSetMouseResolution(_width, _height);
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

} // namespace entry

extern "C" bool entry_process_events(uint32_t* _width, uint32_t* _height, uint32_t* _debug, uint32_t* _reset)
{
	return entry::processEvents(*_width, *_height, *_debug, *_reset, NULL);
}
