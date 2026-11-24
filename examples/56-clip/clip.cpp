/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

static const char* s_axisNames[] = { "X", "Y", "Z" };

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

static const ClipVertex s_capYVertices[] =
{
	{ -1.0f, 0.0f, -1.0f, 0xff0000ff },
	{ 1.0f, 0.0f, -1.0f,  0xff0000ff },
	{ -1.0f, 0.0f,  1.0f, 0xff0000ff },
	{ 1.0f, 0.0f,  1.0f,  0xff0000ff },
};

static const ClipVertex s_capZVertices[] =
{
	{ -1.0f, -1.0f, 0.0f, 0xff0080ff },
	{ 1.0f, -1.0f, 0.0f,  0xff0080ff },
	{ -1.0f,  1.0f, 0.0f, 0xff0080ff },
	{ 1.0f,  1.0f, 0.0f, 0xff0080ff },
};

static const uint16_t s_capIndices[] = { 0, 1, 2, 1, 3, 2 };

static void buildCapVertices(uint8_t _axis, float _distance, uint32_t _color, ClipVertex* _vertices)
{
	const float min = -1.0f;
	const float max =  1.0f;

	switch (_axis)
	{
	case 0: // x = distance
		_vertices[0] = { _distance, min, min, _color };
		_vertices[1] = { _distance, max, min, _color };
		_vertices[2] = { _distance, min, max, _color };
		_vertices[3] = { _distance, max, max, _color };
		break;

	case 1: // y = distance
		_vertices[0] = { min, _distance, min, _color };
		_vertices[1] = { max, _distance, min, _color };
		_vertices[2] = { min, _distance, max, _color };
		_vertices[3] = { max, _distance, max, _color };
		break;

	default: // z = distance
		_vertices[0] = { min, min, _distance, _color };
		_vertices[1] = { max, min, _distance, _color };
		_vertices[2] = { min, max, _distance, _color };
		_vertices[3] = { max, max, _distance, _color };
		break;
	}
}

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
		, m_capYVbh(BGFX_INVALID_HANDLE)
		, m_capZVbh(BGFX_INVALID_HANDLE)
		, m_capIbh(BGFX_INVALID_HANDLE)
		, m_program(BGFX_INVALID_HANDLE)
		, m_stencilProgram(BGFX_INVALID_HANDLE)
		, m_capProgram(BGFX_INVALID_HANDLE)
		, m_clipPlane0(BGFX_INVALID_HANDLE)
		, m_clipPlane1(BGFX_INVALID_HANDLE)
		, m_cameraPos(BGFX_INVALID_HANDLE)
		, m_capIndex(BGFX_INVALID_HANDLE)
		, m_planeAxis0(1)
		, m_planeAxis1(2)
		, m_planeDistance0(0.0f)
		, m_planeDistance1(0.0f)
		, m_invertNormal0(false)
		, m_invertNormal1(false)
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
		bgfx::setViewName(0, "Stencil back faces");
		bgfx::setViewName(1, "Stencil front faces");
		bgfx::setViewName(2, "Clipped mesh");
		bgfx::setViewName(3, "Y cap");
		bgfx::setViewName(4, "Z cap");

		// Create vertex stream declaration.
		ClipVertex::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_clipVertices, sizeof(s_clipVertices)), ClipVertex::ms_layout);

		// Create static index buffer for triangle list rendering.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_clipIndices, sizeof(s_clipIndices)));

		// Create one cap plane for each clipping plane.
		m_capYVbh = bgfx::createDynamicVertexBuffer(4, ClipVertex::ms_layout);
		m_capZVbh = bgfx::createDynamicVertexBuffer(4, ClipVertex::ms_layout);
		m_capIbh = bgfx::createIndexBuffer(bgfx::makeRef(s_capIndices, sizeof(s_capIndices)));

		// Create the normal, stencil, and cap programs.
		m_program = loadProgram("vs_clip", "fs_clip");
		m_stencilProgram = loadProgram("vs_clip", "fs_clip_stencil");
		m_capProgram = loadProgram("vs_clip", "fs_cap");
		m_clipPlane0 = bgfx::createUniform("u_clipPlane0", bgfx::UniformType::Vec4);
		m_clipPlane1 = bgfx::createUniform("u_clipPlane1", bgfx::UniformType::Vec4);
		m_cameraPos = bgfx::createUniform("u_cameraPos", bgfx::UniformType::Vec4);
		m_capIndex = bgfx::createUniform("u_capIndex", bgfx::UniformType::Vec4);

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_capIbh);
		bgfx::destroy(m_capZVbh);
		bgfx::destroy(m_capYVbh);
		bgfx::destroy(m_capProgram);
		bgfx::destroy(m_stencilProgram);
		bgfx::destroy(m_program);
		bgfx::destroy(m_clipPlane0);
		bgfx::destroy(m_clipPlane1);
		bgfx::destroy(m_cameraPos);
		bgfx::destroy(m_capIndex);
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

		ImGui::SetNextWindowPos(
			  ImVec2(m_width - m_width / 4.0f - 10.0f, 10.0f)
			, ImGuiCond_FirstUseEver
			);
		ImGui::SetNextWindowSize(
			  ImVec2(m_width / 4.0f, m_height / 3.0f)
			, ImGuiCond_FirstUseEver
			);
		ImGui::Begin("Clipping Planes", NULL, 0);
		ImGui::Text("Kept side: coordinate <= distance");
		ImGui::Separator();

		ImGui::PushID(0);
		ImGui::Text("Plane 0");
		ImGui::Combo("Axis", &m_planeAxis0, s_axisNames, BX_COUNTOF(s_axisNames));
		ImGui::SliderFloat("Distance", &m_planeDistance0, -2.0f, 2.0f, "%.2f");
		ImGui::Checkbox("Invert normal", &m_invertNormal0);
		ImGui::PopID();

		ImGui::Separator();

		ImGui::PushID(1);
		ImGui::Text("Plane 1");
		ImGui::Combo("Axis", &m_planeAxis1, s_axisNames, BX_COUNTOF(s_axisNames));
		ImGui::SliderFloat("Distance", &m_planeDistance1, -2.0f, 2.0f, "%.2f");
		ImGui::Checkbox("Invert normal", &m_invertNormal1);
		ImGui::PopID();

		ImGui::End();
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

		for (bgfx::ViewId viewId = 0; viewId < 5; ++viewId)
		{
			bgfx::setViewRect(viewId, 0, 0, uint16_t(m_width), uint16_t(m_height));
			bgfx::setViewTransform(viewId, view, proj);
		}

		float model[16];
		bx::mtxIdentity(model);

		// Keep the negative side of both planes. For a plane at coordinate d,
		// the equation is 0.5 * (coordinate - d), so distance <= 0 keeps
		// coordinate <= d.
		float clipPlane0[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		float clipPlane1[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		const float normalSign0 = m_invertNormal0 ? -1.0f : 1.0f;
		const float normalSign1 = m_invertNormal1 ? -1.0f : 1.0f;
		clipPlane0[m_planeAxis0] = 0.5f * normalSign0;
		clipPlane0[3] = -0.5f * m_planeDistance0 * normalSign0;
		clipPlane1[m_planeAxis1] = 0.5f * normalSign1;
		clipPlane1[3] = -0.5f * m_planeDistance1 * normalSign1;
		bgfx::setUniform(m_clipPlane0, clipPlane0);
		bgfx::setUniform(m_clipPlane1, clipPlane1);

		ClipVertex cap0Vertices[4];
		ClipVertex cap1Vertices[4];
		buildCapVertices(uint8_t(m_planeAxis0), m_planeDistance0, 0xff0000ff, cap0Vertices);
		buildCapVertices(uint8_t(m_planeAxis1), m_planeDistance1, 0xff0080ff, cap1Vertices);
		bgfx::update(m_capYVbh, 0, bgfx::copy(cap0Vertices, sizeof(cap0Vertices)));
		bgfx::update(m_capZVbh, 0, bgfx::copy(cap1Vertices, sizeof(cap1Vertices)));

		// The stencil shader needs the camera position in the same space as the
		// vertex positions. The model is currently identity, so world space and
		// object space are the same here.
		const float cameraPos[4] = { eye.x, eye.y, eye.z, 1.0f };
		bgfx::setUniform(m_cameraPos, cameraPos);

		// The stencil shader uses the same test. Use it on the CPU as well so
		// that an away-facing plane does not submit a cap into the shared mask.
		const float cameraPlaneDistance0 =
			eye.x * clipPlane0[0]
			+ eye.y * clipPlane0[1]
			+ eye.z * clipPlane0[2]
			+ clipPlane0[3]
			;
		const float cameraPlaneDistance1 =
			eye.x * clipPlane1[0]
			+ eye.y * clipPlane1[1]
			+ eye.z * clipPlane1[2]
			+ clipPlane1[3]
			;
		const bool plane0FacesCamera = cameraPlaneDistance0 > 0.0f;
		const bool plane1FacesCamera = cameraPlaneDistance1 > 0.0f;

		// Pass 0: Increment the stencil where a backface exists. The stencil
		// shader only clips against planes facing the camera.
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
		bgfx::submit(0, m_stencilProgram);

		// Pass 1: Decrement the stencil where a frontface exists. Together with
		// the previous pass, this leaves nonzero values in the cap region.
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
		bgfx::submit(1, m_stencilProgram);

		// Pass 2: render the cube clipped by every active plane.
		bgfx::setStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);
		bgfx::setTransform(model);
		bgfx::setVertexBuffer(0, m_vbh);
		bgfx::setIndexBuffer(m_ibh);
		bgfx::setState(
			BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A|BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS|BGFX_STATE_MSAA
			);
		bgfx::submit(2, m_program);

		// Pass 3: render the y = 0 cap only when that plane faces the camera.
		if (plane0FacesCamera)
		{
			bgfx::setTransform(model);
			bgfx::setVertexBuffer(0, m_capYVbh);
			bgfx::setIndexBuffer(m_capIbh);
			const float yCapIndex[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			bgfx::setUniform(m_capIndex, yCapIndex);
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
			bgfx::submit(3, m_capProgram);
		}

		// Pass 4: render the z = 0 cap only when that plane faces the camera.
		if (plane1FacesCamera)
		{
			bgfx::setTransform(model);
			bgfx::setVertexBuffer(0, m_capZVbh);
			bgfx::setIndexBuffer(m_capIbh);
			const float zCapIndex[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
			bgfx::setUniform(m_capIndex, zCapIndex);
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
			bgfx::submit(4, m_capProgram);
		}

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
	bgfx::DynamicVertexBufferHandle m_capYVbh;
	bgfx::DynamicVertexBufferHandle m_capZVbh;
	bgfx::IndexBufferHandle m_capIbh;
	bgfx::ProgramHandle m_program;
	bgfx::ProgramHandle m_stencilProgram;
	bgfx::ProgramHandle m_capProgram;
	bgfx::UniformHandle m_clipPlane0;
	bgfx::UniformHandle m_clipPlane1;
	bgfx::UniformHandle m_cameraPos;
	bgfx::UniformHandle m_capIndex;
	int m_planeAxis0;
	int m_planeAxis1;
	float m_planeDistance0;
	float m_planeDistance1;
	bool m_invertNormal0;
	bool m_invertNormal1;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleClip
	, "56-clip"
	, "Rendering a simple position/color geometry for clipping experiments."
	, "https://bkaradzic.github.io/bgfx/examples.html#clip" //: Pending implementation
	);
