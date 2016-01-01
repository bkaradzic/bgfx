/*
 * Copyright 2014-2015 Daniel Collin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef OCORNUT_IMGUI_H_HEADER_GUARD
#define OCORNUT_IMGUI_H_HEADER_GUARD

#include <ocornut-imgui/imgui.h>

namespace bx { struct AllocatorI; }

void IMGUI_create(const void* _data, uint32_t _size, float _fontSize, bx::AllocatorI* _allocator);
void IMGUI_destroy();
void IMGUI_beginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, int _width, int _height, char _inputChar, uint8_t _viewId);
void IMGUI_endFrame();

#endif // OCORNUT_IMGUI_H_HEADER_GUARD
