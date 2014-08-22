/*
 * Copyright 2010-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <memory.h>
#include <string>

#include "entry_p.h"
#include "input.h"

#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>
namespace stl = tinystl;

struct Mouse
{
	Mouse()
		: m_width(1280)
		, m_height(720)
		, m_wheelDelta(120)
		, m_lock(false)
	{
	}

	void reset()
	{
		if (m_lock)
		{
			m_norm[0] = 0.0f;
			m_norm[1] = 0.0f;
			m_norm[2] = 0.0f;
		}

		memset(m_buttons, 0, sizeof(m_buttons) );
	}

	void setResolution(uint16_t _width, uint16_t _height)
	{
		m_width = _width;
		m_height = _height;
	}

	void setPos(int32_t _mx, int32_t _my, int32_t _mz)
	{
		m_absolute[0] = _mx;
		m_absolute[1] = _my;
		m_absolute[2] = _mz;
		m_norm[0] = float(_mx)/float(m_width);
		m_norm[1] = float(_my)/float(m_height);
		m_norm[2] = float(_mz)/float(m_wheelDelta);
	}

	void setButtonState(entry::MouseButton::Enum _button, uint8_t _state)
	{
		m_buttons[_button] = _state;
	}

	int32_t m_absolute[3];
	float m_norm[3];
	int32_t m_wheel;
	uint8_t m_buttons[entry::MouseButton::Count];
	uint16_t m_width;
	uint16_t m_height;
	uint16_t m_wheelDelta;
	bool m_lock;
};

struct Keyboard
{
	Keyboard()
	{
	}

	void reset()
	{
		memset(m_key, 0, sizeof(m_key) );
		memset(m_once, 0xff, sizeof(m_once) );
	}

	static uint32_t encodeKeyState(uint8_t _modifiers, bool _down)
	{
		uint32_t state = 0;
		state |= uint32_t(_modifiers)<<16;
		state |= uint32_t(_down)<<8;
		return state;
	}

	static void decodeKeyState(uint32_t _state, uint8_t& _modifiers, bool& _down)
	{
		_modifiers = (_state>>16)&0xff;
		_down = 0 != ( (_state>>8)&0xff);
	}

	void setKeyState(entry::Key::Enum _key, uint8_t _modifiers, bool _down)
	{
		m_key[_key] = encodeKeyState(_modifiers, _down);
		m_once[_key] = false;
	}

	uint32_t m_key[256];
	bool m_once[256];
};

struct Input
{
	Input()
	{
		reset();
	}

	~Input()
	{
	}

	void addBindings(const char* _name, const InputBinding* _bindings)
	{
		m_inputBindingsMap.insert(stl::make_pair(_name, _bindings) );
	}

	void removeBindings(const char* _name)
	{
		m_inputBindingsMap.erase(m_inputBindingsMap.find(_name));
	}

	void process(const InputBinding* _bindings)
	{
		for (const InputBinding* binding = _bindings; binding->m_key != entry::Key::None; ++binding)
		{
			uint8_t modifiers;
			bool down;
			Keyboard::decodeKeyState(m_keyboard.m_key[binding->m_key], modifiers, down);

			if (binding->m_flags == 1)
			{
				if (down)
				{
					if (modifiers == binding->m_modifiers
					&&  !m_keyboard.m_once[binding->m_key])
					{
						binding->m_fn(binding->m_userData);
						m_keyboard.m_once[binding->m_key] = true;
					}
				}
				else
				{
					m_keyboard.m_once[binding->m_key] = false;
				}
			}
			else
			{
				if (down
				&&  modifiers == binding->m_modifiers)
				{
					binding->m_fn(binding->m_userData);
				}
			}
		}
	}

	void process()
	{
		for (InputBindingMap::const_iterator it = m_inputBindingsMap.begin(); it != m_inputBindingsMap.end(); ++it)
		{
			process(it->second);
		}
	}

	void reset()
	{
		m_mouse.reset();
		m_keyboard.reset();
	}

	typedef stl::unordered_map<const char*, const InputBinding*> InputBindingMap;
	InputBindingMap m_inputBindingsMap;
	Mouse m_mouse;
	Keyboard m_keyboard;
};

static Input s_input;

void inputAddBindings(const char* _name, const InputBinding* _bindings)
{
	s_input.addBindings(_name, _bindings);
}

void inputRemoveBindings(const char* _name)
{
	s_input.removeBindings(_name);
}

void inputProcess()
{
	s_input.process();
}

void inputSetMouseResolution(uint16_t _width, uint16_t _height)
{
	s_input.m_mouse.setResolution(_width, _height);
}

void inputSetKeyState(entry::Key::Enum _key, uint8_t _modifiers, bool _down)
{
	s_input.m_keyboard.setKeyState(_key, _modifiers, _down);
}

void inputSetMousePos(int32_t _mx, int32_t _my, int32_t _mz)
{
	s_input.m_mouse.setPos(_mx, _my, _mz);
}

void inputSetMouseButtonState(entry::MouseButton::Enum _button, uint8_t _state)
{
	s_input.m_mouse.setButtonState(_button, _state);
}

void inputGetMouse(float _mouse[3])
{
	_mouse[0] = s_input.m_mouse.m_norm[0];
	_mouse[1] = s_input.m_mouse.m_norm[1];
	_mouse[2] = s_input.m_mouse.m_norm[2];
	s_input.m_mouse.m_norm[0] = 0.0f;
	s_input.m_mouse.m_norm[1] = 0.0f;
	s_input.m_mouse.m_norm[2] = 0.0f;
}

bool inputIsMouseLocked()
{
	return s_input.m_mouse.m_lock;
}

void inputSetMouseLock(bool _lock)
{
	if (s_input.m_mouse.m_lock != _lock)
	{
		s_input.m_mouse.m_lock = _lock;
		entry::setMouseLock(_lock);
		if (_lock)
		{
			s_input.m_mouse.m_norm[0] = 0.0f;
			s_input.m_mouse.m_norm[1] = 0.0f;
			s_input.m_mouse.m_norm[2] = 0.0f;
		}
	}
}
