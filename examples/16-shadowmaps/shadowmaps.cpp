/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <string>
#include <vector>
#include <algorithm>

#include "common.h"
#include "bgfx_utils.h"

#include <bgfx/bgfx.h>
#include <bx/timer.h>
#include <bx/math.h>
#include <bx/file.h>
#include "entry/entry.h"
#include "camera.h"
#include "imgui/imgui.h"

namespace bgfx
{
	int32_t read(bx::ReaderI* _reader, bgfx::VertexDecl& _decl, bx::Error* _err = NULL);
}

namespace
{

#define RENDERVIEW_SHADOWMAP_0_ID 1
#define RENDERVIEW_SHADOWMAP_1_ID 2
#define RENDERVIEW_SHADOWMAP_2_ID 3
#define RENDERVIEW_SHADOWMAP_3_ID 4
#define RENDERVIEW_SHADOWMAP_4_ID 5
#define RENDERVIEW_VBLUR_0_ID     6
#define RENDERVIEW_HBLUR_0_ID     7
#define RENDERVIEW_VBLUR_1_ID     8
#define RENDERVIEW_HBLUR_1_ID     9
#define RENDERVIEW_VBLUR_2_ID     10
#define RENDERVIEW_HBLUR_2_ID     11
#define RENDERVIEW_VBLUR_3_ID     12
#define RENDERVIEW_HBLUR_3_ID     13
#define RENDERVIEW_DRAWSCENE_0_ID 14
#define RENDERVIEW_DRAWSCENE_1_ID 15
#define RENDERVIEW_DRAWDEPTH_0_ID 16
#define RENDERVIEW_DRAWDEPTH_1_ID 17
#define RENDERVIEW_DRAWDEPTH_2_ID 18
#define RENDERVIEW_DRAWDEPTH_3_ID 19

struct LightType
{
	enum Enum
	{
		SpotLight,
		PointLight,
		DirectionalLight,

		Count
	};

};

struct DepthImpl
{
	enum Enum
	{
		InvZ,
		Linear,

		Count
	};
};

struct PackDepth
{
	enum Enum
	{
		RGBA,
		VSM,

		Count
	};
};

struct SmImpl
{
	enum Enum
	{
		Hard,
		PCF,
		VSM,
		ESM,

		Count
	};
};

struct SmType
{
	enum Enum
	{
		Single,
		Omni,
		Cascade,

		Count
	};
};

struct TetrahedronFaces
{
	enum Enum
	{
		Green,
		Yellow,
		Blue,
		Red,

		Count
	};
};

struct ProjType
{
	enum Enum
	{
		Horizontal,
		Vertical,

		Count
	};
};

struct ShadowMapRenderTargets
{
	enum Enum
	{
		First,
		Second,
		Third,
		Fourth,

		Count
	};
};

struct PosNormalTexcoordVertex
{
	float    m_x;
	float    m_y;
	float    m_z;
	uint32_t m_normal;
	float    m_u;
	float    m_v;
};

static const float s_texcoord = 5.0f;
static PosNormalTexcoordVertex s_hplaneVertices[] =
{
	{ -1.0f, 0.0f,  1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f), s_texcoord, s_texcoord },
	{  1.0f, 0.0f,  1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f), s_texcoord, 0.0f       },
	{ -1.0f, 0.0f, -1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f), 0.0f,       s_texcoord },
	{  1.0f, 0.0f, -1.0f, encodeNormalRgba8(0.0f, 1.0f, 0.0f), 0.0f,       0.0f       },
};

static PosNormalTexcoordVertex s_vplaneVertices[] =
{
	{ -1.0f,  1.0f, 0.0f, encodeNormalRgba8(0.0f, 0.0f, -1.0f), 1.0f, 1.0f },
	{  1.0f,  1.0f, 0.0f, encodeNormalRgba8(0.0f, 0.0f, -1.0f), 1.0f, 0.0f },
	{ -1.0f, -1.0f, 0.0f, encodeNormalRgba8(0.0f, 0.0f, -1.0f), 0.0f, 1.0f },
	{  1.0f, -1.0f, 0.0f, encodeNormalRgba8(0.0f, 0.0f, -1.0f), 0.0f, 0.0f },
};

static const uint16_t s_planeIndices[] =
{
	0, 1, 2,
	1, 3, 2,
};

static bool s_flipV = false;
static float s_texelHalf = 0.0f;

static bgfx::UniformHandle s_texColor;
static bgfx::UniformHandle s_shadowMap[ShadowMapRenderTargets::Count];
static bgfx::FrameBufferHandle s_rtShadowMap[ShadowMapRenderTargets::Count];
static bgfx::FrameBufferHandle s_rtBlur;

void mtxBillboard(float* __restrict _result
				  , const float* __restrict _view
				  , const float* __restrict _pos
				  , const float* __restrict _scale)
{
	_result[ 0] = _view[0]  * _scale[0];
	_result[ 1] = _view[4]  * _scale[0];
	_result[ 2] = _view[8]  * _scale[0];
	_result[ 3] = 0.0f;
	_result[ 4] = _view[1]  * _scale[1];
	_result[ 5] = _view[5]  * _scale[1];
	_result[ 6] = _view[9]  * _scale[1];
	_result[ 7] = 0.0f;
	_result[ 8] = _view[2]  * _scale[2];
	_result[ 9] = _view[6]  * _scale[2];
	_result[10] = _view[10] * _scale[2];
	_result[11] = 0.0f;
	_result[12] = _pos[0];
	_result[13] = _pos[1];
	_result[14] = _pos[2];
	_result[15] = 1.0f;
}

void mtxYawPitchRoll(float* __restrict _result
		            , float _yaw
		            , float _pitch
		            , float _roll
		            )
{
	float sroll  = bx::sin(_roll);
	float croll  = bx::cos(_roll);
	float spitch = bx::sin(_pitch);
	float cpitch = bx::cos(_pitch);
	float syaw   = bx::sin(_yaw);
	float cyaw   = bx::cos(_yaw);

	_result[ 0] = sroll * spitch * syaw + croll * cyaw;
	_result[ 1] = sroll * cpitch;
	_result[ 2] = sroll * spitch * cyaw - croll * syaw;
	_result[ 3] = 0.0f;
	_result[ 4] = croll * spitch * syaw - sroll * cyaw;
	_result[ 5] = croll * cpitch;
	_result[ 6] = croll * spitch * cyaw + sroll * syaw;
	_result[ 7] = 0.0f;
	_result[ 8] = cpitch * syaw;
	_result[ 9] = -spitch;
	_result[10] = cpitch * cyaw;
	_result[11] = 0.0f;
	_result[12] = 0.0f;
	_result[13] = 0.0f;
	_result[14] = 0.0f;
	_result[15] = 1.0f;
}

struct Material
{
	union Ambient
	{
		struct
		{
			float m_r;
			float m_g;
			float m_b;
			float m_unused;
		};

		float m_v[4];
	};

	union Diffuse
	{
		struct
		{
			float m_r;
			float m_g;
			float m_b;
			float m_unused;
		};

		float m_v[4];
	};

	union Specular
	{
		struct
		{
			float m_r;
			float m_g;
			float m_b;
			float m_ns;
		};

		float m_v[4];
	};

	Ambient m_ka;
	Diffuse m_kd;
	Specular m_ks;
};

struct Light
{
	union Position
	{
		struct
		{
			float m_x;
			float m_y;
			float m_z;
			float m_w;
		};

		float m_v[4];
	};

	union LightRgbPower
	{
		struct
		{
			float m_r;
			float m_g;
			float m_b;
			float m_power;
		};

		float m_v[4];
	};

	union SpotDirectionInner
	{
		struct
		{
			float m_x;
			float m_y;
			float m_z;
			float m_inner;
		};

		float m_v[4];
	};

	union AttenuationSpotOuter
	{
		struct
		{
			float m_attnConst;
			float m_attnLinear;
			float m_attnQuadrantic;
			float m_outer;
		};

		float m_v[4];
	};

	void computeViewSpaceComponents(float* _viewMtx)
	{
		bx::vec4MulMtx(m_position_viewSpace, m_position.m_v, _viewMtx);

		float tmp[] =
		{
			  m_spotDirectionInner.m_x
			, m_spotDirectionInner.m_y
			, m_spotDirectionInner.m_z
			, 0.0f
		};
		bx::vec4MulMtx(m_spotDirectionInner_viewSpace, tmp, _viewMtx);
		m_spotDirectionInner_viewSpace[3] = m_spotDirectionInner.m_v[3];
	}

	Position              m_position;
	float				  m_position_viewSpace[4];
	LightRgbPower         m_ambientPower;
	LightRgbPower         m_diffusePower;
	LightRgbPower         m_specularPower;
	SpotDirectionInner    m_spotDirectionInner;
	float				  m_spotDirectionInner_viewSpace[4];
	AttenuationSpotOuter  m_attenuationSpotOuter;
};

struct Uniforms
{
	void init()
	{
		m_ambientPass    = 1.0f;
		m_lightingPass   = 1.0f;

		m_shadowMapBias   = 0.003f;
		m_shadowMapOffset = 0.0f;
		m_shadowMapParam0 = 0.5;
		m_shadowMapParam1 = 1.0;
		m_depthValuePow   = 1.0f;
		m_showSmCoverage  = 1.0f;
		m_shadowMapTexelSize = 1.0f/512.0f;

		m_csmFarDistances[0] = 30.0f;
		m_csmFarDistances[1] = 90.0f;
		m_csmFarDistances[2] = 180.0f;
		m_csmFarDistances[3] = 1000.0f;

		m_tetraNormalGreen[0] = 0.0f;
		m_tetraNormalGreen[1] = -0.57735026f;
		m_tetraNormalGreen[2] = 0.81649661f;

		m_tetraNormalYellow[0] = 0.0f;
		m_tetraNormalYellow[1] = -0.57735026f;
		m_tetraNormalYellow[2] = -0.81649661f;

		m_tetraNormalBlue[0] = -0.81649661f;
		m_tetraNormalBlue[1] = 0.57735026f;
		m_tetraNormalBlue[2] = 0.0f;

		m_tetraNormalRed[0] = 0.81649661f;
		m_tetraNormalRed[1] = 0.57735026f;
		m_tetraNormalRed[2] = 0.0f;

		m_XNum = 2.0f;
		m_YNum = 2.0f;
		m_XOffset = 10.0f/512.0f;
		m_YOffset = 10.0f/512.0f;

		u_params0          = bgfx::createUniform("u_params0",          bgfx::UniformType::Vec4);
		u_params1          = bgfx::createUniform("u_params1",          bgfx::UniformType::Vec4);
		u_params2          = bgfx::createUniform("u_params2",          bgfx::UniformType::Vec4);
		u_color            = bgfx::createUniform("u_color",            bgfx::UniformType::Vec4);
		u_smSamplingParams = bgfx::createUniform("u_smSamplingParams", bgfx::UniformType::Vec4);
		u_csmFarDistances  = bgfx::createUniform("u_csmFarDistances",  bgfx::UniformType::Vec4);
		u_lightMtx         = bgfx::createUniform("u_lightMtx",         bgfx::UniformType::Mat4);

		u_tetraNormalGreen  = bgfx::createUniform("u_tetraNormalGreen",  bgfx::UniformType::Vec4);
		u_tetraNormalYellow = bgfx::createUniform("u_tetraNormalYellow", bgfx::UniformType::Vec4);
		u_tetraNormalBlue   = bgfx::createUniform("u_tetraNormalBlue",   bgfx::UniformType::Vec4);
		u_tetraNormalRed    = bgfx::createUniform("u_tetraNormalRed",    bgfx::UniformType::Vec4);

		u_shadowMapMtx0 = bgfx::createUniform("u_shadowMapMtx0", bgfx::UniformType::Mat4);
		u_shadowMapMtx1 = bgfx::createUniform("u_shadowMapMtx1", bgfx::UniformType::Mat4);
		u_shadowMapMtx2 = bgfx::createUniform("u_shadowMapMtx2", bgfx::UniformType::Mat4);
		u_shadowMapMtx3 = bgfx::createUniform("u_shadowMapMtx3", bgfx::UniformType::Mat4);

		u_lightPosition             = bgfx::createUniform("u_lightPosition",              bgfx::UniformType::Vec4);
		u_lightAmbientPower         = bgfx::createUniform("u_lightAmbientPower",          bgfx::UniformType::Vec4);
		u_lightDiffusePower         = bgfx::createUniform("u_lightDiffusePower",          bgfx::UniformType::Vec4);
		u_lightSpecularPower        = bgfx::createUniform("u_lightSpecularPower",         bgfx::UniformType::Vec4);
		u_lightSpotDirectionInner   = bgfx::createUniform("u_lightSpotDirectionInner",    bgfx::UniformType::Vec4);
		u_lightAttenuationSpotOuter = bgfx::createUniform("u_lightAttenuationSpotOuter",  bgfx::UniformType::Vec4);

		u_materialKa = bgfx::createUniform("u_materialKa", bgfx::UniformType::Vec4);
		u_materialKd = bgfx::createUniform("u_materialKd", bgfx::UniformType::Vec4);
		u_materialKs = bgfx::createUniform("u_materialKs", bgfx::UniformType::Vec4);

	}

	void setPtrs(Material* _materialPtr, Light* _lightPtr, float* _colorPtr, float* _lightMtxPtr, float* _shadowMapMtx0, float* _shadowMapMtx1, float* _shadowMapMtx2, float* _shadowMapMtx3)
	{
		m_lightMtxPtr = _lightMtxPtr;
		m_colorPtr    = _colorPtr;
		m_materialPtr = _materialPtr;
		m_lightPtr    = _lightPtr;

		m_shadowMapMtx0 = _shadowMapMtx0;
		m_shadowMapMtx1 = _shadowMapMtx1;
		m_shadowMapMtx2 = _shadowMapMtx2;
		m_shadowMapMtx3 = _shadowMapMtx3;
	}

	// Call this once at initialization.
	void submitConstUniforms()
	{
		bgfx::setUniform(u_tetraNormalGreen,  m_tetraNormalGreen);
		bgfx::setUniform(u_tetraNormalYellow, m_tetraNormalYellow);
		bgfx::setUniform(u_tetraNormalBlue,   m_tetraNormalBlue);
		bgfx::setUniform(u_tetraNormalRed,    m_tetraNormalRed);
	}

	// Call this once per frame.
	void submitPerFrameUniforms()
	{
		bgfx::setUniform(u_params1, m_params1);
		bgfx::setUniform(u_params2, m_params2);
		bgfx::setUniform(u_smSamplingParams, m_paramsBlur);
		bgfx::setUniform(u_csmFarDistances, m_csmFarDistances);

		bgfx::setUniform(u_materialKa, &m_materialPtr->m_ka);
		bgfx::setUniform(u_materialKd, &m_materialPtr->m_kd);
		bgfx::setUniform(u_materialKs, &m_materialPtr->m_ks);

		bgfx::setUniform(u_lightPosition,             &m_lightPtr->m_position_viewSpace);
		bgfx::setUniform(u_lightAmbientPower,         &m_lightPtr->m_ambientPower);
		bgfx::setUniform(u_lightDiffusePower,         &m_lightPtr->m_diffusePower);
		bgfx::setUniform(u_lightSpecularPower,        &m_lightPtr->m_specularPower);
		bgfx::setUniform(u_lightSpotDirectionInner,   &m_lightPtr->m_spotDirectionInner_viewSpace);
		bgfx::setUniform(u_lightAttenuationSpotOuter, &m_lightPtr->m_attenuationSpotOuter);
	}

	// Call this before each draw call.
	void submitPerDrawUniforms()
	{
		bgfx::setUniform(u_shadowMapMtx0, m_shadowMapMtx0);
		bgfx::setUniform(u_shadowMapMtx1, m_shadowMapMtx1);
		bgfx::setUniform(u_shadowMapMtx2, m_shadowMapMtx2);
		bgfx::setUniform(u_shadowMapMtx3, m_shadowMapMtx3);

		bgfx::setUniform(u_params0,  m_params0);
		bgfx::setUniform(u_lightMtx, m_lightMtxPtr);
		bgfx::setUniform(u_color,    m_colorPtr);
	}

	void destroy()
	{
		bgfx::destroy(u_params0);
		bgfx::destroy(u_params1);
		bgfx::destroy(u_params2);
		bgfx::destroy(u_color);
		bgfx::destroy(u_smSamplingParams);
		bgfx::destroy(u_csmFarDistances);

		bgfx::destroy(u_materialKa);
		bgfx::destroy(u_materialKd);
		bgfx::destroy(u_materialKs);

		bgfx::destroy(u_tetraNormalGreen);
		bgfx::destroy(u_tetraNormalYellow);
		bgfx::destroy(u_tetraNormalBlue);
		bgfx::destroy(u_tetraNormalRed);

		bgfx::destroy(u_shadowMapMtx0);
		bgfx::destroy(u_shadowMapMtx1);
		bgfx::destroy(u_shadowMapMtx2);
		bgfx::destroy(u_shadowMapMtx3);

		bgfx::destroy(u_lightMtx);
		bgfx::destroy(u_lightPosition);
		bgfx::destroy(u_lightAmbientPower);
		bgfx::destroy(u_lightDiffusePower);
		bgfx::destroy(u_lightSpecularPower);
		bgfx::destroy(u_lightSpotDirectionInner);
		bgfx::destroy(u_lightAttenuationSpotOuter);
	}

	union
	{
		struct
		{
			float m_ambientPass;
			float m_lightingPass;
			float m_unused00;
			float m_unused01;
		};

		float m_params0[4];
	};

	union
	{
		struct
		{
			float m_shadowMapBias;
			float m_shadowMapOffset;
			float m_shadowMapParam0;
			float m_shadowMapParam1;
		};

		float m_params1[4];
	};

	union
	{
		struct
		{
			float m_depthValuePow;
			float m_showSmCoverage;
			float m_shadowMapTexelSize;
			float m_unused23;
		};

		float m_params2[4];
	};

	union
	{
		struct
		{
			float m_XNum;
			float m_YNum;
			float m_XOffset;
			float m_YOffset;
		};

		float m_paramsBlur[4];
	};

	float m_tetraNormalGreen[3];
	float m_tetraNormalYellow[3];
	float m_tetraNormalBlue[3];
	float m_tetraNormalRed[3];
	float m_csmFarDistances[4];

	float* m_lightMtxPtr;
	float* m_colorPtr;
	Light* m_lightPtr;
	float* m_shadowMapMtx0;
	float* m_shadowMapMtx1;
	float* m_shadowMapMtx2;
	float* m_shadowMapMtx3;
	Material* m_materialPtr;

private:
	bgfx::UniformHandle u_params0;
	bgfx::UniformHandle u_params1;
	bgfx::UniformHandle u_params2;
	bgfx::UniformHandle u_color;
	bgfx::UniformHandle u_smSamplingParams;
	bgfx::UniformHandle u_csmFarDistances;

	bgfx::UniformHandle u_materialKa;
	bgfx::UniformHandle u_materialKd;
	bgfx::UniformHandle u_materialKs;

	bgfx::UniformHandle u_tetraNormalGreen;
	bgfx::UniformHandle u_tetraNormalYellow;
	bgfx::UniformHandle u_tetraNormalBlue;
	bgfx::UniformHandle u_tetraNormalRed;

	bgfx::UniformHandle u_shadowMapMtx0;
	bgfx::UniformHandle u_shadowMapMtx1;
	bgfx::UniformHandle u_shadowMapMtx2;
	bgfx::UniformHandle u_shadowMapMtx3;

	bgfx::UniformHandle u_lightMtx;
	bgfx::UniformHandle u_lightPosition;
	bgfx::UniformHandle u_lightAmbientPower;
	bgfx::UniformHandle u_lightDiffusePower;
	bgfx::UniformHandle u_lightSpecularPower;
	bgfx::UniformHandle u_lightSpotDirectionInner;
	bgfx::UniformHandle u_lightAttenuationSpotOuter;
};
static Uniforms s_uniforms;

struct RenderState
{
	enum Enum
	{
		Default = 0,

		ShadowMap_PackDepth,
		ShadowMap_PackDepthHoriz,
		ShadowMap_PackDepthVert,

		Custom_BlendLightTexture,
		Custom_DrawPlaneBottom,

		Count
	};

	uint64_t m_state;
	uint32_t m_blendFactorRgba;
	uint32_t m_fstencil;
	uint32_t m_bstencil;
};

static RenderState s_renderStates[RenderState::Count] =
{
	{ // Default
		0
		| BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // ShadowMap_PackDepth
		0
		| BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // ShadowMap_PackDepthHoriz
		0
		| BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_TEST_EQUAL
		| BGFX_STENCIL_FUNC_REF(1)
		| BGFX_STENCIL_FUNC_RMASK(0xff)
		| BGFX_STENCIL_OP_FAIL_S_KEEP
		| BGFX_STENCIL_OP_FAIL_Z_KEEP
		| BGFX_STENCIL_OP_PASS_Z_KEEP
		, BGFX_STENCIL_NONE
	},
	{ // ShadowMap_PackDepthVert
		0
		| BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_TEST_EQUAL
		| BGFX_STENCIL_FUNC_REF(0)
		| BGFX_STENCIL_FUNC_RMASK(0xff)
		| BGFX_STENCIL_OP_FAIL_S_KEEP
		| BGFX_STENCIL_OP_FAIL_Z_KEEP
		| BGFX_STENCIL_OP_PASS_Z_KEEP
		, BGFX_STENCIL_NONE
	},
	{ // Custom_BlendLightTexture
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_COLOR, BGFX_STATE_BLEND_INV_SRC_COLOR)
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // Custom_DrawPlaneBottom
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_CULL_CW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
};

struct ViewState
{
	ViewState(uint16_t _width = 1280, uint16_t _height = 720)
		: m_width(_width)
		, m_height(_height)
	{
	}

	uint16_t m_width;
	uint16_t m_height;

	float m_view[16];
	float m_proj[16];
};

struct ClearValues
{
	ClearValues(uint32_t _clearRgba  = 0x30303000
		, float    _clearDepth       = 1.0f
		, uint8_t  _clearStencil     = 0
		)
		: m_clearRgba(_clearRgba)
		, m_clearDepth(_clearDepth)
		, m_clearStencil(_clearStencil)
	{
	}

	uint32_t m_clearRgba;
	float    m_clearDepth;
	uint8_t  m_clearStencil;
};

struct Aabb
{
	float m_min[3];
	float m_max[3];
};

struct Obb
{
	float m_mtx[16];
};

struct Sphere
{
	float m_center[3];
	float m_radius;
};

struct Primitive
{
	uint32_t m_startIndex;
	uint32_t m_numIndices;
	uint32_t m_startVertex;
	uint32_t m_numVertices;

	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
};

typedef std::vector<Primitive> PrimitiveArray;

struct Group
{
	Group()
	{
		reset();
	}

	void reset()
	{
		m_vbh.idx = bgfx::kInvalidHandle;
		m_ibh.idx = bgfx::kInvalidHandle;
		m_prims.clear();
	}

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
	PrimitiveArray m_prims;
};

struct Mesh
{
	void load(const void* _vertices, uint32_t _numVertices, const bgfx::VertexDecl _decl, const uint16_t* _indices, uint32_t _numIndices)
	{
		Group group;
		const bgfx::Memory* mem;
		uint32_t size;

		size = _numVertices*_decl.getStride();
		mem = bgfx::makeRef(_vertices, size);
		group.m_vbh = bgfx::createVertexBuffer(mem, _decl);

		size = _numIndices*2;
		mem = bgfx::makeRef(_indices, size);
		group.m_ibh = bgfx::createIndexBuffer(mem);

		m_groups.push_back(group);
	}

	void load(const char* _filePath)
	{
#define BGFX_CHUNK_MAGIC_VB  BX_MAKEFOURCC('V', 'B', ' ', 0x1)
#define BGFX_CHUNK_MAGIC_IB  BX_MAKEFOURCC('I', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_PRI BX_MAKEFOURCC('P', 'R', 'I', 0x0)

		bx::FileReaderI* reader = entry::getFileReader();
		bx::open(reader, _filePath);

		Group group;

		uint32_t chunk;
		while (4 == bx::read(reader, chunk) )
		{
			switch (chunk)
			{
			case BGFX_CHUNK_MAGIC_VB:
				{
					bx::read(reader, group.m_sphere);
					bx::read(reader, group.m_aabb);
					bx::read(reader, group.m_obb);

					bgfx::read(reader, m_decl);
					uint16_t stride = m_decl.getStride();

					uint16_t numVertices;
					bx::read(reader, numVertices);
					const bgfx::Memory* mem = bgfx::alloc(numVertices*stride);
					bx::read(reader, mem->data, mem->size);

					group.m_vbh = bgfx::createVertexBuffer(mem, m_decl);
				}
				break;

			case BGFX_CHUNK_MAGIC_IB:
				{
					uint32_t numIndices;
					bx::read(reader, numIndices);
					const bgfx::Memory* mem = bgfx::alloc(numIndices*2);
					bx::read(reader, mem->data, mem->size);
					group.m_ibh = bgfx::createIndexBuffer(mem);
				}
				break;

			case BGFX_CHUNK_MAGIC_PRI:
				{
					uint16_t len;
					bx::read(reader, len);

					std::string material;
					material.resize(len);
					bx::read(reader, const_cast<char*>(material.c_str() ), len);

					uint16_t num;
					bx::read(reader, num);

					for (uint32_t ii = 0; ii < num; ++ii)
					{
						bx::read(reader, len);

						std::string name;
						name.resize(len);
						bx::read(reader, const_cast<char*>(name.c_str() ), len);

						Primitive prim;
						bx::read(reader, prim.m_startIndex);
						bx::read(reader, prim.m_numIndices);
						bx::read(reader, prim.m_startVertex);
						bx::read(reader, prim.m_numVertices);
						bx::read(reader, prim.m_sphere);
						bx::read(reader, prim.m_aabb);
						bx::read(reader, prim.m_obb);

						group.m_prims.push_back(prim);
					}

					m_groups.push_back(group);
					group.reset();
				}
				break;

			default:
				DBG("%08x at %d", chunk, bx::seek(reader) );
				break;
			}
		}

		bx::close(reader);
	}

	void unload()
	{
		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;
			bgfx::destroy(group.m_vbh);

			if (bgfx::kInvalidHandle != group.m_ibh.idx)
			{
				bgfx::destroy(group.m_ibh);
			}
		}
		m_groups.clear();
	}

	void submit(uint8_t _viewId, float* _mtx, bgfx::ProgramHandle _program, const RenderState& _renderState, bool _submitShadowMaps = false)
	{
		bgfx::TextureHandle texture = BGFX_INVALID_HANDLE;
		submit(_viewId, _mtx, _program, _renderState, texture, _submitShadowMaps);
	}

	void submit(uint8_t _viewId, float* _mtx, bgfx::ProgramHandle _program, const RenderState& _renderState, bgfx::TextureHandle _texture, bool _submitShadowMaps = false)
	{
		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;

			// Set uniforms.
			s_uniforms.submitPerDrawUniforms();

			// Set model matrix for rendering.
			bgfx::setTransform(_mtx);
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(0, group.m_vbh);

			// Set textures.
			if (bgfx::kInvalidHandle != _texture.idx)
			{
				bgfx::setTexture(0, s_texColor, _texture);
			}

			if (_submitShadowMaps)
			{
				for (uint8_t ii = 0; ii < ShadowMapRenderTargets::Count; ++ii)
				{
					bgfx::setTexture(4 + ii, s_shadowMap[ii], bgfx::getTexture(s_rtShadowMap[ii]) );
				}
			}

			// Apply render state.
			bgfx::setStencil(_renderState.m_fstencil, _renderState.m_bstencil);
			bgfx::setState(_renderState.m_state, _renderState.m_blendFactorRgba);

			// Submit.
			bgfx::submit(_viewId, _program);
		}
	}

	bgfx::VertexDecl m_decl;
	typedef std::vector<Group> GroupArray;
	GroupArray m_groups;
};

struct PosColorTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_rgba;
	float m_u;
	float m_v;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorTexCoord0Vertex::ms_decl;

void screenSpaceQuad(float _textureWidth, float _textureHeight, bool _originBottomLeft = true, float _width = 1.0f, float _height = 1.0f)
{
	if (3 == bgfx::getAvailTransientVertexBuffer(3, PosColorTexCoord0Vertex::ms_decl) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosColorTexCoord0Vertex::ms_decl);
		PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)vb.data;

		const float zz = 0.0f;

		const float minx = -_width;
		const float maxx =  _width;
		const float miny = 0.0f;
		const float maxy = _height*2.0f;

		const float texelHalfW = s_texelHalf/_textureWidth;
		const float texelHalfH = s_texelHalf/_textureHeight;
		const float minu = -1.0f + texelHalfW;
		const float maxu =  1.0f + texelHalfW;

		float minv = texelHalfH;
		float maxv = 2.0f + texelHalfH;

		if (_originBottomLeft)
		{
			std::swap(minv, maxv);
			minv -= 1.0f;
			maxv -= 1.0f;
		}

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_z = zz;
		vertex[0].m_rgba = 0xffffffff;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = zz;
		vertex[1].m_rgba = 0xffffffff;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = zz;
		vertex[2].m_rgba = 0xffffffff;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		bgfx::setVertexBuffer(0, &vb);
	}
}

void worldSpaceFrustumCorners(float* _corners24f
	, float _near
	, float _far
	, float _projWidth
	, float _projHeight
	, const float* __restrict _invViewMtx
	)
{
	// Define frustum corners in view space.
	const float nw = _near * _projWidth;
	const float nh = _near * _projHeight;
	const float fw = _far  * _projWidth;
	const float fh = _far  * _projHeight;

	const uint8_t numCorners = 8;
	const float corners[numCorners][3] =
	{
		{ -nw,  nh, _near },
		{  nw,  nh, _near },
		{  nw, -nh, _near },
		{ -nw, -nh, _near },
		{ -fw,  fh, _far  },
		{  fw,  fh, _far  },
		{  fw, -fh, _far  },
		{ -fw, -fh, _far  },
	};

	// Convert them to world space.
	float (*out)[3] = (float(*)[3])_corners24f;
	for (uint8_t ii = 0; ii < numCorners; ++ii)
	{
		bx::vec3MulMtx( (float*)&out[ii], (float*)&corners[ii], _invViewMtx);
	}
}

/**
 * _splits = { near0, far0, near1, far1... nearN, farN }
 * N = _numSplits
 */
void splitFrustum(float* _splits, uint8_t _numSplits, float _near, float _far, float _splitWeight = 0.75f)
{
	const float l = _splitWeight;
	const float ratio = _far/_near;
	const int8_t numSlices = _numSplits*2;
	const float numSlicesf = float(numSlices);

	// First slice.
	_splits[0] = _near;

	for (uint8_t nn = 2, ff = 1; nn < numSlices; nn+=2, ff+=2)
	{
		float si = float(int8_t(ff) ) / numSlicesf;

		const float nearp = l*(_near*bx::pow(ratio, si) ) + (1 - l)*(_near + (_far - _near)*si);
		_splits[nn] = nearp;          //near
		_splits[ff] = nearp * 1.005f; //far from previous split
	}

	// Last slice.
	_splits[numSlices-1] = _far;
}

struct Programs
{
	void init()
	{
		// Misc.
		m_black        = loadProgram("vs_shadowmaps_color",         "fs_shadowmaps_color_black");
		m_texture      = loadProgram("vs_shadowmaps_texture",       "fs_shadowmaps_texture");
		m_colorTexture = loadProgram("vs_shadowmaps_color_texture", "fs_shadowmaps_color_texture");

		// Blur.
		m_vBlur[PackDepth::RGBA] = loadProgram("vs_shadowmaps_vblur", "fs_shadowmaps_vblur");
		m_hBlur[PackDepth::RGBA] = loadProgram("vs_shadowmaps_hblur", "fs_shadowmaps_hblur");
		m_vBlur[PackDepth::VSM]  = loadProgram("vs_shadowmaps_vblur", "fs_shadowmaps_vblur_vsm");
		m_hBlur[PackDepth::VSM]  = loadProgram("vs_shadowmaps_hblur", "fs_shadowmaps_hblur_vsm");

		// Draw depth.
		m_drawDepth[PackDepth::RGBA] = loadProgram("vs_shadowmaps_unpackdepth", "fs_shadowmaps_unpackdepth");
		m_drawDepth[PackDepth::VSM]  = loadProgram("vs_shadowmaps_unpackdepth", "fs_shadowmaps_unpackdepth_vsm");

		// Pack depth.
		m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] = loadProgram("vs_shadowmaps_packdepth", "fs_shadowmaps_packdepth");
		m_packDepth[DepthImpl::InvZ][PackDepth::VSM]  = loadProgram("vs_shadowmaps_packdepth", "fs_shadowmaps_packdepth_vsm");

		m_packDepth[DepthImpl::Linear][PackDepth::RGBA] = loadProgram("vs_shadowmaps_packdepth_linear", "fs_shadowmaps_packdepth_linear");
		m_packDepth[DepthImpl::Linear][PackDepth::VSM]  = loadProgram("vs_shadowmaps_packdepth_linear", "fs_shadowmaps_packdepth_vsm_linear");

		// Color lighting.
		m_colorLighting[SmType::Single][DepthImpl::InvZ][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lighting", "fs_shadowmaps_color_lighting_hard");
		m_colorLighting[SmType::Single][DepthImpl::InvZ][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lighting", "fs_shadowmaps_color_lighting_pcf");
		m_colorLighting[SmType::Single][DepthImpl::InvZ][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lighting", "fs_shadowmaps_color_lighting_vsm");
		m_colorLighting[SmType::Single][DepthImpl::InvZ][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lighting", "fs_shadowmaps_color_lighting_esm");

		m_colorLighting[SmType::Single][DepthImpl::Linear][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lighting_linear", "fs_shadowmaps_color_lighting_hard_linear");
		m_colorLighting[SmType::Single][DepthImpl::Linear][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lighting_linear", "fs_shadowmaps_color_lighting_pcf_linear");
		m_colorLighting[SmType::Single][DepthImpl::Linear][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lighting_linear", "fs_shadowmaps_color_lighting_vsm_linear");
		m_colorLighting[SmType::Single][DepthImpl::Linear][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lighting_linear", "fs_shadowmaps_color_lighting_esm_linear");

		m_colorLighting[SmType::Omni][DepthImpl::InvZ][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lighting_omni", "fs_shadowmaps_color_lighting_hard_omni");
		m_colorLighting[SmType::Omni][DepthImpl::InvZ][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lighting_omni", "fs_shadowmaps_color_lighting_pcf_omni");
		m_colorLighting[SmType::Omni][DepthImpl::InvZ][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lighting_omni", "fs_shadowmaps_color_lighting_vsm_omni");
		m_colorLighting[SmType::Omni][DepthImpl::InvZ][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lighting_omni", "fs_shadowmaps_color_lighting_esm_omni");

		m_colorLighting[SmType::Omni][DepthImpl::Linear][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lighting_linear_omni", "fs_shadowmaps_color_lighting_hard_linear_omni");
		m_colorLighting[SmType::Omni][DepthImpl::Linear][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lighting_linear_omni", "fs_shadowmaps_color_lighting_pcf_linear_omni");
		m_colorLighting[SmType::Omni][DepthImpl::Linear][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lighting_linear_omni", "fs_shadowmaps_color_lighting_vsm_linear_omni");
		m_colorLighting[SmType::Omni][DepthImpl::Linear][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lighting_linear_omni", "fs_shadowmaps_color_lighting_esm_linear_omni");

		m_colorLighting[SmType::Cascade][DepthImpl::InvZ][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lighting_csm", "fs_shadowmaps_color_lighting_hard_csm");
		m_colorLighting[SmType::Cascade][DepthImpl::InvZ][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lighting_csm", "fs_shadowmaps_color_lighting_pcf_csm");
		m_colorLighting[SmType::Cascade][DepthImpl::InvZ][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lighting_csm", "fs_shadowmaps_color_lighting_vsm_csm");
		m_colorLighting[SmType::Cascade][DepthImpl::InvZ][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lighting_csm", "fs_shadowmaps_color_lighting_esm_csm");

		m_colorLighting[SmType::Cascade][DepthImpl::Linear][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lighting_linear_csm", "fs_shadowmaps_color_lighting_hard_linear_csm");
		m_colorLighting[SmType::Cascade][DepthImpl::Linear][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lighting_linear_csm", "fs_shadowmaps_color_lighting_pcf_linear_csm");
		m_colorLighting[SmType::Cascade][DepthImpl::Linear][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lighting_linear_csm", "fs_shadowmaps_color_lighting_vsm_linear_csm");
		m_colorLighting[SmType::Cascade][DepthImpl::Linear][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lighting_linear_csm", "fs_shadowmaps_color_lighting_esm_linear_csm");
	}

	void destroy()
	{
		// Color lighting.
		for (uint8_t ii = 0; ii < SmType::Count; ++ii)
		{
			for (uint8_t jj = 0; jj < DepthImpl::Count; ++jj)
			{
				for (uint8_t kk = 0; kk < SmImpl::Count; ++kk)
				{
					bgfx::destroy(m_colorLighting[ii][jj][kk]);
				}
			}
		}

		// Pack depth.
		for (uint8_t ii = 0; ii < DepthImpl::Count; ++ii)
		{
			for (uint8_t jj = 0; jj < PackDepth::Count; ++jj)
			{
				bgfx::destroy(m_packDepth[ii][jj]);
			}
		}

		// Draw depth.
		for (uint8_t ii = 0; ii < PackDepth::Count; ++ii)
		{
			bgfx::destroy(m_drawDepth[ii]);
		}

		// Hblur.
		for (uint8_t ii = 0; ii < PackDepth::Count; ++ii)
		{
			bgfx::destroy(m_hBlur[ii]);
		}

		// Vblur.
		for (uint8_t ii = 0; ii < PackDepth::Count; ++ii)
		{
			bgfx::destroy(m_vBlur[ii]);
		}

		// Misc.
		bgfx::destroy(m_colorTexture);
		bgfx::destroy(m_texture);
		bgfx::destroy(m_black);
	}

	bgfx::ProgramHandle m_black;
	bgfx::ProgramHandle m_texture;
	bgfx::ProgramHandle m_colorTexture;
	bgfx::ProgramHandle m_vBlur[PackDepth::Count];
	bgfx::ProgramHandle m_hBlur[PackDepth::Count];
	bgfx::ProgramHandle m_drawDepth[PackDepth::Count];
	bgfx::ProgramHandle m_packDepth[DepthImpl::Count][PackDepth::Count];
	bgfx::ProgramHandle m_colorLighting[SmType::Count][DepthImpl::Count][SmImpl::Count];
};

static Programs s_programs;

struct ShadowMapSettings
{
#define IMGUI_FLOAT_PARAM(_name) float _name, _name##Min, _name##Max, _name##Step
	IMGUI_FLOAT_PARAM(m_sizePwrTwo);
	IMGUI_FLOAT_PARAM(m_depthValuePow);
	IMGUI_FLOAT_PARAM(m_near);
	IMGUI_FLOAT_PARAM(m_far);
	IMGUI_FLOAT_PARAM(m_bias);
	IMGUI_FLOAT_PARAM(m_normalOffset);
	IMGUI_FLOAT_PARAM(m_customParam0);
	IMGUI_FLOAT_PARAM(m_customParam1);
	IMGUI_FLOAT_PARAM(m_xNum);
	IMGUI_FLOAT_PARAM(m_yNum);
	IMGUI_FLOAT_PARAM(m_xOffset);
	IMGUI_FLOAT_PARAM(m_yOffset);
	bool m_doBlur;
	bgfx::ProgramHandle* m_progPack;
	bgfx::ProgramHandle* m_progDraw;
#undef IMGUI_FLOAT_PARAM
};

struct SceneSettings
{
	LightType::Enum m_lightType;
	DepthImpl::Enum m_depthImpl;
	SmImpl::Enum m_smImpl;
	float m_spotOuterAngle;
	float m_spotInnerAngle;
	float m_fovXAdjust;
	float m_fovYAdjust;
	float m_coverageSpotL;
	float m_splitDistribution;
	int   m_numSplits;
	bool m_updateLights;
	bool m_updateScene;
	bool m_drawDepthBuffer;
	bool m_showSmCoverage;
	bool m_stencilPack;
	bool m_stabilize;
};

class ExampleShadowmaps : public entry::AppI
{
public:
	ExampleShadowmaps(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_debug = BGFX_DEBUG_NONE;
		m_reset = BGFX_RESET_VSYNC;

		m_width  = _width;
		m_height = _height;
		m_viewState = ViewState(uint16_t(m_width), uint16_t(m_height));
		m_clearValues = ClearValues(0x00000000, 1.0f, 0);

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_viewState.m_width, m_viewState.m_height, m_reset);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Setup root path for binary shaders. Shader binaries are different
		// for each renderer.
		switch (bgfx::getRendererType() )
		{
			case bgfx::RendererType::Direct3D9:
				s_texelHalf = 0.5f;
				break;

			case bgfx::RendererType::OpenGL:
			case bgfx::RendererType::OpenGLES:
				s_flipV = true;
				break;

			default:
				break;
		}

		// Imgui.
		imguiCreate();

		// Uniforms.
		s_uniforms.init();
		s_texColor = bgfx::createUniform("s_texColor",  bgfx::UniformType::Int1);
		s_shadowMap[0] = bgfx::createUniform("s_shadowMap0", bgfx::UniformType::Int1);
		s_shadowMap[1] = bgfx::createUniform("s_shadowMap1", bgfx::UniformType::Int1);
		s_shadowMap[2] = bgfx::createUniform("s_shadowMap2", bgfx::UniformType::Int1);
		s_shadowMap[3] = bgfx::createUniform("s_shadowMap3", bgfx::UniformType::Int1);

		// Programs.
		s_programs.init();

		// Vertex declarations.
		bgfx::VertexDecl PosNormalTexcoordDecl;
		PosNormalTexcoordDecl.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();

		m_posDecl.begin();
		m_posDecl.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float);
		m_posDecl.end();

		PosColorTexCoord0Vertex::init();

		// Textures.
		m_texFigure     = loadTexture("textures/figure-rgba.dds");
		m_texFlare      = loadTexture("textures/flare.dds");
		m_texFieldstone = loadTexture("textures/fieldstone-rgba.dds");

		// Meshes.
		m_bunnyMesh.load("meshes/bunny.bin");
		m_treeMesh.load("meshes/tree.bin");
		m_cubeMesh.load("meshes/cube.bin");
		m_hollowcubeMesh.load("meshes/hollowcube.bin");
		m_hplaneMesh.load(s_hplaneVertices, BX_COUNTOF(s_hplaneVertices), PosNormalTexcoordDecl, s_planeIndices, BX_COUNTOF(s_planeIndices) );
		m_vplaneMesh.load(s_vplaneVertices, BX_COUNTOF(s_vplaneVertices), PosNormalTexcoordDecl, s_planeIndices, BX_COUNTOF(s_planeIndices) );

		// Materials.
		m_defaultMaterial =
		{
			{ { 1.0f, 1.0f, 1.0f, 0.0f } }, //ambient
			{ { 1.0f, 1.0f, 1.0f, 0.0f } }, //diffuse
			{ { 1.0f, 1.0f, 1.0f, 0.0f } }, //specular, exponent
		};

		// Lights.
		m_pointLight =
		{
			{ { 0.0f, 0.0f, 0.0f, 1.0f   } }, //position
			{   0.0f, 0.0f, 0.0f, 0.0f     }, //-ignore
			{ { 1.0f, 1.0f, 1.0f, 0.0f   } }, //ambient
			{ { 1.0f, 1.0f, 1.0f, 850.0f } }, //diffuse
			{ { 1.0f, 1.0f, 1.0f, 0.0f   } }, //specular
			{ { 0.0f,-0.4f,-0.6f, 0.0f   } }, //spotdirection, spotexponent
			{   0.0f, 0.0f, 0.0f, 0.0f     }, //-ignore
			{ { 1.0f, 0.0f, 1.0f, 91.0f  } }, //attenuation, spotcutoff
		};

		m_directionalLight =
		{
			{ { 0.5f,-1.0f, 0.1f, 0.0f  } }, //position
			{   0.0f, 0.0f, 0.0f, 0.0f    }, //-ignore
			{ { 1.0f, 1.0f, 1.0f, 0.02f } }, //ambient
			{ { 1.0f, 1.0f, 1.0f, 0.4f  } }, //diffuse
			{ { 1.0f, 1.0f, 1.0f, 0.0f  } }, //specular
			{ { 0.0f, 0.0f, 0.0f, 1.0f  } }, //spotdirection, spotexponent
			{   0.0f, 0.0f, 0.0f, 0.0f    }, //-ignore
			{ { 0.0f, 0.0f, 0.0f, 1.0f  } }, //attenuation, spotcutoff
		};

		// Setup uniforms.
		m_color[0] = m_color[1] = m_color[2] = m_color[3] = 1.0f;
		s_uniforms.setPtrs(&m_defaultMaterial
						   , &m_pointLight
						   , m_color
						   , m_lightMtx
						   , &m_shadowMapMtx[ShadowMapRenderTargets::First][0]
						   , &m_shadowMapMtx[ShadowMapRenderTargets::Second][0]
						   , &m_shadowMapMtx[ShadowMapRenderTargets::Third][0]
						   , &m_shadowMapMtx[ShadowMapRenderTargets::Fourth][0]
						   );
		s_uniforms.submitConstUniforms();

		// Settings.
		ShadowMapSettings smSettings[LightType::Count][DepthImpl::Count][SmImpl::Count] =
		{
			{ //LightType::Spot

				{ //DepthImpl::InvZ

					{ //SmImpl::Hard
						10.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 10.0f, 1.0f, 20.0f, 1.0f         // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.0035f, 0.0f, 0.01f, 0.00001f   // m_bias
						, 0.0012f, 0.0f, 0.05f, 0.00001f   // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 500.0f, 1.0f, 1000.0f, 1.0f      // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Single][DepthImpl::InvZ][SmImpl::Hard] //m_progDraw
					},
					{ //SmImpl::PCF
						10.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 10.0f, 1.0f, 20.0f, 1.0f         // m_depthValuePow
						, 1.0f, 1.0f, 99.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.007f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 500.0f, 1.0f, 1000.0f, 1.0f      // m_customParam1
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Single][DepthImpl::InvZ][SmImpl::PCF] //m_progDraw
					},
					{ //SmImpl::VSM
						10.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 10.0f, 1.0f, 20.0f, 1.0f         // m_depthValuePow
						, 8.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.045f, 0.0f, 0.1f, 0.00001f     // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.02f, 0.0f, 0.04f, 0.00001f     // m_customParam0
						, 450.0f, 1.0f, 1000.0f, 1.0f      // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::VSM] //m_progPack
						, &s_programs.m_colorLighting[SmType::Single][DepthImpl::InvZ][SmImpl::VSM] //m_progDraw
					},
					{ //SmImpl::ESM
						10.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 10.0f, 1.0f, 20.0f, 1.0f         // m_depthValuePow
						, 3.0f, 1.0f, 10.0f, 0.01f         // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.02f, 0.0f, 0.3f, 0.00001f      // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 9000.0f, 1.0f, 15000.0f, 1.0f    // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Single][DepthImpl::InvZ][SmImpl::ESM] //m_progDraw
					}

				},
				{ //DepthImpl::Linear

					{ //SmImpl::Hard
						10.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.0025f, 0.0f, 0.01f, 0.00001f   // m_bias
						, 0.0012f, 0.0f, 0.05f, 0.00001f   // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 500.0f, 1.0f, 1000.0f, 1.0f      // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Single][DepthImpl::Linear][SmImpl::Hard] //m_progDraw
					},
					{ //SmImpl::PCF
						10.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 99.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.0025f, 0.0f, 0.01f, 0.00001f   // m_bias
						, 0.001f, 0.0f, 0.05f,  0.00001f   // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 2000.0f, 1.0f, 2000.0f, 1.0f     // m_customParam1
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Single][DepthImpl::Linear][SmImpl::PCF] //m_progDraw
					},
					{ //SmImpl::VSM
						10.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.006f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.02f, 0.0f, 0.1f, 0.00001f      // m_customParam0
						, 300.0f, 1.0f, 1500.0f, 1.0f      // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::VSM] //m_progPack
						, &s_programs.m_colorLighting[SmType::Single][DepthImpl::Linear][SmImpl::VSM] //m_progDraw
					},
					{ //SmImpl::ESM
						10.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 0.01f         // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.0055f, 0.0f, 0.01f, 0.00001f   // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 2500.0f, 1.0f, 5000.0f, 1.0f     // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Single][DepthImpl::Linear][SmImpl::ESM] //m_progDraw
					}

				}

			},
			{ //LightType::Point

				{ //DepthImpl::InvZ

					{ //SmImpl::Hard
						12.0f, 9.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 10.0f, 1.0f, 20.0f, 1.0f         // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.006f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 50.0f, 1.0f, 300.0f, 1.0f        // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_xOffset
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Omni][DepthImpl::InvZ][SmImpl::Hard] //m_progDraw
					},
					{ //SmImpl::PCF
						12.0f, 9.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 10.0f, 1.0f, 20.0f, 1.0f         // m_depthValuePow
						, 1.0f, 1.0f, 99.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.004f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 50.0f, 1.0f, 300.0f, 1.0f        // m_customParam1
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.001f         // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.001f         // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Omni][DepthImpl::InvZ][SmImpl::PCF] //m_progDraw
					},
					{ //SmImpl::VSM
						12.0f, 9.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 10.0f, 1.0f, 20.0f, 1.0f         // m_depthValuePow
						, 8.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.055f, 0.0f, 0.1f, 0.00001f     // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.02f, 0.0f, 0.04f, 0.00001f     // m_customParam0
						, 450.0f, 1.0f, 900.0f, 1.0f       // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_xOffset
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::VSM] //m_progPack
						, &s_programs.m_colorLighting[SmType::Omni][DepthImpl::InvZ][SmImpl::VSM] //m_progDraw
					},
					{ //SmImpl::ESM
						12.0f, 9.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 10.0f, 1.0f, 20.0f, 1.0f         // m_depthValuePow
						, 3.0f, 1.0f, 10.0f, 0.01f         // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.035f, 0.0f, 0.1f, 0.00001f     // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 9000.0f, 1.0f, 15000.0f, 1.0f    // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_xOffset
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Omni][DepthImpl::InvZ][SmImpl::ESM] //m_progDraw
					}

				},
				{ //DepthImpl::Linear

					{ //SmImpl::Hard
						12.0f, 9.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.003f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 120.0f, 1.0f, 300.0f, 1.0f       // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_xOffset
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Omni][DepthImpl::Linear][SmImpl::Hard] //m_progDraw
					},
					{ //SmImpl::PCF
						12.0f, 9.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 99.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.0035f, 0.0f, 0.01f, 0.00001f   // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 120.0f, 1.0f, 300.0f, 1.0f       // m_customParam1
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.001f         // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.001f         // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Omni][DepthImpl::Linear][SmImpl::PCF] //m_progDraw
					},
					{ //SmImpl::VSM
						12.0f, 9.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.006f, 0.0f, 0.1f, 0.00001f     // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.02f, 0.0f, 0.1f, 0.00001f      // m_customParam0
						, 400.0f, 1.0f, 900.0f, 1.0f       // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_xOffset
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::VSM] //m_progPack
						, &s_programs.m_colorLighting[SmType::Omni][DepthImpl::Linear][SmImpl::VSM] //m_progDraw
					},
					{ //SmImpl::ESM
						12.0f, 9.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 0.01f         // m_near
						, 250.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.007f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.05f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 8000.0f, 1.0f, 15000.0f, 1.0f    // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_xOffset
						, 0.25f, 0.0f, 2.0f, 0.001f        // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Omni][DepthImpl::Linear][SmImpl::ESM] //m_progDraw
					}

				}

			},
			{ //LightType::Directional

				{ //DepthImpl::InvZ

					{ //SmImpl::Hard
						11.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 550.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.0012f, 0.0f, 0.01f, 0.00001f   // m_bias
						, 0.001f, 0.0f, 0.04f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 200.0f, 1.0f, 400.0f, 1.0f       // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_xOffset
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Cascade][DepthImpl::InvZ][SmImpl::Hard] //m_progDraw
					},
					{ //SmImpl::PCF
						11.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 99.0f, 1.0f          // m_near
						, 550.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.0012f, 0.0f, 0.01f, 0.00001f   // m_bias
						, 0.001f, 0.0f, 0.04f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 200.0f, 1.0f, 400.0f, 1.0f       // m_customParam1
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Cascade][DepthImpl::InvZ][SmImpl::PCF] //m_progDraw
					},
					{ //SmImpl::VSM
						11.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 550.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.004f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.04f, 0.00001f    // m_normalOffset
						, 0.02f, 0.0f, 0.04f, 0.00001f     // m_customParam0
						, 2500.0f, 1.0f, 5000.0f, 1.0f     // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_xOffset
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::VSM] //m_progPack
						, &s_programs.m_colorLighting[SmType::Cascade][DepthImpl::InvZ][SmImpl::VSM] //m_progDraw
					},
					{ //SmImpl::ESM
						11.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 0.01f         // m_near
						, 550.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.004f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.04f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 9500.0f, 1.0f, 15000.0f, 1.0f    // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_xOffset
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::InvZ][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Cascade][DepthImpl::InvZ][SmImpl::ESM] //m_progDraw
					}

				},
				{ //DepthImpl::Linear

					{ //SmImpl::Hard
						11.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 550.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.0012f, 0.0f, 0.01f, 0.00001f   // m_bias
						, 0.001f, 0.0f, 0.04f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 500.0f, 1.0f, 1000.0f, 1.0f      // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_xOffset
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Cascade][DepthImpl::Linear][SmImpl::Hard] //m_progDraw
					},
					{ //SmImpl::PCF
						11.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 99.0f, 1.0f          // m_near
						, 550.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.0012f, 0.0f, 0.01f, 0.00001f   // m_bias
						, 0.001f, 0.0f, 0.04f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 200.0f, 1.0f, 400.0f, 1.0f       // m_customParam1
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 8.0f, 1.0f           // m_yNum
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_xOffset
						, 1.0f, 0.0f, 3.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Cascade][DepthImpl::Linear][SmImpl::PCF] //m_progDraw
					},
					{ //SmImpl::VSM
						11.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 1.0f          // m_near
						, 550.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.004f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.04f, 0.00001f    // m_normalOffset
						, 0.02f, 0.0f, 0.04f, 0.00001f     // m_customParam0
						, 2500.0f, 1.0f, 5000.0f, 1.0f     // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_xOffset
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::VSM] //m_progPack
						, &s_programs.m_colorLighting[SmType::Cascade][DepthImpl::Linear][SmImpl::VSM] //m_progDraw
					},
					{ //SmImpl::ESM
						11.0f, 7.0f, 12.0f, 1.0f         // m_sizePwrTwo
						, 1.0f, 1.0f, 20.0f, 1.0f          // m_depthValuePow
						, 1.0f, 1.0f, 10.0f, 0.01f         // m_near
						, 550.0f, 100.0f, 2000.0f, 50.0f   // m_far
						, 0.004f, 0.0f, 0.01f, 0.00001f    // m_bias
						, 0.001f, 0.0f, 0.04f, 0.00001f    // m_normalOffset
						, 0.7f, 0.0f, 1.0f, 0.01f          // m_customParam0
						, 9500.0f, 1.0f, 15000.0f, 1.0f    // m_customParam1
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_xNum
						, 2.0f, 0.0f, 4.0f, 1.0f           // m_yNum
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_xOffset
						, 0.2f, 0.0f, 1.0f, 0.01f          // m_yOffset
						, true                             // m_doBlur
						, &s_programs.m_packDepth[DepthImpl::Linear][PackDepth::RGBA] //m_progPack
						, &s_programs.m_colorLighting[SmType::Cascade][DepthImpl::Linear][SmImpl::ESM] //m_progDraw
					}

				}
			}
		};
		bx::memCopy(m_smSettings, smSettings, sizeof(smSettings));

		m_settings.m_lightType = LightType::SpotLight;
		m_settings.m_depthImpl = DepthImpl::InvZ;
		m_settings.m_smImpl    = SmImpl::Hard;
		m_settings.m_spotOuterAngle  = 45.0f;
		m_settings.m_spotInnerAngle  = 30.0f;
		m_settings.m_fovXAdjust      = 0.0f;
		m_settings.m_fovYAdjust      = 0.0f;
		m_settings.m_coverageSpotL   = 90.0f;
		m_settings.m_splitDistribution = 0.6f;
		m_settings.m_numSplits       = 4;
		m_settings.m_updateLights    = true;
		m_settings.m_updateScene     = true;
		m_settings.m_drawDepthBuffer = false;
		m_settings.m_showSmCoverage  = false;
		m_settings.m_stencilPack     = true;
		m_settings.m_stabilize       = true;

		ShadowMapSettings* currentSmSettings = &m_smSettings[m_settings.m_lightType][m_settings.m_depthImpl][m_settings.m_smImpl];

		// Render targets.
		uint16_t shadowMapSize = 1 << uint32_t(currentSmSettings->m_sizePwrTwo);
		m_currentShadowMapSize = shadowMapSize;
		float currentShadowMapSizef = float(int16_t(m_currentShadowMapSize) );
		s_uniforms.m_shadowMapTexelSize = 1.0f / currentShadowMapSizef;
		for (uint8_t ii = 0; ii < ShadowMapRenderTargets::Count; ++ii)
		{
			bgfx::TextureHandle fbtextures[] =
			{
				bgfx::createTexture2D(m_currentShadowMapSize, m_currentShadowMapSize, false, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT),
				bgfx::createTexture2D(m_currentShadowMapSize, m_currentShadowMapSize, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT),
			};
			s_rtShadowMap[ii] = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
		}
		s_rtBlur = bgfx::createFrameBuffer(m_currentShadowMapSize, m_currentShadowMapSize, bgfx::TextureFormat::BGRA8);

		// Setup camera.
		float initialPos[3] = { 0.0f, 60.0f, -105.0f };
		cameraCreate();
		cameraSetPosition(initialPos);
		cameraSetVerticalAngle(-0.45f);

		m_timeAccumulatorLight = 0.0f;
		m_timeAccumulatorScene = 0.0f;
	}

	virtual int shutdown() override
	{
		m_bunnyMesh.unload();
		m_treeMesh.unload();
		m_cubeMesh.unload();
		m_hollowcubeMesh.unload();
		m_hplaneMesh.unload();
		m_vplaneMesh.unload();

		bgfx::destroy(m_texFigure);
		bgfx::destroy(m_texFieldstone);
		bgfx::destroy(m_texFlare);

		for (uint8_t ii = 0; ii < ShadowMapRenderTargets::Count; ++ii)
		{
			bgfx::destroy(s_rtShadowMap[ii]);
		}
		bgfx::destroy(s_rtBlur);

		s_programs.destroy();

		bgfx::destroy(s_texColor);
		bgfx::destroy(s_shadowMap[3]);
		bgfx::destroy(s_shadowMap[2]);
		bgfx::destroy(s_shadowMap[1]);
		bgfx::destroy(s_shadowMap[0]);

		s_uniforms.destroy();

		cameraDestroy();
		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			m_viewState.m_width  = uint16_t(m_width);
			m_viewState.m_height = uint16_t(m_height);

			const bgfx::Caps* caps = bgfx::getCaps();

			// Set view and projection matrices.
			const float camFovy    = 60.0f;
			const float camAspect  = float(int32_t(m_viewState.m_width) ) / float(int32_t(m_viewState.m_height) );
			const float camNear    = 0.1f;
			const float camFar     = 2000.0f;
			const float projHeight = 1.0f/bx::tan(bx::toRad(camFovy)*0.5f);
			const float projWidth  = projHeight * camAspect;
			bx::mtxProj(m_viewState.m_proj, camFovy, camAspect, camNear, camFar, caps->homogeneousDepth);
			cameraGetViewMtx(m_viewState.m_view);

			float currentShadowMapSizef = float(int16_t(m_currentShadowMapSize) );
			s_uniforms.m_shadowMapTexelSize = 1.0f / currentShadowMapSizef;

			s_uniforms.submitConstUniforms();

			//		s_uniforms.submitConstUniforms();

			// Imgui.
			imguiBeginFrame(m_mouseState.m_mx
							, m_mouseState.m_my
							, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
							| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
							| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
							, m_mouseState.m_mz
							, m_viewState.m_width
							, m_viewState.m_height
							);

			showExampleDialog(this);

			ImGui::SetNextWindowPos(
				  ImVec2(m_viewState.m_width - m_viewState.m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_viewState.m_width / 5.0f, m_viewState.m_height - 20.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

#define IMGUI_FLOAT_SLIDER(_name, _val) \
	ImGui::SliderFloat(_name            \
			, &_val                     \
			, *( ((float*)&_val)+1)     \
			, *( ((float*)&_val)+2)     \
			)

#define IMGUI_RADIO_BUTTON(_name, _var, _val)     \
	if (ImGui::RadioButton(_name, _var == _val) ) \
	{                                             \
		_var = _val;                              \
	}

			ImGui::Checkbox("Update lights", &m_settings.m_updateLights);
			ImGui::Checkbox("Update scene", &m_settings.m_updateScene);

			ImGui::Separator();
			ImGui::Text("Shadow map depth:");
			IMGUI_RADIO_BUTTON("InvZ", m_settings.m_depthImpl, DepthImpl::InvZ);
			IMGUI_RADIO_BUTTON("Linear", m_settings.m_depthImpl, DepthImpl::Linear);

			ShadowMapSettings* currentSmSettings = &m_smSettings[m_settings.m_lightType][m_settings.m_depthImpl][m_settings.m_smImpl];

			ImGui::Separator();
			ImGui::Checkbox("Draw depth buffer", &m_settings.m_drawDepthBuffer);
			if (m_settings.m_drawDepthBuffer)
			{
				IMGUI_FLOAT_SLIDER("Depth value pow", currentSmSettings->m_depthValuePow);
			}

			ImGui::Separator();
			ImGui::Text("Shadow Map implementation");
			IMGUI_RADIO_BUTTON("Hard", m_settings.m_smImpl, SmImpl::Hard);
			IMGUI_RADIO_BUTTON("PCF", m_settings.m_smImpl, SmImpl::PCF);
			IMGUI_RADIO_BUTTON("VSM", m_settings.m_smImpl, SmImpl::VSM);
			IMGUI_RADIO_BUTTON("ESM", m_settings.m_smImpl, SmImpl::ESM);
			currentSmSettings = &m_smSettings[m_settings.m_lightType][m_settings.m_depthImpl][m_settings.m_smImpl];

			ImGui::Separator();
			IMGUI_FLOAT_SLIDER("Bias", currentSmSettings->m_bias);
			IMGUI_FLOAT_SLIDER("Normal offset", currentSmSettings->m_normalOffset);
			ImGui::Separator();
			if (LightType::DirectionalLight != m_settings.m_lightType)
			{
				IMGUI_FLOAT_SLIDER("Near plane", currentSmSettings->m_near);
			}
			IMGUI_FLOAT_SLIDER("Far plane", currentSmSettings->m_far);

			ImGui::Separator();
			switch(m_settings.m_smImpl)
			{
				case SmImpl::Hard:
					//ImGui::Text("Hard");
					break;

				case SmImpl::PCF:
					ImGui::Text("PCF");
					IMGUI_FLOAT_SLIDER("X Offset", currentSmSettings->m_xOffset);
					IMGUI_FLOAT_SLIDER("Y Offset", currentSmSettings->m_yOffset);
					break;

				case SmImpl::VSM:
					ImGui::Text("VSM");
					IMGUI_FLOAT_SLIDER("Min variance", currentSmSettings->m_customParam0);
					IMGUI_FLOAT_SLIDER("Depth multiplier", currentSmSettings->m_customParam1);
					ImGui::Checkbox("Blur shadow map", &currentSmSettings->m_doBlur);
					if (currentSmSettings->m_doBlur)
					{
						IMGUI_FLOAT_SLIDER("Blur X Offset", currentSmSettings->m_xOffset);
						IMGUI_FLOAT_SLIDER("Blur Y Offset", currentSmSettings->m_yOffset);
					}
					break;

				case SmImpl::ESM:
					ImGui::Text("ESM");
					IMGUI_FLOAT_SLIDER("ESM Hardness", currentSmSettings->m_customParam0);
					IMGUI_FLOAT_SLIDER("Depth multiplier", currentSmSettings->m_customParam1);
					ImGui::Checkbox("Blur shadow map", &currentSmSettings->m_doBlur);
					if (currentSmSettings->m_doBlur)
					{
						IMGUI_FLOAT_SLIDER("Blur X Offset", currentSmSettings->m_xOffset);
						IMGUI_FLOAT_SLIDER("Blur Y Offset", currentSmSettings->m_yOffset);
					}
					break;

				default:
					break;
			};

			ImGui::End();
#undef IMGUI_RADIO_BUTTON

			ImGui::SetNextWindowPos(
				  ImVec2(10.0f, 260.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_viewState.m_width / 5.0f, 350.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Light"
				, NULL
				, 0
				);
			ImGui::PushItemWidth(185.0f);

			bool bLtChanged = false;
			if ( ImGui::RadioButton("Spot light", m_settings.m_lightType == LightType::SpotLight ))
			{
				m_settings.m_lightType = LightType::SpotLight; bLtChanged = true;
			}
			if ( ImGui::RadioButton("Point light", m_settings.m_lightType == LightType::PointLight ))
			{
				m_settings.m_lightType = LightType::PointLight; bLtChanged = true;
			}
			if ( ImGui::RadioButton("Directional light", m_settings.m_lightType == LightType::DirectionalLight ))
			{
				m_settings.m_lightType = LightType::DirectionalLight; bLtChanged = true;
			}

			ImGui::Separator();
			ImGui::Checkbox("Show shadow map coverage.", &m_settings.m_showSmCoverage);

			ImGui::Separator();
			ImGui::Text("Shadow map resolution: %ux%u", m_currentShadowMapSize, m_currentShadowMapSize);
			ImGui::SliderFloat("##SizePwrTwo", &currentSmSettings->m_sizePwrTwo,
							   currentSmSettings->m_sizePwrTwoMin,
							   currentSmSettings->m_sizePwrTwoMax, "%.0f");

			ImGui::Separator();
			if (LightType::SpotLight == m_settings.m_lightType)
			{
				ImGui::Text("Spot light");
				ImGui::SliderFloat("Shadow map area", &m_settings.m_coverageSpotL, 45.0f, 120.0f);

				ImGui::Separator();
				ImGui::SliderFloat("Spot outer cone", &m_settings.m_spotOuterAngle, 0.0f, 91.0f);
				ImGui::SliderFloat("Spot inner cone", &m_settings.m_spotInnerAngle, 0.0f, 90.0f);
			}
			else if (LightType::PointLight == m_settings.m_lightType)
			{
				ImGui::Text("Point light");
				ImGui::Checkbox("Stencil pack", &m_settings.m_stencilPack);

				ImGui::SliderFloat("Fov X adjust", &m_settings.m_fovXAdjust, -20.0f, 20.0f);
				ImGui::SliderFloat("Fov Y adjust", &m_settings.m_fovYAdjust, -20.0f, 20.0f);
			}
			else if (LightType::DirectionalLight == m_settings.m_lightType)
			{
				ImGui::Text("Directional light");
				ImGui::Checkbox("Stabilize cascades", &m_settings.m_stabilize);
				ImGui::SliderInt("Cascade splits", &m_settings.m_numSplits, 1, 4);
				ImGui::SliderFloat("Cascade distribution", &m_settings.m_splitDistribution, 0.0f, 1.0f);
			}

#undef IMGUI_FLOAT_SLIDER

			ImGui::End();

			imguiEndFrame();

			// Update uniforms.
			s_uniforms.m_shadowMapBias   = currentSmSettings->m_bias;
			s_uniforms.m_shadowMapOffset = currentSmSettings->m_normalOffset;
			s_uniforms.m_shadowMapParam0 = currentSmSettings->m_customParam0;
			s_uniforms.m_shadowMapParam1 = currentSmSettings->m_customParam1;
			s_uniforms.m_depthValuePow   = currentSmSettings->m_depthValuePow;
			s_uniforms.m_XNum            = currentSmSettings->m_xNum;
			s_uniforms.m_YNum            = currentSmSettings->m_yNum;
			s_uniforms.m_XOffset         = currentSmSettings->m_xOffset;
			s_uniforms.m_YOffset         = currentSmSettings->m_yOffset;
			s_uniforms.m_showSmCoverage  = float(m_settings.m_showSmCoverage);
			s_uniforms.m_lightPtr = (LightType::DirectionalLight == m_settings.m_lightType) ? &m_directionalLight : &m_pointLight;

			if (LightType::SpotLight == m_settings.m_lightType)
			{
				m_pointLight.m_attenuationSpotOuter.m_outer = m_settings.m_spotOuterAngle;
				m_pointLight.m_spotDirectionInner.m_inner   = m_settings.m_spotInnerAngle;
			}
			else
			{
				m_pointLight.m_attenuationSpotOuter.m_outer = 91.0f; //above 90.0f means point light
			}

			s_uniforms.submitPerFrameUniforms();

			// Time.
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const float deltaTime = float(frameTime/freq);

			// Update camera.
			cameraUpdate(deltaTime, m_mouseState);

			// Update view mtx.
			cameraGetViewMtx(m_viewState.m_view);

			// Update lights.
			m_pointLight.computeViewSpaceComponents(m_viewState.m_view);
			m_directionalLight.computeViewSpaceComponents(m_viewState.m_view);

			// Update time accumulators.
			if (m_settings.m_updateLights) { m_timeAccumulatorLight += deltaTime; }
			if (m_settings.m_updateScene)  { m_timeAccumulatorScene += deltaTime; }

			// Setup lights.
			m_pointLight.m_position.m_x = bx::cos(m_timeAccumulatorLight) * 20.0f;
			m_pointLight.m_position.m_y = 26.0f;
			m_pointLight.m_position.m_z = bx::sin(m_timeAccumulatorLight) * 20.0f;
			m_pointLight.m_spotDirectionInner.m_x = -m_pointLight.m_position.m_x;
			m_pointLight.m_spotDirectionInner.m_y = -m_pointLight.m_position.m_y;
			m_pointLight.m_spotDirectionInner.m_z = -m_pointLight.m_position.m_z;

			m_directionalLight.m_position.m_x = -bx::cos(m_timeAccumulatorLight);
			m_directionalLight.m_position.m_y = -1.0f;
			m_directionalLight.m_position.m_z = -bx::sin(m_timeAccumulatorLight);

			// Setup instance matrices.
			float mtxFloor[16];
			const float floorScale = 550.0f;
			bx::mtxSRT(mtxFloor
					   , floorScale //scaleX
					   , floorScale //scaleY
					   , floorScale //scaleZ
					   , 0.0f //rotX
					   , 0.0f //rotY
					   , 0.0f //rotZ
					   , 0.0f //translateX
					   , 0.0f //translateY
					   , 0.0f //translateZ
					   );

			float mtxBunny[16];
			bx::mtxSRT(mtxBunny
					   , 5.0f
					   , 5.0f
					   , 5.0f
					   , 0.0f
					   , 1.56f - m_timeAccumulatorScene
					   , 0.0f
					   , 15.0f
					   , 5.0f
					   , 0.0f
					   );

			float mtxHollowcube[16];
			bx::mtxSRT(mtxHollowcube
					   , 2.5f
					   , 2.5f
					   , 2.5f
					   , 0.0f
					   , 1.56f - m_timeAccumulatorScene
					   , 0.0f
					   , 0.0f
					   , 10.0f
					   , 0.0f
					   );

			float mtxCube[16];
			bx::mtxSRT(mtxCube
					   , 2.5f
					   , 2.5f
					   , 2.5f
					   , 0.0f
					   , 1.56f - m_timeAccumulatorScene
					   , 0.0f
					   , -15.0f
					   , 5.0f
					   , 0.0f
					   );

			const uint8_t numTrees = 10;
			float mtxTrees[numTrees][16];
			for (uint8_t ii = 0; ii < numTrees; ++ii)
			{
				bx::mtxSRT(mtxTrees[ii]
						   , 2.0f
						   , 2.0f
						   , 2.0f
						   , 0.0f
						   , float(ii)
						   , 0.0f
						   , bx::sin(float(ii)*2.0f*bx::kPi/float(numTrees) ) * 60.0f
						   , 0.0f
						   , bx::cos(float(ii)*2.0f*bx::kPi/float(numTrees) ) * 60.0f
						   );
			}

			// Compute transform matrices.
			const uint8_t shadowMapPasses = ShadowMapRenderTargets::Count;
			float lightView[shadowMapPasses][16];
			float lightProj[shadowMapPasses][16];
			float mtxYpr[TetrahedronFaces::Count][16];

			float screenProj[16];
			float screenView[16];
			bx::mtxIdentity(screenView);

			bx::mtxOrtho(
						 screenProj
						 , 0.0f
						 , 1.0f
						 , 1.0f
						 , 0.0f
						 , 0.0f
						 , 100.0f
						 , 0.0f
						 , caps->homogeneousDepth
						 );

			if (LightType::SpotLight == m_settings.m_lightType)
			{
				const float fovy = m_settings.m_coverageSpotL;
				const float aspect = 1.0f;
				bx::mtxProj(
							lightProj[ProjType::Horizontal]
							, fovy
							, aspect
							, currentSmSettings->m_near
							, currentSmSettings->m_far
							, false
							);

				//For linear depth, prevent depth division by variable w-component in shaders and divide here by far plane
				if (DepthImpl::Linear == m_settings.m_depthImpl)
				{
					lightProj[ProjType::Horizontal][10] /= currentSmSettings->m_far;
					lightProj[ProjType::Horizontal][14] /= currentSmSettings->m_far;
				}

				float at[3];
				bx::vec3Add(at, m_pointLight.m_position.m_v, m_pointLight.m_spotDirectionInner.m_v);
				bx::mtxLookAt(lightView[TetrahedronFaces::Green], m_pointLight.m_position.m_v, at);
			}
			else if (LightType::PointLight == m_settings.m_lightType)
			{
				float ypr[TetrahedronFaces::Count][3] =
				{
					{ bx::toRad(  0.0f), bx::toRad( 27.36780516f), bx::toRad(0.0f) },
					{ bx::toRad(180.0f), bx::toRad( 27.36780516f), bx::toRad(0.0f) },
					{ bx::toRad(-90.0f), bx::toRad(-27.36780516f), bx::toRad(0.0f) },
					{ bx::toRad( 90.0f), bx::toRad(-27.36780516f), bx::toRad(0.0f) },
				};


				if (m_settings.m_stencilPack)
				{
					const float fovx = 143.98570868f + 3.51f + m_settings.m_fovXAdjust;
					const float fovy = 125.26438968f + 9.85f + m_settings.m_fovYAdjust;
					const float aspect = bx::tan(bx::toRad(fovx*0.5f) )/bx::tan(bx::toRad(fovy*0.5f) );

					bx::mtxProj(
						  lightProj[ProjType::Vertical]
								, fovx
								, aspect
								, currentSmSettings->m_near
								, currentSmSettings->m_far
								, false
								);

					//For linear depth, prevent depth division by variable w-component in shaders and divide here by far plane
					if (DepthImpl::Linear == m_settings.m_depthImpl)
					{
						lightProj[ProjType::Vertical][10] /= currentSmSettings->m_far;
						lightProj[ProjType::Vertical][14] /= currentSmSettings->m_far;
					}

					ypr[TetrahedronFaces::Green ][2] = bx::toRad(180.0f);
					ypr[TetrahedronFaces::Yellow][2] = bx::toRad(  0.0f);
					ypr[TetrahedronFaces::Blue  ][2] = bx::toRad( 90.0f);
					ypr[TetrahedronFaces::Red   ][2] = bx::toRad(-90.0f);
				}

				const float fovx = 143.98570868f + 7.8f + m_settings.m_fovXAdjust;
				const float fovy = 125.26438968f + 3.0f + m_settings.m_fovYAdjust;
				const float aspect = bx::tan(bx::toRad(fovx*0.5f) )/bx::tan(bx::toRad(fovy*0.5f) );

				bx::mtxProj(
							lightProj[ProjType::Horizontal]
							, fovy
							, aspect
							, currentSmSettings->m_near
							, currentSmSettings->m_far
							, caps->homogeneousDepth
							);

				//For linear depth, prevent depth division by variable w component in shaders and divide here by far plane
				if (DepthImpl::Linear == m_settings.m_depthImpl)
				{
					lightProj[ProjType::Horizontal][10] /= currentSmSettings->m_far;
					lightProj[ProjType::Horizontal][14] /= currentSmSettings->m_far;
				}


				for (uint8_t ii = 0; ii < TetrahedronFaces::Count; ++ii)
				{
					float mtxTmp[16];
					mtxYawPitchRoll(mtxTmp, ypr[ii][0], ypr[ii][1], ypr[ii][2]);

					float tmp[3] =
					{
						-bx::vec3Dot(m_pointLight.m_position.m_v, &mtxTmp[0]),
						-bx::vec3Dot(m_pointLight.m_position.m_v, &mtxTmp[4]),
						-bx::vec3Dot(m_pointLight.m_position.m_v, &mtxTmp[8]),
					};

					bx::mtxTranspose(mtxYpr[ii], mtxTmp);

					bx::memCopy(lightView[ii], mtxYpr[ii], 12*sizeof(float) );
					lightView[ii][12] = tmp[0];
					lightView[ii][13] = tmp[1];
					lightView[ii][14] = tmp[2];
					lightView[ii][15] = 1.0f;
				}
			}
			else // LightType::DirectionalLight == settings.m_lightType
			{
				// Setup light view mtx.
				float eye[3] =
				{
					-m_directionalLight.m_position.m_x
					, -m_directionalLight.m_position.m_y
					, -m_directionalLight.m_position.m_z
				};
				float at[3] = { 0.0f, 0.0f, 0.0f };
				bx::mtxLookAt(lightView[0], eye, at);

				// Compute camera inverse view mtx.
				float mtxViewInv[16];
				bx::mtxInverse(mtxViewInv, m_viewState.m_view);

				// Compute split distances.
				const uint8_t maxNumSplits = 4;
				BX_CHECK(maxNumSplits >= settings.m_numSplits, "Error! Max num splits.");

				float splitSlices[maxNumSplits*2];
				splitFrustum(splitSlices
					, uint8_t(m_settings.m_numSplits)
					, currentSmSettings->m_near
					, currentSmSettings->m_far
					, m_settings.m_splitDistribution
					);

				// Update uniforms.
				for (uint8_t ii = 0, ff = 1; ii < m_settings.m_numSplits; ++ii, ff+=2)
				{
					// This lags for 1 frame, but it's not a problem.
					s_uniforms.m_csmFarDistances[ii] = splitSlices[ff];
				}

				float mtxProj[16];
				bx::mtxOrtho(
							 mtxProj
							 , 1.0f
							 , -1.0f
							 , 1.0f
							 , -1.0f
							 , -currentSmSettings->m_far
							 , currentSmSettings->m_far
							 , 0.0f
							 , caps->homogeneousDepth
							 );

				const uint8_t numCorners = 8;
				float frustumCorners[maxNumSplits][numCorners][3];
				for (uint8_t ii = 0, nn = 0, ff = 1; ii < m_settings.m_numSplits; ++ii, nn+=2, ff+=2)
				{
					// Compute frustum corners for one split in world space.
					worldSpaceFrustumCorners( (float*)frustumCorners[ii], splitSlices[nn], splitSlices[ff], projWidth, projHeight, mtxViewInv);

					float min[3] = {  9000.0f,  9000.0f,  9000.0f };
					float max[3] = { -9000.0f, -9000.0f, -9000.0f };

					for (uint8_t jj = 0; jj < numCorners; ++jj)
					{
						// Transform to light space.
						float lightSpaceFrustumCorner[3];
						bx::vec3MulMtx(lightSpaceFrustumCorner, frustumCorners[ii][jj], lightView[0]);

						// Update bounding box.
						min[0] = bx::min(min[0], lightSpaceFrustumCorner[0]);
						max[0] = bx::max(max[0], lightSpaceFrustumCorner[0]);
						min[1] = bx::min(min[1], lightSpaceFrustumCorner[1]);
						max[1] = bx::max(max[1], lightSpaceFrustumCorner[1]);
						min[2] = bx::min(min[2], lightSpaceFrustumCorner[2]);
						max[2] = bx::max(max[2], lightSpaceFrustumCorner[2]);
					}

					float minproj[3];
					float maxproj[3];
					bx::vec3MulMtxH(minproj, min, mtxProj);
					bx::vec3MulMtxH(maxproj, max, mtxProj);

					float offsetx, offsety;
					float scalex, scaley;

					scalex = 2.0f / (maxproj[0] - minproj[0]);
					scaley = 2.0f / (maxproj[1] - minproj[1]);

					if (m_settings.m_stabilize)
					{
						const float quantizer = 64.0f;
						scalex = quantizer / bx::ceil(quantizer / scalex);
						scaley = quantizer / bx::ceil(quantizer / scaley);
					}

					offsetx = 0.5f * (maxproj[0] + minproj[0]) * scalex;
					offsety = 0.5f * (maxproj[1] + minproj[1]) * scaley;

					if (m_settings.m_stabilize)
					{
						const float halfSize = currentShadowMapSizef * 0.5f;
						offsetx = bx::ceil(offsetx * halfSize) / halfSize;
						offsety = bx::ceil(offsety * halfSize) / halfSize;
					}

					float mtxCrop[16];
					bx::mtxIdentity(mtxCrop);
					mtxCrop[ 0] = scalex;
					mtxCrop[ 5] = scaley;
					mtxCrop[12] = offsetx;
					mtxCrop[13] = offsety;

					bx::mtxMul(lightProj[ii], mtxCrop, mtxProj);
				}
			}

			// Reset render targets.
			const bgfx::FrameBufferHandle invalidRt = BGFX_INVALID_HANDLE;
			for (uint8_t ii = 0; ii < RENDERVIEW_DRAWDEPTH_3_ID+1; ++ii)
			{
				bgfx::setViewFrameBuffer(ii, invalidRt);
			}

			// Determine on-screen rectangle size where depth buffer will be drawn.
			uint16_t depthRectHeight = uint16_t(float(m_viewState.m_height) / 2.5f);
			uint16_t depthRectWidth  = depthRectHeight;
			uint16_t depthRectX = 0;
			uint16_t depthRectY = m_viewState.m_height - depthRectHeight;

			// Setup views and render targets.
			bgfx::setViewRect(0, 0, 0, m_viewState.m_width, m_viewState.m_height);
			bgfx::setViewTransform(0, m_viewState.m_view, m_viewState.m_proj);

			if (LightType::SpotLight == m_settings.m_lightType)
			{
				/**
				 * RENDERVIEW_SHADOWMAP_0_ID - Clear shadow map. (used as convenience, otherwise render_pass_1 could be cleared)
				 * RENDERVIEW_SHADOWMAP_1_ID - Craft shadow map.
				 * RENDERVIEW_VBLUR_0_ID - Vertical blur.
				 * RENDERVIEW_HBLUR_0_ID - Horizontal blur.
				 * RENDERVIEW_DRAWSCENE_0_ID - Draw scene.
				 * RENDERVIEW_DRAWSCENE_1_ID - Draw floor bottom.
				 * RENDERVIEW_DRAWDEPTH_0_ID - Draw depth buffer.
				 */

				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_0_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_1_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_VBLUR_0_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_HBLUR_0_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_DRAWSCENE_0_ID, 0, 0, m_viewState.m_width, m_viewState.m_height);
				bgfx::setViewRect(RENDERVIEW_DRAWSCENE_1_ID, 0, 0, m_viewState.m_width, m_viewState.m_height);
				bgfx::setViewRect(RENDERVIEW_DRAWDEPTH_0_ID, depthRectX, depthRectY, depthRectWidth, depthRectHeight);

				bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_0_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_1_ID, lightView[0], lightProj[ProjType::Horizontal]);
				bgfx::setViewTransform(RENDERVIEW_VBLUR_0_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_HBLUR_0_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_0_ID, m_viewState.m_view, m_viewState.m_proj);
				bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_1_ID, m_viewState.m_view, m_viewState.m_proj);
				bgfx::setViewTransform(RENDERVIEW_DRAWDEPTH_0_ID, screenView, screenProj);

				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_0_ID, s_rtShadowMap[0]);
				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_1_ID, s_rtShadowMap[0]);
				bgfx::setViewFrameBuffer(RENDERVIEW_VBLUR_0_ID, s_rtBlur);
				bgfx::setViewFrameBuffer(RENDERVIEW_HBLUR_0_ID, s_rtShadowMap[0]);
			}
			else if (LightType::PointLight == m_settings.m_lightType)
			{
				/**
				 * RENDERVIEW_SHADOWMAP_0_ID - Clear entire shadow map.
				 * RENDERVIEW_SHADOWMAP_1_ID - Craft green tetrahedron shadow face.
				 * RENDERVIEW_SHADOWMAP_2_ID - Craft yellow tetrahedron shadow face.
				 * RENDERVIEW_SHADOWMAP_3_ID - Craft blue tetrahedron shadow face.
				 * RENDERVIEW_SHADOWMAP_4_ID - Craft red tetrahedron shadow face.
				 * RENDERVIEW_VBLUR_0_ID - Vertical blur.
				 * RENDERVIEW_HBLUR_0_ID - Horizontal blur.
				 * RENDERVIEW_DRAWSCENE_0_ID - Draw scene.
				 * RENDERVIEW_DRAWSCENE_1_ID - Draw floor bottom.
				 * RENDERVIEW_DRAWDEPTH_0_ID - Draw depth buffer.
				 */

				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_0_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				if (m_settings.m_stencilPack)
				{
					const uint16_t f = m_currentShadowMapSize;   //full size
					const uint16_t h = m_currentShadowMapSize/2; //half size
					bgfx::setViewRect(RENDERVIEW_SHADOWMAP_1_ID, 0, 0, f, h);
					bgfx::setViewRect(RENDERVIEW_SHADOWMAP_2_ID, 0, h, f, h);
					bgfx::setViewRect(RENDERVIEW_SHADOWMAP_3_ID, 0, 0, h, f);
					bgfx::setViewRect(RENDERVIEW_SHADOWMAP_4_ID, h, 0, h, f);
				}
				else
				{
					const uint16_t h = m_currentShadowMapSize/2; //half size
					bgfx::setViewRect(RENDERVIEW_SHADOWMAP_1_ID, 0, 0, h, h);
					bgfx::setViewRect(RENDERVIEW_SHADOWMAP_2_ID, h, 0, h, h);
					bgfx::setViewRect(RENDERVIEW_SHADOWMAP_3_ID, 0, h, h, h);
					bgfx::setViewRect(RENDERVIEW_SHADOWMAP_4_ID, h, h, h, h);
				}
				bgfx::setViewRect(RENDERVIEW_VBLUR_0_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_HBLUR_0_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_DRAWSCENE_0_ID, 0, 0, m_viewState.m_width, m_viewState.m_height);
				bgfx::setViewRect(RENDERVIEW_DRAWSCENE_1_ID, 0, 0, m_viewState.m_width, m_viewState.m_height);
				bgfx::setViewRect(RENDERVIEW_DRAWDEPTH_0_ID, depthRectX, depthRectY, depthRectWidth, depthRectHeight);

				bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_0_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_1_ID, lightView[TetrahedronFaces::Green],  lightProj[ProjType::Horizontal]);
				bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_2_ID, lightView[TetrahedronFaces::Yellow], lightProj[ProjType::Horizontal]);
				if(m_settings.m_stencilPack)
				{
					bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_3_ID, lightView[TetrahedronFaces::Blue], lightProj[ProjType::Vertical]);
					bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_4_ID, lightView[TetrahedronFaces::Red],  lightProj[ProjType::Vertical]);
				}
				else
				{
					bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_3_ID, lightView[TetrahedronFaces::Blue], lightProj[ProjType::Horizontal]);
					bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_4_ID, lightView[TetrahedronFaces::Red],  lightProj[ProjType::Horizontal]);
				}
				bgfx::setViewTransform(RENDERVIEW_VBLUR_0_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_HBLUR_0_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_0_ID, m_viewState.m_view, m_viewState.m_proj);
				bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_1_ID, m_viewState.m_view, m_viewState.m_proj);
				bgfx::setViewTransform(RENDERVIEW_DRAWDEPTH_0_ID, screenView, screenProj);

				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_0_ID, s_rtShadowMap[0]);
				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_1_ID, s_rtShadowMap[0]);
				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_2_ID, s_rtShadowMap[0]);
				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_3_ID, s_rtShadowMap[0]);
				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_4_ID, s_rtShadowMap[0]);
				bgfx::setViewFrameBuffer(RENDERVIEW_VBLUR_0_ID, s_rtBlur);
				bgfx::setViewFrameBuffer(RENDERVIEW_HBLUR_0_ID, s_rtShadowMap[0]);
			}
			else // LightType::DirectionalLight == settings.m_lightType
			{
				/**
				 * RENDERVIEW_SHADOWMAP_1_ID - Craft shadow map for first  split.
				 * RENDERVIEW_SHADOWMAP_2_ID - Craft shadow map for second split.
				 * RENDERVIEW_SHADOWMAP_3_ID - Craft shadow map for third  split.
				 * RENDERVIEW_SHADOWMAP_4_ID - Craft shadow map for fourth split.
				 * RENDERVIEW_VBLUR_0_ID - Vertical   blur for first  split.
				 * RENDERVIEW_HBLUR_0_ID - Horizontal blur for first  split.
				 * RENDERVIEW_VBLUR_1_ID - Vertical   blur for second split.
				 * RENDERVIEW_HBLUR_1_ID - Horizontal blur for second split.
				 * RENDERVIEW_VBLUR_2_ID - Vertical   blur for third  split.
				 * RENDERVIEW_HBLUR_2_ID - Horizontal blur for third  split.
				 * RENDERVIEW_VBLUR_3_ID - Vertical   blur for fourth split.
				 * RENDERVIEW_HBLUR_3_ID - Horizontal blur for fourth split.
				 * RENDERVIEW_DRAWSCENE_0_ID - Draw scene.
				 * RENDERVIEW_DRAWSCENE_1_ID - Draw floor bottom.
				 * RENDERVIEW_DRAWDEPTH_0_ID - Draw depth buffer for first  split.
				 * RENDERVIEW_DRAWDEPTH_1_ID - Draw depth buffer for second split.
				 * RENDERVIEW_DRAWDEPTH_2_ID - Draw depth buffer for third  split.
				 * RENDERVIEW_DRAWDEPTH_3_ID - Draw depth buffer for fourth split.
				 */

				depthRectHeight = m_viewState.m_height / 3;
				depthRectWidth  = depthRectHeight;
				depthRectX = 0;
				depthRectY = m_viewState.m_height - depthRectHeight;

				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_1_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_2_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_3_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_4_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_VBLUR_0_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_HBLUR_0_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_VBLUR_1_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_HBLUR_1_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_VBLUR_2_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_HBLUR_2_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_VBLUR_3_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_HBLUR_3_ID, 0, 0, m_currentShadowMapSize, m_currentShadowMapSize);
				bgfx::setViewRect(RENDERVIEW_DRAWSCENE_0_ID, 0, 0, m_viewState.m_width, m_viewState.m_height);
				bgfx::setViewRect(RENDERVIEW_DRAWSCENE_1_ID, 0, 0, m_viewState.m_width, m_viewState.m_height);
				bgfx::setViewRect(RENDERVIEW_DRAWDEPTH_0_ID, depthRectX+(0*depthRectWidth), depthRectY, depthRectWidth, depthRectHeight);
				bgfx::setViewRect(RENDERVIEW_DRAWDEPTH_1_ID, depthRectX+(1*depthRectWidth), depthRectY, depthRectWidth, depthRectHeight);
				bgfx::setViewRect(RENDERVIEW_DRAWDEPTH_2_ID, depthRectX+(2*depthRectWidth), depthRectY, depthRectWidth, depthRectHeight);
				bgfx::setViewRect(RENDERVIEW_DRAWDEPTH_3_ID, depthRectX+(3*depthRectWidth), depthRectY, depthRectWidth, depthRectHeight);

				bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_1_ID, lightView[0], lightProj[0]);
				bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_2_ID, lightView[0], lightProj[1]);
				bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_3_ID, lightView[0], lightProj[2]);
				bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_4_ID, lightView[0], lightProj[3]);
				bgfx::setViewTransform(RENDERVIEW_VBLUR_0_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_HBLUR_0_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_VBLUR_1_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_HBLUR_1_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_VBLUR_2_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_HBLUR_2_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_VBLUR_3_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_HBLUR_3_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_0_ID, m_viewState.m_view, m_viewState.m_proj);
				bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_1_ID, m_viewState.m_view, m_viewState.m_proj);
				bgfx::setViewTransform(RENDERVIEW_DRAWDEPTH_0_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_DRAWDEPTH_1_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_DRAWDEPTH_2_ID, screenView, screenProj);
				bgfx::setViewTransform(RENDERVIEW_DRAWDEPTH_3_ID, screenView, screenProj);

				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_1_ID, s_rtShadowMap[0]);
				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_2_ID, s_rtShadowMap[1]);
				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_3_ID, s_rtShadowMap[2]);
				bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_4_ID, s_rtShadowMap[3]);
				bgfx::setViewFrameBuffer(RENDERVIEW_VBLUR_0_ID, s_rtBlur);         //vblur
				bgfx::setViewFrameBuffer(RENDERVIEW_HBLUR_0_ID, s_rtShadowMap[0]); //hblur
				bgfx::setViewFrameBuffer(RENDERVIEW_VBLUR_1_ID, s_rtBlur);         //vblur
				bgfx::setViewFrameBuffer(RENDERVIEW_HBLUR_1_ID, s_rtShadowMap[1]); //hblur
				bgfx::setViewFrameBuffer(RENDERVIEW_VBLUR_2_ID, s_rtBlur);         //vblur
				bgfx::setViewFrameBuffer(RENDERVIEW_HBLUR_2_ID, s_rtShadowMap[2]); //hblur
				bgfx::setViewFrameBuffer(RENDERVIEW_VBLUR_3_ID, s_rtBlur);         //vblur
				bgfx::setViewFrameBuffer(RENDERVIEW_HBLUR_3_ID, s_rtShadowMap[3]); //hblur
			}

			// Clear backbuffer at beginning.
			bgfx::setViewClear(0
							   , BGFX_CLEAR_COLOR
							   | BGFX_CLEAR_DEPTH
							   , m_clearValues.m_clearRgba
							   , m_clearValues.m_clearDepth
							   , m_clearValues.m_clearStencil
							   );
			bgfx::touch(0);

			// Clear shadowmap rendertarget at beginning.
			const uint8_t flags0 = (LightType::DirectionalLight == m_settings.m_lightType)
			? 0
			: BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL
			;

			bgfx::setViewClear(RENDERVIEW_SHADOWMAP_0_ID
							   , flags0
							   , 0xfefefefe //blur fails on completely white regions
							   , m_clearValues.m_clearDepth
							   , m_clearValues.m_clearStencil
							   );
			bgfx::touch(RENDERVIEW_SHADOWMAP_0_ID);

			const uint8_t flags1 = (LightType::DirectionalLight == m_settings.m_lightType)
			? BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
			: 0
			;

			for (uint8_t ii = 0; ii < 4; ++ii)
			{
				bgfx::setViewClear(RENDERVIEW_SHADOWMAP_1_ID+ii
								   , flags1
								   , 0xfefefefe //blur fails on completely white regions
								   , m_clearValues.m_clearDepth
								   , m_clearValues.m_clearStencil
								   );
				bgfx::touch(RENDERVIEW_SHADOWMAP_1_ID+ii);
			}

			// Render.

			// Craft shadow map.
			{
				// Craft stencil mask for point light shadow map packing.
				if(LightType::PointLight == m_settings.m_lightType && m_settings.m_stencilPack)
				{
					if (6 == bgfx::getAvailTransientVertexBuffer(6, m_posDecl) )
					{
						struct Pos
						{
							float m_x, m_y, m_z;
						};

						bgfx::TransientVertexBuffer vb;
						bgfx::allocTransientVertexBuffer(&vb, 6, m_posDecl);
						Pos* vertex = (Pos*)vb.data;

						const float min = 0.0f;
						const float max = 1.0f;
						const float center = 0.5f;
						const float zz = 0.0f;

						vertex[0].m_x = min;
						vertex[0].m_y = min;
						vertex[0].m_z = zz;

						vertex[1].m_x = max;
						vertex[1].m_y = min;
						vertex[1].m_z = zz;

						vertex[2].m_x = center;
						vertex[2].m_y = center;
						vertex[2].m_z = zz;

						vertex[3].m_x = center;
						vertex[3].m_y = center;
						vertex[3].m_z = zz;

						vertex[4].m_x = max;
						vertex[4].m_y = max;
						vertex[4].m_z = zz;

						vertex[5].m_x = min;
						vertex[5].m_y = max;
						vertex[5].m_z = zz;

						bgfx::setState(0);
						bgfx::setStencil(BGFX_STENCIL_TEST_ALWAYS
										 | BGFX_STENCIL_FUNC_REF(1)
										 | BGFX_STENCIL_FUNC_RMASK(0xff)
										 | BGFX_STENCIL_OP_FAIL_S_REPLACE
										 | BGFX_STENCIL_OP_FAIL_Z_REPLACE
										 | BGFX_STENCIL_OP_PASS_Z_REPLACE
										 );
						bgfx::setVertexBuffer(0, &vb);
						bgfx::submit(RENDERVIEW_SHADOWMAP_0_ID, s_programs.m_black);
					}
				}

				// Draw scene into shadowmap.
				uint8_t drawNum;
				if (LightType::SpotLight == m_settings.m_lightType)
				{
					drawNum = 1;
				}
				else if (LightType::PointLight == m_settings.m_lightType)
				{
					drawNum = 4;
				}
				else //LightType::DirectionalLight == settings.m_lightType)
				{
					drawNum = uint8_t(m_settings.m_numSplits);
				}

				for (uint8_t ii = 0; ii < drawNum; ++ii)
				{
					const uint8_t viewId = RENDERVIEW_SHADOWMAP_1_ID + ii;

					uint8_t renderStateIndex = RenderState::ShadowMap_PackDepth;
					if(LightType::PointLight == m_settings.m_lightType && m_settings.m_stencilPack)
					{
						renderStateIndex = uint8_t( (ii < 2) ? RenderState::ShadowMap_PackDepthHoriz : RenderState::ShadowMap_PackDepthVert);
					}

					// Floor.
					m_hplaneMesh.submit(viewId
										, mtxFloor
										, *currentSmSettings->m_progPack
										, s_renderStates[renderStateIndex]
										);

					// Bunny.
					m_bunnyMesh.submit(viewId
									   , mtxBunny
									   , *currentSmSettings->m_progPack
									   , s_renderStates[renderStateIndex]
									   );

					// Hollow cube.
					m_hollowcubeMesh.submit(viewId
											, mtxHollowcube
											, *currentSmSettings->m_progPack
											, s_renderStates[renderStateIndex]
											);

					// Cube.
					m_cubeMesh.submit(viewId
									  , mtxCube
									  , *currentSmSettings->m_progPack
									  , s_renderStates[renderStateIndex]
									  );

					// Trees.
					for (uint8_t jj = 0; jj < numTrees; ++jj)
					{
						m_treeMesh.submit(viewId
										  , mtxTrees[jj]
										  , *currentSmSettings->m_progPack
										  , s_renderStates[renderStateIndex]
										  );
					}
				}
			}

			PackDepth::Enum depthType = (SmImpl::VSM == m_settings.m_smImpl) ? PackDepth::VSM : PackDepth::RGBA;
			bool bVsmOrEsm = (SmImpl::VSM == m_settings.m_smImpl) || (SmImpl::ESM == m_settings.m_smImpl);

			// Blur shadow map.
			if (bVsmOrEsm
				&&  currentSmSettings->m_doBlur)
			{
				bgfx::setTexture(4, s_shadowMap[0], bgfx::getTexture(s_rtShadowMap[0]) );
				bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
				screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
				bgfx::submit(RENDERVIEW_VBLUR_0_ID, s_programs.m_vBlur[depthType]);

				bgfx::setTexture(4, s_shadowMap[0], bgfx::getTexture(s_rtBlur) );
				bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
				screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
				bgfx::submit(RENDERVIEW_HBLUR_0_ID, s_programs.m_hBlur[depthType]);

				if (LightType::DirectionalLight == m_settings.m_lightType)
				{
					for (uint8_t ii = 1, jj = 2; ii < m_settings.m_numSplits; ++ii, jj+=2)
					{
						const uint8_t viewId = RENDERVIEW_VBLUR_0_ID + jj;

						bgfx::setTexture(4, s_shadowMap[0], bgfx::getTexture(s_rtShadowMap[ii]) );
						bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
						screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
						bgfx::submit(viewId, s_programs.m_vBlur[depthType]);

						bgfx::setTexture(4, s_shadowMap[0], bgfx::getTexture(s_rtBlur) );
						bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
						screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
						bgfx::submit(viewId+1, s_programs.m_hBlur[depthType]);
					}
				}
			}

			// Draw scene.
			{
				// Setup shadow mtx.
				float mtxShadow[16];

				const float ymul = (s_flipV) ? 0.5f : -0.5f;
				float zadd = (DepthImpl::Linear == m_settings.m_depthImpl) ? 0.0f : 0.5f;

				const float mtxBias[16] =
				{
					0.5f, 0.0f, 0.0f, 0.0f,
					0.0f, ymul, 0.0f, 0.0f,
					0.0f, 0.0f, 0.5f, 0.0f,
					0.5f, 0.5f, zadd, 1.0f,
				};

				if (LightType::SpotLight == m_settings.m_lightType)
				{
					float mtxTmp[16];
					bx::mtxMul(mtxTmp, lightProj[ProjType::Horizontal], mtxBias);
					bx::mtxMul(mtxShadow, lightView[0], mtxTmp); //lightViewProjBias
				}
				else if (LightType::PointLight == m_settings.m_lightType)
				{
					const float s = (s_flipV) ? 1.0f : -1.0f; //sign
					zadd = (DepthImpl::Linear == m_settings.m_depthImpl) ? 0.0f : 0.5f;

					const float mtxCropBias[2][TetrahedronFaces::Count][16] =
					{
						{ // settings.m_stencilPack == false

							{ // D3D: Green, OGL: Blue
								0.25f,    0.0f, 0.0f, 0.0f,
							 0.0f, s*0.25f, 0.0f, 0.0f,
							 0.0f,    0.0f, 0.5f, 0.0f,
								0.25f,   0.25f, zadd, 1.0f,
							},
							{ // D3D: Yellow, OGL: Red
								0.25f,    0.0f, 0.0f, 0.0f,
							 0.0f, s*0.25f, 0.0f, 0.0f,
							 0.0f,    0.0f, 0.5f, 0.0f,
								0.75f,   0.25f, zadd, 1.0f,
							},
							{ // D3D: Blue, OGL: Green
								0.25f,    0.0f, 0.0f, 0.0f,
							 0.0f, s*0.25f, 0.0f, 0.0f,
							 0.0f,    0.0f, 0.5f, 0.0f,
								0.25f,   0.75f, zadd, 1.0f,
							},
							{ // D3D: Red, OGL: Yellow
								0.25f,    0.0f, 0.0f, 0.0f,
							 0.0f, s*0.25f, 0.0f, 0.0f,
							 0.0f,    0.0f, 0.5f, 0.0f,
								0.75f,   0.75f, zadd, 1.0f,
							},
						},
						{ // settings.m_stencilPack == true

							{ // D3D: Red, OGL: Blue
								0.25f,   0.0f, 0.0f, 0.0f,
							 0.0f, s*0.5f, 0.0f, 0.0f,
							 0.0f,   0.0f, 0.5f, 0.0f,
								0.25f,   0.5f, zadd, 1.0f,
							},
							{ // D3D: Blue, OGL: Red
								0.25f,   0.0f, 0.0f, 0.0f,
							 0.0f, s*0.5f, 0.0f, 0.0f,
							 0.0f,   0.0f, 0.5f, 0.0f,
								0.75f,   0.5f, zadd, 1.0f,
							},
							{ // D3D: Green, OGL: Green
								0.5f,    0.0f, 0.0f, 0.0f,
								0.0f, s*0.25f, 0.0f, 0.0f,
								0.0f,    0.0f, 0.5f, 0.0f,
								0.5f,   0.75f, zadd, 1.0f,
							},
							{ // D3D: Yellow, OGL: Yellow
								0.5f,    0.0f, 0.0f, 0.0f,
								0.0f, s*0.25f, 0.0f, 0.0f,
								0.0f,    0.0f, 0.5f, 0.0f,
								0.5f,   0.25f, zadd, 1.0f,
							},
						}
					};

					//Use as: [stencilPack][flipV][tetrahedronFace]
					static const uint8_t cropBiasIndices[2][2][4] =
					{
						{ // settings.m_stencilPack == false
							{ 0, 1, 2, 3 }, //flipV == false
							{ 2, 3, 0, 1 }, //flipV == true
						},
						{ // settings.m_stencilPack == true
							{ 3, 2, 0, 1 }, //flipV == false
							{ 2, 3, 0, 1 }, //flipV == true
						},
					};

					for (uint8_t ii = 0; ii < TetrahedronFaces::Count; ++ii)
					{
						ProjType::Enum projType = (m_settings.m_stencilPack) ? ProjType::Enum(ii>1) : ProjType::Horizontal;
						uint8_t biasIndex = cropBiasIndices[m_settings.m_stencilPack][uint8_t(s_flipV)][ii];

						float mtxTmp[16];
						bx::mtxMul(mtxTmp, mtxYpr[ii], lightProj[projType]);
						bx::mtxMul(m_shadowMapMtx[ii], mtxTmp, mtxCropBias[m_settings.m_stencilPack][biasIndex]); //mtxYprProjBias
					}

					bx::mtxTranslate(mtxShadow //lightInvTranslate
									 , -m_pointLight.m_position.m_v[0]
									 , -m_pointLight.m_position.m_v[1]
									 , -m_pointLight.m_position.m_v[2]
									 );
				}
				else //LightType::DirectionalLight == settings.m_lightType
				{
					for (uint8_t ii = 0; ii < m_settings.m_numSplits; ++ii)
					{
						float mtxTmp[16];

						bx::mtxMul(mtxTmp, lightProj[ii], mtxBias);
						bx::mtxMul(m_shadowMapMtx[ii], lightView[0], mtxTmp); //lViewProjCropBias
					}
				}

				// Floor.
				if (LightType::DirectionalLight != m_settings.m_lightType)
				{
					bx::mtxMul(m_lightMtx, mtxFloor, mtxShadow); //not needed for directional light
				}
				m_hplaneMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
									, mtxFloor
									, *currentSmSettings->m_progDraw
									, s_renderStates[RenderState::Default]
									, true
									);

				// Bunny.
				if (LightType::DirectionalLight != m_settings.m_lightType)
				{
					bx::mtxMul(m_lightMtx, mtxBunny, mtxShadow);
				}
				m_bunnyMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
								   , mtxBunny
								   , *currentSmSettings->m_progDraw
								   , s_renderStates[RenderState::Default]
								   , true
								   );

				// Hollow cube.
				if (LightType::DirectionalLight != m_settings.m_lightType)
				{
					bx::mtxMul(m_lightMtx, mtxHollowcube, mtxShadow);
				}
				m_hollowcubeMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
										, mtxHollowcube
										, *currentSmSettings->m_progDraw
										, s_renderStates[RenderState::Default]
										, true
										);

				// Cube.
				if (LightType::DirectionalLight != m_settings.m_lightType)
				{
					bx::mtxMul(m_lightMtx, mtxCube, mtxShadow);
				}
				m_cubeMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
								  , mtxCube
								  , *currentSmSettings->m_progDraw
								  , s_renderStates[RenderState::Default]
								  , true
								  );

				// Trees.
				for (uint8_t ii = 0; ii < numTrees; ++ii)
				{
					if (LightType::DirectionalLight != m_settings.m_lightType)
					{
						bx::mtxMul(m_lightMtx, mtxTrees[ii], mtxShadow);
					}
					m_treeMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
									  , mtxTrees[ii]
									  , *currentSmSettings->m_progDraw
									  , s_renderStates[RenderState::Default]
									  , true
									  );
				}

				// Lights.
				if (LightType::SpotLight == m_settings.m_lightType || LightType::PointLight == m_settings.m_lightType)
				{
					const float lightScale[3] = { 1.5f, 1.5f, 1.5f };
					float mtx[16];
					mtxBillboard(mtx, m_viewState.m_view, m_pointLight.m_position.m_v, lightScale);
					m_vplaneMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
										, mtx
										, s_programs.m_colorTexture
										, s_renderStates[RenderState::Custom_BlendLightTexture]
										, m_texFlare
										);
				}

				// Draw floor bottom.
				float floorBottomMtx[16];
				bx::mtxSRT(floorBottomMtx
						   , floorScale //scaleX
						   , floorScale //scaleY
						   , floorScale //scaleZ
						   , 0.0f  //rotX
						   , 0.0f  //rotY
						   , 0.0f  //rotZ
						   , 0.0f  //translateX
						   , -0.1f //translateY
						   , 0.0f  //translateZ
						   );

				m_hplaneMesh.submit(RENDERVIEW_DRAWSCENE_1_ID
									, floorBottomMtx
									, s_programs.m_texture
									, s_renderStates[RenderState::Custom_DrawPlaneBottom]
									, m_texFigure
									);
			}

			// Draw depth rect.
			if (m_settings.m_drawDepthBuffer)
			{
				bgfx::setTexture(4, s_shadowMap[0], bgfx::getTexture(s_rtShadowMap[0]) );
				bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
				screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
				bgfx::submit(RENDERVIEW_DRAWDEPTH_0_ID, s_programs.m_drawDepth[depthType]);

				if (LightType::DirectionalLight == m_settings.m_lightType)
				{
					for (uint8_t ii = 1; ii < m_settings.m_numSplits; ++ii)
					{
						bgfx::setTexture(4, s_shadowMap[0], bgfx::getTexture(s_rtShadowMap[ii]) );
						bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
						screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
						bgfx::submit(RENDERVIEW_DRAWDEPTH_0_ID+ii, s_programs.m_drawDepth[depthType]);
					}
				}
			}

			// Update render target size.
			uint16_t shadowMapSize = 1 << uint32_t(currentSmSettings->m_sizePwrTwo);
			if (bLtChanged || m_currentShadowMapSize != shadowMapSize)
			{
				m_currentShadowMapSize = shadowMapSize;
				s_uniforms.m_shadowMapTexelSize = 1.0f / currentShadowMapSizef;

				{
					bgfx::destroy(s_rtShadowMap[0]);

					bgfx::TextureHandle fbtextures[] =
					{
						bgfx::createTexture2D(m_currentShadowMapSize, m_currentShadowMapSize, false, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT),
						bgfx::createTexture2D(m_currentShadowMapSize, m_currentShadowMapSize, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT),
					};
					s_rtShadowMap[0] = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
				}

				if (LightType::DirectionalLight == m_settings.m_lightType)
				{
					for (uint8_t ii = 1; ii < ShadowMapRenderTargets::Count; ++ii)
					{
						{
							bgfx::destroy(s_rtShadowMap[ii]);

							bgfx::TextureHandle fbtextures[] =
							{
								bgfx::createTexture2D(m_currentShadowMapSize, m_currentShadowMapSize, false, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT),
								bgfx::createTexture2D(m_currentShadowMapSize, m_currentShadowMapSize, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT),
							};
							s_rtShadowMap[ii] = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
						}
					}
				}

				bgfx::destroy(s_rtBlur);
				s_rtBlur = bgfx::createFrameBuffer(m_currentShadowMapSize, m_currentShadowMapSize, bgfx::TextureFormat::BGRA8);
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

	ViewState m_viewState;
	ClearValues m_clearValues;

	bgfx::VertexDecl m_posDecl;

	bgfx::TextureHandle m_texFigure;
	bgfx::TextureHandle m_texFlare;
	bgfx::TextureHandle m_texFieldstone;

	Mesh m_bunnyMesh;
	Mesh m_treeMesh;
	Mesh m_cubeMesh;
	Mesh m_hollowcubeMesh;
	Mesh m_hplaneMesh;
	Mesh m_vplaneMesh;

	float m_color[4];
	Material m_defaultMaterial;
	Light m_pointLight;
	Light m_directionalLight;

	float m_lightMtx[16];
	float m_shadowMapMtx[ShadowMapRenderTargets::Count][16];

	ShadowMapSettings m_smSettings[LightType::Count][DepthImpl::Count][SmImpl::Count];
	SceneSettings m_settings;

	uint16_t m_currentShadowMapSize;

	float m_timeAccumulatorLight;
	float m_timeAccumulatorScene;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleShadowmaps, "16-shadowmaps", "Shadow maps example.");
