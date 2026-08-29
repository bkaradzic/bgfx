/*
 * Copyright 2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

struct PosColorTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
	float m_u;
	float m_v;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorTexCoord0Vertex::ms_layout;

static const char* s_exampleNames[] =
{
	"Hello World",
	"Hello Screen",
	"Features: Gather",
	"Features: 2D Arrow",
	"Features: 2D Coordinate System",
	"Features: Table",
	"Features: Generate User Font",
	"Features: 2D",
	"Features: 3D",
};

void renderScreenSpaceQuad(uint8_t _view, bgfx::ProgramHandle _program)
{
	bgfx::TransientVertexBuffer tvb;
	bgfx::TransientIndexBuffer tib;

	if (bgfx::allocTransientBuffers(&tvb, PosColorTexCoord0Vertex::ms_layout, 4, &tib, 6) )
	{
		PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)tvb.data;

		vertex[0] = { -1.0f, -1.0f, 0.0f, 0xffffffff, 0.0f, 1.0f };
		vertex[1] = {  1.0f, -1.0f, 0.0f, 0xffffffff, 1.0f, 1.0f };
		vertex[2] = {  1.0f,  1.0f, 0.0f, 0xffffffff, 1.0f, 0.0f };
		vertex[3] = { -1.0f,  1.0f, 0.0f, 0xffffffff, 0.0f, 0.0f };

		uint16_t* indices = (uint16_t*)tib.data;
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

		bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
		bgfx::setIndexBuffer(&tib);
		bgfx::setVertexBuffer(0, &tvb);
		bgfx::submit(_view, _program);
	}
}

class ExampleS2h : public entry::AppI
{
public:
	ExampleS2h(const char* _name, const char* _description, const char* _url)
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

		bgfx::setDebug(m_debug);
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x050505ff, 1.0f, 0);

		PosColorTexCoord0Vertex::init();
		m_timeUniform    = bgfx::createUniform("u_s2hTime",    bgfx::UniformFreq::View, bgfx::UniformType::Vec4);
		m_uiStateUniform = bgfx::createUniform("u_s2hUiState", bgfx::UniformFreq::View, bgfx::UniformType::Vec4);
		m_colorUniform   = bgfx::createUniform("u_s2hColor",   bgfx::UniformFreq::View, bgfx::UniformType::Vec4);
		m_mouseUniform   = bgfx::createUniform("u_s2hMouse",   bgfx::UniformFreq::View, bgfx::UniformType::Vec4);

		m_program[0] = loadProgram("vs_s2h", "fs_s2h");
		m_program[1] = loadProgram("vs_s2h", "fs_s2h_screen");
		m_program[2] = loadProgram("vs_s2h", "fs_s2h_gather");
		m_program[3] = loadProgram("vs_s2h", "fs_s2h_arrow");
		m_program[4] = loadProgram("vs_s2h", "fs_s2h_coordinate_system");
		m_program[5] = loadProgram("vs_s2h", "fs_s2h_table");
		m_program[6] = loadProgram("vs_s2h", "fs_s2h_generate_user_font");
		m_program[7] = loadProgram("vs_s2h", "fs_s2h_2d");
		m_program[8] = loadProgram("vs_s2h", "fs_s2h_3d");

		imguiCreate();
		m_frameTime.reset();
	}

	int shutdown() override
	{
		imguiDestroy();
		for (bgfx::ProgramHandle& program : m_program)
		{
			bgfx::destroy(program);
		}
		bgfx::destroy(m_timeUniform);
		bgfx::destroy(m_uiStateUniform);
		bgfx::destroy(m_colorUniform);
		bgfx::destroy(m_mouseUniform);
		bgfx::shutdown();
		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			m_frameTime.frame();
			imguiBeginFrame(m_mouseState.m_mx, m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				, m_mouseState.m_mz, uint16_t(m_width), uint16_t(m_height) );
			m_gatherMouseDown = m_mouseState.m_buttons[entry::MouseButton::Left];
			showExampleDialog(this);

			drawSettings();
			if (2 == m_example)
			{
				updateGatherControls();
			}

			imguiEndFrame();

			const float time[] =
			{
				bx::toSeconds<float>(m_frameTime.getDurationTime() ),
				0.0f,
				0.0f,
				0.0f,
			};
			const float uiState[] =
			{
				float(m_gatherRadio),
				m_gatherCheckbox ? 1.0f : 0.0f,
				m_gatherColor[3],
				0.0f,
			};
			const float mouse[] =
			{
				float(m_mouseState.m_mx),
				float(m_mouseState.m_my),
				m_gatherMouseDown ? 1.0f : 0.0f,
				0.0f,
			};
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			bgfx::setViewUniform(0, m_timeUniform, time);
			bgfx::setViewUniform(0, m_uiStateUniform, uiState);
			bgfx::setViewUniform(0, m_colorUniform, m_gatherColor);
			bgfx::setViewUniform(0, m_mouseUniform, mouse);
			bgfx::touch(0);
			renderScreenSpaceQuad(0, m_program[m_example]);
			bgfx::frame();
			return true;
		}

		return false;
	}

	void drawSettings()
	{
		ImGui::SetNextWindowPos(
			ImVec2(m_width - m_width / 4.0f - 10.0f, 10.0f)
			, ImGuiCond_FirstUseEver
			);
		ImGui::SetNextWindowSize(
			ImVec2(m_width / 4.0f, m_height / 1.35f)
			, ImGuiCond_FirstUseEver
			);
		ImGui::Begin("Settings", NULL, 0);

		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.55f);
		ImGui::Combo("example", &m_example, s_exampleNames, BX_COUNTOF(s_exampleNames) );
		ImGui::Separator();

		if (2 == m_example)
		{
			ImGui::Text("Gather controls:");
			ImGui::RadioButton("red##gather-radio-red",     &m_gatherRadio, 1); ImGui::SameLine();
			ImGui::RadioButton("green##gather-radio-green", &m_gatherRadio, 2); ImGui::SameLine();
			ImGui::RadioButton("blue##gather-radio-blue",   &m_gatherRadio, 3);
			ImGui::Checkbox("checkbox##gather-checkbox", &m_gatherCheckbox);
			ImGui::SliderFloat("alpha##gather-alpha", &m_gatherColor[3], 0.0f, 1.0f);
			ImGui::SliderFloat("red##gather-red",     &m_gatherColor[0], 0.0f, 1.0f);
			ImGui::SliderFloat("green##gather-green", &m_gatherColor[1], 0.0f, 1.0f);
			ImGui::SliderFloat("blue##gather-blue",   &m_gatherColor[2], 0.0f, 1.0f);
		}
		else
		{
			ImGui::TextWrapped("Select a Shader To Human sample. Sample-specific controls appear here.");
		}

		ImGui::PopItemWidth();
		ImGui::End();
	}

	void updateGatherControls()
	{
		const ImVec2 mouse = ImGui::GetIO().MousePos;
		const auto isInside = [&mouse](float _x, float _y, float _width, float _height)
		{
			return mouse.x >= _x && mouse.x < _x + _width
				&& mouse.y >= _y && mouse.y < _y + _height;
		};

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) )
		{
			if (isInside(105.0f, 185.0f, 16.0f, 16.0f) )
			{
				m_gatherRadio = 1;
			}
			else if (isInside(121.0f, 185.0f, 16.0f, 16.0f) )
			{
				m_gatherRadio = 2;
			}
			else if (isInside(137.0f, 185.0f, 16.0f, 16.0f) )
			{
				m_gatherRadio = 3;
			}
			else if (isInside(105.0f, 201.0f, 16.0f, 16.0f) )
			{
				m_gatherCheckbox = !m_gatherCheckbox;
			}
		}

		if (ImGui::IsMouseDown(ImGuiMouseButton_Left) )
		{
			auto updateSlider = [&isInside, &mouse](float _x, float _y, float& _value)
			{
				if (isInside(_x, _y, 128.0f, 14.0f) )
				{
					_value = bx::clamp((mouse.x - (_x + 2.0f)) / 124.0f, 0.0f, 1.0f);
				}
			};

			updateSlider(42.0f, 234.0f, m_gatherColor[3]);
			updateSlider(90.0f, 250.0f, m_gatherColor[0]);
			updateSlider(90.0f, 266.0f, m_gatherColor[1]);
			updateSlider(90.0f, 282.0f, m_gatherColor[2]);
		}
	}

	entry::MouseState m_mouseState;
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	int m_example = 0;
	bgfx::ProgramHandle m_program[BX_COUNTOF(s_exampleNames)];
	FrameTime m_frameTime;
	bgfx::UniformHandle m_timeUniform;
	bgfx::UniformHandle m_uiStateUniform;
	bgfx::UniformHandle m_colorUniform;
	bgfx::UniformHandle m_mouseUniform;
	int m_gatherRadio = 0;
	bool m_gatherCheckbox = false;
	bool m_gatherMouseDown = false;
	float m_gatherColor[4] = { 0.0f, 0.3f, 1.0f, 1.0f };
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleS2h
	, "54-s2h"
	, "Shader To Human: Hello World."
	, ""
	);
