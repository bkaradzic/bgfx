/*
* Copyright 2014 Stanlo Slasinski. All rights reserved.
* License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
*/

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"
#include <bgfx/bgfx.h>

namespace
{

static const char* s_shapeNames[] =
{
	"Point",
	"Sphere",
	"Box",
	"Donut"
};

struct ParamsData
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

void initializeParams(int32_t _mode, ParamsData* _params)
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

const uint32_t kThreadGroupUpdateSize = 512;
const uint32_t kMaxParticleCount      = 32 * 1024;

class ExampleNbody : public entry::AppI
{
public:
	ExampleNbody(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
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

		const bgfx::Caps* caps = bgfx::getCaps();
		m_computeSupported  = !!(caps->supported & BGFX_CAPS_COMPUTE);
		m_indirectSupported = !!(caps->supported & BGFX_CAPS_DRAW_INDIRECT);

		imguiCreate();

		if (m_computeSupported)
		{
			bgfx::VertexDecl quadVertexDecl;
			quadVertexDecl.begin()
				.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
				.end();

			// Create static vertex buffer.
			m_vbh = bgfx::createVertexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_quadVertices, sizeof(s_quadVertices) )
				, quadVertexDecl
				);

			// Create static index buffer.
			m_ibh = bgfx::createIndexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_quadIndices, sizeof(s_quadIndices) )
				);

			// Create particle program from shaders.
			m_particleProgram = loadProgram("vs_particle", "fs_particle");

			// Setup compute buffers
			bgfx::VertexDecl computeVertexDecl;
			computeVertexDecl.begin()
				.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float)
				.end();

			m_currPositionBuffer0 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);
			m_currPositionBuffer1 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);
			m_prevPositionBuffer0 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);
			m_prevPositionBuffer1 = bgfx::createDynamicVertexBuffer(1 << 15, computeVertexDecl, BGFX_BUFFER_COMPUTE_READ_WRITE);

			u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, 3);

			m_initInstancesProgram   = bgfx::createProgram(loadShader("cs_init_instances"), true);
			m_updateInstancesProgram = bgfx::createProgram(loadShader("cs_update_instances"), true);

			m_indirectProgram = BGFX_INVALID_HANDLE;
			m_indirectBuffer  = BGFX_INVALID_HANDLE;

			if (m_indirectSupported)
			{
				m_indirectProgram = bgfx::createProgram(loadShader("cs_indirect"), true);
				m_indirectBuffer  = bgfx::createIndirectBuffer(2);
			}

			initializeParams(0, &m_paramsData);

			bgfx::setUniform(u_params, &m_paramsData, 3);
			bgfx::setBuffer(0, m_prevPositionBuffer0, bgfx::Access::Write);
			bgfx::setBuffer(1, m_currPositionBuffer0, bgfx::Access::Write);
			bgfx::dispatch(0, m_initInstancesProgram, kMaxParticleCount / kThreadGroupUpdateSize, 1, 1);

			float initialPos[3] = { 0.0f, 0.0f, -45.0f };
			cameraCreate();
			cameraSetPosition(initialPos);
			cameraSetVerticalAngle(0.0f);

			m_useIndirect = false;

			m_timeOffset = bx::getHPCounter();
		}
	}

	virtual int shutdown() override
	{
		// Cleanup.
		cameraDestroy();
		imguiDestroy();

		if (m_computeSupported)
		{
			if (m_indirectSupported)
			{
				bgfx::destroy(m_indirectProgram);
				bgfx::destroy(m_indirectBuffer);
			}

			bgfx::destroy(u_params);
			bgfx::destroy(m_currPositionBuffer0);
			bgfx::destroy(m_currPositionBuffer1);
			bgfx::destroy(m_prevPositionBuffer0);
			bgfx::destroy(m_prevPositionBuffer1);
			bgfx::destroy(m_updateInstancesProgram);
			bgfx::destroy(m_initInstancesProgram);
			bgfx::destroy(m_ibh);
			bgfx::destroy(m_vbh);
			bgfx::destroy(m_particleProgram);
		}

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(
				   m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this
				, !m_computeSupported
				? "Compute is not supported."
				: NULL
				);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const float deltaTime = float(frameTime/freq);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			if (m_computeSupported)
			{
				ImGui::SetNextWindowPos(
					  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
					, ImGuiCond_FirstUseEver
					);
				ImGui::SetNextWindowSize(
					  ImVec2(m_width / 5.0f, m_height / 1.5f)
					, ImGuiCond_FirstUseEver
					);
				ImGui::Begin("Settings"
					, NULL
					, 0
					);

				bool    reset = false;
				int32_t shape = m_paramsData.initialShape;
				if (ImGui::Combo("Initial shape", &shape, s_shapeNames, BX_COUNTOF(s_shapeNames) ) )
				{
					// Modify parameters and reset if shape is changed
					initializeParams(shape, &m_paramsData);
					reset = true;
				}

				ImGui::SliderInt("Random seed", &m_paramsData.baseSeed, 0, 100);

				if (ImGui::Button("Reset") )
				{
					reset = true;
				}

				ImGui::Separator();

				ImGui::SliderInt("Particle count (x512)", &m_paramsData.dispatchSize, 1, 64);
				ImGui::SliderFloat("Gravity", &m_paramsData.gravity, 0.0f, 0.3f);
				ImGui::SliderFloat("Damping", &m_paramsData.damping, 0.0f, 1.0f);
				ImGui::SliderFloat("Max acceleration", &m_paramsData.maxAccel, 0.0f, 100.0f);
				ImGui::SliderFloat("Time step", &m_paramsData.timeStep, 0.0f, 0.02f);

				ImGui::Separator();

				ImGui::SliderFloat("Particle intensity", &m_paramsData.particleIntensity, 0.0f, 1.0f);
				ImGui::SliderFloat("Particle size", &m_paramsData.particleSize, 0.0f, 1.0f);
				ImGui::SliderFloat("Particle power", &m_paramsData.particlePower, 0.001f, 16.0f);

				ImGui::Separator();

				if (m_indirectSupported)
				{
					ImGui::Checkbox("Use draw/dispatch indirect", &m_useIndirect);
				}

				ImGui::End();

				if (reset)
				{
					bgfx::setBuffer(0, m_prevPositionBuffer0, bgfx::Access::Write);
					bgfx::setBuffer(1, m_currPositionBuffer0, bgfx::Access::Write);
					bgfx::setUniform(u_params, &m_paramsData, 3);
					bgfx::dispatch(0, m_initInstancesProgram, kMaxParticleCount / kThreadGroupUpdateSize, 1, 1);
				}

				if (m_useIndirect)
				{
					bgfx::setUniform(u_params, &m_paramsData, 3);
					bgfx::setBuffer(0, m_indirectBuffer, bgfx::Access::Write);
					bgfx::dispatch(0, m_indirectProgram);
				}

				bgfx::setBuffer(0, m_prevPositionBuffer0, bgfx::Access::Read);
				bgfx::setBuffer(1, m_currPositionBuffer0, bgfx::Access::Read);
				bgfx::setBuffer(2, m_prevPositionBuffer1, bgfx::Access::Write);
				bgfx::setBuffer(3, m_currPositionBuffer1, bgfx::Access::Write);
				bgfx::setUniform(u_params, &m_paramsData, 3);

				if (m_useIndirect)
				{
					bgfx::dispatch(0, m_updateInstancesProgram, m_indirectBuffer, 1);
				}
				else
				{
					bgfx::dispatch(0, m_updateInstancesProgram, uint16_t(m_paramsData.dispatchSize), 1, 1);
				}

				bx::xchg(m_currPositionBuffer0, m_currPositionBuffer1);
				bx::xchg(m_prevPositionBuffer0, m_prevPositionBuffer1);

				// Update camera.
				cameraUpdate(deltaTime, m_mouseState);

				float view[16];
				cameraGetViewMtx(view);

				// Set view and projection matrix for view 0.
				{
					float proj[16];
					bx::mtxProj(
						  proj
						, 90.0f
						, float(m_width)/float(m_height)
						, 0.1f
						, 10000.0f
						, bgfx::getCaps()->homogeneousDepth
						);
					bgfx::setViewTransform(0, view, proj);

					// Set view 0 default viewport.
					bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				}

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setIndexBuffer(m_ibh);
				bgfx::setInstanceDataBuffer(m_currPositionBuffer0
					, 0
					, m_paramsData.dispatchSize * kThreadGroupUpdateSize
					);

				// Set render states.
				bgfx::setState(0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_BLEND_ADD
					| BGFX_STATE_DEPTH_TEST_ALWAYS
					);

				// Submit primitive for rendering to view 0.
				if (m_useIndirect)
				{
					bgfx::submit(0, m_particleProgram, m_indirectBuffer, 0);
				}
				else
				{
					bgfx::submit(0, m_particleProgram);
				}
			}

			imguiEndFrame();

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
	bool m_useIndirect;
	bool m_computeSupported;
	bool m_indirectSupported;

	ParamsData m_paramsData;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
	bgfx::ProgramHandle m_particleProgram;
	bgfx::ProgramHandle m_indirectProgram;
	bgfx::ProgramHandle m_initInstancesProgram;
	bgfx::ProgramHandle m_updateInstancesProgram;
	bgfx::IndirectBufferHandle m_indirectBuffer;
	bgfx::DynamicVertexBufferHandle m_currPositionBuffer0;
	bgfx::DynamicVertexBufferHandle m_currPositionBuffer1;
	bgfx::DynamicVertexBufferHandle m_prevPositionBuffer0;
	bgfx::DynamicVertexBufferHandle m_prevPositionBuffer1;
	bgfx::UniformHandle u_params;

	int64_t m_timeOffset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleNbody, "24-nbody", "N-body simulation with compute shaders using buffers.");
