/*
 * Copyright 2013-2014 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include <string>
#include <vector>
#include <map>
#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>
namespace stl = tinystl;

#include "common.h"
#include "bgfx_utils.h"

#include <bgfx/bgfx.h>
#include <bx/timer.h>
#include <bx/allocator.h>
#include <bx/hash.h>
#include <bx/simd_t.h>
#include <bx/math.h>
#include <bx/file.h>
#include "entry/entry.h"
#include "camera.h"
#include "imgui/imgui.h"

namespace bgfx
{
	int32_t read(bx::ReaderI* _reader, bgfx::VertexLayout& _layout, bx::Error* _err = NULL);
}

namespace
{

#define SV_USE_SIMD 1
#define MAX_INSTANCE_COUNT 25
#define MAX_LIGHTS_COUNT 5

#define VIEWID_RANGE1_PASS0     1
#define VIEWID_RANGE1_RT_PASS1  2
#define VIEWID_RANGE15_PASS2    3
#define VIEWID_RANGE1_PASS3    20

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
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosNormalTexcoordVertex::ms_layout;

static const float s_texcoord = 50.0f;
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

static bool s_oglNdc = false;
static float s_texelHalf = 0.0f;

static uint32_t s_viewMask = 0;

static bgfx::UniformHandle s_texColor;
static bgfx::UniformHandle s_texStencil;
static bgfx::FrameBufferHandle s_stencilFb;

void setViewClearMask(uint32_t _viewMask, uint8_t _flags, uint32_t _rgba, float _depth, uint8_t _stencil)
{
	for (uint32_t view = 0, viewMask = _viewMask; 0 != viewMask; viewMask >>= 1, view += 1 )
	{
		const uint32_t ntz = bx::uint32_cnttz(viewMask);
		viewMask >>= ntz;
		view += ntz;

		bgfx::setViewClear( (uint8_t)view, _flags, _rgba, _depth, _stencil);
	}
}

void setViewTransformMask(uint32_t _viewMask, const void* _view, const void* _proj)
{
	for (uint32_t view = 0, viewMask = _viewMask; 0 != viewMask; viewMask >>= 1, view += 1 )
	{
        const uint32_t ntz = bx::uint32_cnttz(viewMask);
		viewMask >>= ntz;
		view += ntz;

		bgfx::setViewTransform( (uint8_t)view, _view, _proj);
	}
}

void setViewRectMask(uint32_t _viewMask, uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height)
{
	for (uint32_t view = 0, viewMask = _viewMask; 0 != viewMask; viewMask >>= 1, view += 1 )
	{
        const uint32_t ntz = bx::uint32_cnttz(viewMask);
		viewMask >>= ntz;
		view += ntz;

		bgfx::setViewRect( (uint8_t)view, _x, _y, _width, _height);
	}
}

void mtxBillboard(
	  float* _result
	, const float* _view
	, const float* _pos
	, const float* _scale
	)
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

void planeNormal(
	  float* _result
	, const float* _v0
	, const float* _v1
	, const float* _v2
	)
{
	const bx::Vec3 v0    = bx::load<bx::Vec3>(_v0);
	const bx::Vec3 v1    = bx::load<bx::Vec3>(_v1);
	const bx::Vec3 v2    = bx::load<bx::Vec3>(_v2);
	const bx::Vec3 vec0  = bx::sub(v1, v0);
	const bx::Vec3 vec1  = bx::sub(v2, v1);
	const bx::Vec3 cross = bx::cross(vec0, vec1);

	bx::store(_result, bx::normalize(cross) );

	_result[3] = -bx::dot(bx::load<bx::Vec3>(_result), bx::load<bx::Vec3>(_v0) );
}

struct Uniforms
{
	void init()
	{
		m_params.m_ambientPass   = 1.0f;
		m_params.m_lightingPass  = 1.0f;
		m_params.m_texelHalf     = 0.0f;

		m_ambient[0] = 0.05f;
		m_ambient[1] = 0.05f;
		m_ambient[2] = 0.05f;
		m_ambient[3] = 0.0f; //unused

		m_diffuse[0] = 0.8f;
		m_diffuse[1] = 0.8f;
		m_diffuse[2] = 0.8f;
		m_diffuse[3] = 0.0f; //unused

		m_specular_shininess[0] = 1.0f;
		m_specular_shininess[1] = 1.0f;
		m_specular_shininess[2] = 1.0f;
		m_specular_shininess[3] = 25.0f; //shininess

		m_fog[0] = 0.0f; //color
		m_fog[1] = 0.0f;
		m_fog[2] = 0.0f;
		m_fog[3] = 0.0055f; //density

		m_color[0] = 1.0f;
		m_color[1] = 1.0f;
		m_color[2] = 1.0f;
		m_color[3] = 1.0f;

		m_time = 0.0f;

		m_lightPosRadius[0] = 0.0f;
		m_lightPosRadius[1] = 0.0f;
		m_lightPosRadius[2] = 0.0f;
		m_lightPosRadius[3] = 1.0f;

		m_lightRgbInnerR[0] = 0.0f;
		m_lightRgbInnerR[1] = 0.0f;
		m_lightRgbInnerR[2] = 0.0f;
		m_lightRgbInnerR[3] = 1.0f;

		m_virtualLightPos_extrusionDist[0] = 0.0f;
		m_virtualLightPos_extrusionDist[1] = 0.0f;
		m_virtualLightPos_extrusionDist[2] = 0.0f;
		m_virtualLightPos_extrusionDist[3] = 100.0f;

		u_params                        = bgfx::createUniform("u_params",                        bgfx::UniformType::Vec4);
		u_svparams                      = bgfx::createUniform("u_svparams",                      bgfx::UniformType::Vec4);
		u_ambient                       = bgfx::createUniform("u_ambient",                       bgfx::UniformType::Vec4);
		u_diffuse                       = bgfx::createUniform("u_diffuse",                       bgfx::UniformType::Vec4);
		u_specular_shininess            = bgfx::createUniform("u_specular_shininess",            bgfx::UniformType::Vec4);
		u_fog                           = bgfx::createUniform("u_fog",                           bgfx::UniformType::Vec4);
		u_color                         = bgfx::createUniform("u_color",                         bgfx::UniformType::Vec4);
		u_lightPosRadius                = bgfx::createUniform("u_lightPosRadius",                bgfx::UniformType::Vec4);
		u_lightRgbInnerR                = bgfx::createUniform("u_lightRgbInnerR",                bgfx::UniformType::Vec4);
		u_virtualLightPos_extrusionDist = bgfx::createUniform("u_virtualLightPos_extrusionDist", bgfx::UniformType::Vec4);
	}

	//call this once at initialization
	void submitConstUniforms()
	{
		bgfx::setUniform(u_ambient,            &m_ambient);
		bgfx::setUniform(u_diffuse,            &m_diffuse);
		bgfx::setUniform(u_specular_shininess, &m_specular_shininess);
		bgfx::setUniform(u_fog,                &m_fog);
	}

	//call this before each draw call
	void submitPerDrawUniforms()
	{
		bgfx::setUniform(u_params,                        &m_params);
		bgfx::setUniform(u_svparams,                      &m_svparams);
		bgfx::setUniform(u_color,                         &m_color);
		bgfx::setUniform(u_lightPosRadius,                &m_lightPosRadius);
		bgfx::setUniform(u_lightRgbInnerR,                &m_lightRgbInnerR);
		bgfx::setUniform(u_virtualLightPos_extrusionDist, &m_virtualLightPos_extrusionDist);
	}

	void destroy()
	{
		bgfx::destroy(u_params);
		bgfx::destroy(u_svparams);
		bgfx::destroy(u_ambient);
		bgfx::destroy(u_diffuse);
		bgfx::destroy(u_specular_shininess);
		bgfx::destroy(u_fog);
		bgfx::destroy(u_color);
		bgfx::destroy(u_lightPosRadius);
		bgfx::destroy(u_lightRgbInnerR);
		bgfx::destroy(u_virtualLightPos_extrusionDist);
	}

	struct Params
	{
		float m_ambientPass;
		float m_lightingPass;
		float m_texelHalf;
		float m_unused00;
	};

	struct SvParams
	{
		float m_useStencilTex;
		float m_dfail;
		float m_unused10;
		float m_unused11;
	};

	Params m_params;
	SvParams m_svparams;
	float m_ambient[4];
	float m_diffuse[4];
	float m_specular_shininess[4];
	float m_fog[4];
	float m_color[4];
	float m_time;
	float m_lightPosRadius[4];
	float m_lightRgbInnerR[4];
	float m_virtualLightPos_extrusionDist[4];

	/**
	 * u_params.x - u_ambientPass
	 * u_params.y - u_lightingPass
	 * u_params.z - u_texelHalf
	 * u_params.w - unused

	 * u_svparams.x - u_useStencilTex
	 * u_svparams.y - u_dfail
	 * u_svparams.z - unused
	 * u_svparams.w - unused
	 */

	bgfx::UniformHandle u_params;
	bgfx::UniformHandle u_svparams;
	bgfx::UniformHandle u_ambient;
	bgfx::UniformHandle u_diffuse;
	bgfx::UniformHandle u_specular_shininess;
	bgfx::UniformHandle u_fog;
	bgfx::UniformHandle u_color;
	bgfx::UniformHandle u_lightPosRadius;
	bgfx::UniformHandle u_lightRgbInnerR;
	bgfx::UniformHandle u_virtualLightPos_extrusionDist;
};

static Uniforms s_uniforms;

struct RenderState
{
	enum Enum
	{
		ShadowVolume_UsingStencilTexture_DrawAmbient = 0,
		ShadowVolume_UsingStencilTexture_BuildDepth,
		ShadowVolume_UsingStencilTexture_CraftStencil_DepthPass,
		ShadowVolume_UsingStencilTexture_CraftStencil_DepthFail,
		ShadowVolume_UsingStencilTexture_DrawDiffuse,

		ShadowVolume_UsingStencilBuffer_DrawAmbient,
		ShadowVolume_UsingStencilBuffer_CraftStencil_DepthPass,
		ShadowVolume_UsingStencilBuffer_CraftStencil_DepthFail,
		ShadowVolume_UsingStencilBuffer_DrawDiffuse,

		Custom_Default,
		Custom_BlendLightTexture,
		Custom_DrawPlaneBottom,
		Custom_DrawShadowVolume_Lines,

		Count
	};

	uint64_t m_state;
	uint32_t m_blendFactorRgba;
	uint32_t m_fstencil;
	uint32_t m_bstencil;
};

static void setRenderState(const RenderState& _renderState)
{
	bgfx::setStencil(_renderState.m_fstencil, _renderState.m_bstencil);
	bgfx::setState(_renderState.m_state, _renderState.m_blendFactorRgba);
}

static RenderState s_renderStates[RenderState::Count]  =
{
	{ // ShadowVolume_UsingStencilTexture_DrawAmbient
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // ShadowVolume_UsingStencilTexture_BuildDepth
		BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // ShadowVolume_UsingStencilTexture_CraftStencil_DepthPass
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
		| BGFX_STATE_DEPTH_TEST_LEQUAL
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // ShadowVolume_UsingStencilTexture_CraftStencil_DepthFail
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
		| BGFX_STATE_DEPTH_TEST_GEQUAL
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
		},
	{ // ShadowVolume_UsingStencilTexture_DrawDiffuse
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_EQUAL
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // ShadowVolume_UsingStencilBuffer_DrawAmbient
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // ShadowVolume_UsingStencilBuffer_CraftStencil_DepthPass
		BGFX_STATE_DEPTH_TEST_LEQUAL
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_TEST_ALWAYS
		| BGFX_STENCIL_FUNC_REF(1)
		| BGFX_STENCIL_FUNC_RMASK(0xff)
		| BGFX_STENCIL_OP_FAIL_S_KEEP
		| BGFX_STENCIL_OP_FAIL_Z_KEEP
		| BGFX_STENCIL_OP_PASS_Z_DECR
		, BGFX_STENCIL_TEST_ALWAYS
		| BGFX_STENCIL_FUNC_REF(1)
		| BGFX_STENCIL_FUNC_RMASK(0xff)
		| BGFX_STENCIL_OP_FAIL_S_KEEP
		| BGFX_STENCIL_OP_FAIL_Z_KEEP
		| BGFX_STENCIL_OP_PASS_Z_INCR
	},
	{ // ShadowVolume_UsingStencilBuffer_CraftStencil_DepthFail
		BGFX_STATE_DEPTH_TEST_LEQUAL
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_TEST_ALWAYS
		| BGFX_STENCIL_FUNC_REF(1)
		| BGFX_STENCIL_FUNC_RMASK(0xff)
		| BGFX_STENCIL_OP_FAIL_S_KEEP
		| BGFX_STENCIL_OP_FAIL_Z_INCR
		| BGFX_STENCIL_OP_PASS_Z_KEEP
		, BGFX_STENCIL_TEST_ALWAYS
		| BGFX_STENCIL_FUNC_REF(1)
		| BGFX_STENCIL_FUNC_RMASK(0xff)
		| BGFX_STENCIL_OP_FAIL_S_KEEP
		| BGFX_STENCIL_OP_FAIL_Z_DECR
		| BGFX_STENCIL_OP_PASS_Z_KEEP
	},
	{ // ShadowVolume_UsingStencilBuffer_DrawDiffuse
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
		| BGFX_STATE_DEPTH_TEST_EQUAL
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
	{ // Custom_Default
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // Custom_BlendLightTexture
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_COLOR, BGFX_STATE_BLEND_INV_SRC_COLOR)
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // Custom_DrawPlaneBottom
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_CULL_CW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // Custom_DrawShadowVolume_Lines
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_FACTOR, BGFX_STATE_BLEND_SRC_ALPHA)
		| BGFX_STATE_PT_LINES
		| BGFX_STATE_MSAA
		, 0x0f0f0fff
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	}
};

struct ViewState
{
	ViewState(uint32_t _width = 0, uint32_t _height = 0)
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
	uint32_t m_clearRgba;
	float    m_clearDepth;
	uint8_t  m_clearStencil;
};

void submit(bgfx::ViewId _id, bgfx::ProgramHandle _handle, int32_t _depth = 0)
{
	bgfx::submit(_id, _handle, _depth);

	// Keep track of submited view ids.
	s_viewMask |= 1 << _id;
}

void touch(bgfx::ViewId _id)
{
	bgfx::ProgramHandle handle = BGFX_INVALID_HANDLE;
	::submit(_id, handle);
}

struct Face
{
	uint16_t m_i[3];
	float m_plane[4];
};
typedef std::vector<Face> FaceArray;

struct Edge
{
	bool m_faceReverseOrder[2];
	uint8_t m_faceIndex;
	uint16_t m_i0, m_i1;
};

struct Plane
{
	float m_plane[4];
};

struct HalfEdge
{
#define INVALID_EDGE_INDEX UINT16_MAX
	uint16_t m_secondIndex;
	bool m_marked;
};

struct HalfEdges
{
	HalfEdges()
		: m_data()
		, m_offsets()
		, m_endPtr()
	{
	}

	void init(uint16_t* _indices, uint32_t _numIndices)
	{
		m_data = (HalfEdge*)malloc(2 * _numIndices * sizeof(HalfEdge) );

		stl::unordered_map<uint16_t, std::vector<uint16_t> > edges;
		for (uint32_t ii = 0; ii < _numIndices; ii+=3)
		{
			uint16_t idx0 = _indices[ii];
			uint16_t idx1 = _indices[ii+1];
			uint16_t idx2 = _indices[ii+2];

			edges[idx0].push_back(idx1);
			edges[idx1].push_back(idx2);
			edges[idx2].push_back(idx0);
		}

		uint32_t numRows = (uint32_t)edges.size();
		m_offsets = (uint32_t*)malloc(numRows * sizeof(uint32_t) );

		HalfEdge* he = m_data;
		for (uint16_t ii = 0; ii < numRows; ++ii)
		{
			m_offsets[ii] = uint32_t(he - m_data);

			std::vector<uint16_t>& row = edges[ii];
			for (uint32_t jj = 0, size = (uint32_t)row.size(); jj < size; ++jj)
			{
				he->m_secondIndex = row[jj];
				he->m_marked = false;
				++he;
			}
			he->m_secondIndex = INVALID_EDGE_INDEX;
			++he;
		}
		he->m_secondIndex = 0;
		m_endPtr = he;
	}

	void destroy()
	{
		free(m_data);
		m_data = NULL;
		free(m_offsets);
		m_offsets = NULL;
	}

	void mark(uint16_t _firstIndex, uint16_t _secondIndex)
	{
		HalfEdge* ptr = &m_data[m_offsets[_firstIndex]];
		while (INVALID_EDGE_INDEX != ptr->m_secondIndex)
		{
			if (ptr->m_secondIndex == _secondIndex)
			{
				ptr->m_marked = true;
				break;
			}
			++ptr;
		}
	}

	bool unmark(uint16_t _firstIndex, uint16_t _secondIndex)
	{
		bool ret = false;
		HalfEdge* ptr = &m_data[m_offsets[_firstIndex]];
		while (INVALID_EDGE_INDEX != ptr->m_secondIndex)
		{
			if (ptr->m_secondIndex == _secondIndex && ptr->m_marked)
			{
				ptr->m_marked = false;
				ret = true;
				break;
			}
			++ptr;
		}
		return ret;
	}

	inline HalfEdge* begin() const
	{
		return m_data;
	}

	inline HalfEdge* end() const
	{
		return m_endPtr;
	}

	HalfEdge* m_data;
	uint32_t* m_offsets;
	HalfEdge* m_endPtr;
};

struct WeldedVertex
{
	uint16_t m_v;
	bool m_welded;
};

inline float sqLength(const float _a[3], const float _b[3])
{
	const float xx = _a[0] - _b[0];
	const float yy = _a[1] - _b[1];
	const float zz = _a[2] - _b[2];
	return xx*xx + yy*yy + zz*zz;
}

uint16_t weldVertices(WeldedVertex* _output, const bgfx::VertexLayout& _layout, const void* _data, uint16_t _num, float _epsilon)
{
	const uint32_t hashSize = bx::uint32_nextpow2(_num);
	const uint32_t hashMask = hashSize-1;
	const float epsilonSq = _epsilon*_epsilon;

	uint16_t numVertices = 0;

	const uint32_t size = sizeof(uint16_t)*(hashSize + _num);
	uint16_t* hashTable = (uint16_t*)alloca(size);
	bx::memSet(hashTable, 0xff, size);

	uint16_t* next = hashTable + hashSize;

	for (uint16_t ii = 0; ii < _num; ++ii)
	{
		float pos[4];
		vertexUnpack(pos, bgfx::Attrib::Position, _layout, _data, ii);
		uint32_t hashValue = bx::hash<bx::HashMurmur2A>(pos, 3*sizeof(float) ) & hashMask;

		uint16_t offset = hashTable[hashValue];
		for (; UINT16_MAX != offset; offset = next[offset])
		{
			float test[4];
			vertexUnpack(test, bgfx::Attrib::Position, _layout, _data, _output[offset].m_v);

			if (sqLength(test, pos) < epsilonSq)
			{
				_output[ii].m_v = _output[offset].m_v;
				_output[ii].m_welded = true;
				break;
			}
		}

		if (UINT16_MAX == offset)
		{
			_output[ii].m_v = ii;
			_output[ii].m_welded = false;
			next[ii] = hashTable[hashValue];
			hashTable[hashValue] = ii;
			numVertices++;
		}
	}

	return numVertices;
}

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
		m_numVertices = 0;
		m_vertices = NULL;
		m_numIndices = 0;
		m_indices = NULL;
		m_numEdges = 0;
		m_edges = NULL;
		m_edgePlanesUnalignedPtr = NULL;
		m_prims.clear();
	}

	typedef struct { float f[6]; } f6_t;

	struct EdgeAndPlane
	{
		EdgeAndPlane(uint16_t _i0, uint16_t _i1)
			: m_faceIndex(0)
			, m_i0(_i0)
			, m_i1(_i1)
		{
		}

		bool m_faceReverseOrder[2];
		uint8_t m_faceIndex;
		uint16_t m_i0, m_i1;
		Plane m_plane[2];
	};

	void fillStructures(const bgfx::VertexLayout& _layout)
	{
		uint16_t stride = _layout.getStride();
		m_faces.clear();
		m_halfEdges.destroy();

		//Init halfedges.
		m_halfEdges.init(m_indices, m_numIndices);

		//Init faces and edges.
		m_faces.reserve(m_numIndices/3); //1 face = 3 indices
		m_edges = (Edge*)malloc(m_numIndices * sizeof(Edge) ); //1 triangle = 3 indices = 3 edges.
		m_edgePlanesUnalignedPtr = (Plane*)malloc(m_numIndices * sizeof(Plane) + 15);
		m_edgePlanes = (Plane*)bx::alignPtr(m_edgePlanesUnalignedPtr, 0, 16);

		typedef std::map<std::pair<uint16_t, uint16_t>, EdgeAndPlane> EdgeMap;
		EdgeMap edgeMap;

		//Get unique indices.
		WeldedVertex* uniqueVertices = (WeldedVertex*)malloc(m_numVertices*sizeof(WeldedVertex) );
		::weldVertices(uniqueVertices, _layout, m_vertices, m_numVertices, 0.0001f);
		uint16_t* uniqueIndices = (uint16_t*)malloc(m_numIndices*sizeof(uint16_t) );
		for (uint32_t ii = 0; ii < m_numIndices; ++ii)
		{
			uint16_t index = m_indices[ii];
			if (uniqueVertices[index].m_welded)
			{
				uniqueIndices[ii] = uniqueVertices[index].m_v;
			}
			else
			{
				uniqueIndices[ii] = index;
			}
		}
		free(uniqueVertices);

		for (uint32_t ii = 0, size = m_numIndices/3; ii < size; ++ii)
		{
			const uint16_t* indices = &m_indices[ii*3];
			uint16_t i0 = indices[0];
			uint16_t i1 = indices[1];
			uint16_t i2 = indices[2];
			const float* v0 = (float*)&m_vertices[i0*stride];
			const float* v1 = (float*)&m_vertices[i1*stride];
			const float* v2 = (float*)&m_vertices[i2*stride];

			float plane[4];
			planeNormal(plane, v0, v2, v1);

			Face face;
			face.m_i[0] = i0;
			face.m_i[1] = i1;
			face.m_i[2] = i2;
			bx::memCopy(face.m_plane, plane, 4*sizeof(float) );
			m_faces.push_back(face);

			//Use unique indices for EdgeMap.
			const uint16_t* uindices = &uniqueIndices[ii*3];
			i0 = uindices[0];
			i1 = uindices[1];
			i2 = uindices[2];

			const uint16_t triangleEdge[3][2] =
			{
				{ i0, i1 },
				{ i1, i2 },
				{ i2, i0 },
			};

			for (uint8_t jj = 0; jj < 3; ++jj)
			{
				const uint16_t ui0 = triangleEdge[jj][0];
				const uint16_t ui1 = triangleEdge[jj][1];

				std::pair<uint16_t, uint16_t> key    = std::make_pair(ui0, ui1);
				std::pair<uint16_t, uint16_t> keyInv = std::make_pair(ui1, ui0);

				EdgeMap::iterator iter = edgeMap.find(keyInv);
				if (iter != edgeMap.end() )
				{
					EdgeAndPlane& ep = iter->second;
					bx::memCopy(ep.m_plane[ep.m_faceIndex].m_plane, plane, 4*sizeof(float) );
					ep.m_faceReverseOrder[ep.m_faceIndex] = true;
				}
				else
				{
					std::pair<EdgeMap::iterator, bool> result = edgeMap.insert(std::make_pair(key, EdgeAndPlane(ui0, ui1) ) );
					EdgeAndPlane& ep = result.first->second;
					bx::memCopy(ep.m_plane[ep.m_faceIndex].m_plane, plane, 4*sizeof(float) );
					ep.m_faceReverseOrder[ep.m_faceIndex] = false;
					ep.m_faceIndex++;
				}
			}
		}

		free(uniqueIndices);

		uint32_t index = 0;
		for (EdgeMap::const_iterator iter = edgeMap.begin(), end = edgeMap.end(); iter != end; ++iter)
		{
			Edge* edge = &m_edges[m_numEdges];
			Plane* plane = &m_edgePlanes[index];

			bx::memCopy(edge, iter->second.m_faceReverseOrder, sizeof(Edge) );
			bx::memCopy(plane, iter->second.m_plane, 2 * sizeof(Plane) );

			m_numEdges++;
			index += 2;
		}
	}

	void unload()
	{
		bgfx::destroy(m_vbh);
		if (bgfx::kInvalidHandle != m_ibh.idx)
		{
			bgfx::destroy(m_ibh);
		}
		free(m_vertices);
		m_vertices = NULL;
		free(m_indices);
		m_indices = NULL;
		free(m_edges);
		m_edges = NULL;
		free(m_edgePlanesUnalignedPtr);
		m_edgePlanesUnalignedPtr = NULL;
		m_halfEdges.destroy();
	}

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	uint16_t m_numVertices;
	uint8_t* m_vertices;
	uint32_t m_numIndices;
	uint16_t* m_indices;
	Sphere m_sphere;
	Aabb m_aabb;
	Obb m_obb;
	PrimitiveArray m_prims;
	uint32_t m_numEdges;
	Edge* m_edges;
	Plane* m_edgePlanesUnalignedPtr;
	Plane* m_edgePlanes;
	FaceArray m_faces;
	HalfEdges m_halfEdges;
};

typedef std::vector<Group> GroupArray;

struct Mesh
{
	void load(const void* _vertices, uint16_t _numVertices, const bgfx::VertexLayout _layout, const uint16_t* _indices, uint32_t _numIndices)
	{
		Group group;
		const bgfx::Memory* mem;
		uint32_t size;

		//vertices
		group.m_numVertices = _numVertices;
		size = _numVertices*_layout.getStride();

		group.m_vertices = (uint8_t*)malloc(size);
		bx::memCopy(group.m_vertices, _vertices, size);

		mem = bgfx::makeRef(group.m_vertices, size);
		group.m_vbh = bgfx::createVertexBuffer(mem, _layout);

		//indices
		group.m_numIndices = _numIndices;
		size = _numIndices*2;

		group.m_indices = (uint16_t*)malloc(size);
		bx::memCopy(group.m_indices, _indices, size);

		mem = bgfx::makeRef(group.m_indices, size);
		group.m_ibh = bgfx::createIndexBuffer(mem);

		m_groups.push_back(group);
	}

	void load(const char* _filePath)
	{
		::Mesh* mesh = ::meshLoad(_filePath, true);
		m_layout = mesh->m_layout;
		uint16_t stride = m_layout.getStride();

		for (::GroupArray::iterator it = mesh->m_groups.begin(), itEnd = mesh->m_groups.end(); it != itEnd; ++it)
		{
			Group group;
			group.m_numVertices = it->m_numVertices;
			const uint32_t vertexSize = group.m_numVertices*stride;
			group.m_vertices = (uint8_t*)malloc(vertexSize);
			bx::memCopy(group.m_vertices, it->m_vertices, vertexSize);

			const bgfx::Memory* mem = bgfx::makeRef(group.m_vertices, vertexSize);
			group.m_vbh = bgfx::createVertexBuffer(mem, m_layout);

			group.m_numIndices = it->m_numIndices;
			const uint32_t indexSize = 2 * group.m_numIndices;
			group.m_indices = (uint16_t*)malloc(indexSize);
			bx::memCopy(group.m_indices, it->m_indices, indexSize);

			mem = bgfx::makeRef(group.m_indices, indexSize);
			group.m_ibh = bgfx::createIndexBuffer(mem);

			group.m_sphere = it->m_sphere;
			group.m_aabb = it->m_aabb;
			group.m_obb = it->m_obb;
			group.m_prims = it->m_prims;

			m_groups.push_back(group);
		}
		::meshUnload(mesh);

		for (GroupArray::iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			it->fillStructures(m_layout);
		}
	}

	void unload()
	{
		for (GroupArray::iterator it = m_groups.begin(), itEnd = m_groups.end(); it != itEnd; ++it)
		{
			it->unload();
		}
		m_groups.clear();
	}

	bgfx::VertexLayout m_layout;
	GroupArray m_groups;
};

struct Model
{
	Model()
	{
		m_program.idx = bgfx::kInvalidHandle;
		m_texture.idx = bgfx::kInvalidHandle;
	}

	void load(const void* _vertices, uint16_t _numVertices, const bgfx::VertexLayout _layout, const uint16_t* _indices, uint32_t _numIndices)
	{
		m_mesh.load(_vertices, _numVertices, _layout, _indices, _numIndices);
	}

	void load(const char* _meshFilePath)
	{
		m_mesh.load(_meshFilePath);
	}

	void unload()
	{
		m_mesh.unload();
	}

	void submit(uint8_t _viewId, float* _mtx, const RenderState& _renderState)
	{
		for (GroupArray::const_iterator it = m_mesh.m_groups.begin(), itEnd = m_mesh.m_groups.end(); it != itEnd; ++it)
		{
			const Group& group = *it;

			// Set uniforms
			s_uniforms.submitPerDrawUniforms();

			// Set transform
			bgfx::setTransform(_mtx);

			// Set buffers
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(0, group.m_vbh);

			// Set textures
			if (bgfx::kInvalidHandle != m_texture.idx)
			{
				bgfx::setTexture(0, s_texColor, m_texture);
			}
			bgfx::setTexture(1, s_texStencil, bgfx::getTexture(s_stencilFb) );

			// Apply render state
			::setRenderState(_renderState);

			// Submit
			BX_ASSERT(bgfx::kInvalidHandle != m_program, "Error, program is not set.");
			::submit(_viewId, m_program);
		}
	}

	Mesh m_mesh;
	bgfx::ProgramHandle m_program;
	bgfx::TextureHandle m_texture;
};

struct Instance
{
	Instance()
		: m_svExtrusionDistance(150.0f)
	{
		m_color[0] = 1.0f;
		m_color[1] = 1.0f;
		m_color[2] = 1.0f;
	}

	void submit(uint8_t _viewId, const RenderState& _renderState)
	{
		bx::memCopy(s_uniforms.m_color, m_color, 3*sizeof(float) );

		float mtx[16];
		bx::mtxSRT(mtx
			, m_scale[0]
			, m_scale[1]
			, m_scale[2]
			, m_rotation[0]
			, m_rotation[1]
			, m_rotation[2]
			, m_pos[0]
			, m_pos[1]
			, m_pos[2]
			);

		BX_ASSERT(NULL != m_model, "Instance model cannot be NULL!");
		m_model->submit(_viewId, mtx, _renderState);
	}

	float m_scale[3];
	float m_rotation[3];
	float m_pos[3];

	float m_color[3];
	float m_svExtrusionDistance;

	Model* m_model;
};

#define SV_INSTANCE_MEM_SIZE (1500 << 10)
#define SV_INSTANCE_COUNT ( (25 > MAX_INSTANCE_COUNT) ? 25 : MAX_INSTANCE_COUNT)
#define SV_PAGE_SIZE (SV_INSTANCE_MEM_SIZE * SV_INSTANCE_COUNT * MAX_LIGHTS_COUNT)

struct ShadowVolumeAllocator
{
	ShadowVolumeAllocator()
	{
		m_mem = (uint8_t*)malloc(SV_PAGE_SIZE*2);
		m_ptr = m_mem;
		m_firstPage = true;
	}

	~ShadowVolumeAllocator()
	{
		free(m_mem);
	}

	void* alloc(uint32_t _size)
	{
		void* ret = (void*)m_ptr;
		m_ptr += _size;
		BX_ASSERT(m_ptr - m_mem < (m_firstPage ? SV_PAGE_SIZE : 2 * SV_PAGE_SIZE), "Buffer overflow!");
		return ret;
	}

	void swap()
	{
		m_ptr = m_firstPage ? m_mem + SV_PAGE_SIZE : m_mem;
		m_firstPage = !m_firstPage;
	}

	uint8_t* m_mem;
	uint8_t* m_ptr;
	bool m_firstPage;
};
static ShadowVolumeAllocator s_svAllocator;

struct ShadowVolumeImpl
{
	enum Enum
	{
		DepthPass,
		DepthFail,
	};
};

struct ShadowVolumeAlgorithm
{
	enum Enum
	{
		FaceBased,
		EdgeBased,
	};
};

struct ShadowVolume
{
	bgfx::VertexBufferHandle m_vbSides;
	bgfx::IndexBufferHandle m_ibSides;
	bgfx::IndexBufferHandle m_ibFrontCap;
	bgfx::IndexBufferHandle m_ibBackCap;

	uint32_t m_numVertices;
	uint32_t m_numIndices;

	const float* m_mtx;
	const float* m_lightPos;

	bool m_cap;
};

void shadowVolumeLightTransform(
	  float* _outLightPos
	, const float* _scale
	, const float* _rotate
	, const float* _translate
	, const float* _lightPos // world pos
	)
{
	/**
	 * Instead of transforming all the vertices, transform light instead:
	 * mtx = pivotTranslate -> rotateZYX -> invScale
	 * light = mtx * origin
	 */

	float pivot[16];
	bx::mtxTranslate(pivot
		, _lightPos[0] - _translate[0]
		, _lightPos[1] - _translate[1]
		, _lightPos[2] - _translate[2]
		);

	float mzyx[16];
	bx::mtxRotateZYX(mzyx
		, -_rotate[0]
		, -_rotate[1]
		, -_rotate[2]
		);

	float invScale[16];
	bx::mtxScale(invScale
		, 1.0f / _scale[0]
		, 1.0f / _scale[1]
		, 1.0f / _scale[2]
		);

	float tmp0[16];
	bx::mtxMul(tmp0, pivot, mzyx);

	float mtx[16];
	bx::mtxMul(mtx, tmp0, invScale);

	bx::store(_outLightPos, bx::mul({ 0.0f, 0.0f, 0.0f }, mtx) );
}

void shadowVolumeCreate(
	  ShadowVolume& _shadowVolume
	, Group& _group
	, uint16_t _stride
	, const float* _mtx
	, const float* _light // in model space
	, ShadowVolumeImpl::Enum _impl = ShadowVolumeImpl::DepthPass
	, ShadowVolumeAlgorithm::Enum _algo = ShadowVolumeAlgorithm::FaceBased
	, bool _textureAsStencil = false
	)
{
	const uint8_t*    vertices   = _group.m_vertices;
	const FaceArray&  faces      = _group.m_faces;
	const Edge*       edges      = _group.m_edges;
	const Plane*      edgePlanes = _group.m_edgePlanes;
	const uint32_t    numEdges   = _group.m_numEdges;
	HalfEdges&        halfEdges  = _group.m_halfEdges;

	struct VertexData
	{
		VertexData()
		{
		}

		VertexData(const float* _v3, float _extrude = 0.0f, float _k = 1.0f)
		{
			bx::memCopy(m_v, _v3, 3*sizeof(float) );
			m_extrude = _extrude;
			m_k = _k;
		}

		float m_v[3];
		float m_extrude;
		float m_k;
	};

	bool cap = (ShadowVolumeImpl::DepthFail == _impl);

	VertexData* verticesSide    = (VertexData*) s_svAllocator.alloc(20000 * sizeof(VertexData) );
	uint16_t*   indicesSide     = (uint16_t*)   s_svAllocator.alloc(20000 * 3*sizeof(uint16_t) );
	uint16_t*   indicesFrontCap = 0;
	uint16_t*   indicesBackCap  = 0;

	if (cap)
	{
		indicesFrontCap = (uint16_t*)s_svAllocator.alloc(80000 * 3*sizeof(uint16_t) );
		indicesBackCap  = (uint16_t*)s_svAllocator.alloc(80000 * 3*sizeof(uint16_t) );
	}

	uint32_t vsideI    = 0;
	uint32_t sideI     = 0;
	uint32_t frontCapI = 0;
	uint32_t backCapI  = 0;

	uint16_t indexSide = 0;

	if (ShadowVolumeAlgorithm::FaceBased == _algo)
	{
		for (FaceArray::const_iterator iter = faces.begin(), end = faces.end(); iter != end; ++iter)
		{
			const Face& face = *iter;

			bool frontFacing = false;
			const float f = bx::dot(bx::load<bx::Vec3>(face.m_plane), bx::load<bx::Vec3>(_light) ) + face.m_plane[3];
			if (f > 0.0f)
			{
				frontFacing = true;
				uint16_t triangleEdges[3][2] =
				{
					{ face.m_i[0], face.m_i[1] },
					{ face.m_i[1], face.m_i[2] },
					{ face.m_i[2], face.m_i[0] },
				};

				for (uint8_t ii = 0; ii < 3; ++ii)
				{
					uint16_t first  = triangleEdges[ii][0];
					uint16_t second = triangleEdges[ii][1];

					if (!halfEdges.unmark(second, first) )
					{
						halfEdges.mark(first, second);
					}
				}
			}

			if (cap)
			{
				if (frontFacing)
				{
					indicesFrontCap[frontCapI++] = face.m_i[0];
					indicesFrontCap[frontCapI++] = face.m_i[1];
					indicesFrontCap[frontCapI++] = face.m_i[2];
				}
				else
				{
					indicesBackCap[backCapI++] = face.m_i[0];
					indicesBackCap[backCapI++] = face.m_i[1];
					indicesBackCap[backCapI++] = face.m_i[2];
				}

				/**
				 * if '_useFrontFacingFacesAsBackCap' is needed, implement it as such:
				 *
				 * bool condition0 = frontFacing && _useFrontFacingFacesAsBackCap;
				 * bool condition1 = !frontFacing && !_useFrontFacingFacesAsBackCap;
				 * if (condition0 || condition1)
				 * {
				 *      indicesBackCap[backCapI++] = face.m_i[0];
				 *      indicesBackCap[backCapI++] = face.m_i[1+condition0];
				 *      indicesBackCap[backCapI++] = face.m_i[2-condition0];
				 * }
				 */
			}
		}

		// Fill side arrays.
		uint16_t firstIndex = 0;
		HalfEdge* he = halfEdges.begin();
		while (halfEdges.end() != he)
		{
			if (he->m_marked)
			{
				he->m_marked = false;

				const float* v0 = (float*)&vertices[firstIndex*_stride];
				const float* v1 = (float*)&vertices[he->m_secondIndex*_stride];

				verticesSide[vsideI++] = VertexData(v0, 0.0f);
				verticesSide[vsideI++] = VertexData(v0, 1.0f);
				verticesSide[vsideI++] = VertexData(v1, 0.0f);
				verticesSide[vsideI++] = VertexData(v1, 1.0f);

				indicesSide[sideI++] = indexSide+0;
				indicesSide[sideI++] = indexSide+1;
				indicesSide[sideI++] = indexSide+2;

				indicesSide[sideI++] = indexSide+2;
				indicesSide[sideI++] = indexSide+1;
				indicesSide[sideI++] = indexSide+3;

				indexSide += 4;
			}

			++he;
			if (INVALID_EDGE_INDEX == he->m_secondIndex)
			{
				++he;
				++firstIndex;
			}
		}
	}
	else // ShadowVolumeAlgorithm::EdgeBased:
	{
		{
			uint32_t ii = 0;

#if SV_USE_SIMD
			uint32_t numEdgesRounded = numEdges & (~0x1);

			using namespace bx;

			const simd128_t lx = simd_splat(_light[0]);
			const simd128_t ly = simd_splat(_light[1]);
			const simd128_t lz = simd_splat(_light[2]);

			for (; ii < numEdgesRounded; ii+=2)
			{
				const Edge& edge0 = edges[ii];
				const Edge& edge1 = edges[ii+1];
				const Plane* edgePlane0 = &edgePlanes[ii*2];
				const Plane* edgePlane1 = &edgePlanes[ii*2 + 2];

				const simd128_t reverse =
					simd_ild(edge0.m_faceReverseOrder[0]
							, edge1.m_faceReverseOrder[0]
							, edge0.m_faceReverseOrder[1]
							, edge1.m_faceReverseOrder[1]
							);

				const simd128_t p00 = simd_ld(edgePlane0[0].m_plane);
				const simd128_t p10 = simd_ld(edgePlane1[0].m_plane);
				const simd128_t p01 = simd_ld(edgePlane0[1].m_plane);
				const simd128_t p11 = simd_ld(edgePlane1[1].m_plane);

				const simd128_t xxyy0 = simd_shuf_xAyB(p00, p01);
				const simd128_t zzww0 = simd_shuf_zCwD(p00, p01);
				const simd128_t xxyy1 = simd_shuf_xAyB(p10, p11);
				const simd128_t zzww1 = simd_shuf_zCwD(p10, p11);

				const simd128_t vX = simd_shuf_xAyB(xxyy0, xxyy1);
				const simd128_t vY = simd_shuf_zCwD(xxyy0, xxyy1);
				const simd128_t vZ = simd_shuf_xAyB(zzww0, zzww1);
				const simd128_t vW = simd_shuf_zCwD(zzww0, zzww1);

				const simd128_t r0 = simd_mul(vX, lx);
				const simd128_t r1 = simd_mul(vY, ly);
				const simd128_t r2 = simd_mul(vZ, lz);

				const simd128_t dot = simd_add(r0, simd_add(r1, r2) );
				const simd128_t f = simd_add(dot, vW);

				const simd128_t zero = simd_zero();
				const simd128_t mask = simd_cmpgt(f, zero);
				const simd128_t onef = simd_splat(1.0f);
				const simd128_t tmp0 = simd_and(mask, onef);
				const simd128_t tmp1 = simd_ftoi(tmp0);
				const simd128_t tmp2 = simd_xor(tmp1, reverse);
				const simd128_t tmp3 = simd_sll(tmp2, 1);
				const simd128_t onei = simd_isplat(1);
				const simd128_t tmp4 = simd_isub(tmp3, onei);

				BX_ALIGN_DECL_16(int32_t res[4]);
				simd_st(&res, tmp4);

				for (uint16_t jj = 0; jj < 2; ++jj)
				{
					int32_t kk = res[jj] + res[jj+2];
					if (kk != 0)
					{
						float* v0 = (float*)&vertices[edges[ii+jj].m_i0*_stride];
						float* v1 = (float*)&vertices[edges[ii+jj].m_i1*_stride];
						verticesSide[vsideI++] = VertexData(v0, 0.0f, float(kk) );
						verticesSide[vsideI++] = VertexData(v0, 1.0f, float(kk) );
						verticesSide[vsideI++] = VertexData(v1, 0.0f, float(kk) );
						verticesSide[vsideI++] = VertexData(v1, 1.0f, float(kk) );

						kk = _textureAsStencil ? 1 : kk;
						uint16_t winding = uint16_t(kk > 0);
						for (int32_t ll = 0, end = abs(kk); ll < end; ++ll)
						{
							indicesSide[sideI++] = indexSide;
							indicesSide[sideI++] = indexSide + 2 - winding;
							indicesSide[sideI++] = indexSide + 1 + winding;

							indicesSide[sideI++] = indexSide + 2;
							indicesSide[sideI++] = indexSide + 3 - winding*2;
							indicesSide[sideI++] = indexSide + 1 + winding*2;
						}

						indexSide += 4;
					}
				}
			}
#endif

			for (; ii < numEdges; ++ii)
			{
				const Edge& edge = edges[ii];
				const Plane* edgePlane = &edgePlanes[ii*2];

				int16_t s0 = ( (bx::dot(bx::load<bx::Vec3>(edgePlane[0].m_plane), bx::load<bx::Vec3>(_light) ) + edgePlane[0].m_plane[3]) > 0.0f) ^ edge.m_faceReverseOrder[0];
				int16_t s1 = ( (bx::dot(bx::load<bx::Vec3>(edgePlane[1].m_plane), bx::load<bx::Vec3>(_light) ) + edgePlane[1].m_plane[3]) > 0.0f) ^ edge.m_faceReverseOrder[1];
				int16_t kk = ( (s0 + s1) << 1) - 2;

				if (kk != 0)
				{
					float* v0 = (float*)&vertices[edge.m_i0*_stride];
					float* v1 = (float*)&vertices[edge.m_i1*_stride];
					verticesSide[vsideI++] = VertexData(v0, 0.0f, kk);
					verticesSide[vsideI++] = VertexData(v0, 1.0f, kk);
					verticesSide[vsideI++] = VertexData(v1, 0.0f, kk);
					verticesSide[vsideI++] = VertexData(v1, 1.0f, kk);

					kk = _textureAsStencil ? 1 : kk;
					uint16_t winding = uint16_t(kk > 0);
					for (int32_t jj = 0, end = abs(kk); jj < end; ++jj)
					{
						indicesSide[sideI++] = indexSide;
						indicesSide[sideI++] = indexSide + 2 - winding;
						indicesSide[sideI++] = indexSide + 1 + winding;

						indicesSide[sideI++] = indexSide + 2;
						indicesSide[sideI++] = indexSide + 3 - winding*2;
						indicesSide[sideI++] = indexSide + 1 + winding*2;
					}

					indexSide += 4;
				}
			}
		}

		if (cap)
		{
			// This could/should be done on GPU!
			for (FaceArray::const_iterator iter = faces.begin(), end = faces.end(); iter != end; ++iter)
			{
				const Face& face = *iter;

				const float f = bx::dot(bx::load<bx::Vec3>(face.m_plane), bx::load<bx::Vec3>(_light) ) + face.m_plane[3];
				bool frontFacing = (f > 0.0f);

				for (uint8_t ii = 0, num = 1 + uint8_t(!_textureAsStencil); ii < num; ++ii)
				{
					if (frontFacing)
					{
						indicesFrontCap[frontCapI++] = face.m_i[0];
						indicesFrontCap[frontCapI++] = face.m_i[1];
						indicesFrontCap[frontCapI++] = face.m_i[2];
					}
					else
					{
						indicesBackCap[backCapI++] = face.m_i[0];
						indicesBackCap[backCapI++] = face.m_i[1];
						indicesBackCap[backCapI++] = face.m_i[2];
					}
				}
			}
		}
	}

	bgfx::VertexLayout layout;
	layout.begin()
		.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.end();

	//fill the structure
	_shadowVolume.m_numVertices = vsideI;
	_shadowVolume.m_numIndices  = sideI + frontCapI + backCapI;
	_shadowVolume.m_mtx         = _mtx;
	_shadowVolume.m_lightPos    = _light;
	_shadowVolume.m_cap         = cap;

	const bgfx::Memory* mem;

	//sides
	uint32_t vsize = vsideI * 5*sizeof(float);
	uint32_t isize = sideI * sizeof(uint16_t);

	mem = bgfx::makeRef(verticesSide, vsize);
	_shadowVolume.m_vbSides = bgfx::createVertexBuffer(mem, layout);

	mem = bgfx::makeRef(indicesSide, isize);
	_shadowVolume.m_ibSides = bgfx::createIndexBuffer(mem);

	// bgfx::destroy*Buffer doesn't actually destroy buffers now.
	// Instead, these bgfx::destroy*Buffer commands get queued to be executed after the end of the next frame.
	bgfx::destroy(_shadowVolume.m_vbSides);
	bgfx::destroy(_shadowVolume.m_ibSides);

	if (cap)
	{
		//front cap
		isize = frontCapI * sizeof(uint16_t);
		mem = bgfx::makeRef(indicesFrontCap, isize);
		_shadowVolume.m_ibFrontCap = bgfx::createIndexBuffer(mem);

		//gets destroyed after the end of the next frame
		bgfx::destroy(_shadowVolume.m_ibFrontCap);

		//back cap
		isize = backCapI * sizeof(uint16_t);
		mem = bgfx::makeRef(indicesBackCap, isize);
		_shadowVolume.m_ibBackCap = bgfx::createIndexBuffer(mem);

		//gets destroyed after the end of the next frame
		bgfx::destroy(_shadowVolume.m_ibBackCap);
	}
}

void createNearClipVolume(
	  float* _outPlanes24f
	, float* _lightPos
	, float* _view
	, float _fovy
	, float _aspect
	, float _near
	)
{
	float (*volumePlanes)[4] = (float(*)[4])_outPlanes24f;

	float mtxViewInv[16];
	float mtxViewTrans[16];
	bx::mtxInverse(mtxViewInv, _view);
	bx::mtxTranspose(mtxViewTrans, _view);

	float lightPosV[4];
	bx::vec4MulMtx(lightPosV, _lightPos, _view);

	const float delta = 0.1f;

	const float nearNormal[4] = { 0.0f, 0.0f, 1.0f, _near };
	const float d = bx::dot(bx::load<bx::Vec3>(lightPosV), bx::load<bx::Vec3>(nearNormal) ) + lightPosV[3] * nearNormal[3];

	// Light is:
	//  1.0f - in front of near plane
	//  0.0f - on the near plane
	// -1.0f - behind near plane
	const float lightSide = float( (d > delta) - (d < -delta) );

	const float t = bx::tan(bx::toRad(_fovy)*0.5f) * _near;
	const float b = -t;
	const float r = t * _aspect;
	const float l = -r;

	const bx::Vec3 corners[4] =
	{
		bx::mul({ r, t, _near }, mtxViewInv),
		bx::mul({ l, t, _near }, mtxViewInv),
		bx::mul({ l, b, _near }, mtxViewInv),
		bx::mul({ r, b, _near }, mtxViewInv),
	};

	float planeNormals[4][3];
	for (uint8_t ii = 0; ii < 4; ++ii)
	{
		float* outNormal = planeNormals[ii];
		float* outPlane  = volumePlanes[ii];

		const bx::Vec3 c0       = corners[ii];
		const bx::Vec3 planeVec = bx::sub(c0, corners[(ii-1)&3]);
		const bx::Vec3 light    = bx::sub(bx::load<bx::Vec3>(_lightPos), bx::mul(c0, _lightPos[3]) );
		const bx::Vec3 normal   = bx::mul(bx::cross(planeVec, light), lightSide);

		const float invLen = 1.0f / bx::sqrt(bx::dot(normal, normal) );

		bx::store(outNormal, normal);
		bx::store(outPlane, bx::mul(normal, invLen) );
		outPlane[3] = -bx::dot(normal, c0) * invLen;
	}

	float nearPlaneV[4] =
	{
		0.0f * lightSide,
		0.0f * lightSide,
		1.0f * lightSide,
		_near * lightSide,
	};
	bx::vec4MulMtx(volumePlanes[4], nearPlaneV, mtxViewTrans);

	float* lightPlane = volumePlanes[5];
	const bx::Vec3 lightPlaneNormal = bx::sub(bx::mul({ 0.0f, 0.0f, -_near * lightSide }, mtxViewInv), bx::load<bx::Vec3>(_lightPos) );

	float lenInv = 1.0f / bx::sqrt(bx::dot(lightPlaneNormal, lightPlaneNormal) );

	lightPlane[0] = lightPlaneNormal.x * lenInv;
	lightPlane[1] = lightPlaneNormal.y * lenInv;
	lightPlane[2] = lightPlaneNormal.z * lenInv;
	lightPlane[3] = -bx::dot(lightPlaneNormal, bx::load<bx::Vec3>(_lightPos) ) * lenInv;
}

bool clipTest(const float* _planes, uint8_t _planeNum, const Mesh& _mesh, const float* _scale, const float* _translate)
{
	float (*volumePlanes)[4] = (float(*)[4])_planes;
	float scale = bx::max(_scale[0], _scale[1], _scale[2]);

	const GroupArray& groups = _mesh.m_groups;
	for (GroupArray::const_iterator it = groups.begin(), itEnd = groups.end(); it != itEnd; ++it)
	{
		const Group& group = *it;

		Sphere sphere = group.m_sphere;
		sphere.center.x = sphere.center.x * scale + _translate[0];
		sphere.center.y = sphere.center.y * scale + _translate[1];
		sphere.center.z = sphere.center.z * scale + _translate[2];
		sphere.radius *= (scale+0.4f);

		bool isInside = true;
		for (uint8_t ii = 0; ii < _planeNum; ++ii)
		{
			const float* plane = volumePlanes[ii];

			float positiveSide = bx::dot(bx::load<bx::Vec3>(plane), sphere.center ) + plane[3] + sphere.radius;

			if (positiveSide < 0.0f)
			{
				isInside = false;
				break;
			}
		}

		if (isInside)
		{
			return true;
		}
	}

	return false;
}

struct ShadowVolumeProgramType
{
	enum Enum
	{
		Blank = 0,
		Color,
		Tex1,
		Tex2,

		Count
	};
};

struct ShadowVolumePart
{
	enum Enum
	{
		Back = 0,
		Side,
		Front,

		Count
	};
};

enum LightPattern
{
	LightPattern0 = 0,
	LightPattern1
};

enum MeshChoice
{
	BunnyHighPoly = 0,
	BunnyLowPoly
};

enum Scene
{
	Scene0 = 0,
	Scene1,

	SceneCount
};

class ExampleShadowVolumes : public entry::AppI
{
public:
	ExampleShadowVolumes(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_viewState   = ViewState(_width, _height);
		m_clearValues = { 0x00000000, 1.0f, 0 };

		m_debug = BGFX_DEBUG_TEXT;
		m_reset = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_viewState.m_width;
		init.resolution.height = m_viewState.m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		const bgfx::Caps* caps = bgfx::getCaps();
		s_oglNdc    = caps->homogeneousDepth;
		s_texelHalf = bgfx::RendererType::Direct3D9 == caps->rendererType ? 0.5f : 0.0f;

		// Imgui
		imguiCreate();

		PosNormalTexcoordVertex::init();

		s_uniforms.init();

		m_figureTex     = loadTexture("textures/figure-rgba.dds");
		m_flareTex      = loadTexture("textures/flare.dds");
		m_fieldstoneTex = loadTexture("textures/fieldstone-rgba.dds");

		bgfx::TextureHandle fbtextures[] =
		{
			bgfx::createTexture2D(uint16_t(m_viewState.m_width), uint16_t(m_viewState.m_height), false, 1, bgfx::TextureFormat::BGRA8, BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_TEXTURE_RT),
			bgfx::createTexture2D(uint16_t(m_viewState.m_width), uint16_t(m_viewState.m_height), false, 1, bgfx::TextureFormat::D16,   BGFX_TEXTURE_RT_WRITE_ONLY),
		};

		s_stencilFb  = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);

		s_texColor   = bgfx::createUniform("s_texColor",   bgfx::UniformType::Sampler);
		s_texStencil = bgfx::createUniform("s_texStencil", bgfx::UniformType::Sampler);

		m_programTextureLighting = loadProgram("vs_shadowvolume_texture_lighting", "fs_shadowvolume_texture_lighting");
		m_programColorLighting   = loadProgram("vs_shadowvolume_color_lighting",   "fs_shadowvolume_color_lighting"  );
		m_programColorTexture    = loadProgram("vs_shadowvolume_color_texture",    "fs_shadowvolume_color_texture"   );
		m_programTexture         = loadProgram("vs_shadowvolume_texture",          "fs_shadowvolume_texture"         );

		m_programBackBlank       = loadProgram("vs_shadowvolume_svback",  "fs_shadowvolume_svbackblank" );
		m_programSideBlank       = loadProgram("vs_shadowvolume_svside",  "fs_shadowvolume_svsideblank" );
		m_programFrontBlank      = loadProgram("vs_shadowvolume_svfront", "fs_shadowvolume_svfrontblank");

		m_programBackColor       = loadProgram("vs_shadowvolume_svback",  "fs_shadowvolume_svbackcolor" );
		m_programSideColor       = loadProgram("vs_shadowvolume_svside",  "fs_shadowvolume_svsidecolor" );
		m_programFrontColor      = loadProgram("vs_shadowvolume_svfront", "fs_shadowvolume_svfrontcolor");

		m_programSideTex         = loadProgram("vs_shadowvolume_svside",  "fs_shadowvolume_svsidetex"   );
		m_programBackTex1        = loadProgram("vs_shadowvolume_svback",  "fs_shadowvolume_svbacktex1"  );
		m_programBackTex2        = loadProgram("vs_shadowvolume_svback",  "fs_shadowvolume_svbacktex2"  );
		m_programFrontTex1       = loadProgram("vs_shadowvolume_svfront", "fs_shadowvolume_svfronttex1" );
		m_programFrontTex2       = loadProgram("vs_shadowvolume_svfront", "fs_shadowvolume_svfronttex2" );

		bgfx::ProgramHandle svProgs[ShadowVolumeProgramType::Count][ShadowVolumePart::Count] =
		{
			{ m_programBackBlank, m_programSideBlank, m_programFrontBlank }, // Blank
			{ m_programBackColor, m_programSideColor, m_programFrontColor }, // Color
			{ m_programBackTex1,  m_programSideTex,   m_programFrontTex1  }, // Tex1
			{ m_programBackTex2,  m_programSideTex,   m_programFrontTex2  }, // Tex2
		};
		bx::memCopy(m_svProgs, svProgs, sizeof(svProgs));

		m_bunnyHighPolyModel.load("meshes/bunny_patched.bin");
		m_bunnyHighPolyModel.m_program = m_programColorLighting;

		m_bunnyLowPolyModel.load("meshes/bunny_decimated.bin");
		m_bunnyLowPolyModel.m_program = m_programColorLighting;

		m_columnModel.load("meshes/column.bin");
		m_columnModel.m_program = m_programColorLighting;

		m_platformModel.load("meshes/platform.bin");
		m_platformModel.m_program = m_programTextureLighting;
		m_platformModel.m_texture = m_figureTex;

		m_cubeModel.load("meshes/cube.bin");
		m_cubeModel.m_program = m_programTextureLighting;
		m_cubeModel.m_texture = m_figureTex;

		m_hplaneFieldModel.load(s_hplaneVertices
			, BX_COUNTOF(s_hplaneVertices)
			, PosNormalTexcoordVertex::ms_layout
			, s_planeIndices
			, BX_COUNTOF(s_planeIndices)
			);
		m_hplaneFieldModel.m_program = m_programTextureLighting;
		m_hplaneFieldModel.m_texture = m_fieldstoneTex;

		m_hplaneFigureModel.load(s_hplaneVertices
			, BX_COUNTOF(s_hplaneVertices)
			, PosNormalTexcoordVertex::ms_layout
			, s_planeIndices
			, BX_COUNTOF(s_planeIndices)
			);
		m_hplaneFigureModel.m_program = m_programTextureLighting;
		m_hplaneFigureModel.m_texture = m_figureTex;

		m_vplaneModel.load(s_vplaneVertices
			, BX_COUNTOF(s_vplaneVertices)
			, PosNormalTexcoordVertex::ms_layout
			, s_planeIndices
			, BX_COUNTOF(s_planeIndices)
			);
		m_vplaneModel.m_program = m_programColorTexture;
		m_vplaneModel.m_texture = m_flareTex;

		// Setup lights.
		const float rgbInnerR[MAX_LIGHTS_COUNT][4] =
		{
			{ 1.0f, 0.7f, 0.2f, 0.0f }, //yellow
			{ 0.7f, 0.2f, 1.0f, 0.0f }, //purple
			{ 0.2f, 1.0f, 0.7f, 0.0f }, //cyan
			{ 1.0f, 0.4f, 0.2f, 0.0f }, //orange
			{ 0.7f, 0.7f, 0.7f, 0.0f }, //white
		};

		for (uint8_t ii = 0, jj = 0; ii < MAX_LIGHTS_COUNT; ++ii, ++jj)
		{
			const uint8_t index = jj%MAX_LIGHTS_COUNT;
			m_lightRgbInnerR[ii][0] = rgbInnerR[index][0];
			m_lightRgbInnerR[ii][1] = rgbInnerR[index][1];
			m_lightRgbInnerR[ii][2] = rgbInnerR[index][2];
			m_lightRgbInnerR[ii][3] = rgbInnerR[index][3];
		}

		m_profTime = 0;
		m_timeOffset = bx::getHPCounter();

		m_numShadowVolumeVertices = 0;
		m_numShadowVolumeIndices  = 0;

		m_oldWidth = 0;
		m_oldHeight = 0;

		// Imgui.
		m_showHelp          = false;
		m_updateLights      = true;
		m_updateScene       = true;
		m_mixedSvImpl       = true;
		m_useStencilTexture = false;
		m_drawShadowVolumes = false;
		m_numLights         = 1;
		m_instanceCount     = 9;
		m_shadowVolumeImpl      = ShadowVolumeImpl::DepthFail;
		m_shadowVolumeAlgorithm = ShadowVolumeAlgorithm::EdgeBased;

		m_lightPattern = LightPattern0;
		m_currentMesh  = BunnyLowPoly;
		m_currentScene = Scene0;

		// Set view matrix
		cameraCreate();
		cameraSetPosition({ 3.0f, 20.0f, -58.0f });
		cameraSetVerticalAngle(-0.25f);
		cameraGetViewMtx(m_viewState.m_view);
	}

	virtual int shutdown() override
	{
		// Cleanup
		m_bunnyLowPolyModel.unload();
		m_bunnyHighPolyModel.unload();
		m_columnModel.unload();
		m_cubeModel.unload();
		m_platformModel.unload();
		m_hplaneFieldModel.unload();
		m_hplaneFigureModel.unload();
		m_vplaneModel.unload();

		s_uniforms.destroy();

		bgfx::destroy(s_texColor);
		bgfx::destroy(s_texStencil);
		bgfx::destroy(s_stencilFb);

		bgfx::destroy(m_figureTex);
		bgfx::destroy(m_fieldstoneTex);
		bgfx::destroy(m_flareTex);

		bgfx::destroy(m_programTextureLighting);
		bgfx::destroy(m_programColorLighting);
		bgfx::destroy(m_programColorTexture);
		bgfx::destroy(m_programTexture);

		bgfx::destroy(m_programBackBlank);
		bgfx::destroy(m_programSideBlank);
		bgfx::destroy(m_programFrontBlank);
		bgfx::destroy(m_programBackColor);
		bgfx::destroy(m_programSideColor);
		bgfx::destroy(m_programFrontColor);
		bgfx::destroy(m_programSideTex);
		bgfx::destroy(m_programBackTex1);
		bgfx::destroy(m_programBackTex2);
		bgfx::destroy(m_programFrontTex1);
		bgfx::destroy(m_programFrontTex2);

		cameraDestroy();
		imguiDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_viewState.m_width, m_viewState.m_height, m_debug, m_reset, &m_mouseState) )
		{
			s_uniforms.submitConstUniforms();

			// Set projection matrices.
			const float fov = 60.0f;
			const float aspect = float(m_viewState.m_width)/float(m_viewState.m_height);
			const float nearPlane = 1.0f;
			const float farPlane = 1000.0f;

			// Respond properly on resize.
			if (m_oldWidth  != m_viewState.m_width
			||  m_oldHeight != m_viewState.m_height)
			{
				m_oldWidth  = m_viewState.m_width;
				m_oldHeight = m_viewState.m_height;

				bgfx::destroy(s_stencilFb);

				bgfx::TextureHandle fbtextures[] =
				{
					bgfx::createTexture2D(uint16_t(m_viewState.m_width), uint16_t(m_viewState.m_height), false, 1, bgfx::TextureFormat::BGRA8, BGFX_SAMPLER_U_CLAMP|BGFX_SAMPLER_V_CLAMP|BGFX_TEXTURE_RT),
					bgfx::createTexture2D(uint16_t(m_viewState.m_width), uint16_t(m_viewState.m_height), false, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_WRITE_ONLY)
				};
				s_stencilFb = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
			}

			// Time.
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0/freq;
			float time = (float)( (now - m_timeOffset)/double(bx::getHPFrequency() ) );
			const float deltaTime = float(frameTime/freq);
			s_uniforms.m_time = time;

			// Update camera.
			cameraUpdate(deltaTime, m_mouseState, ImGui::MouseOverArea() );

			// Set view and projection matrix for view 0.
			{
				cameraGetViewMtx(m_viewState.m_view);
				bx::mtxProj(m_viewState.m_proj, fov, aspect, nearPlane, farPlane, s_oglNdc);
			}

			imguiBeginFrame(
				   m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_viewState.m_width)
				, uint16_t(m_viewState.m_height)
				);

			showExampleDialog(this);

			ImGui::SetNextWindowPos(
				  ImVec2(m_viewState.m_width - 256.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(256.0f, 700.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			const char* titles[2] =
			{
				"Scene 0",
				"Scene 1",
			};

			if (ImGui::RadioButton(titles[Scene0], Scene0 == m_currentScene) )
			{
				m_currentScene = Scene0;
			}

			if (ImGui::RadioButton(titles[Scene1], Scene1 == m_currentScene) )
			{
				m_currentScene = Scene1;
			}

			ImGui::SliderInt("Lights", &m_numLights, 1, MAX_LIGHTS_COUNT);
			ImGui::Checkbox("Update lights", &m_updateLights);
			ImGui::Indent();

			if (ImGui::RadioButton("Light pattern 0", LightPattern0 == m_lightPattern) )
			{
				m_lightPattern = LightPattern0;
			}

			if (ImGui::RadioButton("Light pattern 1", LightPattern1 == m_lightPattern) )
			{
				m_lightPattern = LightPattern1;
			}

			ImGui::Unindent();

			if ( Scene0 == m_currentScene )
			{
				ImGui::Checkbox("Update scene", &m_updateScene);
			}

			ImGui::Separator();

			ImGui::Text("Stencil buffer implementation:");
			ImGui::Checkbox("Mixed", &m_mixedSvImpl);
			if (!m_mixedSvImpl)
			{
				m_shadowVolumeImpl = (ImGui::RadioButton("Depth fail", ShadowVolumeImpl::DepthFail == m_shadowVolumeImpl) ? ShadowVolumeImpl::DepthFail : m_shadowVolumeImpl);
				m_shadowVolumeImpl = (ImGui::RadioButton("Depth pass", ShadowVolumeImpl::DepthPass == m_shadowVolumeImpl) ? ShadowVolumeImpl::DepthPass : m_shadowVolumeImpl);
			}

			ImGui::Text("Shadow volume implementation:");
			m_shadowVolumeAlgorithm = (ImGui::RadioButton("Face based impl.", ShadowVolumeAlgorithm::FaceBased == m_shadowVolumeAlgorithm) ? ShadowVolumeAlgorithm::FaceBased : m_shadowVolumeAlgorithm);
			m_shadowVolumeAlgorithm = (ImGui::RadioButton("Edge based impl.", ShadowVolumeAlgorithm::EdgeBased == m_shadowVolumeAlgorithm) ? ShadowVolumeAlgorithm::EdgeBased : m_shadowVolumeAlgorithm);

			ImGui::Text("Stencil:");
			if (ImGui::RadioButton("Use stencil buffer", !m_useStencilTexture) )
			{
				if (m_useStencilTexture)
				{
					m_useStencilTexture = false;
				}
			}
			if (ImGui::RadioButton("Use texture as stencil", m_useStencilTexture) )
			{
				if (!m_useStencilTexture)
				{
					m_useStencilTexture = true;
				}
			}

			ImGui::Separator();
			ImGui::Text("Mesh:");
			if (ImGui::RadioButton("Bunny - high poly", BunnyHighPoly == m_currentMesh) )
			{
				m_currentMesh = BunnyHighPoly;
			}

			if (ImGui::RadioButton("Bunny - low poly",  BunnyLowPoly  == m_currentMesh) )
			{
				m_currentMesh = BunnyLowPoly;
			}

			if (Scene1 == m_currentScene)
			{
				ImGui::SliderInt("Instance count", &m_instanceCount, 1, MAX_INSTANCE_COUNT);
			}

			ImGui::Text("CPU Time: %7.1f [ms]", double(m_profTime)*toMs);
			ImGui::Text("Volume Vertices: %5.uk", m_numShadowVolumeVertices/1000);
			ImGui::Text("Volume Indices: %6.uk", m_numShadowVolumeIndices/1000);
			m_numShadowVolumeVertices = 0;
			m_numShadowVolumeIndices = 0;

			ImGui::Separator();
			ImGui::Checkbox("Draw Shadow Volumes", &m_drawShadowVolumes);

			ImGui::End();

			ImGui::SetNextWindowPos(
				  ImVec2(10, float(m_viewState.m_height) - 77.0f - 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(120.0f, 77.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Show help:"
				, NULL
				, 0
				);

			if (ImGui::Button(m_showHelp ? "ON" : "OFF") )
			{
				m_showHelp = !m_showHelp;
			}

			ImGui::End();

			imguiEndFrame();

			//update settings
			s_uniforms.m_params.m_ambientPass     = 1.0f;
			s_uniforms.m_params.m_lightingPass    = 1.0f;
			s_uniforms.m_params.m_texelHalf       = s_texelHalf;
			s_uniforms.m_svparams.m_useStencilTex = float(m_useStencilTexture);

			//set picked bunny model
			Model* bunnyModel = BunnyLowPoly == m_currentMesh ? &m_bunnyLowPolyModel : &m_bunnyHighPolyModel;

			//update time accumulators
			static float sceneTimeAccumulator = 0.0f;
			if (m_updateScene)
			{
				sceneTimeAccumulator += deltaTime;
			}

			static float lightTimeAccumulator = 0.0f;
			if (m_updateLights)
			{
				lightTimeAccumulator += deltaTime;
			}

			//setup light positions
			float lightPosRadius[MAX_LIGHTS_COUNT][4];
			if (LightPattern0 == m_lightPattern)
			{
				for (uint8_t ii = 0; ii < m_numLights; ++ii)
				{
					lightPosRadius[ii][0] = bx::cos(2.0f*bx::kPi/float(m_numLights) * float(ii) + lightTimeAccumulator * 1.1f + 3.0f) * 20.0f;
					lightPosRadius[ii][1] = 20.0f;
					lightPosRadius[ii][2] = bx::sin(2.0f*bx::kPi/float(m_numLights) * float(ii) + lightTimeAccumulator * 1.1f + 3.0f) * 20.0f;
					lightPosRadius[ii][3] = 20.0f;
				}
			}
			else
			{
				for (uint8_t ii = 0; ii < m_numLights; ++ii)
				{
					lightPosRadius[ii][0] = bx::cos(float(ii) * 2.0f/float(m_numLights) + lightTimeAccumulator * 1.3f + bx::kPi) * 40.0f;
					lightPosRadius[ii][1] = 20.0f;
					lightPosRadius[ii][2] = bx::sin(float(ii) * 2.0f/float(m_numLights) + lightTimeAccumulator * 1.3f + bx::kPi) * 40.0f;
					lightPosRadius[ii][3] = 20.0f;
				}
			}

			if (m_showHelp)
			{
				uint8_t row = 18;
				bgfx::dbgTextPrintf(3, row++, 0x0f, "Stencil buffer implementation:");
				bgfx::dbgTextPrintf(8, row++, 0x0f, "Depth fail - Robust, but slower than 'Depth pass'. Requires computing and drawing of shadow volume caps.");
				bgfx::dbgTextPrintf(8, row++, 0x0f, "Depth pass - Faster, but not stable. Shadows are wrong when camera is in the shadow.");
				bgfx::dbgTextPrintf(8, row++, 0x0f, "Mixed      - 'Depth pass' where possible, 'Depth fail' where necessary. Best of both words.");

				row++;
				bgfx::dbgTextPrintf(3, row++, 0x0f, "Shadow volume implementation:");
				bgfx::dbgTextPrintf(8, row++, 0x0f, "Face Based - Slower. Works fine with either stencil buffer or texture as stencil.");
				bgfx::dbgTextPrintf(8, row++, 0x0f, "Edge Based - Faster, but requires +2 incr/decr on stencil buffer. To avoid massive redraw, use RGBA texture as stencil.");

				row++;
				bgfx::dbgTextPrintf(3, row++, 0x0f, "Stencil:");
				bgfx::dbgTextPrintf(8, row++, 0x0f, "Stencil buffer     - Faster, but capable only of +1 incr.");
				bgfx::dbgTextPrintf(8, row++, 0x0f, "Texture as stencil - Slower, but capable of +2 incr.");
			}
			else
			{
				bgfx::dbgTextClear();
			}

			// Setup instances
			Instance shadowCasters[SceneCount][60];
			uint16_t shadowCastersCount[SceneCount];
			for (uint8_t ii = 0; ii < SceneCount; ++ii)
			{
				shadowCastersCount[ii] = 0;
			}

			Instance shadowReceivers[SceneCount][10];
			uint16_t shadowReceiversCount[SceneCount];
			for (uint8_t ii = 0; ii < SceneCount; ++ii)
			{
				shadowReceiversCount[ii] = 0;
			}

			// Scene 0 - shadow casters - Bunny
			{
				Instance& inst = shadowCasters[Scene0][shadowCastersCount[Scene0]++];
				inst.m_scale[0]    = 5.0f;
				inst.m_scale[1]    = 5.0f;
				inst.m_scale[2]    = 5.0f;
				inst.m_rotation[0] = 0.0f;
				inst.m_rotation[1] = float(4.0f - sceneTimeAccumulator * 0.7f);
				inst.m_rotation[2] = 0.0f;
				inst.m_pos[0]      = 0.0f;
				inst.m_pos[1]      = 10.0f;
				inst.m_pos[2]      = 0.0f;
				inst.m_color[0]    = 0.68f;
				inst.m_color[1]    = 0.65f;
				inst.m_color[2]    = 0.60f;
				inst.m_model       = bunnyModel;
			}

			// Scene 0 - shadow casters - Cubes top.
			const uint8_t numCubesTop = 9;
			for (uint16_t ii = 0; ii < numCubesTop; ++ii)
			{
				Instance& inst = shadowCasters[Scene0][shadowCastersCount[Scene0]++];
				inst.m_scale[0]    = 1.0f;
				inst.m_scale[1]    = 1.0f;
				inst.m_scale[2]    = 1.0f;
				inst.m_rotation[0] = 0.0f;
				inst.m_rotation[1] = 0.0f;
				inst.m_rotation[2] = 0.0f;
				inst.m_pos[0]      = bx::sin(ii * 2.0f + 13.0f + sceneTimeAccumulator * 1.1f) * 13.0f;
				inst.m_pos[1]      = 6.0f;
				inst.m_pos[2]      = bx::cos(ii * 2.0f + 13.0f + sceneTimeAccumulator * 1.1f) * 13.0f;
				inst.m_model       = &m_cubeModel;
			}

			// Scene 0 - shadow casters - Cubes bottom.
			const uint8_t numCubesBottom = 9;
			for (uint16_t ii = 0; ii < numCubesBottom; ++ii)
			{
				Instance& inst = shadowCasters[Scene0][shadowCastersCount[Scene0]++];
				inst.m_scale[0]    = 1.0f;
				inst.m_scale[1]    = 1.0f;
				inst.m_scale[2]    = 1.0f;
				inst.m_rotation[0] = 0.0f;
				inst.m_rotation[1] = 0.0f;
				inst.m_rotation[2] = 0.0f;
				inst.m_pos[0]      = bx::sin(ii * 2.0f + 13.0f + sceneTimeAccumulator * 1.1f) * 13.0f;
				inst.m_pos[1]      = 22.0f;
				inst.m_pos[2]      = bx::cos(ii * 2.0f + 13.0f + sceneTimeAccumulator * 1.1f) * 13.0f;
				inst.m_model       = &m_cubeModel;
			}

			// Scene 0 - shadow casters - Columns.
			const float dist = 16.0f;
			const float columnPositions[][3] =
			{
				{  dist, 3.3f,  dist },
				{ -dist, 3.3f,  dist },
				{  dist, 3.3f, -dist },
				{ -dist, 3.3f, -dist },
			};

			for (uint8_t ii = 0; ii < 4; ++ii)
			{
				Instance& inst = shadowCasters[Scene0][shadowCastersCount[Scene0]++];
				inst.m_scale[0]    = 1.5f;
				inst.m_scale[1]    = 1.5f;
				inst.m_scale[2]    = 1.5f;
				inst.m_rotation[0] = 0.0f;
				inst.m_rotation[1] = 1.57f;
				inst.m_rotation[2] = 0.0f;
				inst.m_pos[0]      = columnPositions[ii][0];
				inst.m_pos[1]      = columnPositions[ii][1];
				inst.m_pos[2]      = columnPositions[ii][2];
				inst.m_color[0]    = 0.25f;
				inst.m_color[1]    = 0.25f;
				inst.m_color[2]    = 0.25f;
				inst.m_model       = &m_columnModel;
			}

			// Scene 0 - shadow casters - Ceiling.
			{
				Instance& inst = shadowCasters[Scene0][shadowCastersCount[Scene0]++];
				inst.m_scale[0]    = 21.0f;
				inst.m_scale[1]    = 21.0f;
				inst.m_scale[2]    = 21.0f;
				inst.m_rotation[0] = bx::kPi;
				inst.m_rotation[1] = 0.0f;
				inst.m_rotation[2] = 0.0f;
				inst.m_pos[0]      = 0.0f;
				inst.m_pos[1]      = 28.2f;
				inst.m_pos[2]      = 0.0f;
				inst.m_model       = &m_platformModel;
				inst.m_svExtrusionDistance = 2.0f; //prevent culling on tight view frustum
			}

			// Scene 0 - shadow casters - Platform.
			{
				Instance& inst = shadowCasters[Scene0][shadowCastersCount[Scene0]++];
				inst.m_scale[0]    = 24.0f;
				inst.m_scale[1]    = 24.0f;
				inst.m_scale[2]    = 24.0f;
				inst.m_rotation[0] = 0.0f;
				inst.m_rotation[1] = 0.0f;
				inst.m_rotation[2] = 0.0f;
				inst.m_pos[0]      = 0.0f;
				inst.m_pos[1]      = 0.0f;
				inst.m_pos[2]      = 0.0f;
				inst.m_model       = &m_platformModel;
				inst.m_svExtrusionDistance = 2.0f; //prevent culling on tight view frustum
			}

			// Scene 0 - shadow receivers - Floor.
			{
				Instance& inst = shadowReceivers[Scene0][shadowReceiversCount[Scene0]++];
				inst.m_scale[0]    = 500.0f;
				inst.m_scale[1]    = 500.0f;
				inst.m_scale[2]    = 500.0f;
				inst.m_rotation[0] = 0.0f;
				inst.m_rotation[1] = 0.0f;
				inst.m_rotation[2] = 0.0f;
				inst.m_pos[0]      = 0.0f;
				inst.m_pos[1]      = 0.0f;
				inst.m_pos[2]      = 0.0f;
				inst.m_model       = &m_hplaneFieldModel;
			}

			// Scene 1 - shadow casters - Bunny instances
			{
				enum Direction
				{
					Left  = 0x0,
					Down  = 0x1,
					Right = 0x2,
					Up    = 0x3,
				};
				const uint8_t directionMask = 0x3;

				uint8_t currentDirection = Left;
				float currX = 0.0f;
				float currY = 0.0f;
				const float stepX = 20.0f;
				const float stepY = 20.0f;
				uint8_t stateStep = 0;
				uint8_t stateChange = 1;

				for (uint8_t ii = 0; ii < m_instanceCount; ++ii)
				{
					Instance& inst = shadowCasters[Scene1][shadowCastersCount[Scene1]++];
					inst.m_scale[0]    = 5.0f;
					inst.m_scale[1]    = 5.0f;
					inst.m_scale[2]    = 5.0f;
					inst.m_rotation[0] = 0.0f;
					inst.m_rotation[1] = bx::kPi;
					inst.m_rotation[2] = 0.0f;
					inst.m_pos[0]      = currX;
					inst.m_pos[1]      = 0.0f;
					inst.m_pos[2]      = currY;
					inst.m_model       = bunnyModel;

					++stateStep;
					if (stateStep >= ( (stateChange & ~0x1) >> 1) )
					{
						currentDirection = (currentDirection + 1) & directionMask;
						stateStep = 0;
						++stateChange;
					}

					switch (currentDirection)
					{
					case Left:  currX -= stepX; break;
					case Down:  currY -= stepY; break;
					case Right: currX += stepX; break;
					case Up:    currY += stepY; break;
					}
				}
			}

			// Scene 1 - shadow receivers - Floor.
			{
				Instance& inst = shadowReceivers[Scene1][shadowReceiversCount[Scene1]++];
				inst.m_scale[0]    = 500.0f;
				inst.m_scale[1]    = 500.0f;
				inst.m_scale[2]    = 500.0f;
				inst.m_rotation[0] = 0.0f;
				inst.m_rotation[1] = 0.0f;
				inst.m_rotation[2] = 0.0f;
				inst.m_pos[0]      = 0.0f;
				inst.m_pos[1]      = 0.0f;
				inst.m_pos[2]      = 0.0f;
				inst.m_model       = &m_hplaneFigureModel;
			}

			// Make sure at the beginning everything gets cleared.
			bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR
				| BGFX_CLEAR_DEPTH
				| BGFX_CLEAR_STENCIL
				, m_clearValues.m_clearRgba
				, m_clearValues.m_clearDepth
				, m_clearValues.m_clearStencil
				);

			::touch(0);

			// Draw ambient only.
			s_uniforms.m_params.m_ambientPass = 1.0f;
			s_uniforms.m_params.m_lightingPass = 0.0f;

			s_uniforms.m_color[0] = 1.0f;
			s_uniforms.m_color[1] = 1.0f;
			s_uniforms.m_color[2] = 1.0f;

			const RenderState& drawAmbient = m_useStencilTexture
				? s_renderStates[RenderState::ShadowVolume_UsingStencilTexture_DrawAmbient]
				: s_renderStates[RenderState::ShadowVolume_UsingStencilBuffer_DrawAmbient]
				;

			// Draw shadow casters.
			for (uint8_t ii = 0; ii < shadowCastersCount[m_currentScene]; ++ii)
			{
				shadowCasters[m_currentScene][ii].submit(VIEWID_RANGE1_PASS0, drawAmbient);
			}

			// Draw shadow receivers.
			for (uint8_t ii = 0; ii < shadowReceiversCount[m_currentScene]; ++ii)
			{
				shadowReceivers[m_currentScene][ii].submit(VIEWID_RANGE1_PASS0, drawAmbient);
			}

			// Using stencil texture requires rendering to separate render target. first pass is building depth buffer.
			if (m_useStencilTexture)
			{
				bgfx::setViewClear(VIEWID_RANGE1_RT_PASS1, BGFX_CLEAR_DEPTH, 0x00000000, 1.0f, 0);
				bgfx::setViewFrameBuffer(VIEWID_RANGE1_RT_PASS1, s_stencilFb);

				const RenderState& renderState = s_renderStates[RenderState::ShadowVolume_UsingStencilTexture_BuildDepth];

				for (uint8_t ii = 0; ii < shadowCastersCount[m_currentScene]; ++ii)
				{
					shadowCasters[m_currentScene][ii].submit(VIEWID_RANGE1_RT_PASS1, renderState);
				}

				for (uint8_t ii = 0; ii < shadowReceiversCount[m_currentScene]; ++ii)
				{
					shadowReceivers[m_currentScene][ii].submit(VIEWID_RANGE1_RT_PASS1, renderState);
				}
			}

			m_profTime = bx::getHPCounter();

			/**
			 * For each light:
			 * 1. Compute and draw shadow volume to stencil buffer
			 * 2. Draw diffuse with stencil test
			 */
			for (uint8_t ii = 0, viewId = VIEWID_RANGE15_PASS2; ii < m_numLights; ++ii, ++viewId)
			{
				const float* lightPos = lightPosRadius[ii];

				bx::memCopy(s_uniforms.m_lightPosRadius, lightPosRadius[ii],   4*sizeof(float) );
				bx::memCopy(s_uniforms.m_lightRgbInnerR, m_lightRgbInnerR[ii], 3*sizeof(float) );
				bx::memCopy(s_uniforms.m_color,          m_lightRgbInnerR[ii], 3*sizeof(float) );

				if (m_useStencilTexture)
				{
					bgfx::setViewFrameBuffer(viewId, s_stencilFb);

					bgfx::setViewClear(viewId
						, BGFX_CLEAR_COLOR
						, 0x00000000
						, 1.0f
						, 0
						);
				}
				else
				{
					const bgfx::FrameBufferHandle invalid = BGFX_INVALID_HANDLE;
					bgfx::setViewFrameBuffer(viewId, invalid);

					bgfx::setViewClear(viewId
						, BGFX_CLEAR_STENCIL
						, m_clearValues.m_clearRgba
						, m_clearValues.m_clearDepth
						, m_clearValues.m_clearStencil
						);
				}

				// Create near clip volume for current light.
				float nearClipVolume[6 * 4] = {};
				float pointLight[4];
				if (m_mixedSvImpl)
				{
					pointLight[0] = lightPos[0];
					pointLight[1] = lightPos[1];
					pointLight[2] = lightPos[2];
					pointLight[3] = 1.0f;
					createNearClipVolume(nearClipVolume, pointLight, m_viewState.m_view, fov, aspect, nearPlane);
				}

				for (uint8_t jj = 0; jj < shadowCastersCount[m_currentScene]; ++jj)
				{
					const Instance& instance = shadowCasters[m_currentScene][jj];
					Model* model = instance.m_model;

					ShadowVolumeImpl::Enum shadowVolumeImpl = m_shadowVolumeImpl;
					if (m_mixedSvImpl)
					{
						// If instance is inside near clip volume, depth fail must be used, else depth pass is fine.
						bool isInsideVolume = clipTest(nearClipVolume, 6, model->m_mesh, instance.m_scale, instance.m_pos);
						shadowVolumeImpl = (isInsideVolume ? ShadowVolumeImpl::DepthFail : ShadowVolumeImpl::DepthPass);
					}
					s_uniforms.m_svparams.m_dfail = float(ShadowVolumeImpl::DepthFail == shadowVolumeImpl);

					// Compute virtual light position for shadow volume generation.
					float transformedLightPos[3];
					shadowVolumeLightTransform(transformedLightPos
						, instance.m_scale
						, instance.m_rotation
						, instance.m_pos
						, lightPos
						);

					// Set virtual light pos.
					bx::memCopy(s_uniforms.m_virtualLightPos_extrusionDist, transformedLightPos, 3*sizeof(float) );
					s_uniforms.m_virtualLightPos_extrusionDist[3] = instance.m_svExtrusionDistance;

					// Compute transform for shadow volume.
					float shadowVolumeMtx[16];
					bx::mtxSRT(shadowVolumeMtx
						, instance.m_scale[0]
						, instance.m_scale[1]
						, instance.m_scale[2]
						, instance.m_rotation[0]
						, instance.m_rotation[1]
						, instance.m_rotation[2]
						, instance.m_pos[0]
						, instance.m_pos[1]
						, instance.m_pos[2]
						);

					GroupArray& groups = model->m_mesh.m_groups;
					const uint16_t stride = model->m_mesh.m_layout.getStride();
					for (GroupArray::iterator it = groups.begin(), itEnd = groups.end(); it != itEnd; ++it)
					{
						Group& group = *it;

						// Create shadow volume.
						ShadowVolume shadowVolume;
						shadowVolumeCreate(shadowVolume
							, group
							, stride
							, shadowVolumeMtx
							, transformedLightPos
							, shadowVolumeImpl
							, m_shadowVolumeAlgorithm
							, m_useStencilTexture
							);

						m_numShadowVolumeVertices += shadowVolume.m_numVertices;
						m_numShadowVolumeIndices += shadowVolume.m_numIndices;

						ShadowVolumeProgramType::Enum programIndex = ShadowVolumeProgramType::Blank;
						RenderState::Enum renderStateIndex;
						if (m_useStencilTexture)
						{
							renderStateIndex = ShadowVolumeImpl::DepthFail == shadowVolumeImpl
								? RenderState::ShadowVolume_UsingStencilTexture_CraftStencil_DepthFail
								: RenderState::ShadowVolume_UsingStencilTexture_CraftStencil_DepthPass
								;

							programIndex = ShadowVolumeAlgorithm::FaceBased == m_shadowVolumeAlgorithm
								? ShadowVolumeProgramType::Tex1
								: ShadowVolumeProgramType::Tex2
								;
						}
						else
						{
							renderStateIndex = ShadowVolumeImpl::DepthFail == shadowVolumeImpl
								? RenderState::ShadowVolume_UsingStencilBuffer_CraftStencil_DepthFail
								: RenderState::ShadowVolume_UsingStencilBuffer_CraftStencil_DepthPass
								;
						}
						const RenderState& renderStateCraftStencil = s_renderStates[renderStateIndex];

						s_uniforms.submitPerDrawUniforms();
						bgfx::setTransform(shadowVolumeMtx);
						bgfx::setVertexBuffer(0, shadowVolume.m_vbSides);
						bgfx::setIndexBuffer(shadowVolume.m_ibSides);
						setRenderState(renderStateCraftStencil);
						::submit(viewId, m_svProgs[programIndex][ShadowVolumePart::Side]);

						if (shadowVolume.m_cap)
						{
							s_uniforms.submitPerDrawUniforms();
							bgfx::setTransform(shadowVolumeMtx);
							bgfx::setVertexBuffer(0, group.m_vbh);
							bgfx::setIndexBuffer(shadowVolume.m_ibFrontCap);
							setRenderState(renderStateCraftStencil);
							::submit(viewId, m_svProgs[programIndex][ShadowVolumePart::Front]);

							s_uniforms.submitPerDrawUniforms();
							bgfx::setTransform(shadowVolumeMtx);
							bgfx::setVertexBuffer(0, group.m_vbh);
							bgfx::setIndexBuffer(shadowVolume.m_ibBackCap);
							::setRenderState(renderStateCraftStencil);
							::submit(viewId, m_svProgs[programIndex][ShadowVolumePart::Back]);
						}

						if (m_drawShadowVolumes)
						{
							const RenderState& renderState = s_renderStates[RenderState::Custom_DrawShadowVolume_Lines];

							s_uniforms.submitPerDrawUniforms();
							bgfx::setTransform(shadowVolumeMtx);
							bgfx::setVertexBuffer(0, shadowVolume.m_vbSides);
							bgfx::setIndexBuffer(shadowVolume.m_ibSides);
							::setRenderState(renderState);
							::submit(VIEWID_RANGE1_PASS3, m_svProgs[ShadowVolumeProgramType::Color][ShadowVolumePart::Side]);

							if (shadowVolume.m_cap)
							{
								s_uniforms.submitPerDrawUniforms();
								bgfx::setTransform(shadowVolumeMtx);
								bgfx::setVertexBuffer(0, group.m_vbh);
								bgfx::setIndexBuffer(shadowVolume.m_ibFrontCap);
								::setRenderState(renderState);
								::submit(VIEWID_RANGE1_PASS3, m_svProgs[ShadowVolumeProgramType::Color][ShadowVolumePart::Front]);

								s_uniforms.submitPerDrawUniforms();
								bgfx::setTransform(shadowVolumeMtx);
								bgfx::setVertexBuffer(0, group.m_vbh);
								bgfx::setIndexBuffer(shadowVolume.m_ibBackCap);
								::setRenderState(renderState);
								::submit(VIEWID_RANGE1_PASS3, m_svProgs[ShadowVolumeProgramType::Color][ShadowVolumePart::Back]);
							}
						}
					}
				}

				// Draw diffuse only.
				s_uniforms.m_params.m_ambientPass = 0.0f;
				s_uniforms.m_params.m_lightingPass = 1.0f;

				RenderState& drawDiffuse = m_useStencilTexture
					? s_renderStates[RenderState::ShadowVolume_UsingStencilTexture_DrawDiffuse]
					: s_renderStates[RenderState::ShadowVolume_UsingStencilBuffer_DrawDiffuse]
					;

				// If using stencil texture, viewId is set to render target. Incr it to render to default back buffer.
				viewId += uint8_t(m_useStencilTexture);

				// Draw shadow casters.
				for (uint8_t jj = 0; jj < shadowCastersCount[m_currentScene]; ++jj)
				{
					shadowCasters[m_currentScene][jj].submit(viewId, drawDiffuse);
				}

				// Draw shadow receivers.
				for (uint8_t jj = 0; jj < shadowReceiversCount[m_currentScene]; ++jj)
				{
					shadowReceivers[m_currentScene][jj].submit(viewId, drawDiffuse);
				}
			}

			m_profTime = bx::getHPCounter() - m_profTime;

			// Lights.
			const float lightScale[3] = { 1.5f, 1.5f, 1.5f };
			for (uint8_t ii = 0; ii < m_numLights; ++ii)
			{
				bx::memCopy(s_uniforms.m_color, m_lightRgbInnerR[ii], 3*sizeof(float) );

				float lightMtx[16];
				mtxBillboard(lightMtx, m_viewState.m_view, lightPosRadius[ii], lightScale);

				m_vplaneModel.submit(VIEWID_RANGE1_PASS3, lightMtx, s_renderStates[RenderState::Custom_BlendLightTexture]);
			}

			// Setup view rect and transform for all used views.
			setViewRectMask(s_viewMask, 0, 0, uint16_t(m_viewState.m_width), uint16_t(m_viewState.m_height) );
			setViewTransformMask(s_viewMask, m_viewState.m_view, m_viewState.m_proj);
			s_viewMask = 0;

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			// Swap memory pages.
			s_svAllocator.swap();

			// Reset clear values.
			setViewClearMask(UINT32_MAX
				, BGFX_CLEAR_NONE
				, m_clearValues.m_clearRgba
				, m_clearValues.m_clearDepth
				, m_clearValues.m_clearStencil
				);

			return true;
		}

		return false;
	}

	ViewState m_viewState;
	ClearValues m_clearValues;

	uint32_t m_debug;
	uint32_t m_reset;

	bgfx::TextureHandle m_figureTex;
	bgfx::TextureHandle m_flareTex;
	bgfx::TextureHandle m_fieldstoneTex;

	bgfx::ProgramHandle m_programTextureLighting;
	bgfx::ProgramHandle m_programColorLighting;
	bgfx::ProgramHandle m_programColorTexture;
	bgfx::ProgramHandle m_programTexture;

	bgfx::ProgramHandle m_programBackBlank;
	bgfx::ProgramHandle m_programSideBlank;
	bgfx::ProgramHandle m_programFrontBlank;

	bgfx::ProgramHandle m_programBackColor;
	bgfx::ProgramHandle m_programSideColor;
	bgfx::ProgramHandle m_programFrontColor;

	bgfx::ProgramHandle m_programSideTex;
	bgfx::ProgramHandle m_programBackTex1;
	bgfx::ProgramHandle m_programBackTex2;
	bgfx::ProgramHandle m_programFrontTex1;
	bgfx::ProgramHandle m_programFrontTex2;

	bgfx::ProgramHandle m_svProgs[ShadowVolumeProgramType::Count][ShadowVolumePart::Count];

	Model m_bunnyLowPolyModel;
	Model m_bunnyHighPolyModel;
	Model m_columnModel;
	Model m_platformModel;
	Model m_cubeModel;
	Model m_hplaneFieldModel;
	Model m_hplaneFigureModel;
	Model m_vplaneModel;

	float m_lightRgbInnerR[MAX_LIGHTS_COUNT][4];

	int64_t m_profTime;
	int64_t m_timeOffset;

	uint32_t m_numShadowVolumeVertices;
	uint32_t m_numShadowVolumeIndices;

	uint32_t m_oldWidth;
	uint32_t m_oldHeight;

	int32_t m_numLights;
	int32_t m_instanceCount;
	bool m_showHelp;
	bool m_updateLights;
	bool m_updateScene;
	bool m_mixedSvImpl;
	bool m_useStencilTexture;
	bool m_drawShadowVolumes;
	ShadowVolumeImpl::Enum      m_shadowVolumeImpl;
	ShadowVolumeAlgorithm::Enum m_shadowVolumeAlgorithm;

	LightPattern m_lightPattern;
	MeshChoice   m_currentMesh;
	Scene        m_currentScene;

	entry::MouseState m_mouseState;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleShadowVolumes
	, "14-shadowvolumes"
	, "Shadow volumes."
	, "https://bkaradzic.github.io/bgfx/examples.html#shadowvolumes");
