/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"

#include <bgfx/bgfx.h>
#include <bx/timer.h>
#include <bx/math.h>

#include "font/font_manager.h"
#include "font/text_metrics.h"
#include "font/text_buffer_manager.h"
#include "imgui/imgui.h"

namespace
{

TrueTypeHandle loadTtf(FontManager* _fm, const char* _filePath)
{
	uint32_t size;
	void* data = load(_filePath, &size);

	if (NULL != data)
	{
		TrueTypeHandle handle = _fm->createTtf( (uint8_t*)data, size);
		BX_FREE(entry::getAllocator(), data);
		return handle;
	}

	TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
	return invalid;
}

class ExampleFontSDF : public entry::AppI
{
public:
	ExampleFontSDF(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug = BGFX_DEBUG_NONE;
		m_reset = BGFX_RESET_VSYNC;

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
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
			);

		// Initialize Imgui
		// This initializes the same allocator used by stb_truetype, so must do that before creating the font manager
		imguiCreate();

		uint32_t size;
		m_txtFile = load("text/sherlock_holmes_a_scandal_in_bohemia_arthur_conan_doyle.txt", &size);
		m_bigText = bx::StringView( (const char*)m_txtFile, size);

		// Set up some defaults.
		m_outlineColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		m_outlineWidth = 1.0f;
		m_dropShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);
		m_dropShadowOffsetX = 1.0f;
		m_dropShadowOffsetY = 1.0f;
		m_dropShadowSoftener = 2.0f;

		m_textScroll = 0.0f;
		m_textRotation = 0.0f;
		m_textScale = 1.0f;
		m_textSize = 14.0f;

		// Init the text rendering system.
		m_fontManager = NULL;
		m_textBufferManager = NULL;
		m_font = BGFX_INVALID_HANDLE;
		m_fontSdf = BGFX_INVALID_HANDLE;
		m_fontScaled = BGFX_INVALID_HANDLE;
		m_scrollableBuffer = BGFX_INVALID_HANDLE;

		initializeFont(FONT_TYPE_DISTANCE);

		m_lineCount = m_metrics.getLineCount(m_bigText);

		m_visibleLineCount = 20.0f;

		m_textBegin = 0;
		m_textEnd = 0;
		m_metrics.getSubText(m_bigText, 0, (uint32_t)m_visibleLineCount, m_textBegin, m_textEnd);

		initializeTextBuffer(FONT_TYPE_DISTANCE);

		applyTextBufferAttributes();

		m_textBufferManager->appendText(m_scrollableBuffer, m_fontScaled, m_textBegin, m_textEnd);
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		unload(m_txtFile);

		m_fontManager->destroyTtf(m_font);
		// Destroy the fonts.
		m_fontManager->destroyFont(m_fontSdf);
		m_fontManager->destroyFont(m_fontScaled);

		m_textBufferManager->destroyTextBuffer(m_scrollableBuffer);

		delete m_textBufferManager;
		delete m_fontManager;

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

			bool recomputeVisibleText = false;

			static int fontTypeIndex = 0;
			if (ImGui::Combo("SDF Font Type", &fontTypeIndex, "Standard\0Outline\0Outline_Image\0DropShadow\0DropShadow_Image\0Outline_DropShadow_Image\0\0"))
			{
				uint32_t fontTypeList[] =
				{
					FONT_TYPE_DISTANCE,
					FONT_TYPE_DISTANCE_OUTLINE,
					FONT_TYPE_DISTANCE_OUTLINE_IMAGE,
					FONT_TYPE_DISTANCE_DROP_SHADOW,
					FONT_TYPE_DISTANCE_DROP_SHADOW_IMAGE,
					FONT_TYPE_DISTANCE_OUTLINE_DROP_SHADOW_IMAGE
				};
				uint32_t fontType = fontTypeList[fontTypeIndex];

				initializeFont(fontType);
				initializeTextBuffer(fontType);
				recomputeVisibleText = true;
			}

			if (ImGui::SliderFloat("Font size", &m_textSize, 6.0f, 64.0f) )
			{
				m_fontManager->destroyFont(m_fontScaled);
				m_fontScaled = m_fontManager->createScaledFontToPixelSize(m_fontSdf, (uint32_t) m_textSize);
				m_metrics = TextLineMetrics(m_fontManager->getFontInfo(m_fontScaled) );
				recomputeVisibleText = true;
			}

			if (ImGui::ColorEdit3("Outline Color", (float*)&m_outlineColor))
			{
				recomputeVisibleText = true;
			}
			if (ImGui::SliderFloat("Outline Width", &m_outlineWidth, 0.5f, 5.0f))
			{
				recomputeVisibleText = true;
			}
			if (ImGui::ColorEdit4("Drop Shadow Color", (float*)&m_dropShadowColor))
			{
				recomputeVisibleText = true;
			}
			if (ImGui::SliderFloat("Drop Shadow Offset X", &m_dropShadowOffsetX, -5.0f, 5.0f))
			{
				recomputeVisibleText = true;
			}
			if (ImGui::SliderFloat("Drop Shadow Offset Y", &m_dropShadowOffsetY, -5.0f, 5.0f))
			{
				recomputeVisibleText = true;
			}
			if (ImGui::SliderFloat("Drop Shadow Softener", &m_dropShadowSoftener, 0.0f, 5.0f))
			{
				recomputeVisibleText = true;
			}

			recomputeVisibleText |= ImGui::SliderFloat("# of lines", &m_visibleLineCount, 1.0f, 177.0f);
			recomputeVisibleText |= ImGui::SliderFloat("Scroll", &m_textScroll, 0.0f, (m_lineCount-m_visibleLineCount));
			ImGui::SliderFloat("Rotate", &m_textRotation, 0.0f, bx::kPi*2.0f);
			recomputeVisibleText |= ImGui::SliderFloat("Scale", &m_textScale, 0.1f, 10.0f);

			if (recomputeVisibleText)
			{
				m_textBufferManager->clearTextBuffer(m_scrollableBuffer);

				applyTextBufferAttributes();

				m_metrics.getSubText(m_bigText,(uint32_t)m_textScroll, (uint32_t)(m_textScroll+m_visibleLineCount), m_textBegin, m_textEnd);
				m_textBufferManager->appendText(m_scrollableBuffer, m_fontScaled, m_textBegin, m_textEnd);
			}

			ImGui::End();

			imguiEndFrame();

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -1.0f };

			float view[16];
			bx::mtxLookAt(view, eye, at);

			float centering = 0.0f;
			if (bgfx::getRendererType() == bgfx::RendererType::Direct3D9) {
				centering = -0.5f;
			}

			// Setup a top-left ortho matrix for screen space drawing.
			const bgfx::Caps* caps = bgfx::getCaps();
			{
				float ortho[16];
				bx::mtxOrtho(ortho, centering, m_width + centering, m_height + centering, centering, -1.0f, 1.0f, 0.0f, caps->homogeneousDepth);
				bgfx::setViewTransform(0, view, ortho);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			//very crude approximation :(
			float textAreaWidth = 0.5f * 66.0f * m_fontManager->getFontInfo(m_fontScaled).maxAdvanceWidth;

			float textRotMat[16];
			float textCenterMat[16];
			float textScaleMat[16];
			float screenCenterMat[16];

			bx::mtxRotateZ(textRotMat, m_textRotation);
			bx::mtxTranslate(textCenterMat, -(textAreaWidth * 0.5f), (-m_visibleLineCount)*m_metrics.getLineHeight()*0.5f, 0);
			bx::mtxScale(textScaleMat, m_textScale, m_textScale, 1.0f);
			bx::mtxTranslate(screenCenterMat, ( (m_width) * 0.5f), ( (m_height) * 0.5f), 0);

			//first translate to text center, then scale, then rotate
			float tmpMat[16];
			bx::mtxMul(tmpMat, textCenterMat, textRotMat);

			float tmpMat2[16];
			bx::mtxMul(tmpMat2, tmpMat, textScaleMat);

			float tmpMat3[16];
			bx::mtxMul(tmpMat3, tmpMat2, screenCenterMat);

			// Set model matrix for rendering.
			bgfx::setTransform(tmpMat3);

			// Draw your text.
			m_textBufferManager->submitTextBuffer(m_scrollableBuffer, 0);

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	void initializeFont(uint32_t fontType)
	{
		if (m_font.idx != bgfx::kInvalidHandle)
		{
			m_fontManager->destroyTtf(m_font);
		}

		if (m_scrollableBuffer.idx != bgfx::kInvalidHandle)
		{
			m_textBufferManager->destroyTextBuffer(m_scrollableBuffer);
		}

		if (m_fontScaled.idx != bgfx::kInvalidHandle)
		{
			m_fontManager->destroyFont(m_fontScaled);
		}
		if (m_fontSdf.idx != bgfx::kInvalidHandle)
		{
			m_fontManager->destroyFont(m_fontSdf);
		}

		delete m_textBufferManager;
		delete m_fontManager;

		m_fontManager = new FontManager(512);
		m_textBufferManager = new TextBufferManager(m_fontManager);

		m_font = loadTtf(m_fontManager, "font/special_elite.ttf");

		m_fontSdf = m_fontManager->createFontByPixelSize(m_font, 0, 48, fontType, 6 + 2, 6 + 2);

		m_fontScaled = m_fontManager->createScaledFontToPixelSize(m_fontSdf, (uint32_t) m_textSize);

		if (fontType & FONT_TYPE_MASK_DISTANCE_IMAGE)
		{
			float extraScale = 2.0f;
			bimg::ImageContainer* glyphImage = imageLoad("font/glyph_space.png", bgfx::TextureFormat::Enum::BGRA8);
			m_fontManager->addGlyphBitmap(m_fontSdf, 32, (uint16_t)glyphImage->m_width, (uint16_t)glyphImage->m_height, (uint16_t)(glyphImage->m_width * 4), extraScale, (const uint8_t*)glyphImage->m_data, 0.0f, -3.0f);

			glyphImage = imageLoad("font/glyph_long.png", bgfx::TextureFormat::Enum::BGRA8);
			m_fontManager->addGlyphBitmap(m_fontSdf, 65, (uint16_t)glyphImage->m_width, (uint16_t)glyphImage->m_height, (uint16_t)(glyphImage->m_width * 4), extraScale, (const uint8_t*)glyphImage->m_data, 0.0f, -3.0f);
		}

		m_metrics = TextLineMetrics(m_fontManager->getFontInfo(m_fontScaled) );
	}

	void initializeTextBuffer(uint32_t fontType)
	{
		m_scrollableBuffer = m_textBufferManager->createTextBuffer(fontType, BufferType::Transient);
	}

	void applyTextBufferAttributes()
	{
		m_textBufferManager->setTextColor(m_scrollableBuffer, 0xFFFFFFFF);
		m_textBufferManager->setOutlineColor(m_scrollableBuffer, ((uint32_t)(m_outlineColor.x * 255) << 24) | ((uint32_t)(m_outlineColor.y * 255) << 16) | ((uint32_t)(m_outlineColor.z * 255) << 8) | ((uint32_t)(m_outlineColor.w * 255)));
		m_textBufferManager->setOutlineWidth(m_scrollableBuffer, m_outlineWidth);
		m_textBufferManager->setDropShadowColor(m_scrollableBuffer, ((uint32_t)(m_dropShadowColor.x * 255) << 24) | ((uint32_t)(m_dropShadowColor.y * 255) << 16) | ((uint32_t)(m_dropShadowColor.z * 255) << 8) | ((uint32_t)(m_dropShadowColor.w * 255)));
		m_textBufferManager->setDropShadowOffset(m_scrollableBuffer, m_dropShadowOffsetX, m_dropShadowOffsetY);
		m_textBufferManager->setDropShadowSoftener(m_scrollableBuffer, m_dropShadowSoftener);
	}

	entry::MouseState m_mouseState;
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	void* m_txtFile;
	bx::StringView m_bigText;

	// Init the text rendering system.
	FontManager* m_fontManager;
	TextBufferManager* m_textBufferManager;

	TrueTypeHandle m_font;
	FontHandle m_fontSdf;
	FontHandle m_fontScaled;

	TextBufferHandle m_scrollableBuffer;

	TextLineMetrics m_metrics = TextLineMetrics(FontInfo());
	uint32_t m_lineCount;
	float m_visibleLineCount;
	const char* m_textBegin;
	const char* m_textEnd;

	ImVec4 m_outlineColor;
	float m_outlineWidth;
	ImVec4 m_dropShadowColor;
	float m_dropShadowOffsetX;
	float m_dropShadowOffsetY;
	float m_dropShadowSoftener;

	float m_textScroll;
	float m_textRotation;
	float m_textScale;
	float m_textSize;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleFontSDF
	, "11-fontsdf"
	, "Use a single distance field font to render text of various size."
	, "https://bkaradzic.github.io/bgfx/examples.html#fontsdf"
	);
