/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <bx/uint32_t.h>

#include "common.h"
#include "imgui/imgui.h"

// embedded shaders
#include "vs_drawstress.bin.h"
#include "fs_drawstress.bin.h"

#if BX_PLATFORM_EMSCRIPTEN
#	include <emscripten.h>
#endif // BX_PLATFORM_EMSCRIPTEN

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

uint32_t width = 1280;
uint32_t height = 720;
uint32_t debug = BGFX_DEBUG_TEXT;
uint32_t reset = BGFX_RESET_NONE;

bool autoAdjust = true;
int32_t scrollArea = 0;
int32_t dim = 16;
int32_t maxDim = 40;
uint32_t transform = 0;

entry::MouseState mouseState;

int64_t timeOffset = bx::getHPCounter();

int64_t deltaTimeNs = 0;
int64_t deltaTimeAvgNs = 0;
int64_t numFrames = 0;

#if BX_PLATFORM_EMSCRIPTEN || BX_PLATFORM_NACL
static const int64_t highwm = 1000000/35;
static const int64_t lowwm  = 1000000/27;
#else
static const int64_t highwm = 1000000/65;
static const int64_t lowwm  = 1000000/57;
#endif // BX_PLATFORM_EMSCRIPTEN || BX_PLATFORM_NACL

bgfx::ProgramHandle program;
bgfx::VertexBufferHandle vbh;
bgfx::IndexBufferHandle ibh;

BX_NO_INLINE bool mainloop()
{
	if (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t hpFreq = bx::getHPFrequency();
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(hpFreq);
		const double toMs = 1000.0/freq;

		deltaTimeNs += frameTime*1000000/hpFreq;

		if (deltaTimeNs > 1000000)
		{
			deltaTimeAvgNs = deltaTimeNs / bx::int64_max(1, numFrames);

			if (autoAdjust)
			{
				if (deltaTimeAvgNs < highwm)
				{
					dim = bx::uint32_min(dim + 2, maxDim);
				}
				else if (deltaTimeAvgNs > lowwm)
				{
					dim = bx::uint32_max(dim - 1, 2);
				}
			}

			deltaTimeNs = 0;
			numFrames = 0;
		}
		else
		{
			++numFrames;
		}

		float time = (float)( (now-timeOffset)/freq);

		imguiBeginFrame(mouseState.m_mx
				, mouseState.m_my
				, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT  : 0)
				| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT : 0)
				, 0
				, width
				, height
				);

		imguiBeginScrollArea("Settings", width - width / 4 - 10, 10, width / 4, height / 3, &scrollArea);
		imguiSeparatorLine();

		transform = imguiChoose(transform
				, "Rotate"
				, "No fragments"
				);
		imguiSeparatorLine();

		if (imguiCheck("Auto adjust", autoAdjust) )
		{
			autoAdjust ^= true;
		}

		imguiSlider("Dim", dim, 5, maxDim);
		imguiLabel("Draw calls: %d", dim*dim*dim);
		imguiLabel("Avg Delta Time (1 second) [ms]: %0.4f", deltaTimeAvgNs/1000.0f);

		imguiEndScrollArea();
		imguiEndFrame();

		float at[3] = { 0.0f, 0.0f, 0.0f };
		float eye[3] = { 0.0f, 0.0f, -35.0f };

		float view[16];
		float proj[16];
		bx::mtxLookAt(view, eye, at);
		bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::submit(0);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/17-drawstress");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Draw stress, maximizing number of draw calls.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: %7.3f[ms]", double(frameTime)*toMs);

		float mtxS[16];
		const float scale = 0 == transform ? 0.25f : 0.0f;
		bx::mtxScale(mtxS, scale, scale, scale);

		const float step = 0.6f;
		float pos[3];
		pos[0] = -step*dim / 2.0f;
		pos[1] = -step*dim / 2.0f;
		pos[2] = -15.0;

		for (uint32_t zz = 0; zz < uint32_t(dim); ++zz)
		{
			for (uint32_t yy = 0; yy < uint32_t(dim); ++yy)
			{
				for (uint32_t xx = 0; xx < uint32_t(dim); ++xx)
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

					// Set vertex and fragment shaders.
					bgfx::setProgram(program);

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(vbh);
					bgfx::setIndexBuffer(ibh);

					// Set render states.
					bgfx::setState(BGFX_STATE_DEFAULT);

					// Submit primitive for rendering to view 0.
					bgfx::submit(0);
				}
			}
		}

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();

		return false;
	}

	return true;
}

void loop()
{
	mainloop();
}

int _main_(int /*_argc*/, char** /*_argv*/)
{
	bgfx::init();
	bgfx::reset(width, height, reset);

	const bgfx::Caps* caps = bgfx::getCaps();
	maxDim = (int32_t)powf(float(caps->maxDrawCalls), 1.0f/3.0f);

	// Enable debug text.
	bgfx::setDebug(debug);

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

		default:
			vs_drawstress = bgfx::makeRef(vs_drawstress_glsl, sizeof(vs_drawstress_glsl) );
			fs_drawstress = bgfx::makeRef(fs_drawstress_glsl, sizeof(fs_drawstress_glsl) );
			break;
	}

	// Create program from shaders.
	program = bgfx::createProgram(
		  bgfx::createShader(vs_drawstress)
		, bgfx::createShader(fs_drawstress)
		, true /* destroy shaders when program is destroyed */
		);

	const bgfx::Memory* mem;

	// Create static vertex buffer.
	mem = bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) );
	vbh = bgfx::createVertexBuffer(mem, PosColorVertex::ms_decl);

	// Create static index buffer.
	mem = bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) );
	ibh = bgfx::createIndexBuffer(mem);

	// Imgui.
	imguiCreate();

#if BX_PLATFORM_EMSCRIPTEN
	emscripten_set_main_loop(&loop, -1, 1);
#else
	while (!mainloop() );
#endif // BX_PLATFORM_EMSCRIPTEN

	// Cleanup.
	imguiDestroy();
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(program);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
