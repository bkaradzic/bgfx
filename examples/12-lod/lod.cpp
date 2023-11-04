/*
 * Copyright 2013 Milos Tosic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

#include <bx/readerwriter.h>

namespace
{

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

class ExampleLod : public entry::AppI
{
public:
	ExampleLod(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
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
		init.platformData.nwh  = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.platformData.ndt  = entry::getNativeDisplayHandle();
		init.platformData.type = entry::getNativeWindowHandleType();
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

		s_texColor   = bgfx::createUniform("s_texColor",   bgfx::UniformType::Sampler);
		s_texStipple = bgfx::createUniform("s_texStipple", bgfx::UniformType::Sampler);
		u_stipple    = bgfx::createUniform("u_stipple",    bgfx::UniformType::Vec4);

		m_program = loadProgram("vs_tree", "fs_tree");

		m_textureLeafs = loadTexture("textures/leafs1.dds");
		m_textureBark  = loadTexture("textures/bark1.dds");

		const bgfx::Memory* stippleTex = bgfx::alloc(8*4);
		bx::memSet(stippleTex->data, 0, stippleTex->size);

		for (uint8_t ii = 0; ii < 32; ++ii)
		{
			stippleTex->data[knightTour[ii].m_y * 8 + knightTour[ii].m_x] = ii*4;
		}

		m_textureStipple = bgfx::createTexture2D(8, 4, false, 1
			, bgfx::TextureFormat::R8
			, BGFX_SAMPLER_MAG_POINT|BGFX_SAMPLER_MIN_POINT
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

	virtual int shutdown() override
	{
		imguiDestroy();

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_meshTop); ++ii)
		{
			meshUnload(m_meshTop[ii]);
			meshUnload(m_meshTrunk[ii]);
		}

		// Cleanup.
		bgfx::destroy(m_program);

		bgfx::destroy(s_texColor);
		bgfx::destroy(s_texStipple);
		bgfx::destroy(u_stipple);

		bgfx::destroy(m_textureStipple);
		bgfx::destroy(m_textureLeafs);
		bgfx::destroy(m_textureBark);

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

			ImGui::Checkbox("Transition", &m_transitions);

			static float distance = 2.0f;
			ImGui::SliderFloat("Distance", &distance, 2.0f, 6.0f);

			ImGui::End();

			imguiEndFrame();

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			const bx::Vec3 at  = { 0.0f, 1.0f,      0.0f };
			const bx::Vec3 eye = { 0.0f, 2.0f, -distance };

			// Set view and projection matrix for view 0.
			{
				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
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
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
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
			if (eye.z < -2.5f)
			{
				lod = 1;
			}

			if (eye.z < -5.0f)
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

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleLod
	, "12-lod"
	, "Mesh LOD transitions."
	, "https://bkaradzic.github.io/bgfx/examples.html#lod"
	);
