/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

static const uint8_t kNumClipPlanes = 6;
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
static const uint16_t s_planeOutlineIndices[] = { 0, 1, 1, 3, 3, 2, 2, 0 };

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
		, m_capIbh(BGFX_INVALID_HANDLE)
		, m_planeIbh(BGFX_INVALID_HANDLE)
		, m_program(BGFX_INVALID_HANDLE)
		, m_stencilProgram(BGFX_INVALID_HANDLE)
		, m_capProgram(BGFX_INVALID_HANDLE)
		, m_planeProgram(BGFX_INVALID_HANDLE)
		, m_clipPlanes(BGFX_INVALID_HANDLE)
		, m_cameraPos(BGFX_INVALID_HANDLE)
		, m_capIndex(BGFX_INVALID_HANDLE)
		, m_meshSelection(0)
		, m_mesh(NULL)
	{
		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			m_capVbh[ii].idx = bgfx::kInvalidHandle;
			m_planeVbh[ii].idx = bgfx::kInvalidHandle;
			m_planeAxis[ii] = ii / 2;
			m_planeDistance[ii] = 0.0f;
			m_invertNormal[ii] = 0 != (ii % 2);
		}

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

		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			m_planeDistance[ii] = m_invertNormal[ii]
				? m_meshBoundsMin[m_planeAxis[ii]]
				: m_meshBoundsMax[m_planeAxis[ii]];
		}
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
		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			bgfx::setViewName(bgfx::ViewId(3 + ii), "Clipping plane cap");
			bgfx::setViewName(bgfx::ViewId(3 + kNumClipPlanes + ii), "Clipping plane outline");
		}

		// Create the vertex stream declaration used by the generated cap quads.
		ClipVertex::init();

		for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshChoices); ++ii)
		{
			m_meshes[ii] = meshLoad(s_meshChoices[ii].m_path);
		}
		selectMesh(0);

		// Create a dynamic quad buffer for each clipping plane cap.
		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			m_capVbh[ii] = bgfx::createDynamicVertexBuffer(4, ClipVertex::ms_layout);
			m_planeVbh[ii] = bgfx::createDynamicVertexBuffer(4, ClipVertex::ms_layout);
		}
		m_capIbh = bgfx::createIndexBuffer(bgfx::makeRef(s_capIndices, sizeof(s_capIndices)));
		m_planeIbh = bgfx::createIndexBuffer(bgfx::makeRef(s_planeOutlineIndices, sizeof(s_planeOutlineIndices)));

		// Create the normal, stencil, and cap programs.
		m_program = loadProgram("vs_clip", "fs_clip");
		m_stencilProgram = loadProgram("vs_clip", "fs_clip_stencil");
		m_capProgram = loadProgram("vs_cap", "fs_cap");
		m_planeProgram = loadProgram("vs_cap", "fs_plane");
		BX_ASSERT(bgfx::isValid(m_planeProgram), "Failed to create clipping plane outline program");
		m_clipPlanes = bgfx::createUniform("u_clipPlanes", bgfx::UniformType::Vec4, kNumClipPlanes);
		m_cameraPos = bgfx::createUniform("u_cameraPos", bgfx::UniformType::Vec4);
		m_capIndex = bgfx::createUniform("u_capIndex", bgfx::UniformType::Vec4);

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();
		bgfx::destroy(m_capIbh);
		bgfx::destroy(m_planeIbh);
		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			bgfx::destroy(m_capVbh[ii]);
			bgfx::destroy(m_planeVbh[ii]);
		}
		bgfx::destroy(m_capProgram);
		bgfx::destroy(m_planeProgram);
		bgfx::destroy(m_stencilProgram);
		bgfx::destroy(m_program);
		bgfx::destroy(m_clipPlanes);
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
		ImGui::Text("Normal: coordinate <= distance");
		ImGui::Text("Inverted: coordinate >= distance");
		ImGui::Separator();

		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			if (ii > 0)
			{
				ImGui::Separator();
			}
			ImGui::PushID(ii);
			ImGui::Text("Plane %u", uint32_t(ii + 1));
			ImGui::Combo("Axis", &m_planeAxis[ii], s_axisNames, BX_COUNTOF(s_axisNames));
			ImGui::SliderFloat("Distance", &m_planeDistance[ii], m_meshBoundsMin[m_planeAxis[ii]], m_meshBoundsMax[m_planeAxis[ii]], "%.2f");
			ImGui::Checkbox("Invert normal", &m_invertNormal[ii]);
			ImGui::PopID();
		}

		ImGui::End();
		imguiEndFrame();
	}

	void setupViews(const bx::Vec3& _eye) const
	{
		const bx::Vec3 at = { 0.0f, 0.0f, 0.0f };
		// All nine passes use the same camera and viewport.
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

		for (bgfx::ViewId viewId = 0; viewId < 3 + 2 * kNumClipPlanes; ++viewId)
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

	void updatePlaneUniforms(const bx::Vec3& _cameraObject, bool* _planeFacesCamera) const
	{
		float clipPlanes[kNumClipPlanes][4] = {};
		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			const float normalSign = m_invertNormal[ii] ? -1.0f : 1.0f;
			clipPlanes[ii][m_planeAxis[ii]] = 0.5f * normalSign;
			clipPlanes[ii][3] = -0.5f * m_planeDistance[ii] * normalSign;
		}
		bgfx::setUniform(m_clipPlanes, clipPlanes[0], kNumClipPlanes);

		// Camera and plane equations must use the same space as v_position.
		const float cameraPos[4] = { _cameraObject.x, _cameraObject.y, _cameraObject.z, 1.0f };
		bgfx::setUniform(m_cameraPos, cameraPos);

		// The stencil shader uses the same test. Use it on the CPU as well so
		// that an away-facing plane does not submit a cap into the shared mask.
		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			const float cameraPlaneDistance =
				_cameraObject.x * clipPlanes[ii][0]
				+ _cameraObject.y * clipPlanes[ii][1]
				+ _cameraObject.z * clipPlanes[ii][2]
				+ clipPlanes[ii][3]
				;
			_planeFacesCamera[ii] = cameraPlaneDistance > 0.0f;
		}
	}

	void updateCapGeometry() const
	{
		static const uint32_t capColors[kNumClipPlanes] =
		{
			0xff0000ff, 0xff0080ff, 0xff00ff00,
			0xffff0000, 0xffffff00, 0xffff00ff,
		};
		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			ClipVertex vertices[4];
			buildCapVertices(uint8_t(m_planeAxis[ii]), m_planeDistance[ii], m_meshBoundsMin, m_meshBoundsMax, capColors[ii], vertices);
			bgfx::update(m_capVbh[ii], 0, bgfx::copy(vertices, sizeof(vertices)));
			for (ClipVertex& vertex : vertices)
			{
				vertex.m_abgr = (capColors[ii] & 0x00ffffff) | 0x33000000;
			}
			bgfx::update(m_planeVbh[ii], 0, bgfx::copy(vertices, sizeof(vertices)));
		}
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
		bool planeFacesCamera[kNumClipPlanes] = {};
		updatePlaneUniforms(cameraObject, planeFacesCamera);
		updateCapGeometry();

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

		// Passes 3-8: render each cap inside the stencil mask when its plane
		// faces the camera and intersects the mesh bounds.
		const uint32_t capStencil =
			BGFX_STENCIL_TEST_NOTEQUAL
			| BGFX_STENCIL_FUNC_REF(0)
			| BGFX_STENCIL_FUNC_RMASK(0xff)
			| BGFX_STENCIL_OP_FAIL_S_KEEP
			| BGFX_STENCIL_OP_FAIL_Z_KEEP
			| BGFX_STENCIL_OP_PASS_Z_KEEP
			;
		for (uint8_t ii = 0; ii < kNumClipPlanes; ++ii)
		{
			const bool intersectsMesh = planeIntersectsMesh(uint8_t(m_planeAxis[ii]), m_planeDistance[ii], m_meshBoundsMin, m_meshBoundsMax);
			if (!planeFacesCamera[ii] || !intersectsMesh)
			{
				continue;
			}

			bgfx::setTransform(model);
			bgfx::setVertexBuffer(0, m_capVbh[ii]);
			bgfx::setIndexBuffer(m_capIbh);
			const float capIndex[4] = { float(ii), 0.0f, 0.0f, 0.0f };
			bgfx::setUniform(m_capIndex, capIndex);
			bgfx::setStencil(capStencil, BGFX_STENCIL_NONE);
			bgfx::setState(
				BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_LESS|BGFX_STATE_MSAA
				);
			bgfx::submit(bgfx::ViewId(3 + ii), m_capProgram);
		}

		// Passes 9-14: outline each clipping plane across the mesh bounds.
		bgfx::setStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);
		for (uint8_t ii = 0; bgfx::isValid(m_planeProgram) && ii < kNumClipPlanes; ++ii)
		{
			bgfx::setTransform(model);
			bgfx::setVertexBuffer(0, m_planeVbh[ii]);
			bgfx::setIndexBuffer(m_planeIbh);
			bgfx::setState(
				BGFX_STATE_WRITE_RGB|BGFX_STATE_WRITE_A
				| BGFX_STATE_BLEND_ALPHA|BGFX_STATE_MSAA
				| BGFX_STATE_PT_LINES
				);
			bgfx::submit(bgfx::ViewId(3 + kNumClipPlanes + ii), m_planeProgram);
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
	bgfx::DynamicVertexBufferHandle m_capVbh[kNumClipPlanes];
	bgfx::DynamicVertexBufferHandle m_planeVbh[kNumClipPlanes];
	bgfx::IndexBufferHandle m_capIbh;
	bgfx::IndexBufferHandle m_planeIbh;
	bgfx::ProgramHandle m_program;
	bgfx::ProgramHandle m_stencilProgram;
	bgfx::ProgramHandle m_capProgram;
	bgfx::ProgramHandle m_planeProgram;
	bgfx::UniformHandle m_clipPlanes;
	bgfx::UniformHandle m_cameraPos;
	bgfx::UniformHandle m_capIndex;
	int m_planeAxis[kNumClipPlanes];
	float m_planeDistance[kNumClipPlanes];
	bool m_invertNormal[kNumClipPlanes];
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
