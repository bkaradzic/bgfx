/*
* Copyright 2021 elven cache. All rights reserved.
* License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
*/

/*
* Implement bokeh depth of field as described in the blog post here:
* https://web.archive.org/web/20201215123940/https://blog.tuxedolabs.com/2018/05/04/bokeh-depth-of-field-in-single-pass.html
*
* Additionally, implement the optimizations discussed in the closing paragraph.
* Apply the effect in multiple passes. Calculate the circle of confusion and store
* in the alpha channel while downsampling the image. Then compute depth of field
* at this lower res, storing sample size in alpha. Then composite the blurred image,
* based on the sample size. Compositing the lower res like this can lead to blocky
* edges where there's a depth discontinuity and the blur is just enough. May be
* an area to improve on.
*
* Provide an alternate means of determining radius of current sample when blurring.
* I find the blog post's sample pattern to be difficult to directly reason about. It
* is not obvious, given the parameters, how many samples will be taken. And it can
* be very many samples. Though the results are good. The 'sqrt' pattern chosen here
* looks alright and allows for the number of samples to be set directly. If you are
* going to use this in a project, may be worth exploring additional sample patterns.
* And certainly update the shader to remove the pattern choice from inside the
* sample loop.
*/


#include <common.h>
#include <camera.h>
#include <bgfx_utils.h>
#include <imgui/imgui.h>
#include <bx/rng.h>
#include <bx/os.h>


namespace {

#define FRAMEBUFFER_RT_COLOR       0
#define FRAMEBUFFER_RT_DEPTH       1
#define FRAMEBUFFER_RENDER_TARGETS 2

enum Meshes
{
	MeshCube = 0,
	MeshHollowCube
};

static const char * s_meshPaths[] =
{
	"meshes/cube.bin",
	"meshes/hollowcube.bin"
};

static const float s_meshScale[] =
{
	0.45f,
	0.30f
};

// Vertex decl for our screen space quad (used in deferred rendering)
struct PosTexCoord0Vertex
{
	float m_x;
	float m_y;
	float m_z;
	float m_u;
	float m_v;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosTexCoord0Vertex::ms_layout;

struct PassUniforms
{
	enum { NumVec4 = 4 };

	void init() {
		u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4, NumVec4);
	};

	void submit() const {
		bgfx::setUniform(u_params, m_params, NumVec4);
	}

	void destroy() {
		bgfx::destroy(u_params);
	}

	union
	{
		struct
		{
			/* 0    */ struct { float m_depthUnpackConsts[2]; float m_frameIdx; float m_lobeRotation; };
			/* 1    */ struct { float m_ndcToViewMul[2]; float m_ndcToViewAdd[2]; };
			/* 2    */ struct { float m_blurSteps; float m_lobeCount; float m_lobeRadiusMin; float m_lobeRadiusDelta2x; };
			/* 3    */ struct { float m_maxBlurSize; float m_focusPoint; float m_focusScale; float m_radiusScale; };
		};

		float m_params[NumVec4 * 4];
	};

	bgfx::UniformHandle u_params;
};

struct ModelUniforms
{
	enum { NumVec4 = 2 };

	void init() {
		u_params = bgfx::createUniform("u_modelParams", bgfx::UniformType::Vec4, NumVec4);
	};

	void submit() const {
		bgfx::setUniform(u_params, m_params, NumVec4);
	};

	void destroy() {
		bgfx::destroy(u_params);
	}

	union
	{
		struct
		{
			/* 0 */ struct { float m_color[3]; float m_unused0; };
			/* 1 */ struct { float m_lightPosition[3]; float m_unused1; };
		};

		float m_params[NumVec4 * 4];
	};

	bgfx::UniformHandle u_params;
};

struct RenderTarget
{
	void init(uint32_t _width, uint32_t _height, bgfx::TextureFormat::Enum _format, uint64_t _flags)
	{
		m_texture = bgfx::createTexture2D(uint16_t(_width), uint16_t(_height), false, 1, _format, _flags);
		const bool destroyTextures = true;
		m_buffer = bgfx::createFrameBuffer(1, &m_texture, destroyTextures);
	}

	void destroy()
	{
		// also responsible for destroying texture
		bgfx::destroy(m_buffer);
	}

	bgfx::TextureHandle m_texture;
	bgfx::FrameBufferHandle m_buffer;
};

void screenSpaceQuad(bool _originBottomLeft, float _width = 1.0f, float _height = 1.0f)
{
	if (3 == bgfx::getAvailTransientVertexBuffer(3, PosTexCoord0Vertex::ms_layout))
	{
		bgfx::TransientVertexBuffer vb;
		bgfx::allocTransientVertexBuffer(&vb, 3, PosTexCoord0Vertex::ms_layout);
		PosTexCoord0Vertex* vertex = (PosTexCoord0Vertex*)vb.data;

		const float minx = -_width;
		const float maxx =  _width;
		const float miny = 0.0f;
		const float maxy =  _height * 2.0f;

		const float minu = -1.0f;
		const float maxu =  1.0f;

		const float zz = 0.0f;

		float minv = 0.0f;
		float maxv = 2.0f;

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
		vertex[0].m_u = minu;
		vertex[0].m_v = minv;

		vertex[1].m_x = maxx;
		vertex[1].m_y = miny;
		vertex[1].m_z = zz;
		vertex[1].m_u = maxu;
		vertex[1].m_v = minv;

		vertex[2].m_x = maxx;
		vertex[2].m_y = maxy;
		vertex[2].m_z = zz;
		vertex[2].m_u = maxu;
		vertex[2].m_v = maxv;

		bgfx::setVertexBuffer(0, &vb);
	}
}

void vec2Set(float* _v, float _x, float _y)
{
	_v[0] = _x;
	_v[1] = _y;
}

class ExampleBokeh : public entry::AppI
{
public:
	ExampleBokeh(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
		, m_currFrame(UINT32_MAX)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width = _width;
		m_height = _height;
		m_debug = BGFX_DEBUG_NONE;
		m_reset = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.platformData.nwh  = entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
		init.platformData.ndt  = entry::getNativeDisplayHandle();
		init.platformData.type = entry::getNativeWindowHandleType();
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Create uniforms for screen passes and models
		m_uniforms.init();
		m_modelUniforms.init();

		// Create texture sampler uniforms (used when we bind textures)
		s_albedo = bgfx::createUniform("s_albedo", bgfx::UniformType::Sampler);
		s_color = bgfx::createUniform("s_color", bgfx::UniformType::Sampler);
		s_normal = bgfx::createUniform("s_normal", bgfx::UniformType::Sampler);
		s_depth = bgfx::createUniform("s_depth", bgfx::UniformType::Sampler);
		s_blurredColor = bgfx::createUniform("s_blurredColor", bgfx::UniformType::Sampler);

		// Create program from shaders.
		m_forwardProgram			= loadProgram("vs_bokeh_forward",		"fs_bokeh_forward");
		m_gridProgram				= loadProgram("vs_bokeh_forward",		"fs_bokeh_forward_grid");
		m_copyProgram				= loadProgram("vs_bokeh_screenquad",	"fs_bokeh_copy");
		m_copyLinearToGammaProgram	= loadProgram("vs_bokeh_screenquad",	"fs_bokeh_copy_linear_to_gamma");
		m_linearDepthProgram		= loadProgram("vs_bokeh_screenquad",	"fs_bokeh_linear_depth");
		m_dofSinglePassProgram		= loadProgram("vs_bokeh_screenquad",	"fs_bokeh_dof_single_pass");
		m_dofDownsampleProgram		= loadProgram("vs_bokeh_screenquad",	"fs_bokeh_dof_downsample");
		m_dofQuarterProgram			= loadProgram("vs_bokeh_screenquad",	"fs_bokeh_dof_second_pass");
		m_dofCombineProgram			= loadProgram("vs_bokeh_screenquad",	"fs_bokeh_dof_combine");
		m_dofDebugProgram			= loadProgram("vs_bokeh_screenquad",	"fs_bokeh_dof_debug");

		// Load some meshes
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
		{
			m_meshes[ii] = meshLoad(s_meshPaths[ii]);
		}

		m_groundTexture = loadTexture("textures/fieldstone-rgba.dds");
		m_normalTexture = loadTexture("textures/fieldstone-n.dds");

		m_recreateFrameBuffers = false;
		createFramebuffers();

		// Vertex decl
		PosTexCoord0Vertex::init();

		// Init camera
		cameraCreate();
		cameraSetPosition({ 0.0f, 2.5f, -20.0f });
		cameraSetVerticalAngle(-0.3f);
		m_fovY = 60.0f;

		// Init "prev" matrices, will be same for first frame
		cameraGetViewMtx(m_view);
		bx::mtxProj(m_proj, m_fovY, float(m_size[0]) / float(m_size[1]), 0.01f, 100.0f,  bgfx::getCaps()->homogeneousDepth);

		m_bokehTexture.idx = bgfx::kInvalidHandle;
		updateDisplayBokehTexture(m_radiusScale, m_maxBlurSize, m_lobeCount, (1.0f-m_lobePinch), 1.0f, m_lobeRotation);

		imguiCreate();
	}

	int32_t shutdown() override
	{
		for (uint32_t ii = 0; ii < BX_COUNTOF(s_meshPaths); ++ii)
		{
			meshUnload(m_meshes[ii]);
		}

		bgfx::destroy(m_normalTexture);
		bgfx::destroy(m_groundTexture);
		bgfx::destroy(m_bokehTexture);

		bgfx::destroy(m_forwardProgram);
		bgfx::destroy(m_gridProgram);
		bgfx::destroy(m_copyProgram);
		bgfx::destroy(m_copyLinearToGammaProgram);
		bgfx::destroy(m_linearDepthProgram);
		bgfx::destroy(m_dofSinglePassProgram);
		bgfx::destroy(m_dofDownsampleProgram);
		bgfx::destroy(m_dofQuarterProgram);
		bgfx::destroy(m_dofCombineProgram);
		bgfx::destroy(m_dofDebugProgram);

		m_uniforms.destroy();
		m_modelUniforms.destroy();

		bgfx::destroy(s_albedo);
		bgfx::destroy(s_color);
		bgfx::destroy(s_normal);
		bgfx::destroy(s_depth);
		bgfx::destroy(s_blurredColor);

		destroyFramebuffers();

		cameraDestroy();

		imguiDestroy();

		bgfx::shutdown();

		return 0;
	}

	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
		{
			// skip processing when minimized, otherwise crashing
			if (0 == m_width || 0 == m_height)
			{
				return true;
			}

			// Update frame timer
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency());
			const float deltaTime = float(frameTime / freq);
			const bgfx::Caps* caps = bgfx::getCaps();

			if (m_size[0] != (int32_t)m_width
			||  m_size[1] != (int32_t)m_height
			||  m_recreateFrameBuffers)
			{
				destroyFramebuffers();
				createFramebuffers();
				m_recreateFrameBuffers = false;
			}

			// update animation time
			const float rotationSpeed = 0.75f;
			m_animationTime += deltaTime * rotationSpeed;
			if (bx::kPi2 < m_animationTime)
			{
				m_animationTime -= bx::kPi2;
			}

			// Update camera
			cameraUpdate(deltaTime*0.15f, m_mouseState, ImGui::MouseOverArea() );

			cameraGetViewMtx(m_view);

			updateUniforms();

			bx::mtxProj(m_proj, m_fovY, float(m_size[0]) / float(m_size[1]), 0.01f, 100.0f, caps->homogeneousDepth);
			bx::mtxProj(m_proj2, m_fovY, float(m_size[0]) / float(m_size[1]), 0.01f, 100.0f, false);

			bgfx::ViewId view = 0;

			// Draw models into scene
			{
				bgfx::setViewName(view, "forward scene");
				bgfx::setViewClear(view
					, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
					, 0x7fb8ffff // clear to a sky blue
					, 1.0f
					, 0
				);

				bgfx::setViewRect(view, 0, 0, uint16_t(m_size[0]), uint16_t(m_size[1]));
				bgfx::setViewTransform(view, m_view, m_proj);
				bgfx::setViewFrameBuffer(view, m_frameBuffer);

				bgfx::setState(0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					| BGFX_STATE_WRITE_Z
					| BGFX_STATE_DEPTH_TEST_LESS
					);

				drawAllModels(view, m_forwardProgram, m_modelUniforms);

				++view;
			}

			float orthoProj[16];
			bx::mtxOrtho(orthoProj, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, caps->homogeneousDepth);
			{
				// clear out transform stack
				float identity[16];
				bx::mtxIdentity(identity);
				bgfx::setTransform(identity);
			}

			// Convert depth to linear depth for shadow depth compare
			{
				bgfx::setViewName(view, "linear depth");
				bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height));
				bgfx::setViewTransform(view, NULL, orthoProj);
				bgfx::setViewFrameBuffer(view, m_linearDepth.m_buffer);
				bgfx::setState(0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					| BGFX_STATE_DEPTH_TEST_ALWAYS
					);
				bgfx::setTexture(0, s_depth, m_frameBufferTex[FRAMEBUFFER_RT_DEPTH]);
				m_uniforms.submit();
				screenSpaceQuad(caps->originBottomLeft);
				bgfx::submit(view, m_linearDepthProgram);
				++view;
			}

			// optionally, apply dof
			const bool useOrDebugDof = m_useBokehDof || m_showDebugVisualization;
			if (useOrDebugDof)
			{
				view = drawDepthOfField(view, m_frameBufferTex[FRAMEBUFFER_RT_COLOR], orthoProj, caps->originBottomLeft);
			}
			else
			{
				bgfx::setViewName(view, "display");
				bgfx::setViewClear(view
					, BGFX_CLEAR_NONE
					, 0
					, 1.0f
					, 0
				);

				bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height));
				bgfx::setViewTransform(view, NULL, orthoProj);
				bgfx::setViewFrameBuffer(view, BGFX_INVALID_HANDLE);
				bgfx::setState(0
					| BGFX_STATE_WRITE_RGB
					| BGFX_STATE_WRITE_A
					);
				bgfx::setTexture(0, s_color, m_frameBufferTex[FRAMEBUFFER_RT_COLOR]);
				screenSpaceQuad(caps->originBottomLeft);
				bgfx::submit(view, m_copyLinearToGammaProgram);
				++view;
			}

			// Draw UI
			imguiBeginFrame(m_mouseState.m_mx
				, m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				, m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);

			showExampleDialog(this);

			ImGui::SetNextWindowPos(
				ImVec2(m_width - m_width / 4.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				ImVec2(m_width / 4.0f, m_height / 1.35f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);

			{
				ImGui::Checkbox("use bokeh dof", &m_useBokehDof);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("turn effect on and off");

				ImGui::Checkbox("use single pass at full res", &m_useSinglePassBokehDof);
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text("calculate in a single pass at full resolution or use");
					ImGui::Text("multiple passes to compute at lower res and composite");
					ImGui::EndTooltip();
				}

				ImGui::Checkbox("show debug vis", &m_showDebugVisualization);
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::Text("apply coloration to screen. fades from grey to orange with");
					ImGui::Text("increasing foreground blur. from grey to blue in background");
					ImGui::EndTooltip();
				}
				ImGui::Separator();

				bool isChanged = false;

				ImGui::Text("blur controls:");
				isChanged |= ImGui::SliderFloat("max blur size", &m_maxBlurSize, 10.0f, 50.0f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("maximum blur size in screen pixels");

				ImGui::SliderFloat("focusPoint", &m_focusPoint, 1.0f, 20.0f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("distance to focus plane");

				ImGui::SliderFloat("focusScale", &m_focusScale, 0.0f, 10.0f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("multiply focus calculation, larger=tighter focus");
				ImGui::Separator();

				ImGui::Text("bokeh shape and sample controls:");
				isChanged |= ImGui::SliderFloat("radiusScale", &m_radiusScale, 0.5f, 4.0f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("controls number of samples taken");

				isChanged |= ImGui::SliderInt("lobe count", &m_lobeCount, 1, 8);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("using triangle lobes to emulate aperture blades");

				isChanged |= ImGui::SliderFloat("lobe pinch", &m_lobePinch, 0.0f, 1.0f);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("adjust lobe shape, 0=round, 1=starry");

				isChanged |= ImGui::SliderFloat("lobe rotation", &m_lobeRotation, -1.0f, 1.0f);

				if (isChanged)
				{
					updateDisplayBokehTexture(m_radiusScale, m_maxBlurSize, m_lobeCount, (1.0f-m_lobePinch), 1.0f, m_lobeRotation);
				}

				ImGui::Text("number of samples taken: %d", m_sampleCount);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("number of sample taps as determined by radiusScale and maxBlurSize");


				ImGui::Image(m_bokehTexture, ImVec2(128.0f, 128.0f) );
			}

			ImGui::End();

			imguiEndFrame();

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			m_currFrame = bgfx::frame();

			return true;
		}

		return false;
	}

	void drawAllModels(bgfx::ViewId _pass, bgfx::ProgramHandle _program, ModelUniforms & _uniforms)
	{
		const int32_t width = 6;
		const int32_t length = 20;

		float c0[] = {  72.0f/255.0f, 126.0f/255.0f, 149.0f/255.0f }; // blue
		float c1[] = { 235.0f/255.0f, 146.0f/255.0f, 251.0f/255.0f }; // purple
		float c2[] = { 199.0f/255.0f,   0.0f/255.0f,  57.0f/255.0f }; // pink

		for (int32_t zz = 0; zz < length; ++zz)
		{
			// make a color gradient, nothing special about this for example
			float * ca = c0;
			float * cb = c1;
			float lerpVal = float(zz) / float(length);

			if (0.5f <= lerpVal)
			{
				ca = c1;
				cb = c2;
			}
			lerpVal = bx::fract(2.0f*lerpVal);

			float r = bx::lerp(ca[0], cb[0], lerpVal);
			float g = bx::lerp(ca[1], cb[1], lerpVal);
			float b = bx::lerp(ca[2], cb[2], lerpVal);

			for (int32_t xx = 0; xx < width; ++xx)
			{
				const float angle = m_animationTime + float(zz)*(bx::kPi2/length) + float(xx)*(bx::kPiHalf/width);

				const float posX = 2.0f * xx - width + 1.0f;
				const float posY = bx::sin(angle);
				const float posZ = 2.0f * zz - length + 1.0f;

				const float scale = s_meshScale[MeshHollowCube];
				float mtx[16];
				bx::mtxSRT(mtx
					, scale
					, scale
					, scale
					, 0.0f
					, 0.0f
					, 0.0f
					, posX
					, posY
					, posZ
					);

				bgfx::setTexture(0, s_albedo, m_groundTexture);
				bgfx::setTexture(1, s_normal, m_normalTexture);
				_uniforms.m_color[0] = r;
				_uniforms.m_color[1] = g;
				_uniforms.m_color[2] = b;
				_uniforms.submit();

				meshSubmit(m_meshes[MeshHollowCube], _pass, _program, mtx);
			}
		}

		// draw box as ground plane
		{
			const float posY = -2.0f;
			const float scale = length;
			float mtx[16];
			bx::mtxSRT(mtx
				, scale
				, scale
				, scale
				, 0.0f
				, 0.0f
				, 0.0f
				, 0.0f
				, -scale + posY
				, 0.0f
				);

			_uniforms.m_color[0] = 0.5f;
			_uniforms.m_color[1] = 0.5f;
			_uniforms.m_color[2] = 0.5f;
			_uniforms.submit();

			meshSubmit(m_meshes[MeshCube], _pass, m_gridProgram, mtx);
		}
	}

	bgfx::ViewId drawDepthOfField(bgfx::ViewId _pass, bgfx::TextureHandle _colorTexture, float* _orthoProj, bool _originBottomLeft)
	{
		bgfx::ViewId view = _pass;
		bgfx::TextureHandle lastTex = _colorTexture;

		if (m_showDebugVisualization)
		{
			bgfx::setViewName(view, "bokeh dof debug pass");
			bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height));
			bgfx::setViewTransform(view, NULL, _orthoProj);
			bgfx::setViewFrameBuffer(view, BGFX_INVALID_HANDLE);
			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				);
			bgfx::setTexture(0, s_color, lastTex);
			bgfx::setTexture(1, s_depth, m_linearDepth.m_texture);
			m_uniforms.submit();
			screenSpaceQuad(_originBottomLeft);
			bgfx::submit(view, m_dofDebugProgram);
			++view;
		}
		else if (m_useSinglePassBokehDof)
		{
			bgfx::setViewName(view, "bokeh dof single pass");
			bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height));
			bgfx::setViewTransform(view, NULL, _orthoProj);
			bgfx::setViewFrameBuffer(view, BGFX_INVALID_HANDLE);
			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				);
			bgfx::setTexture(0, s_color, lastTex);
			bgfx::setTexture(1, s_depth, m_linearDepth.m_texture);
			m_uniforms.submit();
			screenSpaceQuad(_originBottomLeft);
			bgfx::submit(view, m_dofSinglePassProgram);
			++view;
		}
		else
		{
			unsigned halfWidth = (m_width/2);
			unsigned halfHeight = (m_height/2);

			bgfx::setViewName(view, "bokeh dof downsample");
			bgfx::setViewRect(view, 0, 0, uint16_t(halfWidth), uint16_t(halfHeight));
			bgfx::setViewTransform(view, NULL, _orthoProj);
			bgfx::setViewFrameBuffer(view, m_dofQuarterInput.m_buffer);
			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				);
			bgfx::setTexture(0, s_color, lastTex);
			bgfx::setTexture(1, s_depth, m_linearDepth.m_texture);
			m_uniforms.submit();
			screenSpaceQuad(_originBottomLeft);
			bgfx::submit(view, m_dofDownsampleProgram);
			++view;
			lastTex = m_dofQuarterInput.m_texture;

			/*
				replace the copy with bokeh dof combine
				able to read circle of confusion and color from downsample pass
				along with full res color and depth?
				do we need half res depth? i'm confused about that...
			*/

			bgfx::setViewName(view, "bokeh dof quarter");
			bgfx::setViewRect(view, 0, 0, uint16_t(halfWidth), uint16_t(halfHeight));
			bgfx::setViewTransform(view, NULL, _orthoProj);
			bgfx::setViewFrameBuffer(view, m_dofQuarterOutput.m_buffer);
			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				);
			bgfx::setTexture(0, s_color, lastTex);
			m_uniforms.submit();
			screenSpaceQuad(_originBottomLeft);
			bgfx::submit(view, m_dofQuarterProgram);
			++view;
			lastTex = m_dofQuarterOutput.m_texture;

			bgfx::setViewName(view, "bokeh dof combine");
			bgfx::setViewRect(view, 0, 0, uint16_t(m_width), uint16_t(m_height));
			bgfx::setViewTransform(view, NULL, _orthoProj);
			bgfx::setViewFrameBuffer(view, BGFX_INVALID_HANDLE);
			bgfx::setState(0
				| BGFX_STATE_WRITE_RGB
				| BGFX_STATE_WRITE_A
				| BGFX_STATE_DEPTH_TEST_ALWAYS
				);
			bgfx::setTexture(0, s_color, _colorTexture);
			bgfx::setTexture(1, s_blurredColor, lastTex);
			m_uniforms.submit();
			screenSpaceQuad(_originBottomLeft);
			bgfx::submit(view, m_dofCombineProgram);
			++view;
		}

		return view;
	}

	void createFramebuffers()
	{
		m_size[0] = m_width;
		m_size[1] = m_height;

		const uint64_t bilinearFlags = 0
			| BGFX_TEXTURE_RT
			| BGFX_SAMPLER_U_CLAMP
			| BGFX_SAMPLER_V_CLAMP
			;

		m_frameBufferTex[FRAMEBUFFER_RT_COLOR] = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::RGBA16F, bilinearFlags);
		m_frameBufferTex[FRAMEBUFFER_RT_DEPTH] = bgfx::createTexture2D(uint16_t(m_size[0]), uint16_t(m_size[1]), false, 1, bgfx::TextureFormat::D32F,    bilinearFlags);
		m_frameBuffer = bgfx::createFrameBuffer(BX_COUNTOF(m_frameBufferTex), m_frameBufferTex, true);

		m_linearDepth.init(m_size[0], m_size[1], bgfx::TextureFormat::R16F, bilinearFlags);

		unsigned halfWidth = m_size[0]/2;
		unsigned halfHeight = m_size[1]/2;
		m_dofQuarterInput.init(halfWidth, halfHeight, bgfx::TextureFormat::RGBA16F, bilinearFlags);
		m_dofQuarterOutput.init(halfWidth, halfHeight, bgfx::TextureFormat::RGBA16F, bilinearFlags);
	}

	// all buffers set to destroy their textures
	void destroyFramebuffers()
	{
		bgfx::destroy(m_frameBuffer);

		m_linearDepth.destroy();
		m_dofQuarterInput.destroy();
		m_dofQuarterOutput.destroy();
	}

	void updateUniforms()
	{
		// from assao sample, cs_assao_prepare_depths.sc
		{
			// float depthLinearizeMul = ( clipFar * clipNear ) / ( clipFar - clipNear );
			// float depthLinearizeAdd = clipFar / ( clipFar - clipNear );
			// correct the handedness issue. need to make sure this below is correct, but I think it is.

			float depthLinearizeMul = -m_proj2[3*4+2];
			float depthLinearizeAdd =  m_proj2[2*4+2];

			if (depthLinearizeMul * depthLinearizeAdd < 0)
			{
				depthLinearizeAdd = -depthLinearizeAdd;
			}

			vec2Set(m_uniforms.m_depthUnpackConsts, depthLinearizeMul, depthLinearizeAdd);

			float tanHalfFOVY = 1.0f / m_proj2[1*4+1];	// = tanf( drawContext.Camera.GetYFOV( ) * 0.5f );
			float tanHalfFOVX = 1.0F / m_proj2[0];		// = tanHalfFOVY * drawContext.Camera.GetAspect( );

			if (bgfx::getRendererType() == bgfx::RendererType::OpenGL)
			{
				vec2Set(m_uniforms.m_ndcToViewMul, tanHalfFOVX * 2.0f, tanHalfFOVY * 2.0f);
				vec2Set(m_uniforms.m_ndcToViewAdd, tanHalfFOVX * -1.0f, tanHalfFOVY * -1.0f);
			}
			else
			{
				vec2Set(m_uniforms.m_ndcToViewMul, tanHalfFOVX * 2.0f, tanHalfFOVY * -2.0f);
				vec2Set(m_uniforms.m_ndcToViewAdd, tanHalfFOVX * -1.0f, tanHalfFOVY * 1.0f);
			}
		}

		m_uniforms.m_frameIdx = float(m_currFrame % 8);

		{
			float lightPosition[] = { 0.0f, 6.0f, 10.0f };
			bx::memCopy(m_modelUniforms.m_lightPosition, lightPosition, 3*sizeof(float));
		}

		// bokeh depth of field
		{
			// reduce dimensions by half to go along with smaller render target
			const float blurScale = (m_useSinglePassBokehDof) ? 1.0f : 0.5f;
			m_uniforms.m_blurSteps = m_blurSteps;
			m_uniforms.m_lobeCount = float(m_lobeCount);
			m_uniforms.m_lobeRadiusMin = (1.0f - m_lobePinch);
			m_uniforms.m_lobeRadiusDelta2x = 2.0f * m_lobePinch;
			m_uniforms.m_maxBlurSize = m_maxBlurSize * blurScale;
			m_uniforms.m_focusPoint = m_focusPoint;
			m_uniforms.m_focusScale = m_focusScale;
			m_uniforms.m_radiusScale = m_radiusScale * blurScale;
			m_uniforms.m_lobeRotation = m_lobeRotation;
		}
	}

	static float bokehShapeFromAngle (int _lobeCount, float _radiusMin, float _radiusDelta2x, float _rotation, float _theta)
	{
		// don't shape for 0, 1 blades...
		if (_lobeCount <= 1)
		{
			return 1.0f;
		}

		// divide edge into some number of lobes
		const float invPeriod = float(_lobeCount) / (bx::kPi2);
		float periodFraction = bx::fract(_theta * invPeriod + _rotation);

		// apply triangle shape to each lobe to approximate blades of a camera aperture
		periodFraction = bx::abs(periodFraction - 0.5f);
		return periodFraction * _radiusDelta2x + _radiusMin;
	}

	void updateDisplayBokehTexture(
		float _radiusScale,
		float _maxBlurSize,
		int _lobeCount,
		float _lobeRadiusMin,
		float _lobeRadiusMax,
		float _lobeRotation)
	{
		if (m_bokehTexture.idx != bgfx::kInvalidHandle)
		{
			bgfx::destroy(m_bokehTexture);
		}
		BX_ASSERT(0 < _lobeCount, "");

		const int32_t bokehSize = 128;

		const bgfx::Memory* mem = bgfx::alloc(bokehSize*bokehSize*4);
		bx::memSet(mem->data, 0x00, bokehSize*bokehSize*4);

		const float thetaStep = 2.39996323f; // golden angle
		float loopValue = _radiusScale;
		const float loopEnd = _maxBlurSize;
		float theta = 0.0f;

		// bokeh shape function multiples this by half later
		const float radiusDelta2x = 2.0f * (_lobeRadiusMax - _lobeRadiusMin);
		int32_t counter = 0;

		while (loopValue < loopEnd)
		{
			float radius = loopValue;

			// apply shape to circular distribution
			const float shapeScale = bokehShapeFromAngle(_lobeCount, _lobeRadiusMin, radiusDelta2x, _lobeRotation, theta);
			BX_ASSERT(_lobeRadiusMin <= shapeScale, "");

			float spiralCoordX = bx::cos(theta) * (radius * shapeScale);
			float spiralCoordY = bx::sin(theta) * (radius * shapeScale);
			// normalize for texture display
			spiralCoordX /= _maxBlurSize;
			spiralCoordY /= _maxBlurSize;
			// scale from -1,1 into 0,1 normalized texture space
			spiralCoordX = spiralCoordX * 0.5f + 0.5f;
			spiralCoordY = spiralCoordY * 0.5f + 0.5f;
			// convert to pixel coordinates
			int32_t pixelCoordX = int32_t(bx::floor(spiralCoordX * float(bokehSize-1) + 0.5f));
			int32_t pixelCoordY = int32_t(bx::floor(spiralCoordY * float(bokehSize-1) + 0.5f));

			BX_ASSERT(0 <= pixelCoordX, "");
			BX_ASSERT(0 <= pixelCoordY, "");
			BX_ASSERT(pixelCoordX < bokehSize, "");
			BX_ASSERT(pixelCoordY < bokehSize, "");

			// plot sample position, track for total samples
			uint32_t offset = (pixelCoordY * bokehSize + pixelCoordX) * 4;
			mem->data[offset + 0] = 0xff;
			mem->data[offset + 1] = 0xff;
			mem->data[offset + 2] = 0xff;
			mem->data[offset + 3] = 0xff;
			++counter;

			theta += thetaStep;
			loopValue += (_radiusScale / loopValue);
		}
		m_sampleCount = counter;

		// hoping texture deals with mem
		m_bokehTexture = bgfx::createTexture2D(bokehSize, bokehSize, false, 1
			, bgfx::TextureFormat::BGRA8
			, 0
			| BGFX_SAMPLER_MIN_POINT
			| BGFX_SAMPLER_MIP_POINT
			| BGFX_SAMPLER_MAG_POINT
			, mem
			);
	}


	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	entry::MouseState m_mouseState;

	// Resource handles
	bgfx::ProgramHandle m_forwardProgram;
	bgfx::ProgramHandle m_gridProgram;
	bgfx::ProgramHandle m_copyProgram;
	bgfx::ProgramHandle m_copyLinearToGammaProgram;
	bgfx::ProgramHandle m_linearDepthProgram;
	bgfx::ProgramHandle m_dofSinglePassProgram;
	bgfx::ProgramHandle m_dofDownsampleProgram;
	bgfx::ProgramHandle m_dofQuarterProgram;
	bgfx::ProgramHandle m_dofCombineProgram;
	bgfx::ProgramHandle m_dofDebugProgram;

	// Shader uniforms
	PassUniforms m_uniforms;
	ModelUniforms m_modelUniforms;

	// Uniforms to identify texture samplers
	bgfx::UniformHandle s_albedo;
	bgfx::UniformHandle s_color;
	bgfx::UniformHandle s_normal;
	bgfx::UniformHandle s_depth;
	bgfx::UniformHandle s_blurredColor;

	bgfx::FrameBufferHandle m_frameBuffer;
	bgfx::TextureHandle m_frameBufferTex[FRAMEBUFFER_RENDER_TARGETS];

	RenderTarget m_linearDepth;
	RenderTarget m_dofQuarterInput;
	RenderTarget m_dofQuarterOutput;

	struct Model
	{
		uint32_t mesh; // Index of mesh in m_meshes
		float position[3];
	};

	Mesh* m_meshes[BX_COUNTOF(s_meshPaths)];
	bgfx::TextureHandle m_groundTexture;
	bgfx::TextureHandle m_normalTexture;
	bgfx::TextureHandle m_bokehTexture;

	uint32_t m_currFrame;
	float m_lightRotation = 0.0f;
	float m_fovY = 60.0f;
	bool m_recreateFrameBuffers = false;
	float m_animationTime = 0.0f;

	float m_view[16];
	float m_proj[16];
	float m_proj2[16];
	int32_t m_size[2];

	// UI parameters
	bool m_useBokehDof = true;
	bool m_useSinglePassBokehDof = false;
	float m_maxBlurSize = 20.0f;
	float m_focusPoint = 5.0f;
	float m_focusScale = 3.0f;
	float m_radiusScale = 0.5f;
	float m_blurSteps = 50.0f;
	bool m_showDebugVisualization = false;
	int32_t m_lobeCount = 6;
	float m_lobePinch = 0.2f;
	float m_lobeRotation = 0.0f;
	int32_t m_sampleCount = 0;
};

} // namespace

ENTRY_IMPLEMENT_MAIN(ExampleBokeh, "45-bokeh", "Bokeh Depth of Field");
