/*
 * Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"

namespace
{

constexpr float kWorldSize = 100.0f; // (km)
constexpr float kAmplitude = 18.0f;  // (km)

struct PosNormalVertex
{
	float m_x, m_y, m_z;
	float m_nx, m_ny, m_nz;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,   3, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosNormalVertex::ms_layout;

enum : bgfx::ViewId
{
	kViewTerrain = 0,
};

class ExampleSky2 : public entry::AppI
{
public:
	ExampleSky2(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
		, m_terrain_vbh(BGFX_INVALID_HANDLE)
		, m_terrain_ibh(BGFX_INVALID_HANDLE)
		, m_gridW(0)
		, m_gridH(0)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.platformData.nwh  = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.platformData.ndt  = entry::getNativeDisplayHandle();
		init.platformData.type = entry::getNativeWindowHandleType();
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		bgfx::setDebug(m_debug);

		PosNormalVertex::init();

		m_terrainProgram = loadProgram("vs_sky2", "fs_sky2");

		s_grass = bgfx::createUniform("s_grass", bgfx::UniformType::Sampler);
		s_rock  = bgfx::createUniform("s_rock",  bgfx::UniformType::Sampler);

		// BC1 with mip chains
		m_grassTex = loadTexture("textures/terrain_grass_1k_diff.dds");
		m_rockTex  = loadTexture("textures/terrain_rock_1k_diff.dds");

		buildTerrain();
		buildQuad();

		cameraCreate();
		cameraSetPosition({ -3.0f, 16.0f, 42.0f });
		cameraSetHorizontalAngle(bx::kPi - bx::kPi / 20.0f);
		cameraSetVerticalAngle(-bx::kPi / 12.0f);

		m_frameTime.reset();

		imguiCreate();
	}

	virtual int shutdown() override
	{
		cameraDestroy();
		imguiDestroy();

		bgfx::destroy(m_terrain_vbh);
		bgfx::destroy(m_terrain_ibh);

		bgfx::destroy(m_quad_vbh);
		bgfx::destroy(m_terrainProgram);

		bgfx::destroy(m_grassTex);
		bgfx::destroy(m_rockTex);

		bgfx::destroy(s_grass);
		bgfx::destroy(s_rock);

		bgfx::shutdown();

		return 0;
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

			imguiEndFrame();

			m_frameTime.frame();
			const float deltaTime = bx::toSeconds<float>(m_frameTime.getDeltaTime());

			cameraUpdate(deltaTime, m_mouseState, ImGui::MouseOverArea());

			float view[16];
			cameraGetViewMtx(view);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.02f, 400.0f, bgfx::getCaps()->homogeneousDepth);

			float viewProj[16];
			bx::mtxMul(viewProj, view, proj);

			bgfx::setViewClear(kViewTerrain, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);
			bgfx::setViewRect(kViewTerrain, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			bgfx::setViewTransform(kViewTerrain, view, proj);

			bgfx::setTexture(0, s_grass, m_grassTex);
			bgfx::setTexture(1, s_rock,  m_rockTex);

			bgfx::setVertexBuffer(0, m_terrain_vbh);
			bgfx::setIndexBuffer(m_terrain_ibh);

			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_WRITE_Z
				| BGFX_STATE_DEPTH_TEST_LESS
			);

			bgfx::submit(kViewTerrain, m_terrainProgram);

			bgfx::frame();

			return true;
		}

		return false;
	}

	void buildTerrain() {
		bimg::ImageContainer* image = imageLoad("textures/heightmap.exr", bgfx::TextureFormat::R32F);

		const uint32_t w = image->m_width;
		const uint32_t h = image->m_height;
		const float* src = (const float*)image->m_data;

		const float range = 1.0f; // heightmap must be exactly 0.0 - 1.0

		const float cellSize = kWorldSize / float(w - 1);
		const float originX  = -0.5f * kWorldSize;
		const float originZ  = -0.5f * cellSize * float(h - 1);

		const uint32_t numVertices = w * h;
		const bgfx::Memory* vbMem = bgfx::alloc(uint32_t(numVertices * sizeof(PosNormalVertex)));
		PosNormalVertex* vertices = (PosNormalVertex*)vbMem->data;

		for (uint32_t z = 0; z < h; ++z)
		{
			for (uint32_t x = 0; x < w; ++x)
			{
				const float height = (src[z * w + x]) / range * kAmplitude;
				PosNormalVertex& v = vertices[z * w + x];
				v.m_x = originX + float(x) * cellSize;
				v.m_y = height;
				v.m_z = originZ + float(z) * cellSize;
			}
		}

		bimg::imageFree(image);

		for (uint32_t z = 0; z < h; ++z)
		{
			for (uint32_t x = 0; x < w; ++x)
			{
				const uint32_t xl = (x > 0    ) ? x - 1 : x;
				const uint32_t xr = (x < w - 1) ? x + 1 : x;
				const uint32_t zd = (z > 0    ) ? z - 1 : z;
				const uint32_t zu = (z < h - 1) ? z + 1 : z;

				const float hL = vertices[z * w + xl].m_y;
				const float hR = vertices[z * w + xr].m_y;
				const float hD = vertices[zd * w + x].m_y;
				const float hU = vertices[zu * w + x].m_y;

				const float dx = hR - hL;
				const float dz = hU - hD;

				const bx::Vec3 normal = bx::normalize({ -dx, 2.0f * cellSize, -dz });

				PosNormalVertex& v = vertices[z*w + x];
				v.m_nx = normal.x;
				v.m_ny = normal.y;
				v.m_nz = normal.z;
			}
		}

		const uint32_t numIndices = (w - 1) * (h - 1) * 6;
		const bgfx::Memory* ibMem = bgfx::alloc(uint32_t(numIndices * sizeof(uint32_t)));
		uint32_t* indices = (uint32_t*)ibMem->data;

		uint32_t offset = 0;
		for (uint32_t z = 0; z < h - 1; ++z)
		{
			for (uint32_t x = 0; x < w - 1; ++x)
			{
				const uint32_t i0 = z * w + x;
				const uint32_t i1 = z * w + x + 1;
				const uint32_t i2 = (z + 1) * w + x;
				const uint32_t i3 = (z + 1) * w + x + 1;

				indices[offset++] = i0;
				indices[offset++] = i2;
				indices[offset++] = i1;

				indices[offset++] = i1;
				indices[offset++] = i2;
				indices[offset++] = i3;
			}
		}

		m_terrain_vbh = bgfx::createVertexBuffer(vbMem, PosNormalVertex::ms_layout);
		m_terrain_ibh = bgfx::createIndexBuffer(ibMem, BGFX_BUFFER_INDEX32);

		m_gridW = w;
		m_gridH = h;
	}

	void buildQuad() {
		const bgfx::Memory* mem = bgfx::alloc(6 * sizeof(float) );

		float* pos = (float*)mem->data;

		pos[0] = -1.0f; pos[1] = -1.0f;
		pos[2] =  3.0f; pos[3] = -1.0f;
		pos[4] = -1.0f; pos[5] =  3.0f;

		bgfx::VertexLayout layout;

		layout
			.begin()
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.end();

		m_quad_vbh = bgfx::createVertexBuffer(mem, layout);
	}

	entry::MouseState m_mouseState;

	bgfx::VertexBufferHandle m_quad_vbh;
	bgfx::VertexBufferHandle m_terrain_vbh;
	bgfx::IndexBufferHandle  m_terrain_ibh;

	bgfx::ProgramHandle m_terrainProgram;

	bgfx::TextureHandle m_grassTex;
	bgfx::TextureHandle m_rockTex;

	bgfx::UniformHandle s_grass;
	bgfx::UniformHandle s_rock;

	FrameTime m_frameTime;

	uint32_t m_gridW;
	uint32_t m_gridH;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleSky2
	, "53-sky2"
	, "Hillaire sky/atmosphere."
	, "https://bkaradzic.github.io/bgfx/examples.html#sky2"
	);
