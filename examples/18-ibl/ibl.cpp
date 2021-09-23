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

namespace
{

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
		bgfx::destroy(u_params);
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
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorTexCoord0Vertex::ms_layout;

void screenSpaceQuad(float _textureWidth, float _textureHeight, bool _originBottomLeft = false, float _width = 1.0f, float _height = 1.0f)
{
	if (3 == bgfx::getAvailTransientVertexBuffer(3, PosColorTexCoord0Vertex::ms_layout) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosColorTexCoord0Vertex::ms_layout);
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

		bgfx::setVertexBuffer(0, &vb);
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
		m_tex = loadTexture(filePath, BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_SAMPLER_W_CLAMP);

		bx::snprintf(filePath, BX_COUNTOF(filePath), "textures/%s_irr.dds", _name);
		m_texIrr = loadTexture(filePath, BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_SAMPLER_W_CLAMP);
	}

	void destroy()
	{
		bgfx::destroy(m_tex);
		bgfx::destroy(m_texIrr);
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
		m_target.curr = { 0.0f, 0.0f, 0.0f };
		m_target.dest = { 0.0f, 0.0f, 0.0f };

		m_pos.curr = { 0.0f, 0.0f, -3.0f };
		m_pos.dest = { 0.0f, 0.0f, -3.0f };

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
		const float cfar  = 100.0f;

		const bx::Vec3 toTarget     = bx::sub(m_target.dest, m_pos.dest);
		const float toTargetLen     = bx::length(toTarget);
		const float invToTargetLen  = 1.0f / (toTargetLen + bx::kFloatMin);
		const bx::Vec3 toTargetNorm = bx::mul(toTarget, invToTargetLen);

		float delta  = toTargetLen * _dz;
		float newLen = toTargetLen + delta;
		if ( (cnear  < newLen || _dz < 0.0f)
		&&   (newLen < cfar   || _dz > 0.0f) )
		{
			m_pos.dest = bx::mad(toTargetNorm, delta, m_pos.dest);
		}
	}

	void consumeOrbit(float _amount)
	{
		float consume[2];
		consume[0] = m_orbit[0] * _amount;
		consume[1] = m_orbit[1] * _amount;
		m_orbit[0] -= consume[0];
		m_orbit[1] -= consume[1];

		const bx::Vec3 toPos     = bx::sub(m_pos.curr, m_target.curr);
		const float toPosLen     = bx::length(toPos);
		const float invToPosLen  = 1.0f / (toPosLen + bx::kFloatMin);
		const bx::Vec3 toPosNorm = bx::mul(toPos, invToPosLen);

		float ll[2];
		bx::toLatLong(&ll[0], &ll[1], toPosNorm);
		ll[0] += consume[0];
		ll[1] -= consume[1];
		ll[1]  = bx::clamp(ll[1], 0.02f, 0.98f);

		const bx::Vec3 tmp  = bx::fromLatLong(ll[0], ll[1]);
		const bx::Vec3 diff = bx::mul(bx::sub(tmp, toPosNorm), toPosLen);

		m_pos.curr = bx::add(m_pos.curr, diff);
		m_pos.dest = bx::add(m_pos.dest, diff);
	}

	void update(float _dt)
	{
		const float amount = bx::min(_dt / 0.12f, 1.0f);

		consumeOrbit(amount);

		m_target.curr = bx::lerp(m_target.curr, m_target.dest, amount);
		m_pos.curr    = bx::lerp(m_pos.curr,    m_pos.dest,    amount);
	}

	void envViewMtx(float* _mtx)
	{
		const bx::Vec3 toTarget     = bx::sub(m_target.curr, m_pos.curr);
		const float toTargetLen     = bx::length(toTarget);
		const float invToTargetLen  = 1.0f / (toTargetLen + bx::kFloatMin);
		const bx::Vec3 toTargetNorm = bx::mul(toTarget, invToTargetLen);

		const bx::Vec3 right = bx::normalize(bx::cross({ 0.0f, 1.0f, 0.0f }, toTargetNorm) );
		const bx::Vec3 up    = bx::normalize(bx::cross(toTargetNorm, right) );

		_mtx[ 0] = right.x;
		_mtx[ 1] = right.y;
		_mtx[ 2] = right.z;
		_mtx[ 3] = 0.0f;
		_mtx[ 4] = up.x;
		_mtx[ 5] = up.y;
		_mtx[ 6] = up.z;
		_mtx[ 7] = 0.0f;
		_mtx[ 8] = toTargetNorm.x;
		_mtx[ 9] = toTargetNorm.y;
		_mtx[10] = toTargetNorm.z;
		_mtx[11] = 0.0f;
		_mtx[12] = 0.0f;
		_mtx[13] = 0.0f;
		_mtx[14] = 0.0f;
		_mtx[15] = 1.0f;
	}

	struct Interp3f
	{
		bx::Vec3 curr = bx::init::None;
		bx::Vec3 dest = bx::init::None;
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
	bool  m_doDiffuse;
	bool  m_doSpecular;
	bool  m_doDiffuseIbl;
	bool  m_doSpecularIbl;
	bool  m_showLightColorWheel;
	bool  m_showDiffColorWheel;
	bool  m_showSpecColorWheel;
	int32_t m_metalOrSpec;
	int32_t m_meshSelection;
};

class ExampleIbl : public entry::AppI
{
public:
	ExampleIbl(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug = BGFX_DEBUG_NONE;
		m_reset  = 0
			| BGFX_RESET_VSYNC
			| BGFX_RESET_MSAA_X16
			;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

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
		m_uniforms.init();

		// Vertex declarations.
		PosColorTexCoord0Vertex::init();

		m_lightProbes[LightProbe::Bolonga].load("bolonga");
		m_lightProbes[LightProbe::Kyoto  ].load("kyoto");
		m_currentLightProbe = LightProbe::Bolonga;

		u_mtx        = bgfx::createUniform("u_mtx",        bgfx::UniformType::Mat4);
		u_params     = bgfx::createUniform("u_params",     bgfx::UniformType::Vec4);
		u_flags      = bgfx::createUniform("u_flags",      bgfx::UniformType::Vec4);
		u_camPos     = bgfx::createUniform("u_camPos",     bgfx::UniformType::Vec4);
		s_texCube    = bgfx::createUniform("s_texCube",    bgfx::UniformType::Sampler);
		s_texCubeIrr = bgfx::createUniform("s_texCubeIrr", bgfx::UniformType::Sampler);

		m_programMesh  = loadProgram("vs_ibl_mesh",   "fs_ibl_mesh");
		m_programSky   = loadProgram("vs_ibl_skybox", "fs_ibl_skybox");

		m_meshBunny = meshLoad("meshes/bunny.bin");
		m_meshOrb = meshLoad("meshes/orb.bin");
	}

	virtual int shutdown() override
	{
		meshUnload(m_meshBunny);
		meshUnload(m_meshOrb);

		// Cleanup.
		bgfx::destroy(m_programMesh);
		bgfx::destroy(m_programSky);

		bgfx::destroy(u_camPos);
		bgfx::destroy(u_flags);
		bgfx::destroy(u_params);
		bgfx::destroy(u_mtx);

		bgfx::destroy(s_texCube);
		bgfx::destroy(s_texCubeIrr);

		for (uint8_t ii = 0; ii < LightProbe::Count; ++ii)
		{
			m_lightProbes[ii].destroy();
		}

		m_uniforms.destroy();

		imguiDestroy();

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

			ImGui::SetNextWindowPos(
				  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_width / 5.0f, m_height - 20.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);
			ImGui::PushItemWidth(180.0f);

			ImGui::Text("Environment light:");
			ImGui::Indent();
			ImGui::Checkbox("IBL Diffuse",  &m_settings.m_doDiffuseIbl);
			ImGui::Checkbox("IBL Specular", &m_settings.m_doSpecularIbl);

			if (ImGui::BeginTabBar("Cubemap", ImGuiTabBarFlags_None) )
			{
				if (ImGui::BeginTabItem("Bolonga") )
				{
					m_currentLightProbe = LightProbe::Bolonga;
					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Kyoto") )
				{
					m_currentLightProbe = LightProbe::Kyoto;
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}

			ImGui::SliderFloat("Texture LOD", &m_settings.m_lod, 0.0f, 10.1f);
			ImGui::Unindent();

			ImGui::Separator();
			ImGui::Text("Directional light:");
			ImGui::Indent();
			ImGui::Checkbox("Diffuse",  &m_settings.m_doDiffuse);
			ImGui::Checkbox("Specular", &m_settings.m_doSpecular);
			const bool doDirectLighting = m_settings.m_doDiffuse || m_settings.m_doSpecular;
			if (doDirectLighting)
			{
				ImGui::SliderFloat("Light direction X", &m_settings.m_lightDir[0], -1.0f, 1.0f);
				ImGui::SliderFloat("Light direction Y", &m_settings.m_lightDir[1], -1.0f, 1.0f);
				ImGui::SliderFloat("Light direction Z", &m_settings.m_lightDir[2], -1.0f, 1.0f);
				ImGui::ColorWheel("Color:", m_settings.m_lightCol, 0.6f);
			}
			ImGui::Unindent();

			ImGui::Separator();
			ImGui::Text("Background:");
			ImGui::Indent();
			{
				if (ImGui::BeginTabBar("CubemapSelection", ImGuiTabBarFlags_None) )
				{
					if (ImGui::BeginTabItem("Irradiance") )
					{
						m_settings.m_bgType = m_settings.m_radianceSlider;
						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Radiance") )
					{
						m_settings.m_bgType = 7.0f;

						ImGui::SliderFloat("Mip level", &m_settings.m_radianceSlider, 1.0f, 6.0f);

						ImGui::EndTabItem();
					}

					if (ImGui::BeginTabItem("Skybox") )
					{
						m_settings.m_bgType = 0.0f;
						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}
			}
			ImGui::Unindent();

			ImGui::Separator();
			ImGui::Text("Post processing:");
			ImGui::Indent();
			ImGui::SliderFloat("Exposure",& m_settings.m_exposure, -4.0f, 4.0f);
			ImGui::Unindent();

			ImGui::PopItemWidth();
			ImGui::End();

			ImGui::SetNextWindowPos(
				  ImVec2(10.0f, 260.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_width / 5.0f, 450.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Mesh"
				, NULL
				, 0
				);

			ImGui::Text("Mesh:");
			ImGui::Indent();
			ImGui::RadioButton("Bunny", &m_settings.m_meshSelection, 0);
			ImGui::RadioButton("Orbs",  &m_settings.m_meshSelection, 1);
			ImGui::Unindent();

			const bool isBunny = (0 == m_settings.m_meshSelection);
			if (!isBunny)
			{
				m_settings.m_metalOrSpec = 0;
			}
			else
			{
				ImGui::Separator();
				ImGui::Text("Workflow:");
				ImGui::Indent();
				ImGui::RadioButton("Metalness", &m_settings.m_metalOrSpec, 0);
				ImGui::RadioButton("Specular", &m_settings.m_metalOrSpec, 1);
				ImGui::Unindent();

				ImGui::Separator();
				ImGui::Text("Material:");
				ImGui::Indent();
				ImGui::PushItemWidth(130.0f);
				ImGui::SliderFloat("Glossiness", &m_settings.m_glossiness, 0.0f, 1.0f);
				ImGui::SliderFloat(0 == m_settings.m_metalOrSpec ? "Metalness" : "Diffuse - Specular", &m_settings.m_reflectivity, 0.0f, 1.0f);
				ImGui::PopItemWidth();
				ImGui::Unindent();
			}


			ImGui::ColorWheel("Diffuse:", &m_settings.m_rgbDiff[0], 0.7f);
			ImGui::Separator();
			if ( (1 == m_settings.m_metalOrSpec) && isBunny )
			{
				ImGui::ColorWheel("Specular:", &m_settings.m_rgbSpec[0], 0.7f);
			}

			ImGui::End();

			imguiEndFrame();

			m_uniforms.m_glossiness   = m_settings.m_glossiness;
			m_uniforms.m_reflectivity = m_settings.m_reflectivity;
			m_uniforms.m_exposure     = m_settings.m_exposure;
			m_uniforms.m_bgType       = m_settings.m_bgType;
			m_uniforms.m_metalOrSpec   = float(m_settings.m_metalOrSpec);
			m_uniforms.m_doDiffuse     = float(m_settings.m_doDiffuse);
			m_uniforms.m_doSpecular    = float(m_settings.m_doSpecular);
			m_uniforms.m_doDiffuseIbl  = float(m_settings.m_doDiffuseIbl);
			m_uniforms.m_doSpecularIbl = float(m_settings.m_doSpecularIbl);
			bx::memCopy(m_uniforms.m_rgbDiff,  m_settings.m_rgbDiff,  3*sizeof(float) );
			bx::memCopy(m_uniforms.m_rgbSpec,  m_settings.m_rgbSpec,  3*sizeof(float) );
			bx::memCopy(m_uniforms.m_lightDir, m_settings.m_lightDir, 3*sizeof(float) );
			bx::memCopy(m_uniforms.m_lightCol, m_settings.m_lightCol, 3*sizeof(float) );

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const float deltaTimeSec = float(double(frameTime)/freq);

			// Camera.
			const bool mouseOverGui = ImGui::MouseOverArea();
			m_mouse.update(float(m_mouseState.m_mx), float(m_mouseState.m_my), m_mouseState.m_mz, m_width, m_height);
			if (!mouseOverGui)
			{
				if (m_mouseState.m_buttons[entry::MouseButton::Left])
				{
					m_camera.orbit(m_mouse.m_dx, m_mouse.m_dy);
				}
				else if (m_mouseState.m_buttons[entry::MouseButton::Right])
				{
					m_camera.dolly(m_mouse.m_dx + m_mouse.m_dy);
				}
				else if (m_mouseState.m_buttons[entry::MouseButton::Middle])
				{
					m_settings.m_envRotDest += m_mouse.m_dx*2.0f;
				}
				else if (0 != m_mouse.m_scroll)
				{
					m_camera.dolly(float(m_mouse.m_scroll)*0.05f);
				}
			}
			m_camera.update(deltaTimeSec);
			bx::memCopy(m_uniforms.m_cameraPos, &m_camera.m_pos.curr.x, 3*sizeof(float) );

			// View Transform 0.
			float view[16];
			bx::mtxIdentity(view);

			const bgfx::Caps* caps = bgfx::getCaps();

			float proj[16];
			bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f, 0.0, caps->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);

			// View Transform 1.
			m_camera.mtxLookAt(view);
			bx::mtxProj(proj, 45.0f, float(m_width)/float(m_height), 0.1f, 100.0f, caps->homogeneousDepth);
			bgfx::setViewTransform(1, view, proj);

			// View rect.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			bgfx::setViewRect(1, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// Env rotation.
			const float amount = bx::min(deltaTimeSec/0.12f, 1.0f);
			m_settings.m_envRotCurr = bx::lerp(m_settings.m_envRotCurr, m_settings.m_envRotDest, amount);

			// Env mtx.
			float mtxEnvView[16];
			m_camera.envViewMtx(mtxEnvView);
			float mtxEnvRot[16];
			bx::mtxRotateY(mtxEnvRot, m_settings.m_envRotCurr);
			bx::mtxMul(m_uniforms.m_mtx, mtxEnvView, mtxEnvRot); // Used for Skybox.

			// Submit view 0.
			bgfx::setTexture(0, s_texCube, m_lightProbes[m_currentLightProbe].m_tex);
			bgfx::setTexture(1, s_texCubeIrr, m_lightProbes[m_currentLightProbe].m_texIrr);
			bgfx::setState(BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A);
			screenSpaceQuad( (float)m_width, (float)m_height, true);
			m_uniforms.submit();
			bgfx::submit(0, m_programSky);

			// Submit view 1.
			bx::memCopy(m_uniforms.m_mtx, mtxEnvRot, 16*sizeof(float)); // Used for IBL.
			if (0 == m_settings.m_meshSelection)
			{
				// Submit bunny.
				float mtx[16];
				bx::mtxSRT(mtx, 1.0f, 1.0f, 1.0f, 0.0f, bx::kPi, 0.0f, 0.0f, -0.80f, 0.0f);
				bgfx::setTexture(0, s_texCube,    m_lightProbes[m_currentLightProbe].m_tex);
				bgfx::setTexture(1, s_texCubeIrr, m_lightProbes[m_currentLightProbe].m_texIrr);
				m_uniforms.submit();
				meshSubmit(m_meshBunny, 1, m_programMesh, mtx);
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

						m_uniforms.m_glossiness   =        xx*(1.0f/xend);
						m_uniforms.m_reflectivity = (yend-yy)*(1.0f/yend);
						m_uniforms.m_metalOrSpec = 0.0f;
						m_uniforms.submit();

						bgfx::setTexture(0, s_texCube,    m_lightProbes[m_currentLightProbe].m_tex);
						bgfx::setTexture(1, s_texCubeIrr, m_lightProbes[m_currentLightProbe].m_texIrr);
						meshSubmit(m_meshOrb, 1, m_programMesh, mtx);
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

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	entry::MouseState m_mouseState;

	Uniforms m_uniforms;

	LightProbe m_lightProbes[LightProbe::Count];
	LightProbe::Enum m_currentLightProbe;

	bgfx::UniformHandle u_mtx;
	bgfx::UniformHandle u_params;
	bgfx::UniformHandle u_flags;
	bgfx::UniformHandle u_camPos;
	bgfx::UniformHandle s_texCube;
	bgfx::UniformHandle s_texCubeIrr;

	bgfx::ProgramHandle m_programMesh;
	bgfx::ProgramHandle m_programSky;

	Mesh* m_meshBunny;
	Mesh* m_meshOrb;
	Camera m_camera;
	Mouse m_mouse;

	Settings m_settings;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleIbl
	, "18-ibl"
	, "Image-based lighting."
	, "https://bkaradzic.github.io/bgfx/examples.html#ibl"
	);
