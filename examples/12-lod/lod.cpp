/*
 * Copyright 2013 Milos Tosic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <string>
#include <vector>

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

#include <bx/readerwriter.h>

struct KnightPos
{
	int32_t m_x;
	int32_t m_y;
};

KnightPos knightTour[8*4] =
{
	{0,0}, {1,2}, {3,3}, {4,1}, {5,3}, {7,2}, {6,0}, {5,2},
	{7,3}, {6,1}, {4,0}, {3,2}, {2,0}, {0,1}, {1,3}, {2,1},
	{0,2}, {1,0}, {2,2}, {0,3}, {1,1}, {3,0}, {4,2}, {5,0},
	{7,1}, {6,3}, {5,1}, {7,0}, {6,2}, {4,3}, {3,1}, {2,3}
};

struct Aabb
{
	float m_min[3];
	float m_max[3];
};

struct Obb
{
	float m_mtx[16];
};

struct Sphere
{
	float m_center[3];
	float m_radius;
};

struct Primitive
{
	uint32_t m_startIndex;
	uint32_t m_numIndices;
	uint32_t m_startVertex;
	uint32_t m_numVertices;

	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
};

typedef std::vector<Primitive> PrimitiveArray;

struct Group
{
	Group()
	{
		reset();
	}

	void reset()
	{
		m_vbh.idx = bgfx::invalidHandle;
		m_ibh.idx = bgfx::invalidHandle;
		m_prims.clear();
	}

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
	PrimitiveArray m_prims;
};

struct Mesh
{
	void load(const char* _filePath)
	{
#define BGFX_CHUNK_MAGIC_VB BX_MAKEFOURCC('V', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_IB BX_MAKEFOURCC('I', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_PRI BX_MAKEFOURCC('P', 'R', 'I', 0x0)

		bx::CrtFileReader reader;
		reader.open(_filePath);

		Group group;

		uint32_t chunk;
		while (4 == bx::read(&reader, chunk) )
		{
			switch (chunk)
			{
			case BGFX_CHUNK_MAGIC_VB:
				{
					bx::read(&reader, group.m_sphere);
					bx::read(&reader, group.m_aabb);
					bx::read(&reader, group.m_obb);

					bx::read(&reader, m_decl);
					uint16_t stride = m_decl.getStride();

					uint16_t numVertices;
					bx::read(&reader, numVertices);
					const bgfx::Memory* mem = bgfx::alloc(numVertices*stride);
					bx::read(&reader, mem->data, mem->size);

					group.m_vbh = bgfx::createVertexBuffer(mem, m_decl);
				}
				break;

			case BGFX_CHUNK_MAGIC_IB:
				{
					uint32_t numIndices;
					bx::read(&reader, numIndices);
					const bgfx::Memory* mem = bgfx::alloc(numIndices*2);
					bx::read(&reader, mem->data, mem->size);
					group.m_ibh = bgfx::createIndexBuffer(mem);
				}
				break;

			case BGFX_CHUNK_MAGIC_PRI:
				{
					uint16_t len;
					bx::read(&reader, len);

					std::string material;
					material.resize(len);
					bx::read(&reader, const_cast<char*>(material.c_str() ), len);

					uint16_t num;
					bx::read(&reader, num);

					for (uint32_t ii = 0; ii < num; ++ii)
					{
						bx::read(&reader, len);

						std::string name;
						name.resize(len);
						bx::read(&reader, const_cast<char*>(name.c_str() ), len);

						Primitive prim;
						bx::read(&reader, prim.m_startIndex);
						bx::read(&reader, prim.m_numIndices);
						bx::read(&reader, prim.m_startVertex);
						bx::read(&reader, prim.m_numVertices);
						bx::read(&reader, prim.m_sphere);
						bx::read(&reader, prim.m_aabb);
						bx::read(&reader, prim.m_obb);

						group.m_prims.push_back(prim);
					}

					m_groups.push_back(group);
					group.reset();
				}
				break;

			default:
				DBG("%08x at %d", chunk, reader.seek() );
				break;
			}
		}

		reader.close();
	}

	void unload()
	{
		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;
			bgfx::destroyVertexBuffer(group.m_vbh);

			if (bgfx::isValid(group.m_ibh) )
			{
				bgfx::destroyIndexBuffer(group.m_ibh);
			}
		}
		m_groups.clear();
	}

	void submit(bgfx::ProgramHandle _program, float* _mtx, bool _blend)
	{
		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;

			// Set model matrix for rendering.
			bgfx::setTransform(_mtx);
			bgfx::setProgram(_program);
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(group.m_vbh);

			// Set render states.
			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_ALPHA_WRITE
				| (_blend?0:BGFX_STATE_DEPTH_WRITE)
				| BGFX_STATE_DEPTH_TEST_LESS
				| BGFX_STATE_CULL_CCW
				| BGFX_STATE_MSAA
				| (_blend?BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA):0)
				);

			// Submit primitive for rendering to view 0.
			bgfx::submit(0);
		}
	}

	bgfx::VertexDecl m_decl;
	typedef std::vector<Group> GroupArray;
	GroupArray m_groups;
};

int _main_(int /*_argc*/, char** /*_argv*/)
{
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT
		, 0x303030ff
		, 1.0f
		, 0
		);
	
	bgfx::UniformHandle u_texColor = bgfx::createUniform("u_texColor", bgfx::UniformType::Uniform1iv);
	bgfx::UniformHandle u_stipple = bgfx::createUniform("u_stipple", bgfx::UniformType::Uniform3fv);
	bgfx::UniformHandle u_texStipple = bgfx::createUniform("u_texStipple", bgfx::UniformType::Uniform1iv);

	bgfx::ProgramHandle program = loadProgram("vs_tree", "fs_tree");

	bgfx::TextureHandle textureLeafs = loadTexture("leafs1.dds"); 
	bgfx::TextureHandle textureBark  = loadTexture("bark1.dds"); 

	bgfx::TextureHandle textureStipple;

	const bgfx::Memory* stipple = bgfx::alloc(8*4);
	memset(stipple->data, 0, stipple->size);

	for (uint32_t ii = 0; ii < 32; ++ii)
	{
		stipple->data[knightTour[ii].m_y * 8 + knightTour[ii].m_x] = ii*4;
	}
		
	textureStipple = bgfx::createTexture2D(8, 4, 1, bgfx::TextureFormat::R8, BGFX_TEXTURE_MAG_POINT|BGFX_TEXTURE_MIN_POINT, stipple);

	Mesh mesh_top[3];
	mesh_top[0].load("meshes/tree1b_lod0_1.bin");
	mesh_top[1].load("meshes/tree1b_lod1_1.bin");
	mesh_top[2].load("meshes/tree1b_lod2_1.bin");
	
	Mesh mesh_trunk[3];
	mesh_trunk[0].load("meshes/tree1b_lod0_2.bin");
	mesh_trunk[1].load("meshes/tree1b_lod1_2.bin");
	mesh_trunk[2].load("meshes/tree1b_lod2_2.bin");

	// Imgui.
	void* data = load("font/droidsans.ttf");
	imguiCreate(data);
	free(data);

	int32_t scrollArea = 0;

	bool transitions = true;
	int transitionFrame = 0;
	int currLOD = 0;
	int targetLOD = 0;

	float at[3] = { 0.0f, 1.0f, 0.0f };
	float eye[3] = { 0.0f, 1.0f, -2.0f };

	entry::MouseState mouseState;
	while (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT : 0)
			, 0
			, width
			, height
			);

		imguiBeginScrollArea("Toggle transitions", width - width / 5 - 10, 10, width / 5, height / 6, &scrollArea);
		imguiSeparatorLine();

		if (imguiButton(transitions ? "ON" : "OFF") )
		{
			transitions = !transitions;
		}

		static float distance = 2.0f;
		imguiSlider("Distance", &distance, 2.0f, 6.0f, .01f);

		imguiEndScrollArea();
		imguiEndFrame();

		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::submit(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/12-lod");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Mesh LOD transitions.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);
		bgfx::dbgTextPrintf(0, 4, transitions ? 0x2f : 0x1f, transitions ? "Transitions on" : "Transitions off");

		eye[2] = -distance;
				
		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);
		mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		float mtx[16];
		mtxIdentity(mtx); 

		float stipple[3];
		float stippleInv[3];

		const int currentLODframe = transitions ? 32-transitionFrame : 32;
		const int mainLOD = transitions ? currLOD : targetLOD;
		
		stipple[0] = 0.0f;
		stipple[1] = -1.0f;
		stipple[2] = (float(currentLODframe)*4.0f/255.0f) - (1.0f/255.0f);
	
		stippleInv[0] = (float(31)*4.0f/255.0f);
		stippleInv[1] = 1.0f;
		stippleInv[2] = (float(transitionFrame)*4.0f/255.0f) - (1.0f/255.0f);

		bgfx::setTexture(0, u_texColor, textureBark);
		bgfx::setTexture(1, u_texStipple, textureStipple);
		bgfx::setUniform(u_stipple, stipple);
		mesh_trunk[mainLOD].submit(program, mtx, false);

		bgfx::setTexture(0, u_texColor, textureLeafs);
		bgfx::setTexture(1, u_texStipple, textureStipple);
		bgfx::setUniform(u_stipple, stipple);
		mesh_top[mainLOD].submit(program, mtx, true);

		if (transitions 
		&& (transitionFrame != 0) )
		{
			bgfx::setTexture(0, u_texColor, textureBark);
			bgfx::setTexture(1, u_texStipple, textureStipple);
			bgfx::setUniform(u_stipple, stippleInv);
			mesh_trunk[targetLOD].submit(program, mtx, false);

			bgfx::setTexture(0, u_texColor, textureLeafs);
			bgfx::setTexture(1, u_texStipple, textureStipple);
			bgfx::setUniform(u_stipple, stippleInv);
			mesh_top[targetLOD].submit(program, mtx, true);
		}
	
		int lod = 0;
		if (eye[2] < -2.5f)
		{
			lod = 1;
		}

		if (eye[2] < -5.0f)
		{
			lod = 2;
		}

		if (targetLOD!=lod)
		{
			if (targetLOD==currLOD)
			{
				targetLOD = lod;
			}
		}
		
		if (currLOD != targetLOD)
		{
			transitionFrame++;
		}

		if (transitionFrame>32)
		{
			currLOD = targetLOD;
			transitionFrame = 0;
		}

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	imguiDestroy();

	for (uint32_t ii = 0; ii < 3; ++ii)
	{
		mesh_top[ii].unload();
		mesh_trunk[ii].unload();
	}

	// Cleanup.
	bgfx::destroyProgram(program);

	bgfx::destroyUniform(u_texColor);
	bgfx::destroyUniform(u_stipple);
	bgfx::destroyUniform(u_texStipple);

	bgfx::destroyTexture(textureStipple);
	bgfx::destroyTexture(textureLeafs);
	bgfx::destroyTexture(textureBark); 
	
	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
