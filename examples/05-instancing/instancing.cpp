/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

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

class ExampleInstancing : public entry::AppI
{
public:
	ExampleInstancing(const char* _name, const char* _description)
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

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

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

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
					  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
					, PosColorVertex::ms_decl
					);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(
					bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) )
					);

		// Create program from shaders.
		m_program = loadProgram("vs_instancing", "fs_instancing");

		m_timeOffset = bx::getHPCounter();

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();

		// Cleanup.
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

			showExampleDialog(this);

			imguiEndFrame();

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			float time = (float)( (bx::getHPCounter() - m_timeOffset)/double(bx::getHPFrequency() ) );

			// Get renderer capabilities info.
			const bgfx::Caps* caps = bgfx::getCaps();

			// Check if instancing is supported.
			if (0 == (BGFX_CAPS_INSTANCING & caps->supported) )
			{
				// When instancing is not supported by GPU, implement alternative
				// code path that doesn't use instancing.
				bool blink = uint32_t(time*3.0f)&1;
				bgfx::dbgTextPrintf(0, 0, blink ? 0x1f : 0x01, " Instancing is not supported by GPU. ");
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
					bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);

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
					bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
					bgfx::setViewTransform(0, view, proj);

					// Set view 0 default viewport.
					bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				}

				// 80 bytes stride = 64 bytes for 4x4 matrix + 16 bytes for RGBA color.
				const uint16_t instanceStride = 80;
				// 11x11 cubes
				const uint32_t numInstances   = 121;

				if (numInstances == bgfx::getAvailInstanceDataBuffer(numInstances, instanceStride) )
				{
					bgfx::InstanceDataBuffer idb;
					bgfx::allocInstanceDataBuffer(&idb, numInstances, instanceStride);

					uint8_t* data = idb.data;

					// Write instance data for 11x11 cubes.
					for (uint32_t yy = 0; yy < 11; ++yy)
					{
						for (uint32_t xx = 0; xx < 11; ++xx)
						{
							float* mtx = (float*)data;
							bx::mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
							mtx[12] = -15.0f + float(xx)*3.0f;
							mtx[13] = -15.0f + float(yy)*3.0f;
							mtx[14] = 0.0f;

							float* color = (float*)&data[64];
							color[0] = bx::sin(time+float(xx)/11.0f)*0.5f+0.5f;
							color[1] = bx::cos(time+float(yy)/11.0f)*0.5f+0.5f;
							color[2] = bx::sin(time*3.0f)*0.5f+0.5f;
							color[3] = 1.0f;

							data += instanceStride;
						}
					}

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(0, m_vbh);
					bgfx::setIndexBuffer(m_ibh);

					// Set instance data buffer.
					bgfx::setInstanceDataBuffer(&idb);

					// Set render states.
					bgfx::setState(BGFX_STATE_DEFAULT);

					// Submit primitive for rendering to view 0.
					bgfx::submit(0, m_program);
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
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
	bgfx::ProgramHandle m_program;

	int64_t m_timeOffset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleInstancing, "05-instancing", "Geometry instancing.");
