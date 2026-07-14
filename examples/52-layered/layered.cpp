/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
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
	};

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorVertex::ms_layout;

static PosColorVertex s_cubeVertices[] =
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

static const uint16_t s_cubeTriList[] =
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

// Full-screen triangle used to blit a single layer of the array render target.
void screenSpaceQuad(bool _originBottomLeft)
{
	if (3 == bgfx::getAvailTransientVertexBuffer(3, PosTexCoord0Vertex::ms_layout) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosTexCoord0Vertex::ms_layout);
		PosTexCoord0Vertex* vertex = (PosTexCoord0Vertex*)vb.data;

		const float minx = -1.0f;
		const float maxx =  3.0f;
		const float miny = -1.0f;
		const float maxy =  3.0f;

		float minu = 0.0f;
		float maxu = 2.0f;
		float minv = 0.0f;
		float maxv = 2.0f;

		if (_originBottomLeft)
		{
			minv = 1.0f;
			maxv = -1.0f;
		}

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_z = 0.0f;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = 0.0f;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = minx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = 0.0f;
		vertex[2].m_u = minu;
		vertex[2].m_v = maxv;

		bgfx::setVertexBuffer(0, &vb);
	}
}

// The array render target has one layer per eye.
static const uint16_t kNumLayers = 2;

// View ids.
static const bgfx::ViewId kRenderLayered = 0; // Renders both eyes in a single instanced draw.
static const bgfx::ViewId kRenderEye0    = 1; // Non-layered: one draw per eye...
static const bgfx::ViewId kRenderEye1    = 2; // ...into a single layer of the array.
static const bgfx::ViewId kDisplayLeft   = 3; // Blit layer 0 to the left half of the screen.
static const bgfx::ViewId kDisplayRight  = 4; // Blit layer 1 to the right half.

class ExampleLayered : public entry::AppI
{
public:
	ExampleLayered(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
		, m_layered(true)
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

		// Layered rendering requires the BGFX_CAPS_VIEWPORT_LAYER_ARRAY capability.
		m_layeredSupported = 0 != (bgfx::getCaps()->supported & BGFX_CAPS_VIEWPORT_LAYER_ARRAY);
		m_layered &= m_layeredSupported;

		PosColorVertex::init();
		PosTexCoord0Vertex::init();

		m_vbh = bgfx::createVertexBuffer(
			  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
			, PosColorVertex::ms_layout
			);

		m_ibh = bgfx::createIndexBuffer(
			bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList) )
			);

		// One scene shader writes gl_Layer from the instance id (layered path),
		// the other renders a single eye selected by a uniform (non-layered path).
		m_programLayered    = loadProgram("vs_layered",    "fs_layered");
		m_programNonLayered = loadProgram("vs_layered_eye", "fs_layered");
		m_programBlit       = loadProgram("vs_layered_blit","fs_layered_blit");

		s_texColor  = bgfx::createUniform("s_texColor",  bgfx::UniformType::Sampler);
		u_eyeParams = bgfx::createUniform("u_eyeParams", bgfx::UniformType::Vec4);

		m_texColor = BGFX_INVALID_HANDLE;
		m_texDepth = BGFX_INVALID_HANDLE;
		m_fbLayered = BGFX_INVALID_HANDLE;
		m_fbEye[0]  = BGFX_INVALID_HANDLE;
		m_fbEye[1]  = BGFX_INVALID_HANDLE;
		createFramebuffers();

		m_frameTime.reset();

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		destroyFramebuffers();

		bgfx::destroy(s_texColor);
		bgfx::destroy(u_eyeParams);

		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_programBlit);
		bgfx::destroy(m_programNonLayered);
		bgfx::destroy(m_programLayered);

		bgfx::shutdown();

		return 0;
	}

	void createFramebuffers()
	{
		m_texColor = bgfx::createTexture2D(
			  uint16_t(m_width)
			, uint16_t(m_height)
			, false
			, kNumLayers
			, bgfx::TextureFormat::BGRA8
			, BGFX_TEXTURE_RT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
			);

		m_texDepth = bgfx::createTexture2D(
			  uint16_t(m_width)
			, uint16_t(m_height)
			, false
			, kNumLayers
			, bgfx::TextureFormat::D16
			, BGFX_TEXTURE_RT_WRITE_ONLY
			);

		// Layered framebuffer: color and depth attachments each span all layers.
		bgfx::Attachment layered[2];
		layered[0].init(m_texColor, bgfx::Access::Write, 0, kNumLayers, 0, BGFX_RESOLVE_NONE);
		layered[1].init(m_texDepth, bgfx::Access::Write, 0, kNumLayers, 0, BGFX_RESOLVE_NONE);
		m_fbLayered = bgfx::createFrameBuffer(BX_COUNTOF(layered), layered);

		// Non-layered framebuffers: one per eye, each bound to a single layer.
		for (uint16_t ii = 0; ii < kNumLayers; ++ii)
		{
			bgfx::Attachment eye[2];
			eye[0].init(m_texColor, bgfx::Access::Write, ii, 1, 0, BGFX_RESOLVE_NONE);
			eye[1].init(m_texDepth, bgfx::Access::Write, ii, 1, 0, BGFX_RESOLVE_NONE);
			m_fbEye[ii] = bgfx::createFrameBuffer(BX_COUNTOF(eye), eye);
		}
	}

	void destroyFramebuffers()
	{
		bgfx::destroy(m_fbLayered);
		for (uint16_t ii = 0; ii < kNumLayers; ++ii)
		{
			bgfx::destroy(m_fbEye[ii]);
		}

		bgfx::destroy(m_texColor);
		bgfx::destroy(m_texDepth);
	}

	void submitScene(bgfx::ViewId _view, bgfx::ProgramHandle _program, float _time, float _eyeSeparation, bool _instanced, float _eye)
	{
		float mtx[16];
		bx::mtxRotateXY(mtx, _time, _time * 0.37f);
		bgfx::setTransform(mtx);

		bgfx::setVertexBuffer(0, m_vbh);
		bgfx::setIndexBuffer(m_ibh);

		bgfx::setState(0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CW
			| BGFX_STATE_MSAA
			);

		// x = eye separation, y = eye index (only used by the non-layered path).
		float eyeParams[4] = { _eyeSeparation, _eye, 0.0f, 0.0f };
		bgfx::setUniform(u_eyeParams, eyeParams);

		if (_instanced)
		{
			// One draw, kNumLayers instances. The vertex shader routes each
			// instance to its own array layer via gl_Layer.
			bgfx::setInstanceCount(kNumLayers);
		}

		bgfx::submit(_view, _program);
	}

	void blitLayer(bgfx::ViewId _view, float _layer)
	{
		float layerParams[4] = { _layer, 0.0f, 0.0f, 0.0f };
		bgfx::setUniform(u_eyeParams, layerParams);
		bgfx::setTexture(0, s_texColor, m_texColor);
		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
		screenSpaceQuad(bgfx::getCaps()->originBottomLeft);
		bgfx::submit(_view, m_programBlit);
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			// Recreate the array render target when the window is resized.
			if (m_width != m_oldWidth || m_height != m_oldHeight)
			{
				destroyFramebuffers();
				createFramebuffers();
				m_oldWidth  = m_width;
				m_oldHeight = m_height;
			}

			m_frameTime.frame();
			const float time = bx::toSeconds<float>(m_frameTime.getDurationTime() );

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
				  ImVec2(m_width / 5.0f, m_height / 4.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			if (!m_layeredSupported)
			{
				ImGui::TextWrapped("BGFX_CAPS_VIEWPORT_LAYER_ARRAY is not supported by this renderer.");
			}

			ImGui::BeginDisabled(!m_layeredSupported);
			ImGui::Checkbox("Layered rendering", &m_layered);
			ImGui::EndDisabled();

			ImGui::Text("Both layers of an array render target");
			ImGui::Text("are shown as left/right eye.");
			ImGui::Separator();
			ImGui::Text("Technique   : %s", m_layered ? "layered" : "non-layered");
			ImGui::Text("Scene draws : %d", m_layered ? 1 : kNumLayers);
			// Real draw-call count reported by the backend. Toggling the
			// technique changes this by one: layered renders both eyes in a
			// single draw, non-layered issues one draw per eye.
			ImGui::Text("Backend draws: %d", bgfx::getStats()->numDraw);

			ImGui::End();

			imguiEndFrame();

			const float eyeSeparation = 0.06f;

			const bx::Vec3 at  = { 0.0f, 0.0f,  0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };

			float view[16];
			bx::mtxLookAt(view, eye, at);

			// Each eye is displayed in a half-width viewport, so use that aspect.
			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) * 0.5f / float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

			if (m_layered)
			{
				bgfx::setViewFrameBuffer(kRenderLayered, m_fbLayered);
				bgfx::setViewRect(kRenderLayered, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setViewClear(kRenderLayered, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
				bgfx::setViewTransform(kRenderLayered, view, proj);

				submitScene(kRenderLayered, m_programLayered, time, eyeSeparation, true, 0.0f);
			}
			else
			{
				const bgfx::ViewId views[kNumLayers] = { kRenderEye0, kRenderEye1 };
				for (uint16_t ii = 0; ii < kNumLayers; ++ii)
				{
					bgfx::setViewFrameBuffer(views[ii], m_fbEye[ii]);
					bgfx::setViewRect(views[ii], 0, 0, uint16_t(m_width), uint16_t(m_height) );
					bgfx::setViewClear(views[ii], BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
					bgfx::setViewTransform(views[ii], view, proj);

					submitScene(views[ii], m_programNonLayered, time, eyeSeparation, false, float(ii) );
				}
			}

			// Blit each layer of the array to one half of the back buffer.
			const uint16_t halfWidth = uint16_t(m_width / 2);
			bgfx::setViewRect(kDisplayLeft,  0,         0, halfWidth, uint16_t(m_height) );
			bgfx::setViewRect(kDisplayRight, halfWidth, 0, halfWidth, uint16_t(m_height) );

			blitLayer(kDisplayLeft,  0.0f);
			blitLayer(kDisplayRight, 1.0f);

			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_oldWidth  = 0;
	uint32_t m_oldHeight = 0;
	uint32_t m_debug;
	uint32_t m_reset;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;

	bgfx::ProgramHandle m_programLayered;
	bgfx::ProgramHandle m_programNonLayered;
	bgfx::ProgramHandle m_programBlit;

	bgfx::TextureHandle m_texColor;
	bgfx::TextureHandle m_texDepth;
	bgfx::FrameBufferHandle m_fbLayered;
	bgfx::FrameBufferHandle m_fbEye[kNumLayers];

	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle u_eyeParams;

	FrameTime m_frameTime;

	bool m_layered;
	bool m_layeredSupported = false;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleLayered
	, "52-layered"
	, "Layered rendering to a texture array."
	, "https://bkaradzic.github.io/bgfx/examples.html#layered"
	);
