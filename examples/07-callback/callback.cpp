/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include "bgfx_utils.h"

#include <bx/allocator.h>
#include <bx/string.h>
#include "aviwriter.h"

#include <inttypes.h>

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

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

void saveTga(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip)
{
	FILE* file = fopen(_filePath, "wb");
	if (NULL != file)
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

long int fsize(FILE* _file)
{
	long int pos = ftell(_file);
	fseek(_file, 0L, SEEK_END);
	long int size = ftell(_file);
	fseek(_file, pos, SEEK_SET);
	return size;
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

	virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) BX_OVERRIDE
	{
		dbgPrintf("%s (%d): ", _filePath, _line);
		dbgPrintfVargs(_format, _argList);
	}

	virtual uint32_t cacheReadSize(uint64_t _id) BX_OVERRIDE
	{
		char filePath[256];
		bx::snprintf(filePath, sizeof(filePath), "temp/%016" PRIx64, _id);

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
		char temp[1024];

		// Save screen shot as TGA.
		bx::snprintf(temp, BX_COUNTOF(temp), "%s.mip0.tga", _filePath);
		saveTga(temp, _width, _height, _pitch, _data, false, _yflip);

		uint32_t width = _width;
		uint32_t height = _height;
		uint32_t pitch = _pitch;

		uint8_t* data = (uint8_t*)_data;

		// Generate mip maps.
		uint32_t mip = 1;
		for (; 2 <= width && 2 <= height; ++mip)
		{
			bx::snprintf(temp, BX_COUNTOF(temp), "%s.mip%d.tga", _filePath, mip);
			bgfx::imageRgba8Downsample2x2(width, height, pitch, data, data);

			width >>= 1;
			height >>= 1;
			pitch = width*4;

			saveTga(temp, width, height, pitch, _data, false, _yflip);
		}

		if (width > height)
		{
			for (; 2 <= width; ++mip)
			{
				memcpy(&data[width*4], data, width*4);

				bx::snprintf(temp, BX_COUNTOF(temp), "%s.mip%d.tga", _filePath, mip);
				bgfx::imageRgba8Downsample2x2(width, 2, pitch, data, data);

				width >>= 1;
				pitch = width*4;

				saveTga(temp, width, 2, pitch, _data, false, _yflip);
			}
		}
		else
		{
			for (; 2 <= height; ++mip)
			{
				uint32_t* src = (uint32_t*)data;
				for (uint32_t ii = 0; ii < height; ++ii, src += 2)
				{
					src[1] = src[0];
				}

				bx::snprintf(temp, BX_COUNTOF(temp), "%s.mip%d.tga", _filePath, mip);
				bgfx::imageRgba8Downsample2x2(2, height, 8, data, data);

				height >>= 1;

				saveTga(temp, 2, height, 8, _data, false, _yflip);
			}
		}
	}

	virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t /*_pitch*/, bgfx::TextureFormat::Enum /*_format*/, bool _yflip) BX_OVERRIDE
	{
		m_writer = new AviWriter(entry::getFileWriter() );
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

class BgfxAllocator : public bx::ReallocatorI
{
public:
	BgfxAllocator()
		: m_numBlocks(0)
		, m_maxBlocks(0)
	{
	}

	virtual ~BgfxAllocator()
	{
	}

	virtual void* alloc(size_t _size, size_t _align, const char* _file, uint32_t _line) BX_OVERRIDE
	{
		if (BX_CONFIG_ALLOCATOR_NATURAL_ALIGNMENT >= _align)
		{
			void* ptr = ::malloc(_size);
			dbgPrintf("%s(%d): ALLOC %p of %d byte(s)\n", _file, _line, ptr, _size);
			++m_numBlocks;
			m_maxBlocks = bx::uint32_max(m_maxBlocks, m_numBlocks);
			return ptr;
		}

		return bx::alignedAlloc(this, _size, _align, _file, _line);
	}

	virtual void free(void* _ptr, size_t _align, const char* _file, uint32_t _line) BX_OVERRIDE
	{
		if (NULL != _ptr)
		{
			if (BX_CONFIG_ALLOCATOR_NATURAL_ALIGNMENT >= _align)
			{
				dbgPrintf("%s(%d): FREE %p\n", _file, _line, _ptr);
				::free(_ptr);
				--m_numBlocks;
			}
			else
			{
				bx::alignedFree(this, _ptr, _align, _file, _line);
			}
		}
	}

	virtual void* realloc(void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line) BX_OVERRIDE
	{
		if (BX_CONFIG_ALLOCATOR_NATURAL_ALIGNMENT >= _align)
		{
			void* ptr = ::realloc(_ptr, _size);
			dbgPrintf("%s(%d): REALLOC %p (old %p) of %d byte(s)\n", _file, _line, ptr, _ptr, _size);

			if (NULL == _ptr)
			{
				++m_numBlocks;
				m_maxBlocks = bx::uint32_max(m_maxBlocks, m_numBlocks);
			}

			return ptr;
		}

		return bx::alignedRealloc(this, _ptr, _size, _align, _file, _line);
	}

	void dumpStats() const
	{
		dbgPrintf("Allocator stats: num blocks %d (peak: %d)\n", m_numBlocks, m_maxBlocks);
	}

private:
	uint32_t m_numBlocks;
	uint32_t m_maxBlocks;
};

int _main_(int _argc, char** _argv)
{
	Args args(_argc, _argv);

	BgfxCallback callback;
	BgfxAllocator allocator;

	uint32_t width = 1280;
	uint32_t height = 720;

	// Enumerate supported backend renderers.
	bgfx::RendererType::Enum renderers[bgfx::RendererType::Count];
	uint8_t numRenderers = bgfx::getSupportedRenderers(renderers);

	bgfx::init(bgfx::RendererType::Count == args.m_type
		? renderers[bx::getHPCounter() % numRenderers] /* randomize renderer */
		: args.m_type
		, args.m_pciId
		, 0
		, &callback  // custom callback handler
		, &allocator // custom allocator
		);
	bgfx::reset(width, height, BGFX_RESET_CAPTURE|BGFX_RESET_MSAA_X16);

	// Enable debug text.
	bgfx::setDebug(BGFX_DEBUG_TEXT);

	// Set view 0 default viewport.
	bgfx::setViewRect(0, 0, 0, 1280, 720);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	// Create vertex stream declaration.
	PosColorVertex::init();

	// Create static vertex buffer.
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
		  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
		, PosColorVertex::ms_decl
		);

	// Create static index buffer.
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

	// Create program from shaders.
	bgfx::ProgramHandle program = loadProgram("vs_callback", "fs_callback");

	float time = 0.0f;

	const bgfx::RendererType::Enum rendererType = bgfx::getRendererType();

	// 5 second 60Hz video
	for (uint32_t frame = 0; frame < 300; ++frame)
	{
		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

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

		bgfx::dbgTextPrintf( 2, 6, 0x0e, "Supported renderers:");
		for (uint8_t ii = 0; ii < numRenderers; ++ii)
		{
			bgfx::dbgTextPrintf( 2, 7+ii, 0x0c, "[%c] %s"
				, renderers[ii] == rendererType ? '\xfe' : ' '
				, bgfx::getRendererName(renderers[ii])
				);
		}

		float at[3] = { 0.0f, 0.0f, 0.0f };
		float eye[3] = { 0.0f, 0.0f, -35.0f };

		float view[16];
		float proj[16];
		bx::mtxLookAt(view, eye, at);
		bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(0, view, proj);

		time += 1.0f/60.0f;

		// Submit 11x11 cubes.
		for (uint32_t yy = 0; yy < 11; ++yy)
		{
			for (uint32_t xx = 0; xx < 11-yy; ++xx)
			{
				float mtx[16];
				bx::mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
				mtx[12] = -15.0f + float(xx)*3.0f;
				mtx[13] = -15.0f + float(yy)*3.0f;
				mtx[14] = 0.0f;

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(vbh);
				bgfx::setIndexBuffer(ibh);

				// Set render states.
				bgfx::setState(BGFX_STATE_DEFAULT);

				// Submit primitive for rendering to view 0.
				bgfx::submit(0, program);
			}
		}

		// Take screen shot at frame 150.
		if (150 == frame)
		{
			bgfx::saveScreenShot("temp/frame150");
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

	allocator.dumpStats();

	return 0;
}
