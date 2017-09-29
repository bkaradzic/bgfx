/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include <entry/cmd.h>
#include <entry/input.h>
#include <debugdraw/debugdraw.h>
#include "camera.h"
#include "imgui/imgui.h"

#include <bx/uint32_t.h>

namespace
{

void imageCheckerboard(void* _dst, uint32_t _width, uint32_t _height, uint32_t _step, uint32_t _0, uint32_t _1)
{
	uint32_t* dst = (uint32_t*)_dst;
	for (uint32_t yy = 0; yy < _height; ++yy)
	{
		for (uint32_t xx = 0; xx < _width; ++xx)
		{
			uint32_t abgr = ( (xx/_step)&1) ^ ( (yy/_step)&1) ? _1 : _0;
			*dst++ = abgr;
		}
	}
}

class ExampleDebugDraw : public entry::AppI
{
public:
	ExampleDebugDraw(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
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

		uint8_t data[32*32*4];
		imageCheckerboard(data, 32, 32, 4, 0xff808080, 0xffc0c0c0);

		m_sprite = ddCreateSprite(32, 32, data);

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		ddDestroy(m_sprite);

		ddShutdown();

		cameraDestroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	template<typename Ty>
	bool intersect(const Ray& _ray, const Ty& _shape)
	{
		Hit hit;
		if (::intersect(_ray, _shape, &hit) )
		{
			ddPush();

			ddSetWireframe(false);

			ddSetColor(0xff0000ff);

			float tmp[3];
			bx::vec3Mul(tmp, hit.m_normal, 0.7f);

			float end[3];
			bx::vec3Add(end, hit.m_pos, tmp);

			ddDrawCone(hit.m_pos, end, 0.1f);

			ddPop();

			return true;
		}

		return false;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(
				   m_mouseState.m_mx
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

			int64_t now = bx::getHPCounter() - m_timeOffset;
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const float deltaTime = float(frameTime/freq);

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
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

				bgfx::setViewTransform(0, view, proj);
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			float mtxVp[16];
			bx::mtxMul(mtxVp, view, proj);

			float mtxInvVp[16];
			bx::mtxInverse(mtxInvVp, mtxVp);

			float zero[3] = {};
			float eye[] = { 5.0f, 10.0f, 5.0f };
			bx::mtxLookAt(view, eye, zero);
			bx::mtxProj(proj, 45.0f, float(m_width)/float(m_height), 1.0f, 15.0f, bgfx::getCaps()->homogeneousDepth);
			bx::mtxMul(mtxVp, view, proj);

			Ray ray = makeRay(
				   (float(m_mouseState.m_mx)/float(m_width)  * 2.0f - 1.0f)
				, -(float(m_mouseState.m_my)/float(m_height) * 2.0f - 1.0f)
				, mtxInvVp
				);

			const uint32_t selected = 0xff80ffff;

			ddBegin(0);
			ddDrawAxis(0.0f, 0.0f, 0.0f);

			ddPush();
				Aabb aabb =
				{
					{  5.0f, 1.0f, 1.0f },
					{ 10.0f, 5.0f, 5.0f },
				};
				ddSetWireframe(true);
				ddSetColor(intersect(ray, aabb) ? selected : 0xff00ff00);
				ddDraw(aabb);
			ddPop();

			float time = float(now/freq);

			Obb obb;
			bx::mtxRotateX(obb.m_mtx, time);
			ddSetWireframe(true);
			ddSetColor(intersect(ray, obb) ? selected : 0xffffffff);
			ddDraw(obb);

			bx::mtxSRT(obb.m_mtx, 1.0f, 1.0f, 1.0f, time*0.23f, time, 0.0f, 3.0f, 0.0f, 0.0f);

			ddPush();
				toAabb(aabb, obb);
				ddSetWireframe(true);
				ddSetColor(0xff0000ff);
				ddDraw(aabb);
			ddPop();

			ddSetWireframe(false);
			ddSetColor(intersect(ray, obb) ? selected : 0xffffffff);
			ddDraw(obb);

			ddSetColor(0xffffffff);
			ddSetTranslate(0.0f, -2.0f, 0.0f);
			ddDrawGrid(Axis::Y, zero, 20, 1.0f);
			ddSetTransform(NULL);

			ddDrawFrustum(mtxVp);

			ddPush();
				Sphere sphere = { { 0.0f, 5.0f, 0.0f }, 1.0f };
				ddSetColor(intersect(ray, sphere) ? selected : 0xfff0c0ff);
				ddSetWireframe(true);
				ddSetLod(3);
				ddDraw(sphere);
				ddSetWireframe(false);

				sphere.m_center[0] = -2.0f;
				ddSetColor(intersect(ray, sphere) ? selected : 0xc0ffc0ff);
				ddSetLod(2);
				ddDraw(sphere);

				sphere.m_center[0] = -4.0f;
				ddSetColor(intersect(ray, sphere) ? selected : 0xa0f0ffff);
				ddSetLod(1);
				ddDraw(sphere);

				sphere.m_center[0] = -6.0f;
				ddSetColor(intersect(ray, sphere) ? selected : 0xffc0ff00);
				ddSetLod(0);
				ddDraw(sphere);
			ddPop();

			ddSetColor(0xffffffff);

			ddPush();
			{
				float normal[3] = {  0.0f, 0.0f, 1.0f };
				float center[3] = { -8.0f, 0.0f, 0.0f };
				ddPush();
					ddSetStipple(true, 1.0f, time*0.1f);
					ddSetColor(0xff0000ff);
					ddDrawCircle(normal, center, 1.0f, 0.5f + bx::fsin(time*10.0f) );
				ddPop();

				ddSetSpin(time);
				ddDrawQuad(m_sprite, normal, center, 2.0f);
			}
			ddPop();

			ddPush();
				ddSetStipple(true, 1.0f, -time*0.1f);
				ddDrawCircle(Axis::Z, -8.0f, 0.0f, 0.0f, 1.25f, 2.0f);
			ddPop();

			ddPush();
				ddSetLod(UINT8_MAX);

				ddPush();
					ddSetSpin(time*0.3f);
					{
						Cone cone =
						{
							{ -11.0f, 4.0f,  0.0f },
							{ -13.0f, 6.0f,  1.0f },
							1.0f
						};

						Cylinder cylinder =
						{
							{  -9.0f, 2.0f, -1.0f },
							{ -11.0f, 4.0f,  0.0f },
							0.5f
						};

						ddSetColor(false
							|| intersect(ray, cone)
							|| intersect(ray, cylinder)
							? selected
							: 0xffffffff
							);

						ddDraw(cone);
						ddDraw(cylinder);
					}
				ddPop();

				{
					ddSetLod(0);
					Capsule capsule =
					{
						{  0.0f, 7.0f, 0.0f },
						{ -6.0f, 7.0f, 0.0f },
						0.5f
					};
					ddSetColor(intersect(ray, capsule) ? selected : 0xffffffff);
					ddDraw(capsule);
				}
			ddPop();

			ddPush();

				float mtx[16];
				bx::mtxSRT(mtx
					, 1.0f, 1.0f, 1.0f
					, 0.0f, time, time*0.53f
					, -10.0f, 1.0f, 10.0f
					);

				Cylinder cylinder =
				{
					{ -10.0f, 1.0f, 10.0f },
					{ 0.0f, 0.0f, 0.0f },
					1.0f
				};

				float up[3] = { 0.0f, 4.0f, 0.0f };
				bx::vec3MulMtx(cylinder.m_end, up, mtx);
				ddSetColor(intersect(ray, cylinder) ? selected : 0xffffffff);
				ddDraw(cylinder);

				ddPush();
					toAabb(aabb, cylinder);
					ddSetWireframe(true);
					ddSetColor(0xff0000ff);
					ddDraw(aabb);
				ddPop();

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
	SpriteHandle m_sprite;

	int64_t m_timeOffset;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleDebugDraw, "29-debugdraw", "Debug draw.");
