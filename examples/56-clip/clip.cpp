/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

struct ClipVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout ClipVertex::ms_layout;

static const ClipVertex s_clipVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 }, { 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 }, { 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 }, { 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 }, { 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_clipIndices[] =
{
	0, 1, 2, 1, 3, 2,
	4, 6, 5, 5, 6, 7,
	0, 2, 4, 4, 2, 6,
	1, 5, 3, 5, 7, 3,
	0, 4, 1, 4, 5, 1,
	2, 3, 6, 6, 3, 7,
};

static const ClipVertex s_capVertices[] =
{
	{ -1.0f, 0.0f, -1.0f, 0xff0000ff },
	{ 1.0f, 0.0f, -1.0f,  0xff0000ff },
	{ -1.0f, 0.0f,  1.0f, 0xff0000ff },
	{ 1.0f, 0.0f,  1.0f,  0xff0000ff },
};

static const uint16_t s_capIndices[] = { 0, 1, 2, 1, 3, 2 };

class ExampleClip : public entry::AppI
{
public:
	ExampleClip(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
		, m_width(0)
		, m_height(0)
		, m_debug(BGFX_DEBUG_NONE)
		, m_reset(BGFX_RESET_VSYNC)
		, m_vbh(BGFX_INVALID_HANDLE)
		, m_ibh(BGFX_INVALID_HANDLE)
		, m_capVbh(BGFX_INVALID_HANDLE)
		, m_capIbh(BGFX_INVALID_HANDLE)
		, m_program(BGFX_INVALID_HANDLE)
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
		init.swapChain.nwh = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.swapChain.ndt = entry::getNativeDisplayHandle();
		init.platformData.type = entry::getNativeWindowHandleType();
		init.swapChain.width = m_width;
		init.swapChain.height = m_height;
		init.reset = m_reset;
		bgfx::init(init);

		bgfx::setDebug(m_debug);
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH|BGFX_CLEAR_STENCIL, 0x303030ff, 1.0f, 0);

		// Create vertex stream declaration.
		ClipVertex::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_clipVertices, sizeof(s_clipVertices)), ClipVertex::ms_layout);

		// Create static index buffer for triangle list rendering.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_clipIndices, sizeof(s_clipIndices)));

		// Create the plane used to visualize the clipped opening.
		m_capVbh = bgfx::createVertexBuffer(bgfx::makeRef(s_capVertices, sizeof(s_capVertices)), ClipVertex::ms_layout);
		m_capIbh = bgfx::createIndexBuffer(bgfx::makeRef(s_capIndices, sizeof(s_capIndices)));

		// Create program from shaders.
		m_program = loadProgram("vs_clip", "fs_clip");
		m_clipPlane = bgfx::createUniform("u_clipPlane", bgfx::UniformType::Vec4);

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_capIbh);
		bgfx::destroy(m_capVbh);
		bgfx::destroy(m_program);
		bgfx::destroy(m_clipPlane);
		bgfx::shutdown();
		return 0;
	}

	bool update() override
	{
		if (entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			return false;

		imguiBeginFrame(m_mouseState.m_mx, m_mouseState.m_my,
			(m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
			| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
			| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0),
			m_mouseState.m_mz, uint16_t(m_width), uint16_t(m_height));
		showExampleDialog(this);
		imguiEndFrame();

		// Isometric-style camera: view the origin diagonally from above.
		const bx::Vec3 at = { 0.0f, 0.0f, 0.0f };
		const bx::Vec3 eye = { 6.0f, 5.0f, -6.0f };
		// Set view and projection matrix for view 0.
		float view[16];
		float proj[16];
		bx::mtxLookAt(view, eye, at);

		const float aspect = float(m_width) / float(m_height);
		const float viewHeight = 4.0f;
		const float viewWidth = viewHeight * aspect;
		bx::mtxOrtho(
			proj
			, -viewWidth * 0.5f
			,  viewWidth * 0.5f
			, -viewHeight * 0.5f
			,  viewHeight * 0.5f
			,  0.1f
			,  100.0f
			,  0.0f
			,  bgfx::getCaps()->homogeneousDepth
			);

		for (bgfx::ViewId viewId = 0; viewId < 4; ++viewId)
		{
			bgfx::setViewRect(viewId, 0, 0, uint16_t(m_width), uint16_t(m_height));
			bgfx::setViewTransform(viewId, view, proj);
		}

		float model[16];
		bx::mtxIdentity(model);

		// Clip against the horizontal plane y = 0.
		const float clipPlane[4] = { 0.0f, 0.5f, 0.0f, 0.0f };
		bgfx::setUniform(m_clipPlane, clipPlane);

		// Pass 0: Increment the stencil where backface exists.
		bgfx::setTransform(model);
		bgfx::setVertexBuffer(0, m_vbh);
		bgfx::setIndexBuffer(m_ibh);
		bgfx::setStencil(
			BGFX_STENCIL_TEST_ALWAYS
			| BGFX_STENCIL_OP_FAIL_S_KEEP
			| BGFX_STENCIL_OP_FAIL_Z_KEEP
			| BGFX_STENCIL_OP_PASS_Z_INCRSAT
			, BGFX_STENCIL_NONE
			);
		bgfx::setState(
			BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			);
		bgfx::submit(0, m_program);

		// Pass 1: Decrement the stencil where frontface exists to leave peeping backface in stencil.
		bgfx::setStencil(
			BGFX_STENCIL_TEST_ALWAYS
			| BGFX_STENCIL_OP_FAIL_S_KEEP
			| BGFX_STENCIL_OP_FAIL_Z_KEEP
			| BGFX_STENCIL_OP_PASS_Z_DECRSAT
			, BGFX_STENCIL_NONE
			);
		bgfx::setState(
			BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CW
			);
		bgfx::submit(1, m_program);

		// Pass 2: render the clipped cube normally.
		bgfx::setStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);
		bgfx::setTransform(model);
		bgfx::setVertexBuffer(0, m_vbh);
		bgfx::setIndexBuffer(m_ibh);
		bgfx::setState(
			BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A|BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS|BGFX_STATE_MSAA
			);
		bgfx::submit(2, m_program);

		// Pass 3: Render the capp masked with above computed stencil.
		bgfx::setTransform(model);
		bgfx::setVertexBuffer(0, m_capVbh);
		bgfx::setIndexBuffer(m_capIbh);
		bgfx::setStencil(
			BGFX_STENCIL_TEST_NOTEQUAL
			| BGFX_STENCIL_FUNC_REF(0)
			| BGFX_STENCIL_FUNC_RMASK(0xff)
			| BGFX_STENCIL_OP_FAIL_S_KEEP
			| BGFX_STENCIL_OP_FAIL_Z_KEEP
			| BGFX_STENCIL_OP_PASS_Z_KEEP
			, BGFX_STENCIL_NONE
			);
		bgfx::setState(
			BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A
			| BGFX_STATE_DEPTH_TEST_LESS|BGFX_STATE_MSAA
			);
		bgfx::submit(3, m_program);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
		return true;
	}

	entry::MouseState m_mouseState;
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::VertexBufferHandle m_capVbh;
	bgfx::IndexBufferHandle m_capIbh;
	bgfx::ProgramHandle m_program;
	bgfx::UniformHandle m_clipPlane;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleClip
	, "56-clip"
	, "Rendering a simple position/color geometry for clipping experiments."
	//, "https://bkaradzic.github.io/bgfx/examples.html#clip" : Pending implementation
	);
