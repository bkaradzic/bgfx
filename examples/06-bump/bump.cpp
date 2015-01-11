/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include "bgfx_utils.h"

struct PosNormalTangentTexcoordVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_normal;
	uint32_t m_tangent;
	int16_t m_u;
	int16_t m_v;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
			.add(bgfx::Attrib::Tangent,   4, bgfx::AttribType::Uint8, true, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosNormalTangentTexcoordVertex::ms_decl;

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

static PosNormalTangentTexcoordVertex s_cubeVertices[24] =
{
	{-1.0f,  1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0, 0x7fff, 0x7fff },
	{-1.0f,  1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0,      0,      0 },
	{ 1.0f,  1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0, 0x7fff, 0x7fff },
	{-1.0f,  1.0f,  1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f,  1.0f, -1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f,  1.0f, -1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{-1.0f, -1.0f,  1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0,      0,      0 },
	{ 1.0f, -1.0f,  1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f, -1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{ 1.0f, -1.0f,  1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0, 0x7fff,      0 },
	{ 1.0f, -1.0f, -1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f,  1.0f, -1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{-1.0f, -1.0f,  1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0,      0,      0 },
	{-1.0f,  1.0f,  1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0,      0, 0x7fff },
	{-1.0f,  1.0f, -1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0, 0x7fff, 0x7fff },
};

static const uint16_t s_cubeIndices[36] =
{
	 0,  2,  1,
	 1,  2,  3,
	 4,  5,  6,
	 5,  7,  6,

	 8, 10,  9,
	 9, 10, 11,
	12, 13, 14,
	13, 15, 14,

	16, 18, 17,
	17, 18, 19,
	20, 21, 22,
	21, 23, 22,
};

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

	// Get renderer capabilities info.
	const bgfx::Caps* caps = bgfx::getCaps();
	bool instancingSupported = 0 != (caps->supported & BGFX_CAPS_INSTANCING);

	// Create vertex stream declaration.
	PosNormalTangentTexcoordVertex::init();

	calcTangents(s_cubeVertices
		, BX_COUNTOF(s_cubeVertices)
		, PosNormalTangentTexcoordVertex::ms_decl
		, s_cubeIndices
		, BX_COUNTOF(s_cubeIndices)
		);

	// Create static vertex buffer.
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
		  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
		, PosNormalTangentTexcoordVertex::ms_decl
		);

	// Create static index buffer.
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

	// Create texture sampler uniforms.
	bgfx::UniformHandle u_texColor  = bgfx::createUniform("u_texColor",  bgfx::UniformType::Uniform1iv);
	bgfx::UniformHandle u_texNormal = bgfx::createUniform("u_texNormal", bgfx::UniformType::Uniform1iv);

	uint16_t numLights = 4;
	bgfx::UniformHandle u_lightPosRadius = bgfx::createUniform("u_lightPosRadius", bgfx::UniformType::Uniform4fv, numLights);
	bgfx::UniformHandle u_lightRgbInnerR = bgfx::createUniform("u_lightRgbInnerR", bgfx::UniformType::Uniform4fv, numLights);

	// Create program from shaders.
	bgfx::ProgramHandle program = loadProgram(instancingSupported ? "vs_bump_instanced" : "vs_bump", "fs_bump");

	// Load diffuse texture.
	bgfx::TextureHandle textureColor = loadTexture("fieldstone-rgba.dds");

	// Load normal texture.
	bgfx::TextureHandle textureNormal = loadTexture("fieldstone-n.dds");

	int64_t timeOffset = bx::getHPCounter();

	while (!entry::processEvents(width, height, debug, reset) )
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
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		float time = (float)( (now-timeOffset)/freq);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/06-bump");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Loading textures.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		float at[3]  = { 0.0f, 0.0f,  0.0f };
		float eye[3] = { 0.0f, 0.0f, -7.0f };
		
		// Set view and projection matrix for view 0.
		const bgfx::HMD* hmd = bgfx::getHMD();
		if (NULL != hmd)
		{
			float view[16];
			bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);

			float proj[16];
			bx::mtxProj(proj, hmd->eye[0].fov, 0.1f, 100.0f);

			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			//
			// Use HMD's width/height since HMD's internal frame buffer size
			// might be much larger than window size.
			bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
		}
		else
		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);
			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, width, height);
		}

		float lightPosRadius[4][4];
		for (uint32_t ii = 0; ii < numLights; ++ii)
		{
			lightPosRadius[ii][0] = sin( (time*(0.1f + ii*0.17f) + ii*bx::piHalf*1.37f ) )*3.0f;
			lightPosRadius[ii][1] = cos( (time*(0.2f + ii*0.29f) + ii*bx::piHalf*1.49f ) )*3.0f;
			lightPosRadius[ii][2] = -2.5f;
			lightPosRadius[ii][3] = 3.0f;
		}

		bgfx::setUniform(u_lightPosRadius, lightPosRadius, numLights);

		float lightRgbInnerR[4][4] =
		{
			{ 1.0f, 0.7f, 0.2f, 0.8f },
			{ 0.7f, 0.2f, 1.0f, 0.8f },
			{ 0.2f, 1.0f, 0.7f, 0.8f },
			{ 1.0f, 0.4f, 0.2f, 0.8f },
		};

		bgfx::setUniform(u_lightRgbInnerR, lightRgbInnerR, numLights);

		const uint16_t instanceStride = 64;
		const uint16_t numInstances = 3;

		if (instancingSupported)
		{
			// Write instance data for 3x3 cubes.
			for (uint32_t yy = 0; yy < 3; ++yy)
			{
				const bgfx::InstanceDataBuffer* idb = bgfx::allocInstanceDataBuffer(numInstances, instanceStride);
				if (NULL != idb)
				{
					uint8_t* data = idb->data;

					for (uint32_t xx = 0; xx < 3; ++xx)
					{
						float* mtx = (float*)data;
						bx::mtxRotateXY(mtx, time*0.023f + xx*0.21f, time*0.03f + yy*0.37f);
						mtx[12] = -3.0f + float(xx)*3.0f;
						mtx[13] = -3.0f + float(yy)*3.0f;
						mtx[14] = 0.0f;

						data += instanceStride;
					}

					// Set instance data buffer.
					bgfx::setInstanceDataBuffer(idb, numInstances);

					// Set vertex and fragment shaders.
					bgfx::setProgram(program);

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(vbh);
					bgfx::setIndexBuffer(ibh);

					// Bind textures.
					bgfx::setTexture(0, u_texColor, textureColor);
					bgfx::setTexture(1, u_texNormal, textureNormal);

					// Set render states.
					bgfx::setState(0
						| BGFX_STATE_RGB_WRITE
						| BGFX_STATE_ALPHA_WRITE
						| BGFX_STATE_DEPTH_WRITE
						| BGFX_STATE_DEPTH_TEST_LESS
						| BGFX_STATE_MSAA
						);

					// Submit primitive for rendering to view 0.
					bgfx::submit(0);
				}
			}
		}
		else
		{
			for (uint32_t yy = 0; yy < 3; ++yy)
			{
				for (uint32_t xx = 0; xx < 3; ++xx)
				{
					float mtx[16];
					bx::mtxRotateXY(mtx, time*0.023f + xx*0.21f, time*0.03f + yy*0.37f);
					mtx[12] = -3.0f + float(xx)*3.0f;
					mtx[13] = -3.0f + float(yy)*3.0f;
					mtx[14] = 0.0f;

					// Set transform for draw call.
					bgfx::setTransform(mtx);

					// Set vertex and fragment shaders.
					bgfx::setProgram(program);

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(vbh);
					bgfx::setIndexBuffer(ibh);

					// Bind textures.
					bgfx::setTexture(0, u_texColor, textureColor);
					bgfx::setTexture(1, u_texNormal, textureNormal);

					// Set render states.
					bgfx::setState(0
						| BGFX_STATE_RGB_WRITE
						| BGFX_STATE_ALPHA_WRITE
						| BGFX_STATE_DEPTH_WRITE
						| BGFX_STATE_DEPTH_TEST_LESS
						| BGFX_STATE_MSAA
						);

					// Submit primitive for rendering to view 0.
					bgfx::submit(0);
				}
			}
		}

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(program);
	bgfx::destroyTexture(textureColor);
	bgfx::destroyTexture(textureNormal);
	bgfx::destroyUniform(u_texColor);
	bgfx::destroyUniform(u_texNormal);
	bgfx::destroyUniform(u_lightPosRadius);
	bgfx::destroyUniform(u_lightRgbInnerR);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
