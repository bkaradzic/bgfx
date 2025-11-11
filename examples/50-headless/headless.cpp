/*
 * Copyright 2011-2025 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include <entry/entry.h>
#include <bgfx_utils.h>
#include <bx/timer.h>
#include <bx/file.h>

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

static PosColorVertex s_cubeVertices[] =
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

static const uint16_t s_cubeTriList[] =
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

int _main_(int _argc, char** _argv)
{
	bx::printf(
		"\n"
		"\n"
		"\tThis example demonstrates headless initialization.\n"
		"\n"
		);

	Args args(_argc, _argv);

	bgfx::Init init;
	init.type     = args.m_type;
	init.vendorId = args.m_pciId;
	init.resolution.width  = 0;
	init.resolution.height = 0;

	if (!bgfx::init(init) )
	{
		bx::printf(
			"\t - Failed to initialize headless mode!\n"
			"\n"
			);
		return bx::kExitFailure;
	}

	bx::printf(
		"\t - Headless mode initialized successfuly!\n"
		"\n"
		);

	constexpr uint32_t kWidth  = 1280;
	constexpr uint32_t kHeight = 720;

	// Create vertex stream declaration.
	PosColorVertex::init();

	// Create static vertex buffer.
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
		// Static data can be passed with bgfx::makeRef
		  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
		, PosColorVertex::ms_layout
		);

	// Create static index buffer for triangle list rendering.
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(
		// Static data can be passed with bgfx::makeRef
		bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList) )
		);

	bgfx::ProgramHandle program = loadProgram("vs_cubes", "fs_cubes");

	bgfx::FrameBufferHandle fbh = bgfx::createFrameBuffer(
		  kWidth
		, kHeight
		, bgfx::TextureFormat::BGRA8
		);

	bgfx::TextureHandle rb = bgfx::createTexture2D(
		  kWidth
		, kHeight
		, false
		, 1
		, bgfx::TextureFormat::BGRA8
		, BGFX_TEXTURE_BLIT_DST|BGFX_TEXTURE_READ_BACK
		);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	constexpr uint64_t state = 0
		| BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_WRITE_Z
		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CW
		| BGFX_STATE_MSAA
		;

	const uint64_t timeOffset = bx::getHPCounter();

	uint32_t currentFrame = 0;

	bx::printf(
		"\t - Rendering into offscreen framebuffer.\n"
		"\n"
		);

	for (uint32_t ii = 0; ii < 5; ++ii)
	{
		const float time = (float)( (bx::getHPCounter()-timeOffset)/double(bx::getHPFrequency() ) );

		const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f, -35.0f };

		// Set view and projection matrix for view 0.
		{
			float view[16];
			bx::mtxLookAt(view, eye, at);

			float proj[16];
			bx::mtxProj(proj, 60.0f, float(kWidth)/float(kHeight), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(kWidth), uint16_t(kHeight) );
			bgfx::setViewFrameBuffer(0, fbh);
		}

		// Submit 11x11 cubes.
		for (uint32_t yy = 0; yy < 11; ++yy)
		{
			for (uint32_t xx = 0; xx < 11; ++xx)
			{
				float mtx[16];
				bx::mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
				mtx[12] = -15.0f + float(xx)*3.0f;
				mtx[13] = -15.0f + float(yy)*3.0f;
				mtx[14] = 0.0f;

				// Set model matrix for rendering.
				bgfx::setTransform(mtx);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(0, vbh);
				bgfx::setIndexBuffer(ibh);

				// Set render states.
				bgfx::setState(state);

				// Submit primitive for rendering to view 0.
				bgfx::submit(0, program);
			}
		}

		bgfx::blit(1, rb, 0, 0, bgfx::getTexture(fbh) );

		currentFrame = bgfx::frame();
	}

	bx::FilePath filePath(bx::Dir::Current);
	filePath.join("temp/headless.tga");

	bx::FileWriter writer;
	bx::Error err;
	if (bx::open(&writer, filePath, false, &err) )
	{
		bx::DefaultAllocator allocator;

		uint8_t* data = (uint8_t*)bx::alloc(&allocator, kWidth*kHeight*4);

		uint32_t expectedFrame = bgfx::readTexture(rb, data);

		while (currentFrame < expectedFrame) // Make sure read texture is complete.
		{
			currentFrame = bgfx::frame();
		}

		bimg::imageWriteTga(&writer, kWidth, kHeight, kWidth*4, data, false, false, &err);
		bx::close(&writer);

		bx::free(&allocator, data);
	}

	bx::printf(
		"\t - Screenshot written into:\n"
		"\t   %s\n"
		"\n"
		"\t - Shuting it down!\n"
		"\n"
		, filePath.getCPtr()
		);

	bgfx::destroy(rb);
	bgfx::destroy(fbh);
	bgfx::destroy(program);
	bgfx::destroy(ibh);
	bgfx::destroy(vbh);

	bgfx::shutdown();

	bx::printf(
		"\t - Exiting.\n"
		"\n"
		"\n"
		);

	return bx::kExitSuccess;
}
