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

			float col1Length = ImGui::CalcTextSize("Format").x;
			for (int i = 0; i < NUM_FORMATS; ++i)
			{
				int format = (int)bgfx::TextureFormat::Unknown + 1 + i;
				ImVec2 textSize = ImGui::CalcTextSize(bimg::getName(bimg::TextureFormat::Enum(format)));
				col1Length = bx::max(col1Length, textSize.x);
			}
			col1Length += 25.0f;

			ImGui::Begin("Formats");
			ImGui::Text("Format");
			ImGui::SameLine(col1Length);
			ImGui::Text("Texture");
			ImGui::Separator();
			for (int i = 0; i < NUM_FORMATS; ++i)
			{
				int format = (int)bgfx::TextureFormat::Unknown + 1 + i;
				ImGui::Text("%s", bimg::getName(bimg::TextureFormat::Enum(format)));
				ImGui::SameLine(col1Length);
				if (bgfx::isValid(m_textures[i]))
				{
					ImGui::Image(m_textures[i], ImVec2(50.0f, 50.0f));
					if (ImGui::IsItemHovered())
					{
						ImVec2 windowTopLeft = ImGui::GetMousePos();
						windowTopLeft.x += 10;
						ImGuiStyle& style = ImGui::GetStyle();
						float titleBarHeight = ImGui::GetFontSize() + style.FramePadding.y * 2;
						ImVec2 windowBottomRight = {
							windowTopLeft.x + TEXTURE_SIZE + 2 * style.WindowPadding.x,
							windowTopLeft.y + TEXTURE_SIZE + 2 * style.WindowPadding.y + titleBarHeight
						};
						if (windowBottomRight.x > m_width)
						{
							windowTopLeft.x -= windowBottomRight.x - m_width;
						}
						if (windowBottomRight.y > m_height)
						{
							windowTopLeft.y -= windowBottomRight.y - m_height;
						}
						ImGui::SetNextWindowPos(windowTopLeft);
						ImGuiWindowFlags flags = 0
							| ImGuiWindowFlags_NoResize
							| ImGuiWindowFlags_NoScrollbar
							| ImGuiWindowFlags_NoCollapse
							| ImGuiWindowFlags_NoInputs
							;

						ImGui::Begin(bimg::getName(bimg::TextureFormat::Enum(format)), NULL, flags);
						ImGui::Image(m_textures[i], ImVec2(TEXTURE_SIZE, TEXTURE_SIZE));
						ImGui::End();
					}
				}
				else
				{
					ImGui::Text("INVALID");
				}
				ImGui::Separator();
			}
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

	bgfx::TextureHandle m_textures[NUM_FORMATS];
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
		ExamplePixelFormats
	, "47-pixelformats"
	, "Texture formats."
	, "https://bkaradzic.github.io/bgfx/examples.html#pixelformats"
	);
