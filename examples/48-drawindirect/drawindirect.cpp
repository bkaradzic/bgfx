/*
 * Copyright 2022-2022 Liam Twigger. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

// Draw Indirect
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

struct RenderInstance {
	float m_mtx[16];
	float m_color[4];

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord1, 4, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord2, 4, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord3, 4, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float)
			.end();
	};

	static bgfx::VertexLayout ms_layout;
	};

bgfx::VertexLayout RenderInstance::ms_layout;

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

static const uint32_t s_maxSideSize = 81;

class DrawIndirect : public entry::AppI
{
public:
	DrawIndirect(const char* _name, const char* _description, const char* _url)
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
		m_sideSize = 11;
		m_nDrawElements = s_maxSideSize*s_maxSideSize;
		m_useIndirectCount = false;

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
		RenderInstance::init();

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
		m_indirect_count_program = BGFX_INVALID_HANDLE;
		m_indirect_buffer_handle = BGFX_INVALID_HANDLE;
		m_indirect_count_buffer_handle = BGFX_INVALID_HANDLE;
		m_object_list_buffer = BGFX_INVALID_HANDLE;

		u_drawParams = bgfx::createUniform("u_drawParams", bgfx::UniformType::Vec4);

		const bool computeSupported = !!(BGFX_CAPS_COMPUTE & bgfx::getCaps()->supported);
		const bool indirectSupported = !!(BGFX_CAPS_DRAW_INDIRECT & bgfx::getCaps()->supported);
		const bool instancingSupported = !!(BGFX_CAPS_INSTANCING & bgfx::getCaps()->supported);

		if (computeSupported && indirectSupported && instancingSupported)
		{
			// Set up indirect program
			// This is a barebones program that populates the indirect buffer handle with draw requests
			m_indirect_program = bgfx::createProgram(loadShader("cs_drawindirect"), true);
			m_indirect_buffer_handle = bgfx::createIndirectBuffer(m_nDrawElements);

			const bool indirectCountSupported = !!(BGFX_CAPS_DRAW_INDIRECT_COUNT & bgfx::getCaps()->supported);
			if (indirectCountSupported)
			{
				m_useIndirectCount = true;
				m_indirect_count_program = bgfx::createProgram(loadShader("cs_drawindirect_count"), true);

				const bgfx::Memory * mem = bgfx::alloc(sizeof(uint32_t));
				*(uint32_t *)mem->data = 0;
				m_indirect_count_buffer_handle = bgfx::createIndexBuffer(mem, BGFX_BUFFER_INDEX32 | BGFX_BUFFER_COMPUTE_WRITE | BGFX_BUFFER_DRAW_INDIRECT);
			}

			const bgfx::Memory * mem = bgfx::alloc(sizeof(ObjectInstance) * m_nDrawElements);
			ObjectInstance* objs = (ObjectInstance*) mem->data;

			for (uint32_t ii = 0; ii < m_nDrawElements; ++ii)
			{
				if (ii % 2)
				{
					// Tetrahedron
					objs[ii].m_vertexOffset = 8;
					objs[ii].m_vertexCount = 4; // m_vertexCount is unused in compute shader, its only here for completeness
					objs[ii].m_indexOffset = 36;
					objs[ii].m_indexCount = 12;
				}
				else
				{
					// Cube
					objs[ii].m_vertexOffset = 0;
					objs[ii].m_vertexCount = 8;
					objs[ii].m_indexOffset = 0;
					objs[ii].m_indexCount = 36;
				}
			}

			// This is a list of objects to be rendered via the indirect program
			m_object_list_buffer = bgfx::createVertexBuffer(mem, ObjectInstance::ms_layout, BGFX_BUFFER_COMPUTE_READ);

			// This is the instance buffer used for rendering.
			// You could instead use a dynamic instance buffer when rendering (use bgfx::allocInstanceDataBuffer in draw loop)
			m_instance_buffer = bgfx::createDynamicVertexBuffer(m_nDrawElements, RenderInstance::ms_layout, BGFX_BUFFER_COMPUTE_WRITE);
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
		{
			bgfx::destroy(m_indirect_program);
		}
		if (bgfx::isValid(m_indirect_count_program))
		{
			bgfx::destroy(m_indirect_count_program);
		}
		if (bgfx::isValid(m_indirect_buffer_handle))
		{
			bgfx::destroy(m_indirect_buffer_handle);
		}
		if (bgfx::isValid(m_indirect_count_buffer_handle))
		{
			bgfx::destroy(m_indirect_count_buffer_handle);
		}
		if (bgfx::isValid(m_object_list_buffer))
		{
			bgfx::destroy(m_object_list_buffer);
		}
		if (bgfx::isValid(m_instance_buffer))
		{
			bgfx::destroy(m_instance_buffer);
		}
		bgfx::destroy(u_drawParams);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			// Get renderer capabilities info.
			const bool computeSupported = !!(BGFX_CAPS_COMPUTE & bgfx::getCaps()->supported);
			const bool indirectSupported = !!(BGFX_CAPS_DRAW_INDIRECT & bgfx::getCaps()->supported);
			const bool indirectCountSupported = !!(BGFX_CAPS_DRAW_INDIRECT_COUNT & bgfx::getCaps()->supported);
			const bool instancingSupported = !!(BGFX_CAPS_INSTANCING & bgfx::getCaps()->supported);

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

			ImGui::Text("%d draw calls", bgfx::getStats()->numDraw);
			ImGui::Text("%d objects drawn", m_sideSize*m_sideSize);

			ImGui::Text("Grid Side Size:");
			ImGui::SliderInt("##size", (int*)&m_sideSize, 1, s_maxSideSize);

			ImGui::BeginDisabled(!indirectCountSupported);
			ImGui::Checkbox("Indirect Count", &m_useIndirectCount);
			ImGui::EndDisabled();
			if (!indirectCountSupported && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled) )
			{
				ImGui::SetTooltip("Indirect Count is not supported by GPU.");
			}

			ImGui::End();

			imguiEndFrame();


			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -35.0f };

			// Set view and projection matrix for view 0.
			{
				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 500.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			float time = (float)( (bx::getHPCounter() - m_timeOffset)/double(bx::getHPFrequency() ) );

			if (computeSupported && indirectSupported && instancingSupported)
			{
				// Build indirect buffer & prepare instance buffer
				// NOTE: IF you are rendering static data then
				// this could be done once on startup and results stored
				// This is done here for demonstration purposes

				// The model matrix for each instance is also set on compute
				// you could modify this to, eg, do frustrum culling on the GPU
				float ud[4] = { float(m_nDrawElements), float(m_sideSize), float(time), 0 };
				uint32_t numToDraw = (m_sideSize*m_sideSize);

				bgfx::setUniform(u_drawParams, ud);

				bgfx::setBuffer(0, m_object_list_buffer, bgfx::Access::Read);
				bgfx::setBuffer(1, m_indirect_buffer_handle, bgfx::Access::Write);
				bgfx::setBuffer(2, m_instance_buffer, bgfx::Access::Write);

				// Dispatch the call. We are using 64 local threads on the GPU to process the object list
				// So lets dispatch ceil(numToDraw/64) workgroups of 64 local threads
				if (m_useIndirectCount)
				{
					bgfx::setBuffer(3, m_indirect_count_buffer_handle, bgfx::Access::Write);
					bgfx::dispatch(0, m_indirect_count_program, uint32_t(numToDraw/64 + 1), 1, 1);
				}
				else
				{
					bgfx::dispatch(0, m_indirect_program, uint32_t(numToDraw/64 + 1), 1, 1);
				}

				// Submit our 1 draw call
				// Set vertex and index buffer.
				bgfx::setIndexBuffer(m_ibh);
				bgfx::setVertexBuffer(0, m_vbh);
				bgfx::setInstanceDataBuffer(m_instance_buffer, 0, numToDraw);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 0.
				if (m_useIndirectCount)
				{
					// With indirect count, the number of draws is read from a buffer
					bgfx::submit(0, m_program, m_indirect_buffer_handle, 0, m_indirect_count_buffer_handle);
				}
				else
				{
					bgfx::submit(0, m_program, m_indirect_buffer_handle, 0, numToDraw);
				}
			}
			else
			{
				// Compute/Indirect/Instancing is not supported
				bool blink = uint32_t(time*3.0f)&1;
				bgfx::dbgTextPrintf(0, 0, blink ? 0x4f : 0x04, " Compute/Indirect/Instancing is not supported by GPU. ");
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
	bool m_useIndirectCount;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
	bgfx::ProgramHandle m_program;
	bgfx::IndirectBufferHandle m_indirect_buffer_handle;
	bgfx::IndexBufferHandle m_indirect_count_buffer_handle;
	bgfx::ProgramHandle m_indirect_program;
	bgfx::ProgramHandle m_indirect_count_program;
	bgfx::VertexBufferHandle m_object_list_buffer;
	bgfx::DynamicVertexBufferHandle m_instance_buffer;
	bgfx::UniformHandle u_drawParams;

	int64_t m_timeOffset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  DrawIndirect
	, "48-drawindirect"
	, "Simple example of indirect rendering to render multiple different meshes with 1 draw call"
	, "https://bkaradzic.github.io/bgfx/examples.html#drawindirect"
	);
