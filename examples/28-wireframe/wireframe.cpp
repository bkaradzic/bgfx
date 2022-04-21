/*
 * Copyright 2016 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

namespace
{

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
		m_target.curr = bx::init::Zero;
		m_target.dest = bx::init::Zero;

		m_pos.curr = { 0.0f, 0.0f, -2.0f };
		m_pos.dest = { 0.0f, 0.0f, -2.0f };

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
		const float cnear = 1.0f;
		const float cfar  = 100.0f;

		const bx::Vec3 toTarget     = bx::sub(m_target.dest, m_pos.dest);
		const float toTargetLen     = bx::length(toTarget);
		const float invToTargetLen  = 1.0f / (toTargetLen + bx::kFloatMin);
		const bx::Vec3 toTargetNorm = bx::mul(toTarget, invToTargetLen);

		float delta  = toTargetLen * _dz;
		float newLen = toTargetLen + delta;
		if ( (cnear  < newLen || _dz < 0.0f)
		&&   (newLen < cfar   || _dz > 0.0f) )
		{
			m_pos.dest = bx::mad(toTargetNorm, delta, m_pos.dest);
		}
	}

	void consumeOrbit(float _amount)
	{
		float consume[2];
		consume[0] = m_orbit[0] * _amount;
		consume[1] = m_orbit[1] * _amount;
		m_orbit[0] -= consume[0];
		m_orbit[1] -= consume[1];

		const bx::Vec3 toPos     = bx::sub(m_pos.curr, m_target.curr);
		const float toPosLen     = bx::length(toPos);
		const float invToPosLen  = 1.0f / (toPosLen + bx::kFloatMin);
		const bx::Vec3 toPosNorm = bx::mul(toPos, invToPosLen);

		float ll[2];
		bx::toLatLong(&ll[0], &ll[1], toPosNorm);
		ll[0] += consume[0];
		ll[1] -= consume[1];
		ll[1]  = bx::clamp(ll[1], 0.02f, 0.98f);

		const bx::Vec3 tmp  = bx::fromLatLong(ll[0], ll[1]);
		const bx::Vec3 diff = bx::mul(bx::sub(tmp, toPosNorm), toPosLen);

		m_pos.curr = bx::add(m_pos.curr, diff);
		m_pos.dest = bx::add(m_pos.dest, diff);
	}

	void update(float _dt)
	{
		const float amount = bx::min(_dt / 0.12f, 1.0f);

		consumeOrbit(amount);

		m_target.curr = bx::lerp(m_target.curr, m_target.dest, amount);
		m_pos.curr    = bx::lerp(m_pos.curr,    m_pos.dest,    amount);
	}

	void envViewMtx(float* _mtx)
	{
		const bx::Vec3 toTarget     = bx::sub(m_target.curr, m_pos.curr);
		const float toTargetLen     = bx::length(toTarget);
		const float invToTargetLen  = 1.0f / (toTargetLen + bx::kFloatMin);
		const bx::Vec3 toTargetNorm = bx::mul(toTarget, invToTargetLen);

		const bx::Vec3 right = bx::normalize(bx::cross({ 0.0f, 1.0f, 0.0f }, toTargetNorm) );
		const bx::Vec3 up    = bx::normalize(bx::cross(toTargetNorm, right) );

		_mtx[ 0] = right.x;
		_mtx[ 1] = right.y;
		_mtx[ 2] = right.z;
		_mtx[ 3] = 0.0f;
		_mtx[ 4] = up.x;
		_mtx[ 5] = up.y;
		_mtx[ 6] = up.z;
		_mtx[ 7] = 0.0f;
		_mtx[ 8] = toTargetNorm.x;
		_mtx[ 9] = toTargetNorm.y;
		_mtx[10] = toTargetNorm.z;
		_mtx[11] = 0.0f;
		_mtx[12] = 0.0f;
		_mtx[13] = 0.0f;
		_mtx[14] = 0.0f;
		_mtx[15] = 1.0f;
	}

	struct Interp3f
	{
		bx::Vec3 curr = bx::init::None;
		bx::Vec3 dest = bx::init::None;
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
		m_wfColor[3] = 1.0f;
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
		bgfx::destroy(u_params);
	}

	union
	{
		struct
		{
			/*0*/struct { float m_camPos[3], m_unused0; };
			/*1*/struct { float m_wfColor[4]; };
			/*2*/struct { float m_drawEdges, m_wfThickness, m_unused2[2]; };
		};

		float m_params[NumVec4*4];
	};

	bgfx::UniformHandle u_params;
};

class ExampleWireframe : public entry::AppI
{
public:
	ExampleWireframe(const char* _name, const char* _description, const char* _url)
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
			| BGFX_RESET_MSAA_X16
			;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

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

		m_meshes[0].init("meshes/bunny.bin",      1.0f, 0.0f, bx::kPi, 0.0f, 0.0f, -0.8f,  0.0f);
		m_meshes[1].init("meshes/hollowcube.bin", 1.0f, 0.0f,   0.0f, 0.0f, 0.0f,  0.0f,  0.0f);
		m_meshes[2].init("meshes/orb.bin",        1.2f, 0.0f,   0.0f, 0.0f, 0.0f, -0.65f, 0.0f);

		// Imgui.
		imguiCreate();

		m_oldWidth  = 0;
		m_oldHeight = 0;
		m_oldReset  = m_reset;

		m_meshSelection = 1;
		m_drawMode = DrawMode::WireframeShaded;
	}

	virtual int shutdown() override
	{
		// Cleanup.
		imguiDestroy();

		m_meshes[0].destroy();
		m_meshes[1].destroy();
		m_meshes[2].destroy();

		bgfx::destroy(m_wfProgram);
		bgfx::destroy(m_meshProgram);

		m_uniforms.destroy();

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() override
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
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this);

			ImGui::SetNextWindowPos(
				  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_width / 5.0f, m_height * 0.75f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			ImGui::Separator();
			ImGui::Text("Draw mode:");
			ImGui::RadioButton("Wireframe + Shaded", &m_drawMode, 0);
			ImGui::RadioButton("Wireframe", &m_drawMode, 1);
			ImGui::RadioButton("Shaded", &m_drawMode, 2);

			const bool wfEnabled = (DrawMode::Shaded != m_drawMode);
			if ( wfEnabled )
			{
				ImGui::Separator();

				ImGui::ColorWheel("Color", m_uniforms.m_wfColor, 0.6f);
				ImGui::SliderFloat("Thickness", &m_uniforms.m_wfThickness, 0.6f, 2.2f);
			}

			ImGui::Separator();
			ImGui::Text("Mesh:");
			{
				bool meshChanged = false;
				meshChanged |= ImGui::RadioButton("Bunny", &m_meshSelection, 0);
				meshChanged |= ImGui::RadioButton("Hollowcubes", &m_meshSelection, 1);
				meshChanged |= ImGui::RadioButton("Orb", &m_meshSelection, 2);

				if (meshChanged)
				{
					m_camera.reset();
				}
			}

			ImGui::End();
			imguiEndFrame();

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const float deltaTimeSec = float(double(frameTime)/freq);

			// Setup view.
			bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
			bgfx::setViewClear(0, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);

			const bool mouseOverGui = ImGui::MouseOverArea();
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
			bx::memCopy(m_uniforms.m_camPos, &m_camera.m_pos.curr.x, 3*sizeof(float));
			m_camera.mtxLookAt(view);
			bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
			bgfx::setViewTransform(0, view, proj);

			m_uniforms.m_drawEdges = (DrawMode::WireframeShaded == m_drawMode) ? 1.0f : 0.0f;
			m_uniforms.submit();

			if (DrawMode::Wireframe == m_drawMode)
			{
				uint64_t state = 0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					| BGFX_STATE_WRITE_Z
					| BGFX_STATE_CULL_CCW
					| BGFX_STATE_MSAA
					| BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
					;
				meshSubmit(m_meshes[m_meshSelection].m_mesh, 0, m_wfProgram, m_meshes[m_meshSelection].m_mtx, state);
			}
			else
			{
				uint64_t state = 0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					| BGFX_STATE_DEPTH_TEST_LESS
					| BGFX_STATE_WRITE_Z
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
	int32_t m_meshSelection;
	int32_t m_drawMode; // Holds data for 'DrawMode'.
};

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleWireframe
	, "28-wirefame"
	, "Drawing wireframe mesh."
	, "https://bkaradzic.github.io/bgfx/examples.html#wireframe"
	);
