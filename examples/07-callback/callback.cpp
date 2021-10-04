/*
 * Copyright 2011-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

#include <bx/allocator.h>
#include <bx/file.h>
#include <bx/string.h>

#include "aviwriter.h"

#include <inttypes.h>

#include <bimg/bimg.h>

namespace
{

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorVertex::ms_layout;

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

void savePng(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bimg::TextureFormat::Enum _format, bool _yflip)
{
	bx::FileWriter writer;
	bx::Error err;
	if (bx::open(&writer, _filePath, false, &err) )
	{
		bimg::imageWritePng(&writer, _width, _height, _srcPitch, _src, _format, _yflip, &err);
		bx::close(&writer);
	}
}

void saveTga(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _srcPitch, const void* _src, bool _grayscale, bool _yflip)
{
	bx::FileWriter writer;
	bx::Error err;
	if (bx::open(&writer, _filePath, false, &err) )
	{
		bimg::imageWriteTga(&writer, _width, _height, _srcPitch, _src, _grayscale, _yflip, &err);
		bx::close(&writer);
	}
}

struct BgfxCallback : public bgfx::CallbackI
{
	virtual ~BgfxCallback()
	{
	}

	virtual void fatal(const char* _filePath, uint16_t _line, bgfx::Fatal::Enum _code, const char* _str) override
	{
		BX_UNUSED(_filePath, _line);

		// Something unexpected happened, inform user and bail out.
		bx::debugPrintf("Fatal error: 0x%08x: %s", _code, _str);

		// Must terminate, continuing will cause crash anyway.
		abort();
	}

	virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) override
	{
		bx::debugPrintf("%s (%d): ", _filePath, _line);
		bx::debugPrintfVargs(_format, _argList);
	}

	virtual void profilerBegin(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
	{
	}

	virtual void profilerBeginLiteral(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
	{
	}

	virtual void profilerEnd() override
	{
	}

	virtual uint32_t cacheReadSize(uint64_t _id) override
	{
		char filePath[256];
		bx::snprintf(filePath, sizeof(filePath), "temp/%016" PRIx64, _id);

		// Use cache id as filename.
		bx::FileReaderI* reader = entry::getFileReader();
		bx::Error err;
		if (bx::open(reader, filePath, &err) )
		{
			uint32_t size = (uint32_t)bx::getSize(reader);
			bx::close(reader);
			// Return size of shader file.
			return size;
		}

		// Return 0 if shader is not found.
		return 0;
	}

	virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) override
	{
		char filePath[256];
		bx::snprintf(filePath, sizeof(filePath), "temp/%016" PRIx64, _id);

		// Use cache id as filename.
		bx::FileReaderI* reader = entry::getFileReader();
		bx::Error err;
		if (bx::open(reader, filePath, &err) )
		{
			// Read shader.
			uint32_t result = bx::read(reader, _data, _size, &err);
			bx::close(reader);

			// Make sure that read size matches requested size.
			return result == _size;
		}

		// Shader is not found in cache, needs to be rebuilt.
		return false;
	}

	virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) override
	{
		char filePath[256];
		bx::snprintf(filePath, sizeof(filePath), "temp/%016" PRIx64, _id);

		// Use cache id as filename.
		bx::FileWriterI* writer = entry::getFileWriter();
		bx::Error err;
		if (bx::open(writer, filePath, false, &err) )
		{
			// Write shader to cache location.
			bx::write(writer, _data, _size, &err);
			bx::close(writer);
		}
	}

	virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t /*_size*/, bool _yflip) override
	{
		char temp[1024];

		// Save screen shot as PNG.
		bx::snprintf(temp, BX_COUNTOF(temp), "%s.png", _filePath);
		savePng(temp, _width, _height, _pitch, _data, bimg::TextureFormat::BGRA8, _yflip);

		// Save screen shot as TGA.
		bx::snprintf(temp, BX_COUNTOF(temp), "%s.tga", _filePath);
		saveTga(temp, _width, _height, _pitch, _data, false, _yflip);
	}

	virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t /*_pitch*/, bgfx::TextureFormat::Enum /*_format*/, bool _yflip) override
	{
		m_writer = BX_NEW(entry::getAllocator(), AviWriter)(entry::getFileWriter() );
		if (!m_writer->open("temp/capture.avi", _width, _height, 60, _yflip) )
		{
			BX_DELETE(entry::getAllocator(), m_writer);
			m_writer = NULL;
		}
	}

	virtual void captureEnd() override
	{
		if (NULL != m_writer)
		{
			m_writer->close();
			BX_DELETE(entry::getAllocator(), m_writer);
			m_writer = NULL;
		}
	}

	virtual void captureFrame(const void* _data, uint32_t /*_size*/) override
	{
		if (NULL != m_writer)
		{
			m_writer->frame(_data);
		}
	}

	AviWriter* m_writer;
};

const size_t kNaturalAlignment = 8;

class BgfxAllocator : public bx::AllocatorI
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

	virtual void* realloc(void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line) override
	{
		if (0 == _size)
		{
			if (NULL != _ptr)
			{
				if (kNaturalAlignment >= _align)
				{
					bx::debugPrintf("%s(%d): FREE %p\n", _file, _line, _ptr);
					::free(_ptr);
					--m_numBlocks;
				}
				else
				{
					bx::alignedFree(this, _ptr, _align, _file, _line);
				}
			}

			return NULL;
		}
		else if (NULL == _ptr)
		{
			if (kNaturalAlignment >= _align)
			{
				void* ptr = ::malloc(_size);
				bx::debugPrintf("%s(%d): ALLOC %p of %d byte(s)\n", _file, _line, ptr, _size);
				++m_numBlocks;
				m_maxBlocks = bx::uint32_max(m_maxBlocks, m_numBlocks);
				return ptr;
			}

			return bx::alignedAlloc(this, _size, _align, _file, _line);
		}

		if (kNaturalAlignment >= _align)
		{
			void* ptr = ::realloc(_ptr, _size);
			bx::debugPrintf("%s(%d): REALLOC %p (old %p) of %d byte(s)\n", _file, _line, ptr, _ptr, _size);

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
		bx::debugPrintf("Allocator stats: num blocks %d (peak: %d)\n", m_numBlocks, m_maxBlocks);
	}

private:
	uint32_t m_numBlocks;
	uint32_t m_maxBlocks;
};

class ExampleCallback : public entry::AppI
{
public:
	ExampleCallback(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
		m_reset  = 0
			| BGFX_RESET_VSYNC
			| BGFX_RESET_CAPTURE
			| BGFX_RESET_MSAA_X16
			;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		init.callback  = &m_callback;  // custom callback handler
		init.allocator = &m_allocator; // custom allocator
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

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
		m_vbh = bgfx::createVertexBuffer(
			  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
			, PosColorVertex::ms_layout
			);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

		// Create program from shaders.
		m_program = loadProgram("vs_callback", "fs_callback");

		m_time  = 0.0f;
		m_frame = 0;

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		// Cleanup.
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);

		// Shutdown bgfx.
		bgfx::shutdown();

		m_allocator.dumpStats();

		return 0;
	}

	bool update() override
	{
		bool exit = false;

		// 5 second 60Hz video
		if (m_frame < 300)
		{
			++m_frame;
		}
		else
		{
			m_reset &= ~BGFX_RESET_CAPTURE;

			exit = entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState);

			imguiBeginFrame(m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this);

			imguiEndFrame();
		}

		if (!exit)
		{
			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -35.0f };

			float view[16];
			float proj[16];
			bx::mtxLookAt(view, eye, at);
			bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

			// Set view and projection matrix for view 0.
			bgfx::setViewTransform(0, view, proj);

			m_time += 1.0f/60.0f;

			// Submit 11x11 cubes.
			for (uint32_t yy = 0; yy < 11; ++yy)
			{
				for (uint32_t xx = 0; xx < 11-yy; ++xx)
				{
					float mtx[16];
					bx::mtxRotateXY(mtx, m_time + xx*0.21f, m_time + yy*0.37f);
					mtx[12] = -15.0f + float(xx)*3.0f;
					mtx[13] = -15.0f + float(yy)*3.0f;
					mtx[14] = 0.0f;

					// Set model matrix for rendering.
					bgfx::setTransform(mtx);

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(0, m_vbh);
					bgfx::setIndexBuffer(m_ibh);

					// Set render states.
					bgfx::setState(BGFX_STATE_DEFAULT);

					// Submit primitive for rendering to view 0.
					bgfx::submit(0, m_program);
				}
			}

			// Take screen shot at frame 150.
			if (150 == m_frame)
			{
				bgfx::FrameBufferHandle fbh = BGFX_INVALID_HANDLE;
				bgfx::requestScreenShot(fbh, "temp/frame150");
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	BgfxCallback  m_callback;
	BgfxAllocator m_allocator;

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::ProgramHandle m_program;
	float m_time;
	uint32_t m_frame;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleCallback
	, "07-callback"
	, "Implementing application specific callbacks for taking screen shots, caching OpenGL binary shaders, and video capture."
	, "https://bkaradzic.github.io/bgfx/examples.html#callback"
	);
