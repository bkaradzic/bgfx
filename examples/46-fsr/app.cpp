/*
 * Copyright 2021 Richard Schubert. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 *
 * AMD FidelityFX Super Resolution 1.0 (FSR)
 * Based on https://github.com/GPUOpen-Effects/FidelityFX-FSR/blob/master/sample/
 */

#include <common.h>
#include <camera.h>
#include <bgfx_utils.h>
#include <imgui/imgui.h>
#include <bx/rng.h>
#include <bx/os.h>

#include "fsr.h"

namespace
{

#define FRAMEBUFFER_RT_COLOR 0
#define FRAMEBUFFER_RT_DEPTH 1
#define FRAMEBUFFER_RENDER_TARGETS 2

	enum Meshes
	{
		MeshCube = 0,
		MeshHollowCube,
	};

	static const char *s_meshPaths[] =
	{
		"meshes/cube.bin",
		"meshes/hollowcube.bin",
	};

	static const float s_meshScale[] =
	{
		0.45f,
		0.30f,
	};

	// Vertex decl for our screen space quad (used in deferred rendering)
	struct PosTexCoord0Vertex
	{
		float m_x;
		float m_y;
		float m_z;
		float m_u;
		float m_v;

		static void init()
		{
			ms_layout
				.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.end();
		}

		static bgfx::VertexLayout ms_layout;
	};

	bgfx::VertexLayout PosTexCoord0Vertex::ms_layout;

	void screenSpaceTriangle(float _textureWidth, float _textureHeight, float _texelHalf, bool _originBottomLeft, float _width = 1.0f, float _height = 1.0f, float _offsetX = 0.0f, float _offsetY = 0.0f)
	{
		if (3 == bgfx::getAvailTransientVertexBuffer(3, PosTexCoord0Vertex::ms_layout) )
		{
			bgfx::TransientVertexBuffer vb;
			bgfx::allocTransientVertexBuffer(&vb, 3, PosTexCoord0Vertex::ms_layout);
			PosTexCoord0Vertex *vertex = (PosTexCoord0Vertex *)vb.data;

			const float minx = -_width - _offsetX;
			const float maxx = _width - _offsetX;
			const float miny = 0.0f - _offsetY;
			const float maxy = _height * 2.0f - _offsetY;

			const float texelHalfW = _texelHalf / _textureWidth;
			const float texelHalfH = _texelHalf / _textureHeight;
			const float minu = -1.0f + texelHalfW;
			const float maxu = 1.0f + texelHalfW;

			const float zz = 0.0f;

			float minv = texelHalfH;
			float maxv = 2.0f + texelHalfH;

			if (_originBottomLeft)
			{
				float temp = minv;
				minv = maxv;
				maxv = temp;

				minv -= 1.0f;
				maxv -= 1.0f;
			}

			vertex[0].m_x = minx;
			vertex[0].m_y = miny;
			vertex[0].m_z = zz;
			vertex[0].m_u = minu;
			vertex[0].m_v = minv;

			vertex[1].m_x = maxx;
			vertex[1].m_y = miny;
			vertex[1].m_z = zz;
			vertex[1].m_u = maxu;
			vertex[1].m_v = minv;

			vertex[2].m_x = maxx;
			vertex[2].m_y = maxy;
			vertex[2].m_z = zz;
			vertex[2].m_u = maxu;
			vertex[2].m_v = maxv;

			bgfx::setVertexBuffer(0, &vb);
		}
	}

	struct ModelUniforms
	{
		enum
		{
			NumVec4 = 2
		};

		void init()
		{
			u_params = bgfx::createUniform("u_modelParams", bgfx::UniformType::Vec4, NumVec4);
		};

		void submit() const
		{
			bgfx::setUniform(u_params, m_params, NumVec4);
		};

		void destroy()
		{
			bgfx::destroy(u_params);
		}

		union
		{
			struct
			{
				/* 0 */ struct
				{
					float m_color[3];
					float m_unused0;
				};
				/* 1 */ struct
				{
					float m_lightPosition[3];
					float m_unused1;
				};
			};

			float m_params[NumVec4 * 4];
		};

		bgfx::UniformHandle u_params;
	};

	struct AppState
	{
		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_debug;
		uint32_t m_reset;

		entry::MouseState m_mouseState;

		// Resource handles
		bgfx::ProgramHandle m_forwardProgram;
		bgfx::ProgramHandle m_gridProgram;
		bgfx::ProgramHandle m_copyLinearToGammaProgram;

		// Shader uniforms
		ModelUniforms m_modelUniforms;

		// Uniforms to identify texture samplers
		bgfx::UniformHandle s_albedo;
		bgfx::UniformHandle s_color;
		bgfx::UniformHandle s_normal;

		bgfx::FrameBufferHandle m_frameBuffer;
		bgfx::TextureHandle m_frameBufferTex[FRAMEBUFFER_RENDER_TARGETS];

		Mesh *m_meshes[BX_COUNTOF(s_meshPaths)];
		bgfx::TextureHandle m_groundTexture;
		bgfx::TextureHandle m_normalTexture;

		uint32_t m_currFrame{UINT32_MAX};
		float m_lightRotation = 0.0f;
		float m_texelHalf = 0.0f;
		float m_fovY = 60.0f;
		float m_animationTime = 0.0f;

		float m_view[16];
		float m_proj[16];
		int32_t m_size[2];

		// UI parameters
		bool m_renderNativeResolution = false;
		bool m_animateScene = false;
		int32_t m_antiAliasingSetting = 2;

		Fsr m_fsr;
	};

	struct RenderTarget
	{
		void init(uint32_t _width, uint32_t _height, bgfx::TextureFormat::Enum _format, uint64_t _flags)
		{
			m_width   = _width;
			m_height  = _height;
			m_texture = bgfx::createTexture2D(uint16_t(_width), uint16_t(_height), false, 1, _format, _flags);
			m_buffer  = bgfx::createFrameBuffer(1, &m_texture, true);
		}

		void destroy()
		{
			// also responsible for destroying texture
			bgfx::destroy(m_buffer);
		}

		uint32_t m_width;
		uint32_t m_height;
		bgfx::TextureHandle m_texture;
		bgfx::FrameBufferHandle m_buffer;
	};

	struct MagnifierWidget
	{
		void init(uint32_t _width, uint32_t _height)
		{
			m_content.init(_width, _height, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT | BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT);
			createWidgetTexture(_width + 6, _height + 6);
		}

		void destroy()
		{
			bgfx::destroy(m_widgetTexture);
			m_content.destroy();
		}

		void setPosition(float x, float y)
		{
			m_position.x = x;
			m_position.y = y;
		}

		void drawToScreen(bgfx::ViewId &view, AppState const &state)
		{
			float invScreenScaleX = 1.0f / float(state.m_width);
			float invScreenScaleY = 1.0f / float(state.m_height);
			float scaleX = m_widgetWidth * invScreenScaleX;
			float scaleY = m_widgetHeight * invScreenScaleY;
			float offsetX = -bx::min(bx::max(m_position.x - m_widgetWidth * 0.5f, -3.0f), float(state.m_width - m_widgetWidth + 3) ) * invScreenScaleX;
			float offsetY = -bx::min(bx::max(m_position.y - m_widgetHeight * 0.5f, -3.0f), float(state.m_height - m_widgetHeight + 3) ) * invScreenScaleY;

			bgfx::setState(0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_ALWAYS | BGFX_STATE_BLEND_ALPHA);
			bgfx::setTexture(0, state.s_color, m_widgetTexture);
			screenSpaceTriangle(float(m_widgetWidth), float(m_widgetHeight), state.m_texelHalf, false, scaleX, scaleY, offsetX, offsetY);
			bgfx::submit(view, state.m_copyLinearToGammaProgram);
		}

		void updateContent(bgfx::ViewId &view, AppState const &state, const bgfx::Caps *caps, bgfx::TextureHandle srcTexture)
		{
			float orthoProj[16];
			bx::mtxOrtho(orthoProj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, caps->homogeneousDepth);
			{
				// clear out transform stack
				float identity[16];
				bx::mtxIdentity(identity);
				bgfx::setTransform(identity);
			}

			const float verticalPos = caps->originBottomLeft ? state.m_height - m_position.y : m_position.y;
			const float invMagScaleX = 1.0f / float(m_content.m_width);
			const float invMagScaleY = 1.0f / float(m_content.m_height);
			const float scaleX = state.m_width * invMagScaleX;
			const float scaleY = state.m_height * invMagScaleY;
			const float offsetX = bx::min(bx::max(m_position.x - m_content.m_width * 0.5f, 0.0f), float(state.m_width - m_content.m_width) ) * scaleX / state.m_width;
			const float offsetY = bx::min(bx::max(verticalPos - m_content.m_height * 0.5f, 0.0f), float(state.m_height - m_content.m_height) ) * scaleY / state.m_height;

			bgfx::setViewName(view, "magnifier");
			bgfx::setViewRect(view, 0, 0, uint16_t(m_content.m_width), uint16_t(m_content.m_height) );
			bgfx::setViewTransform(view, NULL, orthoProj);
			bgfx::setViewFrameBuffer(view, m_content.m_buffer);
			bgfx::setState(0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
			bgfx::setTexture(0, state.s_color, srcTexture, BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);
			screenSpaceTriangle(float(state.m_width), float(state.m_height), state.m_texelHalf, false, scaleX, scaleY, offsetX, offsetY);
			bgfx::submit(view, state.m_copyLinearToGammaProgram);
			++view;
		}

		uint32_t m_widgetWidth{0};
		uint32_t m_widgetHeight{0};
		bgfx::TextureHandle m_widgetTexture;
		RenderTarget m_content;
		ImVec2 m_position;

	private:
		void createWidgetTexture(uint32_t _width, uint32_t _height)
		{
			const bgfx::Memory *mem = bgfx::alloc(_width * _height * sizeof(uint32_t) );

			uint32_t *pixels = (uint32_t*)mem->data;
			bx::memSet(pixels, 0, mem->size);

			const uint32_t white = 0xFFFFFFFF;
			const uint32_t black = 0xFF000000;

			const uint32_t y0 = 1;
			const uint32_t y1 = _height - 3;

			for (uint32_t x = 0; x < _width - 4; x++)
			{
				pixels[(y0 + 0) * _width + x + 1] = white;
				pixels[(y0 + 1) * _width + x + 2] = black;
				pixels[(y1 + 0) * _width + x + 1] = white;
				pixels[(y1 + 1) * _width + x + 2] = black;
			}

			const uint32_t x0 = 1;
			const uint32_t x1 = _width - 3;

			for (uint32_t y = 0; y < _height - 3; y++)
			{
				pixels[(y + 1) * _width + x0 + 0] = white;
				pixels[(y + 2) * _width + x0 + 1] = black;
				pixels[(y + 1) * _width + x1 + 0] = white;
				pixels[(y + 2) * _width + x1 + 1] = black;
			}

			pixels[(y1 + 0) * _width + 2] = white;

			m_widgetWidth   = _width;
			m_widgetHeight  = _height;
			m_widgetTexture = bgfx::createTexture2D(
				  uint16_t(_width)
				, uint16_t(_height)
				, false
				, 1
				, bgfx::TextureFormat::BGRA8
				, BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
				, mem
				);
		}
	};

	class ExampleFsr : public entry::AppI
	{
	public:
		ExampleFsr(const char *_name, const char *_description)
			: entry::AppI(_name, _description)
		{
		}

		void init(int32_t _argc, const char *const *_argv, uint32_t _width, uint32_t _height) override
		{
			Args args(_argc, _argv);

			m_state.m_width  = _width;
			m_state.m_height = _height;
			m_state.m_debug  = BGFX_DEBUG_NONE;
			m_state.m_reset  = 0
				| BGFX_RESET_VSYNC
				| BGFX_RESET_MAXANISOTROPY
				;

			bgfx::Init init;
			init.type = args.m_type;

			init.vendorId          = args.m_pciId;
			init.resolution.width  = m_state.m_width;
			init.resolution.height = m_state.m_height;
			init.resolution.reset  = m_state.m_reset;
			bgfx::init(init);

			// Enable debug text.
			bgfx::setDebug(m_state.m_debug);

			// Create uniforms for screen passes and models
			m_state.m_modelUniforms.init();

			// Create texture sampler uniforms (used when we bind textures)
			m_state.s_albedo = bgfx::createUniform("s_albedo", bgfx::UniformType::Sampler);
			m_state.s_color  = bgfx::createUniform("s_color",  bgfx::UniformType::Sampler);
			m_state.s_normal = bgfx::createUniform("s_normal", bgfx::UniformType::Sampler);

			// Create program from shaders.
			m_state.m_forwardProgram           = loadProgram("vs_fsr_forward",    "fs_fsr_forward");
			m_state.m_gridProgram              = loadProgram("vs_fsr_forward",    "fs_fsr_forward_grid");
			m_state.m_copyLinearToGammaProgram = loadProgram("vs_fsr_screenquad", "fs_fsr_copy_linear_to_gamma");

			// Load some meshes
			for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
			{
				m_state.m_meshes[ii] = meshLoad(s_meshPaths[ii]);
			}

			m_state.m_groundTexture = loadTexture("textures/fieldstone-rgba.dds");
			m_state.m_normalTexture = loadTexture("textures/fieldstone-n.dds");

			createFramebuffers();

			// Vertex decl
			PosTexCoord0Vertex::init();

			// Init camera
			cameraCreate();
			cameraSetPosition({-10.0f, 2.5f, -0.0f});
			cameraSetVerticalAngle(-0.2f);
			cameraSetHorizontalAngle(0.8f);

			// Init "prev" matrices, will be same for first frame
			cameraGetViewMtx(m_state.m_view);
			bx::mtxProj(m_state.m_proj, m_state.m_fovY, float(m_state.m_size[0]) / float(m_state.m_size[1]), 0.01f, 100.0f, bgfx::getCaps()->homogeneousDepth);

			// Get renderer capabilities info.
			const bgfx::RendererType::Enum renderer = bgfx::getRendererType();
			m_state.m_texelHalf = bgfx::RendererType::Direct3D9 == renderer ? 0.5f : 0.0f;

			const uint32_t magnifierSize = 32;
			m_magnifierWidget.init(magnifierSize, magnifierSize);
			m_magnifierWidget.setPosition(m_state.m_width * 0.5f, m_state.m_height * 0.5f);

			imguiCreate();

			m_state.m_fsr.init(_width, _height);
		}

		int32_t shutdown() override
		{
			m_state.m_fsr.destroy();

			for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
			{
				meshUnload(m_state.m_meshes[ii]);
			}

			bgfx::destroy(m_state.m_normalTexture);
			bgfx::destroy(m_state.m_groundTexture);

			bgfx::destroy(m_state.m_forwardProgram);
			bgfx::destroy(m_state.m_gridProgram);
			bgfx::destroy(m_state.m_copyLinearToGammaProgram);

			m_state.m_modelUniforms.destroy();

			m_magnifierWidget.destroy();

			bgfx::destroy(m_state.s_albedo);
			bgfx::destroy(m_state.s_color);
			bgfx::destroy(m_state.s_normal);

			destroyFramebuffers();

			cameraDestroy();

			imguiDestroy();

			bgfx::shutdown();

			return 0;
		}

		bool update() override
		{
			if (!entry::processEvents(m_state.m_width, m_state.m_height, m_state.m_debug, m_state.m_reset, &m_state.m_mouseState) )
			{
				// skip processing when minimized, otherwise crashing
				if (0 == m_state.m_width
				||  0 == m_state.m_height)
				{
					return true;
				}

				if (m_state.m_mouseState.m_buttons[entry::MouseButton::Left]
				&&  !ImGui::MouseOverArea() )
				{
					m_magnifierWidget.setPosition(
						  float(m_state.m_mouseState.m_mx)
						, float(m_state.m_mouseState.m_my)
						);
				}

				// Update frame timer
				int64_t now = bx::getHPCounter();
				static int64_t last = now;
				const int64_t frameTime = now - last;
				last = now;
				const double freq = double(bx::getHPFrequency() );
				const float deltaTime = float(frameTime / freq);
				const bgfx::Caps* caps = bgfx::getCaps();

				if (m_state.m_size[0] != (int32_t)m_state.m_width || m_state.m_size[1] != (int32_t)m_state.m_height)
				{
					resize();
				}

				// update animation time
				const float rotationSpeed = 0.25f;
				if (m_state.m_animateScene)
				{
					m_state.m_animationTime += deltaTime * rotationSpeed;
					if (bx::kPi2 < m_state.m_animationTime)
					{
						m_state.m_animationTime -= bx::kPi2;
					}
				}

				// Update camera
				cameraUpdate(deltaTime * 0.15f, m_state.m_mouseState, ImGui::MouseOverArea() );

				cameraGetViewMtx(m_state.m_view);

				updateUniforms();

				bx::mtxProj(
					  m_state.m_proj
					, m_state.m_fovY
					, float(m_state.m_size[0]) / float(m_state.m_size[1])
					, 0.01f
					, 100.0f
					, caps->homogeneousDepth
					);

				bgfx::ViewId view = 0;

				// Clear full frame buffer to avoid sampling into garbage during FSR pass
				if (!m_state.m_renderNativeResolution)
				{
					bgfx::setViewRect(view, 0, 0, (uint16_t)m_state.m_width, (uint16_t)m_state.m_height);
					bgfx::setViewClear(view, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x00000000, 1.0f, 0);
					bgfx::setViewFrameBuffer(view, m_state.m_frameBuffer);
					bgfx::touch(view);

					++view;
				}

				// Draw models into scene
				{
					bgfx::setViewName(view, "forward scene");
					bgfx::setViewClear(view, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x7fb8ffff, 1.0f, 0);

					const float viewScale = m_state.m_renderNativeResolution
						? 1.0f
						: 1.0f / m_state.m_fsr.m_config.m_superSamplingFactor
						;
					const uint16_t viewRectWidth  = uint16_t(bx::ceil(m_state.m_size[0] * viewScale) );
					const uint16_t viewRectHeight = uint16_t(bx::ceil(m_state.m_size[1] * viewScale) );
					const uint16_t viewRectY      = uint16_t(caps->originBottomLeft ? m_state.m_size[1] - viewRectHeight : 0);

					bgfx::setViewRect(view, 0, viewRectY, viewRectWidth, viewRectHeight);
					bgfx::setViewTransform(view, m_state.m_view, m_state.m_proj);
					bgfx::setViewFrameBuffer(view, m_state.m_frameBuffer);

					bgfx::setState(0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_WRITE_Z
						| BGFX_STATE_DEPTH_TEST_LESS
						);

					drawAllModels(view, m_state.m_forwardProgram, m_state.m_modelUniforms);

					++view;
				}

				// optionally run FSR
				if (!m_state.m_renderNativeResolution)
				{
					view = m_state.m_fsr.computeFsr(view, m_state.m_frameBufferTex[FRAMEBUFFER_RT_COLOR]);
				}

				// render result to screen
				{
					bgfx::TextureHandle srcTexture = m_state.m_frameBufferTex[FRAMEBUFFER_RT_COLOR];

					if (!m_state.m_renderNativeResolution)
					{
						srcTexture = m_state.m_fsr.getResultTexture();
					}

					m_magnifierWidget.updateContent(view, m_state, caps, srcTexture);

					float orthoProj[16];
					bx::mtxOrtho(orthoProj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, caps->homogeneousDepth);

					bgfx::setViewName(view, "display");
					bgfx::setViewClear(view, BGFX_CLEAR_NONE, 0, 1.0f, 0);

					bgfx::setViewRect(view, 0, 0, uint16_t(m_state.m_width), uint16_t(m_state.m_height) );
					bgfx::setViewTransform(view, NULL, orthoProj);
					bgfx::setViewFrameBuffer(view, BGFX_INVALID_HANDLE);
					bgfx::setState(0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
					bgfx::setTexture(0, m_state.s_color, srcTexture, BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);
					screenSpaceTriangle(float(m_state.m_width), float(m_state.m_height), m_state.m_texelHalf, caps->originBottomLeft);
					bgfx::submit(view, m_state.m_copyLinearToGammaProgram);
				}

				m_magnifierWidget.drawToScreen(view, m_state);

				++view;

				// Draw UI
				imguiBeginFrame(m_state.m_mouseState.m_mx, m_state.m_mouseState.m_my, (m_state.m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0) | (m_state.m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0) | (m_state.m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0), m_state.m_mouseState.m_mz, uint16_t(m_state.m_width), uint16_t(m_state.m_height) );

				showExampleDialog(this);

				ImGui::SetNextWindowPos(ImVec2(m_state.m_width - m_state.m_width / 4.0f - 10.0f, 10.0f), ImGuiCond_FirstUseEver);
				ImGui::SetNextWindowSize(ImVec2(m_state.m_width / 4.0f, m_state.m_height / 1.2f), ImGuiCond_FirstUseEver);
				ImGui::Begin("Settings", NULL, 0);
				ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);

				const ImVec2 itemSize = ImGui::GetItemRectSize();

				{
					ImGui::Checkbox("Animate scene", &m_state.m_animateScene);

					if (ImGui::Combo("Antialiasing", &m_state.m_antiAliasingSetting, "none\0""4x\0""16x\0""\0") )
					{
						resize();
					}

					ImGui::Checkbox("Render native resolution", &m_state.m_renderNativeResolution);

					if (ImGui::IsItemHovered() )
					{
						ImGui::SetTooltip("Disable super sampling and FSR.");
					}

					ImGui::Image(m_magnifierWidget.m_content.m_texture, ImVec2(itemSize.x * 0.94f, itemSize.x * 0.94f) );

					if (!m_state.m_renderNativeResolution)
					{
						ImGui::SliderFloat("Super sampling", &m_state.m_fsr.m_config.m_superSamplingFactor, 1.0f, 2.0f);

						if (ImGui::IsItemHovered() )
						{
							ImGui::BeginTooltip();
							ImGui::Text("2.0 means the scene is rendered at half window resolution.");
							ImGui::Text("1.0 means the scene is rendered at native window resolution.");
							ImGui::EndTooltip();
						}

						ImGui::Separator();

						if (m_state.m_fsr.supports16BitPrecision() )
						{
							ImGui::Checkbox("Use 16 Bit", &m_state.m_fsr.m_config.m_fsr16Bit);

							if (ImGui::IsItemHovered() )
							{
								ImGui::BeginTooltip();
								ImGui::Text("For better performance and less memory consumption use 16 Bit precision.");
								ImGui::Text("If disabled use 32 Bit per channel precision for FSR which works better on older hardware.");
								ImGui::Text("FSR in 16 Bit precision is also prone to be broken in Direct3D11, Direct3D12 works though.");
								ImGui::EndTooltip();
							}
						}

						ImGui::Checkbox("Apply FSR", &m_state.m_fsr.m_config.m_applyFsr);

						if (ImGui::IsItemHovered() )
						{
							ImGui::SetTooltip("Compare between FSR and bilinear interpolation of source image.");
						}

						if (m_state.m_fsr.m_config.m_applyFsr)
						{
							ImGui::Checkbox("Apply FSR sharpening", &m_state.m_fsr.m_config.m_applyFsrRcas);

							if (ImGui::IsItemHovered() )
							{
								ImGui::SetTooltip("Apply the FSR RCAS sharpening pass.");
							}

							if (m_state.m_fsr.m_config.m_applyFsrRcas)
							{
								ImGui::SliderFloat("Sharpening attenuation", &m_state.m_fsr.m_config.m_rcasAttenuation, 0.01f, 2.0f);

								if (ImGui::IsItemHovered() )
								{
									ImGui::SetTooltip("Lower value means sharper.");
								}
							}
						}
					}
				}

				ImGui::End();

				imguiEndFrame();

				// Advance to next frame. Rendering thread will be kicked to
				// process submitted rendering primitives.
				m_state.m_currFrame = bgfx::frame();

				return true;
			}

			return false;
		}

		void drawAllModels(bgfx::ViewId _pass, bgfx::ProgramHandle _program, ModelUniforms &_uniforms)
		{
			const int32_t width = 6;
			const int32_t length = 20;

			float c0[] = { 235.0f / 255.0f, 126.0f / 255.0f,  30.0f / 255.0f}; // orange
			float c1[] = { 235.0f / 255.0f, 146.0f / 255.0f, 251.0f / 255.0f}; // purple
			float c2[] = { 199.0f / 255.0f,   0.0f / 255.0f,  57.0f / 255.0f}; // pink

			for (int32_t zz = 0; zz < length; ++zz)
			{
				// make a color gradient, nothing special about this for example
				float *ca = c0;
				float *cb = c1;
				float lerpVal = float(zz) / float(length);

				if (0.5f <= lerpVal)
				{
					ca = c1;
					cb = c2;
				}
				lerpVal = bx::fract(2.0f * lerpVal);

				float r = bx::lerp(ca[0], cb[0], lerpVal);
				float g = bx::lerp(ca[1], cb[1], lerpVal);
				float b = bx::lerp(ca[2], cb[2], lerpVal);

				for (int32_t xx = 0; xx < width; ++xx)
				{
					const float angle = m_state.m_animationTime + float(zz) * (bx::kPi2 / length) + float(xx) * (bx::kPiHalf / width);

					const float posX = 2.0f * xx - width + 1.0f;
					const float posY = bx::sin(angle);
					const float posZ = 2.0f * zz - length + 1.0f;

					const float scale = s_meshScale[MeshHollowCube];
					float mtx[16];
					bx::mtxSRT(mtx, scale, scale, scale, 0.0f, 0.0f, 0.0f, posX, posY, posZ);

					bgfx::setTexture(0, m_state.s_albedo, m_state.m_groundTexture);
					bgfx::setTexture(1, m_state.s_normal, m_state.m_normalTexture);
					_uniforms.m_color[0] = r;
					_uniforms.m_color[1] = g;
					_uniforms.m_color[2] = b;
					_uniforms.submit();

					meshSubmit(m_state.m_meshes[MeshHollowCube], _pass, _program, mtx);
				}
			}

			// draw box as ground plane
			{
				const float posY = -2.0f;
				const float scale = length;
				float mtx[16];
				bx::mtxSRT(mtx, scale, scale, scale, 0.0f, 0.0f, 0.0f, 0.0f, -scale + posY, 0.0f);

				_uniforms.m_color[0] = 0.5f;
				_uniforms.m_color[1] = 0.5f;
				_uniforms.m_color[2] = 0.5f;
				_uniforms.submit();

				meshSubmit(m_state.m_meshes[MeshCube], _pass, m_state.m_gridProgram, mtx);
			}
		}

		void resize()
		{
			destroyFramebuffers();
			createFramebuffers();
			m_state.m_fsr.resize(m_state.m_width, m_state.m_height);
		}

		void createFramebuffers()
		{
			m_state.m_size[0] = m_state.m_width;
			m_state.m_size[1] = m_state.m_height;

			constexpr uint64_t msaaFlags[] =
			{
				BGFX_TEXTURE_NONE,
				BGFX_TEXTURE_RT_MSAA_X4,
				BGFX_TEXTURE_RT_MSAA_X16,
			};

			const uint64_t msaa = msaaFlags[m_state.m_antiAliasingSetting];
			const uint64_t colorFlags = 0
				| BGFX_TEXTURE_RT
				| BGFX_SAMPLER_U_CLAMP
				| BGFX_SAMPLER_V_CLAMP
				| msaa
				;
			const uint64_t depthFlags = 0
				| BGFX_TEXTURE_RT_WRITE_ONLY
				| msaa
				;

			m_state.m_frameBufferTex[FRAMEBUFFER_RT_COLOR] = bgfx::createTexture2D(
				  uint16_t(m_state.m_size[0])
				, uint16_t(m_state.m_size[1])
				, false
				, 1
				, bgfx::TextureFormat::RGBA16F
				, colorFlags
				);

			m_state.m_frameBufferTex[FRAMEBUFFER_RT_DEPTH] = bgfx::createTexture2D(
				  uint16_t(m_state.m_size[0])
				, uint16_t(m_state.m_size[1])
				, false
				, 1
				, bgfx::TextureFormat::D32F
				, depthFlags
				);

			m_state.m_frameBuffer = bgfx::createFrameBuffer(
				  BX_COUNTOF(m_state.m_frameBufferTex)
				, m_state.m_frameBufferTex
				, true
				);
		}

		// all buffers set to destroy their textures
		void destroyFramebuffers()
		{
			bgfx::destroy(m_state.m_frameBuffer);
		}

		void updateUniforms()
		{
			m_state.m_modelUniforms.m_lightPosition[0] = 0.0f;
			m_state.m_modelUniforms.m_lightPosition[1] = 6.0f;
			m_state.m_modelUniforms.m_lightPosition[2] = 10.0f;
		}

		AppState m_state;
		MagnifierWidget m_magnifierWidget;
	};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleFsr
	, "46-fsr"
	, "AMD FidelityFX Super Resolution (FSR)\n"
	  "\n"
	  "For an optimal FSR result high quality antialiasing for the low resolution source image and negative texture LOD bias is recommended."
	);
