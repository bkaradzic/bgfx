/*
 * Copyright 2021 elven cache. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 * Implement SVGF style denoising as bgfx example. Goal is to explore various
 * options and parameters, not produce an optimized, efficient denoiser.
 *
 * Starts with deferred rendering scene with very basic lighting. Lighting is
 * masked out with a noise pattern to provide something to denoise. There are
 * two options for the noise pattern. One is a fixed 2x2 dither pattern to
 * stand-in for lighting at quarter resolution. The other is the common
 * shadertoy random pattern as a stand-in for some fancier lighting without
 * enough samples per pixel, like ray tracing.
 *
 * First a temporal denoising filter is applied. The temporal filter is only
 * using normals to reject previous samples. The SVGF paper also describes using
 * depth comparison to reject samples but that is not implemented here.
 *
 * Followed by some number of spatial filters. These are implemented like in the
 * SVGF paper. As an alternative to the 5x5 Edge-Avoiding A-Trous filter, can
 * select a 3x3 filter instead. The 3x3 filter takes fewer samples and covers a
 * smaller area, but takes less time to compute. From a loosely eyeballed
 * comparison, N 5x5 passes looks similar to N+1 3x3 passes. The wider spatial
 * filters take a fair chunk of time to compute. I wonder if it would be a good
 * idea to interleave the input texture before computing, after the first pass
 * which skips zero pixels.
 *
 * I have not implemetened the variance guided part.
 *
 * There's also an optional TXAA pass to be applied after. I am not happy with
 * its implementation yet, so it defaults to off here.
 */

/*
 * Reference(s):
 *
 * - Spatiotemporal Variance-Guided Filtering: Real-Time Reconstruction for Path-Traced Global Illumination.
 *   https://web.archive.org/web/20170720213354/https://research.nvidia.com/sites/default/files/pubs/2017-07_Spatiotemporal-Variance-Guided-Filtering%3A/svgf_preprint.pdf
 *
 * - Streaming G-Buffer Compression for Multi-Sample Anti-Aliasing.
 *   https://web.archive.org/web/20200807211002/https://software.intel.com/content/www/us/en/develop/articles/streaming-g-buffer-compression-for-multi-sample-anti-aliasing.html
 *
 * - Edge-Avoiding A-Trous Wavelet Transform for fast Global Illumination Filtering
 *   https://web.archive.org/web/20130412085423/https://www.uni-ulm.de/fileadmin/website_uni_ulm/iui.inst.100/institut/Papers/atrousGIfilter.pdf
 *
 */

#include <common.h>
#include <camera.h>
#include <bgfx_utils.h>
#include <imgui/imgui.h>
#include <bx/rng.h>
#include <bx/os.h>

namespace {

#define DENOISE_MAX_PASSES		6

// Gbuffer has multiple render targets
#define GBUFFER_RT_COLOR		0
#define GBUFFER_RT_NORMAL		1
#define GBUFFER_RT_VELOCITY		2
#define GBUFFER_RT_DEPTH		3
#define GBUFFER_RENDER_TARGETS	4

#define MODEL_COUNT				100

static const char * s_meshPaths[] =
{
	"meshes/column.bin",
	"meshes/tree.bin",
	"meshes/hollowcube.bin",
	"meshes/bunny.bin"
};

static const float s_meshScale[] =
{
	0.05f,
	0.15f,
	0.25f,
	0.25f
};

// Vertex decl for our screen space quad (used in deferred rendering)
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

struct Uniforms
{
	enum { NumVec4 = 13 };

	void init() {
		u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, NumVec4);
	};

	void submit() const {
		bgfx::setUniform(u_params, m_params, NumVec4);
	}

	void destroy() {
		bgfx::destroy(u_params);
	}

	union
	{
		struct
		{
			/*  0    */ struct { float m_cameraJitterCurr[2]; float m_cameraJitterPrev[2]; };
			/*  1    */ struct { float m_feedbackMin; float m_feedbackMax; float m_unused1[2]; };
			/*  2    */ struct { float m_unused2; float m_applyMitchellFilter; float m_options[2]; };
			/*  3-6  */ struct { float m_worldToViewPrev[16]; };
			/*  7-10 */ struct { float m_viewToProjPrev[16]; };
			/* 11    */ struct { float m_frameOffsetForNoise; float m_noiseType; float m_unused11[2]; };
			/* 12    */ struct { float m_denoiseStep; float m_sigmaDepth; float m_sigmaNormal; float m_unused12; };
		};

		float m_params[NumVec4 * 4];
	};

	bgfx::UniformHandle u_params;
};

struct RenderTarget
{
	void init(uint32_t _width, uint32_t _height, bgfx::TextureFormat::Enum _format, uint64_t _flags)
	{
		m_texture = bgfx::createTexture2D(uint16_t(_width), uint16_t(_height), false, 1, _format, _flags);
		const bool destroyTextures = true;
		m_buffer = bgfx::createFrameBuffer(1, &m_texture, destroyTextures);
	}

	void destroy()
	{
		// also responsible for destroying texture
		bgfx::destroy(m_buffer);
	}

	bgfx::TextureHandle m_texture;
	bgfx::FrameBufferHandle m_buffer;
};

void screenSpaceQuad(bool _originBottomLeft, float _width = 1.0f, float _height = 1.0f)
{
	if (3 == bgfx::getAvailTransientVertexBuffer(3, PosTexCoord0Vertex::ms_layout) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosTexCoord0Vertex::ms_layout);
		PosTexCoord0Vertex* vertex = (PosTexCoord0Vertex*)vb.data;

		const float minx = -_width;
		const float maxx =  _width;
		const float miny = 0.0f;
		const float maxy =  _height * 2.0f;

		const float minu = -1.0f;
		const float maxu =  1.0f;

		const float zz = 0.0f;

		float minv = 0.0f;
		float maxv = 2.0f;

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

void vec2Set(float* _v, float _x, float _y)
{
	_v[0] = _x;
	_v[1] = _y;
}

void mat4Set(float * _m, const float * _src)
{
	const uint32_t MAT4_FLOATS = 16;
	for (uint32_t ii = 0; ii < MAT4_FLOATS; ++ii) {
		_m[ii] = _src[ii];
	}
}

class ExampleDenoise : public entry::AppI
{
public:
	ExampleDenoise(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
		, m_currFrame(UINT32_MAX)
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
		init.platformData.nwh  = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.platformData.ndt  = entry::getNativeDisplayHandle();
		init.platformData.type = entry::getNativeWindowHandleType();
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Create uniforms
		m_uniforms.init();

		// Create texture sampler uniforms (used when we bind textures)
		s_albedo         = bgfx::createUniform("s_albedo",         bgfx::UniformType::Sampler); // Model's source albedo
		s_color          = bgfx::createUniform("s_color",          bgfx::UniformType::Sampler); // Color (albedo) gbuffer, default color input
		s_normal         = bgfx::createUniform("s_normal",         bgfx::UniformType::Sampler); // Normal gbuffer, Model's source normal
		s_velocity       = bgfx::createUniform("s_velocity",       bgfx::UniformType::Sampler); // Velocity gbuffer
		s_depth          = bgfx::createUniform("s_depth",          bgfx::UniformType::Sampler); // Depth gbuffer
		s_previousColor  = bgfx::createUniform("s_previousColor",  bgfx::UniformType::Sampler); // Previous frame's result
		s_previousNormal = bgfx::createUniform("s_previousNormal", bgfx::UniformType::Sampler); // Previous frame's gbuffer normal

		// Create program from shaders.
		m_gbufferProgram           = loadProgram("vs_denoise_gbuffer",    "fs_denoise_gbuffer"); // Fill gbuffer
		m_combineProgram           = loadProgram("vs_denoise_screenquad", "fs_denoise_deferred_combine"); // Compute lighting from gbuffer
		m_copyProgram              = loadProgram("vs_denoise_screenquad", "fs_denoise_copy");
		m_denoiseTemporalProgram   = loadProgram("vs_denoise_screenquad", "fs_denoise_temporal");
		m_denoiseSpatialProgram3x3 = loadProgram("vs_denoise_screenquad", "fs_denoise_spatial_3x3");
		m_denoiseSpatialProgram5x5 = loadProgram("vs_denoise_screenquad", "fs_denoise_spatial_5x5");
		m_denoiseApplyLighting     = loadProgram("vs_denoise_screenquad", "fs_denoise_apply_lighting");
		m_txaaProgram              = loadProgram("vs_denoise_screenquad", "fs_denoise_txaa");

		// Load some meshes
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
		{
			m_meshes[ii] = meshLoad(s_meshPaths[ii]);
		}

		// Randomly create some models
		bx::RngMwc mwc;
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_models); ++ii)
		{
			Model& model = m_models[ii];

			model.mesh = mwc.gen() % BX_COUNTOF(s_meshPaths);
			model.position[0] = ( ( (mwc.gen() % 256) ) - 128.0f) / 20.0f;
			model.position[1] = 0;
			model.position[2] = ( ( (mwc.gen() % 256) ) - 128.0f) / 20.0f;
		}

		// Load ground, just use the cube
		m_ground = meshLoad("meshes/cube.bin");

		m_groundTexture = loadTexture("textures/fieldstone-rgba.dds");
		m_normalTexture = loadTexture("textures/fieldstone-n.dds");

		m_recreateFrameBuffers = false;
		createFramebuffers();

		// Vertex decl
		PosTexCoord0Vertex::init();

		// Init camera
		cameraCreate();
		cameraSetPosition({ 0.0f, 1.5f, 0.0f });
		cameraSetVerticalAngle(-0.3f);
		m_fovY = 60.0f;

		// Init "prev" matrices, will be same for first frame
		cameraGetViewMtx(m_view);
		bx::mtxProj(m_proj, m_fovY, float(m_size[0]) / float(m_size[1]), 0.01f, 100.0f,  bgfx::getCaps()->homogeneousDepth);
		mat4Set(m_worldToViewPrev, m_view);
		mat4Set(m_viewToProjPrev, m_proj);

		// Track whether previous results are valid
		m_havePrevious = false;

		imguiCreate();
	}

	int32_t shutdown() override
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
		{
			meshUnload(m_meshes[ii]);
		}

		meshUnload(m_ground);

		bgfx::destroy(m_normalTexture);
		bgfx::destroy(m_groundTexture);

		bgfx::destroy(m_gbufferProgram);
		bgfx::destroy(m_combineProgram);
		bgfx::destroy(m_copyProgram);
		bgfx::destroy(m_denoiseTemporalProgram);
		bgfx::destroy(m_denoiseSpatialProgram3x3);
		bgfx::destroy(m_denoiseSpatialProgram5x5);
		bgfx::destroy(m_denoiseApplyLighting);
		bgfx::destroy(m_txaaProgram);

		m_uniforms.destroy();

		bgfx::destroy(s_albedo);
		bgfx::destroy(s_color);
		bgfx::destroy(s_normal);
		bgfx::destroy(s_velocity);
		bgfx::destroy(s_depth);
		bgfx::destroy(s_previousColor);
		bgfx::destroy(s_previousNormal);

		destroyFramebuffers();

		cameraDestroy();

		imguiDestroy();

		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			// skip processing when minimized, otherwise crashing
			if (0 == m_width
			||  0 == m_height)
			{
				return true;
			}

			// Update frame timer
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const float deltaTime = float(frameTime / freq);
			const bgfx::Caps* caps = bgfx::getCaps();

			if (m_size[0] != (int32_t)m_width
			||  m_size[1] != (int32_t)m_height
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

			updateUniforms();

			bx::mtxProj(m_proj, m_fovY, float(m_size[0]) / float(m_size[1]), 0.01f, 100.0f, caps->homogeneousDepth);
			bx::mtxProj(m_proj2, m_fovY, float(m_size[0]) / float(m_size[1]), 0.01f, 100.0f, false);

			if (m_enableTxaa)
			{
				m_proj[2*4+0] += m_jitter[0] * (2.0f / m_size[0]);
				m_proj[2*4+1] -= m_jitter[1] * (2.0f / m_size[1]);
			}

			bgfx::ViewId view = 0;

			// Draw everything into gbuffer
			{
				bgfx::setViewName(view, "GBuffer");
				bgfx::setViewClear(view
					, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
					, 0
					, 1.0f
					, 0
					);

				bgfx::setViewRect(view, 0, 0, uint16_t(m_size[0]), uint16_t(m_size[1]) );
				bgfx::setViewTransform(view, m_view, m_proj);
				// Make sure when we draw it goes into gbuffer and not backbuffer
				bgfx::setViewFrameBuffer(view, m_gbuffer);

				bgfx::setState(0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					| BGFX_STATE_WRITE_Z
					| BGFX_STATE_DEPTH_TEST_LESS
					);

				drawAllModels(view, m_gbufferProgram, m_uniforms);
				++view;
			}

			float orthoProj[16];
			bx::mtxOrtho(orthoProj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, caps->homogeneousDepth);

			// Shade gbuffer
			{
				bgfx::setViewName(view, "Combine");

				// for some reason, previous draws texture lingering in transform stack
				// need to clear out, otherwise this copy is garbled. this used to work
				// and broke after updating, but i last updated like 2 years ago.
				float identity[16];
				bx::mtxIdentity(identity);
				bgfx::setTransform(identity);

				bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setViewTransform(view, NULL, orthoProj);
				bgfx::setViewFrameBuffer(view, m_currentColor.m_buffer);

				bgfx::setState(0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					| BGFX_STATE_DEPTH_TEST_ALWAYS
					);
				bgfx::setTexture(0, s_color, m_gbufferTex[GBUFFER_RT_COLOR]);
				bgfx::setTexture(1, s_normal, m_gbufferTex[GBUFFER_RT_NORMAL]);

				m_uniforms.submit();

				screenSpaceQuad(caps->originBottomLeft);

				bgfx::submit(view, m_combineProgram);

				++view;
			}

			// update last texture written, to chain passes together
			bgfx::TextureHandle lastTex = m_currentColor.m_texture;

			// denoise temporal pass
			if (m_useTemporalPass && m_havePrevious)
			{
				bgfx::setViewName(view, "Denoise Temporal");

				bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setViewTransform(view, NULL, orthoProj);
				bgfx::setViewFrameBuffer(view, m_temporaryColor.m_buffer);
				bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_ALWAYS);

				// want color, prevColor
				//		normal, prevNormal
				//		depth, prevDepth to reject previous samples from accumulating - skipping depth for now

				bgfx::setTexture(0, s_color, lastTex);
				bgfx::setTexture(1, s_normal, m_gbufferTex[GBUFFER_RT_NORMAL]);
				bgfx::setTexture(2, s_velocity, m_gbufferTex[GBUFFER_RT_VELOCITY]);
				bgfx::setTexture(3, s_previousColor, m_previousDenoise.m_texture);
				bgfx::setTexture(4, s_previousNormal, m_previousNormal.m_texture);

				m_uniforms.submit();

				screenSpaceQuad(caps->originBottomLeft);

				bgfx::submit(view, m_denoiseTemporalProgram);

				++view;

				lastTex = m_temporaryColor.m_texture;
			}

			// denoise spatial passes
			if (0 < m_denoisePasses)
			{
				// variable number of passes for denoise, alternate between two textures/buffers
				bgfx::FrameBufferHandle destBuffer[] =
				{
					m_previousDenoise.m_buffer,
					m_currentColor.m_buffer,
					m_temporaryColor.m_buffer,
					m_currentColor.m_buffer,
					m_temporaryColor.m_buffer,
					m_currentColor.m_buffer,
				};
				BX_STATIC_ASSERT(BX_COUNTOF(destBuffer) == DENOISE_MAX_PASSES);

				const uint32_t denoisePasses = bx::min(DENOISE_MAX_PASSES, m_denoisePasses);

				for (uint32_t ii = 0; ii < denoisePasses; ++ii)
				{
					char name[64];
					bx::snprintf(name, BX_COUNTOF(name), "Denoise %d/%d", ii, denoisePasses-1);
					bgfx::setViewName(view, name);

					bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewTransform(view, NULL, orthoProj);
					bgfx::setViewFrameBuffer(view, destBuffer[ii]);

					bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_ALWAYS);
					bgfx::setTexture(0, s_color,  lastTex);
					bgfx::setTexture(1, s_normal, m_gbufferTex[GBUFFER_RT_NORMAL]);
					bgfx::setTexture(2, s_depth,  m_gbufferTex[GBUFFER_RT_DEPTH]);

					// need to update some denoise uniforms per draw
					const float denoiseStepScale = bx::pow(2.0f, float(ii) );
					m_uniforms.m_denoiseStep = denoiseStepScale;
					m_uniforms.submit();

					screenSpaceQuad(caps->originBottomLeft);

					const bgfx::ProgramHandle spatialProgram = (0 == m_spatialSampleType)
						? m_denoiseSpatialProgram3x3
						: m_denoiseSpatialProgram5x5
						;
					bgfx::submit(view, spatialProgram);

					++view;

					if (m_previousDenoise.m_buffer.idx == destBuffer[ii].idx)
					{
						lastTex = m_previousDenoise.m_texture;
					}
					else if (m_temporaryColor.m_buffer.idx == destBuffer[ii].idx)
					{
						lastTex = m_temporaryColor.m_texture;
					}
					else
					{
						lastTex = m_currentColor.m_texture;
					}
				}
			}
			else
			{
				// need color result for temporal denoise if not supplied by spatial pass
				// (per SVGF paper, reuse previous frame's first spatial pass output as previous color
				bgfx::setViewName(view, "Copy Color for Temporal Denoise");
				bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setViewTransform(view, NULL, orthoProj);
				bgfx::setViewFrameBuffer(view, m_previousDenoise.m_buffer);
				bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_ALWAYS);
				bgfx::setTexture(0, s_color, lastTex);

				screenSpaceQuad(caps->originBottomLeft);
				bgfx::submit(view, m_copyProgram);

				++view;
			}

			// apply lighting
			{
				bgfx::setViewName(view, "Apply Lighting");

				bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setViewTransform(view, NULL, orthoProj);

				bgfx::FrameBufferHandle destBuffer = (lastTex.idx == m_currentColor.m_texture.idx)
					? m_temporaryColor.m_buffer
					: m_currentColor.m_buffer
					;
				bgfx::setViewFrameBuffer(view, destBuffer);
				bgfx::setState(0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					| BGFX_STATE_DEPTH_TEST_ALWAYS
					);
				bgfx::setTexture(0, s_color, lastTex);
				bgfx::setTexture(1, s_albedo, m_gbufferTex[GBUFFER_RT_COLOR]);
				m_uniforms.submit();

				screenSpaceQuad(caps->originBottomLeft);
				bgfx::submit(view, m_denoiseApplyLighting);
				++view;

				lastTex = (m_temporaryColor.m_buffer.idx == destBuffer.idx)
					? m_temporaryColor.m_texture
					: m_currentColor.m_texture
					;
			}

			if (m_enableTxaa)
			{
				// Draw txaa to txaa buffer
				{
					bgfx::setViewName(view, "Temporal AA");

					bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewTransform(view, NULL, orthoProj);
					bgfx::setViewFrameBuffer(view, m_txaaColor.m_buffer);

					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_DEPTH_TEST_ALWAYS
						);
					bgfx::setTexture(0, s_color, lastTex);
					bgfx::setTexture(1, s_previousColor, m_previousColor.m_texture);
					bgfx::setTexture(2, s_velocity, m_gbufferTex[GBUFFER_RT_VELOCITY]);
					bgfx::setTexture(3, s_depth, m_gbufferTex[GBUFFER_RT_DEPTH]);
					m_uniforms.submit();

					screenSpaceQuad(caps->originBottomLeft);
					bgfx::submit(view, m_txaaProgram);

					++view;
				}

				// Copy txaa result to previous
				{
					bgfx::setViewName(view, "Copy to Previous");

					bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewTransform(view, NULL, orthoProj);
					bgfx::setViewFrameBuffer(view, m_previousColor.m_buffer);
					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_DEPTH_TEST_ALWAYS
						);
					bgfx::setTexture(0, s_color, m_txaaColor.m_texture);

					screenSpaceQuad(caps->originBottomLeft);
					bgfx::submit(view, m_copyProgram);

					++view;
				}

				// Copy txaa result to swap chain
				{
					bgfx::setViewName(view, "Display");

					bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewTransform(view, NULL, orthoProj);
					bgfx::setViewFrameBuffer(view, BGFX_INVALID_HANDLE);
					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_DEPTH_TEST_ALWAYS
						);
					bgfx::setTexture(0, s_color, m_txaaColor.m_texture);

					screenSpaceQuad(caps->originBottomLeft);
					bgfx::submit(view, m_copyProgram);

					++view;
				}
			}
			else
			{
				// Copy color result to swap chain
				{
					bgfx::setViewName(view, "Display");
					bgfx::setViewClear(view
						, BGFX_CLEAR_NONE
						, 0
						, 1.0f
						, 0
						);

					bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewTransform(view, NULL, orthoProj);
					bgfx::setViewFrameBuffer(view, BGFX_INVALID_HANDLE);
					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						);
					bgfx::setTexture(0, s_color, lastTex);

					screenSpaceQuad(caps->originBottomLeft);
					bgfx::submit(view, m_copyProgram);

					++view;
				}
			}

			// copy the normal buffer for next time
			{
				bgfx::setViewName(view, "Copy Normals");
				bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setViewTransform(view, NULL, orthoProj);
				bgfx::setViewFrameBuffer(view, m_previousNormal.m_buffer);
				bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_ALWAYS);
				bgfx::setTexture(0, s_color, m_gbufferTex[GBUFFER_RT_NORMAL]);

				screenSpaceQuad(caps->originBottomLeft);
				bgfx::submit(view, m_copyProgram);

				++view;

				// update previous status
				m_havePrevious = true;
			}

			// Copy matrices for next time
			mat4Set(m_worldToViewPrev, m_view);
			mat4Set(m_viewToProjPrev, m_proj);

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
				ImVec2(m_width / 4.0f, m_height / 1.24f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);

			{
				ImGui::TextWrapped(
					"In this demo, noise is added to results of deferred lighting. Then denoise is applied "
					"before multiplying the lit result with gbuffer albedo. Optionally, temporal antialiasing "
					"can be applied after that. (off by default, implementation blurry)");
				ImGui::Separator();

				ImGui::Text("noise controls:");
				ImGui::Combo("pattern", &m_noiseType, "none\0dither\0random\0\0");
				if (ImGui::IsItemHovered() )
				{
					ImGui::BeginTooltip();
					ImGui::Text("none");
					ImGui::BulletText("compare denoised results to this");
					ImGui::BulletText("brighter than noisy images, not losing any pixel's energy");
					ImGui::Text("dither");
					ImGui::BulletText("reject 3 out of 4 pixels in 2x2 pattern");
					ImGui::BulletText("could represent lower resolution signal");
					ImGui::Text("random");
					ImGui::BulletText("reject about half pixels, using common shader random");
					ImGui::BulletText("could represent monte carlo something or other");
					ImGui::EndTooltip();
				}

				ImGui::Checkbox("dynamic noise", &m_dynamicNoise);
				if (ImGui::IsItemHovered() )
				{
					ImGui::SetTooltip("update noise pattern each frame");
				}

				ImGui::Separator();
			}

			{
				ImGui::Text("temporal denoise pass controls:");
				ImGui::Checkbox("use temporal pass", &m_useTemporalPass);
				ImGui::Separator();
			}

			{
				ImGui::Text("spatial denoise pass controls:");
				ImGui::SliderInt("spatial passes", &m_denoisePasses, 0, DENOISE_MAX_PASSES);
				if (ImGui::IsItemHovered() )
				{
					ImGui::SetTooltip("set passes to 0 to turn off spatial denoise");
				}

				ImGui::Combo("spatial sample extent", &m_spatialSampleType, "three\0five\0\0");
				if (ImGui::IsItemHovered() )
				{
					ImGui::SetTooltip("select 3x3 or 5x5 filter kernel");
				}

				ImGui::SliderFloat("sigma z", &m_sigmaDepth, 0.0f, 0.1f, "%.5f");
				if (ImGui::IsItemHovered() )
				{
					ImGui::SetTooltip("lower sigma z, pickier blending across depth edges");
				}

				ImGui::SliderFloat("sigma n", &m_sigmaNormal, 1.0f, 256.0f);
				if (ImGui::IsItemHovered() )
				{
					ImGui::SetTooltip("higher sigma n, pickier blending across normal edges");
				}

				ImGui::Separator();
			}

			if (ImGui::CollapsingHeader("TXAA options") )
			{
				ImGui::Checkbox("use TXAA", &m_enableTxaa);
				ImGui::Checkbox("apply extra blur to current color", &m_applyMitchellFilter);
				if (ImGui::IsItemHovered() )
				{
					ImGui::SetTooltip("reduces flicker/crawl on thin features, maybe too much!");
				}

				ImGui::SliderFloat("feedback min", &m_feedbackMin, 0.0f, 1.0f);
				if (ImGui::IsItemHovered() )
				{
					ImGui::SetTooltip("minimum amount of previous frame to blend in");
				}

				ImGui::SliderFloat("feedback max", &m_feedbackMax, 0.0f, 1.0f);
				if (ImGui::IsItemHovered() )
				{
					ImGui::SetTooltip("maximum amount of previous frame to blend in");
				}

				ImGui::Checkbox("debug TXAA with slow frame rate", &m_useTxaaSlow);
				if (ImGui::IsItemHovered() )
				{
					ImGui::BeginTooltip();
					ImGui::Text("sleep 100ms per frame to highlight temporal artifacts");
					ImGui::Text("high framerate compensates for flickering, masking issues");
					ImGui::EndTooltip();
				}

				ImGui::Separator();
			}

			ImGui::End();

			imguiEndFrame();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			m_currFrame = bgfx::frame();

			// add artificial wait to emphasize txaa behavior
			if (m_useTxaaSlow)
			{
				bx::sleep(100);
			}

			return true;
		}

		return false;
	}

	void drawAllModels(bgfx::ViewId _pass, bgfx::ProgramHandle _program, const Uniforms & _uniforms)
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_models); ++ii)
		{
			const Model& model = m_models[ii];

			// Set up transform matrix for each model
			const float scale = s_meshScale[model.mesh];
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
			bgfx::setTexture(0, s_albedo, m_groundTexture);
			bgfx::setTexture(1, s_normal, m_normalTexture);
			_uniforms.submit();

			meshSubmit(m_meshes[model.mesh], _pass, _program, mtx);
		}

		// Draw ground
		float mtxScale[16];
		const float scale = 10.0f;
		bx::mtxScale(mtxScale, scale, scale, scale);

		float mtxTranslate[16];
		bx::mtxTranslate(mtxTranslate
			, 0.0f
			, -10.0f
			, 0.0f
			);

		float mtx[16];
		bx::mtxMul(mtx, mtxScale, mtxTranslate);
		bgfx::setTexture(0, s_albedo, m_groundTexture);
		bgfx::setTexture(1, s_normal, m_normalTexture);
		_uniforms.submit();

		meshSubmit(m_ground, _pass, _program, mtx);
	}

	void createFramebuffers()
	{
		m_size[0] = m_width;
		m_size[1] = m_height;

		const uint64_t bilinearFlags = 0
			| BGFX_TEXTURE_RT
			| BGFX_SAMPLER_U_CLAMP
			| BGFX_SAMPLER_V_CLAMP
			;

		const uint64_t pointSampleFlags = bilinearFlags
			| BGFX_SAMPLER_MIN_POINT
			| BGFX_SAMPLER_MAG_POINT
			| BGFX_SAMPLER_MIP_POINT
			;

		m_gbufferTex[GBUFFER_RT_COLOR]    = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::BGRA8, pointSampleFlags);
		m_gbufferTex[GBUFFER_RT_NORMAL]   = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::BGRA8, pointSampleFlags);
		m_gbufferTex[GBUFFER_RT_VELOCITY] = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::RG16F, pointSampleFlags);
		m_gbufferTex[GBUFFER_RT_DEPTH]    = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::D32F , pointSampleFlags);
		m_gbuffer = bgfx::createFrameBuffer(BX_COUNTOF(m_gbufferTex), m_gbufferTex, true);

		bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RG11B10F;
		if (!bgfx::isTextureValid(1, false, 1, format, bilinearFlags))
		{
			format = bgfx::TextureFormat::RGBA16F;
		}

		m_currentColor   .init(m_size[0], m_size[1], format, bilinearFlags);
		m_previousColor  .init(m_size[0], m_size[1], format, bilinearFlags);
		m_txaaColor      .init(m_size[0], m_size[1], format, bilinearFlags);
		m_temporaryColor .init(m_size[0], m_size[1], format, bilinearFlags);
		m_previousNormal .init(m_size[0], m_size[1], format, pointSampleFlags);
		m_previousDenoise.init(m_size[0], m_size[1], format, bilinearFlags);
	}

	// all buffers set to destroy their textures
	void destroyFramebuffers()
	{
		bgfx::destroy(m_gbuffer);

		m_currentColor.destroy();
		m_previousColor.destroy();
		m_txaaColor.destroy();
		m_temporaryColor.destroy();
		m_previousNormal.destroy();
		m_previousDenoise.destroy();
	}

	void updateUniforms()
	{
		{
			uint32_t idx = m_currFrame % 8;
			const float offsets[] =
			{
				(1.0f/ 2.0f), (1.0f/3.0f),
				(1.0f/ 4.0f), (2.0f/3.0f),
				(3.0f/ 4.0f), (1.0f/9.0f),
				(1.0f/ 8.0f), (4.0f/9.0f),
				(5.0f/ 8.0f), (7.0f/9.0f),
				(3.0f/ 8.0f), (2.0f/9.0f),
				(7.0f/ 8.0f), (5.0f/9.0f),
				(1.0f/16.0f), (8.0f/9.0f),
			};

			// Strange constant for jitterX is because 8 values from halton2
			// sequence above do not average out to 0.5, 1/16 skews it to the
			// left. Subtracting a smaller value to center the range of jitter
			// around 0. Not necessary for jitterY. Not confident this makes sense...
			const float jitterX = 1.0f * (offsets[2*idx]   - (7.125f/16.0f) );
			const float jitterY = 1.0f * (offsets[2*idx+1] - 0.5f);

			vec2Set(m_uniforms.m_cameraJitterCurr, jitterX, jitterY);
			vec2Set(m_uniforms.m_cameraJitterPrev, m_jitter[0], m_jitter[1]);

			m_jitter[0] = jitterX;
			m_jitter[1] = jitterY;
		}

		m_uniforms.m_feedbackMin = m_feedbackMin;
		m_uniforms.m_feedbackMax = m_feedbackMax;
		m_uniforms.m_applyMitchellFilter = m_applyMitchellFilter ? 1.0f : 0.0f;

		mat4Set(m_uniforms.m_worldToViewPrev, m_worldToViewPrev);
		mat4Set(m_uniforms.m_viewToProjPrev, m_viewToProjPrev);

		m_uniforms.m_frameOffsetForNoise = m_dynamicNoise
			? float(m_currFrame % 8)
			: 0.0f
			;
		m_uniforms.m_noiseType = float(m_noiseType);
		m_uniforms.m_sigmaDepth = m_sigmaDepth;
		m_uniforms.m_sigmaNormal = m_sigmaNormal;
	}


	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	entry::MouseState m_mouseState;

	// Resource handles
	bgfx::ProgramHandle m_gbufferProgram;
	bgfx::ProgramHandle m_combineProgram;
	bgfx::ProgramHandle m_copyProgram;
	bgfx::ProgramHandle m_denoiseTemporalProgram;
	bgfx::ProgramHandle m_denoiseSpatialProgram3x3;
	bgfx::ProgramHandle m_denoiseSpatialProgram5x5;
	bgfx::ProgramHandle m_denoiseApplyLighting;
	bgfx::ProgramHandle m_txaaProgram;

	// Shader uniforms
	Uniforms m_uniforms;

	// Uniforms to identify texture samplers
	bgfx::UniformHandle s_albedo;
	bgfx::UniformHandle s_color;
	bgfx::UniformHandle s_normal;
	bgfx::UniformHandle s_velocity;
	bgfx::UniformHandle s_depth;
	bgfx::UniformHandle s_previousColor;
	bgfx::UniformHandle s_previousNormal;

	bgfx::FrameBufferHandle m_gbuffer;
	bgfx::TextureHandle m_gbufferTex[GBUFFER_RENDER_TARGETS];

	RenderTarget m_currentColor;
	RenderTarget m_previousColor;
	RenderTarget m_txaaColor;
	RenderTarget m_temporaryColor; // need another buffer to ping-pong results
	RenderTarget m_previousNormal;
	RenderTarget m_previousDenoise; // color output by first spatial denoise pass, input to next frame as previous color

	struct Model
	{
		uint32_t mesh; // Index of mesh in m_meshes
		float position[3];
	};

	Model m_models[MODEL_COUNT];
	Mesh* m_meshes[BX_COUNTOF(s_meshPaths)];
	Mesh* m_ground;
	bgfx::TextureHandle m_groundTexture;
	bgfx::TextureHandle m_normalTexture;

	uint32_t m_currFrame;
	float    m_fovY                 = 60.0f;
	bool     m_recreateFrameBuffers = false;
	bool     m_havePrevious         = false;

	float   m_view[16];
	float   m_proj[16];
	float   m_proj2[16];
	float   m_viewToProjPrev[16];
	float   m_worldToViewPrev[16];
	float   m_jitter[2];
	int32_t m_size[2];

	// UI parameters
	int32_t m_noiseType           = 2;
	int32_t m_spatialSampleType   = 1;
	int32_t m_denoisePasses       = 5;
	float   m_sigmaDepth          = 0.05f;
	float   m_sigmaNormal         = 128.0f;
	float   m_feedbackMin         = 0.8f;
	float   m_feedbackMax         = 0.95f;
	bool    m_dynamicNoise        = true;
	bool    m_useTemporalPass     = true;
	bool    m_enableTxaa          = false;
	bool    m_applyMitchellFilter = true;
	bool    m_useTxaaSlow         = false;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleDenoise, "43-denoise", "Denoise.");
