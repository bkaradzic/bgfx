/*
 * Copyright 2013 Dario Manesku. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"

#include <bgfx.h>
#include <bx/timer.h>
#include <bx/readerwriter.h>
#include "entry/entry.h"
#include "fpumath.h"
#include "imgui/imgui.h"

#include <string>
#include <vector>

#define RENDER_VIEWID_RANGE1_PASS_0   1 
#define RENDER_VIEWID_RANGE1_PASS_1   2 
#define RENDER_VIEWID_RANGE1_PASS_2   3 
#define RENDER_VIEWID_RANGE1_PASS_3   4 
#define RENDER_VIEWID_RANGE1_PASS_4   5 
#define RENDER_VIEWID_RANGE1_PASS_5   6 
#define RENDER_VIEWID_RANGE5_PASS_6   7
#define RENDER_VIEWID_RANGE1_PASS_7   13 

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
};

static const float s_texcoord = 5.0f;
static const uint32_t s_numHPlaneVertices = 4;
static PosNormalTexcoordVertex s_hplaneVertices[s_numHPlaneVertices] =
{
	{ -1.0f, 0.0f,  1.0f, packF4u(0.0f, 1.0f, 0.0f), s_texcoord, s_texcoord },
	{  1.0f, 0.0f,  1.0f, packF4u(0.0f, 1.0f, 0.0f), s_texcoord, 0.0f       },
	{ -1.0f, 0.0f, -1.0f, packF4u(0.0f, 1.0f, 0.0f), 0.0f,       s_texcoord },
	{  1.0f, 0.0f, -1.0f, packF4u(0.0f, 1.0f, 0.0f), 0.0f,       0.0f       },
};

static const uint32_t s_numVPlaneVertices = 4;
static PosNormalTexcoordVertex s_vplaneVertices[s_numVPlaneVertices] =
{
	{ -1.0f,  1.0f, 0.0f, packF4u(0.0f, 0.0f, -1.0f), 1.0f, 1.0f },
	{  1.0f,  1.0f, 0.0f, packF4u(0.0f, 0.0f, -1.0f), 1.0f, 0.0f },
	{ -1.0f, -1.0f, 0.0f, packF4u(0.0f, 0.0f, -1.0f), 0.0f, 1.0f },
	{  1.0f, -1.0f, 0.0f, packF4u(0.0f, 0.0f, -1.0f), 0.0f, 0.0f },
};

static const uint32_t s_numCubeVertices = 24;
static const PosNormalTexcoordVertex s_cubeVertices[s_numCubeVertices] =
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

static const uint32_t s_numCubeIndices = 36;
static const uint16_t s_cubeIndices[s_numCubeIndices] =
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

static const uint32_t s_numPlaneIndices = 6;
static const uint16_t s_planeIndices[s_numPlaneIndices] =
{
	0, 1, 2,
	1, 3, 2,
};

//-------------------------------------------------
// Helper functions
//-------------------------------------------------

static const char* s_shaderPath = NULL;
static bool s_flipV = false;
static uint32_t s_viewMask = 0;
static uint32_t s_clearMask = 0;
static bgfx::UniformHandle u_texColor;

static void shaderFilePath(char* _out, const char* _name)
{
	strcpy(_out, s_shaderPath);
	strcat(_out, _name);
	strcat(_out, ".bin");
}

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
}

static const bgfx::Memory* load(const char* _filePath)
{
	FILE* file = fopen(_filePath, "rb");
	if (NULL != file)
	{
		uint32_t size = (uint32_t)fsize(file);
		const bgfx::Memory* mem = bgfx::alloc(size+1);
		size_t ignore = fread(mem->data, 1, size, file);
		BX_UNUSED(ignore);
		fclose(file);
		mem->data[mem->size-1] = '\0';
		return mem;
	}

	return NULL;
}

static const bgfx::Memory* loadShader(const char* _name)
{
	char filePath[512];
	shaderFilePath(filePath, _name);
	return load(filePath);
}

static const bgfx::Memory* loadTexture(const char* _name)
{
	char filePath[512];
	strcpy(filePath, "textures/");
	strcat(filePath, _name);
	return load(filePath);
}

static bgfx::ProgramHandle loadProgram(const char* _vsName, const char* _fsName)
{
	const bgfx::Memory* mem;

	// Load vertex shader.
	mem = loadShader(_vsName);
	bgfx::VertexShaderHandle vsh = bgfx::createVertexShader(mem);

	// Load fragment shader.
	mem = loadShader(_fsName);
	bgfx::FragmentShaderHandle fsh = bgfx::createFragmentShader(mem);

	// Create program from shaders.
	bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh);

	// We can destroy vertex and fragment shader here since
	// their reference is kept inside bgfx after calling createProgram.
	// Vertex and fragment shader will be destroyed once program is
	// destroyed.
	bgfx::destroyVertexShader(vsh);
	bgfx::destroyFragmentShader(fsh);

	return program;
}

//-------------------------------------------------
// Math
//-------------------------------------------------

void mtxScaleRotateTranslate(float* _result
							 , const float _scaleX
							 , const float _scaleY
							 , const float _scaleZ
							 , const float _rotX
							 , const float _rotY
							 , const float _rotZ
							 , const float _translateX
							 , const float _translateY
							 , const float _translateZ
							 )
{
	float mtxRotateTranslate[16];
	float mtxScale[16];

	mtxRotateXYZ(mtxRotateTranslate, _rotX, _rotY, _rotZ);
	mtxRotateTranslate[12] = _translateX;
	mtxRotateTranslate[13] = _translateY;
	mtxRotateTranslate[14] = _translateZ;

	memset(mtxScale, 0, sizeof(float)*16);
	mtxScale[0]  = _scaleX;
	mtxScale[5]  = _scaleY;
	mtxScale[10] = _scaleZ;
	mtxScale[15] = 1.0f;

	mtxMul(_result, mtxScale, mtxRotateTranslate);
}

void mtxReflected(float*__restrict _result
				  , const float* __restrict _p  /* plane */
				  , const float* __restrict _n  /* normal */
				  )
{
	float dot = vec3Dot(_p, _n);

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

struct RenderState
{
	enum Enum
	{
		StencilReflection_CraftStencil = 0,
		StencilReflection_DrawReflected,
		StencilReflection_DarkenReflections,
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
		BGFX_STATE_MSAA
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
	{ // StencilReflection_DarkenReflections
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ZERO, BGFX_STATE_BLEND_FACTOR)
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CCW
		| BGFX_STATE_MSAA
		, UINT32_MAX
		, BGFX_STENCIL_NONE
		, BGFX_STENCIL_NONE
	},
	{ // StencilReflection_BlendPlane
		BGFX_STATE_RGB_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_BLEND_LIGHTEN
		| BGFX_STATE_DEPTH_TEST_EQUAL
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
		| BGFX_STATE_DEPTH_WRITE
		| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_FACTOR, BGFX_STATE_BLEND_ONE)
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
	ViewState(uint32_t _width  = 1280
		, uint32_t _height = 720
		)
		: m_width(_width)
		, m_height(_height)
	{ }

	uint32_t m_width;
	uint32_t m_height;

	float m_view[16], m_proj[16];
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

void setViewRectTransform(uint8_t _view, const ViewState& _viewState)
{
	bgfx::setViewRect(_view, 0, 0, _viewState.m_width, _viewState.m_height);
	bgfx::setViewTransform(_view, _viewState.m_view, _viewState.m_proj);
}

void setViewRectTransformMask(uint32_t _viewMask, const ViewState& _viewState)
{
	bgfx::setViewRectMask(_viewMask, 0, 0, _viewState.m_width, _viewState.m_height);
	bgfx::setViewTransformMask(_viewMask, _viewState.m_view, _viewState.m_proj);
}

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
	bgfx::setViewClearMask(_viewMask
		, _flags
		, _clearValues.m_clearRgba
		, _clearValues.m_clearDepth
		, _clearValues.m_clearStencil
		);

	// Keep track of cleared views
	s_clearMask |= _viewMask;
}

void submit(uint8_t _id, int32_t _depth = 0)
{
	// Submit
	bgfx::submit(_id, _depth);

	// Keep track of submited view ids
	s_viewMask |= 1 << _id;
}

void submitMask(uint32_t _viewMask, int32_t _depth = 0)
{
	// Submit
	bgfx::submitMask(_viewMask, _depth);

	// Keep track of submited view ids
	s_viewMask |= _viewMask;
}

//-------------------------------------------------
// Mesh
//-------------------------------------------------

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
#define BGFX_CHUNK_MAGIC_VB BX_MAKEFOURCC('V', 'B', ' ', 0x0)
#define BGFX_CHUNK_MAGIC_IB BX_MAKEFOURCC('I', 'B', ' ', 0x0)
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

					bx::read(&reader, m_decl);
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

			// Set model matrix for rendering.
			bgfx::setTransform(_mtx);
			bgfx::setProgram(_program);
			bgfx::setIndexBuffer(group.m_ibh);
			bgfx::setVertexBuffer(group.m_vbh);

			// Set texture
			if (bgfx::invalidHandle != _texture.idx)
			{
				bgfx::setTexture(0, u_texColor, _texture);
			}

			// Apply render state
			bgfx::setStencil(_renderState.m_fstencil, _renderState.m_bstencil);
			bgfx::setState(_renderState.m_state, _renderState.m_blendFactorRgba);

			// Submit
			::submit(_viewId);
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
	default:
	case bgfx::RendererType::Direct3D9:
		s_shaderPath = "shaders/dx9/";
		break;

	case bgfx::RendererType::Direct3D11:
		s_shaderPath = "shaders/dx11/";
		break;

	case bgfx::RendererType::OpenGL:
		s_shaderPath = "shaders/glsl/";
		s_flipV = true;
		break;

	case bgfx::RendererType::OpenGLES2:
	case bgfx::RendererType::OpenGLES3:
		s_shaderPath = "shaders/gles/";
		s_flipV = true;
		break;
	}

	FILE* file = fopen("font/droidsans.ttf", "rb");
	uint32_t size = (uint32_t)fsize(file);
	void* data = malloc(size);
	size_t ignore = fread(data, 1, size, file);
	BX_UNUSED(ignore);
	fclose(file);
	imguiCreate(data, size);

	bgfx::VertexDecl PosNormalTexcoordDecl;
	PosNormalTexcoordDecl.begin();
	PosNormalTexcoordDecl.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float);
	PosNormalTexcoordDecl.add(bgfx::Attrib::Normal,    4, bgfx::AttribType::Uint8, true, true);
	PosNormalTexcoordDecl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
	PosNormalTexcoordDecl.end();

	const uint8_t MAX_NUM_LIGHTS = 5;

	//u_params.x - u_ambientPass
	//u_params.y - u_lightningPass
	//u_params.z - u_alpha
	//u_params.w - u_lightCount
	struct UniformParams
	{
		float m_ambientPass;
		float m_lightningPass;
		float m_alpha;
		float m_lightCount;
	} params;

	u_texColor                           = bgfx::createUniform("u_texColor",            bgfx::UniformType::Uniform1iv);

	bgfx::UniformHandle u_params         = bgfx::createUniform("u_params",              bgfx::UniformType::Uniform4fv);
	bgfx::UniformHandle u_ambient        = bgfx::createUniform("u_ambient",             bgfx::UniformType::Uniform3fv);
	bgfx::UniformHandle u_diffuse        = bgfx::createUniform("u_diffuse",             bgfx::UniformType::Uniform3fv);
	bgfx::UniformHandle u_specular       = bgfx::createUniform("u_specular_shininess",  bgfx::UniformType::Uniform4fv);
	bgfx::UniformHandle u_color          = bgfx::createUniform("u_color",               bgfx::UniformType::Uniform4fv);
	bgfx::UniformHandle u_time           = bgfx::createUniform("u_time",                bgfx::UniformType::Uniform1f );
	bgfx::UniformHandle u_lightPosRadius = bgfx::createUniform("u_lightPosRadius",      bgfx::UniformType::Uniform4fv, MAX_NUM_LIGHTS);
	bgfx::UniformHandle u_lightRgbInnerR = bgfx::createUniform("u_lightRgbInnerR",      bgfx::UniformType::Uniform4fv, MAX_NUM_LIGHTS);

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
	cubeMesh.load(s_cubeVertices, s_numCubeVertices, PosNormalTexcoordDecl, s_cubeIndices, s_numCubeIndices);
	hplaneMesh.load(s_hplaneVertices, s_numHPlaneVertices, PosNormalTexcoordDecl, s_planeIndices, s_numPlaneIndices);
	vplaneMesh.load(s_vplaneVertices, s_numVPlaneVertices, PosNormalTexcoordDecl, s_planeIndices, s_numPlaneIndices);

	const bgfx::Memory* mem;

	mem = loadTexture("figure-rgba.dds");
	bgfx::TextureHandle figureTex = bgfx::createTexture(mem);

	mem = loadTexture("flare.dds");
	bgfx::TextureHandle flareTex = bgfx::createTexture(mem);

	mem = loadTexture("fieldstone-rgba.dds");
	bgfx::TextureHandle fieldstoneTex = bgfx::createTexture(mem);

	//setup lights
	uint8_t numLights = 5;
	const float rgbInnerR[5][4] =
	{
		{ 1.0f, 0.7f, 0.2f, 0.0f }, //yellow
		{ 0.7f, 0.2f, 1.0f, 0.0f }, //purple
		{ 0.2f, 1.0f, 0.7f, 0.0f }, //cyan
		{ 1.0f, 0.4f, 0.2f, 0.0f }, //orange
		{ 0.7f, 0.7f, 0.7f, 0.0f }, //white
	};

	float lightRgbInnerR[MAX_NUM_LIGHTS][4];
	for (uint8_t ii = 0, jj = 0; ii < numLights; ++ii, ++jj)
	{
		const uint8_t index = jj%numLights;
		lightRgbInnerR[ii][0] = rgbInnerR[index][0];
		lightRgbInnerR[ii][1] = rgbInnerR[index][1];
		lightRgbInnerR[ii][2] = rgbInnerR[index][2];
		lightRgbInnerR[ii][3] = rgbInnerR[index][3];
	}
	bgfx::setUniform(u_lightRgbInnerR, lightRgbInnerR, numLights);

	//init uniforms
	params.m_ambientPass = 1.0f;
	params.m_lightningPass = 1.0f;
	params.m_lightCount = 4.0f;
	params.m_alpha = 1.0f;
	bgfx::setUniform(u_params, (const void*)&params);

	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bgfx::setUniform(u_color, color);

	float ambient[3]  = { 0.02f, 0.02f, 0.02f };
	float diffuse[3]  = { 0.8f, 0.8f, 0.8f };
	float specular[4] = { 1.0f, 1.0f, 1.0f, 5.0f };
	bgfx::setUniform(u_ambient, ambient);
	bgfx::setUniform(u_diffuse, diffuse);
	bgfx::setUniform(u_specular, specular);

	int64_t timeOffset = bx::getHPCounter();

	enum Scene
	{
		StencilReflectionScene = 0,
		ProjectionShadowsScene,
	}

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
		//imgui

		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT : 0)
			, 0
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
		imguiSlider("Lights", &settings_numLights, 1.0f, 5.0f, 1.0f);
		if (scene == StencilReflectionScene)
		{
			imguiSlider("Reflection value", &settings_reflectionValue, 0.0f, 1.0f, 0.01f);
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
		numLights = (uint8_t)settings_numLights;
		params.m_ambientPass = 1.0f;
		params.m_lightningPass = 1.0f;
		params.m_lightCount = settings_numLights;
		bgfx::setUniform(u_params, (const void*)&params);

		// Time.
		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;
		float time = (float)( (now - timeOffset)/double(bx::getHPFrequency() ) );
		const float deltaTime = float(frameTime/freq);
		bgfx::setUniform(u_time, &time);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/13-stencil");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Stencil reflections and shadows.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Set view and projection matrices.
		const float aspect = float(viewState.m_width)/float(viewState.m_height);
		mtxProj(viewState.m_proj, 60.0f, aspect, 0.1f, 100.0f);
		float at[3] = { 0.0f, 5.0f, 0.0f };
		float eye[3] = { 0.0f, 18.0f, -40.0f };
		mtxLookAt(viewState.m_view, eye, at);

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
		const float radius = (scene == StencilReflectionScene) ? 0.0f : 60.0f;
		for (uint8_t ii = 0; ii < numLights; ++ii)
		{
			lightPosRadius[ii][0] = sin( (lightTimeAccumulator*(1.1f + ii*0.07f) + float(ii*M_PI_2)*1.07f ) )*25.0f;
			lightPosRadius[ii][1] = 7.0f + (1.0f - cos( (lightTimeAccumulator*(1.2f + ii*0.29f) + float(ii*M_PI_2)*1.49f ) ))*5.0f;
			lightPosRadius[ii][2] = cos( (lightTimeAccumulator*(1.3f + ii*0.09f) + float(ii*M_PI_2)*1.79f ) )*20.0f;
			lightPosRadius[ii][3] = radius;
		}
		bgfx::setUniform(u_lightPosRadius, lightPosRadius, numLights);


		//-------------------------------------------------
		// Render
		//-------------------------------------------------

		//floor position
		float floorMtx[16];
		mtxScaleRotateTranslate(floorMtx
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

		//bunny position
		float bunnyMtx[16];
		mtxScaleRotateTranslate(bunnyMtx
			, 5.0f                          //scaleX
			, 5.0f                          //scaleY
			, 5.0f                          //scaleZ
			, 0.0f                          //rotX
			, 1.56f + sceneTimeAccumulator  //rotY
			, 0.0f                          //rotZ
			, 0.0f                          //translateX
			, 2.0f                          //translateY
			, 0.0f                          //translateZ
			);

		//columns position
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
			mtxScaleRotateTranslate(columnMtx[ii]
				, 1.0f                    //scaleX
				, 1.0f                    //scaleY
				, 1.0f                    //scaleZ
				, 0.0f                    //rotX
				, 0.0f                    //rotY
				, 0.0f                    //rotZ
				, columnPositions[ii][0]  //translateX
				, columnPositions[ii][1]  //translateY
				, columnPositions[ii][2]  //translateZ
				);
		}

		const uint8_t numCubes = 9;
		float cubeMtx[numCubes][16];
		for (uint16_t ii = 0; ii < numCubes; ++ii)
		{
			mtxScaleRotateTranslate(cubeMtx[ii]
				, 1.0f  //scaleX
				, 1.0f  //scaleY
				, 1.0f  //scaleZ
				, 0.0f  //rotX
				, 0.0f  //rotY
				, 0.0f  //rotZ
				, sin(ii * 2.0f + 13.0f + sceneTimeAccumulator) * 13.0f  //translateX
				, 4.0f                                                   //translateY
				, cos(ii * 2.0f + 13.0f + sceneTimeAccumulator) * 13.0f  //translateZ
				);
		}

		// Make sure at the beginning everything gets cleared
		clearView(0, BGFX_CLEAR_COLOR_BIT | BGFX_CLEAR_DEPTH_BIT | BGFX_CLEAR_STENCIL_BIT, clearValues);
		submit(0);

		//white bunny and columns
		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 1.0f;
		bgfx::setUniform(u_color, color);

		switch (scene)
		{
		case StencilReflectionScene:
			{
				// First pass - Draw plane.

				// Floor
				hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_0
					, floorMtx
					, programColorBlack
					, s_renderStates[RenderState::StencilReflection_CraftStencil]
					);

				// Second pass - Draw reflected objects.

				// Compute reflected matrix.
				float reflectMtx[16];
				float plane_pos[3] = { 0.0f, 0.01f, 0.0f };
				float normal[3] = { 0.0f, 1.0f, 0.0f };
				mtxReflected(reflectMtx, plane_pos, normal);

				// Reflect lights.
				float reflectedLights[MAX_NUM_LIGHTS][4];
				for (uint8_t ii = 0; ii < numLights; ++ii)
				{
					vec3MulMtx(reflectedLights[ii], lightPosRadius[ii], reflectMtx);
					reflectedLights[ii][3] = lightPosRadius[ii][3];
				}
				bgfx::setUniform(u_lightPosRadius, reflectedLights, numLights);

				// Reflect and submit bunny.
				float mtxReflectedBunny[16];
				mtxMul(mtxReflectedBunny, bunnyMtx, reflectMtx);
				bunnyMesh.submit(RENDER_VIEWID_RANGE1_PASS_1
					, mtxReflectedBunny
					, programColorLightning
					, s_renderStates[RenderState::StencilReflection_DrawReflected]
					);

				// Reflect and submit columns.
				float mtxReflectedColumn[16];
				for (uint8_t ii = 0; ii < 4; ++ii)
				{
					mtxMul(mtxReflectedColumn, columnMtx[ii], reflectMtx);
					columnMesh.submit(RENDER_VIEWID_RANGE1_PASS_1
						, mtxReflectedColumn
						, programColorLightning
						, s_renderStates[RenderState::StencilReflection_DrawReflected]
						);
				}

				// Set lights back.
				bgfx::setUniform(u_lightPosRadius, lightPosRadius, numLights);

				// Third pass - Darken reflected objects.

				uint8_t val = uint8_t(settings_reflectionValue * UINT8_MAX);
				uint32_t factor = (val << 24)
					| (val << 16)
					| (val << 8 )
					| (val << 0 )
					;
				s_renderStates[RenderState::StencilReflection_DarkenReflections].m_blendFactorRgba = factor;

				// Floor.
				hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_2
					, floorMtx
					, programColorBlack
					, s_renderStates[RenderState::StencilReflection_DarkenReflections]
					);

				// Fourth pass - Draw plane. (blend plane with what's behind it)

				// Floor.
				hplaneMesh.submit(RENDER_VIEWID_RANGE1_PASS_3
					, floorMtx
					, programTextureLightning
					, s_renderStates[RenderState::StencilReflection_BlendPlane]
					, fieldstoneTex
					);

				// Fifth pass - Draw everything else but the plane.
				
				// Bunny.
				bunnyMesh.submit(RENDER_VIEWID_RANGE1_PASS_4
					, bunnyMtx
					, programColorLightning
					, s_renderStates[RenderState::StencilReflection_DrawScene]
					);

				// Columns.
				for (uint8_t ii = 0; ii < 4; ++ii)
				{
					columnMesh.submit(RENDER_VIEWID_RANGE1_PASS_4
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
				params.m_ambientPass = 1.0f;
				params.m_lightningPass = 1.0f;
				bgfx::setUniform(u_params, (const void*)&params);

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
				ground[3] = -vec3Dot(plane_pos, normal) - 0.01f; // - 0.01 against z-fighting

				for (uint8_t ii = 0; ii < numLights; ++ii)               
				{
					uint8_t viewId = RENDER_VIEWID_RANGE5_PASS_6+ii;
					clearView(viewId, BGFX_CLEAR_STENCIL_BIT, clearValues);

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
					mtxMul(mtxShadowedBunny, bunnyMtx, shadowMtx);
					bunnyMesh.submit(viewId
						, mtxShadowedBunny
						, programColorLightning
						, s_renderStates[RenderState::ProjectionShadows_CraftStencil]
					);

					// Submit cube shadows.
					float mtxShadowedCube[16];
					for (uint8_t ii = 0; ii < numCubes; ++ii)
					{
						mtxMul(mtxShadowedCube, cubeMtx[ii], shadowMtx);
						cubeMesh.submit(viewId
							, mtxShadowedCube
							, programTextureLightning
							, s_renderStates[RenderState::ProjectionShadows_CraftStencil]
						);
					}

					// Draw entire scene. (lightning pass only. blending is on)

					params.m_ambientPass = 0.0f;
					params.m_lightningPass = 1.0f;
					bgfx::setUniform(u_params, (const void*)&params);

					// Set blending factor based on number of lights.
					uint32_t factor = 0xff / (numLights < 1 ? 1 : numLights);
					factor = (factor << 24)
						| (factor << 16)
						| (factor << 8 )
						| (factor << 0 )
						;
					s_renderStates[RenderState::ProjectionShadows_DrawDiffuse].m_blendFactorRgba = factor;

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
					for (uint8_t ii = 0; ii < numCubes; ++ii)
					{
						cubeMesh.submit(viewId
							, cubeMtx[ii]
							, programTextureLightning
							, s_renderStates[RenderState::ProjectionShadows_DrawDiffuse]
							, figureTex
							);
					}
				}

				// Reset these to default..
				params.m_ambientPass = 1.0f;
				params.m_lightningPass = 1.0f;
				bgfx::setUniform(u_params, (const void*)&params);
			}
			break;
		};

		//lights
		const float lightScale[3] = { 1.5f, 1.5f, 1.5f };
		float lightMtx[16];
		for (uint8_t ii = 0; ii < numLights; ++ii)
		{
			color[0] = lightRgbInnerR[ii][0];
			color[1] = lightRgbInnerR[ii][1];
			color[2] = lightRgbInnerR[ii][2];
			bgfx::setUniform(u_color, color);

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
		mtxScaleRotateTranslate(floorBottomMtx
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
		setViewRectTransformMask(s_viewMask, viewState);
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

	bgfx::destroyUniform(u_params);
	bgfx::destroyUniform(u_ambient);
	bgfx::destroyUniform(u_diffuse);
	bgfx::destroyUniform(u_specular);
	bgfx::destroyUniform(u_color);
	bgfx::destroyUniform(u_time);
	bgfx::destroyUniform(u_lightPosRadius);
	bgfx::destroyUniform(u_lightRgbInnerR);
	bgfx::destroyUniform(u_texColor);

	imguiDestroy();

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
