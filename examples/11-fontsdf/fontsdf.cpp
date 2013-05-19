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
#include "../common/font/text_buffer_manager.h"

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

	// Init the text rendering system.
	FontManager* fontManager = new FontManager(512);
	TextBufferManager* textBufferManager = new TextBufferManager(fontManager);

	TrueTypeHandle times_tt = fontManager->loadTrueTypeFromFile("font/bleeding_cowboys.ttf");

	// Create a distance field font.
	FontHandle distance_font = fontManager->createFontByPixelSize(times_tt, 0, 48, FONT_TYPE_DISTANCE);

	// Create a scalled down version of the same font (without adding 
	// anything to the atlas).
	FontHandle smaller_font = fontManager->createScaledFontToPixelSize(distance_font, 32);

	// Preload glyph and generate (generate bitmap's).
	fontManager->preloadGlyph(distance_font, L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,\" \n");

	// You can unload the TTF files at this stage, but in that case, the 
	// set of glyph's will be limited to the set of preloaded glyph.
	fontManager->unloadTrueType(times_tt);

	TextBufferHandle staticText = textBufferManager->createTextBuffer(FONT_TYPE_DISTANCE, STATIC);
	textBufferManager->setTextColor(staticText, 0xDD0000FF);

	textBufferManager->appendText(staticText, distance_font, L"BGFX ");
	textBufferManager->appendText(staticText, smaller_font, L"bgfx");

	int64_t timeOffset = bx::getHPCounter();
	while (!processEvents(width, height, debug, reset) )
	{
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
		float time = (float)( (now - timeOffset) / double(bx::getHPFrequency() ) );

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
		TextRectangle rect = textBufferManager->getRectangle(staticText);

		float mtxA[16];
		float mtxB[16];
		float mtxC[16];
		mtxRotateZ(mtxA, time * 0.37f);
		mtxTranslate(mtxB, -(rect.width * 0.5f), -(rect.height * 0.5f), 0);

		mtxMul(mtxC, mtxB, mtxA);

		float scale = 4.1f + 4.0f * sinf(time);
		mtxScale(mtxA, scale, scale, 1.0f);
		mtxMul(mtxB, mtxC, mtxA);

		mtxTranslate(mtxC, ( (width) * 0.5f), ( (height) * 0.5f), 0);
		mtxMul(mtxA, mtxB, mtxC);

		// Set model matrix for rendering.
		bgfx::setTransform(mtxA);

		// Draw your text.
		textBufferManager->submitTextBuffer(staticText, 0);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Destroy the fonts.
	fontManager->destroyFont(distance_font);
	fontManager->destroyFont(smaller_font);

	textBufferManager->destroyTextBuffer(staticText);

	delete textBufferManager;
	delete fontManager;

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
