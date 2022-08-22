/*
 * Copyright 2022-2022 Sandy Carter. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

#include <bx/allocator.h>
#include <bx/math.h>

namespace
{

const int TEXTURE_SIZE = 256;
const int HALF_TEXTURE_SIZE = TEXTURE_SIZE / 2;
const int NUM_FORMATS = bgfx::TextureFormat::UnknownDepth - bgfx::TextureFormat::Unknown - 1;
const int NUM_FORMATS_IN_ROW = (int)bx::ceil(bx::sqrt(NUM_FORMATS));

class ExamplePixelFormats : public entry::AppI
{
public:
	ExamplePixelFormats(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_TEXT;
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

		const uint32_t flags = 0
			| BGFX_SAMPLER_U_CLAMP
			| BGFX_SAMPLER_V_CLAMP
			| BGFX_SAMPLER_MIN_POINT
			| BGFX_SAMPLER_MAG_POINT
			;
		float* rgbaf32Pixels = (float*)BX_ALLOC(entry::getAllocator(), TEXTURE_SIZE * TEXTURE_SIZE * 4 * sizeof(float));
		int x, y;
		for (y = 0 ; y < TEXTURE_SIZE; ++y)
		{
			for (x = 0; x < TEXTURE_SIZE; ++x)
			{
				float relX = (x - HALF_TEXTURE_SIZE) / (float) HALF_TEXTURE_SIZE;
				float relY = (y - HALF_TEXTURE_SIZE) / (float) HALF_TEXTURE_SIZE;
				float distance = bx::min(1.0f, bx::sqrt(relX * relX + relY * relY));
				float angle = bx::atan2(relY, relX);
				float* pixel = &rgbaf32Pixels[(x + y * TEXTURE_SIZE) * 4];
				float hsv[3] = {angle / (2.0f * bx::kPi), 1.0f, 1.0f - distance};
				bx::hsvToRgb(pixel, hsv);
				pixel[3] = 1.0f - distance;
			}
		}

		for (y = 0; y < 16; ++y)
		{
			for (x = 0; x < 16; ++x)
			{
				float* r = &rgbaf32Pixels[(x + (TEXTURE_SIZE - 36 + y) * TEXTURE_SIZE) * 4];
				r[0] = 1.0f;
				r[1] = 0.0f;
				r[2] = 0.0f;
				r[3] = 1.0f;

				float* g = &rgbaf32Pixels[(x + 16 + (TEXTURE_SIZE - 36 + y) * TEXTURE_SIZE) * 4];
				g[0] = 0.0f;
				g[1] = 1.0f;
				g[2] = 0.0f;
				g[3] = 1.0f;

				float* b = &rgbaf32Pixels[(x + 32 + (TEXTURE_SIZE - 36 + y) * TEXTURE_SIZE) * 4];
				b[0] = 0.0f;
				b[1] = 0.0f;
				b[2] = 1.0f;
				b[3] = 1.0f;
			}
		}

		for (y = 0; y < 16; ++y)
		{
			for (x = 0; x < 48; ++x)
			{
				float* a = &rgbaf32Pixels[(x + (TEXTURE_SIZE - 20 + y) * TEXTURE_SIZE) * 4];
				a[0] = 1.0f;
				a[1] = 1.0f;
				a[2] = 1.0f;
				a[3] = 1.0f - (float)x / 48.0f;
			}
		}

		bimg::TextureInfo info;
		for (int i = 0; i < NUM_FORMATS; ++i)
		{
			int format = (int)bgfx::TextureFormat::Unknown + 1 + i;
			const char* formatName = bimg::getName(bimg::TextureFormat::Enum(format));
			int32_t formatNameLen = bx::strLen(formatName);
			if (!bimg::imageConvert(bimg::TextureFormat::Enum(format), bimg::TextureFormat::RGBA32F)
				|| formatName[formatNameLen - 1] == 'I'
				|| formatName[formatNameLen - 1] == 'U'
				)
			{
				m_textures[i] = BGFX_INVALID_HANDLE;
				continue;
			}
			bimg::imageGetSize(&info, TEXTURE_SIZE, TEXTURE_SIZE, 1, false, false, 1, bimg::TextureFormat::Enum(format));
			const bgfx::Memory* mem = bgfx::alloc(info.storageSize);
			bimg::imageConvert(entry::getAllocator(), mem->data, info.format, rgbaf32Pixels, bimg::TextureFormat::RGBA32F, TEXTURE_SIZE, TEXTURE_SIZE, 1);
			m_textures[i] = bgfx::createTexture2D(info.width, info.height, info.numMips > 1, info.numLayers, bgfx::TextureFormat::Enum(info.format), flags, mem);
			bgfx::setName(m_textures[i], formatName);
			bgfx::setViewName(bgfx::ViewId(i + 1), formatName);
		}

		BX_FREE(entry::getAllocator(), rgbaf32Pixels);

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();

		for (auto texture: m_textures)
		{
			if (bgfx::isValid(texture))
				bgfx::destroy(texture);
		}

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	void imguiTextBoxUnformatted(const ImVec2& size, const char* text) const
	{
		ImVec2 textSize = ImGui::CalcTextSize(text);
		ImVec2 textOffset = ImVec2(
			size.x >= 0.0f ? bx::max((size.x - textSize.x) / 2, 0.0f) : 0.0f,
			size.y >= 0.0f ? bx::max((size.y - textSize.y) / 2, 0.0f) : 0.0f
		);
		ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + textOffset.x, ImGui::GetCursorPosY() + textOffset.y));
		ImGui::TextUnformatted(text);
	};

	void imguiTexturePreview(const ImVec2& size, bgfx::TextureHandle texture, const ImVec2& previewSizeHint = ImVec2(-1.0f, -1.0f)) const
	{
		ImVec2 origin = ImGui::GetCursorScreenPos();

		ImVec2 previewSize = ImVec2(
			previewSizeHint.x >= 0.0f ? previewSizeHint.x : size.x,
			previewSizeHint.y >= 0.0f ? previewSizeHint.y : size.y
		);

		ImVec2 previewPos = ImVec2(
			origin.x + bx::max(0.0f, (size.x - previewSize.x) / 2),
			origin.y + bx::max(0.0f, (size.y - previewSize.y) / 2)
		);

		if (bgfx::isValid(texture))
		{
			ImGui::SetCursorScreenPos(previewPos);
			ImGui::Image(texture, previewSize);
		}
		else
		{
			ImU32 color = ImGui::GetColorU32(ImGuiCol_TextDisabled, 0.25f);

			ImDrawList* drawList = ImGui::GetWindowDrawList();
			ImVec2 p0 = previewPos;
			ImVec2 p1 = ImVec2(p0.x + previewSize.x, p0.y + previewSize.y);
			drawList->AddRect(p0, p1, color);
			drawList->AddLine(p0, p1, color);

//			imguiTextBoxUnformatted(size, "INVALID");
		}

		ImGui::SetCursorScreenPos(origin);
		ImGui::Dummy(size);
	};

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

			ImGui::SetNextWindowPos(ImVec2(360.0f, 40.0f), ImGuiCond_FirstUseEver);
			ImGui::Begin("Formats", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

			float cellWidth = m_previewSize;
			for (int i = 0; i < NUM_FORMATS; ++i)
			{
				int format = (int)bgfx::TextureFormat::Unknown + 1 + i;
				ImVec2 textSize = ImGui::CalcTextSize(bimg::getName(bimg::TextureFormat::Enum(format)));
				cellWidth = bx::max(cellWidth, textSize.x);
			}

			ImDrawList* drawList = ImGui::GetWindowDrawList();

			ImGui::DragFloat("Preview Size", &m_previewSize, 1.0f, 10.0f, TEXTURE_SIZE);
			ImGui::BeginTable("Formats", NUM_FORMATS_IN_ROW, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit);
			for (int i = 0; i < NUM_FORMATS; ++i)
			{
				ImGui::TableNextColumn();

				int format = (int)bgfx::TextureFormat::Unknown + 1 + i;

				bool isSelected = (m_selectedFormat == format);

				ImDrawListSplitter splitter;
				splitter.Split(drawList, 2);
				splitter.SetCurrentChannel(drawList, 1);

				ImGui::BeginGroup();
				ImGuiTextBuffer label;
				label.append(bimg::getName(bimg::TextureFormat::Enum(format)));
				imguiTextBoxUnformatted(ImVec2(cellWidth, 0.0f), label.c_str());
				imguiTexturePreview(ImVec2(cellWidth, m_previewSize), m_textures[i], ImVec2(m_previewSize, m_previewSize));
				ImGui::EndGroup();

				splitter.SetCurrentChannel(drawList, 0);
				ImGui::SetCursorScreenPos(ImGui::GetItemRectMin());

				ImGui::PushID(i);
				if (ImGui::Selectable("##selectable", &isSelected, ImGuiSelectableFlags_AllowItemOverlap, ImGui::GetItemRectSize()))
					m_selectedFormat = bimg::TextureFormat::Enum(format);
				ImGui::PopID();

				splitter.Merge(drawList);
			}
			ImGui::EndTable();
			ImGui::End();

			ImGui::SetNextWindowPos(ImVec2(40.0f, 300.0f), ImGuiCond_FirstUseEver);
			ImGui::Begin("Selected Format", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::Text("Format: %s", bimg::getName(m_selectedFormat));
			int selectedTextureIndex = m_selectedFormat - 1 - (int)bimg::TextureFormat::Unknown;
			bgfx::TextureHandle selectedTexture = BGFX_INVALID_HANDLE;
			if (m_selectedFormat != bimg::TextureFormat::Unknown)
				selectedTexture = m_textures[selectedTextureIndex];
			imguiTexturePreview(ImVec2(TEXTURE_SIZE, TEXTURE_SIZE), selectedTexture);
			ImGui::End();

			imguiEndFrame();
			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to viewZ 0.
			bgfx::touch(0);

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
	float    m_previewSize = 50.0f;
	bimg::TextureFormat::Enum m_selectedFormat = bimg::TextureFormat::Unknown;

	bgfx::TextureHandle m_textures[NUM_FORMATS];
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
		ExamplePixelFormats
	, "47-pixelformats"
	, "Texture formats."
	, "https://bkaradzic.github.io/bgfx/examples.html#pixelformats"
	);
