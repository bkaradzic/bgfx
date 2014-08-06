/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef ENTRY_PRIVATE_H_HEADER_GUARD
#define ENTRY_PRIVATE_H_HEADER_GUARD

#include <bx/spscqueue.h>

#include "entry.h"

#ifndef ENTRY_CONFIG_USE_SDL
#	define ENTRY_CONFIG_USE_SDL 0
#endif // ENTRY_CONFIG_USE_SDL

#if !ENTRY_CONFIG_USE_SDL && \
	!defined(ENTRY_CONFIG_USE_NATIVE)
#	define ENTRY_CONFIG_USE_NATIVE 1
#else
#	define ENTRY_CONFIG_USE_NATIVE 0
#endif // ...

#if !defined(ENTRY_DEFAULT_WIDTH) && !defined(ENTRY_DEFAULT_HEIGHT)
#	define ENTRY_DEFAULT_WIDTH  1280
#	define ENTRY_DEFAULT_HEIGHT 720
#elif !defined(ENTRY_DEFAULT_WIDTH) || !defined(ENTRY_DEFAULT_HEIGHT)
#	error "Both ENTRY_DEFAULT_WIDTH and ENTRY_DEFAULT_HEIGHT must be defined."
#endif // ENTRY_DEFAULT_WIDTH

namespace entry
{
	int main(int _argc, char** _argv);

	struct Event
	{
		enum Enum
		{
			Exit,
			Key,
			Mouse,
			Size,
		};

		Event::Enum m_type;
	};

	struct KeyEvent : public Event
	{
		Key::Enum m_key;
		uint8_t m_modifiers;
		bool m_down;
	};

	struct MouseEvent : public Event
	{
		int32_t m_mx;
		int32_t m_my;
		int32_t m_mz;
		MouseButton::Enum m_button;
		bool m_down;
		bool m_move;
	};

	struct SizeEvent : public Event
	{
		uint32_t m_width;
		uint32_t m_height;
	};

	const Event* poll();
	void release(const Event* _event);

	class EventQueue
	{
	public:
		void postExitEvent()
		{
			Event* ev = new Event;
			ev->m_type = Event::Exit;
			m_queue.push(ev);
		}

		void postKeyEvent(Key::Enum _key, uint8_t _modifiers, bool _down)
		{
			KeyEvent* ev = new KeyEvent;
			ev->m_type = Event::Key;
			ev->m_key = _key;
			ev->m_modifiers = _modifiers;
			ev->m_down = _down;
			m_queue.push(ev);
		}

		void postMouseEvent(int32_t _mx, int32_t _my, int32_t _mz)
		{
			MouseEvent* ev = new MouseEvent;
			ev->m_type = Event::Mouse;
			ev->m_mx = _mx;
			ev->m_my = _my;
			ev->m_mz = _mz;
			ev->m_button = MouseButton::None;
			ev->m_down = false;
			ev->m_move = true;
			m_queue.push(ev);
		}

		void postMouseEvent(int32_t _mx, int32_t _my, int32_t _mz, MouseButton::Enum _button, bool _down)
		{
			MouseEvent* ev = new MouseEvent;
			ev->m_type = Event::Mouse;
			ev->m_mx = _mx;
			ev->m_my = _my;
			ev->m_mz = _mz;
			ev->m_button = _button;
			ev->m_down = _down;
			ev->m_move = false;
			m_queue.push(ev);
		}

		void postSizeEvent(uint32_t _width, uint32_t _height)
		{
			SizeEvent* ev = new SizeEvent;
			ev->m_type = Event::Size;
			ev->m_width = _width;
			ev->m_height = _height;
			m_queue.push(ev);
		}

		const Event* poll()
		{
			return m_queue.pop();
		}

		void release(const Event* _event) const
		{
			delete _event;
		}

	private:
		bx::SpScUnboundedQueue<Event> m_queue;
	};

} // namespace entry

#endif // ENTRY_PRIVATE_H_HEADER_GUARD
