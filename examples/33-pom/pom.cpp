/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"

#include <imgui/imgui.h>

namespace
{

struct PosTangentBitangentTexcoordVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_tangent;
	uint32_t m_bitangent;
	float m_u;
	float m_v;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Tangent,   4, bgfx::AttribType::Uint8, true, true)
			.add(bgfx::Attrib::Bitangent, 4, bgfx::AttribType::Uint8, true, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true, true)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosTangentBitangentTexcoordVertex::ms_decl;

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

static PosTangentBitangentTexcoordVertex s_cubeVertices[24] =
{
	{-1, -1,  1, packF4u(-1,  0,  0), packF4u( 0, -1,  0),   1,  1 }, // Back
	{ 1,  1,  1, packF4u(-1,  0,  0), packF4u( 0, -1,  0),   0,  0 },
	{-1,  1,  1, packF4u(-1,  0,  0), packF4u( 0, -1,  0),   1,  0 },
	{ 1, -1,  1, packF4u(-1,  0,  0), packF4u( 0, -1,  0),   0,  1 },
	{-1, -1, -1, packF4u( 1,  0,  0), packF4u( 0, -1,  0),   0,  1 }, // Front
	{ 1,  1, -1, packF4u( 1,  0,  0), packF4u( 0, -1,  0),   1,  0 },
	{-1,  1, -1, packF4u( 1,  0,  0), packF4u( 0, -1,  0),   0,  0 },
	{ 1, -1, -1, packF4u( 1,  0,  0), packF4u( 0, -1,  0),   1,  1 },
	{ 1, -1, -1, packF4u( 0,  0,  1), packF4u( 0, -1,  0),   0,  1 }, // Right
	{ 1,  1,  1, packF4u( 0,  0,  1), packF4u( 0, -1,  0),   1,  0 },
	{ 1, -1,  1, packF4u( 0,  0,  1), packF4u( 0, -1,  0),   1,  1 },
	{ 1,  1, -1, packF4u( 0,  0,  1), packF4u( 0, -1,  0),   0,  0 },
	{-1, -1, -1, packF4u( 0,  0, -1), packF4u( 0, -1,  0),   1,  1 }, // Left
	{-1,  1,  1, packF4u( 0,  0, -1), packF4u( 0, -1,  0),   0,  0 },
	{-1, -1,  1, packF4u( 0,  0, -1), packF4u( 0, -1,  0),   0,  1 },
	{-1,  1, -1, packF4u( 0,  0, -1), packF4u( 0, -1,  0),   1,  0 },
	{-1,  1, -1, packF4u( 1,  0,  0), packF4u( 0,  0, -1),   0,  1 }, // Top
	{ 1,  1,  1, packF4u( 1,  0,  0), packF4u( 0,  0, -1),   1,  0 },
	{-1,  1,  1, packF4u( 1,  0,  0), packF4u( 0,  0, -1),   0,  0 },
	{ 1,  1, -1, packF4u( 1,  0,  0), packF4u( 0,  0, -1),   1,  1 },
	{-1, -1, -1, packF4u( 1,  0,  0), packF4u( 0,  0,  1),   0,  0 }, // Bottom
	{ 1, -1,  1, packF4u( 1,  0,  0), packF4u( 0,  0,  1),   1,  1 },
	{-1, -1,  1, packF4u( 1,  0,  0), packF4u( 0,  0,  1),   0,  1 },
	{ 1, -1, -1, packF4u( 1,  0,  0), packF4u( 0,  0,  1),   1,  0 },
};

static const uint16_t s_cubeIndices[36] =
{
	0 , 1 , 2 ,
	0 , 3 , 1 ,
	4 , 6 , 5 ,
	4 , 5 , 7 ,

	8 , 9 , 10,
	8 , 11, 9 ,
	12, 14, 13,
	12, 13, 15,

	16, 18, 17,
	16, 17, 19,
	20, 21, 22,
	20, 23, 21,
};

class ExamplePom : public entry::AppI
{
public:
	ExamplePom(const char* _name, const char* _description)
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
		PosTangentBitangentTexcoordVertex::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) ),
						 PosTangentBitangentTexcoordVertex::ms_decl);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

		// Create texture sampler uniforms.
		s_texColor  = bgfx::createUniform("s_texColor",  bgfx::UniformType::Int1);
		s_texNormal = bgfx::createUniform("s_texNormal", bgfx::UniformType::Int1);
		s_texDepth = bgfx::createUniform("s_texDepth",  bgfx::UniformType::Int1);


		u_light_pos = bgfx::createUniform("u_light_pos", bgfx::UniformType::Vec4);
		u_norm_mtx  = bgfx::createUniform("u_norm_mtx",  bgfx::UniformType::Mat4);
		u_pomParam  = bgfx::createUniform("u_pomParam",  bgfx::UniformType::Vec4);

		// Create program from shaders.
		m_program = loadProgram("vs_pom", "fs_pom");

		// Load diffuse texture.
		m_textureColor = loadTexture("textures/parallax-d.ktx");

		// Load normal texture.
		m_textureNormal = loadTexture("textures/parallax-n.ktx");

		// Load depth texture.
		m_textureDepth = loadTexture("textures/parallax-h.ktx");

		imguiCreate();

		m_timeOffset = bx::getHPCounter();
		m_shading_type = 4;
		m_show_diffuse_texture = true;
		m_parallax_scale = 50;
		m_num_steps = 16;
	}

	virtual int shutdown() override
	{
		// Cleanup.
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);
		bgfx::destroy(m_textureColor);
		bgfx::destroy(m_textureNormal);
		bgfx::destroy(m_textureDepth);
		bgfx::destroy(s_texColor);
		bgfx::destroy(s_texNormal);
		bgfx::destroy(s_texDepth);
		bgfx::destroy(u_light_pos);
		bgfx::destroy(u_norm_mtx);
		bgfx::destroy(u_pomParam);

		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			const double freq = double(bx::getHPFrequency() );

			float time = (float)( (now-m_timeOffset)/freq);

			float at[3]  = { 0.0f, 0.0f, 1.0f };
			float eye[3] = { 0.0f, 0.0f, 0.0f };

			// Set view and projection matrix for view 0.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
			{
				float view[16];
				bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);
				bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);

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
				bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			imguiBeginFrame(
				   m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this);

			ImGui::SetNextWindowPos(
				  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_width / 5.0f, m_height / 2.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			ImGui::RadioButton("No bump mapping", &m_shading_type, 0);
			ImGui::RadioButton("Normal mapping", &m_shading_type, 1);
			ImGui::RadioButton("Parallax mapping", &m_shading_type, 2);
			ImGui::RadioButton("Steep parallax mapping", &m_shading_type, 3);
			ImGui::RadioButton("Parallax occlusion mapping", &m_shading_type, 4);

			ImGui::Separator();

			ImGui::Checkbox("Show diffuse texture", &m_show_diffuse_texture);

			if (m_shading_type > 1)
			{
				ImGui::Separator();

				float multiplier = 1000.0f;
				float x = (float)m_parallax_scale / multiplier;
				ImGui::SliderFloat("Parallax scale", &x, 0.0f, 0.1f);
				m_parallax_scale = (int32_t)(x * multiplier);
			}

			if (m_shading_type > 2)
			{
				ImGui::Separator();

				ImGui::SliderInt("Number of steps", &m_num_steps, 1, 32);
			}

			ImGui::End();

			imguiEndFrame();

			float lightPos[4] = { 1.0f, 2.0f, 0.0f, 0.0f };
			bgfx::setUniform(u_light_pos, lightPos);

			float a[16];
			float b[16];
			float c[16];
			float d[16];
			float mtx[16];
			bx::mtxRotateY(a, time * 0.4f);
			bx::mtxRotateX(b, 0.4f);
			bx::mtxMul(c, a, b);
			bx::mtxTranslate(d, 0.0f, 0.0f, 4.0f);
			bx::mtxMul(mtx, c, d);

			// Set transform for draw call.
			bgfx::setTransform(mtx);

			float pomParam[4] = { float(m_shading_type), float(m_show_diffuse_texture), float(m_parallax_scale), float(m_num_steps) };
			bgfx::setUniform(u_pomParam, pomParam);

			// Set normal matrix uniform
			float inv[16];
			float transpose[16];
			bx::mtxInverse(inv, mtx);
			bx::mtxTranspose(transpose, inv);
			bgfx::setUniform(u_norm_mtx, transpose);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(0, m_vbh);
			bgfx::setIndexBuffer(m_ibh);

			// Bind textures.
			bgfx::setTexture(0, s_texColor,  m_textureColor);
			bgfx::setTexture(1, s_texNormal, m_textureNormal);
			bgfx::setTexture(2, s_texDepth, m_textureDepth);

			// Set render states.
			bgfx::setState(0
					| BGFX_STATE_RGB_WRITE
					| BGFX_STATE_ALPHA_WRITE
					| BGFX_STATE_DEPTH_WRITE
					| BGFX_STATE_DEPTH_TEST_LESS
					| BGFX_STATE_MSAA
					);

			// Submit primitive for rendering to view 0.
			bgfx::submit(0, m_program);

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texNormal;
	bgfx::UniformHandle s_texDepth;
	bgfx::UniformHandle u_light_pos;
	bgfx::UniformHandle u_norm_mtx;
	bgfx::UniformHandle u_pomParam;
	bgfx::ProgramHandle m_program;
	bgfx::TextureHandle m_textureColor;
	bgfx::TextureHandle m_textureNormal;
	bgfx::TextureHandle m_textureDepth;

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	int64_t m_timeOffset;

	int32_t m_shading_type;
	bool    m_show_diffuse_texture;
	int32_t m_parallax_scale;
	int32_t m_num_steps;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExamplePom, "33-pom", "Parallax mapping.");
