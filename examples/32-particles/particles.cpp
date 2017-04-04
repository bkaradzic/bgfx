/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include <entry/cmd.h>
#include <entry/input.h>

#include <camera.h>
#include <debugdraw/debugdraw.h>
#include <imgui/imgui.h>

#include <bx/rng.h>
#include <bx/easing.h>

#include <ps/particle_system.h>

static const char* s_shapeNames[] =
{
	"Sphere",
	"Hemisphere",
	"Circle",
	"Disc",
	"Rect",
};

static const char* s_directionName[] =
{
	"Up",
	"Outward",
};

static const char* s_easeFuncName[] =
{
	"Linear",
	"InQuad",
	"OutQuad",
	"InOutQuad",
	"OutInQuad",
	"InCubic",
	"OutCubic",
	"InOutCubic",
	"OutInCubic",
	"InQuart",
	"OutQuart",
	"InOutQuart",
	"OutInQuart",
	"InQuint",
	"OutQuint",
	"InOutQuint",
	"OutInQuint",
	"InSine",
	"OutSine",
	"InOutSine",
	"OutInSine",
	"InExpo",
	"OutExpo",
	"InOutExpo",
	"OutInExpo",
	"InCirc",
	"OutCirc",
	"InOutCirc",
	"OutInCirc",
	"InElastic",
	"OutElastic",
	"InOutElastic",
	"OutInElastic",
	"InBack",
	"OutBack",
	"InOutBack",
	"OutInBack",
	"InBounce",
	"OutBounce",
	"InOutBounce",
	"OutInBounce",
};
BX_STATIC_ASSERT(BX_COUNTOF(s_easeFuncName) == bx::Easing::Count);

struct Emitter
{
	EmitterUniforms m_uniforms;
	EmitterHandle   m_handle;

	EmitterShape::Enum     m_shape;
	EmitterDirection::Enum m_direction;

	void create()
	{
		m_shape      = EmitterShape::Sphere;
		m_direction  = EmitterDirection::Outward;

		m_handle = psCreateEmitter(m_shape, m_direction, 1024);
		m_uniforms.reset();
	}

	void destroy()
	{
		psDestroyEmitter(m_handle);
	}

	void update()
	{
		psUpdateEmitter(m_handle, &m_uniforms);
	}

	void imgui(const float* _view, const float* _proj)
	{
//		if (ImGui::CollapsingHeader("General") )
		{
			if (ImGui::Combo("Shape", (int*)&m_shape, s_shapeNames, BX_COUNTOF(s_shapeNames) )
			||  ImGui::Combo("Direction", (int*)&m_direction, s_directionName, BX_COUNTOF(s_directionName) ) )
			{
				psDestroyEmitter(m_handle);
				m_handle = psCreateEmitter(m_shape, m_direction, 1024);
			}

			ImGui::SliderInt("particles / s", (int*)&m_uniforms.m_particlesPerSecond, 0, 1024);

			ImGui::SliderFloat("Gravity scale"
					, &m_uniforms.m_gravityScale
					, -2.0f
					,  2.0f
					);

			ImGui::RangeSliderFloat("Life span"
					, &m_uniforms.m_lifeSpan[0]
					, &m_uniforms.m_lifeSpan[1]
					, 0.1f
					, 5.0f
					);

			if (ImGui::Button("Reset") )
			{
				psUpdateEmitter(m_handle);
			}
		}

		if (ImGui::CollapsingHeader("Position and scale") )
		{
			ImGui::Combo("Position Ease", (int*)&m_uniforms.m_easePos, s_easeFuncName, BX_COUNTOF(s_easeFuncName) );

			ImGui::RangeSliderFloat("Start offset"
					, &m_uniforms.m_offsetStart[0]
					, &m_uniforms.m_offsetStart[1]
					, 0.0f
					, 10.0f
					);
			ImGui::RangeSliderFloat("End offset"
					, &m_uniforms.m_offsetEnd[0]
					, &m_uniforms.m_offsetEnd[1]
					, 0.0f
					, 10.0f
					);

			ImGui::Text("Scale:");

			ImGui::Combo("Scale Ease", (int*)&m_uniforms.m_easeScale, s_easeFuncName, BX_COUNTOF(s_easeFuncName) );

			ImGui::RangeSliderFloat("Scale Start"
					, &m_uniforms.m_scaleStart[0]
					, &m_uniforms.m_scaleStart[1]
					, 0.0f
					, 3.0f
					);
			ImGui::RangeSliderFloat("Scale End"
					, &m_uniforms.m_scaleEnd[0]
					, &m_uniforms.m_scaleEnd[1]
					, 0.0f
					, 3.0f
					);
		}

		if (ImGui::CollapsingHeader("Blending and color") )
		{
			ImGui::Combo("Blend Ease", (int*)&m_uniforms.m_easeBlend, s_easeFuncName, BX_COUNTOF(s_easeFuncName) );
			ImGui::RangeSliderFloat("Blend Start"
					, &m_uniforms.m_blendStart[0]
					, &m_uniforms.m_blendStart[1]
					, 0.0f
					, 1.0f
					);
			ImGui::RangeSliderFloat("Blend End"
					, &m_uniforms.m_blendEnd[0]
					, &m_uniforms.m_blendEnd[1]
					, 0.0f
					, 1.0f
					);

			ImGui::Text("Color:");

			ImGui::Combo("RGBA Ease", (int*)&m_uniforms.m_easeRgba, s_easeFuncName, BX_COUNTOF(s_easeFuncName) );
			ImGui::ColorEdit4("RGBA0", &m_uniforms.m_rgba[0], true);
			ImGui::ColorEdit4("RGBA1", &m_uniforms.m_rgba[1], true);
			ImGui::ColorEdit4("RGBA2", &m_uniforms.m_rgba[2], true);
			ImGui::ColorEdit4("RGBA3", &m_uniforms.m_rgba[3], true);
			ImGui::ColorEdit4("RGBA4", &m_uniforms.m_rgba[4], true);
		}

		ImGui::End();

		float mtx[16];
		bx::mtxSRT(mtx
				, 1.0f, 1.0f, 1.0f
				, m_uniforms.m_angle[0],    m_uniforms.m_angle[1],    m_uniforms.m_angle[2]
				, m_uniforms.m_position[0], m_uniforms.m_position[1], m_uniforms.m_position[2]
				);

		ImGuizmo::Manipulate(
				_view
				, _proj
				, ImGuizmo::TRANSLATE
				, ImGuizmo::LOCAL
				, mtx
				);

		float scale[3];
		ImGuizmo::DecomposeMatrixToComponents(mtx, m_uniforms.m_position, m_uniforms.m_angle, scale);
	}
};

class Particles : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = 1280;
		m_height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		// Enable m_debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x202020ff
				, 1.0f
				, 0
				);

		ddInit();

		psInit();

		bimg::ImageContainer* image = imageLoad(
			  "textures/particle.ktx"
			, bgfx::TextureFormat::BGRA8
			);

		EmitterSpriteHandle sprite = psCreateSprite(
				  uint16_t(image->m_width)
				, uint16_t(image->m_height)
				, image->m_data
				);

		bimg::imageFree(image);

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_emitter); ++ii)
		{
			m_emitter[ii].create();
			m_emitter[ii].m_uniforms.m_handle = sprite;
		}

		imguiCreate();

		cameraCreate();

		const float initialPos[3] = { 0.0f, 2.0f, -12.0f };
		cameraSetPosition(initialPos);
		cameraSetVerticalAngle(0.0f);

		m_timeOffset = bx::getHPCounter();
	}

	virtual int shutdown() BX_OVERRIDE
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(m_emitter); ++ii)
		{
			m_emitter[ii].destroy();
		}

		psShutdown();

		ddShutdown();

		imguiDestroy();

		cameraDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			bgfx::touch(0);

			int64_t now = bx::getHPCounter() - m_timeOffset;
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0/freq;
			const float deltaTime = float(frameTime/freq);

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/32-particles");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Particles.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			// Update camera.George RR Martin
			cameraUpdate(deltaTime, m_mouseState);

			float view[16];
			cameraGetViewMtx(view);

			float proj[16];

			// Set view and projection matrix for view 0.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
			{
				float eye[3];
				cameraGetPosition(eye);
				bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);
				bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

				bgfx::setViewTransform(0, view, proj);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			imguiBeginFrame(
				   m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			ImGui::Begin("Properties"
				, NULL
				, ImVec2(400.0f, 600.0f)
				, ImGuiWindowFlags_AlwaysAutoResize
				);

			static float timeScale = 1.0f;
			ImGui::SliderFloat("Time scale"
				, &timeScale
				, 0.0f
				, 1.0f
				);

			static bool showBounds;
			ImGui::Checkbox("Show bounds", &showBounds);

			ImGui::Text("Emitter:");
			static int currentEmitter = 0;
			for (uint32_t ii = 0; ii < BX_COUNTOF(m_emitter); ++ii)
			{
				ImGui::SameLine();

				char name[16];
				bx::snprintf(name, BX_COUNTOF(name), "%d", ii);

				ImGui::RadioButton(name, &currentEmitter, ii);
			}

			m_emitter[currentEmitter].imgui(view, proj);

			imguiEndFrame();

			ddBegin(0);

			float center[3] = { 0.0f, 0.0f, 0.0f };
			ddDrawGrid(Axis::Y, center);

			float eye[3];
			cameraGetPosition(eye);

			m_emitter[currentEmitter].update();

			psUpdate(deltaTime * timeScale);
			psRender(0, view, eye);

			if (showBounds)
			{
				Aabb aabb;
				psGetAabb(m_emitter[currentEmitter].m_handle, aabb);
				ddSetColor(0xff0000ff);
				ddDraw(aabb);
			}

			ddEnd();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	int64_t m_timeOffset;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	Emitter m_emitter[4];
};

ENTRY_IMPLEMENT_MAIN(Particles);
