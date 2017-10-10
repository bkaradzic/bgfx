/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "camera.h"
#include "imgui/imgui.h"

namespace
{

class ExampleSponza : public entry::AppI
{
public:
	ExampleSponza(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
				);

		float initialPos[3] = { 400.0f, 500.0f, 0.0f };
		cameraCreate();
		cameraSetPosition(initialPos);
		cameraSetHorizontalAngle(-bx::kPi * 0.5f);
		cameraSetVerticalAngle(-0.35f);
		cameraSetMoveSpeed(240.0f);

		u_lightDir = bgfx::createUniform("u_lightDir", bgfx::UniformType::Vec4);
		u_viewDir = bgfx::createUniform("u_viewDir", bgfx::UniformType::Vec4);

		s_diffuseMap = bgfx::createUniform("s_diffuseMap", bgfx::UniformType::Int1);
		s_normalMap = bgfx::createUniform("s_normalMap", bgfx::UniformType::Int1);
		s_specularMap = bgfx::createUniform("s_specularMap", bgfx::UniformType::Int1);

		// Create program from shaders.
		m_program = loadProgram("vs_sponza", "fs_sponza");

		m_mesh = meshLoad("meshes/sponza.bin");

		m_timeOffset = bx::getHPCounter();

		imguiCreate();
	}

	int shutdown() override
	{
		cameraDestroy();

		imguiDestroy();

		meshUnload(m_mesh);

		// Cleanup.
		bgfx::destroy(m_program);

		bgfx::destroy(u_lightDir);
		bgfx::destroy(u_viewDir);

		bgfx::destroy(s_diffuseMap);
		bgfx::destroy(s_normalMap);
		bgfx::destroy(s_specularMap);

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

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency());
			const float deltaTime = float(frameTime / freq);

			// Update camera.
			float view[16];
			cameraUpdate(deltaTime, m_mouseState);
			cameraGetViewMtx(view);

			lightDir[0] = 0.3f;
			lightDir[1] = 1.0f;
			lightDir[2] = 0.3f;
			lightDir[3] = 0.0f;
			bx::vec3Norm(&lightDir[0], &lightDir[0]);

			viewDir[0] = -view[2];
			viewDir[1] = -view[6];
			viewDir[2] = -view[10];
			viewDir[3] = 0.0f;
			bx::vec3Norm(&viewDir[0], &viewDir[0]);

			// Set view and projection matrix for view 0.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING))
			{
				float viewHead[16];
				float eye[3] = {};
				bx::mtxQuatTranslationHMD(viewHead, hmd->eye[0].rotation, eye);

				float tmp[16];
				bx::mtxMul(tmp, view, viewHead);

				bgfx::setViewTransform(0, tmp, hmd->eye[0].projection);
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);

				//bgfx::setViewTransform(1, tmp, hmd->eye[1].projection);
				//bgfx::setViewRect(1, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width) / float(m_height), 0.5f, 3000.0f, bgfx::getCaps()->homogeneousDepth);

				bgfx::setViewTransform(0, view, proj);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				//bgfx::setViewTransform(1, view, proj);
				//bgfx::setViewRect(1, 0, 0, uint16_t(m_width), uint16_t(m_height));
			}

			float mtx[16];
			bx::mtxIdentity(mtx);

			meshSubmit(m_mesh, 0, m_program, mtx, BGFX_STATE_MASK, staticMeshSubmitCallback, this);

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	void meshSubmitCallback(uint32_t index, bgfx::TextureHandle diffuseMap, bgfx::TextureHandle normalMap, bgfx::TextureHandle specularMap)
	{
		BX_UNUSED(index);

		bgfx::setUniform(u_lightDir, &lightDir[0]);
		bgfx::setUniform(u_viewDir, &viewDir[0]);

		if (bgfx::isValid(s_diffuseMap) && bgfx::isValid(diffuseMap))
		{
			bgfx::setTexture(0, s_diffuseMap, diffuseMap);
		}
		if (bgfx::isValid(s_normalMap) && bgfx::isValid(normalMap))
		{
			bgfx::setTexture(1, s_normalMap, normalMap);
		}
		if (bgfx::isValid(s_specularMap) && bgfx::isValid(specularMap))
		{
			bgfx::setTexture(2, s_specularMap, specularMap);
		}
	}

	static void staticMeshSubmitCallback(uint32_t index, bgfx::TextureHandle diffuseMap, bgfx::TextureHandle normalMap, bgfx::TextureHandle specularMap, void* userData)
	{
		ExampleSponza* self = (ExampleSponza*)userData;
		self->meshSubmitCallback(index, diffuseMap, normalMap, specularMap);
	}



	entry::MouseState m_mouseState;

	float lightDir[4];
	float viewDir[4];

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	int64_t m_timeOffset;
	Mesh* m_mesh;
	bgfx::ProgramHandle m_program;
	bgfx::UniformHandle u_lightDir;
	bgfx::UniformHandle u_viewDir;
	bgfx::UniformHandle s_diffuseMap;
	bgfx::UniformHandle s_normalMap;
	bgfx::UniformHandle s_specularMap;

};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleSponza, "37-sponza", "Loading meshes with materials.");
