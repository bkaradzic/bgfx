/*
 * Copyright 2011-2013 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <bgfx.h>
#include <bx/bx.h>
#include <bx/timer.h>
#include <bx/readerwriter.h>
#include <bx/string.h>
#include "../common/dbg.h"
#include "../common/math.h"
#include "../common/aviwriter.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
};

static bgfx::VertexDecl s_PosColorDecl;

static PosColorVertex s_cubeVertices[8] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeIndices[36] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
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

void saveTga(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip)
{
	FILE* file = fopen(_filePath, "wb");
	if ( NULL != file )
	{
		uint8_t type = _grayscale ? 3 : 2;
		uint8_t bpp = _grayscale ? 8 : 32;

		putc(0, file);
		putc(0, file);
		putc(type, file);
		putc(0, file); 
		putc(0, file);
		putc(0, file); 
		putc(0, file);
		putc(0, file);
		putc(0, file); 
		putc(0, file);
		putc(0, file); 
		putc(0, file);
		putc(_width&0xff, file);
		putc( (_width>>8)&0xff, file);
		putc(_height&0xff, file);
		putc( (_height>>8)&0xff, file);
		putc(bpp, file);
		putc(32, file);

		uint32_t dstPitch = _width*bpp/8;
		if (_yflip)
		{
			uint8_t* data = (uint8_t*)_src + _srcPitch*_height - _srcPitch;
			for (uint32_t yy = 0; yy < _height; ++yy)
			{
				fwrite(data, dstPitch, 1, file);
				data -= _srcPitch;
			}
		}
		else
		{
			uint8_t* data = (uint8_t*)_src;
			for (uint32_t yy = 0; yy < _height; ++yy)
			{
				fwrite(data, dstPitch, 1, file);
				data += _srcPitch;
			}
		}

		fclose(file);
	}
}

struct BgfxCallback : public bgfx::CallbackI
{
	virtual ~BgfxCallback()
	{
	}

	virtual void fatal(bgfx::Fatal::Enum _code, const char* _str) BX_OVERRIDE
	{
		// Something unexpected happened, inform user and bail out.
		dbgPrintf("Fatal error: 0x%08x: %s", _code, _str);

		// Must terminate, continuing will cause crash anyway.
		abort();
	}

	virtual uint32_t cacheReadSize(uint64_t _id) BX_OVERRIDE
	{
		char filePath[256];
		bx::snprintf(filePath, sizeof(filePath), "%016" PRIx64, _id);

		// Use cache id as filename.
		FILE* file = fopen(filePath, "rb");
		if (NULL != file)
		{
			uint32_t size = fsize(file);
			fclose(file);
			// Return size of shader file.
			return size;
		}

		// Return 0 if shader is not found.
		return 0;
	}

	virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) BX_OVERRIDE
	{
		char filePath[256];
		bx::snprintf(filePath, sizeof(filePath), "temp/%016" PRIx64, _id);

		// Use cache id as filename.
		FILE* file = fopen(filePath, "rb");
		if (NULL != file)
		{
			// Read shader.
			size_t result = fread(_data, 1, _size, file);
			fclose(file);

			// Make sure that read size matches requested size.
			return result == _size;
		}

		// Shader is not found in cache, needs to be rebuilt.
		return false;
	}

	virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) BX_OVERRIDE
	{
		char filePath[256];
		bx::snprintf(filePath, sizeof(filePath), "temp/%016" PRIx64, _id);

		// Use cache id as filename.
		FILE* file = fopen(filePath, "wb");
		if (NULL != file)
		{
			// Write shader to cache location.
			fwrite(_data, 1, _size, file);
			fclose(file);
		}
	}

	virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t /*_size*/, bool _yflip) BX_OVERRIDE
	{
		// Save screen shot as TGA.
		saveTga(_filePath, _width, _height, _pitch, _data, false, _yflip);
	}

	virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t /*_pitch*/, bgfx::TextureFormat::Enum /*_format*/, bool _yflip) BX_OVERRIDE
	{
		m_writer = new AviWriter;
		if (!m_writer->open("temp/capture.avi", _width, _height, 60, _yflip) )
		{
			delete m_writer;
			m_writer = NULL;
		}
	}

	virtual void captureEnd() BX_OVERRIDE
	{
		if (NULL != m_writer)
		{
			m_writer->close();
			delete m_writer;
			m_writer = NULL;
		}
	}

	virtual void captureFrame(const void* _data, uint32_t /*_size*/) BX_OVERRIDE
	{
		if (NULL != m_writer)
		{
			m_writer->frame(_data);
		}
	}

	AviWriter* m_writer;
};

int _main_(int /*_argc*/, char** /*_argv*/)
{
	BgfxCallback callback;

	bgfx::init(&callback);
	bgfx::reset(1280, 720, BGFX_RESET_CAPTURE);

	// Enable debug text.
	bgfx::setDebug(BGFX_DEBUG_TEXT);

	// Set view 0 default viewport.
	bgfx::setViewRect(0, 0, 0, 1280, 720);

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
	s_PosColorDecl.begin();
	s_PosColorDecl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
	s_PosColorDecl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
	s_PosColorDecl.end();

	const bgfx::Memory* mem;

	// Create static vertex buffer.
	mem = bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) );
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(mem, s_PosColorDecl);

	// Create static index buffer.
	mem = bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) );
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(mem);

	// Load vertex shader.
	mem = loadShader("vs_callback");
	bgfx::VertexShaderHandle vsh = bgfx::createVertexShader(mem);

	// Load fragment shader.
	mem = loadShader("fs_callback");
	bgfx::FragmentShaderHandle fsh = bgfx::createFragmentShader(mem);

	// Create program from shaders.
	bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh);

	// We can destroy vertex and fragment shader here since
	// their reference is kept inside bgfx after calling createProgram.
	// Vertex and fragment shader will be destroyed once program is
	// destroyed.
	bgfx::destroyVertexShader(vsh);
	bgfx::destroyFragmentShader(fsh);

	float time = 0.0f;

	// 5 second 60Hz video
	for (uint32_t frame = 0; frame < 300; ++frame)
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

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf( 0, 1, 0x4f, "bgfx/examples/07-callback");
		bgfx::dbgTextPrintf( 0, 2, 0x6f, "Description: Implementing application specific callbacks for taking screen shots,");
		bgfx::dbgTextPrintf(13, 3, 0x6f, "caching OpenGL binary shaders, and video capture.");
		bgfx::dbgTextPrintf( 0, 4, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		float at[3] = { 0.0f, 0.0f, 0.0f };
		float eye[3] = { 0.0f, 0.0f, -35.0f };
		
		float view[16];
		float proj[16];
		mtxLookAt(view, eye, at);
		mtxProj(proj, 60.0f, 16.0f/9.0f, 0.1f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		time += 1.0f/60.0f;

		// Submit 11x11 cubes.
		for (uint32_t yy = 0; yy < 11; ++yy)
		{
			for (uint32_t xx = 0; xx < 11-yy; ++xx)
			{
				float mtx[16];
				mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
				mtx[12] = -15.0f + float(xx)*3.0f;
				mtx[13] = -15.0f + float(yy)*3.0f;
				mtx[14] = 0.0f;

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and fragment shaders.
				bgfx::setProgram(program);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(vbh);
				bgfx::setIndexBuffer(ibh);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 0.
				bgfx::submit(0);
			}
		}

		// Take screen shot at frame 150.
		if (150 == frame)
		{
			bgfx::saveScreenShot("temp/frame150.tga");
		}

		// Advance to next frame. Rendering thread will be kicked to 
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(program);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
