/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <string>
#include <vector>
#include <algorithm>

#include "common.h"
#include "bgfx_utils.h"

#include <bgfx/bgfx.h>
#include <bx/timer.h>
#include <bx/readerwriter.h>
#include <bx/fpumath.h>
#include "entry/entry.h"
#include "camera.h"
#include "imgui/imgui.h"

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

uint32_t packUint32(uint8_t _x, uint8_t _y, uint8_t _z, uint8_t _w)
{
	union
	{
		uint32_t ui32;
		uint8_t arr[4];
	} un;

	un.arr[0] = _x;
	un.arr[1] = _y;
	un.arr[2] = _z;
	un.arr[3] = _w;

	return un.ui32;
}

uint32_t packF4u(float _x, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f)
{
	const uint8_t xx = uint8_t(_x*127.0f + 128.0f);
	const uint8_t yy = uint8_t(_y*127.0f + 128.0f);
	const uint8_t zz = uint8_t(_z*127.0f + 128.0f);
	const uint8_t ww = uint8_t(_w*127.0f + 128.0f);
	return packUint32(xx, yy, zz, ww);
}

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

void imguiEnum(SmImpl::Enum& _enum)
{
	_enum = (SmImpl::Enum)imguiChoose(_enum
			, "Hard"
			, "PCF"
			, "VSM"
			, "ESM"
			);
}

void imguiEnum(DepthImpl::Enum& _enum)
{
	_enum = (DepthImpl::Enum)imguiChoose(_enum
			, "InvZ"
			, "Linear"
			);
}

void imguiEnum(LightType::Enum& _enum)
{
	_enum = (LightType::Enum)imguiChoose(_enum
			, "Spot light"
			, "Point light"
			, "Directional light"
			);
}

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
	{ -1.0f, 0.0f,  1.0f, packF4u(0.0f, 1.0f, 0.0f), s_texcoord, s_texcoord },
	{  1.0f, 0.0f,  1.0f, packF4u(0.0f, 1.0f, 0.0f), s_texcoord, 0.0f       },
	{ -1.0f, 0.0f, -1.0f, packF4u(0.0f, 1.0f, 0.0f), 0.0f,       s_texcoord },
	{  1.0f, 0.0f, -1.0f, packF4u(0.0f, 1.0f, 0.0f), 0.0f,       0.0f       },
};

static PosNormalTexcoordVertex s_vplaneVertices[] =
{
	{ -1.0f,  1.0f, 0.0f, packF4u(0.0f, 0.0f, -1.0f), 1.0f, 1.0f },
	{  1.0f,  1.0f, 0.0f, packF4u(0.0f, 0.0f, -1.0f), 1.0f, 0.0f },
	{ -1.0f, -1.0f, 0.0f, packF4u(0.0f, 0.0f, -1.0f), 0.0f, 1.0f },
	{  1.0f, -1.0f, 0.0f, packF4u(0.0f, 0.0f, -1.0f), 0.0f, 0.0f },
};

static const uint16_t s_planeIndices[] =
{
	0, 1, 2,
	1, 3, 2,
};

static bool s_flipV = false;
static float s_texelHalf = 0.0f;

static bgfx::UniformHandle u_texColor;
static bgfx::UniformHandle u_shadowMap[ShadowMapRenderTargets::Count];
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
	float sroll  = sinf(_roll);
	float croll  = cosf(_roll);
	float spitch = sinf(_pitch);
	float cpitch = cosf(_pitch);
	float syaw   = sinf(_yaw);
	float cyaw   = cosf(_yaw);

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
		m_lightningPass  = 1.0f;

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
		bgfx::destroyUniform(u_params0);
		bgfx::destroyUniform(u_params1);
		bgfx::destroyUniform(u_params2);
		bgfx::destroyUniform(u_color);
		bgfx::destroyUniform(u_smSamplingParams);
		bgfx::destroyUniform(u_csmFarDistances);

		bgfx::destroyUniform(u_materialKa);
		bgfx::destroyUniform(u_materialKd);
		bgfx::destroyUniform(u_materialKs);

		bgfx::destroyUniform(u_tetraNormalGreen);
		bgfx::destroyUniform(u_tetraNormalYellow);
		bgfx::destroyUniform(u_tetraNormalBlue);
		bgfx::destroyUniform(u_tetraNormalRed);

		bgfx::destroyUniform(u_shadowMapMtx0);
		bgfx::destroyUniform(u_shadowMapMtx1);
		bgfx::destroyUniform(u_shadowMapMtx2);
		bgfx::destroyUniform(u_shadowMapMtx3);

		bgfx::destroyUniform(u_lightMtx);
		bgfx::destroyUniform(u_lightPosition);
		bgfx::destroyUniform(u_lightAmbientPower);
		bgfx::destroyUniform(u_lightDiffusePower);
		bgfx::destroyUniform(u_lightSpecularPower);
		bgfx::destroyUniform(u_lightSpotDirectionInner);
		bgfx::destroyUniform(u_lightAttenuationSpotOuter);
	}

	union
	{
		struct
		{
			float m_ambientPass;
			float m_lightningPass;
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
	ViewState(uint32_t _width = 1280, uint32_t _height = 720)
		: m_width(_width)
		, m_height(_height)
	{
	}

	uint32_t m_width;
	uint32_t m_height;

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
		m_vbh.idx = bgfx::invalidHandle;
		m_ibh.idx = bgfx::invalidHandle;
		m_prims.clear();
	}

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
	PrimitiveArray m_prims;
};

namespace bgfx
{
	int32_t read(bx::ReaderI* _reader, bgfx::VertexDecl& _decl);
}

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

		//TODO:
		// group.m_sphere = ...
		// group.m_aabb = ...
		// group.m_obb = ...
		// group.m_prims = ...

		m_groups.push_back(group);
	}

	void load(const char* _filePath)
	{
#define BGFX_CHUNK_MAGIC_VB  BX_MAKEFOURCC('V', 'B', ' ', 0x1)
#define BGFX_CHUNK_MAGIC_IB  BX_MAKEFOURCC('I', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_PRI BX_MAKEFOURCC('P', 'R', 'I', 0x0)

		bx::CrtFileReader reader;
		reader.open(_filePath);

		Group group;

		uint32_t chunk;
		while (4 == bx::read(&reader, chunk) )
		{
			switch (chunk)
			{
			case BGFX_CHUNK_MAGIC_VB:
				{
					bx::read(&reader, group.m_sphere);
					bx::read(&reader, group.m_aabb);
					bx::read(&reader, group.m_obb);

					bgfx::read(&reader, m_decl);
					uint16_t stride = m_decl.getStride();

					uint16_t numVertices;
					bx::read(&reader, numVertices);
					const bgfx::Memory* mem = bgfx::alloc(numVertices*stride);
					bx::read(&reader, mem->data, mem->size);

					group.m_vbh = bgfx::createVertexBuffer(mem, m_decl);
				}
				break;

			case BGFX_CHUNK_MAGIC_IB:
				{
					uint32_t numIndices;
					bx::read(&reader, numIndices);
					const bgfx::Memory* mem = bgfx::alloc(numIndices*2);
					bx::read(&reader, mem->data, mem->size);
					group.m_ibh = bgfx::createIndexBuffer(mem);
				}
				break;

			case BGFX_CHUNK_MAGIC_PRI:
				{
					uint16_t len;
					bx::read(&reader, len);

					std::string material;
					material.resize(len);
					bx::read(&reader, const_cast<char*>(material.c_str() ), len);

					uint16_t num;
					bx::read(&reader, num);

					for (uint32_t ii = 0; ii < num; ++ii)
					{
						bx::read(&reader, len);

						std::string name;
						name.resize(len);
						bx::read(&reader, const_cast<char*>(name.c_str() ), len);

						Primitive prim;
						bx::read(&reader, prim.m_startIndex);
						bx::read(&reader, prim.m_numIndices);
						bx::read(&reader, prim.m_startVertex);
						bx::read(&reader, prim.m_numVertices);
						bx::read(&reader, prim.m_sphere);
						bx::read(&reader, prim.m_aabb);
						bx::read(&reader, prim.m_obb);

						group.m_prims.push_back(prim);
					}

					m_groups.push_back(group);
					group.reset();
				}
				break;

			default:
				DBG("%08x at %d", chunk, reader.seek() );
				break;
			}
		}

		reader.close();
	}

	void unload()
	{
		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;
			bgfx::destroyVertexBuffer(group.m_vbh);

			if (bgfx::invalidHandle != group.m_ibh.idx)
			{
				bgfx::destroyIndexBuffer(group.m_ibh);
			}
		}
		m_groups.clear();
	}

	void submit(uint8_t _viewId, float* _mtx, bgfx::ProgramHandle _program, const RenderState& _renderState)
	{
		bgfx::TextureHandle texture = BGFX_INVALID_HANDLE;
		submit(_viewId, _mtx, _program, _renderState, texture);
	}

	void submit(uint8_t _viewId, float* _mtx, bgfx::ProgramHandle _program, const RenderState& _renderState, bgfx::TextureHandle _texture)
	{
		for (GroupArray::const_iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;

			// Set uniforms.
			s_uniforms.submitPerDrawUniforms();

			// Set model matrix for rendering.
			bgfx::setTransform(_mtx);
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(group.m_vbh);

			// Set textures.
			if (bgfx::invalidHandle != _texture.idx)
			{
				bgfx::setTexture(0, u_texColor, _texture);
			}

			for (uint8_t ii = 0; ii < ShadowMapRenderTargets::Count; ++ii)
			{
				bgfx::setTexture(4 + ii, u_shadowMap[ii], s_rtShadowMap[ii]);
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
	if (bgfx::checkAvailTransientVertexBuffer(3, PosColorTexCoord0Vertex::ms_decl) )
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

		bgfx::setVertexBuffer(&vb);
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

		const float nearp = l*(_near*powf(ratio, si) ) + (1 - l)*(_near + (_far - _near)*si);
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

		// Color lightning.
		m_colorLightning[SmType::Single][DepthImpl::InvZ][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lightning", "fs_shadowmaps_color_lightning_hard");
		m_colorLightning[SmType::Single][DepthImpl::InvZ][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lightning", "fs_shadowmaps_color_lightning_pcf");
		m_colorLightning[SmType::Single][DepthImpl::InvZ][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lightning", "fs_shadowmaps_color_lightning_vsm");
		m_colorLightning[SmType::Single][DepthImpl::InvZ][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lightning", "fs_shadowmaps_color_lightning_esm");

		m_colorLightning[SmType::Single][DepthImpl::Linear][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lightning_linear", "fs_shadowmaps_color_lightning_hard_linear");
		m_colorLightning[SmType::Single][DepthImpl::Linear][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lightning_linear", "fs_shadowmaps_color_lightning_pcf_linear");
		m_colorLightning[SmType::Single][DepthImpl::Linear][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lightning_linear", "fs_shadowmaps_color_lightning_vsm_linear");
		m_colorLightning[SmType::Single][DepthImpl::Linear][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lightning_linear", "fs_shadowmaps_color_lightning_esm_linear");

		m_colorLightning[SmType::Omni][DepthImpl::InvZ][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lightning_omni", "fs_shadowmaps_color_lightning_hard_omni");
		m_colorLightning[SmType::Omni][DepthImpl::InvZ][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lightning_omni", "fs_shadowmaps_color_lightning_pcf_omni");
		m_colorLightning[SmType::Omni][DepthImpl::InvZ][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lightning_omni", "fs_shadowmaps_color_lightning_vsm_omni");
		m_colorLightning[SmType::Omni][DepthImpl::InvZ][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lightning_omni", "fs_shadowmaps_color_lightning_esm_omni");

		m_colorLightning[SmType::Omni][DepthImpl::Linear][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lightning_linear_omni", "fs_shadowmaps_color_lightning_hard_linear_omni");
		m_colorLightning[SmType::Omni][DepthImpl::Linear][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lightning_linear_omni", "fs_shadowmaps_color_lightning_pcf_linear_omni");
		m_colorLightning[SmType::Omni][DepthImpl::Linear][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lightning_linear_omni", "fs_shadowmaps_color_lightning_vsm_linear_omni");
		m_colorLightning[SmType::Omni][DepthImpl::Linear][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lightning_linear_omni", "fs_shadowmaps_color_lightning_esm_linear_omni");

		m_colorLightning[SmType::Cascade][DepthImpl::InvZ][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lightning_csm", "fs_shadowmaps_color_lightning_hard_csm");
		m_colorLightning[SmType::Cascade][DepthImpl::InvZ][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lightning_csm", "fs_shadowmaps_color_lightning_pcf_csm");
		m_colorLightning[SmType::Cascade][DepthImpl::InvZ][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lightning_csm", "fs_shadowmaps_color_lightning_vsm_csm");
		m_colorLightning[SmType::Cascade][DepthImpl::InvZ][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lightning_csm", "fs_shadowmaps_color_lightning_esm_csm");

		m_colorLightning[SmType::Cascade][DepthImpl::Linear][SmImpl::Hard] = loadProgram("vs_shadowmaps_color_lightning_linear_csm", "fs_shadowmaps_color_lightning_hard_linear_csm");
		m_colorLightning[SmType::Cascade][DepthImpl::Linear][SmImpl::PCF]  = loadProgram("vs_shadowmaps_color_lightning_linear_csm", "fs_shadowmaps_color_lightning_pcf_linear_csm");
		m_colorLightning[SmType::Cascade][DepthImpl::Linear][SmImpl::VSM]  = loadProgram("vs_shadowmaps_color_lightning_linear_csm", "fs_shadowmaps_color_lightning_vsm_linear_csm");
		m_colorLightning[SmType::Cascade][DepthImpl::Linear][SmImpl::ESM]  = loadProgram("vs_shadowmaps_color_lightning_linear_csm", "fs_shadowmaps_color_lightning_esm_linear_csm");
	}

	void destroy()
	{
		// Color lightning.
		for (uint8_t ii = 0; ii < SmType::Count; ++ii)
		{
			for (uint8_t jj = 0; jj < DepthImpl::Count; ++jj)
			{
				for (uint8_t kk = 0; kk < SmImpl::Count; ++kk)
				{
					bgfx::destroyProgram(m_colorLightning[ii][jj][kk]);
				}
			}
		}

		// Pack depth.
		for (uint8_t ii = 0; ii < DepthImpl::Count; ++ii)
		{
			for (uint8_t jj = 0; jj < PackDepth::Count; ++jj)
			{
				bgfx::destroyProgram(m_packDepth[ii][jj]);
			}
		}

		// Draw depth.
		for (uint8_t ii = 0; ii < PackDepth::Count; ++ii)
		{
			bgfx::destroyProgram(m_drawDepth[ii]);
		}

		// Hblur.
		for (uint8_t ii = 0; ii < PackDepth::Count; ++ii)
		{
			bgfx::destroyProgram(m_hBlur[ii]);
		}

		// Vblur.
		for (uint8_t ii = 0; ii < PackDepth::Count; ++ii)
		{
			bgfx::destroyProgram(m_vBlur[ii]);
		}

		// Misc.
		bgfx::destroyProgram(m_colorTexture);
		bgfx::destroyProgram(m_texture);
		bgfx::destroyProgram(m_black);
	}

	bgfx::ProgramHandle m_black;
	bgfx::ProgramHandle m_texture;
	bgfx::ProgramHandle m_colorTexture;
	bgfx::ProgramHandle m_vBlur[PackDepth::Count];
	bgfx::ProgramHandle m_hBlur[PackDepth::Count];
	bgfx::ProgramHandle m_drawDepth[PackDepth::Count];
	bgfx::ProgramHandle m_packDepth[DepthImpl::Count][PackDepth::Count];
	bgfx::ProgramHandle m_colorLightning[SmType::Count][DepthImpl::Count][SmImpl::Count];
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

int _main_(int /*_argc*/, char** /*_argv*/)
{
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	ViewState viewState(1280, 720);
	ClearValues clearValues(0x00000000, 1.0f, 0);

	bgfx::init();
	bgfx::reset(viewState.m_width, viewState.m_height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

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
	u_texColor = bgfx::createUniform("u_texColor",  bgfx::UniformType::Int1);
	u_shadowMap[0] = bgfx::createUniform("u_shadowMap0", bgfx::UniformType::Int1);
	u_shadowMap[1] = bgfx::createUniform("u_shadowMap1", bgfx::UniformType::Int1);
	u_shadowMap[2] = bgfx::createUniform("u_shadowMap2", bgfx::UniformType::Int1);
	u_shadowMap[3] = bgfx::createUniform("u_shadowMap3", bgfx::UniformType::Int1);

	// Programs.
	s_programs.init();

	// Vertex declarations.
	bgfx::VertexDecl PosNormalTexcoordDecl;
	PosNormalTexcoordDecl.begin()
		.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.end();

	bgfx::VertexDecl posDecl;
	posDecl.begin();
	posDecl.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float);
	posDecl.end();

	PosColorTexCoord0Vertex::init();

	// Textures.
	bgfx::TextureHandle texFigure     = loadTexture("figure-rgba.dds");
	bgfx::TextureHandle texFlare      = loadTexture("flare.dds");
	bgfx::TextureHandle texFieldstone = loadTexture("fieldstone-rgba.dds");

	// Meshes.
	Mesh bunnyMesh;
	Mesh treeMesh;
	Mesh cubeMesh;
	Mesh hollowcubeMesh;
	Mesh hplaneMesh;
	Mesh vplaneMesh;
	bunnyMesh.load("meshes/bunny.bin");
	treeMesh.load("meshes/tree.bin");
	cubeMesh.load("meshes/cube.bin");
	hollowcubeMesh.load("meshes/hollowcube.bin");
	hplaneMesh.load(s_hplaneVertices, BX_COUNTOF(s_hplaneVertices), PosNormalTexcoordDecl, s_planeIndices, BX_COUNTOF(s_planeIndices) );
	vplaneMesh.load(s_vplaneVertices, BX_COUNTOF(s_vplaneVertices), PosNormalTexcoordDecl, s_planeIndices, BX_COUNTOF(s_planeIndices) );

	// Materials.
	Material defaultMaterial =
	{
		{ { 1.0f, 1.0f, 1.0f, 0.0f } }, //ambient
		{ { 1.0f, 1.0f, 1.0f, 0.0f } }, //diffuse
		{ { 1.0f, 1.0f, 1.0f, 0.0f } }, //specular, exponent
	};

	// Lights.
	Light pointLight =
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

	Light directionalLight =
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
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float lightMtx[16];
	float shadowMapMtx[ShadowMapRenderTargets::Count][16];
	s_uniforms.setPtrs(&defaultMaterial
					 , &pointLight
					 , color
					 , lightMtx
					 , &shadowMapMtx[ShadowMapRenderTargets::First][0]
					 , &shadowMapMtx[ShadowMapRenderTargets::Second][0]
					 , &shadowMapMtx[ShadowMapRenderTargets::Third][0]
					 , &shadowMapMtx[ShadowMapRenderTargets::Fourth][0]
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
			, &s_programs.m_colorLightning[SmType::Single][DepthImpl::InvZ][SmImpl::Hard] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Single][DepthImpl::InvZ][SmImpl::PCF] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Single][DepthImpl::InvZ][SmImpl::VSM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Single][DepthImpl::InvZ][SmImpl::ESM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Single][DepthImpl::Linear][SmImpl::Hard] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Single][DepthImpl::Linear][SmImpl::PCF] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Single][DepthImpl::Linear][SmImpl::VSM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Single][DepthImpl::Linear][SmImpl::ESM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Omni][DepthImpl::InvZ][SmImpl::Hard] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Omni][DepthImpl::InvZ][SmImpl::PCF] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Omni][DepthImpl::InvZ][SmImpl::VSM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Omni][DepthImpl::InvZ][SmImpl::ESM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Omni][DepthImpl::Linear][SmImpl::Hard] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Omni][DepthImpl::Linear][SmImpl::PCF] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Omni][DepthImpl::Linear][SmImpl::VSM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Omni][DepthImpl::Linear][SmImpl::ESM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Cascade][DepthImpl::InvZ][SmImpl::Hard] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Cascade][DepthImpl::InvZ][SmImpl::PCF] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Cascade][DepthImpl::InvZ][SmImpl::VSM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Cascade][DepthImpl::InvZ][SmImpl::ESM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Cascade][DepthImpl::Linear][SmImpl::Hard] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Cascade][DepthImpl::Linear][SmImpl::PCF] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Cascade][DepthImpl::Linear][SmImpl::VSM] //m_progDraw
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
			, &s_programs.m_colorLightning[SmType::Cascade][DepthImpl::Linear][SmImpl::ESM] //m_progDraw
		}

		}
		}
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
		float m_numSplitsf;
		float m_splitDistribution;
		uint8_t m_numSplits;
		bool m_updateLights;
		bool m_updateScene;
		bool m_drawDepthBuffer;
		bool m_showSmCoverage;
		bool m_stencilPack;
		bool m_stabilize;
	};

	SceneSettings settings;
	settings.m_lightType = LightType::SpotLight;
	settings.m_depthImpl = DepthImpl::InvZ;
	settings.m_smImpl    = SmImpl::Hard;
	settings.m_spotOuterAngle  = 45.0f;
	settings.m_spotInnerAngle  = 30.0f;
	settings.m_fovXAdjust      = 0.0f;
	settings.m_fovYAdjust      = 0.0f;
	settings.m_coverageSpotL   = 90.0f;
	settings.m_numSplitsf      = 4.0f;
	settings.m_splitDistribution = 0.6f;
	settings.m_numSplits       = uint8_t(settings.m_numSplitsf);
	settings.m_updateLights    = true;
	settings.m_updateScene     = true;
	settings.m_drawDepthBuffer = false;
	settings.m_showSmCoverage  = false;
	settings.m_stencilPack     = true;
	settings.m_stabilize       = true;

	ShadowMapSettings* currentSmSettings = &smSettings[settings.m_lightType][settings.m_depthImpl][settings.m_smImpl];

	// Render targets.
	uint16_t shadowMapSize = 1 << uint32_t(currentSmSettings->m_sizePwrTwo);
	uint16_t currentShadowMapSize = shadowMapSize;
	float currentShadowMapSizef = float(int16_t(currentShadowMapSize) );
	s_uniforms.m_shadowMapTexelSize = 1.0f / currentShadowMapSizef;
	for (uint8_t ii = 0; ii < ShadowMapRenderTargets::Count; ++ii)
	{
		bgfx::TextureHandle fbtextures[] =
		{
			bgfx::createTexture2D(currentShadowMapSize, currentShadowMapSize, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT),
			bgfx::createTexture2D(currentShadowMapSize, currentShadowMapSize, 1, bgfx::TextureFormat::D24S8),
		};
		s_rtShadowMap[ii] = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
	}
	s_rtBlur = bgfx::createFrameBuffer(currentShadowMapSize, currentShadowMapSize, bgfx::TextureFormat::BGRA8);

	// Setup camera.
	float initialPos[3] = { 0.0f, 60.0f, -105.0f };
	cameraCreate();
	cameraSetPosition(initialPos);
	cameraSetVerticalAngle(-0.45f);

	// Set view and projection matrices.
	const float camFovy    = 60.0f;
	const float camAspect  = float(int32_t(viewState.m_width) ) / float(int32_t(viewState.m_height) );
	const float camNear    = 0.1f;
	const float camFar     = 2000.0f;
	const float projHeight = 1.0f/tanf(bx::toRad(camFovy)*0.5f);
	const float projWidth  = projHeight * 1.0f/camAspect;
	bx::mtxProj(viewState.m_proj, camFovy, camAspect, camNear, camFar);
	cameraGetViewMtx(viewState.m_view);

	float timeAccumulatorLight = 0.0f;
	float timeAccumulatorScene = 0.0f;

	entry::MouseState mouseState;
	while (!entry::processEvents(viewState.m_width, viewState.m_height, debug, reset, &mouseState) )
	{
		// Imgui.
		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
			, mouseState.m_mz
			, viewState.m_width
			, viewState.m_height
			);

		static int32_t rightScrollArea = 0;
		imguiBeginScrollArea("Settings", viewState.m_width - 256 - 10, 10, 256, 660, &rightScrollArea);

#define IMGUI_FLOAT_SLIDER(_name, _val) \
			imguiSlider(_name \
					, _val \
					, *( ((float*)&_val)+1) \
					, *( ((float*)&_val)+2) \
					, *( ((float*)&_val)+3) \
					)

		imguiBool("Update lights", settings.m_updateLights);
		imguiBool("Update scene", settings.m_updateScene);

		imguiSeparatorLine();
		imguiLabel("Shadow map depth:");
		imguiEnum(settings.m_depthImpl);
	    currentSmSettings = &smSettings[settings.m_lightType][settings.m_depthImpl][settings.m_smImpl];

		imguiSeparator();
		imguiBool("Draw depth buffer.", settings.m_drawDepthBuffer);
		if (settings.m_drawDepthBuffer)
		{
			IMGUI_FLOAT_SLIDER("Depth value pow:", currentSmSettings->m_depthValuePow);
		}

		imguiSeparatorLine();
		imguiLabel("Shadow Map implementation:");
		imguiEnum(settings.m_smImpl);
	    currentSmSettings = &smSettings[settings.m_lightType][settings.m_depthImpl][settings.m_smImpl];

		imguiSeparator();
		IMGUI_FLOAT_SLIDER("Bias:", currentSmSettings->m_bias);
		IMGUI_FLOAT_SLIDER("Normal offset:", currentSmSettings->m_normalOffset);
		imguiSeparator();
		if (LightType::DirectionalLight != settings.m_lightType)
		{
			IMGUI_FLOAT_SLIDER("Near plane:", currentSmSettings->m_near);
		}
		IMGUI_FLOAT_SLIDER("Far plane:", currentSmSettings->m_far);

		imguiSeparator();
		switch(settings.m_smImpl)
		{
			case SmImpl::Hard:
				//imguiLabel("Hard");
				break;

			case SmImpl::PCF:
				imguiLabel("PCF");
				IMGUI_FLOAT_SLIDER("X Offset:", currentSmSettings->m_xOffset);
				IMGUI_FLOAT_SLIDER("Y Offset:", currentSmSettings->m_yOffset);
				break;

			case SmImpl::VSM:
				imguiLabel("VSM");
				IMGUI_FLOAT_SLIDER("Min variance", currentSmSettings->m_customParam0);
				IMGUI_FLOAT_SLIDER("Depth multiplier", currentSmSettings->m_customParam1);
				imguiBool("Blur shadow map", currentSmSettings->m_doBlur);
				if (currentSmSettings->m_doBlur)
				{
					IMGUI_FLOAT_SLIDER("Blur X Offset:", currentSmSettings->m_xOffset);
					IMGUI_FLOAT_SLIDER("Blur Y Offset:", currentSmSettings->m_yOffset);
				}
				break;

			case SmImpl::ESM:
				imguiLabel("ESM");
				IMGUI_FLOAT_SLIDER("ESM Hardness", currentSmSettings->m_customParam0);
				IMGUI_FLOAT_SLIDER("Depth multiplier", currentSmSettings->m_customParam1);
				imguiBool("Blur shadow map", currentSmSettings->m_doBlur);
				if (currentSmSettings->m_doBlur)
				{
					IMGUI_FLOAT_SLIDER("Blur X Offset:", currentSmSettings->m_xOffset);
					IMGUI_FLOAT_SLIDER("Blur Y Offset:", currentSmSettings->m_yOffset);
				}
				break;

			default:
				break;
		};

		imguiEndScrollArea();

		static int32_t leftScrollArea = 0;
		imguiBeginScrollArea("Light", 10, 70, 256, 334, &leftScrollArea);

		const LightType::Enum ltBefore = settings.m_lightType;
		imguiEnum(settings.m_lightType);
		const LightType::Enum ltAfter = settings.m_lightType;
		const bool bLtChanged = (ltAfter != ltBefore);

		imguiSeparator();
		imguiBool("Show shadow map coverage.", settings.m_showSmCoverage);

		imguiSeparator();
		imguiLabel("Shadow map resolution: %ux%u", currentShadowMapSize, currentShadowMapSize);
		IMGUI_FLOAT_SLIDER(" ", currentSmSettings->m_sizePwrTwo);

		imguiSeparatorLine();
		if (LightType::SpotLight == settings.m_lightType)
		{
			imguiLabel("Spot light");
			imguiSlider("Shadow map area:", settings.m_coverageSpotL, 45.0f, 120.0f, 1.0f);

			imguiSeparator();
			imguiSlider("Spot outer cone:", settings.m_spotOuterAngle, 0.0f, 91.0f, 0.1f);
			imguiSlider("Spot inner cone:", settings.m_spotInnerAngle, 0.0f, 90.0f, 0.1f);
		}
		else if (LightType::PointLight == settings.m_lightType)
		{
			imguiLabel("Point light");
			imguiBool("Stencil pack", settings.m_stencilPack);

			imguiSlider("Fov X adjust:", settings.m_fovXAdjust, -20.0f, 20.0f, 0.0001f);
			imguiSlider("Fov Y adjust:", settings.m_fovYAdjust, -20.0f, 20.0f, 0.0001f);
		}
		else if (LightType::DirectionalLight == settings.m_lightType)
		{
			imguiLabel("Directional light");
			imguiBool("Stabilize cascades", settings.m_stabilize);
			imguiSlider("Cascade splits:", settings.m_numSplitsf, 1.0f, 4.0f, 1.0f);
			imguiSlider("Cascade distribution:", settings.m_splitDistribution, 0.0f, 1.0f, 0.001f);
			settings.m_numSplits = uint8_t(settings.m_numSplitsf);
		}

#undef IMGUI_FLOAT_SLIDER

		imguiEndScrollArea();
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
		s_uniforms.m_showSmCoverage  = float(settings.m_showSmCoverage);
		s_uniforms.m_lightPtr = (LightType::DirectionalLight == settings.m_lightType) ? &directionalLight : &pointLight;

		if (LightType::SpotLight == settings.m_lightType)
		{
			pointLight.m_attenuationSpotOuter.m_outer = settings.m_spotOuterAngle;
			pointLight.m_spotDirectionInner.m_inner   = settings.m_spotInnerAngle;
		}
		else
		{
			pointLight.m_attenuationSpotOuter.m_outer = 91.0f; //above 90.0f means point light
		}

		s_uniforms.submitPerFrameUniforms();

		// Time.
		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;
		const float deltaTime = float(frameTime/freq);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/16-shadowmaps");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Shadow maps example.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Update camera.
		cameraUpdate(deltaTime, mouseState);

		// Update view mtx.
		cameraGetViewMtx(viewState.m_view);

		// Update lights.
		pointLight.computeViewSpaceComponents(viewState.m_view);
		directionalLight.computeViewSpaceComponents(viewState.m_view);

		// Update time accumulators.
		if (settings.m_updateLights) { timeAccumulatorLight += deltaTime; }
		if (settings.m_updateScene)  { timeAccumulatorScene += deltaTime; }

		// Setup lights.
		pointLight.m_position.m_x = cosf(timeAccumulatorLight) * 20.0f;
		pointLight.m_position.m_y = 26.0f;
		pointLight.m_position.m_z = sinf(timeAccumulatorLight) * 20.0f;
		pointLight.m_spotDirectionInner.m_x = -pointLight.m_position.m_x;
		pointLight.m_spotDirectionInner.m_y = -pointLight.m_position.m_y;
		pointLight.m_spotDirectionInner.m_z = -pointLight.m_position.m_z;

		directionalLight.m_position.m_x = -cosf(timeAccumulatorLight);
		directionalLight.m_position.m_y = -1.0f;
		directionalLight.m_position.m_z = -sinf(timeAccumulatorLight);

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
			, 1.56f - timeAccumulatorScene
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
			, 1.56f - timeAccumulatorScene
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
			, 1.56f - timeAccumulatorScene
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
				, sinf(float(ii)*2.0f*bx::pi/float(numTrees) ) * 60.0f
				, 0.0f
				, cosf(float(ii)*2.0f*bx::pi/float(numTrees) ) * 60.0f
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
		bx::mtxOrtho(screenProj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);

	    if (LightType::SpotLight == settings.m_lightType)
		{
			const float fovy = settings.m_coverageSpotL;
			const float aspect = 1.0f;
			bx::mtxProj(lightProj[ProjType::Horizontal], fovy, aspect, currentSmSettings->m_near, currentSmSettings->m_far);

			//For linear depth, prevent depth division by variable w-component in shaders and divide here by far plane
			if (DepthImpl::Linear == settings.m_depthImpl)
			{
				lightProj[ProjType::Horizontal][10] /= currentSmSettings->m_far;
				lightProj[ProjType::Horizontal][14] /= currentSmSettings->m_far;
			}

			float at[3];
			bx::vec3Add(at, pointLight.m_position.m_v, pointLight.m_spotDirectionInner.m_v);
			bx::mtxLookAt(lightView[TetrahedronFaces::Green], pointLight.m_position.m_v, at);
		}
		else if (LightType::PointLight == settings.m_lightType)
		{
			float ypr[TetrahedronFaces::Count][3] =
			{
				{ bx::toRad(  0.0f), bx::toRad( 27.36780516f), bx::toRad(0.0f) },
				{ bx::toRad(180.0f), bx::toRad( 27.36780516f), bx::toRad(0.0f) },
				{ bx::toRad(-90.0f), bx::toRad(-27.36780516f), bx::toRad(0.0f) },
				{ bx::toRad( 90.0f), bx::toRad(-27.36780516f), bx::toRad(0.0f) },
			};


			if (settings.m_stencilPack)
			{
				const float fovx = 143.98570868f + 3.51f + settings.m_fovXAdjust;
				const float fovy = 125.26438968f + 9.85f + settings.m_fovYAdjust;
				const float aspect = tanf(bx::toRad(fovx*0.5f) )/tanf(bx::toRad(fovy*0.5f) );

				bx::mtxProj(lightProj[ProjType::Vertical]
						, fovx
						, aspect
						, currentSmSettings->m_near
						, currentSmSettings->m_far
						);

				//For linear depth, prevent depth division by variable w-component in shaders and divide here by far plane
				if (DepthImpl::Linear == settings.m_depthImpl)
				{
					lightProj[ProjType::Vertical][10] /= currentSmSettings->m_far;
					lightProj[ProjType::Vertical][14] /= currentSmSettings->m_far;
				}

				ypr[TetrahedronFaces::Green ][2] = bx::toRad(180.0f);
				ypr[TetrahedronFaces::Yellow][2] = bx::toRad(  0.0f);
				ypr[TetrahedronFaces::Blue  ][2] = bx::toRad( 90.0f);
				ypr[TetrahedronFaces::Red   ][2] = bx::toRad(-90.0f);
			}

			const float fovx = 143.98570868f + 7.8f + settings.m_fovXAdjust;
			const float fovy = 125.26438968f + 3.0f + settings.m_fovYAdjust;
			const float aspect = tanf(bx::toRad(fovx*0.5f) )/tanf(bx::toRad(fovy*0.5f) );

			bx::mtxProj(lightProj[ProjType::Horizontal], fovy, aspect, currentSmSettings->m_near, currentSmSettings->m_far);

			//For linear depth, prevent depth division by variable w component in shaders and divide here by far plane
			if (DepthImpl::Linear == settings.m_depthImpl)
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
					-bx::vec3Dot(pointLight.m_position.m_v, &mtxTmp[0]),
					-bx::vec3Dot(pointLight.m_position.m_v, &mtxTmp[4]),
					-bx::vec3Dot(pointLight.m_position.m_v, &mtxTmp[8]),
				};

				bx::mtxTranspose(mtxYpr[ii], mtxTmp);

				memcpy(lightView[ii], mtxYpr[ii], 12*sizeof(float) );
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
				  -directionalLight.m_position.m_x
				, -directionalLight.m_position.m_y
				, -directionalLight.m_position.m_z
			};
			float at[3] = { 0.0f, 0.0f, 0.0f };
			bx::mtxLookAt(lightView[0], eye, at);

			// Compute camera inverse view mtx.
			float mtxViewInv[16];
			bx::mtxInverse(mtxViewInv, viewState.m_view);

			// Compute split distances.
			const uint8_t maxNumSplits = 4;
			BX_CHECK(maxNumSplits >= settings.m_numSplits, "Error! Max num splits.");

			float splitSlices[maxNumSplits*2];
			splitFrustum(splitSlices, settings.m_numSplits, currentSmSettings->m_near, currentSmSettings->m_far, settings.m_splitDistribution);

			// Update uniforms.
			for (uint8_t ii = 0, ff = 1; ii < settings.m_numSplits; ++ii, ff+=2)
			{
				// This lags for 1 frame, but it's not a problem.
				s_uniforms.m_csmFarDistances[ii] = splitSlices[ff];
			}

			float mtxProj[16];
			bx::mtxOrtho(mtxProj, 1.0f, -1.0f, 1.0f, -1.0f, -currentSmSettings->m_far, currentSmSettings->m_far);

			const uint8_t numCorners = 8;
			float frustumCorners[maxNumSplits][numCorners][3];
			for (uint8_t ii = 0, nn = 0, ff = 1; ii < settings.m_numSplits; ++ii, nn+=2, ff+=2)
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
					min[0] = bx::fmin(min[0], lightSpaceFrustumCorner[0]);
					max[0] = bx::fmax(max[0], lightSpaceFrustumCorner[0]);
					min[1] = bx::fmin(min[1], lightSpaceFrustumCorner[1]);
					max[1] = bx::fmax(max[1], lightSpaceFrustumCorner[1]);
					min[2] = bx::fmin(min[2], lightSpaceFrustumCorner[2]);
					max[2] = bx::fmax(max[2], lightSpaceFrustumCorner[2]);
				}

				float minproj[3];
				float maxproj[3];
				bx::vec3MulMtxH(minproj, min, mtxProj);
				bx::vec3MulMtxH(maxproj, max, mtxProj);

				float offsetx, offsety;
				float scalex, scaley;

				scalex = 2.0f / (maxproj[0] - minproj[0]);
				scaley = 2.0f / (maxproj[1] - minproj[1]);

				if (settings.m_stabilize)
				{
					const float quantizer = 64.0f;
					scalex = quantizer / ceilf(quantizer / scalex);
					scaley = quantizer / ceilf(quantizer / scaley);
				}

				offsetx = 0.5f * (maxproj[0] + minproj[0]) * scalex;
				offsety = 0.5f * (maxproj[1] + minproj[1]) * scaley;

				if (settings.m_stabilize)
				{
					const float halfSize = currentShadowMapSizef * 0.5f;
					offsetx = ceilf(offsetx * halfSize) / halfSize;
					offsety = ceilf(offsety * halfSize) / halfSize;
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
		for (uint32_t ii = 0; ii < RENDERVIEW_DRAWDEPTH_3_ID+1; ++ii)
		{
			bgfx::setViewFrameBuffer(ii, invalidRt);
		}

		// Determine on-screen rectangle size where depth buffer will be drawn.
		uint16_t depthRectHeight = uint16_t(float(viewState.m_height) / 2.5f);
		uint16_t depthRectWidth  = depthRectHeight;
		uint16_t depthRectX = 0;
		uint16_t depthRectY = viewState.m_height - depthRectHeight;

		// Setup views and render targets.
		bgfx::setViewRect(0, 0, 0, viewState.m_width, viewState.m_height);
		bgfx::setViewTransform(0, viewState.m_view, viewState.m_proj);

		if (LightType::SpotLight == settings.m_lightType)
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

			bgfx::setViewRect(RENDERVIEW_SHADOWMAP_0_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_SHADOWMAP_1_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_VBLUR_0_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_HBLUR_0_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_DRAWSCENE_0_ID, 0, 0, viewState.m_width, viewState.m_height);
			bgfx::setViewRect(RENDERVIEW_DRAWSCENE_1_ID, 0, 0, viewState.m_width, viewState.m_height);
			bgfx::setViewRect(RENDERVIEW_DRAWDEPTH_0_ID, depthRectX, depthRectY, depthRectWidth, depthRectHeight);

			bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_0_ID, screenView, screenProj);
			bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_1_ID, lightView[0], lightProj[ProjType::Horizontal]);
			bgfx::setViewTransform(RENDERVIEW_VBLUR_0_ID, screenView, screenProj);
			bgfx::setViewTransform(RENDERVIEW_HBLUR_0_ID, screenView, screenProj);
			bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_0_ID, viewState.m_view, viewState.m_proj);
			bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_1_ID, viewState.m_view, viewState.m_proj);
			bgfx::setViewTransform(RENDERVIEW_DRAWDEPTH_0_ID, screenView, screenProj);

			bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_0_ID, s_rtShadowMap[0]);
			bgfx::setViewFrameBuffer(RENDERVIEW_SHADOWMAP_1_ID, s_rtShadowMap[0]);
			bgfx::setViewFrameBuffer(RENDERVIEW_VBLUR_0_ID, s_rtBlur);
			bgfx::setViewFrameBuffer(RENDERVIEW_HBLUR_0_ID, s_rtShadowMap[0]);
		}
		else if (LightType::PointLight == settings.m_lightType)
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

			bgfx::setViewRect(RENDERVIEW_SHADOWMAP_0_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			if (settings.m_stencilPack)
			{
				const uint16_t f = currentShadowMapSize;   //full size
				const uint16_t h = currentShadowMapSize/2; //half size
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_1_ID, 0, 0, f, h);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_2_ID, 0, h, f, h);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_3_ID, 0, 0, h, f);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_4_ID, h, 0, h, f);
			}
			else
			{
				const uint16_t h = currentShadowMapSize/2; //half size
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_1_ID, 0, 0, h, h);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_2_ID, h, 0, h, h);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_3_ID, 0, h, h, h);
				bgfx::setViewRect(RENDERVIEW_SHADOWMAP_4_ID, h, h, h, h);
			}
			bgfx::setViewRect(RENDERVIEW_VBLUR_0_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_HBLUR_0_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_DRAWSCENE_0_ID, 0, 0, viewState.m_width, viewState.m_height);
			bgfx::setViewRect(RENDERVIEW_DRAWSCENE_1_ID, 0, 0, viewState.m_width, viewState.m_height);
			bgfx::setViewRect(RENDERVIEW_DRAWDEPTH_0_ID, depthRectX, depthRectY, depthRectWidth, depthRectHeight);

			bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_0_ID, screenView, screenProj);
			bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_1_ID, lightView[TetrahedronFaces::Green],  lightProj[ProjType::Horizontal]);
			bgfx::setViewTransform(RENDERVIEW_SHADOWMAP_2_ID, lightView[TetrahedronFaces::Yellow], lightProj[ProjType::Horizontal]);
			if(settings.m_stencilPack)
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
			bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_0_ID, viewState.m_view, viewState.m_proj);
			bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_1_ID, viewState.m_view, viewState.m_proj);
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

			depthRectHeight = viewState.m_height / 3;
			depthRectWidth  = depthRectHeight;
			depthRectX = 0;
			depthRectY = viewState.m_height - depthRectHeight;

			bgfx::setViewRect(RENDERVIEW_SHADOWMAP_1_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_SHADOWMAP_2_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_SHADOWMAP_3_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_SHADOWMAP_4_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_VBLUR_0_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_HBLUR_0_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_VBLUR_1_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_HBLUR_1_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_VBLUR_2_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_HBLUR_2_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_VBLUR_3_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_HBLUR_3_ID, 0, 0, currentShadowMapSize, currentShadowMapSize);
			bgfx::setViewRect(RENDERVIEW_DRAWSCENE_0_ID, 0, 0, viewState.m_width, viewState.m_height);
			bgfx::setViewRect(RENDERVIEW_DRAWSCENE_1_ID, 0, 0, viewState.m_width, viewState.m_height);
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
			bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_0_ID, viewState.m_view, viewState.m_proj);
			bgfx::setViewTransform(RENDERVIEW_DRAWSCENE_1_ID, viewState.m_view, viewState.m_proj);
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
				, clearValues.m_clearRgba
				, clearValues.m_clearDepth
				, clearValues.m_clearStencil
				);
		bgfx::touch(0);

		// Clear shadowmap rendertarget at beginning.
		const uint8_t flags0 = (LightType::DirectionalLight == settings.m_lightType)
							 ? 0
							 : BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL
							 ;

		bgfx::setViewClear(RENDERVIEW_SHADOWMAP_0_ID
				, flags0
				, 0xfefefefe //blur fails on completely white regions
				, clearValues.m_clearDepth
				, clearValues.m_clearStencil
				);
		bgfx::touch(RENDERVIEW_SHADOWMAP_0_ID);

		const uint8_t flags1 = (LightType::DirectionalLight == settings.m_lightType)
							 ? BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
							 : 0
							 ;

		for (uint8_t ii = 0; ii < 4; ++ii)
		{
			bgfx::setViewClear(RENDERVIEW_SHADOWMAP_1_ID+ii
					, flags1
					, 0xfefefefe //blur fails on completely white regions
					, clearValues.m_clearDepth
					, clearValues.m_clearStencil
					);
			bgfx::touch(RENDERVIEW_SHADOWMAP_1_ID+ii);
		}

		// Render.

		// Craft shadow map.
		{
			// Craft stencil mask for point light shadow map packing.
			if(LightType::PointLight == settings.m_lightType && settings.m_stencilPack)
			{
				if (bgfx::checkAvailTransientVertexBuffer(6, posDecl) )
				{
					struct Pos
					{
						float m_x, m_y, m_z;
					};

					bgfx::TransientVertexBuffer vb;
					bgfx::allocTransientVertexBuffer(&vb, 6, posDecl);
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
					bgfx::setVertexBuffer(&vb);
					bgfx::submit(RENDERVIEW_SHADOWMAP_0_ID, s_programs.m_black);
				}
			}

			// Draw scene into shadowmap.
			uint8_t drawNum;
			if (LightType::SpotLight == settings.m_lightType)
			{
				drawNum = 1;
			}
			else if (LightType::PointLight == settings.m_lightType)
			{
				drawNum = 4;
			}
			else //LightType::DirectionalLight == settings.m_lightType)
			{
				drawNum = settings.m_numSplits;
			}

			for (uint8_t ii = 0; ii < drawNum; ++ii)
			{
				const uint8_t viewId = RENDERVIEW_SHADOWMAP_1_ID + ii;

				uint8_t renderStateIndex = RenderState::ShadowMap_PackDepth;
				if(LightType::PointLight == settings.m_lightType && settings.m_stencilPack)
				{
					renderStateIndex = (ii < 2) ? RenderState::ShadowMap_PackDepthHoriz : RenderState::ShadowMap_PackDepthVert;
				}

				// Floor.
				hplaneMesh.submit(viewId
						, mtxFloor
						, *currentSmSettings->m_progPack
						, s_renderStates[renderStateIndex]
						);

				// Bunny.
				bunnyMesh.submit(viewId
						, mtxBunny
						, *currentSmSettings->m_progPack
						, s_renderStates[renderStateIndex]
						);

				// Hollow cube.
				hollowcubeMesh.submit(viewId
						, mtxHollowcube
						, *currentSmSettings->m_progPack
						, s_renderStates[renderStateIndex]
						);

				// Cube.
				cubeMesh.submit(viewId
						, mtxCube
						, *currentSmSettings->m_progPack
						, s_renderStates[renderStateIndex]
						);

				// Trees.
				for (uint8_t jj = 0; jj < numTrees; ++jj)
				{
					treeMesh.submit(viewId
							, mtxTrees[jj]
							, *currentSmSettings->m_progPack
							, s_renderStates[renderStateIndex]
							);
				}
			}
		}

		PackDepth::Enum depthType = (SmImpl::VSM == settings.m_smImpl) ? PackDepth::VSM : PackDepth::RGBA;
		bool bVsmOrEsm = (SmImpl::VSM == settings.m_smImpl) || (SmImpl::ESM == settings.m_smImpl);

		// Blur shadow map.
		if (bVsmOrEsm
		&&  currentSmSettings->m_doBlur)
		{
			bgfx::setTexture(4, u_shadowMap[0], s_rtShadowMap[0]);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
			bgfx::submit(RENDERVIEW_VBLUR_0_ID, s_programs.m_vBlur[depthType]);

			bgfx::setTexture(4, u_shadowMap[0], s_rtBlur);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
			bgfx::submit(RENDERVIEW_HBLUR_0_ID, s_programs.m_hBlur[depthType]);

			if (LightType::DirectionalLight == settings.m_lightType)
			{
				for (uint8_t ii = 1, jj = 2; ii < settings.m_numSplits; ++ii, jj+=2)
				{
					const uint8_t viewId = RENDERVIEW_VBLUR_0_ID + jj;

					bgfx::setTexture(4, u_shadowMap[0], s_rtShadowMap[ii]);
					bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
					screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
					bgfx::submit(viewId, s_programs.m_vBlur[depthType]);

					bgfx::setTexture(4, u_shadowMap[0], s_rtBlur);
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
			float zadd = (DepthImpl::Linear == settings.m_depthImpl) ? 0.0f : 0.5f;

			const float mtxBias[16] =
			{
				0.5f, 0.0f, 0.0f, 0.0f,
				0.0f, ymul, 0.0f, 0.0f,
				0.0f, 0.0f, 0.5f, 0.0f,
				0.5f, 0.5f, zadd, 1.0f,
			};

			if (LightType::SpotLight == settings.m_lightType)
			{
				float mtxTmp[16];
				bx::mtxMul(mtxTmp, lightProj[ProjType::Horizontal], mtxBias);
				bx::mtxMul(mtxShadow, lightView[0], mtxTmp); //lightViewProjBias
			}
			else if (LightType::PointLight == settings.m_lightType)
			{
				const float s = (s_flipV) ? 1.0f : -1.0f; //sign
				zadd = (DepthImpl::Linear == settings.m_depthImpl) ? 0.0f : 0.5f;

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
					ProjType::Enum projType = (settings.m_stencilPack) ? ProjType::Enum(ii>1) : ProjType::Horizontal;
					uint8_t biasIndex = cropBiasIndices[settings.m_stencilPack][uint8_t(s_flipV)][ii];

					float mtxTmp[16];
					bx::mtxMul(mtxTmp, mtxYpr[ii], lightProj[projType]);
					bx::mtxMul(shadowMapMtx[ii], mtxTmp, mtxCropBias[settings.m_stencilPack][biasIndex]); //mtxYprProjBias
				}

				bx::mtxTranslate(mtxShadow //lightInvTranslate
						, -pointLight.m_position.m_v[0]
						, -pointLight.m_position.m_v[1]
						, -pointLight.m_position.m_v[2]
						);
			}
			else //LightType::DirectionalLight == settings.m_lightType
			{
				for (uint8_t ii = 0; ii < settings.m_numSplits; ++ii)
				{
					float mtxTmp[16];

					bx::mtxMul(mtxTmp, lightProj[ii], mtxBias);
					bx::mtxMul(shadowMapMtx[ii], lightView[0], mtxTmp); //lViewProjCropBias
				}
			}

			// Floor.
			if (LightType::DirectionalLight != settings.m_lightType)
			{
				bx::mtxMul(lightMtx, mtxFloor, mtxShadow); //not needed for directional light
			}
			hplaneMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
					, mtxFloor
					, *currentSmSettings->m_progDraw
					, s_renderStates[RenderState::Default]
					);

			// Bunny.
			if (LightType::DirectionalLight != settings.m_lightType)
			{
				bx::mtxMul(lightMtx, mtxBunny, mtxShadow);
			}
			bunnyMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
					, mtxBunny
					, *currentSmSettings->m_progDraw
					, s_renderStates[RenderState::Default]
					);

			// Hollow cube.
			if (LightType::DirectionalLight != settings.m_lightType)
			{
				bx::mtxMul(lightMtx, mtxHollowcube, mtxShadow);
			}
			hollowcubeMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
					, mtxHollowcube
					, *currentSmSettings->m_progDraw
					, s_renderStates[RenderState::Default]
					);

			// Cube.
			if (LightType::DirectionalLight != settings.m_lightType)
			{
				bx::mtxMul(lightMtx, mtxCube, mtxShadow);
			}
			cubeMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
					, mtxCube
					, *currentSmSettings->m_progDraw
					, s_renderStates[RenderState::Default]
					);

			// Trees.
			for (uint8_t ii = 0; ii < numTrees; ++ii)
			{
				if (LightType::DirectionalLight != settings.m_lightType)
				{
					bx::mtxMul(lightMtx, mtxTrees[ii], mtxShadow);
				}
				treeMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
						, mtxTrees[ii]
						, *currentSmSettings->m_progDraw
						, s_renderStates[RenderState::Default]
						);
			}

			// Lights.
			if (LightType::SpotLight == settings.m_lightType || LightType::PointLight == settings.m_lightType)
			{
				const float lightScale[3] = { 1.5f, 1.5f, 1.5f };
				float mtx[16];
				mtxBillboard(mtx, viewState.m_view, pointLight.m_position.m_v, lightScale);
				vplaneMesh.submit(RENDERVIEW_DRAWSCENE_0_ID
						, mtx
						, s_programs.m_colorTexture
						, s_renderStates[RenderState::Custom_BlendLightTexture]
						, texFlare
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

			hplaneMesh.submit(RENDERVIEW_DRAWSCENE_1_ID
					, floorBottomMtx
					, s_programs.m_texture
					, s_renderStates[RenderState::Custom_DrawPlaneBottom]
					, texFigure
					);
		}

		// Draw depth rect.
		if (settings.m_drawDepthBuffer)
		{
			bgfx::setTexture(4, u_shadowMap[0], s_rtShadowMap[0]);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
			bgfx::submit(RENDERVIEW_DRAWDEPTH_0_ID, s_programs.m_drawDepth[depthType]);

			if (LightType::DirectionalLight == settings.m_lightType)
			{
				for (uint8_t ii = 1; ii < settings.m_numSplits; ++ii)
				{
					bgfx::setTexture(4, u_shadowMap[0], s_rtShadowMap[ii]);
					bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
					screenSpaceQuad(currentShadowMapSizef, currentShadowMapSizef, s_flipV);
					bgfx::submit(RENDERVIEW_DRAWDEPTH_0_ID+ii, s_programs.m_drawDepth[depthType]);
				}
			}
		}

		// Update render target size.
		shadowMapSize = 1 << uint32_t(currentSmSettings->m_sizePwrTwo);
		if (bLtChanged || currentShadowMapSize != shadowMapSize)
		{
			currentShadowMapSize = shadowMapSize;
			currentShadowMapSizef = float(int16_t(currentShadowMapSize) );
			s_uniforms.m_shadowMapTexelSize = 1.0f / currentShadowMapSizef;

			{
				bgfx::destroyFrameBuffer(s_rtShadowMap[0]);

				bgfx::TextureHandle fbtextures[] =
				{
					bgfx::createTexture2D(currentShadowMapSize, currentShadowMapSize, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT),
					bgfx::createTexture2D(currentShadowMapSize, currentShadowMapSize, 1, bgfx::TextureFormat::D24S8),
				};
				s_rtShadowMap[0] = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
			}

			if (LightType::DirectionalLight == settings.m_lightType)
			{
				for (uint8_t ii = 1; ii < ShadowMapRenderTargets::Count; ++ii)
				{
					{
						bgfx::destroyFrameBuffer(s_rtShadowMap[ii]);

						bgfx::TextureHandle fbtextures[] =
						{
							bgfx::createTexture2D(currentShadowMapSize, currentShadowMapSize, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT),
							bgfx::createTexture2D(currentShadowMapSize, currentShadowMapSize, 1, bgfx::TextureFormat::D24S8),
						};
						s_rtShadowMap[ii] = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
					}
				}
			}

			bgfx::destroyFrameBuffer(s_rtBlur);
			s_rtBlur = bgfx::createFrameBuffer(currentShadowMapSize, currentShadowMapSize, bgfx::TextureFormat::BGRA8);
		}

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();

	}

	bunnyMesh.unload();
	treeMesh.unload();
	cubeMesh.unload();
	hollowcubeMesh.unload();
	hplaneMesh.unload();
	vplaneMesh.unload();

	bgfx::destroyTexture(texFigure);
	bgfx::destroyTexture(texFieldstone);
	bgfx::destroyTexture(texFlare);

	for (uint8_t ii = 0; ii < ShadowMapRenderTargets::Count; ++ii)
	{
		bgfx::destroyFrameBuffer(s_rtShadowMap[ii]);
	}
	bgfx::destroyFrameBuffer(s_rtBlur);

	s_programs.destroy();

	bgfx::destroyUniform(u_texColor);
	bgfx::destroyUniform(u_shadowMap[3]);
	bgfx::destroyUniform(u_shadowMap[2]);
	bgfx::destroyUniform(u_shadowMap[1]);
	bgfx::destroyUniform(u_shadowMap[0]);

	s_uniforms.destroy();

	cameraDestroy();
	imguiDestroy();

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
