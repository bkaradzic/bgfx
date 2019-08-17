/*
 * Copyright 2017 Stanislav Pidhorskyi. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

/*
 * This example demonstrates:
 * - Usage of Perez sky model [1] to render a dynamic sky.
 * - Rendering a mesh with a lightmap, shading of which is driven by the same parameters as the sky.
 *
 * Typically, the sky is rendered using cubemaps or other environment maps.
 * This approach can provide a high-quality sky, but the downside is that the
 * image is static. To achieve daytime changes in sky appearance, there is a need
 * in a dynamic model.
 *
 * Perez "An All-Weather Model for Sky Luminance Distribution" is a simple,
 * but good enough model which is, in essence, a function that
 * interpolates a sky color. As input, it requires several turbidity
 * coefficients, a color at zenith and direction to the sun.
 * Turbidity coefficients are taken from [2], which are computed using more
 * complex physically based models. Color at zenith depends on daytime and can
 * vary depending on many factors.
 *
 * In the code below, there are two tables that contain sky and sun luminance
 * which were computed using code from [3]. Luminance in those tables
 * represents actual scale of light energy that comes from sun compared to
 * the sky.
 *
 * The sky is driven by luminance of the sky, while the material of the
 * landscape is driven by both, the luminance of the sky and the sun. The
 * lightening model is very simple and consists of two parts: directional
 * light and hemisphere light. The first is used for the sun while the second
 * is used for the sky. Additionally, the second part is modulated by a
 * lightmap to achieve ambient occlusion effect.
 *
 * References
 * ==========
 *
 * [1] R. Perez, R. Seals, and J. Michalsky."An All-Weather Model for Sky Luminance Distribution".
 *     Solar Energy, Volume 50, Number 3 (March 1993), pp. 235–245.
 *
 * [2] A. J. Preetham, Peter Shirley, and Brian Smits. "A Practical Analytic Model for Daylight",
 *     Proceedings of the 26th Annual Conference on Computer Graphics and Interactive Techniques,
 *     1999, pp. 91–100.
 *     https://www.cs.utah.edu/~shirley/papers/sunsky/sunsky.pdf
 *
 * [3] E. Lengyel, Game Engine Gems, Volume One. Jones & Bartlett Learning, 2010. pp. 219 - 234
 *
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"
#include "bounds.h"

#include <map>

namespace
{
	// Represents color. Color-space depends on context.
	// In the code below, used to represent color in XYZ, and RGB color-space
	typedef bx::Vec3 Color;

	// HDTV rec. 709 matrix.
	static float M_XYZ2RGB[] =
	{
		 3.240479f, -0.969256f,  0.055648f,
		-1.53715f,   1.875991f, -0.204043f,
		-0.49853f,   0.041556f,  1.057311f,
	};

	// Converts color repesentation from CIE XYZ to RGB color-space.
	Color xyzToRgb(const Color& xyz)
	{
		Color rgb;
		rgb.x = M_XYZ2RGB[0] * xyz.x + M_XYZ2RGB[3] * xyz.y + M_XYZ2RGB[6] * xyz.z;
		rgb.y = M_XYZ2RGB[1] * xyz.x + M_XYZ2RGB[4] * xyz.y + M_XYZ2RGB[7] * xyz.z;
		rgb.z = M_XYZ2RGB[2] * xyz.x + M_XYZ2RGB[5] * xyz.y + M_XYZ2RGB[8] * xyz.z;
		return rgb;
	};


	// Precomputed luminance of sunlight in XYZ colorspace.
	// Computed using code from Game Engine Gems, Volume One, chapter 15. Implementation based on Dr. Richard Bird model.
	// This table is used for piecewise linear interpolation. Transitions from and to 0.0 at sunset and sunrise are highly inaccurate
	static std::map<float, Color> sunLuminanceXYZTable = {
		{  5.0f, {  0.000000f,  0.000000f,  0.000000f } },
		{  7.0f, { 12.703322f, 12.989393f,  9.100411f } },
		{  8.0f, { 13.202644f, 13.597814f, 11.524929f } },
		{  9.0f, { 13.192974f, 13.597458f, 12.264488f } },
		{ 10.0f, { 13.132943f, 13.535914f, 12.560032f } },
		{ 11.0f, { 13.088722f, 13.489535f, 12.692996f } },
		{ 12.0f, { 13.067827f, 13.467483f, 12.745179f } },
		{ 13.0f, { 13.069653f, 13.469413f, 12.740822f } },
		{ 14.0f, { 13.094319f, 13.495428f, 12.678066f } },
		{ 15.0f, { 13.142133f, 13.545483f, 12.526785f } },
		{ 16.0f, { 13.201734f, 13.606017f, 12.188001f } },
		{ 17.0f, { 13.182774f, 13.572725f, 11.311157f } },
		{ 18.0f, { 12.448635f, 12.672520f,  8.267771f } },
		{ 20.0f, {  0.000000f,  0.000000f,  0.000000f } },
	};


	// Precomputed luminance of sky in the zenith point in XYZ colorspace.
	// Computed using code from Game Engine Gems, Volume One, chapter 15. Implementation based on Dr. Richard Bird model.
	// This table is used for piecewise linear interpolation. Day/night transitions are highly inaccurate.
	// The scale of luminance change in Day/night transitions is not preserved.
	// Luminance at night was increased to eliminate need the of HDR render.
	static std::map<float, Color> skyLuminanceXYZTable = {
		{  0.0f, { 0.308f,    0.308f,    0.411f    } },
		{  1.0f, { 0.308f,    0.308f,    0.410f    } },
		{  2.0f, { 0.301f,    0.301f,    0.402f    } },
		{  3.0f, { 0.287f,    0.287f,    0.382f    } },
		{  4.0f, { 0.258f,    0.258f,    0.344f    } },
		{  5.0f, { 0.258f,    0.258f,    0.344f    } },
		{  7.0f, { 0.962851f, 1.000000f, 1.747835f } },
		{  8.0f, { 0.967787f, 1.000000f, 1.776762f } },
		{  9.0f, { 0.970173f, 1.000000f, 1.788413f } },
		{ 10.0f, { 0.971431f, 1.000000f, 1.794102f } },
		{ 11.0f, { 0.972099f, 1.000000f, 1.797096f } },
		{ 12.0f, { 0.972385f, 1.000000f, 1.798389f } },
		{ 13.0f, { 0.972361f, 1.000000f, 1.798278f } },
		{ 14.0f, { 0.972020f, 1.000000f, 1.796740f } },
		{ 15.0f, { 0.971275f, 1.000000f, 1.793407f } },
		{ 16.0f, { 0.969885f, 1.000000f, 1.787078f } },
		{ 17.0f, { 0.967216f, 1.000000f, 1.773758f } },
		{ 18.0f, { 0.961668f, 1.000000f, 1.739891f } },
		{ 20.0f, { 0.264f,    0.264f,    0.352f    } },
		{ 21.0f, { 0.264f,    0.264f,    0.352f    } },
		{ 22.0f, { 0.290f,    0.290f,    0.386f    } },
		{ 23.0f, { 0.303f,    0.303f,    0.404f    } },
	};


	// Turbidity tables. Taken from:
	// A. J. Preetham, P. Shirley, and B. Smits. A Practical Analytic Model for Daylight. SIGGRAPH ’99
	// Coefficients correspond to xyY colorspace.
	static Color ABCDE[] =
	{
		{ -0.2592f, -0.2608f, -1.4630f },
		{  0.0008f,  0.0092f,  0.4275f },
		{  0.2125f,  0.2102f,  5.3251f },
		{ -0.8989f, -1.6537f, -2.5771f },
		{  0.0452f,  0.0529f,  0.3703f },
	};
	static Color ABCDE_t[] =
	{
		{ -0.0193f, -0.0167f,  0.1787f },
		{ -0.0665f, -0.0950f, -0.3554f },
		{ -0.0004f, -0.0079f, -0.0227f },
		{ -0.0641f, -0.0441f,  0.1206f },
		{ -0.0033f, -0.0109f, -0.0670f },
	};


	// Performs piecewise linear interpolation of a Color parameter.
	class DynamicValueController
	{
		typedef Color ValueType;
		typedef std::map<float, ValueType> KeyMap;

	public:
		DynamicValueController()
		{
		}

		~DynamicValueController()
		{
		}

		void SetMap(const KeyMap& keymap)
		{
			m_keyMap = keymap;
		}

		ValueType GetValue(float time) const
		{
			typename KeyMap::const_iterator itUpper = m_keyMap.upper_bound(time + 1e-6f);
			typename KeyMap::const_iterator itLower = itUpper;
			--itLower;

			if (itLower == m_keyMap.end())
			{
				return itUpper->second;
			}

			if (itUpper == m_keyMap.end())
			{
				return itLower->second;
			}

			float lowerTime = itLower->first;
			const ValueType& lowerVal = itLower->second;
			float upperTime = itUpper->first;
			const ValueType& upperVal = itUpper->second;

			if (lowerTime == upperTime)
			{
				return lowerVal;
			}

			return interpolate(lowerTime, lowerVal, upperTime, upperVal, time);
		};

		void Clear()
		{
			m_keyMap.clear();
		};

	private:
		ValueType interpolate(float lowerTime, const ValueType& lowerVal, float upperTime, const ValueType& upperVal, float time) const
		{
			const float tt = (time - lowerTime) / (upperTime - lowerTime);
			const ValueType result = bx::lerp(lowerVal, upperVal, tt);
			return result;
		};

		KeyMap	m_keyMap;
	};

	// Controls sun position according to time, month, and observer's latitude.
	// Sun position computation based on Earth's orbital elements: https://nssdc.gsfc.nasa.gov/planetary/factsheet/earthfact.html
	class SunController
	{
	public:
		enum Month : int
		{
			January = 0,
			February,
			March,
			April,
			May,
			June,
			July,
			August,
			September,
			October,
			November,
			December
		};

		SunController()
			: m_latitude(50.0f)
			, m_month(June)
			, m_eclipticObliquity(bx::toRad(23.4f) )
			, m_delta(0.0f)
		{
			m_northDir = { 1.0f,  0.0f, 0.0f };
			m_sunDir   = { 0.0f, -1.0f, 0.0f };
			m_upDir    = { 0.0f,  1.0f, 0.0f };
		}

		void Update(float _time)
		{
			CalculateSunOrbit();
			UpdateSunPosition(_time - 12.0f);
		}

		bx::Vec3 m_northDir;
		bx::Vec3 m_sunDir;
		bx::Vec3 m_upDir;
		float m_latitude;
		Month m_month;

	private:
		void CalculateSunOrbit()
		{
			float day = 30.0f * m_month + 15.0f;
			float lambda = 280.46f + 0.9856474f * day;
			lambda  = bx::toRad(lambda);
			m_delta = bx::asin(bx::sin(m_eclipticObliquity) * bx::sin(lambda) );
		}

		void UpdateSunPosition(float _hour)
		{
			const float latitude = bx::toRad(m_latitude);
			const float hh = _hour * bx::kPi / 12.0f;
			const float azimuth = bx::atan2(
				  bx::sin(hh)
				, bx::cos(hh) * bx::sin(latitude) - bx::tan(m_delta) * bx::cos(latitude)
				);

			const float altitude = bx::asin(
				bx::sin(latitude) * bx::sin(m_delta) + bx::cos(latitude) * bx::cos(m_delta) * bx::cos(hh)
				);

			const bx::Quaternion rot0 = bx::rotateAxis(m_upDir, -azimuth);
			const bx::Vec3 dir = bx::mul(m_northDir, rot0);
			const bx::Vec3 uxd = bx::cross(m_upDir, dir);

			const bx::Quaternion rot1 = bx::rotateAxis(uxd, altitude);
			m_sunDir = bx::mul(dir, rot1);
		}

		float m_eclipticObliquity;
		float m_delta;
	};

	struct ScreenPosVertex
	{
		float m_x;
		float m_y;

		static void init()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
				.end();
		}

		static bgfx::VertexLayout ms_layout;
	};

	bgfx::VertexLayout ScreenPosVertex::ms_layout;

	// Renders a screen-space grid of triangles.
	// Because of performance reasons, and because sky color is smooth, sky color is computed in vertex shader.
	// 32x32 is a reasonable size for the grid to have smooth enough colors.
	struct ProceduralSky
	{
		void init(int verticalCount, int horizontalCount)
		{
			// Create vertex stream declaration.
			ScreenPosVertex::init();

			m_skyProgram = loadProgram("vs_sky", "fs_sky");
			m_skyProgram_colorBandingFix = loadProgram("vs_sky", "fs_sky_color_banding_fix");

			m_preventBanding = true;

			bx::AllocatorI* allocator = entry::getAllocator();

			ScreenPosVertex* vertices = (ScreenPosVertex*)BX_ALLOC(allocator
				, verticalCount * horizontalCount * sizeof(ScreenPosVertex)
				);

			for (int i = 0; i < verticalCount; i++)
			{
				for (int j = 0; j < horizontalCount; j++)
				{
					ScreenPosVertex& v = vertices[i * verticalCount + j];
					v.m_x = float(j) / (horizontalCount - 1) * 2.0f - 1.0f;
					v.m_y = float(i) / (verticalCount - 1) * 2.0f - 1.0f;
				}
			}

			uint16_t* indices = (uint16_t*)BX_ALLOC(allocator
				, (verticalCount - 1) * (horizontalCount - 1) * 6 * sizeof(uint16_t)
				);

			int k = 0;
			for (int i = 0; i < verticalCount - 1; i++)
			{
				for (int j = 0; j < horizontalCount - 1; j++)
				{
					indices[k++] = (uint16_t)(j + 0 + horizontalCount * (i + 0));
					indices[k++] = (uint16_t)(j + 1 + horizontalCount * (i + 0));
					indices[k++] = (uint16_t)(j + 0 + horizontalCount * (i + 1));

					indices[k++] = (uint16_t)(j + 1 + horizontalCount * (i + 0));
					indices[k++] = (uint16_t)(j + 1 + horizontalCount * (i + 1));
					indices[k++] = (uint16_t)(j + 0 + horizontalCount * (i + 1));
				}
			}

			m_vbh = bgfx::createVertexBuffer(bgfx::copy(vertices, sizeof(ScreenPosVertex) * verticalCount * horizontalCount), ScreenPosVertex::ms_layout);
			m_ibh = bgfx::createIndexBuffer(bgfx::copy(indices, sizeof(uint16_t) * k));

			BX_FREE(allocator, indices);
			BX_FREE(allocator, vertices);
		}

		void shutdown()
		{
			bgfx::destroy(m_ibh);
			bgfx::destroy(m_vbh);
			bgfx::destroy(m_skyProgram);
			bgfx::destroy(m_skyProgram_colorBandingFix);
		}

		void draw()
		{
			bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_DEPTH_TEST_EQUAL);
			bgfx::setIndexBuffer(m_ibh);
			bgfx::setVertexBuffer(0, m_vbh);
			bgfx::submit(0, m_preventBanding ? m_skyProgram_colorBandingFix : m_skyProgram);
		}

		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle m_ibh;

		bgfx::ProgramHandle m_skyProgram;
		bgfx::ProgramHandle m_skyProgram_colorBandingFix;

		bool m_preventBanding;
	};

	class ExampleProceduralSky : public entry::AppI
	{
	public:
		ExampleProceduralSky(const char* _name, const char* _description, const char* _url)
			: entry::AppI(_name, _description, _url)
		{
		}

		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
		{
			Args args(_argc, _argv);

			m_width = _width;
			m_height = _height;
			m_debug = BGFX_DEBUG_NONE;
			m_reset = BGFX_RESET_VSYNC;

			bgfx::Init init;
			init.type     = args.m_type;
			init.vendorId = args.m_pciId;
			init.resolution.width  = m_width;
			init.resolution.height = m_height;
			init.resolution.reset  = m_reset;
			bgfx::init(init);

			// Enable m_debug text.
			bgfx::setDebug(m_debug);

			// Set view 0 clear state.
			bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x000000ff
				, 1.0f
				, 0
				);

			m_sunLuminanceXYZ.SetMap(sunLuminanceXYZTable);
			m_skyLuminanceXYZ.SetMap(skyLuminanceXYZTable);

			m_mesh = meshLoad("meshes/test_scene.bin");

			m_lightmapTexture = loadTexture("textures/lightmap.ktx");

			// Imgui.
			imguiCreate();

			m_timeOffset = bx::getHPCounter();
			m_time = 0.0f;
			m_timeScale = 1.0f;

			s_texLightmap     = bgfx::createUniform("s_texLightmap",     bgfx::UniformType::Sampler);
			u_sunLuminance    = bgfx::createUniform("u_sunLuminance",    bgfx::UniformType::Vec4);
			u_skyLuminanceXYZ = bgfx::createUniform("u_skyLuminanceXYZ", bgfx::UniformType::Vec4);
			u_skyLuminance    = bgfx::createUniform("u_skyLuminance",    bgfx::UniformType::Vec4);
			u_sunDirection    = bgfx::createUniform("u_sunDirection",    bgfx::UniformType::Vec4);
			u_parameters      = bgfx::createUniform("u_parameters",      bgfx::UniformType::Vec4);
			u_perezCoeff      = bgfx::createUniform("u_perezCoeff",      bgfx::UniformType::Vec4, 5);

			m_landscapeProgram = loadProgram("vs_sky_landscape", "fs_sky_landscape");

			m_sky.init(32, 32);

			m_sun.Update(0);

			cameraCreate();

			cameraSetPosition({ 5.0f, 3.0, 0.0f });
			cameraSetVerticalAngle(bx::kPi / 8.0f);
			cameraSetHorizontalAngle(-bx::kPi / 3.0f);

			m_turbidity = 2.15f;
		}

		virtual int shutdown() override
		{
			// Cleanup.
			cameraDestroy();
			imguiDestroy();

			meshUnload(m_mesh);

			m_sky.shutdown();

			bgfx::destroy(s_texLightmap);
			bgfx::destroy(u_sunLuminance);
			bgfx::destroy(u_skyLuminanceXYZ);
			bgfx::destroy(u_skyLuminance);
			bgfx::destroy(u_sunDirection);
			bgfx::destroy(u_parameters);
			bgfx::destroy(u_perezCoeff);

			bgfx::destroy(m_lightmapTexture);
			bgfx::destroy(m_landscapeProgram);

			bgfx::frame();

			// Shutdown bgfx.
			bgfx::shutdown();

			return 0;
		}

		void imgui(float _width)
		{
			ImGui::Begin("ProceduralSky");
			ImGui::SetWindowSize(ImVec2(_width, 200.0f) );
			ImGui::SliderFloat("Time scale", &m_timeScale, 0.0f, 1.0f);
			ImGui::SliderFloat("Time", &m_time, 0.0f, 24.0f);
			ImGui::SliderFloat("Latitude", &m_sun.m_latitude, -90.0f, 90.0f);
			ImGui::SliderFloat("Turbidity", &m_turbidity, 1.9f, 10.0f);
			ImGui::Checkbox("Prevent color banding", &m_sky.m_preventBanding);

			const char* items[] =
			{
				"January",
				"February",
				"March",
				"April",
				"May",
				"June",
				"July",
				"August",
				"September",
				"October",
				"November",
				"December"
			};

			ImGui::Combo("Month", (int*)&m_sun.m_month, items, 12);

			ImGui::End();
		}

		bool update() override
		{
			if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			{
				int64_t now = bx::getHPCounter();
				static int64_t last = now;
				const int64_t frameTime = now - last;
				last = now;
				const double freq = double(bx::getHPFrequency());
				const float deltaTime = float(frameTime / freq);
				m_time += m_timeScale * deltaTime;
				m_time = bx::mod(m_time, 24.0f);
				m_sun.Update(m_time);

				imguiBeginFrame(m_mouseState.m_mx
					, m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left]   ? IMGUI_MBUT_LEFT   : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right]  ? IMGUI_MBUT_RIGHT  : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					, m_mouseState.m_mz
					, uint16_t(m_width)
					, uint16_t(m_height)
					);

				showExampleDialog(this);

				ImGui::SetNextWindowPos(
					  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
					, ImGuiCond_FirstUseEver
					);

				imgui(m_width / 5.0f - 10.0f);

				imguiEndFrame();

				if (!ImGui::MouseOverArea())
				{
					// Update camera.
					cameraUpdate(deltaTime, m_mouseState);
				}

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				float view[16];
				cameraGetViewMtx(view);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 2000.0f, bgfx::getCaps()->homogeneousDepth);

				bgfx::setViewTransform(0, view, proj);

				Color sunLuminanceXYZ = m_sunLuminanceXYZ.GetValue(m_time);
				Color sunLuminanceRGB = xyzToRgb(sunLuminanceXYZ);

				Color skyLuminanceXYZ = m_skyLuminanceXYZ.GetValue(m_time);
				Color skyLuminanceRGB = xyzToRgb(skyLuminanceXYZ);

				bgfx::setUniform(u_sunLuminance,    &sunLuminanceRGB.x);
				bgfx::setUniform(u_skyLuminanceXYZ, &skyLuminanceXYZ.x);
				bgfx::setUniform(u_skyLuminance,    &skyLuminanceRGB.x);

				bgfx::setUniform(u_sunDirection, &m_sun.m_sunDir.x);

				float exposition[4] = { 0.02f, 3.0f, 0.1f, m_time };
				bgfx::setUniform(u_parameters, exposition);

				float perezCoeff[4 * 5];
				computePerezCoeff(m_turbidity, perezCoeff);
				bgfx::setUniform(u_perezCoeff, perezCoeff, 5);

				bgfx::setTexture(0, s_texLightmap, m_lightmapTexture);
				meshSubmit(m_mesh, 0, m_landscapeProgram, NULL);

				m_sky.draw();

				bgfx::frame();

				return true;
			}

			return false;
		}

		void computePerezCoeff(float _turbidity, float* _outPerezCoeff)
		{
			const bx::Vec3 turbidity = { _turbidity, _turbidity, _turbidity };
			for (uint32_t ii = 0; ii < 5; ++ii)
			{
				const bx::Vec3 tmp = bx::mad(ABCDE_t[ii], turbidity, ABCDE[ii]);
				float* out = _outPerezCoeff + 4 * ii;
				bx::store(out, tmp);
				out[3] = 0.0f;
			}
		}

		bgfx::ProgramHandle m_landscapeProgram;
		bgfx::UniformHandle s_texLightmap;
		bgfx::TextureHandle m_lightmapTexture;

		bgfx::UniformHandle u_sunLuminance;
		bgfx::UniformHandle u_skyLuminanceXYZ;
		bgfx::UniformHandle u_skyLuminance;
		bgfx::UniformHandle u_sunDirection;
		bgfx::UniformHandle u_parameters;
		bgfx::UniformHandle u_perezCoeff;

		ProceduralSky m_sky;
		SunController m_sun;

		DynamicValueController m_sunLuminanceXYZ;
		DynamicValueController m_skyLuminanceXYZ;

		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_debug;
		uint32_t m_reset;

		Mesh* m_mesh;

		entry::MouseState m_mouseState;

		float m_time;
		float m_timeScale;
		int64_t m_timeOffset;

		float m_turbidity;
	};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleProceduralSky
	, "36-sky"
	, "Perez dynamic sky model."
	, "https://bkaradzic.github.io/bgfx/examples.html#sky"
	);
