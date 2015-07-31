/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include <entry/input.h>
#include <bx/string.h>

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
	};

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

#define MAX_WINDOWS 8
entry::WindowState windows[MAX_WINDOWS];

void cmdCreateWindow(const void* /*_userData*/)
{
	entry::WindowHandle handle = entry::createWindow(rand()%1280, rand()%720, 640, 480);
	if (entry::isValid(handle) )
	{
		char str[256];
		bx::snprintf(str, BX_COUNTOF(str), "Window - handle %d", handle.idx);
		entry::setWindowTitle(handle, str);
		windows[handle.idx].m_handle = handle;
	}
}

void cmdDestroyWindow(const void* /*_userData*/)
{
	for (uint32_t ii = 0; ii < MAX_WINDOWS; ++ii)
	{
		if (entry::isValid(windows[ii].m_handle) )
		{
			entry::destroyWindow(windows[ii].m_handle);
			windows[ii].m_handle.idx = UINT16_MAX;
			return;
		}
	}
}

static const InputBinding s_bindings[] =
{
	{ entry::Key::KeyC, entry::Modifier::None, 1, cmdCreateWindow,  NULL },
	{ entry::Key::KeyD, entry::Modifier::None, 1, cmdDestroyWindow, NULL },
	INPUT_BINDING_END
};

int _main_(int /*_argc*/, char** /*_argv*/)
{
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();
	bgfx::reset(width, height, reset);

	const bgfx::Caps* caps = bgfx::getCaps();
	bool swapChainSupported = 0 != (caps->supported & BGFX_CAPS_SWAP_CHAIN);

	if (swapChainSupported)
	{
		inputAddBindings("22-windows", s_bindings);
	}

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

	// Create static vertex buffer.
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
		  // Static data can be passed with bgfx::makeRef
		  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
		, PosColorVertex::ms_decl
		);

	// Create static index buffer.
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) )
		);

	// Create program from shaders.
	bgfx::ProgramHandle program = loadProgram("vs_cubes", "fs_cubes");

	float at[3]  = { 0.0f, 0.0f,   0.0f };
	float eye[3] = { 0.0f, 0.0f, -35.0f };

	int64_t timeOffset = bx::getHPCounter();

	bgfx::FrameBufferHandle fbh[MAX_WINDOWS];
	memset(fbh, 0xff, sizeof(fbh) );

	entry::WindowState state;
	while (!entry::processWindowEvents(state, debug, reset) )
	{
		if (isValid(state.m_handle) )
		{
			if (0 == state.m_handle.idx)
			{
				width  = state.m_width;
				height = state.m_height;
			}
			else
			{
				uint8_t viewId = (uint8_t)state.m_handle.idx;
				entry::WindowState& win = windows[viewId];

				if (win.m_nwh    != state.m_nwh
				|| (win.m_width  != state.m_width
				||  win.m_height != state.m_height) )
				{
					// When window changes size or native window handle changed
					// frame buffer must be recreated.
					if (bgfx::isValid(fbh[viewId]) )
					{
						bgfx::destroyFrameBuffer(fbh[viewId]);
						fbh[viewId].idx = bgfx::invalidHandle;
					}

					win.m_nwh    = state.m_nwh;
					win.m_width  = state.m_width;
					win.m_height = state.m_height;

					if (NULL != win.m_nwh)
					{
						fbh[viewId] = bgfx::createFrameBuffer(win.m_nwh, win.m_width, win.m_height);
					}
					else
					{
						win.m_handle.idx = UINT16_MAX;
					}
				}
			}
		}

		float view[16];
		float proj[16];
		bx::mtxLookAt(view, eye, at);
		bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		bgfx::setViewTransform(0, view, proj);
		bgfx::setViewRect(0, 0, 0, width, height);
		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

		// Set view and projection matrix for view 0.
		for (uint32_t ii = 1; ii < MAX_WINDOWS; ++ii)
		{
			bgfx::setViewTransform(ii, view, proj);
			bgfx::setViewFrameBuffer(ii, fbh[ii]);

			if (!bgfx::isValid(fbh[ii]) )
			{
				// Set view to default viewport.
				bgfx::setViewRect(ii, 0, 0, width, height);
				bgfx::setViewClear(ii, BGFX_CLEAR_NONE);
			}
			else
			{
				bgfx::setViewRect(ii, 0, 0, windows[ii].m_width, windows[ii].m_height);
				bgfx::setViewClear(ii
					, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
					, 0x303030ff
					, 1.0f
					, 0
					);
			}
		}

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		float time = (float)( (now-timeOffset)/double(bx::getHPFrequency() ) );

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/22-windows");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Rendering into multiple windows.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		if (swapChainSupported)
		{
			bgfx::dbgTextPrintf(0, 5, 0x2f, "Press 'c' to create or 'd' to destroy window.");
		}
		else
		{
			bool blink = uint32_t(time*3.0f)&1;
			bgfx::dbgTextPrintf(0, 5, blink ? 0x1f : 0x01, " Multiple windows is not supported by `%s` renderer. ", bgfx::getRendererName(caps->rendererType) );
		}

		uint32_t count = 0;

		// Submit 11x11 cubes.
		for (uint32_t yy = 0; yy < 11; ++yy)
		{
			for (uint32_t xx = 0; xx < 11; ++xx)
			{
				float mtx[16];
				bx::mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
				mtx[12] = -15.0f + float(xx)*3.0f;
				mtx[13] = -15.0f + float(yy)*3.0f;
				mtx[14] = 0.0f;

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(vbh);
				bgfx::setIndexBuffer(ibh);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering.
				bgfx::submit(count%MAX_WINDOWS, program);
				++count;
			}
		}

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	for (uint32_t ii = 0; ii < MAX_WINDOWS; ++ii)
	{
		if (bgfx::isValid(fbh[ii]) )
		{
			bgfx::destroyFrameBuffer(fbh[ii]);
		}
	}

//	entry::destroyWindow(win.m_handle);

	// Cleanup.
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(program);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
