/*
 * Copyright 2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

struct DrawMode
{
	enum
	{
		WireframeShaded,
		Wireframe,
		Shaded,
	};
};

struct Camera
{
	Camera()
	{
		reset();
	}

	void reset()
	{
		m_target.curr[0] = 0.0f;
		m_target.curr[1] = 0.0f;
		m_target.curr[2] = 0.0f;
		m_target.dest[0] = 0.0f;
		m_target.dest[1] = 0.0f;
		m_target.dest[2] = 0.0f;

		m_pos.curr[0] =  0.0f;
		m_pos.curr[1] =  0.0f;
		m_pos.curr[2] = -2.0f;
		m_pos.dest[0] =  0.0f;
		m_pos.dest[1] =  0.0f;
		m_pos.dest[2] = -2.0f;

		m_orbit[0] = 0.0f;
		m_orbit[1] = 0.0f;
	}

	void mtxLookAt(float* _outViewMtx)
	{
		bx::mtxLookAt(_outViewMtx, m_pos.curr, m_target.curr);
	}

	void orbit(float _dx, float _dy)
	{
		m_orbit[0] += _dx;
		m_orbit[1] += _dy;
	}

	void dolly(float _dz)
	{
		const float cnear = 0.01f;
		const float cfar  = 10.0f;

		const float toTarget[3] =
		{
			m_target.dest[0] - m_pos.dest[0],
			m_target.dest[1] - m_pos.dest[1],
			m_target.dest[2] - m_pos.dest[2],
		};
		const float toTargetLen = bx::vec3Length(toTarget);
		const float invToTargetLen = 1.0f/(toTargetLen+FLT_MIN);
		const float toTargetNorm[3] =
		{
			toTarget[0]*invToTargetLen,
			toTarget[1]*invToTargetLen,
			toTarget[2]*invToTargetLen,
		};

		float delta = toTargetLen*_dz;
		float newLen = toTargetLen + delta;
		if ( (cnear < newLen || _dz < 0.0f)
		&&   (newLen < cfar  || _dz > 0.0f) )
		{
			m_pos.dest[0] += toTargetNorm[0]*delta;
			m_pos.dest[1] += toTargetNorm[1]*delta;
			m_pos.dest[2] += toTargetNorm[2]*delta;
		}
	}

	void consumeOrbit(float _amount)
	{
		float consume[2];
		consume[0] = m_orbit[0]*_amount;
		consume[1] = m_orbit[1]*_amount;
		m_orbit[0] -= consume[0];
		m_orbit[1] -= consume[1];

		const float toPos[3] =
		{
			m_pos.curr[0] - m_target.curr[0],
			m_pos.curr[1] - m_target.curr[1],
			m_pos.curr[2] - m_target.curr[2],
		};
		const float toPosLen = bx::vec3Length(toPos);
		const float invToPosLen = 1.0f/(toPosLen+FLT_MIN);
		const float toPosNorm[3] =
		{
			toPos[0]*invToPosLen,
			toPos[1]*invToPosLen,
			toPos[2]*invToPosLen,
		};

		float ll[2];
		latLongFromVec(ll[0], ll[1], toPosNorm);
		ll[0] += consume[0];
		ll[1] -= consume[1];
		ll[1] = bx::fclamp(ll[1], 0.02f, 0.98f);

		float tmp[3];
		vecFromLatLong(tmp, ll[0], ll[1]);

		float diff[3];
		diff[0] = (tmp[0]-toPosNorm[0])*toPosLen;
		diff[1] = (tmp[1]-toPosNorm[1])*toPosLen;
		diff[2] = (tmp[2]-toPosNorm[2])*toPosLen;

		m_pos.curr[0] += diff[0];
		m_pos.curr[1] += diff[1];
		m_pos.curr[2] += diff[2];
		m_pos.dest[0] += diff[0];
		m_pos.dest[1] += diff[1];
		m_pos.dest[2] += diff[2];
	}

	void update(float _dt)
	{
		const float amount = bx::fmin(_dt/0.12f, 1.0f);

		consumeOrbit(amount);

		m_target.curr[0] = bx::flerp(m_target.curr[0], m_target.dest[0], amount);
		m_target.curr[1] = bx::flerp(m_target.curr[1], m_target.dest[1], amount);
		m_target.curr[2] = bx::flerp(m_target.curr[2], m_target.dest[2], amount);
		m_pos.curr[0] = bx::flerp(m_pos.curr[0], m_pos.dest[0], amount);
		m_pos.curr[1] = bx::flerp(m_pos.curr[1], m_pos.dest[1], amount);
		m_pos.curr[2] = bx::flerp(m_pos.curr[2], m_pos.dest[2], amount);
	}

	static inline void vecFromLatLong(float _vec[3], float _u, float _v)
	{
		const float phi   = _u * 2.0f*bx::pi;
		const float theta = _v * bx::pi;

		const float st = bx::fsin(theta);
		const float sp = bx::fsin(phi);
		const float ct = bx::fcos(theta);
		const float cp = bx::fcos(phi);

		_vec[0] = -st*sp;
		_vec[1] = ct;
		_vec[2] = -st*cp;
	}

	static inline void latLongFromVec(float& _u, float& _v, const float _vec[3])
	{
		const float phi   = bx::fatan2(_vec[0], _vec[2]);
		const float theta = bx::facos(_vec[1]);

		_u = (bx::pi + phi)*bx::invPi*0.5f;
		_v = theta*bx::invPi;
	}

	struct Interp3f
	{
		float curr[3];
		float dest[3];
	};

	Interp3f m_target;
	Interp3f m_pos;
	float m_orbit[2];
};

struct Mouse
{
	Mouse()
	{
		m_dx = 0.0f;
		m_dy = 0.0f;
		m_prevMx = 0.0f;
		m_prevMx = 0.0f;
		m_scroll = 0;
		m_scrollPrev = 0;
	}

	void update(float _mx, float _my, int32_t _mz, uint32_t _width, uint32_t _height)
	{
		const float widthf  = float(int32_t(_width));
		const float heightf = float(int32_t(_height));

		// Delta movement.
		m_dx = float(_mx - m_prevMx)/widthf;
		m_dy = float(_my - m_prevMy)/heightf;

		m_prevMx = _mx;
		m_prevMy = _my;

		// Scroll.
		m_scroll = _mz - m_scrollPrev;
		m_scrollPrev = _mz;
	}

	float m_dx; // Screen space.
	float m_dy;
	float m_prevMx;
	float m_prevMy;
	int32_t m_scroll;
	int32_t m_scrollPrev;
};

struct MeshMtx
{
	MeshMtx()
	{
		m_mesh = NULL;
	}

	void init(const char* _path
			, float _scale = 1.0f
			, float _rotX = 0.0f
			, float _rotY = 0.0f
			, float _rotZ = 0.0f
			, float _transX = 0.0f
			, float _transY = 0.0f
			, float _transZ = 0.0f
			)
	{
		m_mesh = meshLoad(_path);
		bx::mtxSRT(m_mtx
					, _scale
					, _scale
					, _scale
					, _rotX
					, _rotY
					, _rotZ
					, _transX
					, _transY
					, _transZ
					);
	}

	void destroy()
	{
		if (NULL != m_mesh)
		{
			meshUnload(m_mesh);
		}
	}

	Mesh* m_mesh;
	float m_mtx[16];
};

struct Uniforms
{
	enum { NumVec4 = 3 };

	void init()
	{
		m_camPos[0] = 0.0f;
		m_camPos[1] = 1.0f;
		m_camPos[2] = -2.5f;
		m_wfColor[0] = 1.0f;
		m_wfColor[1] = 0.0f;
		m_wfColor[2] = 0.0f;
		m_wfOpacity = 0.7f;
		m_drawEdges = 0.0f;
		m_wfThickness = 1.5f;

		u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, NumVec4);
	}

	void submit()
	{
		bgfx::setUniform(u_params, m_params, NumVec4);
	}

	void destroy()
	{
		bgfx::destroyUniform(u_params);
	}

	union
	{
		struct
		{
			/*0*/struct { float m_camPos[3], m_unused0; };
			/*1*/struct { float m_wfColor[3], m_wfOpacity; };
			/*2*/struct { float m_drawEdges, m_wfThickness, m_unused2[2]; };
		};

		float m_params[NumVec4*4];
	};

	bgfx::UniformHandle u_params;
};

class ExampleWireframe : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		Args args(_argc, _argv);

		m_width  = 1280;
		m_height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = 0
			| BGFX_RESET_VSYNC
			| BGFX_RESET_MSAA_X16
			;

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

		m_wfProgram   = loadProgram("vs_wf_wireframe", "fs_wf_wireframe");
		m_meshProgram = loadProgram("vs_wf_mesh",      "fs_wf_mesh");

		m_uniforms.init();

		m_meshes[0].init("meshes/bunny.bin",      1.0f, 0.0f, bx::pi, 0.0f, 0.0f, -0.8f,  0.0f);
		m_meshes[1].init("meshes/hollowcube.bin", 1.0f, 0.0f,   0.0f, 0.0f, 0.0f,  0.0f,  0.0f);
		m_meshes[2].init("meshes/orb.bin",        1.2f, 0.0f,   0.0f, 0.0f, 0.0f, -0.65f, 0.0f);

		// Imgui.
		imguiCreate();

		m_oldWidth  = 0;
		m_oldHeight = 0;
		m_oldReset  = m_reset;

		m_meshSelection = 1;
		m_drawMode = DrawMode::WireframeShaded;
		m_scrollArea = 0;
		m_showWfColor = true;
	}

	virtual int shutdown() BX_OVERRIDE
	{
		// Cleanup.
		imguiDestroy();

		m_meshes[0].destroy();
		m_meshes[1].destroy();
		m_meshes[2].destroy();

		bgfx::destroyProgram(m_wfProgram);
		bgfx::destroyProgram(m_meshProgram);

		m_uniforms.destroy();

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

			imguiBeginScrollArea("Settings"
							    , m_width - m_width / 5 - 10
							    , 10
							    , m_width / 5
							    , 492
							    , &m_scrollArea
							    );

			imguiSeparatorLine(1); imguiIndent(8); imguiLabel("Draw mode:"); imguiUnindent(8); imguiSeparatorLine(1);
			imguiSeparator(4);
			{
				imguiIndent();
				m_drawMode = imguiChoose(m_drawMode
										, "Wireframe + Shaded"
										, "Wireframe"
										, "Shaded"
										);
				imguiUnindent();
			}
			imguiSeparator(8);

			const bool wfEnabled = (DrawMode::Shaded != m_drawMode);
			imguiSeparatorLine(1); imguiIndent(8); imguiLabel("Wireframe:", wfEnabled); imguiUnindent(8); imguiSeparatorLine(1);
			imguiSeparator(4);
			{
				imguiColorWheel("Color", m_uniforms.m_wfColor, m_showWfColor, 0.6f, wfEnabled);
				imguiIndent();
				imguiSlider("Opacity",   m_uniforms.m_wfOpacity,   0.1f, 1.0f, 0.1f, wfEnabled);
				imguiSlider("Thickness", m_uniforms.m_wfThickness, 0.6f, 2.2f, 0.1f, wfEnabled);
				imguiUnindent();
			}
			imguiSeparator(8);

			imguiSeparatorLine(1); imguiIndent(8); imguiLabel("Mesh:"); imguiUnindent(8); imguiSeparatorLine(1);
			imguiSeparator(4);
			{
				imguiIndent();
				const uint32_t prevMeshSel = m_meshSelection;
				m_meshSelection = imguiChoose(m_meshSelection
											, "Bunny"
											, "Hollowcubes"
											, "Orb"
											);
				if (prevMeshSel != m_meshSelection)
				{
					m_camera.reset();
				}
				imguiUnindent();
			}
			imguiSeparator(8);

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
			const float deltaTimeSec = float(double(frameTime)/freq);

			// Use m_debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/28-wirefame");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Drawing wireframe mesh.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			// Setup view.
			bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
			bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);

			const bool mouseOverGui = imguiMouseOverArea();
			m_mouse.update(float(m_mouseState.m_mx), float(m_mouseState.m_my), m_mouseState.m_mz, m_width, m_height);
			if (!mouseOverGui)
			{
				if (m_mouseState.m_buttons[entry::MouseButton::Left])
				{
					m_camera.orbit(m_mouse.m_dx, m_mouse.m_dy);
				}
				else if (m_mouseState.m_buttons[entry::MouseButton::Right])
				{
					m_camera.dolly(m_mouse.m_dx + m_mouse.m_dy);
				}
				else if (0 != m_mouse.m_scroll)
				{
					m_camera.dolly(float(m_mouse.m_scroll)*0.1f);
				}
			}

			float view[16];
			float proj[16];
			m_camera.update(deltaTimeSec);
			bx::memCopy(m_uniforms.m_camPos, m_camera.m_pos.curr, 3*sizeof(float));
			m_camera.mtxLookAt(view);
			bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);

			m_uniforms.m_drawEdges = (DrawMode::WireframeShaded == m_drawMode) ? 1.0f : 0.0f;
			m_uniforms.submit();

			if (DrawMode::Wireframe == m_drawMode)
			{
				uint64_t state = 0
							   | BGFX_STATE_RGB_WRITE
							   | BGFX_STATE_ALPHA_WRITE
							   | BGFX_STATE_DEPTH_WRITE
							   | BGFX_STATE_CULL_CCW
							   | BGFX_STATE_MSAA
							   | BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
							   ;
				meshSubmit(m_meshes[m_meshSelection].m_mesh, 0, m_wfProgram, m_meshes[m_meshSelection].m_mtx, state);
			}
			else
			{
				uint64_t state = 0
							   | BGFX_STATE_RGB_WRITE
							   | BGFX_STATE_ALPHA_WRITE
							   | BGFX_STATE_DEPTH_TEST_LESS
							   | BGFX_STATE_DEPTH_WRITE
							   | BGFX_STATE_CULL_CCW
							   | BGFX_STATE_MSAA
							   ;
				meshSubmit(m_meshes[m_meshSelection].m_mesh, 0, m_meshProgram, m_meshes[m_meshSelection].m_mtx, state);
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	bgfx::ProgramHandle m_wfProgram;
	bgfx::ProgramHandle m_meshProgram;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	uint32_t m_oldWidth;
	uint32_t m_oldHeight;
	uint32_t m_oldReset;

	Camera m_camera;
	Mouse m_mouse;
	Uniforms m_uniforms;
	MeshMtx m_meshes[3];
	uint32_t m_meshSelection;
	uint32_t m_drawMode; // Holds data for 'DrawMode'.

	bool m_showWfColor;
	int32_t m_scrollArea;
};

ENTRY_IMPLEMENT_MAIN(ExampleWireframe);
