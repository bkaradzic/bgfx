/*
 * Copyright 2011-2014 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"

#include <bgfx.h>
#include <bx/timer.h>
#include <bx/uint32_t.h>
#include "fpumath.h"
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

static PosColorVertex s_cubeVertices[28] =
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

	{-1.0f,  1.0f,  1.0f, -2.0f,  2.0f,  2.0f },
	{ 1.0f,  1.0f,  1.0f,  2.0f,  2.0f,  2.0f },
	{-1.0f, -1.0f,  1.0f, -2.0f, -2.0f,  2.0f },
	{ 1.0f, -1.0f,  1.0f,  2.0f, -2.0f,  2.0f },
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

static bgfx::ProgramHandle loadProgram(const char* _vshName, const char* _fshName)
{
	const bgfx::Memory* mem;

	mem = loadShader(_vshName);
	bgfx::ShaderHandle vsh = bgfx::createShader(mem);

	mem = loadShader(_fshName);
	bgfx::ShaderHandle fsh = bgfx::createShader(mem);

	// Create program from shaders.
	bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh);

	// We can destroy vertex and fragment shader here since
	// their reference is kept inside bgfx after calling createProgram.
	// Vertex and fragment shader will be destroyed once program is
	// destroyed.
	bgfx::destroyShader(vsh);
	bgfx::destroyShader(fsh);

	return program;
}

static const bgfx::Memory* loadTexture(const char* _name)
{
	char filePath[512];
	strcpy(filePath, "textures/");
	strcat(filePath, _name);
	return load(filePath);
}

static void updateTextureCubeRectBgra8(bgfx::TextureHandle _handle, uint8_t _side, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 0xff)
{
	bgfx::TextureInfo ti;
	bgfx::calcTextureSize(ti, _width, _height, 1, 1, bgfx::TextureFormat::BGRA8);

	const bgfx::Memory* mem = bgfx::alloc(ti.storageSize);
	uint8_t* data = (uint8_t*)mem->data;
	for (uint32_t ii = 0, num = ti.storageSize*8/ti.bitsPerPixel; ii < num; ++ii)
	{
		data[0] = _b;
		data[1] = _g;
		data[2] = _r;
		data[3] = _a;
		data += 4;
	}

	bgfx::updateTextureCube(_handle, _side, 0, _x, _y, _width, _height, mem);
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

	case bgfx::RendererType::OpenGLES:
		s_shaderPath = "shaders/gles/";
		break;
	}

	// Create vertex stream declaration.
	s_PosTexcoordDecl.begin();
	s_PosTexcoordDecl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
	s_PosTexcoordDecl.add(bgfx::Attrib::TexCoord0, 3, bgfx::AttribType::Float);
	s_PosTexcoordDecl.end();

	bgfx::TextureHandle textures[] =
	{
		bgfx::createTexture(loadTexture("texture_compression_bc1.dds"), BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP),
		bgfx::createTexture(loadTexture("texture_compression_bc2.dds"), BGFX_TEXTURE_U_CLAMP),
		bgfx::createTexture(loadTexture("texture_compression_bc3.dds"), BGFX_TEXTURE_V_CLAMP),
		bgfx::createTexture(loadTexture("texture_compression_etc1.ktx") ),
		bgfx::createTexture(loadTexture("texture_compression_etc2.ktx") ),
		bgfx::createTexture(loadTexture("texture_compression_ptc12.pvr") ),
		bgfx::createTexture(loadTexture("texture_compression_ptc14.pvr") ),
		bgfx::createTexture(loadTexture("texture_compression_ptc22.pvr") ),
		bgfx::createTexture(loadTexture("texture_compression_ptc24.pvr") ),
	};

	const bgfx::Memory* mem;

	// Create static vertex buffer.
	mem = bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) );
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(mem, s_PosTexcoordDecl);

	// Create static index buffer.
	mem = bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) );
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(mem);

	// Create texture sampler uniforms.
	bgfx::UniformHandle u_texCube = bgfx::createUniform("u_texCube", bgfx::UniformType::Uniform1iv);

	bgfx::UniformHandle u_texColor = bgfx::createUniform("u_texColor", bgfx::UniformType::Uniform1iv);

	bgfx::ProgramHandle program = loadProgram("vs_update", "fs_update");
	bgfx::ProgramHandle programCmp = loadProgram("vs_update", "fs_update_cmp");

	const uint32_t textureSide = 2048;

	bgfx::TextureHandle textureCube = bgfx::createTextureCube(textureSide, 1
		, bgfx::TextureFormat::BGRA8
		, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT
		);

	const uint32_t texture2dSize = 256;

	bgfx::TextureHandle texture2d = bgfx::createTexture2D(texture2dSize, texture2dSize, 1
		, bgfx::TextureFormat::BGRA8
		, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT
		);

	uint8_t* texture2dData = (uint8_t*)malloc(texture2dSize*texture2dSize*4);

	uint8_t rr = rand()%255;
	uint8_t gg = rand()%255;
	uint8_t bb = rand()%255;

	int64_t updateTime = 0;

	RectPackCubeT<256> cube(textureSide);

	uint32_t hit = 0;
	uint32_t miss = 0;
	std::list<PackCube> quads;

	int64_t timeOffset = bx::getHPCounter();

	while (!entry::processEvents(width, height, debug, reset) )
	{
		// Set view 0 and 1 viewport.
		bgfx::setViewRectMask(0x3, 0, 0, width, height);

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
				const Pack2D& rect = face.m_rect;

				updateTextureCubeRectBgra8(textureCube, face.m_side, rect.m_x, rect.m_y, rect.m_width, rect.m_height, rr, gg, bb);

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

			{
				// Fill rect.
				const uint32_t pitch = texture2dSize*4;

				const uint16_t tw = rand()%texture2dSize;
				const uint16_t th = rand()%texture2dSize;
				const uint16_t tx = rand()%(texture2dSize-tw);
				const uint16_t ty = rand()%(texture2dSize-th);

				uint8_t* dst = &texture2dData[(ty*texture2dSize+tx)*4];
				uint8_t* next = dst + pitch;

				// Using makeRef to pass texture memory without copying.
				const bgfx::Memory* mem = bgfx::makeRef(dst, tw*th*4);

				for (uint32_t yy = 0; yy < th; ++yy, dst = next, next += pitch)
				{
					for (uint32_t xx = 0; xx < tw; ++xx, dst += 4)
					{
						dst[0] = bb;
						dst[1] = gg;
						dst[2] = rr;
						dst[3] = 255;
					}
				}

				// Pitch here makes possible to pass data from source to destination
				// without need for textures and allocated memory to be the same size.
				bgfx::updateTexture2D(texture2d, 0, tx, ty, tw, th, mem, pitch);
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


		// Set view and projection matrix for view 1.
		const float aspectRatio = float(height)/float(width);
		const float size = 10.0f;
		mtxOrtho(proj, -size, size, size*aspectRatio, -size*aspectRatio, 0.0f, 1000.0f);
		bgfx::setViewTransform(1, NULL, proj);


		mtxTranslate(mtx, -8.0f - BX_COUNTOF(textures)*0.1f*0.5f, 1.9f, 0.0f);

		// Set model matrix for rendering.
		bgfx::setTransform(mtx);

		// Set vertex and fragment shaders.
		bgfx::setProgram(programCmp);

		// Set vertex and index buffer.
		bgfx::setVertexBuffer(vbh);
		bgfx::setIndexBuffer(ibh);

		// Bind texture.
		bgfx::setTexture(0, u_texColor, texture2d);

		// Set render states.
		bgfx::setState(BGFX_STATE_DEFAULT);

		// Submit primitive for rendering to view 0.
		bgfx::submit(1);


		for (uint32_t ii = 0; ii < BX_COUNTOF(textures); ++ii)
		{
			mtxTranslate(mtx, -8.0f - BX_COUNTOF(textures)*0.1f*0.5f + ii*2.1f, 4.0f, 0.0f);

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and fragment shaders.
			bgfx::setProgram(programCmp);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(vbh);
			bgfx::setIndexBuffer(ibh, 0, 6);

			// Bind texture.
			bgfx::setTexture(0, u_texColor, textures[ii]);

			// Set render states.
			bgfx::setState(BGFX_STATE_DEFAULT);

			// Submit primitive for rendering to view 0.
			bgfx::submit(1);
		}

		for (uint32_t ii = 0; ii < 3; ++ii)
		{
			mtxTranslate(mtx, -8.0f - BX_COUNTOF(textures)*0.1f*0.5f + 8*2.1f, -4.0f + ii*2.1f, 0.0f);

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and fragment shaders.
			bgfx::setProgram(programCmp);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(vbh, 24, 4);
			bgfx::setIndexBuffer(ibh, 0, 6);

			// Bind texture.
			bgfx::setTexture(0, u_texColor, textures[ii]);

			// Set render states.
			bgfx::setState(BGFX_STATE_DEFAULT);

			// Submit primitive for rendering to view 0.
			bgfx::submit(1);
		}

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// texture2dData is managed from main thread, and it's passed to renderer
	// just as MemoryRef. At this point render might be using it. We must wait
	// previous frame to finish before we can free it.
	bgfx::frame();

	// Cleanup.
	free(texture2dData);

	for (uint32_t ii = 0; ii < BX_COUNTOF(textures); ++ii)
	{
		bgfx::destroyTexture(textures[ii]);
	}

	bgfx::destroyTexture(texture2d);
	bgfx::destroyTexture(textureCube);
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(programCmp);
	bgfx::destroyProgram(program);
	bgfx::destroyUniform(u_texColor);
	bgfx::destroyUniform(u_texCube);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
