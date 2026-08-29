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
		m_program[0] = loadProgram("vs_s2h", "fs_s2h");
		m_program[1] = loadProgram("vs_s2h", "fs_s2h_screen");

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();
		for (bgfx::ProgramHandle& program : m_program)
		{
			bgfx::destroy(program);
		}
		bgfx::shutdown();
		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx, m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				, m_mouseState.m_mz, uint16_t(m_width), uint16_t(m_height) );
			showExampleDialog(this);

			ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_FirstUseEver);
			ImGui::Begin("S2H Examples", NULL, 0);
			ImGui::Combo("Example", &m_example, s_exampleNames, BX_COUNTOF(s_exampleNames) );
			ImGui::TextWrapped("Select a Shader To Human sample. New samples can share this fullscreen renderer.");
			ImGui::End();
			imguiEndFrame();

			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			bgfx::touch(0);
			renderScreenSpaceQuad(0, m_program[m_example]);
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
	int m_example = 0;
	bgfx::ProgramHandle m_program[BX_COUNTOF(s_exampleNames)];
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleS2h
	, "54-s2h"
	, "Shader To Human: Hello World."
	, ""
	);
