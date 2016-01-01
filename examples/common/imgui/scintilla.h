/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef SCINTILLA_H_HEADER_GUARD
#define SCINTILLA_H_HEADER_GUARD

#if defined(SCI_NAMESPACE)

#include <scintilla/include/Scintilla.h>

struct ScintillaEditor
{
	static ScintillaEditor* create(int _width, int _height);
	static void destroy(ScintillaEditor* _scintilla);

	intptr_t command(unsigned int _message, uintptr_t _p0 = 0, intptr_t _p1 = 0);
	void draw();
};

ScintillaEditor* ImGuiScintilla(const char* _name, bool* _opened, const ImVec2& _size);

#endif // defined(SCI_NAMESPACE)

#endif // SCINTILLA_H_HEADER_GUARD
