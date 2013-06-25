/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"

#include <bgfx.h>
#include <bx/timer.h>
#include <bx/countof.h>
#include <bx/string.h>
#include "entry.h"
#include "dbg.h"
#include "fpumath.h"
#include "processevents.h"

#include "font/font_manager.h"
#include "font/text_buffer_manager.h"

#include <stdio.h>
#include <wchar.h>

TrueTypeHandle loadTtf(FontManager* _fm, const char* _fontPath)
{
	FILE* pFile;
	pFile = fopen(_fontPath, "rb");
	if (NULL != pFile)
	{
		if (0 == fseek(pFile, 0L, SEEK_END) )
		{
			// Get the size of the file.
			long bufsize = ftell(pFile);
			if (bufsize == -1)
			{
				fclose(pFile);
				TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			uint8_t* buffer = new uint8_t[bufsize];

			// Go back to the start of the file.
			fseek(pFile, 0L, SEEK_SET);

			// Read the entire file into memory.
			uint32_t newLen = fread( (void*)buffer, sizeof(char), bufsize, pFile);
			if (newLen == 0)
			{
				fclose(pFile);
				delete [] buffer;
				TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
				return invalid;
			}

			fclose(pFile);

			return _fm->createTtf(buffer, bufsize);
		}
	}

	TrueTypeHandle invalid = BGFX_INVALID_HANDLE;
	return invalid;
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

	// Load some TTF files.
	const char* fontNames[7] =
	{
		"font/droidsans.ttf",
		"font/chp-fire.ttf",
		"font/bleeding_cowboys.ttf",
		"font/mias_scribblings.ttf",
		"font/ruritania.ttf",
		"font/signika-regular.ttf",
		"font/five_minutes.otf"
	};

	const uint32_t fontCount = countof(fontNames);

	TrueTypeHandle fontFiles[fontCount];
	FontHandle fonts[fontCount];
	for (uint32_t ii = 0; ii < fontCount; ++ii)
	{
		// Instantiate a usable font.
		fontFiles[ii] = loadTtf(fontManager, fontNames[ii]);
		fonts[ii] = fontManager->createFontByPixelSize(fontFiles[ii], 0, 32);

		// Preload glyphs and blit them to atlas.
		fontManager->preloadGlyph(fonts[ii], L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. \n");

		// You can unload the truetype files at this stage, but in that 
		// case, the set of glyph's will be limited to the set of preloaded 
		// glyph.
		fontManager->destroyTtf(fontFiles[ii]);
	}

	TrueTypeHandle console_tt = loadTtf(fontManager, "font/visitor1.ttf");

	// This font doesn't have any preloaded glyph's but the truetype file 
	// is loaded so glyph will be generated as needed.
	FontHandle consola_16 = fontManager->createFontByPixelSize(console_tt, 0, 10);

	//create a static text buffer compatible with alpha font
	//a static text buffer content cannot be modified after its first submit.
	TextBufferHandle staticText = textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, BufferType::Static);

	// The pen position represent the top left of the box of the first line 
	// of text.
	textBufferManager->setPenPosition(staticText, 24.0f, 100.0f);

	for (uint32_t ii = 0; ii < fontCount; ++ii)
	{
		// Add some text to the buffer.
		// The position of the pen is adjusted when there is an endline.
		textBufferManager->appendText(staticText, fonts[ii], L"The quick brown fox jumps over the lazy dog\n");
	}

	// Now write some styled text.

	// Setup style colors.
	textBufferManager->setBackgroundColor(staticText, 0x551111FF);
	textBufferManager->setUnderlineColor(staticText, 0xFF2222FF);
	textBufferManager->setOverlineColor(staticText, 0x2222FFFF);
	textBufferManager->setStrikeThroughColor(staticText, 0x22FF22FF);

	// Background.
	textBufferManager->setStyle(staticText, STYLE_BACKGROUND);
	textBufferManager->appendText(staticText, fonts[0], L"The quick ");

	// Strike-through.
	textBufferManager->setStyle(staticText, STYLE_STRIKE_THROUGH);
	textBufferManager->appendText(staticText, fonts[0], L"brown fox ");

	// Overline.
	textBufferManager->setStyle(staticText, STYLE_OVERLINE);
	textBufferManager->appendText(staticText, fonts[0], L"jumps over ");

	// Underline.
	textBufferManager->setStyle(staticText, STYLE_UNDERLINE);
	textBufferManager->appendText(staticText, fonts[0], L"the lazy ");

	// Background + strike-through.
	textBufferManager->setStyle(staticText, STYLE_BACKGROUND | STYLE_STRIKE_THROUGH);
	textBufferManager->appendText(staticText, fonts[0], L"dog\n");

	// Create a transient buffer for real-time data.
	TextBufferHandle transientText = textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, BufferType::Transient);

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

		// Use transient text to display debug information.
		wchar_t fpsText[64];
		bx::swnprintf(fpsText, countof(fpsText), L"Frame: % 7.3f[ms]", double(frameTime) * toMs);

		textBufferManager->clearTextBuffer(transientText);
		textBufferManager->setPenPosition(transientText, 20.0, 4.0f);
		textBufferManager->appendText(transientText, consola_16, L"bgfx/examples/10-font\n");
		textBufferManager->appendText(transientText, consola_16, L"Description: Use the font system to display text and styled text.\n");
		textBufferManager->appendText(transientText, consola_16, fpsText);

		float at[3] = { 0, 0, 0.0f };
		float eye[3] = {0, 0, -1.0f };

		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);

		// Setup a top-left ortho matrix for screen space drawing.
		float centering = 0.5f;
		mtxOrtho(proj, centering, width + centering, height + centering, centering, -1.0f, 1.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		// Submit the debug text.
		textBufferManager->submitTextBuffer(transientText, 0);

		// Submit the static text.
		textBufferManager->submitTextBuffer(staticText, 0);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	fontManager->destroyTtf(console_tt);

	// Destroy the fonts.
	fontManager->destroyFont(consola_16);
	for (uint32_t ii = 0; ii < fontCount; ++ii)
	{
		fontManager->destroyFont(fonts[ii]);
	}

	textBufferManager->destroyTextBuffer(staticText);
	textBufferManager->destroyTextBuffer(transientText);

	delete textBufferManager;
	delete fontManager;

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
