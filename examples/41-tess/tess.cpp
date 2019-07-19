/*
 * Copyright 2019 Daniel Gavin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

 /*
  * Reference(s):
  * - Adaptive GPU Tessellation with Compute Shaders by Jad Khoury, Jonathan Dupuy, and Christophe Riccio
  *  http://onrendering.com/data/papers/isubd/isubd.pdf
  * - Based on Demo
  *  https://github.com/jdupuy/opengl-framework/tree/master/demo-isubd-terrain#implicit-subdivision-on-the-gpu
  */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"
#include "camera.h"
#include "bounds.h"
#include <bx/allocator.h>
#include <bx/debug.h>
#include <bx/math.h>
#include <bx/file.h>
#include <vector>

#include "constants.h"

namespace
{
	enum {
		PROGRAM_TERRAIN_NORMAL,
		PROGRAM_TERRAIN,
		SHADING_COUNT };

	enum {
		BUFFER_SUBD
	};

	enum {
		PROGRAM_SUBD_CS_LOD,    
		PROGRAM_UPDATE_INDIRECT,  
		PROGRAM_INIT_INDIRECT,
		PROGRAM_UPDATE_DRAW,
		PROGRAM_COUNT
	};

	enum {
		TERRAIN_DMAP_SAMPLER,
		TERRAIN_SMAP_SAMPLER,
		SAMPLER_COUNT
	};

	enum {
		TEXTURE_DMAP,
		TEXTURE_SMAP,
		TEXTURE_COUNT
	};

	struct {
		char* pathToFile;
		float scale;
	} dmap;

	struct Uniforms
	{
		enum { NumVec4 = 2 };

		void init()
		{
			u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, NumVec4);

			cull = 1;
			freeze = 0;
			gpuSubd = 3;

		}

		void submit()
		{
			bgfx::setUniform(u_params, params, NumVec4);
		}

		void destroy()
		{
			bgfx::destroy(u_params);
		}

		union
		{
			struct
			{
				float dmapFactor; float lodFactor; float cull; float freeze;
				float gpuSubd; float padding[3];
			};

			float params[NumVec4 * 4];
		};

		bgfx::UniformHandle u_params;
	};
	class ExampleTessellation : public entry::AppI
	{
	public:
		ExampleTessellation(const char* _name, const char* _description)
			: entry::AppI(_name, _description)
		{
		}

		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
		{
			Args args(_argc, _argv);

			m_width = _width;
			m_height = _height;
			m_debug = BGFX_DEBUG_NONE;
			m_reset = BGFX_RESET_NONE;

			bgfx::Init init;
			init.type = args.m_type;
			init.vendorId = args.m_pciId;
			init.resolution.width = m_width;
			init.resolution.height = m_height;
			init.resolution.reset = m_reset;
			bgfx::init(init);

			m_dmap = { "textures/dmap.png", 0.45f };
			m_computeThreadCount = 5;
			m_shading = PROGRAM_TERRAIN;
			m_primitivePixelLengthTarget = 7.0f;
			m_fovy = 60.0f;
			m_pingPong = 0;
			m_reset_gpu = true;

			// Enable m_debug text.
			bgfx::setDebug(m_debug);

			// Set view 0 clear state.
			bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
			);

			bgfx::setViewClear(1
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
			);

			// Imgui.
			imguiCreate();

			m_timeOffset = bx::getHPCounter();

			m_oldWidth = 0;
			m_oldHeight = 0;
			m_oldReset = m_reset;

			cameraCreate();
			cameraSetPosition({ 0.0f, 0.5f, 0.0f });
			cameraSetVerticalAngle(0);

			is_wireframe = false;
			is_frozen = false;
			is_culled = true;

			loadPrograms();
			loadBuffers();
			loadTextures();

			createAtomicCounters();

			m_dispatchIndirect = bgfx::createIndirectBuffer(2);
		}

		virtual int shutdown() override
		{
			// Cleanup.
			cameraDestroy();
			imguiDestroy();

			m_uniforms.destroy();

			bgfx::destroy(m_bufferCounter);
			bgfx::destroy(m_bufferCulledSubd);
			bgfx::destroy(m_bufferSubd[0]);
			bgfx::destroy(m_bufferSubd[1]);
			bgfx::destroy(m_dispatchIndirect);
			bgfx::destroy(m_geometryIndices);
			bgfx::destroy(m_geometryVertices);
			bgfx::destroy(m_instancedGeometryIndices);
			bgfx::destroy(m_instancedGeometryVertices);

			for (uint32_t i = 0; i < PROGRAM_COUNT; ++i) {
				bgfx::destroy(m_programsCompute[i]);
			}

			for (uint32_t i = 0; i < SHADING_COUNT; ++i) {
				bgfx::destroy(m_programsDraw[i]);
			}

			for (uint32_t i = 0; i < SAMPLER_COUNT; ++i) {
				bgfx::destroy(m_samplers[i]);
			}

			for (uint32_t i = 0; i < TEXTURE_COUNT; ++i) {
				bgfx::destroy(m_textures[i]);
			}

			// Shutdown bgfx.
			bgfx::shutdown();

			return 0;
		}

		bool update() override
		{
			if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			{
				int64_t now = bx::getHPCounter();
				static int64_t last = now;
				const int64_t frameTime = now - last;
				last = now;
				const double freq = double(bx::getHPFrequency());
				const float deltaTime = float(frameTime / freq);

				imguiBeginFrame(m_mouseState.m_mx
					, m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					, m_mouseState.m_mz
					, uint16_t(m_width)
					, uint16_t(m_height)
				);

				showExampleDialog(this);

				ImGui::SetNextWindowPos(
					ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::SetNextWindowSize(
					ImVec2(m_width / 5.0f, m_height / 3.0f)
					, ImGuiCond_FirstUseEver
				);
				ImGui::Begin("Settings"
					, NULL
					, 0
				);

				if (ImGui::Checkbox("Debug wireframe", &is_wireframe)) {
					if (is_wireframe) {
						bgfx::setDebug(BGFX_DEBUG_WIREFRAME);
					}
					else {
						bgfx::setDebug(BGFX_DEBUG_NONE);
					}
				}

				ImGui::SameLine();

				if (ImGui::Checkbox("Cull", &is_culled)) {
					if (is_culled) {
						m_uniforms.cull = 1.0;
					}
					else {
						m_uniforms.cull = 0.0;
					}
				}

				ImGui::SameLine();

				if (ImGui::Checkbox("Freeze subdividing", &is_frozen)) {
					if (is_frozen) {
						m_uniforms.freeze = 1.0;
					}
					else {
						m_uniforms.freeze = 0.0;
					}
				}


				ImGui::SliderFloat("Pixels per edge", &m_primitivePixelLengthTarget, 1, 20);

				int gpuSlider = (int)m_uniforms.gpuSubd;

				if (ImGui::SliderInt("Triangle Patch level", &gpuSlider, 0, 3)) {
					m_reset_gpu = true;
					m_uniforms.gpuSubd = (float)gpuSlider;
				}

				ImGui::Combo("Shading", &m_shading, shader_options, 2);

				ImGui::Text("Some variables require rebuilding the subdivide buffers and causes a stutter.");


				ImGui::End();
				
				if (!ImGui::MouseOverArea())
				{
					// Update camera.
					cameraUpdate(deltaTime, m_mouseState);

					if (!!m_mouseState.m_buttons[entry::MouseButton::Left])
					{
					}
				}

				bgfx::touch(0);
				bgfx::touch(1);

				configureUniforms();

				cameraGetViewMtx(m_viewMtx);

				float model[16];

				bx::mtxRotateX(model, bx::toRad(90));

				bx::mtxProj(m_projMtx, m_fovy, float(m_width) / float(m_height), 0.0001f, 2000.0f, bgfx::getCaps()->homogeneousDepth);

				// Set view 0
				bgfx::setViewTransform(0, m_viewMtx, m_projMtx);

				// Set view 1
				bgfx::setViewRect(1, 0, 0, uint16_t(m_width), uint16_t(m_height));
				bgfx::setViewTransform(1, m_viewMtx, m_projMtx);

				m_uniforms.submit();

				// update the subd buffers
				if (m_reset_gpu) {
					
					m_pingPong = 1;

					bgfx::destroy(m_instancedGeometryVertices);
					bgfx::destroy(m_instancedGeometryIndices);

					bgfx::destroy(m_bufferSubd[BUFFER_SUBD]);
					bgfx::destroy(m_bufferSubd[BUFFER_SUBD + 1]);
					bgfx::destroy(m_bufferCulledSubd);

					loadInstancedGeometryBuffers();
					loadSubdivisionBuffers();

					//init indirect
					bgfx::setBuffer(1, m_bufferSubd[m_pingPong], bgfx::Access::ReadWrite);
					bgfx::setBuffer(2, m_bufferCulledSubd, bgfx::Access::ReadWrite);
					bgfx::setBuffer(3, m_dispatchIndirect, bgfx::Access::ReadWrite);
					bgfx::setBuffer(4, m_bufferCounter, bgfx::Access::ReadWrite);
					bgfx::setBuffer(8, m_bufferSubd[1 - m_pingPong], bgfx::Access::ReadWrite);
					bgfx::dispatch(0, m_programsCompute[PROGRAM_INIT_INDIRECT], 1, 1, 1);


					m_reset_gpu = false;
				}

				else {
					// update batch
					bgfx::setBuffer(3, m_dispatchIndirect, bgfx::Access::ReadWrite);
					bgfx::setBuffer(4, m_bufferCounter, bgfx::Access::ReadWrite);
					bgfx::dispatch(0, m_programsCompute[PROGRAM_UPDATE_INDIRECT], 1, 1, 1);
				}

				bgfx::setBuffer(1, m_bufferSubd[m_pingPong], bgfx::Access::ReadWrite);
				bgfx::setBuffer(2, m_bufferCulledSubd, bgfx::Access::ReadWrite);
				bgfx::setBuffer(4, m_bufferCounter, bgfx::Access::ReadWrite);
				bgfx::setBuffer(6, m_geometryVertices, bgfx::Access::Read);
				bgfx::setBuffer(7, m_geometryIndices, bgfx::Access::Read);
				bgfx::setBuffer(8, m_bufferSubd[1 - m_pingPong], bgfx::Access::Read);
				bgfx::setTransform(model);

				bgfx::setTexture(0, m_samplers[TERRAIN_DMAP_SAMPLER], m_textures[TEXTURE_DMAP], BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);

				m_uniforms.submit();

				// update the subd buffer
				bgfx::dispatch(0, m_programsCompute[PROGRAM_SUBD_CS_LOD], m_dispatchIndirect, 1);

				// update draw
				bgfx::setBuffer(3, m_dispatchIndirect, bgfx::Access::ReadWrite);
				bgfx::setBuffer(4, m_bufferCounter, bgfx::Access::ReadWrite);

				m_uniforms.submit();

				bgfx::dispatch(1, m_programsCompute[PROGRAM_UPDATE_DRAW], 1, 1, 1);

				// render the terrain
				bgfx::setTexture(0, m_samplers[TERRAIN_DMAP_SAMPLER], m_textures[TEXTURE_DMAP], BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP);
				bgfx::setTexture(1, m_samplers[TERRAIN_SMAP_SAMPLER], m_textures[TEXTURE_SMAP], BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC);

				bgfx::setTransform(model);
				bgfx::setVertexBuffer(0, m_instancedGeometryVertices);
				bgfx::setIndexBuffer(m_instancedGeometryIndices);
				bgfx::setBuffer(2, m_bufferCulledSubd, bgfx::Access::Read);
				bgfx::setBuffer(3, m_geometryVertices, bgfx::Access::Read);
				bgfx::setBuffer(4, m_geometryIndices, bgfx::Access::Read);
				bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LESS);

				m_uniforms.submit();

				bgfx::submit(1, m_programsDraw[m_shading], m_dispatchIndirect, 0, true);

				m_pingPong = 1 - m_pingPong;

				imguiEndFrame();

				// Advance to next frame. Rendering thread will be kicked to
				// process submitted rendering primitives.
				bgfx::frame(false);

				return true;
			}

			return false;
		}

		void createAtomicCounters()
		{
			m_bufferCounter = bgfx::createDynamicIndexBuffer(3, BGFX_BUFFER_INDEX32 | BGFX_BUFFER_COMPUTE_READ_WRITE);
		}

		void configureUniforms()
		{
			float lodFactor = 2.0f * bx::tan(bx::toRad(m_fovy) / 2.0f)
				/ m_width * (1 << (int)m_uniforms.gpuSubd)
				* m_primitivePixelLengthTarget;

			m_uniforms.lodFactor = lodFactor;
			m_uniforms.dmapFactor = m_dmap.scale;
		}

		/**
		* Load the Terrain Program
		*
		* This program renders an adaptive terrain using the implicit subdivision
		* technique discribed in GPU Zen 2.
		**/
		void loadPrograms()
		{
			m_samplers[TERRAIN_DMAP_SAMPLER] = bgfx::createUniform("u_DmapSampler", bgfx::UniformType::Sampler);
			m_samplers[TERRAIN_SMAP_SAMPLER] = bgfx::createUniform("u_SmapSampler", bgfx::UniformType::Sampler);

			m_uniforms.init();

			m_programsDraw[PROGRAM_TERRAIN] = loadProgram("vs_terrain_render", "fs_terrain_render");
			m_programsDraw[PROGRAM_TERRAIN_NORMAL] = loadProgram("vs_terrain_render", "fs_terrain_render_normal");

			m_programsCompute[PROGRAM_SUBD_CS_LOD] = bgfx::createProgram(loadShader("cs_terrain_lod"), true);
			m_programsCompute[PROGRAM_UPDATE_INDIRECT] = bgfx::createProgram(loadShader("cs_terrain_update_indirect"), true);
			m_programsCompute[PROGRAM_UPDATE_DRAW] = bgfx::createProgram(loadShader("cs_terrain_update_draw"), true);
			m_programsCompute[PROGRAM_INIT_INDIRECT] = bgfx::createProgram(loadShader("cs_terrain_init"), true);
		}

		void loadSmapTexture()
		{
			int w = dmap->m_width;
			int h = dmap->m_height;

			const uint16_t *texels = (const uint16_t *)dmap->m_data;

			int mipcnt = dmap->m_numMips;

			std::vector<float> smap(w * h * 2);

			for (int j = 0; j < h; ++j) {
				for (int i = 0; i < w; ++i) {
					int i1 = bx::max(0, i - 1);
					int i2 = bx::min(w - 1, i + 1);
					int j1 = bx::max(0, j - 1);
					int j2 = bx::min(h - 1, j + 1);
					uint16_t px_l = texels[i1 + w * j]; // in [0,2^16-1]
					uint16_t px_r = texels[i2 + w * j]; // in [0,2^16-1]
					uint16_t px_b = texels[i + w * j1]; // in [0,2^16-1]
					uint16_t px_t = texels[i + w * j2]; // in [0,2^16-1]
					float z_l = (float)px_l / 65535.0f; // in [0, 1]
					float z_r = (float)px_r / 65535.0f; // in [0, 1]
					float z_b = (float)px_b / 65535.0f; // in [0, 1]
					float z_t = (float)px_t / 65535.0f; // in [0, 1]
					float slope_x = (float)w * 0.5f * (z_r - z_l);
					float slope_y = (float)h * 0.5f * (z_t - z_b);

					smap[2 * (i + w * j)] = slope_x;
					smap[1 + 2 * (i + w * j)] = slope_y;
				}
			}

			m_textures[TEXTURE_SMAP] = bgfx::createTexture2D((uint16_t)w, (uint16_t)h, mipcnt > 1, 1, bgfx::TextureFormat::RG32F,
				BGFX_TEXTURE_NONE, bgfx::copy(smap.data(), (unsigned int)smap.size()*sizeof(float)));

		}


		/**
		 * Load the Displacement Texture
		 *
		 * This loads an R16 texture used as a displacement map
		 */
		void loadDmapTexture()
		{
			dmap = imageLoad(m_dmap.pathToFile, bgfx::TextureFormat::R16);

			m_textures[TEXTURE_DMAP] = bgfx::createTexture2D((uint16_t)dmap->m_width, (uint16_t)dmap->m_height, false, 1, bgfx::TextureFormat::R16,
				BGFX_TEXTURE_NONE, bgfx::makeRef(dmap->m_data, dmap->m_size));
		}

		/**
		 * Load All Textures
		 */
		void loadTextures()
		{
			loadDmapTexture();
			loadSmapTexture();
		}

		/**
        * Load the Geometry Buffer
		*
		* This procedure loads the scene geometry into an index and
		* vertex buffer. Here, we only load 2 triangles to define the
	    * terrain.
	    **/
		void loadGeometryBuffers()
		{
			float vertices[] = {
				-1.0f, -1.0f, 0.0f, 1.0f,
				+1.0f, -1.0f, 0.0f, 1.0f,
				+1.0f, +1.0f, 0.0f, 1.0f,
				-1.0f, +1.0f, 0.0f, 1.0f
			};

			uint32_t indices[] = {
				0, 
				1, 
				3, 
				2, 
				3, 
				1 
			};

			m_geometryDecl.begin().add(bgfx::Attrib::Position, 4, bgfx::AttribType::Float).end();

			m_geometryVertices = bgfx::createVertexBuffer(bgfx::copy(vertices, sizeof(vertices)), m_geometryDecl, BGFX_BUFFER_COMPUTE_READ);
			m_geometryIndices = bgfx::createIndexBuffer(bgfx::copy(indices, sizeof(indices)),  BGFX_BUFFER_COMPUTE_READ | BGFX_BUFFER_INDEX32);
		}

		void loadSubdivisionBuffers()
		{
			const size_t bufferCapacity = 1 << 27;

			m_bufferSubd[BUFFER_SUBD] = bgfx::createDynamicIndexBuffer(bufferCapacity, BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_INDEX32);
			m_bufferSubd[BUFFER_SUBD + 1] = bgfx::createDynamicIndexBuffer(bufferCapacity, BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_INDEX32);
			m_bufferCulledSubd = bgfx::createDynamicIndexBuffer(bufferCapacity, BGFX_BUFFER_COMPUTE_READ_WRITE | BGFX_BUFFER_INDEX32);
		}

		/**
		 * Load All Buffers
		 *
		 */
		void loadBuffers()
		{
			loadSubdivisionBuffers();
			loadGeometryBuffers();
			loadInstancedGeometryBuffers();
		}

		/**
		* This will be used to instantiate a triangle grid for each subdivision
		* key present in the subd buffer.
		*/
		void loadInstancedGeometryBuffers()
		{
			const float* vertices;
			const uint32_t* indexes;

			if (m_uniforms.gpuSubd == 0) {

				m_instancedMeshVertexCount = 3;
				m_instancedMeshPrimitiveCount = 1;

				vertices = verticesL0;
				indexes = indexesL0;
			}

			else if (m_uniforms.gpuSubd == 1) {
				m_instancedMeshVertexCount = 6;
				m_instancedMeshPrimitiveCount = 4;

				vertices = verticesL1;
				indexes = indexesL1;
			}

			else if (m_uniforms.gpuSubd == 2) {
				m_instancedMeshVertexCount = 15;
				m_instancedMeshPrimitiveCount = 16;

				vertices = verticesL2;
				indexes = indexesL2;
			}

			else { //(m_settings.gpuSubd == 3) {
				m_instancedMeshVertexCount = 45;
				m_instancedMeshPrimitiveCount = 64;

				vertices = verticesL3;
				indexes = indexesL3;
			}

			m_instancedGeometryDecl.begin().add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float).end();

			m_instancedGeometryVertices = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(float) * 2 * m_instancedMeshVertexCount), m_instancedGeometryDecl);
			m_instancedGeometryIndices = bgfx::createIndexBuffer(bgfx::makeRef(indexes, sizeof(uint32_t) * m_instancedMeshPrimitiveCount * 3), BGFX_BUFFER_INDEX32);
		}

		Uniforms m_uniforms;

		bgfx::ProgramHandle m_programsCompute[PROGRAM_COUNT];
		bgfx::ProgramHandle m_programsDraw[SHADING_COUNT];
		bgfx::TextureHandle m_textures[TEXTURE_COUNT];
		bgfx::UniformHandle m_samplers[SAMPLER_COUNT];

		bgfx::DynamicIndexBufferHandle m_bufferSubd[2];
		bgfx::DynamicIndexBufferHandle m_bufferCulledSubd;

		bgfx::DynamicIndexBufferHandle m_bufferCounter;

		bgfx::IndexBufferHandle m_geometryIndices;
		bgfx::VertexBufferHandle m_geometryVertices;
		bgfx::VertexDecl m_geometryDecl;

		bgfx::IndexBufferHandle m_instancedGeometryIndices;
		bgfx::VertexBufferHandle m_instancedGeometryVertices;
		bgfx::VertexDecl m_instancedGeometryDecl;

		bgfx::IndirectBufferHandle m_dispatchIndirect;

		bimg::ImageContainer* dmap;

		float m_viewMtx[16];
		float m_projMtx[16];

		uint32_t m_width;
		uint32_t m_height;
		uint32_t m_debug;
		uint32_t m_reset;

		uint32_t m_oldWidth;
		uint32_t m_oldHeight;
		uint32_t m_oldReset;

		uint32_t m_instancedMeshVertexCount;
		uint32_t m_instancedMeshPrimitiveCount;

		entry::MouseState m_mouseState;

		int64_t m_timeOffset;

		struct {
			char* pathToFile;
			float scale;
		} m_dmap;


		int m_computeThreadCount;
		int m_shading;
		int m_gpuSubd;
		float m_primitivePixelLengthTarget;
		float m_fovy;
		int m_pingPong;
		bool m_reset_gpu;
		bool is_wireframe;
		bool is_culled;
		bool is_frozen;
	};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleTessellation, "41-tess", "Adaptive Gpu Tessellation.");
