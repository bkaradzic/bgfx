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

#include <stdio.h>
#include <bx/string.h>
#include <bx/uint32_t.h>
#include <bx/fpumath.h>
#include <bx/handlealloc.h>
#include <bx/crtimpl.h>

#include "imgui.h"
#include "ocornut_imgui.h"
#include "../bgfx_utils.h"
#include "../nanovg/nanovg.h"

#include <bgfx/embedded_shader.h>

// embedded shaders
#include "vs_imgui_color.bin.h"
#include "fs_imgui_color.bin.h"
#include "vs_imgui_texture.bin.h"
#include "fs_imgui_texture.bin.h"
#include "vs_imgui_cubemap.bin.h"
#include "fs_imgui_cubemap.bin.h"
#include "vs_imgui_latlong.bin.h"
#include "fs_imgui_latlong.bin.h"
#include "vs_imgui_image.bin.h"
#include "fs_imgui_image.bin.h"
#include "fs_imgui_image_swizz.bin.h"

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_imgui_color),
	BGFX_EMBEDDED_SHADER(fs_imgui_color),
	BGFX_EMBEDDED_SHADER(vs_imgui_texture),
	BGFX_EMBEDDED_SHADER(fs_imgui_texture),
	BGFX_EMBEDDED_SHADER(vs_imgui_cubemap),
	BGFX_EMBEDDED_SHADER(fs_imgui_cubemap),
	BGFX_EMBEDDED_SHADER(vs_imgui_latlong),
	BGFX_EMBEDDED_SHADER(fs_imgui_latlong),
	BGFX_EMBEDDED_SHADER(vs_imgui_image),
	BGFX_EMBEDDED_SHADER(fs_imgui_image),
	BGFX_EMBEDDED_SHADER(fs_imgui_image_swizz),

	BGFX_EMBEDDED_SHADER_END()
};

BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4244); // warning C4244: '=' : conversion from '' to '', possible loss of data

void* imguiMalloc(size_t _size, void*);
void  imguiFree(void* _ptr, void*);

BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4505); // error C4505: '' : unreferenced local function has been removed
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-function"); // warning: ‘int rect_width_compare(const void*, const void*)’ defined but not used
BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunknown-pragmas")
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-but-set-variable"); // warning: variable ‘L1’ set but not used
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wtype-limits"); // warning: comparison is always true due to limited range of data type
#define STBTT_malloc(_size, _userData) imguiMalloc(_size, _userData)
#define STBTT_free(_ptr, _userData) imguiFree(_ptr, _userData)
#define STB_RECT_PACK_IMPLEMENTATION
#include <stb/stb_rect_pack.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>
BX_PRAGMA_DIAGNOSTIC_POP();

namespace
{
	static uint32_t addQuad(uint16_t* _indices, uint16_t _idx0, uint16_t _idx1, uint16_t _idx2, uint16_t _idx3)
	{
		_indices[0] = _idx0;
		_indices[1] = _idx3;
		_indices[2] = _idx1;

		_indices[3] = _idx1;
		_indices[4] = _idx3;
		_indices[5] = _idx2;

		return 6;
	}

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

		float len = bx::fsqrt(lx*lx+ly*ly);

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

		const float lab = bx::fsqrt(pabx*pabx+paby*paby);
		const float lbc = bx::fsqrt(pbcx*pbcx+pbcy*pbcy);
		const float lca = bx::fsqrt(pcax*pcax+pcay*pcay);

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

	struct PosNormalVertex
	{
		float m_x;
		float m_y;
		float m_z;
		float m_nx;
		float m_ny;
		float m_nz;

		static void init()
		{
			ms_decl.begin()
				   .add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
				   .add(bgfx::Attrib::Normal,    3, bgfx::AttribType::Float)
				   .end();
		}

		void set(float _x, float _y, float _z, float _nx, float _ny, float _nz)
		{
			m_x = _x;
			m_y = _y;
			m_z = _z;
			m_nx = _nx;
			m_ny = _ny;
			m_nz = _nz;
		}

		static bgfx::VertexDecl ms_decl;
	};

	bgfx::VertexDecl PosNormalVertex::ms_decl;

} // namespace

struct Imgui
{
	Imgui()
		: m_mx(-1)
		, m_my(-1)
		, m_scroll(0)
		, m_textureWidth(512)
		, m_textureHeight(512)
		, m_halfTexel(0.0f)
		, m_view(255)
		, m_surfaceWidth(0)
		, m_surfaceHeight(0)
		, m_viewWidth(0)
		, m_viewHeight(0)
	{
		m_invTextureWidth  = 1.0f/m_textureWidth;
		m_invTextureHeight = 1.0f/m_textureHeight;

		u_imageLodEnabled.idx = bgfx::kInvalidHandle;
		u_imageSwizzle.idx    = bgfx::kInvalidHandle;
		s_texColor.idx        = bgfx::kInvalidHandle;
		m_missingTexture.idx  = bgfx::kInvalidHandle;

		m_colorProgram.idx      = bgfx::kInvalidHandle;
		m_textureProgram.idx    = bgfx::kInvalidHandle;
		m_cubeMapProgram.idx    = bgfx::kInvalidHandle;
		m_latlongProgram.idx    = bgfx::kInvalidHandle;
		m_imageProgram.idx      = bgfx::kInvalidHandle;
		m_imageSwizzProgram.idx = bgfx::kInvalidHandle;
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

		return bgfx::createTexture2D(
					  uint16_t(_width)
					, uint16_t(_height)
					, false
					, 1
					, bgfx::TextureFormat::BGRA8
					, 0
					, mem
					);
	}

	void create(float _fontSize, bx::AllocatorI* _allocator)
	{
		m_allocator = _allocator;

		if (NULL == _allocator)
		{
			static bx::DefaultAllocator allocator;
			m_allocator = &allocator;
		}

		IMGUI_create(_fontSize, m_allocator);

		PosColorVertex::init();
		PosColorUvVertex::init();
		PosUvVertex::init();
		PosNormalVertex::init();

		u_imageLodEnabled = bgfx::createUniform("u_imageLodEnabled", bgfx::UniformType::Vec4);
		u_imageSwizzle    = bgfx::createUniform("u_swizzle",         bgfx::UniformType::Vec4);
		s_texColor        = bgfx::createUniform("s_texColor",        bgfx::UniformType::Int1);

		bgfx::ShaderHandle vsh;
		bgfx::ShaderHandle fsh;

		bgfx::RendererType::Enum type = bgfx::getRendererType();
		vsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_imgui_color");
		fsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui_color");
		m_colorProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(vsh);
		bgfx::destroyShader(fsh);

		vsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_imgui_texture");
		fsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui_texture");
		m_textureProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(vsh);
		bgfx::destroyShader(fsh);

		vsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_imgui_cubemap");
		fsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui_cubemap");
		m_cubeMapProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(vsh);
		bgfx::destroyShader(fsh);

		vsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_imgui_latlong");
		fsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui_latlong");
		m_latlongProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(vsh);
		bgfx::destroyShader(fsh);

		vsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_imgui_image");
		fsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui_image");
		m_imageProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(fsh);

		// Notice: using the same vsh.
		fsh = bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui_image_swizz");
		m_imageSwizzProgram = bgfx::createProgram(vsh, fsh);
		bgfx::destroyShader(fsh);
		bgfx::destroyShader(vsh);

		m_missingTexture = genMissingTexture(256, 256, 0.04f);
	}

	void destroy()
	{
		bgfx::destroyUniform(u_imageLodEnabled);
		bgfx::destroyUniform(u_imageSwizzle);
		bgfx::destroyUniform(s_texColor);
		bgfx::destroyTexture(m_missingTexture);
		bgfx::destroyProgram(m_colorProgram);
		bgfx::destroyProgram(m_textureProgram);
		bgfx::destroyProgram(m_cubeMapProgram);
		bgfx::destroyProgram(m_latlongProgram);
		bgfx::destroyProgram(m_imageProgram);
		bgfx::destroyProgram(m_imageSwizzProgram);

		IMGUI_destroy();
	}

	void beginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, uint16_t _surfaceWidth, uint16_t _surfaceHeight, char _inputChar, uint8_t _view)
	{
		m_view = _view;
		m_viewWidth = _width;
		m_viewHeight = _height;
		m_surfaceWidth = _surfaceWidth;
		m_surfaceHeight = _surfaceHeight;

		const float xscale = float(m_surfaceWidth) /float(m_viewWidth);
		const float yscale = float(m_surfaceHeight)/float(m_viewHeight);
		const int32_t mx = int32_t(float(_mx)*xscale);
		const int32_t my = int32_t(float(_my)*yscale);

		IMGUI_beginFrame(mx, my, _button, _scroll, _width, _height, _inputChar, _view);

		bgfx::setViewName(_view, "IMGUI");
		bgfx::setViewMode(_view, bgfx::ViewMode::Sequential);

		const bgfx::HMD*  hmd  = bgfx::getHMD();
		const bgfx::Caps* caps = bgfx::getCaps();
		if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
		{
			m_viewWidth = _width / 2;
			m_surfaceWidth = _surfaceWidth / 2;

			float proj[16];
			bx::mtxProj(proj, hmd->eye[0].fov, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

			static float time = 0.0f;
			time += 0.05f;

			const float dist = 10.0f;
			const float offset0 = -proj[8] + (hmd->eye[0].viewOffset[0] / dist * proj[0]);
			const float offset1 = -proj[8] + (hmd->eye[1].viewOffset[0] / dist * proj[0]);

			float ortho[2][16];
			const float viewOffset = _surfaceWidth/4.0f;
			const float viewWidth  = _surfaceWidth/2.0f;
			bx::mtxOrtho(ortho[0], viewOffset, viewOffset + viewWidth, (float)m_surfaceHeight, 0.0f, 0.0f, 1000.0f, offset0, caps->homogeneousDepth);
			bx::mtxOrtho(ortho[1], viewOffset, viewOffset + viewWidth, (float)m_surfaceHeight, 0.0f, 0.0f, 1000.0f, offset1, caps->homogeneousDepth);
			bgfx::setViewTransform(_view, NULL, ortho[0], BGFX_VIEW_STEREO, ortho[1]);
			bgfx::setViewRect(_view, 0, 0, hmd->width, hmd->height);
		}
		else
		{
			float ortho[16];
			bx::mtxOrtho(ortho, 0.0f, (float)m_surfaceWidth, (float)m_surfaceHeight, 0.0f, 0.0f, 1000.0f, 0.0f, caps->homogeneousDepth);
			bgfx::setViewTransform(_view, NULL, ortho);
			bgfx::setViewRect(_view, 0, 0, _width, _height);
		}
	}

	void endFrame()
	{
		IMGUI_endFrame();
	}

#if 0
	bool cubeMap(bgfx::TextureHandle _cubemap, float _lod, bool _cross, bool _sameHeight, ImguiAlign::Enum _align, bool _enabled)
	{
		const uint32_t id = getId();

		Area& area = getCurrentArea();
		int32_t xx;
		int32_t width;
		if (ImguiAlign::Left == _align)
		{
			xx = area.m_contentX + SCROLL_AREA_PADDING;
			width = area.m_widgetW;
		}
		else if (ImguiAlign::LeftIndented == _align
			 ||  ImguiAlign::Right        == _align)
		{
			xx = area.m_widgetX;
			width = area.m_widgetW;
		}
		else //if (ImguiAlign::Center         == _align
			 //||  ImguiAlign::CenterIndented == _align).
		{
			xx = area.m_widgetX;
			width = area.m_widgetW - (area.m_widgetX-area.m_contentX);
		}

		const bool adjustHeight = (_cross && _sameHeight);
		const bool fullHeight   = (_cross && !_sameHeight);

		if (adjustHeight)
		{
			xx += width/6;
		}

		const int32_t height = fullHeight ? (width*3)/4 : (width/2);
		const int32_t yy = area.m_widgetY;
		area.m_widgetY += height + DEFAULT_SPACING;

		const uint32_t numVertices = 14;
		const uint32_t numIndices  = 36;
		if (checkAvailTransientBuffers(numVertices, PosNormalVertex::ms_decl, numIndices) )
		{
			bgfx::TransientVertexBuffer tvb;
			bgfx::allocTransientVertexBuffer(&tvb, numVertices, PosNormalVertex::ms_decl);

			bgfx::TransientIndexBuffer tib;
			bgfx::allocTransientIndexBuffer(&tib, numIndices);

			PosNormalVertex* vertex = (PosNormalVertex*)tvb.data;
			uint16_t* indices = (uint16_t*)tib.data;

			if (_cross)
			{
				vertex->set(0.0f, 0.5f, 0.0f, -1.0f,  1.0f, -1.0f); ++vertex;
				vertex->set(0.0f, 1.0f, 0.0f, -1.0f, -1.0f, -1.0f); ++vertex;

				vertex->set(0.5f, 0.0f, 0.0f, -1.0f,  1.0f, -1.0f); ++vertex;
				vertex->set(0.5f, 0.5f, 0.0f, -1.0f,  1.0f,  1.0f); ++vertex;
				vertex->set(0.5f, 1.0f, 0.0f, -1.0f, -1.0f,  1.0f); ++vertex;
				vertex->set(0.5f, 1.5f, 0.0f, -1.0f, -1.0f, -1.0f); ++vertex;

				vertex->set(1.0f, 0.0f, 0.0f,  1.0f,  1.0f, -1.0f); ++vertex;
				vertex->set(1.0f, 0.5f, 0.0f,  1.0f,  1.0f,  1.0f); ++vertex;
				vertex->set(1.0f, 1.0f, 0.0f,  1.0f, -1.0f,  1.0f); ++vertex;
				vertex->set(1.0f, 1.5f, 0.0f,  1.0f, -1.0f, -1.0f); ++vertex;

				vertex->set(1.5f, 0.5f, 0.0f,  1.0f,  1.0f, -1.0f); ++vertex;
				vertex->set(1.5f, 1.0f, 0.0f,  1.0f, -1.0f, -1.0f); ++vertex;

				vertex->set(2.0f, 0.5f, 0.0f, -1.0f,  1.0f, -1.0f); ++vertex;
				vertex->set(2.0f, 1.0f, 0.0f, -1.0f, -1.0f, -1.0f); ++vertex;

				indices += addQuad(indices,  0,  3,  4,  1);
				indices += addQuad(indices,  2,  6,  7,  3);
				indices += addQuad(indices,  3,  7,  8,  4);
				indices += addQuad(indices,  4,  8,  9,  5);
				indices += addQuad(indices,  7, 10, 11,  8);
				indices += addQuad(indices, 10, 12, 13, 11);
			}
			else
			{
				vertex->set(0.0f, 0.25f, 0.0f, -1.0f,  1.0f, -1.0f); ++vertex;
				vertex->set(0.0f, 0.75f, 0.0f, -1.0f, -1.0f, -1.0f); ++vertex;

				vertex->set(0.5f, 0.00f, 0.0f, -1.0f,  1.0f,  1.0f); ++vertex;
				vertex->set(0.5f, 0.50f, 0.0f, -1.0f, -1.0f,  1.0f); ++vertex;
				vertex->set(0.5f, 1.00f, 0.0f,  1.0f, -1.0f, -1.0f); ++vertex;

				vertex->set(1.0f, 0.25f, 0.0f,  1.0f,  1.0f,  1.0f); ++vertex;
				vertex->set(1.0f, 0.75f, 0.0f,  1.0f, -1.0f,  1.0f); ++vertex;

				vertex->set(1.0f, 0.25f, 0.0f,  1.0f,  1.0f,  1.0f); ++vertex;
				vertex->set(1.0f, 0.75f, 0.0f,  1.0f, -1.0f,  1.0f); ++vertex;

				vertex->set(1.5f, 0.00f, 0.0f, -1.0f,  1.0f,  1.0f); ++vertex;
				vertex->set(1.5f, 0.50f, 0.0f,  1.0f,  1.0f, -1.0f); ++vertex;
				vertex->set(1.5f, 1.00f, 0.0f,  1.0f, -1.0f, -1.0f); ++vertex;

				vertex->set(2.0f, 0.25f, 0.0f, -1.0f,  1.0f, -1.0f); ++vertex;
				vertex->set(2.0f, 0.75f, 0.0f, -1.0f, -1.0f, -1.0f); ++vertex;

				indices += addQuad(indices,  0,  2,  3,  1);
				indices += addQuad(indices,  1,  3,  6,  4);
				indices += addQuad(indices,  2,  5,  6,  3);
				indices += addQuad(indices,  7,  9, 12, 10);
				indices += addQuad(indices,  7, 10, 11,  8);
				indices += addQuad(indices, 10, 12, 13, 11);
			}

			const bool enabled = _enabled && isEnabled(m_areaId);
			const bool over = enabled && inRect(xx, yy, width, height);
			const bool res = buttonLogic(id, over);

			const float widthf = float(width);
			const float scale = adjustHeight ? (widthf+0.5f)/3.0f : (widthf*0.5f + 0.25f);

			float mtx[16];
			bx::mtxSRT(mtx, scale, scale, 1.0f, 0.0f, 0.0f, 0.0f, float(xx), float(yy), 0.0f);

			const float lodEnabled[4] = { _lod, float(enabled), 0.0f, 0.0f };
			bgfx::setUniform(u_imageLodEnabled, lodEnabled);

			bgfx::setTransform(mtx);
			bgfx::setTexture(0, s_texColor, _cubemap);
			bgfx::setVertexBuffer(0, &tvb);
			bgfx::setIndexBuffer(&tib);
			bgfx::setState(BGFX_STATE_RGB_WRITE
						  |BGFX_STATE_ALPHA_WRITE
						  |BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
						  );
			setCurrentScissor();
			bgfx::submit(m_view, m_cubeMapProgram);

			return res;
		}

		return false;
	}
#endif // 0

	bx::AllocatorI* m_allocator;
	int32_t m_mx;
	int32_t m_my;
	int32_t m_scroll;

	uint16_t m_textureWidth;
	uint16_t m_textureHeight;
	float m_invTextureWidth;
	float m_invTextureHeight;
	float m_halfTexel;

	uint8_t m_view;
	uint16_t m_surfaceWidth;
	uint16_t m_surfaceHeight;
	uint16_t m_viewWidth;
	uint16_t m_viewHeight;

	bgfx::UniformHandle u_imageLodEnabled;
	bgfx::UniformHandle u_imageSwizzle;
	bgfx::UniformHandle s_texColor;
	bgfx::ProgramHandle m_colorProgram;
	bgfx::ProgramHandle m_textureProgram;
	bgfx::ProgramHandle m_cubeMapProgram;
	bgfx::ProgramHandle m_latlongProgram;
	bgfx::ProgramHandle m_imageProgram;
	bgfx::ProgramHandle m_imageSwizzProgram;
	bgfx::TextureHandle m_missingTexture;
};

static Imgui s_imgui;

void* imguiMalloc(size_t _size, void*)
{
	return BX_ALLOC(s_imgui.m_allocator, _size);
}

void imguiFree(void* _ptr, void*)
{
	BX_FREE(s_imgui.m_allocator, _ptr);
}

void imguiCreate(const void*, uint32_t, float _fontSize, bx::AllocatorI* _allocator)
{
	s_imgui.create(_fontSize, _allocator);
}

void imguiDestroy()
{
	s_imgui.destroy();
}

void imguiBeginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, uint16_t _surfaceWidth, uint16_t _surfaceHeight, char _inputChar, uint8_t _view)
{
	s_imgui.beginFrame(_mx, _my, _button, _scroll, _width, _height, _surfaceWidth, _surfaceHeight, _inputChar, _view);
}

void imguiBeginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, char _inputChar, uint8_t _view)
{
	s_imgui.beginFrame(_mx, _my, _button, _scroll, _width, _height, _width, _height, _inputChar, _view);
}

void imguiEndFrame()
{
	s_imgui.endFrame();
}

bgfx::ProgramHandle imguiGetImageProgram(uint8_t _mip)
{
	const float lodEnabled[4] = { float(_mip), 1.0f, 0.0f, 0.0f };
	bgfx::setUniform(s_imgui.u_imageLodEnabled, lodEnabled);
	return s_imgui.m_imageProgram;
}
