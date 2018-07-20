/*
 * Copyright 2013 Jeremie Roy. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"

#include <bx/timer.h>
#include <bx/string.h>
#include <bx/math.h>

#include "font/font_manager.h"
#include "font/text_buffer_manager.h"
#include "entry/input.h"

#include <iconfontheaders/icons_font_awesome.h>
#include <iconfontheaders/icons_kenney.h>

#include <wchar.h>

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

static const char* s_fontFilePath[] =
{
	"font/droidsans.ttf",
	"font/chp-fire.ttf",
	"font/bleeding_cowboys.ttf",
	"font/mias_scribblings.ttf",
	"font/ruritania.ttf",
	"font/signika-regular.ttf",
	"font/five_minutes.otf",
};

class ExampleFont : public entry::AppI
{
public:
	ExampleFont(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
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
						   , BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
						   , 0x303030ff
						   , 1.0f
						   , 0
						   );

		// Init the text rendering system.
		m_fontManager = new FontManager(512);
		m_textBufferManager = new TextBufferManager(m_fontManager);

		// Load some TTF files.
		for (uint32_t ii = 0; ii < numFonts; ++ii)
		{
			// Instantiate a usable font.
			m_fontFiles[ii] = loadTtf(m_fontManager, s_fontFilePath[ii]);
			m_fonts[ii] = m_fontManager->createFontByPixelSize(m_fontFiles[ii], 0, 32);

			// Preload glyphs and blit them to atlas.
			m_fontManager->preloadGlyph(m_fonts[ii], L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. \n");

			// You can unload the truetype files at this stage, but in that
			// case, the set of glyph's will be limited to the set of preloaded
			// glyph.
			m_fontManager->destroyTtf(m_fontFiles[ii]);
		}

		m_fontAwesomeTtf = loadTtf(m_fontManager, "font/fontawesome-webfont.ttf");
		m_fontKenneyTtf  = loadTtf(m_fontManager, "font/kenney-icon-font.ttf");

		// This font doesn't have any preloaded glyph's but the truetype file
		// is loaded so glyph will be generated as needed.
		m_fontAwesome72 = m_fontManager->createFontByPixelSize(m_fontAwesomeTtf, 0, 72);
		m_fontKenney64  = m_fontManager->createFontByPixelSize(m_fontKenneyTtf,  0, 64);

		m_visitorTtf = loadTtf(m_fontManager, "font/visitor1.ttf");

		// This font doesn't have any preloaded glyph's but the truetype file
		// is loaded so glyph will be generated as needed.
		m_visitor10 = m_fontManager->createFontByPixelSize(m_visitorTtf, 0, 10);

		//create a static text buffer compatible with alpha font
		//a static text buffer content cannot be modified after its first submit.
		m_staticText = m_textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, BufferType::Static);

		// The pen position represent the top left of the box of the first line
		// of text.
		m_textBufferManager->setPenPosition(m_staticText, 24.0f, 100.0f);

		for (uint32_t ii = 0; ii < numFonts; ++ii)
		{
			// Add some text to the buffer.
			// The position of the pen is adjusted when there is an endline.
			m_textBufferManager->appendText(m_staticText, m_fonts[ii], L"The quick brown fox jumps over the lazy dog\n");
		}

		// Now write some styled text.

		// Setup style colors.
		m_textBufferManager->setBackgroundColor(m_staticText, 0x551111ff);
		m_textBufferManager->setUnderlineColor(m_staticText, 0xff2222ff);
		m_textBufferManager->setOverlineColor(m_staticText, 0x2222ffff);
		m_textBufferManager->setStrikeThroughColor(m_staticText, 0x22ff22ff);

		// Background.
		m_textBufferManager->setStyle(m_staticText, STYLE_BACKGROUND);
		m_textBufferManager->appendText(m_staticText, m_fonts[0], L"The quick ");

		// Strike-through.
		m_textBufferManager->setStyle(m_staticText, STYLE_STRIKE_THROUGH);
		m_textBufferManager->appendText(m_staticText, m_fonts[0], L"brown fox ");

		// Overline.
		m_textBufferManager->setStyle(m_staticText, STYLE_OVERLINE);
		m_textBufferManager->appendText(m_staticText, m_fonts[0], L"jumps over ");

		// Underline.
		m_textBufferManager->setStyle(m_staticText, STYLE_UNDERLINE);
		m_textBufferManager->appendText(m_staticText, m_fonts[0], L"the lazy ");

		// Background + strike-through.
		m_textBufferManager->setStyle(m_staticText, STYLE_BACKGROUND | STYLE_STRIKE_THROUGH);
		m_textBufferManager->appendText(m_staticText, m_fonts[0], L"dog\n");

		m_textBufferManager->setStyle(m_staticText, STYLE_NORMAL);
		m_textBufferManager->appendText(m_staticText, m_fontAwesome72,
			" " ICON_FA_POWER_OFF
			" " ICON_FA_TWITTER_SQUARE
			" " ICON_FA_CERTIFICATE
			" " ICON_FA_FLOPPY_O
			" " ICON_FA_GITHUB
			" " ICON_FA_GITHUB_ALT
			"\n"
			);
		m_textBufferManager->appendText(m_staticText, m_fontKenney64,
			" " ICON_KI_COMPUTER
			" " ICON_KI_JOYSTICK
			" " ICON_KI_EXLAMATION
			" " ICON_KI_STAR
			" " ICON_KI_BUTTON_START
			" " ICON_KI_DOWNLOAD
			"\n"
			);

		// Create a transient buffer for real-time data.
		m_transientText = m_textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, BufferType::Transient);

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		m_fontManager->destroyTtf(m_fontKenneyTtf);
		m_fontManager->destroyTtf(m_fontAwesomeTtf);
		m_fontManager->destroyTtf(m_visitorTtf);

		// Destroy the fonts.
		m_fontManager->destroyFont(m_fontKenney64);
		m_fontManager->destroyFont(m_fontAwesome72);
		m_fontManager->destroyFont(m_visitor10);
		for (uint32_t ii = 0; ii < numFonts; ++ii)
		{
			m_fontManager->destroyFont(m_fonts[ii]);
		}

		m_textBufferManager->destroyTextBuffer(m_staticText);
		m_textBufferManager->destroyTextBuffer(m_transientText);

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

			imguiEndFrame();

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0 / freq;

			// Use transient text to display debug information.
			char fpsText[64];
			bx::snprintf(fpsText, BX_COUNTOF(fpsText), "Frame: % 7.3f[ms]", double(frameTime) * toMs);

			m_textBufferManager->clearTextBuffer(m_transientText);
			m_textBufferManager->setPenPosition(m_transientText, m_width - 150.0f, 10.0f);
			m_textBufferManager->appendText(m_transientText, m_visitor10, "Transient\n");
			m_textBufferManager->appendText(m_transientText, m_visitor10, "text buffer\n");
			m_textBufferManager->appendText(m_transientText, m_visitor10, fpsText);

			float at[3]  = { 0, 0,  0.0f };
			float eye[3] = { 0, 0, -1.0f };

			float view[16];
			bx::mtxLookAt(view, eye, at);

			const float centering = 0.5f;

			// Setup a top-left ortho matrix for screen space drawing.
			const bgfx::Caps* caps = bgfx::getCaps();
			{
				float ortho[16];
				bx::mtxOrtho(
					  ortho
					, centering
					, m_width  + centering
					, m_height + centering
					, centering
					, 0.0f
					, 100.0f
					, 0.0f
					, caps->homogeneousDepth
					);
				bgfx::setViewTransform(0, view, ortho);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			// Submit the debug text.
			m_textBufferManager->submitTextBuffer(m_transientText, 0);

			// Submit the static text.
			m_textBufferManager->submitTextBuffer(m_staticText, 0);

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

	FontManager* m_fontManager;
	TextBufferManager* m_textBufferManager;

	FontHandle m_visitor10;
	TrueTypeHandle m_fontAwesomeTtf;
	TrueTypeHandle m_fontKenneyTtf;
	FontHandle m_fontAwesome72;
	FontHandle m_fontKenney64;
	TrueTypeHandle m_visitorTtf;

	TextBufferHandle m_transientText;
	TextBufferHandle m_staticText;

	static const uint32_t numFonts = BX_COUNTOF(s_fontFilePath);

	TrueTypeHandle m_fontFiles[numFonts];
	FontHandle m_fonts[numFonts];
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleFont, "10-font", "Use the font system to display text and styled text.");
