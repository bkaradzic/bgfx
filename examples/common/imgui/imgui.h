/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

// This code is based on:
//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
// Source altered and distributed from https://github.com/AdrienHerubel/imgui

#ifndef __IMGUI_H__
#define __IMGUI_H__

enum imguiMouseButton
{
	IMGUI_MBUT_LEFT = 0x01,
	IMGUI_MBUT_RIGHT = 0x02,
};

enum imguiTextAlign
{
	IMGUI_ALIGN_LEFT,
	IMGUI_ALIGN_CENTER,
	IMGUI_ALIGN_RIGHT,
};

inline uint32_t imguiRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255)
{
	return 0
		| (uint32_t(_r) <<  0) 
		| (uint32_t(_g) <<  8)
		| (uint32_t(_b) << 16)
		| (uint32_t(_a) << 24)
		;
}

bool imguiCreate(void* _data, uint32_t _size);
void imguiDestroy();

void imguiBeginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, uint8_t _view = 31);
void imguiEndFrame();

bool imguiBeginScrollArea(const char* _name, int _x, int _y, int _width, int _height, int* _scroll);
void imguiEndScrollArea();

void imguiIndent();
void imguiUnindent();
void imguiSeparator();
void imguiSeparatorLine();

bool imguiButton(const char* _text, bool _enabled = true);
bool imguiItem(const char* _text, bool _enabled = true);
bool imguiCheck(const char* _text, bool _checked, bool _enabled = true);
bool imguiCollapse(const char* _text, const char* _subtext, bool _checked, bool _enabled = true);
void imguiLabel(const char* _format, ...);
void imguiValue(const char* _text);
bool imguiSlider(const char* _text, float* val, float vmin, float vmax, float vinc, bool _enabled = true);

void imguiDrawText(int _x, int _y, imguiTextAlign _align, const char* _text, uint32_t _argb);
void imguiDrawLine(float _x0, float _y0, float _x1, float _y1, float _r, uint32_t _argb);
void imguiDrawRoundedRect(float _x, float _y, float _w, float _h, float _r, uint32_t _argb);
void imguiDrawRect(float _x, float _y, float _w, float _h, uint32_t _argb);

#endif // __IMGUI_H__
