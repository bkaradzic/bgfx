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

struct PosNormalVertex
{
	float    m_x;
	float    m_y;
	float    m_z;
	uint32_t m_normal;
};

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
	void init(int _argc, char** _argv) BX_OVERRIDE
	{

		Args args(_argc, _argv);
		
		m_width = 1280;
		m_height = 720;
		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;
		
		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);
		
		bgfx::RendererType::Enum renderer = bgfx::getRendererType();
		m_flipV = false
		|| renderer == bgfx::RendererType::OpenGL
		|| renderer == bgfx::RendererType::OpenGLES
		;
		
		// Enable debug text.
		bgfx::setDebug(m_debug);
		
		// Uniforms.
		u_shadowMap = bgfx::createUniform("u_shadowMap", bgfx::UniformType::Int1);
		u_lightPos  = bgfx::createUniform("u_lightPos",  bgfx::UniformType::Vec4);
		u_lightMtx  = bgfx::createUniform("u_lightMtx",  bgfx::UniformType::Mat4);
		
		// When using GL clip space depth range [-1, 1] and packing depth into color buffer, we need to
		// adjust the depth range to be [0, 1] for writing to the color buffer
		u_depthScaleOffset = bgfx::createUniform("u_depthScaleOffset",  bgfx::UniformType::Vec4);
		m_depthScale = m_flipV ? 0.5f : 1.0f;
		m_depthOffset = m_flipV ? 0.5f : 0.0f;
		float depthScaleOffset[4] = {m_depthScale, m_depthOffset, 0.0f, 0.0f};
		bgfx::setUniform(u_depthScaleOffset, depthScaleOffset);
		
		// Vertex declarations.
		bgfx::VertexDecl PosNormalDecl;
		PosNormalDecl.begin()
		.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
		.end();
		
		// Meshes.
		m_bunny      = meshLoad("meshes/bunny.bin");
		m_cube       = meshLoad("meshes/cube.bin");
		m_hollowcube = meshLoad("meshes/hollowcube.bin");
		
		m_vbh = bgfx::createVertexBuffer(
										 bgfx::makeRef(s_hplaneVertices, sizeof(s_hplaneVertices) )
										 , PosNormalDecl
										 );
		
		m_ibh = bgfx::createIndexBuffer(
										bgfx::makeRef(s_planeIndices, sizeof(s_planeIndices) )
										);
		
		// Render targets.
		m_shadowMapSize = 512;
		
		// Get renderer capabilities info.
		const bgfx::Caps* caps = bgfx::getCaps();
		// Shadow samplers are supported at least partially supported if texture
		// compare less equal feature is supported.
		m_shadowSamplerSupported = 0 != (caps->supported & BGFX_CAPS_TEXTURE_COMPARE_LEQUAL);
		
		bgfx::TextureHandle shadowMapTexture;
		
		if (m_shadowSamplerSupported)
		{
			// Depth textures and shadow samplers are supported.
			m_progShadow = loadProgram("vs_sms_shadow", "fs_sms_shadow");
			m_progMesh   = loadProgram("vs_sms_mesh",   "fs_sms_mesh");
			
			shadowMapTexture = bgfx::createTexture2D(m_shadowMapSize, m_shadowMapSize, false, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT | BGFX_TEXTURE_COMPARE_LEQUAL);
			bgfx::TextureHandle fbtextures[] = { shadowMapTexture };
			m_shadowMapFB = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
		}
		else
		{
			// Depth textures and shadow samplers are not supported. Use float
			// depth packing into color buffer instead.
			m_progShadow = loadProgram("vs_sms_shadow_pd", "fs_sms_shadow_pd");
			m_progMesh   = loadProgram("vs_sms_mesh",      "fs_sms_mesh_pd");
			
			shadowMapTexture = bgfx::createTexture2D(m_shadowMapSize, m_shadowMapSize, false, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT);
			bgfx::TextureHandle fbtextures[] =
			{
				shadowMapTexture,
				bgfx::createTexture2D(m_shadowMapSize, m_shadowMapSize, false, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_WRITE_ONLY),
			};
			m_shadowMapFB = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
		}
		
		m_state[0] = meshStateCreate();
		m_state[0]->m_state = 0
		| BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		;
		m_state[0]->m_program = m_progShadow;
		m_state[0]->m_viewId  = RENDER_SHADOW_PASS_ID;
		m_state[0]->m_numTextures = 0;
		
		m_state[1] = meshStateCreate();
		m_state[1]->m_state = 0
		| BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		;
		m_state[1]->m_program = m_progMesh;
		m_state[1]->m_viewId  = RENDER_SCENE_PASS_ID;
		m_state[1]->m_numTextures = 1;
		m_state[1]->m_textures[0].m_flags = UINT32_MAX;
		m_state[1]->m_textures[0].m_stage = 0;
		m_state[1]->m_textures[0].m_sampler = u_shadowMap;
		m_state[1]->m_textures[0].m_texture = shadowMapTexture;
		
		// Set view and projection matrices.
		
		float eye[3] = { 0.0f, 30.0f, -60.0f };
		float at[3]  = { 0.0f,  5.0f,   0.0f };
		bx::mtxLookAt(m_view, eye, at);
		
		const float aspect = float(int32_t(m_width) ) / float(int32_t(m_height) );
		bx::mtxProj(m_proj, 60.0f, aspect, 0.1f, 1000.0f, bgfx::getCaps()->homogeneousDepth);
		
		// Time acumulators.
		m_timeAccumulatorLight = 0.0f;
		m_timeAccumulatorScene = 0.0f;
	}
	
	virtual int shutdown() BX_OVERRIDE
	{
		meshUnload(m_bunny);
		meshUnload(m_cube);
		meshUnload(m_hollowcube);
		
		meshStateDestroy(m_state[0]);
		meshStateDestroy(m_state[1]);
		
		bgfx::destroyVertexBuffer(m_vbh);
		bgfx::destroyIndexBuffer(m_ibh);
		
		bgfx::destroyProgram(m_progShadow);
		bgfx::destroyProgram(m_progMesh);
		
		bgfx::destroyFrameBuffer(m_shadowMapFB);
		
		bgfx::destroyUniform(u_shadowMap);
		bgfx::destroyUniform(u_lightPos);
		bgfx::destroyUniform(u_lightMtx);
		bgfx::destroyUniform(u_depthScaleOffset);
		
		// Shutdown bgfx.
		bgfx::shutdown();
		
		return 0;
	}

	bool update() BX_OVERRIDE
	{
		while (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
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
			m_timeAccumulatorLight += deltaTime;
			m_timeAccumulatorScene += deltaTime;
			
			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/15-shadowmaps-simple");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Shadow maps example (technique: %s).", m_shadowSamplerSupported ? "depth texture and shadow samplers" : "shadow depth packed into color texture");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);
			
			// Setup lights.
			float lightPos[4];
			lightPos[0] = -bx::fcos(m_timeAccumulatorLight);
			lightPos[1] = -1.0f;
			lightPos[2] = -bx::fsin(m_timeAccumulatorLight);
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
					   , 0.0f, bx::kPi - m_timeAccumulatorScene, 0.0f
					   , 15.0f, 5.0f, 0.0f
					   );
			
			float mtxHollowcube[16];
			bx::mtxSRT(mtxHollowcube
					   , 2.5f, 2.5f, 2.5f
					   , 0.0f, 1.56f - m_timeAccumulatorScene, 0.0f
					   , 0.0f, 10.0f, 0.0f
					   );
			
			float mtxCube[16];
			bx::mtxSRT(mtxCube
					   , 2.5f, 2.5f, 2.5f
					   , 0.0f, 1.56f - m_timeAccumulatorScene, 0.0f
					   , -15.0f, 5.0f, 0.0f
					   );
			
			// Define matrices.
			float lightView[16];
			float lightProj[16];
			
			float eye[3] = { -lightPos[0], -lightPos[1], -lightPos[2] };
			float at[3]  = { 0.0f,  0.0f,   0.0f };
			
			bx::mtxLookAt(lightView, eye, at);
			
			const float area = 30.0f;
			bx::mtxOrtho(lightProj, -area, area, -area, area, -100.0f, 100.0f, 0.0f, m_flipV);
			
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
			
			const float sy = m_flipV ? 0.5f : -0.5f;
			const float mtxCrop[16] =
			{
				0.5f, 0.0f, 0.0f, 0.0f,
				0.0f,   sy, 0.0f, 0.0f,
				0.0f, 0.0f, m_depthScale, 0.0f,
				0.5f, 0.5f, m_depthOffset, 1.0f,
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
	
	bool m_flipV;
	
	bgfx::UniformHandle u_shadowMap;
	bgfx::UniformHandle u_lightPos;
	bgfx::UniformHandle u_lightMtx;
	
	bgfx::UniformHandle u_depthScaleOffset;
	float m_depthScale;
	float m_depthOffset;
	
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
	
	float m_timeAccumulatorLight;
	float m_timeAccumulatorScene;
	
	float m_view[16];
	float m_proj[16];

};

ENTRY_IMPLEMENT_MAIN(ExampleShadowmapsSimple);

