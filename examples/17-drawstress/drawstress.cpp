/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx/bgfx.h>
#include <bx/uint32_t.h>

#include "common.h"
#include "imgui/imgui.h"

// embedded shaders
#include "vs_drawstress.bin.h"
#include "fs_drawstress.bin.h"

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

static PosColorVertex s_cubeVertices[8] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeIndices[36] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

#if BX_PLATFORM_EMSCRIPTEN || BX_PLATFORM_NACL
static const int64_t highwm = 1000000/35;
static const int64_t lowwm  = 1000000/27;
#else
static const int64_t highwm = 1000000/65;
static const int64_t lowwm  = 1000000/57;
#endif // BX_PLATFORM_EMSCRIPTEN || BX_PLATFORM_NACL

class DrawStress : public entry::AppI
{
	void init(int /*_argc*/, char** /*_argv*/) BX_OVERRIDE
	{
		m_width  = 1280;
		m_height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_NONE;

		m_autoAdjust = true;
		m_scrollArea = 0;
		m_dim        = 16;
		m_maxDim     = 40;
		m_transform  = 0;

		m_timeOffset = bx::getHPCounter();

		m_deltaTimeNs    = 0;
		m_deltaTimeAvgNs = 0;
		m_numFrames      = 0;

		bgfx::init();
		bgfx::reset(m_width, m_height, m_reset);

		const bgfx::Caps* caps = bgfx::getCaps();
		m_maxDim = (int32_t)powf(float(caps->maxDrawCalls), 1.0f/3.0f);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
				);

		// Create vertex stream declaration.
		PosColorVertex::init();

		const bgfx::Memory* vs_drawstress;
		const bgfx::Memory* fs_drawstress;

		switch (bgfx::getRendererType() )
		{
			case bgfx::RendererType::Direct3D9:
				vs_drawstress = bgfx::makeRef(vs_drawstress_dx9, sizeof(vs_drawstress_dx9) );
				fs_drawstress = bgfx::makeRef(fs_drawstress_dx9, sizeof(fs_drawstress_dx9) );
				break;

			case bgfx::RendererType::Direct3D11:
			case bgfx::RendererType::Direct3D12:
				vs_drawstress = bgfx::makeRef(vs_drawstress_dx11, sizeof(vs_drawstress_dx11) );
				fs_drawstress = bgfx::makeRef(fs_drawstress_dx11, sizeof(fs_drawstress_dx11) );
				break;

			case bgfx::RendererType::Metal:
				vs_drawstress = bgfx::makeRef(vs_drawstress_mtl, sizeof(vs_drawstress_mtl) );
				fs_drawstress = bgfx::makeRef(fs_drawstress_mtl, sizeof(fs_drawstress_mtl) );
				break;

			default:
				vs_drawstress = bgfx::makeRef(vs_drawstress_glsl, sizeof(vs_drawstress_glsl) );
				fs_drawstress = bgfx::makeRef(fs_drawstress_glsl, sizeof(fs_drawstress_glsl) );
				break;
		}

		// Create program from shaders.
		m_program = bgfx::createProgram(
				  bgfx::createShader(vs_drawstress)
				, bgfx::createShader(fs_drawstress)
				, true /* destroy shaders when program is destroyed */
				);

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
					  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
					, PosColorVertex::ms_decl
					);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

		// Imgui.
		imguiCreate();
	}

	int shutdown() BX_OVERRIDE
	{
		// Cleanup.
		imguiDestroy();
		bgfx::destroyIndexBuffer(m_ibh);
		bgfx::destroyVertexBuffer(m_vbh);
		bgfx::destroyProgram(m_program);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t hpFreq = bx::getHPFrequency();
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(hpFreq);
			const double toMs = 1000.0/freq;

			m_deltaTimeNs += frameTime*1000000/hpFreq;

			if (m_deltaTimeNs > 1000000)
			{
				m_deltaTimeAvgNs = m_deltaTimeNs / bx::int64_max(1, m_numFrames);

				if (m_autoAdjust)
				{
					if (m_deltaTimeAvgNs < highwm)
					{
						m_dim = bx::uint32_min(m_dim + 2, m_maxDim);
					}
					else if (m_deltaTimeAvgNs > lowwm)
					{
						m_dim = bx::uint32_max(m_dim - 1, 2);
					}
				}

				m_deltaTimeNs = 0;
				m_numFrames   = 0;
			}
			else
			{
				++m_numFrames;
			}

			float time = (float)( (now-m_timeOffset)/freq);

			imguiBeginFrame(m_mouseState.m_mx
					,  m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					,  m_mouseState.m_mz
					, m_width
					, m_height
					);

			imguiBeginScrollArea("Settings", m_width - m_width / 4 - 10, 10, m_width / 4, m_height / 3, &m_scrollArea);
			imguiSeparatorLine();

			m_transform = imguiChoose(m_transform
					, "Rotate"
					, "No fragments"
					);
			imguiSeparatorLine();

			if (imguiCheck("Auto adjust", m_autoAdjust) )
			{
				m_autoAdjust ^= true;
			}

			imguiSlider("Dim", m_dim, 5, m_maxDim);
			imguiLabel("Draw calls: %d", m_dim*m_dim*m_dim);
			imguiLabel("Avg Delta Time (1 second) [ms]: %0.4f", m_deltaTimeAvgNs/1000.0f);

			imguiEndScrollArea();
			imguiEndFrame();

			float at[3] = { 0.0f, 0.0f, 0.0f };
			float eye[3] = { 0.0f, 0.0f, -35.0f };

			float view[16];
			float proj[16];
			bx::mtxLookAt(view, eye, at);
			bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f);

			// Set view and projection matrix for view 0.
			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, m_width, m_height);

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/17-drawstress");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Draw stress, maximizing number of draw calls.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: %7.3f[ms]", double(frameTime)*toMs);

			float mtxS[16];
			const float scale = 0 == m_transform ? 0.25f : 0.0f;
			bx::mtxScale(mtxS, scale, scale, scale);

			const float step = 0.6f;
			float pos[3];
			pos[0] = -step*m_dim / 2.0f;
			pos[1] = -step*m_dim / 2.0f;
			pos[2] = -15.0;

			for (uint32_t zz = 0; zz < uint32_t(m_dim); ++zz)
			{
				for (uint32_t yy = 0; yy < uint32_t(m_dim); ++yy)
				{
					for (uint32_t xx = 0; xx < uint32_t(m_dim); ++xx)
					{
						float mtxR[16];
						bx::mtxRotateXYZ(mtxR, time + xx*0.21f, time + yy*0.37f, time + yy*0.13f);

						float mtx[16];
						bx::mtxMul(mtx, mtxS, mtxR);

						mtx[12] = pos[0] + float(xx)*step;
						mtx[13] = pos[1] + float(yy)*step;
						mtx[14] = pos[2] + float(zz)*step;

						// Set model matrix for rendering.
						bgfx::setTransform(mtx);

						// Set vertex and index buffer.
						bgfx::setVertexBuffer(m_vbh);
						bgfx::setIndexBuffer(m_ibh);

						// Set render states.
						bgfx::setState(BGFX_STATE_DEFAULT);

						// Submit primitive for rendering to view 0.
						bgfx::submit(0, m_program);
					}
				}
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	bool     m_autoAdjust;
	int32_t  m_scrollArea;
	int32_t  m_dim;
	int32_t  m_maxDim;
	uint32_t m_transform;

	int64_t  m_timeOffset;

	int64_t  m_deltaTimeNs;
	int64_t  m_deltaTimeAvgNs;
	int64_t  m_numFrames;

	bgfx::ProgramHandle m_program;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
};

ENTRY_IMPLEMENT_MAIN(DrawStress);
