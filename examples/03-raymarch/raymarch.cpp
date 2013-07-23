/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"

#include <bgfx.h>
#include <bx/timer.h>
#include "entry.h"
#include "dbg.h"
#include "fpumath.h"
#include "processevents.h"

#include <stdio.h>
#include <string.h>

struct PosColorTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
	float m_u;
	float m_v;
};

static bgfx::VertexDecl s_PosColorTexCoord0Decl;

static const char* s_shaderPath = NULL;
static bool s_flipV = false;

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

bool allocTransientBuffers(bgfx::TransientVertexBuffer* _tvb, const bgfx::VertexDecl& _decl, uint16_t _numVertices, bgfx::TransientIndexBuffer* _tib, uint16_t _numIndices)
{
	if (bgfx::checkAvailTransientVertexBuffer(_numVertices, _decl)
	&&  bgfx::checkAvailTransientIndexBuffer(_numIndices) )
	{
		bgfx::allocTransientVertexBuffer(_tvb, _numVertices, _decl);
		bgfx::allocTransientIndexBuffer(_tib, _numIndices);
		return true;
	}

	return false;
}

void renderScreenSpaceQuad(uint32_t _view, bgfx::ProgramHandle _program, float _x, float _y, float _width, float _height)
{
	bgfx::TransientVertexBuffer tvb;
	bgfx::TransientIndexBuffer tib;

	if (allocTransientBuffers(&tvb, s_PosColorTexCoord0Decl, 4, &tib, 6) )
	{
		PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)tvb.data;

		float zz = 0.0f;

		const float minx = _x;
		const float maxx = _x + _width;
		const float miny = _y;
		const float maxy = _y + _height;

		float minu = -1.0f;
		float minv = -1.0f;
		float maxu =  1.0f;
		float maxv =  1.0f;

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_z = zz;
		vertex[0].m_abgr = 0xff0000ff;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = zz;
		vertex[1].m_abgr = 0xff00ff00;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = zz;
		vertex[2].m_abgr = 0xffff0000;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		vertex[3].m_x = minx;
		vertex[3].m_y = maxy;
		vertex[3].m_z = zz;
		vertex[3].m_abgr = 0xffffffff;
		vertex[3].m_u = minu;
		vertex[3].m_v = maxv;

		uint16_t* indices = (uint16_t*)tib.data;

		indices[0] = 0;
		indices[1] = 2;
		indices[2] = 1;
		indices[3] = 0;
		indices[4] = 3;
		indices[5] = 2;

		bgfx::setProgram(_program);
		bgfx::setState(BGFX_STATE_DEFAULT);
		bgfx::setIndexBuffer(&tib);
		bgfx::setVertexBuffer(&tvb);
		bgfx::submit(_view);
	}
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
		s_flipV = true;
		break;

	case bgfx::RendererType::OpenGLES2:
	case bgfx::RendererType::OpenGLES3:
		s_shaderPath = "shaders/gles/";
		s_flipV = true;
		break;
	}

	// Create vertex stream declaration.
	s_PosColorTexCoord0Decl.begin();
	s_PosColorTexCoord0Decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
	s_PosColorTexCoord0Decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
	s_PosColorTexCoord0Decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
	s_PosColorTexCoord0Decl.end();  

	bgfx::UniformHandle u_time = bgfx::createUniform("u_time", bgfx::UniformType::Uniform1f);
	bgfx::UniformHandle u_mtx = bgfx::createUniform("u_mtx", bgfx::UniformType::Uniform4x4fv);
	bgfx::UniformHandle u_lightDir = bgfx::createUniform("u_lightDir", bgfx::UniformType::Uniform3fv);

	bgfx::ProgramHandle raymarching = loadProgram("vs_raymarching", "fs_raymarching");

	int64_t timeOffset = bx::getHPCounter();

	while (!processEvents(width, height, debug, reset) )
	{
		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

		// Set view 1 default viewport.
		bgfx::setViewRect(1, 0, 0, width, height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to viewZ 0.
		bgfx::submit(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/03-raymarch");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Updating shader uniforms.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		float at[3] = { 0.0f, 0.0f, 0.0f };
		float eye[3] = { 0.0f, 0.0f, -15.0f };
		
		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);
		mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		// Set view and projection matrix for view 1.
		bgfx::setViewTransform(0, view, proj);

		float ortho[16];
		mtxOrtho(ortho, 0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(1, NULL, ortho);

		float time = (float)( (bx::getHPCounter()-timeOffset)/double(bx::getHPFrequency() ) );

		float vp[16];
		mtxMul(vp, view, proj);

		float mtx[16];
		mtxRotateXY(mtx
			, time
			, time*0.37f
			); 

		float mtxInv[16];
		mtxInverse(mtxInv, mtx);
		float lightDirModel[4] = { -0.4f, -0.5f, -1.0f, 0.0f };
		float lightDirModelN[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		vec3Norm(lightDirModelN, lightDirModel);
		float lightDir[4];
		vec4MulMtx(lightDir, lightDirModelN, mtxInv);
		bgfx::setUniform(u_lightDir, lightDir);

		float mvp[16];
		mtxMul(mvp, mtx, vp);

		float invMvp[16];
		mtxInverse(invMvp, mvp);
		bgfx::setUniform(u_mtx, invMvp);

		bgfx::setUniform(u_time, &time);

		renderScreenSpaceQuad(1, raymarching, 0.0f, 0.0f, 1280.0f, 720.0f);

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	bgfx::destroyProgram(raymarching);

	bgfx::destroyUniform(u_time);
	bgfx::destroyUniform(u_mtx);
	bgfx::destroyUniform(u_lightDir);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
