/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include "bgfx_utils.h"

#include <bx/uint32_t.h>
#include "packrect.h"

#include <list>

struct PosTexcoordVertex
{
	float m_x;
	float m_y;
	float m_z;
	float m_u;
	float m_v;
	float m_w;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 3, bgfx::AttribType::Float)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosTexcoordVertex::ms_decl;

static PosTexcoordVertex s_cubeVertices[28] =
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

static void updateTextureCubeRectBgra8(bgfx::TextureHandle _handle, uint8_t _side, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 0xff)
{
	bgfx::TextureInfo ti;
	bgfx::calcTextureSize(ti, _width, _height, 1, 1, false, bgfx::TextureFormat::BGRA8);

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
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	// Create vertex stream declaration.
	PosTexcoordVertex::init();

	bgfx::TextureHandle textures[] =
	{
		loadTexture("texture_compression_bc1.dds",  BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP),
		loadTexture("texture_compression_bc2.dds",  BGFX_TEXTURE_U_CLAMP),
		loadTexture("texture_compression_bc3.dds",  BGFX_TEXTURE_V_CLAMP),
		loadTexture("texture_compression_etc1.ktx", BGFX_TEXTURE_U_BORDER|BGFX_TEXTURE_V_BORDER),
		loadTexture("texture_compression_etc2.ktx"),
		loadTexture("texture_compression_ptc12.pvr"),
		loadTexture("texture_compression_ptc14.pvr"),
		loadTexture("texture_compression_ptc22.pvr"),
		loadTexture("texture_compression_ptc24.pvr"),
	};

	const bgfx::Memory* mem8   = bgfx::alloc(32*32*32);
	const bgfx::Memory* mem16f = bgfx::alloc(32*32*32*2);
	const bgfx::Memory* mem32f = bgfx::alloc(32*32*32*4);
	for (uint8_t zz = 0; zz < 32; ++zz)
	{
		for (uint8_t yy = 0; yy < 32; ++yy)
		{
			for (uint8_t xx = 0; xx < 32; ++xx)
			{
				const uint32_t offset = ( (zz*32+yy)*32+xx);
				const uint32_t val = xx ^ yy ^ zz;
				mem8->data[offset] = val<<3;
				*(uint16_t*)&mem16f->data[offset*2] = bx::halfFromFloat( (float)val/32.0f);
				*(float*)&mem32f->data[offset*4] = (float)val/32.0f;
			}
		}
	}

	const bgfx::Caps* caps = bgfx::getCaps();
	const bool texture3DSupported = !!(caps->supported & BGFX_CAPS_TEXTURE_3D);

	uint32_t numTextures3d = 0;
	bgfx::TextureHandle textures3d[3] = {};

	if (texture3DSupported)
	{
		if (0 != (BGFX_CAPS_FORMAT_TEXTURE_COLOR & caps->formats[bgfx::TextureFormat::R8]) )
		{
			textures3d[numTextures3d++] = bgfx::createTexture3D(32, 32, 32, 0, bgfx::TextureFormat::R8,   BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP, mem8);
		}

		if (0 != (BGFX_CAPS_FORMAT_TEXTURE_COLOR & caps->formats[bgfx::TextureFormat::R16F]) )
		{
			textures3d[numTextures3d++] = bgfx::createTexture3D(32, 32, 32, 0, bgfx::TextureFormat::R16F, BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP, mem16f);
		}

		if (0 != (BGFX_CAPS_FORMAT_TEXTURE_COLOR & caps->formats[bgfx::TextureFormat::R32F]) )
		{
			textures3d[numTextures3d++] = bgfx::createTexture3D(32, 32, 32, 0, bgfx::TextureFormat::R32F, BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP, mem32f);
		}
	}

	// Create static vertex buffer.
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) ), PosTexcoordVertex::ms_decl);

	// Create static index buffer.
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

	// Create texture sampler uniforms.
	bgfx::UniformHandle s_texCube  = bgfx::createUniform("s_texCube",  bgfx::UniformType::Int1);
	bgfx::UniformHandle s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);

	bgfx::UniformHandle u_time = bgfx::createUniform("u_time", bgfx::UniformType::Vec4);

	bgfx::ProgramHandle program     = loadProgram("vs_update", "fs_update");
	bgfx::ProgramHandle programCmp  = loadProgram("vs_update", "fs_update_cmp");
	bgfx::ProgramHandle program3d   = BGFX_INVALID_HANDLE;
	if (texture3DSupported)
	{
		program3d = loadProgram("vs_update", "fs_update_3d");
	}

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
		bgfx::setViewRect(0, 0, 0, width, height);
		bgfx::setViewRect(1, 0, 0, width, height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const int64_t freq = bx::getHPFrequency();
		const double toMs = 1000.0/double(freq);
		float time = (float)( (now - timeOffset)/double(bx::getHPFrequency() ) );
		bgfx::setUniform(u_time, &time);

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
					cube.clear(quads.front() );
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
		bx::mtxLookAt(view, eye, at);
		bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		float mtx[16];
		bx::mtxRotateXY(mtx, time, time*0.37f);

		// Set model matrix for rendering.
		bgfx::setTransform(mtx);

		// Set vertex and index buffer.
		bgfx::setVertexBuffer(vbh);
		bgfx::setIndexBuffer(ibh);

		// Bind texture.
		bgfx::setTexture(0, s_texCube, textureCube);

		// Set render states.
		bgfx::setState(BGFX_STATE_DEFAULT);

		// Submit primitive for rendering to view 0.
		bgfx::submit(0, program);


		// Set view and projection matrix for view 1.
		const float aspectRatio = float(height)/float(width);
		const float size = 11.0f;
		bx::mtxOrtho(proj, -size, size, size*aspectRatio, -size*aspectRatio, 0.0f, 1000.0f);
		bgfx::setViewTransform(1, NULL, proj);


		bx::mtxTranslate(mtx, -size+2.0f - BX_COUNTOF(textures)*0.1f*0.5f, 1.9f, 0.0f);

		// Set model matrix for rendering.
		bgfx::setTransform(mtx);

		// Set vertex and index buffer.
		bgfx::setVertexBuffer(vbh);
		bgfx::setIndexBuffer(ibh);

		// Bind texture.
		bgfx::setTexture(0, s_texColor, texture2d);

		// Set render states.
		bgfx::setState(BGFX_STATE_DEFAULT);

		// Submit primitive for rendering to view 1.
		bgfx::submit(1, programCmp);

		const float xpos = -size+2.0f - BX_COUNTOF(textures)*0.1f*0.5f;

		for (uint32_t ii = 0; ii < BX_COUNTOF(textures); ++ii)
		{
			bx::mtxTranslate(mtx, xpos + ii*2.1f, size-6.5f, 0.0f);

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(vbh);
			bgfx::setIndexBuffer(ibh, 0, 6);

			// Bind texture.
			bgfx::setTexture(0, s_texColor, textures[ii]);

			// Set render states.
			bgfx::setState(BGFX_STATE_DEFAULT);

			// Submit primitive for rendering to view 1.
			bgfx::submit(1, programCmp);
		}

		for (uint32_t ii = 0; ii < numTextures3d; ++ii)
		{
			bx::mtxTranslate(mtx, xpos + ii*2.1f, -size+6.5f, 0.0f);

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(vbh);
			bgfx::setIndexBuffer(ibh, 0, 6);

			// Bind texture.
			bgfx::setTexture(0, s_texColor, textures3d[ii]);

			// Set render states.
			bgfx::setState(BGFX_STATE_DEFAULT);

			// Submit primitive for rendering to view 1.
			bgfx::submit(1, program3d);
		}

		for (uint32_t ii = 0; ii < 4; ++ii)
		{
			bx::mtxTranslate(mtx, xpos + (size-2.0f)*2.1f, -size+6.5f + ii*2.1f, 0.0f);

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(vbh, 24, 4);
			bgfx::setIndexBuffer(ibh, 0, 6);

			// Bind texture.
			bgfx::setTexture(0, s_texColor, textures[ii]);

			// Set render states.
			bgfx::setState(BGFX_STATE_DEFAULT);

			// Submit primitive for rendering to view 1.
			bgfx::submit(1, programCmp);
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

	for (uint32_t ii = 0; ii < numTextures3d; ++ii)
	{
		bgfx::destroyTexture(textures3d[ii]);
	}

	bgfx::destroyTexture(texture2d);
	bgfx::destroyTexture(textureCube);
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	if (bgfx::isValid(program3d) )
	{
		bgfx::destroyProgram(program3d);
	}
	bgfx::destroyProgram(programCmp);
	bgfx::destroyProgram(program);
	bgfx::destroyUniform(u_time);
	bgfx::destroyUniform(s_texColor);
	bgfx::destroyUniform(s_texCube);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
