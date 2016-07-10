/*
 * Copyright 2016 Joseph Cherlin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include <bx/rng.h>
#include <map>

#define RENDER_PASS_SHADING 0  // Default forward rendered geo with simple shading
#define RENDER_PASS_ID      1  // ID buffer for picking
#define RENDER_PASS_BLIT    2  // Blit GPU render target to CPU texture

#define ID_DIM 8  // Size of the ID buffer

class ExamplePicking : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width = 1280;
		m_height = 720;
		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);

		bgfx::reset(m_width, m_height, m_reset);

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
		u_tint = bgfx::createUniform("u_tint", bgfx::UniformType::Vec4);  // Tint for when you click on items
		u_id = bgfx::createUniform("u_id", bgfx::UniformType::Vec4);      // ID for drawing into ID buffer

		// Create program from shaders.
		m_shadingProgram = loadProgram("vs_picking_shaded", "fs_picking_shaded");  // Blinn shading
		m_idProgram = loadProgram("vs_picking_shaded", "fs_picking_id");           // Shader for drawing into ID buffer

		const char * meshPaths[] = { "meshes/orb.bin", "meshes/column.bin", "meshes/bunny.bin", "meshes/cube.bin", "meshes/tree.bin", "meshes/hollowcube.bin" };
		const float meshScale[] = { 0.5f, 0.05f, 0.5f, 0.25f, 0.05f, 0.05f };

		m_highlighted = UINT32_MAX;
		m_reading = 0;
		m_currFrame = UINT32_MAX;
		m_fov = 3.0f;
		m_cameraSpin = false;

		bx::RngMwc mwc;  // Random number generator
		for (int32_t i = 0; i < 12; i++)
		{
			m_meshes[i] = meshLoad(meshPaths[i % 6]);
			m_meshScale[i] = meshScale[i % 6];
			// For the sake of this example, we'll give each mesh a random color,  so the debug output looks colorful.
			// In an actual app, you'd probably just want to count starting from 1
			uint32_t r = mwc.gen() % 256;
			uint32_t g = mwc.gen() % 256;
			uint32_t b = mwc.gen() % 256;
			m_idsF[i][0] = r / 255.0f;
			m_idsF[i][1] = g / 255.0f;
			m_idsF[i][2] = b / 255.0f;
			m_idsF[i][3] = 1.0f;
			m_idsU[i] = (r)+(g << 8) + (b << 16) + (255u << 24);
		}

		m_timeOffset = bx::getHPCounter();

		// Set up ID buffer, which has a color target and depth buffer
		m_pickingRT = bgfx::createTexture2D(ID_DIM, ID_DIM, 1, bgfx::TextureFormat::RGBA8, 0 // Probably would be better to use unsigned format
			| BGFX_TEXTURE_RT                                                                // but currently doesn't display in imgui
			| BGFX_TEXTURE_MIN_POINT
			| BGFX_TEXTURE_MAG_POINT
			| BGFX_TEXTURE_MIP_POINT
			| BGFX_TEXTURE_U_CLAMP
			| BGFX_TEXTURE_V_CLAMP
			);
		m_pickingRTDepth = bgfx::createTexture2D(ID_DIM, ID_DIM, 1, bgfx::TextureFormat::D24S8, 0
			| BGFX_TEXTURE_RT
			| BGFX_TEXTURE_MIN_POINT
			| BGFX_TEXTURE_MAG_POINT
			| BGFX_TEXTURE_MIP_POINT
			| BGFX_TEXTURE_U_CLAMP
			| BGFX_TEXTURE_V_CLAMP
			);

		// CPU texture for blitting to and reading ID buffer so we can see what was clicked on
		// Impossible to read directly from a render target, you *must* blit to a CPU texture first.
		// Algorithm Overview:
		// Render on GPU -> Blit to CPU texture -> Read from CPU texture
		m_blitTex = bgfx::createTexture2D(ID_DIM, ID_DIM, 1, bgfx::TextureFormat::RGBA8, 0
			| BGFX_TEXTURE_BLIT_DST  // <==
			| BGFX_TEXTURE_READ_BACK // <==
			| BGFX_TEXTURE_MIN_POINT
			| BGFX_TEXTURE_MAG_POINT
			| BGFX_TEXTURE_MIP_POINT
			| BGFX_TEXTURE_U_CLAMP
			| BGFX_TEXTURE_V_CLAMP
			);

		bgfx::TextureHandle rt[2] = { m_pickingRT, m_pickingRTDepth };
		m_pickingFB = bgfx::createFrameBuffer(BX_COUNTOF(rt), rt, true);

		imguiCreate();
	}

	int shutdown() BX_OVERRIDE
	{
		for (int32_t i = 0; i < 12; i++)
		{
			meshUnload(m_meshes[i]);
		}

		// Cleanup.
		bgfx::destroyProgram(m_shadingProgram);
		bgfx::destroyProgram(m_idProgram);

		bgfx::destroyUniform(u_tint);
		bgfx::destroyUniform(u_id);

		bgfx::destroyFrameBuffer(m_pickingFB);
		bgfx::destroyTexture(m_pickingRT);
		bgfx::destroyTexture(m_pickingRTDepth);
		bgfx::destroyTexture(m_blitTex);

		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
		{
			bgfx::setViewFrameBuffer(RENDER_PASS_ID, m_pickingFB);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency());
			const double toMs = 1000.0 / freq;
			float time = (float)((bx::getHPCounter() - m_timeOffset) / double(bx::getHPFrequency()));

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/30-picking");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Mouse picking.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			// Set up matrices for basic forward renderer
			const float camSpeed = 0.25;
			float cameraSpin = (float)m_cameraSpin;
			float eyeDist = 2.5f;
			float eye[3] = { -eyeDist * bx::fsin(time*cameraSpin*camSpeed), 0.0f, -eyeDist * bx::fcos(time*cameraSpin*camSpeed) };
			float at[3] = { 0.0f, 0.0f,  0.0f };

			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.1f, 100.0f);

			// Set up view rect and transform for the shaded pass
			bgfx::setViewRect(RENDER_PASS_SHADING, 0, 0, uint16_t(m_width), uint16_t(m_height));
			bgfx::setViewTransform(RENDER_PASS_SHADING, view, proj);

			// Set up picking pass
			float pickView[16];
			float pickAt[4]; // Need to inversly project the mouse pointer to determin what we're looking at
			float pickEye[3] = { eye[0], eye[1], eye[2] };  // Eye is same location as before
			float viewProj[16];
			bx::mtxMul(viewProj, view, proj);
			float invViewProj[16];
			bx::mtxInverse(invViewProj, viewProj);
			// Mouse coord in NDC
			float mouseXNDC = (m_mouseState.m_mx / (float)m_width) * 2.0f - 1.0f;
			float mouseYNDC = ((m_height - m_mouseState.m_my) / (float)m_height) * 2.0f - 1.0f;
			float mousePosNDC[4] = { mouseXNDC, mouseYNDC, 0, 1.0f };
			// Unproject and perspective divide
			bx::vec4MulMtx(pickAt, mousePosNDC, invViewProj);
			pickAt[3] = 1.0f / pickAt[3];
			pickAt[0] *= pickAt[3];
			pickAt[1] *= pickAt[3];
			pickAt[2] *= pickAt[3];

			// Look at our unprojected point
			bx::mtxLookAt(pickView, pickEye, pickAt);
			float pickProj[16];

			// Tight FOV is best for picking
			bx::mtxProj(pickProj, m_fov, 1, 0.1f, 100.0f);
			// View rect and transforms for picking pass
			bgfx::setViewRect(RENDER_PASS_ID, 0, 0, ID_DIM, ID_DIM);
			bgfx::setViewTransform(RENDER_PASS_ID, pickView, pickProj);

			// Now that our passes are set up, we can finally draw each mesh

			// Picking highlights a mesh so we'll set up this tint color
			const float tintBasic[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			const float tintHighlighted[4] = { 0.3f, 0.3f, 2.0f, 1.0f };

			for (uint32_t m = 0; m < 12; m++)
			{
				// Set up transform matrix for each mesh
				float mtxRot[16];
				bx::mtxRotateXY(mtxRot
					, 0.0f
					, time*0.37f*(m % 2 ? 1.0f : -1.0f)
					);
				float mtxScale[16];
				float scale = m_meshScale[m];
				bx::mtxScale(mtxScale
					, scale
					, scale
					, scale
					);
				float mtxTrans[16];
				bx::mtxTranslate(mtxTrans
					, (m % 4) - 1.5f
					, (m / 4) - 1.25f
					, 0.0f
					);

				float mtx[16];
				float mtxTransScale[16];
				bx::mtxMul(mtxTransScale, mtxScale, mtxTrans);
				bx::mtxMul(mtx, mtxRot, mtxTransScale);

				// Submit mesh to both of our render passes

				// Set uniform based on if this is the highlighted mesh
				bgfx::setUniform(u_tint, m == m_highlighted ? tintHighlighted : tintBasic);
				meshSubmit(m_meshes[m], RENDER_PASS_SHADING, m_shadingProgram, mtx);

				// Submit ID pass based on mesh ID
				bgfx::setUniform(u_id, m_idsF[m]);
				meshSubmit(m_meshes[m], RENDER_PASS_ID, m_idProgram, mtx);
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
					uint8_t r = *x++;
					uint8_t g = *x++;
					uint8_t b = *x++;
					uint8_t a = *x++;

					const bgfx::Caps* caps = bgfx::getCaps();
					if (bgfx::RendererType::Direct3D9 == caps->rendererType){
						// Comes back as BGRA
						uint8_t temp = r;
						r = b;
						b = temp;
					}

					if (r == 0 && g == 0 && b == 0) // Skip background
						continue;

					uint32_t hashKey = (r)+(g << 8) + (b << 16) + (a << 24);
					std::map<uint32_t, uint32_t>::iterator mapIter = ids.find(hashKey);
					uint32_t amount = 1;
					if (mapIter != ids.end() )
					{
						amount = mapIter->second + 1;
					}
					ids[hashKey] = amount; // Amount of times this ID (color) has been clicked on in buffer
					maxAmount = maxAmount > amount ? maxAmount : amount;
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
					for (uint32_t i = 0; i < 12; i++)
					{
						if (m_idsU[i] == idKey)
						{
							m_highlighted = i;
							break;
						}
					}
				}
			}

			// Start a new readback?
			if (!m_reading && m_mouseState.m_buttons[entry::MouseButton::Left])
			{
				// Blit and read
				bgfx::blit(RENDER_PASS_BLIT, m_blitTex, 0, 0, m_pickingRT);
				m_reading = bgfx::readTexture(m_blitTex, m_blitData);
			}

			// Draw UI
			imguiBeginFrame(m_mouseState.m_mx
				, m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				, m_mouseState.m_mz
				, m_width
				, m_height
				);

			imguiBeginArea("Picking Render Target:", 10, 100, 300, 400);
			imguiImage(m_pickingRT, 1.0f, 1.0f, 1.0f);
			imguiSlider("FOV", m_fov, 1.0f, 60.0f, 1.0f);

			if (imguiCheck("Spin Camera", m_cameraSpin))
			{
				m_cameraSpin = !m_cameraSpin;
			}

			imguiEndArea();
			imguiEndFrame();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			m_currFrame = bgfx::frame();

			return true;
		}

		return false;
	}

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	int64_t m_timeOffset;

	entry::MouseState m_mouseState;

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

ENTRY_IMPLEMENT_MAIN(ExamplePicking);
