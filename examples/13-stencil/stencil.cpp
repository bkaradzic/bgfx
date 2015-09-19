/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <string>
#include <vector>

#include "common.h"
#include "bgfx_utils.h"

#include <bgfx/bgfx.h>
#include <bx/timer.h>
#include <bx/readerwriter.h>
#include <bx/fpumath.h>
#include "entry/entry.h"
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

static const PosNormalTexcoordVertex s_cubeVertices[] =
{
	{ -1.0f,  1.0f,  1.0f, packF4u( 0.0f,  1.0f,  0.0f), 1.0f, 1.0f },
	{  1.0f,  1.0f,  1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0.0f, 1.0f },
	{ -1.0f,  1.0f, -1.0f, packF4u( 0.0f,  1.0f,  0.0f), 1.0f, 0.0f },
	{  1.0f,  1.0f, -1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0.0f, 0.0f },
	{ -1.0f, -1.0f,  1.0f, packF4u( 0.0f, -1.0f,  0.0f), 1.0f, 1.0f },
	{  1.0f, -1.0f,  1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0.0f, 1.0f },
	{ -1.0f, -1.0f, -1.0f, packF4u( 0.0f, -1.0f,  0.0f), 1.0f, 0.0f },
	{  1.0f, -1.0f, -1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0.0f, 0.0f },
	{  1.0f, -1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0.0f, 0.0f },
	{  1.0f,  1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0.0f, 1.0f },
	{ -1.0f, -1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 1.0f, 0.0f },
	{ -1.0f,  1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 1.0f, 1.0f },
	{  1.0f, -1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0.0f, 0.0f },
	{  1.0f,  1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0.0f, 1.0f },
	{ -1.0f, -1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 1.0f, 0.0f },
	{ -1.0f,  1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 1.0f, 1.0f },
	{  1.0f,  1.0f, -1.0f, packF4u( 1.0f,  0.0f,  0.0f), 1.0f, 1.0f },
	{  1.0f,  1.0f,  1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0.0f, 1.0f },
	{  1.0f, -1.0f, -1.0f, packF4u( 1.0f,  0.0f,  0.0f), 1.0f, 0.0f },
	{  1.0f, -1.0f,  1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0.0f, 0.0f },
	{ -1.0f,  1.0f, -1.0f, packF4u(-1.0f,  0.0f,  0.0f), 1.0f, 1.0f },
	{ -1.0f,  1.0f,  1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0.0f, 1.0f },
	{ -1.0f, -1.0f, -1.0f, packF4u(-1.0f,  0.0f,  0.0f), 1.0f, 0.0f },
	{ -1.0f, -1.0f,  1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0.0f, 0.0f },
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
		m_params.m_lightningPass = 1.0f;
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
		float m_lightningPass;
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
	 * u_params.y - u_lightningPass
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
	void load(const void* _vertices, uint32_t _numVertices, const bgfx::VertexDecl _decl
		, const uint16_t* _indices, uint32_t _numIndices)
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
				abort();
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

			// Set uniforms
			s_uniforms.submitPerDrawUniforms();

			// Set model matrix for rendering.
			bgfx::setTransform(_mtx);
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(group.m_vbh);

			// Set texture
			if (bgfx::invalidHandle != _texture.idx)
			{
				bgfx::setTexture(0, s_texColor, _texture);
			}

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

int _main_(int /*_argc*/, char** /*_argv*/)
{
	ViewState viewState(1280, 720);
	ClearValues clearValues(0x30303000, 1.0f, 0);

	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();
	bgfx::reset(viewState.m_width, viewState.m_height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

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
	s_uniforms.submitConstUniforms();

	s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);

	bgfx::ProgramHandle programTextureLightning = loadProgram("vs_stencil_texture_lightning", "fs_stencil_texture_lightning");
	bgfx::ProgramHandle programColorLightning   = loadProgram("vs_stencil_color_lightning",   "fs_stencil_color_lightning"  );
	bgfx::ProgramHandle programColorTexture     = loadProgram("vs_stencil_color_texture",     "fs_stencil_color_texture"    );
	bgfx::ProgramHandle programColorBlack       = loadProgram("vs_stencil_color",             "fs_stencil_color_black"      );
	bgfx::ProgramHandle programTexture          = loadProgram("vs_stencil_texture",           "fs_stencil_texture"          );

	Mesh bunnyMesh;
	Mesh columnMesh;
	Mesh cubeMesh;
	Mesh hplaneMesh;
	Mesh vplaneMesh;
	bunnyMesh.load("meshes/bunny.bin");
	columnMesh.load("meshes/column.bin");
	cubeMesh.load(s_cubeVertices, BX_COUNTOF(s_cubeVertices), PosNormalTexcoordVertex::ms_decl, s_cubeIndices, BX_COUNTOF(s_cubeIndices) );
	hplaneMesh.load(s_hplaneVertices, BX_COUNTOF(s_hplaneVertices), PosNormalTexcoordVertex::ms_decl, s_planeIndices, BX_COUNTOF(s_planeIndices) );
	vplaneMesh.load(s_vplaneVertices, BX_COUNTOF(s_vplaneVertices), PosNormalTexcoordVertex::ms_decl, s_planeIndices, BX_COUNTOF(s_planeIndices) );

	bgfx::TextureHandle figureTex     = loadTexture("figure-rgba.dds");
	bgfx::TextureHandle flareTex      = loadTexture("flare.dds");
	bgfx::TextureHandle fieldstoneTex = loadTexture("fieldstone-rgba.dds");

	// Setup lights.
	const float rgbInnerR[][4] =
	{
		{ 1.0f, 0.7f, 0.2f, 0.0f }, //yellow
		{ 0.7f, 0.2f, 1.0f, 0.0f }, //purple
		{ 0.2f, 1.0f, 0.7f, 0.0f }, //cyan
		{ 1.0f, 0.4f, 0.2f, 0.0f }, //orange
		{ 0.7f, 0.7f, 0.7f, 0.0f }, //white
	};

	float lightRgbInnerR[MAX_NUM_LIGHTS][4];
	for (uint8_t ii = 0, jj = 0; ii < MAX_NUM_LIGHTS; ++ii, ++jj)
	{
		const uint8_t index = jj%BX_COUNTOF(rgbInnerR);
		lightRgbInnerR[ii][0] = rgbInnerR[index][0];
		lightRgbInnerR[ii][1] = rgbInnerR[index][1];
		lightRgbInnerR[ii][2] = rgbInnerR[index][2];
		lightRgbInnerR[ii][3] = rgbInnerR[index][3];
	}
	memcpy(s_uniforms.m_lightRgbInnerR, lightRgbInnerR, MAX_NUM_LIGHTS * 4*sizeof(float) );

	// Set view and projection matrices.
	const float aspect = float(viewState.m_width)/float(viewState.m_height);
	mtxProj(viewState.m_proj, 60.0f, aspect, 0.1f, 100.0f);

	float initialPos[3] = { 0.0f, 18.0f, -40.0f };
	cameraCreate();
	cameraSetPosition(initialPos);
	cameraSetVerticalAngle(-0.35f);
	cameraGetViewMtx(viewState.m_view);

	int64_t timeOffset = bx::getHPCounter();

	enum Scene
	{
		StencilReflectionScene = 0,
		ProjectionShadowsScene,
	};

	Scene scene = StencilReflectionScene;
	float settings_numLights       = 4.0f;
	float settings_reflectionValue = 0.8f;
	bool  settings_updateLights    = true;
	bool  settings_updateScene     = true;

	static const char* titles[3] =
	{
		"Stencil Reflection Scene",
		"Projection Shadows Scene",
	};

	entry::MouseState mouseState;
	while (!entry::processEvents(viewState.m_width, viewState.m_height, debug, reset, &mouseState) )
	{
		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
			, mouseState.m_mz
			, viewState.m_width
			, viewState.m_height
			);

		static int32_t scrollArea = 0;
		imguiBeginScrollArea("Settings", viewState.m_width - 256 - 10, 10, 256, 215, &scrollArea);

		if (imguiCheck(titles[StencilReflectionScene], StencilReflectionScene == scene) )
		{
			scene = StencilReflectionScene;
			settings_numLights = 4.0f;
		}

		if (imguiCheck(titles[ProjectionShadowsScene], ProjectionShadowsScene == scene) )
		{
			scene = ProjectionShadowsScene;
			settings_numLights = 1.0f;
		}

		imguiSeparatorLine();
		imguiSlider("Lights", settings_numLights, 1.0f, float(MAX_NUM_LIGHTS), 1.0f);
		if (scene == StencilReflectionScene)
		{
			imguiSlider("Reflection value", settings_reflectionValue, 0.0f, 1.0f, 0.01f);
		}

		if (imguiCheck("Update lights", settings_updateLights) )
		{
			settings_updateLights = !settings_updateLights;
		}

		if (imguiCheck("Update scene", settings_updateScene) )
		{
			settings_updateScene = !settings_updateScene;
		}

		imguiEndScrollArea();
		imguiEndFrame();

		// Update settings.
		uint8_t numLights = (uint8_t)settings_numLights;
		s_uniforms.m_params.m_ambientPass     = 1.0f;
		s_uniforms.m_params.m_lightningPass   = 1.0f;
		s_uniforms.m_params.m_lightCount      = settings_numLights;
		s_uniforms.m_params.m_lightIndex      = 0.0f;
		s_uniforms.m_color[3]                 = settings_reflectionValue;

		// Time.
		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;
		float time = (float)( (now - timeOffset)/double(bx::getHPFrequency() ) );
		const float deltaTime = float(frameTime/freq);
		s_uniforms.m_time = time;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/13-stencil");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Stencil reflections and shadows.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Update camera.
		cameraUpdate(deltaTime, mouseState);
		cameraGetViewMtx(viewState.m_view);

		static float lightTimeAccumulator = 0.0f;
		if (settings_updateLights)
		{
			lightTimeAccumulator += deltaTime;
		}

		static float sceneTimeAccumulator = 0.0f;
		if (settings_updateScene)
		{
			sceneTimeAccumulator += deltaTime;
		}

		float lightPosRadius[MAX_NUM_LIGHTS][4];
		const float radius = (scene == StencilReflectionScene) ? 15.0f : 25.0f;
		for (uint8_t ii = 0; ii < numLights; ++ii)
		{
			lightPosRadius[ii][0] = sinf( (lightTimeAccumulator*1.1f + ii*0.03f + ii*bx::piHalf*1.07f ) )*20.0f;
			lightPosRadius[ii][1] = 8.0f + (1.0f - cosf( (lightTimeAccumulator*1.5f + ii*0.29f + bx::piHalf*1.49f ) ) )*4.0f;
			lightPosRadius[ii][2] = cosf( (lightTimeAccumulator*1.3f + ii*0.13f + ii*bx::piHalf*1.79f ) )*20.0f;
			lightPosRadius[ii][3] = radius;
		}
		memcpy(s_uniforms.m_lightPosRadius, lightPosRadius, numLights * 4*sizeof(float) );

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
				, sinf(ii * 2.0f + 13.0f - sceneTimeAccumulator) * 13.0f
				, 4.0f
				, cosf(ii * 2.0f + 13.0f - sceneTimeAccumulator) * 13.0f
				);
		}

		// Make sure at the beginning everything gets cleared.
		clearView(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, clearValues);
		bgfx::touch(0);
		s_viewMask |= 1;

		// Bunny and columns color.
		s_uniforms.m_color[0] = 0.70f;
		s_uniforms.m_color[1] = 0.65f;
		s_uniforms.m_color[2] = 0.60f;

		switch (scene)
		{
		case StencilReflectionScene:
			{
				// First pass - Draw plane.

				// Setup params for this scene.
				s_uniforms.m_params.m_ambientPass = 1.0f;
				s_uniforms.m_params.m_lightningPass = 1.0f;

				// Floor.
				hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
					, floorMtx
					, programColorBlack
					, s_renderStates[RenderState::StencilReflection_CraftStencil]
					);

				// Second pass - Draw reflected objects.

				// Clear depth from previous pass.
				clearView(RENDER_VIEWID_RANGE1_PASS_1, BGFX_CLEAR_DEPTH, clearValues);

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
				memcpy(s_uniforms.m_lightPosRadius, reflectedLights, numLights * 4*sizeof(float) );

				// Reflect and submit bunny.
				float mtxReflectedBunny[16];
				bx::mtxMul(mtxReflectedBunny, bunnyMtx, reflectMtx);
				bunnyMesh.submit(RENDER_VIEWID_RANGE1_PASS_1
					, mtxReflectedBunny
					, programColorLightning
					, s_renderStates[RenderState::StencilReflection_DrawReflected]
					);

				// Reflect and submit columns.
				float mtxReflectedColumn[16];
				for (uint8_t ii = 0; ii < 4; ++ii)
				{
					bx::mtxMul(mtxReflectedColumn, columnMtx[ii], reflectMtx);
					columnMesh.submit(RENDER_VIEWID_RANGE1_PASS_1
						, mtxReflectedColumn
						, programColorLightning
						, s_renderStates[RenderState::StencilReflection_DrawReflected]
						);
				}

				// Set lights back.
				memcpy(s_uniforms.m_lightPosRadius, lightPosRadius, numLights * 4*sizeof(float) );
				// Third pass - Blend plane.

				// Floor.
				hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_2
					, floorMtx
					, programTextureLightning
					, s_renderStates[RenderState::StencilReflection_BlendPlane]
					, fieldstoneTex
					);

				// Fourth pass - Draw everything else but the plane.

				// Bunny.
				bunnyMesh.submit(RENDER_VIEWID_RANGE1_PASS_3
					, bunnyMtx
					, programColorLightning
					, s_renderStates[RenderState::StencilReflection_DrawScene]
					);

				// Columns.
				for (uint8_t ii = 0; ii < 4; ++ii)
				{
					columnMesh.submit(RENDER_VIEWID_RANGE1_PASS_3
						, columnMtx[ii]
						, programColorLightning
						, s_renderStates[RenderState::StencilReflection_DrawScene]
						);
				}

			}
			break;

		case ProjectionShadowsScene:
			{
				// First pass - Draw entire scene. (ambient only).
				s_uniforms.m_params.m_ambientPass = 1.0f;
				s_uniforms.m_params.m_lightningPass = 0.0f;

				// Bunny.
				bunnyMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
					, bunnyMtx
					, programColorLightning
					, s_renderStates[RenderState::ProjectionShadows_DrawAmbient]
				);

				// Floor.
				hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
					, floorMtx
					, programTextureLightning
					, s_renderStates[RenderState::ProjectionShadows_DrawAmbient]
					, fieldstoneTex
					);

				// Cubes.
				for (uint8_t ii = 0; ii < numCubes; ++ii)
				{
					cubeMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
						, cubeMtx[ii]
						, programTextureLightning
						, s_renderStates[RenderState::ProjectionShadows_DrawAmbient]
						, figureTex
						);
				}

				// Ground plane.
				float ground[4];
				float plane_pos[3] = { 0.0f, 0.0f, 0.0f };
				float normal[3] = { 0.0f, 1.0f, 0.0f };
				memcpy(ground, normal, sizeof(float) * 3);
				ground[3] = -bx::vec3Dot(plane_pos, normal) - 0.01f; // - 0.01 against z-fighting

				for (uint8_t ii = 0, viewId = RENDER_VIEWID_RANGE5_PASS_6; ii < numLights; ++ii, ++viewId)
				{
					// Clear stencil for this light source.
					clearView(viewId, BGFX_CLEAR_STENCIL, clearValues);

					// Draw shadow projection of scene objects.

					// Get homogeneous light pos.
					float* lightPos = lightPosRadius[ii];
					float pos[4];
					memcpy(pos, lightPos, sizeof(float) * 3);
					pos[3] = 1.0f;

					// Calculate shadow mtx for current light.
					float shadowMtx[16];
					mtxShadow(shadowMtx, ground, pos);

					// Submit bunny's shadow.
					float mtxShadowedBunny[16];
					bx::mtxMul(mtxShadowedBunny, bunnyMtx, shadowMtx);
					bunnyMesh.submit(viewId
						, mtxShadowedBunny
						, programColorBlack
						, s_renderStates[RenderState::ProjectionShadows_CraftStencil]
					);

					// Submit cube shadows.
					float mtxShadowedCube[16];
					for (uint8_t jj = 0; jj < numCubes; ++jj)
					{
						bx::mtxMul(mtxShadowedCube, cubeMtx[jj], shadowMtx);
						cubeMesh.submit(viewId
							, mtxShadowedCube
							, programColorBlack
							, s_renderStates[RenderState::ProjectionShadows_CraftStencil]
						);
					}

					// Draw entire scene. (lightning pass only. blending is on)
					s_uniforms.m_params.m_ambientPass = 0.0f;
					s_uniforms.m_params.m_lightningPass = 1.0f;
					s_uniforms.m_params.m_lightCount = 1.0f;
					s_uniforms.m_params.m_lightIndex = float(ii);

					// Bunny.
					bunnyMesh.submit(viewId
						, bunnyMtx
						, programColorLightning
						, s_renderStates[RenderState::ProjectionShadows_DrawDiffuse]
					);

					// Floor.
					hplaneMesh.submit(viewId
						, floorMtx
						, programTextureLightning
						, s_renderStates[RenderState::ProjectionShadows_DrawDiffuse]
						, fieldstoneTex
						);

					// Cubes.
					for (uint8_t jj = 0; jj < numCubes; ++jj)
					{
						cubeMesh.submit(viewId
							, cubeMtx[jj]
							, programTextureLightning
							, s_renderStates[RenderState::ProjectionShadows_DrawDiffuse]
							, figureTex
							);
					}
				}

				// Reset these to default..
				s_uniforms.m_params.m_ambientPass = 1.0f;
				s_uniforms.m_params.m_lightningPass = 1.0f;
			}
			break;
		};

		//lights
		const float lightScale[3] = { 1.5f, 1.5f, 1.5f };
		float lightMtx[16];
		for (uint8_t ii = 0; ii < numLights; ++ii)
		{
			s_uniforms.m_color[0] = lightRgbInnerR[ii][0];
			s_uniforms.m_color[1] = lightRgbInnerR[ii][1];
			s_uniforms.m_color[2] = lightRgbInnerR[ii][2];

			mtxBillboard(lightMtx, viewState.m_view, lightPosRadius[ii], lightScale);
			vplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_7
				, lightMtx
				, programColorTexture
				, s_renderStates[RenderState::Custom_BlendLightTexture]
				, flareTex
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

		hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_7
			, floorBottomMtx
			, programTexture
			, s_renderStates[RenderState::Custom_DrawPlaneBottom]
			, figureTex
			);

		// Setup view rect and transform for all used views.
		setViewRectMask(s_viewMask, 0, 0, viewState.m_width, viewState.m_height);
		setViewTransformMask(s_viewMask, viewState.m_view, viewState.m_proj);
		s_viewMask = 0;

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();

		//reset clear values on used views
		clearViewMask(s_clearMask, BGFX_CLEAR_NONE, clearValues);
		s_clearMask = 0;
	}

	// Cleanup.
	bunnyMesh.unload();
	columnMesh.unload();
	cubeMesh.unload();
	hplaneMesh.unload();
	vplaneMesh.unload();

	bgfx::destroyTexture(figureTex);
	bgfx::destroyTexture(fieldstoneTex);
	bgfx::destroyTexture(flareTex);

	bgfx::destroyProgram(programTextureLightning);
	bgfx::destroyProgram(programColorLightning);
	bgfx::destroyProgram(programColorTexture);
	bgfx::destroyProgram(programColorBlack);
	bgfx::destroyProgram(programTexture);

	bgfx::destroyUniform(s_texColor);

	s_uniforms.destroy();

	cameraDestroy();
	imguiDestroy();

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
