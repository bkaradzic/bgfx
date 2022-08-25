/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

// Multi Draw Indirect
// Render multiple different objects with one draw command. This example shows a minimal implementation of indirect drawing
// Reading References:
// https://litasa.github.io/blog/2017/09/04/OpenGL-MultiDrawIndirect-with-Individual-Textures
// https://cpp-rendering.io/indirect-rendering/

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

struct ObjectInstance {
	float m_vertexOffset;
	float m_vertexCount;
	float m_indexOffset;
	float m_indexCount;
	
	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float)
			.end();
	};
	
	static bgfx::VertexLayout ms_layout;
	};

bgfx::VertexLayout ObjectInstance::ms_layout;

static PosColorVertex s_multiMeshVertices[12] =
{
	// Cube Model
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
	
	// Tetrahedron Model (offset = 8)
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{ 1.0f, -1.0f, -1.0f, 0xff000000 },
	{-1.0f,  1.0f, -1.0f, 0xff00ff00 },
	{-1.0f, -1.0f,  1.0f, 0xff00ffff },
};

static const uint16_t s_multiMeshIndices[48] =
{
	// Cube Indicies
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
	
	// Tetrahedron Indices (offset = 36)
	0, 2, 1,
	1, 2, 3,
	0, 3, 2,
	1, 3, 0,
};


class MultiDrawIndirect : public entry::AppI
{
public:
	MultiDrawIndirect(const char* _name, const char* _description, const char* _url)
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
		m_sideSize         = 11;
		m_nDrawElements = 121;

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

		// Create vertex stream declaration.
		PosColorVertex::init();
		ObjectInstance::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
					  bgfx::makeRef(s_multiMeshVertices, sizeof(s_multiMeshVertices) )
					, PosColorVertex::ms_layout
					);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(
					bgfx::makeRef(s_multiMeshIndices, sizeof(s_multiMeshIndices) )
					);

		// Create program from shaders.
		m_program = loadProgram("vs_instancing", "fs_instancing"); // These are reused from 05-instancing
		
		m_indirect_program = BGFX_INVALID_HANDLE;
		m_indirect_buffer_handle = BGFX_INVALID_HANDLE;
		m_object_list_buffer = BGFX_INVALID_HANDLE;
		
		u_drawParams = bgfx::createUniform("u_drawParams", bgfx::UniformType::Vec4);
		
		const bool computeSupported = !!(BGFX_CAPS_DRAW_INDIRECT & bgfx::getCaps()->supported);
		const bool instancingSupported = !!(BGFX_CAPS_INSTANCING & bgfx::getCaps()->supported);
		
		if (computeSupported && instancingSupported) {
			// Set up indirect program
			// This is a barebones program that populates the indirect buffer handle with draw requests
			m_indirect_program = bgfx::createProgram(loadShader("cs_multidrawindirect"), true);
			m_indirect_buffer_handle = bgfx::createIndirectBuffer(m_nDrawElements);
			
			ObjectInstance objs[m_nDrawElements];
			
			for (uint32_t ii = 0; ii < m_nDrawElements; ++ii) {
				if (ii % 2) {
					// Tetrahedron
					objs[ii].m_vertexOffset = 8;
					objs[ii].m_vertexCount = 4; // m_vertexCount is unused in compute shader, its only here for completeness
					objs[ii].m_indexOffset = 36;
					objs[ii].m_indexCount = 12;
					}
				else {
					// Cube
					objs[ii].m_vertexOffset = 0;
					objs[ii].m_vertexCount = 8;
					objs[ii].m_indexOffset = 0;
					objs[ii].m_indexCount = 36;
					}
				}
			
			// This is a list of objects to be rendered via the indirect program
			m_object_list_buffer = bgfx::createVertexBuffer(bgfx::copy(objs, sizeof(objs) ), ObjectInstance::ms_layout, BGFX_BUFFER_COMPUTE_READ);
			}
			
		m_timeOffset = bx::getHPCounter();

		imguiCreate();
	}

	int shutdown() override
	{
		imguiDestroy();

		// Cleanup.
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);

		if (bgfx::isValid(m_indirect_program))
			bgfx::destroy(m_indirect_program);
		if (bgfx::isValid(m_indirect_buffer_handle))
			bgfx::destroy(m_indirect_buffer_handle);
		if (bgfx::isValid(m_object_list_buffer))
			bgfx::destroy(m_object_list_buffer);
		bgfx::destroy(u_drawParams);
		
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

			showExampleDialog(this);

			imguiEndFrame();
			
			// Get renderer capabilities info.
			const bool computeSupported = !!(BGFX_CAPS_DRAW_INDIRECT & bgfx::getCaps()->supported);
			const bool instancingSupported = !!(BGFX_CAPS_INSTANCING & bgfx::getCaps()->supported);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			float time = (float)( (bx::getHPCounter() - m_timeOffset)/double(bx::getHPFrequency() ) );

			if (!computeSupported)
			{
				// When instancing is not supported by GPU, implement alternative
				// code path that doesn't use instancing.
				bool blink = uint32_t(time*3.0f)&1;
				bgfx::dbgTextPrintf(0, 0, blink ? 0x4f : 0x04, " Compute is not supported by GPU. ");
			}
			if (!instancingSupported)
			{
				bool blink = uint32_t(time*3.0f)&1;
				bgfx::dbgTextPrintf(0, 1, blink ? 0x4f : 0x04, " Instancing is not supported by GPU. ");
			}

			const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -35.0f };

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

			if (computeSupported && instancingSupported) {
				// Prepare instance buffer
				const uint16_t instanceStride = 80;
				bgfx::InstanceDataBuffer idb;
				bgfx::allocInstanceDataBuffer(&idb, m_nDrawElements, instanceStride);

				uint8_t* data = idb.data;

				for (uint32_t ii = 0; ii < m_nDrawElements; ++ii)
				{
					uint32_t yy = ii / m_sideSize;
					uint32_t xx = ii % m_sideSize;

					float* mtx = (float*)data;
					bx::mtxRotateXY(mtx, time + xx * 0.21f, time + yy * 0.37f);
					mtx[12] = -15.0f + float(xx) * 3.0f;
					mtx[13] = -15.0f + float(yy) * 3.0f;
					mtx[14] = 0.0f;

					float* color = (float*)&data[64];
					color[0] = bx::sin(time + float(xx) / 11.0f) * 0.5f + 0.5f;
					color[1] = bx::cos(time + float(yy) / 11.0f) * 0.5f + 0.5f;
					color[2] = bx::sin(time * 3.0f) * 0.5f + 0.5f;
					color[3] = 1.0f;

					data += instanceStride;
				}
				
				// Build indirect buffer
				// NOTE: This could be done once on startup and results stored
				// This is done here for demonstration purposes
				// You could modify this to, eg, do frustrum culling on the GPU				
				bgfx::setBuffer(0, m_indirect_buffer_handle, bgfx::Access::Write);
				bgfx::setBuffer(1, m_object_list_buffer, bgfx::Access::Read);
				
				float ud[4] = { float(m_nDrawElements), 0, 0, 0 };
				bgfx::setUniform(u_drawParams, ud);
					
				bgfx::dispatch(0, m_indirect_program);
				
				// Set vertex and index buffer.
				bgfx::setIndexBuffer(m_ibh);
				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setInstanceDataBuffer(&idb);
				
				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 0.
				// note that this submission requires the draw count
				bgfx::submit(0, m_program, m_indirect_buffer_handle, 0, m_nDrawElements);
			}
			
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
	uint32_t m_sideSize;
	uint32_t m_nDrawElements;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
	bgfx::ProgramHandle m_program;
	bgfx::IndirectBufferHandle  m_indirect_buffer_handle;
	bgfx::ProgramHandle m_indirect_program;
	bgfx::VertexBufferHandle m_object_list_buffer;
	bgfx::UniformHandle u_drawParams;

	int64_t m_timeOffset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  MultiDrawIndirect
	, "48-multidrawindirect"
	, "Simple example of indirect rendering to render multiple different meshes with 1 draw call"
	, "https://bkaradzic.github.io/bgfx/examples.html#multidrawindirect"
	);
