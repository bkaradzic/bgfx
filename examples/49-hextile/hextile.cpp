/*
 * Copyright 2022-2022 Preetish Kakkar. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

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
		{-1.0f, 0.0f,  1.0f, 0.0, 1.0 },
		{ 1.0f, 0.0f, -1.0f, 1.0, 0.0 },
		{ 1.0f, 0.0f,  1.0f, 1.0, 1.0 },
	};

	static const uint16_t s_screenSpaceQuadIndices[] =
	{
		2, 3, 1,
		0, 2, 1,
	};


	struct HextileData
	{
		bool    m_showWeights = false;
		int		m_tileRate = 10;
		float	m_tileRotationStrength = 0.0f;
		bool	m_useRegularTiling = false;
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
		init.platformData.type = entry::getNativeWindowHandleType();
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
			m_tileTexture = loadTexture("textures/aerial_rocks_04_diff_2k.ktx");

			// Imgui.
			imguiCreate();

			m_timeOffset = bx::getHPCounter();

			s_tileSampler = bgfx::createUniform("s_trx_d", bgfx::UniformType::Sampler);

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

			if (bgfx::isValid(u_params))
			{
				bgfx::destroy(u_params);
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
					ImVec2(m_width - m_width / 4.5f - 5.0f, 10.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::SetNextWindowSize(
					ImVec2(m_width / 4.5f, m_height / 4.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::Begin("Settings"
					, NULL
					, 0
				);

				ImGui::Separator();

				ImGui::Checkbox("Use Regular Tiling", &m_hexTileData.m_useRegularTiling);
				ImGui::Checkbox("Show Weights", &m_hexTileData.m_showWeights);
				ImGui::Checkbox("Pause Animation", &m_hexTileData.m_pauseAnimation);

				ImGui::SliderInt("Tile Rate", &m_hexTileData.m_tileRate, 2, 25);

				ImGui::SliderFloat("Tile Rotation", &m_hexTileData.m_tileRotationStrength, 0.0f, 20.0f);

				ImGui::Separator();

				ImGui::End();
				imguiEndFrame();

				// This dummy draw call is here to make sure that view 0 is cleared
				// if no other draw calls are submitted to view 0.
				bgfx::touch(0);

				const bx::Vec3 at = { 0.0f, 0.0f, 0.0f };

				if (!m_hexTileData.m_pauseAnimation)
				{
					m_eye.z = bx::abs(m_eye.z) + (deltaTime / 4.0f);

					if (m_eye.z < 10.0f)
					{
						m_eye.z *= -1;
					}
					else
					{
						m_eye.z = -0.01f;
					}
				}

				float viewMtx[16];
				bx::mtxLookAt(viewMtx, m_eye, at);

				float projMtx[16];
				bx::mtxProj(projMtx, 30.0f, float(m_width) / float(m_height), 0.1f, 1000.0f, bgfx::getCaps()->homogeneousDepth);

				bgfx::setViewTransform(0, viewMtx, projMtx);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				float modelTransform[16];
				bx::mtxSRT(modelTransform, 30.0f, 30.0f, 30.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
				bgfx::setTransform(modelTransform);

				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setIndexBuffer(m_ibh);

				bgfx::setTexture(0, s_tileSampler, m_tileTexture);

				const float data[4] = { float(m_hexTileData.m_showWeights), float(m_hexTileData.m_tileRate),
										float(m_hexTileData.m_tileRotationStrength), float(m_hexTileData.m_useRegularTiling) };
				bgfx::setUniform(u_params, data);

				bgfx::setState(0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					| BGFX_STATE_WRITE_Z
					| BGFX_STATE_DEPTH_TEST_LESS
					| BGFX_STATE_MSAA
				);

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
