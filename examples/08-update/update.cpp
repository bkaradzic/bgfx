/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"

#include <bgfx.h>
#include <bx/timer.h>
#include <bx/uint32_t.h>
#include "entry.h"
#include "dbg.h"
#include "fpumath.h"
#include "processevents.h"
#include "packrect.h"

#include <stdio.h>
#include <string.h>
#include <list>

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	float m_u;
	float m_v;
	float m_w;
};

static bgfx::VertexDecl s_PosTexcoordDecl;

static PosColorVertex s_cubeVertices[24] =
{
	{-1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f },
	{ 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f },
	{-1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f },
	{ 1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f },

	{-1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f },
	{ 1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f },
	{-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f },
	{ 1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f },

	{-1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f },
	{-1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f },
	{-1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f },
	{-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f },

	{ 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f },
	{ 1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f },
	{ 1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f },
	{ 1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f },

	{-1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f },
	{ 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f },
	{-1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f },
	{ 1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f },

	{-1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f },
	{-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f },
	{ 1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f },
	{ 1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f },
};

static const uint16_t s_cubeIndices[36] =
{
	 0,  1,  2, // 0
	 1,  3,  2,
		  
	 4,  6,  5, // 2
	 5,  6,  7,
		  
	 8, 10,  9, // 4
	 9, 10, 11,
		  
	12, 14, 13, // 6
	14, 15, 13, 
		  
	16, 18, 17, // 8
	18, 19, 17,
		  
	20, 22, 21, // 10
	21, 22, 23,
};

static const char* s_shaderPath = NULL;

static void shaderFilePath(char* _out, const char* _name)
{
	strcpy(_out, s_shaderPath);
	strcat(_out, _name);
	strcat(_out, ".bin");
}

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

static const bgfx::Memory* load(const char* _filePath)
{
	FILE* file = fopen(_filePath, "rb");
	if (NULL != file)
	{
		uint32_t size = (uint32_t)fsize(file);
		const bgfx::Memory* mem = bgfx::alloc(size+1);
		size_t ignore = fread(mem->data, 1, size, file);
		BX_UNUSED(ignore);
		fclose(file);
		mem->data[mem->size-1] = '\0';
		return mem;
	}

	return NULL;
}

static const bgfx::Memory* loadShader(const char* _name)
{
	char filePath[512];
	shaderFilePath(filePath, _name);
	return load(filePath);
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

	// Create vertex stream declaration.
	s_PosTexcoordDecl.begin();
	s_PosTexcoordDecl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
	s_PosTexcoordDecl.add(bgfx::Attrib::TexCoord0, 3, bgfx::AttribType::Float);
	s_PosTexcoordDecl.end();

	const bgfx::Memory* mem;

	// Create static vertex buffer.
	mem = bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) );
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(mem, s_PosTexcoordDecl);

	// Create static index buffer.
	mem = bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) );
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(mem);

	// Create texture sampler uniforms.
	bgfx::UniformHandle u_texCube = bgfx::createUniform("u_texCube", bgfx::UniformType::Uniform1iv);

	// Load vertex shader.
	mem = loadShader("vs_update");
	bgfx::VertexShaderHandle vsh = bgfx::createVertexShader(mem);

	// Load fragment shader.
	mem = loadShader("fs_update");
	bgfx::FragmentShaderHandle fsh = bgfx::createFragmentShader(mem);

	// Create program from shaders.
	bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh);

	// We can destroy vertex and fragment shader here since
	// their reference is kept inside bgfx after calling createProgram.
	// Vertex and fragment shader will be destroyed once program is
	// destroyed.
	bgfx::destroyVertexShader(vsh);
	bgfx::destroyFragmentShader(fsh);

	const uint32_t textureSide = 2048;

	bgfx::TextureHandle textureCube = 
		bgfx::createTextureCube(6
			, textureSide
			, 1
			, bgfx::TextureFormat::BGRA8
			, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT
			);

	uint8_t rr = rand()%255;
	uint8_t gg = rand()%255;
	uint8_t bb = rand()%255;

	int64_t updateTime = 0;

	RectPackCubeT<256> cube(textureSide);

	uint32_t hit = 0;
	uint32_t miss = 0;
	std::list<PackCube> quads;

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
		const int64_t freq = bx::getHPFrequency();
		const double toMs = 1000.0/double(freq);
		float time = (float)( (now - timeOffset)/double(bx::getHPFrequency() ) );

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/08-update");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Updating textures.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		if (now > updateTime)
		{
			PackCube face;

			uint32_t bw = bx::uint16_max(1, rand()%(textureSide/4) );
			uint32_t bh = bx::uint16_max(1, rand()%(textureSide/4) );

			if (cube.find(bw, bh, face) )
			{
				quads.push_back(face);

				++hit;
				bgfx::TextureInfo ti;
				const Pack2D& rect = face.m_rect;
				bgfx::calcTextureSize(ti, rect.m_width, rect.m_height, 1, 1, bgfx::TextureFormat::BGRA8);

// 				updateTime = now + freq/10;
				const bgfx::Memory* mem = bgfx::alloc(ti.storageSize);
				uint8_t* data = (uint8_t*)mem->data;
				for (uint32_t ii = 0, num = ti.storageSize*8/ti.bitsPerPixel; ii < num; ++ii)
				{
					data[0] = bb;
					data[1] = rr;
					data[2] = gg;
					data[3] = 0xff;
					data += 4;
				}

				bgfx::updateTextureCube(textureCube, face.m_side, 0, rect.m_x, rect.m_y, rect.m_width, rect.m_height, mem);

				rr = rand()%255;
				gg = rand()%255;
				bb = rand()%255;
			}
			else
			{
				++miss;

				for (uint32_t ii = 0, num = bx::uint32_min(10, (uint32_t)quads.size() ); ii < num; ++ii)
				{
					const PackCube& face = quads.front();
					cube.clear(face);
					quads.pop_front();
				}
			}
		}

		bgfx::dbgTextPrintf(0, 4, 0x0f, "hit: %d, miss %d", hit, miss);

		float at[3] = { 0.0f, 0.0f, 0.0f };
		float eye[3] = { 0.0f, 0.0f, -5.0f };
		
		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);
		mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		float mtx[16];
		mtxRotateXY(mtx, time, time*0.37f);

		// Set model matrix for rendering.
		bgfx::setTransform(mtx);

		// Set vertex and fragment shaders.
		bgfx::setProgram(program);

		// Set vertex and index buffer.
		bgfx::setVertexBuffer(vbh);
		bgfx::setIndexBuffer(ibh);

		// Bind texture.
		bgfx::setTexture(0, u_texCube, textureCube);

		// Set render states.
		bgfx::setState(BGFX_STATE_DEFAULT);

		// Submit primitive for rendering to view 0.
		bgfx::submit(0);

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(program);
	bgfx::destroyTexture(textureCube);
	bgfx::destroyUniform(u_texCube);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
