/*
 * Copyright 2022-2022 Preetish Kakkar. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <cstdlib>

#include <bx/allocator.h>
#include <bx/debug.h>
#include <bx/math.h>
#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{
	struct PosTextCoord0Vertex
	{
		float m_x;
		float m_y;
		float m_z;
		float m_u;
		float m_v;

		static void init()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.end();
		}

		static bgfx::VertexLayout ms_layout;
	};

	bgfx::VertexLayout PosTextCoord0Vertex::ms_layout;


	static PosTextCoord0Vertex s_screenSpaceQuadVertices[] =
	{
		{-1.0f, 0.0f, -1.0f, 0.0, 0.0 },
		{-1.0f, 0.0f, 1.0f, 0.0, 1.0  },
		{ 1.0f, 0.0f, -1.0f, 1.0, 0.0  },
		{ 1.0f, 0.0f, 1.0f, 1.0, 1.0  },
	};

	static const uint16_t s_screenSpaceQuadIndices[] =
	{
		2, 3, 1,
		0, 2, 1,
	};


	struct HextileData
	{
		bool    m_showWeights;
		bool	m_pauseAnimation;
	};

	class ExampleHextile : public entry::AppI
	{
	public:
		ExampleHextile(const char* _name, const char* _description, const char* _url)
			: entry::AppI(_name, _description, _url)
			, m_width(0)
			, m_height(0)
			, m_debug(BGFX_DEBUG_NONE)
			, m_reset()
		{
		}

		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
		{
			Args args(_argc, _argv);

			m_width = _width;
			m_height = _height;
			m_debug = BGFX_DEBUG_NONE;
			m_reset = BGFX_RESET_VSYNC;

			bgfx::Init init;
			init.type = args.m_type;
			init.vendorId = args.m_pciId;
			init.platformData.nwh = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
			init.platformData.ndt = entry::getNativeDisplayHandle();
			init.resolution.width = m_width;
			init.resolution.height = m_height;
			init.resolution.reset = m_reset;
			bgfx::init(init);

			// Enable m_debug text.
			bgfx::setDebug(m_debug);

			// Set view 0 clear state.
			bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
			);

			m_hexTileData.m_showWeights = false;
			m_hexTileData.m_pauseAnimation = false;

			// Create vertex stream declaration.
			PosTextCoord0Vertex::init();

			// Create static vertex buffer.
			m_vbh = bgfx::createVertexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_screenSpaceQuadVertices, sizeof(s_screenSpaceQuadVertices))
				, PosTextCoord0Vertex::ms_layout
			);

			// Create static index buffer
			m_ibh = bgfx::createIndexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_screenSpaceQuadIndices, sizeof(s_screenSpaceQuadIndices))
			);

			// Create program from shaders.
			m_hextileProgram = loadProgram("vs_hextile", "fs_hextile");

			// load texture to hextile
			m_tileTexture = loadTexture("textures/Nature_Pebbles_4K.png");

			// Imgui.
			imguiCreate();

			m_timeOffset = bx::getHPCounter();

			s_tileSampler = bgfx::createUniform("s_trx_d", bgfx::UniformType::Sampler);

			bx::mtxSRT(m_modelTransform, 30, 30, 30, 0.0, 0.0, 0.0f, 0.0f, 0.0f, 0.0f);

			bx::mtxProj(m_projMtx, 30.0f, float(m_width) / float(m_height), 0.1f, 1000.0f, bgfx::getCaps()->homogeneousDepth);

			u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, 3);
		}

		virtual int shutdown() override
		{
			// Cleanup.
			imguiDestroy();

			if (bgfx::isValid(m_ibh))
			{
				bgfx::destroy(m_ibh);
			}

			if (bgfx::isValid(m_vbh))
			{
				bgfx::destroy(m_vbh);
			}

			if (bgfx::isValid(m_tileTexture))
			{
				bgfx::destroy(m_tileTexture);
			}

			if (bgfx::isValid(s_tileSampler))
			{
				bgfx::destroy(s_tileSampler);
			}

			bgfx::destroy(m_hextileProgram);

			/// When data is passed to bgfx via makeRef we need to make
			/// sure library is done with it before freeing memory blocks.
			bgfx::frame();


			// Shutdown bgfx.
			bgfx::shutdown();

			return 0;
		}

		bool update() override
		{
			if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			{
				int64_t now = bx::getHPCounter();
				static int64_t last = now;
				const int64_t frameTime = now - last;
				last = now;
				const double freq = double(bx::getHPFrequency());
				const float deltaTime = float(frameTime / freq);

				imguiBeginFrame(m_mouseState.m_mx
					, m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					, m_mouseState.m_mz
					, uint16_t(m_width)
					, uint16_t(m_height)
				);

				showExampleDialog(this);

				ImGui::SetNextWindowPos(
					ImVec2(m_width - m_width / 7.0f - 10.0f, 10.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::SetNextWindowSize(
					ImVec2(m_width / 7.0f, m_height / 7.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::Begin("Settings"
					, NULL
					, 0
				);

				ImGui::Separator();

				ImGui::Checkbox("Show Weights", &m_hexTileData.m_showWeights);
				ImGui::Checkbox("Pause Animation", &m_hexTileData.m_pauseAnimation);

				ImGui::End();
				imguiEndFrame();

				// This dummy draw call is here to make sure that view 0 is cleared
				// if no other draw calls are submitted to view 0.
				bgfx::touch(0);

				const bx::Vec3 at = { 0.0f, 0.0f, 0.0f };

				if (!m_hexTileData.m_pauseAnimation)
				{
					m_eye.z = std::abs(m_eye.z) + (deltaTime / 4.0f);

					if (m_eye.z < 4.0f)
					{
						m_eye.z *= -1;
					}
					else
					{
						m_eye.z = -0.01f;
					}
				}

				bx::mtxLookAt(m_viewMtx, m_eye, at);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				bgfx::setViewTransform(0, m_viewMtx, m_projMtx);
				bgfx::setTransform(m_modelTransform);

				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setIndexBuffer(m_ibh);

				bgfx::setTexture(0, s_tileSampler, m_tileTexture);

				const float data[4] = { float(m_hexTileData.m_showWeights) };
				bgfx::setUniform(u_params, data);

				bgfx::submit(0, m_hextileProgram);

				// Advance to next frame. Rendering thread will be kicked to
				// process submitted rendering primitives.
				bgfx::frame();

				return true;
			}

			return false;
		}

		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle m_ibh;


		bgfx::ProgramHandle m_hextileProgram;
		bgfx::UniformHandle s_tileSampler;
		bgfx::TextureHandle m_tileTexture;


		float m_modelTransform[16];

		float m_viewMtx[16];
		float m_projMtx[16];

		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_debug;
		uint32_t m_reset;

		HextileData m_hexTileData;

		entry::MouseState m_mouseState;

		bgfx::UniformHandle u_params;

		int64_t m_timeOffset;

		bx::Vec3 m_eye = { 0.0f, 2.0f, -0.01f };
	};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	ExampleHextile
	, "49-hextile"
	, "Hextile example."
	, "https://bkaradzic.github.io/bgfx/examples.html#hextile"
);
