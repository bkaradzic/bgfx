/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
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

static PosTexcoordVertex s_m_cubeVertices[28] =
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

static const uint16_t s_m_cubeIndices[36] =
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

static const uint32_t m_textureside   = 512;
static const uint32_t m_texture2dSize = 256;

class Update : public entry::AppI
{
public:
	Update()
		: m_cube(m_textureside)
	{
	}

	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = 1280;
		m_height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
			);

		// Create vertex stream declaration.
		PosTexcoordVertex::init();

		m_textures[0] = loadTexture("texture_compression_bc1.dds",  BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);
		m_textures[1] = loadTexture("texture_compression_bc2.dds",  BGFX_TEXTURE_U_CLAMP);
		m_textures[2] = loadTexture("texture_compression_bc3.dds",  BGFX_TEXTURE_V_CLAMP);
		m_textures[3] = loadTexture("texture_compression_etc1.ktx", BGFX_TEXTURE_U_BORDER|BGFX_TEXTURE_V_BORDER|BGFX_TEXTURE_BORDER_COLOR(1) );
		m_textures[4] = loadTexture("texture_compression_etc2.ktx");
		m_textures[5] = loadTexture("texture_compression_ptc12.pvr");
		m_textures[6] = loadTexture("texture_compression_ptc14.pvr");
		m_textures[7] = loadTexture("texture_compression_ptc22.pvr");
		m_textures[8] = loadTexture("texture_compression_ptc24.pvr");

		const bgfx::Caps* caps = bgfx::getCaps();
		m_texture3DSupported = !!(caps->supported & BGFX_CAPS_TEXTURE_3D);
		m_blitSupported      = !!(caps->supported & BGFX_CAPS_TEXTURE_BLIT);
		m_numm_textures3d      = 0;

		if (m_texture3DSupported)
		{
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

			if (0 != (BGFX_CAPS_FORMAT_TEXTURE_2D & caps->formats[bgfx::TextureFormat::R8]) )
			{
				m_textures3d[m_numm_textures3d++] = bgfx::createTexture3D(32, 32, 32, 0, bgfx::TextureFormat::R8,   BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP, mem8);
			}

			if (0 != (BGFX_CAPS_FORMAT_TEXTURE_2D & caps->formats[bgfx::TextureFormat::R16F]) )
			{
				m_textures3d[m_numm_textures3d++] = bgfx::createTexture3D(32, 32, 32, 0, bgfx::TextureFormat::R16F, BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP, mem16f);
			}

			if (0 != (BGFX_CAPS_FORMAT_TEXTURE_2D & caps->formats[bgfx::TextureFormat::R32F]) )
			{
				m_textures3d[m_numm_textures3d++] = bgfx::createTexture3D(32, 32, 32, 0, bgfx::TextureFormat::R32F, BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP, mem32f);
			}
		}

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_m_cubeVertices, sizeof(s_m_cubeVertices) ), PosTexcoordVertex::ms_decl);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_m_cubeIndices, sizeof(s_m_cubeIndices) ) );

		// Create programs.
		m_program    = loadProgram("vs_update", "fs_update");
		m_programCmp = loadProgram("vs_update", "fs_update_cmp");
		m_program3d.idx = bgfx::invalidHandle;
		if (m_texture3DSupported)
		{
			m_program3d = loadProgram("vs_update", "fs_update_3d");
		}

		// Create texture sampler uniforms.
		s_texCube  = bgfx::createUniform("s_texCube",  bgfx::UniformType::Int1);
		s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);

		// Create time uniform.
		u_time = bgfx::createUniform("u_time", bgfx::UniformType::Vec4);

		m_textureCube[0] = bgfx::createTextureCube(m_textureside, 1
				, bgfx::TextureFormat::BGRA8
				, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT
				);

		if (m_blitSupported)
		{
			m_textureCube[1] = bgfx::createTextureCube(m_textureside, 1
					, bgfx::TextureFormat::BGRA8
					, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT|BGFX_TEXTURE_BLIT_DST
					);
		}

		m_texture2d = bgfx::createTexture2D(m_texture2dSize, m_texture2dSize, 1
				, bgfx::TextureFormat::BGRA8
				, BGFX_TEXTURE_MIN_POINT|BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIP_POINT
				);

		m_m_texture2dData = (uint8_t*)malloc(m_texture2dSize*m_texture2dSize*4);

		m_rr = rand()%255;
		m_gg = rand()%255;
		m_bb = rand()%255;

		m_hit  = 0;
		m_miss = 0;

		m_updateTime = 0;
		m_timeOffset = bx::getHPCounter();
	}

	virtual int shutdown() BX_OVERRIDE
	{
		// m_m_texture2dData is managed from main thread, and it's passed to renderer
		// just as MemoryRef. At this point render might be using it. We must wait
		// previous frame to finish before we can free it.
		bgfx::frame();

		// Cleanup.
		free(m_m_texture2dData);

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
		{
			bgfx::destroyTexture(m_textures[ii]);
		}

		for (uint32_t ii = 0; ii < m_numm_textures3d; ++ii)
		{
			bgfx::destroyTexture(m_textures3d[ii]);
		}

		bgfx::destroyTexture(m_texture2d);
		bgfx::destroyTexture(m_textureCube[0]);
		if (m_blitSupported)
		{
			bgfx::destroyTexture(m_textureCube[1]);
		}
		bgfx::destroyIndexBuffer(m_ibh);
		bgfx::destroyVertexBuffer(m_vbh);
		if (bgfx::isValid(m_program3d) )
		{
			bgfx::destroyProgram(m_program3d);
		}
		bgfx::destroyProgram(m_programCmp);
		bgfx::destroyProgram(m_program);
		bgfx::destroyUniform(u_time);
		bgfx::destroyUniform(s_texColor);
		bgfx::destroyUniform(s_texCube);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset) )
		{
			float borderColor[4] = { float(rand()%255)/255.0f, float(rand()%255)/255.0f, float(rand()%255)/255.0f, float(rand()%255)/255.0f };
			bgfx::setPaletteColor(1, borderColor);

			// Set view 0 and 1 viewport.
			bgfx::setViewRect(0, 0, 0, m_width, m_height);
			bgfx::setViewRect(1, 0, 0, m_width, m_height);

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const int64_t freq = bx::getHPFrequency();
			const double toMs = 1000.0/double(freq);
			float time = (float)( (now - m_timeOffset)/double(bx::getHPFrequency() ) );
			bgfx::setUniform(u_time, &time);

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/08-update");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Updating m_textures.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			if (now > m_updateTime)
			{
				PackCube face;

				uint32_t bw = bx::uint16_max(1, rand()%(m_textureside/4) );
				uint32_t bh = bx::uint16_max(1, rand()%(m_textureside/4) );

				if (m_cube.find(bw, bh, face) )
				{
					m_quads.push_back(face);

					++m_hit;
					const Pack2D& rect = face.m_rect;

					updateTextureCubeRectBgra8(m_textureCube[0], face.m_side, rect.m_x, rect.m_y, rect.m_width, rect.m_height, m_rr, m_gg, m_bb);
					if (m_blitSupported)
					{
						bgfx::blit(0, m_textureCube[1], 0, rect.m_x, rect.m_y, face.m_side, m_textureCube[0], 0, rect.m_x, rect.m_y, face.m_side, rect.m_width, rect.m_height);
					}

					m_rr = rand()%255;
					m_gg = rand()%255;
					m_bb = rand()%255;
				}
				else
				{
					++m_miss;

					for (uint32_t ii = 0, num = bx::uint32_min(10, (uint32_t)m_quads.size() ); ii < num; ++ii)
					{
						face = m_quads.front();
						const Pack2D& rect = face.m_rect;

						updateTextureCubeRectBgra8(m_textureCube[0], face.m_side, rect.m_x, rect.m_y, rect.m_width, rect.m_height, 0, 0, 0);
						if (m_blitSupported)
						{
							bgfx::blit(0, m_textureCube[1], 0, rect.m_x, rect.m_y, face.m_side, m_textureCube[0], 0, rect.m_x, rect.m_y, face.m_side, rect.m_width, rect.m_height);
						}

						m_cube.clear(face);
						m_quads.pop_front();
					}
				}

				{
					// Fill rect.
					const uint32_t pitch = m_texture2dSize*4;

					const uint16_t tw = rand()%m_texture2dSize;
					const uint16_t th = rand()%m_texture2dSize;
					const uint16_t tx = rand()%(m_texture2dSize-tw);
					const uint16_t ty = rand()%(m_texture2dSize-th);

					uint8_t* dst = &m_m_texture2dData[(ty*m_texture2dSize+tx)*4];
					uint8_t* next = dst + pitch;

					// Using makeRef to pass texture memory without copying.
					const bgfx::Memory* mem = bgfx::makeRef(dst, tw*th*4);

					for (uint32_t yy = 0; yy < th; ++yy, dst = next, next += pitch)
					{
						for (uint32_t xx = 0; xx < tw; ++xx, dst += 4)
						{
							dst[0] = m_bb;
							dst[1] = m_gg;
							dst[2] = m_rr;
							dst[3] = 255;
						}
					}

					// Pitch here makes possible to pass data from source to destination
					// without need for m_textures and allocated memory to be the same size.
					bgfx::updateTexture2D(m_texture2d, 0, tx, ty, tw, th, mem, pitch);
				}
			}

			bgfx::dbgTextPrintf(0, 4, 0x0f, "m_hit: %d, m_miss %d", m_hit, m_miss);

			float at[3] = { 0.0f, 0.0f, 0.0f };
			float eye[3] = { 0.0f, 0.0f, -5.0f };

			float view[16];
			float proj[16];
			bx::mtxLookAt(view, eye, at);
			bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f);

			// Set view and projection matrix for view 0.
			bgfx::setViewTransform(0, view, proj);

			for (uint32_t ii = 0; ii < 1 + uint32_t(m_blitSupported); ++ii)
			{
				float mtx[16];
				bx::mtxSRT(mtx, 1.0f, 1.0f, 1.0f, time, time*0.37f, 0.0f, -1.5f*m_blitSupported + ii*3.0f, 0.0f, 0.0f);

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(m_vbh);
				bgfx::setIndexBuffer(m_ibh);

				// Bind texture.
				bgfx::setTexture(0, s_texCube, m_textureCube[ii]);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 0.
				bgfx::submit(0, m_program);
			}

			// Set view and projection matrix for view 1.
			const float aspectRatio = float(m_height)/float(m_width);
			const float size = 11.0f;
			bx::mtxOrtho(proj, -size, size, size*aspectRatio, -size*aspectRatio, 0.0f, 1000.0f);
			bgfx::setViewTransform(1, NULL, proj);

			float mtx[16];
			bx::mtxTranslate(mtx, -size+2.0f - BX_COUNTOF(m_textures)*0.1f*0.5f, 1.9f, 0.0f);

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(m_vbh);
			bgfx::setIndexBuffer(m_ibh);

			// Bind texture.
			bgfx::setTexture(0, s_texColor, m_texture2d);

			// Set render states.
			bgfx::setState(BGFX_STATE_DEFAULT);

			// Submit primitive for rendering to view 1.
			bgfx::submit(1, m_programCmp);

			const float xpos = -size+2.0f - BX_COUNTOF(m_textures)*0.1f*0.5f;

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				bx::mtxTranslate(mtx, xpos + ii*2.1f, size-6.5f, 0.0f);

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(m_vbh);
				bgfx::setIndexBuffer(m_ibh, 0, 6);

				// Bind texture.
				bgfx::setTexture(0, s_texColor, m_textures[ii]);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 1.
				bgfx::submit(1, m_programCmp);
			}

			for (uint32_t ii = 0; ii < m_numm_textures3d; ++ii)
			{
				bx::mtxTranslate(mtx, xpos + ii*2.1f, -size+6.5f, 0.0f);

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(m_vbh);
				bgfx::setIndexBuffer(m_ibh, 0, 6);

				// Bind texture.
				bgfx::setTexture(0, s_texColor, m_textures3d[ii]);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 1.
				bgfx::submit(1, m_program3d);
			}

			for (uint32_t ii = 0; ii < 4; ++ii)
			{
				bx::mtxTranslate(mtx, xpos + (size-2.0f)*2.1f, -size+6.5f + ii*2.1f, 0.0f);

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(m_vbh, 24, 4);
				bgfx::setIndexBuffer(m_ibh, 0, 6);

				// Bind texture.
				bgfx::setTexture(0, s_texColor, m_textures[ii]);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 1.
				bgfx::submit(1, m_programCmp);
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();
			return true;
		}

		return false;
	}

	uint8_t* m_m_texture2dData;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	uint32_t m_numm_textures3d;
	bool m_texture3DSupported;
	bool m_blitSupported;

	std::list<PackCube> m_quads;
	RectPackCubeT<256> m_cube;
	int64_t m_updateTime;
	int64_t m_timeOffset;

	uint32_t m_hit;
	uint32_t m_miss;

	uint8_t m_rr;
	uint8_t m_gg;
	uint8_t m_bb;

	bgfx::TextureHandle m_textures[9];
	bgfx::TextureHandle m_textures3d[3];
	bgfx::TextureHandle m_texture2d;
	bgfx::TextureHandle m_textureCube[2];
	bgfx::IndexBufferHandle m_ibh;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::ProgramHandle m_program3d;
	bgfx::ProgramHandle m_programCmp;
	bgfx::ProgramHandle m_program;
	bgfx::UniformHandle u_time;
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texCube;

};

ENTRY_IMPLEMENT_MAIN(Update);
