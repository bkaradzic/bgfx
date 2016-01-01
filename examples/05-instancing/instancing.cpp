/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"

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

int _main_(int _argc, char** _argv)
{
	Args args(_argc, _argv);

	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init(args.m_type, args.m_pciId);
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	// Get renderer capabilities info.
	const bgfx::Caps* caps = bgfx::getCaps();

	// Create vertex stream declaration.
	PosColorVertex::init();

	const bgfx::Memory* mem;

	// Create static vertex buffer.
	mem = bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) );
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(mem, PosColorVertex::ms_decl);

	// Create static index buffer.
	mem = bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) );
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(mem);

	// Create program from shaders.
	bgfx::ProgramHandle program = loadProgram("vs_instancing", "fs_instancing");

	int64_t timeOffset = bx::getHPCounter();

	while (!entry::processEvents(width, height, debug, reset) )
	{
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
		const double toMs = 1000.0/freq;
		float time = (float)( (now - timeOffset)/double(bx::getHPFrequency() ) );

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/05-instancing");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Geometry instancing.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Check if instancing is supported.
		if (0 == (BGFX_CAPS_INSTANCING & caps->supported) )
		{
			// When instancing is not supported by GPU, implement alternative
			// code path that doesn't use instancing.
			bool blink = uint32_t(time*3.0f)&1;
			bgfx::dbgTextPrintf(0, 5, blink ? 0x1f : 0x01, " Instancing is not supported by GPU. ");
		}
		else
		{
			float at[3]  = { 0.0f, 0.0f,   0.0f };
			float eye[3] = { 0.0f, 0.0f, -35.0f };

			// Set view and projection matrix for view 0.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
			{
				float view[16];
				bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);

				float proj[16];
				bx::mtxProj(proj, hmd->eye[0].fov, 0.1f, 100.0f);

				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				//
				// Use HMD's width/height since HMD's internal frame buffer size
				// might be much larger than window size.
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, width, height);
			}

			const uint16_t instanceStride = 80;
			const bgfx::InstanceDataBuffer* idb = bgfx::allocInstanceDataBuffer(121, instanceStride);
			if (NULL != idb)
			{
				uint8_t* data = idb->data;

				// Write instance data for 11x11 cubes.
				for (uint32_t yy = 0, numInstances = 0; yy < 11 && numInstances < idb->num; ++yy)
				{
					for (uint32_t xx = 0; xx < 11 && numInstances < idb->num; ++xx, ++numInstances)
					{
						float* mtx = (float*)data;
						bx::mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
						mtx[12] = -15.0f + float(xx)*3.0f;
						mtx[13] = -15.0f + float(yy)*3.0f;
						mtx[14] = 0.0f;

						float* color = (float*)&data[64];
						color[0] = sinf(time+float(xx)/11.0f)*0.5f+0.5f;
						color[1] = cosf(time+float(yy)/11.0f)*0.5f+0.5f;
						color[2] = sinf(time*3.0f)*0.5f+0.5f;
						color[3] = 1.0f;

						data += instanceStride;
					}
				}

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(vbh);
				bgfx::setIndexBuffer(ibh);

				// Set instance data buffer.
				bgfx::setInstanceDataBuffer(idb);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 0.
				bgfx::submit(0, program);
			}
		}

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(program);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
