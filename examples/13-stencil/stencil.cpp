/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <string>
#include <vector>

#include "common.h"
#include "bgfx_utils.h"

#include <bx/crtimpl.h>
#include "camera.h"
#include "imgui/imgui.h"

#define RENDER_VIEWID_RANGE1_PASS_0   1
#define RENDER_VIEWID_RANGE1_PASS_1   2
#define RENDER_VIEWID_RANGE1_PASS_2   3
#define RENDER_VIEWID_RANGE1_PASS_3   4
#define RENDER_VIEWID_RANGE1_PASS_4   5
#define RENDER_VIEWID_RANGE1_PASS_5   6
#define RENDER_VIEWID_RANGE5_PASS_6   7
#define RENDER_VIEWID_RANGE1_PASS_7  13

#define MAX_NUM_LIGHTS 5

struct PosNormalTexcoordVertex
{
	float    m_x;
	float    m_y;
	float    m_z;
	uint32_t m_normal;
	float    m_u;
	float    m_v;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosNormalTexcoordVertex::ms_decl;

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

static const PosNormalTexcoordVertex s_cubeVertices[] =
{
	{ -1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 1.0f, 1.0f },
	{  1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 0.0f, 1.0f },
	{ -1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 1.0f, 0.0f },
	{  1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  1.0f,  0.0f), 0.0f, 0.0f },
	{ -1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 1.0f, 1.0f },
	{  1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 0.0f, 1.0f },
	{ -1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 1.0f, 0.0f },
	{  1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f, -1.0f,  0.0f), 0.0f, 0.0f },
	{  1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 0.0f, 0.0f },
	{  1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 0.0f, 1.0f },
	{ -1.0f, -1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 1.0f, 0.0f },
	{ -1.0f,  1.0f,  1.0f, encodeNormalRgba8( 0.0f,  0.0f,  1.0f), 1.0f, 1.0f },
	{  1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 0.0f, 0.0f },
	{  1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 0.0f, 1.0f },
	{ -1.0f, -1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 1.0f, 0.0f },
	{ -1.0f,  1.0f, -1.0f, encodeNormalRgba8( 0.0f,  0.0f, -1.0f), 1.0f, 1.0f },
	{  1.0f,  1.0f, -1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 1.0f, 1.0f },
	{  1.0f,  1.0f,  1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 0.0f, 1.0f },
	{  1.0f, -1.0f, -1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 1.0f, 0.0f },
	{  1.0f, -1.0f,  1.0f, encodeNormalRgba8( 1.0f,  0.0f,  0.0f), 0.0f, 0.0f },
	{ -1.0f,  1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 1.0f, 1.0f },
	{ -1.0f,  1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0.0f, 1.0f },
	{ -1.0f, -1.0f, -1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 1.0f, 0.0f },
	{ -1.0f, -1.0f,  1.0f, encodeNormalRgba8(-1.0f,  0.0f,  0.0f), 0.0f, 0.0f },
};

static const uint16_t s_cubeIndices[] =
{
	0,  1,  2,
	1,  3,  2,
	4,  6,  5,
	5,  6,  7,

	8,  9, 10,
	9, 11, 10,
	12, 14, 13,
	13, 14, 15,

	16, 17, 18,
	17, 19, 18,
	20, 22, 21,
	21, 22, 23,
};

static const uint16_t s_planeIndices[] =
{
	0, 1, 2,
	1, 3, 2,
};

static bool s_flipV = false;
static uint32_t s_viewMask = 0;
static uint32_t s_clearMask = 0;
static bgfx::UniformHandle s_texColor;

inline void mtxProj(float* _result, float _fovy, float _aspect, float _near, float _far)
{
	bx::mtxProj(_result, _fovy, _aspect, _near, _far, s_flipV);
}

void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
{
	for (uint32_t view = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, view += 1, ntz = bx::uint32_cnttz(viewMask) )
	{
		viewMask >>= ntz;
		view += ntz;

		bgfx::setViewClear( (uint8_t)view, _flags, _rgba, _depth, _stencil);
	}
}

void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj)
{
	for (uint32_t view = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, view += 1, ntz = bx::uint32_cnttz(viewMask) )
	{
		viewMask >>= ntz;
		view += ntz;

		bgfx::setViewTransform( (uint8_t)view, _view, _proj);
	}
}

void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	for (uint32_t view = 0, viewMask = _viewMask, ntz = bx::uint32_cnttz(_viewMask); 0 != viewMask; viewMask >>= 1, view += 1, ntz = bx::uint32_cnttz(viewMask) )
	{
		viewMask >>= ntz;
		view += ntz;

		bgfx::setViewRect( (uint8_t)view, _x, _y, _width, _height);
	}
}

void mtxReflected(float*__restrict _result
				  , const float* __restrict _p  /* plane */
				  , const float* __restrict _n  /* normal */
				  )
{
	float dot = bx::vec3Dot(_p, _n);

	_result[ 0] =  1.0f -  2.0f * _n[0] * _n[0]; //1-2Nx^2
	_result[ 1] = -2.0f * _n[0] * _n[1];         //-2*Nx*Ny
	_result[ 2] = -2.0f * _n[0] * _n[2];         //-2*NxNz
	_result[ 3] =  0.0f;                         //0

	_result[ 4] = -2.0f * _n[0] * _n[1];         //-2*NxNy
	_result[ 5] =  1.0f -  2.0f * _n[1] * _n[1]; //1-2*Ny^2
	_result[ 6] = -2.0f * _n[1] * _n[2];         //-2*NyNz
	_result[ 7] =  0.0f;                         //0

	_result[ 8] = -2.0f * _n[0] * _n[2];         //-2*NxNz
	_result[ 9] = -2.0f * _n[1] * _n[2];         //-2NyNz
	_result[10] =  1.0f -  2.0f * _n[2] * _n[2]; //1-2*Nz^2
	_result[11] =  0.0f;                         //0

	_result[12] =  2.0f * dot * _n[0];           //2*dot*Nx
	_result[13] =  2.0f * dot * _n[1];           //2*dot*Ny
	_result[14] =  2.0f * dot * _n[2];           //2*dot*Nz
	_result[15] =  1.0f;                         //1
}

void mtxShadow(float* __restrict _result
			   , const float* __restrict _ground
			   , const float* __restrict _light
			   )
{
	float dot = _ground[0] * _light[0]
		+ _ground[1] * _light[1]
		+ _ground[2] * _light[2]
		+ _ground[3] * _light[3]
		;

	_result[ 0] =  dot - _light[0] * _ground[0];
	_result[ 1] = 0.0f - _light[1] * _ground[0];
	_result[ 2] = 0.0f - _light[2] * _ground[0];
	_result[ 3] = 0.0f - _light[3] * _ground[0];

	_result[ 4] = 0.0f - _light[0] * _ground[1];
	_result[ 5] =  dot - _light[1] * _ground[1];
	_result[ 6] = 0.0f - _light[2] * _ground[1];
	_result[ 7] = 0.0f - _light[3] * _ground[1];

	_result[ 8] = 0.0f - _light[0] * _ground[2];
	_result[ 9] = 0.0f - _light[1] * _ground[2];
	_result[10] =  dot - _light[2] * _ground[2];
	_result[11] = 0.0f - _light[3] * _ground[2];

	_result[12] = 0.0f - _light[0] * _ground[3];
	_result[13] = 0.0f - _light[1] * _ground[3];
	_result[14] = 0.0f - _light[2] * _ground[3];
	_result[15] =  dot - _light[3] * _ground[3];
}

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

struct Uniforms
{
	void init()
	{
		m_params.m_ambientPass   = 1.0f;
		m_params.m_lightingPass  = 1.0f;
		m_params.m_lightCount    = 4.0f;
		m_params.m_lightIndex    = 4.0f;

		m_ambient[0] = 0.02f;
		m_ambient[1] = 0.02f;
		m_ambient[2] = 0.02f;
		m_ambient[3] = 0.0f; //unused

		m_diffuse[0] = 0.2f;
		m_diffuse[1] = 0.2f;
		m_diffuse[2] = 0.2f;
		m_diffuse[3] = 0.0f; //unused

		m_specular_shininess[0] = 1.0f;
		m_specular_shininess[1] = 1.0f;
		m_specular_shininess[2] = 1.0f;
		m_specular_shininess[3] = 10.0f; //shininess

		m_color[0] = 1.0f;
		m_color[1] = 1.0f;
		m_color[2] = 1.0f;
		m_color[3] = 1.0f;

		m_time = 0.0f;

		for (uint8_t ii = 0; ii < MAX_NUM_LIGHTS; ++ii)
		{
			m_lightPosRadius[ii][0] = 0.0f;
			m_lightPosRadius[ii][1] = 0.0f;
			m_lightPosRadius[ii][2] = 0.0f;
			m_lightPosRadius[ii][3] = 1.0f;

			m_lightRgbInnerR[ii][0] = 1.0f;
			m_lightRgbInnerR[ii][1] = 1.0f;
			m_lightRgbInnerR[ii][2] = 1.0f;
			m_lightRgbInnerR[ii][3] = 1.0f;
		}

		u_params             = bgfx::createUniform("u_params",              bgfx::UniformType::Vec4);
		u_ambient            = bgfx::createUniform("u_ambient",             bgfx::UniformType::Vec4);
		u_diffuse            = bgfx::createUniform("u_diffuse",             bgfx::UniformType::Vec4);
		u_specular_shininess = bgfx::createUniform("u_specular_shininess",  bgfx::UniformType::Vec4);
		u_color              = bgfx::createUniform("u_color",               bgfx::UniformType::Vec4);
		u_lightPosRadius     = bgfx::createUniform("u_lightPosRadius",      bgfx::UniformType::Vec4, MAX_NUM_LIGHTS);
		u_lightRgbInnerR     = bgfx::createUniform("u_lightRgbInnerR",      bgfx::UniformType::Vec4, MAX_NUM_LIGHTS);
	}

	//call this once at initialization
	void submitConstUniforms()
	{
		bgfx::setUniform(u_ambient,            &m_ambient);
		bgfx::setUniform(u_diffuse,            &m_diffuse);
		bgfx::setUniform(u_specular_shininess, &m_specular_shininess);
	}

	//call this before each draw call
	void submitPerDrawUniforms()
	{
		bgfx::setUniform(u_params,         &m_params);
		bgfx::setUniform(u_color,          &m_color);
		bgfx::setUniform(u_lightPosRadius, &m_lightPosRadius, MAX_NUM_LIGHTS);
		bgfx::setUniform(u_lightRgbInnerR, &m_lightRgbInnerR, MAX_NUM_LIGHTS);
	}

	void destroy()
	{
		bgfx::destroyUniform(u_params);
		bgfx::destroyUniform(u_ambient);
		bgfx::destroyUniform(u_diffuse);
		bgfx::destroyUniform(u_specular_shininess);
		bgfx::destroyUniform(u_color);
		bgfx::destroyUniform(u_lightPosRadius);
		bgfx::destroyUniform(u_lightRgbInnerR);
	}

	struct Params
	{
		float m_ambientPass;
		float m_lightingPass;
		float m_lightCount;
		float m_lightIndex;
	};

	struct SvParams
	{
		float m_useStencilTex;
		float m_dfail;
		float m_unused0;
		float m_unused1;
	};


	Params m_params;
	SvParams m_svparams;
	float m_ambient[4];
	float m_diffuse[4];
	float m_specular_shininess[4];
	float m_color[4];
	float m_time;
	float m_lightPosRadius[MAX_NUM_LIGHTS][4];
	float m_lightRgbInnerR[MAX_NUM_LIGHTS][4];

	/**
	 * u_params.x - u_ambientPass
	 * u_params.y - u_lightingPass
	 * u_params.z - u_lightCount
	 * u_params.w - u_lightIndex
	 */
	bgfx::UniformHandle u_params;
	bgfx::UniformHandle u_ambient;
	bgfx::UniformHandle u_diffuse;
	bgfx::UniformHandle u_specular_shininess;
	bgfx::UniformHandle u_color;
	bgfx::UniformHandle u_lightPosRadius;
	bgfx::UniformHandle u_lightRgbInnerR;
};
static Uniforms s_uniforms;

//-------------------------------------------------
// Render state
//-------------------------------------------------

struct RenderState
{
	enum Enum
	{
		StencilReflection_CraftStencil = 0,
		StencilReflection_DrawReflected,
		StencilReflection_BlendPlane,
		StencilReflection_DrawScene,

		ProjectionShadows_DrawAmbient,
		ProjectionShadows_CraftStencil,
		ProjectionShadows_DrawDiffuse,

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
	{ // StencilReflection_CraftStencil
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_TEST_ALWAYS         // pass always
		| BGFX_STENCIL_FUNC_REF(1)         // value = 1
		| BGFX_STENCIL_FUNC_RMASK(0xff)
		| BGFX_STENCIL_OP_FAIL_S_REPLACE
		| BGFX_STENCIL_OP_FAIL_Z_REPLACE
		| BGFX_STENCIL_OP_PASS_Z_REPLACE   // store the value
		, BGFX_STENCIL_NONE
	},
	{ // StencilReflection_DrawReflected
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_ALPHA_WRITE
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CW    //reflection matrix has inverted normals. using CCW instead of CW.
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_TEST_EQUAL
		| BGFX_STENCIL_FUNC_REF(1)
		| BGFX_STENCIL_FUNC_RMASK(1)
		| BGFX_STENCIL_OP_FAIL_S_KEEP
		| BGFX_STENCIL_OP_FAIL_Z_KEEP
		| BGFX_STENCIL_OP_PASS_Z_KEEP
		, BGFX_STENCIL_NONE
	},
	{ // StencilReflection_BlendPlane
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_SRC_COLOR)
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // StencilReflection_DrawScene
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // ProjectionShadows_DrawAmbient
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_DEPTH_WRITE // write depth !
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // ProjectionShadows_CraftStencil
		BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_TEST_ALWAYS         // pass always
		| BGFX_STENCIL_FUNC_REF(1)         // value = 1
		| BGFX_STENCIL_FUNC_RMASK(0xff)
		| BGFX_STENCIL_OP_FAIL_S_KEEP
		| BGFX_STENCIL_OP_FAIL_Z_KEEP
		| BGFX_STENCIL_OP_PASS_Z_REPLACE   // store the value
		, BGFX_STENCIL_NONE
	},
	{ // ProjectionShadows_DrawDiffuse
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
		| BGFX_STATE_DEPTH_TEST_EQUAL
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_TEST_NOTEQUAL
		| BGFX_STENCIL_FUNC_REF(1)
		| BGFX_STENCIL_FUNC_RMASK(1)
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
	ClearValues(uint32_t _clearRgba     = 0x30303000
		, float    _clearDepth    = 1.0f
		, uint8_t  _clearStencil  = 0
		)
		: m_clearRgba(_clearRgba)
		, m_clearDepth(_clearDepth)
		, m_clearStencil(_clearStencil)
	{ }

	uint32_t m_clearRgba;
	float    m_clearDepth;
	uint8_t  m_clearStencil;
};

void clearView(uint8_t _id, uint8_t _flags, const ClearValues& _clearValues)
{
	bgfx::setViewClear(_id
		, _flags
		, _clearValues.m_clearRgba
		, _clearValues.m_clearDepth
		, _clearValues.m_clearStencil
		);

	// Keep track of cleared views
	s_clearMask |= 1 << _id;
}

void clearViewMask(uint32_t _viewMask, uint8_t _flags, const ClearValues& _clearValues)
{
	setViewClearMask(_viewMask
		, _flags
		, _clearValues.m_clearRgba
		, _clearValues.m_clearDepth
		, _clearValues.m_clearStencil
		);

	// Keep track of cleared views
	s_clearMask |= _viewMask;
}

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

namespace bgfx
{
	int32_t read(bx::ReaderI* _reader, bgfx::VertexDecl& _decl, bx::Error* _err = NULL);
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
				abort();
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
			bgfx::destroyVertexBuffer(group.m_vbh);

			if (bgfx::isValid(group.m_ibh) )
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

			// Set uniforms
			s_uniforms.submitPerDrawUniforms();

			// Set model matrix for rendering.
			bgfx::setTransform(_mtx);
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(0, group.m_vbh);

			// Set texture
			bgfx::setTexture(0, s_texColor, _texture);

			// Apply render state
			bgfx::setStencil(_renderState.m_fstencil, _renderState.m_bstencil);
			bgfx::setState(_renderState.m_state, _renderState.m_blendFactorRgba);

			// Submit
			bgfx::submit(_viewId, _program);

			// Keep track of submited view ids
			s_viewMask |= 1 << _viewId;
		}
	}

	bgfx::VertexDecl m_decl;
	typedef std::vector<Group> GroupArray;
	GroupArray m_groups;
};


class ExampleStencil : public entry::AppI
{
public:
	virtual void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);
		
		m_viewState = ViewState(1280, 720);
		m_clearValues = ClearValues(0x30303000, 1.0f, 0);
		
		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;
		
		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_viewState.m_width, m_viewState.m_height, m_reset);
		
		// Enable debug text.
		bgfx::setDebug(m_debug);
		
		// Setup root path for binary shaders. Shader binaries are different
		// for each renderer.
		switch (bgfx::getRendererType() )
		{
			case bgfx::RendererType::OpenGL:
			case bgfx::RendererType::OpenGLES:
				s_flipV = true;
				break;
				
			default:
				break;
		}
		
		// Imgui.
		imguiCreate();
		
		PosNormalTexcoordVertex::init();
		
		s_uniforms.init();
		
		s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);
		
		m_programTextureLighting = loadProgram("vs_stencil_texture_lighting", "fs_stencil_texture_lighting");
		m_programColorLighting   = loadProgram("vs_stencil_color_lighting",   "fs_stencil_color_lighting"  );
		m_programColorTexture    = loadProgram("vs_stencil_color_texture",    "fs_stencil_color_texture"   );
		m_programColorBlack      = loadProgram("vs_stencil_color",            "fs_stencil_color_black"     );
		m_programTexture         = loadProgram("vs_stencil_texture",          "fs_stencil_texture"         );
		
		m_bunnyMesh.load("meshes/bunny.bin");
		m_columnMesh.load("meshes/column.bin");
		m_cubeMesh.load(s_cubeVertices, BX_COUNTOF(s_cubeVertices), PosNormalTexcoordVertex::ms_decl, s_cubeIndices, BX_COUNTOF(s_cubeIndices) );
		m_hplaneMesh.load(s_hplaneVertices, BX_COUNTOF(s_hplaneVertices), PosNormalTexcoordVertex::ms_decl, s_planeIndices, BX_COUNTOF(s_planeIndices) );
		m_vplaneMesh.load(s_vplaneVertices, BX_COUNTOF(s_vplaneVertices), PosNormalTexcoordVertex::ms_decl, s_planeIndices, BX_COUNTOF(s_planeIndices) );
		
		m_figureTex     = loadTexture("textures/figure-rgba.dds");
		m_flareTex      = loadTexture("textures/flare.dds");
		m_fieldstoneTex = loadTexture("textures/fieldstone-rgba.dds");
		
		// Setup lights.
		const float rgbInnerR[][4] =
		{
			{ 1.0f, 0.7f, 0.2f, 0.0f }, //yellow
			{ 0.7f, 0.2f, 1.0f, 0.0f }, //purple
			{ 0.2f, 1.0f, 0.7f, 0.0f }, //cyan
			{ 1.0f, 0.4f, 0.2f, 0.0f }, //orange
			{ 0.7f, 0.7f, 0.7f, 0.0f }, //white
		};
		
		for (uint8_t ii = 0, jj = 0; ii < MAX_NUM_LIGHTS; ++ii, ++jj)
		{
			const uint8_t index = jj%BX_COUNTOF(rgbInnerR);
			m_lightRgbInnerR[ii][0] = rgbInnerR[index][0];
			m_lightRgbInnerR[ii][1] = rgbInnerR[index][1];
			m_lightRgbInnerR[ii][2] = rgbInnerR[index][2];
			m_lightRgbInnerR[ii][3] = rgbInnerR[index][3];
		}
		bx::memCopy(s_uniforms.m_lightRgbInnerR, m_lightRgbInnerR, MAX_NUM_LIGHTS * 4*sizeof(float) );
		
		// Set view and projection matrices.
		const float aspect = float(m_viewState.m_width)/float(m_viewState.m_height);
		mtxProj(m_viewState.m_proj, 60.0f, aspect, 0.1f, 100.0f);
		
		float initialPos[3] = { 0.0f, 18.0f, -40.0f };
		cameraCreate();
		cameraSetPosition(initialPos);
		cameraSetVerticalAngle(-0.35f);
		cameraGetViewMtx(m_viewState.m_view);
		
		m_timeOffset = bx::getHPCounter();
		
		m_scene = StencilReflectionScene;
		m_settings_numLights       = 4.0f;
		m_settings_reflectionValue = 0.8f;
		m_settings_updateLights    = true;
		m_settings_updateScene     = true;
	}

	virtual int shutdown() BX_OVERRIDE
	{
		// Cleanup.
		m_bunnyMesh.unload();
		m_columnMesh.unload();
		m_cubeMesh.unload();
		m_hplaneMesh.unload();
		m_vplaneMesh.unload();
		
		bgfx::destroyTexture(m_figureTex);
		bgfx::destroyTexture(m_fieldstoneTex);
		bgfx::destroyTexture(m_flareTex);
		
		bgfx::destroyProgram(m_programTextureLighting);
		bgfx::destroyProgram(m_programColorLighting);
		bgfx::destroyProgram(m_programColorTexture);
		bgfx::destroyProgram(m_programColorBlack);
		bgfx::destroyProgram(m_programTexture);
		
		bgfx::destroyUniform(s_texColor);
		
		s_uniforms.destroy();
		
		cameraDestroy();
		imguiDestroy();
		
		// Shutdown bgfx.
		bgfx::shutdown();
		
		return 0;
	}

	virtual bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_viewState.m_width, m_viewState.m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx
							, m_mouseState.m_my
							, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
							| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
							| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
							, m_mouseState.m_mz
							, uint16_t(m_viewState.m_width)
							, uint16_t(m_viewState.m_height)
							);
			
			static const char* titles[3] =
			{
				"Stencil Reflection Scene",
				"Projection Shadows Scene",
			};
			
			static int32_t scrollArea = 0;
			imguiBeginScrollArea("Settings", m_viewState.m_width - 256 - 10, 10, 256, 215, &scrollArea);
			
			if (imguiCheck(titles[StencilReflectionScene], StencilReflectionScene == m_scene) )
			{
				m_scene = StencilReflectionScene;
				m_settings_numLights = 4.0f;
			}
			
			if (imguiCheck(titles[ProjectionShadowsScene], ProjectionShadowsScene == m_scene) )
			{
				m_scene = ProjectionShadowsScene;
				m_settings_numLights = 1.0f;
			}
			
			imguiSeparatorLine();
			imguiSlider("Lights", m_settings_numLights, 1.0f, float(MAX_NUM_LIGHTS), 1.0f);
			if (m_scene == StencilReflectionScene)
			{
				imguiSlider("Reflection value", m_settings_reflectionValue, 0.0f, 1.0f, 0.01f);
			}
			
			if (imguiCheck("Update lights", m_settings_updateLights) )
			{
				m_settings_updateLights = !m_settings_updateLights;
			}
			
			if (imguiCheck("Update scene", m_settings_updateScene) )
			{
				m_settings_updateScene = !m_settings_updateScene;
			}
			
			imguiEndScrollArea();
			imguiEndFrame();
			
			s_uniforms.submitConstUniforms();
			
			// Update settings.
			uint8_t numLights = (uint8_t)m_settings_numLights;
			s_uniforms.m_params.m_ambientPass     = 1.0f;
			s_uniforms.m_params.m_lightingPass    = 1.0f;
			s_uniforms.m_params.m_lightCount      = m_settings_numLights;
			s_uniforms.m_params.m_lightIndex      = 0.0f;
			s_uniforms.m_color[3]                 = m_settings_reflectionValue;
			
			// Time.
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0/freq;
			const float time = (float)( (now - m_timeOffset)/double(bx::getHPFrequency() ) );
			const float deltaTime = float(frameTime/freq);
			s_uniforms.m_time = time;
			
			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/13-stencil");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Stencil reflections and shadows.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);
			
			// Update camera.
			cameraUpdate(deltaTime, m_mouseState);
			cameraGetViewMtx(m_viewState.m_view);
			
			static float lightTimeAccumulator = 0.0f;
			if (m_settings_updateLights)
			{
				lightTimeAccumulator += deltaTime;
			}
			
			static float sceneTimeAccumulator = 0.0f;
			if (m_settings_updateScene)
			{
				sceneTimeAccumulator += deltaTime;
			}
			
			float lightPosRadius[MAX_NUM_LIGHTS][4];
			const float radius = (m_scene == StencilReflectionScene) ? 15.0f : 25.0f;
			for (uint8_t ii = 0; ii < numLights; ++ii)
			{
				lightPosRadius[ii][0] = bx::fsin( (lightTimeAccumulator*1.1f + ii*0.03f + ii*bx::kPiHalf*1.07f ) )*20.0f;
				lightPosRadius[ii][1] = 8.0f + (1.0f - bx::fcos( (lightTimeAccumulator*1.5f + ii*0.29f + bx::kPiHalf*1.49f ) ) )*4.0f;
				lightPosRadius[ii][2] = bx::fcos( (lightTimeAccumulator*1.3f + ii*0.13f + ii*bx::kPiHalf*1.79f ) )*20.0f;
				lightPosRadius[ii][3] = radius;
			}
			bx::memCopy(s_uniforms.m_lightPosRadius, lightPosRadius, numLights * 4*sizeof(float) );
			
			// Floor position.
			float floorMtx[16];
			bx::mtxSRT(floorMtx
					   , 20.0f  //scaleX
					   , 20.0f  //scaleY
					   , 20.0f  //scaleZ
					   , 0.0f   //rotX
					   , 0.0f   //rotY
					   , 0.0f   //rotZ
					   , 0.0f   //translateX
					   , 0.0f   //translateY
					   , 0.0f   //translateZ
					   );
			
			// Bunny position.
			float bunnyMtx[16];
			bx::mtxSRT(bunnyMtx
					   , 5.0f
					   , 5.0f
					   , 5.0f
					   , 0.0f
					   , 1.56f - sceneTimeAccumulator
					   , 0.0f
					   , 0.0f
					   , 2.0f
					   , 0.0f
					   );
			
			// Columns position.
			const float dist = 14.0f;
			const float columnPositions[4][3] =
			{
				{  dist, 0.0f,  dist },
				{ -dist, 0.0f,  dist },
				{  dist, 0.0f, -dist },
				{ -dist, 0.0f, -dist },
			};
			
			float columnMtx[4][16];
			for (uint8_t ii = 0; ii < 4; ++ii)
			{
				bx::mtxSRT(columnMtx[ii]
						   , 1.0f
						   , 1.0f
						   , 1.0f
						   , 0.0f
						   , 0.0f
						   , 0.0f
						   , columnPositions[ii][0]
						   , columnPositions[ii][1]
						   , columnPositions[ii][2]
						   );
			}
			
			const uint8_t numCubes = 9;
			float cubeMtx[numCubes][16];
			for (uint16_t ii = 0; ii < numCubes; ++ii)
			{
				bx::mtxSRT(cubeMtx[ii]
						   , 1.0f
						   , 1.0f
						   , 1.0f
						   , 0.0f
						   , 0.0f
						   , 0.0f
						   , bx::fsin(ii * 2.0f + 13.0f - sceneTimeAccumulator) * 13.0f
						   , 4.0f
						   , bx::fcos(ii * 2.0f + 13.0f - sceneTimeAccumulator) * 13.0f
						   );
			}
			
			// Make sure at the beginning everything gets cleared.
			clearView(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, m_clearValues);
			bgfx::touch(0);
			s_viewMask |= 1;
			
			// Bunny and columns color.
			s_uniforms.m_color[0] = 0.70f;
			s_uniforms.m_color[1] = 0.65f;
			s_uniforms.m_color[2] = 0.60f;
			
			switch (m_scene)
			{
				case StencilReflectionScene:
				{
					// First pass - Draw plane.
					
					// Setup params for this scene.
					s_uniforms.m_params.m_ambientPass = 1.0f;
					s_uniforms.m_params.m_lightingPass = 1.0f;
					
					// Floor.
					m_hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
										, floorMtx
										, m_programColorBlack
										, s_renderStates[RenderState::StencilReflection_CraftStencil]
										);
					
					// Second pass - Draw reflected objects.
					
					// Clear depth from previous pass.
					clearView(RENDER_VIEWID_RANGE1_PASS_1, BGFX_CLEAR_DEPTH, m_clearValues);
					
					// Compute reflected matrix.
					float reflectMtx[16];
					float plane_pos[3] = { 0.0f, 0.01f, 0.0f };
					float normal[3] = { 0.0f, 1.0f, 0.0f };
					mtxReflected(reflectMtx, plane_pos, normal);
					
					// Reflect lights.
					float reflectedLights[MAX_NUM_LIGHTS][4];
					for (uint8_t ii = 0; ii < numLights; ++ii)
					{
						bx::vec3MulMtx(reflectedLights[ii], lightPosRadius[ii], reflectMtx);
						reflectedLights[ii][3] = lightPosRadius[ii][3];
					}
					bx::memCopy(s_uniforms.m_lightPosRadius, reflectedLights, numLights * 4*sizeof(float) );
					
					// Reflect and submit bunny.
					float mtxReflectedBunny[16];
					bx::mtxMul(mtxReflectedBunny, bunnyMtx, reflectMtx);
					m_bunnyMesh.submit(RENDER_VIEWID_RANGE1_PASS_1
									   , mtxReflectedBunny
									   , m_programColorLighting
									   , s_renderStates[RenderState::StencilReflection_DrawReflected]
									   );
					
					// Reflect and submit columns.
					float mtxReflectedColumn[16];
					for (uint8_t ii = 0; ii < 4; ++ii)
					{
						bx::mtxMul(mtxReflectedColumn, columnMtx[ii], reflectMtx);
						m_columnMesh.submit(RENDER_VIEWID_RANGE1_PASS_1
											, mtxReflectedColumn
											, m_programColorLighting
											, s_renderStates[RenderState::StencilReflection_DrawReflected]
											);
					}
					
					// Set lights back.
					bx::memCopy(s_uniforms.m_lightPosRadius, lightPosRadius, numLights * 4*sizeof(float) );
					// Third pass - Blend plane.
					
					// Floor.
					m_hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_2
										, floorMtx
										, m_programTextureLighting
										, s_renderStates[RenderState::StencilReflection_BlendPlane]
										, m_fieldstoneTex
										);
					
					// Fourth pass - Draw everything else but the plane.
					
					// Bunny.
					m_bunnyMesh.submit(RENDER_VIEWID_RANGE1_PASS_3
									   , bunnyMtx
									   , m_programColorLighting
									   , s_renderStates[RenderState::StencilReflection_DrawScene]
									   );
					
					// Columns.
					for (uint8_t ii = 0; ii < 4; ++ii)
					{
						m_columnMesh.submit(RENDER_VIEWID_RANGE1_PASS_3
											, columnMtx[ii]
											, m_programColorLighting
											, s_renderStates[RenderState::StencilReflection_DrawScene]
											);
					}
					
				}
					break;
					
				case ProjectionShadowsScene:
				{
					// First pass - Draw entire scene. (ambient only).
					s_uniforms.m_params.m_ambientPass = 1.0f;
					s_uniforms.m_params.m_lightingPass = 0.0f;
					
					// Bunny.
					m_bunnyMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
									   , bunnyMtx
									   , m_programColorLighting
									   , s_renderStates[RenderState::ProjectionShadows_DrawAmbient]
									   );
					
					// Floor.
					m_hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
										, floorMtx
										, m_programTextureLighting
										, s_renderStates[RenderState::ProjectionShadows_DrawAmbient]
										, m_fieldstoneTex
										);
					
					// Cubes.
					for (uint8_t ii = 0; ii < numCubes; ++ii)
					{
						m_cubeMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
										  , cubeMtx[ii]
										  , m_programTextureLighting
										  , s_renderStates[RenderState::ProjectionShadows_DrawAmbient]
										  , m_figureTex
										  );
					}
					
					// Ground plane.
					float ground[4];
					float plane_pos[3] = { 0.0f, 0.0f, 0.0f };
					float normal[3] = { 0.0f, 1.0f, 0.0f };
					bx::memCopy(ground, normal, sizeof(float) * 3);
					ground[3] = -bx::vec3Dot(plane_pos, normal) - 0.01f; // - 0.01 against z-fighting
					
					for (uint8_t ii = 0, viewId = RENDER_VIEWID_RANGE5_PASS_6; ii < numLights; ++ii, ++viewId)
					{
						// Clear stencil for this light source.
						clearView(viewId, BGFX_CLEAR_STENCIL, m_clearValues);
						
						// Draw shadow projection of scene objects.
						
						// Get homogeneous light pos.
						float* lightPos = lightPosRadius[ii];
						float pos[4];
						bx::memCopy(pos, lightPos, sizeof(float) * 3);
						pos[3] = 1.0f;
						
						// Calculate shadow mtx for current light.
						float shadowMtx[16];
						mtxShadow(shadowMtx, ground, pos);
						
						// Submit bunny's shadow.
						float mtxShadowedBunny[16];
						bx::mtxMul(mtxShadowedBunny, bunnyMtx, shadowMtx);
						m_bunnyMesh.submit(viewId
										   , mtxShadowedBunny
										   , m_programColorBlack
										   , s_renderStates[RenderState::ProjectionShadows_CraftStencil]
										   );
						
						// Submit cube shadows.
						float mtxShadowedCube[16];
						for (uint8_t jj = 0; jj < numCubes; ++jj)
						{
							bx::mtxMul(mtxShadowedCube, cubeMtx[jj], shadowMtx);
							m_cubeMesh.submit(viewId
											  , mtxShadowedCube
											  , m_programColorBlack
											  , s_renderStates[RenderState::ProjectionShadows_CraftStencil]
											  );
						}
						
						// Draw entire scene. (lighting pass only. blending is on)
						s_uniforms.m_params.m_ambientPass = 0.0f;
						s_uniforms.m_params.m_lightingPass = 1.0f;
						s_uniforms.m_params.m_lightCount = 1.0f;
						s_uniforms.m_params.m_lightIndex = float(ii);
						
						// Bunny.
						m_bunnyMesh.submit(viewId
										   , bunnyMtx
										   , m_programColorLighting
										   , s_renderStates[RenderState::ProjectionShadows_DrawDiffuse]
										   );
						
						// Floor.
						m_hplaneMesh.submit(viewId
											, floorMtx
											, m_programTextureLighting
											, s_renderStates[RenderState::ProjectionShadows_DrawDiffuse]
											, m_fieldstoneTex
											);
						
						// Cubes.
						for (uint8_t jj = 0; jj < numCubes; ++jj)
						{
							m_cubeMesh.submit(viewId
											  , cubeMtx[jj]
											  , m_programTextureLighting
											  , s_renderStates[RenderState::ProjectionShadows_DrawDiffuse]
											  , m_figureTex
											  );
						}
					}
					
					// Reset these to default..
					s_uniforms.m_params.m_ambientPass = 1.0f;
					s_uniforms.m_params.m_lightingPass = 1.0f;
				}
					break;
			};
			
			//lights
			const float lightScale[3] = { 1.5f, 1.5f, 1.5f };
			float lightMtx[16];
			for (uint8_t ii = 0; ii < numLights; ++ii)
			{
				s_uniforms.m_color[0] = m_lightRgbInnerR[ii][0];
				s_uniforms.m_color[1] = m_lightRgbInnerR[ii][1];
				s_uniforms.m_color[2] = m_lightRgbInnerR[ii][2];
				
				mtxBillboard(lightMtx, m_viewState.m_view, lightPosRadius[ii], lightScale);
				m_vplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_7
									, lightMtx
									, m_programColorTexture
									, s_renderStates[RenderState::Custom_BlendLightTexture]
									, m_flareTex
									);
			}
			
			// Draw floor bottom.
			float floorBottomMtx[16];
			bx::mtxSRT(floorBottomMtx
					   , 20.0f  //scaleX
					   , 20.0f  //scaleY
					   , 20.0f  //scaleZ
					   , 0.0f   //rotX
					   , 0.0f   //rotY
					   , 0.0f   //rotZ
					   , 0.0f   //translateX
					   , -0.1f  //translateY
					   , 0.0f   //translateZ
					   );
			
			m_hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_7
								, floorBottomMtx
								, m_programTexture
								, s_renderStates[RenderState::Custom_DrawPlaneBottom]
								, m_figureTex
								);
			
			// Setup view rect and transform for all used views.
			setViewRectMask(s_viewMask, 0, 0, uint16_t(m_viewState.m_width), uint16_t(m_viewState.m_height) );
			setViewTransformMask(s_viewMask, m_viewState.m_view, m_viewState.m_proj);
			s_viewMask = 0;
			
			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();
			
			//reset clear values on used views
			clearViewMask(s_clearMask, BGFX_CLEAR_NONE, m_clearValues);
			s_clearMask = 0;
			
			return true;
		}
		
		return false;
	}

	ViewState m_viewState;
	entry::MouseState m_mouseState;
	ClearValues m_clearValues;
	
	uint32_t m_debug;
	uint32_t m_reset;
	
	bgfx::ProgramHandle m_programTextureLighting;
	bgfx::ProgramHandle m_programColorLighting;
	bgfx::ProgramHandle m_programColorTexture;
	bgfx::ProgramHandle m_programColorBlack;
	bgfx::ProgramHandle m_programTexture;
	
	Mesh m_bunnyMesh;
	Mesh m_columnMesh;
	Mesh m_cubeMesh;
	Mesh m_hplaneMesh;
	Mesh m_vplaneMesh;
	
	bgfx::TextureHandle m_figureTex;
	bgfx::TextureHandle m_flareTex;
	bgfx::TextureHandle m_fieldstoneTex;
	
	float m_lightRgbInnerR[MAX_NUM_LIGHTS][4];
	
	int64_t m_timeOffset;
	
	enum Scene
	{
		StencilReflectionScene = 0,
		ProjectionShadowsScene,
	};
	
	Scene m_scene;
	float m_settings_numLights;
	float m_settings_reflectionValue;
	bool  m_settings_updateLights;
	bool  m_settings_updateScene;
	
};

ENTRY_IMPLEMENT_MAIN(ExampleStencil);
