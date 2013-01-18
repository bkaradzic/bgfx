/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef __ENTRY_PRIVATE_H__
#define __ENTRY_PRIVATE_H__

#include <bgfxplatform.h>
#include <bx/spscqueue.h>

#include "dbg.h"
#include "entry.h"

namespace entry
{
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

		void postMouseEvent(int32_t _mx, int32_t _my, MouseButton::Enum _button, bool _down)
		{
			MouseEvent* ev = new MouseEvent;
			ev->m_type = Event::Mouse;
			ev->m_mx = _mx;
			ev->m_my = _my;
			ev->m_button = _button;
			ev->m_down = _down;
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

#endif // __ENTRY_PRIVATE_H__
