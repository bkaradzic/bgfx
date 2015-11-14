/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
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

#include <stdio.h>
#include <string.h>

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

static char* loadText(const char* _filePath)
{
	FILE* file = fopen(_filePath, "rb");
	if (NULL != file)
	{
		uint32_t size = (uint32_t)fsize(file);
		char* mem = (char*)malloc(size+1);
		size_t ignore = fread(mem, 1, size, file);
		BX_UNUSED(ignore);
		fclose(file);
		mem[size-1] = '\0';
		return mem;
	}

	return NULL;
}

TrueTypeHandle loadTtf(FontManager* _fm, const char* _filePath)
{
	FILE* file = fopen(_filePath, "rb");
	if (NULL != file)
	{
		uint32_t size = (uint32_t)fsize(file);
		uint8_t* mem = (uint8_t*)malloc(size+1);
		size_t ignore = fread(mem, 1, size, file);
		BX_UNUSED(ignore);
		fclose(file);
		mem[size-1] = '\0';
		TrueTypeHandle handle = _fm->createTtf(mem, size);
		free(mem);
		return handle;
	}

	TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
	return invalid;
}

int _main_(int _argc, char** _argv)
{
	Args args(_argc, _argv);

	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init(args.m_type, args.m_pciId);
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	// Imgui.
	imguiCreate();

	char* bigText = loadText( "text/sherlock_holmes_a_scandal_in_bohemia_arthur_conan_doyle.txt");

	// Init the text rendering system.
	FontManager* fontManager = new FontManager(512);
	TextBufferManager* textBufferManager = new TextBufferManager(fontManager);

	TrueTypeHandle font = loadTtf(fontManager, "font/special_elite.ttf");

	// Create a distance field font.
	FontHandle fontSdf = fontManager->createFontByPixelSize(font, 0, 48, FONT_TYPE_DISTANCE);

	// Create a scaled down version of the same font (without adding anything to the atlas).
	FontHandle fontScaled = fontManager->createScaledFontToPixelSize(fontSdf, 14);

	TextLineMetrics metrics(fontManager->getFontInfo(fontScaled) );
	uint32_t lineCount = metrics.getLineCount(bigText);

	float visibleLineCount = 20.0f;

	const char* textBegin = 0;
	const char* textEnd = 0;
	metrics.getSubText(bigText, 0, (uint32_t)visibleLineCount, textBegin, textEnd);

	TextBufferHandle scrollableBuffer = textBufferManager->createTextBuffer(FONT_TYPE_DISTANCE, BufferType::Transient);
	textBufferManager->setTextColor(scrollableBuffer, 0xFFFFFFFF);

	textBufferManager->appendText(scrollableBuffer, fontScaled, textBegin, textEnd);

	entry::MouseState mouseState;
	int32_t scrollArea = 0;
	const int32_t guiPanelWidth = 250;
	const int32_t guiPanelHeight = 200;
	float textScroll = 0.0f;
	float textRotation = 0.0f;
	float textScale = 1.0f;
	float textSize = 14.0f;

	while (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
			, mouseState.m_mz
			, width
			, height
			);

		imguiBeginScrollArea("Text Area"
			, width - guiPanelWidth - 10
			, 10
			, guiPanelWidth
			, guiPanelHeight
			, &scrollArea
			);
		imguiSeparatorLine();

		bool recomputeVisibleText = false;
		recomputeVisibleText |= imguiSlider("Number of lines", visibleLineCount, 1.0f, 177.0f , 1.0f);
		if (imguiSlider("Font size", textSize, 6.0f, 64.0f , 1.0f) )
		{
			fontManager->destroyFont(fontScaled);
			fontScaled = fontManager->createScaledFontToPixelSize(fontSdf, (uint32_t) textSize);
			metrics = TextLineMetrics(fontManager->getFontInfo(fontScaled) );
			recomputeVisibleText = true;
		}

		recomputeVisibleText |= imguiSlider("Scroll", textScroll, 0.0f, (lineCount-visibleLineCount) , 1.0f);
		imguiSlider("Rotate", textRotation, 0.0f, bx::pi*2.0f , 0.1f);
		recomputeVisibleText |= imguiSlider("Scale", textScale, 0.1f, 10.0f , 0.1f);

		if (recomputeVisibleText)
		{
			textBufferManager->clearTextBuffer(scrollableBuffer);
			metrics.getSubText(bigText,(uint32_t)textScroll, (uint32_t)(textScroll+visibleLineCount), textBegin, textEnd);
			textBufferManager->appendText(scrollableBuffer, fontScaled, textBegin, textEnd);
		}

		imguiEndScrollArea();

		imguiEndFrame();

		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

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
			bx::mtxProj(proj, hmd->eye[0].fov, 0.1f, 100.0f);

			static float time = 0.0f;
			time += 0.05f;

			const float dist = 10.0f;
			const float offset0 = -proj[8] + (hmd->eye[0].viewOffset[0] / dist * proj[0]);
			const float offset1 = -proj[8] + (hmd->eye[1].viewOffset[0] / dist * proj[0]);

			float ortho[2][16];
			const float viewOffset = width/4.0f;
			const float viewWidth  = width/2.0f;
			bx::mtxOrtho(ortho[0], centering + viewOffset, centering + viewOffset + viewWidth, height + centering, centering, -1.0f, 1.0f, offset0);
			bx::mtxOrtho(ortho[1], centering + viewOffset, centering + viewOffset + viewWidth, height + centering, centering, -1.0f, 1.0f, offset1);
			bgfx::setViewTransform(0, view, ortho[0], BGFX_VIEW_STEREO, ortho[1]);
			bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
		}
		else
		{
			float ortho[16];
			bx::mtxOrtho(ortho, centering, width + centering, height + centering, centering, -1.0f, 1.0f);
			bgfx::setViewTransform(0, view, ortho);
			bgfx::setViewRect(0, 0, 0, width, height);
		}

		//very crude approximation :(
		float textAreaWidth = 0.5f * 66.0f * fontManager->getFontInfo(fontScaled).maxAdvanceWidth;

		float textRotMat[16];
		float textCenterMat[16];
		float textScaleMat[16];
		float screenCenterMat[16];

		bx::mtxRotateZ(textRotMat, textRotation);
		bx::mtxTranslate(textCenterMat, -(textAreaWidth * 0.5f), (-visibleLineCount)*metrics.getLineHeight()*0.5f, 0);
		bx::mtxScale(textScaleMat, textScale, textScale, 1.0f);
		bx::mtxTranslate(screenCenterMat, ( (width) * 0.5f), ( (height) * 0.5f), 0);

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
		textBufferManager->submitTextBuffer(scrollableBuffer, 0);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	imguiDestroy();

	free(bigText);

	fontManager->destroyTtf(font);
	// Destroy the fonts.
	fontManager->destroyFont(fontSdf);
	fontManager->destroyFont(fontScaled);

	textBufferManager->destroyTextBuffer(scrollableBuffer);

	delete textBufferManager;
	delete fontManager;

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
