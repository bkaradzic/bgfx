/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <string>
#include <vector>
#include <algorithm>

#include "common.h"

#include <bgfx/bgfx.h>
#include <bx/timer.h>
#include <bx/readerwriter.h>
#include <bx/math.h>
#include "entry/entry.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

#define RENDER_SHADOW_PASS_ID 0
#define RENDER_SCENE_PASS_ID  1

struct PosNormalVertex
{
	float    m_x;
	float    m_y;
	float    m_z;
	uint32_t m_normal;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,   4, bgfx::AttribType::Uint8, true, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosNormalVertex::ms_decl;

static PosNormalVertex s_hplaneVertices[] =
{
	{ -1.0f, 0.0f,  1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f) },
	{  1.0f, 0.0f,  1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f) },
	{ -1.0f, 0.0f, -1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f) },
	{  1.0f, 0.0f, -1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f) },
};

static const uint16_t s_planeIndices[] =
{
	0, 1, 2,
	1, 3, 2,
};

class ExampleShadowmapsSimple : public entry::AppI
{
public:
	ExampleShadowmapsSimple(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug = BGFX_DEBUG_NONE;
		m_reset = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Uniforms.
		s_shadowMap = bgfx::createUniform("s_shadowMap", bgfx::UniformType::Int1);
		u_lightPos  = bgfx::createUniform("u_lightPos",  bgfx::UniformType::Vec4);
		u_lightMtx  = bgfx::createUniform("u_lightMtx",  bgfx::UniformType::Mat4);

		// When using GL clip space depth range [-1, 1] and packing depth into color buffer, we need to
		// adjust the depth range to be [0, 1] for writing to the color buffer
		u_depthScaleOffset = bgfx::createUniform("u_depthScaleOffset",  bgfx::UniformType::Vec4);

		// Get renderer capabilities info.
		const bgfx::Caps* caps = bgfx::getCaps();

		float depthScaleOffset[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
		if (caps->homogeneousDepth)
		{
			depthScaleOffset[0] = 0.5f;
			depthScaleOffset[1] = 0.5f;
		}
		bgfx::setUniform(u_depthScaleOffset, depthScaleOffset);

		// Create vertex stream declaration.
		PosNormalVertex::init();

		// Meshes.
		m_bunny      = meshLoad("meshes/bunny.bin");
		m_cube       = meshLoad("meshes/cube.bin");
		m_hollowcube = meshLoad("meshes/hollowcube.bin");

		m_vbh = bgfx::createVertexBuffer(
			  bgfx::makeRef(s_hplaneVertices, sizeof(s_hplaneVertices) )
			, PosNormalVertex::ms_decl
			);

		m_ibh = bgfx::createIndexBuffer(
			  bgfx::makeRef(s_planeIndices, sizeof(s_planeIndices) )
			);

		// Render targets.
		m_shadowMapSize = 512;

		// Shadow samplers are supported at least partially supported if texture
		// compare less equal feature is supported.
		m_shadowSamplerSupported = 0 != (caps->supported & BGFX_CAPS_TEXTURE_COMPARE_LEQUAL);

		bgfx::TextureHandle shadowMapTexture;

		if (m_shadowSamplerSupported)
		{
			// Depth textures and shadow samplers are supported.
			m_progShadow = loadProgram("vs_sms_shadow", "fs_sms_shadow");
			m_progMesh   = loadProgram("vs_sms_mesh",   "fs_sms_mesh");

			bgfx::TextureHandle fbtextures[] =
			{
				bgfx::createTexture2D(
					  m_shadowMapSize
					, m_shadowMapSize
					, false
					, 1
					, bgfx::TextureFormat::D16
					, BGFX_TEXTURE_RT | BGFX_SAMPLER_COMPARE_LEQUAL
					),
			};
			shadowMapTexture = fbtextures[0];
			m_shadowMapFB = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
		}
		else
		{
			// Depth textures and shadow samplers are not supported. Use float
			// depth packing into color buffer instead.
			m_progShadow = loadProgram("vs_sms_shadow_pd", "fs_sms_shadow_pd");
			m_progMesh   = loadProgram("vs_sms_mesh",      "fs_sms_mesh_pd");

			bgfx::TextureHandle fbtextures[] =
			{
				bgfx::createTexture2D(
					  m_shadowMapSize
					, m_shadowMapSize
					, false
					, 1
					, bgfx::TextureFormat::BGRA8
					, BGFX_TEXTURE_RT
					),
				bgfx::createTexture2D(
					  m_shadowMapSize
					, m_shadowMapSize
					, false
					, 1
					, bgfx::TextureFormat::D16
					, BGFX_TEXTURE_RT_WRITE_ONLY
					),
			};
			shadowMapTexture = fbtextures[0];
			m_shadowMapFB = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
		}

		m_state[0] = meshStateCreate();
		m_state[0]->m_state = 0
			| (m_shadowSamplerSupported ? 0 : BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A)
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			| BGFX_STATE_MSAA
			;
		m_state[0]->m_program = m_progShadow;
		m_state[0]->m_viewId  = RENDER_SHADOW_PASS_ID;
		m_state[0]->m_numTextures = 0;

		m_state[1] = meshStateCreate();
		m_state[1]->m_state = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			| BGFX_STATE_MSAA
			;
		m_state[1]->m_program = m_progMesh;
		m_state[1]->m_viewId  = RENDER_SCENE_PASS_ID;
		m_state[1]->m_numTextures = 1;
		m_state[1]->m_textures[0].m_flags = UINT32_MAX;
		m_state[1]->m_textures[0].m_stage = 0;
		m_state[1]->m_textures[0].m_sampler = s_shadowMap;
		m_state[1]->m_textures[0].m_texture = shadowMapTexture;

		// Set view and projection matrices.

		float eye[3] = { 0.0f, 30.0f, -60.0f };
		float at[3]  = { 0.0f,  5.0f,   0.0f };
		bx::mtxLookAt(m_view, eye, at);

		const float aspect = float(int32_t(m_width) ) / float(int32_t(m_height) );
		bx::mtxProj(m_proj, 60.0f, aspect, 0.1f, 1000.0f, bgfx::getCaps()->homogeneousDepth);

		m_timeOffset = bx::getHPCounter();

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		meshUnload(m_bunny);
		meshUnload(m_cube);
		meshUnload(m_hollowcube);

		meshStateDestroy(m_state[0]);
		meshStateDestroy(m_state[1]);

		bgfx::destroy(m_vbh);
		bgfx::destroy(m_ibh);

		bgfx::destroy(m_progShadow);
		bgfx::destroy(m_progMesh);

		bgfx::destroy(m_shadowMapFB);

		bgfx::destroy(s_shadowMap);
		bgfx::destroy(u_lightPos);
		bgfx::destroy(u_lightMtx);
		bgfx::destroy(u_depthScaleOffset);

		// Shutdown bgfx.
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

			int64_t now = bx::getHPCounter();
			const double freq = double(bx::getHPFrequency() );
			float time = float( (now-m_timeOffset)/freq);

			// Setup lights.
			float lightPos[4];
			lightPos[0] = -bx::cos(time);
			lightPos[1] = -1.0f;
			lightPos[2] = -bx::sin(time);
			lightPos[3] = 0.0f;

			bgfx::setUniform(u_lightPos, lightPos);

			// Setup instance matrices.
			float mtxFloor[16];
			bx::mtxSRT(mtxFloor
				, 30.0f, 30.0f, 30.0f
				, 0.0f, 0.0f, 0.0f
				, 0.0f, 0.0f, 0.0f
				);

			float mtxBunny[16];
			bx::mtxSRT(mtxBunny
				, 5.0f, 5.0f, 5.0f
				, 0.0f, bx::kPi - time, 0.0f
				, 15.0f, 5.0f, 0.0f
				);

			float mtxHollowcube[16];
			bx::mtxSRT(mtxHollowcube
				, 2.5f, 2.5f, 2.5f
				, 0.0f, 1.56f - time, 0.0f
				, 0.0f, 10.0f, 0.0f
				);

			float mtxCube[16];
			bx::mtxSRT(mtxCube
				, 2.5f, 2.5f, 2.5f
				, 0.0f, 1.56f - time, 0.0f
				, -15.0f, 5.0f, 0.0f
				);

			// Define matrices.
			float lightView[16];
			float lightProj[16];

			float eye[3] = { -lightPos[0], -lightPos[1], -lightPos[2] };
			float at[3]  = { 0.0f,  0.0f,   0.0f };

			bx::mtxLookAt(lightView, eye, at);

			const bgfx::Caps* caps = bgfx::getCaps();
			const float area = 30.0f;
			bx::mtxOrtho(lightProj, -area, area, -area, area, -100.0f, 100.0f, 0.0f, caps->homogeneousDepth);

			bgfx::setViewRect(RENDER_SHADOW_PASS_ID, 0, 0, m_shadowMapSize, m_shadowMapSize);
			bgfx::setViewFrameBuffer(RENDER_SHADOW_PASS_ID, m_shadowMapFB);
			bgfx::setViewTransform(RENDER_SHADOW_PASS_ID, lightView, lightProj);

			bgfx::setViewRect(RENDER_SCENE_PASS_ID, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			bgfx::setViewTransform(RENDER_SCENE_PASS_ID, m_view, m_proj);

			// Clear backbuffer and shadowmap framebuffer at beginning.
			bgfx::setViewClear(RENDER_SHADOW_PASS_ID
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x303030ff, 1.0f, 0
				);

			bgfx::setViewClear(RENDER_SCENE_PASS_ID
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x303030ff, 1.0f, 0
				);

			// Render.
			float mtxShadow[16];
			float lightMtx[16];

			const float sy = caps->originBottomLeft ? 0.5f : -0.5f;
			const float sz = caps->homogeneousDepth ? 0.5f :  1.0f;
			const float tz = caps->homogeneousDepth ? 0.5f :  0.0f;
			const float mtxCrop[16] =
			{
				0.5f, 0.0f, 0.0f, 0.0f,
				0.0f,   sy, 0.0f, 0.0f,
				0.0f, 0.0f, sz,   0.0f,
				0.5f, 0.5f, tz,   1.0f,
			};

			float mtxTmp[16];
			bx::mtxMul(mtxTmp,    lightProj, mtxCrop);
			bx::mtxMul(mtxShadow, lightView, mtxTmp);

			// Floor.
			bx::mtxMul(lightMtx, mtxFloor, mtxShadow);
			uint32_t cached = bgfx::setTransform(mtxFloor);
			for (uint32_t pass = 0; pass < 2; ++pass)
			{
				const MeshState& st = *m_state[pass];
				bgfx::setTransform(cached);
				for (uint8_t tex = 0; tex < st.m_numTextures; ++tex)
				{
					const MeshState::Texture& texture = st.m_textures[tex];
					bgfx::setTexture(texture.m_stage
						, texture.m_sampler
						, texture.m_texture
						, texture.m_flags
						);
				}
				bgfx::setUniform(u_lightMtx, lightMtx);
				bgfx::setIndexBuffer(m_ibh);
				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setState(st.m_state);
				bgfx::submit(st.m_viewId, st.m_program);
			}

			// Bunny.
			bx::mtxMul(lightMtx, mtxBunny, mtxShadow);
			bgfx::setUniform(u_lightMtx, lightMtx);
			meshSubmit(m_bunny, &m_state[0], 1, mtxBunny);
			bgfx::setUniform(u_lightMtx, lightMtx);
			meshSubmit(m_bunny, &m_state[1], 1, mtxBunny);

			// Hollow cube.
			bx::mtxMul(lightMtx, mtxHollowcube, mtxShadow);
			bgfx::setUniform(u_lightMtx, lightMtx);
			meshSubmit(m_hollowcube, &m_state[0], 1, mtxHollowcube);
			bgfx::setUniform(u_lightMtx, lightMtx);
			meshSubmit(m_hollowcube, &m_state[1], 1, mtxHollowcube);

			// Cube.
			bx::mtxMul(lightMtx, mtxCube, mtxShadow);
			bgfx::setUniform(u_lightMtx, lightMtx);
			meshSubmit(m_cube, &m_state[0], 1, mtxCube);
			bgfx::setUniform(u_lightMtx, lightMtx);
			meshSubmit(m_cube, &m_state[1], 1, mtxCube);

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

	bgfx::UniformHandle s_shadowMap;
	bgfx::UniformHandle u_lightPos;
	bgfx::UniformHandle u_lightMtx;

	bgfx::UniformHandle u_depthScaleOffset;

	Mesh* m_bunny;
	Mesh* m_cube;
	Mesh* m_hollowcube;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;

	uint16_t m_shadowMapSize;

	bgfx::ProgramHandle m_progShadow;
	bgfx::ProgramHandle m_progMesh;
	bgfx::FrameBufferHandle m_shadowMapFB;

	bool m_shadowSamplerSupported;

	MeshState* m_state[2];

	float m_view[16];
	float m_proj[16];

	int64_t m_timeOffset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleShadowmapsSimple, "15-shadowmaps-simple", "Shadow maps example");
