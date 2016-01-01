/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

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
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

struct PosColorTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_rgba;
	float m_u;
	float m_v;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position,  3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorTexCoord0Vertex::ms_decl;

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

static float s_texelHalf = 0.0f;
static bool s_flipV = false;

inline void mtxProj(float* _result, float _fovy, float _aspect, float _near, float _far)
{
	bx::mtxProj(_result, _fovy, _aspect, _near, _far, s_flipV);
}

void screenSpaceQuad(float _textureWidth, float _textureHeight, bool _originBottomLeft = false, float _width = 1.0f, float _height = 1.0f)
{
	if (bgfx::checkAvailTransientVertexBuffer(3, PosColorTexCoord0Vertex::ms_decl) )
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosColorTexCoord0Vertex::ms_decl);
		PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)vb.data;

		const float zz = 0.0f;

		const float minx = -_width;
		const float maxx =  _width;
		const float miny = 0.0f;
		const float maxy = _height*2.0f;

		const float texelHalfW = s_texelHalf/_textureWidth;
		const float texelHalfH = s_texelHalf/_textureHeight;
		const float minu = -1.0f + texelHalfW;
		const float maxu =  1.0f + texelHalfW;

		float minv = texelHalfH;
		float maxv = 2.0f + texelHalfH;

		if (_originBottomLeft)
		{
			float tmp = minv;
			minv = maxv;
			maxv = tmp;

			minv -= 1.0f;
			maxv -= 1.0f;
		}

		vertex[0].m_x = minx;
		vertex[0].m_y = miny;
		vertex[0].m_z = zz;
		vertex[0].m_rgba = 0xffffffff;
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = zz;
		vertex[1].m_rgba = 0xffffffff;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = zz;
		vertex[2].m_rgba = 0xffffffff;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		bgfx::setVertexBuffer(&vb);
	}
}

int _main_(int _argc, char** _argv)
{
	Args args(_argc, _argv);

	uint32_t width = 1280;
	uint32_t height = 720;
	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::init(args.m_type, args.m_pciId);
	bgfx::reset(width, height, reset);

	// Create vertex stream declaration.
	PosColorVertex::init();
	PosColorTexCoord0Vertex::init();

	// Enable debug text.
	bgfx::setDebug(debug);

	// Get renderer capabilities info.
	const bgfx::Caps* caps = bgfx::getCaps();

	// Setup root path for binary shaders. Shader binaries are different
	// for each renderer.
	switch (caps->rendererType)
	{
	default:
		break;

	case bgfx::RendererType::OpenGL:
	case bgfx::RendererType::OpenGLES:
		s_flipV = true;
		break;
	}

	// Imgui.
	imguiCreate();

	const bgfx::Memory* mem;

	// Create static vertex buffer.
	mem = bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) );
	bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(mem, PosColorVertex::ms_decl);

	// Create static index buffer.
	mem = bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) );
	bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(mem);

	// Create texture sampler uniforms.
	bgfx::UniformHandle s_texColor0 = bgfx::createUniform("s_texColor0", bgfx::UniformType::Int1);
	bgfx::UniformHandle s_texColor1 = bgfx::createUniform("s_texColor1", bgfx::UniformType::Int1);
	bgfx::UniformHandle u_color     = bgfx::createUniform("u_color",     bgfx::UniformType::Vec4);

	bgfx::ProgramHandle blend          = loadProgram("vs_oit",      "fs_oit"                  );
	bgfx::ProgramHandle wbSeparatePass = loadProgram("vs_oit",      "fs_oit_wb_separate"      );
	bgfx::ProgramHandle wbSeparateBlit = loadProgram("vs_oit_blit", "fs_oit_wb_separate_blit" );
	bgfx::ProgramHandle wbPass         = loadProgram("vs_oit",      "fs_oit_wb"               );
	bgfx::ProgramHandle wbBlit         = loadProgram("vs_oit_blit", "fs_oit_wb_blit"          );

	bgfx::TextureHandle fbtextures[2] = { BGFX_INVALID_HANDLE, BGFX_INVALID_HANDLE };
	bgfx::FrameBufferHandle fbh = BGFX_INVALID_HANDLE;

	int64_t timeOffset = bx::getHPCounter();

	uint32_t mode = 1;
	int32_t scrollArea = 0;
	bool frontToBack = true;
	bool fadeInOut = false;

	uint32_t oldWidth = 0;
	uint32_t oldHeight = 0;
	uint32_t oldReset = reset;

	entry::MouseState mouseState;
	while (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		if (oldWidth  != width
		||  oldHeight != height
		||  oldReset  != reset
		||  !bgfx::isValid(fbh) )
		{
			// Recreate variable size render targets when resolution changes.
			oldWidth  = width;
			oldHeight = height;
			oldReset  = reset;

			if (bgfx::isValid(fbh) )
			{
				bgfx::destroyFrameBuffer(fbh);
			}

			fbtextures[0] = bgfx::createTexture2D(width, height, 1, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_RT);
			fbtextures[1] = bgfx::createTexture2D(width, height, 1, bgfx::TextureFormat::R16F,    BGFX_TEXTURE_RT);
			fbh = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
		}

		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
			, mouseState.m_mz
			, width
			, height
			);

		imguiBeginScrollArea("Settings", width - width / 4 - 10, 10, width / 4, height / 3, &scrollArea);
		imguiSeparatorLine();

		imguiLabel("Blend mode:");

		mode = imguiChoose(mode
			, "None"
			, "Separate"
			, "MRT Independent"
			);

		imguiSeparatorLine();

		if (imguiCheck("Front to back", frontToBack) )
		{
			frontToBack ^= true;
		}

		if (imguiCheck("Fade in/out", fadeInOut) )
		{
			fadeInOut ^= true;
		}

		imguiEndScrollArea();
		imguiEndFrame();

		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);
		bgfx::setViewRect(1, 0, 0, width, height);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		float time = (float)( (now-timeOffset)/freq);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		// Reference:
		// Weighted, Blended Order-Independent Transparency
		// http://jcgt.org/published/0002/02/09/
		// http://casual-effects.blogspot.com/2014/03/weighted-blended-order-independent.html
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/19-oit");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Weighted, Blended Order Independent Transparency.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		float at[3] = { 0.0f, 0.0f, 0.0f };
		float eye[3] = { 0.0f, 0.0f, -7.0f };

		float view[16];
		float proj[16];

		// Set view and projection matrix for view 0.
		bx::mtxLookAt(view, eye, at);
		mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		bgfx::setViewTransform(0, view, proj);

		// Set palette color for index 0
		bgfx::setPaletteColor(0, 0.0f, 0.0f, 0.0f, 0.0f);

		// Set palette color for index 1
		bgfx::setPaletteColor(1, 1.0f, 1.0f, 1.0f, 1.0f);

		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
			, 1.0f // Depth
			, 0    // Stencil
			, 0    // FB texture 0, color palette 0
			, 1 == mode ? 1 : 0 // FB texture 1, color palette 1
			);

		bgfx::setViewClear(1
			, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
			, 1.0f // Depth
			, 0    // Stencil
			, 0    // Color palette 0
			);

		bgfx::FrameBufferHandle invalid = BGFX_INVALID_HANDLE;
		bgfx::setViewFrameBuffer(0, 0 == mode ? invalid : fbh);

		// Set view and projection matrix for view 1.
		bx::mtxIdentity(view);
		bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);
		bgfx::setViewTransform(1, view, proj);

		for (uint32_t depth = 0; depth < 3; ++depth)
		{
			uint32_t zz = frontToBack ? 2-depth : depth;

			for (uint32_t yy = 0; yy < 3; ++yy)
			{
				for (uint32_t xx = 0; xx < 3; ++xx)
				{
					float color[4] = { xx*1.0f/3.0f, zz*1.0f/3.0f, yy*1.0f/3.0f, 0.5f };

					if (fadeInOut
					&&  zz == 1)
					{
						color[3] = sinf(time*3.0f)*0.49f+0.5f;
					}

					bgfx::setUniform(u_color, color);

					BX_UNUSED(time);
					float mtx[16];
					bx::mtxRotateXY(mtx, time*0.023f + xx*0.21f, time*0.03f + yy*0.37f);
					//mtxIdentity(mtx);
					mtx[12] = -2.5f + float(xx)*2.5f;
					mtx[13] = -2.5f + float(yy)*2.5f;
					mtx[14] = -2.5f + float(zz)*2.5f;

					// Set transform for draw call.
					bgfx::setTransform(mtx);

					// Set vertex and index buffer.
					bgfx::setVertexBuffer(vbh);
					bgfx::setIndexBuffer(ibh);

					const uint64_t state = 0
						| BGFX_STATE_CULL_CW
						| BGFX_STATE_RGB_WRITE
						| BGFX_STATE_ALPHA_WRITE
						| BGFX_STATE_DEPTH_TEST_LESS
						| BGFX_STATE_MSAA
						;

					bgfx::ProgramHandle program = BGFX_INVALID_HANDLE;
					switch (mode)
					{
						case 0:
							// Set vertex and fragment shaders.
							program = blend;

							// Set render states.
							bgfx::setState(state
								| BGFX_STATE_BLEND_ALPHA
								);
							break;

						case 1:
							// Set vertex and fragment shaders.
							program = wbSeparatePass;

							// Set render states.
							bgfx::setState(state
								| BGFX_STATE_BLEND_FUNC_SEPARATE(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ZERO, BGFX_STATE_BLEND_INV_SRC_ALPHA)
								);
							break;

						default:
							// Set vertex and fragment shaders.
							program = wbPass;

							// Set render states.
							bgfx::setState(state
								| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_ONE, BGFX_STATE_BLEND_ONE)
								| BGFX_STATE_BLEND_INDEPENDENT
								, 0
								| BGFX_STATE_BLEND_FUNC_RT_1(BGFX_STATE_BLEND_ZERO, BGFX_STATE_BLEND_SRC_COLOR)
								);
							break;
					}

					// Submit primitive for rendering to view 0.
					bgfx::submit(0, program);
				}
			}
		}

		if (0 != mode)
		{
			bgfx::setTexture(0, s_texColor0, fbtextures[0]);
			bgfx::setTexture(1, s_texColor1, fbtextures[1]);
			bgfx::setState(0
				| BGFX_STATE_RGB_WRITE
				| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_INV_SRC_ALPHA, BGFX_STATE_BLEND_SRC_ALPHA)
				);
			screenSpaceQuad( (float)width, (float)height, s_flipV);
			bgfx::submit(1
				, 1 == mode ? wbSeparateBlit : wbBlit
				);
		}

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	imguiDestroy();

	bgfx::destroyFrameBuffer(fbh);
	bgfx::destroyIndexBuffer(ibh);
	bgfx::destroyVertexBuffer(vbh);
	bgfx::destroyProgram(blend);
	bgfx::destroyProgram(wbSeparatePass);
	bgfx::destroyProgram(wbSeparateBlit);
	bgfx::destroyProgram(wbPass);
	bgfx::destroyProgram(wbBlit);
	bgfx::destroyUniform(s_texColor0);
	bgfx::destroyUniform(s_texColor1);
	bgfx::destroyUniform(u_color);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
