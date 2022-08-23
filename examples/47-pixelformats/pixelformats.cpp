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

constexpr int32_t kTextureSize = 256;
constexpr int32_t kHalfTextureSize = kTextureSize / 2;
constexpr int32_t kNumFormats = bgfx::TextureFormat::UnknownDepth - bgfx::TextureFormat::Unknown - 1;
const     int32_t kNumFormatsInRow = (int32_t)bx::ceil(bx::sqrt(kNumFormats) );

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

		float* rgbaf32Pixels = (float*)BX_ALLOC(entry::getAllocator(), kTextureSize * kTextureSize * 4 * sizeof(float) );

		for (int32_t y = 0 ; y < kTextureSize; ++y)
		{
			for (int32_t x = 0; x < kTextureSize; ++x)
			{
				float relX = (x - kHalfTextureSize) / (float) kHalfTextureSize;
				float relY = (y - kHalfTextureSize) / (float) kHalfTextureSize;
				float distance = bx::min(1.0f, bx::sqrt(relX * relX + relY * relY) );
				float angle = bx::atan2(relY, relX);
				float* pixel = &rgbaf32Pixels[(x + y * kTextureSize) * 4];
				float hsv[3] = {angle / (2.0f * bx::kPi), 1.0f, 1.0f - distance};
				bx::hsvToRgb(pixel, hsv);
				pixel[3] = 1.0f - distance;
			}
		}

		for (int32_t y = 0; y < 16; ++y)
		{
			for (int32_t x = 0; x < 16; ++x)
			{
				float* r = &rgbaf32Pixels[(x + (kTextureSize - 36 + y) * kTextureSize) * 4];
				r[0] = 1.0f;
				r[1] = 0.0f;
				r[2] = 0.0f;
				r[3] = 1.0f;

				float* g = &rgbaf32Pixels[(x + 16 + (kTextureSize - 36 + y) * kTextureSize) * 4];
				g[0] = 0.0f;
				g[1] = 1.0f;
				g[2] = 0.0f;
				g[3] = 1.0f;

				float* b = &rgbaf32Pixels[(x + 32 + (kTextureSize - 36 + y) * kTextureSize) * 4];
				b[0] = 0.0f;
				b[1] = 0.0f;
				b[2] = 1.0f;
				b[3] = 1.0f;
			}
		}

		for (int32_t y = 0; y < 16; ++y)
		{
			for (int32_t x = 0; x < 48; ++x)
			{
				float* a = &rgbaf32Pixels[(x + (kTextureSize - 20 + y) * kTextureSize) * 4];
				a[0] = 1.0f;
				a[1] = 1.0f;
				a[2] = 1.0f;
				a[3] = 1.0f - (float)x / 48.0f;
			}
		}

		for (int32_t i = 0; i < kNumFormats; ++i)
		{
			int32_t format = (int32_t)bgfx::TextureFormat::Unknown + 1 + i;
			const char* formatName = bimg::getName(bimg::TextureFormat::Enum(format) );
			int32_t formatNameLen = bx::strLen(formatName);

			if (!bimg::imageConvert(bimg::TextureFormat::Enum(format), bimg::TextureFormat::RGBA32F)
			||  formatName[formatNameLen - 1] == 'I'
			||  formatName[formatNameLen - 1] == 'U'
				)
			{
				m_textures[i] = BGFX_INVALID_HANDLE;
				continue;
			}

			bimg::TextureInfo info;
			bimg::imageGetSize(
				  &info
				, kTextureSize
				, kTextureSize
				, 1
				, false
				, false
				, 1
				, bimg::TextureFormat::Enum(format)
				);

			const bgfx::Memory* mem = bgfx::alloc(info.storageSize);
			bimg::imageConvert(
				  entry::getAllocator()
				, mem->data
				, info.format
				, rgbaf32Pixels
				, bimg::TextureFormat::RGBA32F
				, kTextureSize
				, kTextureSize
				, 1
				);

			m_textures[i] = bgfx::createTexture2D(
				  info.width
				, info.height
				, info.numMips > 1
				, info.numLayers
				, bgfx::TextureFormat::Enum(info.format)
				, flags
				, mem
				);

			bgfx::setName(m_textures[i], formatName);
			bgfx::setViewName(bgfx::ViewId(i + 1), formatName);
		}

		const bgfx::Memory* checkerboardImageMemory = bgfx::alloc(kTextureSize * kTextureSize * 4);
		bimg::imageCheckerboard(
			  checkerboardImageMemory->data
			, kTextureSize
			, kTextureSize
			, 16
			, 0xFF909090
			, 0xFF707070
			);
		m_checkerboard = bgfx::createTexture2D(
			  kTextureSize
			, kTextureSize
			, false
			, 1
			, bgfx::TextureFormat::RGBA8
			, flags
			, checkerboardImageMemory
			);

		BX_FREE(entry::getAllocator(), rgbaf32Pixels);

		imguiCreate();
	}

	int32_t shutdown() override
	{
		imguiDestroy();

		for (auto texture : m_textures)
		{
			if (bgfx::isValid(texture) )
			{
				bgfx::destroy(texture);
			}
		}

		if (bgfx::isValid(m_checkerboard) )
		{
			bgfx::destroy(m_checkerboard);
		}

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	void imguiTextBoxUnformatted(const ImVec2& size, const char* text) const
	{
		ImVec2 textSize = ImGui::CalcTextSize(text);
		ImVec2 textOffset = ImVec2(
			  size.x >= 0.0f ? bx::max( (size.x - textSize.x) / 2, 0.0f) : 0.0f
			, size.y >= 0.0f ? bx::max( (size.y - textSize.y) / 2, 0.0f) : 0.0f
			);
		ImGui::SetCursorPos(ImVec2(
			  ImGui::GetCursorPosX() + textOffset.x
			, ImGui::GetCursorPosY() + textOffset.y
			) );
		ImGui::TextUnformatted(text);
	};

	void imguiTexturePreview(const ImVec2& size, bgfx::TextureHandle texture, const ImVec2& previewSizeHint = ImVec2(-1.0f, -1.0f) ) const
	{
		ImVec2 origin = ImGui::GetCursorScreenPos();

		ImVec2 previewSize = ImVec2(
			  previewSizeHint.x >= 0.0f ? previewSizeHint.x : size.x
			, previewSizeHint.y >= 0.0f ? previewSizeHint.y : size.y
			);

		ImVec2 previewPos = ImVec2(
			  origin.x + bx::max(0.0f, (size.x - previewSize.x) / 2)
			, origin.y + bx::max(0.0f, (size.y - previewSize.y) / 2)
			);

		if (bgfx::isValid(texture) )
		{
			if (bgfx::isValid(m_checkerboard) )
			{
				ImGui::SetCursorScreenPos(previewPos);
				ImGui::Image(m_checkerboard, previewSize);
			}

			ImGui::SetCursorScreenPos(previewPos);
			ImGui::Image(texture, m_useAlpha ? IMGUI_FLAGS_ALPHA_BLEND : IMGUI_FLAGS_NONE, 0, previewSize);
		}
		else
		{
			ImU32 color = ImGui::GetColorU32(ImGuiCol_TextDisabled, 0.25f);

			ImDrawList* drawList = ImGui::GetWindowDrawList();
			ImVec2 p0 = previewPos;
			ImVec2 p1 = ImVec2(p0.x + previewSize.x, p0.y + previewSize.y);
			drawList->AddRect(p0, p1, color);
			drawList->AddLine(p0, p1, color);
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
			ImGui::Begin("Formats", NULL, ImGuiWindowFlags_AlwaysAutoResize);

			float cellWidth = m_previewSize;
			for (int32_t i = 0; i < kNumFormats; ++i)
			{
				int32_t format = (int32_t)bgfx::TextureFormat::Unknown + 1 + i;
				ImVec2 textSize = ImGui::CalcTextSize(bimg::getName(bimg::TextureFormat::Enum(format) ) );
				cellWidth = bx::max(cellWidth, textSize.x);
			}

			ImDrawList* drawList = ImGui::GetWindowDrawList();

			ImGui::DragFloat("Preview Size", &m_previewSize, 1.0f, 10.0f, kTextureSize);
			ImGui::SameLine();
			ImGui::Checkbox("Alpha", &m_useAlpha);
			ImGui::BeginTable("Formats", kNumFormatsInRow, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit);

			for (int32_t i = 0; i < kNumFormats; ++i)
			{
				ImGui::TableNextColumn();

				int32_t format = (int32_t)bgfx::TextureFormat::Unknown + 1 + i;

				bool isSelected = (m_selectedFormat == format);

				ImDrawListSplitter splitter;
				splitter.Split(drawList, 2);
				splitter.SetCurrentChannel(drawList, 1);

				ImGui::BeginGroup();
				ImGuiTextBuffer label;
				label.append(bimg::getName(bimg::TextureFormat::Enum(format) ) );
				imguiTextBoxUnformatted(ImVec2(cellWidth, 0.0f), label.c_str() );
				imguiTexturePreview(ImVec2(cellWidth, m_previewSize), m_textures[i], ImVec2(m_previewSize, m_previewSize) );

				ImGui::EndGroup();

				splitter.SetCurrentChannel(drawList, 0);
				ImGui::SetCursorScreenPos(ImGui::GetItemRectMin() );

				ImGui::PushID(i);

				if (ImGui::Selectable(
					  "##selectable"
					, &isSelected
					, ImGuiSelectableFlags_AllowItemOverlap
					, ImGui::GetItemRectSize()
					) )
				{
					m_selectedFormat = bimg::TextureFormat::Enum(format);
				}

				ImGui::PopID();

				splitter.Merge(drawList);
			}

			ImGui::EndTable();
			ImGui::End();

			{
				ImGui::SetNextWindowPos(ImVec2(40.0f, 300.0f), ImGuiCond_FirstUseEver);
				ImGui::Begin("Selected Format", NULL, ImGuiWindowFlags_AlwaysAutoResize);
				ImGui::Text("Format: %s", bimg::getName(m_selectedFormat) );

				const bgfx::Caps* caps = bgfx::getCaps();

				if (caps->formats[m_selectedFormat] == BGFX_CAPS_FORMAT_TEXTURE_NONE)
				{
					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 10.0f));
					ImGui::Text("Not supported!");
					ImGui::PopStyleVar();
				}
				else
				{
					const uint32_t formatFlags = caps->formats[m_selectedFormat];

					bool emulated = 0 != (formatFlags & (0
						| BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED
						| BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED
						| BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED
						) );
					ImGui::PushEnabled(false);
					ImGui::Checkbox("Emu", &emulated);
					ImGui::PopEnabled();
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					{
						ImGui::SetTooltip("Texture format is emulated.");
					}
					ImGui::SameLine();

					bool framebuffer = 0 != (formatFlags & BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER);
					ImGui::PushEnabled(false);
					ImGui::Checkbox("FB", &framebuffer);
					ImGui::PopEnabled();
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					{
						ImGui::SetTooltip("Texture format can be used as frame buffer.");
					}
					ImGui::SameLine();

					bool msaa = 0 != (formatFlags & BGFX_CAPS_FORMAT_TEXTURE_MSAA);
					ImGui::PushEnabled(false);
					ImGui::Checkbox("MSAA", &msaa);
					ImGui::PopEnabled();
					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					{
						ImGui::SetTooltip("Texture can be sampled as MSAA.");
					}

				}

				int32_t selectedTextureIndex = m_selectedFormat - 1 - (int32_t)bimg::TextureFormat::Unknown;

				bgfx::TextureHandle selectedTexture = BGFX_INVALID_HANDLE;

				if (m_selectedFormat != bimg::TextureFormat::Unknown)
				{
					selectedTexture = m_textures[selectedTextureIndex];
				}

				imguiTexturePreview(ImVec2(kTextureSize, kTextureSize), selectedTexture);
				ImGui::End();
			}

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
	bool     m_useAlpha = true;
	bimg::TextureFormat::Enum m_selectedFormat = bimg::TextureFormat::RGBA8;

	bgfx::TextureHandle m_checkerboard = BGFX_INVALID_HANDLE;
	bgfx::TextureHandle m_textures[kNumFormats];
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
		ExamplePixelFormats
	, "47-pixelformats"
	, "Texture formats."
	, "https://bkaradzic.github.io/bgfx/examples.html#pixelformats"
	);
