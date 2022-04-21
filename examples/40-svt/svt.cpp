/*
 * Copyright 2018 Ales Mlakar. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

 /*
  * Reference(s):
  * - Sparse Virtual Textures by Sean Barrett
  *   http://web.archive.org/web/20190103162611/http://silverspaceship.com/src/svt/
  * - Based on Virtual Texture Demo by Brad Blanchard
  *   http://web.archive.org/web/20190103162638/http://linedef.com/virtual-texture-demo.html
  * - Mars texture
  *   http://web.archive.org/web/20190103162730/http://www.celestiamotherlode.net/catalog/mars.php
  */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"
#include "vt.h"

namespace
{

struct PosTexcoordVertex
{
	float    m_x;
	float    m_y;
	float    m_z;
	float    m_u;
	float    m_v;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	};

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosTexcoordVertex::ms_layout;

static const float s_planeScale = 50.0f;

static PosTexcoordVertex s_vplaneVertices[] =
{
	{ -s_planeScale, 0.0f,  s_planeScale, 1.0f, 1.0f },
	{  s_planeScale, 0.0f,  s_planeScale, 1.0f, 0.0f },
	{ -s_planeScale, 0.0f, -s_planeScale, 0.0f, 1.0f },
	{  s_planeScale, 0.0f, -s_planeScale, 0.0f, 0.0f },
};

static const uint16_t s_planeIndices[] =
{
	0, 1, 2,
	1, 3, 2,
};

class ExampleSVT : public entry::AppI
{
public:
	ExampleSVT(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width = _width;
		m_height = _height;
		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;

		bgfx::Init init;

		init.type = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width = m_width;
		init.resolution.height = m_height;
		init.resolution.reset = m_reset;
		bgfx::init(init);

		// Enable m_debug text.
		bgfx::setDebug(m_debug);

		// Set views clear state (first pass to 0, second pass to some background color)
		for (uint16_t i = 0; i < 2; ++i)
		{
			bgfx::setViewClear(i
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, i == 0 ? 0 : 0x101050ff
				, 1.0f
				, 0
			);
		}

		// Create vertex stream declaration.
		PosTexcoordVertex::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
			  bgfx::makeRef(s_vplaneVertices, sizeof(s_vplaneVertices))
			, PosTexcoordVertex::ms_layout
		);

		m_ibh = bgfx::createIndexBuffer(
			  bgfx::makeRef(s_planeIndices, sizeof(s_planeIndices))
		);

		// Create program from shaders.
		m_vt_unlit = loadProgram("vs_vt_generic", "fs_vt_unlit");
		m_vt_mip = loadProgram("vs_vt_generic", "fs_vt_mip");

		// Imgui.
		imguiCreate();

		m_timeOffset = bx::getHPCounter();

		// Get renderer capabilities info.
		m_caps = bgfx::getCaps();

		m_scrollArea = 0;

		// Create and setup camera
		cameraCreate();

		cameraSetPosition({ 0.0f, 5.0f, 0.0f });
		cameraSetVerticalAngle(0.0f);

		// Set VirtualTexture system allocator
		vt::VirtualTexture::setAllocator(&m_vtAllocator);

		// Create Virtual texture info
		m_vti = new vt::VirtualTextureInfo();
		m_vti->m_virtualTextureSize = 8192; // The actual size will be read from the tile data file
		m_vti->m_tileSize = 128;
		m_vti->m_borderSize = 1;

		// Generate tile data file (if not yet created)
		{
			vt::TileGenerator tileGenerator(m_vti);
			tileGenerator.generate("textures/8k_mars.jpg");
		}

		// Load tile data file
		auto tileDataFile = new vt::TileDataFile("temp/8k_mars.vt", m_vti);
		tileDataFile->readInfo();

		// Create virtual texture and feedback buffer
		m_vt = new vt::VirtualTexture(tileDataFile, m_vti, 2048, 1);
		m_feedbackBuffer = new vt::FeedbackBuffer(m_vti, 64, 64);

	}

	virtual int shutdown() override
	{
		// Cleanup.
		bgfx::frame();

		cameraDestroy();
		imguiDestroy();

		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);

		bgfx::destroy(m_vt_unlit);
		bgfx::destroy(m_vt_mip);

		delete m_vti;
		delete m_vt;
		delete m_feedbackBuffer;

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
		{
			imguiBeginFrame(
				  m_mouseState.m_mx
				, m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				, m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
			);

			showExampleDialog(this);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency());
			const float deltaTime = float(frameTime / freq);

			float time = (float)((now - m_timeOffset) / freq);

			if ((BGFX_CAPS_TEXTURE_BLIT | BGFX_CAPS_TEXTURE_READ_BACK) != (bgfx::getCaps()->supported & (BGFX_CAPS_TEXTURE_BLIT | BGFX_CAPS_TEXTURE_READ_BACK)))
			{
				// When texture read-back or blit is not supported by GPU blink!
				bool blink = uint32_t(time*3.0f) & 1;
				bgfx::dbgTextPrintf(0, 0, blink ? 0x4f : 0x04, " Texture read-back and/or blit not supported by GPU. ");

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				// This dummy draw call is here to make sure that view 0 is cleared
				// if no other draw calls are submitted to view 0.
				bgfx::touch(0);
			}
			else
			{
				ImGui::SetNextWindowPos(
					  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::SetNextWindowSize(
					  ImVec2(m_width / 5.0f, m_height - 10.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::Begin("Settings"
					, NULL
					, 0
				);

				//ImGui::SliderFloat("intensity", &m_intensity, 0.0f, 3.0f);
				auto showBorders = m_vt->isShowBoardersEnabled();
				if (ImGui::Checkbox("Show borders", &showBorders))
				{
					m_vt->enableShowBoarders(showBorders);
				}
				auto colorMipLevels = m_vt->isColorMipLevelsEnabled();
				if (ImGui::Checkbox("Color mip levels", &colorMipLevels))
				{
					m_vt->enableColorMipLevels(colorMipLevels);
				}
				auto uploadsperframe = m_vt->getUploadsPerFrame();
				if (ImGui::InputInt("Updates per frame", &uploadsperframe, 1, 2))
				{
					uploadsperframe = bx::clamp(uploadsperframe, 1, 100);
					m_vt->setUploadsPerFrame(uploadsperframe);
				}

				ImGui::ImageButton(m_vt->getAtlastTexture(), ImVec2(m_width / 5.0f - 16.0f, m_width / 5.0f - 16.0f));
				ImGui::ImageButton(bgfx::getTexture(m_feedbackBuffer->getFrameBuffer()), ImVec2(m_width / 5.0f - 16.0f, m_width / 5.0f - 16.0f));

				ImGui::End();

				// Update camera.
				cameraUpdate(deltaTime, m_mouseState, ImGui::MouseOverArea() );

				float view[16];
				cameraGetViewMtx(view);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 1000.0f, m_caps->homogeneousDepth);

				// Setup views
				for (uint16_t i = 0; i < 2; ++i)
				{
					uint16_t viewWidth = 0;
					uint16_t viewHeight = 0;
					// Setup pass, first pass is into mip-map feedback buffer, second pass is on screen
					if (i == 0)
					{
						bgfx::setViewFrameBuffer(i, m_feedbackBuffer->getFrameBuffer());
						viewWidth = uint16_t(m_feedbackBuffer->getWidth());
						viewHeight = uint16_t(m_feedbackBuffer->getHeight());
					}
					else
					{
						bgfx::FrameBufferHandle invalid = BGFX_INVALID_HANDLE;
						bgfx::setViewFrameBuffer(i, invalid);
						viewWidth = uint16_t(m_width);
						viewHeight = uint16_t(m_height);
					}

					bgfx::setViewRect(i, 0, 0, viewWidth, viewHeight);
					bgfx::setViewTransform(i, view, proj);

					float mtx[16];
					bx::mtxIdentity(mtx);

					// Set identity transform for draw call.
					bgfx::setTransform(mtx);

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(0, m_vbh);
					bgfx::setIndexBuffer(m_ibh);

					// Set render states.
					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_WRITE_Z
						| BGFX_STATE_DEPTH_TEST_LESS
					);

					// Set virtual texture uniforms
					m_vt->setUniforms();

					// Submit primitive for rendering to first pass (to feedback buffer, where mip levels and tile x/y will be rendered
					if (i == 0)
					{
						bgfx::submit(i, m_vt_mip);
						// Download previous frame feedback info
						m_feedbackBuffer->download();
						// Update and upload new requests
						m_vt->update(m_feedbackBuffer->getRequests(), 4);
						// Clear feedback
						m_feedbackBuffer->clear();
						// Copy new frame feedback buffer
						m_feedbackBuffer->copy(3);
					}
					else
					{
						// Submit primitive for rendering to second pass (to back buffer, where virtual texture page table and atlas will be used)
						bgfx::submit(i, m_vt_unlit);
					}
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

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;

	bgfx::ProgramHandle m_vt_unlit;
	bgfx::ProgramHandle m_vt_mip;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	int32_t m_scrollArea;

	entry::MouseState m_mouseState;

	const bgfx::Caps* m_caps;
	int64_t m_timeOffset;

	bx::DefaultAllocator m_vtAllocator;
	vt::VirtualTextureInfo* m_vti;
	vt::VirtualTexture* m_vt;
	vt::FeedbackBuffer* m_feedbackBuffer;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleSVT
	, "40-svt"
	, "Sparse Virtual Textures."
	, "https://bkaradzic.github.io/bgfx/examples.html#svt"
	);
