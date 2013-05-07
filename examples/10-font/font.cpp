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
long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

static const bgfx::Memory* loadShader(const char* _shaderPath, const char* _shaderName)
{
	char out[512];
	strcpy(out, _shaderPath);
	strcat(out, _shaderName);
	strcat(out, ".bin");

	FILE* file = fopen(out, "rb");
	if (NULL != file)
	{
		uint32_t size = (uint32_t)fsize(file);
		const bgfx::Memory* mem = bgfx::alloc(size+1);
		/*size_t ignore =*/ fread(mem->data, 1, size, file);
		/*BX_UNUSED(ignore);*/
		fclose(file);
		mem->data[mem->size-1] = '\0';
		return mem;
	}

	return NULL;
}

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
		, 0x303030ff		
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
		
	//load some truetype files
	TrueTypeHandle times_tt = fontManager->loadTrueTypeFromFile("c:/windows/fonts/times.ttf");
	TrueTypeHandle consola_tt = fontManager->loadTrueTypeFromFile("c:/windows/fonts/consola.ttf");

	//create some usable font with of a specific size
	FontHandle times_24 = fontManager->createFontByPixelSize(times_tt, 0, 24);
		
	//preload glyphs and blit them to atlas
	fontManager->preloadGlyph(times_24, L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. \n");
		
	//You can unload the truetype files at this stage, but in that case, the set of glyph's will be limited to the set of preloaded glyph
	fontManager->unloadTrueType(times_tt);

	//this font doesn't have any preloaded glyph's but the truetype file is loaded
	//so glyph will be generated as needed
	FontHandle consola_16 = fontManager->createFontByPixelSize(consola_tt, 0, 16);
	
	//create a static text buffer compatible with alpha font
	//a static text buffer content cannot be modified after its first submit.
	TextBufferHandle staticText = textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, STATIC);
	
	//the pen position represent the top left of the box of the first line of text
	textBufferManager->setPenPosition(staticText, 20.0f, 100.0f);
	
	//add some text to the buffer
	textBufferManager->appendText(staticText, times_24, L"The quick brown fox jumps over the lazy dog\n");
	//the position of the pen is adjusted when there is an endline
	
	//setup style colors 
	textBufferManager->setBackgroundColor(staticText, 0x551111FF);
	textBufferManager->setUnderlineColor(staticText, 0xFF2222FF);
	textBufferManager->setOverlineColor(staticText, 0x2222FFFF);
	textBufferManager->setStrikeThroughColor(staticText, 0x22FF22FF);
	

	//text + bkg
	textBufferManager->setStyle(staticText, STYLE_BACKGROUND);
	textBufferManager->appendText(staticText, times_24, L"The quick brown fox jumps over the lazy dog\n");

	//text + strike-through
	textBufferManager->setStyle(staticText, STYLE_STRIKE_THROUGH);
	textBufferManager->appendText(staticText, times_24, L"The quick brown fox jumps over the lazy dog\n");

	//text + overline
	textBufferManager->setStyle(staticText, STYLE_OVERLINE);
	textBufferManager->appendText(staticText, times_24, L"The quick brown fox jumps over the lazy dog\n");
	
	//text + underline
	textBufferManager->setStyle(staticText, STYLE_UNDERLINE);
	textBufferManager->appendText(staticText, times_24, L"The quick brown fox jumps over the lazy dog\n");

	
	//text + bkg + strike-through
	textBufferManager->setStyle(staticText, STYLE_BACKGROUND|STYLE_STRIKE_THROUGH);
	textBufferManager->appendText(staticText, times_24, L"The quick brown fox jumps over the lazy dog\n");

	//create a transient buffer for realtime data	
	TextBufferHandle transientText = textBufferManager->createTextBuffer(FONT_TYPE_ALPHA, TRANSIENT);	
			
	
	uint32_t w = 0,h = 0;
    while (!processEvents(width, height, debug, reset) )
	{
		
		if(w!=width|| h!=height)
		{
			w=width;
			h= height;
			printf("ri: %d,%d\n",width,height);
		}
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
		//bgfx::dbgTextClear();
		//bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/10-font");
		//bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Use the font system to display text and styled text.");
		//bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);
		
		//Use transient text to display debug information
		//Code below is similar to commented code above
		wchar_t fpsText[64];
		swprintf(fpsText,L"Frame: % 7.3f[ms]", double(frameTime)*toMs);
		
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
		//setup a top-left ortho matrix for screen space drawing		
		float centering = 0.5f;
		mtxOrtho(proj, centering, width+centering,height+centering, centering,-1.0f, 1.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		//submit the debug text
		textBufferManager->submitTextBuffer(transientText, 0);

		//submit the static text
		textBufferManager->submitTextBuffer(staticText, 0);	
				
        // Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}
	
	
	fontManager->unloadTrueType(consola_tt);
	fontManager->destroyFont(consola_16);
	fontManager->destroyFont(times_24);

	textBufferManager->destroyTextBuffer(staticText);
	textBufferManager->destroyTextBuffer(transientText);	

	delete textBufferManager;
	delete fontManager;	
	
	// Shutdown bgfx.
    bgfx::shutdown();

	return 0;
}
