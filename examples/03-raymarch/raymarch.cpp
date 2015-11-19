/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include "bgfx_utils.h"

struct PosColorTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
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

static bool s_oglNdc = false;

inline void mtxProj(float* _result, float _fovy, float _aspect, float _near, float _far)
{
	bx::mtxProj(_result, _fovy, _aspect, _near, _far, s_oglNdc);
}

void renderScreenSpaceQuad(uint32_t _view, bgfx::ProgramHandle _program, float _x, float _y, float _width, float _height)
{
	bgfx::TransientVertexBuffer tvb;
	bgfx::TransientIndexBuffer tib;

	if (bgfx::allocTransientBuffers(&tvb, PosColorTexCoord0Vertex::ms_decl, 4, &tib, 6) )
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

		bgfx::setState(BGFX_STATE_DEFAULT);
		bgfx::setIndexBuffer(&tib);
		bgfx::setVertexBuffer(&tvb);
		bgfx::submit(_view, _program);
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

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	// Setup root path for binary shaders. Shader binaries are different
	// for each renderer.
	switch (bgfx::getRendererType() )
	{
	default:
		break;

	case bgfx::RendererType::OpenGL:
	case bgfx::RendererType::OpenGLES:
		s_oglNdc = true;
		break;
	}

	// Create vertex stream declaration.
	PosColorTexCoord0Vertex::init();

	bgfx::UniformHandle u_mtx          = bgfx::createUniform("u_mtx",      bgfx::UniformType::Mat4);
	bgfx::UniformHandle u_lightDirTime = bgfx::createUniform("u_lightDirTime", bgfx::UniformType::Vec4);

	// Create program from shaders.
	bgfx::ProgramHandle raymarching = loadProgram("vs_raymarching", "fs_raymarching");

	int64_t timeOffset = bx::getHPCounter();

	while (!entry::processEvents(width, height, debug, reset) )
	{
		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

		// Set view 1 default viewport.
		bgfx::setViewRect(1, 0, 0, width, height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to viewZ 0.
		bgfx::touch(0);

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
		bx::mtxLookAt(view, eye, at);
		mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 100.0f);

		// Set view and projection matrix for view 1.
		bgfx::setViewTransform(0, view, proj);

		float ortho[16];
		bx::mtxOrtho(ortho, 0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 100.0f);

		// Set view and projection matrix for view 0.
		bgfx::setViewTransform(1, NULL, ortho);

		float time = (float)( (bx::getHPCounter()-timeOffset)/double(bx::getHPFrequency() ) );

		float vp[16];
		bx::mtxMul(vp, view, proj);

		float mtx[16];
		bx::mtxRotateXY(mtx
			, time
			, time*0.37f
			);

		float mtxInv[16];
		bx::mtxInverse(mtxInv, mtx);
		float lightDirModel[4] = { -0.4f, -0.5f, -1.0f, 0.0f };
		float lightDirModelN[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		bx::vec3Norm(lightDirModelN, lightDirModel);
		float lightDirTime[4];
		bx::vec4MulMtx(lightDirTime, lightDirModelN, mtxInv);
		lightDirTime[3] = time;
		bgfx::setUniform(u_lightDirTime, lightDirTime);

		float mvp[16];
		bx::mtxMul(mvp, mtx, vp);

		float invMvp[16];
		bx::mtxInverse(invMvp, mvp);
		bgfx::setUniform(u_mtx, invMvp);

		renderScreenSpaceQuad(1, raymarching, 0.0f, 0.0f, 1280.0f, 720.0f);

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();
	}

	// Cleanup.
	bgfx::destroyProgram(raymarching);

	bgfx::destroyUniform(u_mtx);
	bgfx::destroyUniform(u_lightDirTime);

	// Shutdown bgfx.
	bgfx::shutdown();

	return 0;
}
