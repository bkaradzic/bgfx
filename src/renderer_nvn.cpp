/********************************************************
*   (c) Mojang. All rights reserved                     *
*   (c) Microsoft. All rights reserved.                 *
*********************************************************/

#include "bgfx_p.h"

#if BGFX_CONFIG_RENDERER_NVN

#include "renderer_nvn.h"
#include "renderer_nvn/resources.h"

#include <nn/nn_Log.h>

#define BGFX_NVN_USE_STAGING_FOR_UPDATE 0

#if BX_PLATFORM_NX
extern "C"
{
	PFNNVNGENERICFUNCPTRPROC NVNAPIENTRY nvnBootstrapLoader(const char* name);
}
#endif

namespace bgfx { namespace nvn
{
	//
	//
	//

	static char s_viewName[BGFX_CONFIG_MAX_VIEWS][BGFX_CONFIG_MAX_VIEW_NAME];

	struct PrimitiveInfo
	{
		NVNdrawPrimitive m_type;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimitiveInfo s_primitiveInfo[] =
	{
		{ NVN_DRAW_PRIMITIVE_TRIANGLES,			3, 3, 0 },
		{ NVN_DRAW_PRIMITIVE_TRIANGLE_STRIP,	3, 1, 2 },
		{ NVN_DRAW_PRIMITIVE_LINES,				2, 2, 0 },
		{ NVN_DRAW_PRIMITIVE_LINE_STRIP,		2, 1, 1 },
		{ NVN_DRAW_PRIMITIVE_POINTS,			1, 1, 0 },
		{ NVN_DRAW_PRIMITIVE_POLYGON,			0, 0, 0 }  // Undefined
	};
	BX_STATIC_ASSERT(Topology::Count == BX_COUNTOF(s_primitiveInfo) - 1);

	// BBI-NOTE: (tstump) Int8/UInt16 commented out, these are used in the game version of bgfx so keeping here for posterity and ease of porting
	static const NVNformat s_attribType[][4][2] =
	{
		{ // Uint8
			{ NVN_FORMAT_R8UI,		NVN_FORMAT_R8			},
			{ NVN_FORMAT_RG8UI,		NVN_FORMAT_RG8			},
			{ NVN_FORMAT_RGB8UI,	NVN_FORMAT_RGB8			},
			{ NVN_FORMAT_RGBA8UI,	NVN_FORMAT_RGBA8		}
		},
//		{ // Int8
//			{ NVN_FORMAT_R8I,		NVN_FORMAT_R8SN			},
//			{ NVN_FORMAT_RG8I,		NVN_FORMAT_RG8SN		},
//			{ NVN_FORMAT_RGB8I,		NVN_FORMAT_RGB8SN		},
//			{ NVN_FORMAT_RGBA8I,	NVN_FORMAT_RGBA8SN		}
//		},
		{ // Uint10
			{ NVN_FORMAT_RGB10A2UI,	NVN_FORMAT_RGB10A2SN	},
			{ NVN_FORMAT_RGB10A2UI,	NVN_FORMAT_RGB10A2SN	},
			{ NVN_FORMAT_RGB10A2UI,	NVN_FORMAT_RGB10A2SN	},
			{ NVN_FORMAT_RGB10A2UI,	NVN_FORMAT_RGB10A2SN	}
		},
//		{ // UInt16
//			{ NVN_FORMAT_R16UI,		NVN_FORMAT_R16SN		},
//			{ NVN_FORMAT_RG16UI,	NVN_FORMAT_RG16SN		},
//			{ NVN_FORMAT_RGB16UI,	NVN_FORMAT_RGB16SN		},
//			{ NVN_FORMAT_RGBA16UI,	NVN_FORMAT_RGBA16SN		}
//		},
		{ // Int16
			{ NVN_FORMAT_R16I,		NVN_FORMAT_R16SN		},
			{ NVN_FORMAT_RG16I,		NVN_FORMAT_RG16SN		},
			{ NVN_FORMAT_RGB16I,	NVN_FORMAT_RGB16SN		},
			{ NVN_FORMAT_RGBA16I,	NVN_FORMAT_RGBA16SN		}
		},
		{ // Half
			{ NVN_FORMAT_R16F,		NVN_FORMAT_R16F			},
			{ NVN_FORMAT_RG16F,		NVN_FORMAT_RG16F		},
			{ NVN_FORMAT_RGB16F,	NVN_FORMAT_RGB16F		},
			{ NVN_FORMAT_RGBA16F,	NVN_FORMAT_RGBA16F		}
		},
		{ // Float
			{ NVN_FORMAT_R32F,		NVN_FORMAT_R32F			},
			{ NVN_FORMAT_RG32F,		NVN_FORMAT_RG32F		},
			{ NVN_FORMAT_RGB32F,	NVN_FORMAT_RGB32F		},
			{ NVN_FORMAT_RGBA32F,	NVN_FORMAT_RGBA32F		}
		}
	};
	BX_STATIC_ASSERT(AttribType::Count == BX_COUNTOF(s_attribType));

	static const NVNblendFunc s_blendFactor[][2] =
	{
		{ NVNblendFunc::NVN_BLEND_FUNC_ZERO,						NVNblendFunc::NVN_BLEND_FUNC_ZERO						}, // ignored
		{ NVNblendFunc::NVN_BLEND_FUNC_ZERO,						NVNblendFunc::NVN_BLEND_FUNC_ZERO						}, // ZERO
		{ NVNblendFunc::NVN_BLEND_FUNC_ONE,							NVNblendFunc::NVN_BLEND_FUNC_ONE						}, // ONE
		{ NVNblendFunc::NVN_BLEND_FUNC_SRC_COLOR,					NVNblendFunc::NVN_BLEND_FUNC_SRC_ALPHA					}, // SRC_COLOR
		{ NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_SRC_COLOR,			NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_SRC_ALPHA		}, // INV_SRC_COLOR
		{ NVNblendFunc::NVN_BLEND_FUNC_SRC_ALPHA,					NVNblendFunc::NVN_BLEND_FUNC_SRC_ALPHA					}, // SRC_ALPHA
		{ NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_SRC_ALPHA,			NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_SRC_ALPHA		}, // INV_SRC_ALPHA
		{ NVNblendFunc::NVN_BLEND_FUNC_DST_ALPHA,					NVNblendFunc::NVN_BLEND_FUNC_DST_ALPHA					}, // DST_ALPHA
		{ NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_DST_ALPHA,			NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_DST_ALPHA		}, // INV_DST_ALPHA
		{ NVNblendFunc::NVN_BLEND_FUNC_DST_COLOR,					NVNblendFunc::NVN_BLEND_FUNC_DST_ALPHA					}, // DST_COLOR
		{ NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_DST_COLOR,			NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_DST_ALPHA		}, // INV_DST_COLOR
		{ NVNblendFunc::NVN_BLEND_FUNC_SRC_ALPHA_SATURATE,			NVNblendFunc::NVN_BLEND_FUNC_ONE						}, // SRC_ALPHA_SAT
		{ NVNblendFunc::NVN_BLEND_FUNC_CONSTANT_ALPHA,				NVNblendFunc::NVN_BLEND_FUNC_CONSTANT_ALPHA				}, // FACTOR
		{ NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_CONSTANT_ALPHA,	NVNblendFunc::NVN_BLEND_FUNC_ONE_MINUS_CONSTANT_ALPHA	}, // INV_FACTOR
	};

	static const NVNblendEquation s_blendEquation[] =
	{
		NVNblendEquation::NVN_BLEND_EQUATION_ADD,
		NVNblendEquation::NVN_BLEND_EQUATION_SUB,
		NVNblendEquation::NVN_BLEND_EQUATION_REVERSE_SUB,
		NVNblendEquation::NVN_BLEND_EQUATION_MIN,
		NVNblendEquation::NVN_BLEND_EQUATION_MAX,
	};

	static const NVNcompareFunc s_cmpFunc[] =
	{
		NVNcompareFunc::NVN_COMPARE_FUNC_ALWAYS, // ignored
		NVNcompareFunc::NVN_COMPARE_FUNC_LESS,
		NVNcompareFunc::NVN_COMPARE_FUNC_LEQUAL,
		NVNcompareFunc::NVN_COMPARE_FUNC_EQUAL,
		NVNcompareFunc::NVN_COMPARE_FUNC_GEQUAL,
		NVNcompareFunc::NVN_COMPARE_FUNC_GREATER,
		NVNcompareFunc::NVN_COMPARE_FUNC_NOTEQUAL,
		NVNcompareFunc::NVN_COMPARE_FUNC_NEVER,
		NVNcompareFunc::NVN_COMPARE_FUNC_ALWAYS,
	};

	static const NVNdepthFunc s_depthFunc[] =
	{
		NVNdepthFunc::NVN_DEPTH_FUNC_ALWAYS, // ignored
		NVNdepthFunc::NVN_DEPTH_FUNC_LESS,
		NVNdepthFunc::NVN_DEPTH_FUNC_LEQUAL,
		NVNdepthFunc::NVN_DEPTH_FUNC_EQUAL,
		NVNdepthFunc::NVN_DEPTH_FUNC_GEQUAL,
		NVNdepthFunc::NVN_DEPTH_FUNC_GREATER,
		NVNdepthFunc::NVN_DEPTH_FUNC_NOTEQUAL,
		NVNdepthFunc::NVN_DEPTH_FUNC_NEVER,
		NVNdepthFunc::NVN_DEPTH_FUNC_ALWAYS,
	};

	static const NVNstencilFunc s_stencilFunc[] =
	{
		NVNstencilFunc::NVN_STENCIL_FUNC_ALWAYS, // ignored
		NVNstencilFunc::NVN_STENCIL_FUNC_LESS,
		NVNstencilFunc::NVN_STENCIL_FUNC_LEQUAL,
		NVNstencilFunc::NVN_STENCIL_FUNC_EQUAL,
		NVNstencilFunc::NVN_STENCIL_FUNC_GEQUAL,
		NVNstencilFunc::NVN_STENCIL_FUNC_GREATER,
		NVNstencilFunc::NVN_STENCIL_FUNC_NOTEQUAL,
		NVNstencilFunc::NVN_STENCIL_FUNC_NEVER,
		NVNstencilFunc::NVN_STENCIL_FUNC_ALWAYS,
	};

	static const NVNstencilOp s_stencilOp[] =
	{
		NVNstencilOp::NVN_STENCIL_OP_ZERO,
		NVNstencilOp::NVN_STENCIL_OP_KEEP,
		NVNstencilOp::NVN_STENCIL_OP_REPLACE,
		NVNstencilOp::NVN_STENCIL_OP_INCR,
		NVNstencilOp::NVN_STENCIL_OP_INCR, // D3D11_STENCIL_OP_INCR_SAT
		NVNstencilOp::NVN_STENCIL_OP_DECR,
		NVNstencilOp::NVN_STENCIL_OP_DECR, // D3D11_STENCIL_OP_DECR_SAT
		NVNstencilOp::NVN_STENCIL_OP_INVERT,
	};

	static const NVNface s_cullMode[] =
	{
		NVNface::NVN_FACE_NONE,
		NVNface::NVN_FACE_BACK,
		NVNface::NVN_FACE_FRONT
	};

	struct TextureFilter
	{
		NVNmagFilter magFilter[3];
		NVNminFilter minFilter[2][3];
	};

	static const TextureFilter s_textureFilter =
	{
		{
			NVN_MAG_FILTER_LINEAR, // min linear
			NVN_MAG_FILTER_NEAREST, // min point
			NVN_MAG_FILTER_LINEAR, // anisotropic
		},
		{
			{ // linear mipmap
				NVN_MIN_FILTER_LINEAR_MIPMAP_LINEAR,
				NVN_MIN_FILTER_NEAREST_MIPMAP_LINEAR,
				NVN_MIN_FILTER_LINEAR_MIPMAP_LINEAR
			},
			{ // point mipmap
				NVN_MIN_FILTER_LINEAR_MIPMAP_NEAREST,
				NVN_MIN_FILTER_NEAREST_MIPMAP_NEAREST,
				NVN_MIN_FILTER_LINEAR_MIPMAP_LINEAR
			}
		}
	};

	static const NVNwrapMode s_textureAddress[] =
	{
		NVN_WRAP_MODE_REPEAT,
		NVN_WRAP_MODE_MIRRORED_REPEAT,
		NVN_WRAP_MODE_CLAMP_TO_EDGE,
		NVN_WRAP_MODE_CLAMP_TO_BORDER
	};

	NVNdevice* g_nvnDevice = NULL;

	//
	//
	//

	struct ContextResources
	{
		Resolution m_resolution;

		TextureNVN m_textures[BGFX_CONFIG_MAX_TEXTURES];
		BufferNVN m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferNVN m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		VertexLayout m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		ShaderNVN m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramNVN m_program[BGFX_CONFIG_MAX_PROGRAMS];
		FrameBufferNVN m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		void* m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];

		uint8_t m_uniformsPredefinedVS[64 << 10];
		uint8_t m_uniformsPredefinedFS[64 << 10];
		UniformRegistry m_uniformReg;
		UniformBufferRegistry m_uniformBuffers;
		TexturesSamplersPool m_textureSamplersPool;
		DoubleBufferedResource<CommandMemoryPool> m_commandMemoryPools;
		std::vector<std::pair<uint64_t, PipelineVboState>> m_vboStateCache;
		std::vector<std::pair<uint32_t, NVNsampler>> m_samplerCache;
		std::vector<std::pair<uint16_t, NVNtextureView>> m_imageCache;

		MemoryPool m_shaderScratch;

		ContextResources()
		{
			memset(m_uniforms, 0, sizeof(m_uniforms));
			memset(m_shaders, 0, sizeof(m_shaders));
		}

		void initPools()
		{
			m_textureSamplersPool.init(g_nvnDevice);
			m_commandMemoryPools.init(g_nvnDevice);

			m_samplerCache.resize(m_textureSamplersPool.m_numSamplers);
			for (auto& it : m_samplerCache)
			{
				it.first = 0;
			}

			m_imageCache.resize(m_textureSamplersPool.m_numTextures);
			for (auto& it : m_imageCache)
			{
				it.first = kInvalidHandle;
				nvnTextureViewSetDefaults(&it.second);
			}

			// give shaders 1MB of extra scratch memory
			uint32_t alignment = 4096; // NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_ALIGNMENT
			uint32_t granularity = 131072; // NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_GRANULARITY
			m_shaderScratch.Init(nullptr, granularity * 8, NVN_MEMORY_POOL_FLAGS_CPU_NO_ACCESS_BIT | NVN_MEMORY_POOL_FLAGS_GPU_CACHED_BIT, g_nvnDevice);
		}

		PipelineVboState* getPipelineVboState(const uint64_t& _key)
		{
			for (auto& it : m_vboStateCache)
			{
				if (it.first == _key)
				{
					return &it.second;
				}
			}

			return nullptr;
		}

		PipelineVboState* createPipelineVboState(const uint64_t& _key)
		{
			m_vboStateCache.push_back(std::pair<uint64_t, PipelineVboState>(_key, {}));
			auto& it = m_vboStateCache.back();
			return &it.second;
		}

		int getTextureId(const uint16_t _texture)
		{
			return _texture + m_textureSamplersPool.m_numReservedTextures;
		}

		int getImageId(const uint16_t _texture, const uint8_t _mip)
		{
			return m_textureSamplersPool.m_numReservedTextures;
		}

		int getSamplerId(const uint32_t _samplerFlags, const float *_rgba)
		{
			int numSamplers = m_samplerCache.size();
			int idx = 0;
			for (idx = 0; idx < numSamplers && m_samplerCache[idx].first; ++idx)
			{
				if (m_samplerCache[idx].first == _samplerFlags)
				{
					return idx + m_textureSamplersPool.m_numReservedSamplers;
				}
			}

			NVNsamplerBuilder builder;
			nvnSamplerBuilderSetDefaults(&builder);
			nvnSamplerBuilderSetDevice(&builder, g_nvnDevice);

			const uint32_t cmpFunc = (_samplerFlags & BGFX_SAMPLER_COMPARE_MASK) >> BGFX_SAMPLER_COMPARE_SHIFT;

			NVNminFilter minFilter = s_textureFilter.minFilter[(_samplerFlags & BGFX_SAMPLER_MIP_MASK) >> BGFX_SAMPLER_MIP_SHIFT][(_samplerFlags & BGFX_SAMPLER_MIN_MASK) >> BGFX_SAMPLER_MIN_SHIFT];
			NVNmagFilter magFilter = s_textureFilter.magFilter[(_samplerFlags & BGFX_SAMPLER_MAG_MASK) >> BGFX_SAMPLER_MAG_SHIFT];

			NVNwrapMode wrapU = s_textureAddress[(_samplerFlags & BGFX_SAMPLER_U_MASK) >> BGFX_SAMPLER_U_SHIFT];
			NVNwrapMode wrapV = s_textureAddress[(_samplerFlags & BGFX_SAMPLER_V_MASK) >> BGFX_SAMPLER_V_SHIFT];
			NVNwrapMode wrapW = s_textureAddress[(_samplerFlags & BGFX_SAMPLER_W_MASK) >> BGFX_SAMPLER_W_SHIFT];

			NVNcompareMode compareMode = (0 == cmpFunc) ? NVN_COMPARE_MODE_NONE : NVN_COMPARE_MODE_COMPARE_R_TO_TEXTURE;
			NVNcompareFunc compareFunc = (0 == cmpFunc) ? NVN_COMPARE_FUNC_ALWAYS : s_cmpFunc[cmpFunc];

			nvnSamplerBuilderSetMinMagFilter(&builder, minFilter, magFilter);
			nvnSamplerBuilderSetMaxAnisotropy(&builder, 1.f);
			nvnSamplerBuilderSetWrapMode(&builder, wrapU, wrapV, wrapW);
			nvnSamplerBuilderSetBorderColor(&builder, _rgba); // this will cache the border color forever and there's no way to change it without building a new sampler
			nvnSamplerBuilderSetCompare(&builder, compareMode, compareFunc);

			m_samplerCache[idx].first = _samplerFlags;
			nvnSamplerInitialize(&m_samplerCache[idx].second, &builder);
			m_textureSamplersPool.set(idx, &m_samplerCache[idx].second);

			return idx + m_textureSamplersPool.m_numReservedSamplers;
		}

		void registerImage(const uint16_t _texture, const uint8_t _mip)
		{
			NVNtexture* tex = &m_textures[_texture].m_ptr;
			NVNtextureView* view = nullptr;

			int numImages = m_imageCache.size();

			int i = 0;
			for (i = 0; i < numImages; ++i)
			{
				auto& it = m_imageCache[i];
				view = &it.second;

				int mip, numLevels;
				nvnTextureViewGetLevels(view, &mip, &numLevels);

				if (it.first == _texture && mip == _mip)
				{
					return; // already registered
				}

				if (it.first == kInvalidHandle)
				{
					it.first = _texture;
					break;
				}
			}

			BX_ASSERT(i < numImages, "Too many images registered.");

			nvnTextureViewSetDefaults(view);
			nvnTextureViewSetLevels(view, _mip, 1);

			m_textureSamplersPool.set(i, tex, view);
		}

		void unregisterImages(const uint16_t _texture)
		{
			auto it = m_imageCache.begin();
			while (it != m_imageCache.end())
			{
				if (it->first == _texture)
				{
					it = m_imageCache.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
	};

	//
	//
	//

	struct Commands
	{
		struct CurrentState
		{
			bool isCompute = false;
			bool wasCompute = false;
			bool programChanged = false;
			uint16_t view = UINT16_MAX;
			uint16_t programIndex = kInvalidHandle;
			uint16_t frameBuffer = kInvalidHandle;
			uint32_t resolutionHeight = 0;
			float depthNear = 0.f;
			float depthFar = 0.f;
			Rect scissor;

			PrimitiveInfo primitiveType;
			ViewState viewState;
			RenderDraw drawState;
			RenderBind bindState;

			CurrentState(Frame* _render)
				: viewState(_render)
			{
				drawState.clear();
				bindState.clear();

				drawState.m_stateFlags = BGFX_STATE_NONE;
				drawState.m_stencil = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

				const uint64_t primType = _render->m_debug & BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
				uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);
				primitiveType = s_primitiveInfo[primIndex];
			}
		};

		CommandListNVN& m_cmdList;
		ContextResources& m_resources;
		CurrentState m_state;

		Frame* m_render;

		Commands(CommandListNVN& cmd, Frame* _render, ContextResources& resources)
			: m_cmdList(cmd)
			, m_state(_render)
			, m_resources(resources)
			, m_render(_render)
		{
			m_state.resolutionHeight = m_resources.m_resolution.height;
			nvnCommandBufferSetShaderScratchMemory(m_cmdList.get(), m_resources.m_shaderScratch.GetMemoryPool(), 0, m_resources.m_shaderScratch.GetSize());
		}

		void setFrameBuffer(uint16_t _count, NVNtexture** _colors, NVNtexture* _depth, NVNtextureView** _colorViews, NVNtextureView* _depthView)
		{
			for (uint16_t i = 0; i < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++i)
			{
				m_cmdList.m_currentColor[i] = (i < _count) ? _colors[i] : nullptr;
			}

			m_cmdList.m_currentDepth = _depth;

			nvnCommandBufferBarrier(m_cmdList.get(), NVN_BARRIER_ORDER_FRAGMENTS_BIT);
			nvnCommandBufferSetRenderTargets(m_cmdList.get(), BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS, m_cmdList.m_currentColor.data(), _colorViews, m_cmdList.m_currentDepth, _depthView);
		}

		bool setView(Frame* _render, uint16_t _view, bool _force, BackBuffer& _backBuffer)
		{
			bool changed = false;

			if (m_state.view != _view || _force)
			{
				FrameBufferHandle fbh = _render->m_view[_view].m_fbh;

				if (fbh.idx != m_state.frameBuffer)
				{
					m_state.frameBuffer = fbh.idx;

					uint16_t count = 0;
					std::array<NVNtexture*, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> targets;
					std::array<NVNtextureView*, BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> views;
					NVNtexture* depth = nullptr;
					NVNtextureView* depthView = nullptr;

					memset(views.data(), 0, sizeof(NVNtextureView*) * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS);

					if (!isValid(fbh))
					{
						count = 1;
						targets[0] = &_backBuffer.m_color->m_ptr;
						views[0] = nullptr;
						depth = &_backBuffer.m_depth->m_ptr;
						depthView = nullptr;

						m_state.resolutionHeight = m_resources.m_resolution.height;
					}
					else
					{
						FrameBufferNVN& fb = m_resources.m_frameBuffers[fbh.idx];

						for (uint8_t i = 0; i < fb.m_numTargets; ++i)
						{
							TextureHandle handle = fb.m_colorTargets[i];
							TextureNVN& tex = m_resources.m_textures[handle.idx];
							targets[i] = &tex.m_ptr;
							views[i] = &fb.m_colorViews[i];
						}

						if (isValid(fb.m_depthTarget))
						{
							TextureNVN& tex = m_resources.m_textures[fb.m_depthTarget.idx];
							depth = &tex.m_ptr;
							depthView = &fb.m_depthView;
						}

						count = fb.m_numTargets;

						m_state.resolutionHeight = fb.m_height;
					}

					setFrameBuffer(count, targets.data(), depth, views.data(), depthView);
				}

				m_state.view = _view;

				changed = true;
			}

			return changed;
		}

		void setViewport(const Rect& _vp, const Rect& _scissor, float _near, float _far)
		{
			std::array<float, 4 * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> viewportRects;
			std::array<int, 4 * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> scissorRects;

			int numTargets = 1;
			if (m_state.frameBuffer != kInvalidHandle)
			{
				FrameBufferNVN& fb = m_resources.m_frameBuffers[m_state.frameBuffer];
				numTargets = fb.m_numTargets;
			}

			if (memcmp(&m_state.viewState.m_rect, &_vp, sizeof(Rect)) != 0)
			{
				m_state.viewState.m_rect = _vp;

				for (int i = 0; i < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++i)
				{
					int index = i * 4;
					viewportRects[index + 0] = _vp.m_x;
					viewportRects[index + 1] = m_state.resolutionHeight - _vp.m_height - _vp.m_y;
					viewportRects[index + 2] = _vp.m_width;
					viewportRects[index + 3] = _vp.m_height;
				}

				nvnCommandBufferSetViewports(m_cmdList.get(), 0, numTargets, viewportRects.data());
			}

			Rect scissor = _scissor.isZeroArea() ? _vp : _scissor;
			if (memcmp(&m_state.scissor, &scissor, sizeof(Rect)) != 0)
			{
				m_state.scissor = scissor;

				for (int i = 0; i < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++i)
				{
					int index = i * 4;
					scissorRects[index + 0] = scissor.m_x;
					scissorRects[index + 1] = m_state.resolutionHeight - scissor.m_height - scissor.m_y;
					scissorRects[index + 2] = scissor.m_width;
					scissorRects[index + 3] = scissor.m_height;
				}

				nvnCommandBufferSetScissors(m_cmdList.get(), 0, numTargets, scissorRects.data());
			}

			if (m_state.depthNear != _near || m_state.depthFar != _far)
			{
				m_state.depthNear = _near;
				m_state.depthFar = _far;
				nvnCommandBufferSetDepthRange(m_cmdList.get(), _near, _far);
			}
		}

		void clearViewport(const Clear& _clear, const float _palette[][4])
		{
			if (BGFX_CLEAR_NONE != (_clear.m_flags & BGFX_CLEAR_MASK))
			{
				if (_clear.m_flags & BGFX_CLEAR_COLOR)
				{
					float rgba[4] =
					{
						_clear.m_index[0] * 1.0f / 255.0f,
						_clear.m_index[1] * 1.0f / 255.0f,
						_clear.m_index[2] * 1.0f / 255.0f,
						_clear.m_index[3] * 1.0f / 255.0f
					};

					for (int i = 0; i < m_cmdList.m_currentColor.size(); i++)
					{
						if (m_cmdList.m_currentColor[i] != nullptr)
						{
							if (_clear.m_flags & BGFX_CLEAR_COLOR_USE_PALETTE)
							{
								int index = _clear.m_index[i];
								rgba[0] = _palette[index][0];
								rgba[1] = _palette[index][1];
								rgba[2] = _palette[index][2];
								rgba[3] = _palette[index][3];
							}

							nvnCommandBufferClearColor(m_cmdList.get(), i, rgba, NVN_CLEAR_COLOR_MASK_RGBA);
						}
					}
				}

				if (_clear.m_flags & (BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL))
				{
					if (m_cmdList.m_currentDepth != nullptr)
					{
						nvnCommandBufferClearDepthStencil(m_cmdList.get(), _clear.m_depth, _clear.m_flags & BGFX_CLEAR_DEPTH, _clear.m_stencil, (_clear.m_flags & BGFX_CLEAR_STENCIL) ? 0xff : 0);
					}
				}
			}
		}

		void processBlits(Frame* _render)
		{
			BlitState bs(_render);
			while (bs.hasItem(m_state.view))
			{
				const BlitItem& blit = bs.advance();

				const TextureNVN& src = m_resources.m_textures[blit.m_src.idx];
				const TextureNVN& dst = m_resources.m_textures[blit.m_dst.idx];

				NVNtextureView srcView;
				nvnTextureViewSetDefaults(&srcView);
				nvnTextureViewSetLevels(&srcView, blit.m_srcMip, 1);

				NVNtextureView dstView;
				nvnTextureViewSetDefaults(&dstView);
				nvnTextureViewSetLevels(&dstView, blit.m_dstMip, 1);

				NVNcopyRegion srcRegion;
				srcRegion.xoffset = blit.m_srcX;
				srcRegion.yoffset = blit.m_srcY;
				srcRegion.zoffset = 0;
				srcRegion.width = blit.m_width;
				srcRegion.height = blit.m_height;
				srcRegion.depth = 1;

				NVNcopyRegion dstRegion;
				dstRegion.xoffset = blit.m_dstX;
				dstRegion.yoffset = blit.m_dstY;
				dstRegion.zoffset = 0;
				dstRegion.width = blit.m_width;
				dstRegion.height = blit.m_height;
				dstRegion.depth = 1;

				if (src.m_type == TextureNVN::Enum::Texture3D)
				{
					srcRegion.zoffset = blit.m_srcZ;
					srcRegion.depth = blit.m_depth;
					dstRegion.zoffset = blit.m_dstZ;
					dstRegion.depth = blit.m_depth;
				}
				else
				{
					nvnTextureViewSetLayers(&srcView, blit.m_srcZ, 1);
					nvnTextureViewSetLayers(&dstView, blit.m_dstZ, 1);
				}

				nvnCommandBufferCopyTextureToTexture(m_cmdList.get(), &src.m_ptr, &srcView, &srcRegion, &dst.m_ptr, &dstView, &dstRegion, 0);
			}
		}

		void _setPolygonState(uint64_t _state)
		{
			bool wireframe = false;
			uint32_t cull = (_state & BGFX_STATE_CULL_MASK) >> BGFX_STATE_CULL_SHIFT;

			NVNpolygonState polygonState;
			nvnPolygonStateSetDefaults(&polygonState);
			nvnPolygonStateSetPolygonMode(&polygonState, wireframe ? NVNpolygonMode::NVN_POLYGON_MODE_LINE : NVNpolygonMode::NVN_POLYGON_MODE_FILL);
			nvnPolygonStateSetCullFace(&polygonState, s_cullMode[cull]);
			nvnCommandBufferBindPolygonState(m_cmdList.get(), &polygonState);
		}

		void _setBlendState(uint64_t _state, uint32_t _rgba = 0)
		{
			//_state &= BGFX_NVN_BLEND_STATE_MASK;

			if (!!(BGFX_STATE_BLEND_ALPHA_TO_COVERAGE & _state))
			{
				BX_ASSERT(false, "Alpha To Coverage not implemented");
			}

			const bool independentBlendEnable = !!(BGFX_STATE_BLEND_INDEPENDENT & _state);

			NVNblendState blendState;
			NVNcolorState colorState;
			NVNchannelMaskState channelState;
			nvnBlendStateSetDefaults(&blendState);
			nvnColorStateSetDefaults(&colorState);
			nvnChannelMaskStateSetDefaults(&channelState);

			const uint32_t blend = uint32_t((_state & BGFX_STATE_BLEND_MASK) >> BGFX_STATE_BLEND_SHIFT);
			const uint32_t equation = uint32_t((_state & BGFX_STATE_BLEND_EQUATION_MASK) >> BGFX_STATE_BLEND_EQUATION_SHIFT);

			const uint32_t srcRGB = (blend) & 0xf;
			const uint32_t dstRGB = (blend >> 4) & 0xf;
			const uint32_t srcA = (blend >> 8) & 0xf;
			const uint32_t dstA = (blend >> 12) & 0xf;

			const uint32_t equRGB = (equation) & 0x7;
			const uint32_t equA = (equation >> 3) & 0x7;

			NVNboolean writeR = _state & BGFX_STATE_WRITE_R;
			NVNboolean writeG = _state & BGFX_STATE_WRITE_G;
			NVNboolean writeB = _state & BGFX_STATE_WRITE_B;
			NVNboolean writeA = _state & BGFX_STATE_WRITE_A;

			if (independentBlendEnable)
			{
				for (uint32_t ii = 1, rgba = _rgba; ii < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++ii, rgba >>= 11)
				{
					const uint32_t src = (rgba) & 0xf;
					const uint32_t dst = (rgba >> 4) & 0xf;
					const uint32_t equ = (rgba >> 8) & 0x7;

					nvnChannelMaskStateSetChannelMask(&channelState, ii, writeR, writeG, writeB, writeA);
					nvnColorStateSetBlendEnable(&colorState, ii, 0 != (rgba & 0x7ff));

					nvnBlendStateSetBlendTarget(&blendState, ii);
					nvnBlendStateSetBlendFunc(&blendState, s_blendFactor[src][0], s_blendFactor[dst][0], s_blendFactor[src][1], s_blendFactor[dst][1]);
					nvnBlendStateSetBlendEquation(&blendState, s_blendEquation[equ], s_blendEquation[equ]);

					nvnCommandBufferBindBlendState(m_cmdList.get(), &blendState);
				}
			}
			else
			{
				nvnBlendStateSetBlendFunc(&blendState, s_blendFactor[srcRGB][0], s_blendFactor[dstRGB][0], s_blendFactor[srcA][1], s_blendFactor[dstA][1]);
				nvnBlendStateSetBlendEquation(&blendState, s_blendEquation[equRGB], s_blendEquation[equA]);

				for (int ii = 0; ii < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ii++)
				{
					nvnColorStateSetBlendEnable(&colorState, ii, !!(BGFX_STATE_BLEND_MASK & _state));
					nvnChannelMaskStateSetChannelMask(&channelState, ii, writeR, writeG, writeB, writeA);
					nvnBlendStateSetBlendTarget(&blendState, ii);

					nvnCommandBufferBindBlendState(m_cmdList.get(), &blendState);
				}
			}

			nvnCommandBufferBindColorState(m_cmdList.get(), &colorState);
			nvnCommandBufferBindChannelMaskState(m_cmdList.get(), &channelState);
		}

		void _setDepthStencilState(uint64_t _state, uint64_t _stencil)
		{
			NVNdepthStencilState depthStencilState;
			nvnDepthStencilStateSetDefaults(&depthStencilState);

			uint32_t func = (_state & BGFX_STATE_DEPTH_TEST_MASK) >> BGFX_STATE_DEPTH_TEST_SHIFT;

			nvnDepthStencilStateSetDepthTestEnable(&depthStencilState, 0 != func);
			nvnDepthStencilStateSetDepthWriteEnable(&depthStencilState, !!(BGFX_STATE_WRITE_Z & _state));
			nvnDepthStencilStateSetDepthFunc(&depthStencilState, s_depthFunc[func]);
			nvnDepthStencilStateSetStencilTestEnable(&depthStencilState, _stencil != 0);

			if (_stencil != 0)
			{
				uint32_t fstencil = unpackStencil(0, _stencil);
				uint32_t bstencil = unpackStencil(1, _stencil);
				uint32_t frontAndBack = bstencil != BGFX_STENCIL_NONE && bstencil != fstencil;
				bstencil = frontAndBack ? bstencil : fstencil;

				uint32_t ref = (fstencil & BGFX_STENCIL_FUNC_REF_MASK) >> BGFX_STENCIL_FUNC_REF_SHIFT;

				nvnCommandBufferSetStencilRef(m_cmdList.get(), NVNface::NVN_FACE_FRONT_AND_BACK, ref);
				nvnCommandBufferSetStencilMask(m_cmdList.get(), NVNface::NVN_FACE_FRONT_AND_BACK, (fstencil & BGFX_STENCIL_FUNC_RMASK_MASK) >> BGFX_STENCIL_FUNC_RMASK_SHIFT);

				nvnDepthStencilStateSetStencilOp(
					&depthStencilState,
					NVNface::NVN_FACE_FRONT,
					s_stencilOp[(fstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT],
					s_stencilOp[(fstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT],
					s_stencilOp[(fstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT]
				);
				nvnDepthStencilStateSetStencilFunc(
					&depthStencilState,
					NVNface::NVN_FACE_FRONT,
					s_stencilFunc[(fstencil & BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT]
				);

				nvnDepthStencilStateSetStencilOp(
					&depthStencilState,
					NVNface::NVN_FACE_BACK,
					s_stencilOp[(bstencil & BGFX_STENCIL_OP_FAIL_S_MASK) >> BGFX_STENCIL_OP_FAIL_S_SHIFT],
					s_stencilOp[(bstencil & BGFX_STENCIL_OP_FAIL_Z_MASK) >> BGFX_STENCIL_OP_FAIL_Z_SHIFT],
					s_stencilOp[(bstencil & BGFX_STENCIL_OP_PASS_Z_MASK) >> BGFX_STENCIL_OP_PASS_Z_SHIFT]
				);
				nvnDepthStencilStateSetStencilFunc(
					&depthStencilState,
					NVNface::NVN_FACE_BACK,
					s_stencilFunc[(bstencil & BGFX_STENCIL_TEST_MASK) >> BGFX_STENCIL_TEST_SHIFT]
				);
			}

			nvnCommandBufferBindDepthStencilState(m_cmdList.get(), &depthStencilState);
		}

		void setRasterState(const RenderDraw& _draw)
		{
			uint64_t state = _draw.m_stateFlags;
			uint64_t stencil = _draw.m_stencil;

			bool stateChanged = m_state.drawState.m_stateFlags != state;
			bool stencilChanged = m_state.drawState.m_stencil != stencil;

			if (stateChanged)
			{
				_setPolygonState(state);
				_setBlendState(state);

				const uint64_t pt = state & BGFX_STATE_PT_MASK;
				m_state.primitiveType = s_primitiveInfo[(pt >> BGFX_STATE_PT_SHIFT)];
			}

			if (stateChanged || stencilChanged)
			{
				_setDepthStencilState(state, stencil);
			}

			m_state.drawState.m_stateFlags = state;
			m_state.drawState.m_stencil = stencil;
		}

		void bindProgram(const ProgramHandle& handle)
		{
			m_state.programChanged = (handle.idx != m_state.programIndex);
			if (m_state.programChanged)
			{
				m_state.programIndex = handle.idx;

				if (m_state.programIndex != kInvalidHandle)
				{
					ProgramNVN& program = m_resources.m_program[m_state.programIndex];
					nvnCommandBufferBindProgram(m_cmdList.get(), &program.m_program, program.m_Stages);
				}
				else
				{
					nvnCommandBufferBindProgram(m_cmdList.get(), nullptr, NVN_SHADER_STAGE_ALL_GRAPHICS_BITS | NVN_SHADER_STAGE_COMPUTE_BIT);
				}
			}
		}

		void bindUniformBuffers(ProgramNVN& _program)
		{
			const ShaderNVN* shaders[2] =
			{
				_program.m_vsh,
				_program.m_fsh
			};

			NVNshaderStage stages[2] =
			{
				m_state.isCompute ? NVN_SHADER_STAGE_COMPUTE : NVN_SHADER_STAGE_VERTEX,
				NVN_SHADER_STAGE_FRAGMENT
			};

			for (int i = 0; i < 2; ++i)
			{
				if (shaders[i] == nullptr)
				{
					continue;
				}

				int curBinding = 0;
				for (uint32_t index : shaders[i]->m_constantBuffers)
				{
					if (index == UniformBufferRegistry::InvalidEntry)
					{
						continue;
					}

					ShaderUniformBuffer& ub = m_resources.m_uniformBuffers.get(index);
					ub.update(m_cmdList.get());
					nvnCommandBufferBindUniformBuffer(m_cmdList.get(), stages[i], curBinding, ub.m_buffer->m_gpuAddress, ub.m_size);
					curBinding++;
				}
			}
		}

		void _bindImage(int _idx, const Binding& _bind)
		{
			int imageIndex = m_resources.getImageId(_bind.m_idx, _bind.m_mip);
			NVNimageHandle imageHandle = nvnDeviceGetImageHandle(g_nvnDevice, imageIndex);

			if (m_state.isCompute)
			{
				nvnCommandBufferBindImage(m_cmdList.get(), NVN_SHADER_STAGE_COMPUTE, _idx, imageHandle);
			}
			else
			{
				nvnCommandBufferBindImage(m_cmdList.get(), NVN_SHADER_STAGE_VERTEX, _idx, imageHandle); // bind in the vertex shader as well?
				nvnCommandBufferBindImage(m_cmdList.get(), NVN_SHADER_STAGE_FRAGMENT, _idx, imageHandle);
			}
		}

		void _bindTexture(int _idx, const Binding& _bind, const float _palette[][4])
		{
			TextureNVN& tex = m_resources.m_textures[_bind.m_idx];

			uint32_t samplerFlags = (0 == (BGFX_SAMPLER_INTERNAL_DEFAULT & _bind.m_samplerFlags)) ? _bind.m_samplerFlags : tex.m_flags;

			uint32_t index = (samplerFlags & BGFX_SAMPLER_BORDER_COLOR_MASK) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;

			int textureIndex = m_resources.getTextureId(_bind.m_idx);
			int samplerIndex = m_resources.getSamplerId(samplerFlags, _palette[index]);

			NVNtextureHandle textureHandle = nvnDeviceGetTextureHandle(g_nvnDevice, textureIndex, samplerIndex);

			if (m_state.isCompute)
			{
				nvnCommandBufferBindTexture(m_cmdList.get(), NVN_SHADER_STAGE_COMPUTE, _idx, textureHandle);
			}
			else
			{
				nvnCommandBufferBindTexture(m_cmdList.get(), NVN_SHADER_STAGE_VERTEX, _idx, textureHandle); // bind in the vertex shader as well?
				nvnCommandBufferBindTexture(m_cmdList.get(), NVN_SHADER_STAGE_FRAGMENT, _idx, textureHandle);
			}
		}

		void _bindBuffer(int _idx, const Binding& _bind)
		{
			NVNbufferAddress addr = 0;
			size_t size = 0;

			switch (_bind.m_type)
			{
			case Binding::IndexBuffer:
				addr = m_resources.m_indexBuffers[_bind.m_idx].m_gpuAddress;
				size = m_resources.m_indexBuffers[_bind.m_idx].m_size;
				break;
			case Binding::VertexBuffer:
				addr = m_resources.m_vertexBuffers[_bind.m_idx].m_gpuAddress;
				size = m_resources.m_vertexBuffers[_bind.m_idx].m_size;
				break;
			default:
				break;
			}

			BX_ASSERT(size > 0, "Invalid buffer binding.");

			if (m_state.isCompute)
			{
				nvnCommandBufferBindStorageBuffer(m_cmdList.get(), NVN_SHADER_STAGE_COMPUTE, _idx, addr, size);
			}
			else
			{
				nvnCommandBufferBindStorageBuffer(m_cmdList.get(), NVN_SHADER_STAGE_VERTEX, _idx, addr, size);
				nvnCommandBufferBindStorageBuffer(m_cmdList.get(), NVN_SHADER_STAGE_FRAGMENT, _idx, addr, size);
			}
		}

		void bindSamplers(const RenderBind& _bindings, const float _palette[][4])
		{
			for (int i = 0; i < BGFX_CONFIG_MAX_TEXTURE_SAMPLERS; ++i)
			{
				const Binding& bind = _bindings.m_bind[i];
				if (bind.m_idx != kInvalidHandle)
				{
					switch (bind.m_type)
					{
					case Binding::Image:
						_bindImage(i, bind);
						break;
					case Binding::Texture:
						_bindTexture(i, bind, _palette);
						break;
					case Binding::IndexBuffer:
					case Binding::VertexBuffer:
						_bindBuffer(i, bind);
						break;
					default:
						break;
					}
				}
			}
		}

		void setInputLayout(const uint8_t _numStreams, const VertexLayout** _layouts, const uint32_t _numInstanceData)
		{
			const ProgramNVN& program = m_resources.m_program[m_state.programIndex];

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_numInstanceData);
			for (uint8_t stream = 0; stream < _numStreams; ++stream)
			{
				murmur.add(_layouts[stream]->m_hash);
			}

			uint64_t layoutHash = (uint64_t(program.m_vsh->m_hash) << 32) | murmur.end();

			PipelineVboState* vboState = m_resources.getPipelineVboState(layoutHash);
			if (vboState == nullptr)
			{
				// create empty vbo state
				vboState = m_resources.createPipelineVboState(layoutHash);

				struct PipelineVboBindPoint
				{
					bool m_isSet = false;
					NVNformat m_format = NVNformat::NVN_FORMAT_NONE;
					uint8_t m_streamIndex = 0;
					uint16_t m_offset = 0;
					uint16_t m_stride = 0;
				};

				std::array<PipelineVboBindPoint, PipelineVboState::MaxAttributes> vboBindings;

				// populate vbo state
				uint16_t attrMask[Attrib::Count];
				uint8_t attrRemap[Attrib::Count];
				memcpy(attrMask, program.m_vsh->m_attrMask, sizeof(attrMask));
				memcpy(attrRemap, program.m_vsh->m_attrRemap, sizeof(attrRemap));

				for (uint8_t stream = 0; stream < _numStreams; ++stream)
				{
					VertexLayout layout;
					memcpy(&layout, _layouts[stream], sizeof(VertexLayout));

					const bool last = (stream == _numStreams - 1);

					uint8_t currentBindingIndex = 0;

					for (uint32_t attr = 0; attr < Attrib::Count; ++attr)
					{
						uint16_t mask = attrMask[attr];
						uint16_t attribute = (layout.m_attributes[attr] & mask);

						if (attribute == 0 || attribute == UINT16_MAX)
						{
							layout.m_attributes[attr] = last ? ~attribute : UINT16_MAX;
						}

						if (layout.m_attributes[attr] != UINT16_MAX && layout.m_attributes[attr] != 0)
						{
							if (currentBindingIndex >= PipelineVboState::MaxAttributes)
							{
								BX_ASSERT(false, "Exceeded the maximum number of vertex attributes (16)");
								continue;
							}

							uint8_t num;
							AttribType::Enum type;
							bool normalized;
							bool asInt;
							layout.decode(Attrib::Enum(attr), num, type, normalized, asInt);

							const uint8_t remapindex = attrRemap[attr];

							PipelineVboBindPoint& currentBinding = vboBindings[remapindex];

							currentBinding.m_isSet = true;
							currentBinding.m_format = s_attribType[type][num - 1][normalized];
							currentBinding.m_offset = layout.m_offset[attr];
							currentBinding.m_streamIndex = stream;
							currentBinding.m_stride = layout.m_stride;

							currentBindingIndex++;
						}
					}

					NVNvertexStreamState& streamState = vboState->m_streamStates[vboState->m_numStreams];
					nvnVertexStreamStateSetDefaults(&streamState);
					nvnVertexStreamStateSetStride(&streamState, layout.m_stride);
					vboState->m_numStreams++;
				}

				for (uint8_t bindingIndex = 0; bindingIndex < vboBindings.size(); bindingIndex++)
				{
					const PipelineVboBindPoint& currentBinding = vboBindings[bindingIndex];

					const bool isSet = currentBinding.m_isSet;

					NVNvertexAttribState& vaState = vboState->m_attribStates[vboState->m_numAttributes];
					nvnVertexAttribStateSetDefaults(&vaState);

					if (isSet)
					{
						nvnVertexAttribStateSetStreamIndex(&vaState, currentBinding.m_streamIndex);
						nvnVertexAttribStateSetFormat(&vaState, currentBinding.m_format, currentBinding.m_offset);
						vboState->m_numAttributes++;
					}
				}

				if (_numInstanceData > 0)
				{
					for (uint32_t inst = 0; inst < _numInstanceData; ++inst)
					{
						NVNvertexAttribState& vaState = vboState->m_attribStates[vboState->m_numAttributes];
						nvnVertexAttribStateSetDefaults(&vaState);
						nvnVertexAttribStateSetStreamIndex(&vaState, _numStreams);
						nvnVertexAttribStateSetFormat(&vaState, NVN_FORMAT_RGBA32F, inst * 16);
						vboState->m_numAttributes++;
					}

					NVNvertexStreamState& streamState = vboState->m_streamStates[vboState->m_numStreams];
					nvnVertexStreamStateSetDefaults(&streamState);
					nvnVertexStreamStateSetStride(&streamState, _numInstanceData * 16);
					nvnVertexStreamStateSetDivisor(&streamState, 1);
					vboState->m_numStreams++;
				}
			}

			BX_ASSERT(vboState != nullptr, "Invalid vbo state.");

			nvnCommandBufferBindVertexStreamState(m_cmdList.get(), vboState->m_numStreams, vboState->m_streamStates);
			nvnCommandBufferBindVertexAttribState(m_cmdList.get(), vboState->m_numAttributes, vboState->m_attribStates);
		}

		void bindVertexBuffers(const RenderDraw& _draw)
		{
			bool vertexStreamChanged = hasVertexStreamChanged(m_state.drawState, _draw);
			if (vertexStreamChanged)
			{
				m_state.drawState.m_streamMask = _draw.m_streamMask;
				m_state.drawState.m_instanceDataBuffer.idx = _draw.m_instanceDataBuffer.idx;
				m_state.drawState.m_instanceDataOffset = _draw.m_instanceDataOffset;
				m_state.drawState.m_instanceDataStride = _draw.m_instanceDataStride;

				NVNbufferRange buffers[BGFX_CONFIG_MAX_VERTEX_STREAMS + 1];
				const VertexLayout* layouts[BGFX_CONFIG_MAX_VERTEX_STREAMS];

				// BBI-TODO: (tstump 3) validate that BGFX_CONFIG_MAX_VERTEX_STREAMS < max number of NVN vertex streams (queried from the driver with NVN_DEVICE_INFO_VERTEX_BUFFER_BINDINGS)
				//                      needs to be less than since 1 stream is reserved for instance data
				BX_STATIC_ASSERT(BX_COUNTOF(buffers) <= 16); // 16 is the max number of vertex buffer bindings according to the docs, good enough for now

				memset(buffers, 0, sizeof(buffers));

				uint32_t numVertices = _draw.m_numVertices;
				uint8_t numStreams = 0;

				if (UINT8_MAX != _draw.m_streamMask)
				{
					uint32_t idx = 0;
					for (uint32_t streamMask = _draw.m_streamMask; streamMask != 0; streamMask >>= 1)
					{
						// jump to first set bit
						uint32_t ntz = bx::uint32_cnttz(streamMask);
						streamMask >>= ntz;
						idx += ntz;

						m_state.drawState.m_stream[idx].m_layoutHandle = _draw.m_stream[idx].m_layoutHandle;
						m_state.drawState.m_stream[idx].m_handle = _draw.m_stream[idx].m_handle;
						m_state.drawState.m_stream[idx].m_startVertex = _draw.m_stream[idx].m_startVertex;

						const uint16_t handle = _draw.m_stream[idx].m_handle.idx;
						const VertexBufferNVN& vb = m_resources.m_vertexBuffers[handle];
						const uint16_t layout = isValid(_draw.m_stream[idx].m_layoutHandle) ? _draw.m_stream[idx].m_layoutHandle.idx : vb.m_layoutHandle.idx;
						const VertexLayout& vertexLayout = m_resources.m_vertexLayouts[layout];
						const uint32_t stride = vertexLayout.m_stride;
						uint32_t offset = _draw.m_stream[idx].m_startVertex * stride;

						numVertices = bx::uint32_min(UINT32_MAX == _draw.m_numVertices ? (vb.m_size / stride) : _draw.m_numVertices, numVertices);

						buffers[numStreams] = { vb.m_gpuAddress + offset, numVertices * stride };
						layouts[numStreams] = &vertexLayout;

						idx++;
						numStreams++;
					}
				}

				m_state.drawState.m_numVertices = numVertices;

				uint32_t numInstanceData = 0;
				if (isValid(_draw.m_instanceDataBuffer))
				{
					const VertexBufferNVN& inst = m_resources.m_vertexBuffers[_draw.m_instanceDataBuffer.idx];
					const uint32_t instCount = _draw.m_numInstances;
					const uint32_t instStride = _draw.m_instanceDataStride;
					const uint32_t instOffset = _draw.m_instanceDataOffset;
					numInstanceData = instStride / 16; // determine the number of texcoords to pass instance data in (always vec4, so 16 bytes)
					buffers[numStreams] = { inst.m_gpuAddress + instOffset, instStride * instCount };
				}

				// this will set the current buffers and clear unused ones
				nvnCommandBufferBindVertexBuffers(m_cmdList.get(), 0, BGFX_CONFIG_MAX_VERTEX_STREAMS + 1, buffers);
				setInputLayout(numStreams, layouts, numInstanceData);
			}
		}

		void bindIndexBuffer(const RenderDraw& _draw)
		{
			if (m_state.drawState.m_indexBuffer.idx != _draw.m_indexBuffer.idx)
			{
				m_state.drawState.m_indexBuffer = _draw.m_indexBuffer;

				uint16_t handle = _draw.m_indexBuffer.idx;
				if (kInvalidHandle != handle)
				{
					const BufferNVN& ib = m_resources.m_indexBuffers[handle];
					m_cmdList.m_currentIndexBufferIndexType = (ib.m_flags & BGFX_BUFFER_INDEX32) ? NVNindexType::NVN_INDEX_TYPE_UNSIGNED_INT : NVNindexType::NVN_INDEX_TYPE_UNSIGNED_SHORT;
					m_cmdList.m_currentIndexBufferAddress = ib.m_gpuAddress;
				}
				else
				{
					m_cmdList.m_currentIndexBufferIndexType = NVNindexType::NVN_INDEX_TYPE_LARGE;
					m_cmdList.m_currentIndexBufferAddress = 0;
				}
			}
		}

		void draw(const RenderDraw& _draw)
		{
			if (m_state.drawState.m_streamMask != 0)
			{
				NVNdrawPrimitive prim = m_state.primitiveType.m_type;
				uint32_t numInstances = _draw.m_numInstances;
				uint32_t numVertices = m_state.drawState.m_numVertices;

				if (isValid(_draw.m_indexBuffer))
				{
					const BufferNVN& ib = m_resources.m_indexBuffers[_draw.m_indexBuffer.idx];

					uint32_t numIndices = _draw.m_numIndices;
					uint32_t startIndex = _draw.m_startIndex;
					const uint32_t indexSize = 0 == (ib.m_flags & BGFX_BUFFER_INDEX32) ? 2 : 4;

					if (numIndices == UINT32_MAX)
					{
						numIndices = ib.m_size / indexSize;
						startIndex = 0;
					}

					NVNindexType indexType = m_cmdList.m_currentIndexBufferIndexType;
					NVNbufferAddress indexAddr = m_cmdList.m_currentIndexBufferAddress + (startIndex * indexSize);

					if (isValid(_draw.m_indirectBuffer))
					{
						NVNbufferAddress indirectAddr = m_resources.m_vertexBuffers[_draw.m_indirectBuffer.idx].m_gpuAddress + (_draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
						nvnCommandBufferBarrier(m_cmdList.get(), NVN_BARRIER_ORDER_INDIRECT_DATA_BIT);
						nvnCommandBufferDrawElementsIndirect(m_cmdList.get(), prim, indexType, indexAddr, indirectAddr);
					}
					else
					{
						nvnCommandBufferDrawElementsInstanced(m_cmdList.get(), prim, indexType, numIndices, indexAddr, 0, 0, numInstances);
					}
				}
				else
				{
					if (isValid(_draw.m_indirectBuffer))
					{
						NVNbufferAddress indirectAddr = m_resources.m_vertexBuffers[_draw.m_indirectBuffer.idx].m_gpuAddress + (_draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
						nvnCommandBufferBarrier(m_cmdList.get(), NVN_BARRIER_ORDER_INDIRECT_DATA_BIT);
						nvnCommandBufferDrawArraysIndirect(m_cmdList.get(), prim, indirectAddr);
					}
					else
					{
						nvnCommandBufferDrawArraysInstanced(m_cmdList.get(), prim, 0, numVertices, 0, numInstances);
					}
				}
			}
		}

		void dispatch(const RenderCompute& _compute)
		{
			if (isValid(_compute.m_indirectBuffer))
			{
				NVNbufferAddress indirectAddr = m_resources.m_vertexBuffers[_compute.m_indirectBuffer.idx].m_gpuAddress + (_compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
				nvnCommandBufferBarrier(m_cmdList.get(), NVN_BARRIER_ORDER_INDIRECT_DATA_BIT);
				nvnCommandBufferDispatchComputeIndirect(m_cmdList.get(), indirectAddr);
			}
			else
			{
				nvnCommandBufferDispatchCompute(m_cmdList.get(), _compute.m_numX, _compute.m_numY, _compute.m_numZ);
			}
		}
	};

	//
	// RendererContextNVN
	//

	struct RendererContextNVN : public RendererContextI
	{
		struct DeleteOperation
		{
			uint8_t m_count = 3;
			CopyOperation::Data* m_data;
		};

		NVNnativeWindow m_Hwnd = nullptr;

		PFNNVNBOOTSTRAPLOADERPROC m_nvnLoader = nullptr;

		NVNdevice m_Device;
		nn::vi::Display* m_pDisplay = nullptr;
		nn::vi::Layer* m_pLayer = nullptr;

		int m_CommandBufferCommandAlignment = 0;
		int m_CommandBufferControlAlignment = 0;
		int m_maxAnisotropy = 1;
		int m_UniformBufferAlignment = 0;

		ContextResources m_resources;

		SwapChainNVN m_SwapChain;
		CommandQueueNVN m_Queue;
		Commands* m_currentCommands = nullptr;

		NVNsync* m_PreviousFrameSync = nullptr; // BBI-TODO: (tstump 1) change this from previous frame to array to we can do triple buffering
		uint64_t m_SubmitCounter = 0;

		std::vector<CopyOperation> m_copyOperations;
		std::vector<DeleteOperation> m_deleteOperations;

		RendererContextNVN()
		{
			// Pretend all features are available.
			g_caps.supported = 0
				| BGFX_CAPS_ALPHA_TO_COVERAGE
				| BGFX_CAPS_BLEND_INDEPENDENT
				| BGFX_CAPS_COMPUTE
				| BGFX_CAPS_CONSERVATIVE_RASTER
				| BGFX_CAPS_DRAW_INDIRECT
				| BGFX_CAPS_FRAGMENT_DEPTH
				| BGFX_CAPS_IMAGE_RW
				| BGFX_CAPS_INDEX32
				| BGFX_CAPS_INSTANCING
				| BGFX_CAPS_OCCLUSION_QUERY
				| BGFX_CAPS_TEXTURE_2D_ARRAY
				| BGFX_CAPS_TEXTURE_3D
				| BGFX_CAPS_TEXTURE_BLIT
				| BGFX_CAPS_TEXTURE_COMPARE_ALL
				| BGFX_CAPS_TEXTURE_CUBE_ARRAY
				| BGFX_CAPS_TEXTURE_READ_BACK
				| BGFX_CAPS_VERTEX_ATTRIB_HALF
				| BGFX_CAPS_VERTEX_ATTRIB_UINT10
				| BGFX_CAPS_VERTEX_ID
				//| BGFX_CAPS_VIEWPORT_LAYER_ARRAY
				;

			// Pretend all features are available for all texture formats.
			for (uint32_t formatIdx = 0; formatIdx < TextureFormat::Count; ++formatIdx)
			{
				uint16_t caps = TextureNVN::getCaps((TextureFormat::Enum)formatIdx);
				if (caps)
				{
					g_caps.formats[formatIdx] = TextureNVN::getCaps((TextureFormat::Enum)formatIdx);
				}
			}

			// Pretend we have no limits
			g_caps.limits.maxTextureSize     = 16384;
			g_caps.limits.maxTextureLayers   = 2048;
			g_caps.limits.maxComputeBindings = g_caps.limits.maxTextureSamplers;
			g_caps.limits.maxFBAttachments   = BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS;
			g_caps.limits.maxVertexStreams   = BGFX_CONFIG_MAX_VERTEX_STREAMS;
			g_caps.homogeneousDepth          = true;
			g_caps.originBottomLeft          = true;
		}

		~RendererContextNVN()
		{
		}

		RendererType::Enum getRendererType() const override
		{
			return RendererType::Nvn;
		}

		const char* getRendererName() const override
		{
			return BGFX_RENDERER_NVN_NAME;
		}

		// NVN on NX
		bool nvnInit()
		{
			BX_ASSERT(m_Hwnd != nullptr, "No native window passed at initialization");

			pfnc_nvnDeviceGetProcAddress = (PFNNVNDEVICEGETPROCADDRESSPROC)(*nvnBootstrapLoader)("nvnDeviceGetProcAddress");
			nvnLoadCProcs(NULL, pfnc_nvnDeviceGetProcAddress);

			return true;
		}

		void nvnShutdown()
		{

		}

		static void debugLayerCallback(
			NVNdebugCallbackSource source,
			NVNdebugCallbackType type,
			int id,
			NVNdebugCallbackSeverity severity,
			const char* message,
			void* pUser
		)
		{
			BX_TRACE("NVN Debug Layer Callback:\n");
			BX_TRACE("  source:       0x%08x\n", source);
			BX_TRACE("  type:         0x%08x\n", type);
			BX_TRACE("  id:           0x%08x\n", id);
			BX_TRACE("  severity:     0x%08x\n", severity);
			BX_TRACE("  message:      %s\n", message);

			BX_ASSERT(false, "NVN Debug layer callback hit");
		}

		bool nvnInitDevice(const Init& _init)
		{
			int deviceFlags = 0;

			if (_init.debug) {
				deviceFlags = NVN_DEVICE_FLAG_DEBUG_ENABLE_BIT | NVN_DEVICE_FLAG_DEBUG_ENABLE_LEVEL_4_BIT;
			}

			NVNdeviceBuilder deviceBuilder;
			nvnDeviceBuilderSetDefaults(&deviceBuilder);
			nvnDeviceBuilderSetFlags(&deviceBuilder, deviceFlags);

			if (!nvnDeviceInitialize(&m_Device, &deviceBuilder))
			{
				BX_ASSERT(false, "nvnDeviceInitialize");
				return false;
			}

			nvnLoadCProcs(&m_Device, pfnc_nvnDeviceGetProcAddress);

			/*
				* Debug Layer Callback
				* --------------------
				* Install the debug layer callback if the debug layer was enabled during
				* device initialization. It is possible to pass a pointer to the NVN API
				* to remember and pass back through the debug callback.
				*/
			if (deviceFlags & NVN_DEVICE_FLAG_DEBUG_ENABLE_LEVEL_4_BIT)
			{
				nvnDeviceInstallDebugCallback(
					&m_Device,
					reinterpret_cast<PFNNVNDEBUGCALLBACKPROC>(&debugLayerCallback),
					NULL, // For testing purposes; any pointer is OK here.
					NVN_TRUE // NVN_TRUE = Enable the callback.
				);
			}

			int apiMajor, apiMinor;
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_API_MAJOR_VERSION, &apiMajor);
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_API_MINOR_VERSION, &apiMinor);

			// do quick API version check? is that even necessary?

			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_COMMAND_BUFFER_COMMAND_ALIGNMENT, &m_CommandBufferCommandAlignment);
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_COMMAND_BUFFER_CONTROL_ALIGNMENT, &m_CommandBufferControlAlignment);
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_UNIFORM_BUFFER_ALIGNMENT, &m_UniformBufferAlignment);
			nvnDeviceGetInteger(&m_Device, NVN_DEVICE_INFO_MAX_TEXTURE_ANISOTROPY, &m_maxAnisotropy);

			return true;
		}

		void initializeMemoryPool()
		{
			m_resources.initPools();
		}

		void initializeSwapChain(const Init& _init)
		{
			m_SwapChain.create(m_Hwnd, &m_Device, _init.resolution, bgfx::TextureFormat::Enum::RGBA8, bgfx::TextureFormat::Enum::D24S8);
			m_Queue.init(&m_Device, &m_SwapChain);
		}

		void initializeWindow(const Init& _init)
		{
			// configure to be like D3D, need to figure out how to get it to not display upside down though
			//nvnDeviceSetWindowOriginMode(g_nvnDevice, NVN_WINDOW_ORIGIN_MODE_UPPER_LEFT);
			//nvnDeviceSetDepthMode(g_nvnDevice, NVN_DEPTH_MODE_NEAR_IS_ZERO);

#if 0
			for (int ii = 0; ii < SwapChainBufferCount; ii++)
			{
				nvnSyncInitialize(&m_DisplayFence[ii], &m_Device);
			}

			if (nn::oe::GetOperationMode() == nn::oe::OperationMode_Console) {
				g_caps.displayWidth = 1920;
				g_caps.displayHeight = 1080;
			}
			else {
				g_caps.displayWidth = 1280;
				g_caps.displayHeight = 720;
			}
#endif
		}

		bool init(const Init& _init)
		{
			m_Hwnd = (NVNnativeWindow)g_platformData.nwh;

			if (!m_Hwnd)
			{
				BX_ASSERT(false, "No hwnd provided");
				return false;
			}

			if (!nvnInit())
			{
				return false;
			}

			if (!nvnInitDevice(_init))
			{
				return false;
			}

			g_nvnDevice = &m_Device;

			initializeMemoryPool();
			initializeSwapChain(_init);
			initializeWindow(_init);

			m_resources.m_resolution = _init.resolution;

			return true;
		}

		void shutdown()
		{
			//for (int ii = 0; ii < SwapChainBufferCount; ii++)
			//{
			//	nvnSyncFinalize(&m_DisplayFence[ii]);
			//}

			//m_activeSamplersCount = 0;
			//m_samplers.invalidate();
			//m_Queue.shutdown();

			m_SwapChain.destroy();

			m_resources.m_commandMemoryPools.shutdown();
			m_resources.m_textureSamplersPool.shutdown();

			g_nvnDevice = NULL;
			nvnDeviceFinalize(&m_Device);
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
			m_SwapChain.present(&m_Queue.m_GfxQueue);
		}

		void createIndexBuffer(IndexBufferHandle _handle, const Memory* _mem, uint16_t _flags) override
		{
			m_resources.m_indexBuffers[_handle.idx].create(_mem->size, _mem->data, _flags, 0, BufferNVN::Usage::IndexBuffer);
		}

		void destroyIndexBuffer(IndexBufferHandle _handle) override
		{
			m_resources.m_indexBuffers[_handle.idx].destroy();
		}

		void createVertexLayout(VertexLayoutHandle _handle, const VertexLayout& _layout) override
		{
			VertexLayout& layout = m_resources.m_vertexLayouts[_handle.idx];
			::memcpy(&layout, &_layout, sizeof(VertexLayout));
			dump(layout);
		}

		void destroyVertexLayout(VertexLayoutHandle _handle) override
		{
			VertexLayout& layout = m_resources.m_vertexLayouts[_handle.idx];
			memset(&layout, 0, sizeof(VertexLayout));
		}

		void createVertexBuffer(VertexBufferHandle _handle, const Memory* _mem, VertexLayoutHandle _layoutHandle, uint16_t _flags) override
		{
			m_resources.m_vertexBuffers[_handle.idx].create(_mem->size, _mem->data, _layoutHandle, _flags);
		}

		void destroyVertexBuffer(VertexBufferHandle _handle) override
		{
			m_resources.m_vertexBuffers[_handle.idx].destroy();
		}

		void createDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			m_resources.m_indexBuffers[_handle.idx].create(_size, nullptr, _flags, 0, BufferNVN::Usage::IndexBuffer);
		}

		void destroyDynamicIndexBuffer(IndexBufferHandle _handle) override
		{
			m_resources.m_indexBuffers[_handle.idx].destroy();
		}

		void createDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _size, uint16_t _flags) override
		{
			VertexLayoutHandle layout = BGFX_INVALID_HANDLE;
			m_resources.m_vertexBuffers[_handle.idx].create(_size, nullptr, layout, _flags);
		}

		void destroyDynamicVertexBuffer(VertexBufferHandle _handle) override
		{
			m_resources.m_vertexBuffers[_handle.idx].destroy();
		}

#if BGFX_NVN_USE_STAGING_FOR_UPDATE
		void _updateDynamicBuffer(NVNbufferAddress _addr, uint32_t _offset, uint32_t _size, const Memory* _mem)
		{
			CopyOperation copyOp;
			copyOp.m_data = (CopyOperation::Data*)BX_ALLOC(g_allocator, sizeof(CopyOperation::Data));
			copyOp.createBuffer(_size, copyOp.m_data);

			// populate src buffer
			uint8_t* dst = (uint8_t*)nvnBufferMap(&copyOp.m_data->m_buffer);
			memcpy(dst, _mem->data, _size);
			nvnBufferFlushMappedRange(&copyOp.m_data->m_buffer, 0, _size);

			CopyOperation::Op op;
			op.m_type = CopyOperation::Op::Buffer;
			op.m_dstBuffer = _addr + _offset; // _offset is destination offset, op.m_offset is source offset
			op.m_memSize = _size;
			copyOp.m_ops.push_back(op);

			m_copyOperations.push_back(copyOp);
		}
#endif

		void updateDynamicIndexBuffer(IndexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
#if BGFX_NVN_USE_STAGING_FOR_UPDATE
			NVNbufferAddress addr = m_resources.m_indexBuffers[_handle.idx].m_gpuAddress;
			_updateDynamicBuffer(addr, _offset, _size, _mem);
#else
			m_resources.m_indexBuffers[_handle.idx].update(_offset, _size, _mem->data, true);
#endif
		}

		void updateDynamicVertexBuffer(VertexBufferHandle _handle, uint32_t _offset, uint32_t _size, const Memory* _mem) override
		{
#if BGFX_NVN_USE_STAGING_FOR_UPDATE
			NVNbufferAddress addr = m_resources.m_vertexBuffers[_handle.idx].m_gpuAddress;
			_updateDynamicBuffer(addr, _offset, _size, _mem);
#else
			m_resources.m_vertexBuffers[_handle.idx].update(_offset, _size, _mem->data, true);
#endif
		}

		void createShader(ShaderHandle _handle, const Memory* _mem) override
		{
			ShaderNVN& shader = m_resources.m_shaders[_handle.idx];

			shader.create(&m_Device, _mem, m_resources.m_uniformReg, m_resources.m_uniformBuffers);

			// resolve uniform references in uniform buffers
			for (uint32_t index : shader.m_constantBuffers)
			{
				ShaderUniformBuffer& cb = m_resources.m_uniformBuffers.get(index);
				for (ShaderUniformBuffer::UniformReference& uniformRef : cb.m_uniforms)
				{
					if (uniformRef.m_data == nullptr)
					{
						if (uniformRef.m_predefined != PredefinedUniform::Enum::Count)
						{
							int predefined = 0;
							for (predefined = 0; predefined < shader.m_numPredefined; ++predefined)
							{
								if (shader.m_predefined[predefined].m_type == uniformRef.m_predefined)
								{
									break;
								}
							}

							if (predefined != shader.m_numPredefined)
							{
								uint32_t loc = shader.m_predefined[predefined].m_loc;

								if (uniformRef.m_predefined & kUniformFragmentBit)
								{
									uniformRef.m_data = &m_resources.m_uniformsPredefinedFS[loc];
								}
								else
								{
									uniformRef.m_data = &m_resources.m_uniformsPredefinedVS[loc];
								}
							}
						}
						else
						{
							uniformRef.m_data = m_resources.m_uniforms[uniformRef.m_handle.idx];
						}
					}
				}
			}
		}

		void destroyShader(ShaderHandle _handle) override
		{
			m_resources.m_shaders[_handle.idx].destroy();
		}

		void createProgram(ProgramHandle _handle, ShaderHandle _vsh, ShaderHandle _fsh) override
		{
			m_resources.m_program[_handle.idx].create(&m_Device, isValid(_vsh) ? &m_resources.m_shaders[_vsh.idx] : nullptr, isValid(_fsh) ? &m_resources.m_shaders[_fsh.idx] : nullptr);
		}

		void destroyProgram(ProgramHandle _handle) override
		{
			m_resources.m_program[_handle.idx].destroy();
		}

		void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override
		{
			CopyOperation copyOp;
			m_resources.m_textures[_handle.idx].create(&m_Device, _mem, _flags, _skip, copyOp);
			m_resources.m_textureSamplersPool.set(_handle.idx, &m_resources.m_textures[_handle.idx].m_ptr);
			if (_flags & BGFX_TEXTURE_COMPUTE_WRITE)
			{
				TextureNVN& tex = m_resources.m_textures[_handle.idx];
				for (uint8_t i = 0; i < tex.m_numMips; ++i)
				{
					m_resources.registerImage(_handle.idx, i);
				}
			}

			if (!copyOp.m_ops.empty())
			{
				m_copyOperations.push_back(std::move(copyOp));
			}
			return NULL;
		}

		void updateTextureBegin(TextureHandle /*_handle*/, uint8_t /*_side*/, uint8_t /*_mip*/) override
		{
		}

		void updateTexture(TextureHandle _handle, uint8_t _side, uint8_t _mip, const Rect& _rect, uint16_t _z, uint16_t _depth, uint16_t _pitch, const Memory* _mem) override
		{
			TextureNVN& tex = m_resources.m_textures[_handle.idx];
			const bool convert = tex.m_textureFormat != tex.m_requestedFormat;

			uint32_t bpp = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(tex.m_textureFormat));
			uint32_t rectpitch = _rect.m_width * bpp / 8;
			uint32_t rectheight = _rect.m_height;

			if (bimg::isCompressed(bimg::TextureFormat::Enum(tex.m_textureFormat)))
			{
				const bimg::ImageBlockInfo& blockInfo = bimg::getBlockInfo(bimg::TextureFormat::Enum(tex.m_textureFormat));
				rectpitch = (_rect.m_width / blockInfo.blockWidth) * blockInfo.blockSize;
				rectheight = _rect.m_height / blockInfo.blockHeight;
			}

			uint32_t srcpitch = (UINT16_MAX == _pitch) ? rectpitch : _pitch;
			uint32_t size = rectpitch * rectheight;

			CopyOperation copyOp;
			copyOp.m_data = (CopyOperation::Data*)BX_ALLOC(g_allocator, sizeof(CopyOperation::Data));
			copyOp.createBuffer(size, copyOp.m_data);

			// populate src buffer
			uint8_t* dst = (uint8_t*)nvnBufferMap(&copyOp.m_data->m_buffer);

			if (convert)
			{
				bimg::imageDecodeToBgra8(g_allocator, dst, _mem->data, _rect.m_width, _rect.m_height, rectpitch, bimg::TextureFormat::Enum(tex.m_requestedFormat));
			}
			else
			{
				if (rectpitch != srcpitch)
				{
					for (int y = 0; y < rectheight; ++y)
					{
						memcpy(dst + (rectpitch * y), _mem->data + (srcpitch * y), rectpitch);
					}
				}
				else
				{
					memcpy(dst, _mem->data, size);
				}
			}

			nvnBufferFlushMappedRange(&copyOp.m_data->m_buffer, 0, _mem->size);

			CopyOperation::Op op;
			op.m_type = CopyOperation::Op::Texture;
			op.m_dstTexture = &tex.m_ptr;
			op.m_offset = 0;
			op.m_memSize = _mem->size;

			nvnTextureViewSetDefaults(&op.m_dstView);
			nvnTextureViewSetLevels(&op.m_dstView, _mip, 1);

			op.m_dstRegion.xoffset = _rect.m_x;
			op.m_dstRegion.yoffset = _rect.m_y;
			op.m_dstRegion.zoffset = _z;
			op.m_dstRegion.width = _rect.m_width;
			op.m_dstRegion.height = _rect.m_height;
			op.m_dstRegion.depth = _depth;

			if (tex.m_type != TextureNVN::Enum::Texture3D)
			{
				nvnTextureViewSetLayers(&op.m_dstView, _side, 1);
			}

			copyOp.m_ops.push_back(op);

			m_copyOperations.push_back(copyOp);
		}

		void updateTextureEnd() override
		{
		}

		void readTexture(TextureHandle _handle, void* _data, uint8_t _mip) override
		{
			TextureNVN& tex = m_resources.m_textures[_handle.idx];

			NVNtextureView view;
			nvnTextureViewSetDefaults(&view);
			nvnTextureViewSetLayers(&view, 0, 1);
			nvnTextureViewSetLevels(&view, _mip, 1);

			NVNcopyRegion region;
			region.xoffset = 0;
			region.yoffset = 0;
			region.zoffset = 0;
			region.width = tex.m_width >> _mip;
			region.height = tex.m_height >> _mip;
			region.depth = std::max(tex.m_depth >> _mip, 1u);

			nvnTextureInvalidateTexels(&tex.m_ptr, nullptr, &region);
			nvnTextureReadTexels(&tex.m_ptr, &view, &region, _data);
		}

		void resizeTexture(TextureHandle /*_handle*/, uint16_t /*_width*/, uint16_t /*_height*/, uint8_t /*_numMips*/, uint16_t /*_numLayers*/) override
		{
		}

		void overrideInternal(TextureHandle /*_handle*/, uintptr_t /*_ptr*/) override
		{
		}

		uintptr_t getInternal(TextureHandle /*_handle*/) override
		{
			return 0;
		}

		void destroyTexture(TextureHandle _handle) override
		{
			m_resources.unregisterImages(_handle.idx);
			m_resources.m_textures[_handle.idx].destroy();
		}

		void createFrameBuffer(FrameBufferHandle _handle, uint8_t _num, const Attachment* _attachment) override
		{
			FrameBufferNVN& fb = m_resources.m_frameBuffers[_handle.idx];

			fb.create(_num, _attachment);

			// resolve handles to texture objects
			fb.m_numTargets = 0;
			for (int i = 0; i < _num; ++i)
			{
				const Attachment& attachment = _attachment[i];
				TextureNVN& tex = m_resources.m_textures[attachment.handle.idx];

				if (!bimg::isDepth((bimg::TextureFormat::Enum)tex.m_textureFormat))
				{
					fb.m_colorTargets[fb.m_numTargets] = attachment.handle;
					nvnTextureViewSetDefaults(&fb.m_colorViews[fb.m_numTargets]);
					nvnTextureViewSetLevels(&fb.m_colorViews[fb.m_numTargets], attachment.mip, 1);
					nvnTextureViewSetLayers(&fb.m_colorViews[fb.m_numTargets], attachment.layer, 1);

					fb.m_numTargets++;
				}
				else
				{
					fb.m_depthTarget = attachment.handle;
					nvnTextureViewSetDefaults(&fb.m_depthView);
					nvnTextureViewSetLevels(&fb.m_depthView, attachment.mip, 1);
					nvnTextureViewSetLayers(&fb.m_depthView, attachment.layer, 1);
				}
			}

			if (_num)
			{
				const Attachment& attachment = _attachment[0];
				TextureNVN& tex = m_resources.m_textures[attachment.handle.idx];
				fb.m_width = tex.m_width >> attachment.mip;
				fb.m_height = tex.m_height >> attachment.mip;
			}
			else
			{
				fb.m_width = 0;
				fb.m_height = 0;
			}
		}

		void createFrameBuffer(FrameBufferHandle /*_handle*/, void* /*_nwh*/, uint32_t /*_width*/, uint32_t /*_height*/, TextureFormat::Enum /*_format*/, TextureFormat::Enum /*_depthFormat*/) override
		{
			BX_ASSERT(false, "NVN doesn't support multiple windows.");
		}

		void destroyFrameBuffer(FrameBufferHandle /*_handle*/) override
		{
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override
		{
			if (NULL != m_resources.m_uniforms[_handle.idx])
			{
				BX_FREE(g_allocator, m_resources.m_uniforms[_handle.idx]);
			}

			uint32_t size = nn::util::align_up(g_uniformTypeSize[_type] * _num, 16);
			void* data = BX_ALLOC(g_allocator, size);
			bx::memSet(data, 0, size);
			m_resources.m_uniforms[_handle.idx] = data;
			m_resources.m_uniformReg.add(_handle, _name);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			BX_FREE(g_allocator, m_resources.m_uniforms[_handle.idx]);
			m_resources.m_uniforms[_handle.idx] = NULL;
		}

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			if (_flags & kUniformFragmentBit)
			{
				memcpy(&m_resources.m_uniformsPredefinedFS[_regIndex], _val, _numRegs * 16);
			}
			else
			{
				memcpy(&m_resources.m_uniformsPredefinedVS[_regIndex], _val, _numRegs * 16);
			}
		}

		void setShaderUniform4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _regIndex, _val, _numRegs);
		}

		void setShaderUniform4x4f(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			setShaderUniform(_flags, _regIndex, _val, _numRegs);
		}

		void requestScreenShot(FrameBufferHandle /*_handle*/, const char* /*_filePath*/) override
		{
		}

		void updateViewName(ViewId _id, const char* _name) override
		{
			bx::strCopy(&s_viewName[_id][BGFX_CONFIG_MAX_VIEW_NAME_RESERVED]
				, BX_COUNTOF(s_viewName[0]) - BGFX_CONFIG_MAX_VIEW_NAME_RESERVED
				, _name
			);
		}

		void updateUniform(uint16_t _loc, const void* _data, uint32_t _size) override
		{
			memcpy(m_resources.m_uniforms[_loc], _data, _size);
		}

		void invalidateOcclusionQuery(OcclusionQueryHandle /*_handle*/) override
		{
		}

		void setMarker(const char* _marker, uint16_t /*_len*/) override
		{
			if (BX_ENABLED(BGFX_CONFIG_DEBUG_ANNOTATION))
			{
				if (m_currentCommands)
				{
					nvnCommandBufferInsertDebugMarker(m_currentCommands->m_cmdList.get(), _marker);
				}
			}
		}

		virtual void setName(Handle /*_handle*/, const char* /*_name*/, uint16_t /*_len*/) override
		{
		}

		void _processCopyOperations(CommandListNVN& cmd, Frame* _render)
		{
			if (_render->m_iboffset > 0)
			{
				BGFX_PROFILER_SCOPE("bgfx/Update transient index buffer", kColorResource);
				TransientIndexBuffer* ib = _render->m_transientIb;
				m_resources.m_indexBuffers[ib->handle.idx].update(0, _render->m_iboffset, ib->data, true);
			}

			if (_render->m_vboffset > 0)
			{
				BGFX_PROFILER_SCOPE("bgfx/Update transient vertex buffer", kColorResource);
				TransientVertexBuffer* vb = _render->m_transientVb;
				m_resources.m_vertexBuffers[vb->handle.idx].update(0, _render->m_vboffset, vb->data, true);
			}

			// process pending transient deletions first
			{
				auto it = m_deleteOperations.begin();
				while (it != m_deleteOperations.end())
				{
					DeleteOperation& op = *it;
					op.m_count--;
					if (op.m_count == 0)
					{
						nvnBufferFinalize(&op.m_data->m_buffer);
						nvnMemoryPoolFinalize(&op.m_data->m_pool);
						BX_ALIGNED_FREE(g_allocator, op.m_data->m_mem, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);
						it = m_deleteOperations.erase(it);
					}
					else
					{
						++it;
					}
				}
			}

			// then process pending copy operations
			{
				NVNcommandBuffer* cmdBuf = cmd.get();

				for (CopyOperation& copyOp : m_copyOperations)
				{
					CopyOperation::Data* data = copyOp.m_data;

					NVNbufferAddress srcAddr = nvnBufferGetAddress(&data->m_buffer);
					for (CopyOperation::Op& op : copyOp.m_ops)
					{
						switch (op.m_type)
						{
						case CopyOperation::Op::Texture:
							nvnCommandBufferCopyBufferToTexture(cmdBuf, srcAddr + op.m_offset, op.m_dstTexture, &op.m_dstView, &op.m_dstRegion, 0);
							break;
						case CopyOperation::Op::Buffer:
							nvnCommandBufferCopyBufferToBuffer(cmdBuf, srcAddr + op.m_offset, op.m_dstBuffer, op.m_memSize, 0);
							break;
						default:
							break;
						}
					}

					DeleteOperation delOp;
					delOp.m_data = data;
					m_deleteOperations.push_back(delOp);
				}

				m_copyOperations.clear();
			}
		}

		void _processItemCompute(Commands& _cmds, Frame* _render, const RenderCompute& _compute, const RenderBind& _bind)
		{
			ProgramNVN& program = m_resources.m_program[_cmds.m_state.programIndex];

			_cmds.m_state.viewState.setPredefined<4>(this, _cmds.m_state.view, program, _render, _compute);
			rendererUpdateUniforms(this, _render->m_uniformBuffer[_compute.m_uniformIdx], _compute.m_uniformBegin, _compute.m_uniformEnd);

			_cmds.bindUniformBuffers(program);
			_cmds.bindSamplers(_bind, _render->m_colorPalette);
			_cmds.dispatch(_compute);
		}

		void _processItemDraw(Commands& _cmds, Frame* _render, const RenderDraw& _draw, const RenderBind& _bind)
		{
			ProgramNVN& program = m_resources.m_program[_cmds.m_state.programIndex];

			_cmds.setRasterState(_draw);

			_cmds.m_state.viewState.setPredefined<4>(this, _cmds.m_state.view, program, _render, _draw);
			rendererUpdateUniforms(this, _render->m_uniformBuffer[_draw.m_uniformIdx], _draw.m_uniformBegin, _draw.m_uniformEnd);

			_cmds.bindUniformBuffers(program); // potentially update uniform buffers for this draw
			_cmds.bindSamplers(_bind, _render->m_colorPalette);
			_cmds.bindVertexBuffers(_draw);
			_cmds.bindIndexBuffer(_draw);
			_cmds.draw(_draw);
		}

		void _processViewItems(Commands& cmds, Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter)
		{
			BGFX_PROFILER_SCOPE("gfx::_processViewItems", 0xff2040ff);

			BX_UNUSED(_clearQuad);
			BX_UNUSED(_textVideoMemBlitter);

			CommandListNVN& cmd = cmds.m_cmdList;

			SortKey key;

			BackBuffer backBuffer = m_SwapChain.get();

			std::array<NVNtexture*, 1> defaultTarget = { &backBuffer.m_color->m_ptr };
			cmds.setFrameBuffer(1, defaultTarget.data(), &backBuffer.m_depth->m_ptr, nullptr, nullptr);

			int32_t numItems = _render->m_numRenderItems;
			for (int32_t item = 0, restartItem = numItems; item < numItems || restartItem < numItems;)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];

				cmds.m_state.isCompute = key.decode(encodedKey, _render->m_viewRemap);

				const uint32_t itemIdx = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];

				BX_UNUSED(renderBind);

				const View& view = _render->m_view[key.m_view];

				if (cmds.setView(_render, key.m_view, item == numItems, backBuffer))
				{
					cmds.processBlits(_render);
					cmds.setViewport(view.m_rect, view.m_scissor, 0.f, 1.f);
					cmds.clearViewport(view.m_clear, _render->m_colorPalette);
				}

				cmds.bindProgram(key.m_program);

				if (cmds.m_state.isCompute)
				{
					_processItemCompute(cmds, _render, renderItem.compute, renderBind);
				}
				else
				{
					_processItemDraw(cmds, _render, renderItem.draw, renderBind);
				}

				cmds.m_state.wasCompute = cmds.m_state.isCompute;

				++item;
			}

			// reset back to the default backbuffer
			cmds.setFrameBuffer(1, defaultTarget.data(), &backBuffer.m_depth->m_ptr, nullptr, nullptr);
		}

		bool _updateResolution(const Resolution& _resolution)
		{
			bool changed = false;
			if (m_resources.m_resolution.width != _resolution.width || m_resources.m_resolution.height != _resolution.height)
			{
				m_resources.m_resolution = _resolution;
				changed = true;
			}
			return changed;
		}

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override
		{
			BGFX_PROFILER_SCOPE("gfx::submit", 0xff2040ff);

			if (_updateResolution(_render->m_resolution))
			{
				// recreate swap chain?
			}

			_render->sort();

			int64_t timeBegin = 0;
			int64_t timeEnd = 0;

			if (0 == (_render->m_debug & BGFX_DEBUG_IFH))
			{
				{
					BGFX_PROFILER_SCOPE("gfx::acquireNextScanBuffer", 0xff2040ff);

					m_SwapChain.acquireNext();
					m_resources.m_commandMemoryPools.swap();
				}

				{
					BGFX_PROFILER_SCOPE("gfx::waitForPreviousFrame", 0xff2040ff);

					if (m_PreviousFrameSync != nullptr)
					{
						m_Queue.finish(m_PreviousFrameSync);
						m_PreviousFrameSync = nullptr;
					}

					m_SubmitCounter++;
				}

				timeBegin = bx::getHPCounter();

				CommandListNVN& cmd = *m_Queue.alloc(m_resources.m_commandMemoryPools.get(), "submit");
				Commands cmds(cmd, _render, m_resources);
				m_currentCommands = &cmds;

				m_resources.m_textureSamplersPool.bind(cmd.get());

				_processCopyOperations(cmd, _render);
				_processViewItems(cmds, _render, _clearQuad, _textVideoMemBlitter);

				if (_render->m_debug & (BGFX_DEBUG_IFH | BGFX_DEBUG_STATS))
				{
					blit(this, _textVideoMemBlitter, _render->m_textVideoMem);
				}
				else if (_render->m_debug & BGFX_DEBUG_TEXT)
				{
					blit(this, _textVideoMemBlitter, _render->m_textVideoMem);
				}

				m_currentCommands = nullptr;

				m_PreviousFrameSync = m_Queue.kick();

				timeEnd = bx::getHPCounter();
			}

			int64_t frameTime = timeEnd - timeBegin;
			const int64_t timerFreq = bx::getHPFrequency();

			Stats& perfStats = _render->m_perfStats;
			perfStats.cpuTimeBegin = timeBegin;
			perfStats.cpuTimeEnd = timeEnd;
			perfStats.cpuTimerFreq = timerFreq;
			//const TimerQueryD3D11::Result& result = m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];
			perfStats.gpuTimeBegin = 0; // result.m_begin;
			perfStats.gpuTimeEnd = 0; // result.m_end;
			perfStats.gpuTimerFreq = 1000000000; // result.m_frequency;
			perfStats.numDraw = 0; // statsKeyType[0];
			perfStats.numCompute = 0; // statsKeyType[1];
			perfStats.numBlit = _render->m_numBlitItems;
			perfStats.maxGpuLatency = 0; // maxGpuLatency;
			//bx::memCopy(perfStats.numPrims, statsNumPrimsRendered, sizeof(perfStats.numPrims));
		}

		void blitSetup(TextVideoMemBlitter& _blitter) override
		{
			Commands& cmds = *m_currentCommands;

			const uint32_t width = m_resources.m_resolution.width;
			const uint32_t height = m_resources.m_resolution.height;

			float proj[16];
			bx::mtxOrtho(proj, 0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f, 0.0f, g_caps.homogeneousDepth);

			ProgramNVN& program = m_resources.m_program[_blitter.m_program.idx];

			for (int i = 0; i < PredefinedUniform::Count; ++i)
			{
				PredefinedUniform& predefined = program.m_predefined[i];
				if (predefined.m_type == PredefinedUniform::ModelViewProj)
				{
					setShaderUniform(predefined.m_type, predefined.m_loc, proj, 4);
				}
			}

			VertexBufferNVN& vb = m_resources.m_vertexBuffers[_blitter.m_vb->handle.idx];
			VertexLayout& layout = m_resources.m_vertexLayouts[_blitter.m_vb->layoutHandle.idx];

			uint32_t writeMask = (BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
			uint32_t blendState = BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
			uint32_t blendEquation = BGFX_STATE_BLEND_EQUATION_ADD;

			RenderDraw draw;
			draw.clear();
			draw.m_streamMask = 1;
			draw.m_stream[0].m_startVertex = 0;
			draw.m_stream[0].m_handle = _blitter.m_vb->handle;
			draw.m_stream[0].m_layoutHandle = _blitter.m_vb->layoutHandle;
			draw.m_indexBuffer = _blitter.m_ib->handle;
			draw.m_instanceDataBuffer.idx = BGFX_INVALID_HANDLE;
			draw.m_instanceDataOffset = 0;
			draw.m_instanceDataStride = 0;
			draw.m_numVertices = vb.m_size / layout.m_stride;
			draw.m_stateFlags = blendState | blendEquation | writeMask;

			RenderBind bind;
			bind.clear();
			bind.m_bind[0].m_type = Binding::Texture;
			bind.m_bind[0].m_idx = _blitter.m_texture.idx;
			bind.m_bind[0].m_samplerFlags = m_resources.m_textures[_blitter.m_texture.idx].m_flags & BGFX_SAMPLER_BITS_MASK;

			cmds.setRasterState(draw);
			cmds.bindProgram(_blitter.m_program);
			cmds.bindUniformBuffers(program);
			cmds.bindSamplers(bind, cmds.m_render->m_colorPalette);
			cmds.bindVertexBuffers(draw);
			cmds.bindIndexBuffer(draw);
		}

		void blitRender(TextVideoMemBlitter& _blitter, uint32_t _numIndices) override
		{
			Commands& cmds = *m_currentCommands;

			const uint32_t numVertices = _numIndices * 4 / 6;
			if (0 < numVertices)
			{
				BufferNVN& ib = m_resources.m_indexBuffers[_blitter.m_ib->handle.idx];
				VertexBufferNVN& vb = m_resources.m_vertexBuffers[_blitter.m_vb->handle.idx];

				ib.update(0, _numIndices * 2, _blitter.m_ib->data);
				vb.update(0, numVertices * _blitter.m_layout.m_stride, _blitter.m_vb->data, true);

				NVNindexType indexType = cmds.m_cmdList.m_currentIndexBufferIndexType;
				NVNbufferAddress indexAddr = ib.m_gpuAddress;

				nvnCommandBufferDrawElementsInstanced(cmds.m_cmdList.get(), NVN_DRAW_PRIMITIVE_TRIANGLES, NVN_INDEX_TYPE_UNSIGNED_SHORT, _numIndices, indexAddr, 0, 0, 1);
			}
		}
	};

	static RendererContextNVN* s_renderNVN = NULL;

	void OutOfCommandBufferMemoryEventCallback(NVNcommandBuffer* cmdBuf,
		NVNcommandBufferMemoryEvent event,
		size_t minSize,
		void* callbackData)
	{
		const size_t size = std::max(size_t{ 512 }, minSize);

		CommandMemoryPool& pools = s_renderNVN->m_resources.m_commandMemoryPools.get();

		MemoryPool& poolCommands = pools[MemoryPoolType::CommandBufferCommands];
		MemoryPool& poolControls = pools[MemoryPoolType::CommandBufferControls];

		switch (event)
		{
		case NVNcommandBufferMemoryEvent::NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_COMMAND_MEMORY:
			nvnCommandBufferAddCommandMemory(cmdBuf, poolCommands.GetMemoryPool(), poolCommands.GetNewMemoryChunkOffset(size, s_renderNVN->m_CommandBufferCommandAlignment), size);
			break;
		case NVNcommandBufferMemoryEvent::NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_CONTROL_MEMORY:
			nvnCommandBufferAddControlMemory(cmdBuf, static_cast<uint8_t*>(poolControls.GetMemory()) + poolControls.GetNewMemoryChunkOffset(size, s_renderNVN->m_CommandBufferControlAlignment), size);
			break;
		default:
			BX_ASSERT(false, "Unknown event");
			break;
		}
	}

	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		s_renderNVN = BX_NEW(g_allocator, RendererContextNVN);
		if (!s_renderNVN->init(_init))
		{
			BX_DELETE(g_allocator, s_renderNVN);
			s_renderNVN = NULL;
		}

		return s_renderNVN;
	}

	void rendererDestroy()
	{
		s_renderNVN->shutdown();
		BX_DELETE(g_allocator, s_renderNVN);
		s_renderNVN = NULL;
	}
} /* namespace nvn */ } // namespace bgfx

#else

namespace bgfx { namespace nvn
{
	RendererContextI* rendererCreate(const Init& _init)
	{
		BX_UNUSED(_init);
		return NULL;
	}

	void rendererDestroy()
	{
	}
} /* namespace nvn */ } // namespace bgfx

#endif // BGFX_CONFIG_RENDERER_NVN
