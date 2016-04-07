/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include <entry/cmd.h>
#include <entry/input.h>
#include "camera.h"

#include <bx/uint32_t.h>

#include "../common/debugdraw/debugdraw.h"

class DebugDrawApp : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = 1280;
		m_height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X16;

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

		m_timeOffset = bx::getHPCounter();

		cameraCreate();

		const float initialPos[3] = { 0.0f, 2.0f, -12.0f };
		cameraSetPosition(initialPos);
		cameraSetVerticalAngle(0.0f);

		ddInit();
	}

	virtual int shutdown() BX_OVERRIDE
	{
		ddShutdown();

		cameraDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			int64_t now = bx::getHPCounter() - m_timeOffset;
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0/freq;
			const float deltaTime = float(frameTime/freq);

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/29-debugdraw");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Debug draw.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			// Update camera.
			cameraUpdate(deltaTime, m_mouseState);

			float view[16];
			cameraGetViewMtx(view);

			float proj[16];

			// Set view and projection matrix for view 0.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
			{
				float eye[3];
				cameraGetPosition(eye);
				bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);
				bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f);

				bgfx::setViewTransform(0, view, proj);
				bgfx::setViewRect(0, 0, 0, m_width, m_height);
			}

			float zero[3] = {};

			float mvp[16];
			float eye[] = { 5.0f, 10.0f, 5.0f };
			bx::mtxLookAt(view, eye, zero);
			bx::mtxProj(proj, 45.0f, float(m_width)/float(m_height), 1.0f, 15.0f);
			bx::mtxMul(mvp, view, proj);

			ddBegin(0);
			ddDrawAxis(0.0f, 0.0f, 0.0f);

			ddPush();
				ddSetColor(0xff00ff00);

				Aabb aabb =
				{
					{  5.0f, 1.0f, 1.0f },
					{ 10.0f, 5.0f, 5.0f },
				};
				ddDraw(aabb);
			ddPop();

			float time = float(now/freq);

			Obb obb;
			bx::mtxRotateX(obb.m_mtx, time);
			ddSetWireframe(true);
			ddDraw(obb);

			ddSetColor(0xffffffff);
			bx::mtxSRT(obb.m_mtx, 1.0f, 1.0f, 1.0f, 0.0f, time, 0.0f, 3.0f, 0.0f, 0.0f);
			ddSetWireframe(false);
			ddDraw(obb);

			ddSetTranslate(0.0f, -2.0f, 0.0f);
			ddDrawGrid(Axis::Y, zero, 20, 1.0f);
			ddSetTransform(NULL);

			ddDrawFrustum(mvp);

			ddPush();
				Sphere sphere = { { 0.0f, 5.0f, 0.0f }, 1.0f };
				ddSetColor(0xfff0c0ff);
				ddSetWireframe(true);
				ddSetLod(3);
				ddDraw(sphere);
				ddSetWireframe(false);

				ddSetColor(0xf0ffc0ff);
				sphere.m_center[0] = -2.0f;
				ddSetLod(2);
				ddDraw(sphere);

				ddSetColor(0xc0f0ffff);
				sphere.m_center[0] = -4.0f;
				ddSetLod(1);
				ddDraw(sphere);

				ddSetColor(0xffc0ff00);
				sphere.m_center[0] = -6.0f;
				ddSetLod(0);
				ddDraw(sphere);
			ddPop();

			ddSetColor(0xffffffff);

			ddPush();
				ddSetStipple(true, 1.0f, time*0.1f);
				ddSetColor(0xff0000ff);
				{
					float normal[3] = {  0.0f, 0.0f, 1.0f };
					float center[3] = { -8.0f, 0.0f, 0.0f };
					ddDrawCircle(normal, center, 1.0f, 0.5f + bx::fsin(time*10.0f) );
				}
			ddPop();

			ddPush();
				ddSetStipple(true, 1.0f, -time*0.1f);
				ddDrawCircle(Axis::Z, -8.0f, 0.0f, 0.0f, 1.25f, 2.0f);
			ddPop();

			ddPush();
				ddSetLod(UINT8_MAX);
				{
					float from[3] = { -11.0f, 4.0f,  0.0f };
					float to[3]   = { -13.0f, 6.0f,  1.0f };
					ddDrawCone(from, to, 1.0f );
				}

				{
					float from[3] = {  -9.0f, 2.0f, -1.0f };
					float to[3]   = { -11.0f, 4.0f,  0.0f };
					ddDrawCylinder(from, to, 0.5f );
				}
			ddPop();

			ddDrawOrb(-11.0f, 0.0f, 0.0f, 1.0f);
			ddEnd();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	int64_t m_timeOffset;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
};

ENTRY_IMPLEMENT_MAIN(DebugDrawApp);
