/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
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
#include <bx/fpumath.h>
#include <bx/handlealloc.h>

#include "../entry/dbg.h"
#include "imgui.h"
#include "../nanovg/nanovg.h"

#include "vs_imgui_color.bin.h"
#include "fs_imgui_color.bin.h"
#include "vs_imgui_texture.bin.h"
#include "fs_imgui_texture.bin.h"
#include "vs_imgui_image.bin.h"
#include "fs_imgui_image.bin.h"
#include "fs_imgui_image_swizz.bin.h"

#define USE_NANOVG_FONT 0

#define IMGUI_CONFIG_MAX_FONTS 20

#define MAX_TEMP_COORDS 100
#define NUM_CIRCLE_VERTS (8 * 4)

static const int32_t BUTTON_HEIGHT = 20;
static const int32_t SLIDER_HEIGHT = 20;
static const int32_t SLIDER_MARKER_WIDTH = 10;
static const int32_t CHECK_SIZE = 8;
static const int32_t DEFAULT_SPACING = 4;
static const int32_t TEXT_HEIGHT = 8;
static const int32_t SCROLL_AREA_PADDING = 6;
static const int32_t AREA_HEADER = 20;
static const int32_t COLOR_WHEEL_PADDING = 60;
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

namespace
{
	float sign(float px, float py, float ax, float ay, float bx, float by)
	{
		return (px - bx) * (ay - by) - (ax - bx) * (py - by);
	}

	bool pointInTriangle(float px, float py, float ax, float ay, float bx, float by, float cx, float cy)
	{
		const bool b1 = sign(px, py, ax, ay, bx, by) < 0.0f;
		const bool b2 = sign(px, py, bx, by, cx, cy) < 0.0f;
		const bool b3 = sign(px, py, cx, cy, ax, ay) < 0.0f;

		return ( (b1 == b2) && (b2 == b3) );
	}

	void closestPointOnLine(float& ox, float &oy, float px, float py, float ax, float ay, float bx, float by)
	{
		float dx = px - ax;
		float dy = py - ay;

		float lx = bx - ax;
		float ly = by - ay;

		float len = sqrtf(lx*lx+ly*ly);

		// Normalize.
		float invLen = 1.0f/len;
		lx*=invLen;
		ly*=invLen;

		float dot = (dx*lx + dy*ly);

		if (dot < 0.0f)
		{
			ox = ax;
			oy = ay;
		}
		else if (dot > len)
		{
			ox = bx;
			oy = by;
		}
		else
		{
			ox = ax + lx*dot;
			oy = ay + ly*dot;
		}
	}

	void closestPointOnTriangle(float& ox, float &oy, float px, float py, float ax, float ay, float bx, float by, float cx, float cy)
	{
		float abx, aby;
		float bcx, bcy;
		float cax, cay;
		closestPointOnLine(abx, aby, px, py, ax, ay, bx, by);
		closestPointOnLine(bcx, bcy, px, py, bx, by, cx, cy);
		closestPointOnLine(cax, cay, px, py, cx, cy, ax, ay);

		const float pabx = px - abx;
		const float paby = py - aby;
		const float pbcx = px - bcx;
		const float pbcy = py - bcy;
		const float pcax = px - cax;
		const float pcay = py - cay;

		const float lab = sqrtf(pabx*pabx+paby*paby);
		const float lbc = sqrtf(pbcx*pbcx+pbcy*pbcy);
		const float lca = sqrtf(pcax*pcax+pcay*pcay);

		const float m = bx::fmin3(lab, lbc, lca);
		if (m == lab)
		{
			ox = abx;
			oy = aby;
		}
		else if (m == lbc)
		{
			ox = bcx;
			oy = bcy;
		}
		else// if (m == lca).
		{
			ox = cax;
			oy = cay;
		}
	}

	inline float vec2Dot(const float* __restrict _a, const float* __restrict _b)
	{
		return _a[0]*_b[0] + _a[1]*_b[1];
	}

	void barycentric(float& _u, float& _v, float& _w
		, float _ax, float _ay
		, float _bx, float _by
		, float _cx, float _cy
		, float _px, float _py
		)
	{
		const float v0[2] = { _bx - _ax, _by - _ay };
		const float v1[2] = { _cx - _ax, _cy - _ay };
		const float v2[2] = { _px - _ax, _py - _ay };
		const float d00 = vec2Dot(v0, v0);
		const float d01 = vec2Dot(v0, v1);
		const float d11 = vec2Dot(v1, v1);
		const float d20 = vec2Dot(v2, v0);
		const float d21 = vec2Dot(v2, v1);
		const float denom = d00 * d11 - d01 * d01;
		_v = (d11 * d20 - d01 * d21) / denom;
		_w = (d00 * d21 - d01 * d20) / denom;
		_u = 1.0f - _v - _w;
	}

	struct PosColorVertex
	{
		float m_x;
		float m_y;
		uint32_t m_abgr;

		static void init()
		{
			ms_decl
				.begin()
				.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
				.end();
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
			ms_decl
				.begin()
				.add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
				.end();
		}

		static bgfx::VertexDecl ms_decl;
	};

	bgfx::VertexDecl PosColorUvVertex::ms_decl;

	struct PosUvVertex
	{
		float m_x;
		float m_y;
		float m_u;
		float m_v;

		static void init()
		{
			ms_decl
				.begin()
				.add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.end();
		}

		static bgfx::VertexDecl ms_decl;
	};

	bgfx::VertexDecl PosUvVertex::ms_decl;

} // namespace

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
		, m_enabledAreaIds(0)
		, m_scissor(UINT16_MAX)
		, m_scrollTop(0)
		, m_scrollHeight(0)
		, m_scrollRight(0)
		, m_scrollAreaTop(0)
		, m_scrollAreaWidth(0)
		, m_scrollAreaInnerWidth(0)
		, m_scrollAreaX(0)
		, m_scrollVal(NULL)
		, m_scrollId(0)
		, m_insideScrollArea(false)
		, m_textureWidth(512)
		, m_textureHeight(512)
		, m_halfTexel(0.0f)
		, m_nvg(NULL)
		, m_view(31)
		, m_viewWidth(0)
		, m_viewHeight(0)
		, m_currentFontIdx(0)
	{
		m_invTextureWidth  = 1.0f/m_textureWidth;
		m_invTextureHeight = 1.0f/m_textureHeight;

		u_imageLod.idx       = bgfx::invalidHandle;
		u_imageSwizzle.idx   = bgfx::invalidHandle;
		s_texColor.idx       = bgfx::invalidHandle;
		m_missingTexture.idx = bgfx::invalidHandle;

		m_colorProgram.idx      = bgfx::invalidHandle;
		m_textureProgram.idx    = bgfx::invalidHandle;
		m_imageProgram.idx      = bgfx::invalidHandle;
		m_imageSwizzProgram.idx = bgfx::invalidHandle;
	}

	ImguiFontHandle createFont(const void* _data, float _fontSize)
	{
#if !USE_NANOVG_FONT
		const ImguiFontHandle handle = { m_fontHandle.alloc() };
		const bgfx::Memory* mem = bgfx::alloc(m_textureWidth * m_textureHeight);
		stbtt_BakeFontBitmap( (uint8_t*)_data, 0, _fontSize, mem->data, m_textureWidth, m_textureHeight, 32, 96, m_fonts[handle.idx].m_cdata);
		m_fonts[handle.idx].m_texture = bgfx::createTexture2D(m_textureWidth, m_textureHeight, 1, bgfx::TextureFormat::R8, BGFX_TEXTURE_NONE, mem);
		m_fonts[handle.idx].m_size = _fontSize;
#else
		const ImguiFontHandle handle = { bgfx::invalidHandle };
#endif // !USE_NANOVG_FONT
		return handle;
	}

	void setFont(ImguiFontHandle _handle)
	{
		if (isValid(_handle) )
		{
			m_currentFontIdx = _handle.idx;
		}
	}

	bgfx::TextureHandle genMissingTexture(uint32_t _width, uint32_t _height, float _lineWidth = 0.02f)
	{
		const bgfx::Memory* mem = bgfx::alloc(_width*_height*4);
		uint32_t* bgra8 = (uint32_t*)mem->data;

		const float sx = 0.70710677f;
		const float cx = 0.70710677f;

		for (uint32_t yy = 0; yy < _height; ++yy)
		{
			for (uint32_t xx = 0; xx < _width; ++xx)
			{
				float px = xx / float(_width)  * 2.0f - 1.0f;
				float py = yy / float(_height) * 2.0f - 1.0f;

				float sum = bx::fpulse(px * cx - py * sx, _lineWidth, -_lineWidth)
						  + bx::fpulse(px * sx + py * cx, _lineWidth, -_lineWidth)
						  ;
				*bgra8++ = sum >= 1.0f ? 0xffff0000 : 0xffffffff;
			}
		}

		return bgfx::createTexture2D(_width, _height, 0, bgfx::TextureFormat::BGRA8, 0, mem);
	}

	ImguiFontHandle create(const void* _data, float _fontSize)
	{
		m_nvg = nvgCreate(512, 512, 1, m_view);
		nvgCreateFontMem(m_nvg, "default", (unsigned char*)_data, INT32_MAX, 0);
		nvgFontSize(m_nvg, _fontSize);
		nvgFontFace(m_nvg, "default");

		for (int32_t ii = 0; ii < NUM_CIRCLE_VERTS; ++ii)
		{
			float a = (float)ii / (float)NUM_CIRCLE_VERTS * (float)(M_PI * 2.0);
			m_circleVerts[ii * 2 + 0] = cosf(a);
			m_circleVerts[ii * 2 + 1] = sinf(a);
		}

		PosColorVertex::init();
		PosColorUvVertex::init();
		PosUvVertex::init();

		u_imageLod     = bgfx::createUniform("u_imageLod", bgfx::UniformType::Uniform1f);
		u_imageSwizzle = bgfx::createUniform("u_swizzle",  bgfx::UniformType::Uniform4fv);
		s_texColor     = bgfx::createUniform("s_texColor", bgfx::UniformType::Uniform1i);

		const bgfx::Memory* vs_imgui_color;
		const bgfx::Memory* fs_imgui_color;
		const bgfx::Memory* vs_imgui_texture;
		const bgfx::Memory* fs_imgui_texture;
		const bgfx::Memory* vs_imgui_image;
		const bgfx::Memory* fs_imgui_image;
		const bgfx::Memory* fs_imgui_image_swizz;

		switch (bgfx::getRendererType() )
		{
		case bgfx::RendererType::Direct3D9:
			vs_imgui_color       = bgfx::makeRef(vs_imgui_color_dx9, sizeof(vs_imgui_color_dx9) );
			fs_imgui_color       = bgfx::makeRef(fs_imgui_color_dx9, sizeof(fs_imgui_color_dx9) );
			vs_imgui_texture     = bgfx::makeRef(vs_imgui_texture_dx9, sizeof(vs_imgui_texture_dx9) );
			fs_imgui_texture     = bgfx::makeRef(fs_imgui_texture_dx9, sizeof(fs_imgui_texture_dx9) );
			vs_imgui_image       = bgfx::makeRef(vs_imgui_image_dx9, sizeof(vs_imgui_image_dx9) );
			fs_imgui_image       = bgfx::makeRef(fs_imgui_image_dx9, sizeof(fs_imgui_image_dx9) );
			fs_imgui_image_swizz = bgfx::makeRef(fs_imgui_image_swizz_dx9, sizeof(fs_imgui_image_swizz_dx9) );
			m_halfTexel = 0.5f;
			break;

		case bgfx::RendererType::Direct3D11:
			vs_imgui_color       = bgfx::makeRef(vs_imgui_color_dx11, sizeof(vs_imgui_color_dx11) );
			fs_imgui_color       = bgfx::makeRef(fs_imgui_color_dx11, sizeof(fs_imgui_color_dx11) );
			vs_imgui_texture     = bgfx::makeRef(vs_imgui_texture_dx11, sizeof(vs_imgui_texture_dx11) );
			fs_imgui_texture     = bgfx::makeRef(fs_imgui_texture_dx11, sizeof(fs_imgui_texture_dx11) );
			vs_imgui_image       = bgfx::makeRef(vs_imgui_image_dx11, sizeof(vs_imgui_image_dx11) );
			fs_imgui_image       = bgfx::makeRef(fs_imgui_image_dx11, sizeof(fs_imgui_image_dx11) );
			fs_imgui_image_swizz = bgfx::makeRef(fs_imgui_image_swizz_dx11, sizeof(fs_imgui_image_swizz_dx11) );
			break;

		default:
			vs_imgui_color       = bgfx::makeRef(vs_imgui_color_glsl, sizeof(vs_imgui_color_glsl) );
			fs_imgui_color       = bgfx::makeRef(fs_imgui_color_glsl, sizeof(fs_imgui_color_glsl) );
			vs_imgui_texture     = bgfx::makeRef(vs_imgui_texture_glsl, sizeof(vs_imgui_texture_glsl) );
			fs_imgui_texture     = bgfx::makeRef(fs_imgui_texture_glsl, sizeof(fs_imgui_texture_glsl) );
			vs_imgui_image       = bgfx::makeRef(vs_imgui_image_glsl, sizeof(vs_imgui_image_glsl) );
			fs_imgui_image       = bgfx::makeRef(fs_imgui_image_glsl, sizeof(fs_imgui_image_glsl) );
			fs_imgui_image_swizz = bgfx::makeRef(fs_imgui_image_swizz_glsl, sizeof(fs_imgui_image_swizz_glsl) );
			break;
		}

		bgfx::ShaderHandle vsh;
		bgfx::ShaderHandle fsh;

		vsh = bgfx::createShader(vs_imgui_color);
		fsh = bgfx::createShader(fs_imgui_color);
		m_colorProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(vsh);
		bgfx::destroyShader(fsh);

		vsh = bgfx::createShader(vs_imgui_texture);
		fsh = bgfx::createShader(fs_imgui_texture);
		m_textureProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(vsh);
		bgfx::destroyShader(fsh);

		vsh = bgfx::createShader(vs_imgui_image);
		fsh = bgfx::createShader(fs_imgui_image);
		m_imageProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(fsh);

		// Notice: using the same vsh.
		fsh = bgfx::createShader(fs_imgui_image_swizz);
		m_imageSwizzProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(fsh);
		bgfx::destroyShader(vsh);

		m_missingTexture = genMissingTexture(256, 256, 0.04f);

#if !USE_NANOVG_FONT
		const ImguiFontHandle handle = createFont(_data, _fontSize);
		m_currentFontIdx = handle.idx;
#else
		const ImguiFontHandle handle = { bgfx::invalidHandle };
#endif // !USE_NANOVG_FONT
		return handle;
	}

	void destroy()
	{
		bgfx::destroyUniform(u_imageLod);
		bgfx::destroyUniform(u_imageSwizzle);
		bgfx::destroyUniform(s_texColor);
#if !USE_NANOVG_FONT
		for (uint16_t ii = 0; ii < IMGUI_CONFIG_MAX_FONTS; ++ii)
		{
			if (bgfx::isValid(m_fonts[ii].m_texture) )
			{
				bgfx::destroyTexture(m_fonts[ii].m_texture);
			}
		}
#endif // !USE_NANOVG_FONT
		bgfx::destroyTexture(m_missingTexture);
		bgfx::destroyProgram(m_colorProgram);
		bgfx::destroyProgram(m_textureProgram);
		bgfx::destroyProgram(m_imageProgram);
		bgfx::destroyProgram(m_imageSwizzProgram);
		nvgDelete(m_nvg);
	}

	bool anyActive() const
	{
		return m_active != 0;
	}

	bool isActive(uint32_t _id) const
	{
		return m_active == _id;
	}

	bool isActiveInputField(uint32_t _id) const
	{
		return m_inputField == _id;
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

	bool isEnabled(uint8_t _areaId)
	{
		return (m_enabledAreaIds>>_areaId)&0x1;
	}

	void setEnabled(uint8_t _areaId)
	{
		m_enabledAreaIds |= (UINT64_C(1)<<_areaId);
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

	void clearActiveInputField()
	{
		m_inputField = 0;
	}

	void setActive(uint32_t _id)
	{
		m_active = _id;
		m_wentActive = true;
		m_inputField = 0;
	}

	void setActiveInputField(uint32_t _id)
	{
		m_inputField = _id;
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

	void inputLogic(uint32_t _id, bool _over)
	{
		if (!anyActive() )
		{
			if (_over)
			{
				setHot(_id);
			}

			if (isHot(_id)
			&& m_leftPressed)
			{
				// Toggle active input.
				if (isActiveInputField(_id))
				{
					clearActiveInputField();
				}
				else
				{
					setActiveInputField(_id);
				}
			}
		}

		if (isHot(_id) )
		{
			m_isHot = true;
		}

		if (m_leftPressed
		&&  !m_isHot
		&&  m_inputField != 0)
		{
			clearActiveInputField();
		}
	}

	void updateInput(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, char _inputChar)
	{
		bool left = (_button & IMGUI_MBUT_LEFT) != 0;

		m_mx = _mx;
		m_my = _my;
		m_leftPressed = !m_left && left;
		m_leftReleased = m_left && !left;
		m_left = left;
		m_scroll = _scroll;

		_inputChar = _inputChar & 0x7f; // ASCII of GTFO! :)
		m_lastChar = m_char;
		m_char = _inputChar;
	}

	void beginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, char _inputChar, uint8_t _view)
	{
		nvgBeginFrame(m_nvg, _width, _height, 1.0f, NVG_STRAIGHT_ALPHA);

		m_view = _view;
		m_viewWidth = _width;
		m_viewHeight = _height;
		bgfx::setViewSeq(_view, true);
		bgfx::setViewRect(_view, 0, 0, _width, _height);

		float proj[16];
		bx::mtxOrtho(proj, 0.0f, (float)_width, (float)_height, 0.0f, 0.0f, 1000.0f);
		bgfx::setViewTransform(_view, NULL, proj);

		updateInput(_mx, _my, _button, _scroll, _inputChar);

		m_hot = m_hotToBe;
		m_hotToBe = 0;

		m_wentActive = false;
		m_isActive = false;
		m_isHot = false;

		m_widgetX = 0;
		m_widgetY = 0;
		m_widgetW = 0;

		m_areaId = 0;
		m_widgetId = 0;
		m_enabledAreaIds = 0;
	}

	void endFrame()
	{
		clearInput();
		nvgEndFrame(m_nvg);
	}

	bool beginScrollArea(const char* _name, int32_t _x, int32_t _y, int32_t _width, int32_t _height, int32_t* _scroll, bool _enabled, int32_t _r)
	{
		m_areaId++;
		m_widgetId = 0;
		m_scrollId = (m_areaId << 8) | m_widgetId;

		if (_enabled)
		{
			setEnabled(m_areaId);
		}

		if (0 == _r)
		{
			drawRect( (float)_x
				    , (float)_y
				    , (float)_width  + 0.3f /*border fix for seamlessly joining two scroll areas*/
				    , (float)_height + 0.3f /*border fix for seamlessly joining two scroll areas*/
				    , imguiRGBA(0, 0, 0, 192)
				    );
		}
		else
		{
			drawRoundedRect( (float)_x
						   , (float)_y
						   , (float)_width
						   , (float)_height
						   , (float)_r
						   , imguiRGBA(0, 0, 0, 192)
						   );
		}

		const bool hasTitle = (NULL != _name && '\0' != _name[0]);

		int32_t header = 0;
		if (hasTitle)
		{
			drawText(_x + 10
				   , _y + 18
				   , ImguiTextAlign::Left
				   , _name
				   , imguiRGBA(255, 255, 255, 128)
				   );
			header = AREA_HEADER;
		}

		const int32_t contentX = _x + SCROLL_AREA_PADDING;
		const int32_t contentY = _y + SCROLL_AREA_PADDING + header;
		const int32_t contentWidth = _width - SCROLL_AREA_PADDING * 3;
		const int32_t contentHeight = _height - 2*SCROLL_AREA_PADDING - header;

		nvgScissor(m_nvg
				 , float(contentX)
				 , float(contentY-1)
				 , float(contentWidth)
				 , float(contentHeight+1)
				 );

		m_scissor = bgfx::setScissor(uint16_t(contentX)
								   , uint16_t(contentY-1)
								   , uint16_t(contentWidth)
								   , uint16_t(contentHeight+1)
								   );

		m_widgetX = contentX;
		m_widgetY = contentY + (*_scroll);
		m_widgetW = _width - SCROLL_AREA_PADDING * 4 - 2;

		m_scrollTop    = contentY;
		m_scrollHeight = contentHeight;
		m_scrollRight  = _x + _width - SCROLL_AREA_PADDING * 3;

		m_scrollVal = _scroll;
		m_scrollAreaX = _x;
		m_scrollAreaWidth = _width;
		m_scrollAreaInnerWidth = m_widgetW;
		m_scrollAreaTop = m_widgetY;

		m_insideScrollArea = inRect(_x, _y, _width, _height, false);
		m_insideCurrentScroll = m_insideScrollArea;

		return m_insideScrollArea;
	}

	void endScrollArea(int32_t _r)
	{
		// Disable scissoring.
		m_scissor = UINT16_MAX;
		nvgResetScissor(m_nvg);

		// Draw scroll bar
		int32_t xx     = m_scrollRight + SCROLL_AREA_PADDING / 2;
		int32_t yy     = m_scrollTop;
		int32_t width  = SCROLL_AREA_PADDING * 2;
		int32_t height = m_scrollHeight;

		int32_t stop = m_scrollAreaTop;
		int32_t sbot = m_widgetY - DEFAULT_SPACING;
		int32_t sh   = sbot - stop; // The scrollable area height.

		float barHeight = (float)height / (float)sh;

		// Handle m_scrollVal properly on variable scrollable area height.
		const int32_t diff = height - sh;
		if (diff < 0)
		{
			*m_scrollVal = (*m_scrollVal > diff) ? *m_scrollVal : diff; // m_scrollVal = max(diff, m_scrollVal).
		}
		else
		{
			*m_scrollVal = 0;
		}

		if (barHeight < 1.0f)
		{
			float barY = bx::fsaturate( (float)(yy - stop) / (float)sh);

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
				float uu = (float)(hy - yy) / (float)range;
				if (m_wentActive)
				{
					m_dragY = m_my;
					m_dragOrig = uu;
				}

				if (m_dragY != m_my)
				{
					uu = bx::fsaturate(m_dragOrig + (m_my - m_dragY) / (float)range);
					*m_scrollVal = (int)(uu * (height - sh) );
				}
			}

			// BG
			if (0 == _r)
			{
				drawRect( (float)xx
					, (float)yy
					, (float)width
					, (float)height
					, imguiRGBA(0, 0, 0, 196)
					);
			}
			else
			{
				drawRoundedRect( (float)xx
					, (float)yy
					, (float)width
					, (float)height
					, (float)_r
					, imguiRGBA(0, 0, 0, 196)
					);
			}

			// Bar
			if (isActive(hid) )
			{
				if (0 == _r)
				{
					drawRect( (float)hx
						, (float)hy
						, (float)hw
						, (float)hh
						, imguiRGBA(255, 196, 0, 196)
						);
				}
				else
				{
					drawRoundedRect( (float)hx
						, (float)hy
						, (float)hw
						, (float)hh
						, (float)_r
						, imguiRGBA(255, 196, 0, 196)
						);
				}
			}
			else
			{
				if (0 == _r)
				{
					drawRect( (float)hx
						, (float)hy
						, (float)hw
						, (float)hh
						, isHot(hid) ? imguiRGBA(255, 196, 0, 96) : imguiRGBA(255, 255, 255, 64)
						);
				}
				else
				{
					drawRoundedRect( (float)hx
						, (float)hy
						, (float)hw
						, (float)hh
						, (float)_r
						, isHot(hid) ? imguiRGBA(255, 196, 0, 96) : imguiRGBA(255, 255, 255, 64)
						);
				}
			}

			// Handle mouse scrolling.
			if (m_insideScrollArea) // && !anyActive() )
			{
				if (m_scroll)
				{
					*m_scrollVal += bx::uint32_clamp(20 * m_scroll, 0, sh - height);
				}
			}
		}

		m_insideCurrentScroll = false;
	}

	bool button(const char* _text, bool _enabled, uint32_t _rgb0, int32_t _r)
	{
		m_widgetId++;
		uint16_t id = (m_areaId << 8) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = BUTTON_HEIGHT;
		m_widgetY += BUTTON_HEIGHT + DEFAULT_SPACING;

		bool enabled = _enabled && isEnabled(m_areaId);
		bool over = enabled	&& inRect(xx, yy, width, height);
		bool res = buttonLogic(id, over);

		const uint32_t rgb0 = _rgb0&0x00ffffff;

		if (0 == _r)
		{
			drawRect( (float)xx
				, (float)yy
				, (float)width
				, (float)height
				, rgb0 | imguiRGBA(0, 0, 0, isActive(id) ? 196 : 96)
				);
		}
		else
		{
			drawRoundedRect( (float)xx
				, (float)yy
				, (float)width
				, (float)height
				, (float)_r
				, rgb0 | imguiRGBA(0, 0, 0, isActive(id) ? 196 : 96)
				);
		}

		if (enabled)
		{
			drawText(xx + BUTTON_HEIGHT / 2
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Left
				, _text
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + BUTTON_HEIGHT / 2
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Left
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		return res;
	}

	bool item(const char* _text, bool _enabled)
	{
		m_widgetId++;
		uint16_t id = (m_areaId << 8) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = BUTTON_HEIGHT;
		m_widgetY += BUTTON_HEIGHT + DEFAULT_SPACING;

		bool enabled = _enabled && isEnabled(m_areaId);
		bool over = enabled && inRect(xx, yy, width, height);
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

		if (enabled)
		{
			drawText(xx + BUTTON_HEIGHT / 2
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Left
				, _text
				, imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + BUTTON_HEIGHT / 2
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Left
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		return res;
	}

	bool check(const char* _text, bool _checked, bool _enabled)
	{
		m_widgetId++;
		uint16_t id = (m_areaId << 8) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = BUTTON_HEIGHT;
		m_widgetY += BUTTON_HEIGHT + DEFAULT_SPACING;

		bool enabled = _enabled && isEnabled(m_areaId);
		bool over = enabled && inRect(xx, yy, width, height);
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
			if (enabled)
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

		if (enabled)
		{
			drawText(xx + BUTTON_HEIGHT
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Left
				, _text
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + BUTTON_HEIGHT
				, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Left
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		return res;
	}

	void input(const char* _label, char* _str, uint32_t _len, bool _enabled, int32_t _r)
	{
		m_widgetId++;
		const uint16_t id = (m_areaId << 8) | m_widgetId;
		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		m_widgetY += BUTTON_HEIGHT + DEFAULT_SPACING;

		const bool drawLabel = (NULL != _label && _label[0] != '\0');

		if (drawLabel)
		{
			drawText(xx
				   , yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
				   , ImguiTextAlign::Left
				   , _label
				   , imguiRGBA(255, 255, 255, 200)
				   );
		}

		// Handle input.
		if (isActiveInputField(id) )
		{
			const size_t cursor = size_t(strlen(_str));

			if (m_char == 0x08) //backspace
			{
				_str[cursor-1] = '\0';
			}
			else if (m_char == 0x0d || m_char == 0x1b) //enter or escape
			{
				clearActiveInputField();
			}
			else if (cursor < _len-1
				 &&  0 != m_char)
			{
				_str[cursor] = m_char;
				_str[cursor+1] = '\0';
			}
		}

		// Draw input area.
		int32_t height = BUTTON_HEIGHT;
		int32_t width = m_widgetW;
		if (drawLabel)
		{
			uint32_t numVertices = 0; //unused
			const int32_t labelWidth = int32_t(getTextLength(m_fonts[m_currentFontIdx].m_cdata, _label, numVertices));
			xx    += (labelWidth + 6);
			width -= (labelWidth + 6);
		}
		const bool enabled = _enabled && isEnabled(m_areaId);
		const bool over = enabled && inRect(xx, yy, width, height);
		inputLogic(id, over);

		if (0 == _r)
		{
			drawRect( (float)xx
				, (float)yy
				, (float)width
				, (float)height
				, isActiveInputField(id)?imguiRGBA(255,196,0,255):imguiRGBA(128,128,128,96)
				);
		}
		else
		{
			drawRoundedRect( (float)xx
				, (float)yy
				, (float)width
				, (float)height
				, (float)_r
				, isActiveInputField(id)?imguiRGBA(255,196,0,255):imguiRGBA(128,128,128,96)
				);
		}

		if (isActiveInputField(id) )
		{
			drawText(xx + 6
					, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
					, ImguiTextAlign::Left
					, _str
					, imguiRGBA(0, 0, 0, 255)
					);
		}
		else
		{
			drawText(xx + 6
					, yy + BUTTON_HEIGHT / 2 + TEXT_HEIGHT / 2
					, ImguiTextAlign::Left
					, _str
					, isHot(id) ? imguiRGBA(255,196,0,255) : imguiRGBA(255,255,255,255)
					);
		}
	}

	uint8_t tabs(uint8_t _selected, bool _enabled, int32_t _height, int32_t _r, va_list _argList)
	{
		uint8_t count;
		const char* titles[16];
		const char* str = va_arg(_argList, const char*);
		for (count = 0; str != NULL || count >= 16; ++count, str = va_arg(_argList, const char*) )
		{
			titles[count] = str;
		}

		const int32_t yy = m_widgetY;
		m_widgetY += _height + DEFAULT_SPACING;

		uint8_t selected = _selected;
		const int32_t tabWidth     = m_widgetW / count;
		const int32_t tabWidthHalf = m_widgetW / (count*2);
		const int32_t textY = yy + _height/2 + int32_t(m_fonts[m_currentFontIdx].m_size)/2 - 2;

		if (0 == _r)
		{
			drawRect( (float)m_widgetX
				    , (float)yy
				    , (float)m_widgetW
				    , (float)_height
				    , imguiRGBA(128, 128, 128, 96)
				    );
		}
		else
		{
			drawRoundedRect( (float)m_widgetX
						   , (float)yy
						   , (float)m_widgetW
						   , (float)_height
						   , (float)_r
						   , imguiRGBA(128, 128, 128, 96)
						   );
		}

		for (uint8_t ii = 0; ii < count; ++ii)
		{
			m_widgetId++;
			const uint16_t id = (m_areaId << 8) | m_widgetId;

			int32_t xx = m_widgetX + ii*tabWidth;
			int32_t textX = xx + tabWidthHalf;

			const bool enabled = _enabled && isEnabled(m_areaId);
			const bool over = enabled && inRect(xx, yy, tabWidth, _height);
			const bool res = buttonLogic(id, over);

			if (res)
			{
				selected = ii;
			}

			uint32_t textColor;
			if (ii == selected)
			{
				textColor = enabled?imguiRGBA(0,0,0,255):imguiRGBA(255,255,255,100);

				if (0 == _r)
				{
					drawRect( (float)xx
						    , (float)yy
						    , (float)tabWidth
						    , (float)_height
						    , enabled?imguiRGBA(255,196,0,200):imguiRGBA(128,128,128,96)
						    );
				}
				else
				{
					drawRoundedRect( (float)xx
								   , (float)yy
								   , (float)tabWidth
								   , (float)_height
								   , (float)_r
								   , enabled?imguiRGBA(255,196,0,200):imguiRGBA(128,128,128,96)
								   );
				}
			}
			else
			{
				textColor = isHot(id) ? imguiRGBA(255, 196, 0, enabled?255:100) : imguiRGBA(255, 255, 255, enabled?200:100);
			}

			drawText(textX
				   , textY
				   , ImguiTextAlign::Center
				   , titles[ii]
				   , textColor
				   );
		}

		return selected;
	}

	void image(bgfx::TextureHandle _image, float _lod, int32_t _width, int32_t _height, ImguiImageAlign::Enum _align)
	{
		int32_t xx;
		if (ImguiImageAlign::Left == _align)
		{
			xx = m_scrollAreaX + SCROLL_AREA_PADDING;
		}
		else if (ImguiImageAlign::LeftIndented == _align)
		{
			xx = m_widgetX;
		}
		else if (ImguiImageAlign::Center == _align)
		{
			xx = m_scrollAreaX + (m_scrollAreaInnerWidth-_width)/2;
		}
		else if (ImguiImageAlign::CenterIndented == _align)
		{
			xx = (m_widgetX + m_scrollAreaInnerWidth + m_scrollAreaX - _width)/2;
		}
		else //if (ImguiImageAlign::Right == _align).
		{
			xx = m_scrollAreaX + m_scrollAreaInnerWidth - _width;
		}

		const int32_t yy = m_widgetY;
		m_widgetY += _height + DEFAULT_SPACING;

		screenQuad(xx, yy, _width, _height);
		bgfx::setUniform(u_imageLod, &_lod);
		bgfx::setTexture(0, s_texColor, bgfx::isValid(_image) ? _image : m_missingTexture);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		bgfx::setProgram(m_imageProgram);
		bgfx::setScissor(m_scissor);
		bgfx::submit(m_view);
	}

	void image(bgfx::TextureHandle _image, float _lod, float _width, float _aspect, ImguiImageAlign::Enum _align)
	{
		const float width = _width*float(m_scrollAreaInnerWidth);
		const float height = width/_aspect;

		image(_image, _lod, int32_t(width), int32_t(height), _align);
	}

	void imageChannel(bgfx::TextureHandle _image, uint8_t _channel, float _lod, int32_t _width, int32_t _height, ImguiImageAlign::Enum _align)
	{
		BX_CHECK(_channel < 4, "Channel param must be from 0 to 3!");

		int32_t xx;
		if (ImguiImageAlign::Left == _align)
		{
			xx = m_scrollAreaX + SCROLL_AREA_PADDING;
		}
		else if (ImguiImageAlign::LeftIndented == _align)
		{
			xx = m_widgetX;
		}
		else if (ImguiImageAlign::Center == _align)
		{
			xx = m_scrollAreaX + (m_scrollAreaInnerWidth-_width)/2;
		}
		else if (ImguiImageAlign::CenterIndented == _align)
		{
			xx = (m_widgetX + m_scrollAreaInnerWidth + m_scrollAreaX - _width)/2;
		}
		else //if (ImguiImageAlign::Right == _align).
		{
			xx = m_scrollAreaX + m_scrollAreaInnerWidth - _width;
		}

		const int32_t yy = m_widgetY;
		m_widgetY += _height + DEFAULT_SPACING;

		screenQuad(xx, yy, _width, _height);
		bgfx::setUniform(u_imageLod, &_lod);

		float swizz[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		swizz[_channel] = 1.0f;
		bgfx::setUniform(u_imageSwizzle, swizz);

		bgfx::setTexture(0, s_texColor, bgfx::isValid(_image) ? _image : m_missingTexture);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		bgfx::setProgram(m_imageSwizzProgram);
		bgfx::setScissor(m_scissor);
		bgfx::submit(m_view);
	}

	void imageChannel(bgfx::TextureHandle _image, uint8_t _channel, float _lod, float _width, float _aspect, ImguiImageAlign::Enum _align)
	{
		const float width = _width*float(m_scrollAreaInnerWidth);
		const float height = width/_aspect;

		imageChannel(_image, _channel, _lod, int32_t(width), int32_t(height), _align);
	}

	bool collapse(const char* _text, const char* _subtext, bool _checked, bool _enabled)
	{
		m_widgetId++;
		uint16_t id = (m_areaId << 8) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = BUTTON_HEIGHT;
		m_widgetY += BUTTON_HEIGHT + DEFAULT_SPACING;

		const int32_t cx = xx + BUTTON_HEIGHT/2 - CHECK_SIZE/2;
		const int32_t cy = yy + BUTTON_HEIGHT/2 - CHECK_SIZE/2 + DEFAULT_SPACING/2;

		const int32_t textY = yy + BUTTON_HEIGHT/2 + TEXT_HEIGHT/2 + DEFAULT_SPACING/2;

		bool enabled = _enabled && isEnabled(m_areaId);
		bool over = enabled && inRect(xx, yy, width, height);
		bool res = buttonLogic(id, over);

		if (_checked)
		{
			drawTriangle(cx
				, cy
				, CHECK_SIZE
				, CHECK_SIZE
				, TriangleOrientation::Up
				, imguiRGBA(255, 255, 255, isActive(id) ? 255 : 200)
				);
		}
		else
		{
			drawTriangle(cx
				, cy
				, CHECK_SIZE
				, CHECK_SIZE
				, TriangleOrientation::Right
				, imguiRGBA(255, 255, 255, isActive(id) ? 255 : 200)
				);
		}

		if (enabled)
		{
			drawText(xx + BUTTON_HEIGHT
				, textY
				, ImguiTextAlign::Left
				, _text
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + BUTTON_HEIGHT
				, textY
				, ImguiTextAlign::Left
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		if (_subtext)
		{
			drawText(xx + width - BUTTON_HEIGHT / 2
				, textY
				, ImguiTextAlign::Right
				, _subtext
				, imguiRGBA(255, 255, 255, 128)
				);
		}

		return res;
	}

	bool borderButton(ImguiBorder::Enum _border, bool _checked, bool _enabled)
	{
		m_widgetId++;
		uint16_t id = (m_areaId << 8) | m_widgetId;

		const int32_t triSize = 12;
		const int32_t borderSize = 15;

		int32_t xx;
		int32_t yy;
		int32_t width;
		int32_t height;
		int32_t triX;
		int32_t triY;
		TriangleOrientation::Enum orientation;

		if (ImguiBorder::Left == _border)
		{
			xx = -borderSize;
			yy = 0;
			width = 2*borderSize;
			height = m_viewHeight;
			triX = 0;
			triY = (m_viewHeight-triSize)/2;
			orientation = _checked ? TriangleOrientation::Left : TriangleOrientation::Right;
		}
		else if (ImguiBorder::Right == _border)
		{
			xx = m_viewWidth - borderSize;
			yy = 0;
			width = 2*borderSize;
			height = m_viewHeight;
			triX = m_viewWidth - triSize - 2;
			triY = (m_viewHeight-width)/2;
			orientation = _checked ? TriangleOrientation::Right : TriangleOrientation::Left;
		}
		else if (ImguiBorder::Top == _border)
		{
			xx = 0;
			yy = -borderSize;
			width = m_viewWidth;
			height = 2*borderSize;
			triX = (m_viewWidth-triSize)/2;
			triY = 0;
			orientation = _checked ? TriangleOrientation::Up : TriangleOrientation::Down;
		}
		else //if (ImguiBorder::Bottom == _border).
		{
			xx = 0;
			yy = m_viewHeight - borderSize;
			width = m_viewWidth;
			height = 2*borderSize;
			triX = (m_viewWidth-triSize)/2;
			triY = m_viewHeight-triSize;
			orientation = _checked ? TriangleOrientation::Down : TriangleOrientation::Up;
		}

		const bool over = _enabled && inRect(xx, yy, width, height, false);
		const bool res = buttonLogic(id, over);

		drawRoundedRect( (float)xx
					   , (float)yy
					   , (float)width
					   , (float)height
					   , 0.0f
					   , isActive(id) ? imguiRGBA(23, 23, 23, 192) : imguiRGBA(0, 0, 0, 222)
					   );

		drawTriangle( triX
					, triY
					, triSize
					, triSize
					, orientation
					, isHot(id) ? imguiRGBA(255, 196, 0, 222) : imguiRGBA(255, 255, 255, 192)
					);

		return res;
	}

	void labelVargs(const char* _format, va_list _argList, bool _enabled)
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
			, yy + BUTTON_HEIGHT/2 + TEXT_HEIGHT/2
			, ImguiTextAlign::Left
			, out
			, _enabled?imguiRGBA(255, 255, 255, 255):imguiRGBA(255, 255, 255, 128)
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
			, ImguiTextAlign::Right
			, _text
			, imguiRGBA(255, 255, 255, 200)
			);
	}

	bool slider(const char* _text, float& _val, float _vmin, float _vmax, float _vinc, bool _enabled)
	{
		m_widgetId++;
		uint16_t id = (m_areaId << 8) | m_widgetId;

		int32_t xx = m_widgetX;
		int32_t yy = m_widgetY;
		int32_t width = m_widgetW;
		int32_t height = SLIDER_HEIGHT;
		m_widgetY += SLIDER_HEIGHT + DEFAULT_SPACING;

		drawRoundedRect( (float)xx, (float)yy, (float)width, (float)height, 4.0f, imguiRGBA(0, 0, 0, 128) );

		const int32_t range = width - SLIDER_MARKER_WIDTH;

		float uu = bx::fsaturate( (_val - _vmin) / (_vmax - _vmin) );
		int32_t m = (int)(uu * range);

		bool enabled = _enabled && isEnabled(m_areaId);
		bool over = enabled && inRect(xx + m, yy, SLIDER_MARKER_WIDTH, SLIDER_HEIGHT);
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
				uu = bx::fsaturate(m_dragOrig + (float)(m_mx - m_dragX) / (float)range);

				_val = _vmin + uu * (_vmax - _vmin);
				_val = floorf(_val / _vinc + 0.5f) * _vinc; // Snap to vinc
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
		bx::snprintf(msg, 128, fmt, _val);

		if (enabled)
		{
			drawText(xx + SLIDER_HEIGHT / 2
				, yy + SLIDER_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Left
				, _text
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);

			drawText(xx + width - SLIDER_HEIGHT / 2
				, yy + SLIDER_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Right
				, msg
				, isHot(id) ? imguiRGBA(255, 196, 0, 255) : imguiRGBA(255, 255, 255, 200)
				);
		}
		else
		{
			drawText(xx + SLIDER_HEIGHT / 2
				, yy + SLIDER_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Left
				, _text
				, imguiRGBA(128, 128, 128, 200)
				);

			drawText(xx + width - SLIDER_HEIGHT / 2
				, yy + SLIDER_HEIGHT / 2 + TEXT_HEIGHT / 2
				, ImguiTextAlign::Right
				, msg
				, imguiRGBA(128, 128, 128, 200)
				);
		}

		return res || valChanged;
	}

	void indent(uint16_t _width)
	{
		m_widgetX += _width;
		m_widgetW -= _width;
	}

	void unindent(uint16_t _width)
	{
		m_widgetX -= _width;
		m_widgetW += _width;
	}

	void separator(uint16_t _height)
	{
		m_widgetY += _height;
	}

	void separatorLine(uint16_t _height)
	{
		const int32_t rectWidth = m_widgetW;
		const int32_t rectHeight = 1;
		const int32_t xx = m_widgetX;
		const int32_t yy = m_widgetY + _height/2 - rectHeight;
		m_widgetY += _height;

		drawRect( (float)xx
				, (float)yy
				, (float)rectWidth
				, (float)rectHeight
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
			bgfx::setScissor(m_scissor);
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

	struct TriangleOrientation
	{
		enum Enum
		{
			Left,
			Right,
			Up,
			Down,
		};
	};

	void drawTriangle(int32_t _x, int32_t _y, int32_t _width, int32_t _height, TriangleOrientation::Enum _orientation, uint32_t _abgr)
	{
		if (TriangleOrientation::Left == _orientation)
		{
			const float verts[3 * 2] =
			{
				(float)_x + 0.5f + (float)_width * 1.0f, (float)_y + 0.5f,
				(float)_x + 0.5f,                        (float)_y + 0.5f + (float)_height / 2.0f - 0.5f,
				(float)_x + 0.5f + (float)_width * 1.0f, (float)_y + 0.5f + (float)_height - 1.0f,
			};

			drawPolygon(verts, 3, 1.0f, _abgr);
		}
		else if (TriangleOrientation::Right == _orientation)
		{
			const float verts[3 * 2] =
			{
				(float)_x + 0.5f,                        (float)_y + 0.5f,
				(float)_x + 0.5f + (float)_width * 1.0f, (float)_y + 0.5f + (float)_height / 2.0f - 0.5f,
				(float)_x + 0.5f,                        (float)_y + 0.5f + (float)_height - 1.0f,
			};

			drawPolygon(verts, 3, 1.0f, _abgr);
		}
		else if (TriangleOrientation::Up == _orientation)
		{
			const float verts[3 * 2] =
			{
				(float)_x + 0.5f,                               (float)_y + 0.5f + (float)_height - 1.0f,
				(float)_x + 0.5f + (float)_width / 2.0f - 0.5f, (float)_y + 0.5f,
				(float)_x + 0.5f + (float)_width - 1.0f,        (float)_y + 0.5f + (float)_height - 1.0f,
			};

			drawPolygon(verts, 3, 1.0f, _abgr);
		}
		else //if (TriangleOrientation::Down == _orientation).
		{
			const float verts[3 * 2] =
			{
				(float)_x + 0.5f,                               (float)_y + 0.5f,
				(float)_x + 0.5f + (float)_width / 2.0f - 0.5f, (float)_y + 0.5f + (float)_height - 1.0f,
				(float)_x + 0.5f + (float)_width - 1.0f,        (float)_y + 0.5f,
			};

			drawPolygon(verts, 3, 1.0f, _abgr);
		}
	}

#if !USE_NANOVG_FONT
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
#endif // !USE_NANOVG_FONT

	void drawText(int32_t _x, int32_t _y, ImguiTextAlign::Enum _align, const char* _text, uint32_t _abgr)
	{
		drawText( (float)_x, (float)_y, _text, _align, _abgr);
	}

	void drawText(float _x, float _y, const char* _text, ImguiTextAlign::Enum _align, uint32_t _abgr)
	{
		if (NULL == _text
		||  '\0' == _text[0])
		{
			return;
		}

#if USE_NANOVG_FONT
		static uint32_t textAlign[ImguiTextAlign::Count] =
		{
			NVG_ALIGN_LEFT,
			NVG_ALIGN_CENTER,
			NVG_ALIGN_RIGHT,
		};

		nvgTextAlign(m_nvg, textAlign[_align]);

		nvgFontBlur(m_nvg, 0.0f);
		nvgFillColor(m_nvg, nvgRGBAu(_abgr) );
		nvgText(m_nvg, _x, _y, _text, NULL);
#else
		uint32_t numVertices = 0;
		if (_align == ImguiTextAlign::Center)
		{
			_x -= getTextLength(m_fonts[m_currentFontIdx].m_cdata, _text, numVertices) / 2;
		}
		else if (_align == ImguiTextAlign::Right)
		{
			_x -= getTextLength(m_fonts[m_currentFontIdx].m_cdata, _text, numVertices);
		}
		else // just count vertices
		{
			getTextLength(m_fonts[m_currentFontIdx].m_cdata, _text, numVertices);
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
					getBakedQuad(m_fonts[m_currentFontIdx].m_cdata, ch - 32, &_x, &_y, &quad);

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

			bgfx::setTexture(0, s_texColor, m_fonts[m_currentFontIdx].m_texture);
			bgfx::setVertexBuffer(&tvb);
			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
				);
			bgfx::setProgram(m_textureProgram);
			bgfx::setScissor(m_scissor);
			bgfx::submit(m_view);
		}
#endif // USE_NANOVG_FONT
	}

	void screenQuad(int32_t _x, int32_t _y, int32_t _width, uint32_t _height)
	{
		if (bgfx::checkAvailTransientVertexBuffer(6, PosUvVertex::ms_decl) )
		{
			bgfx::TransientVertexBuffer vb;
			bgfx::allocTransientVertexBuffer(&vb, 6, PosUvVertex::ms_decl);
			PosUvVertex* vertex = (PosUvVertex*)vb.data;

			const float widthf  = float(_width);
			const float heightf = float(_height);

			const float minx = float(_x);
			const float miny = float(_y);
			const float maxx = minx+widthf;
			const float maxy = miny+heightf;

			const float texelHalfW = m_halfTexel/widthf;
			const float texelHalfH = m_halfTexel/heightf;
			const float minu = texelHalfW;
			const float maxu = 1.0f - texelHalfW;
			const float minv = texelHalfH;
			const float maxv = texelHalfH + 1.0f;

			vertex[0].m_x = minx;
			vertex[0].m_y = miny;
			vertex[0].m_u = minu;
			vertex[0].m_v = minv;

			vertex[1].m_x = maxx;
			vertex[1].m_y = miny;
			vertex[1].m_u = maxu;
			vertex[1].m_v = minv;

			vertex[2].m_x = maxx;
			vertex[2].m_y = maxy;
			vertex[2].m_u = maxu;
			vertex[2].m_v = maxv;

			vertex[3].m_x = maxx;
			vertex[3].m_y = maxy;
			vertex[3].m_u = maxu;
			vertex[3].m_v = maxv;

			vertex[4].m_x = minx;
			vertex[4].m_y = maxy;
			vertex[4].m_u = minu;
			vertex[4].m_v = maxv;

			vertex[5].m_x = minx;
			vertex[5].m_y = miny;
			vertex[5].m_u = minu;
			vertex[5].m_v = minv;

			bgfx::setVertexBuffer(&vb);
		}
	}

	void colorWheelWidget(float _rgb[3], bool _respectIndentation, bool _enabled)
	{
		m_widgetId++;
		const uint16_t wheelId = (m_areaId << 8) | m_widgetId;
		m_widgetId++;
		const uint16_t triangleId = (m_areaId << 8) | m_widgetId;

		const int32_t height = m_scrollAreaWidth - COLOR_WHEEL_PADDING;
		const float heightf = float(height);
		const float widthf = float(m_scrollAreaWidth - COLOR_WHEEL_PADDING);
		const float xx = float( (_respectIndentation ? m_widgetX-SCROLL_AREA_PADDING : m_scrollAreaX) + COLOR_WHEEL_PADDING/2);
		const float yy = float(m_widgetY);

		m_widgetY += height + DEFAULT_SPACING;

		const float ro = (widthf < heightf ? widthf : heightf) * 0.5f - 5.0f; // radiusOuter.
		const float rd = 20.0f; // radiusDelta.
		const float ri = ro - rd; // radiusInner.
		const float aeps = 0.5f / ro; // Half a pixel arc length in radians (2pi cancels out).
		const float center[2] = { xx + widthf*0.5f, yy + heightf*0.5f };
		const float cmx = float(m_mx) - center[0];
		const float cmy = float(m_my) - center[1];

		const float aa[2] = { ri - 6.0f, 0.0f }; // Hue point.
		const float bb[2] = { cosf(-120.0f/180.0f*NVG_PI) * aa[0], sinf(-120.0f/180.0f*NVG_PI) * aa[0] }; // Black point.
		const float cc[2] = { cosf( 120.0f/180.0f*NVG_PI) * aa[0], sinf( 120.0f/180.0f*NVG_PI) * aa[0] }; // White point.

		const float ca[2] = { aa[0] - cc[0], aa[1] - cc[1] };
		const float lenCa = sqrtf(ca[0]*ca[0]+ca[1]*ca[1]);
		const float invLenCa = 1.0f/lenCa;
		const float dirCa[2] = { ca[0]*invLenCa, ca[1]*invLenCa };

		float sel[2];

		float hsv[3];
		bx::rgbToHsv(hsv, _rgb);

		bool enabled = _enabled && isEnabled(m_areaId);
		if (enabled)
		{
			if (m_leftPressed)
			{
				const float len = sqrtf(cmx*cmx + cmy*cmy);
				if (len > ri)
				{
					if (len < ro)
					{
						setActive(wheelId);
					}
				}
				else
				{
					setActive(triangleId);
				}
			}

			if (m_leftReleased
			&& (isActive(wheelId) || isActive(triangleId) ) )
			{
				clearActive();
			}

			// Set hue.
			if (m_left
			&&  isActive(wheelId) )
			{
				hsv[0] = atan2f(cmy, cmx)/NVG_PI*0.5f;
				if (hsv[0] < 0.0f)
				{
					hsv[0]+=1.0f;
				}
			}

		}

		if (enabled
		&&  m_left
		&&  isActive(triangleId) )
		{
			float an = -hsv[0]*NVG_PI*2.0f;
			float tmx = (cmx*cosf(an)-cmy*sinf(an) );
			float tmy = (cmx*sinf(an)+cmy*cosf(an) );

			if (pointInTriangle(tmx, tmy, aa[0], aa[1], bb[0], bb[1], cc[0], cc[1]) )
			{
				sel[0] = tmx;
				sel[1] = tmy;
			}
			else
			{
				closestPointOnTriangle(sel[0], sel[1], tmx, tmy, aa[0], aa[1], bb[0], bb[1], cc[0], cc[1]);
			}
		}
		else
		{
			/*
			 *                  bb (black)
			 *                  /\
			 *                 /  \
			 *                /    \
			 *               /      \
			 *              /        \
			 *             /    .sel  \
			 *            /            \
			 *  cc(white)/____.ss_______\aa (hue)
			 */
			const float ss[2] =
			{
				cc[0] + dirCa[0]*lenCa*hsv[1],
				cc[1] + dirCa[1]*lenCa*hsv[1],
			};

			const float sb[2] = { bb[0]-ss[0], bb[1]-ss[1] };
			const float lenSb = sqrtf(sb[0]*sb[0]+sb[1]*sb[1]);
			const float invLenSb = 1.0f/lenSb;
			const float dirSb[2] = { sb[0]*invLenSb, sb[1]*invLenSb };

			sel[0] = cc[0] + dirCa[0]*lenCa*hsv[1] + dirSb[0]*lenSb*(1.0f - hsv[2]);
			sel[1] = cc[1] + dirCa[1]*lenCa*hsv[1] + dirSb[1]*lenSb*(1.0f - hsv[2]);
		}

		float uu, vv, ww;
		barycentric(uu, vv, ww
				  , aa[0],  aa[1]
				  , bb[0],  bb[1]
				  , cc[0],  cc[1]
				  , sel[0], sel[1]
				  );

		const float val = bx::fclamp(1.0f-vv, 0.0001f, 1.0f);
		const float sat = bx::fclamp(uu/val,  0.0001f, 1.0f);

		const float out[3] = { hsv[0], sat, val };
		bx::hsvToRgb(_rgb, out);

		// Draw widget.
		nvgSave(m_nvg);
		{
			float saturation;
			uint8_t alpha0;
			uint8_t alpha1;
			if (enabled)
			{
				saturation = 1.0f;
				alpha0 = 255;
				alpha1 = 192;
			}
			else
			{
				saturation = 0.0f;
				alpha0 = 10;
				alpha1 = 10;
			}

			// Circle.
			for (uint8_t ii = 0; ii < 6; ii++)
			{
				const float a0 = float(ii)/6.0f      * 2.0f*NVG_PI - aeps;
				const float a1 = float(ii+1.0f)/6.0f * 2.0f*NVG_PI + aeps;
				nvgBeginPath(m_nvg);
				nvgArc(m_nvg, center[0], center[1], ri, a0, a1, NVG_CW);
				nvgArc(m_nvg, center[0], center[1], ro, a1, a0, NVG_CCW);
				nvgClosePath(m_nvg);

				const float ax = center[0] + cosf(a0) * (ri+ro)*0.5f;
				const float ay = center[1] + sinf(a0) * (ri+ro)*0.5f;
				const float bx = center[0] + cosf(a1) * (ri+ro)*0.5f;
				const float by = center[1] + sinf(a1) * (ri+ro)*0.5f;
				NVGpaint paint = nvgLinearGradient(m_nvg
												 , ax, ay
												 , bx, by
												 , nvgHSLA(a0/NVG_PI*0.5f,saturation,0.55f,alpha0)
												 , nvgHSLA(a1/NVG_PI*0.5f,saturation,0.55f,alpha0)
												 );

				nvgFillPaint(m_nvg, paint);
				nvgFill(m_nvg);
			}

			// Circle stroke.
			nvgBeginPath(m_nvg);
			nvgCircle(m_nvg, center[0], center[1], ri-0.5f);
			nvgCircle(m_nvg, center[0], center[1], ro+0.5f);
			nvgStrokeColor(m_nvg, nvgRGBA(0,0,0,64) );
			nvgStrokeWidth(m_nvg, 1.0f);
			nvgStroke(m_nvg);

			nvgSave(m_nvg);
			{
				// Hue selector.
				nvgTranslate(m_nvg, center[0], center[1]);
				nvgRotate(m_nvg, hsv[0]*NVG_PI*2.0f);
				nvgStrokeWidth(m_nvg, 2.0f);
				nvgBeginPath(m_nvg);
				nvgRect(m_nvg, ri-1.0f,-3.0f,rd+2.0f,6.0f);
				nvgStrokeColor(m_nvg, nvgRGBA(255,255,255,alpha1) );
				nvgStroke(m_nvg);

				// Hue selector drop shadow.
				NVGpaint paint = nvgBoxGradient(m_nvg, ri-3.0f,-5.0f,ro-ri+6.0f,10.0f, 2.0f,4.0f, nvgRGBA(0,0,0,128), nvgRGBA(0,0,0,0) );
				nvgBeginPath(m_nvg);
				nvgRect(m_nvg, ri-2.0f-10.0f,-4.0f-10.0f,ro-ri+4.0f+20.0f,8.0f+20.0f);
				nvgRect(m_nvg, ri-2.0f,-4.0f,ro-ri+4.0f,8.0f);
				nvgPathWinding(m_nvg, NVG_HOLE);
				nvgFillPaint(m_nvg, paint);
				nvgFill(m_nvg);

				// Center triangle stroke.
				nvgBeginPath(m_nvg);
				nvgMoveTo(m_nvg, aa[0], aa[1]);
				nvgLineTo(m_nvg, bb[0], bb[1]);
				nvgLineTo(m_nvg, cc[0], cc[1]);
				nvgClosePath(m_nvg);
				nvgStrokeColor(m_nvg, nvgRGBA(0,0,0,64) );
				nvgStroke(m_nvg);

				// Center triangle fill.
				paint = nvgLinearGradient(m_nvg, aa[0], aa[1], bb[0], bb[1], nvgHSL(hsv[0],saturation,0.5f), nvgRGBA(0,0,0,alpha0) );
				nvgFillPaint(m_nvg, paint);
				nvgFill(m_nvg);
				paint = nvgLinearGradient(m_nvg, (aa[0]+bb[0])*0.5f, (aa[1]+bb[1])*0.5f, cc[0], cc[1], nvgRGBA(0,0,0,0), nvgRGBA(255,255,255,alpha0) );
				nvgFillPaint(m_nvg, paint);
				nvgFill(m_nvg);

				// Color selector.
				nvgStrokeWidth(m_nvg, 2.0f);
				nvgBeginPath(m_nvg);
				nvgCircle(m_nvg, sel[0], sel[1], 5);
				nvgStrokeColor(m_nvg, nvgRGBA(255,255,255,alpha1) );
				nvgStroke(m_nvg);

				// Color selector stroke.
				paint = nvgRadialGradient(m_nvg, sel[0], sel[1], 7.0f, 9.0f, nvgRGBA(0,0,0,64), nvgRGBA(0,0,0,0) );
				nvgBeginPath(m_nvg);
				nvgRect(m_nvg, sel[0]-20.0f, sel[1]-20.0f, 40.0f, 40.0f);
				nvgCircle(m_nvg, sel[0], sel[1], 7.0f);
				nvgPathWinding(m_nvg, NVG_HOLE);
				nvgFillPaint(m_nvg, paint);
				nvgFill(m_nvg);
			}
			nvgRestore(m_nvg);
		}
		nvgRestore(m_nvg);
	}

	int32_t m_mx;
	int32_t m_my;
	int32_t m_scroll;
	uint32_t m_active;
	uint32_t m_hot;
	uint32_t m_hotToBe;
	char m_char;
	char m_lastChar;
	uint32_t m_inputField;
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

	uint8_t m_areaId;
	uint8_t m_widgetId;
	uint64_t m_enabledAreaIds;
	uint16_t m_scissor;

	float m_tempCoords[MAX_TEMP_COORDS * 2];
	float m_tempNormals[MAX_TEMP_COORDS * 2];

	float m_circleVerts[NUM_CIRCLE_VERTS * 2];

	int32_t m_scrollTop;
	int32_t m_scrollHeight;
	int32_t m_scrollRight;
	int32_t m_scrollAreaTop;
	int32_t m_scrollAreaWidth;
	int32_t m_scrollAreaInnerWidth;
	int32_t m_scrollAreaX;
	int32_t* m_scrollVal;
	uint16_t m_scrollId;
	bool m_insideScrollArea;

	uint16_t m_textureWidth;
	uint16_t m_textureHeight;
	float m_invTextureWidth;
	float m_invTextureHeight;
	float m_halfTexel;

	NVGcontext* m_nvg;

	uint8_t m_view;
	uint16_t m_viewWidth;
	uint16_t m_viewHeight;

#if !USE_NANOVG_FONT
	struct Font
	{
		stbtt_bakedchar m_cdata[96]; // ASCII 32..126 is 95 glyphs
		bgfx::TextureHandle m_texture;
		float m_size;
	};

	uint16_t m_currentFontIdx;
	bx::HandleAllocT<IMGUI_CONFIG_MAX_FONTS> m_fontHandle;
	Font m_fonts[IMGUI_CONFIG_MAX_FONTS];
#endif // !USE_NANOVG_FONT

	bgfx::UniformHandle u_imageLod;
	bgfx::UniformHandle u_imageSwizzle;
	bgfx::UniformHandle s_texColor;
	bgfx::ProgramHandle m_colorProgram;
	bgfx::ProgramHandle m_textureProgram;
	bgfx::ProgramHandle m_imageProgram;
	bgfx::ProgramHandle m_imageSwizzProgram;
	bgfx::TextureHandle m_missingTexture;
};

static Imgui s_imgui;

ImguiFontHandle imguiCreate(const void* _data, float _fontSize)
{
	return s_imgui.create(_data, _fontSize);
}

void imguiSetFont(ImguiFontHandle _handle)
{
	s_imgui.setFont(_handle);
}

ImguiFontHandle imguiCreateFont(const void* _data, float _fontSize)
{
	return s_imgui.createFont(_data, _fontSize);
}

void imguiDestroy()
{
	s_imgui.destroy();
}

void imguiBeginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, char _inputChar, uint8_t _view)
{
	s_imgui.beginFrame(_mx, _my, _button, _scroll, _width, _height, _inputChar, _view);
}

void imguiEndFrame()
{
	s_imgui.endFrame();
}

bool imguiBorderButton(ImguiBorder::Enum _border, bool _checked, bool _enabled)
{
	return s_imgui.borderButton(_border, _checked, _enabled);
}

bool imguiBeginScrollArea(const char* _name, int32_t _x, int32_t _y, int32_t _width, int32_t _height, int32_t* _scroll, bool _enabled, int32_t _r)
{
	return s_imgui.beginScrollArea(_name, _x, _y, _width, _height, _scroll, _enabled, _r);
}

void imguiEndScrollArea(int32_t _r)
{
	s_imgui.endScrollArea(_r);
}

void imguiIndent(uint16_t _width)
{
	s_imgui.indent(_width);
}

void imguiUnindent(uint16_t _width)
{
	s_imgui.unindent(_width);
}

void imguiSeparator(uint16_t _height)
{
	s_imgui.separator(_height);
}

void imguiSeparatorLine(uint16_t _height)
{
	s_imgui.separatorLine(_height);
}

int32_t imguiGetWidgetX()
{
	return s_imgui.m_widgetX;
}

int32_t imguiGetWidgetY()
{
	return s_imgui.m_widgetY;
}

bool imguiButton(const char* _text, bool _enabled, uint32_t _rgb0, int32_t _r)
{
	return s_imgui.button(_text, _enabled, _rgb0, _r);
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
	s_imgui.labelVargs(_format, argList, true);
	va_end(argList);
}

void imguiLabel(bool _enabled, const char* _format, ...)
{
	va_list argList;
	va_start(argList, _format);
	s_imgui.labelVargs(_format, argList, _enabled);
	va_end(argList);
}

void imguiValue(const char* _text)
{
	s_imgui.value(_text);
}

bool imguiSlider(const char* _text, float& _val, float _vmin, float _vmax, float _vinc, bool _enabled)
{
	return s_imgui.slider(_text, _val, _vmin, _vmax, _vinc, _enabled);
}

bool imguiSlider(const char* _text, int32_t& _val, int32_t _vmin, int32_t _vmax, bool _enabled)
{
	float val = (float)_val;
	bool result = s_imgui.slider(_text, val, (float)_vmin, (float)_vmax, 1.0f, _enabled);
	_val = (int32_t)val;
	return result;
}

void imguiInput(const char* _label, char* _str, uint32_t _len, bool _enabled, int32_t _r)
{
	s_imgui.input(_label, _str, _len, _enabled, _r);
}

uint8_t imguiTabsUseMacroInstead(uint8_t _selected, bool _enabled, ...)
{
	va_list argList;
	va_start(argList, _enabled);
	const uint8_t result = s_imgui.tabs(_selected, _enabled, BUTTON_HEIGHT, BUTTON_HEIGHT/2 - 1, argList);
	va_end(argList);

	return result;
}

uint8_t imguiTabsUseMacroInstead(uint8_t _selected, bool _enabled, int32_t _height, int32_t _r, ...)
{
	va_list argList;
	va_start(argList, _r);
	const uint8_t result = s_imgui.tabs(_selected, _enabled, _height, _r, argList);
	va_end(argList);

	return result;
}

uint32_t imguiChooseUseMacroInstead(uint32_t _selected, ...)
{
	va_list argList;
	va_start(argList, _selected);

	const char* str = va_arg(argList, const char*);
	for (uint32_t ii = 0; str != NULL; ++ii, str = va_arg(argList, const char*) )
	{
		if (imguiCheck(str, ii == _selected) )
		{
			_selected = ii;
		}
	}

	va_end(argList);

	return _selected;
}

void imguiDrawText(int32_t _x, int32_t _y, ImguiTextAlign::Enum _align, const char* _text, uint32_t _argb)
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

void imguiBool(const char* _text, bool& _flag, bool _enabled)
{
	if (imguiCheck(_text, _flag, _enabled) )
	{
		_flag = !_flag;
	}
}

void imguiColorWheel(float _rgb[3], bool _respectIndentation, bool _enabled)
{
	s_imgui.colorWheelWidget(_rgb, _respectIndentation, _enabled);
}

void imguiColorWheel(const char* _text, float _rgb[3], bool& _activated, bool _enabled)
{
	char buf[128];
	bx::snprintf(buf, sizeof(buf), "[RGB %-2.2f %-2.2f %-2.2f]"
		, _rgb[0]
		, _rgb[1]
		, _rgb[2]
		);

	if (imguiCollapse(_text, buf, _activated, _enabled) )
	{
		_activated = !_activated;
	}

	if (_activated)
	{
		imguiColorWheel(_rgb, false, _enabled);
	}
}

void imguiImage(bgfx::TextureHandle _image, float _lod, int32_t _width, int32_t _height, ImguiImageAlign::Enum _align)
{
	s_imgui.image(_image, _lod, _width, _height, _align);
}

void imguiImage(bgfx::TextureHandle _image, float _lod, float _width, float _aspect, ImguiImageAlign::Enum _align)
{
	s_imgui.image(_image, _lod, _width, _aspect, _align);
}

void imguiImageChannel(bgfx::TextureHandle _image, uint8_t _channel, float _lod, int32_t _width, int32_t _height, ImguiImageAlign::Enum _align)
{
	s_imgui.imageChannel(_image, _channel, _lod, _width, _height, _align);
}

void imguiImageChannel(bgfx::TextureHandle _image, uint8_t _channel, float _lod, float _width, float _aspect, ImguiImageAlign::Enum _align)
{
	s_imgui.imageChannel(_image, _channel, _lod, _width, _aspect, _align);
}
