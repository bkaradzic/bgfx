/*
 * Copyright 2014 Kai Jourdan. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 *
 */

#include "common.h"
#include "bgfx_utils.h"

#include "vectordisplay.h"

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
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

int _main_(int _argc, char** _argv)
{
	Args args(_argc, _argv);

	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init(args.m_type, args.m_pciId);
	bgfx::reset(width, height, reset);

	const bgfx::RendererType::Enum renderer = bgfx::getRendererType();
	float texelHalf = bgfx::RendererType::Direct3D9 == renderer ? 0.5f : 0.0f;
	bool originBottomLeft = bgfx::RendererType::OpenGL == renderer
	                        || bgfx::RendererType::OpenGLES == renderer;
	VectorDisplay vd(originBottomLeft, texelHalf);
	vd.setup(width, height);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);

	// Create vertex stream declaration.
	PosColorVertex::init();

	float at[3] = { 0.0f, 0.0f, 0.0f };
	float eye[3] = { 0.0f, 0.0f, -35.0f };

	uint32_t oldWidth = width;
	uint32_t oldHeight = height;

	while (!entry::processEvents(width, height, debug, reset) )
	{
		if (oldWidth  != width
		||  oldHeight != height)
		{
			oldWidth  = width;
			oldHeight = height;
			vd.resize(width, height);
		}

		float view[16];
		float proj[16];
		bx::mtxLookAt(view, eye, at);
		bx::mtxProj(proj, 60.0f, float(width) / float(height), 0.1f, 100.0f);
		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0 / freq;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/23-vectordisplay");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Rendering lines as oldschool vectors.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime) * toMs);

		vd.beginFrame();

		//simplex test
		vd.setDrawColor(0.7f, 0.7f, 1.0f);
		vd.drawSimplexFont(50.0f,  80.0f, 1.5f, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		vd.drawSimplexFont(50.0f, 140.0f, 1.5f, "abcdefghijklmnopqrstuvwxyz");
		vd.drawSimplexFont(50.0f, 200.0f, 1.5f, "!@#$%^&*()-=<>/?;:'\"{}[]|\\+=-_");

		vd.setDrawColor(1.0f, 0.7f, 0.7f);

		//test pattern for lines
		for (int ii = 0; ii < 4; ii++)
		{
			for (int jj = 0; jj < ii; jj++) //draw more intensive lines
			{
				vd.drawLine(50.0f, 350.0f + 40 * ii, 200.0f, 350.0f + 40 * ii);
			}
		}

		for (int ii = 0; ii < 4; ii++)
		{
			for (int jj = 0; jj <= ii; jj++)
			{
				vd.drawLine(50.0f + 40 * ii, 600.0f, 50.0f + 40 * ii, 700.0f);
			}
		}

		//
		// test pattern for shapes
		//
		vd.setDrawColor(0.7f, 0.7f, 1.0f);
		vd.drawCircle(250.0f, 450.0f, 10.0f, 32.0f);
		vd.drawCircle(300.0f, 450.0f, 30.0f, 32.0f);
		vd.drawCircle(400.0f, 450.0f, 60.0f, 32.0f);
		vd.drawCircle(500.0f, 450.0f, 80.0f, 64.0f);

		vd.setDrawColor(0.7f, 1.0f, 0.7f);
		vd.drawBox(250.0f, 600.0f, 10.0f, 10.0f);
		vd.drawBox(300.0f, 600.0f, 30.0f, 30.0f);
		vd.drawBox(350.0f, 600.0f, 60.0f, 60.0f);
		vd.drawBox(450.0f, 600.0f, 80.0f, 80.0f);

		vd.setDrawColor(1.0f, 0.7f, 1.0f);
		vd.drawWheel(bx::pi, 800.0f, 450.0f, 80.0f);
		vd.drawWheel(3.0f * bx::pi / 4.0f, 95.0f, 450.0f, 60.0f);
		vd.drawWheel(bx::pi / 2.0f, 1150.0f, 450.0f, 30.0f);
		vd.drawWheel(bx::pi / 4.0f, 1250.0f, 450.0f, 10.0f);

		// draw moving shape
		static float counter = 0.0f;
		counter += 0.01f;
		float posX = width  / 2.0f + sinf(counter * 3.18378f) * (width / 2.0f);
		float posY = height / 2.0f + cosf(counter) * (height / 2.0f);
		vd.drawCircle(posX, posY, 5.0f, 10.0f);

		vd.endFrame();

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	vd.teardown();

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
