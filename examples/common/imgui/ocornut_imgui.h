/*
 * Copyright 2014-2015 Daniel Collin. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#ifndef OCORNUT_IMGUI_H_HEADER_GUARD
#define OCORNUT_IMGUI_H_HEADER_GUARD

#include <ocornut-imgui/imgui.h>

void IMGUI_setup(int _width, int _height, uint8_t _viewId = 31);
void IMGUI_updateSize(int width, int height);
void IMGUI_preUpdate(float x, float y, int mouseLmb, int keyDown, int keyMod);
void IMGUI_postUpdate();

void IMGUI_setMouse(float x, float y, int mouseLmb);
void IMGUI_setKeyDown(int key, int modifier);
void IMGUI_setKeyUp(int key, int modifier);

#endif // OCORNUT_IMGUI_H_HEADER_GUARD
