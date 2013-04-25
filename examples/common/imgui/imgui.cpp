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

#include <stdio.h>
#include <bx/string.h>
#include <bx/uint32_t.h>
#include <bgfx.h>

#include "imgui.h"
#include "../math.h"

#include "vs_imgui_color.bin.h"
#include "fs_imgui_color.bin.h"
#include "vs_imgui_texture.bin.h"
#include "fs_imgui_texture.bin.h"

#define MAX_TEMP_COORDS 100
#define NUM_CIRCLE_VERTS (8 * 4)

static const int32_t BUTTON_HEIGHT = 20;
static const int32_t SLIDER_HEIGHT = 20;
static const int32_t SLIDER_MARKER_WIDTH = 10;
static const int32_t CHECK_SIZE = 8;
static const int32_t DEFAULT_SPACING = 4;
static const int32_t TEXT_HEIGHT = 8;
static const int32_t SCROLL_AREA_PADDING = 6;
static const int32_t INDENT_SIZE = 16;
static const int32_t AREA_HEADER = 28;
static const float s_tabStops[4] = {150, 210, 270, 330};

static void* imguiMalloc(size_t size, void* /*_userptr*/)
{
	return malloc(size);
}

static void imguiFree(void* _ptr, void* /*_userptr*/)
{
	free(_ptr);
}

#define STBTT_malloc(_x, _y) imguiMalloc(_x, _y)
#define STBTT_free(_x, _y) imguiFree(_x, _y)
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype/stb_truetype.h>

struct PosColorVertex
{
	float m_x;
	float m_y;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl.begin();
		ms_decl.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float);
		ms_decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
		ms_decl.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

struct PosColorUvVertex
{
	float m_x;
	float m_y;
	float m_u;
	float m_v;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl.begin();
		ms_decl.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float);
		ms_decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
		ms_decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
		ms_decl.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorUvVertex::ms_decl;

struct Imgui
{
	Imgui()
		: m_mx(-1)
		, m_my(-1)
		, m_scroll(0)
		, m_active(0)
		, m_hot(0)
		, m_hotToBe(0)
		, m_dragX(0)
		, m_dragY(0)
		, m_dragOrig(0)
		, m_widgetX(0)
		, m_widgetY(0)
		, m_widgetW(100)
		, m_left(false)
		, m_leftPressed(false)
		, m_leftReleased(false)
		, m_isHot(false)
		, m_isActive(false)
		, m_wentActive(false)
		, m_insideCurrentScroll(false)
		, m_areaId(0)
		, m_widgetId(0)
		, m_scrollTop(0)
		, m_scrollBottom(0)
		, m_scrollRight(0)
		, m_scrollAreaTop(0)
		, m_scrollVal(NULL)
		, m_focusTop(0)
		, m_focusBottom(0)
		, m_scrollId(0)
		, m_insideScrollArea(false)
		, m_textureWidth(512)
		, m_textureHeight(512)
		, m_halfTexel(0.0f)
		, m_view(31)
	{
		m_invTextureWidth  = 1.0f/m_textureWidth;
		m_invTextureHeight = 1.0f/m_textureHeight;

		u_texColor.idx = bgfx::invalidHandle;
		m_fontTexture.idx = bgfx::invalidHandle;
		m_colorProgram.idx = bgfx::invalidHandle;
		m_textureProgram.idx = bgfx::invalidHandle;
	}

	bool create(void* _data, uint32_t /*_size*/)
	{
		for (int32_t ii = 0; ii < NUM_CIRCLE_VERTS; ++ii)
		{
			float a = (float)ii / (float)NUM_CIRCLE_VERTS * (float)(M_PI * 2.0);
			m_circleVerts[ii * 2 + 0] = cosf(a);
			m_circleVerts[ii * 2 + 1] = sinf(a);
		}

		PosColorVertex::init();
		PosColorUvVertex::init();

		u_texColor  = bgfx::createUniform("u_texColor", bgfx::UniformType::Uniform1i);

		const bgfx::Memory* vs_imgui_color;
		const bgfx::Memory* fs_imgui_color;
		const bgfx::Memory* vs_imgui_texture;
		const bgfx::Memory* fs_imgui_texture;

		switch (bgfx::getRendererType() )
		{
		case bgfx::RendererType::Direct3D9:
			vs_imgui_color   = bgfx::makeRef(vs_imgui_color_dx9, sizeof(vs_imgui_color_dx9) );
			fs_imgui_color   = bgfx::makeRef(fs_imgui_color_dx9, sizeof(fs_imgui_color_dx9) );
			vs_imgui_texture = bgfx::makeRef(vs_imgui_texture_dx9, sizeof(vs_imgui_texture_dx9) );
			fs_imgui_texture = bgfx::makeRef(fs_imgui_texture_dx9, sizeof(fs_imgui_texture_dx9) );
			m_halfTexel = 0.5f;
			break;

		case bgfx::RendererType::Direct3D11:
			vs_imgui_color   = bgfx::makeRef(vs_imgui_color_dx11, sizeof(vs_imgui_color_dx11) );
			fs_imgui_color   = bgfx::makeRef(fs_imgui_color_dx11, sizeof(fs_imgui_color_dx11) );
			vs_imgui_texture = bgfx::makeRef(vs_imgui_texture_dx11, sizeof(vs_imgui_texture_dx11) );
			fs_imgui_texture = bgfx::makeRef(fs_imgui_texture_dx11, sizeof(fs_imgui_texture_dx11) );
			break;

		default:
			vs_imgui_color   = bgfx::makeRef(vs_imgui_color_glsl, sizeof(vs_imgui_color_glsl) );
			fs_imgui_color   = bgfx::makeRef(fs_imgui_color_glsl, sizeof(fs_imgui_color_glsl) );
			vs_imgui_texture = bgfx::makeRef(vs_imgui_texture_glsl, sizeof(vs_imgui_texture_glsl) );
			fs_imgui_texture = bgfx::makeRef(fs_imgui_texture_glsl, sizeof(fs_imgui_texture_glsl) );
			break;
		}

		bgfx::VertexShaderHandle vsh;
		bgfx::FragmentShaderHandle fsh;

		vsh = bgfx::createVertexShader(vs_imgui_color);
		fsh = bgfx::createFragmentShader(fs_imgui_color);
		m_colorProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyVertexShader(vsh);
		bgfx::destroyFragmentShader(fsh);

		vsh = bgfx::createVertexShader(vs_imgui_texture);
		fsh = bgfx::createFragmentShader(fs_imgui_texture);
		m_textureProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyVertexShader(vsh);
		bgfx::destroyFragmentShader(fsh);

		const bgfx::Memory* mem = bgfx::alloc(m_textureWidth * m_textureHeight);
		stbtt_BakeFontBitmap( (uint8_t*)_data, 0, 15.0f, mem->data, m_textureWidth, m_textureHeight, 32, 96, m_cdata);
		m_fontTexture = bgfx::createTexture2D(m_textureWidth, m_textureHeight, 1, bgfx::TextureFormat::L8, BGFX_TEXTURE_NONE, mem);

		return true;
	}

	void destroy()
	{
		bgfx::destroyUniform(u_texColor);
		bgfx::destroyTexture(m_fontTexture);
	}

	bool anyActive() const
	{
		return m_active != 0;
	}

	bool isActive(uint32_t _id) const
	{
		return m_active == _id;
	}

	bool isHot(uint32_t _id) const
	{
		return m_hot == _id;
	}

	bool inRect(int32_t _x, int32_t _y, int32_t _width, int32_t _height, bool _checkScroll = true) const
	{
		return (!_checkScroll || m_insideCurrentScroll)
			&& m_mx >= _x
			&& m_mx <= _x + _width
			&& m_my >= _y
			&& m_my <= _y + _height;
	}

	void clearInput()
	{
		m_leftPressed = false;
		m_leftReleased = false;
		m_scroll = 0;
	}

	void clearActive()
	{
		m_active = 0;
		// mark all UI for this frame as processed
		clearInput();
	}

	void setActive(uint32_t _id)
	{
		m_active = _id;
		m_wentActive = true;
	}

	void setHot(uint32_t _id)
	{
		m_hotToBe = _id;
	}

	bool buttonLogic(uint32_t _id, bool _over)
	{
		bool res = false;
		// process down
		if (!anyActive() )
		{
			if (_over)
			{
				setHot(_id);
			}

			if (isHot(_id)
			&& m_leftPressed)
			{
				setActive(_id);
			}
		}

		// if button is active, then react on left up
		if (isActive(_id) )
		{
			m_isActive = true;
			if (_over)
			{
				setHot(_id);
			}

			if (m_leftReleased)
			{
				if (isHot(_id) )
				{
					res = true;
				}

				clearActive();
			}
		}

		if (isHot(_id) )
		{
			m_isHot = true;
		}

		return res;
	}

	void updateInput(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll)
	{
		bool left = (_button & IMGUI_MBUT_LEFT) != 0;

		m_mx = _mx;
		m_my = _my;
		m_leftPressed = !m_left && left;
		m_leftReleased = m_left && !left;
		m_left = left;
		m_scroll = _scroll;
	}

	void beginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, uint8_t _view)
	{
		m_view = _view;
		bgfx::setViewSeq(_view, true);
		bgfx::setViewRect(_view, 0, 0, _width, _height);

		float proj[16];
		mtxOrtho(proj, 0.0f, (float)_width, (float)_height, 0.0f, 0.0f, 1000.0f);
		bgfx::setViewTransform(_view, NULL, proj);

		updateInput(_mx, _my, _button, _scroll);

		m_hot = m_hotToBe;
		m_hotToBe = 0;

		m_wentActive = false;
		m_isActive = false;
		m_isHot = false;

		m_widgetX = 0;
		m_widgetY = 0;
		m_widgetW = 0;

		m_areaId = 1;
		m_widgetId = 1;
	}

	void endFrame()
	{
		clearInput();
	}

	bool beginScrollArea(const char* _name, int32_t _x, int32_t _y, int32_t _width, int32_t _height, int32_t* _scroll)
	{
		m_areaId++;
		m_widgetId = 0;
		m_scrollId = (m_areaId << 16) | m_widgetId;

		m_widgetX = _x + SCROLL_AREA_PADDING;
		m_widgetY = _y + + AREA_HEADER + (*_scroll);
		m_widgetW = _width - SCROLL_AREA_PADDING * 4;
		m_scrollTop = _y + SCROLL_AREA_PADDING;
		m_scrollBottom = _y - AREA_HEADER + _height;
		m_scrollRight = _x + _width - SCROLL_AREA_PADDING * 3;
		m_scrollVal = _scroll;

		m_scrollAreaTop = m_widgetY;

		m_focusTop = _y - AREA_HEADER;
		m_focusBottom = _y - AREA_HEADER + _height;

		m_insideScrollArea = inRect(_x, _y, _width, _height, false);
		m_insideCurrentScroll = m_insideScrollArea;

		drawRoundedRect( (float)_x
			, (float)_y
			, (float)_width
			, (float)_height
			, 6
			, imguiRGBA(0, 0, 0, 192)
			);

		drawText(_x + AREA_HEADER / 2
			, _y + AREA_HEADER / 2
			, IMGUI_ALIGN_LEFT
			, _name
			, imguiRGBA(255, 255, 255, 128)
			);

//		setScissor(_x + SCROLL_AREA_PADDING, _y + SCROLL_AREA_PADDING, _width - SCROLL_AREA_PADDING * 4, _height - AREA_HEADER - SCROLL_AREA_PADDING);

		return m_insideScrollArea;
	}

	void endScrollArea()
	{
		// Disable scissoring.
//		setScissor(-1, -1, -1, -1);

		// Draw scroll bar
		int32_t xx = m_scrollRight + SCROLL_AREA_PADDING / 2;
		int32_t yy = m_scrollTop;
		int32_t width = SCROLL_AREA_PADDING * 2;
		int32_t height = m_scrollBottom - m_scrollTop;

		int32_t stop = m_scrollAreaTop;
		int32_t sbot = m_widgetY;
		int32_t sh = sbot - stop; // The scrollable area height.

		float barHeight = (float)height / (float)sh;

		if (barHeight < 1)
		{
			float barY = (float)(yy - sbot) / (float)sh;
			if (barY < 0)
			{
				barY = 0;
			}

			if (barY > 1)
			{
				barY = 1;
			}

			// Handle scroll bar logic.
			uint32_t hid = m_scrollId;
			int32_t hx = xx;
			int32_t hy = yy + (int)(barY * height);
			int32_t hw = width;
			int32_t hh = (int)(barHeight * height);

			const int32_t range = height - (hh - 1);
			bool over = inRect(hx, hy, hw, hh);
			buttonLogic(hid, over);
			if (isActive(hid) )
			{
				float u = (float)(hy - yy) / (float)range;
				if (m_wentActive)
				{
					m_dragY = m_my;
					m_dragOrig = u;
				}

				if (m_dragY != m_my)
				{
					u = m_dragOrig + (m_my - m_dragY) / (float)range;
					if (u < 0)
					{
						u = 0;
					}

					if (u > 1)
					{
						u = 1;
					}

					*m_scrollVal = (int)( (1 - u) * (sh - height) );
				}
			}

			// BG
			drawRoundedRect( (float)xx
				, (float)yy
				, (float)width
				, (float)height
				, (float)width / 2 - 1
				, imguiRGBA(0, 0, 0, 196)
				);

			// Bar
			if (isActive(hid) )
			{
				drawRoundedRect( (float)hx
					, (float)hy
					, (float)hw
					, (float)hh
					, (float)width / 2 - 1
					, imguiRGBA(255, 196, 0, 196)
					);
			}
			else
			{
				drawRoundedRect( (float)hx
					, (float)hy
					, (float)hw
					, (float)hh
					, (float)width / 2 - 1
					, isHot(hid) ? imguiRGBA(255, 196, 0, 96) : imguiRGBA(255, 255, 255, 64)
					);
			}

			// Handle mouse scrolling.
			if (m_insideScrollArea) // && !anyActive())
			{
				if (m_scroll)
				{
					*m_scrollVal += 20 * m_scroll;
					if (*m_scrollVal < 0)
					{
						*m_scrollVal = 0;
					}

					if (*m_scrollVal > (sh - height) )
					{
						*m_scrollVal = (sh - height);
					}
				}
			}
		}

		m_insideCurrentScroll = false;
	}

	bool button(const char* _text, bool _enabled)
	{
		m_widgetId++;
		uint32_t id = (m_areaId << 16) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = BUTTON_HEIGHT;
		m_widgetY += BUTTON_HEIGHT + DEFAULT_SPACING;

		bool over = _enabled	&& inRect(xx, yy, width, height);
		bool res = buttonLogic(id, over);

		drawRoundedRect( (float)xx
			, (float)yy
			, (float)width
			, (float)height
			, (float)BUTTON_HEIGHT / 2 - 1
			, imguiRGBA(128, 128, 128, isActive(id) ? 196 : 96)
			);

		if (_enabled)
		{
			drawText(xx + BUTTON_HEIGHT / 2
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + BUTTON_HEIGHT / 2
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		return res;
	}

	bool item(const char* _text, bool _enabled)
	{
		m_widgetId++;
		uint32_t id = (m_areaId << 16) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = BUTTON_HEIGHT;
		m_widgetY += BUTTON_HEIGHT + DEFAULT_SPACING;

		bool over = _enabled && inRect(xx, yy, width, height);
		bool res = buttonLogic(id, over);

		if (isHot(id) )
		{
			drawRoundedRect( (float)xx
				, (float)yy
				, (float)width
				, (float)height
				, 2.0f
				, imguiRGBA(255, 196, 0, isActive(id) ? 196 : 96)
				);
		}

		if (_enabled)
		{
			drawText(xx + BUTTON_HEIGHT / 2
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + BUTTON_HEIGHT / 2
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		return res;
	}

	bool check(const char* _text, bool _checked, bool _enabled)
	{
		m_widgetId++;
		uint32_t id = (m_areaId << 16) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = BUTTON_HEIGHT;
		m_widgetY += BUTTON_HEIGHT + DEFAULT_SPACING;

		bool over = _enabled && inRect(xx, yy, width, height);
		bool res = buttonLogic(id, over);

		const int32_t cx = xx + BUTTON_HEIGHT / 2 - CHECK_SIZE / 2;
		const int32_t cy = yy + BUTTON_HEIGHT / 2 - CHECK_SIZE / 2;
		drawRoundedRect( (float)cx - 3
			, (float)cy - 3
			, (float)CHECK_SIZE + 6
			, (float)CHECK_SIZE + 6
			, 4
			, imguiRGBA(128, 128, 128, isActive(id) ? 196 : 96)
			);

		if (_checked)
		{
			if (_enabled)
			{
				drawRoundedRect( (float)cx
					, (float)cy
					, (float)CHECK_SIZE
					, (float)CHECK_SIZE
					, (float)CHECK_SIZE / 2 - 1
					, imguiRGBA(255, 255, 255, isActive(id) ? 255 : 200)
					);
			}
			else
			{
				drawRoundedRect( (float)cx
					, (float)cy
					, (float)CHECK_SIZE
					, (float)CHECK_SIZE
					, (float)CHECK_SIZE / 2 - 1
					, imguiRGBA(128, 128, 128, 200)
					);
			}
		}

		if (_enabled)
		{
			drawText(xx + BUTTON_HEIGHT
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + BUTTON_HEIGHT
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		return res;
	}

	bool collapse(const char* _text, const char* _subtext, bool _checked, bool _enabled)
	{
		m_widgetId++;
		uint32_t id = (m_areaId << 16) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = BUTTON_HEIGHT;
		m_widgetY += BUTTON_HEIGHT + DEFAULT_SPACING;

		const int32_t cx = xx + BUTTON_HEIGHT / 2 - CHECK_SIZE / 2;
		const int32_t cy = yy + BUTTON_HEIGHT / 2 - CHECK_SIZE / 2;

		bool over = _enabled && inRect(xx, yy, width, height);
		bool res = buttonLogic(id, over);

		if (_checked)
		{
			drawTriangle(cx
				, cy
				, CHECK_SIZE
				, CHECK_SIZE
				, 2
				, imguiRGBA(255, 255, 255, isActive(id) ? 255 : 200)
				);
		}
		else
		{
			drawTriangle(cx
				, cy
				, CHECK_SIZE
				, CHECK_SIZE
				, 1
				, imguiRGBA(255, 255, 255, isActive(id) ? 255 : 200)
				);
		}

		if (_enabled)
		{
			drawText(xx + BUTTON_HEIGHT
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + BUTTON_HEIGHT
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		if (_subtext)
		{
			drawText(xx + width - BUTTON_HEIGHT / 2
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_RIGHT
				, _subtext
				, imguiRGBA(255, 255, 255, 128)
				);
		}

		return res;
	}

	void labelVargs(const char* _format, va_list _argList)
	{
		char temp[8192];
		char* out = temp;
		int32_t len = bx::vsnprintf(out, sizeof(temp), _format, _argList);
		if ( (int32_t)sizeof(temp) < len)
		{
			out = (char*)alloca(len+1);
			len = bx::vsnprintf(out, len, _format, _argList);
		}
		out[len] = '\0';

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		m_widgetY += BUTTON_HEIGHT;
		drawText(xx
			, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
			, IMGUI_ALIGN_LEFT
			, out
			, imguiRGBA(255, 255, 255, 255)
			);
	}

	void value(const char* _text)
	{
		const int32_t xx = m_widgetX;
		const int32_t yy = m_widgetY;
		const int32_t ww = m_widgetW;
		m_widgetY += BUTTON_HEIGHT;

		drawText(xx + ww - BUTTON_HEIGHT / 2
			, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
			, IMGUI_ALIGN_RIGHT
			, _text
			, imguiRGBA(255, 255, 255, 200)
			);
	}

	bool slider(const char* _text, float* _val, float _vmin, float _vmax, float _vinc, bool _enabled)
	{
		m_widgetId++;
		uint32_t id = (m_areaId << 16) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = SLIDER_HEIGHT;
		m_widgetY += SLIDER_HEIGHT + DEFAULT_SPACING;

		drawRoundedRect( (float)xx, (float)yy, (float)width, (float)height, 4.0f, imguiRGBA(0, 0, 0, 128) );

		const int32_t range = width - SLIDER_MARKER_WIDTH;

		float uu = (*_val - _vmin) / (_vmax - _vmin);
		if (uu < 0)
		{
			uu = 0;
		}

		if (uu > 1)
		{
			uu = 1;
		}

		int32_t m = (int)(uu * range);

		bool over = _enabled && inRect(xx + m, yy, SLIDER_MARKER_WIDTH, SLIDER_HEIGHT);
		bool res = buttonLogic(id, over);
		bool valChanged = false;

		if (isActive(id) )
		{
			if (m_wentActive)
			{
				m_dragX = m_mx;
				m_dragOrig = uu;
			}

			if (m_dragX != m_mx)
			{
				uu = m_dragOrig + (float)(m_mx - m_dragX) / (float)range;
				if (uu < 0)
				{
					uu = 0;
				}

				if (uu > 1)
				{
					uu = 1;
				}

				*_val = _vmin + uu * (_vmax - _vmin);
				*_val = floorf(*_val / _vinc + 0.5f) * _vinc; // Snap to vinc
				m = (int)(uu * range);
				valChanged = true;
			}
		}

		if (isActive(id) )
		{
			drawRoundedRect( (float)(xx + m)
				, (float)yy
				, (float)SLIDER_MARKER_WIDTH
				, (float)SLIDER_HEIGHT
				, 4.0f
				, imguiRGBA(255, 255, 255, 255)
				);
		}
		else
		{
			drawRoundedRect( (float)(xx + m)
				, (float)yy
				, (float)SLIDER_MARKER_WIDTH
				, (float)SLIDER_HEIGHT
				, 4.0f
				, isHot(id) ? imguiRGBA(255, 196, 0, 128) : imguiRGBA(255, 255, 255, 64)
				);
		}

		// TODO: fix this, take a look at 'nicenum'.
		int32_t digits = (int)(ceilf(log10f(_vinc) ) );
		char fmt[16];
		bx::snprintf(fmt, 16, "%%.%df", digits >= 0 ? 0 : -digits);
		char msg[128];
		bx::snprintf(msg, 128, fmt, *_val);

		if (_enabled)
		{
			drawText(xx + SLIDER_HEIGHT / 2
				, yy + SLIDER_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);

			drawText(xx + width - SLIDER_HEIGHT / 2
				, yy + SLIDER_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_RIGHT
				, msg
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + SLIDER_HEIGHT / 2
				, yy + SLIDER_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_LEFT
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);

			drawText(xx + width - SLIDER_HEIGHT / 2
				, yy + SLIDER_HEIGHT / 2 + TEXT_HEIGHT / 2
				, IMGUI_ALIGN_RIGHT
				, msg
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		return res || valChanged;
	}

	void indent()
	{
		m_widgetX += INDENT_SIZE;
		m_widgetW -= INDENT_SIZE;
	}

	void unindent()
	{
		m_widgetX -= INDENT_SIZE;
		m_widgetW += INDENT_SIZE;
	}

	void separator()
	{
		m_widgetY += DEFAULT_SPACING * 3;
	}

	void separatorLine()
	{
		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = 1;
		m_widgetY += DEFAULT_SPACING * 4;

		drawRect( (float)xx
			, (float)yy
			, (float)width
			, (float)height
			, imguiRGBA(255, 255, 255, 32)
			);
	}

	void drawPolygon(const float* _coords, uint32_t _numCoords, float _r, uint32_t _abgr)
	{
		_numCoords = bx::uint32_min(_numCoords, MAX_TEMP_COORDS);

		for (uint32_t ii = 0, jj = _numCoords - 1; ii < _numCoords; jj = ii++)
		{
			const float* v0 = &_coords[jj * 2];
			const float* v1 = &_coords[ii * 2];
			float dx = v1[0] - v0[0];
			float dy = v1[1] - v0[1];
			float d = sqrtf(dx * dx + dy * dy);
			if (d > 0)
			{
				d = 1.0f / d;
				dx *= d;
				dy *= d;
			}

			m_tempNormals[jj * 2 + 0] = dy;
			m_tempNormals[jj * 2 + 1] = -dx;
		}

		for (uint32_t ii = 0, jj = _numCoords - 1; ii < _numCoords; jj = ii++)
		{
			float dlx0 = m_tempNormals[jj * 2 + 0];
			float dly0 = m_tempNormals[jj * 2 + 1];
			float dlx1 = m_tempNormals[ii * 2 + 0];
			float dly1 = m_tempNormals[ii * 2 + 1];
			float dmx = (dlx0 + dlx1) * 0.5f;
			float dmy = (dly0 + dly1) * 0.5f;
			float dmr2 = dmx * dmx + dmy * dmy;
			if (dmr2 > 0.000001f)
			{
				float scale = 1.0f / dmr2;
				if (scale > 10.0f)
				{
					scale = 10.0f;
				}

				dmx *= scale;
				dmy *= scale;
			}

			m_tempCoords[ii * 2 + 0] = _coords[ii * 2 + 0] + dmx * _r;
			m_tempCoords[ii * 2 + 1] = _coords[ii * 2 + 1] + dmy * _r;
		}

		uint32_t numVertices = _numCoords*6 + (_numCoords-2)*3;
		if (bgfx::checkAvailTransientVertexBuffer(numVertices, PosColorVertex::ms_decl) )
		{
			bgfx::TransientVertexBuffer tvb;
			bgfx::allocTransientVertexBuffer(&tvb, numVertices, PosColorVertex::ms_decl);
			uint32_t trans = _abgr&0xffffff;

			PosColorVertex* vertex = (PosColorVertex*)tvb.data;
			for (uint32_t ii = 0, jj = _numCoords-1; ii < _numCoords; jj = ii++)
			{
				vertex->m_x = _coords[ii*2+0];
				vertex->m_y = _coords[ii*2+1];
				vertex->m_abgr = _abgr;
				++vertex;

				vertex->m_x = _coords[jj*2+0];
				vertex->m_y = _coords[jj*2+1];
				vertex->m_abgr = _abgr;
				++vertex;

				vertex->m_x = m_tempCoords[jj*2+0];
				vertex->m_y = m_tempCoords[jj*2+1];
				vertex->m_abgr = trans;
				++vertex;

				vertex->m_x = m_tempCoords[jj*2+0];
				vertex->m_y = m_tempCoords[jj*2+1];
				vertex->m_abgr = trans;
				++vertex;

				vertex->m_x = m_tempCoords[ii*2+0];
				vertex->m_y = m_tempCoords[ii*2+1];
				vertex->m_abgr = trans;
				++vertex;

				vertex->m_x = _coords[ii*2+0];
				vertex->m_y = _coords[ii*2+1];
				vertex->m_abgr = _abgr;
				++vertex;
			}

			for (uint32_t ii = 2; ii < _numCoords; ++ii)
			{
				vertex->m_x = _coords[0];
				vertex->m_y = _coords[1];
				vertex->m_abgr = _abgr;
				++vertex;

				vertex->m_x = _coords[(ii-1)*2+0];
				vertex->m_y = _coords[(ii-1)*2+1];
				vertex->m_abgr = _abgr;
				++vertex;

				vertex->m_x = _coords[ii*2+0];
				vertex->m_y = _coords[ii*2+1];
				vertex->m_abgr = _abgr;
				++vertex;
			}

			bgfx::setVertexBuffer(&tvb);
			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
				);
			bgfx::setProgram(m_colorProgram);
			bgfx::submit(m_view);
		}
	}

	void drawRect(float _x, float _y, float w, float h, uint32_t _argb, float _fth = 1.0f)
	{
		float verts[4 * 2] =
		{
			_x + 0.5f,     _y + 0.5f,
			_x + w - 0.5f, _y + 0.5f,
			_x + w - 0.5f, _y + h - 0.5f,
			_x + 0.5f,     _y + h - 0.5f,
		};

		drawPolygon(verts, 4, _fth, _argb);
	}

	void drawRoundedRect(float _x, float _y, float w, float h, float r, uint32_t _argb, float _fth = 1.0f)
	{
		const uint32_t num = NUM_CIRCLE_VERTS / 4;
		const float* cverts = m_circleVerts;
		float verts[(num + 1) * 4 * 2];
		float* vv = verts;

		for (uint32_t ii = 0; ii <= num; ++ii)
		{
			*vv++ = _x + w - r + cverts[ii * 2] * r;
			*vv++ = _y + h - r + cverts[ii * 2 + 1] * r;
		}

		for (uint32_t ii = num; ii <= num * 2; ++ii)
		{
			*vv++ = _x + r + cverts[ii * 2] * r;
			*vv++ = _y + h - r + cverts[ii * 2 + 1] * r;
		}

		for (uint32_t ii = num * 2; ii <= num * 3; ++ii)
		{
			*vv++ = _x + r + cverts[ii * 2] * r;
			*vv++ = _y + r + cverts[ii * 2 + 1] * r;
		}

		for (uint32_t ii = num * 3; ii < num * 4; ++ii)
		{
			*vv++ = _x + w - r + cverts[ii * 2] * r;
			*vv++ = _y + r + cverts[ii * 2 + 1] * r;
		}

		*vv++ = _x + w - r + cverts[0] * r;
		*vv++ = _y + r + cverts[1] * r;

		drawPolygon(verts, (num + 1) * 4, _fth, _argb);
	}

	void drawLine(float _x0, float _y0, float _x1, float _y1, float _r, uint32_t _abgr, float _fth = 1.0f)
	{
		float dx = _x1 - _x0;
		float dy = _y1 - _y0;
		float d = sqrtf(dx * dx + dy * dy);
		if (d > 0.0001f)
		{
			d = 1.0f / d;
			dx *= d;
			dy *= d;
		}

		float nx = dy;
		float ny = -dx;
		float verts[4 * 2];
		_r -= _fth;
		_r *= 0.5f;
		if (_r < 0.01f)
		{
			_r = 0.01f;
		}

		dx *= _r;
		dy *= _r;
		nx *= _r;
		ny *= _r;

		verts[0] = _x0 - dx - nx;
		verts[1] = _y0 - dy - ny;

		verts[2] = _x0 - dx + nx;
		verts[3] = _y0 - dy + ny;

		verts[4] = _x1 + dx + nx;
		verts[5] = _y1 + dy + ny;

		verts[6] = _x1 + dx - nx;
		verts[7] = _y1 + dy - ny;

		drawPolygon(verts, 4, _fth, _abgr);
	}

	void drawTriangle(int32_t _x, int32_t _y, int32_t _width, int32_t _height, int32_t _flags, uint32_t _abgr)
	{
		if (1 == _flags)
		{
			const float verts[3 * 2] =
			{
				(float)_x + 0.5f,                        (float)_y + 0.5f,
				(float)_x + 0.5f + (float)_width * 1.0f, (float)_y + 0.5f + (float)_height / 2.0f - 0.5f,
				(float)_x + 0.5f,                        (float)_y + 0.5f + (float)_height - 1.0f,
			};

			drawPolygon(verts, 3, 1.0f, _abgr);
		}
		else
		{
			const float verts[3 * 2] =
			{
				(float)_x + 0.5f,                               (float)_y + 0.5f + (float)_height - 1.0f,
				(float)_x + 0.5f + (float)_width / 2.0f - 0.5f, (float)_y + 0.5f,
				(float)_x + 0.5f + (float)_width - 1.0f,        (float)_y + 0.5f + (float)_height - 1.0f,
			};

			drawPolygon(verts, 3, 1.0f, _abgr);
		}
	}

	void getBakedQuad(stbtt_bakedchar* _chardata, int32_t char_index, float* _xpos, float* _ypos, stbtt_aligned_quad* _quad)
	{
		stbtt_bakedchar* b = _chardata + char_index;
		int32_t round_x = STBTT_ifloor(*_xpos + b->xoff);
		int32_t round_y = STBTT_ifloor(*_ypos + b->yoff);

		_quad->x0 = (float)round_x;
		_quad->y0 = (float)round_y;
		_quad->x1 = (float)round_x + b->x1 - b->x0;
		_quad->y1 = (float)round_y + b->y1 - b->y0;

		_quad->s0 = (b->x0 + m_halfTexel) * m_invTextureWidth;
		_quad->t0 = (b->y0 + m_halfTexel) * m_invTextureWidth;
		_quad->s1 = (b->x1 + m_halfTexel) * m_invTextureHeight;
		_quad->t1 = (b->y1 + m_halfTexel) * m_invTextureHeight;

		*_xpos += b->xadvance;
	}

	float getTextLength(stbtt_bakedchar* _chardata, const char* _text, uint32_t& _numVertices)
	{
		float xpos = 0;
		float len = 0;
		uint32_t numVertices = 0;

		while (*_text)
		{
			int32_t ch = (uint8_t)*_text;
			if (ch == '\t')
			{
				for (int32_t ii = 0; ii < 4; ++ii)
				{
					if (xpos < s_tabStops[ii])
					{
						xpos = s_tabStops[ii];
						break;
					}
				}
			}
			else if (ch >= ' '
				 &&  ch < 128)
			{
				stbtt_bakedchar* b = _chardata + ch - ' ';
				int32_t round_x = STBTT_ifloor( (xpos + b->xoff) + 0.5);
				len = round_x + b->x1 - b->x0 + 0.5f;
				xpos += b->xadvance;
				numVertices += 6;
			}

			++_text;
		}

		_numVertices = numVertices;

		return len;
	}

	void drawText(int32_t _x, int32_t _y, imguiTextAlign _align, const char* _text, uint32_t _abgr)
	{
		drawText( (float)_x, (float)_y, _text, _align, _abgr);
	}

	void drawText(float _x, float _y, const char* _text, imguiTextAlign _align, uint32_t _abgr)
	{
		if (!_text)
		{
			return;
		}

		uint32_t numVertices = 0;
		if (_align == IMGUI_ALIGN_CENTER)
		{
			_x -= getTextLength(m_cdata, _text, numVertices) / 2;
		}
		else if (_align == IMGUI_ALIGN_RIGHT)
		{
			_x -= getTextLength(m_cdata, _text, numVertices);
		}
		else // just count vertices
		{
			getTextLength(m_cdata, _text, numVertices);
		}

		if (bgfx::checkAvailTransientVertexBuffer(numVertices, PosColorUvVertex::ms_decl) )
		{
			bgfx::TransientVertexBuffer tvb;
			bgfx::allocTransientVertexBuffer(&tvb, numVertices, PosColorUvVertex::ms_decl);

			PosColorUvVertex* vertex = (PosColorUvVertex*)tvb.data;

			const float ox = _x;

			while (*_text)
			{
				int32_t ch = (uint8_t)*_text;
				if (ch == '\t')
				{
					for (int32_t i = 0; i < 4; ++i)
					{
						if (_x < s_tabStops[i] + ox)
						{
							_x = s_tabStops[i] + ox;
							break;
						}
					}
				}
				else if (ch >= ' '
					 &&  ch < 128)
				{
					stbtt_aligned_quad quad;
					getBakedQuad(m_cdata, ch - 32, &_x, &_y, &quad);

					vertex->m_x = quad.x0;
					vertex->m_y = quad.y0;
					vertex->m_u = quad.s0;
					vertex->m_v = quad.t0;
					vertex->m_abgr = _abgr;
					++vertex;

					vertex->m_x = quad.x1;
					vertex->m_y = quad.y1;
					vertex->m_u = quad.s1;
					vertex->m_v = quad.t1;
					vertex->m_abgr = _abgr;
					++vertex;

					vertex->m_x = quad.x1;
					vertex->m_y = quad.y0;
					vertex->m_u = quad.s1;
					vertex->m_v = quad.t0;
					vertex->m_abgr = _abgr;
					++vertex;

					vertex->m_x = quad.x0;
					vertex->m_y = quad.y0;
					vertex->m_u = quad.s0;
					vertex->m_v = quad.t0;
					vertex->m_abgr = _abgr;
					++vertex;

					vertex->m_x = quad.x0;
					vertex->m_y = quad.y1;
					vertex->m_u = quad.s0;
					vertex->m_v = quad.t1;
					vertex->m_abgr = _abgr;
					++vertex;

					vertex->m_x = quad.x1;
					vertex->m_y = quad.y1;
					vertex->m_u = quad.s1;
					vertex->m_v = quad.t1;
					vertex->m_abgr = _abgr;
					++vertex;
				}

				++_text;
			}

			bgfx::setTexture(0, u_texColor, m_fontTexture);
			bgfx::setVertexBuffer(&tvb);
			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
				);
			bgfx::setProgram(m_textureProgram);
			bgfx::submit(m_view);
		}
	}

	int32_t m_mx;
	int32_t m_my;
	int32_t m_scroll;
	uint32_t m_active;
	uint32_t m_hot;
	uint32_t m_hotToBe;
	int32_t m_dragX;
	int32_t m_dragY;
	float m_dragOrig;
	int32_t m_widgetX;
	int32_t m_widgetY;
	int32_t m_widgetW;
	bool m_left;
	bool m_leftPressed;
	bool m_leftReleased;
	bool m_isHot;
	bool m_isActive;
	bool m_wentActive;
	bool m_insideCurrentScroll;

	uint32_t m_areaId;
	uint32_t m_widgetId;

	float m_tempCoords[MAX_TEMP_COORDS * 2];
	float m_tempNormals[MAX_TEMP_COORDS * 2];

	float m_circleVerts[NUM_CIRCLE_VERTS * 2];

	int32_t m_scrollTop;
	int32_t m_scrollBottom;
	int32_t m_scrollRight;
	int32_t m_scrollAreaTop;
	int32_t* m_scrollVal;
	int32_t m_focusTop;
	int32_t m_focusBottom;
	uint32_t m_scrollId;
	bool m_insideScrollArea;

	stbtt_bakedchar m_cdata[96]; // ASCII 32..126 is 95 glyphs

	uint16_t m_textureWidth;
	uint16_t m_textureHeight;
	float m_invTextureWidth;
	float m_invTextureHeight;
	float m_halfTexel;

	uint8_t m_view;
	bgfx::UniformHandle u_texColor;
	bgfx::TextureHandle m_fontTexture;
	bgfx::ProgramHandle m_colorProgram;
	bgfx::ProgramHandle m_textureProgram;
};

static Imgui s_imgui;

bool imguiCreate(void* _data, uint32_t _size)
{
	return s_imgui.create(_data, _size);
}

void imguiDestroy()
{
	s_imgui.destroy();
}

void imguiBeginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, uint8_t _view)
{
	s_imgui.beginFrame(_mx, _my, _button, _scroll, _width, _height, _view);
}

void imguiEndFrame()
{
	s_imgui.endFrame();
}

bool imguiBeginScrollArea(const char* _name, int32_t _x, int32_t _y, int32_t _width, int32_t _height, int32_t* _scroll)
{
	return s_imgui.beginScrollArea(_name, _x, _y, _width, _height, _scroll);
}

void imguiEndScrollArea()
{
	return s_imgui.endScrollArea();
}

void imguiIndent()
{
	s_imgui.indent();
}

void imguiUnindent()
{
	s_imgui.unindent();
}

void imguiSeparator()
{
	s_imgui.separator();
}

void imguiSeparatorLine()
{
	s_imgui.separatorLine();
}

bool imguiButton(const char* _text, bool _enabled)
{
	return s_imgui.button(_text, _enabled);
}

bool imguiItem(const char* _text, bool _enabled)
{
	return s_imgui.item(_text, _enabled);
}

bool imguiCheck(const char* _text, bool _checked, bool _enabled)
{
	return s_imgui.check(_text, _checked, _enabled);
}

bool imguiCollapse(const char* _text, const char* _subtext, bool _checked, bool _enabled)
{
	return s_imgui.collapse(_text, _subtext, _checked, _enabled);
}

void imguiLabel(const char* _format, ...)
{
	va_list argList;
	va_start(argList, _format);
	s_imgui.labelVargs(_format, argList);
	va_end(argList);
}

void imguiValue(const char* _text)
{
	s_imgui.value(_text);
}

bool imguiSlider(const char* _text, float* _val, float _vmin, float _vmax, float _vinc, bool _enabled)
{
	return s_imgui.slider(_text, _val, _vmin, _vmax, _vinc, _enabled);
}

void imguiDrawText(int32_t _x, int32_t _y, imguiTextAlign _align, const char* _text, uint32_t _argb)
{
	s_imgui.drawText(_x, _y, _align, _text, _argb);
}

void imguiDrawLine(float _x0, float _y0, float _x1, float _y1, float _r, uint32_t _argb)
{
	s_imgui.drawLine(_x0, _y0, _x1, _y1, _r, _argb);
}

void imguiDrawRoundedRect(float _x, float _y, float _width, float _height, float _r, uint32_t _argb)
{
	s_imgui.drawRoundedRect(_x, _y, _width, _height, _r, _argb);
}

void imguiDrawRect(float _x, float _y, float _width, float _height, uint32_t _argb)
{
	s_imgui.drawRect(_x, _y, _width, _height, _argb);
}
