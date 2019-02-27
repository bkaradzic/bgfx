/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx/c99/bgfx.h>
#include "../00-helloworld/logo.h"

extern bool entry_process_events(uint32_t* _width, uint32_t* _height, uint32_t* _debug, uint32_t* _reset);

uint16_t uint16_max(uint16_t _a, uint16_t _b)
{
	return _a < _b ? _b : _a;
}

int32_t _main_(int32_t _argc, char** _argv)
{
	uint32_t width  = 1280;
	uint32_t height = 720;
	uint32_t debug  = BGFX_DEBUG_TEXT;
	uint32_t reset  = BGFX_RESET_VSYNC;
	(void)_argc;
	(void)_argv;

	bgfx_init_t init;
	bgfx_init_ctor(&init);

	bgfx_init(&init);
	bgfx_reset(width, height, reset, init.resolution.format);

	// Enable debug text.
	bgfx_set_debug(debug);

	bgfx_set_view_clear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	while (!entry_process_events(&width, &height, &debug, &reset) )
	{
		// Set view 0 default viewport.
		bgfx_set_view_rect(0, 0, 0, (uint16_t)width, (uint16_t)height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx_encoder_t* encoder = bgfx_encoder_begin(true);
		bgfx_encoder_touch(encoder, 0);
		bgfx_encoder_end(encoder);

		// Use debug font to print information about this example.
		bgfx_dbg_text_clear(0, false);
		bgfx_dbg_text_image(
			  uint16_max( (uint16_t)width /2/8, 20)-20
			, uint16_max( (uint16_t)height/2/16, 6)-6
			, 40
			, 12
			, s_logo
			, 160
			);

		bgfx_dbg_text_printf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

		bgfx_dbg_text_printf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
		bgfx_dbg_text_printf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

		bgfx_dbg_text_printf(0, 3, 0x1f, "bgfx/examples/25-c99");
		bgfx_dbg_text_printf(0, 4, 0x3f, "Description: Initialization and debug text with C99 API.");

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx_frame(false);
	}

	// Shutdown bgfx.
	bgfx_shutdown();

	return 0;
}
