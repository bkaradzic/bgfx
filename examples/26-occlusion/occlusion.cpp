/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "camera.h"
#include "imgui/imgui.h"

namespace
{

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
public:
	ExampleOcclusion(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

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

		const bgfx::Caps* caps = bgfx::getCaps();
		m_occlusionQuerySupported = !!(caps->supported & BGFX_CAPS_OCCLUSION_QUERY);

		if (m_occlusionQuerySupported)
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_occlusionQueries); ++ii)
			{
				m_occlusionQueries[ii] = bgfx::createOcclusionQuery();
			}
		}

		cameraCreate();

		const float initialPos[3] = { 15.5f, 0.0f, -15.5f };
		cameraSetPosition(initialPos);
		cameraSetHorizontalAngle(bx::toRad(-45.0f) );

		m_timeOffset = bx::getHPCounter();

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		// Cleanup.
		cameraDestroy();

		if (m_occlusionQuerySupported)
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_occlusionQueries); ++ii)
			{
				bgfx::destroy(m_occlusionQueries[ii]);
			}
		}

		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this
				, !m_occlusionQuerySupported
				? "Occlusion query is not supported."
				: NULL
				);

			imguiEndFrame();

			if (m_occlusionQuerySupported)
			{
				int64_t now = bx::getHPCounter();
				static int64_t last = now;
				const int64_t frameTime = now - last;
				last = now;
				const double freq = double(bx::getHPFrequency() );
				const float time = (float)( (now-m_timeOffset)/double(bx::getHPFrequency() ) );
				const float deltaTime = float(frameTime/freq);

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
					bx::mtxProj(proj, 90.0f, float(m_width)/float(m_height), 0.1f, 10000.0f, bgfx::getCaps()->homogeneousDepth);

					bgfx::setViewTransform(0, view, proj);
					bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

					bgfx::setViewTransform(1, view, proj);
					bgfx::setViewRect(1, 0, 0, uint16_t(m_width), uint16_t(m_height) );

					float at[3]  = {  0.0f,  0.0f,   0.0f };
					float eye[3] = { 17.5f, 10.0f, -17.5f };
					bx::mtxLookAt(view, eye, at);

					bgfx::setViewTransform(2, view, proj);
					bgfx::setViewRect(2, 10, uint16_t(m_height - m_height/4 - 10), uint16_t(m_width/4), uint16_t(m_height/4) );
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
						bgfx::setVertexBuffer(0, m_vbh);
						bgfx::setIndexBuffer(m_ibh);
						bgfx::setCondition(occlusionQuery, true);
						bgfx::setState(BGFX_STATE_DEFAULT);
						bgfx::submit(0, m_program);

						bgfx::setTransform(mtx);
						bgfx::setVertexBuffer(0, m_vbh);
						bgfx::setIndexBuffer(m_ibh);
						bgfx::setState(0
							| BGFX_STATE_DEPTH_TEST_LEQUAL
							| BGFX_STATE_CULL_CW
							);
						bgfx::submit(1, m_program, occlusionQuery);

						bgfx::setTransform(mtx);
						bgfx::setVertexBuffer(0, m_vbh);
						bgfx::setIndexBuffer(m_ibh);
						bgfx::setCondition(occlusionQuery, true);
						bgfx::setState(BGFX_STATE_DEFAULT);
						bgfx::submit(2, m_program);

						img[(yy*CUBES_DIM+xx)*2+0] = " \xfex"[bgfx::getResult(occlusionQuery)];
						img[(yy*CUBES_DIM+xx)*2+1] = 0xf;
					}
				}

				for (uint16_t xx = 0; xx < CUBES_DIM; ++xx)
				{
					bgfx::dbgTextImage(5 + xx*2, 20, 1, CUBES_DIM, img + xx*2, CUBES_DIM*2);
				}

				int32_t numPixels = 0;
				bgfx::getResult(m_occlusionQueries[0], &numPixels);
				bgfx::dbgTextPrintf(5, 20 + CUBES_DIM + 1, 0xf, "Passing pixels count: %d", numPixels);
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

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::ProgramHandle m_program;
	int64_t m_timeOffset;
	bool m_occlusionQuerySupported;

	bgfx::OcclusionQueryHandle m_occlusionQueries[CUBES_DIM*CUBES_DIM];

	entry::WindowState m_state;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleOcclusion, "26-occlusion", "Using occlusion query for conditional rendering.");
