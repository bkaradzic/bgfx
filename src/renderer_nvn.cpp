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

#if !defined(BGFX_CONFIG_NVN_GRAPHICS_POOL_SIZE)
#define BGFX_CONFIG_NVN_GRAPHICS_POOL_SIZE ((size_t)512 * (size_t)1024 * (size_t)1024) // default to 512MB
#endif

#if !defined(BGFX_CONFIG_NVN_MAX_SHADER_NAME)
#define BGFX_CONFIG_NVN_MAX_SHADER_NAME 32
#endif

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
	static char s_shaderName[BGFX_CONFIG_MAX_SHADERS][BGFX_CONFIG_NVN_MAX_SHADER_NAME];

	struct PrimitiveInfo
	{
		Topology::Enum m_type;
		NVNdrawPrimitive m_typeNVN;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	static const PrimitiveInfo s_primitiveInfo[] =
	{
		{ Topology::Enum::TriList,		NVN_DRAW_PRIMITIVE_TRIANGLES,		3, 3, 0 },
		{ Topology::Enum::TriStrip,		NVN_DRAW_PRIMITIVE_TRIANGLE_STRIP,	3, 1, 2 },
		{ Topology::Enum::LineList,		NVN_DRAW_PRIMITIVE_LINES,			2, 2, 0 },
		{ Topology::Enum::LineStrip,	NVN_DRAW_PRIMITIVE_LINE_STRIP,		2, 1, 1 },
		{ Topology::Enum::PointList,	NVN_DRAW_PRIMITIVE_POINTS,			1, 1, 0 },
		{ Topology::Enum::Count,		NVN_DRAW_PRIMITIVE_POLYGON,			0, 0, 0 }  // Undefined
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

	struct DrawStats
	{
		enum StatType
		{
			DispatchMesh = 0,
			DispatchCompute,
			NumIndices,
			NumTypes
		};

		struct PrimitiveStas
		{
			int numRendered;
			int numInstances;
			int numSubmitted;
			int numIndirect;
		};

		int m_stats[NumTypes];
		PrimitiveStas m_primStats[Topology::Enum::Count];

		void add(const StatType _type, const int _count)
		{
			m_stats[_type] += _count;
		}

		int get(const StatType _type) const
		{
			return m_stats[_type];
		}

		void reset()
		{
			memset(m_stats, 0, sizeof(m_stats));
			memset(m_primStats, 0, sizeof(m_primStats));
		}
	};

	struct ContextResources
	{
		Resolution m_resolution;

		TextureNVN m_textures[BGFX_CONFIG_MAX_TEXTURES];
		BufferNVN m_shaderBuffers[BGFX_CONFIG_MAX_SHADER_BUFFERS];
		BufferNVN m_indexBuffers[BGFX_CONFIG_MAX_INDEX_BUFFERS];
		VertexBufferNVN m_vertexBuffers[BGFX_CONFIG_MAX_VERTEX_BUFFERS];
		VertexLayout m_vertexLayouts[BGFX_CONFIG_MAX_VERTEX_LAYOUTS];
		ShaderNVN m_shaders[BGFX_CONFIG_MAX_SHADERS];
		ProgramNVN m_program[BGFX_CONFIG_MAX_PROGRAMS];
		FrameBufferNVN m_frameBuffers[BGFX_CONFIG_MAX_FRAME_BUFFERS];
		UniformNVN m_uniforms[BGFX_CONFIG_MAX_UNIFORMS];
		UniformNVN m_uniformsPredefined[PredefinedUniform::Count];
		UniformRegistry m_uniformReg;
		UniformBufferRegistry m_uniformBuffers;
		TexturesSamplersPool m_textureSamplersPool;
		std::vector<std::pair<uint64_t, PipelineVboState>> m_vboStateCache;
		std::vector<std::pair<uint32_t, NVNsampler>> m_samplerCache;
		std::vector<std::pair<uint16_t, NVNtextureView>> m_imageCache;

		MemoryPool m_shaderScratch;

		OcclusionQueryNVN m_occlusionQuery;
		TimerQueryNVN m_gpuTimer;

		DrawStats m_drawStats;

		ContextResources()
		{
			memset(m_shaders, 0, sizeof(m_shaders));
		}

		void initPools(int _numFrames)
		{
			m_textureSamplersPool.init(g_nvnDevice);

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
			int numImages = m_imageCache.size();

			int i = 0;
			for (i = 0; i < numImages; ++i)
			{
				auto& it = m_imageCache[i];

				int mip, numLevels;
				nvnTextureViewGetLevels(&it.second, &mip, &numLevels);

				if (it.first == _texture && mip == _mip)
				{
					return m_textureSamplersPool.m_numReservedTextures + BGFX_CONFIG_MAX_TEXTURES + i;
				}
			}

			BX_ASSERT(false, "Failed to find image.");
			return 0;
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
			uint8_t m_numSamples = 0;
			uint16_t numTargets = 0;
			uint16_t view = UINT16_MAX;
			uint16_t programIndex = kInvalidHandle;
			uint16_t frameBuffer = kInvalidHandle;
			uint32_t resolutionHeight = 0;
			float depthNear = 0.f;
			float depthFar = 0.f;
			Rect scissor;
			Rect viewScissor;

			PrimitiveInfo primitiveType;
			ViewState viewState;
			RenderDraw drawState;

			uint32_t bindState[BGFX_CONFIG_MAX_TEXTURE_SAMPLERS];
			uint32_t uniformBuffers[2][14]; // vertex/fragment stages, NVN_DEVICE_INFO_UNIFORM_BUFFER_BINDINGS_PER_STAGE

			CurrentState(Frame* _render)
				: viewState(_render)
			{
				drawState.clear();

				drawState.m_stateFlags = BGFX_STATE_NONE;
				drawState.m_stencil = packStencil(BGFX_STENCIL_NONE, BGFX_STENCIL_NONE);

				const uint64_t primType = _render->m_debug & BGFX_DEBUG_WIREFRAME ? BGFX_STATE_PT_LINES : 0;
				uint8_t primIndex = uint8_t(primType >> BGFX_STATE_PT_SHIFT);
				primitiveType = s_primitiveInfo[primIndex];

				memset(bindState, 0, sizeof(bindState));
				memset(uniformBuffers, 0xFF, sizeof(uniformBuffers));
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

		void setFrameBuffer(uint16_t _count, NVNtexture** _colors, NVNtexture* _depth, NVNtextureView** _colorViews, NVNtextureView* _depthView, uint8_t _numSamples)
		{
			for (uint16_t i = 0; i < BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS; ++i)
			{
				m_cmdList.m_currentColor[i] = (i < _count) ? _colors[i] : nullptr;
			}

			m_cmdList.m_currentDepth = _depth;

			if (m_state.m_numSamples != _numSamples)
			{
				NVNmultisampleState msaaState;
				nvnMultisampleStateSetDefaults(&msaaState);
				nvnMultisampleStateSetMultisampleEnable(&msaaState, _numSamples > 0);
				nvnMultisampleStateSetSamples(&msaaState, _numSamples);
				nvnCommandBufferBindMultisampleState(m_cmdList.get(), &msaaState);
				m_state.m_numSamples = _numSamples;
			}

			nvnCommandBufferBarrier(m_cmdList.get(), NVN_BARRIER_ORDER_FRAGMENTS_BIT);
			nvnCommandBufferSetRenderTargets(m_cmdList.get(), _count, m_cmdList.m_currentColor.data(), _colorViews, m_cmdList.m_currentDepth, _depthView);

			m_state.numTargets = _count;
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

					uint8_t numSamples = 0xFF;

					if (!isValid(fbh))
					{
						count = 1;
						targets[0] = &_backBuffer.m_color->m_ptr;
						views[0] = nullptr;
						depth = &_backBuffer.m_depth->m_ptr;
						depthView = nullptr;

						numSamples = _backBuffer.m_color->m_numSamples;

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
							BX_ASSERT(numSamples == 0xFF || numSamples == tex.m_numSamples, "Mismatched samples count.");
							numSamples = tex.m_numSamples;
						}

						if (isValid(fb.m_depthTarget))
						{
							TextureNVN& tex = m_resources.m_textures[fb.m_depthTarget.idx];
							depth = &tex.m_ptr;
							depthView = &fb.m_depthView;
							BX_ASSERT(numSamples == 0xFF || numSamples == tex.m_numSamples, "Mismatched samples count.");
						}

						if (numSamples == 0xFF)
						{
							numSamples = 0;
						}

						count = fb.m_numTargets;

						m_state.resolutionHeight = fb.m_height;
					}

					setFrameBuffer(count, targets.data(), depth, views.data(), depthView, numSamples);
				}

				m_state.view = _view;

				changed = true;
			}

			return changed;
		}

		void setViewport(const Rect& _vp, const Rect& _scissor)
		{
			std::array<float, 4 * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> viewportRects;
			std::array<int, 4 * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> scissorRects;

			int numTargets = bx::max(1, (int)m_state.numTargets);

			if (memcmp(&m_state.viewState.m_rect, &_vp, sizeof(Rect)) != 0)
			{
				m_state.viewState.m_rect = _vp;

				for (int i = 0; i < numTargets; ++i)
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
				m_state.viewScissor = scissor;

				for (int i = 0; i < numTargets; ++i)
				{
					int index = i * 4;
					scissorRects[index + 0] = scissor.m_x;
					scissorRects[index + 1] = m_state.resolutionHeight - scissor.m_height - scissor.m_y;
					scissorRects[index + 2] = scissor.m_width;
					scissorRects[index + 3] = scissor.m_height;
				}

				nvnCommandBufferSetScissors(m_cmdList.get(), 0, numTargets, scissorRects.data());
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

				if (src.m_numSamples)
				{
					BX_ASSERT(dst.m_numSamples == 0, "Blitting from multisampled texture to multisampled texture not supported.");
					nvnCommandBufferDownsample(m_cmdList.get(), &src.m_ptr, &dst.m_ptr);
				}
				else
				{
					nvnCommandBufferCopyTextureToTexture(m_cmdList.get(), &src.m_ptr, &srcView, &srcRegion, &dst.m_ptr, &dstView, &dstRegion, 0);
				}
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

			const bool blendEnable = !!(BGFX_STATE_BLEND_MASK & _state);
			const uint32_t blend = uint32_t((_state & BGFX_STATE_BLEND_MASK) >> BGFX_STATE_BLEND_SHIFT);
			const uint32_t equation = uint32_t((_state & BGFX_STATE_BLEND_EQUATION_MASK) >> BGFX_STATE_BLEND_EQUATION_SHIFT);

			const uint32_t srcRGB = blendEnable ? ((blend) & 0xf) : (BGFX_STATE_BLEND_ONE >> BGFX_STATE_BLEND_SHIFT);
			const uint32_t dstRGB = (blend >> 4) & 0xf;
			const uint32_t srcA = blendEnable ? ((blend >> 8) & 0xf) : (BGFX_STATE_BLEND_ONE >> BGFX_STATE_BLEND_SHIFT);;
			const uint32_t dstA = (blend >> 12) & 0xf;

			const uint32_t equRGB = (equation) & 0x7;
			const uint32_t equA = (equation >> 3) & 0x7;

			NVNboolean writeR = _state & BGFX_STATE_WRITE_R;
			NVNboolean writeG = _state & BGFX_STATE_WRITE_G;
			NVNboolean writeB = _state & BGFX_STATE_WRITE_B;
			NVNboolean writeA = _state & BGFX_STATE_WRITE_A;

			if (independentBlendEnable)
			{
				for (uint32_t ii = 1, rgba = _rgba; ii < m_state.numTargets; ++ii, rgba >>= 11)
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

				for (int ii = 0; ii < m_state.numTargets; ii++)
				{
					nvnColorStateSetBlendEnable(&colorState, ii, blendEnable);
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

		void _setScissor(Frame* _render, uint16_t _scissor)
		{
			const Rect& viewScissor = m_state.viewScissor;
			int numTargets = bx::max(1, (int)m_state.numTargets);

			std::array<int, 4 * BGFX_CONFIG_MAX_FRAME_BUFFER_ATTACHMENTS> scissorRects;

			if (_scissor == UINT16_MAX || _render == nullptr)
			{
				m_state.scissor = viewScissor;
			}
			else
			{
				m_state.scissor.setIntersect(viewScissor, _render->m_frameCache.m_rectCache.m_cache[_scissor]);
			}

			for (int i = 0; i < numTargets; ++i)
			{
				int index = i * 4;
				scissorRects[index + 0] = m_state.scissor.m_x;
				scissorRects[index + 1] = m_state.resolutionHeight - m_state.scissor.m_height - m_state.scissor.m_y;
				scissorRects[index + 2] = m_state.scissor.m_width;
				scissorRects[index + 3] = m_state.scissor.m_height;
			}

			nvnCommandBufferSetScissors(m_cmdList.get(), 0, numTargets, scissorRects.data());
		}

		void setRasterState(Frame* _render, const RenderDraw& _draw)
		{
			uint64_t state = _draw.m_stateFlags;
			uint64_t stencil = _draw.m_stencil;
			uint16_t scissor = _draw.m_scissor;

			bool stateChanged = m_state.drawState.m_stateFlags != state;
			bool stencilChanged = m_state.drawState.m_stencil != stencil;
			bool scissorChanged = m_state.drawState.m_scissor != scissor;

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

			if (scissorChanged)
			{
				_setScissor(_render, scissor);
			}

			m_state.drawState.m_stateFlags = state;
			m_state.drawState.m_stencil = stencil;
			m_state.drawState.m_scissor = scissor;
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
					nvnCommandBufferBindProgram(m_cmdList.get(), &program.m_program, program.m_stages);
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

				for (const ShaderNVN::UniformBufferBinding& binding : shaders[i]->m_constantBuffers)
				{
					if (binding.m_handle != UniformBufferRegistry::InvalidEntry)
					{
						ShaderUniformBuffer& ub = m_resources.m_uniformBuffers.get(binding.m_handle);

						bool bind = m_state.uniformBuffers[i][binding.m_slot] != binding.m_handle;

						ub.update(m_cmdList.get());

						if (bind)
						{
							nvnCommandBufferBindUniformBuffer(m_cmdList.get(), stages[i], binding.m_slot, ub.m_buffer->m_gpuAddress, ub.m_size);
						}

						m_state.uniformBuffers[i][binding.m_slot] = binding.m_handle;
					}
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
			case Binding::ShaderBuffer:
				addr = m_resources.m_shaderBuffers[_bind.m_idx].m_gpuAddress;
				size = m_resources.m_shaderBuffers[_bind.m_idx].m_size;
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
					bx::HashMurmur2A murmur;
					murmur.begin();
					murmur.add(&bind, sizeof(Binding));
					murmur.add(m_state.isCompute);
					uint32_t hash = murmur.end();

					if (m_state.bindState[i] != hash)
					{
						m_state.bindState[i] = hash;

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
						case Binding::ShaderBuffer:
							_bindBuffer(i, bind);
							break;
						default:
							break;
						}
					}
				}
			}
		}

		void setInputLayout(const uint8_t _numStreams, const VertexLayout** _layouts, const uint32_t _instanceDataStride)
		{
			const ProgramNVN& program = m_resources.m_program[m_state.programIndex];

			bx::HashMurmur2A murmur;
			murmur.begin();
			murmur.add(_instanceDataStride);
			for (uint8_t stream = 0; stream < _numStreams; ++stream)
			{
				murmur.add(_layouts[stream]->m_hash);
			}

			uint64_t layoutHash = (uint64_t(program.m_vsh->m_hash) << 32) | murmur.end();

			PipelineVboState* vboState = m_resources.getPipelineVboState(layoutHash);
			if (vboState == nullptr)
			{
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
								BX_ASSERT(false, "Exceeded the maximum number of vertex attributes (%d)", PipelineVboState::MaxAttributes);
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

					NVNvertexAttribState& vaState = vboState->m_attribStates[bindingIndex];
					nvnVertexAttribStateSetDefaults(&vaState);

					if (currentBinding.m_isSet)
					{
						nvnVertexAttribStateSetStreamIndex(&vaState, currentBinding.m_streamIndex);
						nvnVertexAttribStateSetFormat(&vaState, currentBinding.m_format, currentBinding.m_offset);
					}
				}

				BX_ASSERT((program.m_vsh->m_numInstanceData * 16) <= _instanceDataStride, "Instance buffer stride too small: expected %d found %d.", program.m_vsh->m_numInstanceData * 16, _instanceDataStride);

				if (program.m_vsh->m_numInstanceData > 0)
				{
					for (uint32_t inst = 0; inst < program.m_vsh->m_numInstanceData; ++inst)
					{
						uint8_t loc = program.m_vsh->m_instanceLoc[inst];
						NVNvertexAttribState& vaState = vboState->m_attribStates[loc];
						nvnVertexAttribStateSetStreamIndex(&vaState, _numStreams);
						nvnVertexAttribStateSetFormat(&vaState, NVN_FORMAT_RGBA32F, inst * 16);
					}

					NVNvertexStreamState& streamState = vboState->m_streamStates[vboState->m_numStreams];
					nvnVertexStreamStateSetDefaults(&streamState);
					nvnVertexStreamStateSetStride(&streamState, _instanceDataStride);
					nvnVertexStreamStateSetDivisor(&streamState, 1);
					vboState->m_numStreams++;
				}
			}

			BX_ASSERT(vboState != nullptr, "Invalid vbo state.");

			nvnCommandBufferBindVertexStreamState(m_cmdList.get(), vboState->m_numStreams, vboState->m_streamStates);
			nvnCommandBufferBindVertexAttribState(m_cmdList.get(), PipelineVboState::MaxAttributes, vboState->m_attribStates);
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

				uint32_t instStride = 0;
				if (isValid(_draw.m_instanceDataBuffer))
				{
					const VertexBufferNVN& inst = m_resources.m_vertexBuffers[_draw.m_instanceDataBuffer.idx];
					uint32_t instCount = _draw.m_numInstances;
					uint32_t instOffset = _draw.m_instanceDataOffset;
					instStride = _draw.m_instanceDataStride;
					buffers[numStreams] = { inst.m_gpuAddress + instOffset, instStride * instCount };
				}

				// this will set the current buffers and clear unused ones
				nvnCommandBufferBindVertexBuffers(m_cmdList.get(), 0, BGFX_CONFIG_MAX_VERTEX_STREAMS + 1, buffers);
				setInputLayout(numStreams, layouts, instStride);
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
				const PrimitiveInfo& prim = m_state.primitiveType;
				uint32_t numInstances = _draw.m_numInstances;
				uint32_t numVertices = m_state.drawState.m_numVertices;

				bool hasOcclusionQuery = 0 != (_draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);

				m_resources.m_drawStats.add(DrawStats::DispatchMesh, 1);
				m_resources.m_drawStats.m_primStats[m_state.primitiveType.m_type].numInstances += numInstances;

				if (hasOcclusionQuery)
				{
					m_resources.m_occlusionQuery.begin(m_cmdList.get(), m_render, _draw.m_occlusionQuery);
				}

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

					m_resources.m_drawStats.add(DrawStats::NumIndices, numIndices);

					int numPrimsSubmitted = numIndices / m_state.primitiveType.m_div - m_state.primitiveType.m_sub;
					int numPrimsRendered = numPrimsSubmitted * numInstances;

					m_resources.m_drawStats.m_primStats[m_state.primitiveType.m_type].numSubmitted += numPrimsSubmitted;
					m_resources.m_drawStats.m_primStats[m_state.primitiveType.m_type].numRendered += numPrimsRendered;

					NVNindexType indexType = m_cmdList.m_currentIndexBufferIndexType;
					NVNbufferAddress indexAddr = m_cmdList.m_currentIndexBufferAddress + (startIndex * indexSize);

					if (isValid(_draw.m_indirectBuffer))
					{
						VertexBufferNVN& vb = m_resources.m_vertexBuffers[_draw.m_indirectBuffer.idx];
						NVNbufferAddress indirectAddr = vb.m_gpuAddress + (_draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
						uint32_t numDrawIndirect = (UINT16_MAX == _draw.m_numIndirect) ? (vb.m_size / BGFX_CONFIG_DRAW_INDIRECT_STRIDE) : _draw.m_numIndirect;

						nvnCommandBufferBarrier(m_cmdList.get(), NVN_BARRIER_ORDER_INDIRECT_DATA_BIT);

						for (uint32_t i = 0; i < numDrawIndirect; ++i)
						{
							nvnCommandBufferDrawElementsIndirect(m_cmdList.get(), prim.m_typeNVN, indexType, indexAddr, indirectAddr + (i * BGFX_CONFIG_DRAW_INDIRECT_STRIDE));
						}

						m_resources.m_drawStats.m_primStats[m_state.primitiveType.m_type].numIndirect += numDrawIndirect;
					}
					else
					{
						nvnCommandBufferDrawElementsInstanced(m_cmdList.get(), prim.m_typeNVN, indexType, numIndices, indexAddr, 0, 0, numInstances);
					}
				}
				else
				{
					int numPrimsSubmitted = numVertices / m_state.primitiveType.m_div - m_state.primitiveType.m_sub;
					int numPrimsRendered = numPrimsSubmitted * numInstances;

					m_resources.m_drawStats.m_primStats[m_state.primitiveType.m_type].numSubmitted += numPrimsSubmitted;
					m_resources.m_drawStats.m_primStats[m_state.primitiveType.m_type].numRendered += numPrimsRendered;

					if (isValid(_draw.m_indirectBuffer))
					{
						VertexBufferNVN& vb = m_resources.m_vertexBuffers[_draw.m_indirectBuffer.idx];
						NVNbufferAddress indirectAddr = vb.m_gpuAddress + (_draw.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
						uint32_t numDrawIndirect = (UINT16_MAX == _draw.m_numIndirect) ? (vb.m_size / BGFX_CONFIG_DRAW_INDIRECT_STRIDE) : _draw.m_numIndirect;

						nvnCommandBufferBarrier(m_cmdList.get(), NVN_BARRIER_ORDER_INDIRECT_DATA_BIT);

						for (uint32_t i = 0; i < numDrawIndirect; ++i)
						{
							nvnCommandBufferDrawArraysIndirect(m_cmdList.get(), prim.m_typeNVN, indirectAddr + (i * BGFX_CONFIG_DRAW_INDIRECT_STRIDE));
						}

						m_resources.m_drawStats.m_primStats[m_state.primitiveType.m_type].numIndirect += numDrawIndirect;
					}
					else
					{
						nvnCommandBufferDrawArraysInstanced(m_cmdList.get(), prim.m_typeNVN, 0, numVertices, 0, numInstances);
					}
				}

				if (hasOcclusionQuery)
				{
					m_resources.m_occlusionQuery.end(m_cmdList.get());
				}
			}
		}

		void dispatch(const RenderCompute& _compute)
		{
			m_resources.m_drawStats.add(DrawStats::DispatchCompute, 1);

			if (isValid(_compute.m_indirectBuffer))
			{
				VertexBufferNVN& vb = m_resources.m_vertexBuffers[_compute.m_indirectBuffer.idx];
				NVNbufferAddress indirectAddr = vb.m_gpuAddress + (_compute.m_startIndirect * BGFX_CONFIG_DRAW_INDIRECT_STRIDE);
				uint32_t numIndirect = (UINT16_MAX == _compute.m_numIndirect) ? (vb.m_size / BGFX_CONFIG_DRAW_INDIRECT_STRIDE) : _compute.m_numIndirect;

				nvnCommandBufferBarrier(m_cmdList.get(), NVN_BARRIER_ORDER_INDIRECT_DATA_BIT);

				for (uint32_t i = 0; i < numIndirect; ++i)
				{
					nvnCommandBufferDispatchComputeIndirect(m_cmdList.get(), indirectAddr + (i * BGFX_CONFIG_DRAW_INDIRECT_STRIDE));
				}
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

		NVNdevice m_device;

		int m_maxAnisotropy = 1;
		int m_numFramesInFlight = BGFX_CONFIG_MAX_FRAME_LATENCY;
		int m_currentFrameInFlight = 0;

		ContextResources m_resources;

		SwapChainNVN m_swapChain;
		CommandQueueNVN m_queue;
		Commands* m_currentCommands = nullptr;

		NVNsync* m_previousFrameSync[BGFX_CONFIG_MAX_FRAME_LATENCY];
		uint64_t m_SubmitCounter = 0;

		std::vector<CopyOperation> m_copyOperations;
		std::vector<DeleteOperation> m_deleteOperations;

		TextVideoMem m_textVideoMem;

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
				| BGFX_CAPS_STRUCTURED_BUFFERS
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

			memset(m_previousFrameSync, 0, sizeof(m_previousFrameSync));
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

			if (severity < NVN_DEBUG_CALLBACK_SEVERITY_NOTIFICATION)
			{
				BX_ASSERT(false, "NVN Debug layer callback hit");
			}
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

			if (!nvnDeviceInitialize(&m_device, &deviceBuilder))
			{
				BX_ASSERT(false, "nvnDeviceInitialize");
				return false;
			}

			nvnLoadCProcs(&m_device, pfnc_nvnDeviceGetProcAddress);

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
					&m_device,
					reinterpret_cast<PFNNVNDEBUGCALLBACKPROC>(&debugLayerCallback),
					NULL, // For testing purposes; any pointer is OK here.
					NVN_TRUE // NVN_TRUE = Enable the callback.
				);
			}

			int apiMajor, apiMinor;
			nvnDeviceGetInteger(&m_device, NVN_DEVICE_INFO_API_MAJOR_VERSION, &apiMajor);
			nvnDeviceGetInteger(&m_device, NVN_DEVICE_INFO_API_MINOR_VERSION, &apiMinor);

			// do quick API version check? is that even necessary?

			nvnDeviceGetInteger(&m_device, NVN_DEVICE_INFO_MAX_TEXTURE_ANISOTROPY, &m_maxAnisotropy);

			return true;
		}

		void initializeMemoryPool()
		{
			m_resources.initPools(m_numFramesInFlight);
		}

		void initializeSwapChain(const Init& _init)
		{
			m_swapChain.create(m_numFramesInFlight, m_Hwnd, &m_device, _init.resolution, bgfx::TextureFormat::Enum::RGBA8, bgfx::TextureFormat::Enum::D24S8);
			m_queue.init(&m_device, &m_swapChain);
		}

		void initializeWindow(const Init& _init)
		{
#if 0
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
			g_allocatorNVN.init(BGFX_CONFIG_NVN_GRAPHICS_POOL_SIZE);

			m_Hwnd = (NVNnativeWindow)g_platformData.nwh;

			m_numFramesInFlight = (_init.resolution.maxFrameLatency == 0) ? BGFX_CONFIG_MAX_FRAME_LATENCY : bx::clamp((int)_init.resolution.maxFrameLatency, 1, BGFX_CONFIG_MAX_FRAME_LATENCY);
			m_currentFrameInFlight = 0;

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

			g_nvnDevice = &m_device;

			initializeMemoryPool();
			initializeSwapChain(_init);
			initializeWindow(_init);

			m_resources.m_gpuTimer.init();
			m_resources.m_occlusionQuery.init();

			memset(&m_resources.m_resolution, 0xFF, sizeof(Resolution));
			_updateResolution(_init.resolution);

			// Init reserved part of view name.
			for (uint32_t ii = 0; ii < BGFX_CONFIG_MAX_VIEWS; ++ii)
			{
				bx::snprintf(s_viewName[ii], BGFX_CONFIG_MAX_VIEW_NAME_RESERVED + 1, "%3d   ", ii);
			}

			for (int i = 0; i < BGFX_CONFIG_MAX_SHADERS; ++i)
			{
				s_shaderName[i][0] = '\0';
			}

			return true;
		}

		void shutdown()
		{
			m_resources.m_gpuTimer.destroy();
			m_resources.m_occlusionQuery.destroy();

			m_queue.shutdown();
			m_swapChain.destroy();

			m_resources.m_textureSamplersPool.shutdown();

			g_nvnDevice = NULL;
			nvnDeviceFinalize(&m_device);

			for (int i = 0; i < PredefinedUniform::Count; ++i)
			{
				UniformNVN& uniform = m_resources.m_uniformsPredefined[i];
				if (uniform.m_mem)
				{
					BX_FREE(&g_allocatorNVN, m_resources.m_uniformsPredefined[i].m_mem);
				}
			}

			g_allocatorNVN.release();
		}

		bool isDeviceRemoved() override
		{
			return false;
		}

		void flip() override
		{
			m_swapChain.present(&m_queue.m_GfxQueue);
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
			copyOp.m_data = (CopyOperation::Data*)BX_ALLOC(&g_allocatorNVN, sizeof(CopyOperation::Data));
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

			shader.create(&m_device, _mem, m_resources.m_uniformReg, m_resources.m_uniformBuffers);
			shader.m_name = s_shaderName[_handle.idx];

			// resolve uniform references in uniform buffers
			for (const ShaderNVN::UniformBufferBinding& binding : shader.m_constantBuffers)
			{
				ShaderUniformBuffer& cb = m_resources.m_uniformBuffers.get(binding.m_handle);
				for (ShaderUniformBuffer::UniformReference& uniformRef : cb.m_uniforms)
				{
					if (uniformRef.m_data == nullptr)
					{
						if ((uniformRef.m_predefined & ~kUniformFragmentBit) != PredefinedUniform::Enum::Count)
						{
							if (shader.m_numPredefined > 0)
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

									UniformNVN& uniform = m_resources.m_uniformsPredefined[uniformRef.m_predefined & ~kUniformFragmentBit];
									if (uniform.m_mem == nullptr)
									{
										uniform.m_loc = loc;
										uniform.m_mem = BX_ALLOC(&g_allocatorNVN, shader.m_predefined[predefined].m_count * 16);
									}

									uniform.m_references.push_back(&uniformRef);
									uniformRef.m_data = uniform.m_mem;
									uniformRef.m_dirtySize = uniformRef.m_count;
								}
							}
						}
						else
						{
							UniformNVN& uniform = m_resources.m_uniforms[uniformRef.m_handle.idx];
							auto it = std::find_if(uniform.m_references.begin(), uniform.m_references.end(), [&](const ShaderUniformBuffer::UniformReference* rhs)
							{
								return &uniformRef == rhs;
							});

							if (it == uniform.m_references.end())
							{
								uniform.m_references.push_back(&uniformRef);
							}

							uniformRef.m_data = uniform.m_mem;
							uniformRef.m_dirtySize = uniformRef.m_count;
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
			m_resources.m_program[_handle.idx].create(&m_device, isValid(_vsh) ? &m_resources.m_shaders[_vsh.idx] : nullptr, isValid(_fsh) ? &m_resources.m_shaders[_fsh.idx] : nullptr);
		}

		void destroyProgram(ProgramHandle _handle) override
		{
			m_resources.m_program[_handle.idx].destroy();
		}

		void* createTexture(TextureHandle _handle, const Memory* _mem, uint64_t _flags, uint8_t _skip) override
		{
			CopyOperation copyOp;
			m_resources.m_textures[_handle.idx].create(&m_device, _mem, _flags, _skip, copyOp);
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
			copyOp.m_data = (CopyOperation::Data*)BX_ALLOC(&g_allocatorNVN, sizeof(CopyOperation::Data));
			copyOp.createBuffer(size, copyOp.m_data);

			// populate src buffer
			uint8_t* dst = (uint8_t*)nvnBufferMap(&copyOp.m_data->m_buffer);

			if (convert)
			{
				bimg::imageDecodeToBgra8(&g_allocatorNVN, dst, _mem->data, _rect.m_width, _rect.m_height, rectpitch, bimg::TextureFormat::Enum(tex.m_requestedFormat));
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

			nvnBufferFlushMappedRange(&copyOp.m_data->m_buffer, 0, size);

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

		void createShaderBuffer(ShaderBufferHandle _handle, uint32_t _size, uint32_t _stride) override
		{
			m_resources.m_shaderBuffers[_handle.idx].create(_size, nullptr, 0, _stride, BufferNVN::Usage::GenericGpu);
		}

		void updateShaderBuffer(ShaderBufferHandle _handle, const Memory* _mem) override
		{
			BufferNVN& buffer = m_resources.m_shaderBuffers[_handle.idx];

			CopyOperation copyOp;
			copyOp.m_data = (CopyOperation::Data*)BX_ALLOC(&g_allocatorNVN, sizeof(CopyOperation::Data));
			copyOp.createBuffer(_mem->size, copyOp.m_data);

			// populate src buffer
			uint8_t* dst = (uint8_t*)nvnBufferMap(&copyOp.m_data->m_buffer);
			memcpy(dst, _mem->data, _mem->size);
			nvnBufferFlushMappedRange(&copyOp.m_data->m_buffer, 0, _mem->size);

			CopyOperation::Op op;
			op.m_type = CopyOperation::Op::Buffer;
			op.m_dstBuffer = buffer.m_gpuAddress;
			op.m_memSize = _mem->size;
			copyOp.m_ops.push_back(op);

			m_copyOperations.push_back(copyOp);
		}

		void destroyShaderBuffer(ShaderBufferHandle _handle) override
		{
			m_resources.m_shaderBuffers[_handle.idx].destroy();
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

		void markUniformDirty(const UniformNVN& _uniform, uint32_t _dirtySize)
		{
			for (ShaderUniformBuffer::UniformReference* uniformRef : _uniform.m_references)
			{
				uniformRef->m_dirtySize = bx::max(uniformRef->m_dirtySize, _dirtySize);
			}
		}

		void createUniform(UniformHandle _handle, UniformType::Enum _type, uint16_t _num, const char* _name) override
		{
			UniformNVN& uniform = m_resources.m_uniforms[_handle.idx];

			if (NULL != uniform.m_mem)
			{
				BX_FREE(&g_allocatorNVN, uniform.m_mem);
			}

			uint32_t size = nn::util::align_up(g_uniformTypeSize[_type] * _num, 16);
			void* data = BX_ALLOC(&g_allocatorNVN, size);
			bx::memSet(data, 0, size);
			uniform.m_mem = data;
			m_resources.m_uniformReg.add(_handle, _name);
		}

		void destroyUniform(UniformHandle _handle) override
		{
			BX_FREE(&g_allocatorNVN, m_resources.m_uniforms[_handle.idx].m_mem);
			m_resources.m_uniforms[_handle.idx].m_mem = NULL;
			m_resources.m_uniformReg.remove(_handle);
		}

		void setShaderUniform(uint8_t _flags, uint32_t _regIndex, const void* _val, uint32_t _numRegs)
		{
			UniformNVN& uniform = m_resources.m_uniformsPredefined[_flags & ~kUniformFragmentBit];
			if (uniform.m_mem != nullptr) // this will be nullptr for unreferenced uniforms, safe to ignore updates
			{
				memcpy(uniform.m_mem, _val, _numRegs * 16);
				markUniformDirty(uniform, _numRegs * 16);
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
			UniformNVN& uniform = m_resources.m_uniforms[_loc];
			memcpy(uniform.m_mem, _data, _size);
			markUniformDirty(uniform, _size);
		}

		void invalidateOcclusionQuery(OcclusionQueryHandle _handle) override
		{
			m_resources.m_occlusionQuery.invalidate(_handle);
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

		virtual void setName(Handle _handle, const char* _name, uint16_t _len) override
		{
			switch (_handle.type)
			{
			case Handle::IndexBuffer:
				nvnBufferSetDebugLabel(&m_resources.m_indexBuffers[_handle.idx].m_buffer, _name);
				break;
			case Handle::Shader:
				// NVN only provides debug label support for programs, not individual shaders
				strncpy(s_shaderName[_handle.idx], _name, bx::min(_len, uint16_t(BGFX_CONFIG_NVN_MAX_SHADER_NAME)));
				break;
			case Handle::Texture:
				nvnTextureSetDebugLabel(&m_resources.m_textures[_handle.idx].m_ptr, _name);
				break;
			case Handle::VertexBuffer:
				nvnBufferSetDebugLabel(&m_resources.m_vertexBuffers[_handle.idx].m_buffer, _name);
				break;
			default:
				BX_ASSERT(false, "Invalid handle type?! %d", _handle.type);
				break;
			}
		}

		void _processCopyOperations(CommandListNVN& _cmd, Frame* _render)
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
						BX_ALIGNED_FREE(&g_allocatorNVN, op.m_data->m_mem, NVN_MEMORY_POOL_STORAGE_ALIGNMENT);
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
				NVNcommandBuffer* cmdBuf = _cmd.get();

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

		bool _isVisible(Frame* _render, OcclusionQueryHandle _handle, bool _visible)
		{
			if (!isValid(_handle))
			{
				return true;
			}

			return _visible == (0 != _render->m_occlusion[_handle.idx]);
		}

		void _processItemCompute(Commands& _cmds, Frame* _render, const RenderCompute& _compute, const RenderBind& _bind)
		{
			BGFX_PROFILER_SCOPE("gfx::_processItemCompute", 0xff2040ff);

			ProgramNVN& program = m_resources.m_program[_cmds.m_state.programIndex];

			_cmds.m_state.viewState.setPredefined<4>(this, _cmds.m_state.view, program, _render, _compute);
			rendererUpdateUniforms(this, _render->m_uniformBuffer[_compute.m_uniformIdx], _compute.m_uniformBegin, _compute.m_uniformEnd);

			_cmds.bindUniformBuffers(program);
			_cmds.bindSamplers(_bind, _render->m_colorPalette);
			_cmds.dispatch(_compute);
		}

		void _processItemDraw(Commands& _cmds, Frame* _render, const RenderDraw& _draw, const RenderBind& _bind)
		{
			BGFX_PROFILER_SCOPE("gfx::_processItemDraw", 0xff2040ff);

			bool hasOcclusionQuery = 0 != (_draw.m_stateFlags & BGFX_STATE_INTERNAL_OCCLUSION_QUERY);

			bool occluded = true
				&& !hasOcclusionQuery
				&& !_isVisible(_render, _draw.m_occlusionQuery, 0 != (_draw.m_submitFlags & BGFX_SUBMIT_INTERNAL_OCCLUSION_VISIBLE))
				;

			if (!occluded)
			{
				ProgramNVN& program = m_resources.m_program[_cmds.m_state.programIndex];

				_cmds.setRasterState(_render, _draw);

				_cmds.m_state.viewState.setPredefined<4>(this, _cmds.m_state.view, program, _render, _draw);
				rendererUpdateUniforms(this, _render->m_uniformBuffer[_draw.m_uniformIdx], _draw.m_uniformBegin, _draw.m_uniformEnd);

				_cmds.bindUniformBuffers(program); // potentially update uniform buffers for this draw
				_cmds.bindSamplers(_bind, _render->m_colorPalette);
				_cmds.bindVertexBuffers(_draw);
				_cmds.bindIndexBuffer(_draw);
				_cmds.draw(_draw);
			}
		}

		void _processViewItems(Commands& cmds, Frame* _render, Profiler<TimerQueryNVN>& _profiler)
		{
			BGFX_PROFILER_SCOPE("gfx::_processViewItems", 0xff2040ff);

			CommandListNVN& cmd = cmds.m_cmdList;

			SortKey key;

			BackBuffer backBuffer = m_swapChain.get();

			std::array<NVNtexture*, 1> defaultTarget = { &backBuffer.m_color->m_ptr };
			cmds.setFrameBuffer(1, defaultTarget.data(), &backBuffer.m_depth->m_ptr, nullptr, nullptr, backBuffer.m_color->m_numSamples);

			int32_t numItems = _render->m_numRenderItems;
			for (int32_t item = 0, restartItem = numItems; item < numItems || restartItem < numItems;)
			{
				const uint64_t encodedKey = _render->m_sortKeys[item];

				cmds.m_state.isCompute = key.decode(encodedKey, _render->m_viewRemap);

				const uint32_t itemIdx = _render->m_sortValues[item];
				const RenderItem& renderItem = _render->m_renderItem[itemIdx];
				const RenderBind& renderBind = _render->m_renderItemBind[itemIdx];

				const View& view = _render->m_view[key.m_view];
				bool viewChanged = cmds.setView(_render, key.m_view, item == numItems, backBuffer);

				if (viewChanged)
				{
					if (item > 0)
					{
						nvnCommandBufferPopDebugGroup(cmds.m_cmdList.get());
						_profiler.end();
					}

					_profiler.begin(key.m_view);
					nvnCommandBufferPushDebugGroup(cmds.m_cmdList.get(), s_viewName[key.m_view]);

					cmds.processBlits(_render);
					cmds.setViewport(view.m_rect, view.m_scissor);
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

			if (numItems > 0)
			{
				nvnCommandBufferPopDebugGroup(cmds.m_cmdList.get());
				_profiler.end();
			}

			// reset back to the default backbuffer
			cmds.setFrameBuffer(1, defaultTarget.data(), &backBuffer.m_depth->m_ptr, nullptr, nullptr, backBuffer.m_color->m_numSamples);
		}

		bool _updateResolution(const Resolution& _resolution)
		{
			bool changed = false;

			if (m_resources.m_resolution.reset != _resolution.reset)
			{
				int interval = (_resolution.reset & BGFX_RESET_VSYNC) ? 1 : 0;
				nvnWindowSetPresentInterval(&m_swapChain.m_window, interval);
			}

			if (m_resources.m_resolution.width != _resolution.width || m_resources.m_resolution.height != _resolution.height)
			{
				BX_ASSERT(_resolution.width <= SwapChainNVN::MaxWidth, "Invalid width.");
				BX_ASSERT(_resolution.height <= SwapChainNVN::MaxHeight, "Invalid height.");

				m_textVideoMem.resize(false, _resolution.width, _resolution.height);
				m_textVideoMem.clear();
				nvnWindowSetCrop(&m_swapChain.m_window, 0, 0, _resolution.width, _resolution.height);

				changed = true;
			}

			m_resources.m_resolution = _resolution;

			return changed;
		}

		void _waitForGpu()
		{
			{
				BGFX_PROFILER_SCOPE("gfx::acquireNextScanBuffer", 0xff2040ff);

				m_swapChain.acquireNext();
			}

			{
				BGFX_PROFILER_SCOPE("gfx::waitForPreviousFrame", 0xff2040ff);

				if (m_previousFrameSync[m_currentFrameInFlight] != nullptr)
				{
					m_queue.finish(m_previousFrameSync[m_currentFrameInFlight]);
					m_previousFrameSync[m_currentFrameInFlight] = nullptr;
				}
			}
		}

		void _drawDebugStats(CommandListNVN& _cmdList, Frame* _render, TextVideoMemBlitter& _textVideoMemBlitter, const Profiler<TimerQueryNVN>& _profiler)
		{
			TextVideoMem& tvm = m_textVideoMem;

			tvm.clear();
			uint16_t pos = 0;
			tvm.printf(0, pos++, BGFX_CONFIG_DEBUG ? 0x8c : 0x8f
				, " %s / " BX_COMPILER_NAME
				  " / " BX_CPU_NAME
				  " / " BX_ARCH_NAME
				  " / " BX_PLATFORM_NAME
				  " / Version 1.%d.%d (commit: " BGFX_REV_SHA1 ")"
				, getRendererName()
				, BGFX_API_VERSION
				, BGFX_REV_NUMBER
			);

			pos = 8;

			const uint32_t msaa = (m_resources.m_resolution.reset & BGFX_RESET_MSAA_MASK) >> BGFX_RESET_MSAA_SHIFT;
			tvm.printf(10, pos++, 0x8b, "  Reset flags: [%c] vsync, [%c] MSAAx%d, [%c] MaxAnisotropy "
				, !!(m_resources.m_resolution.reset & BGFX_RESET_VSYNC) ? '\xfe' : ' '
				, 0 != msaa ? '\xfe' : ' '
				, 1 << msaa
				, !!(m_resources.m_resolution.reset & BGFX_RESET_MAXANISOTROPY) ? '\xfe' : ' '
			);

			tvm.printf(10, pos++, 0x8b, "    Submitted: %5d (draw %5d, compute %4d) "
				, _render->m_numRenderItems
				, m_resources.m_drawStats.get(DrawStats::DispatchMesh)
				, m_resources.m_drawStats.get(DrawStats::DispatchCompute)
			);

			for (uint32_t ii = 0; ii < Topology::Count; ++ii)
			{
				tvm.printf(10, pos++, 0x8b, "   %10s: %7d (#inst: %5d), submitted: %7d, indirect %7d"
					, getName(Topology::Enum(ii))
					, m_resources.m_drawStats.m_primStats[ii].numRendered
					, m_resources.m_drawStats.m_primStats[ii].numInstances
					, m_resources.m_drawStats.m_primStats[ii].numSubmitted
					, m_resources.m_drawStats.m_primStats[ii].numIndirect
				);
			}

			char memFreeTotal[16];
			bx::prettify(memFreeTotal, BX_COUNTOF(memFreeTotal), g_allocatorNVN.m_totalFree);

			char memFreeLargest[16];
			bx::prettify(memFreeLargest, BX_COUNTOF(memFreeLargest), g_allocatorNVN.m_largestFree);

			char memHighwater[16];
			bx::prettify(memHighwater, BX_COUNTOF(memHighwater), g_allocatorNVN.m_highwater);

			size_t cmdListMetrics[6] =
			{
				0,
				0,
				BGFX_CONFIG_NVN_COMMAND_BUFFER_COMMAND_SIZE,
				0,
				0,
				BGFX_CONFIG_NVN_COMMAND_BUFFER_CONTROL_SIZE
			};
			_cmdList.getUsage(cmdListMetrics[0], cmdListMetrics[3], cmdListMetrics[1], cmdListMetrics[4]);
			char cmdListUsage[6][16];
			for (int i = 0; i < 6; ++i)
			{
				bx::prettify(cmdListUsage[i], BX_COUNTOF(cmdListUsage[0]), cmdListMetrics[i]);
			}

			tvm.printf(10, pos++, 0x8b, "      Indices: %7d ", m_resources.m_drawStats.get(DrawStats::NumIndices));
			tvm.printf(10, pos++, 0x8b, "     DVB size: %7d ", _render->m_vboffset);
			tvm.printf(10, pos++, 0x8b, "     DIB size: %7d ", _render->m_iboffset);
			tvm.printf(10, pos++, 0x8b, "     Mem free: %s [%s] - HW %s", memFreeTotal, memFreeLargest, memHighwater);
			tvm.printf(10, pos++, 0x8b, " Command list: %s / %s [%s] - %s / %s [%s]", cmdListUsage[0], cmdListUsage[2], cmdListUsage[1], cmdListUsage[3], cmdListUsage[5], cmdListUsage[4]);

			if (_profiler.m_enabled)
			{
				pos++;

				float cpuTotal = 0.f;
				float gpuTotal = 0.f;

				tvm.printf(10, pos++, 0x89, "%37s", "View Stats");

				for (int i = 0; i < _profiler.m_numViews; ++i)
				{
					const auto& viewStat = _render->m_perfStats.viewStats[i];
					int64_t cpuElapsed = viewStat.cpuTimeEnd - viewStat.cpuTimeBegin;
					int64_t gpuElapsed = viewStat.gpuTimeEnd - viewStat.gpuTimeBegin;

					float cpuTime = (float)(double(cpuElapsed) * 1000.0 / bx::getHPFrequency());
					float gpuTime = (float)(double(gpuElapsed) * 1000.0 / m_resources.m_gpuTimer.m_frequency);

					cpuTotal += cpuTime;
					gpuTotal += gpuTime;

					tvm.printf(10, pos++, 0x8b, "%16s: CPU %5.2f GPU %5.2f", s_viewName[viewStat.view], cpuTime, gpuTime);
				}

				tvm.printf(10, pos++, 0x8f, "%16s: CPU %5.2f GPU %5.2f", "Total", cpuTotal, gpuTotal);
			}
		}

		void submit(Frame* _render, ClearQuad& _clearQuad, TextVideoMemBlitter& _textVideoMemBlitter) override
		{
			BGFX_PROFILER_SCOPE("gfx::submit", 0xff2040ff);

			BX_UNUSED(_clearQuad);

			if (_updateResolution(_render->m_resolution))
			{
				// recreate swap chain?
			}

			_render->sort();

			int64_t timeBegin = 0;
			int64_t timeEnd = 0;

			m_resources.m_drawStats.reset();

			size_t cmdUsageCommand = 0;
			size_t cmdUsageControl = 0;
			size_t cmdHwCommand = 0;
			size_t cmdHwControl = 0;

			if (0 == (_render->m_debug & BGFX_DEBUG_IFH))
			{
				_waitForGpu();

				timeBegin = bx::getHPCounter();

				CommandListNVN& cmd = *m_queue.alloc("submit");
				Commands cmds(cmd, _render, m_resources);
				m_currentCommands = &cmds;

				Profiler<TimerQueryNVN> profiler(_render, m_resources.m_gpuTimer, s_viewName, true);
				uint32_t frameQueryIdx = m_resources.m_gpuTimer.begin(BGFX_CONFIG_MAX_VIEWS);

				m_resources.m_textureSamplersPool.bind(cmd.get());

				_processCopyOperations(cmd, _render);
				_processViewItems(cmds, _render, profiler);

				if (_render->m_debug & BGFX_DEBUG_STATS)
				{
					_drawDebugStats(cmd, _render, _textVideoMemBlitter, profiler);
					blit(this, _textVideoMemBlitter, &m_textVideoMem);
				}
				else if (_render->m_debug & BGFX_DEBUG_TEXT)
				{
					blit(this, _textVideoMemBlitter, _render->m_textVideoMem);
				}

				m_swapChain.resolve(cmd.get(), m_resources.m_resolution);

				m_resources.m_gpuTimer.end(frameQueryIdx);

				m_currentCommands = nullptr;
				m_previousFrameSync[m_currentFrameInFlight] = m_queue.kick();

				cmds.m_cmdList.getUsage(cmdUsageCommand, cmdUsageControl, cmdHwCommand, cmdHwControl);

				timeEnd = bx::getHPCounter();
			}

			int64_t frameTime = timeEnd - timeBegin;
			int64_t timerFreq = bx::getHPFrequency();

			const TimerQueryNVN::Result& result = m_resources.m_gpuTimer.m_result[BGFX_CONFIG_MAX_VIEWS];

			Stats& perfStats = _render->m_perfStats;
			perfStats.cpuTimeBegin = timeBegin;
			perfStats.cpuTimeEnd = timeEnd;
			perfStats.cpuTimerFreq = timerFreq;
			perfStats.gpuTimeBegin = result.m_begin;
			perfStats.gpuTimeEnd = result.m_end;
			perfStats.gpuTimerFreq = m_resources.m_gpuTimer.m_frequency;
			perfStats.numDraw = m_resources.m_drawStats.get(DrawStats::DispatchMesh);
			perfStats.numCompute = m_resources.m_drawStats.get(DrawStats::DispatchCompute);
			perfStats.numBlit = _render->m_numBlitItems;
			perfStats.maxGpuLatency = 0; // maxGpuLatency;
			perfStats.gpuMemoryMax = g_allocatorNVN.m_size;
			perfStats.gpuMemoryUsed = g_allocatorNVN.m_size - g_allocatorNVN.m_totalFree;
			for (int i = 0; i < Topology::Count; ++i)
			{
				perfStats.numPrims[i] = m_resources.m_drawStats.m_primStats[i].numRendered;
			}

			m_SubmitCounter++;
			m_currentFrameInFlight = (m_currentFrameInFlight + 1) % m_numFramesInFlight;
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

			cmds.setRasterState(nullptr, draw);
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

	//
	//
	//

	bool TimerQueryNVN::init()
	{
		m_buffer.create(m_control.m_size * 2 * kQueryStride, nullptr, 0, 0, BufferNVN::Usage::GenericGpu);

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_result); ++ii)
		{
			m_result[ii].reset();
		}

		m_control.reset();

		// timestamps are converted to nanoseconds, so just need conversion from nanoseconds to seconds
		m_frequency = 1000000000;

		return true;
	}

	void TimerQueryNVN::destroy()
	{
		m_buffer.destroy();
	}

	uint32_t TimerQueryNVN::begin(uint32_t _resultIdx)
	{
		while (0 == m_control.reserve(1))
		{
			m_control.consume(1);
		}

		Result& result = m_result[_resultIdx];
		++result.m_pending;

		const uint32_t idx = m_control.m_current;
		Query& query = m_query[idx];
		query.m_resultIdx = _resultIdx;
		query.m_ready = false;

		uint32_t offset = (idx * 2) + 0;
		nvnCommandBufferReportCounter(s_renderNVN->m_currentCommands->m_cmdList.get(), NVN_COUNTER_TYPE_TIMESTAMP, m_buffer.m_gpuAddress + (offset * kQueryStride));

		m_control.commit(1);

		return idx;
	}

	void TimerQueryNVN::end(uint32_t _idx)
	{
		uint32_t offset = (_idx * 2) + 1;
		nvnCommandBufferReportCounter(s_renderNVN->m_currentCommands->m_cmdList.get(), NVN_COUNTER_TYPE_TIMESTAMP, m_buffer.m_gpuAddress + (offset * kQueryStride));

		Query& query = m_query[_idx];
		query.m_ready = true;
		query.m_completed = s_renderNVN->m_SubmitCounter + s_renderNVN->m_numFramesInFlight;

		update();
	}

	void TimerQueryNVN::update()
	{
		while (m_control.available() != 0)
		{
			uint32_t idx = m_control.m_read;
			Query& query = m_query[idx];

			if (!query.m_ready)
			{
				break;
			}

			if (query.m_completed > s_renderNVN->m_SubmitCounter)
			{
				break;
			}

			m_control.consume(1);

			Result& result = m_result[query.m_resultIdx];
			--result.m_pending;

			int offset = idx * 2;

			nvnBufferInvalidateMappedRange(&m_buffer.m_buffer, offset * kQueryStride, kQueryStride * 2);
			NVNcounterData* queries = (NVNcounterData*)nvnBufferMap(&m_buffer.m_buffer);
			result.m_begin = nvnDeviceGetTimestampInNanoseconds(g_nvnDevice, &queries[offset + 0]);
			result.m_end = nvnDeviceGetTimestampInNanoseconds(g_nvnDevice, &queries[offset + 1]);
		}
	}

	//
	//
	//

	void OutOfCommandBufferMemoryEventCallback(NVNcommandBuffer* cmdBuf,
		NVNcommandBufferMemoryEvent event,
		size_t minSize,
		void* callbackData)
	{
		switch (event)
		{
		case NVNcommandBufferMemoryEvent::NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_COMMAND_MEMORY:
			BX_ASSERT(false, "Out of command buffer command memory. Increase BGFX_CONFIG_NVN_COMMAND_BUFFER_COMMAND_SIZE.");
			break;
		case NVNcommandBufferMemoryEvent::NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_CONTROL_MEMORY:
			BX_ASSERT(false, "Out of command buffer control memory. Increase BGFX_CONFIG_NVN_COMMAND_BUFFER_CONTROL_SIZE.");
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
