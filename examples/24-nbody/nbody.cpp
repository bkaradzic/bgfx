/*
 * Copyright 2014 Stanlo Slasinski. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"
#include <bgfx.h>

static const float s_quadVertices[] = 
{ 
	 1.0f,  1.0f,
	-1.0f,  1.0f,
	-1.0f, -1.0f,
	 1.0f, -1.0f,
};

static const uint16_t s_quadIndices[] = { 0, 1, 2, 2, 3, 0, };

int _main_(int /*_argc*/, char** /*_argv*/)
{
	uint32_t width  = 1280;
	uint32_t height = 720;
	uint32_t debug  = BGFX_DEBUG_TEXT;
	uint32_t reset  = BGFX_RESET_VSYNC;

	bgfx::init();
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT
		, 0x303030ff
		, 1.0f
		, 0
		);

	void* data = load("font/droidsans.ttf");
	imguiCreate(data);
	free(data);

	bgfx::VertexDecl quadVertexDecl;
	quadVertexDecl.begin()
		.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
		.end();

	// Create static vertex buffer.
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_quadVertices, sizeof(s_quadVertices) )
		, quadVertexDecl
		);

	// Create static index buffer.
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_quadIndices, sizeof(s_quadIndices) )
		);

	// Create particle program from shaders.
	bgfx::ProgramHandle particleProgram = loadProgram("vs_particle", "fs_particle");

	// Setup compute buffers
	bgfx::VertexDecl computeVertexDecl;
	computeVertexDecl.begin()
		.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float)
		.end();

	const uint32_t threadGroupUpdateSize = 512;

	bgfx::DynamicVertexBufferHandle currPositionBuffer0 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);
	bgfx::DynamicVertexBufferHandle currPositionBuffer1 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);
	bgfx::DynamicVertexBufferHandle prevPositionBuffer0 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);
	bgfx::DynamicVertexBufferHandle prevPositionBuffer1 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);

	bgfx::UniformHandle u_params = bgfx::createUniform("u_params", bgfx::UniformType::Uniform4fv, 3);
	struct
	{
		float   timeStep;
		int32_t dispatchSize;
		float   gravity;
		float   damping;
		float   particleIntensity;
		float   particleSize;
		int32_t baseSeed;
		float   particlePower;
		float   initialSpeed;
		int32_t initialShape;
		float   maxAccel;

	} u_paramsData;

	u_paramsData.timeStep          = 0.0083f;
	u_paramsData.dispatchSize      = 16;
	u_paramsData.gravity           = 0.069f * 0.069f;
	u_paramsData.damping           = 0.07f;
	u_paramsData.particleIntensity = 0.35f;
	u_paramsData.particleSize      = 0.4f;
	u_paramsData.baseSeed          = 0;
	u_paramsData.particlePower     = 5.0f;
	u_paramsData.initialSpeed      = 85.0f; //112.0f;
	u_paramsData.initialShape      = 0;
	u_paramsData.maxAccel          = 30.0;

	float uiGravity = 0.069f;

	bgfx::ShaderHandle  initInstancesShader    = loadShader("cs_init_instances");
	bgfx::ProgramHandle initInstancesProgram   = bgfx::createProgram(initInstancesShader, true);
	bgfx::ShaderHandle  updateInstancesShader  = loadShader("cs_update_instances");
	bgfx::ProgramHandle updateInstancesProgram = bgfx::createProgram(updateInstancesShader, true);

	bgfx::setUniform(u_params, &u_paramsData, 3);
	bgfx::setBuffer(0, prevPositionBuffer0, bgfx::Access::Write);
	bgfx::setBuffer(1, currPositionBuffer0, bgfx::Access::Write);
	bgfx::dispatch(0, initInstancesProgram, (32 * threadGroupUpdateSize) / 1024, 1, 1);

	float view[16];
	float initialPos[3] = { 0.0f, 0.0f, -25.0f };
	cameraCreate();
	cameraSetPosition(initialPos);
	cameraSetVerticalAngle(0.0f);
	cameraGetViewMtx(view);

	int32_t scrollArea = 0;

	entry::MouseState mouseState;
	while (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const float deltaTime = float(frameTime/freq);

		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/24-nbody");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: N-body simulation with compute shaders using buffers.");

		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT : 0)
			, 0
			, width
			, height
			);
		imguiBeginScrollArea("Settings", width - width / 4 - 10, 10, width / 4, 500, &scrollArea);
		imguiSlider("Random seed", u_paramsData.baseSeed, 0, 100);
		u_paramsData.initialShape = imguiChoose(u_paramsData.initialShape, "Point", "Sphere", "Box", "Donut");
		imguiSlider("Initial speed", u_paramsData.initialSpeed, 0.0f, 300.0f, 0.1f);
		bool reset = imguiButton("Reset");
		imguiSeparatorLine();
		imguiSlider("Particle count (x1024)", u_paramsData.dispatchSize, 1, 32);
		imguiSlider("Gravity", uiGravity, 0.0f, 0.3f, 0.001f);
		imguiSlider("Damping", u_paramsData.damping, 0.0f, 1.0f, 0.01f);
		imguiSlider("Max acceleration", u_paramsData.maxAccel, 0.0f, 100.0f, 0.01f);
		imguiSlider("Time step", u_paramsData.timeStep, 0.0f, 0.02f, 0.0001f);
		imguiSeparatorLine();
		imguiSlider("Particle intensity", u_paramsData.particleIntensity, 0.0f, 1.0f, 0.001f);
		imguiSlider("Particle size", u_paramsData.particleSize, 0.0f, 1.0f, 0.001f);
		imguiSlider("Particle power", u_paramsData.particlePower, 0.001f, 16.0f, 0.01f);
		imguiEndScrollArea();
		imguiEndFrame();

		u_paramsData.gravity = uiGravity * uiGravity;

		float eye[3] = { 0.0f, 0.0f, -35.0f };
		float view[16];

		// Update camera.
		cameraUpdate(deltaTime, mouseState);
		cameraGetViewMtx(view);

		// Set view and projection matrix for view 0.
		const bgfx::HMD* hmd = bgfx::getHMD();
		if (NULL != hmd)
		{
			float view[16];
			bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);

			float proj[16];
			bx::mtxProj(proj, hmd->eye[0].fov, 0.1f, 10000.0f);

			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			//
			// Use HMD's width/height since HMD's internal frame buffer size
			// might be much larger than window size.
			bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
		}
		else
		{
			float proj[16];
			bx::mtxProj(proj, 90.0f, float(width)/float(height), 0.1f, 10000.0f);
			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, width, height);
		}

		// Update instances
		bgfx::setUniform(u_params, &u_paramsData, 3);
		
		if (reset)
		{
			bgfx::setBuffer(0, prevPositionBuffer0, bgfx::Access::Write);
			bgfx::setBuffer(1, currPositionBuffer0, bgfx::Access::Write);
			bgfx::dispatch(0, initInstancesProgram, (32 * threadGroupUpdateSize) / 1024, 1, 1);
		}

		bgfx::setBuffer(0, prevPositionBuffer0, bgfx::Access::Read);
		bgfx::setBuffer(1, currPositionBuffer0, bgfx::Access::Read);
		bgfx::setBuffer(2, prevPositionBuffer1, bgfx::Access::Write);
		bgfx::setBuffer(3, currPositionBuffer1, bgfx::Access::Write);
		bgfx::dispatch(0, updateInstancesProgram, u_paramsData.dispatchSize, 1, 1);

		bx::swap(currPositionBuffer0, currPositionBuffer1);
		bx::swap(prevPositionBuffer0, prevPositionBuffer1);

		// Set vertex and fragment shaders.
		bgfx::setProgram(particleProgram);

		// Set vertex and index buffer.
		bgfx::setVertexBuffer(vbh);
		bgfx::setIndexBuffer(ibh);
		bgfx::setInstanceDataBuffer(currPositionBuffer0, 0, u_paramsData.dispatchSize * threadGroupUpdateSize);

		// Set render states.
		bgfx::setState(0
			| BGFX_STATE_RGB_WRITE
			| BGFX_STATE_BLEND_ADD
			| BGFX_STATE_DEPTH_TEST_ALWAYS
			);

		// Submit primitive for rendering to view 0.
		bgfx::submit(0);

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	cameraDestroy();
	imguiDestroy();
	bgfx::destroyUniform(u_params);
	bgfx::destroyDynamicVertexBuffer(currPositionBuffer0);
	bgfx::destroyDynamicVertexBuffer(currPositionBuffer1);
	bgfx::destroyDynamicVertexBuffer(prevPositionBuffer0);
	bgfx::destroyDynamicVertexBuffer(prevPositionBuffer1);
	bgfx::destroyProgram(updateInstancesProgram);
	bgfx::destroyProgram(initInstancesProgram);
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(particleProgram);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
