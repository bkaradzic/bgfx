/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
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

#ifndef IMGUI_H_HEADER_GUARD
#define IMGUI_H_HEADER_GUARD

#include <bgfx/bgfx.h>
#include <ocornut-imgui/imgui.h>
#include <iconfontheaders/icons_kenney.h>
#include <iconfontheaders/icons_font_awesome.h>

#define IMGUI_MBUT_LEFT   0x01
#define IMGUI_MBUT_RIGHT  0x02
#define IMGUI_MBUT_MIDDLE 0x04

inline uint32_t imguiRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255)
{
	return 0
		| (uint32_t(_r) <<  0)
		| (uint32_t(_g) <<  8)
		| (uint32_t(_b) << 16)
		| (uint32_t(_a) << 24)
		;
}

namespace bx { struct AllocatorI; }

void imguiCreate(const void* _data = NULL, uint32_t _size = 0, float _fontSize = 18.0f, bx::AllocatorI* _allocator = NULL);
void imguiDestroy();

void imguiBeginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, char _inputChar = 0, uint8_t _view = 255);
void imguiBeginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, uint16_t _surfaceWidth, uint16_t _surfaceHeight, char _inputChar = 0, uint8_t _view = 255);
void imguiEndFrame();

namespace ImGui
{
#define IMGUI_FLAGS_NONE        UINT8_C(0x00)
#define IMGUI_FLAGS_ALPHA_BLEND UINT8_C(0x01)

	// Helper function for passing bgfx::TextureHandle to ImGui::Image.
	inline void Image(bgfx::TextureHandle _handle
		, uint8_t _flags
		, uint8_t _mip
		, const ImVec2& _size
		, const ImVec2& _uv0       = ImVec2(0.0f, 0.0f)
		, const ImVec2& _uv1       = ImVec2(1.0f, 1.0f)
		, const ImVec4& _tintCol   = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
		, const ImVec4& _borderCol = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
		)
	{
		union { struct { bgfx::TextureHandle handle; uint8_t flags; uint8_t mip; } s; ImTextureID ptr; } texture;
		texture.s.handle = _handle;
		texture.s.flags  = _flags;
		texture.s.mip    = _mip;
		Image(texture.ptr, _size, _uv0, _uv1, _tintCol, _borderCol);
	}

	// Helper function for passing bgfx::TextureHandle to ImGui::Image.
	inline void Image(bgfx::TextureHandle _handle
		, const ImVec2& _size
		, const ImVec2& _uv0       = ImVec2(0.0f, 0.0f)
		, const ImVec2& _uv1       = ImVec2(1.0f, 1.0f)
		, const ImVec4& _tintCol   = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
		, const ImVec4& _borderCol = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
		)
	{
		Image(_handle, IMGUI_FLAGS_ALPHA_BLEND, 0, _size, _uv0, _uv1, _tintCol, _borderCol);
	}

	// Helper function for passing bgfx::TextureHandle to ImGui::ImageButton.
	inline bool ImageButton(bgfx::TextureHandle _handle
		, uint8_t _flags
		, uint8_t _mip
		, const ImVec2& _size
		, const ImVec2& _uv0     = ImVec2(0.0f, 0.0f)
		, const ImVec2& _uv1     = ImVec2(1.0f, 1.0f)
		, int _framePadding      = -1
		, const ImVec4& _bgCol   = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
		, const ImVec4& _tintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
		)
	{
		union { struct { bgfx::TextureHandle handle; uint8_t flags; uint8_t mip; } s; ImTextureID ptr; } texture;
		texture.s.handle = _handle;
		texture.s.flags  = _flags;
		texture.s.mip    = _mip;
		return ImageButton(texture.ptr, _size, _uv0, _uv1, _framePadding, _bgCol, _tintCol);
	}

	// Helper function for passing bgfx::TextureHandle to ImGui::ImageButton.
	inline bool ImageButton(bgfx::TextureHandle _handle
		, const ImVec2& _size
		, const ImVec2& _uv0     = ImVec2(0.0f, 0.0f)
		, const ImVec2& _uv1     = ImVec2(1.0f, 1.0f)
		, int _framePadding      = -1
		, const ImVec4& _bgCol   = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
		, const ImVec4& _tintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
		)
	{
		return ImageButton(_handle, IMGUI_FLAGS_ALPHA_BLEND, 0, _size, _uv0, _uv1, _framePadding, _bgCol, _tintCol);
	}

	inline void NextLine()
	{
		SetCursorPosY(GetCursorPosY() + GetTextLineHeightWithSpacing() );
	}

	inline bool TabButton(const char* _text, float _width, bool _active)
	{
		int32_t count = 1;

		if (_active)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.75f, 0.0f, 0.78f) );
			ImGui::PushStyleColor(ImGuiCol_Text,   ImVec4(0.0f, 0.0f,  0.0f, 1.0f ) );
			count = 2;
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 0.7f) );
		}

		bool retval = ImGui::Button(_text, ImVec2(_width, 20.0f) );
		ImGui::PopStyleColor(count);

		return retval;
	}

	inline bool MouseOverArea()
	{
		return false
			|| ImGui::IsAnyItemHovered()
			|| ImGui::IsMouseHoveringAnyWindow()
			;
	}

} // namespace ImGui

#endif // IMGUI_H_HEADER_GUARD
