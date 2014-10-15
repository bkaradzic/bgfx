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

#define ENTRY_WINDOW_FLAG_NONE         UINT32_C(0x00000000)
#define ENTRY_WINDOW_FLAG_ASPECT_RATIO UINT32_C(0x00000001)
#define ENTRY_WINDOW_FLAG_FRAME        UINT32_C(0x00000002)

namespace entry
{
	struct WindowHandle { uint16_t idx; static const uint16_t invalidHandle; };
	inline bool isValid(WindowHandle _handle) { return WindowHandle::invalidHandle != _handle.idx; }

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

	char keyToAscii(entry::Key::Enum _key, bool _shiftModifier);
	bool processEvents(uint32_t& _width, uint32_t& _height, uint32_t& _debug, uint32_t& _reset, MouseState* _mouse = NULL);

	bx::FileReaderI* getFileReader();
	bx::FileWriterI* getFileWriter();

	WindowHandle createWindow(int32_t _x, int32_t _y, uint32_t _width, uint32_t _height, uint32_t _flags = ENTRY_WINDOW_FLAG_NONE, const char* _title = "");
	void destroyWindow(WindowHandle _handle);
	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y);
	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height);
	void setWindowTitle(WindowHandle _handle, const char* _title);
	void toggleWindowFrame(WindowHandle _handle);
	void setMouseLock(WindowHandle _handle, bool _lock);

	struct WindowState
	{
		WindowState()
			: m_nwh(NULL)
		{
			m_handle.idx = UINT16_MAX;
		}

		WindowHandle m_handle;
		uint32_t     m_width;
		uint32_t     m_height;
		MouseState   m_mouse;
		void*        m_nwh;
	};

	bool processWindowEvents(WindowState& _state, uint32_t& _debug, uint32_t& _reset);

} // namespace entry

#endif // ENTRY_H_HEADER_GUARD
