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
#include <bx/fpumath.h>
#include "entry/entry.h"
#include "bgfx_utils.h"

#define RENDER_SHADOW_PASS_ID 0
#define RENDER_SCENE_PASS_ID  1

uint32_t packUint32(uint8_t _x, uint8_t _y, uint8_t _z, uint8_t _w)
{
	union
	{
		uint32_t ui32;
		uint8_t arr[4];
	} un;

	un.arr[0] = _x;
	un.arr[1] = _y;
	un.arr[2] = _z;
	un.arr[3] = _w;

	return un.ui32;
}

uint32_t packF4u(float _x, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f)
{
	const uint8_t xx = uint8_t(_x*127.0f + 128.0f);
	const uint8_t yy = uint8_t(_y*127.0f + 128.0f);
	const uint8_t zz = uint8_t(_z*127.0f + 128.0f);
	const uint8_t ww = uint8_t(_w*127.0f + 128.0f);
	return packUint32(xx, yy, zz, ww);
}

struct PosNormalVertex
{
	float    m_x;
	float    m_y;
	float    m_z;
	uint32_t m_normal;
};

static PosNormalVertex s_hplaneVertices[] =
{
	{ -1.0f, 0.0f,  1.0f, packF4u(0.0f, 1.0f, 0.0f) },
	{  1.0f, 0.0f,  1.0f, packF4u(0.0f, 1.0f, 0.0f) },
	{ -1.0f, 0.0f, -1.0f, packF4u(0.0f, 1.0f, 0.0f) },
	{  1.0f, 0.0f, -1.0f, packF4u(0.0f, 1.0f, 0.0f) },
};

static const uint16_t s_planeIndices[] =
{
	0, 1, 2,
	1, 3, 2,
};

int _main_(int _argc, char** _argv)
{
	Args args(_argc, _argv);

	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init(args.m_type, args.m_pciId);
	bgfx::reset(width, height, reset);

	bgfx::RendererType::Enum renderer = bgfx::getRendererType();
	bool flipV = false
		|| renderer == bgfx::RendererType::OpenGL
		|| renderer == bgfx::RendererType::OpenGLES
		;

	// Enable debug text.
	bgfx::setDebug(debug);

	// Uniforms.
	bgfx::UniformHandle u_shadowMap = bgfx::createUniform("u_shadowMap", bgfx::UniformType::Int1);
	bgfx::UniformHandle u_lightPos  = bgfx::createUniform("u_lightPos",  bgfx::UniformType::Vec4);
	bgfx::UniformHandle u_lightMtx  = bgfx::createUniform("u_lightMtx",  bgfx::UniformType::Mat4);
	// When using GL clip space depth range [-1, 1] and packing depth into color buffer, we need to
	// adjust the depth range to be [0, 1] for writing to the color buffer
	bgfx::UniformHandle u_depthScaleOffset = bgfx::createUniform("u_depthScaleOffset",  bgfx::UniformType::Vec4);
	const float depthScale = flipV ? 0.5f : 1.0f;
	const float depthOffset = flipV ? 0.5f : 0.0f;
	float depthScaleOffset[4] = {depthScale, depthOffset, 0.0f, 0.0f};
	bgfx::setUniform(u_depthScaleOffset, depthScaleOffset);

	// Vertex declarations.
	bgfx::VertexDecl PosNormalDecl;
	PosNormalDecl.begin()
		.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
		.end();

	// Meshes.
	Mesh* bunny      = meshLoad("meshes/bunny.bin");
	Mesh* cube       = meshLoad("meshes/cube.bin");
	Mesh* hollowcube = meshLoad("meshes/hollowcube.bin");

	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
			  bgfx::makeRef(s_hplaneVertices, sizeof(s_hplaneVertices) )
			, PosNormalDecl
			);

	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(
			bgfx::makeRef(s_planeIndices, sizeof(s_planeIndices) )
			);

	// Render targets.
	uint16_t shadowMapSize = 512;

	// Get renderer capabilities info.
	const bgfx::Caps* caps = bgfx::getCaps();
	// Shadow samplers are supported at least partially supported if texture
	// compare less equal feature is supported.
	bool shadowSamplerSupported = 0 != (caps->supported & BGFX_CAPS_TEXTURE_COMPARE_LEQUAL);

	bgfx::ProgramHandle progShadow;
	bgfx::ProgramHandle progMesh;
	bgfx::TextureHandle shadowMapTexture;
	bgfx::FrameBufferHandle shadowMapFB;

	if (shadowSamplerSupported)
	{
		// Depth textures and shadow samplers are supported.
		progShadow = loadProgram("vs_sms_shadow", "fs_sms_shadow");
		progMesh   = loadProgram("vs_sms_mesh",   "fs_sms_mesh");

		shadowMapTexture = bgfx::createTexture2D(shadowMapSize, shadowMapSize, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT | BGFX_TEXTURE_COMPARE_LEQUAL);
		bgfx::TextureHandle fbtextures[] = { shadowMapTexture };
		shadowMapFB = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
	}
	else
	{
		// Depth textures and shadow samplers are not supported. Use float
		// depth packing into color buffer instead.
		progShadow = loadProgram("vs_sms_shadow_pd", "fs_sms_shadow_pd");
		progMesh   = loadProgram("vs_sms_mesh",      "fs_sms_mesh_pd");

		shadowMapTexture = bgfx::createTexture2D(shadowMapSize, shadowMapSize, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT);
		bgfx::TextureHandle fbtextures[] =
		{
			shadowMapTexture,
			bgfx::createTexture2D(shadowMapSize, shadowMapSize, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_WRITE_ONLY),
		};
		shadowMapFB = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
	}

	MeshState* state[2];
	state[0] = meshStateCreate();
	state[0]->m_state = 0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_WRITE
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_CULL_CCW
				| BGFX_STATE_MSAA
				;
	state[0]->m_program = progShadow;
	state[0]->m_viewId  = RENDER_SHADOW_PASS_ID;
	state[0]->m_numTextures = 0;

	state[1] = meshStateCreate();
	state[1]->m_state = 0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| BGFX_STATE_DEPTH_WRITE
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_CULL_CCW
				| BGFX_STATE_MSAA
				;
	state[1]->m_program = progMesh;
	state[1]->m_viewId  = RENDER_SCENE_PASS_ID;
	state[1]->m_numTextures = 1;
	state[1]->m_textures[0].m_flags = UINT32_MAX;
	state[1]->m_textures[0].m_stage = 0;
	state[1]->m_textures[0].m_sampler = u_shadowMap;
	state[1]->m_textures[0].m_texture = shadowMapTexture;

	// Set view and projection matrices.
	float view[16];
	float proj[16];

	float eye[3] = { 0.0f, 30.0f, -60.0f };
	float at[3]  = { 0.0f,  5.0f,   0.0f };
	bx::mtxLookAt(view, eye, at);

	const float aspect = float(int32_t(width) ) / float(int32_t(height) );
	bx::mtxProj(proj, 60.0f, aspect, 0.1f, 1000.0f, flipV);

	// Time acumulators.
	float timeAccumulatorLight = 0.0f;
	float timeAccumulatorScene = 0.0f;

	entry::MouseState mouseState;
	while (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		// Time.
		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;
		const float deltaTime = float(frameTime/freq);

		// Update time accumulators.
		timeAccumulatorLight += deltaTime;
		timeAccumulatorScene += deltaTime;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/15-shadowmaps-simple");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Shadow maps example (technique: %s).", shadowSamplerSupported ? "depth texture and shadow samplers" : "shadow depth packed into color texture");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Setup lights.
		float lightPos[4];
		lightPos[0] = -cosf(timeAccumulatorLight);
		lightPos[1] = -1.0f;
		lightPos[2] = -sinf(timeAccumulatorLight);
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
			, 0.0f, bx::pi - timeAccumulatorScene, 0.0f
			, 15.0f, 5.0f, 0.0f
			);

		float mtxHollowcube[16];
		bx::mtxSRT(mtxHollowcube
			, 2.5f, 2.5f, 2.5f
			, 0.0f, 1.56f - timeAccumulatorScene, 0.0f
			, 0.0f, 10.0f, 0.0f
			);

		float mtxCube[16];
		bx::mtxSRT(mtxCube
			, 2.5f, 2.5f, 2.5f
			, 0.0f, 1.56f - timeAccumulatorScene, 0.0f
			, -15.0f, 5.0f, 0.0f
			);

		// Define matrices.
		float lightView[16];
		float lightProj[16];

		eye[0] = -lightPos[0];
		eye[1] = -lightPos[1];
		eye[2] = -lightPos[2];

		at[0] = 0.0f;
		at[1] = 0.0f;
		at[2] = 0.0f;

		bx::mtxLookAt(lightView, eye, at);

		const float area = 30.0f;
		bx::mtxOrtho(lightProj, -area, area, -area, area, -100.0f, 100.0f, 0.0f, flipV);

		bgfx::setViewRect(RENDER_SHADOW_PASS_ID, 0, 0, shadowMapSize, shadowMapSize);
		bgfx::setViewFrameBuffer(RENDER_SHADOW_PASS_ID, shadowMapFB);
		bgfx::setViewTransform(RENDER_SHADOW_PASS_ID, lightView, lightProj);

		bgfx::setViewRect(RENDER_SCENE_PASS_ID, 0, 0, width, height);
		bgfx::setViewTransform(RENDER_SCENE_PASS_ID, view, proj);

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

		const float sy = flipV ? 0.5f : -0.5f;
		const float mtxCrop[16] =
		{
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f,   sy, 0.0f, 0.0f,
			0.0f, 0.0f, depthScale, 0.0f,
			0.5f, 0.5f, depthOffset, 1.0f,
		};

		float mtxTmp[16];
		bx::mtxMul(mtxTmp,    lightProj, mtxCrop);
		bx::mtxMul(mtxShadow, lightView, mtxTmp);

		// Floor.
		bx::mtxMul(lightMtx, mtxFloor, mtxShadow);
		uint32_t cached = bgfx::setTransform(mtxFloor);
		for (uint32_t pass = 0; pass < 2; ++pass)
		{
			const MeshState& st = *state[pass];
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
			bgfx::setIndexBuffer(ibh);
			bgfx::setVertexBuffer(vbh);
			bgfx::setState(st.m_state);
			bgfx::submit(st.m_viewId, st.m_program);
		}

		// Bunny.
		bx::mtxMul(lightMtx, mtxBunny, mtxShadow);
		bgfx::setUniform(u_lightMtx, lightMtx);
		meshSubmit(bunny, &state[0], 1, mtxBunny);
		bgfx::setUniform(u_lightMtx, lightMtx);
		meshSubmit(bunny, &state[1], 1, mtxBunny);

		// Hollow cube.
		bx::mtxMul(lightMtx, mtxHollowcube, mtxShadow);
		bgfx::setUniform(u_lightMtx, lightMtx);
		meshSubmit(hollowcube, &state[0], 1, mtxHollowcube);
		bgfx::setUniform(u_lightMtx, lightMtx);
		meshSubmit(hollowcube, &state[1], 1, mtxHollowcube);

		// Cube.
		bx::mtxMul(lightMtx, mtxCube, mtxShadow);
		bgfx::setUniform(u_lightMtx, lightMtx);
		meshSubmit(cube, &state[0], 1, mtxCube);
		bgfx::setUniform(u_lightMtx, lightMtx);
		meshSubmit(cube, &state[1], 1, mtxCube);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	meshUnload(bunny);
	meshUnload(cube);
	meshUnload(hollowcube);

	meshStateDestroy(state[0]);
	meshStateDestroy(state[1]);

	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyIndexBuffer(ibh);

	bgfx::destroyProgram(progShadow);
	bgfx::destroyProgram(progMesh);

	bgfx::destroyFrameBuffer(shadowMapFB);

	bgfx::destroyUniform(u_shadowMap);
	bgfx::destroyUniform(u_lightPos);
	bgfx::destroyUniform(u_lightMtx);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
