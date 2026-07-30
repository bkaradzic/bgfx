/*
* Copyright 2026 Mateusz Kozdrowicki. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"

namespace
{

constexpr float kWorldSize = 96.0f; // (km)
constexpr float kAmplitude = 16.0f; // (km)

constexpr float kSunColor[3] = { 1.0f, 0.975f, 0.94f };

constexpr float kSunDiscCos   = 0.9999f;
constexpr float kSunDiscScale = 60.0f;

constexpr uint16_t kTransmittanceW = 256;
constexpr uint16_t kTransmittanceH = 64;

constexpr uint16_t kMultiscatterSz = 32;

constexpr uint16_t kSkyviewW = 192;
constexpr uint16_t kSkyviewH = 108;

constexpr uint16_t kShadowMapSize = 2048;

struct PosNormalVertex
{
	float m_x, m_y, m_z;
	float m_nx, m_ny, m_nz;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,   3, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosNormalVertex::ms_layout;

enum : bgfx::ViewId
{
	kViewTransmittance = 0,
	kViewMultiscatter  = 1,
	kViewSkyview       = 2,
	kViewShadow        = 3,
	kViewSky           = 4,
	kViewTerrain       = 5,
};

class ExampleSky2 : public entry::AppI
{
public:
	ExampleSky2(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
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
		init.platformData.nwh  = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.platformData.ndt  = entry::getNativeDisplayHandle();
		init.platformData.type = entry::getNativeWindowHandleType();
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		bgfx::setDebug(m_debug);

		const bgfx::Caps* caps = bgfx::getCaps();
		m_computeSupported = !!(caps->supported & BGFX_CAPS_COMPUTE);

		if (!m_computeSupported)
		{
			return;
		}

		PosNormalVertex::init();

		u_atmoRayleigh = bgfx::createUniform("u_atmoRayleigh", bgfx::UniformType::Vec4);
		u_atmoMie      = bgfx::createUniform("u_atmoMie",      bgfx::UniformType::Vec4);
		u_atmoOzone    = bgfx::createUniform("u_atmoOzone",    bgfx::UniformType::Vec4);
		u_atmoPlanet   = bgfx::createUniform("u_atmoPlanet",   bgfx::UniformType::Vec4);
		u_atmoGround   = bgfx::createUniform("u_atmoGround",   bgfx::UniformType::Vec4);

		u_atmoParams   = bgfx::createUniform("u_atmo_params",  bgfx::UniformType::Vec4);
		u_atmoParams2  = bgfx::createUniform("u_atmo_params2", bgfx::UniformType::Vec4);

		u_skyParams    = bgfx::createUniform("u_skyParams",      bgfx::UniformType::Vec4);
		u_sunDirection = bgfx::createUniform("u_sunDirection",   bgfx::UniformType::Vec4);
		u_sunRadiance  = bgfx::createUniform("u_sunRadiance",    bgfx::UniformType::Vec4);
		u_invViewProj  = bgfx::createUniform("u_skyInvViewProj", bgfx::UniformType::Mat4);
		u_cameraPos    = bgfx::createUniform("u_cameraPos",      bgfx::UniformType::Vec4);
		u_aerialParams = bgfx::createUniform("u_aerialParams",   bgfx::UniformType::Vec4);

		u_shadowParams  = bgfx::createUniform("u_shadowParams",  bgfx::UniformType::Vec4);
		u_lightViewProj = bgfx::createUniform("u_lightViewProj", bgfx::UniformType::Mat4);
		u_lightMtx      = bgfx::createUniform("u_lightMtx",      bgfx::UniformType::Mat4);

		s_atmoTransmittance = bgfx::createUniform("s_atmo_transmittance", bgfx::UniformType::Sampler);
		s_atmoMultiscatter  = bgfx::createUniform("s_atmo_multiscatter",  bgfx::UniformType::Sampler);
		s_skyView           = bgfx::createUniform("s_sky_view",           bgfx::UniformType::Sampler);
		s_shadowMap         = bgfx::createUniform("s_shadowMap",          bgfx::UniformType::Sampler);

		s_grass = bgfx::createUniform("s_grass", bgfx::UniformType::Sampler);
		s_rock  = bgfx::createUniform("s_rock",  bgfx::UniformType::Sampler);

		m_terrainProgram = loadProgram("vs_sky2", "fs_sky2");
		m_skyProgram     = loadProgram("vs_sky2_bg", "fs_sky2_bg");
		m_shadowProgram  = loadProgram("vs_sky2_shadow", "fs_sky2_shadow");

		m_csTransmittance = bgfx::createProgram(loadShader("cs_atmo_transmittance"), true);
		m_csMultiscatter  = bgfx::createProgram(loadShader("cs_atmo_multiscatter"),  true);
		m_csSkyview       = bgfx::createProgram(loadShader("cs_atmo_skyview"),       true);

		const uint64_t lutFlags = BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP;
		m_transmittanceLut = bgfx::createTexture2D(kTransmittanceW, kTransmittanceH, false, 1, bgfx::TextureFormat::RGBA16F, lutFlags);
		m_multiscatterLut  = bgfx::createTexture2D(kMultiscatterSz, kMultiscatterSz, false, 1, bgfx::TextureFormat::RGBA16F, lutFlags);

		m_skyviewLut = bgfx::createTexture2D(kSkyviewW, kSkyviewH, false, 1, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_COMPUTE_WRITE | BGFX_SAMPLER_V_CLAMP);

		m_shadowColor = bgfx::createTexture2D(kShadowMapSize, kShadowMapSize, false, 1, bgfx::TextureFormat::R32F, BGFX_TEXTURE_RT
			| BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_MIP_POINT
			| BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);

		m_shadowDepth = bgfx::createTexture2D(kShadowMapSize, kShadowMapSize, false, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_WRITE_ONLY);

		bgfx::TextureHandle shadowAttachments[2] = { m_shadowColor, m_shadowDepth };
		m_shadowFb = bgfx::createFrameBuffer(2, shadowAttachments, false);

		// BC1 with mip chains
		m_grassTx = loadTexture("textures/terrain_grass_1k_diff.dds");
		m_rockTx  = loadTexture("textures/terrain_rock_1k_diff.dds");

		bx::mtxIdentity(m_lightMtx);

		buildTerrain();
		buildQuad();

		cameraCreate();
		cameraSetPosition({ -3.0f, 16.0f, 42.0f });
		cameraSetHorizontalAngle(bx::kPi - bx::kPi / 20.0f);
		cameraSetVerticalAngle(-bx::kPi / 12.0f);

		bgfx::setViewClear(kViewShadow, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xffffffff, 1.0f, 0);
		bgfx::setViewClear(kViewSky, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);

		m_frameTime.reset();

		imguiCreate();
	}

	virtual int shutdown() override
	{
		if (!m_computeSupported)
		{
			bgfx::shutdown();

			return 0;
		}

		cameraDestroy();
		imguiDestroy();

		bgfx::destroy(m_terrain_vbh);
		bgfx::destroy(m_terrain_ibh);

		bgfx::destroy(m_quad_vbh);
		bgfx::destroy(m_terrainProgram);
		bgfx::destroy(m_skyProgram);
		bgfx::destroy(m_shadowProgram);
		bgfx::destroy(m_csTransmittance);
		bgfx::destroy(m_csMultiscatter);
		bgfx::destroy(m_csSkyview);

		bgfx::destroy(m_transmittanceLut);
		bgfx::destroy(m_multiscatterLut);
		bgfx::destroy(m_skyviewLut);

		bgfx::destroy(m_shadowFb);
		bgfx::destroy(m_shadowColor);
		bgfx::destroy(m_shadowDepth);

		bgfx::destroy(m_grassTx);
		bgfx::destroy(m_rockTx);

		bgfx::destroy(u_atmoRayleigh);
		bgfx::destroy(u_atmoMie);
		bgfx::destroy(u_atmoOzone);
		bgfx::destroy(u_atmoPlanet);
		bgfx::destroy(u_atmoGround);
		bgfx::destroy(u_atmoParams);
		bgfx::destroy(u_atmoParams2);
		bgfx::destroy(u_skyParams);
		bgfx::destroy(u_sunDirection);
		bgfx::destroy(u_sunRadiance);
		bgfx::destroy(u_invViewProj);
		bgfx::destroy(u_cameraPos);
		bgfx::destroy(u_aerialParams);
		bgfx::destroy(u_shadowParams);
		bgfx::destroy(u_lightViewProj);
		bgfx::destroy(u_lightMtx);

		bgfx::destroy(s_atmoTransmittance);
		bgfx::destroy(s_atmoMultiscatter);
		bgfx::destroy(s_skyView);
		bgfx::destroy(s_shadowMap);
		bgfx::destroy(s_grass);
		bgfx::destroy(s_rock);

		bgfx::shutdown();

		return 0;
	}

	void setAtmosphereUniforms()
	{
		const float rayleigh[4] =
		{
			m_rayleighColor[0] * m_rayleighScale,
			m_rayleighColor[1] * m_rayleighScale,
			m_rayleighColor[2] * m_rayleighScale,
			m_rayleighScaleHeight,
		};
		const float mie[4] = { m_mieScatter, m_mieScatter + m_mieAbsorption, m_mieScaleHeight, m_miePhaseG };
		const float ozone[4] =
		{
			m_ozoneColor[0] * m_ozoneScale,
			m_ozoneColor[1] * m_ozoneScale,
			m_ozoneColor[2] * m_ozoneScale,
			m_multiscatter,
		};
		const float planet[4] = { m_planetRadius, m_planetRadius + m_atmosHeight, m_ozoneCenter, m_ozoneHalf };
		const float ground[4] = { m_groundAlbedo[0], m_groundAlbedo[1], m_groundAlbedo[2], 0.0f };

		bgfx::setUniform(u_atmoRayleigh, rayleigh);
		bgfx::setUniform(u_atmoMie,      mie);
		bgfx::setUniform(u_atmoOzone,    ozone);
		bgfx::setUniform(u_atmoPlanet,   planet);
		bgfx::setUniform(u_atmoGround,   ground);
	}

	void drawComputeUnsupported()
	{
		bgfx::setViewClear(kViewSky, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);
		bgfx::setViewRect(kViewSky, 0, 0, uint16_t(m_width), uint16_t(m_height) );
		bgfx::touch(kViewSky);

		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 0, 0x04, " Compute is not supported.");
	}

	void drawPanel()
	{
		ImGui::SetNextWindowPos(ImVec2(m_width - 340.0f, 10.0f), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(330.0f, 480.0f), ImGuiCond_FirstUseEver);
		ImGui::Begin("Settings");

		ImGui::SeparatorText("Sun");
		ImGui::SliderFloat("Elevation", &m_sunElevationDeg, -10.0f, 89.0f);
		ImGui::SliderFloat("Azimuth",   &m_sunAzimuthDeg, -180.0f, 180.0f);
		ImGui::SliderFloat("Intensity", &m_sunIntensity, 0.0f, 30.0f);
		ImGui::Checkbox("Shadow mapping", &m_shadowsEnabled);

		ImGui::SeparatorText("Rayleigh");
		ImGui::ColorEdit3("Ray color", m_rayleighColor);
		ImGui::SliderFloat("Ray scale",  &m_rayleighScale, 0.0f, 0.1f, "%.5f");
		ImGui::SliderFloat("Ray height", &m_rayleighScaleHeight, 0.5f, 20.0f);

		ImGui::SeparatorText("Mie");
		ImGui::SliderFloat("Mie scatter", &m_mieScatter, 0.0f, 0.02f, "%.5f");
		ImGui::SliderFloat("Mie absorb",  &m_mieAbsorption, 0.0f, 0.02f, "%.5f");
		ImGui::SliderFloat("Mie height",  &m_mieScaleHeight, 0.2f, 8.0f);
		ImGui::SliderFloat("Mie g",       &m_miePhaseG, 0.0f, 0.99f);

		ImGui::SeparatorText("Ozone");
		ImGui::ColorEdit3("Ozone color", m_ozoneColor);
		ImGui::SliderFloat("Ozone scale",  &m_ozoneScale, 0.0f, 0.01f, "%.5f");

		ImGui::SeparatorText("Planet");
		ImGui::SliderFloat("Radius",       &m_planetRadius, 1000.0f, 12000.0f);
		ImGui::SliderFloat("Atmos height", &m_atmosHeight, 10.0f, 200.0f);
		ImGui::ColorEdit3("Ground",        m_groundAlbedo);
		ImGui::SliderFloat("Multiscatter", &m_multiscatter, 0.0f, 5.0f);

		ImGui::SeparatorText("Aerial perspective");
		ImGui::SliderFloat("Inscatter", &m_aerialPerspectiveInscatter, 0.0f, 8.0f);
		ImGui::SliderFloat("Density",   &m_aerialPerspectiveDensity, 0.0f, 8.0f);
		ImGui::SliderFloat("Ambient",   &m_aerialPerspectiveambientStrength, 0.0f, 4.0f);

		ImGui::End();
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			if (!m_computeSupported)
			{
				drawComputeUnsupported();

				bgfx::frame();

				return true;
			}

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
			drawPanel();

			imguiEndFrame();

			m_frameTime.frame();
			const float deltaTime = bx::toSeconds<float>(m_frameTime.getDeltaTime());

			cameraUpdate(deltaTime, m_mouseState, ImGui::MouseOverArea());

			const float elevation = bx::toRad(m_sunElevationDeg);
			const float azimuth   = bx::toRad(m_sunAzimuthDeg);
			const bx::Vec3 toSun =
			{
				bx::cos(elevation) * bx::sin(azimuth),
				bx::sin(elevation),
				bx::cos(elevation) * bx::cos(azimuth),
			};
			const float sunDir[4]    = { -toSun.x, -toSun.y, -toSun.z, 0.0f };
			const float sunCosZenith = toSun.y;

			const bx::Vec3 camPos     = cameraGetPosition();
			const float    viewRadius = m_planetRadius + bx::max(camPos.y, 0.001f);

			const float sunRadiance[4] =
			{
				kSunColor[0] * m_sunIntensity,
				kSunColor[1] * m_sunIntensity,
				kSunColor[2] * m_sunIntensity,
				0.0f,
			};

			// --- LUT compute ---
			setAtmosphereUniforms();
			bgfx::setImage(0, m_transmittanceLut, 0, bgfx::Access::Write, bgfx::TextureFormat::RGBA16F);
			bgfx::dispatch(kViewTransmittance, m_csTransmittance, kTransmittanceW/8, kTransmittanceH/8, 1);

			setAtmosphereUniforms();
			bgfx::setTexture(0, s_atmoTransmittance, m_transmittanceLut);
			bgfx::setImage(1, m_multiscatterLut, 0, bgfx::Access::Write, bgfx::TextureFormat::RGBA16F);
			bgfx::dispatch(kViewMultiscatter, m_csMultiscatter, kMultiscatterSz/8, kMultiscatterSz/8, 1);

			const float atmoParams2[4] = { sunCosZenith, viewRadius, float(kSkyviewW), float(kSkyviewH) };
			setAtmosphereUniforms();
			bgfx::setUniform(u_atmoParams,  sunRadiance);
			bgfx::setUniform(u_atmoParams2, atmoParams2);
			bgfx::setTexture(0, s_atmoTransmittance, m_transmittanceLut);
			bgfx::setTexture(2, s_atmoMultiscatter,  m_multiscatterLut);
			bgfx::setImage(1, m_skyviewLut, 0, bgfx::Access::Write, bgfx::TextureFormat::RGBA16F);
			bgfx::dispatch(kViewSkyview, m_csSkyview, (kSkyviewW + 7)/8, (kSkyviewH + 7)/8, 1);

			float view[16];
			cameraGetViewMtx(view);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.02f, 400.0f, bgfx::getCaps()->homogeneousDepth);

			float viewProj[16];
			bx::mtxMul(viewProj, view, proj);

			float invViewProj[16];
			bx::mtxInverse(invViewProj, viewProj);

			const float skyParams[4] = { viewRadius, kSunDiscCos, kSunDiscScale, 0.0f };

			// ortho half extent
			const float shadowExtent = 0.8f * kWorldSize;
			const float shadowTexel  = 2.0f * shadowExtent / float(kShadowMapSize);
			const float shadowParams[4] =
			{
				1.0f / float(kShadowMapSize),
				shadowTexel,
				m_shadowsEnabled ? 1.0f : 0.0f,
				0.0f,
			};

			// --- Shadow map ---
			if (m_shadowsEnabled)
			{
				const bx::Vec3 lightDir  = bx::normalize(bx::Vec3{ sunDir[0], sunDir[1], sunDir[2] });
				const bx::Vec3 center    = { 0.0f, kAmplitude * 0.35f, 0.0f };
				const float    lightDist = kWorldSize * 1.2f;
				const bx::Vec3 lightEye  = bx::mad(lightDir, -lightDist, center);
				const bx::Vec3 up = (bx::abs(lightDir.y) > 0.99f)
					? bx::Vec3{ 0.0f, 0.0f, 1.0f }
					: bx::Vec3{ 0.0f, 1.0f, 0.0f };

				float lightView[16];
				bx::mtxLookAt(lightView, lightEye, center, up);

				float lightProj[16];
				bx::mtxOrtho(lightProj, -shadowExtent, shadowExtent, -shadowExtent, shadowExtent, 0.1f, 2.0f*lightDist + 2.0f*kAmplitude, 0.0f, bgfx::getCaps()->homogeneousDepth);

				float lightViewProj[16];
				bx::mtxMul(lightViewProj, lightView, lightProj);

				// bias matrix
				const bool  originBottomLeft = bgfx::getCaps()->originBottomLeft;
				const bool  homogeneousDepth = bgfx::getCaps()->homogeneousDepth;
				const float sy = originBottomLeft ?  0.5f : -0.5f;
				const float sz = homogeneousDepth ?  0.5f :  1.0f;
				const float tz = homogeneousDepth ?  0.5f :  0.0f;
				const float mtxCrop[16] =
				{
					0.5f, 0.0f, 0.0f, 0.0f,
					0.0f, sy,   0.0f, 0.0f,
					0.0f, 0.0f, sz,   0.0f,
					0.5f, 0.5f, tz,   1.0f,
				};

				bx::mtxMul(m_lightMtx, lightViewProj, mtxCrop);

				bgfx::setViewFrameBuffer(kViewShadow, m_shadowFb);
				bgfx::setViewRect(kViewShadow, 0, 0, kShadowMapSize, kShadowMapSize);

				bgfx::setUniform(u_lightViewProj, lightViewProj);
				bgfx::setUniform(u_lightMtx,      m_lightMtx);
				bgfx::setVertexBuffer(0, m_terrain_vbh);
				bgfx::setIndexBuffer(m_terrain_ibh);
				bgfx::setState(BGFX_STATE_WRITE_R | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS);
				bgfx::submit(kViewShadow, m_shadowProgram);
			}

			// --- Sky pass ---
			bgfx::setViewRect(kViewSky, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			setAtmosphereUniforms();
			bgfx::setUniform(u_invViewProj,  invViewProj);
			bgfx::setUniform(u_skyParams,    skyParams);
			bgfx::setUniform(u_sunDirection, sunDir);
			bgfx::setUniform(u_sunRadiance,  sunRadiance);
			bgfx::setTexture(0, s_skyView,           m_skyviewLut);
			bgfx::setTexture(1, s_atmoTransmittance, m_transmittanceLut);
			bgfx::setVertexBuffer(0, m_quad_vbh);
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
			bgfx::submit(kViewSky, m_skyProgram);

			// --- Terrain pass ---
			bgfx::setViewRect(kViewTerrain, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			bgfx::setViewTransform(kViewTerrain, view, proj);

			const float camPos4[4] = { camPos.x, camPos.y, camPos.z, 0.0f };
			const float aerial[4]  = { m_aerialPerspectiveInscatter, m_aerialPerspectiveDensity, m_aerialPerspectiveambientStrength, 0.0f };

			setAtmosphereUniforms();
			bgfx::setUniform(u_sunDirection, sunDir);
			bgfx::setUniform(u_sunRadiance,  sunRadiance);
			bgfx::setUniform(u_cameraPos,    camPos4);
			bgfx::setUniform(u_skyParams,    skyParams);
			bgfx::setUniform(u_aerialParams, aerial);
			bgfx::setUniform(u_shadowParams, shadowParams);
			bgfx::setUniform(u_lightMtx,     m_lightMtx);

			bgfx::setTexture(0, s_atmoTransmittance, m_transmittanceLut);
			bgfx::setTexture(1, s_atmoMultiscatter,  m_multiscatterLut);
			bgfx::setTexture(2, s_skyView,           m_skyviewLut);
			bgfx::setTexture(3, s_grass,             m_grassTx);
			bgfx::setTexture(4, s_rock,              m_rockTx);
			bgfx::setTexture(5, s_shadowMap,         m_shadowColor);

			bgfx::setVertexBuffer(0, m_terrain_vbh);
			bgfx::setIndexBuffer(m_terrain_ibh);

			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_WRITE_Z
				| BGFX_STATE_DEPTH_TEST_LESS
			);

			bgfx::submit(kViewTerrain, m_terrainProgram);

			bgfx::frame();

			return true;
		}

		return false;
	}

	void buildTerrain() {
		bimg::ImageContainer* image = imageLoad("textures/heightmap.exr", bgfx::TextureFormat::R32F);

		const uint32_t w = image->m_width;
		const uint32_t h = image->m_height;
		const float* src = (const float*)image->m_data;

		float hmin = src[0];
		float hmax = src[0];
		for (uint32_t ii = 0, num = w * h; ii < num; ++ii)
		{
			hmin = bx::min(hmin, src[ii]);
			hmax = bx::max(hmax, src[ii]);
		}

		float range = hmax - hmin;
		if (range < 1e-6f)
		{
			range = 1.0f;
		}

		const float cellSize = kWorldSize / float(w - 1);
		const float originX  = -0.5f * kWorldSize;
		const float originZ  = -0.5f * cellSize * float(h - 1);

		const uint32_t numVertices = w * h;
		const bgfx::Memory* vbMem = bgfx::alloc(uint32_t(numVertices * sizeof(PosNormalVertex)));
		PosNormalVertex* vertices = (PosNormalVertex*)vbMem->data;

		for (uint32_t z = 0; z < h; ++z)
		{
			for (uint32_t x = 0; x < w; ++x)
			{
				const float height = (src[z * w + x]) / range * kAmplitude;
				PosNormalVertex& v = vertices[z * w + x];
				v.m_x = originX + float(x) * cellSize;
				v.m_y = height;
				v.m_z = originZ + float(z) * cellSize;
			}
		}

		bimg::imageFree(image);

		for (uint32_t z = 0; z < h; ++z)
		{
			for (uint32_t x = 0; x < w; ++x)
			{
				const uint32_t xl = (x > 0    ) ? x - 1 : x;
				const uint32_t xr = (x < w - 1) ? x + 1 : x;
				const uint32_t zd = (z > 0    ) ? z - 1 : z;
				const uint32_t zu = (z < h - 1) ? z + 1 : z;

				const float hL = vertices[z * w + xl].m_y;
				const float hR = vertices[z * w + xr].m_y;
				const float hD = vertices[zd * w + x].m_y;
				const float hU = vertices[zu * w + x].m_y;

				const float dx = hR - hL;
				const float dz = hU - hD;

				const bx::Vec3 normal = bx::normalize({ -dx, 2.0f * cellSize, -dz });

				PosNormalVertex& v = vertices[z*w + x];
				v.m_nx = normal.x;
				v.m_ny = normal.y;
				v.m_nz = normal.z;
			}
		}

		const uint32_t numIndices = (w - 1) * (h - 1) * 6;
		const bgfx::Memory* ibMem = bgfx::alloc(uint32_t(numIndices * sizeof(uint32_t)));
		uint32_t* indices = (uint32_t*)ibMem->data;

		uint32_t offset = 0;
		for (uint32_t z = 0; z < h - 1; ++z)
		{
			for (uint32_t x = 0; x < w - 1; ++x)
			{
				const uint32_t i0 = z * w + x;
				const uint32_t i1 = z * w + x + 1;
				const uint32_t i2 = (z + 1) * w + x;
				const uint32_t i3 = (z + 1) * w + x + 1;

				indices[offset++] = i0;
				indices[offset++] = i2;
				indices[offset++] = i1;

				indices[offset++] = i1;
				indices[offset++] = i2;
				indices[offset++] = i3;
			}
		}

		m_terrain_vbh = bgfx::createVertexBuffer(vbMem, PosNormalVertex::ms_layout);
		m_terrain_ibh = bgfx::createIndexBuffer(ibMem, BGFX_BUFFER_INDEX32);
	}

	void buildQuad() {
		const bgfx::Memory* mem = bgfx::alloc(6 * sizeof(float) );

		float* pos = (float*)mem->data;

		pos[0] = -1.0f; pos[1] = -1.0f;
		pos[2] =  3.0f; pos[3] = -1.0f;
		pos[4] = -1.0f; pos[5] =  3.0f;

		bgfx::VertexLayout layout;

		layout
			.begin()
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.end();

		m_quad_vbh = bgfx::createVertexBuffer(mem, layout);
	}

	entry::MouseState m_mouseState;

	bgfx::VertexBufferHandle m_quad_vbh;
	bgfx::VertexBufferHandle m_terrain_vbh;
	bgfx::IndexBufferHandle  m_terrain_ibh;

	bgfx::ProgramHandle m_terrainProgram;
	bgfx::ProgramHandle m_skyProgram;
	bgfx::ProgramHandle m_shadowProgram;
	bgfx::ProgramHandle m_csTransmittance;
	bgfx::ProgramHandle m_csMultiscatter;
	bgfx::ProgramHandle m_csSkyview;

	bgfx::TextureHandle m_transmittanceLut;
	bgfx::TextureHandle m_multiscatterLut;
	bgfx::TextureHandle m_skyviewLut;

	bgfx::TextureHandle m_grassTx;
	bgfx::TextureHandle m_rockTx;

	bgfx::TextureHandle     m_shadowColor;
	bgfx::TextureHandle     m_shadowDepth;
	bgfx::FrameBufferHandle m_shadowFb;

	bgfx::UniformHandle u_atmoRayleigh;
	bgfx::UniformHandle u_atmoMie;
	bgfx::UniformHandle u_atmoOzone;
	bgfx::UniformHandle u_atmoPlanet;
	bgfx::UniformHandle u_atmoGround;
	bgfx::UniformHandle u_atmoParams;
	bgfx::UniformHandle u_atmoParams2;
	bgfx::UniformHandle u_skyParams;
	bgfx::UniformHandle u_sunDirection;
	bgfx::UniformHandle u_sunRadiance;
	bgfx::UniformHandle u_invViewProj;
	bgfx::UniformHandle u_cameraPos;
	bgfx::UniformHandle u_aerialParams;
	bgfx::UniformHandle u_shadowParams;
	bgfx::UniformHandle u_lightViewProj;
	bgfx::UniformHandle u_lightMtx;

	bgfx::UniformHandle s_atmoTransmittance;
	bgfx::UniformHandle s_atmoMultiscatter;
	bgfx::UniformHandle s_skyView;
	bgfx::UniformHandle s_shadowMap;
	bgfx::UniformHandle s_grass;
	bgfx::UniformHandle s_rock;

	float m_lightMtx[16];

	FrameTime m_frameTime;

	bool m_computeSupported = true;

	float m_sunElevationDeg = 11.0f;
	float m_sunAzimuthDeg   = 155.0f;
	float m_sunIntensity    = 10.0f;
	bool  m_shadowsEnabled  = true;

	float m_rayleighColor[3]    = { 0.1753f, 0.4096f, 1.0f }; // * scale = earth
	float m_rayleighScale       = 0.0331f;
	float m_rayleighScaleHeight = 8.0f;

	float m_mieScatter     = 0.003996f;
	float m_mieAbsorption  = 0.000444f;
	float m_mieScaleHeight = 1.2f;
	float m_miePhaseG      = 0.8f;

	float m_ozoneColor[3] = { 0.3456f, 1.0f, 0.0452f }; // * scale = earth
	float m_ozoneScale    = 0.001881f;
	float m_multiscatter  = 1.0f;

	float m_planetRadius = 6360.0f;
	float m_atmosHeight  = 100.0f;
	float m_ozoneCenter  = 25.0f;
	float m_ozoneHalf    = 15.0f;
	float m_groundAlbedo[3] = { 0.3f, 0.3f, 0.3f };

	float m_aerialPerspectiveInscatter		 = 1.0f;
	float m_aerialPerspectiveDensity		 = 1.0f;
	float m_aerialPerspectiveambientStrength = 1.0f;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleSky2
	, "53-sky2"
	, "Hillaire sky/atmosphere."
	, "https://bkaradzic.github.io/bgfx/examples.html#sky2"
	);
