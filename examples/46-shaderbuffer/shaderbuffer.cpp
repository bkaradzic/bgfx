/*
 * Copyright 2011-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{
	// Render passes
#define RENDER_PASS_POPULATE 0
#define RENDER_PASS_DRAW 1

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexLayout ms_layout;
};

struct InstanceData
{
	float m_transform[16];
	float m_color[4];
};

bgfx::VertexLayout PosColorVertex::ms_layout;

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

class ExampleShaderBuffer : public entry::AppI
{
public:
	ExampleShaderBuffer(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_STATS | BGFX_DEBUG_PROFILER;
		m_reset  = BGFX_RESET_VSYNC;
		m_useInstancing    = true;
		m_lastFrameMissing = 0;
		m_sideSize         = 11;

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
		bgfx::setViewClear(RENDER_PASS_DRAW
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
					, PosColorVertex::ms_layout
					);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(
					bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) )
					);


		m_sbh = bgfx::createShaderBuffer(512*512, sizeof(InstanceData), 0); // max side is 512

		// Create program from shaders.
		m_program_populate = loadProgram("cs_instance_data", nullptr);
		m_program = loadProgram("vs_explicit_instancing", "fs_explicit_instancing");
		m_program_non_instanced = loadProgram("vs_cubes", "fs_cubes");

		m_timeOffset = bx::getHPCounter();

		m_instanceData = bgfx::createUniform("s_instanceData", bgfx::UniformType::Sampler);
		m_instanceCount = bgfx::createUniform("u_instanceCount", bgfx::UniformType::Vec4);

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();

		// Cleanup.
		bgfx::destroy(m_sbh);
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program_populate);
		bgfx::destroy(m_program);
		bgfx::destroy(m_program_non_instanced);

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

			ImGui::SetNextWindowPos(
				ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
			);
			ImGui::SetNextWindowSize(
				ImVec2(m_width / 5.0f, m_height / 2.0f)
				, ImGuiCond_FirstUseEver
			);
			ImGui::Begin("Settings"
				, NULL
				, 0
			);

			// Get renderer capabilities info.
			const bgfx::Caps* caps = bgfx::getCaps();

			// Check if instancing is supported.
			const bool instancingSupported = 0 != (BGFX_CAPS_INSTANCING & caps->supported);
			m_useInstancing &= instancingSupported;

			ImGui::Text("%d draw calls", bgfx::getStats()->numDraw);

			ImGui::PushEnabled(instancingSupported);
			ImGui::Checkbox("Use Instancing", &m_useInstancing);
			ImGui::PopEnabled();

			ImGui::Text("Grid Side Size:");
			ImGui::SliderInt("", (int*)&m_sideSize, 1, 512);

			if (m_lastFrameMissing > 0)
			{
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Couldn't draw %d cubes last frame", m_lastFrameMissing);
			}

			if (bgfx::getStats()->numDraw >= bgfx::getCaps()->limits.maxDrawCalls)
			{
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Draw call limit reached!");
			}

			ImGui::End();

			imguiEndFrame();

			// Set view 0 default viewport.
			bgfx::setViewRect(RENDER_PASS_DRAW, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(RENDER_PASS_DRAW);

			float time = (float)( (bx::getHPCounter() - m_timeOffset)/double(bx::getHPFrequency() ) );

			if (!instancingSupported)
			{
				// When instancing is not supported by GPU, implement alternative
				// code path that doesn't use instancing.
				bool blink = uint32_t(time*3.0f)&1;
				bgfx::dbgTextPrintf(0, 0, blink ? 0x4f : 0x04, " Instancing is not supported by GPU. ");

				m_useInstancing = false;
			}

			const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -35.0f };

			// Set view and projection matrix for view 0.
			{
				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(RENDER_PASS_DRAW, view, proj);
			}

			m_lastFrameMissing = 0;

			if (m_useInstancing)
			{
				m_lastFrameMissing = 0;

				// view 0 - populate instance data via compute
				{
					float instanceCount[4];
					instanceCount[0] = m_sideSize;
					instanceCount[1] = time;
					instanceCount[2] = 0.f;
					instanceCount[3] = 0.f;

					uint16_t groupSize = 16;
					uint16_t groups = (m_sideSize + (groupSize - 1)) / groupSize;
					bgfx::setBuffer(0, m_instanceData, m_sbh, bgfx::Access::Write);
					bgfx::setUniform(m_instanceCount, instanceCount);
					bgfx::dispatch(RENDER_PASS_POPULATE, m_program_populate, groups, groups, 1);
				}

				// view 1 - draw instances
				{
					// Set vertex and index buffer.
					bgfx::setVertexBuffer(0, m_vbh);
					bgfx::setIndexBuffer(m_ibh);
					bgfx::setBuffer(0, m_instanceData, m_sbh, bgfx::Access::Read);
					bgfx::setInstanceCount(m_sideSize * m_sideSize);

					// Set render states.
					bgfx::setState(BGFX_STATE_DEFAULT);

					// Submit primitive for rendering to view 0.
					bgfx::submit(RENDER_PASS_DRAW, m_program);
				}
			}
			else
			{
				// non-instanced path
				for (uint32_t yy = 0; yy < m_sideSize; ++yy)
				{
					for (uint32_t xx = 0; xx < m_sideSize; ++xx)
					{
						float mtx[16];
						bx::mtxRotateXY(mtx, time + xx * 0.21f, time + yy * 0.37f);
						mtx[12] = -15.0f + float(xx) * 3.0f;
						mtx[13] = -15.0f + float(yy) * 3.0f;
						mtx[14] = 0.0f;

						// Set model matrix for rendering.
						bgfx::setTransform(mtx);

						// Set vertex and index buffer.
						bgfx::setVertexBuffer(0, m_vbh);
						bgfx::setIndexBuffer(m_ibh);

						// Set render states.
						bgfx::setState(BGFX_STATE_DEFAULT);

						// Submit primitive for rendering to view 0.
						bgfx::submit(RENDER_PASS_DRAW, m_program_non_instanced);
					}
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
	bool     m_useInstancing;
	uint32_t m_lastFrameMissing;
	uint32_t m_sideSize;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
	bgfx::ShaderBufferHandle m_sbh;
	bgfx::UniformHandle m_instanceData;
	bgfx::UniformHandle m_instanceCount;
	bgfx::ProgramHandle m_program_populate;
	bgfx::ProgramHandle m_program;
	bgfx::ProgramHandle m_program_non_instanced;

	bgfx::Memory* m_mem[2];

	int64_t m_timeOffset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleShaderBuffer
	, "46-shaderbuffer"
	, "Shader buffers."
	, "https://bkaradzic.github.io/bgfx/examples.html#instancing"
	);
