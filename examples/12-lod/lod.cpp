/*
 * Copyright 2013 Milos Tosic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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

KnightPos knightTour[8*4] =
{
	{0,0}, {1,2}, {3,3}, {4,1}, {5,3}, {7,2}, {6,0}, {5,2},
	{7,3}, {6,1}, {4,0}, {3,2}, {2,0}, {0,1}, {1,3}, {2,1},
	{0,2}, {1,0}, {2,2}, {0,3}, {1,1}, {3,0}, {4,2}, {5,0},
	{7,1}, {6,3}, {5,1}, {7,0}, {6,2}, {4,3}, {3,1}, {2,3},
};

int _main_(int /*_argc*/, char** /*_argv*/)
{
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();
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

	bgfx::UniformHandle s_texColor   = bgfx::createUniform("s_texColor",   bgfx::UniformType::Int1);
	bgfx::UniformHandle s_texStipple = bgfx::createUniform("s_texStipple", bgfx::UniformType::Int1);
	bgfx::UniformHandle u_stipple    = bgfx::createUniform("u_stipple",    bgfx::UniformType::Vec4);

	bgfx::ProgramHandle program = loadProgram("vs_tree", "fs_tree");

	bgfx::TextureHandle textureLeafs = loadTexture("leafs1.dds");
	bgfx::TextureHandle textureBark  = loadTexture("bark1.dds");

	bgfx::TextureHandle textureStipple;

	const bgfx::Memory* stippleTex = bgfx::alloc(8*4);
	memset(stippleTex->data, 0, stippleTex->size);

	for (uint32_t ii = 0; ii < 32; ++ii)
	{
		stippleTex->data[knightTour[ii].m_y * 8 + knightTour[ii].m_x] = ii*4;
	}

	textureStipple = bgfx::createTexture2D(8, 4, 1
			, bgfx::TextureFormat::R8
			, BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIN_POINT
			, stippleTex
			);

	Mesh* meshTop[3] =
	{
		meshLoad("meshes/tree1b_lod0_1.bin"),
		meshLoad("meshes/tree1b_lod1_1.bin"),
		meshLoad("meshes/tree1b_lod2_1.bin"),
	};

	Mesh* meshTrunk[3] =
	{
		meshLoad("meshes/tree1b_lod0_2.bin"),
		meshLoad("meshes/tree1b_lod1_2.bin"),
		meshLoad("meshes/tree1b_lod2_2.bin"),
	};

	// Imgui.
	imguiCreate();

	const uint64_t stateCommon = 0
		| BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		;

	const uint64_t stateTransparent = stateCommon
		| BGFX_STATE_BLEND_ALPHA
		;

	const uint64_t stateOpaque = stateCommon
		| BGFX_STATE_DEPTH_WRITE
		;

	int32_t scrollArea = 0;

	bool transitions = true;
	int transitionFrame = 0;
	int currLOD = 0;
	int targetLOD = 0;

	float at[3] = { 0.0f, 1.0f, 0.0f };
	float eye[3] = { 0.0f, 1.0f, -2.0f };

	entry::MouseState mouseState;
	while (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
			, mouseState.m_mz
			, width
			, height
			);

		imguiBeginScrollArea("Toggle transitions", width - width / 5 - 10, 10, width / 5, height / 6, &scrollArea);
		imguiSeparatorLine();

		if (imguiButton(transitions ? "ON" : "OFF") )
		{
			transitions = !transitions;
		}

		static float distance = 2.0f;
		imguiSlider("Distance", distance, 2.0f, 6.0f, .01f);

		imguiEndScrollArea();
		imguiEndFrame();

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

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/12-lod");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Mesh LOD transitions.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);
		bgfx::dbgTextPrintf(0, 4, transitions ? 0x2f : 0x1f, transitions ? "Transitions on" : "Transitions off");

		eye[2] = -distance;

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

		float mtx[16];
		bx::mtxScale(mtx, 0.1f, 0.1f, 0.1f);

		float stipple[3];
		float stippleInv[3];

		const int currentLODframe = transitions ? 32-transitionFrame : 32;
		const int mainLOD = transitions ? currLOD : targetLOD;

		stipple[0] = 0.0f;
		stipple[1] = -1.0f;
		stipple[2] = (float(currentLODframe)*4.0f/255.0f) - (1.0f/255.0f);

		stippleInv[0] = (float(31)*4.0f/255.0f);
		stippleInv[1] = 1.0f;
		stippleInv[2] = (float(transitionFrame)*4.0f/255.0f) - (1.0f/255.0f);

		bgfx::setTexture(0, s_texColor, textureBark);
		bgfx::setTexture(1, s_texStipple, textureStipple);
		bgfx::setUniform(u_stipple, stipple);
		meshSubmit(meshTrunk[mainLOD], 0, program, mtx, stateOpaque);

		bgfx::setTexture(0, s_texColor, textureLeafs);
		bgfx::setTexture(1, s_texStipple, textureStipple);
		bgfx::setUniform(u_stipple, stipple);
		meshSubmit(meshTop[mainLOD], 0, program, mtx, stateTransparent);

		if (transitions
		&& (transitionFrame != 0) )
		{
			bgfx::setTexture(0, s_texColor, textureBark);
			bgfx::setTexture(1, s_texStipple, textureStipple);
			bgfx::setUniform(u_stipple, stippleInv);
			meshSubmit(meshTrunk[targetLOD], 0, program, mtx, stateOpaque);

			bgfx::setTexture(0, s_texColor, textureLeafs);
			bgfx::setTexture(1, s_texStipple, textureStipple);
			bgfx::setUniform(u_stipple, stippleInv);
			meshSubmit(meshTop[targetLOD], 0, program, mtx, stateTransparent);
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

		if (targetLOD!=lod)
		{
			if (targetLOD==currLOD)
			{
				targetLOD = lod;
			}
		}

		if (currLOD != targetLOD)
		{
			transitionFrame++;
		}

		if (transitionFrame>32)
		{
			currLOD = targetLOD;
			transitionFrame = 0;
		}

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	imguiDestroy();

	for (uint32_t ii = 0; ii < 3; ++ii)
	{
		meshUnload(meshTop[ii]);
		meshUnload(meshTrunk[ii]);
	}

	// Cleanup.
	bgfx::destroyProgram(program);

	bgfx::destroyUniform(s_texColor);
	bgfx::destroyUniform(s_texStipple);
	bgfx::destroyUniform(u_stipple);

	bgfx::destroyTexture(textureStipple);
	bgfx::destroyTexture(textureLeafs);
	bgfx::destroyTexture(textureBark);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
