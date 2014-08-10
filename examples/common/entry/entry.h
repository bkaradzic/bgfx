/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef ENTRY_H_HEADER_GUARD
#define ENTRY_H_HEADER_GUARD

#include "dbg.h"

#include <bx/bx.h>

namespace bx { struct FileReaderI; struct FileWriterI; }

extern "C" int _main_(int _argc, char** _argv);

namespace entry
{
	struct MouseButton
	{
		enum Enum
		{
			None,
			Left,
			Middle,
			Right,

			Count
		};
	};

	struct Modifier
	{
		enum Enum
		{
			None       = 0,
			LeftAlt    = 0x01,
			RightAlt   = 0x02,
			LeftCtrl   = 0x04,
			RightCtrl  = 0x08,
			LeftShift  = 0x10,
			RightShift = 0x20,
			LeftMeta   = 0x40,
			RightMeta  = 0x80,
		};
	};

	struct Key
	{
		enum Enum
		{
			None = 0,
			Esc,
			Return,
			Tab,
			Space,
			Backspace,
			Up,
			Down,
			Left,
			Right,
			PageUp,
			PageDown,
			Home,
			End,
			Print,
			Plus,
			Minus,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			NumPad0,
			NumPad1,
			NumPad2,
			NumPad3,
			NumPad4,
			NumPad5,
			NumPad6,
			NumPad7,
			NumPad8,
			NumPad9,
			Key0,
			Key1,
			Key2,
			Key3,
			Key4,
			Key5,
			Key6,
			Key7,
			Key8,
			Key9,
			KeyA,
			KeyB,
			KeyC,
			KeyD,
			KeyE,
			KeyF,
			KeyG,
			KeyH,
			KeyI,
			KeyJ,
			KeyK,
			KeyL,
			KeyM,
			KeyN,
			KeyO,
			KeyP,
			KeyQ,
			KeyR,
			KeyS,
			KeyT,
			KeyU,
			KeyV,
			KeyW,
			KeyX,
			KeyY,
			KeyZ,

			Count,
		};
	};

	struct MouseState
	{
		MouseState()
			: m_mx(0)
			, m_my(0)
			, m_mz(0)
		{
			for (uint32_t ii = 0; ii < entry::MouseButton::Count; ++ii)
			{
				m_buttons[ii] = entry::MouseButton::None;
			}
		}

		int32_t m_mx;
		int32_t m_my;
		int32_t m_mz;
		uint8_t m_buttons[entry::MouseButton::Count];
	};

	struct KeyState
	{
		uint8_t m_modifiers;
		bool m_keysDown[entry::Key::Count];
	};

	char keyToAscii(entry::Key::Enum _key, bool _shiftModifier);
	bool processEvents(uint32_t& _width, uint32_t& _height, uint32_t& _debug, uint32_t& _reset, MouseState* _mouse = NULL, KeyState* _keyboard = NULL);

	bx::FileReaderI* getFileReader();
	bx::FileWriterI* getFileWriter();

	void setWindowSize(uint32_t _width, uint32_t _height);
	void setWindowTitle(const char* _title);
	void toggleWindowFrame();
	void setMouseLock(bool _lock);

} // namespace entry

#endif // ENTRY_H_HEADER_GUARD
