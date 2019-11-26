/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include <bx/rng.h>
#include <map>

namespace
{

#define RENDER_PASS_SHADING 0  // Default forward rendered geo with simple shading
#define RENDER_PASS_ID      1  // ID buffer for picking
#define RENDER_PASS_BLIT    2  // Blit GPU render target to CPU texture

#define ID_DIM 8  // Size of the ID buffer

class ExamplePicking : public entry::AppI
{
public:
	ExamplePicking(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
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
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set up screen clears
		bgfx::setViewClear(RENDER_PASS_SHADING
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
			);

		// ID buffer clears to black, which represnts clicking on nothing (background)
		bgfx::setViewClear(RENDER_PASS_ID
			, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			, 0x000000ff
			, 1.0f
			, 0
			);

		// Create uniforms
		u_tint = bgfx::createUniform("u_tint", bgfx::UniformType::Vec4); // Tint for when you click on items
		u_id   = bgfx::createUniform("u_id",   bgfx::UniformType::Vec4); // ID for drawing into ID buffer

		// Create program from shaders.
		m_shadingProgram = loadProgram("vs_picking_shaded", "fs_picking_shaded"); // Blinn shading
		m_idProgram      = loadProgram("vs_picking_shaded", "fs_picking_id");     // Shader for drawing into ID buffer

		static const char* meshPaths[] =
		{
			"meshes/orb.bin",
			"meshes/column.bin",
			"meshes/bunny.bin",
			"meshes/cube.bin",
			"meshes/tree.bin",
			"meshes/hollowcube.bin",
		};

		static const float meshScale[] =
		{
			0.5f,
			0.05f,
			0.5f,
			0.25f,
			0.05f,
			0.05f,
		};

		m_highlighted = UINT32_MAX;
		m_reading = 0;
		m_currFrame = UINT32_MAX;
		m_fov = 3.0f;
		m_cameraSpin = false;

		bx::RngMwc mwc;  // Random number generator
		for (uint32_t ii = 0; ii < 12; ++ii)
		{
			m_meshes[ii]    = meshLoad(meshPaths[ii % BX_COUNTOF(meshPaths)]);
			m_meshScale[ii] = meshScale[ii % BX_COUNTOF(meshPaths)];
			// For the sake of this example, we'll give each mesh a random color,  so the debug output looks colorful.
			// In an actual app, you'd probably just want to count starting from 1
			uint32_t rr = mwc.gen() % 256;
			uint32_t gg = mwc.gen() % 256;
			uint32_t bb = mwc.gen() % 256;
			m_idsF[ii][0] = rr / 255.0f;
			m_idsF[ii][1] = gg / 255.0f;
			m_idsF[ii][2] = bb / 255.0f;
			m_idsF[ii][3] = 1.0f;
			m_idsU[ii] = rr + (gg << 8) + (bb << 16) + (255u << 24);
		}

		m_timeOffset = bx::getHPCounter();

		// Set up ID buffer, which has a color target and depth buffer
		m_pickingRT = bgfx::createTexture2D(ID_DIM, ID_DIM, false, 1, bgfx::TextureFormat::RGBA8, 0
			| BGFX_TEXTURE_RT
			| BGFX_SAMPLER_MIN_POINT
			| BGFX_SAMPLER_MAG_POINT
			| BGFX_SAMPLER_MIP_POINT
			| BGFX_SAMPLER_U_CLAMP
			| BGFX_SAMPLER_V_CLAMP
			);
		m_pickingRTDepth = bgfx::createTexture2D(ID_DIM, ID_DIM, false, 1, bgfx::TextureFormat::D24S8, 0
			| BGFX_TEXTURE_RT
			| BGFX_SAMPLER_MIN_POINT
			| BGFX_SAMPLER_MAG_POINT
			| BGFX_SAMPLER_MIP_POINT
			| BGFX_SAMPLER_U_CLAMP
			| BGFX_SAMPLER_V_CLAMP
			);

		// CPU texture for blitting to and reading ID buffer so we can see what was clicked on.
		// Impossible to read directly from a render target, you *must* blit to a CPU texture
		// first. Algorithm Overview: Render on GPU -> Blit to CPU texture -> Read from CPU
		// texture.
		m_blitTex = bgfx::createTexture2D(ID_DIM, ID_DIM, false, 1, bgfx::TextureFormat::RGBA8, 0
			| BGFX_TEXTURE_BLIT_DST
			| BGFX_TEXTURE_READ_BACK
			| BGFX_SAMPLER_MIN_POINT
			| BGFX_SAMPLER_MAG_POINT
			| BGFX_SAMPLER_MIP_POINT
			| BGFX_SAMPLER_U_CLAMP
			| BGFX_SAMPLER_V_CLAMP
			);

		bgfx::TextureHandle rt[2] =
		{
			m_pickingRT,
			m_pickingRTDepth
		};
		m_pickingFB = bgfx::createFrameBuffer(BX_COUNTOF(rt), rt, true);

		imguiCreate();
	}

	int shutdown() override
	{
		for (uint32_t ii = 0; ii < 12; ++ii)
		{
			meshUnload(m_meshes[ii]);
		}

		// Cleanup.
		bgfx::destroy(m_shadingProgram);
		bgfx::destroy(m_idProgram);

		bgfx::destroy(u_tint);
		bgfx::destroy(u_id);

		bgfx::destroy(m_pickingFB);
		bgfx::destroy(m_pickingRT);
		bgfx::destroy(m_pickingRTDepth);
		bgfx::destroy(m_blitTex);

		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			// Draw UI
			imguiBeginFrame(
				   m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			const bgfx::Caps* caps = bgfx::getCaps();
			bool blitSupport = 0 != (caps->supported & BGFX_CAPS_TEXTURE_BLIT);

			showExampleDialog(this
				, !blitSupport
				? "BGFX_CAPS_TEXTURE_BLIT is not supported."
				: NULL
				);

			if (blitSupport)
			{
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

				ImGui::Image(m_pickingRT, ImVec2(m_width / 5.0f - 16.0f, m_width / 5.0f - 16.0f) );
				ImGui::SliderFloat("Field of view", &m_fov, 1.0f, 60.0f);
				ImGui::Checkbox("Spin Camera", &m_cameraSpin);

				ImGui::End();

				bgfx::setViewFrameBuffer(RENDER_PASS_ID, m_pickingFB);

				float time = (float)( (bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency() ) );

				// Set up matrices for basic forward renderer
				const float camSpeed = 0.25;
				float cameraSpin = (float)m_cameraSpin;
				float eyeDist = 2.5f;

				const bx::Vec3 at = { 0.0f, 0.0f, 0.0f };
				const bx::Vec3 eye =
				{
					-eyeDist * bx::sin(time*cameraSpin*camSpeed),
					0.0f,
					-eyeDist * bx::cos(time*cameraSpin*camSpeed),
				};

				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f, caps->homogeneousDepth);

				// Set up view rect and transform for the shaded pass
				bgfx::setViewRect(RENDER_PASS_SHADING, 0, 0, uint16_t(m_width), uint16_t(m_height) );
				bgfx::setViewTransform(RENDER_PASS_SHADING, view, proj);

				// Set up picking pass
				float viewProj[16];
				bx::mtxMul(viewProj, view, proj);

				float invViewProj[16];
				bx::mtxInverse(invViewProj, viewProj);

				// Mouse coord in NDC
				float mouseXNDC = ( m_mouseState.m_mx             / (float)m_width ) * 2.0f - 1.0f;
				float mouseYNDC = ((m_height - m_mouseState.m_my) / (float)m_height) * 2.0f - 1.0f;

				const bx::Vec3 pickEye = bx::mulH({ mouseXNDC, mouseYNDC, 0.0f }, invViewProj);
				const bx::Vec3 pickAt  = bx::mulH({ mouseXNDC, mouseYNDC, 1.0f }, invViewProj);

				// Look at our unprojected point
				float pickView[16];
				bx::mtxLookAt(pickView, pickEye, pickAt);

				// Tight FOV is best for picking
				float pickProj[16];
				bx::mtxProj(pickProj, m_fov, 1, 0.1f, 100.0f, caps->homogeneousDepth);

				// View rect and transforms for picking pass
				bgfx::setViewRect(RENDER_PASS_ID, 0, 0, ID_DIM, ID_DIM);
				bgfx::setViewTransform(RENDER_PASS_ID, pickView, pickProj);

				// Now that our passes are set up, we can finally draw each mesh

				// Picking highlights a mesh so we'll set up this tint color
				const float tintBasic[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
				const float tintHighlighted[4] = { 0.3f, 0.3f, 2.0f, 1.0f };

				for (uint32_t mesh = 0; mesh < 12; ++mesh)
				{
					const float scale = m_meshScale[mesh];

					// Set up transform matrix for each mesh
					float mtx[16];
					bx::mtxSRT(mtx
						, scale, scale, scale
						, 0.0f
						, time*0.37f*(mesh % 2 ? 1.0f : -1.0f)
						, 0.0f
						, (mesh % 4) - 1.5f
						, (mesh / 4) - 1.25f
						, 0.0f
						);

					// Submit mesh to both of our render passes
					// Set uniform based on if this is the highlighted mesh
					bgfx::setUniform(u_tint
						, mesh == m_highlighted
						? tintHighlighted
						: tintBasic
						);
					meshSubmit(m_meshes[mesh], RENDER_PASS_SHADING, m_shadingProgram, mtx);

					// Submit ID pass based on mesh ID
					bgfx::setUniform(u_id, m_idsF[mesh]);
					meshSubmit(m_meshes[mesh], RENDER_PASS_ID, m_idProgram, mtx);
				}

				// If the user previously clicked, and we're done reading data from GPU, look at ID buffer on CPU
				// Whatever mesh has the most pixels in the ID buffer is the one the user clicked on.
				if (m_reading == m_currFrame)
				{
					m_reading = 0;
					std::map<uint32_t, uint32_t> ids;  // This contains all the IDs found in the buffer
					uint32_t maxAmount = 0;
					for (uint8_t *x = m_blitData; x < m_blitData + ID_DIM * ID_DIM * 4;)
					{
						uint8_t rr = *x++;
						uint8_t gg = *x++;
						uint8_t bb = *x++;
						uint8_t aa = *x++;

						if (bgfx::RendererType::Direct3D9 == caps->rendererType)
						{
							// Comes back as BGRA
							uint8_t temp = rr;
							rr = bb;
							bb = temp;
						}

						if (0 == (rr|gg|bb) ) // Skip background
						{
							continue;
						}

						uint32_t hashKey = rr + (gg << 8) + (bb << 16) + (aa << 24);
						std::map<uint32_t, uint32_t>::iterator mapIter = ids.find(hashKey);
						uint32_t amount = 1;
						if (mapIter != ids.end() )
						{
							amount = mapIter->second + 1;
						}

						ids[hashKey] = amount; // Amount of times this ID (color) has been clicked on in buffer
						maxAmount = maxAmount > amount
							? maxAmount
							: amount
							;
					}

					uint32_t idKey = 0;
					m_highlighted = UINT32_MAX;
					if (maxAmount)
					{
						for (std::map<uint32_t, uint32_t>::iterator mapIter = ids.begin(); mapIter != ids.end(); mapIter++)
						{
							if (mapIter->second == maxAmount)
							{
								idKey = mapIter->first;
								break;
							}
						}

						for (uint32_t ii = 0; ii < 12; ++ii)
						{
							if (m_idsU[ii] == idKey)
							{
								m_highlighted = ii;
								break;
							}
						}
					}
				}

				// Start a new readback?
				if (!m_reading
				&&  m_mouseState.m_buttons[entry::MouseButton::Left])
				{
					// Blit and read
					bgfx::blit(RENDER_PASS_BLIT, m_blitTex, 0, 0, m_pickingRT);
					m_reading = bgfx::readTexture(m_blitTex, m_blitData);
				}
			}

			imguiEndFrame();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			m_currFrame = bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	int64_t m_timeOffset;

	Mesh* m_meshes[12];
	float m_meshScale[12];
	float m_idsF[12][4];
	uint32_t m_idsU[12];
	uint32_t m_highlighted;

	// Resource handles
	bgfx::ProgramHandle m_shadingProgram;
	bgfx::ProgramHandle m_idProgram;
	bgfx::UniformHandle u_tint;
	bgfx::UniformHandle u_id;
	bgfx::TextureHandle m_pickingRT;
	bgfx::TextureHandle m_pickingRTDepth;
	bgfx::TextureHandle m_blitTex;
	bgfx::FrameBufferHandle m_pickingFB;

	uint8_t m_blitData[ID_DIM*ID_DIM * 4]; // Read blit into this

	uint32_t m_reading;
	uint32_t m_currFrame;

	float m_fov;
	bool  m_cameraSpin;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExamplePicking
	, "30-picking"
	, "Mouse picking via GPU texture readback."
	, "https://bkaradzic.github.io/bgfx/examples.html#picking"
	);
