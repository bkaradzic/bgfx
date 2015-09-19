/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"

#include <bgfx/bgfx.h>
#include <bx/timer.h>
#include <bx/string.h>
#include <bx/fpumath.h>

#include "font/font_manager.h"
#include "font/text_buffer_manager.h"
#include "entry/input.h"

#include <stdio.h>
#include <wchar.h>

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
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
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	// Init the text rendering system.
	FontManager* fontManager = new FontManager(512);
	TextBufferManager* textBufferManager = new TextBufferManager(fontManager);

	// Load some TTF files.
	const char* fontFilePath[7] =
	{
		"font/droidsans.ttf",
		"font/chp-fire.ttf",
		"font/bleeding_cowboys.ttf",
		"font/mias_scribblings.ttf",
		"font/ruritania.ttf",
		"font/signika-regular.ttf",
		"font/five_minutes.otf",
	};

	const uint32_t numFonts = BX_COUNTOF(fontFilePath);

	TrueTypeHandle fontFiles[numFonts];
	FontHandle fonts[numFonts];
	for (uint32_t ii = 0; ii < numFonts; ++ii)
	{
		// Instantiate a usable font.
		fontFiles[ii] = loadTtf(fontManager, fontFilePath[ii]);
		fonts[ii] = fontManager->createFontByPixelSize(fontFiles[ii], 0, 32);

		// Preload glyphs and blit them to atlas.
		fontManager->preloadGlyph(fonts[ii], L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. \n");

		// You can unload the truetype files at this stage, but in that
		// case, the set of glyph's will be limited to the set of preloaded
		// glyph.
		fontManager->destroyTtf(fontFiles[ii]);
	}

	TrueTypeHandle fontAwesomeTtf = loadTtf(fontManager, "font/fontawesome-webfont.ttf");

	// This font doesn't have any preloaded glyph's but the truetype file
	// is loaded so glyph will be generated as needed.
	FontHandle fontAwesome72 = fontManager->createFontByPixelSize(fontAwesomeTtf, 0, 72);

	TrueTypeHandle visitorTtf = loadTtf(fontManager, "font/visitor1.ttf");

	// This font doesn't have any preloaded glyph's but the truetype file
	// is loaded so glyph will be generated as needed.
	FontHandle visitor10 = fontManager->createFontByPixelSize(visitorTtf, 0, 10);

	//create a static text buffer compatible with alpha font
	//a static text buffer content cannot be modified after its first submit.
	TextBufferHandle staticText = textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, BufferType::Static);

	// The pen position represent the top left of the box of the first line
	// of text.
	textBufferManager->setPenPosition(staticText, 24.0f, 100.0f);

	for (uint32_t ii = 0; ii < numFonts; ++ii)
	{
		// Add some text to the buffer.
		// The position of the pen is adjusted when there is an endline.
		textBufferManager->appendText(staticText, fonts[ii], L"The quick brown fox jumps over the lazy dog\n");
	}

	// Now write some styled text.

	// Setup style colors.
	textBufferManager->setBackgroundColor(staticText, 0x551111ff);
	textBufferManager->setUnderlineColor(staticText, 0xff2222ff);
	textBufferManager->setOverlineColor(staticText, 0x2222ffff);
	textBufferManager->setStrikeThroughColor(staticText, 0x22ff22ff);

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

	textBufferManager->setStyle(staticText, STYLE_NORMAL);
	textBufferManager->appendText(staticText, fontAwesome72, L"\xf011 \xf02e \xf061 \xf087 \xf0d9 \xf099 \xf05c \xf021 \xf113\n");

	// Create a transient buffer for real-time data.
	TextBufferHandle transientText = textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, BufferType::Transient);

	while (!entry::processEvents(width, height, debug, reset) )
	{
		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0 / freq;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/10-font");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Use the font system to display text and styled text.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Use transient text to display debug information.
		wchar_t fpsText[64];
		bx::swnprintf(fpsText, BX_COUNTOF(fpsText), L"Frame: % 7.3f[ms]", double(frameTime) * toMs);

		textBufferManager->clearTextBuffer(transientText);
		textBufferManager->setPenPosition(transientText, width - 150.0f, 10.0f);
		textBufferManager->appendText(transientText, visitor10, L"Transient\n");
		textBufferManager->appendText(transientText, visitor10, L"text buffer\n");
		textBufferManager->appendText(transientText, visitor10, fpsText);

		float at[3]  = { 0, 0,  0.0f };
		float eye[3] = { 0, 0, -1.0f };

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
			const float offsetx = width/2.0f;
			bx::mtxOrtho(ortho[0], centering, offsetx + centering, height + centering, centering, -1.0f, 1.0f, offset0);
			bx::mtxOrtho(ortho[1], centering, offsetx + centering, height + centering, centering, -1.0f, 1.0f, offset1);
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

		// Submit the debug text.
		textBufferManager->submitTextBuffer(transientText, 0);

		// Submit the static text.
		textBufferManager->submitTextBuffer(staticText, 0);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	fontManager->destroyTtf(fontAwesomeTtf);
	fontManager->destroyTtf(visitorTtf);

	// Destroy the fonts.
	fontManager->destroyFont(fontAwesome72);
	fontManager->destroyFont(visitor10);
	for (uint32_t ii = 0; ii < numFonts; ++ii)
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
