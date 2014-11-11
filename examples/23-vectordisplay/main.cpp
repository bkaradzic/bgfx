/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

int _main_(int /*_argc*/, char** /*_argv*/)
{
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();
	bgfx::reset(width, height, reset);

	const bgfx::RendererType::Enum renderer = bgfx::getRendererType();
	float texelHalf = bgfx::RendererType::Direct3D9 == renderer ? 0.5f : 0.0f;
	bool originBottomLeft = bgfx::RendererType::OpenGL == renderer || bgfx::RendererType::OpenGLES == renderer;
	VectorDisplay vectorDisplay(originBottomLeft, texelHalf);
	vectorDisplay.setup((float)width, (float)height);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT, 0x303030ff, 1.0f, 0);

	// Create vertex stream declaration.
	PosColorVertex::init();

	float at[3] = { 0.0f, 0.0f, 0.0f };
	float eye[3] = { 0.0f, 0.0f, -35.0f };

	uint32_t oldWidth = width;
	uint32_t oldHeight = height;

	while (!entry::processEvents(width, height, debug, reset) )
	{
		if((oldWidth != width) || (oldHeight != height)) 
		{
			oldWidth = width;
			oldHeight = height;
			vectorDisplay.resize((float)width, (float)height);
		}

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

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/23-vectordisplay");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Rendering lines as oldschool vectors.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		vectorDisplay.beginFrame();

	   //simplex test
	   vectorDisplay.setDrawColor(0.7f, 0.7f, 1.0f);
		vectorDisplay.drawSimplexFont(50, 80, 1.5, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		vectorDisplay.drawSimplexFont(50, 140, 1.5, "abcdefghijklmnopqrstuvwxyz");
		vectorDisplay.drawSimplexFont(50, 200, 1.5, "!@#$%^&*()-=<>/?;:'\"{}[]|\\+=-_");

		vectorDisplay.setDrawColor(1.0f, 0.7f, 0.7f);

		//test pattern for lines
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < i; j++) {			//draw more intensive lines
				vectorDisplay.drawLine(50.0f,  350.0f+40*i, 200.0f, 350.0f+40*i);     
			}
		}
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j <= i; j++) {
				vectorDisplay.drawLine(50.0f + 40 * i, 600.0f, 50.0f + 40 * i, 700.0f);    
			}
		}

		//
		// test pattern for shapes
		//
		vectorDisplay.setDrawColor(0.7f, 0.7f, 1.0f);
		vectorDisplay.drawCircle(250, 450, 10,  32);
		vectorDisplay.drawCircle(300, 450, 30,  32);
		vectorDisplay.drawCircle(400, 450, 60, 32);
		vectorDisplay.drawCircle(500, 450, 80, 64);

		vectorDisplay.setDrawColor(0.7f, 1.0f, 0.7f);
		vectorDisplay.drawBox(250, 600, 10, 10);
		vectorDisplay.drawBox(300, 600, 30, 30);
		vectorDisplay.drawBox(350, 600, 60, 60);
		vectorDisplay.drawBox(450, 600, 80, 80);

		vectorDisplay.setDrawColor(1.0f, 0.7f, 1.0f);
		vectorDisplay.drawWheel(bx::pi,         800,  450, 80);
		vectorDisplay.drawWheel(3 * bx::pi / 4, 950,  450, 60);
		vectorDisplay.drawWheel(bx::pi / 2,     1150, 450, 30);
		vectorDisplay.drawWheel(bx::pi / 4,     1250, 450, 10);

		// draw moving shape
		static float counter = 0.0f;
		counter += 0.01f;
		float posX = width/2 + sin(counter*3.18378f)*(width/2);
		float posY = height/2 + cos(counter)*(height/2);
		vectorDisplay.drawCircle(posX, posY, 5, 10);

 	 	vectorDisplay.endFrame();

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	vectorDisplay.teardown();

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
