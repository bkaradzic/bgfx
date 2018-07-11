/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx/c99/bgfx.h>
#include <stdio.h>
#include <string.h>

#define BGFX_UTILS_C99_IMPLEMENTATION
#include "../../common/c99/bgfx_utils.h"

#define RAYMATH_IMPLEMENTATION
#define RAYMATH_STANDALONE
#include "../../common/c99/raymath.h"

typedef struct {
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
} PosColorVertex;

static PosColorVertex s_cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

static const uint16_t s_cubeTriStrip[] =
{
	0, 1, 2,
	3,
	7,
	1,
	5,
	0,
	4,
	2,
	6,
	7,
	4,
	5,
};

static const uint16_t s_cubeLineList[] =
{
	0, 1,
	0, 2,
	0, 4,
	1, 3,
	1, 5,
	2, 3,
	2, 6,
	3, 7,
	4, 5,
	4, 6,
	5, 7,
	6, 7,
};

static const uint16_t s_cubePointList[] =
{
	0, 1, 2, 3, 4, 5, 6, 7
};

static const char* s_ptName[]=
{
	"Triangle List",
	"Triangle Strip",
	"Lines",
	"Points",
};

static const uint64_t s_ptState[]=
{
	UINT64_C(0),
	BGFX_STATE_PT_TRISTRIP,
	BGFX_STATE_PT_LINES,
	BGFX_STATE_PT_POINTS,
};

static const uint16_t s_ptSize[]=
{
	sizeof(s_cubeTriList)/sizeof(s_cubeTriList[0]),
	sizeof(s_cubeTriStrip)/sizeof(s_cubeTriStrip[0]),
	sizeof(s_cubeLineList)/sizeof(s_cubeLineList[0]),
	sizeof(s_cubePointList)/sizeof(s_cubePointList[0]),
};

static bgfx_program_handle_t m_program;
static int32_t m_pt=0;
static uint8_t r_on=1, g_on=1, b_on=1, a_on=1;

static bgfx_vertex_buffer_handle_t m_vbh;
static bgfx_index_buffer_handle_t m_ibh[4];

static uint32_t cycle_timer=0, cycle_interval=100;
static float rotation_speed=0.015f;

static inline int randomize(const int value, const int range) {
	int n=value;
	while(n==value) {
		n=rand()%range;
	}
	return n;
}

static inline void cycle_settings(const int drawtype, const int colors) {
	if(cycle_timer) {
		cycle_timer--;
		if(!cycle_timer) {
			if(drawtype) {
				m_pt++; m_pt*=m_pt<4;
			}
			if(colors) {
				a_on=1;
				uint8_t rgba=(r_on<<3)|(g_on<<2)|(b_on<<1)|a_on;
				rgba=randomize(rgba,15);
				if(!(rgba&14)) rgba|=1<<((rand()%3)+1);
				r_on=rgba&8; g_on=rgba&4; b_on=rgba&2; a_on=rgba&1;
				a_on=1;
			}
			cycle_timer=cycle_interval;
		}
	}
}

static inline void cubes_init(void) {
	// Create static vertex buffer.
	bgfx_vertex_decl_t dec;
	bgfx_vertex_decl_begin(&dec,bgfx_get_renderer_type());
	bgfx_vertex_decl_add(&dec,BGFX_ATTRIB_POSITION,3,BGFX_ATTRIB_TYPE_FLOAT,0,0);
	bgfx_vertex_decl_add(&dec,BGFX_ATTRIB_COLOR0,4,BGFX_ATTRIB_TYPE_UINT8,1,0);
	bgfx_vertex_decl_end(&dec);
	m_vbh = bgfx_create_vertex_buffer(
		// Static data can be passed with bgfx_make_ref
		bgfx_make_ref(s_cubeVertices, sizeof(s_cubeVertices) ),
		&dec, BGFX_BUFFER_NONE
		);

	// Create static index buffer for triangle list rendering.
	m_ibh[0] = bgfx_create_index_buffer(
		// Static data can be passed with bgfx_make_ref
		bgfx_make_ref(s_cubeTriList, sizeof(s_cubeTriList) ),
		BGFX_BUFFER_NONE
		);

	// Create static index buffer for triangle strip rendering.
	m_ibh[1] = bgfx_create_index_buffer(
		// Static data can be passed with bgfx_make_ref
		bgfx_make_ref(s_cubeTriStrip, sizeof(s_cubeTriStrip) ),
		BGFX_BUFFER_NONE
		);

	// Create static index buffer for line rendering.
	m_ibh[2] = bgfx_create_index_buffer(
		// Static data can be passed with bgfx_make_ref
		bgfx_make_ref(s_cubeLineList, sizeof(s_cubeLineList) ),
		BGFX_BUFFER_NONE
		);

	// Create static index buffer for point rendering.
	m_ibh[3] = bgfx_create_index_buffer(
		// Static data can be passed with bgfx_make_ref
		bgfx_make_ref(s_cubePointList, sizeof(s_cubePointList) ),
		BGFX_BUFFER_NONE
		);
}

static inline void cubes_draw(void) {
	int xx=0, yy=0;
	static float rotation=0;
	rotation+=rotation_speed;
	for(yy=0;yy<11;yy++) {
		for(xx=0;xx<11;xx++) {
			float mtx[16];
			Matrix ok=MatrixMultiply(MatrixRotateX(rotation + xx*0.21f),MatrixRotateY(rotation + yy*0.37f));
			memcpy(mtx,MatrixToFloatV(ok).v,16*sizeof(float));
			mtx[12] = -15.0f + ((float)xx)*3.0f;
			mtx[13] = -15.0f + ((float)yy)*3.0f;
			mtx[14] = 0.0f;

			// Set model matrix for rendering.
			bgfx_set_transform(mtx, 1);

			// Set vertex and index buffer.
			bgfx_set_vertex_buffer(0, m_vbh, 0, 8);
			bgfx_set_index_buffer(m_ibh[m_pt], 0, s_ptSize[m_pt]);

			// Set render states.
					uint64_t state = 0
						| (r_on ? BGFX_STATE_WRITE_R : 0)
						| (g_on ? BGFX_STATE_WRITE_G : 0)
						| (b_on ? BGFX_STATE_WRITE_B : 0)
						| (a_on ? BGFX_STATE_WRITE_A : 0)
						| BGFX_STATE_WRITE_Z
						| BGFX_STATE_DEPTH_TEST_LESS
						| BGFX_STATE_CULL_CCW
						| BGFX_STATE_MSAA
						| s_ptState[m_pt]
						;
			bgfx_set_state(state, 0);

			// Submit primitive for rendering to view 0.
			bgfx_submit(0, m_program, 0, 0);
		}
	}
}

extern bool entry_process_events(uint32_t* _width, uint32_t* _height, uint32_t* _debug, uint32_t* _reset);

static inline void showargs(void) {
	puts("Arguments:");
	puts("  -h        print arguments");
	puts("  -x1       use no MSAA");
	puts("  -x2       use MSAA X2 (default)");
	puts("  -x4       use MSAA X4");
	puts("  -x8       use MSAA X8");
	puts("  -x16      use MSAA X16");
	puts("  -r        disable red channel");
	puts("  -g        disable green channel");
	puts("  -b        disable blue channel");
	puts("  -a        disable alpha channel");
	puts("  -list     draw as triangle list");
	puts("  -strip    draw as triangle strip");
	puts("  -lines    draw as lines");
	puts("  -points   draw as points");
	puts("  -cc       cycle colors");
	puts("  -dc       cycle draw mode");
	puts("  -c X      set cycle interval = X (default=100)");
	puts("  -speed X  set rotation speed = X (default=0.015)");
	exit(EXIT_SUCCESS);
}

int32_t _main_(int32_t _argc, char** _argv)
{
	uint8_t cc_on=0, dc_on=0, msaa=1;
	if(_argc>1) { // parse arguments
		#define CARG(CARGNAME) !strcmp(_argv[opti],CARGNAME)
		#define CARGNEXT opti+1<_argc
		int opti;
		for(opti=1;opti<_argc;opti++) {
			if(CARGNEXT) {
				if(CARG("-c")) { // cycle interval
					int i=0;
					if(!sscanf(_argv[opti+1],"%d",&i)) {
						printf("Invalid arguments, please use decimal values != 0:\n'%s %s'\n",_argv[opti],_argv[opti+1]);
						exit(EXIT_FAILURE);
					}
					cycle_interval=i;
					opti++;
					continue;
				} else if(CARG("-speed")) { // clock speed
					if(!sscanf(_argv[opti+1],"%f",&rotation_speed)) {
						printf("Invalid arguments, please use floats:\n'%s %s'\n",_argv[opti],_argv[opti+1]);
						exit(EXIT_FAILURE);
					}
					opti++;
					continue;
				}
			}
			if(CARG("-h")) { // print arguments
				showargs();
			} else if(CARG("-x1")) { // MSAA off
				msaa=0;
			} else if(CARG("-x2")) { // MSAA X2
				msaa=1;
			} else if(CARG("-x4")) { // MSAA X4
				msaa=2;
			} else if(CARG("-x8")) { // MSAA X8
				msaa=3;
			} else if(CARG("-x16")) { // MSAA X16
				msaa=4;
			} else if(CARG("-r")) { // disable red channel
				r_on=0;
			} else if(CARG("-g")) { // disable green channel
				g_on=0;
			} else if(CARG("-b")) { // disable blue channel
				b_on=0;
			} else if(CARG("-a")) { // disable alpha channel
				a_on=0;
			} else if(CARG("-cc")) { // enable color cycle
				cc_on=1;
				cycle_timer=cycle_interval;
			} else if(CARG("-dc")) { // enable draw mode cycle
				dc_on=1;
				cycle_timer=cycle_interval;
			} else if(CARG("-list")) { // draw mode: triangle list
				m_pt=0;
			} else if(CARG("-strip")) { // draw mode: triangle strip
				m_pt=1;
			} else if(CARG("-lines")) { // draw mode: lines
				m_pt=2;
			} else if(CARG("-points")) { // draw mode: points
				m_pt=3;
			} else {
				printf("Unknown argument '%s'\n",_argv[opti]);
				showargs();
			}
		}
	}
	uint32_t msaa_list[]={0,BGFX_RESET_MSAA_X2,BGFX_RESET_MSAA_X4,BGFX_RESET_MSAA_X8,BGFX_RESET_MSAA_X16};
	uint32_t width  = 1280;
	uint32_t height = 720;
	uint32_t debug  = BGFX_DEBUG_TEXT;
	uint32_t reset  = 0
			| BGFX_RESET_VSYNC
			| msaa_list[msaa]
			;

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
	
	cubes_init();

	// Create program from shaders.
	m_program = loadProgram("vs_cubes", "fs_cubes");

	while (!entry_process_events(&width, &height, &debug, &reset) ) // update()
	{
		// Set view 0 default viewport.
		bgfx_set_view_rect(0, 0, 0, (uint16_t)width, (uint16_t)height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx_touch(0);

		Vector3 eye={ 0.0f, 0.0f, -35.0f }, at={ 0.0f, 0.0f, 0.0f }, up={ 0, 1, 0 };

		// Set view and projection matrix for view 0.
		const bgfx_hmd_t* hmd = bgfx_get_hmd();
		if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
		{
			// TODO: Support HMD in C. Possibly add it to raymath.h and pull-request it into raylib?
			/*float view[16];
			mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);
			bgfx_set_view_transform_stereo(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);

			// Set view 0 default viewport.
			//
			// Use HMD's width/height since HMD's internal frame buffer size
			// might be much larger than window size.
			bgfx_set_view_rect(0, 0, 0, hmd->width, hmd->height);*/
		}
		else
		{
			Matrix viewmtx=MatrixLookAt(eye,at,up);

			Matrix projmtx=MatrixPerspective(60.0f*DEG2RAD,((float)width)/((float)height),0.1f,100.0f);
			bgfx_set_view_transform(0, MatrixToFloatV(viewmtx).v, MatrixToFloatV(projmtx).v);

			// Set view 0 default viewport.
			bgfx_set_view_rect(0, 0, 0, (uint16_t)width, (uint16_t)height);
		}

		cubes_draw();

		// Use debug font to print information about this example.
		bgfx_dbg_text_clear(0, false);

		// Color macros for easier tweaking
		#define HEADER_MAIN 0x1F
		#define HEADER_DESC 0x3F
		#define TEXT_SELECT 0x60
		#define TEXT_NORMAL 0x07
		#define HIGHLIGHT_IF_TRUE(ARG0) (ARG0)?TEXT_SELECT:TEXT_NORMAL
		#define ONOFF(ARG0) (ARG0)?"On":"Off"

		// Print header and settings
		bgfx_dbg_text_printf(2, 1, HEADER_MAIN, "bgfx/examples/c99/01-cubes");
		bgfx_dbg_text_printf(2, 2, HEADER_DESC, "Description: Rendering a simple static mesh with the C99 API.");
		bgfx_dbg_text_printf(2, 4, TEXT_NORMAL, "Settings");
		bgfx_dbg_text_printf(6, 5, TEXT_NORMAL, "Write R:  %s",ONOFF(r_on));
		bgfx_dbg_text_printf(6, 6, TEXT_NORMAL, "Write G:  %s",ONOFF(g_on));
		bgfx_dbg_text_printf(6, 7, TEXT_NORMAL, "Write B:  %s",ONOFF(b_on));
		bgfx_dbg_text_printf(6, 8, TEXT_NORMAL, "Write A:  %s",ONOFF(a_on));
		bgfx_dbg_text_printf(6, 9, TEXT_NORMAL, "   MSAA:  %d",(!msaa)?0:(int)pow(2,msaa));
		bgfx_dbg_text_printf(6, 10, TEXT_NORMAL, "  Speed:  %.03f",rotation_speed);
		bgfx_dbg_text_printf(2, 12, TEXT_NORMAL, "Cycle (%s)",ONOFF(cycle_timer));
		bgfx_dbg_text_printf(6, 13, TEXT_NORMAL, "  Color:  %s",ONOFF(cc_on));
		bgfx_dbg_text_printf(6, 14, TEXT_NORMAL, "   Mode:  %s",ONOFF(dc_on));
		bgfx_dbg_text_printf(6-1, 15, TEXT_NORMAL, "Interval:  %d",cycle_interval);
		bgfx_dbg_text_printf(2, 17, TEXT_NORMAL, "Primitive Topology");
		bgfx_dbg_text_printf(6, 18, HIGHLIGHT_IF_TRUE(m_pt==0), s_ptName[0]);
		bgfx_dbg_text_printf(6, 19, HIGHLIGHT_IF_TRUE(m_pt==1), s_ptName[1]);
		bgfx_dbg_text_printf(6, 20, HIGHLIGHT_IF_TRUE(m_pt==2), s_ptName[2]);
		bgfx_dbg_text_printf(6, 21, HIGHLIGHT_IF_TRUE(m_pt==3), s_ptName[3]);
		bgfx_dbg_text_printf(2, 23, TEXT_NORMAL, "Run with argument -h for");
		bgfx_dbg_text_printf(2, 24, TEXT_NORMAL, "help adjusting settings.");

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx_frame(false);
		cycle_settings(dc_on,cc_on);
	}

	// Shutdown bgfx.
	bgfx_shutdown();

	return 0;
}
