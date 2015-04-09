/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include "bgfx_utils.h"

/*********************************************************************************************/

#define VSH_HEADER "VSH\3\0\0\0\0\0\0\0\0\0\0"
#define FSH_HEADER "FSH\3\0\0\0\0\0\0\0\0\0\0"

static const uint8_t vs_txt[] = VSH_HEADER
"layout(location = 0) in vec3 a_position;									  \n"
"layout(location = 1) in vec3 a_normal;										  \n"
"layout(location = 2) in ivec2 a_texcoord0;									  \n"
"																			  \n"
"out vec2 v_texture0;														  \n"
"																			  \n"
"uniform mat4  u_modelViewProj;												  \n"
"																			  \n"
"void main()																  \n"
"{																			  \n"
"	gl_Position = u_modelViewProj * vec4(a_position,1.0);					  \n"
"	v_texture0 = a_texcoord0;												  \n"
"}					 														  \n";


static const uint8_t fs_txt[] = FSH_HEADER
"in vec2 v_texture0;													      \n"
"out vec4 outputColor;														  \n"
"																			  \n"
"uniform sampler2D s0;														  \n"
"																			  \n"
"void main()																  \n"
"{																			  \n"
"	vec4 coltex = texture(s0,v_texture0);									  \n"
"	outputColor = coltex * 1.2;										          \n"
"}																			  \n";
	
/*********************************************************************************************/


struct VertexPNT
{
	float px,py,pz;
	float nx,ny,nz;
	//float u0,v0;
	int16_t u0,v0;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,3,bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,3,bgfx::AttribType::Float)
			//.add(bgfx::Attrib::TexCoord0,2,bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0,2,bgfx::AttribType::Int16,true,true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl VertexPNT::ms_decl;

static const VertexPNT s_cubeVertices[] =
{
	{ -1,1,-1,0,0,-1,0,0,},
	{ 1,1,-1,0,0,-1,1,0,},
	{ 1,-1,-1,0,0,-1,1,1,},
	{ -1,-1,-1,0,0,-1,0,1,},

	{ -1,-1,1,0,0,1,0,0,},
	{ 1,-1,1,0,0,1,1,0,},
	{ 1,1,1,0,0,1,1,1,},
	{ -1,1,1,0,0,1,0,1,},

	{ -1,-1,-1,0,-1,0,0,0,},
	{ 1,-1,-1,0,-1,0,1,0,},
	{ 1,-1,1,0,-1,0,1,1,},
	{ -1,-1,1,0,-1,0,0,1,},

	{ 1,-1,-1,1,0,0,0,0,},
	{ 1,1,-1,1,0,0,1,0,},
	{ 1,1,1,1,0,0,1,1,},
	{ 1,-1,1,1,0,0,0,1,},

	{ 1,1,-1,0,1,0,0,0,},
	{ -1,1,-1,0,1,0,1,0,},
	{ -1,1,1,0,1,0,1,1,},
	{ 1,1,1,0,1,0,0,1,},

	{ -1,1,-1,-1,0,0,0,0,},
	{ -1,-1,-1,-1,0,0,1,0,},
	{ -1,-1,1,-1,0,0,1,1,},
	{ -1,1,1,-1,0,0,0,1,},
};


static const uint16_t s_cubeIndices[] =
{
	0,1,2,
	0,2,3,
	4,5,6,
	4,6,7,
	8,9,10,
	8,10,11,
	12,13,14,
	12,14,15,
	16,17,18,
	16,18,19,
	20,21,22,
	20,22,23,
};

/*static PosColorVertex s_cubeVertices[8] =
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

static const uint16_t s_cubeIndices[36] =
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
};*/

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
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	// Create vertex stream declaration.
	VertexPNT::init();

	// Create static vertex buffer.
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
		  // Static data can be passed with bgfx::makeRef
		  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
		  ,VertexPNT::ms_decl
		);

	// Create static index buffer.
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) )
		);

	// Create program from shaders.
	//bgfx::ProgramHandle program = loadProgram("vs_cubes", "fs_cubes");

	// Create program from shaders text.
	const bgfx::Memory* memvs = bgfx::makeRef(vs_txt,sizeof(vs_txt));
	bgfx::ShaderHandle vsh = bgfx::createShader(memvs);
	const bgfx::Memory* memfs = bgfx::makeRef(fs_txt,sizeof(fs_txt));
	bgfx::ShaderHandle fsh = bgfx::createShader(memfs);
	bgfx::ProgramHandle program = bgfx::createProgram(vsh,fsh,true);

	// Load diffuse texture.
	bgfx::UniformHandle u_texColor = bgfx::createUniform("u_texColor",bgfx::UniformType::Uniform1iv);
	bgfx::TextureHandle textureColor = loadTexture("fieldstone-rgba.dds");


	int64_t timeOffset = bx::getHPCounter();

	while (!entry::processEvents(width, height, debug, reset) )
	{
		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		float time = (float)( (now-timeOffset)/double(bx::getHPFrequency() ) );

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/01-cube");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Rendering simple static mesh.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		float at[3]  = { 0.0f, 0.0f,   0.0f };
		float eye[3] = { 0.0f, 0.0f, -35.0f };

		// Set view and projection matrix for view 0.
		const bgfx::HMD* hmd = bgfx::getHMD();
		if (NULL != hmd)
		{
			float view[16];
			bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);

			float proj[16];
			bx::mtxProj(proj, hmd->eye[0].fov, 0.1f, 100.0f);

			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			//
			// Use HMD's width/height since HMD's internal frame buffer size
			// might be much larger than window size.
			bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
		}
		else
		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);
			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, width, height);
		}

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::submit(0);

		// Submit 11x11 cubes.
		for (uint32_t yy = 0; yy < 11; ++yy)
		{
			for (uint32_t xx = 0; xx < 11; ++xx)
			{
				float mtx[16];
				bx::mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
				mtx[12] = -15.0f + float(xx)*3.0f;
				mtx[13] = -15.0f + float(yy)*3.0f;
				mtx[14] = 0.0f;

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and fragment shaders.
				bgfx::setProgram(program);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(vbh);
				bgfx::setIndexBuffer(ibh);

				// Bind textures.
				bgfx::setTexture(0,u_texColor,textureColor);

				// Set render states.
				//bgfx::setState(BGFX_STATE_DEFAULT);

				// Set render states.
				bgfx::setState(0
					| BGFX_STATE_RGB_WRITE
					| BGFX_STATE_ALPHA_WRITE
					| BGFX_STATE_DEPTH_WRITE
					| BGFX_STATE_DEPTH_TEST_LESS
					| BGFX_STATE_MSAA
					);

				// Submit primitive for rendering to view 0.
				bgfx::submit(0);
			}
		}

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(program);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
