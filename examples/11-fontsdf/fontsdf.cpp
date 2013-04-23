#include <bgfx.h>
#include <bx/bx.h>
#include <bx/timer.h>
#include "../common/entry.h"
#include "../common/dbg.h"
#include "../common/math.h"
#include "../common/processevents.h"

#include "../common/font/font_manager.h"
#include "../common/font/text_buffer_manager.h"

#include <stdio.h>
#include <string.h>

static const char* s_shaderPath = NULL;

int _main_(int /*_argc*/, char** /*_argv*/)
{
    uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = 0;

	bgfx::init();

	bgfx::reset(width, height);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT
		//, 0x303030ff
		//, 0xffffffff
		, 0x000000FF
		, 1.0f
		, 0
		);

    // Setup root path for binary shaders. Shader binaries are different 
	// for each renderer.
	switch (bgfx::getRendererType() )
	{
	default:
	case bgfx::RendererType::Direct3D9:
		s_shaderPath = "shaders/dx9/";
		break;

	case bgfx::RendererType::Direct3D11:
		s_shaderPath = "shaders/dx11/";
		break;

	case bgfx::RendererType::OpenGL:
		s_shaderPath = "shaders/glsl/";
		break;

	case bgfx::RendererType::OpenGLES2:
	case bgfx::RendererType::OpenGLES3:
		s_shaderPath = "shaders/gles/";
		break;
	}

	//init the text rendering system
	FontManager* fontManager = new FontManager(512);
	TextBufferManager* textBufferManager = new TextBufferManager(fontManager);
	textBufferManager->init(s_shaderPath);

	//load a truetype files
	TrueTypeHandle times_tt = fontManager->loadTrueTypeFromFile("c:/windows/fonts/times.ttf");	
	FontHandle distance_font = fontManager->createFontByPixelSize(times_tt, 0, 48, FONT_TYPE_DISTANCE);
	//preload glyph and generate (generate bitmap's)
	fontManager->preloadGlyph(distance_font, L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. \n");

	uint32_t fontsCount = 0;
	FontHandle fonts[64];
	fonts[fontsCount++] = distance_font;
	//generate various sub distance field fonts at various size
	int step=4;
	for(int i = 64; i>1 ; i-=step)
	{		
		if(i<32) step = 2;
		//instantiate a usable font
		FontHandle font = fontManager->createScaledFontToPixelSize(distance_font, i);
		fonts[fontsCount++] = font;
	}
	//You can unload the truetype files at this stage, but in that case, the set of glyph's will be limited to the set of preloaded glyph
	fontManager->unloadTrueType(times_tt);
			
	TextBufferHandle staticText = textBufferManager->createTextBuffer(FONT_TYPE_DISTANCE, STATIC);
	
	textBufferManager->setPenPosition(staticText, 10.0f, 70.0f);		
	textBufferManager->setTextColor(staticText, 0xFFFFFFFF);
	//textBufferManager->setTextColor(staticText, 0x000000FF);
	for(size_t i = 0; i< fontsCount; ++i)
	{				
		textBufferManager->appendText(staticText, fonts[i], L"The quick brown fox jumps over the lazy dog\n");		
		//textBufferManager->appendText(staticText, fonts[i], L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
	}	
		
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
		const double toMs = 1000.0/freq;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/11-fontsdf");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Use a single distance field font to render text of various size.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		float at[3] = { 0, 0, 0.0f };
		float eye[3] = {0, 0, -1.0f };
		
		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);		
		float centering = 0.5f;
		//setup a top-left ortho matrix for screen space drawing
		mtxOrtho(proj, centering, width+centering,height+centering, centering,-1.0f, 1.0f);		
		
		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);				
		
		//draw your text
		textBufferManager->submitTextBuffer(staticText, 0);	

        // Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
		//just to prevent my CG Fan to howl
		Sleep(2);
	}

	//destroy the fonts
	for(size_t i=0; i<fontsCount;++i)
	{
		fontManager->destroyFont(fonts[i]);
	}
	
	textBufferManager->destroyTextBuffer(staticText);
	delete textBufferManager;
	delete fontManager;	
	// Shutdown bgfx.
    bgfx::shutdown();

	return 0;
}
