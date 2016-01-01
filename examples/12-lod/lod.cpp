/*
 * Copyright 2013 Milos Tosic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

#include <bx/readerwriter.h>

struct KnightPos
{
	int32_t m_x;
	int32_t m_y;
};

static const KnightPos knightTour[8*4] =
{
	{0,0}, {1,2}, {3,3}, {4,1}, {5,3}, {7,2}, {6,0}, {5,2},
	{7,3}, {6,1}, {4,0}, {3,2}, {2,0}, {0,1}, {1,3}, {2,1},
	{0,2}, {1,0}, {2,2}, {0,3}, {1,1}, {3,0}, {4,2}, {5,0},
	{7,1}, {6,3}, {5,1}, {7,0}, {6,2}, {4,3}, {3,1}, {2,3},
};

class Lod : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = 1280;
		m_height = 720;
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

		s_texColor   = bgfx::createUniform("s_texColor",   bgfx::UniformType::Int1);
		s_texStipple = bgfx::createUniform("s_texStipple", bgfx::UniformType::Int1);
		u_stipple    = bgfx::createUniform("u_stipple",    bgfx::UniformType::Vec4);

		m_program = loadProgram("vs_tree", "fs_tree");

		m_textureLeafs = loadTexture("leafs1.dds");
		m_textureBark  = loadTexture("bark1.dds");

		const bgfx::Memory* stippleTex = bgfx::alloc(8*4);
		memset(stippleTex->data, 0, stippleTex->size);

		for (uint32_t ii = 0; ii < 32; ++ii)
		{
			stippleTex->data[knightTour[ii].m_y * 8 + knightTour[ii].m_x] = ii*4;
		}

		m_textureStipple = bgfx::createTexture2D(8, 4, 1
			, bgfx::TextureFormat::R8
			, BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIN_POINT
			, stippleTex
			);

		m_meshTop[0] = meshLoad("meshes/tree1b_lod0_1.bin");
		m_meshTop[1] = meshLoad("meshes/tree1b_lod1_1.bin");
		m_meshTop[2] = meshLoad("meshes/tree1b_lod2_1.bin");

		m_meshTrunk[0] = meshLoad("meshes/tree1b_lod0_2.bin");
		m_meshTrunk[1] = meshLoad("meshes/tree1b_lod1_2.bin");
		m_meshTrunk[2] = meshLoad("meshes/tree1b_lod2_2.bin");

		// Imgui.
		imguiCreate();

		m_scrollArea  = 0;
		m_transitions = true;

		m_transitionFrame = 0;
		m_currLod         = 0;
		m_targetLod       = 0;
	}

	virtual int shutdown() BX_OVERRIDE
	{
		imguiDestroy();

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_meshTop); ++ii)
		{
			meshUnload(m_meshTop[ii]);
			meshUnload(m_meshTrunk[ii]);
		}

		// Cleanup.
		bgfx::destroyProgram(m_program);

		bgfx::destroyUniform(s_texColor);
		bgfx::destroyUniform(s_texStipple);
		bgfx::destroyUniform(u_stipple);

		bgfx::destroyTexture(m_textureStipple);
		bgfx::destroyTexture(m_textureLeafs);
		bgfx::destroyTexture(m_textureBark);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, m_width
				, m_height
				);

			imguiBeginScrollArea("Toggle transitions", m_width - m_width / 5 - 10, 10, m_width / 5, m_height / 6, &m_scrollArea);
			imguiSeparatorLine();

			if (imguiButton(m_transitions ? "ON" : "OFF") )
			{
				m_transitions = !m_transitions;
			}

			static float distance = 2.0f;
			imguiSlider("Distance", distance, 2.0f, 6.0f, 0.01f);

			imguiEndScrollArea();
			imguiEndFrame();

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, m_width, m_height);

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0/freq;

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/12-lod");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Mesh LOD transitions.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			float at[3]  = { 0.0f, 1.0f,      0.0f };
			float eye[3] = { 0.0f, 2.0f, -distance };

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
				// Use HMD's m_width/m_height since HMD's internal frame buffer size
				// might be much larger than window size.
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, m_width, m_height);
			}

			float mtx[16];
			bx::mtxScale(mtx, 0.1f, 0.1f, 0.1f);

			float stipple[3];
			float stippleInv[3];

			const int currentLODframe = m_transitions ? 32-m_transitionFrame : 32;
			const int mainLOD = m_transitions ? m_currLod : m_targetLod;

			stipple[0] = 0.0f;
			stipple[1] = -1.0f;
			stipple[2] = (float(currentLODframe)*4.0f/255.0f) - (1.0f/255.0f);

			stippleInv[0] = (float(31)*4.0f/255.0f);
			stippleInv[1] = 1.0f;
			stippleInv[2] = (float(m_transitionFrame)*4.0f/255.0f) - (1.0f/255.0f);

			const uint64_t stateTransparent = 0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_CULL_CCW
				| BGFX_STATE_MSAA
				| BGFX_STATE_BLEND_ALPHA
				;

			const uint64_t stateOpaque = BGFX_STATE_DEFAULT;

			bgfx::setTexture(0, s_texColor, m_textureBark);
			bgfx::setTexture(1, s_texStipple, m_textureStipple);
			bgfx::setUniform(u_stipple, stipple);
			meshSubmit(m_meshTrunk[mainLOD], 0, m_program, mtx, stateOpaque);

			bgfx::setTexture(0, s_texColor, m_textureLeafs);
			bgfx::setTexture(1, s_texStipple, m_textureStipple);
			bgfx::setUniform(u_stipple, stipple);
			meshSubmit(m_meshTop[mainLOD], 0, m_program, mtx, stateTransparent);

			if (m_transitions
			&& (m_transitionFrame != 0) )
			{
				bgfx::setTexture(0, s_texColor, m_textureBark);
				bgfx::setTexture(1, s_texStipple, m_textureStipple);
				bgfx::setUniform(u_stipple, stippleInv);
				meshSubmit(m_meshTrunk[m_targetLod], 0, m_program, mtx, stateOpaque);

				bgfx::setTexture(0, s_texColor, m_textureLeafs);
				bgfx::setTexture(1, s_texStipple, m_textureStipple);
				bgfx::setUniform(u_stipple, stippleInv);
				meshSubmit(m_meshTop[m_targetLod], 0, m_program, mtx, stateTransparent);
			}

			int lod = 0;
			if (eye[2] < -2.5f)
			{
				lod = 1;
			}

			if (eye[2] < -5.0f)
			{
				lod = 2;
			}

			if (m_targetLod != lod)
			{
				if (m_targetLod == m_currLod)
				{
					m_targetLod = lod;
				}
			}

			if (m_currLod != m_targetLod)
			{
				m_transitionFrame++;
			}

			if (m_transitionFrame > 32)
			{
				m_currLod = m_targetLod;
				m_transitionFrame = 0;
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

	Mesh* m_meshTop[3];
	Mesh* m_meshTrunk[3];

	bgfx::ProgramHandle m_program;
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texStipple;
	bgfx::UniformHandle u_stipple;

	bgfx::TextureHandle m_textureStipple;
	bgfx::TextureHandle m_textureLeafs;
	bgfx::TextureHandle m_textureBark;

	int32_t m_scrollArea;
	int32_t m_transitionFrame;
	int32_t m_currLod;
	int32_t m_targetLod;
	bool    m_transitions;
};

ENTRY_IMPLEMENT_MAIN(Lod);
