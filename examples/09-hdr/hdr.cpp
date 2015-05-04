/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

static float s_texelHalf = 0.0f;
static bool  s_originBottomLeft = false;

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
			float temp = minv;
			minv = maxv;
			maxv = temp;

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

void setOffsets2x2Lum(bgfx::UniformHandle _handle, uint32_t _width, uint32_t _height)
{
	float offsets[16][4];

	float du = 1.0f/_width;
	float dv = 1.0f/_height;

	uint32_t num = 0;
	for (uint32_t yy = 0; yy < 3; ++yy)
	{
		for (uint32_t xx = 0; xx < 3; ++xx)
		{
			offsets[num][0] = (xx - s_texelHalf) * du;
			offsets[num][1] = (yy - s_texelHalf) * dv;
			++num;
		}
	}

	bgfx::setUniform(_handle, offsets, num);
}

void setOffsets4x4Lum(bgfx::UniformHandle _handle, uint32_t _width, uint32_t _height)
{
	float offsets[16][4];

	float du = 1.0f/_width;
	float dv = 1.0f/_height;

	uint32_t num = 0;
	for (uint32_t yy = 0; yy < 4; ++yy)
	{
		for (uint32_t xx = 0; xx < 4; ++xx)
		{
			offsets[num][0] = (xx - 1.0f - s_texelHalf) * du;
			offsets[num][1] = (yy - 1.0f - s_texelHalf) * dv;
			++num;
		}
	}

	bgfx::setUniform(_handle, offsets, num);
}

inline float square(float _x)
{
	return _x*_x;
}

int _main_(int /*_argc*/, char** /*_argv*/)
{
	PosColorTexCoord0Vertex::init();

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
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	// Set view debug names.
	bgfx::setViewName(0, "Skybox");
	bgfx::setViewName(1, "Mesh");
	bgfx::setViewName(2, "Luminance");
	bgfx::setViewName(3, "Downscale luminance 0");
	bgfx::setViewName(4, "Downscale luminance 1");
	bgfx::setViewName(5, "Downscale luminance 2");
	bgfx::setViewName(6, "Downscale luminance 3");
	bgfx::setViewName(7, "Brightness");
	bgfx::setViewName(8, "Blur vertical");
	bgfx::setViewName(9, "Blur horizontal + tonemap");

	bgfx::TextureHandle uffizi = loadTexture("uffizi.dds"
			, 0
			| BGFX_TEXTURE_U_CLAMP
			| BGFX_TEXTURE_V_CLAMP
			| BGFX_TEXTURE_W_CLAMP
			);

	bgfx::ProgramHandle skyProgram     = loadProgram("vs_hdr_skybox",  "fs_hdr_skybox");
	bgfx::ProgramHandle lumProgram     = loadProgram("vs_hdr_lum",     "fs_hdr_lum");
	bgfx::ProgramHandle lumAvgProgram  = loadProgram("vs_hdr_lumavg",  "fs_hdr_lumavg");
	bgfx::ProgramHandle blurProgram    = loadProgram("vs_hdr_blur",    "fs_hdr_blur");
	bgfx::ProgramHandle brightProgram  = loadProgram("vs_hdr_bright",  "fs_hdr_bright");
	bgfx::ProgramHandle meshProgram    = loadProgram("vs_hdr_mesh",    "fs_hdr_mesh");
	bgfx::ProgramHandle tonemapProgram = loadProgram("vs_hdr_tonemap", "fs_hdr_tonemap");

	bgfx::UniformHandle u_time      = bgfx::createUniform("u_time",     bgfx::UniformType::Uniform1f);
	bgfx::UniformHandle u_texCube   = bgfx::createUniform("u_texCube",  bgfx::UniformType::Uniform1i);
	bgfx::UniformHandle u_texColor  = bgfx::createUniform("u_texColor", bgfx::UniformType::Uniform1i);
	bgfx::UniformHandle u_texLum    = bgfx::createUniform("u_texLum",   bgfx::UniformType::Uniform1i);
	bgfx::UniformHandle u_texBlur   = bgfx::createUniform("u_texBlur",  bgfx::UniformType::Uniform1i);
	bgfx::UniformHandle u_mtx       = bgfx::createUniform("u_mtx",      bgfx::UniformType::Uniform4x4fv);
	bgfx::UniformHandle u_tonemap   = bgfx::createUniform("u_tonemap",  bgfx::UniformType::Uniform4fv);
	bgfx::UniformHandle u_offset    = bgfx::createUniform("u_offset",   bgfx::UniformType::Uniform4fv, 16);

	Mesh* mesh = meshLoad("meshes/bunny.bin");

	bgfx::FrameBufferHandle fbh;
	bgfx::TextureHandle fbtextures[] =
	{
		bgfx::createTexture2D(width, height, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT|BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP),
		bgfx::createTexture2D(width, height, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_BUFFER_ONLY),
	};
	fbh = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);

	bgfx::FrameBufferHandle lum[5];
	lum[0] = bgfx::createFrameBuffer(128, 128, bgfx::TextureFormat::BGRA8);
	lum[1] = bgfx::createFrameBuffer( 64,  64, bgfx::TextureFormat::BGRA8);
	lum[2] = bgfx::createFrameBuffer( 16,  16, bgfx::TextureFormat::BGRA8);
	lum[3] = bgfx::createFrameBuffer(  4,   4, bgfx::TextureFormat::BGRA8);
	lum[4] = bgfx::createFrameBuffer(  1,   1, bgfx::TextureFormat::BGRA8);

	bgfx::FrameBufferHandle bright;
	bright = bgfx::createFrameBuffer(bgfx::BackbufferRatio::Half, bgfx::TextureFormat::BGRA8);

	bgfx::FrameBufferHandle blur;
	blur = bgfx::createFrameBuffer(bgfx::BackbufferRatio::Eighth, bgfx::TextureFormat::BGRA8);

	// Imgui.
	imguiCreate();

	const bgfx::RendererType::Enum renderer = bgfx::getRendererType();
	s_texelHalf = bgfx::RendererType::Direct3D9 == renderer ? 0.5f : 0.0f;
	s_originBottomLeft = bgfx::RendererType::OpenGL == renderer || bgfx::RendererType::OpenGLES == renderer;

	uint32_t oldWidth  = 0;
	uint32_t oldHeight = 0;
	uint32_t oldReset  = reset;

	float speed      = 0.37f;
	float middleGray = 0.18f;
	float white      = 1.1f;
	float threshold  = 1.5f;

	int32_t scrollArea = 0;

	float time = 0.0f;

	entry::MouseState mouseState;
	while (!entry::processEvents(width, height, debug, reset, &mouseState) )
	{
		if (oldWidth  != width
		||  oldHeight != height
		||  oldReset  != reset)
		{
			// Recreate variable size render targets when resolution changes.
			oldWidth  = width;
			oldHeight = height;
			oldReset  = reset;

			uint32_t msaa = (reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;

			bgfx::destroyFrameBuffer(fbh);

			fbtextures[0] = bgfx::createTexture2D(width, height, 1, bgfx::TextureFormat::BGRA8, ( (msaa+1)<<BGFX_TEXTURE_RT_MSAA_SHIFT)|BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);
			fbtextures[1] = bgfx::createTexture2D(width, height, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_BUFFER_ONLY|( (msaa+1)<<BGFX_TEXTURE_RT_MSAA_SHIFT) );
			fbh = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
		}

		imguiBeginFrame(mouseState.m_mx
			, mouseState.m_my
			, (mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT  : 0)
			| (mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT : 0)
			, 0
			, width
			, height
			);

		imguiBeginScrollArea("Settings", width - width / 5 - 10, 10, width / 5, height / 3, &scrollArea);
		imguiSeparatorLine();

		imguiSlider("Speed", speed, 0.0f, 1.0f, 0.01f);
		imguiSeparator();

		imguiSlider("Middle gray", middleGray, 0.1f, 1.0f, 0.01f);
		imguiSlider("White point", white, 0.1f, 2.0f, 0.01f);
		imguiSlider("Threshold", threshold, 0.1f, 2.0f, 0.01f);

		imguiEndScrollArea();
		imguiEndFrame();

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::submit(0);

		int64_t now = bx::getHPCounter();
		static int64_t last = now;
		const int64_t frameTime = now - last;
		last = now;
		const double freq = double(bx::getHPFrequency() );
		const double toMs = 1000.0/freq;

		time += (float)(frameTime*speed/freq);

		bgfx::setUniform(u_time, &time);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/09-hdr");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Using multiple views and frame buffers.");
		bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

		// Set views.
		for (uint32_t ii = 0; ii < 6; ++ii)
		{
			bgfx::setViewRect(ii, 0, 0, width, height);
		}
		bgfx::setViewFrameBuffer(0, fbh);
		bgfx::setViewFrameBuffer(1, fbh);
		bgfx::setViewClear(1, BGFX_CLEAR_DISCARD_DEPTH|BGFX_CLEAR_DISCARD_STENCIL);

		bgfx::setViewRect(2, 0, 0, 128, 128);
		bgfx::setViewFrameBuffer(2, lum[0]);

		bgfx::setViewRect(3, 0, 0, 64, 64);
		bgfx::setViewFrameBuffer(3, lum[1]);

		bgfx::setViewRect(4, 0, 0, 16, 16);
		bgfx::setViewFrameBuffer(4, lum[2]);

		bgfx::setViewRect(5, 0, 0, 4, 4);
		bgfx::setViewFrameBuffer(5, lum[3]);

		bgfx::setViewRect(6, 0, 0, 1, 1);
		bgfx::setViewFrameBuffer(6, lum[4]);

		bgfx::setViewRect(7, 0, 0, width/2, height/2);
		bgfx::setViewFrameBuffer(7, bright);

		bgfx::setViewRect(8, 0, 0, width/8, height/8);
		bgfx::setViewFrameBuffer(8, blur);

		bgfx::setViewRect(9, 0, 0, width, height);

		float view[16];
		float proj[16];

		bx::mtxIdentity(view);
		bx::mtxOrtho(proj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 100.0f);

		// Set view and projection matrix for view 0.
		for (uint32_t ii = 0; ii < 10; ++ii)
		{
			bgfx::setViewTransform(ii, view, proj);
		}

		float at[3] = { 0.0f, 1.0f, 0.0f };
		float eye[3] = { 0.0f, 1.0f, -2.5f };

		float mtx[16];
		bx::mtxRotateXY(mtx
			, 0.0f
			, time
			);

		float temp[4];
		bx::vec3MulMtx(temp, eye, mtx);

		bx::mtxLookAt(view, temp, at);
		bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		// Set view and projection matrix for view 1.
		bgfx::setViewTransform(1, view, proj);

		bgfx::setUniform(u_mtx, mtx);

		// Render skybox into view 0.
		bgfx::setTexture(0, u_texCube, uffizi);

		bgfx::setProgram(skyProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width, (float)height, true);
		bgfx::submit(0);

		// Render mesh into view 1
		bgfx::setTexture(0, u_texCube, uffizi);
		meshSubmit(mesh, 1, meshProgram, NULL);

		// Calculate luminance.
		setOffsets2x2Lum(u_offset, 128, 128);
		bgfx::setTexture(0, u_texColor, fbtextures[0]);
		bgfx::setProgram(lumProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(128.0f, 128.0f, s_originBottomLeft);
		bgfx::submit(2);

		// Downscale luminance 0.
		setOffsets4x4Lum(u_offset, 128, 128);
		bgfx::setTexture(0, u_texColor, lum[0]);
		bgfx::setProgram(lumAvgProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(64.0f, 64.0f, s_originBottomLeft);
		bgfx::submit(3);

		// Downscale luminance 1.
		setOffsets4x4Lum(u_offset, 64, 64);
		bgfx::setTexture(0, u_texColor, lum[1]);
		bgfx::setProgram(lumAvgProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(16.0f, 16.0f, s_originBottomLeft);
		bgfx::submit(4);

		// Downscale luminance 2.
		setOffsets4x4Lum(u_offset, 16, 16);
		bgfx::setTexture(0, u_texColor, lum[2]);
		bgfx::setProgram(lumAvgProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(4.0f, 4.0f, s_originBottomLeft);
		bgfx::submit(5);

		// Downscale luminance 3.
		setOffsets4x4Lum(u_offset, 4, 4);
		bgfx::setTexture(0, u_texColor, lum[3]);
		bgfx::setProgram(lumAvgProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad(1.0f, 1.0f, s_originBottomLeft);
		bgfx::submit(6);

		float tonemap[4] = { middleGray, square(white), threshold, 0.0f };
		bgfx::setUniform(u_tonemap, tonemap);

		// Bright pass threshold is tonemap[3].
		setOffsets4x4Lum(u_offset, width/2, height/2);
		bgfx::setTexture(0, u_texColor, fbtextures[0]);
		bgfx::setTexture(1, u_texLum, lum[4]);
		bgfx::setProgram(brightProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width/2.0f, (float)height/2.0f, s_originBottomLeft);
		bgfx::submit(7);

		// Blur bright pass vertically.
		bgfx::setTexture(0, u_texColor, bright);
		bgfx::setProgram(blurProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width/8.0f, (float)height/8.0f, s_originBottomLeft);
		bgfx::submit(8);

		// Blur bright pass horizontally, do tonemaping and combine.
		bgfx::setTexture(0, u_texColor, fbtextures[0]);
		bgfx::setTexture(1, u_texLum, lum[4]);
		bgfx::setTexture(2, u_texBlur, blur);
		bgfx::setProgram(tonemapProgram);
		bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
		screenSpaceQuad( (float)width, (float)height, s_originBottomLeft);
		bgfx::submit(9);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	imguiDestroy();

	meshUnload(mesh);

	for (uint32_t ii = 0; ii < BX_COUNTOF(lum); ++ii)
	{
		bgfx::destroyFrameBuffer(lum[ii]);
	}
	bgfx::destroyFrameBuffer(bright);
	bgfx::destroyFrameBuffer(blur);
	bgfx::destroyFrameBuffer(fbh);

	bgfx::destroyProgram(meshProgram);
	bgfx::destroyProgram(skyProgram);
	bgfx::destroyProgram(tonemapProgram);
	bgfx::destroyProgram(lumProgram);
	bgfx::destroyProgram(lumAvgProgram);
	bgfx::destroyProgram(blurProgram);
	bgfx::destroyProgram(brightProgram);
	bgfx::destroyTexture(uffizi);

	bgfx::destroyUniform(u_time);
	bgfx::destroyUniform(u_texCube);
	bgfx::destroyUniform(u_texColor);
	bgfx::destroyUniform(u_texLum);
	bgfx::destroyUniform(u_texBlur);
	bgfx::destroyUniform(u_mtx);
	bgfx::destroyUniform(u_tonemap);
	bgfx::destroyUniform(u_offset);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
