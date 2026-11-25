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

struct MeshChoice
{
	const char* m_name;
	const char* m_path;
};

static const MeshChoice s_meshChoices[] =
{
	{ "Bunny",          "meshes/bunny.bin"          },
	{ "Bunny decimated", "meshes/bunny_decimated.bin" },
	{ "Column",         "meshes/column.bin"         },
	{ "Cube",           "meshes/cube.bin"           },
	{ "Hollow cube",    "meshes/hollowcube.bin"    },
	{ "Orb",            "meshes/orb.bin"            },
	{ "Platform",       "meshes/platform.bin"       },
	{ "Tree",           "meshes/tree.bin"           },
	{ "Unit sphere",    "meshes/unit_sphere.bin"    },
};

static const char* s_meshNames[BX_COUNTOF(s_meshChoices)] =
{
	"Bunny",
	"Bunny decimated",
	"Column",
	"Cube",
	"Hollow cube",
	"Orb",
	"Platform",
	"Tree",
	"Unit sphere",
};

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

static const uint16_t s_capIndices[] = { 0, 1, 2, 1, 3, 2 };

static void buildCapVertices(uint8_t _axis, float _distance, const float* _min, const float* _max, uint32_t _color, ClipVertex* _vertices)
{
	switch (_axis)
	{
	case 0: // x = distance
		_vertices[0] = { _distance, _min[1], _min[2], _color };
		_vertices[1] = { _distance, _max[1], _min[2], _color };
		_vertices[2] = { _distance, _min[1], _max[2], _color };
		_vertices[3] = { _distance, _max[1], _max[2], _color };
		break;

	case 1: // y = distance
		_vertices[0] = { _min[0], _distance, _min[2], _color };
		_vertices[1] = { _max[0], _distance, _min[2], _color };
		_vertices[2] = { _min[0], _distance, _max[2], _color };
		_vertices[3] = { _max[0], _distance, _max[2], _color };
		break;

	default: // z = distance
		_vertices[0] = { _min[0], _min[1], _distance, _color };
		_vertices[1] = { _max[0], _min[1], _distance, _color };
		_vertices[2] = { _min[0], _max[1], _distance, _color };
		_vertices[3] = { _max[0], _max[1], _distance, _color };
		break;
	}
}

static bool planeIntersectsMesh(uint8_t _axis, float _distance, const float* _min, const float* _max)
{
	return _distance >= _min[_axis] && _distance <= _max[_axis];
}

static float component(const bx::Vec3& _value, uint32_t _axis)
{
	return 0 == _axis ? _value.x : 1 == _axis ? _value.y : _value.z;
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
		, m_meshSelection(0)
		, m_mesh(NULL)
	{
		for (Mesh*& mesh : m_meshes)
		{
			mesh = NULL;
		}

		m_meshBoundsMin[0] = -1.0f;
		m_meshBoundsMin[1] = -1.0f;
		m_meshBoundsMin[2] = -1.0f;
		m_meshBoundsMax[0] =  1.0f;
		m_meshBoundsMax[1] =  1.0f;
		m_meshBoundsMax[2] =  1.0f;
	}

	void selectMesh(int _selection)
	{
		m_meshSelection = bx::clamp(_selection, 0, int(BX_COUNTOF(s_meshChoices) - 1));
		m_mesh = m_meshes[m_meshSelection];

		if (NULL == m_mesh || m_mesh->m_groups.isEmpty())
		{
			return;
		}

		bool first = true;
		for (const Group& group : m_mesh->m_groups)
		{
			if (first)
			{
				m_meshBoundsMin[0] = group.m_aabb.min.x;
				m_meshBoundsMin[1] = group.m_aabb.min.y;
				m_meshBoundsMin[2] = group.m_aabb.min.z;
				m_meshBoundsMax[0] = group.m_aabb.max.x;
				m_meshBoundsMax[1] = group.m_aabb.max.y;
				m_meshBoundsMax[2] = group.m_aabb.max.z;
				first = false;
			}
			else
			{
				for (uint32_t axis = 0; axis < 3; ++axis)
				{
					m_meshBoundsMin[axis] = bx::min(m_meshBoundsMin[axis], component(group.m_aabb.min, axis));
					m_meshBoundsMax[axis] = bx::max(m_meshBoundsMax[axis], component(group.m_aabb.max, axis));
				}
			}
		}

		m_planeDistance0 = bx::clamp(m_planeDistance0, m_meshBoundsMin[m_planeAxis0], m_meshBoundsMax[m_planeAxis0]);
		m_planeDistance1 = bx::clamp(m_planeDistance1, m_meshBoundsMin[m_planeAxis1], m_meshBoundsMax[m_planeAxis1]);
	}

	void submitMesh(bgfx::ViewId _view, bgfx::ProgramHandle _program) const
	{
		if (NULL == m_mesh)
		{
			return;
		}

		for (const Group& group : m_mesh->m_groups)
		{
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(0, group.m_vbh);
			bgfx::submit(
				  _view
				, _program
				, 0
				, BGFX_DISCARD_INDEX_BUFFER|BGFX_DISCARD_VERTEX_STREAMS
				);
		}
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

		// Create the vertex stream declaration used by the generated cap quads.
		ClipVertex::init();

		for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshChoices); ++ii)
		{
			m_meshes[ii] = meshLoad(s_meshChoices[ii].m_path);
		}
		selectMesh(0);

		// Create one cap plane for each clipping plane.
		m_capYVbh = bgfx::createDynamicVertexBuffer(4, ClipVertex::ms_layout);
		m_capZVbh = bgfx::createDynamicVertexBuffer(4, ClipVertex::ms_layout);
		m_capIbh = bgfx::createIndexBuffer(bgfx::makeRef(s_capIndices, sizeof(s_capIndices)));

		// Create the normal, stencil, and cap programs.
		m_program = loadProgram("vs_clip", "fs_clip");
		m_stencilProgram = loadProgram("vs_clip", "fs_clip_stencil");
		m_capProgram = loadProgram("vs_cap", "fs_cap");
		m_clipPlane0 = bgfx::createUniform("u_clipPlane0", bgfx::UniformType::Vec4);
		m_clipPlane1 = bgfx::createUniform("u_clipPlane1", bgfx::UniformType::Vec4);
		m_cameraPos = bgfx::createUniform("u_cameraPos", bgfx::UniformType::Vec4);
		m_capIndex = bgfx::createUniform("u_capIndex", bgfx::UniformType::Vec4);

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();
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
		for (Mesh* mesh : m_meshes)
		{
			if (NULL != mesh)
			{
				meshUnload(mesh);
			}
		}
		bgfx::shutdown();
		return 0;
	}

	void drawControls()
	{
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
		ImGui::Text("Model");
		if (ImGui::Combo("Mesh", &m_meshSelection, s_meshNames, BX_COUNTOF(s_meshNames)))
		{
			selectMesh(m_meshSelection);
		}
		ImGui::Separator();
		ImGui::Text("Kept side: coordinate <= distance");
		ImGui::Separator();

		ImGui::PushID(0);
		ImGui::Text("Plane 0");
		ImGui::Combo("Axis", &m_planeAxis0, s_axisNames, BX_COUNTOF(s_axisNames));
		ImGui::SliderFloat("Distance", &m_planeDistance0, m_meshBoundsMin[m_planeAxis0], m_meshBoundsMax[m_planeAxis0], "%.2f");
		ImGui::Checkbox("Invert normal", &m_invertNormal0);
		ImGui::PopID();

		ImGui::Separator();

		ImGui::PushID(1);
		ImGui::Text("Plane 1");
		ImGui::Combo("Axis", &m_planeAxis1, s_axisNames, BX_COUNTOF(s_axisNames));
		ImGui::SliderFloat("Distance", &m_planeDistance1, m_meshBoundsMin[m_planeAxis1], m_meshBoundsMax[m_planeAxis1], "%.2f");
		ImGui::Checkbox("Invert normal", &m_invertNormal1);
		ImGui::PopID();

		ImGui::End();
		imguiEndFrame();
	}

	void setupViews(const bx::Vec3& _eye) const
	{
		const bx::Vec3 at = { 0.0f, 0.0f, 0.0f };
		// All five passes use the same camera and viewport.
		float view[16];
		float proj[16];
		bx::mtxLookAt(view, _eye, at);

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
	}

	// Center and scale the mesh; return the camera in that mesh's object space.
	bx::Vec3 buildModelTransform(float* _model, const bx::Vec3& _eye) const
	{
		const float centerX = (m_meshBoundsMin[0] + m_meshBoundsMax[0]) * 0.5f;
		const float centerY = (m_meshBoundsMin[1] + m_meshBoundsMax[1]) * 0.5f;
		const float centerZ = (m_meshBoundsMin[2] + m_meshBoundsMax[2]) * 0.5f;
		const float extentX = m_meshBoundsMax[0] - m_meshBoundsMin[0];
		const float extentY = m_meshBoundsMax[1] - m_meshBoundsMin[1];
		const float extentZ = m_meshBoundsMax[2] - m_meshBoundsMin[2];
		const float extent = bx::max(extentX, bx::max(extentY, extentZ));
		const float modelScale = extent > 0.0f ? 2.0f / extent : 1.0f;
		bx::mtxSRT(
			_model
			, modelScale, modelScale, modelScale
			, 0.0f, 0.0f, 0.0f
			, -centerX * modelScale, -centerY * modelScale, -centerZ * modelScale
			);

		return bx::Vec3(
			  _eye.x / modelScale + centerX
			, _eye.y / modelScale + centerY
			, _eye.z / modelScale + centerZ
			);
	}

	void updatePlaneUniforms(const bx::Vec3& _cameraObject, bool& _plane0FacesCamera, bool& _plane1FacesCamera) const
	{
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

		// Camera and plane equations must use the same space as v_position.
		const float cameraPos[4] = { _cameraObject.x, _cameraObject.y, _cameraObject.z, 1.0f };
		bgfx::setUniform(m_cameraPos, cameraPos);

		// The stencil shader uses the same test. Use it on the CPU as well so
		// that an away-facing plane does not submit a cap into the shared mask.
		const float cameraPlaneDistance0 =
			_cameraObject.x * clipPlane0[0]
			+ _cameraObject.y * clipPlane0[1]
			+ _cameraObject.z * clipPlane0[2]
			+ clipPlane0[3]
			;
		const float cameraPlaneDistance1 =
			_cameraObject.x * clipPlane1[0]
			+ _cameraObject.y * clipPlane1[1]
			+ _cameraObject.z * clipPlane1[2]
			+ clipPlane1[3]
			;
		_plane0FacesCamera = cameraPlaneDistance0 > 0.0f;
		_plane1FacesCamera = cameraPlaneDistance1 > 0.0f;
	}

	void updateCapGeometry() const
	{
		ClipVertex cap0Vertices[4];
		ClipVertex cap1Vertices[4];
		buildCapVertices(uint8_t(m_planeAxis0), m_planeDistance0, m_meshBoundsMin, m_meshBoundsMax, 0xff0000ff, cap0Vertices);
		buildCapVertices(uint8_t(m_planeAxis1), m_planeDistance1, m_meshBoundsMin, m_meshBoundsMax, 0xff0080ff, cap1Vertices);
		bgfx::update(m_capYVbh, 0, bgfx::copy(cap0Vertices, sizeof(cap0Vertices)));
		bgfx::update(m_capZVbh, 0, bgfx::copy(cap1Vertices, sizeof(cap1Vertices)));
	}

	bool update() override
	{
		if (entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			return false;

		drawControls();

		// Isometric-style camera: view the origin diagonally from above.
		const bx::Vec3 eye = { 6.0f, 5.0f, -6.0f };
		setupViews(eye);
		float model[16];
		const bx::Vec3 cameraObject = buildModelTransform(model, eye);
		bool plane0FacesCamera = false;
		bool plane1FacesCamera = false;
		updatePlaneUniforms(cameraObject, plane0FacesCamera, plane1FacesCamera);
		updateCapGeometry();

		const bool plane0IntersectsMesh = planeIntersectsMesh(uint8_t(m_planeAxis0), m_planeDistance0, m_meshBoundsMin, m_meshBoundsMax);
		const bool plane1IntersectsMesh = planeIntersectsMesh(uint8_t(m_planeAxis1), m_planeDistance1, m_meshBoundsMin, m_meshBoundsMax);

		// Pass 0: Increment the stencil where a backface exists.
		bgfx::setTransform(model);
		const uint32_t stencilIncrement =
			BGFX_STENCIL_TEST_ALWAYS
			| BGFX_STENCIL_OP_FAIL_S_KEEP
			| BGFX_STENCIL_OP_FAIL_Z_KEEP
			| BGFX_STENCIL_OP_PASS_Z_INCRSAT
			;
		// NONE applies the first state to both face orientations and supplies
		// the 0xff write mask encoded in the second argument by this bgfx revision.
		bgfx::setStencil(stencilIncrement, BGFX_STENCIL_NONE);
		bgfx::setState(
			BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CW
			);
		submitMesh(0, m_stencilProgram);

		// Pass 1: Decrement the stencil where a frontface exists. Together with
		// the previous pass, this leaves nonzero values in the cap region.
		const uint32_t stencilDecrement =
			BGFX_STENCIL_TEST_ALWAYS
			| BGFX_STENCIL_OP_FAIL_S_KEEP
			| BGFX_STENCIL_OP_FAIL_Z_KEEP
			| BGFX_STENCIL_OP_PASS_Z_DECRSAT
			;
		bgfx::setStencil(stencilDecrement, BGFX_STENCIL_NONE);
		bgfx::setState(
			BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			);
		submitMesh(1, m_stencilProgram);

		// Pass 2: render the mesh clipped by every active plane.
		bgfx::setStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);
		bgfx::setTransform(model);
		bgfx::setState(
			BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A|BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS|BGFX_STATE_MSAA
			);
		submitMesh(2, m_program);

		// Pass 3: render the first cap only when the plane faces the camera and
		// intersects the mesh bounds. Outside those bounds, there is no cap.
		if (plane0FacesCamera && plane0IntersectsMesh)
		{
			bgfx::setTransform(model);
			bgfx::setVertexBuffer(0, m_capYVbh);
			bgfx::setIndexBuffer(m_capIbh);
			const float yCapIndex[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			bgfx::setUniform(m_capIndex, yCapIndex);
			const uint32_t capStencil =
				BGFX_STENCIL_TEST_NOTEQUAL
				| BGFX_STENCIL_FUNC_REF(0)
				| BGFX_STENCIL_FUNC_RMASK(0xff)
				| BGFX_STENCIL_OP_FAIL_S_KEEP
				| BGFX_STENCIL_OP_FAIL_Z_KEEP
				| BGFX_STENCIL_OP_PASS_Z_KEEP
				;
			bgfx::setStencil(capStencil, capStencil);
			bgfx::setState(
				BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_LESS|BGFX_STATE_MSAA
				);
			bgfx::submit(3, m_capProgram);
		}

		// Pass 4: render the second cap only when the plane faces the camera and
		// intersects the mesh bounds. Outside those bounds, there is no cap.
		if (plane1FacesCamera && plane1IntersectsMesh)
		{
			bgfx::setTransform(model);
			bgfx::setVertexBuffer(0, m_capZVbh);
			bgfx::setIndexBuffer(m_capIbh);
			const float zCapIndex[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
			bgfx::setUniform(m_capIndex, zCapIndex);
			const uint32_t capStencil =
				BGFX_STENCIL_TEST_NOTEQUAL
				| BGFX_STENCIL_FUNC_REF(0)
				| BGFX_STENCIL_FUNC_RMASK(0xff)
				| BGFX_STENCIL_OP_FAIL_S_KEEP
				| BGFX_STENCIL_OP_FAIL_Z_KEEP
				| BGFX_STENCIL_OP_PASS_Z_KEEP
				;
			bgfx::setStencil(capStencil, capStencil);
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
	int m_meshSelection;
	Mesh* m_meshes[BX_COUNTOF(s_meshChoices)];
	Mesh* m_mesh;
	float m_meshBoundsMin[3];
	float m_meshBoundsMax[3];
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleClip
	, "56-clip"
	, "Clipping runtime meshes with stencil-based caps."
	, "https://bkaradzic.github.io/bgfx/examples.html#clip" //: Pending implementation
	);
