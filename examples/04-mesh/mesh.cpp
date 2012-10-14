/*
 * Copyright 2011-2012 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <bx/bx.h>
#include <bx/timer.h>
#include <openctm.h>
#include "../common/dbg.h"
#include "../common/math.h"

#include <stdio.h>
#include <string.h>

void fatalCb(bgfx::Fatal::Enum _code, const char* _str)
{
	DBG("%x: %s", _code, _str);
}

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

static const bgfx::Memory* loadShader(const char* _name, const char* _default = NULL)
{
	char filePath[512];
	shaderFilePath(filePath, _name);
	BX_UNUSED(_default);
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

struct Mesh
{
	void load(const char* _filePath)
	{
		CTMcontext ctm;
		ctm = ctmNewContext(CTM_IMPORT);
		ctmLoad(ctm, _filePath);

		// Create vertex decleration.
		{
			m_decl.begin();
			m_decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);

			if (ctmGetInteger(ctm, CTM_HAS_NORMALS) )
			{
				m_decl.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float, true);
			}

			if (0 < ctmGetInteger(ctm, CTM_UV_MAP_COUNT) )
			{
				m_decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
			}

			CTMenum colorAttrib = ctmGetNamedAttribMap(ctm, "Color");
			if (CTM_NONE != colorAttrib)
			{
				m_decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
			}

			m_decl.end();
		}

		// Allocate vertex buffer and copy vertex attributes.
		{
			CTMuint numVertices = ctmGetInteger(ctm, CTM_VERTEX_COUNT);
			uint32_t stride = m_decl.m_stride;
			const CTMfloat* vertices = ctmGetFloatArray(ctm, CTM_VERTICES);
			const CTMfloat* normals = ctmGetFloatArray(ctm, CTM_NORMALS);
			const bgfx::Memory* mem = bgfx::alloc(numVertices*stride);
			uint8_t* data = mem->data;
			const uint16_t normalOffset = m_decl.getOffset(bgfx::Attrib::Normal);
			const uint16_t color0Offset = m_decl.getOffset(bgfx::Attrib::Color0);
			const bool hasColor0 = m_decl.has(bgfx::Attrib::Color0);

			for (uint32_t ii = 0; ii < numVertices; ++ii)
			{
				{
					float* xyz = (float*)data;
					xyz[0] = vertices[0];
					xyz[1] = vertices[1];
					xyz[2] = vertices[2];
					vertices += 3;
				}

				if (hasColor0)
				{
					uint32_t* abgr = (uint32_t*)&data[color0Offset];
					abgr[0] = 0xff000000;
					abgr[0] |= uint8_t( (ii%37)/37.0f*255.0f)<<16;
					abgr[0] |= uint8_t( (ii%59)/59.0f*255.0f)<<8;
					abgr[0] |= uint8_t( (ii%79)/79.0f*255.0f);
				}

				if (NULL != normals)
				{
					float* nxyz = (float*)&data[normalOffset];
					nxyz[0] = normals[0];
					nxyz[1] = normals[1];
					nxyz[2] = normals[2];
					normals += 3;
				}

				data += stride;
			}

			m_vbh = bgfx::createVertexBuffer(mem, m_decl);
		}

		// Allocated static index buffer and fill with indices.
		{
			CTMuint numTriangles = ctmGetInteger(ctm, CTM_TRIANGLE_COUNT);
			const CTMuint* indices = ctmGetIntegerArray(ctm, CTM_INDICES);
			const bgfx::Memory* mem = bgfx::alloc(numTriangles*3*sizeof(uint16_t) );
			uint16_t* data = (uint16_t*)mem->data;
			for (uint32_t ii = 0, num = numTriangles * 3; ii < num; ++ii)
			{
				data[ii] = (uint16_t)indices[ii];
			}

			m_ibh = bgfx::createIndexBuffer(mem);
		}

		ctmFreeContext(ctm);
	}

	void setup()
	{
		bgfx::setIndexBuffer(m_ibh);
		bgfx::setVertexBuffer(m_vbh);
	}

	bgfx::VertexDecl m_decl;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
};

int _main_(int _argc, char** _argv)
{
	bgfx::init(BX_PLATFORM_WINDOWS, fatalCb);
	bgfx::reset(1280, 720);

	// Enable debug text.
	bgfx::setDebug(BGFX_DEBUG_TEXT);

	// Set view 0 default viewport.
	bgfx::setViewRect(0, 0, 0, 1280, 720);

	// Set view 1 default viewport.
	bgfx::setViewRect(1, 0, 0, 1280, 720);

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
	case bgfx::RendererType::Null:
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

	bgfx::UniformHandle u_time = bgfx::createUniform("u_time", bgfx::ConstantType::Uniform1f);

	bgfx::ProgramHandle program = loadProgram("vs_mesh", "fs_mesh");

	Mesh mesh;
	mesh.load("meshes/bunny.ctm");

	while (true)
	{
		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::submit(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;
		float time = (float)(bx::getHPCounter()/double(bx::getHPFrequency() ) );
		bgfx::setUniform(u_time, &time);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/04-mesh");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Loading OpenCTM meshes.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		float at[3] = { 0.0f, 1.0f, 0.0f };
		float eye[3] = { 0.0f, 1.0f, -2.5f };

		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);
		mtxProj(proj, 60.0f, 16.0f/9.0f, 0.1f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		float mtx[16];
		mtxRotateXY(mtx
			, 0.0f
			, time*0.37f
			); 

		// Set model matrix for rendering.
		bgfx::setTransform(mtx);

		bgfx::setProgram(program);

		mesh.setup();

		// Set render states.
		bgfx::setState(BGFX_STATE_RGB_WRITE
			|BGFX_STATE_DEPTH_WRITE
			|BGFX_STATE_DEPTH_TEST_LESS
			);

		// Submit primitive for rendering to view 0.
		bgfx::submit(0);

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	bgfx::destroyProgram(program);

	bgfx::destroyUniform(u_time);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
