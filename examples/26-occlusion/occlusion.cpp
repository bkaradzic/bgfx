/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "camera.h"

#define CUBES_DIM 10

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

class ExampleOcclusion : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		uint32_t width  = 1280;
		uint32_t height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(width, height, m_reset);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
				);

		bgfx::setViewClear(2
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x202020ff
				, 1.0f
				, 0
				);

		// Create vertex stream declaration.
		PosColorVertex::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
				, PosColorVertex::ms_decl
				);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) )
				);

		// Create program from shaders.
		m_program = loadProgram("vs_cubes", "fs_cubes");

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_occlusionQueries); ++ii)
		{
			m_occlusionQueries[ii] = bgfx::createOcclusionQuery();
		}

		cameraCreate();

		const float initialPos[3] = { 15.5f, 0.0f, -15.5f };
		cameraSetPosition(initialPos);
		cameraSetHorizontalAngle(bx::toRad(-45.0f) );

		m_timeOffset = bx::getHPCounter();
	}

	virtual int shutdown() BX_OVERRIDE
	{
		// Cleanup.
		cameraDestroy();

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_occlusionQueries); ++ii)
		{
			bgfx::destroyOcclusionQuery(m_occlusionQueries[ii]);
		}

		bgfx::destroyIndexBuffer(m_ibh);
		bgfx::destroyVertexBuffer(m_vbh);
		bgfx::destroyProgram(m_program);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processWindowEvents(m_state, m_debug, m_reset) )
		{
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0/freq;
			const float time = (float)( (now-m_timeOffset)/double(bx::getHPFrequency() ) );
			const float deltaTime = float(frameTime/freq);

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/26-occlusion");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Using occlusion query for conditional rendering.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			uint32_t width  = m_state.m_width;
			uint32_t height = m_state.m_height;

			// Update camera.
			float view[16];
			cameraUpdate(deltaTime, m_state.m_mouse);
			cameraGetViewMtx(view);

			// Set view and projection matrix for view 0.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
			{
				float viewHead[16];
				float eye[3] = {};
				bx::mtxQuatTranslationHMD(viewHead, hmd->eye[0].rotation, eye);

				float tmp[16];
				bx::mtxMul(tmp, view, viewHead);

				bgfx::setViewTransform(0, tmp, hmd->eye[0].projection);
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);

				bgfx::setViewTransform(1, tmp, hmd->eye[1].projection);
				bgfx::setViewRect(1, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				float proj[16];
				bx::mtxProj(proj, 90.0f, float(width)/float(height), 0.1f, 10000.0f, bgfx::getCaps()->homogeneousDepth);

				bgfx::setViewTransform(0, view, proj);
				bgfx::setViewRect(0, 0, 0, width, height);

				bgfx::setViewTransform(1, view, proj);
				bgfx::setViewRect(1, 0, 0, width, height);

				float at[3]  = {  0.0f,  0.0f,   0.0f };
				float eye[3] = { 17.5f, 10.0f, -17.5f };
				bx::mtxLookAt(view, eye, at);

				bgfx::setViewTransform(2, view, proj);
				bgfx::setViewRect(2, 10, height - height/4 - 10, width/4, height/4);
			}

			bgfx::touch(0);
			bgfx::touch(2);

			uint8_t img[CUBES_DIM*CUBES_DIM*2];

			for (uint32_t yy = 0; yy < CUBES_DIM; ++yy)
			{
				for (uint32_t xx = 0; xx < CUBES_DIM; ++xx)
				{
					float mtx[16];
					bx::mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
					mtx[12] = -(CUBES_DIM-1) * 3.0f / 2.0f + float(xx)*3.0f;
					mtx[13] = 0.0f;
					mtx[14] = -(CUBES_DIM-1) * 3.0f / 2.0f + float(yy)*3.0f;

					bgfx::OcclusionQueryHandle occlusionQuery = m_occlusionQueries[yy*CUBES_DIM+xx];

					bgfx::setTransform(mtx);
					bgfx::setVertexBuffer(m_vbh);
					bgfx::setIndexBuffer(m_ibh);
					bgfx::setCondition(occlusionQuery, true);
					bgfx::setState(BGFX_STATE_DEFAULT);
					bgfx::submit(0, m_program);

					bgfx::setTransform(mtx);
					bgfx::setVertexBuffer(m_vbh);
					bgfx::setIndexBuffer(m_ibh);
					bgfx::setState(0
						| BGFX_STATE_DEPTH_TEST_LEQUAL
						| BGFX_STATE_CULL_CW
						);
					bgfx::submit(1, m_program, occlusionQuery);

					bgfx::setTransform(mtx);
					bgfx::setVertexBuffer(m_vbh);
					bgfx::setIndexBuffer(m_ibh);
					bgfx::setCondition(occlusionQuery, true);
					bgfx::setState(BGFX_STATE_DEFAULT);
					bgfx::submit(2, m_program);

					img[(yy*CUBES_DIM+xx)*2+0] = " \xfex"[bgfx::getResult(occlusionQuery)];
					img[(yy*CUBES_DIM+xx)*2+1] = 0xf;
				}
			}

			for (uint32_t xx = 0; xx < CUBES_DIM; ++xx)
			{
				bgfx::dbgTextImage(5 + xx*2, 5, 1, CUBES_DIM, img + xx*2, CUBES_DIM*2);
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	uint32_t m_reset;
	uint32_t m_debug;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::ProgramHandle m_program;
	int64_t m_timeOffset;

	bgfx::OcclusionQueryHandle m_occlusionQueries[CUBES_DIM*CUBES_DIM];

	entry::WindowState m_state;
};

ENTRY_IMPLEMENT_MAIN(ExampleOcclusion);
