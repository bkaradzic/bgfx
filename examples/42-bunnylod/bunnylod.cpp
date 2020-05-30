/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <bx/easing.h>
#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

extern "C" void ProgressiveMesh(int vert_n, int vert_stride, const float *v, int tri_n, const int *tri, int *map, int *permutation);

static void * Alloc(size_t sz) {
	return BX_ALLOC(entry::getAllocator(), sz);
}

static void Free(void *p) {
	BX_FREE(entry::getAllocator(), p);
}

namespace
{

class ExampleBunnyLOD : public entry::AppI
{
public:
	ExampleBunnyLOD(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void PermuteMesh(const bgfx::Memory *vb, const bgfx::Memory *ib, const bgfx::VertexLayout &layout) {
		int i;
		int stride = layout.getStride();
		int offset = layout.getOffset(bgfx::Attrib::Position);
		int vertices = vb->size / stride;
		int triangles = ib->size / ( 3 * sizeof(uint32_t) );
		int *permutation = (int*)Alloc(vertices * sizeof(int));
		m_map = (int *)Alloc(vertices * sizeof(int));

		// It will takes long time if there are too many vertices.
		ProgressiveMesh(vertices, stride, (const float *)(vb->data + offset), triangles, (const int *)ib->data, m_map, permutation);

		// rearrange the vertex Array
		char * temp = (char *)Alloc(vertices * stride);
		bx::memCopy(temp, vb->data, vb->size);
		for (i = 0; i<vertices; i++) {
			bx::memCopy(vb->data + permutation[i] * stride , temp + i * stride, stride);
		}
		Free(temp);

		// update the changes in the entries in the triangle Array
		for (i = 0; i<triangles * 3; i++) {
			int *indices = (int *)(ib->data + i * sizeof(uint32_t));
			*indices = permutation[*indices];
		}

		Free(permutation);
	}

	int findDuplicateVertices(const char *vb, int n, const bgfx::VertexLayout &layout, int *map) {
		int i,j;
		int stride = layout.getStride();
		int poffset = layout.getOffset(bgfx::Attrib::Position);
		for (i=0;i<n;i++) {
			map[i] = i;
		}
		int merge = 0;
		for (i=merge;i<n;i++) {
			if (map[i] == i) {
				float *p1 = (float *)(vb + i*stride + poffset);
				map[i] = merge;
				for (j=i+1;j<n;j++) {
					if (map[j] == j) {
						float *p2 = (float *)(vb + j*stride + poffset);
						if (p1[0] == p2[0] && p1[1] == p2[1] && p1[2] == p2[2]) {
							map[j] = merge;
						}
					}
				}
				++merge;
			}
		}
		return merge;
	}

	const bgfx::Memory * mergeVertices(const char *vb, int stride, const int *map, int n, int merged) {
		const bgfx::Memory * buffer = bgfx::alloc(stride * merged);
		int i;
		int target = 0;
		for (i=0;i<n;i++) {
			if (map[i] == target) {
				bx::memCopy(buffer->data + target*stride, vb + i*stride, stride);
				++target;
			}
		}
		return buffer;
	}

	void loadMesh(Mesh *mesh) {
		// merge sub mesh
		int vertices = 0;
		int indices = 0;
		for (GroupArray::const_iterator it = mesh->m_groups.begin(), itEnd = mesh->m_groups.end(); it != itEnd; ++it) {
			vertices += it->m_numVertices;
			indices += it->m_numIndices;
		}

		const bgfx::Memory *ib = bgfx::alloc(indices * sizeof(uint32_t));
		char * vb_data = (char *)Alloc(mesh->m_layout.getSize(vertices));

		size_t voffset = 0;
		size_t ioffset = 0;
		int index = 0;
		for (GroupArray::const_iterator it = mesh->m_groups.begin(), itEnd = mesh->m_groups.end(); it != itEnd; ++it) {
			size_t vsize = mesh->m_layout.getSize(it->m_numVertices);
			bx::memCopy(vb_data + voffset, it->m_vertices, vsize);
			uint32_t *ibptr = (uint32_t *)(ib->data + ioffset);
			for (uint32_t i = 0; i<it->m_numIndices; i++) {
				ibptr[i] = it->m_indices[i] + index;
			}
			voffset+=vsize;
			ioffset+=it->m_numIndices * sizeof(uint32_t);
			index+=it->m_numVertices;
		}

		int * map = (int *)Alloc(vertices * sizeof(int));
		int	merged	= findDuplicateVertices(vb_data, vertices, mesh->m_layout, map);

		const bgfx::Memory *vb = mergeVertices(vb_data, mesh->m_layout.getStride(), map, vertices, merged);
		Free(vb_data);
		vertices = merged;

		int i;
		int *ib_data = (int *)ib->data;
		for (i=0; i<indices; i++) {
			ib_data[i] = map[ib_data[i]];
		}

		Free(map);

		PermuteMesh(vb, ib, mesh->m_layout);

		m_triangle = (int *)Alloc(ib->size);
		bx::memCopy(m_triangle, ib->data, ib->size);

		m_vb = bgfx::createVertexBuffer(vb, mesh->m_layout);
		m_ib = bgfx::createDynamicIndexBuffer(ib, BGFX_BUFFER_INDEX32);

		m_numVertices = vertices;
		m_numTriangles = indices/3;
		m_totalVertices = m_numVertices;
		m_totalTriangles = m_numTriangles;
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

		// Set view 0 clear state.
		bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
				);

		u_tint = bgfx::createUniform("u_tint", bgfx::UniformType::Vec4);

		// Create program from shaders.
		m_program = loadProgram("vs_picking_shaded", "fs_picking_shaded");

		Mesh *mesh = meshLoad("meshes/bunny_patched.bin", true);
		loadMesh(mesh);
		meshUnload(mesh);

		m_timeOffset = bx::getHPCounter();
		m_LOD = 1.0f;
		m_lastLOD = m_LOD;

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();

		// Cleanup.
		bgfx::destroy(m_program);
		bgfx::destroy(m_vb);
		bgfx::destroy(m_ib);
		bgfx::destroy(u_tint);

		Free(m_map);
		Free(m_triangle);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	void updateIndexBuffer() {
		int verts = bx::easeInQuad(m_LOD) * m_totalVertices;
		if (verts <= 0)
			return;

		int i,j;
		int tris = 0;
		const bgfx::Memory * ib = bgfx::alloc(m_totalTriangles * 3 * sizeof(uint32_t));

		for (i = 0; i < (int)m_totalTriangles; i++) {
			int v[3];
			for (j=0;j<3;j++) {
				int idx = m_triangle[i*3+j];
				while (idx >= verts) {
					idx = m_map[idx];
				}
				v[j] = idx;
			}
			if (v[0] != v[1] && v[0] != v[2] && v[1] != v[2]) {
				bx::memCopy(ib->data + tris * 3 * sizeof(uint32_t), v, 3 * sizeof(int));
				++tris;
			}
		}
		m_numTriangles = tris;
		m_numVertices = verts;

		bgfx::update(m_ib, 0, ib);

	}

	void submitLOD(bgfx::ViewId viewid, const float *mtx) {
		bgfx::setTransform(mtx);
		bgfx::setState(0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			| BGFX_STATE_MSAA
		);

		if (m_LOD != m_lastLOD) {
			updateIndexBuffer();
			m_lastLOD = m_LOD;
		}

		bgfx::setIndexBuffer(m_ib, 0, m_numTriangles*3);
		bgfx::setVertexBuffer(0, m_vb, 0, m_numVertices);
		bgfx::submit(viewid, m_program);
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

			showExampleDialog(this);

			ImGui::SetNextWindowPos(
				  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_width / 5.0f, m_height / 2.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			ImGui::Text("Vertices: %d", m_numVertices);
			ImGui::Text("Triangles: %d", m_numTriangles);

			ImGui::SliderFloat("LOD Level", &m_LOD, 0.0f, 1.0f);

			ImGui::End();

			imguiEndFrame();

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			float time = (float)( (bx::getHPCounter()-m_timeOffset)/double(bx::getHPFrequency() ) );
			const float BasicColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			bgfx::setUniform(u_tint, BasicColor);

			const bx::Vec3 at  = { 0.0f, 1.0f,  0.0f };
			const bx::Vec3 eye = { 0.0f, 1.0f, -2.5f };

			// Set view and projection matrix for view 0.
			{
				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			float mtx[16];
			bx::mtxRotateXY(mtx
				, 0.0f
				, time*0.37f
				);

			submitLOD(0, mtx);

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	float m_lastLOD;
	float m_LOD;
	uint32_t m_numVertices;
	uint32_t m_numTriangles;
	uint32_t m_totalVertices;
	uint32_t m_totalTriangles;

	int *m_map;
	int *m_triangle;

	int64_t m_timeOffset;
	bgfx::VertexBufferHandle m_vb;
	bgfx::DynamicIndexBufferHandle m_ib;
	bgfx::ProgramHandle m_program;
	bgfx::UniformHandle u_tint;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleBunnyLOD
	, "42-bunnylod"
	, "Progressive Mesh LOD"
	, "https://bkaradzic.github.io/bgfx/examples.html#bunnylod"
	);
