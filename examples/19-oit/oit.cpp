/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorVertex::ms_layout;

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

static PosColorVertex s_cubeVertices[8] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeIndices[36] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

static float s_texelHalf = 0.0f;
static bool s_flipV = false;

inline void mtxProj(float* _result, float _fovy, float _aspect, float _near, float _far)
{
	bx::mtxProj(_result, _fovy, _aspect, _near, _far, s_flipV);
}

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
			float tmp = minv;
			minv = maxv;
			maxv = tmp;

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

class ExampleOIT : public entry::AppI
{
public:
	ExampleOIT(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
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
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Create vertex stream declaration.
		PosColorVertex::init();
		PosColorTexCoord0Vertex::init();

		// Get renderer capabilities info.
		const bgfx::Caps* caps = bgfx::getCaps();

		// Setup root path for binary shaders. Shader binaries are different
		// for each renderer.
		switch (caps->rendererType)
		{
		default:
			break;

		case bgfx::RendererType::OpenGL:
		case bgfx::RendererType::OpenGLES:
			s_flipV = true;
			break;
		}

		// Imgui.
		imguiCreate();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
			  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
			, PosColorVertex::ms_layout
			);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

		// Create texture sampler uniforms.
		s_texColor0 = bgfx::createUniform("s_texColor0", bgfx::UniformType::Sampler);
		s_texColor1 = bgfx::createUniform("s_texColor1", bgfx::UniformType::Sampler);
		u_color     = bgfx::createUniform("u_color",     bgfx::UniformType::Vec4);

		m_blend          = loadProgram("vs_oit",      "fs_oit"                  );
		m_wbSeparatePass = loadProgram("vs_oit",      "fs_oit_wb_separate"      );
		m_wbSeparateBlit = loadProgram("vs_oit_blit", "fs_oit_wb_separate_blit" );
		m_wbPass         = loadProgram("vs_oit",      "fs_oit_wb"               );
		m_wbBlit         = loadProgram("vs_oit_blit", "fs_oit_wb_blit"          );

		m_fbtextures[0].idx = bgfx::kInvalidHandle;
		m_fbtextures[1].idx = bgfx::kInvalidHandle;
		m_fbh.idx = bgfx::kInvalidHandle;

		m_mode = 1;
		m_frontToBack = true;
		m_fadeInOut   = false;

		m_oldWidth  = 0;
		m_oldHeight = 0;
		m_oldReset  = m_reset;

		m_mrtSupported = true
			&& 2 <= caps->limits.maxFBAttachments
			&& bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_RT)
			&& bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::R16F,    BGFX_TEXTURE_RT)
			;

		m_timeOffset = bx::getHPCounter();
	}

	int shutdown() override
	{
		// Cleanup.
		imguiDestroy();

		if (bgfx::isValid(m_fbh) )
		{
			bgfx::destroy(m_fbh);
		}

		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_blend);
		bgfx::destroy(m_wbSeparatePass);
		bgfx::destroy(m_wbSeparateBlit);
		bgfx::destroy(m_wbPass);
		bgfx::destroy(m_wbBlit);
		bgfx::destroy(s_texColor0);
		bgfx::destroy(s_texColor1);
		bgfx::destroy(u_color);

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

			showExampleDialog(this
				, !m_mrtSupported
				? "MRT or frame buffer texture format are not supported."
				: NULL
				);

			if (m_mrtSupported)
			{
				if (m_oldWidth  != m_width
				||  m_oldHeight != m_height
				||  m_oldReset  != m_reset
				||  !bgfx::isValid(m_fbh) )
				{
					// Recreate variable size render targets when resolution changes.
					m_oldWidth  = m_width;
					m_oldHeight = m_height;
					m_oldReset  = m_reset;

					if (bgfx::isValid(m_fbh) )
					{
						bgfx::destroy(m_fbh);
					}

					m_fbtextures[0] = bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_RT);
					m_fbtextures[1] = bgfx::createTexture2D(uint16_t(m_width), uint16_t(m_height), false, 1, bgfx::TextureFormat::R16F,    BGFX_TEXTURE_RT);
					m_fbh = bgfx::createFrameBuffer(BX_COUNTOF(m_fbtextures), m_fbtextures, true);
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

				ImGui::Separator();

				ImGui::Text("Blend mode:");

				ImGui::RadioButton("None", &m_mode, 0);
				ImGui::RadioButton("Separate", &m_mode, 1);
				ImGui::RadioButton("MRT Independent", &m_mode, 2);

				ImGui::Separator();

				ImGui::Checkbox("Front to back", &m_frontToBack);
				ImGui::Checkbox("Fade in/out", &m_fadeInOut);

				ImGui::End();

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setViewRect(1, 0, 0, uint16_t(m_width), uint16_t(m_height) );

				int64_t now = bx::getHPCounter();
				const double freq = double(bx::getHPFrequency() );
				float time = (float)( (now-m_timeOffset)/freq);

				// Reference(s):
				// - Weighted, Blended Order-Independent Transparency
				//   https://web.archive.org/save/http://jcgt.org/published/0002/02/09/
				//   https://web.archive.org/web/20181126040455/http://casual-effects.blogspot.com/2014/03/weighted-blended-order-independent.html
				//
				const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
				const bx::Vec3 eye = { 0.0f, 0.0f, -7.0f };

				float view[16];
				float proj[16];

				// Set view and projection matrix for view 0.
				bx::mtxLookAt(view, eye, at);
				mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f);

				bgfx::setViewTransform(0, view, proj);

				// Set palette color for index 0
				bgfx::setPaletteColor(0, 0.0f, 0.0f, 0.0f, 0.0f);

				// Set palette color for index 1
				bgfx::setPaletteColor(1, 1.0f, 1.0f, 1.0f, 1.0f);

				bgfx::setViewClear(0
					, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
					, 1.0f // Depth
					, 0    // Stencil
					, 0    // FB texture 0, color palette 0
					, 1 == m_mode ? 1 : 0 // FB texture 1, color palette 1
					);

				bgfx::setViewClear(1
					, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
					, 1.0f // Depth
					, 0    // Stencil
					, 0    // Color palette 0
					);

				bgfx::FrameBufferHandle invalid = BGFX_INVALID_HANDLE;
				bgfx::setViewFrameBuffer(0, 0 == m_mode ? invalid : m_fbh);

				// Set view and projection matrix for view 1.
				bx::mtxIdentity(view);

				const bgfx::Caps* caps = bgfx::getCaps();
				bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f, 0.0f, caps->homogeneousDepth);
				bgfx::setViewTransform(1, view, proj);

				for (uint32_t depth = 0; depth < 3; ++depth)
				{
					uint32_t zz = m_frontToBack ? 2-depth : depth;

					for (uint32_t yy = 0; yy < 3; ++yy)
					{
						for (uint32_t xx = 0; xx < 3; ++xx)
						{
							float color[4] = { xx*1.0f/3.0f, zz*1.0f/3.0f, yy*1.0f/3.0f, 0.5f };

							if (m_fadeInOut
							&&  zz == 1)
							{
								color[3] = bx::sin(time*3.0f)*0.49f+0.5f;
							}

							bgfx::setUniform(u_color, color);

							BX_UNUSED(time);
							float mtx[16];
							bx::mtxRotateXY(mtx, time*0.023f + xx*0.21f, time*0.03f + yy*0.37f);
							//mtxIdentity(mtx);
							mtx[12] = -2.5f + float(xx)*2.5f;
							mtx[13] = -2.5f + float(yy)*2.5f;
							mtx[14] = -2.5f + float(zz)*2.5f;

							// Set transform for draw call.
							bgfx::setTransform(mtx);

							// Set vertex and index buffer.
							bgfx::setVertexBuffer(0, m_vbh);
							bgfx::setIndexBuffer(m_ibh);

							const uint64_t state = 0
								| BGFX_STATE_CULL_CW
								| BGFX_STATE_WRITE_RGB
								| BGFX_STATE_WRITE_A
								| BGFX_STATE_DEPTH_TEST_LESS
								| BGFX_STATE_MSAA
								;

							const uint64_t stateNoDepth = 0
								| BGFX_STATE_CULL_CW
								| BGFX_STATE_WRITE_RGB
								| BGFX_STATE_WRITE_A
								| BGFX_STATE_DEPTH_TEST_ALWAYS
								| BGFX_STATE_MSAA
								;

							bgfx::ProgramHandle program = BGFX_INVALID_HANDLE;
							switch (m_mode)
							{
							case 0:
								// Set vertex and fragment shaders.
								program = m_blend;

								// Set render states.
								bgfx::setState(state
									| BGFX_STATE_BLEND_ALPHA
									);
								break;

							case 1:
								// Set vertex and fragment shaders.
								program = m_wbSeparatePass;

								// Set render states.
								bgfx::setState(stateNoDepth
									| BGFX_STATE_BLEND_FUNC_SEPARATE(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ZERO, BGFX_STATE_BLEND_INV_SRC_ALPHA)
									);
								break;

							default:
								// Set vertex and fragment shaders.
								program = m_wbPass;

								// Set render states.
								bgfx::setState(stateNoDepth
									| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
									| BGFX_STATE_BLEND_INDEPENDENT
									, 0
									| BGFX_STATE_BLEND_FUNC_RT_1(BGFX_STATE_BLEND_ZERO, BGFX_STATE_BLEND_SRC_COLOR)
									);
								break;
							}

							// Submit primitive for rendering to view 0.
							bgfx::submit(0, program);
						}
					}
				}

				if (0 != m_mode)
				{
					bgfx::setTexture(0, s_texColor0, m_fbtextures[0]);
					bgfx::setTexture(1, s_texColor1, m_fbtextures[1]);
					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_INV_SRC_ALPHA, BGFX_STATE_BLEND_SRC_ALPHA)
						);
					screenSpaceQuad( (float)m_width, (float)m_height, s_flipV);
					bgfx::submit(1
						, 1 == m_mode ? m_wbSeparateBlit : m_wbBlit
						);
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

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	int32_t m_mode;
	bool m_frontToBack;
	bool m_fadeInOut;
	bool m_mrtSupported;

	uint32_t m_oldWidth;
	uint32_t m_oldHeight;
	uint32_t m_oldReset;

	entry::MouseState m_mouseState;

	int64_t m_timeOffset;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;

	bgfx::UniformHandle s_texColor0;
	bgfx::UniformHandle s_texColor1;
	bgfx::UniformHandle u_color;

	bgfx::ProgramHandle m_blend;
	bgfx::ProgramHandle m_wbSeparatePass;
	bgfx::ProgramHandle m_wbSeparateBlit;
	bgfx::ProgramHandle m_wbPass;
	bgfx::ProgramHandle m_wbBlit;

	bgfx::TextureHandle m_fbtextures[2];
	bgfx::FrameBufferHandle m_fbh;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleOIT
	, "19-oit"
	, "Weighted, Blended Order Independent Transparency."
	, "https://bkaradzic.github.io/bgfx/examples.html#oit"
	);
