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
	"Features: 3D",
	"Features: 2D",
	"Features: Gather",
	"Features: Debug Zoom",
	"Features: Scatter",
	"Features: Quad VS/PS",
	"Features: Table",
	"Features: Quad Post",
	"Features: 2D Arrow",
	"Features: Generate User Font",
	"Features: Use User Font",
	"Features: 2D Coordinate System",
	"Hello World",
	"Hello Screen",
	"Features: Clear",
	"Zoom 2D",
};

void renderScreenSpaceQuad(uint8_t _view, bgfx::ProgramHandle _program, bool _originBottomLeft = false)
{
	bgfx::TransientVertexBuffer tvb;
	bgfx::TransientIndexBuffer tib;

	if (bgfx::allocTransientBuffers(&tvb, PosColorTexCoord0Vertex::ms_layout, 4, &tib, 6) )
	{
		PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)tvb.data;

		const float minV = _originBottomLeft ? 1.0f : 0.0f;
		const float maxV = _originBottomLeft ? 0.0f : 1.0f;
		vertex[0] = { -1.0f, -1.0f, 0.0f, 0xffffffff, 0.0f, maxV };
		vertex[1] = {  1.0f, -1.0f, 0.0f, 0xffffffff, 1.0f, maxV };
		vertex[2] = {  1.0f,  1.0f, 0.0f, 0xffffffff, 1.0f, minV };
		vertex[3] = { -1.0f,  1.0f, 0.0f, 0xffffffff, 0.0f, minV };

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
		init.platformData.type = entry::getNativeWindowHandleType();
		init.swapChain.nwh     = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.swapChain.ndt     = entry::getNativeDisplayHandle();
		init.swapChain.width   = m_width;
		init.swapChain.height  = m_height;
		init.reset = m_reset;
		bgfx::init(init);

		bgfx::setDebug(m_debug);
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x050505ff, 1.0f, 0);

		PosColorTexCoord0Vertex::init();
		for (bgfx::ProgramHandle& program : m_program)
		{
			program = BGFX_INVALID_HANDLE;
		}

		m_timeUniform        = bgfx::createUniform("u_s2hTime",        bgfx::UniformFreq::Frame, bgfx::UniformType::Vec4);
		m_uiStateUniform     = bgfx::createUniform("u_s2hUiState",     bgfx::UniformFreq::Frame, bgfx::UniformType::Vec4);
		m_colorUniform       = bgfx::createUniform("u_s2hColor",       bgfx::UniformFreq::Frame, bgfx::UniformType::Vec4);
		m_mouseUniform       = bgfx::createUniform("u_s2hMouse",       bgfx::UniformFreq::Frame, bgfx::UniformType::Vec4);
		m_zoomUniform        = bgfx::createUniform("u_s2hZoom",        bgfx::UniformFreq::Frame, bgfx::UniformType::Vec4);
		m_scatterSizeUniform = bgfx::createUniform("u_s2hScatterSize", bgfx::UniformFreq::Frame, bgfx::UniformType::Vec4);
		m_quadPostSampler    = bgfx::createUniform("s_quadPostColor",  bgfx::UniformType::Sampler);
		m_scatterSampler     = bgfx::createUniform("s_scatterColor",   bgfx::UniformType::Sampler);

		m_program[ 0] = loadProgram("vs_s2h", "fs_s2h_3d");
		m_program[ 1] = loadProgram("vs_s2h", "fs_s2h_2d");
		m_program[ 2] = loadProgram("vs_s2h", "fs_s2h_gather");
		m_program[ 5] = loadProgram("vs_s2h", "fs_s2h_quadvsps");
		m_program[ 6] = loadProgram("vs_s2h", "fs_s2h_table");
		m_program[ 7] = loadProgram("vs_s2h", "fs_s2h_quadpost_scene");
		m_program[ 8] = loadProgram("vs_s2h", "fs_s2h_arrow");
		m_program[ 9] = loadProgram("vs_s2h", "fs_s2h_generate_user_font");
		m_program[11] = loadProgram("vs_s2h", "fs_s2h_coordinate_system");
		m_program[12] = loadProgram("vs_s2h", "fs_s2h");
		m_program[13] = loadProgram("vs_s2h", "fs_s2h_screen");
		m_program[14] = loadProgram("vs_s2h", "fs_s2h_clear");
		m_program[15] = loadProgram("vs_s2h", "fs_s2h_zoom2d");
		m_quadPostProgram       = loadProgram("vs_s2h", "fs_s2h_quadpost");
		m_userFontProgram       = loadProgram("vs_s2h", "fs_s2h_use_user_font");
		m_debugZoomProgram      = loadProgram("vs_s2h", "fs_s2h_debug_zoom");
		m_scatterClearProgram   = loadProgram("cs_s2h_scatter_clear", NULL);
		m_scatterProgram        = loadProgram("cs_s2h_scatter", NULL);
		m_scatterDisplayProgram = loadProgram("vs_s2h", "fs_s2h_scatter_display");

		createQuadPostTarget();
		createScatterTarget();

		imguiCreate();
		m_frameTime.reset();
	}

	int shutdown() override
	{
		imguiDestroy();

		for (bgfx::ProgramHandle& program : m_program)
		{
			if (bgfx::isValid(program) )
			{
				bgfx::destroy(program);
			}
		}

		bgfx::destroy(m_quadPostProgram);
		bgfx::destroy(m_userFontProgram);
		bgfx::destroy(m_debugZoomProgram);
		bgfx::destroy(m_scatterClearProgram);
		bgfx::destroy(m_scatterProgram);
		bgfx::destroy(m_scatterDisplayProgram);
		bgfx::destroy(m_quadPostFrameBuffer);
		bgfx::destroy(m_quadPostTexture);
		bgfx::destroy(m_quadPostSampler);
		bgfx::destroy(m_scatterTexture);
		bgfx::destroy(m_scatterSampler);
		bgfx::destroy(m_scatterSizeUniform);
		bgfx::destroy(m_timeUniform);
		bgfx::destroy(m_uiStateUniform);
		bgfx::destroy(m_colorUniform);
		bgfx::destroy(m_mouseUniform);
		bgfx::destroy(m_zoomUniform);

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
			else if (15 == m_example)
			{
				updateZoomControls();
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

			const float zoom[] =
			{
				m_zoomPan[0],
				m_zoomPan[1],
				m_zoomScale,
				0.0f,
			};

			const bool originBottomLeft = bgfx::getCaps()->originBottomLeft;

			const float scatterSize[] = { float(m_width), float(m_height), originBottomLeft ? 1.0f : 0.0f, 0.0f };

			bgfx::setFrameUniform(m_timeUniform, time);
			bgfx::setFrameUniform(m_uiStateUniform, uiState);
			bgfx::setFrameUniform(m_colorUniform, m_gatherColor);
			bgfx::setFrameUniform(m_mouseUniform, mouse);
			bgfx::setFrameUniform(m_zoomUniform, zoom);
			bgfx::setFrameUniform(m_scatterSizeUniform, scatterSize);

			if (4 == m_example)
			{
				const uint32_t dispatchWidth = (m_width  + 7) / 8;
				const uint32_t dispatchHeight = (m_height + 7) / 8;

				bgfx::setImage(0, m_scatterTexture, 0, bgfx::Access::Write, bgfx::TextureFormat::RGBA8);
				bgfx::dispatch(2, m_scatterClearProgram, uint16_t(dispatchWidth), uint16_t(dispatchHeight) );

				bgfx::setImage(0, m_scatterTexture, 0, bgfx::Access::Write, bgfx::TextureFormat::RGBA8);
				bgfx::dispatch(3, m_scatterProgram, 1, 1);

				bgfx::setViewFrameBuffer(4, BGFX_INVALID_HANDLE);
				bgfx::setViewRect(4, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setTexture(0, m_scatterSampler, m_scatterTexture);
				renderScreenSpaceQuad(4, m_scatterDisplayProgram, originBottomLeft);
			}
			else if (3 == m_example || 7 == m_example || 10 == m_example)
			{
				bgfx::setViewFrameBuffer(0, m_quadPostFrameBuffer);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x101018ff);
				renderScreenSpaceQuad(0, 10 == m_example ? m_program[9] : m_program[7]);

				bgfx::setViewFrameBuffer(1, BGFX_INVALID_HANDLE);
				bgfx::setViewRect(1, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setTexture(0, m_quadPostSampler, m_quadPostTexture);
				renderScreenSpaceQuad(1, 7 == m_example ? m_quadPostProgram : (10 == m_example ? m_userFontProgram : m_debugZoomProgram), originBottomLeft);
			}
			else
			{
				bgfx::setViewFrameBuffer(0, BGFX_INVALID_HANDLE);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

				bgfx::touch(0);
				renderScreenSpaceQuad(0, m_program[m_example]);
			}
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
		else if (15 == m_example)
		{
			ImGui::TextWrapped("Left-drag to pan the zoomed canvas. Right-drag vertically to zoom. The fragment shader draws the grid and S2H overlay at the transformed pixel coordinates.");
			if (ImGui::Button("Reset view##zoom2d-reset") )
			{
				resetZoom();
			}
		}
		else
		{
			ImGui::TextWrapped("Select a Shader To Human sample. Sample-specific controls appear here.");
		}

		ImGui::PopItemWidth();
		ImGui::End();
	}

	void createQuadPostTarget()
	{
		m_quadPostTexture = bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT);
		m_quadPostFrameBuffer = bgfx::createFrameBuffer(1, &m_quadPostTexture, false);
	}

	void createScatterTarget()
	{
		m_scatterTexture = bgfx::createTexture2D(
			  uint16_t(m_width)
			, uint16_t(m_height)
			, false
			, 1
			, bgfx::TextureFormat::RGBA8
			, BGFX_TEXTURE_COMPUTE_WRITE|BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP
			);
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
			if (isInside(105.0f, 218.0f, 16.0f, 16.0f) )
			{
				m_gatherRadio = 1;
			}
			else if (isInside(121.0f, 218.0f, 16.0f, 16.0f) )
			{
				m_gatherRadio = 2;
			}
			else if (isInside(137.0f, 218.0f, 16.0f, 16.0f) )
			{
				m_gatherRadio = 3;
			}
			else if (isInside(105.0f, 250.0f, 80.0f, 16.0f) )
			{
				m_gatherRadio = 0;
			}
			else if (isInside(105.0f, 282.0f, 16.0f, 16.0f) )
			{
				m_gatherCheckbox = !m_gatherCheckbox;
			}
		}

		if (ImGui::IsMouseDown(ImGuiMouseButton_Left) )
		{
			auto updateSlider = [&isInside, &mouse](float _x, float _y, float _width, float& _value)
			{
				if (isInside(_x, _y, _width, 14.0f) )
				{
					_value = bx::clamp((mouse.x - (_x + 2.0f)) / (_width - 4.0f), 0.0f, 1.0f);
				}
			};

			updateSlider(42.0f, 346.0f, 128.0f, m_gatherColor[3]);
			updateSlider(90.0f, 378.0f, 80.0f, m_gatherColor[0]);
			updateSlider(90.0f, 394.0f, 80.0f, m_gatherColor[1]);
			updateSlider(90.0f, 410.0f, 80.0f, m_gatherColor[2]);
		}
	}

	void resetZoom()
	{
		m_zoomPan[0] = 0.0f;
		m_zoomPan[1] = 0.0f;
		m_zoomScale = 1.0f;
	}

	void updateZoomControls()
	{
		const int32_t mouseX = m_mouseState.m_mx;
		const int32_t mouseY = m_mouseState.m_my;
		const bool leftDown  = m_mouseState.m_buttons[entry::MouseButton::Left];
		const bool rightDown = m_mouseState.m_buttons[entry::MouseButton::Right];

		if (ImGui::GetIO().WantCaptureMouse)
		{
			m_zoomLastMouseX = mouseX;
			m_zoomLastMouseY = mouseY;
			m_zoomLeftDown = false;
			m_zoomRightDown = false;
			return;
		}

		if (leftDown && m_zoomLeftDown)
		{
			m_zoomPan[0] -= float(mouseX - m_zoomLastMouseX) / m_zoomScale;
			m_zoomPan[1] += float(mouseY - m_zoomLastMouseY) / m_zoomScale;
		}
		if (rightDown && m_zoomRightDown)
		{
			m_zoomScale = bx::clamp(m_zoomScale * bx::pow(2.0f, float(m_zoomLastMouseY - mouseY) * 0.02f), 0.125f, 32.0f);
		}

		m_zoomLastMouseX = mouseX;
		m_zoomLastMouseY = mouseY;
		m_zoomLeftDown = leftDown;
		m_zoomRightDown = rightDown;
	}

	entry::MouseState m_mouseState;
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	int m_example = 0;

	bgfx::ProgramHandle m_program[BX_COUNTOF(s_exampleNames)];
	bgfx::ProgramHandle m_quadPostProgram;
	bgfx::ProgramHandle m_userFontProgram;
	bgfx::ProgramHandle m_debugZoomProgram;
	bgfx::ProgramHandle m_scatterClearProgram;
	bgfx::ProgramHandle m_scatterProgram;
	bgfx::ProgramHandle m_scatterDisplayProgram;
	bgfx::TextureHandle m_quadPostTexture;

	bgfx::FrameBufferHandle m_quadPostFrameBuffer;
	bgfx::TextureHandle m_scatterTexture;

	bgfx::UniformHandle m_quadPostSampler;
	bgfx::UniformHandle m_scatterSampler;
	bgfx::UniformHandle m_scatterSizeUniform;
	bgfx::UniformHandle m_timeUniform;
	bgfx::UniformHandle m_uiStateUniform;
	bgfx::UniformHandle m_colorUniform;
	bgfx::UniformHandle m_mouseUniform;
	bgfx::UniformHandle m_zoomUniform;

	FrameTime m_frameTime;

	int m_gatherRadio = 0;
	bool m_gatherCheckbox = false;
	bool m_gatherMouseDown = false;
	float m_gatherColor[4] = { 0.0f, 0.3f, 1.0f, 1.0f };
	float m_zoomPan[2] = { 0.0f, 0.0f };
	float m_zoomScale = 1.0f;
	int32_t m_zoomLastMouseX = 0;
	int32_t m_zoomLastMouseY = 0;
	bool m_zoomLeftDown = false;
	bool m_zoomRightDown = false;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleS2h
	, "54-s2h"
	, "Shader To Human: Hello World."
	, ""
	);
