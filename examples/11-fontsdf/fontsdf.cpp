/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"

#include <bgfx/bgfx.h>
#include <bx/timer.h>
#include <bx/fpumath.h>

#include "font/font_manager.h"
#include "font/text_metrics.h"
#include "font/text_buffer_manager.h"
#include "imgui/imgui.h"

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
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);
		
		m_width = 1280;
		m_height = 720;
		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;
		
		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);
		
		// Enable debug text.
		bgfx::setDebug(m_debug);
		
		// Set view 0 clear state.
		bgfx::setViewClear(0
						   , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
						   , 0x303030ff
						   , 1.0f
						   , 0
						   );
		
		// Imgui.
		imguiCreate();
		
		m_bigText = (char*)load("text/sherlock_holmes_a_scandal_in_bohemia_arthur_conan_doyle.txt");
		
		// Init the text rendering system.
		m_fontManager = new FontManager(512);
		m_textBufferManager = new TextBufferManager(m_fontManager);
		
		m_font = loadTtf(m_fontManager, "font/special_elite.ttf");
		
		// Create a distance field font.
		m_fontSdf = m_fontManager->createFontByPixelSize(m_font, 0, 48, FONT_TYPE_DISTANCE);
		
		// Create a scaled down version of the same font (without adding anything to the atlas).
		m_fontScaled = m_fontManager->createScaledFontToPixelSize(m_fontSdf, 14);
		
		m_metrics = TextLineMetrics(m_fontManager->getFontInfo(m_fontScaled) );
		m_lineCount = m_metrics.getLineCount(m_bigText);
		
		m_visibleLineCount = 20.0f;
		
		m_textBegin = 0;
		m_textEnd = 0;
		m_metrics.getSubText(m_bigText, 0, (uint32_t)m_visibleLineCount, m_textBegin, m_textEnd);
		
		m_scrollableBuffer = m_textBufferManager->createTextBuffer(FONT_TYPE_DISTANCE, BufferType::Transient);
		m_textBufferManager->setTextColor(m_scrollableBuffer, 0xFFFFFFFF);
		
		m_textBufferManager->appendText(m_scrollableBuffer, m_fontScaled, m_textBegin, m_textEnd);
		
		m_scrollArea = 0;
		m_textScroll = 0.0f;
		m_textRotation = 0.0f;
		m_textScale = 1.0f;
		m_textSize = 14.0f;
	}
	
	virtual int shutdown() BX_OVERRIDE
	{
		
		imguiDestroy();
		
		BX_FREE(entry::getAllocator(), m_bigText);
		
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

	bool update() BX_OVERRIDE
	{
		
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx
							, m_mouseState.m_my
							, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
							| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
							| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
							, m_mouseState.m_mz
							, uint16_t(m_width)
							, uint16_t(m_height)
							);
			
			const int32_t guiPanelWidth = 250;
			const int32_t guiPanelHeight = 200;
			
			imguiBeginScrollArea("Text Area"
								 , m_width - guiPanelWidth - 10
								 , 10
								 , guiPanelWidth
								 , guiPanelHeight
								 , &m_scrollArea
								 );
			imguiSeparatorLine();
			
			bool recomputeVisibleText = false;
			recomputeVisibleText |= imguiSlider("Number of lines", m_visibleLineCount, 1.0f, 177.0f , 1.0f);
			if (imguiSlider("Font size", m_textSize, 6.0f, 64.0f , 1.0f) )
			{
				m_fontManager->destroyFont(m_fontScaled);
				m_fontScaled = m_fontManager->createScaledFontToPixelSize(m_fontSdf, (uint32_t) m_textSize);
				m_metrics = TextLineMetrics(m_fontManager->getFontInfo(m_fontScaled) );
				recomputeVisibleText = true;
			}
			
			recomputeVisibleText |= imguiSlider("Scroll", m_textScroll, 0.0f, (m_lineCount-m_visibleLineCount) , 1.0f);
			imguiSlider("Rotate", m_textRotation, 0.0f, bx::kPi*2.0f , 0.1f);
			recomputeVisibleText |= imguiSlider("Scale", m_textScale, 0.1f, 10.0f , 0.1f);
			
			if (recomputeVisibleText)
			{
				m_textBufferManager->clearTextBuffer(m_scrollableBuffer);
				m_metrics.getSubText(m_bigText,(uint32_t)m_textScroll, (uint32_t)(m_textScroll+m_visibleLineCount), m_textBegin, m_textEnd);
				m_textBufferManager->appendText(m_scrollableBuffer, m_fontScaled, m_textBegin, m_textEnd);
			}
			
			imguiEndScrollArea();
			
			imguiEndFrame();
			
			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			
			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);
			
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0 / freq;
			
			// Use debug font to print32_t information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/11-fontsdf");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Use a single distance field font to render text of various size.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime) * toMs);
			
			float at[3]  = { 0, 0, 0.0f };
			float eye[3] = {0, 0, -1.0f };
			
			float view[16];
			bx::mtxLookAt(view, eye, at);
			
			const float centering = 0.5f;
			
			// Setup a top-left ortho matrix for screen space drawing.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
			{
				float proj[16];
				bx::mtxProj(proj, hmd->eye[0].fov, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
				
				static float time = 0.0f;
				time += 0.05f;
				
				const float dist = 10.0f;
				const float offset0 = -proj[8] + (hmd->eye[0].viewOffset[0] / dist * proj[0]);
				const float offset1 = -proj[8] + (hmd->eye[1].viewOffset[0] / dist * proj[0]);
				
				float ortho[2][16];
				const float viewOffset = m_width/4.0f;
				const float viewWidth  = m_width/2.0f;
				bx::mtxOrtho(ortho[0], centering + viewOffset, centering + viewOffset + viewWidth, m_height + centering, centering, -1.0f, 1.0f, offset0);
				bx::mtxOrtho(ortho[1], centering + viewOffset, centering + viewOffset + viewWidth, m_height + centering, centering, -1.0f, 1.0f, offset1);
				bgfx::setViewTransform(0, view, ortho[0], BGFX_VIEW_STEREO, ortho[1]);
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				float ortho[16];
				bx::mtxOrtho(ortho, centering, m_width + centering, m_height + centering, centering, -1.0f, 1.0f);
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

	entry::MouseState m_mouseState;
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	
	char* m_bigText;
	
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
	
	int32_t m_scrollArea;
	float m_textScroll;
	float m_textRotation;
	float m_textScale;
	float m_textSize;
};

ENTRY_IMPLEMENT_MAIN(ExampleFontSDF);
