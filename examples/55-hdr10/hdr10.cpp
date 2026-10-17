/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

#include <bx/math.h>

namespace
{

constexpr uint32_t kSwapChainFlags = 0
	| BGFX_SWAP_CHAIN_FULLSCREEN_MASK
	| BGFX_SWAP_CHAIN_MSAA_MASK
	| BGFX_SWAP_CHAIN_SRGB_BACKBUFFER
	| BGFX_SWAP_CHAIN_HDR10
	| BGFX_SWAP_CHAIN_HIDPI
	| BGFX_SWAP_CHAIN_TRANSPARENT_BACKBUFFER
	;

constexpr uint32_t kNumGray = 7;
constexpr uint32_t kNumBars = 6;

constexpr float kGrayNits[kNumGray]  = { 0.0f, 100.0f, 203.0f, 400.0f, 1000.0f, 4000.0f, 10000.0f };
constexpr float kGrayScale[kNumGray] = { 0.0f, 0.5f, 1.0f, 2.0f, 4.0f, 8.0f, 16.0f };
constexpr float kBarNits = 203.0f;

constexpr float kBarColor[kNumBars][3] =
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f },
};

constexpr const char* kBarName[kNumBars] = { "R", "G", "B", "C", "M", "Y" };

float encodePq(float _nits)
{
	constexpr float m1 = 2610.0f/16384.0f;
	constexpr float m2 = 2523.0f/4096.0f*128.0f;
	constexpr float c1 = 3424.0f/4096.0f;
	constexpr float c2 = 2413.0f/4096.0f*32.0f;
	constexpr float c3 = 2392.0f/4096.0f*32.0f;

	const float yy = bx::pow(bx::clamp(_nits/10000.0f, 0.0f, 1.0f), m1);

	return bx::pow( (c1 + c2*yy) / (1.0f + c3*yy), m2);
}

class ExampleHdr10 : public entry::AppI
{
public:
	ExampleHdr10(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
		m_reset  = BGFX_RESET_VSYNC|BGFX_RESET_HDR10;
		m_pq     = true;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.swapChain.nwh         = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.swapChain.ndt         = entry::getNativeDisplayHandle();
		init.platformData.type     = entry::getNativeWindowHandleType();
		init.swapChain.width       = m_width;
		init.swapChain.height      = m_height;
		init.swapChain.formatColor = getFormat();
		init.reset = m_reset;
		bgfx::init(init);

		bgfx::setDebug(m_debug);

		m_appliedWidth  = m_width;
		m_appliedHeight = m_height;
		m_appliedReset  = m_reset;
		m_appliedPq     = m_pq;

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();

		bgfx::shutdown();

		return 0;
	}

	bgfx::TextureFormat::Enum getFormat() const
	{
		return m_pq
			? bgfx::TextureFormat::RGB10A2
			: bgfx::TextureFormat::RGBA16F
			;
	}

	void setPatch(uint8_t _index, float _red, float _green, float _blue)
	{
		const float rgba[4] = { _red, _green, _blue, 1.0f };
		bgfx::setPaletteColor(_index, rgba);
	}

	float encode(float _nits, float _scale) const
	{
		return m_pq ? encodePq(_nits) : _scale;
	}

	void imguiLabel(float _x, float _y, const char* _id, const char* _text)
	{
		ImGui::SetNextWindowPos(ImVec2(_x, _y), 0, ImVec2(0.5f, 1.0f) );
		ImGui::SetNextWindowBgAlpha(0.5f);

		ImGui::Begin(_id, NULL, 0
			| ImGuiWindowFlags_NoInputs
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_AlwaysAutoResize
			);
		ImGui::Text("%s", _text);
		ImGui::End();
	}

	void submitPatch(bgfx::ViewId _view, uint8_t _index, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
	{
		bgfx::setViewRect(_view, _x, _y, _width, _height);
		bgfx::setViewClear(_view, BGFX_CLEAR_COLOR, 1.0f, 0, _index);
		bgfx::touch(_view);
	}

	bool update() override
	{
		if (entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			return false;
		}

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

		bool hdr10 = 0 != (m_reset & BGFX_RESET_HDR10);

		ImGui::SetNextWindowPos(ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(m_width / 5.0f, m_height / 6.0f), ImGuiCond_FirstUseEver);
		ImGui::Begin("Settings", NULL, 0);

		if (ImGui::RadioButton("PQ, RGB10A2", m_pq) )
		{
			m_pq = true;
		}

		if (ImGui::RadioButton("Linear, RGBA16F", !m_pq) )
		{
			m_pq = false;
		}

		ImGui::Checkbox("HDR10", &hdr10);

		ImGui::End();

		const float labelRowHeight = float(m_height*2/5);

		char id[32];
		char text[128];

		for (uint32_t ii = 0; ii < kNumGray; ++ii)
		{
			if (m_pq)
			{
				bx::snprintf(text, BX_COUNTOF(text), "%.0f nits", kGrayNits[ii]);
			}
			else
			{
				bx::snprintf(text, BX_COUNTOF(text), "%.1fx white", kGrayScale[ii]);
			}

			bx::snprintf(id, BX_COUNTOF(id), "gray%d", ii);
			imguiLabel(m_width*(ii + 0.5f)/kNumGray, labelRowHeight - 10.0f, id, text);
		}

		for (uint32_t ii = 0; ii < kNumBars; ++ii)
		{
			if (m_pq)
			{
				bx::snprintf(text, BX_COUNTOF(text), "%s %.0f nits", kBarName[ii], kBarNits);
			}
			else
			{
				bx::snprintf(text, BX_COUNTOF(text), "%s 1.0x white", kBarName[ii]);
			}

			bx::snprintf(id, BX_COUNTOF(id), "bar%d", ii);
			imguiLabel(m_width*(ii + 0.5f)/kNumBars, 2.0f*labelRowHeight - 10.0f, id, text);
		}

		const bgfx::Caps* caps = bgfx::getCaps();

		bx::snprintf(text, BX_COUNTOF(text), "BGFX_CAPS_HDR10: %s, back buffer: %s"
			, 0 != (caps->supported & BGFX_CAPS_HDR10) ? "supported" : "not supported"
			, m_pq ? "RGB10A2, PQ BT.2020" : "RGBA16F, extended linear sRGB"
			);
		imguiLabel(m_width*0.5f, m_height - 10.0f, "status", text);

		const bool hdr10Output = true
			&& hdr10
			&& 0 != (caps->supported & BGFX_CAPS_HDR10)
			;

		imguiSetOutput(
			  !hdr10Output ? ImguiOutput::Srgb
			: m_pq         ? ImguiOutput::Pq
			:                ImguiOutput::Linear
			, m_pq ? kBarNits : 1.0f
			);

		imguiEndFrame();

		m_reset = (m_reset & ~BGFX_RESET_HDR10) | (hdr10 ? BGFX_RESET_HDR10 : 0);

		if (m_width  != m_appliedWidth
		||  m_height != m_appliedHeight
		||  m_reset  != m_appliedReset
		||  m_pq     != m_appliedPq)
		{
			m_appliedWidth  = m_width;
			m_appliedHeight = m_height;
			m_appliedReset  = m_reset;
			m_appliedPq     = m_pq;

			bgfx::SwapChain swapChain;
			swapChain.width       = m_width;
			swapChain.height      = m_height;
			swapChain.flags       = m_reset & kSwapChainFlags;
			swapChain.formatColor = getFormat();

			bgfx::reset(m_reset & ~kSwapChainFlags, &swapChain);
		}

		bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x000000ff, 1.0f, 0);
		bgfx::touch(0);

		const uint16_t rowHeight = uint16_t(m_height*2/5);

		for (uint32_t ii = 0; ii < kNumGray; ++ii)
		{
			const float value = encode(kGrayNits[ii], kGrayScale[ii]);
			setPatch(uint8_t(ii), value, value, value);

			const uint16_t x0 = uint16_t(m_width* ii     /kNumGray);
			const uint16_t x1 = uint16_t(m_width*(ii + 1)/kNumGray);
			submitPatch(bgfx::ViewId(1 + ii), uint8_t(ii), x0, 0, x1 - x0, rowHeight);
		}

		for (uint32_t ii = 0; ii < kNumBars; ++ii)
		{
			const float on = encode(kBarNits, 1.0f);
			setPatch(uint8_t(kNumGray + ii)
				, kBarColor[ii][0]*on
				, kBarColor[ii][1]*on
				, kBarColor[ii][2]*on
				);

			const uint16_t x0 = uint16_t(m_width* ii     /kNumBars);
			const uint16_t x1 = uint16_t(m_width*(ii + 1)/kNumBars);
			submitPatch(bgfx::ViewId(1 + kNumGray + ii), uint8_t(kNumGray + ii), x0, rowHeight, x1 - x0, rowHeight);
		}

		bgfx::frame();

		return true;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	bool     m_pq;

	uint32_t m_appliedWidth;
	uint32_t m_appliedHeight;
	uint32_t m_appliedReset;
	bool     m_appliedPq;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleHdr10
	, "55-hdr10"
	, "HDR10 test pattern."
	, "https://bkaradzic.github.io/bgfx/examples.html#hdr10"
	);
