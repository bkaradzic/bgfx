/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

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

static PosNormalTangentTexcoordVertex s_cubeVertices[24] =
{
	{-1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 0, 0x7fff, 0x7fff },
	{-1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 0,      0,      0 },
	{ 1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 0, 0x7fff, 0x7fff },
	{-1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{-1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 0,      0,      0 },
	{ 1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{ 1.0f, -1.0f,  1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 0, 0x7fff,      0 },
	{ 1.0f, -1.0f, -1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f,  1.0f, -1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{-1.0f, -1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0,      0,      0 },
	{-1.0f,  1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0,      0, 0x7fff },
	{-1.0f,  1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0, 0x7fff, 0x7fff },
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

class ExampleBump : public entry::AppI
{
public:
	ExampleBump(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
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

		// Get renderer capabilities info.
		const bgfx::Caps* caps = bgfx::getCaps();
		m_instancingSupported = 0 != (caps->supported & BGFX_CAPS_INSTANCING);

		// Create vertex stream declaration.
		PosNormalTangentTexcoordVertex::init();

		calcTangents(s_cubeVertices
				, BX_COUNTOF(s_cubeVertices)
				, PosNormalTangentTexcoordVertex::ms_decl
				, s_cubeIndices
				, BX_COUNTOF(s_cubeIndices)
				);

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
					  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
					, PosNormalTangentTexcoordVertex::ms_decl
					);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

		// Create texture sampler uniforms.
		s_texColor  = bgfx::createUniform("s_texColor",  bgfx::UniformType::Int1);
		s_texNormal = bgfx::createUniform("s_texNormal", bgfx::UniformType::Int1);

		m_numLights = 4;
		u_lightPosRadius = bgfx::createUniform("u_lightPosRadius", bgfx::UniformType::Vec4, m_numLights);
		u_lightRgbInnerR = bgfx::createUniform("u_lightRgbInnerR", bgfx::UniformType::Vec4, m_numLights);

		// Create program from shaders.
		m_program = loadProgram(m_instancingSupported ? "vs_bump_instanced" : "vs_bump", "fs_bump");

		// Load diffuse texture.
		m_textureColor = loadTexture("textures/fieldstone-rgba.dds");

		// Load normal texture.
		m_textureNormal = loadTexture("textures/fieldstone-n.dds");

		m_timeOffset = bx::getHPCounter();

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		// Cleanup.
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);
		bgfx::destroy(m_textureColor);
		bgfx::destroy(m_textureNormal);
		bgfx::destroy(s_texColor);
		bgfx::destroy(s_texNormal);
		bgfx::destroy(u_lightPosRadius);
		bgfx::destroy(u_lightRgbInnerR);

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

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			float time = (float)( (bx::getHPCounter()-m_timeOffset)/double(bx::getHPFrequency() ));

			float at[3]  = { 0.0f, 0.0f,  0.0f };
			float eye[3] = { 0.0f, 0.0f, -7.0f };

			// Set view and projection matrix for view 0.
			{
				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			float lightPosRadius[4][4];
			for (uint32_t ii = 0; ii < m_numLights; ++ii)
			{
				lightPosRadius[ii][0] = bx::sin( (time*(0.1f + ii*0.17f) + ii*bx::kPiHalf*1.37f ) )*3.0f;
				lightPosRadius[ii][1] = bx::cos( (time*(0.2f + ii*0.29f) + ii*bx::kPiHalf*1.49f ) )*3.0f;
				lightPosRadius[ii][2] = -2.5f;
				lightPosRadius[ii][3] = 3.0f;
			}

			bgfx::setUniform(u_lightPosRadius, lightPosRadius, m_numLights);

			float lightRgbInnerR[4][4] =
			{
				{ 1.0f, 0.7f, 0.2f, 0.8f },
				{ 0.7f, 0.2f, 1.0f, 0.8f },
				{ 0.2f, 1.0f, 0.7f, 0.8f },
				{ 1.0f, 0.4f, 0.2f, 0.8f },
			};

			bgfx::setUniform(u_lightRgbInnerR, lightRgbInnerR, m_numLights);

			const uint16_t instanceStride = 64;
			const uint16_t numInstances   = 3;

			if (m_instancingSupported)
			{
				// Write instance data for 3x3 cubes.
				for (uint32_t yy = 0; yy < 3; ++yy)
				{
					if (numInstances == bgfx::getAvailInstanceDataBuffer(numInstances, instanceStride) )
					{
						bgfx::InstanceDataBuffer idb;
						bgfx::allocInstanceDataBuffer(&idb, numInstances, instanceStride);

						uint8_t* data = idb.data;

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
						bgfx::setInstanceDataBuffer(&idb, 0, numInstances);

						// Set vertex and index buffer.
						bgfx::setVertexBuffer(0, m_vbh);
						bgfx::setIndexBuffer(m_ibh);

						// Bind textures.
						bgfx::setTexture(0, s_texColor,  m_textureColor);
						bgfx::setTexture(1, s_texNormal, m_textureNormal);

						// Set render states.
						bgfx::setState(0
								| BGFX_STATE_WRITE_RGB
								| BGFX_STATE_WRITE_A
								| BGFX_STATE_WRITE_Z
								| BGFX_STATE_DEPTH_TEST_LESS
								| BGFX_STATE_MSAA
								);

						// Submit primitive for rendering to view 0.
						bgfx::submit(0, m_program);
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

						// Set vertex and index buffer.
						bgfx::setVertexBuffer(0, m_vbh);
						bgfx::setIndexBuffer(m_ibh);

						// Bind textures.
						bgfx::setTexture(0, s_texColor,  m_textureColor);
						bgfx::setTexture(1, s_texNormal, m_textureNormal);

						// Set render states.
						bgfx::setState(0
								| BGFX_STATE_WRITE_RGB
								| BGFX_STATE_WRITE_A
								| BGFX_STATE_WRITE_Z
								| BGFX_STATE_DEPTH_TEST_LESS
								| BGFX_STATE_MSAA
								);

						// Submit primitive for rendering to view 0.
						bgfx::submit(0, m_program);
					}
				}
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texNormal;
	bgfx::UniformHandle u_lightPosRadius;
	bgfx::UniformHandle u_lightRgbInnerR;
	bgfx::ProgramHandle m_program;
	bgfx::TextureHandle m_textureColor;
	bgfx::TextureHandle m_textureNormal;
	uint16_t m_numLights;
	bool m_instancingSupported;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	int64_t m_timeOffset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleBump, "06-bump", "Loading textures.");
