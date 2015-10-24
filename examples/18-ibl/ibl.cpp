/*
 * Copyright 2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <vector>
#include <string>

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "nanovg/nanovg.h"

#include <bx/readerwriter.h>
#include <bx/string.h>

static float s_texelHalf = 0.0f;

struct Uniforms
{
	void init()
	{
		m_time = 0.0f;
		bx::mtxIdentity(m_mtx);

		u_mtx     = bgfx::createUniform("u_mtx",     bgfx::UniformType::Mat4);
		u_params  = bgfx::createUniform("u_params",  bgfx::UniformType::Vec4);
		u_flags   = bgfx::createUniform("u_flags",   bgfx::UniformType::Vec4);
		u_camPos  = bgfx::createUniform("u_camPos",  bgfx::UniformType::Vec4);
		u_rgbDiff = bgfx::createUniform("u_rgbDiff", bgfx::UniformType::Vec4);
		u_rgbSpec = bgfx::createUniform("u_rgbSpec", bgfx::UniformType::Vec4);
	}

	// Call this once per frame.
	void submitPerFrameUniforms()
	{
		bgfx::setUniform(u_mtx,     m_mtx);
		bgfx::setUniform(u_flags,   m_flags);
		bgfx::setUniform(u_camPos,  m_camPosTime);
		bgfx::setUniform(u_rgbDiff, m_rgbDiff);
		bgfx::setUniform(u_rgbSpec, m_rgbSpec);
	}

	// Call this before each draw call.
	void submitPerDrawUniforms()
	{
		bgfx::setUniform(u_params, m_params);
	}

	void destroy()
	{
		bgfx::destroyUniform(u_rgbSpec);
		bgfx::destroyUniform(u_rgbDiff);
		bgfx::destroyUniform(u_camPos);
		bgfx::destroyUniform(u_flags);
		bgfx::destroyUniform(u_params);
		bgfx::destroyUniform(u_mtx);
	}

	union
	{
		struct
		{
			float m_glossiness;
			float m_exposure;
			float m_diffspec;
			float m_time;
		};

		float m_params[4];
	};

	union
	{
		struct
		{
			float m_diffuse;
			float m_specular;
			float m_diffuseIbl;
			float m_specularIbl;
		};

		float m_flags[4];
	};

	float m_mtx[16];
	float m_camPosTime[4];
	float m_rgbDiff[4];
	float m_rgbSpec[4];

	bgfx::UniformHandle u_mtx;
	bgfx::UniformHandle u_params;
	bgfx::UniformHandle u_flags;
	bgfx::UniformHandle u_camPos;
	bgfx::UniformHandle u_rgbDiff;
	bgfx::UniformHandle u_rgbSpec;
};

static Uniforms s_uniforms;

struct PosColorTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_rgba;
	float m_u;
	float m_v;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorTexCoord0Vertex::ms_decl;

void screenSpaceQuad(float _textureWidth, float _textureHeight, bool _originBottomLeft = false, float _width = 1.0f, float _height = 1.0f)
{
	if (bgfx::checkAvailTransientVertexBuffer(3, PosColorTexCoord0Vertex::ms_decl) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosColorTexCoord0Vertex::ms_decl);
		PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)vb.data;

		const float zz = 0.0f;

		const float minx = -_width;
		const float maxx =  _width;
		const float miny = 0.0f;
		const float maxy = _height*2.0f;

		const float texelHalfW = s_texelHalf/_textureWidth;
		const float texelHalfH = s_texelHalf/_textureHeight;
		const float minu = -1.0f + texelHalfW;
		const float maxu =  1.0f + texelHalfW;

		float minv = texelHalfH;
		float maxv = 2.0f + texelHalfH;

		if (_originBottomLeft)
		{
			std::swap(minv, maxv);
			minv -= 1.0f;
			maxv -= 1.0f;
		}

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_z = zz;
		vertex[0].m_rgba = 0xffffffff;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = zz;
		vertex[1].m_rgba = 0xffffffff;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = zz;
		vertex[2].m_rgba = 0xffffffff;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		bgfx::setVertexBuffer(&vb);
	}
}

struct LightProbe
{
	enum Enum
	{
		Wells,
		Uffizi,
		Pisa,
		Ennis,
		Grace,

		Count
	};

	void load(const char* _name)
	{
		char filePath[512];

		strcpy(filePath, _name);
		strcat(filePath, "_lod.dds");
		m_tex = loadTexture(filePath, BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP);

		strcpy(filePath, _name);
		strcat(filePath, "_irr.dds");
		m_texIrr = loadTexture(filePath, BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP);
	}

	void destroy()
	{
		bgfx::destroyTexture(m_tex);
		bgfx::destroyTexture(m_texIrr);
	}

	bgfx::TextureHandle m_tex;
	bgfx::TextureHandle m_texIrr;
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

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set views  clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	// Imgui.
	imguiCreate();

	// Uniforms.
	s_uniforms.init();

	// Vertex declarations.
	PosColorTexCoord0Vertex::init();

	LightProbe lightProbes[LightProbe::Count];
	lightProbes[LightProbe::Wells ].load("wells");
	lightProbes[LightProbe::Uffizi].load("uffizi");
	lightProbes[LightProbe::Pisa  ].load("pisa");
	lightProbes[LightProbe::Ennis ].load("ennis");
	lightProbes[LightProbe::Grace ].load("grace");
	LightProbe::Enum currentLightProbe = LightProbe::Wells;

	bgfx::UniformHandle u_mtx        = bgfx::createUniform("u_mtx",        bgfx::UniformType::Mat4);
	bgfx::UniformHandle u_params     = bgfx::createUniform("u_params",     bgfx::UniformType::Vec4);
	bgfx::UniformHandle u_flags      = bgfx::createUniform("u_flags",      bgfx::UniformType::Vec4);
	bgfx::UniformHandle u_camPos     = bgfx::createUniform("u_camPos",     bgfx::UniformType::Vec4);
	bgfx::UniformHandle s_texCube    = bgfx::createUniform("s_texCube",    bgfx::UniformType::Int1);
	bgfx::UniformHandle s_texCubeIrr = bgfx::createUniform("s_texCubeIrr", bgfx::UniformType::Int1);

	bgfx::ProgramHandle programMesh  = loadProgram("vs_ibl_mesh",   "fs_ibl_mesh");
	bgfx::ProgramHandle programSky   = loadProgram("vs_ibl_skybox", "fs_ibl_skybox");

	Mesh* meshBunny;
	meshBunny = meshLoad("meshes/bunny.bin");

	struct Settings
	{
		float m_speed;
		float m_glossiness;
		float m_exposure;
		float m_diffspec;
		float m_rgbDiff[3];
		float m_rgbSpec[3];
		bool m_diffuse;
		bool m_specular;
		bool m_diffuseIbl;
		bool m_specularIbl;
		bool m_showDiffColorWheel;
		bool m_showSpecColorWheel;
		ImguiCubemap::Enum m_crossCubemapPreview;
	};

	Settings settings;
	settings.m_speed = 0.37f;
	settings.m_glossiness = 1.0f;
	settings.m_exposure = 0.0f;
	settings.m_diffspec = 0.65f;
	settings.m_rgbDiff[0] = 0.2f;
	settings.m_rgbDiff[1] = 0.2f;
	settings.m_rgbDiff[2] = 0.2f;
	settings.m_rgbSpec[0] = 1.0f;
	settings.m_rgbSpec[1] = 1.0f;
	settings.m_rgbSpec[2] = 1.0f;
	settings.m_diffuse = true;
	settings.m_specular = true;
	settings.m_diffuseIbl = true;
	settings.m_specularIbl = true;
	settings.m_showDiffColorWheel = true;
	settings.m_showSpecColorWheel = false;
	settings.m_crossCubemapPreview = ImguiCubemap::Cross;

	float time = 0.0f;

	int32_t leftScrollArea = 0;

	entry::MouseState mouseState;
	while (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
			, mouseState.m_mz
			, width
			, height
			);

		static int32_t rightScrollArea = 0;
		imguiBeginScrollArea("Settings", width - 256 - 10, 10, 256, 540, &rightScrollArea);

		imguiLabel("Shade:");
		imguiSeparator();
		imguiBool("Diffuse",      settings.m_diffuse);
		imguiBool("Specular",     settings.m_specular);
		imguiBool("IBL Diffuse",  settings.m_diffuseIbl);
		imguiBool("IBL Specular", settings.m_specularIbl);

		imguiSeparatorLine();
		imguiSlider("Speed", settings.m_speed, 0.0f, 1.0f, 0.01f);
		imguiSeparatorLine();

		imguiSeparator();
		imguiSlider("Exposure", settings.m_exposure, -8.0f, 8.0f, 0.01f);
		imguiSeparator();

		imguiLabel("Environment:");
		currentLightProbe = LightProbe::Enum(imguiChoose(currentLightProbe
													   , "Wells"
													   , "Uffizi"
													   , "Pisa"
													   , "Ennis"
													   , "Grace"
													   ) );
		static float lod = 0.0f;
		if (imguiCube(lightProbes[currentLightProbe].m_tex, lod, settings.m_crossCubemapPreview, true) )
		{
			settings.m_crossCubemapPreview = ImguiCubemap::Enum( (settings.m_crossCubemapPreview+1) % ImguiCubemap::Count);
		}
		imguiSlider("Texture LOD", lod, 0.0f, 10.1f, 0.1f);

		imguiEndScrollArea();

		imguiBeginScrollArea("Settings", 10, 70, 256, 576, &leftScrollArea);

		imguiLabel("Material properties:");
		imguiSeparator();
		imguiSlider("Diffuse - Specular", settings.m_diffspec,   0.0f, 1.0f, 0.01f);
		imguiSlider("Glossiness"        , settings.m_glossiness, 0.0f, 1.0f, 0.01f);
		imguiSeparator();

		imguiColorWheel("Diffuse color:", &settings.m_rgbDiff[0], settings.m_showDiffColorWheel);
		imguiSeparator();
		imguiColorWheel("Specular color:", &settings.m_rgbSpec[0], settings.m_showSpecColorWheel);

		imguiSeparator();
		imguiLabel("Predefined materials:");
		imguiSeparator();

		if (imguiButton("Gold") )
		{
			settings.m_glossiness = 0.8f;
			settings.m_diffspec   = 1.0f;

			settings.m_rgbDiff[0] = 0.0f;
			settings.m_rgbDiff[1] = 0.0f;
			settings.m_rgbDiff[2] = 0.0f;

			settings.m_rgbSpec[0] = 1.0f;
			settings.m_rgbSpec[1] = 0.86f;
			settings.m_rgbSpec[2] = 0.58f;
		}

		if (imguiButton("Copper") )
		{
			settings.m_glossiness = 0.67f;
			settings.m_diffspec   = 1.0f;

			settings.m_rgbDiff[0] = 0.0f;
			settings.m_rgbDiff[1] = 0.0f;
			settings.m_rgbDiff[2] = 0.0f;

			settings.m_rgbSpec[0] = 0.98f;
			settings.m_rgbSpec[1] = 0.82f;
			settings.m_rgbSpec[2] = 0.76f;
		}

		if (imguiButton("Titanium") )
		{
			settings.m_glossiness = 0.57f;
			settings.m_diffspec   = 1.0f;

			settings.m_rgbDiff[0] = 0.0f;
			settings.m_rgbDiff[1] = 0.0f;
			settings.m_rgbDiff[2] = 0.0f;

			settings.m_rgbSpec[0] = 0.76f;
			settings.m_rgbSpec[1] = 0.73f;
			settings.m_rgbSpec[2] = 0.71f;
		}

		if (imguiButton("Steel") )
		{
			settings.m_glossiness = 0.82f;
			settings.m_diffspec   = 1.0f;

			settings.m_rgbDiff[0] = 0.0f;
			settings.m_rgbDiff[1] = 0.0f;
			settings.m_rgbDiff[2] = 0.0f;

			settings.m_rgbSpec[0] = 0.77f;
			settings.m_rgbSpec[1] = 0.78f;
			settings.m_rgbSpec[2] = 0.77f;
		}

		imguiEndScrollArea();

		imguiEndFrame();

		s_uniforms.m_glossiness = settings.m_glossiness;
		s_uniforms.m_exposure = settings.m_exposure;
		s_uniforms.m_diffspec = settings.m_diffspec;
		s_uniforms.m_flags[0] = float(settings.m_diffuse);
		s_uniforms.m_flags[1] = float(settings.m_specular);
		s_uniforms.m_flags[2] = float(settings.m_diffuseIbl);
		s_uniforms.m_flags[3] = float(settings.m_specularIbl);
		memcpy(s_uniforms.m_rgbDiff, settings.m_rgbDiff, 3*sizeof(float) );
		memcpy(s_uniforms.m_rgbSpec, settings.m_rgbSpec, 3*sizeof(float) );

		s_uniforms.submitPerFrameUniforms();

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		time += (float)(frameTime*settings.m_speed/freq);
		s_uniforms.m_camPosTime[3] = time;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/18-ibl");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Image based lightning.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		float at[3] = { 0.0f, 0.0f, 0.0f };
		float eye[3] = { 0.0f, 0.0f, -3.0f };

		bx::mtxRotateXY(s_uniforms.m_mtx
			, 0.0f
			, time
			);

		float view[16];
		float proj[16];

		bx::mtxIdentity(view);
		bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);
		bgfx::setViewTransform(0, view, proj);

		bx::mtxLookAt(view, eye, at);
		memcpy(s_uniforms.m_camPosTime, eye, 3*sizeof(float) );
		bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);
		bgfx::setViewTransform(1, view, proj);

		bgfx::setViewRect(0, 0, 0, width, height);
		bgfx::setViewRect(1, 0, 0, width, height);

		// View 0.
		bgfx::setTexture(0, s_texCube, lightProbes[currentLightProbe].m_tex);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width, (float)height, true);
		s_uniforms.submitPerDrawUniforms();
		bgfx::submit(0, programSky);

		// View 1.
		float mtx[16];
		bx::mtxSRT(mtx
				, 1.0f
				, 1.0f
				, 1.0f
				, 0.0f
				, bx::pi+time
				, 0.0f
				, 0.0f
				, -1.0f
				, 0.0f
				);

		bgfx::setTexture(0, s_texCube,    lightProbes[currentLightProbe].m_tex);
		bgfx::setTexture(1, s_texCubeIrr, lightProbes[currentLightProbe].m_texIrr);
		meshSubmit(meshBunny, 1, programMesh, mtx);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	meshUnload(meshBunny);

	// Cleanup.
	bgfx::destroyProgram(programMesh);
	bgfx::destroyProgram(programSky);

	bgfx::destroyUniform(u_camPos);
	bgfx::destroyUniform(u_flags);
	bgfx::destroyUniform(u_params);
	bgfx::destroyUniform(u_mtx);

	bgfx::destroyUniform(s_texCube);
	bgfx::destroyUniform(s_texCubeIrr);

	for (uint8_t ii = 0; ii < LightProbe::Count; ++ii)
	{
		lightProbes[ii].destroy();
	}

	s_uniforms.destroy();

	imguiDestroy();

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
