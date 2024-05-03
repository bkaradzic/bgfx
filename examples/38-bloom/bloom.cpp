/*
 * Copyright 2018 Eric Arnebäck. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

/*
 * Reference(s):
 * - Next Generation Post Processing in Call of Duty: Advanced Warfare
 *   https://web.archive.org/web/20180920045230/http://www.iryoku.com/next-generation-post-processing-in-call-of-duty-advanced-warfare
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"

namespace
{

// pass that render the geometry of the boxes.
#define RENDER_PASS_GEOMETRY_ID 0

// the first downsample pass.
#define RENDER_PASS_DOWNSAMPLE0_ID 1

// the first upsample pass.
#define RENDER_PASS_UPSAMPLE0_ID ( (TEX_CHAIN_LEN-1)  + 1)

// the final pass the combines the bloom with the g-buffer.
#define RENDER_PASS_COMBINE_ID ( (TEX_CHAIN_LEN-1) + 1 + (TEX_CHAIN_LEN-1) )

// number of downsampled and then upsampled textures(used for bloom.)
#define TEX_CHAIN_LEN 5

struct PosVertex
{
	float m_x;
	float m_y;
	float m_z;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosVertex::ms_layout;

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
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosTexCoord0Vertex::ms_layout;

constexpr float cs = 0.29f;

static PosVertex s_cubeVertices[24] =
{
	{-cs,  cs,  cs },
	{ cs,  cs,  cs },
	{-cs, -cs,  cs },
	{ cs, -cs,  cs },
	{-cs,  cs, -cs },
	{ cs,  cs, -cs },
	{-cs, -cs, -cs },
	{ cs, -cs, -cs },
	{-cs,  cs,  cs },
	{ cs,  cs,  cs },
	{-cs,  cs, -cs },
	{ cs,  cs, -cs },
	{-cs, -cs,  cs },
	{ cs, -cs,  cs },
	{-cs, -cs, -cs },
	{ cs, -cs, -cs },
	{ cs, -cs,  cs },
	{ cs,  cs,  cs },
	{ cs, -cs, -cs },
	{ cs,  cs, -cs },
	{-cs, -cs,  cs },
	{-cs,  cs,  cs },
	{-cs, -cs, -cs },
	{-cs,  cs, -cs },
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
		const float maxy = _height*2.0f;

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

class ExampleBloom : public entry::AppI
{
public:
	ExampleBloom(const char* _name, const char* _description, const char* _url)
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

		// Enable m_debug text.
		bgfx::setDebug(m_debug);

		// Set palette color for index 0
		bgfx::setPaletteColor(0, UINT32_C(0x00000000) );

		// Set geometry pass view clear state.
		bgfx::setViewClear(RENDER_PASS_GEOMETRY_ID
			, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
			, 1.0f
			, 0
			, 0
			, 0
			);

		// we need to clear the textures in the chain, before downsampling into them.
		for (uint16_t ii = 0; ii < TEX_CHAIN_LEN-1; ++ii)
		{
			bgfx::setViewClear(RENDER_PASS_DOWNSAMPLE0_ID + ii
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 1.0f
				, 0
				, 0
				);
		}

		// Create vertex stream declaration.
		PosVertex::init();
		PosTexCoord0Vertex::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
			  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
			, PosVertex::ms_layout
			);

		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

		s_albedo    = bgfx::createUniform("s_albedo",    bgfx::UniformType::Sampler);
		s_tex       = bgfx::createUniform("s_tex",       bgfx::UniformType::Sampler);
		s_depth     = bgfx::createUniform("s_depth",     bgfx::UniformType::Sampler);
		s_light     = bgfx::createUniform("s_light",     bgfx::UniformType::Sampler);
		u_pixelSize = bgfx::createUniform("u_pixelSize", bgfx::UniformType::Vec4);
		u_intensity = bgfx::createUniform("u_intensity", bgfx::UniformType::Vec4);
		u_color     = bgfx::createUniform("u_color",     bgfx::UniformType::Vec4);
		u_mtx       = bgfx::createUniform("u_mtx",       bgfx::UniformType::Mat4);

		// Create program from shaders.
		m_geomProgram       = loadProgram("vs_albedo_output", "fs_albedo_output");
		m_downsampleProgram = loadProgram("vs_fullscreen",    "fs_downsample");
		m_upsampleProgram   = loadProgram("vs_fullscreen",    "fs_upsample");
		m_combineProgram    = loadProgram("vs_fullscreen",    "fs_bloom_combine");

		m_gbuffer = BGFX_INVALID_HANDLE;

		for (int ii = 0; ii < TEX_CHAIN_LEN; ++ii)
		{
			m_texChainFb[ii]  = BGFX_INVALID_HANDLE;
		}

		// Imgui.
		imguiCreate();

		m_timeOffset = bx::getHPCounter();

		// Get renderer capabilities info.
		m_caps = bgfx::getCaps();

		m_oldWidth  = 0;
		m_oldHeight = 0;
		m_oldReset  = m_reset;

		m_scrollArea = 0;

		cameraCreate();

		cameraSetPosition({ 0.0f, 0.0f, -15.0f });
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
		}

		for (int ii = 0; ii < TEX_CHAIN_LEN; ++ii)
		{
			bgfx::destroy(m_texChainFb[ii]);
		}

		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);

		bgfx::destroy(m_geomProgram);
		bgfx::destroy(m_downsampleProgram);
		bgfx::destroy(m_upsampleProgram);
		bgfx::destroy(m_combineProgram);

		bgfx::destroy(s_albedo);
		bgfx::destroy(s_tex);
		bgfx::destroy(s_depth);
		bgfx::destroy(s_light);

		bgfx::destroy(u_mtx);
		bgfx::destroy(u_pixelSize);
		bgfx::destroy(u_intensity);
		bgfx::destroy(u_color);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(
				  m_mouseState.m_mx
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
						| BGFX_SAMPLER_U_CLAMP
						| BGFX_SAMPLER_V_CLAMP
						;

					for (int ii = 0; ii < TEX_CHAIN_LEN; ++ii)
					{
						if (bgfx::isValid(m_texChainFb[ii]) )
						{
							bgfx::destroy(m_texChainFb[ii]);
						}

						m_texChainFb[ii]  = bgfx::createFrameBuffer(
							  (uint16_t)(m_width  >> ii)
							, (uint16_t)(m_height >> ii)
							, bgfx::TextureFormat::RGBA32F
							, tsFlags
							);
					}

					bgfx::TextureHandle gbufferTex[] =
					{
						bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::RGBA32F, tsFlags),
						bgfx::getTexture(m_texChainFb[0]),
						bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::D32F, tsFlags),
					};

					m_gbuffer = bgfx::createFrameBuffer(BX_COUNTOF(gbufferTex), gbufferTex, true);
				}

				ImGui::SetNextWindowPos(
					  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
					, ImGuiCond_FirstUseEver
					);
				ImGui::SetNextWindowSize(
					  ImVec2(m_width / 5.0f, m_height / 6.0f)
					, ImGuiCond_FirstUseEver
					);
				ImGui::Begin("Settings"
					, NULL
					, 0
					);

				ImGui::SliderFloat("intensity", &m_intensity, 0.0f, 3.0f);

				ImGui::End();

				// Update camera.
				cameraUpdate(deltaTime, m_mouseState, ImGui::MouseOverArea() );

				float view[16];
				cameraGetViewMtx(view);

				float proj[16];
				// Setup views
				{
					bgfx::setViewRect(RENDER_PASS_GEOMETRY_ID,      0, 0, uint16_t(m_width), uint16_t(m_height) );

					for (uint16_t ii = 0; ii < TEX_CHAIN_LEN-1; ++ii)
					{
						const uint16_t shift = ii + 1;
						bgfx::setViewRect(RENDER_PASS_DOWNSAMPLE0_ID + ii, 0, 0
							, uint16_t(m_width  >> shift)
							, uint16_t(m_height >> shift)
							);
					}

					for (uint16_t ii = 0; ii < TEX_CHAIN_LEN-1; ++ii)
					{
						const uint16_t shift = TEX_CHAIN_LEN - ii - 2;
						bgfx::setViewRect(RENDER_PASS_UPSAMPLE0_ID + ii, 0, 0
							, uint16_t(m_width  >> shift)
							, uint16_t(m_height >> shift)
							);
					}

					bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, m_caps->homogeneousDepth);
					bgfx::setViewFrameBuffer(RENDER_PASS_GEOMETRY_ID, m_gbuffer);
					bgfx::setViewTransform(RENDER_PASS_GEOMETRY_ID, view, proj);

					bgfx::setViewRect(RENDER_PASS_COMBINE_ID, 0, 0, uint16_t(m_width), uint16_t(m_height));

					bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f, 0.0f, m_caps->homogeneousDepth);

					for (uint16_t ii = 0; ii < TEX_CHAIN_LEN-1; ++ii)
					{
						bgfx::setViewTransform(RENDER_PASS_DOWNSAMPLE0_ID + ii, NULL, proj);
						bgfx::setViewFrameBuffer(RENDER_PASS_DOWNSAMPLE0_ID + ii, m_texChainFb[ii+1]);
					}

					for (uint16_t ii = 0; ii < TEX_CHAIN_LEN-1; ++ii)
					{
						bgfx::setViewTransform(RENDER_PASS_UPSAMPLE0_ID + ii, NULL, proj);
						bgfx::setViewFrameBuffer(RENDER_PASS_UPSAMPLE0_ID + ii, m_texChainFb[TEX_CHAIN_LEN - ii - 2]);
					}

					bgfx::setViewTransform(RENDER_PASS_COMBINE_ID, NULL, proj);
				}

				const uint32_t kNum = 9;
				const int kNumColors = 5;
				const float color[4*kNumColors] =
				{   // Reference(s):
					// - Palette
					//   https://web.archive.org/web/20180219034657/http://www.colourlovers.com/palette/3647908/RGB_Ice_Cream
					0.847f*0.2f, 0.365f*0.2f, 0.408f*0.2f, 1.0f,
					0.976f*0.2f, 0.827f*0.2f, 0.533f*0.2f, 1.0f,
					0.533f*0.2f, 0.867f*0.2f, 0.741f*0.2f, 1.0f,
					0.894f*0.2f, 0.620f*0.2f, 0.416f*0.2f, 1.0f,
					0.584f*0.2f, 0.788f*0.2f, 0.882f*0.2f, 1.0f,
				};

				// Render a whole bunch of colored cubes to the g-buffer.
				for (uint32_t xx = 0; xx < kNum; ++xx)
				{
					bgfx::setUniform(u_color, &color[4 * (xx % kNumColors)]);

					float mtx[16];

					bx::mtxIdentity(mtx);

					const float tt = (float)xx / (float)kNum + 0.07f * time;
					const float rr = bx::sin(0.47f * time * bx::kPi2) + 1.4f;

					mtx[12] = bx::sin(tt * bx::kPi2)*rr;
					mtx[13] = bx::cos(tt * bx::kPi2)*rr;
					mtx[14] = 0.2f * (float)xx / (float)kNum;

					// Set transform for draw call.
					bgfx::setTransform(mtx);

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(0, m_vbh);
					bgfx::setIndexBuffer(m_ibh);

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

				// Now downsample.
				for (uint16_t ii = 0; ii < TEX_CHAIN_LEN-1; ++ii)
				{
					const uint16_t shift = ii + 1;
					const float pixelSize[4] =
					{
						1.0f / (float)(m_width  >> shift),
						1.0f / (float)(m_height >> shift),
						0.0f,
						0.0f,
					};

					bgfx::setUniform(u_pixelSize, pixelSize);
					bgfx::setTexture(0, s_tex, bgfx::getTexture(m_texChainFb[ii]) );

					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						);

					screenSpaceQuad(m_caps->originBottomLeft);
					bgfx::submit(RENDER_PASS_DOWNSAMPLE0_ID + ii, m_downsampleProgram);
				}

				// Now upsample.
				for (uint16_t ii = 0; ii < TEX_CHAIN_LEN - 1; ++ii)
				{
					const uint16_t shift = TEX_CHAIN_LEN - 2 - ii;
					const float pixelSize[4] =
					{
						1.0f / (float)(m_width  >> shift),
						1.0f / (float)(m_height >> shift),
						0.0f,
						0.0f,
					};
					const float intensity[4] = { m_intensity, 0.0f, 0.0f, 0.0f };

					bgfx::setUniform(u_pixelSize, pixelSize);
					bgfx::setUniform(u_intensity, intensity);

					// Combine color and light buffers.
					bgfx::setTexture(0, s_tex, bgfx::getTexture(m_texChainFb[TEX_CHAIN_LEN - 1 - ii]) );

					// As we upscale, we also sum with the previous mip level. We do this by alpha blending.
					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_BLEND_ADD
						);

					screenSpaceQuad(m_caps->originBottomLeft);
					bgfx::submit(RENDER_PASS_UPSAMPLE0_ID + ii, m_upsampleProgram);
				}

				// Do final pass, that combines the bloom with the g-buffer.
				bgfx::setTexture(0, s_albedo, bgfx::getTexture(m_gbuffer, 0) );
				bgfx::setTexture(1, s_light,  bgfx::getTexture(m_texChainFb[0]) );
				bgfx::setState(0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					);
				screenSpaceQuad(m_caps->originBottomLeft);
				bgfx::submit(RENDER_PASS_COMBINE_ID, m_combineProgram);
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

	bgfx::UniformHandle s_albedo;
	bgfx::UniformHandle s_tex;
	bgfx::UniformHandle s_depth;
	bgfx::UniformHandle s_light;
	bgfx::UniformHandle u_pixelSize;
	bgfx::UniformHandle u_intensity;
	bgfx::UniformHandle u_color;


	bgfx::UniformHandle u_mtx;

	bgfx::ProgramHandle m_geomProgram;
	bgfx::ProgramHandle m_downsampleProgram;
	bgfx::ProgramHandle m_upsampleProgram;
	bgfx::ProgramHandle m_combineProgram;

	bgfx::FrameBufferHandle m_gbuffer;
	bgfx::FrameBufferHandle m_texChainFb[TEX_CHAIN_LEN];

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	float m_intensity = 1.0f;

	uint32_t m_oldWidth;
	uint32_t m_oldHeight;
	uint32_t m_oldReset;

	int32_t m_scrollArea;

	entry::MouseState m_mouseState;

	const bgfx::Caps* m_caps;
	int64_t m_timeOffset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleBloom
	, "38-bloom"
	, "Bloom."
	, "https://bkaradzic.github.io/bgfx/examples.html#bloom"
	);
