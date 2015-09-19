/*
* Copyright 2014 Stanlo Slasinski. All rights reserved.
* License: http://www.opensource.org/licenses/BSD-2-Clause
*/

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"
#include <bgfx/bgfx.h>

struct u_paramsDataStruct
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
};

void InitializeParams(int32_t _mode, u_paramsDataStruct* _params)
{
	switch(_mode)
	{
	case 0:
		_params->timeStep          = 0.0067f;
		_params->dispatchSize      = 32;
		_params->gravity           = 0.069f;
		_params->damping           = 0.0f;
		_params->particleIntensity = 0.35f;
		_params->particleSize      = 0.925f;
		_params->baseSeed          = 0;
		_params->particlePower     = 5.0f;
		_params->initialSpeed      = 122.6f;
		_params->initialShape      = 0;
		_params->maxAccel          = 30.0;
		break;

	case 1:
		_params->timeStep          = 0.0157f;
		_params->dispatchSize      = 32;
		_params->gravity           = 0.109f;
		_params->damping           = 0.25f;
		_params->particleIntensity = 0.64f;
		_params->particleSize      = 0.279f;
		_params->baseSeed          = 57;
		_params->particlePower     = 3.5f;
		_params->initialSpeed      = 3.2f;
		_params->initialShape      = 1;
		_params->maxAccel          = 100.0;
		break;

	case 2:
		_params->timeStep          = 0.02f;
		_params->dispatchSize      = 32;
		_params->gravity           = 0.24f;
		_params->damping           = 0.12f;
		_params->particleIntensity = 1.0f;
		_params->particleSize      = 1.0f;
		_params->baseSeed          = 23;
		_params->particlePower     = 4.0f;
		_params->initialSpeed      = 31.1f;
		_params->initialShape      = 2;
		_params->maxAccel          = 39.29f;
		break;

	case 3:
		_params->timeStep          = 0.0118f;
		_params->dispatchSize      = 32;
		_params->gravity           = 0.141f;
		_params->damping           = 1.0f;
		_params->particleIntensity = 0.64f;
		_params->particleSize      = 0.28f;
		_params->baseSeed          = 60;
		_params->particlePower     = 1.97f;
		_params->initialSpeed      = 69.7f;
		_params->initialShape      = 3;
		_params->maxAccel          = 3.21f;
		break;
	}
}

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
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	const bgfx::Caps* caps = bgfx::getCaps();
	const bool computeSupported  = !!(caps->supported & BGFX_CAPS_COMPUTE);
	const bool indirectSupported = !!(caps->supported & BGFX_CAPS_DRAW_INDIRECT);

	if (computeSupported)
	{
		// Imgui.
		imguiCreate();

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
		const uint32_t maxParticleCount = 32 * 1024;

		bgfx::DynamicVertexBufferHandle currPositionBuffer0 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);
		bgfx::DynamicVertexBufferHandle currPositionBuffer1 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);
		bgfx::DynamicVertexBufferHandle prevPositionBuffer0 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);
		bgfx::DynamicVertexBufferHandle prevPositionBuffer1 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);

		bgfx::UniformHandle u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, 3);

		bgfx::ProgramHandle initInstancesProgram   = bgfx::createProgram(loadShader("cs_init_instances"), true);
		bgfx::ProgramHandle updateInstancesProgram = bgfx::createProgram(loadShader("cs_update_instances"), true);

		bgfx::ProgramHandle indirectProgram       = BGFX_INVALID_HANDLE;
		bgfx::IndirectBufferHandle indirectBuffer = BGFX_INVALID_HANDLE;

		if (indirectSupported)
		{
			indirectProgram = bgfx::createProgram(loadShader("cs_indirect"), true);
			indirectBuffer  = bgfx::createIndirectBuffer(2);
		}

		u_paramsDataStruct u_paramsData;
		InitializeParams(0, &u_paramsData);

		bgfx::setUniform(u_params, &u_paramsData, 3);
		bgfx::setBuffer(0, prevPositionBuffer0, bgfx::Access::Write);
		bgfx::setBuffer(1, currPositionBuffer0, bgfx::Access::Write);
		bgfx::dispatch(0, initInstancesProgram, maxParticleCount / threadGroupUpdateSize, 1, 1);

		float view[16];
		float initialPos[3] = { 0.0f, 0.0f, -45.0f };
		cameraCreate();
		cameraSetPosition(initialPos);
		cameraSetVerticalAngle(0.0f);
		cameraGetViewMtx(view);

		int32_t scrollArea = 0;

		bool useIndirect = false;

		entry::MouseState mouseState;
		while (!entry::processEvents(width, height, debug, reset, &mouseState) )
		{
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const float deltaTime = float(frameTime/freq);

			if (deltaTime > 1000.0)
			{
				abort();
			}

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, width, height);

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/24-nbody");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: N-body simulation with compute shaders using buffers.");

			imguiBeginFrame(mouseState.m_mx
					, mouseState.m_my
					, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
					| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
					| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					, mouseState.m_mz
					, width
					, height
					);
			imguiBeginScrollArea("Settings", width - width / 4 - 10, 10, width / 4, 500, &scrollArea);
			imguiSlider("Random seed", u_paramsData.baseSeed, 0, 100);
			int32_t shape = imguiChoose(u_paramsData.initialShape, "Point", "Sphere", "Box", "Donut");
			imguiSlider("Initial speed", u_paramsData.initialSpeed, 0.0f, 300.0f, 0.1f);
			bool defaults = imguiButton("Reset");
			imguiSeparatorLine();
			imguiSlider("Particle count (x512)", u_paramsData.dispatchSize, 1, 64);
			imguiSlider("Gravity", u_paramsData.gravity, 0.0f, 0.3f, 0.001f);
			imguiSlider("Damping", u_paramsData.damping, 0.0f, 1.0f, 0.01f);
			imguiSlider("Max acceleration", u_paramsData.maxAccel, 0.0f, 100.0f, 0.01f);
			imguiSlider("Time step", u_paramsData.timeStep, 0.0f, 0.02f, 0.0001f);
			imguiSeparatorLine();
			imguiSlider("Particle intensity", u_paramsData.particleIntensity, 0.0f, 1.0f, 0.001f);
			imguiSlider("Particle size", u_paramsData.particleSize, 0.0f, 1.0f, 0.001f);
			imguiSlider("Particle power", u_paramsData.particlePower, 0.001f, 16.0f, 0.01f);
			imguiSeparatorLine();
			if (imguiCheck("Use draw/dispatch indirect", useIndirect, indirectSupported) )
			{
				useIndirect = !useIndirect;
			}
			imguiEndScrollArea();
			imguiEndFrame();

			// Modify parameters and reset if shape is changed
			if (shape != u_paramsData.initialShape)
			{
				defaults = true;
				InitializeParams(shape, &u_paramsData);
			}

			if (defaults)
			{
				bgfx::setBuffer(0, prevPositionBuffer0, bgfx::Access::Write);
				bgfx::setBuffer(1, currPositionBuffer0, bgfx::Access::Write);
				bgfx::setUniform(u_params, &u_paramsData, 3);
				bgfx::dispatch(0, initInstancesProgram, maxParticleCount / threadGroupUpdateSize, 1, 1);
			}

			if (useIndirect)
			{
				bgfx::setUniform(u_params, &u_paramsData, 3);
				bgfx::setBuffer(0, indirectBuffer, bgfx::Access::Write);
				bgfx::dispatch(0, indirectProgram);
			}

			bgfx::setBuffer(0, prevPositionBuffer0, bgfx::Access::Read);
			bgfx::setBuffer(1, currPositionBuffer0, bgfx::Access::Read);
			bgfx::setBuffer(2, prevPositionBuffer1, bgfx::Access::Write);
			bgfx::setBuffer(3, currPositionBuffer1, bgfx::Access::Write);
			bgfx::setUniform(u_params, &u_paramsData, 3);

			if (useIndirect)
			{
				bgfx::dispatch(0, updateInstancesProgram, indirectBuffer, 1);
			}
			else
			{
				bgfx::dispatch(0, updateInstancesProgram, u_paramsData.dispatchSize, 1, 1);
			}

			bx::xchg(currPositionBuffer0, currPositionBuffer1);
			bx::xchg(prevPositionBuffer0, prevPositionBuffer1);

			// Update camera.
			cameraUpdate(deltaTime, mouseState);
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

				float proj[16];
				bx::mtxProj(proj, hmd->eye[0].fov, 0.1f, 10000.0f);

				bgfx::setViewTransform(0, tmp, proj);

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
			if (useIndirect)
			{
				bgfx::submit(0, particleProgram, indirectBuffer, 0);
			}
			else
			{
				bgfx::submit(0, particleProgram);
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();
		}

		// Cleanup.
		cameraDestroy();
		imguiDestroy();

		if (indirectSupported)
		{
			bgfx::destroyProgram(indirectProgram);
			bgfx::destroyIndirectBuffer(indirectBuffer);
		}


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
	}
	else
	{
		int64_t timeOffset = bx::getHPCounter();

		entry::MouseState mouseState;
		while (!entry::processEvents(width, height, debug, reset, &mouseState) )
		{
			int64_t now = bx::getHPCounter();
			float time = (float)( (now - timeOffset)/double(bx::getHPFrequency() ) );

			bgfx::setViewRect(0, 0, 0, width, height);

			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/24-nbody");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: N-body simulation with compute shaders using buffers.");

			bool blink = uint32_t(time*3.0f)&1;
			bgfx::dbgTextPrintf(0, 5, blink ? 0x1f : 0x01, " Compute is not supported by GPU. ");

			bgfx::touch(0);
			bgfx::frame();
		}
	}

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
