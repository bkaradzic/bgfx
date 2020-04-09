/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "packrect.h"
#include "imgui/imgui.h"
#include "entry/entry.h"
#include <bimg/decode.h>

#include <bx/rng.h>

#include <list>

namespace
{

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
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 3, bgfx::AttribType::Float)
			.end();
	};

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosTexcoordVertex::ms_layout;

static PosTexcoordVertex s_cubeVertices[] =
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
BX_STATIC_ASSERT(BX_COUNTOF(s_cubeVertices) == 28);

static const uint16_t s_cubeIndices[] =
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
BX_STATIC_ASSERT(BX_COUNTOF(s_cubeIndices) == 36);

bx::Vec3 s_faceColors[] =
{
	{ 0.75f, 0.0f,  0.0f  },
	{ 0.75f, 0.75f, 0.0f  },
	{ 0.75f, 0.0f,  0.75f },
	{ 0.0f,  0.75f, 0.0f  },
	{ 0.0f,  0.75f, 0.75f },
	{ 0.0f,  0.0f,  0.75f },
};

static void updateTextureCubeRectBgra8(
	  bgfx::TextureHandle _handle
	, uint8_t _side
	, uint16_t _x
	, uint16_t _y
	, uint16_t _width
	, uint16_t _height
	, uint8_t _r
	, uint8_t _g
	, uint8_t _b
	, uint8_t _a = 0xff
	)
{
	bgfx::TextureInfo ti;
	bgfx::calcTextureSize(ti, _width, _height, 1, false, false, 1, bgfx::TextureFormat::BGRA8);

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

	bgfx::updateTextureCube(_handle, 0, _side, 0, _x, _y, _width, _height, mem);
}

bgfx::TextureHandle loadTextureWithUpdate(const char* _filePath, uint64_t _flags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE)
{
	bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

	uint32_t size;
	void* data = load(_filePath, &size);
	if (NULL != data)
	{
		bimg::ImageContainer* imageContainer = bimg::imageParse(entry::getAllocator(), data, size);

		if (NULL != imageContainer)
		{
			BX_CHECK(!imageContainer->m_cubeMap, "Cubemap Texture loading not supported");
			BX_CHECK(1 >= imageContainer->m_depth, "3D Texture loading not supported");
			BX_CHECK(1 == imageContainer->m_numLayers, "Texture Layer loading not supported");

			if (!imageContainer->m_cubeMap
			&&  1 >= imageContainer->m_depth
			&&  1 == imageContainer->m_numLayers
			&&  bgfx::isTextureValid(0, false, imageContainer->m_numLayers, bgfx::TextureFormat::Enum(imageContainer->m_format), _flags)
			   )
			{
				handle = bgfx::createTexture2D(
					  uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, NULL
					);

				uint32_t width = imageContainer->m_width;
				uint32_t height = imageContainer->m_height;

				for (uint8_t lod = 0, num = imageContainer->m_numMips; lod < num; ++lod)
				{
					if (width < 4 || height < 4)
					{
						break;
					}

					width  = bx::max(1u, width);
					height = bx::max(1u, height);

					bimg::ImageMip mip;

					if (bimg::imageGetRawData(*imageContainer, 0, lod, imageContainer->m_data, imageContainer->m_size, mip))
					{
						const uint8_t* mipData = mip.m_data;
						uint32_t mipDataSize = mip.m_size;

						bgfx::updateTexture2D(
							  handle
							, 0
							, lod
							, 0
							, 0
							, uint16_t(width)
							, uint16_t(height)
							, bgfx::copy(mipData, mipDataSize)
							);
					}

					width  >>= 1;
					height >>= 1;
				}

				unload(data);
			}

			if (bgfx::isValid(handle))
			{
				bgfx::setName(handle, _filePath);
			}
		}
	}

	return handle;
}

static const uint16_t kTextureSide   = 512;
static const uint32_t kTexture2dSize = 256;

class ExampleUpdate : public entry::AppI
{
public:
	ExampleUpdate(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
		, m_cube(kTextureSide)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
			);

		m_showDescriptions = true;

		// Create vertex stream declaration.
		PosTexcoordVertex::init();

		m_textures[ 0] = loadTexture("textures/texture_compression_bc1.ktx", BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);
		m_textures[ 1] = loadTexture("textures/texture_compression_bc2.ktx", BGFX_SAMPLER_U_CLAMP);
		m_textures[ 2] = loadTexture("textures/texture_compression_bc3.ktx", BGFX_SAMPLER_V_CLAMP);
		m_textures[ 3] = loadTexture("textures/texture_compression_etc1.ktx", BGFX_SAMPLER_U_BORDER | BGFX_SAMPLER_V_BORDER | BGFX_SAMPLER_BORDER_COLOR(1));
		m_textures[ 4] = loadTexture("textures/texture_compression_etc2.ktx");
		m_textures[ 5] = loadTexture("textures/texture_compression_ptc12.pvr");
		m_textures[ 6] = loadTexture("textures/texture_compression_ptc14.pvr");
		m_textures[ 7] = loadTexture("textures/texture_compression_ptc22.pvr");
		m_textures[ 8] = loadTexture("textures/texture_compression_ptc24.pvr");
		m_textures[ 9] = loadTexture("textures/texture_compression_atc.dds");
		m_textures[10] = loadTexture("textures/texture_compression_atci.dds");
		m_textures[11] = loadTexture("textures/texture_compression_atce.dds");

		m_textures[12] = loadTextureWithUpdate("textures/texture_compression_bc1.ktx", BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);
		m_textures[13] = loadTextureWithUpdate("textures/texture_compression_bc2.ktx", BGFX_SAMPLER_U_CLAMP);
		m_textures[14] = loadTextureWithUpdate("textures/texture_compression_bc3.ktx", BGFX_SAMPLER_V_CLAMP);
		m_textures[15] = loadTextureWithUpdate("textures/texture_compression_etc1.ktx", BGFX_SAMPLER_U_BORDER | BGFX_SAMPLER_V_BORDER | BGFX_SAMPLER_BORDER_COLOR(1));
		m_textures[16] = loadTextureWithUpdate("textures/texture_compression_etc2.ktx");
		m_textures[17] = loadTextureWithUpdate("textures/texture_compression_ptc12.pvr");
		m_textures[18] = loadTextureWithUpdate("textures/texture_compression_ptc14.pvr");
		m_textures[19] = loadTextureWithUpdate("textures/texture_compression_ptc22.pvr");
		m_textures[20] = loadTextureWithUpdate("textures/texture_compression_ptc24.pvr");
		m_textures[21] = loadTextureWithUpdate("textures/texture_compression_atc.dds");
		m_textures[22] = loadTextureWithUpdate("textures/texture_compression_atci.dds");
		m_textures[23] = loadTextureWithUpdate("textures/texture_compression_atce.dds");

		BX_STATIC_ASSERT(24 == BX_COUNTOF(m_textures));

		const bgfx::Caps* caps = bgfx::getCaps();
		m_texture3DSupported = !!(caps->supported & BGFX_CAPS_TEXTURE_3D);
		m_blitSupported      = !!(caps->supported & BGFX_CAPS_TEXTURE_BLIT);
		m_computeSupported   = !!(caps->supported & BGFX_CAPS_COMPUTE);
		m_numTextures3d      = 0;

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
						mem8->data[offset] = uint8_t(val<<3);
						*(uint16_t*)&mem16f->data[offset*2] = bx::halfFromFloat( (float)val/32.0f);
						*(float*)&mem32f->data[offset*4] = (float)val/32.0f;
					}
				}
			}

			if (0 != (BGFX_CAPS_FORMAT_TEXTURE_3D & caps->formats[bgfx::TextureFormat::R8]) )
			{
				m_textures3d[m_numTextures3d++] = bgfx::createTexture3D(32, 32, 32, false, bgfx::TextureFormat::R8,   BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_SAMPLER_W_CLAMP, mem8);
			}

			if (0 != (BGFX_CAPS_FORMAT_TEXTURE_3D & caps->formats[bgfx::TextureFormat::R16F]) )
			{
				m_textures3d[m_numTextures3d++] = bgfx::createTexture3D(32, 32, 32, false, bgfx::TextureFormat::R16F, BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_SAMPLER_W_CLAMP, mem16f);
			}

			if (0 != (BGFX_CAPS_FORMAT_TEXTURE_3D & caps->formats[bgfx::TextureFormat::R32F]) )
			{
				m_textures3d[m_numTextures3d++] = bgfx::createTexture3D(32, 32, 32, false, bgfx::TextureFormat::R32F, BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_SAMPLER_W_CLAMP, mem32f);
			}
		}

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) ), PosTexcoordVertex::ms_layout);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

		// Create programs.
		m_program       = loadProgram("vs_update", "fs_update");
		m_programCmp    = loadProgram("vs_update", "fs_update_cmp");
		m_program3d.idx = bgfx::kInvalidHandle;

		if (m_texture3DSupported)
		{
			m_program3d = loadProgram("vs_update", "fs_update_3d");
		}

		m_programCompute.idx = bgfx::kInvalidHandle;

		if (m_computeSupported)
		{
			m_programCompute = bgfx::createProgram( loadShader( "cs_update" ), true );
		}

		// Create texture sampler uniforms.
		s_texCube  = bgfx::createUniform("s_texCube",  bgfx::UniformType::Sampler);
		s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);

		// Create time uniform.
		u_time = bgfx::createUniform("u_time", bgfx::UniformType::Vec4);

		for(uint32_t ii = 0; ii<BX_COUNTOF( m_textureCube ); ++ii)
		{
			m_textureCube[ii].idx = bgfx::kInvalidHandle;
		}

		m_textureCube[0] = bgfx::createTextureCube(
			  kTextureSide
			, false
			, 1
			, bgfx::TextureFormat::BGRA8
			, BGFX_SAMPLER_MIN_POINT|BGFX_SAMPLER_MAG_POINT|BGFX_SAMPLER_MIP_POINT
			);

		if (m_blitSupported)
		{
			m_textureCube[1] = bgfx::createTextureCube(
				  kTextureSide
				, false
				, 1
				, bgfx::TextureFormat::BGRA8
				, BGFX_SAMPLER_MIN_POINT|BGFX_SAMPLER_MAG_POINT|BGFX_SAMPLER_MIP_POINT|BGFX_TEXTURE_BLIT_DST
				);
		}

		if (m_computeSupported)
		{
			m_textureCube[2] = bgfx::createTextureCube(
				  kTextureSide
				, false
				, 1
				, bgfx::TextureFormat::RGBA8
				, BGFX_TEXTURE_COMPUTE_WRITE
				);
		}

		{
			m_textureCube[3] = bgfx::createTextureCube(kTextureSide, false, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT);

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textureCubeFaceFb); ++ii)
			{
				bgfx::Attachment at;
				at.init(m_textureCube[3], bgfx::Access::Write, uint16_t(ii));
				m_textureCubeFaceFb[ii] = bgfx::createFrameBuffer(1, &at);
			}
		}

		m_texture2d = bgfx::createTexture2D(
			  kTexture2dSize
			, kTexture2dSize
			, false
			, 1
			, bgfx::TextureFormat::BGRA8
			, BGFX_SAMPLER_MIN_POINT|BGFX_SAMPLER_MAG_POINT|BGFX_SAMPLER_MIP_POINT
			);

		m_texture2dData = (uint8_t*)malloc(kTexture2dSize*kTexture2dSize*4);

		m_rr = m_rng.gen()%255;
		m_gg = m_rng.gen()%255;
		m_bb = m_rng.gen()%255;

		m_hit  = 0;
		m_miss = 0;

		m_updateTime = 0;
		m_timeOffset = bx::getHPCounter();

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		// m_texture2dData is managed from main thread, and it's passed to renderer
		// just as MemoryRef. At this point render might be using it. We must wait
		// previous frame to finish before we can free it.
		bgfx::frame();

		// Cleanup.
		free(m_texture2dData);

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
		{
			bgfx::destroy(m_textures[ii]);
		}

		for (uint32_t ii = 0; ii < m_numTextures3d; ++ii)
		{
			bgfx::destroy(m_textures3d[ii]);
		}

		bgfx::destroy(m_texture2d);

		for (uint32_t ii = 0; ii<BX_COUNTOF(m_textureCube); ++ii)
		{
			if (bgfx::isValid(m_textureCube[ii]))
			{
				bgfx::destroy(m_textureCube[ii]);
			}
		}

		for (uint32_t ii = 0; ii<BX_COUNTOF(m_textureCubeFaceFb); ++ii)
		{
			if (bgfx::isValid(m_textureCubeFaceFb[ii]))
			{
				bgfx::destroy(m_textureCubeFaceFb[ii]);
			}
		}

		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		if (bgfx::isValid(m_program3d) )
		{
			bgfx::destroy(m_program3d);
		}
		bgfx::destroy(m_programCmp);
		if (bgfx::isValid(m_programCompute) )
		{
			bgfx::destroy(m_programCompute);
		}
		bgfx::destroy(m_program);
		bgfx::destroy(u_time);
		bgfx::destroy(s_texColor);
		bgfx::destroy(s_texCube);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	void ImGuiDescription(float _x, float _y, float _z, const float* _worldToScreen, const char* _text)
	{
		if (m_showDescriptions)
		{
			float worldPos[4] = { _x, _y, _z, 1.0f };
			float screenPos[4];

			bx::vec4MulMtx(screenPos, worldPos, _worldToScreen);

			ImGui::SetNextWindowPos(ImVec2(screenPos[0] / screenPos[3], screenPos[1] / screenPos[3]), 0, ImVec2(0.5f, 0.5f));
			ImGuiWindowFlags flags = ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;
			ImGui::SetNextWindowBgAlpha(0.5f);

			ImGui::Begin(_text, NULL, flags);
			ImGui::Text("%s", _text);
			ImGui::End();
		}
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this);

			ImGui::SetNextWindowPos (ImVec2( 10.0f, 270.0f), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(150.0f,  70.0f), ImGuiCond_FirstUseEver);

			ImGui::Begin(
				  "Show descriptions"
				, NULL
				, ImGuiWindowFlags_NoResize
				);

			if (ImGui::Button(m_showDescriptions ? "On" : "Off"))
			{
				m_showDescriptions = !m_showDescriptions;
			}

			ImGui::End();

			float borderColor[4] =
			{
				float(m_rng.gen()%255)/255.0f,
				float(m_rng.gen()%255)/255.0f,
				float(m_rng.gen()%255)/255.0f,
				float(m_rng.gen()%255)/255.0f,
			};
			bgfx::setPaletteColor(1, borderColor);

			// Set view 0 and 1 viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			bgfx::setViewRect(1, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			float time = (float)( (now - m_timeOffset)/double(bx::getHPFrequency() ) );
			bgfx::setUniform(u_time, &time);

			if (now > m_updateTime)
			{
				PackCube face;

				uint16_t bw = bx::max<uint16_t>(1, m_rng.gen()%(kTextureSide/4) );
				uint16_t bh = bx::max<uint16_t>(1, m_rng.gen()%(kTextureSide/4) );

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

					m_rr = m_rng.gen()%255;
					m_gg = m_rng.gen()%255;
					m_bb = m_rng.gen()%255;
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
					const uint32_t pitch = kTexture2dSize*4;

					const uint16_t tw = m_rng.gen()% kTexture2dSize;
					const uint16_t th = m_rng.gen()% kTexture2dSize;
					const uint16_t tx = m_rng.gen()%(kTexture2dSize-tw);
					const uint16_t ty = m_rng.gen()%(kTexture2dSize-th);

					uint8_t* dst = &m_texture2dData[(ty*kTexture2dSize+tx)*4];
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
					bgfx::updateTexture2D(m_texture2d, 0, 0, tx, ty, tw, th, mem, pitch);
				}
			}

			const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };

			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

			// Set view and projection matrix for view 0.
			bgfx::setViewTransform(0, view, proj);

			float projToScreen[16];
			bx::mtxSRT(projToScreen, float(m_width) * 0.5f, -float(m_height) * 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, float(m_width) * 0.5f, float(m_height) * 0.5f, 0.0f);

			float viewProj[16];
			bx::mtxMul(viewProj, view, proj);

			float worldToScreen[16];
			bx::mtxMul(worldToScreen, viewProj, projToScreen);

			// Update texturecube using compute shader
			if (bgfx::isValid(m_programCompute) )
			{
				bgfx::setImage(0, m_textureCube[2], 0, bgfx::Access::Write);
				bgfx::dispatch(0, m_programCompute, kTextureSide/16, kTextureSide/16);
			}

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textureCubeFaceFb); ++ii)
			{
				bgfx::ViewId viewId = bgfx::ViewId(ii+2);
				bgfx::setViewFrameBuffer(viewId, m_textureCubeFaceFb[ii]);

				bx::Vec3 color = bx::add(s_faceColors[ii], bx::sin(time*4.0f)*0.25f);
				uint32_t colorRGB8 = 0
					| uint32_t(bx::toUnorm(color.x, 255.0f) ) << 24
					| uint32_t(bx::toUnorm(color.y, 255.0f) ) << 16
					| uint32_t(bx::toUnorm(color.z, 255.0f) ) <<  8
					;

				bgfx::setViewClear(viewId, BGFX_CLEAR_COLOR, colorRGB8);
				bgfx::setViewRect(viewId, 0,0,512,512);

				bgfx::touch(viewId);
			}

			static const char* descTextureCube[BX_COUNTOF(m_textureCube)] =
			{
					"updateTextureCube",
					"blit",
					"compute",
					"frameBuffer",
			};
			BX_STATIC_ASSERT(BX_COUNTOF(descTextureCube) == BX_COUNTOF(m_textureCube));

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textureCube); ++ii)
			{
				if (bgfx::isValid(m_textureCube[ii]))
				{
					float mtx[16];
					bx::mtxSRT(mtx, 0.65f, 0.65f, 0.65f, time, time*0.37f, 0.0f, -2.5f +ii*1.8f, 0.0f, 0.0f);

					// Set model matrix for rendering.
					bgfx::setTransform(mtx);

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(0,  m_vbh);
					bgfx::setIndexBuffer(m_ibh);

					// Bind texture.
					bgfx::setTexture(0, s_texCube, m_textureCube[ii]);

					// Set render states.
					bgfx::setState(BGFX_STATE_DEFAULT);

					// Submit primitive for rendering to view 0.
					bgfx::submit(0, m_program);

					ImGuiDescription(mtx[12], mtx[13], mtx[14], worldToScreen, descTextureCube[ii]);
				}
			}

			// Set view and projection matrix for view 1.
			const uint32_t numColumns = BX_COUNTOF(m_textures) / 2;

			const float aspectRatio = float(m_height)/float(m_width);
			const float margin = 0.7f;
			const float sizeX = 0.5f * numColumns * 2.3f + margin;
			const float sizeY = sizeX * aspectRatio;

			const bgfx::Caps* caps = bgfx::getCaps();
			bx::mtxOrtho(proj, -sizeX, sizeX, sizeY, -sizeY, 0.0f, 1000.0f, 0.0f, caps->homogeneousDepth);
			bgfx::setViewTransform(1, NULL, proj);

			bx::mtxMul(worldToScreen, proj, projToScreen);

			float mtx[16];
			bx::mtxTranslate(mtx, -sizeX + margin + 1.0f, 1.9f, 0.0f);

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setIndexBuffer(m_ibh);

			// Bind texture.
			bgfx::setTexture(0, s_texColor, m_texture2d);

			// Set render states.
			bgfx::setState(BGFX_STATE_DEFAULT);

			// Submit primitive for rendering to view 1.
			bgfx::submit(1, m_programCmp);

			ImGuiDescription(mtx[12], mtx[13], mtx[14], worldToScreen, "updateTexture2D");

			const float xpos = -sizeX + margin + 1.0f;

			static const char* descTextures[] =
			{
				"create\nbc1",
				"create\nbc2",
				"create\nbc3",
				"create\netc1",
				"create\netc2",
				"create\nptc12",
				"create\nptc14",
				"create\nptc22",
				"create\nptc24",
				"create\natc",
				"create\natci",
				"create\natce",
				"update\nbc1",
				"update\nbc2",
				"update\nbc3",
				"update\netc1",
				"update\netc2",
				"update\nptc12",
				"update\nptc14",
				"update\nptc22",
				"update\nptc24",
				"update\natc",
				"update\natci",
				"update\natce",
			};
			BX_STATIC_ASSERT(BX_COUNTOF(descTextures)  == BX_COUNTOF(m_textures));

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_textures); ++ii)
			{
				bx::mtxTranslate(mtx, xpos + (ii%numColumns) * 2.3f, sizeY - margin - 2.8f + (ii/numColumns) * 2.3f, 0.0f);

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setIndexBuffer(m_ibh, 0, 6);

				// Bind texture.
				bgfx::setTexture(0, s_texColor, m_textures[ii]);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 1.
				bgfx::submit(1, m_programCmp);

				ImGuiDescription(mtx[12], mtx[13], mtx[14], worldToScreen, descTextures[ii]);
			}

			static const char* descTextures3d[] =
			{
					"Tex3D R8",
					"Tex3D R16F",
					"Tex3D R32F",
			};
			BX_STATIC_ASSERT(BX_COUNTOF(descTextures3d) == BX_COUNTOF(m_textures3d));

			for (uint32_t ii = 0; ii < m_numTextures3d; ++ii)
			{
				bx::mtxTranslate(mtx, xpos + (ii+(numColumns - m_numTextures3d)*0.5f)*2.3f, -sizeY + margin + 1.0f, 0.0f);

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setIndexBuffer(m_ibh, 0, 6);

				// Bind texture.
				bgfx::setTexture(0, s_texColor, m_textures3d[ii]);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 1.
				bgfx::submit(1, m_program3d);

				ImGuiDescription(mtx[12], mtx[13], mtx[14], worldToScreen, descTextures3d[ii]);
			}

			static const char* descSampler[] =
			{
					"U_CLAMP\nV_CLAMP",
					"U_CLAMP\nV_WRAP",
					"U_WRAP\nV_CLAMP",
					"U_BORDER\nV_BORDER",
					"U_WRAP\nV_WRAP",
			};

			for (uint32_t ii = 0; ii < 5; ++ii)
			{
				bx::mtxTranslate(mtx, sizeX - margin - 1.0f, -sizeY + margin + 1.0f + ii*2.1f, 0.0f);

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(0, m_vbh, 24, 4);
				bgfx::setIndexBuffer(m_ibh, 0, 6);

				// Bind texture.
				bgfx::setTexture(0, s_texColor, m_textures[ii]);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 1.
				bgfx::submit(1, m_programCmp);

				ImGuiDescription(mtx[12], mtx[13], mtx[14], worldToScreen, descSampler[ii]);
			}

			imguiEndFrame();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	uint8_t* m_texture2dData;
	uint32_t m_numTextures3d;
	bool m_texture3DSupported;
	bool m_blitSupported;
	bool m_computeSupported;
	bool m_showDescriptions;

	std::list<PackCube> m_quads;
	RectPackCubeT<256> m_cube;
	int64_t m_updateTime;
	int64_t m_timeOffset;
	bx::RngMwc m_rng;

	uint32_t m_hit;
	uint32_t m_miss;

	uint8_t m_rr;
	uint8_t m_gg;
	uint8_t m_bb;

	bgfx::TextureHandle m_textures[24];
	bgfx::TextureHandle m_textures3d[3];
	bgfx::TextureHandle m_texture2d;
	bgfx::TextureHandle m_textureCube[4];
	bgfx::FrameBufferHandle m_textureCubeFaceFb[6];
	bgfx::IndexBufferHandle m_ibh;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::ProgramHandle m_program3d;
	bgfx::ProgramHandle m_programCmp;
	bgfx::ProgramHandle m_programCompute;
	bgfx::ProgramHandle m_program;
	bgfx::UniformHandle u_time;
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texCube;

};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleUpdate
	, "08-update"
	, "Updating textures."
	, "https://bkaradzic.github.io/bgfx/examples.html#update"
	);
