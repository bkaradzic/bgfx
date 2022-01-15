/*
* Copyright 2018 Attila Kocsis. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

/*
 * Reference(s):
 * - ASSAO is a SSAO implementation tuned for scalability and flexibility.
 *   https://web.archive.org/web/20181214222937/https://software.intel.com/en-us/articles/adaptive-screen-space-ambient-occlusion
 *   https://github.com/GameTechDev/ASSAO
 */

#include <common.h>
#include <camera.h>
#include <bgfx_utils.h>
#include <imgui/imgui.h>
#include <bx/rng.h>
#include <bx/os.h>

#define USE_ASSAO 0

namespace
{

// Render passes
#define RENDER_PASS_GBUFFER 0  // GBuffer for normals and albedo
#define RENDER_PASS_COMBINE 1  // Directional light and final result

// Gbuffer has multiple render targets
#define GBUFFER_RT_NORMAL 0
#define GBUFFER_RT_COLOR  1
#define GBUFFER_RT_DEPTH  2

// Random meshes we draw
#define MODEL_COUNT 120  // In this demo, a model is a mesh plus a transform

#define SAMPLER_POINT_CLAMP  (BGFX_SAMPLER_POINT|BGFX_SAMPLER_UVW_CLAMP)
#define SAMPLER_POINT_MIRROR (BGFX_SAMPLER_POINT|BGFX_SAMPLER_UVW_MIRROR)
#define SAMPLER_LINEAR_CLAMP (BGFX_SAMPLER_UVW_CLAMP)

#define SSAO_DEPTH_MIP_LEVELS                       4

	static const char * s_meshPaths[] =
	{
		"meshes/cube.bin",
		"meshes/orb.bin",
		"meshes/column.bin",
		"meshes/bunny_decimated.bin",
		"meshes/tree.bin",
		"meshes/hollowcube.bin"
	};

	static const float s_meshScale[] =
	{
		0.25f,
		0.5f,
		0.05f,
		0.5f,
		0.05f,
		0.25f
	};

	// Vertex layout for our screen space quad (used in deferred rendering)
	struct PosTexCoord0Vertex
	{
		float m_x;
		float m_y;
		float m_z;
		float m_u;
		float m_v;

		static void init()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.end();
		}

		static bgfx::VertexLayout ms_layout;
	};

	bgfx::VertexLayout PosTexCoord0Vertex::ms_layout;

	// Utility function to draw a screen space quad for deferred rendering
	void screenSpaceQuad(float _textureWidth, float _textureHeight, float _texelHalf, bool _originBottomLeft, float _width = 1.0f, float _height = 1.0f)
	{
		if (3 == bgfx::getAvailTransientVertexBuffer(3, PosTexCoord0Vertex::ms_layout))
		{
			bgfx::TransientVertexBuffer vb;
			bgfx::allocTransientVertexBuffer(&vb, 3, PosTexCoord0Vertex::ms_layout);
			PosTexCoord0Vertex* vertex = (PosTexCoord0Vertex*)vb.data;

			const float minx = -_width;
			const float maxx = _width;
			const float miny = 0.0f;
			const float maxy = _height * 2.0f;

			const float texelHalfW = _texelHalf / _textureWidth;
			const float texelHalfH = _texelHalf / _textureHeight;
			const float minu = -1.0f + texelHalfW;
			const float maxu = 1.0f + texelHalfH;

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

	struct Settings
	{
		float   m_radius;                            // [0.0,  ~ ] World (view) space size of the occlusion sphere.
		float   m_shadowMultiplier;                  // [0.0, 5.0] Effect strength linear multiplier
		float   m_shadowPower;                       // [0.5, 5.0] Effect strength pow modifier
		float   m_shadowClamp;                       // [0.0, 1.0] Effect max limit (applied after multiplier but before blur)
		float   m_horizonAngleThreshold;             // [0.0, 0.2] Limits self-shadowing (makes the sampling area less of a hemisphere, more of a spherical cone, to avoid self-shadowing and various artifacts due to low tessellation and depth buffer imprecision, etc.)
		float   m_fadeOutFrom;                       // [0.0,  ~ ] Distance to start start fading out the effect.
		float   m_fadeOutTo;                         // [0.0,  ~ ] Distance at which the effect is faded out.
		int32_t m_qualityLevel;                      // [ -1,  3 ] Effect quality; -1 - lowest (low, half res checkerboard), 0 - low, 1 - medium, 2 - high, 3 - very high / adaptive; each quality level is roughly 2x more costly than the previous, except the q3 which is variable but, in general, above q2.
		float   m_adaptiveQualityLimit;              // [0.0, 1.0] (only for Quality Level 3)
		int32_t m_blurPassCount;                     // [  0,   6] Number of edge-sensitive smart blur passes to apply. Quality 0 is an exception with only one 'dumb' blur pass used.
		float   m_sharpness;                         // [0.0, 1.0] (How much to bleed over edges; 1: not at all, 0.5: half-half; 0.0: completely ignore edges)
		float   m_temporalSupersamplingAngleOffset;  // [0.0,  PI] Used to rotate sampling kernel; If using temporal AA / supersampling, suggested to rotate by ( (frame%3)/3.0*PI ) or similar. Kernel is already symmetrical, which is why we use PI and not 2*PI.
		float   m_temporalSupersamplingRadiusOffset; // [0.0, 2.0] Used to scale sampling kernel; If using temporal AA / supersampling, suggested to scale by ( 1.0f + (((frame%3)-1.0)/3.0)*0.1 ) or similar.
		float   m_detailShadowStrength;              // [0.0, 5.0] Used for high-res detail AO using neighboring depth pixels: adds a lot of detail but also reduces temporal stability (adds aliasing).
		bool    m_generateNormals;                   // [true/false] If true normals will be generated from depth.

		Settings()
		{
			m_radius = 1.2f;
			m_shadowMultiplier = 1.0f;
			m_shadowPower = 1.50f;
			m_shadowClamp = 0.98f;
			m_horizonAngleThreshold = 0.06f;
			m_fadeOutFrom = 50.0f;
			m_fadeOutTo = 200.0f;
			m_adaptiveQualityLimit = 0.45f;
			m_qualityLevel = 3;
			m_blurPassCount = 2;
			m_sharpness = 0.98f;
			m_temporalSupersamplingAngleOffset = 0.0f;
			m_temporalSupersamplingRadiusOffset = 1.0f;
			m_detailShadowStrength = 0.5f;
			m_generateNormals = true;
		}
	};

	struct Uniforms
	{
		enum { NumVec4 = 19 };

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
				/*  0    */ struct { float m_viewportPixelSize[2]; float m_halfViewportPixelSize[2]; };
				/*  1    */ struct { float m_depthUnpackConsts[2]; float m_unused0[2]; };
				/*  2    */ struct { float m_ndcToViewMul[2]; float m_ndcToViewAdd[2]; };
				/*  3    */ struct { float m_perPassFullResCoordOffset[2]; float m_perPassFullResUVOffset[2]; };
				/*  4    */ struct { float m_viewport2xPixelSize[2]; float m_viewport2xPixelSize_x_025[2]; };
				/*  5    */ struct { float m_effectRadius; float m_effectShadowStrength; float m_effectShadowPow; float m_effectShadowClamp; };
				/*  6    */ struct { float m_effectFadeOutMul; float m_effectFadeOutAdd; float m_effectHorizonAngleThreshold; float m_effectSamplingRadiusNearLimitRec; };
				/*  7    */ struct { float m_depthPrecisionOffsetMod; float m_negRecEffectRadius; float m_loadCounterAvgDiv; float m_adaptiveSampleCountLimit; };
				/*  8    */ struct { float m_invSharpness; float m_passIndex; float m_quarterResPixelSize[2]; };
				/*  9-13 */ struct { float m_patternRotScaleMatrices[5][4]; };
				/* 14    */ struct { float m_normalsUnpackMul; float m_normalsUnpackAdd; float m_detailAOStrength; float m_layer; };
				/* 15-18 */ struct { float m_normalsWorldToViewspaceMatrix[16]; };
			};

			float m_params[NumVec4 * 4];
		};

		bgfx::UniformHandle u_params;
	};

	void vec2Set(float* _v, float _x, float _y)
	{
		_v[0] = _x;
		_v[1] = _y;
	}

	void vec4Set(float* _v, float _x, float _y, float _z, float _w)
	{
		_v[0] = _x;
		_v[1] = _y;
		_v[2] = _z;
		_v[3] = _w;
	}

	void vec4iSet(int32_t* _v, int32_t _x, int32_t _y, int32_t _z, int32_t _w)
	{
		_v[0] = _x;
		_v[1] = _y;
		_v[2] = _z;
		_v[3] = _w;
	}

	static const int32_t cMaxBlurPassCount = 6;

	class ExampleASSAO : public entry::AppI
	{
	public:
		ExampleASSAO(const char* _name, const char* _description, const char* _url)
			: entry::AppI(_name, _description, _url)
			, m_currFrame(UINT32_MAX)
			, m_enableSSAO(true)
			, m_enableTexturing(true)
			, m_texelHalf(0.0f)
			, m_framebufferGutter(true)
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
			init.type = args.m_type;

			init.vendorId = args.m_pciId;
			init.resolution.width = m_width;
			init.resolution.height = m_height;
			init.resolution.reset = m_reset;
			bgfx::init(init);

			// Enable debug text.
			bgfx::setDebug(m_debug);

			// Labeling for renderdoc captures, etc
			bgfx::setViewName(RENDER_PASS_GBUFFER, "gbuffer");
			bgfx::setViewName(RENDER_PASS_COMBINE, "post combine");

			// Set up screen clears
			bgfx::setViewClear(RENDER_PASS_GBUFFER
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0
				, 1.0f
				, 0
			);

			// Create uniforms
			u_combineParams = bgfx::createUniform("u_combineParams", bgfx::UniformType::Vec4, 2);
			u_rect = bgfx::createUniform("u_rect", bgfx::UniformType::Vec4);  // viewport/scissor rect for compute
			m_uniforms.init();

			// Create texture sampler uniforms (used when we bind textures)
			s_normal = bgfx::createUniform("s_normal", bgfx::UniformType::Sampler);  // Normal gbuffer
			s_depth  = bgfx::createUniform("s_depth",  bgfx::UniformType::Sampler);  // Normal gbuffer
			s_color  = bgfx::createUniform("s_color",  bgfx::UniformType::Sampler);  // Color (albedo) gbuffer
			s_albedo = bgfx::createUniform("s_albedo", bgfx::UniformType::Sampler);

			s_ao                         = bgfx::createUniform("s_ao", bgfx::UniformType::Sampler);
			s_blurInput                  = bgfx::createUniform("s_blurInput", bgfx::UniformType::Sampler);
			s_finalSSAO                  = bgfx::createUniform("s_finalSSAO", bgfx::UniformType::Sampler);
			s_depthSource                = bgfx::createUniform("s_depthSource", bgfx::UniformType::Sampler);
			s_viewspaceDepthSource       = bgfx::createUniform("s_viewspaceDepthSource", bgfx::UniformType::Sampler);
			s_viewspaceDepthSourceMirror = bgfx::createUniform("s_viewspaceDepthSourceMirror", bgfx::UniformType::Sampler);
			s_importanceMap              = bgfx::createUniform("s_importanceMap", bgfx::UniformType::Sampler);

			// Create program from shaders.
			m_gbufferProgram = loadProgram("vs_assao_gbuffer", "fs_assao_gbuffer");  // Gbuffer
			m_combineProgram = loadProgram("vs_assao", "fs_assao_deferred_combine");

			m_prepareDepthsProgram               = loadProgram("cs_assao_prepare_depths", NULL);
			m_prepareDepthsAndNormalsProgram     = loadProgram("cs_assao_prepare_depths_and_normals", NULL);
			m_prepareDepthsHalfProgram           = loadProgram("cs_assao_prepare_depths_half", NULL);
			m_prepareDepthsAndNormalsHalfProgram = loadProgram("cs_assao_prepare_depths_and_normals_half", NULL);
			m_prepareDepthMipProgram             = loadProgram("cs_assao_prepare_depth_mip", NULL);
			m_generateQ0Program                  = loadProgram("cs_assao_generate_q0", NULL);
			m_generateQ1Program                  = loadProgram("cs_assao_generate_q1", NULL);
			m_generateQ2Program                  = loadProgram("cs_assao_generate_q2", NULL);
			m_generateQ3Program                  = loadProgram("cs_assao_generate_q3", NULL);
			m_generateQ3BaseProgram              = loadProgram("cs_assao_generate_q3base", NULL);
			m_smartBlurProgram                   = loadProgram("cs_assao_smart_blur", NULL);
			m_smartBlurWideProgram               = loadProgram("cs_assao_smart_blur_wide", NULL);
			m_nonSmartBlurProgram                = loadProgram("cs_assao_non_smart_blur", NULL);
			m_applyProgram                       = loadProgram("cs_assao_apply", NULL);
			m_nonSmartApplyProgram               = loadProgram("cs_assao_non_smart_apply", NULL);
			m_nonSmartHalfApplyProgram           = loadProgram("cs_assao_non_smart_half_apply", NULL);
			m_generateImportanceMapProgram       = loadProgram("cs_assao_generate_importance_map", NULL);
			m_postprocessImportanceMapAProgram   = loadProgram("cs_assao_postprocess_importance_map_a", NULL);
			m_postprocessImportanceMapBProgram   = loadProgram("cs_assao_postprocess_importance_map_b", NULL);
			m_loadCounterClearProgram            = loadProgram("cs_assao_load_counter_clear", NULL);

			 // Load some meshes
			for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
			{
				m_meshes[ii] = meshLoad(s_meshPaths[ii]);
			}

			// Randomly create some models
			bx::RngMwc mwc;  // Random number generator
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_models); ++ii)
			{
				Model& model = m_models[ii];

				model.mesh = 1 + mwc.gen() % (BX_COUNTOF(s_meshPaths) - 1);
				model.position[0] = (((mwc.gen() % 256)) - 128.0f) / 20.0f;
				model.position[1] = 0;
				model.position[2] = (((mwc.gen() % 256)) - 128.0f) / 20.0f;
			}

			// Load ground.  We'll just use the cube since I don't have a ground model right now
			m_ground = meshLoad("meshes/cube.bin");

			m_groundTexture = loadTexture("textures/fieldstone-rgba.dds");
			const bgfx::Memory* mem = bgfx::alloc(4);
			bx::memSet(mem->data, 0xc0, 4);
			m_modelTexture = bgfx::createTexture2D(1,1, false, 1, bgfx::TextureFormat::RGBA8, 0,  mem);

			m_recreateFrameBuffers = false;
			createFramebuffers();

			m_loadCounter = bgfx::createDynamicIndexBuffer(1, BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_INDEX32);

			// Vertex layout
			PosTexCoord0Vertex::init();

			// Init camera
			cameraCreate();
			cameraSetPosition({ 0.0f, 1.5f, 0.0f });
			cameraSetVerticalAngle(-0.3f);
			m_fovY = 60.0f;

			// Get renderer capabilities info.
			const bgfx::RendererType::Enum renderer = bgfx::getRendererType();
			m_texelHalf = bgfx::RendererType::Direct3D9 == renderer ? 0.5f : 0.0f;

			imguiCreate();
		}

		int32_t shutdown() override
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
			{
				meshUnload(m_meshes[ii]);
			}

			meshUnload(m_ground);
			bgfx::destroy(m_groundTexture);
			bgfx::destroy(m_modelTexture);

			// Cleanup.
			bgfx::destroy(m_gbufferProgram);
			bgfx::destroy(m_combineProgram);

			bgfx::destroy(m_prepareDepthsProgram);
			bgfx::destroy(m_prepareDepthsAndNormalsProgram);
			bgfx::destroy(m_prepareDepthsHalfProgram);
			bgfx::destroy(m_prepareDepthsAndNormalsHalfProgram);
			bgfx::destroy(m_prepareDepthMipProgram);
			bgfx::destroy(m_generateQ0Program);
			bgfx::destroy(m_generateQ1Program);
			bgfx::destroy(m_generateQ2Program);
			bgfx::destroy(m_generateQ3Program);
			bgfx::destroy(m_generateQ3BaseProgram);
			bgfx::destroy(m_smartBlurProgram);
			bgfx::destroy(m_smartBlurWideProgram);
			bgfx::destroy(m_nonSmartBlurProgram);
			bgfx::destroy(m_applyProgram);
			bgfx::destroy(m_nonSmartApplyProgram);
			bgfx::destroy(m_nonSmartHalfApplyProgram);
			bgfx::destroy(m_generateImportanceMapProgram);
			bgfx::destroy(m_postprocessImportanceMapAProgram);
			bgfx::destroy(m_postprocessImportanceMapBProgram);
			bgfx::destroy(m_loadCounterClearProgram);
			bgfx::destroy(m_combineProgram);

			m_uniforms.destroy();

			bgfx::destroy(u_combineParams);
			bgfx::destroy(u_rect);

			bgfx::destroy(s_normal);
			bgfx::destroy(s_depth);
			bgfx::destroy(s_color);
			bgfx::destroy(s_albedo);
			bgfx::destroy(s_ao);
			bgfx::destroy(s_blurInput);
			bgfx::destroy(s_finalSSAO);
			bgfx::destroy(s_depthSource);
			bgfx::destroy(s_viewspaceDepthSource);
			bgfx::destroy(s_viewspaceDepthSourceMirror);
			bgfx::destroy(s_importanceMap);

			bgfx::destroy(m_loadCounter);
			destroyFramebuffers();

			cameraDestroy();

			imguiDestroy();

			// Shutdown bgfx.
			bgfx::shutdown();

			return 0;
		}

		bool update() override
		{
			if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			{
				// Update frame timer
				int64_t now = bx::getHPCounter();
				static int64_t last = now;
				const int64_t frameTime = now - last;
				last = now;
				const double freq = double(bx::getHPFrequency());
				const float deltaTime = float(frameTime / freq);
				const bgfx::Caps* caps = bgfx::getCaps();

				if (m_size[0] != (int32_t)m_width  + 2*m_border
				||  m_size[1] != (int32_t)m_height + 2*m_border
				||  m_recreateFrameBuffers)
				{
					destroyFramebuffers();
					createFramebuffers();
					m_recreateFrameBuffers = false;
				}

				// Update camera
				cameraUpdate(deltaTime*0.15f, m_mouseState, ImGui::MouseOverArea() );

				// Set up matrices for gbuffer
				cameraGetViewMtx(m_view);

				bx::mtxProj(m_proj, m_fovY, float(m_size[0]) / float(m_size[1]), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
				bx::mtxProj(m_proj2, m_fovY, float(m_size[0]) / float(m_size[1]), 0.1f, 100.0f, false);

				bgfx::setViewRect(RENDER_PASS_GBUFFER, 0, 0, uint16_t(m_size[0]), uint16_t(m_size[1]));
				bgfx::setViewTransform(RENDER_PASS_GBUFFER, m_view, m_proj);
				// Make sure when we draw it goes into gbuffer and not backbuffer
				bgfx::setViewFrameBuffer(RENDER_PASS_GBUFFER, m_gbuffer);
				// Draw everything into g-buffer
				drawAllModels(RENDER_PASS_GBUFFER, m_gbufferProgram);

				// Set up transform matrix for fullscreen quad
#if USE_ASSAO == 1
				float orthoProj[16];
				bx::mtxOrtho(orthoProj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, caps->homogeneousDepth);
				bgfx::setViewTransform(RENDER_PASS_COMBINE, NULL, orthoProj);
				bgfx::setViewRect(RENDER_PASS_COMBINE, 0, 0, uint16_t(m_width), uint16_t(m_height));
				// Bind vertex buffer and draw quad
				screenSpaceQuad((float)m_width, (float)m_height, m_texelHalf, caps->originBottomLeft);
				//bgfx::submit(RENDER_PASS_COMBINE, m_combineProgram);
				bgfx::touch(RENDER_PASS_COMBINE);

				BX_UNUSED(orthoProj, caps)
#endif

				// ASSAO passes
#if USE_ASSAO == 0
				updateUniforms(0);

				bgfx::ViewId view = 2;
				bgfx::setViewName(view, "ASSAO");

				{
					bgfx::setTexture(0, s_depthSource, bgfx::getTexture(m_gbuffer, GBUFFER_RT_DEPTH), SAMPLER_POINT_CLAMP);
					m_uniforms.submit();

					if (m_settings.m_generateNormals)
					{
						bgfx::setImage(5, m_normals, 0, bgfx::Access::Write, bgfx::TextureFormat::RGBA8);
					}

					if (m_settings.m_qualityLevel < 0)
					{
						for (int32_t j = 0; j < 2; ++j)
						{
							bgfx::setImage((uint8_t)(j + 1), m_halfDepths[j == 0 ? 0 : 3], 0, bgfx::Access::Write, bgfx::TextureFormat::R16F);
						}

						bgfx::dispatch(view, m_settings.m_generateNormals ? m_prepareDepthsAndNormalsHalfProgram : m_prepareDepthsHalfProgram, (m_halfSize[0] + 7) / 8, (m_halfSize[1] + 7) / 8);
					}
					else
					{
						for(int32_t j = 0; j < 4; ++j)
						{
							bgfx::setImage((uint8_t)(j+1), m_halfDepths[j], 0, bgfx::Access::Write, bgfx::TextureFormat::R16F);
						}

						bgfx::dispatch(view, m_settings.m_generateNormals ? m_prepareDepthsAndNormalsProgram : m_prepareDepthsProgram, (m_halfSize[0] + 7) / 8, (m_halfSize[1] + 7) / 8);

					}
				}

				// only do mipmaps for higher quality levels (not beneficial on quality level 1, and detrimental on quality level 0)
				if (m_settings.m_qualityLevel > 1)
				{
					uint16_t mipWidth = (uint16_t)m_halfSize[0];
					uint16_t mipHeight = (uint16_t)m_halfSize[1];

					for (uint8_t i = 1; i < SSAO_DEPTH_MIP_LEVELS; i++)
					{
						mipWidth = (uint16_t)bx::max(1, mipWidth >> 1);
						mipHeight = (uint16_t)bx::max(1, mipHeight >> 1);

						for (uint8_t j = 0; j < 4; ++j)
						{
							bgfx::setImage(j, m_halfDepths[j], i-1, bgfx::Access::Read, bgfx::TextureFormat::R16F);
							bgfx::setImage(j + 4, m_halfDepths[j], i, bgfx::Access::Write, bgfx::TextureFormat::R16F);
						}

						m_uniforms.submit();
						float rect[4] = { 0.0f, 0.0f, (float)mipWidth, (float)mipHeight };
						bgfx::setUniform(u_rect, rect);

						bgfx::dispatch(view, m_prepareDepthMipProgram, (mipWidth + 7) / 8, (mipHeight + 7) / 8);
					}
				}

				// for adaptive quality, importance map pass
				for (int32_t ssaoPass = 0; ssaoPass < 2; ++ssaoPass)
				{
					if (ssaoPass == 0
					&&  m_settings.m_qualityLevel < 3)
					{
						continue;
					}

					bool adaptiveBasePass = (ssaoPass == 0);

					BX_UNUSED(adaptiveBasePass);

					int32_t passCount = 4;

					int32_t halfResNumX = (m_halfResOutScissorRect[2] - m_halfResOutScissorRect[0] + 7) / 8;
					int32_t halfResNumY = (m_halfResOutScissorRect[3] - m_halfResOutScissorRect[1] + 7) / 8;
					float halfResRect[4] = { (float)m_halfResOutScissorRect[0], (float)m_halfResOutScissorRect[1], (float)m_halfResOutScissorRect[2], (float)m_halfResOutScissorRect[3] };

					for (int32_t pass = 0; pass < passCount; pass++)
					{
						if (m_settings.m_qualityLevel < 0
						&& (pass == 1 || pass == 2) )
						{
							continue;
						}

						int32_t blurPasses = m_settings.m_blurPassCount;
						blurPasses = bx::min(blurPasses, cMaxBlurPassCount);

						if (m_settings.m_qualityLevel == 3)
						{
							// if adaptive, at least one blur pass needed as the first pass needs to read the final texture results - kind of awkward
							if (adaptiveBasePass)
							{
								blurPasses = 0;
							}
							else
							{
								blurPasses = bx::max(1, blurPasses);
							}
						}
						else if (m_settings.m_qualityLevel <= 0)
						{
							// just one blur pass allowed for minimum quality
							blurPasses = bx::min(1, m_settings.m_blurPassCount);
						}

						updateUniforms(pass);

						bgfx::TextureHandle pPingRT = m_pingPongHalfResultA;
						bgfx::TextureHandle pPongRT = m_pingPongHalfResultB;

						// Generate
						{
							bgfx::setImage(6, blurPasses == 0 ? m_finalResults : pPingRT, 0, bgfx::Access::Write, bgfx::TextureFormat::RG8);

							bgfx::setUniform(u_rect, halfResRect);

							bgfx::setTexture(0, s_viewspaceDepthSource, m_halfDepths[pass], SAMPLER_POINT_CLAMP);
							bgfx::setTexture(1, s_viewspaceDepthSourceMirror, m_halfDepths[pass], SAMPLER_POINT_MIRROR);
							if (m_settings.m_generateNormals)
								bgfx::setImage(2, m_normals,0, bgfx::Access::Read, bgfx::TextureFormat::RGBA8);
							else
								bgfx::setImage(2, bgfx::getTexture(m_gbuffer, GBUFFER_RT_NORMAL), 0, bgfx::Access::Read, bgfx::TextureFormat::RGBA8);

							if (!adaptiveBasePass && (m_settings.m_qualityLevel == 3))
							{
								bgfx::setBuffer(3, m_loadCounter, bgfx::Access::Read);
								bgfx::setTexture(4, s_importanceMap, m_importanceMap, SAMPLER_LINEAR_CLAMP);
								bgfx::setImage(5, m_finalResults, 0, bgfx::Access::Read, bgfx::TextureFormat::RG8);
							}

							bgfx::ProgramHandle programs[5] = { m_generateQ0Program, m_generateQ1Program , m_generateQ2Program , m_generateQ3Program , m_generateQ3BaseProgram };
							int32_t programIndex = bx::max(0, (!adaptiveBasePass) ? (m_settings.m_qualityLevel) : (4));

							m_uniforms.m_layer = blurPasses == 0 ? (float)pass : 0.0f;
							m_uniforms.submit();
							bgfx::dispatch(view, programs[programIndex], halfResNumX, halfResNumY);
						}

						// Blur
						if (blurPasses > 0)
						{
							int32_t wideBlursRemaining = bx::max(0, blurPasses - 2);

							for (int32_t i = 0; i < blurPasses; i++)
							{
								bgfx::setViewFrameBuffer(view, BGFX_INVALID_HANDLE);
								bgfx::touch(view);

								m_uniforms.m_layer = ((i == (blurPasses - 1)) ? (float)pass : 0.0f);
								m_uniforms.submit();

								bgfx::setUniform(u_rect, halfResRect);

								bgfx::setImage(0, i == (blurPasses - 1) ? m_finalResults : pPongRT, 0, bgfx::Access::Write, bgfx::TextureFormat::RG8);
								bgfx::setTexture(1, s_blurInput, pPingRT, m_settings.m_qualityLevel > 0 ? SAMPLER_POINT_MIRROR : SAMPLER_LINEAR_CLAMP);

								if (m_settings.m_qualityLevel > 0)
								{
									if (wideBlursRemaining > 0)
									{
										bgfx::dispatch(view, m_smartBlurWideProgram, halfResNumX, halfResNumY);
										wideBlursRemaining--;
									}
									else
									{
										bgfx::dispatch(view, m_smartBlurProgram, halfResNumX, halfResNumY);
									}
								}
								else
								{
									bgfx::dispatch(view, m_nonSmartBlurProgram, halfResNumX, halfResNumY); // just for quality level 0 (and -1)
								}

								bgfx::TextureHandle temp = pPingRT;
								pPingRT = pPongRT;
								pPongRT = temp;
							}
						}
					}

					if (ssaoPass == 0 && m_settings.m_qualityLevel == 3)
					{	// Generate importance map
						m_uniforms.submit();
						bgfx::setImage(0, m_importanceMap, 0, bgfx::Access::Write, bgfx::TextureFormat::R8);
						bgfx::setTexture(1, s_finalSSAO, m_finalResults, SAMPLER_POINT_CLAMP);
						bgfx::dispatch(view, m_generateImportanceMapProgram, (m_quarterSize[0] + 7) / 8, (m_quarterSize[1] + 7) / 8);

						m_uniforms.submit();
						bgfx::setImage(0, m_importanceMapPong, 0, bgfx::Access::Write, bgfx::TextureFormat::R8);
						bgfx::setTexture(1, s_importanceMap, m_importanceMap);
						bgfx::dispatch(view, m_postprocessImportanceMapAProgram, (m_quarterSize[0] + 7) / 8, (m_quarterSize[1] + 7) / 8);

						bgfx::setBuffer(0, m_loadCounter, bgfx::Access::ReadWrite);
						bgfx::dispatch(view, m_loadCounterClearProgram, 1,1);

						m_uniforms.submit();
						bgfx::setImage(0, m_importanceMap, 0, bgfx::Access::Write, bgfx::TextureFormat::R8);
						bgfx::setTexture(1, s_importanceMap, m_importanceMapPong);
						bgfx::setBuffer(2, m_loadCounter, bgfx::Access::ReadWrite);
						bgfx::dispatch(view, m_postprocessImportanceMapBProgram, (m_quarterSize[0]+7) / 8, (m_quarterSize[1]+7) / 8);
						++view;
					}
				}

				// Apply
				{
					// select 4 deinterleaved AO textures (texture array)
					bgfx::setImage(0, m_aoMap, 0, bgfx::Access::Write, bgfx::TextureFormat::R8);
					bgfx::setTexture(1, s_finalSSAO, m_finalResults);

					m_uniforms.submit();

					float rect[4] = {(float)m_fullResOutScissorRect[0], (float)m_fullResOutScissorRect[1], (float)m_fullResOutScissorRect[2], (float)m_fullResOutScissorRect[3] };
					bgfx::setUniform(u_rect, rect);

					bgfx::ProgramHandle program;
					if (m_settings.m_qualityLevel < 0)
						program = m_nonSmartHalfApplyProgram;
					else if (m_settings.m_qualityLevel == 0)
						program = m_nonSmartApplyProgram;
					else
						program = m_applyProgram;
					bgfx::dispatch(view, program, (m_fullResOutScissorRect[2]- m_fullResOutScissorRect[0] + 7) / 8,
												(m_fullResOutScissorRect[3] - m_fullResOutScissorRect[1] + 7) / 8);


					++view;
				}

				{	// combine
					bgfx::setViewFrameBuffer(view, BGFX_INVALID_HANDLE);
					bgfx::setViewName(view, "Combine");
					bgfx::setViewRect(view, 0, 0, (uint16_t)m_width, (uint16_t)m_height);
					float orthoProj[16];
					bx::mtxOrtho(orthoProj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, caps->homogeneousDepth);
					bgfx::setViewTransform(view, NULL, orthoProj);

					bgfx::setTexture(0, s_color, bgfx::getTexture(m_gbuffer, GBUFFER_RT_COLOR), SAMPLER_POINT_CLAMP);
					bgfx::setTexture(1, s_normal, bgfx::getTexture(m_gbuffer, GBUFFER_RT_NORMAL), SAMPLER_POINT_CLAMP);

					bgfx::setTexture(2, s_ao, m_aoMap, SAMPLER_POINT_CLAMP);

					m_uniforms.submit();
					float combineParams[8] = { m_enableTexturing ? 1.0f : 0.0f, m_enableSSAO ? 1.0f : 0.0f, 0.0f,0.0f,
						(float)(m_size[0]-2*m_border) / (float)m_size[0], (float)(m_size[1] - 2 * m_border) / (float)m_size[1],
						(float)m_border / (float)m_size[0], (float)m_border / (float)m_size[1] };
					bgfx::setUniform(u_combineParams, combineParams, 2);
					screenSpaceQuad((float)m_width, (float)m_height, m_texelHalf, caps->originBottomLeft);
					bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_ALWAYS);
					bgfx::submit(view, m_combineProgram);
					++view;
				}
#endif

				// Draw UI
				imguiBeginFrame(m_mouseState.m_mx
					, m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					, m_mouseState.m_mz
					, uint16_t(m_width)
					, uint16_t(m_height)
					);

				showExampleDialog(this);

				ImGui::SetNextWindowPos(
					ImVec2(m_width - m_width / 4.0f - 10.0f, 10.0f)
					, ImGuiCond_FirstUseEver
					);
				ImGui::SetNextWindowSize(
					ImVec2(m_width / 4.0f, m_height / 1.3f)
					, ImGuiCond_FirstUseEver
					);
				ImGui::Begin("Settings"
					, NULL
					, 0
					);

				ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
				ImGui::Checkbox("Enable SSAO", &m_enableSSAO);
				ImGui::Checkbox("Enable Texturing & Lighting", &m_enableTexturing);
				ImGui::Separator();

				int32_t quality = m_settings.m_qualityLevel + 1;

				if (ImGui::Combo("Quality Level", &quality, "Lowest (Half Resolution)\0Low\0Medium\0High\0Adaptive\0\0"))
				{
					m_settings.m_qualityLevel = quality - 1;
				}

				ImGui::Checkbox("Generate Normals", &m_settings.m_generateNormals);

				if (ImGui::Checkbox("Framebuffer Gutter", &m_framebufferGutter))
				{
					m_recreateFrameBuffers = true;
				}

				ImGui::SliderFloat("Effect Radius", &m_settings.m_radius, 0.0f, 4.0f);
				ImGui::SliderFloat("Effect Strength", &m_settings.m_shadowMultiplier, 0.0f, 5.0f);
				ImGui::SliderFloat("Effect Power", &m_settings.m_shadowPower, 0.5f, 4.0f);
				ImGui::SliderFloat("Effect Max Limit", &m_settings.m_shadowClamp, 0.0f, 1.0f);
				ImGui::SliderFloat("Horizon Angle Threshold", &m_settings.m_horizonAngleThreshold, 0.0f, 0.2f);
				ImGui::SliderFloat("Fade Out From", &m_settings.m_fadeOutFrom, 0.0f, 100.0f);
				ImGui::SliderFloat("Fade Out To", &m_settings.m_fadeOutTo, 0.0f, 300.0f);

				if (m_settings.m_qualityLevel == 3)
				{
					ImGui::SliderFloat("Adaptive Quality Limit", &m_settings.m_adaptiveQualityLimit, 0.0f, 1.0f);
				}

				ImGui::SliderInt("Blur Pass Count", &m_settings.m_blurPassCount, 0, 6);
				ImGui::SliderFloat("Sharpness", &m_settings.m_sharpness, 0.0f, 1.0f);
				ImGui::SliderFloat("Temporal Supersampling Angle Offset", &m_settings.m_temporalSupersamplingAngleOffset, 0.0f, bx::kPi);
				ImGui::SliderFloat("Temporal Supersampling Radius Offset", &m_settings.m_temporalSupersamplingRadiusOffset, 0.0f, 2.0f);
				ImGui::SliderFloat("Detail Shadow Strength", &m_settings.m_detailShadowStrength, 0.0f, 4.0f);

				ImGui::End();

				imguiEndFrame();

				// Advance to next frame. Rendering thread will be kicked to
				// process submitted rendering primitives.
				m_currFrame = bgfx::frame();

				return true;
			}

			return false;
		}

		void drawAllModels(uint8_t _pass, bgfx::ProgramHandle _program)
		{
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_models); ++ii)
			{
				const Model& model = m_models[ii];

				// Set up transform matrix for each model
				float scale = s_meshScale[model.mesh];
				float mtx[16];
				bx::mtxSRT(mtx
					, scale
					, scale
					, scale
					, 0.0f
					, 0.0f
					, 0.0f
					, model.position[0]
					, model.position[1]
					, model.position[2]
					);

				// Submit mesh to gbuffer
				bgfx::setTexture(0, s_albedo, m_modelTexture);
				meshSubmit(m_meshes[model.mesh], _pass, _program, mtx);
			}

			// Draw ground
			float mtxScale[16];
			const float scale = 10.0f;
			bx::mtxScale(mtxScale, scale, scale, scale);

			float mtxTrans[16];
			bx::mtxTranslate(mtxTrans
				, 0.0f
				, -10.0f
				, 0.0f
				);

			float mtx[16];
			bx::mtxMul(mtx, mtxScale, mtxTrans);
			bgfx::setTexture(0, s_albedo, m_groundTexture);
			meshSubmit(m_ground, _pass, _program, mtx);
		}

		void createFramebuffers()
		{
			// update resolution and camera FOV if there's border expansion
			const int32_t drawResolutionBorderExpansionFactor = 12; // will be expanded by Height / expansionFactor
			const float fovY = 60.0f;

			m_border = 0;

			if (m_framebufferGutter)
			{
				m_border = (bx::min(m_width, m_height) / drawResolutionBorderExpansionFactor) / 2 * 2;
				int32_t expandedSceneResolutionY = m_height + m_border * 2;
				float yScaleDueToBorder = (expandedSceneResolutionY * 0.5f) / (float)(m_height * 0.5f);

				float nonExpandedTan = bx::tan(bx::toRad(fovY / 2.0f));
				m_fovY = bx::toDeg(bx::atan(nonExpandedTan * yScaleDueToBorder) * 2.0f);
			}
			else
			{
				m_fovY = fovY;
			}

			m_size[0] = m_width + 2 * m_border;
			m_size[1] = m_height + 2 * m_border;
			m_halfSize[0] = (m_size[0] + 1) / 2;
			m_halfSize[1] = (m_size[1] + 1) / 2;
			m_quarterSize[0] = (m_halfSize[0] + 1) / 2;
			m_quarterSize[1] = (m_halfSize[1] + 1) / 2;

			vec4iSet(m_fullResOutScissorRect, m_border, m_border, m_width + m_border, m_height + m_border);
			vec4iSet(m_halfResOutScissorRect, m_fullResOutScissorRect[0] / 2, m_fullResOutScissorRect[1] / 2, (m_fullResOutScissorRect[2] + 1) / 2, (m_fullResOutScissorRect[3] + 1) / 2);

			int32_t blurEnlarge = cMaxBlurPassCount + bx::max(0, cMaxBlurPassCount - 2);  // +1 for max normal blurs, +2 for wide blurs
			vec4iSet(m_halfResOutScissorRect, bx::max(0, m_halfResOutScissorRect[0] - blurEnlarge), bx::max(0, m_halfResOutScissorRect[1] - blurEnlarge),
						bx::min(m_halfSize[0], m_halfResOutScissorRect[2] + blurEnlarge), bx::min(m_halfSize[1], m_halfResOutScissorRect[3] + blurEnlarge));

			// Make gbuffer and related textures
			const uint64_t tsFlags = 0
				| BGFX_TEXTURE_RT
				| BGFX_SAMPLER_MIN_POINT
				| BGFX_SAMPLER_MAG_POINT
				| BGFX_SAMPLER_MIP_POINT
				| BGFX_SAMPLER_U_CLAMP
				| BGFX_SAMPLER_V_CLAMP
				;

			bgfx::TextureHandle gbufferTex[3];
			gbufferTex[GBUFFER_RT_NORMAL] = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::BGRA8, tsFlags);
			gbufferTex[GBUFFER_RT_COLOR]  = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::BGRA8, tsFlags);
			gbufferTex[GBUFFER_RT_DEPTH]  = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::D32F,  tsFlags);
			m_gbuffer = bgfx::createFrameBuffer(BX_COUNTOF(gbufferTex), gbufferTex, true);

			for (int32_t i = 0; i < 4; i++)
			{
				m_halfDepths[i] = bgfx::createTexture2D(uint16_t(m_halfSize[0]), uint16_t(m_halfSize[1]), true, 1, bgfx::TextureFormat::R16F, BGFX_TEXTURE_COMPUTE_WRITE | SAMPLER_POINT_CLAMP);
			}

			m_pingPongHalfResultA = bgfx::createTexture2D(uint16_t(m_halfSize[0]), uint16_t(m_halfSize[1]), false, 2, bgfx::TextureFormat::RG8, BGFX_TEXTURE_COMPUTE_WRITE);
			m_pingPongHalfResultB = bgfx::createTexture2D(uint16_t(m_halfSize[0]), uint16_t(m_halfSize[1]), false, 2, bgfx::TextureFormat::RG8, BGFX_TEXTURE_COMPUTE_WRITE);

			m_finalResults = bgfx::createTexture2D(uint16_t(m_halfSize[0]), uint16_t(m_halfSize[1]),  false, 4, bgfx::TextureFormat::RG8, BGFX_TEXTURE_COMPUTE_WRITE | SAMPLER_LINEAR_CLAMP);

			m_normals = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]),  false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_COMPUTE_WRITE);

			m_importanceMap     = bgfx::createTexture2D(uint16_t(m_quarterSize[0]), uint16_t(m_quarterSize[1]), false, 1, bgfx::TextureFormat::R8, BGFX_TEXTURE_COMPUTE_WRITE | SAMPLER_LINEAR_CLAMP);
			m_importanceMapPong = bgfx::createTexture2D(uint16_t(m_quarterSize[0]), uint16_t(m_quarterSize[1]), false, 1, bgfx::TextureFormat::R8, BGFX_TEXTURE_COMPUTE_WRITE | SAMPLER_LINEAR_CLAMP);

			m_aoMap = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::R8, BGFX_TEXTURE_COMPUTE_WRITE | SAMPLER_POINT_CLAMP);
		}

		void destroyFramebuffers()
		{
			bgfx::destroy(m_gbuffer);

			for (uint32_t ii = 0; ii < BX_COUNTOF(m_halfDepths); ++ii)
			{
				bgfx::destroy(m_halfDepths[ii]);
			}

			bgfx::destroy(m_pingPongHalfResultA);
			bgfx::destroy(m_pingPongHalfResultB);
			bgfx::destroy(m_finalResults);
			bgfx::destroy(m_normals);
			bgfx::destroy(m_aoMap);

			bgfx::destroy(m_importanceMap);
			bgfx::destroy(m_importanceMapPong);
		}

		void updateUniforms(int32_t _pass)
		{
			vec2Set(m_uniforms.m_viewportPixelSize, 1.0f / (float)m_size[0], 1.0f / (float)m_size[1]);
			vec2Set(m_uniforms.m_halfViewportPixelSize, 1.0f / (float)m_halfSize[0], 1.0f / (float)m_halfSize[1]);

			vec2Set(m_uniforms.m_viewport2xPixelSize, m_uniforms.m_viewportPixelSize[0] * 2.0f, m_uniforms.m_viewportPixelSize[1] * 2.0f);
			vec2Set(m_uniforms.m_viewport2xPixelSize_x_025, m_uniforms.m_viewport2xPixelSize[0] * 0.25f, m_uniforms.m_viewport2xPixelSize[1] * 0.25f);

			float depthLinearizeMul = -m_proj2[3*4+2]; // float depthLinearizeMul = ( clipFar * clipNear ) / ( clipFar - clipNear );
			float depthLinearizeAdd =  m_proj2[2*4+2]; // float depthLinearizeAdd = clipFar / ( clipFar - clipNear );
			                                           // correct the handedness issue. need to make sure this below is correct, but I think it is.

			if (depthLinearizeMul * depthLinearizeAdd < 0)
			{
				depthLinearizeAdd = -depthLinearizeAdd;
			}

			vec2Set(m_uniforms.m_depthUnpackConsts, depthLinearizeMul, depthLinearizeAdd);

			float tanHalfFOVY = 1.0f / m_proj2[1*4+1];    // = tanf( drawContext.Camera.GetYFOV( ) * 0.5f );
			float tanHalfFOVX = 1.0F / m_proj2[0];    // = tanHalfFOVY * drawContext.Camera.GetAspect( );

			if (bgfx::getRendererType() == bgfx::RendererType::OpenGL)
			{
				vec2Set(m_uniforms.m_ndcToViewMul, tanHalfFOVX * 2.0f, tanHalfFOVY * 2.0f);
				vec2Set(m_uniforms.m_ndcToViewAdd, tanHalfFOVX * -1.0f, tanHalfFOVY * -1.0f);
			}
			else
			{
				vec2Set(m_uniforms.m_ndcToViewMul, tanHalfFOVX * 2.0f, tanHalfFOVY * -2.0f);
				vec2Set(m_uniforms.m_ndcToViewAdd, tanHalfFOVX * -1.0f, tanHalfFOVY * 1.0f);
			}

			m_uniforms.m_effectRadius = bx::clamp(m_settings.m_radius, 0.0f, 100000.0f);
			m_uniforms.m_effectShadowStrength = bx::clamp(m_settings.m_shadowMultiplier * 4.3f, 0.0f, 10.0f);
			m_uniforms.m_effectShadowPow = bx::clamp(m_settings.m_shadowPower, 0.0f, 10.0f);
			m_uniforms.m_effectShadowClamp = bx::clamp(m_settings.m_shadowClamp, 0.0f, 1.0f);
			m_uniforms.m_effectFadeOutMul = -1.0f / (m_settings.m_fadeOutTo - m_settings.m_fadeOutFrom);
			m_uniforms.m_effectFadeOutAdd = m_settings.m_fadeOutFrom / (m_settings.m_fadeOutTo - m_settings.m_fadeOutFrom) + 1.0f;
			m_uniforms.m_effectHorizonAngleThreshold = bx::clamp(m_settings.m_horizonAngleThreshold, 0.0f, 1.0f);

			// 1.2 seems to be around the best trade off - 1.0 means on-screen radius will stop/slow growing when the camera is at 1.0 distance, so, depending on FOV, basically filling up most of the screen
			// This setting is viewspace-dependent and not screen size dependent intentionally, so that when you change FOV the effect stays (relatively) similar.
			float effectSamplingRadiusNearLimit = (m_settings.m_radius * 1.2f);

			// if the depth precision is switched to 32bit float, this can be set to something closer to 1 (0.9999 is fine)
			m_uniforms.m_depthPrecisionOffsetMod = 0.9992f;

			// used to get average load per pixel; 9.0 is there to compensate for only doing every 9th InterlockedAdd in PSPostprocessImportanceMapB for performance reasons
			m_uniforms.m_loadCounterAvgDiv = 9.0f / (float)(m_quarterSize[0] * m_quarterSize[1] * 255.0);

			// Special settings for lowest quality level - just nerf the effect a tiny bit
			if (m_settings.m_qualityLevel <= 0)
			{
				effectSamplingRadiusNearLimit *= 1.50f;

				if (m_settings.m_qualityLevel < 0)
				{
					m_uniforms.m_effectRadius *= 0.8f;
				}
			}

			effectSamplingRadiusNearLimit /= tanHalfFOVY; // to keep the effect same regardless of FOV

			m_uniforms.m_effectSamplingRadiusNearLimitRec = 1.0f / effectSamplingRadiusNearLimit;

			m_uniforms.m_adaptiveSampleCountLimit = m_settings.m_adaptiveQualityLimit;

			m_uniforms.m_negRecEffectRadius = -1.0f / m_uniforms.m_effectRadius;

			if (bgfx::getCaps()->originBottomLeft)
			{
				vec2Set(m_uniforms.m_perPassFullResCoordOffset, (float)(_pass % 2), 1.0f-(float)(_pass / 2));
				vec2Set(m_uniforms.m_perPassFullResUVOffset, ((_pass % 2) - 0.0f) / m_size[0], (1.0f-((_pass / 2) - 0.0f)) / m_size[1]);
			}
			else
			{
				vec2Set(m_uniforms.m_perPassFullResCoordOffset, (float)(_pass % 2), (float)(_pass / 2));
				vec2Set(m_uniforms.m_perPassFullResUVOffset, ((_pass % 2) - 0.0f) / m_size[0], ((_pass / 2) - 0.0f) / m_size[1]);
			}

			m_uniforms.m_invSharpness = bx::clamp(1.0f - m_settings.m_sharpness, 0.0f, 1.0f);
			m_uniforms.m_passIndex = (float)_pass;
			vec2Set(m_uniforms.m_quarterResPixelSize, 1.0f / (float)m_quarterSize[0], 1.0f / (float)m_quarterSize[1]);

			float additionalAngleOffset = m_settings.m_temporalSupersamplingAngleOffset;  // if using temporal supersampling approach (like "Progressive Rendering Using Multi-frame Sampling" from GPU Pro 7, etc.)
			float additionalRadiusScale = m_settings.m_temporalSupersamplingRadiusOffset; // if using temporal supersampling approach (like "Progressive Rendering Using Multi-frame Sampling" from GPU Pro 7, etc.)
			const int32_t subPassCount = 5;
			for (int32_t subPass = 0; subPass < subPassCount; subPass++)
			{
				int32_t a = _pass;
				int32_t b = subPass;

				int32_t spmap[5]{ 0, 1, 4, 3, 2 };
				b = spmap[subPass];

				float ca, sa;
				float angle0 = ((float)a + (float)b / (float)subPassCount) * (3.1415926535897932384626433832795f) * 0.5f;
				angle0 += additionalAngleOffset;

				ca = bx::cos(angle0);
				sa = bx::sin(angle0);

				float scale = 1.0f + (a - 1.5f + (b - (subPassCount - 1.0f) * 0.5f) / (float)subPassCount) * 0.07f;
				scale *= additionalRadiusScale;

				vec4Set(m_uniforms.m_patternRotScaleMatrices[subPass], scale * ca, scale * -sa, -scale * sa, -scale * ca);
			}

			m_uniforms.m_normalsUnpackMul = 2.0f;
			m_uniforms.m_normalsUnpackAdd = -1.0f;

			m_uniforms.m_detailAOStrength = m_settings.m_detailShadowStrength;

			if (m_settings.m_generateNormals)
			{
				bx::mtxIdentity(m_uniforms.m_normalsWorldToViewspaceMatrix);
			}
			else
			{
				bx::mtxTranspose(m_uniforms.m_normalsWorldToViewspaceMatrix, m_view);
			}
		}


		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_debug;
		uint32_t m_reset;

		entry::MouseState m_mouseState;

		Uniforms m_uniforms;

		 // Resource handles
		bgfx::ProgramHandle m_gbufferProgram;
		bgfx::ProgramHandle m_combineProgram;

		bgfx::ProgramHandle m_prepareDepthsProgram;
		bgfx::ProgramHandle m_prepareDepthsAndNormalsProgram;
		bgfx::ProgramHandle m_prepareDepthsHalfProgram;
		bgfx::ProgramHandle m_prepareDepthsAndNormalsHalfProgram;
		bgfx::ProgramHandle m_prepareDepthMipProgram;
		bgfx::ProgramHandle m_generateQ0Program;
		bgfx::ProgramHandle m_generateQ1Program;
		bgfx::ProgramHandle m_generateQ2Program;
		bgfx::ProgramHandle m_generateQ3Program;
		bgfx::ProgramHandle m_generateQ3BaseProgram;
		bgfx::ProgramHandle m_smartBlurProgram;
		bgfx::ProgramHandle m_smartBlurWideProgram;
		bgfx::ProgramHandle m_nonSmartBlurProgram;
		bgfx::ProgramHandle m_applyProgram;
		bgfx::ProgramHandle m_nonSmartApplyProgram;
		bgfx::ProgramHandle m_nonSmartHalfApplyProgram;
		bgfx::ProgramHandle m_generateImportanceMapProgram;
		bgfx::ProgramHandle m_postprocessImportanceMapAProgram;
		bgfx::ProgramHandle m_postprocessImportanceMapBProgram;
		bgfx::ProgramHandle m_loadCounterClearProgram;

		bgfx::FrameBufferHandle m_gbuffer;

		// Shader uniforms
		bgfx::UniformHandle u_rect;
		bgfx::UniformHandle u_combineParams;

		// Uniforms to identify texture samples
		bgfx::UniformHandle s_normal;
		bgfx::UniformHandle s_depth;
		bgfx::UniformHandle s_color;
		bgfx::UniformHandle s_albedo;
		bgfx::UniformHandle s_ao;
		bgfx::UniformHandle s_blurInput;
		bgfx::UniformHandle s_finalSSAO;
		bgfx::UniformHandle s_depthSource;
		bgfx::UniformHandle s_viewspaceDepthSource;
		bgfx::UniformHandle s_viewspaceDepthSourceMirror;
		bgfx::UniformHandle s_importanceMap;

		// Various render targets
		bgfx::TextureHandle m_halfDepths[4];
		bgfx::TextureHandle m_pingPongHalfResultA;
		bgfx::TextureHandle m_pingPongHalfResultB;
		bgfx::TextureHandle m_finalResults;
		bgfx::TextureHandle m_aoMap;
		bgfx::TextureHandle m_normals;

		// Only needed for quality level 3 (adaptive quality)
		bgfx::TextureHandle m_importanceMap;
		bgfx::TextureHandle m_importanceMapPong;
		bgfx::DynamicIndexBufferHandle m_loadCounter;

		struct Model
		{
			uint32_t mesh; // Index of mesh in m_meshes
			float position[3];
		};

		Model m_models[MODEL_COUNT];
		Mesh* m_meshes[BX_COUNTOF(s_meshPaths)];
		Mesh* m_ground;

		bgfx::TextureHandle m_groundTexture;
		bgfx::TextureHandle m_modelTexture;

		uint32_t m_currFrame;

		// UI
		Settings m_settings;
		bool m_enableSSAO;
		bool m_enableTexturing;

		float m_texelHalf;
		float m_fovY;

		bool m_framebufferGutter;
		bool m_recreateFrameBuffers;

		float   m_view[16];
		float   m_proj[16];
		float   m_proj2[16];
		int32_t m_size[2];
		int32_t m_halfSize[2];
		int32_t m_quarterSize[2];
		int32_t m_fullResOutScissorRect[4];
		int32_t m_halfResOutScissorRect[4];
		int32_t m_border;
	};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleASSAO
	, "39-assao"
	, "Adaptive Screen Space Ambient Occlusion."
	, "https://bkaradzic.github.io/bgfx/examples.html#assao"
	);


