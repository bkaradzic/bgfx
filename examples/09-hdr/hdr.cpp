/*
 * Copyright 2011-2016 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

static float s_texelHalf = 0.0f;

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

class ExampleHDR : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = 1280;
		m_height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		// Enable m_debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
				);

		// Create vertex stream declaration.
		PosColorTexCoord0Vertex::init();

		// Set view m_debug names.
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

		m_uffizi = loadTexture("uffizi.dds"
				, 0
				| BGFX_TEXTURE_U_CLAMP
				| BGFX_TEXTURE_V_CLAMP
				| BGFX_TEXTURE_W_CLAMP
				);

		m_skyProgram     = loadProgram("vs_hdr_skybox",  "fs_hdr_skybox");
		m_lumProgram     = loadProgram("vs_hdr_lum",     "fs_hdr_lum");
		m_lumAvgProgram  = loadProgram("vs_hdr_lumavg",  "fs_hdr_lumavg");
		m_blurProgram    = loadProgram("vs_hdr_blur",    "fs_hdr_blur");
		m_brightProgram  = loadProgram("vs_hdr_bright",  "fs_hdr_bright");
		m_meshProgram    = loadProgram("vs_hdr_mesh",    "fs_hdr_mesh");
		m_tonemapProgram = loadProgram("vs_hdr_tonemap", "fs_hdr_tonemap");

		s_texCube   = bgfx::createUniform("s_texCube",  bgfx::UniformType::Int1);
		s_texColor  = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);
		s_texLum    = bgfx::createUniform("s_texLum",   bgfx::UniformType::Int1);
		s_texBlur   = bgfx::createUniform("s_texBlur",  bgfx::UniformType::Int1);
		u_mtx       = bgfx::createUniform("u_mtx",      bgfx::UniformType::Mat4);
		u_tonemap   = bgfx::createUniform("u_tonemap",  bgfx::UniformType::Vec4);
		u_offset    = bgfx::createUniform("u_offset",   bgfx::UniformType::Vec4, 16);

		m_mesh = meshLoad("meshes/bunny.bin");

		m_fbtextures[0] = bgfx::createTexture2D(m_width, m_height, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_RT|BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);
		m_fbtextures[1] = bgfx::createTexture2D(m_width, m_height, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_WRITE_ONLY);
		m_fbh = bgfx::createFrameBuffer(BX_COUNTOF(m_fbtextures), m_fbtextures, true);

		m_lum[0] = bgfx::createFrameBuffer(128, 128, bgfx::TextureFormat::BGRA8);
		m_lum[1] = bgfx::createFrameBuffer( 64,  64, bgfx::TextureFormat::BGRA8);
		m_lum[2] = bgfx::createFrameBuffer( 16,  16, bgfx::TextureFormat::BGRA8);
		m_lum[3] = bgfx::createFrameBuffer(  4,   4, bgfx::TextureFormat::BGRA8);
		m_lum[4] = bgfx::createFrameBuffer(  1,   1, bgfx::TextureFormat::BGRA8);

		m_bright = bgfx::createFrameBuffer(bgfx::BackbufferRatio::Half,   bgfx::TextureFormat::BGRA8);
		m_blur   = bgfx::createFrameBuffer(bgfx::BackbufferRatio::Eighth, bgfx::TextureFormat::BGRA8);

		m_lumBgra8 = 0;
		if ( (BGFX_CAPS_TEXTURE_BLIT|BGFX_CAPS_TEXTURE_READ_BACK) == (bgfx::getCaps()->supported & (BGFX_CAPS_TEXTURE_BLIT|BGFX_CAPS_TEXTURE_READ_BACK) ) )
		{
			m_rb = bgfx::createTexture2D(1, 1, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_READ_BACK);
		}
		else
		{
			m_rb.idx = bgfx::invalidHandle;
		}

		// Imgui.
		imguiCreate();

		m_caps = bgfx::getCaps();
		s_texelHalf = bgfx::RendererType::Direct3D9 == m_caps->rendererType ? 0.5f : 0.0f;

		m_oldWidth  = 0;
		m_oldHeight = 0;
		m_oldReset  = m_reset;

		m_speed      = 0.37f;
		m_middleGray = 0.18f;
		m_white      = 1.1f;
		m_threshold  = 1.5f;

		m_scrollArea = 0;

		m_time = 0.0f;
	}

	virtual int shutdown() BX_OVERRIDE
	{
		// Cleanup.
		imguiDestroy();

		meshUnload(m_mesh);

		for (uint32_t ii = 0; ii < BX_COUNTOF(m_lum); ++ii)
		{
			bgfx::destroyFrameBuffer(m_lum[ii]);
		}
		bgfx::destroyFrameBuffer(m_bright);
		bgfx::destroyFrameBuffer(m_blur);
		bgfx::destroyFrameBuffer(m_fbh);

		bgfx::destroyProgram(m_meshProgram);
		bgfx::destroyProgram(m_skyProgram);
		bgfx::destroyProgram(m_tonemapProgram);
		bgfx::destroyProgram(m_lumProgram);
		bgfx::destroyProgram(m_lumAvgProgram);
		bgfx::destroyProgram(m_blurProgram);
		bgfx::destroyProgram(m_brightProgram);
		bgfx::destroyTexture(m_uffizi);
		if (bgfx::isValid(m_rb) )
		{
			bgfx::destroyTexture(m_rb);
		}

		bgfx::destroyUniform(s_texCube);
		bgfx::destroyUniform(s_texColor);
		bgfx::destroyUniform(s_texLum);
		bgfx::destroyUniform(s_texBlur);
		bgfx::destroyUniform(u_mtx);
		bgfx::destroyUniform(u_tonemap);
		bgfx::destroyUniform(u_offset);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			if (m_oldWidth  != m_width
			||  m_oldHeight != m_height
			||  m_oldReset  != m_reset)
			{
				// Recreate variable size render targets when resolution changes.
				m_oldWidth  = m_width;
				m_oldHeight = m_height;
				m_oldReset  = m_reset;

				uint32_t msaa = (m_reset&BGFX_RESET_MSAA_MASK)>>BGFX_RESET_MSAA_SHIFT;

				bgfx::destroyFrameBuffer(m_fbh);

				m_fbtextures[0] = bgfx::createTexture2D(m_width, m_height, 1, bgfx::TextureFormat::BGRA8, ( (msaa+1)<<BGFX_TEXTURE_RT_MSAA_SHIFT)|BGFX_TEXTURE_U_CLAMP|BGFX_TEXTURE_V_CLAMP);
				m_fbtextures[1] = bgfx::createTexture2D(m_width, m_height, 1, bgfx::TextureFormat::D16, BGFX_TEXTURE_RT_WRITE_ONLY|( (msaa+1)<<BGFX_TEXTURE_RT_MSAA_SHIFT) );
				m_fbh = bgfx::createFrameBuffer(BX_COUNTOF(m_fbtextures), m_fbtextures, true);
			}

			imguiBeginFrame(m_mouseState.m_mx
					,  m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					,  m_mouseState.m_mz
					, m_width
					, m_height
					);

			imguiBeginScrollArea("Settings", m_width - m_width / 5 - 10, 10, m_width / 5, m_height / 2, &m_scrollArea);
			imguiSeparatorLine();

			imguiSlider("Speed", m_speed, 0.0f, 1.0f, 0.01f);
			imguiSeparator();

			imguiSlider("Middle gray", m_middleGray, 0.1f, 1.0f, 0.01f);
			imguiSlider("White point", m_white,      0.1f, 2.0f, 0.01f);
			imguiSlider("Threshold",   m_threshold,  0.1f, 2.0f, 0.01f);

			if (bgfx::isValid(m_rb) )
			{
				union { uint32_t color; uint8_t bgra[4]; } cast = { m_lumBgra8 };
				float exponent = cast.bgra[3]/255.0f * 255.0f - 128.0f;
				float lumAvg   = cast.bgra[2]/255.0f * bx::fexp2(exponent);
				imguiSlider("Lum Avg", lumAvg, 0.0f, 1.0f, 0.01f, false);
			}

			imguiEndScrollArea();
			imguiEndFrame();

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0/freq;

			m_time += (float)(frameTime*m_speed/freq);

			// Use m_debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/09-hdr");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Using multiple views and frame buffers.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			// Set views.
			for (uint32_t ii = 0; ii < 6; ++ii)
			{
				bgfx::setViewRect(ii, 0, 0, bgfx::BackbufferRatio::Equal);
			}
			bgfx::setViewFrameBuffer(0, m_fbh);
			bgfx::setViewFrameBuffer(1, m_fbh);
			bgfx::setViewClear(1, BGFX_CLEAR_DISCARD_DEPTH|BGFX_CLEAR_DISCARD_STENCIL);

			bgfx::setViewRect(2, 0, 0, 128, 128);
			bgfx::setViewFrameBuffer(2, m_lum[0]);

			bgfx::setViewRect(3, 0, 0, 64, 64);
			bgfx::setViewFrameBuffer(3, m_lum[1]);

			bgfx::setViewRect(4, 0, 0, 16, 16);
			bgfx::setViewFrameBuffer(4, m_lum[2]);

			bgfx::setViewRect(5, 0, 0, 4, 4);
			bgfx::setViewFrameBuffer(5, m_lum[3]);

			bgfx::setViewRect(6, 0, 0, 1, 1);
			bgfx::setViewFrameBuffer(6, m_lum[4]);

			bgfx::setViewRect(7, 0, 0, bgfx::BackbufferRatio::Half);
			bgfx::setViewFrameBuffer(7, m_bright);

			bgfx::setViewRect(8, 0, 0, bgfx::BackbufferRatio::Eighth);
			bgfx::setViewFrameBuffer(8, m_blur);

			bgfx::setViewRect(9, 0, 0, bgfx::BackbufferRatio::Equal);

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
					, m_time
					);

			float temp[4];
			bx::vec3MulMtx(temp, eye, mtx);

			bx::mtxLookAt(view, temp, at);
			bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f);

			// Set view and projection matrix for view 1.
			bgfx::setViewTransform(1, view, proj);

			bgfx::setUniform(u_mtx, mtx);

			// Render skybox into view 0.
			bgfx::setTexture(0, s_texCube, m_uffizi);

			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad( (float)m_width, (float)m_height, true);
			bgfx::submit(0, m_skyProgram);

			// Render m_mesh into view 1
			bgfx::setTexture(0, s_texCube, m_uffizi);
			meshSubmit(m_mesh, 1, m_meshProgram, NULL);

			// Calculate luminance.
			setOffsets2x2Lum(u_offset, 128, 128);
			bgfx::setTexture(0, s_texColor, m_fbtextures[0]);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad(128.0f, 128.0f, m_caps->originBottomLeft);
			bgfx::submit(2, m_lumProgram);

			// Downscale luminance 0.
			setOffsets4x4Lum(u_offset, 128, 128);
			bgfx::setTexture(0, s_texColor, m_lum[0]);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad(64.0f, 64.0f, m_caps->originBottomLeft);
			bgfx::submit(3, m_lumAvgProgram);

			// Downscale luminance 1.
			setOffsets4x4Lum(u_offset, 64, 64);
			bgfx::setTexture(0, s_texColor, m_lum[1]);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad(16.0f, 16.0f, m_caps->originBottomLeft);
			bgfx::submit(4, m_lumAvgProgram);

			// Downscale luminance 2.
			setOffsets4x4Lum(u_offset, 16, 16);
			bgfx::setTexture(0, s_texColor, m_lum[2]);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad(4.0f, 4.0f, m_caps->originBottomLeft);
			bgfx::submit(5, m_lumAvgProgram);

			// Downscale luminance 3.
			setOffsets4x4Lum(u_offset, 4, 4);
			bgfx::setTexture(0, s_texColor, m_lum[3]);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad(1.0f, 1.0f, m_caps->originBottomLeft);
			bgfx::submit(6, m_lumAvgProgram);

			float tonemap[4] = { m_middleGray, square(m_white), m_threshold, m_time };
			bgfx::setUniform(u_tonemap, tonemap);

			// m_bright pass m_threshold is tonemap[3].
			setOffsets4x4Lum(u_offset, m_width/2, m_height/2);
			bgfx::setTexture(0, s_texColor, m_fbtextures[0]);
			bgfx::setTexture(1, s_texLum, m_lum[4]);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad( (float)m_width/2.0f, (float)m_height/2.0f, m_caps->originBottomLeft);
			bgfx::submit(7, m_brightProgram);

			// m_blur m_bright pass vertically.
			bgfx::setTexture(0, s_texColor, m_bright);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad( (float)m_width/8.0f, (float)m_height/8.0f, m_caps->originBottomLeft);
			bgfx::submit(8, m_blurProgram);

			// m_blur m_bright pass horizontally, do tonemaping and combine.
			bgfx::setTexture(0, s_texColor, m_fbtextures[0]);
			bgfx::setTexture(1, s_texLum, m_lum[4]);
			bgfx::setTexture(2, s_texBlur, m_blur);
			bgfx::setState(BGFX_STATE_RGB_WRITE|BGFX_STATE_ALPHA_WRITE);
			screenSpaceQuad( (float)m_width, (float)m_height, m_caps->originBottomLeft);
			bgfx::submit(9, m_tonemapProgram);

			if (bgfx::isValid(m_rb) )
			{
				bgfx::blit(9, m_rb, 0, 0, m_lum[4]);
				bgfx::readTexture(m_rb, &m_lumBgra8);
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	bgfx::ProgramHandle m_skyProgram;
	bgfx::ProgramHandle m_lumProgram;
	bgfx::ProgramHandle m_lumAvgProgram;
	bgfx::ProgramHandle m_blurProgram;
	bgfx::ProgramHandle m_brightProgram;
	bgfx::ProgramHandle m_meshProgram;
	bgfx::ProgramHandle m_tonemapProgram;

	bgfx::TextureHandle m_uffizi;
	bgfx::UniformHandle s_texCube;
	bgfx::UniformHandle s_texColor;
	bgfx::UniformHandle s_texLum;
	bgfx::UniformHandle s_texBlur;
	bgfx::UniformHandle u_mtx;
	bgfx::UniformHandle u_tonemap;
	bgfx::UniformHandle u_offset;

	Mesh* m_mesh;

	bgfx::TextureHandle m_fbtextures[2];
	bgfx::TextureHandle m_rb;
	bgfx::FrameBufferHandle m_fbh;
	bgfx::FrameBufferHandle m_lum[5];
	bgfx::FrameBufferHandle m_bright;
	bgfx::FrameBufferHandle m_blur;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	uint32_t m_lumBgra8;

	uint32_t m_oldWidth;
	uint32_t m_oldHeight;
	uint32_t m_oldReset;

	float m_speed;
	float m_middleGray;
	float m_white;
	float m_threshold;

	int32_t m_scrollArea;

	const bgfx::Caps* m_caps;
	float m_time;
};

ENTRY_IMPLEMENT_MAIN(ExampleHDR);
