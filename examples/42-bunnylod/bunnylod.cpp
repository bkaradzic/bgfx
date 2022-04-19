/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bx/easing.h>
#include <bx/file.h>
#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

extern "C" void ProgressiveMesh(int vert_n, int vert_stride, const float *v, int tri_n, const int *tri, int *map, int *permutation);

namespace
{

class ExampleBunnyLOD : public entry::AppI
{
public:
	ExampleBunnyLOD(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void PermuteMesh(const bgfx::Memory* _vb, const bgfx::Memory* _ib, const bgfx::VertexLayout& _layout)
	{
		const uint32_t stride       = _layout.getStride();
		const uint32_t offset       = _layout.getOffset(bgfx::Attrib::Position);
		const uint32_t numVertices  = _vb->size / stride;
		const uint32_t numTriangles = _ib->size / (3 * sizeof(uint32_t) );

		if (m_cachePermutation == NULL)
		{
			m_cachePermutation = (uint32_t*)BX_ALLOC(entry::getAllocator(), numVertices * sizeof(uint32_t) );
			m_map = (uint32_t*)BX_ALLOC(entry::getAllocator(), numVertices * sizeof(uint32_t) );

			// It will takes long time if there are too many vertices.
			ProgressiveMesh(
				  numVertices
				, stride
				, (const float*)(_vb->data + offset)
				, numTriangles
				, (const int*)_ib->data
				, (int*)m_map
				, (int*)m_cachePermutation
				);
		}

		// rearrange the vertex Array
		char* temp = (char*)BX_ALLOC(entry::getAllocator(), numVertices * stride);
		bx::memCopy(temp, _vb->data, _vb->size);

		for (uint32_t ii = 0; ii < numVertices; ++ii)
		{
			bx::memCopy(_vb->data + m_cachePermutation[ii] * stride , temp + ii * stride, stride);
		}

		BX_FREE(entry::getAllocator(), temp);

		// update the changes in the entries in the triangle Array
		for (uint32_t ii = 0, num = numTriangles*3; ii < num; ++ii)
		{
			uint32_t* indices = (uint32_t*)(_ib->data + ii * sizeof(uint32_t) );
			*indices = m_cachePermutation[*indices];
		}
	}

	static void remapIndices(uint32_t* _indices, uint32_t _num)
	{
		uint32_t target = 0;
		for (uint32_t i = 0; i < _num; i++) {
			uint32_t map = _indices[i];
			if (i != map) {
				_indices[i] = _indices[map];
			} else {
				_indices[i] = target;
				++target;
			}
		}
	}

	static const bgfx::Memory* mergeVertices(const uint8_t* _vb, uint16_t _stride, const uint32_t* _indices, uint32_t _num, uint32_t _numMerged)
	{
		const bgfx::Memory* mem = bgfx::alloc(_stride * _numMerged);

		for (uint32_t ii = 0; ii < _num; ++ii)
		{
			bx::memCopy(mem->data + _indices[ii]*_stride, _vb + ii*_stride, _stride);
		}

		return mem;
	}

	void loadMesh(Mesh* _mesh)
	{
		// merge sub mesh
		uint32_t numVertices = 0;
		uint32_t numIndices  = 0;

		for (GroupArray::const_iterator it = _mesh->m_groups.begin(), itEnd = _mesh->m_groups.end()
			; it != itEnd
			; ++it
			)
		{
			numVertices += it->m_numVertices;
			numIndices  += it->m_numIndices;
		}

		const bgfx::Memory* ib = bgfx::alloc(numIndices * sizeof(uint32_t) );
		uint8_t* vbData = (uint8_t*)BX_ALLOC(entry::getAllocator(), _mesh->m_layout.getSize(numVertices) );

		{
			uint32_t voffset = 0;
			uint32_t ioffset = 0;
			uint32_t index   = 0;

			for (GroupArray::const_iterator it = _mesh->m_groups.begin(), itEnd = _mesh->m_groups.end()
				; it != itEnd
				; ++it
				)
			{
				const uint32_t vsize = _mesh->m_layout.getSize(it->m_numVertices);
				bx::memCopy(vbData + voffset, it->m_vertices, vsize);

				uint32_t* ibptr = (uint32_t*)(ib->data + ioffset);

				for (uint32_t ii = 0, num = it->m_numIndices; ii < num; ++ii)
				{
					ibptr[ii] = it->m_indices[ii] + index;
				}

				voffset += vsize;
				ioffset += uint32_t(it->m_numIndices * sizeof(uint32_t) );
				index   += uint32_t(it->m_numVertices);
			}
		}

		bool cacheInvalid = false;
		loadCache();

		if (m_originalVertices != numVertices
		||  m_cacheWeld == NULL)
		{
			cacheInvalid       = true;
			m_originalVertices = numVertices;

			BX_FREE(entry::getAllocator(), m_cachePermutation);
			m_cachePermutation = NULL;

			BX_FREE(entry::getAllocator(), m_cacheWeld);
			m_cacheWeld = (uint32_t*)BX_ALLOC(entry::getAllocator(), numVertices * sizeof(uint32_t) );

			m_totalVertices	= bgfx::weldVertices(m_cacheWeld, _mesh->m_layout, vbData, numVertices, true, 0.00001f);
			remapIndices(m_cacheWeld, numVertices);
		}

		const bgfx::Memory* vb = mergeVertices(
			  vbData
			, _mesh->m_layout.getStride()
			, m_cacheWeld
			, numVertices
			, m_totalVertices
			);
		BX_FREE(entry::getAllocator(), vbData);

		{
			uint32_t* ibData = (uint32_t*)ib->data;
			for (uint32_t ii = 0; ii < numIndices; ++ii)
			{
				ibData[ii] = m_cacheWeld[ibData[ii] ];
			}
		}

		PermuteMesh(vb, ib, _mesh->m_layout);

		if (cacheInvalid)
		{
			saveCache();
		}

		m_triangle = (uint32_t*)BX_ALLOC(entry::getAllocator(), ib->size);
		bx::memCopy(m_triangle, ib->data, ib->size);

		m_vb = bgfx::createVertexBuffer(vb, _mesh->m_layout);
		m_ib = bgfx::createDynamicIndexBuffer(ib, BGFX_BUFFER_INDEX32);

		m_numVertices    = m_totalVertices;
		m_numTriangles   = numIndices/3;
		m_totalTriangles = m_numTriangles;
	}

	const bx::FilePath kCacheFilePath = bx::FilePath("temp/bunnylod.cache");

	void loadCache()
	{
		m_cacheWeld = NULL;
		m_cachePermutation = NULL;
		m_originalVertices = 0;

		bx::Error err;

		bx::FileReader reader;

		if (bx::open(&reader, kCacheFilePath) )
		{
			bx::read(&reader, m_originalVertices, &err);
			bx::read(&reader, m_totalVertices, &err);
			m_cacheWeld = (uint32_t*)BX_ALLOC(entry::getAllocator(), m_originalVertices * sizeof(uint32_t) );

			bx::read(&reader, m_cacheWeld, m_originalVertices * sizeof(uint32_t), &err);
			m_cachePermutation = (uint32_t*)BX_ALLOC(entry::getAllocator(), m_totalVertices * sizeof(uint32_t) );

			bx::read(&reader, m_cachePermutation, m_totalVertices * sizeof(uint32_t), &err);
			m_map = (uint32_t*)BX_ALLOC(entry::getAllocator(), m_totalVertices * sizeof(uint32_t) );

			bx::read(&reader, m_map, m_totalVertices * sizeof(uint32_t), &err);

			if (!err.isOk() )
			{
				// read fail
				BX_FREE(entry::getAllocator(), m_cacheWeld);
				m_cacheWeld = NULL;

				BX_FREE(entry::getAllocator(), m_cachePermutation);
				m_cachePermutation = NULL;

				BX_FREE(entry::getAllocator(), m_map);
				m_map = NULL;
			}

			bx::close(&reader);
		}
	}

	void saveCache()
	{
		bx::FileWriter writer;

		if (bx::open(&writer, kCacheFilePath) )
		{
			bx::Error err;

			bx::write(&writer, m_originalVertices, &err);
			bx::write(&writer, m_totalVertices, &err);
			bx::write(&writer, m_cacheWeld, m_originalVertices * sizeof(uint32_t), &err);
			bx::write(&writer, m_cachePermutation, m_totalVertices * sizeof(uint32_t), &err);
			bx::write(&writer, m_map, m_totalVertices * sizeof(uint32_t), &err);

			bx::close(&writer);
		}
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
		m_program = loadProgram("vs_bunnylod", "fs_bunnylod");

		Mesh* mesh = meshLoad("meshes/bunny_patched.bin", true);
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

		BX_FREE(entry::getAllocator(), m_map);
		BX_FREE(entry::getAllocator(), m_triangle);
		BX_FREE(entry::getAllocator(), m_cacheWeld);
		BX_FREE(entry::getAllocator(), m_cachePermutation);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	void updateIndexBuffer()
	{
		int verts = int(bx::easeInQuad(m_LOD) * m_totalVertices);
		if (verts <= 0)
		{
			return;
		}

		int tris = 0;
		const bgfx::Memory* ib = bgfx::alloc(m_totalTriangles * 3 * sizeof(uint32_t) );

		for (uint32_t ii = 0; ii < m_totalTriangles; ++ii)
		{
			int v[3];

			for (uint32_t jj = 0; jj < 3; ++jj)
			{
				int idx = m_triangle[ii*3+jj];
				while (idx >= verts)
				{
					idx = m_map[idx];
				}

				v[jj] = idx;
			}

			if (v[0] != v[1]
			&&  v[0] != v[2]
			&&  v[1] != v[2])
			{
				bx::memCopy(ib->data + tris * 3 * sizeof(uint32_t), v, 3 * sizeof(int) );
				++tris;
			}
		}

		m_numTriangles = tris;
		m_numVertices = verts;

		bgfx::update(m_ib, 0, ib);
	}

	void submitLod(bgfx::ViewId _viewid, const float* _mtx)
	{
		bgfx::setTransform(_mtx);
		bgfx::setState(0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_CULL_CCW
			| BGFX_STATE_MSAA
			);

		if (m_LOD != m_lastLOD)
		{
			updateIndexBuffer();
			m_lastLOD = m_LOD;
		}

		bgfx::setIndexBuffer(m_ib, 0, m_numTriangles*3);
		bgfx::setVertexBuffer(0, m_vb, 0, m_numVertices);
		bgfx::submit(_viewid, m_program);
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

			ImGui::SliderFloat("LOD Level", &m_LOD, 0.05f, 1.0f);

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

			submitLod(0, mtx);

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
	uint32_t m_originalVertices;

	uint32_t* m_map;
	uint32_t* m_triangle;
	uint32_t* m_cacheWeld;
	uint32_t* m_cachePermutation;

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
