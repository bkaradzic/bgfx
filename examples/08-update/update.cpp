/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <bx/bx.h>
#include <bx/timer.h>
#include "../common/dbg.h"
#include "../common/math.h"

#include <stdio.h>
#include <string.h>

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
	 0,  2,  1, // 0
	 1,  2,  3,

	 4,  5,  6, // 2
	 5,  7,  6,

	 8,  9, 10, // 4
	 9, 11, 10,

	12, 13, 14, // 6
	14, 13, 15, 

	16, 17, 18, // 8
	18, 17, 19,

	20, 21, 22, // 10
	21, 23, 22,
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

int _main_(int _argc, char** _argv)
{
	bgfx::init();
	bgfx::reset(1280, 720);

	// Enable debug text.
	bgfx::setDebug(BGFX_DEBUG_TEXT);

	// Set view 0 default viewport.
	bgfx::setViewRect(0, 0, 0, 1280, 720);

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

	uint32_t blockSide = 0;
	uint32_t blockX = 0;
	uint32_t blockY = 0;
	const uint32_t blockWidth = 8;
	const uint32_t blockHeight = 8;
	const uint32_t textureSide = 256;

	bgfx::TextureHandle textureCube = 
		bgfx::createTextureCube(6
			, textureSide
			, 1
			, bgfx::TextureFormat::BGRA8
			, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT
			);

	bgfx::TextureInfo ti;
	bgfx::calcTextureSize(ti, blockWidth, blockHeight, 1, 1, bgfx::TextureFormat::BGRA8);

	uint8_t rr = rand()%255;
	uint8_t gg = rand()%255;
	uint8_t bb = rand()%255;

	int64_t updateTime = 0;

	while (true)
	{
		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::submit(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const int64_t freq = bx::getHPFrequency();
		const double toMs = 1000.0/double(freq);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/08-update");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Updating textures.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		if (now > updateTime)
		{
//			updateTime = now + freq/100;
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

			bgfx::updateTextureCube(textureCube, blockSide, 0, blockX, blockY, blockWidth, blockHeight, mem);

			blockX += 8;
			if (blockX > textureSide-1)
			{
				blockX = 0;
				blockY += 8;

				if (blockY > textureSide-1)
				{
					rr = rand()%255;
					gg = rand()%255;
					bb = rand()%255;

					blockY = 0;
					++blockSide;

					if (blockSide > 5)
					{
						blockSide = 0;
					}
				}
			}
		}

		float at[3] = { 0.0f, 0.0f, 0.0f };
		float eye[3] = { 0.0f, 0.0f, -5.0f };
		
		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);
		mtxProj(proj, 60.0f, 16.0f/9.0f, 0.1f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		float time = (float)(bx::getHPCounter()/double(bx::getHPFrequency() ) );

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
		bgfx::setState(BGFX_STATE_RGB_WRITE
			|BGFX_STATE_DEPTH_WRITE
			|BGFX_STATE_DEPTH_TEST_LESS
			);

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

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
