/*
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef ENTRY_H_HEADER_GUARD
#define ENTRY_H_HEADER_GUARD

#include "dbg.h"
#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <bx/filepath.h>
#include <bx/string.h>

namespace bx { struct FileReaderI; struct FileWriterI; struct AllocatorI; }

extern "C" int _main_(int _argc, char** _argv);

#define ENTRY_WINDOW_FLAG_NONE         UINT32_C(0x00000000)
#define ENTRY_WINDOW_FLAG_ASPECT_RATIO UINT32_C(0x00000001)
#define ENTRY_WINDOW_FLAG_FRAME        UINT32_C(0x00000002)

#ifndef ENTRY_CONFIG_IMPLEMENT_MAIN
#	define ENTRY_CONFIG_IMPLEMENT_MAIN 0
#endif // ENTRY_CONFIG_IMPLEMENT_MAIN

#if ENTRY_CONFIG_IMPLEMENT_MAIN
#define ENTRY_IMPLEMENT_MAIN(_app, ...)                 \
	int _main_(int _argc, char** _argv)                 \
	{                                                   \
			_app app(__VA_ARGS__);                      \
			return entry::runApp(&app, _argc, _argv);   \
	}
#else
#define ENTRY_IMPLEMENT_MAIN(_app, ...) \
	_app s_ ## _app ## App(__VA_ARGS__)
#endif // ENTRY_CONFIG_IMPLEMENT_MAIN

///
#define ENTRY_HANDLE(_name)                                                \
	struct _name { uint16_t idx; };                                        \
	inline bool isValid(_name _handle) { return UINT16_MAX != _handle.idx; }

namespace entry
{
	ENTRY_HANDLE(WindowHandle);
	ENTRY_HANDLE(GamepadHandle);

	///
	constexpr WindowHandle kDefaultWindowHandle = { 0 };

	///
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

	///
	struct GamepadAxis
	{
		enum Enum
		{
			LeftX,
			LeftY,
			LeftZ,
			RightX,
			RightY,
			RightZ,

			Count
		};
	};

	///
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

	///
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
			Insert,
			Delete,
			Home,
			End,
			PageUp,
			PageDown,
			Print,
			Plus,
			Minus,
			LeftBracket,
			RightBracket,
			Semicolon,
			Quote,
			Comma,
			Period,
			Slash,
			Backslash,
			Tilde,
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

			GamepadA,
			GamepadB,
			GamepadX,
			GamepadY,
			GamepadThumbL,
			GamepadThumbR,
			GamepadShoulderL,
			GamepadShoulderR,
			GamepadUp,
			GamepadDown,
			GamepadLeft,
			GamepadRight,
			GamepadBack,
			GamepadStart,
			GamepadGuide,

			Count
		};
	};

	///
	struct Suspend
	{
		enum Enum
		{
			WillSuspend,
			DidSuspend,
			WillResume,
			DidResume,

			Count
		};
	};

	///
	const char* getName(Key::Enum _key);

	///
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

	///
	struct GamepadState
	{
		GamepadState()
		{
			bx::memSet(m_axis, 0, sizeof(m_axis) );
		}

		int32_t m_axis[entry::GamepadAxis::Count];
	};

	///
	bool processEvents(uint32_t& _width, uint32_t& _height, uint32_t& _debug, uint32_t& _reset, MouseState* _mouse = NULL);

	///
	bx::FileReaderI* getFileReader();

	///
	bx::FileWriterI* getFileWriter();

	///
	bx::AllocatorI*  getAllocator();

	///
	WindowHandle createWindow(int32_t _x, int32_t _y, uint32_t _width, uint32_t _height, uint32_t _flags = ENTRY_WINDOW_FLAG_NONE, const char* _title = "");

	///
	void destroyWindow(WindowHandle _handle);

	///
	void setWindowPos(WindowHandle _handle, int32_t _x, int32_t _y);

	///
	void setWindowSize(WindowHandle _handle, uint32_t _width, uint32_t _height);

	///
	void setWindowTitle(WindowHandle _handle, const char* _title);

	///
	void setWindowFlags(WindowHandle _handle, uint32_t _flags, bool _enabled);

	///
	void toggleFullscreen(WindowHandle _handle);

	///
	void setMouseLock(WindowHandle _handle, bool _lock);

	///
	void* getNativeWindowHandle(WindowHandle _handle);

	///
	void* getNativeDisplayHandle();

	///
	bgfx::NativeWindowHandleType::Enum getNativeWindowHandleType();

	///
	void setCurrentDir(const char* _dir);

	///
	struct WindowState
	{
		WindowState()
			: m_width(0)
			, m_height(0)
			, m_nwh(NULL)
		{
			m_handle.idx = UINT16_MAX;
		}

		WindowHandle m_handle;
		uint32_t     m_width;
		uint32_t     m_height;
		MouseState   m_mouse;
		void*        m_nwh;
		bx::FilePath m_dropFile;
	};

	///
	bool processWindowEvents(WindowState& _state, uint32_t& _debug, uint32_t& _reset);

	///
	class BX_NO_VTABLE AppI
	{
	public:
		///
		AppI(const char* _name, const char* _description, const char* _url = "https://bkaradzic.github.io/bgfx/index.html");

		///
		virtual ~AppI() = 0;

		///
		virtual void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) = 0;

		///
		virtual int  shutdown() = 0;

		///
		virtual bool update() = 0;

		///
		const char* getName() const;

		///
		const char* getDescription() const;

		///
		const char* getUrl() const;

		///
		AppI* getNext();

	private:
		BX_ALIGN_DECL(16, uintptr_t) m_internal[4];
	};

	///
	AppI* getFirstApp();

	///
	uint32_t getNumApps();

	///
	int runApp(AppI* _app, int _argc, const char* const* _argv);

} // namespace entry

#endif // ENTRY_H_HEADER_GUARD
