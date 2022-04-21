/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "common.h"
#include "bgfx_utils.h"

#include <bx/uint32_t.h>
#include <bx/thread.h>
#include <bx/os.h>
#include "imgui/imgui.h"

#include <bgfx/embedded_shader.h>

// embedded shaders
#include "vs_drawstress.bin.h"
#include "fs_drawstress.bin.h"

namespace
{

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_drawstress),
	BGFX_EMBEDDED_SHADER(fs_drawstress),

	BGFX_EMBEDDED_SHADER_END()
};

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
	}

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

static const float s_mod[6][3] =
{
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 0.0f, 1.0f, 1.0f },
};

#if BX_PLATFORM_EMSCRIPTEN
static const int64_t highwm = 1000000/35;
static const int64_t lowwm  = 1000000/27;
#else
static const int64_t highwm = 1000000/65;
static const int64_t lowwm  = 1000000/57;
#endif // BX_PLATFORM_EMSCRIPTEN

int32_t threadFunc(bx::Thread* _thread, void* _userData);

class ExampleDrawStress : public entry::AppI
{
public:
	ExampleDrawStress(const char* _name, const char* _description, const char* _url)
		: entry::AppI(_name, _description, _url)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_NONE;
		m_reset  = BGFX_RESET_NONE;

		m_autoAdjust = true;
		m_scrollArea = 0;
		m_dim        = 16;
		m_maxDim     = 40;
		m_transform  = 0;

		m_timeOffset = bx::getHPCounter();

		m_deltaTimeNs    = 0;
		m_deltaTimeAvgNs = 0;
		m_numFrames      = 0;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		const bgfx::Caps* caps = bgfx::getCaps();
		m_maxDim = (int32_t)bx::pow(float(caps->limits.maxDrawCalls), 1.0f/3.0f);

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

		bgfx::RendererType::Enum type = bgfx::getRendererType();

		// Create program from shaders.
		m_program = bgfx::createProgram(
			  bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_drawstress")
			, bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_drawstress")
			, true /* destroy shaders when program is destroyed */
			);

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
			  bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
			, PosColorVertex::ms_layout
			);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) ) );

		// Imgui.
		imguiCreate();

		m_maxThreads = bx::min<int32_t>(caps->limits.maxEncoders, BX_COUNTOF(m_thread) );
		m_numThreads = (m_maxThreads+1)/2;

		for (int32_t ii = 0; ii < m_maxThreads; ++ii)
		{
			m_thread[ii].init(threadFunc, this);
		}
	}

	int shutdown() override
	{
		for (int32_t ii = 0; ii < m_maxThreads; ++ii)
		{
			m_thread[ii].push(reinterpret_cast<void*>(UINTPTR_MAX) );
			m_thread[ii].shutdown();
		}

		// Cleanup.
		imguiDestroy();
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	int32_t thread(bx::Thread* _thread)
	{
		for (;;)
		{
			union
			{
				void* ptr;
				uintptr_t id;

			} cast;

			cast.ptr = _thread->pop();
			if (UINTPTR_MAX == cast.id)
			{
				break;
			}

			const uint32_t numThreads = uint32_t(cast.id);
			const uint32_t idx = uint32_t(_thread - m_thread);
			const uint32_t num = uint32_t(m_dim)/numThreads;
			const uint32_t rem = idx == numThreads-1 ? uint32_t(m_dim)%numThreads : 0;
			const uint32_t xx  = idx*num;
			submit(idx+1, xx, num + rem);
		}

		return bx::kExitSuccess;
	}

	void submit(uint32_t _tid, uint32_t _xstart, uint32_t _num)
	{
		bgfx::Encoder* encoder = bgfx::begin();
		if (0 != _tid)
		{
			m_sync.post();
		}

		if (NULL != encoder)
		{
			const int64_t now = bx::getHPCounter();
			const double freq = double(bx::getHPFrequency() );
			float time = (float)( (now-m_timeOffset)/freq);

			const float* mod = s_mod[_tid%BX_COUNTOF(s_mod)];

			float mtxS[16];
			const float scale = 0 == m_transform ? 0.25f : 0.0f;
			bx::mtxScale(mtxS, scale, scale, scale);

			const float step = 0.6f;
			float pos[3];
			pos[0] = -step*m_dim / 2.0f;
			pos[1] = -step*m_dim / 2.0f;
			pos[2] = -15.0;

			for (uint32_t zz = 0; zz < uint32_t(m_dim); ++zz)
			{
				for (uint32_t yy = 0; yy < uint32_t(m_dim); ++yy)
				{
					for (uint32_t xx = _xstart, xend = _xstart+_num; xx < xend; ++xx)
					{
						float mtxR[16];
						bx::mtxRotateXYZ(mtxR
							, (time + xx*0.21f)*mod[0]
							, (time + yy*0.37f)*mod[1]
							, (time + zz*0.13f)*mod[2]
							);

						float mtx[16];
						bx::mtxMul(mtx, mtxS, mtxR);

						mtx[12] = pos[0] + float(xx)*step;
						mtx[13] = pos[1] + float(yy)*step;
						mtx[14] = pos[2] + float(zz)*step;

						encoder->setTransform(mtx);
						encoder->setVertexBuffer(0, m_vbh);
						encoder->setIndexBuffer(m_ibh);
						encoder->setState(BGFX_STATE_DEFAULT);
						encoder->submit(0, m_program);
					}
				}
			}

			bgfx::end(encoder);
		}
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t hpFreq = bx::getHPFrequency();
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(hpFreq);
			const double toMs = 1000.0/freq;

			m_deltaTimeNs += frameTime*1000000/hpFreq;

			if (m_deltaTimeNs > 1000000)
			{
				m_deltaTimeAvgNs = m_deltaTimeNs / bx::max<int64_t>(1, m_numFrames);

				if (m_autoAdjust)
				{
					if (m_deltaTimeAvgNs < highwm)
					{
						m_dim = bx::uint32_min(m_dim + 2, m_maxDim);
					}
					else if (m_deltaTimeAvgNs > lowwm)
					{
						m_dim = bx::uint32_max(m_dim - 1, 2);
					}
				}

				m_deltaTimeNs = 0;
				m_numFrames   = 0;
			}
			else
			{
				++m_numFrames;
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
				  ImVec2((float)m_width - (float)m_width / 4.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2((float)m_width / 4.0f, (float)m_height / 2.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			ImGui::RadioButton("Rotate",&m_transform,0);
			ImGui::RadioButton("No fragments",&m_transform,1);
			ImGui::Separator();

			ImGui::Checkbox("Auto adjust", &m_autoAdjust);

			ImGui::SliderInt("Num threads", &m_numThreads, 1, m_maxThreads);
			const uint32_t numThreads = m_numThreads;

			ImGui::SliderInt("Dim", &m_dim, 5, m_maxDim);
			ImGui::Text("Draw calls: %d", m_dim*m_dim*m_dim);
			ImGui::Text("Avg Delta Time (1 second) [ms]: %0.4f", m_deltaTimeAvgNs/1000.0f);

			ImGui::Separator();
			const bgfx::Stats* stats = bgfx::getStats();
			ImGui::Text("GPU %0.6f [ms]", double(stats->gpuTimeEnd - stats->gpuTimeBegin)*1000.0/stats->gpuTimerFreq);
			ImGui::Text("CPU %0.6f [ms]", double(stats->cpuTimeEnd - stats->cpuTimeBegin)*1000.0/stats->cpuTimerFreq);
			ImGui::Text("Waiting for render thread %0.6f [ms]", double(stats->waitRender) * toMs);
			ImGui::Text("Waiting for submit thread %0.6f [ms]", double(stats->waitSubmit) * toMs);

			ImGui::End();

			imguiEndFrame();

			const bx::Vec3 at  = { 0.0f, 0.0f,   0.0f };
			const bx::Vec3 eye = { 0.0f, 0.0f, -35.0f };

			float view[16];
			bx::mtxLookAt(view, eye, at);

			const bgfx::Caps* caps = bgfx::getCaps();
			float proj[16];
			bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, caps->homogeneousDepth);

			// Set view and projection matrix for view 0.
			bgfx::setViewTransform(0, view, proj);

			// Set view 0 default viewport.
			bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			if (1 < numThreads)
			{
				for (uint32_t ii = 0; ii < numThreads; ++ii)
				{
					m_thread[ii].push(reinterpret_cast<void*>(uintptr_t(numThreads) ) );
				}

				for (uint32_t ii = 0; ii < numThreads; ++ii)
				{
					m_sync.wait();
				}
			}
			else
			{
				submit(0, 0, uint32_t(m_dim) );
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	bool     m_autoAdjust;
	int32_t  m_scrollArea;
	int32_t  m_dim;
	int32_t  m_maxDim;
	int32_t  m_transform;
	int32_t  m_numThreads;
	int32_t  m_maxThreads;

	int64_t  m_timeOffset;

	int64_t  m_deltaTimeNs;
	int64_t  m_deltaTimeAvgNs;
	int64_t  m_numFrames;

	bx::Thread m_thread[5];
	bx::Semaphore m_sync;

	bgfx::ProgramHandle m_program;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle  m_ibh;
};

int32_t threadFunc(bx::Thread* _thread, void* _userData)
{
	ExampleDrawStress* self = static_cast<ExampleDrawStress*>(_userData);
	return self->thread(_thread);
}

} // namespace

ENTRY_IMPLEMENT_MAIN(
	  ExampleDrawStress
	, "17-drawstress"
	, "Draw stress, maximizing number of draw calls."
	, "https://bkaradzic.github.io/bgfx/examples.html#drawstress"
	);
