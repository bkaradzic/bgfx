/*
 * Copyright 2010-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef INPUT_H_HEADER_GUARD
#define INPUT_H_HEADER_GUARD

#include <stdint.h>
#include "entry.h"

typedef void (*InputBindingFn)(const void* _userData);

struct InputBinding
{
	entry::Key::Enum m_key;
	uint8_t m_modifiers;
	uint8_t m_flags;
	InputBindingFn m_fn;
	const void* m_userData;
};

#define INPUT_BINDING_END { entry::Key::None, entry::Modifier::None, 0, NULL, NULL }

///
void inputAddBindings(const char* _name, const InputBinding* _bindings);

///
void inputRemoveBindings(const char* _name);

///
void inputProcess();

///
void inputSetKeyState(entry::Key::Enum  _key, uint8_t _modifiers, bool _down);

///
void inputSetMouseResolution(uint16_t _width, uint16_t _height);

///
void inputSetMousePos(int32_t _mx, int32_t _my, int32_t _mz);

///
void inputSetMouseButtonState(entry::MouseButton::Enum _button, uint8_t _state);

///
void inputSetMouseLock(bool _lock);

///
void inputGetMouse(float _mouse[3]);

///
bool inputIsMouseLocked();

#endif // INPUT_H_HEADER_GUARD
