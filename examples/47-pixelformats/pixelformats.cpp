/*
 * Copyright 2022-2022 Sandy Carter. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

#include <bx/allocator.h>
#include <bx/math.h>

#include <bimg/decode.h>

#include <tinystl/string.h>
#include <tinystl/vector.h>
namespace stl = tinystl;

namespace
{

constexpr int32_t kCheckerboardSize             = 128;
constexpr int32_t kFirstUncompressedFormatIndex = bgfx::TextureFormat::Unknown + 1;
constexpr int32_t kNumCompressedFormats         = bgfx::TextureFormat::Unknown;
constexpr int32_t kNumUncompressedFormats       = bgfx::TextureFormat::UnknownDepth - kFirstUncompressedFormatIndex;
constexpr int32_t kNumFormats                   = kNumCompressedFormats + kNumUncompressedFormats;
constexpr int32_t kNumFormatsInRow              = 10;

int32_t formatToIndex(bimg::TextureFormat::Enum _format)
{
	int32_t index = _format;

	if (index >= kFirstUncompressedFormatIndex)
	{
		--index;
	}

	return index;
}

bimg::TextureFormat::Enum indexToFormat(int32_t _index)
{
	if (_index < kNumCompressedFormats)
	{
		return bimg::TextureFormat::Enum(_index);
	}

	if (_index >= kNumCompressedFormats
	&&  _index <  kNumFormats)
	{
		return bimg::TextureFormat::Enum(_index + 1);
	}

	return bimg::TextureFormat::Unknown;
}

struct TextureStatus
{
	enum Enum
	{
		Ok,
		NotInitialized,
		FormatNotSupported,
		ConversionNotSupported,
		FormatIgnored
	};

	static const char* getDescription(Enum _value)
	{
		switch (_value)
		{
		case Ok:                     return "Ok";
		case NotInitialized:         return "Texture was not initialized";
		case FormatNotSupported:     return "Format not supported by GPU/backend";
		case ConversionNotSupported: return "Conversion from RGBA8 not supported";
		case FormatIgnored:          return "Format is ignored by this example";

		default:
			break;
		}

		return "Unknown";
	}

	static bool isError(Enum _value)
	{
		return false
			|| _value == FormatNotSupported
			|| _value == ConversionNotSupported
			;
	}
};

struct Texture
{
	uint16_t m_width  = 0;
	uint16_t m_height = 0;
	TextureStatus::Enum m_status = TextureStatus::NotInitialized;
	bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;
};

struct TextureSet
{
	stl::string m_name;
	uint16_t m_maxWidth  = 0;
	uint16_t m_maxHeight = 0;
	bool m_hasCompressedTextures = false;
	Texture m_textures[kNumFormats];
};

static bimg::ImageContainer* generateHueWheelImage()
{
	constexpr int32_t kTextureSize = 256;
	constexpr int32_t kHalfTextureSize = kTextureSize / 2;

	bimg::ImageContainer* image = bimg::imageAlloc(
		entry::getAllocator(),
		bimg::TextureFormat::RGBA32F,
		kTextureSize,
		kTextureSize,
		1,
		1,
		false,
		false,
		NULL
		);

	if (NULL == image)
	{
		return NULL;
	}

	float* rgbaf32Pixels = (float*)image->m_data;

	for (int32_t yy = 0 ; yy < kTextureSize; ++yy)
	{
		for (int32_t xx = 0; xx < kTextureSize; ++xx)
		{
			float relX = (xx - kHalfTextureSize) / (float) kHalfTextureSize;
			float relY = (yy - kHalfTextureSize) / (float) kHalfTextureSize;
			float distance = bx::min(1.0f, bx::sqrt(relX * relX + relY * relY) );
			float angle = bx::atan2(relY, relX);
			float* pixel = &rgbaf32Pixels[(xx + yy * kTextureSize) * 4];
			float hsv[3] = {angle / (2.0f * bx::kPi), 1.0f, 1.0f - distance};
			bx::hsvToRgb(pixel, hsv);
			pixel[3] = 1.0f - distance;
		}
	}

	for (int32_t yy = 0; yy < 16; ++yy)
	{
		for (int32_t xx = 0; xx < 16; ++xx)
		{
			float* rr = &rgbaf32Pixels[(xx + (kTextureSize - 36 + yy) * kTextureSize) * 4];
			rr[0] = 1.0f;
			rr[1] = 0.0f;
			rr[2] = 0.0f;
			rr[3] = 1.0f;

			float* gg = &rgbaf32Pixels[(xx + 16 + (kTextureSize - 36 + yy) * kTextureSize) * 4];
			gg[0] = 0.0f;
			gg[1] = 1.0f;
			gg[2] = 0.0f;
			gg[3] = 1.0f;

			float* bb = &rgbaf32Pixels[(xx + 32 + (kTextureSize - 36 + yy) * kTextureSize) * 4];
			bb[0] = 0.0f;
			bb[1] = 0.0f;
			bb[2] = 1.0f;
			bb[3] = 1.0f;
		}
	}

	for (int32_t yy = 0; yy < 16; ++yy)
	{
		for (int32_t xx = 0; xx < 48; ++xx)
		{
			float* aa = &rgbaf32Pixels[(xx + (kTextureSize - 20 + yy) * kTextureSize) * 4];
			aa[0] = 1.0f;
			aa[1] = 1.0f;
			aa[2] = 1.0f;
			aa[3] = 1.0f - (float)xx / 48.0f;
		}
	}

	return image;
}

static void textureSetPopulateCompressedFormat(TextureSet& textureSet, bimg::ImageContainer* source, bool freeImage = true)
{
	if (NULL == source)
	{
		return;
	}

	uint32_t textureIndex = indexToFormat(source->m_format);
	Texture& texture = textureSet.m_textures[textureIndex];

	if (bgfx::isValid(texture.m_texture) || texture.m_status == TextureStatus::FormatNotSupported)
	{
		if (freeImage)
		{
			bimg::imageFree(source);
		}

		return;
	}

	bimg::ImageMip mip0;
	bimg::imageGetRawData(
		  *source
		, 0
		, 0
		, source->m_data
		, source->m_size
		, mip0
	);

	texture.m_width   = uint16_t(mip0.m_width);
	texture.m_height  = uint16_t(mip0.m_height);
	texture.m_status  = TextureStatus::Ok;
	texture.m_texture = bgfx::createTexture2D(
		  uint16_t(mip0.m_width)
		, uint16_t(mip0.m_height)
		, false
		, 1
		, bgfx::TextureFormat::Enum(mip0.m_format)
		, BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT
		, bgfx::copy(mip0.m_data, mip0.m_size)
		);

	bgfx::setName(texture.m_texture, bimg::getName(source->m_format) );

	if (freeImage)
	{
		bimg::imageFree(source);
	}

	textureSet.m_maxWidth = bx::max(textureSet.m_maxWidth, texture.m_width);
	textureSet.m_maxHeight = bx::max(textureSet.m_maxHeight, texture.m_height);
}

static void textureSetPopulateUncompressedFormats(TextureSet& textureSet, bimg::ImageContainer* source, bool freeImage = true)
{
	if (NULL == source)
	{
		return;
	}

	const uint32_t flags = 0
		| BGFX_SAMPLER_MIN_POINT
		| BGFX_SAMPLER_MAG_POINT
		;

	for (int32_t ii = 0; ii < kNumUncompressedFormats; ++ii)
	{
		int32_t textureIndex = kNumCompressedFormats + ii;

		Texture& texture = textureSet.m_textures[textureIndex];

		if (bgfx::isValid(texture.m_texture)
		||  texture.m_status == TextureStatus::FormatNotSupported)
		{
			continue;
		}

		bimg::TextureFormat::Enum format = indexToFormat(textureIndex);
		const char* formatName = bimg::getName(format);
		int32_t formatNameLen = bx::strLen(formatName);

		if (!bimg::imageConvert(format, source->m_format) )
		{
			texture.m_status  = TextureStatus::ConversionNotSupported;
			continue;
		}

		if (formatName[formatNameLen - 1] == 'I'
		||  formatName[formatNameLen - 1] == 'U')
		{
			texture.m_status  = TextureStatus::FormatIgnored;
			continue;
		}

		bimg::TextureInfo info;
		bimg::imageGetSize(
			  &info
			, uint16_t(source->m_width)
			, uint16_t(source->m_height)
			, 1
			, false
			, false
			, 1
			, format
			);

		const bgfx::Memory* mem = bgfx::alloc(info.storageSize);
		bimg::imageConvert(
			  entry::getAllocator()
			, mem->data
			, info.format
			, source->m_data
			, source->m_format
			, source->m_width
			, source->m_height
			, 1
			);

		texture.m_width = info.width;
		texture.m_height = info.height;
		texture.m_status = TextureStatus::Ok;
		texture.m_texture = bgfx::createTexture2D(
			  info.width
			, info.height
			, info.numMips > 1
			, info.numLayers
			, bgfx::TextureFormat::Enum(info.format)
			, flags
			, mem
			);

		bgfx::setName(texture.m_texture, formatName);

		textureSet.m_maxWidth = bx::max(textureSet.m_maxWidth, texture.m_width);
		textureSet.m_maxHeight = bx::max(textureSet.m_maxHeight, texture.m_height);
	}

	if (freeImage)
	{
		bimg::imageFree(source);
	}
}

static TextureSet makeEmptyTextureSet(const char* name)
{
	TextureSet textureSet;
	textureSet.m_name = name;

	for (int32_t ii = 0; ii < kNumFormats; ++ii)
	{
		bimg::TextureFormat::Enum format = indexToFormat(ii);

		if (!bgfx::isTextureValid(
			  1
			, false
			, 1
			, bgfx::TextureFormat::Enum(format)
			, BGFX_TEXTURE_NONE
		) )
		{
			textureSet.m_textures[ii].m_status = TextureStatus::FormatNotSupported;
		}
	}

	return textureSet;
}

static TextureSet generateTextureSetFromImage(const char* name, bimg::ImageContainer* source, bool freeImage = true)
{
	TextureSet textureSet = makeEmptyTextureSet(name);

	if (NULL == source)
	{
		return textureSet;
	}

	textureSetPopulateUncompressedFormats(textureSet, source, freeImage);

	return textureSet;
}

static TextureSet generateTextureSetFromFileSet(const char* name, const char* filePaths[])
{
	TextureSet textureSet = makeEmptyTextureSet(name);

	while (NULL != *filePaths)
	{
		const char* filePath = *filePaths++;

		uint32_t size;
		void* data = load(filePath, &size);
		if (NULL == data)
		{
			continue;
		}

		bimg::ImageContainer* image = bimg::imageParse(entry::getAllocator(), data, size);
		if (NULL == image)
		{
			unload(data);
			continue;
		}

		if (bimg::isCompressed(image->m_format) )
		{
			textureSet.m_hasCompressedTextures = true;

			textureSetPopulateCompressedFormat(textureSet, image);
		}
		else
		{
			textureSetPopulateUncompressedFormats(textureSet, image);
		}
	}

	return textureSet;
}

static TextureSet generateTextureSetFromFile(const char* filePath)
{
	const char* filePaths[] =
	{
		filePath,
		NULL
	};

	return generateTextureSetFromFileSet(bx::FilePath(filePath).getFileName().getPtr(), filePaths);
}

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

		const bgfx::Memory* checkerboardImageMemory = bgfx::alloc(kCheckerboardSize * kCheckerboardSize * 4);

		bimg::imageCheckerboard(
			  checkerboardImageMemory->data
			, kCheckerboardSize
			, kCheckerboardSize
			, 16
			, 0xFF909090
			, 0xFF707070
			);

		m_checkerboard = bgfx::createTexture2D(
			  kCheckerboardSize
			, kCheckerboardSize
			, false
			, 1
			, bgfx::TextureFormat::RGBA8
			, BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT
			, checkerboardImageMemory
			);

		m_textureSets.push_back(generateTextureSetFromImage("Hue Wheel", generateHueWheelImage() ) );
		m_textureSets.push_back(generateTextureSetFromFile("textures/pf_alpha_test.dds") );
		m_textureSets.push_back(generateTextureSetFromFile("textures/pf_uv_filtering_test.dds") );

		const char* textureCompressionSetFiles[] =
		{
			"textures/texture_compression_astc_4x4.dds",
			"textures/texture_compression_astc_5x4.dds",
			"textures/texture_compression_astc_5x5.dds",
			"textures/texture_compression_astc_6x5.dds",
			"textures/texture_compression_astc_6x6.dds",
			"textures/texture_compression_astc_8x5.dds",
			"textures/texture_compression_astc_8x6.dds",
			"textures/texture_compression_astc_8x8.dds",
			"textures/texture_compression_astc_10x5.dds",
			"textures/texture_compression_astc_10x6.dds",
			"textures/texture_compression_astc_10x8.dds",
			"textures/texture_compression_astc_10x10.dds",
			"textures/texture_compression_astc_12x10.dds",
			"textures/texture_compression_astc_12x12.dds",
			"textures/texture_compression_atc.dds",
			"textures/texture_compression_atce.dds",
			"textures/texture_compression_atci.dds",
			"textures/texture_compression_bc1.ktx",
			"textures/texture_compression_bc2.ktx",
			"textures/texture_compression_bc3.ktx",
			"textures/texture_compression_bc7.ktx",
			"textures/texture_compression_etc1.ktx",
			"textures/texture_compression_etc2.ktx",
			"textures/texture_compression_ptc12.pvr",
			"textures/texture_compression_ptc14.pvr",
			"textures/texture_compression_ptc22.pvr",
			"textures/texture_compression_ptc24.pvr",
			"textures/texture_compression_rgba8.dds",
			NULL
		};

		m_textureSets.push_back(generateTextureSetFromFileSet("texture_compression_* set", textureCompressionSetFiles) );

		m_currentTextureSet = &m_textureSets[0];

		for (auto& textureSet : m_textureSets)
		{
			m_largestTextureSize = bx::max(m_largestTextureSize, float(bx::max(textureSet.m_maxWidth, textureSet.m_maxHeight) ) );
		}

		imguiCreate();
	}

	int32_t shutdown() override
	{
		imguiDestroy();

		for (auto& textureSet : m_textureSets)
		{
			for (auto texture : textureSet.m_textures)
			{
				if (bgfx::isValid(texture.m_texture) )
				{
					bgfx::destroy(texture.m_texture);
				}
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

	void imguiStrikethroughItem()
	{
		ImVec2 itemSize = ImGui::GetItemRectSize();
		if (itemSize.x <= 0.0f || itemSize.y <= 0.0f)
			return;

		ImVec2 p0 = ImGui::GetItemRectMin();
		ImVec2 p1 = ImGui::GetItemRectMax();
		p0.y = p1.y = p0.y + itemSize.y * 0.5f;

		ImGui::GetWindowDrawList()->AddLine(p0, p1, ImGui::GetColorU32(ImGuiCol_Text) );
	}

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
				static int64_t timeOffset = bx::getHPCounter();
				const float time = float( (bx::getHPCounter()-timeOffset)/double(bx::getHPFrequency() ) );
				const float animate = float(m_animate)*0.5f;
				const float xx = bx::sin(time * 0.37f) * animate;
				const float yy = bx::cos(time * 0.43f) * animate;

				const float uTile = bx::max(1.0f, previewSize.x / kCheckerboardSize);
				const float vTile = bx::max(1.0f, previewSize.y / kCheckerboardSize);

				ImGui::SetCursorScreenPos(previewPos);
				ImGui::Image(m_checkerboard, previewSize, ImVec2(xx, yy), ImVec2(xx+uTile, yy+vTile) );
			}

			ImGui::SetCursorScreenPos(previewPos);
			ImGui::Image(texture, m_useAlpha ? IMGUI_FLAGS_ALPHA_BLEND : IMGUI_FLAGS_NONE, 0, previewSize);
		}
		else
		{
			ImU32 color = ImGui::GetColorU32(ImGuiCol_Text, 0.25f);

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

			ImGui::SetNextWindowPos(ImVec2(340.0f, 10.0f), ImGuiCond_FirstUseEver);
			ImGui::Begin("Formats", NULL, ImGuiWindowFlags_None);

			ImVec2 previewSize = ImVec2(m_previewSize, m_previewSize);

			if (m_currentTextureSet->m_maxWidth > m_currentTextureSet->m_maxHeight)
			{
				previewSize.y /= float(m_currentTextureSet->m_maxWidth) / m_currentTextureSet->m_maxHeight;
			}
			else if (m_currentTextureSet->m_maxWidth < m_currentTextureSet->m_maxHeight)
			{
				previewSize.x *= float(m_currentTextureSet->m_maxWidth) / m_currentTextureSet->m_maxHeight;
			}

			float cellWidth = previewSize.x;
			for (int32_t ii = 0; ii < kNumFormats; ++ii)
			{
				int32_t format = indexToFormat(ii);
				ImVec2 textSize = ImGui::CalcTextSize(bimg::getName(bimg::TextureFormat::Enum(format) ) );
				cellWidth = bx::max(cellWidth, textSize.x);
			}

			ImDrawList* drawList = ImGui::GetWindowDrawList();

			if (ImGui::BeginCombo("Sample", m_currentTextureSet ? m_currentTextureSet->m_name.c_str() : NULL) )
			{
				for (auto& textureSet : m_textureSets)
				{
					bool isSelected = (&textureSet == m_currentTextureSet);
					if (ImGui::Selectable(textureSet.m_name.c_str(), &isSelected) )
					{
						m_currentTextureSet = &textureSet;
						if (!m_currentTextureSet->m_hasCompressedTextures && formatToIndex(m_selectedFormat) < kNumCompressedFormats)
						{
							m_selectedFormat = bimg::TextureFormat::RGBA8;
						}
					}
				}

				ImGui::EndCombo();
			}

			ImGui::DragFloat("Preview Size", &m_previewSize, 1.0f, 10.0f, m_largestTextureSize, "%.0f px");
			ImGui::SameLine();
			ImGui::Checkbox("Alpha", &m_useAlpha);
			ImGui::SameLine();
			ImGui::Checkbox("Animate", &m_animate);
			ImGui::BeginTable("Formats", kNumFormatsInRow, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit);

			for (int32_t ii = m_currentTextureSet->m_hasCompressedTextures ? 0 : kNumCompressedFormats; ii < kNumFormats; ++ii)
			{
				ImGui::TableNextColumn();

				bimg::TextureFormat::Enum format = indexToFormat(ii);
				const Texture& texture = m_currentTextureSet->m_textures[ii];

				bool isSelected = (m_selectedFormat == format);
				const bool isFormatSupported = texture.m_status == TextureStatus::Ok;
				const bool isError = TextureStatus::isError(texture.m_status);
				ImU32 labelColor = isError
					? IM_COL32(255, 96, 96, 255)
					: ImGui::GetColorU32(isFormatSupported ? ImGuiCol_Text : ImGuiCol_TextDisabled)
					;

				ImDrawListSplitter splitter;
				splitter.Split(drawList, 2);
				splitter.SetCurrentChannel(drawList, 1);

				ImGui::BeginGroup();
				ImGuiTextBuffer label;
				label.append(bimg::getName(bimg::TextureFormat::Enum(format) ) );
				ImGui::PushStyleColor(ImGuiCol_Text, labelColor);
				imguiTextBoxUnformatted(ImVec2(cellWidth, 0.0f), label.c_str() );

				if (TextureStatus::isError(texture.m_status) )
				{
					imguiStrikethroughItem();
				}

				imguiTexturePreview(ImVec2(cellWidth, previewSize.y), m_currentTextureSet->m_textures[ii].m_texture, previewSize );
				ImGui::PopStyleColor();
				ImGui::EndGroup();

				if (!isFormatSupported && ImGui::IsItemHovered() )
				{
					ImGui::SetTooltip("%s", TextureStatus::getDescription(texture.m_status) );
				}

				splitter.SetCurrentChannel(drawList, 0);
				ImGui::SetCursorScreenPos(ImGui::GetItemRectMin() );

				ImGui::PushID(ii);

				if (ImGui::Selectable(
					  "##selectable"
					, &isSelected
					, ImGuiSelectableFlags_AllowOverlap
					, ImGui::GetItemRectSize()
					) )
				{
					m_selectedFormat = format;
				}

				ImGui::PopID();

				splitter.Merge(drawList);
			}

			ImGui::EndTable();
			ImGui::End();

			{
				int32_t selectedTextureIndex = formatToIndex(m_selectedFormat);
				const Texture& texture = m_currentTextureSet->m_textures[selectedTextureIndex];

				ImGui::SetNextWindowPos(ImVec2(10.0f, 280.0f), ImGuiCond_FirstUseEver);
				ImGui::Begin("Selected Format", NULL, ImGuiWindowFlags_AlwaysAutoResize);
				ImGui::Text("Format: %s", bimg::getName(m_selectedFormat) );
				ImGui::Text("Status: %s", TextureStatus::getDescription(texture.m_status) );

				const bgfx::Caps* caps = bgfx::getCaps();

				const uint32_t formatFlags = caps->formats[m_selectedFormat];

				{
					bool emulated = 0 != (formatFlags & (0
						| BGFX_CAPS_FORMAT_TEXTURE_2D_EMULATED
						| BGFX_CAPS_FORMAT_TEXTURE_3D_EMULATED
						| BGFX_CAPS_FORMAT_TEXTURE_CUBE_EMULATED
						) );
					ImGui::PushEnabled(false);
					ImGui::Checkbox("Emu", &emulated);
					ImGui::PopEnabled();

					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled) )
					{
						ImGui::SetTooltip("Texture format is%s emulated.", emulated ? "" : " not");
					}
					ImGui::SameLine();

					bool framebuffer = 0 != (formatFlags & BGFX_CAPS_FORMAT_TEXTURE_FRAMEBUFFER);
					ImGui::PushEnabled(false);
					ImGui::Checkbox("FB", &framebuffer);
					ImGui::PopEnabled();

					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled) )
					{
						ImGui::SetTooltip("Texture format can%s be used as frame buffer.", framebuffer ? "" : "not");
					}
					ImGui::SameLine();

					bool msaa = 0 != (formatFlags & BGFX_CAPS_FORMAT_TEXTURE_MSAA);
					ImGui::PushEnabled(false);
					ImGui::Checkbox("MSAA", &msaa);
					ImGui::PopEnabled();

					if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled) )
					{
						ImGui::SetTooltip("Texture can%s be sampled as MSAA.", msaa ? "" : "not");
					}
				}

				ImVec2 size = ImVec2(float(m_currentTextureSet->m_maxWidth), float(m_currentTextureSet->m_maxHeight) );
				ImVec2 selectedPreviewSize = bgfx::isValid(texture.m_texture) ? ImVec2(float(texture.m_width), float(texture.m_height) ) : size;

				imguiTexturePreview(size, texture.m_texture, selectedPreviewSize);
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

	float    m_largestTextureSize = 256.0f;
	float    m_previewSize        = 75.0f;
	bool     m_useAlpha           = true;
	bool     m_animate            = true;

	bimg::TextureFormat::Enum m_selectedFormat = bimg::TextureFormat::RGBA8;

	bgfx::TextureHandle m_checkerboard = BGFX_INVALID_HANDLE;
	stl::vector<TextureSet> m_textureSets;
	TextureSet* m_currentTextureSet = NULL;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
		ExamplePixelFormats
	, "47-pixelformats"
	, "Texture formats."
	, "https://bkaradzic.github.io/bgfx/examples.html#pixelformats"
	);
