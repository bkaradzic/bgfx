/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "../common/common.h"

#include <bgfx.h>
#include <bx/countof.h>
#include <bx/timer.h>
#include "../common/entry.h"
#include "../common/dbg.h"
#include "../common/math.h"
#include "../common/processevents.h"

#include <stdio.h>
#include <string.h>

struct PosNormalTangentTexcoordVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_normal;
	uint32_t m_tangent;
	int16_t m_u;
	int16_t m_v;
};

static bgfx::VertexDecl s_PosNormalTangentTexcoordDecl;

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

static PosNormalTangentTexcoordVertex s_cubeVertices[24] =
{
	{-1.0f,  1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f,  1.0f, packF4u( 0.0f,  0.0f,  1.0f), 0, 0x7fff, 0x7fff },
	{-1.0f,  1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0,      0,      0 },
	{ 1.0f,  1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f, -1.0f, packF4u( 0.0f,  0.0f, -1.0f), 0, 0x7fff, 0x7fff },
	{-1.0f,  1.0f,  1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f,  1.0f, -1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f,  1.0f, -1.0f, packF4u( 0.0f,  1.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{-1.0f, -1.0f,  1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0,      0,      0 },
	{ 1.0f, -1.0f,  1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f, -1.0f, -1.0f, packF4u( 0.0f, -1.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{ 1.0f, -1.0f,  1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0,      0,      0 },
	{ 1.0f,  1.0f,  1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0, 0x7fff,      0 },
	{ 1.0f, -1.0f, -1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0,      0, 0x7fff },
	{ 1.0f,  1.0f, -1.0f, packF4u( 1.0f,  0.0f,  0.0f), 0, 0x7fff, 0x7fff },
	{-1.0f, -1.0f,  1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0,      0,      0 },
	{-1.0f,  1.0f,  1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0, 0x7fff,      0 },
	{-1.0f, -1.0f, -1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0,      0, 0x7fff },
	{-1.0f,  1.0f, -1.0f, packF4u(-1.0f,  0.0f,  0.0f), 0, 0x7fff, 0x7fff },
};

static const uint16_t s_cubeIndices[36] =
{
	 0,  2,  1,
	 1,  2,  3,
	 4,  5,  6,
	 5,  7,  6,

	 8, 10,  9,
	 9, 10, 11,
    12, 13, 14,
	13, 15, 14,

	16, 18, 17,
	17, 18, 19,
	20, 21, 22,
	21, 23, 22,
};

static const char* s_shaderPath = NULL;

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

void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexDecl _decl, const uint16_t* _indices, uint32_t _numIndices)
{
	struct PosTexcoord
	{
		float m_x;
		float m_y;
		float m_z;
		float m_pad0;
		float m_u;
		float m_v;
		float m_pad1;
		float m_pad2;
	};

	float* tangents = new float[6*_numVertices];
	memset(tangents, 0, 6*_numVertices*sizeof(float) );

	PosTexcoord v0;
	PosTexcoord v1;
	PosTexcoord v2;

	for (uint32_t ii = 0, num = _numIndices/3; ii < num; ++ii)
	{
		const uint16_t* indices = &_indices[ii*3];
		uint32_t i0 = indices[0];
		uint32_t i1 = indices[1];
		uint32_t i2 = indices[2];

		bgfx::vertexUnpack(&v0.m_x, bgfx::Attrib::Position, _decl, _vertices, i0);
		bgfx::vertexUnpack(&v0.m_u, bgfx::Attrib::TexCoord0, _decl, _vertices, i0);

		bgfx::vertexUnpack(&v1.m_x, bgfx::Attrib::Position, _decl, _vertices, i1);
		bgfx::vertexUnpack(&v1.m_u, bgfx::Attrib::TexCoord0, _decl, _vertices, i1);

		bgfx::vertexUnpack(&v2.m_x, bgfx::Attrib::Position, _decl, _vertices, i2);
		bgfx::vertexUnpack(&v2.m_u, bgfx::Attrib::TexCoord0, _decl, _vertices, i2);

		const float bax = v1.m_x - v0.m_x;
		const float bay = v1.m_y - v0.m_y;
		const float baz = v1.m_z - v0.m_z;
		const float bau = v1.m_u - v0.m_u;
		const float bav = v1.m_v - v0.m_v;

		const float cax = v2.m_x - v0.m_x;
		const float cay = v2.m_y - v0.m_y;
		const float caz = v2.m_z - v0.m_z;
		const float cau = v2.m_u - v0.m_u;
		const float cav = v2.m_v - v0.m_v;

		const float det = (bau * cav - bav * cau);
		const float invDet = 1.0f / det;

		const float tx = (bax * cav - cax * bav) * invDet;
		const float ty = (bay * cav - cay * bav) * invDet;
		const float tz = (baz * cav - caz * bav) * invDet;

		const float bx = (cax * bau - bax * cau) * invDet;
		const float by = (cay * bau - bay * cau) * invDet;
		const float bz = (caz * bau - baz * cau) * invDet;

		for (uint32_t jj = 0; jj < 3; ++jj)
		{
			float* tanu = &tangents[indices[jj]*6];
			float* tanv = &tanu[3];
			tanu[0] += tx;
			tanu[1] += ty;
			tanu[2] += tz;

			tanv[0] += bx;
			tanv[1] += by;
			tanv[2] += bz;
		}
	}

	for (uint32_t ii = 0; ii < _numVertices; ++ii)
	{
		const float* tanu = &tangents[ii*6];
		const float* tanv = &tangents[ii*6 + 3];

		float normal[4];
		bgfx::vertexUnpack(normal, bgfx::Attrib::Normal, _decl, _vertices, ii);
		float ndt = vec3Dot(normal, tanu);

		float nxt[3];
		vec3Cross(nxt, normal, tanu);

		float tmp[3];
		tmp[0] = tanu[0] - normal[0] * ndt;
		tmp[1] = tanu[1] - normal[1] * ndt;
		tmp[2] = tanu[2] - normal[2] * ndt;

		float tangent[4];
		vec3Norm(tangent, tmp);

		tangent[3] = vec3Dot(nxt, tanv) < 0.0f ? -1.0f : 1.0f;
		bgfx::vertexPack(tangent, true, bgfx::Attrib::Tangent, _decl, _vertices, ii);
	}

	delete [] tangents;
} 

int _main_(int /*_argc*/, char** /*_argv*/)
{
	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init();
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT
		, 0x303030ff
		, 1.0f
		, 0
		);

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
		break;

	case bgfx::RendererType::OpenGLES2:
	case bgfx::RendererType::OpenGLES3:
		s_shaderPath = "shaders/gles/";
		break;
	}

	// Create vertex stream declaration.
	s_PosNormalTangentTexcoordDecl.begin();
	s_PosNormalTangentTexcoordDecl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
	s_PosNormalTangentTexcoordDecl.add(bgfx::Attrib::Normal, 4, bgfx::AttribType::Uint8, true, true);
	s_PosNormalTangentTexcoordDecl.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Uint8, true, true);
	s_PosNormalTangentTexcoordDecl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true, true);
	s_PosNormalTangentTexcoordDecl.end();

	const bgfx::Memory* mem;

	calcTangents(s_cubeVertices, countof(s_cubeVertices), s_PosNormalTangentTexcoordDecl, s_cubeIndices, countof(s_cubeIndices) );

	// Create static vertex buffer.
	mem = bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) );
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(mem, s_PosNormalTangentTexcoordDecl);

	// Create static index buffer.
	mem = bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) );
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(mem);

	// Create texture sampler uniforms.
	bgfx::UniformHandle u_texColor = bgfx::createUniform("u_texColor", bgfx::UniformType::Uniform1iv);
	bgfx::UniformHandle u_texNormal = bgfx::createUniform("u_texNormal", bgfx::UniformType::Uniform1iv);

	uint16_t numLights = 4;
	bgfx::UniformHandle u_lightPosRadius = bgfx::createUniform("u_lightPosRadius", bgfx::UniformType::Uniform4fv, numLights);
	bgfx::UniformHandle u_lightRgbInnerR = bgfx::createUniform("u_lightRgbInnerR", bgfx::UniformType::Uniform4fv, numLights);

	// Load vertex shader.
	mem = loadShader("vs_bump");
	bgfx::VertexShaderHandle vsh = bgfx::createVertexShader(mem);

	// Load fragment shader.
	mem = loadShader("fs_bump");
	bgfx::FragmentShaderHandle fsh = bgfx::createFragmentShader(mem);

	// Create program from shaders.
	bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh);

	// We can destroy vertex and fragment shader here since
	// their reference is kept inside bgfx after calling createProgram.
	// Vertex and fragment shader will be destroyed once program is^
	// destroyed.
	bgfx::destroyVertexShader(vsh);
	bgfx::destroyFragmentShader(fsh);

	// Load diffuse texture.
	mem = loadTexture("fieldstone-rgba.dds");
	bgfx::TextureHandle textureColor = bgfx::createTexture(mem);

	// Load normal texture.
	mem = loadTexture("fieldstone-n.dds");
	bgfx::TextureHandle textureNormal = bgfx::createTexture(mem);

	int64_t timeOffset = bx::getHPCounter();

	while (!processEvents(width, height, debug, reset) )
	{
		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::submit(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		float time = (float)( (now-timeOffset)/freq);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/06-bump");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Loading textures.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		float at[3] = { 0.0f, 0.0f, 0.0f };
		float eye[3] = { 0.0f, 0.0f, -7.0f };
		
		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);
		mtxProj(proj, 60.0f, 16.0f/9.0f, 0.1f, 100.0f);

		float lightPosRadius[4][4];
		for (uint32_t ii = 0; ii < numLights; ++ii)
		{
			lightPosRadius[ii][0] = sin( (time*(0.1f + ii*0.17f) + float(ii*M_PI_2)*1.37f ) )*3.0f;
			lightPosRadius[ii][1] = cos( (time*(0.2f + ii*0.29f) + float(ii*M_PI_2)*1.49f ) )*3.0f;
			lightPosRadius[ii][2] = -2.5f;
			lightPosRadius[ii][3] = 3.0f;
		}

		bgfx::setUniform(u_lightPosRadius, lightPosRadius, numLights);

		float lightRgbInnerR[4][4] =
		{
			{ 1.0f, 0.7f, 0.2f, 0.8f },
			{ 0.7f, 0.2f, 1.0f, 0.8f },
			{ 0.2f, 1.0f, 0.7f, 0.8f },
			{ 1.0f, 0.4f, 0.2f, 0.8f },
		};

		bgfx::setUniform(u_lightRgbInnerR, lightRgbInnerR, numLights);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		const uint16_t instanceStride = 64;
		const bgfx::InstanceDataBuffer* idb = bgfx::allocInstanceDataBuffer(9, instanceStride);
		if (NULL != idb)
		{
			uint8_t* data = idb->data;

			// Write instance data for 3x3 cubes.
			for (uint32_t yy = 0; yy < 3; ++yy)
			{
				for (uint32_t xx = 0; xx < 3; ++xx)
				{
					float* mtx = (float*)data;
					mtxRotateXY(mtx, time*0.023f + xx*0.21f, time*0.03f + yy*0.37f);
					mtx[12] = -3.0f + float(xx)*3.0f;
					mtx[13] = -3.0f + float(yy)*3.0f;
					mtx[14] = 0.0f;

					float* color = (float*)&data[64];
					color[0] = sin(time+float(xx)/11.0f)*0.5f+0.5f;
					color[1] = cos(time+float(yy)/11.0f)*0.5f+0.5f;
					color[2] = sin(time*3.0f)*0.5f+0.5f;
					color[3] = 1.0f;

					data += instanceStride;
				}
			}

			uint16_t numInstances = (uint16_t)( (data - idb->data)/instanceStride);

			// Set vertex and fragment shaders.
			bgfx::setProgram(program);

			// Set vertex and index buffer.
			bgfx::setVertexBuffer(vbh);
			bgfx::setIndexBuffer(ibh);

			// Set instance data buffer.
			bgfx::setInstanceDataBuffer(idb, numInstances);

			// Bind textures.
			bgfx::setTexture(0, u_texColor, textureColor);
			bgfx::setTexture(1, u_texNormal, textureNormal);

			// Set render states.
			bgfx::setState(0
				|BGFX_STATE_RGB_WRITE
				|BGFX_STATE_ALPHA_WRITE
				|BGFX_STATE_DEPTH_WRITE
				|BGFX_STATE_DEPTH_TEST_LESS
				|BGFX_STATE_MSAA
				);

			// Submit primitive for rendering to view 0.
			bgfx::submit(0);
		}

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(program);
	bgfx::destroyTexture(textureColor);
	bgfx::destroyTexture(textureNormal);
	bgfx::destroyUniform(u_texColor);
	bgfx::destroyUniform(u_texNormal);
	bgfx::destroyUniform(u_lightPosRadius);
	bgfx::destroyUniform(u_lightRgbInnerR);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
