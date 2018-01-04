/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef ENTRY_PRIVATE_H_HEADER_GUARD
#define ENTRY_PRIVATE_H_HEADER_GUARD

#define TINYSTL_ALLOCATOR entry::TinyStlAllocator

#include <bx/spscqueue.h>
#include <bx/filepath.h>

#include "entry.h"

#ifndef ENTRY_CONFIG_USE_NOOP
#	define ENTRY_CONFIG_USE_NOOP 0
#endif // ENTRY_CONFIG_USE_NOOP

#ifndef ENTRY_CONFIG_USE_SDL
#	define ENTRY_CONFIG_USE_SDL BX_PLATFORM_STEAMLINK
#endif // ENTRY_CONFIG_USE_SDL

#ifndef ENTRY_CONFIG_USE_GLFW
#	define ENTRY_CONFIG_USE_GLFW 0
#endif // ENTRY_CONFIG_USE_GLFW

#if !defined(ENTRY_CONFIG_USE_NATIVE) \
	&& !ENTRY_CONFIG_USE_NOOP \
	&& !ENTRY_CONFIG_USE_SDL \
	&& !ENTRY_CONFIG_USE_GLFW
#	define ENTRY_CONFIG_USE_NATIVE 1
#else
#	define ENTRY_CONFIG_USE_NATIVE 0
#endif // ...

#ifndef ENTRY_CONFIG_MAX_WINDOWS
#	define ENTRY_CONFIG_MAX_WINDOWS 8
#endif // ENTRY_CONFIG_MAX_WINDOWS

#ifndef ENTRY_CONFIG_MAX_GAMEPADS
#	define ENTRY_CONFIG_MAX_GAMEPADS 4
#endif // ENTRY_CONFIG_MAX_GAMEPADS

#if !defined(ENTRY_DEFAULT_WIDTH) && !defined(ENTRY_DEFAULT_HEIGHT)
#	define ENTRY_DEFAULT_WIDTH  1280
#	define ENTRY_DEFAULT_HEIGHT 720
#elif !defined(ENTRY_DEFAULT_WIDTH) || !defined(ENTRY_DEFAULT_HEIGHT)
#	error "Both ENTRY_DEFAULT_WIDTH and ENTRY_DEFAULT_HEIGHT must be defined."
#endif // ENTRY_DEFAULT_WIDTH

#ifndef ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR
#	define ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR 1
#endif // ENTRY_CONFIG_IMPLEMENT_DEFAULT_ALLOCATOR

#ifndef ENTRY_CONFIG_PROFILER
#	define ENTRY_CONFIG_PROFILER 0
#endif // ENTRY_CONFIG_PROFILER

#define ENTRY_IMPLEMENT_EVENT(_class, _type) \
			_class(WindowHandle _handle) : Event(_type, _handle) {}

namespace entry
{
	struct TinyStlAllocator
	{
		static void* static_allocate(size_t _bytes);
		static void static_deallocate(void* _ptr, size_t /*_bytes*/);
	};

	int main(int _argc, const char* const* _argv);

	char keyToAscii(Key::Enum _key, uint8_t _modifiers);

	struct Event
	{
		enum Enum
		{
			Axis,
			Char,
			Exit,
			Gamepad,
			Key,
			Mouse,
			Size,
			Window,
			Suspend,
			DropFile,
		};

		Event(Enum _type)
			: m_type(_type)
		{
			m_handle.idx = UINT16_MAX;
		}

		Event(Enum _type, WindowHandle _handle)
			: m_type(_type)
			, m_handle(_handle)
		{
		}

		Event::Enum m_type;
		WindowHandle m_handle;
	};

	struct AxisEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(AxisEvent, Event::Axis);

		GamepadAxis::Enum m_axis;
		int32_t m_value;
		GamepadHandle m_gamepad;
	};

	struct CharEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(CharEvent, Event::Char);

		uint8_t m_len;
		uint8_t m_char[4];
	};

	struct GamepadEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(GamepadEvent, Event::Gamepad);

		GamepadHandle m_gamepad;
		bool m_connected;
	};

	struct KeyEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(KeyEvent, Event::Key);

		Key::Enum m_key;
		uint8_t m_modifiers;
		bool m_down;
	};

	struct MouseEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(MouseEvent, Event::Mouse);

		int32_t m_mx;
		int32_t m_my;
		int32_t m_mz;
		MouseButton::Enum m_button;
		bool m_down;
		bool m_move;
	};

	struct SizeEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(SizeEvent, Event::Size);

		uint32_t m_width;
		uint32_t m_height;
	};

	struct WindowEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(WindowEvent, Event::Window);

		void* m_nwh;
	};

	struct SuspendEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(SuspendEvent, Event::Suspend);

		Suspend::Enum m_state;
	};

	struct DropFileEvent : public Event
	{
		ENTRY_IMPLEMENT_EVENT(DropFileEvent, Event::DropFile);

		bx::FilePath m_filePath;
	};

	const Event* poll();
	const Event* poll(WindowHandle _handle);
	void release(const Event* _event);

	class EventQueue
	{
	public:
		EventQueue()
			: m_queue(getAllocator() )
		{
		}

		~EventQueue()
		{
			for (const Event* ev = poll(); NULL != ev; ev = poll() )
			{
				release(ev);
			}
		}

		void postAxisEvent(WindowHandle _handle, GamepadHandle _gamepad, GamepadAxis::Enum _axis, int32_t _value)
		{
			AxisEvent* ev = BX_NEW(getAllocator(), AxisEvent)(_handle);
			ev->m_gamepad = _gamepad;
			ev->m_axis    = _axis;
			ev->m_value   = _value;
			m_queue.push(ev);
		}

		void postCharEvent(WindowHandle _handle, uint8_t _len, const uint8_t _char[4])
		{
			CharEvent* ev = BX_NEW(getAllocator(), CharEvent)(_handle);
			ev->m_len = _len;
			bx::memCopy(ev->m_char, _char, 4);
			m_queue.push(ev);
		}

		void postExitEvent()
		{
			Event* ev = BX_NEW(getAllocator(), Event)(Event::Exit);
			m_queue.push(ev);
		}

		void postGamepadEvent(WindowHandle _handle, GamepadHandle _gamepad, bool _connected)
		{
			GamepadEvent* ev = BX_NEW(getAllocator(), GamepadEvent)(_handle);
			ev->m_gamepad   = _gamepad;
			ev->m_connected = _connected;
			m_queue.push(ev);
		}

		void postKeyEvent(WindowHandle _handle, Key::Enum _key, uint8_t _modifiers, bool _down)
		{
			KeyEvent* ev = BX_NEW(getAllocator(), KeyEvent)(_handle);
			ev->m_key       = _key;
			ev->m_modifiers = _modifiers;
			ev->m_down      = _down;
			m_queue.push(ev);
		}

		void postMouseEvent(WindowHandle _handle, int32_t _mx, int32_t _my, int32_t _mz)
		{
			MouseEvent* ev = BX_NEW(getAllocator(), MouseEvent)(_handle);
			ev->m_mx     = _mx;
			ev->m_my     = _my;
			ev->m_mz     = _mz;
			ev->m_button = MouseButton::None;
			ev->m_down   = false;
			ev->m_move   = true;
			m_queue.push(ev);
		}

		void postMouseEvent(WindowHandle _handle, int32_t _mx, int32_t _my, int32_t _mz, MouseButton::Enum _button, bool _down)
		{
			MouseEvent* ev = BX_NEW(getAllocator(), MouseEvent)(_handle);
			ev->m_mx     = _mx;
			ev->m_my     = _my;
			ev->m_mz     = _mz;
			ev->m_button = _button;
			ev->m_down   = _down;
			ev->m_move   = false;
			m_queue.push(ev);
		}

		void postSizeEvent(WindowHandle _handle, uint32_t _width, uint32_t _height)
		{
			SizeEvent* ev = BX_NEW(getAllocator(), SizeEvent)(_handle);
			ev->m_width  = _width;
			ev->m_height = _height;
			m_queue.push(ev);
		}

		void postWindowEvent(WindowHandle _handle, void* _nwh = NULL)
		{
			WindowEvent* ev = BX_NEW(getAllocator(), WindowEvent)(_handle);
			ev->m_nwh = _nwh;
			m_queue.push(ev);
		}

		void postSuspendEvent(WindowHandle _handle, Suspend::Enum _state)
		{
			SuspendEvent* ev = BX_NEW(getAllocator(), SuspendEvent)(_handle);
			ev->m_state = _state;
			m_queue.push(ev);
		}

		void postDropFileEvent(WindowHandle _handle, const bx::FilePath& _filePath)
		{
			DropFileEvent* ev = BX_NEW(getAllocator(), DropFileEvent)(_handle);
			ev->m_filePath = _filePath;
			m_queue.push(ev);
		}

		const Event* poll()
		{
			return m_queue.pop();
		}

		const Event* poll(WindowHandle _handle)
		{
			if (isValid(_handle) )
			{
				Event* ev = m_queue.peek();
				if (NULL == ev
				||  ev->m_handle.idx != _handle.idx)
				{
					return NULL;
				}
			}

			return poll();
		}

		void release(const Event* _event) const
		{
			BX_DELETE(getAllocator(), const_cast<Event*>(_event) );
		}

	private:
		bx::SpScUnboundedQueueT<Event> m_queue;
	};

} // namespace entry

#endif // ENTRY_PRIVATE_H_HEADER_GUARD
