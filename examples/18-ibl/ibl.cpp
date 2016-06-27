/*
 * Copyright 2014-2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
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
	enum { NumVec4 = 12 };

	void init()
	{
		u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, NumVec4);
	}

	void submit()
	{
		bgfx::setUniform(u_params, m_params, NumVec4);
	}

	void destroy()
	{
		bgfx::destroyUniform(u_params);
	}

	union
	{
		struct
		{
			union
			{
				  float m_mtx[16];
			/* 0*/ struct { float m_mtx0[4]; };
			/* 1*/ struct { float m_mtx1[4]; };
			/* 2*/ struct { float m_mtx2[4]; };
			/* 3*/ struct { float m_mtx3[4]; };
			};
			/* 4*/ struct { float m_glossiness, m_reflectivity, m_exposure, m_bgType; };
			/* 5*/ struct { float m_metalOrSpec, m_unused5[3]; };
			/* 6*/ struct { float m_doDiffuse, m_doSpecular, m_doDiffuseIbl, m_doSpecularIbl; };
			/* 7*/ struct { float m_cameraPos[3], m_unused7[1]; };
			/* 8*/ struct { float m_rgbDiff[4]; };
			/* 9*/ struct { float m_rgbSpec[4]; };
			/*10*/ struct { float m_lightDir[3], m_unused10[1]; };
			/*11*/ struct { float m_lightCol[3], m_unused11[1]; };
		};

		float m_params[NumVec4*4];
	};

	bgfx::UniformHandle u_params;
};

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
		Bolonga,
		Kyoto,

		Count
	};

	void load(const char* _name)
	{
		char filePath[512];

		bx::snprintf(filePath, BX_COUNTOF(filePath), "textures/%s_lod.dds", _name);
		m_tex = loadTexture(filePath, BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP|BGFX_TEXTURE_W_CLAMP);

		bx::snprintf(filePath, BX_COUNTOF(filePath), "textures/%s_irr.dds", _name);
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

struct Camera
{
	Camera()
	{
		reset();
	}

	void reset()
	{
		m_target.curr[0] = 0.0f;
		m_target.curr[1] = 0.0f;
		m_target.curr[2] = 0.0f;
		m_target.dest[0] = 0.0f;
		m_target.dest[1] = 0.0f;
		m_target.dest[2] = 0.0f;

		m_pos.curr[0] =  0.0f;
		m_pos.curr[1] =  0.0f;
		m_pos.curr[2] = -3.0f;
		m_pos.dest[0] =  0.0f;
		m_pos.dest[1] =  0.0f;
		m_pos.dest[2] = -3.0f;

		m_orbit[0] = 0.0f;
		m_orbit[1] = 0.0f;
	}

	void mtxLookAt(float* _outViewMtx)
	{
		bx::mtxLookAt(_outViewMtx, m_pos.curr, m_target.curr);
	}

	void orbit(float _dx, float _dy)
	{
		m_orbit[0] += _dx;
		m_orbit[1] += _dy;
	}

	void dolly(float _dz)
	{
		const float cnear = 1.0f;
		const float cfar  = 10.0f;

		const float toTarget[3] =
		{
			m_target.dest[0] - m_pos.dest[0],
			m_target.dest[1] - m_pos.dest[1],
			m_target.dest[2] - m_pos.dest[2],
		};
		const float toTargetLen = bx::vec3Length(toTarget);
		const float invToTargetLen = 1.0f/(toTargetLen+FLT_MIN);
		const float toTargetNorm[3] =
		{
			toTarget[0]*invToTargetLen,
			toTarget[1]*invToTargetLen,
			toTarget[2]*invToTargetLen,
		};

		float delta = toTargetLen*_dz;
		float newLen = toTargetLen + delta;
		if ( (cnear < newLen || _dz < 0.0f)
		&&   (newLen < cfar  || _dz > 0.0f) )
		{
			m_pos.dest[0] += toTargetNorm[0]*delta;
			m_pos.dest[1] += toTargetNorm[1]*delta;
			m_pos.dest[2] += toTargetNorm[2]*delta;
		}
	}

	void consumeOrbit(float _amount)
	{
		float consume[2];
		consume[0] = m_orbit[0]*_amount;
		consume[1] = m_orbit[1]*_amount;
		m_orbit[0] -= consume[0];
		m_orbit[1] -= consume[1];

		const float toPos[3] =
		{
			m_pos.curr[0] - m_target.curr[0],
			m_pos.curr[1] - m_target.curr[1],
			m_pos.curr[2] - m_target.curr[2],
		};
		const float toPosLen = bx::vec3Length(toPos);
		const float invToPosLen = 1.0f/(toPosLen+FLT_MIN);
		const float toPosNorm[3] =
		{
			toPos[0]*invToPosLen,
			toPos[1]*invToPosLen,
			toPos[2]*invToPosLen,
		};

		float ll[2];
		latLongFromVec(ll[0], ll[1], toPosNorm);
		ll[0] += consume[0];
		ll[1] -= consume[1];
		ll[1] = bx::fclamp(ll[1], 0.02f, 0.98f);

		float tmp[3];
		vecFromLatLong(tmp, ll[0], ll[1]);

		float diff[3];
		diff[0] = (tmp[0]-toPosNorm[0])*toPosLen;
		diff[1] = (tmp[1]-toPosNorm[1])*toPosLen;
		diff[2] = (tmp[2]-toPosNorm[2])*toPosLen;

		m_pos.curr[0] += diff[0];
		m_pos.curr[1] += diff[1];
		m_pos.curr[2] += diff[2];
		m_pos.dest[0] += diff[0];
		m_pos.dest[1] += diff[1];
		m_pos.dest[2] += diff[2];
	}

	void update(float _dt)
	{
		const float amount = bx::fmin(_dt/0.12f, 1.0f);

		consumeOrbit(amount);

		m_target.curr[0] = bx::flerp(m_target.curr[0], m_target.dest[0], amount);
		m_target.curr[1] = bx::flerp(m_target.curr[1], m_target.dest[1], amount);
		m_target.curr[2] = bx::flerp(m_target.curr[2], m_target.dest[2], amount);
		m_pos.curr[0] = bx::flerp(m_pos.curr[0], m_pos.dest[0], amount);
		m_pos.curr[1] = bx::flerp(m_pos.curr[1], m_pos.dest[1], amount);
		m_pos.curr[2] = bx::flerp(m_pos.curr[2], m_pos.dest[2], amount);
	}

	void envViewMtx(float* _mtx)
	{
		const float toTarget[3] =
		{
			m_target.curr[0] - m_pos.curr[0],
			m_target.curr[1] - m_pos.curr[1],
			m_target.curr[2] - m_pos.curr[2],
		};

		const float toTargetLen = bx::vec3Length(toTarget);
		const float invToTargetLen = 1.0f/(toTargetLen+FLT_MIN);
		const float toTargetNorm[3] =
		{
			toTarget[0]*invToTargetLen,
			toTarget[1]*invToTargetLen,
			toTarget[2]*invToTargetLen,
		};

		float tmp[3];
		const float fakeUp[3] = { 0.0f, 1.0f, 0.0f };

		float right[3];
		bx::vec3Cross(tmp, fakeUp, toTargetNorm);
		bx::vec3Norm(right, tmp);

		float up[3];
		bx::vec3Cross(tmp, toTargetNorm, right);
		bx::vec3Norm(up, tmp);

		_mtx[ 0] = right[0];
		_mtx[ 1] = right[1];
		_mtx[ 2] = right[2];
		_mtx[ 3] = 0.0f;
		_mtx[ 4] = up[0];
		_mtx[ 5] = up[1];
		_mtx[ 6] = up[2];
		_mtx[ 7] = 0.0f;
		_mtx[ 8] = toTargetNorm[0];
		_mtx[ 9] = toTargetNorm[1];
		_mtx[10] = toTargetNorm[2];
		_mtx[11] = 0.0f;
		_mtx[12] = 0.0f;
		_mtx[13] = 0.0f;
		_mtx[14] = 0.0f;
		_mtx[15] = 1.0f;
	}

	static inline void vecFromLatLong(float _vec[3], float _u, float _v)
	{
		const float phi   = _u * 2.0f*bx::pi;
		const float theta = _v * bx::pi;

		const float st = bx::fsin(theta);
		const float sp = bx::fsin(phi);
		const float ct = bx::fcos(theta);
		const float cp = bx::fcos(phi);

		_vec[0] = -st*sp;
		_vec[1] = ct;
		_vec[2] = -st*cp;
	}

	static inline void latLongFromVec(float& _u, float& _v, const float _vec[3])
	{
		const float phi = atan2f(_vec[0], _vec[2]);
		const float theta = acosf(_vec[1]);

		_u = (bx::pi + phi)*bx::invPi*0.5f;
		_v = theta*bx::invPi;
	}

	struct Interp3f
	{
		float curr[3];
		float dest[3];
	};

	Interp3f m_target;
	Interp3f m_pos;
	float m_orbit[2];
};

struct Mouse
{
	Mouse()
		: m_dx(0.0f)
		, m_dy(0.0f)
		, m_prevMx(0.0f)
		, m_prevMy(0.0f)
		, m_scroll(0)
		, m_scrollPrev(0)
	{
	}

	void update(float _mx, float _my, int32_t _mz, uint32_t _width, uint32_t _height)
	{
		const float widthf  = float(int32_t(_width));
		const float heightf = float(int32_t(_height));

		// Delta movement.
		m_dx = float(_mx - m_prevMx)/widthf;
		m_dy = float(_my - m_prevMy)/heightf;

		m_prevMx = _mx;
		m_prevMy = _my;

		// Scroll.
		m_scroll = _mz - m_scrollPrev;
		m_scrollPrev = _mz;
	}

	float m_dx; // Screen space.
	float m_dy;
	float m_prevMx;
	float m_prevMy;
	int32_t m_scroll;
	int32_t m_scrollPrev;
};

int _main_(int _argc, char** _argv)
{
	Args args(_argc, _argv);

	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset  = 0
		| BGFX_RESET_VSYNC
		| BGFX_RESET_MSAA_X16
		;

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
	Uniforms uniforms;
	uniforms.init();

	// Vertex declarations.
	PosColorTexCoord0Vertex::init();

	LightProbe lightProbes[LightProbe::Count];
	lightProbes[LightProbe::Bolonga].load("bolonga");
	lightProbes[LightProbe::Kyoto  ].load("kyoto");
	LightProbe::Enum currentLightProbe = LightProbe::Bolonga;

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

	Mesh* meshOrb;
	meshOrb = meshLoad("meshes/orb.bin");

	Camera camera;
	Mouse mouse;

	struct Settings
	{
		Settings()
		{
			m_envRotCurr = 0.0f;
			m_envRotDest = 0.0f;
			m_lightDir[0] = -0.8f;
			m_lightDir[1] = 0.2f;
			m_lightDir[2] = -0.5f;
			m_lightCol[0] = 1.0f;
			m_lightCol[1] = 1.0f;
			m_lightCol[2] = 1.0f;
			m_glossiness = 0.7f;
			m_exposure = 0.0f;
			m_bgType = 3.0f;
			m_radianceSlider = 2.0f;
			m_reflectivity = 0.85f;
			m_rgbDiff[0] = 1.0f;
			m_rgbDiff[1] = 1.0f;
			m_rgbDiff[2] = 1.0f;
			m_rgbSpec[0] = 1.0f;
			m_rgbSpec[1] = 1.0f;
			m_rgbSpec[2] = 1.0f;
			m_lod = 0.0f;
			m_doDiffuse = false;
			m_doSpecular = false;
			m_doDiffuseIbl = true;
			m_doSpecularIbl = true;
			m_showLightColorWheel = true;
			m_showDiffColorWheel = true;
			m_showSpecColorWheel = true;
			m_metalOrSpec = 0;
			m_meshSelection = 0;
			m_crossCubemapPreview = ImguiCubemap::Latlong;
		}

		float m_envRotCurr;
		float m_envRotDest;
		float m_lightDir[3];
		float m_lightCol[3];
		float m_glossiness;
		float m_exposure;
		float m_radianceSlider;
		float m_bgType;
		float m_reflectivity;
		float m_rgbDiff[3];
		float m_rgbSpec[3];
		float m_lod;
		bool m_doDiffuse;
		bool m_doSpecular;
		bool m_doDiffuseIbl;
		bool m_doSpecularIbl;
		bool m_showLightColorWheel;
		bool m_showDiffColorWheel;
		bool m_showSpecColorWheel;
		uint8_t m_metalOrSpec;
		uint8_t m_meshSelection;
		ImguiCubemap::Enum m_crossCubemapPreview;
	};

	Settings settings;

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
		imguiBeginScrollArea("", width - 256 - 10, 10, 256, 700, &rightScrollArea);

		imguiLabel("Environment light:");
		imguiIndent();
		imguiBool("IBL Diffuse",  settings.m_doDiffuseIbl);
		imguiBool("IBL Specular", settings.m_doSpecularIbl);
		currentLightProbe = LightProbe::Enum(imguiTabs(currentLightProbe, true, ImguiAlign::LeftIndented, 16, 2, 2
													   , "Bolonga"
													   , "Kyoto"
													   ) );
		if (imguiCube(lightProbes[currentLightProbe].m_tex, settings.m_lod, settings.m_crossCubemapPreview, true) )
		{
			settings.m_crossCubemapPreview = ImguiCubemap::Enum( (settings.m_crossCubemapPreview+1) % ImguiCubemap::Count);
		}
		imguiSlider("Texture LOD", settings.m_lod, 0.0f, 10.1f, 0.1f);
		imguiUnindent();

		imguiSeparator(8);
		imguiLabel("Directional light:");
		imguiIndent();
		imguiBool("Diffuse",  settings.m_doDiffuse);
		imguiBool("Specular", settings.m_doSpecular);
		const bool doDirectLighting = settings.m_doDiffuse || settings.m_doSpecular;
		imguiSlider("Light direction X", settings.m_lightDir[0], -1.0f, 1.0f, 0.1f, doDirectLighting);
		imguiSlider("Light direction Y", settings.m_lightDir[1], -1.0f, 1.0f, 0.1f, doDirectLighting);
		imguiSlider("Light direction Z", settings.m_lightDir[2], -1.0f, 1.0f, 0.1f, doDirectLighting);
		imguiColorWheel("Color:", settings.m_lightCol, settings.m_showLightColorWheel, 0.6f, doDirectLighting);
		imguiUnindent();

		imguiSeparator(8);
		imguiLabel("Background:");
		imguiIndent();
		{
			int32_t selection;
			if      (0.0f == settings.m_bgType) { selection = 0; }
			else if (7.0f == settings.m_bgType) { selection = 2; }
			else                                { selection = 1; }
			selection = imguiTabs(selection, true, ImguiAlign::LeftIndented, 16, 2, 3
								 , "Skybox"
								 , "Radiance"
								 , "Irradiance"
								 );
			if      (0 == selection) { settings.m_bgType = 0.0f; }
			else if (2 == selection) { settings.m_bgType = 7.0f; }
			else                     { settings.m_bgType = settings.m_radianceSlider; }
			const bool isRadiance = (selection == 1);
			imguiSlider("Mip level", settings.m_radianceSlider, 1.0f, 6.0f, 0.1f, isRadiance);
		}
		imguiUnindent();

		imguiSeparator(8);
		imguiLabel("Post processing:");
		imguiIndent();
		imguiSlider("Exposure", settings.m_exposure, -4.0f, 4.0f, 0.1f);
		imguiUnindent();

		imguiSeparator();

		imguiEndScrollArea();

		imguiBeginScrollArea("", 10, 70, 256, 636, &leftScrollArea);

		imguiLabel("Mesh:");
		imguiIndent();
		settings.m_meshSelection = imguiChoose(settings.m_meshSelection, "Bunny", "Orbs");
		imguiUnindent();

		const bool isBunny = (0 == settings.m_meshSelection);
		if (!isBunny)
		{
			settings.m_metalOrSpec = 0;
		}

		imguiSeparator(4);
		imguiLabel("Workflow:");
		imguiIndent();
		if (imguiCheck("Metalness", 0 == settings.m_metalOrSpec, isBunny) ) { settings.m_metalOrSpec = 0; }
		if (imguiCheck("Specular",  1 == settings.m_metalOrSpec, isBunny) ) { settings.m_metalOrSpec = 1; }
		imguiUnindent();

		imguiSeparator(4);
		imguiLabel("Material:");
		imguiIndent();
		imguiSlider("Glossiness", settings.m_glossiness, 0.0f, 1.0f, 0.01f, isBunny);
		imguiSlider(0 == settings.m_metalOrSpec ? "Metalness" : "Diffuse - Specular", settings.m_reflectivity, 0.0f, 1.0f, 0.01f, isBunny);
		imguiUnindent();

		imguiColorWheel("Diffuse:", &settings.m_rgbDiff[0], settings.m_showDiffColorWheel, 0.7f);
		imguiSeparator();
		imguiColorWheel("Specular:", &settings.m_rgbSpec[0], settings.m_showSpecColorWheel, 0.7f, (1 == settings.m_metalOrSpec) && isBunny);

		imguiEndScrollArea();

		imguiEndFrame();

		uniforms.m_glossiness   = settings.m_glossiness;
		uniforms.m_reflectivity = settings.m_reflectivity;
		uniforms.m_exposure     = settings.m_exposure;
		uniforms.m_bgType       = settings.m_bgType;
		uniforms.m_metalOrSpec   = float(settings.m_metalOrSpec);
		uniforms.m_doDiffuse     = float(settings.m_doDiffuse);
		uniforms.m_doSpecular    = float(settings.m_doSpecular);
		uniforms.m_doDiffuseIbl  = float(settings.m_doDiffuseIbl);
		uniforms.m_doSpecularIbl = float(settings.m_doSpecularIbl);
		memcpy(uniforms.m_rgbDiff,  settings.m_rgbDiff,  3*sizeof(float) );
		memcpy(uniforms.m_rgbSpec,  settings.m_rgbSpec,  3*sizeof(float) );
		memcpy(uniforms.m_lightDir, settings.m_lightDir, 3*sizeof(float) );
		memcpy(uniforms.m_lightCol, settings.m_lightCol, 3*sizeof(float) );

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;
		const float deltaTimeSec = float(double(frameTime)/freq);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/18-ibl");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Image-based lighting.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Camera.
		const bool mouseOverGui = imguiMouseOverArea();
		mouse.update(float(mouseState.m_mx), float(mouseState.m_my), mouseState.m_mz, width, height);
		if (!mouseOverGui)
		{
			if (mouseState.m_buttons[entry::MouseButton::Left])
			{
				camera.orbit(mouse.m_dx, mouse.m_dy);
			}
			else if (mouseState.m_buttons[entry::MouseButton::Right])
			{
				camera.dolly(mouse.m_dx + mouse.m_dy);
			}
			else if (mouseState.m_buttons[entry::MouseButton::Middle])
			{
				settings.m_envRotDest += mouse.m_dx*2.0f;
			}
			else if (0 != mouse.m_scroll)
			{
				camera.dolly(float(mouse.m_scroll)*0.05f);
			}
		}
		camera.update(deltaTimeSec);
		memcpy(uniforms.m_cameraPos, camera.m_pos.curr, 3*sizeof(float) );

		// View Transform 0.
		float view[16];
		float proj[16];
		bx::mtxIdentity(view);
		bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);
		bgfx::setViewTransform(0, view, proj);

		// View Transform 1.
		camera.mtxLookAt(view);
		bx::mtxProj(proj, 45.0f, float(width)/float(height), 0.1f, 100.0f);
		bgfx::setViewTransform(1, view, proj);

		// View rect.
		bgfx::setViewRect(0, 0, 0, width, height);
		bgfx::setViewRect(1, 0, 0, width, height);

		// Env rotation.
		const float amount = bx::fmin(deltaTimeSec/0.12f, 1.0f);
		settings.m_envRotCurr = bx::flerp(settings.m_envRotCurr, settings.m_envRotDest, amount);

		// Env mtx.
		float mtxEnvView[16];
		camera.envViewMtx(mtxEnvView);
		float mtxEnvRot[16];
		bx::mtxRotateY(mtxEnvRot, settings.m_envRotCurr);
		bx::mtxMul(uniforms.m_mtx, mtxEnvView, mtxEnvRot); // Used for Skybox.

		// Submit view 0.
		bgfx::setTexture(0, s_texCube, lightProbes[currentLightProbe].m_tex);
		bgfx::setTexture(1, s_texCubeIrr, lightProbes[currentLightProbe].m_texIrr);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width, (float)height, true);
		uniforms.submit();
		bgfx::submit(0, programSky);

		// Submit view 1.
		memcpy(uniforms.m_mtx, mtxEnvRot, 16*sizeof(float)); // Used for IBL.
		if (0 == settings.m_meshSelection)
		{
			// Submit bunny.
			float mtx[16];
			bx::mtxSRT(mtx, 1.0f, 1.0f, 1.0f, 0.0f, bx::pi, 0.0f, 0.0f, -0.80f, 0.0f);
			bgfx::setTexture(0, s_texCube,    lightProbes[currentLightProbe].m_tex);
			bgfx::setTexture(1, s_texCubeIrr, lightProbes[currentLightProbe].m_texIrr);
			uniforms.submit();
			meshSubmit(meshBunny, 1, programMesh, mtx);
		}
		else
		{
			// Submit orbs.
			for (float yy = 0, yend = 5.0f; yy < yend; yy+=1.0f)
			{
				for (float xx = 0, xend = 5.0f; xx < xend; xx+=1.0f)
				{
					const float scale   =  1.2f;
					const float spacing =  2.2f;
					const float yAdj    = -0.8f;

					float mtx[16];
					bx::mtxSRT(mtx
							, scale/xend
							, scale/xend
							, scale/xend
							, 0.0f
							, 0.0f
							, 0.0f
							, 0.0f      + (xx/xend)*spacing - (1.0f + (scale-1.0f)*0.5f - 1.0f/xend)
							, yAdj/yend + (yy/yend)*spacing - (1.0f + (scale-1.0f)*0.5f - 1.0f/yend)
							, 0.0f
							);

					uniforms.m_glossiness   =        xx*(1.0f/xend);
					uniforms.m_reflectivity = (yend-yy)*(1.0f/yend);
					uniforms.m_metalOrSpec = 0.0f;
					uniforms.submit();

					bgfx::setTexture(0, s_texCube,    lightProbes[currentLightProbe].m_tex);
					bgfx::setTexture(1, s_texCubeIrr, lightProbes[currentLightProbe].m_texIrr);
					meshSubmit(meshOrb, 1, programMesh, mtx);
				}
			}
		}

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	meshUnload(meshBunny);
	meshUnload(meshOrb);

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

	uniforms.destroy();

	imguiDestroy();

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
