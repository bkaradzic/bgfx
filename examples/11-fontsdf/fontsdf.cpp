/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.h"
#include <bgfx.h>
#include <bx/timer.h>
#include "../common/entry.h"
#include "../common/dbg.h"
#include "../common/math.h"
#include "../common/processevents.h"

#include "../common/font/font_manager.h"
#include "../common/font/text_metrics.h"
#include "../common/font/text_buffer_manager.h"
#include "../common/imgui/imgui.h"

#include <stdio.h>
#include <string.h>

inline void mtxTranslate(float* _result, float x, float y, float z)
{
	memset(_result, 0, sizeof(float) * 16);
	_result[0] = _result[5] = _result[10] = _result[15] = 1.0f;
	_result[12] = x;
	_result[13] = y;
	_result[14] = z;
}

inline void mtxScale(float* _result, float x, float y, float z)
{
	memset(_result, 0, sizeof(float) * 16);
	_result[0] = x;
	_result[5] = y;
	_result[10] = z;
	_result[15] = 1.0f;
}

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

char* loadText(const char* _textFile)
{	
	FILE* pFile;
	pFile = fopen(_textFile, "rb");
	if (pFile == NULL)
	{		
		return NULL;
	}

	// Go to the end of the file.
	if (fseek(pFile, 0L, SEEK_END) == 0)
	{
		// Get the size of the file.
		long bufsize = ftell(pFile);
		if (bufsize == -1)
		{
			fclose(pFile);			
			return NULL;
		}

		char* buffer = new char[bufsize];

		// Go back to the start of the file.
		fseek(pFile, 0L, SEEK_SET);

		// Read the entire file into memory.
		uint32_t newLen = fread( (void*)buffer, sizeof(char), bufsize, pFile);
		if (newLen == 0)
		{
			fclose(pFile);
			delete[] buffer;
			return NULL;
		}

		fclose(pFile);

		return buffer;
	}
	return NULL;
}

int _main_(int /*_argc*/, char** /*_argv*/)
{
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();

	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR_BIT | BGFX_CLEAR_DEPTH_BIT
		, 0x303030ff
		, 1.0f
		, 0
		);

	FILE* file = fopen("font/droidsans.ttf", "rb");
	uint32_t size = (uint32_t)fsize(file);
	void* data = malloc(size);
	size_t ignore = fread(data, 1, size, file);
	BX_UNUSED(ignore);
	fclose(file);

	imguiCreate(data, size);

	free(data);

	char* bigText = loadText( "text/sherlock_holmes_a_scandal_in_bohemia_arthur_conan_doyle.txt");

	// Init the text rendering system.
	FontManager* fontManager = new FontManager(512);
	TextBufferManager* textBufferManager = new TextBufferManager(fontManager);

	TrueTypeHandle font_tt = fontManager->loadTrueTypeFromFile("font/special_elite.ttf");//bleeding_cowboys.ttf");

	// Create a distance field font.
	FontHandle base_distance_font = fontManager->createFontByPixelSize(font_tt, 0, 48, FONT_TYPE_DISTANCE);
	
	// Create a scaled down version of the same font (without adding anything to the atlas).
	FontHandle scaled_font = fontManager->createScaledFontToPixelSize(base_distance_font, 14);
		
	TextLineMetrics metrics(fontManager, scaled_font);		
	uint32_t lineCount = metrics.getLineCount(bigText);
	
	float visibleLineCount = 20.0f;

	const char* textBegin = 0;
	const char* textEnd = 0;
	metrics.getSubText(bigText, 0, (uint32_t)visibleLineCount, textBegin, textEnd);

	TextBufferHandle scrollableBuffer = textBufferManager->createTextBuffer(FONT_TYPE_DISTANCE, TRANSIENT);
	textBufferManager->setTextColor(scrollableBuffer, 0xFFFFFFFF);

	textBufferManager->appendText(scrollableBuffer, scaled_font, textBegin, textEnd);
	
	MouseState mouseState;
	int32_t scrollArea = 0;
	while (!processEvents(width, height, debug, reset, &mouseState) )
	{
		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT : 0)
			, 0
			, width
			, height
			);

		const int guiPanelWidth = 250;
		const int guiPanelHeight = 200;
	
		imguiBeginScrollArea("Text Area", width - guiPanelWidth - 10, 10, guiPanelWidth, guiPanelHeight, &scrollArea);
		imguiSeparatorLine();
				
		static float textScroll = 0.0f;
		static float textRotation = 0.0f;
		static float textScale = 1.0f;
		static float textSize = 14.0f;
		
		bool recomputeVisibleText = false;		
		recomputeVisibleText |= imguiSlider("Number of lines", &visibleLineCount, 1.0f, 177.0f , 1.0f);
		if(imguiSlider("Font size", &textSize, 6.0f, 64.0f , 1.0f))
		{
			fontManager->destroyFont(scaled_font);
			scaled_font = fontManager->createScaledFontToPixelSize(base_distance_font, (uint32_t) textSize);
			metrics = TextLineMetrics (fontManager, scaled_font);			
			recomputeVisibleText = true;
		}

		recomputeVisibleText |= imguiSlider("Scroll", &textScroll, 0.0f, (lineCount-visibleLineCount) , 1.0f);
		imguiSlider("Rotate", &textRotation, 0.0f, (float) M_PI *2.0f , 0.1f);
		recomputeVisibleText |= imguiSlider("Scale", &textScale, 0.1f, 10.0f , 0.1f);

		if(	recomputeVisibleText)
		{
			textBufferManager->clearTextBuffer(scrollableBuffer);
			metrics.getSubText(bigText,(uint32_t)textScroll, (uint32_t)(textScroll+visibleLineCount), textBegin, textEnd);			
			textBufferManager->appendText(scrollableBuffer, scaled_font, textBegin, textEnd);
		}			
		
		imguiEndScrollArea();
		
		imguiEndFrame();

		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::submit(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0 / freq;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/11-fontsdf");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Use a single distance field font to render text of various size.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime) * toMs);

		float at[3] = { 0, 0, 0.0f };
		float eye[3] = {0, 0, -1.0f };

		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);
		float centering = 0.5f;

		// Setup a top-left ortho matrix for screen space drawing.
		mtxOrtho(proj, centering, width + centering, height + centering, centering, -1.0f, 1.0f);
				
		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);
		
		//very crude approximation :(
		float textAreaWidth = 0.5f * 66.0f * fontManager->getFontInfo(scaled_font).maxAdvanceWidth;

		float textRotMat[16];
		float textCenterMat[16];
		float textScaleMat[16];
		float screenCenterMat[16];
		
		mtxRotateZ(textRotMat, textRotation);
		mtxTranslate(textCenterMat, -(textAreaWidth * 0.5f), (-visibleLineCount)*metrics.getLineHeight()*0.5f, 0);
		mtxScale(textScaleMat, textScale, textScale, 1.0f);
		mtxTranslate(screenCenterMat, ( (width) * 0.5f), ( (height) * 0.5f), 0);

		//first translate to text center, then scale, then rotate
		float tmpMat[16];
		mtxMul(tmpMat, textCenterMat, textRotMat);
		
		float tmpMat2[16];
		mtxMul(tmpMat2, tmpMat, textScaleMat);
		
		float tmpMat3[16];
		mtxMul(tmpMat3, tmpMat2, screenCenterMat);

		// Set model matrix for rendering.
		bgfx::setTransform(tmpMat3);
	
		// Draw your text.
		textBufferManager->submitTextBuffer(scrollableBuffer, 0);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	fontManager->unloadTrueType(font_tt);
	// Destroy the fonts.
	fontManager->destroyFont(base_distance_font);
	fontManager->destroyFont(scaled_font);

	textBufferManager->destroyTextBuffer(scrollableBuffer);

	delete textBufferManager;
	delete fontManager;

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
