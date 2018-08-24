/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"
#include "bounds.h"

namespace
{

#define RENDER_PASS_GEOMETRY_ID       0
#define RENDER_PASS_LIGHT_ID          1
#define RENDER_PASS_COMBINE_ID        2
#define RENDER_PASS_DEBUG_LIGHTS_ID   3
#define RENDER_PASS_DEBUG_GBUFFER_ID  4

static float s_texelHalf = 0.0f;

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

struct PosTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	float m_u;
	float m_v;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosTexCoord0Vertex::ms_decl;

struct DebugVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl DebugVertex::ms_decl;

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

void screenSpaceQuad(float _textureWidth, float _textureHeight, float _texelHalf, bool _originBottomLeft, float _width = 1.0f, float _height = 1.0f)
{
	if (3 == bgfx::getAvailTransientVertexBuffer(3, PosTexCoord0Vertex::ms_decl) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosTexCoord0Vertex::ms_decl);
		PosTexCoord0Vertex* vertex = (PosTexCoord0Vertex*)vb.data;

		const float minx = -_width;
		const float maxx =  _width;
		const float miny = 0.0f;
		const float maxy = _height*2.0f;

		const float texelHalfW = _texelHalf/_textureWidth;
		const float texelHalfH = _texelHalf/_textureHeight;
		const float minu = -1.0f + texelHalfW;
		const float maxu =  1.0f + texelHalfH;

		const float zz = 0.0f;

		float minv = texelHalfH;
		float maxv = 2.0f + texelHalfH;

		if (_originBottomLeft)
		{
			float temp = minv;
			minv = maxv;
			maxv = temp;

			minv -= 1.0f;
			maxv -= 1.0f;
		}

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_z = zz;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = zz;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = zz;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		bgfx::setVertexBuffer(0, &vb);
	}
}

class ExampleDeferred : public entry::AppI
{
public:
	ExampleDeferred(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
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
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable m_debug text.
		bgfx::setDebug(m_debug);

		// Set palette color for index 0
		bgfx::setPaletteColor(0, UINT32_C(0x00000000) );

		// Set palette color for index 1
		bgfx::setPaletteColor(1, UINT32_C(0x303030ff) );

		// Set geometry pass view clear state.
		bgfx::setViewClear(RENDER_PASS_GEOMETRY_ID
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 1.0f
				, 0
				, 1
				);

		// Set light pass view clear state.
		bgfx::setViewClear(RENDER_PASS_LIGHT_ID
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 1.0f
				, 0
				, 0
				);

		// Create vertex stream declaration.
		PosNormalTangentTexcoordVertex::init();
		PosTexCoord0Vertex::init();
		DebugVertex::init();

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

		s_albedo = bgfx::createUniform("s_albedo", bgfx::UniformType::Int1);
		s_normal = bgfx::createUniform("s_normal", bgfx::UniformType::Int1);
		s_depth  = bgfx::createUniform("s_depth",  bgfx::UniformType::Int1);
		s_light  = bgfx::createUniform("s_light",  bgfx::UniformType::Int1);

		u_mtx            = bgfx::createUniform("u_mtx",            bgfx::UniformType::Mat4);
		u_lightPosRadius = bgfx::createUniform("u_lightPosRadius", bgfx::UniformType::Vec4);
		u_lightRgbInnerR = bgfx::createUniform("u_lightRgbInnerR", bgfx::UniformType::Vec4);

		// Create program from shaders.
		m_geomProgram    = loadProgram("vs_deferred_geom",       "fs_deferred_geom");
		m_lightProgram   = loadProgram("vs_deferred_light",      "fs_deferred_light");
		m_combineProgram = loadProgram("vs_deferred_combine",    "fs_deferred_combine");
		m_debugProgram   = loadProgram("vs_deferred_debug",      "fs_deferred_debug");
		m_lineProgram    = loadProgram("vs_deferred_debug_line", "fs_deferred_debug_line");

		// Load diffuse texture.
		m_textureColor  = loadTexture("textures/fieldstone-rgba.dds");

		// Load normal texture.
		m_textureNormal = loadTexture("textures/fieldstone-n.dds");

		m_gbufferTex[0].idx = bgfx::kInvalidHandle;
		m_gbufferTex[1].idx = bgfx::kInvalidHandle;
		m_gbufferTex[2].idx = bgfx::kInvalidHandle;
		m_gbuffer.idx = bgfx::kInvalidHandle;
		m_lightBuffer.idx = bgfx::kInvalidHandle;

		// Imgui.
		imguiCreate();

		m_timeOffset = bx::getHPCounter();
		const bgfx::RendererType::Enum renderer = bgfx::getRendererType();
		s_texelHalf = bgfx::RendererType::Direct3D9 == renderer ? 0.5f : 0.0f;

		// Get renderer capabilities info.
		m_caps = bgfx::getCaps();

		m_oldWidth  = 0;
		m_oldHeight = 0;
		m_oldReset  = m_reset;

		m_scrollArea = 0;
		m_numLights = 512;
		m_lightAnimationSpeed = 0.3f;
		m_animateMesh = true;
		m_showScissorRects = false;
		m_showGBuffer = true;

		cameraCreate();

		const float initialPos[3] = { 0.0f, 0.0f, -15.0f };
		cameraSetPosition(initialPos);
		cameraSetVerticalAngle(0.0f);
	}

	virtual int shutdown() override
	{
		// Cleanup.
		cameraDestroy();
		imguiDestroy();

		if (bgfx::isValid(m_gbuffer) )
		{
			bgfx::destroy(m_gbuffer);
			bgfx::destroy(m_lightBuffer);
		}

		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);

		bgfx::destroy(m_geomProgram);
		bgfx::destroy(m_lightProgram);
		bgfx::destroy(m_combineProgram);
		bgfx::destroy(m_debugProgram);
		bgfx::destroy(m_lineProgram);

		bgfx::destroy(m_textureColor);
		bgfx::destroy(m_textureNormal);
		bgfx::destroy(s_texColor);
		bgfx::destroy(s_texNormal);

		bgfx::destroy(s_albedo);
		bgfx::destroy(s_normal);
		bgfx::destroy(s_depth);
		bgfx::destroy(s_light);

		bgfx::destroy(u_lightPosRadius);
		bgfx::destroy(u_lightRgbInnerR);
		bgfx::destroy(u_mtx);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx
					, m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					, m_mouseState.m_mz
					, uint16_t(m_width)
					, uint16_t(m_height)
					);

			showExampleDialog(this);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const float deltaTime = float(frameTime/freq);

			float time = (float)( (now-m_timeOffset)/freq);

			if (2 > m_caps->limits.maxFBAttachments)
			{
				// When multiple render targets (MRT) is not supported by GPU,
				// implement alternative code path that doesn't use MRT.
				bool blink = uint32_t(time*3.0f)&1;
				bgfx::dbgTextPrintf(0, 0, blink ? 0x4f : 0x04, " MRT not supported by GPU. ");

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

				// This dummy draw call is here to make sure that view 0 is cleared
				// if no other draw calls are submitted to view 0.
				bgfx::touch(0);
			}
			else
			{
				if (m_oldWidth  != m_width
				||  m_oldHeight != m_height
				||  m_oldReset  != m_reset
				||  !bgfx::isValid(m_gbuffer) )
				{
					// Recreate variable size render targets when resolution changes.
					m_oldWidth  = m_width;
					m_oldHeight = m_height;
					m_oldReset  = m_reset;

					if (bgfx::isValid(m_gbuffer) )
					{
						bgfx::destroy(m_gbuffer);
					}

					const uint64_t tsFlags = 0
						| BGFX_TEXTURE_RT
						| BGFX_SAMPLER_MIN_POINT
						| BGFX_SAMPLER_MAG_POINT
						| BGFX_SAMPLER_MIP_POINT
						| BGFX_SAMPLER_U_CLAMP
						| BGFX_SAMPLER_V_CLAMP
						;
					m_gbufferTex[0] = bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::BGRA8, tsFlags);
					m_gbufferTex[1] = bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::BGRA8, tsFlags);
					m_gbufferTex[2] = bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::D24S8, tsFlags);
					m_gbuffer = bgfx::createFrameBuffer(BX_COUNTOF(m_gbufferTex), m_gbufferTex, true);

					if (bgfx::isValid(m_lightBuffer) )
					{
						bgfx::destroy(m_lightBuffer);
					}

					m_lightBuffer = bgfx::createFrameBuffer(uint16_t(m_width), uint16_t(m_height), bgfx::TextureFormat::BGRA8, tsFlags);
				}

				ImGui::SetNextWindowPos(
					  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
					, ImGuiCond_FirstUseEver
					);
				ImGui::SetNextWindowSize(
					  ImVec2(m_width / 5.0f, m_height / 3.0f)
					, ImGuiCond_FirstUseEver
					);
				ImGui::Begin("Settings"
					, NULL
					, 0
					);

				ImGui::SliderInt("Num lights", &m_numLights, 1, 2048);
				ImGui::Checkbox("Show G-Buffer.", &m_showGBuffer);
				ImGui::Checkbox("Show light scissor.", &m_showScissorRects);
				ImGui::Checkbox("Animate mesh.", &m_animateMesh);
				ImGui::SliderFloat("Anim.speed", &m_lightAnimationSpeed, 0.0f, 0.4f);

				ImGui::End();

				// Update camera.
				cameraUpdate(deltaTime, m_mouseState);

				float view[16];
				cameraGetViewMtx(view);

				// Setup views
				float vp[16];
				float invMvp[16];
				{
					bgfx::setViewRect(RENDER_PASS_GEOMETRY_ID,      0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewRect(RENDER_PASS_LIGHT_ID,         0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewRect(RENDER_PASS_COMBINE_ID,       0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewRect(RENDER_PASS_DEBUG_LIGHTS_ID,  0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewRect(RENDER_PASS_DEBUG_GBUFFER_ID, 0, 0, uint16_t(m_width), uint16_t(m_height) );

					bgfx::setViewFrameBuffer(RENDER_PASS_LIGHT_ID, m_lightBuffer);

					float proj[16];
					bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, m_caps->homogeneousDepth);

					bgfx::setViewFrameBuffer(RENDER_PASS_GEOMETRY_ID, m_gbuffer);
					bgfx::setViewTransform(RENDER_PASS_GEOMETRY_ID, view, proj);

					bx::mtxMul(vp, view, proj);
					bx::mtxInverse(invMvp, vp);

					const bgfx::Caps* caps = bgfx::getCaps();

					bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f, 0.0f, caps->homogeneousDepth);
					bgfx::setViewTransform(RENDER_PASS_LIGHT_ID,   NULL, proj);
					bgfx::setViewTransform(RENDER_PASS_COMBINE_ID, NULL, proj);

					const float aspectRatio = float(m_height)/float(m_width);
					const float size = 10.0f;
					bx::mtxOrtho(proj, -size, size, size*aspectRatio, -size*aspectRatio, 0.0f, 1000.0f, 0.0f, caps->homogeneousDepth);
					bgfx::setViewTransform(RENDER_PASS_DEBUG_GBUFFER_ID, NULL, proj);

					bx::mtxOrtho(proj, 0.0f, (float)m_width, 0.0f, (float)m_height, 0.0f, 1000.0f, 0.0f, caps->homogeneousDepth);
					bgfx::setViewTransform(RENDER_PASS_DEBUG_LIGHTS_ID, NULL, proj);
				}

				const uint32_t dim = 11;
				const float offset = (float(dim-1) * 3.0f) * 0.5f;

				// Draw into geometry pass.
				for (uint32_t yy = 0; yy < dim; ++yy)
				{
					for (uint32_t xx = 0; xx < dim; ++xx)
					{
						float mtx[16];
						if (m_animateMesh)
						{
							bx::mtxRotateXY(mtx, time*1.023f + xx*0.21f, time*0.03f + yy*0.37f);
						}
						else
						{
							bx::mtxIdentity(mtx);
						}
						mtx[12] = -offset + float(xx)*3.0f;
						mtx[13] = -offset + float(yy)*3.0f;
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
						bgfx::submit(RENDER_PASS_GEOMETRY_ID, m_geomProgram);
					}
				}

				// Draw lights into light buffer.
				for (int32_t light = 0; light < m_numLights; ++light)
				{
					Sphere lightPosRadius;

					float lightTime = time * m_lightAnimationSpeed * (bx::sin(light/float(m_numLights) * bx::kPiHalf ) * 0.5f + 0.5f);
					lightPosRadius.m_center[0] = bx::sin( ( (lightTime + light*0.47f) + bx::kPiHalf*1.37f ) )*offset;
					lightPosRadius.m_center[1] = bx::cos( ( (lightTime + light*0.69f) + bx::kPiHalf*1.49f ) )*offset;
					lightPosRadius.m_center[2] = bx::sin( ( (lightTime + light*0.37f) + bx::kPiHalf*1.57f ) )*2.0f;
					lightPosRadius.m_radius = 2.0f;

					Aabb aabb;
					toAabb(aabb, lightPosRadius);

					float box[8][3] =
					{
						{ aabb.m_min[0], aabb.m_min[1], aabb.m_min[2] },
						{ aabb.m_min[0], aabb.m_min[1], aabb.m_max[2] },
						{ aabb.m_min[0], aabb.m_max[1], aabb.m_min[2] },
						{ aabb.m_min[0], aabb.m_max[1], aabb.m_max[2] },
						{ aabb.m_max[0], aabb.m_min[1], aabb.m_min[2] },
						{ aabb.m_max[0], aabb.m_min[1], aabb.m_max[2] },
						{ aabb.m_max[0], aabb.m_max[1], aabb.m_min[2] },
						{ aabb.m_max[0], aabb.m_max[1], aabb.m_max[2] },
					};

					float xyz[3];
					bx::vec3MulMtxH(xyz, box[0], vp);
					float minx = xyz[0];
					float miny = xyz[1];
					float maxx = xyz[0];
					float maxy = xyz[1];
					float maxz = xyz[2];

					for (uint32_t ii = 1; ii < 8; ++ii)
					{
						bx::vec3MulMtxH(xyz, box[ii], vp);
						minx = bx::min(minx, xyz[0]);
						miny = bx::min(miny, xyz[1]);
						maxx = bx::max(maxx, xyz[0]);
						maxy = bx::max(maxy, xyz[1]);
						maxz = bx::max(maxz, xyz[2]);
					}

					// Cull light if it's fully behind camera.
					if (maxz >= 0.0f)
					{
						float x0 = bx::clamp( (minx * 0.5f + 0.5f) * m_width,  0.0f, (float)m_width);
						float y0 = bx::clamp( (miny * 0.5f + 0.5f) * m_height, 0.0f, (float)m_height);
						float x1 = bx::clamp( (maxx * 0.5f + 0.5f) * m_width,  0.0f, (float)m_width);
						float y1 = bx::clamp( (maxy * 0.5f + 0.5f) * m_height, 0.0f, (float)m_height);

						if (m_showScissorRects)
						{
							bgfx::TransientVertexBuffer tvb;
							bgfx::TransientIndexBuffer tib;
							if (bgfx::allocTransientBuffers(&tvb, DebugVertex::ms_decl, 4, &tib, 8) )
							{
								uint32_t abgr = 0x8000ff00;

								DebugVertex* vertex = (DebugVertex*)tvb.data;
								vertex->m_x = x0;
								vertex->m_y = y0;
								vertex->m_z = 0.0f;
								vertex->m_abgr = abgr;
								++vertex;

								vertex->m_x = x1;
								vertex->m_y = y0;
								vertex->m_z = 0.0f;
								vertex->m_abgr = abgr;
								++vertex;

								vertex->m_x = x1;
								vertex->m_y = y1;
								vertex->m_z = 0.0f;
								vertex->m_abgr = abgr;
								++vertex;

								vertex->m_x = x0;
								vertex->m_y = y1;
								vertex->m_z = 0.0f;
								vertex->m_abgr = abgr;

								uint16_t* indices = (uint16_t*)tib.data;
								*indices++ = 0;
								*indices++ = 1;
								*indices++ = 1;
								*indices++ = 2;
								*indices++ = 2;
								*indices++ = 3;
								*indices++ = 3;
								*indices++ = 0;

								bgfx::setVertexBuffer(0, &tvb);
								bgfx::setIndexBuffer(&tib);
								bgfx::setState(0
										| BGFX_STATE_WRITE_RGB
										| BGFX_STATE_PT_LINES
										| BGFX_STATE_BLEND_ALPHA
										);
								bgfx::submit(RENDER_PASS_DEBUG_LIGHTS_ID, m_lineProgram);
							}
						}

						uint8_t val = light&7;
						float lightRgbInnerR[4] =
						{
							val & 0x1 ? 1.0f : 0.25f,
							val & 0x2 ? 1.0f : 0.25f,
							val & 0x4 ? 1.0f : 0.25f,
							0.8f,
						};

						// Draw light.
						bgfx::setUniform(u_lightPosRadius, &lightPosRadius);
						bgfx::setUniform(u_lightRgbInnerR, lightRgbInnerR);
						bgfx::setUniform(u_mtx, invMvp);
						const uint16_t scissorHeight = uint16_t(y1-y0);
						bgfx::setScissor(uint16_t(x0), uint16_t(m_height-scissorHeight-y0), uint16_t(x1-x0), uint16_t(scissorHeight) );
						bgfx::setTexture(0, s_normal, bgfx::getTexture(m_gbuffer, 1) );
						bgfx::setTexture(1, s_depth,  bgfx::getTexture(m_gbuffer, 2) );
						bgfx::setState(0
								| BGFX_STATE_WRITE_RGB
								| BGFX_STATE_WRITE_A
								| BGFX_STATE_BLEND_ADD
								);
						screenSpaceQuad( (float)m_width, (float)m_height, s_texelHalf, m_caps->originBottomLeft);
						bgfx::submit(RENDER_PASS_LIGHT_ID, m_lightProgram);
					}
				}

				// Combine color and light buffers.
				bgfx::setTexture(0, s_albedo, bgfx::getTexture(m_gbuffer,     0) );
				bgfx::setTexture(1, s_light,  bgfx::getTexture(m_lightBuffer, 0) );
				bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						);
				screenSpaceQuad( (float)m_width, (float)m_height, s_texelHalf, m_caps->originBottomLeft);
				bgfx::submit(RENDER_PASS_COMBINE_ID, m_combineProgram);

				if (m_showGBuffer)
				{
					const float aspectRatio = float(m_width)/float(m_height);

					// Draw m_debug m_gbuffer.
					for (uint32_t ii = 0; ii < BX_COUNTOF(m_gbufferTex); ++ii)
					{
						float mtx[16];
						bx::mtxSRT(mtx
								, aspectRatio, 1.0f, 1.0f
								, 0.0f, 0.0f, 0.0f
								, -7.9f - BX_COUNTOF(m_gbufferTex)*0.1f*0.5f + ii*2.1f*aspectRatio, 4.0f, 0.0f
								);

						bgfx::setTransform(mtx);
						bgfx::setVertexBuffer(0, m_vbh);
						bgfx::setIndexBuffer(m_ibh, 0, 6);
						bgfx::setTexture(0, s_texColor, m_gbufferTex[ii]);
						bgfx::setState(BGFX_STATE_WRITE_RGB);
						bgfx::submit(RENDER_PASS_DEBUG_GBUFFER_ID, m_debugProgram);
					}
				}
			}

			imguiEndFrame();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texNormal;

	bgfx::UniformHandle s_albedo;
	bgfx::UniformHandle s_normal;
	bgfx::UniformHandle s_depth;
	bgfx::UniformHandle s_light;

	bgfx::UniformHandle u_mtx;
	bgfx::UniformHandle u_lightPosRadius;
	bgfx::UniformHandle u_lightRgbInnerR;

	bgfx::ProgramHandle m_geomProgram;
	bgfx::ProgramHandle m_lightProgram;
	bgfx::ProgramHandle m_combineProgram;
	bgfx::ProgramHandle m_debugProgram;
	bgfx::ProgramHandle m_lineProgram;
	bgfx::TextureHandle m_textureColor;
	bgfx::TextureHandle m_textureNormal;

	bgfx::TextureHandle m_gbufferTex[3];
	bgfx::FrameBufferHandle m_gbuffer;
	bgfx::FrameBufferHandle m_lightBuffer;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	uint32_t m_oldWidth;
	uint32_t m_oldHeight;
	uint32_t m_oldReset;

	int32_t m_scrollArea;
	int32_t m_numLights;
	float m_lightAnimationSpeed;
	bool m_animateMesh;
	bool m_showScissorRects;
	bool m_showGBuffer;

	entry::MouseState m_mouseState;

	const bgfx::Caps* m_caps;
	int64_t m_timeOffset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleDeferred, "21-deferred", "MRT rendering and deferred shading.");
