/*
 * 2018 bgfx
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <bgfx/c99/bgfx.h>
#include <bgfx/c99/platform.h>

static int sdl_set_window(SDL_Window* _window)
{
	SDL_SysWMinfo wmi;
	SDL_VERSION(&wmi.version);
	if (!SDL_GetWindowWMInfo(_window, &wmi) )
	{
		return false;
	}

	bgfx_platform_data_t pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	pd.ndt          = wmi.info.x11.display;
	pd.nwh          = (void*)(uintptr_t)wmi.info.x11.window;
#	elif BX_PLATFORM_OSX
	pd.ndt          = NULL;
	pd.nwh          = wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
	pd.ndt          = NULL;
	pd.nwh          = wmi.info.win.window;
#	elif BX_PLATFORM_STEAMLINK
	pd.ndt          = wmi.info.vivante.display;
	pd.nwh          = wmi.info.vivante.window;
#	endif // BX_PLATFORM_
	pd.context      = NULL;
	pd.backBuffer   = NULL;
	pd.backBufferDS = NULL;
	bgfx_set_platform_data(&pd);

	return true;
}

int32_t main(int32_t _argc, char** _argv)
{
	int width  = 640;
	int height = 100;

	int running=1;
	char letter=0;

	uint32_t debug  = BGFX_DEBUG_TEXT;
	uint32_t reset  = 0
			| BGFX_RESET_VSYNC
			;

	// Initialize SDL2's events and create window
	SDL_Init(0|SDL_INIT_GAMECONTROLLER);
	SDL_Window *window = SDL_CreateWindow("bgfx"
							, SDL_WINDOWPOS_UNDEFINED
							, SDL_WINDOWPOS_UNDEFINED
							, width
							, height
							, SDL_WINDOW_SHOWN
							| SDL_WINDOW_RESIZABLE
							);
	if(!sdl_set_window(window)) {
		printf("Error: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

	bgfx_init_t init;
	bgfx_init_ctor(&init);

	bgfx_init(&init);
	bgfx_reset(width, height, reset);

	// Enable debug text.
	bgfx_set_debug(debug);

	bgfx_set_view_clear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	while (running) {
		// Poll for events with SDL2
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_WINDOWEVENT:
					switch(event.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							SDL_GetWindowSize(window,&width,&height);
							bgfx_reset(width, height, reset);
							break;
					}
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym>=SDLK_a && event.key.keysym.sym<=SDLK_z)
						letter='A'+(event.key.keysym.sym-SDLK_a);
					break;
				case SDL_QUIT:
					running=0;
					break;
			}
		}

		// Set view 0 default viewport.
		bgfx_set_view_rect(0, 0, 0, (uint16_t)width, (uint16_t)height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx_touch(0);

		// Use debug font to print information about this example.
		bgfx_dbg_text_clear(0, false);
		bgfx_dbg_text_printf(2, 1, 0x1F, "bgfx/examples/38-c99-sdl2");
		bgfx_dbg_text_printf(2, 2, 0x3F, "Description: Using SDL2 for input and window creation with the C99 API.");
		bgfx_dbg_text_printf(2, 4, 0x07, "Last letter key pressed: %c", letter);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx_frame(false);
	}

	// Shut down bgfx.
	bgfx_shutdown();

	return 0;
}
